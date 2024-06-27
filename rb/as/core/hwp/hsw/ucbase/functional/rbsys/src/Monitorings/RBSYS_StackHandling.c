/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Stack handling
 *
 * Handling stack allocation of FSW (functional software). Bootblock stack will
 * be handled separate. Stack size must be a part of project specific configuration.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_ErrorHooks.h"
#include "RBLCF_MemoryRemap.h"
#include "rba_MultiStackTrace.h"
#include "RBSYS_CpuInfo.h"


/* realized interfaces */
#include "RBSYS_StackHandling.h"
#include "RBSYS_StackMon_Cfg.h"
#include "RBSYS_Subsystem.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);



RBSECTION_START_STACK_CPU0_NOCLEAR
volatile unsigned int RB_Stack0_FSW[RB_STACK0_ARRAYSIZE];      // stack for core 0
/*[[MEASUREMENT*/
/*NAME=RB_Stack0_FSW[RB_STACK_LOWCHK0]*/
/*COMMENT=Stack0: Last check word at stack end required for test automation*/
/*MTEVENT=c_MT_Default_Task_x1*/
/*]]MEASUREMENT*/
RBSECTION_END_STACK_CPU0_NOCLEAR

/* place pointer in .text to have it before c-init is done */
RBSECTION_START_SECTTYPE_NO_SDA
volatile unsigned int* const RB_SP0_FSW = &RB_Stack0_FSW[RB_STACK0_INITSP];
RBSECTION_END_SECTTYPE_NO_SDA


#if(RBFS_MCORE == RBFS_MCORE_ON)

  RBSECTION_START_STACK_CPU1_NOCLEAR
  volatile unsigned int RB_Stack1_FSW[RB_STACK1_ARRAYSIZE];    // stack for core 1
  /*[[MEASUREMENT*/
  /*NAME=RB_Stack1_FSW[RB_STACK_LOWCHK0]*/
  /*COMMENT=Stack1: Last check word at stack end required for test automation*/
  /*MTEVENT=c_MT_Default_Task_x1*/
  /*]]MEASUREMENT*/
  RBSECTION_END_STACK_CPU1_NOCLEAR

  RBSECTION_START_SECTTYPE_NO_SDA
  volatile unsigned int* const RB_SP1_FSW = &RB_Stack1_FSW[RB_STACK1_INITSP];
  RBSECTION_END_SECTTYPE_NO_SDA

#else  // set stackpointer 1 to be FS independent in .850 CPUInit file

  RBSECTION_START_SECTTYPE_NO_SDA
  volatile unsigned int* const RB_SP1_FSW = &RB_Stack0_FSW[RB_STACK0_INITSP];
  RBSECTION_END_SECTTYPE_NO_SDA

#endif



void RBSYS_PRC_StackCheckInit(void)
{
  (void)rba_MultiStackTrace_InitCoreLocalStacks();

  if (RBSYS_getCoreID() == RBSYS_CORE_ID_0){
    /* Principle stack is ok after initial setup of stack monitor by definition */
    RBSYS_setGoodCheckRequest(DemConf_DemEventParameter_RBSYS_StackOverUnderFlow);
  }
}


/* freespace is measured in bytes */
static uint32 RBSYS_Stack0_freespace;
/*[[MEASUREMENT*/
/*NAME=RBSYS_Stack0_freespace*/
/*COMMENT=RBSYS_Stack0_freespace*/
/*MTEVENT=c_MT_Default_Task_x4*/
/*]]MEASUREMENT*/

#if(RBFS_MCORE == RBFS_MCORE_ON)
  static uint32 RBSYS_Stack1_freespace;
  /*[[MEASUREMENT*/
  /*NAME=RBSYS_Stack1_freespace*/
  /*COMMENT=RBSYS_Stack1_freespace*/
  /*MTEVENT=c_MT_Default_Task_x4*/
  /*]]MEASUREMENT*/
