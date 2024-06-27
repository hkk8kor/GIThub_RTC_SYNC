#include "SwTest_Global.h"                      // for SWT functionality
#include "RBSYS_Config.h"
#include "RBSYS_CoreMpu.h"

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  uint32 RBSYS_CoreMpu_Init_CallCnt = 0;
  void RBSYS_CoreMpu_Init(void)
  {
    RBSYS_CoreMpu_Init_CallCnt++;
  }
  uint32 TRBSYS_CoreMpu_attributes[16] = {0};
  void RBSYS_CoreMpu_SetRegionAttr(uint32 mpu_region, uint32 attr)
  {
    TRBSYS_CoreMpu_attributes[mpu_region] = attr;
  }
  #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_TPSWSVPRestrictions == RBFS_TPSWSVPRestrictions_ON))
    uint32 TRBSYS_CoreMpu_AllowRamExecution_cnt = 0;
    void RBSYS_CoreMpu_AllowRamExecution(void)
    {
      TRBSYS_CoreMpu_AllowRamExecution_cnt++;
    }
  #endif
#endif