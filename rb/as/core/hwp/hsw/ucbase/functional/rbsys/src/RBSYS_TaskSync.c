/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Flexray Task Synchronization
 *
 * This module is responsible for the task scheme adaptation to the flexray cycle. It provides in
 * addition a possibility  to test the adaption (e.g. via RB Diag)
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_SystemTimer.h"
#include "RBSYS_TimerOsConfig.h"
#include "RB_MathHelpers.h"

/* realized interfaces */
#include "RBSYS_TaskSync.h"
#include "RBSYS_Subsystem.h"



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSync,
                          RBFS_TaskSync_ON,
                          RBFS_TaskSync_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTask0p5ms,
                          RBFS_SysTask0p5ms_OFF,
                          RBFS_SysTask0p5ms_ON);



#if (RBFS_TaskSync == RBFS_TaskSync_ON)

  //SRMS (Synchronized Rate Monotonic Scheduling)

  static sint32 RBSYS_SRMS_ticks_to_adapt;
  /*[[MEASUREMENT*/
  /*NAME=RBSYS_SRMS_ticks_to_adapt*/
  /*COMMENT=task sync - ticks to adapt*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/


  static sint32 RBSYS_SRMS_overall_adapted_ticks;
  /*[[MEASUREMENT*/
  /*NAME=RBSYS_SRMS_overall_adapted_ticks*/
  /*COMMENT=task sync - already adapted ticks*/
  /*MTEVENT=c_MT_Default_Task_1ms*/
  /*]]MEASUREMENT*/



  #if (RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
    #define RBSYS_SRMS_CYCLETIME_US               CYCLETIME_0p5ms
  #else
    #define RBSYS_SRMS_CYCLETIME_US               CYCLETIME_1ms
  #endif

  /** Adaption must be done in highest prio task (below values are based on 2% max)
   *  RBFS_SysTask0p5ms_ON  -> max. correction 10us per 500us
   *  RBFS_SysTask0p5ms_OFF -> max. correction 20us per 1ms
   */
  #define RBSYS_SRMSMAXCORRECTION_US        ((uint32)((RBSYS_TASKSCHEME_ADJUST_MAX_PERCENT*(float64)RBSYS_SRMS_CYCLETIME_US)/100.0))
  #define RBSYS_SRMSMAXCORRECTION_TICKS     ((sint32)RBSYS_convertUsecToTimerTicks(RBSYS_SRMSMAXCORRECTION_US))


  /* Adaptation must be done in highest prio task */
  void RBSYS_PRC_SRMSTimeBaseAdaptation(void)
  {
    sint32 ticks = RBSYS_SRMS_ticks_to_adapt;
    /**< Reading of requested adaption can be done without lock (latest written value will always be considered under lock) */

    if (ticks != 0)
    {
      /* Global lock only needed for update of global variables below, but as optimization,
       * it is nested with locks needed in RBSYS_STMControlTicks to avoid fine grained lock sequences */
      RBSYS_SchM_Enter_GlobLock();
      ticks = RB_Clamp_s32(ticks, -RBSYS_SRMSMAXCORRECTION_TICKS, RBSYS_SRMSMAXCORRECTION_TICKS);
      ticks = RBSYS_STMControlTicks(ticks);
      RBSYS_SRMS_ticks_to_adapt -= ticks;
      RBSYS_SchM_Exit_GlobLock();

      RBSYS_SRMS_overall_adapted_ticks += ticks;
    }
  }


  /* reinit current adaptation */
  void RBSYS_SRMS_adapt_timebase(sint32 ticks_to_adapt)
  {
    RBSYS_SchM_Enter_GlobLock();
    RBSYS_SRMS_ticks_to_adapt = ticks_to_adapt;
    RBSYS_SchM_Exit_GlobLock();
  }


  /* returns number of adaptation ticks left */
  sint32 RBSYS_SRMS_adapt_ticks_left(void)
  {
    return RBSYS_SRMS_ticks_to_adapt;
  }



  uint16 RBSYS_SRMS_test_advance_ticks;
  /*[[MEASUREMENT*/
  /*NAME=RBSYS_SRMS_test_advance_ticks*/
  /*COMMENT=RBSYS_SRMS_test_advance_ticks*/
  /*MTEVENT=c_MT_Default_Task_x1*/
  /*]]MEASUREMENT*/

  uint16 RBSYS_SRMS_test_retard_ticks;
  /*[[MEASUREMENT*/
  /*NAME=RBSYS_SRMS_test_retard_ticks*/
  /*COMMENT=RBSYS_SRMS_test_retard_ticks*/
  /*MTEVENT=c_MT_Default_Task_x1*/
  /*]]MEASUREMENT*/

 /**
  * @brief Process to test the task adaptation (e.g. via RB Diag)
  *
  * @return void
  */
  void RBSYS_PRC_SRMSCylicTest(void)
  {
    if (RBSYS_SRMS_test_advance_ticks != 0)
    {
      sint32 ticks = (sint32)RBSYS_SRMS_test_advance_ticks;
      RBSYS_SRMS_adapt_timebase(ticks);
    }
    else if (RBSYS_SRMS_test_retard_ticks != 0)
    {
      sint32 ticks = (sint32)RBSYS_SRMS_test_retard_ticks;
      RBSYS_SRMS_adapt_timebase(-ticks);
    }
    else
    {
      /* all if … else if constructs shall be terminated with an else statement */
    }

  }


#endif



/** @} */
/* End ingroup RBSYS */
