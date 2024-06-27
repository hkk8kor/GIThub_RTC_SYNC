#ifndef RBSYS_OPBT_U2A_H__
#define RBSYS_OPBT_U2A_H__

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

#include "RBSYS_Config.h"

/* used interfaces */
#include "RBSYS_OPBT_U2C_config.h"

RB_ASSERT_SWITCH_SETTINGS(RBFS_RBSYSuCSupplyVoltageRegulator,
                          RBFS_RBSYSuCSupplyVoltageRegulator_Enabled,
                          RBFS_RBSYSuCSupplyVoltageRegulator_Disabled);


/** Attention: If HSM is active, none of the PEs will boot without triggering it from HSM via BOOTCTRL  */


#define RBSYS_SANITYCHECK_SIZE(struct2check, startAddr, endAddr) \
    static_assert(sizeof(struct2check) == ((endAddr) - (startAddr)), "Size of struct is invalid")

#define RBSYS_SANITYCHECK_OFFSET(struct, member, expected_offset) \
    static_assert((uint32)offsetof(struct, member) == (uint32)(expected_offset), "Address is invalid")

typedef const struct
{
  uint32 otpConfigSetting[3];
  uint32 res[5];
}tCsaOtpSettingArea;

RBSYS_SANITYCHECK_SIZE(tCsaOtpSettingArea, 0x200, 0x220);
RBSYS_SANITYCHECK_OFFSET(tCsaOtpSettingArea, otpConfigSetting, 0u);

