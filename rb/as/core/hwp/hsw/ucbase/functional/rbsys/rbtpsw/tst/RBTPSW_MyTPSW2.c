/**
 * @ingroup 'SW-group'
 * @{
 *
 * \file
 * \brief 'Short description of this module, up to 80 characters
 *
 * 'Detailed description of this module, several lines/paragraphes'
 *
 * \copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBCMHSW_Global.h"
#include "RBSYS_Config.h"


/* used interfaces */
#include "RBLCF_MemoryRemap.h"
#include "RBLCF_MemoryMap.h"
#include "RBSYS_uCRegisters.h"  // peripheral labels
#include "Os.h"
#include "../src/RBTPSW_TPSWCapsule_TimerDriver.h"


/* realized interfaces */
#include "RBTPSW_MyTPSWCapsule.h"
#include "RBTPSW_MyTPSW2.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWCapsule,
                          RBFS_TPSWCapsule_OFF,
                          RBFS_TPSWCapsule_SC3,
                          RBFS_TPSWCapsule_SC4);
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWTestsuite,
                          RBFS_TPSWTestsuite_OFF,
                          RBFS_TPSWTestsuite_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasP1xGRAM,
                          RBFS_RenesasP1xGRAM_OFF,
                          RBFS_RenesasP1xGRAM_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasU2aCRAM0,
                          RBFS_RenesasU2aCRAM0_OFF,
                          RBFS_RenesasU2aCRAM0_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A);

#if (RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON)

void TPSW2_WriteAccessTpsw1(void)
{
    // access to tpsw1 data
    uint32* ptr = (uint32*)&RBTPSW_LINKERSYMBOL_MYTPSW1_LCF_start;
    *ptr = 0;
}

void TPSW2_UTStackCheckTestAbove(void)
{
    // break stack pointer
    TRUSTED_MoveSP((void*)
        #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
            RBLCF_getStartAddress_GRAM()
        #elif (RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON)
            RBLCF_getStartAddress_CRAM0()
        #else
            #error "Unsupported RAM type"
        #endif
    );

    // wait for any timer interrupt
    for(;;){}
}

void TPSW2_UTStackCheckTestBelow(void)
{
    // break stack pointer
    TRUSTED_MoveSP((void*)
        #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
            RBLCF_getEndAddress_GRAM()
        #elif (RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON)
            RBLCF_getEndAddress_CRAM0()
        #else
            #error "Unsupported RAM type"
        #endif
    );

    // wait for any timer interrupt
    for(;;){}
}



uint32 TPSW2_TestCaseId = 0;
uint32 TPSW2_TestSuiteExecutionCount = 0;
void TPSW2_TestWrapper(void)
{
    void* sp = TRUSTED_GetSP();

    TPSW2_TestCaseId++;

    MYTPSW_CHECK_SF(FALSE);

    // Execute all test twice.
    // From here, all application could be killed at any time.
    RBTPSW_CALL(TPSW1_TestExecution(sp, TPSW2_TestCaseId));

    MYTPSW_CHECK_SF(FALSE);

    // If TPSW1 is killed, the second call will not occur.
    RBTPSW_CALL(TPSW1_TestExecution(sp, TPSW2_TestCaseId));

    MYTPSW_CHECK_SF(FALSE);
}

/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/
void TPSW2_Mytest_BadCaseUTUTwithIntLock(void)
{
    RBTPSW_EnterLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
}


uint32 TPSW2_DataTable[TPSW2_DATATABLESIZE];
void TPSW2_BreakSpToValidRam(void)
{
    asm("mov  sdaoff23(_TPSW2_DataTable+200),r3"); // stack pointer = TRUSTED_MoveSP((void*)&TPSW2_DataTable[50]);
}
void TPSW2_BreakSpToInvalidRam(void)
{
    asm("mov  sdaoff23(_RBTPSW_LINKERSYMBOL_MYTPSW2_GLOBAL_LCF_end+16),r3"); // stack pointer = TRUSTED_MoveSP((void*)(&RBTPSW_LINKERSYMBOL_MYTPSW2_GLOBAL_LCF_end + 4));
}


void TPSW2_FuncWithHugeStack(void){}

void TPSW2_EmptyFunction(void){}

void TPSW2_CommonLockSpBroken(void)
{
    TRUSTED_MoveSP(&TrustedData);
    RBTPSW_EnterLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
    RBTPSW_ExitLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
}


