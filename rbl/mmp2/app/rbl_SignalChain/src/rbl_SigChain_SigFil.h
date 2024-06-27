/// @file rbl_SigChain_SigFil.h
/// @brief definitions and functions used within the signal chain - SignalFilter
/// @copyright (C) 2020 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_SIGCHAIN_SIGFIL_H
#define RBL_SIGCHAIN_SIGFIL_H

#include "rbl_SigChain.h"   // for data types
#include "rbl_ImuGenFunc_Types.h"
#include "rbl_SigChain_Nvm_priv.h"

#define RBL_SIGCHN_FIL 2  /* filter steps for second order section filter */

typedef struct /*TOOL_SCAN*/
{
rbl_SigChain_Filter_t filVal[RBL_SIGCHN_FIL];
} rbl_SigChain_FilterArray_t;

typedef struct /*TOOL_SCAN*/
{
    float32 filTabs[2][2];
}rbl_SigChain_FilTabs_t;

/*Filter flush time: */
#define RBL_SIGCHAIN_SIGFILNONEFLUSH  0u
#define RBL_SIGCHAIN_SIGFIL45HZFLUSH 28u // 28ms Flush time for 45Hz filter
#define RBL_SIGCHAIN_SIGFIL20HZFLUSH 50u // 50ms Flush time for 20Hz filter

#define RBL_SIGCHAIN_TIMESTAMPDELAYMS45HZ 6.56f  //Timestamp delay of 6.56 ms for 45Hz Filter
#define RBL_SIGCHAIN_TIMESTAMPDELAYMS20HZ 13.83f // Timestamp delay of 13.83 ms for 20Hz Filter
#define RBL_SIGCHAIN_TIMESTAMPDELAYMSNONE 0.0f // No Time Delay

#define RBL_SIGCHAIN_FIRSTFILTER  0
#define RBL_SIGCHAIN_SECONDFILTER 1

typedef struct
{
  uint16 counter[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC];
} rbl_SigChain_AccFilCnt_t;

typedef struct
{
  uint16 counter[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT];
} rbl_SigChain_RateFilCnt_t;

typedef struct
{
  rbl_SigChain_FilTabs_t tabs[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC][RBL_SIGCHN_FIL];
} rbl_SigChain_AccFilTabsSteps_t;

typedef struct
{
  rbl_SigChain_FilTabs_t tabs[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT][RBL_SIGCHN_FIL];
} rbl_SigChain_RateFilTabsSteps_t;

typedef struct
{
  rbl_SigChain_FilTabs_t tabs[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ACC];
} rbl_SigChain_AccFilTabs_t;

typedef struct
{
  rbl_SigChain_FilTabs_t tabs[RBL_IMUSTDTYPES_AXIS_NO][RBL_IMUSTDTYPES_MAX_NO_OF_RED_ROT];
} rbl_SigChain_RateFilTabs_t;

typedef struct
{
  rbl_SigChain_AccFilCnt_t * initCnt;
  rbl_SigChain_AccFilCnt_t * Cnt;
  rbl_SigChain_AccFilTabsSteps_t *steps;
  rbl_SigChain_AccFilTabs_t *derived;
  rbl_SigChain_AccFilTabs_t *phaCorrn;
}rbl_SigChain_AccFilData_t;

typedef struct
{
  rbl_SigChain_RateFilCnt_t * initCnt;
  rbl_SigChain_RateFilCnt_t * Cnt;
  rbl_SigChain_RateFilTabsSteps_t *steps;
  rbl_SigChain_RateFilTabs_t *derived;
  rbl_SigChain_RateFilTabs_t *phaCorrn;
}rbl_SigChain_RateFilData_t;

typedef struct
{
  rbl_SigChain_AccFilData_t acc;
  rbl_SigChain_RateFilData_t rate;
  rbl_SigChain_FilterArray_t * filter;
  uint16 * flush;
  uint32 * timestampdelaytick;
}rbl_SigChain_FilData_t;

