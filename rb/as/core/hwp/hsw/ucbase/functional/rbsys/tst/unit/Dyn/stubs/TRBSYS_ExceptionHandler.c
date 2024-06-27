#include "RBSYS_Config.h"

#define __interrupt
#include "RBSYS_ExceptionHandler.h"

uint32 TRBSYS_HandleSupervisorMpuViolation_CallCnt = 0;
void RBSYS_HandleSupervisorMpuViolation(void)
{
  TRBSYS_HandleSupervisorMpuViolation_CallCnt++;
}