/**
 * @ingroup RBSYS
 * @{
 *
 * \file
 * \brief Unit test for RBSYS_uCReset
 *
 * This unit test checks the correct behaviour of reset functions in RBSYS_uCReset.
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "SwTest_Global.h"          // for SWT functionality
#include "RBSYS_Config.h"          // for RBFS_uCFamily

/* used interfaces */
#include "TRBSYS_TestInjection.h"
#include "RBSYS_BBFSW_StartupServices.h"
#include "TRBSYS_BBFSW_StartupServices.h"
#include "TRBSYS_RAMBackupServiceIntern.h"
#include "RBSYS_PlantStartupCtrl.h"
#include "TRBSYS_uCRegisters.h"
#include "RBSYS_ResetSync.h"
#include "RBSYS_CpuInfo.h"
#include "TRBSYS_CpuInfo.h"
#include "TRBSYS_Intrinsics.h"
#include "RBSYS_uCResetInfo.h"
#include "RBSYS_uCResetInternal.h"
#include "TRBSYS_uCReset.h"
#include "TRBSYS_LocksHelper.h"


static void TRBSYS_uCReset_CheckAllResetFlagsCleared(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    SWT_EvalEq(RBSYS_RESFC, RBSYS_RESET_FLAG_SW_SYSTEM_0 | RBSYS_RESET_FLAG_SW_APPLICATION_0 | RBSYS_RESET_FLAG_TERMINAL);
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    SWT_EvalEq(MC_RGM_PER.DES, RBSYS_RESET_DEST_FLAG_RESETPIN_A | RBSYS_RESET_DEST_FLAG_SW_RESET);
    SWT_EvalEq(MC_RGM_PER.FES, RBSYS_RESET_FUNC_FLAG_SW_RESET);
  #endif
}





