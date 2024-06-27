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
#include "RBSYS_Intrinsics.h"
#include "RBLCF_MemoryMap.h"
#include "RBSYS_uCResetCtrl.h"
#include "rba_MultiStackTrace.h"
#include "RBLCF_MemoryRemap.h"
#include "RBSYS_uCRegisters.h"  // peripheral labels
#include <math.h>
#include <float.h>
#include "RBTPSW_MyTPSW_RAMBackupService.h"



/* realized interfaces */
#include "RBTPSW_MyTPSWCapsule.h"
#include "RBTPSW_MyTPSW1.h"
#include "RBTPSW_MyTPSW2.h"
#include "RBTPSW_MyTPSW3.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);
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
RB_ASSERT_SWITCH_SETTINGS(RBFS_FlashBank0Support,
                          RBFS_FlashBank0Support_OFF,
                          RBFS_FlashBank0Support_INACTIVE,
                          RBFS_FlashBank0Support_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_FlashBank1Support,
                          RBFS_FlashBank1Support_OFF,
                          RBFS_FlashBank1Support_INACTIVE,
                          RBFS_FlashBank1Support_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_FlashBank2Support,
                          RBFS_FlashBank2Support_OFF,
                          RBFS_FlashBank2Support_INACTIVE,
                          RBFS_FlashBank2Support_ON);
RB_ASSERT_SWITCH_SETTINGS(RBFS_FlashBank3Support,
                          RBFS_FlashBank3Support_OFF,
                          RBFS_FlashBank3Support_INACTIVE,
                          RBFS_FlashBank3Support_ON);

#if (RBFS_TPSWTestsuite == RBFS_TPSWTestsuite_ON)

#define TRBTPSW_RBSECTION_START_GRAM_TEXT     RBSECTION_START_REMAP_TEXT(.gram_text)
#define TRBTPSW_RBSECTION_END_GRAM_TEXT       RBSECTION_END_REMAP_TEXT

#define TPSW1_FIRST_TIMING_TC 106


volatile boolean TPSW1_ActiveWaiting = false;
volatile boolean TPSW1_ActiveWaitingPreemptedCoreAck = false;
volatile boolean TPSW1_ActiveWaitingMultiCoreAck = false;

/************************************************************************************************************/
/** when using TPSW1_TestCaseIdMultiCore for triggering a test on core1, care must be taken not to kill TPSW1! **/
/************************************************************************************************************/
static volatile uint32 TPSW1_TestCaseIdMultiCore = 0;


static inline void access_all_stack(void)
{
    uint32* adr;
    uint32* start = RBTPSW_CALL(TRUSTED_getStackStart());

    {
        uint32 dummy = 0;

        for(adr=start; adr<=&dummy; adr++)
        {
            (*adr)++;
        }
    }
}

void TPSW1_ActiveWaitingPreemptedCore(void)
{
    access_all_stack();

    MYTPSW_CHECK_SF(FALSE);

    while(TPSW1_ActiveWaiting == true)
    {
        TPSW1_ActiveWaitingPreemptedCoreAck = true;
    }

    MYTPSW_CHECK_SF(FALSE);

    TPSW1_ActiveWaitingPreemptedCoreAck = false;
}

#if (RBFS_MCORE == RBFS_MCORE_ON)
void TPSW1_ActiveWaitingMultiCore(void)
{
    boolean activeWaiting = false;
    uint32 testCaseIdMultiCore = 0;
    access_all_stack();


    activeWaiting = TPSW1_ActiveWaiting;
    testCaseIdMultiCore = TPSW1_TestCaseIdMultiCore;
    while((activeWaiting == true) || (testCaseIdMultiCore != 0))
    {
        TPSW1_ActiveWaitingMultiCoreAck = true;

        /* when using TPSW1_TestCaseIdMultiCore for triggering a test on core1, care must be taken not to kill TPSW1! */
        switch(TPSW1_TestCaseIdMultiCore)
        {
            case TPSW1_FIRST_TIMING_TC + 0:
            {
                /* Testcase description: Good cases  */
                /* Desired Reaction:     No Reaction */
                TPSW1_TestGoodCases();

                (void)RBTPSW_CALL(TPSW3_WaitingFunction(0));
                (void)RBTPSW_CALL(TPSW3_WaitingFunction(TPSW3_WAITINGFUNCTION_TIMELIMIT - 25));

                TPSW1_TPSW3_WaitingFunction_Switch2Trust_GC();

                TPSW1_TestCaseIdMultiCore = 0;
                break;
            }

            case TPSW1_FIRST_TIMING_TC + 6:
            {
                /* Testcase description: See below. */
                /* Desired Reaction:     See below. */
                (void)RBTPSW_CALL(TPSW3_WaitingFunction(TPSW3_WAITINGFUNCTION_TIMELIMIT + 1));
                TPSW1_TestCaseIdMultiCore = 0;
                break;
            }

            case TPSW1_FIRST_TIMING_TC + 7:
            {
                /* Testcase description: See below. */
                /* Desired Reaction:     See below. */
                TPSW1_TPSW3_WaitingFunction_Switch2Trust_BC1();
                TPSW1_TestCaseIdMultiCore = 0;
                break;
            }

            case TPSW1_FIRST_TIMING_TC + 8:
            {
                /* Testcase description: See below. */
                /* Desired Reaction:     See below. */
                TPSW1_TPSW3_WaitingFunction_Switch2Trust_BC2();
                TPSW1_TestCaseIdMultiCore = 0;
                break;
            }

            case TPSW1_FIRST_TIMING_TC + 9:
            {
                /* Testcase description: See below. */
                /* Desired Reaction:     See below. */
                TPSW1_TPSW3_WaitingFunction_Switch2Trust_BC3();
                TPSW1_TestCaseIdMultiCore = 0;
                break;
            }

            default:
            {
                break;
            }
        }
        activeWaiting = TPSW1_ActiveWaiting;
        testCaseIdMultiCore = TPSW1_TestCaseIdMultiCore;
    }

    TPSW1_ActiveWaitingMultiCoreAck = false;
}
#endif


static void TPSW1_PushSP(uint32 val);
__asmleaf void TPSW1_PushSP(uint32 val)
{
%reg val
  mov  val, r26
  prepare {r26},0
%con val
  mov  val, r26
  prepare {r26},0
%mem val
  mov  val, r26
  prepare {r26},0
}


static void TPSW1_ReservedInstructionFunc(void)
{
    asm("rie\n");
}


TRBTPSW_RBSECTION_START_GRAM_TEXT
static void TPSW1_ReservedInstructionFunc_in_GRAM(void)
{
    asm("rie\n");
}
TRBTPSW_RBSECTION_END_GRAM_TEXT

#define TPSW1_DATATABLESIZE 100
static uint32 TPSW1_DataTable[TPSW1_DATATABLESIZE];

static rbtpsw_appstatus_t TPSW1_Tpsw2StateByApp;
static rbtpsw_appstatus_t TPSW1_Tpsw2StateByFunc;
static rbtpsw_debuginfo_t TPSW1_Tpsw2DebugCore0;
static rbtpsw_debuginfo_t TPSW1_Tpsw2DebugCore1;

static volatile uint8 TPSW1_Global_u8;
static volatile uint32 TPSW1_Global_u32 = 0;

// div by 0 tests
float TPSW1_Zero_f = 0.0f;
float TPSW1_Value_f = 1.0f;
float TPSW1_Inf_f = INFINITY;
uint32 TPSW1_SNaN_u32 = 0x7fa00000u; // Exponent all 1s and Mantissa != 0 with the highest bit 0 which makes it signalling. Because we can't specify floats with hex we need to trick here with pointers
float TPSW1_SNaN_f = 0.0f; //Filled in testcase
float TPSW1_Result_f;

double TPSW1_Zero_d = 0.0;
double TPSW1_Value_d = 1.0;
double TPSW1_Inf_d = HUGE_VAL;
uint64 TPSW1_SNaN_u64 = 0x7FF4000000000000u; // Exponent all 1s and Mantissa != 0 with the highest bit 0 which makes it signalling. Because we can't specify doubles with hex we need to trick here with pointers
double TPSW1_SNaN_d = 0.0; //Filled in testcase
double TPSW1_Result_d;

static volatile uint32 TPSW1_Zero_u32 = 0;
static volatile uint32 TPSW1_Value_u32 = 1u;
static volatile uint32 TPSW1_Result_u32;


/***********************************************************************************************************/
/** TPSW1_ForceTestId == 0 ---> Automatic test mode: the TestId test coming from TPSW2 will be performed. **/
/** TPSW1_ForceTestId != 0 ---> Debugger test mode: The TPSW1_ForceTestId test will be performed.         **/
/***********************************************************************************************************/
uint32 TPSW1_ForceTestId = 0;

/************************************************************************************************************/
/** test function to be located in GRAM                                                                    **/
/************************************************************************************************************/
TRBTPSW_RBSECTION_START_GRAM_TEXT
static int __attribute__((noinline)) sum_in_ram(int a, int b)
{
    return a + b;
}
TRBTPSW_RBSECTION_END_GRAM_TEXT

