#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                       ///< for RBFS_MCORE, RBFS_TPSWCapsule

#include "Os.h"
#include "RBSYS_Subsystem.h"
#include "RBSYS_ErrorHooks.h"
#include "TRBSYS_Intrinsics.h"
#include "TRBSYS_uCReset.h"
#include "RBSYS_RAMBackupServiceIntern.h"
#include "RBSYS_CoreInit.h"

#include "RBHSWDEM_Facade.h"
#include "DemStub_Helper.h"


/**
  * \Reference
  *  InvalidInt, Gen_SWCS_HSW_uC_Base_SYS-338
  *
  * \Purpose
  *  Invalid interrupt must enter a SYSErrorHook failure entry
  *
  * \Sequence
  *  Renesas: Initialize FEIC and EIIC register
  *  Stellar: Initialize ICC_IAR0 and ICC_IAR1 register
  *  Call function InvalidInt
  *
  * \ExpectedResult
  *  SYSErrorHook failure entry must be set with corresponding failure entry (debug data 1 contains lower 16 bit of both registers)
  */
SWTEST void TRBSYS_InvalidInt1(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
    unsigned int feic_stub = 0xA5A5AAAA;
    unsigned int eiic_stub = 0x5A5A5555;

    TRBSYS_SetSystemRegister(RBSYS_FEIC_REGID, RBSYS_FEIC_SELID, feic_stub);
    TRBSYS_SetSystemRegister(RBSYS_EIIC_REGID, RBSYS_EIIC_SELID, eiic_stub);
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    uint32 icc_iar0_stub = 0xA5A5AAAA;
    uint32 icc_iar1_stub = 0x5A5A5555;

    TRBSYS_SetSystemRegister(15,0,icc_iar0_stub,12,8,0);
    TRBSYS_SetSystemRegister(15,0,icc_iar1_stub,12,12,0);
  #endif

  InvalidInt();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidInt);
  SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0x5555AAAA);
}


/**
  * \Reference
  *  InvalidInt, Gen_SWCS_HSW_uC_Base_SYS-338
  *
  * \Purpose
  *  Invalid interrupt must enter a SYSErrorHook failure entry
  *
  * \Sequence
  *  Renesas: Initialize FEIC and EIIC register
  *  Stellar: Initialize ICC_IAR0 and ICC_IAR1 register
  *  Call function InvalidInt
  *
  * \ExpectedResult
  *  SYSErrorHook failure entry must be set with corresponding failure entry (debug data 1 contains lower 16 bit of both registers)
  */
SWTEST void TRBSYS_InvalidInt2(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
    unsigned int feic_stub = 0xA5A5AAAA;
    unsigned int eiic_stub = 0x0;

    TRBSYS_SetSystemRegister(RBSYS_FEIC_REGID, RBSYS_FEIC_SELID, feic_stub);
    TRBSYS_SetSystemRegister(RBSYS_EIIC_REGID, RBSYS_EIIC_SELID, eiic_stub);
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    uint32 icc_iar0_stub = 0xA5A5AAAA;
    uint32 icc_iar1_stub = 0x0;

    TRBSYS_SetSystemRegister(15,0,icc_iar0_stub,12,8,0);
    TRBSYS_SetSystemRegister(15,0,icc_iar1_stub,12,12,0);
  #endif

  InvalidInt();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidInt);
  SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0x0000AAAA);
}


/**
* \Reference
*  InvalidInt, Gen_SWCS_HSW_uC_Base_SYS-338
*
* \Purpose
*  Invalid interrupt must enter a SYSErrorHook failure entry
*
* \Sequence
*  Renesas: Initialize FEIC and EIIC register
*  Stellar: Initialize ICC_IAR0 and ICC_IAR1 register
*  Call function InvalidInt
*
* \ExpectedResult
*  SYSErrorHook failure entry must be set with corresponding failure entry (debug data 1 contains lower 16 bit of both registers)
*/
SWTEST void TRBSYS_InvalidInt3(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) )
    uint32 feic_stub = 0x0;
    uint32 eiic_stub = 0x5A5A5555;

    TRBSYS_SetSystemRegister(RBSYS_FEIC_REGID, RBSYS_FEIC_SELID, feic_stub);
    TRBSYS_SetSystemRegister(RBSYS_EIIC_REGID, RBSYS_EIIC_SELID, eiic_stub);
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    uint32 icc_iar0_stub = 0x0;
    uint32 icc_iar1_stub = 0x5A5A5555;

    TRBSYS_SetSystemRegister(15,0,icc_iar0_stub,12,8,0);
    TRBSYS_SetSystemRegister(15,0,icc_iar1_stub,12,12,0);
  #endif

  InvalidInt();

  SWT_EvalEq(DemStub_isFailed(DemConf_DemEventParameter_RBSYS_SYSErrorHook), TRUE);
  SWT_EvalEq(DemStub_GetLastReportedDebugData0(DemConf_DemEventParameter_RBSYS_SYSErrorHook), RBSYS_Error_InvalidInt);
  SWT_EvalEqX(DemStub_GetLastReportedDebugData1(DemConf_DemEventParameter_RBSYS_SYSErrorHook), 0x55550000);
}

