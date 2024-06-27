/// @file rbl_CustIf_TiSync_AMG.c
/// @brief This file provides definitions to get Global Timestamp for Time Domain 2
/// @copyright (C) 2022 Robert Bosch GmbH.
/// The reproduction, distribution and utilization of this file as well as the
/// communication of its contents to others without express authorization is
/// prohibited. Offenders will be held liable for the payment of damages. All rights
/// reserved in the event of the grant of a patent, utility model or design.

/* ***** SECTION Includes ***** */

#include "rbl_CustIf_TiSync.h"
#include "Bfx.h"
#include "rbl_CustIf_GTS_Monitoring.h"

/* ***** END_SECTION Includes ***** */

/* ***** SECTION Local Definitions ***** */

static RBL_CUSTIF_GTS_LOCALFALLBACK_STATE rbl_Custif_GtslocalfallbackStatus = GTS_LOCALFALLBACK_IDLE;
static boolean rbl_Custif_Gtslocalfallback = FALSE;
static void rbl_TiSync_StbMAddNanoSeconds_AMG(StbM_TimeStampType *timeGTS_st, uint32 nanoseconds);
static Std_ReturnType rbl_TiSync_convertSystemTickstoGTS_AMG(uint32 timeMMP_u32, StbM_TimeStampType * timeGTS_st);

/* ***** END_SECTION Local Definitions ***** */

static uint8 rbl_TiSync_eventStatus_AMG = 0;
static boolean rbl_TiSync_rateCorrection_AMG = FALSE;
static boolean rbl_TiSync_cloneToPureLocal_AMG = FALSE;

/* ***** END_SECTION Local Definitions ***** */

/* ***** PUBLIC/PROTECTED API functions ***** */
/* ****************************************************************************/

Std_ReturnType rbl_CustIf_TiSync_eventStatusCallback_AMG(StbM_TimeBaseNotificationType eventNotification)
{
	/* Set a flag to Call the Cloning function upon recption of SYNCH-FUP message */
    //if(eventNotification == 0x01 || eventNotification == 0x0200)
    {
        rbl_TiSync_cloneToPureLocal_AMG = TRUE;
    }

	/* Set a flag to monitor rate correction is performed at least once */
    if(eventNotification == 0x0400)
    {
        rbl_TiSync_rateCorrection_AMG = TRUE;
    }

    return E_OK;
}

/* ***** PUBLIC/PROTECTED API functions ***** */
/* ****************************************************************************/


 /* ***** Local function: rbl_CustIf_TiSync_MMP2GtsTime_AMG *****/
Std_ReturnType rbl_CustIf_TiSync_MMP2GtsTime_AMG(uint32 timeMMP_u32, StbM_TimeStampType * timeGTS_st)
{
    Std_ReturnType retVal = E_NOT_OK;
    StbM_SynchronizedTimeBaseType TimeBaseId = 2;
    StbM_TimeBaseStatusType syncTimeBaseStatus;
    StbM_TimeBaseStatusType offsetTimeBaseStatus;
    StbM_TimeBaseStatusType lTimeBaseStatus;

	/* Call the Cloning function upon recption of SYNCH-FUP message */
    if(rbl_TiSync_cloneToPureLocal_AMG == TRUE)
    {
        rbl_TiSync_cloneToPureLocal_AMG = FALSE;
        rbl_TiSync_cloneToPureLocalTime_AMG();
    }
    retVal = rbl_TiSync_convertSystemTickstoGTS_AMG(timeMMP_u32, timeGTS_st);

    if(retVal == E_OK)
    {
        /* Write back the status, as this is not provided by the pure local timers */
        // The status of the Timestamp is transmitted every 5ms
        retVal = StbM_GetTimeBaseStatus(TimeBaseId, &syncTimeBaseStatus, &offsetTimeBaseStatus);

        lTimeBaseStatus = syncTimeBaseStatus;

        /* Modify status*/
        timeGTS_st->timeBaseStatus = RBL_CUSTIF_SNA;  /* Initialize to SNA */

        if (!Bfx_GetBit_u8u8_u8(lTimeBaseStatus, RBL_CUSTIF_GLOBAL_TIMEBASE_BflPn))
        {
            timeGTS_st->timeBaseStatus = RBL_CUSTIF_NO_INITIAL_SYNC; /* When GTB = 0, Time stamp status is NoInitialSync (1) */
        }

        else
        {
            /* Status is Synchronization SYNC LOST when any of TIMEOUT bit, TIME LEAP PAST, TIME LEAP FUTURE bits are SET (1) */
            /* TO + TLP + TLF > 0 */
            if((Bfx_GetBit_u8u8_u8(lTimeBaseStatus, RBL_CUSTIF_TIMEOUT_BflPn)) ||
                    (Bfx_GetBit_u8u8_u8(lTimeBaseStatus, RBL_CUSTIF_TIMELEAP_PAST_BflPn)) ||
                    (Bfx_GetBit_u8u8_u8(lTimeBaseStatus, RBL_CUSTIF_TIMELEAP_FUTURE_BflPn)))
           {
                timeGTS_st->timeBaseStatus = RBL_CUSTIF_SYNC_LOST;
           }
            /* If none of the Timeout, Time Leap Past, Time  Leap Future is set,  status is Synchronization OK */
            else
            {
                timeGTS_st->timeBaseStatus = RBL_CUSTIF_SYNC_OK; /* Status is sync OK when TO, TLP, TLF bits are 0 */
            }
        }

    }

    // Log monitor data for Copy Time and Copy Rate functionalities
    rbl_CustIf_StbM_Monitor_Time_Rate_Copy_AMG(rbl_TiSync_eventStatus_AMG);

    return retVal;
}

