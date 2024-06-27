/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_CustIf_GTS_Monitoring.c
 *    Author: GDEV1KOR
 *    Generated on: 16-Feb-2024 12:31:57
 *    Generated from: rbl_CustIf_GTS_Monitoring.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "../../../../../../rbl/mmp2/cust/mb/rbl_CustIf/src/TimeSync/rbl_CustIf_GTS_Monitoring.h"
#include "Dem.h"
#include "Bfx.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern boolean ACCESS_FUNCTION_rbl_CustIf_GTS_Monitoring_Bfx_Prv_GetBit_u8u8_u8_Inl(uint8 Data, uint8 BitPn);
extern Std_ReturnType ACCESS_FUNCTION_rbl_CustIf_GTS_Monitoring_rbl_CustIf_StbM_Init_Base_Time();
extern boolean rbl_CustIf_StbM_Check_Init_Sync();
extern boolean ACCESS_FUNCTION_rbl_CustIf_GTS_Monitoring_rbl_CustIf_StbM_Monitor_Init_Timeout();
extern boolean rbl_CustIf_StbM_Check_Lost_Sync();
extern boolean rbl_CustIf_StbM_Check_TimeLeap();
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);
Std_ReturnType StbM_GetCurrentTime(StbM_SynchronizedTimeBaseType timeBaseId, StbM_TimeStampType * timeStamp, StbM_UserDataType * userData);
Std_ReturnType StbM_GetTimeBaseStatus(StbM_SynchronizedTimeBaseType timeBaseId, StbM_TimeBaseStatusType * syncTimeBaseStatus, StbM_TimeBaseStatusType * offsetTimeBaseStatus);

/* Global data */
typedef struct rbl_CustIf_GTS_Monitoring_av_struct { StbM_TimeStampType * ref_rbl_CustIf_TimeStampBaseInit; const StbM_TimeStampType * ref_rbl_CustIf_initTimeoutTime; } rbl_CustIf_GTS_Monitoring_av_struct;
extern rbl_CustIf_GTS_Monitoring_av_struct av_rbl_CustIf_GTS_Monitoring;
extern STBM_MONITOR_STATE * LOCAL_VARIABLE_ACCESSOR(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State);

/* Expected variables for global data */
typedef struct expected_rbl_CustIf_GTS_Monitoring_av_struct { StbM_TimeStampType ref_rbl_CustIf_TimeStampBaseInit; StbM_TimeStampType ref_rbl_CustIf_initTimeoutTime; } expected_rbl_CustIf_GTS_Monitoring_av_struct;
expected_rbl_CustIf_GTS_Monitoring_av_struct expected_av_rbl_CustIf_GTS_Monitoring;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit));
    /* No initialisation for const data: rbl_CustIf_initTimeoutTime */
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit));
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_MEMORY("ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit)", &ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit), &ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit)));
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_CustIf_GTS_Monitoring(int);
void ut_rbl_CustIf_StbM_Init_Base_Time(int);
void ut_rbl_CustIf_StbM_Check_Init_Sync(int);
void ut_rbl_CustIf_StbM_Check_Lost_Sync(int);
void ut_rbl_CustIf_StbM_Check_TimeLeap(int);
void ut_rbl_CustIf_StbM_Monitor_Init_Timeout(int);
void ut_rbl_CustIf_StbM_Monitor_Time_Rate_Copy(int);
/*****************************************************************************/
/* Coverage Analysis                                                         */
/*****************************************************************************/
/* Coverage Rule Set: ISO26262-6 2011 ASIL D unit level (HR) */
static void rule_set(char* cppca_sut,
                     char* cppca_context)
{
    START_TEST("COVERAGE RULE SET",
               "ISO26262-6 2011 ASIL D unit level (HR)");
#ifdef CANTPP_SUBSET_DEFERRED_ANALYSIS
    TEST_SCRIPT_WARNING("Coverage Rule Set ignored in deferred analysis mode\n");
#elif CANTPP_COVERAGE_INSTRUMENTATION_DISABLED
    TEST_SCRIPT_WARNING("Coverage Instrumentation has been disabled\n");
#elif CANTPP_INSTRUMENTATION_DISABLED
    TEST_SCRIPT_WARNING("Instrumentation has been disabled\n");
#else
    ANALYSIS_CHECK("100% Entry Point Coverage",
                   cppca_entrypoint_cov,
                   100.0);
    
    ANALYSIS_CHECK("100% Statement Coverage",
                   cppca_statement_cov,
                   100.0);
    
    ANALYSIS_CHECK("100% Decision Coverage",
                   cppca_decision_cov,
                   100.0);
    
    ANALYSIS_CHECK("100% Boolean Operand Effectiveness Coverage",
                   cppca_booleff_cov,
                   100.0);
    
    REPORT_COVERAGE(cppca_entrypoint_cov|
                    cppca_statement_cov|
                    cppca_decision_cov|
                    cppca_booleff_cov,
                    cppca_sut,
                    cppca_all_details|cppca_include_catch,
                    cppca_context);
#endif
    END_TEST();
}

