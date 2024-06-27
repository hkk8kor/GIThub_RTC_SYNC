#ifndef RBSYS_SYSTEMTIMER_H__
#define RBSYS_SYSTEMTIMER_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief System timer services
 *
 * This interface provides System Timer services.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_uCRegisters.h"
#include "RBSYS_ClockSettings.h"
#include "RBSYS_Intrinsics.h" // For RBSYS_snooze

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TriggerTimerSupport,
                          RBFS_TriggerTimerSupport_On,
                          RBFS_TriggerTimerSupport_Off);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSync,
                          RBFS_TaskSync_ON,
                          RBFS_TaskSync_OFF);

extern void RBSYS_waitUsecLoop(uint16 time_in_usec);

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_TriggerTimerSupport == RBFS_TriggerTimerSupport_On) )
/**
 * @brief Start Timer to issue a trigger / interrupt when finished
 *
 * System Timer STM0 Channel 0 is used as the timer. Only one timer is running at a time.
 * Any call of this function will overwrite the (potentially) running counter.
 *
 * Hint: This function is used to start SPI transmission at a dedicated time.
 *       Therefore, only STM0Int0 or STM0Int1 can be used -> only supported by STM0 Channel 0 and 2.
 *
 * @returns void
 */
extern void RBSYS_StartTriggerTimer(uint16 time_in_usec);

/**
 * @brief Stop Trigger Timer (see RBSYS_StartTriggerTimer)
 *
 * STM0 Channel 0 is stopped.
 *
 * @returns void
 */
extern void RBSYS_StopTriggerTimer(void);
#endif



/* System Timer (STM):
 *  P1x / U2A: 80 MHz = 12,5 ns per timer tick = 80 ticks per us
 *  Stellar:  100 MHz = 10 ns per timer tick  = 100 ticks per us */
#define RBSYS_TIMERTICKS_PER_US  ((unsigned)(RBSYS_STM_CLK_KHZ / 1000))

/* Macros for converting between system timer ticks and microseconds */
#define RBSYS_convertTimerTicksToUsec(ticks) ((ticks) / RBSYS_TIMERTICKS_PER_US)
#define RBSYS_convertUsecToTimerTicks(usecs) ((usecs) * RBSYS_TIMERTICKS_PER_US)

/* Timer counter register used as System Timer */
#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  #define RBSYS_SystemTimerSynctimeCnt        (STM0CNT1) /* STM0 channel 1 */
  #define RBSYS_SystemTimerRealtimeCnt        (STM0CNT2) /* STM0 channel 2 */
  #define RBSYS_SystemTimerRealtimeCntAddress ((uint32)&STM0CNT2)
#elif(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
  #define RBSYS_SystemTimerSynctimeCnt        (TPTMPE0TPTM0UCNT0) /* TPTM0 channel 0 */
  #define RBSYS_SystemTimerRealtimeCnt        (TPTMPE0TPTM0UCNT1) /* TPTM0 channel 1 */
  #define RBSYS_SystemTimerRealtimeCntAddress ((uint32)&TPTMPE0TPTM0UCNT1) /* TPTM0 channel 1 */
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  #define RBSYS_SystemTimerSynctimeCnt        (GST_0.ARC[0].READ)       /* GST channel 1 */
  #define RBSYS_SystemTimerRealtimeCnt        (RBSYS_MRRC(15,0,14))     /* GenericTimer (Core specific register with common time base) */
  #define RBSYS_SystemTimerRealtimeCntAddress ((uint32)&(GST_0.NSC_LWORD_READ)) /* GenericTimer common time base (memory mapped) */
  #if( RBFS_TaskSync == RBFS_TaskSync_ON )
    extern uint32 RBSYS_GetSynctimeAdaptedTicks(void);
  #endif
#else
  #error ("Exception: Implementation for this uCFamily is missing")
#endif


/**
 * @brief Get synchronized counter ticks
 *
 * System Timer (used for OS), which will be adapted in case of task scheme synchronization
 * (inline function for efficiency)
 *
 * @returns System Timer free running counter ticks of synchronized timer [unit: device dependent, use conversion macros!]
 */
