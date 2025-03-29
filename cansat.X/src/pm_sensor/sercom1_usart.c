#include "sercom1_usart.h"

// This is a ring buffer mode USART peripheral
/*
 * The USART peripheral continuously reads received data bits in the background,
 * even when the user is not actively reading from the buffer.
 * These received bits are stored in a ring buffer, which allows for efficient
 * handling of incoming data by the user when needed, without losing any information.
 */

/* SERCOM1 USART baud value for 9600 Hz baud rate */
// BAUD_VALUE = 65536*(1 - 16*BAUD_RATE/CLK_FREQ)
#define SERCOM1_USART_INT_BAUD_VALUE            (65326UL)

static volatile SERCOM_USART_RING_BUFFER_OBJECT sercom1USARTObj;

// *****************************************************************************
// *****************************************************************************
// Section: SERCOM1 USART Interface Routines
// *****************************************************************************
// *****************************************************************************

#define SERCOM1_USART_READ_BUFFER_SIZE      64U
#define SERCOM1_USART_READ_BUFFER_9BIT_SIZE     (64U >> 1U)
#define SERCOM1_USART_RX_INT_DISABLE()      SERCOM1_REGS->USART_INT.SERCOM_INTENCLR = SERCOM_USART_INT_INTENCLR_RXC_Msk
#define SERCOM1_USART_RX_INT_ENABLE()       SERCOM1_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_RXC_Msk

static volatile uint8_t SERCOM1_USART_ReadBuffer[SERCOM1_USART_READ_BUFFER_SIZE];

#define SERCOM1_USART_WRITE_BUFFER_SIZE     32U
#define SERCOM1_USART_WRITE_BUFFER_9BIT_SIZE  (32U >> 1U)
#define SERCOM1_USART_TX_INT_DISABLE()      SERCOM1_REGS->USART_INT.SERCOM_INTENCLR = SERCOM_USART_INT_INTENCLR_DRE_Msk
#define SERCOM1_USART_TX_INT_ENABLE()       SERCOM1_REGS->USART_INT.SERCOM_INTENSET = SERCOM_USART_INT_INTENSET_DRE_Msk

static volatile uint8_t SERCOM1_USART_WriteBuffer[SERCOM1_USART_WRITE_BUFFER_SIZE];

static void NVIC_Initialize( void );

void SERCOM1_USART_Initialize( void )
{
    /*
     * Configures USART Clock Mode
     * Configures TXPO and RXPO
     * Configures Data Order
     * Configures Standby Mode
     * Configures Sampling rate
     * Configures IBON
     */
    SERCOM1_REGS->USART_INT.SERCOM_CTRLA = SERCOM_USART_INT_CTRLA_MODE_USART_INT_CLK | SERCOM_USART_INT_CTRLA_RXPO(0x1UL) | SERCOM_USART_INT_CTRLA_TXPO(0x0UL) | SERCOM_USART_INT_CTRLA_DORD_Msk | SERCOM_USART_INT_CTRLA_IBON_Msk | SERCOM_USART_INT_CTRLA_FORM(0x0UL) | SERCOM_USART_INT_CTRLA_SAMPR(0UL) ;

    /* Configure Baud Rate */
    SERCOM1_REGS->USART_INT.SERCOM_BAUD = (uint16_t)SERCOM_USART_INT_BAUD_BAUD(SERCOM1_USART_INT_BAUD_VALUE);

    /*
     * Configures RXEN
     * Configures TXEN
     * Configures CHSIZE
     * Configures Parity
     * Configures Stop bits
     */
    SERCOM1_REGS->USART_INT.SERCOM_CTRLB = SERCOM_USART_INT_CTRLB_CHSIZE_8_BIT | SERCOM_USART_INT_CTRLB_SBMODE_1_BIT | SERCOM_USART_INT_CTRLB_RXEN_Msk | SERCOM_USART_INT_CTRLB_TXEN_Msk;

    /* Wait for sync */
    while((SERCOM1_REGS->USART_INT.SERCOM_SYNCBUSY) != 0U)
    {
        /* Do nothing */
    }


    /* Enable the UART after the configurations */
    SERCOM1_REGS->USART_INT.SERCOM_CTRLA |= SERCOM_USART_INT_CTRLA_ENABLE_Msk;

    /* Wait for sync */
    while((SERCOM1_REGS->USART_INT.SERCOM_SYNCBUSY) != 0U)
    {
        /* Do nothing */
    }

    /* Initialize instance object */
    sercom1USARTObj.rdCallback = NULL;
    sercom1USARTObj.rdInIndex = 0U;
    sercom1USARTObj.rdOutIndex = 0U;
    sercom1USARTObj.isRdNotificationEnabled = false;
    sercom1USARTObj.isRdNotifyPersistently = false;
    sercom1USARTObj.rdThreshold = 0U;
    sercom1USARTObj.errorStatus = USART_ERROR_NONE;
    sercom1USARTObj.wrCallback = NULL;
    sercom1USARTObj.wrInIndex = 0U;
    sercom1USARTObj.wrOutIndex = 0U;
    sercom1USARTObj.isWrNotificationEnabled = false;
    sercom1USARTObj.isWrNotifyPersistently = false;
    sercom1USARTObj.wrThreshold = 0U;
    if (((SERCOM1_REGS->USART_INT.SERCOM_CTRLB & SERCOM_USART_INT_CTRLB_CHSIZE_Msk) >> SERCOM_USART_INT_CTRLB_CHSIZE_Pos) != 0x01U)
    {
        sercom1USARTObj.rdBufferSize = SERCOM1_USART_READ_BUFFER_SIZE;
        sercom1USARTObj.wrBufferSize = SERCOM1_USART_WRITE_BUFFER_SIZE;
    }
    else
    {
        sercom1USARTObj.rdBufferSize = SERCOM1_USART_READ_BUFFER_9BIT_SIZE;
        sercom1USARTObj.wrBufferSize = SERCOM1_USART_WRITE_BUFFER_9BIT_SIZE;
    }
    /* Enable error interrupt */
    SERCOM1_REGS->USART_INT.SERCOM_INTENSET = (uint8_t)SERCOM_USART_INT_INTENSET_ERROR_Msk;

    /* Enable Receive Complete interrupt */
    SERCOM1_REGS->USART_INT.SERCOM_INTENSET = (uint8_t)SERCOM_USART_INT_INTENSET_RXC_Msk;
    NVIC_Initialize();
}

