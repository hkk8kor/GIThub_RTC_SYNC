#ifndef TRB_MEMORYBARRIER_H__
#define TRB_MEMORYBARRIER_H__

#include "RBSYS_Config.h"
#include "RBSYS_Intrinsics.h"

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
  ||(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  ||(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) \
  )
  #define RB_FullHardwareMemoryBarrier() RBSYS_SYNCM()
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  #define RB_FullHardwareMemoryBarrier() RBSYS_DSB()
#endif


#endif