#include "SwTest_Global.h"

#include "RBSYS_Config.h" ///< for RBFS_CpuClock, RBFS_TargetDevice, RBFS_uCFamily


// access API for api header under test
#include "TRBSYS_ClockSettingsAdaptor.h"


#include "TRBSYS_uCRegisters.h"  // to set the include protection and avoid further use of the unstubbed header
#include "TRBSYS_CpuVersions.h"  // to set the include protection and avoid further use of the unstubbed header
#include "TRBSYS_TestInjection.h"
#include "TRBSYS_CpuInfo.h"
#include "RBSYS_Subsystem.h"

#include "RBHSWDEM_Facade.h"
#include "DemStub_Helper.h"

// to get some defines
#include "RBSYS_ClockSettings.h"



/**
 * \UT_TestCaseName TRBSYS_ClockSettings_001
 *
 * \UT_Reference
 * Gen_SWCS_HSW_uC_Base_SYS-206, Gen_SWCS_HSW_uC_Base_SYS-208, Gen_SWCS_HSW_uC_Base_SYS-209
 *
 * \UT_Purpose Test functionality of the RBSYS_SetupECP function
 *
 * \UT_Sequence
 * - P1x:
 *   - initialize ECLK registers and clock model to their default
 *   - call function under test with a frequency as parameter
 * - U2A:
 *   - initialize ECLK registers such that clock divider is active and both divider and clock source are set
 *     different than they are set by the function under test
 *   - call function under test with a frequency
 *   - change clock source of ECLK
 *   - call function under test again with a different frequency
 * - Stellar:
 *   - initialize SYSCLK0 to 4MHz (default value for System ASIC)
 *   - SYSCLK0 supports range 780kHz - 400MHz -> test border cases (assert should hit)
 *
 * \UT_ExpectedResult
 * - P1x:
 *   - clock divider is set according to given frequency
 *   - clock divider is active and synchronized
 *   - clock source is set to CLK_HSB
 *   - register CLKD2STAT was read multiple times according to UM
 * - U2A:
 *   - after first call of the function under, test clock source and divider are changed, divider is active and stable
 *   - after second call, clock source was not changed, but divider is set according to new frequency, divider is active and stable
 * - Stellar:
 *   - valid values: correct divider shall be set
 *   - invalid values: assertion fails
 */
