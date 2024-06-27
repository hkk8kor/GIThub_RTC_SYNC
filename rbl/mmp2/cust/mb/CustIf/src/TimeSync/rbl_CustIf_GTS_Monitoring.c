/// @file rbl_CustIf_GTS_Monitoring.c
/// @brief This file provides definitions to Monitor the Global Time Synchronization.
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */

#include "rbl_CustIf_GTS_Monitoring.h"
#include "Dem.h"
#include "Bfx.h"

/* ***** END_SECTION Includes ***** */

/* ***** PUBLIC/PROTECTED API functions ***** */
static Std_ReturnType rbl_CustIf_StbM_Init_Base_Time(void);
static boolean rbl_CustIf_StbM_Monitor_Init_Timeout(void);

static StbM_TimeStampType rbl_CustIf_TimeStampBaseInit = {0, 0, 0, 0};
static const StbM_TimeStampType rbl_CustIf_initTimeoutTime = {0, 0, 15, 0};

/* ****************************************************************************
 * ***** API public: rbl_CustIf_GTS_Monitoring ***** */

void rbl_CustIf_GTS_Monitoring(void)
{
    static STBM_MONITOR_STATE StbM_Monitor_State = SMS_GET_INIT_BASE_TIME;

    switch (StbM_Monitor_State)
    {
        /* Initialize the base time to monitor init sync timeout */
        case SMS_GET_INIT_BASE_TIME:

            if (E_OK == rbl_CustIf_StbM_Init_Base_Time())
            {
                StbM_Monitor_State = SMS_CHECK_INIT_SYNC;
            }

            break;

        /* Monitor init sync timeout */
        case SMS_CHECK_INIT_SYNC:

		/*Check for init synchronisation ie bit 3 of TimeBaseStatus is set or not */
            if (TRUE == rbl_CustIf_StbM_Check_Init_Sync())
            {
				/*Report corresponding DEM event as passed and update the state to lost sync check*/
                /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
                (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_STBM_NO_INIT_SYNC_TIMEOUT,DEM_EVENT_STATUS_PASSED);
                StbM_Monitor_State = SMS_CHECK_LOST_SYNC;
            }
            else
            {
                if (TRUE == rbl_CustIf_StbM_Monitor_Init_Timeout())
                {
                  /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
                  (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_STBM_NO_INIT_SYNC_TIMEOUT,DEM_EVENT_STATUS_FAILED);
                  StbM_Monitor_State = SMS_WAIT_INIT_SYNC;
                }
            }
            break;

        /* Check till init synchronisation happens */
        case SMS_WAIT_INIT_SYNC:
            if (TRUE == rbl_CustIf_StbM_Check_Init_Sync())
            {
                /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
                (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_STBM_NO_INIT_SYNC_TIMEOUT,DEM_EVENT_STATUS_PASSED);
                StbM_Monitor_State = SMS_CHECK_LOST_SYNC;
            }
            else
            {
                /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
                (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_STBM_NO_INIT_SYNC_TIMEOUT,DEM_EVENT_STATUS_FAILED);
            }
            break;

        /* Monitor sync lost timeout */
        case SMS_CHECK_LOST_SYNC:

		/*Check for lost synchronisation ie bit 0 of TimeBaseStatus is set or not*/
            if (TRUE == rbl_CustIf_StbM_Check_Lost_Sync())
            {
                //TimeStampStatus = 0xCA;
				/*Report corresponding DEM event as failed and stay in lost sync check state*/
                /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
                (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_STBM_SYNC_LOST_TIMEOUT,DEM_EVENT_STATUS_FAILED);

            }
            else
            {
				/*Report corresponding DEM event as passed and update the state to timeleap check*/
                /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
                (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_STBM_SYNC_LOST_TIMEOUT,DEM_EVENT_STATUS_PASSED);
                StbM_Monitor_State = SMS_CHECK_TIME_LEAP;

            }
            break;

        /* Monitor time leap */
        case SMS_CHECK_TIME_LEAP:

		/*Check for time leap ie bit 4 or 5 of TimeBaseStatus is set or not*/
            if (TRUE == rbl_CustIf_StbM_Check_TimeLeap())
            {
				/*Report corresponding DEM event as failed and update the state to lost sync check*/
                /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
                (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_CUSTIF_STBM_TIMELEAP,DEM_EVENT_STATUS_FAILED);
                StbM_Monitor_State = SMS_CHECK_LOST_SYNC;

            }
            else
            {
				/*Report corresponding DEM event as passed and update the state to lost sync check*/
                /*No Handling done for E_NOT_OK as the old interface DemReportError had no return value */
                (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_CUSTIF_STBM_TIMELEAP,DEM_EVENT_STATUS_PASSED);
                StbM_Monitor_State = SMS_CHECK_LOST_SYNC;

            }
            break;

        default:
            StbM_Monitor_State = SMS_GET_INIT_BASE_TIME;
            break;
    }
}