/*****************************************************************************/
/* Program Entry Point                                                       */
/*****************************************************************************/
int main()
{
    CONFIGURE_COVERAGE("cov:boolcomb:yes");
    OPEN_LOG("ut_rbl_CustIf_GTS_Monitoring.ctr", false, 100);
    START_SCRIPT("rbl_CustIf_GTS_Monitoring", true);

    run_tests();

    return !END_SCRIPT(true);
}

/*****************************************************************************/
/* Test Control                                                              */
/*****************************************************************************/
/* run_tests() contains calls to the individual test cases, you can turn test*/
/* cases off by adding comments*/
void run_tests()
{
    ut_rbl_CustIf_GTS_Monitoring(1);
    ut_rbl_CustIf_StbM_Init_Base_Time(1);
    ut_rbl_CustIf_StbM_Check_Init_Sync(1);
    ut_rbl_CustIf_StbM_Check_Lost_Sync(1);
    ut_rbl_CustIf_StbM_Check_TimeLeap(1);
    ut_rbl_CustIf_StbM_Monitor_Init_Timeout(1);
    ut_rbl_CustIf_StbM_Monitor_Time_Rate_Copy(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_CustIf_GTS_Monitoring.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rbl_CustIf_GTS_Monitoring(int doIt)
{
    if (doIt)
        {
            START_TEST("48695: [MMP2.11]UTC_rbl_CustIf_GTS_Monitoring",
                       "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48695");

            START_STEP("1_NTS", TRUE);
            {
                // Expected Call Sequence
                EXPECTED_CALLS("rbl_CustIf_StbM_Init_Base_Time#Valid");

                 /* Call SUT */
                 rbl_CustIf_GTS_Monitoring();

                 /* Test case checks */
                 CHECK_U_INT(ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State), SMS_CHECK_INIT_SYNC);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("2_NTS", TRUE);
            {

                ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State ) = SMS_GET_INIT_BASE_TIME;

                // Expected Call Sequence
                EXPECTED_CALLS("rbl_CustIf_StbM_Init_Base_Time#InValid");

                 /* Call SUT */
                 rbl_CustIf_GTS_Monitoring();

                 /* Test case checks */
                 CHECK_U_INT(ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State), SMS_GET_INIT_BASE_TIME);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("3_NTS", TRUE);
            {
                ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State) = SMS_CHECK_INIT_SYNC;

                // Expected Call Sequence
                EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#Valid;"
                               "Dem_SetEventStatus#TIMEOUT_PASSED");

                 /* Call SUT */
                 rbl_CustIf_GTS_Monitoring();

                 /* Test case checks */
                 CHECK_U_INT(ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State), SMS_CHECK_LOST_SYNC);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("4_NTS", TRUE);
            {
                ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State) = SMS_CHECK_INIT_SYNC;

                // Expected Call Sequence
                EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#InValid;"
                               "rbl_CustIf_StbM_Monitor_Init_Timeout#Valid;"
                               "Dem_SetEventStatus#TIMEOUT_FAILED");

                 /* Call SUT */
                 rbl_CustIf_GTS_Monitoring();

                 /* Test case checks */
                 CHECK_U_INT(ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State), SMS_WAIT_INIT_SYNC);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("5_NTS", TRUE);
            {
                ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State) = SMS_CHECK_INIT_SYNC;

                // Expected Call Sequence
                EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#InValid;"
                               "rbl_CustIf_StbM_Monitor_Init_Timeout#InValid");

                 /* Call SUT */
                 rbl_CustIf_GTS_Monitoring();

                 /* Test case checks */
                 CHECK_U_INT(ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State), SMS_CHECK_INIT_SYNC);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("6_NTS", TRUE);
            {
                ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State) = SMS_WAIT_INIT_SYNC;

                // Expected Call Sequence
                EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#Valid;"
                               "Dem_SetEventStatus#TIMEOUT_PASSED");

                 /* Call SUT */
                 rbl_CustIf_GTS_Monitoring();

                 /* Test case checks */
                 CHECK_U_INT(ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State), SMS_CHECK_LOST_SYNC);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("7_NTS", TRUE);
            {
                ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State) = SMS_WAIT_INIT_SYNC;

                // Expected Call Sequence
                EXPECTED_CALLS("rbl_CustIf_StbM_Check_Init_Sync#InValid;"
                               "Dem_SetEventStatus#TIMEOUT_FAILED");

                 /* Call SUT */
                 rbl_CustIf_GTS_Monitoring();

                 /* Test case checks */
                 CHECK_U_INT(ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State), SMS_WAIT_INIT_SYNC);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("8_NTS", TRUE);
            {
                ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State) = SMS_CHECK_LOST_SYNC;

                // Expected Call Sequence
                EXPECTED_CALLS("rbl_CustIf_StbM_Check_Lost_Sync#Valid;"
                               "Dem_SetEventStatus#LOST_TIMEOUT_FAILED");

                 /* Call SUT */
                 rbl_CustIf_GTS_Monitoring();

                 /* Test case checks */
                 CHECK_U_INT(ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State), SMS_CHECK_LOST_SYNC);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("9_NTS", TRUE);
            {
                ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State) = SMS_CHECK_LOST_SYNC;

                // Expected Call Sequence
                EXPECTED_CALLS("rbl_CustIf_StbM_Check_Lost_Sync#InValid;"
                               "Dem_SetEventStatus#LOST_TIMEOUT_PASSED");

                 /* Call SUT */
                 rbl_CustIf_GTS_Monitoring();

                 /* Test case checks */
                 CHECK_U_INT(ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State), SMS_CHECK_TIME_LEAP);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("10_NTS", TRUE);
            {
                ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State) = SMS_CHECK_TIME_LEAP;

                // Expected Call Sequence
                EXPECTED_CALLS("rbl_CustIf_StbM_Check_TimeLeap#Valid;"
                               "Dem_SetEventStatus#TIMELEAP_FAILED");

                 /* Call SUT */
                 rbl_CustIf_GTS_Monitoring();

                 /* Test case checks */
                 CHECK_U_INT(ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State), SMS_CHECK_LOST_SYNC);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("11_NTS", TRUE);
            {
                ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State) = SMS_CHECK_TIME_LEAP;

                // Expected Call Sequence
                EXPECTED_CALLS("rbl_CustIf_StbM_Check_TimeLeap#InValid;"
                               "Dem_SetEventStatus#TIMELEAP_PASSED");

                 /* Call SUT */
                 rbl_CustIf_GTS_Monitoring();

                 /* Test case checks */
                 CHECK_U_INT(ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State), SMS_CHECK_LOST_SYNC);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("12_NTS", TRUE);
            {
                ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State) = 10;

                // Expected Call Sequence
                EXPECTED_CALLS("");

                 /* Call SUT */
                 rbl_CustIf_GTS_Monitoring();

                 /* Test case checks */
                 CHECK_U_INT(ACCESS_LOCAL_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_GTS_Monitoring, StbM_Monitor_State), SMS_GET_INIT_BASE_TIME);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }
        }
}

