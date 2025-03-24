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

// Global variables
static char gpsBuffer[GPS_BUFFER_SIZE];
static uint32_t gpsBufferIndex = 0;
static uint32_t noDataCounter = 0;

/* typedef for non-secure callback functions */
typedef void (*funcptr_void) (void) __attribute__((cmse_nonsecure_call));
volatile uint8_t delay_pause = 0;

// Function prototypes
void delay_ms(uint32_t ms);
bool validateChecksum(const char *sentence, uint32_t len);
bool readGPSData(void);
int findCharacter(const char *buffer, uint32_t size, char target);
void processGPSBuffer(void);
bool processSingleNMEASentence(void);
void transmitSentence(const char *sentence, uint32_t length);

void delay_ms(uint32_t ms) {
    delay_pause = 1U;
        /* In one-shot timer mode, first disable the timer */
    TCC0_REGS->TCC_CTRLA &= ~TCC_CTRLA_ENABLE_Msk;
    while((TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_ENABLE_Msk) == TCC_SYNCBUSY_ENABLE_Msk)
    {
        /* Wait for Write Synchronization */
    }
    TCC0_REGS->TCC_PER = (ms * 46.875);
    while((TCC0_REGS->TCC_SYNCBUSY) != 0U);
    TCC0_REGS->TCC_CTRLA |= TCC_CTRLA_ENABLE_Msk;
    while((TCC0_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_ENABLE_Msk) == TCC_SYNCBUSY_ENABLE_Msk)
    {
        /* Wait for Write Synchronization */
    }
    while(delay_pause);
    
}

// Find first occurrence of character in buffer
int findCharacter(const char *buffer, uint32_t size, char target) {
    for (uint32_t i = 0; i < size; i++) {
        if (buffer[i] == target) {
            return i;
        }
    }
    return -1;
}

// Validate NMEA checksum
bool validateChecksum(const char *sentence, uint32_t len) {
    if (sentence[0] != '$')
        return false;
    
    int asteriskIndex = findCharacter(sentence, len, '*');
    if (asteriskIndex < 0)
        return false;  // No '*' found.
    
    uint8_t checksum = 0;
    for (int i = 1; i < asteriskIndex; i++) {
        checksum ^= (uint8_t)(sentence[i]);
    }
    
    // Check that there are at least two characters after '*'
    if (asteriskIndex + 3 > len)
        return false;
    
    char hexStr[3];
    hexStr[0] = sentence[asteriskIndex + 1];
    hexStr[1] = sentence[asteriskIndex + 2];
    hexStr[2] = '\0';
    
    // Verify that both characters are valid hex digits.
    if (!isxdigit(hexStr[0]) || !isxdigit(hexStr[1]))
        return false;
    
    uint8_t sentenceChecksum = (uint8_t)strtoul(hexStr, NULL, 16);
    
    return (checksum == sentenceChecksum);
}

// Read data from GPS module
bool readGPSData(void) {
    if (SERCOM0_USART_ReadIsBusy()) {
        noDataCounter++;
        return false;
    }
    
    // Check if there's room in the buffer
    if (gpsBufferIndex + CHUNK_SIZE > GPS_BUFFER_SIZE) {
        // Buffer is full, discard old data
        return false;
    }
    
    if (SERCOM0_USART_Read((uint8_t*)&gpsBuffer[gpsBufferIndex], CHUNK_SIZE)) {
        while (SERCOM0_USART_ReadIsBusy()) {
            asm("nop");
        }
        uint32_t bytesRead = SERCOM0_USART_ReadCountGet();
        if (bytesRead > 0) {
            gpsBufferIndex += bytesRead;
            noDataCounter = 0; // Reset timeout counter when new data arrives
            return true;
        }
    }
    return false;
}

