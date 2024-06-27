#ifndef TRBSYS_IDLE_H__
#define TRBSYS_IDLE_H__

#include "RBSYS_Config.h"

extern uint32 sys_general_idleloop_cnt[RB_NUM_CORES];

extern uint32 sys_delayed_idleloop_cnt[RB_NUM_CORES];

extern uint32 sys_idleloop_request_rerun_cnt;


#endif
