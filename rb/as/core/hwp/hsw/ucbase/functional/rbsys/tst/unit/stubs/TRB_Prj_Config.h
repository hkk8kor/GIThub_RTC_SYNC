#ifndef TRB_PRJ_CONFIG_H__
#define TRB_PRJ_CONFIG_H__

#include "TRB_Prj_ConfigElements.h"

#include "RBCMHSW_Global.h"
#include "Platform_Types.h"
#include "Cfg_MTC_ConfigurationDefines.cfg"
#include "RB_AssertSwitchSettings.h"

// CMHSW is including RBSYS_LocksImpl.h
#include "RBSYS_LocksImpl.h"

#include "RBSYS_ConfigElements.h"

/**************************************************************************************/
/***************                  Device configuration                  ***************/
/**************************************************************************************/

/* specific configurations for specific unittests */
#if (  (RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_TRBSYS_GuardConfigU2A) \
    || (RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_TRBSYS_FlashConfigAreaU2A) \
    )
  #define RBFS_uCRenesasU2A RBFS_uCRenesasU2A_M6onM6ED
#endif

#if (  (RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_TRBSYS_GuardConfigP1x) \
    || (RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_TRBSYS_FlashConfigAreaP1x) \
    )
  #define RBFS_uCRenesasP1x RBFS_uCRenesasP1x_D5onD5ED
#endif

#if (  (RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_TRBSYS_GuardConfigStellar) \
    || (RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_TRBSYS_FlashConfigAreaStellar) \
    )
  #define RBFS_uC RBFS_uC_STMP6onP7ED
#endif

#if (  (RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_TRBSYS_GuardConfigU2C) \
    || (RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_TRBSYS_FlashConfigAreaU2C) \
    )
  #define RBFS_uC RBFS_uC_RenesasK1onK3ED
#endif

#if( RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_TRBSYS_GuardConfigBB )
  #define RBFS_HexBlockBuild RBFS_HexBlockBuild_RBBOOTLOADER
  #define RBFS_BootblockEnableAsicSupport RBFS_BootblockEnableAsicSupport_ON
#endif

#if (  ( RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_TRBSYS_uCReset_Bootblock ) \
    || ( RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_TRBSYS_BootblockStartup ) \
    || ( RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_TRBSYS_BBFSWSS ) \
    )
  #define RBFS_HexBlockBuild RBFS_HexBlockBuild_BOOTMANAGER
#endif


#if (RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_TRBSYS_PerformanceCounter)
  #define RBFS_uC                             RBFS_uC_RenesasK1
#endif

#if (RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_TRBSYS_BootblockStartup \
  || RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_TRBSYS_uCReset_Bootblock)
  #define RBFS_BootblockSysStartupCode        RBFS_BootblockSysStartupCode_ON
#else
  #define RBFS_BootblockSysStartupCode        RBFS_BootblockSysStartupCode_OFF
#endif


/* set RBFS_uC if variance execution over a single uC family is used */
#ifdef RBFS_uCRenesasP1x
  #if   (RBFS_uCRenesasP1x == RBFS_uCRenesasP1x_D1)
    #define RBFS_uC RBFS_uC_RenesasD1
  #elif (RBFS_uCRenesasP1x == RBFS_uCRenesasP1x_D1onD3ED)
    #define RBFS_uC RBFS_uC_RenesasD1onD3ED
  #elif (RBFS_uCRenesasP1x == RBFS_uCRenesasP1x_D2)
    #define RBFS_uC RBFS_uC_RenesasD2
  #elif (RBFS_uCRenesasP1x == RBFS_uCRenesasP1x_D2onD3ED)
    #define RBFS_uC RBFS_uC_RenesasD2onD3ED
  #elif (RBFS_uCRenesasP1x == RBFS_uCRenesasP1x_160MHzD3)
    #define RBFS_uC RBFS_uC_Renesas160MHzD3
  #elif (RBFS_uCRenesasP1x == RBFS_uCRenesasP1x_160MHzD3onD3ED)
    #define RBFS_uC RBFS_uC_Renesas160MHzD3onD3ED
  #elif (RBFS_uCRenesasP1x == RBFS_uCRenesasP1x_160MHzD3onD5ED)
    #define RBFS_uC RBFS_uC_Renesas160MHzD3onD5ED
  #elif (RBFS_uCRenesasP1x == RBFS_uCRenesasP1x_240MHzD3)
    #define RBFS_uC RBFS_uC_Renesas240MHzD3
  #elif (RBFS_uCRenesasP1x == RBFS_uCRenesasP1x_240MHzD3onD3ED)
    #define RBFS_uC RBFS_uC_Renesas240MHzD3onD3ED
  #elif (RBFS_uCRenesasP1x == RBFS_uCRenesasP1x_240MHzD3onD5ED)
    #define RBFS_uC RBFS_uC_Renesas240MHzD3onD5ED
  #elif (RBFS_uCRenesasP1x == RBFS_uCRenesasP1x_D4)
    #define RBFS_uC RBFS_uC_RenesasD4
  #elif (RBFS_uCRenesasP1x == RBFS_uCRenesasP1x_D4onD5ED)
    #define RBFS_uC RBFS_uC_RenesasD4onD5ED
  #elif (RBFS_uCRenesasP1x == RBFS_uCRenesasP1x_D5)
    #define RBFS_uC RBFS_uC_RenesasD5
  #elif (RBFS_uCRenesasP1x == RBFS_uCRenesasP1x_D5onD5ED)
    #define RBFS_uC RBFS_uC_RenesasD5onD5ED
  #endif
#endif

