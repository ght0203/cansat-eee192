

#ifndef SERCOM2_SPI_H
#define	SERCOM2_SPI_H
#include <xc.h>
#include <stdbool.h>
#include <string.h>
#ifdef	__cplusplus
extern "C" {
#endif

typedef void (*SERCOM_SPI_CALLBACK)(uintptr_t context);

typedef enum
{
        SPI_DATA_BITS_8 = SERCOM_SPIM_CTRLB_CHSIZE_8_BIT,
    SPI_DATA_BITS_9 = SERCOM_SPIM_CTRLB_CHSIZE_9_BIT,


    /* Force the compiler to reserve 32-bit space for each enum value */
    SPI_DATA_BITS_INVALID = 0xFFFFFFFFU

} SPI_DATA_BITS;

void SERCOM2_SPI_Initialize();

typedef enum
{
         SPI_CLOCK_POLARITY_IDLE_LOW = SERCOM_SPIM_CTRLA_CPOL_IDLE_LOW,
    SPI_CLOCK_POLARITY_IDLE_HIGH = SERCOM_SPIM_CTRLA_CPOL_IDLE_HIGH,


    /* Force the compiler to reserve 32-bit space for each enum value */
    SPI_CLOCK_POLARITY_INVALID = 0xFFFFFFFFU

} SPI_CLOCK_POLARITY;

typedef enum
{
        SPI_CLOCK_PHASE_LEADING_EDGE = SERCOM_SPIM_CTRLA_CPHA_LEADING_EDGE,
    SPI_CLOCK_PHASE_TRAILING_EDGE = SERCOM_SPIM_CTRLA_CPHA_TRAILING_EDGE,


    /* Force the compiler to reserve 32-bit space for each enum value */
    SPI_CLOCK_PHASE_INVALID = 0xFFFFFFFFU

} SPI_CLOCK_PHASE;

typedef struct
{
    /* Baud Rate or clock frequency */
    uint32_t            clockFrequency;

    /* Clock Phase */
    SPI_CLOCK_PHASE     clockPhase;

    /* Clock Polarity */
    SPI_CLOCK_POLARITY  clockPolarity;

    /* Number of bits per transfer */
    SPI_DATA_BITS       dataBits;

} SPI_TRANSFER_SETUP;

typedef struct
{
    /* Pointer to the transmitter buffer */
    void *                   txBuffer;

    /* Pointer to the received buffer */
    void *                   rxBuffer;

    size_t                   txSize;

    size_t                   rxSize;

    size_t                   dummySize;

    /* Size of the receive processed exchange size */
    size_t                   rxCount;

    /* Size of the transmit processed exchange size */
    size_t                   txCount;

    /* Exchange busy status of the SPI */
    bool                     transferIsBusy;

    /* SPI Event handler */
    SERCOM_SPI_CALLBACK      callback;

    /* Context */
    uintptr_t                context;

    uint32_t                 status;

} SPI_OBJECT;

void SERCOM2_SPI_Initialize();
bool SERCOM2_SPI_Read(void* pReceiveData, size_t rxSize);
bool SERCOM2_SPI_Write(void* pTransmitData, size_t txSize);
bool SERCOM2_SPI_IsBusy(void);
void __attribute__((used)) SERCOM2_SPI_InterruptHandler(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SERCOM2_SPI_H */

