#ifndef RBSYS_COREINIT_H__
#define RBSYS_COREINIT_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Core specific initialization
 *
 * This interface provides special core initialization routines and could be used by bootblock as
 * well as in application software.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_Intrinsics.h"
#include "RBSYS_CpuInfo.h"
#include "RBSYS_uCRegisters.h"
#include <assert.h>
#include "RBSYS_CoreMpu.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_SysOverwriteEBASE,
                          RBFS_SysOverwriteEBASE_ON,
                          RBFS_SysOverwriteEBASE_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_ON,
                          RBFS_MCORE_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TargetDevice,
                          RBFS_TargetDevice_RenesasD1,
                          RBFS_TargetDevice_RenesasD2,
                          RBFS_TargetDevice_RenesasD3,
                          RBFS_TargetDevice_RenesasD4,
                          RBFS_TargetDevice_RenesasD5,
                          RBFS_TargetDevice_RenesasD7,
                          RBFS_TargetDevice_RenesasM2,
                          RBFS_TargetDevice_RenesasM3,
                          RBFS_TargetDevice_RenesasM6,
                          RBFS_TargetDevice_RenesasK0,
                          RBFS_TargetDevice_RenesasK1,
                          RBFS_TargetDevice_STMP6);

RB_ASSERT_SWITCH_SETTINGS(RBFS_EmulationDevice,
                          RBFS_EmulationDevice_None,
                          RBFS_EmulationDevice_RenesasD3ED,
                          RBFS_EmulationDevice_RenesasD5ED,
                          RBFS_EmulationDevice_RenesasD7ED,
                          RBFS_EmulationDevice_RenesasM6ED,
                          RBFS_EmulationDevice_RenesasK3ED,
                          RBFS_EmulationDevice_STMP7ED);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasP1xGRAM,
                          RBFS_RenesasP1xGRAM_ON,
                          RBFS_RenesasP1xGRAM_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasU2aCRAM0,
                          RBFS_RenesasU2aCRAM0_ON,
                          RBFS_RenesasU2aCRAM0_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasU2aCRAM1,
                          RBFS_RenesasU2aCRAM1_ON,
                          RBFS_RenesasU2aCRAM1_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasU2aCRAM2,
                          RBFS_RenesasU2aCRAM2_ON,
                          RBFS_RenesasU2aCRAM2_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasU2aCRAM3,
                          RBFS_RenesasU2aCRAM3_ON,
                          RBFS_RenesasU2aCRAM3_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_DataFlashECC,
                          RBFS_DataFlashECC_Disabled,
                          RBFS_DataFlashECC_Enabled);

RB_ASSERT_SWITCH_SETTINGS(RBFS_CPUMisalignedAccessSupport,
                          RBFS_CPUMisalignedAccessSupport_ON,
                          RBFS_CPUMisalignedAccessSupport_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

RB_ASSERT_SWITCH_SETTINGS(RBFS_CyberSecurityBoot,
                          RBFS_CyberSecurityBoot_NonTrusted,
                          RBFS_CyberSecurityBoot_Trusted,
                          RBFS_CyberSecurityBoot_Gracious,
                          RBFS_CyberSecurityBoot_Staged,
                          RBFS_CyberSecurityBoot_Concurrent,
                          RBFS_CyberSecurityBoot_Secure);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEnvironment,
                            RBFS_SysEnvironment_Target,
                            RBFS_SysEnvironment_Simulation);



#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  // core specific system register 11, 2 - PMR (interrupt priority masking)
  #define RBSYS_PMR_REGID      11
  #define RBSYS_PMR_SELID      2
#endif

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  // core specific system register 14, 2 - PLMR (interrupt priority level mask)
  #define RBSYS_PLMR_REGID      14
  #define RBSYS_PLMR_SELID      2
#endif

// core specific system register 5, 0 - PSW (program status word)
#define RBSYS_PSW_REGID      5
#define RBSYS_PSW_SELID      0
#define RBSYS_PSW_ID_MASK    (1u<<5)

// core specific system register 3, 1 - EBASE (exception handler vector base address)
#define RBSYS_EBASE_REGID    3
#define RBSYS_EBASE_SELID    1

// core specific system register 5, 1 - MCTL (CPU control)
#define RBSYS_MCTL_REGID     5
#define RBSYS_MCTL_SELID     1

// core specific system register 13, 0 - EIIC (EI level exception cause)
#define RBSYS_EIIC_REGID     13
#define RBSYS_EIIC_SELID     0

// core specific system register 14, 0 - FEIC (FE level exception cause)
#define RBSYS_FEIC_REGID     14
#define RBSYS_FEIC_SELID     0


/**
 * @brief Clear EIIC register
 *
 * Clears EI level exception register which indicates the last EI level exception cause.
 * This is for example used after handling a TPSW exception to not pollute debug data of other failures.
 */
#define RBSYS_ClearEIIC() RBSYS_LDSR(RBSYS_EIIC_REGID, RBSYS_EIIC_SELID, 0)

/**
 * @brief Clear FEIC register
 *
 * Clears FE level exception register which indicates the last FE level exception cause.
 * This is for example used after handling a TPSW exception to not pollute debug data of other failures.
 */
#define RBSYS_ClearFEIC() RBSYS_LDSR(RBSYS_FEIC_REGID, RBSYS_FEIC_SELID, 0)


/* -------------------------------------------------------------------------- */
/* QAC|DEV 0009: In-line assembly embedded in normal C code                   */
/* -------------------------------------------------------------------------- */
/* Msg 1006: In-line assembler construct is a language extension.             */
/* -------------------------------------------------------------------------- */
#ifdef __QAC__
  #pragma PRQA_MESSAGES_OFF 1006
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  #define C0_CPU0_tcma_start (0x68000000)
  #define C0_CPU0_tcma_size  (64*1024)
  #define C0_CPU0_tcmb_start (0x68100000)
  #define C0_CPU0_tcmb_size  (16*1024)
  #define C0_CPU0_tcmc_start (0x68200000)
  #define C0_CPU0_tcmc_size  (16*1024)

  #define C0_CPU1_tcma_start (0x68400000)
  #define C0_CPU1_tcma_size  (64*1024)
  #define C0_CPU1_tcmb_start (0x68500000)
  #define C0_CPU1_tcmb_size  (16*1024)
  #define C0_CPU1_tcmc_start (0x68600000)
  #define C0_CPU1_tcmc_size  (16*1024)

  /* Stellar X7 actually has more CRAM than defined below, but we only want to use what is available on Stellar P6 */
  #define CRAM0_0_start      (0x60000000)
  #define CRAM0_0_size       (256*1024)
  #define BURAM_start        (0x60400000)
  #define BURAM_size         (1*1024)
  #define CRAM0_1_start      (0x60400400) /* 1K BURAM at start of CRAM_0_1 */
  #define CRAM0_1_size       (255*1024)   /* 256K - 1K BURAM */

  #define CRAM1_0_start      (0x60800000)
  #define CRAM1_0_size       (128*1024)
  #define CRAM1_1_start      (0x60C00000)
  #define CRAM1_1_size       (128*1024)

  #define CRAM2_0_start      (0x61000000)
  #define CRAM2_0_size       (128*1024)
  #define CRAM2_1_start      (0x61400000)
  #define CRAM2_1_size       (128*1024)


  #define SYSRAM0_start      (0x64000000)
  #define SYSRAM0_size       (128*1024)
  #define SYSRAM1_start      (0x64400000)
  #define SYSRAM1_size       (128*1024)
#endif


/**
 * @brief CPU register initialization
 *
 * This register initialization is required for dual cores running in lockstep mode.
 * The registers are during device start-up in an undefined state and reading of
 * uninitialized registers could result in an dual core compare failure.
 *
 * @note Sequence based on HW UM Rev.1.00: "D3_D4_D5_D5EDv2_r01uh0490ej0100_rh850p1x-c_bosch.pdf"
 *
 * @return void
 */
