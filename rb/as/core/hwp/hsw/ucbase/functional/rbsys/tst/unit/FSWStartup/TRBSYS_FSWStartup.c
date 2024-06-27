#include "SwTest_Global.h"         // for SWT functionality

#include "RBSYS_Config.h"          ///< for RBFS_MCORE, RBFS_RenesasP1xGRAM, RBFS_SysOverwriteEBASE, RBFS_TargetDevice, RBFS_TPSWSVPRestrictions
/* "///< for RBFS" required for our UT framework for compl. disabled UTs via RBFS */

#include "RBSYS_FSWStartup.h"
#include "TRBSYS_FSWStartup_Adaptor.h"

#include "RBSYS_CoreInit.h"
#include "TRBSYS_CoreInit.h"
#include "TRBSYS_CpuInfo.h"
#include "RBSYS_CpuVersions.h"
#include "TRBSYS_StackHandling.h"
#include "TRBSYS_uCRegisters.h"
#include "RBSYS_GuardConfig.h"
#include "TRBSYS_GuardConfig.h"
#include "TRBSYS_TimerSetup.h"
#include "TRBSYS_Intrinsics.h"
#include "TRBSYS_CacheControlIntern.h"
#include "TRBSYS_Os.h"
#include "RBSYS_RAMBackupServiceIntern.h"
#include "TRBSYS_RAMBackupServiceIntern.h"
#include "RBSYS_MultiCoreSync.h"
#include "RBSYS_ClockSettings.h"
#include "TRBSYS_ClockSettings.h"
#include "RBSYS_StartupTimingIntern.h"
#include "TRBLCF_MemoryMap.h"
#include "TRBSYS_GHS.h"
#include "TRBSYS_uCReset.h"
#include "RBSYS_Subsystem.h"
#if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  #include "RBSYS_GuardConfigInternalP1x.h"
#elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
  #include "RBSYS_GuardConfigInternalU2a.h"
#elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
  #include "RBSYS_GuardConfigInternalU2C.h"
#endif

#include "RBSYS_PlantStartupCtrl.h"
#include "RBHSWDEM_Facade.h"
#include "DemStub_Helper.h"
#include "RBSYS_ErrorHooks.h"
#include "TRBSYS_CoreMpu.h"


/**
 * \Reference
 *  RBSYS_registerInit, RBSYS_SDA_registerInit, Gen_SWCS_HSW_uC_Base_SYS-175
 *
 * \Purpose
 *  Ensure correct uC register initialization ...
 *  - to prevent dual core lockstep failure due to uninitialized registers
 *  - to allow Small Data Area (SDA) compiler optimization
 *
 * \Sequence
 *  Call function RBSYS_StartupPreOSPhase0 on each core
 *
 * \ExpectedResult
 *  Function RBSYS_registerInit must be called on each core
 *  Function RBSYS_SDA_registerInit must be called on each core
 */
SWTEST void TRBSYS_registerInit_StartupPreOSPhase(void)
{
  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    CallPrivate_RBSYS_StartupPreOSPhase0();

    SWT_EvalEq(TRBSYS_registerInit_cnt, i+1);
    #if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
      SWT_EvalEq(TRBSYS_SDA_registerInit_cnt, i+1);
    #endif
  }
}


#if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
  /**
   * \Reference
   *  RBSYS_ClearLRAM, RBSYS_ClearCRAM0, RBSYS_ClearCRAM1, RBSYS_ClearCRAM2, RBSYS_ClearCRAM3, RBSYS_ClearBURAM, Gen_SWCS_HSW_uC_Base_SYS-329
   *
   * \Purpose
   *  Ensure LRAM/CRAM zeroing
   *
   * \Sequence
   *  Call function RBSYS_StartupPreOSPhase0 on each core
   *
   * \ExpectedResult
   *  Function RBSYS_ClearLRAM must be called on each core
   *  Function RBSYS_ClearCRAM0-3 and RBSYS_ClearBURAM must be called on core0
   */
  SWTEST void TRBSYS_ClearRAM_StartupPreOSPhase(void)
  {
    int i;

    for (i=0; i<(RB_NUM_CORES); i++)
    {
      TRBSYS_setCoreID(i);
      CallPrivate_RBSYS_StartupPreOSPhase0();

      SWT_EvalEq(TRBSYS_ClearLRAM_cnt[i], 1);
      if(i == 0)
      {
        #if( RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON )
          SWT_EvalEq(TRBSYS_ClearCRAM0_cnt, 1);
        #endif
        #if( RBFS_RenesasU2aCRAM1 == RBFS_RenesasU2aCRAM1_ON )
          SWT_EvalEq(TRBSYS_ClearCRAM1_cnt, 1);
        #endif
        #if( RBFS_RenesasU2aCRAM2 == RBFS_RenesasU2aCRAM2_ON )
          SWT_EvalEq(TRBSYS_ClearCRAM2_cnt, 1);
        #endif
        #if( RBFS_RenesasU2aCRAM3 == RBFS_RenesasU2aCRAM3_ON )
          SWT_EvalEq(TRBSYS_ClearCRAM3_cnt, 1);
        #endif
        SWT_EvalEq(TRBSYS_ClearBURAM_cnt, 1);
      }
    }
  }


  /**
   * \Reference
   *  RBSYS_ClearBURAM, Gen_SWCS_HSW_uC_Base_SYS-329
   *
   * \Purpose
   *  Ensure BURAM zeroing
   *
   * \Sequence
   *  Call function RBSYS_StartupPreOSPhase0 on each core
   *
   * \ExpectedResult
   *  Function RBSYS_ClearBURAM must be called on Core0 even if Application Reset AND Terminal Reset was done
   *  Hint: Terminal Reset overrules Application Reset but keeps the reset flag
   */
  SWTEST void TRBSYS_ClearBURAM_StartupPreOSPhase(void)
  {
    int i;

    for (i=0; i<(RB_NUM_CORES); i++)
    {
      TRBSYS_setCoreID(i);
      RBSYS_RESF = RBSYS_RESET_FLAG_TERMINAL | RBSYS_RESET_FLAG_SW_APPLICATION_0;
      TRBSYS_ClearBURAM_cnt = 0;

      CallPrivate_RBSYS_StartupPreOSPhase0();
      if(i == 0)
      {
        SWT_EvalEq(TRBSYS_ClearBURAM_cnt, 1);
        SWT_EvalEq(RBSYS_RESFC, RBSYS_RESET_FLAG_TERMINAL | RBSYS_RESET_FLAG_SW_APPLICATION_0 | RBSYS_RESET_FLAG_SW_SYSTEM_0);
      }
      else
      {
        SWT_EvalEq(TRBSYS_ClearBURAM_cnt, 0);
      }
    }
  }

  /**
   * \Reference
   *  RBSYS_ClearBURAM, Gen_SWCS_HSW_uC_Base_SYS-330
   *
   * \Purpose
   *  Ensure that BURAM is preserved in case of Software Application Reset
   *
   * \Sequence
   *  Set Software Application Reset
   *  Call function RBSYS_StartupPreOSPhase0 on each core
   *
   * \ExpectedResult
   *  Function RBSYS_ClearBURAM must not be called
   */
  SWTEST void TRBSYS_NoClearBURAM_StartupPreOSPhase(void)
  {
    int i;
    RBSYS_RESF = RBSYS_RESET_FLAG_SW_APPLICATION_0;

    for (i=0; i<(RB_NUM_CORES); i++)
    {
      TRBSYS_setCoreID(i);
      CallPrivate_RBSYS_StartupPreOSPhase0();
    }

    SWT_EvalEq(TRBSYS_ClearBURAM_cnt, 0);
  }
