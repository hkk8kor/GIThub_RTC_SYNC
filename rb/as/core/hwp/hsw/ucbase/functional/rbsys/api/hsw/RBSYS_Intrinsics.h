#ifndef RBSYS_INTRINSICS_H__
#define RBSYS_INTRINSICS_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Intrinsics
 *
 * Guideline for usage of intrinsics:
 * - Using intrinsics is only allowed for agreed applications due to portability issues -
 *   therefore contact always RBSYS responsible!!!
 * - Also do not use target specific intrinsics directly (name of a C intrinsic function begins with two underscores (__))
 *   use RBSYS encapsulated functions provided via this interface.
 *
 * General hint:
 * Since asm statements are not portable, the RH850 compiler provides special
 * inline intrinsic functions. This intrinsic functions perform certain tasks
 * which are difficult or inefficient to write in a high-level language. It
 * usually generates optimized inline code, often using special instructions
 * that do not correspond to standard C and C++ operations. Therefore take
 * caution when using these intrinsics!
 *
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */

#include "RBSYS_Config.h"

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_Compiler,
                          RBFS_Compiler_GHS,
                          RBFS_Compiler_GCC4HSim,
                          RBFS_Compiler_GCC4BSWSim,
                          RBFS_Compiler_GHS2018,
                          RBFS_Compiler_GHS2021,
                          RBFS_Compiler_GCC4,
                          RBFS_Compiler_TDM5);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEnvironment,
                            RBFS_SysEnvironment_Target,
                            RBFS_SysEnvironment_Simulation);


