/* 
 * File:   usart.h
 * Author: WX-78
 *
 * Created on March 30, 2025, 12:09 PM
 */

#ifndef BME_280_H
#define	BME_280_H
#include <xc.h>
#ifdef	__cplusplus
extern "C" {
#endif

void SPI_BME280_Initialize( void );
void SPI_BME280_NormalMode(void);
float SPI_BME280_GetTemp(void);

#ifdef	__cplusplus
}
#endif

#endif	/* BME_280_H */

