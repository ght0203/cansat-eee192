#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "clock/clock.h"
#include "delay_timer/delay_timer.h"
#include "usb_serial/usb_serial.h"
#include "bme_280/bme280.h"
/*
 * 
 */

/* Useful debug commands
    PORT_SEC_REGS->GROUP[0].PORT_DIRSET = (1 << 15);
    PORT_SEC_REGS->GROUP[0].PORT_OUTTGL = (1 << 15);
     */

int main() {
    CLOCK_Initialize();
    DMAC_Initialize(); // Direct memory access controller
    DelayTimer_Initialize();
    USBSerial_Initialize(38500); // BAUD Rate 38500
    SPI_BME280_Initialize();
    
    
    PORT_SEC_REGS->GROUP[0].PORT_DIRSET = (1 << 15);
    USBSerial_Write("\033c");  
    while (true) {
        delay_ms(1000);
        USBSerial_Write("Temp: ");
        float T = SPI_BME280_GetTemp();
        char tempStr[20];  // Enough space for float and possible negative sign
        snprintf(tempStr, sizeof(tempStr), "%.2f", T);
        USBSerial_Write(tempStr);
        USBSerial_Write("\r\n");
    }
    return (EXIT_SUCCESS);
}