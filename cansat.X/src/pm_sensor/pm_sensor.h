/* 
 * File:   pm_sensor.h
 * Author: WX-78
 *
 * Created on March 29, 2025, 11:24 AM
 */

#ifndef PM_SENSOR_H
#define	PM_SENSOR_H

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>    
#include <stdio.h>
#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
void PMSUsart_Read(char *message, uint8_t length);
void PMS_Initialize(void);
void PMSUsart_DebugRead(void);
void PMSUsart_PassiveMode(void);
uint16_t PMS_GetDataPM10(void);
uint16_t PMS_GetDataPM2_5(void);
uint16_t PMS_GetDataPM1(void);

#ifdef	__cplusplus
}
#endif

#endif	/* PM_SENSOR_H */

