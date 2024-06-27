#include "SwTest_Global.h"                      // for SWT functionality

#include "TRBSYS_LocksImplIntern.h"
#include "RBSYS_Subsystem.h"


uint32 TRBSYS_ResetMaxLock_cnt = 0;

void RBSYS_PRC_ResetMaxLockTime_Init(void)
{
  TRBSYS_ResetMaxLock_cnt++;
}