static void NVIC_Initialize( void )
{

    /* Enable NVIC Controller */
    __DMB();
    __enable_irq();

    /* Enable the interrupt sources and configure the priorities as configured
     * from within the "Interrupt Manager" of MHC. */
    
    NVIC_SetPriority(SERCOM1_2_IRQn, 3);
    NVIC_EnableIRQ(SERCOM1_2_IRQn);
    NVIC_SetPriority(SERCOM1_1_IRQn, 3);
    NVIC_EnableIRQ(SERCOM1_1_IRQn);
    NVIC_SetPriority(SERCOM1_0_IRQn, 3);
    NVIC_EnableIRQ(SERCOM1_0_IRQn);
    NVIC_SetPriority(SERCOM1_OTHER_IRQn, 3);
    NVIC_EnableIRQ(SERCOM1_OTHER_IRQn);
}

#define SERCOM1_HANDLER(name) \
    void __attribute__((interrupt())) name(void) { \
        SERCOM1_USART_InterruptHandler(); \
    }

SERCOM1_HANDLER(SERCOM1_0_Handler)
SERCOM1_HANDLER(SERCOM1_1_Handler)
SERCOM1_HANDLER(SERCOM1_2_Handler)
SERCOM1_HANDLER(SERCOM1_OTHER_Handler)

static void SERCOM1_USART_ErrorClear( void )
{
    uint16_t  u16dummyData = 0;

    /* Clear error flag */
    SERCOM1_REGS->USART_INT.SERCOM_INTFLAG = SERCOM_USART_INT_INTFLAG_ERROR_Msk;

    /* Clear all errors */
    SERCOM1_REGS->USART_INT.SERCOM_STATUS = SERCOM_USART_INT_STATUS_PERR_Msk | SERCOM_USART_INT_STATUS_FERR_Msk | SERCOM_USART_INT_STATUS_BUFOVF_Msk ;

    /* Flush existing error bytes from the RX FIFO */
    while((SERCOM1_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_RXC_Msk) == SERCOM_USART_INT_INTFLAG_RXC_Msk)
    {
        u16dummyData = (uint16_t)SERCOM1_REGS->USART_INT.SERCOM_DATA;
    }

    /* Ignore the warning */
    (void)u16dummyData;
}


