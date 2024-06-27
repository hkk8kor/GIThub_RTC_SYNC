#ifndef RBSYS_CONFIG_H__
#define RBSYS_CONFIG_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Configuration of RBSYS
 *
 * Provides configuration of parameters, constants and function switches for RBSYS.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


/* used interfaces */
#include "RBCMHSW_Global.h"
#include "RB_Config.h"                          /* for RBFS_Bootblock, RBFS_HexBlockBuild, RBFS_FlexraySupport, RBFS_FlxrTaskSync, RBFS_RTMOWINRTMMEASURE, stack size */
#include "RBHSW_Config.h"                       /* for RBFS_BackdoorBootblock */
#include "RBSYS_ConfigElements.h"
#include "RBCMHSW_SWDebugSupport.h"             /* for RBFS_SYSDebugFeatures */
#include "RBCMHSW_Locks.h"                      /* for RBSYS_*LOCK */
#include "RBCMHSW_CoreInfo.h"                   /* for RBFS_MCORE, RB_NUM_CORES */
#include "RBCMHSW_TaskSchemeAddOn.h"            /* for RBFS_Task0p5ms */
#include "RBCMHSW_MemoryInfo.h"                 /* for RBFS_RenesasP1xGRAM, ... */
#include "RBCMHSW_uCSafety.h"                   /* for RBFS_DataFlashECC */
#include <assert.h>                             /* for static_assert, assert */

#include "RBSYS_DefaultElements.h"              /* SEQUENCE: must be the last include for defaulting of RBSYS only used switch settings */




/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_BUILDTYPE,
                          RBFS_BUILDTYPE_RELEASE,
                          RBFS_BUILDTYPE_DEVELOP);
RB_ASSERT_SWITCH_SETTINGS(RBFS_Bootblock,
                          RBFS_Bootblock_Enabled,
                          RBFS_Bootblock_Disabled);
RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);
RB_ASSERT_SWITCH_SETTINGS(RBFS_FlexraySupport,
                          RBFS_FlexraySupport_Yes,
                          RBFS_FlexraySupport_No);
RB_ASSERT_SWITCH_SETTINGS(RBFS_Ethernet,
                          RBFS_Ethernet_Enabled,
                          RBFS_Ethernet_Disabled);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEthernetSupport,
                          RBFS_SysEthernetSupport_ON,
                          RBFS_SysEthernetSupport_OFF);
RB_ASSERT_SWITCH_SETTINGS(RBFS_Task0p5ms,
                          RBFS_Task0p5ms_ON,
                          RBFS_Task0p5ms_OFF);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWTestsuite,
                          RBFS_TPSWTestsuite_ON,
                          RBFS_TPSWTestsuite_OFF);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SYSDebugFeatures,
                          RBFS_SYSDebugFeatures_ON,
                          RBFS_SYSDebugFeatures_OFF);
RB_ASSERT_SWITCH_SETTINGS(RBFS_HardwareSecurityModule,
                          RBFS_HardwareSecurityModule_Supported,
                          RBFS_HardwareSecurityModule_Unsupported);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysHsmSharedGRAMsize,
                          RBFS_SysHsmSharedGRAMsize_0K,
                          RBFS_SysHsmSharedGRAMsize_16K,
                          RBFS_SysHsmSharedGRAMsize_32K);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysHSMsharedGRAM,
                          RBFS_SysHSMsharedGRAM_Host,
                          RBFS_SysHSMsharedGRAM_Restricted);
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_ON,
                          RBFS_MCORE_OFF);
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
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEthSharedGRAMsize,
                          RBFS_SysEthSharedGRAMsize_0K,
                          RBFS_SysEthSharedGRAMsize_32K,
                          RBFS_SysEthSharedGRAMsize_64K,
                          RBFS_SysEthSharedGRAMsize_96K,
                          RBFS_SysEthSharedGRAMsize_128K);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSchemeExtension,
                          RBFS_TaskSchemeExtension_None,
                          RBFS_TaskSchemeExtension_VMPS,
                          RBFS_TaskSchemeExtension_HostCore0GuestCore1,
                          RBFS_TaskSchemeExtension_AB15);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TriggerTimerSupport,
                          RBFS_TriggerTimerSupport_On,
                          RBFS_TriggerTimerSupport_Off);
