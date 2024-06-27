#ifndef RBTPSW_TPSWCAPSULE_MPUDRIVER_H__
#define RBTPSW_TPSWCAPSULE_MPUDRIVER_H__

/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief Third party software capsule - MPU driver
 *
 * This internal API provides MPU services for TPSW memory protection
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* used interfaces */
#include "Os.h"
#include "RBSYS_StackMon_Cfg.h"
#include "RBTPSW_TPSWCapsule_Priv.h"
#include <assert.h>                           // for static_assert()

/* Assert supported configurations: switches, parameters, constants, ... */

RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTPSWSupport,
                          RBFS_SysTPSWSupport_YES,
                          RBFS_SysTPSWSupport_NO);


#if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)

  /* Function prototypes */
  extern void RBTPSW_ConfigMpu(const rbtpsw_fncall_context_t* tpsw_config, uint32 sp, uint32 sp_end, CoreIdType CoreId);

  /* Inline function implementations */
  static inline uint8 RBTPSW_IsAdrWithinStack(CoreIdType CoreId, uint32 sp)
  {
    #if(RBFS_MCORE == RBFS_MCORE_ON)
      uint8 ret = RBTPSW_FALSE;

      if(CoreId == OS_CORE_ID_0)
      {
        ret = ((sp < (uint32)RBSYS_Stack0_Start) && (sp > (uint32)RBSYS_Stack0_End)) ? RBTPSW_TRUE : RBTPSW_FALSE;
      }
      else if(CoreId == OS_CORE_ID_1)
      {
        ret = ((sp < (uint32)RBSYS_Stack1_Start) && (sp > (uint32)RBSYS_Stack1_End)) ? RBTPSW_TRUE : RBTPSW_FALSE;
      }
      else
      {
        /* MISRA - shall never occure (see below sanity check) */
        static_assert(RB_NUM_CORES == 2, "RB_NUM_CORES is not equal to 2 and therefore this part must be adapted!");
      }

      return ret;
    #else
      (void)CoreId;
      return ((sp < (uint32)RBSYS_Stack0_Start) && (sp > (uint32)RBSYS_Stack0_End)) ? RBTPSW_TRUE : RBTPSW_FALSE;
    #endif
  }


#endif

/** @} */
/* End ingroup RBTPSW */

#endif /* End of multiple include protection */