uint32 TPSW2_TimingAndMpuAbort(uint32 x)
{
    return RBTPSW_CALL(TPSW3_TimingAndMpuAbort(x));
}

uint32 TPSW2_TimingAndMpuAbort_Tp(uint32 x)
{
    return RBTPSW_CALL(TPSW3_TimingAndMpuAbort_Tp(x));
}

/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/
/****************************************************************************************/

volatile uint32 MYTPSW2_Data = 0;

uint32 TPSW2_ErrorCounter_UL;

void     TPSW2_1Param_V (uint32 p1)
{
  if  (
            (p1 != 1u)
      )
  {
    TPSW2_ErrorCounter_UL++;
  }
}

void     TPSW2_2Param_V (uint32 p1, uint32 p2)
{
  if  (
            (p1 != 1u)
          ||(p2 != 2u)
      )
  {
    TPSW2_ErrorCounter_UL++;
  }
}

void     TPSW2_3Param_V (uint32 p1, uint32 p2, uint32 p3)
{
  if  (
            (p1 != 1u)
          ||(p2 != 2u)
          ||(p3 != 3u)
      )
  {
    TPSW2_ErrorCounter_UL++;
  }
}

void     TPSW2_4Param_V (uint32 p1, uint32 p2, uint32 p3, uint32 p4)
{
  if  (
            (p1 != 1u)
          ||(p2 != 2u)
          ||(p3 != 3u)
          ||(p4 != 4u)
      )
  {
    TPSW2_ErrorCounter_UL++;
  }
}

void     TPSW2_5Param_V (uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5)
{
  if  (
            (p1 != 1u)
          ||(p2 != 2u)
          ||(p3 != 3u)
          ||(p4 != 4u)
          ||(p5 != 5u)
      )
  {
    TPSW2_ErrorCounter_UL++;
  }
}

void     TPSW2_6Param_V (uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6)
{
  if  (
            (p1 != 1u)
          ||(p2 != 2u)
          ||(p3 != 3u)
          ||(p4 != 4u)
          ||(p5 != 5u)
          ||(p6 != 6u)
      )
  {
    TPSW2_ErrorCounter_UL++;
  }
}

void     TPSW2_7Param_V (uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6, uint32 p7)
{
  if  (
            (p1 != 1u)
          ||(p2 != 2u)
          ||(p3 != 3u)
          ||(p4 != 4u)
          ||(p5 != 5u)
          ||(p6 != 6u)
          ||(p7 != 7u)
      )
  {
    TPSW2_ErrorCounter_UL++;
  }
}

void     TPSW2_8Param_V (uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6, uint32 p7, uint32 p8)
{
  if  (
            (p1 != 1u)
          ||(p2 != 2u)
          ||(p3 != 3u)
          ||(p4 != 4u)
          ||(p5 != 5u)
          ||(p6 != 6u)
          ||(p7 != 7u)
          ||(p8 != 8u)
      )
  {
    TPSW2_ErrorCounter_UL++;
  }
}

void     TPSW2_9Param_V (uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6, uint32 p7, uint32 p8, uint32 p9)
{
  if  (
            (p1 != 1u)
          ||(p2 != 2u)
          ||(p3 != 3u)
          ||(p4 != 4u)
          ||(p5 != 5u)
          ||(p6 != 6u)
          ||(p7 != 7u)
          ||(p8 != 8u)
          ||(p9 != 9u)
      )
  {
    TPSW2_ErrorCounter_UL++;
  }
}

void     TPSW2_9Param_U8_V (uint8 p1, uint8 p2, uint8 p3, uint8 p4, uint8 p5, uint8 p6, uint8 p7, uint8 p8, uint8 p9)
{
  if  (
            (p1 != 1u)
          ||(p2 != 2u)
          ||(p3 != 3u)
          ||(p4 != 4u)
          ||(p5 != 5u)
          ||(p6 != 6u)
          ||(p7 != 7u)
          ||(p8 != 8u)
          ||(p9 != 9u)
      )
  {
    TPSW2_ErrorCounter_UL++;
  }
}

uint32 TPSW2_0Param_UL(void)
{
  return 0xFFFFFFFFu;
}

uint32 TPSW2_1Param_UL(uint32 p1)
{
  TPSW2_1Param_V(p1);
  return 1u;
}

uint32 TPSW2_2Param_UL(uint32 p1, uint32 p2)
{
  TPSW2_2Param_V(p1, p2);
  return 2u;
}

