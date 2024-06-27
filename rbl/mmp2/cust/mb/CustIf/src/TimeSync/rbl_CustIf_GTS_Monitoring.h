/// @file rbl_CustIf_GTS_Monitoring.h
/// @brief This header provides definitions to get Monitoring done for Global Time Synchronization.
/// @copyright (C) 2023 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.
/// @note The Sequence Diagram for Monitoring for Global Time Synchronization is as below
/// @startuml
/// !include gts_Monitoring_Sequence_Diagram.puml
/// @enduml

#ifndef RBL_CUSTIF_GTS_MONITORING_H_
#define RBL_CUSTIF_GTS_MONITORING_H_

#include "Std_Types.h"
#include "StbM.h"
#include "StbM_Priv.h"
#include "rbl_CustIf_TiSync.h"
#include "Dem.h"

///Bit defines whether Time Base was atleast one time synchronized with Global Time Base
#ifndef RBL_CUSTIF_GLOBAL_TIMEBASE_BflPn
#define RBL_CUSTIF_GLOBAL_TIMEBASE_BflPn (3U)
#endif /* !RBL_CUSTIF_GLOBAL_TIMEBASE_BflPn */

///Bit defines whether there is a Timeout on receiving Synchronization Messages
#ifndef RBL_CUSTIF_TIMEOUT_BflPn
#define RBL_CUSTIF_TIMEOUT_BflPn (0U)
#endif /* !RBL_CUSTIF_TIMEOUT_BflPn */

///Bit defines whether there is a Leap into the future within the received time for Time Base exceeds a configured threshold
#ifndef RBL_CUSTIF_TIMELEAP_FUTURE_BflPn
#define RBL_CUSTIF_TIMELEAP_FUTURE_BflPn (4U)
#endif /* !RBL_CUSTIF_TIMELEAP_FUTURE_BflPn */

///Bit defines whether there is a Leap into the past within the received time for Time Base exceeds a configured threshold
#ifndef RBL_CUSTIF_TIMELEAP_PAST_BflPn
#define RBL_CUSTIF_TIMELEAP_PAST_BflPn (5U)
#endif /* !RBL_CUSTIF_TIMELEAP_PAST_BflPn */


///Definition for Gts Monitoring State Machine
typedef enum STBM_MONITOR_STATE
{
  SMS_GET_INIT_BASE_TIME,   ///<Initialize the Base Time
  SMS_CHECK_INIT_SYNC,      ///<To Check for INIT Synchroniztion
  SMS_WAIT_INIT_SYNC,       ///<To check  for Init Synchronization after a delay
  SMS_CHECK_LOST_SYNC,      ///<To Check for LOST Synchroniztion
  SMS_CHECK_TIME_LEAP,     ///<To Check for TIMELEAP
}STBM_MONITOR_STATE;

/// @c_file rbl_CustIf_GTS_Monitoring.c
/// @brief The function is used to Monitor the INIT_Timeout, LOST_Timeout and TimeLeap in
/// Global Time Synchronization and log the respective DEM event.
/// @pre Corresponding Dem event have to be configured.
/// @return void
/// @startuml
/// !include rbl_CustIf_GTS_Monitoring.puml
/// @enduml
/// @details Calls function @ref StbM_GetCurrentTime to get the Current Time synchronized, @ref StbM_GetTimeBaseStatus
/// to get the Time Sync Status and @ref Bfx_GetBit_u8u8_u8 is used get the values for bit's RBL_CUSTIF_GLOBAL_TIMEBASE_BflPn,
/// RBL_CUSTIF_TIMEOUT_BflPn, RBL_CUSTIF_TIMELEAP_FUTURE_BflPn and RBL_CUSTIF_TIMELEAP_PAST_BflPn
void rbl_CustIf_GTS_Monitoring(void);


/// @c_file rbl_CustIf_GTS_Monitoring.c
/// @brief The function is used to Monitor the INIT_Timeout.
/// @pre Corresponding Dem event have to be configured.
/// @param[in] void
/// @return boolean
/// @startuml
/// !include rbl_CustIf_StbM_Check_Init_Sync.puml
/// @enduml
boolean rbl_CustIf_StbM_Check_Init_Sync(void);


