#include "sercom1_usart.h"
#include "pm_sensor.h"
#include "../usb_serial/usb_serial.h"

static bool PMSUsart_ValidData(uint8_t data[32]);
static volatile uint8_t sampled_bytes[32] = {0}; 
static void PMSUSart_Command(uint8_t cmd, uint8_t datah, uint8_t datal);

// static volatile PMS7003_DATABUF sensorData;

void PMS_Initialize(void) {
    SERCOM1_USART_Initialize();
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[16] = 0x1U;
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[17] = 0x1U;
    PORT_SEC_REGS->GROUP[0].PORT_PMUX[8] = 0x22U;
}

void PMSUsart_PassiveMode(void)
{
    PMSUSart_Command(0xe1, 0x00, 0x00);// change to  passive mode command (from datasheet)
    // PMSUSart_Command(0xe4, 0x00, 0x01);//
}

// This function sends the bytes {0x42, 0x4D, cmd, datah, datal, LRCH, LRCL} to PMS (datasheet)
static void PMSUSart_Command(uint8_t cmd, uint8_t datah, uint8_t datal) {
    uint8_t buffer[7] = {0x42, 0x4D, cmd, datah, datal, 0x00, 0x00}; 
    // Compute checksum: sum of all bytes before LRCH/LRCL
    uint16_t checksum = 0;
    for (uint8_t i = 0; i < 5; i++) {  // Sum only the first 5 bytes
        checksum += buffer[i];
    }
    
    // Store checksum in buffer (MSB first)
    buffer[5] = (checksum >> 8) & 0xFF; // LRCH (High byte)
    buffer[6] = checksum & 0xFF;        // LRCL (Low byte)
    
    // Wait until USART TX has enough space
    while (SERCOM1_USART_WriteFreeBufferCountGet() < sizeof(buffer)); 
    // Transmit the formatted string
    SERCOM1_USART_Write((void *)buffer, sizeof(buffer));
}

// This polls the data from the sensor by sending a TX command
void PMS_PollSensorData(void) {
    PMSUSart_Command(0xe2, 0x00, 0x00); // this transmits a command for reading the sensor
    
    while (SERCOM1_USART_ReadCountGet() < 32);
    uint8_t start_byte = 0;
    uint8_t next_byte = 0;
    
    while (start_byte != 0x42 && next_byte != 0x4d) {
        SERCOM1_USART_Read(&start_byte, 1);
        SERCOM1_USART_Read(&next_byte, 1);
    }
    
    sampled_bytes[0] = start_byte;
    sampled_bytes[1] = next_byte;
    
    SERCOM1_USART_Read(sampled_bytes+2, 30);
}

// Read the raw bytes and print them to serial display
void PMSUsart_DebugRead(void) {
    PMS_PollSensorData();
    
    for (uint8_t i = 0; i < 30; i++) {
        USBSerial_Write("%02X ", sampled_bytes[i]); // Print each byte as a hex number
    }
    USBSerial_Write("\r\n");
}

// Always POLL the sensor before running the functions below:
uint16_t PMS_GetDataPM10(void) { // returns the PM10 reading
    uint8_t msb, lsb;
    msb = sampled_bytes[8];
    lsb = sampled_bytes[9];
    return ((uint16_t) msb << 8) | lsb;
}
uint16_t PMS_GetDataPM1(void) {
    uint8_t msb, lsb;
    msb = sampled_bytes[4];
    lsb = sampled_bytes[5];
    return ((uint16_t) msb << 8) | lsb;
}

uint16_t PMS_GetDataPM2_5(void) {
    return ((uint16_t)sampled_bytes[6] << 8) | sampled_bytes[7];
}

// To be used only in active mode
static bool PMSUsart_ValidData(uint8_t data[32]) {
    uint16_t sum = 0;
    uint16_t checksum = ((uint16_t)data[30] << 8) | data[31];
    for(int i=0; i<30; i++){
      sum += data[i];
    }
    if (sum == checksum)
    {
      return 1;
    }
    return 0;
}