#include "bme280.h"
#include "sercom2_spi.h"

#define BME280_S32_t int32_t
#define BME280_DIG_T1_LSB 0x88


static void SPI_BME280_WriteBytes(const uint8_t* bytes, uint8_t bytecount);
static void SPI_BME280_ReadBytes(uint8_t* readbytes, uint8_t bytecount);
static void SPI_BME280_ReadTempCalibration();
volatile static int16_t dig_T1, dig_T2, dig_T3;

void SPI_BME280_Initialize( void ) {
    SERCOM2_SPI_Initialize();
    
    PORT_SEC_REGS->GROUP[0].PORT_DIRSET = (1 << 1);
    PORT_SEC_REGS->GROUP[0].PORT_OUTSET = (1 << 1);
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[8] = 0x1U;
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[9] = 0x1U;
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[10] = 0x1U;
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[11] = 0x1U;
    PORT_SEC_REGS->GROUP[0].PORT_PMUX[4] = 0x33U;
    PORT_SEC_REGS->GROUP[0].PORT_PMUX[5] = 0x33U;
    
    SPI_BME280_NormalMode();
    SPI_BME280_ReadTempCalibration();
}

static void SPI_BME280_WriteBytes(const uint8_t* bytes, uint8_t bytecount) {
    // Wait for the transmission to complete (no other transfer in progress)
    //while (SERCOM2_SPI_IsBusy()) asm("nop");
    //SERCOM2_SPI_Write(bytes, bytecount);
    DMAC_ChannelTransfer(DMAC_CHANNEL_0, bytes, (const void *)&SERCOM2_REGS->SPIM.SERCOM_DATA, bytecount);
}

static void SPI_BME280_ReadBytes(uint8_t* readbytes, uint8_t bytecount) {
    SERCOM2_SPI_Read(readbytes, bytecount);
    while (SERCOM2_SPI_IsBusy()) asm("nop");
}

static void begin_transfer(void) {
    PORT_SEC_REGS->GROUP[0].PORT_OUTCLR = (1U << 1U);
}

static void end_transfer(void) {
    PORT_SEC_REGS->GROUP[0].PORT_OUTSET = (1U << 1U);
}

static void SPI_BME280_ReadTempCalibration(void) {
    uint8_t writebytes[1] = {BME280_DIG_T1_LSB};
    uint8_t rxBuffer[6];  // 6 bytes: LSB+MSB for each dig_T1, dig_T2, dig_T3
    
    begin_transfer();
    SPI_BME280_WriteBytes(writebytes, 1);
    SPI_BME280_ReadBytes(rxBuffer, 6);
    // Extract calibration values from received buffer
    dig_T1 = (rxBuffer[1] << 8) | rxBuffer[0];  // Unsigned 16-bit
    dig_T2 = (int16_t)((rxBuffer[3] << 8) | rxBuffer[2]);  // Signed 16-bit
    dig_T3 = (int16_t)((rxBuffer[5] << 8) | rxBuffer[4]);  // Signed 16-bit

    end_transfer();
}

void SPI_BME280_NormalMode(void) {
    uint8_t writebytes[4] = { 0x74, 0b00100011, 0x75, 0b01000 };
    begin_transfer();
    SPI_BME280_WriteBytes(writebytes, 4);
    SPI_BME280_WriteBytes(writebytes, 4);
    SPI_BME280_WriteBytes(writebytes, 4);
    end_transfer();
}

float SPI_BME280_GetTemp(void) {
    uint8_t cmd1[1] = {0xFA}; 
    begin_transfer();
    uint8_t rxBuffer[3];
    SPI_BME280_WriteBytes(cmd1, 1);
    SPI_BME280_ReadBytes(rxBuffer, 3);
    end_transfer();
    
    uint8_t T1 = rxBuffer[2];
    uint8_t T2 = rxBuffer[1];
    uint8_t T3 = rxBuffer[0];

    BME280_S32_t adc_T = (T3 << 12 | T2 << 4 | T1);

    BME280_S32_t var1, var2;
    SPI_BME280_ReadTempCalibration();
    var1 = ((((adc_T>>3) - ((BME280_S32_t)dig_T1<<1))) * ((BME280_S32_t)dig_T2)) >> 11;
    var2 = (((((adc_T>>4) - ((BME280_S32_t)dig_T1)) * ((adc_T>>4) - ((BME280_S32_t)dig_T1))) >> 12) * ((BME280_S32_t)dig_T3)) >> 14;
    BME280_S32_t t_fine = var1 + var2;
    float T = ((t_fine * 5 + 128) >> 8) / 100.0;  // Convert to float
    
    return T;
}