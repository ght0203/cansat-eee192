#include "sercom2_spi.h"


/* SERCOM2 clk freq value for the baud calculation */
#define SERCOM2_Frequency      (48000000UL)

/* SERCOM2 SPI baud value for 1000000 Hz baud rate */
#define SERCOM2_SPIM_BAUD_VALUE         (23UL)

/*Global object to save SPI Exchange related data  */
static volatile SPI_OBJECT sercom2SPIObj;


void SERCOM2_SPI_Initialize(void)
{
    /* Instantiate the SERCOM2 SPI object */
    sercom2SPIObj.callback = NULL ;
    sercom2SPIObj.transferIsBusy = false ;
    sercom2SPIObj.txSize = 0U;
    sercom2SPIObj.rxSize = 0U;

    /* Selection of the Character Size and Receiver Enable */
    SERCOM2_REGS->SPIM.SERCOM_CTRLB = SERCOM_SPIM_CTRLB_CHSIZE_8_BIT | SERCOM_SPIM_CTRLB_RXEN_Msk;
    //SERCOM2_REGS->SPIM.SERCOM_CTRLC =  SERCOM_SPIM_CTRLC_FIFOEN_Msk; // delete if not using

    /* Wait for synchronization */
    while((SERCOM2_REGS->SPIM.SERCOM_SYNCBUSY) != 0U)
    {
        /* Do nothing */
    }

    /* Selection of the Baud Value */
    SERCOM2_REGS->SPIM.SERCOM_BAUD = (uint8_t)SERCOM_SPIM_BAUD_BAUD(SERCOM2_SPIM_BAUD_VALUE);

    SERCOM2_REGS->SPIM.SERCOM_CTRLA = SERCOM_SPIM_CTRLA_MODE_SPI_MASTER | SERCOM_SPIM_CTRLA_DOPO_PAD0 | SERCOM_SPIM_CTRLA_DIPO_PAD3 | SERCOM_SPIM_CTRLA_CPOL_IDLE_LOW | SERCOM_SPIM_CTRLA_CPHA_LEADING_EDGE | SERCOM_SPIM_CTRLA_DORD_MSB | SERCOM_SPIM_CTRLA_ENABLE_Msk ;

    
    /* Wait for synchronization */
    while((SERCOM2_REGS->SPIM.SERCOM_SYNCBUSY) != 0U)
    {
        /* Do nothing */
    }
    __DMB();
    __enable_irq();

    /* Enable the interrupt sources and configure the priorities as configured
     * from within the "Interrupt Manager" of MHC. */
    NVIC_SetPriority(SERCOM2_0_IRQn, 3);
    NVIC_EnableIRQ(SERCOM2_0_IRQn);
    NVIC_SetPriority(SERCOM2_1_IRQn, 3);
    NVIC_EnableIRQ(SERCOM2_1_IRQn);
    NVIC_SetPriority(SERCOM2_2_IRQn, 3);
    NVIC_EnableIRQ(SERCOM2_2_IRQn);
    NVIC_SetPriority(SERCOM2_OTHER_IRQn, 3);
    NVIC_EnableIRQ(SERCOM2_OTHER_IRQn);
}