/* This routine is only called from ISR. Hence do not disable/enable USART interrupts. */
static inline bool SERCOM1_USART_RxPushByte(uint16_t rdByte)
{
    uint32_t tempInIndex;
    uint32_t rdInIdx;
    bool isSuccess = false;

    tempInIndex = sercom1USARTObj.rdInIndex + 1U;

    if (tempInIndex >= sercom1USARTObj.rdBufferSize)
    {
        tempInIndex = 0U;
    }

    if (tempInIndex == sercom1USARTObj.rdOutIndex)
    {
        /* Queue is full - Report it to the application. Application gets a chance to free up space by reading data out from the RX ring buffer */
        if(sercom1USARTObj.rdCallback != NULL)
        {
            uintptr_t rdContext = sercom1USARTObj.rdContext;
            sercom1USARTObj.rdCallback(SERCOM_USART_EVENT_READ_BUFFER_FULL, rdContext);

            /* Read the indices again in case application has freed up space in RX ring buffer */
            tempInIndex = sercom1USARTObj.rdInIndex + 1U;

            if (tempInIndex >= sercom1USARTObj.rdBufferSize)
            {
                tempInIndex = 0U;
            }
        }
    }

    /* Attempt to push the data into the ring buffer */
    if (tempInIndex != sercom1USARTObj.rdOutIndex)
    {
        if (((SERCOM1_REGS->USART_INT.SERCOM_CTRLB & SERCOM_USART_INT_CTRLB_CHSIZE_Msk) >> SERCOM_USART_INT_CTRLB_CHSIZE_Pos) != 0x01U)
        {
            /* 8-bit */
            rdInIdx = sercom1USARTObj.rdInIndex;

            SERCOM1_USART_ReadBuffer[rdInIdx] = (uint8_t)rdByte;
        }
        else
        {
            /* 9-bit */
            rdInIdx = sercom1USARTObj.rdInIndex << 1U;

            SERCOM1_USART_ReadBuffer[rdInIdx] = (uint8_t)rdByte;
            SERCOM1_USART_ReadBuffer[rdInIdx + 1U] = (uint8_t)(rdByte >> 8U);
        }

        sercom1USARTObj.rdInIndex = tempInIndex;
        isSuccess = true;
    }
    else
    {
        /* Queue is full. Data will be lost. */
    }

    return isSuccess;
}

/* This routine is only called from ISR. Hence do not disable/enable USART interrupts. */
static void SERCOM1_USART_ReadNotificationSend(void)
{
    uint32_t nUnreadBytesAvailable;

    if (sercom1USARTObj.isRdNotificationEnabled == true)
    {
        nUnreadBytesAvailable = SERCOM1_USART_ReadCountGet();

        if(sercom1USARTObj.rdCallback != NULL)
        {
            uintptr_t rdContext = sercom1USARTObj.rdContext;

            if (sercom1USARTObj.isRdNotifyPersistently == true)
            {
                if (nUnreadBytesAvailable >= sercom1USARTObj.rdThreshold)
                {
                    sercom1USARTObj.rdCallback(SERCOM_USART_EVENT_READ_THRESHOLD_REACHED, rdContext);
                }
            }
            else
            {
                if (nUnreadBytesAvailable == sercom1USARTObj.rdThreshold)
                {
                    sercom1USARTObj.rdCallback(SERCOM_USART_EVENT_READ_THRESHOLD_REACHED, rdContext);
                }
            }
        }
    }
}

size_t SERCOM1_USART_Read(uint8_t* pRdBuffer, const size_t size)
{
    size_t nBytesRead = 0U;
    uint32_t rdOutIndex;
    uint32_t rdInIndex;
    uint32_t rdOutIdx;
    uint32_t nBytesReadIdx;

    /* Take a snapshot of indices to avoid creation of critical section */

    rdOutIndex = sercom1USARTObj.rdOutIndex;
    rdInIndex = sercom1USARTObj.rdInIndex;

    while (nBytesRead < size)
    {
        if (rdOutIndex != rdInIndex)
        {
            if (((SERCOM1_REGS->USART_INT.SERCOM_CTRLB & SERCOM_USART_INT_CTRLB_CHSIZE_Msk) >> SERCOM_USART_INT_CTRLB_CHSIZE_Pos) != 0x01U)
            {
                pRdBuffer[nBytesRead] = SERCOM1_USART_ReadBuffer[rdOutIndex];
                nBytesRead += 1U;
                rdOutIndex += 1U;
            }
            else
            {
                rdOutIdx = rdOutIndex << 1U;
                nBytesReadIdx = nBytesRead << 1U;

                pRdBuffer[nBytesReadIdx] = SERCOM1_USART_ReadBuffer[rdOutIdx];
                pRdBuffer[nBytesReadIdx + 1U] = SERCOM1_USART_ReadBuffer[rdOutIdx + 1U];

                rdOutIndex += 1U;
                nBytesRead += 1U;
            }

            if (rdOutIndex >= sercom1USARTObj.rdBufferSize)
            {
                rdOutIndex = 0U;
            }
        }
        else
        {
            /* No more data available in the RX buffer */
            break;
        }
    }

    sercom1USARTObj.rdOutIndex = rdOutIndex;

    return nBytesRead;
}