#if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    static void RBSYS_registerInit(void);
    asm void RBSYS_registerInit(void)
    {
      -- Initialize CPU register to avoid Compare Unit Mismatch Error
      -- This code must be executed in supervisor mode (PSW.UM = 0)
      mov r0, r1
      mov r0, r2
      mov r0, r3
      mov r0, r4
      mov r0, r5
      mov r0, r6
      mov r0, r7
      mov r0, r8
      mov r0, r9
      mov r0, r10
      mov r0, r11
      mov r0, r12
      mov r0, r13
      mov r0, r14
      mov r0, r15
      mov r0, r16
      mov r0, r17
      mov r0, r18
      mov r0, r19
      mov r0, r20
      mov r0, r21
      mov r0, r22
      mov r0, r23
      mov r0, r24
      mov r0, r25
      mov r0, r26
      mov r0, r27
      mov r0, r28
      mov r0, r29
      mov r0, r30
      mov r0, r31

      -- CPU function group system register set
      ldsr r0, EIPC
      ldsr r0, FEPC
      ldsr r0, CTPC
      ldsr r0, CTBP         -- CALLT Base Pointer: Not required as CALLT is not being used - kept for consistency

      #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
        ldsr r0, ASID,2     -- This is not mandatory for U2A/U2C
      #endif

      ldsr r0, EIWR
      ldsr r0, FEWR
      ldsr r0, MEA,2
      ldsr r0, MEI,2
      ldsr r0, EBASE,1
      ldsr r0, INTBP,1

      ldsr r0, SCCFG,1      -- SYSCALL Operation Setting: Not required as SYSCALL is not being used - kept for consistency
      ldsr r0, SCBP,1       -- SYSCALL Base Pointer: Not required as SYSCALL is not being used - kept for consistency

      #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        ldsr r0, RBIP, 2
      #endif

      -- Reserved registers for virtual machine functions (see 2258170: [HSW] HSW support for hypervisor concept)
      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
        -- Initialization is required (even if HV is unused)
        ldsr r0, 10, 1      -- regID SR10 (former TCSEL)
        ldsr r0, 15, 1      -- regID SR15 (former VCSEL)
        ldsr r0, 13, 1      -- regID SR13 (former HVCCFG)
        ldsr r0, 14, 1      -- regID SR14 (former HVCB)
      #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        -- Feedback REL: As long as HV is not being used, registers dont have to be initialized
      #endif

      -- FPU registers
      mov 0x00010020,r1
      ldsr r1, PSW          -- enable temporary FPU to initialize FPU registers
      mov 0x00020000,r1
      ldsr r1, FPSR
      ldsr r0, FPEPC
      ldsr r0, FPST
      ldsr r0, FPCC
      mov 0x00000020,r1
      ldsr r1, PSW          -- disable FPU again (handling of HW FPU is done within RBSYS_InitFPU)

      -- SIMD registers (not implemented)

      -- MMU registers (not implemented)

      -- MPU function registers
      ldsr r0, MCA, 5
      ldsr r0, MCS, 5
      ldsr r0, MCR, 5

      #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
        ldsr r0, MPLA0, 6
        ldsr r0, MPUA0, 6
        ldsr r0, MPAT0, 6
        ldsr r0, MPLA1, 6
        ldsr r0, MPUA1, 6
        ldsr r0, MPAT1, 6
        ldsr r0, MPLA2, 6
        ldsr r0, MPUA2, 6
        ldsr r0, MPAT2, 6
        ldsr r0, MPLA3, 6
        ldsr r0, MPUA3, 6
        ldsr r0, MPAT3, 6
        ldsr r0, MPLA4, 6
        ldsr r0, MPUA4, 6
        ldsr r0, MPAT4, 6
        ldsr r0, MPLA5, 6
        ldsr r0, MPUA5, 6
        ldsr r0, MPAT5, 6
        ldsr r0, MPLA6, 6
        ldsr r0, MPUA6, 6
        ldsr r0, MPAT6, 6
        ldsr r0, MPLA7, 6
        ldsr r0, MPUA7, 6
        ldsr r0, MPAT7, 6
        ldsr r0, MPLA8, 7
        ldsr r0, MPUA8, 7
        ldsr r0, MPAT8, 7
        ldsr r0, MPLA9, 7
        ldsr r0, MPUA9, 7
        ldsr r0, MPAT9, 7
        ldsr r0, MPLA10, 7
        ldsr r0, MPUA10, 7
        ldsr r0, MPAT10, 7
        ldsr r0, MPLA11, 7
        ldsr r0, MPUA11, 7
        ldsr r0, MPAT11, 7
        ldsr r0, MPLA12, 7
        ldsr r0, MPUA12, 7
        ldsr r0, MPAT12, 7
        ldsr r0, MPLA13, 7
        ldsr r0, MPUA13, 7
        ldsr r0, MPAT13, 7
        ldsr r0, MPLA14, 7
        ldsr r0, MPUA14, 7
        ldsr r0, MPAT14, 7
        ldsr r0, MPLA15, 7
        ldsr r0, MPUA15, 7
        ldsr r0, MPAT15, 7
      #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
        mov 0x00000000, r1  -- start index
        #if(RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
          mov 0x00000020, r12 -- number of MP reg sets = 32
        #elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)
          mov 0x00000018, r12 -- number of MP reg sets = 24
        #endif

        loop:
          ldsr r1, MPIDX, 5   -- set accessed MP reg set
          ldsr r0, MPLA, 5    -- MPLA[r1] = 0
          ldsr r0, MPUA, 5    -- MPUA[r1] = 0
          ldsr r0, MPAT, 5    -- MPAT[r1] = 0
          add  0x00000001, r1 -- r1++
          cmp  r1, r12        -- r1 != end
          bne  loop

        mov r0, r12 -- reset r12 to 0

        ldsr r0, MPID0, 5
        ldsr r0, MPID1, 5
        ldsr r0, MPID2, 5
        ldsr r0, MPID3, 5
        ldsr r0, MPID4, 5
        ldsr r0, MPID5, 5
        ldsr r0, MPID6, 5
        ldsr r0, MPID7, 5

        ldsr r0, MCI, 5
      #endif

      -- Cache operation function registers (instruction cache is not available on D1 and D2)
      #if(!(                                                                                                               \
              ((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) && (RBFS_EmulationDevice == RBFS_EmulationDevice_None))  \
          || ((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2) && (RBFS_EmulationDevice == RBFS_EmulationDevice_None))  \
          ))
        ldsr r0, ICTAGL, 4
        ldsr r0, ICTAGH, 4
        ldsr r0, ICDATL, 4
        ldsr r0, ICDATH, 4
        -- ldsr r0, DCTAGL, 4 -- not implemented
        -- ldsr r0, DCTAGH, 4 -- not implemented
        -- ldsr r0, DCDATL, 4 -- not implemented
        -- ldsr r0, DCDATH, 4 -- not implemented
        ldsr r0, ICERR, 4
        -- ldsr r0, DCERR, 4  -- not implemented
        -- ldsr r0, BWERRL, 4 -- not implemented
        -- ldsr r0, BWERRH, 4 -- not implemented
        -- ldsr r0, BRERRL, 4 -- not implemented
        -- ldsr r0, BRERRH, 4 -- not implemented
      #endif

      #if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
        -- Stop Watchdog in case of debugger break event (RB196)
        mov EPC_SVSTOP58_ADDR, ep
        sst.w r0, 0[ep]
        -- todo: U2C support?
      #endif
    }

  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

    static void RBSYS_registerInit(void);
    asm void RBSYS_registerInit(void)
    {
%lab end %lab way_loop %lab set_loop %lab dcisw_and_while
      ; Initialize CPU Registers
      mov r0,  0
      mov r1,  0
      mov r2,  0
      mov r3,  0
      mov r4,  0
      mov r5,  0
      mov r6,  0
      mov r7,  0
      mov r8,  0
      mov r9,  0
      mov r10, 0
      mov r11, 0
      mov r12, 0
      mov r13, 0

      ; *********************************************************************************************
      ; * Configuration of memory protection unit (MPU)                                             *
      ; *********************************************************************************************

      ; MAIR0 = HMAIR0 = RBSYS_CoreMPU_MAIR0
      movw    r0, %lo(RBSYS_CoreMPU_MAIR0) ; Attribute Indexes see RBSYS_CoreMpu.h
      movt    r0, %hi(RBSYS_CoreMPU_MAIR0)
      mcr     p15, 0, r0, c10, c2, 0 ; MAIR0 Memory Attribute Indirection Reg 0
      mcr     p15, 4, r0, c10, c2, 0 ; HMAIR0 Hypv Mem Attribute Indirection Reg 0

      ; *********************************************************************************************
      ; * disable MPU as it might be activated in BCS code from ST (formerly known as BAF)          *
      ; *********************************************************************************************
      ; disable MPU
      mrc     p15, 4, r0, c1, c0, 0   ; HSCTLR
      bic     r0, r0, 0x1             ; disable MPU
      mcr     p15, 4, r0, c1, c0, 0   ; HSCTLR
      dsb
      isb

      ; disable region 0..6 in EL-2 MPU -> todo 0..6????
      mov     r0, 0x0                 ; disable all EL2 MPU regions
      mcr     p15, 4, r0, c6, c1, 1   ; HPRENR Hypv Protect. Region Enable Reg.

      ; *********************************************************************************************
      ; * configure MPU regions                                                                     *
      ; *********************************************************************************************
      ; Todo: Optimization possibility: Invalidate + Enable Instruction$ before configuring the MPU Regions (Background-
      ;       Region could be used in the meantime)

      ; initialize MPU region loop index and pointer into RBSYS_MpuRegionConfig table, see RBSYS_CoreMpu.c
      mov     r0, 0x0
      movw    r1, %lo(RBSYS_MpuRegionConfigSize)
      movt    r1, %hi(RBSYS_MpuRegionConfigSize)
      ldr.w   r1, [r1]
      movw    r2, %lo(RBSYS_MpuRegionConfig)
      movt    r2, %hi(RBSYS_MpuRegionConfig)
mpu_regions_loop:
      cmp     r0, r1                    ; i >= RBSYS_MpuRegionConfigSize
      bhs     mpu_regions_done          ; if above is true jump out of loop
      ldm.w   r2!, {r3, r4, r5, r6, r7} ; load RBSYS_MpuRegionConfig[i] members and increment RBSYS_MpuRegionConfig pointer

      ; set mpu region index
      mcr     p15, 4, r0, c6, c2, 1     ; HPRSELR
      mcr     p15, 0, r0, c6, c2, 1     ; PRSELR

      ; set base address and properties
      bic.w   r3, r3, 0x3F              ; r3  = RBSYS_MpuRegionConfig[i].start  & 0xFFFFFFC0
      orr.w   r3, r3, r6                ; r3 |= RBSYS_MpuRegionConfig[i].memoryType1
      mcr     p15, 4, r3, c6, c3, 0     ; HPRBAR
      mcr     p15, 0, r3, c6, c3, 0     ; PRBAR

      ; set limit address, attribute index and enable
      bic.w   r5, r5, 0x3F              ; r5  = RBSYS_MpuRegionConfig[i].end  & 0xFFFFFFC0
      orr.w   r5, r5, r7                ; r5 |= RBSYS_MpuRegionConfig[i].memoryType2
      orr.w   r5, 1                     ; r5 |= 1
      mcr     p15, 4, r5, c6, c3, 1     ; HPRLAR
      mcr     p15, 0, r5, c6, c3, 1     ; PRLAR

      ; increment loop index
      add     r0, 1
      b mpu_regions_loop
mpu_regions_done:

      ; todo: Do we activate DCache for DFlash?

      ; *********************************************************************************************
      ; * reenable MPU                                                                              *
      ; *********************************************************************************************

      ; enable EL2-MPU
      mrc     p15, 4, r0, c1, c0, 0   ; HSCTLR
      orr     r0, r0, 0x1             ; enable EL2-MPU
      orr     r0, r0, 0x2             ; enable alignment check for EL2
      dsb
      mcr     p15, 4, r0, c1, c0, 0   ; HSCTLR
      isb

      ; enable EL1-MPU
      mrc     p15, 0, r0, c1, c0, 0   ; SCTLR
      orr     r0, r0, 0x1             ; enable EL1-MPU
      orr     r0, r0, 0x2             ; enable alignment check for EL1/0
      dsb
      mcr     p15, 0, r0, c1, c0, 0   ; SCTLR
      isb

      ; *********************************************************************************************
      ; * Enable and invalidate cache                                                               *
      ; *********************************************************************************************

      ; *********************************************************************************************
      ; * Configure Cache way
      ; *********************************************************************************************
      mrc     p15, 1, r1, c9, c1, 0
      orr     r1, r1, (0x4)          ; D-$, 0 ways AXI_M (RW), 4 ways Flash (RO)
      orr     r1, r1, (0x4 << 8)     ; I-$, all 4 ways on Flash
      mcr     p15, 1, r1, c9, c1, 0

      ; *********************************************************************************************
      ; * Invalidate Icache
      ; *********************************************************************************************
      mcr     p15,0,r0,c7,c5,0        ; ICIALLU operation, invalidate I$ (ignores the value in r0)

      ; *********************************************************************************************
      ; * Invalidate Dcache
      ; *   Invalidate: invalidate currently cached data and do not write back
      ; *   Clean:      write back dirty data (dirty data = cached write commands), clear dirty flags
      ; *********************************************************************************************
      ;
      ; NOTE: For a detailed description, see function RBSYS_invalidateDataCache!
      ;
      MOV r0, 0
      MCR p15, 2, r0, c0, c0, 0     ; Select Data Cache Size Register (CCSELR = 0)
      MRC p15, 1, r0, c0, c0, 0     ; Read Cache Size ID (CCSIDR)
      ; Bit [13:27] => Number of sets
      ; Bit [3:12]  => Associativity
      ; Bit [0:2]   => LineSize
      MOV r3, 0x7fff
      AND r0, r3, r0, LSR 13        ; r0 = no. of sets - 1
      ADD r0, r0, 1                 ; r0 = no. of sets
      MOV r1, 0                     ; r1 = way_counter way_loop
way_loop:
      MOV r3, 0                     ; r3 = set_counter set_loop
set_loop:
      MOV r2, r1, LSL 30            ; r2  = (way_counter << 30)
      ORR r2, r3, LSL 6             ; r2 |= (set_counter << 6)   -> set/way cache operation format
dcisw_and_while:
      MCR p15, 0, r2, c7, c6, 2     ; DCISW command              (Invalidate line described by r2)
      ADD r3, r3, 1                 ; r3 += 1                    (Increment set counter)
      CMP r0, r3                    ;                            (Last set reached yet?)
      BNE set_loop                  ; r3 == r0 ? continue : loop (if not, iterate set_loop)
      ADD r1, r1, 1                 ; r1 += 1                    (Increment way counter)
      CMP r1, 4                     ;                            (Last way reached yet?)
      BNE way_loop                  ; r1 == 4 ? continue : loop  (if not, iterate way_loop)

      ; *********************************************************************************************
      ; * Enable caches in privileged mode(EL2)
      ; *********************************************************************************************
      mrc     p15, 4, r1, c1, c0, 0     ; HSCTLR
      orr     r1, r1, (0x1 << 2)       ; C bit (data cache)
      orr     r1, r1, (0x1 << 12)      ; I bit (instruction cache)
      mcr     p15, 4, r1, c1, c0, 0
      ; *********************************************************************************************
      ; * Enable caches in privileged mode(EL1/0)
      ; *********************************************************************************************
      mrc     p15, 0, r1, c1, c0, 0    ; SCTLR
      orr     r1, r1, (0x1 << 2)       ; C bit (data cache)
      orr     r1, r1, (0x1 << 12)      ; I bit (instruction cache)
      mcr     p15, 0, r1, c1, c0, 0

      ; Set core id via VMPIDR
      ; todo: special handling needed for P5
      mrc  p15, 4, r0, c0, c0, 5   ; Read VMPIDR
      and  r1, r0, 0xff            ; coreIdInCluster = vmpidr & 0xFFu
      ubfx r2, r0, 8, 8            ; clusterId = (vmpidr >> 8) & 0xFFu
      add  r1, r1, r2, LSL 1       ; coreId = coreIdInCluster + (clusterId * 2)
      and  r0, 0xff000000          ; vmpidr &= 0xFF000000u
      orr  r0, r1                  ; vmpidr |= coreId
      mcr  p15, 4, r0, c0, c0, 5   ; Write VMPIDR


      ; The following procedure to enter EL1 is implemented according to Arm Cortex-R52 Technical Reference Manual Revision r1p1 page 204.

      ; Program the HACTLR register because it defaults to only allowing EL2 accesses. HACTLR controls whether EL1 can access memory region registers and CPUACTLR.
      ; todo: check which controls are actually needed
      mrc p15, 4, r0, c1, c0, 1   ; Read HACTLR
      orr r0, r0, (0x1 << 8)      ; Enable PERIPHREGIONR EL1
      orr r0, r0, (0x1 << 7)      ; Enable FLASHIFREGIONR EL1
      orr r0, r0, (0x1 << 0)      ; Enable CPUACTLR EL1
      mcr p15, 4, r0, c1, c0, 1   ; Write HACTLR

      ; CPUACTLR: default is Ok
      ; todo: Do we want to prioritize Data-Accesses on the PFlash? (CPUACTLR.FLASHARBCTL)

      ; Current Program Status Register - Mode (CPSR.M [Bit 0:3])
      ;  User:  0b0000
      ;  FIQ:   0b0001
      ;  IRQ:   0b0010
      ;  SVC:   0b0011
      ;  Mon:   0b0110
      ;  Abort: 0b0111
      ;  Hyp:   0b1010
      ;  Undef: 0b1011
      ;  System:0b1111


      ; Set VBAR and HVBAR to the correct location for the vector tables

      ldr r0, =Os_CPUVec0         ; Load address of OS interrupt vector
      mcr p15, 0, r0, c12, c0, 0  ; Write VBAR
      ldr r0, =HypVect            ; Load address of Hypervisor interrupt vector
      mcr p15, 4, r0, c12, c0, 0  ; Write HVBAR



      ; Program the SPSR before entering EL1
      mrs r0, cpsr                ; Read CPSR
      and r0, r0, ~0x000f         ; Clear CPSR.M
      and r0, r0, ~0x100          ; Clear CPSR.A (enable exception handling)
      orr r0, r0, 0x000f          ; Set CPSR.M to System mode
      orr r0, r0, (0x1 << 5)      ; Set T bit so that T32 instructions are expected
      msr spsr_hyp, r0            ; Store the new value into the SPSR
      isb
      dsb

      ; Set the Core specific Generic Counter Frequency
      movw r0, 0xE100
      movt r0, 0x05F5
      mcr p15,0,r0,c14,c0,0       ; CNTFRQ = 100,000,000 [Hz]

      ; TODO: Keep HVC instruction enabled to be able to trap to HV mode again
      ; Disable the HVC instruction by setting HCR.HCD to 1
      ; mrc p15, 4, r0, c1, c1, 0   ; Read HCR
      ; orr r0, r0, (1 << 29)       ; Set HCR.HCD to 1
      ; mcr p15, 4, r0, c1, c1, 0   ; Write HCR

      ; Set ELR to point to the entry point of the EL1 code and call ERET.
      ldr r0, =end                ; Load address after ERET
      msr elr_hyp, r0             ; Set return address for ERET
      dsb                         ; Ensure completion of memory accesses
      isb                         ; Flush pipeline in PE
      eret                        ; ERET uses the value in ELR_hyp as the return address
    end:
    }

  #endif