bool SERCOM2_SPI_TransferSetup(SPI_TRANSFER_SETUP *setup, uint32_t spiSourceClock)
{
    uint32_t baudValue = 0U;

    bool statusValue = false;

    if(spiSourceClock == 0U)
    {
        /* Fetch Master Clock Frequency directly */
        spiSourceClock = SERCOM2_Frequency;
    }

    /* Disable the SPI Module */
    SERCOM2_REGS->SPIM.SERCOM_CTRLA &= ~(SERCOM_SPIM_CTRLA_ENABLE_Msk);

    sercom2SPIObj.rxSize = 0;
    sercom2SPIObj.txSize = 0;

    /* Wait for synchronization */
    while((SERCOM2_REGS->SPIM.SERCOM_SYNCBUSY) != 0U)
    {
        /* Do nothing */
    }

    if(setup != NULL)
    {
        if (setup->clockFrequency <= spiSourceClock/2U)
        {
            baudValue = (spiSourceClock/(2U*(setup->clockFrequency))) - 1U;

            /* Set the lowest possible baud */
            if (baudValue >= 255U)
            {
                baudValue = 255U;
            }

            /* Selection of the Clock Polarity and Clock Phase */
            SERCOM2_REGS->SPIM.SERCOM_CTRLA &= ~(SERCOM_SPIM_CTRLA_CPOL_Msk | SERCOM_SPIM_CTRLA_CPHA_Msk);
            SERCOM2_REGS->SPIM.SERCOM_CTRLA |= (uint32_t)setup->clockPolarity | (uint32_t)setup->clockPhase;

            /* Selection of the Baud Value */
            SERCOM2_REGS->SPIM.SERCOM_BAUD = (uint8_t)baudValue;

            /* Selection of the Character Size */
            SERCOM2_REGS->SPIM.SERCOM_CTRLB &= ~SERCOM_SPIM_CTRLB_CHSIZE_Msk;
            SERCOM2_REGS->SPIM.SERCOM_CTRLB |= (uint32_t)setup->dataBits;

            /* Wait for synchronization */
            while((SERCOM2_REGS->SPIM.SERCOM_SYNCBUSY) != 0U)
            {
                /* Do nothing */
            }

            statusValue = true;
        }
    }

    /* Enabling the SPI Module */
    SERCOM2_REGS->SPIM.SERCOM_CTRLA |= SERCOM_SPIM_CTRLA_ENABLE_Msk;

    /* Wait for synchronization */
    while((SERCOM2_REGS->SPIM.SERCOM_SYNCBUSY) != 0U)
    {
        /* Do nothing */
    }
    return statusValue;
}

#define SERCOM2_HANDLER(name) \
    void __attribute__((interrupt())) name(void) { \
        SERCOM2_SPI_InterruptHandler(); \
    }

SERCOM2_HANDLER(SERCOM2_0_Handler)
SERCOM2_HANDLER(SERCOM2_1_Handler)
SERCOM2_HANDLER(SERCOM2_2_Handler)
SERCOM2_HANDLER(SERCOM2_OTHER_Handler)

void SERCOM2_SPI_CallbackRegister(SERCOM_SPI_CALLBACK callBack, uintptr_t context )
{
    sercom2SPIObj.callback = callBack;

    sercom2SPIObj.context = context;
}

bool SERCOM2_SPI_IsBusy(void)
{
    bool isBusy = false;
    size_t txSize = sercom2SPIObj.txSize;
    bool transferIsBusy = sercom2SPIObj.transferIsBusy;

    if ((sercom2SPIObj.rxSize == 0U) && (txSize == 0U))
    {
        /* This means no transfer has been requested yet; hence SPI is not busy. */
        isBusy = false;
    }
    else
    {
        /* if transmit is not complete or if the state flag is not set, SPI is busy */
        isBusy = (((SERCOM2_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_TXC_Msk) == 0U) || transferIsBusy);
    }
    return isBusy;
}

bool SERCOM2_SPI_IsTransmitterBusy(void)
{
    return ((SERCOM2_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_TXC_Msk) == 0U)? true : false;
}