RB_ASSERT_SWITCH_SETTINGS(RBFS_RestrictedExclusiveGRAMsize,
                          RBFS_RestrictedExclusiveGRAMsize_0K,
                          RBFS_RestrictedExclusiveGRAMsize_16K,
                          RBFS_RestrictedExclusiveGRAMsize_32K,
                          RBFS_RestrictedExclusiveGRAMsize_64K,
                          RBFS_RestrictedExclusiveGRAMsize_128K,
                          RBFS_RestrictedExclusiveGRAMsize_256K);
RB_ASSERT_SWITCH_SETTINGS(RBFS_Compiler,
                          RBFS_Compiler_GHS,
                          RBFS_Compiler_GCC4HSim,
                          RBFS_Compiler_GCC4BSWSim,
                          RBFS_Compiler_GHS2018,
                          RBFS_Compiler_GHS2021,
                          RBFS_Compiler_GCC4,
                          RBFS_Compiler_TDM5);
RB_ASSERT_SWITCH_SETTINGS(RBFS_HSWSimulation,
                          RBFS_HSWSimulation_OFF,
                          RBFS_HSWSimulation_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_T1FlexSupport,
                          RBFS_T1FlexSupport_No,
                          RBFS_T1FlexSupport_Yes);
RB_ASSERT_SWITCH_SETTINGS(RBFS_DownloadModuleSupport,
                          RBFS_DownloadModuleSupport_NO,
                          RBFS_DownloadModuleSupport_YES);
RB_ASSERT_SWITCH_SETTINGS(RBFS_EmulationDevice,
                          RBFS_EmulationDevice_None,
                          RBFS_EmulationDevice_RenesasD3ED,
                          RBFS_EmulationDevice_RenesasD5ED,
                          RBFS_EmulationDevice_RenesasD7ED,
                          RBFS_EmulationDevice_RenesasM6ED,
                          RBFS_EmulationDevice_RenesasK3ED,
                          RBFS_EmulationDevice_STMP3ED,
                          RBFS_EmulationDevice_STMP7ED);
RB_ASSERT_SWITCH_SETTINGS(RBFS_ReprogDriverSupport,
                          RBFS_ReprogDriverSupport_ON,
                          RBFS_ReprogDriverSupport_OFF);
RB_ASSERT_SWITCH_SETTINGS(RBFS_CANCommunicationDuringInitTask,
                          RBFS_CANCommunicationDuringInitTask_Enabled,
                          RBFS_CANCommunicationDuringInitTask_Disabled);
RB_ASSERT_SWITCH_SETTINGS(RBFS_FlxrTaskSync,
                          RBFS_FlxrTaskSync_ON,
                          RBFS_FlxrTaskSync_OFF);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSync,
                          RBFS_TaskSync_ON,
                          RBFS_TaskSync_OFF);
RB_ASSERT_SWITCH_SETTINGS(RBFS_HswCompilerRuntimeChecks,
                          RBFS_HswCompilerRuntimeChecks_On,
                          RBFS_HswCompilerRuntimeChecks_Off);
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysUnittestSimulationModel,
                          RBFS_SysUnittestSimulationModel_ON,
                          RBFS_SysUnittestSimulationModel_OFF);



/* typedef for processes: void-void function call */
typedef void (*PRC_PTR)(void);



/******************************************************************************************/
/*                                DEBUG features                                          */
/******************************************************************************************/

/** Debug feature to check unbalanced locks after each process */
#define RBFS_SysDebugUnbalancedLock_ON   1
/** Debug feature must be switched off for series builds (still active on task granularity) */
#define RBFS_SysDebugUnbalancedLock_OFF  2

/* MTC introduced a define to distinguish between development and release phase -
   derive RBSYS related function switch setting from generic project setting */
#if (RBFS_SYSDebugFeatures == RBFS_SYSDebugFeatures_OFF)
  #define RBFS_SysDebugUnbalancedLock   RBFS_SysDebugUnbalancedLock_OFF
#else
  #define RBFS_SysDebugUnbalancedLock   RBFS_SysDebugUnbalancedLock_ON
#endif


/** Debug features to store for each task the longest running process using code instrumentation
    from rba_Runtime and prepare data for MM6 (see measurement variable RBSYS_DebugInfo_MaxProcPerTask) */
#define RBFS_SysDebugProcRuntime_ON   1
/** Debug features must be switched off for series builds - requires additional (critical) runtime */
#define RBFS_SysDebugProcRuntime_OFF  2

#define RBFS_SysDebugProcRuntime   RBFS_SysDebugProcRuntime_OFF






/******************************************************************************************/
/*                                SERIES features                                         */
/******************************************************************************************/

/** Configuration of Base Control task */
#define C_BaseCtrlTaskms_UL   5



