#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"

#include "RBSYS_GuardConfigCommon.h"
#include "TRBSYS_GuardConfig.h"
#include "RBSYS_CpuInfo.h"
#include "RBSYS_Subsystem.h"

TRBSYS_Callback_t TRBSYS_setCoreSPID2SafeSPID_Callback = NULL;
uint32 TRBSYS_setCoreSPID2SafeSPID_cnt[RB_NUM_CORES];

#if(RBFS_uCFamily != RBFS_uCFamily_STMStellar)
  void RBSYS_setCoreSPID2SafeSPID(void)
  {
    if(TRBSYS_setCoreSPID2SafeSPID_Callback != NULL)
    {
      TRBSYS_setCoreSPID2SafeSPID_Callback();
    }
    TRBSYS_setCoreSPID2SafeSPID_cnt[RBSYS_getCoreID()]++;
  }
 
  uint32 TRBSYS_PBUSGuardInit_ForPEGuard_cnt[RB_NUM_CORES];
  void RBSYS_PBUSGuardInit_ForPEGuard(void){
    TRBSYS_PBUSGuardInit_ForPEGuard_cnt[RBSYS_getCoreID()]++;
  }
  uint32 TRBSYS_PEGuardInit_cnt[RB_NUM_CORES];
  void RBSYS_PEGuardInit(void){
    TRBSYS_PEGuardInit_cnt[RBSYS_getCoreID()]++;
  }
#else
  #warning("Set Core SPID concept is missing for Stellar.")
  uint32 TRBSYS_LRAMGuardInit_cnt[RB_NUM_CORES];
  void RBSYS_LRAMGuardInit(void)
  {
    TRBSYS_LRAMGuardInit_cnt[RBSYS_getCoreID()]++;
  }
#endif

uint32 RBSYS_EnhancedGuardInit_cnt[RB_NUM_CORES];
void RBSYS_EnhancedGuardInit(void)
{
  RBSYS_EnhancedGuardInit_cnt[RBSYS_getCoreID()]++;
}

uint32 TRBSYS_FSW_FinalGuardInit_cnt[RB_NUM_CORES];
void RBSYS_PRC_FSW_FinalGuard_Init(void)
{
  int coreID = RBSYS_getCoreID();
  TRBSYS_FSW_FinalGuardInit_cnt[coreID]++;
}

#if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
  uint32 TRBSYS_PBUSGuardInit_cnt[RB_NUM_CORES];
  void RBSYS_PBUSGuardInit(void)
  {
    TRBSYS_PBUSGuardInit_cnt[RBSYS_getCoreID()]++;
  }

  uint32 TRBSYS_HBusGuardInit_cnt[RB_NUM_CORES];
  void RBSYS_HBusGuardInit(void)
  {
    TRBSYS_HBusGuardInit_cnt[RBSYS_getCoreID()]++;
  }
#endif

