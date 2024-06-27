/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief RBSYS related start-up code for bootblock
 *
 * This module must be part of the bootblock and contains the whole uC start-up and
 * controller specific initialization.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "../../RBSYS_CoreInit.h"
#include "RBSYS_CpuInfo.h"
#include "../../Monitorings/RBSYS_StackHandling.h"
#include "RBSYS_GuardConfig.h"
#include "../../SystemMemoryProtection/RBSYS_GuardConfigCommon.h"
#include "../../RBSYS_TimerSetup.h"
#include "../../RBSYS_CacheControlIntern.h"
#include "RBSYS_ClockSettings.h"
#include "../../RBSYS_ClockSettingsIntern.h"
#include "RBLCF_MemoryRemap.h"
#include "RBSYS_BBFSW_StartupServices.h"
#include "RBSYS_Intrinsics.h"
#include "RBSYS_BBFSW_jump.h"
#include "RBSYS_BBMain.h"
#include "RBSYS_uCRegisters.h"
#include "RBSYS_uCResetInfo.h"
#include "../../RBSYS_uCResetInternal.h"
#include "../../RBSYS_RAMBackupServiceIntern.h"
#include "../../RBSYS_MultiCoreSyncIntern.h"

/* realized interfaces */
#include "RBSYS_Bootblock_Startup.h"
#include "RBSYS_GHS_ProgramStartup.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysBootblockBuild,
                          RBFS_SysBootblockBuild_Active,
                          RBFS_SysBootblockBuild_NotActive);

RB_ASSERT_SWITCH_SETTINGS(RBFS_BootblockSysStartupCode,
                          RBFS_BootblockSysStartupCode_ON,
                          RBFS_BootblockSysStartupCode_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasP1xGRAM,
                          RBFS_RenesasP1xGRAM_ON,
                          RBFS_RenesasP1xGRAM_OFF);

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
                          RBFS_TargetDevice_STMP6);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

RB_ASSERT_SWITCH_SETTINGS(RBFS_DataFlashECC,
                          RBFS_DataFlashECC_Disabled,
                          RBFS_DataFlashECC_Enabled);

RB_ASSERT_SWITCH_SETTINGS(RBFS_CompilationLanguage,
                          RBFS_CompilationLanguage_PureC,
                          RBFS_CompilationLanguage_PureCPP,
                          RBFS_CompilationLanguage_MixedCandCPP);

RB_ASSERT_SWITCH_SETTINGS(RBFS_CPUMisalignedAccessSupport,
                          RBFS_CPUMisalignedAccessSupport_ON,
                          RBFS_CPUMisalignedAccessSupport_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_BackupRAMLayout,
                          RBFS_BackupRAMLayout_Legacy,
                          RBFS_BackupRAMLayout_V1);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RBSYSGlobalRAMGuardsBB,
                          RBFS_RBSYSGlobalRAMGuardsBB_ON,
                          RBFS_RBSYSGlobalRAMGuardsBB_OFF);



