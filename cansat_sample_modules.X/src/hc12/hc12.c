#include "hc12.h"
#include "sercom5_usart.h"

void HC12_Initialize(void) {
    SERCOM5_USART_Initialize();
    PORT_SEC_REGS->GROUP[1].PORT_PINCFG[2] = 0x1U;
    PORT_SEC_REGS->GROUP[1].PORT_PINCFG[3] = 0x1U;
    PORT_SEC_REGS->GROUP[1].PORT_PMUX[1] = 0x33U;
}

// ------------HC12Serial_Write(formatted_str)----------------------
// example usage:
// Sending a simple string: HC12Serial_Write("Hello, HC12! \r\n");
// Max transmit length, 512 characters (ring buffer size)
void HC12Serial_Write(const char * str)
{
    uint8_t length = strlen(str);
    if (length > 512) return;
    while(SERCOM5_USART_WriteFreeBufferCountGet() < length); // wait for free space
    // Transmit the formatted string
    SERCOM5_USART_Write((void *)str, length);
}

// ------------HC12Serial_Read(buffer, length)----------------------
// example usage:
// char message[128];
// HC12Serial_Read(message, 128); // program stops until 128 chars is read
void HC12Serial_Read(char *buffer, uint8_t length)
{
    // Ensure the buffer is valid
    if (buffer == NULL || length == 0) {
        return;
    }

    while (SERCOM5_USART_ReadCountGet() < length);
    SERCOM5_USART_Read(buffer, length);
    
    // Null-terminate the buffer
    buffer[length] = '\0';
}
// If 'length' characters are already available in the receiver ring buffer, 
// the function completes immediately.