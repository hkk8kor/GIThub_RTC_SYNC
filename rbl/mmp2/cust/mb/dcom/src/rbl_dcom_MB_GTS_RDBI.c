/// @file rbl_dcom_MB_GTS_RDBI.c
/// @brief The file consists of the API's for Read Data by Identifier DID identified for
/// Global Time Synchronization for MB
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/
#include "rbl_dcom_Lib.h"
#include "rbl_dcom_MB_Pub.h"
#include "rbl_dcom_MB_GTS_RDBI.h"
#include "CanTSyn.h"
#include "StbM.h"
#include "Rte_StbM.h"


/*
**********************************************************************************************************************
* Variables
**********************************************************************************************************************
*/
/* Daimler GTS Complete Measurement Structure declaration and initialization */
static dcom_MB_GTS_Measurement_Data_Type_tst dcom_MB_GTS_Measurement_st = {{DCOM_MB_GTS_MEASUREMENT_DATA_STRUCTURE_TYPE,DCOM_GTSHEADER_FREQUENCY_INIT,DCOM_GTSHEADER_PRESCALER_INIT,DCOM_MB_GTS_MEASUREMENT_DEFAULT_INDEX},
        {DCOM_GTSTYPE1_GLBSECONDS_INIT,DCOM_GTSTYPE1_GLBNANOSECONDS_INIT,DCOM_GTSTYPE1_TIMEBASESTATUS_INIT,DCOM_GTSTYPE1_VIRTUALLOCALTIMELOW_INIT,DCOM_GTSTYPE1_RATEDEVIATION_INIT,DCOM_GTSTYPE1_LOCSECONDS_INIT,DCOM_GTSTYPE1_LOCNANOSECONDS_INIT},
        {{DCOM_GTSTYPE2_GLSECONDSLO_INIT,{DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT},DCOM_GTSTYPE2_TIMEBASESTATUS_INIT,DCOM_GTSTYPE2_VIRTUALLOCALTIMELOW_INIT,DCOM_GTSTYPE2_RATEDEVIATION_INIT,{DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT}},
        {DCOM_GTSTYPE2_GLSECONDSLO_INIT,{DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT},DCOM_GTSTYPE2_TIMEBASESTATUS_INIT,DCOM_GTSTYPE2_VIRTUALLOCALTIMELOW_INIT,DCOM_GTSTYPE2_RATEDEVIATION_INIT,{DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT}},
        {DCOM_GTSTYPE2_GLSECONDSLO_INIT,{DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT},DCOM_GTSTYPE2_TIMEBASESTATUS_INIT,DCOM_GTSTYPE2_VIRTUALLOCALTIMELOW_INIT,DCOM_GTSTYPE2_RATEDEVIATION_INIT,{DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT}},
        {DCOM_GTSTYPE2_GLSECONDSLO_INIT,{DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT},DCOM_GTSTYPE2_TIMEBASESTATUS_INIT,DCOM_GTSTYPE2_VIRTUALLOCALTIMELOW_INIT,DCOM_GTSTYPE2_RATEDEVIATION_INIT,{DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT}},
        {DCOM_GTSTYPE2_GLSECONDSLO_INIT,{DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT},DCOM_GTSTYPE2_TIMEBASESTATUS_INIT,DCOM_GTSTYPE2_VIRTUALLOCALTIMELOW_INIT,DCOM_GTSTYPE2_RATEDEVIATION_INIT,{DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT}},
        {DCOM_GTSTYPE2_GLSECONDSLO_INIT,{DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT},DCOM_GTSTYPE2_TIMEBASESTATUS_INIT,DCOM_GTSTYPE2_VIRTUALLOCALTIMELOW_INIT,DCOM_GTSTYPE2_RATEDEVIATION_INIT,{DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT}},
        {DCOM_GTSTYPE2_GLSECONDSLO_INIT,{DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT},DCOM_GTSTYPE2_TIMEBASESTATUS_INIT,DCOM_GTSTYPE2_VIRTUALLOCALTIMELOW_INIT,DCOM_GTSTYPE2_RATEDEVIATION_INIT,{DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT}},
        {DCOM_GTSTYPE2_GLSECONDSLO_INIT,{DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT},DCOM_GTSTYPE2_TIMEBASESTATUS_INIT,DCOM_GTSTYPE2_VIRTUALLOCALTIMELOW_INIT,DCOM_GTSTYPE2_RATEDEVIATION_INIT,{DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT}},
        {DCOM_GTSTYPE2_GLSECONDSLO_INIT,{DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT},DCOM_GTSTYPE2_TIMEBASESTATUS_INIT,DCOM_GTSTYPE2_VIRTUALLOCALTIMELOW_INIT,DCOM_GTSTYPE2_RATEDEVIATION_INIT,{DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT}},
        {DCOM_GTSTYPE2_GLSECONDSLO_INIT,{DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT},DCOM_GTSTYPE2_TIMEBASESTATUS_INIT,DCOM_GTSTYPE2_VIRTUALLOCALTIMELOW_INIT,DCOM_GTSTYPE2_RATEDEVIATION_INIT,{DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT}},
        {DCOM_GTSTYPE2_GLSECONDSLO_INIT,{DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT,DCOM_GTSTYPE2_GNANOSECONDSPART_INIT},DCOM_GTSTYPE2_TIMEBASESTATUS_INIT,DCOM_GTSTYPE2_VIRTUALLOCALTIMELOW_INIT,DCOM_GTSTYPE2_RATEDEVIATION_INIT,{DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT,DCOM_GTSTYPE2_LNANOSECONDSPART_INIT}}}};

