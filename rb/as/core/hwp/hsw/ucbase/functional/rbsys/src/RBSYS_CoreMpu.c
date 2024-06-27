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
#include <assert.h>
#include "RBSYS_Intrinsics.h"
#include "RBLCF_MemoryMap.h"


/* realized interfaces */
#include "RBSYS_CoreMpu.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TPSWSVPRestrictions,
                          RBFS_TPSWSVPRestrictions_OFF,
                          RBFS_TPSWSVPRestrictions_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasP1xGRAM,
                          RBFS_RenesasP1xGRAM_OFF,
                          RBFS_RenesasP1xGRAM_ON);

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

RB_ASSERT_SWITCH_SETTINGS(RBFS_RenesasU2cCRAM0,
                          RBFS_RenesasU2cCRAM0_ON,
                          RBFS_RenesasU2cCRAM0_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_LocalRamCore1Support,
                          RBFS_LocalRamCore1Support_OFF,
                          RBFS_LocalRamCore1Support_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_FlashBank0Support,
                          RBFS_FlashBank0Support_OFF,
                          RBFS_FlashBank0Support_INACTIVE,
                          RBFS_FlashBank0Support_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_FlashBank1Support,
                          RBFS_FlashBank1Support_OFF,
                          RBFS_FlashBank1Support_INACTIVE,
                          RBFS_FlashBank1Support_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_FlashBank2Support,
                          RBFS_FlashBank2Support_ON,
                          RBFS_FlashBank2Support_INACTIVE,
                          RBFS_FlashBank2Support_OFF);

RB_ASSERT_SWITCH_SETTINGS(RBFS_FlashBank3Support,
                          RBFS_FlashBank3Support_ON,
                          RBFS_FlashBank3Support_INACTIVE,
                          RBFS_FlashBank3Support_OFF);


