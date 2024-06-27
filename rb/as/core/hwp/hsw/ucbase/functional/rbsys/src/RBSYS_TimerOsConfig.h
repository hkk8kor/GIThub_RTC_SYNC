#ifndef RBSYS_TIMEROSCONFIG_H__
#define RBSYS_TIMEROSCONFIG_H__

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


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSync,
                          RBFS_TaskSync_ON,
                          RBFS_TaskSync_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTask0p5ms,
                          RBFS_SysTask0p5ms_OFF,
                          RBFS_SysTask0p5ms_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

extern void RBSYS_SetupOsTimer(void);
extern void RBSYS_EnableOsTimerIRQs(void);

#if (RBFS_TaskSync == RBFS_TaskSync_ON)
  extern sint32 RBSYS_STMControlTicks(sint32 delta_ticks);
#endif


#define CYCLETIME_0p5ms            (500)
#define CYCLETIME_1ms             (1000)
#define CYCLETIME_x1              (5000)

#define DELAY_init_TO_1ms_US       (200)

#if (RBFS_SysTask0p5ms ==  RBFS_SysTask0p5ms_ON)
  #define DELAY_1ms_TO_x1_US       (300)           /* increase x1 delay in case of available 0p5ms task */
  #define CYCLETIME_STM04           CYCLETIME_0p5ms
#else
  #define DELAY_1ms_TO_x1_US       (200)
  #define CYCLETIME_STM04           CYCLETIME_1ms
#endif

/* Abstraction of timer registers used as System Timer */
#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  #define RBSYS_SYNCTIME_STP      STM0TT
  #define RBSYS_SYNCTIME_STPVAL   (0x2)
  #define RBSYS_SYNCTIME_STR      STM0CSTR
  #define RBSYS_SYNCTIME_STRMASK  (0x2u)
  #define RBSYS_SYNCTIME_CNT      STM0CNT1
  #define RBSYS_SYNCTIME_CMP0     STM0CMP1A
  #define RBSYS_SYNCTIME_CMP1     STM0CMP1B
  #define RBSYS_SYNCTIME_RUN      STM0TS
  #define RBSYS_SYNCTIME_RUNVAL   (0x2)
#elif(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
  #define RBSYS_SYNCTIME_STP      TPTMPE0TPTM0USTP
  #define RBSYS_SYNCTIME_STPVAL   (0x1)
  #define RBSYS_SYNCTIME_STR      TPTMPE0TPTM0USTR
  #define RBSYS_SYNCTIME_STRMASK  (0x1u)
  #define RBSYS_SYNCTIME_CNT      TPTMPE0TPTM0UCNT0
  #define RBSYS_SYNCTIME_CMP0     TPTMPE0TPTM0UCMP00
  #define RBSYS_SYNCTIME_CMP1     TPTMPE0TPTM0UCMP01
  #define RBSYS_SYNCTIME_RUN      TPTMPE0TPTM0URRUN
  #define RBSYS_SYNCTIME_RUNVAL   (0x1)
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  #define RBSYS_SYNCTIME_CNT           (GST_0.ARC[0].READ)
  #define RBSYS_SYNCTIME_RELOAD        (GST_0.ARC[0].RELOAD_VALUE)
  #define RBSYS_SYNCTIME_EXPIRATION    (GST_0.ARC[0].EXPIRY_CFG)
  #define RBSYS_SYNCTIME_STP           (GST_0.ARC[0].CTRL)
  #define RBSYS_SYNCTIME_STPVAL        (1u<<20)
  #define RBSYS_SYNCTIME_STR           (GST_0.ARC[0].STATUS)
  #define RBSYS_SYNCTIME_STRMASK       (1u<<12)
  #define RBSYS_SYNCTIME_RUN           (GST_0.ARC[0].CTRL)
  #define RBSYS_SYNCTIME_RUNVAL        (1u<<16)
  #define RBSYS_SYNCTIME_CMP0          (GST_0.ARC[0].COMPARE_1_CFG)
  #define RBSYS_SYNCTIME_CMP1          (GST_0.ARC[0].COMPARE_2_CFG)
  #define RBSYS_SYNCTIME_CLRINT        (GST_0.ARC[0].INT_CLR)
  #define RBSYS_SYNCTIME_INT_STATUS    (GST_0.ARC[0].INT_STATUS)
  #define RBSYS_SYNCTIME_INTPULSEENCFG (GST_0.ARC[0].INT_PULSE_EN_CFG)
#else
  #error ("Not yet implemented for this uC family")
#endif

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
