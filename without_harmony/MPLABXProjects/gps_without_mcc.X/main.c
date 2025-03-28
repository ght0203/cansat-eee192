#include <xc.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "platform.h"

#define GPS_START_BYTE '$'
#define NMEA_MAX_LENGTH 120
#define RX_BUF_SIZE 256

// Structure for raw NMEA parsing state
typedef struct {
    char buffer[NMEA_MAX_LENGTH];
    uint16_t buffer_index;
    bool sentence_complete;
} NMEAParser;

// Structure for overall program state
typedef struct prog_state_type {
    uint16_t flags;
    platform_usart_tx_bufdesc_t tx_desc[2];
    char tx_buf[NMEA_MAX_LENGTH];
    uint16_t tx_blen;
    platform_usart_rx_async_desc_t rx_desc;
    char rx_desc_buf[RX_BUF_SIZE];  // Increased buffer size
    NMEAParser nmea_parser;
} prog_state_t;

// Structure to hold the parsed key fields from a GPGGA sentence
typedef struct {
    char utc_time[11];    // e.g., "081512.00"
    char latitude[16];    // e.g., "1437.82800"
    char lat_dir[2];      // e.g., "N"
    char longitude[16];   // e.g., "12101.34403"
    char lon_dir[2];      // e.g., "E"
    char altitude[10];    // e.g., "55.3"
} ParsedNMEA;

// Function prototypes
static bool is_valid_nmea_sentence(const char* sentence);
static void reset_nmea_parser(NMEAParser* parser);
static void process_received_byte(NMEAParser* parser, char byte);
static bool parse_gpgga_sentence(const char *sentence, ParsedNMEA *parsed);
static void gps_read(prog_state_t *ps);
static void prog_setup(prog_state_t *ps);
static void prog_loop_one(prog_state_t *ps);

