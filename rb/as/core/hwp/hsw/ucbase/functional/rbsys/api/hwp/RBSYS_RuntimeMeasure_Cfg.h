#ifndef RBSYS_RUNTIMEMEASURE_CFG_H__
#define RBSYS_RUNTIMEMEASURE_CFG_H__

/**
 * @ingroup RBSYS
 * @{
 *
 * @file
 * @brief Configuration header of rba_Runtime derived from rba_Runtime_Cfg.h
 *
 * @copyright
 * Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
 * We reserve all rights of disposal such as copying and passing on to third parties.
 */


#include "RBSYS_Config.h"


#include "RBSYS_SystemTimer.h"
#include "RBSYS_CpuInfo.h"

/* Assert supported configurations: switches, parameters, constants, ... */
RB_ASSERT_SWITCH_SETTINGS(RBFS_RTMOWINRTMMEASURE,
                          RBFS_RTMOWINRTMMEASURE_OFF,
                          RBFS_RTMOWINRTMMEASURE_ON);

RB_ASSERT_SWITCH_SETTINGS(RBFS_uCFamily,
                          RBFS_uCFamily_RenesasP1x,
                          RBFS_uCFamily_RenesasU2A,
                          RBFS_uCFamily_STMStellar);

RB_ASSERT_SWITCH_SETTINGS(RBFS_SysSystemLoadCalc,
                          RBFS_SysSystemLoadCalc_20ms,
                          RBFS_SysSystemLoadCalc_120ms,
                          RBFS_SysSystemLoadCalc_1000ms);

RB_ASSERT_SWITCH_SETTINGS(RBFS_TaskSchemeExtension,
                          RBFS_TaskSchemeExtension_None,
                          RBFS_TaskSchemeExtension_VMPS,
                          RBFS_TaskSchemeExtension_HostCore0GuestCore1,
                          RBFS_TaskSchemeExtension_AB15);

RB_ASSERT_SWITCH_SETTINGS(RBFS_EmulationDevice,
                          RBFS_EmulationDevice_None,
                          RBFS_EmulationDevice_RenesasD3ED,
                          RBFS_EmulationDevice_RenesasD5ED,
                          RBFS_EmulationDevice_RenesasD7ED,
                          RBFS_EmulationDevice_RenesasM6ED,
                          RBFS_EmulationDevice_STMP7ED);

RB_ASSERT_SWITCH_SETTINGS(RBFS_GlobalSWResourceOptimizationStrategy,
                          RBFS_GlobalSWResourceOptimizationStrategy_Balanced,
                          RBFS_GlobalSWResourceOptimizationStrategy_RamLight,
                          RBFS_GlobalSWResourceOptimizationStrategy_RamFull,
                          RBFS_GlobalSWResourceOptimizationStrategy_RomLight,
                          RBFS_GlobalSWResourceOptimizationStrategy_RomFull,
                          RBFS_GlobalSWResourceOptimizationStrategy_RuntimeLight,
                          RBFS_GlobalSWResourceOptimizationStrategy_RuntimeFull);


#define RBSYS_RBA_RUNTIME_MON_LIST_END {NULL_PTR, NULL_PTR}


/* Enable/disable version info api (STD_ON or STD_OFF) */
#define RBSYS_RBA_RUNTIME_VERSIONINFOAPI            STD_OFF



/* How often is the main function called in one second?
 * This depends on the task in which the runnable is integrated
 * E.g. 100ms task -> 10
         40ms task -> 25 */
#define RBSYS_RBA_RUNTIME_MAINFCT_CALLS_PER_SECOND  100   /* Gen9.3: rba runs in 10 ms task */

/* How fast is the free running counter clocked */
#define RBSYS_RBA_RUNTIME_TICKS_PER_SECOND          (1000000*RBSYS_TIMERTICKS_PER_US)