typedef const struct {
  uint32 SwCfgOptByte0; /* H'FF321300 SW Config Opt Byte 0              */
  uint32 SwCfgOptByte1; /* H'FF321304 SW Config Opt Byte 1              */
  uint32 SwCfgOptByte2; /* H'FF321308 SW Config Opt Byte 2              */
  uint32 SwCfgOptByte3; /* H'FF32130C SW Config Opt Byte 3              */
  uint32 SwCfgOptByte4; /* H'FF321310 SW Config Opt Byte 4              */
  uint32 SwCfgOptByte5; /* H'FF321314 SW Config Opt Byte 5              */
  uint32 SwCfgOptByte6; /* H'FF321318 SW Config Opt Byte 6              */
  uint32 SwCfgOptByte7; /* H'FF32131C SW Config Opt Byte 7              */
  uint32 SwCfgOptByte8; /* H'FF321320 SW Config Opt Byte 8              */
  uint32 SwCfgOptByte9; /* H'FF321324 SW Config Opt Byte 9              */
  uint32 SwCfgOptByte10;/* H'FF321328 SW Config Opt Byte 10             */
  uint32 SwCfgOptByte11;/* H'FF32132C SW Config Opt Byte 11             */
  uint32 SwCfgOptByte12;/* H'FF321330 SW Config Opt Byte 12             */
  uint32 SwCfgOptByte13;/* H'FF321334 SW Config Opt Byte 13             */
  uint32 SwCfgOptByte14;/* H'FF321338 SW Config Opt Byte 14             */
  uint32 SwCfgOptByte15;/* H'FF32133C SW Config Opt Byte 15             */
  uint32 SwCfgOptByte16;/* H'FF321340 SW Config Opt Byte 16             */
  uint32 SwCfgOptByte17;/* H'FF321344 SW Config Opt Byte 17             */
  uint32 SwCfgOptByte18;/* H'FF321348 SW Config Opt Byte 18             */
  uint32 SwCfgOptByte19;/* H'FF32134C SW Config Opt Byte 19             */
  uint32 SwCfgOptByte20;/* H'FF321350 SW Config Opt Byte 20             */
  uint32 SwCfgOptByte21;/* H'FF321354 SW Config Opt Byte 21             */
  uint32 SwCfgOptByte22;/* H'FF321358 SW Config Opt Byte 22             */
  uint32 SwCfgOptByte23;/* H'FF32135C SW Config Opt Byte 23             */
  uint32 SwCfgOptByte24;/* H'FF321360 SW Config Opt Byte 24             */
  uint32 SwCfgOptByte25;/* H'FF321364 SW Config Opt Byte 25             */
  uint32 SwCfgOptByte26;/* H'FF321368 SW Config Opt Byte 26             */
  uint32 SwCfgOptByte27;/* H'FF32136C SW Config Opt Byte 27             */
  uint32 SwCfgOptByte28;/* H'FF321370 SW Config Opt Byte 28             */
  uint32 SwCfgOptByte29;/* H'FF321374 SW Config Opt Byte 29             */
  uint32 SwCfgOptByte30;/* H'FF321378 SW Config Opt Byte 30             */
  uint32 SwCfgOptByte31;/* H'FF32137C SW Config Opt Byte 31             */
  uint32 resV_PE0;      /* H'FF321380 Reset Vector (PE0)                */
  uint32 resV_PE1;      /* H'FF321384 Reset Vector (PE1)                */
  uint32 resV_PE2;      /* H'FF321388 Reset Vector (PE2)                */
  uint32 resV_PE3;      /* H'FF32138C Reset Vector (PE3)                */
  uint32 reserved_0;    /* H'FF321390 Reserved                          */
  uint32 reservde_1;    /* H'FF321394 Reserved                          */
  uint32 reservde_2;    /* H'FF321398 Reserved                          */
  uint32 reservde_3;    /* H'FF32139C Reserved                          */
  uint32 OptionByte0;   /* H'FF3213A0 OPBT0                             */
  uint32 OptionByte1;   /* H'FF3213A4 OPBT1                             */
  uint32 OptionByte2;   /* H'FF3213A8 OPBT2                             */
  uint32 OptionByte3;   /* H'FF3213AC OPBT3                             */
  uint32 OptionByte4;   /* H'FF3213B0 OPBT4                             */
  uint32 OptionByte5;   /* H'FF3213B4 Reserved                          */
  uint32 OptionByte6;   /* H'FF3213B8 OPBT6                             */
  uint32 OptionByte7;   /* H'FF3213BC OPBT7                             */
  uint32 OptionByte8;   /* H'FF3213C0 OPBT8                             */
  uint32 OptionByte9;   /* H'FF3213C4 OPBT9                             */
  uint32 OptionByte10;  /* H'FF3213C8 OPBT10                            */
  uint32 OptionByte11;  /* H'FF3213CC OPBT11                            */
  uint32 OptionByte12;  /* H'FF3213D0 OPBT12                            */
  uint32 OptionByte13;  /* H'FF3213D4 OPBT13                            */
  uint32 OptionByte14;  /* H'FF3213D8 OPBT14                            */
  uint32 OptionByte15;  /* H'FF3213DC Reserved                          */
  uint32 OptionByte16;  /* H'FF3213E0 OPBT16                            */
  uint32 OptionByte17;  /* H'FF3213E4 OPBT17                            */
  uint32 OptionByte18;  /* H'FF3213E8 OPBT18                            */
  uint32 OptionByte19;  /* H'FF3213EC OPBT19                            */
  uint32 OptionByte20;  /* H'FF3213F0 OPBT20, inverted values of OPBT16 */
  uint32 OptionByte21;  /* H'FF3213F4 OPBT21, inverted values of OPBT17 */
  uint32 OptionByte22;  /* H'FF3213F8 OPBT22, inverted values of OPBT18 */
  uint32 OptionByte23;  /* H'FF3213FC OPBT23, inverted values of OPBT19 */
  uint32 reservde_4;    /* H'FF321400 Reserved                          */
  uint32 reservde_5;    /* H'FF321404 Reserved                          */
  uint32 reservde_6;    /* H'FF321408 Reserved                          */
  uint32 reservde_7;    /* H'FF32140C Reserved                          */
  uint32 reservde_8;    /* H'FF321410 Reserved                          */
  uint32 reservde_9;    /* H'FF321414 Reserved                          */
  uint32 reservde_10;   /* H'FF321418 Reserved                          */
  uint32 reservde_11;   /* H'FF32141C Reserved                          */
  uint32 reservde_12;   /* H'FF321420 Reserved                          */
  uint32 reservde_13;   /* H'FF321424 Reserved                          */
  uint32 reservde_14;   /* H'FF321428 Reserved                          */
  uint32 reservde_15;   /* H'FF32142C Reserved                          */
  uint32 reservde_16;   /* H'FF321430 Reserved                          */
  uint32 reservde_17;   /* H'FF321434 Reserved                          */
  uint32 reservde_18;   /* H'FF321438 Reserved                          */
  uint32 reservde_19;   /* H'FF32143C Reserved                          */
  uint32 reservde_20;   /* H'FF321440 Reserved                          */
  uint32 reservde_21;   /* H'FF321444 Reserved                          */
  uint32 reservde_22;   /* H'FF321448 Reserved                          */
  uint32 reservde_23;   /* H'FF32144C Reserved                          */
  uint32 reservde_24;   /* H'FF321450 Reserved                          */
  uint32 reservde_25;   /* H'FF321454 Reserved                          */
  uint32 reservde_26;   /* H'FF321458 Reserved                          */
  uint32 reservde_27;   /* H'FF32145C Reserved                          */
  uint32 reservde_28;   /* H'FF321460 Reserved                          */
  uint32 reservde_29;   /* H'FF321464 Reserved                          */
  uint32 reservde_30;   /* H'FF321468 Reserved                          */
  uint32 reservde_31;   /* H'FF32146C Reserved                          */
  uint32 reservde_32;   /* H'FF321470 Reserved                          */
  uint32 reservde_33;   /* H'FF321474 Reserved                          */
  uint32 reservde_34;   /* H'FF321478 Reserved                          */
  uint32 reservde_35;   /* H'FF32147C Reserved                          */
} tConfigData;
RBSYS_SANITYCHECK_SIZE(tConfigData, 0x300, 0x480);
RBSYS_SANITYCHECK_OFFSET(tConfigData, OptionByte0, 0xA0u);
RBSYS_SANITYCHECK_OFFSET(tConfigData, OptionByte23, 0xFCu);