#ifdef RBFS_uCRenesasU2A
  #if   (RBFS_uCRenesasU2A == RBFS_uCRenesasU2A_M2)
    #define RBFS_uC RBFS_uC_RenesasM2
  #elif (RBFS_uCRenesasU2A == RBFS_uCRenesasU2A_M2onM6ED)
    #define RBFS_uC RBFS_uC_RenesasM2onM6ED
  #elif (RBFS_uCRenesasU2A == RBFS_uCRenesasU2A_M3)
    #define RBFS_uC RBFS_uC_RenesasM3
  #elif (RBFS_uCRenesasU2A == RBFS_uCRenesasU2A_M3onM6ED)
    #define RBFS_uC RBFS_uC_RenesasM3onM6ED
  #elif (RBFS_uCRenesasU2A == RBFS_uCRenesasU2A_D7)
    #define RBFS_uC RBFS_uC_RenesasD7
  #elif (RBFS_uCRenesasU2A == RBFS_uCRenesasU2A_M6)
    #define RBFS_uC RBFS_uC_RenesasM6
  #elif (RBFS_uCRenesasU2A == RBFS_uCRenesasU2A_D7onD7ED)
    #define RBFS_uC RBFS_uC_RenesasD7onD7ED
  #elif (RBFS_uCRenesasU2A == RBFS_uCRenesasU2A_M6onM6ED)
    #define RBFS_uC RBFS_uC_RenesasM6onM6ED
  #endif
#endif

#ifdef RBFS_uCRenesasU2C
  #if (RBFS_uCRenesasU2C == RBFS_uC_RenesasK0)
    #define RBFS_uC RBFS_uC_RenesasK0
  #elif (RBFS_uCRenesasU2C == RBFS_uC_RenesasK0onK3ED)
    #define RBFS_uC RBFS_uC_RenesasK0onK3ED
  #elif (RBFS_uCRenesasU2C == RBFS_uC_RenesasK1)
    #define RBFS_uC RBFS_uC_RenesasK1
  #elif (RBFS_uCRenesasU2C == RBFS_uC_RenesasK1onK3ED)
    #define RBFS_uC RBFS_uC_RenesasK1onK3ED
  #endif
#endif

#ifdef RBFS_uCSTMStellar
  #if (RBFS_uCSTMStellar == RBFS_uCSTMStellar_P6onP7ED)
    #define RBFS_uC RBFS_uC_STMP6onP7ED
  #elif (RBFS_uCSTMStellar == RBFS_uCSTMStellar_P6)
    #define RBFS_uC RBFS_uC_STMP6
  #endif
#endif

