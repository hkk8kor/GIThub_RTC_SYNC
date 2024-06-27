#ifndef RBSYS_FLASHOPTIONBYTES_H__
#define RBSYS_FLASHOPTIONBYTES_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Declarations of structures for HCUHEX file generation
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

 /*===========================================================================*/
/* Module      = R7F701325_ExtraAreaAB.h                                     */
/* Version     = E1.0                                                        */
/*               based on FlashOptionByte table V1.10                        */
/*               generated manualy                                           */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2014 by Renesas Electronics Europe GmbH,                    */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/* Purpose:      Declarations of structures for HCUHEX file generation       */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
/* Warranty Disclaimer                                                       */
/*                                                                           */
/* Because the Product(s) is licensed free of charge, there is no warranty   */
/* of any kind whatsoever and expressly disclaimed and excluded by Renesas,  */
/* either expressed or implied, including but not limited to those for       */
/* non-infringement of intellectual property, merchantability and/or         */
/* fitness for the particular purpose.                                       */
/* Renesas shall not have any obligation to maintain, service or provide bug */
/* fixes for the supplied Product(s) and/or the Application.                 */
/*                                                                           */
/* Each User is solely responsible for determining the appropriateness of    */
/* using the Product(s) and assumes all risks associated with its exercise   */
/* of rights under this Agreement, including, but not limited to the risks   */
/* and costs of program errors, compliance with applicable laws, damage to   */
/* or loss of data, programs or equipment, and unavailability or             */
/* interruption of operations.                                               */
/*                                                                           */
/* Limitation of Liability                                                   */
/*                                                                           */
/* In no event shall Renesas be liable to the User for any incidental,       */
/* consequential, indirect, or punitive damage (including but not limited    */
/* to lost profits) regardless of whether such liability is based on breach  */
/* of contract, tort, strict liability, breach of warranties, failure of     */
/* essential purpose or otherwise and even if advised of the possibility of  */
/* such damages. Renesas shall not be liable for any services or products    */
/* provided by third party vendors, developers or consultants identified or  */
/* referred to the User by Renesas in connection with the Product(s) and/or  */
/* the Application.                                                          */
/*                                                                           */
/*===========================================================================*/
/* Environment:                                                              */
/*              Device:         R7F701325EEBG                                */
/*              IDE:            GHS Multi for V800  V6.xx or later           */
/*===========================================================================*/

#include "RBSYS_Config.h"

RB_ASSERT_SWITCH_SETTINGS(RBFS_TargetDevice,
                          RBFS_TargetDevice_RenesasD1,
                          RBFS_TargetDevice_RenesasD2,
                          RBFS_TargetDevice_RenesasD3,
                          RBFS_TargetDevice_RenesasD4,
                          RBFS_TargetDevice_RenesasD5);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSchemeExtension,
                          RBFS_TaskSchemeExtension_None,
                          RBFS_TaskSchemeExtension_VMPS,
                          RBFS_TaskSchemeExtension_HostCore0GuestCore1,
                          RBFS_TaskSchemeExtension_AB15);

#if (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5)
  #include "RBSYS_FlashOptionBytes_D5.h"
#elif (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4)
  #include "RBSYS_FlashOptionBytes_D4.h"
#elif (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3)
  #include "RBSYS_FlashOptionBytes_D3.h"
#elif (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2)
  #include "RBSYS_FlashOptionBytes_D2.h"
#elif (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1)
  #include "RBSYS_FlashOptionBytes_D1.h"
#else
  #error("Flash option bytes are located within the HEX-File, this device is not supported yet.")
#endif

RB_ASSERT_SWITCH_SETTINGS(RBFS_RBSYSSecureBootStartup,
                          RBFS_RBSYSSecureBootStartup_HSMonly,
                          RBFS_RBSYSSecureBootStartup_HSMandHost);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HardwareSecurityModule,
                          RBFS_HardwareSecurityModule_Supported,
                          RBFS_HardwareSecurityModule_Unsupported);

#define SECFLG_FALSE          1
#define SECFLG_TRUE           0

#define FLAG_FALSE            1
#define FLAG_TRUE             0

#define PROTECT_FALSE         1
#define PROTECT_TRUE          0

#define CFRPFDIS              1
#define CFRPFEN               0

#define RESERVED_1BIT         0x1u
#define RESERVED_2BIT         0x3u
#define RESERVED_3BIT         0x7u
#define RESERVED_4BIT         0xFu
#define RESERVED_5BIT         0x1Fu
#define RESERVED_6BIT         0x3Fu
#define RESERVED_8BIT         0xFFu
#define RESERVED_9BIT         0x1FFu
#define RESERVED_12BIT        0xFFFu
#define RESERVED_13BIT        0x1FFFu
#define RESERVED_14BIT        0x3FFFu
#define RESERVED_15BIT        0x7FFFu
#define RESERVED_16BIT        0xFFFFu
#define RESERVED_24BIT        0xFFFFFFu
#define RESERVED_25BIT        0x1FFFFFFu
#define RESERVED_28BIT        0xFFFFFFFu
#define RESERVED_32BIT        0xFFFFFFFFu


