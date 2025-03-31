#ifndef PMS_7003_H
#define	PMS_7003_H
#include <xc.h>
#ifdef	__cplusplus
extern "C" {
#endif

void PMS_Initialize( void );
uint16_t PMS_GetDataPM1(void);
uint16_t PMS_GetDataPM10(void);
uint16_t PMS_GetDataPM2_5(void);
void PMS_RawBytes(void); // used for debugging


#ifdef	__cplusplus
}
#endif

#endif	/* PMS_7003_H */

