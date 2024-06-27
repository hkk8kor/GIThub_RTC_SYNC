/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Startup synchronization for MultiCore
 *
 * Independent of the hardware startup strategy (reset release) of the cores in MultiCore system,
 * it is necessary to synchronize both cores during startup in different situations. Not all cores
 * will execute the same startup routines. Therefore this general barrier synchronization is provided.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


/* used interfaces */
#include "RBSYS_CpuInfo.h"
#include "RBSYS_uCRegisters.h"      // peripheral labels
#include "RBSYS_Intrinsics.h"     // RBSYS_SNOOZE_LOOP, RBSYS_SYNCM
#include "RBSYS_SystemTimer.h"
#include "RBSYS_TestInjection.h"
#include "RB_MemoryBarrier.h"


/* realized interfaces */
#include "RBSYS_MultiCoreSync.h"
#include "RBSYS_MultiCoreSyncIntern.h"
#include "RBSYS_ResetSync.h"
#include "RBSYS_Subsystem.h"


/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                          RBFS_MCORE_OFF,
                          RBFS_MCORE_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_RenesasU2C,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_CANCommunicationDuringInitTask,
                          RBFS_CANCommunicationDuringInitTask_Enabled,
                          RBFS_CANCommunicationDuringInitTask_Disabled);

RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);


