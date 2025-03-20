#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "definitions.h"
#include <stdint.h>

#define F_CPU 48000000UL
#define CYCLES_PER_MS (F_CPU / 1000UL)
#define CYCLES_PER_LOOP 4UL
#define LOOP_COUNT (CYCLES_PER_MS / CYCLES_PER_LOOP)
#define GPS_BUFFER_SIZE 4000
#define CHUNK_SIZE 100

char gpsBuffer[GPS_BUFFER_SIZE];
uint32_t gpsBufferIndex = 0;
uint32_t loopCounter = 0;  // Added for debugging

void delay_ms(uint32_t ms) {
    volatile uint32_t count;
    while (ms--) {
        count = LOOP_COUNT;
        while (count--) {}
    }
}

int main(void)
{
    SYS_Initialize(NULL);
    SERCOM0_USART_Initialize();  
    SERCOM3_USART_Initialize();
    SERCOM3_USART_TransmitterEnable();
    
    const char welcomeMsg[] = "GPS Bridge IRQ Polling Started\r\n";
    SERCOM3_USART_Write((uint8_t*)welcomeMsg, sizeof(welcomeMsg) - 1);
    while (!SERCOM3_USART_TransmitComplete());
    
    //const char debugMsg[] = "Hi\r\n";
    const char debugMsg1[] = "Inside the for loop\r\n";
    const char debugMsg2[] = "Reached 1000 bytes, printing buffer\r\n";
    const char readSuccessMsg[] = "Read successful\r\n";
    const char readFailMsg[] = "Read failed\r\n";
    
    while (1)
    {
        if (SERCOM0_USART_ReadIsBusy())
        {
            asm("nop");
            continue;
        }
        
        SERCOM3_USART_Write((uint8_t*)debugMsg1, sizeof(debugMsg1) - 1);
        while (!SERCOM3_USART_TransmitComplete());
        
        bool status = SERCOM0_USART_Read(&gpsBuffer[gpsBufferIndex], CHUNK_SIZE);
        
        if (status)
        {
            SERCOM3_USART_Write((uint8_t*)readSuccessMsg, sizeof(readSuccessMsg) - 1);
            while (!SERCOM3_USART_TransmitComplete());
            
            gpsBufferIndex += CHUNK_SIZE;
            char byteCountMsg[] = "Total bytes: 0000\r\n";
            byteCountMsg[13] = '0' + (gpsBufferIndex / 1000) % 10;
            byteCountMsg[14] = '0' + (gpsBufferIndex / 100) % 10;
            byteCountMsg[15] = '0' + (gpsBufferIndex / 10) % 10;
            byteCountMsg[16] = '0' + gpsBufferIndex % 10;
            SERCOM3_USART_Write((uint8_t*)byteCountMsg, sizeof(byteCountMsg) - 1);
            while (!SERCOM3_USART_TransmitComplete());
            
            
            if (gpsBufferIndex >= 100)
            {
                // Update loop counter for debugging
                loopCounter++;
                char countMsg[] = "Loop count: 000\r\n";
                countMsg[12] = '0' + (loopCounter / 100) % 10;
                countMsg[13] = '0' + (loopCounter / 10) % 10;
                countMsg[14] = '0' + loopCounter % 10;
                
                SERCOM3_USART_Write((uint8_t*)countMsg, sizeof(countMsg) - 1);
                while (!SERCOM3_USART_TransmitComplete());
                
                SERCOM3_USART_Write((uint8_t*)debugMsg2, sizeof(debugMsg2) - 1);
                while (!SERCOM3_USART_TransmitComplete());
                
                // First try printing the first 10 bytes as a test
                const char firstBytesMsg[] = "First 10 bytes: ";
                SERCOM3_USART_Write((uint8_t*)firstBytesMsg, sizeof(firstBytesMsg) - 1);
                while (!SERCOM3_USART_TransmitComplete());
                
                // Print just the first 10 bytes
                SERCOM3_USART_Write((uint8_t*)gpsBuffer, 10);
                while (!SERCOM3_USART_TransmitComplete());
                
                // Print newline
                const char newlineMsg[] = "\r\n";
                SERCOM3_USART_Write((uint8_t*)newlineMsg, sizeof(newlineMsg) - 1);
                while (!SERCOM3_USART_TransmitComplete());
                
                // Now try printing the entire buffer byte by byte with a counter
                const char byteByByteMsg[] = "Printing byte by byte:\r\n";
                SERCOM3_USART_Write((uint8_t*)byteByByteMsg, sizeof(byteByByteMsg) - 1);
                while (!SERCOM3_USART_TransmitComplete());
                
                for (uint32_t i = 0; i < gpsBufferIndex && i < 100; i++)
                {
                    // Print the byte number
                    char byteNumMsg[] = "Byte 000: 0x00 | ";
                    byteNumMsg[5] = '0' + (i / 100) % 10;
                    byteNumMsg[6] = '0' + (i / 10) % 10;
                    byteNumMsg[7] = '0' + i % 10;

                    // Convert byte to hex
                    uint8_t byteValue = gpsBuffer[i];
                    char hexDigits[] = "0123456789ABCDEF";
                    byteNumMsg[13] = hexDigits[(byteValue >> 4) & 0xF];
                    byteNumMsg[14] = hexDigits[byteValue & 0xF];

                    SERCOM3_USART_Write((uint8_t*)byteNumMsg, sizeof(byteNumMsg) - 1);
                    while (!SERCOM3_USART_TransmitComplete());

                    // Print the character if it's printable (between 32 and 126)
                    if (byteValue >= 32 && byteValue <= 126) {
                        SERCOM3_USART_Write((uint8_t*)&gpsBuffer[i], 1);
                    } else {
                        // Print a placeholder for non-printable characters
                        char nonPrintable = '.';
                        SERCOM3_USART_Write((uint8_t*)&nonPrintable, 1);
                    }

                    // Print newline
                    const char newlineMsg[] = "\r\n";
                    SERCOM3_USART_Write((uint8_t*)newlineMsg, sizeof(newlineMsg) - 1);
                    while (!SERCOM3_USART_TransmitComplete());

                    // Add a small delay between bytes
                    delay_ms(1);
                }
                
                gpsBufferIndex = 0;
            }
        }
        else
        {
            SERCOM3_USART_Write((uint8_t*)readFailMsg, sizeof(readFailMsg) - 1);
            while (!SERCOM3_USART_TransmitComplete());
        }
        
        delay_ms(10);
    }
    
    return 0;
}