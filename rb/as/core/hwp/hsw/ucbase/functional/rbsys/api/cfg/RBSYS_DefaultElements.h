#ifndef RBSYS_DEFAULTELEMENTS_H__
#define RBSYS_DEFAULTELEMENTS_H__

/**
 * @file
 * @brief Provides RBSYS specific default switch settings, which could be overwritten by project configuration
 *
 * @note "RBSYS_DefaultElements.h" is only allowed to be included within "RBSYS_Config.h"
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


/* used interfaces */
#include "RBCMHSW_Global.h"
#include "RB_Config.h"
#include "RBSYS_ConfigElements.h"
// Include the defaultings that were placed in another file for bcfg (pre compiler time) compatibility
#include "RBSYS_DefaultElementsPure.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_BUILDTYPE,
                          RBFS_BUILDTYPE_RELEASE,
                          RBFS_BUILDTYPE_DEVELOP);
RB_ASSERT_SWITCH_SETTINGS(RBFS_FlexraySupport,
                          RBFS_FlexraySupport_Yes,
                          RBFS_FlexraySupport_No);
RB_ASSERT_SWITCH_SETTINGS(RBFS_pTSWSupport,
                          RBFS_pTSWSupport_ON,
                          RBFS_pTSWSupport_OFF);
RB_ASSERT_SWITCH_SETTINGS(RBFS_FOTA,
                          RBFS_FOTA_OFF,
                          RBFS_FOTA_BASE,
                          RBFS_FOTA_BASEPLUS,
                          RBFS_FOTA_ENHANCED,
                          RBFS_FOTA_PREMIUM);
RB_ASSERT_SWITCH_SETTINGS(RBFS_CyberSecurityBoot,
                          RBFS_CyberSecurityBoot_NonTrusted,
                          RBFS_CyberSecurityBoot_Trusted,
                          RBFS_CyberSecurityBoot_Gracious,
                          RBFS_CyberSecurityBoot_Staged,
                          RBFS_CyberSecurityBoot_Concurrent,
                          RBFS_CyberSecurityBoot_Secure);
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);
RB_ASSERT_SWITCH_SETTINGS(RBFS_Compiler,
                          RBFS_Compiler_GHS,
                          RBFS_Compiler_GCC4HSim,
                          RBFS_Compiler_GCC4BSWSim,
                          RBFS_Compiler_GHS2018,
                          RBFS_Compiler_GHS2021,
                          RBFS_Compiler_GCC4,
                          RBFS_Compiler_TDM5);
RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

/*
RB_ASSERT_SWITCH_SETTINGS(RBFS_HydrActSystem, ...)
RB_ASSERT_SWITCH_SETTINGS(RBFS_WssMounted, ...)

RBSYS is not really interested on signal chain settings of the two above switches. The settings below are always "safe"
in case new settings are introduced due to the evaluation of "RBFS_HydrActSystem_Unused" and "RBFS_WssMounted_None" only.
Therefore a Bauhaus deviation is available to ignore the RB_ASSERT_SWITCH_SETTINGS for this switches to reduce the dependency
from signal chains to RBSYS. The jitter monitoring is anyway disabled on series builds.
*/



