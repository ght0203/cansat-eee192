#ifndef SERCOM4_I2C_H
#define SERCOM4_I2C_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/* This section lists the other files that are included in this file.
*/

#include "sercom_i2c_master_common.h"

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

/*
 * The following functions make up the methods (set of possible operations) of
 * this interface.
 */

void SERCOM4_I2C_Initialize(void);

bool SERCOM4_I2C_Read(uint16_t address, uint8_t* rdData, uint32_t rdLength);

bool SERCOM4_I2C_Write(uint16_t address, uint8_t* wrData, uint32_t wrLength);

bool SERCOM4_I2C_WriteRead(uint16_t address, uint8_t* wrData, uint32_t wrLength, uint8_t* rdData, uint32_t rdLength);

bool SERCOM4_I2C_IsBusy(void);

SERCOM_I2C_ERROR SERCOM4_I2C_ErrorGet(void);

void SERCOM4_I2C_CallbackRegister(SERCOM_I2C_CALLBACK callback, uintptr_t contextHandle);

bool SERCOM4_I2C_TransferSetup(SERCOM_I2C_TRANSFER_SETUP* setup, uint32_t srcClkFreq );


void SERCOM4_I2C_TransferAbort( void );

bool SERCOM4_I2C_BusScan(uint16_t start_addr, uint16_t end_addr, void* pDevicesList, uint8_t* nDevicesFound);


// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
}
#endif
// DOM-IGNORE-END

#endif /* SERCOM4_I2C_H */
