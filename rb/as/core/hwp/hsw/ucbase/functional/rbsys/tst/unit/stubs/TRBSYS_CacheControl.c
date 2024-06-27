#include "RBSYS_Config.h"
#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_CacheControlIntern.h"
#include "TRBSYS_CacheControlIntern.h"

#if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
  uint32 TRBSYS_WTBufErrataHandling_cnt = 0;
  void RBSYS_WTBufErrataHandling(void)
  {
    TRBSYS_WTBufErrataHandling_cnt++;
  }
#endif

#if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2))
  uint32 TRBSYS_DisableInstructionCache_cnt = 0;
  void RBSYS_DisableInstructionCache(void)
  {
    TRBSYS_DisableInstructionCache_cnt++;
  }
#endif