#ifndef RBSYS_DEFAULTELEMENTSPURE_H__
#define RBSYS_DEFAULTELEMENTSPURE_H__

/**
 * @file
 * @brief Provides RBSYS specific default switch settings, which could be overwritten by project configuration
 *
 * @note "RBSYS_DefaultElementsPure.h" is only allowed to be included within "RBSYS_DefaultElements.h" or "RBSYS_GuardMemoryMap.h" or RBSYS specific BCFG files
 *        This file shall only contain defaulting for function switches that are used in the above mentioned files.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


/* used interfaces */
/** no includes allowed due to usage within Build_Config.bcfg or LD file */


/* Assert supported configurations: switches, parameters, constants, ... */
/** no RB_ASSERT_SWITCH_SETTINGS allowed due to usage within Build_Config.bcfg or LD file */



/**
  @addtogroup HSW_RBSYS_DefaultElements
  @{
*/


/** @defgroup RBFS_SysHsmSharedGRAMsize

In case of RBFS_HardwareSecurityModule_Supported a RBFS_SysHsmSharedGRAMsize different from 0K
must be specified by the project. In case of RBFS_HardwareSecurityModule_Unsupported specifying
a shared HsmGRAM is possible, but then is must be 0K (sanity checks in RBSYS_Config.h).

@{
*/

#if (RBFS_HardwareSecurityModule == RBFS_HardwareSecurityModule_Unsupported)
  #ifndef RBFS_SysHsmSharedGRAMsize
    #define RBFS_SysHsmSharedGRAMsize   RBFS_SysHsmSharedGRAMsize_0K
  #endif
#endif

/** @} */ // ingroup  RBFS_SysHsmSharedGRAMsize




/** @defgroup RBFS_RestrictedExclusiveGRAMsize

In case of using the Restricted-SPID feature a RBFS_RestrictedExclusiveGRAMsize different from 0K
must be specified by the project. In case nothing is specified, it shall be defaulted to 0.

@{
*/

#ifndef RBFS_RestrictedExclusiveGRAMsize
  #define RBFS_RestrictedExclusiveGRAMsize   RBFS_RestrictedExclusiveGRAMsize_0K
#endif

/** @} */ // ingroup  RBFS_RestrictedExclusiveGRAMsize




/** @defgroup RBFS_SysEthSharedGRAMsize

In case of using the Sys Ethernet support a RBFS_SysEthSharedGRAMsize different from 0K
must be specified by the project. In case nothing is specified, it shall be defaulted to 0.

@{
*/

#ifndef RBFS_SysEthSharedGRAMsize
  #define RBFS_SysEthSharedGRAMsize   RBFS_SysEthSharedGRAMsize_0K
#endif

/** @} */ // ingroup  RBFS_SysEthSharedGRAMsize



/** @defgroup RBFS_BootblockSysStartupCode RBSYS start-up Code for bootblock

This switch configures the availability of the RBSYS provided start-up code for bootblock builds.
The setting depends on the usage of a boot loader in combination with or without a boot manager:

1.) Boot manager & boot loader:
      Only boot manager needs to activate the start-up code

2.) Only boot loader (without boot manager):
      Boot loader needs to activate the start-up code

@{
*/

/** Deactivate bootblock startupcode per default */
#ifndef RBFS_BootblockSysStartupCode
  #define RBFS_BootblockSysStartupCode        RBFS_BootblockSysStartupCode_OFF
#endif

/** @} */ // ingroup  RBFS_BootblockSysStartupCode



/** @defgroup RBFS_TPSWTestsuite RBSYS Third Party Software testsuite

This switch configures the availability of the Third Party Software (TPSW) testsuite,
which is only used for development purpose.

Hint: Take care - setting must be _OFF in case of customer project or of course series builds!
Therefore the switch will be configured per default to RBFS_TPSWTestsuite_OFF

@{
*/

/** Deactivate TPSW testsuite per default */
#ifndef RBFS_TPSWTestsuite
  #define RBFS_TPSWTestsuite        RBFS_TPSWTestsuite_OFF
#endif

/** @} */ // ingroup  RBFS_TPSWTestsuite


/** @defgroup RBFS_SysTPSWSupport RBSYS Third Party Software support

This switch indicates if RBSYS provides measures to integrate Third Party Software (especially 
TPSW rated as Non-ASIL-D).

Attention: This RBFS cannot be configured, it will be derived from RBFS_TPSWCapsule.

@{
*/

/** RBSYS has to provide a TPSW environment for SC3/SC4 */
#define RBFS_SysTPSWSupport_YES 1
/** RBSYS does not integrate / capsule TPSW */
#define RBFS_SysTPSWSupport_NO  2

#if( (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC3) \
  || (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4) )
  #define RBFS_SysTPSWSupport RBFS_SysTPSWSupport_YES
#else
  #define RBFS_SysTPSWSupport RBFS_SysTPSWSupport_NO
#endif

/** @} */ // ingroup  RBFS_SysTPSWSupport


/** @defgroup RBFS_SysRAMLayoutFragmentation RBSYS RAM Layout Fragmentation Optimizations

This switch indicates if the RAM Layout is optimized for any kind of fragmentation (e.g. less fragmentation of the Global RAM).

Attention: This RBFS cannot be configured, it will be derived from RBFS_RAMLayoutFragmentation.

@{
*/

#define RBFS_SysRAMLayoutFragmentation_Default 1
#define RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR 2

#ifdef RBFS_RAMLayoutFragmentation
  #if( RBFS_RAMLayoutFragmentation == RBFS_RAMLayoutFragmentation_GRAMOptimizedForBLDR )
    /* if RAMLayoutFragmentation (currently only for D3 w/ HSM) is set, derive internal function switch */
    #define RBFS_SysRAMLayoutFragmentation RBFS_SysRAMLayoutFragmentation_GRAMOptimizedForBLDR
  #endif
#endif

#ifndef RBFS_SysRAMLayoutFragmentation
  /* if RAMLayoutFragmentation is not derived from global function switch, default to _Default */
  #define RBFS_SysRAMLayoutFragmentation RBFS_SysRAMLayoutFragmentation_Default
#endif

/** @} */ // ingroup  RBFS_SysRAMLayoutFragmentation


/** @} */ // ingroup  HSW_RBSYS_DefaultElements




#endif /* End of multiple include protection */
