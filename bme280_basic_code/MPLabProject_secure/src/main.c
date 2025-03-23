/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <stdio.h>  
#include "definitions.h"                // SYS function prototypes

/* typedef for non-secure callback functions */
typedef void (*funcptr_void) (void) __attribute__((cmse_nonsecure_call));
volatile uint8_t delay_pause = 0;
#define SPI_BUFFER_SIZE 10  // Adjust based on your needs
#define BME280_S32_t int32_t
#define BME280_DIG_T1_LSB 0x88

uint16_t dig_T1;
int16_t dig_T2, dig_T3;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
void BME280_ReadTempCalibration(void) {
    uint8_t command[1];
    uint8_t rxBuffer[6];  // 6 bytes: LSB+MSB for each dig_T1, dig_T2, dig_T3

    command[0] = BME280_DIG_T1_LSB;
    PORT_SEC_REGS->GROUP[0].PORT_OUTCLR = (1U << 1U);
    while (SERCOM2_SPI_IsBusy());

    bool status = SERCOM2_SPI_Write(command, 1);
    while (SERCOM2_SPI_IsBusy());

    if (status && SERCOM2_SPI_Read(rxBuffer, 6)) {
        while (SERCOM2_SPI_IsBusy());

        // Extract calibration values from received buffer
        dig_T1 = (rxBuffer[1] << 8) | rxBuffer[0];  // Unsigned 16-bit
        dig_T2 = (int16_t)((rxBuffer[3] << 8) | rxBuffer[2]);  // Signed 16-bit
        dig_T3 = (int16_t)((rxBuffer[5] << 8) | rxBuffer[4]);  // Signed 16-bit
    }

    PORT_SEC_REGS->GROUP[0].PORT_OUTSET = (1U << 1U);
}

void delay_ms(uint16_t ms) {
    delay_pause = 1U;
        /* In one-shot timer mode, first disable the timer */
    TCC0_REGS->TCC_CTRLA &= ~TCC_CTRLA_ENABLE_Msk;
    while((TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_ENABLE_Msk) == TCC_SYNCBUSY_ENABLE_Msk)
    {
        /* Wait for Write Synchronization */
    }
    TCC0_REGS->TCC_PER = (ms * 46.875);
    while((TCC0_REGS->TCC_SYNCBUSY) != 0U);
    TCC0_REGS->TCC_CTRLA |= TCC_CTRLA_ENABLE_Msk;
    while((TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_ENABLE_Msk) == TCC_SYNCBUSY_ENABLE_Msk)
    {
        /* Wait for Write Synchronization */
    }
    while(delay_pause);
}

void SerialPrint(const char *str)
{
    while (*str)
    {
        SERCOM3_USART_Write((void *)str, 1);
        while (SERCOM3_USART_WriteIsBusy());
        str++; 
    }
}

bool BME280_WriteCommand(uint8_t cmd1, uint8_t cmd2) {
    uint8_t command[2] = { cmd1, cmd2 };
    bool status = SERCOM2_SPI_Write(command, 2);
    while (SERCOM2_SPI_IsBusy());  // Wait for completion
    return status;
}


void BME280_NormalMode(void) {
    // BME280_WriteCommand(cmd1, cmd2);
    uint8_t command[4] = { 0x74, 0b00100011, 0x75, 0b01000 };
    PORT_SEC_REGS->GROUP[0].PORT_OUTCLR = (1U << 1U);
    while (SERCOM2_SPI_IsBusy());
    SERCOM2_SPI_Write(command, 4);
    while (SERCOM2_SPI_IsBusy());  // Wait for completion
    PORT_SEC_REGS->GROUP[0].PORT_OUTSET = (1U << 1U);  
}

void BME280_GetTemp(void) {
    uint8_t cmd1 = 0xFA; 
    // uint8_t cmd2 = (1U << 7 ) | 0xFB; 
    // BME280_WriteCommand(cmd1, cmd2);
    uint8_t command[1] = { cmd1 };
    PORT_SEC_REGS->GROUP[0].PORT_OUTCLR = (1U << 1U);
    while (SERCOM2_SPI_IsBusy()); 
    bool status = SERCOM2_SPI_Write(command, 1);
    while (SERCOM2_SPI_IsBusy());  // Wait for completion
    
    uint8_t rxBuffer[SPI_BUFFER_SIZE];
    // uint8_t msb;
    if (status && SERCOM2_SPI_Read(rxBuffer, 3)) {
        while (SERCOM2_SPI_IsBusy());
        PORT_SEC_REGS->GROUP[0].PORT_OUTSET = (1U << 1U);
        uint8_t T1 = rxBuffer[2];
        uint8_t T2 = rxBuffer[1];
        uint8_t T3 = rxBuffer[0];

        BME280_S32_t adc_T = (T3 << 12 | T2 << 4 | T1);
        
        BME280_S32_t var1, var2;
        BME280_ReadTempCalibration();
        var1 = ((((adc_T>>3) - ((BME280_S32_t)dig_T1<<1))) * ((BME280_S32_t)dig_T2)) >> 11;
        var2 = (((((adc_T>>4) - ((BME280_S32_t)dig_T1)) * ((adc_T>>4) - ((BME280_S32_t)dig_T1))) >> 12) * ((BME280_S32_t)dig_T3)) >> 14;
        BME280_S32_t t_fine = var1 + var2;
        float T = ((t_fine * 5 + 128) >> 8) / 100.0;  // Convert to float

        char message[50];
        sprintf(message, "TEMP: %.2f deg\r\n", T);  // Format as a float with 2 decimal places
        SerialPrint(message);  // Print MSB value
    }  
}

int main ( void )
{
    uint32_t msp_ns = *((uint32_t *)(TZ_START_NS));
    volatile funcptr_void NonSecure_ResetHandler;

    /* Initialize all modules */
    SYS_Initialize ( NULL );

    if (msp_ns != 0xFFFFFFFF)
    {
        /* Set non-secure main stack (MSP_NS) */
        __TZ_set_MSP_NS(msp_ns);

        /* Get non-secure reset handler */
        NonSecure_ResetHandler = (funcptr_void)(*((uint32_t *)((TZ_START_NS) + 4U)));

        /* Start non-secure state software application */
        NonSecure_ResetHandler();
    }
    //PORT_SEC_REGS->GROUP[0].PORT_OUTSET = (1<< 15);
    delay_ms(3000);
    //PORT_SEC_REGS->GROUP[0].PORT_OUTCLR = (1<< 15);
    // PORT_SEC_REGS->GROUP[0].PORT_OUTCLR = (1<< 10);
    BME280_NormalMode();
    while ( true )
    {
        BME280_GetTemp();
        delay_ms(500);
    }

    /* Execution should not come here during normal operation */
    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

