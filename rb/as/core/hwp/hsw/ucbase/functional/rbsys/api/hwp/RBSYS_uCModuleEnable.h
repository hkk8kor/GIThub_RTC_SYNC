#ifndef RBSYS_UCMODULEENABLE_H__
#define RBSYS_UCMODULEENABLE_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file RBSYS_uCModuleEnable.h
 * @brief uC peripheral startup handling
 *
 * Dependent on uC device, some peripherals must be explicitly switched from standby mode to run mode.
 * The strategy is to enable all available instances of the corresponding peripheral.
 * This must be done before first usage by the responsible SW part that owns the peripheral.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */



/* Assert supported configurations: switches, parameters, constants, ... */
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

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_EmulationDevice,
                          RBFS_EmulationDevice_None,
                          RBFS_EmulationDevice_RenesasD3ED,
                          RBFS_EmulationDevice_RenesasD5ED,
                          RBFS_EmulationDevice_RenesasD7ED,
                          RBFS_EmulationDevice_RenesasM6ED,
                          RBFS_EmulationDevice_RenesasK3ED);


/**
 * @brief Set CAN module to run mode
 *
 * After uC reset is released, CAN module enter in standby mode. This requires an activation before first usage
 * via this function. It activates the clock for the peripheral and switches from standby to run mode.
 *
 * @return void
 */
extern void RBSYS_CAN_SetToRunMode(void);

/**
 * @brief Set GTM module to run mode
 *
 * After uC reset is released, GTM module enter in standby mode. This requires an activation before first usage
 * via this function. It activates the clock for the peripheral and switches from standby to run mode.
 *
 * @return void
 */
extern void RBSYS_GTM_SetToRunMode(void);

/**
 * @brief Set SENT module to run mode
 *
 * After uC reset is released, SENT module enter in standby mode. This requires an activation before first usage
 * via this function. It activates the clock for the peripheral and switches from standby to run mode.
 *
 * @return void
 */
extern void RBSYS_SENT_SetToRunMode(void);

/**
 * @brief Set SPI module to run mode
 *
 * After uC reset is released, SPI module enter in standby mode. This requires an activation before first usage
 * via this function. It activates the clock for the peripheral and switches from standby to run mode.
 *
 * @return void
 */
extern void RBSYS_SPI_SetToRunMode(void);

/**
 * @brief Set RLIN3 module to run mode
 *
 * After uC reset is released, RLIN3 module enter in standby mode. This requires an activation before first usage
 * via this function. It activates the clock for the peripheral and switches from standby to run mode.
 *
 * @return void
 */
extern void RBSYS_RLIN3_SetToRunMode(void);

/**
 * @brief Set ADC module to run mode
 *
 * After uC reset is released, ADC module enter in standby mode. This requires an activation before first usage
 * via this function. It activates the clock for the peripheral and switches from standby to run mode.
 *
 * @return void
 */
extern void RBSYS_ADC_SetToRunMode(void);


/* For Renesas devices D1 and D2, there are no module standby registers avalable */

#if((RBFS_TargetDevice != RBFS_TargetDevice_RenesasD1) && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD2))
  /**
   * @brief Set FlexRay module to run mode
   *
   * After uC reset is released, FlexRay module enter in standby mode. This requires an activation before first usage
   * via this function. It activates the clock for the peripheral and switches from standby to run mode.
   *
   * @return void
   */
  extern void RBSYS_FlexRay_SetToRunMode(void);

  /**
   * @brief Set Ethernet module to run mode
   *
   * After uC reset is released, Ethernet module enter in standby mode. This requires an activation before first usage
   * via this function. It activates the clock for the peripheral and switches from standby to run mode.
   *
   * @return void
   */
  extern void RBSYS_Ethernet_SetToRunMode(void);

  
  #if((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  || ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ) && (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasK3ED))) 
    /**
    * @brief Set HS-USART module to run mode
    *
    * After uC reset is released, HS-USART module enter in standby mode. This requires an activation before first usage
    * via this function. It activates the clock for the peripheral and switches from standby to run mode.
    *
    * @return void
    */
    extern void RBSYS_HSUSRT_SetToRunMode(void);
  #endif

#endif

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  /**
   * @brief Set TAUD0 module to run mode
   *
   * After uC reset is released, TAUD0 module enter in standby mode. This requires an activation before first usage
   * via this function. It activates the clock for the peripheral and switches from standby to run mode.
   *
   * @return void
   */
  extern void RBSYS_TAUD0_SetToRunMode(void);
#endif

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
