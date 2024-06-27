/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Initialization of structures for HCUHEX file generation
 *
 * Standard hexfile contains only the program code, the additional device configuration
 * for Renesas CC CUBE (security settings, option bytes, OTP settings, ...) must be
 * programmed separately by flash programming tools like the RFP or via self-programming.
 * A HCUHEX file enables the user to generate one hexfile which contains both, the
 * program code and the additional device information.
 * The Renesas Flash Programming (RFP) tool can program by one command such file
 * with the whole data. Thereby, it is ensured that the SW always runs with the
 * correct device configuration and miss-configuration (e.g. wrong PLL setting) can be
 * avoided.
 * In the HCUHEX file the additional information are mapped to an unused memory area.
 * When the RFP detects an HCUHEX file, it can translate this "dummy" addresses to the
 * corresponding flash area for config data, OTP settings and Lockbit settings.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

 /*===========================================================================*/
/* Module      = R7F701325_ExtraAreaAB.c                                     */
/* Version     = E1.0                                                        */
/*               based on FlashOptionByte table V1.10                        */
/*               generated manualy                                           */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2014 by Renesas Electronics Europe GmbH,                    */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/* Purpose:      Initialization of structures for HCUHEX file generation     */
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

/* used interfaces */
#include "RBLCF_MemoryRemap.h"
#include "RBLCF_Hexblocks_Layout.h"
#include "RBSYS_uCRegisters.h"

/* realized interfaces */
#include "RBSYS_FlashConfigArea.h"
#include "RBSYS_FlashOptionBytes.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TargetDevice,
                          RBFS_TargetDevice_RenesasD1,
                          RBFS_TargetDevice_RenesasD2,
                          RBFS_TargetDevice_RenesasD3,
                          RBFS_TargetDevice_RenesasD4,
                          RBFS_TargetDevice_RenesasD5);

RB_ASSERT_SWITCH_SETTINGS(RBFS_CpuClock,
                          RBFS_CpuClock_80MHz,
                          RBFS_CpuClock_160MHz,
                          RBFS_CpuClock_240MHz);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HardwareSecurityModule,
                          RBFS_HardwareSecurityModule_Supported,
                          RBFS_HardwareSecurityModule_Unsupported);

RB_ASSERT_SWITCH_SETTINGS(RBFS_BUILDTYPE,
                          RBFS_BUILDTYPE_RELEASE,
                          RBFS_BUILDTYPE_DEVELOP);

RB_ASSERT_SWITCH_SETTINGS(RBFS_ReprogDriverSupport,
                          RBFS_ReprogDriverSupport_ON,
                          RBFS_ReprogDriverSupport_OFF);



#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)

/* Functions to provide the expected (configured in software and expected value for this application)
 * and the actual (configured in HW) value of certain parts of the flash config area.
 * Currently only provides values for parts needed by RBROMSafety.           */

/** CAUTION: RBSYS_OPBT_Addresses, RBSYS_OPBT_ExpectedValues and RBSYS_OPBT must match up! */
static const volatile uint32* const RBSYS_OPBT_Addresses[RBSYS_FlashConfigAreaSetting_MaxNumberOfSettings] =
{
  &GREG8,
  &OPBT0,
  &OPBT1,
  &OPBT14,
  &OPBT15,
};

/* Current and past values of option bytes, past values are needed for safety critical option bytes checked via RBROMSafety Option Bytes Check */
static const RBSYS_FlashConfigArea_ExpectedValues_t RBSYS_OPBT_ExpectedValues[] =
{
    {RBSYS_FlashConfigAreaSetting_ResetVector, PE_RESET_VECTOR},
    {RBSYS_FlashConfigAreaSetting_OPBT1,       RBSYS_OPBT1},
    {RBSYS_FlashConfigAreaSetting_OPBT14,      RBSYS_OPBT14},
    {RBSYS_FlashConfigAreaSetting_OPBT15,      RBSYS_OPBT15},
};

#define RBSYS_OPBT_EXPECTEDVALUES_SIZE   (sizeof(RBSYS_OPBT_ExpectedValues)/sizeof(RBSYS_OPBT_ExpectedValues[0]))

uint32 RBSYS_FlashConfigArea_GetCurrentValue(RBSYS_FlashConfigAreaSetting_t opbt_id)
{
  assert(opbt_id < RBSYS_FlashConfigAreaSetting_MaxNumberOfSettings);
  return *RBSYS_OPBT_Addresses[opbt_id];
}