#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
  || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )

  /* used interfaces */
  #if( (RBFS_Compiler == RBFS_Compiler_GHS) || (RBFS_Compiler == RBFS_Compiler_GHS2018) || (RBFS_Compiler == RBFS_Compiler_GHS2021) )
    #include <v800_ghs.h>
    #include <ghs_barrier.h>
  #endif

  /**************************************************************************************/
  /* Using intrinsics is only allowed for agreed applications due portability issues!!  */
  /* Contact RBSYS responsible!!!                                                       */
  /**************************************************************************************/






  /**
  * @brief Store content of system register into a program register
  *
  * Program Registers are accessible in user and supervisor mode (r0–r31 and program counter).
  *
  * System Registers can only be read by using the STSR instruction. The basic system registers control
  * CPU status and exception information (e.g. PSW).
  *
  * Hint: consider guidelines at the top of this file
  * Hint: some intrinsics do not generate sequence points, see https://inside-docupedia.bosch.com/confluence/display/BBMCOM/Ordering+and+optimization+for+intrinsics%2C+asm+statements+and+volatile+variables
  *       consider adding __memory_changed() calls around this intrinsic
  *
  * @param regID   System register number
  * @param selID   System register group number
  *
  * @returns the system register content
  */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #define RBSYS_STSR(regID, selID)            __STSR(regID, selID)
  #else
    // stub for simulation, todo: provide C implementation of intrinsic, see WI 2243461
    #define RBSYS_STSR(regID, selID)            (0xABCDEF55u)
  #endif


  /**
  * @brief Load a system register with the content of a program register
  *
  * Program Registers are accessible in user and supervisor mode (r0–r31 and program counter).
  *
  * System Registers can only be written by using the LDSR instruction. The basic system registers control
  * CPU status and exception information (e.g. PSW).
  *
  * Hint: consider guidelines at the top of this file
  *
  * @param regID   System register number
  * @param selID   System register group number
  * @param val     System register value
  *
  * @return void
  */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #define RBSYS_LDSR(regID, selID, val)       __memory_changed(); __LDSR(regID, selID, val); __memory_changed()
  #else
    // stub for simulation, todo: provide C implementation of intrinsic, see WI 2243461
    #define RBSYS_LDSR(regID, selID, val)
  #endif


  /************************************************************************************************************/
  /* Memory access introduction on RH850/P1x-C                                                                */
  /*                                                                                                          */
  /* The bus interface units are operating independently from the CPU. In case of a read and write access     */
  /* of the CPU to a memory location, the CPU triggers an access to this memory, but does not necessarily     */
  /* wait for its completion. In this context the following rules for memory accesses from the CPU do apply:  */
  /* - When a read access is performed: the CPU stalls only when the data is needed                           */
  /* - When a write access is performed: the CPU is not waiting for completion                                */
  /* - A read access has a higher priority than a write access. Therefore a read access may be executed       */
  /*   before a write access to a different memory location, even if it was issued later.                     */
  /* Note: This does not apply for peripheral accesses. These are strictly in order.                          */
  /*                                                                                                          */
  /* Renesas provided an application note for further details:                                                */
  /* "Ensuring Completion of Memory and Register Accesses" "R01AN2319ED0100_RH850P1x-C.pdf"                   */
  /* in addition you can see Mantis issue 0000677 within CC-Cube DeviceSupport                                */
  /************************************************************************************************************/


  /**
  * @brief Synchronize memory operations
  *
  * The "syncm"-instruction waits for completion of all data transfers. So it synchronizes
  * data load/stores to GRAM/LRAM, peripheral registers and peripheral RAMs:
  *
  * It waits for the completion of the write operation before the subsequent instruction is executed.
  * And "syncm" ensures the arrival of the written data at its final destination by return of an
  * acknowledge signal. It also ensures, that a read access has been finished.
  *
  * @note "syncm" does not wait for completion of instruction transfers (remember that the
  * Harvard architecture has separate instruction and data busses).
  *
  * @note Also note that limitations for certain data busses may apply. Current devices do not
  * support "syncm" for the HBUS.
  */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #define RBSYS_SYNCM()                       __memory_changed(); __SYNCM(); __memory_changed()
  #else
    // stub for simulation, todo: provide C implementation of intrinsic, see WI 2243461
    #define RBSYS_SYNCM()
  #endif


  /**
  * @brief Synchronize pipeline operations
  *
  * The "syncp"-instruction ensures, that all previous instructions have been completed and
  * the read data requested (e.g. from a peripheral) has arrived at the CPU. It does not ensure,
  * that written data has reached its final destination.
  *
  * @note "syncp" ensures that write data has left the CPU write buffer, but it does not ensure
  * that write data has reached its final destination.
  */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #define RBSYS_SYNCP()                       __memory_changed(); __SYNCP(); __memory_changed()
  #else
    // stub for simulation, todo: provide C implementation of intrinsic, see WI 2243461
    #define RBSYS_SYNCP()
  #endif


  /**
  * @brief Synchronize instruction pipeline
  *
  * The "synci"-instruction clears the CPU instruction fetch pipeline so that subsequently executed
  * instructions are re-fetched. The purpose of "synci" is to realize self-modifying code.
  * And "synci" will not wait for completion of any previous memory accesses.
  *
  * @note "synci" will flush all applicable buffers in the instruction fetch queue, with the exception
  * of cache memory. So the instruction cache is not invalidated, therefore it's recommended to disable
  * the instruction cache when implementing self-programming sequences.
  */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #define RBSYS_SYNCI()                       __memory_changed(); __SYNCI(); __memory_changed()
  #else
    // stub for simulation, todo: provide C implementation of intrinsic, see WI 2243461
    #define RBSYS_SYNCI()
  #endif




  /**
  * @brief Load Linked
  *
  * Load to start atomic word data manipulation.
  *
  * Mutual Exclusion: REL recommended to execute exclusive control by using the
  * LDL/STC instructions. This means in case of multi-core systems requiring an
  * atomic guarantee, LDL.W and STC.W instructions are used.
  *
  * For details see RH850G3M/RH850G3K Software Manual
  *
  * Hint: consider guidlines at the top of this file
  * Hint: some intrinsics do not generate sequence points, see https://inside-docupedia.bosch.com/confluence/display/BBMCOM/Ordering+and+optimization+for+intrinsics%2C+asm+statements+and+volatile+variables
  *       consider adding __memory_changed() calls around this intrinsic
  */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #if (RBFS_Compiler == RBFS_Compiler_GHS2021)
      //latest GHS compiler supports volatile qualifier
      #define RBSYS_LDL_W(p)                      __LDL_Wv(p)
    #elif( (RBFS_Compiler == RBFS_Compiler_GHS) || (RBFS_Compiler == RBFS_Compiler_GHS2018) )
      #define RBSYS_LDL_W(p)                      __LDL_W(p)
    #endif
  #else
    // stub for simulation, todo: provide C implementation of intrinsic, see WI 2243461
    #define RBSYS_LDL_W(p)
  #endif


  /**
  * @brief Store Conditional
  *
  * Conditional storage when atomic word data manipulation is complete.
  * For details see RH850G3M/RH850G3K Software Manual
  *
  * Hint: consider guidlines at the top of this file
  * Hint: some intrinsics do not generate sequence points, see https://inside-docupedia.bosch.com/confluence/display/BBMCOM/Ordering+and+optimization+for+intrinsics%2C+asm+statements+and+volatile+variables
  *       consider adding __memory_changed() calls around this intrinsic
  */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #if(RBFS_Compiler == RBFS_Compiler_GHS2021)
      //latest GHS compiler supports volatile qualifier
      #define RBSYS_STC_W(d, p)                   __STC_Wv(d, p)
    #elif( (RBFS_Compiler == RBFS_Compiler_GHS) || (RBFS_Compiler == RBFS_Compiler_GHS2018) )
      #define RBSYS_STC_W(d, p)                   __STC_W(d, p)
    #endif
  #else
    // stub for simulation, todo: provide C implementation of intrinsic, see WI 2243461
    #define RBSYS_STC_W(d, p) (0xABCDEF55u)
  #endif


  // The following define is needed because old GHS compiler versions do not support volatile qualifier in above intrinsics, see task 726910
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #if(RBFS_Compiler == RBFS_Compiler_GHS2021)
      // no type cast required
      #define RBSYS_CAST2LDLSTC_TYPE(var) (var)
    #elif( (RBFS_Compiler == RBFS_Compiler_GHS) || (RBFS_Compiler == RBFS_Compiler_GHS2018) )
      #define RBSYS_CAST2LDLSTC_TYPE(var) ((int *) (var))
    #endif
  #else
    // no type cast required for simulation
    #define RBSYS_CAST2LDLSTC_TYPE(var) (var)
  #endif


  /**
  * @brief Bit manipulation instruction "clear bit"
  *
  * Bit manipulation instructions like (set1, clr1, not1, ...) are not allowed to be used
  * for RAM variables, because they are not traceable due to HW restrictions (see UM).
  *
  * @note The compiler setting "-no_rh850_1bit" prevents the compiler from using these instructions.
  *
  * @param [out] addr only for special peripheral registers where clr1 is supported by HW (see spec)
  * @param [in]  bitnum works only on bytes; i.e. bitnum must be 0..7
  *
  * @return void
  */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #define RBSYS_CLR1(addr,bitnum)         __memory_changed(); __CLR1(addr,bitnum); __memory_changed()
  #else
    // stub for simulation, will be moved to CBaseLib, see WI 2243401
    #define RBSYS_CLR1(addr,bitnum)
  #endif


  /**
  * @brief Bit manipulation instruction "set bit"
  *
  * Bit manipulation instructions like (set1, clr1, not1, ...) are not allowed to be used
  * for RAM variables, because they are not traceable due to HW restrictions (see UM).
  *
  * @note The compiler setting "-no_rh850_1bit" prevents the compiler from using these instructions.
  *
  * @param [out] addr only for special peripheral registers where set1 is supported by HW (see spec)
  * @param [in]  bitnum works only on bytes; i.e. bitnum must be 0..7
  *
  * @return void
  */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #define RBSYS_SET1(addr, bitnum)        __memory_changed(); __SET1(addr, bitnum); __memory_changed()
  #else
    // stub for simulation, will be moved to CBaseLib, see WI 2243401
    #define RBSYS_SET1(addr, bitnum)
  #endif




  /**
  * @brief RBSYS_getPositionOfFirstBitValue1
  *
  * Examples:
  *    value 0x80000000 returns 32
  *    value 0xFFFFFFFE returns 2
  *
  * GHS compiler instrinsics __SCH1R used to have the interface int __SCH1R(int) until 2013.
  * Afterwards, it's defined as unsigned int __SCH1R(unsigned int).
  * We don't support GHS compiler 2013 anymore.
  *
  * @param [in] value  32-bit unsigned integer argument for searching corresponding bit position
  *
  * @returns the position of the first 1 encountered in parameter "value" when searching from
  * right-to-left. If no 1 is found, 0 is returned. If the first bit examined matches,
  * then 1 is returned, with 2 returned for the second bit, and so forth.
  */
  static inline uint32 RBSYS_getPositionOfFirstBitValue1(uint32 value)
  {
    #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
      uint32 ret;
      __memory_changed();
      ret = __SCH1R(value);
      __memory_changed();
      return ret;
    #else
      // stub for simulation, will be moved to CBaseLib, see WI 2243401
      int pos = 0;
      if(value != 0)
      {
        pos = 1; // Bit 0 => position 1

        while((value & 1) == 0)
        {
          value >>= 1;
          pos++;
        }
      }
      return pos;
    #endif
  }
#elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)

  /* used interfaces */
  #if(RBFS_Compiler == RBFS_Compiler_GHS2021)
    #include <arm_ghs.h>
    #include <ghs_barrier.h>
  #endif


  /**
   * @brief Move to general-purpose register from System register
   *
   * System Registers can only be read by using the MRC instruction.
   *
   * Hint: consider guidelines at the top of this file
   * Hint: some intrinsics do not generate sequence points, see https://inside-docupedia.bosch.com/confluence/display/BBMCOM/Ordering+and+optimization+for+intrinsics%2C+asm+statements+and+volatile+variables
   *       consider adding __memory_changed() calls around this intrinsic
   *
   * @param coproc    System register encoding space, can only have the values 14 and 15
   * @param opcode1   opc1 within the system register encoding space
   * @param CRn       CRn within the system register encoding space
   * @param CRm       CRm within the system register encoding space
   * @param opcode2   opc2 within the system register encoding space
   *
   * @returns the system register content
   */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #define RBSYS_MRC(coproc, opcode1, CRn, CRm, opcode2)            __MRC(coproc, opcode1, CRn, CRm, opcode2)
    #define RBSYS_MRRC(coproc, opcode, CRm)                          __MRRC(coproc, opcode, CRm)
  #else
    // stub for simulation, todo: provide C implementation of intrinsic, see WI 2243461
    #define RBSYS_MRC(coproc, opcode1, CRn, CRm, opcode2)            (0xABCDEF55u)
    #define RBSYS_MRRC(coproc, opcode, CRm)                          (0xABCDEF0123456789u)
  #endif


  /**
   * @brief Move to System register from general-purpose register or execute a System instruction
   *
   * System Registers can only be written by using the MCR instruction.
   *
   * Hint: consider guidelines at the top of this file
   *
   * @param coproc    System register encoding space, can only have the values 14 and 15
   * @param opcode1   opc1 within the system register encoding space
   * @param val       System register value
   * @param CRn       CRn within the system register encoding space
   * @param CRm       CRm within the system register encoding space
   * @param opcode2   opc2 within the system register encoding space
   *
   * @return void
   */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #define RBSYS_MCR(coproc, opcode1, val, CRn, CRm, opcode2)       __memory_changed(); __MCR(coproc, opcode1, val, CRn, CRm, opcode2); __memory_changed()
    #define RBSYS_MCRR(coproc, opcode, val64, CRm)                   __memory_changed(); __MCRR(coproc, opcode, val64, CRm); __memory_changed()
  #else
    // stub for simulation, todo: provide C implementation of intrinsic, see WI 2243461
    #define RBSYS_MCR(coproc, opcode1, val, CRn, CRm, opcode2)
    #define RBSYS_MCRR(coproc, opcode, val64, CRm)
  #endif


  /**
   * @brief Move the value of an Advanced SIMD and floating-point System register to a general-purpose register
   *
   * Advanced SIMD and floating-point System register can only be read by using the VMRS instruction.
   *
   * Hint: consider guidelines at the top of this file
   * Hint: some intrinsics do not generate sequence points, see https://inside-docupedia.bosch.com/confluence/display/BBMCOM/Ordering+and+optimization+for+intrinsics%2C+asm+statements+and+volatile+variables
   *       consider adding __memory_changed() calls around this intrinsic
   *
   * @param regnum    Advanced SIMD and floating-point System register number. Details see ARMv8 Architecture Reference Manual
   *
   * @returns the register content
   */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #define RBSYS_VMRS(regnum)       __VMRS(regnum)
  #else
    // stub for simulation, todo: provide C implementation of intrinsic, see WI 2243461
    #define RBSYS_VMRS(regnum)       (0xABCDEF55u)
  #endif

  /**
   * @brief Move the value of a general-purpose register to a floating-point System register
   *
   * Advanced SIMD and floating-point System register can only be written by using the VMSR instruction.
   *
   * Hint: consider guidelines at the top of this file
   *
   * @param regnum    Advanced SIMD and floating-point System register number. Details see ARMv8 Architecture Reference Manual
   * @param val       value to write
   *
   * @return void
   */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #define RBSYS_VMSR(regnum, val)       __memory_changed(); __VMSR(regnum, val); __memory_changed()
  #else
    // stub for simulation, todo: provide C implementation of intrinsic, see WI 2243461
    #define RBSYS_VMSR(regnum, val)
  #endif

  /* temporary stub: */
  #define RBSYS_SYNCM() __memory_changed(); __DSB(); __memory_changed()


  /**
   * @brief Trigger a Hypervisor Call exception
   *
   * Non-secure software executing at EL1 can use this instruction to call the hypervisor to request a service.
   * On executing an HVC instruction, the HSR reports the exception as a Hypervisor Call exception, using the EC value 0x12, and captures the value of the immediate argument.
   *
   * @param code    16 bit integer which is passed to the hypervisor call via HSR
   *
   * @return void
   */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #define RBSYS_HVC(code)       __memory_changed(); __HVC(code); __memory_changed()
  #else
    // stub for simulation, todo: provide C implementation of intrinsic, see WI 2243461
    #define RBSYS_HVC(code)
  #endif