bool SERCOM2_SPI_WriteRead (void* pTransmitData, size_t txSize, void* pReceiveData, size_t rxSize)
{
    bool isRequestAccepted = false;
    uint32_t dummyData = 0U;
    size_t txSz;

    if (sercom2SPIObj.transferIsBusy == false)
    {
        /* Verify the request */
        if(((txSize > 0U) && (pTransmitData != NULL)) || ((rxSize > 0U) && (pReceiveData != NULL)))
        {
            if((SERCOM2_REGS->SPIM.SERCOM_CTRLB & SERCOM_SPIM_CTRLB_CHSIZE_Msk) == (uint32_t)SPI_DATA_BITS_9)
            {
                /* For 9-bit transmission, the txSize and rxSize must be an even number. */
                if(((txSize > 0U) && ((txSize & 0x01U) != 0U)) || ((rxSize > 0U) && ((rxSize & 0x01U) != 0U)))
                {
                    return isRequestAccepted;
                }
            }

            isRequestAccepted = true;
            sercom2SPIObj.txBuffer = pTransmitData;
            sercom2SPIObj.rxBuffer = pReceiveData;
            sercom2SPIObj.rxCount = 0U;
            sercom2SPIObj.txCount = 0U;
            sercom2SPIObj.dummySize = 0U;

            if(pTransmitData != NULL)
            {
                sercom2SPIObj.txSize = txSize;
            }
            else
            {
                sercom2SPIObj.txSize = 0U;
            }

            if(pReceiveData != NULL)
            {
                sercom2SPIObj.rxSize = rxSize;
            }
            else
            {
                sercom2SPIObj.rxSize = 0U;
            }

            sercom2SPIObj.transferIsBusy = true;

            /* Flush out any unread data in SPI read buffer */
            while((SERCOM2_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_RXC_Msk) == SERCOM_SPIM_INTFLAG_RXC_Msk)
            {
                dummyData = SERCOM2_REGS->SPIM.SERCOM_DATA;
                (void)dummyData;
            }

            SERCOM2_REGS->SPIM.SERCOM_STATUS |= SERCOM_SPIM_STATUS_BUFOVF_Msk;

            SERCOM2_REGS->SPIM.SERCOM_INTFLAG |= (uint8_t)SERCOM_SPIM_INTFLAG_ERROR_Msk;

            txSz = sercom2SPIObj.txSize;

            if(sercom2SPIObj.rxSize > txSz)
            {
                sercom2SPIObj.dummySize = sercom2SPIObj.rxSize - txSz;
            }

            /* Start the first write here itself, rest will happen in ISR context */
            if((SERCOM2_REGS->SPIM.SERCOM_CTRLB & SERCOM_SPIM_CTRLB_CHSIZE_Msk) == (uint32_t)SPI_DATA_BITS_8)
            {
                if(sercom2SPIObj.txCount < txSz)
                {
                    SERCOM2_REGS->SPIM.SERCOM_DATA = *((uint8_t*)sercom2SPIObj.txBuffer);

                    sercom2SPIObj.txCount++;
                }
                else if(sercom2SPIObj.dummySize > 0U)
                {
                    SERCOM2_REGS->SPIM.SERCOM_DATA = 0xFFU;

                    sercom2SPIObj.dummySize--;
                }
                else
                {
                    /* Do nothing */
                }
            }
            else
            {
                sercom2SPIObj.txSize >>= 1U;
                sercom2SPIObj.dummySize >>= 1U;
                sercom2SPIObj.rxSize >>= 1U;

                txSz = sercom2SPIObj.txSize;

                if(sercom2SPIObj.txCount < txSz)
                {
                    SERCOM2_REGS->SPIM.SERCOM_DATA = *((uint16_t*)sercom2SPIObj.txBuffer) & SERCOM_SPIM_DATA_Msk;

                    sercom2SPIObj.txCount++;
                }
                else if(sercom2SPIObj.dummySize > 0U)
                {
                    SERCOM2_REGS->SPIM.SERCOM_DATA = 0xFFFFU & SERCOM_SPIM_DATA_Msk;

                    sercom2SPIObj.dummySize--;
                }
                else
                {
                    /* Do nothing */
                }
            }

            if(rxSize > 0U)
            {
                /* Enable ReceiveComplete  */
                SERCOM2_REGS->SPIM.SERCOM_INTENSET = (uint8_t)SERCOM_SPIM_INTENSET_RXC_Msk;
            }
            else
            {
                /* Enable the DataRegisterEmpty  */
                SERCOM2_REGS->SPIM.SERCOM_INTENSET = (uint8_t)SERCOM_SPIM_INTENSET_DRE_Msk;
            }
        }
    }

    return isRequestAccepted;
}

bool SERCOM2_SPI_Write(void* pTransmitData, size_t txSize)
{
    return SERCOM2_SPI_WriteRead(pTransmitData, txSize, NULL, 0U);
}

bool SERCOM2_SPI_Read(void* pReceiveData, size_t rxSize)
{
    return SERCOM2_SPI_WriteRead(NULL, 0U, pReceiveData, rxSize);
}

