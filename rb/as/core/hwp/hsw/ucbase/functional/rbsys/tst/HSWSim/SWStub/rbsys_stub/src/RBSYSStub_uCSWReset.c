#include "RBSYS_uCResetCtrl.h"
#include "RBSYS_RAMBackupServiceIntern.h"
#include "HwModels/Memory/Hwm_RAMBackupService.h"
#include "TestEnvironment_ECMStub.h" /* TestEnv_SetErrorPinLocked */

void RBSYS_uCReset_ApplResetSkipBootBlock(void)
{
  extern int SimControl_PerformSwReset;
  RBSYS_saveBaseOSRequestToBackupRAM();
  SimControl_PerformSwReset = TRUE;
}

#if(RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
  void RBSYS_uCReset_ApplResetSkipBootBlockNoGramZeroing(void){}
#endif

#if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) \
  || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2) \
   )
  void RBSYS_uCReset_ApplResetSkipBootBlockNoLramZeroing(void){}
#endif

#if (RBFS_SysBootblockSupport == RBFS_SysBootblockSupport_ON)
  void RBSYS_uCReset_ApplResetWithBootBlock4OEM(void){}

  void RBSYS_uCReset_ApplResetWithBootBlock4RB(void){}

  void RBSYS_uCReset_ApplResetWithBootBlock(void){}
#endif

boolean RBSYS_HasPowerOnResetOccurred(void)
{
  return TRUE;
}

  #if ( (RBFS_FOTA == RBFS_FOTA_PREMIUM) || (RBFS_HswRecoveryReset == RBFS_HswRecoveryReset_Enabled) )
    void RBSYS_uCReset_SystemReset(void)
    {
      extern int SimControl_PerformSwReset;
      /*Delete Backup RAM*/
      Hwm_BackupRAM_Reset();
      /* Free Error Pin */
      TestEnv_SetErrorPinLocked(FALSE);
      SimControl_PerformSwReset = TRUE;
    }
  #endif

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) \
  )
  void RBSYS_uCReset_ClearuCVoltageMonResetFlags(void)
  {
    //So far no handling required for HSWSim
  }
#endif

void RBSYS_ClearResetFactorsAfterSafetyTests(void)
{
  //So far no handling required for HSWSim
}