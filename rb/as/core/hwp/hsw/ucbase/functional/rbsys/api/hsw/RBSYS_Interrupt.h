#ifndef RBSYS_INTERRUPT_H__
#define RBSYS_INTERRUPT_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * \file RBSYS_Interrupt
 * \brief Interrupt Handling API
 *
 * Interfaces to get the Request Status of an INTC2 Interrupt
 * Interfaces to clear the interrupt request of an ADC Interrupt at INTC2
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"

/* used interfaces */
#include "RBSYS_uCRegisters.h"

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  #define RBSYS_INTC2_INDEX_MIN (32)
  #define RBSYS_INTC2_INDEX_MAX (245) //< 246 - 255 are reserved
  #define RBSYS_INTC2_EIC ((volatile uint16 *) &EIC32)
  #define RBSYS_INTC2_EICn(n) (RBSYS_INTC2_EIC[(n)-RBSYS_INTC2_INDEX_MIN])

  /** Interrupt Request Clearing is dedicated to ADC usage */
  /** ADC Interrupt Sources: 81 - 85, 167 - 171 */

#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  #define RBSYS_INTC2_INDEX_MIN (32)
  #define RBSYS_INTC2_INDEX_MAX (716) //< 717 - 767 are reserved
  #define RBSYS_INTC2_EIC ((volatile uint16 *) &INTC2EIC32)
  #define RBSYS_INTC2_EICn(n) (RBSYS_INTC2_EIC[(n)-RBSYS_INTC2_INDEX_MIN])

  /** Interrupt Request Clearing is dedicated to ADC usage */
  /** ADC Interrupt Sources: 226 - 243 */

#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  #define RBSYS_INTC2_INDEX_MIN (32)
  #define RBSYS_INTC2_INDEX_MAX (629)
  #define RBSYS_INTC2_EIC ((volatile uint16 *) &INTC2EIC32)
  #define RBSYS_INTC2_EICn(n) (RBSYS_INTC2_EIC[(n)-RBSYS_INTC2_INDEX_MIN])

  /** Interrupt Request Clearing is dedicated to ADC usage */
  /** ADC Interrupt Sources: 69 - 73 and 371 - 375 */

#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  #warning("Interrupt.h is not supporting STMStellar yet.")
#else
  #error ("Exception: Implementation for this uCFamily is missing")
#endif

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)  )
  #define RBSYS_EIRFn (0x1000u)


  /** RBSYS_IsInterruptRequestPending
    * \brief returns TRUE if Interrupt request is pending at Interrupt Controller 2
    *
    * \param interruptIndex      Index of the requested Interrupt
    *
    * Attention: Can only be used if interrupt is configured as "Edge Detection".
    *
    * Renesas P1x / U2A / U2C: Index 0-31 are related to INTC1 which is core specific - Not supported by this interface.
    *                          Index 32-x are related to INTC2 which is common.
    */
  static inline boolean RBSYS_IsInterruptRequestPending(uint32 interruptIndex)
  {
    assert( (interruptIndex >= RBSYS_INTC2_INDEX_MIN) && (interruptIndex <= RBSYS_INTC2_INDEX_MAX) ); // Only INTC2 is supported

    return (RBSYS_INTC2_EICn(interruptIndex) & RBSYS_EIRFn) != 0;
  }

  /** RBSYS_ClearInterruptRequest
    * \brief Clears the interrupt request if the requested interrupt at Interrupt Controller 2
    *
    * \param interruptIndex      Index of the requested Interrupt
    *
    * Attention: Shall only be used for ADC interrupt requests!!
    *
    * Renesas P1x / U2A / U2C: Index 0-31 are related to INTC1 which is core specific - Not supported by this interface.
    *                          Index 32-x are related to INTC2 which is common.
    */
  static inline void RBSYS_ClearInterruptRequest(uint32 interruptIndex)
  {
    /** Sanity check: Only ADC related interrupts shall be used */
    #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
      assert( ((interruptIndex >= 81) && (interruptIndex <= 85)) || ((interruptIndex >= 167) && (interruptIndex <= 171)) );
    #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
      assert( (interruptIndex >= 226) && (interruptIndex <= 243) );
    #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
      assert( (interruptIndex >= 69) && (interruptIndex <= 73) || (interruptIndex >= 371) && (interruptIndex <= 375) );
    #else
      assert( 0 && "Implementation for this uCFamily is missing" );
    #endif

    RBSYS_INTC2_EICn(interruptIndex) &= (~RBSYS_EIRFn) & 0xFFFFu;
  }
#endif

/** @} */
/* End ingroup RBSYS */

#endif // Multi-Include-Protection