typedef const struct
{
  uint32 ssaOtp[3];
  uint32 res[5];
  uint32 ssaOtp2;
  uint32 res1[7];
} tssaOtpConfig;
RBSYS_SANITYCHECK_SIZE(tssaOtpConfig, 0x200, 0x240);
RBSYS_SANITYCHECK_OFFSET(tssaOtpConfig, ssaOtp, 0);
RBSYS_SANITYCHECK_OFFSET(tssaOtpConfig, ssaOtp2, 0x20u);

typedef const struct
{
  uint32 res[8];
  uint32 S_OPBT0;
  uint32 res1;
  uint32 res2;
  uint32 S_OPBT3;
  uint32 S_OPBT4;
  uint32 S_OPBT5;
  uint32 S_OPBT6;
  uint32 S_OPBT7;
  uint32 OCD_ID[8];
  uint32 Serial_ID[8];
  uint32 Customer_ID_A[8];
  uint32 DataFlash_ID[8];
  uint32 res3[8];
  uint32 RHSIF_ID[8];
  uint32 Customer_ID_B[8];
  uint32 Customer_ID_C[8];
  uint32 res4[16];
}tssaConfig1;
RBSYS_SANITYCHECK_SIZE(tssaConfig1, 0x2E0, 0x460);
RBSYS_SANITYCHECK_OFFSET(tssaConfig1, S_OPBT0, 0x20);
RBSYS_SANITYCHECK_OFFSET(tssaConfig1, S_OPBT3, 0x2C);
RBSYS_SANITYCHECK_OFFSET(tssaConfig1, OCD_ID, 0x40);
RBSYS_SANITYCHECK_OFFSET(tssaConfig1, Customer_ID_B, 0x100);

