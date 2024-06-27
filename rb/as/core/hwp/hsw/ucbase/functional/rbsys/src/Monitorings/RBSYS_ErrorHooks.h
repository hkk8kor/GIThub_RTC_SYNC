#ifndef RBSYS_ERRORHOOKS_H__
#define RBSYS_ERRORHOOKS_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief General RBSYS error handling
 *
 * Complete RB specific failure handling (setting faults and/or good check) of RBSYS is encapsulated within this module.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"


RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )  //< DEM is not available within other than Application
  /* used interfaces */
  #include "RBHSWESR_FailureHandling.h"


  /* Assert supported configurations: switches, parameters, constants, ... */
  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysMaxTaskx1Jitter,
                            RBFS_SysMaxTaskx1Jitter_5,
                            RBFS_SysMaxTaskx1Jitter_15,
                            RBFS_SysMaxTaskx1Jitter_SERIES);


  /** Error type for failure word RBSYS_SYSErrorHook */
  typedef enum
  {
    RBSYS_Error_InvalidInt = 0,
    RBSYS_Error_InvalidLockNesting,
    RBSYS_Error_LockTooLong,
    RBSYS_Error_WrongAPIcalled,
    RBSYS_Error_TimerMonitoring,
    RBSYS_Error_PeripheralReset,
    RBSYS_Error_PeripheralResetTimeOut,
    RBSYS_Error_SupervisorRestriction,
    RBSYS_Error_GuardConfigurationFailed,
    RBSYS_Error_TPSWConfigurationFailed,
    RBSYS_Error_ClockConfigurationInvalid,
    RBSYS_Error_TimerInterruptMonitoring,
  }RBSYSError_t;


  extern boolean RBSYS_IsSYSErrorHookFailureReported(void);
  extern void RBSYS_setSYSErrorHook(RBSYSError_t d0, uint32 d1);
  extern void RBSYS_setStackOverUnderFlowError(uint32 d0, uint32 d1);
  extern void RBSYS_setTaskOverRunError(uint32 d0);
  extern void RBSYS_setGoodCheckRequest(Dem_EventIdType rbsys_event_id);

  #if (  (RBFS_SysMaxTaskx1Jitter == RBFS_SysMaxTaskx1Jitter_5)  \
      || (RBFS_SysMaxTaskx1Jitter == RBFS_SysMaxTaskx1Jitter_15) \
      )
    extern void RBSYS_setTaskJitterError(uint32 d0, uint32 d1);
  #endif
#endif

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