/** @addtogroup HSW_uCBase_DefaultElements
    @{
      @defgroup HSW_RBSYS_DefaultElements RBSYS HSW Operating System Handling
    @}
*/

  /**
    @addtogroup HSW_RBSYS_DefaultElements
    @{
  */

  /** @defgroup RBFS_CPUMisalignedAccessSupport Allow Misaligned accesses by CPU

    P1x devices do support handling misaligned accesses of the CPU.
    Using Misaligned Accesses is ceritified within GHS2015 Compiler option set.
    GHS2018 (and later GHS versions) will NOT allow misaligned accesses!!

    U2A devices do not support misaligned accesses of the CPU in general.
    Therefore strategy is to disable the feature for all future Devices / Compilers -> commmon concept.

  @{
  */
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_Compiler == RBFS_Compiler_GHS) )
    #define RBFS_CPUMisalignedAccessSupport RBFS_CPUMisalignedAccessSupport_ON
  #else
    #define RBFS_CPUMisalignedAccessSupport RBFS_CPUMisalignedAccessSupport_OFF
  #endif
  /** */

  /** @} */ // ingroup  RBFS_CPUMisalignedAccessSupport


  /** @defgroup RBFS_SYSDebugFeatures RBSYS debug features

  RBSYS specific debug features will be enabled per default on development builds and
  disabled for official release builds. Each project could overwrite the default setting
  during development phase to _OFF (e.g. in case of resource optimization).

  @{
  */
  // MTC introduced a define to distinguish between development and release phase
  #if (RBFS_BUILDTYPE == RBFS_BUILDTYPE_RELEASE)
    #define RBFS_SYSDebugFeatures           RBFS_SYSDebugFeatures_OFF
  #else
    #ifndef RBFS_SYSDebugFeatures
      #define RBFS_SYSDebugFeatures         RBFS_SYSDebugFeatures_ON
    #endif
  #endif
  /** */

  /** @} */ // ingroup  RBFS_SYSDebugFeatures



  /** @defgroup RBFS_SysSystemLoadCalc RBSYS SystemLoad calculation

  RBSYS specific SystemLoad calculation will be configured per default to 120ms. If projects are
  interested on fine grained SystemLoad to see also peaks, switch setting can be overwritten inside
  the project area to 20ms.

  @{
  */
  #ifndef RBFS_SysSystemLoadCalc
    #define RBFS_SysSystemLoadCalc    RBFS_SysSystemLoadCalc_120ms
  #endif
  /** */

  /** @} */ // ingroup  RBFS_SysSystemLoadCalc



  /** @defgroup RBFS_TPSWSVPRestrictions RBSYS Third Party Software supervisor restrictions

  This switch configures the availability of Third Party Software (TPSW) supervisor restrictions.
  If the switch is configured to _ON the RAM will not be executable in supervisor mode!

  todo: remove after some time
  @{
  */

  /** Deactivate TPSW SVP restrictions (MPU active in supervisor mode) by default */
  #ifndef RBFS_TPSWSVPRestrictions
    #define RBFS_TPSWSVPRestrictions    RBFS_TPSWSVPRestrictions_OFF
  #endif

  /** @} */ // ingroup  RBFS_TPSWSVPRestrictions



  /** @defgroup RBFS_SysSignalOsArVersion RBSYS OS AUTOSAR version

  RBSYS will signal different versions, because from API and functionality
  the latest is always usable just the version is signalled as required.

  More projects are based on 4.0.2 therefore default currently configured
  to this. Nevertheless the impact is just two allow compilation of components
  having coupled there release to OS-AR-Version. There is no functional impact.

  @{
  */

  #ifndef RBFS_SysSignalOsArVersion
    #define RBFS_SysSignalOsArVersion RBFS_SysSignalOsArVersion_4x0x2
  #endif

  /** @} */ // ingroup  RBFS_SysSignalOsArVersion





/** @defgroup RBFS_SysHSMsharedGRAM

In case of using the Restricted-SPID feature the attribute  RBFS_SysHSMsharedGRAM specifies the partner
which shares the GRAM with HSM. If nothing is specified RBFS_SysHSMsharedGRAM_Host is defaulted.

@{
*/

#ifndef RBFS_SysHSMsharedGRAM
  #define RBFS_SysHSMsharedGRAM   RBFS_SysHSMsharedGRAM_Host
#endif

/** @} */ // ingroup  RBFS_SysHSMsharedGRAM



/** @defgroup RBFS_FlxrTaskSync

In case of RBFS_FlexraySupport_No and RBFS_FlxrTaskSync unspecified it shall be defaulted to RBFS_FlxrTaskSync_OFF

@{
*/

#if (RBFS_FlexraySupport == RBFS_FlexraySupport_No)
  #ifndef RBFS_FlxrTaskSync
    #define RBFS_FlxrTaskSync   RBFS_FlxrTaskSync_OFF
  #endif