void ut_rbl_CustIf_StbM_Init_Base_Time(int doIt)
{
    if (doIt)
        {
            START_TEST("48694: [MMP2.11]UTC_CustIf_StbM_Init_Base_Time",
                       "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48694");

            START_STEP("1_NTS", TRUE);
            {
                Std_ReturnType returnValue = E_NOT_OK;

                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).secondsHi = 123;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).seconds = 123;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).nanoseconds = 123;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetCurrentTime#Valid");

                 /* Call SUT */
                 returnValue = ACCESS_FUNCTION(rbl_CustIf_GTS_Monitoring, rbl_CustIf_StbM_Init_Base_Time)();

                 /* Test case checks */
                 CHECK_U_CHAR(returnValue,E_OK);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("2_NTS", TRUE);
            {
                Std_ReturnType returnValue = E_NOT_OK;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetCurrentTime#OK_INVALID");

                 /* Call SUT */
                 returnValue = ACCESS_FUNCTION(rbl_CustIf_GTS_Monitoring, rbl_CustIf_StbM_Init_Base_Time)();

                 /* Test case checks */
                 CHECK_U_CHAR(returnValue,E_NOT_OK);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("3_NTS", TRUE);
            {
                Std_ReturnType returnValue = E_NOT_OK;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetCurrentTime#InValid");

                 /* Call SUT */
                 returnValue = ACCESS_FUNCTION(rbl_CustIf_GTS_Monitoring, rbl_CustIf_StbM_Init_Base_Time)();

                 /* Test case checks */
                 CHECK_U_CHAR(returnValue,E_NOT_OK);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }
            END_TEST();
       }
}