#ifdef RBFS_uCandPackage
  #if(RBFS_uCandPackage == RBFS_uCandPackage_D1QFP80)
    #define RBFS_uC RBFS_uC_RenesasD1
    #define RBFS_uCPackage RBFS_uCPackage_QFP80
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_D1onD3EDQFP80)
    #define RBFS_uC RBFS_uC_RenesasD1onD3ED
    #define RBFS_uCPackage RBFS_uCPackage_QFP80
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_D1QFP100)
    #define RBFS_uC RBFS_uC_RenesasD1
    #define RBFS_uCPackage RBFS_uCPackage_QFP100
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_D1onD3EDQFP100)
    #define RBFS_uC RBFS_uC_RenesasD1onD3ED
    #define RBFS_uCPackage RBFS_uCPackage_QFP100
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_D2QFP100)
    #define RBFS_uC RBFS_uC_RenesasD2
    #define RBFS_uCPackage RBFS_uCPackage_QFP100
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_D2onD3EDQFP100)
    #define RBFS_uC RBFS_uC_RenesasD2onD3ED
    #define RBFS_uCPackage RBFS_uCPackage_QFP100
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_D2QFP144)
    #define RBFS_uC RBFS_uC_RenesasD2
    #define RBFS_uCPackage RBFS_uCPackage_QFP144
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_D2onD3EDQFP144)
    #define RBFS_uC RBFS_uC_RenesasD2onD3ED
    #define RBFS_uCPackage RBFS_uCPackage_QFP144
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_160MHzD3QFP144)
    #define RBFS_uC RBFS_uC_Renesas160MHzD3
    #define RBFS_uCPackage RBFS_uCPackage_QFP144
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_160MHzD3onD3EDQFP144)
    #define RBFS_uC RBFS_uC_Renesas160MHzD3onD3ED
    #define RBFS_uCPackage RBFS_uCPackage_QFP144
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_160MHzD3onD5EDQFP144)
    #define RBFS_uC RBFS_uC_Renesas160MHzD3onD5ED
    #define RBFS_uCPackage RBFS_uCPackage_QFP144
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_160MHzD3BGA156)
    #define RBFS_uC RBFS_uC_Renesas160MHzD3
    #define RBFS_uCPackage RBFS_uCPackage_BGA156
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_160MHzD3onD3EDBGA156)
    #define RBFS_uC RBFS_uC_Renesas160MHzD3onD3ED
    #define RBFS_uCPackage RBFS_uCPackage_BGA156
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_160MHzD3onD5EDBGA156)
    #define RBFS_uC RBFS_uC_Renesas160MHzD3onD5ED
    #define RBFS_uCPackage RBFS_uCPackage_BGA156
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_160MHzD3BGA292)
    #define RBFS_uC RBFS_uC_Renesas160MHzD3
    #define RBFS_uCPackage RBFS_uCPackage_BGA292
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_160MHzD3onD5EDBGA292)
    #define RBFS_uC RBFS_uC_Renesas160MHzD3onD5ED
    #define RBFS_uCPackage RBFS_uCPackage_BGA292
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_240MHzD3QFP144)
    #define RBFS_uC RBFS_uC_Renesas240MHzD3
    #define RBFS_uCPackage RBFS_uCPackage_QFP144
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_240MHzD3onD3EDQFP144)
    #define RBFS_uC RBFS_uC_Renesas240MHzD3onD3ED
    #define RBFS_uCPackage RBFS_uCPackage_QFP144
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_240MHzD3onD5EDQFP144)
    #define RBFS_uC RBFS_uC_Renesas240MHzD3onD5ED
    #define RBFS_uCPackage RBFS_uCPackage_QFP144
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_240MHzD3BGA156)
    #define RBFS_uC RBFS_uC_Renesas240MHzD3
    #define RBFS_uCPackage RBFS_uCPackage_BGA156
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_240MHzD3onD3EDBGA156)
    #define RBFS_uC RBFS_uC_Renesas240MHzD3onD3ED
    #define RBFS_uCPackage RBFS_uCPackage_BGA156
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_240MHzD3onD5EDBGA156)
    #define RBFS_uC RBFS_uC_Renesas240MHzD3onD5ED
    #define RBFS_uCPackage RBFS_uCPackage_BGA156
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_240MHzD3BGA292)
    #define RBFS_uC RBFS_uC_Renesas240MHzD3
    #define RBFS_uCPackage RBFS_uCPackage_BGA292
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_240MHzD3onD5EDBGA292)
    #define RBFS_uC RBFS_uC_Renesas240MHzD3onD5ED
    #define RBFS_uCPackage RBFS_uCPackage_BGA292
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_D4BGA292)
    #define RBFS_uC RBFS_uC_RenesasD4
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_D4onD5EDBGA292)
    #define RBFS_uC RBFS_uC_RenesasD4onD5ED
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_D5BGA292)
    #define RBFS_uC RBFS_uC_RenesasD5
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_D5onD5EDBGA292)
    #define RBFS_uC RBFS_uC_RenesasD5onD5ED
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_M2QFP144)
    #define RBFS_uC RBFS_uC_RenesasM2
    #define RBFS_uCPackage RBFS_uCPackage_QFP144
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_M2onM6EDQFP144)
    #define RBFS_uC RBFS_uC_RenesasM2onM6ED
    #define RBFS_uCPackage RBFS_uCPackage_QFP144
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_M2BGA292)
    #define RBFS_uC RBFS_uC_RenesasM2
    #define RBFS_uCPackage RBFS_uCPackage_BGA292
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_M2onM6EDBGA292)
    #define RBFS_uC RBFS_uC_RenesasM2onM6ED
    #define RBFS_uCPackage RBFS_uCPackage_BGA292
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_M3BGA292)
    #define RBFS_uC RBFS_uC_RenesasM3
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_M3onM6EDBGA292)
    #define RBFS_uC RBFS_uC_RenesasM3onM6ED
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_M6BGA292)
    #define RBFS_uC RBFS_uC_RenesasM6
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_M6onM6EDBGA292)
    #define RBFS_uC RBFS_uC_RenesasM6onM6ED
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_K0QFP144)
    #define RBFS_uC RBFS_uC_RenesasK0
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_K0onK3EDBGA404)
    #define RBFS_uC RBFS_uC_RenesasK0onK3ED
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_K1QFP144)
    #define RBFS_uC RBFS_uC_RenesasK1
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_K1BGA292)
    #define RBFS_uC RBFS_uC_RenesasK1
  #elif(RBFS_uCandPackage == RBFS_uCandPackage_K1onK3EDBGA404)
    #define RBFS_uC RBFS_uC_RenesasK1onK3ED
  #endif
#endif


/* default switch settings in case variance unit test execution is not used */
#ifndef RBFS_uC
  #define RBFS_uC                               RBFS_uC_RenesasD5onD5ED
#endif









/**************************************************************************************/
/***************                Device config derivation                ***************/
/**************************************************************************************/

#define RBFS_TargetDevice_RenesasD1 1
#define RBFS_TargetDevice_RenesasD2 2
#define RBFS_TargetDevice_RenesasD3 3
#define RBFS_TargetDevice_RenesasD4 4
#define RBFS_TargetDevice_RenesasD5 5
#define RBFS_TargetDevice_RenesasD7 8
#define RBFS_TargetDevice_RenesasM2 6
#define RBFS_TargetDevice_RenesasM3 7
#define RBFS_TargetDevice_RenesasM6 8
#define RBFS_TargetDevice_STMP2     9
#define RBFS_TargetDevice_STMP3     10
#define RBFS_TargetDevice_STMP6     11
#define RBFS_TargetDevice_RenesasK0 12
#define RBFS_TargetDevice_RenesasK1 13


#define RBFS_uCFamily_RenesasP1x    1
#define RBFS_uCFamily_RenesasU2A    2
#define RBFS_uCFamily_STMStellar    3
#define RBFS_uCFamily_RenesasU2C    4

#define RBFS_EmulationDevice_None           1
#define RBFS_EmulationDevice_RenesasD3ED    2
#define RBFS_EmulationDevice_RenesasD5ED    3
#define RBFS_EmulationDevice_RenesasD7ED    4
#define RBFS_EmulationDevice_RenesasM6ED    4
#define RBFS_EmulationDevice_STMP3ED        5
#define RBFS_EmulationDevice_STMP7ED        6
#define RBFS_EmulationDevice_RenesasK3ED    7

#define RBFS_ConfigCore_SingleCore          1
#define RBFS_ConfigCore_MultiCore           2

#define RBFS_MCORE_OFF  1
#define RBFS_MCORE_ON   2

