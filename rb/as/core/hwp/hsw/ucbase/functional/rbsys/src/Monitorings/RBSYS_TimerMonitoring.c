/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief System Timer Monitoring
 *
 * This unit contains a timer monitoring between the synchronized time base
 * (which will be adapted in case of task scheme synchronization) and the
 * real time base (which is not adapted in any case).
 *
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_SystemTimer.h"
#include "RBSYS_ErrorHooks.h"
#include "RBSYS_uCModuleEnable.h"   // for RBSYS_TAUD0_SetToRunMode
#include "RBSYS_TestInjection.h"
#include "RBSYS_ClockSettings.h"

/* realized interfaces */
#include "RBSYS_Subsystem.h"

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTask0p5ms,
                          RBFS_SysTask0p5ms_ON,
                          RBFS_SysTask0p5ms_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSync,
                          RBFS_TaskSync_ON,
                          RBFS_TaskSync_OFF);

/* ------------------------------------------------------------------------------------------------
   SW workaround for GHS compiler incident 65175:
   __attribute__((used)) will not work as expected on current available GHS compiler suite.
   Due to an internal compiler issue it's not possible to declare the measurement variable
   RBSYS_TimerMonitoring_sync_dev__debug and RBSYS_TimerMonitoring_rt_dev__debug
   as static. The compiler will still remove the whole variable even with usage of the
   attribute used because there is no visible reference. This problem was fixed in the
   v2016.5 final release, but as long as we are using 2015.1. we've to keep the external visibility.

   static __attribute__((used)) uint32 RBSYS_TimerMonitoring_sync_dev__debug;
   static __attribute__((used)) uint32 RBSYS_TimerMonitoring_rt_dev__debug;
   --------------------------------------------------------------------------------------------- */


uint32 RBSYS_TimerMonitoring_sync_dev__debug;    /* just for MM6 debug */
/*[[MEASUREMENT*/
/*NAME=RBSYS_TimerMonitoring_sync_dev__debug*/
/*COMMENT=Delta of two succeeding tasks from the synchronized time base [timer ticks]*/
/*MTEVENT=c_MT_Default_Task_x2*/
/*]]MEASUREMENT*/

uint32 RBSYS_TimerMonitoring_rt_dev__debug;     /* just for MM6 debug */
/*[[MEASUREMENT*/
/*NAME=RBSYS_TimerMonitoring_rt_dev__debug*/
/*COMMENT=Delta of two succeeding tasks from the real time base [timer ticks]*/
/*MTEVENT=c_MT_Default_Task_x2*/
/*]]MEASUREMENT*/

static uint32 RBSYS_TimerMonitoring_sync_last;
/*[[MEASUREMENT*/
/*NAME=RBSYS_TimerMonitoring_sync_last*/
/*COMMENT=Last timer ticks of the synchronized time base (adapted in case of task scheme synchronization)*/
/*MTEVENT=c_MT_Default_Task_x2*/
/*]]MEASUREMENT*/

static uint32 RBSYS_TimerMonitoring_rt_last;
/*[[MEASUREMENT*/
/*NAME=RBSYS_TimerMonitoring_rt_last*/
/*COMMENT=Last timer ticks of the real time base (not adapted in any case)*/
/*MTEVENT=c_MT_Default_Task_x2*/
/*]]MEASUREMENT*/



/* 2%+2%: within 1ms real-time two task scheme synchronization adaptations can happen (2*1ms tasks)
   +40..60us in case of small real-time deltas between two x2 tasks (very worst case; i.e. <1ms) */
#define TIMERMON_MAX_DEV        ((2.0*RBSYS_TASKSCHEME_ADJUST_MAX_PERCENT)/100.0)
#define TIMERMON_DEV_ADDITONAL  ((unsigned)RBSYS_convertUsecToTimerTicks(50))


