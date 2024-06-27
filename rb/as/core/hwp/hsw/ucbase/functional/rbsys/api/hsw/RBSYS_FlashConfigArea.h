#ifndef RBSYS_FLASHCONFIGAREA_H__
#define RBSYS_FLASHCONFIGAREA_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Declarations of OPBT getter functions
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"

/* used interfaces */

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C);


#if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)

  /**
   * @brief Enum of all Option Bytes
   *
   * CAUTION: Order of RBSYS_OPBT_Addresses must match up!
   */
  typedef enum
  {
    RBSYS_FlashConfigAreaSetting_ResetVector,
    RBSYS_FlashConfigAreaSetting_OPBT0,
    RBSYS_FlashConfigAreaSetting_OPBT1,
    RBSYS_FlashConfigAreaSetting_OPBT14,
    RBSYS_FlashConfigAreaSetting_OPBT15,
    RBSYS_FlashConfigAreaSetting_MaxNumberOfSettings,
  } RBSYS_FlashConfigAreaSetting_t;

#elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)

  /**
   * @brief Enum of all Option Bytes
   *
   * CAUTION: Order of RBSYS_OPBT_Addresses must match up!
   */
  typedef enum
  {
    RBSYS_FlashConfigAreaSetting_ResetVectorPE0,
    RBSYS_FlashConfigAreaSetting_ResetVectorPE1,
    RBSYS_FlashConfigAreaSetting_ResetVectorPE2,
    RBSYS_FlashConfigAreaSetting_ResetVectorPE3,
    RBSYS_FlashConfigAreaSetting_OPBT0,
    RBSYS_FlashConfigAreaSetting_OPBT1,
    RBSYS_FlashConfigAreaSetting_OPBT2,
    RBSYS_FlashConfigAreaSetting_OPBT3,
    RBSYS_FlashConfigAreaSetting_OPBT4,
    RBSYS_FlashConfigAreaSetting_OPBT6,
    RBSYS_FlashConfigAreaSetting_OPBT7,
    RBSYS_FlashConfigAreaSetting_OPBT8,
    RBSYS_FlashConfigAreaSetting_OPBT9,
    RBSYS_FlashConfigAreaSetting_OPBT10,
    RBSYS_FlashConfigAreaSetting_OPBT11,
    RBSYS_FlashConfigAreaSetting_OPBT12,
    RBSYS_FlashConfigAreaSetting_OPBT13,
    RBSYS_FlashConfigAreaSetting_OPBT14,
    RBSYS_FlashConfigAreaSetting_OPBT16,
    RBSYS_FlashConfigAreaSetting_OPBT17,
    RBSYS_FlashConfigAreaSetting_OPBT18,
    RBSYS_FlashConfigAreaSetting_OPBT19,
    RBSYS_FlashConfigAreaSetting_OPBT20,
    RBSYS_FlashConfigAreaSetting_OPBT21,
    RBSYS_FlashConfigAreaSetting_OPBT22,
    RBSYS_FlashConfigAreaSetting_OPBT23,
    RBSYS_FlashConfigAreaSetting_MaxNumberOfSettings,
  } RBSYS_FlashConfigAreaSetting_t;

#elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
  //todo: check

  /**
   * @brief Enum of all Option Bytes
   *
   * CAUTION: Order of RBSYS_OPBT_Addresses must match up!
   */
  typedef enum
  {
    RBSYS_FlashConfigAreaSetting_ResetVectorPE0,
    RBSYS_FlashConfigAreaSetting_ResetVectorPE1,
    RBSYS_FlashConfigAreaSetting_ResetVectorPE2,
    RBSYS_FlashConfigAreaSetting_ResetVectorPE3,
    RBSYS_FlashConfigAreaSetting_OPBT0,
    RBSYS_FlashConfigAreaSetting_OPBT1,
    RBSYS_FlashConfigAreaSetting_OPBT2,
    RBSYS_FlashConfigAreaSetting_OPBT3,
    RBSYS_FlashConfigAreaSetting_OPBT4,
    RBSYS_FlashConfigAreaSetting_OPBT6,
    RBSYS_FlashConfigAreaSetting_OPBT7,
    RBSYS_FlashConfigAreaSetting_OPBT8,
    RBSYS_FlashConfigAreaSetting_OPBT9,
    RBSYS_FlashConfigAreaSetting_OPBT10,
    RBSYS_FlashConfigAreaSetting_OPBT11,
    RBSYS_FlashConfigAreaSetting_OPBT12,
    RBSYS_FlashConfigAreaSetting_OPBT13,
    RBSYS_FlashConfigAreaSetting_OPBT14,
    RBSYS_FlashConfigAreaSetting_OPBT16,
    RBSYS_FlashConfigAreaSetting_OPBT17,
    RBSYS_FlashConfigAreaSetting_OPBT18,
    RBSYS_FlashConfigAreaSetting_OPBT19,
    RBSYS_FlashConfigAreaSetting_OPBT20,
    RBSYS_FlashConfigAreaSetting_OPBT21,
    RBSYS_FlashConfigAreaSetting_OPBT22,
    RBSYS_FlashConfigAreaSetting_OPBT23,
    RBSYS_FlashConfigAreaSetting_MaxNumberOfSettings,
  } RBSYS_FlashConfigAreaSetting_t;

#endif

typedef struct
{
  RBSYS_FlashConfigAreaSetting_t type;
  uint32 value;
} RBSYS_FlashConfigArea_ExpectedValues_t;

/**
 * @brief Getter for Option Byte values
 *
 * @param opbt_id (RBSYS_FlashConfigAreaSetting_t)     Specifies the option byte to get the value for
 *
 * @return Option Byte value
 */
extern uint32 RBSYS_FlashConfigArea_GetCurrentValue(RBSYS_FlashConfigAreaSetting_t opbt_id);

/**
 * @brief Getter for list of valid option bytes values
 *
 * @return List of option bytes mapping to valid values. Same option byte may appear multiple times if it has multiple valid values.
 */
extern const RBSYS_FlashConfigArea_ExpectedValues_t* RBSYS_FlashConfigArea_GetValidValues(void);

/**
 * @brief Getter for size of list of valid option bytes values
 *
 * @return Size of list obtained with RBSYS_FlashConfigArea_GetValidOpbtValues()
 */
extern uint32 RBSYS_FlashConfigArea_GetValidValuesSize(void);


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