#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )

  /* realized interfaces */
  #include "TRBSYS_uCReset_Adaptor.h"

  #if( (RBFS_FOTA == RBFS_FOTA_PREMIUM) || (RBFS_HswRecoveryReset == RBFS_HswRecoveryReset_Enabled) )
    /**
      * \Reference
      *  RBSYS_uCReset_SystemReset, Gen_SWCS_HSW_uC_Base_SYS-315
      *
      * \Purpose
      *  Verification of function RBSYS_uCReset_SystemReset
      *
      * \Sequence
      *  Call function under test
      *
      * \ExpectedResult
      * Only core local interrupts are disabled and no common lock was entered
      * SW System / SW Application / Terminal Reset flags are cleared (will be set again once reset is executed)
      * Registers for System Reset are set
      * An endless loop is entered for waiting for reset
      */  
    SWTEST void TRBSYS_uCReset_SystemReset(void)
    {
      // call function under test
      RBSYS_uCReset_SystemReset();

      // core local interrupts are disabled
      SWT_Eval(TRBSYS_CoreLocalLock.fnc_call_cnt > 0);
      SWT_Eval(TRBSYS_CoreLocalLock.nest_cnt > 0);
      // no global lock was entered
      SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 0);

      // all flags cleared
      TRBSYS_uCReset_CheckAllResetFlagsCleared();

      // registers for system reset are set
      #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
        SWT_EvalEq(BSEQ0CTL, 0x1);       //< HWBISTEXE = 1, execute Field Bist after next SysRes2
        SWT_EvalEq(SWSRESA0, 0x1);       //< System Reset 2 triggered
      #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
        SWT_EvalEq(SYS0BSEQ0CTL, 0x0);   //< Execute HWBist according to Flash Option Byte
        SWT_EvalEq(SYSCTRLSWSRESA, 0x1); //< System Reset 2 triggered
      #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        SWT_EvalEq(MC_ME_PER.ModeReg.MCTL, (0xF << 28) | (0xA50F)); // destructive reset triggered
      #endif

      // function runs into endless loop that waits for reset
      SWT_Eval(TRBSYS_EndlessLoopCount > 0);
    }
  #endif


  /**
  * \Reference
  *  RBSYS_uCReset_ApplResetSkipBootBlock, Gen_SWCS_HSW_uC_Base_SYS-315, Gen_SWCS_HSW_uC_Base_SYS-330
  *
  * \Purpose
  *  Verification of function RBSYS_uCReset_ApplResetSkipBootBlock
  *
  * \Sequence
  *  Call function under test
  *
  * \ExpectedResult
  * Only core local interrupts are disabled and no common lock was entered
  * Boot parameters are set as follows:
  *    Bootblock request: RBSYS_SKIP_BOOTBLOCK
  *    Skip bootblock indication: RBSYS_SKIP_BOOTBLOCKTrigbyFSW
  * Boot parameters are stored to backup RAM
  * SW System / SW Application / Terminal Reset flags are cleared (will be set again once reset is executed)
  * Registers for application reset 1 are set with zeroing of GRAM and LRAM except for Backup RAM
  * An endless loop is entered for waiting for reset
  */
  SWTEST void TRBSYS_uCResetSkipBootBlock(void)
  {
    RBMESG_DefineMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);

    // call function under test
    RBSYS_uCReset_ApplResetSkipBootBlock();

    // FSW BURAM shall not be zeroed, as it will be interpreted in next run of Application
    SWT_EvalEq(TRBSYS_ClearFSWBackupRAM_callCount, 0);

    // core local interrupts are disabled
    SWT_Eval(TRBSYS_CoreLocalLock.fnc_call_cnt > 0);
    SWT_Eval(TRBSYS_CoreLocalLock.nest_cnt > 0);
    // no global lock was entered
    SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 0);

    // boot parameters are set
    SWT_EvalEq(RBSYS_BURAM_BB_FSW_INTERFACE.BootblockRequest, RBSYS_SKIP_BOOTBLOCK);

    // boot parameters are stored in backup RAM
    SWT_Eval(TRBSYS_saveBaseOSRequestToBackupRAM_callCount > 0);
    SWT_Eval(RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM_callcount > 0);

    // skipbootblock requester is set
    RBMESG_RcvMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);
    SWT_EvalEq(l_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32, RBSYS_SKIP_BOOTBLOCKTrigbyFSW);

    // all flags cleared
    TRBSYS_uCReset_CheckAllResetFlagsCleared();

    // registers for application reset 1 are set
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEq(SWARESA0, 0x1); // software application reset 1 is generated
      SWT_EvalEq(STAC_LM0, 0x1); // RAM initialization mode for CPU0 is enabled exluding Backup Section
    #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      SWT_EvalEq(SYSCTRLRESKCPROT0, 0xA5A5A501u); // write access to SWARESA is enabled
      SWT_EvalEq(SYSCTRLSWARESA, 0x1); // software application reset 1 is generated
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      SWT_EvalEq(MC_ME_PER.ModeReg.MCTL, (0x0 << 28) | (0xA50F)); // functional reset triggered
    #endif

    // function runs into endless loop that waits for reset
    SWT_Eval(TRBSYS_EndlessLoopCount > 0);
  }

  /**
  * \Reference
  *  RBSYS_ExecuteReset, Gen_SWCS_HSW_uC_Base_SYS-315
  *
  * \Purpose
  *  Verification of function RBSYS_ExecuteReset - defensiveness against invalid states
  *
  * \Sequence
  *  manipulate rbsys_ResetRequest (RBSYS_uCResetType_Undefined, any undefined value)
  *  Call function under test
  *  assertion shall be called, reset is not triggered
  *
  * \ExpectedResult
  *  see sequence
  */
  SWTEST void TRBSYS_ExecuteReset_InvalidDataModelState(void)
  {
    /// "defined-Undefined" Reset Type (Value 0 - to prevent malfunction by RAM zeroing)
    TRBSYS_SetUndefinedRequestedResetType();
    TRBSYS_ExecuteReset();

    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      SWT_EvalEq(SWARESA0, 0);
      SWT_EvalEq(STAC_LM0, 0);
      SWT_EvalEq(STAC_GRAM, 0);
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      SWT_EvalEq(MC_ME_PER.ModeReg.MCTL, 0);
    #endif

    // all flags cleared
    TRBSYS_uCReset_CheckAllResetFlagsCleared();


    /// undefined Reset Type
    TRBSYS_SetInvalidRequestedResetType();
    TRBSYS_ExecuteReset();
    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      SWT_EvalEq(SWARESA0, 0);
      SWT_EvalEq(STAC_LM0, 0);
      SWT_EvalEq(STAC_GRAM, 0);
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      SWT_EvalEq(MC_ME_PER.ModeReg.MCTL, 0);
    #endif

    // all flags cleared
    TRBSYS_uCReset_CheckAllResetFlagsCleared();
  }

  #if( RBFS_MCORE == RBFS_MCORE_ON )
    /**
    * \Reference
    *  RBSYS_ECMTriggerUCResetAfterCoreSync, Gen_SWCS_HSW_uC_Base_SYS-315
    *
    * \Purpose
    *  Verification of function RBSYS_ECMTriggerUCResetAfterCoreSync - defensiveness against invalid states
    *
    * \Sequence
    *  manipulate rbsys_ResetRequest (RBSYS_uCResetType_Undefined, any undefined value)
    *  Call function under test
    *  assertion shall be called, reset is not triggered
    *
    * \ExpectedResult
    *  see sequence
    */
    SWTEST void TRBSYS_ECMTriggerUCResetAfterCoreSync_InvalidDataModelState(void)
    {
      /// "defined-Undefined" Reset Type (Value 0 - to prevent malfunction by RAM zeroing)
      TRBSYS_SetUndefinedRequestedResetType();
      RBSYS_ECMTriggerUCResetAfterCoreSync();
      #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
        SWT_EvalEq(SWARESA0, 0);
        SWT_EvalEq(STAC_LM0, 0);
        SWT_EvalEq(STAC_GRAM, 0);
      #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        SWT_EvalEq(MC_ME_PER.ModeReg.MCTL, 0);
      #endif

      // all flags cleared
      TRBSYS_uCReset_CheckAllResetFlagsCleared();


      /// undefined Reset Type
      TRBSYS_SetInvalidRequestedResetType();
      RBSYS_ECMTriggerUCResetAfterCoreSync();
      #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
        SWT_EvalEq(SWARESA0, 0);
        SWT_EvalEq(STAC_LM0, 0);
        SWT_EvalEq(STAC_GRAM, 0);
      #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        SWT_EvalEq(MC_ME_PER.ModeReg.MCTL, 0);
      #endif

      // all flags cleared
      TRBSYS_uCReset_CheckAllResetFlagsCleared();
    }
  #endif


  #if(RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)

    /**
    * \Reference
    *  RBSYS_uCReset_ApplResetSkipBootBlockNoGramZeroing, Gen_SWCS_HSW_uC_Base_SYS-315, Gen_SWCS_HSW_uC_Base_SYS-330
    *
    * \Purpose
    *  Verification of function RBSYS_uCReset_ApplResetSkipBootBlockNoGramZeroing
    *
    * \Sequence
    *  Call function under test
    *
    * \ExpectedResult
    * Only core local interrupts are disabled and no common lock was entered
    * Boot parameters are set as follows:
    *    Bootblock request: RBSYS_SKIP_BOOTBLOCK
    *    Skip bootblock indication: RBSYS_SKIP_BOOTBLOCKTrigbyFSW
    * Boot parameters are stored to backup RAM
    * SW System / SW Application / Terminal Reset flags are cleared (will be set again once reset is executed)
    * Registers for application reset 1 are set with zeroing of LRAM except for Backup RAM, no zeroing of GRAM
    * An endless loop is entered for waiting for reset
    */
    SWTEST void TRBSYS_uCResetSkipBootBlockNoGramZeroing(void)
    {
      RBMESG_DefineMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);

      // call function under test
      RBSYS_uCReset_ApplResetSkipBootBlockNoGramZeroing();

      // FSW BURAM shall not be zeroed, as Reprog Driver will zero it by peforming SW System Reset
      SWT_EvalEq(TRBSYS_ClearFSWBackupRAM_callCount, 0);

      // core local interrupts are disabled
      SWT_Eval(TRBSYS_CoreLocalLock.fnc_call_cnt > 0);
      SWT_Eval(TRBSYS_CoreLocalLock.nest_cnt > 0);
      // no global lock was entered
      SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 0);

      // boot parameters are set
      SWT_EvalEq(RBSYS_BURAM_BB_FSW_INTERFACE.BootblockRequest, RBSYS_SKIP_BOOTBLOCK);

      // boot parameters are stored in backup RAM
      SWT_Eval(TRBSYS_saveBaseOSRequestToBackupRAM_callCount > 0);
      SWT_Eval(RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM_callcount > 0);

      // bootblock request is set
      RBMESG_RcvMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);
      SWT_EvalEq(l_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32, RBSYS_SKIP_BOOTBLOCKTrigbyFSW);

      // all flags cleared
      TRBSYS_uCReset_CheckAllResetFlagsCleared();

      // registers for application reset 1 are set
      SWT_EvalEq(SWARESA0, 0x1); // software application reset 1 is generated
      SWT_EvalEq(STAC_GRAM, 0x0); // no zeroing of GRAM
      SWT_EvalEq(STAC_LM0, 0x1); // RAM initialization mode for CPU0 is enabled exluding Backup Section

      // function runs into endless loop that waits for reset
      SWT_Eval(TRBSYS_EndlessLoopCount > 0);
    }

  #endif /* RBFS_RenesasP1xGRAM_ON && RBFS_uCFamily_RenesasP1x */



  #if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2))

    /**
    * \Reference
    *  RBSYS_uCReset_ApplResetSkipBootBlockNoLramZeroing, Gen_SWCS_HSW_uC_Base_SYS-315, Gen_SWCS_HSW_uC_Base_SYS-330
    *
    * \Purpose
    *  Verification of function RBSYS_uCReset_ApplResetSkipBootBlockNoLramZeroing
    *
    * \Sequence
    *  Call function under test
    *
    * \ExpectedResult
    * Only core local interrupts are disabled and no common lock was entered
    * Boot parameters are set as follows:
    *    Bootblock request: RBSYS_SKIP_BOOTBLOCK
    *    Skip bootblock indication: RBSYS_SKIP_BOOTBLOCKTrigbyFSW
    * Boot parameters are stored to backup RAM
    * SW System / SW Application / Terminal Reset flags are cleared (will be set again once reset is executed)
    * Registers for application reset 1 are set with zeroing of GRAM, no zeroing of LRAM
    * An endless loop is entered for waiting for reset
    */
    SWTEST void TRBSYS_uCResetSkipBootBlockNoLramZeroing(void)
    {
      RBMESG_DefineMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);

      // call function under test
      RBSYS_uCReset_ApplResetSkipBootBlockNoLramZeroing();

      // FSW BURAM shall not be zeroed, as Reprog Driver will zero it by peforming SW System Reset
      SWT_EvalEq(TRBSYS_ClearFSWBackupRAM_callCount, 0);

      // core local interrupts are disabled
      SWT_Eval(TRBSYS_CoreLocalLock.fnc_call_cnt > 0);
      SWT_Eval(TRBSYS_CoreLocalLock.nest_cnt > 0);
      // no global lock was entered
      SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 0);

      // boot parameters are set
      SWT_EvalEq(RBSYS_BURAM_BB_FSW_INTERFACE.BootblockRequest, RBSYS_SKIP_BOOTBLOCK);

      // boot parameters are stored in backup RAM
      SWT_Eval(TRBSYS_saveBaseOSRequestToBackupRAM_callCount > 0);
      SWT_Eval(RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM_callcount > 0);

      // skipbootblock requester is set
      RBMESG_RcvMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);
      SWT_EvalEq(l_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32, RBSYS_SKIP_BOOTBLOCKTrigbyFSW);

      // all flags cleared
      TRBSYS_uCReset_CheckAllResetFlagsCleared();

      // registers for application reset 1 are set
      SWT_EvalEq(SWARESA0, 0x1); // software application reset 1 is generated
      SWT_EvalEq(STAC_LM0, 0x0); // no zeroing of LRAM

      // function runs into endless loop that waits for reset
      SWT_Eval(TRBSYS_EndlessLoopCount > 0);
    }

  #endif /* RBFS_TargetDevice_RenesasD1 || RBFS_TargetDevice_RenesasD2 */



  #if (RBFS_SysBootblockSupport == RBFS_SysBootblockSupport_ON)

    /**
    * \Reference
    *  RBSYS_uCReset_ApplResetWithBootBlock4OEM, Gen_SWCS_HSW_uC_Base_SYS-315, Gen_SWCS_HSW_uC_Base_SYS-330
    *
    * \Purpose
    *  Verification of function RBSYS_uCReset_ApplResetWithBootBlock4OEM
    *
    * \Sequence
    *  Call function under test
    *
    * \ExpectedResult
    * Only core local interrupts are disabled and no common lock was entered
    * Boot parameters are set as follows:
    *    Bootblock request: RBSYS_FSW_RUN_OEM_BOOTBLOCK
    *    Skip bootblock indication: RBSYS_WITH_BOOTBLOCKTrigbyFSW
    * Boot parameters are stored to backup RAM
    * SW System / SW Application / Terminal Reset flags are cleared (will be set again once reset is executed)
    * Registers for application reset 1 are set with zeroing of GRAM and LRAM except for Backup RAM
    * An endless loop is entered for waiting for reset
    */
    SWTEST void TRBSYS_uCResetWithBootBlock4OEM(void)
    {
      RBMESG_DefineMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);

      // set default of BootblockRequest to something different than 0 as RBSYS_FSW_RUN_OEM_BOOTBLOCK == 0x0
      RBSYS_BURAM_BB_FSW_INTERFACE.BootblockRequest = 0xFFFFFFFFu;

      // call function under test
      RBSYS_uCReset_ApplResetWithBootBlock4OEM();

      // FSW BURAM shall be zeroed to not misinterpret the BackupRAM after reprogramming new software
      SWT_EvalEq(TRBSYS_ClearFSWBackupRAM_callCount, 1);

      // core local interrupts are disabled
      SWT_Eval(TRBSYS_CoreLocalLock.fnc_call_cnt > 0);
      SWT_Eval(TRBSYS_CoreLocalLock.nest_cnt > 0);
      // no global lock was entered
      SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 0);

      // boot parameters are set
      SWT_EvalEq(RBSYS_BURAM_BB_FSW_INTERFACE.BootblockRequest, RBSYS_FSW_RUN_OEM_BOOTBLOCK);


      // boot parameters are stored in backup RAM
      SWT_Eval(TRBSYS_saveBaseOSRequestToBackupRAM_callCount > 0);
      SWT_Eval(RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM_callcount > 0);

      // skipbootblock requester is set
      RBMESG_RcvMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);
      SWT_EvalEq(l_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32, RBSYS_WITH_BOOTBLOCKTrigbyFSW);

      // all flags cleared
      TRBSYS_uCReset_CheckAllResetFlagsCleared();

      // registers for application reset 1 are set
      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        SWT_EvalEq(SWARESA0, 0x1); // software application reset 1 is generated
        SWT_EvalEq(STAC_LM0, 0x1); // RAM initialization mode for CPU0 is enabled exluding Backup Section
      #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        SWT_EvalEq(SYSCTRLRESKCPROT0, 0xA5A5A501u); // write access to SWARESA is enabled
        SWT_EvalEq(SYSCTRLSWARESA, 0x1); // software application reset 1 is generated
      #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        SWT_EvalEq(MC_ME_PER.ModeReg.MCTL, ((0x0<<28) | 0xA50F));
      #endif

      // function runs into endless loop that waits for reset
      SWT_Eval(TRBSYS_EndlessLoopCount > 0);
    }


    /**
    * \Reference
    *  RBSYS_uCReset_ApplResetWithBootBlock4RB, Gen_SWCS_HSW_uC_Base_SYS-315, Gen_SWCS_HSW_uC_Base_SYS-330
    *
    * \Purpose
    *  Verification of function RBSYS_uCReset_ApplResetWithBootBlock4RB
    *
    * \Sequence
    *  Call function under test
    *
    * \ExpectedResult
    * Only core local interrupts are disabled and no common lock was entered
    * Boot parameters are set as follows:
    *    Bootblock request: RBSYS_FSW_RUN_RB_BOOTBLOCK
    *    Skip bootblock indication: RBSYS_WITH_BOOTBLOCKTrigbyFSW
    * Boot parameters are stored to backup RAM
    * SW System / SW Application / Terminal Reset flags are cleared (will be set again once reset is executed)
    * Registers for application reset 1 are set with zeroing of GRAM and LRAM except for Backup RAM
    * An endless loop is entered for waiting for reset
    */
    SWTEST void TRBSYS_uCResetWithBootBlock4RB(void)
    {
      RBMESG_DefineMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);

      // call function under test
      RBSYS_uCReset_ApplResetWithBootBlock4RB();

      // FSW BURAM shall be zeroed to not misinterpret the BackupRAM after reprogramming new software
      SWT_EvalEq(TRBSYS_ClearFSWBackupRAM_callCount, 1);

      // core local interrupts are disabled
      SWT_Eval(TRBSYS_CoreLocalLock.fnc_call_cnt > 0);
      SWT_Eval(TRBSYS_CoreLocalLock.nest_cnt > 0);
      // no global lock was entered
      SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 0);

      // boot parameters are set
      SWT_EvalEq(RBSYS_BURAM_BB_FSW_INTERFACE.BootblockRequest, RBSYS_FSW_RUN_RB_BOOTBLOCK);

      // boot parameters are stored in backup RAM
      SWT_Eval(TRBSYS_saveBaseOSRequestToBackupRAM_callCount > 0);
      SWT_Eval(RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM_callcount > 0);

      // skipbootblock requester is set
      RBMESG_RcvMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);
      SWT_EvalEq(l_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32, RBSYS_WITH_BOOTBLOCKTrigbyFSW);

      // all flags cleared
      TRBSYS_uCReset_CheckAllResetFlagsCleared();

      // registers for application reset 1 are set
      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        SWT_EvalEq(SWARESA0, 0x1); // software application reset 1 is generated
        SWT_EvalEq(STAC_LM0, 0x1); // RAM initialization mode for CPU0 is enabled exluding Backup Section
      #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        SWT_EvalEq(SYSCTRLRESKCPROT0, 0xA5A5A501u); // write access to SWARESA is enabled
        SWT_EvalEq(SYSCTRLSWARESA, 0x1); // software application reset 1 is generated
      #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        SWT_EvalEq(MC_ME_PER.ModeReg.MCTL, ((0x0<<28) | 0xA50F));
      #endif

      // function runs into endless loop that waits for reset
      SWT_Eval(TRBSYS_EndlessLoopCount > 0);
    }


    /**
    * \Reference
    *  RBSYS_uCReset_ApplResetWithBootBlock, Gen_SWCS_HSW_uC_Base_SYS-315, Gen_SWCS_HSW_uC_Base_SYS-330
    *
    * \Purpose
    *  Verification of function RBSYS_uCReset_ApplResetWithBootBlock
    *
    * \Sequence
    *  Call function under test
    *
    * \ExpectedResult
    * Only core local interrupts are disabled and no common lock was entered
    * Boot parameters are set as follows:
    *    Bootblock request: RBSYS_FSW_RUN_OEM_BOOTBLOCK
    *    Skip bootblock indication: RBSYS_WITH_BOOTBLOCKTrigbyFSW
    * Boot parameters are stored to backup RAM
    * SW System / SW Application / Terminal Reset flags are cleared (will be set again once reset is executed)
    * Registers for application reset 1 are set with zeroing of GRAM and LRAM except for Backup RAM
    * An endless loop is entered for waiting for reset
    */
    SWTEST void TRBSYS_uCResetWithBootBlock(void)
    {
      RBMESG_DefineMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);

      // call function under test
      RBSYS_uCReset_ApplResetWithBootBlock();

      // FSW BURAM shall be zeroed to not misinterpret the BackupRAM after reprogramming new software
      SWT_EvalEq(TRBSYS_ClearFSWBackupRAM_callCount, 1);

      // core local interrupts are disabled
      SWT_Eval(TRBSYS_CoreLocalLock.fnc_call_cnt > 0);
      SWT_Eval(TRBSYS_CoreLocalLock.nest_cnt > 0);
      // no global lock was entered
      SWT_EvalEq(TRBSYS_GlobLock.fnc_call_cnt, 0);

      // boot parameters are set
      SWT_EvalEq(RBSYS_BURAM_BB_FSW_INTERFACE.BootblockRequest, RBSYS_FSW_RUN_OEM_BOOTBLOCK);

      // boot parameters are stored in backup RAM
      SWT_Eval(TRBSYS_saveBaseOSRequestToBackupRAM_callCount > 0);
      SWT_Eval(RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM_callcount > 0);

      // skipbootblock requester is set
      RBMESG_RcvMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);
      SWT_EvalEq(l_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32, RBSYS_WITH_BOOTBLOCKTrigbyFSW);

      // all flags cleared
      TRBSYS_uCReset_CheckAllResetFlagsCleared();

      // registers for application reset 1 are set
      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        SWT_EvalEq(SWARESA0, 0x1); // software application reset 1 is generated
        SWT_EvalEq(STAC_LM0, 0x1); // RAM initialization mode for CPU0 is enabled exluding Backup Section
      #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        SWT_EvalEq(SYSCTRLRESKCPROT0, 0xA5A5A501u); // write access to SWARESA is enabled
        SWT_EvalEq(SYSCTRLSWARESA, 0x1); // software application reset 1 is generated
      #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        SWT_EvalEq(MC_ME_PER.ModeReg.MCTL, ((0x0<<28) | 0xA50F));
      #endif

      // function runs into endless loop that waits for reset
      SWT_Eval(TRBSYS_EndlessLoopCount > 0);
    }

  #endif /* RBFS_SysBootblockSupport_ON */


  #if( RBFS_MCORE == RBFS_MCORE_ON )
    /**
    * \Reference
    *  rbsys_TriggerReset, Gen_SWCS_HSW_uC_Base_SYS-318, Gen_SWFS_0979_HSW_OverallRequirements_7365
    *
    * \Purpose
    *  Verification of wait time inside rbsys_TriggerReset
    *
    * \Sequence
    *  Call function under test
    *
    * \ExpectedResult
    *  rbsys_TriggerReset shall have 100us timeout time until RBSYS_ExecuteReset is triggered as fallback solution
    */
    SWTEST void TRBSYS_TestTriggerReset(void)
    {
      TRBSYS_SetValidRequestedResetType();
      TRBSYS_TriggerReset();

      /** 100us wait time will always expire in Unittest because MergeProc does not fill "RBSYS_CauseResetSyncInterrupt" */
      SWT_EvalEq(TRBSYS_GetWaitUsecLoop_ExpiredTime(), 100);
    }
  #endif


  /**
  * \Reference
  *  RBSYS_ClearResetFactorsAfterSafetyTests
  *
  * \Purpose
  *  Hint: Multiple components require to do specific actions once per Reset (e.g. PowerOn Reset)
  *  RBSYS_ClearResetFactorsAfterSafetyTests will be called in every Application Startup after the Safety Tests
  *  It shall clear PowerOn and HWBist Reset flag.
  *
  * \Sequence
  *  Call RBSYS_ClearResetFactorsAfterSafetyTests
  *  Verify that PowerOn and HWBist Reset Flag(s) are cleared
  *
  * \ExpectedResult
  *  see \Seq
  */
  SWTEST void TRBSYS_ClearResetFactorsAfterSafetyTests(void)
  {
    RBSYS_ClearResetFactorsAfterSafetyTests();

    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
      SWT_EvalEq( RBSYS_RESF, 0); //< shall not be changed, is readonly
      SWT_EvalEq( RBSYS_RESFC, RBSYS_RESET_FLAG_POWERON | RBSYS_RESET_FLAG_HW_BIST );
    #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      SWT_EvalEq( RBSYS_RESF, 0); //< shall not be changed, is readonly
      SWT_EvalEq( RBSYS_RESFC, RBSYS_RESET_FLAG_POWERON | RBSYS_RESET_FLAG_HW_BIST_F0 | RBSYS_RESET_FLAG_HW_BIST_F1 | RBSYS_RESET_FLAG_HW_BIST_F2 );
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      /* Status registers are w1c */
      SWT_EvalEq( MC_RGM_PER.DES, RBSYS_RESET_DEST_FLAG_POWERON );
      SWT_EvalEq( MC_RGM_PER.FES, RBSYS_RESET_FUNC_FLAG_HW_BIST_COMPLETE );
    #endif
  }

  /**
    * \Reference
    *  RBSYS_isBISTReset
    *
    * \Purpose
    *  Safety Tests will be executed if the BIST has been executed. Therefore, the information, if the BIST has been
    *  completed, has to be provided.
    *
    * \Sequence
    *  Call RBSYS_isBISTReset
    *  Verify if correct flags are read
    *
    * \ExpectedResult
    *  see \Seq
    */
  SWTEST void TRBSYS_SafetyTestExecutionCondition(void)
  {
    // Result TRUE
    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
      RBSYS_RESF = RBSYS_RESET_FLAG_HW_BIST;
    #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      RBSYS_RESF = RBSYS_RESET_FLAG_HW_BIST_F0;
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      MC_RGM_PER.FES = RBSYS_RESET_FUNC_FLAG_HW_BIST_COMPLETE;
    #endif

    SWT_EvalEq(RBSYS_isBISTReset(), TRUE);

    // Result TRUE (all bit set in register)
    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
      RBSYS_RESF = 0xFFFFFFFFu;
    #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      RBSYS_RESF = 0xFFFFFFFFu;
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      MC_RGM_PER.FES = 0xFFFFFFFFu;
    #endif

    SWT_EvalEq(RBSYS_isBISTReset(), TRUE);

    // Result FALSE (only relevant bit is not set)
    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
      RBSYS_RESF = 0xFFFFFFFFu & ~RBSYS_RESET_FLAG_HW_BIST;
    #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      RBSYS_RESF = 0xFFFFFFFFu & ~RBSYS_RESET_FLAG_HW_BIST_F0;
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      MC_RGM_PER.FES = 0xFFFFFFFFu & ~RBSYS_RESET_FUNC_FLAG_HW_BIST_COMPLETE;
    #endif

    SWT_EvalEq(RBSYS_isBISTReset(), FALSE);
  }

  /**
  * \Reference
  *  RBSYS_isSWResetTriggeredByFSW
  *
  * \Purpose
  *  Check detection of reset source "FSW" (Application)
  *
  * \Sequence
  *  1. Set Reset Source (BURAM) to "FSW"
  *  Do not set Reset Flags
  *  Eval: False
  *  2. Set Reset Source (BURAM) to None
  *  Set Application Reset Flag
  *  Eval: False
  *  3. Set Reset Source (BURAM) to "FSW" and Reset Flag to Application Reset
  *  Eval: True
  *
  * \ExpectedResult
  *  see \Seq
  */
  SWTEST void TRBSYS_isSWResetTriggeredByFSW(void)
  {
    RBMESG_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32 = RBSYS_SKIP_BOOTBLOCKTrigbyFSW;
    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      RBSYS_RESF = 0;
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      MC_RGM_PER.FES = 0;
    #endif
    SWT_EvalEq(RBSYS_isSWResetTriggeredByFSW(), FALSE);

    RBMESG_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32 = 0;
    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      RBSYS_RESF = RBSYS_RESET_FLAG_SW_APPLICATION_0;
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      MC_RGM_PER.FES = RBSYS_RESET_FUNC_FLAG_SW_RESET;
    #endif
    SWT_EvalEq(RBSYS_isSWResetTriggeredByFSW(), FALSE);

    RBMESG_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32 = RBSYS_SKIP_BOOTBLOCKTrigbyFSW;
    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      RBSYS_RESF = RBSYS_RESET_FLAG_SW_APPLICATION_0;
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      MC_RGM_PER.FES = RBSYS_RESET_FUNC_FLAG_SW_RESET;
    #endif
    SWT_EvalEq(RBSYS_isSWResetTriggeredByFSW(), TRUE);

    /* additionally: check with wrong Reset Flag "System Reset" */
    RBMESG_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32 = RBSYS_SKIP_BOOTBLOCKTrigbyFSW;
    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      RBSYS_RESF = RBSYS_RESET_FLAG_SW_SYSTEM_0;
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      MC_RGM_PER.DES = RBSYS_RESET_DEST_FLAG_SW_RESET;
    #endif
    SWT_EvalEq(RBSYS_isSWResetTriggeredByFSW(), FALSE);
  }

  /**
  * \Reference
  *  RBSYS_HasPowerOnResetOccurred, RBSYS_ClearResetFactorsAfterSafetyTests
  *
  * \Purpose
  *  Check Detection, Storage and Get-Interface for Power Cycle Flag
  *
  * \Sequence
  *  Set any other than PowerOn Reset Flag
  *  Call RBSYS_ClearResetFactorsAfterSafetyTests
  *  Eval: RBSYS_HasPowerOnResetOccurred shall return FALSE
  *
  *  Set PowerOn Reset Flag
  *  Call RBSYS_ClearResetFactorsAfterSafetyTests
  *  Eval: RBSYS_HasPowerOnResetOccurred shall return TRUE
  *
  * \ExpectedResult
  *  see \Seq
  */
  SWTEST void TRBSYS_PowerCycleFlagStorage(void)
  {
    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      RBSYS_RESF = ~RBSYS_RESET_FLAG_POWERON;
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      MC_RGM_PER.DES = ~RBSYS_RESET_DEST_FLAG_POWERON;
      MC_RGM_PER.FES = 0xFFFFFFFF;
    #endif
    RBSYS_ClearResetFactorsAfterSafetyTests();
    SWT_EvalEq(RBSYS_HasPowerOnResetOccurred(), FALSE);

    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      RBSYS_RESF = RBSYS_RESET_FLAG_POWERON;
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      MC_RGM_PER.DES = RBSYS_RESET_DEST_FLAG_POWERON;
      MC_RGM_PER.FES = 0;
    #endif
    RBSYS_ClearResetFactorsAfterSafetyTests();
    SWT_EvalEq(RBSYS_HasPowerOnResetOccurred(), TRUE);
  }

