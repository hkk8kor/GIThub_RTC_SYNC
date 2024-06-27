/// @file rbl_CustIf_TiSync.h
/// @brief This header provides definitions to get Global Timestampe
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_CUSTIF_TISYNC_H_
#define RBL_CUSTIF_TISYNC_H_


#include "Std_Types.h"
#include "RBSYS_SystemTimer.h"
#include "StbM.h"
#include "Rte_StbM.h"

/* Constants for Conversion between time systems */

/// MMP2 System Ticks
#define RBL_CUSTIF_TISYNC_MS2SYSTICKS  (80000u)

/// MMP2 Max system Ticks
#define RBL_CUSTIF_TISYNC_MAXSYSTICKS  (500 * (sint32)RBL_CUSTIF_TISYNC_MS2SYSTICKS)

/// Synchronized Ticks
#define RBL_CUSTIF_TISYNC_2SYSTICKS2NS (25u)

/// Synchronization Time for NanoSeconds
#define RBL_CUSTIF_TISYNC_S2NS         (1000000000u)

/// Pure Local Wait Time
#define RBL_CUSTIF_PLOCWAITTIME        (3500u) //Wait timeis 70s

/// Event for Resyncronization
#define RBL_CUSTIF_TISYNC_EV_RESYNCHRONIZATION (0x0200)

/// Event for Rate Correction
#define RBL_CUSTIF_TISYNC_EV_RATECORRECTION (0x0400)

/// Bit defines whether there is a sync to Pure Local Time
#ifndef RBL_CUSTIF_SYNC2PURELOCAL_TIMEBASE_BflPn
#define RBL_CUSTIF_SYNC2PURELOCAL_TIMEBASE_BflPn (6U)
#endif /* !RBL_CUSTIF_SYNC2PURELOCAL_TIMEBASE_BflPn */


/// Cloning Delay Ticks
#define RBL_CUSTIF_CLONING_DELAY_TICKS    (1593u)

/// Cloning Delay
#define RBL_CUSTIF_CLONING_DELAY_NS       ((RBL_CUSTIF_CLONING_DELAY_TICKS * ((sint32)RBL_CUSTIF_TISYNC_2SYSTICKS2NS + 1))/2)

/// Cloning of Time Domain 0 to Pure Local Time Domain delay
#define RBL_CUSTIF_CLONING_TB0_TO_TB32    (100u)

#if(RBFS_MMP2 == RBFS_MMP2_IMUB)
    #define RBL_CUSTIF_SYNC_OK              (0u)
    #define RBL_CUSTIF_NO_INITIAL_SYNC      (1u)
    #define RBL_CUSTIF_SYNC_LOST            (2u)
    #define RBL_CUSTIF_SNA                  (3u)
#endif

///Definition for Gts Monitoring State Machine
typedef enum
{
  GTS_LOCALFALLBACK_IDLE,        ///<Wait for Esp Clk_OK
  GTS_LOCALFALLBACK_CHECK,      ///<To check Leaps, Timeout and Esp Clk_OK
  GTS_LOCALFALLBACK_WAIT       ///<To wait PLOC time
}RBL_CUSTIF_GTS_LOCALFALLBACK_STATE;

typedef enum
{
  GTS_DEMEVENT_GETCURRENT = 0,    ///<Bit for DEM Event for Get Current
  GTS_DEMEVENT_SETCURRENT,        ///<Bit for DEM Event for Set Current
  GTS_DEMEVENT_GETRATE,           ///<Bit for DEM Event for Get Rate
  GTS_DEMEVENT_SETRATE            ///<Bit for DEM Event for Set Rate
}RBL_CUSTIF_GTS_EVENTSTATUS;

