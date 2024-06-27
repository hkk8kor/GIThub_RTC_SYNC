#ifndef RBSYS_MULTICORESYNCINTERN_H__
#define RBSYS_MULTICORESYNCINTERN_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Startup synchronization for MultiCore
 *
 * Independent of the hardware startup strategy (reset release) of the cores in Multi-Core system,
 * it is necessary to synchronize both cores during startup in different situations. Not all cores
 * will execute the same startup routines. Therefore this general barrier synchronization is provided.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_MultiCoreSync.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

#if (RBFS_MCORE == RBFS_MCORE_ON)  /* in case of single core systems, sync functionality is not required */

  typedef enum{
    RBSYS_AfterStartPE2 = 0u,
    RBSYS_AfterBootblock,
    RBSYS_AfterGRAMGuardInit,
    RBSYS_AfterCinit,
    RBSYS_ReprogDecision,
    RBSYS_BaseOsDecision,
    RBSYS_BeforeSafety,
    RBSYS_BeforePreOS,
    RBSYS_BeforeOS,
    RBSYS_BeforeInitTaskProcs,
    RBSYS_AfterInitTaskProcs,
    RBSYS_OsTimerSetupFinished,
    RBSYS_PreInitCanCommunicationFinished,
    RBSYS_TaskInitEnd,
    RBSYS_MaxNumberOfStartupSyncPhases
  } RBSYS_StartupSyncPhases_t;


  /**
   * @brief Initialize MultiCore synchronization mechanism
   *
   * Using RBSYS related MultiCore synchronization mechanism before cinit requires this initialization.
   * A basic synchronization is done via interrupt controller (INTC), which belongs to RBSYS. It's not
   * possible to have this first synchronization via default strategy (accessing the foreign LRAM).
   * Because this access is not ensured due to possible destructive SW pattern test (MBIST failure handling)
   * and default access restriction to foreign LRAM after reset.
   *
   * @note Ensure that RBSYS_BasicGuardInit() is called before to open local RAM for other CPUs
   *
   * @return void
   */
  extern void RBSYS_InitMultiCoreSync(void);


  /**
   * @brief Encapsulates RBSYS_SyncBarrier with startup synchronization struct
   *
   * Hint: In case of single core systems, sync functionality will be optimized away.
   *       So it is not required to use function switch "RBFS_MCORE" for calling this function.
   *
   * @param phase is the next synchronization barrier
   */
  extern void RBSYS_StartupSyncBarrier(RBSYS_StartupSyncPhases_t phase);


  #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_BOOTMANAGER )

    /**
      * @brief Once Core0 reaches Application, it will release the other Cores (which are stuck in Bootmanager)
      * @return returns TRUE once Core1 can continue to jump to Application
      */
    extern boolean RBSYS_MultiCoreSync_IsCore1Released(void);

  #elif( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )

    /**
      * @brief Once Core0 reaches Application, RBSYS_MultiCoreSync_ReleaseCore1 is used to release the other Cores (which are stuck in Bootmanager)
      * @return void
      */
    extern void RBSYS_MultiCoreSync_ReleaseCore1(void);

  #endif


#else
  // For single core build configurations map this function empty
  #define RBSYS_StartupSyncBarrier(phase)
#endif

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
