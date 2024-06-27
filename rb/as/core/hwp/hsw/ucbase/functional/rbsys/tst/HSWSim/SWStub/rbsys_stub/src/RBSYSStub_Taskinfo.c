#include "RBSYS_TaskInfo.h"
#include "RBSYSStub_TaskSlackTimeManipulation.h"

static uint32 stubbedSlackTime = 0;

void RBSYSStub_SetReturn_getSlackTime(uint32 slacktime)
{
  stubbedSlackTime = slacktime;
}

uint32 RBSYS_getSlackTime(RBSYS_TaskType task)
{
  return stubbedSlackTime;
}

extern uint32 RBSYSStub_TaskActivation_ticks;
uint32 RBSYS_get_task_activation_ts(RBSYS_TaskType task)
{
  /// in sim only one task is running at one point in time.
  /// this value is set, when task is activated.
  return RBSYSStub_TaskActivation_ticks;
}

uint32 RBSYS_getSlackTimeMin(RBSYS_TaskType task){return 0;}

uint32 RBSYS_getTaskRuntime(RBSYS_TaskType task, RBSYS_RuntimeType_t type)
{
  (void)task;
  (void)type;
  return 0;
}

uint32 RBSYS_getIsrRuntime(RBSYS_ISRType isr, RBSYS_RuntimeType_t type)
{
  (void)isr;
  (void)type;
  return 0;
}
#if( RBFS_SysResettableSlackTimesSupport == RBFS_SysResettableSlackTimesSupport_ON )
  uint32 RBSYS_getResettableSlackTimeMin( RBSYS_TaskType task ){return 0;}

  uint32 RBSYS_getTimestampResettableSlackTimeMin( RBSYS_TaskType task ){return 0;}

  void   RBSYS_clearResettableSlackTimeMin( RBSYS_TaskType task ){}

  void   RBSYS_clearAllResettableSlackTimesMin( void ){}
#endif

uint16 RBSYS_getSystemLoadCore0(void){return 0;}

#if (RBFS_MCORE == RBFS_MCORE_ON)
  uint16 RBSYS_getSystemLoadCore1(void){return 0;}
#endif