#else
  /* Declare assembly function as extern so that it can be stubbed in x86 testing */
  extern void RBSYS_registerInit(void);
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  // todo: unclear why we need this after PLL configuration
  // todo: check if default is always MEMACC_WAIT and RWS_EN
  static inline void RBSYS_SetWaitStatesForOperationAtLowSpeed(void)
  {
    #define CR_RWS_EN      ((uint32)1<<2)
    #define CR_MEMACC_WAIT ((uint32)1<<3)

    /* RAM:
    *  - WaitStates for partial Write Accesses (RMW) += 1
    *  - WaitStates for Read Accesses  += 1
    * NVM:
    *  - ?? */

    /* Cluster0_RAM */
    /* BootCtrl FixRAM */
    PRAM_0.CR |= (CR_MEMACC_WAIT | CR_RWS_EN);
    /* Cluster1_RAM */
    PRAM_1.CR |= (CR_MEMACC_WAIT | CR_RWS_EN);
    /* Cluster2_RAM */
    PRAM_2.CR |= (CR_MEMACC_WAIT | CR_RWS_EN);
    /* SYSRAM_0 */
    PRAM_3.CR |= (CR_MEMACC_WAIT | CR_RWS_EN);
    /* SYSRAM_1 */
    PRAM_4.CR |= (CR_MEMACC_WAIT | CR_RWS_EN);

    /* PRAM_5..8 not available */

    /* OVLY_PRAM_0 */
    OVLY_PRAM_0.CR |= (CR_MEMACC_WAIT | CR_RWS_EN);
    /* OVLY_PRAM_1 */
    OVLY_PRAM_1.CR |= (CR_MEMACC_WAIT | CR_RWS_EN);
    /* OVLY_PRAM_2 */
    OVLY_PRAM_2.CR |= (CR_MEMACC_WAIT | CR_RWS_EN);
    /* OVLY_PRAM_3 */
    OVLY_PRAM_3.CR |= (CR_MEMACC_WAIT | CR_RWS_EN);
    /* OVLY_PRAM_4 */
    OVLY_PRAM_4.CR |= (CR_MEMACC_WAIT | CR_RWS_EN);
    /* OVLY_PRAM_5 */
    OVLY_PRAM_5.CR |= (CR_MEMACC_WAIT | CR_RWS_EN);

    /* set flash waitstates */
    NVM_CTRL_0_0.PFCR1 = 0x00000603uL; //< todo: Is this calculation for the WaitStates valid?
    NVM_CTRL_0_1.PFCR1 = 0x00000603uL; //< todo: Is this calculation for the WaitStates valid?
    NVM_CTRL_1_0.PFCR1 = 0x00000603uL; //< todo: Is this calculation for the WaitStates valid?
    NVM_CTRL_1_1.PFCR1 = 0x00000603uL; //< todo: Is this calculation for the WaitStates valid?
    NVM_CTRL_2_0.PFCR1 = 0x00000603uL; //< todo: Is this calculation for the WaitStates valid?
    NVM_CTRL_2_1.PFCR1 = 0x00000603uL; //< todo: Is this calculation for the WaitStates valid?
  }
