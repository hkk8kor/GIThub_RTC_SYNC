#ifndef TRBSYS_COREINIT_H__
#define TRBSYS_COREINIT_H__


#include "RBSYS_Config.h"

  #include "TRBSYS_uCRegisters.h"
  #include "TRBSYS_CpuInfo.h"

extern uint32 TRBSYS_registerInit_cnt;
extern uint32 TRBSYS_SDA_registerInit_cnt;
extern uint32 TRBSYS_maskINT_cnt;
extern uint32 TRBSYS_ConfigureAlignmentReaction;

extern uint32 TRBSYS_ClearLRAM_cnt[RB_NUM_CORES];
extern uint32 TRBSYS_ClearGRAM_cnt;
extern uint32 TRBSYS_ClearCRAM0_cnt;
extern uint32 TRBSYS_ClearBURAM_cnt;
extern uint32 TRBSYS_ClearCRAM1_cnt;
extern uint32 TRBSYS_ClearCRAM2_cnt;
extern uint32 TRBSYS_ClearCRAM3_cnt;

#if(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
  extern uint32 TRBSYS_SwitchHVToSV_cnt;
#endif

#endif