/** Map SYS used lock to common available SYS lock */
#define RBSYS_SchM_Enter_GlobLock     RBSYS_ENTER_COMMON_LOCK
/** Map SYS used lock to common available SYS lock */
#define RBSYS_SchM_Exit_GlobLock      RBSYS_EXIT_COMMON_LOCK



/** Map SYS used core-specific lock to common available SYS lock */
#define RBSYS_SchM_Enter_CoreLocalLock     RBSYS_ENTER_CORELOCAL_INTLOCK
/** Map SYS used core-specific lock to common available SYS lock */
#define RBSYS_SchM_Exit_CoreLocalLock      RBSYS_EXIT_CORELOCAL_INTLOCK



/** project without bootblock support */
#define RBFS_SysBootblockSupport_OFF  1
/** project with bootblock support */
#define RBFS_SysBootblockSupport_ON   2

/** derive RBSYS related function switch setting from generic project setting */
#if (RBFS_Bootblock == RBFS_Bootblock_Enabled)
  #define RBFS_SysBootblockSupport   RBFS_SysBootblockSupport_ON
#else
  #define RBFS_SysBootblockSupport   RBFS_SysBootblockSupport_OFF
#endif



/** current build is a bootblock build */
#define RBFS_SysBootblockBuild_Active      1
/** current build is no bootblock build */
#define RBFS_SysBootblockBuild_NotActive   2

#if (  (RBFS_HexBlockBuild == RBFS_HexBlockBuild_BOOTMANAGER)   \
    || (RBFS_HexBlockBuild == RBFS_HexBlockBuild_BOOTLOADER)    \
    || (RBFS_HexBlockBuild == RBFS_HexBlockBuild_RBBOOTLOADER)  \
    )
  #define RBFS_SysBootblockBuild   RBFS_SysBootblockBuild_Active
#else
  #define RBFS_SysBootblockBuild   RBFS_SysBootblockBuild_NotActive
#endif



/** RBSYS does not provide a FlexRay Task */
#define RBFS_SysFlxrTask_OFF  1
/** RBSYS has to provide a FlexRay Task */
#define RBFS_SysFlxrTask_ON   2

/** derive RBSYS related function switch setting from generic project setting */
#if (RBFS_FlexraySupport == RBFS_FlexraySupport_Yes)
  #define RBFS_SysFlxrTask       RBFS_SysFlxrTask_ON
#else
  #define RBFS_SysFlxrTask       RBFS_SysFlxrTask_OFF
#endif




/** 0.5ms task not used */
#define RBFS_SysTask0p5ms_OFF  1
/** 0.5ms task used*/
#define RBFS_SysTask0p5ms_ON   2

/** derive RBSYS related function switch setting from generic project setting */
#if( RBFS_Task0p5ms == RBFS_Task0p5ms_OFF )
  #define RBFS_SysTask0p5ms   RBFS_SysTask0p5ms_OFF
#else
  #define RBFS_SysTask0p5ms   RBFS_SysTask0p5ms_ON
#endif


/** Maximum task scheme adjust value in percent - adaptation is done in the highest prio task!
    Example 2% means +/- 20 us adaptation every 1ms task */
#define RBSYS_TASKSCHEME_ADJUST_MAX_PERCENT   (2.0)


#if (RBFS_HswCompilerRuntimeChecks == RBFS_HswCompilerRuntimeChecks_On)
  /** Because with activated runtime checks code is injected by the compiler, the allowed locktime must be increased **/
  #define RBSYS_MAX_LOCKTIME_US  100
#else
  /** maximum allowed lock time in Gen9.3 is 50us, therefore monitored for 70us */
  #define RBSYS_MAX_LOCKTIME_US  70
#endif

/** Monitoring of maximum lock time is enabled */
#define RBFS_LockTimeMonitoring_Enabled       1
/** Monitoring of maximum lock time is disabled */
#define RBFS_LockTimeMonitoring_Disabled      2

#define RBFS_LockTimeMonitoring RBFS_LockTimeMonitoring_Enabled


/** APIs for Exclusive SPID are available */
#define RBFS_SysExclusiveSPID_Used    1
/** APIs for Exclusive SPID are unavailable */
#define RBFS_SysExclusiveSPID_NotUsed 2

#if( (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K) || (RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted) )
  #define RBFS_SysExclusiveSPID RBFS_SysExclusiveSPID_Used
#else
  #define RBFS_SysExclusiveSPID RBFS_SysExclusiveSPID_NotUsed