#if (RBFS_SigChain45HzFilter == RBFS_SigChain45HzFilter_Available)
extern rbl_SigChain_FilterArray_t rbl_SigChain_FilVal45Hz;
#endif
#if (RBFS_SigChainNoFilter ==  RBFS_SigChainNoFilter_Available)
extern rbl_SigChain_FilterArray_t rbl_SigChain_FilValNoFilter;
#endif

#if (RBFS_SigChain20HzFilter == RBFS_SigChain20HzFilter_Available)
extern rbl_SigChain_FilterArray_t rbl_SigChain_FilVal20Hz;
#endif


/* -----------------Signal Chain Init functions ---------------------------*/

/// @c_file rbl_SigChain_SigFil.c
/// @brief Initialisation of Filter values
///
/// @pre part of signal chain
/// @param[in]  flush time value for the selected filter for First Filter
/// @param[in]  timestampdelay value in usec for the selected filter
/// @param[in]  *filter - Filter coefficient value
///
/// @details
///  For RBFS_NvmBasedFilter_ON, this function initialises with the selected filter coefficient, Flush time and time stamp delay
///  For RBFS_NvmBasedFilter_OFF, filter coefficient, Flush time and time stamp delay is set to NULL to avoid overwriting of the hardcoded Filter values
void rbl_SigChain_InitFilter(const rbl_SigChain_FilterArray_t* filter, uint16 flush, float timestampdelay);

/// @c_file rbl_SigChain_SigFil.c
/// @brief Initialisation of Filter values for second filter
///
/// @pre part of signal chain
/// @param[in]  flush time value for the selected filter
/// @param[in]  timestampdelay value in usec for the selected filter
/// @param[in]  *filter - Filter coefficient value
///
/// @details
/// filter coefficient, Flush time and time stamp delay is set to NULL to avoid overwriting of the hardcoded Filter values
void rbl_SigChain_InitFilter2(const rbl_SigChain_FilterArray_t* filter, uint16 flush, float timestampdelay);

/* -----------------Signal Chain cyclic functions ---------------------------*/
/// @c_file rbl_SigChain_SigFil.c
/// @brief Signal Filtering logic includes - Update of Filter, Phase Correction, Update Derivation and Update Status
///
/// @pre part of signal chain
/// @param[in]  filterNumber - Filter Number
/// @param[in]  *signalSetRaw - signals in IMU coordinate system
/// @param[out] *signalSetFil - filtered signal set
/// @param[out] *setsignalSetDer - derived signal set
///
/// @details
///  Below are the steps involved in the Signal Filter
/// @startuml
/// start
/// !include SignalFilter.puml
/// end
/// @enduml
/// Update of Filter Tab is done as below
/// @startuml
/// start
/// !include SignalFilter0_FilterTab.puml
/// end
/// @enduml
/// Step 1) Update Of Filter
/// Call Filter function with parameters @ref rbl_SigChain_FilVal, @ref rbl_SigChain_AccFilTabs and @ref filVal
/// @startuml
/// start
/// !include SignalFilter1_UpdateFilter.puml
/// end
/// @enduml
/// Step 2) Phase Correction
/// Call Filter function with parameters @ref rbl_SigChain_PhaseCorrnCfg, @ref rbl_SigChain_AccPhaCorrnTabs and @ref filVal
/// @startuml
/// start
/// !include SignalFilter2_PhaseCorrection.puml
/// end
/// @enduml
/// Step 3) Update Derivation
/// Call Filter function with parameters @ref rbl_SigChain_DerFilCfg, @ref rbl_SigChain_AccDerFilTabs and @ref filVal
/// @startuml
/// start
/// !include SignalFilter3_UpdateDerivation.puml
/// end
/// @enduml
/// Step 4) Update Status
/// @startuml
/// !include SignalFilter4_UpdateStatus.puml
/// @enduml
///  Filter Function
/// @startuml
/// start
/// !include SignalFilter5_FilterFunction.puml
/// end
/// @enduml

void rbl_SigChainSigFil(const rbl_ImuStdTypes_ImuSignalSet_t *signalSetRaw, rbl_ImuStdTypes_ImuSignalSet_t *signalSetFil, rbl_ImuStdTypes_ImuSignalSet_t *signalSetDer, uint32 filterNumber);

#endif /* End of multiple include protection */
