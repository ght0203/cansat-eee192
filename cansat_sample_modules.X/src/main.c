#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "clock/clock.h"
#include "delay_timer/delay_timer.h"
#include "usb_serial/usb_serial.h"
#include "bme_280/bme280.h"
#include "dmac/dmac_transmit.h"
#include "pms7003/pms7003.h"
#include "hc12/hc12.h"
#include "neo6m/neo6m.h"
/*
 * 
 */

/* Useful debug commands
    PORT_SEC_REGS->GROUP[0].PORT_DIRSET = (1 << 15);
    PORT_SEC_REGS->GROUP[0].PORT_OUTTGL = (1 << 15);
    PORT_SEC_REGS->GROUP[0].PORT_OUTSET = (1 << 15);
     */

const char debug_str[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.\r\n";



int main() {
    PORT_SEC_REGS->GROUP[0].PORT_DIRSET = (1 << 15);
    CLOCK_Initialize();
    DMAC_Initialize(); // Direct memory access controller
    DelayTimer_Initialize();
    USBSerial_Initialize(38500); // BAUD Rate 38500
    SPI_BME280_Initialize();
    PMS_Initialize(); // also begin reading PMS bytes in background
    HC12_Initialize();
    GPS_Initialize();
    
    USBSerial_Write("\033c");  // clear terminal
    uint16_t counter = 0;
    while (true) {
        // PMS DATA ---------------------------------
        delay_ms(1000);
        // PMS_RawBytes(); // used to print raw bytes read for debugging only
        char out[100];  // Buffer to hold the formatted string
        uint16_t pm1, pm10, pm2_5;
        pm1 = PMS_GetDataPM1();
        pm10 = PMS_GetDataPM10();  
        pm2_5 = PMS_GetDataPM2_5();
        sprintf(out, "PM1: %u, PM2.5: %u, PM10: %u \r\n", pm1, pm2_5, pm10);
        USBSerial_Write(out);
        
        // BME280 DATA ---------------------------------
        float temp = SPI_BME280_GetTemperature();
        snprintf(out, sizeof(out), "BME 280 Temp: %.2f\r\n", temp);
        USBSerial_Write(out);
        USBSerial_Write(debug_str);
        
        // Testing HC12 TX --------------------------------
        HC12Serial_Write(debug_str);
        
        // Debug ----------------------------------------
        counter++;
        char counter_str[20];
        snprintf(counter_str, sizeof(counter_str), "Cycle Count: %d\r\n", counter);
        USBSerial_Write(counter_str);

        // GPS -------------------------------------------
        GPS_DebugPrint();
    }
    return (EXIT_SUCCESS);
}