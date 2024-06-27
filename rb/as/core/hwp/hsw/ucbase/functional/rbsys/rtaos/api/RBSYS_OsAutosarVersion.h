#ifndef RBSYS_OSAUTOSARVERSION_H__
#define RBSYS_OSAUTOSARVERSION_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief OS Autosar version
 *
 * This interface provides the Autosar version info of the operating system.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h" ///< for RBFS_SysSignalOsArVersion

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysSignalOsArVersion,
                          RBFS_SysSignalOsArVersion_4x0x2,
                          RBFS_SysSignalOsArVersion_4x2x2,
                          RBFS_SysSignalOsArVersion_4x5x0);


/* At least EcuM is strongly coupled to AR version defines.
 * RBSYS will therefore signal different versions, because from
 * API and functionality the latest is always usable
 * just the version is signalled as required. */

/* Used RTAOS interfaces are same for all supported Autosar versions (confirmed by OS Team), 
 * therefore version is defined centrally here. */

#if( RBFS_SysSignalOsArVersion == RBFS_SysSignalOsArVersion_4x0x2 )

  #define OS_AR_MAJOR_VERSION (4U)
  #define OS_AR_MINOR_VERSION (0U)
  #define OS_AR_PATCH_VERSION (2U)
  #define OS_AR_RELEASE_MAJOR_VERSION (4U)
  #define OS_AR_RELEASE_MINOR_VERSION (0U)
  #define OS_AR_RELEASE_REVISION_VERSION (2U)
  
#elif( RBFS_SysSignalOsArVersion == RBFS_SysSignalOsArVersion_4x2x2 )

  #define OS_AR_MAJOR_VERSION (4U)
  #define OS_AR_MINOR_VERSION (2U)
  #define OS_AR_PATCH_VERSION (2U)
  #define OS_AR_RELEASE_MAJOR_VERSION (4U)
  #define OS_AR_RELEASE_MINOR_VERSION (2U)
  #define OS_AR_RELEASE_REVISION_VERSION (2U)

#elif( RBFS_SysSignalOsArVersion == RBFS_SysSignalOsArVersion_4x5x0 )

  #define OS_AR_MAJOR_VERSION (4U)
  #define OS_AR_MINOR_VERSION (5U)
  #define OS_AR_PATCH_VERSION (0U)
  #define OS_AR_RELEASE_MAJOR_VERSION (4U)
  #define OS_AR_RELEASE_MINOR_VERSION (5U)
  #define OS_AR_RELEASE_REVISION_VERSION (0U)

#else

  #error("RBFS_SysSignalOsArVersion unknown switch setting.")

#endif


/** @} */
/* End ingroup RBSYS */

#endif