/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief RBSYS exception handler
 *
 * RBSYS exception handler for FEINT and SYSERR
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "Os.h"
#include "RBSYS_Intrinsics.h"
#include "RBSYS_GHS_ProgramStartup.h"
#include "SystemMemoryProtection/RBSYS_GuardConfigCommon.h"
#include "RBSYS_uCResetCtrl.h"
#include "RBSYS_RAMBackupServiceIntern.h"
#include "Monitorings/RBSYS_ErrorHooks.h"


/******************************************************************************/
/* header includes for ECM and TPSW exception handler via MergeProc                    */
/******************************************************************************/
/*ROOT_SECTION: ExceptionHandlerHeaderIncludes_Root |#include "|" */
/*PROC_EP: ExceptionHandlerHeaderIncludes */
/*ROOT_SECTION_END: */


/* realized interfaces */
#include "RBSYS_ExceptionInfo.h"
#include "RBSYS_ExceptionHandler.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysTPSWSupport,
                          RBFS_SysTPSWSupport_YES,
                          RBFS_SysTPSWSupport_NO);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWSVPRestrictions,
                          RBFS_TPSWSVPRestrictions_OFF,
                          RBFS_TPSWSVPRestrictions_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEnvironment,
                          RBFS_SysEnvironment_Target,
                          RBFS_SysEnvironment_Simulation);





/* -------------------------------------------------------------------------- */
/* QAC|DEV 0009: In-line assembly embedded in normal C code                   */
/* -------------------------------------------------------------------------- */
/* Msg 1006: In-line assembler construct is a language extension.             */
/* -------------------------------------------------------------------------- */
#ifdef __QAC__
  #pragma PRQA_MESSAGES_OFF 1006
#endif