#define RBFS_RenesasP1xGRAM_OFF   1
#define RBFS_RenesasP1xGRAM_ON    2

#define RBFS_RenesasU2aCRAM0_ON          1
#define RBFS_RenesasU2aCRAM0_OFF         2

#define RBFS_RenesasU2aCRAM1_ON          1
#define RBFS_RenesasU2aCRAM1_OFF         2

#define RBFS_RenesasU2aCRAM2_ON          1
#define RBFS_RenesasU2aCRAM2_OFF         2

#define RBFS_RenesasU2aCRAM3_ON          1
#define RBFS_RenesasU2aCRAM3_OFF         2

#define RBFS_RenesasU2cCRAM0_ON          1
#define RBFS_RenesasU2cCRAM0_OFF         2

#define RBFS_DataFlashECC_Disabled       1
#define RBFS_DataFlashECC_Enabled        2

#define RBFS_LocalRamCore1Support_ON     1
#define RBFS_LocalRamCore1Support_OFF    2

#define RBFS_LocalRamCore2Support_ON     1
#define RBFS_LocalRamCore2Support_OFF    2

#define RBFS_LocalRamCore3Support_ON     1
#define RBFS_LocalRamCore3Support_OFF    2

#define RBFS_LocalRamCore4Support_ON     1
#define RBFS_LocalRamCore4Support_OFF    2

#define RBFS_LocalRamCore5Support_ON     1
#define RBFS_LocalRamCore5Support_OFF    2

#define RBFS_FlashBank0Support_ON        1
#define RBFS_FlashBank0Support_INACTIVE  2
#define RBFS_FlashBank0Support_OFF       3

#define RBFS_FlashBank1Support_ON        1
#define RBFS_FlashBank1Support_INACTIVE  2
#define RBFS_FlashBank1Support_OFF       3

#define RBFS_FlashBank2Support_ON        1
#define RBFS_FlashBank2Support_INACTIVE  2
#define RBFS_FlashBank2Support_OFF       3

#define RBFS_FlashBank3Support_ON        1
#define RBFS_FlashBank3Support_INACTIVE  2
#define RBFS_FlashBank3Support_OFF       3

#define RBFS_FlashBank4Support_ON        1
#define RBFS_FlashBank4Support_INACTIVE  2
#define RBFS_FlashBank4Support_OFF       3

#define RBFS_FlashBank5Support_ON        1
#define RBFS_FlashBank5Support_INACTIVE  2
#define RBFS_FlashBank5Support_OFF       3

#define RBFS_GlobalRamSupport_OFF  1
#define RBFS_GlobalRamSupport_ON   2

#define RBFS_CpuClock_80MHz     1
#define RBFS_CpuClock_160MHz    2
#define RBFS_CpuClock_240MHz    3
#define RBFS_CpuClock_320MHz    4
#define RBFS_CpuClock_400MHz    5



#if (RBFS_uC == RBFS_uC_RenesasD1)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD1
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_None
  #define RBFS_CpuClock                   RBFS_CpuClock_80MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_SingleCore
  #define RBFS_MCORE                      RBFS_MCORE_OFF
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_OFF
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_OFF
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Unsupported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasP1x
#endif

#if (RBFS_uC == RBFS_uC_RenesasD1onD3ED)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD1
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_RenesasD3ED
  #define RBFS_CpuClock                   RBFS_CpuClock_80MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_SingleCore
  #define RBFS_MCORE                      RBFS_MCORE_OFF
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_OFF
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Unsupported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasP1x
#endif

#if (RBFS_uC == RBFS_uC_RenesasD2)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD2
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_None
  #define RBFS_CpuClock                   RBFS_CpuClock_80MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_SingleCore
  #define RBFS_MCORE                      RBFS_MCORE_OFF
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_OFF
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_OFF
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Unsupported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasP1x
#endif

#if (RBFS_uC == RBFS_uC_RenesasD2onD3ED)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD2
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_RenesasD3ED
  #define RBFS_CpuClock                   RBFS_CpuClock_80MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_SingleCore
  #define RBFS_MCORE                      RBFS_MCORE_OFF
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_OFF
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Unsupported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasP1x
#endif

#if (RBFS_uC == RBFS_uC_Renesas160MHzD3)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD3
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_None
  #define RBFS_CpuClock                   RBFS_CpuClock_160MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_SingleCore
  #define RBFS_MCORE                      RBFS_MCORE_OFF
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_OFF
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_OFF
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_ON
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasP1x
#endif

#if (RBFS_uC == RBFS_uC_Renesas160MHzD3onD3ED)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD3
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_RenesasD3ED
  #define RBFS_CpuClock                   RBFS_CpuClock_160MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_SingleCore
  #define RBFS_MCORE                      RBFS_MCORE_OFF
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_OFF
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_ON
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasP1x
#endif

#if (RBFS_uC == RBFS_uC_Renesas160MHzD3onD5ED)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD3
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_RenesasD5ED
  #define RBFS_CpuClock                   RBFS_CpuClock_160MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_SingleCore
  #define RBFS_MCORE                      RBFS_MCORE_OFF
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_OFF
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_ON
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasP1x
#endif

#if (RBFS_uC == RBFS_uC_Renesas240MHzD3)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD3
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_None
  #define RBFS_CpuClock                   RBFS_CpuClock_240MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_SingleCore
  #define RBFS_MCORE                      RBFS_MCORE_OFF
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_OFF
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_OFF
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_ON
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasP1x
#endif

#if (RBFS_uC == RBFS_uC_Renesas240MHzD3onD3ED)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD3
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_RenesasD3ED
  #define RBFS_CpuClock                   RBFS_CpuClock_240MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_SingleCore
  #define RBFS_MCORE                      RBFS_MCORE_OFF
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_OFF
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_ON
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasP1x
#endif

