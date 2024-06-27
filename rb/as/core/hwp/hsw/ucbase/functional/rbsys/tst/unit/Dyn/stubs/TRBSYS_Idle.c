#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Idle.h"
#include "TRBSYS_Idle.h"


uint32 sys_general_idleloop_cnt[RB_NUM_CORES];
void sys_general_idleloop(unsigned int core)
{
  sys_general_idleloop_cnt[core]++;
}

uint32 sys_delayed_idleloop_cnt[RB_NUM_CORES];
void sys_delayed_idleloop(unsigned int core)
{
  sys_delayed_idleloop_cnt[core]++;
}

uint32 sys_idleloop_request_rerun_cnt = 0;
void sys_idleloop_request_rerun(void)
{
  sys_idleloop_request_rerun_cnt++;
}


