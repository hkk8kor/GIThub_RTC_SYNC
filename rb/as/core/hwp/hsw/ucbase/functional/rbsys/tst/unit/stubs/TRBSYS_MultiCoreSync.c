#include "RBSYS_MultiCoreSyncIntern.h"
#include "RBSYS_Config.h"
#include "RBSYS_uCRegisters.h"
#include "TRBSYS_MultiCoreSync_Helper.h"

#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  #define RBSYS_REG_CORE0_ARRIVED         (EIBD41)         // STM0 Interrupt 0 -> default value of the register is 0x00000001
  #define RBSYS_REG_CORE1_ARRIVED         (EIBD42)         // STM0 Interrupt 1 -> default value of the register is 0x00000001
  #define RBSYS_REG_CORE0_FINISHED        (EIBD43)         // STM1 Interrupt 0 -> default value of the register is 0x00000001
#elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
  #define RBSYS_REG_CORE0_ARRIVED         (INTC2EIBD221)   // TPTM3 timer interrupt for comparison value 0 -> default value of the register is 0x0
  #define RBSYS_REG_CORE1_ARRIVED         (INTC2EIBD222)   // TPTM3 timer interrupt for comparison value 1 -> default value of the register is 0x0
  #define RBSYS_REG_CORE0_FINISHED        (INTC2EIBD223)   // TPTM3 timer interrupt for comparison value 2 -> default value of the register is 0x0
#elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
  /* todo: cleanup */
  /* todo: Start SENT Module first (STB controller) */

  #define RBSYS_REG_CORE0_ARRIVED         (SENT_0.CH[0].CONFIG)
  #define RBSYS_REG_CORE1_ARRIVED         (SENT_0.CH[1].CONFIG)
  #define RBSYS_REG_CORE0_FINISHED        (SENT_0.CH[2].CONFIG)
#endif
#define RBSYS_REG_START_OTHER_CORES       (RBSYS_REG_CORE0_ARRIVED) //< reuse any of above registers

#define RBSYS_SYNC_START_OTHER_CORES  (0x3u)
#define RBSYS_SYNC_CORE_ARRIVED       (0x7u)

#if( RBFS_MCORE == RBFS_MCORE_ON )
  #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_BOOTMANAGER )

    boolean RBSYS_MultiCoreSync_IsCore1Released(void)
    {
      return (RBSYS_REG_START_OTHER_CORES & RBSYS_SYNC_START_OTHER_CORES) == RBSYS_SYNC_START_OTHER_CORES;
    }

  #elif( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )

    void RBSYS_MultiCoreSync_ReleaseCore1(void)
    {
      RBSYS_REG_START_OTHER_CORES |= RBSYS_SYNC_START_OTHER_CORES; //< notify Core1 by writing into INTC2 register
    }
  #endif
#endif


void TRBSYS_Bootblock_ReleaseCore0FromApplication(void)
{
  RBSYS_REG_START_OTHER_CORES |= RBSYS_SYNC_START_OTHER_CORES;
}