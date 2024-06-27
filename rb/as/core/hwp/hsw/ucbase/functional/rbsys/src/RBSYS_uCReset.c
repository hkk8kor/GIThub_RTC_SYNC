/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Handling of Reset Actuation and Info
 *
 * This unit handles only an immediate low level uC reset, which is allowed to be called only in case
 * of serious "not recoverable" system faults or within very special circumstances (BaseOS).
 * This unit handles storing and resetting the uC reset flags for any usecase.
 *
 * Official interface RB_SWReset.h must be used for default SW reset use cases, which handles the ASIC safety logic
 * before triggering an uC reset!
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */



#include "RBSYS_Config.h"

/* realized interfaces */
#include "RBSYS_uCResetInfo.h"
#include "RBSYS_uCResetInternal.h"

#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
  #include "RBSYS_uCResetCtrl.h"
  #include "RBSYS_ResetSync.h"
#else // Bootmanager, Bootloader
  #include "RBSYS_BBResetHandling.h"
#endif

/* used interfaces */
#include "RBSYS_uCRegisters.h"
#include "RBSYS_Intrinsics.h"
#include "RBSYS_BBFSW_StartupServices.h"
#include "RBSYS_PlantStartupCtrl.h"
#include "RBSYS_RAMBackupServiceIntern.h"
#include "RBSYS_TestInjection.h"
#include "RBSYS_SystemTimer.h"
#include "RB_MemoryBarrier.h"


/******************************************************************************/
/* default header includes for appl. processes via merge proc                 */
/******************************************************************************/
/*ROOT_SECTION: HeaderIncludes_Root |#include "|" */
/*PROC_EP: HeaderIncludes */
/*ROOT_SECTION_END: */


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysBootblockSupport,
                          RBFS_SysBootblockSupport_OFF,
                          RBFS_SysBootblockSupport_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TargetDevice,
                          RBFS_TargetDevice_RenesasD1,
                          RBFS_TargetDevice_RenesasD2,
                          RBFS_TargetDevice_RenesasD3,
                          RBFS_TargetDevice_RenesasD4,
                          RBFS_TargetDevice_RenesasD5,
                          RBFS_TargetDevice_RenesasD7,
                          RBFS_TargetDevice_RenesasM2,
                          RBFS_TargetDevice_RenesasM3,
                          RBFS_TargetDevice_RenesasM6,
                          RBFS_TargetDevice_RenesasK0,
                          RBFS_TargetDevice_RenesasK1,
                          RBFS_TargetDevice_STMP6);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasP1xGRAM,
                          RBFS_RenesasP1xGRAM_ON,
                          RBFS_RenesasP1xGRAM_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_ON,
                          RBFS_MCORE_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

/* Hint: Even if HexBlockBuild is BMGR/BLDR/RBBLDR, RBSYS bootblock interfaces do not have to be used */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysBootblockBuild,
                          RBFS_SysBootblockBuild_Active,
                          RBFS_SysBootblockBuild_NotActive);

RB_ASSERT_SWITCH_SETTINGS(RBFS_FOTA,
                          RBFS_FOTA_OFF,
                          RBFS_FOTA_BASE,
                          RBFS_FOTA_BASEPLUS,
                          RBFS_FOTA_ENHANCED,
                          RBFS_FOTA_PREMIUM);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HswRecoveryReset,
                          RBFS_HswRecoveryReset_Enabled,
                          RBFS_HswRecoveryReset_Disabled);


#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  // Stellar: Resets are triggered via uC Domain Control Modules (only via Peripheral-Domain, will propagate to Core-Domains)
  #include "RBSYS_uCModuleModeCtrl.h"
#endif