#if (RBFS_MCORE == RBFS_MCORE_ON)

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

  /// START_OTHER_CORES must be subset of CORE_ARRIVED, because Core1 may still have to receive the START trigger while Core0 has already ARRIVED at barrier
  static_assert( (RBSYS_SYNC_START_OTHER_CORES & RBSYS_SYNC_CORE_ARRIVED) == RBSYS_SYNC_START_OTHER_CORES, "Invalid values for CORE_ARRIVED and START_OTHER_CORES");
  /// START_OTHER_CORES must be != CORE_ARRIVED to differ between ReleaseCore1 and MultiCoreSync
  static_assert( (RBSYS_SYNC_START_OTHER_CORES != RBSYS_SYNC_CORE_ARRIVED), "Invalid values for CORE_ARRIVED and START_OTHER_CORES" );

  #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_BOOTMANAGER )

    boolean RBSYS_MultiCoreSync_IsCore1Released(void)
    {
      return (RBSYS_REG_START_OTHER_CORES & RBSYS_SYNC_START_OTHER_CORES) == RBSYS_SYNC_START_OTHER_CORES;
    }

  #elif( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )

    #if( RBFS_CANCommunicationDuringInitTask == RBFS_CANCommunicationDuringInitTask_Enabled )
      static_assert(RB_NUM_CORES == 2, "Invalid Configuration for CANCommunicationDuringInitTask Feature."); /*< Currently, only 2 Cores will be synchronized for CAN communication during Init Task */

      /** @brief RBSYS Process to synchronize Cores during Init Tasks
        * Hint: Must always be called on all Cores.
        */
      void RBSYS_PRC_SynchronizeCores_TaskInit(void)
      {
        RBSYS_StartupSyncBarrier(RBSYS_PreInitCanCommunicationFinished);
      }
    #endif

    /**
      * MultiCoreSync Service Implementation
      */
    void RBSYS_SyncBarrier(const RBSYS_SyncPhaseCounter_t* syncphases, uint8 phase)
    {
      unsigned int myCoreID = RBSYS_getCoreID();
      unsigned int otherCoreID = (myCoreID+1)%2;
      volatile uint8 * currentCoreCounter = &(syncphases->ptr[myCoreID][phase]);
      volatile const uint8 * const otherCoreCounter = &(syncphases->ptr[otherCoreID][phase]);
      uint8 ownCounterValue;
      uint8 counterDifference;

      (*currentCoreCounter)++; // mark own barrier as "reached"
      ownCounterValue = *currentCoreCounter;

      RB_FullHardwareMemoryBarrier(); // prevent code re-ordering

      // Wait until ownCounter is equal or less than the otherCoreCounter,
      // indicating that the other core also reached this point or even reached the next sync barrier.
      // hint: This comparison is done by calculating the difference between the counter in uint8 to
      //       also work when the counters or the difference overflow.
      //       By design the difference between the counters is always in the interval [-1,1], due to
      //       the difference being a uint8 it is in the set {0,1,255}.
      //       A core only needs to wait if its own counter is higher, so if the difference is 1.
      // hint: Alternative design by just calculating the difference and relying on integer promotion
      //       for the cast to signed does not work ((ownCounterValue - *otherCoreCounter) > 0).
      //       In the case 0 - 255 the expected difference would be +1, so the core should wait,
      //       but with the result -255 the comparison becomes false and the core does not wait.
      counterDifference = ownCounterValue - *otherCoreCounter;
      while ( counterDifference == 1 )
      {
        RBSYS_SNOOZE_LOOP(1);
        RBSYS_TEST_INJECTION_CoreSyncPhaseUpdate();
        counterDifference = ownCounterValue - *otherCoreCounter;
      }
    }


    /**
      * MultiCoreSync RBSYS internal usage
      */
    RBSYS_MULTICORESYNC_DEFINE_SYNCPHASES_LRAM(RBSYS_StartupSync, RBSYS_MaxNumberOfStartupSyncPhases);

    static void RBSYS_ResetPhaseCounter(const RBSYS_SyncPhaseCounter_t* syncphases, uint32 numberOfPhases)
    {
        uint32 coreIdx, phaseIdx;
        for (coreIdx = 0; coreIdx < RB_NUM_CORES; coreIdx++)
        {
          for (phaseIdx = 0; phaseIdx < numberOfPhases; phaseIdx++)
          {
            syncphases->ptr[coreIdx][phaseIdx] = 0;
          }
        }
    }


    void RBSYS_MultiCoreSync_ReleaseCore1(void)
    {
      RBSYS_REG_START_OTHER_CORES |= RBSYS_SYNC_START_OTHER_CORES; //< notify Core1 by writing into INTC2 register
    }

    void RBSYS_InitMultiCoreSync(void)
    {
      unsigned int myCoreID = RBSYS_getCoreID();

      /** Synchronize Cores */
      if (myCoreID == 0)
      {
        // Signal Core0 in SYNC
        RBSYS_REG_CORE0_ARRIVED |= RBSYS_SYNC_CORE_ARRIVED;
        // Wait until Core1 is in SYNC
        while ((RBSYS_REG_CORE1_ARRIVED & RBSYS_SYNC_CORE_ARRIVED) != RBSYS_SYNC_CORE_ARRIVED)
        {
          RBSYS_SNOOZE_LOOP(1);
          RBSYS_TEST_INJECTION_CoreSyncRegisterUpdate();
        }
      }
      else
      {
        // Signal Core1 in SYNC
        RBSYS_REG_CORE1_ARRIVED |= RBSYS_SYNC_CORE_ARRIVED;
        // Wait until Core0 is in SYNC
        while ((RBSYS_REG_CORE0_ARRIVED & RBSYS_SYNC_CORE_ARRIVED) != RBSYS_SYNC_CORE_ARRIVED)
        {
          RBSYS_SNOOZE_LOOP(1);
          RBSYS_TEST_INJECTION_CoreSyncRegisterUpdate();
        }
      }

      /** Cores are in Sync now */

      /* Hint: From now on it's ensured that RAM can be used for synchronization, e.g.
      * - both CPUs have finished the MBIST evaluation including possible SW pattern test
      * - PE guards are configured via RBSYS_BasicGuardInit() -> local RAM is open for other CPUs */

      if (myCoreID == 0)
      {
        // reset sync structure as cinit was not executed yet, might not be needed as RAM was already zeroed
        RBSYS_ResetPhaseCounter(&RBSYS_StartupSync, RBSYS_MaxNumberOfStartupSyncPhases);

        RB_FullHardwareMemoryBarrier();  //sync barrier instruction to ensure that init of MultiCoreSync structure is finished before further valid flag in hw register is written

        // interrupt bind register will be used as release flag of MultiCoreSync feature
        RBSYS_REG_CORE0_FINISHED |= RBSYS_SYNC_CORE_ARRIVED;

        // from now on MultiCore Sync feature could be used by both cores
      }
      else
      {
        // wait till MultiCoreSync feature is released
        while ((RBSYS_REG_CORE0_FINISHED & RBSYS_SYNC_CORE_ARRIVED) != RBSYS_SYNC_CORE_ARRIVED)
        {
          RBSYS_SNOOZE_LOOP(1);
          RBSYS_TEST_INJECTION_CoreSyncRegisterUpdate();
        }

        #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
          RBSYS_REG_CORE0_ARRIVED         &= 0xFFFFFFF9u;     // set register value back to default
          RBSYS_REG_CORE1_ARRIVED         &= 0xFFFFFFF9u;     // set register value back to default
          RBSYS_REG_CORE0_FINISHED        &= 0xFFFFFFF9u;     // set register value back to default
        #elif((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C))
          RBSYS_REG_CORE0_ARRIVED         &= 0xFFFFFFF8u;     // set register value back to default
          RBSYS_REG_CORE1_ARRIVED         &= 0xFFFFFFF8u;     // set register value back to default
          RBSYS_REG_CORE0_FINISHED        &= 0xFFFFFFF8u;     // set register value back to default
        #elif(RBFS_uCFamily == RBFS_uCFamily_STMStellar)
          RBSYS_REG_CORE0_ARRIVED         = 0x00000104u;     // set register value back to default
          RBSYS_REG_CORE1_ARRIVED         = 0x00000104u;     // set register value back to default
          RBSYS_REG_CORE0_FINISHED        = 0x00000104u;     // set register value back to default
        #endif
      }
    }


    typedef enum{
      RBSYS_RuntimeResetSyncPhase_BeforeReset = 0u,
      RBSYS_RuntimeResetSyncPhase_MaxNumberOfRuntimeSyncPhases
    } RBSYS_RuntimeResetSyncPhase_t;

    RBSYS_MULTICORESYNC_DEFINE_SYNCPHASES_LRAM(RBSYS_RuntimeResetSync, RBSYS_RuntimeResetSyncPhase_MaxNumberOfRuntimeSyncPhases);

    /**< Runtime Sync Barriers will timeout defensively within 150us by default */
    #define RBSYS_RUNTIMERESETSYNCBARRIER_TIMEOUT_US (150)

    /**
      * @brief Runtime reset synchronization mechanism for MultiCore uC SW resets
      *
      * If one core reached a synch barrier it must be ensured that the other core will also reach
      * this position before both could continue. Currently, there is no need to minimize the bus traffic
      * by placing the status objects withing the local RAM of the other core (as done in startup barrier).
      *
      * @return void
      */
    void RBSYS_RuntimeResetSyncBarrier(void)
    {
      uint32 startTimestamp;
      uint32 myCoreID = RBSYS_getCoreID();
      uint32 otherCoreID = (myCoreID+1)%2;
      boolean isTimerElapsed = FALSE;

      RBSYS_startUsecTimer(&startTimestamp);

      RBSYS_RuntimeResetSync.ptr[myCoreID][RBSYS_RuntimeResetSyncPhase_BeforeReset] = 1;

      RB_FullHardwareMemoryBarrier();

      while ((RBSYS_RuntimeResetSync.ptr[otherCoreID][RBSYS_RuntimeResetSyncPhase_BeforeReset] != 1) && !isTimerElapsed)
      {
        RBSYS_SNOOZE_LOOP(10);
        RBSYS_TEST_INJECTION_ProgressTime();
        RBSYS_TEST_INJECTION_CoreSyncPhaseUpdateConditionally();
        isTimerElapsed = (RBSYS_isUsecTimerElapsed(&startTimestamp, RBSYS_RUNTIMERESETSYNCBARRIER_TIMEOUT_US) != 0);
      }
    }

    void RBSYS_StartupSyncBarrier(RBSYS_StartupSyncPhases_t phase)
    {
      RBSYS_SyncBarrier(&RBSYS_StartupSync, phase);
    }

  #endif // RBFS_HexBlockBuild
#endif // RBFS_MCORE

/** @} */
/* End ingroup RBSYS */
