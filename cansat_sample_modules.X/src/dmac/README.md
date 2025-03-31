# DMA (Direct Memory Access) Controller

This document provides an overview of the DMA functions available in the library. DMA allows for high-speed data transfers between peripherals and memory without involving the CPU for each byte transfer, thus improving performance. It also allows the program to read SERCOM peripheral bytes in background and store them to a buffer without having to actively read the registers.

## Functions

### `void DMAC_Initialize(void);`

**Description:**
Initializes the DMA controller. This function must be called before any DMA operations can be performed. It configures the DMA channels and ensures the DMA hardware is ready to perform data transfers.

**Usage:**

```c
DMAC_Initialize();
```

This function does not require any parameters and does not return any value. It prepares the DMA system for use.

---

### `bool DMAC_ChannelTransfer(DMAC_CHANNEL channel, const void *srcAddr, const void *destAddr, size_t blockSize);`

**Description:**
Initiates a DMA transfer for the specified channel. This function transfers data from the source address to the destination address for the specified number of bytes.

**Parameters:**
- `channel`: The DMA channel to use (e.g., `DMAC_CHANNEL_0`, `DMAC_CHANNEL_1`).
- `srcAddr`: The source memory address from where data will be read.
- `destAddr`: The destination memory address to which data will be written.
- `blockSize`: The number of bytes to transfer.

**Return Value:**
- `true`: If the transfer is successfully initiated.
- `false`: If the transfer could not be initiated (e.g., if the channel is already busy).

**Usage Example:**

```c
uint8_t srcData[256];
uint8_t destData[256];

// Initialize source and destination buffers
for (int i = 0; i < 256; i++) {
    srcData[i] = i;  // Filling source buffer with data
}

bool success = DMAC_ChannelTransfer(DMAC_CHANNEL_0, srcData, destData, sizeof(srcData));

if (success) {
    // Transfer initiated successfully
} else {
    // Transfer failed
}
```

---

### `bool DMAC_ChannelIsBusy(DMAC_CHANNEL channel);`

**Description:**
Checks if the specified DMA channel is currently busy processing a transfer. This function is useful for determining if a channel is available for a new transfer or if the current transfer is still in progress.

**Parameters:**
- `channel`: The DMA channel to check (e.g., `DMAC_CHANNEL_0`, `DMAC_CHANNEL_1`).

**Return Value:**
- `true`: If the DMA channel is busy and currently processing a transfer.
- `false`: If the DMA channel is idle and available.

**Usage Example:**

```c
if (DMAC_ChannelIsBusy(DMAC_CHANNEL_0)) {
    // DMA channel is currently busy
} else {
    // DMA channel is free
}
```

---

### `void DMAC_ChannelCallbackRegister(DMAC_CHANNEL channel, const DMAC_CHANNEL_CALLBACK eventHandler, const uintptr_t contextHandle);`

**Description:**
Registers a callback function for a specific DMA channel. The callback function will be called when a DMA transfer on the channel completes or encounters an error. The `eventHandler` function is used to handle the completion or error event.

**Parameters:**
- `channel`: The DMA channel to register the callback for (e.g., `DMAC_CHANNEL_0`, `DMAC_CHANNEL_1`).
- `eventHandler`: A pointer to the callback function that will handle the transfer event.
- `contextHandle`: A pointer to any additional context that needs to be passed to the callback function (e.g., a pointer to a structure or a value).

**Usage Example:**

```c
// Callback function definition
void MyDMAC_Callback(DMAC_TRANSFER_EVENT event, uintptr_t context) {
    if (event == DMAC_TRANSFER_EVENT_COMPLETE) {
        // Transfer complete
    } else if (event == DMAC_TRANSFER_EVENT_ERROR) {
        // Transfer error occurred
    }
}

// Register the callback for a DMA channel
DMAC_ChannelCallbackRegister(DMAC_CHANNEL_0, MyDMAC_Callback, 0);

// Trigger a DMA transfer
DMAC_ChannelTransfer(DMAC_CHANNEL_0, srcData, destData, sizeof(srcData));
```

---

## Example Code

Here is a complete example demonstrating how to use the DMA functions together:

```c
#include "dma.h"

#define DMA_CHANNEL_TRANSMIT DMAC_CHANNEL_1
#define DMA_CHANNEL_RECEIVE DMAC_CHANNEL_0

uint8_t txData[256];
uint8_t rxData[256];

// Callback function for the transmit channel
void DMAC_TxCallback(DMAC_TRANSFER_EVENT event, uintptr_t context) {
    if (event == DMAC_TRANSFER_EVENT_COMPLETE) {
        // Handle successful transfer completion
    } else if (event == DMAC_TRANSFER_EVENT_ERROR) {
        // Handle transfer error
    }
}

// Callback function for the receive channel
void DMAC_RxCallback(DMAC_TRANSFER_EVENT event, uintptr_t context) {
    if (event == DMAC_TRANSFER_EVENT_COMPLETE) {
        // Handle successful transfer completion
    } else if (event == DMAC_TRANSFER_EVENT_ERROR) {
        // Handle transfer error
    }
}

int main(void) {
    // Initialize DMA
    DMAC_Initialize();

    // Register callback functions
    DMAC_ChannelCallbackRegister(DMA_CHANNEL_TRANSMIT, DMAC_TxCallback, 0);
    DMAC_ChannelCallbackRegister(DMA_CHANNEL_RECEIVE, DMAC_RxCallback, 0);

    // Prepare data for transmission
    for (int i = 0; i < sizeof(txData); i++) {
        txData[i] = i;  // Fill the transmit buffer with data
    }

    // Start DMA transfer
    DMAC_ChannelTransfer(DMA_CHANNEL_TRANSMIT, txData, (void *)&SERCOM3_REGS->SPIM.SERCOM_DATA, sizeof(txData));
    DMAC_ChannelTransfer(DMA_CHANNEL_RECEIVE, (void *)&SERCOM3_REGS->SPIM.SERCOM_DATA, rxData, sizeof(rxData));

    // Main loop
    while (true) {
        // Application code
    }

    return 0;
}
```

## Notes:
- Ensure the DMA channels are properly configured before starting transfers. This includes setting up descriptors, buffers, and peripheral addresses.
- The callback functions should handle both the transfer success and error events to ensure proper operation.
- The `DMAC_Initialize` function should be called once at the start of your application to prepare the DMA system.

---