#include "delay_timer.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data
// *****************************************************************************
// *****************************************************************************
static void NVIC_Initialize( void );
static volatile bool delay_pause = false;
static volatile TCC_CALLBACK_OBJECT TCC0_CallbackObject;
static volatile bool timeout_active = false;
// *****************************************************************************
// *****************************************************************************
// Section: TCC0 Implementation
// *****************************************************************************
// *****************************************************************************
static void (*timeout_callback)(void) = NULL;

void delay_ms(uint16_t ms) {
    delay_pause = true;
        /* In one-shot timer mode, first disable the timer */
    TCC0_REGS->TCC_CTRLA &= ~TCC_CTRLA_ENABLE_Msk;
    while((TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_ENABLE_Msk) == TCC_SYNCBUSY_ENABLE_Msk)
    {
        /* Wait for Write Synchronization */
    }
    TCC0_REGS->TCC_PER = (uint32_t)(ms * 46.875);
    while((TCC0_REGS->TCC_SYNCBUSY) != 0U);
    TCC0_REGS->TCC_CTRLA |= TCC_CTRLA_ENABLE_Msk;
    while((TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_ENABLE_Msk) == TCC_SYNCBUSY_ENABLE_Msk)
    {
        /* Wait for Write Synchronization */
    }
    while(delay_pause);
}

void timeout_ms(uint16_t ms, void (*callback)(void)) {
    while (timeout_active || delay_pause) asm("nop");
    timeout_callback = callback; // Store the callback function
    timeout_active = true;
    /* Disable the timer before configuring */
    TCC0_REGS->TCC_CTRLA &= ~TCC_CTRLA_ENABLE_Msk;
    while ((TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_ENABLE_Msk) == TCC_SYNCBUSY_ENABLE_Msk);

    /* Set the timer period */
    TCC0_REGS->TCC_PER = (uint32_t)(ms * 46.875);
    while ((TCC0_REGS->TCC_SYNCBUSY) != 0U);

    /* Enable interrupt on overflow */
    TCC0_REGS->TCC_INTENSET = TCC_INTENSET_OVF_Msk;

    /* Enable the timer */
    TCC0_REGS->TCC_CTRLA |= TCC_CTRLA_ENABLE_Msk;
    while ((TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_ENABLE_Msk) == TCC_SYNCBUSY_ENABLE_Msk);
}

// *****************************************************************************
/* Initialize the TCC module in Timer mode */
void DelayTimer_Initialize( void )
{
    NVIC_Initialize();
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

    /* Clear all interrupt flags */
    TCC0_REGS->TCC_INTFLAG = TCC_INTFLAG_Msk;

    /* Enable interrupt*/
    TCC0_REGS->TCC_INTENSET = (TCC_INTENSET_OVF_Msk);

    while((TCC0_REGS->TCC_SYNCBUSY) != 0U)
    {
        /* Wait for Write Synchronization */
    }
}

static void NVIC_Initialize( void )
{

    /* Enable NVIC Controller */
    __DMB();
    __enable_irq();

    /* Enable the interrupt sources and configure the priorities as configured
     * from within the "Interrupt Manager" of MHC. */
    
    NVIC_SetPriority(TCC0_IRQn, 3);
    NVIC_EnableIRQ(TCC0_IRQn);
}


void __attribute__((interrupt())) TCC0_Handler( void )
{
    uint32_t status;
    /* Additional local variable to prevent MISRA C violations (Rule 13.x) */
    uintptr_t context;
    context = TCC0_CallbackObject.context;
    status = TCC0_REGS->TCC_INTFLAG;
    /* Clear interrupt flags */
    TCC0_REGS->TCC_INTFLAG = TCC_INTFLAG_Msk;
    (void)TCC0_REGS->TCC_INTFLAG;
    if (timeout_active) {
        if( timeout_callback != NULL)
        {
            timeout_callback();
        }
        timeout_callback = NULL;
        timeout_active = false;
    } else {
        delay_pause = 0;
    }
}
