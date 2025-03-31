#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "clock/clock.h"
#include "delay_timer/delay_timer.h"
#include "usb_serial/usb_serial.h"
#include "bme_280/bme280.h"
#include "dmac/dmac_transmit.h"
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
    CLOCK_Initialize();
    DMAC_Initialize(); // Direct memory access controller
    DelayTimer_Initialize();
    USBSerial_Initialize(38500); // BAUD Rate 38500
    SPI_BME280_Initialize();
    
    USBSerial_Write("\033c");  
    while (true) {
        delay_ms(1000);
        char buffer[128];
        snprintf(buffer, sizeof(buffer), "Temp: %.2fC\r\nPressure: %2f Pa | Humidity: %.2f%% | Altitude: %.2f m above sea\r",
                 SPI_BME280_GetTemperature(),
                 SPI_BME280_GetPressure(),
                 SPI_BME280_GetHumidity(),
                 SPI_BME280_GetAltitude(53, 99963.687500));
        USBSerial_Write(buffer);
        USBSerial_Write("\r\n");
    }
    return (EXIT_SUCCESS);
}