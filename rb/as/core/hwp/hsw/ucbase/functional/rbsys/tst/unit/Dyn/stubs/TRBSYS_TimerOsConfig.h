#ifndef TRBSYS_TIMEROSCONFIG_H__
#define TRBSYS_TIMEROSCONFIG_H__


#include "RBSYS_Config.h"


extern boolean TRBSYS_SyncBarrier4SetupOsTimer[RB_NUM_CORES];
extern uint32 TRBSYS_SetupOsTimer_cnt[RB_NUM_CORES];

extern boolean TRBSYS_SyncBarrier4EnableOsTimerIRQs[RB_NUM_CORES];
extern uint32 TRBSYS_EnableOsTimerIRQs_cnt[RB_NUM_CORES];


#endif