typedef const struct
{
  uint32 ICUM_OPBT0;
  uint32 ICUM_OPBT1;
  uint32 ICUM_OPBT2;
  uint32 ICUM_OPBT3;
  uint32 ICUM_OPBT4;
  uint32 res2[3];
} tssaConfig2;
RBSYS_SANITYCHECK_SIZE(tssaConfig2, 0x700, 0x720);
RBSYS_SANITYCHECK_OFFSET(tssaConfig2, ICUM_OPBT2, 0x08);


typedef const struct
{
  uint32 OTPSettingUserArea0[8];
  uint32 OTPSettingUserArea1[8];
} tbpa0OtpSettings;
RBSYS_SANITYCHECK_SIZE(tbpa0OtpSettings, 0x200, 0x240);
RBSYS_SANITYCHECK_OFFSET(tbpa0OtpSettings, OTPSettingUserArea1, 0x20);


typedef const struct
{
  uint32 res[16];
} tbpa0Otp1Settings;
RBSYS_SANITYCHECK_SIZE(tbpa0Otp1Settings, 0x2C0, 0x300);

typedef const struct
{
  uint32 OTPSettingExtendedDataArea[8];
  uint32 CustomerIDProtAndEraseSettings_UserArea0[16];
  uint32 CustomerIDProtAndEraseSettings_UserArea1[16];
} tbpa0Config1;
RBSYS_SANITYCHECK_SIZE(tbpa0Config1, 0x3E0, 0x480);
RBSYS_SANITYCHECK_OFFSET(tbpa0Config1, CustomerIDProtAndEraseSettings_UserArea0, 0x20);
RBSYS_SANITYCHECK_OFFSET(tbpa0Config1, CustomerIDProtAndEraseSettings_UserArea1, 0x60);

typedef const struct
{
  uint32 res[32];
} tbpa0Config1a;
RBSYS_SANITYCHECK_SIZE(tbpa0Config1a, 0x580, 0x600);

typedef const struct
{
  uint32 CustomerIDProSettings_ExtDataArea[8];
} tbpa0Config2;
RBSYS_SANITYCHECK_SIZE(tbpa0Config2, 0x6E0, 0x700);

typedef const struct
{
  uint32 OTPSettingsUserArea2[8];
  uint32 OTPSettingsUserArea3[8];
  uint32 res[48];
} tbpa1OtpSettings;
RBSYS_SANITYCHECK_SIZE(tbpa1OtpSettings, 0x200, 0x300);
RBSYS_SANITYCHECK_OFFSET(tbpa1OtpSettings, OTPSettingsUserArea3, 0x20);

typedef const struct
{
  uint32 CustomerIDProtAndEraseSettings_UserArea2[16];
  uint32 CustomerIDProtAndEraseSettings_UserArea3[16];
  uint32 res[96];
} tbpa1Config;
RBSYS_SANITYCHECK_SIZE(tbpa1Config, 0x400, 0x600);
RBSYS_SANITYCHECK_OFFSET(tbpa1Config, CustomerIDProtAndEraseSettings_UserArea3, 0x40);




#define nRESERVED             0x0

