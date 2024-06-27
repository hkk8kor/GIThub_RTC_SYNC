#include "RBSYS_Config.h"
#include "TRBSYS_uCRegisters.h"
#include "TRBSYS_Intrinsics.h"
#include "RBSYS_TimerSetup.h"
#include "RBSYS_CpuInfo.h"
#include "RBSYS_CoreInit.h"
#include "RBSYS_SystemTimer.h"


uint16 TRBSYS_wait_time;

void RBSYS_waitUsecLoop(uint16 time_in_usec)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    if (BOOTCTRL != 0)
  #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    if (SYSCTRLBOOTCTRL != 0)
  #elif (RBFS_uCFamily == RBFS_uCFamily_STMStellar)
    if (MC_ME_CL0.CoreReg.CCTL[0] != 0x0u)
  #endif
  {
    SWT_EvalEx(FALSE, "It must be ensured that CPU1 is started minimum 50us after CPU0!");
  }

  TRBSYS_wait_time += time_in_usec;
}

uint16 TRBSYS_GetWaitUsecLoop_ExpiredTime(void)
{
  return TRBSYS_wait_time;
}


uint32 TRBSYS_InitTimers_cnt = 0;
TRBSYS_Callback_t TRBSYS_InitTimers_Callback = NULL;
void RBSYS_InitTimers(void)
{
  if(TRBSYS_InitTimers_Callback != NULL)
  {
    TRBSYS_InitTimers_Callback();
  }
  TRBSYS_InitTimers_cnt++;
}