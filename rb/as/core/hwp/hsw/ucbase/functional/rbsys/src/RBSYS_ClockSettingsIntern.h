#ifndef RBSYS_CLOCKSETTINGSINTERN_H__
#define RBSYS_CLOCKSETTINGSINTERN_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Information about system clock frequencies
 *
 * The system clock generation is mainly configured by Flash Options and controlled via hardware.
 * Therefore frequency ramp up is completely handled in HW and SW must not consider stuff like timing,
 * current peaks or clock frequency during HW BISTs. Keep in mind, that in general it's not supported
 * to have different Flash Options for Bootblock and FSW builds related to system clock frequencies!
 *
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_TestInjection.h" //< for Unittest instrumentation macros
#include "RBSYS_uCRegisters.h"
#include "Monitorings/RBSYS_ErrorHooks.h"
#include "RBSYS_uCModuleModeCtrl.h"
#include "RBSYS_Intrinsics.h"



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

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



#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                            RBFS_HexBlockBuild_BOOTMANAGER,
                            RBFS_HexBlockBuild_BOOTLOADER,
                            RBFS_HexBlockBuild_RBBOOTLOADER,
                            RBFS_HexBlockBuild_APPLICATION);

  extern void RBSYS_SetupClocks_RenesasU2A(void);

  /**
   * While configuring CLK_CPU different wait times at different clock speeds are needed.
   * RBSYS_SNOOZE has to be used instead of RBSYS_waitUsecLoop as the latter uses TPTM which depends on CLK_CPU.
   * CLK_CPU can either operate on CLK_IOSC or CLK_PLLO (Table 13.5 in U2A HW UM 1.10 p. 1002)
   * Clock source of CLK_IOSC is HS IntOsc (only exception is in standby mode, see U2A HW UM 1.10 p. 1000)
   * So before operating on CLK_PLLO, a clock speed of 100MHz is assumed.
   * When operating on CLK_PLLO, an intermediate clock speed of 200MHz is active during gear up until the target speed of 400MHz is reached.
   */
  #define RBSYS_SNOOZE_AT_LEAST_1_4US_AT_100MHZ() RBSYS_SNOOZE_LOOP(5)     //    5 * 32 ticks at 100MHz = 1.6us
  #define RBSYS_SNOOZE_AT_LEAST_100US_AT_100MHZ() RBSYS_SNOOZE_LOOP(313)   //  313 * 32 ticks at 100MHz = 100.16us
  #define RBSYS_SNOOZE_AT_LEAST_100US_AT_200MHZ() RBSYS_SNOOZE_LOOP(625)   //  625 * 32 ticks at 200MHz = 100us
  #define RBSYS_SNOOZE_AT_LEAST_100US_AT_400MHZ() RBSYS_SNOOZE_LOOP(1250)  // 1250 * 32 ticks at 400MHz = 100us

  /**
   * @brief Enable write access to "Clock Controller Register"
   *
   * Enable access protection of Clock Controller Register on RH850/U2A via CLKKCPROT1
   * (Clock Controller Register Key Code Protection Register 1).
   *
   * @return void
   */
  __attribute__((always_inline))  static inline void RBSYS_EnableWriteAccessToClockController(void)
  {
    RBSYS_UnlockAccessToHwModule( &SYSCTRLCLKKCPROT1 ); // enable write access
  }


  /**
   * @brief Disable write access to "Clock Controller Register"
   *
   * Disable access protection of Clock Controller Register on RH850/U2A via CLKKCPROT1
   * (Clock Controller Register Key Code Protection Register 1).
   *
   * @return void
   */
  __attribute__((always_inline))  static inline void RBSYS_DisableWriteAccessToClockController(void)
  {
    RBSYS_LockAccessToHwModule( &SYSCTRLCLKKCPROT1 ); // disable write access
  }

  #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )  //< Error reporting is not available within other than Application
    /**
    * @brief Checks if PLL Clock Tree is configured as expected
    *
    * Hint: Necessary because HSM takes over Clock configuration for U2A.
    */
    static inline void RBSYS_CheckClockTreeConfiguration(void)
    {
      // copy register content to RAM -> prevents later modification during condition evaluation
      uint32 rbsys_SYSCTRLMOSCS     = SYSCTRLMOSCS;
      uint32 rbsys_SYSCTRLPLLS      = SYSCTRLPLLS;
      uint32 rbsys_SYSCTRLCLKD_PLLC = SYSCTRLCLKD_PLLC;
      uint32 rbsys_SYSCTRLCLKD_PLLS = SYSCTRLCLKD_PLLS;
      #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        uint32 rbsys_SYSCTRLCKSC_CPUS = SYSCTRLCKSC_CPUS;
      #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
        uint32 rbsys_SYSCTRLCKSC_CPUS = SYSCTRLCKSC_CLEANS;
      #endif

      if( (rbsys_SYSCTRLMOSCS     == 0x3u)    //< Main Oscillator ON and Stable
       && (rbsys_SYSCTRLPLLS      == 0x3u)    //< PLL ON and Stable
       && (rbsys_SYSCTRLCLKD_PLLC == 0x1u)    //< No PLL Clock Divider
       && (rbsys_SYSCTRLCLKD_PLLS == 0x3u)    //< PLL Clock output uses divider specified by SYSCTRLCLKD_PLLC (which is 1)
       && (rbsys_SYSCTRLCKSC_CPUS == 0x0u) )  //< CPU is operating on PLL frequency
      { /* clock tree is configured properly and stable */ }
      else
      {
        // PLL Clock tree is not configured properly - potentially safety critical
        RBSYS_setSYSErrorHook(RBSYS_Error_ClockConfigurationInvalid, 0xDEADBEEF);
      }
    }
  #endif
