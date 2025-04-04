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

void USBSerial_Initialize( uint32_t baud_rate );
void USBSerial_Write(const char* message);

// Reads up to maxLength bytes from the input buffer into outputBuffer.
// The function stops when either the unread buffer is empty or maxLength bytes have been read.
uint8_t USBSerial_Read(char* outputBuffer, uint8_t maxLength);

#ifdef	__cplusplus
}
#endif

#endif	/* USB_SERIAL_H */

