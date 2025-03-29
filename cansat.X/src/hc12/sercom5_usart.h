#ifndef SERCOM5_USART_H // Guards against multiple inclusion
#define SERCOM5_USART_H

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

size_t SERCOM5_USART_Write(uint8_t* pWrBuffer, const size_t size );
size_t SERCOM5_USART_Read(uint8_t* pRdBuffer, const size_t size);
size_t SERCOM5_USART_ReadCountGet(void);
void __attribute__((used)) SERCOM5_USART_InterruptHandler( void );
void SERCOM5_USART_Initialize( void );
bool SERCOM5_USART_TransmitComplete( void );
size_t SERCOM5_USART_WriteFreeBufferCountGet(void);


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif
// DOM-IGNORE-END

#endif //SERCOM5_USART_H
