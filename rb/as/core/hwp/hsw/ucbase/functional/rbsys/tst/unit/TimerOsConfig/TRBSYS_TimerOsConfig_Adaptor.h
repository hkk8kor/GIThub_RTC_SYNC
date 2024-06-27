#ifndef TRBSYS_TIMEROSCONFIG_ADAPTOR_H__
#define TRBSYS_TIMEROSCONFIG_ADAPTOR_H__

#include "SwTest_Global.h"
#include "RBSYS_Config.h"

/********************************************************/
/*                Get private variables                 */
/********************************************************/
extern uint32 TRBSYS_getTask1msFirstTickCtr(void);
extern uint32 TRBSYS_getTaskBaseCtrlFirstTickCtr(void);

extern uint32 GetPrivate_RBSYS_timer_freq_mhz(void);

/********************************************************/
/*                Set private variables                 */
/********************************************************/

/********************************************************/
/*              Access private Functions                */
/********************************************************/
#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  extern sint32 CallPrivate_rbsys_STMControlTicks_LimitedAccelerationTicks(sint32 delta_ticks, sint32 diff_to_compare);
  extern sint32 CallPrivate_rbsys_STMControlTicks_LimitedDecelerationTicks(sint32 delta_ticks, sint32 diff_to_compare);
#endif

#endif