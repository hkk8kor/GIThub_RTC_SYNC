/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Initialization of structures for HCUHEX file generation
 *
 * Standard hexfile contains only the program code, the additional device configuration
 * for Renesas CC CUBE+ (security settings, option bytes, OTP settings, ...) must be
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

#include "RBSYS_Config.h"

/* used interfaces */
#include "RBLCF_MemoryRemap.h"
#include "RBLCF_Hexblocks_Layout.h"
#include "RBSYS_uCRegisters.h"


/* realized interfaces */
#include "RBSYS_OPBT_U2a.h" //< for RBSECTION_
#include "RBSYS_OPBT_U2a_SanityCheck.h" //< for RBLCF_HSM_CFLASH_
#include "RBSYS_FlashConfigArea.h"

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasU2A);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TargetDevice,
                          RBFS_TargetDevice_RenesasD7,
                          RBFS_TargetDevice_RenesasM2,
                          RBFS_TargetDevice_RenesasM3,
                          RBFS_TargetDevice_RenesasM6);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HardwareSecurityModule,
                          RBFS_HardwareSecurityModule_Supported,
                          RBFS_HardwareSecurityModule_Unsupported);

RB_ASSERT_SWITCH_SETTINGS(RBFS_CodeFlashMemoryMode,
                          RBFS_CodeFlashMemoryMode_SingleMap,
                          RBFS_CodeFlashMemoryMode_DoubleMap);


#if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)



/* Functions to provide the expected (configured in software and expected value for this application)
 * and the actual (configured in HW) value of certain parts of the flash config area.
 **/

/** CAUTION: RBSYS_OPBT_Addresses, RBSYS_OPBT_ExpectedValues and RBSYS_OPBT must match up! */
static const volatile uint32* const RBSYS_OPBT_Addresses[RBSYS_FlashConfigAreaSetting_MaxNumberOfSettings] =
{
  (volatile uint32*)(RBSYS_CSAf_base + 0x380u),    // RESET_VECTOR_PE0
  (volatile uint32*)(RBSYS_CSAf_base + 0x384u),    // RESET_VECTOR_PE1
  (volatile uint32*)(RBSYS_CSAf_base + 0x388u),    // RESET_VECTOR_PE2
  (volatile uint32*)(RBSYS_CSAf_base + 0x38Cu),    // RESET_VECTOR_PE3
  (volatile uint32*)(RBSYS_CSAf_base + 0x3A0u),    // OPBT0
  (volatile uint32*)(RBSYS_CSAf_base + 0x3A4u),    // OPBT1
  (volatile uint32*)(RBSYS_CSAf_base + 0x3A8u),    // OPBT2
  (volatile uint32*)(RBSYS_CSAf_base + 0x3ACu),    // OPBT3
  (volatile uint32*)(RBSYS_CSAf_base + 0x3B0u),    // OPBT4
  (volatile uint32*)(RBSYS_CSAf_base + 0x3B8u),    // OPBT6
  (volatile uint32*)(RBSYS_CSAf_base + 0x3BCu),    // OPBT7
  (volatile uint32*)(RBSYS_CSAf_base + 0x3C0u),    // OPBT8
  (volatile uint32*)(RBSYS_CSAf_base + 0x3C4u),    // OPBT9
  (volatile uint32*)(RBSYS_CSAf_base + 0x3C8u),    // OPBT10
  (volatile uint32*)(RBSYS_CSAf_base + 0x3CCu),    // OPBT11
  (volatile uint32*)(RBSYS_CSAf_base + 0x3D0u),    // OPBT12
  (volatile uint32*)(RBSYS_CSAf_base + 0x3D4u),    // OPBT13
  (volatile uint32*)(RBSYS_CSAf_base + 0x3D8u),    // OPBT14
  (volatile uint32*)(RBSYS_CSAf_base + 0x3E0u),    // OPBT16
  (volatile uint32*)(RBSYS_CSAf_base + 0x3E4u),    // OPBT17
  (volatile uint32*)(RBSYS_CSAf_base + 0x3E8u),    // OPBT18
  (volatile uint32*)(RBSYS_CSAf_base + 0x3ECu),    // OPBT19
  (volatile uint32*)(RBSYS_CSAf_base + 0x3F0u),    // OPBT20
  (volatile uint32*)(RBSYS_CSAf_base + 0x3F4u),    // OPBT21
  (volatile uint32*)(RBSYS_CSAf_base + 0x3F8u),    // OPBT22
  (volatile uint32*)(RBSYS_CSAf_base + 0x3FCu),    // OPBT23
};

