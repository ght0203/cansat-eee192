#include <string.h>

#define UART_BUFFER_SIZE 256  // Circular buffer size
#define GPGGA_MAX_LENGTH 82   // Maximum possible NMEA sentence length

volatile char dma_rx_buffer[UART_BUFFER_SIZE]; // DMA buffer
volatile size_t dma_head = 0;  // Head index (write position)
volatile size_t dma_tail = 0;  // Tail index (read position)

static volatile bool capturing_gpgga = false;
static volatile size_t gpgga_index = 0;
static volatile char gpgga_sentence[GPGGA_MAX_LENGTH];

// Function to configure DMA for USART RX
void setup_dma_uart_rx(void)
{
    // Configure DMA to continuously receive UART data into dma_rx_buffer
    // Example: Set up DMA for USART RX with circular mode enabled
    DMA_Setup(UART_DMA_CHANNEL, 
              (uint32_t)&SERCOM5_REGS->USART_INT.SERCOM_DATA, 
              (uint32_t)dma_rx_buffer, 
              UART_BUFFER_SIZE);
    
    // Enable Idle Line Detection interrupt (detects end of a message)
    USART_EnableIdleLineInterrupt();
}

// USART Idle Line Interrupt Handler (called when transmission pauses)
void USART_IdleLine_IRQHandler(void)
{
    // Process new data from DMA buffer
    process_nmea_dma();
}

// Process data from DMA buffer
void process_nmea_dma(void)
{
    while (dma_tail != dma_head)  // Read data while buffer is not empty
    {
        char received_byte = dma_rx_buffer[dma_tail];
        dma_tail = (dma_tail + 1) % UART_BUFFER_SIZE;

        // Detect start of an NMEA sentence
        if (received_byte == '$')
        {
            capturing_gpgga = false;  // Reset capture flag
            gpgga_index = 0;
        }

        // Capture only if it's a $GPGGA sentence
        if (gpgga_index < 6)
        {
            gpgga_sentence[gpgga_index++] = received_byte;

            if (gpgga_index == 6)
            {
                // Check if it matches "$GPGGA"
                if (strncmp(gpgga_sentence, "$GPGGA", 6) == 0)
                {
                    capturing_gpgga = true;
                }
            }
        }
        else if (capturing_gpgga)
        {
            if (gpgga_index < GPGGA_MAX_LENGTH - 1)
            {
                gpgga_sentence[gpgga_index++] = received_byte;
            }

            // End of sentence detected
            if (received_byte == '\n' || received_byte == '\r')
            {
                gpgga_sentence[gpgga_index] = '\0'; // Null-terminate
                capturing_gpgga = false;
                process_gpgga_sentence(gpgga_sentence); // Process valid GPGGA
            }
        }
    }
}
