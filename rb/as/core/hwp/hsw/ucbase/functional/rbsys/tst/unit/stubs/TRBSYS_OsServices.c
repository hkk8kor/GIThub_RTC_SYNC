#include "RBSYS_Config.h"

#if(RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
  #include "RBSYS_OsConfig.h"
  #include "TRBSYS_OsConfig.h"

  RBSYS_OperationMode_n TRBSYS_CurrentOperationMode = RBSYS_OperationMode_PreInit;
  void RBSYS_SetCurrentOperationMode(RBSYS_OperationMode_n mode)
  {
    TRBSYS_CurrentOperationMode = mode;
  }
#endif
