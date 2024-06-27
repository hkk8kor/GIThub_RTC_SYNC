/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief System Timer (STM) configuration
 *
 * Timer services and timer configuration for Operating System provided by RBSYS
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_uCRegisters.h"         // peripheral labels
#include "RBSYS_OsServices.h"
#include "Monitorings/RBSYS_ErrorHooks.h"
#include "RBSYS_EnableIRQs.h"
#include "Os.h"
#include "RBSYS_CpuInfo.h"
#include "RBSYS_SystemTimer.h"
#include "RBSYS_TestInjection.h"
#include "RB_MathHelpers.h"
#include <stdlib.h> // for abs()
#include <assert.h>


/* realized interfaces */
#include "RBSYS_TimerOsConfig.h"
#include "RBSYS_TaskSync.h"
#include "RBSYS_TaskInfo.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSync,
                          RBFS_TaskSync_ON,
                          RBFS_TaskSync_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);


RBMESG_DefineMESG(RBMESG_Task1msFirstTickCtr);
RBMESG_DefineMESG(RBMESG_TaskBaseCtrlFirstTickCtr);

/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_Task1msFirstTickCtr*/
/*COMMENT=Sampled once at power up only*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/

/*[[MEASUREMENT*/
/*NAME=RBMESG_RBMESG_TaskBaseCtrlFirstTickCtr*/
/*COMMENT=Sampled once at power up only*/
/*MTEVENT=c_MT_Default_Task_x24*/
/*]]MEASUREMENT*/



/* ------------------------------------------------------------------------------------------------
   SW workaround for GHS compiler incident 65175:
   __attribute__((used)) will not work as expected on current available GHS compiler suite.
   Due to an internal compiler issue it's not possible to declare the measurement variable RBSYS_timer_freq_mhz
   as static. The compiler will still remove the whole variable even with usage of the
   attribute used because there is no visible reference. This problem was fixed in the
   v2016.5 final release, but as long as we are using 2015.1. we've to keep the external visibility.

   static __attribute__((used)) uint32 RBSYS_timer_freq_mhz ...
   --------------------------------------------------------------------------------------------- */

/* Store timer frequency to measurement variable:
 * This is done mainly for MM6 measurement to normalize runtime measurement variables.
 * Initialization is done via cinit to ensure valid content before first MT trigger event (currently at the end of InitTask).
 */
uint32 RBSYS_timer_freq_mhz = RBSYS_TIMERTICKS_PER_US;
/*[[MEASUREMENT*/
/*NAME=RBSYS_timer_freq_mhz*/
/*COMMENT=System timer frequency for converting MM6 results [in MHz] */
/*MTEVENT=c_MT_Default_Task_x4*/
/*]]MEASUREMENT*/


/**
  * @brief Configure timer for Operating System
  *
  * Configure System Timer
  *  - compare 0 for 1ms task and
  *  - compare 1 for x1 task
  * without enabling interrupts.
  *
  * @return void
  */
void RBSYS_SetupOsTimer(void)
{
  uint32 frc, compare0, compare1;

  RBSYS_SchM_Enter_GlobLock();

  frc = RBSYS_SYNCTIME_CNT;

  compare0 = frc + RBSYS_convertUsecToTimerTicks(DELAY_init_TO_1ms_US);
  compare1 = frc + RBSYS_convertUsecToTimerTicks(DELAY_init_TO_1ms_US + DELAY_1ms_TO_x1_US);

  RBSYS_SYNCTIME_CMP0 = compare0;
  RBSYS_SYNCTIME_CMP1 = compare1;

  RBMESG_SendMESG(RBMESG_Task1msFirstTickCtr, compare0);
  RBMESG_SendMESG(RBMESG_TaskBaseCtrlFirstTickCtr, compare1);


  // Clear Pending interrupt requests + Enable Interrupts if necessary
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    STM0STC = 0x10;
    STM0STC = 0x20;
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    RBSYS_SYNCTIME_CLRINT = 0x1Fu;       //< Clear all pending Interrupts
    RBSYS_SYNCTIME_INTPULSEENCFG = 0x5u; //< Enable Interrupts for CMP0 and CMP1
  #endif

  RBSYS_SchM_Exit_GlobLock();
}