#endif

/*todo: provide separate defines for different architectures, e.g. _TargetRH850 */
/* RBSYS is used inside target ECU build */
#define RBFS_SysEnvironment_Target      1
/* RBSYS is used inside Simulation (x86 Simulation, x86 Unittest, x86 Componenttest) */
#define RBFS_SysEnvironment_Simulation  2

#if( (RBFS_SysUnittestSimulationModel == RBFS_SysUnittestSimulationModel_ON) || (RBFS_HSWSimulation == RBFS_HSWSimulation_ON) )
  #define RBFS_SysEnvironment RBFS_SysEnvironment_Simulation
#else
  #define RBFS_SysEnvironment RBFS_SysEnvironment_Target
#endif



/******************************************************************************************/
/*                                Sanity Checks                                           */
/******************************************************************************************/
#if ( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) \
   && (RBFS_HSWSimulation == RBFS_HSWSimulation_OFF) \
   && (RBFS_Compiler == RBFS_Compiler_GHS) \
    )
  #error ("Renesas U2A devices are not supported with GHS compiler 2015")
#endif

#if ( (RBFS_uCFamily == RBFS_uCFamily_STMStellar) \
   && (RBFS_HSWSimulation == RBFS_HSWSimulation_OFF) \
   && (RBFS_Compiler != RBFS_Compiler_GHS2021) \
    )
  #error ("STM Stellar devices require GHS compiler 2021")
#endif

/* NO_TOOL_SCAN */
/* REASON: Sanity check */
#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  #if( (__RB_MTC_MAJOR_VERSION__ < 10) || ((__RB_MTC_MAJOR_VERSION__ == 10) && (__RB_MTC_MINOR_VERSION__ < 7)) )
    /// For MTC < 10 and for MTC 10 with Minor Version < 7 -> U2A is not supported
    #error "MTC >= MTC10.7 is needed to build projects for Renesas U2A"
  #endif
#endif
/* NO_TOOL_SCAN_END */

#if ( (RBFS_BUILDTYPE == RBFS_BUILDTYPE_RELEASE) \
   && (RBFS_SysDebugUnbalancedLock == RBFS_SysDebugUnbalancedLock_ON) )
  #error ("Debug feature not allowed for series build!")
#endif

#if ( (RBFS_BUILDTYPE == RBFS_BUILDTYPE_RELEASE) \
   && (RBFS_SysDebugProcRuntime == RBFS_SysDebugProcRuntime_ON) )
  #error ("Debug feature not allowed for series build!")
#endif

#if ( (RBFS_BUILDTYPE == RBFS_BUILDTYPE_RELEASE) \
   && (RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON) )
  #error ("TPSW Testsuite not allowed for series build!")
#endif

#if ( (RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Supported) \
   && (RBFS_SysHsmSharedGRAMsize == RBFS_SysHsmSharedGRAMsize_0K) )
  #error ("HSM needs shared GRAM (RBFS_SysHsmSharedGRAMsize_0K not allowed)")
#endif

#if ( (RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Unsupported) \
   && (RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_0K) )
  #error ("Shared GRAM for HSM must be 0K if RBFS_HardwareSecurityModule_Unsupported (RBFS_SysHsmSharedGRAMsize_0K)")
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  #if( (RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_0K) \
    && (RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_32K)  )
    static_assert(FALSE, "RBFS_SysHsmSharedGRAMsize must be configured to 0K or 32K on U2C devices")
  #endif
#endif

#if ( (RBFS_SysEthSharedGRAMsize != RBFS_SysEthSharedGRAMsize_0K) \
   && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD3) \
   && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD4) \
   && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD5) \
   && (RBFS_TargetDevice != RBFS_TargetDevice_STMP6) \
   )
  #error ("SysEthernetSupport (i.e. not RBFS_SysEthSharedGRAMsize_0K) only allowed for target devices D3, D4, D5, P6")
#endif

#if(RBFS_Ethernet == RBFS_Ethernet_Enabled)
  #if( (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD3) \
    && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD4) \
    && (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD5) )
    #error ("Ethernet is only supported for D3, D4, D5")
  #endif
#endif


#if ( (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS) \
   && (RBFS_HSWSimulation == RBFS_HSWSimulation_OFF) \
   && (RBFS_Compiler != RBFS_Compiler_GHS2018) )
  #error ("VMPS Operating System is supported for GHS 2018.1.5 only")
#endif

#if ( (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS) \
   && (RBFS_MCORE != RBFS_MCORE_ON) )
  #error ("VMPS task scheme extension only supported on MultiCore")
