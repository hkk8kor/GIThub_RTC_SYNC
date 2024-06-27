#ifndef RBSYS_OSSERVICES_H__
#define RBSYS_OSSERVICES_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief OS services
 *
 * RBSYS specific abstraction of OS services
 * These services are not supported outside of application software
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"

#if(RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION)
  /* used interfaces */
  #include "Os.h"


  /* Assert supported configurations: switches, parameters, constants, ... */
  RB_ASSERT_SWITCH_SETTINGS(RBFS_MCORE,
                            RBFS_MCORE_OFF,
                            RBFS_MCORE_ON);
  RB_ASSERT_SWITCH_SETTINGS(RBFS_HexBlockBuild,
                            RBFS_HexBlockBuild_BOOTMANAGER,
                            RBFS_HexBlockBuild_BOOTLOADER,
                            RBFS_HexBlockBuild_RBBOOTLOADER,
                            RBFS_HexBlockBuild_APPLICATION);
  RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                            RBFS_uCFamily_RenesasP1x,
                            RBFS_uCFamily_RenesasU2A,
                            RBFS_uCFamily_RenesasU2C,
                            RBFS_uCFamily_STMStellar);
  RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSchemeExtension,
                            RBFS_TaskSchemeExtension_None,
                            RBFS_TaskSchemeExtension_VMPS,
                            RBFS_TaskSchemeExtension_HostCore0GuestCore1,
                            RBFS_TaskSchemeExtension_AB15);
  RB_ASSERT_SWITCH_SETTINGS(RBFS_SysFlxrTask,
                            RBFS_SysFlxrTask_ON,
                            RBFS_SysFlxrTask_OFF);



  /* Mapping of OS task type to RBSYS specific task type - in general OS task type should not be used, therefore use RBSYS specific task type */
  typedef TaskType RBSYS_TaskType;

  #define RBSYS_TaskType_TaskInit               TaskInit
  #define RBSYS_TaskType_TaskInitP              TaskInitP
  #define RBSYS_TaskType_Task0p5ms              Task0p5ms
  #define RBSYS_TaskType_Task1ms                Task1ms
  #define RBSYS_TaskType_TaskBaseCtrlCycx1High  TaskBaseCtrlCycx1High
  #define RBSYS_TaskType_TaskFlexray            TaskFlexray
  #define RBSYS_TaskType_TaskBaseCtrlCycx1Low   TaskBaseCtrlCycx1Low
  #define RBSYS_TaskType_TaskBaseCtrlCycx2      TaskBaseCtrlCycx2
  #define RBSYS_TaskType_TaskBaseCtrlCycx2p     TaskBaseCtrlCycx2p
  #define RBSYS_TaskType_TaskBaseCtrlCycx4      TaskBaseCtrlCycx4
  #define RBSYS_TaskType_TaskBaseCtrlCycx8      TaskBaseCtrlCycx8
  #define RBSYS_TaskType_TaskBaseCtrlCycx24     TaskBaseCtrlCycx24
  #define RBSYS_TaskType_Invalid                INVALID_TASK

  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
    #define RBSYS_TaskType_TaskBaseCtrlCycx4pLow           TaskBaseCtrlCycx4pLow
    #define RBSYS_TaskType_TaskBaseCtrlCycx200Background   TaskBaseCtrlCycx200Background
    #define RBSYS_TaskType_TaskEventCtrlExtPrio1           TaskEventCtrlExtPrio1
    #define RBSYS_TaskType_TaskEventCtrlExtPrio2           TaskEventCtrlExtPrio2
  #elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
    #define RBSYS_TaskType_TaskBaseCtrlCycx1Guest          TaskBaseCtrlCycx1Guest
    #define RBSYS_TaskType_TaskBaseCtrlCycx2Guest          TaskBaseCtrlCycx2Guest
    #define RBSYS_TaskType_TaskBaseCtrlCycx4Guest          TaskBaseCtrlCycx4Guest
    #define RBSYS_TaskType_TaskBaseCtrlCycx10Guest         TaskBaseCtrlCycx10Guest
    #define RBSYS_TaskType_TaskBaseCtrlCycx20Guest         TaskBaseCtrlCycx20Guest
  #elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
    #define RBSYS_TaskType_TaskBaseCtrlCycx10              TaskBaseCtrlCycx10
    #define RBSYS_TaskType_TaskBaseCtrlCycx20              TaskBaseCtrlCycx20
  #endif

  static inline uint32 RBSYS_GetTaskIndex(RBSYS_TaskType task)
  {
    return OS_TASKTYPE_TO_INDEX(task);
  }


  typedef ISRType  RBSYS_ISRType;

  #define RBSYS_IsrType_ISRFLX0LINE0            ISRFLX0LINE0
  #define RBSYS_IsrType_ISRFLX1LINE0            ISRFLX1LINE0
  #define RBSYS_IsrType_ISRSTM04                ISRSTM04
  #define RBSYS_IsrType_ISRSTM05                ISRSTM05
  #define RBSYS_IsrType_ISRSWINT0               ISRSWINT0

  #if( RBFS_uCFamily == RBFS_uCFamily_RenesasP1x )
    #define RBSYS_IsrType_ISRMCAN0I0              ISRMCAN0I0
    #define RBSYS_IsrType_ISRMCAN1I0              ISRMCAN1I0
    #define RBSYS_IsrType_ISRMCAN2I0              ISRMCAN2I0
    #define RBSYS_IsrType_ISRMTTCANI0             ISRMTTCANI0
    #define RBSYS_IsrType_ISRRLIN30RX             ISRRLIN30RX
    #define RBSYS_IsrType_ISRRLIN30STATUS         ISRRLIN30STATUS
    #define RBSYS_IsrType_ISRRLIN31RX             ISRRLIN31RX
    #define RBSYS_IsrType_ISRRLIN31STATUS         ISRRLIN31STATUS
    #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
      #define RBSYS_IsrType_ISR0p5ms              ISR0p5ms
    #endif

  #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
    #define RBSYS_IsrType_ISRCAN0REC              ISRCAN0REC
    #define RBSYS_IsrType_ISRCAN0TRX              ISRCAN0TRX
    #define RBSYS_IsrType_ISRCAN1REC              ISRCAN1REC
    #define RBSYS_IsrType_ISRCAN1TRX              ISRCAN1TRX
    #define RBSYS_IsrType_ISRCAN2REC              ISRCAN2REC
    #define RBSYS_IsrType_ISRCAN2TRX              ISRCAN2TRX
    #define RBSYS_IsrType_ISRCAN6REC              ISRCAN6REC
    #define RBSYS_IsrType_ISRCAN6TRX              ISRCAN6TRX
    #define RBSYS_IsrType_ISRCAN8REC              ISRCAN8REC
    #define RBSYS_IsrType_ISRCAN8TRX              ISRCAN8TRX
  #elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C )
    //todo: fill
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    #warning("ISR definitions are missing for STM Stellar")
  #else
    #error ("Exception: Implementation for this uCFamily is missing")
  #endif




  /* Mapping of OS CoreID's to RBSYS specific CoreID's */
  #define RBSYS_OS_CORE_FOR_TaskBaseCtrlCycx2       OS_CORE_FOR_TaskBaseCtrlCycx2
  #define RBSYS_OS_CORE_FOR_TaskBaseCtrlCycx1High   OS_CORE_FOR_TaskBaseCtrlCycx1High
  #define RBSYS_OS_CORE_FOR_TaskBaseCtrlCycx1Low    OS_CORE_FOR_TaskBaseCtrlCycx1Low
  #define RBSYS_OS_CORE_FOR_ISRSWINT0               OS_CORE_FOR_ISRSWINT0
  #define RBSYS_OS_CORE_FOR_Task1ms                 OS_CORE_FOR_Task1ms

  #if (RBFS_MCORE == RBFS_MCORE_OFF)
    //OS_CORE_IDs are not available in case of single core OS -> therefore explicit define within RBSYS
    #define OS_CORE_ID_0    (0u)
    #define OS_CORE_ID_1    (1u)

    #define OS_CORE_FOR_ISRSTM04      OS_CORE_ID_0
    #define OS_CORE_FOR_ISRSTM05      OS_CORE_ID_0
    #define OS_CORE_FOR_ISRSWINT0     OS_CORE_ID_0

    #define OS_CORE_FOR_TaskBaseCtrlCycx2       OS_CORE_ID_0
    #define OS_CORE_FOR_TaskBaseCtrlCycx1High   OS_CORE_ID_0
    #define OS_CORE_FOR_TaskBaseCtrlCycx1Low    OS_CORE_ID_0
    #define OS_CORE_FOR_Task1ms                 OS_CORE_ID_0
  #endif

  typedef enum {
    RBSYS_OperationMode_PreInit = 0u, //< uC Startup, Initial Safety Tests, OS is NOT started yet
    RBSYS_OperationMode_Init,        //< OS has been started, Init Task is running
    RBSYS_OperationMode_Cyclic       //< Cyclic Task scheme is used
  } RBSYS_OperationMode_n;

  static_assert( RBSYS_OperationMode_PreInit == 0u, "RBSYS_OperationMode_PreInit shall always be 0 (default after reset, RAM zeroing and CInit)");

  /**
    * @brief  Get the current RBSYS Operation Mode {PreInit, Init, Cyclic} which provides information on what is
    *         the active System Startup / Runtime Phase.
    *
    * Hint: Can e.g. be used to decide if OS APIs may already be used.
    *
    * Attention: For Bootblock, this API is not available. If made available, it will always return RBSYS_OperationMode_PreInit!!!
    *
    * @return Current RBSYS Operation Mode [RBSYS_OperationMode_n]
    */
  extern RBSYS_OperationMode_n RBSYS_GetCurrentOperationMode(void);

  /**
  * This service may not be called from interrupt handler, idle task and startup phases before TaskInit!
  *
  * @returns the currently running task RBSYS_TaskType_XXX.
  */
  extern RBSYS_TaskType RBSYS_GetCurrentTask(void);

  #if( RBFS_SysFlxrTask == RBFS_SysFlxrTask_ON )
    /**
    * Flexray task will be activated directly by CUBAS via this interface and not from RBSYS itself!
    *
    * @returns void
    */
    extern void RBSYS_ActivateFlexrayTask(void);
  #endif

  /**
  * This service may not be called from interrupt handler, idle task and startup phases before TaskInit!
  *
  * @param [out] TaskID reference to the running task
  *
  * @returns values of Os type StatusType (no conversion to RBSYS_StatusType due to usage in cubas where pure Os type is required)
  */
  extern StatusType RBSYS_GetTaskID(TaskRefType TaskID);

  // #if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  //   todo: clarify why prototype is missing from OS side
  //   static void Os_adjust_stack(uint32 val);
  // #endif

#endif /* RBFS_HexBlockBuild_APPLICATION */

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
