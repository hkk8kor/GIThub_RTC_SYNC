#include "SwTest_Global.h"                      // for SWT functionality

#include "TRBLCF_MemoryMap.h"


uint32 TRBSYS_DummyReprogDriver_cnt = 0;

void TRBSYS_DummyReprogDriver(void)
{
  TRBSYS_DummyReprogDriver_cnt++;
}

uint32 RBLCF_getStartAddress_DLM_RAM(void)
{
  return (uint32)&TRBSYS_DummyReprogDriver;
}

uint32 TRBSYS_BURAM_FSW[TRBSYS_BURAM_FSW_Length] = {0};
uint32 RBLCF_getStartAddress_BURAM_FSW(void)
{
  return (uint32)&TRBSYS_BURAM_FSW[0];
}

uint32 RBLCF_getLength_BURAM_FSW(void)
{
  return sizeof(TRBSYS_BURAM_FSW);
}


