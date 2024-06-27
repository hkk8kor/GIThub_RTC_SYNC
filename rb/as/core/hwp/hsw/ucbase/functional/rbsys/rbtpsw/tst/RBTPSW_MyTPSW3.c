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
#include "RBSYS_uCRegisters.h"  // peripheral labels
#include "RBSYS_SystemTimer.h"
#include "Os.h"


/* realized interfaces */
#include "RBTPSW_MyTPSWCapsule.h"
#include "RBTPSW_MyTPSW3.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWTestsuite,
                          RBFS_TPSWTestsuite_OFF,
                          RBFS_TPSWTestsuite_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A);


#if (RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON)

uint8 TPSW3_dummydata;

void TPSW3_BreakStack(void)
{
    volatile uint32* end;

    end = RBTPSW_CALL(TRUSTED_getStackEnd());

    // overwrite os stack
    *end = 0x4000ab01; end--;
    *end = 0x4000ab02; end--;
    *end = 0x4000ab03; end--;

    // ???
    *end = 0x4000ab04; end--;

    // overwrite stack frame of TRUSTED_UntrustedFuncCore0() for register 29 used by os
    *end = 0x40000029;
}

static void TPSW3_MoveSP(void* stackP);
__asmleaf void TPSW3_MoveSP(void* stackP)
{
%reg stackP
  mov  stackP, r3
%con stackP
  mov  stackP, r3
%mem stackP
  mov  stackP, r3
}


void TPSW3_InterruptLockSpBroken(void)
{
    TPSW3_MoveSP(&TrustedData);
    RBTPSW_EnterCorelocalIntlock();
    RBTPSW_ExitCorelocalIntlock();
}

void TPSW3_WriteStmRegOk(void)
{
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        STM0CMP3C = 0; // is opened by MPU channel
    #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        TPTMPE0TPTM0UCMP02 = TPTMPE0TPTM0UCMP02 + 1; // is opened by MPU channel. Write 0 would cause timing abort and false fail
    #endif
}

void TPSW3_WriteStmRegNotOk(void)
{
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        STM0CMP3D = 0; // is not opened by MPU channel
    #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        TPTMPE0TPTM0UCMP03 = 0; // is not opened by MPU channel
    #endif
}

static void TPSW3_OverwriteReg_intern(void);
__asmleaf void TPSW3_OverwriteReg_intern(void)
{
  // overwrite r1, r2, r6-r30 with 0x40000000
  // r3(sp), r4(gp), r5(tp) and r31(lp) must be preserved
  movhi hi(67108864),zero,r1
  mov  r1, r2
  mov  r1, r6
  mov  r1, r7
  mov  r1, r8
  mov  r1, r9
  mov  r1, r10
  mov  r1, r11
  mov  r1, r12
  mov  r1, r13
  mov  r1, r14
  mov  r1, r15
  mov  r1, r16
  mov  r1, r17
  mov  r1, r18
  mov  r1, r19
  mov  r1, r20
  mov  r1, r21
  mov  r1, r22
  mov  r1, r23
  mov  r1, r24
  mov  r1, r25
  mov  r1, r26
  mov  r1, r27
  mov  r1, r28
  mov  r1, r29
  mov  r1, r30
}

static void TPSW3_OverwriteRegAndSpGpTp_intern(void);
__asmleaf void TPSW3_OverwriteRegAndSpGpTp_intern(void)
{
  // overwrite r1-r30 with 0x40000000
  // r31(lp) must be preserved
  movhi hi(67108864),zero,r1
  mov  r1, r2
  mov  r1, r3
  mov  r1, r4
  mov  r1, r5
  mov  r1, r6
  mov  r1, r7
  mov  r1, r8
  mov  r1, r9
  mov  r1, r10
  mov  r1, r11
  mov  r1, r12
  mov  r1, r13
  mov  r1, r14
  mov  r1, r15
  mov  r1, r16
  mov  r1, r17
  mov  r1, r18
  mov  r1, r19
  mov  r1, r20
  mov  r1, r21
  mov  r1, r22
  mov  r1, r23
  mov  r1, r24
  mov  r1, r25
  mov  r1, r26
  mov  r1, r27
  mov  r1, r28
  mov  r1, r29
  mov  r1, r30
}


void TPSW3_OverwriteReg(void)
{
    TPSW3_OverwriteReg_intern();
}

void TPSW3_OverwriteRegAndSpGpTp(void)
{
    TPSW3_OverwriteRegAndSpGpTp_intern();
}



static void TPSW3_OverwriteGp_intern(void);
__asmleaf void TPSW3_OverwriteGp_intern(void)
{
  // overwrite gp (r4) with 0x40000000
  movhi hi(67108864),zero,r1
  mov  r1, r4
}

static void TPSW3_OverwriteTp_intern(void);
__asmleaf void TPSW3_OverwriteTp_intern(void)
{
  // overwrite tp (r5) with 0x40000000
  movhi hi(67108864),zero,r1
  mov  r1, r5
}

static void TPSW3_OverwriteEp_intern(void);
__asmleaf void TPSW3_OverwriteEp_intern(void)
{
  // overwrite ep (r30) with 0x40000000
  movhi hi(67108864),zero,r1
  mov  r1, r30
}

static void TPSW3_OverwriteLp_intern(void);
__asmleaf void TPSW3_OverwriteLp_intern(void)
{
  // overwrite lp (r31) with 0x800000000
  movhi hi(2147483648),zero,r1
  mov  r1, r31
}
void TPSW3_OverwriteGp(void){TPSW3_OverwriteGp_intern();}
void TPSW3_OverwriteTp(void){TPSW3_OverwriteTp_intern();}
void TPSW3_OverwriteEp(void){TPSW3_OverwriteEp_intern();}
void TPSW3_OverwriteLp(void){TPSW3_OverwriteLp_intern();}






