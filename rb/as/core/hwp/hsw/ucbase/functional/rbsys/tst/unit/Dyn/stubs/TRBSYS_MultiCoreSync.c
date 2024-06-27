#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"
#include "RBSYS_CpuInfo.h"

#include "RBSYS_MultiCoreSync.h"
#include "RBSYS_MultiCoreSyncIntern.h"
#include "TRBSYS_MultiCoreSync.h"

#if (RBFS_MCORE == RBFS_MCORE_ON)
  RBSYS_MULTICORESYNC_DEFINE_SYNCPHASES_LRAM(RBSYS_StartupSync, RBSYS_MaxNumberOfStartupSyncPhases);
  void RBSYS_SyncBarrier(const RBSYS_SyncPhaseCounter_t* syncphases, uint8 phase)
  {
    (syncphases->ptr[RBSYS_getCoreID()][phase])++;
  }

  void RBSYS_StartupSyncBarrier(RBSYS_StartupSyncPhases_t phase)
  {
    RBSYS_SyncBarrier(&RBSYS_StartupSync, phase);
  }

  uint8 TRBSYS_getStartupSyncPhaseCounter(uint8 phase)
  {
    return RBSYS_StartupSync.ptr[RBSYS_getCoreID()][phase];
  }

#else
  #define RBSYS_SyncBarrier(syncphases, phase)
#endif