#endif

/**
* @brief Disable interrupt
*
* Disable EI level maskable exception => not safe for Multi-Core systems
*/
#if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
  #define RBSYS_DI()                          __memory_changed(); __DI(); __memory_changed()
#else
  // stub for simulation, todo: provide C implementation of intrinsic, see WI 2243461
  #define RBSYS_DI()
#endif


/**
* @brief Enable interrupt
*
* Enable EI level maskable exception => not safe for Multi-Core systems
*/
#if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
  #define RBSYS_EI()                          __memory_changed(); __EI(); __memory_changed()
#else
  // stub for simulation, todo: provide C implementation of intrinsic, see WI 2243461
  #define RBSYS_EI()
#endif

/**
* @brief Memory Barrier Optimization Intrinsics
*
* Adds a barrier that forces all loads, stores and low-level operations sequenced before the barrier
* to occur in instruction execution order before the barrier. And all loads, stores and low-level
* operations sequenced after the barrier to occur in instruction execution order after the barrier.
*
* So it informs the compiler that memory must be treated as if it has changed. This prevents any
* assumptions that the value of memory after the intrinsic will be the same as it was before the intrinsic.
*
* Referenced wiki sites:
* - <a href="https://connect.bosch.com/wikis/home?lang=de-de#!/wiki/Wd57076c137e9_40c5_be40_2960a6b1391b/page/
* Reordering%20of%20intrinsics%20and%20asm%20statements">Reordering of intrinsics and asm statements</a>\n
* - <a href="https://connect.bosch.com/wikis/home?lang=en-us#!/wiki/Wd57076c137e9_40c5_be40_2960a6b1391b/page/
* Inline%20Assembler%20Code%20as%20Optimization%20Blocker">Inline Assembler Code as Optimization Blocker </a>
*/
#if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
  #define RBSYS_memory_changed()             __memory_changed()