SWTEST void TRBSYS_ClockSettings_001(void)
{
  uint16 my_ECLK_KHZ = 2000;  // deliberately something different from the usual RBSYS_ECLK_DEFAULT_KHZ == 4000

  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
    // default: clock divider 1, active and synchronized
    // default: clock source CLK_LSB
    TRBSYS_ClockModelInit();

    RBSYS_SetupECP(my_ECLK_KHZ);

    SWT_EvalEq(CLKD2DIV, (RBSYS_CPU_CLK_KHZ/my_ECLK_KHZ)); // clock divider set correctly
    SWT_EvalEq(pysCLKD2STAT, 0x3); // clock divider active and synchronized
    SWT_EvalEq(CKSC2C, 0x5); // clock source CLK_HSB
    SWT_EvalEq(TRBSYS_GetReadCnt_CLKD2STAT(), 11);  // 1.Iteration: 4 Dummy Gets + 2 Gets in while-loop; 2.Iteration: 4 Dummy Gets + 1 Get in while-loop = 11

  #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    SYSCTRLCLKD_FOUT0C = 0x1; // clock divider is set to 1
    SYSCTRLCLKD_FOUT0S = 0x3; // clock divider active and stable
    SYSCTRLCKSC_FOUT0C = 0x0; // CLK_MOSC set as clock source
    SYSCTRLCKSC_FOUT0S = 0x0;
    SYSCTRLCLKD_EXTCLK0C = 0x1; // clock divider is set to 1
    SYSCTRLCLKD_EXTCLK0S = 0x3; // clock divider active and stable
    SYSCTRLCKSC_EXTCLK0C = 0x0; // CLK_MOSC set as clock source
    SYSCTRLCKSC_EXTCLK0S = 0x0;

    TRBSYS_ClockModelInit();

    RBSYS_SetupECP(15);//< 15 khz

    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
      SWT_EvalEq(SYSCTRLCLKD_FOUT0C, RBSYS_HSB_CLK_KHZ/15); // clock divider set correctly
      SWT_EvalEq(SYSCTRLCLKD_FOUT0S, 0x3); // clock divider active and stable
      SWT_EvalEq(SYSCTRLCKSC_FOUT0C, 0x1); // CLK_HSB set as clock source
      SWT_EvalEq(SYSCTRLCKSC_FOUT0S, 0x1);
    #else
      SWT_EvalEq(SYSCTRLCLKD_EXTCLK0C, RBSYS_HSB_CLK_KHZ/15); // clock divider set correctly
      SWT_EvalEq(SYSCTRLCLKD_EXTCLK0S, 0x3); // clock divider active and stable
      SWT_EvalEq(SYSCTRLCKSC_EXTCLK0C, 0x4); // CLK_HSB set as clock source
      SWT_EvalEq(SYSCTRLCKSC_EXTCLK0S, 0x4);
    #endif


    // subsequent calls of RBSYS_SetupECP shall only change the frequency
    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
      SYSCTRLCKSC_FOUT0C = 0x2; //< to see if it changes
      SYSCTRLCKSC_FOUT0S = 0x2;
    #else
      SWT_EvalEq(SYSCTRLCKSC_EXTCLK0C, 0x4); //< to see if it changes
      SWT_EvalEq(SYSCTRLCKSC_EXTCLK0S, 0x4);
    #endif
    TRBSYS_ClockModelInit();

    RBSYS_SetupECP(10); //< 10 khz

    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
      SWT_EvalEq(SYSCTRLCLKD_FOUT0C, RBSYS_HSB_CLK_KHZ/10);   // clock divider set correctly
      SWT_EvalEq(SYSCTRLCLKD_FOUT0S, 0x3);                    // clock divider active and stable
      SWT_EvalEq(SYSCTRLCKSC_FOUT0C, 0x2);                    // not have changed
      SWT_EvalEq(SYSCTRLCKSC_FOUT0S, 0x2);                    // not have changed
    #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
      SWT_EvalEq(SYSCTRLCLKD_EXTCLK0C, RBSYS_HSB_CLK_KHZ/10); // clock divider set correctly
      SWT_EvalEq(SYSCTRLCLKD_EXTCLK0S, 0x3);                  // clock divider active and stable
      SWT_EvalEq(SYSCTRLCKSC_EXTCLK0C, 0x4);                  // not have changed
      SWT_EvalEq(SYSCTRLCKSC_EXTCLK0S, 0x4);                  // not have changed
    #endif

  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    MC_CGM_PERIPHERAL_DOMAIN.AC6_SS = 0x02000000u;

    RBSYS_SetupECP(4000);

    SWT_EvalEq( MC_CGM_PERIPHERAL_DOMAIN.AC6_SC,  0x02000000u );
    SWT_EvalEq( MC_CGM_PERIPHERAL_DOMAIN.AC6_DC0, 0x80630000u );

    SWT_AssertCheckStart("RBSYS_SetupECP", "divider <= 512");
    RBSYS_SetupECP(779 /*kHz*/);
    SWT_AssertCheckEnd();

    // SWT_AssertCheckStart("RBSYS_SetupECP", "(0 < divider) && (divider <= 512)");
    // RBSYS_SetupECP(400001 /*kHz*/);
    // SWT_AssertCheckEnd();
    /* Hint: -> Divider cannot be below 6 as maximum input to RBSYS_SetupECP is 65535kHz */

  #endif
}

#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )

#if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2))

/**
 * \UT_TestCaseName TRBSYS_ClockSettings_002a
 *
 * \UT_Reference
 * Gen_SWCS_HSW_uC_Base_SYS-268
 *
 * \UT_Purpose Test functionality of the RBSYS_SetupClocks_RenesasP1x function (no D1/D2 running on D3ED/D5ED)
 *
 * \UT_Sequence
 * Call function under test when no emulation device is used
 *
 * \UT_ExpectedResult
 * CLKD0DIV and CLKD1DIV are not set
 *
 */
