#ifndef RBSYS_TESTINJECTION_H__
#define RBSYS_TESTINJECTION_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * \file
 * \brief Test Injection preparation
 *
 * The macros in this file are used for injection of test code.
 * They must be empty in production code and can be stubbed in tests.
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEnvironment,
                          RBFS_SysEnvironment_Target,
                          RBFS_SysEnvironment_Simulation);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HSWSimulation,
                          RBFS_HSWSimulation_OFF,
                          RBFS_HSWSimulation_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysUnittestSimulationModel,
                          RBFS_SysUnittestSimulationModel_ON,
                          RBFS_SysUnittestSimulationModel_OFF);

#if( RBFS_SysUnittestSimulationModel == RBFS_SysUnittestSimulationModel_ON )
  #include "TRBSYS_TestInjection.h"
#elif( (RBFS_SysEnvironment == RBFS_SysEnvironment_Target) || (RBFS_HSWSimulation == RBFS_HSWSimulation_ON) )
  #define RBSYS_TEST_INJECTION_ClockModelUpdate()
  #define RBSYS_TEST_INJECTION_LeaveInfiniteLoop()
  #define RBSYS_TEST_INJECTION_StopSystemTimer()
  #define RBSYS_TEST_INJECTION_StopTAUD0Channel(chnl)
  #define RBSYS_TEST_INJECTION_CheckIdleCfg()
  #define RBSYS_TEST_INJECTION_ProgressTime()
  #define RBSYS_TEST_INJECTION_Preemption()
  #define RBSYS_TEST_INJECTION_CoreSyncRegisterUpdate()
  #define RBSYS_TEST_INJECTION_CoreSyncPhaseUpdate()
  #define RBSYS_TEST_INJECTION_CoreSyncPhaseUpdateConditionally()
  #define RBSYS_TEST_INJECTION_DelayRunMode()
  #define RBSYS_TEST_INJECTION_SetRunMode()
  #define RBSYS_TEST_INJECTION_PBUSGuardForGRAMManipulation()
  #define RBSYS_TEST_INJECTION_uCModeCtrlModelUpdate()
  #define RBSYS_TEST_INJECTION_ReleaseOtherCores()
#else
  #error("Invalid switch setting.")
#endif

/** @} */
/* End ingroup RBSYS */

#endif
