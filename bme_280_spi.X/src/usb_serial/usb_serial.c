#include "usb_serial.h"
#include "sercom3_usart.h"
#include "../dmac/dmac_transmit.h"

#define MESSAGE_QUEUE_SIZE 256  // Adjust size as needed
#define RX_BUFFER_SIZE 65  // Adjust size as needed

// Ignore these /////////////////////////////
static void ReceiveCompleteCallback(DMAC_TRANSFER_EVENT event, uintptr_t contextHandle);
static void SerialRXPoll(void);
static char rxRingBuffer[RX_BUFFER_SIZE] = {}; // Ring buffer for received data
static volatile uint8_t rxHead = 0;
static volatile uint8_t rxTail = 0;
static volatile uint8_t rxCount = 0; // This is the number of bytes recieved so far in background
static volatile char dmaRxBuffer; // DMA buffer for polling 1 byte at a time
// End Ignore  /////////////////////////////

void USBSerial_Initialize( uint32_t baud_rate ) {
    SERCOM3_USART_Initialize(baud_rate);
    PORT_SEC_REGS->GROUP[1].PORT_PINCFG[8] = 0x1U;
    PORT_SEC_REGS->GROUP[1].PORT_PINCFG[9] = 0x1U;
    PORT_SEC_REGS->GROUP[1].PORT_PMUX[4] = 0x33U;
    
    SerialRXPoll(); // starts DMA reading in background, independent of program cycle
    
    // Register DMA callback (ReceiveCompleteCallback function executes evertime a byte is read in background)
    DMAC_ChannelCallbackRegister(DMAC_CHANNEL_1, ReceiveCompleteCallback, 0);
}

// Sends a message over USB serial.  
void USBSerial_Write(const char* message) {
    if (message == NULL || *message == '\0') {
        return;  // Don't send anything if the message is empty
    }

    size_t messageLength = strlen(message);
    
    // Start the DMA transfer for the message
    DMAC_ChannelTransfer(DMAC_CHANNEL_0, message, (const void *)&SERCOM3_REGS->USART_INT.SERCOM_DATA, messageLength);
    while(DMAC_ChannelGetTransferredCount(DMAC_CHANNEL_0) < messageLength);
}



// Reads up to maxLength bytes from the input buffer into outputBuffer.
// The function stops when either the unread buffer is empty or maxLength bytes have been read.
// If space allows, it ensures outputBuffer is null-terminated.
uint8_t USBSerial_Read(char* outputBuffer, uint8_t maxLength)
{
    uint8_t bytesRead = 0;

    while (rxCount && bytesRead < maxLength - 1) {  
        outputBuffer[bytesRead] = rxRingBuffer[rxTail];
        rxTail = (rxTail + 1) % RX_BUFFER_SIZE;
        rxCount--;
        bytesRead++;
    }
    outputBuffer[bytesRead] = '\0';  

    return bytesRead;
}

void USBSerial_ReadLine(char* outputBuffer) {
    uint8_t bytesRead = 0;
    while (rxCount && bytesRead < RX_BUFFER_SIZE - 1) {
        char c = rxRingBuffer[rxTail];
        rxTail = (rxTail + 1) % RX_BUFFER_SIZE;
        rxCount--;
        
        if (c == '\n') {
            break;
        }
        
        outputBuffer[bytesRead++] = c;
    }
    outputBuffer[bytesRead] = '\0';
}

// Similar to Serial.available() in Arduino
uint8_t USBSerial_BytesAvailable(void) {
    return rxCount;
}

/* --------------------- IGNORE EVERYTHING BELOW ---------------------------------------*/
// Start a DMA receive transfer (polling 1 byte at a time in background)
static void SerialRXPoll(void) {
    if (!DMAC_ChannelIsBusy(DMAC_CHANNEL_1)) {
        DMAC_ChannelTransfer(DMAC_CHANNEL_1, (const void *)&SERCOM3_REGS->USART_INT.SERCOM_DATA, (void*)&dmaRxBuffer, 1);
    }
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


