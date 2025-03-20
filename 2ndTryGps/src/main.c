#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "definitions.h"
#include <stdint.h>
#include <string.h>

#define F_CPU 48000000UL
#define GPS_BUFFER_SIZE 4000
#define CHUNK_SIZE 100

char gpsBuffer[GPS_BUFFER_SIZE];
uint32_t gpsBufferIndex = 0;

void delay_ms(uint32_t ms) {
    volatile uint32_t count;
    while(ms--){
        count = (F_CPU / 1000UL) / 4;
        while(count--) {}
    }
}

int main(void)
{
    SYS_Initialize(NULL);
    SERCOM0_USART_Initialize();   // GPS RX
    SERCOM3_USART_Initialize();   // Debug TX
    SERCOM3_USART_TransmitterEnable();

    while(1)
    {
        // Initiate a new read if not already busy.
        if (!SERCOM0_USART_ReadIsBusy()) {
            if (SERCOM0_USART_Read(&gpsBuffer[gpsBufferIndex], CHUNK_SIZE)) {
                // Wait for this read to complete.
                while(SERCOM0_USART_ReadIsBusy()){
                    asm("nop");
                }
                uint32_t bytesRead = SERCOM0_USART_ReadCountGet();
                if(bytesRead > 0) {
                    gpsBufferIndex += bytesRead;
                }
            }
        }
        
        // Process complete NMEA sentences in the accumulated buffer.
        while(1) {
            int start = -1, end = -1;
            // Find the start marker ('$').
            for(uint32_t i = 0; i < gpsBufferIndex; i++){
                if(gpsBuffer[i] == '$'){
                    start = i;
                    break;
                }
            }
            if(start == -1) break;  // No sentence start found.
            
            // Look for the newline ('\n') that ends the sentence.
            for(uint32_t i = start; i < gpsBufferIndex; i++){
                if(gpsBuffer[i] == '\n'){
                    end = i;
                    break;
                }
            }
            if(end == -1) break;  // No complete sentence yet.
            
            // Compute sentence length and trim a trailing CR if present.
            uint32_t sentenceLen = end - start + 1;
            if(sentenceLen >= 2 && gpsBuffer[end-1] == '\r')
                sentenceLen--;
            
            // Output the complete sentence on its own line.
            SERCOM3_USART_Write((uint8_t*)&gpsBuffer[start], sentenceLen);
            while(!SERCOM3_USART_TransmitComplete());
            // Append CR+LF explicitly.
            SERCOM3_USART_Write((uint8_t*)"\r\n", 2);
            while(!SERCOM3_USART_TransmitComplete());
            
            // Shift any remaining data in the buffer to the front.
            uint32_t remaining = gpsBufferIndex - (end + 1);
            if(remaining > 0)
                memmove(gpsBuffer, &gpsBuffer[end + 1], remaining);
            gpsBufferIndex = remaining;
        }
        
        // Short delay to avoid hogging the CPU (adjust as needed).
        delay_ms(5);
    }
    
    return 0;
}