#define RESERVED_1BIT         0x1u
#define RESERVED_2BIT         0x3u
#define RESERVED_3BIT         0x7u
#define RESERVED_4BIT         0xFu
#define RESERVED_5BIT         0x1Fu
#define RESERVED_6BIT         0x3Fu
#define RESERVED_7BIT         0x7Fu
#define RESERVED_8BIT         0xFFu
#define RESERVED_9BIT         0x1FFu
#define RESERVED_10BIT        0x3FFu
#define RESERVED_11BIT        0x7FFu
#define RESERVED_12BIT        0xFFFu
#define RESERVED_13BIT        0x1FFFu
#define RESERVED_14BIT        0x3FFFu
#define RESERVED_15BIT        0x7FFFu
#define RESERVED_16BIT        0xFFFFu
#define RESERVED_17BIT        0x1FFFFu
#define RESERVED_18BIT        0x3FFFFu
#define RESERVED_19BIT        0x7FFFFu
#define RESERVED_20BIT        0xFFFFFu
#define RESERVED_21BIT        0x1FFFFFu
#define RESERVED_22BIT        0x3FFFFFu
#define RESERVED_23BIT        0x7FFFFFu
#define RESERVED_24BIT        0xFFFFFFu
#define RESERVED_25BIT        0x1FFFFFFu
#define RESERVED_26BIT        0x3FFFFFFu
#define RESERVED_27BIT        0x7FFFFFFu
#define RESERVED_28BIT        0xFFFFFFFu
#define RESERVED_29BIT        0x1FFFFFFFu
#define RESERVED_30BIT        0x3FFFFFFFu
#define RESERVED_31BIT        0x7FFFFFFFu
#define RESERVED_32BIT        0xFFFFFFFFu


/* ATTENTION: When changing option byte values take care to update the option byte history for the option bytes check.
              Changes must be discussed with SiKo */


#define OPBT0  (0x3FF20010u)    // H'FF3213A0 OPBT0
#define OPBT1  (0xF0FB0000u)    // H'FF3213A4 OPBT1
#define OPBT2  (RESERVED_32BIT) // H'FF3213A8 OPBT2
//OPBT3 BIST and Mode control
#define OPBT3 ( \
      ((uint32) (c_STMSEL0     & 0x1u)  << 0)  /* select operating mode */ \
    | ((uint32) (c_STMSEL1     & 0x1u)  << 1)  /* select operating mode */ \
    | ((uint32) RESERVED_6BIT           << 2)  /* reserved bits */ \
    | ((uint32) (c_LBISTSEL    & 0x3u)  << 8)  /* lbist scenario selection */ \
    | ((uint32) (c_TESTSET     & 0x3u)  << 10) /* power on bist selection */ \
    | ((uint32) RESERVED_3BIT           << 12) /* reserved bits */ \
    | ((uint32) (c_HWBIST      & 0x1u)  << 15) /* power on bist enable */ \
    | ((uint32) RESERVED_9BIT           << 16) /* reserved bits */ \
    | ((uint32) (c_PE1_DISABLE & 0x1u)  << 25) /* PE1 disable bit */ \
    | ((uint32) (c_PE2_DISABLE & 0x1u)  << 26) /* PE2 disable bit */ \
    | ((uint32) (c_PE3_DISABLE & 0x1u)  << 27) /* PE3 disable bit */ \
    | ((uint32) RESERVED_4BIT           << 28) /* reserved bits */ \
  )                             // H'FF3213AC OPBT3
#define OPBT4  (0xFFFFFFFFu)    // H'FF3213B0 OPBT4
#define OPBT5  (RESERVED_32BIT) // H'FF3213B4 Reserved
#define OPBT6  (0xFFFF0FC3u)    // H'FF3213B8 OPBT6
#define OPBT7  (0xFFCFFFFFu)    // H'FF3213BC OPBT7
#define OPBT8  (0xFFFFFFFEu)    // H'FF3213C0 OPBT8

// Both cores in DCLS
#define OPBT9  (0xFFFCFFFFu)

