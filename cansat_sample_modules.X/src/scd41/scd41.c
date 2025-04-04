#include "scd41.h"
#include "sercom4_i2c_master.h"
#include "../delay_timer/delay_timer.h"

const int16_t SCD_ADDRESS = 0x62;
static void SCD41_WriteCommand(uint8_t* cmd_array, uint8_t length);
static void SCD41_ReadData(uint8_t *buffer, uint32_t length);

void SCD41_Initialize(void)
{
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[12] = 0x1U;
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[13] = 0x1U;
    PORT_SEC_REGS->GROUP[0].PORT_PMUX[6] = 0x33U;
    SERCOM4_I2C_Initialize();
    delay_ms(1000);
    uint8_t cmd[2] = {0x21, 0xB1};
    SCD41_WriteCommand(cmd, 2);
    delay_ms(1);
    uint8_t cmd1[3] = {0x24, 0x16, 0x0};
    SCD41_WriteCommand(cmd1, 3);
    delay_ms(1);
}

static void SCD41_WriteCommand(uint8_t* cmd_array, uint8_t length) {
    SERCOM4_I2C_Write(SCD_ADDRESS, cmd_array, length);
    while (SERCOM4_I2C_IsBusy());  // Wait for completion
}

static void SCD41_ReadData(uint8_t *buffer, uint32_t length) {
    SERCOM4_I2C_Read(SCD_ADDRESS, buffer, length);
    while (SERCOM4_I2C_IsBusy()); // Wait for completion
}

float SCD41_ReadCO2(void) {
    float co2 = 0;
    uint8_t data[12];
    uint8_t cmd[2] = {0xEC, 0x05};
    SCD41_WriteCommand(cmd, 2);
    SCD41_ReadData(data, 12);
    co2 = (float)((uint16_t) data[0] << 8 | data[1]);
    return co2;
}

    