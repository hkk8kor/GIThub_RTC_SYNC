#ifndef RBSYS_UCRESETINTERNAL_H__
#define RBSYS_UCRESETINTERNAL_H__

/**
* @ingroup RBSYS
* @{
*
* @file RBSYS_uCResetInternal.h
* @brief Internal Reset Flag Handling APIs (clearing, reading, ...)
*
* @copyright
* Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
* We reserve all rights of disposal such as copying and passing on to third parties.
*/


#include "RBSYS_Config.h"

/* used interfaces */
#include "RBSYS_uCResetInfo.h"
#include "RBSYS_uCRegisters.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);


#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  static inline void RBSYS_ConfigureResetReactions(void)
  {
    MC_RGM_PER.DERD = 0x00010004u; // Disable Reset by TempSens Failure, Disable Reset by Reset B (XCP POD)
    MC_RGM_PER.DEAR = 0x00010004u; // TempSens Failure causes Interrupt, Reset B causes an Interrupt (XCP POD)

    MC_RGM_PER.FERD = 0x2F010080u; // Disable all functional VMON Resets, Disalbe TempSens Reset
    MC_RGM_PER.FEAR = 0x2F010000u; // Functional VMON Reset, TempSens Reset cause Interrupts
    MC_RGM_PER.FESS = 0x00008040u; // All functional Resets starting from PHASE1 (except HSM_FUNC, FCCU_SOFT)
    MC_RGM_PER.FBRE = 0x2F018469u; // Reset A is not asserted on triggering any type of Reset!! Important!

    MC_RGM_PER.FRET = 0x00u; // no escalation of functional resets
    MC_RGM_PER.DRET = 0x00u; // no escalation of destructive resets

    // MC_RGM_CL0.FESS = 0x00000000u; // All functional Resets starting from PHASE1
    // MC_RGM_CL1.FESS = 0x00000000u; // All functional Resets starting from PHASE1
    // MC_RGM_CL2.FESS = 0x00000000u; // All functional Resets starting from PHASE1
  }
#endif






/**
* @brief Checks if latest reset was initiated by FSW (application SW)
*
* This function may only be called by the FSW.
* It indicates whether the application SW has triggered the latest SW-reset via RBSYS_uCReset_ApplResetSkipBootBlock, RBSYS_uCReset_ApplResetSkipBootBlockNoGramZeroing/RBSYS_uCReset_ApplResetSkipBootBlockNoLramZeroing
*
* @return TRUE if latest reset was initiated by FSW, otherwise (Bootblock has triggered) FALSE
*/
extern boolean RBSYS_isSWResetTriggeredByFSW(void);

/** @brief Clear Reset Factors At Startup (Terminal Reset Handling)
  * If Terminal Reset has occurred, invalidate Terminal, Application and System Reset
  */
extern void RBSYS_ClearResetFactorsAtStartup(void);



/** @} */
/* End ingroup RBSYS */


#endif