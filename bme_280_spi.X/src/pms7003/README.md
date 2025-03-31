# USB Serial DMA Library

## Overview
This library provides an interface for USB serial communication using Direct Memory Access (DMA) on Microchip microcontrollers. It includes functions for transmitting and receiving data efficiently. 

DMA allows for faster data transfers by bypassing the CPU, enabling direct communication between memory and peripherals. This reduces the CPU load, freeing it up to perform other tasks, which improves overall system performance. Additionally, DMA can optimize power consumption by minimizing the time the CPU spends on data handling. This also allows the program to read USART bytes in background (stored in a buffer) even when the user is not actively reading the registers.

## Functions

### USBSerial_Write
```c
void USBSerial_Write(const char* message);
```
Writes a message to the USB serial interface. If the DMA is busy, the message is queued for later transmission.

**Parameters:**
- `message` – The null-terminated string to be sent over USB serial.

**Example Usage:**
```c
USBSerial_Write("Hello, world!\n");
```

---

### USBSerial_Read
```c
uint8_t USBSerial_Read(char* outputBuffer, uint8_t maxLength);
```
Reads data from the USB serial interface into `outputBuffer`, up to `maxLength - 1` bytes. The result is null-terminated.

**Parameters:**
- `outputBuffer` – The buffer where received data will be stored.
- `maxLength` – The maximum number of bytes to read.

**Returns:**
- The number of bytes actually read.

**Example Usage:**
```c
char buffer[64];
uint8_t bytesRead = USBSerial_Read(buffer, sizeof(buffer));
```

---

### USBSerial_ReadLine
```c
void USBSerial_ReadLine(char* outputBuffer);
```
Reads a single line (terminated by `\n`) from the USB serial interface, up to a maximum of 64 bytes.

**Parameters:**
- `outputBuffer` – The buffer where the received line will be stored.

**Example Usage:**
```c
char lineBuffer[64];
USBSerial_ReadLine(lineBuffer);
```

---

## DMAC Interface Functions

### DMAC_Initialize
```c
void DMAC_Initialize(void);
```
Initializes the DMA controller.

**Example Usage:**
```c
DMAC_Initialize();
```

---

### DMAC_ChannelTransfer
```c
bool DMAC_ChannelTransfer(DMAC_CHANNEL channel, const void *srcAddr, const void *destAddr, size_t blockSize);
```
Initiates a DMA transfer.

**Parameters:**
- `channel` – The DMA channel to use.
- `srcAddr` – Pointer to the source data.
- `destAddr` – Pointer to the destination.
- `blockSize` – Size of the data to transfer.

**Returns:**
- `true` if the transfer was successfully started.

**Example Usage:**
```c
DMAC_ChannelTransfer(DMAC_CHANNEL_0, dataBuffer, (void *)&SERCOM3_REGS->USART_INT.SERCOM_DATA, length);
```

---

### DMAC_ChannelIsBusy
```c
bool DMAC_ChannelIsBusy(DMAC_CHANNEL channel);
```
Checks if a DMA channel is currently busy.

**Parameters:**
- `channel` – The DMA channel to check.

**Returns:**
- `true` if the channel is busy.

**Example Usage:**
```c
if (!DMAC_ChannelIsBusy(DMAC_CHANNEL_0)) {
    USBSerial_Write("DMA is free\n");
}
```

---

### DMAC_ChannelCallbackRegister
```c
void DMAC_ChannelCallbackRegister(DMAC_CHANNEL channel, const DMAC_CHANNEL_CALLBACK eventHandler, const uintptr_t contextHandle);
```
Registers a callback function for DMA transfer events.

**Parameters:**
- `channel` – The DMA channel.
- `eventHandler` – The callback function to be executed on DMA transfer events.
- `contextHandle` – User-defined context.

**Example Usage:**
```c
void MyDMAC_Callback(DMAC_TRANSFER_EVENT event, uintptr_t context) {
    if (event == DMAC_TRANSFER_EVENT_COMPLETE) {
        USBSerial_Write("DMA Transfer Complete\n");
    }
}

DMAC_ChannelCallbackRegister(DMAC_CHANNEL_0, MyDMAC_Callback, 0);
```

## License
This library is provided "as is" under the Microchip Technology Inc. license agreement. See the original source file for details.