const RBSYS_FlashConfigArea_ExpectedValues_t* RBSYS_FlashConfigArea_GetValidValues(void)
{
  return RBSYS_OPBT_ExpectedValues;
}

uint32 RBSYS_FlashConfigArea_GetValidValuesSize(void)
{
  return RBSYS_OPBT_EXPECTEDVALUES_SIZE;
}


/* The following value is agreed to be fix between GUAM development and HSW */
#define RBSYS_HSM_INTVECS_OFFSET        (16 * 1024u)


/* ------------------------------------------------------------------------------------------------
   SW workaround for GHS compiler incident 65175:
   __attribute__((used)) will not work as expected on current available GHS compiler suite.
   Due to an internal compiler issue it's not possible to declare the flash option byte structures itself
   as static const. The compiler will still remove the whole structure even with usage of the
   attribute used because there is no visible reference. This problem should be fixed in the
   v2016.5 final release. Until then keep the external visibility.
   --------------------------------------------------------------------------------------------- */


RBSECTION_START_HCU_CONFIG
/**
 * @brief Definition of the Flash Option Bytes
 *
 * The option bytes of the flash memory are an extended area and hold project specific
 * device configuration data. Initial settings specified by the option bytes become
 * effective after reset release.
 */
tConfigData RBSYS_FlashConfigArea_Config =
{

  /* Address: 40h, Security Flags */
  {
    RESERVED_24BIT,
    SECFLG_FALSE,           /* SPIE (Ser. Progr. ID enable)         TRUE: ID auth. in serial progr. mode enabled;     FALSE: ID auth. in serial progr. mode is disabled*/
    RESERVED_2BIT,
    SECFLG_FALSE,           /* SPD (Serial Programming Disable)     TRUE: Serial Prog. is diabled                     FALSE: Serial Prog. is enabled*/
    RESERVED_1BIT,
    SECFLG_FALSE,           /* SEPR (Block Erase Protection)        TRUE: Block Erase disabled                        FALSE: Block Erase enabled*/
    SECFLG_FALSE,           /* WRPR (Write Protection)              TRUE: Ser. Prog. write disabled                   FALSE: Ser. Prog. write enabled*/
    SECFLG_FALSE            /* RDPR (Read Protection)               TRUE: Ser. Prog. read disabled                    FALSE: Ser. Prog. read enabled*/
  },

  /* Address: 44h */
  RESERVED_32BIT,

  /* Address: 48h */
  RESERVED_32BIT,

  /* Address: 4Ch */
  RESERVED_32BIT,

  /* Address: 50h, ID 0-3 (first 128bit)*/
  0xFFFFFFFFu,
  0xFFFFFFFFu,
  0xFFFFFFFFu,
  0xFFFFFFFFu,

  /* Address: 60h, Reset Vector */
  PE_RESET_VECTOR,

  /* Address: 64h */
  RESERVED_32BIT,

  /* Address: 68h */
  RESERVED_32BIT,

  /* Address: 6Ch */
  RESERVED_32BIT,

  /* Address: 70h, OPBT0 */
  RBSYS_OPBT0,

  /* Address: 74h, OPBT1 */
  RBSYS_OPBT1,

  /* Address: 78h, OPBT2 */
  {
    SWDOPWDOVF,           /* SWDOPWDOVF (SWDT clock sel.)*/
    SWDOPSCKS,            /* SWDOPSCKS (SWDT mode sel.)           1: Fast mode            0: Slow mode (depending on the value in CKSC4C - if default 0x8 is set) */
    SWDOPRUN,             /* SWDOPRUN (SWDT aut. start)           1: Automatic start      0: SW triggered start */
    RESERVED_24BIT,
    OPJTAG,               /* OPJTAG 00: GPIO,
                                    01: LPD 4-pin
                                    10: setting prohibited
                                    11: JTAG */
    RESERVED_1BIT
  },

  /* Address: 7Ch, OPBT3 */
  0xFFFFFFFFu,            /* SWDPCCADDR */

  /* Address: 80h, OPBT4 */
  RESERVED_32BIT,

  /* Address: 84h, OPBT5 */
  RESERVED_32BIT,

  /* Address: 88h, OPBT6*/
  RESERVED_32BIT,

  /* Address: 8Ch, OPBT7*/
  RESERVED_32BIT,

  /* Address: 90h, OPBT8 */
  {
    RESERVED_28BIT,
    0x0                   /* [D5ED, D5, D4, D3] see ALM Task 96500 */
  },

  #if (RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Supported)
    /* Address: 94h, OPBT9 */
    (RBLCF_HSM_CFLASH_START + RBSYS_HSM_INTVECS_OFFSET),

    /* Workaround for Reprog limitation with XFlash - only needed when RBBootloader is not used (flashing via Download Module) */
    #if ((RBFS_BUILDTYPE == RBFS_BUILDTYPE_RELEASE) || (RBFS_ReprogDriverSupport == RBFS_ReprogDriverSupport_OFF))
      /* Address: 98h, OPBT10 */
      RBLCF_HSM_CFLASH_START,
    #else
      /* Address: 98h, OPBT10 - Workaround for limitation with XFlash using reprog download driver */
      RBLCF_HSM_LRAM_START, // some address behind CFlash, HSM CFlash Guard should not protect HSM CFlash
    #endif

    /* Address: 9Ch, OPBT11 */
    0xFF3002C0u,

    /* Address: A0h, OPBT12 */
    0xFFFCFFCFu,

  #else
    /* Address: 94h, OPBT9 */
    RESERVED_32BIT,

    /* Address: 98h, OPBT10 */
    RESERVED_32BIT,

    /* Address: 9Ch, OPBT11 */
    RESERVED_32BIT,

    /* Address: A0h, OPBT12 */
    RESERVED_32BIT,

  #endif

  /* Address: A4h, OPBT13 */
  {
    RESERVED_5BIT,
    CVMLDETEN,            /* CVMLDETEN (CVM low detec. enable)  1: Enable low detect.     0: Disable low detect.*/
    CVMHDETEN,            /* CVMHDETEN (CVM HIGH detec. enable) 1: Enable high detect.    0: Disable high detect.*/
    RESERVED_9BIT,
    CFRPFEN,              /* CFRPFEN (CFRPF - Code Flash Read Protection Flag) 1: Password authentication is not needed.  0: Password authentication IS needed. */
    RESERVED_1BIT,
    RESERVED_14BIT
  },

  /* Address: A8h, OPBT14 */
  RBSYS_OPBT14,

  /* Address: ACh, OPBT15 */
  RBSYS_OPBT15,

  /* Address: B0h */
  0xFFFFFFFFu,            /* ID 4-7 (last 128bit) */
  0xFFFFFFFFu,
  0xFFFFFFFFu,
  0xFFFFFFFFu,

  /* Address: C0h */
  RESERVED_32BIT,
  RESERVED_32BIT,
  RESERVED_32BIT,
  RESERVED_32BIT,
  RESERVED_32BIT,
  RESERVED_32BIT,
  RESERVED_32BIT,
  RESERVED_32BIT,

  /* Address: E0h */
  RESERVED_32BIT,
  RESERVED_32BIT,
  RESERVED_32BIT,
  RESERVED_32BIT,
  RESERVED_32BIT,
  RESERVED_32BIT,
  RESERVED_32BIT,
  RESERVED_32BIT
};