size_t SERCOM1_USART_ReadCountGet(void)
{
    size_t nUnreadBytesAvailable;
    uint32_t rdOutIndex;
    uint32_t rdInIndex;

    /* Take a snapshot of indices to avoid creation of critical section */
    rdOutIndex = sercom1USARTObj.rdOutIndex;
    rdInIndex = sercom1USARTObj.rdInIndex;

    if ( rdInIndex >=  rdOutIndex)
    {
        nUnreadBytesAvailable =  rdInIndex - rdOutIndex;
    }
    else
    {
        nUnreadBytesAvailable =  (sercom1USARTObj.rdBufferSize -  rdOutIndex) + rdInIndex;
    }

    return nUnreadBytesAvailable;
}

size_t SERCOM1_USART_ReadFreeBufferCountGet(void)
{
    return (sercom1USARTObj.rdBufferSize - 1U) - SERCOM1_USART_ReadCountGet();
}

size_t SERCOM1_USART_ReadBufferSizeGet(void)
{
    return (sercom1USARTObj.rdBufferSize - 1U);
}


bool SERCOM1_USART_TransmitComplete( void )
{
    bool transmitComplete = false;

    if ((SERCOM1_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_TXC_Msk) == SERCOM_USART_INT_INTFLAG_TXC_Msk)
    {
        transmitComplete = true;
    }

    return transmitComplete;
}


/* This routine is only called from ISR. Hence do not disable/enable USART interrupts. */
static bool SERCOM1_USART_TxPullByte(void* pWrData)
{
    bool isSuccess = false;
    uint32_t wrInIndex = sercom1USARTObj.wrInIndex;
    uint32_t wrOutIndex = sercom1USARTObj.wrOutIndex;
    uint32_t wrOutIdx;
    uint8_t* pWrByte = (uint8_t*)pWrData;

    if (wrOutIndex != wrInIndex)
    {
        if (((SERCOM1_REGS->USART_INT.SERCOM_CTRLB & SERCOM_USART_INT_CTRLB_CHSIZE_Msk) >> SERCOM_USART_INT_CTRLB_CHSIZE_Pos) != 0x01U)
        {
            *pWrByte = SERCOM1_USART_WriteBuffer[wrOutIndex];
            wrOutIndex++;
        }
        else
        {
            wrOutIdx = wrOutIndex << 1U;
            pWrByte[0] = SERCOM1_USART_WriteBuffer[wrOutIdx];
            pWrByte[1] = SERCOM1_USART_WriteBuffer[wrOutIdx + 1U];

            wrOutIndex++;
        }


        if (wrOutIndex >= sercom1USARTObj.wrBufferSize)
        {
            wrOutIndex = 0U;
        }

        sercom1USARTObj.wrOutIndex = wrOutIndex;

        isSuccess = true;
    }

    return isSuccess;
}

static inline bool SERCOM1_USART_TxPushByte(uint16_t wrByte)
{
    uint32_t tempInIndex;
    uint32_t wrInIndex = sercom1USARTObj.wrInIndex;
    uint32_t wrOutIndex = sercom1USARTObj.wrOutIndex;
    uint32_t wrInIdx;

    bool isSuccess = false;

    tempInIndex = wrInIndex + 1U;

    if (tempInIndex >= sercom1USARTObj.wrBufferSize)
    {
        tempInIndex = 0U;
    }
    if (tempInIndex != wrOutIndex)
    {
        if (((SERCOM1_REGS->USART_INT.SERCOM_CTRLB & SERCOM_USART_INT_CTRLB_CHSIZE_Msk) >> SERCOM_USART_INT_CTRLB_CHSIZE_Pos) != 0x01U)
        {
            SERCOM1_USART_WriteBuffer[wrInIndex] = (uint8_t)wrByte;
        }
        else
        {
            wrInIdx = wrInIndex << 1U;

            SERCOM1_USART_WriteBuffer[wrInIdx] = (uint8_t)wrByte;
            wrInIdx++;
            SERCOM1_USART_WriteBuffer[wrInIdx] = (uint8_t)(wrByte >> 8U);
        }

        sercom1USARTObj.wrInIndex = tempInIndex;

        isSuccess = true;
    }
    else
    {
        /* Queue is full. Report Error. */
    }

    return isSuccess;
}

