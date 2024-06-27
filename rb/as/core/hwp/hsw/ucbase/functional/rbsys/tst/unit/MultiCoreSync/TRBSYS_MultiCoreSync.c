#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_Config.h"                      // for RBFS_MCORE

#include "RBSYS_CpuInfo.h"
#include "TRBSYS_CpuInfo.h"
#include "RBLCF_MemoryRemap.h"
#include "TRBSYS_uCRegisters.h"      // peripheral labels
#include "RBSYS_Intrinsics.h"      // RBSYS_SNOOZE_LOOP, RBSYS_SYNCM
#include "RBSYS_SystemTimer.h"
#include "TRBSYS_SystemTimer.h"
#include "RBSYS_ResetSync.h"
#include "TRBSYS_TestInjection.h"
#include "RBSYS_MultiCoreSync.h"
#include "RBSYS_MultiCoreSyncIntern.h"

#include "TRBSYS_MultiCoreSync_Adaptor.h"

#if ( RBFS_MCORE == RBFS_MCORE_ON )
  #if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
    /**
    * \Reference
    *  RBSYS_InitMultiCoreSync, Gen_SWCS_HSW_uC_Base_SYS-351
    *
    * \Purpose
    *  Verification of the initialization routine "RBSYS_InitMultiCoreSync"
    *
    * \Sequence
    *  Initialize compl. array "RBSYS_Core0_arrived" and "RBSYS_Core1_arrived" with values unequal to zero
    *  Initialize registers used for synchronization to HW default value (for core0)
    *  Call function RBSYS_InitMultiCoreSync by core0
    *  Initialize registers used for synchronization to HW default value (for core1)
    *  Call function RBSYS_InitMultiCoreSync by core1
    *
    * \ExpectedResult
    *  Intermediate results of registers used for synchronization must be 3 after function was called by core0 only
    *  Final results of registers used for synchronization must be HW default value after function was called by core1
    *  Compl. array "RBSYS_Core0_arrived" and "RBSYS_Core1_arrived" must be initialized to zero
    *  RBSYS_StartupSync structure must be correct initialized to corresponding array
    */
    SWTEST void TRBSYS_InitMultiCoreSync(void)
    {
      int i;

      for(i = 0; i < RBSYS_MaxNumberOfStartupSyncPhases; i++)
      {
        SetPrivate_RBSYS_Core0_arrived(i, 0xAA);
        SetPrivate_RBSYS_Core1_arrived(i, 0x55);
      }

      TRBSYS_SYNCREG1 = TRBSYS_SYNCREGDEFAULT;            //init EIBD41/INTC2EIBD221 to default value
      TRBSYS_SYNCREG2 = TRBSYS_SYNCREGDEFAULT;            //init EIBD42/INTC2EIBD222 to default value
      TRBSYS_SYNCREG3 = TRBSYS_SYNCREGDEFAULT;            //init EIBD43/INTC2EIBD223 to default value

      // activate test injection inside of while loops to set registers used in the loop condition
      TRBSYS_InjectValues = TRUE;

      //call RBSYS_InitMultiCoreSync by core0
      TRBSYS_setCoreID(0);
      RBSYS_InitMultiCoreSync();

      //intermediate results (function only called by core0)
      SWT_EvalEq(TRBSYS_SYNCREG1, TRBSYS_SYNCREGDEFAULT | 7);                          // set by core0 within RBSYS_InitMultiCoreSync
      SWT_EvalEq(TRBSYS_SYNCREG2, TRBSYS_SYNCREGDEFAULT | 7);                          // set within RBSYS_SNOOZE_LOOP
      SWT_EvalEq(TRBSYS_SYNCREG3, TRBSYS_SYNCREGDEFAULT | 7);                          // set by core0 within RBSYS_InitMultiCoreSync

      /* clear registers used for synchronization for core1 */
      TRBSYS_SYNCREG1 = TRBSYS_SYNCREGDEFAULT;            //init EIBD41/INTC2EIBD221 to default value
      TRBSYS_SYNCREG2 = TRBSYS_SYNCREGDEFAULT;            //init EIBD42/INTC2EIBD222 to default value
      TRBSYS_SYNCREG3 = TRBSYS_SYNCREGDEFAULT;            //init EIBD43/INTC2EIBD223 to default value

      //call RBSYS_InitMultiCoreSync by core1
      TRBSYS_setCoreID(1);
      RBSYS_InitMultiCoreSync();

      //final clear of registers used for synchronization by core1 to default value
      SWT_EvalEq(TRBSYS_SYNCREG1, TRBSYS_SYNCREGDEFAULT);
      SWT_EvalEq(TRBSYS_SYNCREG2, TRBSYS_SYNCREGDEFAULT);
      SWT_EvalEq(TRBSYS_SYNCREG3, TRBSYS_SYNCREGDEFAULT);

      //evaluate manual init (hint: function is called before cinit - therefore manual initialization required)
      for(i = 0; i < RBSYS_MaxNumberOfStartupSyncPhases; i++)
      {
        SWT_EvalEq( *(GetPrivate_RBSYS_Core0_arrived_ptr(i)), 0 );
        SWT_EvalEq( *(GetPrivate_RBSYS_Core1_arrived_ptr(i)), 0 );
      }
      SWT_Eval(GetPrivate_RBSYS_StartupSyncPtr(RBSYS_CORE_ID_0) == GetPrivate_RBSYS_Core0_arrived_ptr(0));
      SWT_Eval(GetPrivate_RBSYS_StartupSyncPtr(RBSYS_CORE_ID_1) == GetPrivate_RBSYS_Core1_arrived_ptr(0));
    }


    /**
    * \Reference
    *  RBSYS_StartupSyncBarrier, Gen_SWCS_HSW_uC_Base_SYS-351
    *
    * \Purpose
    *  Function "RBSYS_StartupSyncBarrier" called by core0
    *
    * \Sequence
    *  Initialize registers used for synchronization to HW default value
    *  Call function RBSYS_InitMultiCoreSync by core0
    *  Call function RBSYS_InitMultiCoreSync by core1
    *  Simulate still arrived core1 (via array "RBSYS_Core1_arrived")
    *  Call RBSYS_StartupSyncBarrier for each phase by core0
    *
    * \ExpectedResult
    *  Arrived status for core0 must be set, which means must be the same status as for core1
    */
    SWTEST void TRBSYS_StartupSyncBarrierCore0(void)
    {
      int phase;
      TRBSYS_SYNCREG1 = TRBSYS_SYNCREGDEFAULT;            //init EIBD41/INTC2EIBD221 to default value
      TRBSYS_SYNCREG2 = TRBSYS_SYNCREGDEFAULT;            //init EIBD42/INTC2EIBD222 to default value
      TRBSYS_SYNCREG3 = TRBSYS_SYNCREGDEFAULT;            //init EIBD43/INTC2EIBD223 to default value

      // activate test injection inside of while loops to set registers used in the loop condition
      TRBSYS_InjectValues = TRUE;

      //call RBSYS_InitMultiCoreSync by core0
      TRBSYS_setCoreID(0);
      RBSYS_InitMultiCoreSync();

      //call RBSYS_InitMultiCoreSync by core1
      TRBSYS_setCoreID(1);
      RBSYS_InitMultiCoreSync();

      //call RBSYS_StartupSyncBarrier for each phase by core0
      TRBSYS_setCoreID(0);
      for(phase = 0; phase < RBSYS_MaxNumberOfStartupSyncPhases; phase++)
      {
        // a corresponding call by the other core is simulated via test injection if needed
        RBSYS_StartupSyncBarrier((RBSYS_StartupSyncPhases_t)phase);
      }

      //arrived status for core0 must be set
      for(phase = 0; phase < RBSYS_MaxNumberOfStartupSyncPhases; phase++)
      {
        SWT_EvalEq( *(GetPrivate_RBSYS_Core0_arrived_ptr(phase)), *(GetPrivate_RBSYS_Core1_arrived_ptr(phase)) );
      }
    }


    /**
    * \Reference
    *  RBSYS_StartupSyncBarrier, Gen_SWCS_HSW_uC_Base_SYS-351
    *
    * \Purpose
    *  Function "RBSYS_StartupSyncBarrier" called by core1
    *
    * \Sequence
    *  Initialize registers used for synchronization to HW default value
    *  Call function RBSYS_InitMultiCoreSync by core0
    *  Call function RBSYS_InitMultiCoreSync by core1
    *  Simulate still arrived core0 (via array "RBSYS_Core0_arrived")
    *  Call RBSYS_StartupSyncBarrier for each phase by core1
    *
    * \ExpectedResult
    *  Arrived status for core1 must be set, which means must be the same status as for core0
    */
    SWTEST void TRBSYS_StartupSyncBarrierCore1(void)
    {
      int phase;
      TRBSYS_SYNCREG1 = TRBSYS_SYNCREGDEFAULT;            //init EIBD41/INTC2EIBD221 to default value
      TRBSYS_SYNCREG2 = TRBSYS_SYNCREGDEFAULT;            //init EIBD42/INTC2EIBD222 to default value
      TRBSYS_SYNCREG3 = TRBSYS_SYNCREGDEFAULT;            //init EIBD43/INTC2EIBD223 to default value

      // activate test injection inside of while loops to set registers used in the loop condition
      TRBSYS_InjectValues = TRUE;

      //call RBSYS_InitMultiCoreSync by core0
      TRBSYS_setCoreID(0);
      RBSYS_InitMultiCoreSync();

      //call RBSYS_InitMultiCoreSync by core1
      TRBSYS_setCoreID(1);
      RBSYS_InitMultiCoreSync();

      //call RBSYS_StartupSyncBarrier for each phase by core1
      for(phase = 0; phase < RBSYS_MaxNumberOfStartupSyncPhases; phase++)
      {
        // a corresponding call by the other core is simulated via test injection if needed
        RBSYS_StartupSyncBarrier((RBSYS_StartupSyncPhases_t)phase);
      }

      //arrived status for core1 must be set
      for(phase = 0; phase < RBSYS_MaxNumberOfStartupSyncPhases; phase++)
      {
        SWT_EvalEq( *(GetPrivate_RBSYS_Core0_arrived_ptr(phase)), *(GetPrivate_RBSYS_Core1_arrived_ptr(phase)) );
      }
    }


    /**
    * \Reference
    *  RBSYS_SyncBarrier, Gen_SWCS_HSW_uC_Base_SYS-351
    *
    * \Purpose
    *  Test sync phase counter overflow
    *
    * \Sequence
    *  Set sync phase counter of both cores to SINT8_MAX
    *  Call RBSYS_SyncBarrier
    *  Set sync phase counter of core0 to 0 and of core1 to 2
    *  Call RBSYS_SyncBarrier
    *  Set sync phase counter of core0 to SINT8_MAX-2 and of core1 to 0
    *  Call RBSYS_SyncBarrier
    *
    * \ExpectedResult
    * Sync phase counter of both cores are 0 after first call (core0 correctly waits on (sint8)(0-255) > 0)
    * Sync phase counter of core0 increments by one and of core1 stays the same after second call (core0 correctly doesn't wait on (sint8)(1-2) > 0)
    * Sync phase counter of core0 increments by one and of core1 stays the same after second call (core0 correctly doesn't wait on (sint8)(255-0) > 0)
    */
    RBSYS_MULTICORESYNC_DEFINE_SYNCPHASES_LRAM(TRBSYS_SyncStruct, 1);
    SWTEST void TRBSYS_SyncBarrierOverflow(void)
    {
      // no core is currently in RBSYS_SyncBarrier
      // core0 should calculate (sint8)(0 - 255) = 1 in its while loop condition
      TRBSYS_SyncStruct.ptr[0][0] = 255;
      TRBSYS_SyncStruct.ptr[1][0] = 255;
      TRBSYS_setCoreID(0);

      // a corresponding call by the other core is simulated via test injection if needed
      RBSYS_SyncBarrier(&TRBSYS_SyncStruct, 0);

      SWT_EvalEq(TRBSYS_SyncStruct.ptr[0][0], 0);
      SWT_EvalEq(TRBSYS_SyncStruct.ptr[1][0], 0); // core1's sync phase counter was incremented, indicating that core0 waited

      // simulate core0 waiting for core1 on counter 1, core1 arriving and quickly calling another sync barrier
      // core0 should calculate (sint8)(1 - 2) = -1 in its while loop condition
      TRBSYS_SyncStruct.ptr[0][0] = 0;
      TRBSYS_SyncStruct.ptr[1][0] = 2;
      TRBSYS_setCoreID(0);

      // a corresponding call by the other core is simulated via test injection if needed
      RBSYS_SyncBarrier(&TRBSYS_SyncStruct, 0);

      SWT_EvalEq(TRBSYS_SyncStruct.ptr[0][0], 1);
      SWT_EvalEq(TRBSYS_SyncStruct.ptr[1][0], 2); // core1's sync phase counter was not incremented, indicating that core0 didn't wait

      // simulate core0 waiting for core1 on counter 255, core1 arriving and quickly calling another sync barrier
      // core0 should calculate (sint8)(255 - 0) = -1 in its while loop condition
      TRBSYS_SyncStruct.ptr[0][0] = 254;
      TRBSYS_SyncStruct.ptr[1][0] = 0;
      TRBSYS_setCoreID(0);

      // a corresponding call by the other core is simulated via test injection if needed
      RBSYS_SyncBarrier(&TRBSYS_SyncStruct, 0);

      SWT_EvalEq(TRBSYS_SyncStruct.ptr[0][0], 255);
      SWT_EvalEq(TRBSYS_SyncStruct.ptr[1][0], 0); // core1's sync phase counter was not incremented, indicating that core0 didn't wait
    }


    /**
    * \Reference
    *  TRBSYS_RuntimeSyncBarrier, Gen_SWCS_HSW_uC_Base_SYS-351
    *
    * \Purpose
    *  Test functionality "RBSYS_RuntimeSyncBarrier" by both Cores on Multicore Systems
    *
    * \Sequence
    *  Call RBSYS_RuntimeSyncBarrier from Core 0
    *  As Core 1 does not call it, Timeout will hit
    *  Call RBSYS_RuntimeSyncBarrier from Core 1
    *  As Core 0 does not call it, Timeout will hit
    *  Both Cores call it
    *  No Timeout will hit -> means both Cores are in Sync
    *
    * \ExpectedResult
    *  see Sequence
    */
    SWTEST void TRBSYS_RuntimeSyncBarrier(void)
    {
      //call RBSYS_RuntimeSyncBarrier(RBSYS_RuntimeSyncPhase_BeforeReset) by core 0
      TRBSYS_setCoreID(0);
      TRBSYS_InjectValues = FALSE; // do not activate test injection inside of while loops to run into timeout
      RBSYS_RuntimeResetSyncBarrier();
      //core 1 has not arrived at the barrier -> timeout shall be 150us
      SWT_EvalEq(RBSYS_getRealtimeTickCtr(), RBSYS_convertUsecToTimerTicks(150) + 1);
      SetPrivate_RBSYS_RuntimeResetSyncPhase(0, 0);

      //call RBSYS_RuntimeSyncBarrier(RBSYS_RuntimeSyncPhase_BeforeReset) by core 1
      TRBSYS_setCoreID(1);
      TRBSYS_InjectValues = FALSE; // do not activate test injection inside of while loops to run into timeout
      RBSYS_RuntimeResetSyncBarrier();
      //core 0 has not arrived at the barrier -> timeout shall be 150us
      SWT_EvalEq(RBSYS_getRealtimeTickCtr(), RBSYS_convertUsecToTimerTicks(300) + 2);
      SetPrivate_RBSYS_RuntimeResetSyncPhase(1, 0);

      /* Core 1 shall arrive at the barrier right after Core 0 */
      TRBSYS_setCoreID(0);
      TRBSYS_InjectValues = TRUE; // activate test injection inside of while loops to set registers used in the loop condition
      RBSYS_RuntimeResetSyncBarrier();

      //No time has passed -> no timeout is hit
      SWT_EvalEq(RBSYS_getRealtimeTickCtr(), RBSYS_convertUsecToTimerTicks(300) + 3);

      /* Restore Defaults */
      SetPrivate_RBSYS_RuntimeResetSyncPhase(0, 0);
      SetPrivate_RBSYS_RuntimeResetSyncPhase(1, 0);

      /* Core 0 shall arrive at the barrier right after Core 1 */
      TRBSYS_setCoreID(1);
      TRBSYS_InjectValues = TRUE; // activate test injection inside of while loops to set registers used in the loop condition
      RBSYS_RuntimeResetSyncBarrier();

      //No time has passed -> no timeout is hit
      SWT_EvalEq(RBSYS_getRealtimeTickCtr(), RBSYS_convertUsecToTimerTicks(300) + 4);
    }

    #if( RBFS_CANCommunicationDuringInitTask == RBFS_CANCommunicationDuringInitTask_Enabled )
      #include "RBSYS_Subsystem.h"
      /**
      * \Reference
      *  TRBSYS_InitTaskSynchronisationForParallelCANCommunication
      *
      * \Purpose
      *  Test sync functionality RBSYS_PRC_SynchronizeCores_TaskInit on both Cores (feature supports only 2 cores)
      *
      * \Sequence
      *  Call RBSYS_PRC_SynchronizeCores_TaskInit on Core 0
      *  Call RBSYS_PRC_SynchronizeCores_TaskInit on Core 1
      *
      * \ExpectedResult
      *  Evaluate if both Core have hit the Sync Barrier
      */
      SWTEST void TRBSYS_InitTaskSynchronisationForParallelCANCommunication(void)
      {
        TRBSYS_setCoreID(0);
        RBSYS_PRC_SynchronizeCores_TaskInit();
        TRBSYS_setCoreID(1);
        RBSYS_PRC_SynchronizeCores_TaskInit();

        SWT_EvalEq( *(GetPrivate_RBSYS_Core0_arrived_ptr(RBSYS_PreInitCanCommunicationFinished)), *(GetPrivate_RBSYS_Core1_arrived_ptr(RBSYS_PreInitCanCommunicationFinished)) );
      }
    #endif

    /**
      * \Reference
      *  RBSYS_MultiCoreSync_ReleaseCore1
      *
      * \Purpose
      *  Test if RBSYS_MultiCoreSync_ReleaseCore1 writes the correct pattern into correct register
      *
      * \Sequence
      *  Call RBSYS_MultiCoreSync_ReleaseCore1
      *  Eval: Register == 0x3
      *
      * \ExpectedResult
      *  see \Sequence
      */
    SWTEST void TRBSYS_MultiCoreSync_ReleaseOtherCores(void)
    {
      RBSYS_MultiCoreSync_ReleaseCore1();

      SWT_EvalEq(TRBSYS_SYNCREG1, 0x3);
      SWT_EvalEq(TRBSYS_SYNCREG2, 0);
      SWT_EvalEq(TRBSYS_SYNCREG3, 0);
    }

  #elif( RBFS_HexBlockBuild == RBFS_HexBlockBuild_BOOTMANAGER )

    /**
      * \Reference
      *  RBSYS_MultiCoreSync_IsCore1Released
      *
      * \Purpose
      *  Test if RBSYS_MultiCoreSync_IsCore1Released detects release condition
      *
      * \Sequence
      *  Call RBSYS_MultiCoreSync_ReleaseCore1 => Eval: Not released
      *  Write Sync Register to 0x3 (Pattern for "released")
      *  Call RBSYS_MultiCoreSync_ReleaseCore1 => Eval: Released
      *  Write Sync Register to 0x7 (Pattern for "sync barrier reached")
      *  Call RBSYS_MultiCoreSync_ReleaseCore1 => Eval: Released
      *
      * \ExpectedResult
      *  see \Sequence
      */
    SWTEST void TRBSYS_MultiCoreSync_IsCore1Released(void)
    {
      SWT_EvalEq( RBSYS_MultiCoreSync_IsCore1Released(), FALSE );

      TRBSYS_SYNCREG1 = 0x3; //< Core 0 has released other Cores, but not yet reached SyncBarrier
      SWT_EvalEq( RBSYS_MultiCoreSync_IsCore1Released(), TRUE );

      TRBSYS_SYNCREG1 = 0x7; //< Core 0 has reached Sync Barrier
      SWT_EvalEq( RBSYS_MultiCoreSync_IsCore1Released(), TRUE );

    }
  
  #else //< Feature not available for OEMBLDR / RBBLDR

  /**
   * \Reference
   *  RBSYS_InitMultiCoreSync, Gen_SWCS_HSW_uC_Base_SYS-351
   *
   * \Purpose
   *  Multi core synchronization feature not available in case of OEMBLDR / RBBLDR.
   *
   * \Sequence
   *  -
   *
   * \ExpectedResult
   *  -
   */
  SWTEST void TRBSYS_InitMultiCoreSync_FeatureNotAvailable(void)
  {
    SWT_EvalEx(TRUE, "Feature not Available");
  }

  #endif

#else

  /**
   * \Reference
   *  RBSYS_InitMultiCoreSync, Gen_SWCS_HSW_uC_Base_SYS-351
   *
   * \Purpose
   *  Multi core synchronization feature not available in case of single core device.
   *
   * \Sequence
   *  -
   *
   * \ExpectedResult
   *  -
   */
  SWTEST void TRBSYS_InitMultiCoreSync_FeatureNotAvailable(void)
  {
    SWT_EvalEx(TRUE, "Feature not Available");
  }

#endif