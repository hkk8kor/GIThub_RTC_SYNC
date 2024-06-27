/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief General RBSYS error handling
 *
 * Complete RB specific failure handling (setting faults and/or good check) of RBSYS is encapsulated within this module.
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                          RBFS_HexBlockBuild_BOOTMANAGER,
                          RBFS_HexBlockBuild_BOOTLOADER,
                          RBFS_HexBlockBuild_RBBOOTLOADER,
                          RBFS_HexBlockBuild_APPLICATION);

#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )  //< DEM is not available within other than Application

  /* used interfaces */
  #include "RBHSWESR_FailureHandling.h"

  /* realized interfaces */
  #include "Os.h"                       // realizes OS callback ErrorHook
  #include "RBSYS_ErrorHooks.h"

  /* Assert supported configurations: switches, parameters, constants, ... */
  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysMaxTaskx1Jitter,
                            RBFS_SysMaxTaskx1Jitter_5,
                            RBFS_SysMaxTaskx1Jitter_15,
                            RBFS_SysMaxTaskx1Jitter_SERIES);



  /**
   * @brief Operating System error hook
   *
   * Callback routine used for trapping errors resulting from incorrect use of the OS API
   * with reporting corresponding failure word "RBSYS_OSErrorHook".
   *
   * @return void
   */
  FUNC(void, OS_CALLOUT_CODE) ErrorHook(StatusType Error)
  {
    uint32 d0=0;
    uint32 d1=0;
    OSServiceIdType service = OSErrorGetServiceId();

    /* Encode Error code and service id on debug 0 */
    d0=(((uint32)service) << 16) | ((uint32)(Error));

    /* special additional debug values for d1 */
    switch (Error)
    {
      /* for OS limit (over-activation of tasks) */
      case E_OS_LIMIT:
      {
        switch (service)
        {
          case OSServiceId_ActivateTask:
          {
              /* ActivateTask() call results in an error, OSErrorGetServiceId will return OSServiceId_ActivateTask*/
              d1=(uint32)((OSError_ActivateTask_TaskID())->entry_function);
          } break;

          default:
          {
              /* error case without additional debug value for d1 */
          } break;
        }
      } break;

      default:
      {
        /* error case without additional debug value for d1 */
      } break;
    }

    /** @Debuginfo{RBSYS_OSErrorHook}
     *
     *  @FWC_Requirements{ Gen_SWCS_HSW_uC_Base_SYS-252 }
     *
     *  @Data_D0{ @Bit[31..0] Error code 0x10004 means a task was restarted but still running (overload; OS_LIMIT) @condition{D0 == 0x10004}
     *            @Bit[31..0] Error code not 0x10004: Check OS manual with OS GR                                   @condition{D0 != 0x10004}}
     *  @Data_D1{ @Bit[31..0] Address of task @condition{D0 == 0x10004}
     *            @Bit[31..0] not relevant    @condition{D0 != 0x10004}}
     */
    RBHSWESR_ReportElShutdownErrorWithEnvData(DemConf_DemEventParameter_RBSYS_OSErrorHook, DEM_EVENT_STATUS_FAILED, d0, d1);
  }

  static boolean RBSYS_SYSErrorHookFailureReported = FALSE;
  /**
   * @brief Returns whether SYSErrorHook was already reported as failed since the last reset
   *
   * @return TRUE if SYSErrorHook has been reported as failed since the last reset, otherwise FALSE
   */
  boolean RBSYS_IsSYSErrorHookFailureReported(void)
  {
    return RBSYS_SYSErrorHookFailureReported;
  }

  /**
   * @brief Report RBSYS failure "RBSYS_SYSErrorHook" as central hook for SYS (e.g. interrupt) related errors
   *
   * @return void
   */
  void RBSYS_setSYSErrorHook(RBSYSError_t d0, uint32 d1)
  {
    /** @Debuginfo{RBSYS_SYSErrorHook}
      *
      *  @FWC_Requirements{ Gen_SWCS_HSW_uC_Base_SYS-338,
      *                     Gen_SWCS_HSW_uC_Base_SYS-220,
      *                     Gen_SWCS_HSW_uC_Base_SYS-290,
      *                     Gen_SWCS_HSW_uC_Base_SYS-287,
      *                     Gen_SWCS_HSW_uC_Base_SYS-303,
      *                     Gen_SWCS_HSW_uC_Base_SYS-306,
      *                     Gen_SWCS_HSW_uC_Base_SYS-307,
      *                     Gen_SWCS_HSW_uC_Base_SYS-332}
      *
      *  @Data_D0{ @Bit[31..0] @condition{D0 == 0}  RBSYS_Error_InvalidInt
      *            @Bit[31..0] @condition{D0 == 1}  RBSYS_Error_InvalidLockNesting
      *            @Bit[31..0] @condition{D0 == 2}  RBSYS_Error_LockTooLong
      *            @Bit[31..0] @condition{D0 == 3}  RBSYS_Error_WrongAPIcalled
      *            @Bit[31..0] @condition{D0 == 4}  RBSYS_Error_TimerMonitoring
      *                                             (until HSW 2022.2 also includes RBSYS_Error_TimerInterruptMonitoring, separated afterwards)
      *            @Bit[31..0] @condition{D0 == 5}  RBSYS_Error_PeripheralReset
      *            @Bit[31..0] @condition{D0 == 6}  RBSYS_Error_PeripheralResetTimeOut
      *            @Bit[31..0] @condition{D0 == 7}  RBSYS_Error_SupervisorRestriction
      *            @Bit[31..0] @condition{D0 == 8}  RBSYS_Error_GuardConfigurationFailed
      *            @Bit[31..0] @condition{D0 == 9}  RBSYS_Error_TPSWConfigurationFailed
      *            @Bit[31..0] @condition{D0 == 10} RBSYS_Error_ClockConfigurationInvalid
      *            @Bit[31..0] @condition{D0 == 11} RBSYS_Error_TimerInterruptMonitoring
      *          }
      *  @Data_D1{ @Bit[31..16] @condition{D0 == 0}  lower 16 bit of EI level exception cause register EIIC (RH850) or IRQ ID register ICC_IAR1 (Stellar)
      *            @Bit[15..0]  @condition{D0 == 0}  lower 16 bit of FE level exception cause register FEIC (RH850) or FIQ ID register ICC_IAR0 (Stellar)
      *            @Bit[31..28] @condition{D0 == 1}  nesting counter
      *            @Bit[27..26] @condition{D0 == 1}  lock type (see RBSYS_locktype_t)
      *            @Bit[25..24] @condition{D0 == 1}  core id
      *            @Bit[23..0]  @condition{D0 == 1}  monitoring address (see RBFS_SysDebugUnbalancedLock_ON)
      *            @Bit[31..0]  @condition{D0 == 2}  address of lock location
      *            @Bit[31..0]  @condition{D0 == 3}  corresponding address of wrong API (only in case RBFS_TaskSync_ON)
      *            @Bit[31..0]  @condition{D0 == 4}  timer delta (see RBSYS_PRC_TimerMonitoring)
      *            @Bit[31..0]  @condition{D0 == 5}  corresponding module standby register
      *            @Bit[31..0]  @condition{D0 == 6}  corresponding module standby register
      *            @Bit[31..0]  @condition{D0 == 7}  PC when SVP exception occurred (only in case RBFS_TPSWSVPRestrictions_ON)
      *            @Bit[31..0]  @condition{D0 == 8}  see RBSYS_PRC_FSW_VerifyFinalGuardSettings
      *            @Bit[0]      @condition{D0 == 9}  start address of inactive area is different than start address of flashbank A
      *            @Bit[1]      @condition{D0 == 9}  end address of inactive area is different than end address of flashbank A
      *            @Bit[2]      @condition{D0 == 9}  start address of inactive area is greater than end address of inactive area
      *            @Bit[31..0]  @condition{D0 == 10} 0xDEADBEEF
      *            @Bit[16]     @condition{D0 == 11} TAUD overflow flag
      *            @Bit[15..0]  @condition{D0 == 11} TAUD capture register content
      *          }
      */
    RBSYS_SYSErrorHookFailureReported = TRUE;
    RBHSWESR_ReportElShutdownErrorWithEnvData(DemConf_DemEventParameter_RBSYS_SYSErrorHook, DEM_EVENT_STATUS_FAILED, (uint32)d0, d1);
  }


  /**
   * @brief Report RBSYS failure "RBSYS_StackOverUnderFlow" for stack faults (over- or underflow)
   *
   *  Overflow: The stack is too small for the application
   *  Underflow: Can only occur in case of SW or compiler faults
   *
   * @return void
   */
  void RBSYS_setStackOverUnderFlowError(uint32 d0, uint32 d1)
  {
    /** @Debuginfo{RBSYS_StackOverUnderFlow}
     *
     *  @FWC_Requirements{ Gen_SWCS_HSW_uC_Base_SYS-217 }
     *
     *  @Data_D0{ @Bit[31..0] StackFaultBitMask (=> which limit is reached, 3 limits per stack)}
     *  @Data_D1{ @Bit[31..0] free stack between limit marker and stack end}
     */
    RBHSWESR_ReportElShutdownErrorWithEnvData(DemConf_DemEventParameter_RBSYS_StackOverUnderFlow, DEM_EVENT_STATUS_FAILED, d0, d1);
  }


  /**
   * @brief Report RBSYS failure "RBSYS_TaskOverRun"
   *
   * SYS specific monitoring within x1 timer interrupt for task deadline in addition to OS monitoring (OS_LIMIT).
   * Task must be finished when x1 timer interrupt occurs, which activates next relevant basecycle.
   *
   * @return void
   */
  void RBSYS_setTaskOverRunError(uint32 d0)
  {
    uint32 d1;
    uint32 i;
    uint32 taskIndex = 0;

    // Get the highest task index in d0 as this coincides with the highest priority task having a task overrun
    // todo: replace with something that is using intrinsics __SCH1L (see WI 2243401)
    for(i = 0; i < OS_NUM_TASKS; i++)
    {
      if(((d0 >> i) & 0x1u) == 0x1u)
      {
        taskIndex = i;
      }
    }
    // Get address of task entry function corresponding to highest task index in d0
    d1 = (uint32)(OS_INDEX_TO_TASKTYPE(taskIndex)->entry_function);

    /** @Debuginfo{RBSYS_TaskOverRun}
     *
     *  @FWC_Requirements{ Gen_SWCS_HSW_uC_Base_SYS-252 }
     *
     *  @Data_D0{ @Bit[31..0] index of related OS tasks (e.g. bit0=x24, bit1=x8 ...)}
     *  @Data_D1{ @Bit[31..0] Address of highest priority task that has a task overrun}
     */
    RBHSWESR_ReportElShutdownErrorWithEnvData(DemConf_DemEventParameter_RBSYS_TaskOverRun, DEM_EVENT_STATUS_FAILED, d0, d1);
  }


  #if (  (RBFS_SysMaxTaskx1Jitter == RBFS_SysMaxTaskx1Jitter_5)  \
      || (RBFS_SysMaxTaskx1Jitter == RBFS_SysMaxTaskx1Jitter_15) \
      )
    /**
     * @brief Report RBSYS failure "RBSYS_TaskJitter"
     *
     * RBSYS specific task jitter monitoring in addition to the overall monitoring by the OS and TaskMon.
     * This monitoring is implemted only for some IO sensitive processes.
     *
     * @return void
     */
    void RBSYS_setTaskJitterError(uint32 d0, uint32 d1)
    {
      /** @Debuginfo{RBSYS_TaskJitter}
       *
       *  @FWC_Requirements{ Gen_SWCS_HSW_uC_Base_SYS-218 }
       *
       *   @Data_D0{ @Bit[31..0] default timerticks of the related task}
       *   @Data_D1{ @Bit[31..0] jitter of the task in timerticks}
       */
      RBHSWESR_ReportElShutdownErrorWithEnvData(DemConf_DemEventParameter_RBSYS_TaskJitter, DEM_EVENT_STATUS_FAILED, d0, d1);
    }
  #endif


  /**
   * @brief Central "good check request" hook for RBSYS related failure words
   *
   * @return void
   */
  void RBSYS_setGoodCheckRequest(Dem_EventIdType rbsys_event_id)
  {
    RBHSWESR_ReportElShutdownError(rbsys_event_id, DEM_EVENT_STATUS_PASSED);
  }

#endif

/** @} */
/* End ingroup RBSYS */