#endif


#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_CyberSecurityBoot != RBFS_CyberSecurityBoot_NonTrusted) )
/**
 * \Reference
 *  RBSYS_ClearLRAM, RBSYS_ClearGRAM
 *
 * \Purpose
    Ensure that LRAM + GRAM is zeroed if we start a TrustedBoot Software
 *
 * \Sequence
 *  Call function RBSYS_StartupPreOSPhase0 on each core
 *
 * \ExpectedResult
 *  Each LRAM must be zeroed
 *  Global RAM must be zeroed by Core 0
 */
SWTEST void TRBSYS_RamClearing_StartupAfterBMGRwoReset(void)
{
  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    CallPrivate_RBSYS_StartupPreOSPhase0();
    SWT_EvalEq(TRBSYS_ClearLRAM_cnt[i], 1); //< RBSYS_ClearLRAM is only called once from each core
  }

  #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
    SWT_EvalEq(TRBSYS_ClearGRAM_cnt, 1);  //< GRAM shall only be zeroed once from Core 0
  #endif
}
#endif

/**
 * \Reference
 *  RBSYS_stackInit, Gen_SWCS_HSW_uC_Base_SYS-175, Gen_SWCS_HSW_uC_Base_SYS-217
 *
 * \Purpose
 *  Ensure initialization of stack pointer
 *
 * \Sequence
 *  Call function RBSYS_StartupPreOSPhase0 on each core
 *
 * \ExpectedResult
 *  Function RBSYS_stackInit must be called twice on each core
 */
SWTEST void TRBSYS_StackInit_StartupPreOSPhase(void)
{
  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);
    CallPrivate_RBSYS_StartupPreOSPhase0();

    SWT_EvalEq(TRBSYS_stackInit_cnt, 2+2*i);  // additionally called in RBSYS_StartupPreOSPhase2
  }
}



static void TRBSYS_InitTimers_CheckFEINTMask(void)
{
  // ensures that STM is initialized after masking FEINT
  #if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    if( RBSYS_getCoreID() == RBSYS_CORE_ID_0 )
    {
      SWT_EvalEq(FEINTFMSK0, (RBSYS_P1x_STM_FEINT_MASK | RBSYS_P1x_TERMINAL_NMI_FEINT_MASK));
    }
    else
    {
      SWT_EvalEq(FEINTFMSK1, (RBSYS_P1x_STM_FEINT_MASK | RBSYS_P1x_TERMINAL_NMI_FEINT_MASK));
    }
  #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    if( RBSYS_getCoreID() == RBSYS_CORE_ID_0 )
    {
      SWT_EvalEq(FEINC_PE0FEINTMSK, (RBSYS_U2A_NMIpin_FEINT_MASK | RBSYS_U2A_TPMT_FEINT_MASK));
    }
    else
    {
      SWT_EvalEq(FEINC_PE1FEINTMSK, (RBSYS_U2A_NMIpin_FEINT_MASK | RBSYS_U2A_TPMT_FEINT_MASK));
    }
  #endif
}

/**
 * \Reference
 *  RBSYS_maskFEINT, RBSYS_maskINT, Gen_SWCS_HSW_uC_Base_SYS-175
 *
 * \Purpose
 *  Interrupts shall be masked during uC start-up
 *
 * \Sequence
 *  Call function RBSYS_StartupPreOSPhase0 on each core
 *
 * \ExpectedResult
 *  Function RBSYS_maskFEINT must be called on each core
 *  Function RBSYS_maskInts must be called on each core
 */
SWTEST void TRBSYS_maskIRQ_StartupPreOSPhase(void)
{
  TRBSYS_InitTimers_Callback = TRBSYS_InitTimers_CheckFEINTMask;

  #if (RBFS_MCORE == RBFS_MCORE_ON)
    TRBSYS_setCoreID(RBSYS_CORE_ID_1);
    CallPrivate_RBSYS_StartupPreOSPhase0();

    #if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      // RBSYS_maskFEINT has been called
      SWT_EvalEq(FEINTFMSK0, 0);
      SWT_EvalEq(FEINTFMSK1, (RBSYS_P1x_STM_FEINT_MASK | RBSYS_P1x_TERMINAL_NMI_FEINT_MASK));
      // RBSYS_maskInts has been called
      SWT_EvalEq(IMR0, 0xFFFFFFFF);
      SWT_EvalEq(IMR1, 0x0);
    #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      // RBSYS_maskFEINT has been called
      SWT_EvalEq(FEINC_PE0FEINTMSK, 0);
      SWT_EvalEq(FEINC_PE1FEINTMSK, (RBSYS_U2A_NMIpin_FEINT_MASK | RBSYS_U2A_TPMT_FEINT_MASK));
      // RBSYS_maskInts has been called
      SWT_EvalEq(INTC1_SELFIMR0, 0xFFFFFFFF);
      SWT_EvalEq(INTC2IMR1, 0x0);
    #endif
  #endif

  TRBSYS_setCoreID(RBSYS_CORE_ID_0);
  CallPrivate_RBSYS_StartupPreOSPhase0();

  #if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    // RBSYS_maskFEINT has been called
    SWT_EvalEq(FEINTFMSK0, (RBSYS_P1x_STM_FEINT_MASK | RBSYS_P1x_TERMINAL_NMI_FEINT_MASK));
    // RBSYS_maskInts has been called
    SWT_EvalEq(IMR1, 0xFFFFFFFF);
  #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    // RBSYS_maskFEINT has been called
    SWT_EvalEq(FEINC_PE0FEINTMSK, (RBSYS_U2A_NMIpin_FEINT_MASK | RBSYS_U2A_TPMT_FEINT_MASK));
    // RBSYS_maskInts has been called
    SWT_EvalEq(INTC2IMR1, 0xFFFFFFFF);
  #endif

}

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_CPUMisalignedAccessSupport == RBFS_CPUMisalignedAccessSupport_ON) )
/**
 * \Reference
 *  RBSYS_ConfigureAlignmentReaction, Gen_SWCS_HSW_uC_Base_SYS-271
 *
 * \Purpose
 *  Ensure configuration for behaviour of misaligned r/w accesses
 *
 * \Sequence
 *  Call function RBSYS_StartupPreOSPhase0 on each core
 *
 * \ExpectedResult
 *  Function RBSYS_ConfigureAlignmentReaction must be called on each core
 */