void __attribute__((used)) SERCOM2_SPI_InterruptHandler(void)
{
    uint32_t dataBits = 0U;
    uint32_t receivedData = 0U;
    static bool isLastByteTransferInProgress = false;
    uintptr_t context = sercom2SPIObj.context;

    if(SERCOM2_REGS->SPIM.SERCOM_INTENSET != 0U)
    {
        dataBits = SERCOM2_REGS->SPIM.SERCOM_CTRLB & SERCOM_SPIM_CTRLB_CHSIZE_Msk;

        size_t rxCount = sercom2SPIObj.rxCount;
        size_t txCount = sercom2SPIObj.txCount;
        size_t txSize  = sercom2SPIObj.txSize;

        if((SERCOM2_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_RXC_Msk) == SERCOM_SPIM_INTFLAG_RXC_Msk)
        {
            receivedData =  SERCOM2_REGS->SPIM.SERCOM_DATA;

            if(rxCount < sercom2SPIObj.rxSize)
            {
                if(dataBits == (uint32_t)SPI_DATA_BITS_8)
                {
                    ((uint8_t*)sercom2SPIObj.rxBuffer)[rxCount] = (uint8_t)receivedData;
                    rxCount++;
                }
                else
                {
                    ((uint16_t*)sercom2SPIObj.rxBuffer)[rxCount] = (uint16_t)receivedData;
                    rxCount++;
                }
            }
        }

        /* If there are more words to be transmitted, then transmit them here and keep track of the count */
        if((SERCOM2_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_DRE_Msk) == SERCOM_SPIM_INTFLAG_DRE_Msk)
        {
            /* Disable the DRE interrupt. This will be enabled back if more than
             * one byte is pending to be transmitted */
            SERCOM2_REGS->SPIM.SERCOM_INTENCLR = (uint8_t)SERCOM_SPIM_INTENCLR_DRE_Msk;

            if(dataBits == (uint32_t)SPI_DATA_BITS_8)
            {
                if(txCount < sercom2SPIObj.txSize)
                {
                    SERCOM2_REGS->SPIM.SERCOM_DATA = ((uint8_t*)sercom2SPIObj.txBuffer)[txCount];
                    txCount++;
                }
                else if(sercom2SPIObj.dummySize > 0U)
                {
                    SERCOM2_REGS->SPIM.SERCOM_DATA = 0xFFU;

                    sercom2SPIObj.dummySize--;
                }
                else
                {
                    /* Do nothing */
                }
            }
            else
            {
                if(txCount < sercom2SPIObj.txSize)
                {
                    SERCOM2_REGS->SPIM.SERCOM_DATA = ((uint16_t*)sercom2SPIObj.txBuffer)[txCount];
                    txCount++;
                }
                else if(sercom2SPIObj.dummySize > 0U)
                {
                    SERCOM2_REGS->SPIM.SERCOM_DATA = 0xFFFFU;

                    sercom2SPIObj.dummySize--;
                }
                else
                {
                    /* Do nothing */
                }
            }

            if((sercom2SPIObj.dummySize == 0U) && (txCount == txSize))
            {

                isLastByteTransferInProgress = true;
            }
            else if(rxCount == sercom2SPIObj.rxSize)
            {
                SERCOM2_REGS->SPIM.SERCOM_INTENSET = (uint8_t)SERCOM_SPIM_INTENSET_DRE_Msk;

                SERCOM2_REGS->SPIM.SERCOM_INTENCLR = (uint8_t)SERCOM_SPIM_INTENCLR_RXC_Msk;
            }
            else
            {
                /* Do nothing */
            }
        }

        sercom2SPIObj.rxCount = rxCount;
        sercom2SPIObj.txCount = txCount;

        if(((SERCOM2_REGS->SPIM.SERCOM_INTFLAG & SERCOM_SPIM_INTFLAG_TXC_Msk) == SERCOM_SPIM_INTFLAG_TXC_Msk) && (isLastByteTransferInProgress == true))
        {
            if(rxCount == sercom2SPIObj.rxSize)
            {
                sercom2SPIObj.transferIsBusy = false;

                /* Disable the Data Register empty and Receive Complete Interrupt flags */
                SERCOM2_REGS->SPIM.SERCOM_INTENCLR = (uint8_t)(SERCOM_SPIM_INTENCLR_DRE_Msk | SERCOM_SPIM_INTENCLR_RXC_Msk | SERCOM_SPIM_INTENSET_TXC_Msk);

                isLastByteTransferInProgress = false;

                if(sercom2SPIObj.callback != NULL)
                {
                    sercom2SPIObj.callback(context);
                }
            }
        }

        if(isLastByteTransferInProgress == true)
        {
            SERCOM2_REGS->SPIM.SERCOM_INTENSET = (uint8_t)SERCOM_SPIM_INTENSET_TXC_Msk;
        }
    }
}