RBSECTION_END_HCU_CONFIG



RBSECTION_START_HCU_OTP
/**
 * @brief Definition of the "One Time Programmable" bits
 *
 * One Time Programmable (OTP) can be individually set for each code flash block.
 * When the OTP setting is made for a block, programming by serial programming and
 * by self programming is prohibited. Once set, the OTP setting cannot be released!
 *
 * The code flash memory is divided into 8*8kB and further n*32kB blocks:
 *
 *             |      Bank A      |      Bank B      |
 * --------------------------------------------------
 * D1  (512kB) |  block 0 .. 21   |
 * D2    (1MB) |  block 0 .. 37   |
 * D3    (2MB) |  block 0 .. 69   |
 * D4    (4MB) |  block 0 .. 69   |  block 0 .. 63
 * D5    (8MB) |  block 0 .. 133  |  block 0 .. 127
 * D5ED (10MB) |  block 0 .. 197  |  block 0 .. 127
 *
 *
 * Default OTP bit setting is '1'
 *  - '1' means corresponding code flash block is programmable
 *  - '0' means corresponding code flash block is not reprogrammable
 *
 * Once the state of OTP bit is changed from '1' to '0' it is not possible
 * to change the state of that OTP bit anymore.
 *
 *
 * Flash Access Library (FAL) commands:
 *
 *  - R_FAL_CMD_CODEF_GET_OTP     Get the OTP bit of a certain block of Code Flash
 *  - R_FAL_CMD_CODEF_SET_OTP     Set the OTP bit of a certain block of Code Flash
*/
tOTP_LOCKBITS RBSYS_FlashConfigArea_OTP =
{
  {
    /* Flash Bank A */
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks  0 .. 7  */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks  8 .. 15 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 16 .. 23 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 24 .. 31 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 32 .. 39 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 40 .. 47 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 48 .. 55 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 56 .. 63 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 64 .. 71 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 72 .. 79 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 80 .. 87 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 88 .. 95 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks  96 .. 103 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 104 .. 111 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 112 .. 119 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 120 .. 127 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 128 .. 135 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 136 .. 143 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 144 .. 151 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 152 .. 159 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 160 .. 167 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 168 .. 175 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 176 .. 183 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 184 .. 191 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 192 .. 199 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 200 .. 207 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 208 .. 215 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 216 .. 223 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 224 .. 231 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 232 .. 239 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 240 .. 247 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 248 .. 255 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 256 .. 263 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 264 .. 271 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 272 .. 279 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 280 .. 287 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 288 .. 295 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 296 .. 303 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 304 .. 311 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 312 .. 319 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 320 .. 327 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 328 .. 335 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 336 .. 343 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 344 .. 351 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 352 .. 359 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 360 .. 367 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 368 .. 375 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 376 .. 383 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 384 .. 391 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 392 .. 399 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 400 .. 407 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 408 .. 415 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 416 .. 423 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 424 .. 431 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 432 .. 439 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 440 .. 447 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 448 .. 455 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 456 .. 463 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 464 .. 471 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 472 .. 479 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 480 .. 487 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 488 .. 495 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 496 .. 503 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 504 .. 511 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 512 .. 519 */

      /* Flash Bank B */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks  0 .. 7  */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks  8 .. 15 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 16 .. 23 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 24 .. 31 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 32 .. 39 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 40 .. 47 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 48 .. 55 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 56 .. 63 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 64 .. 71 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 72 .. 79 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 80 .. 87 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks  88 .. 95 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks  96 .. 103 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 104 .. 111 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 112 .. 119 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 120 .. 127 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 128 .. 135 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 136 .. 143 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 144 .. 151 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 152 .. 159 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 160 .. 167 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 168 .. 175 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 176 .. 183 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 184 .. 191 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 192 .. 199 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 200 .. 207 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 208 .. 215 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 216 .. 223 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 224 .. 231 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 232 .. 239 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 240 .. 247 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 248 .. 255 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 256 .. 263 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 264 .. 271 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 272 .. 279 */
    }
  }
};

