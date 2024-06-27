#ifndef TRBA_MULTISTACKTRACE_H__
#define TRBA_MULTISTACKTRACE_H__

#include "SwTest_Global.h"



/* Structure rba_MultiStackTrace_StackMeas_t:
 - FreeSpace: last measured free space of a stack (in bytes).
 - CheckWordReached: this is a mask which gives the reached checkword levels. */
typedef struct {
    uint32 FreeSpace;
    uint8 CheckWordReached;
} rba_MultiStackTrace_StackMeas_t;




typedef enum
{
  TRBSYS_StackCheck_FaultFree = 0,
  TRBSYS_StackCheck_Core0_LowChkWord0,
  TRBSYS_StackCheck_Core0_LowChkWord1,
  TRBSYS_StackCheck_Core0_LowChkWord2,
  TRBSYS_StackCheck_Core1_LowChkWord0,
  TRBSYS_StackCheck_Core1_LowChkWord1,
  TRBSYS_StackCheck_Core1_LowChkWord2,
  TRBSYS_StackCheck_Core0_and_Core1_LowChkWord0
  
} TRBSYS_StackCheckTest_t;

extern void TRBSYS_SetStackCheckType(TRBSYS_StackCheckTest_t type);


extern void rba_MultiStackTrace_InitCoreLocalStacks(void);
extern void rba_MultiStackTrace_ScanAllStacks(void);
extern void rba_MultiStackTrace_GetStackInfo(uint8 StackId, rba_MultiStackTrace_StackMeas_t* OutPointer);
extern uint32 rba_MultiStackTrace_IsLimitExceeded(const rba_MultiStackTrace_StackMeas_t* ResultStruct, uint8 Level);


extern uint32 TRBSYS_getScanAllStacksCounter(void);
extern uint32 TRBSYS_getInitCoreLocalStacksCounter(void);


#endif