#endif


/**
 * @brief SDA base register initialization
 *
 * The Small Data Area (SDA) optimization place certain data in a special memory block,
 * that can be accessed by using an offset from a base address. In most cases, data in this
 * block can be accessed more efficiently than other data using for example absolute addressing.
 *
 * @note Green Hills start-up code will initialize the SDA base register. But this could be to late
 * in our start-up, because accesses to SDA regions are done before cinit. Therefore an explicit
 * initialization is required.
 *
 * @return void
 */
#if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    static void RBSYS_SDA_registerInit(void);
    asm void RBSYS_SDA_registerInit(void)
    {
      -- By convention (Renesas RH850 EABI), the Green Hills compiler uses register r4 as the
      -- base register for the RAM SDA and register r5 as the base register for the ROM SDA.

      mov __gp, r4      -- initialize base register for the RAM SDA (=> Global pointer)
      mov __tp, r5      -- initialize base register for the ROM SDA (=> Text pointer)
    }
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    __attribute__((always_inline)) static inline void RBSYS_SDA_registerInit(void){/*not available for this CPU*/}
  #endif
#else
  /* Declare assembly function as extern so that it can be stubbed in x86 testing */
  extern void RBSYS_SDA_registerInit(void);
#endif


/* EBASE.RINT bit mask (when the RINT bit is set, all EI maskable interrupts are
    handled with a single vector address */
#define RBSYS_EBASE_RINT_MASK             0x00000001u

#if (RBFS_SysOverwriteEBASE == RBFS_SysOverwriteEBASE_ON)

  /* PSW.EBV bit mask (PROGRAM STATUS WORD - RESET and Exception vector operation) */
  #define RBSYS_PSW_EBV_MASK                0x00008000u


  /**
   * @brief Configure exception handler base address
   *
   * The exception handler base address can be changed on RH850/P1x within the EBASE
   * register. But the register content is only valid and used when the PSW.EBV bit is 1.
   * Take care - EBASE register shall be updated only as long as interrupts are disabled
   * (see UM chapter "System Register Hazards")
   *
   * @note To be called after cinit due the assert handling
   * @note EBASE shall only be updated if Interrupts are disabled (see sanity check below)
   *
   * @param[in] baseAddress   New exception handler base address (must be 512 byte aligned)
   *
   * @return void
   */
  static inline void RBSYS_InitEBASE(uint32 baseAddress)
  {
    unsigned int rbsys_psw, rbsys_rint; // use prefix to avoid using reserved identifier rint
    uint32 nEBASE;

    rbsys_rint = RBSYS_STSR(RBSYS_EBASE_REGID, RBSYS_EBASE_SELID);                    // get EBASE
    rbsys_rint &= RBSYS_EBASE_RINT_MASK;                                              // get EBASE.RINT

    assert((RBSYS_STSR(RBSYS_PSW_REGID, RBSYS_PSW_SELID) & RBSYS_PSW_ID_MASK) == RBSYS_PSW_ID_MASK);  // EBASE shall only be updated if Interrupts are disabled
    assert((baseAddress & 0x1FFu) == 0);                                              // ensure 512 byte alignment requirement of EBASE register

    nEBASE = baseAddress | rbsys_rint;                                                // still keep original EBASE.RINT content
    RBSYS_LDSR(RBSYS_EBASE_REGID, RBSYS_EBASE_SELID, nEBASE);

    rbsys_psw = RBSYS_STSR(RBSYS_PSW_REGID, RBSYS_PSW_SELID);
    rbsys_psw |= RBSYS_PSW_EBV_MASK;                                                  // set PSW.EBV to ensure that EBASE is used
    RBSYS_LDSR(RBSYS_PSW_REGID, RBSYS_PSW_SELID, rbsys_psw);
  }
#endif


#if (RBFS_CPUMisalignedAccessSupport == RBFS_CPUMisalignedAccessSupport_ON)
  /**
   * @brief Configure behavior for misaligned r/w accesses
   *
   *  In general the RH850G3M CPU allows misaligned placement of data. The behavior when the result of address
   *  calculation is a misaligned address can be selected by using the MCTL.MA bit. If the MCTL.MA bit has been
   *  set to "1", a misaligned access exception (MAE) does not occur and accessing the address is possible.
   *  So the CPU divides the transaction from misaligned data access to aligned data accesses
   *  for 16-bit and 32-bit accesses. In case of this, atomic characteristics are not guaranteed.
   *  In case of 64-bit access on P1x-C series, an exception still occurs even when MA bit is "1" for a misaligned access
   *  except word boundary address (see Mantis issue 1280 within CC-Cube DeviceSupport).
   *
   *  Due to the fact that the compiler can take advantage of this hardware feature (GHS compiler option -misalign_pack)
   *  and the core supports unaligned access for 16-bit and 32-bit accesses, CC-AS decides to use this optimization feature.
   *  To handle the 64 bit alignment restriction the option "-no_64bit_load_store" is set in the CC-AS compiler option set as well.
   *
   *  Hint: Incorrect c-code (e.g. wrong pointer arithmetic), which could result under some circumstances in
   *  misaligned accesses, will not lead to a MAE (misaligned access exception). Such code constructs must be detected
   *  by analysis tools (e.g. QAC, Bauhaus, ...)
   *
   * @return void
   */
  static inline void RBSYS_ConfigureAlignmentReaction(void)
  {
    unsigned int mctl = RBSYS_STSR(RBSYS_MCTL_REGID, RBSYS_MCTL_SELID);          // read System register 5, 1 - MCTL (Machine control)

    /* set the MCTL.MA bit to 1, that misaligned accesses will be supported by HW */
    mctl |= 0x2U;

    RBSYS_LDSR(RBSYS_MCTL_REGID, RBSYS_MCTL_SELID, mctl);           // write System register 5, 1 - MCTL (Machine control)
  }
#endif


/**
 * @brief Masking interrupts
 *
 * Disable manually all interrupts within core related PMR (P1x) / PLMR (U2A/U2C) (interrupt priority masking) register
 * and additionally within interrupt controller itself to ensure that INTs are really locked.
 *
 * @note To be called after cinit due the assert handling
 * @note P1x: PMR shall only be updated if Interrupts are disabled (see sanity check below)
 *
 * @return void
 */
