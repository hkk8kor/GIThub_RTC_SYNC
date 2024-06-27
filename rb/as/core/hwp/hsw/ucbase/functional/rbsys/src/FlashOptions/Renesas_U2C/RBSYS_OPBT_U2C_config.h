#ifndef RBSYS_OPBT_U2A_CONFIG_H__
#define RBSYS_OPBT_U2A_CONFIG_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Configuration for HCUHEX file generation
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"

RB_ASSERT_SWITCH_SETTINGS(RBFS_CodeFlashMemoryMode,
                          RBFS_CodeFlashMemoryMode_SingleMap,
                          RBFS_CodeFlashMemoryMode_DoubleMap);


#define RBFS_RBSYSuCSupplyVoltageRegulator_Disabled 1
#define RBFS_RBSYSuCSupplyVoltageRegulator_Enabled  2
#define RBFS_RBSYSuCSupplyVoltageRegulator RBFS_RBSYSuCSupplyVoltageRegulator_Enabled
/* used interfaces */
//choose the right SVR Setting
#if( RBFS_RBSYSuCSupplyVoltageRegulator == RBFS_RBSYSuCSupplyVoltageRegulator_Disabled )
  #include "RBSYS_OPBT_U2C_SVRoff.h"
#elif( RBFS_RBSYSuCSupplyVoltageRegulator == RBFS_RBSYSuCSupplyVoltageRegulator_Enabled )
  #include "RBSYS_OPBT_U2C_SVR434.h"
#endif

/* ATTENTION: When changing option byte values take care to update the option byte history for the option bytes check.
              Changes must be discussed with SiKo */

//reset vectors of PE0 to PE3
#define RESET_VECTOR_PE0   (0x00000000u)
#define RESET_VECTOR_PE1   (0x00000000u)
#define RESET_VECTOR_PE2   (0x00000000u)
#define RESET_VECTOR_PE3   (0x00000000u)

//OPBT3 - Bist and Mode control
#define c_STMSEL0            (0x0u)
#define c_STMSEL1            (0x0u)
#define c_LBISTSEL           (0x2u)
#define c_TESTSET            (0x3u)
#define c_HWBIST             (0x1u) // HWBist enabled by default
#define c_PE1_DISABLE        (0x0u)
#define c_PE2_DISABLE        (0x1u)
#define c_PE3_DISABLE        (0x1u)

//OPBT10 - Clock and MOSC control
#define c_MOSC_SHTSTBY_B     (0x0u)
#define c_MOSC_SHTSTBY_A     (0x1u)
#define c_MOSC_RD_SEL_B      (0x1u)
#define c_MOSC_RD_SEL_A      (0x1u)
#define c_MOSC_CAP_SEL       (0x2u)
#define c_MOSC_AMP_SEL_B     (0x7u)
#define c_MOSC_AMP_SEL_A     (0x7u)
#define c_MOSC_FREQ          (0x0u)    //0=16MHz, 1=20MHz, 2=24MHz, 3=40MHz
#define c_MOSC_EXCLKINPUT    (0x1u)    //0=direct clock, 1=oscillator

//OPBT11 - CPU frequency and PLL control
#define c_STARTUPPLL         (0x0u)    //enable PLL at power on 0=enabled, 1=disabled
#define c_CKDIVMOD           (0x3u)    //max CPU frequency 0=240MHz, 2=320MHz, 3=400MHz

//OPBT12 Program Flash Mapping Mode
#if( RBFS_CodeFlashMemoryMode == RBFS_CodeFlashMemoryMode_DoubleMap )
  // M3: Double Map 4MB usable PFlash (only A, B allowed!)
  // M6: Double Map 8MB usable PFlash (only A + C, B + D allowed!)
  #define c_MAPMODE            (0x0u)
#else
  #define c_MAPMODE            (0x1u)    // Single Map 8MB / 16MB PFlash
#endif

#endif
