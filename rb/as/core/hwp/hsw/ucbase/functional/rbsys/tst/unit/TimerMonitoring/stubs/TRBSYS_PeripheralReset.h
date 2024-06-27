#ifndef TRBSYS_PERIPHERALRESET_H__
#define TRBSYS_PERIPHERALRESET_H__

#include "RBSYS_Config.h" // for RBFS_uCFamily

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
  extern uint32 TRBSYS_TAUD0_SetToRunMode_GetCallCount(void);
#endif

#endif