static inline uint32 RBSYS_getSynctimeTickCtr(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    return RBSYS_SystemTimerSynctimeCnt;
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    #if( RBFS_TaskSync == RBFS_TaskSync_ON )
      return (RBSYS_SystemTimerSynctimeCnt + RBSYS_GetSynctimeAdaptedTicks());
    #else
      return RBSYS_SystemTimerSynctimeCnt;
    #endif
  #endif
}


/**
 * @brief Get real-time counter ticks
 *
 * System Timer (for real-time clock), which is not adapted in any case
 * (inline function for efficiency)
 *
 * @returns System Timer free running counter ticks of real-time timer [unit: device dependent, use conversion macros!]
 */
static inline uint32 RBSYS_getRealtimeTickCtr(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

    return RBSYS_SystemTimerRealtimeCnt;

  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

    uint64 realtime_u64; uint32 realtime_u32;

    // ensure that all previous instructions are finished before reading the counter
    // see ARMv8 Architecture RM "ARM DDI 0487A.k_iss10775" p.4222
    RBSYS_ISB();

    realtime_u64 = RBSYS_SystemTimerRealtimeCnt;
    realtime_u32 = (uint32)(realtime_u64 & 0xFFFFFFFFu);
    return realtime_u32;

  #endif
}


/**
 * @brief RBSYS_startUsecTimer
 *
 * @param [out] start_tick  Get current counter ticks of real-time timer for starting individual time measurement
 *
 * @return void
 */
static inline void RBSYS_startUsecTimer(uint32* const start_tick)
{
  *start_tick = RBSYS_getRealtimeTickCtr();
}

/**
 * @brief RBSYS_isUsecTimerElapsed
 *
 * @param[in] start_tick    Counter ticks when individual time measurement started via RBSYS_startUsecTimer
 * @param[in] time_in_usec  Individual time in usec to check if timer is elapsed (up to a maximum of 65 milliseconds)
 *
 * Attention: will overflow if 65 milliseconds is exceeded
 *
 * @returns >0 if timer is elapsed, otherwise 0
 */
static inline uint32 RBSYS_isUsecTimerElapsed(const uint32* const start_tick, uint16 time_in_usec)
{
  return (((uint32)(RBSYS_getRealtimeTickCtr() - *start_tick)) > ((uint32)RBSYS_convertUsecToTimerTicks(time_in_usec))) ? 1u : 0u;
}

/**
 * @brief RBSYS_isUsecTimerElapsed_ExtendedRange
 *
 * @param[in] start_tick    Counter ticks when individual time measurement started via RBSYS_startUsecTimer
 * @param[in] time_in_usec  Individual time in usec to check if timer is elapsed (up to a maximum of 53 seconds (P1x, U2A, U2C) / 42 seconds (Stellar))
 *
 * Attention: assert covers that time_in_used is in defined range
 *
 * @returns TRUE if timer is elapsed, otherwise FALSE
 */
static inline boolean RBSYS_isUsecTimerElapsed_ExtendedRange(const uint32* const start_tick, uint32 time_in_usec)
{
  assert( time_in_usec < RBSYS_convertTimerTicksToUsec(UINT32_MAX) );
  return ((RBSYS_getRealtimeTickCtr() - *start_tick) > RBSYS_convertUsecToTimerTicks(time_in_usec));
}

/**
 * @brief Wait until Timer is elapsed
 *
 * @param[in] start_tick    Counter ticks when individual time measurement started via RBSYS_startUsecTimer
 * @param[in] time_in_usec  Individual time in usec to wait for timer to elapse (up to a maximum of 65 milliseconds)
 *
 * Attention: will overflow if 65 milliseconds is exceeded
 *
 * @return void
 */
static inline void RBSYS_waitUntilTimerElapsed(const uint32* const start_tick, uint16 time_in_usec)
{
  while (RBSYS_isUsecTimerElapsed(start_tick, time_in_usec) == 0u) {
    RBSYS_snooze();
  }
}

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
