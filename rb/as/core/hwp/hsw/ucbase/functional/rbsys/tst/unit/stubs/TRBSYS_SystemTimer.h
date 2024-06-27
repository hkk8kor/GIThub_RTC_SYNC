#ifndef TRBSYS_SYSTEMTIMER_H__
#define TRBSYS_SYSTEMTIMER_H__

#include "RBSYS_Config.h"


#include "TRBSYS_uCRegisters.h"

extern void TRBSYS_setSynctimeTickCtr(uint32 nValue);
extern void TRBSYS_setRealtimeTickCtr(uint32 nValue);
extern void TRBSYS_SetTimeInUsec(uint32 value);
extern uint32 TRBSYS_GetTimeInUsec(void);
extern void TRBSYS_RealtimeTickCtrAddTicks(uint32 value);

#endif