#endif

#if ( (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS) \
   && (RBFS_uCFamily != RBFS_uCFamily_RenesasP1x) )
  #error ("VMPS task scheme extension only supported on Renesas P1x devices")
#endif

#if ( (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1) \
   && (RBFS_HSWSimulation == RBFS_HSWSimulation_OFF) \
   && (RBFS_Compiler != RBFS_Compiler_GHS2018) \
   && (RBFS_Compiler != RBFS_Compiler_GHS2021) )
  #error ("HostCore0GuestCore1 Operating System is only supported for GHS 2018.1.5 and 2021.1.5")
#endif

#if ( (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1) \
   && (RBFS_uCFamily != RBFS_uCFamily_RenesasU2A) )
  #error ("HostCore0GuestCore1 task scheme extension only supported on Renesas U2A devices")
#endif

#if ( (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15) \
   && (RBFS_HSWSimulation == RBFS_HSWSimulation_OFF) \
   && (RBFS_Compiler != RBFS_Compiler_GHS2021) )
  #error ("AB15 Operating System is supported for GHS 2021.1.5 only")
#endif

#if ( (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15) \
   && (RBFS_uCFamily != RBFS_uCFamily_RenesasP1x) )
  #error ("AB15 task scheme extension only supported on Renesas P1x devices")
#endif

#if ( (RBFS_SysEthernetSupport == RBFS_SysEthernetSupport_ON) \
   && (RBFS_uCFamily != RBFS_uCFamily_RenesasP1x) )
  #error ("RBSYS Ethernet support is available till now only on Renesas P1x devices")
#endif

#if( (RBFS_TriggerTimerSupport == RBFS_TriggerTimerSupport_On) && (RBFS_uCFamily != RBFS_uCFamily_RenesasP1x) )
  static_assert(FALSE, "RBFS_TriggerTimerSupport_On is only supported for P1x device family")
#endif

#if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2) )
  #if( (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K) \
    && (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_64K) )
    static_assert(FALSE, "RBFS_RestrictedExclusiveGRAMsize must be configured to 0K or 64K for M2")
  #endif
#endif

#if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM3) )
  #if( (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K) \
    && (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_128K) )
    static_assert(FALSE, "RBFS_RestrictedExclusiveGRAMsize must be configured to 0K or 128K for M3")
  #endif
#endif

#if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) \
  || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6) )
  #if( (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K) \
    && (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_256K) )
    static_assert(FALSE, "RBFS_RestrictedExclusiveGRAMsize must be configured to 0K or 256K for M6")
  #endif
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  #if( (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K) \
    && (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_16K) \
    && (RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_32K) )
    static_assert(FALSE, "RBFS_RestrictedExclusiveGRAMsize must be configured to 0K, 16K or 32K on U2C devices")
  #endif
#endif

#if( ((RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_256K) || (RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_128K) || (RBFS_RestrictedExclusiveGRAMsize == RBFS_RestrictedExclusiveGRAMsize_64K)) \
  && (RBFS_uCFamily != RBFS_uCFamily_RenesasU2A) )
  static_assert(FALSE, "RBFS_RestrictedExclusiveGRAMsize may not be configured to 64K/128K/256K for other controllers than M2/M3/M6")
#endif

#if( RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3 )
  #if( RBFS_SysEthSharedGRAMsize == RBFS_SysEthSharedGRAMsize_128K )
    static_assert(FALSE, "Ethernet Shared GRAM cannot be configured to 128K due to limited amount of GRAM on D3")
  #endif
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  #if( RBFS_SysEthSharedGRAMsize != RBFS_SysEthSharedGRAMsize_0K )
    static_assert(FALSE, "SysEthSharedGRAMsize is not available for U2A devices. Always configure RBFS_SysEthSharedGRAMsize_0K.")
  #endif
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  #if( (RBFS_SysEthSharedGRAMsize != RBFS_SysEthSharedGRAMsize_0K) \
    && (RBFS_SysEthSharedGRAMsize != RBFS_SysEthSharedGRAMsize_32K) )
    static_assert(FALSE, "RBFS_SysEthSharedGRAMsize must be configured to 0K or 32K on U2C devices.")
  #endif
#endif

#if( RBFS_SysExclusiveSPID == RBFS_SysExclusiveSPID_Used )
  #if( RBFS_T1FlexSupport == RBFS_T1FlexSupport_Yes )
    static_assert(FALSE, "Gliwa T1.FLEX cannot be used if Exclusive SPID is used, because Debug Exception handler cannot handle a change from Restricted SPID to SAFE SPID then.")
  #endif