void RBSYS_ClearResetFactorsAtStartup(void)
{
  // If a Terminal Reset was seen, previous Application and System Resets are not relevant anymore */
  if( RBSYS_isTerminalReset() )
  {
    // Delete System, Application and Terminal Reset flag => Next reset can be identified from now on

    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
      || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
      || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

      RBSYS_RESFC = RBSYS_RESET_FLAG_SW_SYSTEM_0 | RBSYS_RESET_FLAG_SW_APPLICATION_0 | RBSYS_RESET_FLAG_TERMINAL;

    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

      MC_RGM_PER.FES = RBSYS_RESET_FUNC_FLAG_SW_RESET;
      MC_RGM_PER.DES = (RBSYS_RESET_DEST_FLAG_RESETPIN_A | RBSYS_RESET_DEST_FLAG_SW_RESET);

    #endif
  }
}

/** @brief Clear Reset Factors before executing Software Reset
  * SW Reset Flags: System Reset, Application Reset
  * HW Reset Flags: Terminal Reset
  */
static void RBSYS_ClearResetFactorsBeforeSWReset(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

    RBSYS_RESFC = RBSYS_RESET_FLAG_SW_SYSTEM_0 | RBSYS_RESET_FLAG_SW_APPLICATION_0 | RBSYS_RESET_FLAG_TERMINAL;

  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

    MC_RGM_PER.FES = RBSYS_RESET_FUNC_FLAG_SW_RESET;
    MC_RGM_PER.DES = (RBSYS_RESET_DEST_FLAG_RESETPIN_A | RBSYS_RESET_DEST_FLAG_SW_RESET);

  #endif
}

#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )

  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) \
    )
    void RBSYS_uCReset_ClearuCVoltageMonResetFlags(void)
    {
      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        RBSYS_RESFC = (RBSYS_RESET_FLAG_CVM);
      #elif(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        RBSYS_RESFC = (RBSYS_RESET_FLAG_VMON);
      #else
        assert(0 && "Not supported.");
      #endif
    }
  #endif

  static boolean rbsys_HasPowerOnResetOccurred = FALSE;
  boolean RBSYS_HasPowerOnResetOccurred(void)
  {
    return rbsys_HasPowerOnResetOccurred;
  }

  void RBSYS_ClearResetFactorsAfterSafetyTests(void)
  {
    /* Store Power Cycle Flag for later use. E.g. could be used to detect if a Power Cycle has occurred */
    /* Hint: Storing the Power Cycle Flag is done right before clearing it */
    if( RBSYS_isPowerOnReset() )
    {
      rbsys_HasPowerOnResetOccurred = TRUE;
    }

    /* Hint: PowerOn and HWBist Reset Flags are cleared right after executing Safety Tests (to not run Safety Tests again).
     *       This ensures that Safety Tests are at least executed once per Power Cycle.
     * Idea: Theoretically, these Reset Flags could be cleared when doing SW Reset by an interruption by asynchronous
     *       HW Resets (Terminal, PowerOn Reset) would have to be considered then. At the moment, we see this as a
     *       critical design because the current design is long-time verified e.g. by VIVA etc.. */

    #if  ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
      RBSYS_RESFC = (RBSYS_RESET_FLAG_POWERON | RBSYS_RESET_FLAG_HW_BIST);
    #elif(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
      RBSYS_RESFC = (RBSYS_RESET_FLAG_POWERON | RBSYS_RESET_FLAG_HW_BIST_F0 |
                    RBSYS_RESET_FLAG_HW_BIST_F1 | RBSYS_RESET_FLAG_HW_BIST_F2);
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      MC_RGM_PER.DES = (RBSYS_RESET_DEST_FLAG_POWERON);
      MC_RGM_PER.FES = (RBSYS_RESET_FUNC_FLAG_HW_BIST_COMPLETE);
    #endif
  }

#endif

