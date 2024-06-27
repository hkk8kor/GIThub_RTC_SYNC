#ifndef TRBSYS_TESTINJECTION_H__
#define TRBSYS_TESTINJECTION_H__

  #include "RBSYS_Config.h"
  #include "TRBSYS_MultiCoreSync_Helper.h"
  #include "TRBSYS_MultiCoreSync.h"
  #include "RBSYS_SystemTimer.h"
  #include "TRBSYS_SystemTimer.h"

  extern bool TRBSYS_InjectValues;
  extern uint32 TRBSYS_InjectTicks;
  extern uint32 TRBSYS_TicksForPreempt;
  extern uint32 TRBSYS_TicksPerLoop;
  extern uint32 TRBSYS_EndlessLoopCount;
  extern PRC_PTR* TRBSYS_IdleCfg;

  
  #define RBSYS_TEST_INJECTION_ClockModelUpdate() TRBSYS_ClockModelUpdate()
  #define RBSYS_TEST_INJECTION_uCModeCtrlModelUpdate() TRBSYS_uCModeCtrlModelUpdate()
  
  #define RBSYS_TEST_INJECTION_CheckIdleCfg() TRBSYS_IdleCfg = (PRC_PTR*)idle;
  #define RBSYS_TEST_INJECTION_CoreSyncPhaseUpdate() (*(uint8*)otherCoreCounter)++
  #define RBSYS_TEST_INJECTION_CoreSyncPhaseUpdateConditionally()  if(TRBSYS_InjectValues) {RBSYS_RuntimeResetSync.ptr[otherCoreID][RBSYS_RuntimeResetSyncPhase_BeforeReset] = 1;} else {}
  #define RBSYS_TEST_INJECTION_CoreSyncRegisterUpdate() TRBSYS_CoreSyncRegisterUpdate()
  #define RBSYS_TEST_INJECTION_DelayRunMode() *standbyRegister = *standbyRegister | bitmask
  extern uint32 TRBSYS_loop_cnt;
  #define RBSYS_TEST_INJECTION_SetRunMode() \
  {\
    if(TRBSYS_loop_cnt > 0) \
    {\
      TRBSYS_loop_cnt--;\
    }else{\
      *standbyRegister = 0; \
    }\
  }
  
  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
    #define  RBSYS_TEST_INJECTION_StopTAUD0Channel(chnl) (TAUD0TE &= ~(1 << chnl))
  #endif
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    #define RBSYS_TEST_INJECTION_StopSystemTimer() TPTMPE0TPTM0USTR = 0x0
  #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
    #define RBSYS_TEST_INJECTION_StopSystemTimer() STM0CSTR = 0x0
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    #define RBSYS_TEST_INJECTION_StopSystemTimer() RBSYS_SYNCTIME_STR = 0x0
  #endif
  #define RBSYS_TEST_INJECTION_LeaveInfiniteLoop() \
  {\
    TRBSYS_EndlessLoopCount++;\
    break;\
  }

  #define RBSYS_TEST_INJECTION_Preemption() do \
                                            { \
                                                RBSYS_SystemTimerSynctimeCnt += TRBSYS_TicksForPreempt; \
                                                TRBSYS_RealtimeTickCtrAddTicks(TRBSYS_TicksForPreempt); \
                                            } \
                                            while(0)
											  
  /* #define RBSYS_TEST_INJECTION_LeaveInfiniteLoop() { \
  *                                                     static int i = 0; \
  *                                                     i++; \
  *                                                     if(i >= TRBSYS_LOOP_CNT) \
  *                                                     { \
  *                                                       i = 0; \
  *                                                       break; \
  *                                                     } \
  *                                                   }
  */



  extern void TRBSYS_ClockModelInit(void);
  extern void TRBSYS_ClockModelUpdate(void);
  extern void TRBSYS_uCModeCtrlModelUpdate(void);
  extern void RBSYS_TEST_INJECTION_ProgressTime(void);

  typedef void(*TRBSYS_Callback_t)(void);
  extern TRBSYS_Callback_t TestInjectionCallback_PBUSGuardForGRAMManipulation;
  extern void RBSYS_TEST_INJECTION_PBUSGuardForGRAMManipulation(void);
  extern void TRBSYS_CoreSyncRegisterUpdate(void);

  

  static inline void RBSYS_TEST_INJECTION_ReleaseOtherCores(void)
  {
    TRBSYS_Bootblock_ReleaseCore0FromApplication();
  }

  extern bool TRBSYS_InjectValues;

#endif
