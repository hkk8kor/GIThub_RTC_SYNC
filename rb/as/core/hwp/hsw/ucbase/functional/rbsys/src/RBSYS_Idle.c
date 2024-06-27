/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Idle handling
 *
 * This interface provides the generic idle loop together with an extension for Multi-Core systems. This extension provides the possiblility
 * to configure the speed of the idle loop depending on a rerun request, which could be used to reduce bus congestion in M-Core systems.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBLCF_MemoryRemap.h"
#include "RBSYS_Intrinsics.h"     // for RBSYS_SNOOZE_LOOP
#include "RBSYS_CpuInfo.h"
#include "RBSYS_SystemTimer.h"
#include "RBSYS_TestInjection.h"

/* realized interfaces */
#include "RBSYS_Idle.h"



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);



RBSECTION_START_LRAM0_BSS_CLEAR
static uint32 idle_cnt_core0;     // allocation in local RAM of Core0
/*[[MEASUREMENT*/
/*NAME=idle_cnt_core0*/
/*COMMENT=Idleloop counter of Core0*/
/*MTEVENT=c_MT_Default_Task_1ms*/
/*]]MEASUREMENT*/
RBSECTION_END_LRAM0_BSS_CLEAR


#if (RBFS_MCORE == RBFS_MCORE_ON)
  RBSECTION_START_LRAM1_BSS_CLEAR
  static uint32 idle_cnt_core1;   // allocation in local RAM of Core1
  /*[[MEASUREMENT*/
  /*NAME=idle_cnt_core1*/
  /*COMMENT=Idleloop counter of Core1*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/
  RBSECTION_END_LRAM1_BSS_CLEAR
#endif


/** flash structure with pointer to core specific idleloop counter (counters are allocated in corresponding LRAM) */
static uint32* const idle_cnt[RB_NUM_CORES] = {  &idle_cnt_core0
                                            #if (RBFS_MCORE == RBFS_MCORE_ON)
                                               , &idle_cnt_core1
                                            #endif
                                              };

/** single idle loop */
void sys_general_idleloop(unsigned int core)
{
  /* just count idle loops => maybe not needed in future */
  (*idle_cnt[core])++;

  /* add some nops to slow-down a bit the idle loop to avoid bus congestion for mcore systems */
  RBSYS_SNOOZE_LOOP(1);
}




RBSECTION_START_LRAM0_BSS_CLEAR
static uint32 idleloop_immediate_rerun_core0;   // core specific idleloop rerun request
RBSECTION_END_LRAM0_BSS_CLEAR

#if (RBFS_MCORE == RBFS_MCORE_ON)
RBSECTION_START_LRAM1_BSS_CLEAR
static uint32 idleloop_immediate_rerun_core1;   // core specific idleloop rerun request
RBSECTION_END_LRAM1_BSS_CLEAR
#endif


/** flash structure with pointer to core specific idleloop rerun request (rerun requests are allocated in corresponding LRAM) */
static uint32* const idleloop_immediate[RB_NUM_CORES] = {  &idleloop_immediate_rerun_core0
                                                      #if (RBFS_MCORE == RBFS_MCORE_ON)
                                                         , &idleloop_immediate_rerun_core1
                                                      #endif
                                                        };


void sys_idleloop_request_rerun(void) // must be called from the process running in idle (i.e. running on same core)
{
  *idleloop_immediate[RBSYS_getCoreID()] = 1;
}

#define IDLE_LOOP_DELAY_US   (50)  /* 50 us delay per idle loop if no rerun is requested via sys_request_idleloop_rerun() */

void sys_delayed_idleloop(unsigned int core)
{
  if (*idleloop_immediate[core] != 0)  // rerun requested -> immediate reexecute
  {
    *idleloop_immediate[core] = 0;
  }
  else
  {
    // no rerun requested: delay execution of next idleloop by x us, to not occupy the resources (bus, ...) for the other core
    uint32 tick;
    RBSYS_startUsecTimer(&tick);

    RBSYS_TEST_INJECTION_Preemption();

    RBSYS_waitUntilTimerElapsed(&tick, IDLE_LOOP_DELAY_US);
  }
}



/** @} */
/* End ingroup RBSYS */