/************************************************************************************************************/
/** Executes test TestId                                                                                   **/
/************************************************************************************************************/
void TPSW1_TestExecution(void* sp_before, uint32 TestId)
{
    MYTPSW_CHECK_SF(TRUE);

    if(TPSW1_ForceTestId != 0)
    {
        TestId = TPSW1_ForceTestId;
    }

    switch(TestId)
    {
        case 1:
        /* Testcase description:  Set stackpointer to a not allowed area (above)       */
        /* Desired Reaction:      MPU Exc MDP (TPSW1)                                  */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TRUSTED_MoveSP(sp_before);
            TPSW1_PushSP(0x0123abcd);
            break;
        }

        case 2:
        /* Testcase description:  Set stackpointer to a not allowed area (below)       */
        /* Desired Reaction:      MPU Exc MDP (TPSW1)                                  */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            void* sp_after = (void *)((uint8*)sp_before - (TPSW1_TestExecution_STACK + 0x200));
            TRUSTED_MoveSP(sp_after);
            TPSW1_PushSP(0x0123abcd);
            break;
        }

        case 3:
        /* Testcase description:  RAM access (read) to a forbidden area which                 */
        /*                        is the next address after MYTPSW1 area                      */
        /* Desired Reaction:      no reaction, read allowed                                   */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            volatile uint8* ptr = (volatile uint8*)&RBTPSW_LINKERSYMBOL_MYTPSW1_LCF_end + 1;
            TPSW1_Global_u8 = *ptr;
            break;
        }

        case 4:
        /* Testcase description:  Try to execute a function which is located in a not         */
        /*                        allowed RAM area.                                           */
        /* Desired Reaction:      MPU Exc MIP (TPSW1)                                         */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            vvfunc_t *adr;
            #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
                adr = (vvfunc_t*)RBLCF_getStartAddress_GRAM();
            #elif (RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON)
                adr = (vvfunc_t*)RBLCF_getStartAddress_CRAM0();
            #else
                #error "Unsupported memory configuration"
            #endif
            adr();
            break;
        }

        case 5:
        /* Testcase description:  Try to execute a function which is located in a not         */
        /*                        allowed device area (local ram 0).                          */
        /* Desired Reaction:      MPU Exc MIP (TPSW1)                                         */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            vvfunc_t *adr;
            #if (RBFS_MCORE == RBFS_MCORE_ON)
              adr=(vvfunc_t*)MYTPSW2_LRAM0_Table;
            #else
                #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
                    adr = (vvfunc_t*)RBLCF_getStartAddress_GRAM();
                #elif (RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON)
                    adr = (vvfunc_t*)RBLCF_getStartAddress_CRAM0();
                #else
                    #error "Unsupported memory configuration"
                #endif
            #endif
            adr();
            break;
        }

        case 6:
        /* Testcase description:  Try to execute a function which is located in a not         */
        /*                        allowed device area (local ram 1).                          */
        /* Desired Reaction:      MPU Exc MIP (TPSW1)                                         */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            vvfunc_t *adr;
            #if (RBFS_MCORE == RBFS_MCORE_ON)
              adr=(vvfunc_t*)MYTPSW2_LRAM1_Table;
            #else
                #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
                    adr = (vvfunc_t*)RBLCF_getStartAddress_GRAM();
                #elif (RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON)
                    adr = (vvfunc_t*)RBLCF_getStartAddress_CRAM0();
                #else
                    #error "Unsupported memory configuration"
                #endif
            #endif
            adr();
            break;
        }

        case 7:
        /* Testcase description:  Try to execute a function which is located in a not         */
        /*                        allowed device area (DTS).                                  */
        /* Desired Reaction:      MPU Exc MIP (TPSW1)                                         */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            vvfunc_t *adr;
            #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
                adr = (vvfunc_t*)&DTS000CM; // DTS000CM register
            #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
                adr = (vvfunc_t*)&SDMAC0DMA0CM_0;
            #endif
            adr();
            break;
        }

        case 8:
        /* Testcase description:  Not allowed RAM access (read) to Peripheral DTS             */
        /* Desired Reaction:      MPU Exc MDP (TPSW1)                                         */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
                TPSW1_Global_u32 = DTS000CM;
            #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
                TPSW1_Global_u32 = SDMAC0DMA0CM_0;
            #endif
            break;
        }

        case 9:
        /* Testcase description:  Not allowed register access (read) to timer register        */
        /* Desired Reaction:      MPU Exc MDP (TPSW1)                                         */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
                TPSW1_Global_u32 = STM0STC;
            #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
                TPSW1_Global_u32 = TPTMPE0TPTM0UTRG;
            #endif
            break;
        }

        case 10:
        /* Testcase description:  RAM access (read) to invalid address                        */
        /* Desired Reaction:      MPU Exc MDP (TPSW1)                                         */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
                #define RBTPSW_RESERVED_ADDRESS     0x00700000U
            #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
                #define RBTPSW_RESERVED_ADDRESS     0x03000000U
            #endif
            TPSW1_Global_u32 = *((volatile uint32*)RBTPSW_RESERVED_ADDRESS);
            break;
        }

        case 11:
        /* Testcase description:  RAM access (write) to next adress after TPSW area (global)  */
        /* Desired Reaction:      MPU Exc MDP (TPSW1)                                         */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            volatile uint8* ptr = (volatile uint8*)&RBTPSW_LINKERSYMBOL_MYTPSW1_LCF_end + 4;
            *ptr = 0xab;
            break;
        }

        case 12:
        /* Testcase description:  Not allowed RAM access (write) to Peripheral DTS RAM        */
        /* Desired Reaction:      MPU Exc MDP (TPSW1)                                         */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
                DTS000CM = 1;
            #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
                SDMAC0DMA0CM_0 = 1;
            #endif
            break;
        }

        case 13:
        /* Testcase description:  Not allowed register access (write) to timer register       */
        /* Desired Reaction:      MPU Exc MDP (TPSW1)                                         */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
                STM0STC = 1;
            #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
                TPTMPE0TPTM0UTRG = 1;
            #endif
            break;
        }

        case 14:
        /* Testcase description:  RAM access (write) to invalid address                       */
        /* Desired Reaction:      MPU Exc MDP (TPSW1)                                         */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
                *((unsigned int*)RBLCF_getStartAddress_GRAM())=0;
            #elif (RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON)
                *((unsigned int*)RBLCF_getStartAddress_CRAM0())=0;
            #else
                #error "Unsupported memory configuration"
            #endif
            break;
        }

        case 15:
        /* Testcase description:  Try to use intlock API in User Mode directly                */
        /* Desired Reaction:      PIE Exc (TPSW1)                                             */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0xa0, 0, 18, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBSYS_EnterCommonLock();
            break;
        }

        case 16:
        /* Testcase description:  Try to change processor mode.                               */
        /* Desired Reaction:      PIE exception (TPSW1)                                       */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0xa0, 0, 18, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            uint32 psw = RBSYS_STSR(5, 0); // stsr is allowed for PSW.UM --> ok, no exc
            psw &= (~0x40000000U); // reset PSW.UM
            RBSYS_LDSR(0, 6, psw); // ldsr is not allowed for PSW in user mode --> PIE exc
            break;
        }

        case 17:
        /* Testcase description:  Try to execute an undefined instruction.                    */
        /* Desired Reaction:      RIE Exception (TPSW1)                                       */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x60, 0, 18, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_ReservedInstructionFunc();
            break;
        }

        case 18:
        /* Testcase description:  pointer "z" points to an odd address (wrong alignment)      */
        /* Desired Reaction:      P1X:                                                        */
        /*                          No reaction (in future strict alignment to be switched on)*/
        /*                        U2A:                                                        */
        /*                          MAE Exc (TPSW1), strict alignement is activated           */
        #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
            #if (RBFS_Compiler != RBFS_Compiler_GHS)
                RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0xC0, 0, 18, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
            #else
                RBTPSW_SetExpectedResultToNoReaction();
            #endif
        #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
            RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0xC0, 0, 18, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        #endif
        {
            volatile char x[10];


/* Suppress compiler diagnostic #2003-D
* "alignment of type pointed to by "volatile char *" is smaller than the one pointed to by "volatile int *",
* which may lead to a misaligned memory access
*/
#ifdef __ghs__
#pragma ghs nowarning 2003
#endif

            volatile int* y = (volatile int*) &x[0];
            volatile int* z = (volatile int*) &x[1];

#ifdef __ghs__
#pragma ghs endnowarning 2003
#endif

            volatile int a;
            a = *y;
            a = *z;
            break;
        }

        case 19:
        RBTPSW_SetExpectedResultToNoReaction();
        {
#if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)

            /* Temporarily deactivated test case 19 for U2A.
             * Dependent on RTAOS EHI 628749 fix in RH850 U2A target port 5.0.4 this can either be activated or it must be documented.
             */
#else
            /* Testcase description: overwrite r1, r2, r6-r30 with faulty 0x40000000     */
            /*                       r3(sp), r4(gp), r5(tp) and r31(lp) are preserved    */
            /* Desired Reaction: TPSW3: nothing should happen because registers must be  */
            /*                   restored with longjmp                                   */
            rbtpsw_appstatus_t mystatus = RBTPSW_START(TPSW3_OverwriteReg);
#endif
            break;
        }

        case 20:
        /* Testcase description: overwrite r1-r30 with faulty 0x40000000              */
        /*                       r31(lp) is preserved                                 */
        /* Desired Reaction: MPU Exc MIP (TPSW3 -> caused by Enhanced Isolation)      */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, 0x90, 9, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_CALL(TPSW3_OverwriteRegAndSpGpTp());
            break;
        }

        case 21:
        /* This test case is only relevant for the RH850 P1x target port of RTA-OS.     */
        /* This target port uses the first entries of the UT stack inside of OS in      */
        /* trusted context (weak implementation...). This tests verifies that the OS    */
        /* does not use the corrupted values in trusted context.                        */

        /* Testcase description:  Overwriting of Os stack (12 bytes data)               */
        /* Desired reaction:      nothing because OS not allowed to touch data on stack */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            /* Test case is not relevant for the RH850 U2A port                             */
            #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
                uint32* aligned_stack_start = RBTPSW_CALL(TRUSTED_getStackEnd());

                *(aligned_stack_start - 0) = 0xDEADBEEF;
                *(aligned_stack_start - 1) = 0xDEADBEEF;
                *(aligned_stack_start - 2) = 0xDEADBEEF;
            #endif
            break;
        }

        case 22:
        /* Testcase description:  Try to access RAM (write) of the other TPSW2  */
        /* Desired Reaction:      MPU Exc MDP (TPSW1)                           */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            MYTPSW2_Data = 0x123abcd;
            break;
        }

        case 23:
        /* Testcase description:  Try to access last RAM address (read/write) of TPSW area    */
        /* Desired Reaction:      no reaction                                                 */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            volatile uint32* ptr = (volatile uint32 *)&RBTPSW_LINKERSYMBOL_MYTPSW1_LCF_end;
            (*ptr)++;
            (*ptr)--;
            break;
        }

        case 24:
        /* Testcase description:  Try to access first RAM address (read/write) of TPSW area   */
        /* Desired Reaction:      no reaction                                                 */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            volatile uint32* ptr = (volatile uint32 *)&RBTPSW_LINKERSYMBOL_MYTPSW1_LCF_start;
            (*ptr)++;
            (*ptr)--;
            break;
        }

        case 25:
        /* Testcase description:  Try to access first RAM address (write) before TPSW area    */
        /* Desired Reaction:      MPU Exc MDP (TPSW1)                                         */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            volatile uint8* ptr = (volatile uint8*)&RBTPSW_LINKERSYMBOL_MYTPSW1_LCF_start - 4;
            *ptr = 0xab;
            break;
        }

        case 26:
        /* Testcase description:  Read flash at any location in bank 0                        */
        /* Desired Reaction:      MPU exc if flash bank 0 is inactive, no reaction otherwise  */
        #if (RBFS_FlashBank0Support == RBFS_FlashBank0Support_INACTIVE)
            RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        #else
            RBTPSW_SetExpectedResultToNoReaction();
        #endif
        {
            #if(RBFS_FlashBank0Support == RBFS_FlashBank0Support_ON)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_ActiveBank0();
                TPSW1_Global_u32 = *ptr;
            #elif(RBFS_FlashBank0Support == RBFS_FlashBank0Support_INACTIVE)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_InactiveBank0();
                TPSW1_Global_u32 = *ptr;
            #endif
            break;
        }

        case 27:
        /* Testcase description:  Write flash at any location in bank 0                       */
        /* Desired Reaction:      MPU Exc MDP (TPSW1)                                         */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            #if(RBFS_FlashBank0Support == RBFS_FlashBank0Support_ON)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_ActiveBank0();
                *ptr = 1;
            #elif(RBFS_FlashBank0Support == RBFS_FlashBank0Support_INACTIVE)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_InactiveBank0();
                *ptr = 1;
            #endif
            break;
        }

        case 28:
        /* Testcase description:  use not allowed RB inline function                          */
        /* Desired Reaction:      PIE Exc (TPSW1)                                             */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0xa0, 0, 18, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBSYS_uCReset_ApplResetSkipBootBlock();
            break;
        }

        case 29:
        /* Testcase description:  use not allowed RB function                                 */
        /* Desired Reaction:      any Exc (TPSW1)                                             */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, RBTPSW_EXPECTEDRESULT_DONTCARE, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            (void)rba_MultiStackTrace_ScanCoreLocalStacks();
            break;
        }

        case 30:
        /* Testcase description:  Set SP in TPSW2 to a not allowed area (above),              */
        /*                        wait for preemption (detection is done by untrusted stack   */
        /*                        check)                                                      */
        /* Desired Reaction:      MPU Exc MIP (TPSW2 -> caused by Enhanced Isolation)         */
        // Test case not supported unless Enhanced Isolation is enabled.
        RBTPSW_SetExpectedResult(2, NOT_ACTIVE, 0x90, 9, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_CALL(TPSW2_UTStackCheckTestAbove());
            break;
        }

        case 31:
        /* Testcase description:  Set SP in TPSW2 to a not allowed area (below),              */
        /*                        wait for preemption (detection is done by untrusted stack   */
        /*                        check)                                                      */
        /* Desired Reaction:      MPU Exc MIP (TPSW2 -> caused by Enhanced Isolation)         */
        // Test case not supported unless Enhanced Isolation is enabled.
        RBTPSW_SetExpectedResult(2, NOT_ACTIVE, 0x90, 9, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_CALL(TPSW2_UTStackCheckTestBelow());
            break;
        }

        case 32:
        /* Testcase description:  good case for RBTPSW_Switch2PrivMode */
        /* Desired Reaction:      no reaction                          */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            rbtpsw_CpuContext_t prevMode = RBTPSW_Switch2PrivMode();
            TrustedData++;
            RBTPSW_RestoreMode(prevMode);
            break;
        }

