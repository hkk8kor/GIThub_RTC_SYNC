#ifndef TRBLCF_MEMORYMAP_H__
#define TRBLCF_MEMORYMAP_H__

#include "RBSYS_Config.h"

#if (RBFS_FlashBank0Support != RBFS_FlashBank0Support_OFF)
  #if (RBFS_FlashBank0Support == RBFS_FlashBank0Support_ON)
    #define RBLCF_getStartAddress_PFLASH_ActiveBank0() (0x0u)
  #else   /* RBFS_FlashBank0Support_INACTIVE - e.g. for FOTAenhanced */
    #define RBLCF_getStartAddress_PFLASH_InactiveBank0() (0x0u)
  #endif

  #if (RBFS_FlashBank0Support == RBFS_FlashBank0Support_ON)
    #define RBLCF_getEndAddress_PFLASH_ActiveBank0() (0x1000u)
  #else   /* RBFS_FlashBank0Support_INACTIVE - e.g. for FOTAenhanced */
    #define RBLCF_getEndAddress_PFLASH_InactiveBank0() (0x1000u)
  #endif

  #if (RBFS_FlashBank0Support == RBFS_FlashBank0Support_ON)
    #define RBLCF_getLength_PFLASH_ActiveBank0() (0x2000u)
  #else   /* RBFS_FlashBank0Support_INACTIVE - e.g. for FOTAenhanced */
    #define RBLCF_getLength_PFLASH_InactiveBank0() (0x2000u)
  #endif
#endif

#if (RBFS_FlashBank1Support != RBFS_FlashBank1Support_OFF)
  #if (RBFS_FlashBank1Support == RBFS_FlashBank1Support_ON)
    #define RBLCF_getStartAddress_PFLASH_ActiveBank1() (0x3000u)
  #else   /* RBFS_FlashBank1Support_INACTIVE */
    #define RBLCF_getStartAddress_PFLASH_InactiveBank1() (0x3000u)
  #endif

  #if (RBFS_FlashBank1Support == RBFS_FlashBank1Support_ON)
    #define RBLCF_getEndAddress_PFLASH_ActiveBank1() (0x4000u)
  #else   /* RBFS_FlashBank1Support_INACTIVE */
    #define RBLCF_getEndAddress_PFLASH_InactiveBank1() (0x4000u)
  #endif

  #if (RBFS_FlashBank1Support == RBFS_FlashBank1Support_ON)
    #define RBLCF_getLength_PFLASH_ActiveBank1() (0x5000u)
  #else   /* RBFS_FlashBank1Support_INACTIVE */
    #define RBLCF_getLength_PFLASH_InactiveBank1() (0x5000u)
  #endif
#endif


#if (RBFS_FlashBank2Support != RBFS_FlashBank2Support_OFF)
  #if (RBFS_FlashBank2Support == RBFS_FlashBank2Support_ON)
    #define RBLCF_getStartAddress_PFLASH_ActiveBank2() (0x6000u)
  #else   /* RBFS_FlashBank2Support_INACTIVE */
    #define RBLCF_getStartAddress_PFLASH_InactiveBank2() (0x6000u)
  #endif

  #if (RBFS_FlashBank2Support == RBFS_FlashBank2Support_ON)
    #define RBLCF_getEndAddress_PFLASH_ActiveBank2() (0x7000u)
  #else   /* RBFS_FlashBank2Support_INACTIVE */
    #define RBLCF_getEndAddress_PFLASH_InactiveBank2() (0x7000u)
  #endif

  #if (RBFS_FlashBank2Support == RBFS_FlashBank2Support_ON)
    #define RBLCF_getLength_PFLASH_ActiveBank2() (0x8000u)
  #else   /* RBFS_FlashBank2Support_INACTIVE */
    #define RBLCF_getLength_PFLASH_InactiveBank2() (0x8000u)
  #endif
#endif


#if (RBFS_FlashBank3Support != RBFS_FlashBank3Support_OFF)
  #if (RBFS_FlashBank3Support == RBFS_FlashBank3Support_ON)
    #define RBLCF_getStartAddress_PFLASH_ActiveBank3() (0x9000u)
  #else   /* RBFS_FlashBank3Support_INACTIVE */
    #define RBLCF_getStartAddress_PFLASH_InactiveBank3() (0x9000u)
  #endif

  #if (RBFS_FlashBank3Support == RBFS_FlashBank3Support_ON)
    #define RBLCF_getEndAddress_PFLASH_ActiveBank3() (0xA000u)
  #else   /* RBFS_FlashBank3Support_INACTIVE */
    #define RBLCF_getEndAddress_PFLASH_InactiveBank3() (0xA000u)
  #endif

  #if (RBFS_FlashBank3Support == RBFS_FlashBank3Support_ON)
    #define RBLCF_getLength_PFLASH_ActiveBank3() (0xB000u)
  #else   /* RBFS_FlashBank3Support_INACTIVE */
    #define RBLCF_getLength_PFLASH_InactiveBank3() (0xB000u)
  #endif