//
// Setup: initialize platforms, USARTs, parser, etc.
//
static void prog_setup(prog_state_t *ps) {
    platform_init();
    platform_usart_init();
    platform_usart_gps_init();
    
    // Initialize NMEA parser
    reset_nmea_parser(&ps->nmea_parser);
    
    // Send banner message (as before)
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

//
// Reset NMEA parser state.
//
static void reset_nmea_parser(NMEAParser* parser) {
    memset(parser->buffer, 0, sizeof(parser->buffer));
    parser->buffer_index = 0;
    parser->sentence_complete = false;
}

//
// Validate the sentence: here we only accept sentences starting with '$'
// and, for our parsing purposes, a GPGGA sentence.
//
static bool is_valid_nmea_sentence(const char* sentence) {
    if (strlen(sentence) < 7) return false; // Minimum valid sentence length
    
    // Check for valid NMEA sentence starting with '$'
    if (sentence[0] != '$') return false;
    
    // Accept only GPGGA sentences for parsing key fields
    if (strncmp(sentence, "$GPGGA", 6) != 0) {
        return false;
    }
    
    return true;
}

//
// Process each received byte and add it to the parser buffer.
// Finalize the sentence when a newline is detected.
//
static void process_received_byte(NMEAParser* parser, char byte) {
    // If starting a new sentence, only accept if the byte is '$'
    if (parser->buffer_index == 0) {
        if (byte == '$') {
            parser->buffer[parser->buffer_index++] = byte;
        }
        return;
    }
    
    // Prevent buffer overflow
    if (parser->buffer_index >= NMEA_MAX_LENGTH - 1) {
        reset_nmea_parser(parser);
        return;
    }
    
    // Append the byte to the buffer
    parser->buffer[parser->buffer_index++] = byte;
    
    // If we see a newline, assume the sentence is complete.
    if (byte == '\n') {
        // Null-terminate the string.
        parser->buffer[parser->buffer_index] = '\0';
        parser->sentence_complete = true;
    }
}

//
// Helper: parse a GPGGA sentence and extract key fields.
// This function makes a temporary copy of the sentence to tokenize it.
// The fields are assumed to be in the following positions:
// Field 0: "$GPGGA"
// Field 1: UTC time
// Field 2: Latitude
// Field 3: N/S
// Field 4: Longitude
// Field 5: E/W
// Field 9: Altitude
//
static bool parse_gpgga_sentence(const char *sentence, ParsedNMEA *parsed) {
    // Create a temporary copy of the sentence for tokenizing.
    char temp[128];
    strncpy(temp, sentence, sizeof(temp));
    temp[sizeof(temp) - 1] = '\0';
    
    // Use strtok to split by comma.
    char *token;
    int fieldIndex = 0;
    token = strtok(temp, ",");
    while(token != NULL) {
        switch(fieldIndex) {
            case 1: // UTC time
                strncpy(parsed->utc_time, token, sizeof(parsed->utc_time));
                parsed->utc_time[sizeof(parsed->utc_time)-1] = '\0';
                break;
            case 2: // Latitude
                strncpy(parsed->latitude, token, sizeof(parsed->latitude));
                parsed->latitude[sizeof(parsed->latitude)-1] = '\0';
                break;
            case 3: // Latitude direction (N/S)
                strncpy(parsed->lat_dir, token, sizeof(parsed->lat_dir));
                parsed->lat_dir[sizeof(parsed->lat_dir)-1] = '\0';
                break;
            case 4: // Longitude
                strncpy(parsed->longitude, token, sizeof(parsed->longitude));
                parsed->longitude[sizeof(parsed->longitude)-1] = '\0';
                break;
            case 5: // Longitude direction (E/W)
                strncpy(parsed->lon_dir, token, sizeof(parsed->lon_dir));
                parsed->lon_dir[sizeof(parsed->lon_dir)-1] = '\0';
                break;
            case 9: // Altitude
                strncpy(parsed->altitude, token, sizeof(parsed->altitude));
                parsed->altitude[sizeof(parsed->altitude)-1] = '\0';
                break;
            default:
                break;
        }
        token = strtok(NULL, ",");
        fieldIndex++;
    }
    // Check that we got the mandatory fields.
    if (strlen(parsed->utc_time) == 0 ||
        strlen(parsed->latitude) == 0 ||
        strlen(parsed->longitude) == 0)
        return false;
    
    return true;
}

//
// Read from the GPS RX buffer, process bytes, and when a complete sentence
// is received, parse out key fields and transmit a concise message.
//
static void gps_read(prog_state_t *ps) {
    if (!platform_usart_gps_rx_busy() && ps->rx_desc.compl_info.data_len > 0) {
        uint16_t rx_len = ps->rx_desc.compl_info.data_len;
        for (uint16_t i = 0; i < rx_len; i++) {
            process_received_byte(&ps->nmea_parser, ps->rx_desc_buf[i]);
            
            // When a complete sentence is detected:
            if (ps->nmea_parser.sentence_complete) {
                if (is_valid_nmea_sentence(ps->nmea_parser.buffer)) {
                    ParsedNMEA parsed;
                    // Clear parsed structure fields
                    memset(&parsed, 0, sizeof(parsed));
                    if (parse_gpgga_sentence(ps->nmea_parser.buffer, &parsed)) {
                        // Prepare a concise message with key fields.
                        // Example format: "Time:081512.00, Lat:1437.82800N, Lon:12101.34403E, Alt:55.3"
                        snprintf(ps->tx_buf, sizeof(ps->tx_buf),
                                 "(%s,%s%s,%s%s,%s)\r\n",
                                 parsed.utc_time,
                                 parsed.latitude, parsed.lat_dir,
                                 parsed.longitude, parsed.lon_dir,
                                 parsed.altitude);
                        ps->tx_desc[0].buf = ps->tx_buf;
                        ps->tx_desc[0].len = strlen(ps->tx_buf);
                        platform_usart_cdc_tx_async(&ps->tx_desc[0], 1);
                    }
                }
                // Reset parser for next sentence.
                reset_nmea_parser(&ps->nmea_parser);
            }
        }
        // Clear RX buffer and restart reception.
        memset(ps->rx_desc_buf, 0, sizeof(ps->rx_desc_buf));
        platform_usart_gps_rx_async(&ps->rx_desc);
    }
}

//
// Main loop function.
//
static void prog_loop_one(prog_state_t *ps) {
    platform_do_loop_one();
    gps_read(ps);
}

//
// Main entry point.
//
int main(void) {
    prog_state_t ps;
    prog_setup(&ps);
    
    for (;;) {
        prog_loop_one(&ps);
    }
    return 1;
}