uint32 TPSW2_3Param_UL(uint32 p1, uint32 p2, uint32 p3)
{
  TPSW2_3Param_V(p1, p2, p3);
  return 3u;
}

uint32 TPSW2_4Param_UL(uint32 p1, uint32 p2, uint32 p3, uint32 p4)
{
  TPSW2_4Param_V(p1, p2, p3, p4);
  return 4u;
}

uint32 TPSW2_5Param_UL(uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5)
{
  TPSW2_5Param_V(p1, p2, p3, p4, p5);
  return 5u;
}

uint32 TPSW2_6Param_UL(uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6)
{
  TPSW2_6Param_V(p1, p2, p3, p4, p5, p6);
  return 6u;
}

uint32 TPSW2_7Param_UL(uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6, uint32 p7)
{
  TPSW2_7Param_V(p1, p2, p3, p4, p5, p6, p7);
  return 7u;
}

uint32 TPSW2_8Param_UL(uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6, uint32 p7, uint32 p8)
{
  TPSW2_8Param_V(p1, p2, p3, p4, p5, p6, p7, p8);
  return 8u;
}

uint32 TPSW2_9Param_UL(uint32 p1, uint32 p2, uint32 p3, uint32 p4, uint32 p5, uint32 p6, uint32 p7, uint32 p8, uint32 p9)
{
  TPSW2_9Param_V(p1, p2, p3, p4, p5, p6, p7, p8, p9);
  return 9u;
}

uint32 TPSW2_9Param_U8(uint8 p1, uint8 p2, uint8 p3, uint8 p4, uint8 p5, uint8 p6, uint8 p7, uint8 p8, uint8 p9)
{
  TPSW2_9Param_U8_V(p1, p2, p3, p4, p5, p6, p7, p8, p9);
  return 9u;
}

mytest_t TPSW2_struct_ST(mytest_t structure)
{
    structure.a++;
    structure.b++;
    return structure;
}

int32_t TPSW2_CPYPTR_UL(uint8_t *p_in, uint8_t *p_out, uint8_t *p_inout)
{
  if (*p_in != 1u)
  {
    TPSW2_ErrorCounter_UL++;
  }

  *p_out = 50u;

  (*p_inout)++;

  return 0;
}


void TPSW2_GetPower2(uint32* length_ptr, uint32* array)
{
    uint32 i;

    *length_ptr=10u;
    array[0] = 1u;

    for(i=1;i<(*length_ptr);i++)
    {
        array[i] = array[i-1]*2;
    }
}


int32_t TPSW2_CPYARRAY_BYLENGTH_UL(uint32 length_in,         mytest_t *array_in,
                                        uint32 length_out,   mytest_t *array_out,
                                        uint32 length_inout, mytest_t *array_inout)
{
  uint32 i;

  /***** in *****/
  for (i=0;i<length_in;i++)
  {
    if((array_in[i].a != (i+1u)) || (array_in[i].b != -((int8_t)i+1)))
    {
      TPSW2_ErrorCounter_UL++;
    }
  }

  /***** out *****/
  for (i=0;i<length_out;i++)
  {
    array_out[i].a = i;
    array_out[i].b = -(int8_t)i;
  }

  /***** inout *****/
  for (i=0;i<length_inout;i++)
  {
    array_inout[i].a++;
    array_inout[i].b++;
  }

  return 0;
}


int32_t TPSW2_CPYARRAY_FIRSTELEM_UL(uint32 *array_in,
                                         uint32 *array_out,
                                         uint32 *array_inout)
{
  uint32 i;

  /***** in *****/
  if(array_in[0]!=10u)
  {
      TPSW2_ErrorCounter_UL++;
  }
  for(i=1;i<=array_in[0];i++)
  {
    if(array_in[i] != i)
    {
      TPSW2_ErrorCounter_UL++;
    }
  }

  /***** out *****/
  array_out[0] = 48u;
  for(i=1u;i<=array_out[0];i++)
  {
    array_out[i] = array_out[0]+1u-i;
  }

  /***** inout *****/
  if(array_inout[0]!=12u)
  {
      TPSW2_ErrorCounter_UL++;
  }
  for(i=1u;i<=array_inout[0];i++)
  {
    array_inout[i]++;
  }

  return 0;
}