#if (RBFS_MCORE == RBFS_MCORE_ON)
        /* RBTPSW Lock code is currently only valid for multi core.
         * See code/comment at top of RBTPSW_EnterLock().
         */
        case 33:
        /* Testcase description:  UT-T call with int lock                                      */
        /* Desired Reaction:      TPSW1 aborted with userinfo = 1 (RBTPSW_USERINFO_LOCKACTIVE) */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 1, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_EnterLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
            RBTPSW_CALL(TRUSTED_1Param_V (1));
            break;
        }

        case 34:
        /* Testcase description:  Call lock which is not allowed                               */
        /* Desired Reaction:      TPSW1 aborted with userinfo = 4 (RBTPSW_USERINFO_WRONGLOCK)  */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 4, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_EnterLock(ANY_LOCK);
            break;
        }

        case 35:
        /* Testcase description:  Call lock which is not allowed                               */
        /* Desired Reaction:      TPSW1 aborted with userinfo = 4 (RBTPSW_USERINFO_WRONGLOCK)  */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 4, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            lockstr_t x = {0};
            RBTPSW_EnterLock(&x);
            break;
        }

        case 36:
        /* Testcase description:  T-UT call with int lock and common lock                       */
        /* Desired Reaction:      TPSW2 and TPSW3 aborted with                                  */
        /*                        userinfo = 5 (RBTPSW_USERINFO_LOCKACTIVE_TRUSTED)             */
        RBTPSW_SetExpectedResult(2, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 5, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 5, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_CALL(TRUSTED_T_UT_CallWithLocks());
            break;
        }
#else
        case 33:
        case 34:
        case 35:
        case 36:
            RBTPSW_SetExpectedResultToNoReaction();
            break;