SWTEST void TRBSYS_ClockSettings_002a(void)
{
  // default: Clock dividers are set to 1, active and synchronized
  TRBSYS_ClockModelInit();

  call_RBSYS_SetupClocks_RenesasP1x();

  SWT_EvalEq(CLKD0DIV, 1); // Not changed
  SWT_EvalEq(CLKD1DIV, 1); // Not changed
}


/**
 * \UT_TestCaseName TRBSYS_ClockSettings_002b
 *
 * \UT_Reference
 * Gen_SWCS_HSW_uC_Base_SYS-268
 *
 * \UT_Purpose Test functionality of the RBSYS_SetupClocks_RenesasP1x function (D1/D2 running on D3ED)
 *
 * \UT_Sequence
 * Call function under test when D3ED is used
 *
 * \UT_ExpectedResult
 * CLKD0DIV and CLKD1DIV are set as expected
 *
 */
SWTEST void TRBSYS_ClockSettings_002b(void)
{
  TRBSYS_SetCPU_D3ED();
  // default: Clock dividers are set to 1, active and synchronized
  TRBSYS_ClockModelInit();

  call_RBSYS_SetupClocks_RenesasP1x();

  SWT_EvalEq(CLKD0DIV, 0x3u); // Clock divider is set to /3
  SWT_EvalEq(pysCLKD0STAT, 0x3); // Clock divider active and synchronized
  SWT_EvalEq(TRBSYS_GetReadCnt_CLKD0STAT(), 2);  // 2 Get in while-loop
  SWT_EvalEq(CLKD1DIV, 0x2u); // Clock divider is set to /2
  SWT_EvalEq(pysCLKD1STAT, 0x3); // Clock divider active and synchronized
  SWT_EvalEq(TRBSYS_GetReadCnt_CLKD1STAT(), 2);  // 2 Get in while-loop
}


/**
 * \UT_TestCaseName TRBSYS_ClockSettings_002c
 *
 * \UT_Reference
 * Gen_SWCS_HSW_uC_Base_SYS-268
 *
 * \UT_Purpose Test functionality of the RBSYS_SetupClocks_RenesasP1x function (D1/D2 running on D5ED)
 *
 * \UT_Sequence
 * Call function under test when D5ED is used
 *
 * \UT_ExpectedResult
 * CLKD0DIV and CLKD1DIV are set as expected
 *
 */
SWTEST void TRBSYS_ClockSettings_002c(void)
{
  TRBSYS_SetCPU_D5ED();
  // default: Clock dividers are set to 1, active and synchronized
  TRBSYS_ClockModelInit();

  call_RBSYS_SetupClocks_RenesasP1x();

  SWT_EvalEq(CLKD0DIV, 0x3u); // Clock divider is set to /3
  SWT_EvalEq(pysCLKD0STAT, 0x3); // Clock divider active and synchronized
  SWT_EvalEq(TRBSYS_GetReadCnt_CLKD0STAT(), 2);  // 2 Get in while-loop
  SWT_EvalEq(CLKD1DIV, 0x2u); // Clock divider is set to /2
  SWT_EvalEq(pysCLKD1STAT, 0x3); // Clock divider active and synchronized
  SWT_EvalEq(TRBSYS_GetReadCnt_CLKD1STAT(), 2);  // 2 Get in while-loop
}
#endif

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
/**
 * \UT_TestCaseName TRBSYS_ClockSettings_003a
 *
 * \UT_Reference
 * Gen_SWCS_HSW_uC_Base_SYS-314
 *
 * \UT_Purpose Test functionality of the RBSYS_SetupClocks_RenesasU2A function
 *
 * \UT_Sequence
 * Configure clock registers such that CPU is operating on PLL
 * Call function under test
 *
 * \UT_ExpectedResult
 * FUT does not change anything
 *
 */
