#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"

#include "RBSYS_MultiCoreSync.h"
#include "RBSYS_MultiCoreSyncIntern.h"
#include "TRBSYS_GuardConfig.h"
#include "RBSYS_CpuInfo.h"

#if (RBFS_MCORE == RBFS_MCORE_ON)
  RBSYS_MULTICORESYNC_DEFINE_SYNCPHASES_LRAM(RBSYS_StartupSync, RBSYS_MaxNumberOfStartupSyncPhases);

  uint32 TRBSYS_InitMultiCoreSync_cnt[RB_NUM_CORES];
  void RBSYS_InitMultiCoreSync(void)
  {
    int coreID = RBSYS_getCoreID();

    TRBSYS_InitMultiCoreSync_cnt[coreID]++;

    /* RBSYS_InitMultiCoreSync() must be called after RBSYS_BasicGuardInit() */

    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
      SWT_EvalEq(TRBSYS_setCoreSPID2SafeSPID_cnt[coreID], 1);
      SWT_EvalEq(TRBSYS_PBUSGuardInit_ForPEGuard_cnt[coreID], 1);
      SWT_EvalEq(TRBSYS_PEGuardInit_cnt[coreID], 1);
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      SWT_EvalEq(TRBSYS_LRAMGuardInit_cnt[coreID], 1);
    #endif
  }

  void RBSYS_SyncBarrier(const RBSYS_SyncPhaseCounter_t* syncphases, uint8 phase)
  {
    int coreID = RBSYS_getCoreID();    /* RBSYS_InitMultiCoreSync() must be called before RBSYS_SyncBarrier()
    * RBSYS_InitMultiCoreSync() is called once before HWBistEval and once afterwards */
    if(phase == RBSYS_AfterStartPE2)
    {
      SWT_EvalEq(TRBSYS_InitMultiCoreSync_cnt[coreID], 1);
    }
    else
    {
      SWT_EvalEq(TRBSYS_InitMultiCoreSync_cnt[coreID], 2);
    }

    syncphases->ptr[RBSYS_getCoreID()][phase]++;
  }

  void RBSYS_StartupSyncBarrier(RBSYS_StartupSyncPhases_t phase)
  {
    RBSYS_SyncBarrier(&RBSYS_StartupSync, phase);
  }

#else
  #define RBSYS_SyncBarrier(syncphases, phase)
#endif