RBSECTION_END_HCU_OTP




RBSECTION_START_HCU_LOCKBITS
/**
 * @brief Definition of the lock bits
 *
 * Code flash write protection for non-secure areas consists of sector based lock
 * bit and section password authentication. The lock bit can be individually
 * set for each Code Flash block. When the lock bit protection mechanism is enabled,
 * programming and erasure is prohibited on Code Flash blocks for which the lock bit
 * is set. Programming or erasure can be executed even though lock bit set, when the
 * lock bit protection mechanism is disabled. Please refer to R_FAL_Enable_Lockbit
 * and R_FAL_Disable_Lockbit. When a Code Flash block is erased, the lock bit for
 * that block is also erased.
 *
 * The code flash memory is divided into 8*8kB and further n*32kB blocks:
 *
 *             |      Bank A      |      Bank B      |
 * --------------------------------------------------
 * D1  (512kB) |  block 0 .. 21   |
 * D2    (1MB) |  block 0 .. 37   |
 * D3    (2MB) |  block 0 .. 69   |
 * D4    (4MB) |  block 0 .. 69   |  block 0 .. 63
 * D5    (8MB) |  block 0 .. 133  |  block 0 .. 127
 * D5ED (10MB) |  block 0 .. 197  |  block 0 .. 127
 *
 *
 * Flash Access Library (FAL) commands:
 *
 *  - R_FAL_CMD_CODEF_GET_LOCKBIT     Get the lock bit of a certain block of Code Flash
 *  - R_FAL_CMD_CODEF_SET_LOCKBIT     Set the lock bit of a certain block of Code Flash
 */
