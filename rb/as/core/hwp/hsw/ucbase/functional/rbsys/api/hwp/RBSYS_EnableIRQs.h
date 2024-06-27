#ifndef RBSYS_ENABLEIRQS_H__
#define RBSYS_ENABLEIRQS_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * \file
 * \brief Enable IRQs
 *
 * All actual used OS interrupts within the SW project must be enabled via this interface.
 * This means that per default the envelop of configured platform OS interrupts are disabled. So all
 * used interrupts within the project must be explicitly enabled by the responsible SW part who
 * requests the interrupt and handles the corresponding ISR.
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "Os_ConfigInterrupts.h"  // to enable IRQs via OS macros
#include "RBSYS_CpuInfo.h"
#include "RBSYS_uCRegisters.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_ON,
                          RBFS_MCORE_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSchemeExtension,
                          RBFS_TaskSchemeExtension_None,
                          RBFS_TaskSchemeExtension_VMPS,
                          RBFS_TaskSchemeExtension_HostCore0GuestCore1,
                          RBFS_TaskSchemeExtension_AB15);

  #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    /**
      * Enable Common Timer Interrupt (GST_0.ARC0)
      */
    static inline void RBSYS_EnableIRQ_ISRCommonTimer(void)
    {
      Os_Enable_ISRCommonTimer();
    }

    /**
      * Clear pending Common Timer Interrupt (GST_0.ARC0)
      */
    static inline void RBSYS_ClearPendingIRQ_ISRCommonTimer(void)
    {
      Os_Clear_ISRCommonTimer();
    }
  #else
    /**
    * Enable System Timer 0 interrupt 4
    */
    static inline void RBSYS_EnableIRQ_STM04(void)
    {
      Os_Enable_ISRSTM04();
    }

    /**
    * Clear pending System Timer 0 interrupt 4
    */
    static inline void RBSYS_ClearPendingIRQ_STM04(void)
    {
      Os_Clear_ISRSTM04();
    }

    /**
    * Enable System Timer 0 interrupt 5
    */
    static inline void RBSYS_EnableIRQ_STM05(void)
    {
      Os_Enable_ISRSTM05();
    }

    /**
    * Clear pending System Timer 0 interrupt 5
    */
    static inline void RBSYS_ClearPendingIRQ_STM05(void)
    {
      Os_Clear_ISRSTM05();
    }

    #if(RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
      /**
      * Enable GTM ATOM0 interrupt 0
      */
      static inline void RBSYS_EnableIRQ_0p5ms(void)
      {
        Os_Enable_ISR0p5ms();
      }

      /**
      * Clear pending GTM ATOM0 interrupt 0
      */
      static inline void RBSYS_ClearPendingIRQ_0p5ms(void)
      {
        Os_Clear_ISR0p5ms();
      }
    #endif
  #endif

/* Attention:
 * Take care of interrupt controller 1 (INTC1) handling - corresponding interrupts at INTC1 must be
 * explicitly enabled core-specific. Bind register has no effect, because INTC1 is available on each core
 * without access possibility of other (foreign) cores.
 * All interrupts at common interrupt controller INTC2 must be configured core-specific via corresponding bind register.
 *
 * Example:
 * Even if ISRx is configure in the OS to core1, but enabled wrongly on core0, ISR is executed on core0
 */
