#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "definitions.h"
#include <stdint.h>
#include <string.h>
#include <ctype.h>  // For isxdigit()

#define F_CPU 48000000UL
#define GPS_BUFFER_SIZE 4000
#define CHUNK_SIZE 100
#define INCOMPLETE_TIMEOUT_THRESHOLD 200  // Adjust threshold (iterations) as needed

char gpsBuffer[GPS_BUFFER_SIZE];
uint32_t gpsBufferIndex = 0;

void delay_ms(uint32_t ms) {
    volatile uint32_t count;
    while(ms--){
        count = (F_CPU / 1000UL) / 4;
        while(count--) {}
    }
}

// Validate NMEA checksum:
// The sentence should be in the format: "$...*XX"
// This function computes the XOR of characters between '$' and '*' (not including either)
// and compares it to the two hex digits following '*'.
bool validateChecksum(const char *sentence, uint32_t len) {
    if (sentence[0] != '$')
        return false;
    
    const char* asterisk = NULL;
    for (uint32_t i = 0; i < len; i++){
        if (sentence[i] == '*'){
            asterisk = &sentence[i];
            break;
        }
    }
    if (asterisk == NULL)
        return false;  // No '*' found.
    
    uint8_t checksum = 0;
    for (const char* p = sentence + 1; p < asterisk; p++){
        checksum ^= (uint8_t)(*p);
    }
    
    // Check that there are at least two characters after '*'
    if ((asterisk - sentence) + 3 > len)
        return false;
    
    char hexStr[3];
    hexStr[0] = *(asterisk + 1);
    hexStr[1] = *(asterisk + 2);
    hexStr[2] = '\0';
    
    // Verify that both characters are valid hex digits.
    if (!isxdigit(hexStr[0]) || !isxdigit(hexStr[1]))
        return false;
    
    uint8_t sentenceChecksum = (uint8_t)strtoul(hexStr, NULL, 16);
    
    return (checksum == sentenceChecksum);
}

int main(void)
{
    SYS_Initialize(NULL);
    SERCOM0_USART_Initialize();   // GPS RX
    SERCOM3_USART_Initialize();   // Debug TX
    SERCOM3_USART_TransmitterEnable();

    uint32_t noDataCounter = 0;
    
    while (1)
    {
        // Initiate a new read if not already busy.
        if (!SERCOM0_USART_ReadIsBusy()) {
            if (SERCOM0_USART_Read(&gpsBuffer[gpsBufferIndex], CHUNK_SIZE)) {
                while (SERCOM0_USART_ReadIsBusy()){
                    asm("nop");
                }
                uint32_t bytesRead = SERCOM0_USART_ReadCountGet();
                if (bytesRead > 0) {
                    gpsBufferIndex += bytesRead;
                    noDataCounter = 0; // Reset timeout counter when new data arrives.
                }
            }
        } else {
            noDataCounter++;
        }
        
        // Clear buffer if no new data for a while.
        if (gpsBufferIndex > 0 && noDataCounter > INCOMPLETE_TIMEOUT_THRESHOLD) {
            gpsBufferIndex = 0;
            noDataCounter = 0;
        }
        
        // Process complete NMEA sentences from the buffer.
        while (1) {
            if (gpsBufferIndex == 0)
                break;
            
            // Resynchronization: Ensure the buffer starts with '$'.
            if (gpsBuffer[0] != '$') {
                int firstDollar = -1;
                for (uint32_t i = 0; i < gpsBufferIndex; i++){
                    if (gpsBuffer[i] == '$'){
                        firstDollar = i;
                        break;
                    }
                }
                if (firstDollar < 0) {
                    // No '$' found; discard entire buffer.
                    gpsBufferIndex = 0;
                    break;
                } else if (firstDollar > 0) {
                    uint32_t remaining = gpsBufferIndex - firstDollar;
                    memmove(gpsBuffer, &gpsBuffer[firstDollar], remaining);
                    gpsBufferIndex = remaining;
                }
            }
            
            // At this point, the buffer starts with '$'.
            // Look for '*' to identify the checksum field.
            int starIndex = -1;
            for (uint32_t i = 0; i < gpsBufferIndex; i++){
                if (gpsBuffer[i] == '*'){
                    starIndex = i;
                    break;
                }
            }
            if (starIndex == -1)
                break; // '*' not found yet; wait for more data.
            
            // Ensure there are at least two characters after '*'
            if (starIndex + 2 >= gpsBufferIndex)
                break; // Incomplete checksum digits.
            
            // Determine the end index of the sentence candidate.
            // We define the sentence as ending after '*' and the two checksum digits.
            uint32_t sentenceEnd = starIndex + 3;
            // Include any trailing CR or LF characters temporarily.
            while (sentenceEnd < gpsBufferIndex && 
                  (gpsBuffer[sentenceEnd] == '\r' || gpsBuffer[sentenceEnd] == '\n')) {
                sentenceEnd++;
            }
            
            // Now, trim trailing CR/LF from the sentence to avoid double newlines.
            uint32_t trimmedSentenceEnd = sentenceEnd;
            while (trimmedSentenceEnd > 0 && 
                  (gpsBuffer[trimmedSentenceEnd - 1] == '\r' || gpsBuffer[trimmedSentenceEnd - 1] == '\n')) {
                trimmedSentenceEnd--;
            }
            uint32_t sentenceLen = trimmedSentenceEnd;
            
            // Validate the sentence checksum.
            if (!validateChecksum(gpsBuffer, sentenceLen)) {
                // Invalid sentence; discard this chunk and re-sync.
                uint32_t remaining = gpsBufferIndex - sentenceEnd;
                if (remaining > 0)
                    memmove(gpsBuffer, &gpsBuffer[sentenceEnd], remaining);
                gpsBufferIndex = remaining;
                continue;
            }
            
            // Only transmit if it is a GPRMC sentence.
            if (sentenceLen >= 6 && strncmp(gpsBuffer, "$GPRMC", 6) == 0) {
                SERCOM3_USART_Write((uint8_t*)gpsBuffer, sentenceLen);
                while (!SERCOM3_USART_TransmitComplete());
                // Append a single CR+LF to ensure a proper line break.
                SERCOM3_USART_Write((uint8_t*)"\r\n", 2);
                while (!SERCOM3_USART_TransmitComplete());
            }
            
            /*
            // Only transmit if it is a GPGGA sentence.
            if (sentenceLen >= 6 && strncmp(gpsBuffer, "$GPGGA", 6) == 0) {
                SERCOM3_USART_Write((uint8_t*)gpsBuffer, sentenceLen);
                while (!SERCOM3_USART_TransmitComplete());
                // Append a single CR+LF to ensure a proper line break.
                SERCOM3_USART_Write((uint8_t*)"\r\n", 2);
                while (!SERCOM3_USART_TransmitComplete());
            }
            */
            // Remove the processed sentence from the buffer.
            uint32_t remaining = gpsBufferIndex - sentenceEnd;
            if (remaining > 0)
                memmove(gpsBuffer, &gpsBuffer[sentenceEnd], remaining);
            gpsBufferIndex = remaining;
        }
        
        // Short delay to avoid hogging the CPU.
        delay_ms(1);
    }
    
    return 0;
}