tOTP_LOCKBITS RBSYS_FlashConfigArea_LOCKBITS =
{
  {
    /* Flash Bank A */
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks  0 .. 7  */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks  8 .. 15 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 16 .. 23 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 24 .. 31 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 32 .. 39 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 40 .. 47 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 48 .. 55 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 56 .. 63 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 64 .. 71 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 72 .. 79 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 80 .. 87 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 88 .. 95 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks  96 .. 103 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 104 .. 111 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 112 .. 119 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 120 .. 127 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 128 .. 135 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 136 .. 143 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 144 .. 151 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 152 .. 159 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 160 .. 167 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 168 .. 175 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 176 .. 183 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 184 .. 191 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 192 .. 199 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 200 .. 207 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 208 .. 215 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 216 .. 223 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 224 .. 231 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 232 .. 239 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 240 .. 247 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 248 .. 255 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 256 .. 263 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 264 .. 271 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 272 .. 279 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 280 .. 287 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 288 .. 295 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 296 .. 303 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 304 .. 311 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 312 .. 319 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 320 .. 327 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 328 .. 335 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 336 .. 343 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 344 .. 351 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 352 .. 359 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 360 .. 367 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 368 .. 375 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 376 .. 383 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 384 .. 391 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 392 .. 399 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 400 .. 407 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 408 .. 415 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 416 .. 423 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 424 .. 431 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 432 .. 439 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 440 .. 447 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 448 .. 455 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 456 .. 463 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 464 .. 471 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 472 .. 479 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 480 .. 487 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 488 .. 495 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 496 .. 503 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF1 Blocks 504 .. 511 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF1 Blocks 512 .. 519 */

      /* Flash Bank B */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks  0 .. 7  */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks  8 .. 15 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 16 .. 23 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 24 .. 31 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 32 .. 39 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 40 .. 47 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 48 .. 55 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 56 .. 63 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 64 .. 71 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 72 .. 79 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 80 .. 87 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks  88 .. 95 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks  96 .. 103 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 104 .. 111 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 112 .. 119 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 120 .. 127 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 128 .. 135 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 136 .. 143 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 144 .. 151 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 152 .. 159 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 160 .. 167 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 168 .. 175 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 176 .. 183 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 184 .. 191 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 192 .. 199 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 200 .. 207 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 208 .. 215 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 216 .. 223 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 224 .. 231 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 232 .. 239 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 240 .. 247 */
    },
    {
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 248 .. 255 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 256 .. 263 */
      1, 1, 1, 1, 1, 1, 1, 1,     /* CF2 Blocks 264 .. 271 */
      1, 1, 1, 1, 1, 1, 1, 1      /* CF2 Blocks 272 .. 279 */
    }
  }
};

RBSECTION_END_HCU_LOCKBITS



/******************************************************************************************/
/*                                Sanity Check                                            */
/******************************************************************************************/


  #if ( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) \
        && (RBFS_CpuClock != RBFS_CpuClock_80MHz) \
        )

    #error ("CC CUBE device D1 is only supported with 80MHz")
  #endif


  #if ( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2) \
        && (RBFS_CpuClock != RBFS_CpuClock_80MHz) \
        )

    #error ("CC CUBE device D2 is only supported with 80MHz")
  #endif


  #if ( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) \
     && ( (RBFS_CpuClock != RBFS_CpuClock_160MHz) && (RBFS_CpuClock != RBFS_CpuClock_240MHz) ) \
      )

    #error ("CC CUBE device D3 is only supported with 160MHz or 240MHz")
  #endif


  #if ( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4) \
        && (RBFS_CpuClock != RBFS_CpuClock_240MHz) \
        )

    #error ("CC CUBE device D4 is only supported with 240MHz")
  #endif


  #if ( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5) \
        && (RBFS_CpuClock != RBFS_CpuClock_240MHz) \
        )

    #error ("CC CUBE device D5 is only supported with 240MHz")
  #endif


#endif

/** @} */
/* End ingroup RBSYS */
