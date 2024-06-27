#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_CoreInit.h"
#include "TRBSYS_CoreInit.h"
#include "RBSYS_Config.h"
#include "RBSYS_CpuInfo.h"


uint32 TRBSYS_registerInit_cnt = 0;
void RBSYS_registerInit(void)
{
  TRBSYS_registerInit_cnt++;
}


uint32 TRBSYS_SDA_registerInit_cnt = 0;
void RBSYS_SDA_registerInit(void)
{
  TRBSYS_SDA_registerInit_cnt++;
}


uint32 TRBSYS_ClearLRAM_cnt[RB_NUM_CORES];
#if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  void RBSYS_ClearLRAM_P1x(void)
  {
    TRBSYS_ClearLRAM_cnt[RBSYS_getCoreID()]++;
  }
  #if(RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
    uint32 TRBSYS_ClearGRAM_cnt = 0;
    void RBSYS_ClearGRAM_P1x(void)
    {
      TRBSYS_ClearGRAM_cnt++;
    }
  #endif
#elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
  void RBSYS_ClearLRAM_U2A(void)
  {
    TRBSYS_ClearLRAM_cnt[RBSYS_getCoreID()]++;
  }

  #if (RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON)
    uint32 TRBSYS_ClearCRAM0_cnt = 0;
    void RBSYS_ClearCRAM0_U2A(void)
    {
      TRBSYS_ClearCRAM0_cnt++;
    }
  #endif

  #if (RBFS_RenesasU2aCRAM1 == RBFS_RenesasU2aCRAM1_ON)
    uint32 TRBSYS_ClearCRAM1_cnt = 0;
    void RBSYS_ClearCRAM1_U2A(void)
    {
      TRBSYS_ClearCRAM1_cnt++;
    }
  #endif

  #if (RBFS_RenesasU2aCRAM2 == RBFS_RenesasU2aCRAM2_ON)
    uint32 TRBSYS_ClearCRAM2_cnt = 0;
    void RBSYS_ClearCRAM2_U2A(void)
    {
      TRBSYS_ClearCRAM2_cnt++;
    }
  #endif

  #if (RBFS_RenesasU2aCRAM3 == RBFS_RenesasU2aCRAM3_ON)
    uint32 TRBSYS_ClearCRAM3_cnt = 0;
    void RBSYS_ClearCRAM3_U2A(void)
    {
      TRBSYS_ClearCRAM3_cnt++;
    }
  #endif

  uint32 TRBSYS_ClearBURAM_cnt = 0;
  void RBSYS_ClearBURAM_U2A(void)
  {
    TRBSYS_ClearBURAM_cnt++;
  }
#elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
  uint32 TRBSYS_ClearGRAM_cnt = 0;
  void RBSYS_ClearGRAM(void)
  {
    TRBSYS_ClearGRAM_cnt++;
  }

  void RBSYS_ClearLRAM_Stellar(void)
  {
    TRBSYS_ClearLRAM_cnt[0]++;
  }

  uint32 TRBSYS_SwitchHVToSV_cnt = 0;
  void RBSYS_SwitchHVToSV(void)
  {
    TRBSYS_SwitchHVToSV_cnt++;
  }
#endif
