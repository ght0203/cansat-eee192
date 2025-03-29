#ifndef SERCOM3_USART_H // Guards against multiple inclusion
#define SERCOM3_USART_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <xc.h>
#include "../usart_common.h"

// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************

size_t SERCOM3_USART_Write(uint8_t* pWrBuffer, const size_t size );
size_t SERCOM3_USART_Read(uint8_t* pRdBuffer, const size_t size);
size_t SERCOM3_USART_ReadCountGet(void);
void SERCOM3_USART_Initialize( void );
bool SERCOM3_USART_TransmitComplete( void );
size_t SERCOM3_USART_WriteFreeBufferCountGet(void);
void __attribute__((used)) SERCOM3_USART_InterruptHandler( void );

// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END

#endif //SERCOM3_USART_H
