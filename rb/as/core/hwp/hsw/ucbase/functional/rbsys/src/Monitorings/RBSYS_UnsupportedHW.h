#ifndef RBSYS_UNSUPPORTEDHW_H__
#define RBSYS_UNSUPPORTEDHW_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Process header for Unsupported HW check
 *
 * This interface contains for the process "unsupported HW check" an extern declaration.
 * The interface itself must be merged via header entry in RBSYS_Subsystem.proc with
 * mergeproc into final RBSYS_Dyn.c
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);


/* used interfaces */

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
  typedef struct /*TOOL_SCAN*/
  {
    uint32 prdname2;
    uint32 prdname3;
    uint32 version;
  }RBSYS_ProductID_t;
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  typedef struct /*TOOL_SCAN*/
  {
    uint32 midr1;
    uint32 midr2;
  }RBSYS_ProductID_t;
#endif

typedef struct /*TOOL_SCAN*/
{
  RBSYS_ProductID_t DeviceID;
  uint32 l_CpuClock;
} RBSYS_ProductName4MM6_t;


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
