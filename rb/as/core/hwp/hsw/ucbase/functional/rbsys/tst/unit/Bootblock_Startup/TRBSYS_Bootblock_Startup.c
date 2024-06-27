#include "SwTest_Global.h"         // for SWT functionality

#include "RBSYS_Config.h"          ///< for RBFS_SysBootblockBuild, RBFS_BootblockSysStartupCode, RBFS_uC

#include "TRBSYS_GHS.h"
#include "TRBSYS_BBMain.h"
#include "RBSYS_CpuInfo.h"
#include "RBSYS_CoreInit.h"
#include "TRBSYS_CoreInit.h"
#include "TRBSYS_BBFSW_jump.h"
#include "TRBSYS_TimerSetup.h"
#include "TRBSYS_Intrinsics.h"
#include "TRBSYS_GuardConfig.h"
#include "RBSYS_ClockSettings.h"
#include "TRBSYS_ClockSettings.h"
#include "TRBSYS_StackHandling.h"
#include "TRBSYS_CacheControlIntern.h"
#include "RBSYS_BBFSW_StartupServices.h"
#include "TRBSYS_BBFSW_StartupServices.h"
#include "TRBSYS_uCRegisters.h"
#include "TRBSYS_uCReset.h"

#include "RBSYS_Bootblock_Startup.h"
#include "TRBSYS_Bootblock_Startup_Adaptor.h"


#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )

