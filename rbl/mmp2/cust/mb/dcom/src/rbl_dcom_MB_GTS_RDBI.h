/// @file rbl_dcom_MB_GTS_RDBI.h
/// @brief This header provides definitions for the Macros and Structure definition api,
/// functions used by Global Time Synchronization DID.
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

#ifndef RBL_DCOM_MB_GTS_RDBI_H
#define RBL_DCOM_MB_GTS_RDBI_H

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
//#include "StbM.h"
#include "rbl_CustIf_Meas_IMU_X_ST3.h"
#include "rbl_CustIf_TiSync.h"
/*
**********************************************************************************************************************
* Macros
**********************************************************************************************************************
*/
/* Size Defintions */
#define DCOM_MB_GTS_MEASUREMENT_SETS_TYPE2                            11 //GTS Measurement Sets Type2
#define DCOM_MB_GTS_MEASUREMENT_HEAD_AND_DATA_TYPE1_SECTION_SIZE      47 //GTS Measurement Head and Data Type1 Section
#define DCOM_MB_GTS_MEASUREMENT_MEASUREMENT_TYPE2_SIZE                14 //GTS Measurement Type2 Section
#define DCOM_MB_GTS_MEASUREMENT_INDEX_BYTE                            23 //GTS Measurement Index byte

/* Definitions for GTS Measurement Header*/
#define DCOM_MB_GTS_MEASUREMENT_DATA_STRUCTURE_TYPE                   0x02U //GTS Measurement Data Structure Type
#define DCOM_MB_GTS_MEASUREMENT_ETHTSYN_MAJOR                         0xACU//GTS Measurement ETHTSYN Major
#define DCOM_MB_GTS_MEASUREMENT_ETHTSYN_MINOR                         0xACU//GTS Measurement ETHTSYN Minor
#define DCOM_MB_GTS_MEASUREMENT_ETHTSYN_PATCH                         0xACU//GTS Measurement ETHTSYN  Patch
#define DCOM_MB_GTS_MEASUREMENT_FRTSYN_MAJOR                          0xACU//GTS Measurement FRTSYN Major
#define DCOM_MB_GTS_MEASUREMENT_FRTSYN_MINOR                          0xACU//GTS Measurement FRTSYN Minor
#define DCOM_MB_GTS_MEASUREMENT_FRTSYN_PATCH                          0xACU//GTS Measurement FRTSYN Patch
#define DCOM_MB_GTS_ADAS_TIME_DOMAIN                                  0XFFU//Timebase of Vehicle is equal to Time Domain
#define DCOM_MB_GTS_MEASUREMENT_DEFAULT_INDEX                         0xACU//GTS Measurement set to Default Index
#define DCOM_GTSHEADER_FREQUENCY_INIT                                 0x4C4B400U//GTS Measurement for Frequency
#define DCOM_GTSHEADER_PRESCALER_INIT                                 0x01U//GTS Measurement for Prescaler


/* Definitions for GTS Measurement Data Tyoe 1*/
#define DCOM_GTSTYPE1_GLBSECONDS_INIT                      			  0xACACACACU//INIT Value for Global Seconds
#define DCOM_GTSTYPE1_GLBNANOSECONDS_INIT                  			  0xACACACACU//INIT Value for Time in Global NanoSeconds
#define DCOM_GTSTYPE1_TIMEBASESTATUS_INIT                  			  0xACU//INIT Value for Time Base Status
#define DCOM_GTSTYPE1_VIRTUALLOCALTIMELOW_INIT                 		  0xACACACACU//INIT Value for Virtual Local Time Low
#define DCOM_GTSTYPE1_RATEDEVIATION_INIT                        	  0xACACU//INIT Value for Rate Deviation
#define DCOM_GTSTYPE1_LOCSECONDS_INIT                           	  0xACACACACU//INIT Value for Time of Local Seconds
#define DCOM_GTSTYPE1_LOCNANOSECONDS_INIT                      		  0xACACACACU//INIT Value for Time of Local Nano Seconds

/* Definitions for GTS Measurement Data Tyoe 2*/
#define DCOM_GTSTYPE2_GLSECONDSLO_INIT                                0xACU//INIT Value for Time of Global Seconds Low
#define DCOM_GTSTYPE2_GNANOSECONDSPART_INIT                           0xACU//INIT Value for Global Nano Seconds Part
#define DCOM_GTSTYPE2_TIMEBASESTATUS_INIT                             0xACU//INIT Value for Time Base Status
#define DCOM_GTSTYPE2_VIRTUALLOCALTIMELOW_INIT                        0xACACACACU//INIT Value for Virtual Local Time Low
#define DCOM_GTSTYPE2_RATEDEVIATION_INIT                              0xACACU//INIT Value for Rate Deviation
#define DCOM_GTSTYPE2_LNANOSECONDSPART_INIT                           0xACU//INIT Value for Time of Local Nano Seconds