SWTEST void TRBSYS_ConfigureAlignment_StartupPreOSPhase(void)
{
  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);
    CallPrivate_RBSYS_StartupPreOSPhase0();
    SWT_EvalEq(RBSYS_STSR(RBSYS_MCTL_REGID, RBSYS_MCTL_SELID) & 0x2u, 0x2u); // RBSYS_ConfigureAlignmentReaction has been called
  }
}
#endif

#if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
  /**
   * \Reference
   *  RBSYS_WTBufErrataHandling, Gen_SWCS_HSW_uC_Base_SYS-257
   *
   * \Purpose
   *  Ensure handling of WTBuffer Errata in case of GRAM usage
   *
   * \Sequence
   *  Call function RBSYS_StartupPreOSPhase0 on each core
   *
   * \ExpectedResult
   *  Function RBSYS_WTBufErrataHandling must be called once (typically on master core)
   */
  SWTEST void TRBSYS_WTBufErrataHandling_StartupPreOSPhase(void)
  {
    int i;

    for (i=0; i<(RB_NUM_CORES); i++)
    {
      TRBSYS_setCoreID(i);
      CallPrivate_RBSYS_StartupPreOSPhase0();

      SWT_EvalEq(TRBSYS_WTBufErrataHandling_cnt, 1);
    }
  }
#endif

#if (RBFS_MCORE == RBFS_MCORE_ON)
  static void TRBSYS_BasicGuardInit_OrderCheck(void)
  {
    int coreID = RBSYS_getCoreID();

    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
      /* Basic guard initialization must be done before CPU1 is enabled via RBSYS_StartPE2() */
      if ((coreID == RBSYS_CORE_ID_0) && (RBSYS_BOOTCTRL != 0))
      {
        SWT_EvalEx(FALSE, "Basic guard initialization must be done before CPU1 is enabled via RBSYS_StartPE2()!");
      }
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      /* Basic guard initialization must be done before CPU1 is enabled via RBSYS_StartPE2() */
      if ( (coreID == RBSYS_CORE_ID_0) && ( (MC_ME_CL0.CoreReg.CCTL[0] != 0) || (MC_ME_CL0.CoreReg.CADDR[1] != 0) ) )
      {
        SWT_EvalEx(FALSE, "Basic guard initialization must be done before CPU1 is enabled via RBSYS_StartPE2()!");
      }
    #endif
  }
#endif

/**
 * \Reference
 *  RBSYS_BasicGuardInit
 *
 * \Purpose
 *  Ensure basic guard setup
 *
 * \Sequence
 *  Call function RBSYS_StartupPreOSPhase0 on each core
 *
 * \ExpectedResult
 *  Function RBSYS_BasicGuardInit must be called on each core
 *  Basic guard initialization on CPU0 must be done before CPU1 is enabled via RBSYS_StartPE2()
 */
SWTEST void TRBSYS_BasicGuardInit_StartupPreOSPhase(void)
{
  int i;
  #if (RBFS_MCORE == RBFS_MCORE_ON)
    TRBSYS_setCoreSPID2SafeSPID_Callback = TRBSYS_BasicGuardInit_OrderCheck;
  #endif

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);
    CallPrivate_RBSYS_StartupPreOSPhase0();

    // RBSYS_BasicGuardInit has been called
    #if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
      SWT_EvalEq(TRBSYS_setCoreSPID2SafeSPID_cnt[i], 1);
    #else
      #warning("SPID concept has to be reworked for Stellar.")
    #endif
    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
      SWT_EvalEq(TRBSYS_PBUSGuardInit_ForPEGuard_cnt[i], 1);
      SWT_EvalEq(TRBSYS_PEGuardInit_cnt[i], 1);
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      SWT_EvalEq(TRBSYS_LRAMGuardInit_cnt[i], 1);
    #endif
  }
}


#if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2))
  /**
   * \Reference
   *  RBSYS_SetupClocks_RenesasP1x, Gen_SWCS_HSW_uC_Base_SYS-255,
   *  RBSYS_DisableInstructionCache, Gen_SWCS_HSW_uC_Base_SYS-268
   *
   * \Purpose
   *  Cycle accurate behaviour with production devices D1/D2 and corresponding emulation device
   *
   * \Sequence
   *  Call function RBSYS_StartupPreOSPhase0 on master core
   *
   * \ExpectedResult
   *  Function RBSYS_SetupClocks_RenesasP1x must be called once
   *  Function RBSYS_DisableInstructionCache must be called once
   */
  SWTEST void TRBSYS_D1_D2_StartupPreOSPhase(void)
  {
    TRBSYS_setCoreID(RBSYS_CORE_ID_0);
    CallPrivate_RBSYS_StartupPreOSPhase0();

    SWT_EvalEq(TRBSYS_SetupClocks_RenesasP1x_cnt, 1);
    SWT_EvalEq(TRBSYS_DisableInstructionCache_cnt, 1);
  }
#endif

#if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
  /**
   * \Reference
   *  RBSYS_SetupClocks_RenesasU2A, Gen_SWCS_HSW_uC_Base_SYS-314
   *
   * \Purpose
   *  Configuration of CPU clock
   *
   * \Sequence
   *  Call function RBSYS_StartupPreOSPhase0 on master core
   *
   * \ExpectedResult
   *  Function RBSYS_SetupClocks_RenesasU2A must be called once
   */
  SWTEST void TRBSYS_RenesasU2A_StartupPreOSPhase(void)
  {
    TRBSYS_setCoreID(RBSYS_CORE_ID_0);
    CallPrivate_RBSYS_StartupPreOSPhase0();

    SWT_EvalEq(SYSCTRLCKSC_CPUS, 0); // RBSYS_SetupClocks_RenesasU2A has been called
  }