#if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    /**
    * Enable interrupt 0 for MTTCAN0
    */
    static inline void RBSYS_EnableIRQ_MTTCAN0(void)
    {
      Os_Enable_ISRMTTCANI0();
    }

    /**
    * Enable interrupt 0 for MCAN0
    */
    static inline void RBSYS_EnableIRQ_MCAN0(void)
    {
      Os_Enable_ISRMCAN0I0();
    }

    /**
    * Enable interrupt 0 for MCAN1
    */
    static inline void RBSYS_EnableIRQ_MCAN1(void)
    {
      Os_Enable_ISRMCAN1I0();
    }

    /**
    * Enable interrupt 0 for MCAN2
    */
    static inline void RBSYS_EnableIRQ_MCAN2(void)
    {
      Os_Enable_ISRMCAN2I0();
    }

  #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )

    /**
    * Enable
    * - CAN0 transmit/receive FIFO receive completion interrupt
    * - CAN0 transmit interrupt
    */
    static inline void RBSYS_EnableIRQ_CAN0(void)
    {
      Os_Enable_ISRCAN0REC();
      Os_Enable_ISRCAN0TRX();
    }

    /**
    * Enable
    * - CAN1 transmit/receive FIFO receive completion interrupt
    * - CAN1 transmit interrupt
    */
    static inline void RBSYS_EnableIRQ_CAN1(void)
    {
      Os_Enable_ISRCAN1REC();
      Os_Enable_ISRCAN1TRX();
    }

    /**
    * Enable
    * - CAN2 transmit/receive FIFO receive completion interrupt
    * - CAN2 transmit interrupt
    */
    static inline void RBSYS_EnableIRQ_CAN2(void)
    {
      Os_Enable_ISRCAN2REC();
      Os_Enable_ISRCAN2TRX();
    }

    /**
    * Enable
    * - CAN6 transmit/receive FIFO receive completion interrupt
    * - CAN6 transmit interrupt
    */
    static inline void RBSYS_EnableIRQ_CAN6(void)
    {
      Os_Enable_ISRCAN6REC();
      Os_Enable_ISRCAN6TRX();
    }

    /**
    * Enable
    * - CAN8 transmit/receive FIFO receive completion interrupt
    * - CAN8 transmit interrupt
    */
    static inline void RBSYS_EnableIRQ_CAN8(void)
    {
      Os_Enable_ISRCAN8REC();
      Os_Enable_ISRCAN8TRX();
    }
  #endif

  /**
  * Enable universal interrupt channel A for FlexRay 0
  */
  static inline void RBSYS_EnableIRQ_Flexray0(void)
  {
    Os_Enable_ISRFLX0LINE0();
  }

  // K0 and K1 do only have one Flexray Module
  #if( RBFS_uCFamily != RBFS_uCFamily_RenesasU2C )
    /**
    * Enable universal interrupt channel A for FlexRay 1
    */
    static inline void RBSYS_EnableIRQ_Flexray1(void)
    {
      Os_Enable_ISRFLX1LINE0();
    }
  #endif

  #if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    /**
    * Enable receive interrupt for RLIN30
    */
    static inline void RBSYS_EnableIRQ_RLIN30RX(void)
    {
      Os_Enable_ISRRLIN30RX();
    }

    /**
    * Enable status interrupt for RLIN30
    */
    static inline void RBSYS_EnableIRQ_RLIN30STATUS(void)
    {
      Os_Enable_ISRRLIN30STATUS();
    }

    /**
    * Enable receive interrupt for RLIN31
    */
    static inline void RBSYS_EnableIRQ_RLIN31RX(void)
    {
      Os_Enable_ISRRLIN31RX();
    }

    /**
    * Enable status interrupt for RLIN31
    */
    static inline void RBSYS_EnableIRQ_RLIN31STATUS(void)
    {
      Os_Enable_ISRRLIN31STATUS();
    }
  #endif



  #if( RBFS_MCORE == RBFS_MCORE_ON )
    /**
    * Clear software interrupt 0 used only for very specific BERT test!
    */
    static inline void RBSYS_ClearIRQ_SWINT0(void)
    {
      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        SINTR0 = 0;
      #else
        EINTSINTR0 = 0;
      #endif
    }

    /**
    * Enable software interrupt 0 only used for very specific BERT test
    */
    static inline void RBSYS_EnableIRQ_SWINT0(void)
    {
      unsigned int core_id = RBSYS_getCoreID();

      if (core_id == OS_CORE_FOR_ISRSWINT0)
      {
        RBSYS_ClearIRQ_SWINT0();  // clear possible software interrupt 0 trigger on source side
        Os_Clear_ISRSWINT0();     // clear possible software interrupt 0 trigger on INTC1

        Os_Enable_ISRSWINT0();
      }
    }

    /**
    * Trigger software interrupt 0 only used for very specific BERT test!
    */
    static inline void RBSYS_GenerateIRQ_SWINT0(void)
    {
      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        SINTR0 = 1;
      #else
        EINTSINTR0 = 1;
      #endif
    }
  #endif //< RBFS_MCORE_ON

#endif

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