#endif

        case 37:
        /* Testcase description:  UT-UT call to MYTPSW2 with access to MYTPSW1 RAM */
        /*                        This test ensures that the mpu channel           */
        /*                        reconfiguration was performed                    */
        /* Desired Reaction:      MPU Exception (TPSW2)                            */
        RBTPSW_SetExpectedResult(2, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_CALL(TPSW2_WriteAccessTpsw1());
            break;
        }

        case 38:
        /* Testcase description:  set trust, set untrust, access to privileged RAM */
        /* Desired Reaction:      MPU Exception (TPSW1)                            */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            {
                rbtpsw_CpuContext_t prevMode = RBTPSW_Switch2PrivMode();

                TrustedData++;

                RBTPSW_RestoreMode(prevMode);
            }
            TrustedData++; // check that the mode was restored correctly
            break;
        }

        case 39:
        /* Testcase description:  Access to timer with MYTPSW3 */
        /* Desired Reaction:      Nothing (good case)          */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            RBTPSW_CALL(TPSW3_WriteStmRegOk());
            break;
        }

        case 40:
        /* Testcase description:  Access (write) to not allowed device area (timer) with MYTPSW3. */
        /* Purpose:               test of RBTPSW_MPUCONFIG_BYADDRESS                              */
        /* Desired Reaction:      MPU Exception (TPSW3)                                           */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_CALL(TPSW3_WriteStmRegNotOk());
            break;
        }

        case 41:
        /* Testcase description:  Access (write) to not allowed RAM area with MYTPSW4. */
        /* Purpose:               test of RBTPSW_MPUCONFIG_BYADDRESS                   */
        /* Desired Reaction:      MPU Exception (TPSW4)                                */
        RBTPSW_SetExpectedResult(4, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_CALL(TPSW4_OutOfRange());
            break;
        }

        case 42:
        /* Testcase description:  check plausibility of MPUtable                        */
        /* Desired Reaction:      userinfo = 2 (RBTPSW_USERINFO_PLAUSIBILITY) for       */
        /*                          TPSW5,6,7,8,9,10 (bad case)                         */
        RBTPSW_SetExpectedResult(5, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 2, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        RBTPSW_SetExpectedResult(6, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 2, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        RBTPSW_SetExpectedResult(7, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 2, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        RBTPSW_SetExpectedResult(8, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 2, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        RBTPSW_SetExpectedResult(9, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 2, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        RBTPSW_SetExpectedResult(10, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 2, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_CALL(TPSW5_DummyFunc() );
            RBTPSW_CALL(TPSW6_DummyFunc() );
            RBTPSW_CALL(TPSW7_DummyFunc() );
            RBTPSW_CALL(TPSW8_DummyFunc() );
            RBTPSW_CALL(TPSW9_DummyFunc() );
            RBTPSW_CALL(TPSW10_DummyFunc());
            break;
        }

        case 43:
        /* Testcase description:  SP is out of its range. UT-UT call.                        */
        /* Desired Reaction:      MYTPSW1 -> MPU Exc MIP (caused by Enhanced Isolation)      */
        /* In this test case, the Enhanced Isolation stack check is tested when switching to */
        /* trusted mode at the beginning of RBTPSW_CALL().                                   */
        /* The C logic is tested here: write on the stack by writing on a volatile local     */
        /* variable. This must be checked for each compiler update.                          */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TRUSTED_MoveSP(sp_before);
            RBTPSW_CALL(TPSW2_1Param_V (1));
            break;
        }

        case 44:
        /* Testcase description: Call int lock and common lock with broken SP                */
        /* Desired Reaction:     MPU Exc(MYTPSW2, MYTPSW3)                                   */
        RBTPSW_SetExpectedResult(2, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_CALL(TPSW2_CommonLockSpBroken());
            RBTPSW_CALL(TPSW3_InterruptLockSpBroken());
            break;
        }

        case 45:
        /* Testcase description: Suspend and resume interrupt                                */
        /* Desired Reaction:     No Reaction                                                 */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            RBTPSW_EnterCorelocalIntlock();
            RBTPSW_ExitCorelocalIntlock();
            break;
        }

        case 46:
        /* Testcase description: Call of TPSW_Switch2PrivMode with broken SP                 */
        /* Desired Reaction:     MPU Exc MIP (MYTPSW1 -> caused by Enhanced Isolation)       */
        /* The C logic is tested here: write on the stack by writing on a volatile local     */
        /* variable. This must be checked for each compiler update.                          */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 9, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            rbtpsw_CpuContext_t previous;

            TRUSTED_MoveSP(sp_before);

            previous = RBTPSW_Switch2PrivMode();
            RBTPSW_RestoreMode(previous);
            break;
        }

        case 47:
        /* Testcase description: RBTPSW_CALL to trusted function with broken SP              */
        /* Desired Reaction:     MYTPSW1 -> MPU Exc MIP (caused by Enhanced Isolation)       */
        /* The C logic is tested here: write on the stack by writing on a volatile local     */
        /* variable. This must be checked for each compiler update.                          */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TRUSTED_MoveSP(sp_before);
            RBTPSW_CALL(TRUSTED_1Param_V(1));
            break;
        }

        case 48:
        /* Testcase description: RBTPSW_CALL to trusted function with intlock */
        /* Desired Reaction:     MYTPSW1 -> SW_ABORTED, userinfo = 1          */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 1, 0, DEBUG_SW_ABORTED , RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_EnterCorelocalIntlock();
            RBTPSW_CALL(TRUSTED_1Param_V(1));
            break;
        }

        case 49:
        /* Testcase description: Call TPSW2 and break the SP (set SP to MYTPSW2 valid RAM area) */
        /* Desired Reaction:     MYTPSW2 -> MPU Exc MIP (caused by Enhanced Isolation)          */
        RBTPSW_SetExpectedResult(2, NOT_ACTIVE, 0x90, 9, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_CALL(TPSW2_BreakSpToValidRam());
            break;
        }

#if (RBFS_MCORE == RBFS_MCORE_ON)
        /* RBTPSW Lock code is currently only valid for multi core.
         * See code/comment at top of RBTPSW_EnterLock().
         */
        case 50:
        /* Testcase description:  Call TPSW_Switch2PrivMode with int locks                      */
        /* Desired Reaction:      MYTPSW1 -> SW_ABORTED, userinfo = 1.                          */
        /* In this test case, FUN_IsIntLockActive() detects the int lock. Abort through         */
        /*  TPSW_DummyTrusted.                                                                  */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 1, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_EnterLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
            (void)RBTPSW_Switch2PrivMode();
            break;
        }

        case 51:
        /* Test case description:  call MYTPSW2 and lock int                                    */
        /* Desired Reaction: MYTPSW2 -> SW_ABORTED, userinfo=1, MYTPSW1 active                  */
        /*                  TPSW1 checks if the PMR clean up is working correctly.              */
        /*                  TPSW1 aborts in case the PMR is != 0.                               */
        RBTPSW_SetExpectedResult(2, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 1, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        {
#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
            /* P1x: take PMR */
            #define RBTPSW_PMR_ID  11
            #define RBTPSW_SELID2   2
            #define RBTPSW_PMR_DEFAULT  0U      /* PMR default value on RH850, see RTAOS StartOS.c */
#elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
            /* U2A: take PLMR - interrupt priority masking register */
            #define RBTPSW_PMR_ID  14
            #define RBTPSW_SELID2   2
            #define RBTPSW_PMR_DEFAULT  16U     /* PLMR default value on RH850, see RTAOS StartOS.c */
#endif
            uint32 pmr;

            RBTPSW_CALL(TPSW2_Mytest_BadCaseUTUTwithIntLock());

            {
                OS_SET_TRUSTED_MODE();

                pmr = RBSYS_STSR(RBTPSW_PMR_ID, RBTPSW_SELID2);

                OS_SET_UNTRUSTED_MODE();
            }

            /* TPSW2_Mytest_BadCaseUTUTwithIntLock enters a common lock on core 0, no check for locks on core 1 is necessary */
            if((RBTPSW_AreCoreLockActive(0) != 0) || (pmr != RBTPSW_PMR_DEFAULT))
            {
                TrustedData++; // kill as we detected an error
            }
            break;
        }
#else
        case 50:
        case 51:
            RBTPSW_SetExpectedResultToNoReaction();
            break;
#endif


        case 52:
        /* Testcase description:  call MYTPSW2 with stack size=10000                              */
        /* Desired Reaction:      MYTPSW2 -> SW_ABORTED, userinfo=3 (detected in SetMemoryAccess) */
        /*                        RBTPSW_USERINFO_STACKOUTOFRANGE                                 */
        RBTPSW_SetExpectedResult(2, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 3, 0, DEBUG_SW_ABORTED , RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_CALL(TPSW2_FuncWithHugeStack());
            break;
        }


        case 53:
        /* Testcase description: Call TPSW2 and break the SP (SP is set after MYTPSW2 stack area)   */
        /* Desired Reaction:     MYTPSW2 -> MPU Exc MIP (caused by Enhanced Isolation);             */
        RBTPSW_SetExpectedResult(2, NOT_ACTIVE, 0x90, 9, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_CALL(TPSW2_BreakSpToInvalidRam());
            break;
        }


#if (RBFS_MCORE == RBFS_MCORE_ON)
        /* RBTPSW Lock code is currently only valid for multi core.
         * See code/comment at top of RBTPSW_EnterLock().
         */
        case 54:
        /* Testcase description: call RBTPSW_ExitLock() with broken SP                           */
        /* Desired Reaction:     MPU Exc MIP (MYTPSW1) caused by Enhanced Isolation              */
        /* The C logic is tested here: write on the stack by writing on a volatile local         */
        /* variable. This must be checked for each compiler update.                              */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_EnterLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
            TRUSTED_MoveSP(sp_before);
            RBTPSW_ExitLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
            break;
        }
#else
        case 54:
            RBTPSW_SetExpectedResultToNoReaction();
            break;
#endif


        case 55:
        /* Testcase description: call RBTPSW_ExitCorelocalIntlock() with broken SP           */
        /* Desired Reaction:     MPU Exc MIP (MYTPSW1) caused by Enhanced Isolation          */
        /* The C logic is tested here: write on the stack by writing on a volatile local     */
        /* variable. This must be checked for each compiler update.                          */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_EnterCorelocalIntlock();
            TRUSTED_MoveSP(sp_before);
            RBTPSW_ExitCorelocalIntlock();
            break;
        }