//OPBT10 clock and main oscillator control
#define OPBT10 ( \
      ((uint32) (c_MOSC_SHTSTBY_B  & 0x1u) << 0)  /* trimming configuration */ \
    | ((uint32) (c_MOSC_SHTSTBY_A  & 0x1u) << 1)  /* trimming configuration */ \
    | ((uint32) RESERVED_2BIT              << 2)  /* reserved bits */ \
    | ((uint32) (c_MOSC_RD_SEL_B   & 0x7u) << 4)  /* trimming configuration */ \
    | ((uint32) RESERVED_1BIT              << 7)  /* reserved bits */ \
    | ((uint32) (c_MOSC_RD_SEL_A   & 0x7u) << 8)  /* trimming configuration */ \
    | ((uint32) RESERVED_1BIT              << 11) /* reserved bits */ \
    | ((uint32) (c_MOSC_CAP_SEL    & 0xFu) << 12) /* trimming configuration */ \
    | ((uint32) (c_MOSC_AMP_SEL_B  & 0x7u) << 16) /* trimming configuration */ \
    | ((uint32) RESERVED_1BIT              << 19) /* reserved bits */ \
    | ((uint32) (c_MOSC_AMP_SEL_A  & 0x7u) << 20) /* trimming configuration */ \
    | ((uint32) RESERVED_1BIT              << 23) /* reserved bits */ \
    | ((uint32) (c_MOSC_FREQ       & 0x7u) << 24) /* MOSC frequency */ \
    | ((uint32) RESERVED_1BIT              << 27) /* reserved bits */ \
    | ((uint32) (c_MOSC_EXCLKINPUT & 0x1u) << 28) /* MOSC input clock selection */ \
    | ((uint32) RESERVED_3BIT              << 29) /* reserved bits */ \
  ) // H'FF3213C8 OPBT10
/** results in OPBT10 = 0xF8FF299E */

//OPBT11 CPU frequency and PLL control
#define OPBT11 ( \
      ((uint32) RESERVED_28BIT        << 0)  /* reserved bits */ \
    | ((uint32) (c_STARTUPPLL & 0x1u) << 28) /* PLL enable at power on */ \
    | ((uint32) RESERVED_1BIT         << 29) /* reserved bits */ \
    | ((uint32) (c_CKDIVMOD   & 0x3u) << 30) /* CPU max frequency */ \
  ) // H'FF3213CC OPBT11

//OPBT12 Program Flash Mapping Mode
#define OPBT12 ( \
      ((uint32) (c_MAPMODE & 0x3u) << 0) /* PFlash usage as Double or Single Map */ \
    | ((uint32) RESERVED_30BIT     << 2) /* reserved bits */ \
  ) //H'FF3213D0
/** results in OPBT12 = 0xFFFFFFFD (Single Map) or 0xFFFFFFFC (Double Map) */

/** Switching pages between A+C and B+D will be done by bootblock team. No rbsys interface is needed. */
#define OPBT13 (0xFFFFFFFFu)    // H'FF3213D4 OPBT13 //< Feedback REL: value can be kept for M2/M3 (see U2A HW UM Rev.1.10 p.6524)
/**<  Double Memory Map: 0xF = Bank A&C are in valid memory
  *   Single Memory Map: Setting unused                      */

#define OPBT14 (0x00000192u)    // H*FF3213D8 OPBT14
//< EmulationDevice specific (see U2A HW UM 1.10 - Table 51.56) - Series Device values is used for EVA device aswell

#define OPBT15 (RESERVED_32BIT) // H'FF3213DC Reserved

//OPBT16 CPU frequency and PLL control
#define OPBT16 ( \
      ((uint32) (c_SVRADNSMP  & 0xFFu) << 0)  /* SVR ADC sampling time */ \
    | ((uint32) RESERVED_8BIT          << 8)  /* reserved bits */ \
    | ((uint32) (c_SVRAJDTP   & 0x7u)  << 16) /* SVR dead time */ \
    | ((uint32) RESERVED_1BIT          << 19) /* reserved bits */ \
    | ((uint32) (c_SVRAJDTN   & 0x7u)  << 20) /* SVR dead time */ \
    | ((uint32) RESERVED_1BIT          << 23) /* reserved bits */ \
    | ((uint32) (c_SVRAJPRDSR & 0xFu)  << 24) /* SVR slew rate */ \
    | ((uint32) nRESERVED              << 28) /* reserved bits */ \
    | ((uint32) RESERVED_2BIT          << 29) /* reserved bits */ \
    | ((uint32) (c_SVRENABLE  & 0x1u)  << 31) /* SVR enable */ \
  ) // H'FF3213E0 OPBT16

