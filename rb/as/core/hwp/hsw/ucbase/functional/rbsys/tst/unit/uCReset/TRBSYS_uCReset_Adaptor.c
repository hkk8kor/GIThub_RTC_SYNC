#include "RBSYS_uCReset.c"

#include "RBSYS_Config.h"



#include "TRBSYS_uCReset_Adaptor.h"

void TRBSYS_SetInvalidRequestedResetType(void)
{
  rbsys_ResetRequest = (RBSYS_uCResetType_t)0xFF;
}

void TRBSYS_SetUndefinedRequestedResetType(void)
{
  rbsys_ResetRequest = RBSYS_uCResetType_Undefined;
}

void TRBSYS_SetValidRequestedResetType(void)
{
  rbsys_ResetRequest = RBSYS_uCResetType_ApplResetDefault;
}

#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
  void TRBSYS_TriggerReset(void)
  {
    rbsys_TriggerReset();
  }
#endif

void TRBSYS_ExecuteReset(void)
{
  RBSYS_ExecuteReset();
}