static Std_ReturnType rbl_CustIf_StbM_Init_Base_Time(void)
{
    Std_ReturnType lRetVal = E_NOT_OK;
    VAR( StbM_TimeStampType, AUTOMATIC ) ltimestampGTS_st = {0, 0, 0, 0};
    VAR( StbM_UserDataType, AUTOMATIC ) lUserData_st;
    StbM_SynchronizedTimeBaseType TimeBaseId = 32;


    if (E_OK == StbM_GetCurrentTime(TimeBaseId,&ltimestampGTS_st, &lUserData_st))
    {
        /* This is a pure local time base, it could never be synchronized */
        if (ltimestampGTS_st.timeBaseStatus == 0)
        {
            /* Fill output pointers */
            rbl_CustIf_TimeStampBaseInit.secondsHi     = ltimestampGTS_st.secondsHi;
            rbl_CustIf_TimeStampBaseInit.seconds       = ltimestampGTS_st.seconds;
            rbl_CustIf_TimeStampBaseInit.nanoseconds   = ltimestampGTS_st.nanoseconds;
            lRetVal = E_OK;
        }
        else
        {
            lRetVal = E_NOT_OK;
        }
    }

    return lRetVal;
}

boolean rbl_CustIf_StbM_Check_Init_Sync(void)
{
    /* Local variables declaration */
    boolean lRetVal = FALSE;
    StbM_TimeBaseStatusType lTimeBaseStatus = 0;
    StbM_TimeBaseStatusType lOffsetTimeBaseStatus = 0;
    StbM_SynchronizedTimeBaseType TimeBaseId = 0;

    if (E_OK == StbM_GetTimeBaseStatus(TimeBaseId,&lTimeBaseStatus, &lOffsetTimeBaseStatus))
    {
        if (Bfx_GetBit_u8u8_u8(lTimeBaseStatus, RBL_CUSTIF_GLOBAL_TIMEBASE_BflPn))
        {
            lRetVal = TRUE;
        }
    }

    return lRetVal;
}

boolean rbl_CustIf_StbM_Check_Lost_Sync(void)
{
    /* Local variables declaration */
    boolean lRetVal = FALSE;
    StbM_TimeBaseStatusType lTimeBaseStatus = 0;
    StbM_TimeBaseStatusType lOffsetTimeBaseStatus = 0;
    StbM_SynchronizedTimeBaseType TimeBaseId = 0;

    if (E_OK == StbM_GetTimeBaseStatus(TimeBaseId,&lTimeBaseStatus, &lOffsetTimeBaseStatus))
    {
        if (Bfx_GetBit_u8u8_u8(lTimeBaseStatus, RBL_CUSTIF_TIMEOUT_BflPn))
        {
            lRetVal = TRUE;
        }
        else
        {
            lRetVal = FALSE;
        }
    }

    return lRetVal;
}


