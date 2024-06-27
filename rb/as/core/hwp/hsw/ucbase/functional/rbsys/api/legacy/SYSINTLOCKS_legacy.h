#ifndef SYSINTLOCKS_LEGACY_H
#define SYSINTLOCKS_LEGACY_H

#include     "RBCMHSW_Locks.h"



static inline void FUN_SYSSuspendIRQs_V(void)
{
   RBSYS_ENTER_COMMON_LOCK();
}
//#define FUN_SYSSuspendIRQs_V SYS_ENTER_COMMON_LOCK

static inline void FUN_SYSResumeIRQs_V(void)
{
  RBSYS_EXIT_COMMON_LOCK();
}


#endif
