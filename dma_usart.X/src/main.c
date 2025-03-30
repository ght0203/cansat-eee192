#include <stdio.h>
#include <stdlib.h>
#include "clock/clock.h"
#include "delay_timer/delay_timer.h"
#include "usb_serial/usb_serial.h"
/*
 * 
 */

/* Useful debug commands
    PORT_SEC_REGS->GROUP[0].PORT_DIRSET = (1 << 15);
    PORT_SEC_REGS->GROUP[0].PORT_OUTTGL = (1 << 15);
     */

int main() {
    CLOCK_Initialize();
    DelayTimer_Initialize();
    USBSerial_Initialize();
    
    
    while(true) {
        delay_ms(1000);
        USBSerial_Write("Serial Read: ");
        delay_ms(10);  
        char test[3] = {};
        USBSerial_Read(test, 3);
        USBSerial_Write(test);
        USBSerial_Write("\r\n");
    }
    
    return (EXIT_SUCCESS);
}