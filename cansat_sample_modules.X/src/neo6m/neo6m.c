#include "neo6m.h"
#include "sercom0_usart.h"
#include "stdio.h"
#include "../dmac/dmac_transmit.h"
#include "../usb_serial/usb_serial.h"

#define RX_FRAME_SIZE 32 // number of bytes that DMA needs to read before it runs the callback function
#define MAX_NMEA_SENTENCE_SIZE 120  // extended NMEA sentence size
#define DMA_RX_CHANNEL DMAC_CHANNEL_2

static char gpgga_buffer[MAX_NMEA_SENTENCE_SIZE];  
static char dma_buffer[RX_FRAME_SIZE];
static int gps_index = 0;
static int capture_active = 0;  // Flag to track if we are capturing a GPGGA sentence
static const char gpgga_prefix[] = "$GPGGA";
static int partial_match_index = 0;  // Tracks partial "$GPGGA" match

// Structure to hold the parsed_gpgga key fields from a GPGGA sentence
typedef struct {
    char utc_time[11];    // e.g., "081512.00"
    char latitude[16];    // e.g., "1437.82800"
    char lat_dir[2];      // e.g., "N"
    char longitude[16];   // e.g., "12101.34403"
    char lon_dir[2];      // e.g., "E"
    char altitude[10];    // e.g., "55.3"
} ParsedNMEA;

static void ReadBytesCycle(DMAC_TRANSFER_EVENT event, uintptr_t contextHandle);
static void GPS_PollData(void);
static bool GPS_ParseGPGGA(const char *sentence);

static ParsedNMEA parsed_gpgga;

void GPS_Initialize( void ) {
    SERCOM0_USART_Initialize(9600);
    // <insert PORT config here>;
    PORT_SEC_REGS->GROUP[0].PORT_PINCFG[5] = 0x1U; // you only need the RX pin
    PORT_SEC_REGS->GROUP[0].PORT_PMUX[2] |= 0x20U;
    // Register DMA callback function (ReadBytesCycle function executes everytime to read 32 bytes in background)
    DMAC_ChannelCallbackRegister(DMA_RX_CHANNEL, ReadBytesCycle, 0);
    // start DMA cyclic transfer:
    GPS_PollData();
}

// Start a DMA receive transfer (polling 32 bytes in background)
static void GPS_PollData(void) {
    while (DMAC_ChannelIsBusy(DMA_RX_CHANNEL)) {
        // Wait for DMA to finish
    }
    DMAC_ChannelTransfer(DMA_RX_CHANNEL, (const void *)&SERCOM0_REGS->USART_INT.SERCOM_DATA, dma_buffer, RX_FRAME_SIZE);
}

void GPS_DebugPrint(void)
{
    char buf[128];
    snprintf(buf, sizeof(buf),
        "GPS:(%s,%s%s,%s%s,%s)\r\n",
        parsed_gpgga.utc_time,
        parsed_gpgga.latitude, parsed_gpgga.lat_dir,
        parsed_gpgga.longitude, parsed_gpgga.lon_dir,
        parsed_gpgga.altitude
    );
    USBSerial_Write(buf);
}


static bool GPS_ParseGPGGA(const char *sentence) {
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
                strncpy(parsed_gpgga.utc_time, token, sizeof(parsed_gpgga.utc_time));
                parsed_gpgga.utc_time[sizeof(parsed_gpgga.utc_time)-1] = '\0';
                break;
            case 2: // Latitude
                strncpy(parsed_gpgga.latitude, token, sizeof(parsed_gpgga.latitude));
                parsed_gpgga.latitude[sizeof(parsed_gpgga.latitude)-1] = '\0';
                break;
            case 3: // Latitude direction (N/S)
                strncpy(parsed_gpgga.lat_dir, token, sizeof(parsed_gpgga.lat_dir));
                parsed_gpgga.lat_dir[sizeof(parsed_gpgga.lat_dir)-1] = '\0';
                break;
            case 4: // Longitude
                strncpy(parsed_gpgga.longitude, token, sizeof(parsed_gpgga.longitude));
                parsed_gpgga.longitude[sizeof(parsed_gpgga.longitude)-1] = '\0';
                break;
            case 5: // Longitude direction (E/W)
                strncpy(parsed_gpgga.lon_dir, token, sizeof(parsed_gpgga.lon_dir));
                parsed_gpgga.lon_dir[sizeof(parsed_gpgga.lon_dir)-1] = '\0';
                break;
            case 9: // Altitude
                strncpy(parsed_gpgga.altitude, token, sizeof(parsed_gpgga.altitude));
                parsed_gpgga.altitude[sizeof(parsed_gpgga.altitude)-1] = '\0';
                break;
            default:
                break;
        }
        token = strtok(NULL, ",");
        fieldIndex++;
    }
    // Check that we got the mandatory fields.
    if (strlen(parsed_gpgga.utc_time) == 0 ||
        strlen(parsed_gpgga.latitude) == 0 ||
        strlen(parsed_gpgga.longitude) == 0)
        return false;
    
    return true;
}


// DMA read cyclic function (the callback function)
static void ReadBytesCycle(DMAC_TRANSFER_EVENT event, uintptr_t contextHandle) {
    for (int i = 0; i < RX_FRAME_SIZE; i++) {
        char c = dma_buffer[i];

        // Handle cases where "$GPGGA" is split across DMA reads
        if (!capture_active) {
            if (c == gpgga_prefix[partial_match_index]) {
                partial_match_index++;
                if (partial_match_index == strlen(gpgga_prefix)) {
                    // Found complete "$GPGGA", start capturing
                    capture_active = 1;
                    gps_index = 0;
                    partial_match_index = 0;
                }
            } else {
                // Reset partial match if the prefix is not $GPGGA
                partial_match_index = 0;
            }
        }

        if (capture_active) {
            gpgga_buffer[gps_index++] = c;

            if (gps_index >= MAX_NMEA_SENTENCE_SIZE - 1) {
                // Prevent buffer overflow
                gps_index = 0;
                capture_active = 0;
                partial_match_index = 0;
            }

            if (c == '\n') {
                // End of sentence, process it
                gpgga_buffer[gps_index] = '\0';  // Null-terminate
                GPS_ParseGPGGA(gpgga_buffer);
                gps_index = 0;
                capture_active = 0;
                partial_match_index = 0;
            }
        }
    }
    GPS_PollData(); // restart polling cycle
}