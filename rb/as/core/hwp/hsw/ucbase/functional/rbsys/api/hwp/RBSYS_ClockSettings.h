#ifndef RBSYS_CLOCKSETTINGS_H__
#define RBSYS_CLOCKSETTINGS_H__

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
#include <assert.h>                           // for static_assert()


/* used interfaces */



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_CpuClock,
                          RBFS_CpuClock_80MHz,
                          RBFS_CpuClock_160MHz,
                          RBFS_CpuClock_240MHz,
                          RBFS_CpuClock_320MHz,
                          RBFS_CpuClock_400MHz);

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

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCWatchdog,
                          RBFS_uCWatchdog_Enabled,
                          RBFS_uCWatchdog_Disabled);


/** Hint: RBSYS_CPU_CLK_KHZ must be kept equal to 1000 * FlsRbHclk as defined in the corresponding
 *  Fls EcucValues (see rb\as\core\hwp\cubas\MemStack\cfg\Fls\Fls_DF_*_EcucValues.arxml).
 *  A sanity check is already implemented within rb\as\core\hwp\cubas\MemStack\cfg\Fls\Fls_SanityChecks.c.
 */

/* clock settings configured via FLASH Option (fix till now) */
#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)

  #if (RBFS_CpuClock == RBFS_CpuClock_80MHz)
    #define RBSYS_CPU_CLK_KHZ     ((uint32) 80000)  /* Each core is working at CLK_CPU: 80 MHz */
    #define RBSYS_STM_CLK_KHZ     ((uint32) 80000)  /* System Timer peripheral clock is 80 MHz */
    #define RBSYS_GTM_CLK_KHZ     ((uint32) 80000)  /* GTM peripheral clock is 80 MHz */
    #define RBSYS_CAN_CLK_KHZ     ((uint32) 80000)  /* M(TT)CAN and MCAN peripheral clock is 80 MHz */
    #define RBSYS_RLIN3_CLK_KHZ   ((uint32) 40000)  /* RLIN3 / UART clock frequency is set to 40 MHz */
    #define RBSYS_SPI_CLK_KHZ     ((uint32) 80000)  /* SPI clock frequency is set to 80 MHz */
  #endif

  #if (RBFS_CpuClock == RBFS_CpuClock_160MHz)
    #define RBSYS_CPU_CLK_KHZ     ((uint32)160000)  /* Each core is working at CLK_CPU: 160 MHz */
    #define RBSYS_STM_CLK_KHZ     ((uint32) 80000)  /* System Timer peripheral clock is 80 MHz */
    #define RBSYS_GTM_CLK_KHZ     ((uint32) 80000)  /* GTM peripheral clock is 80 MHz */
    #define RBSYS_CAN_CLK_KHZ     ((uint32) 80000)  /* M(TT)CAN and MCAN peripheral clock is 80 MHz */
    #define RBSYS_RLIN3_CLK_KHZ   ((uint32) 40000)  /* RLIN3 / UART clock frequency is set to 40 MHz */
    #define RBSYS_SPI_CLK_KHZ     ((uint32)160000)  /* SPI clock frequency is set to 160 MHz */
  #endif

  #if (RBFS_CpuClock == RBFS_CpuClock_240MHz)
    #define RBSYS_CPU_CLK_KHZ     ((uint32)240000)  /* Each core is working at CLK_CPU: 240 MHz */
    #define RBSYS_STM_CLK_KHZ     ((uint32) 80000)  /* System Timer peripheral clock is 80 MHz */
    #define RBSYS_GTM_CLK_KHZ     ((uint32) 80000)  /* GTM peripheral clock is 80 MHz */
    #define RBSYS_CAN_CLK_KHZ     ((uint32) 80000)  /* M(TT)CAN and MCAN peripheral clock is 80 MHz */
    #define RBSYS_RLIN3_CLK_KHZ   ((uint32) 40000)  /* RLIN3 / UART clock frequency is set to 40 MHz */
    #define RBSYS_SPI_CLK_KHZ     ((uint32)160000)  /* SPI clock frequency is set to 160 MHz */
  #endif

  // Restriction by Renesas HW Erratum RB110 for devices D3-D5: CLK_HSB < CLKP_C < (3 x CLK_HSB)
  // Hint: CLK_HSB is e.g. used for STM; CLKP_C is the peripheral Clock for SPI
  #if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4) \
    || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5) )
    static_assert( (RBSYS_STM_CLK_KHZ < RBSYS_SPI_CLK_KHZ) && (RBSYS_SPI_CLK_KHZ < (3*RBSYS_STM_CLK_KHZ)),
                  "Clock Tree setting is not correct (see RB110)" );
  #endif

  // Renesas D3 may be configured for CPU Clock 160MHz oder 240MHz only.
  #if( RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3 )
    #if( (RBFS_CpuClock != RBFS_CpuClock_160MHz) \
      && (RBFS_CpuClock != RBFS_CpuClock_240MHz) )
      static_assert( 0, "Renesas D3 may only be configured for 160MHz or 240MHz CPU Frequency");
    #endif
  #endif