/* ***** Local function: rbl_TiSync_convertSystemTickstoGTS_AMG *****/
static Std_ReturnType rbl_TiSync_convertSystemTickstoGTS_AMG(uint32 timeMMP_u32, StbM_TimeStampType * timeGTS_st)
{
    Std_ReturnType retVal = E_NOT_OK;
    StbM_SynchronizedTimeBaseType TimeBaseIdPureLocal = 33;
    StbM_UserDataType UserData_st = {0};
    static uint32 currenttimestampMMP_u32 = 0;
    sint32 validTimeRange_i32 = 0;
    sint32 deltaTimeMMP_i32 = 0;
    uint32 timetimestampDifference = 0;
    sint32 nanosecondIncrease = 0;

    /*Start Interrupt Lock*/
    RBSYS_EnterCorelocalIntlock();

    /* Global Time Sync (GTS) Timestamp pure local time */
    retVal = StbM_GetCurrentTime(TimeBaseIdPureLocal, timeGTS_st, &UserData_st);

    currenttimestampMMP_u32 = RBSYS_getRealtimeTickCtr(); //RBSYS_getRealtimeTickCtr returns uint32

    /*Release Interrupt Lock*/
    RBSYS_ExitCorelocalIntlock();

    if(retVal != E_OK) /*Get Current for Tiime Base 2 is not succesful */
    {
        Bfx_SetBit_u8u8(&rbl_TiSync_eventStatus_AMG, GTS_DEMEVENT_GETCURRENT);
    }

    /* Compute time difference to extrapolate */
    timetimestampDifference = timeMMP_u32 - currenttimestampMMP_u32;
    deltaTimeMMP_i32 = (sint32)timetimestampDifference;

    /* Make sure that time difference is within acceptable range from last timestamp */
    validTimeRange_i32 = RBL_CUSTIF_TISYNC_MAXSYSTICKS;  // Convert time range to system ticks
    if ((deltaTimeMMP_i32 <=  validTimeRange_i32) &&
       (deltaTimeMMP_i32 >= -validTimeRange_i32) &&
       (retVal == E_OK))
    {

       /* Compute updated nanoseconds */
       nanosecondIncrease = ((deltaTimeMMP_i32 * ((sint32)RBL_CUSTIF_TISYNC_2SYSTICKS2NS + 1))/2);

       /* Add time difference to timestamp */
       (void)rbl_TiSync_StbMAddNanoSeconds_AMG(timeGTS_st,(uint32)nanosecondIncrease);

    }

    else
    {
       retVal = E_NOT_OK;
    }

    return retVal;
}
/* ***** END_API rbl_TiSync_convertSystemTickstoGTS_AMG ***** */

/* ***** Local function: rbl_TiSync_cloneToPureLocalTime_AMG *****/
void rbl_TiSync_cloneToPureLocalTime_AMG(void)
{
    Std_ReturnType retVal = E_NOT_OK;
    StbM_TimeStampType timestampGTS_st = {0};
    StbM_SynchronizedTimeBaseType TimeBaseIdPureLocal = 33;
    StbM_SynchronizedTimeBaseType TimeBaseId = 2;
    StbM_UserDataType UserData_st = {0};
    StbM_RateDeviationType rateDeviation = 0;
    StbM_TimeBaseStatusType TimeStampStatus;

    /*Start Interrupt Lock*/
    RBSYS_EnterCorelocalIntlock();

    /* get the synced Global Time and status */
    //To check for the Time Copy from Time Domain 2 to Time Domain 33
    retVal = StbM_GetCurrentTime(TimeBaseId, &timestampGTS_st, &UserData_st);

    if(retVal != E_OK) /*Get Current for Tiime Base 2 is not succesful */
    {
        Bfx_SetBit_u8u8(&rbl_TiSync_eventStatus_AMG, GTS_DEMEVENT_GETCURRENT);
    }

    retVal = StbM_GetRateDeviation(TimeBaseId, &rateDeviation);

	/* Log rate correction failure for cases when rate correction has occured at least once */
    if(retVal != E_OK && rbl_TiSync_rateCorrection_AMG == TRUE) /*Get Rate for Time Base 2 is not succesful */
    {
        Bfx_SetBit_u8u8(&rbl_TiSync_eventStatus_AMG, GTS_DEMEVENT_GETRATE);
    }

    TimeStampStatus = timestampGTS_st.timeBaseStatus;

    if (FALSE == rbl_Custif_Gtslocalfallback)
    {
        /* Compensate the processing delay in cloning */
        (void)rbl_TiSync_StbMAddNanoSeconds_AMG(&timestampGTS_st,(uint32)RBL_CUSTIF_CLONING_DELAY_NS);

        /* sync it back to pure local time */
        /* To check for the Time Copy from Time Domain 0 to Time Domain 32 */
        retVal = StbM_SetGlobalTime(TimeBaseIdPureLocal, &timestampGTS_st, &UserData_st);

        if(retVal != E_OK) /*Set Current for Tiime Base 2 is not succesful */
        {
            Bfx_SetBit_u8u8(&rbl_TiSync_eventStatus_AMG, GTS_DEMEVENT_SETCURRENT);
        }

        /* sync it back to pure local time */
        retVal = StbM_SetRateCorrection(TimeBaseIdPureLocal, rateDeviation);

        if(retVal != E_OK) /*Set Current for Tiime Base 2 is not succesful */
        {
            Bfx_SetBit_u8u8(&rbl_TiSync_eventStatus_AMG, GTS_DEMEVENT_SETRATE);
        }
    }
    else
    {
        /* Set SYNC to Pure Local Time Base Bit to 1 */
        Bfx_SetBit_u8u8(&TimeStampStatus, RBL_CUSTIF_SYNC2PURELOCAL_TIMEBASE_BflPn);
    }

    /*Release Interrupt Lock*/
    RBSYS_ExitCorelocalIntlock();

}
/* ***** END_API rbl_TiSync_cloneToPureLocalTime_AMG ***** */

 /* ***** Local function: rbl_TiSync_StbMAddNanoSeconds_AMG *****/
