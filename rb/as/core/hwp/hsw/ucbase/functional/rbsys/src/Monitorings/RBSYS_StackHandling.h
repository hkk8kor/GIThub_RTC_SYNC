#ifndef RBSYS_STACKHANDLING_H__
#define RBSYS_STACKHANDLING_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Stack handling
 *
 * Stack handling and allocation of functional software (FSW). Bootblock stack will be handled separate.
 * Stack size must be a part of project specific configuration.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBLCF_MemoryRemap.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_ON,
                          RBFS_MCORE_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEnvironment,
                          RBFS_SysEnvironment_Target,
                          RBFS_SysEnvironment_Simulation);



/* for both stacks: */
#define RB_STACK_LOWCHK0    (0)   /* last check word at end */
#define RB_STACK_LOWCHK1    (20)  /* detection 20 words before stack exceeds to have a small buffer in case of an overflow .. */

/* stack 0: */
#define RB_STACK0_ARRAYSIZE  ((RB_STACK0_SIZE_FSW/4)+RB_STACK_LOWCHK1+6)  /* +6 (3 checkwords each 2 words) */
#define RB_STACK0_START      ((RB_STACK0_ARRAYSIZE)-1)  /* first word on stack */
#define RB_STACK0_UPPERCHK   ((RB_STACK0_START)-1)      /* two 32 bit checkwords are placed */
#define RB_STACK0_INITSP     ((RB_STACK0_UPPERCHK)-1)   /* init sp below upper checkword */

/* stack 1: */
#define RB_STACK1_ARRAYSIZE  ((RB_STACK1_SIZE_FSW/4)+RB_STACK_LOWCHK1+6)
#define RB_STACK1_START      ((RB_STACK1_ARRAYSIZE)-1)
#define RB_STACK1_UPPERCHK   ((RB_STACK1_START)-1)
#define RB_STACK1_INITSP     ((RB_STACK1_UPPERCHK)-1)



/* contains init SP value to be used during start-up */
RBSECTION_START_SECTTYPE_NO_SDA
extern volatile unsigned int* const RB_SP0_FSW;
extern volatile unsigned int* const RB_SP1_FSW;
RBSECTION_END_SECTTYPE_NO_SDA


// export only for rba_MultiStackTrace
RBSECTION_START_STACK_CPU0_NOCLEAR
extern volatile unsigned int RB_Stack0_FSW[RB_STACK0_ARRAYSIZE];
RBSECTION_END_STACK_CPU0_NOCLEAR

#if(RBFS_MCORE == RBFS_MCORE_ON)
  RBSECTION_START_STACK_CPU1_NOCLEAR
  extern volatile unsigned int RB_Stack1_FSW[RB_STACK1_ARRAYSIZE];
  RBSECTION_END_STACK_CPU1_NOCLEAR
#endif




/* -------------------------------------------------------------------------- */
/* QAC|DEV 0009: In-line assembly embedded in normal C code                   */
/* -------------------------------------------------------------------------- */
/* Msg 1006: In-line assembler construct is a language extension.             */
/* -------------------------------------------------------------------------- */
#ifdef __QAC__
  #pragma PRQA_MESSAGES_OFF 1006
#endif


/**
 * \brief Stack initialization
 *
 * SP (stack pointer) initialization will be done explicitly with this asm macro in the corresponding
 * context directly at startup (bootblock and application context) and therefore removed from
 * GHS startup code. So this function must be called by both cores and will init corespecific the stack pointer.
 * It's done in asm macro to ensure inline code.
 *
 * @param [in] asm_sp0 defines the pointer to stack area of Core0
 * @param [in] asm_sp1 defines the pointer to stack area of Core1
 *
 * @return void
 */
#if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

    static void RBSYS_stackInit(volatile unsigned int* const asm_sp0, volatile unsigned int* const asm_sp1);
    asm void RBSYS_stackInit(volatile unsigned int* const asm_sp0, volatile unsigned int* const asm_sp1)
    {
%farmem asm_sp0 %farmem asm_sp1 %lab cpuid0 %lab cpuid1 %lab end
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      stsr  0, r10, 2   --myid = (__STSR(0,2)>>16);
      shr 16, r10
      addi -1, r10, r10
    #else
      stsr  0, r10, 2   --myid = __STSR(0,2)
    #endif
      cmp 1, r10
      be cpuid1
    cpuid0:
      mov asm_sp0, r10
      ld.w  0[r10], sp
      jr end

    cpuid1:
      mov asm_sp1, r10
      ld.w  0[r10], sp

    end:
%error
    }

  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

    static void RBSYS_stackInit(volatile unsigned int* const asm_sp0, volatile unsigned int* const asm_sp1);
    asm void RBSYS_stackInit(volatile unsigned int* const asm_sp0, volatile unsigned int* const asm_sp1)
    {
%farmem asm_sp0 %farmem asm_sp1 %lab cpuid0 %lab cpuid1 %lab end
      mrc   p15,0,r0,c0,c0,5
      and   r0,r0,1
      cmp   r0,1
      beq   cpuid1
    cpuid0:
      movw  r0,%lo(asm_sp0)
      movt  r0,%hi(asm_sp0)
      ldr   sp,[r0,0]
      b     end

    cpuid1:
      movw  r0,%lo(asm_sp1)
      movt  r0,%hi(asm_sp1)
      ldr   sp,[r0,0]

    end:
%error
    }

  #endif
#else
  /* Declare assembly function as extern so that it can be stubbed in x86 testing */
  extern void RBSYS_stackInit(volatile unsigned int* const asm_sp0, volatile unsigned int* const asm_sp1);
#endif


#ifdef __QAC__
  #pragma PRQA_MESSAGES_ON 1006
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