#if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) \
    )
    /*
    Example from OS (os.h):

    #define OS_FETRAP_EXCEPTION(name, isr)   OS_PRAGMA( ghs noprologue)   \
      void name( void) {     OS_FETRAP_ENTRY();     isr();     OS_FETRAP_LEAVE();   }
    */

    #if(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
      /** TODO: Cross-Check with final OS port */
      #define OS_FETRAP_ENTRY RBSYS_TRAP_ENTRY
      #define OS_FETRAP_LEAVE RBSYS_TRAP_LEAVE
    #endif


    // Hint: Below code is taken from OS (os.h) => cross-check with new OS delivery

    /* NO_TOOL_SCAN */
    /* REASON: Usage of RH850 specific predefined compiler macros */

    #pragma asm

      #if (__V800_registermode==22)
        .set  regframe, 18
      #endif
      #if (__V800_registermode==26)
        .set  regframe, 20
      #endif
      #if (__V800_registermode==32)
        .set  regframe, 23
      #endif
        .set  framesize, regframe*4

    #pragma endasm


    //ToDo: Adapt for U2A
    static void RBSYS_TRAP_ENTRY(void);
    asm void RBSYS_TRAP_ENTRY(void)
    {
%lab cpuid0 %lab cpuid1

        -- isr prolog
        -- 22 reg mode: save 15 registers + FEPSW + FEPC  + FPSR + FPEPC
        -- 26 reg mode: save 17 registers + FEPSW + FEPC  + FPSR + FPEPC
        -- 32 reg mode: save 20 registers + FEPSW + FEPC  + FPSR + FPEPC
        prepare   {ep-lp}, regframe, sp
        sst.w     r1,  (framesize-4)[ep]

        stsr      FEPSW, r1, 0
        sst.w     r1,  (framesize-8)[ep]

        stsr      FEPC, r1, 0
        sst.w     r1,  (framesize-12)[ep]

        sst.w     r2,  (framesize-16)[ep]
        sst.w     gp,  (framesize-20)[ep]
        sst.w     r5,  (framesize-24)[ep]
        sst.w     r6,  (framesize-28)[ep]
        sst.w     r7,  (framesize-32)[ep]
        sst.w     r8,  (framesize-36)[ep]
        sst.w     r9,  (framesize-40)[ep]
        sst.w     r10, (framesize-44)[ep]
        sst.w     r11, (framesize-48)[ep]
        sst.w     r12, (framesize-52)[ep]
        sst.w     r13, (framesize-56)[ep]
        sst.w     r14, (framesize-60)[ep]

        stsr      FPSR, r1, 0
        sst.w     r1,  (framesize-64)[ep]

        stsr      FPEPC, r1, 0
        sst.w     r1,  (framesize-68)[ep]

    #if (__V800_registermode==26)
        sst.w     r15, (framesize-72)[ep]
        sst.w     r16, (framesize-76)[ep]
    #endif
    #if (__V800_registermode==32)
        sst.w     r15, (framesize-72)[ep]
        sst.w     r16, (framesize-76)[ep]
        sst.w     r17, (framesize-80)[ep]
        sst.w     r18, (framesize-84)[ep]
        sst.w     r19, (framesize-88)[ep]
    #endif



    }


    #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    static void RBSYS_CLEAR_FEINT_STATUS(void);
    asm void RBSYS_CLEAR_FEINT_STATUS(void)
    {
      // check cpu id
      stsr  0, r10, 2   --myid = __STSR(0,2)
      cmp 1, r10
      be cpuid1

    cpuid0:
      movhi hi(-6669560),zero,r11  --clear FEINC_PE0FEINTC (0xFF9A3B08)
      mov 4, r12
      st.w r12, 15112[r11]

    cpuid1:
      movhi hi(-6669304),zero,r11  --clear FEINC_PE1FEINTC (0xFF9A3C08)
      mov 4, r12
      st.w r12, 15368[r11]
    }
    #endif


    //ToDo: Adapt for U2A
    static void RBSYS_TRAP_LEAVE(void);
    asm void RBSYS_TRAP_LEAVE(void)
    {
%lab cpuid0 %lab cpuid1

        mov       sp, ep
        di

    #if (__V800_registermode==32)
        sld.w     (framesize-88)[ep], r19
        sld.w     (framesize-84)[ep], r18
        sld.w     (framesize-80)[ep], r17
        sld.w     (framesize-76)[ep], r16
        sld.w     (framesize-72)[ep], r15
    #endif
    #if (__V800_registermode==26)
        sld.w     (framesize-76)[ep], r16
        sld.w     (framesize-72)[ep], r15
    #endif
        sld.w     (framesize-60)[ep], r14
        sld.w     (framesize-56)[ep], r13
        sld.w     (framesize-52)[ep], r12
        sld.w     (framesize-48)[ep], r11
        sld.w     (framesize-44)[ep], r10
        sld.w     (framesize-40)[ep], r9
        sld.w     (framesize-36)[ep], r8
        sld.w     (framesize-32)[ep], r7
        sld.w     (framesize-28)[ep], r6
        sld.w     (framesize-24)[ep], r5
        sld.w     (framesize-20)[ep], gp
        sld.w     (framesize-16)[ep], r2

        //di   moved to top
        sld.w     (framesize-68)[ep], r1
        ldsr      r1, FPEPC, 0

        sld.w     (framesize-64)[ep], r1
        ldsr      r1, FPSR, 0

        syncp  // see P1x UM Rev. 1.30 Chapter 3.4.8 "System Register Hazards"

        sld.w     (framesize-12)[ep], r1
        ldsr      r1, FEPC, 0

        sld.w     (framesize-8)[ep], r1
        ldsr      r1, FEPSW, 0

        sld.w     (framesize-4)[ep], r1
        dispose   regframe, {ep-lp}
    }

    /* return from FE level exception */
    static void RBSYS_FERET(void);
    asm void RBSYS_FERET(void)
    {
      feret
    }

    /* return from debug exception */
    static void RBSYS_DBRET(void);
    asm void RBSYS_DBRET(void)
    {
      dbret
    }


    /******************************************************************/
    /* --------------- FPP EXCEPTION HANDLER ------------------------ */
    /******************************************************************/

    static void RBSYS_EXCFPP_IMPL(void)
    {
      /*ROOT_SECTION: SPG_RBSYS_EXCFPP_Root | |(); */
      /*PROC_EP: SPG_RBSYS_EXCFPP */
      /*ROOT_SECTION_END: */
    }

    __interrupt void RBSYS_EXCFPP_Handler(void)
    {
      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        Os_imaskType Os_imask = OS_STSR(OS_PMR, OS_SELID_2);
        OS_BARRIER();
        OS_SYNCI();
        OS_LDSR(OS_PMR, OS_SELID_2, (Os_imaskType)0xFFFFU);
        OS_EI();
        OS_BARRIER();
        RBSYS_EXCFPP_IMPL();
        OS_BARRIER();
        OS_LDSR(OS_PMR, OS_SELID_2, Os_imask);
        OS_SYNCI();
        OS_BARRIER();
      #elif ((RBFS_uCFamily== RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily== RBFS_uCFamily_RenesasU2C))
        Os_imaskType Os_imask = OS_STSR(OS_PLMR_REGID, OS_PLMR_SELID);
        uint32 Os_FPSR = OS_STSR(OS_FPSR_REGID, OS_FPSR_SELID);
        uint32 Os_FPEPC = OS_STSR(OS_FPEPC_REGID, OS_FPEPC_SELID);
        RBSYS_LDSR(OS_PLMR_REGID, OS_PLMR_SELID, 0);
        RBSYS_EXCFPP_IMPL();
        RBSYS_LDSR(OS_PLMR_REGID, OS_PLMR_SELID, Os_imask);
        RBSYS_LDSR(OS_FPSR_REGID, OS_FPSR_SELID, Os_FPSR);
        RBSYS_LDSR(OS_FPEPC_REGID, OS_FPEPC_SELID, Os_FPEPC);
      #else
        assert(0 && "FPP Handler is not implemented for this uC Family");
      #endif
    }



    /* NO_TOOL_SCAN_END */

    #ifdef __QAC__
      #pragma PRQA_MESSAGES_ON 1006
    #endif


    /* raw handler (without OS interaction) for "FPU exception" */
    RBSYS_ATTR_NO_PROLOGUE
    void b_EXCFPP(void)
    {
      RBSYS_TRAP_PERMISSION_ENTRY(); //< Set Core SPID to SAFE.

      /* TPSW Software:      FPP Exception could be caused by TPSW and TPSW shall be aborted. */
      /* Non-TPSW Software:  FPP Exception was caused by non-Third Party Software and shall be handled. */
      #if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)
        /*ROOT_SECTION: SPG_RBSYS_TPSWEXCFPP_Root | |(); */
        /*PROC_EP: SPG_RBSYS_TPSWEXCFPP */
        /*ROOT_SECTION_END: */
      #else
        RBSYS_EXCFPP_Handler();
      #endif

      RBSYS_TRAP_PERMISSION_LEAVE(); //< Restore previous SPID
    }



    /******************************************************************/
    /* --------------- MAE EXCEPTION HANDLER ------------------------ */
    /******************************************************************/

    static void RBSYS_EXCMAE_IMPL(void)
    {
      /*ROOT_SECTION: SPG_RBSYS_EXCMAE_Root | |(); */
      /*PROC_EP: SPG_RBSYS_EXCMAE */
      /*ROOT_SECTION_END: */
    }


    /* raw handler (without OS interaction) for "misalign exception" */
    RBSYS_ATTR_NO_PROLOGUE
    void b_EXCMAE(void)
    {
      RBSYS_TRAP_PERMISSION_ENTRY(); //< Set Core SPID to SAFE.

      #if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)
        /*ROOT_SECTION: SPG_RBSYS_TPSWEXCMAE_Root | |(); */
        /*PROC_EP: SPG_RBSYS_TPSWEXCMAE */
        /*ROOT_SECTION_END: */
      #endif

      OS_FETRAP_ENTRY(); // Why OS_ or RBSYS_ ??
      RBSYS_EXCMAE_IMPL();
      OS_FETRAP_LEAVE(); // Why OS_ or RBSYS_ ??

      RBSYS_TRAP_PERMISSION_LEAVE(); //< Restore previous SPID //< this has no effect because OS_FETRAP does call FERET
    }



    /******************************************************************/
    /* --------------- RIE EXCEPTION HANDLER ------------------------ */
    /******************************************************************/

    static void RBSYS_EXCRIE_IMPL(void)
    {
      /*ROOT_SECTION: SPG_RBSYS_EXCRIE_Root | |(); */
      /*PROC_EP: SPG_RBSYS_EXCRIE */
      /*ROOT_SECTION_END: */
    }


    /* raw handler (without OS interaction) for "reserved instruction exception" */
    RBSYS_ATTR_NO_PROLOGUE
    void b_EXCRIE(void)
    {
      RBSYS_TRAP_PERMISSION_ENTRY(); //< Set Core SPID to SAFE.

      #if (RBFS_SysTPSWSupport == RBFS_SysTPSWSupport_YES)
        /*ROOT_SECTION: SPG_RBSYS_TPSWEXCRIE_Root | |(); */
        /*PROC_EP: SPG_RBSYS_TPSWEXCRIE */
        /*ROOT_SECTION_END: */
      #endif

      OS_FETRAP_ENTRY(); // Why OS_ or RBSYS_ ??
      RBSYS_EXCRIE_IMPL();
      OS_FETRAP_LEAVE(); // Why OS_ or RBSYS_ ??

      RBSYS_TRAP_PERMISSION_LEAVE(); //< Restore previous SPID //< this has no effect because OS_FETRAP does call FERET
    }



    /******************************************************************/
    /* --------------- SYSERR EXCEPTION HANDLER --------------------- */
    /******************************************************************/

    static void RBSYS_EXCSYSERR_IMPL(void)
    {
    /*
      -- not needed => we do not call any public function in the exception handler
      -- so locking via automatic di exception entry is sufficient

      -- TODO: if locks etc are needed it is better to work via PMR instead of EI/DI

      Os_imaskType Os_imask = __STSR(OS_PMR, OS_SELID_2);
      Os_synci();
      __LDSR(OS_PMR, OS_SELID_2, (Os_imaskType)0xFFFFU);
      __EI();
      */

      /*ROOT_SECTION: SPG_RBSYS_EXCSYSERR_Root | |(); */
      /*PROC_EP: SPG_RBSYS_EXCSYSERR */
      /*ROOT_SECTION_END: */

      /*
    __LDSR(OS_PMR, OS_SELID_2, Os_imask);
      Os_synci();
    */
    }


    /* raw handler (without OS interaction) for "system error exceptions" */
    RBSYS_ATTR_NO_PROLOGUE
    void b_EXCSYSERR(void)
    {
      RBSYS_TRAP_PERMISSION_ENTRY(); //< Set Core SPID to SAFE.

      /* HW-Erratum RB148 @ U2A: It is possible that Instruction Fetch Errors are not notified to ECM and FEInt is not
        generated. Nevertheless, these Errors will cause SYSERR Exceptions. It is important to set the Error-Pin once we
        acknowledge an Instruction Fetch Error via SYSERR. (Implicitly done when calling RBECM_EXCSYSERR_Handler -> see
        MergeProc file) */
      RBSYS_TRAP_ENTRY(); // Why OS_ or RBSYS_ ??
      RBSYS_EXCSYSERR_IMPL();
      RBSYS_TRAP_LEAVE(); // Why OS_ or RBSYS_ ??

      RBSYS_TRAP_PERMISSION_LEAVE(); //< Restore previous SPID
      RBSYS_FERET();
    }



    /******************************************************************/
    /* --------------- FEINT EXCEPTION HANDLER ---------------------- */
    /******************************************************************/

    static void RBSYS_EXCFEINT_IMPL(void)
    {
      /*ROOT_SECTION: SPG_RBSYS_EXCFEINT_Root | |(); */
      /*PROC_EP: SPG_RBSYS_EXCFEINT */
      /*ROOT_SECTION_END: */

      /* todo:
      * The event status flag should be cleared by software in the beginning of the interrupt service routine.
      * If there is a pending interrupt flag after leaving the interrupt service routine the interrupt will be asserted
      * again until all flags in FEINTESTAT are cleared.
      */
    }


    /* raw handler (without OS interaction) for "FE-level maskable interrupts" */
    RBSYS_ATTR_NO_PROLOGUE
    void b_EXCFEINT(void)
    {
      RBSYS_TRAP_PERMISSION_ENTRY(); //< Set Core SPID to SAFE.

      RBSYS_TRAP_ENTRY(); // Why OS_ or RBSYS_ ??

      #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        RBSYS_CLEAR_FEINT_STATUS();
      #endif

      RBSYS_EXCFEINT_IMPL();
      RBSYS_TRAP_LEAVE(); // Why OS_ or RBSYS_ ??

      RBSYS_TRAP_PERMISSION_LEAVE(); //< Restore previous SPID
      RBSYS_FERET();
    }



    /******************************************************************/
    /* --------------- DEBUG EXCEPTION HANDLER ---------------------- */
    /******************************************************************/

    /* SYS debug exception handler only called if Gliwa T1.flex is not integrated */
    static void RBSYS_EXCDEBUG_IMPL(void)
    {
      /*ROOT_SECTION: SPG_RBSYS_EXCDEBUG_Root | |(); */
      /*PROC_EP: SPG_RBSYS_EXCDEBUG */
      /*ROOT_SECTION_END: */
    }


    /* generate asm statement .globl (extern prototype) for T1 flex pocess integrated via MergeProc*/
    #pragma asm
    /*ROOT_SECTION: SPG_T1_EXCDEBUG_ROOT1 | .globl | */
    /*PROC_EP: SPG_T1_EXCDEBUG */
    /*ROOT_SECTION_END: */
    #pragma endasm


    /* raw handler (without OS interaction) for "debug exceptions" */
    RBSYS_ATTR_NO_PROLOGUE
    void b_EXCDEBUG(void)
    {
      /********************************************************************************************/
      /* raw exception handler for Gliwa T1.flex:                                                 */
      /* Gliwa T1.flex requires a direct jump in asm without modification of link register.       */
      /* MergeProc is used therefore to add inline assembler instruction if T1.flex is integrated */
      /* in the project. T1 will not return afterwards here.                                      */
      /********************************************************************************************/

      /*ROOT_SECTION: SPG_T1_EXCDEBUG_ROOT2 | __asm("jr _| "); */
      /*PROC_EP: SPG_T1_EXCDEBUG */
      /*ROOT_SECTION_END: */

      // Gliwa has to handle permissions (at entry and exit) once interrupt is called. This function will never be executed then
      // because Gliwa will return to calling function directly.
      RBSYS_TRAP_PERMISSION_ENTRY(); //< Set Core SPID to SAFE.

      /********************************************************************************************/
      /* default SYS exception handling only called if Gliwa T1.flex is not integrated            */
      /********************************************************************************************/
      RBSYS_TRAP_ENTRY(); // Why OS_ or RBSYS_ ??
      RBSYS_EXCDEBUG_IMPL();
      RBSYS_TRAP_LEAVE(); // Why OS_ or RBSYS_ ??

      RBSYS_TRAP_PERMISSION_LEAVE(); //< Restore previous SPID
      RBSYS_DBRET();
    }

  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

    static void RBSYS_TRAP_ENTRY(void);
    asm void RBSYS_TRAP_ENTRY(void)
    {
%lab core0 %lab core1 %lab end

      mrs SP, SP_usr               ; restore generic Stackpointer
      push {r0-r12, lr}            ; Store the original registers

      ; get core ID
      mrc p15, 0, r2, c0, c0, 5   ; Read MPIDR
      and r2, 0xff                ; Extract core ID

      cmp r2, RBSYS_CORE_ID_0
      bne core1

      core0:
        // store current LP of core 0 into global RAM variables
        mov r0, lr
        movw r1, %lo(RBSYS_ExceptionProgramCounterForDebug)
        movt r1, %hi(RBSYS_ExceptionProgramCounterForDebug)
        add r1,0
        str r0, [r1], 4

        b end

      core1:
        // store current LP of core 1 into global RAM variables
        mov r0, lr
        movw r1, %lo(RBSYS_ExceptionProgramCounterForDebug)
        movt r1, %hi(RBSYS_ExceptionProgramCounterForDebug)
        add r1,4
        str r0, [r1], 4

        b end

      end:
    }


    static void RBSYS_TRAP_LEAVE(void);
    asm void RBSYS_TRAP_LEAVE(void)
    {
      pop {r0-r12, lr}          ; Restore original registers

      // Dependent of current Mode (Abort / Undef / FIQ / ...), different return instructions have to be used.
      // Following example is valid for DataAbort only!
      subs pc, lr, 8            ; Return from TRAP: change Mode to previous CPSR (stored in SPSR) and branch to LR
    }

    extern void RBSYS_ExceptionVector_UndefinedInstruction(void);
    void RBSYS_ExceptionVector_UndefinedInstruction(void)
    {
      RBSYS_TRAP_ENTRY();

      /*ROOT_SECTION: SPG_RBSYS_EXCUNDEFINSTR_Root | |(); */
      /*PROC_EP: SPG_RBSYS_EXCUNDEFINSTR */
      /*ROOT_SECTION_END: */

      // /* todo: decide where to handle the exception (e.g. RBECM for Reneses) */

      // RBSYS_uCResetSkipBootBlock();

      /* Do something regarding Instruction Prefetch Abort*/

      /* We cannot return from here!!!
        -------------------------------------------------------------------------------------
        Why? => Example: Undefined Instruction exception could be caused by jumping to invalid address
          1. the Program Counter points to an invalid address
          2. R52 will copy PC+1 (still invalid) to the Link Register
          3. Returning from Exception does make no sense
      */
    }

    extern void RBSYS_ExceptionVector_PrefetchAbort(void);
    void RBSYS_ExceptionVector_PrefetchAbort(void)
    {
      RBSYS_TRAP_ENTRY();

      /*ROOT_SECTION: SPG_RBSYS_EXCPREFETCHABORT_Root | |(); */
      /*PROC_EP: SPG_RBSYS_EXCPREFETCHABORT */
      /*ROOT_SECTION_END: */



      // /* todo: decide where to handle the exception (e.g. RBECM for Reneses) */

      // RBSYS_uCResetSkipBootBlock();

      /* Do something regarding Instruction Prefetch Abort*/

      /* We cannot return from here!!!
        -------------------------------------------------------------------------------------
        Why? => Example: Prefetch Abort exception could be caused by jumping to invalid address
          1. the Program Counter points to an invalid address
          2. R52 will copy PC+1 (still invalid) to the Link Register
          3. Returning from Exception does make no sense
      */
    }

    extern void RBSYS_ExceptionVector_DataAbort(void);
    void RBSYS_ExceptionVector_DataAbort(void)
    {
      RBSYS_TRAP_ENTRY();

      /*ROOT_SECTION: SPG_RBSYS_EXCDATAABORT_Root | |(); */
      /*PROC_EP: SPG_RBSYS_EXCDATAABORT */
      /*ROOT_SECTION_END: */


      // /* todo: decide where to handle the exception (e.g. RBECM for Reneses) */

      // RBSYS_uCResetSkipBootBlock();

      /* Do something regarding Data Abort*/

      /* We cannot return from here!!!
        -------------------------------------------------------------------------------------
        Why? => Data Abort exception is not always synchronous and !!!precise!!!. Therefore,
          1. the Program Counter could be incremented already
          2. R52 will copy Program Counter+1 to the Link Register
          3. ERET will jump to Program Counter+1
          4. New PC is being aligned
          5. That can result in a wrong Program Flow because the not executed instruction may have been a branch instruction
        */

      RBSYS_TRAP_LEAVE();
    }

  #endif

