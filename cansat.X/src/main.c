#include <stdio.h>
#include <stdlib.h>
#include "clock/clock.h"
#include "hc12/hc12.h"
#include "usb_serial/usb_serial.h"
#include "delay_timer/delay_timer.h"
#include "pm_sensor/pm_sensor.h"
/*
 * 
 */

/* Useful debug commands
    PORT_SEC_REGS->GROUP[0].PORT_DIRSET = (1 << 15);
    PORT_SEC_REGS->GROUP[0].PORT_OUTTGL = (1 << 15);
     */

int main() {
    CLOCK_Initialize();
    USBSerial_Initialize();
    HC12_Initialize();
    PMS_Initialize();
    DelayTimer_Initialize();
    PMSUsart_PassiveMode();
    
    
    
    while(true) {
        delay_ms(2000);
        
        USBSerial_Write("hello, putty \r\n");
        HC12Serial_Write("Hello, raspi \r\n");
        PMSUsart_DebugRead(); // Polls the sensor, read the raw bytes and print them to serial display
        
        uint16_t pm10 = PMS_GetDataPM10();
        uint16_t pm2_5 = PMS_GetDataPM2_5();
        USBSerial_WriteNewLine("PM10: %d ug/cm^3", pm10);
        USBSerial_WriteNewLine("PM2.5: %d ug/cm^3", pm2_5);
    }
    
    return (EXIT_SUCCESS);
}