/* 
 * File:   usart.h
 * Author: WX-78
 *
 * Created on March 30, 2025, 12:09 PM
 */

#ifndef SCD41_H
#define	SCD41_H
#include <xc.h>
#ifdef	__cplusplus
extern "C" {
#endif

    void SCD41_Initialize(void);
    float SCD41_ReadCO2(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SCD41_H */
