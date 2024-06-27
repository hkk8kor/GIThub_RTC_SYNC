/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief System Timer (STM) initialization
 *
 * Timer initialization and timer services
 *
 * This timer functions are placed within a separate source file instead of inline implementation within an interface.
 * So it could be used as single source for bootblock- and FSW-builds.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_uCRegisters.h"         // peripheral labels
#include "RBSYS_Intrinsics.h"
#include "RBSYS_TestInjection.h"
#include "RBSYS_CpuInfo.h"
//#include "Os.h" // todo: remove if not needed
//#include "Os_ConfigInterrupts.h"

/* realized interfaces */
#include "RBSYS_TimerSetup.h"
#include "RBSYS_SystemTimer.h"



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWCapsule,
                          RBFS_TPSWCapsule_OFF,
                          RBFS_TPSWCapsule_SC3,
                          RBFS_TPSWCapsule_SC4);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TriggerTimerSupport,
                          RBFS_TriggerTimerSupport_On,
                          RBFS_TriggerTimerSupport_Off);

RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_ON,
                          RBFS_MCORE_OFF);


/**
 * @brief Initialization of System Timer
 *
 * System Timer strategy for Renesas P1x with STM:
 * (channel 1 and 2 for STM are always used independent of task scheme synchronization usage)
 *
 * STM 0 channel 1 for OS (counter will be adapted in case of task scheme synchronization)
 *     compare A: 1ms task
 *     compare B: x1 task
 *
 * STM0 channel 2 for real-time clock (real time at least required for task scheme synchronization and not adapted)
 *     compare A: timing protection core 0
 *     compare B: timing protection core 1
 *
 *
 * System Timer strategy for Renesas U2A with TPTM:
 * (channel 0 and 1 for TPTM are always used independent of task scheme synchronization usage)
 *
 * TPTM 0 channel 0 for OS (counter will be adapted in case of task scheme synchronization)
 *     compare 0: 1ms task
 *     compare 1: x1 task
 *
 * TPTM0 channel 1 for real-time clock (real time at least required for task scheme synchronization and not adapted)
 *     compare 2: timing protection core 0
 *     compare 3: timing protection core 1
 *
 *
 * System Timer strategy for ST Stellar with GST:
 * (ARC0, 1 and 2 for GST are always used independent of task scheme synchronization usage)
 *    ARC0: real-time clock (real time at least required for task scheme synchronization and not adapted)
 *        no compare used
 *    ARC1: for OS sync timer 1 (counter will be adapted in case of task scheme synchronization)
 *        compare 0: 1ms task
 *    ARC2: for OS sync timer 2 (counter will be adapted in case of task scheme synchronization)
 *        compare 0: x1 task
 *
 *    Note: all compares of one ARC generate the same interrupt, therefore different ARCs need to be used for
 *          1ms and x1 task to identify which compare triggered the interrupt
 *    TODO: How to start ARC1 and 2 synchronously? Should another timer be used for task interrupts?
 *    How does OS handle the timers?
 *      -> GST provides clock signal to Generic Timer attached to R52 (separate module for every core)
 *      -> Generic Timer is used for task scheduling
 *      => pro: hypervising per Generic Timer module is possible
 *
 *
 * Hint 1: This function will be used in bootblock and FSW, therefore (re-)configuration within FSW must be considered.
 *
 * Hint 2: Furthermore this function is only allowed to be called after STM FEINT is masked via RBSYS_maskFEINT()!
 *         Current startup order consider masking of STM0 interrupt 8 and STM0 initialization due to the usage of STM0 only.
 *         If STM1 will also be used in future, masking of STM1 interrupt 8 and STM1 initialization must be considered for startup concept of CPU1!
 *
 * ATTENTION: Regarding caution note in U2A HW UM 1.10 page 511:
 * TPTM CMP register may be written while TPTM is running, but care has to be taken, that either (CMP < CNT) or (CNT << CMP) .
 * For more details see emails in HSW Doc.
 *
 * @return void
 */