#endif


/**
 * \Reference
 *  RBSYS_InitTimers, Gen_SWCS_HSW_uC_Base_SYS-173
 *  Gen_SWFS_0979_HSW_OverallRequirements_3677
 *
 * \Purpose
 *  Ensure initialization of system timer
 *
 * \Sequence
 *  Call function RBSYS_StartupPreOSPhase0 on each core
 *
 * \ExpectedResult
 *  Function RBSYS_InitTimers must be called once
 */
SWTEST void TRBSYS_InitTimer_StartupPreOSPhase(void)
{
  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);
    CallPrivate_RBSYS_StartupPreOSPhase0();

    SWT_EvalEq(TRBSYS_InitTimers_cnt, i+1);
  }
}

#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
  #if (RBFS_MCORE == RBFS_MCORE_ON)
    /**
    * \Reference
    *  RBSYS_StartPE2, Gen_SWCS_HSW_uC_Base_SYS-282
    *
    * \Purpose
    *  CC CUBE MCORE devices are only starting initially the master core. Therefore the master core must trigger the start of the second core
    *
    * \Sequence
    *  Call function RBSYS_StartupPreOSPhase0 on each core
    *
    * \ExpectedResult
    *  Due to current constraints it must be ensured that CPU1 is started minimum 50us after CPU0
    *  CPU1 shall be triggered via BOOTCTRL register
    */
    SWTEST void TRBSYS_StartCPU1_StartupPreOSPhase(void)
    {
      int i;

      for (i=0; i<(RB_NUM_CORES); i++)
      {
        // clear TRBSYS_wait_time and BOOTCTRL
        TRBSYS_wait_time = 0;
        RBSYS_BOOTCTRL = 0;


        TRBSYS_setCoreID(i);
        CallPrivate_RBSYS_StartupPreOSPhase0();

        if (i == 0)
        {
          SWT_EvalEq(TRBSYS_wait_time, 50);
          SWT_EvalEq(RBSYS_BOOTCTRL, RBSYS_BOOT_CPU1);
        } else
        {
          SWT_EvalEq(TRBSYS_wait_time, 0);
          SWT_EvalEq(RBSYS_BOOTCTRL, 0);
        }
      }
    }
  #endif
#else
  #warning("StartPE2 Unittest is missing")
#endif


#if (RBFS_SysOverwriteEBASE == RBFS_SysOverwriteEBASE_ON)
  /**
   * \Reference
   *  RBSYS_EBASE, Gen_SWCS_HSW_uC_Base_SYS-272
   *
   * \Purpose
   *  Initialize routing of interrupts via EBASE (exception base register)
   *
   * \Sequence
   *  Call function RBSYS_StartupPreOSPhase0 on each core
   *
   * \ExpectedResult
   *  EBASE register is initialized to FSWStart address on each core
   */
  SWTEST void TRBSYS_EBASE_main_Core0(void)
  {
    int i;
    for (i=0; i<(RB_NUM_CORES); i++)
    {
      TRBSYS_setCoreID(i);

      CallPrivate_RBSYS_StartupPreOSPhase0();
      CallPrivate_main();

      SWT_EvalEq(TRBSYS_GetSystemRegister(3,1), (uint32)&FSWStart);
    }
  }
#endif


/**
 * \Reference
 *  RBSYS_SetupECP, Gen_SWCS_HSW_uC_Base_SYS-206
 *
 * \Purpose
 *  Ensure correct ECLK configuration
 *
 * \Sequence
 *  Call function RBSYS_StartupPreOSPhase0 on each core
 *  Call function main on each core
 *
 * \ExpectedResult
 *  ECLK must be configured to default value (4MHz)
 *  Function RBSYS_SetupECP shall be called only once by master core
 */
SWTEST void TRBSYS_ECLK_main(void)
{
  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    CallPrivate_RBSYS_StartupPreOSPhase0();
    CallPrivate_main();

    SWT_EvalEq(TRBSYS_ECLK_KHZ, RBSYS_ECLK_DEFAULT_KHZ);
    SWT_EvalEq(TRBSYS_SetupECP_cnt, 1);  // called only once by master core
  }
}


/**
 * \Reference
 *  RBSYS_setGoodCheckRequest
 *
 * \Purpose
 *  Verify good check request for RBSYS_SYSErrorHook, RBSYS_OSErrorHook and RBSYS_TaskOverRun
 *
 * \Sequence
 *  Call RBSYS_StartupPreOSPhase0 and main function on each core
 *
 * \ExpectedResult
 *  Ensure that for each mentioned failure word above the function RBSYS_setGoodCheckRequest is called once
 */
SWTEST void TRBSYS_GoodCheckRequest_main(void)
{
  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    CallPrivate_RBSYS_StartupPreOSPhase0();
    CallPrivate_main();
  }

  SWT_EvalEq(DemStub_GetNumOfReportPassedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 1);
  SWT_EvalEq(DemStub_GetNumOfReportPassedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_OSErrorHook), 1);
  SWT_EvalEq(DemStub_GetNumOfReportPassedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);
}


/**
 * \Reference
 *  RBSYS_setGoodCheckRequest
 *
 * \Purpose
 *  Verify good check request in case of SW reset from FSW for RBSYS_SYSErrorHook, RBSYS_OSErrorHook and RBSYS_TaskOverRun
 *
 * \Sequence
 *  Simulate SW reset by FSW
 *  Call RBSYS_StartupPreOSPhase0 and main function on each core
 *
 * \ExpectedResult
 *  Ensure that for each mentioned failure word above the function RBSYS_setGoodCheckRequest is called once
 */
SWTEST void TRBSYS_GoodCheckRequest_main2(void)
{
  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);
    TRBSYS_setSWResetTriggeredByFSW();

    CallPrivate_RBSYS_StartupPreOSPhase0();
    CallPrivate_main();
  }

  SWT_EvalEq(DemStub_GetNumOfReportPassedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 1);
  SWT_EvalEq(DemStub_GetNumOfReportPassedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_OSErrorHook), 1);
  SWT_EvalEq(DemStub_GetNumOfReportPassedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_TaskOverRun), 1);
}