/* Daimler GTS Complete Measurement Structure declaration and initialization */
static uint8 dcom_MB_MeasurementDataIndex = 0;

/* Flag to check if the GTS Measurement Index was received or not */
static boolean dcom_MB_GTS_Measurement_Received = FALSE;

/* ***** PUBLIC/PROTECTED/PRIVATE API functions ***** */
/* ****************************************************************************
 *  ***** API private: dcom_MB_GTS_Measurement_Fill_TimeRecordHeader  ***** */

static Std_ReturnType dcom_MB_GTS_Measurement_Fill_TimeRecordHeader(void)
{
    /* Local Data Declaration */
    Std_ReturnType retVal = E_OK;
    StbM_SyncRecordTableHeadType syncRecordTableHead = {0};

    /*  -------------------------------------- Server Call Point  --------------------------------  */
    retVal = StbM_GetSyncTimeRecordHead(0, &syncRecordTableHead);

    if (E_NOT_OK != retVal)
    {
        /* Set the Flag to indicate that GTS Measurement is Available */
        if (dcom_MB_GTS_Measurement_Received != TRUE)
        {
            dcom_MB_GTS_Measurement_Received = TRUE;
        }

        /* Get Header information for Measurement Structure*/
        dcom_MB_GTS_Measurement_st.Header.HWFrequency                  = syncRecordTableHead.HWfrequency;
        dcom_MB_GTS_Measurement_st.Header.HWPrescaler                  = syncRecordTableHead.HWprescaler;
        dcom_MB_GTS_Measurement_st.Header.Index                        = dcom_MB_MeasurementDataIndex;
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}
/* ***** END_API dcom_MB_GTS_Measurement_Fill_TimeRecordHeader ***** */


/* ****************************************************************************
 *  ***** API private: dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1  ***** */

static Std_ReturnType dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1(const StbM_SyncRecordTableBlockType *syncRecordTableBlock)
{
    /* Local Data Declaration */
    Std_ReturnType retVal = E_OK;

    if (NULL_PTR != syncRecordTableBlock)
    {
        dcom_MB_GTS_Measurement_st.TimeRecord1.GlbSeconds          = syncRecordTableBlock->GlbSeconds;
        dcom_MB_GTS_Measurement_st.TimeRecord1.GlbNanoSeconds      = syncRecordTableBlock->GlbNanoSeconds;
        dcom_MB_GTS_Measurement_st.TimeRecord1.TimeBaseStatus      = syncRecordTableBlock->TimeBaseStatus;
        dcom_MB_GTS_Measurement_st.TimeRecord1.VirtualLocalTimeLow = syncRecordTableBlock->VirtualLocalTimeLow;
        dcom_MB_GTS_Measurement_st.TimeRecord1.RateDeviation       = (uint16)(syncRecordTableBlock->RateDeviation);
        dcom_MB_GTS_Measurement_st.TimeRecord1.LocSeconds          = syncRecordTableBlock->LocSeconds;
        dcom_MB_GTS_Measurement_st.TimeRecord1.LocNanoSeconds      = syncRecordTableBlock->LocNanoSeconds;
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}

/* ***** END_API dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1 ***** */

/* ****************************************************************************
 *  ***** API private: dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2  ***** */

static Std_ReturnType dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2(const StbM_SyncRecordTableBlockType *syncRecordTableBlock)
{
    /* Local Data Declaration */
    Std_ReturnType retVal = E_OK;
    uint8 i;

    if (NULL_PTR != syncRecordTableBlock)
    {
        i = dcom_MB_MeasurementDataIndex - 1 ;
        dcom_MB_GTS_Measurement_st.TimeRecord2[i].GLSecondsLo         = (uint8)((syncRecordTableBlock->GlbSeconds & 0x0FU) |
                                                                                                     ((syncRecordTableBlock->LocSeconds & 0x0FU) << 4));
        dcom_MB_GTS_Measurement_st.TimeRecord2[i].GNanoSecondsPart[0] = (uint8)(syncRecordTableBlock->GlbNanoSeconds >> 6);
        dcom_MB_GTS_Measurement_st.TimeRecord2[i].GNanoSecondsPart[1] = (uint8)(syncRecordTableBlock->GlbNanoSeconds >> 14);
        dcom_MB_GTS_Measurement_st.TimeRecord2[i].GNanoSecondsPart[2] = (uint8)(syncRecordTableBlock->GlbNanoSeconds >> 22);
        dcom_MB_GTS_Measurement_st.TimeRecord2[i].TimeBaseStatus      = syncRecordTableBlock->TimeBaseStatus;
        dcom_MB_GTS_Measurement_st.TimeRecord2[i].VirtualLocalTimeLow = syncRecordTableBlock->VirtualLocalTimeLow;
        dcom_MB_GTS_Measurement_st.TimeRecord2[i].RateDeviation       = (uint16)(syncRecordTableBlock->RateDeviation);
        dcom_MB_GTS_Measurement_st.TimeRecord2[i].LNanoSecondsPart[0] = (uint8)(syncRecordTableBlock->LocNanoSeconds >> 6);
        dcom_MB_GTS_Measurement_st.TimeRecord2[i].LNanoSecondsPart[1] = (uint8)(syncRecordTableBlock->LocNanoSeconds >> 14);
        dcom_MB_GTS_Measurement_st.TimeRecord2[i].LNanoSecondsPart[2] = (uint8)(syncRecordTableBlock->LocNanoSeconds >> 22);
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;
}
/* ***** END_API dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2 ***** */

/* ****************************************************************************
 *  ***** API public: dcom_Global_Time_Sync_Measured_Values_0107_ReadData  ***** */

Std_ReturnType dcom_Global_Time_Sync_Measured_Values_0107_ReadData (uint8 * Data)
{
/* Local Data Declaration */
    Std_ReturnType retVal   = E_OK;
    uint8 i = 0;
    uint8 k = DCOM_MB_GTS_MEASUREMENT_HEAD_AND_DATA_TYPE1_SECTION_SIZE;

    if (NULL_PTR != Data)
    {
        /* Convert the Daimler Header Structure to fit Data array*/
        Data[0]  =   DCOM_MB_GTS_ADAS_TIME_DOMAIN;
        Data[1]  =   dcom_MB_GTS_Measurement_st.Header.MeasurementDataStructureType;
        Data[2]  =   (uint8)(dcom_MB_GTS_Measurement_st.Header.HWFrequency >> DCOM_THREE_BYTES_SHIFT);
        Data[3]  =   (uint8)(dcom_MB_GTS_Measurement_st.Header.HWFrequency >> DCOM_TWO_BYTES_SHIFT);
        Data[4]  =   (uint8)(dcom_MB_GTS_Measurement_st.Header.HWFrequency >> DCOM_ONE_BYTE_SHIFT);
        Data[5]  =   (uint8)(dcom_MB_GTS_Measurement_st.Header.HWFrequency);
        Data[6]  =   (uint8)(dcom_MB_GTS_Measurement_st.Header.HWPrescaler >> DCOM_ONE_BYTE_SHIFT);
        Data[7]  =   (uint8)(dcom_MB_GTS_Measurement_st.Header.HWPrescaler);
        Data[8]  =   DCOM_ECU_EXTRACT_MAJOR_VERSION;
        Data[9]  =   DCOM_ECU_EXTRACT_MINOR_VERSION;
        Data[10] =   DCOM_ECU_EXTRACT_PATCH_VERSION;
        Data[11] =   STBM_SOFTWARE_MAJOR_VERSION;
        Data[12] =   STBM_SOFTWARE_MINOR_VERSION;
        Data[13] =   STBM_SOFTWARE_PATCH_VERSION;
        Data[14] =   DCOM_MB_GTS_MEASUREMENT_ETHTSYN_MAJOR;
        Data[15] =   DCOM_MB_GTS_MEASUREMENT_ETHTSYN_MINOR;
        Data[16] =   DCOM_MB_GTS_MEASUREMENT_ETHTSYN_PATCH;
        Data[17] =   CANTSYN_SW_MAJOR_VERSION;
        Data[18] =   CANTSYN_SW_MINOR_VERSION;
        Data[19] =   CANTSYN_SW_PATCH_VERSION;
        Data[20] =   DCOM_MB_GTS_MEASUREMENT_FRTSYN_MAJOR;
        Data[21] =   DCOM_MB_GTS_MEASUREMENT_FRTSYN_MINOR;
        Data[22] =   DCOM_MB_GTS_MEASUREMENT_FRTSYN_PATCH;

        /* Check if the GTS Measurement was never received before */
        if (dcom_MB_GTS_Measurement_Received == FALSE)
        {
            /* if GTS measurements were not received then set to default value */
            Data[DCOM_MB_GTS_MEASUREMENT_INDEX_BYTE]           = DCOM_MB_GTS_MEASUREMENT_DEFAULT_INDEX;
        }
        else
        {
            /* if GTS measurements are received then set index to normal value coming from GTS update */
            Data[DCOM_MB_GTS_MEASUREMENT_INDEX_BYTE]           = dcom_MB_GTS_Measurement_st.Header.Index;
        }

        /* Convert 1 measurement to fit Data array*/
           Data[24]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.GlbSeconds >> DCOM_THREE_BYTES_SHIFT);
           Data[25]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.GlbSeconds >> DCOM_TWO_BYTES_SHIFT);
           Data[26]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.GlbSeconds >> DCOM_ONE_BYTE_SHIFT);
           Data[27]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.GlbSeconds);
           Data[28]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.GlbNanoSeconds >> DCOM_THREE_BYTES_SHIFT);
           Data[29]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.GlbNanoSeconds >> DCOM_TWO_BYTES_SHIFT);
           Data[30]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.GlbNanoSeconds >> DCOM_ONE_BYTE_SHIFT);
           Data[31]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.GlbNanoSeconds);
           Data[32]  = dcom_MB_GTS_Measurement_st.TimeRecord1.TimeBaseStatus;
           Data[33]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.VirtualLocalTimeLow >> DCOM_THREE_BYTES_SHIFT);
           Data[34]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.VirtualLocalTimeLow >> DCOM_TWO_BYTES_SHIFT);
           Data[35]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.VirtualLocalTimeLow >> DCOM_ONE_BYTE_SHIFT);
           Data[36]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.VirtualLocalTimeLow);
           Data[37]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.RateDeviation >> DCOM_ONE_BYTE_SHIFT);
           Data[38]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.RateDeviation);
           Data[39]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.LocSeconds >> DCOM_THREE_BYTES_SHIFT);
           Data[40]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.LocSeconds >> DCOM_TWO_BYTES_SHIFT);
           Data[41]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.LocSeconds >> DCOM_ONE_BYTE_SHIFT);
           Data[42]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.LocSeconds);
           Data[43]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.LocNanoSeconds >> DCOM_THREE_BYTES_SHIFT);
           Data[44]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.LocNanoSeconds >> DCOM_TWO_BYTES_SHIFT);
           Data[45]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.LocNanoSeconds >> DCOM_ONE_BYTE_SHIFT);
           Data[46]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord1.LocNanoSeconds);

        /* Convert 11 measurement to fit Data array*/
        for(i=0; i<DCOM_MB_GTS_MEASUREMENT_SETS_TYPE2; i++)
        {
           Data[k + 0]  = dcom_MB_GTS_Measurement_st.TimeRecord2[i].GLSecondsLo;
           Data[k + 1]  = dcom_MB_GTS_Measurement_st.TimeRecord2[i].GNanoSecondsPart[2];
           Data[k + 2]  = dcom_MB_GTS_Measurement_st.TimeRecord2[i].GNanoSecondsPart[1];
           Data[k + 3]  = dcom_MB_GTS_Measurement_st.TimeRecord2[i].GNanoSecondsPart[0];
           Data[k + 4]  = dcom_MB_GTS_Measurement_st.TimeRecord2[i].TimeBaseStatus;
           Data[k + 5]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord2[i].VirtualLocalTimeLow >> DCOM_THREE_BYTES_SHIFT);
           Data[k + 6]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord2[i].VirtualLocalTimeLow >> DCOM_TWO_BYTES_SHIFT);
           Data[k + 7]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord2[i].VirtualLocalTimeLow >> DCOM_ONE_BYTE_SHIFT);
           Data[k + 8]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord2[i].VirtualLocalTimeLow);
           Data[k + 9]  = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord2[i].RateDeviation >> DCOM_ONE_BYTE_SHIFT);
           Data[k + 10] = (uint8)(dcom_MB_GTS_Measurement_st.TimeRecord2[i].RateDeviation);
           Data[k + 11] = dcom_MB_GTS_Measurement_st.TimeRecord2[i].LNanoSecondsPart[2];
           Data[k + 12] = dcom_MB_GTS_Measurement_st.TimeRecord2[i].LNanoSecondsPart[1];
           Data[k + 13] = dcom_MB_GTS_Measurement_st.TimeRecord2[i].LNanoSecondsPart[0];
           k            =  k + DCOM_MB_GTS_MEASUREMENT_MEASUREMENT_TYPE2_SIZE;
        }
    }
    else
    {
        retVal = E_NOT_OK;
    }

    return retVal;

}

