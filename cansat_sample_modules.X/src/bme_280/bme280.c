#include "bme280.h"
#include "sercom2_spi.h"
#include "../usb_serial/usb_serial.h"
#include "../dmac/dmac_transmit.h"
#include <math.h>

#define BME280_DIG_T1_LSB 0x88
#define BME280_CTRL_HUM   0xF2
#define BME280_CTRL_MEAS  0xF4
#define BME280_CONFIG     0xF5
#define BME280_S32_t int32_t
#define BME280_S64_t int64_t
#define BME280_U32_t uint32_t

volatile static uint16_t dig_T1;
volatile static int16_t dig_T2, dig_T3;

volatile static uint16_t dig_P1;
volatile static int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;

volatile static uint8_t dig_H1, dig_H3;
volatile static int16_t dig_H2;
volatile static int16_t dig_H4, dig_H5;
volatile static int8_t dig_H6;

volatile static int32_t t_fine = 0;

static void SPI_BME280_WriteBytes(const uint8_t* bytes, uint8_t bytecount);
static void SPI_BME280_ReadBytes(uint8_t* readbytes, uint8_t bytecount);
static void SPI_BME280_TempCalibration(void);
static void SPI_BME280_PressureCalibration(void);
static void SPI_BME280_ReadCalibrationData(void);

static void begin_transfer(void) {
    PORT_SEC_REGS->GROUP[0].PORT_OUTCLR = (1U << 1U);
}
static void end_transfer(void) {
    PORT_SEC_REGS->GROUP[0].PORT_OUTSET = (1U << 1U);
}

void SPI_BME280_Initialize(void) {
    PORT_SEC_REGS->GROUP[0].PORT_DIRSET = (1 << 1);
    PORT_SEC_REGS->GROUP[0].PORT_OUTSET = (1 << 1);
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[8] = 0x1U;
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[9] = 0x1U;
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[10] = 0x1U;
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[11] = 0x1U;
    PORT_SEC_REGS->GROUP[0].PORT_PMUX[4] = 0x33U;
    PORT_SEC_REGS->GROUP[0].PORT_PMUX[5] = 0x33U;
    SERCOM2_SPI_Initialize();
    begin_transfer();
    SPI_BME280_SetMode();
    SPI_BME280_ReadCalibrationData();
    SPI_BME280_PressureCalibration();
    end_transfer();
}

static void SPI_BME280_WriteBytes(const uint8_t* bytes, uint8_t bytecount) {
    SERCOM2_SPI_Write(bytes, bytecount);
    while (SERCOM2_SPI_IsBusy()) asm("nop");
}

static void SPI_BME280_ReadBytes(uint8_t* readbytes, uint8_t bytecount) {
    SERCOM2_SPI_Read(readbytes, bytecount);
    while (SERCOM2_SPI_IsBusy()) asm("nop");
}

static void SPI_BME280_ReadCalibrationData(void) {
    uint8_t cmd[] = {0x88};
    uint8_t rxBuffer[25];
    
    begin_transfer();
    SPI_BME280_WriteBytes(cmd, 1);
    SPI_BME280_ReadBytes(rxBuffer, 25);
    end_transfer();
    
    dig_T1 = (rxBuffer[1] << 8) | rxBuffer[0];
    dig_T2 = (rxBuffer[3] << 8) | rxBuffer[2];
    dig_T3 = (rxBuffer[5] << 8) | rxBuffer[4];
    dig_P1 = (rxBuffer[7] << 8) | rxBuffer[6];
    dig_P2 = (rxBuffer[9] << 8) | rxBuffer[8];
    dig_P3 = (rxBuffer[11] << 8) | rxBuffer[10];
    dig_P4 = (rxBuffer[13] << 8) | rxBuffer[12];
    dig_P5 = (rxBuffer[15] << 8) | rxBuffer[14];
    dig_P6 = (rxBuffer[17] << 8) | rxBuffer[16];
    dig_P7 = (rxBuffer[19] << 8) | rxBuffer[18];
    dig_P8 = (rxBuffer[21] << 8) | rxBuffer[20];
    dig_P9 = (rxBuffer[23] << 8) | rxBuffer[22];
    dig_H1 = rxBuffer[24];
    
    uint8_t humCmd[] = {0xE1};
    uint8_t humBuffer[7];
    
    begin_transfer();
    SPI_BME280_WriteBytes(humCmd, 1);
    SPI_BME280_ReadBytes(humBuffer, 7);
    end_transfer();
    
    
    dig_H2 = (humBuffer[1] << 8) | humBuffer[0];
    dig_H3 = humBuffer[2];
    dig_H4 = ((int8_t)humBuffer[3] << 4) | (humBuffer[4] & 0x0F);
    dig_H5 = ((int8_t)humBuffer[5] << 4) | ((humBuffer[4] >> 4) & 0x0F);
    dig_H6 = humBuffer[6];
}