/*
  =========================================================================
  Attention
  -------------------------------------------------------------------------
  Renesas RH850:
    Current SW reset concept triggers an Application Reset 1 without re-
    triggering BIST and therefore without HW based zeroing of Backup-RAM.
    If BIST must be executed after a SW triggered reset (e.g. long runners),
    it's necessary to handle this via the ASIC (SPI_res_HW) and not via the
    uC internal System Reset 2. This limitation of the System Reset 2 with
    BIST is documented within the CVM chapter of the user manual.
    This implies of course that the Backup-RAM content will be destroyed!
  ST Stellar:
    Current SW reset concept triggers a Functional SW Reset (RBSYS_uCResetxxxxBootblock)
    without retriggering BIST and thereby retaining the Backup-RAM.
    In case new SW has been programmed, the HWBIST shall be re-executed - a Destructive
    SW Reset must be issued (RBSYS_BBSystemReset). This implies that the Backup-RAM
    will be zeroed during next startup.
  =========================================================================
*/


typedef enum {
  RBSYS_uCResetType_Undefined = 0,
  RBSYS_uCResetType_ApplResetDefault,
  #if(RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
    RBSYS_uCResetType_ApplResetNoGRAMZeroing,
  #endif
  #if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2))
    RBSYS_uCResetType_ApplResetNoLRAMZeroing,
  #endif
  #if( (RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active) || (RBFS_FOTA == RBFS_FOTA_PREMIUM) || (RBFS_HswRecoveryReset == RBFS_HswRecoveryReset_Enabled) )
    RBSYS_uCResetType_SystemReset,
  #endif
  RBSYS_uCResetType_NumOfOptions
} RBSYS_uCResetType_t;

static RBSYS_uCResetType_t rbsys_ResetRequest = RBSYS_uCResetType_Undefined;




#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )

  #if( RBFS_MCORE == RBFS_MCORE_ON )
    /** \brief Trigger the necessary ResetSync FEInt */
    static void RBSYS_CauseResetSyncInterrupt(void)
    {
      /*ROOT_SECTION: SPG_RBSYS_ResetSync_Root | |(); */
      /*PROC_EP: SPG_RBSYS_ResetSync */
      /*ROOT_SECTION_END: */
    }
  #endif

  /** \brief Call functions to prepare the System for a Reset
    *
    * Attention:
    *  1. Function will be executed on the Core which is triggering the reset.
    *  2. Anything added to SPG_RBSYS_AfterResetSync must be lock-free, because we cannot garantuee that other
    *     cores will release their locks!!  */
  static void RBSYS_PreResetCleanup(void)
  {
    /*ROOT_SECTION: SPG_RBSYS_AfterResetSync_Root | |(); */
    /*PROC_EP: SPG_RBSYS_AfterResetSync */
    /*ROOT_SECTION_END: */

    RB_FullHardwareMemoryBarrier();
  }

#endif //< RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION

