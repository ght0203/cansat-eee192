#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "definitions.h"    // SYS function prototypes
#include <stdint.h>

#define F_CPU 48000000UL         // CPU clock frequency: 48 MHz
#define CYCLES_PER_MS (F_CPU / 1000UL)  // 48000 cycles per millisecond

// Estimate the number of cycles each loop iteration takes.
#define CYCLES_PER_LOOP 4UL       
#define LOOP_COUNT (CYCLES_PER_MS / CYCLES_PER_LOOP)

// Define a smaller read size for the GPS data
#define READ_SIZE 1

void delay_ms(uint32_t ms) {
    volatile uint32_t count;
    while (ms--) {
        count = LOOP_COUNT;
        while (count--) {
            // Empty loop for delay
        }
    }
}

int main(void)
{
    SYS_Initialize(NULL);

    // --- Initialize SERCOM0 (GPS) ---
    SERCOM0_USART_Initialize();
    // Enable receiver so SERCOM0 can accept data from the GPS.
    SERCOM0_USART_ReceiverEnable();
    
    // --- Initialize SERCOM3 (Debug Terminal) ---
    SERCOM3_USART_Initialize();
    // Enable transmitter to send data to the terminal.
    SERCOM3_USART_TransmitterEnable();

    // Write a welcome message to the debug terminal.
    const char welcomeMsg[] = "Hello Terminal\r\n";
    SERCOM3_USART_Write((void *)welcomeMsg, sizeof(welcomeMsg) - 1);
    while (!SERCOM3_USART_TransmitComplete())
    {
        // Wait for the welcome message to be completely transmitted.
    }

    // Buffer to hold received data from GPS
    uint8_t rxBuffer[READ_SIZE];

    while (1)
    {
        // Start a non-blocking read from the GPS (SERCOM0) for READ_SIZE bytes.
        if (SERCOM0_USART_Read(rxBuffer, READ_SIZE))
        {
            LED_PA15_Set();
            // Wait until the read operation is complete.
            while (SERCOM0_USART_ReadIsBusy());
            LED_PA15_Clear();
            
            // Get the number of bytes received.
            size_t numBytes = SERCOM0_USART_ReadCountGet();

            if (numBytes > 0)
            {
                // Forward the received data to the terminal using SERCOM3.
                SERCOM3_USART_Write(rxBuffer, numBytes);
                // Wait for the transmission to complete.
                while (!SERCOM3_USART_TransmitComplete());
            }
        }
        // Other processing can be done here.
    }

    return 0;
}
