#include "RBSYS_Idle.c"



#include "RBSYS_Config.h"
#include "TRBSYS_Idle_Adaptor.h"

/********************************************************/
/*                Get private variables                 */
/********************************************************/
uint32 GetPrivate_idle_cnt_core0(void)
{
  return idle_cnt_core0;
}

#if (RBFS_MCORE == RBFS_MCORE_ON)
uint32 GetPrivate_idle_cnt_core1(void)
{
  return idle_cnt_core1;
}
#endif


uint32 GetPrivate_idleloop_immediate_rerun_core0(void)
{
  return idleloop_immediate_rerun_core0;
}

#if (RBFS_MCORE == RBFS_MCORE_ON)
uint32 GetPrivate_idleloop_immediate_rerun_core1(void)
{
  return idleloop_immediate_rerun_core1;
}
#endif


int GetPrivate_IDLE_LOOP_DELAY_US(void)
{
  return IDLE_LOOP_DELAY_US;
}

/********************************************************/
/*                Set private variables                 */
/********************************************************/


/********************************************************/
/*              Access private Functions                */
/********************************************************/
