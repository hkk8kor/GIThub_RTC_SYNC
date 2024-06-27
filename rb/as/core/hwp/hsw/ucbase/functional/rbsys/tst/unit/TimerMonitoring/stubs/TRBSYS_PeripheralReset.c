#include "SwTest_Global.h"                      // for SWT functionality
#include "RBSYS_Config.h"

#include "RBSYS_uCModuleEnable.h"
#include "TRBSYS_PeripheralReset.h"

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
static uint32 RBSYS_TAUD0_SetToRunMode_CallCount = 0;

extern void RBSYS_TAUD0_SetToRunMode(void)
{
  RBSYS_TAUD0_SetToRunMode_CallCount++;
}


uint32 TRBSYS_TAUD0_SetToRunMode_GetCallCount(void)
{
  return RBSYS_TAUD0_SetToRunMode_CallCount;
}
#endif