boolean rbl_CustIf_StbM_Check_TimeLeap(void)
{
    /* Local variables declaration */
    boolean lRetVal = FALSE;
    StbM_TimeBaseStatusType lTimeBaseStatus = 0;
    StbM_TimeBaseStatusType lOffsetTimeBaseStatus = 0;
    StbM_SynchronizedTimeBaseType TimeBaseId = 0;

    if (E_OK == StbM_GetTimeBaseStatus(TimeBaseId,&lTimeBaseStatus, &lOffsetTimeBaseStatus))
    {
        if ( (Bfx_GetBit_u8u8_u8(lTimeBaseStatus, RBL_CUSTIF_TIMELEAP_FUTURE_BflPn) == TRUE) ||
                     (Bfx_GetBit_u8u8_u8(lTimeBaseStatus, RBL_CUSTIF_TIMELEAP_PAST_BflPn) == TRUE  ))
        {
            lRetVal = TRUE;
        }
        else
        {
            lRetVal = FALSE;
        }
    }

    return lRetVal;
}

static boolean rbl_CustIf_StbM_Monitor_Init_Timeout(void)
{
    /* Local variables declaration */
    uint32 nanoseconds = 0;
    boolean lRetVal = FALSE;
    VAR( StbM_TimeStampType, AUTOMATIC ) ltimestampGTS_st = {0, 0, 0, 0};
    VAR( StbM_UserDataType, AUTOMATIC ) lUserData_st;
    StbM_SynchronizedTimeBaseType TimeBaseId = 32;

    if (E_OK == StbM_GetCurrentTime(TimeBaseId,&ltimestampGTS_st, &lUserData_st))
    {
        /* This is a pure local time base, it could never be synchronized */
        //if (ltimestampGTS_st.timeBaseStatus == 0)
        //{
            if (((ltimestampGTS_st.secondsHi - rbl_CustIf_TimeStampBaseInit.secondsHi) > 0)
                    || ((ltimestampGTS_st.seconds - rbl_CustIf_TimeStampBaseInit.seconds) > rbl_CustIf_initTimeoutTime.seconds))
            {
                lRetVal = TRUE;
            }
            else
            {
                if ((ltimestampGTS_st.seconds - rbl_CustIf_TimeStampBaseInit.seconds) == rbl_CustIf_initTimeoutTime.seconds)
                {
                    if (ltimestampGTS_st.nanoseconds < rbl_CustIf_TimeStampBaseInit.nanoseconds)
                    {
                        nanoseconds = (1000000000 - rbl_CustIf_TimeStampBaseInit.nanoseconds) + ltimestampGTS_st.nanoseconds;
                    }
                    else
                    {
                        nanoseconds = ltimestampGTS_st.nanoseconds - rbl_CustIf_TimeStampBaseInit.nanoseconds;
                    }
                    if (nanoseconds > rbl_CustIf_initTimeoutTime.nanoseconds)
                    {
                        lRetVal = TRUE;
                    }
                }
            }
        //}
    }

    return lRetVal;
}



void rbl_CustIf_StbM_Monitor_Time_Rate_Copy(uint8 eventStatus)
{
    Dem_EventStatusType lCurrentStatus = DEM_EVENT_STATUS_PASSED;
    Dem_EventStatusType lRateStatus = DEM_EVENT_STATUS_PASSED;

    /* Current failure has occured */
    if ((Bfx_GetBit_u8u8_u8(eventStatus, GTS_DEMEVENT_GETCURRENT) == TRUE) ||
            (Bfx_GetBit_u8u8_u8(eventStatus, GTS_DEMEVENT_SETCURRENT) == TRUE ))
    {
        lCurrentStatus = DEM_EVENT_STATUS_FAILED;
    }

    /* Rate failure has occured */
    if ((Bfx_GetBit_u8u8_u8(eventStatus, GTS_DEMEVENT_GETRATE) == TRUE) ||
            (Bfx_GetBit_u8u8_u8(eventStatus, GTS_DEMEVENT_SETRATE) == TRUE ))
    {
        lRateStatus = DEM_EVENT_STATUS_FAILED;
    }

    (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_STBM_TIME_COPY,lCurrentStatus);

    (void)Dem_SetEventStatus(DemConf_DemEventParameter_RBL_STBM_RATE_COPY,lRateStatus);
}


