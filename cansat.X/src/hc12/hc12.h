/* 
 * File:   hc12.h
 * Author: WX-78
 *
 * Created on March 28, 2025, 11:08 PM
 */

#ifndef HC12_H
#define	HC12_H

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

void HC12Serial_Write(const char *formatted_str, ...);
void HC12_Initialize(void);

#ifdef	__cplusplus
}
#endif

#endif	/* HC12_H */

