#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"

#include "RBSYS_BBMain.h"
#include "TRBSYS_BBMain.h"


uint32 TRBSYS_BBJumpToBBMain_cnt = 0;
#if ( (RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active) \
   && (RBFS_BootblockSysStartupCode == RBFS_BootblockSysStartupCode_ON) )
  void RB_JumpToBBMain(void)
  {
    TRBSYS_BBJumpToBBMain_cnt++;
  }
#endif