#else // all Bootblock builds

  #include "TRBSYS_uCReset_Adaptor.h"
  #include "RBSYS_BBResetHandling.h"

  /**
  * \Reference
  *  RBSYS_BBSWResetSkipBB, Gen_SWCS_HSW_uC_Base_SYS-315, Gen_SWCS_HSW_uC_Base_SYS-330
  *
  * \Purpose
  *  Verification of function RBSYS_BBSWResetSkipBB
  *
  * \Sequence
  *  Call function under test
  *
  * \ExpectedResult
  * Boot parameters are set as follows:
  *    Bootblock request: RBSYS_SKIP_BOOTBLOCK
  * Boot parameters are stored to backup RAM
  * SW System / SW Application / Terminal Reset flags are cleared (will be set again once reset is executed)
  * Registers for application reset 1 are set with zeroing of GRAM and LRAM except for Backup RAM
  * An endless loop is entered for waiting for reset
  */
  SWTEST void TRBSYS_BBSWResetSkipBB(void)
  {
    // call function under test
    RBSYS_BBSWResetSkipBB();


    // boot parameters are set
    SWT_EvalEq(RBSYS_BURAM_BB_FSW_INTERFACE.BootblockRequest, RBSYS_SKIP_BOOTBLOCK);

    // all flags cleared
    TRBSYS_uCReset_CheckAllResetFlagsCleared();

    // registers for application reset 1 are set
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEq(SWARESA0, 0x1); // software application reset 1 is generated
      SWT_EvalEq(STAC_LM0, 0x1); // RAM initialization mode for CPU0 is enabled exluding Backup Section
    #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      SWT_EvalEq(SYSCTRLRESKCPROT0, 0xA5A5A501u); // write access to SWARESA is enabled
      SWT_EvalEq(SYSCTRLSWARESA, 0x1); // software application reset 1 is generated
    #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
      SWT_EvalEq(MC_ME_PER.ModeReg.MCTL, ((0x0<<28) | 0xA50F));
    #endif

    // function runs into endless loop that waits for reset
    SWT_Eval(TRBSYS_EndlessLoopCount > 0);
  }

  /**
  * \Reference
  *  RBSYS_ExecuteReset, Gen_SWCS_HSW_uC_Base_SYS-315
  *
  * \Purpose
  *  Verification of function RBSYS_ExecuteReset - defensiveness against invalid states
  *
  * \Sequence
  *  manipulate rbsys_ResetRequest (RBSYS_uCResetType_Undefined, any undefined value)
  *  Call function under test
  *  assertion shall be called, reset is not triggered
  *
  * \ExpectedResult
  *  see sequence
  */
  SWTEST void TRBSYS_ExecuteReset_InvalidDataModelStateBB(void)
  {
    /// "defined-Undefined" Reset Type (Value 0 - to prevent malfunction by RAM zeroing)
    TRBSYS_SetUndefinedRequestedResetType();
    TRBSYS_ExecuteReset();
    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
      SWT_EvalEq(SWARESA0, 0);
      SWT_EvalEq(STAC_LM0, 0);
      SWT_EvalEq(STAC_GRAM, 0);
    #endif

    // all flags cleared
    TRBSYS_uCReset_CheckAllResetFlagsCleared();

    /// undefined Reset Type
    TRBSYS_SetInvalidRequestedResetType();
    TRBSYS_ExecuteReset();
    SWT_EvalEq(SWARESA0, 0);
    SWT_EvalEq(STAC_LM0, 0);
    SWT_EvalEq(STAC_GRAM, 0);

    // all flags cleared
    TRBSYS_uCReset_CheckAllResetFlagsCleared();
  }

  /**
  * \Reference
  *  RBSYS_BBSWResetWithBB, Gen_SWCS_HSW_uC_Base_SYS-315, Gen_SWCS_HSW_uC_Base_SYS-330
  *
  * \Purpose
  *  Verification of function RBSYS_BBSWResetWithBB
  *
  * \Sequence
  *  Call function under test
  *
  * \ExpectedResult
  * Boot parameters are set as follows:
  *    Bootblock request: RBSYS_BB_RUN_BOOTBLOCK
  * Boot parameters are stored to backup RAM
  * SW System / SW Application / Terminal Reset flags are cleared (will be set again once reset is executed)
  * Registers for application reset 1 are set with zeroing of GRAM and LRAM except for Backup RAM
  * An endless loop is entered for waiting for reset
  */
  SWTEST void TRBSYS_BBSWResetWithBB(void)
  {
    // call function under test
    RBSYS_BBSWResetWithBB();


    // boot parameters are set
    SWT_EvalEq(RBSYS_BURAM_BB_FSW_INTERFACE.BootblockRequest, RBSYS_BB_RUN_BOOTBLOCK);

    // all flags cleared
    TRBSYS_uCReset_CheckAllResetFlagsCleared();

    // registers for application reset 1 are set
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEq(SWARESA0, 0x1); // software application reset 1 is generated
      SWT_EvalEq(STAC_LM0, 0x1); // RAM initialization mode for CPU0 is enabled exluding Backup Section
    #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      SWT_EvalEq(SYSCTRLRESKCPROT0, 0xA5A5A501u); // write access to SWARESA is enabled
      SWT_EvalEq(SYSCTRLSWARESA, 0x1); // software application reset 1 is generated
    #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
      SWT_EvalEq(MC_ME_PER.ModeReg.MCTL, ((0x0<<28) | 0xA50F));
    #endif

    // function runs into endless loop that waits for reset
    SWT_Eval(TRBSYS_EndlessLoopCount > 0);
  }

  /**
  * \Reference
  *  RBSYS_BBSystemReset, Gen_SWCS_HSW_uC_Base_SYS-315, Gen_SWCS_HSW_uC_Base_SYS-330
  *
  * \Purpose
  *  Verification of function RBSYS_BBSystemReset
  *
  * \Sequence
  *  Call function under test
  *
  * \ExpectedResult
  * SW System / SW Application / Terminal Reset flags are cleared (will be set again once reset is executed)
  * Registers for system reset 2 are set
  * An endless loop is entered for waiting for reset
  */
  SWTEST void TRBSYS_BBSystemReset(void)
  {
    // call function under test
    RBSYS_BBSystemReset();

    // all flags cleared
    TRBSYS_uCReset_CheckAllResetFlagsCleared();

    // registers for application reset 1 are set
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEq(SWSRESA0, 0x1); // software application reset 1 is generated
      SWT_EvalEq(BSEQ0CTL, 0x1); // execute HWBist after SysReset
    #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      SWT_EvalEq(SYSCTRLRESKCPROT0, 0xA5A5A501u); // write access to SWARESA is enabled
      SWT_EvalEq(SYSCTRLSWSRESA, 0x1); // software application reset 1 is generated
      SWT_EvalEq(SYS0BSEQ0CTL, 0x0); // execute HWBist according to Flash Option Byte
    #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
      SWT_EvalEq(MC_ME_PER.ModeReg.MCTL, ((0xF<<28) | 0xA50F));
    #endif

    // function runs into endless loop that waits for reset
    SWT_Eval(TRBSYS_EndlessLoopCount > 0);
  }




  /**
  * \Reference
  *  RBSYS_BBisSWResetByBB, RBSYS_BBisSWResetByFSW2OEMBoot, RBSYS_BBisSWResetByFSW2RBBoot
  *
  * \Purpose
  *  Verification of functions (see reference)
  *
  * \Sequence
  *  Check all combinations and the expected result (see implementation)
  *
  * \ExpectedResult
  *  see \Seq
  */
  SWTEST void TRBSYS_BBReset_IsSWResetInterfaces(void)
  {
    uint32 i;

    typedef struct {
      // input
      boolean IsApplicationReset;
      boolean IsSystemReset;
      uint32  BootblockRequest;
      // expectation
      boolean IsSWResetByBB;
      boolean IsSWResetFromFSW2OEMBoot;
      boolean IsSWResetFromFSW2RBBoot;
    } testCombination_t;

    testCombination_t testInput[] = {
      /* ApplReset, SystemReset, BootblockRequest,            IsSWResetByBB,  IsSWResetFromFSW2OEMBoot, IsSWResetFromFSW2RBBoot */
      {  TRUE,      FALSE,       RBSYS_BB_RUN_BOOTBLOCK,      TRUE,           FALSE,                    FALSE          },
      {  TRUE,      FALSE,       RBSYS_FSW_RUN_RB_BOOTBLOCK,  FALSE,          FALSE,                    TRUE           },
      {  TRUE,      FALSE,       RBSYS_FSW_RUN_OEM_BOOTBLOCK, FALSE,          TRUE,                     FALSE          },
      {  TRUE,      FALSE,       RBSYS_FSW_RUN_BOOTBLOCK,     FALSE,          TRUE,                     FALSE          },
      {  FALSE,     TRUE,        RBSYS_BB_RUN_BOOTBLOCK,      FALSE,          FALSE,                    FALSE          } //< System Reset was performed, RAM was zeroed -> no Request
    };

    for(i=0; i< (sizeof(testInput)/sizeof(testCombination_t)); i++)
    {
      testCombination_t input = testInput[i];

      if( input.IsApplicationReset )
      {
        TRBSYS_setSWResetByApplicationReset();
      }
      if( input.IsSystemReset )
      {
        TRBSYS_setSWResetBySystemReset();
      }

      TRBSYS_setBootblockRequest(input.BootblockRequest);

      SWT_EvalEq(RBSYS_BBisSWResetByBB(),          input.IsSWResetByBB);
      SWT_EvalEq(RBSYS_BBisSWResetByFSW2OEMBoot(), input.IsSWResetFromFSW2OEMBoot);
      SWT_EvalEq(RBSYS_BBisSWResetByFSW2RBBoot(),  input.IsSWResetFromFSW2RBBoot);
    }
  }

