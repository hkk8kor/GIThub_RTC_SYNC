
#include "RBSYS_Config.h"
#include "RBSYS_CpuInfo.h"

#include "trba_MultiStackTrace.h"
#include "RBSYS_StackHandling.h"
#include "RBSYS_StackMon_Cfg.h"


static uint32 InitCoreLocalStacksCounter = 0;
static uint32 ScanAllStacksCounter = 0;
static TRBSYS_StackCheckTest_t TRBSYS_StackCheckTest = TRBSYS_StackCheck_FaultFree;


uint32 TRBSYS_getInitCoreLocalStacksCounter(void)
{
  return InitCoreLocalStacksCounter;
}

uint32 TRBSYS_getScanAllStacksCounter(void)
{
  return ScanAllStacksCounter;
}


void TRBSYS_SetStackCheckType(TRBSYS_StackCheckTest_t nTest)
{
  TRBSYS_StackCheckTest = nTest;
}


void rba_MultiStackTrace_InitCoreLocalStacks(void)
{
  InitCoreLocalStacksCounter++;
}

void rba_MultiStackTrace_ScanAllStacks(void)
{
  ScanAllStacksCounter++;
}

void rba_MultiStackTrace_GetStackInfo(uint8 StackId, rba_MultiStackTrace_StackMeas_t* OutPointer)
{
  if (StackId == RBSYS_Stack0_StackId)
  {
    switch (TRBSYS_StackCheckTest)
    {
      case TRBSYS_StackCheck_FaultFree:
          OutPointer->FreeSpace = RB_STACK0_SIZE_FSW;
          OutPointer->CheckWordReached = 0;
          break;

      case TRBSYS_StackCheck_Core0_LowChkWord0:
      case TRBSYS_StackCheck_Core0_and_Core1_LowChkWord0:
          OutPointer->FreeSpace = 20;
          OutPointer->CheckWordReached = 1<<0;
          break;

      case TRBSYS_StackCheck_Core0_LowChkWord1:
          OutPointer->FreeSpace = 20;
          OutPointer->CheckWordReached = 1<<1;
          break;

      case TRBSYS_StackCheck_Core0_LowChkWord2:
          OutPointer->FreeSpace = 20;
          OutPointer->CheckWordReached = 1<<2;
          break;

      default:
          OutPointer->FreeSpace = RB_STACK0_SIZE_FSW;
          OutPointer->CheckWordReached = 0;
          break;
    }

  }
#if(RBFS_MCORE == RBFS_MCORE_ON)
  else if (StackId == RBSYS_Stack1_StackId)
  {
    switch (TRBSYS_StackCheckTest)
    {
      case TRBSYS_StackCheck_FaultFree:
          OutPointer->FreeSpace = RB_STACK1_SIZE_FSW;
          OutPointer->CheckWordReached = 0;
          break;

      case TRBSYS_StackCheck_Core1_LowChkWord0:
      case TRBSYS_StackCheck_Core0_and_Core1_LowChkWord0:
          OutPointer->FreeSpace = 20;
          OutPointer->CheckWordReached = 1<<0;
          break;

      case TRBSYS_StackCheck_Core1_LowChkWord1:
          OutPointer->FreeSpace = 20;
          OutPointer->CheckWordReached = 1<<1;
          break;

      case TRBSYS_StackCheck_Core1_LowChkWord2:
          OutPointer->FreeSpace = 20;
          OutPointer->CheckWordReached = 1<<2;
          break;

      default:
          OutPointer->FreeSpace = RB_STACK0_SIZE_FSW;
          OutPointer->CheckWordReached = 0;
          break;
    }
  }
#endif
  else
  {
    SWT_Eval(FALSE);
  }

}


uint32 rba_MultiStackTrace_IsLimitExceeded(const rba_MultiStackTrace_StackMeas_t* ResultStruct, uint8 Level)
{
  return ((uint8)((uint8)(ResultStruct->CheckWordReached & ((uint8)(1U << (Level))))) >> (Level));
}