#if (RBFS_uC == RBFS_uC_Renesas240MHzD3onD5ED)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD3
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_RenesasD5ED
  #define RBFS_CpuClock                   RBFS_CpuClock_240MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_SingleCore
  #define RBFS_MCORE                      RBFS_MCORE_OFF
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_OFF
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_ON
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasP1x
#endif

#if (RBFS_uC == RBFS_uC_RenesasD4)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD4
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_None
  #define RBFS_CpuClock                   RBFS_CpuClock_240MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_MultiCore
  #define RBFS_MCORE                      RBFS_MCORE_ON
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_ON
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_ON
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasP1x
#endif

#if (RBFS_uC == RBFS_uC_RenesasD4onD5ED)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD4
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_RenesasD5ED
  #define RBFS_CpuClock                   RBFS_CpuClock_240MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_MultiCore
  #define RBFS_MCORE                      RBFS_MCORE_ON
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_ON
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_ON
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasP1x
#endif

#if (RBFS_uC == RBFS_uC_RenesasD5)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD5
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_None
  #define RBFS_CpuClock                   RBFS_CpuClock_240MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_MultiCore
  #define RBFS_MCORE                      RBFS_MCORE_ON
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_ON
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_ON
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasP1x
#endif

#if (RBFS_uC == RBFS_uC_RenesasD5onD5ED)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD5
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_RenesasD5ED
  #define RBFS_CpuClock                   RBFS_CpuClock_240MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_MultiCore
  #define RBFS_MCORE                      RBFS_MCORE_ON
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_ON
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_ON
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasP1x
#endif

#if (RBFS_uC == RBFS_uC_RenesasM2)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasM2
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_None
  #define RBFS_CpuClock                   RBFS_CpuClock_400MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_MultiCore
  #define RBFS_MCORE                      RBFS_MCORE_ON
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_ON
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_ON
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_ON
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasU2A
  #define RBFS_CPUMisalignedAccessSupport RBFS_CPUMisalignedAccessSupport_OFF
#endif

#if (RBFS_uC == RBFS_uC_RenesasM2onM6ED)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasM2
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_RenesasM6ED
  #define RBFS_CpuClock                   RBFS_CpuClock_400MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_MultiCore
  #define RBFS_MCORE                      RBFS_MCORE_ON
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_ON
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_ON
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_ON
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasU2A
  #define RBFS_CPUMisalignedAccessSupport RBFS_CPUMisalignedAccessSupport_OFF
#endif

#if (RBFS_uC == RBFS_uC_RenesasM3)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasM3
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_None
  #define RBFS_CpuClock                   RBFS_CpuClock_400MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_MultiCore
  #define RBFS_MCORE                      RBFS_MCORE_ON
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_ON
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_ON
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_ON
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_ON
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasU2A
  #define RBFS_CPUMisalignedAccessSupport RBFS_CPUMisalignedAccessSupport_OFF
#endif

#if (RBFS_uC == RBFS_uC_RenesasM3onM6ED)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasM3
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_RenesasM6ED
  #define RBFS_CpuClock                   RBFS_CpuClock_400MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_MultiCore
  #define RBFS_MCORE                      RBFS_MCORE_ON
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_ON
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_ON
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_ON
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_ON
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasU2A
  #define RBFS_CPUMisalignedAccessSupport RBFS_CPUMisalignedAccessSupport_OFF
#endif

#if (RBFS_uC == RBFS_uC_RenesasD7)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD7
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_None
  #define RBFS_CpuClock                   RBFS_CpuClock_400MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_MultiCore
  #define RBFS_MCORE                      RBFS_MCORE_ON
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_ON
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_ON
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_ON
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_ON
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_ON
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_ON
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_ON
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_ON
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_ON
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasU2A
  #define RBFS_CPUMisalignedAccessSupport RBFS_CPUMisalignedAccessSupport_OFF
#endif

#if (RBFS_uC == RBFS_uC_RenesasD7onD7ED)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasD7
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_RenesasD7ED
  #define RBFS_CpuClock                   RBFS_CpuClock_400MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_MultiCore
  #define RBFS_MCORE                      RBFS_MCORE_ON
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_ON
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_ON
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_ON
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_ON
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_ON
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_ON
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_ON
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_ON
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_ON
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasU2A
  #define RBFS_CPUMisalignedAccessSupport RBFS_CPUMisalignedAccessSupport_OFF
#endif

#if (RBFS_uC == RBFS_uC_RenesasK0)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasK0
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_None
  #define RBFS_CpuClock                   RBFS_CpuClock_320MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_SingleCore
  #define RBFS_MCORE                      RBFS_MCORE_OFF
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_OFF
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_ON
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasU2C
  #define RBFS_CPUMisalignedAccessSupport RBFS_CPUMisalignedAccessSupport_OFF
#endif

#if (RBFS_uC == RBFS_uC_RenesasK0onK3ED)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasK0
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_RenesasK3ED
  #define RBFS_CpuClock                   RBFS_CpuClock_320MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_SingleCore
  #define RBFS_MCORE                      RBFS_MCORE_OFF
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_OFF
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_ON
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasU2C
  #define RBFS_CPUMisalignedAccessSupport RBFS_CPUMisalignedAccessSupport_OFF
#endif

#if (RBFS_uC == RBFS_uC_RenesasK1)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasK1
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_None
  #define RBFS_CpuClock                   RBFS_CpuClock_320MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_MultiCore
  #define RBFS_MCORE                      RBFS_MCORE_ON
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_ON
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_ON
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasU2C
  #define RBFS_CPUMisalignedAccessSupport RBFS_CPUMisalignedAccessSupport_OFF