/* This routine is only called from ISR. Hence do not disable/enable USART interrupts. */
static void SERCOM1_USART_SendWriteNotification(void)
{
    uint32_t nFreeWrBufferCount;

    if (sercom1USARTObj.isWrNotificationEnabled == true)
    {
        nFreeWrBufferCount = SERCOM1_USART_WriteFreeBufferCountGet();

        if(sercom1USARTObj.wrCallback != NULL)
        {
            uintptr_t wrContext = sercom1USARTObj.wrContext;

            if (sercom1USARTObj.isWrNotifyPersistently == true)
            {
                if (nFreeWrBufferCount >= sercom1USARTObj.wrThreshold)
                {
                    sercom1USARTObj.wrCallback(SERCOM_USART_EVENT_WRITE_THRESHOLD_REACHED, wrContext);
                }
            }
            else
            {
                if (nFreeWrBufferCount == sercom1USARTObj.wrThreshold)
                {
                    sercom1USARTObj.wrCallback(SERCOM_USART_EVENT_WRITE_THRESHOLD_REACHED, wrContext);
                }
            }
        }
    }
}

static size_t SERCOM1_USART_WritePendingBytesGet(void)
{
    size_t nPendingTxBytes;

    /* Take a snapshot of indices to avoid creation of critical section */
    uint32_t wrInIndex = sercom1USARTObj.wrInIndex;
    uint32_t wrOutIndex = sercom1USARTObj.wrOutIndex;

    if ( wrInIndex >= wrOutIndex)
    {
        nPendingTxBytes =  wrInIndex - wrOutIndex;
    }
    else
    {
        nPendingTxBytes =  (sercom1USARTObj.wrBufferSize -  wrOutIndex) + wrInIndex;
    }

    return nPendingTxBytes;
}

size_t SERCOM1_USART_WriteCountGet(void)
{
    size_t nPendingTxBytes;

    nPendingTxBytes = SERCOM1_USART_WritePendingBytesGet();

    return nPendingTxBytes;
}

size_t SERCOM1_USART_Write(uint8_t* pWrBuffer, const size_t size )
{
    size_t nBytesWritten  = 0U;

    while (nBytesWritten < size)
    {
        if (((SERCOM1_REGS->USART_INT.SERCOM_CTRLB & SERCOM_USART_INT_CTRLB_CHSIZE_Msk) >> SERCOM_USART_INT_CTRLB_CHSIZE_Pos) != 0x01U)
        {
            if (SERCOM1_USART_TxPushByte(pWrBuffer[nBytesWritten]) == true)
            {
                nBytesWritten++;
            }
            else
            {
                /* Queue is full, exit the loop */
                break;
            }
        }
        else
        {
            uint16_t halfWordData = (uint16_t)(pWrBuffer[(2U * nBytesWritten) + 1U]);
            halfWordData <<= 8U;
            halfWordData |= (uint16_t)pWrBuffer[2U * nBytesWritten];
            if (SERCOM1_USART_TxPushByte(halfWordData) == true)
            {
                nBytesWritten++;
            }
            else
            {
                /* Queue is full, exit the loop */
                break;
            }
        }
    }

    /* Check if any data is pending for transmission */
    if (SERCOM1_USART_WritePendingBytesGet() > 0U)
    {
        /* Enable TX interrupt as data is pending for transmission */
        SERCOM1_USART_TX_INT_ENABLE();
    }

    return nBytesWritten;
}

size_t SERCOM1_USART_WriteFreeBufferCountGet(void)
{
    return (sercom1USARTObj.wrBufferSize - 1U) - SERCOM1_USART_WriteCountGet();
}

size_t SERCOM1_USART_WriteBufferSizeGet(void)
{
    return (sercom1USARTObj.wrBufferSize - 1U);
}


bool SERCOM1_USART_WriteNotificationEnable(bool isEnabled, bool isPersistent)
{
    bool previousStatus = sercom1USARTObj.isWrNotificationEnabled;

    sercom1USARTObj.isWrNotificationEnabled = isEnabled;

    sercom1USARTObj.isWrNotifyPersistently = isPersistent;

    return previousStatus;
}

