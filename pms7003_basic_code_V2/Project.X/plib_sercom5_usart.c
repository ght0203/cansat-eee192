#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <xc.h>
#include "plib_sercom5_usart.h"

static volatile SERCOM_USART_OBJECT sercom5USARTObj;
#define USART_ERROR_NONE 0U

bool SERCOM5_USART_Write( void *buffer, const size_t size )
{
    bool writeStatus      = false;
    uint32_t processedSize = 0U;

    if(buffer != NULL)
    {
        if(sercom5USARTObj.txBusyStatus == false)
        {
            sercom5USARTObj.txBuffer = buffer;
            sercom5USARTObj.txSize = size;
            sercom5USARTObj.txBusyStatus = true;

            size_t txSize = sercom5USARTObj.txSize;

            /* Initiate the transfer by sending first byte */
            while (((SERCOM5_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk) == SERCOM_USART_INT_INTFLAG_DRE_Msk) &&
                    (processedSize < txSize))
            {
                if (((SERCOM5_REGS->USART_INT.SERCOM_CTRLB & SERCOM_USART_INT_CTRLB_CHSIZE_Msk) >> SERCOM_USART_INT_CTRLB_CHSIZE_Pos) != 0x01U)
                {
                    /* 8-bit mode */
                    SERCOM5_REGS->USART_INT.SERCOM_DATA = ((uint8_t*)(buffer))[processedSize];
                }
                else
                {
                    /* 9-bit mode */
                    SERCOM5_REGS->USART_INT.SERCOM_DATA = ((uint16_t*)(buffer))[processedSize];
                }
                processedSize += 1U;
            }
            sercom5USARTObj.txProcessedSize = processedSize;
            SERCOM5_REGS->USART_INT.SERCOM_INTENSET = (uint8_t)SERCOM_USART_INT_INTFLAG_DRE_Msk;

            writeStatus = true;
        }
    }

    return writeStatus;
}

bool SERCOM5_USART_Read( void *buffer, const size_t size )
{
    bool readStatus         = false;

    if(buffer != NULL)
    {
        if(sercom5USARTObj.rxBusyStatus == false)
        {
            /* Clear error flags and flush out error data that may have been received when no active request was pending */
            SERCOM5_USART_ErrorClear();

            sercom5USARTObj.rxBuffer = buffer;
            sercom5USARTObj.rxSize = size;
            sercom5USARTObj.rxProcessedSize = 0U;
            sercom5USARTObj.rxBusyStatus = true;
            sercom5USARTObj.errorStatus = USART_ERROR_NONE;

            readStatus = true;

            /* Enable receive and error interrupt */
            SERCOM5_REGS->USART_INT.SERCOM_INTENSET = (uint8_t)(SERCOM_USART_INT_INTENSET_ERROR_Msk | SERCOM_USART_INT_INTENSET_RXC_Msk);
        }
    }

    return readStatus;
}

static void SERCOM5_USART_ErrorClear( void )
{
    uint8_t  u8dummyData = 0U;
    USART_ERROR errorStatus = (USART_ERROR) (SERCOM5_REGS->USART_INT.SERCOM_STATUS & (uint16_t)(SERCOM_USART_INT_STATUS_PERR_Msk | SERCOM_USART_INT_STATUS_FERR_Msk | SERCOM_USART_INT_STATUS_BUFOVF_Msk ));

    if(errorStatus != USART_ERROR_NONE)
    {
        /* Clear error flag */
        SERCOM5_REGS->USART_INT.SERCOM_INTFLAG = (uint8_t)SERCOM_USART_INT_INTFLAG_ERROR_Msk;
        /* Clear all errors */
        SERCOM5_REGS->USART_INT.SERCOM_STATUS = (uint16_t)(SERCOM_USART_INT_STATUS_PERR_Msk | SERCOM_USART_INT_STATUS_FERR_Msk | SERCOM_USART_INT_STATUS_BUFOVF_Msk);

        /* Flush existing error bytes from the RX FIFO */
        while((SERCOM5_REGS->USART_INT.SERCOM_INTFLAG & (uint8_t)SERCOM_USART_INT_INTFLAG_RXC_Msk) == (uint8_t)SERCOM_USART_INT_INTFLAG_RXC_Msk)
        {
            u8dummyData = (uint8_t)SERCOM5_REGS->USART_INT.SERCOM_DATA;
        }
    }

    /* Ignore the warning */
    (void)u8dummyData;
}