#endif


typedef enum
{
  RBSYS_stack0check0 = 0,
  RBSYS_stack0check1,
  RBSYS_stack0check2,
  RBSYS_stack1check0,
  RBSYS_stack1check1,
  RBSYS_stack1check2
}RBSYS_StackFaultBitMask_t;



/* measured stack size has to be reduced by reserved space at the end (RB_STACK_LOWCHK1)
  plus two stack checkwords, each consisting of two 32 bit values; the third checkword is
  considered in RB_STACK_LOWCHK1 */
#define STACK_LIMITRED_BYTES  ((RB_STACK_LOWCHK1+(2*2))*4)

void RBSYS_PRC_StackCheck(void)
{
  rba_MultiStackTrace_StackMeas_t result = {
    UINT32_MAX, //< FreeSpace
    0u          //< CheckWordReached
  };

  uint32 stackfault = 0;
  uint32 freestack_dbg = 0xFFFFFFFFu;

  // called a few times (i.e. 1 word checked per call) until the stack size is set properly, so fasten freespace detection
  (void)rba_MultiStackTrace_ScanAllStacks();
  (void)rba_MultiStackTrace_ScanAllStacks();
  (void)rba_MultiStackTrace_ScanAllStacks();
  (void)rba_MultiStackTrace_ScanAllStacks();
  (void)rba_MultiStackTrace_ScanAllStacks();
  (void)rba_MultiStackTrace_ScanAllStacks();
  (void)rba_MultiStackTrace_ScanAllStacks();
  (void)rba_MultiStackTrace_ScanAllStacks();

  (void)rba_MultiStackTrace_GetStackInfo(RBSYS_Stack0_StackId, &result);
  RBSYS_Stack0_freespace = (result.FreeSpace > STACK_LIMITRED_BYTES) ? (result.FreeSpace - STACK_LIMITRED_BYTES) : 0;

  if (result.CheckWordReached != 0)
  {
    if ((rba_MultiStackTrace_IsLimitExceeded(&result, 0)) != 0)
    {
      stackfault |= (1u<<RBSYS_stack0check0);
    }
    if ((rba_MultiStackTrace_IsLimitExceeded(&result, 1)) != 0)
    {
      stackfault |= (1u<<RBSYS_stack0check1);
    }
    if ((rba_MultiStackTrace_IsLimitExceeded(&result, 2)) != 0)
    {
      stackfault |= (1u<<RBSYS_stack0check2);
    }
    freestack_dbg = RBSYS_Stack0_freespace;
  }

#if(RBFS_MCORE == RBFS_MCORE_ON)
  (void)rba_MultiStackTrace_GetStackInfo(RBSYS_Stack1_StackId, &result);
  RBSYS_Stack1_freespace = (result.FreeSpace > STACK_LIMITRED_BYTES) ? (result.FreeSpace - STACK_LIMITRED_BYTES) : 0;

  if (result.CheckWordReached != 0)
  {
    if ((rba_MultiStackTrace_IsLimitExceeded(&result, 0)) != 0)
    {
      stackfault |= (1u<<RBSYS_stack1check0);
    }
    if ((rba_MultiStackTrace_IsLimitExceeded(&result, 1)) != 0)
    {
      stackfault |= (1u<<RBSYS_stack1check1);
    }
    if ((rba_MultiStackTrace_IsLimitExceeded(&result, 2)) != 0)
    {
      stackfault |= (1u<<RBSYS_stack1check2);
    }
    // use stack1 freestack as d1 only in case stack0 did not overflow
    if (freestack_dbg == 0xFFFFFFFFu)
    {
      freestack_dbg = RBSYS_Stack1_freespace;
    }

  }
#endif

  if (stackfault != 0)
  {
    RBSYS_setStackOverUnderFlowError(stackfault, freestack_dbg);
  }
}


/** @} */
/* End ingroup RBSYS */
