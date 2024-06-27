#include "RBSYS_SystemTimer.h"

void RBSYS_waitUsecLoop(uint16 l_timeInuS_u16)
{
  int i;

  for(i=0;i<l_timeInuS_u16;i++)
    RBSYS_getSynctimeTickCtr();///< increments pseudo TickCtr by 1us for each call.

  return;
}

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_TriggerTimerSupport == RBFS_TriggerTimerSupport_On) )
  void RBSYS_StartTriggerTimer(uint16 time_in_usec)
  {

  }

  void RBSYS_StopTriggerTimer(void)
  {

  }
#endif