#endif

#if( (RBFS_BUILDTYPE == RBFS_BUILDTYPE_RELEASE) \
  && (RBFS_ReprogDriverSupport == RBFS_ReprogDriverSupport_OFF) \
  && (RBFS_Bootblock == RBFS_Bootblock_Disabled ) \
  && (RBFS_EmulationDevice == RBFS_EmulationDevice_None) )
  static_assert(FALSE,"No bootblock and no reprogdriver leaves no way to reprog device");
#endif

#if( (RBFS_DownloadModuleSupport == RBFS_DownloadModuleSupport_NO) && (RBFS_ReprogDriverSupport == RBFS_ReprogDriverSupport_ON) )
  static_assert(FALSE,"RBFS_ReprogDriverSupport can only be enabled if RBFS_DownloadModuleSupport_YES is configured");
#endif

/* The following sanity check is only needed as long as RBFS_ReprogDriverSupport can be overwritten */
#if( (RBFS_uCFamily != RBFS_uCFamily_RenesasP1x) && (RBFS_ReprogDriverSupport == RBFS_ReprogDriverSupport_ON) )
  static_assert(FALSE,"RBFS_ReprogDriverSupport can only be enabled for Renesas P1x");
#endif




#ifdef RBFS_RAMLayoutFragmentation
  RB_ASSERT_SWITCH_SETTINGS(RBFS_RAMLayoutFragmentation,
                            RBFS_RAMLayoutFragmentation_Default,
                            RBFS_RAMLayoutFragmentation_GRAMOptimizedForBLDR);

  #if( (RBFS_TargetDevice != RBFS_TargetDevice_RenesasD3) && (RBFS_RAMLayoutFragmentation != RBFS_RAMLayoutFragmentation_Default) )
    static_assert(FALSE, "Special Fragmentation of RAM Layout is (currently) only supported for Renesas D3. Configure _Default for your TargetDevice!");
  #endif

  #if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) && ( RBFS_RAMLayoutFragmentation == RBFS_RAMLayoutFragmentation_GRAMOptimizedForBLDR ) )
    #if( RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Supported )
      #if( RBFS_SysHsmSharedGRAMsize != RBFS_SysHsmSharedGRAMsize_32K )
        static_assert(FALSE, "Configure RBFS_SysHsmSharedGRAMsize to 32K for D3 in case of RBFS_RAMLayoutFragmentation_GRAMOptimizedForBLDR.");
      #endif
      #if( (RBFS_SysHSMsharedGRAM == RBFS_SysHSMsharedGRAM_Restricted) )
        static_assert(FALSE, "Restricted SPID Features are not supported for D3 in case of RBFS_RAMLayoutFragmentation_GRAMOptimizedForBLDR.");
      #endif
    #endif

    #if( RBFS_RestrictedExclusiveGRAMsize != RBFS_RestrictedExclusiveGRAMsize_0K )
      static_assert(FALSE, "Restricted SPID Features are not supported for D3 in case of RBFS_RAMLayoutFragmentation_GRAMOptimizedForBLDR.");
    #endif
  #endif

#endif

#if( RBFS_SysExclusiveSPID == RBFS_SysExclusiveSPID_Used )
  #if( RBFS_HexBlockBuild != RBFS_HexBlockBuild_APPLICATION )
    static_assert(FALSE, "RBSYS Exclusive SPID Features are only supported within Application");
  #endif
#endif

#if( RBFS_CANCommunicationDuringInitTask == RBFS_CANCommunicationDuringInitTask_Enabled )
  #if( RBFS_MCORE != RBFS_MCORE_ON )
    static_assert(FALSE, "Network Communication during InitTask requires >= 2 Cores running in parallel");
  #endif
#endif

#ifdef RBFS_FlxrTaskSync
  #if (  (RBFS_FlexraySupport == RBFS_FlexraySupport_No) \
      && (RBFS_FlxrTaskSync == RBFS_FlxrTaskSync_ON) \
      )
    #error ("Invalid Flexray switch setting combination!")
    // Hint: If you have problems with this sanity check, please verify availability of EbOS DefectFix 66195!
  #endif
  #if (  (RBFS_FlxrTaskSync == RBFS_FlxrTaskSync_ON) \
      && (RBFS_TaskSync == RBFS_TaskSync_OFF) \
      )
    #error ("Invalid Task Sync switch setting combination!")
  #endif
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
