#include "RBSYS_Config.h"
#include "SwTest_Global.h"                      // for SWT functionality

#include "TRBSYS_CpuVersions.h"
#include "TRBSYS_uCRegisters.h"

#if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  void TRBSYS_SetCPU_D3_LQFP144_DPS_V100(void)
  {
    PRDSEL3 = (PRDSEL3 & ~(0xFFF << 16)) | (0x100 << 16);
    PRDNAME2 = 0x33333130u;
    PRDNAME3 = 0x20202030u;
  }

  void TRBSYS_SetCPU_D3_BGA292_DPS_V100(void)
  {
    PRDSEL3 = (PRDSEL3 & ~(0xFFF << 16)) | (0x100 << 16);
    PRDNAME2 = 0x32333130u;
    PRDNAME3 = 0x20202038u;
  }

  void TRBSYS_SetCPU_D3_BGA292_EVR_V100(void)
  {
    PRDSEL3 = (PRDSEL3 & ~(0xFFF << 16)) | (0x100 << 16);
    PRDNAME2 = 0x32333130u;
    PRDNAME3 = 0x20202039u;
  }

  void TRBSYS_SetCPU_D3_LQFP144_EVR_V100(void)
  {
    PRDSEL3 = (PRDSEL3 & ~(0xFFF << 16)) | (0x100 << 16);
    PRDNAME2 = 0x33333130u;
    PRDNAME3 = 0x20202031u;
  }

  void TRBSYS_SetCPU_D3_HQFP144_EVR_V100(void)
  {
    PRDSEL3 = (PRDSEL3 & ~(0xFFF << 16)) | (0x100 << 16);
    PRDNAME2 = 0x33333130u;
    PRDNAME3 = 0x20202033u;
  }

  void TRBSYS_SetCPU_D3ED_V100(void)
  {
    PRDSEL3 = (PRDSEL3 & ~(0xFFF << 16)) | (0x100 << 16);
    PRDNAME2 = 0x33333130u;
    PRDNAME3 = 0x20204134u;
  }

  void TRBSYS_SetCPU_D4_V200(void)
  {
    PRDSEL3 = (PRDSEL3 & ~(0xFFF << 16)) | (0x200 << 16);
    PRDNAME2 = 0x32333130u;
    PRDNAME3 = 0x20202037u;
  }

  void TRBSYS_SetCPU_D5EDV2_V100(void)
  {
    PRDSEL3 = (PRDSEL3 & ~(0xFFF << 16)) | (0x100 << 16);
    PRDNAME2 = 0x32333130u;
    PRDNAME3 = 0x20204135u;
  }

  void TRBSYS_SetCPU_D5EDV3_V100(void)
  {
    PRDSEL3 = (PRDSEL3 & ~(0xFFF << 16)) | (0x100 << 16);
    PRDNAME2 = 0x32333130u;
    PRDNAME3 = 0x20204235u;
  }

  void TRBSYS_SetCPU_D3ED(void)
  {
    PRDSEL3 = (PRDSEL3 & ~(0xFFF << 16)) | (0x100 << 16);
    PRDNAME2 = 0x33333130u;
    PRDNAME3 = 0x20204134u;
  }

  void TRBSYS_SetCPU_D5ED(void)
  {
    PRDSEL3 = (PRDSEL3 & ~(0xFFF << 16)) | (0x100 << 16);
    PRDNAME2 = 0x32333130u;
    PRDNAME3 = 0x20204235u;
  }
#endif