/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Invalid interrupt handling
 *
 * This module provides the interface called by the OS and TPSW when an unconfigured interrupt has been triggered.
 * It leads to a SW reset and deals with reporting to DEM on startup.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"

/* used interfaces */
#include "Monitorings/RBSYS_ErrorHooks.h"
#include "RBSYS_Intrinsics.h"
#include "RBSYS_CoreInit.h"
#include "RBSYS_RAMBackupServiceIntern.h"
#include "RBSYS_uCResetCtrl.h"

/* realized interfaces */
#include "Os.h"
#include "RBSYS_Subsystem.h"

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);



/**
 * @brief Interrupt handler for unused/unconfigured interrupts
 *
 * Invalid interrupt handler will be called either by the OS if any unused interrupt is raised
 * or in case of an MDP exception if RBFS_TPSWSVPRestrictions_ON is configured.
 * It stores relevant debug data in the backup RAM and triggers a reset.
 * This function does not return.
 *
 */
void InvalidInt(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    unsigned int eiic = RBSYS_STSR(RBSYS_EIIC_REGID, RBSYS_EIIC_SELID);   // EIIC (regID, selID): SR  13, 0 - EI level exception cause
    unsigned int feic = RBSYS_STSR(RBSYS_FEIC_REGID, RBSYS_FEIC_SELID);   // FEIC (regID, selID): SR  14, 0 - FE level exception cause register

    RBSYS_setSYSErrorHook(RBSYS_Error_InvalidInt, ((eiic & 0xFFFFu) << 16) | (feic & 0xFFFFu));
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    uint32 acknowledgedIRQIdx = RBSYS_MRC(15, 0, 12, 12, 0); //< read ICC_IAR1
    uint32 acknowledgedFIQIdx = RBSYS_MRC(15, 0, 12, 8, 0);  //< read ICC_IAR0

    RBSYS_setSYSErrorHook(RBSYS_Error_InvalidInt, ((acknowledgedIRQIdx & 0xFFFFu) << 16) | (acknowledgedFIQIdx & 0xFFFFu));
  #endif
}