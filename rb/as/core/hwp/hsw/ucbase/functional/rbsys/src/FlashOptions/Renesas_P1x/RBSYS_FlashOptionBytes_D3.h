#ifndef RBSYS_FLASHOPTIONBYTES_D3_H__
#define RBSYS_FLASHOPTIONBYTES_D3_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Flash Option Bytes defines for Renesas D3
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_CpuClock,
                          RBFS_CpuClock_160MHz,
                          RBFS_CpuClock_240MHz);

RB_ASSERT_SWITCH_SETTINGS(RBFS_Ethernet,
                          RBFS_Ethernet_Enabled,
                          RBFS_Ethernet_Disabled);

/* ATTENTION: When changing option byte values take care to update the option byte history for the option bytes check.
              Changes must be discussed with SiKo */

// Offset 0x60
#define PE_RESET_VECTOR   (0x00000000u)

// Offset 0x70
#define FAL_MODE          (1u)     /* Only available on D1 and D2 devices, flag is reserved and must be 1 for all other devices */
#define OPAUDR            (1u)

#if( RBFS_Ethernet == RBFS_Ethernet_Enabled )
  #define ETHDISABLE      (1u)     /* enable Ethernet module */
#else
  #define ETHDISABLE      (0u)     /* disable Ethernet module */
#endif

#define OPWDRUN1          (1u)     /* Has to be '1' for D3/D3ED Mode (see UM R01UH0490EJ0130 p.3330) */
#define OPWDVAC           (0u)
#define OPWD0MD           (0u)
#define OPWDOVF           (0x07u)
#define OPWDRUN0          (0u)

#if (RBFS_CpuClock == RBFS_CpuClock_240MHz)
  // Offset 0x74 --> 240Mhz
  #define PLL0PDIV        (0x00u)
  #define PLL0NDIV        (0x3Bu)
  #define PLL0MDIV        (0x01u)
#elif (RBFS_CpuClock == RBFS_CpuClock_160MHz)
  // Offset 0x74 --> 160Mhz
  #define PLL0PDIV        (0x00u)
  #define PLL0NDIV        (0x27u)
  #define PLL0MDIV        (0x01u)
#endif

#define EXCLKIN           (0x01u)  /* EXCLKIN (External clock control)     1: XTAL selected        0: ExtClkIn selected */

#if (RBFS_CpuClock == RBFS_CpuClock_240MHz)
  #define PLL0FREQ        (0x02u)
#elif (RBFS_CpuClock == RBFS_CpuClock_160MHz)
  #define PLL0FREQ        (0x01u)
#endif

// Offset 0x78
#define SWDOPWDOVF        (0x07)  /* SWDOPWDOVF (SWDT clock sel.)*/
#define SWDOPSCKS         (1)     /* SWDOPSCKS (SWDT mode sel.)           1: Fast mode            0: Slow mode (depending on the value in CKSC4C - if default 0x8 is set) */
#define SWDOPRUN          (1)     /* SWDOPRUN (SWDT aut. start)           1: Automatic start      0: SW triggered start */
#define OPJTAG            (3)     /* OPJTAG (1= LPD 4-pin; 2= LPD 1-pin; 3= JTAG; )*/

// Offset 0xA4
#define CVMLDETEN         (0x01)  /* CVMLDETEN (CVM low detec. enable)  1: Enable low detect.     0: Disable low detect.*/
#define CVMHDETEN         (0x01)  /* CVMHDETEN (CVM HIGH detec. enable) 1: Enable high detect.    0: Disable high detect.*/

// Offset 0xA8
#define PE2DIS            (0x01u)  /* PE2DIS (PE2 enable disable)        1: PE2 disabled           0: PE2 enabled */
#define RD_SEL            (0x04u)  /* RD_SEL */
#define PE2PB             (0x01u)  /* PE2PB (PE2 parity bit)             1: Parity of PE2 enabled  0: Parity of PE2 disabled */
#define EMF               (0x05u)  /* EMF (Emulation mode select flag) */



/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
