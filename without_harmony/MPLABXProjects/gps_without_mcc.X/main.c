#include <xc.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "platform.h"

// For GPS, we typically look for an NMEA sentence start character, e.g., '$'
#define GPS_START_BYTE '$'

#define FLAG_GPS_RECEIVED (1 << 0)

static const char banner_msg[] =
"\033[0m\033[2J\033[1;1H"
"+-----------------------------------------------------------+\r\n"
"| EEE 192: GPS Module Readings                              |\r\n"
"+-----------------------------------------------------------+\r\n";

typedef struct prog_state_type {
    uint16_t flags;
    platform_usart_tx_bufdesc_t tx_desc[2];
    char tx_buf[128];
    uint16_t tx_blen;
    platform_usart_rx_async_desc_t rx_desc;
    char rx_desc_buf[32];
} prog_state_t;

static void prog_setup(prog_state_t *ps) {
    platform_init();
    platform_usart_init();
    platform_usart_gps_init();
    
    // Send the banner message
    ps->tx_desc[0].buf = banner_msg;
    ps->tx_desc[0].len = sizeof(banner_msg) - 1;
    platform_usart_cdc_tx_async(&ps->tx_desc[0], 1);

    ps->rx_desc.buf = ps->rx_desc_buf;
    ps->rx_desc.max_len = sizeof(ps->rx_desc_buf);
    platform_usart_gps_rx_async(&ps->rx_desc);
}

static void gps_read(prog_state_t *ps) {
    if (!platform_usart_gps_rx_busy() && sizeof(ps->rx_desc_buf) >= 32) {
        uint8_t *buffer = (uint8_t *)ps->rx_desc_buf;
        
        // Check if the first character indicates an NMEA sentence (e.g., '$')
        if (buffer[0] == GPS_START_BYTE) {  
            // Example: Process the NMEA sentence here.
            // (Parsing logic should be added based on your GPS module's output.)
            snprintf(ps->tx_buf, sizeof(ps->tx_buf), "Received GPS data: %s\r\n", buffer);
        }

        // Send the processed data to USB CDC
        ps->tx_desc[0].buf = ps->tx_buf;
        ps->tx_desc[0].len = strlen(ps->tx_buf);
        platform_usart_cdc_tx_async(&ps->tx_desc[0], 1);

        // Restart reception
        memset(ps->rx_desc_buf, 0, sizeof(ps->rx_desc_buf)); // Clear buffer before next read
        platform_usart_gps_rx_async(&ps->rx_desc);
    }
}

static void prog_loop_one(prog_state_t *ps) {
    platform_do_loop_one();
    gps_read(ps);
}

int main(void) {
    prog_state_t ps;
    prog_setup(&ps);
    
    for (;;) {
        prog_loop_one(&ps);
    }
    return 1;
}
