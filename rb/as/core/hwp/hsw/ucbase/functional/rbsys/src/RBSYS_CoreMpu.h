#ifndef RBSYS_COREMPU_H__
#define RBSYS_COREMPU_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"

/* used interfaces */


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWSVPRestrictions,
                          RBFS_TPSWSVPRestrictions_OFF,
                          RBFS_TPSWSVPRestrictions_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysEnvironment,
                          RBFS_SysEnvironment_Target,
                          RBFS_SysEnvironment_Simulation);


#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  typedef struct{
    uint32 start;
    uint32 size;
    uint32 end;
    uint32 memoryType1;
    uint32 memoryType2;
  } RBSYS_MpuRegion_t;
  #define RBSYS_MPU_REGION_SIZE 20
  static_assert(RBSYS_MPU_REGION_SIZE == sizeof(RBSYS_MpuRegion_t), "RBSYS_MPU_REGION_SIZE is defined incorrectly");

  extern const RBSYS_MpuRegion_t RBSYS_MpuRegionConfig[];
  extern const uint32 RBSYS_MpuRegionConfigSize;

  /* We have 4 types of memories
    1.) PERIPHERALS (LLPP + NOC-Peripherals)
      Device, nGnRnE                   ==> Attr. 0 = 0x00
   Device-nGnRnE Device non-Gathering,
   non-Reordering, No Early write acknowledgement.
   Equivalent to the Strongly-ordered memory type in earlier versions of the
   architecture.)
    2.) Not used atm
      Normal, Outer non-cacheable, Inner non-cacheable
                               ==> Attr. 1 = 0x44
    3.) PROGRAM FLASH
      Normal, Outer WT, read allocate, write no allocate, non-transient
              Inner WT, read allocate, write no allocate, non-transient
                               ==> Attr. 2 = 0xAA
    4.) RAM + DATA FLASH R/W -> will not be cached, because it is shareable!!!
      Device, GRE non-cacheable, XN (execute never) = 1, no speculation
              Inner WT, read allocate, write no allocate, execute never (XN=1 by default)
                               ==> Attr. 3 = 0x0C
        todo: why is this device memory?

  LLPP and peripherals use 1.)
  PFlash uses 3.) and is the only memory to use caches
  TCM-A, TCM-B, TCM-C, SRAM, Overlay-RAM, DME/DSPH SRAM, NVM Programming, Data NVM programming, Data NVM read. uses 4.)

  Hints:
    - R / W => policy active for Read and/or Write Accesses (allocate)
    - "Transient": A Transient memory region has a higher probability of changing its value. Therefore,
      the allocation of non-transient memory in the cache is prioritized.
  */

  // MAIR.Attr<n>[7:4]
  #define RBSYS_CoreMPU_MAIR_Device                                        (0x0)
  #define RBSYS_CoreMPU_MAIR_Normal_OuterNonCacheable                      (0x4)
  #define RBSYS_CoreMPU_MAIR_Normal_OuterWriteThroughNonTransientRead      (0xA)

  // MAIR.Attr<n>[3:0] if MAIR.Attr<n>[7:4] == Device
  #define RBSYS_CoreMPU_MAIR_Device_nGnRnE                                 (0x0)
  #define RBSYS_CoreMPU_MAIR_Device_GRE                                    (0xC)

  // MAIR.Attr<n>[3:0] if MAIR.Attr<n>[7:4] == Normal
  #define RBSYS_CoreMPU_MAIR_Normal_InnerNonCacheable                      (0x4)
  #define RBSYS_CoreMPU_MAIR_Normal_InnerWriteThroughNonTransientRead      (0xA)


  #define RBSYS_CoreMPU_MAIR_Peripherals         ((RBSYS_CoreMPU_MAIR_Device                                   << 4) | RBSYS_CoreMPU_MAIR_Device_nGnRnE)
  #define RBSYS_CoreMPU_MAIR_NotUsed             ((RBSYS_CoreMPU_MAIR_Normal_OuterNonCacheable                 << 4) | RBSYS_CoreMPU_MAIR_Normal_InnerNonCacheable)
  #define RBSYS_CoreMPU_MAIR_ReadOnlyFlash       ((RBSYS_CoreMPU_MAIR_Normal_OuterWriteThroughNonTransientRead << 4) | RBSYS_CoreMPU_MAIR_Normal_InnerWriteThroughNonTransientRead)
  #define RBSYS_CoreMPU_MAIR_WritableFlashAndRAM ((RBSYS_CoreMPU_MAIR_Device                                   << 4) | RBSYS_CoreMPU_MAIR_Device_GRE)

  #define RBSYS_CoreMPU_MAIR_Peripherals_Index          (0u)
  #define RBSYS_CoreMPU_MAIR_NotUsed_Index              (1u)
  #define RBSYS_CoreMPU_MAIR_ReadOnlyFlash_Index        (2u)
  #define RBSYS_CoreMPU_MAIR_WritableFlashAndRAM_Index  (3u)

  #define RBSYS_CoreMPU_MAIR0   (RBSYS_CoreMPU_MAIR_Peripherals         << (RBSYS_CoreMPU_MAIR_Peripherals_Index         * 8)) \
                              | (RBSYS_CoreMPU_MAIR_NotUsed             << (RBSYS_CoreMPU_MAIR_NotUsed_Index             * 8)) \
                              | (RBSYS_CoreMPU_MAIR_ReadOnlyFlash       << (RBSYS_CoreMPU_MAIR_ReadOnlyFlash_Index       * 8)) \
                              | (RBSYS_CoreMPU_MAIR_WritableFlashAndRAM << (RBSYS_CoreMPU_MAIR_WritableFlashAndRAM_Index * 8))

#elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  /* Common MPU Driver interface definitions */
  #define RBSYS_MPU_ACCESS_USER_RD (1U<<0)
  #define RBSYS_MPU_ACCESS_USER_WR (1U<<1)
  #define RBSYS_MPU_ACCESS_USER_EX (1U<<2)
  #define RBSYS_MPU_ACCESS_SV_RD   (1U<<3)
  #define RBSYS_MPU_ACCESS_SV_WR   (1U<<4)
  #define RBSYS_MPU_ACCESS_SV_EX   (1U<<5)
  /* Bit 6 is intentionally left out - Hardware specifc for Renesas P1x */
  #define RBSYS_MPU_ACCESS_E       (1U<<7)


  #define RBSYS_BASICATTR_UM_R    (RBSYS_MPU_ACCESS_USER_RD)
  #define RBSYS_BASICATTR_UM_RX   (RBSYS_MPU_ACCESS_USER_RD | RBSYS_MPU_ACCESS_USER_EX)
  #define RBSYS_BASICATTR_UM_RW   (RBSYS_MPU_ACCESS_USER_RD | RBSYS_MPU_ACCESS_USER_WR)
  #define RBSYS_BASICATTR_UM_RWX  (RBSYS_BASICATTR_UM_RW | RBSYS_MPU_ACCESS_USER_EX)
  #define RBSYS_BASICATTR_SV_RW   (RBSYS_MPU_ACCESS_SV_RD | RBSYS_MPU_ACCESS_SV_WR)
  #define RBSYS_BASICATTR_SV_RX   (RBSYS_MPU_ACCESS_SV_RD | RBSYS_MPU_ACCESS_SV_EX)
  #define RBSYS_BASICATTR_SV_RWX  (RBSYS_BASICATTR_SV_RW | RBSYS_MPU_ACCESS_SV_EX)

  /* Common MPU region attribute values, depending on SVP restrictions */
  #if (RBFS_TPSWSVPRestrictions == RBFS_TPSWSVPRestrictions_ON)
    // SVP restrictions on: MPU active in supervisor mode, RAM not executable
    #define RBSYS_USERSTACK         (RBSYS_BASICATTR_UM_RW | RBSYS_BASICATTR_SV_RW)
    #define RBSYS_USERDATA          (RBSYS_BASICATTR_UM_RW | RBSYS_BASICATTR_SV_RW)
    #define RBSYS_USERFLASH         (RBSYS_BASICATTR_UM_RX | RBSYS_BASICATTR_SV_RX)
    #define RBSYS_SVDATA            (RBSYS_BASICATTR_SV_RW)
    #define RBSYS_SVFLASH           (RBSYS_BASICATTR_SV_RX)
    #define RBSYS_WHOLERAM          (RBSYS_BASICATTR_UM_R | RBSYS_BASICATTR_SV_RW)
  #else
    // SVP restrictions off: leave RAM executable
    #define RBSYS_USERSTACK         (RBSYS_BASICATTR_UM_RW | RBSYS_BASICATTR_SV_RWX)
    #define RBSYS_USERDATA          (RBSYS_BASICATTR_UM_RWX | RBSYS_BASICATTR_SV_RWX)
    #define RBSYS_USERFLASH         (RBSYS_BASICATTR_UM_RX | RBSYS_BASICATTR_SV_RX)
    #define RBSYS_SVDATA            (RBSYS_BASICATTR_SV_RWX)
    #define RBSYS_SVFLASH           (RBSYS_BASICATTR_SV_RX)
    #define RBSYS_WHOLERAM          (RBSYS_BASICATTR_UM_R | RBSYS_BASICATTR_SV_RWX)
  #endif

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    /* Renesas P1x specific MPU driver definitions */
    /* Register MPATn */
    #define RBSYS_MPU_ACCESS_G       (1U<<6)
    /* Default MPU attribute value for each region */
    #define RBSYS_MPU_ATTR_DEFAULT     RBSYS_MPU_ACCESS_G  /* G must be always set. When this bit is set to 1, the ASID bit has no effect on the area-matching condition. */
  #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
    /* Renesas U2x specific MPU driver definitions */
    /* U2x MPAT bits */
    #define RBSYS_MPU_ACCESS_RG      ((uint32) 1U<<14) // controls execution and read permissions for any SPID. 1 == Execution and reading by any SPID
    #define RBSYS_MPU_ACCESS_WG      ((uint32) 1U<<15) // controls write permission for any SPID. 1 == Writing by any SPID is enabled
    /* Default MPU attribute value for each region */
    #define RBSYS_MPU_ATTR_DEFAULT     (RBSYS_MPU_ACCESS_RG | RBSYS_MPU_ACCESS_WG) /* RG and WG must always be set to turn off SPID awareness */
  #endif

  /**
  mpu regions Renesas P1x:
    - Region 0:  Supervisor execution restriction region: RBFS_TPSWSVPRestrictions deactivated (MPM.SVP==0) => not needed.
                                                          RBFS_TPSWSVPRestrictions activated   (MPM.SVP==1) => supervisor rw
    - Region 1:  flash bank 0: user rd/ex: for TPSW kill and const read
    - Region 2:  flash bank 1: user rd/ex: for TPSW kill and const read
    ---> Remark: Flash banks 0 and 1 are having a address gap in between. Therefore 2 regions must be used.
    - Region 3:  whole global ram (user rd-only)
    - Region 4:  whole local ram0 (user rd-only)
    - Region 5:  whole local ram1 (user rd-only)
    - Region 6:  (user rw) stack
    - Region 7:  (user rw) mpu table entry 0
    - Region 8:  (user rw) mpu table entry 1
    - Region 9:  (user rw) mpu table entry 2
    - Region 10: (user rw) mpu table entry 3
  **/

  #define RBSYS_MPU_REGION_SV_EXEC_RESTRICTION      0UL
  #define RBSYS_MPU_REGION_FLASH_0                  1UL
  #define RBSYS_MPU_REGION_FLASH_1                  2UL
  #define RBSYS_MPU_REGION_GRAM                     3UL
  #define RBSYS_MPU_REGION_LRAM0                    4UL
  #define RBSYS_MPU_REGION_LRAM1                    5UL
  #define RBSYS_MPU_REGION_STACK                    6UL

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      #define RBSYS_MPU_REGION_FIRSTDATA         7UL
  #endif

  /**
    mpu regions Renesas U2A:
      - Region 0:  Supervisor execution restriction region: RBFS_TPSWSVPRestrictions deactivated (MPM.SVP==0) => not needed.
                                                            RBFS_TPSWSVPRestrictions activated   (MPM.SVP==1) => supervisor rw
      - Region 1:  flash bank 0: user rd/ex: for TPSW kill and const read
      ---> Remark: Flash banks 0..3 are consecutive in the address map on U2A. Could be combined to 1 region if required.
      - Region 2:  flash bank 1: user rd/ex: for TPSW kill and const read
      - Region 3:  whole global ram (user rd-only) - CRAM0
      - Region 4:  whole local ram0 (user rd-only)
      - Region 5:  whole local ram1 (user rd-only)
      - Region 6:  (user rw) stack
      - Region 7:  Cluster RAM 1 (user rd-only) - CRAM1
      - Region 8:  Cluster RAM 2 (user rd-only) - CRAM2
      - Region 9:  Cluster RAM 3 (user rd-only) - CRAM3
      - Region 10: flash bank 2: user rd/ex: for TPSW kill and const read
      - Region 11: flash bank 3: user rd/ex: for TPSW kill and const read
      - Region 12: (user rw) mpu table entry 0
      - Region 13: (user rw) mpu table entry 1
      - Region 14: (user rw) mpu table entry 2
      - Region 15: (user rw) mpu table entry 3
  **/

  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      #define RBSYS_MPU_REGION_CLUSTERRAM1       7UL
      #define RBSYS_MPU_REGION_CLUSTERRAM2       8UL
      #define RBSYS_MPU_REGION_CLUSTERRAM3       9UL
      #define RBSYS_MPU_REGION_FLASH_2           10UL
      #define RBSYS_MPU_REGION_FLASH_3           11UL
      #define RBSYS_MPU_REGION_FIRSTDATA         12UL
  #endif

  /* User data mpu table regions */
  #define RBSYS_MPU_NUMBER_DATAREGIONS 4UL

  #define RBSYS_MPU_REGION_LASTDATA      (RBSYS_MPU_REGION_FIRSTDATA + RBSYS_MPU_NUMBER_DATAREGIONS - 1)
  #define RBSYS_MPU_REGION_DATA0         (RBSYS_MPU_REGION_FIRSTDATA + 0UL)
  #define RBSYS_MPU_REGION_DATA1         (RBSYS_MPU_REGION_FIRSTDATA + 1UL)
  #define RBSYS_MPU_REGION_DATA2         (RBSYS_MPU_REGION_FIRSTDATA + 2UL)
  #define RBSYS_MPU_REGION_DATA3         (RBSYS_MPU_REGION_FIRSTDATA + 3UL)

  /* Type definitions */
  typedef struct {
      uint32 region;
      uint32 start;
      uint32 end;
      uint32 attr;
  } RBSYS_MpuRegion_t;
  #define RBSYS_MPU_REGION_SIZE 16
  static_assert(RBSYS_MPU_REGION_SIZE == sizeof(RBSYS_MpuRegion_t), "RBSYS_MPU_REGION_SIZE is defined incorrectly");

  extern const RBSYS_MpuRegion_t RBSYS_MpuRegionConfig[];
  extern const uint32 RBSYS_MpuRegionConfigSize;

  extern void RBSYS_CoreMpu_SetRegion(const RBSYS_MpuRegion_t* mpuCore_p);
  extern void RBSYS_CoreMpu_SetRegionAttr(uint32 mpu_region, uint32 attr);

  #define RBSYS_MPM_HVL           (1U<<2)
  #define RBSYS_MPM_SVP           (1U<<1)
  #define RBSYS_MPM_MPE           (1U<<0)

  #if (RBFS_TPSWSVPRestrictions == RBFS_TPSWSVPRestrictions_ON)
    // SVP restrictions on: MPU active in supervisor mode, RAM not executable

    // MPM.SVP=1 (Restrict access according to the SX, SW, and SR bits even in SV mode),
    // MPM.MPE=1 (enable), MPM.HVL=0 (no hypervisor)
    #define RBSYS_MPM_BASICVALUE    (RBSYS_MPM_MPE | RBSYS_MPM_SVP)
  #else
    // SVP restrictions off: leave RAM executable

    // MPM.SVP=0 (supervisor all access), MPM.MPE=1 (enable), MPM.HVL=0 (no hypervisor)
    #define RBSYS_MPM_BASICVALUE    RBSYS_MPM_MPE
  #endif

  /**************************************************************************
  ** Configuration of the core local mpu.                                  *
  ** Initialize region 1-5. They won't be changed during runtime.          *
  ** Must be called in every core at PreOs.                                *
  **                                                                       *
  ** Hint: RBLCF_getEndAddress_xxx() returns the first 32 bit aligned      *
  **       address which does not belong to the area any more.             *
  **       mpuCoreConfig.endadr is the last 32 bit address which belongs   *
  **       to the mpu channel range.                                       *
  ** Hint: Access to inactive banks must be restricted to supervisor mode. *
  **       Access in user mode is not allowed, because the banks could be  *
  **       erased (due to FOTA concept) and all 1s (data + ecc bits). When *
  **       read, this leads to an ECC failure with complete degradation of *
  **       the system.                                                     *
  **                                                                       *
  **************************************************************************/