/**
* @brief Execute an immediate uC SW Reset
*
* The Software Reset type is preselected (call of one of the public interfaces, e.g. "RBSYS_uCReset_ApplResetSkipBootBlock")
* The Handling of LRAM/GRAM resetting options is done in this function.
* This function does never return!
* This function shall be executed while other cores are not accessing the GRAM -> due to known hardware limitation.
* This function shall only be executed on one core. It shall be executed on the core which is triggering the reset.
*
* @return void
*/
static void RBSYS_ExecuteReset(void)
{
  boolean stayInLoop;

  /* Application: Cases in which Flash is beeing used in Application:
    * - DataFlash: DFlash Access by Application and/or HSM
    * - CodeFlash: Parallel programming within FOTA Enhanced + Premium */

  /* Bootblock:   OEM Bootloader and RBBootloader are always using FACI for DataFlash / CodeFlash:
    * - Bootmanager is only using DataFlash in certain cases
    * - FACIs may have to be cleaned up -> to be considered by BMGR/BLDR/RBBLDR (not by RBSYS) */

  #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
    RBSYS_PreResetCleanup();
  #endif

  /** clear Software System/Application Reset Flag + Terminal Reset Flag so that Reset Type can be clearly identified
    * during next startup */
  RBSYS_ClearResetFactorsBeforeSWReset();

  switch(rbsys_ResetRequest)
  {
    case RBSYS_uCResetType_ApplResetDefault:

      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)   // only P1x has HW based RAM zeroing
        STAC_LM0 = 0x1;   // CPU0 local RAM zeroing excluding Backup Section
        RBSYS_SYNCM();    // ensure completion of previous write instruction (exclude BU RAM zeroing)

        SWARESA0 = 0x1;   // trigger Application Reset 1
      #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        RBSYS_UnlockAccessToHwModule(&SYSCTRLRESKCPROT0);
        SYSCTRLSWARESA = 0x1;                   // trigger Application Reset 1
      #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
        RBSYS_ModeEntry_Switch2ResetMode(RBSYS_ResetMode_Functional);
      #endif

      break;

    #if( (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON) && (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION) )
    case RBSYS_uCResetType_ApplResetNoGRAMZeroing:

      STAC_GRAM = 0x0;  // NO RAM zeroing of GRAM (at next startup)
                  //  --> to keep the (downloaded) BasicDriver in RAM,
                  //      as this will be executed at next startup
      STAC_LM0  = 0x1;  // CPU0 local RAM zeroing excluding Backup Section
      RBSYS_SYNCM();    // ensure completion of previous write instruction (exclude BU RAM zeroing)
      SWARESA0 = 0x1;   // trigger Application Reset 1
      break;
    #endif

    #if( ((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2)) && (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION) )
    case RBSYS_uCResetType_ApplResetNoLRAMZeroing:

      STAC_LM0  = 0x0;  // Disable CPU0 local RAM zeroing
      RBSYS_SYNCM();    // ensure completion of previous write instruction (exclude BU RAM zeroing)
      SWARESA0 = 0x1;   // trigger Application Reset 1
      break;
    #endif

    #if( (RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active) || (RBFS_FOTA == RBFS_FOTA_PREMIUM) || (RBFS_HswRecoveryReset == RBFS_HswRecoveryReset_Enabled) )
    case RBSYS_uCResetType_SystemReset:

      #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
        BSEQ0CTL = 0x1;       //< HWBISTEXE = 1, execute Field Bist after next SysRes2
        RBSYS_SYNCM();        //< assure that BSEQ0CTL is written before triggering reset
        SWSRESA0 = 0x1;       //< Trigger System Reset 2
      #elif(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
        RBSYS_UnlockAccessToHwModule(&SYSCTRLRESKCPROT0);        // enable write access
        SYS0BSEQ0CTL = 0x0;   //< Execute HWBist according to Flash Option Byte
        RBSYS_SYNCM();        //< assure that BSEQ0CTL is written before triggering reset
        SYSCTRLSWSRESA = 0x1; //< Trigger System Reset 2
      #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        // Reset is triggered via uC Mode Control
        RBSYS_ModeEntry_Switch2ResetMode(RBSYS_ResetMode_Destructive); //< HWBIST shall be re-executed on SW Reset => Dest Reset
      #endif

      break;
    #endif

    case RBSYS_uCResetType_Undefined:
    default:
      //assert(0); //< invalid or unimplemented, nevertheless assert cannot be used inside uCReset call path
      break;
  }

  // it takes some time until reset is issued (see Mantis issue 424 & 962 within CC-Cube DeviceSupport)
  // put core into endless-loop to avoid that instructions after issuing the reset are executed
  // wait for reset with endless loop, variable in loop condition is needed for test coverage and will always stay TRUE
  stayInLoop = TRUE;
  while(stayInLoop)
  {
    RBSYS_TEST_INJECTION_LeaveInfiniteLoop();
  }
}