static void rbl_TiSync_StbMAddNanoSeconds_AMG(StbM_TimeStampType *timeGTS_st, uint32 nanoseconds)
{

    timeGTS_st->nanoseconds = timeGTS_st->nanoseconds + (uint32)nanoseconds;

    /* handle nanoseconds overflow */
    if ((timeGTS_st->nanoseconds >= RBL_CUSTIF_TISYNC_S2NS) && ((sint32)timeGTS_st->nanoseconds > 0))
    {
        timeGTS_st->nanoseconds -= RBL_CUSTIF_TISYNC_S2NS;
        timeGTS_st->seconds += 1;

        /* If we encountered an overflow of seconds */
        if(timeGTS_st->seconds == 0)
        {
            timeGTS_st->secondsHi += 1;
        }
    }

    else if((sint32)timeGTS_st->nanoseconds < 0)
    {
        timeGTS_st->nanoseconds += RBL_CUSTIF_TISYNC_S2NS;
        timeGTS_st->seconds -= 1;

        /* If we encountered an overflow of seconds */
        if(timeGTS_st->seconds == 0xFFFFFFFFu)
        {
            timeGTS_st->secondsHi -= 1;
        }
    }

    else
    {
        /* Nothing to Do*/
    }

}
/* ***** END_API rbl_TiSync_StbMAddNanoSeconds_AMG ***** */

 /* ***** Local function: rbl_CustIf_GTS_LocalFallBackCheck *****/
void rbl_CustIf_GTS_LocalFallBackCheck_AMG(void)
{
    static uint16 cnt = 1;
    static boolean isInitSync;
    static boolean isLostSync;
    static boolean isTimeLeap;

    isInitSync = rbl_CustIf_StbM_Check_Init_Sync();
    isLostSync = rbl_CustIf_StbM_Check_Lost_Sync();
    isTimeLeap = rbl_CustIf_StbM_Check_TimeLeap();

    switch(rbl_Custif_GtslocalfallbackStatus)
    {
        case GTS_LOCALFALLBACK_IDLE:

            /* Check Global Time base status bit*/
            if (TRUE == isInitSync)
            {
                rbl_Custif_GtslocalfallbackStatus = GTS_LOCALFALLBACK_CHECK;
            }

        break;

        case GTS_LOCALFALLBACK_CHECK:

            /* Check Sync Timeout and Time leaps*/
            if ((TRUE == isLostSync) || (TRUE == isTimeLeap))
            {
                rbl_Custif_Gtslocalfallback = TRUE;
                rbl_Custif_GtslocalfallbackStatus = GTS_LOCALFALLBACK_WAIT;
            }

        break;

        case GTS_LOCALFALLBACK_WAIT:

            /* wait for 70 seconds to set localfallback to False*/
            if (((TRUE != isLostSync) && (TRUE != isTimeLeap)) && (cnt >= RBL_CUSTIF_PLOCWAITTIME))
            {
                cnt = 0;
                rbl_Custif_Gtslocalfallback = FALSE;
                rbl_Custif_GtslocalfallbackStatus = GTS_LOCALFALLBACK_CHECK;
            }
            cnt++;

        break;

        default:
            /* set to wait state*/
            rbl_Custif_GtslocalfallbackStatus = GTS_LOCALFALLBACK_WAIT;
        break;

    }

}

/* ***** END_API rbl_CustIf_GTS_LocalFallBackCheck_AMG ***** */


/* ***** END_SECTION API functions ***** */