#if(RBFS_SysEnvironment == RBFS_SysEnvironment_Target)
  static void RBSYS_CoreMpu_Init(void);
  asm void RBSYS_CoreMpu_Init(void)
  {
    #if(RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      mov       0, r11                          -- set iteration count to 0
      mov       _RBSYS_MpuRegionConfigSize, r12 -- move address of RBSYS_MpuRegionConfigSize into r12
      ld.w      0[r12], r12                     -- load content of RBSYS_MpuRegionConfigSize into r12
      mov       _RBSYS_MpuRegionConfig, r6      -- move address of RBSYS_MpuRegionConfig into r6

set_region_loop:
      -- loop over RBSYS_MpuRegionConfig and set MPU regions accordingly
      jarl      set_region, lp                  -- set MPU register according to RBSYS_MpuRegionConfig element pointed to by r6
      add       1, r11                          -- increment iteration count
      addi      RBSYS_MPU_REGION_SIZE, r6, r6   -- increment address/pointer into RBSYS_MpuRegionConfig to next element
      cmp       r11, r12                        -- iteration count == RBSYS_MpuRegionConfigSize
      bne       set_region_loop                 -- if end of RBSYS_MpuRegionConfig not reached continue in loop

      -- activate the MPU (register MPM -> RegId=0, SelId=5):
      --     MPM.MPE=1 (enable), MPM.HVL=0 (no hypervisor)
      --     MPM.SVP=0/1 depending to RBFS_TPSWSVPRestrictions setting
      mov       RBSYS_MPM_BASICVALUE, r6
      ldsr      r6, MPM, 5
      -- initialize MEA and MEI with 0 in order to have valid initial values
      ldsr      zero, MEA, 2
      ldsr      zero, MEI, 2
      -- introduce sync instructions after updating MPU registers -> see "RH850G3M User's Manual: Hardware" revision 1.30, p.255 "System Register Hazards"
      syncp
      synci
      jr        RBSYS_CoreMpu_Init_exit

set_region:
      -- set MPU register according to RBSYS_MpuRegionConfig element pointed to by r6
      ld.w      0x0[r6], r7                -- load member region
      ld.w      0x4[r6], r8                -- load member start
      ld.w      0x8[r6], r9                -- load member end
      ld.w      0xC[r6], r10               -- load member attr
      shl       2, r7                      -- multiply region index with 2 to calculate offset in jump table, assumption: each jr has size 2 bytes
      jmp       set_region_jump_table[r7]  -- jump into jump table
set_region_jump_table:
      -- jump table for configuring MPU registers for a specific region
      jr        set_region_0
      jr        set_region_1
      jr        set_region_2
      jr        set_region_3
      jr        set_region_4
      jr        set_region_5
      jr        set_region_6
      jr        set_region_7
      jr        set_region_8
      jr        set_region_9
      jr        set_region_10
      jr        set_region_11
      jr        set_region_12
      jr        set_region_13
      jr        set_region_14
      jr        set_region_15
set_region_0:
      ldsr      r8, MPLA0, 6
      ldsr      r9, MPUA0, 6
      ldsr      r10, MPAT0, 6
      jmp       [lp]
set_region_1:
      ldsr      r8, MPLA1, 6
      ldsr      r9, MPUA1, 6
      ldsr      r10, MPAT1, 6
      jmp       [lp]
set_region_2:
      ldsr      r8, MPLA2, 6
      ldsr      r9, MPUA2, 6
      ldsr      r10, MPAT2, 6
      jmp       [lp]
set_region_3:
      ldsr      r8, MPLA3, 6
      ldsr      r9, MPUA3, 6
      ldsr      r10, MPAT3, 6
      jmp       [lp]
set_region_4:
      ldsr      r8, MPLA4, 6
      ldsr      r9, MPUA4, 6
      ldsr      r10, MPAT4, 6
      jmp       [lp]
set_region_5:
      ldsr      r8, MPLA5, 6
      ldsr      r9, MPUA5, 6
      ldsr      r10, MPAT5, 6
      jmp       [lp]
set_region_6:
      ldsr      r8, MPLA6, 6
      ldsr      r9, MPUA6, 6
      ldsr      r10, MPAT6, 6
      jmp       [lp]
set_region_7:
      ldsr      r8, MPLA7, 6
      ldsr      r9, MPUA7, 6
      ldsr      r10, MPAT7, 6
      jmp       [lp]
set_region_8:
      ldsr      r8, MPLA8, 7
      ldsr      r9, MPUA8, 7
      ldsr      r10, MPAT8, 7
      jmp       [lp]
set_region_9:
      ldsr      r8, MPLA9, 7
      ldsr      r9, MPUA9, 7
      ldsr      r10, MPAT9, 7
      jmp       [lp]
set_region_10:
      ldsr      r8, MPLA10, 7
      ldsr      r9, MPUA10, 7
      ldsr      r10, MPAT10, 7
      jmp       [lp]
set_region_11:
      ldsr      r8, MPLA11, 7
      ldsr      r9, MPUA11, 7
      ldsr      r10, MPAT11, 7
      jmp       [lp]
set_region_12:
      ldsr      r8, MPLA12, 7
      ldsr      r9, MPUA12, 7
      ldsr      r10, MPAT12, 7
      jmp       [lp]
set_region_13:
      ldsr      r8, MPLA13, 7
      ldsr      r9, MPUA13, 7
      ldsr      r10, MPAT13, 7
      jmp       [lp]
set_region_14:
      ldsr      r8, MPLA14, 7
      ldsr      r9, MPUA14, 7
      ldsr      r10, MPAT14, 7
      jmp       [lp]
set_region_15:
      ldsr      r8, MPLA15, 7
      ldsr      r9, MPUA15, 7
      ldsr      r10, MPAT15, 7
      jmp       [lp]
RBSYS_CoreMpu_Init_exit:

    #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      mov       _RBSYS_MpuRegionConfig, r6      -- set iteration count to 0
      mov       0, r11                          -- move address of RBSYS_MpuRegionConfigSize into r12
      mov       _RBSYS_MpuRegionConfigSize, r12 -- load content of RBSYS_MpuRegionConfigSize into r12
      ld.w      0[r12], r12                     -- move address of RBSYS_MpuRegionConfig into r6

set_region_loop:
      -- loop over RBSYS_MpuRegionConfig and set MPU regions accordingly
      ld.w      0x0[r6], r7                   -- load member region
      ldsr      r7, MPIDX, 5                  -- write region to MPIDX
      ld.w      0x4[r6], r7                   -- load member start
      ldsr      r7, MPLA, 5                   -- write start to MPLA
      ld.w      0x8[r6], r7                   -- load member end
      ldsr      r7, MPUA, 5                   -- write end to MPUA
      ld.w      0xC[r6], r7                   -- load member attr
      ldsr      r7, MPAT, 5                   -- write attr to MPAT
      add       1, r11                        -- increment iteration count
      addi      RBSYS_MPU_REGION_SIZE, r6, r6 -- increment address/pointer into RBSYS_MpuRegionConfig to next element
      cmp       r11, r12                      -- iteration count == RBSYS_MpuRegionConfigSize
      bne       set_region_loop               -- if end of RBSYS_MpuRegionConfig not reached continue in loop

      -- activate the MPU (register MPM -> RegId=0, SelId=5):
      --     MPM.MPE=1 (enable), MPM.HVL=0 (no hypervisor)
      --     MPM.SVP=0/1 depending to RBFS_TPSWSVPRestrictions setting
      mov       RBSYS_MPM_BASICVALUE, r6
      ldsr      r6, MPM, 5
      -- initialize MEA and MEI with 0 in order to have valid initial values
      ldsr      zero, MEA, 2
      ldsr      zero, MEI, 2
      -- introduce sync instructions after updating MPU registers -> see "RH850/U2A-EVA Group User’s Manual: Hardware" revision 1.10, "3.2.7.3 Hazard Management after System Register Update"
      synci
    #endif
  }
#else
  extern void RBSYS_CoreMpu_Init(void);
#endif


#endif

#if ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_TPSWSVPRestrictions == RBFS_TPSWSVPRestrictions_ON))
      /**
       * @brief Procedure for disabling MPU restrictions on executing from RAM
       *
       * Should only be used when reprogramming with ReprogDriver on P1x
       */
      extern void RBSYS_CoreMpu_AllowRamExecution(void);
#endif

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
