#ifndef RBSYS_FSWSTARTUP_H__
#define RBSYS_FSWSTARTUP_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Process header for FSW Startup processes
 *
 * This interface contains for the uC Reset Flag clearing an extern declaration.
 * The interface itself must be merged via header entry in RBSYS_Subsystem.proc with
 * mergeproc into final RBSYS_Dyn.c
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBLCF_MemoryRemap.h"  // for RBSECTION_START_SECTTYPE_NO_SDA/RBSECTION_END_SECTTYPE_NO_SDA macros

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_pTSWSupport,
                          RBFS_pTSWSupport_ON,
                          RBFS_pTSWSupport_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);


/* function defined inside "RBSYS_FSWStartVect.850" */

/* Distance in Flash could be farther than what can be covered by sda (small data) feature - so exclude this variable from sda */
RBSECTION_START_SECTTYPE_NO_SDA
extern const uint32 FSWStart;
#if (RBFS_pTSWSupport == RBFS_pTSWSupport_ON)
extern const uint32 ePSWStart;
extern const uint32 TCSWStart;
#endif
RBSECTION_END_SECTTYPE_NO_SDA


#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  #define RBSYS_BOOTCTRL_CORE0_OFFSET (1u)
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  #define RBSYS_BOOTCTRL_CORE0_OFFSET (0u)
#endif

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  #define RBSYS_BOOT_CPU1    (1u << (1 + RBSYS_BOOTCTRL_CORE0_OFFSET))
#endif


/* provide function prototype to prevent compiler diagnostic #1800 for non static declared functions */
extern void RBSYS_StartupPreOSPhase0(void);



/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