void RBSYS_InitTimers(void)
{
  if( RBSYS_getCoreID() == RBSYS_CORE_ID_0 )
  {
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)

      /* stop timer counter channel 1 and channel 2 */
      STM0TT = 0x6;

      /* set peripheral clock as input clock for counter channels 0..3 */
      STM0CKSEL = 0x0;

      /* reset counter values for channel 1 and 2 */
      STM0CNT1 = 0x0;
      STM0CNT2 = 0x0;

      /* Configure interrupts:
      * - Set:
      *     interrupt 4 to channel 1 compare 0 (STM0CMP1A)                              | STM0IS[9:8]   = STMINT4[1:0] = 00
      *     interrupt 5 to channel 1 compare 1 (STM0CMP1B)                              | STM0IS[11:10] = STMINT5[1:0] = 00
      *     interrupt 0 to channel 2 compare 0 (STM0CMP2A) --> timing protection core 0 | STM0IS[1:0]   = STMINT0[1:0] = 01
      *     interrupt 1 to channel 2 compare 1 (STM0CMP2B) --> timing protection core 1 | STM0IS[3:2]   = STMINT1[1:0] = 01
      */
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        #if (RBFS_MCORE == RBFS_MCORE_ON)
          STM0IS = ((uint32)0x0u << 10) | ((uint32)0x0u << 8) | (0x1u << 2) | (0x1u << 0);
        #else
          STM0IS = ((uint32)0x0u << 10) | ((uint32)0x0u << 8) | (0x1u << 0);
        #endif
      #else
        STM0IS = ((uint32)0x0u << 10) | ((uint32)0x0u << 8);
      #endif

      /* no reset mask for STMs, i.e. always reset all counters */
      STM0RM = 0x0;

      /* clear status registers */
      STM0STC = 0x000FFFFF;

      /* start timer counter channel 1 and channel 2 */
      STM0TS = 0x6;

    #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))



      /* Stop up timer 0 channels 0 and 1 */
      TPTMPE0TPTM0USTP = 0x3;
      while(TPTMPE0TPTM0USTR != 0)
      {
        /* Wait until timer stopped */
        RBSYS_TEST_INJECTION_StopSystemTimer();
      }

      /* Enable interrupts */
      #if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
        TPTMPE0TPTM0UIEN = ((uint32)0x3u << 10) | (0x3u << 0); // enable interrupt for timer 0, channel 0, compare value 0 to 1 and channel 1, compare value 2 to 3
      #else
        TPTMPE0TPTM0UIEN = 0x3; // enable interrupt for timer 0, channel 0, compare value 0 and 1
      #endif

      /* Configure clock */
      #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        TPTMPE0TPTM0UDIV = 4; // set divider, 400MHz / (4+1) = 80MHz
      #elif(RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
        TPTMPE0TPTM0UDIV = 3; // set divider, 320MHz / (3+1) = 80MHz
      #endif

      /* Start timer*/
      TPTMPE0TPTM0URUN = 0x3; // start channels 0 and 1 of up timer 0 from counter value 0x0

    #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)

      GST_0.CLK_CTRL = 1u;       //< select TIME_BASE_CLK as clock source for GST

      /* Real Time Counter Setup (NSC cannot be halted for configuration) */
      /********************************************************************/

      GST_0.NSC_DEBUG_CFG = (1<<4);                           //< Freeze RealTimer while debugging
      GST_0.NSC_INCSTEP_CFG = 1;                              //< Increment RealTime by 1 (f=100MHz)
      /* Counter events have to be stretched according to Equation 37 (STM X7 RM "RM0482" p. 1842/1843) */
      GST_0.TS[0].UPDATE_EVENT_STRETCH_CFG = (1u<<8)|(1u<<0); //< without this, the Generic Timer is not updated properly - todo: check why
      GST_0.TS[0].SOURCE_SEL_CFG = 0x0;                       //< TimeBaseUnit 0 operates on NSC timebus
      GST_0.TS[0].BIT_SEL_CFG = 0;                            //< TBU0 value is exactly NSC value (no divider)

      /* Hint: Although called Nano Second Counter, the NSC is operated at 100MHz => "10ns Counter" */

      /* Sync Time Counter Setup */
      /***************************/

      GST_0.ARC[0].CTRL             = (1u<<20);      //< stop SyncTimer
      /* Reset behavior like 32-bit overflow counter: reload value 0 when reaching 0xFFFFFFFF */
      GST_0.ARC[0].RELOAD_VALUE     = 0;
      GST_0.ARC[0].EXPIRY_CFG       = 0xFFFFFFFFu;
      GST_0.ARC[0].CFG              = (1u<<16);      //< configure to auto reload mode and increment on GST clock positive edge
      GST_0.ARC[0].INT_PULSE_EN_CFG = 0;             //< deactivate interrupt of SYNCTIME0 timer until Init is finished
      GST_0.ARC[0].DEBUG_CFG        = (1u<<4);       //< enable freeze timer in debug mode
      GST_0.ARC[0].CTRL             = (1u<<16);      //< start SyncTimer
    #else
      assert(0 && "Timer Setup is not yet implemented for this uC family");
    #endif
  } //< RBSYS_getCoreID() == RBSYS_CORE_ID_0


  #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    /* Stellar uses Core-specific timers, therefore both Core have to enable them */
    RBSYS_ISB();
    RBSYS_MCR(15,0,3,14,2,1); //< Enable Generic Timer (Physical) for current core + Mask Interrupt
    RBSYS_ISB();
  #endif
}

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_TriggerTimerSupport == RBFS_TriggerTimerSupport_On) )
  void RBSYS_StartTriggerTimer(uint16 time_in_usec)
  {
    /* Clear the compare match event flag & overflow flag for channel 0 and counter 0 */
    STM0STC = 0x10001u;

    /* Clear the counter for channel 0 and counter 0 */
    STM0CNT0L = 0x00;
    STM0CNT0H = 0x00;

    STM0CMP0AL = (uint32)RBSYS_convertUsecToTimerTicks(time_in_usec);
    STM0CMP0AH = 0;

    /* Start the timer channel 0 and counter 0 */
    STM0TS = 0x01u;
  }

  void RBSYS_StopTriggerTimer(void)
  {
    STM0TT = 0x01u;
  }
#endif

/**
  * @brief Service to wait a defined time in usec
  *
  * Function executes while loop for the time specified by parameter (using real-time timer).
  *
  * Hint: This function will be used in bootblock and FSW.
  *
  * @param[in]  time_in_usec   time to wait in usec
  *
  * @return void
  */
void RBSYS_waitUsecLoop(uint16 time_in_usec)
{
  uint32 start_tick = RBSYS_getRealtimeTickCtr();

  while ((uint32)(RBSYS_getRealtimeTickCtr() - start_tick) <= ((uint32)RBSYS_convertUsecToTimerTicks(time_in_usec)))
  {
    RBSYS_snooze(); // reduce bus traffic - wait 32 cpu cycles (<0,5us)
  }
}


/** @} */
/* End ingroup RBSYS */