void ut_rbl_CustIf_StbM_Check_Init_Sync(int doIt)
{
    if (doIt)
        {

            START_TEST("48690: [MMP2.11]UTC_rbl_CustIf_GTS_Monitoring_rbl_CustIf_StbM_Check_Init_Sync",
                       "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48690");

            START_STEP("1_NTS", TRUE);
            {
                Std_ReturnType returnValue = FALSE;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetTimeBaseStatus#Valid_INIT_Bit_Set;\
                		        Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_1");

                 /* Call SUT */
                 returnValue = rbl_CustIf_StbM_Check_Init_Sync();

                 /* Test case checks */
                 CHECK_U_CHAR(returnValue,TRUE);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("2_NTS", TRUE);
            {
                Std_ReturnType returnValue = FALSE;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetTimeBaseStatus#Valid_Bit_Not_Set;\
                		        Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_2");
                 /* Call SUT */
                returnValue = rbl_CustIf_StbM_Check_Init_Sync();

                 /* Test case checks */
                 CHECK_U_CHAR(returnValue,FALSE);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("3_NTS", TRUE);
            {
                Std_ReturnType returnValue = FALSE;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetTimeBaseStatus#InValid");

                 /* Call SUT */
                returnValue = rbl_CustIf_StbM_Check_Init_Sync();

                 /* Test case checks */
                 CHECK_U_CHAR(returnValue,FALSE);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }
            END_TEST();
       }
}

void ut_rbl_CustIf_StbM_Check_Lost_Sync(int doIt)
{
    if (doIt)
        {

            START_TEST("48691: [MMP2.11]UTC_rbl_CustIf_GTS_Monitoring_rbl_CustIf_StbM_Check_Lost_Sync",
                       "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48691");

            START_STEP("1_NTS", TRUE);
            {
                Std_ReturnType returnValue = FALSE;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetTimeBaseStatus#Valid_LOST_Bit_Set;\
                		        Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_3");
                 /* Call SUT */
                 returnValue = rbl_CustIf_StbM_Check_Lost_Sync();

                 /* Test case checks */
                 CHECK_U_CHAR(returnValue,TRUE);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("2_NTS", TRUE);
            {
                Std_ReturnType returnValue = FALSE;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetTimeBaseStatus#Valid_Bit_Not_Set;\
                		        Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_4");
                 /* Call SUT */
                returnValue = rbl_CustIf_StbM_Check_Lost_Sync();

                 /* Test case checks */
                 CHECK_U_CHAR(returnValue,FALSE);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
              }

            START_STEP("3_NTS", TRUE);
            {
                Std_ReturnType returnValue = FALSE;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetTimeBaseStatus#InValid");

                 /* Call SUT */
                returnValue = rbl_CustIf_StbM_Check_Lost_Sync();

                 /* Test case checks */
                 CHECK_U_CHAR(returnValue,FALSE);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }
            END_TEST();
      }
}

void ut_rbl_CustIf_StbM_Check_TimeLeap(int doIt)
{
    if (doIt)
        {

            START_TEST("48692: [MMP2.11]UTC_rbl_CustIf_GTS_Monitoring_rbl_CustIf_StbM_Check_TimeLeap",
                       "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48692");

            START_STEP("1_NTS", TRUE);
            {
                Std_ReturnType returnValue = FALSE;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetTimeBaseStatus#Valid_TIMELEAP_Bit_Set;\
                		        Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_5");

                 /* Call SUT */
                 returnValue = rbl_CustIf_StbM_Check_TimeLeap();

                 /* Test case checks */
                 CHECK_U_CHAR(returnValue,TRUE);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("2_NTS", TRUE);
            {
                Std_ReturnType returnValue = FALSE;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetTimeBaseStatus#Valid_Future_Bit_Set;\
                		        Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_6");

                 /* Call SUT */
                returnValue = rbl_CustIf_StbM_Check_TimeLeap();

                 /* Test case checks */
                 CHECK_U_CHAR(returnValue,TRUE);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("3_NTS", TRUE);
            {
                Std_ReturnType returnValue = FALSE;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetTimeBaseStatus#Valid_Past_Bit_Set;\
                		        Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_7;\
                                Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_8");

                 /* Call SUT */
                returnValue = rbl_CustIf_StbM_Check_TimeLeap();

                 /* Test case checks */
                 CHECK_U_CHAR(returnValue,TRUE);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("4_NTS", TRUE);
            {
                Std_ReturnType returnValue = FALSE;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetTimeBaseStatus#Valid_Bit_Not_Set;\
                		        Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_9;\
                                Bfx_Prv_GetBit_u8u8_u8_Inl#Bfx_Prv_GetBit_u8u8_u8_Inl_10");

                 /* Call SUT */
                returnValue = rbl_CustIf_StbM_Check_TimeLeap();

                 /* Test case checks */
                 CHECK_U_CHAR(returnValue,FALSE);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }

            START_STEP("5_NTS", TRUE);
            {
                Std_ReturnType returnValue = FALSE;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetTimeBaseStatus#InValid");

                 /* Call SUT */
                returnValue = rbl_CustIf_StbM_Check_TimeLeap();

                 /* Test case checks */
                 CHECK_U_CHAR(returnValue,FALSE);

                 /* Checks on global data */
                 check_global_data();
                 END_CALLS();
                 END_STEP();
            }
            END_TEST();
            }
}

void ut_rbl_CustIf_StbM_Monitor_Init_Timeout(int doIt)
{
    if (doIt)
        {

            START_TEST("48693: [MMP2.11]UTC_rbl_CustIf_GTS_Monitoring_rbl_CustIf_StbM_Monitor_Init_Timeout",
                       "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48693");

            START_STEP("1_NTS", TRUE);
            {

                boolean returnValue = FALSE;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetCurrentTime#InValid");

                /* Call SUT */
                returnValue = ACCESS_FUNCTION(rbl_CustIf_GTS_Monitoring, rbl_CustIf_StbM_Monitor_Init_Timeout)();

                /* Test case checks */
                CHECK_BOOLEAN(returnValue,FALSE);

                /* Checks on global data */
                check_global_data();
                END_CALLS();
                END_STEP();

            }

            START_STEP("2_NTS", TRUE);
            {

                boolean returnValue = FALSE;

                ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).secondsHi = 0;
                ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).seconds = 0;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).secondsHi = 0;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).seconds = 0;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetCurrentTime#CASE_1");

                /* Call SUT */
                returnValue = ACCESS_FUNCTION(rbl_CustIf_GTS_Monitoring, rbl_CustIf_StbM_Monitor_Init_Timeout)();

                /* Test case checks */
                CHECK_BOOLEAN(returnValue,TRUE);

                /* Checks on global data */
                check_global_data();
                END_CALLS();
                END_STEP();

            }

            START_STEP("3_NTS", TRUE);
            {

                boolean returnValue = FALSE;

                ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).secondsHi = 0;
                ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).seconds = 0;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).secondsHi = 0;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).seconds = 0;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetCurrentTime#CASE_2");

                /* Call SUT */
                returnValue = ACCESS_FUNCTION(rbl_CustIf_GTS_Monitoring, rbl_CustIf_StbM_Monitor_Init_Timeout)();

                /* Test case checks */
                CHECK_BOOLEAN(returnValue,TRUE);

                /* Checks on global data */
                check_global_data();
                END_CALLS();
                END_STEP();

            }

            START_STEP("4_NTS", TRUE);
            {

                boolean returnValue = FALSE;

                ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).secondsHi = 0;
                ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).seconds = 0;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).secondsHi = 0;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).seconds = 0;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetCurrentTime#CASE_3");

                /* Call SUT */
                returnValue = ACCESS_FUNCTION(rbl_CustIf_GTS_Monitoring, rbl_CustIf_StbM_Monitor_Init_Timeout)();

                /* Test case checks */
                CHECK_BOOLEAN(returnValue,FALSE);

                /* Checks on global data */
                check_global_data();
                END_CALLS();
                END_STEP();

            }

            START_STEP("5_NTS", TRUE);
            {

                boolean returnValue = FALSE;

                ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).secondsHi = 0;
                ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).seconds = 0;
                ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).nanoseconds = 1000000000;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).secondsHi = 0;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).seconds = 0;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).nanoseconds = 1000000000;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetCurrentTime#CASE_4");

                /* Call SUT */
                returnValue = ACCESS_FUNCTION(rbl_CustIf_GTS_Monitoring, rbl_CustIf_StbM_Monitor_Init_Timeout)();

                /* Test case checks */
                CHECK_BOOLEAN(returnValue,TRUE);

                /* Checks on global data */
                check_global_data();
                END_CALLS();
                END_STEP();

            }

            START_STEP("6_NTS", TRUE);
            {

                boolean returnValue = FALSE;

                ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).secondsHi = 0;
                ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).seconds = 0;
                ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).nanoseconds = 100;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).secondsHi = 0;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).seconds = 0;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).nanoseconds = 100;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetCurrentTime#CASE_5");

                /* Call SUT */
                returnValue = ACCESS_FUNCTION(rbl_CustIf_GTS_Monitoring, rbl_CustIf_StbM_Monitor_Init_Timeout)();

                /* Test case checks */
                CHECK_BOOLEAN(returnValue,TRUE);

                /* Checks on global data */
                check_global_data();
                END_CALLS();
                END_STEP();

            }

            START_STEP("7_NTS", TRUE);
            {

                boolean returnValue = FALSE;
                uint32 nanoseconds = 10;

                ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).secondsHi = 0;
                ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).seconds = 0;
                ACCESS_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).nanoseconds = 0;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).secondsHi = 0;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).seconds = 0;
                ACCESS_EXPECTED_VARIABLE(rbl_CustIf_GTS_Monitoring, rbl_CustIf_TimeStampBaseInit).nanoseconds = 0;

                // Expected Call Sequence
                EXPECTED_CALLS("StbM_GetCurrentTime#CASE_6");

                /* Call SUT */
                returnValue = ACCESS_FUNCTION(rbl_CustIf_GTS_Monitoring, rbl_CustIf_StbM_Monitor_Init_Timeout)();

                /* Test case checks */
                CHECK_BOOLEAN(returnValue,FALSE);

                /* Checks on global data */
                check_global_data();
                END_CALLS();
                END_STEP();
            }
   }
}

