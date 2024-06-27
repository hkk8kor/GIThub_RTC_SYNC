#include "csw/RBSYS_TaskInfo.h" // ensure include of original RBSYS header instead of CoreStub
#include "RBSYS_TimerOsConfig.c"
#include "RBSYS_Config.h"



#include "TRBSYS_TimerOsConfig_Adaptor.h"

/********************************************************/
/*                Get private variables                 */
/********************************************************/
uint32 TRBSYS_getTask1msFirstTickCtr(void)
{
  uint32 result;
  RBMESG_RcvMESG(result, RBMESG_Task1msFirstTickCtr);

  return result;
}
uint32 TRBSYS_getTaskBaseCtrlFirstTickCtr(void)
{
  uint32 result;
  RBMESG_RcvMESG(result, RBMESG_TaskBaseCtrlFirstTickCtr);

  return result;
}

uint32 GetPrivate_RBSYS_timer_freq_mhz(void)
{
  return RBSYS_timer_freq_mhz;
}

/********************************************************/
/*                Set private variables                 */
/********************************************************/

/********************************************************/
/*              Access private Functions                */
/********************************************************/

#if( (RBFS_uCFamily == RBFS_uCFamily_STMStellar) && (RBFS_TaskSync == RBFS_TaskSync_ON) )
  sint32 CallPrivate_rbsys_STMControlTicks_LimitedAccelerationTicks(sint32 delta_ticks, sint32 diff_to_compare)
  {
    return rbsys_STMControlTicks_LimitedAccelerationTicks(delta_ticks, diff_to_compare);
  }
  sint32 CallPrivate_rbsys_STMControlTicks_LimitedDecelerationTicks(sint32 delta_ticks, sint32 diff_to_compare)
  {
    return rbsys_STMControlTicks_LimitedDecelerationTicks(delta_ticks, diff_to_compare);
  }
#endif