// Process a single complete NMEA sentence
bool processSingleNMEASentence(void) {
    if (gpsBufferIndex == 0)
        return false;
    
    // Resynchronization: Ensure the buffer starts with '$'
    if (gpsBuffer[0] != '$') {
        int firstDollar = findCharacter(gpsBuffer, gpsBufferIndex, '$');
        if (firstDollar < 0) {
            // No '$' found; discard entire buffer
            gpsBufferIndex = 0;
            return false;
        } else if (firstDollar > 0) {
            uint32_t remaining = gpsBufferIndex - firstDollar;
            memmove(gpsBuffer, &gpsBuffer[firstDollar], remaining);
            gpsBufferIndex = remaining;
        }
    }
    
    // Look for '*' to identify the checksum field
    int starIndex = findCharacter(gpsBuffer, gpsBufferIndex, '*');
    if (starIndex < 0)
        return false; // '*' not found yet; wait for more data
    
    // Ensure there are at least two characters after '*'
    if (starIndex + 2 >= gpsBufferIndex)
        return false; // Incomplete checksum digits
    
    // Determine the end index of the sentence candidate
    uint32_t sentenceEnd = starIndex + 3;
    // Include any trailing CR or LF characters temporarily
    while (sentenceEnd < gpsBufferIndex && 
          (gpsBuffer[sentenceEnd] == '\r' || gpsBuffer[sentenceEnd] == '\n')) {
        sentenceEnd++;
    }
    
    // Trim trailing CR/LF from the sentence
    uint32_t trimmedSentenceEnd = sentenceEnd;
    while (trimmedSentenceEnd > 0 && 
          (gpsBuffer[trimmedSentenceEnd - 1] == '\r' || gpsBuffer[trimmedSentenceEnd - 1] == '\n')) {
        trimmedSentenceEnd--;
    }
    uint32_t sentenceLen = trimmedSentenceEnd;
    
    // Validate the sentence checksum
    if (!validateChecksum(gpsBuffer, sentenceLen)) {
        // Invalid sentence; discard this chunk and re-sync
        uint32_t remaining = gpsBufferIndex - sentenceEnd;
        if (remaining > 0)
            memmove(gpsBuffer, &gpsBuffer[sentenceEnd], remaining);
        gpsBufferIndex = remaining;
        return true; // Continue processing other potential sentences
    }
    
    // Check if it's a GPRMC sentence
    if (sentenceLen >= 6 && strncmp(gpsBuffer, "$GPGGA", 6) == 0) {
        transmitSentence(gpsBuffer, sentenceLen);
    }
    
    // Uncomment to also process GPGGA sentences
    /*
    if (sentenceLen >= 6 && strncmp(gpsBuffer, "$GPGGA", 6) == 0) {
        transmitSentence(gpsBuffer, sentenceLen);
    }
    */
    
    // Remove the processed sentence from the buffer
    uint32_t remaining = gpsBufferIndex - sentenceEnd;
    if (remaining > 0)
        memmove(gpsBuffer, &gpsBuffer[sentenceEnd], remaining);
    gpsBufferIndex = remaining;
    
    return true;
}

// Transmit a sentence over the debug UART
void transmitSentence(const char *sentence, uint32_t length) {
    SERCOM3_USART_Write((uint8_t*)sentence, length);
    while (!SERCOM3_USART_TransmitComplete());
    // Append a single CR+LF
    SERCOM3_USART_Write((uint8_t*)"\r\n", 2);
    while (!SERCOM3_USART_TransmitComplete());
}

// Process all available NMEA sentences in the buffer
void processGPSBuffer(void) {
    // Clear buffer if no new data for a while
    if (gpsBufferIndex > 0 && noDataCounter > INCOMPLETE_TIMEOUT_THRESHOLD) {
        gpsBufferIndex = 0;
        noDataCounter = 0;
    }
    
    // Process complete NMEA sentences from the buffer
    while (processSingleNMEASentence()) {
        // Continue processing until no more complete sentences
    }
}

int main(void) {
    // Initialize system and peripherals
    SYS_Initialize(NULL);
    SERCOM0_USART_Initialize();   // GPS RX
    SERCOM3_USART_Initialize();   // Debug TX
    SERCOM3_USART_TransmitterEnable();
    
    while (1) {
        readGPSData();
        processGPSBuffer();
    }
    
    return 0;
}