#endif

#if (RBFS_uC == RBFS_uC_RenesasK1onK3ED)
  #define RBFS_TargetDevice               RBFS_TargetDevice_RenesasK1
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_RenesasK3ED
  #define RBFS_CpuClock                   RBFS_CpuClock_320MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_MultiCore
  #define RBFS_MCORE                      RBFS_MCORE_ON
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_ON
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_OFF
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_OFF
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_OFF
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_OFF
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_ON
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_RenesasU2C
  #define RBFS_CPUMisalignedAccessSupport RBFS_CPUMisalignedAccessSupport_OFF
#endif

#if (RBFS_uC == RBFS_uC_STMP6onP7ED)
  #define RBFS_TargetDevice               RBFS_TargetDevice_STMP6
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_STMP7ED
  #define RBFS_CpuClock                   RBFS_CpuClock_400MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_MultiCore
  #define RBFS_MCORE                      RBFS_MCORE_ON
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_ON
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_ON
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_ON
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_ON
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_ON
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_STMStellar
  #define RBFS_CPUMisalignedAccessSupport RBFS_CPUMisalignedAccessSupport_OFF
#endif

#if (RBFS_uC == RBFS_uC_STMP6)
  #define RBFS_TargetDevice               RBFS_TargetDevice_STMP6
  #define RBFS_EmulationDevice            RBFS_EmulationDevice_None
  #define RBFS_CpuClock                   RBFS_CpuClock_400MHz
  #define RBFS_ConfigCore                 RBFS_ConfigCore_MultiCore
  #define RBFS_MCORE                      RBFS_MCORE_ON
  #define RBFS_LocalRamCore1Support       RBFS_LocalRamCore1Support_ON
  #define RBFS_LocalRamCore2Support       RBFS_LocalRamCore2Support_OFF
  #define RBFS_LocalRamCore3Support       RBFS_LocalRamCore3Support_OFF
  #define RBFS_LocalRamCore4Support       RBFS_LocalRamCore4Support_OFF
  #define RBFS_LocalRamCore5Support       RBFS_LocalRamCore5Support_OFF
  #define RBFS_FlashBank0Support          RBFS_FlashBank0Support_ON
  #define RBFS_FlashBank1Support          RBFS_FlashBank1Support_ON
  #define RBFS_FlashBank2Support          RBFS_FlashBank2Support_ON
  #define RBFS_FlashBank3Support          RBFS_FlashBank3Support_ON
  #define RBFS_FlashBank4Support          RBFS_FlashBank4Support_ON
  #define RBFS_FlashBank5Support          RBFS_FlashBank5Support_ON
  #define RBFS_RenesasP1xGRAM             RBFS_RenesasP1xGRAM_OFF
  #define RBFS_RenesasU2aCRAM0            RBFS_RenesasU2aCRAM0_OFF
  #define RBFS_RenesasU2aCRAM1            RBFS_RenesasU2aCRAM1_OFF
  #define RBFS_RenesasU2aCRAM2            RBFS_RenesasU2aCRAM2_OFF
  #define RBFS_RenesasU2aCRAM3            RBFS_RenesasU2aCRAM3_OFF
  #define RBFS_RenesasU2cCRAM0            RBFS_RenesasU2cCRAM0_OFF
  #define RBFS_HardwareSecurityModule     RBFS_HardwareSecurityModule_Supported
  #define RBFS_uCFamily                   RBFS_uCFamily_STMStellar
  #define RBFS_CPUMisalignedAccessSupport RBFS_CPUMisalignedAccessSupport_OFF
#endif

#if ( (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)   || \
      (RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON) || \
      (RBFS_RenesasU2aCRAM1 == RBFS_RenesasU2aCRAM1_ON) || \
      (RBFS_RenesasU2aCRAM2 == RBFS_RenesasU2aCRAM2_ON) || \
      (RBFS_RenesasU2aCRAM3 == RBFS_RenesasU2aCRAM3_ON)    \
    )
  #define RBFS_GlobalRamSupport     RBFS_GlobalRamSupport_ON
#else
  #define RBFS_GlobalRamSupport     RBFS_GlobalRamSupport_OFF
#endif

#if (RBFS_MCORE == RBFS_MCORE_OFF)
  #define RB_NUM_CORES                1
#else
  #define RB_NUM_CORES                2
#endif

#ifndef RBFS_uCPackage
  #if (RBFS_uC == RBFS_uC_RenesasD1)
    #define RBFS_uCPackage             RBFS_uCPackage_QFP80
  #elif (RBFS_uC == RBFS_uC_RenesasD1onD3ED)
    #define RBFS_uCPackage             RBFS_uCPackage_QFP100
  #elif (RBFS_uC == RBFS_uC_RenesasD2)
    #define RBFS_uCPackage             RBFS_uCPackage_QFP100
  #elif (RBFS_uC == RBFS_uC_RenesasD2onD3ED)
    #define RBFS_uCPackage             RBFS_uCPackage_QFP144
  #elif (RBFS_uC == RBFS_uC_Renesas160MHzD3)
    #define RBFS_uCPackage             RBFS_uCPackage_QFP144
  #elif (RBFS_uC == RBFS_uC_Renesas160MHzD3onD3ED)
    #define RBFS_uCPackage             RBFS_uCPackage_BGA156
  #elif (RBFS_uC == RBFS_uC_Renesas160MHzD3onD5ED)
    #define RBFS_uCPackage             RBFS_uCPackage_BGA292
  #elif (RBFS_uC == RBFS_uC_Renesas240MHzD3)
    #define RBFS_uCPackage             RBFS_uCPackage_BGA292
  #elif (RBFS_uC == RBFS_uC_Renesas240MHzD3onD3ED)
    #define RBFS_uCPackage             RBFS_uCPackage_BGA156
  #elif (RBFS_uC == RBFS_uC_Renesas240MHzD3onD5ED)
    #define RBFS_uCPackage             RBFS_uCPackage_BGA292
  #elif (RBFS_uC == RBFS_uC_RenesasM2)
    #define RBFS_uCPackage             RBFS_uCPackage_QFP144
  #elif (RBFS_uC == RBFS_uC_RenesasM2onM6ED)
    #define RBFS_uCPackage             RBFS_uCPackage_BGA292
  #endif
