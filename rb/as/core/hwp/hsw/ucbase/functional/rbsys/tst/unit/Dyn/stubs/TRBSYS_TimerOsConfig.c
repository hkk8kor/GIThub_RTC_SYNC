#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"

#include "RBSYS_TimerOsConfig.h"
#include "TRBSYS_TimerOsConfig.h"
#include "RBSYS_MultiCoreSyncIntern.h"
#include "TRBSYS_MultiCoreSync.h"
#include "RBSYS_CpuInfo.h"


boolean TRBSYS_SyncBarrier4SetupOsTimer[RB_NUM_CORES];
uint32 TRBSYS_SetupOsTimer_cnt[RB_NUM_CORES];
void RBSYS_SetupOsTimer(void)
{
  unsigned int coreID = RBSYS_getCoreID();

  #if (RBFS_MCORE == RBFS_MCORE_ON)
    // ensure that "RBSYS_SyncBarrier(RBSYS_OsTimerSetupFinished)" is not called before "RBSYS_SetupOsTimer"
    if (TRBSYS_getStartupSyncPhaseCounter(RBSYS_OsTimerSetupFinished) == 0)
    {
      TRBSYS_SyncBarrier4SetupOsTimer[coreID] = TRUE;
    }
  #endif

  TRBSYS_SetupOsTimer_cnt[coreID]++;
}


boolean TRBSYS_SyncBarrier4EnableOsTimerIRQs[RB_NUM_CORES];
uint32 TRBSYS_EnableOsTimerIRQs_cnt[RB_NUM_CORES];
void RBSYS_EnableOsTimerIRQs(void)
{
  unsigned int coreID = RBSYS_getCoreID();

  #if (RBFS_MCORE == RBFS_MCORE_ON)
    // ensure that "RBSYS_SyncBarrier(RBSYS_OsTimerSetupFinished)" is called before "RBSYS_EnableOsTimerIRQs"
    if (TRBSYS_getStartupSyncPhaseCounter(RBSYS_OsTimerSetupFinished) == 1)
    {
      TRBSYS_SyncBarrier4EnableOsTimerIRQs[coreID] = TRUE;
    }
  #endif

  TRBSYS_EnableOsTimerIRQs_cnt[coreID]++;
}