static inline void RBSYS_maskInts(void)
{
  unsigned int core_id = RBSYS_getCoreID();

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    assert((RBSYS_STSR(RBSYS_PSW_REGID, RBSYS_PSW_SELID) & RBSYS_PSW_ID_MASK) == RBSYS_PSW_ID_MASK);  // PMR shall only be updated if Interrupts are disabled

    // masking within core specific system register 11, 2 - PMR (interrupt priority masking)
    RBSYS_LDSR(RBSYS_PMR_REGID, RBSYS_PMR_SELID, 0xFFFFu);

    // additional masking within interrupt controller
    IMR0 = 0xFFFFFFFFu;               // INTC1 0..31 (core-specific)

    if (core_id == RBSYS_CORE_ID_0)   // INTC2 32..255
    {
      IMR1 = 0xFFFFFFFFu;
      IMR2 = 0xFFFFFFFFu;
      IMR3 = 0xFFFFFFFFu;
      IMR4 = 0xFFFFFFFFu;
      IMR5 = 0xFFFFFFFFu;
      IMR6 = 0xFFFFFFFFu;
      IMR7 = 0xFFFFFFFFu;
    }
  #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    // masking within core specific system register 14, 2 - PLMR (interrupt priority level mask)
    RBSYS_LDSR(RBSYS_PLMR_REGID, RBSYS_PLMR_SELID, 0u);

    // additional masking within interrupt controller
    INTC1_SELFIMR0 = 0xFFFFFFFFu;      // INTC1 0..31 (core-specific)

    if (core_id == RBSYS_CORE_ID_0)   // INTC2 32..767
    {
      INTC2IMR1 = 0xFFFFFFFFu;
      INTC2IMR2 = 0xFFFFFFFFu;
      INTC2IMR3 = 0xFFFFFFFFu;
      INTC2IMR4 = 0xFFFFFFFFu;
      INTC2IMR5 = 0xFFFFFFFFu;
      INTC2IMR6 = 0xFFFFFFFFu;
      INTC2IMR7 = 0xFFFFFFFFu;
      INTC2IMR8 = 0xFFFFFFFFu;
      INTC2IMR9 = 0xFFFFFFFFu;
      INTC2IMR10 = 0xFFFFFFFFu;
      INTC2IMR11 = 0xFFFFFFFFu;
      INTC2IMR12 = 0xFFFFFFFFu;
      INTC2IMR13 = 0xFFFFFFFFu;
      INTC2IMR14 = 0xFFFFFFFFu;
      INTC2IMR15 = 0xFFFFFFFFu;
      #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasK1))
        INTC2IMR16 = 0xFFFFFFFFu;
      #endif
      #if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
        INTC2IMR17 = 0xFFFFFFFFu;
        INTC2IMR18 = 0xFFFFFFFFu;
        INTC2IMR19 = 0xFFFFFFFFu;
        INTC2IMR20 = 0xFFFFFFFFu;
        INTC2IMR21 = 0xFFFFFFFFu;
        INTC2IMR22 = 0xFFFFFFFFu;
        INTC2IMR23 = 0xFFFFFFFFu;
      #endif
    }
  #endif
}


#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  /** FE level maskable interrupt event mask: STM interrupt 8 */
  #define RBSYS_P1x_STM_FEINT_MASK              0x1u

  /** FE level maskable interrupt event mask: ECM interrupt */
  #define RBSYS_P1x_ECM_FEINT_MASK              0x2u

  /** FE level maskable interrupt event mask: Terminal NMI interrupt */
  #define RBSYS_P1x_TERMINAL_NMI_FEINT_MASK     0x4u
#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  // todo: rename more generically
  /** FE level maskable interrupt event mask: NMI pin Interrupt */
  #define RBSYS_U2A_NMIpin_FEINT_MASK              0x1u

  /** FE level maskable interrupt event mask: TPTM interrupt */
  #define RBSYS_U2A_TPMT_FEINT_MASK                0x2u

  /** FE level maskable interrupt event mask: ECM interrupt */
  #define RBSYS_U2A_ECM_FEINT_MASK                 0x4u
#endif


/**
 * @brief Masking FE level interrupts
 *
 * There are three sources for FE level interrupts (FEINT): ECM, STM interrupt and terminal NMI.
 * Only ECM interrupts will be configured as FEINT, all others are masked here:
 *
 * P1x:
 * Event 0:  - Interrupt 8 of STM0 (for CPU0, n=1)
 *           - Interrupt 8 of STM1 (for CPU1, n=2)
 * Event 1:  - ECM Interrupt
 * Event 2:  - terminal NMI Interrupt
 *
 * U2A/U2C:
 * Event 0:  - NMI pin Interrupt
 * Event 1:  - TPTM Interrupt
 * Event 2:  - ECM Interrupt
 *
 * @return void
 */
static inline void RBSYS_maskFEINT(void)
{
  unsigned int core_id = RBSYS_getCoreID();
  if (core_id == RBSYS_CORE_ID_0)
  {
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      FEINTFMSK0 = (RBSYS_P1x_STM_FEINT_MASK | RBSYS_P1x_TERMINAL_NMI_FEINT_MASK);
    #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      // todo: rename more generically
      FEINC_PE0FEINTMSK = (RBSYS_U2A_NMIpin_FEINT_MASK | RBSYS_U2A_TPMT_FEINT_MASK);
    #endif
  }
  #if(RBFS_MCORE == RBFS_MCORE_ON)
    else
    {
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      FEINTFMSK1 = (RBSYS_P1x_STM_FEINT_MASK | RBSYS_P1x_TERMINAL_NMI_FEINT_MASK);
    #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      // todo: rename more generically
      FEINC_PE1FEINTMSK = (RBSYS_U2A_NMIpin_FEINT_MASK | RBSYS_U2A_TPMT_FEINT_MASK);
    #endif
    }
  #endif
}

#if (RBFS_DataFlashECC == RBFS_DataFlashECC_Disabled)
  /**
   * @brief Deactivate DataFlash-ECC
   *
   * @return void
   */
  static inline void RBSYS_deactivateDataFlashECC(void)
  {
    #if((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      /**
       * Renesas U2A devices report the ECM-event for UncorrectableDataFlashECC error as double event with
       * the DataAccessError on the respective PE.
       * In development builds the DataAccessError shall be active and DataFlashECC must be disabled (as it would
       * constantly occur in FEE configs), in series builds for data availability reasons DataFlashECC (including 1Bit error correction)
       * must be enabled and therefore the DataAccessError event in ECM disabled.
       * todo: check if this also applies to U2C
       */

      /** Deactivate ECC Checks for DataFlash */
      RBSYS_UnlockAccessToHwModule( &ECCDFDFKCPROT );
      ECCDFDFECCCTL = 0x00000003u;
      RBSYS_LockAccessToHwModule( &ECCDFDFKCPROT );
    #else
      /* ECC Checks for DataFlash are not supposed to be deactivated for P1x */
      assert(0);
    #endif
  }
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
  /* Startaddress of LOCAL RAM (SELF) at [D1 to D5] */
  #if( RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1 )
    #define RBSYS_LRAM_SELF_START_ADDR 0xFEDF0000
  #elif( RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2 )
    #define RBSYS_LRAM_SELF_START_ADDR 0xFEDE7000
  #elif( RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3 )
    #define RBSYS_LRAM_SELF_START_ADDR 0xFEDE0000
  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5) )
    #define RBSYS_LRAM_SELF_START_ADDR 0xFEDF0000
  #endif

  /* Endaddress of LOCAL RAM (SELF) at [D1 to D5] (end address is same for all P1x devices) */
  #define RBSYS_LRAM_SELF_END_ADDR     0xFEE00000

  /**
   * @brief Clear Local RAM
   *
   * This is necessary if the RAM was contaminated by previous SW (e.g. BMGR) and no uC Reset was issued in between.
   * Self addresses are used, so actual zeroed address depends on the core that executes this function.
   * If this function is called by core 0, Backup RAM is not zeroed (just like application reset would not zero it).
   *
   * @return void
   */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    static void RBSYS_ClearLRAM_P1x(void);
    asm void RBSYS_ClearLRAM_P1x(void)
    {
%lab loop %lab cpuid0

      mov       RBSYS_LRAM_SELF_START_ADDR, ep
      mov       RBSYS_LRAM_SELF_END_ADDR, r12

      #if(RBFS_MCORE == RBFS_MCORE_ON)
        stsr      0, r11, 2           -- Get CoreID ((STSR(0,2) >> 16) - 1)
        shr       16, r11
        addi      -1, r11, r11

        bz        cpuid0              -- If CoreID == 0 clear LRAM without BURAM, otherwise clear whole LRAM
        br        loop
      #endif

    cpuid0:
      addi        -1024, r12, r12     -- Endaddress of LOCAL RAM (SELF) at [D1 to D5] - 1K BURAM (end address is same for all P1x devices)

    loop:
      sst.w     zero, 0[ep]
      add       4, ep
      cmp       r12, ep
      bne loop
    }
  #else
    /* Declare assembly function as extern so that it can be stubbed in x86 testing */
    extern void RBSYS_ClearLRAM_P1x(void);
  #endif
#endif