#if (RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active)

  void RBSYS_BBSystemReset(void)
  {
    rbsys_ResetRequest = RBSYS_uCResetType_SystemReset;

    RBSYS_ExecuteReset();
  }

  void RBSYS_BBSWResetSkipBB(void)
  {
    RBSYS_setBootblockRequest(RBSYS_SKIP_BOOTBLOCK);

    rbsys_ResetRequest = RBSYS_uCResetType_ApplResetDefault;

    RBSYS_ExecuteReset();
  }

  void RBSYS_BBSWResetWithBB(void)
  {
    RBSYS_setBootblockRequest(RBSYS_BB_RUN_BOOTBLOCK);

    rbsys_ResetRequest = RBSYS_uCResetType_ApplResetDefault;

    RBSYS_ExecuteReset();
  }

  boolean RBSYS_BBisSWResetByBB(void)
  {
    boolean isSWReset = RBSYS_isSWResetByApplicationReset();
    boolean isRequestByBB = (RBSYS_getBootblockRequest() == RBSYS_BB_RUN_BOOTBLOCK);

    return (isSWReset && isRequestByBB);
  }


  boolean RBSYS_BBisSWResetByFSW2OEMBoot(void)
  {
    boolean isSWReset = RBSYS_isSWResetByApplicationReset();
    boolean isRequestByFSW2OEMBoot = (RBSYS_getBootblockRequest() == RBSYS_FSW_RUN_OEM_BOOTBLOCK);

    return (isSWReset && isRequestByFSW2OEMBoot);
  }


  boolean RBSYS_BBisSWResetByFSW2RBBoot(void)
  {
    boolean isSWReset = RBSYS_isSWResetByApplicationReset();
    boolean isRequestByFSW2RBBoot = (RBSYS_getBootblockRequest() == RBSYS_FSW_RUN_RB_BOOTBLOCK);

    return (isSWReset && isRequestByFSW2RBBoot);
  }
#endif //< RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active