#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

  RB_ASSERT_SWITCH_SETTINGS(RBFS_TargetDevice,
                            RBFS_TargetDevice_STMP6);

  RB_ASSERT_SWITCH_SETTINGS(RBFS_EmulationDevice,
                            RBFS_EmulationDevice_None,
                            RBFS_EmulationDevice_STMP7ED);

  #define GET_END_ADDRESS(start, size) ((start) + (size) - 1 )
  #define NVM_0_0_start      (0x28000000)
  #define NVM_0_1_start      (0x28400000)
  #define NVM_1_0_start      (0x28800000)
  #define NVM_1_1_start      (0x28C00000)
  #define NVM_2_0_start      (0x29000000)
  #define NVM_2_1_start      (0x29400000)

  #define NVM_0_0_size       (3840*1024)
  #define NVM_0_1_size       (3840*1024)
  #if(RBFS_EmulationDevice == RBFS_EmulationDevice_STMP7ED)
    #define NVM_1_0_size     (4096*1024)
    #define NVM_1_1_size     (4096*1024)
  #elif(RBFS_TargetDevice == RBFS_TargetDevice_STMP6)
    #define NVM_1_0_size     (2048*1024)
    #define NVM_1_1_size     (2048*1024)
  #endif
  #define NVM_2_0_size       (2048*1024)
  #define NVM_2_1_size       (2048*1024)

  #define NVM_0_0_end GET_END_ADDRESS(NVM_0_0_start, NVM_0_0_size)
  #define NVM_0_1_end GET_END_ADDRESS(NVM_0_1_start, NVM_0_1_size)
  #define NVM_1_0_end GET_END_ADDRESS(NVM_1_0_start, NVM_1_0_size)
  #define NVM_1_1_end GET_END_ADDRESS(NVM_1_1_start, NVM_1_1_size)
  #define NVM_2_0_end GET_END_ADDRESS(NVM_2_0_start, NVM_2_0_size)
  #define NVM_2_1_end GET_END_ADDRESS(NVM_2_1_start, NVM_2_1_size)

  #define RBSYS_CoreMPU_Executable    (0x0u)
  #define RBSYS_CoreMPU_NotExecutable (0x1u)

  #define RBSYS_CoreMPU_ReadWritePrivileged (0x0u)
  #define RBSYS_CoreMPU_ReadWriteAll        (0x1u)
  #define RBSYS_CoreMPU_ReadOnlyPrivileged  (0x2u)
  #define RBSYS_CoreMPU_ReadOnlyAll         (0x3u)

  #define RBSYS_CoreMPU_NonSharable   (0x0u)
  #define RBSYS_CoreMPU_OuterSharable (0x2u)
  #define RBSYS_CoreMPU_InnerSharable (0x3u)

  #define RBSYS_CoreMPU_MemoryType1_CodeFlashRead     ((RBSYS_CoreMPU_NonSharable   << 3) | (RBSYS_CoreMPU_ReadOnlyAll  << 1) | RBSYS_CoreMPU_Executable)
  #define RBSYS_CoreMPU_MemoryType2_CodeFlashRead     (RBSYS_CoreMPU_MAIR_ReadOnlyFlash_Index       << 1)

  #define RBSYS_CoreMPU_MemoryType1_RAM               ((RBSYS_CoreMPU_OuterSharable << 3) | (RBSYS_CoreMPU_ReadWriteAll << 1) | RBSYS_CoreMPU_NotExecutable)
  #define RBSYS_CoreMPU_MemoryType2_RAM               (RBSYS_CoreMPU_MAIR_WritableFlashAndRAM_Index << 1)

  #define RBSYS_CoreMPU_MemoryType1_Peripherals       ((RBSYS_CoreMPU_OuterSharable << 3) | (RBSYS_CoreMPU_ReadWriteAll << 1) | RBSYS_CoreMPU_NotExecutable)
  #define RBSYS_CoreMPU_MemoryType2_Peripherals       (RBSYS_CoreMPU_MAIR_Peripherals_Index         << 1)

  #define RBSYS_CoreMPU_MemoryType1_OverlayRAM        ((RBSYS_CoreMPU_OuterSharable << 3) | (RBSYS_CoreMPU_ReadWriteAll << 1) | RBSYS_CoreMPU_Executable)
  #define RBSYS_CoreMPU_MemoryType2_OverlayRAM        (RBSYS_CoreMPU_MAIR_WritableFlashAndRAM_Index << 1)

  #define RBSYS_CoreMPU_MemoryType1_CodeFlashWrite    ((RBSYS_CoreMPU_NonSharable   << 3) | (RBSYS_CoreMPU_ReadWriteAll << 1) | RBSYS_CoreMPU_NotExecutable)
  #define RBSYS_CoreMPU_MemoryType2_CodeFlashWrite    (RBSYS_CoreMPU_MAIR_WritableFlashAndRAM_Index << 1)

  #define RBSYS_CoreMPU_MemoryType1_DataFlashWrite    ((RBSYS_CoreMPU_NonSharable   << 3) | (RBSYS_CoreMPU_ReadWriteAll << 1) | RBSYS_CoreMPU_NotExecutable)
  #define RBSYS_CoreMPU_MemoryType2_DataFlashWrite    (RBSYS_CoreMPU_MAIR_WritableFlashAndRAM_Index << 1)

  #define RBSYS_CoreMPU_MemoryType1_DataFlashRead     ((RBSYS_CoreMPU_NonSharable   << 3) | (RBSYS_CoreMPU_ReadOnlyAll  << 1) | RBSYS_CoreMPU_NotExecutable)
  #define RBSYS_CoreMPU_MemoryType2_DataFlashRead     (RBSYS_CoreMPU_MAIR_WritableFlashAndRAM_Index << 1)

  // #pragma remap to pflash
  const RBSYS_MpuRegion_t RBSYS_MpuRegionConfig[] = {
    // Code NVM Read: non shareable, RO any level, execution allowed (XN = 0), Attr Index 2
    {NVM_0_0_start, NVM_0_0_size, NVM_0_0_end, RBSYS_CoreMPU_MemoryType1_CodeFlashRead, RBSYS_CoreMPU_MemoryType2_CodeFlashRead},
    {NVM_0_1_start, NVM_0_1_size, NVM_0_1_end, RBSYS_CoreMPU_MemoryType1_CodeFlashRead, RBSYS_CoreMPU_MemoryType2_CodeFlashRead},
    {NVM_1_0_start, NVM_1_0_size, NVM_1_0_end, RBSYS_CoreMPU_MemoryType1_CodeFlashRead, RBSYS_CoreMPU_MemoryType2_CodeFlashRead},
    {NVM_1_1_start, NVM_1_1_size, NVM_1_1_end, RBSYS_CoreMPU_MemoryType1_CodeFlashRead, RBSYS_CoreMPU_MemoryType2_CodeFlashRead},
    {NVM_2_0_start, NVM_2_0_size, NVM_2_0_end, RBSYS_CoreMPU_MemoryType1_CodeFlashRead, RBSYS_CoreMPU_MemoryType2_CodeFlashRead},
    {NVM_2_1_start, NVM_2_1_size, NVM_2_1_end, RBSYS_CoreMPU_MemoryType1_CodeFlashRead, RBSYS_CoreMPU_MemoryType2_CodeFlashRead},

    // Code NVM ECC test area for FEI tests, same as Code NVM Read
    {0x29FF8000u, 0x6000, 0x29FFDFFF, RBSYS_CoreMPU_MemoryType1_CodeFlashRead, RBSYS_CoreMPU_MemoryType2_CodeFlashRead},

    // CRAM + System RAM: outer shareable, RW any level, execution not allowed (XN = 1), Attr Index 3
    #if(RBFS_EmulationDevice == RBFS_EmulationDevice_STMP7ED)
      {0x60000000, 0x4440000, 0x6443FFFF, RBSYS_CoreMPU_MemoryType1_RAM, RBSYS_CoreMPU_MemoryType2_RAM},
    #elif(RBFS_TargetDevice == RBFS_TargetDevice_STMP6)
      {0x60000000, 0x4420000, 0x6441FFFF, RBSYS_CoreMPU_MemoryType1_RAM, RBSYS_CoreMPU_MemoryType2_RAM},
    #endif

    // TCMs: outer shareable, RW any level, execution not allowed (XN = 1), Attr Index 3
    #if((RBFS_EmulationDevice == RBFS_EmulationDevice_STMP7ED) || (RBFS_TargetDevice == RBFS_TargetDevice_STMP6))
      {0x68000000, 0x2604000, 0x6A603FFF, RBSYS_CoreMPU_MemoryType1_RAM, RBSYS_CoreMPU_MemoryType2_RAM},
    #endif

    // LLPP + Peripherals: outer shareable, RW any level, execution not allowed (XN = 1), Attr Index 0
    #if((RBFS_EmulationDevice == RBFS_EmulationDevice_STMP7ED) || (RBFS_TargetDevice == RBFS_TargetDevice_STMP6))
      {0x6C000000, 0x14000000, 0x7FFFFFFF, RBSYS_CoreMPU_MemoryType1_Peripherals, RBSYS_CoreMPU_MemoryType2_Peripherals},
    #endif

    // Overlay RAM: outer shareable, RW any level, execution allowed (XN = 0), Attr Index 3
    #if(RBFS_EmulationDevice == RBFS_EmulationDevice_STMP7ED)
      {0x50000000, 0x1480000, 0x5147FFFF, RBSYS_CoreMPU_MemoryType1_OverlayRAM, RBSYS_CoreMPU_MemoryType2_OverlayRAM},
    #elif(RBFS_TargetDevice == RBFS_TargetDevice_STMP6)
      {0x50000000, 0x1404000, 0x51403FFF, RBSYS_CoreMPU_MemoryType1_OverlayRAM, RBSYS_CoreMPU_MemoryType2_OverlayRAM},
    #endif

    // DSPH + DME RAM: outer shareable, RW any level, execution allowed (XN = 0), Attr Index 3
    #if(RBFS_EmulationDevice == RBFS_EmulationDevice_STMP7ED)
      {0x2010000, 0x1E510000, 0x2051FFFF, RBSYS_CoreMPU_MemoryType1_RAM, RBSYS_CoreMPU_MemoryType2_RAM},
    #elif(RBFS_TargetDevice == RBFS_TargetDevice_STMP6)
      {0x2010000, 0x1E4F0C00, 0x20500BFF, RBSYS_CoreMPU_MemoryType1_RAM, RBSYS_CoreMPU_MemoryType2_RAM},
    #endif

    // Code NVM Write: non shareable, RW any level, execution forbidden (XN = 1), Attr Index 3
    #if((RBFS_EmulationDevice == RBFS_EmulationDevice_STMP7ED) || (RBFS_TargetDevice == RBFS_TargetDevice_STMP6))
      {0x30000000, 0x1600000, 0x315FFFFF, RBSYS_CoreMPU_MemoryType1_CodeFlashWrite, RBSYS_CoreMPU_MemoryType2_CodeFlashWrite},
    #endif

    // Data NVM Write: non shareable, RW any level, execution forbidden (XN = 1), Attr Index 3
    #if((RBFS_EmulationDevice == RBFS_EmulationDevice_STMP7ED) || (RBFS_TargetDevice == RBFS_TargetDevice_STMP6))
      {0x31E00000, 0x80000, 0x31E7FFFF, RBSYS_CoreMPU_MemoryType1_DataFlashWrite, RBSYS_CoreMPU_MemoryType2_DataFlashWrite},
    #endif

    // Data NVM Read: non shareable, RO any level, execution forbidden (XN = 1), Attr Index 3
    #if((RBFS_EmulationDevice == RBFS_EmulationDevice_STMP7ED) || (RBFS_TargetDevice == RBFS_TargetDevice_STMP6))
      {0x29E00000, 0x80000, 0x29E7FFFF, RBSYS_CoreMPU_MemoryType1_DataFlashRead, RBSYS_CoreMPU_MemoryType2_DataFlashRead},
    #endif
  };
  #define RBSYS_MPUREGIONCONFIGSIZE (sizeof(RBSYS_MpuRegionConfig)/sizeof(RBSYS_MpuRegionConfig[0]))
  const uint32 RBSYS_MpuRegionConfigSize = RBSYS_MPUREGIONCONFIGSIZE;

  static_assert(sizeof(RBSYS_MpuRegionConfig[0]) == 20, "Size of MpuRegionConfig elements is not correct");
  static_assert(RBSYS_MPUREGIONCONFIGSIZE <= 24, "Number of statically configured MPU regions exceeds number of available MPU regions in hardware.");

