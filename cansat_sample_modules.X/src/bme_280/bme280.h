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
void SPI_BME280_SetMode(void);
float SPI_BME280_GetTemperature(void);
float SPI_BME280_GetHumidity(void);
float SPI_BME280_GetPressure(void);
float SPI_BME280_GetAltitude(float reference_altitude, float reference_pressure);

#ifdef	__cplusplus
}
#endif

#endif	/* BME_280_H */

