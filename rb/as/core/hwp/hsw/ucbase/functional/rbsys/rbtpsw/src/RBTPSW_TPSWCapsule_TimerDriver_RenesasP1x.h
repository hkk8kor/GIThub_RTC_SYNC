#ifndef RBTPSW_TPSWCAPSULE_TIMERDRIVER_RENESASP1X_H__
#define RBTPSW_TPSWCAPSULE_TIMERDRIVER_RENESASP1X_H__

/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief Third party software capsule - timer driver for Renesas P1x
 *
 * This internal API provides OS timer services for TPSW timing protection
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_SystemTimer.h"
#include "RBSYS_LocksImpl.h"
#include "RBSYS_CpuInfo.h"
#include "Os_ConfigInterrupts.h"
#include "Os.h"
#include "RB_MathHelpers.h"



/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWCapsule,
                          RBFS_TPSWCapsule_OFF,
                          RBFS_TPSWCapsule_SC3,
                          RBFS_TPSWCapsule_SC4);
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A);
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_ON,
                          RBFS_MCORE_OFF);

#if ( (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4) && (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) )


  /**********************************************************************************************
   ***** TIMER DRIVER ***************************************************************************
   All RBTPSW_TimerDriver_xxx() function must be called from trusted context.
   **********************************************************************************************/

  /** RBTPSW_TimerDriver_ClearIsrReq(CoreId)
      Clears the interrupt request of the timer corresponding to CoreId.
  **/
  static inline void RBTPSW_TimerDriver_ClearIsrReq(CoreIdType CoreId)
  {

      #if (RBFS_MCORE == RBFS_MCORE_ON)
          if(CoreId == OS_CORE_ID_1)
          {
              Os_Clear_ISRSTM07_SC4core1();
          }
          else
      #endif
      {
          Os_Clear_ISRSTM06_SC4core0();
      }
  }

  /** RBTPSW_TimerDriver_ClearPendingBit(CoreId)
      Clears the pending bit the timer corresponding to CoreId.
  **/
  static inline void RBTPSW_TimerDriver_ClearPendingBit(CoreIdType CoreId)
  {
      // core 0: bit 8: STM0STC.CMR2A
      // core 1: bit 9: STM0STC.CMR2B
      STM0STC = (uint32)1u << (CoreId + 8u);
  }

  /** RBTPSW_TimerDriver_DisableInt(CoreId)
      Disables the timer interrupt corresponding to CoreId.
  **/
  static inline void RBTPSW_TimerDriver_DisableInt(CoreIdType CoreId)
  {
      #if (RBFS_MCORE == RBFS_MCORE_ON)
          if(CoreId == OS_CORE_ID_1)
          {
              Os_Disable_ISRSTM07_SC4core1();
          }
          else
      #endif
      {
          Os_Disable_ISRSTM06_SC4core0();
      }
}

  /** RBTPSW_TimerDriver_EnableInt(CoreId)
      Enables the timer interrupt corresponding to CoreId.
  **/
  static inline void RBTPSW_TimerDriver_EnableInt(CoreIdType CoreId)
  {
      /* Enable interrupt.
       * If an interrupt went pending before enabling, we expect the interrupt to come immediately here. */
      #if (RBFS_MCORE == RBFS_MCORE_ON)
          if(CoreId == OS_CORE_ID_1)
          {
              Os_Enable_ISRSTM07_SC4core1();
          }
          else
      #endif
      {
          Os_Enable_ISRSTM06_SC4core0();
      }
  }

  /** RBTPSW_TimerDriver_SetCompareRel(CoreId, relativeCmpValue)
      Sets the match value of corresponding to CoreId to (now + relativeCmpValue).
      For a very short relativeCmpValue (or 0), the interrupt will be immediately pending.
  **/
  static inline void RBTPSW_TimerDriver_SetCompareRel(CoreIdType CoreId, uint32 relativeCmpValue)
  {
      uint32 absoluteCmpValue;
      sint32 diff;
      uint32 local_relativeCmpValue = relativeCmpValue;  // Rule 17.8 A function parameter should not be modified

      // must be called under lock
      RBSYS_EnterCorelocalIntlock();
      {
          #if (RBFS_MCORE == RBFS_MCORE_ON)
              if(CoreId == OS_CORE_ID_1)
              {
                  do
                  {
                      absoluteCmpValue = RBSYS_getRealtimeTickCtr() + local_relativeCmpValue;
                      STM0CMP2B = absoluteCmpValue;  // set HW timer compare value

                      // Check for a race condition in which local_relativeCmpValue is small enough that the running counter
                      // value has already overtaken the desired compare value absoluteCmpValue before it is set in HW. This
                      // would cause a full counter wrap-around to happen before triggering the interrupt. For that reason,
                      // the current counter value is read again to ensure that it is still behind the desired compare value.
                      // If it is not, a few ticks are iteratively added to local_relativeCmpValue and the operation is
                      // repeated until the check passes.

                      // RB_UnsignedDiffToSigned can be used, as the difference between absoluteCmpValue and RBSYS_getRealtimeTickCtr()
                      // is between INT32_MIN and INT32_MAX by design.
                      diff = RB_UnsignedDiffToSigned(absoluteCmpValue, RBSYS_getRealtimeTickCtr());
                      local_relativeCmpValue += RBSYS_TIMERTICKS_PER_US/20;  // 50ns = 1us/20 = 4 ticks @ 80MHz STM
                  } while (diff < 0);
              }
              else
          #endif
          {
              do
              {
                  absoluteCmpValue = RBSYS_getRealtimeTickCtr() + local_relativeCmpValue;
                  STM0CMP2A = absoluteCmpValue;  // set HW timer compare value

                  // Check for a race condition in which local_relativeCmpValue is small enough that the running counter
                  // value has already overtaken the desired compare value absoluteCmpValue before it is set in HW. This
                  // would cause a full counter wrap-around to happen before triggering the interrupt. For that reason,
                  // the current counter value is read again to ensure that it is still behind the desired compare value.
                  // If it is not, a few ticks are iteratively added to local_relativeCmpValue and the operation is
                  // repeated until the check passes.

                  // RB_UnsignedDiffToSigned can be used, as the difference between absoluteCmpValue and RBSYS_getRealtimeTickCtr()
                  // is between INT32_MIN and INT32_MAX by design.
                  diff = RB_UnsignedDiffToSigned(absoluteCmpValue, RBSYS_getRealtimeTickCtr());
                  local_relativeCmpValue += RBSYS_TIMERTICKS_PER_US/20;  // 50ns = 1us/20 = 4 ticks @ 80MHz STM
              } while (diff < 0);
          }
      }
      RBSYS_ExitCorelocalIntlock();
  }

  /** RBTPSW_TimerDriver_SetCompareAbs(CoreId, absoluteCmpValue)
      Sets the match value of corresponding to CoreId to absoluteCmpValue.
  **/
  static inline void RBTPSW_TimerDriver_SetCompareAbs(CoreIdType CoreId, uint32 absoluteCmpValue)
  {
      #if (RBFS_MCORE == RBFS_MCORE_ON)
          if(CoreId == OS_CORE_ID_1)
          {
              STM0CMP2B = absoluteCmpValue;
          }
          else
      #endif
      {
          STM0CMP2A = absoluteCmpValue;
      }
  }

  /** RBTPSW_TimerDriver_GetCompare(CoreId)
      Returns the match value stored for CoreId.
  **/
  static inline uint32 RBTPSW_TimerDriver_GetCompare(CoreIdType CoreId)
  {
      uint32 cmp;

      #if (RBFS_MCORE == RBFS_MCORE_ON)
          if(CoreId == OS_CORE_ID_1)
          {
              cmp = STM0CMP2B;
          }
          else
      #endif
      {
          cmp = STM0CMP2A;
      }

      return cmp;
  }

  /** RBTPSW_TimerDriver_GetCounter()
      Returns the counter value.
  **/
  static inline uint32 RBTPSW_TimerDriver_GetCounter(void)
  {
      return RBSYS_getRealtimeTickCtr(); // STM0CNT2
  }


#endif

/** @} */
/* End ingroup RBTPSW */

#endif /* End of multiple include protection */