#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )

  #if (RBFS_CpuClock == RBFS_CpuClock_400MHz)
    #define RBSYS_CPU_CLK_KHZ       ((uint32)400000)  /* Each core is working at CLK_CPU: 400 MHz */
    #define RBSYS_STM_CLK_KHZ       ((uint32) 80000)  /* OS Timer is running with 80MHz */
    #define RBSYS_GTM_CLK_KHZ       ((uint32)160000)  /* GTM main clock is 160 MHz, but register access clock is 80MHz*/
    #define RBSYS_CAN_CLK_KHZ       ((uint32) 40000)  /* RS-CAN peripheral clock is 40 MHz */
    #define RBSYS_RLIN3_CLK_KHZ     ((uint32) 80000)  /* RLIN3 / UART clock frequency is set to 80 MHz */
    #define RBSYS_SPI_CLK_KHZ       ((uint32) 80000)  /* SPI clock frequency is set to 80 MHz */
    #define RBSYS_HSB_CLK_KHZ       ((uint32) 80000)  /* Peripheral high speed clock: HSB CLK (80 MHz) */
    #define RBSYS_TAUD0_CK0_CLK_KHZ ((uint32) 40000)  /* TAUD0 CK0 is set to 40MHz */
  #endif

#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )

  #if (RBFS_CpuClock == RBFS_CpuClock_320MHz)
    #define RBSYS_CPU_CLK_KHZ       ((uint32)320000)  /* Each core is working at CLK_CPU: 400 MHz */
    #define RBSYS_STM_CLK_KHZ       ((uint32) 80000)  /* OS Timer is running with 80MHz */
    #define RBSYS_GTM_CLK_KHZ       ((uint32)160000)  /* GTM main clock is 160 MHz, but register access clock is 80MHz*/
    #define RBSYS_CAN_CLK_KHZ       ((uint32) 80000)  /* RS-CAN peripheral clock is 80 MHz */
    #define RBSYS_RLIN3_CLK_KHZ     ((uint32) 80000)  /* RLIN3 / UART clock frequency is set to 80 MHz */
    #define RBSYS_SPI_CLK_KHZ       ((uint32) 80000)  /* SPI clock frequency is set to 80 MHz */
    #define RBSYS_HSB_CLK_KHZ       ((uint32) 80000)  /* Peripheral high speed clock: HSB CLK (80 MHz) */
    #define RBSYS_TAUD0_CK0_CLK_KHZ ((uint32) 80000)  /* TAUD0 CK0 is set to 100MHz */
  #endif

#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

  #if (RBFS_CpuClock == RBFS_CpuClock_400MHz)
    #define RBSYS_CPU_CLK_KHZ       ((uint32)400000)  /* Each core is working at CLK_CPU: 400 MHz */
    #define RBSYS_STM_CLK_KHZ       ((uint32)100000)  /* OS Timer is running with 100MHz */
    #define RBSYS_GTM_CLK_KHZ       ((uint32)200000)  /* GTM main clock is 200 MHz, but register access clock is 80MHz*/
    #define RBSYS_CAN_CLK_KHZ       ((uint32) 80000)  /* CAN peripheral clock is 80 MHz */
    #define RBSYS_SPI_CLK_KHZ       ((uint32) 80000)  /* SPI clock frequency is set to 80 MHz */
  #endif

#else
  #error ("Clock Frequency definition is missing for this uCFamily")
#endif


/* External clock default setting is 4 MHz */
#define RBSYS_ECLK_DEFAULT_KHZ  ((uint16) 4000)



/**
 * @brief Setup External Clock Output Pin 0 (ECLK0)
 *
 * @param [in] ECLK_KHZ     Target frequency in khz for ECLK0
 *
 * @return void
 */
extern void RBSYS_SetupECP(uint16 ECLK_KHZ);


#if ((RBFS_uCWatchdog == RBFS_uCWatchdog_Enabled) && ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)))
  typedef enum {
    RBSYS_CLK_WDT_DIVIDER_20,
    RBSYS_CLK_WDT_DIVIDER_640,
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
      RBSYS_CLK_WDT_DIVIDER_800,
    #endif
  } RBSYS_CLK_WDT_Divider_t;

  /**
   * @brief Get the clock divider for the Watchdog clock
   *
   * @return RBSYS_CLK_WDT_Divider_t which indicates which clock divider is used for the watchdog clock
   */
  extern RBSYS_CLK_WDT_Divider_t RBSYS_getClkWdtDivider(void);
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