/// @c_file rbl_CustIf_GTS_Monitoring.c
/// @brief The function is used to Monitor the LOST_Timeout.
/// @pre Corresponding Dem event have to be configured.
/// @param[in] void
/// @return boolean
/// @startuml
/// !include rbl_CustIf_StbM_Check_Lost_Sync.puml
/// @enduml
boolean rbl_CustIf_StbM_Check_Lost_Sync(void);


/// @c_file rbl_CustIf_GTS_Monitoring.c
/// @brief The function is used to Monitor the TimeLeap in Global Time Synchronization in the Future as well as the Past.
/// @pre Corresponding Dem event have to be configured.
/// @param[in] void
/// @return boolean
/// @startuml
/// !include rbl_CustIf_StbM_Check_TimeLeap.puml
/// @enduml
boolean rbl_CustIf_StbM_Check_TimeLeap(void);

/// @c_file rbl_CustIf_GTS_Monitoring.c
/// @brief The function is used to Log the Time and Rate DEM events
/// @pre Initialize variables to DEM Pass status
/// @param[in] Dem_EventStatusType EventStatus Provides the Fail/Pass status of Get/Set Current function
/// @return void
/// @startuml
/// !include rbl_CustIf_StbM_Monitor_Time_Rate.puml
/// @enduml
void rbl_CustIf_StbM_Monitor_Time_Rate_Copy(uint8 eventStatus);


#if(RBFS_MMP2 == RBFS_MMP2_IMUB)

/// @c_file rbl_CustIf_GTS_Monitoring_AMG.c
/// @brief The function is used to Monitor the INIT_Timeout, LOST_Timeout and TimeLeap in
/// Global Time Synchronization and log the respective DEM event  for Time  Domain 2
/// @pre Corresponding Dem event have to be configured.
/// @return void
/// @startuml
/// !include rbl_CustIf_GTS_Monitoring.puml
/// @enduml
/// @details Calls function @ref StbM_GetCurrentTime to get the Current Time synchronized, @ref StbM_GetTimeBaseStatus
/// to get the Time Sync Status and @ref Bfx_GetBit_u8u8_u8 is used get the values for bit's RBL_CUSTIF_GLOBAL_TIMEBASE_BflPn,
/// RBL_CUSTIF_TIMEOUT_BflPn, RBL_CUSTIF_TIMELEAP_FUTURE_BflPn and RBL_CUSTIF_TIMELEAP_PAST_BflPn
void rbl_CustIf_GTS_Monitoring_AMG(void);

/// @c_file rbl_CustIf_GTS_Monitoring_AMG.c
/// @brief The function is used to Monitor the INIT_Timeout for Time  Domain 2
/// @pre Corresponding Dem event have to be configured.
/// @param[in] void
/// @return boolean
/// @startuml
/// !include rbl_CustIf_StbM_Check_Init_Sync.puml
/// @enduml
boolean rbl_CustIf_StbM_Check_Init_Sync_AMG(void);

/// @c_file rbl_CustIf_GTS_Monitoring_AMG.c
/// @brief The function is used to Monitor the LOST_Timeout.
/// @pre Corresponding Dem event have to be configured.
/// @param[in] void
/// @return boolean
/// @startuml
/// !include rbl_CustIf_StbM_Check_Lost_Sync.puml
/// @enduml
boolean rbl_CustIf_StbM_Check_Lost_Sync_AMG(void);

/// @c_file rbl_CustIf_GTS_Monitoring_AMG.c
/// @brief The function is used to Monitor the TimeLeap in Global Time Synchronization in the Future as well as the Past.
/// @pre Corresponding Dem event have to be configured.
/// @param[in] void
/// @return boolean
/// @startuml
/// !include rbl_CustIf_StbM_Check_TimeLeap.puml
/// @enduml
boolean rbl_CustIf_StbM_Check_TimeLeap_AMG(void);

/// @c_file rbl_CustIf_GTS_Monitoring_AMG.c
/// @brief The function is used to Log the Time and Rate DEM events
/// @pre Corresponding Dem event have to be configured and corresponding status of events need to be set
/// @param[in] Dem_EventStatusType EventStatus Provides the Fail/Pass status of Get/Set Current function
/// @return void
/// @startuml
/// !include rbl_CustIf_StbM_Monitor_Time_Rate.puml
/// @enduml
void rbl_CustIf_StbM_Monitor_Time_Rate_Copy_AMG(uint8 eventStatus);

#endif /* RBFS_MMP2_IMUB */

#endif /* RBL_CUSTIF_GTS_MONITORING_H_ */