bool SERCOM5_USART_ReadIsBusy( void )
{
    return sercom5USARTObj.rxBusyStatus;
}

size_t SERCOM5_USART_ReadCountGet( void )
{
    return sercom5USARTObj.rxProcessedSize;
}

void __attribute__((used)) SERCOM5_USART_InterruptHandler( void )
{
    bool testCondition;
    if(SERCOM5_REGS->USART_INT.SERCOM_INTENSET != 0U)
    {
        /* Checks for error flag */
        testCondition = ((SERCOM5_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_ERROR_Msk) == SERCOM_USART_INT_INTFLAG_ERROR_Msk);
        testCondition = ((SERCOM5_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_ERROR_Msk) == SERCOM_USART_INT_INTENSET_ERROR_Msk) && testCondition;
        if(testCondition)
        {
            SERCOM5_USART_ISR_ERR_Handler();
        }

        testCondition = ((SERCOM5_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk) == SERCOM_USART_INT_INTFLAG_DRE_Msk);
        testCondition = ((SERCOM5_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_DRE_Msk) == SERCOM_USART_INT_INTENSET_DRE_Msk) && testCondition;
        /* Checks for data register empty flag */
        if(testCondition)
        {
            SERCOM5_USART_ISR_TX_Handler();
        }

        testCondition = ((SERCOM5_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_RXC_Msk) == SERCOM_USART_INT_INTFLAG_RXC_Msk);
        testCondition = ((SERCOM5_REGS->USART_INT.SERCOM_INTENSET & SERCOM_USART_INT_INTENSET_RXC_Msk) == SERCOM_USART_INT_INTENSET_RXC_Msk) && testCondition;
        /* Checks for receive complete empty flag */
        if(testCondition)
        {
            SERCOM5_USART_ISR_RX_Handler();
        }
    }
}

static void __attribute__((used)) SERCOM5_USART_ISR_ERR_Handler( void )
{
    USART_ERROR errorStatus;

    errorStatus = (USART_ERROR) (SERCOM5_REGS->USART_INT.SERCOM_STATUS & (uint16_t)(SERCOM_USART_INT_STATUS_PERR_Msk | SERCOM_USART_INT_STATUS_FERR_Msk | SERCOM_USART_INT_STATUS_BUFOVF_Msk));

    if(errorStatus != USART_ERROR_NONE)
    {
        /* Save the error to be reported later */
        sercom5USARTObj.errorStatus = errorStatus;

        /* Clear the error flags and flush out the error bytes */
        SERCOM5_USART_ErrorClear();

        /* Disable error and receive interrupt to abort on-going transfer */
        SERCOM5_REGS->USART_INT.SERCOM_INTENCLR = (uint8_t)(SERCOM_USART_INT_INTENCLR_ERROR_Msk | SERCOM_USART_INT_INTENCLR_RXC_Msk);

        /* Clear the RX busy flag */
        sercom5USARTObj.rxBusyStatus = false;

        if(sercom5USARTObj.rxCallback != NULL)
        {
            uintptr_t rxContext = sercom5USARTObj.rxContext;

            sercom5USARTObj.rxCallback(rxContext);
        }
    }
}


