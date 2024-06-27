#ifndef RBSYS_CPUINFO_H__
#define RBSYS_CPUINFO_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief This interface provides information of the CPU status
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_Intrinsics.h"
#include "RBSYS_uCRegisters.h"
#if(RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
  #include "RBSYS_OsServices.h"
  #include "Os.h"                           /* for OS_CORE_ID, OS_NUM_CORES defines */
#endif
#include "RBSYS_PlantStartupCtrl.h"

/* forwarded for backwards compatibility */
#include "RBSYS_uCResetInfo.h"



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);


#if(RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
  // using IDs from OS
  #define RBSYS_CORE_ID_0     OS_CORE_ID_0
  #define RBSYS_CORE_ID_1     OS_CORE_ID_1
#else
  // OS_CORE_ID cannot be used in BB
  #define RBSYS_CORE_ID_0     (0U)
  #define RBSYS_CORE_ID_1     (1U)
#endif


/**
* @brief Core identifier
* Attention: Has to be always_inline due to usage before stack is initialized (PreOSPhase0)
*
* @returns the corresponding core identifier - master core will start with ID 0.
*/
__attribute__((always_inline)) static inline unsigned int RBSYS_getCoreID(void)
{
  #if (RBFS_MCORE == RBFS_MCORE_OFF)
    return RBSYS_CORE_ID_0;
  #else
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      return (RBSYS_STSR(0,2)>>16) - 1;         /* HTCFG0 — Thread configuration register */
    #elif(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
      return (RBSYS_STSR(0,2));                 /* PEID — Processor Element Identifier */
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      return (RBSYS_MRC(15,0,0,0,5) & 0xFFu); /* MPIDR — Multiprocessor Affinity Register, overwritten via VMPIDR at startup */
    #else
      #error ("Implementation of RBSYS_getCoreID is missing for this uCFamily")
    #endif
  #endif
}


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