#endif

#if (RBFS_FlashBank4Support != RBFS_FlashBank4Support_OFF)

  #if (RBFS_FlashBank4Support == RBFS_FlashBank4Support_ON)
    #define RBLCF_getStartAddress_PFLASH_ActiveBank4() (0xC000u)
  #else   /* RBFS_FlashBank4Support_INACTIVE */
    #define RBLCF_getStartAddress_PFLASH_InactiveBank4() (0xC000u)
  #endif

  #if (RBFS_FlashBank4Support == RBFS_FlashBank4Support_ON)
    #define RBLCF_getEndAddress_PFLASH_ActiveBank4() (0xD000u)
  #else   /* RBFS_FlashBank4Support_INACTIVE */
    #define RBLCF_getEndAddress_PFLASH_InactiveBank4() (0xD000u)
  #endif

  #if (RBFS_FlashBank4Support == RBFS_FlashBank4Support_ON)
    #define RBLCF_getLength_PFLASH_ActiveBank4() (0xE000u)
  #else   /* RBFS_FlashBank4Support_INACTIVE */
    #define RBLCF_getLength_PFLASH_InactiveBank4() (0xE000u)
  #endif
#endif

#if (RBFS_FlashBank5Support != RBFS_FlashBank5Support_OFF)
  #if (RBFS_FlashBank5Support == RBFS_FlashBank5Support_ON)
    #define RBLCF_getStartAddress_PFLASH_ActiveBank5() (0xF000u)
  #else   /* RBFS_FlashBank5Support_INACTIVE */
    #define RBLCF_getStartAddress_PFLASH_InactiveBank5() (0xF000u)
  #endif

  #if (RBFS_FlashBank5Support == RBFS_FlashBank5Support_ON)
    #define RBLCF_getEndAddress_PFLASH_ActiveBank5() (0x10000u)
  #else   /* RBFS_FlashBank5Support_INACTIVE */
    #define RBLCF_getEndAddress_PFLASH_InactiveBank5() (0x10000u)
  #endif

  #if (RBFS_FlashBank5Support == RBFS_FlashBank5Support_ON)
    #define RBLCF_getLength_PFLASH_ActiveBank5() (0x11000u)
  #else   /* RBFS_FlashBank5Support_INACTIVE */
    #define RBLCF_getLength_PFLASH_InactiveBank5() (0x11000u)
  #endif
#endif



#if (RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)

  #if (RBFS_FlashBank5Support == RBFS_FlashBank5Support_ON)
    #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_ActiveBank5()
  #elif (RBFS_FlashBank4Support == RBFS_FlashBank4Support_ON)
    #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_ActiveBank4()
  #elif (RBFS_FlashBank3Support == RBFS_FlashBank3Support_ON)
    #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_ActiveBank3()
  #elif (RBFS_FlashBank2Support == RBFS_FlashBank2Support_ON)
    #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_ActiveBank2()
  #elif (RBFS_FlashBank1Support == RBFS_FlashBank1Support_ON)
    #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_ActiveBank1()
  #else
    #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_ActiveBank0()
  #endif
