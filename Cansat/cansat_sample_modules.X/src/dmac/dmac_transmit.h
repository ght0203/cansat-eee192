#ifndef DMAC_TX_H    // Guards against multiple inclusion
#define DMAC_TX_H

#include <xc.h>
#include <string.h>
#include <stdbool.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

typedef enum
{
    DMAC_CHANNEL_0 = 0, // sercom 3
    DMAC_CHANNEL_1 = 1, // sercom 3
    DMAC_CHANNEL_2 = 2, // sercom 0
    DMAC_CHANNEL_3 = 3, // sercom 1
    DMAC_CHANNEL_4 = 4, // sercom 5 tx
    DMAC_CHANNEL_5 = 5, // sercom 5 rx
} DMAC_CHANNEL;

typedef enum
{
    /* No event */
    DMAC_TRANSFER_EVENT_NONE = 0,

    /* Data was transferred successfully. */
    DMAC_TRANSFER_EVENT_COMPLETE = 1,

    /* Error while processing the request */
    DMAC_TRANSFER_EVENT_ERROR = 2

} DMAC_TRANSFER_EVENT;

typedef uint32_t DMAC_CHANNEL_CONFIG;

typedef void (*DMAC_CHANNEL_CALLBACK) (DMAC_TRANSFER_EVENT event, uintptr_t contextHandle);
void DMAC_ChannelCallbackRegister (DMAC_CHANNEL channel, const DMAC_CHANNEL_CALLBACK eventHandler, const uintptr_t contextHandle);
void DMAC_Initialize( void );
bool DMAC_ChannelTransfer (DMAC_CHANNEL channel, const void *srcAddr, const void *destAddr, size_t blockSize);
bool DMAC_ChannelIsBusy ( DMAC_CHANNEL channel );
void DMAC_ChannelCallbackRegister( DMAC_CHANNEL channel, const DMAC_CHANNEL_CALLBACK eventHandler, const uintptr_t contextHandle );
uint16_t DMAC_ChannelGetTransferredCount( DMAC_CHANNEL channel );

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END

#endif //DMAC_TX_H