#endif //< All Bootblock builds

/**
 * \Reference
 *  RBSYS_ClearResetFactorsAtStartup
 *
 * \Purpose
 *  Verify if Application, System and Terminal Reset Flag are cleared if Terminal Reset has happened
 *  Verify that RBSYS_RESF is unchanged if Terminal Reset has not happened
 *
 * \Sequence
 *  Call RBSYS_ClearResetFactorsAtStartup
 *  Verify Reset Factor register
 *  see also UT implementation
 *
 * \ExpectedResult
 *  see \Seq
 */
SWTEST void TRBSYS_ClearResetFactorsAtStartup(void)
{
  /* check for absence of interaction */
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    RBSYS_RESF = ~RBSYS_RESET_FLAG_TERMINAL; //< anything but Terminal Reset
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    MC_RGM_PER.DES = 0;
  #endif

  RBSYS_ClearResetFactorsAtStartup();

  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    SWT_EvalEq( RBSYS_RESF, ~RBSYS_RESET_FLAG_TERMINAL);
    SWT_EvalEq( RBSYS_RESFC, 0);
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    SWT_EvalEq( MC_RGM_PER.DES, 0);  // no destructive reset flag has been zeroed (write 1 clears)
    SWT_EvalEq( MC_RGM_PER.FES, 0);  // no functional reset flag has being zeroed (write 1 clears)
  #endif

  /* check for functionality */
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    RBSYS_RESF = RBSYS_RESET_FLAG_TERMINAL;
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    MC_RGM_PER.DES = RBSYS_RESET_DEST_FLAG_RESETPIN_A;
  #endif

  RBSYS_ClearResetFactorsAtStartup();

  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    SWT_EvalEq( RBSYS_RESF, RBSYS_RESET_FLAG_TERMINAL); //< not changed, flags will be cleared via Clear Register
    SWT_EvalEq( RBSYS_RESFC, RBSYS_RESET_FLAG_SW_APPLICATION_0 | RBSYS_RESET_FLAG_SW_SYSTEM_0 | RBSYS_RESET_FLAG_TERMINAL);
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    SWT_EvalEq( MC_RGM_PER.DES, RBSYS_RESET_DEST_FLAG_SW_RESET | RBSYS_RESET_DEST_FLAG_RESETPIN_A);
    SWT_EvalEq( MC_RGM_PER.FES, RBSYS_RESET_FUNC_FLAG_SW_RESET );
  #endif
}


