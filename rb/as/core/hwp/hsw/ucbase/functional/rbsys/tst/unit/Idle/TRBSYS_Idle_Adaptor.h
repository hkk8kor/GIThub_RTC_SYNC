#ifndef TRBSYS_IDLE_ADAPTOR_H__
#define TRBSYS_IDLE_ADAPTOR_H__

#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"

/********************************************************/
/*                Get private variables                 */
/********************************************************/
extern uint32 GetPrivate_idle_cnt_core0(void);
#if (RBFS_MCORE == RBFS_MCORE_ON)
extern uint32 GetPrivate_idle_cnt_core1(void);
#endif

extern uint32 GetPrivate_idleloop_immediate_rerun_core0(void);
#if (RBFS_MCORE == RBFS_MCORE_ON)
extern uint32 GetPrivate_idleloop_immediate_rerun_core1(void);
#endif

extern int GetPrivate_IDLE_LOOP_DELAY_US(void);

/********************************************************/
/*                Set private variables                 */
/********************************************************/


/********************************************************/
/*              Access private Functions                */
/********************************************************/


#endif