/**
 * \Reference
 *  RBSYS_setGoodCheckRequest
 *
 * \Purpose
 *  Verify that GoodCheck is not done if SYSErrorHook failure was reported before
 *
 * \Sequence
 *  Prepare RBSYS_IsSYSErrorHookFailureReported such that it returns TRUE
 *  Call RBSYS_StartupPreOSPhase0 and main function on each core
 *
 * \ExpectedResult
 *  Ensure that GoodCheck was not called for SYSErrorHook
 */
SWTEST void TRBSYS_GoodCheckRequest_main4(void)
{
  int i;
  RBSYS_setSYSErrorHook(0,0);

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    CallPrivate_RBSYS_StartupPreOSPhase0();
    CallPrivate_main();
  }

  SWT_EvalEq(DemStub_GetNumOfReportPassedErrorStatusCalls(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0);
}

#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
  /**
  * \Reference
  *  RBSYS_InitFPU, Gen_SWCS_HSW_uC_Base_SYS-174
  *
  * \Purpose
  *  Ensure initialization of HW Floating Point Unit (FPU)
  *
  * \Sequence
  *  Call function RBSYS_StartupPreOSPhase0 on each core
  *  Call function main on each core
  *
  * \ExpectedResult
  *  Function RBSYS_InitFPU must be called on each core
  */
  SWTEST void TRBSYS_FPU_main(void)
  {
    int i;

    for (i=0; i<(RB_NUM_CORES); i++)
    {
      TRBSYS_setCoreID(i);

      CallPrivate_RBSYS_StartupPreOSPhase0();
      CallPrivate_main();

      SWT_EvalEq((RBSYS_STSR(RBSYS_PSW_REGID,RBSYS_PSW_SELID) & 0x00010000u), 0x00010000u); // RBSYS_InitFPU has been called
    }
  }
#else
  #warning("FPU configuration Unittest is missing")
#endif

#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
  /**
  * \Reference
  *  RBSYS_CoreMpu_Init
  *
  * \Purpose
  *  Ensure initialization of Memory Protection Unit (MPU)
  *
  * \Sequence
  *  Call function RBSYS_StartupPreOSPhase0 on each core
  *  Call function main on each core
  *
  * \ExpectedResult
  *  Function RBSYS_CoreMpu_Init must be called on each core
  */
  SWTEST void TRBSYS_CoreMpu_Init_main(void)
  {
    int i;

    for (i=0; i<(RB_NUM_CORES); i++)
    {
      TRBSYS_setCoreID(i);

      CallPrivate_RBSYS_StartupPreOSPhase0();
      CallPrivate_main();

      SWT_EvalEq(RBSYS_CoreMpu_Init_CallCnt, i+1); // RBSYS_CoreMpu_Init has been called
    }
  }
#endif


/**
 * \Reference
 *  Os_InitializeVectorTable, StartOS
 *
 * \Purpose
 *  Ensure correct OS start-up
 *
 * \Sequence
 *  Call function RBSYS_StartupPreOSPhase0 on each core
 *  Call main function on each core
 *
 * \ExpectedResult
 *  OS API "Os_InitializeVectorTable()" must be called on each core
 *  Operating System must be started via API "StartOS()" on each core
 */
SWTEST void TRBSYS_StartOS(void)
{
  int i;

  for (i=0; i<(RB_NUM_CORES); i++)
  {
    TRBSYS_setCoreID(i);

    CallPrivate_RBSYS_StartupPreOSPhase0();
    CallPrivate_main();

    SWT_EvalEq(TRBSYS_Os_InitializeVectorTable_cnt, i+1);
    SWT_EvalEq(TRBSYS_StartOS_cnt, i+1);
  }
}


#if (RBFS_MCORE == RBFS_MCORE_ON)
  /**
   * \Reference
   *  StartCore
   *
   * \Purpose
   *  Ensure correct OS MCORE start-up
   *
   * \Sequence
   *  Call function RBSYS_StartupPreOSPhase0 on master core (=> core0 is master core)
   *  Call main function on master core
   *
   * \ExpectedResult
   *  OS API "StartCore" must be called from master core for itself and at least one other core - typically for all cores.
   */
  SWTEST void TRBSYS_Os_StartCore_MCORE(void)
  {
    int i;

    TRBSYS_setCoreID(RBSYS_CORE_ID_0);

    CallPrivate_RBSYS_StartupPreOSPhase0();
    CallPrivate_main();

    for (i=0; i<(RB_NUM_CORES); i++)
    {
      SWT_EvalEq(TRBSYS_StartCore_cnt[i], 1);
    }
  }

  #if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  /**
   * \Reference
   *  Os_AwaitStartup
   *
   * \Purpose
   *  Ensure correct OS MCORE start-up
   *
   * \Sequence
   *  Call function RBSYS_StartupPreOSPhase0 on each core
   *  Call main function on each core
   *
   * \ExpectedResult
   *  OS callback routine "Os_AwaitStartup" must be called from all non master cores (=> core0 is master core)
   */
  SWTEST void TRBSYS_Os_AwaitStartup_P1x(void)
  {
    int i;

    for (i=0; i<(RB_NUM_CORES); i++)
    {
      TRBSYS_setCoreID(i);

      CallPrivate_RBSYS_StartupPreOSPhase0();
      CallPrivate_main();

      SWT_EvalEq(TRBSYS_Os_AwaitStartup_cnt, i);
    }
  }
  #endif

  #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    /**
     * \Reference
     *  Os_AwaitStartup
     *
     * \Purpose
     *  Ensure correct OS U2A start-up
     *
     * \Sequence
     *  Call function RBSYS_StartupPreOSPhase0 on each core
     *  Call main function on each core
     *
     * \ExpectedResult
     *  OS API "Os_AwaitStartup" must be called from slave core.
     */
    SWTEST void TRBSYS_Os_AwaitStartup_U2A(void)
    {
      int i;

      for (i=0; i<(RB_NUM_CORES); i++)
      {
        TRBSYS_setCoreID(i);

        CallPrivate_RBSYS_StartupPreOSPhase0();
        CallPrivate_main();
        if(i == 0)
        {
          SWT_EvalEq(TRBSYS_Os_AwaitStartup_cnt, 0);
        }
        else
        {
          SWT_EvalEq(TRBSYS_Os_AwaitStartup_cnt, i);
        }
      }
    }
  #endif /* RBFS_uCFamily_RenesasU2A */
