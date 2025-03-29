/* 
 * File:   usb_cdc.h
 * Author: WX-78
 *
 * Created on March 28, 2025, 11:08 PM
 */

#ifndef USB_CDC_H
#define	USB_CDC_H

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>    
#include <stdio.h>
#include <xc.h>
#include <string.h>
#include <stdarg.h>

#ifdef	__cplusplus
extern "C" {
#endif

void USBSerial_Initialize(void);
void USBSerial_Write(const char *formatted_str, ...);
void USBSerial_Read(char *message, uint8_t length);
void USBSerial_ReadUntil(char *message, char endchar);
void USBSerial_ReadNewline(char *message);
void USBSerial_WriteNewLine(const char *formatted_str, ...);

#ifdef	__cplusplus
}
#endif

#endif	/* USB_CDC_H */