static void TPSW3_ForceWrite(volatile uint8* addr)
{
    *addr = 0xab;
}

void TPSW3_StackSizeCheck(void)
{
    volatile uint8 dummy;
    volatile uint8* addr = &dummy - TPSW3_LOCAL_ARRAY;

    TPSW3_ForceWrite(addr);
}




void TPSW3_WaitingFunction(Os_StopwatchTickType duration)
{
    WaitingFunction(RBSYS_convertUsecToTimerTicks(duration));
}

volatile uint32 TPSW3_WaitingFunction_Switch2Trust_State;
uint32 TPSW3_WaitingFunction_Switch2Trust(const TPSW3_WaitingFunction_Switch2Trust_t* p)
{
    rbtpsw_CpuContext_t tprev;

    TPSW3_WaitingFunction_Switch2Trust_State = 0;
    TPSW3_WaitingFunction(p->untrustedTimeBefore);
    TPSW3_WaitingFunction_Switch2Trust_State = 1;

    tprev = RBTPSW_Switch2PrivMode();
    {
        TPSW3_WaitingFunction_Switch2Trust_State = 2;
        TPSW3_WaitingFunction(p->trustedTime);
        TPSW3_WaitingFunction_Switch2Trust_State = 3;
    }
    RBTPSW_RestoreMode(tprev);

    TPSW3_WaitingFunction_Switch2Trust_State = 4;
    TPSW3_WaitingFunction(p->untrustedTimeAfter);
    TPSW3_WaitingFunction_Switch2Trust_State = 5;

    return 0;
}

volatile uint32 TPSW3_WaitingFunction_UTnoTP_State;
uint32 TPSW3_WaitingFunction_UTnoTP(const TPSW3_WaitingFunction_Switch2Trust_t* p)
{
    TPSW3_WaitingFunction_UTnoTP_State = 0;
    TPSW3_WaitingFunction(p->untrustedTimeBefore);
    TPSW3_WaitingFunction_UTnoTP_State = 1;

    RBTPSW_CALL(TPSW2_1Param_V(1));

    TPSW3_WaitingFunction_UTnoTP_State = 4;
    TPSW3_WaitingFunction(p->untrustedTimeAfter);
    TPSW3_WaitingFunction_UTnoTP_State = 5;

    return 0;
}

volatile uint32 TPSW3_WaitingFunction_UTTP_State;
uint32 TPSW3_TPSW2_WaitingFunction_UTTP(const TPSW3_WaitingFunction_Switch2Trust_t* p)
{
    TPSW3_WaitingFunction_UTTP_State = 0;
    TPSW3_WaitingFunction(p->untrustedTimeBefore);
    TPSW3_WaitingFunction_UTTP_State = 1;

    (void)RBTPSW_CALL(TPSW2_WaitingFunction_TP(p->trustedTime));

    TPSW3_WaitingFunction_UTTP_State = 4;
    TPSW3_WaitingFunction(p->untrustedTimeAfter);
    TPSW3_WaitingFunction_UTTP_State = 5;

    return 0;
}

uint32 TPSW3_TPSW2_WaitingFunction_UTTP_NoTp(const TPSW3_WaitingFunction_Switch2Trust_t* p)
{
    TPSW3_WaitingFunction_UTTP_State = 0;
    TPSW3_WaitingFunction(p->untrustedTimeBefore);
    TPSW3_WaitingFunction_UTTP_State = 1;

    (void)RBTPSW_CALL(TPSW2_WaitingFunction_NoTP(p->trustedTime));

    TPSW3_WaitingFunction_UTTP_State = 4;
    TPSW3_WaitingFunction(p->untrustedTimeAfter);
    TPSW3_WaitingFunction_UTTP_State = 5;

    return 0;
}

uint32 TPSW3_WaitingFunction_UTTP(const TPSW3_WaitingFunction_Switch2Trust_t* p)
{
    TPSW3_WaitingFunction_UTTP_State = 0;
    TPSW3_WaitingFunction(p->untrustedTimeBefore);
    TPSW3_WaitingFunction_UTTP_State = 1;

    TPSW3_WaitingFunction_UTTP_State = 2;
    TPSW3_WaitingFunction(p->trustedTime);
    TPSW3_WaitingFunction_UTTP_State = 3;

    TPSW3_WaitingFunction_UTTP_State = 4;
    TPSW3_WaitingFunction(p->untrustedTimeAfter);
    TPSW3_WaitingFunction_UTTP_State = 5;

    return 0;
}


uint32 TPSW3_TimingAndMpuAbort(uint32 x)
{
    TPSW3_WaitingFunction(x);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        STM0CMP3D = 0; // is not opened by MPU channel --> mpu exc
    #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        TPTMPE0TPTM0UCMP03 = 1; // is not opened by MPU channel -->  mpu exc
    #endif
    
    return 0;
}

uint32 TPSW3_TimingAndMpuAbort_Tp(uint32 x)
{
    TPSW3_WaitingFunction(x);
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        STM0CMP3D = 0; // is not opened by MPU channel --> mpu exc
    #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        TPTMPE0TPTM0UCMP03 = 1; // is not opened by MPU channel -->  mpu exc
    #endif
    
    return 0;
}

#endif

/** @} */
/* End ingroup 'SW-group' */