//OPBT17 CPU frequency and PLL control
#define OPBT17 ( \
      ((uint32) (c_SVRSWMODE      & 0x3u)  << 0)  /* switching frequency */ \
    | ((uint32) RESERVED_2BIT              << 2)  /* reserved bits */ \
    | ((uint32) (c_SVRMINSKIPDUTY & 0x3u)  << 4)  /* skip minimum puls */ \
    | ((uint32) RESERVED_2BIT              << 6)  /* reserved bits */ \
    | ((uint32) (c_SVRMAXDUTY     & 0xFFu) << 8)  /* maximum on duty */ \
    | ((uint32) (c_SVRADTHRESH    & 0xFFu) << 16) /* SVR ADC sampling start state */ \
    | ((uint32) (c_SVRADTHRESHE   & 0xFFu) << 24) /* SVR ADC conversion completion state */ \
  ) // H'FF3213E4 OPBT17

//OPBT18 CPU frequency and PLL control
#define OPBT18 ( \
      ((uint32) (c_SVRKPVSCL & 0x3FFFu) << 0)  /* SVR PID parameter */ \
    | ((uint32) RESERVED_2BIT           << 14) /* reserved bits */ \
    | ((uint32) (c_SVRKIVSCL & 0x3FFFu) << 16) /* SVR PID parameter */ \
    | ((uint32) RESERVED_2BIT           << 30) /* reserved bits */ \
  ) // H'FF3213E8 OPBT18

//OPBT19 CPU frequency and PLL control
#define OPBT19 ( \
      ((uint32) (c_SVRKDVSCL & 0x3FFFu) << 0) /* SVR PID parameter */ \
    | ((uint32) RESERVED_18BIT         << 14) /* reserved bits */ \
  ) // H'FF3213EC OPBT19

#if( RBFS_RBSYSuCSupplyVoltageRegulator == RBFS_RBSYSuCSupplyVoltageRegulator_Enabled)
  #define OPBT20 ( \
      ((uint32) ((~c_SVRADNSMP)  & 0xFFu) << 0)  /* inverted SVR ADC sampling time */ \
    | ((uint32) RESERVED_8BIT             << 8)  /* reserved bits */ \
    | ((uint32) ((~c_SVRAJDTP)   & 0x7u)  << 16) /* inverted SVR dead time */ \
    | ((uint32) RESERVED_1BIT             << 19) /* reserved bits */ \
    | ((uint32) ((~c_SVRAJDTN)   & 0x7u)  << 20) /* inverted SVR dead time */ \
    | ((uint32) RESERVED_1BIT             << 23) /* reserved bits */ \
    | ((uint32) ((~c_SVRAJPRDSR) & 0xFu)  << 24) /* inverted SVR slew rate */ \
    | ((uint32) RESERVED_1BIT             << 28) /* reserved bits */ \
    | ((uint32) RESERVED_2BIT             << 29) /* reserved bits */ \
    | ((uint32) ((~c_SVRENABLE)  & 0x1u)  << 31) /* inverted SVR enable */ \
  ) // H'FF3213F0 OPBT20
  #define OPBT21 ( \
      ((uint32) ((~c_SVRSWMODE)      & 0x3u)  << 0)  /* inverted switching frequency */ \
    | ((uint32) RESERVED_2BIT                 << 2)  /* reserved bits */ \
    | ((uint32) ((~c_SVRMINSKIPDUTY) & 0x3u)  << 4)  /* inverted skip minimum puls */ \
    | ((uint32) RESERVED_2BIT                 << 6)  /* reserved bits */ \
    | ((uint32) ((~c_SVRMAXDUTY)     & 0xFFu) << 8)  /* inverted maximum on duty */ \
    | ((uint32) ((~c_SVRADTHRESH)    & 0xFFu) << 16) /* inverted SVR ADC sampling start state */ \
    | ((uint32) ((~c_SVRADTHRESHE)   & 0xFFu) << 24) /* inverted SVR ADC conversion completion state */ \
  ) // H'FF3213F4 OPBT21
  #define OPBT22 ( \
      ((uint32) ((~c_SVRKPVSCL) & 0x3FFFu) << 0)  /* inverted SVR PID parameter */ \
    | ((uint32) RESERVED_2BIT              << 14) /* reserved bits */ \
    | ((uint32) ((~c_SVRKIVSCL) & 0x3FFFu) << 16) /* inverted SVR PID parameter */ \
    | ((uint32) RESERVED_2BIT              << 30) /* reserved bits */ \
  ) // H'FF3213F8 OPBT22
  #define OPBT23 ( \
      ((uint32) ((~c_SVRKDVSCL) & 0x3FFFu) << 0)  /* inverted SVR PID parameter */ \
    | ((uint32) RESERVED_18BIT             << 14) /* reserved bits */ \
  ) // H'FF3213FC OPBT23