/// @c_file rbl_CustIf_TiSync.c
/// @brief This Function resposible for calculating time stamp values (in nano sec,sec)
/// Function recieves global time stamp values and compare with the current time stamp value
/// and calculate the time satmp values in nano sec and in sec respectively
/// @pre RBSYS_getRealtimeTickCtr and StbM_GetCurrentTimeshould should read GTS and current timestamp values.
/// @param[in] timeMMP_u32: the parameter contains the time stamp value from application
/// @param[in] timeGTS_st : the stucture contains the global time stamp values
/// @return Std_ReturnType :The function returns Not_ok or OK
/// @retval E_NOT_OK : The Function returns E_NOT_OK if the reading of global time stamp was not successfull
/// @retval E_OK : The Function returns E_OK if the reading of global time stamp was successfull
/// @startuml
/// !include rbl_CustIf_TiSync_MMP2GtsTime.puml
/// @enduml
/// @note The design for the rbl_TiSync_getPureLocalTime function
/// @startuml
/// !include rbl_TiSync_getPureLocalTime.puml
/// @enduml
/// @note The design for rbl_TiSync_StbMAddNanoSeconds function
/// @startuml
/// !include rbl_TiSync_StbMAddNanoSeconds.puml
/// @enduml
extern Std_ReturnType rbl_CustIf_TiSync_MMP2GtsTime(uint32 timeMMP_u32,StbM_TimeStampType * timeGTS_st);


/// @c_file rbl_CustIf_TiSync.c
/// @brief This Function resposible for Getting the local fallback check with the state machine to check
/// @pre ESP_Clk_Stat_Bckp_ST3 should be defined and Received before.
/// @param[in] void
/// @return void
/// @startuml
/// !include rbl_CustIf_GTS_LocalFallBackCheck.puml
/// @enduml
void rbl_CustIf_GTS_LocalFallBackCheck(void);

/* This function provides copying of data from Time Domain 0 to Time Domain 32, it is invoked every 500ms each time GTS
 * RecordBlock call back is invoked
 */

/// @c_file rbl_CustIf_TiSync.c
/// @brief This Function resposible for Cloning the time base data to pure local data for Time Domain 0
/// @param[in] void
/// @return void
/// @startuml
/// !include rbl_TiSync_cloneToPureLocalTime.puml
/// @enduml
void rbl_TiSync_cloneToPureLocalTime(void);


#if(RBFS_MMP2 == RBFS_MMP2_IMUB)

    /// @c_file rbl_CustIf_TiSync_AMG.c
    /// @brief This Function resposible for calculating time stamp values (in nano sec,sec)
    /// Function recieves global time stamp values and compare with the current time stamp value
    /// and calculate the time stamp values in nano sec and in sec respectively for Time Domain 2
    /// @pre RBSYS_getRealtimeTickCtr and StbM_GetCurrentTimeshould should read GTS and current timestamp values.
    /// @param[in] timeMMP_u32: the parameter contains the time stamp value from application
    /// @param[in] timeGTS_st : the stucture contains the global time stamp values
    /// @return Std_ReturnType :The function returns Not_ok or OK
    /// @retval E_NOT_OK : The Function returns E_NOT_OK if the reading of global time stamp was not successfull
    /// @retval E_OK : The Function returns E_OK if the reading of global time stamp was successfull
    /// @startuml
    /// !include rbl_CustIf_TiSync_MMP2GtsTime.puml
    /// @enduml
    /// @note The design for the rbl_TiSync_getPureLocalTime function
    /// @startuml
    /// !include rbl_TiSync_getPureLocalTime.puml
    /// @enduml
    /// @note The design for rbl_TiSync_StbMAddNanoSeconds function
    /// @startuml
    /// !include rbl_TiSync_StbMAddNanoSeconds.puml
    /// @enduml
    extern Std_ReturnType rbl_CustIf_TiSync_MMP2GtsTime_AMG(uint32 timeMMP_u32,StbM_TimeStampType * timeGTS_st);

    /// @c_file rbl_CustIf_TiSync_AMG.c
    /// @brief This Function resposible for Getting the local fallback check with the state machine to check
    ///        for Time Domain 2
    /// @param[in] void
    /// @return void
    /// @startuml
    /// !include rbl_CustIf_GTS_LocalFallBackCheck.puml
    /// @enduml
    void rbl_CustIf_GTS_LocalFallBackCheck_AMG(void);

    /// @c_file rbl_CustIf_TiSync_AMG.c
    /// @brief This Function resposible for Cloning the time base data to pure local data for Time Domain 2
    /// @param[in] void
    /// @return void
    /// @startuml
    /// !include rbl_TiSync_cloneToPureLocalTime_AMG.puml
    /// @enduml
    void rbl_TiSync_cloneToPureLocalTime_AMG(void);
#endif


#endif /* RBL_CUSTIF_TISYNC_H_ */