/** Check if HSM is really active to prevent wrong configurations */
#if( (RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Unsupported) && (RBFS_RBSYSSecureBootStartup == RBFS_RBSYSSecureBootStartup_HSMonly) )
  static_assert(0, "HSM is not active although it shall boot first");
#endif

#if( (RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Unsupported) || (RBFS_RBSYSSecureBootStartup == RBFS_RBSYSSecureBootStartup_HSMandHost) )
  /** HSM is not supported OR Host Core shall start in parallel to HSM -> Autostart Host Core 0 */
  #define STARTUPPE (0x01u)
#else
  #define STARTUPPE (0x00u)
#endif


/* Config word @ EXA-A 0x40) */
typedef struct {
    uint32 res0_23:         24;
    uint32 spie:             1;
    uint32 res25_26:         2;
    uint32 spd:              1;
    uint32 res28:            1;
    uint32 sepr:             1;
    uint32 wrpr:             1;
    uint32 rdpr:             1;
} tEXA_A_40;


/* Config word @ EXA-A 0x78) OPBT2 */
typedef struct {
    uint32 swdopwdovf:       3;
    uint32 swdopscks:        1;
    uint32 swdoprun:         1;
    uint32 res5_28:         24;
    uint32 opjtag:           2;
    uint32 res31:            1;
} tEXA_A_78;

/* Config word @ EXA-A 0x90) OPBT8 */
typedef struct {
    uint32 reserved:        28;
    uint32 icumon:           4;
} tEXA_A_90;

/* Config word @ EXA-A 0xA4) OPBT13 */
typedef struct {
    uint32 res0_4:           5;
    uint32 cvmldeten:        1;
    uint32 cvmhdeten:        1;
    uint32 res7_15:          9;
    uint32 CFRPF:            1;
    uint32 res17:            1;
    uint32 res18_31:        14;
} tEXA_A_A4;



typedef const struct {
    tEXA_A_40   ConfigData_40;
    uint32      ConfigData_44;
    uint32      ConfigData_48;
    uint32      ConfigData_4C;
    uint32      ConfigData_50;
    uint32      ConfigData_54;
    uint32      ConfigData_58;
    uint32      ConfigData_5C;
    uint32      ConfigData_60;
    uint32      ConfigData_64;
    uint32      ConfigData_68;
    uint32      ConfigData_6C;
    uint32      ConfigData_70;
    uint32      ConfigData_74;
    tEXA_A_78   ConfigData_78;
    uint32      ConfigData_7C;
    uint32      ConfigData_80;
    uint32      ConfigData_84;
    uint32      ConfigData_88;
    uint32      ConfigData_8C;
    tEXA_A_90   ConfigData_90;
    uint32      ConfigData_94;
    uint32      ConfigData_98;
    uint32      ConfigData_9C;
    uint32      ConfigData_A0;
    tEXA_A_A4   ConfigData_A4;
    uint32      ConfigData_A8;
    uint32      ConfigData_AC;
    uint32      ConfigData_B0;
    uint32      ConfigData_B4;
    uint32      ConfigData_B8;
    uint32      ConfigData_BC;
    uint32      ConfigData_C0;
    uint32      ConfigData_C4;
    uint32      ConfigData_C8;
    uint32      ConfigData_CC;
    uint32      ConfigData_D0;
    uint32      ConfigData_D4;
    uint32      ConfigData_D8;
    uint32      ConfigData_DC;
    uint32      ConfigData_E0;
    uint32      ConfigData_E4;
    uint32      ConfigData_E8;
    uint32      ConfigData_EC;
    uint32      ConfigData_F0;
    uint32      ConfigData_F4;
    uint32      ConfigData_F8;
    uint32      ConfigData_FC;
} tConfigData;



/* OTP / Lock bit flags */
typedef struct {
    uint32 CFL_BL0:          1;
    uint32 CFL_BL1:          1;
    uint32 CFL_BL2:          1;
    uint32 CFL_BL3:          1;
    uint32 CFL_BL4:          1;
    uint32 CFL_BL5:          1;
    uint32 CFL_BL6:          1;
    uint32 CFL_BL7:          1;
    uint32 CFL_BL8:          1;
    uint32 CFL_BL9:          1;
    uint32 CFL_BL10:         1;
    uint32 CFL_BL11:         1;
    uint32 CFL_BL12:         1;
    uint32 CFL_BL13:         1;
    uint32 CFL_BL14:         1;
    uint32 CFL_BL15:         1;
    uint32 CFL_BL16:         1;
    uint32 CFL_BL17:         1;
    uint32 CFL_BL18:         1;
    uint32 CFL_BL19:         1;
    uint32 CFL_BL20:         1;
    uint32 CFL_BL21:         1;
    uint32 CFL_BL22:         1;
    uint32 CFL_BL23:         1;
    uint32 CFL_BL24:         1;
    uint32 CFL_BL25:         1;
    uint32 CFL_BL26:         1;
    uint32 CFL_BL27:         1;
    uint32 CFL_BL28:         1;
    uint32 CFL_BL29:         1;
    uint32 CFL_BL30:         1;
    uint32 CFL_BL31:         1;
} tOTPLCKB;