#if (RBFS_MCORE == RBFS_MCORE_ON)
        /* RBTPSW Lock code is currently only valid for multi core.
         * See code/comment at top of RBTPSW_EnterLock().
         */
        case 56:
        /* Testcase description: call RBTPSW_ExitLock only */
        /* Desired Reaction:     Sw aborted (MYTPSW1)      */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 1, 0, DEBUG_SW_ABORTED , RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_ExitLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
            break;
        }
#else
        case 56:
            RBTPSW_SetExpectedResultToNoReaction();
            break;
#endif


        case 57:
        /* Testcase description: call RBTPSW_ExitCorelocalIntlock only */
        /* Desired Reaction:     Sw aborted (MYTPSW1)                  */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 1, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_ExitCorelocalIntlock();
            break;
        }


        case 58:
        /* Testcase description: break the stack of RBTPSW_FnCall_Core_xxx()                    */
        /* Desired Reaction:    P1X: no reaction: all register used after CTF SetTrust()        */
        /*                          and before longjmp() must be ok.                            */
        /*                      U2A: MPU Exc (MYTPSW1) expected.                                */
        #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
            RBTPSW_SetExpectedResultToNoReaction();
        #else
            RBTPSW_SetExpectedResult(3, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        #endif
        {
            RBTPSW_CALL(TPSW3_BreakStack());
            break;
        }

        case 59:
        /* Testcase description:  test every function call and manipulator good cases.          */
        /* Desired Reaction: no reaction. TPSW1_ErrorCounter_UL and TPSW2_ErrorCounter_UL       */
        /*                   must always be equal to 0.                                         */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            TPSW1_TestGoodCases();

            if ((TPSW1_ErrorCounter_UL != 0) || (TPSW2_ErrorCounter_UL != 0))
            {
                // kill TPSW1
                TrustedData = 0;
            }
            break;
        }

        case 60:
        /* Testcase description: test of (GOOD CASE):                                               */
        /*                      RBTPSW_GetAppStatusByFunc(),                                        */
        /*                      RBTPSW_GetAppStatus(),                                              */
        /*                      RBTPSW_GetDebugInfo()                                               */
        /* Desired Reaction:     No reaction                                                        */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            TPSW1_Tpsw2StateByApp  = RBTPSW_GetAppStatus(MYTPSW2);
            TPSW1_Tpsw2StateByFunc = RBTPSW_GetAppStatusByFunc(TPSW2_1Param_V);
            TPSW1_Tpsw2DebugCore0  = RBTPSW_GetDebugInfo(MYTPSW2, OS_CORE_ID_0);
            TPSW1_Tpsw2DebugCore1  = RBTPSW_GetDebugInfo(MYTPSW2, OS_CORE_ID_1);
            break;
        }

        case 61:
        /* Testcase description: Test RBTPSW_IntLockChecks() function (called in untrusted mode)  */
        /* Desired Reaction:     TPSW1 killed                                                     */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 7, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            rbtpsw_fncall_context_t l_context = {0};
            (void)RBTPSW_IntLockChecks(&l_context, RBTPSW_GetCoreID_Prv(), RBTPSW_CPUMODE_TRUSTED);
            break;
        }
        case 62:
        /* Testcase description: Test RBTPSW_CallTrustedFunction() function (called in untrusted mode) */
        /* Desired Reaction:     TPSW1 killed                                                          */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 7, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            rbtpsw_fncall_context_t l_context;
            RBTPSW_CallTrustedFunction(RBTPSW_GetCoreID_Prv(), &l_context, 0);
            break;
        }
        case 63:
            RBTPSW_SetExpectedResultToNoReaction();
            break;

        case 64:
        /* Testcase description: Global Pointer (r4) overwritten                                    */
        /* Desired Reaction:     no reaction                                                        */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            RBTPSW_CALL(TPSW3_OverwriteGp());
            break;
        }

        case 65:
        /* Testcase description: Text Pointer (r5) overwritten                                      */
        /* Desired Reaction:     no reaction                                                        */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            RBTPSW_CALL(TPSW3_OverwriteTp());
            break;
        }

        case 66:
        /* Testcase description: break Element Pointer (r30)                                        */
        /* Desired Reaction:     no reaction, as it will loaded each time that it is needed         */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            RBTPSW_CALL(TPSW3_OverwriteEp());
            break;
        }

        case 67:
        /* Testcase description: lp = 0x80000000 (unimplemented H-Bus)  */
        /* Desired Reaction:     MPU Exc (TPSW3 killed)                 */
        /*                       No SYSERR Exc                          */
        /*                       No FEINT Exc                           */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            // TODO: to be fixed, SYSERR is generated
            // uint16 PreviousSEGCONT;
            // rbtpsw_CpuContext_t previous;

            // Activate SYSERR exception.
            // It should be never fired in case a tpsw does something wrong.
            // previous = RBTPSW_Switch2PrivMode();
            // {
                // PreviousSEGCONT = SEGCONT;
                // SEGCONT = 0x0010;
            // }
            // RBTPSW_RestoreMode(previous);

            // RBTPSW_CALL(TPSW3_OverwriteLp());

            // previous = RBTPSW_Switch2PrivMode();
            // {
                // SEGCONT = PreviousSEGCONT;
            // }
            // RBTPSW_RestoreMode(previous);
            break;
        }


        case 68:
        /* Testcase description: exit of TPSW untrusted function with int lock.              */
        /* Desired Reaction:     MYTPSW1 -> SW_ABORTED, userinfo = 1                         */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 1, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_EnterCorelocalIntlock();
            break;
        }


#if (RBFS_MCORE == RBFS_MCORE_ON)
        /* RBTPSW Lock code is currently only valid for multi core.
         * See code/comment at top of RBTPSW_EnterLock().
         */
        case 69:
        /* Testcase description: exit of TPSW untrusted function with common lock            */
        /* Desired Reaction:    MYTPSW1 -> SW_ABORTED, userinfo = 1.                         */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 1, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_ExitLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
            break;
        }
#else
        case 69:
            RBTPSW_SetExpectedResultToNoReaction();
            break;
#endif

        case 70:
        /* Testcase description: Exit of TPSW untrusted function with switch2privmode only.          */
        /*                       This tests the case where RestoreMode() is forgotten --> dev error. */
        /* Desired Reaction:     MPU Exc (MYTPSW1)                                                   */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            (void)RBTPSW_Switch2PrivMode();
            break;
        }


        case 71:
        /* Testcase description:  Call RBTPSW_Switch2PrivMode with RBTPSW_AreCoreLockActive()       */
        /*                          --> int lock                                                    */
        /* Desired Reaction:      MYTPSW1 -> SW_ABORTED, userinfo = 1.                              */
        /* In this test case, FUN_IsIntLockActive() detects the int lock. Abort through             */
        /* TPSW_DummyTrusted.                                                                       */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 1, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_EnterCorelocalIntlock();
            (void)RBTPSW_Switch2PrivMode();
            break;
        }


#if (RBFS_MCORE == RBFS_MCORE_ON)
         /* RBTPSW Lock code is currently only valid for multi core.
         * See code/comment at top of RBTPSW_EnterLock().
         */
        case 72:
        /* Testcase description:  Call RBTPSW_ExitLock with common lock - good test case            */
        /* Desired Reaction:      No reaction                                                */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            CoreIdType Core = TRUSTED_GetCoreId();

            RBTPSW_EnterLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
            {
              #if(RBFS_MCORE == RBFS_MCORE_ON)
                if (RBSYS_getLockNestCnt_perCore(RBTPSW_LOCKCONFIG_COMMONLOCK, Core) == 0)
              #else
                if (RBSYS_getIntlockNestCnt(Core) == 0)
              #endif
                {
                    // kill TPSW1 if lock was not taken
                    TrustedData = 0;
                }
            }
            RBTPSW_ExitLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
            break;
        }
#else
        case 72:
            RBTPSW_SetExpectedResultToNoReaction();
            break;
#endif


        case 73:
        /* Testcase description: call RBTPSW_ExitCorelocalIntlock() with broken SP in */
        /*                       valid TPSW1 RAM.                                     */
        /* Desired Reaction:     MPU Exc MIP (MYTPSW1) caused by Enhanced Isolation   */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 9, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_EnterCorelocalIntlock();
            TRUSTED_MoveSP((void*)&TPSW1_DataTable[TPSW1_DATATABLESIZE/2]);
            RBTPSW_ExitCorelocalIntlock();
            break;
        }


        case 74:
        /* Testcase description: call RBTPSW_Switch2PrivMode() with broken SP in       */
        /*                       valid TPSW1 RAM.                                      */
        /* Desired Reaction:     MPU Exc MIP (MYTPSW1 -> caused by Enhanced Isolation) */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 9, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            rbtpsw_CpuContext_t previous;
            TRUSTED_MoveSP((void*)&TPSW1_DataTable[TPSW1_DATATABLESIZE/2]);
            previous = RBTPSW_Switch2PrivMode();
            RBTPSW_RestoreMode(previous);
            break;
        }


        case 75:
        /* Testcase description: call RBTPSW_EnterCorelocalIntlock() with broken SP in   */
        /*                       valid TPSW1 RAM.                                        */
        /* Desired Reaction:     MPU Exc MIP (MYTPSW1) caused by Enhanced Isolation      */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 9, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TRUSTED_MoveSP((void*)&TPSW1_DataTable[TPSW1_DATATABLESIZE/2]);
            RBTPSW_EnterCorelocalIntlock();
            RBTPSW_ExitCorelocalIntlock();
            break;
        }