/* Shift Definitions */
#define DCOM_ONE_BYTE_SHIFT                                           8U//Shifting one Byte
#define DCOM_TWO_BYTES_SHIFT                                          16U//Shifting Two Bytes
#define DCOM_THREE_BYTES_SHIFT                                        24U//Shifting Three Bytes

/*Mesurment PDU Activation*/
#define DCOM_MB_TRANSMISSION_ACTIVE     (1U)

/*
**********************************************************************************************************************
* Structures
**********************************************************************************************************************
*/

/* GTS Measurement Header Structure */
typedef struct
{
   uint8   MeasurementDataStructureType; ///<Measurement Data Structure Type
   uint32  HWFrequency; ///<Hardware Frequency
   uint32  HWPrescaler; ///<Hardware Prescalar
   uint8   Index; ///<Index Value
} dcom_MB_GTS_Header_Section_Type_tst;

/* GTS Measurement Data Structure-1 */
typedef struct
{
   uint32  GlbSeconds; ///<Time Value in Global Seconds
   uint32  GlbNanoSeconds; ///<Time Value in Global NanoSeconds
   uint8   TimeBaseStatus; ///<Time Base Status
   uint32  VirtualLocalTimeLow; ///<Virtual Local Time Low
   uint16  RateDeviation; ///<Rate Deviation
   uint32  LocSeconds; ///<Time Value for Local Seconds
   uint32  LocNanoSeconds; ///<Time Value for Local Nano Seconds
} dcom_MB_GTS_TimeBaseRecord_Type1_tst;

/* GTS Measurement Data Structure-2 */
typedef struct
{
   uint8   GLSecondsLo; ///<Time Value of Global Seconds Low
   uint8   GNanoSecondsPart[3]; ///<Global Nano Seconds Part
   uint8   TimeBaseStatus; ///<Time Base Status
   uint32  VirtualLocalTimeLow; ///<Virtual Local Time Low
   uint16  RateDeviation; ///<Rate Deviation
   uint8   LNanoSecondsPart[3]; ///<Time Value for Local Nano Seconds
} dcom_MB_GTS_TimeBaseRecord_Type2_tst;

/* GTS Complete Measurement Structure */
typedef struct
{
    dcom_MB_GTS_Header_Section_Type_tst Header; ///<Header Data Structure
    dcom_MB_GTS_TimeBaseRecord_Type1_tst TimeRecord1; ///<GTS Measurement Fill Time Record Type1
    dcom_MB_GTS_TimeBaseRecord_Type2_tst TimeRecord2[DCOM_MB_GTS_MEASUREMENT_SETS_TYPE2]; ///<GTS Measurement Fill Time
                                                                                         ///Record Type2
} dcom_MB_GTS_Measurement_Data_Type_tst;

/**
**********************************************************************************************************************
* Variables
**********************************************************************************************************************
*/

/*
**********************************************************************************************************************
* Function Declarations
**********************************************************************************************************************
*/

/// @c_file rbl_dcom_MB_GTS_RDBI.c
/// @brief This API is to read Global time synch data and fill the response buffer to DCM.
/// @pre Data of Global Time Synchronization macros must be defined.
/// @param[in,out] Data: Buffer where data of Global Time Synchronization is stored.
/// @return Std_ReturnType: The status of read operation is returned and the data is filled in Data buffer
/// @retval E_OK if Request successful
/// @retval E_NOT_OK if Request was not successful
/// @startuml
/// !include rbl_dcom_GTS_RDBI_dcom_Global_Time_Sync_Measured_Values_0107_ReadData.puml
/// @enduml
extern Std_ReturnType dcom_Global_Time_Sync_Measured_Values_0107_ReadData (uint8 * Data);


/// @c_file rbl_dcom_MB_GTS_RDBI.c
/// @brief This API is to fill Timerecordheader and timerecordblock data.
/// @pre Data of Global Time Synchronization macros must be defined.
/// @param[in,out] syncRecordTableBlock: Provides the structure of Record table Block Data.
/// @return Std_ReturnType: The status of operation is returned and the data is filled in Data buffer
/// @retval E_OK if Request successful
/// @retval E_NOT_OK if Request was not successful
/// @startuml
/// !include rbl_dcom_GTS_RDBI_dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase.puml
/// @enduml
extern Std_ReturnType dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase(const StbM_SyncRecordTableBlockType *syncRecordTableBlock);


#endif /* RBL_DCOM_MB_GTS_RDBI_H */
