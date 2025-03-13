#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "definitions.h"    // Contains SERCOM0_USART_Initialize, SERCOM3_USART_Initialize, etc.
#include <stdint.h>

// 48 MHz system clock assumption
#define F_CPU 48000000UL
#define CYCLES_PER_MS (F_CPU / 1000UL)
#define CYCLES_PER_LOOP 4UL
#define LOOP_COUNT (CYCLES_PER_MS / CYCLES_PER_LOOP)

void delay_ms(uint32_t ms) {
    volatile uint32_t count;
    while (ms--) {
        count = LOOP_COUNT;
        while (count--) {
            // Simple busy-wait
        }
    }
}

int main(void)
{
    // Initialize system (clocks, NVIC, etc.)
    SYS_Initialize(NULL);

    // Initialize SERCOM0 at 9600 (RX ring buffer) for GPS
    SERCOM0_USART_Initialize();
    // SERCOM0 is now ready to receive data in its ring buffer

    // Initialize SERCOM3 at 9600 for debug output
    SERCOM3_USART_Initialize();
    SERCOM3_USART_TransmitterEnable();

    // Print a hello message so we know it's running
    const char welcomeMsg[] = "GPS Bridge Started\r\n";
    SERCOM3_USART_Write((uint8_t*)welcomeMsg, sizeof(welcomeMsg) - 1);
    while (!SERCOM3_USART_TransmitComplete());

    while (1)
    {
        // 1) Check if SERCOM0 has any data (like ss.available() > 0)
        size_t available = SERCOM0_USART_ReadCountGet();
        if (available > 0)
        {
            // 2) Read one byte (like byte gpsData = ss.read();)
            uint8_t gpsData;
            size_t bytesRead = SERCOM0_USART_Read(&gpsData, 1);

            if (bytesRead == 1)
            {
                // 3) Write that byte to SERCOM3 (like Serial.write(gpsData);)
                SERCOM3_USART_Write(&gpsData, 1);
                while (!SERCOM3_USART_TransmitComplete());
            }
        } else {
            SERCOM3_USART_Write("No data to read.\r\n", 1);
        }

        // Optional small delay or other tasks
        // delay_ms(1);
    }

    // Normally never reached
    return 0;
}