#if (RBFS_MCORE == RBFS_MCORE_ON)
        /* RBTPSW Lock code is currently only valid for multi core.
         * See code/comment at top of RBTPSW_EnterLock().
         */
        case 76:
        /* Testcase description:  Call lock which is not allowed                              */
        /* Desired Reaction:      TPSW1 aborted with userinfo = 4 (RBTPSW_USERINFO_WRONGLOCK) */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 4, 0, DEBUG_SW_ABORTED , RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_EnterLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
            RBTPSW_ExitLock(ANY_LOCK);
            break;
        }

        case 77:
        /* Testcase description:  Call lock which is not allowed                              */
        /* Desired Reaction:      TPSW1 aborted with userinfo = 4 (RBTPSW_USERINFO_WRONGLOCK) */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 4, 0, DEBUG_SW_ABORTED , RBTPSW_TestExecutionProcCore);
        {
            lockstr_t x = {0};
            RBTPSW_EnterLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
            RBTPSW_ExitLock(&x);
            break;
        }

        case 78:
        /* Testcase description: call RBTPSW_ExitLock() with broken SP in           */
        /*                       valid TPSW1 RAM.                                   */
        /* Desired Reaction:     MPU Exc MIP (MYTPSW1) caused by Enhanced Isolation */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 9, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_EnterLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
            TRUSTED_MoveSP((void*)&TPSW1_DataTable[TPSW1_DATATABLESIZE/2]);
            RBTPSW_ExitLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
            break;
        }

        case 79:
        /* Testcase description: call RBTPSW_EnterLock() with broken SP in           */
        /*                       valid TPSW1 RAM.                                    */
        /* Desired Reaction:     MPU Exc MIP (MYTPSW1) caused by Enhanced Isolation  */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 9, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TRUSTED_MoveSP((void*)&TPSW1_DataTable[TPSW1_DATATABLESIZE/2]);
            RBTPSW_EnterLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
            RBTPSW_ExitLock(RBTPSW_LOCKCONFIG_COMMONLOCK);
            break;
        }
#else
        case 76:
        case 77:
        case 78:
        case 79:
            RBTPSW_SetExpectedResultToNoReaction();
            break;
#endif

        case 80:
        /* Testcase description: generate a division by 0 error in user mode. */
        /* Desired Reaction:     No reaction.                                 */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            TPSW1_Result_u32 = TPSW1_Value_u32/TPSW1_Zero_u32;
            break;
        }

        case 81:
        /* Testcase description: generate a division by zero floating point error in user mode. */
        /* Desired Reaction:     MPU Exc (MYTPSW1)                                              */
        /* A FPP exception is generated. It locks the flash execution for user                  */
        /* mode and returns --> cascading abort                                                 */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_Result_f = TPSW1_Value_f/TPSW1_Zero_f;
            break;
        }

         case 82:
        /* Testcase description:  SP is within the range. UT-UT call.                        */
        /* Desired Reaction:     MYTPSW1 -> MPU Exc MIP (caused by Enhanced Isolation)       */
        /* In this test case, the Enhanced Isolation stack check is tested when switching to */
        /* trusted mode at the beginning of RBTPSW_CALL().                                   */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 9, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TRUSTED_MoveSP((void*)&TPSW1_DataTable[TPSW1_DATATABLESIZE/2]);
            RBTPSW_CALL(TPSW2_1Param_V (1));
            break;
        }

        case 83:
        /* Testcase description: SP is within the range. UT-T call.                          */
        /* Desired Reaction:     MYTPSW1 -> MPU Exc MIP (caused by Enhanced Isolation)       */
        /* In this test case, the Enhanced Isolation stack check is tested when switching to */
        /* trusted mode at the beginning of RBTPSW_CALL().                                   */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 9, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TRUSTED_MoveSP((void*)&TPSW1_DataTable[TPSW1_DATATABLESIZE/2]);
            RBTPSW_CALL(TRUSTED_1Param_V(1));
            break;
        }

        case 84:
        /* Testcase description: To check the stack size within the range.                       */
        /* Desired Reaction:     Good Test case - Application will be Active                     */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            RBTPSW_CALL(TPSW3_StackSizeCheck());
            break;
        }


        case 85:
        /* Testcase description:  Used another lock than common lock.                         */
        /*                        Not allowed because we don't support nonest locks!          */
        /* Desired Reaction:      TPSW1 killed                                                */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 4, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_EnterLock(ANY_LOCK_2);
            break;
        }


        case 86:
        /* Testcase description:  Execute code in GRAM during user mode (UM: GRAM non-executable). */
        /* Desired reaction:      MPU exc (TPSW1 killed). */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            int res;
            /* Execute sum_in_ram() in RAM */
            res = sum_in_ram((int)TestId, 37);
            break;
        }

        case 87:
        RBTPSW_SetExpectedResultToNoReaction();
        break;

        case 88:
        /* Testcase description:  Try to execute an undefined instruction in GRAM in user mode. */
        /* Desired reaction:      MPU exc (TPSW1 killed).    */
        /* Execute RIE */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_ReservedInstructionFunc_in_GRAM();
            break;
        }

        case 89:
        /* Testcase description: generate an invalid operation floating point error in user mode. */
        /* Desired Reaction:     MPU Exc (MYTPSW1)                                                */
        /* A FPP exception is generated. It locks the flash execution for user                    */
        /* mode and returns --> cascading abort                                                   */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_Result_f = TPSW1_Inf_f * TPSW1_Zero_f;
            break;
        }

        case 90:
        /* Testcase description:  Read flash at any location in bank 1, if enabled                  */
        /* Desired Reaction:      MPU exc (TPSW1) if bank 1 inactive, no reaction otherwise         */
        #if (RBFS_FlashBank1Support == RBFS_FlashBank1Support_INACTIVE)
            RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        #else
            RBTPSW_SetExpectedResultToNoReaction();
        #endif
        {
            #if (RBFS_FlashBank1Support == RBFS_FlashBank1Support_ON)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_ActiveBank1();
                TPSW1_Global_u32 = *ptr;
            #elif (RBFS_FlashBank1Support == RBFS_FlashBank1Support_INACTIVE)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_InactiveBank1();
                TPSW1_Global_u32 = *ptr;
            #endif
            break;
        }

        case 91:
        /* Testcase description:  Write flash at any location in bank 1                             */
        /* Desired Reaction:      MPU Exc MDP (TPSW1)                                               */
        #if (RBFS_FlashBank1Support == RBFS_FlashBank1Support_ON || RBFS_FlashBank1Support == RBFS_FlashBank1Support_INACTIVE)
            RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        #else
            RBTPSW_SetExpectedResultToNoReaction();
        #endif
        {
            #if (RBFS_FlashBank1Support == RBFS_FlashBank1Support_ON)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_ActiveBank1();
                *ptr = 1;
            #elif (RBFS_FlashBank1Support == RBFS_FlashBank1Support_INACTIVE)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_InactiveBank1();
                *ptr = 1;
            #endif
            break;
        }

        case 92:
        /* Testcase description:  Read flash at any location in bank 2, if enabled                  */
        /* Desired Reaction:      MPU exc (TPSW1) if bank 2 inactive, no reaction otherwise         */
        #if (RBFS_FlashBank2Support == RBFS_FlashBank2Support_INACTIVE)
            RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        #else
            RBTPSW_SetExpectedResultToNoReaction();
        #endif
        {
            #if (RBFS_FlashBank2Support == RBFS_FlashBank2Support_ON)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_ActiveBank2();
                TPSW1_Global_u32 = *ptr;
            #elif (RBFS_FlashBank2Support == RBFS_FlashBank2Support_INACTIVE)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_InactiveBank2();
                TPSW1_Global_u32 = *ptr;
            #endif
            break;
        }

        case 93:
        /* Testcase description:  Write flash at any location in bank 2                             */
        /* Desired Reaction:      MPU Exc MDP (TPSW1)                                              */
        #if (RBFS_FlashBank2Support == RBFS_FlashBank2Support_ON) || (RBFS_FlashBank2Support == RBFS_FlashBank2Support_INACTIVE)
            RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        #else
            RBTPSW_SetExpectedResultToNoReaction();
        #endif
        {
            #if (RBFS_FlashBank2Support == RBFS_FlashBank2Support_ON)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_ActiveBank2();
                *ptr = 1;
            #elif (RBFS_FlashBank2Support == RBFS_FlashBank2Support_INACTIVE)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_InactiveBank2();
                *ptr = 1;
            #endif
            break;
        }

        case 94:
        /* Testcase description:  Read flash at any location in bank 3, if enabled                  */
        /* Desired Reaction:      MPU exc (TPSW1) if bank 3 inactive, no reaction otherwise         */
        #if (RBFS_FlashBank3Support == RBFS_FlashBank3Support_INACTIVE)
            RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        #else
            RBTPSW_SetExpectedResultToNoReaction();
        #endif
        {
            #if (RBFS_FlashBank3Support == RBFS_FlashBank3Support_ON)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_ActiveBank3();
                TPSW1_Global_u32 = *ptr;
            #elif (RBFS_FlashBank3Support == RBFS_FlashBank3Support_INACTIVE)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_InactiveBank3();
                TPSW1_Global_u32 = *ptr;
            #endif
            break;
        }

        case 95:
        /* Testcase description:  Write flash at any location in bank 3                             */
        /* Desired Reaction:      MPU Exc MDP (TPSW1)                                               */
        #if (RBFS_FlashBank3Support == RBFS_FlashBank3Support_ON) || (RBFS_FlashBank3Support == RBFS_FlashBank3Support_INACTIVE)
            RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        #else
            RBTPSW_SetExpectedResultToNoReaction();
        #endif
        {
            #if (RBFS_FlashBank3Support == RBFS_FlashBank3Support_ON)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_ActiveBank3();
                *ptr = 1;
            #elif (RBFS_FlashBank3Support == RBFS_FlashBank3Support_INACTIVE)
                volatile uint32* ptr = (volatile uint32*)RBLCF_getStartAddress_PFLASH_InactiveBank3();
                *ptr = 1;
            #endif
            break;
        }

        case 96:
        /* Testcase description: generate an invalid operation floating point error in user mode. */
        /* Desired Reaction:     MPU Exc (MYTPSW1)                                                */
        /* A FPP exception is generated. It locks the flash execution for user                    */
        /* mode and returns --> cascading abort                                                   */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_SNaN_f = *((float*)&TPSW1_SNaN_u32);
            TPSW1_Result_f = TPSW1_SNaN_f * TPSW1_Value_f;
            break;
        }
        case 97:
        /* Testcase description: generate an invalid operation floating point error in user mode. */
        /* Desired Reaction:     MPU Exc (MYTPSW1)                                                */
        /* A FPP exception is generated. It locks the flash execution for user                    */
        /* mode and returns --> cascading abort                                                   */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_Result_f = TPSW1_Inf_f - TPSW1_Inf_f;
            break;
        }
        case 98:
        /* Testcase description: generate an invalid operation floating point error in user mode. */
        /* Desired Reaction:     MPU Exc (MYTPSW1)                                                */
        /* A FPP exception is generated. It locks the flash execution for user                    */
        /* mode and returns --> cascading abort                                                   */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_Value_f = 3e38f; //Too big for integer
            TPSW1_Result_u32 = (uint32)TPSW1_Value_f;
            break;
        }

        case 99:
        /* Testcase description: generate a division by zero floating point error in user mode with doubles. */
        /* Desired Reaction:     MPU Exc (MYTPSW1)                                                           */
        /* A FPP exception is generated. It locks the flash execution for user                               */
        /* mode and returns --> cascading abort                                                              */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_Result_d = TPSW1_Value_d/TPSW1_Zero_d;
            break;
        }

        case 100:
        /* Testcase description: generate an invalid operation floating point error in user mode with doubles. */
        /* Desired Reaction:     MPU Exc (MYTPSW1)                                                             */
        /* A FPP exception is generated. It locks the flash execution for user                                 */
        /* mode and returns --> cascading abort                                                                */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_Result_d = TPSW1_Inf_d * TPSW1_Zero_d;
            break;
        }

        case 101:
        /* Testcase description: generate an invalid operation floating point error in user mode with doubles. */
        /* Desired Reaction:     MPU Exc (MYTPSW1)                                                             */
        /* A FPP exception is generated. It locks the flash execution for user                                 */
        /* mode and returns --> cascading abort                                                                */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_SNaN_d = *((double*)&TPSW1_SNaN_u64);
            TPSW1_Result_d = TPSW1_SNaN_d * TPSW1_Value_d;
            break;
        }

        case 102:
        /* Testcase description: generate an invalid operation floating point error in user mode with doubles. */
        /* Desired Reaction:     MPU Exc (MYTPSW1)                                                             */
        /* A FPP exception is generated. It locks the flash execution for user                                 */
        /* mode and returns --> cascading abort                                                                */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_Result_d = TPSW1_Inf_d - TPSW1_Inf_d;
            break;
        }

        case 103:
        /* Testcase description: generate an invalid operation floating point error in user mode with doubles. */
        /* Desired Reaction:     MPU Exc (MYTPSW1)                                                             */
        /* A FPP exception is generated. It locks the flash execution for user                                 */
        /* mode and returns --> cascading abort                                                                */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0x90, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_Value_d = 3e38f; //Too big for integer
            TPSW1_Result_u32 = (uint32)TPSW1_Value_d;
            break;
        }

        case 104:
        /* Testcase description: Read restricted system register in user mode                                  */
        /* Desired Reaction:     PIE Exc (MYTPSW1)                                                             */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0xA0, 0, 18, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_Value_u32 = RBSYS_STSR(6, 1); //Try to read processor id
            break;
        }

        case 105:
        /* Testcase description: Write restricted system register in user mode                                 */
        /* Desired Reaction:     PIE Exc (MYTPSW1)                                                             */
        RBTPSW_SetExpectedResult(1, NOT_ACTIVE, 0xA0, 0, 18, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_Value_u32 = 0xfffff000; //Invalid address for interrupt handler table
            RBSYS_LDSR(4, 1, TPSW1_Value_u32);
            break;
        }