#endif /* RBFS_MCORE_ON */


/**
 * \Reference
 *  RBSYS_restoreBaseOSRequestFromBackupRAM, Gen_SWCS_HSW_uC_Base_SYS-223
 *
 * \Purpose
 *  Previous BaseOS request must be restored during startup in case of SW reset
 *
 * \Sequence
 *  Call function RBSYS_StartupPreOSPhase0 together with main on master core in case of HW reset
 *  Call function RBSYS_StartupPreOSPhase0 together with main on master core in case of SW reset
 *
 * \ExpectedResult
 *  Function RBSYS_restoreBaseOSRequestFromBackupRAM and RBSYS_restoreSkipBootblockRequesterFromBackupRAM must be called once in case of SW reset
 */
SWTEST void TRBSYS_SwReset_main(void)
{
  TRBSYS_setCoreID(RBSYS_CORE_ID_0);

  CallPrivate_RBSYS_StartupPreOSPhase0();
  CallPrivate_main();
  SWT_EvalEq(TRBSYS_restoreBaseOSRequestFromBackupRAM_cnt, 0);
  SWT_EvalEq(TRBSYS_restoreSkipBootblockRequesterFromBackupRAM_cnt, 0);

  TRBSYS_setSoftwareReset();
  CallPrivate_main();
  SWT_EvalEq(TRBSYS_restoreBaseOSRequestFromBackupRAM_cnt, 1);
  SWT_EvalEq(TRBSYS_restoreSkipBootblockRequesterFromBackupRAM_cnt, 1);
}

    /**
     * \Reference
     *  RBSYS_StartupPreOSPhase0, RBSYS_StartupPreOSPhase1, RBSYS_StartupPreOSPhase2, RBSYS_StartupPreOSPhase3
     *
     * \Purpose
     *  Ensure correct OS U2A start-up
     *
     * \Sequence
     *  Call RBSYS_StartupPreOSPhase0
     *  Call RBSYS_PRC_FSW_FinalGuard_Init (normally called in init)
     *  Eval BasicGuardInit is called on every core
     *  Eval FinalGuardInit is called on every core
     *  Eval EnhancedGuardInit is called on one core only
     *
     * \ExpectedResult
     *  see \Sequence
     */
SWTEST void TRBSYS_FSWStartup_GuardInitialization(void)
{
  uint32 i;

  for(i=0; i<RB_NUM_CORES; i++)
  {
    TRBSYS_setCoreID(i);
    CallPrivate_RBSYS_StartupPreOSPhase0();
    RBSYS_PRC_FSW_FinalGuard_Init(); //< not called during PreOSPhases, shall be called during init phase on every core
  }

  for(i=0; i<RB_NUM_CORES; i++)
  {
    // Basic Guard Init is called by every core
    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
      SWT_EvalEq(TRBSYS_setCoreSPID2SafeSPID_cnt[i], 1);
      SWT_EvalEq(TRBSYS_PBUSGuardInit_ForPEGuard_cnt[i], 1);
      SWT_EvalEq(TRBSYS_PEGuardInit_cnt[i], 1);
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      SWT_EvalEq(TRBSYS_LRAMGuardInit_cnt[i], 1);
    #endif
    // Final Guard Init is called by every core
    SWT_EvalEq(TRBSYS_FSW_FinalGuardInit_cnt[i], 1);
  }

  TRBSYS_setCoreID(0);

  // GRAM Guard Init is only called by one core
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    #if(((RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2)) || (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD3ED))
      SWT_EvalEq(HSSPIDRG0, UnSafeSPID);
    #endif
    SWT_EvalEq(APBFSGDSPID_SP4_B, RBSYS_SPID_SAFE_MASK);
    #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
      SWT_EvalEq(MGDGRBAD0, RBSYS_GUARDREGION0_BASEADDR);
    #endif
  #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
    SWT_EvalEq(SPIDCTLBM23SPID, UnSafeSPID);
    #if( RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON )
      SWT_EvalEq(GUARD_CRAMCRG0CRGBAD0, RBSYS_CRG0_GUARDREGION0_BASEADDR & RBSYS_CRG0_VALID_BITS);
    #endif
  #endif

  // Enhanced Guard Init is only called by one core
  SWT_EvalEqX(RBSYS_EnhancedGuardInit_cnt[0], 1); // called by Core 0
  SWT_EvalEqX(RBSYS_EnhancedGuardInit_cnt[1], 0); // NOT called by Core 1 (and all others)
}

/**
 * \Reference
 *  RBSYS_BaseOSRequest, RBMESG_RBSYSBaseOSbySW, RBMESG_RBSYSBaseOSActive, Gen_SWCS_HSW_uC_Base_SYS-223, Gen_SWCS_HSW_uC_Base_SYS-270
 *
 * \Purpose
 *  BaseOS requested via SW
 *
 * \Sequence
 *  Simulate a BaseOS request via RBMESG_RBSYSBaseOSRequestbySW_u32
 *  Call function CallPrivate_RBSYS_StartupPreOSPhase0 on master core
 *  Call function main on master core
 *
 * \ExpectedResult
 *  BaseOS shall only be requested via RBMESG_RBSYSBaseOSActive in case of SW reset
 *  In case RBMESG_RBSYSBaseOSActive is active the message RBMESG_RBSYSBaseOSbySW must also be T
 */
SWTEST void TRBSYS_BaseOS_SW_main(void)
{
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSbySW);
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSActive);

  TRBSYS_setCoreID(RBSYS_CORE_ID_0);

  // HW reset + BaseOS request
  RBMESG_SendMESG(RBMESG_RBSYSBaseOSRequestbySW_u32, RBSYS_BaseOSRequest);
  CallPrivate_RBSYS_StartupPreOSPhase0();
  CallPrivate_main();

  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSbySW);
  SWT_EvalEq(l_RBMESG_RBSYSBaseOSbySW, FALSE);

  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSActive);
  SWT_EvalEq(l_RBMESG_RBSYSBaseOSActive, FALSE);

  // SW reset + BaseOS request
  TRBSYS_setSoftwareReset();
  RBMESG_SendMESG(RBMESG_RBSYSBaseOSRequestbySW_u32, RBSYS_BaseOSRequest);
  CallPrivate_main();

  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSbySW);
  SWT_EvalEq(l_RBMESG_RBSYSBaseOSbySW, TRUE);

  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSActive);
  SWT_EvalEq(l_RBMESG_RBSYSBaseOSActive, TRUE);

}


