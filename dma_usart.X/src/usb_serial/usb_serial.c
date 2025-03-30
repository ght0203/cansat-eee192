#include "usb_serial.h"
#include "sercom3_usart.h"
#include "dmac.h"

#define MESSAGE_QUEUE_SIZE 128  // Adjust size as needed
#define RX_BUFFER_SIZE 64  // Adjust size as needed

// Ignore these /////////////////////////////
static void TransmitCompleteCallback(DMAC_TRANSFER_EVENT event, uintptr_t contextHandle);
static void ReceiveCompleteCallback(DMAC_TRANSFER_EVENT event, uintptr_t contextHandle);
static void SerialRXPoll(void);
static char queuedMessage[MESSAGE_QUEUE_SIZE] = {};
static volatile bool isMessageQueued = false;
static char rxRingBuffer[RX_BUFFER_SIZE] = {}; // Ring buffer for received data
static volatile uint8_t rxHead = 0;
static volatile uint8_t rxTail = 0;
static volatile uint8_t rxCount = 0;
static volatile char dmaRxBuffer; // DMA buffer for polling 1 byte at a time
static volatile bool rxComplete = false;
// End Ignore  /////////////////////////////

void USBSerial_Initialize( void ) {
    SERCOM3_USART_Initialize();
    DMAC_Initialize();
    
    // Register DMA callbacks
    DMAC_ChannelCallbackRegister(DMAC_CHANNEL_0, TransmitCompleteCallback, 0);
    DMAC_ChannelCallbackRegister(DMAC_CHANNEL_1, ReceiveCompleteCallback, 0);
    SerialRXPoll();
}

void USBSerial_Write(char* message) {
    if (DMAC_ChannelIsBusy(DMAC_CHANNEL_0) == true) {
        // DMA is busy, append message in queue
        strncat(queuedMessage, message, MESSAGE_QUEUE_SIZE - strlen(queuedMessage) - 1);
        queuedMessage[MESSAGE_QUEUE_SIZE - 1] = '\0';  // Ensure null termination
        isMessageQueued = true;
    } else {
        // DMA is free, send directly
        DMAC_ChannelTransfer(DMAC_CHANNEL_0, message, (const void *)&SERCOM3_REGS->USART_INT.SERCOM_DATA, strlen(message)); 
    }
}

// Start a DMA receive transfer (polling 1 byte at a time)
static void SerialRXPoll(void) {
    if (!DMAC_ChannelIsBusy(DMAC_CHANNEL_1)) {
        rxComplete = false;
        DMAC_ChannelTransfer(DMAC_CHANNEL_1, (const void *)&SERCOM3_REGS->USART_INT.SERCOM_DATA, (void*)&dmaRxBuffer, 1);
    }
}

// Read a specified number of bytes from the ring buffer (blocking)
uint8_t USBSerial_Read(char* outputBuffer, uint8_t length) {
    uint8_t bytesRead = 0;

    // Block until enough data is available
    while (rxCount < length);  // Busy wait

    // Read from ring buffer once enough data is available
    while (bytesRead < length) {
        outputBuffer[bytesRead] = rxRingBuffer[rxTail];
        rxTail = (rxTail + 1) % RX_BUFFER_SIZE;
        rxCount--;
        bytesRead++;
    }
    outputBuffer[bytesRead] = '\0';  

    return bytesRead;  // Return the number of bytes actually read
}

// DMA receive callback (stores received byte into ring buffer)
static void ReceiveCompleteCallback(DMAC_TRANSFER_EVENT event, uintptr_t contextHandle) {
    if (rxCount < RX_BUFFER_SIZE) {  
        rxRingBuffer[rxHead] = dmaRxBuffer;  // Use the DMA-received byte
        rxHead = (rxHead + 1) % RX_BUFFER_SIZE;
        rxCount++;
    } else {
        // Buffer is full, so overwrite the oldest byte
        rxTail = (rxTail + 1) % RX_BUFFER_SIZE;  // Move tail forward (drop oldest byte)
        rxRingBuffer[rxHead] = dmaRxBuffer;      // Store new data at head position
        rxHead = (rxHead + 1) % RX_BUFFER_SIZE;  // Move head forward
    }
    SerialRXPoll();
}

static void TransmitCompleteCallback(DMAC_TRANSFER_EVENT event, uintptr_t contextHandle) {
    if (isMessageQueued) {
        // Send the queued message
        isMessageQueued = false;
        queuedMessage[0] = '\0'; 
        DMAC_ChannelTransfer(DMAC_CHANNEL_0, queuedMessage, (const void *)&SERCOM3_REGS->USART_INT.SERCOM_DATA, strlen(queuedMessage));
    }
}