static void __attribute__((used)) SERCOM5_USART_ISR_TX_Handler( void )
{
    bool  dataRegisterEmpty;
    bool  dataAvailable;
    if(sercom5USARTObj.txBusyStatus == true)
    {
        size_t txProcessedSize = sercom5USARTObj.txProcessedSize;

        dataAvailable = (txProcessedSize < sercom5USARTObj.txSize);
        dataRegisterEmpty = ((SERCOM5_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk) == SERCOM_USART_INT_INTFLAG_DRE_Msk);

        while(dataRegisterEmpty && dataAvailable)
        {
            if (((SERCOM5_REGS->USART_INT.SERCOM_CTRLB & SERCOM_USART_INT_CTRLB_CHSIZE_Msk) >> SERCOM_USART_INT_CTRLB_CHSIZE_Pos) != 0x01U)
            {
                /* 8-bit mode */
                SERCOM5_REGS->USART_INT.SERCOM_DATA = ((uint8_t*)sercom5USARTObj.txBuffer)[txProcessedSize];
            }
            else
            {
                /* 9-bit mode */
                SERCOM5_REGS->USART_INT.SERCOM_DATA = ((uint16_t*)sercom5USARTObj.txBuffer)[txProcessedSize];
            }
            /* Increment processed size */
            txProcessedSize++;

            dataAvailable = (txProcessedSize < sercom5USARTObj.txSize);
            dataRegisterEmpty = ((SERCOM5_REGS->USART_INT.SERCOM_INTFLAG & SERCOM_USART_INT_INTFLAG_DRE_Msk) == SERCOM_USART_INT_INTFLAG_DRE_Msk);
        }

        sercom5USARTObj.txProcessedSize = txProcessedSize;

        if(txProcessedSize >= sercom5USARTObj.txSize)
        {
            sercom5USARTObj.txBusyStatus = false;
            sercom5USARTObj.txSize = 0U;
            SERCOM5_REGS->USART_INT.SERCOM_INTENCLR = (uint8_t)SERCOM_USART_INT_INTENCLR_DRE_Msk;

            if(sercom5USARTObj.txCallback != NULL)
            {
                uintptr_t txContext = sercom5USARTObj.txContext;
                sercom5USARTObj.txCallback(txContext);
            }
        }
    }
}

static void __attribute__((used)) SERCOM5_USART_ISR_RX_Handler( void )
{
    uint16_t temp;


    if(sercom5USARTObj.rxBusyStatus == true)
    {
        size_t rxSize = sercom5USARTObj.rxSize;

        if(sercom5USARTObj.rxProcessedSize < rxSize)
        {
            uintptr_t rxContext = sercom5USARTObj.rxContext;

            temp = (uint16_t)SERCOM5_REGS->USART_INT.SERCOM_DATA;
            size_t rxProcessedSize = sercom5USARTObj.rxProcessedSize;

            if (((SERCOM5_REGS->USART_INT.SERCOM_CTRLB & SERCOM_USART_INT_CTRLB_CHSIZE_Msk) >> SERCOM_USART_INT_CTRLB_CHSIZE_Pos) != 0x01U)
            {
                /* 8-bit mode */
                ((uint8_t*)sercom5USARTObj.rxBuffer)[rxProcessedSize] = (uint8_t) (temp);
            }
            else
            {
                /* 9-bit mode */
                ((uint16_t*)sercom5USARTObj.rxBuffer)[rxProcessedSize] = temp;
            }

            /* Increment processed size */
            rxProcessedSize++;
            sercom5USARTObj.rxProcessedSize = rxProcessedSize;

            if(rxProcessedSize == sercom5USARTObj.rxSize)
            {
                sercom5USARTObj.rxBusyStatus = false;
                sercom5USARTObj.rxSize = 0U;
                SERCOM5_REGS->USART_INT.SERCOM_INTENCLR = (uint8_t)(SERCOM_USART_INT_INTENCLR_RXC_Msk | SERCOM_USART_INT_INTENCLR_ERROR_Msk);

                if(sercom5USARTObj.rxCallback != NULL)
                {
                    sercom5USARTObj.rxCallback(rxContext);
                }
            }

        }
    }
}