#if ((RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active) && (RBFS_BootblockSysStartupCode == RBFS_BootblockSysStartupCode_ON))

  #include "RBSYS_BBStackHandling.h"

  static void RBSYS_BBStartupPreOSPhase1(void);
  #if (RBFS_MCORE == RBFS_MCORE_ON)
    static void RBSYS_BBFreezePE2(void);
  #endif


  RBSYS_ATTR_NO_PROLOGUE
  __attribute__((noinline)) void RBSYS_BBStartupPreOSPhase0(void)
  {
    RBSYS_registerInit();       /* uC register initialization */

    RBSYS_SDA_registerInit();   /* initialize Small Data Area (SDA) base registers (gp/tp) within BB context */

    /* SW Workaround for connected GHS debugger, which starts always PE1 and PE2 together independent
     * of SW trigger via RBSYS_StartPE2(). At least local RAM of PE1 must be opened for PE2,
     * because Backup RAM belongs to that and could be accessed during bootblock start-up */
    RBSYS_BasicGuardInit(); /* Set SPID, Core 0 could already have locked his LRAM or the CRAM */
    RBSYS_ClearLRAM();         /* LRAM Zeroing is performed under certain conditions only (see RBSYS_ClearLRAM) */

    // Initialize Stack Pointer
    RBSYS_stackInit(RB_SP0_Bootblock, RB_SP1_Bootblock);

    if( RBSYS_getCoreID() == RBSYS_CORE_ID_0 )
    {
      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        RBSYS_SetupClocks_RenesasU2A(); /* Ramp up Clock to be operated from PLL (if not done by hardware). Must be before start of TPTM (TPTM is based on CPU_CLK) */
      #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
        RBSYS_SetWaitStatesForOperationAtLowSpeed();
        RBSYS_SetupPLLs(); /* Ramp up Clock to be operated from PLL. Must be before RBSYS_ClearGRAM */
        // todo: resort this, could be optimiyed by first configuring PLLs
        RBSYS_EnablePeripherals();
        RBSYS_DisableWatchdog();
        RBSYS_ConfigureResetReactions();
      #endif

      RBSYS_SetBusMasterIDs();                /* set the applicable IDs (e.g. Flexray, Ethernet etc.) to unsafe as precondition for below guard configuration. */
      #if( RBFS_RBSYSGlobalRAMGuardsBB == RBFS_RBSYSGlobalRAMGuardsBB_ON )
        RBSYS_GRAMGuardInit();
      #endif

      /* Hint: Any other guards will not be initialized in BMGR to reduce size. RBSYS_EnhancedGuardInit will be called within BBInitHWandHSW_UB. */
      RBSYS_ClearGRAM();        /* GRAM Zeroing is performed under certain conditions only (see RBSYS_ClearGRAM) */

      RBSYS_SetupPeripheralClocks();  /* Setup Peripheral frequencies */

      #if( RBFS_BackupRAMLayout == RBFS_BackupRAMLayout_V1 )
        RBSYS_BackupRAM_BB_ResetFlagHandlingForRBECM(); // Store Reset Flags to BBFSW Backup RAM
      #endif

      // Cleanup Reset factors (has to be done before using RBSYS_isSWReset* APIs)
      // initial issue: undervoltage detected by ASIC leads to Terminal Reset (see defect 181338)
      RBSYS_ClearResetFactorsAtStartup();
    }

    #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      RBSYS_OtherGuardsInit(); // Enable access to LLPP and Flash interface
    #endif

    RBSYS_BBStartupPreOSPhase1();
  }


  /* called when stacks are set-up by all PEs */
  RBSYS_ATTR_NO_PROLOGUE
  static __attribute__((noinline)) void RBSYS_BBStartupPreOSPhase1(void)
  {
    unsigned int core_id = RBSYS_getCoreID();

    #if (RBFS_MCORE == RBFS_MCORE_ON)

      /* Special handling of second core:
       *  - Workaround for VLAB uC Simulation or connected GHS debugger, which starts always PE1 and PE2 together
       *    independent of SW trigger via RBSYS_StartPE2()
       *  - Additional bootblock handling in real M-Core environment: Only PE1 is required for bootblock functionality,
       *    therefore only PE1 calls RB_JumpToBBMain and PE2 will be halted here in an endless loop. Jumping later to
       *    application must always be done via a SW reset trigger from PE1 and this of course resets also PE2.
       */
      if (core_id == RBSYS_CORE_ID_1)
      {
        // todo: remove PE1/PE2 naming inside RBSYS in total
        RBSYS_BBFreezePE2();         //< Freeze here, to wait until Core0 has completed BMGR and started Core1 from Application
        RBSYS_BBJumpToApplication(); //< Core 1 is not used in BB, therefore can directly jump into Application once released by RBSYS_BBFreezePE2
      }

    #endif

    /* Core0: Check if bootblock has to be left immediately:
     *         - bootblock must be left always via software application reset to application software
     *         - bootblock start-up request info is stored in backup RAM
     * Hint: Cores != Core_0 could never reach this code below
     */
    {
      boolean isSWApplicationReset = RBSYS_isSWResetByApplicationReset();
      boolean isSkipBootblockRequest = (RBSYS_getBootblockRequest() == RBSYS_SKIP_BOOTBLOCK);
      if (isSWApplicationReset && isSkipBootblockRequest)
      {
        RBSYS_BBJumpToApplication();
        
        // Jump to Application if Core 0 has reset the system and prepared the BURAM Jump information
      }
    }


    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      /* todo: check if FSW config is ok for BB or if also ECM FEINT should be masked
       * current setting: configure only ECM interrupts as FEINT ==> must be done before STM initialization */
      RBSYS_maskFEINT();
    #endif

    #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
      /* SW workaround for Renesas RH850 Write Transaction Buffer HW Errata - see Renesas Errata RB113 "WT-Buffer data overwrite" */
      RBSYS_WTBufErrataHandling();
    #endif

    #if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2))
      /* configure clock tree to ensure cycle accurancy between production and emulation device */
      RBSYS_SetupClocks_RenesasP1x();
      RBSYS_DisableInstructionCache();
    #endif



    /* STM must be initialized after masking FEINT */
    RBSYS_InitTimers();

    #if (RBFS_CPUMisalignedAccessSupport == RBFS_CPUMisalignedAccessSupport_ON)
      /* configure behavior for misaligned r/w accesses */
      RBSYS_ConfigureAlignmentReaction();
    #endif

    // calls the GHS cinit routine and afterwards return to bootblock specific main function
    _start();

  }


  /* -------------------------------------------------------------------------- */
  /* QAC|DEV xxxx: main() function with 3 arguments (freestanding environment)  */
  /* -------------------------------------------------------------------------- */
  /* Msg 0601: Function 'main()' is not of type 'int (void)' or                 */
  /*           'int (int, char *[])                                             */
  /* In a freestanding environment the name and type of the function called     */
  /* at program startup are implementation-defined. (according C Standard)      */
  /* -------------------------------------------------------------------------- */
  #ifdef __QAC__
    #pragma PRQA_MESSAGES_OFF 601
  #endif


 /* Symbol main is twice available, but bootblock is a separate build run and therefore
  * no conflict with FSW main will occur.
  * main() will only be executed by Core0
  */
  RBSYS_ATTR_NO_PROLOGUE


  int main(int argc, char ** argv, char **envp)
  {
    #if( (RBFS_CompilationLanguage == RBFS_CompilationLanguage_PureCPP) \
      || (RBFS_CompilationLanguage == RBFS_CompilationLanguage_MixedCandCPP) )
      _main(); // call C++ constructors from one core (Core 0) - main is only executed on Core0
    #endif

    /* configure ECLK to default value (=> main is only called by core 0) */
    RBSYS_SetupECP(RBSYS_ECLK_DEFAULT_KHZ);

    #if( RBFS_DataFlashECC == RBFS_DataFlashECC_Disabled )
      RBSYS_deactivateDataFlashECC();
    #endif

    /* jump to specific bootblock code, but never return here - bootblock must always be left via a software reset */
    RB_JumpToBBMain();

    /* return statement unreachable (=> failure case) */
    return 1;
  }

  #ifdef __QAC__
    #pragma PRQA_MESSAGES_ON 601
  #endif


  #if (RBFS_MCORE == RBFS_MCORE_ON)
    /**
     * @brief Special bootblock handling of second core
     *
     *  - Workaround for VLAB uC Simulation or connected GHS debugger, which starts always PE1 and PE2 together
     *    independent of SW trigger via RBSYS_StartPE2()
     *  - Additional bootblock handling in real M-Core environment: Only Core0 is required for bootblock functionality,
     *    therefore only Core0 calls RB_JumpToBBMain and Core1 will be halted here in an endless loop. After Core0 has
     *    finished bootblock handling and has entered Application, it will signal the Core1 to continue execution 
     *    (RBSYS_MultiCoreSync_IsCore1Released).
     *
     * @return void
     */
    static void RBSYS_BBFreezePE2(void)
    {
      /* wait until other Cores are released */
      while( RBSYS_MultiCoreSync_IsCore1Released() == FALSE )
      {
        RBSYS_SNOOZE_LOOP(5);
        RBSYS_TEST_INJECTION_ReleaseOtherCores();
      }
    }
  #endif

#endif


/* ******************************************************************** */
/* Sanity check for RBFS_BootblockSysStartupCode                        */
/* ******************************************************************** */


/*       ****************************                                                                                   */
/* Note: RBFS_BootblockSysStartupCode has to be set explicitly in CSW-PRsettings for the required parts/build configs   */
/*       ****************************                                                                                   */
#if ((RBFS_BootblockSysStartupCode == RBFS_BootblockSysStartupCode_OFF) && (RBFS_HexBlockBuild == RBFS_HexBlockBuild_BOOTMANAGER))
  #error ("Bootmanager builds require SysStartupCode but switch is set to RBFS_BootblockSysStartupCode_OFF!")
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  #warning("BootblockStartup is not yet supported for Stellar.")
#endif



/** @} */
/* End ingroup RBSYS */
