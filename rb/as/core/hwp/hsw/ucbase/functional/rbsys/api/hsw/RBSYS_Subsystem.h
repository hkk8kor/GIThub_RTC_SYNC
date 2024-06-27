#ifndef RBSYS_SUBSYSTEM_H__
#define RBSYS_SUBSYSTEM_H__

  /**
  * @ingroup RBSYS
  * @{
  *
  * \file RBSYS_Subsystem.h
  * \brief Process definitions as public APIs
  *
  * \copyright
  * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
  * We reserve all rights of disposal such as copying and passing on to third parties.
  */

  #include "RBSYS_Config.h"

  RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                            RBFS_uCFamily_RenesasP1x,
                            RBFS_uCFamily_RenesasU2A,
                            RBFS_uCFamily_RenesasU2C,
                            RBFS_uCFamily_STMStellar);

  /** Function Group "Statistics" */
  extern void RBSYS_PRC_RuntimeMeasure_PreOSInit(void);
  extern void RBSYS_PRC_RuntimeMeasure_Init(void);
  extern void RBSYS_PRC_RuntimeMeasure_MainFunction(void);
  extern void RBSYS_PRC_InitTaskStats(void);
  extern void RBSYS_PRC_ResetMaxLockTime_Init(void);
  #if(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ) || ( RBFS_uCFamily == RBFS_uCFamily_STMStellar ))
    extern void RBSYS_PRC_PerformanceCounterMonitoring_x2(void);
  #endif


  /** Function Group "Monitorings" */
  extern void RBSYS_PRC_UnsupportedHW(void);
  extern void RBSYS_PRC_TimerMonitoring(void);
  extern void RBSYS_PRC_JitterMonitoring_x1(void);
  extern void RBSYS_PRC_LockMonitoring(void);
  extern void RBSYS_PRC_StackCheckInit(void);
  extern void RBSYS_PRC_StackCheck(void);
  #if(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
    extern void RBSYS_PRC_TimerInterruptMonitoring(void);
  #endif
  extern void RBSYS_PRC_CheckClockTreeSettings(void);

  /** others */
  extern void RBSYS_PRC_SRMSTimeBaseAdaptation(void);
  extern void RBSYS_PRC_SRMSCylicTest(void);
  extern void RBSYS_PRC_ClearColdStartResetFlags(void);
  extern void RBSYS_PRC_FSW_FinalGuard_Init(void);
  extern void RBSYS_PRC_FSW_VerifyFinalGuardSettings(void);
  extern void RBSYS_PRC_SynchronizeCores_TaskInit(void);
  #if(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
    extern void RBSYS_PRC_ModeChangeAfterFCCUInit(void);
  #endif


  /** @} */
  /* End ingroup RBSYS */

#endif