#else
  #define OPBT20 ( \
      ((uint32) (c_SVRADNSMP  & 0xFFu) << 0)  /* SVR ADC sampling time */ \
    | ((uint32) RESERVED_8BIT          << 8)  /* reserved bits */ \
    | ((uint32) (c_SVRAJDTP   & 0x7u)  << 16) /* SVR dead time */ \
    | ((uint32) RESERVED_1BIT          << 19) /* reserved bits */ \
    | ((uint32) (c_SVRAJDTN   & 0x7u)  << 20) /* SVR dead time */ \
    | ((uint32) RESERVED_1BIT          << 23) /* reserved bits */ \
    | ((uint32) (c_SVRAJPRDSR & 0xFu)  << 24) /* SVR slew rate */ \
    | ((uint32) RESERVED_1BIT          << 28) /* reserved bits */ \
    | ((uint32) RESERVED_2BIT          << 29) /* reserved bits */ \
    | ((uint32) (c_SVRENABLE  & 0x1u)  << 31) /* SVR enable */ \
  ) // H'FF3213F0 OPBT20
  #define OPBT21 ( \
      ((uint32) (c_SVRSWMODE      & 0x3u)  << 0)  /* switching frequency */ \
    | ((uint32) RESERVED_2BIT              << 2)  /* reserved bits */ \
    | ((uint32) (c_SVRMINSKIPDUTY & 0x3u)  << 4)  /* skip minimum puls */ \
    | ((uint32) RESERVED_2BIT              << 6)  /* reserved bits */ \
    | ((uint32) (c_SVRMAXDUTY     & 0xFFu) << 8)  /* maximum on duty */ \
    | ((uint32) (c_SVRADTHRESH    & 0xFFu) << 16) /* SVR ADC sampling start state */ \
    | ((uint32) (c_SVRADTHRESHE   & 0xFFu) << 24) /* SVR ADC conversion completion state */ \
  ) // H'FF3213F4 OPBT21
  #define OPBT22 ( \
      ((uint32) (c_SVRKPVSCL & 0x3FFFu) << 0)  /* SVR PID parameter */ \
    | ((uint32) RESERVED_2BIT           << 14) /* reserved bits */ \
    | ((uint32) (c_SVRKIVSCL & 0x3FFFu) << 16) /* SVR PID parameter */ \
    | ((uint32) RESERVED_2BIT           << 30) /* reserved bits */ \
  ) // H'FF3213F8 OPBT22
  #define OPBT23 ( \
      ((uint32) (c_SVRKDVSCL & 0x3FFFu) << 0) /* SVR PID parameter */ \
    | ((uint32) RESERVED_18BIT         << 14) /* reserved bits */ \
  ) // H'FF3213FC OPBT23
#endif

#endif