#if(RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
  #if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) && (RBFS_EmulationDevice == RBFS_EmulationDevice_None) )
    #define RBSYS_GRAM_START_ADDR 0xFEED8000
    #define RBSYS_GRAM_END_ADDR   0xFEF28000

  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD3) && ((RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD3ED) || (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD5ED)) )
    #define RBSYS_GRAM_START_ADDR 0xFEE58000
    #define RBSYS_GRAM_END_ADDR   0xFEFA8000

  /* Renesas D4 */
  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4) && (RBFS_EmulationDevice == RBFS_EmulationDevice_None) )
    #define RBSYS_GRAM_START_ADDR 0xFEE88000
    #define RBSYS_GRAM_END_ADDR   0xFEF78000

  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD4) && (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD5ED) )
    #define RBSYS_GRAM_START_ADDR 0xFEE58000
    #define RBSYS_GRAM_END_ADDR   0xFEFA8000

  /* Renesas D5 */
  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5) && (RBFS_EmulationDevice == RBFS_EmulationDevice_None) )
    #define RBSYS_GRAM_START_ADDR  0xFEE88000
    #define RBSYS_GRAM_END_ADDR    0xFEF78000

  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD5) && (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasD5ED) )
    #define RBSYS_GRAM_START_ADDR  0xFEE58000
    #define RBSYS_GRAM_END_ADDR    0xFEFA8000

  #else
    /** D1 / D2 does not have GRAM - nothing to do here, invalid configuration */
    static_assert(0, "Misconfiguration, shall never occur"); -- leads to unkown instruction error
  #endif

  /**
   * @brief Clear Global RAM
   *
   * This is necessary if the RAM was contaminated by previous SW (e.g. BMGR) and no uC Reset was issued in between.
   *
   * @return void
   */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    static void RBSYS_ClearGRAM_P1x(void);
    asm void RBSYS_ClearGRAM_P1x(void)
    {
%lab loop %lab end

      mov       RBSYS_GRAM_START_ADDR, ep
      mov       RBSYS_GRAM_END_ADDR, r12

    loop:
      sst.w     zero, 0[ep]
      add       4, ep
      cmp       r12, ep
      bne loop
    end:
    }
  #else
    /* Declare assembly function as extern so that it can be stubbed in x86 testing */
    extern void RBSYS_ClearGRAM_P1x(void);
  #endif
#endif



#if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)

  #define RBSYS_LRAM_SELF_START_ADDR 0xFDE00000
  #define RBSYS_LRAM_SELF_END_ADDR   0xFDE10000

  #define RBSYS_CRAM0_START_ADDR     0xFE000000
  #define RBSYS_CRAM0_END_ADDR       0xFE080000

  #define RBSYS_CRAM1_START_ADDR     0xFE100000
  #define RBSYS_CRAM1_END_ADDR       0xFE180000

  #define RBSYS_CRAM2_START_ADDR     0xFE400000
  #if( RBFS_TargetDevice == RBFS_TargetDevice_RenesasM3 )
    /* Endaddress of Cluster RAM2 - 1KB Backup RAM */
    #define RBSYS_CRAM2_END_ADDR     0xFE4FFC00
  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) \
      || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6) )
    /* Endaddress of Cluster RAM2 - 1KB Backup RAM */
    #define RBSYS_CRAM2_END_ADDR     0xFE5FFC00
  #endif

  #define RBSYS_CRAM3_START_ADDR     0xFE800000
  #if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2) )
    /* Endaddress of Cluster RAM3 - 1KB Backup RAM */
    #define RBSYS_CRAM3_END_ADDR     0xFE81FC00
  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM3) )
    #define RBSYS_CRAM3_END_ADDR     0xFE820000
  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) \
      || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6) )
    #define RBSYS_CRAM3_END_ADDR     0xFE840000
  #endif

  #if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM2) )
    #define RBSYS_BURAM_START_ADDR   0xFE81FC00
    #define RBSYS_BURAM_END_ADDR     0xFE820000
  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM3) )
    #define RBSYS_BURAM_START_ADDR   0xFE4FFC00
    #define RBSYS_BURAM_END_ADDR     0xFE500000
  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD7) \
      || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasM6) )
    #define RBSYS_BURAM_START_ADDR   0xFE5FFC00
    #define RBSYS_BURAM_END_ADDR     0xFE600000
  #endif


  /**
   * @brief Clear Local RAM
   *
   * Renesas U2A devices are not equipped with hardware based zeroing of LRAM.
   * Therefore each CPU must clear its own local RAM (self-address is used here to have a common API for all cores,
   * actual addresses are differnt for the cores)!
   *
   * @return void
   */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    static void RBSYS_ClearLRAM_U2A(void);
    asm void RBSYS_ClearLRAM_U2A(void)
    {
%lab loop

      mov       RBSYS_LRAM_SELF_START_ADDR, ep
      mov       RBSYS_LRAM_SELF_END_ADDR, r12

    loop:
      sst.w     zero, 0[ep]
      add       4, ep
      cmp       r12, ep
      bne loop
    }
  #else
    /* Declare assembly function as extern so that it can be stubbed in x86 testing */
    extern void RBSYS_ClearLRAM_U2A(void);
  #endif


  #if (RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON)

    /**
     * @brief Clear Cluster RAM 0
     *
     * Renesas U2A devices are not equipped with hardware based zeroing of CRAM.
     * Therefore SW must clear the Cluster RAM0!
     *
     * @return void
     */
    #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
      static void RBSYS_ClearCRAM0_U2A(void);
      asm void RBSYS_ClearCRAM0_U2A(void)
      {
%lab loop

        mov       RBSYS_CRAM0_START_ADDR, ep
        mov       RBSYS_CRAM0_END_ADDR, r12

      loop:
        sst.w     zero, 0[ep]
        add       4, ep
        cmp       r12, ep
        bne loop
      }
    #else
      /* Declare assembly function as extern so that it can be stubbed in x86 testing */
      extern void RBSYS_ClearCRAM0_U2A(void);
    #endif

  #endif

  #if (RBFS_RenesasU2aCRAM1 == RBFS_RenesasU2aCRAM1_ON)

    /**
     * @brief Clear Cluster RAM 1
     *
     * Renesas U2A devices are not equipped with hardware based zeroing of CRAM.
     * Therefore SW must clear the Cluster RAM1!
     *
     * @return void
     */
    #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
      static void RBSYS_ClearCRAM1_U2A(void);
      asm void RBSYS_ClearCRAM1_U2A(void)
      {
%lab loop

        mov       RBSYS_CRAM1_START_ADDR, ep
        mov       RBSYS_CRAM1_END_ADDR, r12

      loop:
        sst.w     zero, 0[ep]
        add       4, ep
        cmp       r12, ep
        bne loop
      }
    #else
      /* Declare assembly function as extern so that it can be stubbed in x86 testing */
      extern void RBSYS_ClearCRAM1_U2A(void);
    #endif

  #endif

  #if (RBFS_RenesasU2aCRAM2 == RBFS_RenesasU2aCRAM2_ON)

    /**
     * @brief Clear Cluster RAM 2
     *
     * Renesas U2A devices are not equipped with hardware based zeroing of CRAM.
     * Therefore SW must clear the Cluster RAM2!
     *
     * @return void
     */
    #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
      static void RBSYS_ClearCRAM2_U2A(void);
      asm void RBSYS_ClearCRAM2_U2A(void)
      {
%lab loop

        mov       RBSYS_CRAM2_START_ADDR, ep
        mov       RBSYS_CRAM2_END_ADDR, r12


      loop:
        sst.w     zero, 0[ep]
        add       4, ep
        cmp       r12, ep
        bne loop
      }
    #else
      /* Declare assembly function as extern so that it can be stubbed in x86 testing */
      extern void RBSYS_ClearCRAM2_U2A(void);
    #endif

  #endif

  #if (RBFS_RenesasU2aCRAM3 == RBFS_RenesasU2aCRAM3_ON)

    /**
     * @brief Clear Cluster RAM 3
     *
     * Renesas U2A devices are not equipped with hardware based zeroing of CRAM.
     * Therefore SW must clear the Cluster RAM3!
     *
     * @return void
     */
    #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
      static void RBSYS_ClearCRAM3_U2A(void);
      asm void RBSYS_ClearCRAM3_U2A(void)
      {
%lab loop

        mov       RBSYS_CRAM3_START_ADDR, ep
        mov       RBSYS_CRAM3_END_ADDR, r12

      loop:
        sst.w     zero, 0[ep]
        add       4, ep
        cmp       r12, ep
        bne loop
      }
    #else
      /* Declare assembly function as extern so that it can be stubbed in x86 testing */
      extern void RBSYS_ClearCRAM3_U2A(void);
    #endif

  #endif

  /**
   * @brief Clear Backup RAM
   *
   * Renesas U2A devices are not equipped with hardware based zeroing of CRAM.
   * Therefore SW must clear the Backup RAM (allocated inside Cluster RAM 2 [M3,M6] or Cluster RAM 3 [M2]) once during PowerOn!
   *
   * HINT: There is no physical BURAM on U2A devices - last 1KB of CRAM2/3 is used for BURAM purpose
   *
   * @return void
   */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    static void RBSYS_ClearBURAM_U2A(void);
    asm void RBSYS_ClearBURAM_U2A(void)
    {
%lab loop

      mov       RBSYS_BURAM_START_ADDR, ep
      mov       RBSYS_BURAM_END_ADDR, r12


    loop:
      sst.w     zero, 0[ep]
      add       4, ep
      cmp       r12, ep
      bne loop
    }
  #else
    /* Declare assembly function as extern so that it can be stubbed in x86 testing */
    extern void RBSYS_ClearBURAM_U2A(void);
  #endif