/**
 * @brief Enable timer IRQs for Operating System
 *
 * Enable core specific System Timer interrupts - therefore function must be called on both cores.
 * But it must be ensured, that OS timers are still configured via #RBSYS_SetupOsTimer (done only on one core)!
 *
 * @return void
 */
void RBSYS_EnableOsTimerIRQs(void)
{
  unsigned int core_id = RBSYS_getCoreID();

  // clear pending interrupt flags at interrupt controller 1 and enable corresponding IRQs core-specific

  #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    if( core_id == OS_CORE_FOR_ISRCommonTimer )
    {
      RBSYS_ClearPendingIRQ_ISRCommonTimer();
      RBSYS_EnableIRQ_ISRCommonTimer();
    }
  #else
    if (core_id == OS_CORE_FOR_ISRSTM04)
    {
      RBSYS_ClearPendingIRQ_STM04();
      RBSYS_EnableIRQ_STM04();
    }
    if (core_id == OS_CORE_FOR_ISRSTM05)
    {
      RBSYS_ClearPendingIRQ_STM05();
      RBSYS_EnableIRQ_STM05();
    }
  #endif
}


#if (RBFS_TaskSync == RBFS_TaskSync_ON)



  /**
   * @brief Control System Timer ticks
   *
   * System Timer (used by OS for task scheme) could be synchronized with this service.
   * Limitation of timer adaptation must be realized outside (=> RBSYS_TaskSync.c).
   *
   * @param[in] delta_ticks  Time to adapt task scheme in ticks
   *            - positive value will prepone the next task activation
   *            - negative value will delay the next task activation
   *
   * @returns the actual controlled timer ticks
   */
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    sint32 RBSYS_STMControlTicks(sint32 delta_ticks)
    {
      uint32 start_tick;
      sint32 diff_to_comp0, diff_to_comp1, min_diff_to_comp;
      sint32 actual_controlled_ticks = 0;

      /* is adaptation required? */
      if (delta_ticks != 0)
      {
        RBSYS_SchM_Enter_GlobLock();

        /* stop timer and get counter value */
        RBSYS_SYNCTIME_STP = RBSYS_SYNCTIME_STPVAL;
        while( (RBSYS_SYNCTIME_STR & RBSYS_SYNCTIME_STRMASK) != 0 )
        {
          /* wait until timer is switched off */
          RBSYS_TEST_INJECTION_StopSystemTimer();
        }
        start_tick = RBSYS_SYNCTIME_CNT;

        if( delta_ticks > 0 )
        {
          /* look for next compare values of channel 1 compare 0 (1ms task) and compare 1 (x1 task) to not overjump the value loosing an interrupt
           * RB_UnsignedDiffToSigned can be used, as the difference between RBSYS_SYNCTIME_CMP0/1 and start_tick is between INT32_MIN and INT32_MAX by design */
          diff_to_comp0 = RB_UnsignedDiffToSigned(RBSYS_SYNCTIME_CMP0, start_tick);
          diff_to_comp1 = RB_UnsignedDiffToSigned(RBSYS_SYNCTIME_CMP1, start_tick);

          /* if a compare value is in the past, calculate the next one in the future
           * adding one cycle time should always be enough to get a positive diff_to_comp, if it's not enough, some timer failure must have happened
           * in that case, diff_to_comp becomes negative, min_diff_to_comp becomes negative and then the time adaption below is skipped */
          if(diff_to_comp0 < 0)
          {
            diff_to_comp0 += (sint32)RBSYS_convertUsecToTimerTicks(CYCLETIME_STM04);
          }
          if(diff_to_comp1 < 0)
          {
            diff_to_comp1 += (sint32)RBSYS_convertUsecToTimerTicks(CYCLETIME_x1);
          }

          /* check limitation of timer adaptation */
          min_diff_to_comp = RB_Min_s32(diff_to_comp0, diff_to_comp1);

          /* only modify counter if not near to a compare value (hint: counter stopped) */
          if (min_diff_to_comp > 2)
          {
            /* is limitation required? */
            if (delta_ticks < (min_diff_to_comp - 2))
            {
              actual_controlled_ticks = delta_ticks;
            }
            else  /* ensure that new count is not equal compare */
            {
              actual_controlled_ticks = (min_diff_to_comp - 2);
            }

            RBSYS_SYNCTIME_CNT = start_tick + (uint32)actual_controlled_ticks;
          }
        }
        else
        {
          /* Introduce active waiting until adapted ticks are consumed. If this is not done,
              SW can see inconsistent time stamps because same time stamp could be seen twice.
              On MCORE it's not sufficient to set the counter back and wait. It's necessary
              to keep the sync counter and wait based on the real timer */
          uint32 time_stamp = RBSYS_getRealtimeTickCtr();
          uint32 wait_time = (uint32) abs(delta_ticks);
          actual_controlled_ticks = delta_ticks;
          while ((RBSYS_getRealtimeTickCtr() - time_stamp) < wait_time) {
            RBSYS_TEST_INJECTION_ProgressTime();
          };
        }

        /* start timer again */
        RBSYS_SYNCTIME_RUN = RBSYS_SYNCTIME_RUNVAL;

        RBSYS_SchM_Exit_GlobLock();
      }

      return actual_controlled_ticks;
    }

  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

    /* rbsys_SynctimeAdaptedTicks contains the sum of adapted ticks
     *
     *   Historically, the Synctime value has been adapted to accelerate / decelerate the task scheme.
     *   With the new concept, the Synctime counter is free-running, the interrupt compare values are being adapted and
     *   the sum of adapted ticks is represented by rbsys_SynctimeAdaptedTicks (value may over-/underflow).
     *
     *   Therefore, the Synctime is now calculated as follows:
     *
     *       Synctime = SyncTimeCnt (e.g. HW-Counter) + rbsys_SynctimeAdaptedTicks (sum of adaptations)
     *
     *   ATTENTION: DO NOT USE rbsys_SynctimeAdaptedTicks without the Synctime-Counter value, because a positive value
     *              may also represent a deceleration of the task scheme (over-/underflow of unsigned int is used!)
     */
    static uint32 rbsys_SynctimeAdaptedTicks = 0u;
    uint32 RBSYS_GetSynctimeAdaptedTicks(void)
    {
      return rbsys_SynctimeAdaptedTicks;
    }

    /**************************************************************************************************************
     * There are certain requirements when adapting the CMP values:                                               *
     *   T: Current SynctimeCnt - CMP must not be set to exactly this value, but may already be set to this value *
     *   C: Compare Cnt Value                                                                                     *
     *   x: represents a range - the CMP must not be set into this range, but may already be inside the range     *
     *                                                                                                            *
     * The following scenarios do only apply for the X1 task chain, because the adapting process has to be        *
     * executed in the fastest task!                                                                              *
     *                                                                                                            *
     * .................................................Txxxxxx...................................................*
     *                                                                                                            * Additional explanation:
     * Scenario 0: ..................C..................Txxxxxx...................................................* <- IRQ is pending, but Compare has not been adapted in ISR yet
     * Scenario 1: .....................................T/Cxxxx...................................................* <- Unclear if IRQ is pending (or about to be), because T is increasing continuously
     * Scenario 2: .....................................TxxxCxx...................................................* <- IRQ is not pending, but could be soon, because T is increasing continuously
     * Scenario 3: .....................................Txxxxxx..............C....................................* <- IRQ is not pending
     *                                                                                                            *
     * Hereby, we derive the following requirements:                                                              *
     *   1. If C == T or C in range X, dont modify any Compare!                                                   *
     *   2. Acceleration ("Move C to the left"):                                                                  *
     *        If C > T, C shall only be reduced up to a limit T+x (max_allowed_reduction = C -(T+x) = C -T -x)    *
     *        If C < T, no limit is required                                                                      *
     *   3. Deceleration: ("Move C to the right")                                                                 *
     *        If C > T, no limit is required                                                                      *
     *        If C < T, C shall only be increased up to a limit T-1 (max_allowed_increase = T -1 -C)              *
     *                                                                                                            *
     *   4. Generic Requirement: Adaptation is limited to 2% of corresponding task chain                          *
     *      (see RBSYS_TASKSCHEME_ADJUST_MAX_PERCENT)! -> already covered by caller!                              *  
     **************************************************************************************************************/

    /** Compare values are being adapted while Timer is running. Adapting the Compares must be finished before timer
      * reaches any Compare value. Therefore, if any Compare is closer than 5us to the Counter value, adaption is rejected. */
    #define RBSYS_TASKSYNC_BUFFER_TIME (RBSYS_convertUsecToTimerTicks(5))

    static inline sint32 rbsys_STMControlTicks_LimitedAccelerationTicks(sint32 delta_ticks, sint32 diff_to_compare)
    {
      sint32 delta_ticks_limited;

      assert( delta_ticks > 0 ); // Sanity Check: Should not be called for deceleration

      if( diff_to_compare > 0 )
      {
        sint32 delta_ticks_max;
        assert( diff_to_compare > RBSYS_TASKSYNC_BUFFER_TIME ); // Sanity Check: Interface should not be called if Compare is inside range x

        delta_ticks_max = diff_to_compare - RBSYS_TASKSYNC_BUFFER_TIME;
        if( delta_ticks > delta_ticks_max )
        {
          delta_ticks_limited = delta_ticks_max;
        }
        else
        {
          delta_ticks_limited = delta_ticks;
        }
      }
      else
      {
        // no limit
        delta_ticks_limited = delta_ticks;
      }

      return delta_ticks_limited;
    }

    static inline sint32 rbsys_STMControlTicks_LimitedDecelerationTicks(sint32 delta_ticks, sint32 diff_to_compare )
    {
      sint32 delta_ticks_limited;

      assert( delta_ticks < 0 ); // Sanity Check: Should not be called for acceleration

      if( diff_to_compare > 0 )
      {
        // no limit
        delta_ticks_limited = delta_ticks;
      }
      else
      {
        sint32 delta_ticks_max = diff_to_compare + 1;
        if( delta_ticks /* e.g. -6 */ < delta_ticks_max /* e.g. -5 */ )
        {
          delta_ticks_limited = delta_ticks_max;
        }
        else
        {
          delta_ticks_limited = delta_ticks;
        }
      }

      return delta_ticks_limited;
    }

    sint32 RBSYS_STMControlTicks(sint32 delta_ticks)
    {
      uint32 start_tick;
      sint32 diff_to_comp0, diff_to_comp1, min_diff_to_comp;
      sint32 actual_controlled_ticks = 0;


      /* is adaptation required? */
      if (delta_ticks != 0)
      {
        RBSYS_SchM_Enter_GlobLock();

        start_tick = RBSYS_SYNCTIME_CNT;

        /* look for next compare values of channel 1 compare 0 (1ms task) and compare 1 (x1 task) to not overjump the value loosing an interrupt
          * RB_UnsignedDiffToSigned can be used, as the difference between RBSYS_SYNCTIME_CMP0/1 and start_tick is between INT32_MIN and INT32_MAX by design */
        diff_to_comp0 = RB_UnsignedDiffToSigned(RBSYS_SYNCTIME_CMP0, start_tick);
        diff_to_comp1 = RB_UnsignedDiffToSigned(RBSYS_SYNCTIME_CMP1, start_tick);

        if( ((diff_to_comp0 < 0) || (diff_to_comp0 > RBSYS_TASKSYNC_BUFFER_TIME)) &&
            ((diff_to_comp1 < 0) || (diff_to_comp1 > RBSYS_TASKSYNC_BUFFER_TIME)) ) //< Requirement 1
        {
          uint32 delta_ticks_limited;

          if( delta_ticks > 0 ) //< acceleration (preponing of Compare)
          {
            sint32 accel_ticks_comp0 = rbsys_STMControlTicks_LimitedAccelerationTicks(delta_ticks, diff_to_comp0);
            sint32 accel_ticks_comp1 = rbsys_STMControlTicks_LimitedAccelerationTicks(delta_ticks, diff_to_comp1);

            actual_controlled_ticks = RB_Min_s32(accel_ticks_comp0, accel_ticks_comp1); //< both values are positive, so value closest to 0 is used (Min)
          }
          else //< deceleration
          {
            sint32 decel_ticks_comp0 = rbsys_STMControlTicks_LimitedDecelerationTicks(delta_ticks, diff_to_comp0);
            sint32 decel_ticks_comp1 = rbsys_STMControlTicks_LimitedDecelerationTicks(delta_ticks, diff_to_comp1);

            actual_controlled_ticks = RB_Max_s32(decel_ticks_comp0, decel_ticks_comp1); //< both values are negative, so value closest to 0 is used (Max)
          }

          /** Logic:
            *  - acceleration: actual_controlled_ticks is positive, reduce Interrupt Compare value
            *  - deceleration: actual_controlled_ticks is negative, increase Interrupt Compare value (double negative) */
          RBSYS_SYNCTIME_CMP0 -= actual_controlled_ticks;
          RBSYS_SYNCTIME_CMP1 -= actual_controlled_ticks;

          RBSYS_DSB(); //< ensure that Compare Registers have been updated
        }

        RBSYS_SchM_Exit_GlobLock();
      }

      rbsys_SynctimeAdaptedTicks += actual_controlled_ticks;

      return actual_controlled_ticks;
    }
  #endif

  /**
   * @brief GetTimeToNextBaseCycle
   *
   * @note This function must be called in x1 task, otherwise a RBSYS failure will be reported!
   *
   * @returns timer ticks to next x1 base-cycle activation
   */
  uint32 RBSYS_GetTimeToNextBaseCycle(void)
  {
    uint32 frc, cmp, result;

    RBSYS_TaskType current_task = RBSYS_GetCurrentTask();

    /* ensure that function is only called within x1 tasks, which simplifies timer overflow handling */
    if ((current_task == RBSYS_TaskType_TaskBaseCtrlCycx1High) || (current_task == RBSYS_TaskType_TaskBaseCtrlCycx1Low))
    {
      RBSYS_SchM_Enter_GlobLock();

      /* Base-cycle activations are triggered by evaluating the System Timer sync time registers.
       * Note: Order of reading out register values is not important, because function is called in x1 task.
       *       So frc must always be smaller than cmp - otherwise OS error must be reported because x1 task is not finished and still reactivated.
       */
      frc = RBSYS_SYNCTIME_CNT;
      cmp = RBSYS_SYNCTIME_CMP1;

      RBSYS_SchM_Exit_GlobLock();

      /* simply subtract compare register and current counter, as there is no overflow check necessary because function is called in x1 task */
      result = (uint32) (cmp - frc);
    }
    else
    {
      RBSYS_setSYSErrorHook(RBSYS_Error_WrongAPIcalled, ((uint32)&RBSYS_GetTimeToNextBaseCycle));
      result = 0;
    }

    return result;
  }

#endif


/** @} */
/* End ingroup RBSYS */
