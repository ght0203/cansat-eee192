/* 
 * File:   usart.h
 * Author: WX-78
 *
 * Created on March 30, 2025, 12:09 PM
 */

 #ifndef SERCOM0_USART_H
 #define SERCOM0_USART_H
 #include <xc.h>
 #ifdef	__cplusplus
 extern "C" {
 #endif
 
 void SERCOM0_USART_Initialize( uint32_t baud_rate );
 
 
 #ifdef	__cplusplus
 }
 #endif
 
 #endif	/* SERCOM0_USART_H */
 
 