/* Current and past values of option bytes, past values are needed for safety critical option bytes checked via RBROMSafety Option Bytes Check */
static const RBSYS_FlashConfigArea_ExpectedValues_t RBSYS_OPBT_ExpectedValues[] =
{
    {RBSYS_FlashConfigAreaSetting_ResetVectorPE0, RESET_VECTOR_PE0},
    {RBSYS_FlashConfigAreaSetting_ResetVectorPE1, RESET_VECTOR_PE1},
    {RBSYS_FlashConfigAreaSetting_ResetVectorPE2, RESET_VECTOR_PE2},
    {RBSYS_FlashConfigAreaSetting_ResetVectorPE3, RESET_VECTOR_PE3},
    {RBSYS_FlashConfigAreaSetting_OPBT0,          OPBT0},
    {RBSYS_FlashConfigAreaSetting_OPBT1,          OPBT1},
    {RBSYS_FlashConfigAreaSetting_OPBT2,          OPBT2},
    {RBSYS_FlashConfigAreaSetting_OPBT3,          OPBT3},
    {RBSYS_FlashConfigAreaSetting_OPBT4,          OPBT4},
    {RBSYS_FlashConfigAreaSetting_OPBT6,          OPBT6},
    {RBSYS_FlashConfigAreaSetting_OPBT7,          OPBT7},
    {RBSYS_FlashConfigAreaSetting_OPBT8,          OPBT8},
    {RBSYS_FlashConfigAreaSetting_OPBT9,          OPBT9},
    {RBSYS_FlashConfigAreaSetting_OPBT10,         OPBT10},
    {RBSYS_FlashConfigAreaSetting_OPBT10,         0xF88B588Eu},
    {RBSYS_FlashConfigAreaSetting_OPBT11,         OPBT11},
    {RBSYS_FlashConfigAreaSetting_OPBT12,         OPBT12},
    {RBSYS_FlashConfigAreaSetting_OPBT13,         OPBT13},
    {RBSYS_FlashConfigAreaSetting_OPBT14,         OPBT14},
    {RBSYS_FlashConfigAreaSetting_OPBT16,         OPBT16},
    {RBSYS_FlashConfigAreaSetting_OPBT17,         OPBT17},
    {RBSYS_FlashConfigAreaSetting_OPBT18,         OPBT18},
    {RBSYS_FlashConfigAreaSetting_OPBT19,         OPBT19},
    {RBSYS_FlashConfigAreaSetting_OPBT20,         OPBT20},
    {RBSYS_FlashConfigAreaSetting_OPBT21,         OPBT21},
    {RBSYS_FlashConfigAreaSetting_OPBT22,         OPBT22},
    {RBSYS_FlashConfigAreaSetting_OPBT23,         OPBT23},
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


RBSECTION_START_CSA_OTP
tCsaOtpSettingArea RBSYS_FlashConfigArea_csaOtpSetting = {
    {
      0xFFFFFFFFu, // H'FF321200 State At Shipping
      0xFFFFFFFFu, // H'FF321204 State At Shipping
      0xFFFFFFFFu  // H'FF321208 State At Shipping
    },
    {
      RESERVED_32BIT,
      RESERVED_32BIT,
      RESERVED_32BIT,
      RESERVED_32BIT,
      RESERVED_32BIT
    }
};
RBSECTION_END_CSA_OTP

RBSECTION_START_CSA_CONFIG
tConfigData RBSYS_FlashConfigArea_opbt = {
                 0,          // H'FF321300 SW Config Opt Byte 0
                 0,          // H'FF321304 SW Config Opt Byte 1
                 0,          // H'FF321308 SW Config Opt Byte 2
                 0,          // H'FF32130C SW Config Opt Byte 3
                 0,          // H'FF321310 SW Config Opt Byte 4
                 0,          // H'FF321314 SW Config Opt Byte 5
                 0,          // H'FF321318 SW Config Opt Byte 6
                 0,          // H'FF32131C SW Config Opt Byte 7
                 0,          // H'FF321320 SW Config Opt Byte 8
                 0,          // H'FF321324 SW Config Opt Byte 9
                 0,          // H'FF321328 SW Config Opt Byte 10
                 0,          // H'FF32132C SW Config Opt Byte 11
                 0,          // H'FF321330 SW Config Opt Byte 12
                 0,          // H'FF321334 SW Config Opt Byte 13
                 0,          // H'FF321338 SW Config Opt Byte 14
                 0,          // H'FF32133C SW Config Opt Byte 15
                 0,          // H'FF321340 SW Config Opt Byte 16
                 0,          // H'FF321344 SW Config Opt Byte 17
                 0,          // H'FF321348 SW Config Opt Byte 18
                 0,          // H'FF32134C SW Config Opt Byte 19
                 0,          // H'FF321350 SW Config Opt Byte 20
                 0,          // H'FF321354 SW Config Opt Byte 21
                 0,          // H'FF321358 SW Config Opt Byte 22
                 0,          // H'FF32135C SW Config Opt Byte 23
                 0,          // H'FF321360 SW Config Opt Byte 24
                 0,          // H'FF321364 SW Config Opt Byte 25
                 0,          // H'FF321368 SW Config Opt Byte 26
                 0,          // H'FF32136C SW Config Opt Byte 27
                 0,          // H'FF321370 SW Config Opt Byte 28
                 0,          // H'FF321374 SW Config Opt Byte 29
                 0,          // H'FF321378 SW Config Opt Byte 30
                 0,          // H'FF32137C SW Config Opt Byte 31
    RESET_VECTOR_PE0,        // H'FF321380 Reset Vector (PE0)
    RESET_VECTOR_PE1,        // H'FF321384 Reset Vector (PE1)
    RESET_VECTOR_PE2,        // H'FF321388 Reset Vector (PE2) <<- Core 2 does not exist for M3, nevertheless any value can be written
    RESET_VECTOR_PE3,        // H'FF32138C Reset Vector (PE3) <<- Core 3 does not exist for M3, nevertheless any value can be written
    RESERVED_32BIT,          // H'FF321390 Reserved
    RESERVED_32BIT,          // H'FF321394 Reserved
    RESERVED_32BIT,          // H'FF321398 Reserved
    RESERVED_32BIT,          // H'FF32139C Reserved
    OPBT0,                   // H'FF3213A0 OPBT0
    OPBT1,                   // H'FF3213A4 OPBT1
    OPBT2,                   // H'FF3213A8 OPBT2
    OPBT3,                   // H'FF3213AC OPBT3
    OPBT4,                   // H'FF3213B0 OPBT4
    OPBT5,                   // H'FF3213B4 Reserved
    OPBT6,                   // H'FF3213B8 OPBT6
    OPBT7,                   // H'FF3213BC OPBT7
    OPBT8,                   // H'FF3213C0 OPBT8
    OPBT9,                   // H'FF3213C4 OPBT9
    OPBT10,                  // H'FF3213C8 OPBT10
    OPBT11,                  // H'FF3213CC OPBT11
    OPBT12,                  // H'FF3213D0 OPBT12
    OPBT13,                  // H'FF3213D4 OPBT13
    OPBT14,                  // H'FF3213D8 OPBT14
    OPBT15,                  // H'FF3213DC Reserved
    OPBT16,                  // H'FF3213E0 OPBT16
    OPBT17,                  // H'FF3213E4 OPBT17
    OPBT18,                  // H'FF3213E8 OPBT18
    OPBT19,                  // H'FF3213EC OPBT19
    OPBT20,                  // H'FF3213F0 OPBT20
    OPBT21,                  // H'FF3213F4 OPBT21
    OPBT22,                  // H'FF3213F8 OPBT22
    OPBT23,                  // H'FF3213FC OPBT23
    RESERVED_32BIT,          // H'FF321400 Reserved
    RESERVED_32BIT,          // H'FF321404 Reserved
    RESERVED_32BIT,          // H'FF321408 Reserved
    RESERVED_32BIT,          // H'FF32140C Reserved
    RESERVED_32BIT,          // H'FF321410 Reserved
    RESERVED_32BIT,          // H'FF321414 Reserved
    RESERVED_32BIT,          // H'FF321418 Reserved
    RESERVED_32BIT,          // H'FF32141C Reserved
    RESERVED_32BIT,          // H'FF321420 Reserved
    RESERVED_32BIT,          // H'FF321424 Reserved
    RESERVED_32BIT,          // H'FF321428 Reserved
    RESERVED_32BIT,          // H'FF32142C Reserved
    RESERVED_32BIT,          // H'FF321430 Reserved
    RESERVED_32BIT,          // H'FF321434 Reserved
    RESERVED_32BIT,          // H'FF321438 Reserved
    RESERVED_32BIT,          // H'FF32143C Reserved
    RESERVED_32BIT,          // H'FF321440 Reserved
    RESERVED_32BIT,          // H'FF321444 Reserved
    RESERVED_32BIT,          // H'FF321448 Reserved
    RESERVED_32BIT,          // H'FF32144C Reserved
    RESERVED_32BIT,          // H'FF321450 Reserved
    RESERVED_32BIT,          // H'FF321454 Reserved
    RESERVED_32BIT,          // H'FF321458 Reserved
    RESERVED_32BIT,          // H'FF32145C Reserved
    RESERVED_32BIT,          // H'FF321460 Reserved
    RESERVED_32BIT,          // H'FF321464 Reserved
    RESERVED_32BIT,          // H'FF321468 Reserved
    RESERVED_32BIT,          // H'FF32146C Reserved
    RESERVED_32BIT,          // H'FF321470 Reserved
    RESERVED_32BIT,          // H'FF321474 Reserved
    RESERVED_32BIT,          // H'FF321478 Reserved
    RESERVED_32BIT,          // H'FF32147C Reserved
};
RBSECTION_END_CSA_CONFIG

RBSECTION_START_SSA_OTP
tssaOtpConfig RBSYS_FlashConfigArea_ssaOtpConfig = {
    {
      0xFFFFFFFFu, // H'FF322200 State At Shipping
      0xFFFFFFFFu, // H'FF322204 State At Shipping
      0xFFFFFFFFu  // H'FF322208 State At Shipping
    },
    {RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT},
    0xFFFFFFFFu,   // H'FF322220 State At Shipping
    {RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT}
};
RBSECTION_END_SSA_OTP

#define SSA_IDS_DEFAULT {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu}

RBSECTION_START_SSA_CONFIG1
tssaConfig1 RBSYS_FlashConfigArea_ssaConfig1 = {
    {RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT},

    0xFFFFFFFFu, // H'FF322300   S_OPBT0 (OCD ID related OPBT)
    RESERVED_32BIT,
    RESERVED_32BIT,
    0xFFFFFFFFu, // H'FF32230C   S_OPBT3 (Customer ID related OPBT)
    0xFFFFFFFFu, // H'FF322310   S_OPBT4 (DataFlash ID related OPBT)
    0xFFFFFFFFu, // H'FF322314   S_OPBT5 (Serial Programmer ID related OPBT)

    0xFFFEFFFFu, // H'FF322318   S_OPBT6 (RHSIF ID OPBT) - M2: Program 0xFFFEFFFF as RHSIF is not implemented
    0xFDFFFFFFu, // H'FF32231C   S_OPBT7 (Debug and Calib OPBT)

    SSA_IDS_DEFAULT, // H'FF322320   OCD ID
    SSA_IDS_DEFAULT, // H'FF322340   Serial Programmer ID
    SSA_IDS_DEFAULT, // H'FF322360   Customer ID A
    SSA_IDS_DEFAULT, // H'FF322380   Data Flash ID

    {RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT},

    SSA_IDS_DEFAULT, // H'FF3223C0   RHSIF ID - M2: Program 0xFFFFFFFF as RHSIF is not implemented
    SSA_IDS_DEFAULT, // H'FF3223E0   Customer ID B
    SSA_IDS_DEFAULT, // H'FF322400   Customer ID C

    /* H'FF322420 - H'FF32245C */
    {RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT,
     RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT}
};
RBSECTION_END_SSA_CONFIG1

RBSECTION_START_SSA_CONFIG2
tssaConfig2 RBSYS_FlashConfigArea_ssaConfig2 = {
    #if( RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Supported )
      0x0FFFFFFFu                                         /*ICUM_OPBT0*/, //< ICUM ON and Protection Upgrades
      (RBLCF_HSM_CFLASH_START + RBSYS_HSM_INTVECS_OFFSET) /*ICUM_OPBT1*/, //< ICUM Reset Vector (HSM Bootloader)
      RBLCF_HSM_CFLASH_START                              /*ICUM_OPBT2*/, //< Secure Code Flash Region Start Address
      #if( RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2 )
        0xFF240000u                                         /*ICUM_OPBT3*/, //< Secure Data Flash Region Start Address for M2
      #elif( RBFS_TargetDevice == RBFS_TargetDevice_RenesasM3 )
        0xFF240000u                                         /*ICUM_OPBT3*/, //< Secure Data Flash Region Start Address for M3
      #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) )
        0xFF280000u                                         /*ICUM_OPBT3*/, //< Secure Data Flash Region Start Address for M6 / M6ED
      #endif
      0xFFFFFFCEu                                         /*ICUM_OPBT4*/,  //< VAC, Watchdog configuration for ICUM
    #else
      RESERVED_32BIT,
      RESERVED_32BIT,
      RESERVED_32BIT,
      RESERVED_32BIT,
      0xFFFF7FEFu, /* reserved, but not 0xFFFFFFFF */
    #endif
    {RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT}
};
RBSECTION_END_SSA_CONFIG2

#define BPA_OTP_DEFAULTS {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu}

RBSECTION_START_BPA0_OTP
tbpa0OtpSettings RBSYS_FlashConfigArea_bpa0OtpConfig = {
    /* OTP Setting of User Area 0 Start */
    BPA_OTP_DEFAULTS,
    /* OTP Setting of User Area 0 End */

    /* OTP Setting of User Area 1 Start */
    BPA_OTP_DEFAULTS, //< DoubleMapMode: Shared with UserArea0 OTP Settings, program as Reserved
    /* OTP Setting of User Area 1 End */

    {RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT}
};
RBSECTION_END_BPA0_OTP

RBSECTION_START_BPA0_CONFIG1
tbpa0Config1 RBSYS_FlashConfigArea_bpaConfig1 = {
    /* OTP Setting of Extended Data Area Start */
    BPA_OTP_DEFAULTS,
    /* OTP Setting of Extended Data Area End */

    // Customer ID Protection and Erase Counter Setting for User Area 0 and User Boot Area 0
    // Bank 0: Shall be protected by Customer ID B + Erase Counter enabled
    #if( RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2 ) // M2: 54 Blocks
      {0x99999999u, 0x99999999u, 0x99999999u, 0x99999999u, 0x99999999u, 0x99999999u, 0xFF999999u, 0xFFFFFFFFu,
       0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu },
    #else // M3 + M6 + M6ED: 70 Blocks
      {0x99999999u, 0x99999999u, 0x99999999u, 0x99999999u, 0x99999999u, 0x99999999u, 0x99999999u, 0x99999999u,
       0xFF999999u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu },
    #endif

    // Customer ID Protection and Erase Counter Setting for User Area 1 and User Boot Area 1
    // Bank 1: Shall be protected by Customer ID C + Erase Counter enabled
    #if( RBFS_CodeFlashMemoryMode == RBFS_CodeFlashMemoryMode_SingleMap )

      #if( RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2 ) // M2: 54 Blocks
        {0x88888888u, 0x88888888u, 0x88888888u, 0x88888888u, 0x88888888u, 0x88888888u, 0xFF888888u, 0xFFFFFFFFu,
         0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu },
      #else // M3 + M6 + M6ED: 70 Blocks
        {0x88888888u, 0x88888888u, 0x88888888u, 0x88888888u, 0x88888888u, 0x88888888u, 0x88888888u, 0x88888888u,
         0xFF888888u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu },
      #endif

    #else // DoubleMap (Setting shared with User Area 0)
      {RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT,
       RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT },
    #endif

   {RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT}
};
RBSECTION_END_BPA0_CONFIG1

RBSECTION_START_BPA0_CONFIG2
tbpa0Config2 RBSYS_FlashConfigArea_bpa0Config2 = {
    /* Customer ID Protection Settings for Extended Data Area Start */
    {0xFFFFFFFFu,
    0xFFFFFFFFu,
    0xFFFFFFFFu,
    0xFFFFFFFFu,
    0xFFFFFFFFu,
    0xFFFFFFFFu,
    0xFFFFFFFFu,
    0xFFFFFFFFu}
    /* Customer ID Protection Settings for Extended Data Area End */
};
RBSECTION_END_BPA0_CONFIG2

#if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6))
RBSECTION_START_BPA1_OTP
tbpa1OtpSettings RBSYS_FlashConfigArea_bpa1OtpConfig = {
    /* OTP Setting of User Area 2 Start */
    BPA_OTP_DEFAULTS,
    /* OTP Setting of User Area 2 End */

    /* OTP Setting of User Area 3 Start */
    BPA_OTP_DEFAULTS, //< DoubleMapMode: Shared with UserArea2 OTP Settings, program as Reserved
    /* OTP Setting of User Area 3 End */


   {RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT}
};
RBSECTION_END_BPA1_OTP

RBSECTION_START_BPA1_CONFIG
tbpa1Config RBSYS_FlashConfigArea_bpa1Config = {
    /* Customer ID Protection and Erase Counter Settings for User Area 2 Start */
    // Bank 2: Shall be protected by Customer ID B + Erase Counter enabled
    {0x99999999u, 0x99999999u, 0x99999999u, 0x99999999u, 0x99999999u, 0x99999999u, 0x99999999u, 0x99999999u,
     0xFF999999u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu },
    /* Customer ID Protection and Erase Counter Settings for User Area 2 End */

    /* Customer ID Protection and Erase Counter Settings for User Area 3 Start */
    // Bank 3: Shall be protected by Customer ID C + Erase Counter enabled
    #if( RBFS_CodeFlashMemoryMode == RBFS_CodeFlashMemoryMode_SingleMap )
      {0x88888888u, 0x88888888u, 0x88888888u, 0x88888888u, 0x88888888u, 0x88888888u, 0x88888888u, 0x88888888u,
       0xFF888888u, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu },
    #else // DoubleMap (Setting shared with User Area 2)
      {RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT,
       RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT, RESERVED_32BIT },
    #endif
    /* Customer ID Protection and Erase Counter Settings for User Area 3 End */

   {RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,
    RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT,RESERVED_32BIT}
};
RBSECTION_END_BPA1_CONFIG
#endif


#endif
