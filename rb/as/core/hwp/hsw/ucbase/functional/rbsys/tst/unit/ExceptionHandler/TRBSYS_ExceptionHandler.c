#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                       ///< for RBFS_MCORE, RBFS_TPSWCapsule

#include "Os.h"
#include "RBSYS_Subsystem.h"
#include "RBSYS_ErrorHooks.h"
#include "TRBSYS_Intrinsics.h"
#include "TRBSYS_uCReset.h"
#include "RBSYS_CoreInit.h"
#include "RBSYS_ExceptionHandler.h"
#include "RBSYS_ExceptionInfo.h"
#include "TRBSYS_ExceptionHandler_Adaptor.h"

#include "RBHSWDEM_Facade.h"
#include "DemStub_Helper.h"


#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) \
  )
  /**
    * \Reference
    *  RBSYS_HandleSupervisorMpuViolation
    *  
    * \Purpose Check
    *  Check detection and report of SysErrorHook in case of MIP / MDP from supervisor (invalid access or execution)
    *
    * \Sequence
    *  see below
    *
    * \ExpectedResult
    *  
    */
  SWTEST void TRBSYS_MpuExceptionInSV(void)
  {
    #if (RBFS_TPSWSVPRestrictions == RBFS_TPSWSVPRestrictions_ON)
      // Case 0: MIP Exception
      TRBSYS_SetSystemRegister(2,  0, 0xDEADBEEF); //< FEPC
      TRBSYS_SetSystemRegister(14, 0, 0x90);       //< FEIC = MPU Exception MIP (Execution Privilege)

      RBSYS_HandleSupervisorMpuViolation();

      SWT_EvalEqX( DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_SupervisorRestriction );
      SWT_EvalEqX( DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0xDEADBEEF );
      SWT_EvalEqX( DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE ); //< SYSErrorHook is reported
      DemStub_EnvReset();


      // Case 1: MDP Exception
      TRBSYS_SetSystemRegister(14, 0, 0x91);       //< FEIC = MPU Exception MDP (Access Privilege)

      RBSYS_HandleSupervisorMpuViolation();

      SWT_EvalEqX( DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_SupervisorRestriction );
      SWT_EvalEqX( DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0xDEADBEEF );
      SWT_EvalEqX(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE); //< SYSErrorHook is reported
      DemStub_EnvReset();
    #endif

    // Case 2: No MIP / MDP exception, just some other unexpected interrupt
    TRBSYS_SetSystemRegister(14, 0, 0);          //< FEIC = empty (e.g. EI interrupt)

    RBSYS_HandleSupervisorMpuViolation();

    SWT_EvalEqX( DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidInt );
    SWT_EvalEqX( DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0 );
    SWT_EvalEqX( DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE ); //< SYSErrorHook is reported

  }

#else
    /**
    * \Reference
    *  RBSYS_ExceptionHandler_GetExceptionProgramCounterForDebug
    *  
    * \Purpose Check
    *  Check get interface for LP saving in ARM exceptions
    *
    * \Sequence
    *  see below
    *
    * \ExpectedResult
    *  
    */
  SWTEST void TRBSYS_ExceptionProgramCounter(void)
  {
    TRBSYS_Set_ExceptionProgramCounterForDebug(0, 0xdeadbeef);

    SWT_EvalEqX( RBSYS_ExceptionHandler_GetExceptionProgramCounterForDebug(), 0xdeadbeef);
  }

#endif