#if (RBFS_TPSWCapsule == RBFS_TPSWCapsule_SC4)
/*****************************************************************************************************
******************************************************************************************************
******** TIMING PROTECTION TEST CASES                                               ******************
******** TPSW1_FIRST_TIMING_TC must be the id of the last mpu test case + 1         ******************
******************************************************************************************************
*****************************************************************************************************/
        case TPSW1_FIRST_TIMING_TC + 0:
        /* Testcase description: Good cases for: (test running on core0 and core1)                  */
        /*                        - UT(notp) --> UT(tp) with 0us runtime                            */
        /*                        - UT(notp) --> UT(tp) with limit-25us runtime                     */
        /* Desired Reaction: no reaction                                                            */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            TPSW1_TestCaseIdMultiCore = TestId;

            (void)RBTPSW_CALL(TPSW3_WaitingFunction(0));
            (void)RBTPSW_CALL(TPSW3_WaitingFunction(TPSW3_WAITINGFUNCTION_TIMELIMIT - 25));

            {
                TPSW3_WaitingFunction_Switch2Trust_t mytime;

                mytime.untrustedTimeBefore = 50;
                mytime.trustedTime = 0;
                mytime.untrustedTimeAfter = 50;

                (void)RBTPSW_CALL(TPSW3_WaitingFunction_UTnoTP(&mytime));

                if(TPSW3_WaitingFunction_UTnoTP_State != 5) {TrustedData = 0;}
            }
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 1:
        /* Testcase description: UT(notp) --> UT(tp) bad case, budget expires.                        */
        /* Desired Reaction: TPSW3 Killed (tp)                                                        */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            (void)RBTPSW_CALL(TPSW3_WaitingFunction(TPSW3_WAITINGFUNCTION_TIMELIMIT + 1));
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 2:
        /* Testcase description: Good case: UT(notp) calls UT(tp) with use of                         */
        /*                        switch2priv() / restore()                                           */
        /* Desired Reaction: no reaction                                                              */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            TPSW1_TPSW3_WaitingFunction_Switch2Trust_GC();
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 3:
        /* Testcase description: Bad case: UT(notp) calls UT(tp) with use of switch2priv() /          */
        /*                            restore(). Timing budget expires before switch2priv() call.     */
        /* Desired Reaction: TPSW3 Killed (tp), TPSW1 Active                                          */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_TPSW3_WaitingFunction_Switch2Trust_BC1();
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 4:
        /* Testcase description: Bad case: UT(notp) calls UT(tp) with use of switch2priv() /            */
        /*                        restore(). Timing budget expires during switch2priv() / restore().    */
        /* Desired Reaction: TPSW3 Killed (tp), TPSW1 Active                                            */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_TPSW3_WaitingFunction_Switch2Trust_BC2();
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 5:
        /* Testcase description: Bad case: UT(notp) calls UT(tp) with use of switch2priv() /            */
        /*                        restore(). Timing budget expires after restore() call.                */
        /* Desired Reaction: TPSW3 Killed (tp), TPSW1 Active                                            */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_TPSW3_WaitingFunction_Switch2Trust_BC3();
            break;
        }

