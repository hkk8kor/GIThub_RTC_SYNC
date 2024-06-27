#ifndef RBSYS_EXCEPTIONHANDLER_H__
#define RBSYS_EXCEPTIONHANDLER_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief RBSYS exception handler interface
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEnvironment,
                          RBFS_SysEnvironment_Target,
                          RBFS_SysEnvironment_Simulation);


#if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)

  /* OS FPU CAT1 exception handler */
  __interrupt extern void RBSYS_EXCFPP_Handler(void);

#else

  // Exception Handlers + Trap Entry / Exit functions cannot be tested in Unittests due to ASM implementations

#endif //(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)

/**
  * @brief Procedure for handling MPU exceptions in supervisor mode
  *
  * If RBFS_TPSWSVPRestrictions_ON is configured, this function stores debug information in backup RAM and triggers an Application Reset.
  * Otherwise, MPU exceptions in supervisor mode are unexpected and this function calls InvalidInt.
  */
extern void RBSYS_HandleSupervisorMpuViolation(void);



/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