typedef const struct {
    tOTPLCKB CFL[100/4];
} tOTP_LOCKBITS;

// Offset 0xAC
/* AMPSEL (MainOSC AMP config) */
#define AMPSEL            (0x02u)
/* CAPSEL (MainOSC capacitance config) */
#if( RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15 ) //< todo: move HW-specific settings to higher level, dont derive from TaskSchemeExtension RBFS
  // MOSC characteristic of CC-OSS Airbag MOSC
  #define CAPSEL            (0x03u)
#else
  // MOSC characteristic of CC Brakes MOSC (and VMPS)
  #define CAPSEL            (0x05u)
#endif

/* ATTENTION: When changing option byte values take care to update the option byte history for the option bytes check.
              Changes must be discussed with SiKo */

#define RBSYS_OPBT0 ( \
      ((uint32) RESERVED_3BIT       << 0)                                                                                                              \
    | ((uint32) (FAL_MODE   & 0x1u) << 3)  /* Latency mode of Code Flash access (only for D1 and D2)  1: Performance Mode     0: Normal Mode        */ \
    | ((uint32) (OPAUDR     & 0x1u) << 4)  /* AURORA Debug control                                    1: AUDR enabled         0: AUDR disabled      */ \
    | ((uint32) RESERVED_4BIT       << 5)                                                                                                              \
    | ((uint32) (ETHDISABLE & 0x1u) << 9)  /* Ethernet en-/disable                                    1: Ethernet enabled     0: Ethernet disabled  */ \
    | ((uint32) RESERVED_12BIT      << 10)                                                                                                             \
    | ((uint32) (OPWDRUN1   & 0x1u) << 22) /* WDTA1 aut. start                                        1: Automatic start      0: SW triggered start */ \
    | ((uint32) (OPWDVAC    & 0x1u) << 23) /* WDTA0/1 VAC control                                     1: VAC enabled          0: VAC diabled        */ \
    | ((uint32) (OPWD0MD    & 0x1u) << 24) /* WDTA0/1 mode sel.                                       1: Fast mode            0: Slow mode          */ \
    | ((uint32) (OPWDOVF    & 0x7u) << 25) /* WDTA0/1 clock sel.                                                                                    */ \
    | ((uint32) RESERVED_3BIT       << 28)                                                                                                             \
    | ((uint32) (OPWDRUN0   & 0x1u) << 31) /* WDTA0 automatic start                                   1: Automatic start      0: SW triggered start */ \
  )
#define RBSYS_OPBT1 ( \
      ((uint32) (PLL0PDIV & 0x7u)  << 0)  /* PLL0PDIV */ \
    | ((uint32) (PLL0NDIV & 0xFFu) << 3)  /* PLL0NDIV */ \
    | ((uint32) (PLL0MDIV & 0x7u)  << 11) /* PLL0MDIV 0,95,3 --> 240MHz for X1=20MHz*/ \
    | ((uint32) RESERVED_14BIT     << 14) \
    | ((uint32) (EXCLKIN  & 0x1u)  << 28) /* EXCLKIN (External clock control)     1: XTAL selected        0: ExtClkIn selected */ \
    | ((uint32) RESERVED_1BIT      << 29) \
    | ((uint32) (PLL0FREQ & 0x3u)  << 30) /* PLL0FREQ */ \
  )
#define RBSYS_OPBT14 ( \
      ((uint32) (STARTUPPE & 0x1u) << 0)  /* STARTUPPE (Start up PE enabler controller) */ \
    | ((uint32) RESERVED_1BIT      << 1) \
    | ((uint32) (PE2DIS    & 0x1u) << 2)  /* PE2DIS (PE2 enable disable)        1: PE2 disabled           0: PE2 eanbled */ \
    | ((uint32) RESERVED_5BIT      << 3) \
    | ((uint32) (RD_SEL    & 0x7u) << 8)  /* RD_SEL */ \
    | ((uint32) RESERVED_5BIT      << 11) \
    | ((uint32) (PE2PB     & 0x1u) << 16) /* PE2PB (PE2 parity bit)             1: Parity of PE2 enabled  0: Parity of PE2 disabled */ \
    | ((uint32) RESERVED_12BIT     << 17) \
    | ((uint32) (EMF       & 0x7u) << 29) /* EMF (Emulation mode select flag) */ \
  )
#define RBSYS_OPBT15 ( \
      ((uint32) (AMPSEL & 0x3u) << 0) /* AMPSEL (MainOSC AMP config) */ \
    | ((uint32) RESERVED_2BIT   << 2) \
    | ((uint32) (CAPSEL & 0x7u) << 4) /* CAPSEL (MainOSC capacitance config) */ \
    | ((uint32) RESERVED_25BIT  << 7) \
  )

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