/* Enable/disable callback to acquire idle time for systems with background tasks
 * If this is off the idle time of the idle callback of the OS is used
 * If this is on the callback <rba_Runtime_Cbk_GetIdleTime> must be supplied
 * Prototype in rba_Runtime.h:
FUNC (uint32, RBA_RUNTIME_CALLOUT_CODE) rba_Runtime_Cbk_GetIdleTime (uint8_least coreId);
 * It must return the consumed time in idle mode in accumulated ticks (in a free running counter way that overflows
 * from max of uint32 to 0) */
#define RBSYS_RBA_RUNTIME_IDLETIMECALLBACK   STD_OFF


/*! Controlled measurement ********************************************************************************************/

#if (RBFS_RTMOWINRTMMEASURE == RBFS_RTMOWINRTMMEASURE_OFF)
  /* Disable run-time controlled measurement (e.g. over WinRtm) */
  #define RBSYS_RBA_RUNTIME_CTRL              STD_OFF
#else
  /* Enable run-time controlled measurement (e.g. over WinRtm) */
  #define RBSYS_RBA_RUNTIME_CTRL              STD_ON
#endif

/* Software based measurement configured */
#define RBSYS_RBA_RUNTIME_TARGET_GENERIC  0u
#define RBSYS_RBA_RUNTIME_TARGET_IFX      1u
#define RBSYS_RBA_RUNTIME_TARGET_JDP      2u
#define RBSYS_RBA_RUNTIME_TARGET          RBSYS_RBA_RUNTIME_TARGET_GENERIC

/* Number of concurrent measurements per core.
   Increasing this value will speed up the batch measurement but does occupy RAM and breakpoint units or runtime
   in case of missing hardware support.
   The value must be between 1 and 4

   For hardware supported measurements:
   Breakpoint unit 0 and 1 is occupied in setting <1>
   On IFX: 0 to 2 in setting <2>, 0 to 3 in setting <3> and 0 to 4 in setting <4>
   On JDP: 0 to 3 in setting <2>, 0 to 5 in setting <3> and 0 to 7 in setting <4>
   If a debugger is used during measurements these breakpoint units must be disable in the breakpoint configuration of
   the debugger. */
/* if RBA_RUNTIME_CTRL is off this value has no impact */
#define RBSYS_RBA_RUNTIME_CTRL_CONC_MSRS            2  /* set to 2 to increase WinRTM total measure time */

/* Definition of interface type for controlled measurement. If set to CalibMeas the definition of the input structure
   is "calibration" and in some cases leads to a constant structure in flash. So it may not be accessable from a
   debugger, only from a measure/calibration tool like INCA. */
#define RBSYS_RBA_RUNTIME_INTERFACE_DEBUGGER        1
#define RBSYS_RBA_RUNTIME_INTERFACE_CALIBMEAS       2
#define RBSYS_RBA_RUNTIME_INTERFACE_DUALMODE        3
#define RBSYS_RBA_RUNTIME_INTERFACE                 RBSYS_RBA_RUNTIME_INTERFACE_DEBUGGER

/* Bit mask to exclude cores from controlled measurement (if no task runs on it).
   Examples:
   0 -> no core is excluded,
   1 -> logical core 0 is excluded,
   2 -> logical core 1 is excluded,
   3 -> logical core 0 and core 1 are excluded, etc. */
#define RBSYS_RBA_RUNTIME_CTRL_EXCLUDED_CORES 0u


/*! Task/ISR and systemload monitoring ********************************************************************************/

/* How often should the monitoring build statistical values per minute (systemload and stats that are turned on below).
 * In a time frame the free running counter must not overflow (e.g. with 333MHz a timeframe is max. 12,8seconds -> 5) */
#if (RBFS_SysSystemLoadCalc == RBFS_SysSystemLoadCalc_20ms)
  /* Gen9.3:  SystemLoad calculated each 20ms and replaces RBSYS specific idle measurement */
  #define RBSYS_RBA_RUNTIME_MON_SAMPLES_PER_MINUTE    3000
