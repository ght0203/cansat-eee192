# USB Serial Communication Library

## Overview
This library provides functions to facilitate communication over USB using the SERCOM3 USART interface. It includes support for reading and writing data, formatted printing, and reading until a specified character is encountered.

## Initialization
Before using the USB serial functions, the USART module must be initialized:

```c
void USBSerial_Initialize(void);
```
This function initializes the SERCOM3 USART interface and configures the necessary port pins.

## Writing Data

### `USBSerial_Write`
Emulates Arduino's `Serial.print()`, allowing formatted string output over USB. Supports up to 64-byte input and non-blocking transmission.

```c
void USBSerial_Write(const char *formatted_str, ...);
```
- Example:
  ```c
  USBSerial_Write("Temperature: %d C", 25);
  ```

### `USBSerial_WriteNewLine`
Same as `USBSerial_Write`, but appends a newline (`\r\n`) automatically.

```c
void USBSerial_WriteNewLine(const char *formatted_str, ...);
```
- Example:
  ```c
  USBSerial_WriteNewLine("Data received");
  ```

## Reading Data

### `USBSerial_Read`
Reads a specified number of characters from the USB serial buffer. If the buffer contains fewer characters, the function waits for more data.

```c
void USBSerial_Read(char *message, uint8_t length);
```
- Example:
  ```c
  char buffer[10];
  USBSerial_Read(buffer, 9);
  ```
  The buffer will be null-terminated automatically.

### `USBSerial_ReadUntil`
Reads characters until a specified end character is encountered.

```c
void USBSerial_ReadUntil(char *message, char endchar);
```
- Example:
  ```c
  char buffer[64];
  USBSerial_ReadUntil(buffer, '\n');
  ```
  This function reads until a newline character is found and null-terminates the message.

### `USBSerial_ReadNewline`
Reads input from USB until a newline (`\n`) is received.

```c
void USBSerial_ReadNewline(char *message);
```
- Example:
  ```c
  char input[32];
  USBSerial_ReadNewline(input);
  ```
  This function is equivalent to `USBSerial_ReadUntil(message, '\n')`.

## Internal Functionality
The library uses the SERCOM3 USART interface for transmission and reception, with functions such as:

- `SERCOM3_USART_WriteFreeBufferCountGet()` to check for available TX buffer space.
- `SERCOM3_USART_ReadCountGet()` to check for available RX data.
- `SERCOM3_USART_Write()` to send data.
- `SERCOM3_USART_Read()` to receive data.

## Notes
- `USBSerial_Write` is non-blocking, meaning data is transmitted in the background using a ring buffer.
- `USBSerial_Read` is blocking, waiting for the specified number of bytes.
- Strings are automatically null-terminated to ensure correct handling.

This library is ideal for applications requiring reliable USB communication with formatted text output and character-based reading capabilities.