void ut_rbl_CustIf_StbM_Monitor_Time_Rate_Copy(int doIt)
{
	if (doIt)
	{
		Dem_EventStatusType EventStatusTimeCopy = DEM_EVENT_STATUS_FAILED;
		Dem_EventStatusType EventStatusRateCopy = DEM_EVENT_STATUS_PASSED;

		START_TEST("49816: [MMP2.11]UTC_rbl_CustIf_StbM_Monitor_Time_Rate_Copy",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49816");

		/* Test steps*/
		START_STEP("1_NTS", true);
		{
			/*initialise_globals*/

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Dem_SetEventStatus#Dem_SetEventStatus_1;"
					       "Dem_SetEventStatus#Dem_SetEventStatus_2");

			/* Call SUT */
			rbl_CustIf_StbM_Monitor_Time_Rate_Copy(EventStatusTimeCopy,EventStatusRateCopy);

			/* Test step checks */

		    END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function Dem_SetEventStatus */
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId,
                                  Dem_EventStatusType EventStatus){
    REGISTER_CALL("Dem_SetEventStatus");

    IF_INSTANCE("TIMEOUT_PASSED") {
        CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_STBM_NO_INIT_SYNC_TIMEOUT);
        CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_PASSED);
            return DEM_EVENT_STATUS_PASSED;
        }

        IF_INSTANCE("TIMEOUT_FAILED") {
        CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_STBM_NO_INIT_SYNC_TIMEOUT);
        CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
            return DEM_EVENT_STATUS_FAILED;
        }

        IF_INSTANCE("LOST_TIMEOUT_PASSED") {
        CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_STBM_SYNC_LOST_TIMEOUT);
        CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_PASSED);
            return DEM_EVENT_STATUS_PASSED;
        }

        IF_INSTANCE("LOST_TIMEOUT_FAILED") {
        CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_STBM_SYNC_LOST_TIMEOUT);
        CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
            return DEM_EVENT_STATUS_FAILED;
        }

        IF_INSTANCE("TIMELEAP_PASSED") {
        CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_CUSTIF_STBM_TIMELEAP);
        CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_PASSED);
            return DEM_EVENT_STATUS_PASSED;
        }

        IF_INSTANCE("TIMELEAP_FAILED") {
        CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_CUSTIF_STBM_TIMELEAP);
        CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
            return DEM_EVENT_STATUS_FAILED;
        }

        IF_INSTANCE("Dem_SetEventStatus_1") {
        CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_STBM_TIME_COPY);
        CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_FAILED);
            return DEM_EVENT_STATUS_FAILED;
        }

        IF_INSTANCE("Dem_SetEventStatus_2") {
        CHECK_U_INT(EventId, DemConf_DemEventParameter_RBL_STBM_RATE_COPY);
        CHECK_U_INT(EventStatus, DEM_EVENT_STATUS_PASSED);
            return DEM_EVENT_STATUS_PASSED;
        }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function StbM_GetCurrentTime */