#else

  // Exception Handlers + Trap Entry / Exit functions cannot be tested in Unittests due to ASM implementations

#endif //(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)




#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  /* For ARM R52, there is no persistent exception return register, therefore Link Pointer is saved during assertion of the exception. */
  static uint32 RBSYS_ExceptionProgramCounterForDebug[RB_NUM_CORES];

  uint32 RBSYS_ExceptionHandler_GetExceptionProgramCounterForDebug(void)
  {
    return RBSYS_ExceptionProgramCounterForDebug[RBSYS_getCoreID()];
  }
#endif

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) \
  )
  void RBSYS_HandleSupervisorMpuViolation(void)
  {
    #if (RBFS_TPSWSVPRestrictions == RBFS_TPSWSVPRestrictions_ON)
      uint32 feic = RBSYS_STSR(14, 0) & 0xffffu;
      if ((feic == 0x90u) || (feic == 0x91u))
      {
        /* MIP or MDP exception during supervisor mode */

        /* RH850 FEPC register content: PC when exception occurred */
        uint32 debug_info = RBSYS_STSR(2, 0);

        /* Strategy here is similar to CPU exception handling within RBECM:
            SW reset with subsequent failure entry (=> RBSYS_SYSErrorHook) */
        
        RBSYS_setSYSErrorHook(RBSYS_Error_SupervisorRestriction, debug_info);
      }
      else
        /*->InvalidInt(), see below*/
    #endif
    {
      /* When coming from supervisor, same reaction than SC1: MDP/PIE mapped to Invalid  */
      /* interrupt handler. This handler resets the system. If not, a trusted            */
      /* task/isr would be killed, which is not acceptable.                              */
      InvalidInt();
    }
  }
#else
  #warning("Handler for SupervisorMpuViolation is not implented for this uC-Family yet.")
#endif


/** @} */
/* End ingroup RBSYS */
