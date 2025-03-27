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
#include "definitions.h"                // SYS function prototypes

/* typedef for non-secure callback functions */
typedef void (*funcptr_void) (void) __attribute__((cmse_nonsecure_call));
volatile uint8_t delay_pause = 0;


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
        SERCOM3_USART_Write((void *)str, 32);
        while (SERCOM3_USART_WriteIsBusy());
        str++; 
    }
}

void SerialRead(char *buffer, size_t size)
{
    if (SERCOM1_USART_Read(buffer, size))  // Start UART read
    {
        while (SERCOM1_USART_ReadIsBusy());  // Wait until read is complete
    }
}

void TCC0_TimerInitialize( void )
{
    /* Reset TCC */
    TCC0_REGS->TCC_CTRLA = TCC_CTRLA_SWRST_Msk;

    while((TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_SWRST_Msk) == TCC_SYNCBUSY_SWRST_Msk)
    {
        /* Wait for Write Synchronization */
    }

    /* Configure counter mode & prescaler */
    TCC0_REGS->TCC_CTRLA = TCC_CTRLA_PRESCALER_DIV1024 ;
    /* Configure in Match Frequency Mode */
    TCC0_REGS->TCC_WAVE = TCC_WAVE_WAVEGEN_NFRQ;

    /* Configure timer one shot mode */
    TCC0_REGS->TCC_CTRLBSET = (uint8_t)TCC_CTRLBSET_ONESHOT_Msk;
    /* Configure timer period */
    TCC0_REGS->TCC_PER = 234374U;

    /* Clear all interrupt flags */
    TCC0_REGS->TCC_INTFLAG = TCC_INTFLAG_Msk;

    /* Enable interrupt*/
    TCC0_REGS->TCC_INTENSET = (TCC_INTENSET_OVF_Msk);


    while((TCC0_REGS->TCC_SYNCBUSY) != 0U)
    {
        /* Wait for Write Synchronization */
    }
}


void __attribute__((used)) TCC0_InterruptHandler( void )
{
    /* Clear interrupt flags */
    TCC0_REGS->TCC_INTFLAG = TCC_INTFLAG_Msk;
    (void)TCC0_REGS->TCC_INTFLAG;
    delay_pause = 0;
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
    
    TCC0_TimerInitialize();
    TCC0_InterruptHandler();
    
    SerialPrint("Hello\r\n");
    while ( true )
    {   
        SERCOM3_USART_Write("1",1);
        char message[32];
        SerialRead(message, 32);
        SerialPrint(message);
        delay_ms(1000);
    }

    /* Execution should not come here during normal operation */
    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/