#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    /**
     * \Reference
     *  RBSYS_uCReset_ClearuCVoltageMonResetFlags
     *
     * \Purpose see \Seq
     *
     * \Sequence
     *  Call RBSYS_uCReset_ClearuCVoltageMonResetFlags
     *  Verify that correct Reset Flags are getting cleared
     *
     * \ExpectedResult
     *  see \Seq
     */
    SWTEST void TRBSYS_ClearCVMandVMONFlags(void)
    {
      RBSYS_RESF = (0xFFFFFFFF);

      /* check for absence of interaction */
      #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )

        SWT_EvalEq(RBSYS_isCVMReset(), TRUE );
      
        RBSYS_uCReset_ClearuCVoltageMonResetFlags();
        SWT_EvalEqX( RBSYS_RESFC, (1<<2) );
      
        RBSYS_RESF &= ~RBSYS_RESFC;
        SWT_EvalEq(RBSYS_isCVMReset(), FALSE );
      
      #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

        SWT_EvalEq(RBSYS_isVMONReset(), TRUE; );
      
        RBSYS_uCReset_ClearuCVoltageMonResetFlags();
        SWT_EvalEqX( RBSYS_RESFC, (1<<3) );
      
        RBSYS_RESF &= ~RBSYS_RESFC;
        SWT_EvalEq(RBSYS_isVMONReset(), FALSE; );
      
      #endif
    }
  #endif
#endif


/** @} */
/* End ingroup RBSYS */