#endif



/**************************************************************************************/
/***************        Generic Configuration (and defaultings!)        ***************/
/**************************************************************************************/

#define RB_STACK0_SIZE_FSW (10000)
#define RB_STACK1_SIZE_FSW (10000)

#define RBFS_TaskSchemeExtension              RBFS_TaskSchemeExtension_None
#define RBFS_TPSWCapsule                      RBFS_TPSWCapsule_OFF
#define RBFS_pTSWSupport                      RBFS_pTSWSupport_OFF
#define RBFS_TPSWTestsuite                    RBFS_TPSWTestsuite_OFF
#define RBFS_SysOverwriteEBASE                RBFS_SysOverwriteEBASE_OFF
#define RBFS_TraceMeasurement                 RBFS_TraceMeasurement_RuntimeConfigurable
#define RBFS_BackupRAMLayout                  RBFS_BackupRAMLayout_Legacy


#ifndef RBFS_HexBlockBuild
  #define RBFS_HexBlockBuild                    RBFS_HexBlockBuild_APPLICATION
#endif

#ifndef RBFS_BootblockEnableAsicSupport
  #define RBFS_BootblockEnableAsicSupport RBFS_BootblockEnableAsicSupport_OFF
#endif

#define RBFS_HexBlockConfig                   RBFS_HexBlockConfig_Customized

#define RBFS_FlexraySupport                   RBFS_FlexraySupport_Yes
#define RBFS_FlxrTaskSync                     RBFS_FlxrTaskSync_ON
#define RBFS_TaskSync                         RBFS_TaskSync_ON
#define RBFS_BackdoorBootblock                RBFS_BackdoorBootblock_YES

#define RBFS_SYSDebugFeatures                 RBFS_SYSDebugFeatures_ON

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
  #define RBFS_Compiler                         RBFS_Compiler_GHS2018
#else
  #define RBFS_Compiler                         RBFS_Compiler_GHS2021
#endif
#define RBFS_CompilationLanguage              RBFS_CompilationLanguage_PureC

#define RBFS_CodeFlashMemoryMode              RBFS_CodeFlashMemoryMode_SingleMap

#define RBFS_TPSWSVPRestrictions            RBFS_TPSWSVPRestrictions_ON


#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  #define RBFS_FOTA                             RBFS_FOTA_OFF
#else // all other uCs support FOTA Premium
  #define RBFS_FOTA                             RBFS_FOTA_PREMIUM
#endif

#define RBFS_DataFlashSupport RBFS_DataFlashSupport_No

#define RBFS_HSWSimulation RBFS_HSWSimulation_OFF

#define RBFS_Ethernet RBFS_Ethernet_Disabled

#if(  (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) \
  ||  (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2) \
  ||  (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) \
  || ((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4) && (RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Unsupported)) \
  || ((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5) && (RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Unsupported)) \
   )
  #define RBFS_ReprogDriverSupport RBFS_ReprogDriverSupport_ON
#elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) ||  (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) || (RBFS_uCFamily == RBFS_uCFamily_STMStellar) )
  #define RBFS_ReprogDriverSupport RBFS_ReprogDriverSupport_OFF
#else
  #define RBFS_ReprogDriverSupport RBFS_ReprogDriverSupport_ON
#endif

#if( RBFS_MCORE == RBFS_MCORE_ON )
  #define RBFS_CANCommunicationDuringInitTask RBFS_CANCommunicationDuringInitTask_Enabled
#else
  #define RBFS_CANCommunicationDuringInitTask RBFS_CANCommunicationDuringInitTask_Disabled
#endif


#define RBFS_CpuClockRestriction RBFS_CpuClockRestriction_Default

#define RBFS_uCWatchdog RBFS_uCWatchdog_Enabled

#define RBFS_SysResettableSlackTimesSupport RBFS_SysResettableSlackTimesSupport_ON

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  #define RBFS_TriggerTimerSupport RBFS_TriggerTimerSupport_On
#else
  #define RBFS_TriggerTimerSupport RBFS_TriggerTimerSupport_Off
#endif

#define RBFS_RAMLayoutFragmentation RBFS_RAMLayoutFragmentation_Default

/*  reduce some of the variance  */
#if (RBFS_uC == RBFS_uC_RenesasD5)
  #define RBFS_SysHsmSharedGRAMsize            RBFS_SysHsmSharedGRAMsize_32K
  #define RBFS_SysHSMsharedGRAM                RBFS_SysHSMsharedGRAM_Restricted
#elif( RBFS_uC == RBFS_uC_RenesasD7onD7ED )
  #define RBFS_SysHsmSharedGRAMsize            RBFS_SysHsmSharedGRAMsize_32K
  #define RBFS_SysHSMsharedGRAM                RBFS_SysHSMsharedGRAM_Restricted
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  #define RBFS_SysHsmSharedGRAMsize            RBFS_SysHsmSharedGRAMsize_32K
  #define RBFS_SysHSMsharedGRAM                RBFS_SysHSMsharedGRAM_Restricted