/**
 * @brief System Timer Monitoring
 *
 * A simple timer monitoring between both time bases (synchronized time base which will be adapted in case of task scheme
 * synchronization and the real time base which is not adapted in any case) is implemented to detect hardware (timer) failures.
 * The synchronized time base itself is checked using the OS mechanisms and the task monitoring.
 *
 * The timer monitoring strategy is quite simple and done in the following way. Between two tasks the delta runtime is measured
 * (using the real-time timer) and compared against the synchronized timer. It's important that only differences between two
 * succeeding tasks are monitored to avoid difference accumulation. The allowed deviation is the maximum adjust factor.
 * To cope with rounding issues and the maximum jitter, the max allowed deviation is twice the task scheme adjust value plus a constant
 * value of 50 us.
 *
 * @return void
 */
void RBSYS_PRC_TimerMonitoring(void)
{
  uint32 timer_sync, timer_rt;
  static uint8 init_done = 0;

  RBSYS_SchM_Enter_GlobLock();

  timer_sync = RBSYS_getSynctimeTickCtr();
  timer_rt   = RBSYS_getRealtimeTickCtr();

  RBSYS_SchM_Exit_GlobLock();

  if (init_done != 0)
  {
    uint32 delta_r = timer_rt - RBSYS_TimerMonitoring_rt_last;
    uint32 delta_s = timer_sync - RBSYS_TimerMonitoring_sync_last;

    /* STM free running counter max<100MHz=10ns -> running in x2
      => w.c. 20ms -> delta_stm = 2000000 ticks -> shift factor can be 1024, no overflow in delta_r_hi calculation  */
    static_assert(RBSYS_STM_CLK_KHZ <= 100000, "System Timer is configured faster than Timer Monitoring is expecting");

    /* delta_limit_upper/lower = delta_realtime_actual * round_up((1.0 + allowed_deviation) */
    uint32 delta_r_hi = (delta_r*((uint32)(((1.0+TIMERMON_MAX_DEV)*1024.0)+0.5)))/1024;
    uint32 delta_r_lo = (delta_r*((uint32)(((1.0-TIMERMON_MAX_DEV)*1024.0)+0.5)))/1024;

    delta_r_hi += TIMERMON_DEV_ADDITONAL;
    delta_r_lo  = (delta_r_lo > TIMERMON_DEV_ADDITONAL) ? (delta_r_lo-TIMERMON_DEV_ADDITONAL) : 0;

    /* check for <= to detect deltas of 0 for both STM counters */
    if ((delta_s >= delta_r_hi) || (delta_s <= delta_r_lo))
    {
      /* ignore last 6 bits (div-by-64) to get ~80ms in 16bit; lost resolution 1.3..2.3 us */
      RBSYS_setSYSErrorHook(RBSYS_Error_TimerMonitoring, ((delta_r>>6)<<16)|((delta_s>>6)&0xFFFFU));
    }

    RBSYS_TimerMonitoring_sync_dev__debug = delta_s;   /* just for debug */
    RBSYS_TimerMonitoring_rt_dev__debug = delta_r;    /* just for debug */
  }
  else
  {
    init_done = 1;
  }

  RBSYS_TimerMonitoring_sync_last = timer_sync;
  RBSYS_TimerMonitoring_rt_last = timer_rt;
}