#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
  #if( RBFS_MCORE == RBFS_MCORE_ON )
    void RBSYS_ECMTriggerUCResetAfterCoreSync(void)
    {
      RBSYS_ExecuteReset();
    }
  #endif

  static void rbsys_TriggerReset(void)
  {
    #if( RBFS_MCORE == RBFS_MCORE_ON )
      RBSYS_CauseResetSyncInterrupt();

      /* If Synchronization Interrupt is not generated withing 100us, directly execute Reset */
      RBSYS_waitUsecLoop(100);
    #endif

    /** Fallback (MultiCore) / Default (SingleCore) solution: Execute Reset if cores could not be synchronized */
    RBSYS_ExecuteReset();
  }

  #if ( (RBFS_FOTA == RBFS_FOTA_PREMIUM) || (RBFS_HswRecoveryReset == RBFS_HswRecoveryReset_Enabled) )
    void RBSYS_uCReset_SystemReset(void)
    {
      /* Hint: No global lock allowed here because SW reset could also be called during exceptions/NMI with still active lock;
        => therefore only core local interrupts are locked */
      RBSYS_SchM_Enter_CoreLocalLock();

      /* BackupRAM is invalidated upon reset */

      rbsys_ResetRequest = RBSYS_uCResetType_SystemReset;

      RB_FullHardwareMemoryBarrier();

      rbsys_TriggerReset();
    }
  #endif

  void RBSYS_uCReset_ApplResetSkipBootBlock(void)
  {
    /* Hint: No global lock allowed here because SW reset could also be called during exceptions/NMI with still active lock;
            => therefore only core local interrupts are locked */
    RBSYS_SchM_Enter_CoreLocalLock();

    RBSYS_setBootblockRequest(RBSYS_SKIP_BOOTBLOCK);
    RBSYS_saveBaseOSRequestToBackupRAM();
    RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM(RBSYS_SKIP_BOOTBLOCKTrigbyFSW);

    rbsys_ResetRequest = RBSYS_uCResetType_ApplResetDefault;

    RB_FullHardwareMemoryBarrier();

    rbsys_TriggerReset();
  }

  #if(RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)

    void RBSYS_uCReset_ApplResetSkipBootBlockNoGramZeroing(void)
    {
      /* Hint: No global lock allowed here because SW reset could also be called during exceptions/NMI with still active lock;
              => therefore only core local interrupts are locked */
      RBSYS_SchM_Enter_CoreLocalLock();

      /* Zeroing of FSW-BURAM is not required here. If flashing is done via ReprogDriver, ReprogDriver will issue SW System Reset */

      RBSYS_setBootblockRequest(RBSYS_SKIP_BOOTBLOCK);
      RBSYS_saveBaseOSRequestToBackupRAM();
      RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM(RBSYS_SKIP_BOOTBLOCKTrigbyFSW);


      rbsys_ResetRequest = RBSYS_uCResetType_ApplResetNoGRAMZeroing;
      RB_FullHardwareMemoryBarrier();

      rbsys_TriggerReset();
    }
  #endif



  #if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2) \
    )

    void RBSYS_uCReset_ApplResetSkipBootBlockNoLramZeroing(void)
    {
      /* Hint: No global lock allowed here because SW reset could also be called during exceptions/NMI with still active lock;
              => therefore only core local interrupts are locked */
      RBSYS_SchM_Enter_CoreLocalLock();

      /* Zeroing of FSW-BURAM is not required here. If flashing is done via ReprogDriver, ReprogDriver will issue SW System Reset */

      RBSYS_setBootblockRequest(RBSYS_SKIP_BOOTBLOCK);
      RBSYS_saveBaseOSRequestToBackupRAM();
      RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM(RBSYS_SKIP_BOOTBLOCKTrigbyFSW);

      rbsys_ResetRequest = RBSYS_uCResetType_ApplResetNoLRAMZeroing;
      RB_FullHardwareMemoryBarrier();

      rbsys_TriggerReset();
    }
  #endif



  #if (RBFS_SysBootblockSupport == RBFS_SysBootblockSupport_ON)

    void RBSYS_uCReset_ApplResetWithBootBlock4OEM(void)
    {
      /* Hint: No global lock allowed here because SW reset could also be called during exceptions/NMI with still active lock;
              => therefore only core local interrupts are locked */
      RBSYS_SchM_Enter_CoreLocalLock();

      /* Zero complete FSW-BURAM to not missinterpret it after flashing a new application */
      RBSYS_ClearFSWBackupRAM();

      RBSYS_setBootblockRequest(RBSYS_FSW_RUN_OEM_BOOTBLOCK);
      RBSYS_saveBaseOSRequestToBackupRAM();
      RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM(RBSYS_WITH_BOOTBLOCKTrigbyFSW);

      rbsys_ResetRequest = RBSYS_uCResetType_ApplResetDefault;
      RB_FullHardwareMemoryBarrier();

      rbsys_TriggerReset();
    }



    void RBSYS_uCReset_ApplResetWithBootBlock4RB(void)
    {
      /* Hint: No global lock allowed here because SW reset could also be called during exceptions/NMI with still active lock;
              => therefore only core local interrupts are locked */
      RBSYS_SchM_Enter_CoreLocalLock();

      /* Zero complete FSW-BURAM to not missinterpret it after flashing a new application */
      RBSYS_ClearFSWBackupRAM();

      RBSYS_setBootblockRequest(RBSYS_FSW_RUN_RB_BOOTBLOCK);
      RBSYS_saveBaseOSRequestToBackupRAM();
      RBSYS_setSkipBootblockRequesterAndSaveToBackupRAM(RBSYS_WITH_BOOTBLOCKTrigbyFSW);

      rbsys_ResetRequest = RBSYS_uCResetType_ApplResetDefault;
      RB_FullHardwareMemoryBarrier();

      rbsys_TriggerReset();
    }

    void RBSYS_uCReset_ApplResetWithBootBlock(void)
    {
      RBSYS_uCReset_ApplResetWithBootBlock4OEM();
    }

  #endif

  boolean RBSYS_isSWResetTriggeredByFSW(void)
  {
    RBMESG_DefineMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);
    RBMESG_RcvMESGDef(RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32);

    /* Result is only valid if SW was reset by Application Reset, otherwise (e.g. System Reset), BURAM is invalid */
    return (RBSYS_isSWResetByApplicationReset() && (l_RBMESG_RBSYSSkipBootblockRequesterPrevIC_u32 == RBSYS_SKIP_BOOTBLOCKTrigbyFSW));
  }

#endif // RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION




/** @} */
/* End ingroup RBSYS */