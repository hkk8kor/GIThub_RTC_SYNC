#ifndef RBSYS_UCREGISTERS_H__
#define RBSYS_UCREGISTERS_H__
/**
 * @ingroup RBSYS
 * @{
 *
 * @file RBSYS_uCRegisters.h
 * @brief Wrapper to provide the Register definitions for the currently selected device
 *
 * This interface exports uC register definitions for all supported uC devices.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */


RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEnvironment,
                          RBFS_SysEnvironment_Target,
                          RBFS_SysEnvironment_Simulation);

#if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)\
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)\
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    #include "RBSYS_RH850Regs.h" //< redirect
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    #include "RBSYS_STMStellarRegs.h"
  #else
    #error ("Device header files for this uCFamily are missing")
  #endif
#else
  /* Stub all registers for x86 based testing */
  #include "TRBSYS_uCRegisters.h"
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