/**
 * \Reference
 *  RBMESG_RBSYSPlantModeRequest, RBMESG_RBSYSBaseOSActive, Gen_SWCS_HSW_uC_Base_SYS-270
 *
 * \Purpose
 *  BaseOS requested via ASIC plant mode detection
 *
 * \Sequence
 *  Simulate detected plant mode request via RBMESG_RBSYSPlantModeRequest
 *  Call function RBSYS_StartupPreOSPhase0 from master core
 *  Call function main from master core
 *
 * \ExpectedResult
 *  BaseOS shall be requested via RBMESG_RBSYSBaseOSActive in case of HW and SW reset
 */
SWTEST void TRBSYS_BaseOS_ASIC_main(void)
{
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSActive);

  TRBSYS_setCoreID(RBSYS_CORE_ID_0);

  // HW reset + BaseOS request
  RBMESG_SendMESG(RBMESG_RBSYSPlantModeRequest, TRUE);
  CallPrivate_RBSYS_StartupPreOSPhase0();
  CallPrivate_main();

  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSActive);
  SWT_EvalEq(l_RBMESG_RBSYSBaseOSActive, TRUE);

  // SW reset + BaseOS request
  RBMESG_SendMESG(RBMESG_RBSYSPlantModeRequest, TRUE);
  TRBSYS_setSoftwareReset();
  CallPrivate_main();

  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSActive);
  SWT_EvalEq(l_RBMESG_RBSYSBaseOSActive, TRUE);
}

#if(RBFS_ReprogDriverSupport == RBFS_ReprogDriverSupport_ON)
  /**
   * \Reference
   *  RBSYS_ReprogRequest, Gen_SWCS_HSW_uC_Base_SYS-273
   *
   * \Purpose
   *  Verify jump to CAN reprog driver in case of requested reprog session
   *
   * \Sequence
   *  Simulate reprog request via message RBMESG_RBSYSBaseOSRequestbySW_u32
   *  Call function RBSYS_StartupPreOSPhase0 together with main in case of HW reset
   *  Call function RBSYS_StartupPreOSPhase0 together with main in case of SW reset
   *
   * \ExpectedResult
   *  Reprog driver must be called only in case of SW reset
   *  If RBFS_TPSWSVPRestrictions_ON and RBFS_uCFamily_RenesasP1x are configured, RAM is configured to be executable
   */
  SWTEST void TRBSYS_Reprog_main(void)
  {
    RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);
    RBMESG_SendMESG(RBMESG_RBSYSBaseOSRequestbySW_u32, RBSYS_ReprogRequest);
    TRBSYS_setCoreID(RBSYS_CORE_ID_0);

    // HW reset + ReprogRequest
    CallPrivate_RBSYS_StartupPreOSPhase0();
    CallPrivate_main();

    #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_TPSWSVPRestrictions == RBFS_TPSWSVPRestrictions_ON))
      SWT_EvalEq(TRBSYS_CoreMpu_AllowRamExecution_cnt, 0);
    #endif
    SWT_EvalEq(TRBSYS_DummyReprogDriver_cnt, 0);

    // SW reset + ReprogRequest
    TRBSYS_setSoftwareReset();
    CallPrivate_main();

    #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_TPSWSVPRestrictions == RBFS_TPSWSVPRestrictions_ON))
      SWT_EvalEq(TRBSYS_CoreMpu_AllowRamExecution_cnt, 1);
    #endif
    SWT_EvalEq(TRBSYS_DummyReprogDriver_cnt, 1);
  }
#endif


/**
 * \Reference
 *  RBSYS_Vx1000ReprogRequested
 *
 * \Purpose
 *  Trigger request to BaseOS in case VX1000 handling failed
 *
 * \Sequence
 *  Simulate VX1000 reprog request via message RBMESG_RBSYSBaseOSRequestbySW_u32
 *  Call function RBSYS_StartupPreOSPhase0 together with main in case of HW reset
 *  Call function RBSYS_StartupPreOSPhase0 together with main in case of SW reset
 *
 * \ExpectedResult
 *  BaseOS is requested in case of SW reset and Vx1000ReprogRequest
 */
SWTEST void TRBSYS_Vx1000Reprog_main(void)
{
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSbySW);
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSActive);
  TRBSYS_setCoreID(RBSYS_CORE_ID_0);

  // HW reset + Vx1000ReprogRequest
  RBMESG_SendMESG(RBMESG_RBSYSBaseOSRequestbySW_u32, RBSYS_Vx1000ReprogRequested);
  CallPrivate_RBSYS_StartupPreOSPhase0();
  CallPrivate_main();

  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSbySW);
  SWT_EvalEq(l_RBMESG_RBSYSBaseOSbySW, FALSE);

  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSActive);
  SWT_EvalEq(l_RBMESG_RBSYSBaseOSActive, FALSE);


  // SW reset + Vx1000ReprogRequest
  TRBSYS_setSoftwareReset();
  RBMESG_SendMESG(RBMESG_RBSYSBaseOSRequestbySW_u32, RBSYS_Vx1000ReprogRequested);
  CallPrivate_main();


  // BaseOS request as fallback strategy
  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSbySW);
  SWT_EvalEq(l_RBMESG_RBSYSBaseOSbySW, TRUE);

  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSActive);
  SWT_EvalEq(l_RBMESG_RBSYSBaseOSActive, TRUE);
}


SWTEST void TRBSYS_Vx1000ParHandling_main(void)
{
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);
  RBMESG_SendMESG(RBMESG_RBSYSBaseOSRequestbySW_u32, RBSYS_Vx1000ParHandlingRequested);
  TRBSYS_setCoreID(RBSYS_CORE_ID_0);

  // HW reset + Vx1000ParHandlingRequest
  CallPrivate_RBSYS_StartupPreOSPhase0();
  CallPrivate_main();

  // SW reset + Vx1000ParHandlingRequest
  TRBSYS_setSoftwareReset();
  CallPrivate_main();

  // There is no reasonable test possible as long as corresponding mergeproc entry point is empty.
  SWT_Eval(TRUE);
}


/**
 * \Reference
 *  TRBSYS_PRC_ClearColdStartResetFlags, Gen_SWCS_HSW_uC_Base_SYS-284
 *
 * \Purpose
 *  Call RBSYS_PRC_ClearColdStartResetFlags and see that Reset Flag clear register is set correctly
 *
 * \Sequence
 *  - call RBSYS_PRC_ClearColdStartResetFlags
 *  - check Reset Flag clear register
 *
 * \ExpectedResult
 *  Reset Flag clear register is set correctly
 */