#endif


#if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2))
  /**
   * @brief Setup of clock tree in addition to Flash-Option-Bytes
   *
   * Configuration of clock tree to ensure cycle accurancy between production and emulation device.
   * According to the Users-Manual, the following must be assured while configuring the CLKDiDIV (i = 0,1):
   *  - No Busmaster has access to the Flash
   *  - All Peripherals must be in Stand-By mode
   *
   * Since D1 and D2 devices are not using HSM, there are no other Busmasters which could access the Flash at this early point in time.
   * Peripherals are all initially in Stand-By mode.
   *
   * @return void
   */
  extern void RBSYS_SetupClocks_RenesasP1x(void);
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  /**
   * @brief Setup of Peripheral Clock (dividers) in addition to Clock Tree configuration
   *
   * Central Clock dividers are set centrally here so that the specified Peripheral Clock frequencies (specified in
   * RBSYS_ClockSettings.h are met)
   * Hint: Has to be executed after initializing the Base Clocks for the Peripheral Domain and before using the
   *       peripherals.
   *
   * @return void
   */
  extern void RBSYS_SetupPeripheralClocks(void);

  #define CGM_DC_DIV_Offset (16)
  #define CGM_DC_DIV25 (0x00180000u)
  #define CGM_DC_DIV16 (0x000F0000u)
  #define CGM_DC_DIV12 (0x000B0000u)
  #define CGM_DC_DIV8  (0x00070000u)
  #define CGM_DC_DIV5  (0x00040000u)
  #define CGM_DC_DIV4  (0x00030000u)
  #define CGM_DC_DIV2  (0x00010000u)
  #define CGM_DC_DIV1  (0x00000000u)

  #define CGM_DC_DIVENABLE (0x80000000u)

  static inline void RBSYS_SetupPLLs(void)
  {
    /*
      Configure PLL0 to generate an out put frequency of 50MHz and
      internal frequency ramp to 800MHz
      Crystal oscillator input is 40MHz
    */

    #define CGM_PER_ACx_Source_XOSC ((uint32)1<<24)
    #define PLLDIG_PER_PLLxSR_LOCK  ((uint32)1<<2)

    /* Connect 40MHz crystal to the PLL0 input*/
    MC_CGM_PERIPHERAL_DOMAIN.AC1_SC = CGM_PER_ACx_Source_XOSC;
    while( MC_CGM_PERIPHERAL_DOMAIN.AC1_SS != CGM_PER_ACx_Source_XOSC )
    {
      RBSYS_TEST_INJECTION_ClockModelUpdate(); /* wait unitll crystal is connected to PLL0 */
    };

    if( (PLLDIG_PERIPHERAL_DOMAIN.PLL0SR & PLLDIG_PER_PLLxSR_LOCK) != PLLDIG_PER_PLLxSR_LOCK) //< If PLL is not locked already
    {
      /*Configuration starts only when the pll is not locked*/

      /* Reset/Interrupt is not enabled for Loss of lock or external Power down */
      PLLDIG_PERIPHERAL_DOMAIN.PLL0CR = 0x0U;

      /* PLL0DV                                                                                                      */
      /* Note: The values of PREDIV and MFD "**should not**" be changed when the PLL is on and locked                */
      /* If these fields are changed without powering down the PLL, the PLL will loose                               */
      /* lock and generate either a reset or interrupt based on which is enabled. The reduced frequency dividers     */
      /* (RFDPHI, RFDPHI1) can be changed on the fly                                                                 */

      /* XOSC = 20MHz, RFDPHI1 = 6, RFDPHI = 1, PREDIV = 1, MFD = 20 => VCO = (XOSC / PREDIV) * MFD * 2 = 800MHz, PHI = VCO / (2*RFDPHI) = 400MHz */
      // PLLDIG_PERIPHERAL_DOMAIN.PLL0DV = 0x30011014u;

      /* XOSC = 40MHz, RFDPHI1 = 6, RFDPHI = 1, PREDIV = 1, MFD = 10 => VCO = (XOSC / PREDIV) * MFD * 2 = 800MHz, PHI = VCO / (2*RFDPHI) = 400MHz */
      // PLLDIG_PERIPHERAL_DOMAIN.PLL0DV = 0x3001100Au;

      /* XOSC = 16MHz, RFDPHI1 = 6, RFDPHI = 1, PREDIV = 1, MFD = 25 => VCO = (XOSC / PREDIV) * MFD * 2 = 800MHz, PHI = VCO / (2*RFDPHI) = 400MHz */
      PLLDIG_PERIPHERAL_DOMAIN.PLL0DV = 0x30011019u;


      // Start PLL
      MC_ME_PER.ModeReg.DRUN_MC = (MC_PWRLVL_0 | MC_PDO_OFF | MC_MVR_ON | MC_FLAON_NORMAL | MC_PLL0_ON | MC_XOSC_ON | MC_IROSC_ON | MC_SYSCLK_XOSC); /* start PLL0 */
      RBSYS_ModeEntry_UpdateMode(RBSYS_ModeEntryModule_Peripheral);
      RBSYS_ModeEntry_WaitForStatus(RBSYS_ModeEntryModule_Peripheral, 0x30100071u); // wait until PLL0 Stable but not yet used

      MC_CGM_PERIPHERAL_DOMAIN.SC_DIV_RC = 0x00000001;      /* System clock divider ratios will change with next update.           */
      MC_CGM_PERIPHERAL_DOMAIN.DIV_UPD_TYPE = 0x80000000uL; /* System clock divider ratios updated on writing MC_CGM.DIV_UPD_TRIG. */

      /* DME and DSPH are at half frequency of PLL0 .. which is 200MHz                */
      /* --> DIV is set to 1 i.e 400MHz/(DIV +1)                                      */
      MC_CGM_PERIPHERAL_DOMAIN.SC_DC0 = (CGM_DC_DIVENABLE | CGM_DC_DIV2);

      /* write clock divider registers in order of increasing resultant frequency.    */
      /* ensure consistent settings Part 2*/
      /* Copy System clock divider from shadow register into MC_CGM.SC_DC with one atomic command to ensure consistent settings (if interruprtion occurrs) */
      MC_CGM_PERIPHERAL_DOMAIN.DIV_UPD_TRIG = 0xFEEDFACEuL; /*  trigger update of system clock divider ratio with any value */
      RBSYS_TEST_INJECTION_ClockModelUpdate();

      while(MC_CGM_PERIPHERAL_DOMAIN.DIV_UPD_STAT != 0x00uL)
      {
        RBSYS_TEST_INJECTION_ClockModelUpdate();
      };

      /* ******************************************** */
      /* Enable soft clock ramp up                    */
      /* ******************************************** */
      /* Only preparation! Will be done later on mode transitions between modes with different power levels */

      /* Duration of each step in IRCOSC clocks -> 12,75/2usec (255/40MHz) */
      MC_CGM_PERIPHERAL_DOMAIN.PCS_SDUR = 255u;

      /* Change clock in steps of 5% according to Table 748, P6 RM Rev1 p. 1144 */
      /* d = 0.012 */
      /* RATE = d * 1000 = 12 */

      /* Number of steps required to reach or leave f_src2 with f_src2 > f_src1 according to Equation 7, P6 RM Rev1 p. 1144 */
      /* k = ceil(0.5 + sqrt(0.25 - 2 * (1 - f_src2 / f_src1) / d) */
      /* f_src2 = 400MHz, f_src1 = 40MHz: k = 40 */
      /* f_src2 = 400MHz, f_src1 = 16MHz: k = 64 */

      /* Divider decrement value according to Equation 9, P6 RM Rev1 p. 1145 */
      /* INIT = d * k * 1000 - 1 */
      /* XOSC = 40MHz: INIT = 680 */
      /* XOSC = 16MHz: INIT = 767 */
      MC_CGM_PERIPHERAL_DOMAIN.PCS_DIVC2 = ((767u << 16) | (12u << 0)); /* INIT and RATE */

      /* Divider start value for clock ramp-up according to Equation 10, P6 RM Rev1 p. 1146 */
      /* DIVS = (1 + d * (k * (k + 1) / 2) * 1000 - 1 */
      /* XOSC = 40MHz: DIVS = 10839 */
      /* XOSC = 16MHz: DIVS = 25959 */
      MC_CGM_PERIPHERAL_DOMAIN.PCS_DIVS2 = 25959u;

      /* Divider end value for clock ramp-down according to Equation 8, P6 RM Rev1 p. 1145 */
      /* DIVE = (f_src2 / f_src1) * 1000 - 1 */
      /* XOSC = 40MHz: DIVE = 9999 */
      /* XOSC = 16MHz: DIVE = 24999*/
      MC_CGM_PERIPHERAL_DOMAIN.PCS_DIVE2 = 24999u;

      /* ******************************************** */
      /* Start ramp up                                */
      /* ******************************************** */

      /* DRUN mode: RC oscillator, Quartz oscillator, PLL0 on, Flash on,         */
      /*            Power Level 1                                                */

      //request mode change to DRUN
      MC_ME_PER.ModeReg.DRUN_MC = (MC_PWRLVL_1 | MC_PDO_OFF | MC_MVR_ON | MC_FLAON_NORMAL | MC_PLL0_ON | MC_XOSC_ON | MC_IROSC_ON | MC_SYSCLK_PLL0); /* switch to PLL0 + other higher Power Level to enable PCS */
      RBSYS_ModeEntry_UpdateMode(RBSYS_ModeEntryModule_Peripheral);
      RBSYS_ModeEntry_WaitForStatus(RBSYS_ModeEntryModule_Peripheral, 0x30100072u); // wait until PLL0 Stable and used

      while((PLLDIG_PERIPHERAL_DOMAIN.PLL0SR & (1<<2)) != 1<<2)
      {
        RBSYS_TEST_INJECTION_ClockModelUpdate(); /* wait unitll pLL is locked */
      }

      //< According to "When a PLL is enabled in a mode configuration register, a mode transition to that mode will not complete until the PLL is locked. Software does not need to interrogate the PLL's lock status bit." this should not be necessary -> todo
    }

    // Configure Core 0 to run in DRUN and not reset on Mode Change
    MC_ME_CL0.CoreReg.CCTL[1] = 0x8u; // This is CCTL0 (index 1), it comes after CCTL1 (index 0)
    // Request mode change to DRUN
    MC_ME_CL0.ModeReg.DRUN_MC = (MC_PWRLVL_1 | MC_PDO_OFF | MC_MVR_ON | MC_FLAON_NORMAL | MC_PLL0_ON | MC_XOSC_ON | MC_IROSC_ON | MC_SYSCLK_PLL0); /* switch to PLL0 */
    // switch mode (DRUN -> DRUN)
    RBSYS_ModeEntry_UpdateMode(RBSYS_ModeEntryModule_Domain0);
    RBSYS_ModeEntry_WaitForStatus(RBSYS_ModeEntryModule_Domain0, 0x30130072u); // wait until PLL0 Stable and used

    /* todo: do this for all Core domains */
  }
#else
  /* Currently, only Stellar Port does require centralized configuration of Peripheral Clock Frequencies */
  #define RBSYS_SetupPeripheralClocks()
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
