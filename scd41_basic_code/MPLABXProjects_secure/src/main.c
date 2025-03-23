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
const int16_t SCD_ADDRESS = 0x62;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

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

void SCD4x_WriteCommand(uint8_t cmd1, uint8_t cmd2) {
    uint8_t command[2] = { cmd1, cmd2 };
    SERCOM4_I2C_Write(SCD_ADDRESS, command, 2);
    while (SERCOM4_I2C_IsBusy());  // Wait for completion
}

bool SCD4x_ReadData(uint8_t *buffer, uint32_t length) {
    return SERCOM4_I2C_Read(SCD_ADDRESS, buffer, length);
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
    // useful commands for debugging
    PORT_SEC_REGS->GROUP[0].PORT_DIRSET = (1<< 15);
    // PORT_SEC_REGS->GROUP[0].PORT_OUTSET = (1<< 15);
    delay_ms(1000);
    // PORT_SEC_REGS->GROUP[0].PORT_OUTCLR = (1<< 15);
    SCD4x_WriteCommand(0x21, 0xB1);
    delay_ms(5000);
    while ( true )
    {
        float co2, temperature, humidity;
        uint8_t data[12];
        SCD4x_WriteCommand(0xEC, 0x05);
        delay_ms(1);  
        if (SCD4x_ReadData(data, 12)) {

            // Convert Temperature (-45 + 175 * T_raw / 65536)
            temperature = -45.0 + 175.0 * ((uint16_t)data[3] << 8 | data[4]) / 65536.0;
            co2 = (float)((uint16_t)data[0] << 8 | data[1]);
            humidity = 100 * (float)((uint16_t)data[6] << 8 | data[7]) / 65536;
            
            char sensorStr[64];  // Buffer to store formatted output
            sprintf(sensorStr, "CO2: %.0f ppm, Temp: %.2fC, Hum: %.2f%%\r\n", co2, temperature, humidity);
            SerialPrint(sensorStr);
        } else {
            PORT_SEC_REGS->GROUP[0].PORT_OUTCLR = (1<< 15);
        }
        delay_ms(5000);
    }

    /* Execution should not come here during normal operation */
    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