#elif (((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  const RBSYS_MpuRegion_t RBSYS_MpuRegionConfig[] = {
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A)
      // SVP restrictions OFF: can be left as it is, because region is unused.
      #if (RBFS_TPSWSVPRestrictions == RBFS_TPSWSVPRestrictions_ON)
        // SVP restrictions ON: grant supervisor RW (no X) to region encompassing everything except active code flash
        // todo: RBLCF_getEndAddress_PFLASH() returns the end of active PFLASH, inactive PFLASH is contained in this range and therefore writable by supervisor
        {RBSYS_MPU_REGION_SV_EXEC_RESTRICTION, RBLCF_getEndAddress_PFLASH(), 0xfffffffcu, RBSYS_MPU_ATTR_DEFAULT | RBSYS_BASICATTR_SV_RW | RBSYS_MPU_ACCESS_E},
      #endif

      // flash bank 0
      #if (RBFS_FlashBank0Support == RBFS_FlashBank0Support_ON)
        {RBSYS_MPU_REGION_FLASH_0, RBLCF_getStartAddress_PFLASH_ActiveBank0(), RBLCF_getEndAddress_PFLASH_ActiveBank0() - 4, RBSYS_MPU_ATTR_DEFAULT | RBSYS_USERFLASH | RBSYS_MPU_ACCESS_E},
      #elif (RBFS_FlashBank0Support == RBFS_FlashBank0Support_INACTIVE)
        //todo: inactive bank should be read only
        {RBSYS_MPU_REGION_FLASH_0, RBLCF_getStartAddress_PFLASH_InactiveBank0(), RBLCF_getEndAddress_PFLASH_InactiveBank0() - 4, RBSYS_MPU_ATTR_DEFAULT | RBSYS_SVFLASH | RBSYS_MPU_ACCESS_E},
      #endif
      // flash bank 1
      #if (RBFS_FlashBank1Support == RBFS_FlashBank1Support_ON)
        {RBSYS_MPU_REGION_FLASH_1, RBLCF_getStartAddress_PFLASH_ActiveBank1(), RBLCF_getEndAddress_PFLASH_ActiveBank1() - 4, RBSYS_MPU_ATTR_DEFAULT | RBSYS_USERFLASH | RBSYS_MPU_ACCESS_E},
      #elif (RBFS_FlashBank1Support == RBFS_FlashBank1Support_INACTIVE)
        {RBSYS_MPU_REGION_FLASH_1, RBLCF_getStartAddress_PFLASH_InactiveBank1(), RBLCF_getEndAddress_PFLASH_InactiveBank1() - 4, RBSYS_MPU_ATTR_DEFAULT | RBSYS_SVFLASH | RBSYS_MPU_ACCESS_E},
      #endif
      // flash bank 2 (Renesas U2A only)
      #if (RBFS_FlashBank2Support == RBFS_FlashBank2Support_ON)
        {RBSYS_MPU_REGION_FLASH_2, RBLCF_getStartAddress_PFLASH_ActiveBank2(), RBLCF_getEndAddress_PFLASH_ActiveBank2() - 4, RBSYS_MPU_ATTR_DEFAULT | RBSYS_USERFLASH | RBSYS_MPU_ACCESS_E},
      #elif (RBFS_FlashBank2Support == RBFS_FlashBank2Support_INACTIVE)
        {RBSYS_MPU_REGION_FLASH_2, RBLCF_getStartAddress_PFLASH_InactiveBank2(), RBLCF_getEndAddress_PFLASH_InactiveBank2() - 4, RBSYS_MPU_ATTR_DEFAULT | RBSYS_SVFLASH | RBSYS_MPU_ACCESS_E},
      #endif
      // flash bank 3 (Renesas U2A only)
      #if (RBFS_FlashBank3Support == RBFS_FlashBank3Support_ON)
        {RBSYS_MPU_REGION_FLASH_3, RBLCF_getStartAddress_PFLASH_ActiveBank3(), RBLCF_getEndAddress_PFLASH_ActiveBank3() - 4, RBSYS_MPU_ATTR_DEFAULT | RBSYS_USERFLASH | RBSYS_MPU_ACCESS_E},
      #elif (RBFS_FlashBank3Support == RBFS_FlashBank3Support_INACTIVE)
        {RBSYS_MPU_REGION_FLASH_3, RBLCF_getStartAddress_PFLASH_InactiveBank3(), RBLCF_getEndAddress_PFLASH_InactiveBank3() - 4, RBSYS_MPU_ATTR_DEFAULT | RBSYS_SVFLASH | RBSYS_MPU_ACCESS_E},
      #endif

      // whole local ram 0
      {RBSYS_MPU_REGION_LRAM0, RBLCF_getStartAddress_LRAM_CPU0(), RBLCF_getEndAddress_LRAM_CPU0_forRAMSafety() - 4, RBSYS_MPU_ATTR_DEFAULT | RBSYS_WHOLERAM | RBSYS_MPU_ACCESS_E},
      // whole local ram 1
      #if (RBFS_LocalRamCore1Support == RBFS_LocalRamCore1Support_ON)
        {RBSYS_MPU_REGION_LRAM1, RBLCF_getStartAddress_LRAM_CPU1(), RBLCF_getEndAddress_LRAM_CPU1_forRAMSafety() - 4, RBSYS_MPU_ATTR_DEFAULT | RBSYS_WHOLERAM | RBSYS_MPU_ACCESS_E},
      #endif

      // whole global ram (P1x) or Cluster 0 RAM (U2A)
      #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
        {RBSYS_MPU_REGION_GRAM, RBLCF_getStartAddress_GRAM(), RBLCF_getEndAddress_GRAM_forRAMSafety() - 4, RBSYS_MPU_ATTR_DEFAULT | RBSYS_WHOLERAM | RBSYS_MPU_ACCESS_E},
      #elif ((RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON) || (RBFS_RenesasU2cCRAM0 == RBFS_RenesasU2cCRAM0_ON))
        {RBSYS_MPU_REGION_GRAM, RBLCF_getStartAddress_CRAM0(), RBLCF_getEndAddress_CRAM0_forRAMSafety() - 4, RBSYS_MPU_ATTR_DEFAULT | RBSYS_WHOLERAM | RBSYS_MPU_ACCESS_E},
      #endif
      // Cluster 1 RAM
      #if (RBFS_RenesasU2aCRAM1 == RBFS_RenesasU2aCRAM1_ON)
        {RBSYS_MPU_REGION_CLUSTERRAM1, RBLCF_getStartAddress_CRAM1(), RBLCF_getEndAddress_CRAM1_forRAMSafety() - 4, RBSYS_MPU_ATTR_DEFAULT | RBSYS_WHOLERAM | RBSYS_MPU_ACCESS_E},
      #endif
      // Cluster 2 RAM
      #if (RBFS_RenesasU2aCRAM2 == RBFS_RenesasU2aCRAM2_ON)
        {RBSYS_MPU_REGION_CLUSTERRAM2, RBLCF_getStartAddress_CRAM2(), RBLCF_getEndAddress_CRAM2_forRAMSafety() - 4, RBSYS_MPU_ATTR_DEFAULT | RBSYS_WHOLERAM | RBSYS_MPU_ACCESS_E},
      #endif
      // Cluster 3 RAM
      #if (RBFS_RenesasU2aCRAM3 == RBFS_RenesasU2aCRAM3_ON)
        {RBSYS_MPU_REGION_CLUSTERRAM3, RBLCF_getStartAddress_CRAM3(), RBLCF_getEndAddress_CRAM3_forRAMSafety() - 4, RBSYS_MPU_ATTR_DEFAULT | RBSYS_WHOLERAM | RBSYS_MPU_ACCESS_E},
      #endif
    #else
      {0,0,0,0} // todo: dummy U2C configuration for now
    #endif
  };
  #define RBSYS_MPUREGIONCONFIGSIZE (sizeof(RBSYS_MpuRegionConfig)/sizeof(RBSYS_MpuRegionConfig[0]))
  const uint32 RBSYS_MpuRegionConfigSize = RBSYS_MPUREGIONCONFIGSIZE;

  static_assert(sizeof(RBSYS_MpuRegionConfig[0]) == 16, "Size of MpuRegionConfig elements is not correct");
  static_assert(RBSYS_MPUREGIONCONFIGSIZE <= 12, "Number of statically configured MPU regions exceeds number of available MPU regions in hardware.");


  void RBSYS_CoreMpu_SetRegion(const RBSYS_MpuRegion_t* mpuCore_p)
  {
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      switch(mpuCore_p->region)
      {
        case 0:
        {
          RBSYS_LDSR(0, 6, mpuCore_p->start);
          RBSYS_LDSR(1, 6, mpuCore_p->end);
          RBSYS_LDSR(2, 6, mpuCore_p->attr);
        } break;

        case 1:
        {
          RBSYS_LDSR(4, 6, mpuCore_p->start);
          RBSYS_LDSR(5, 6, mpuCore_p->end);
          RBSYS_LDSR(6, 6, mpuCore_p->attr);
        } break;

        case 2:
        {
          RBSYS_LDSR(8, 6, mpuCore_p->start);
          RBSYS_LDSR(9, 6, mpuCore_p->end);
          RBSYS_LDSR(10, 6, mpuCore_p->attr);
        } break;

        case 3:
        {
          RBSYS_LDSR(12, 6, mpuCore_p->start);
          RBSYS_LDSR(13, 6, mpuCore_p->end);
          RBSYS_LDSR(14, 6, mpuCore_p->attr);
        } break;

        case 4:
      {
          RBSYS_LDSR(16, 6, mpuCore_p->start);
          RBSYS_LDSR(17, 6, mpuCore_p->end);
          RBSYS_LDSR(18, 6, mpuCore_p->attr);
        } break;

        case 5:
        {
          RBSYS_LDSR(20, 6, mpuCore_p->start);
          RBSYS_LDSR(21, 6, mpuCore_p->end);
          RBSYS_LDSR(22, 6, mpuCore_p->attr);
        } break;

        case 6:
        {
          RBSYS_LDSR(24, 6, mpuCore_p->start);
          RBSYS_LDSR(25, 6, mpuCore_p->end);
          RBSYS_LDSR(26, 6, mpuCore_p->attr);
        } break;

        case 7:
        {
          RBSYS_LDSR(28, 6, mpuCore_p->start);
          RBSYS_LDSR(29, 6, mpuCore_p->end);
          RBSYS_LDSR(30, 6, mpuCore_p->attr);
        } break;

        case 8:
        {
          RBSYS_LDSR(0, 7, mpuCore_p->start);
          RBSYS_LDSR(1, 7, mpuCore_p->end);
          RBSYS_LDSR(2, 7, mpuCore_p->attr);
        } break;

        case 9:
        {
          RBSYS_LDSR(4, 7, mpuCore_p->start);
          RBSYS_LDSR(5, 7, mpuCore_p->end);
          RBSYS_LDSR(6, 7, mpuCore_p->attr);
        } break;

        case 10:
        {
          RBSYS_LDSR(8, 7, mpuCore_p->start);
          RBSYS_LDSR(9, 7, mpuCore_p->end);
          RBSYS_LDSR(10, 7, mpuCore_p->attr);
        } break;

        case 11:
        {
          RBSYS_LDSR(12, 7, mpuCore_p->start);
          RBSYS_LDSR(13, 7, mpuCore_p->end);
          RBSYS_LDSR(14, 7, mpuCore_p->attr);
        } break;

        case 12:
        {
          RBSYS_LDSR(16, 7, mpuCore_p->start);
          RBSYS_LDSR(17, 7, mpuCore_p->end);
          RBSYS_LDSR(18, 7, mpuCore_p->attr);
        } break;

        case 13:
        {
          RBSYS_LDSR(20, 7, mpuCore_p->start);
          RBSYS_LDSR(21, 7, mpuCore_p->end);
          RBSYS_LDSR(22, 7, mpuCore_p->attr);
        } break;

        case 14:
        {
          RBSYS_LDSR(24, 7, mpuCore_p->start);
          RBSYS_LDSR(25, 7, mpuCore_p->end);
          RBSYS_LDSR(26, 7, mpuCore_p->attr);
        } break;

        case 15:
        {
          RBSYS_LDSR(28, 7, mpuCore_p->start);
          RBSYS_LDSR(29, 7, mpuCore_p->end);
          RBSYS_LDSR(30, 7, mpuCore_p->attr);
        } break;

        default:
        { /* MISRA */ } break;
      }

      // introduce sync instructions after updating MPU registers -> see "RH850G3M User's Manual: Hardware" revision 1.30, p.255 "System Register Hazards"
      RBSYS_SYNCP();
      RBSYS_SYNCI();
    #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      /* MPIDX, Index of memory protection setting registers to be accessed */
      RBSYS_LDSR(16, 5, mpuCore_p->region);
      /* MPLA */
      RBSYS_LDSR(20, 5, mpuCore_p->start);
      /* MPUA */
      RBSYS_LDSR(21, 5, mpuCore_p->end);
      /* MPAT */
      RBSYS_LDSR(22, 5, mpuCore_p->attr);

      // introduce sync instructions after updating MPU registers -> see "RH850/U2A-EVA Group User’s Manual: Hardware" revision 1.10, "3.2.7.3 Hazard Management after System Register Update"
      RBSYS_SYNCI();
    #endif
  }

  void RBSYS_CoreMpu_SetRegionAttr(uint32 mpu_region, uint32 attr)
  {
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      switch(mpu_region)
      {
        case 0:
        {
          RBSYS_LDSR(2, 6, attr);
        } break;

        case 1:
        {
          RBSYS_LDSR(6, 6, attr);
        } break;

        case 2:
        {
          RBSYS_LDSR(10, 6, attr);
        } break;

        case 3:
        {
          RBSYS_LDSR(14, 6, attr);
        } break;

        case 4:
        {
          RBSYS_LDSR(18, 6, attr);
        } break;

        case 5:
        {
          RBSYS_LDSR(22, 6, attr);
        } break;

        case 6:
        {
          RBSYS_LDSR(26, 6, attr);
        } break;

        case 7:
        {
          RBSYS_LDSR(30, 6, attr);
        } break;

        case 8:
        {
          RBSYS_LDSR(2, 7, attr);
        } break;

        case 9:
        {
          RBSYS_LDSR(6, 7, attr);
        } break;

        case 10:
        {
          RBSYS_LDSR(10, 7, attr);
        } break;

        case 11:
        {
          RBSYS_LDSR(14, 7, attr);
        } break;

        case 12:
        {
          RBSYS_LDSR(18, 7, attr);
        } break;

        case 13:
        {
          RBSYS_LDSR(22, 7, attr);
        } break;

        case 14:
        {
          RBSYS_LDSR(26, 7, attr);
        } break;

        case 15:
        {
          RBSYS_LDSR(30, 7, attr);
        } break;

        default:
        { /* MISRA */ } break;
      }

      // introduce sync instructions after updating MPU registers -> see "RH850G3M User's Manual: Hardware" revision 1.30, p.255 "System Register Hazards"
      RBSYS_SYNCP();
      RBSYS_SYNCI();
    #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
      /* MPIDX, Index of memory protection setting registers to be accessed */
      RBSYS_LDSR(16, 5, mpu_region);
      /* MPAT,  Protection Area Attribute */
      RBSYS_LDSR(22, 5, attr);

      /* introduce sync instructions after updating MPU registers -> see "RH850/U2A-EVA Group User’s Manual: Hardware" revision 1.10, "3.2.7.3 Hazard Management after System Register Update" */
      RBSYS_SYNCI();
    #endif
  }

  #if ((RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) && (RBFS_TPSWSVPRestrictions == RBFS_TPSWSVPRestrictions_ON))
    void RBSYS_CoreMpu_AllowRamExecution(void)
    {
      #if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
        RBSYS_CoreMpu_SetRegionAttr(RBSYS_MPU_REGION_GRAM, RBSYS_MPU_ATTR_DEFAULT | RBSYS_BASICATTR_SV_RWX | RBSYS_MPU_ACCESS_E);
      #endif
      RBSYS_CoreMpu_SetRegionAttr(RBSYS_MPU_REGION_LRAM0, RBSYS_MPU_ATTR_DEFAULT | RBSYS_BASICATTR_SV_RWX | RBSYS_MPU_ACCESS_E);
      #if (RBFS_LocalRamCore1Support == RBFS_LocalRamCore1Support_ON)
        RBSYS_CoreMpu_SetRegionAttr(RBSYS_MPU_REGION_LRAM1, RBSYS_MPU_ATTR_DEFAULT | RBSYS_BASICATTR_SV_RWX | RBSYS_MPU_ACCESS_E);
      #endif
    }
  #endif

#endif

/** @} */
/* End ingroup RBSYS */