#elif (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C)

  #define RBSYS_LRAM_SELF_START_ADDR    0xFDE00000
  #define RBSYS_LRAM_SELF_END_ADDR      0xFDE20000

  #define RBSYS_CRAM0_PART1_START_ADDR  0xFE000000

  #if( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasK0)||(RBFS_TargetDevice == RBFS_TargetDevice_RenesasK1) )
    #define RBSYS_BURAM_START_ADDR   0xFE000400
    #define RBSYS_BURAM_END_ADDR     0xFE000800
  #endif

  #define RBSYS_CRAM0_PART1_END_ADDR   RBSYS_BURAM_START_ADDR
  #define RBSYS_CRAM0_PART2_START_ADDR RBSYS_BURAM_END_ADDR

  #if(   (RBFS_TargetDevice == RBFS_TargetDevice_RenesasK0) && (RBFS_EmulationDevice == RBFS_EmulationDevice_None) )
    #define RBSYS_CRAM0_PART2_END_ADDR       0xFE028000
  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasK0) && (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasK3ED) )
    #define RBSYS_CRAM0_PART2_END_ADDR       0xFE030000
  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasK1) && (RBFS_EmulationDevice == RBFS_EmulationDevice_None) )
    #define RBSYS_CRAM0_PART2_END_ADDR       0xFE070000
  #elif( (RBFS_TargetDevice == RBFS_TargetDevice_RenesasK1) && (RBFS_EmulationDevice == RBFS_EmulationDevice_RenesasK3ED) )
    #define RBSYS_CRAM0_PART2_END_ADDR       0xFE08A000
  #endif


  /**
   * @brief Clear Local RAM
   *
   * Renesas U2C devices are not equipped with hardware based zeroing of LRAM.
   * Therefore each CPU must clear its own local RAM (self-address is used here to have a common API for all cores,
   * actual addresses are differnt for the cores)!
   *
   * @return void
   */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    static void RBSYS_ClearLRAM_U2C(void);
    asm void RBSYS_ClearLRAM_U2C(void)
    {
%lab loop

      mov       RBSYS_LRAM_SELF_START_ADDR, ep
      mov       RBSYS_LRAM_SELF_END_ADDR, r12

    loop:
      sst.w     zero, 0[ep]
      add       4, ep
      cmp       r12, ep
      bne loop
    }
  #else
    /* Declare assembly function as extern so that it can be stubbed in x86 testing */
    extern void RBSYS_ClearLRAM_U2C(void);
  #endif



  /**
    * @brief Clear Cluster RAM 0
    *
    * Renesas U2C devices are not equipped with hardware based zeroing of CRAM.
    * Therefore SW must clear the Cluster RAM0!
    *
    * BURAM is inside CRAM0, therefore clearing CRAM0 means clearing 2 sections.
    *
    * @return void
    */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    static void RBSYS_ClearCRAM0_U2C(void);
    asm void RBSYS_ClearCRAM0_U2C(void)
    {
%lab loop1, loop2

      mov       RBSYS_CRAM0_PART1_START_ADDR, ep
      mov       RBSYS_CRAM0_PART1_END_ADDR, r12

    loop1:
      sst.w     zero, 0[ep]
      add       4, ep
      cmp       r12, ep
      bne loop1

      mov       RBSYS_CRAM0_PART2_START_ADDR, ep
      mov       RBSYS_CRAM0_PART2_END_ADDR, r12

    loop2:
      sst.w     zero, 0[ep]
      add       4, ep
      cmp       r12, ep
      bne loop2

    }
  #else
    /* Declare assembly function as extern so that it can be stubbed in x86 testing */
    extern void RBSYS_ClearCRAM0_U2C(void);
  #endif


  /**
   * @brief Clear Backup RAM
   *
   * Renesas U2C devices are not equipped with hardware based zeroing of CRAM.
   * Therefore SW must clear the Backup RAM (allocated inside Cluster RAM 0) once during PowerOn!
   *
   * HINT: There is no physical BURAM on U2C devices - last 1KB of CRAM0 is used for BURAM purpose, todo: define BURAM for U2C
   *
   * @return void
   */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    static void RBSYS_ClearBURAM_U2C(void);
    asm void RBSYS_ClearBURAM_U2C(void)
    {
%lab loop

      mov       RBSYS_BURAM_START_ADDR, ep
      mov       RBSYS_BURAM_END_ADDR, r12


    loop:
      sst.w     zero, 0[ep]
      add       4, ep
      cmp       r12, ep
      bne loop
    }
  #else
    /* Declare assembly function as extern so that it can be stubbed in x86 testing */
    extern void RBSYS_ClearBURAM_U2C(void);
  #endif

#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    static_assert(RB_NUM_CORES <= 2, "RBSYS_ClearLRAM only supports 2 cores");
    /* Attention:
     * TCM-A incorporates an ECC scheme for each 64-bit chunks of data
     * TCM-B/-C incorporate an ECC scheme for each 32-bit chunks of data
     *   -> see R52 Technical Reference Manual */
    static void RBSYS_ClearLRAM_Stellar(void);
    asm void RBSYS_ClearLRAM_Stellar(void)
    {
%lab init_core0 %lab init_core1 %lab loop_clear_ram %lab clear_ram %lab exit

      mov r0, 0
      mov r1, 0

      ; get core ID
      mrc p15, 0, r2, c0, c0, 5   ; Read MPIDR
      and r2, 0xff                ; Extract core ID

      cmp r2, RBSYS_CORE_ID_0
      bne init_core1

      init_core0:
        movw    r3, %lo(C0_CPU0_tcma_start)
        movt    r3, %hi(C0_CPU0_tcma_start) ; r3 = start addr
        movw    r4, %lo(C0_CPU0_tcma_size)
        movt    r4, %hi(C0_CPU0_tcma_size)  ; r4 = size
        bl  clear_ram

        movw    r3, %lo(C0_CPU0_tcmb_start)
        movt    r3, %hi(C0_CPU0_tcmb_start) ; r3 = start addr
        movw    r4, %lo(C0_CPU0_tcmb_size)
        movt    r4, %hi(C0_CPU0_tcmb_size)  ; r4 = size
        bl  clear_ram

        movw    r3, %lo(C0_CPU0_tcmc_start)
        movt    r3, %hi(C0_CPU0_tcmc_start) ; r3 = start addr
        movw    r4, %lo(C0_CPU0_tcmc_size)
        movt    r4, %hi(C0_CPU0_tcmc_size)  ; r4 = size
        bl  clear_ram
        b exit

      init_core1:
        movw    r3, %lo(C0_CPU1_tcma_start)
        movt    r3, %hi(C0_CPU1_tcma_start) ; r3 = start addr
        movw    r4, %lo(C0_CPU1_tcma_size)
        movt    r4, %hi(C0_CPU1_tcma_size)  ; r4 = size
        bl  clear_ram

        movw    r3, %lo(C0_CPU1_tcmb_start)
        movt    r3, %hi(C0_CPU1_tcmb_start) ; r3 = start addr
        movw    r4, %lo(C0_CPU1_tcmb_size)
        movt    r4, %hi(C0_CPU1_tcmb_size)  ; r4 = size
        bl  clear_ram

        movw    r3, %lo(C0_CPU1_tcmc_start)
        movt    r3, %hi(C0_CPU1_tcmc_start) ; r3 = start addr
        movw    r4, %lo(C0_CPU1_tcmc_size)
        movt    r4, %hi(C0_CPU1_tcmc_size)  ; r4 = size
        bl  clear_ram
        b exit

      clear_ram:
        add r4, r3, r4
      loop_clear_ram:
        strd r0,r1, [r3], 8      ; store r0 and r1 to [r3] and r3 += 8
        cmp  r3,r4               ; current address < end address?
        blo  loop_clear_ram      ; branch if r3 lower r4 (cmp = sub without)
        bx   lr                  ; return
      exit:
    }
  #else
    /* Declare assembly function as extern so that it can be stubbed in x86 testing */
    extern void RBSYS_ClearLRAM_Stellar(void);
  #endif

#endif



/**
 * @brief Clear Local RAM
 *
 * For P1x devices, LRAM has to be cleared if there is no reset between BMGR and APPLICATION (Trusted Boot)
 * For U2A/U2C devices, LRAM has to be zeroed anyways because it's never initialized by hardware.
 *
 * @return void
 */
#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_CyberSecurityBoot != RBFS_CyberSecurityBoot_NonTrusted) && (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION) )
  #define RBSYS_ClearLRAM() RBSYS_ClearLRAM_P1x()
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  #define RBSYS_ClearLRAM() RBSYS_ClearLRAM_U2A()
#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
  #define RBSYS_ClearLRAM() RBSYS_ClearLRAM_U2C()
#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  #define RBSYS_ClearLRAM() RBSYS_ClearLRAM_Stellar()
#else
  #define RBSYS_ClearLRAM()
  //< nothing to do, LRAM zeroing is done by hardware
#endif
/**< This abstraction cannot be handled via inline functions because Stack is not yet set up!! */




/**
 * @brief Clear Global RAM
 *
 * For P1x devices, GRAM has to be cleared if there is no reset between BMGR and APPLICATION (Trusted Boot)
 * For U2A/U2C devices, CRAM has to be zeroed anyways because it's never initialized by hardware.
 *
 * @return void
 */

#if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
  && (RBFS_CyberSecurityBoot != RBFS_CyberSecurityBoot_NonTrusted) \
  && (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION) \
  )

  static inline void RBSYS_ClearGRAM(void)
  {
    /* Secure Boot: To not evaluate software twice, no software reset is done between BMGR and Application. Therefore, System has to
      be put into "reset"-like state (e.g. RAM has to be zeroed). Has to be done for P1x explicitely, as there is no SW RAM zeroing
      by default. */
    #if( RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON )
      unsigned int core_id = RBSYS_getCoreID();

      if (core_id == RBSYS_CORE_ID_0)
      {
        RBSYS_ClearGRAM_P1x();
      }
    #endif
  }