#elif (RBFS_SysSystemLoadCalc == RBFS_SysSystemLoadCalc_120ms)
  /* Gen9.3:  SystemLoad calculated each 120ms and replaces RBSYS specific idle measurement */
  #define RBSYS_RBA_RUNTIME_MON_SAMPLES_PER_MINUTE    500
#else
  /* Gen9.3:  SystemLoad calculated each 1000ms and replaces RBSYS specific idle measurement */
  #define RBSYS_RBA_RUNTIME_MON_SAMPLES_PER_MINUTE    60
#endif

/* Bit mask to exclude cores from central system load measurement (to use core specific system load API).
   Examples:
   0 -> no core is excluded,
   1 -> logical core 0 is excluded,
   2 -> logical core 1 is excluded,
   3 -> logical core 0 and core 1 are excluded, etc. */
#define RBSYS_RBA_RUNTIME_MON_LOAD_MASK             ((uint32)0)

/* additional feature for the task measurement, provides the task counter/cycle*/
#define RBSYS_RBA_RUNTIME_MON_TASK_COUNT_REF          STD_ON

/* Should the monitoring build statistical values for ISRs and tasks */
#if (  (RBFS_EmulationDevice == RBFS_EmulationDevice_None) \
    && (  (RBFS_GlobalSWResourceOptimizationStrategy == RBFS_GlobalSWResourceOptimizationStrategy_RamFull) \
       || (RBFS_GlobalSWResourceOptimizationStrategy == RBFS_GlobalSWResourceOptimizationStrategy_RuntimeFull) \
       || (RBFS_GlobalSWResourceOptimizationStrategy == RBFS_GlobalSWResourceOptimizationStrategy_RomFull) \
       ) \
    )
  /* STD_OFF for fully resource optimized systems */
  #define RBSYS_RBA_RUNTIME_MON_ISR_STAT              STD_OFF
  #define RBSYS_RBA_RUNTIME_MON_TASK_STAT             STD_OFF
#else
  /* STD_ON for all other systems */
  #define RBSYS_RBA_RUNTIME_MON_ISR_STAT              STD_ON
  #define RBSYS_RBA_RUNTIME_MON_TASK_STAT             STD_ON
#endif



/* ==> consider RBSYS_RuntimeMeasure.c which describes the MM6 labels and must be adapted when changing
       the order or number of elements of RBSYS_RBA_RUNTIME_MON_ISR_LIST & RBSYS_RBA_RUNTIME_MON_TASK_LIST
 */

/* Which ISRs should be monitored, the order will define the index in the monitoring array output
 * ISR monitoring can be deactivated with an undefined list
 * This list must end with double zero! */
#if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
  #if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)
      #define RBSYS_RBA_RUNTIME_MON_ISR_LIST                    \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRMTTCANI0),              \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRMCAN0I0),               \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRMCAN1I0),               \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRMCAN2I0),               \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRFLX0LINE0),             \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRFLX1LINE0),             \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRSTM04),                 \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRSTM05),                 \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRSWINT0),                \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRRLIN30RX),              \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRRLIN30STATUS),          \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRRLIN31RX),              \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRRLIN31STATUS),          \
        RBA_RUNTIME_MON_LIST_ENTRY(ISR0p5ms),                 \
        RBSYS_RBA_RUNTIME_MON_LIST_END
  #else
    #define RBSYS_RBA_RUNTIME_MON_ISR_LIST                    \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRMTTCANI0),              \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRMCAN0I0),               \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRMCAN1I0),               \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRMCAN2I0),               \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRFLX0LINE0),             \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRFLX1LINE0),             \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRSTM04),                 \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRSTM05),                 \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRSWINT0),                \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRRLIN30RX),              \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRRLIN30STATUS),          \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRRLIN31RX),              \
        RBA_RUNTIME_MON_LIST_ENTRY(ISRRLIN31STATUS),          \
        RBSYS_RBA_RUNTIME_MON_LIST_END
  #endif

