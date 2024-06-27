#include "SwTest_Global.h"                      // for SWT functionality

#include "TRBSYS_CpuInfo.h"
#include "TRBSYS_Intrinsics.h"





void TRBSYS_setCoreID(unsigned int newCoreID)
{
  TRBSYS_Intrinsics_SetRegisterSetIndex(newCoreID);
  // change Register Set
  // Hint: CoreID is set by default in corresponding System Register set
}

