#ifndef TRBSYS_GUARDCONFIG_H__
#define TRBSYS_GUARDCONFIG_H__

#include "RBSYS_Config.h"

#include "TRBSYS_Helper.h"

extern uint32 TRBSYS_FSW_FinalGuardInit_cnt[RB_NUM_CORES];
extern TRBSYS_Callback_t TRBSYS_setCoreSPID2SafeSPID_Callback;
extern uint32 TRBSYS_setCoreSPID2SafeSPID_cnt[RB_NUM_CORES];
extern uint32 TRBSYS_PBUSGuardInit_ForPEGuard_cnt[RB_NUM_CORES];
extern uint32 TRBSYS_PEGuardInit_cnt[RB_NUM_CORES];
extern uint32 TRBSYS_PBUSGuardInit_cnt[RB_NUM_CORES];
extern uint32 TRBSYS_HBusGuardInit_cnt[RB_NUM_CORES];
extern uint32 RBSYS_EnhancedGuardInit_cnt[RB_NUM_CORES];
extern uint32 TRBSYS_LRAMGuardInit_cnt[RB_NUM_CORES];

#endif