#else
  // stub for simulation, will be moved to CBaseLib, see WI 2243401
  #define RBSYS_memory_changed()
#endif

/**
* @brief Get Link Pointer
*
* Hint: some intrinsics do not generate sequence points, see https://inside-docupedia.bosch.com/confluence/display/BBMCOM/Ordering+and+optimization+for+intrinsics%2C+asm+statements+and+volatile+variables
*       consider adding __memory_changed() calls around this intrinsic
*
* @note This function cannot be used in interrupt procedures.
*
* @returns the return-address of the current function (Link Pointer).
*/
#define RBSYS_getLinkPointer()      __builtin_return_address(0)

/**
* @brief RBSYS_snooze
*
* Renesas:
*   The snooze instruction (SNOOZE) is available for temporary suspension by switching the CPU clock signal
*   off for 32 clock cycles. U2A/U2C: The number of halted CPU clocks can be configured via SNZCFG register.
* STM Stellar:
*   Custom implementation to wait 32 clock cycles without causing bus/RAM load.
*
* Therefore it could be used to prevent excessive bus bandwidth possession (e.g. during a spinlock wait).
*
* @return void
*/
__attribute__((always_inline)) static inline void RBSYS_snooze(void)
{
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
      || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
      || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      __memory_changed();
      __SNOOZE();
      __memory_changed();
    #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      asm("mov r0, r0");
      /* todo: find better solution for Stellar */
    #endif
  #endif
}

  /**
* @brief Snooze loop
*
* This function could avoid bus congestion on MultiCore systems while executing several SNOOZE instructions consecutively.
* @note volatile int i is either placed on core local stack or held in register (allowed according GHS spec) => no bus congestion in any case
*
* @param [in] rounds is the number of consecutive SNOOZE instructions
*
* @return void
*/
#define RBSYS_SNOOZE_LOOP(rounds)   \
  {                                 \
    volatile int i;                 \
    for (i=0; i<(rounds); i++) {    \
      RBSYS_snooze();               \
    }                               \
}

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  #define RBSYS_DSB()              __memory_changed(); __DSB(); __memory_changed()
  #define RBSYS_ISB()              __memory_changed(); __ISB(); __memory_changed()

  /* Hint: some intrinsics do not generate sequence points, see https://inside-docupedia.bosch.com/confluence/display/BBMCOM/Ordering+and+optimization+for+intrinsics%2C+asm+statements+and+volatile+variables
    *       consider adding __memory_changed() calls around this intrinsic */
  #define RBSYS_LDREX(addr)        __LDREX(addr)

  /* Hint: some intrinsics do not generate sequence points, see https://inside-docupedia.bosch.com/confluence/display/BBMCOM/Ordering+and+optimization+for+intrinsics%2C+asm+statements+and+volatile+variables
    *       consider adding __memory_changed() calls around this intrinsic */
  #define RBSYS_STREX(value, addr) __STREX(value, addr)

  #define RBSYS_CLREX()            __memory_changed(); __CLREX(); __memory_changed()
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