#else
    /* iterate over all non-OFF banks */
  #if (RBFS_FlashBank5Support != RBFS_FlashBank5Support_OFF)
    #if (RBFS_FlashBank5Support == RBFS_FlashBank5Support_ON)   /* Flash bank 5 is active */
      #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_ActiveBank5()
    #else   /* RBFS_FlashBank5Support_INACTIVE - no usecases yet - e.g. for FOTApremium on P6 */
      #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_InactiveBank5()
    #endif
  #elif (RBFS_FlashBank4Support != RBFS_FlashBank4Support_OFF)
    #if (RBFS_FlashBank4Support == RBFS_FlashBank4Support_ON)   /* Flash bank 4 is active */
      #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_ActiveBank4()
    #else   /* RBFS_FlashBank4Support_INACTIVE - no usecases yet - e.g. for FOTApremium on P6 */
      #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_InactiveBank4()
    #endif
  #elif (RBFS_FlashBank3Support != RBFS_FlashBank3Support_OFF)
    #if (RBFS_FlashBank3Support == RBFS_FlashBank3Support_ON)   /* Flash bank 3 is active */
      #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_ActiveBank3()
    #else   /* RBFS_FlashBank3Support_INACTIVE - e.g. for FOTApremium on M6 */
      #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_InactiveBank3()
    #endif
  #elif (RBFS_FlashBank2Support != RBFS_FlashBank2Support_OFF)
    #if (RBFS_FlashBank2Support == RBFS_FlashBank2Support_ON)   /* Flash bank 2 is active */
      #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_ActiveBank2()
    #else   /* RBFS_FlashBank2Support_INACTIVE - e.g. for FOTApremium on M6 */
      #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_InactiveBank2()
    #endif
  #elif (RBFS_FlashBank1Support != RBFS_FlashBank1Support_OFF)
    #if (RBFS_FlashBank1Support == RBFS_FlashBank1Support_ON)   /* Flash bank 1 is active */
      #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_ActiveBank1()
    #else   /* RBFS_FlashBank1Support_INACTIVE - usecase of multiple inactive banks after active bank not yet applied */
      #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_InactiveBank1()
    #endif
  #else
    #if (RBFS_FlashBank0Support == RBFS_FlashBank0Support_ON)   /* Flash bank 0 is the only remaining bank */
      #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_ActiveBank0()
    #else   /* RBFS_FlashBank0Support_INACTIVE - not sensible (but generically not forbidden) to have only one inactive bank 0 at all */
      #define RBLCF_getEndAddress_PFLASH() RBLCF_getEndAddress_PFLASH_InactiveBank0()
    #endif
  #endif
#endif


#define RBLCF_getStartAddress_LRAM_CPU0() (0x20000u)
#define RBLCF_getEndAddress_LRAM_CPU0_forRAMSafety()   (0x21000u)
#if (RBFS_LocalRamCore1Support == RBFS_LocalRamCore1Support_ON)
  #define RBLCF_getStartAddress_LRAM_CPU1() (0x22000u)
  #define RBLCF_getEndAddress_LRAM_CPU1_forRAMSafety()   (0x23000u)
#endif
#if (RBFS_LocalRamCore2Support == RBFS_LocalRamCore2Support_ON)
  #define RBLCF_getStartAddress_LRAM_CPU2() (0x24000u)
  #define RBLCF_getEndAddress_LRAM_CPU2_forRAMSafety()   (0x25000u)
#endif  /* RBFS_LocalRamCore2Support_ON */
#if (RBFS_LocalRamCore3Support == RBFS_LocalRamCore3Support_ON)
  #define RBLCF_getStartAddress_LRAM_CPU3() (0x26000u)
  #define RBLCF_getEndAddress_LRAM_CPU3_forRAMSafety()   (0x27000u)
#endif  /* RBFS_LocalRamCore3Support_ON */

#if (RBFS_RenesasU2aCRAM0 == RBFS_RenesasU2aCRAM0_ON)
  #define RBLCF_getStartAddress_CRAM0() (0x28000u)
  #define RBLCF_getEndAddress_CRAM0_forRAMSafety()   (0x29000u)
#endif  /* RBFS_RenesasU2aCRAM0_ON */

#if (RBFS_RenesasU2aCRAM1 == RBFS_RenesasU2aCRAM1_ON)
  #define RBLCF_getStartAddress_CRAM1() (0x2A000u)
  #define RBLCF_getEndAddress_CRAM1_forRAMSafety()   (0x2B000u)
#endif  /* RBFS_RenesasU2aCRAM1_ON */

#if (RBFS_RenesasU2aCRAM2 == RBFS_RenesasU2aCRAM2_ON)
  #define RBLCF_getStartAddress_CRAM2() (0x2C000u)
  #define RBLCF_getEndAddress_CRAM2_forRAMSafety()   (0x2D000u)
#endif  /* RBFS_RenesasU2aCRAM2_ON */

#if (RBFS_RenesasU2aCRAM3 == RBFS_RenesasU2aCRAM3_ON)
  #define RBLCF_getStartAddress_CRAM3() (0x2E000u)
  #define RBLCF_getEndAddress_CRAM3_forRAMSafety()   (0x2F000u)
#endif  /* RBFS_RenesasU2aCRAM3_ON */

#if (RBFS_RenesasP1xGRAM == RBFS_RenesasP1xGRAM_ON)
  #define RBLCF_getStartAddress_GRAM()  (0x30000u)
  #define RBLCF_getEndAddress_GRAM_forRAMSafety()    (0x31000u)
#endif  /* RBFS_RenesasP1xGRAM_ON */

#endif