SWTEST void TRBSYS_ClockSettings_003a(void)
{
  SYSCTRLCKSC_CPUC = 0x0; //CPU is operating on the PLL
  SYSCTRLCKSC_CPUS = 0x0; //CPU is operating on the PLL
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
    SYSCTRLCKSC_SSCGC = 0x0; //CPU is operating on the PLL
    SYSCTRLCKSC_SSCGS = 0x0; //CPU is operating on the PLL
  #endif
  // default: Main OSC is not activated
  // default: PLL is not activated
  // default: clock divider is set to 1 and stable
  TRBSYS_ClockModelInit();

  call_RBSYS_SetupClocks_RenesasU2A();

  SWT_EvalEq(SYSCTRLCKSC_CPUC, 0); // Not changed
  SWT_EvalEq(SYSCTRLCKSC_CPUS, 0); // Not changed
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
    SWT_EvalEq(SYSCTRLCKSC_SSCGC, 0); // Not changed
    SWT_EvalEq(SYSCTRLCKSC_SSCGS, 0); // Not changed
  #endif
  SWT_EvalEq(SYSCTRLMOSCS, 0);     // Not changed
  SWT_EvalEq(SYSCTRLPLLS, 0);      // Not changed
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
    SWT_EvalEq(SYSCTRLCLKD_PLLC, 1); // Not changed
  #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
    SWT_EvalEq(SYSCTRLCLKD_PLLC, 0); // Not changed
  #endif
  SWT_EvalEq(SYSCTRLCLKD_PLLS, 3); // Not changed
}

/**
 * \UT_TestCaseName TRBSYS_ClockSettings_003b
 *
 * \UT_Reference
 * Gen_SWCS_HSW_uC_Base_SYS-314
 *
 * \UT_Purpose Test functionality of the RBSYS_SetupClocks_RenesasU2A function
 *
 * \UT_Sequence
 * Keep clock registers on their default values after reset
 * Call function under test
 *
 * \UT_ExpectedResult
 * CPU operates on PLL,
 * Main OSC ist activated and stable,
 * PLL is activated and stable,
 * clock divider is set to 1 and stable
 *
 */
SWTEST void TRBSYS_ClockSettings_003b(void)
{
  // default: CPU is not operating on the PLL
  // default: Main OSC is not activated
  // default: PLL is not activated
  // default: Clock divider is set to 1 and stable
  TRBSYS_ClockModelInit();

  call_RBSYS_SetupClocks_RenesasU2A();

  SWT_EvalEq(SYSCTRLCKSC_CPUC, 0); // CPU is operating on the PLL
  SWT_EvalEq(SYSCTRLCKSC_CPUS, 0); // CPU is operating on the PLL
  SWT_EvalEq(SYSCTRLMOSCS, 3);     // Main OSC is activated and stable
  SWT_EvalEq(SYSCTRLPLLS, 3);      // PLL is activated and stable
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
    SWT_EvalEq(SYSCTRLCLKD_PLLC, 1); // Clock divider is set to 1
    SWT_EvalEq(SYSCTRLCLKD_PLLS, 3); // Clock divider is stable
  #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
    SWT_EvalEq(SYSCTRLCLKD_PLLC, 0); // Clock divider is set to "no division"
    SWT_EvalEq(SYSCTRLCLKD_PLLS, 3); // Clock divider is stable
  #endif
}

/**
 * \UT_TestCaseName TRBSYS_ClockSettings_003c
 *
 * \UT_Reference
 * Gen_SWCS_HSW_uC_Base_SYS-314
 *
 * \UT_Purpose Test functionality of the RBSYS_SetupClocks_RenesasU2A function
 *
 * \UT_Sequence
 * Configure clock registers such that
 *   CPU is not operating on PLL
 *   Main OSC is activated and stable
 *   PLL is activated and stable
 *   Clock divider is set to /2 and is unstable
 * Call function under test
 *
 * \UT_ExpectedResult
 * CPU operates on PLL,
 * Main OSC ist activated and stable,
 * PLL is activated and stable,
 * clock divider is set to 1 and stable
 *
 */
