/* 
 * File:   delay_timer.h
 * Author: WX-78
 *
 * Created on March 29, 2025, 10:33 AM
 */

#ifndef DELAY_TIMER_H
#define	DELAY_TIMER_H

#include <xc.h>
#include <stdbool.h>
#include <stddef.h>

typedef void (*TCC_CALLBACK)( uint32_t status, uintptr_t context );
typedef struct
{
    TCC_CALLBACK callback_fn;
    uintptr_t context;
} TCC_CALLBACK_OBJECT;

void DelayTimer_Initialize( void );
void delay_ms(uint16_t ms);

#ifdef	__cplusplus
extern "C" {
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* DELAY_TIMER_H */

