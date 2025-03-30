/* 
 * File:   usart.h
 * Author: WX-78
 *
 * Created on March 30, 2025, 12:09 PM
 */

#ifndef USB_SERIAL_H
#define	USB_SERIAL_H
#include <xc.h>
#ifdef	__cplusplus
extern "C" {
#endif

void USBSerial_Initialize( void );
void USBSerial_Write(char* message);
uint8_t USBSerial_Read(char* outputBuffer, uint8_t length);

#ifdef	__cplusplus
}
#endif

#endif	/* USB_SERIAL_H */