#endif

/** @} */ // ingroup  RBFS_FlxrTaskSync



/** @defgroup RBFS_TaskSync

In case of RBFS_FlxrTaskSync_ON this shall be defaulted to RBFS_TaskSync_ON, otherwise _OFF

@{
*/

#ifndef RBFS_TaskSync
  RB_ASSERT_SWITCH_SETTINGS(RBFS_FlxrTaskSync,
                            RBFS_FlxrTaskSync_ON,
                            RBFS_FlxrTaskSync_OFF);

  #if (RBFS_FlxrTaskSync == RBFS_FlxrTaskSync_ON)
    #define RBFS_TaskSync   RBFS_TaskSync_ON
  #else
    #define RBFS_TaskSync   RBFS_TaskSync_OFF
  #endif
#endif

/** @} */ // ingroup  RBFS_TaskSync



/** @defgroup RBFS_SysEthernetSupport
  backward compability is realized by rb.as.core.arch
@{
*/

  RB_ASSERT_SWITCH_SETTINGS(RBFS_Ethernet,
                            RBFS_Ethernet_Enabled,
                            RBFS_Ethernet_Disabled);

  /* derive RBSYS related function switch setting from generic core.arch switch */
  #if (RBFS_Ethernet == RBFS_Ethernet_Enabled)
    #define RBFS_SysEthernetSupport           RBFS_SysEthernetSupport_ON
  #else
    #define RBFS_SysEthernetSupport           RBFS_SysEthernetSupport_OFF
  #endif



/** @} */ // ingroup  RBFS_SysEthernetSupport


/** @defgroup RBFS_SysMaxTaskx1Jitter

VLV signal chain requires 5% jitter monitoring and WSS signal chain normally requires also 5%.
But in case of systems with WSS only (e.g. iBooster on Single Core) the monitoring could be to
strict and dependent on WSS signal chain requirements, projects could overwrite this default
configuration. In case VLV and WSS is not available default setting is 15%.

@{
*/

#if (RBFS_BUILDTYPE == RBFS_BUILDTYPE_RELEASE)
  #define RBFS_SysMaxTaskx1Jitter     RBFS_SysMaxTaskx1Jitter_SERIES
#else
  #if (RBFS_HydrActSystem == RBFS_HydrActSystem_Unused)
    #if(RBFS_WssMounted == RBFS_WssMounted_None)
      /* no WSS and no VLV signal chain available => 15% */
      #define RBFS_SysMaxTaskx1Jitter     RBFS_SysMaxTaskx1Jitter_15
    #else
      /* only WSS signal chain available => default 5% */
      /* But setting could be overwritten by project dependent on WSS requirements */
      #ifndef RBFS_SysMaxTaskx1Jitter
        #define RBFS_SysMaxTaskx1Jitter     RBFS_SysMaxTaskx1Jitter_5
      #endif
    #endif
  #else
    /* VLV signal chain available => 5% */
    #define RBFS_SysMaxTaskx1Jitter     RBFS_SysMaxTaskx1Jitter_5
  #endif
#endif

/** @} */ // ingroup  RBFS_SysMaxTaskx1Jitter


/** The normal CC-AS strategy concerning interrupt vector table is that bootblock routes the
    interrupts and exceptions directly to application software and therefore the EBASE
    (exception base register) is configured to address 0 within the OS (which is also the HW default).
    There are two use cases where this is not the case:

    - PLANT features:
      This concept will not work in case of an pTSW, which includes two separate SW builds -
      one ePSW and one TC-SW build. The BMGR will route his interrupt vectors only to ePSW.
      So it's neccessary to overwrite the EBASE register at least for the TC-SW.

    - FOTA Enhanced features:
      In FOTA Enhanced flash bank A can be programmed during normal operation, so the
      interrupt vector must be positioned on flash bank B.
*/