#else
  #define RBFS_SysHsmSharedGRAMsize            RBFS_SysHsmSharedGRAMsize_16K
  #define RBFS_SysHSMsharedGRAM                RBFS_SysHSMsharedGRAM_Host
#endif

#if (RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Unsupported)
  #undef RBFS_SysHsmSharedGRAMsize
  #define RBFS_SysHsmSharedGRAMsize       RBFS_SysHsmSharedGRAMsize_0K
#endif




#if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) \
  || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4) \
  || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5) )
  #define RBFS_SysEthSharedGRAMsize             RBFS_SysEthSharedGRAMsize_64K
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  #define RBFS_SysEthSharedGRAMsize             RBFS_SysEthSharedGRAMsize_64K
#else
  #define RBFS_SysEthSharedGRAMsize             RBFS_SysEthSharedGRAMsize_0K
#endif

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  #define RBFS_DataFlashECC                     RBFS_DataFlashECC_Disabled
#else
  #define RBFS_DataFlashECC                     RBFS_DataFlashECC_Enabled
#endif

#define RBFS_HydrActSystem                      RBFS_HydrActSystem_ESP

#define RBFS_HswRecoveryReset                   RBFS_HswRecoveryReset_Enabled

#define RBFS_CyberSecurityBoot                  RBFS_CyberSecurityBoot_Secure

#define RBFS_Bootblock                          RBFS_Bootblock_Enabled

#define RBFS_Task0p5ms                          RBFS_Task0p5ms_ON

#define RBFS_HswCompilerRuntimeChecks           RBFS_HswCompilerRuntimeChecks_On

#define __RB_MTC_MAJOR_VERSION__ (10)
#define __RB_MTC_MINOR_VERSION__ (9)




#define RBFS_DownloadModuleSupport              RBFS_DownloadModuleSupport_YES

#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
    #define RBFS_RestrictedExclusiveGRAMsize      RBFS_RestrictedExclusiveGRAMsize_32K
    #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
    #if(   RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2 )
        #define RBFS_RestrictedExclusiveGRAMsize      RBFS_RestrictedExclusiveGRAMsize_64K
    #elif( RBFS_TargetDevice == RBFS_TargetDevice_RenesasM3 )
        #define RBFS_RestrictedExclusiveGRAMsize      RBFS_RestrictedExclusiveGRAMsize_128K
    #elif( RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6 )
        #define RBFS_RestrictedExclusiveGRAMsize      RBFS_RestrictedExclusiveGRAMsize_256K
    #endif
    #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
    #if(   RBFS_TargetDevice == RBFS_TargetDevice_RenesasK0 )
        #define RBFS_RestrictedExclusiveGRAMsize      RBFS_RestrictedExclusiveGRAMsize_16K
    #elif( RBFS_TargetDevice == RBFS_TargetDevice_RenesasK1 )
        #define RBFS_RestrictedExclusiveGRAMsize      RBFS_RestrictedExclusiveGRAMsize_32K
    #endif
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    #define RBFS_RestrictedExclusiveGRAMsize RBFS_RestrictedExclusiveGRAMsize_0K
    #endif
#endif


#ifndef RBFS_RestrictedExclusiveGRAMsize
  #define RBFS_RestrictedExclusiveGRAMsize RBFS_RestrictedExclusiveGRAMsize_0K
#endif


#define RBFS_TRBSYSGuardVariance_supported     1
#define RBFS_TRBSYSGuardVariance_unsupported   2

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  || (RBFS_uCFamily == RBFS_uCFamily_STMStellar) )
  #if( (RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_32K) && (RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_16K) )
    #define RBFS_TRBSYSGuardVariance    RBFS_TRBSYSGuardVariance_unsupported
  #elif( (RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_32K) && \
          ( (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_32K) || (RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_96K) ) \
      )
    #define RBFS_TRBSYSGuardVariance    RBFS_TRBSYSGuardVariance_unsupported
  #elif( (RBFS_RAMLayoutFragmentation == RBFS_RAMLayoutFragmentation_GRAMOptimizedForBLDR) \
      && ( (RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_32K) || (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K) || (RBFS_SysHSMsharedGRAM != RBFS_SysHSMsharedGRAM_Host) ) \
      )
    #define RBFS_TRBSYSGuardVariance    RBFS_TRBSYSGuardVariance_unsupported
  #else
    #define RBFS_TRBSYSGuardVariance    RBFS_TRBSYSGuardVariance_supported
  #endif
#elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  #define RBFS_TRBSYSGuardVariance    RBFS_TRBSYSGuardVariance_supported
#endif

#if( (RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_0K) && (RBFS_SysHSMsharedGRAM != RBFS_SysHSMsharedGRAM_Restricted))
    #define RBFS_T1FlexSupport                      RBFS_T1FlexSupport_Yes
#else
    #define RBFS_T1FlexSupport                      RBFS_T1FlexSupport_No
#endif

#define RBFS_SysUnittestSimulationModel RBFS_SysUnittestSimulationModel_ON




#define RBSYS_ENTER_COMMON_LOCK           RBSYS_EnterCommonLock
#define RBSYS_EXIT_COMMON_LOCK            RBSYS_ExitCommonLock
#define RBSYS_ENTER_CORELOCAL_INTLOCK     RBSYS_EnterCorelocalIntlock
#define RBSYS_EXIT_CORELOCAL_INTLOCK      RBSYS_ExitCorelocalIntlock

#endif