/* ***** END_API dcom_Global_Time_Sync_Measured_Values_0107_ReadData ***** */


/* ****************************************************************************
 *  ***** API private: dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase  ***** */
Std_ReturnType dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase(const StbM_SyncRecordTableBlockType *syncRecordTableBlock)
{
    Std_ReturnType retVal = E_OK;
    Std_ReturnType timerecordheader_fill_retval = E_OK ;
    Std_ReturnType timerecordblock1_fill_retval  = E_OK ;
    Std_ReturnType timerecordblock2_fill_retval  = E_OK ;

    timerecordheader_fill_retval  = dcom_MB_GTS_Measurement_Fill_TimeRecordHeader();

    if (0 == dcom_MB_MeasurementDataIndex)
    {
        timerecordblock1_fill_retval  = dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1(syncRecordTableBlock);
    }
    else
    {
        timerecordblock2_fill_retval  = dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2(syncRecordTableBlock);
    }

    /* Increase index till maximum of measurement sets defined by Daimler */
    dcom_MB_MeasurementDataIndex++;


    if (dcom_MB_MeasurementDataIndex > DCOM_MB_GTS_MEASUREMENT_SETS_TYPE2)
    {
        dcom_MB_MeasurementDataIndex = 0;
    }

    if ((timerecordheader_fill_retval == E_NOT_OK) || (timerecordblock1_fill_retval == E_NOT_OK) || (timerecordblock2_fill_retval == E_NOT_OK))
    {

        retVal = E_NOT_OK;
    }

    if( DCOM_MB_TRANSMISSION_ACTIVE == rbl_dcom_MirrorActvtDbgFrmsAppl_u8[0] )
    {
        /* sending measurement type 1 data to Custif */
        rbl_CustIf_Meas_IMU_X_ST3_PDU_Update(syncRecordTableBlock);
    }


    return retVal;
}
/* ***** END_API dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase ***** */