#ifndef RBFS_SysOverwriteEBASE                     ///< is configurable from project config
  #if ( (RBFS_pTSWSupport == RBFS_pTSWSupport_ON) || (RBFS_FOTA == RBFS_FOTA_ENHANCED) )
    #define RBFS_SysOverwriteEBASE RBFS_SysOverwriteEBASE_ON
  #else
    #define RBFS_SysOverwriteEBASE RBFS_SysOverwriteEBASE_OFF
  #endif
#endif


/** @defgroup RBFS_SysResettableSlackTimesSupport

This feature allows to measure and reset the slack_time_min via separate interfaces (see RBSYS_TaskInfo.h)

@{
*/

#ifndef RBFS_SysResettableSlackTimesSupport
  #define RBFS_SysResettableSlackTimesSupport RBFS_SysResettableSlackTimesSupport_OFF // by default switched off
#endif

/** @} */ // ingroup  RBFS_SysResettableSlackTimesSupport



/** @defgroup RBFS_RBSYSGlobalRAMGuardsBB RBSYS setting to enable RAM guards for GRAM/CRAM in Bootblock
    Hint: Memory Protection for Global RAM is set up in Bootmanager. Per default, OEM-BLDR/RBBLDR are directly called
          from BMGR and the same settings apply for those.
@{
*/
#if( RBFS_HexBlockBuild != RBFS_HexBlockBuild_APPLICATION )
  #ifndef RBFS_RBSYSGlobalRAMGuardsBB
    #define RBFS_RBSYSGlobalRAMGuardsBB   RBFS_RBSYSGlobalRAMGuardsBB_ON    /* by default switched on for Bootmanager */
  #endif
#else
  #define RBFS_RBSYSGlobalRAMGuardsBB   RBFS_RBSYSGlobalRAMGuardsBB_OFF
#endif
/** @} */ // ingroup  RBFS_RBSYSGlobalRAMGuardsBB



/** @defgroup RBFS_RBSYSSecureBootStartup Derived setting to indicate whether HSM or Host is started first

@{
*/

#if( (RBFS_CyberSecurityBoot == RBFS_CyberSecurityBoot_Trusted) \
  || (RBFS_CyberSecurityBoot == RBFS_CyberSecurityBoot_Staged) \
  || (RBFS_CyberSecurityBoot == RBFS_CyberSecurityBoot_Concurrent) \
  || (RBFS_CyberSecurityBoot == RBFS_CyberSecurityBoot_Secure) \
    )
  /** In case of the above settings, Host shall not be started until Host Software is validated */
  #define RBFS_RBSYSSecureBootStartup RBFS_RBSYSSecureBootStartup_HSMonly
#else
  #define RBFS_RBSYSSecureBootStartup RBFS_RBSYSSecureBootStartup_HSMandHost
#endif

/** @} */ // ingroup  RBFS_RBSYSSecureBootStartup


/** @defgroup RBFS_TriggerTimerSupport

See RBSYS_ConfigElements for a description of the provided FS options and the feature purpose.

@{
*/

#ifndef RBFS_TriggerTimerSupport
  #define RBFS_TriggerTimerSupport RBFS_TriggerTimerSupport_Off
#endif

/** @} */ // ingroup  RBFS_TriggerTimerSupport


/** @defgroup RBFS_CpuClockRestriction

See RBSYS_ConfigElements for a description of the provided FS options and the feature purpose.

@{
*/

#ifndef RBFS_CpuClockRestriction
  #define RBFS_CpuClockRestriction RBFS_CpuClockRestriction_Default
#endif

/** @} */ // ingroup  RBFS_CpuClockRestriction


/** @defgroup RBFS_SysUnittestSimulationModel

See RBSYS_ConfigElements for a description of the provided FS options and the feature purpose.

@{
*/

#ifndef RBFS_SysUnittestSimulationModel
  #define RBFS_SysUnittestSimulationModel RBFS_SysUnittestSimulationModel_OFF
#endif

/** @} */ // ingroup  RBFS_SysUnittestSimulationModel

/** @} */ // ingroup  HSW_RBSYS_DefaultElements


#endif /* End of multiple include protection */