int32_t TPSW2_CPYARRAY_0TERM_UL(uint8_t *array_in,
                                     uint8_t *array_out,
                                     uint8_t *array_inout)
{
  uint32 i = 0;

  /***** in *****/
  while(array_in[i] != 0)
  {
    if(array_in[i] != (i+1u))
    {
      TPSW2_ErrorCounter_UL++;
    }
    i++;
  }
  if (i!=(18u))
  {
      TPSW2_ErrorCounter_UL++;
  }

  /***** out *****/
  array_out[40] = 0;
  for(i=0;i<40u;i++)
  {
    array_out[i] = (uint8_t)(i+1u);
  }

  /***** inout *****/
  i = 0;
  while(array_inout[i] != 0)
  {
    array_inout[i]++;
    i++;
  }
  if (i!=(19u))
  {
      TPSW2_ErrorCounter_UL++;
  }
  array_inout[i] = (uint8_t)(i+2u);
  array_inout[i+1u] = 0;

  return 0;
}

void TPSW2_WaitingFunction(uint32 Limit)
{
    WaitingFunction(RBSYS_convertUsecToTimerTicks(Limit));
}

uint32 TPSW2_WaitingFunction_TP(uint32 time_val)
{
    rbtpsw_CpuContext_t tprev;

    tprev = RBTPSW_Switch2PrivMode();
    TPSW3_WaitingFunction_UTTP_State = 2;
    RBTPSW_RestoreMode(tprev);

    TPSW2_WaitingFunction(time_val);

    tprev = RBTPSW_Switch2PrivMode();
    TPSW3_WaitingFunction_UTTP_State = 3;
    RBTPSW_RestoreMode(tprev);

    return 0;
}

uint32 TPSW2_WaitingFunction_NoTP(uint32 time_val)
{
    rbtpsw_CpuContext_t tprev;

    tprev = RBTPSW_Switch2PrivMode();
    TPSW3_WaitingFunction_UTTP_State = 2;
    RBTPSW_RestoreMode(tprev);

    TPSW2_WaitingFunction(time_val);

    tprev = RBTPSW_Switch2PrivMode();
    TPSW3_WaitingFunction_UTTP_State = 3;
    RBTPSW_RestoreMode(tprev);

    return 0;
}

#if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)

uint32 TPSW1_TPSW2_Before_Timing_Exc(uint32 y)
{
    volatile uint32 diff = 0;
    volatile uint32 cmp = 0;
    CoreIdType CoreId = TRUSTED_GetCoreId();

    if(CoreId == OS_CORE_ID_0)
    {
        #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        cmp = STM0CMP2A;
        #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        cmp = TPTMPE0TPTM0UCMP12;
        #endif
    }
    else
    {
        #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        cmp = STM0CMP2B;
        #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        cmp = TPTMPE0TPTM0UCMP13;
        #endif
    }

    do
    {
        #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        diff = cmp - STM0CNT2;
        #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        diff = cmp - TPTMPE0TPTM0UCNT1;
        #endif

    } while(diff > 25);

    TrustedData = 1; /* kill app */
    return 0;
}

void TPSW2_TPNoTP_LockTest(void) {
    RBTPSW_CALL(TPSW2_NoTP_LockTest());
}

void TPSW2_NoTP_LockTest(void) {
#if (RBFS_MCORE == RBFS_MCORE_ON)
    RBTPSW_EnterLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
    RBTPSW_ExitLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
#else
    RBTPSW_EnterCorelocalIntlock();
    RBTPSW_ExitCorelocalIntlock();
#endif
}

void TPSW2_TP_LockTest (void) {
#if (RBFS_MCORE == RBFS_MCORE_ON)
    /* expected to fail at EnterLock */
    RBTPSW_EnterLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
    /* add ExitLock so that we see no exception if the test doesn't fail as expected */
    RBTPSW_ExitLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
#else
    /* expected to fail at EnterCorelocalIntLock */
    RBTPSW_EnterCorelocalIntlock();
    /* add ExitCorelocalIntLoc so that we see no exception if the test doesn't fail as expected */
    RBTPSW_ExitCorelocalIntlock();
#endif
}

#endif

uint32 TPSW2_MpuExc_Lock(uint32 x)
{
    rbtpsw_CpuContext_t tprev;

    tprev = RBTPSW_Switch2PrivMode();
    RBSYS_EnterCorelocalIntlock();
    TPSW2_WaitingFunction(x);
    RBSYS_ExitCorelocalIntlock();
    RBTPSW_RestoreMode(tprev);

    // This test case shall never reach this point
    TrustedData = 1;
    return 0;
}

#endif

/** @} */
/* End ingroup 'SW-group' */