Std_ReturnType StbM_GetCurrentTime(StbM_SynchronizedTimeBaseType timeBaseId,
                                   StbM_TimeStampType * timeStamp,
                                   StbM_UserDataType * userData){
    REGISTER_CALL("StbM_GetCurrentTime");

    IF_INSTANCE("Valid")
        {
            timeStamp->timeBaseStatus = 0;
            timeStamp->nanoseconds = 123;
            timeStamp->seconds = 123;
            timeStamp->secondsHi = 123;
            return E_OK;
        }

    IF_INSTANCE("E_OK")
        {
            return E_OK;
        }

    IF_INSTANCE("OK_INVALID")
        {
           timeStamp->timeBaseStatus = 1;
           return E_OK;
        }

    IF_INSTANCE("CASE_1")
        {
            timeStamp->timeBaseStatus = 0;
            timeStamp->seconds = 123;
            timeStamp->secondsHi = 0;
            return E_OK;
        }

    IF_INSTANCE("CASE_2")
        {
            timeStamp->timeBaseStatus = 0;
            timeStamp->seconds = 0;
            timeStamp->secondsHi = 123;
            return E_OK;
        }

     IF_INSTANCE("CASE_3")
        {
            timeStamp->timeBaseStatus = 0;
            timeStamp->seconds = 0;
            timeStamp->secondsHi = 0;
            return E_OK;
        }

     IF_INSTANCE("CASE_4")
        {
            timeStamp->timeBaseStatus = 0;
            timeStamp->nanoseconds = 1000;
            timeStamp->seconds = 15;
            timeStamp->secondsHi = 0;
            return E_OK;
        }

     IF_INSTANCE("CASE_5")
        {
            timeStamp->timeBaseStatus = 0;
            timeStamp->nanoseconds = 10000;
            timeStamp->seconds = 15;
            timeStamp->secondsHi = 0;
            return E_OK;
        }

     IF_INSTANCE("CASE_6")
        {
            timeStamp->timeBaseStatus = 0;
            timeStamp->nanoseconds = 0;
            timeStamp->seconds = 15;
            timeStamp->secondsHi = 0;
            return E_OK;
         }

     IF_INSTANCE("InValid")
        {
            return E_NOT_OK;
        }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function StbM_GetTimeBaseStatus */
Std_ReturnType StbM_GetTimeBaseStatus(StbM_SynchronizedTimeBaseType timeBaseId,
                                      StbM_TimeBaseStatusType * syncTimeBaseStatus,
                                      StbM_TimeBaseStatusType * offsetTimeBaseStatus){
    REGISTER_CALL("StbM_GetTimeBaseStatus");

    IF_INSTANCE("Valid_INIT_Bit_Set") {
       * syncTimeBaseStatus = 0x08;
              return E_OK;
        }

    IF_INSTANCE("Valid_LOST_Bit_Set") {
       * syncTimeBaseStatus = 0x01;
                  return E_OK;
            }

    IF_INSTANCE("Valid_TIMELEAP_Bit_Set") {
       * syncTimeBaseStatus = 0x30;
                      return E_OK;
                }

    IF_INSTANCE("Valid_Bit_Not_Set") {
        * syncTimeBaseStatus = 0x00;
          return E_OK;
    }

    IF_INSTANCE("Valid_Future_Bit_Set") {
            * syncTimeBaseStatus = 0x10;
            return E_OK;
    }

    IF_INSTANCE("Valid_Past_Bit_Set") {
        * syncTimeBaseStatus = 0x20;
        return E_OK;
     }

    IF_INSTANCE("InValid") {
        return E_NOT_OK;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function Bfx_Prv_GetBit_u8u8_u8_Inl */
int BEFORE_Bfx_Prv_GetBit_u8u8_u8_Inl(uint8 Data,
                                      uint8 BitPn){
    REGISTER_CALL("Bfx_Prv_GetBit_u8u8_u8_Inl");

    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_1") {
    	CHECK_U_CHAR(Data,0x08);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_GLOBAL_TIMEBASE_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_2") {
    	CHECK_U_CHAR(Data,0x00);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_GLOBAL_TIMEBASE_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_3") {
    	CHECK_U_CHAR(Data,0x01);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TIMEOUT_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_4") {
    	CHECK_U_CHAR(Data,0x00);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TIMEOUT_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_5") {
    	CHECK_U_CHAR(Data,0x30);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TIMELEAP_FUTURE_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_6") {
    	CHECK_U_CHAR(Data,0x10);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TIMELEAP_FUTURE_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_7") {
    	CHECK_U_CHAR(Data,0x20);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TIMELEAP_FUTURE_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_8") {
    	CHECK_U_CHAR(Data,0x20);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TIMELEAP_PAST_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_9") {
    	CHECK_U_CHAR(Data,0x00);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TIMELEAP_FUTURE_BflPn);
        return REPLACE_WRAPPER;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_10") {
    	CHECK_U_CHAR(Data,0x00);
    	CHECK_U_CHAR(BitPn,RBL_CUSTIF_TIMELEAP_PAST_BflPn);
        return REPLACE_WRAPPER;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function Bfx_Prv_GetBit_u8u8_u8_Inl */
boolean AFTER_Bfx_Prv_GetBit_u8u8_u8_Inl(boolean cppsm_return_value,
                                         uint8 Data,
                                         uint8 BitPn){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function Bfx_Prv_GetBit_u8u8_u8_Inl */
boolean REPLACE_Bfx_Prv_GetBit_u8u8_u8_Inl(uint8 Data,
                                           uint8 BitPn){
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_1") {
        return TRUE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_2") {
        return FALSE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_3") {
        return TRUE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_4") {
        return FALSE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_5") {
        return TRUE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_6") {
        return TRUE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_7") {
        return FALSE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_8") {
        return TRUE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_9") {
        return FALSE;
    }
    IF_INSTANCE("Bfx_Prv_GetBit_u8u8_u8_Inl_10") {
        return FALSE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_CustIf_StbM_Init_Base_Time */
int BEFORE_rbl_CustIf_StbM_Init_Base_Time(){
    REGISTER_CALL("rbl_CustIf_StbM_Init_Base_Time");

    IF_INSTANCE("Valid") {
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("InValid") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_StbM_Init_Base_Time */
Std_ReturnType AFTER_rbl_CustIf_StbM_Init_Base_Time(Std_ReturnType cppsm_return_value){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_CustIf_StbM_Init_Base_Time */
Std_ReturnType REPLACE_rbl_CustIf_StbM_Init_Base_Time(){
    IF_INSTANCE("Valid") {
        return E_OK;
    }

    IF_INSTANCE("InValid") {
        return E_NOT_OK;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_CustIf_StbM_Check_Init_Sync */
int BEFORE_rbl_CustIf_StbM_Check_Init_Sync(){
    REGISTER_CALL("rbl_CustIf_StbM_Check_Init_Sync");

    IF_INSTANCE("Valid") {
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("InValid") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_StbM_Check_Init_Sync */
boolean AFTER_rbl_CustIf_StbM_Check_Init_Sync(boolean cppsm_return_value){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_CustIf_StbM_Check_Init_Sync */
boolean REPLACE_rbl_CustIf_StbM_Check_Init_Sync(){
    IF_INSTANCE("Valid") {
        return TRUE;
    }

    IF_INSTANCE("InValid") {
        return FALSE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_CustIf_StbM_Monitor_Init_Timeout */
int BEFORE_rbl_CustIf_StbM_Monitor_Init_Timeout(){
    REGISTER_CALL("rbl_CustIf_StbM_Monitor_Init_Timeout");

    IF_INSTANCE("Valid") {
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("InValid") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_StbM_Monitor_Init_Timeout */
boolean AFTER_rbl_CustIf_StbM_Monitor_Init_Timeout(boolean cppsm_return_value){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_CustIf_StbM_Monitor_Init_Timeout */
boolean REPLACE_rbl_CustIf_StbM_Monitor_Init_Timeout(){
    IF_INSTANCE("Valid") {
        return TRUE;
    }

    IF_INSTANCE("InValid") {
        return FALSE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_CustIf_StbM_Check_Lost_Sync */
int BEFORE_rbl_CustIf_StbM_Check_Lost_Sync(){
    REGISTER_CALL("rbl_CustIf_StbM_Check_Lost_Sync");

    IF_INSTANCE("Valid") {
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("InValid") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_StbM_Check_Lost_Sync */
boolean AFTER_rbl_CustIf_StbM_Check_Lost_Sync(boolean cppsm_return_value){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_CustIf_StbM_Check_Lost_Sync */
boolean REPLACE_rbl_CustIf_StbM_Check_Lost_Sync(){
    IF_INSTANCE("Valid") {
        return TRUE;
    }

    IF_INSTANCE("InValid") {
        return FALSE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function rbl_CustIf_StbM_Check_TimeLeap */
int BEFORE_rbl_CustIf_StbM_Check_TimeLeap(){
    REGISTER_CALL("rbl_CustIf_StbM_Check_TimeLeap");

    IF_INSTANCE("Valid") {
        return REPLACE_WRAPPER;
    }

    IF_INSTANCE("InValid") {
        return REPLACE_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function rbl_CustIf_StbM_Check_TimeLeap */
boolean AFTER_rbl_CustIf_StbM_Check_TimeLeap(boolean cppsm_return_value){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function rbl_CustIf_StbM_Check_TimeLeap */
boolean REPLACE_rbl_CustIf_StbM_Check_TimeLeap(){
    IF_INSTANCE("Valid") {
        return TRUE;
    }

    IF_INSTANCE("InValid") {
        return FALSE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

#pragma qas cantata ignore off
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