#if ((RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active) && (RBFS_BootblockSysStartupCode == RBFS_BootblockSysStartupCode_ON))

  static void TRBSYS_InitTimers_CheckTimerAndFEINTMask(void)
  {
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      // ensures that STM is initialized after masking FEINT
      if (RBSYS_getCoreID() == RBSYS_CORE_ID_0) // other cores than Core 0 will not call RBSYS_maskFEINT because they will branch to application before (cannot be simulated in UT)
      {
          SWT_EvalEq(FEINTFMSK0, (RBSYS_P1x_STM_FEINT_MASK | RBSYS_P1x_TERMINAL_NMI_FEINT_MASK));
      }
    #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      // ensures that clocks are setup before TPTM is started
      if( RBSYS_getCoreID() == RBSYS_CORE_ID_0 )
      {
        SWT_EvalEq(SYSCTRLCKSC_CPUS, 0x0u); // RBSYS_SetupClocks_RenesasU2A has been called
      }
      else
      {
        SWT_EvalNeq(SYSCTRLCKSC_CPUS, 0x0u); // RBSYS_SetupClocks_RenesasU2A has not been called
      }
    #endif
  }

  /**
   * \Reference
   *  RBSYS_BBStartupPreOSPhase0, Gen_SWCS_HSW_uC_Base_SYS-173, Gen_SWCS_HSW_uC_Base_SYS-175, Gen_SWCS_HSW_uC_Base_SYS-217,
   *  Gen_SWCS_HSW_uC_Base_SYS-257, Gen_SWCS_HSW_uC_Base_SYS-255, Gen_SWCS_HSW_uC_Base_SYS-268, Gen_SWCS_HSW_uC_Base_SYS-329
   *
   * \Purpose
   *  uC startup initialization of core 0 within bootblock
   *
   * \Sequence
   *  Simulate core0
   *  Call function RBSYS_BBStartupPreOSPhase0()
   *
   * \ExpectedResult
   *  - uC register must be initialized via function RBSYS_registerInit()
   *  - Small Data Area (SDA) base registers must be initialized via function RBSYS_SDA_registerInit()
   *  - U2A: Clear LRAM, BURAM, CRAM0 to CRAM3 as there is no HW based zeroing on U2A devices
   *  - Stack pointer must be initialized via function RBSYS_stackInit
   *  - Open local RAM for other core via function RBSYS_BB_BasicGuardInit()
   *  - P1x:
   *    - Ensure that Fatal-Error-Interrups (FEINT) from System Timer is masked in bootblock via function RBSYS_maskFEINT()
   *    - WT Buffer HW Errata must be handled in case of GRAM availability via function RBSYS_WTBufErrataHandling()
   *    - In case of an D1 or D2 software the cycle accurancy between production and emulation device must be ensured
   *      via function call RBSYS_SetupClocks_RenesasP1x and RBSYS_DisableInstructionCache
   *  - U2A: Ensure that clocks are setup (e.g. clock gear up done) before system timer TPTM is started
   *  - System Timer must be initialized via RBSYS_InitTimers() after masking FEINT (masking is verified in RBSYS_InitTimers)
   *  - P1x: configure behavior for misaligned r/w accesses via function RBSYS_ConfigureAlignmentReaction()
   *  - GHS cinit routine must be called
   */
  SWTEST void TRBSYS_Bootblock_Startup_Core0(void)
  {
    TRBSYS_InitTimers_Callback = TRBSYS_InitTimers_CheckTimerAndFEINTMask;
    TRBSYS_setCoreID(RBSYS_CORE_ID_0);
    RBSYS_BBStartupPreOSPhase0();

    // functions called in RBSYS_BBStartupPreOSPhase0
    SWT_EvalEq(TRBSYS_registerInit_cnt, 1);
    SWT_EvalEq(TRBSYS_SDA_registerInit_cnt, 1);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      SWT_EvalEq(TRBSYS_ClearLRAM_cnt[0], 1);
      #if( RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON )
        SWT_EvalEq(TRBSYS_ClearCRAM0_cnt, 1);
      #endif
      #if( RBFS_RenesasU2aCRAM1 == RBFS_RenesasU2aCRAM1_ON )
        SWT_EvalEq(TRBSYS_ClearCRAM1_cnt, 1);
      #endif
      #if( RBFS_RenesasU2aCRAM2 == RBFS_RenesasU2aCRAM2_ON )
        SWT_EvalEq(TRBSYS_ClearCRAM2_cnt, 1);
        SWT_EvalEq(TRBSYS_ClearBURAM_cnt, 1);
      #endif
      #if( RBFS_RenesasU2aCRAM3 == RBFS_RenesasU2aCRAM3_ON )
        SWT_EvalEq(TRBSYS_ClearCRAM3_cnt, 1);
      #endif
    #endif
    SWT_EvalEq(TRBSYS_stackInit_cnt, 1);

    // functions called in RBSYS_BBStartupPreOSPhase1
    SWT_EvalEq(TRBSYS_setCoreSPID2SafeSPID_cnt[0], 1);
    SWT_EvalEq(TRBSYS_PBUSGuardInit_ForPEGuard_cnt[0], 1);
    SWT_EvalEq(TRBSYS_PEGuardInit_cnt[0], 1);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEq(FEINTFMSK0, (RBSYS_P1x_STM_FEINT_MASK | RBSYS_P1x_TERMINAL_NMI_FEINT_MASK));// RBSYS_maskFEINT has been called

      #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
        SWT_EvalEq(TRBSYS_WTBufErrataHandling_cnt, 1);
      #endif

      #if ( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2) )
        SWT_EvalEq(TRBSYS_SetupClocks_RenesasP1x_cnt, 1);
        SWT_EvalEq(TRBSYS_DisableInstructionCache_cnt, 1);
      #endif
    #endif

    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      SWT_EvalEq(SYSCTRLCKSC_CPUS, 0x0u); // RBSYS_SetupClocks_RenesasU2A has been called
    #endif

    SWT_EvalEq(TRBSYS_InitTimers_cnt, 1);
    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_CPUMisalignedAccessSupport == RBFS_CPUMisalignedAccessSupport_ON) )
      SWT_EvalEq(RBSYS_STSR(RBSYS_MCTL_REGID, RBSYS_MCTL_SELID) & 0x2u, 0x2u); // RBSYS_ConfigureAlignmentReaction has been called
    #endif
    SWT_EvalEq(TRBSYS_start_cnt, 1);
  }

  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
    /**
    * \Reference
    *  RBSYS_ClearBURAM, Gen_SWCS_HSW_uC_Base_SYS-329
    *
    * \Purpose
    *  Ensure BURAM zeroing
    *
    * \Sequence
    *  Call function RBSYS_BBStartupPreOSPhase0
    *
    * \ExpectedResult
    *  Function RBSYS_ClearBURAM must be called even if Application Reset AND Terminal Reset was done
    *  Hint: Terminal Reset overrules Application Reset but keeps the reset flag
    */
    SWTEST void TRBSYS_ClearBURAM_BBStartupPreOSPhase(void)
    {
      TRBSYS_setCoreID(0);
      RBSYS_RESF = RBSYS_RESET_FLAG_TERMINAL | RBSYS_RESET_FLAG_SW_APPLICATION_0;
      TRBSYS_ClearBURAM_cnt = 0;

      RBSYS_BBStartupPreOSPhase0();

      SWT_EvalEq(TRBSYS_ClearBURAM_cnt, 1);
      SWT_EvalEq(RBSYS_RESFC, RBSYS_RESET_FLAG_TERMINAL | RBSYS_RESET_FLAG_SW_APPLICATION_0 | RBSYS_RESET_FLAG_SW_SYSTEM_0);
    }
  #endif

  #if (RBFS_RenesasU2aCRAM2 == RBFS_RenesasU2aCRAM2_ON)
    /**
     * \Reference
     *  RBSYS_BBStartupPreOSPhase0, Gen_SWCS_HSW_uC_Base_SYS-330
     *
     * \Purpose
     *  U2A bootblock startup preserving BURAM in case of application reset
     *
     * \Sequence
     *  Simulate core0
     *  Set flag for application reset
     *  Call function RBSYS_BBStartupPreOSPhase0()
     *
     * \ExpectedResult
     *  - RBSYS_ClearBURAM was not called
     */
    SWTEST void TRBSYS_Bootblock_Startup_Core0_ApplicationReset(void)
    {
      TRBSYS_setCoreID(RBSYS_CORE_ID_0);
      TRBSYS_setSWResetByApplicationReset();

      RBSYS_BBStartupPreOSPhase0();

      SWT_EvalEq(TRBSYS_ClearBURAM_cnt, 0);
    }
  #endif

  /**
   * \Reference
   *  RBSYS_BBStartupPreOSPhase0, Gen_SWCS_HSW_uC_Base_SYS-175,
   *
   * \Purpose
   *  Bootblock startup in case of a terminal reset
   *
   * \Sequence
   *  Simulate a terminal reset
   *  Call function RBSYS_BBStartupPreOSPhase0()
   *
   * \ExpectedResult
   *  - Clear "Terminal" and "Software" reset flags to ensure the same start-up sequence in case of a
   *    "Terminal" reset (e.g. undervoltage detected by ASIC) as in case of a real "Power-On" reset
   *  - Ensure that bootblock is called as on real "Power-On" (=> implicit tested via call of GHS cinit routine)
   */
  SWTEST void TRBSYS_Bootblock_Startup_TerminalReset(void)
  {
    TRBSYS_setCoreID(RBSYS_CORE_ID_0);
    TRBSYS_setTerminalReset();

    RBSYS_BBStartupPreOSPhase0();

    // UT does not consider inverse logic (RBSYS_RESF is set and cleared by RBSYS_RESFC)
    SWT_EvalEq(RBSYS_RESFC, (RBSYS_RESET_FLAG_TERMINAL | RBSYS_RESET_FLAG_SW_SYSTEM_0 | RBSYS_RESET_FLAG_SW_APPLICATION_0));
    SWT_EvalEq(TRBSYS_start_cnt, 1);
  }


  /**
   * \Reference
   *  RBSYS_BBStartupPreOSPhase0, Gen_SWCS_HSW_uC_Base_SYS-175,
   *
   * \Purpose
   *  Bootblock startup in case of NON terminal reset
   *
   * \Sequence
   *  Call function RBSYS_BBStartupPreOSPhase0()
   *
   * \ExpectedResult
   *  - Reset flags are not cleared
   *  - Ensure that bootblock is called as on real "Power-On" (=> implicit tested via call of GHS cinit routine)
   */
  SWTEST void TRBSYS_Bootblock_Startup_NoTerminalReset(void)
  {
    RBSYS_BBStartupPreOSPhase0();

    // UT does not consider inverse logic (RBSYS_RESF is set and cleared by RBSYS_RESFC)
    SWT_EvalEq(RBSYS_RESFC, 0);
    SWT_EvalEq(TRBSYS_start_cnt, 1);
  }


  /**
   * \Reference
   *  RBSYS_BBStartupPreOSPhase0, Gen_SWCS_HSW_uC_Base_SYS-175,
   *
   * \Purpose
   *  Bootblock startup in case of software reset to OEM-Bootblock (old interface)
   *
   * \Sequence
   *  1. Simulate request from application to run bootblock and call function RBSYS_BBStartupPreOSPhase0()
   *  2. Simulate software reset and call function RBSYS_BBStartupPreOSPhase0()
   *
   * \ExpectedResult
   *  In both situations application is not called
   */
  SWTEST void TRBSYS_Bootblock_Startup_SoftwareReset(void)
  {
    TRBSYS_setBootblockRequest(RBSYS_FSW_RUN_BOOTBLOCK);
    RBSYS_BBStartupPreOSPhase0();
    SWT_EvalEq(TRBSYS_BBJumpToApplication_cnt, 0);

    TRBSYS_setSoftwareReset();
    RBSYS_BBStartupPreOSPhase0();
    SWT_EvalEq(TRBSYS_BBJumpToApplication_cnt, 0);
  }


  /**
   * \Reference
   *  RBSYS_BBStartupPreOSPhase0, Gen_SWCS_HSW_uC_Base_SYS-175,
   *
   * \Purpose
   *  Bootblock startup in case of software reset to OEM-Bootblock (new interface)
   *
   * \Sequence
   *  1. Simulate request from application to run bootblock and call function RBSYS_BBStartupPreOSPhase0()
   *  2. Simulate software reset and call function RBSYS_BBStartupPreOSPhase0()
   *
   * \ExpectedResult
   *  In both situations application is not called
   */
  SWTEST void TRBSYS_Bootblock_Startup_SoftwareReset2(void)
  {
    TRBSYS_setBootblockRequest(RBSYS_FSW_RUN_OEM_BOOTBLOCK);
    RBSYS_BBStartupPreOSPhase0();
    SWT_EvalEq(TRBSYS_BBJumpToApplication_cnt, 0);

    TRBSYS_setSoftwareReset();
    RBSYS_BBStartupPreOSPhase0();
    SWT_EvalEq(TRBSYS_BBJumpToApplication_cnt, 0);
  }

  /**
   * \Reference
   *  RBSYS_BBStartupPreOSPhase0, Gen_SWCS_HSW_uC_Base_SYS-175,
   *
   * \Purpose
   *  Bootblock startup in case of software reset to RB-Bootblock
   *
   * \Sequence
   *  1. Simulate request from application to run bootblock and call function RBSYS_BBStartupPreOSPhase0()
   *  2. Simulate software reset and call function RBSYS_BBStartupPreOSPhase0()
   *
   * \ExpectedResult
   *  In both situations application is not called
   */
  SWTEST void TRBSYS_Bootblock_Startup_SoftwareReset3(void)
  {
    TRBSYS_setBootblockRequest(RBSYS_FSW_RUN_RB_BOOTBLOCK);
    RBSYS_BBStartupPreOSPhase0();
    SWT_EvalEq(TRBSYS_BBJumpToApplication_cnt, 0);

    TRBSYS_setSoftwareReset();
    RBSYS_BBStartupPreOSPhase0();
    SWT_EvalEq(TRBSYS_BBJumpToApplication_cnt, 0);
  }


  /**
   * \Reference
   *  RBSYS_BBStartupPreOSPhase0, Gen_SWCS_HSW_uC_Base_SYS-175,
   *
   * \Purpose
   *  Application startup in case of sofware reset
   *
   * \Sequence
   *  1. Simulate request to skip bootblock and call function RBSYS_BBStartupPreOSPhase0()
   *  2. Simulate a software reset and call function RBSYS_BBStartupPreOSPhase0()
   *
   * \ExpectedResult
   *  1. Bootblock is still called (=> no software reset)
   *  2. Application is called after software reset in combination with request to skip bootblock
   */
  SWTEST void TRBSYS_Bootblock_Startup_SoftwareReset_SkipBootblock(void)
  {
    TRBSYS_setBootblockRequest(RBSYS_SKIP_BOOTBLOCK);
    RBSYS_BBStartupPreOSPhase0();
    SWT_EvalEq(TRBSYS_BBJumpToApplication_cnt, 0);

    // jump to appl only if "SW reset" + "skip bootblock" is set
    TRBSYS_setSoftwareReset();
    RBSYS_BBStartupPreOSPhase0();
    SWT_EvalEq(TRBSYS_BBJumpToApplication_cnt, 1);
  }


  #if (RBFS_MCORE == RBFS_MCORE_ON)

    /**
     * \Reference
     *  RBSYS_BBStartupPreOSPhase0, Gen_SWCS_HSW_uC_Base_SYS-175,
     *
     * \Purpose
     *  Application startup in case of sofware reset of core 1
     *
     * \Sequence
     *  Simulate a software reset
     *  Simulate request to skip bootblock
     *  Call function RBSYS_BBStartupPreOSPhase0() from core 1
     *
     * \ExpectedResult
     *  - uC register must be initialized via function RBSYS_registerInit()
     *  - Small Data Area (SDA) base registers must be initialized via function RBSYS_SDA_registerInit()
     *  - U2A: Clear LRAM (but nothing else) as there is no HW based zeroing on U2A devices
     *  - Stack pointer must be initialized via function RBSYS_stackInit
     *  - Open local RAM for other core via function RBSYS_BB_BasicGuardInit()
     *  - Application is called via function RBSYS_BBJumpToApplication()
     */
    SWTEST void TRBSYS_Bootblock_Startup_Core1_SkipBootblock(void)
    {
      TRBSYS_setCoreID(RBSYS_CORE_ID_1);

      RBSYS_BBStartupPreOSPhase0();

      // functions called in RBSYS_BBStartupPreOSPhase0
      SWT_EvalEq(TRBSYS_registerInit_cnt, 1);
      SWT_EvalEq(TRBSYS_SDA_registerInit_cnt, 1);
      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        SWT_EvalEq(TRBSYS_ClearLRAM_cnt[1], 1);
        #if( RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON )
          SWT_EvalEq(TRBSYS_ClearCRAM0_cnt, 0);
        #endif
        #if( RBFS_RenesasU2aCRAM1 == RBFS_RenesasU2aCRAM1_ON )
          SWT_EvalEq(TRBSYS_ClearCRAM1_cnt, 0);
        #endif
        #if( RBFS_RenesasU2aCRAM2 == RBFS_RenesasU2aCRAM2_ON )
          SWT_EvalEq(TRBSYS_ClearCRAM2_cnt, 0);
          SWT_EvalEq(TRBSYS_ClearBURAM_cnt, 0);
        #endif
        #if( RBFS_RenesasU2aCRAM3 == RBFS_RenesasU2aCRAM3_ON )
          SWT_EvalEq(TRBSYS_ClearCRAM3_cnt, 0);
        #endif
      #endif
      SWT_EvalEq(TRBSYS_stackInit_cnt, 1);

      // functions called in RBSYS_BBStartupPreOSPhase1
      SWT_EvalEq(TRBSYS_setCoreSPID2SafeSPID_cnt[1], 1);
      SWT_EvalEq(TRBSYS_PBUSGuardInit_ForPEGuard_cnt[1], 1);
      SWT_EvalEq(TRBSYS_PEGuardInit_cnt[1], 1);

      // will be 0 if Core1 has already been released before Core1 starts, otherwise > 0
      SWT_EvalEq(TRBSYS_GetSnoozeLoopCounter(), 5);

      /* actually, Core1 will only jump to application once. As we cannot exit the function early in the unittest, 
       * it may report 2 (if reset flags are matching) */
      SWT_EvalEq(TRBSYS_BBJumpToApplication_cnt, 1);
    }


    /**
     * \Reference
     *  RBSYS_BBStartupPreOSPhase0, Gen_SWCS_HSW_uC_Base_SYS-175,
     *  Gen_SWCS_HSW_uC_Base_SYS-267
     *
     * \Purpose
     *  Verify special bootblock handling of core 1
     *
     *  Hint: Only core 0 is required for bootblock functionality, therefore only core 0 calls RB_JumpToBBMain
     *  and core 1 will be kept in an endless loop. Jumping later to application must always be done
     *  via a SW reset trigger from CPU0 and this of course resets also CPU1.
     *
     * \Sequence
     *  Call function RBSYS_BBStartupPreOSPhase0() from core 1
     *
     * \ExpectedResult
     *  Core 1 must be kept in the endless loop
     */
    SWTEST void TRBSYS_Bootblock_Startup_Core1_0(void)
    {
      TRBSYS_setCoreID(RBSYS_CORE_ID_1);
      TRBSYS_SetAbortSnoozeLoop();

      RBSYS_BBStartupPreOSPhase0();
      SWT_EvalGE(TRBSYS_GetSnoozeLoopCounter(), 1);
    }


    /**
     * \Reference
     *  RBSYS_BBStartupPreOSPhase0, Gen_SWCS_HSW_uC_Base_SYS-175,
     *  Gen_SWCS_HSW_uC_Base_SYS-267
     *
     * \Purpose
     *  Verify special bootblock handling of core 1 in case of software reset
     *
     *  Hint: Only core 0 is required for bootblock functionality, therefore only core 0 calls RB_JumpToBBMain
     *  and core 1 will be kept in an endless loop. Jumping later to application must always be done
     *  via a SW reset trigger from CPU0 and this of course resets also CPU1.
     *
     * \Sequence
     *  Simulate a software reset
     *  Call function RBSYS_BBStartupPreOSPhase0() from core 1
     *
     * \ExpectedResult
     *  Core 1 must be kept in the endless loop
     */
    SWTEST void TRBSYS_Bootblock_Startup_Core1_1(void)
    {
      TRBSYS_setCoreID(RBSYS_CORE_ID_1);
      TRBSYS_setSoftwareReset();
      TRBSYS_SetAbortSnoozeLoop();

      RBSYS_BBStartupPreOSPhase0();
      SWT_EvalGE(TRBSYS_GetSnoozeLoopCounter(), 1);
    }


    /**
     * \Reference
     *  RBSYS_BBStartupPreOSPhase0, Gen_SWCS_HSW_uC_Base_SYS-175,
     *  Gen_SWCS_HSW_uC_Base_SYS-267
     *
     * \Purpose
     *  Verify special bootblock handling of core 1 in case of skip bootblock request only
     *
     *  Hint: Only core 0 is required for bootblock functionality, therefore only core 0 calls RB_JumpToBBMain
     *  and core 1 will be kept in an endless loop. Jumping later to application must always be done
     *  via a SW reset trigger from CPU0 and this of course resets also CPU1.
     *
     * \Sequence
     *  Simulate request to skip bootblock
     *  Call function RBSYS_BBStartupPreOSPhase0() from core 1
     *
     * \ExpectedResult
     *  Core 1 must be kept in the endless loop
     */
    SWTEST void TRBSYS_Bootblock_Startup_Core1_2(void)
    {
      TRBSYS_setCoreID(RBSYS_CORE_ID_1);
      TRBSYS_setBootblockRequest(RBSYS_SKIP_BOOTBLOCK);
      TRBSYS_SetAbortSnoozeLoop();

      RBSYS_BBStartupPreOSPhase0();
      SWT_EvalGE(TRBSYS_GetSnoozeLoopCounter(), 1);
    }

  #endif

  /**
   * \Reference
   *  RBSYS_BBStartupPreOSPhase0, Gen_SWCS_HSW_uC_Base_SYS-175,
   *  Gen_SWCS_HSW_uC_Base_SYS-206
   *
   * \Purpose
   *  Verify ECLK initialization in bootblock
   *
   * \Sequence
   *  Call main() function
   *
   * \ExpectedResult
   *  ECLK must be configured to default value (4MHZ)
   *  RBSYS_deactivateDataFlashECC() was called if RBFS_DataFlashECC_Disabled is configured
   */
  SWTEST void TRBSYS_Bootblock_Startup_main(void)
  {
    SWT_EvalEq(TRBSYS_ECLK_KHZ, 0);

    CallPrivate_main();

    SWT_EvalEq(TRBSYS_ECLK_KHZ, RBSYS_ECLK_DEFAULT_KHZ);
    #if( RBFS_DataFlashECC == RBFS_DataFlashECC_Disabled )
      SWT_EvalEq(ECCDFDFECCCTL, 0x3u); // RBSYS_deactivateDataFlashECC has been called
    #endif
    SWT_EvalEq(TRBSYS_BBJumpToBBMain_cnt, 1);
  }

  #if( (RBFS_CompilationLanguage == RBFS_CompilationLanguage_PureCPP) \
    || (RBFS_CompilationLanguage == RBFS_CompilationLanguage_MixedCandCPP) )

    /**
   * \Reference Gen_SWCS_HSW_uC_Base_SYS-323
   *  main
   *
   * \Purpose
   *  Check if main is calling _main for CPP builds
   *
   * \Sequence
   *  Call main() function
   *
   * \ExpectedResult
   *  _main must have been called exactly once
   */
    SWTEST void TRBSYS_Bootblock_Startup_main_CPP(void)
    {
      CallPrivate_main();

      SWT_EvalEq(TRBSYS_main_cnt, 1);
    }

  #endif

#else

  SWTEST void TRBSYS_Bootblock_Startup_FeatureNotAvailable(void)
  {
    SWT_EvalEx(TRUE, "Feature not Available");
  }

#endif



#else //( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
/**
    * \TestCaseName TRBSYS_Dummy
    *
    * \Reference
    * Dummy
    *
    *
    * \Purpose Dummy testcase for missing Stellar Unittests. To be removed once there are Stellar implementations.
    *
    * \Sequence
    *
    *
    * \ExpectedResult
    *
    */
  SWTEST void TRBSYS_Dummy(void)
  {
      SWT_EvalEx(TRUE, "Feature is not supported for Series yet.");
  }
#endif