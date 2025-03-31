#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "clock/clock.h"
#include "delay_timer/delay_timer.h"
#include "usb_serial/usb_serial.h"
#include "bme_280/bme280.h"
#include "dmac/dmac_transmit.h"
#include "pms7003/pms7003.h"
/*
 * 
 */

/* Useful debug commands
    PORT_SEC_REGS->GROUP[0].PORT_DIRSET = (1 << 15);
    PORT_SEC_REGS->GROUP[0].PORT_OUTTGL = (1 << 15);
    PORT_SEC_REGS->GROUP[0].PORT_OUTSET = (1 << 15);
     */

int main() {
    PORT_SEC_REGS->GROUP[0].PORT_DIRSET = (1 << 15);
    /* ----------COMMENT OUT UNUSED PERIPHERALS TO PREVENT INFINITE READ/WRITE LOOPS ------*/
    CLOCK_Initialize();
    DMAC_Initialize(); // Direct memory access controller
    DelayTimer_Initialize();
    USBSerial_Initialize(38500); // BAUD Rate 38500
    // SPI_BME280_Initialize();
    PMS_Initialize();
    
    USBSerial_Write("\033c");  // clear terminal
    while (true) {
        delay_ms(1000);
        PMS_RawBytes(); // used to print raw bytes read for debugging
        char out[100];  // Buffer to hold the formatted string
        uint16_t pm1, pm10, pm2_5;
        pm1 = PMS_GetDataPM1();
        pm10 = PMS_GetDataPM10();  // Corrected function call for PM10
        pm2_5 = PMS_GetDataPM2_5();
        sprintf(out, "PM1: %u, PM2.5: %u, PM10: %u \r\n", pm1, pm2_5, pm10);
        
        USBSerial_Write(out);
    }
    return (EXIT_SUCCESS);
}