#if (RBFS_MCORE == RBFS_MCORE_ON)
        case TPSW1_FIRST_TIMING_TC + 6:
        /* Testcase description: same than TPSW1_FIRST_TIMING_TC + 1 on core 1                         */
        /* Desired Reaction:                                                                           */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_MultiProcCore);
        {
            TPSW1_TestCaseIdMultiCore = TestId;
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 7:
        /* Testcase description: same than TPSW1_FIRST_TIMING_TC + 3 on core 1                         */
        /* Desired Reaction:                                                                           */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_MultiProcCore);
        {
            TPSW1_TestCaseIdMultiCore = TestId;
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 8:
        /* Testcase description: same than TPSW1_FIRST_TIMING_TC + 4 on core 1                         */
        /* Desired Reaction:                                                                           */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_MultiProcCore);
        {
            TPSW1_TestCaseIdMultiCore = TestId;
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 9:
        /* Testcase description: same than TPSW1_FIRST_TIMING_TC + 5 on core 1                         */
        /* Desired Reaction:                                                                           */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_MultiProcCore);
        {
            TPSW1_TestCaseIdMultiCore = TestId;
            break;
        }
#else
        case TPSW1_FIRST_TIMING_TC + 6:
        case TPSW1_FIRST_TIMING_TC + 7:
        case TPSW1_FIRST_TIMING_TC + 8:
        case TPSW1_FIRST_TIMING_TC + 9:
            RBTPSW_SetExpectedResultToNoReaction();
            break;
#endif

        case TPSW1_FIRST_TIMING_TC + 10:
        /* Testcase description: call TPSW2 (timing protected) --> call TPSW3 (no tp), time           */
        /*                        expires and then mpu exc occur.                                     */
        /* Desired Reaction:     TPSW2 timing abort, TPSW3 exc abort                                  */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        RBTPSW_SetExpectedResult(2, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            (void)RBTPSW_CALL(TPSW2_TimingAndMpuAbort(TPSW2_TIMINGANDMPUABORT_TIMELIMIT + 50));
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 11:
        /* Testcase description: call TPSW2 (timing protected) --> call TPSW3 (timing protected),      */
        /*                        mpu exc occur.                                                       */
        /* Desired Reaction:     TPSW2 no reaction, TPSW3 exc abort                                    */
        // Hint: TPSW2 remaining time doesn't take the runtime of killed TPSW3 in account. See RB_A227.
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, 0x91, 0, 14, DEBUG_EXC_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            (void)RBTPSW_CALL(TPSW2_TimingAndMpuAbort_Tp(0));
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 12:
        /* Testcase description: checks the error counter of the background test cases.                */
        /* Desired Reaction:     no reaction                                                           */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            if(RBTPSW_BackgroundTestApp_WaitingFunction_ErrorCounter != 0)
            {
                TrustedData++;
            }
            break;
        }

        /* Scenario: TPSW1 (NoTp) --> TPSW3(TP) ---> TPSW2(TP) ---> TPSW3(TP) ---> TPSW1 (NoTp)
           TC:13-16                   _/ Kill: T3    _/ Kill: T3+T2  _/ Kill: T3     _/ Good Case
                                      State= 0      State = 2       State=4            State = 5  */

        case TPSW1_FIRST_TIMING_TC + 13:
        /* Testcase description:                                                                      */
        /* Desired Reaction:     Good case no reaction                                                */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            TPSW1_TPSW3_WaitingFunction_TPSW2CALL_GoodCase_Tp();
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 14:
        /* Testcase description:                                                                      */
        /* Desired Reaction:     TPSW3 killed                                                         */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase1_Tp();
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 15:
        /* Testcase description:                                                                      */
        /* Desired Reaction:     TPSW3/TPSW2 (Timing Abort) killed                                    */
        RBTPSW_SetExpectedResult(2, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase2_Tp();
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 16:
        /* Testcase description:                                                                      */
        /* Desired Reaction:     TPSW3 killed                                                         */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase3_Tp();
            break;
        }

        /* Scenario: TPSW1 (NoTp) --> TPSW3(TP) ---> TPSW2(NoTP) ---> TPSW3(TP) ---> TPSW1 (NoTp)
          TC:17-20                      _/ Kill: T3    _/ Kill: T3   _/ Kill: T3     _/ Good Case
                                      State= 0      State = 2       State=4            State = 5  */

        case TPSW1_FIRST_TIMING_TC + 17:
        /* Testcase description:                                                                      */
        /* Desired Reaction:     Good case no reaction                                                */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            TPSW1_TPSW3_WaitingFunction_TPSW2CALL_GoodCase_NoTp();
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 18:
        /* Testcase description:                                                                      */
        /* Desired Reaction:     TPSW3 killed                                                         */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase1_NoTp();
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 19:
        /* Testcase description:                                                                      */
        /* Desired Reaction:     TPSW3 killed                                                         */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase2_NoTp();
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 20:
        /* Testcase description:                                                                      */
        /* Desired Reaction:     TPSW3 killed                                                         */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_TPSW3_WaitingFunction_TPSW2CALL_BadCase3_NoTp();
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 21:
        /* Testcase description: checks the error counter of the suppression flag background          */
        /*                        test cases.                                                         */
        /* Desired Reaction:     No reaction                                                          */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            if(MYTPSW_SupprFlagErrorCounter != 0)
            {
                TrustedData++;
            }
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 22:
        /* Testcase description: UT => UT(tp) => T                                                    */
        /*                         UT(notp) --> UT(tp) bad case, budget expires.                      */
        /*  Desired Reaction: Good Test case - No Reaction                                            */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            TPSW1_TPSW3_UTTP_GoodCase();
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 23:
        /* Testcase description: UT => UT(tp) => T: timing violation before T.                        */
        /*                        UT(notp) --> UT(tp) bad case                                        */
        /*   Desired Reaction: TPSW3 Killed (tp)                                                      */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_TPSW3_UTTP_BadCase1();
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 24:
        /* Testcase description: UT => UT(tp) => T: timing violation during T.                        */
        /*                        UT(notp) --> UT(tp) bad case                                        */
        /* Desired Reaction: TPSW3 Killed (tp)                                                        */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_TPSW3_UTTP_BadCase2();
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 25:
        /* Testcase description: UT => UT(tp) => T: timing violation after T.                        */
        /*                       UT(notp) --> UT(tp) bad case                                        */
        /* Desired Reaction: TPSW3 Killed (tp)                                                       */
        RBTPSW_SetExpectedResult(3, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            TPSW1_TPSW3_UTTP_BadCase3();
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 26:
        /* Testcase description: Mpu exception just before a timing exception                        */
        /*                          Mpu exc, TPSW2 killed.                                           */
        /* Desired Reaction:     TPSW2 Killed                                                        */
        // TODO: Understand expected reaction of the test case and rework accordingly. Right now it
        // cannot catch both MPU exc and timing exc, as TPSW2 is set to NOT_ACTIVE after MPU exc
        RBTPSW_SetExpectedResultToNoReaction();
        {
            //RBTPSW_CALL(TPSW1_TPSW2_Before_Timing_Exc(0));
            break;
        }

        case TPSW1_FIRST_TIMING_TC + 27:
        /* Testcase description: Manual test case:                                                   */
        /*                       Check that a preemption over the timing protected function          */
        /*                       RBTPSW_MyTPSWCapsule_PreemptedWaitingAndReset_Proc() has no effect. */
        /* Desired Reaction:     No reaction                                                         */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            break;
        }


        case TPSW1_FIRST_TIMING_TC + 28:
        /* Testcase description: Call timing protected function. Timing violation during int lock.   */
        /* Desired Reaction:     TPSW2 Killed by timing isr.                                         */
        RBTPSW_SetExpectedResult(2, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 0, 15, DEBUG_TIMING_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_CALL(TPSW2_MpuExc_Lock(50));
            break;
        }


        case TPSW1_FIRST_TIMING_TC + 29:
        /* Testcase description: A time-protected function calls a non-time-protected function which */
        /*                       attempts to enter lock                                              */
        /* Desired Reaction:     No reaction, as calling an unprotected function supresses the timer */
        RBTPSW_SetExpectedResultToNoReaction();
        {
            RBTPSW_CALL(TPSW2_TPNoTP_LockTest());
            break;
        }


        case TPSW1_FIRST_TIMING_TC + 30:
        /* Testcase description: A time-protected function attempts to enter lock                    */
        /* Desired Reaction:     TPSW2 aborted with userinfo = 6 (RBTPSW_USERINFO_LOCK_WITH_TP)      */
        RBTPSW_SetExpectedResult(2, NOT_ACTIVE, RBTPSW_EXPECTEDRESULT_DONTCARE, 6, 0, DEBUG_SW_ABORTED, RBTPSW_TestExecutionProcCore);
        {
            RBTPSW_CALL(TPSW2_TP_LockTest());
            break;
        }


#endif
        default:
        {
            rbtpsw_CpuContext_t previous;

            RBTPSW_SetExpectedResultToNoReaction();

            /* Reset TPSW2_TestCaseId to start value. TRUSTED mode required */
            previous = RBTPSW_Switch2PrivMode();
            TPSW2_TestCaseId = 0;
            TPSW2_TestSuiteExecutionCount++;
            RBTPSW_RestoreMode(previous);
            break;
        }
    }

    MYTPSW_CHECK_SF(TRUE);

    /* This will stop both active waiting loops. If this point is not
     * reached (because of a bad case test), the cascading abort and
     * cross core kill mechanism will do the job. */
    TPSW1_ActiveWaiting = false;
}

#endif

/** @} */
/* End ingroup 'SW-group' */
