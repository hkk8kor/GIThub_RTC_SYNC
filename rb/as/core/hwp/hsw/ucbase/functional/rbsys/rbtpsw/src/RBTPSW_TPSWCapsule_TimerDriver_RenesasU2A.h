#ifndef RBTPSW_TPSWCAPSULE_TIMERDRIVER_RENESASU2A_H__
#define RBTPSW_TPSWCAPSULE_TIMERDRIVER_RENESASU2A_H__

/**
 * @ingroup RBTPSW
 * @{
 *
 * @file
 * @brief Third party software capsule - timer driver for Renesas U2A
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

#if ( (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4) &&  (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )


  /**********************************************************************************************
   ***** TIMER DRIVER ***************************************************************************
   All RBTPSW_TimerDriver_xxx() function must be called from trusted context.
   **********************************************************************************************/

  /** RBTPSW_TimerDriver_ClearIsrReq(CoreId)
      Clears the interrupt request of the timer corresponding to CoreId.
  **/
  static inline void RBTPSW_TimerDriver_ClearIsrReq(CoreIdType CoreId)
  {
      if(CoreId == OS_CORE_ID_0)
      {
          Os_Clear_ISRSTM06_SC4core0();
      }
      else
      {
          Os_Clear_ISRSTM07_SC4core1();
      }
  }

  /** RBTPSW_TimerDriver_ClearPendingBit(CoreId)
      Clears the pending bit the timer corresponding to CoreId.
  **/
  static inline void RBTPSW_TimerDriver_ClearPendingBit(CoreIdType CoreId)
  {
      /* TPTM Up counting interrupts are edge interrupts - no peripheral clear pending required */
  }

  /** RBTPSW_TimerDriver_DisableInt(CoreId)
      Disables the timer interrupt corresponding to CoreId.
  **/
  static inline void RBTPSW_TimerDriver_DisableInt(CoreIdType CoreId)
  {
      if(CoreId == OS_CORE_ID_0)
      {
          Os_Disable_ISRSTM06_SC4core0();
      }
      else
      {
          Os_Disable_ISRSTM07_SC4core1();
      }
  }

  /** RBTPSW_TimerDriver_EnableInt(CoreId)
      Enables the timer interrupt corresponding to CoreId.
  **/
  static inline void RBTPSW_TimerDriver_EnableInt(CoreIdType CoreId)
  {
      /* Enable interrupt.
       * If an interrupt went pending before enabling, we expect the interrupt to come immediately here. */
      if(CoreId == OS_CORE_ID_0)
      {
          Os_Enable_ISRSTM06_SC4core0();
      }
      else
      {
          Os_Enable_ISRSTM07_SC4core1();
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
          if(CoreId == OS_CORE_ID_0)
          {
              do
              {
                  absoluteCmpValue = RBSYS_getRealtimeTickCtr() + local_relativeCmpValue;
                  TPTMPE0TPTM0UCMP12 = absoluteCmpValue;  // set HW timer compare value

                  // Check for a race condition in which local_relativeCmpValue is small enough that the running counter
                  // value has already overtaken the desired compare value absoluteCmpValue before it is set in HW. This
                  // would cause a full counter wrap-around to happen before triggering the interrupt. For that reason,
                  // the current counter value is read again to ensure that it is still behind the desired compare value.
                  // If it is not, a few ticks are iteratively added to local_relativeCmpValue and the operation is
                  // repeated until the check passes.

                  // RB_UnsignedDiffToSigned can be used, as the difference between absoluteCmpValue and RBSYS_getRealtimeTickCtr()
                  // is between INT32_MIN and INT32_MAX by design.
                  diff = RB_UnsignedDiffToSigned(absoluteCmpValue, RBSYS_getRealtimeTickCtr());
                  local_relativeCmpValue += RBSYS_TIMERTICKS_PER_US/20;  // 50ns = 1us/20 = 20 ticks @ 80MHz TPTM
              } while (diff < 0);
          }
          else
          {
              do
              {
                  absoluteCmpValue = RBSYS_getRealtimeTickCtr() + local_relativeCmpValue;
                  TPTMPE0TPTM0UCMP13 = absoluteCmpValue;  // set HW timer compare value

                  // Check for a race condition in which local_relativeCmpValue is small enough that the running counter
                  // value has already overtaken the desired compare value absoluteCmpValue before it is set in HW. This
                  // would cause a full counter wrap-around to happen before triggering the interrupt. For that reason,
                  // the current counter value is read again to ensure that it is still behind the desired compare value.
                  // If it is not, a few ticks are iteratively added to local_relativeCmpValue and the operation is
                  // repeated until the check passes.

                  // RB_UnsignedDiffToSigned can be used, as the difference between absoluteCmpValue and RBSYS_getRealtimeTickCtr()
                  // is between INT32_MIN and INT32_MAX by design.
                  diff = RB_UnsignedDiffToSigned(absoluteCmpValue, RBSYS_getRealtimeTickCtr());
                  local_relativeCmpValue += RBSYS_TIMERTICKS_PER_US/20;  // 50ns = 1us/20 = 20 ticks @ 80MHz TPTM
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
      if(CoreId == OS_CORE_ID_0)
      {
          TPTMPE0TPTM0UCMP12 = absoluteCmpValue;
      }
      else
      {
          TPTMPE0TPTM0UCMP13 = absoluteCmpValue;
      }
  }

  /** RBTPSW_TimerDriver_GetCompare(CoreId)
      Returns the match value stored for CoreId.
  **/
  static inline uint32 RBTPSW_TimerDriver_GetCompare(CoreIdType CoreId)
  {
      uint32 cmp;

      if(CoreId == OS_CORE_ID_0)
      {
          cmp = TPTMPE0TPTM0UCMP12;
      }
      else
      {
          cmp = TPTMPE0TPTM0UCMP13;
      }

      return cmp;
  }

  /** RBTPSW_TimerDriver_GetCounter()
      Returns the counter value.
  **/
  static inline uint32 RBTPSW_TimerDriver_GetCounter(void)
  {
      return RBSYS_getRealtimeTickCtr(); // TPTMPE0TPTM0UCNT1
  }


#endif

/** @} */
/* End ingroup RBTPSW */

#endif /* End of multiple include protection */
