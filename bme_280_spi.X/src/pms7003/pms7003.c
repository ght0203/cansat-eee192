#include "pms7003.h"
#include "sercom1_usart.h"
#include "../dmac/dmac_transmit.h"
#include "../usb_serial/usb_serial.h"

#include <string.h>  // Ensure <string.h> is included for memcpy
#define RX_FRAME_SIZE 32  // Adjust size as needed

static void ReadBytesCycle(DMAC_TRANSFER_EVENT event, uintptr_t contextHandle);
static void PMS_PollData(void);
static uint8_t verifiedRxBuffer[RX_FRAME_SIZE] = {}; // RX buffer for verified bytes
static volatile uint8_t dmaRawBuffer[RX_FRAME_SIZE] = {}; // DMA buffer for unverified bytes
static bool PMSUsart_CheckValidData(uint8_t data[32]);

void PMS_Initialize( void ) {
    SERCOM1_USART_Initialize(9600);
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[17] = 0x1U; // you only need the RX pin
    PORT_SEC_REGS->GROUP[0].PORT_PMUX[8] |= 0x20U;
    
    // Register DMA callback (ReadBytesCycle function executes everytime to read 32 bytes in background)
    DMAC_ChannelCallbackRegister(DMAC_CHANNEL_3, ReadBytesCycle, 0);
    PMS_PollData(); // starts DMA reading in background, independent of program cycle
}


void PMS_RawBytes(void) // print raw bytes for debugging
{
    char msg[256]; // Ensure enough space for all bytes + formatting
    int offset = 0;
    offset += sprintf(msg + offset, "Bytes: ");
    for (int i = 0; i < 32; i++) {
        offset += sprintf(msg + offset, "%02X ", verifiedRxBuffer[i]); // Hex format
    }
    offset += sprintf(msg + offset, "\n"); // Add newline at the end

    USBSerial_Write(msg); // Send formatted string over USB
    USBSerial_Write("\r\n");
}


// Start a DMA receive transfer (polling 32 bytes in background)
static void PMS_PollData(void) {
    if (!DMAC_ChannelIsBusy(DMAC_CHANNEL_3)) {
        DMAC_ChannelTransfer(DMAC_CHANNEL_3, (const void *)&SERCOM1_REGS->USART_INT.SERCOM_DATA, dmaRawBuffer, RX_FRAME_SIZE);
    }
}

static bool PMSUsart_CheckValidData(uint8_t data[32]) {
    uint16_t sum = 0;
    uint16_t checksum = ((uint16_t)data[30] << 8) | data[31];
    for(int i=0; i<30; i++){
      sum += data[i];
    }
    if (sum == checksum)
    {
      return 1;
    }
    return 0;
}

// DMA read cyclic function
static void ReadBytesCycle(DMAC_TRANSFER_EVENT event, uintptr_t contextHandle) {
    // If the start bytes are incorrect, attempt to resynchronize
    if (!(dmaRawBuffer[0] == 0x42 && dmaRawBuffer[1] == 0x4D)) { // based from the datasheet
        // Manually resync by discarding bytes
        // Search for the synchronization pattern (0x42 0x4D)
        int syncIndex = -1;
        for (int i = 0; i < RX_FRAME_SIZE-1; i++) {  // Search until the second last byte
            if (verifiedRxBuffer[i] == 0x42 && verifiedRxBuffer[i + 1] == 0x4D) {
                syncIndex = i;
                break;
            }
        }
        if (syncIndex > 0)
            DMAC_ChannelTransfer(DMAC_CHANNEL_3, (const void *)&SERCOM1_REGS->USART_INT.SERCOM_DATA, dmaRawBuffer, syncIndex);
        else 
            PMS_PollData();
    } else {
        if (PMSUsart_CheckValidData(dmaRawBuffer))
            memcpy(verifiedRxBuffer, dmaRawBuffer, RX_FRAME_SIZE);
        PMS_PollData();
    }
}


uint16_t PMS_GetDataPM2_5(void) {
    return ((uint16_t)verifiedRxBuffer[6] << 8) | verifiedRxBuffer[7];
}

uint16_t PMS_GetDataPM10(void) {
    return ((uint16_t)verifiedRxBuffer[8] << 8) | verifiedRxBuffer[9];
}

uint16_t PMS_GetDataPM1(void) {
    return ((uint16_t)verifiedRxBuffer[4] << 8) | verifiedRxBuffer[5];
}