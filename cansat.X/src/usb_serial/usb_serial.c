#include "sercom3_usart.h"
#include "usb_serial.h"

void USBSerial_Initialize(void) {
    SERCOM3_USART_Initialize();
    PORT_SEC_REGS->GROUP[1].PORT_PINCFG[8] = 0x1U;
    PORT_SEC_REGS->GROUP[1].PORT_PINCFG[9] = 0x1U;
    PORT_SEC_REGS->GROUP[1].PORT_PMUX[4] = 0x33U;
}

// USBSerial_Write: This emulates Arduino's Serial.print(), maximum input = 64 bytes
// This also supports sprintf formatting e.g. USBSerial_Write("Number: %d", num)
// This is a non blocking function (allows the interrupts to transmit bytes in background via ring buffer)
void USBSerial_Write(const char *formatted_str, ...)
{
    va_list args;
    char buffer[64]; // Statically allocate a 64-byte buffer

    // First, determine the required buffer size (excluding null terminator)
    va_start(args, formatted_str);
    int length = vsnprintf(NULL, 0, formatted_str, args);
    va_end(args);

    if (length <= 0 || length >= sizeof(buffer)) return; // Error in formatting or buffer too small

    // Format the string into the buffer
    va_start(args, formatted_str);
    vsnprintf(buffer, sizeof(buffer), formatted_str, args);
    va_end(args);

    while(SERCOM3_USART_WriteFreeBufferCountGet() < length); // wait for free space in the TX register
    // Transmit the formatted string
    SERCOM3_USART_Write((void *)buffer, length);
}

// Does the same thing as USBSerial_Write but appends newline
void USBSerial_WriteNewLine(const char *formatted_str, ...)
{
    va_list args;
    char buffer[62]; // Reserve space for \r\n and null terminator
    char final_buffer[64]; // Final buffer including newline

    // Determine the formatted string length
    va_start(args, formatted_str);
    int length = vsnprintf(NULL, 0, formatted_str, args);
    va_end(args);

    if (length <= 0 || length >= sizeof(buffer)) return; // Error in formatting or buffer too small

    // Format the string into buffer
    va_start(args, formatted_str);
    vsnprintf(buffer, sizeof(buffer), formatted_str, args);
    va_end(args);

    // Append newline (\r\n)
    snprintf(final_buffer, sizeof(final_buffer), "%s\r\n", buffer);

    while (SERCOM3_USART_WriteFreeBufferCountGet() < length + 2); // Wait for free space

    // Transmit the formatted string with newline
    SERCOM3_USART_Write((void *)final_buffer, length + 2);
}


/* USBSerial_Read
 * Read characters from the USART until the specified message length is reached (virtually unlimited length).
 * If the buffer is not yet full (i.e., fewer characters have been received than the specified length),
 * the function will wait for additional data to arrive before continuing (a blocking function)
 */
void USBSerial_Read(char *message, uint8_t length)
{
    // Ensure the buffer is valid
    if (message == NULL || length == 0) {
        return;
    }
    
    while (SERCOM3_USART_ReadCountGet() < length);
    
    SERCOM3_USART_Read(message, length);
    
    // Null-terminate the buffer
    message[length] = '\0';
}

/* USBSerial_ReadUntil: Read characters until the endchar is found, eg  USBSerial_ReadUntil(buffer, '\n')*/
void USBSerial_ReadUntil(char *message, char endchar)
{
    size_t index = 0;  // Index to keep track of where to store the next byte in the message
    uint8_t byteReceived;

    // Ensure the message buffer is not NULL
    if (message == NULL) {
        return;
    }

    while (true) {
        // Wait until there is data available to read
        while (SERCOM3_USART_ReadCountGet() == 0);

        // Read the byte from the USART buffer
        size_t bytesRead = SERCOM3_USART_Read(&byteReceived, 1);
        
        if (bytesRead > 0) {
            // Store the received byte into the message buffer
            message[index++] = (char)byteReceived;

            // Check if we received the end character
            if (byteReceived == endchar) {
                break;  // Stop reading when the end character is found
            }
        }
    }

    // Null-terminate the message to ensure it is a valid C string
    message[index] = '\0';
}

// Read until it reaches a newline character
void USBSerial_ReadNewline(char *message) {
    USBSerial_ReadUntil(message, "\n");
}