void SERCOM1_USART_WriteThresholdSet(uint32_t nBytesThreshold)
{
    if (nBytesThreshold > 0U)
    {
        sercom1USARTObj.wrThreshold = nBytesThreshold;
    }
}

void SERCOM1_USART_WriteCallbackRegister( SERCOM_USART_RING_BUFFER_CALLBACK callback, uintptr_t context)
{
    sercom1USARTObj.wrCallback = callback;

    sercom1USARTObj.wrContext = context;
}



static void __attribute__((used)) SERCOM1_USART_ISR_ERR_Handler( void )
{
    USART_ERROR errorStatus = (USART_ERROR)(SERCOM1_REGS->USART_INT.SERCOM_STATUS & (SERCOM_USART_INT_STATUS_PERR_Msk | SERCOM_USART_INT_STATUS_FERR_Msk | SERCOM_USART_INT_STATUS_BUFOVF_Msk ));

    if(errorStatus != USART_ERROR_NONE)
    {
        /* Save the error to report later */
        sercom1USARTObj.errorStatus = errorStatus;

        /* Clear error flags and flush the error bytes */
        SERCOM1_USART_ErrorClear();

        if(sercom1USARTObj.rdCallback != NULL)
        {
            uintptr_t rdContext = sercom1USARTObj.rdContext;

            sercom1USARTObj.rdCallback(SERCOM_USART_EVENT_READ_ERROR, rdContext);
        }
    }
}

static void __attribute__((used)) SERCOM1_USART_ISR_RX_Handler( void )
{


    while ((SERCOM1_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_RXC_Msk) == SERCOM_USART_INT_INTFLAG_RXC_Msk)
    {
        if (SERCOM1_USART_RxPushByte( (uint16_t)SERCOM1_REGS->USART_INT.SERCOM_DATA) == true)
        {
            SERCOM1_USART_ReadNotificationSend();
        }
        else
        {
            /* UART RX buffer is full */
        }
    }
}

static void __attribute__((used)) SERCOM1_USART_ISR_TX_Handler( void )
{
    uint16_t wrByte;

    while ((SERCOM1_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk) == SERCOM_USART_INT_INTFLAG_DRE_Msk)
    {
        if (SERCOM1_USART_TxPullByte(&wrByte) == true)
        {
            if (((SERCOM1_REGS->USART_INT.SERCOM_CTRLB & SERCOM_USART_INT_CTRLB_CHSIZE_Msk) >> SERCOM_USART_INT_CTRLB_CHSIZE_Pos) != 0x01U)
            {
                SERCOM1_REGS->USART_INT.SERCOM_DATA = (uint8_t)wrByte;
            }
            else
            {
                SERCOM1_REGS->USART_INT.SERCOM_DATA = wrByte;
            }

            SERCOM1_USART_SendWriteNotification();
        }
        else
        {
            /* Nothing to transmit. Disable the data register empty interrupt. */
            SERCOM1_USART_TX_INT_DISABLE();
            break;
        }
    }
}

void __attribute__((used)) SERCOM1_USART_InterruptHandler( void )
{
    bool testCondition = false;
    if(SERCOM1_REGS->USART_INT.SERCOM_INTENSET != 0U)
    {
        /* Checks for error flag */
        testCondition = ((SERCOM1_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_ERROR_Msk) == SERCOM_USART_INT_INTFLAG_ERROR_Msk);
        testCondition = ((SERCOM1_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_ERROR_Msk) == SERCOM_USART_INT_INTENSET_ERROR_Msk) && testCondition;
        if(testCondition)
        {
            SERCOM1_USART_ISR_ERR_Handler();
        }

        testCondition = ((SERCOM1_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk) == SERCOM_USART_INT_INTFLAG_DRE_Msk);
        testCondition = ((SERCOM1_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_DRE_Msk) == SERCOM_USART_INT_INTENSET_DRE_Msk) && testCondition;
        /* Checks for data register empty flag */
        if(testCondition)
        {
            SERCOM1_USART_ISR_TX_Handler();
        }

        /* Checks for receive complete empty flag */
        testCondition = ((SERCOM1_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_RXC_Msk) != 0U);
        testCondition = ((SERCOM1_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_RXC_Msk) != 0U) && testCondition;
        if(testCondition)
        {
            SERCOM1_USART_ISR_RX_Handler();
        }
    }
}