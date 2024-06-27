#include "RBSYS_Config.h"

#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_BBFSW_jump.h"
#include "TRBSYS_BBFSW_jump.h"


uint32 TRBSYS_BBJumpToApplication_cnt = 0;
#if ( (RBFS_SysBootblockBuild == RBFS_SysBootblockBuild_Active) \
   && (RBFS_BootblockSysStartupCode == RBFS_BootblockSysStartupCode_ON) )
  void RBSYS_BBJumpToApplication(void)
  {
    TRBSYS_BBJumpToApplication_cnt++;
  }
#endif