SWTEST void TRBSYS_ClockSettings_003c(void)
{
  // default: CPU is not operating on the PLL
  SYSCTRLMOSCS     = 3; // Main OSC is activated and stable
  SYSCTRLPLLS      = 3; // PLL is activated and stable
  SYSCTRLCLKD_PLLC = 2; // Clock divider is set to /2
  SYSCTRLCLKD_PLLS = 1; // Clock divider is unstable
  TRBSYS_ClockModelInit();

  call_RBSYS_SetupClocks_RenesasU2A();

  SWT_EvalEq(SYSCTRLCKSC_CPUC, 0); // CPU is operating on the PLL
  SWT_EvalEq(SYSCTRLCKSC_CPUS, 0); // CPU is operating on the PLL
  SWT_EvalEq(SYSCTRLMOSCS, 3);     // Not changed
  SWT_EvalEq(SYSCTRLPLLS, 3);      // Not changed
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
    SWT_EvalEq(SYSCTRLCLKD_PLLC, 1); // Clock divider is set to 1
    SWT_EvalEq(SYSCTRLCLKD_PLLS, 3); // Clock divider is stable
  #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
    SWT_EvalEq(SYSCTRLCLKD_PLLC, 0); // Clock divider is set to "no division"
    SWT_EvalEq(SYSCTRLCLKD_PLLS, 3); // Clock divider is stable
  #endif
}

/**
 * \UT_TestCaseName TRBSYS_ClockSettings_003d
 *
 * \UT_Reference
 * Gen_SWCS_HSW_uC_Base_SYS-314
 *
 * \UT_Purpose Test functionality of the RBSYS_SetupClocks_RenesasU2A function
 *
 * \UT_Sequence
 * Configure clock registers such that
 *   CPU is not operating on PLL
 *   Main OSC is activated and stable
 *   PLL is activated and stable
 *   Clock divider is set to 1 and is unstable
 * Call function under test
 *
 * \UT_ExpectedResult
 * CPU operates on PLL,
 * Main OSC ist activated and stable,
 * PLL is activated and stable,
 * clock divider is set to 1 and stable
 *
 */
SWTEST void TRBSYS_ClockSettings_003d(void)
{
  // default: CPU is not operating on the PLL
  SYSCTRLMOSCS     = 3; // Main OSC is activated and stable
  SYSCTRLPLLS      = 3; // PLL is activated and stable
  // default: Clock divider is set to 1
  SYSCTRLCLKD_PLLS = 1; // Clock divider is unstable
  TRBSYS_ClockModelInit();

  call_RBSYS_SetupClocks_RenesasU2A();

  SWT_EvalEq(SYSCTRLCKSC_CPUC, 0); // CPU is operating on the PLL
  SWT_EvalEq(SYSCTRLCKSC_CPUS, 0); // CPU is operating on the PLL
  SWT_EvalEq(SYSCTRLMOSCS, 3);     // Not changed
  SWT_EvalEq(SYSCTRLPLLS, 3);      // Not changed
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
    SWT_EvalEq(SYSCTRLCLKD_PLLC, 1); // Not changed
    SWT_EvalEq(SYSCTRLCLKD_PLLS, 3); // Clock divider is stable
  #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
    SWT_EvalEq(SYSCTRLCLKD_PLLC, 0); // Not changed
    SWT_EvalEq(SYSCTRLCLKD_PLLS, 3); // Clock divider is stable
  #endif
}

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  /**
   * \UT_TestCaseName TRBSYS_ClockSettings_003e
   *
   * \UT_Reference
   * Gen_SWCS_HSW_uC_Base_SYS-314
   *
   * \UT_Purpose Test functionality of the RBSYS_SetupClocks_RenesasU2A function
   *
   * \UT_Sequence
   * Set System Clock to operate on PLL (not geared up to maximum frequency)
   *
   * \UT_ExpectedResult
   * Clock configuration does not ramp down clock, but does ramp up PLL
   *
   */
  SWTEST void TRBSYS_ClockSettings_003e(void)
  {
    // default: CPU is operating on the PLL
    // default: PLL divider set to anything but "DIV1"
    SYSCTRLCKSC_CLEANC = 0;
    SYSCTRLCKSC_CLEANS = 0;
    SYSCTRLCLKD_PLLC = 6; // DIV16/6
    SYSCTRLCLKD_PLLS = 2; // in sync

    TRBSYS_ClockModelInit();

    call_RBSYS_SetupClocks_RenesasU2A();

    SWT_EvalEq(SYSCTRLCLKD_PLLC, 0); // Clock divider is set to "no division"
    SWT_EvalEq(SYSCTRLCLKD_PLLS, 3); // Clock divider is stable
  }
#endif


