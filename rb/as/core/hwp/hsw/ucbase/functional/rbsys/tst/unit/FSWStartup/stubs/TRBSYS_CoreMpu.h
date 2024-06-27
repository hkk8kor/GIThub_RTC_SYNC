#ifndef TRBSYS_COREMPU_H__
#define TRBSYS_COREMPU_H__

#include "RBSYS_Config.h"

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  extern uint32 RBSYS_CoreMpu_Init_CallCnt;
  extern uint32 TRBSYS_CoreMpu_attributes[16];
  #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_TPSWSVPRestrictions == RBFS_TPSWSVPRestrictions_ON))
    extern uint32 TRBSYS_CoreMpu_AllowRamExecution_cnt;
  #endif
#endif

#endif