SWTEST void TRBSYS_PRC_ClearColdStartResetFlags(void)
{
    // RBSYS_RESFC is initialized to 0 by RAM zeroing of the unit test

    CallPrivate_RBSYS_PRC_ClearColdStartResetFlags();

    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      SWT_EvalEq(RBSYS_RESFC, (RBSYS_RESET_FLAG_POWERON | RBSYS_RESET_FLAG_HW_BIST));
    #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      SWT_EvalEq(RBSYS_RESFC, (RBSYS_RESET_FLAG_POWERON | RBSYS_RESET_FLAG_HW_BIST_F0 | RBSYS_RESET_FLAG_HW_BIST_F1
                        | RBSYS_RESET_FLAG_HW_BIST_F2));
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      SWT_Eval(1);
      #warning("ClearColdStartResetFlags is not implemented and not tested!")
    #endif
}

#if ( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
/**
 * \Reference
 *  TRBSYS_checkVariables4Measurement, Gen_SWCS_HSW_uC_Base_SYS-285
 *
 * \Purpose
 *  Call main() and see that the variable values for measurement are set correctly
 *
 * \Sequence
 *  - call main()
 *  - check that the register values are copied to the measurement variables correctly
 *
 * \ExpectedResult
 *  measurement variables contain expected content
 */
SWTEST void TRBSYS_checkVariables4Measurement(void)
{
    TRBSYS_setCoreID(RBSYS_CORE_ID_0);
    RBSYS_RESF     = 0x07;

    CallPrivate_RBSYS_StartupPreOSPhase0();
    CallPrivate_main();

    SWT_EvalEqX(CallPrivate_RBSYS_getResetFlags4MM6(), (RBSYS_RESF | 0x80000000u));   /* as default here Reset is triggered by FSW -> 0x8000 0000 is or'ed to RBSYS_RESF */
}
#endif

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
#if( RBFS_DataFlashECC == RBFS_DataFlashECC_Disabled )
/**
 * \Reference
 *  TRBSYS_DeactivateECCforDataFlash
 *
 * \Purpose
 *  Call main() and see that ECC Checks for DataFlash are deactivated
 *
 * \Sequence
 *  - call main()
 *  - check that ECC is deactivated
 *  - check that ECC register access protection is active again
 *
 * \ExpectedResult
 *  ECC is deactivated
 */
SWTEST void TRBSYS_DeactivateECCforDataFlash(void)
{
  TRBSYS_setCoreID(RBSYS_CORE_ID_0);

  CallPrivate_RBSYS_StartupPreOSPhase0();
  CallPrivate_main();

  SWT_EvalEq(ECCDFDFECCCTL, 0x3u); // RBSYS_deactivateDataFlashECC has been called
}
#endif
#endif

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
  SWTEST void TRBSYS_FSWStartup_main_CPP(void)
  {
    TRBSYS_setCoreID(RBSYS_CORE_ID_0);

    CallPrivate_RBSYS_StartupPreOSPhase0();
    CallPrivate_main();

    SWT_EvalEq(TRBSYS_main_cnt, 1);
  }
#endif


/* Dummy test functions within a corresponding process table */
static uint32 TRBSYS_UnitTestFunc1_cnt = 0;
static void TRBSYS_UnitTestFunc1(void)
{
  TRBSYS_UnitTestFunc1_cnt++;
}

static uint32 TRBSYS_UnitTestFunc2_cnt = 0;
static void TRBSYS_UnitTestFunc2(void)
{
  TRBSYS_UnitTestFunc2_cnt++;
}

static const PRC_PTR TRBSYS_UnitTestTable[] =
{
  &TRBSYS_UnitTestFunc1,
  &TRBSYS_UnitTestFunc2,
  NULL
};


/**
 * \Reference
 *  startup_prc_calls
 *
 * \Purpose
 *  Ensure call for each process within the correpsonding table
 *
 * \Sequence
 *  Call function "startup_prc_calls" with corresponding parameter
 *  mapping to a process test table
 *
 * \ExpectedResult
 *  Each function within the process table must be called once
 */
SWTEST void TRBSYS_startup_prc_calls(void)
{
  CallPrivate_startup_prc_calls(TRBSYS_UnitTestTable);

  SWT_EvalEq(TRBSYS_UnitTestFunc1_cnt, 1);
  SWT_EvalEq(TRBSYS_UnitTestFunc2_cnt, 1);
}

#if (RBFS_MCORE == RBFS_MCORE_OFF)
  /**
   * \Reference
   *  StartupPreOSPhase, main
   *
   * \Purpose
   *  Startup code has lot of code that is only executed by core 0 enforced with branches decided on the core id.
   *  Single core software also has these branches and will always take them, therefore test coverage is missing for implicit else branches.
   *
   * \Sequence
   *  Call RBSYS_StartupPreOSPhase0
   *  Call main
   *
   * \ExpectedResult
   *  MISUSE, nothing is expected
   */
  SWTEST void TRBSYS_singleCore_COREID_MISUSE(void)
  {
    int i;

    for (i=1; i<2; i++)
    {
      TRBSYS_setCoreID(i);
      CallPrivate_RBSYS_StartupPreOSPhase0();
      CallPrivate_main();
    }
    SWT_Eval(TRUE);
  }
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  /**
   * \Reference
   *  main
   *
   * \Purpose
   *  Using the Interrupt Controller mode "Table Reference" may fail due to a hardware limitation.
   *  Therefore, check the sanity check fails if Table Reference Mode is selected
   *
   * \Sequence
   *  Call RBSYS_StartupPreOSPhase0
   *  Call main
   *
   * \ExpectedResult
   *  assertion failed
   */
  SWTEST void TRBSYS_RenesasP1x_TableReferenceModeIssue(void)
  {
    int i;

    TRBSYS_Os_InitializeVectorTable_EBASEManipulation = 0x00000000u; //EBASE.RINT = 0

    for (i=0; i<2; i++)
    {
      SWT_AssertCheckStart("main2", "(ebase & RBSYS_EBASE_RINT_MASK) == 0x1u");

      TRBSYS_setCoreID(i);
      CallPrivate_RBSYS_StartupPreOSPhase0();
      CallPrivate_main();

      SWT_AssertCheckEnd();
    }
    SWT_Eval(TRUE);
  }
#endif




#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
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