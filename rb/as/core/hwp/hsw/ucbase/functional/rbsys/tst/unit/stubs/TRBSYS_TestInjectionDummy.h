#ifndef TRBSYS_TESTINJECTIONDUMMY_H__
#define TRBSYS_TESTINJECTIONDUMMY_H__

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
extern void RBSYS_TEST_INJECTION_PBUSGuardForGRAMManipulation(void);
#define RBSYS_TEST_INJECTION_uCModeCtrlModelUpdate()

#endif
