#include "hc12.h"
#include "sercom5_usart.h"

void HC12_Initialize(void) {
    SERCOM5_USART_Initialize();
    PORT_SEC_REGS->GROUP[1].PORT_PINCFG[2] = 0x1U;
    PORT_SEC_REGS->GROUP[1].PORT_PINCFG[3] = 0x1U;
    PORT_SEC_REGS->GROUP[1].PORT_PMUX[1] = 0x33U;
}

void HC12Serial_Write(const char *formatted_str, ...)
{
    va_list args;
    char buffer[32]; // Statically allocate a 32-byte buffer

    // First, determine the required buffer size (excluding null terminator)
    va_start(args, formatted_str);
    int length = vsnprintf(NULL, 0, formatted_str, args);
    va_end(args);

    if (length <= 0 || length >= sizeof(buffer)) return; // Error in formatting or buffer too small

    // Format the string into the buffer
    va_start(args, formatted_str);
    vsnprintf(buffer, sizeof(buffer), formatted_str, args);
    va_end(args);

    while(SERCOM3_USART_WriteFreeBufferCountGet() < length); // wait for free space
    // Transmit the formatted string
    SERCOM5_USART_Write((void *)buffer, length);
}