#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )

  // Calculation of maximum TPTM interrupt interval deviation in TAUD0 ticks
  #define RBSYS_TAUD_TICKS_PER_US  ((unsigned)(RBSYS_TAUD0_CK0_CLK_KHZ / 1000))
  #if (RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_ON)
    #define RBSYS_TAUD_TICKS_PER_INTERRUPT (500 * RBSYS_TAUD_TICKS_PER_US)
  #else
    #define RBSYS_TAUD_TICKS_PER_INTERRUPT (1000 * RBSYS_TAUD_TICKS_PER_US)
  #endif

  /* Allowed deviation:
   *   - Timer deviation:       +-1%
   *   - Task scheme adaptions: +-2% (RBFS_TaskSync_ON) */
  #define RBSYS_TIMER_MAX_DEVIATION_DEFAULT  (0.01)
  #define RBSYS_TIMER_MAX_DEVIATION_TASKSYNC (RBSYS_TASKSCHEME_ADJUST_MAX_PERCENT/100.)

  // 1% deviation based on highest prio task + task scheme adaptions
  #if (RBFS_TaskSync == RBFS_TaskSync_ON)
    #define RBSYS_TAUD_TICKS_MAX_DEVIATION ((uint32)((float32)RBSYS_TAUD_TICKS_PER_INTERRUPT * (RBSYS_TIMER_MAX_DEVIATION_DEFAULT + RBSYS_TIMER_MAX_DEVIATION_TASKSYNC)))
  #else
    #define RBSYS_TAUD_TICKS_MAX_DEVIATION ((uint32)((float32)RBSYS_TAUD_TICKS_PER_INTERRUPT * RBSYS_TIMER_MAX_DEVIATION_DEFAULT))
  #endif

  // Base address of TAUD0CMORm registers (16 bit register, but 4 byte aligned)
  static volatile const uint16* RBSYS_TAUD0CMOR = &TAUD0CMOR0;

  /**
  *@brief TPTM Timer Interrupt Monitoring
  *
  * Timer Interrupt monitoring that is checking, that the time interval between two INTTPTMU00 interrupts does not deviate more than 1% ( + max task scheme deviation) from the configured interval.
  * This is done by connecting the interrupt signal INTTPTMU00 via PIC1 to TAUD0 timer using PIC1's Trigger Pulse Width Measurement Function and TAUD's Input Pulse Interval Measurement Function.
  * On each interrupt pulse, TAUD0 captures the current counter value and resets the counter.
  * This captured value has to be checked in every ISR triggered by INTTPTMU00.
  * Possible enhancement for the future: read out captured values via DMA to be able to check multiple values in a lower prio task.
  */

  void RBSYS_PRC_TimerInterruptMonitoring(void)
  {
    static boolean isFirstRun = TRUE, isSecondRun = FALSE;
    uint32 capturedTicks, overflowFlag, i;
    uint32 runningTimers = 0x0u;

    // Configure PIC1 and TAUD0 on first run following procedure in HW UM Rev.1.10 p. 5334
    if(isFirstRun)
    {
      // 1. Set PIC1 selector

      /** PIC1:
      * Configure PIC1 for Trigger Pulse Width Measurement Function with TPTM0 INTTPTMU00 and TAUD0 Channel 0
      * Register settings are described in HW UM Rev.1.10 p. 5386
      */

      PIC1REG31 = (0x31u << 6); // Selects INTTPTMU00 as input signal and TAUD0TTIN0 as output signal
      // Write 0 (value after reset) to PIC1TAUD0SEL[5:0] and PIC1REG30[22,17:16,1:0]) (see UM Rev.1.10 p. 5387 note under first table)
      PIC1TAUD0SEL &= ~0x3Fu;
      PIC1REG30 &= ~(((uint32) 0x1u << 22) | ((uint32) 0x3u << 16) | 0x3u);

      // 2. Set TAUD0

      /** TAUD0:
      * Configure TAUD0 Channel 0 for TAUDnTTINm Input Pulse Interval Measurement Function, see HW UM Rev.1.10 p. 3586.
      * For measuring INTTPTMU00 only TAUD0-2 can be used, see HW UM Rev.1.10 p. 5386.
      * As they are 16 bit counter, the counter clock must not be so fast, that the slowest INTTPTMU00 interrupt interval still fits (1ms).
      * Therefore CK0 with prescaler /2 is used to get an operating clock rate of 40MHz, half of TPTM clock (40 ticks per usec, 1ms = 40000 ticks fits in 16 bit).
      * TAUD0 is set to capture mode, trigger is set to valid edge on TAUD0TTIN00, valid edges are both rising and falling edges.
      */

      // Start up TAUD0 from standby
      RBSYS_TAUD0_SetToRunMode();

      // Stop TAUD0 Channel 0, must only be configured when stopped
      TAUD0TT = 0x1u;
      while((TAUD0TE & 0x1u) != 0x0u)
      {
        RBSYS_TEST_INJECTION_StopTAUD0Channel(0);
      }

      // CK0 prescaler (TAUD0TPS) only rewriteable if all counters using CK0 are stopped.
      for(i = 1; i < 16; i++)
      {
        // Stop all running counters that are using CK0 and remember which where stopped to restart them later (i*2 because TAUD0CMORm is 16 bit register, but 4 byte aligned)
        boolean isEnabled =  (TAUD0TE & ((uint16) 0x1u << i)) != 0x0u;
        boolean isUsingCK0 = ((RBSYS_TAUD0CMOR[i*2] >> 14) & 0x3u) == 0x0u;

        if( isEnabled && isUsingCK0 )
        {
          runningTimers |= (uint32) 0x1u << i;
          TAUD0TT |= (uint16) 0x1u << i;

          do
          {
            isEnabled = (TAUD0TE & ((uint16) 0x1u << i)) != 0x0u;
            RBSYS_TEST_INJECTION_StopTAUD0Channel(i);
          }
          while( isEnabled );

        }
      }
      TAUD0TPS = (TAUD0TPS & 0xFFF0u) | 0x1u; // Set prescaler for CK0 to /2^1 = /2 with clock supply CLK_HSB == 80MHz this is 40 MHz => 40 ticks per us.

      // Restart all other counters using CK0
      for(i = 0; i < 16; i++)
      {
        if((runningTimers & ((uint32) 0x1u << i)) != 0x0u)
        {
          TAUD0TS |= (uint16) 0x1u << i;
        }
      }

      /* Register settings according to HW UM Rev.1.10 p. 3585
      * Use CK0 as operation clock and count clock, master/slave setting does not matter, start trigger is valid detected edge,
      * overflow has to be cleared manually, use capture mode, no interrupt at start (is not used anyway)
      *           operation clock       | count clock           | master/slave          | start trigger        | overflow behaviour   | operating mode       | interrupt on start */
      TAUD0CMOR0 = ((uint32) 0x0u << 14) | ((uint32) 0x0u << 12) | ((uint32) 0x0u << 11) | ((uint32) 0x1u << 8) | ((uint32) 0x1u << 6) | ((uint32) 0x2u << 1) | 0x0u;

      // Use both rising and falling edges as valid triggers
      TAUD0CMUR0 = 0x2u;

      // 3. Initialize DT02 to 0 of PIC1
      PIC1INI01 |= 0x7u;
      // 4. Release initialization of DT02 to 0 of PIC1, meaning clarified in attachement of workitem 1309230
      PIC1INI01 &= (~0x7u) & 0xFFu;

      // 5. Start trigger and pulse width measurement (without simultaneous start trigger as TPTM is already running and only one additional timer is used)
      // Enable operation of TAUD0 Channel 0, this starts the counter, so the value captured on the next INTTPTMU00 interrupt has to be discarded
      TAUD0TS = 0x1u;

      isFirstRun = FALSE;
      isSecondRun = TRUE;
    }
    // Ignore first captured value as TAUD0 did not start to count at the last INTTPTMU00 pulse but when the timer was initialized
    else if(isSecondRun)
    {
      isSecondRun = FALSE;
    }
    // After the second run the captured value is valid, check it against the maximum allowed deviation
    else
    {
      capturedTicks = TAUD0CDR0 + (uint32) 1u; // formula according to HW UM Rev.1.10 p. 3583

      overflowFlag  = TAUD0CSR0 & (uint32) 0x1u;

      // capturedTicks has an inaccuracy of +-1 TAUD tick (see attachement of workitem 1309230), so a value of capturedTicks that corresponds exactly to the maximum deviation is considered to be over the maximum deviation
      if(  (overflowFlag != 0)
        || (capturedTicks >= (RBSYS_TAUD_TICKS_PER_INTERRUPT + RBSYS_TAUD_TICKS_MAX_DEVIATION))
        || (capturedTicks <= (RBSYS_TAUD_TICKS_PER_INTERRUPT - RBSYS_TAUD_TICKS_MAX_DEVIATION))
        )
      {
        RBSYS_setSYSErrorHook(RBSYS_Error_TimerInterruptMonitoring, ((overflowFlag << 16) | capturedTicks));
      }
    }
  }
#elif ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  //todo: implement for U2C
#endif /* RBFS_uCFamily_RenesasU2A */


/** @} */
/* End ingroup RBSYS */