float SPI_BME280_GetTemperature(void) {
    uint8_t cmd = 0xFA;
    uint8_t buffer[3];
    begin_transfer();
    SPI_BME280_WriteBytes(&cmd, 1);
    SPI_BME280_ReadBytes(buffer, 3);
    end_transfer();
    uint32_t adc_T = ((buffer[0] << 16) | (buffer[1] << 8) | buffer[2]) >> 4;
    int32_t var1 = ((((adc_T >> 3) - ((int32_t)dig_T1 << 1))) * (int32_t)dig_T2) >> 11;
    int32_t var2 = (((((adc_T >> 4) - (int32_t)dig_T1) * ((adc_T >> 4) - (int32_t)dig_T1)) >> 12) * (int32_t)dig_T3) >> 14;
    t_fine = var1 + var2;
    return ((t_fine * 5 + 128) >> 8) / 100.0f;
}

float SPI_BME280_GetAltitude(float reference_altitude, float reference_pressure) {
    if (reference_pressure <= 0) {
        return NAN;  // Prevent division by zero
    }
    float relative_pressure = SPI_BME280_GetPressure();
    // Compute altitude using the barometric formula with a reference altitude
    return reference_altitude + (44330.0 * (1.0 - pow(reference_pressure / relative_pressure, 0.1903)));
}



void SPI_BME280_SetMode(void) {
    uint8_t settings1[2] = {0x72, 0x01};
    uint8_t settings2[2] = {0x74, 0b00100110};
    uint8_t settings3[2] = {0x75, 0b00001000};
    begin_transfer();
    SPI_BME280_WriteBytes(settings1, 2);
    SPI_BME280_WriteBytes(settings2, 2);
    SPI_BME280_WriteBytes(settings3, 2);
    end_transfer();
}

static void SPI_BME280_PressureCalibration(void) {
    uint8_t writebytes[1] = {0x8E};
    uint8_t rxBuffer[18];
    
    begin_transfer();
    SPI_BME280_WriteBytes(writebytes, 1);
    SPI_BME280_ReadBytes(rxBuffer, 18);
    end_transfer();
    
    dig_P1 = (rxBuffer[1] << 8) | rxBuffer[0];
    dig_P2 = (rxBuffer[3] << 8) | rxBuffer[2];
    dig_P3 = (rxBuffer[5] << 8) | rxBuffer[4];
    dig_P4 = (rxBuffer[7] << 8) | rxBuffer[6];
    dig_P5 = (rxBuffer[9] << 8) | rxBuffer[8];
    dig_P6 = (rxBuffer[11] << 8) | rxBuffer[10];
    dig_P7 = (rxBuffer[13] << 8) | rxBuffer[12];
    dig_P8 = (rxBuffer[15] << 8) | rxBuffer[14];
    dig_P9 = (rxBuffer[17] << 8) | rxBuffer[16];
}

float SPI_BME280_GetPressure(void) {
    uint8_t cmd[1] = {0xF7};
    uint8_t rxBuffer[3];
    
    begin_transfer();
    SPI_BME280_WriteBytes(cmd, 1);
    SPI_BME280_ReadBytes(rxBuffer, 3);
    end_transfer();
    
    uint32_t adc_P = (rxBuffer[0] << 12) | (rxBuffer[1] << 4) | (rxBuffer[2] >> 4);
    int64_t var1, var2, pressure;
    
    var1 = (int64_t)t_fine - 128000;
    var2 = var1 * var1 * (int64_t)dig_P6;
    var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
    var2 = var2 + (((int64_t)dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)dig_P1) >> 33;
    if (var1 == 0) { return NAN; }                                                         // Don't divide by zero.
    pressure   = 1048576 - adc_P;
    pressure = (((pressure << 31) - var2) * 3125)/var1;
    var1 = (((int64_t)dig_P9) * (pressure >> 13) * (pressure >> 13)) >> 25;
    var2 = (((int64_t)dig_P8) * pressure) >> 19;
    pressure = ((pressure + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);

    return ((uint32_t)pressure)/256.0;
}

float SPI_BME280_GetHumidity(void) {
    uint8_t cmd[1] = {0xFD};
    uint8_t rxBuffer[2];
    
    begin_transfer();
    SPI_BME280_WriteBytes(cmd, 1);
    SPI_BME280_ReadBytes(rxBuffer, 2);
    end_transfer();
    
    BME280_S32_t adc_H = (rxBuffer[0] << 8) | rxBuffer[1];
    BME280_S32_t v_x1_u32r;
    
    v_x1_u32r = (t_fine - ((BME280_S32_t)76800));
    v_x1_u32r = (((((adc_H << 14) - (((BME280_S32_t)dig_H4) << 20) - (((BME280_S32_t)dig_H5) * v_x1_u32r)) + ((BME280_S32_t)16384)) >> 15) * 
                 (((((((v_x1_u32r * ((BME280_S32_t)dig_H6)) >> 10) * (((v_x1_u32r * ((BME280_S32_t)dig_H3)) >> 11) + ((BME280_S32_t)32768))) >> 10) + 
                 ((BME280_S32_t)2097152)) * ((BME280_S32_t)dig_H2) + 8192) >> 14));
    v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((BME280_S32_t)dig_H1)) >> 4));
    v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
    v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
    
    return (float)((BME280_U32_t)(v_x1_u32r >> 12)) / 1024.0;
}