/**
 * \UT_Reference
 * Gen_SWCS_HSW_uC_Base_SYS-314
 *
 * \UT_Purpose Test functionality of RBSYS_PRC_CheckClockTreeSettings
 *
 * \UT_Sequence
 * see comments in Test
 *
 * \UT_ExpectedResult
 * see comments in Test
 *
 */
SWTEST void TRBSYS_ClockSettings_004(void)
{
  void trbsys_ClockSettingsSetGoodValues(void)
  {
    SYSCTRLMOSCS = 3; //< Main OSC is enabled AND stable
    SYSCTRLPLLS = 3;  //< PLL is activated and stable
    SYSCTRLCLKD_PLLC = 1; //< PLL Clock is divided by 1
    SYSCTRLCLKD_PLLS = 3; //< PLL Clock is synchronized
    SYSCTRLCKSC_CPUS = 0; //< CPU is operating on PLL clock
  }

  TRBSYS_setCoreID(0);

  trbsys_ClockSettingsSetGoodValues();
  SYSCTRLMOSCS = 1; //< Main OSC is enabled but not stable
  RBSYS_PRC_CheckClockTreeSettings();
  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE); //< SYSErrorHook is reported

  DemStub_EnvReset();
  trbsys_ClockSettingsSetGoodValues();
  SYSCTRLPLLS = 1;  //< PLL is activated but not stable
  RBSYS_PRC_CheckClockTreeSettings();
  SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE); //< SYSErrorHook is reported

  DemStub_EnvReset();
  trbsys_ClockSettingsSetGoodValues();
  SYSCTRLCLKD_PLLC = 2; //< PLL Clock is divided by 2 (not 1)
  RBSYS_PRC_CheckClockTreeSettings();
  SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE); //< SYSErrorHook is reported

  DemStub_EnvReset();
  trbsys_ClockSettingsSetGoodValues();
  SYSCTRLCLKD_PLLS = 1; //< PLL Clock is not synchronized, thereby Clock divider is not used
  RBSYS_PRC_CheckClockTreeSettings();
  SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE); //< SYSErrorHook is reported

  DemStub_EnvReset();
  trbsys_ClockSettingsSetGoodValues();
  SYSCTRLCKSC_CPUS = 1; //< CPU is operating on Internal clock
  RBSYS_PRC_CheckClockTreeSettings();
  SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE); //< SYSErrorHook is reported

  DemStub_EnvReset();
  trbsys_ClockSettingsSetGoodValues();
  RBSYS_PRC_CheckClockTreeSettings();
  SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), FALSE); //< SYSErrorHook is NOT reported
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

#if ((RBFS_uCWatchdog == RBFS_uCWatchdog_Enabled) && ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)))
/**
 * \UT_TestCaseName TRBSYS_ClockSettings_getClkWdtDivider
 *
 * \UT_Reference RBSYS_getClkWdtDivider
 *
 * \UT_Purpose Test correct behavior and return value of RBSYS_getClkWdtDivider
 *
 * \UT_Sequence
 * 1. Set WDTS register to 0 and ensure RBSYS_getClkWdtDivider() returns RBSYS_CLK_WDT_DIVIDER_20
 * 2. Set WDTS register to 1 and ensure RBSYS_getClkWdtDivider() returns RBSYS_CLK_WDT_DIVIDER_640
 * 3. Set WDTS register to 2 and ensure RBSYS_getClkWdtDivider() returns RBSYS_CLK_WDT_DIVIDER_800 (U2C only)
 *
 * \UT_ExpectedResult
 * As described in UT_Sequence
 */
SWTEST void TRBSYS_ClockSettings_getClkWdtDivider(void)
{
  SYSCTRLCKSC_WDTS = 0;
  SWT_EvalEq(RBSYS_getClkWdtDivider(), RBSYS_CLK_WDT_DIVIDER_20);

  SYSCTRLCKSC_WDTS = 1;
  SWT_EvalEq(RBSYS_getClkWdtDivider(), RBSYS_CLK_WDT_DIVIDER_640);

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
    SYSCTRLCKSC_WDTS = 2;
    SWT_EvalEq(RBSYS_getClkWdtDivider(), RBSYS_CLK_WDT_DIVIDER_800);
  #endif
}
#endif