#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )

  static inline void RBSYS_ClearGRAM(void)
  {
    unsigned int core_id = RBSYS_getCoreID();

    /* CRAM Zeroing has to be performed because U2A Family does not provide HW Initialization for these RAMs */

    /** todo: to save startup Runtime, clear ClusterRAM(s) from different Cores
     *  current solution: Clear everything from Core0 to avoid concurrency effects
     *  Attention: If Core 0 does not clear the whole GRAM, it may also not access the whole GRAM until Cores are synchronized */
    {
      #if( RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON )
        if (core_id == RBSYS_CORE_ID_0)
        {
          RBSYS_ClearCRAM0_U2A();   /* No HW based CRAM0 zeroing on U2A devices! */
        }
      #endif

      #if( RBFS_RenesasU2aCRAM1 == RBFS_RenesasU2aCRAM1_ON )
        if (core_id == RBSYS_CORE_ID_0)
        {
          RBSYS_ClearCRAM1_U2A();   /* No HW based CRAM1 zeroing on U2A devices! */
        }
      #endif

      #if( RBFS_RenesasU2aCRAM2 == RBFS_RenesasU2aCRAM2_ON )
        if (core_id == RBSYS_CORE_ID_0)
        {
          RBSYS_ClearCRAM2_U2A();   /* No HW based CRAM2 zeroing on U2A devices! */
        }
      #endif

      #if( RBFS_RenesasU2aCRAM3 == RBFS_RenesasU2aCRAM3_ON )
        if (core_id == RBSYS_CORE_ID_0)
        {
          RBSYS_ClearCRAM3_U2A();   /* No HW based CRAM3 zeroing on U2A devices! */
        }
      #endif

      if (core_id == RBSYS_CORE_ID_0)
      {
        /* condition: If there is no ApplicationReset or there is a System Reset => Clear BURAM */
        if( (!RBSYS_isSWApplicationReset()) || RBSYS_isSWSystemReset() || RBSYS_isTerminalReset() )
        {
          /** Clear BURAM in case of:
                - SW System Reset
                - HW System Reset (Terminal Reset)
                - No Application Reset (VMON and PowerOn Reset overwrite Application Reset flag)
              only to have identical behavior as in P1x */
          RBSYS_ClearBURAM_U2A();
        }
      }
    }
  }

#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )

  static inline void RBSYS_ClearGRAM(void)
  {
    unsigned int core_id = RBSYS_getCoreID();

    /* CRAM Zeroing has to be performed because U2C Family does not provide HW Initialization for these RAMs */

    /** todo: to save startup Runtime, clear ClusterRAM(s) from different Cores
     *  current solution: Clear everything from Core0 to avoid concurrency effects
     *  Attention: If Core 0 does not clear the whole GRAM, it may also not access the whole GRAM until Cores are synchronized */
    {
      if (core_id == RBSYS_CORE_ID_0)
      {
        RBSYS_ClearCRAM0_U2C();   /* No HW based CRAM0 zeroing on U2C devices! */

        /* condition: If there is no ApplicationReset or there is a System Reset => Clear BURAM */
        if( (!RBSYS_isSWApplicationReset()) || RBSYS_isSWSystemReset() || RBSYS_isTerminalReset() )
        {
          /** Clear BURAM in case of:
                - SW System Reset
                - HW System Reset (Terminal Reset)
                - No Application Reset (VMON and PowerOn Reset overwrite Application Reset flag)
              only to have identical behavior as in P1x */
          RBSYS_ClearBURAM_U2C();
        }
      }
    }
  }

#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

  /* Attention:
   * AXI-connected RAM incorporates an ECC scheme for each 64-bit chunks of data
   *   -> see P6 Reference Manual RM0496 Rev 1 p. 1250 */

  /* attention: this implementation destroys the runtime context - can only be called in StartupPreOsPhase0!
   * if required at later point in time, consider storing LP as well as other used registers */
  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
    static void RBSYS_ClearBURAM_Stellar(void);
    asm void RBSYS_ClearBURAM_Stellar(void)
    {
%lab clear_ram %lab loop_clear_ram %lab exit
      mov r0, 0
      mov r1, 0

      movw r2, %lo(BURAM_start)
      movt r2, %hi(BURAM_start)
      movw r3, %lo(BURAM_size)
      movt r3, %hi(BURAM_size)
      bl  clear_ram

      b exit

    clear_ram:
      add r3, r2, r3
    loop_clear_ram:
      strd r0,r1, [r2], 8      ; store r0 and r1 to [r2] and r2 += 8
      cmp  r2,r3               ; current address < end address?
      blo  loop_clear_ram      ; branch if r2 lower r3 (cmp = sub without)
      bx   lr                  ; return

    exit:
    }

    static void RBSYS_ClearGRAM_Stellar(void);
    asm void RBSYS_ClearGRAM_Stellar(void)
    {
%lab clear_ram %lab loop_clear_ram %lab exit
      mov r0, 0
      mov r1, 0

      movw r2, %lo(SYSRAM0_start)
      movt r2, %hi(SYSRAM0_start)
      movw r3, %lo(SYSRAM0_size)
      movt r3, %hi(SYSRAM0_size)
      bl  clear_ram

      movw r2, %lo(SYSRAM1_start)
      movt r2, %hi(SYSRAM1_start)
      movw r3, %lo(SYSRAM1_size)
      movt r3, %hi(SYSRAM1_size)
      bl  clear_ram

      movw r2, %lo(CRAM0_0_start)
      movt r2, %hi(CRAM0_0_start)
      movw r3, %lo(CRAM0_0_size)
      movt r3, %hi(CRAM0_0_size)
      bl  clear_ram

      movw r2, %lo(CRAM0_1_start)
      movt r2, %hi(CRAM0_1_start)
      movw r3, %lo(CRAM0_1_size)
      movt r3, %hi(CRAM0_1_size)
      bl  clear_ram

      movw r2, %lo(CRAM1_0_start)
      movt r2, %hi(CRAM1_0_start)
      movw r3, %lo(CRAM1_0_size)
      movt r3, %hi(CRAM1_0_size)
      bl  clear_ram

      movw r2, %lo(CRAM1_1_start)
      movt r2, %hi(CRAM1_1_start)
      movw r3, %lo(CRAM1_1_size)
      movt r3, %hi(CRAM1_1_size)
      bl  clear_ram

      movw r2, %lo(CRAM2_0_start)
      movt r2, %hi(CRAM2_0_start)
      movw r3, %lo(CRAM2_0_size)
      movt r3, %hi(CRAM2_0_size)
      bl  clear_ram

      movw r2, %lo(CRAM2_1_start)
      movt r2, %hi(CRAM2_1_start)
      movw r3, %lo(CRAM2_1_size)
      movt r3, %hi(CRAM2_1_size)
      bl  clear_ram

      ; todo: Overlay RAM - do we clear it if not used?

      b exit

    clear_ram:
      add r3, r2, r3
    loop_clear_ram:
      strd r0,r1, [r2], 8      ; store r0 and r1 to [r2] and r2 += 8
      cmp  r2,r3               ; current address < end address?
      blo  loop_clear_ram      ; branch if r2 lower r3 (cmp = sub without)
      bx   lr                  ; return
    exit:
    }

    __attribute__((always_inline)) static inline void RBSYS_ClearGRAM(void)
    {
      RBSYS_ClearGRAM_Stellar();

      if( (!RBSYS_isSWApplicationReset()) || RBSYS_isSWSystemReset() || RBSYS_isTerminalReset())
      {
        RBSYS_ClearBURAM_Stellar();
      }
    }

  #else
    /* Declare assembly function as extern so that it can be stubbed in x86 testing */
    extern void RBSYS_ClearGRAM(void);
  #endif

#else
  #define RBSYS_ClearGRAM()
  //< nothing to do, GRAM zeroing is done by hardware
#endif



#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  static inline void RBSYS_DisableWatchdog(void)
  {
    //only the watchdog SWT_SYS_0 is activated by default on reset
    //todo: not sure if it needs to be disabled, don't know for what exactly SWT_SYS_0 is for
    //clear soft lock bit
    SWT_SYS_0.SR = 0xC520u;
    SWT_SYS_0.SR = 0xD928u;
    //disable watchdog
    SWT_SYS_0.CR = 0xFF00010Au;
  }

  static inline void RBSYS_SwitchSVToHV(void)
  {
    RBSYS_HVC(0);
  }

  #if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
  static void RBSYS_SwitchHVToSV(void);
  asm void RBSYS_SwitchHVToSV(void)
  {
%lab end
      ; Set ELR to point to the entry point of the EL1 code and call ERET.
      push {r0}                   ; store r0 to stack in order to be able to use it
      ldr r0, =end                ; Load address after ERET
      msr elr_hyp, r0             ; Set return address for ERET
      pop {r0}                    ; restore r0 from stack
      msr sp_usr, sp              ; restore generic Stackpointer
      dsb                         ; Ensure completion of memory accesses
      isb                         ; Flush pipeline in PE
      eret                        ; ERET uses the value in ELR_hyp as the return address
    end:
  }
  #else
    /* Declare assembly function as extern so that it can be stubbed in x86 testing */
    extern void RBSYS_SwitchHVToSV(void);
  #endif
#endif


#ifdef __QAC__
  #pragma PRQA_MESSAGES_ON 1006
#endif


/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