#elif( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )

  #define RBSYS_RBA_RUNTIME_MON_ISR_LIST                    \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRCAN0REC),               \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRCAN0TRX),               \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRCAN1REC),               \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRCAN1TRX),               \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRCAN2REC),               \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRCAN2TRX),               \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRCAN6REC),               \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRCAN6TRX),               \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRCAN8REC),               \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRCAN8TRX),               \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRFLX0LINE0),             \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRFLX1LINE0),             \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRSTM04),                 \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRSTM05),                 \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRSWINT0),                \
      RBSYS_RBA_RUNTIME_MON_LIST_END

#elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )

  #define RBSYS_RBA_RUNTIME_MON_ISR_LIST                    \
      RBA_RUNTIME_MON_LIST_ENTRY(ISRCommonTimer),           \
      RBSYS_RBA_RUNTIME_MON_LIST_END

#else
  #error ("RBA_Runtime List of monitored ISRs is undefined")
#endif


/* Which tasks should be monitored, the order will define the index in the monitoring array output
 * This list must end with double zero! */
#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)

  #define RBSYS_RBA_RUNTIME_MON_TASK_LIST                             \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx24),                \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx8),                 \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx4),                 \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx2),                 \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx1Low),              \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskFlexray),                       \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx1High),             \
      RBA_RUNTIME_MON_LIST_ENTRY(Task1ms),                           \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskInit),                          \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskInitP),                         \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx2p),                \
      RBA_RUNTIME_MON_LIST_ENTRY(Task0p5ms),                         \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx4pLow),             \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx200Background),     \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskEventCtrlExtPrio1),             \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskEventCtrlExtPrio2),             \
      RBSYS_RBA_RUNTIME_MON_LIST_END

#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)

  #define RBSYS_RBA_RUNTIME_MON_TASK_LIST                             \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx24),                \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx8),                 \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx4),                 \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx2),                 \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx1Low),              \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskFlexray),                       \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx1High),             \
      RBA_RUNTIME_MON_LIST_ENTRY(Task1ms),                           \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskInit),                          \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskInitP),                         \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx2p),                \
      RBA_RUNTIME_MON_LIST_ENTRY(Task0p5ms),                         \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx1Guest),            \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx2Guest),            \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx4Guest),            \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx10Guest),           \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx20Guest),           \
      RBSYS_RBA_RUNTIME_MON_LIST_END

#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_AB15)

  #define RBSYS_RBA_RUNTIME_MON_TASK_LIST                             \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx24),                \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx8),                 \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx4),                 \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx2),                 \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx1Low),              \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskFlexray),                       \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx1High),             \
      RBA_RUNTIME_MON_LIST_ENTRY(Task1ms),                           \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskInit),                          \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskInitP),                         \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx2p),                \
      RBA_RUNTIME_MON_LIST_ENTRY(Task0p5ms),                         \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx10),                \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx20),                \
      RBSYS_RBA_RUNTIME_MON_LIST_END

#else

  #define RBSYS_RBA_RUNTIME_MON_TASK_LIST                            \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx24),                \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx8),                 \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx4),                 \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx2),                 \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx1Low),              \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskFlexray),                       \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx1High),             \
      RBA_RUNTIME_MON_LIST_ENTRY(Task1ms),                           \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskInit),                          \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskInitP),                         \
      RBA_RUNTIME_MON_LIST_ENTRY(TaskBaseCtrlCycx2p),                \
      RBA_RUNTIME_MON_LIST_ENTRY(Task0p5ms),                         \
      RBSYS_RBA_RUNTIME_MON_LIST_END

#endif


/*! MT measurement *****************************************************************************************************/

/* Should the MT measurement calibration values be calculated on each core?
 * Attention:
 * If this parameter is set to STD_ON, this requires the scheduling of rba_Runtime_Init on all cores!
 * If this parameter is set to STD_OFF, this requires the scheduling of rba_Runtime_Init on one core!
 */
#define RBSYS_RBA_RUNTIME_MT_CORESPECIFIC_CALIB STD_OFF

/** @} */
/* End ingroup RBSYS */

#endif /* End of multiple include protection */
