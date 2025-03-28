#include <xc.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "platform.h"

#define GPS_START_BYTE '$'
#define NMEA_MAX_LENGTH 120
#define MAX_NMEA_SENTENCES 5

typedef struct {
    char buffer[NMEA_MAX_LENGTH];
    uint16_t buffer_index;
    bool sentence_complete;
} NMEAParser;

typedef struct prog_state_type {
    uint16_t flags;
    platform_usart_tx_bufdesc_t tx_desc[2];
    char tx_buf[NMEA_MAX_LENGTH];
    uint16_t tx_blen;
    platform_usart_rx_async_desc_t rx_desc;
    char rx_desc_buf[256];  // Increased buffer size
    NMEAParser nmea_parser;
} prog_state_t;

// Function prototypes
static bool is_valid_nmea_sentence(const char* sentence);
static void reset_nmea_parser(NMEAParser* parser);
static void process_received_byte(NMEAParser* parser, char byte);

static void prog_setup(prog_state_t *ps) {
    platform_init();
    platform_usart_init();
    platform_usart_gps_init();
    
    // Initialize NMEA parser
    reset_nmea_parser(&ps->nmea_parser);
    
    // Send banner message (same as before)
    ps->tx_desc[0].buf = 
        "\033[0m\033[2J\033[1;1H"
        "+-----------------------------------------------------------+\r\n"
        "| EEE 192: GPS Module Readings                              |\r\n"
        "+-----------------------------------------------------------+\r\n";
    ps->tx_desc[0].len = strlen(ps->tx_desc[0].buf);
    platform_usart_cdc_tx_async(&ps->tx_desc[0], 1);
    
    ps->rx_desc.buf = ps->rx_desc_buf;
    ps->rx_desc.max_len = sizeof(ps->rx_desc_buf);
    platform_usart_gps_rx_async(&ps->rx_desc);
}

// Reset NMEA parser state
static void reset_nmea_parser(NMEAParser* parser) {
    memset(parser->buffer, 0, sizeof(parser->buffer));
    parser->buffer_index = 0;
    parser->sentence_complete = false;
}

// Check if NMEA sentence is valid (basic checksum verification)
static bool is_valid_nmea_sentence(const char* sentence) {
    if (strlen(sentence) < 7) return false; // Minimum valid sentence length
    
    // Check for valid NMEA sentence starting with $
    if (sentence[0] != '$') return false;
    
    // Basic validation for GPGGA or GPRMC
    if (strncmp(sentence, "$GPGGA", 6) != 0 && 
        strncmp(sentence, "$GPRMC", 6) != 0) {
        return false;
    }
    
    return true;
}

// Process each received byte
static void process_received_byte(NMEAParser* parser, char byte) {
    // Start of a new sentence
    if (byte == '$' && parser->buffer_index > 0) {
        // Previous sentence was not complete, reset
        reset_nmea_parser(parser);
    }
    
    // Prevent buffer overflow
    if (parser->buffer_index >= NMEA_MAX_LENGTH - 1) {
        reset_nmea_parser(parser);
    }
    
    // Add byte to buffer
    parser->buffer[parser->buffer_index++] = byte;
    
    // Check for end of sentence (CR/LF)
    if (byte == '\n') {
        // Null terminate the string
        parser->buffer[parser->buffer_index] = '\0';
        parser->sentence_complete = true;
    }
}

static void gps_read(prog_state_t *ps) {
    // Check if reception is complete and we have some data
    if (!platform_usart_gps_rx_busy() && ps->rx_desc.compl_info.data_len > 0) {
        uint16_t rx_len = ps->rx_desc.compl_info.data_len;
        
        // Process each received byte
        for (uint16_t i = 0; i < rx_len; i++) {
            process_received_byte(&ps->nmea_parser, ps->rx_desc_buf[i]);
            
            // If a complete sentence is found
            if (ps->nmea_parser.sentence_complete) {
                // Validate the sentence
                if (is_valid_nmea_sentence(ps->nmea_parser.buffer)) {
                    // Prepare transmission
                    snprintf(ps->tx_buf, sizeof(ps->tx_buf), "%s", ps->nmea_parser.buffer);
                    
                    // Send processed data to USB CDC
                    ps->tx_desc[0].buf = ps->tx_buf;
                    ps->tx_desc[0].len = strlen(ps->tx_buf);
                    platform_usart_cdc_tx_async(&ps->tx_desc[0], 1);
                }
                
                // Reset parser for next sentence
                reset_nmea_parser(&ps->nmea_parser);
            }
        }
        
        // Restart reception: clear buffer and re-enable GPS rx
        memset(ps->rx_desc_buf, 0, sizeof(ps->rx_desc_buf));
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