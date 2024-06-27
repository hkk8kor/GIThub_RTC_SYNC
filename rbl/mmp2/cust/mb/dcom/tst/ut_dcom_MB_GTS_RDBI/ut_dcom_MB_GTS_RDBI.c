/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_MB_GTS_RDBI.c
 *    Author: GDEV1KOR
 *    Generated on: 15-Apr-2024 16:35:46
 *    Generated from: dcom_MB_GTS_RDBI.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "dcom_Lib.h"
#include "dcom_MB_Pub.h"
#include "../../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/dcom_MB_GTS_RDBI.h"
#include "CanTSyn.h"
#include "StbM.h"
#include "Rte_StbM.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern Std_ReturnType ACCESS_FUNCTION_dcom_MB_GTS_RDBI_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader();
extern Std_ReturnType ACCESS_FUNCTION_dcom_MB_GTS_RDBI_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1(const StbM_SyncRecordTableBlockType * syncRecordTableBlock);
extern Std_ReturnType ACCESS_FUNCTION_dcom_MB_GTS_RDBI_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2(const StbM_SyncRecordTableBlockType * syncRecordTableBlock);
Std_ReturnType StbM_GetSyncTimeRecordHead(StbM_SynchronizedTimeBaseType Rte_PDAV0, StbM_SyncRecordTableHeadType * syncRecordTableHead);
void rbl_CustIf_Meas_IMU_X_ST3_PDU_Update(const StbM_SyncRecordTableBlockType * syncRecordTableBlock);
void rbl_TiSync_cloneToPureLocalTime();

/* Global data */
uint8 rbl_dcom_MirrorActvtDbgFrmsAppl_u8[1];
typedef struct dcom_MB_GTS_RDBI_av_struct { dcom_MB_GTS_Measurement_Data_Type_tst * ref_dcom_MB_GTS_Measurement_st; uint8 * ref_dcom_MB_MeasurementDataIndex; boolean * ref_dcom_MB_GTS_Measurement_Received; } dcom_MB_GTS_RDBI_av_struct;
extern dcom_MB_GTS_RDBI_av_struct av_dcom_MB_GTS_RDBI;

/* Expected variables for global data */
uint8 expected_rbl_dcom_MirrorActvtDbgFrmsAppl_u8[1];
typedef struct expected_dcom_MB_GTS_RDBI_av_struct { dcom_MB_GTS_Measurement_Data_Type_tst ref_dcom_MB_GTS_Measurement_st; uint8 ref_dcom_MB_MeasurementDataIndex; boolean ref_dcom_MB_GTS_Measurement_Received; } expected_dcom_MB_GTS_RDBI_av_struct;
expected_dcom_MB_GTS_RDBI_av_struct expected_av_dcom_MB_GTS_RDBI;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received));
    INITIALISE(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st));
    INITIALISE(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex));
    INITIALISE(rbl_dcom_MirrorActvtDbgFrmsAppl_u8);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received), ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received));
    COPY_TO_EXPECTED(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st), ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st));
    COPY_TO_EXPECTED(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex), ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex));
    COPY_TO_EXPECTED(rbl_dcom_MirrorActvtDbgFrmsAppl_u8, expected_rbl_dcom_MirrorActvtDbgFrmsAppl_u8);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_BOOLEAN(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received), ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received));
    CHECK_MEMORY("ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st)", &ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st), &ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st), sizeof(ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st)));
    CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex), ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex));
    CHECK_MEMORY("rbl_dcom_MirrorActvtDbgFrmsAppl_u8", rbl_dcom_MirrorActvtDbgFrmsAppl_u8, expected_rbl_dcom_MirrorActvtDbgFrmsAppl_u8, sizeof(expected_rbl_dcom_MirrorActvtDbgFrmsAppl_u8));
}

/* Prototypes for test functions */
void run_tests();
void ut_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader(int doIt);
void ut_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1(int doIt);
void ut_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2(int doIt);
void ut_dcom_Global_Time_Sync_Measured_Values_0107_ReadData(int doIt);
void ut_dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase(int doIt);
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
    OPEN_LOG("ut_dcom_MB_GTS_RDBI.ctr", false, 100);
    START_SCRIPT("dcom_MB_GTS_RDBI", true);

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
    ut_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader(1);
    ut_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1(1);
    ut_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2(1);
    ut_dcom_Global_Time_Sync_Measured_Values_0107_ReadData(1);
    ut_dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_MB_GTS_RDBI.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader(int doIt){
if (doIt) {

    START_TEST("47832: [MMP2.11]UTC_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47832");

    Std_ReturnType returnValue = E_NOT_OK;
            /* Test steps */
            START_STEP("1_NTS", true);
            {
                /* Set global data */
                initialise_global_data();
                *(av_dcom_MB_GTS_RDBI.ref_dcom_MB_GTS_Measurement_Received) = FALSE;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWFrequency = 0x7f7f7f7f;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWPrescaler = 0x7f7f7f7f;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.Index = 0x7f;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x00;

                /* Set expected values for global data checks */
                initialise_expected_global_data();
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_GTS_Measurement_st).Header.HWFrequency = 0xFFFFFFFF;
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_GTS_Measurement_st).Header.HWPrescaler = 0xFFFFFFFF;
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_GTS_Measurement_st).Header.Index = 0x00;
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x00;
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received)= TRUE;

                /* Expected Call Sequence  */
                EXPECTED_CALLS("StbM_GetSyncTimeRecordHead#stub_StbM_GetSyncTimeRecordHead_TRUE_Valid_Values");

                /* Call SUT */
                returnValue = ACCESS_FUNCTION(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Fill_TimeRecordHeader)();

                /* Test case checks */
                CHECK_U_CHAR(returnValue, E_OK);
                CHECK_BOOLEAN(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received), ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received));
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWFrequency,ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_GTS_Measurement_st).Header.HWFrequency);
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWPrescaler,ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_GTS_Measurement_st).Header.HWPrescaler);
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.Index  ,ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_GTS_Measurement_st).Header.Index);

                END_CALLS();
                END_STEP();
           }

            /* Test steps */
            START_STEP("2_NTS", true);
            {
                /* Set global data */
                *(av_dcom_MB_GTS_RDBI.ref_dcom_MB_GTS_Measurement_Received) = TRUE;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWFrequency = 0x00000000;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWPrescaler = 0x00000000;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.Index = 0x00;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x00;

                /* Set expected values for global data checks */
                initialise_expected_global_data();
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_GTS_Measurement_st).Header.HWFrequency = 0x00;
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_GTS_Measurement_st).Header.HWPrescaler = 0x00;
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_GTS_Measurement_st).Header.Index = 0x00;
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x00;

                /* Expected Call Sequence  */
                EXPECTED_CALLS("StbM_GetSyncTimeRecordHead#stub_StbM_GetSyncTimeRecordHead_TRUE_Null_Values");

                /* Call SUT */
                returnValue = ACCESS_FUNCTION(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Fill_TimeRecordHeader)();

                /* Test case checks */
                CHECK_U_CHAR(returnValue, E_OK);
                CHECK_BOOLEAN(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received), ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received));
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWFrequency,ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_GTS_Measurement_st).Header.HWFrequency);
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWPrescaler ,ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_GTS_Measurement_st).Header.HWPrescaler);
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.Index  ,ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_GTS_Measurement_st).Header.Index);

                END_CALLS();
                END_STEP();
            }

            /* Test steps */
            START_STEP("3_NTS", true);
            {
                /* Test case data declarations */
                returnValue = E_OK;

                /* Set global data */
                *(av_dcom_MB_GTS_RDBI.ref_dcom_MB_GTS_Measurement_Received) = TRUE;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWFrequency = 0x7f7f7f7f;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWPrescaler = 0x7f7f7f7f;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.Index = 0x7f;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x00;

                /* Set expected values for global data checks */
                initialise_expected_global_data();

                /* Expected Call Sequence  */
                EXPECTED_CALLS("StbM_GetSyncTimeRecordHead#stub_StbM_GetSyncTimeRecordHead_FALSE");

                /* Call SUT */
                returnValue = ACCESS_FUNCTION(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Fill_TimeRecordHeader)();

                /* Test case checks */
                CHECK_U_CHAR(returnValue, E_NOT_OK);
                CHECK_BOOLEAN(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received), ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received));
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWFrequency,0x7f7f7f7f);
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWPrescaler ,0x7f7f7f7f);
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.Index  ,0x7f);

                END_CALLS();
                END_STEP();
            }
  END_TEST();
 }}

void ut_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1(int doIt){
if (doIt) {

    START_TEST("47833: [MMP2.11]UTC_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47833");

    Std_ReturnType returnValue = E_NOT_OK;
            /* Test steps */
            START_STEP("1_NTS", true);
            {
                StbM_SyncRecordTableBlockType buff_syncRecordTableBlock;
                const StbM_SyncRecordTableBlockType *syncRecordTableBlock  = &buff_syncRecordTableBlock;
                buff_syncRecordTableBlock.GlbSeconds          = 0x55555555;
                buff_syncRecordTableBlock.GlbNanoSeconds      = 0x55555555;
                buff_syncRecordTableBlock.TimeBaseStatus      = 0x55;
                buff_syncRecordTableBlock.VirtualLocalTimeLow = 0x55555555;
                buff_syncRecordTableBlock.RateDeviation       = 0x5555;
                buff_syncRecordTableBlock.LocSeconds          = 0x55555555;
                buff_syncRecordTableBlock.LocNanoSeconds      = 0x55555555;

                /* Set global data */
                initialise_global_data();
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbSeconds          = 0xFFFFFFFF;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbNanoSeconds      = 0xFFFFFFFF;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.TimeBaseStatus      = 0xFF;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.VirtualLocalTimeLow = 0xFFFFFFFF;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.RateDeviation       = 0xFFFF;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocSeconds          = 0xFFFFFFFF;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocNanoSeconds      = 0xFFFFFFFF;

                /* Set expected values for global data checks */
                initialise_expected_global_data();
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbSeconds          = 0x55555555;
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbNanoSeconds      = 0x55555555;
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.TimeBaseStatus      = 0x55;
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.VirtualLocalTimeLow = 0x55555555;
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.RateDeviation       = 0x5555;
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocSeconds          = 0x55555555;
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocNanoSeconds      = 0x55555555;

                /* Expected Call Sequence  */
                EXPECTED_CALLS("");

                /* Call SUT */
                returnValue = ACCESS_FUNCTION(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1)(syncRecordTableBlock);
                /* Test case checks */
                CHECK_U_CHAR(returnValue, E_OK);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbSeconds,ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbSeconds);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbNanoSeconds,ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbNanoSeconds);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.TimeBaseStatus,ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.TimeBaseStatus);
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.VirtualLocalTimeLow,ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.VirtualLocalTimeLow);
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.RateDeviation,ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.RateDeviation);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocSeconds,ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocSeconds);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocNanoSeconds,ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocNanoSeconds);

                END_CALLS();
                END_STEP();
       }

            /* Test steps */
            START_STEP("2_NTS", true);
            {
                StbM_SyncRecordTableBlockType buff_syncRecordTableBlock;
                const StbM_SyncRecordTableBlockType *syncRecordTableBlock  = NULL_PTR;

                /* Test case data declarations */
                returnValue = E_OK;

                /* Set global data */
                initialise_global_data();
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbSeconds          = 0x7F7F7F7F;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbNanoSeconds      = 0x7F7F7F7F;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.TimeBaseStatus      = 0xFF;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.VirtualLocalTimeLow = 0x7F7F7F7F;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.RateDeviation       = 0x7F7F;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocSeconds          = 0x7F7F7F7F;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocNanoSeconds      = 0x7F7F7F7F;

                /* Set expected values for global data checks */
                initialise_expected_global_data();

                /* Expected Call Sequence  */
                EXPECTED_CALLS("");

                /* Call SUT */
                returnValue = ACCESS_FUNCTION(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1)(syncRecordTableBlock);

                /* Test case checks */
                CHECK_U_CHAR(returnValue, E_NOT_OK);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbSeconds,0x7F7F7F7F);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbNanoSeconds,0x7F7F7F7F);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.TimeBaseStatus,0xFF);
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.VirtualLocalTimeLow,0x7F7F7F7F);
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.RateDeviation,0x7F7F);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocSeconds,0x7F7F7F7F);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocNanoSeconds,0x7F7F7F7F);

                END_CALLS();
                END_STEP();
    }
  END_TEST();
  }
}

void ut_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2(int doIt){
if (doIt) {

    START_TEST("47834: [MMP2.11]UTC_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47834");

    Std_ReturnType returnValue = E_NOT_OK;
            /* Test steps */
            START_STEP("1_NTS", true);
            {
              uint8 j = ACCESS_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_MeasurementDataIndex);
              j=2;
              StbM_SyncRecordTableBlockType buff_syncRecordTableBlock;
              const StbM_SyncRecordTableBlockType *syncRecordTableBlock  = &buff_syncRecordTableBlock;
              buff_syncRecordTableBlock.GlbSeconds = 0XFFFFFFFF;
              buff_syncRecordTableBlock.LocSeconds = 0XFFFFFFFF;
              buff_syncRecordTableBlock.GlbNanoSeconds = 0XFFFFFFFF;
              buff_syncRecordTableBlock.TimeBaseStatus = 0XFF;
              buff_syncRecordTableBlock.VirtualLocalTimeLow = 0XFFFFFFFF;
              buff_syncRecordTableBlock.RateDeviation = 0xffff;
              buff_syncRecordTableBlock.LocNanoSeconds =0XFFFFFFFF;
              uint8 i = j - 1;

             /* Set global data */
             initialise_global_data();
             ACCESS_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_MeasurementDataIndex)= 2;
             ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GLSecondsLo  = 0X00;
             ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[0] = 0x00;
             ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[1] = 0x00;
             ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[2] = 0x00;
             ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].TimeBaseStatus = 0x00;
             ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].VirtualLocalTimeLow = 0x00;
             ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].RateDeviation = 0x00;
             ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[0] = 0x00;
             ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[1] = 0x00;
             ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[2] = 0x00;

             /* Set expected values for global data checks */
             initialise_expected_global_data();
             ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_MeasurementDataIndex)= 2;
             ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GLSecondsLo  = 0XFF;
             ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[0] = 0xFF;
             ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[1] = 0xFF;
             ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[2] = 0xFF;
             ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].TimeBaseStatus = 0xFF;
             ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].VirtualLocalTimeLow = 0XFFFFFFFF;
             ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].RateDeviation = 0xFFFF;
             ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[0] = 0xFF;
             ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[1] = 0xFF;
             ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[2] = 0xFF;
             ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_MeasurementDataIndex)= 0x02;

                /* Expected Call Sequence  */
                EXPECTED_CALLS("");

                /* Call SUT */
                returnValue = ACCESS_FUNCTION(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2)(syncRecordTableBlock);

                /* Test case checks */
                CHECK_U_CHAR(returnValue, E_OK);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex),ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex));
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GLSecondsLo , ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GLSecondsLo);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[0], ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[0]);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[1], ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[1]);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[2], ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[2]);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].TimeBaseStatus, ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].TimeBaseStatus);
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].VirtualLocalTimeLow, ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].VirtualLocalTimeLow);
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].RateDeviation, ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].RateDeviation);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[0], ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[0]);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[1], ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[1]);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[2], ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[2]);

                END_CALLS();
                END_STEP();
             }

            /* Test steps */
            START_STEP("2_NTS", true);
            {
                uint8 j = ACCESS_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_MeasurementDataIndex);
                j=5;
                StbM_SyncRecordTableBlockType buff_syncRecordTableBlock;
                const StbM_SyncRecordTableBlockType *syncRecordTableBlock  = NULL_PTR;
                uint8 i = j - 1;

                /* Test case data declarations */
                  returnValue = E_OK;

                /* Set global data */
                initialise_global_data();
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_MeasurementDataIndex)= 5;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GLSecondsLo  = 0X7F;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[0] = 0X7F;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[1] = 0X7F;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[2] = 0X7F;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].TimeBaseStatus = 0XFF;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].VirtualLocalTimeLow = 0X7F;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].RateDeviation = 0X7F;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[0] = 0X7F;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[1] = 0X7F;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[2] = 0X7F;

                /* Set expected values for global data checks */
                initialise_expected_global_data();
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI,dcom_MB_MeasurementDataIndex)= 0x05;

                /* Expected Call Sequence  */
                EXPECTED_CALLS("");

                /* Call SUT */
                returnValue = ACCESS_FUNCTION(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2)(syncRecordTableBlock);

                /* Test case checks */
                CHECK_U_CHAR(returnValue, E_NOT_OK);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex),ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex));
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GLSecondsLo , 0x7F);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[0], 0x7F);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[1], 0x7F);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[2], 0x7F);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].TimeBaseStatus, 0xFF);
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].VirtualLocalTimeLow, 0x7F);
                CHECK_U_INT(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].RateDeviation, 0x7F);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[0], 0x7F);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[1], 0x7F);
                CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[2], 0x7F);

              END_CALLS();
              END_STEP();
        }
  END_TEST();
  }
}

void ut_dcom_Global_Time_Sync_Measured_Values_0107_ReadData(int doIt){
if (doIt) {

    START_TEST("47831: [MMP2.11]UTC_dcom_Global_Time_Sync_Measured_Values_0107_ReadData",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47831");

    Std_ReturnType returnValue = E_NOT_OK;
            /* Test steps */
            START_STEP("1_NTS", true);
            {
              /* Test case data declarations */
               uint8 i, Buff_Data[204];
               uint8 * Data = Buff_Data;

               /* Set global data */
                initialise_global_data();
                *(av_dcom_MB_GTS_RDBI.ref_dcom_MB_GTS_Measurement_Received) = FALSE;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.MeasurementDataStructureType = 0xFF;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWFrequency = 0xF3F2F1F0;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWPrescaler = 0xF1F0;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.Index = 0x00;

                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbSeconds          = 0xF3F2F1F0;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbNanoSeconds      = 0xF3F2F1F0;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.TimeBaseStatus      = 0xFF;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.VirtualLocalTimeLow = 0xF3F2F1F0;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.RateDeviation       = 0xFFFF;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocSeconds          = 0xF3F2F1F0;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocNanoSeconds      = 0xF3F2F1F0;


                for(i=0;i<11;i++)
                {
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GLSecondsLo  = 0xFF;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[0] = 0xFF;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[1] = 0xFF;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[2] = 0xFF;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].TimeBaseStatus = 0xFF;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].VirtualLocalTimeLow = 0xF3F2F1F0;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].RateDeviation = 0xFFFF;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[0] = 0xFF;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[1] = 0xFF;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[2] = 0xFF;

                }



                /* Set expected values for global data checks */
                initialise_expected_global_data();
                {
                    /* Expected Call Sequence  */
                    EXPECTED_CALLS("");

                    /* Call SUT */
                    returnValue = dcom_Global_Time_Sync_Measured_Values_0107_ReadData(Data);

                    /* Test case checks */
                    CHECK_U_CHAR(returnValue, E_OK);
                    CHECK_BOOLEAN(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received), ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received));

                    /* Header Data */
                    CHECK_U_CHAR(Data[0],DCOM_MB_GTS_ADAS_TIME_DOMAIN);
                    CHECK_U_CHAR(Data[1], 0xFF);
                    CHECK_U_CHAR(Data[2], 0xF3);
                    CHECK_U_CHAR(Data[3], 0xF2);
                    CHECK_U_CHAR(Data[4], 0xF1);
                    CHECK_U_CHAR(Data[5], 0xF0);
                    CHECK_U_CHAR(Data[6], 0xF1);
                    CHECK_U_CHAR(Data[7], 0xF0);
                    CHECK_U_CHAR(Data[8], DCOM_ECU_EXTRACT_MAJOR_VERSION);
                    CHECK_U_CHAR(Data[9], DCOM_ECU_EXTRACT_MINOR_VERSION);
                    CHECK_U_CHAR(Data[10], DCOM_ECU_EXTRACT_PATCH_VERSION);
                    CHECK_U_CHAR(Data[11], STBM_SOFTWARE_MAJOR_VERSION);
                    CHECK_U_CHAR(Data[12], STBM_SOFTWARE_MINOR_VERSION);
                    CHECK_U_CHAR(Data[13], STBM_SOFTWARE_PATCH_VERSION);
                    CHECK_U_CHAR(Data[14], DCOM_MB_GTS_MEASUREMENT_ETHTSYN_MAJOR);
                    CHECK_U_CHAR(Data[15], DCOM_MB_GTS_MEASUREMENT_ETHTSYN_MINOR);
                    CHECK_U_CHAR(Data[16], DCOM_MB_GTS_MEASUREMENT_ETHTSYN_PATCH);
                    CHECK_U_CHAR(Data[17], CANTSYN_SW_MAJOR_VERSION);
                    CHECK_U_CHAR(Data[18], CANTSYN_SW_MINOR_VERSION);
                    CHECK_U_CHAR(Data[19], CANTSYN_SW_PATCH_VERSION);
                    CHECK_U_CHAR(Data[20], DCOM_MB_GTS_MEASUREMENT_FRTSYN_MAJOR);
                    CHECK_U_CHAR(Data[21], DCOM_MB_GTS_MEASUREMENT_FRTSYN_MINOR);
                    CHECK_U_CHAR(Data[22], DCOM_MB_GTS_MEASUREMENT_FRTSYN_PATCH);
                    CHECK_U_CHAR(Data[23], DCOM_MB_GTS_MEASUREMENT_DEFAULT_INDEX);

                    /* Data Section - Measurement Type - 1 */
                    CHECK_U_CHAR(Data[24], 0xF3);
                    CHECK_U_CHAR(Data[25], 0xF2);
                    CHECK_U_CHAR(Data[26], 0xF1);
                    CHECK_U_CHAR(Data[27], 0xF0);
                    CHECK_U_CHAR(Data[28], 0xF3);
                    CHECK_U_CHAR(Data[29], 0xF2);
                    CHECK_U_CHAR(Data[30], 0xF1);
                    CHECK_U_CHAR(Data[31], 0xF0);
                    CHECK_U_CHAR(Data[32], 0xFF);
                    CHECK_U_CHAR(Data[33], 0xF3);
                    CHECK_U_CHAR(Data[34], 0xF2);
                    CHECK_U_CHAR(Data[35], 0xF1);
                    CHECK_U_CHAR(Data[36], 0xF0);
                    CHECK_U_CHAR(Data[37], 0xFF);
                    CHECK_U_CHAR(Data[38], 0xFF);
                    CHECK_U_CHAR(Data[39], 0xF3);
                    CHECK_U_CHAR(Data[40], 0xF2);
                    CHECK_U_CHAR(Data[41], 0xF1);
                    CHECK_U_CHAR(Data[42], 0xF0);
                    CHECK_U_CHAR(Data[43], 0xF3);
                    CHECK_U_CHAR(Data[44], 0xF2);
                    CHECK_U_CHAR(Data[45], 0xF1);
                    CHECK_U_CHAR(Data[46], 0xF0);

                    /* Data Section - Measurement Type - 2 */
                    CHECK_U_CHAR(Data[47], 0xFF);
                    CHECK_U_CHAR(Data[48], 0xFF);
                    CHECK_U_CHAR(Data[49], 0xFF);
                    CHECK_U_CHAR(Data[50], 0xFF);
                    CHECK_U_CHAR(Data[51], 0xFF);
                    CHECK_U_CHAR(Data[52], 0xF3);
                    CHECK_U_CHAR(Data[53], 0xF2);
                    CHECK_U_CHAR(Data[54], 0xF1);
                    CHECK_U_CHAR(Data[55], 0xF0);
                    CHECK_U_CHAR(Data[56], 0xFF);
                    CHECK_U_CHAR(Data[57], 0xFF);
                    CHECK_U_CHAR(Data[58], 0xFF);
                    CHECK_U_CHAR(Data[59], 0xFF);
                    CHECK_U_CHAR(Data[60], 0xFF);

                    CHECK_U_CHAR(Data[61], 0xFF);
                    CHECK_U_CHAR(Data[62], 0xFF);
                    CHECK_U_CHAR(Data[63], 0xFF);
                    CHECK_U_CHAR(Data[64], 0xFF);
                    CHECK_U_CHAR(Data[65], 0xFF);
                    CHECK_U_CHAR(Data[66], 0xF3);
                    CHECK_U_CHAR(Data[67], 0xF2);
                    CHECK_U_CHAR(Data[68], 0xF1);
                    CHECK_U_CHAR(Data[69], 0xF0);
                    CHECK_U_CHAR(Data[70], 0xFF);
                    CHECK_U_CHAR(Data[71], 0xFF);
                    CHECK_U_CHAR(Data[72], 0xFF);
                    CHECK_U_CHAR(Data[73], 0xFF);
                    CHECK_U_CHAR(Data[74], 0xFF);

                    CHECK_U_CHAR(Data[75], 0xFF);
                    CHECK_U_CHAR(Data[76], 0xFF);
                    CHECK_U_CHAR(Data[77], 0xFF);
                    CHECK_U_CHAR(Data[78], 0xFF);
                    CHECK_U_CHAR(Data[79], 0xFF);
                    CHECK_U_CHAR(Data[80], 0xF3);
                    CHECK_U_CHAR(Data[81], 0xF2);
                    CHECK_U_CHAR(Data[82], 0xF1);
                    CHECK_U_CHAR(Data[83], 0xF0);
                    CHECK_U_CHAR(Data[84], 0xFF);
                    CHECK_U_CHAR(Data[85], 0xFF);
                    CHECK_U_CHAR(Data[86], 0xFF);
                    CHECK_U_CHAR(Data[87], 0xFF);
                    CHECK_U_CHAR(Data[88], 0xFF);

                    CHECK_U_CHAR(Data[89], 0xFF);
                    CHECK_U_CHAR(Data[90], 0xFF);
                    CHECK_U_CHAR(Data[91], 0xFF);
                    CHECK_U_CHAR(Data[92], 0xFF);
                    CHECK_U_CHAR(Data[93], 0xFF);
                    CHECK_U_CHAR(Data[94], 0xF3);
                    CHECK_U_CHAR(Data[95], 0xF2);
                    CHECK_U_CHAR(Data[96], 0xF1);
                    CHECK_U_CHAR(Data[97], 0xF0);
                    CHECK_U_CHAR(Data[98], 0xFF);
                    CHECK_U_CHAR(Data[99], 0xFF);
                    CHECK_U_CHAR(Data[100], 0xFF);
                    CHECK_U_CHAR(Data[101], 0xFF);
                    CHECK_U_CHAR(Data[102], 0xFF);

                    CHECK_U_CHAR(Data[103], 0xFF);
                    CHECK_U_CHAR(Data[104], 0xFF);
                    CHECK_U_CHAR(Data[105], 0xFF);
                    CHECK_U_CHAR(Data[106], 0xFF);
                    CHECK_U_CHAR(Data[107], 0xFF);
                    CHECK_U_CHAR(Data[108], 0xF3);
                    CHECK_U_CHAR(Data[109], 0xF2);
                    CHECK_U_CHAR(Data[110], 0xF1);
                    CHECK_U_CHAR(Data[111], 0xF0);
                    CHECK_U_CHAR(Data[112], 0xFF);
                    CHECK_U_CHAR(Data[113], 0xFF);
                    CHECK_U_CHAR(Data[114], 0xFF);
                    CHECK_U_CHAR(Data[115], 0xFF);
                    CHECK_U_CHAR(Data[116], 0xFF);

                    CHECK_U_CHAR(Data[117], 0xFF);
                    CHECK_U_CHAR(Data[118], 0xFF);
                    CHECK_U_CHAR(Data[119], 0xFF);
                    CHECK_U_CHAR(Data[120], 0xFF);
                    CHECK_U_CHAR(Data[121], 0xFF);
                    CHECK_U_CHAR(Data[122], 0xF3);
                    CHECK_U_CHAR(Data[123], 0xF2);
                    CHECK_U_CHAR(Data[124], 0xF1);
                    CHECK_U_CHAR(Data[125], 0xF0);
                    CHECK_U_CHAR(Data[126], 0xFF);
                    CHECK_U_CHAR(Data[127], 0xFF);
                    CHECK_U_CHAR(Data[128], 0xFF);
                    CHECK_U_CHAR(Data[129], 0xFF);
                    CHECK_U_CHAR(Data[130], 0xFF);

                    CHECK_U_CHAR(Data[131], 0xFF);
                    CHECK_U_CHAR(Data[132], 0xFF);
                    CHECK_U_CHAR(Data[133], 0xFF);
                    CHECK_U_CHAR(Data[134], 0xFF);
                    CHECK_U_CHAR(Data[135], 0xFF);
                    CHECK_U_CHAR(Data[136], 0xF3);
                    CHECK_U_CHAR(Data[137], 0xF2);
                    CHECK_U_CHAR(Data[138], 0xF1);
                    CHECK_U_CHAR(Data[139], 0xF0);
                    CHECK_U_CHAR(Data[140], 0xFF);
                    CHECK_U_CHAR(Data[141], 0xFF);
                    CHECK_U_CHAR(Data[142], 0xFF);
                    CHECK_U_CHAR(Data[143], 0xFF);
                    CHECK_U_CHAR(Data[144], 0xFF);

                    CHECK_U_CHAR(Data[145], 0xFF);
                    CHECK_U_CHAR(Data[146], 0xFF);
                    CHECK_U_CHAR(Data[147], 0xFF);
                    CHECK_U_CHAR(Data[148], 0xFF);
                    CHECK_U_CHAR(Data[149], 0xFF);
                    CHECK_U_CHAR(Data[150], 0xF3);
                    CHECK_U_CHAR(Data[151], 0xF2);
                    CHECK_U_CHAR(Data[152], 0xF1);
                    CHECK_U_CHAR(Data[153], 0xF0);
                    CHECK_U_CHAR(Data[154], 0xFF);
                    CHECK_U_CHAR(Data[155], 0xFF);
                    CHECK_U_CHAR(Data[156], 0xFF);
                    CHECK_U_CHAR(Data[157], 0xFF);
                    CHECK_U_CHAR(Data[158], 0xFF);

                    CHECK_U_CHAR(Data[159], 0xFF);
                    CHECK_U_CHAR(Data[160], 0xFF);
                    CHECK_U_CHAR(Data[161], 0xFF);
                    CHECK_U_CHAR(Data[162], 0xFF);
                    CHECK_U_CHAR(Data[163], 0xFF);
                    CHECK_U_CHAR(Data[164], 0xF3);
                    CHECK_U_CHAR(Data[165], 0xF2);
                    CHECK_U_CHAR(Data[166], 0xF1);
                    CHECK_U_CHAR(Data[167], 0xF0);
                    CHECK_U_CHAR(Data[168], 0xFF);
                    CHECK_U_CHAR(Data[169], 0xFF);
                    CHECK_U_CHAR(Data[170], 0xFF);
                    CHECK_U_CHAR(Data[171], 0xFF);
                    CHECK_U_CHAR(Data[172], 0xFF);

                    CHECK_U_CHAR(Data[173], 0xFF);
                    CHECK_U_CHAR(Data[174], 0xFF);
                    CHECK_U_CHAR(Data[175], 0xFF);
                    CHECK_U_CHAR(Data[176], 0xFF);
                    CHECK_U_CHAR(Data[177], 0xFF);
                    CHECK_U_CHAR(Data[178], 0xF3);
                    CHECK_U_CHAR(Data[179], 0xF2);
                    CHECK_U_CHAR(Data[180], 0xF1);
                    CHECK_U_CHAR(Data[181], 0xF0);
                    CHECK_U_CHAR(Data[182], 0xFF);
                    CHECK_U_CHAR(Data[183], 0xFF);
                    CHECK_U_CHAR(Data[184], 0xFF);
                    CHECK_U_CHAR(Data[185], 0xFF);
                    CHECK_U_CHAR(Data[186], 0xFF);


                    CHECK_U_CHAR(Data[187], 0xFF);
                    CHECK_U_CHAR(Data[188], 0xFF);
                    CHECK_U_CHAR(Data[189], 0xFF);
                    CHECK_U_CHAR(Data[190], 0xFF);
                    CHECK_U_CHAR(Data[191], 0xFF);
                    CHECK_U_CHAR(Data[192], 0xF3);
                    CHECK_U_CHAR(Data[193], 0xF2);
                    CHECK_U_CHAR(Data[194], 0xF1);
                    CHECK_U_CHAR(Data[195], 0xF0);
                    CHECK_U_CHAR(Data[196], 0xFF);
                    CHECK_U_CHAR(Data[197], 0xFF);
                    CHECK_U_CHAR(Data[198], 0xFF);
                    CHECK_U_CHAR(Data[199], 0xFF);
                    CHECK_U_CHAR(Data[200], 0xFF);

                    /* Checks on global data */
                   check_global_data();
                   END_CALLS();
                   END_STEP();
                    }
                    }

            /* Test steps */
            START_STEP("2_NTS", true);
            {
                /* Test case data declarations */
                 uint8 i, Buff_Data[204];
                 uint8 * Data = Buff_Data;

                 /* Set global data */
                 initialise_global_data();
                 *(av_dcom_MB_GTS_RDBI.ref_dcom_MB_GTS_Measurement_Received) = TRUE;
                 ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.MeasurementDataStructureType = 0xFF;
                 ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWFrequency = 0xFFFFFFFF;
                 ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.HWPrescaler = 0xFFFF;
                 ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).Header.Index = 0x55;

                 ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbSeconds           = 0x00000000;
                 ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.GlbNanoSeconds      = 0x00000000;
                 ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.TimeBaseStatus      = 0x00;
                 ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.VirtualLocalTimeLow = 0xFFFFFFFF;
                 ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.RateDeviation       = 0x0000;
                 ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocSeconds          = 0x00000000;
                 ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord1.LocNanoSeconds      = 0x00000000;

                 for(i =0;i<11;i++)
                 {
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GLSecondsLo  = 0x00;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[0] = 0x00;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[1] = 0x00;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].GNanoSecondsPart[2] = 0x00;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].TimeBaseStatus = 0x00;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].VirtualLocalTimeLow = 0xFFFFFFFF;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].RateDeviation = 0x0000;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[0] = 0x00;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[1] = 0x00;
                    ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_st).TimeRecord2[i].LNanoSecondsPart[2] = 0x00;
                 }

                 /* Set expected values for global data checks */
                initialise_expected_global_data();
                {
                    /* Expected Call Sequence  */
                    EXPECTED_CALLS("");

                    /* Call SUT */
                    returnValue = dcom_Global_Time_Sync_Measured_Values_0107_ReadData(Data);

                    /* Test case checks */
                    CHECK_U_CHAR(returnValue, E_OK);
                    CHECK_BOOLEAN(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received), ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received));

                    /* Header Data */
                    CHECK_U_CHAR(Data[0],DCOM_MB_GTS_ADAS_TIME_DOMAIN);
                    CHECK_U_CHAR(Data[1], 0xFF);
                    CHECK_U_CHAR(Data[2], 0xFF);
                    CHECK_U_CHAR(Data[3], 0xFF);
                    CHECK_U_CHAR(Data[4], 0xFF);
                    CHECK_U_CHAR(Data[5], 0xFF);
                    CHECK_U_CHAR(Data[6], 0xFF);
                    CHECK_U_CHAR(Data[7], 0xFF);
                    CHECK_U_CHAR(Data[8], DCOM_ECU_EXTRACT_MAJOR_VERSION);
                    CHECK_U_CHAR(Data[9], DCOM_ECU_EXTRACT_MINOR_VERSION);
                    CHECK_U_CHAR(Data[10], DCOM_ECU_EXTRACT_PATCH_VERSION);
                    CHECK_U_CHAR(Data[11], STBM_SOFTWARE_MAJOR_VERSION);
                    CHECK_U_CHAR(Data[12], STBM_SOFTWARE_MINOR_VERSION);
                    CHECK_U_CHAR(Data[13], STBM_SOFTWARE_PATCH_VERSION);
                    CHECK_U_CHAR(Data[14], DCOM_MB_GTS_MEASUREMENT_ETHTSYN_MAJOR);
                    CHECK_U_CHAR(Data[15], DCOM_MB_GTS_MEASUREMENT_ETHTSYN_MINOR);
                    CHECK_U_CHAR(Data[16], DCOM_MB_GTS_MEASUREMENT_ETHTSYN_PATCH);
                    CHECK_U_CHAR(Data[17], CANTSYN_SW_MAJOR_VERSION);
                    CHECK_U_CHAR(Data[18], CANTSYN_SW_MINOR_VERSION);
                    CHECK_U_CHAR(Data[19], CANTSYN_SW_PATCH_VERSION);
                    CHECK_U_CHAR(Data[20], DCOM_MB_GTS_MEASUREMENT_FRTSYN_MAJOR);
                    CHECK_U_CHAR(Data[21], DCOM_MB_GTS_MEASUREMENT_FRTSYN_MINOR);
                    CHECK_U_CHAR(Data[22], DCOM_MB_GTS_MEASUREMENT_FRTSYN_PATCH);
                    CHECK_U_CHAR(Data[23], 0x55);

                    /* Data Section - Measurement Type - 1 */
                    CHECK_U_CHAR(Data[24], 0x00);
                    CHECK_U_CHAR(Data[25], 0x00);
                    CHECK_U_CHAR(Data[26], 0x00);
                    CHECK_U_CHAR(Data[27], 0x00);
                    CHECK_U_CHAR(Data[28], 0x00);
                    CHECK_U_CHAR(Data[29], 0x00);
                    CHECK_U_CHAR(Data[30], 0x00);
                    CHECK_U_CHAR(Data[31], 0x00);
                    CHECK_U_CHAR(Data[32], 0x00);
                    CHECK_U_CHAR(Data[33], 0xFF);
                    CHECK_U_CHAR(Data[34], 0xFF);
                    CHECK_U_CHAR(Data[35], 0xFF);
                    CHECK_U_CHAR(Data[36], 0xFF);
                    CHECK_U_CHAR(Data[37], 0x00);
                    CHECK_U_CHAR(Data[38], 0x00);
                    CHECK_U_CHAR(Data[39], 0x00);
                    CHECK_U_CHAR(Data[40], 0x00);
                    CHECK_U_CHAR(Data[41], 0x00);
                    CHECK_U_CHAR(Data[42], 0x00);
                    CHECK_U_CHAR(Data[43], 0x00);
                    CHECK_U_CHAR(Data[44], 0x00);
                    CHECK_U_CHAR(Data[45], 0x00);
                    CHECK_U_CHAR(Data[46], 0x00);

                    /* Data Section - Measurement Type - 2 */
                    CHECK_U_CHAR(Data[47], 0x00);
                    CHECK_U_CHAR(Data[48], 0x00);
                    CHECK_U_CHAR(Data[49], 0x00);
                    CHECK_U_CHAR(Data[50], 0x00);
                    CHECK_U_CHAR(Data[51], 0x00);
                    CHECK_U_CHAR(Data[52], 0xFF);
                    CHECK_U_CHAR(Data[53], 0xFF);
                    CHECK_U_CHAR(Data[54], 0xFF);
                    CHECK_U_CHAR(Data[55], 0xFF);
                    CHECK_U_CHAR(Data[56], 0x00);
                    CHECK_U_CHAR(Data[57], 0x00);
                    CHECK_U_CHAR(Data[58], 0x00);
                    CHECK_U_CHAR(Data[59], 0x00);
                    CHECK_U_CHAR(Data[60], 0x00);

                    CHECK_U_CHAR(Data[61], 0x00);
                    CHECK_U_CHAR(Data[62], 0x00);
                    CHECK_U_CHAR(Data[63], 0x00);
                    CHECK_U_CHAR(Data[64], 0x00);
                    CHECK_U_CHAR(Data[65], 0x00);
                    CHECK_U_CHAR(Data[66], 0xFF);
                    CHECK_U_CHAR(Data[67], 0xFF);
                    CHECK_U_CHAR(Data[68], 0xFF);
                    CHECK_U_CHAR(Data[69], 0xFF);
                    CHECK_U_CHAR(Data[70], 0x00);
                    CHECK_U_CHAR(Data[71], 0x00);
                    CHECK_U_CHAR(Data[72], 0x00);
                    CHECK_U_CHAR(Data[73], 0x00);
                    CHECK_U_CHAR(Data[74], 0x00);

                    CHECK_U_CHAR(Data[75], 0x00);
                    CHECK_U_CHAR(Data[76], 0x00);
                    CHECK_U_CHAR(Data[77], 0x00);
                    CHECK_U_CHAR(Data[78], 0x00);
                    CHECK_U_CHAR(Data[79], 0x00);
                    CHECK_U_CHAR(Data[80], 0xFF);
                    CHECK_U_CHAR(Data[81], 0xFF);
                    CHECK_U_CHAR(Data[82], 0xFF);
                    CHECK_U_CHAR(Data[83], 0xFF);
                    CHECK_U_CHAR(Data[84], 0x00);
                    CHECK_U_CHAR(Data[85], 0x00);
                    CHECK_U_CHAR(Data[86], 0x00);
                    CHECK_U_CHAR(Data[87], 0x00);
                    CHECK_U_CHAR(Data[88], 0x00);

                    CHECK_U_CHAR(Data[89], 0x00);
                    CHECK_U_CHAR(Data[90], 0x00);
                    CHECK_U_CHAR(Data[91], 0x00);
                    CHECK_U_CHAR(Data[92], 0x00);
                    CHECK_U_CHAR(Data[93], 0x00);
                    CHECK_U_CHAR(Data[94], 0xFF);
                    CHECK_U_CHAR(Data[95], 0xFF);
                    CHECK_U_CHAR(Data[96], 0xFF);
                    CHECK_U_CHAR(Data[97], 0xFF);
                    CHECK_U_CHAR(Data[98], 0x00);
                    CHECK_U_CHAR(Data[99], 0x00);
                    CHECK_U_CHAR(Data[100], 0x00);
                    CHECK_U_CHAR(Data[101], 0x00);
                    CHECK_U_CHAR(Data[102], 0x00);

                    CHECK_U_CHAR(Data[103], 0x00);
                    CHECK_U_CHAR(Data[104], 0x00);
                    CHECK_U_CHAR(Data[105], 0x00);
                    CHECK_U_CHAR(Data[106], 0x00);
                    CHECK_U_CHAR(Data[107], 0x00);
                    CHECK_U_CHAR(Data[108], 0xFF);
                    CHECK_U_CHAR(Data[109], 0xFF);
                    CHECK_U_CHAR(Data[110], 0xFF);
                    CHECK_U_CHAR(Data[111], 0xFF);
                    CHECK_U_CHAR(Data[112], 0x00);
                    CHECK_U_CHAR(Data[113], 0x00);
                    CHECK_U_CHAR(Data[114], 0x00);
                    CHECK_U_CHAR(Data[115], 0x00);
                    CHECK_U_CHAR(Data[116], 0x00);

                    CHECK_U_CHAR(Data[117], 0x00);
                    CHECK_U_CHAR(Data[118], 0x00);
                    CHECK_U_CHAR(Data[119], 0x00);
                    CHECK_U_CHAR(Data[120], 0x00);
                    CHECK_U_CHAR(Data[121], 0x00);
                    CHECK_U_CHAR(Data[122], 0xFF);
                    CHECK_U_CHAR(Data[123], 0xFF);
                    CHECK_U_CHAR(Data[124], 0xFF);
                    CHECK_U_CHAR(Data[125], 0xFF);
                    CHECK_U_CHAR(Data[126], 0x00);
                    CHECK_U_CHAR(Data[127], 0x00);
                    CHECK_U_CHAR(Data[128], 0x00);
                    CHECK_U_CHAR(Data[129], 0x00);
                    CHECK_U_CHAR(Data[130], 0x00);

                    CHECK_U_CHAR(Data[131], 0x00);
                    CHECK_U_CHAR(Data[132], 0x00);
                    CHECK_U_CHAR(Data[133], 0x00);
                    CHECK_U_CHAR(Data[134], 0x00);
                    CHECK_U_CHAR(Data[135], 0x00);
                    CHECK_U_CHAR(Data[136], 0xFF);
                    CHECK_U_CHAR(Data[137], 0xFF);
                    CHECK_U_CHAR(Data[138], 0xFF);
                    CHECK_U_CHAR(Data[139], 0xFF);
                    CHECK_U_CHAR(Data[140], 0x00);
                    CHECK_U_CHAR(Data[141], 0x00);
                    CHECK_U_CHAR(Data[142], 0x00);
                    CHECK_U_CHAR(Data[143], 0x00);
                    CHECK_U_CHAR(Data[144], 0x00);

                    CHECK_U_CHAR(Data[145], 0x00);
                    CHECK_U_CHAR(Data[146], 0x00);
                    CHECK_U_CHAR(Data[147], 0x00);
                    CHECK_U_CHAR(Data[148], 0x00);
                    CHECK_U_CHAR(Data[149], 0x00);
                    CHECK_U_CHAR(Data[150], 0xFF);
                    CHECK_U_CHAR(Data[151], 0xFF);
                    CHECK_U_CHAR(Data[152], 0xFF);
                    CHECK_U_CHAR(Data[153], 0xFF);
                    CHECK_U_CHAR(Data[154], 0x00);
                    CHECK_U_CHAR(Data[155], 0x00);
                    CHECK_U_CHAR(Data[156], 0x00);
                    CHECK_U_CHAR(Data[157], 0x00);
                    CHECK_U_CHAR(Data[158], 0x00);

                    CHECK_U_CHAR(Data[159], 0x00);
                    CHECK_U_CHAR(Data[160], 0x00);
                    CHECK_U_CHAR(Data[161], 0x00);
                    CHECK_U_CHAR(Data[162], 0x00);
                    CHECK_U_CHAR(Data[163], 0x00);
                    CHECK_U_CHAR(Data[164], 0xFF);
                    CHECK_U_CHAR(Data[165], 0xFF);
                    CHECK_U_CHAR(Data[166], 0xFF);
                    CHECK_U_CHAR(Data[167], 0xFF);
                    CHECK_U_CHAR(Data[168], 0x00);
                    CHECK_U_CHAR(Data[169], 0x00);
                    CHECK_U_CHAR(Data[170], 0x00);
                    CHECK_U_CHAR(Data[171], 0x00);
                    CHECK_U_CHAR(Data[172], 0x00);

                    CHECK_U_CHAR(Data[173], 0x00);
                    CHECK_U_CHAR(Data[174], 0x00);
                    CHECK_U_CHAR(Data[175], 0x00);
                    CHECK_U_CHAR(Data[176], 0x00);
                    CHECK_U_CHAR(Data[177], 0x00);
                    CHECK_U_CHAR(Data[178], 0xFF);
                    CHECK_U_CHAR(Data[179], 0xFF);
                    CHECK_U_CHAR(Data[180], 0xFF);
                    CHECK_U_CHAR(Data[181], 0xFF);
                    CHECK_U_CHAR(Data[182], 0x00);
                    CHECK_U_CHAR(Data[183], 0x00);
                    CHECK_U_CHAR(Data[184], 0x00);
                    CHECK_U_CHAR(Data[185], 0x00);
                    CHECK_U_CHAR(Data[186], 0x00);

                    CHECK_U_CHAR(Data[187], 0x00);
                    CHECK_U_CHAR(Data[188], 0x00);
                    CHECK_U_CHAR(Data[189], 0x00);
                    CHECK_U_CHAR(Data[190], 0x00);
                    CHECK_U_CHAR(Data[191], 0x00);
                    CHECK_U_CHAR(Data[192], 0xFF);
                    CHECK_U_CHAR(Data[193], 0xFF);
                    CHECK_U_CHAR(Data[194], 0xFF);
                    CHECK_U_CHAR(Data[195], 0xFF);
                    CHECK_U_CHAR(Data[196], 0x00);
                    CHECK_U_CHAR(Data[197], 0x00);
                    CHECK_U_CHAR(Data[198], 0x00);
                    CHECK_U_CHAR(Data[199], 0x00);
                    CHECK_U_CHAR(Data[200], 0x00);

                    /* Checks on global data */
                   check_global_data();
                   END_CALLS();
                   END_STEP();
             }
     }

            /* Test steps */
            START_STEP("3_NTS", true);
            {
                /* Test case data declarations */
                uint8 * Data = NULL_PTR;
                returnValue = E_OK;

                /* Set global data */
                initialise_global_data();
                *(av_dcom_MB_GTS_RDBI.ref_dcom_MB_GTS_Measurement_Received) = TRUE;

                /* Set expected values for global data checks */
                initialise_expected_global_data();
                {
                    /* Expected Call Sequence  */
                    EXPECTED_CALLS("");

                    /* Call SUT */
                    returnValue = dcom_Global_Time_Sync_Measured_Values_0107_ReadData(Data);

                    /* Test case checks */
                    CHECK_U_CHAR(returnValue, E_NOT_OK);
                    CHECK_BOOLEAN(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received), ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_GTS_Measurement_Received));

                    /* Checks on global data */
                   check_global_data();
                   END_CALLS();
                   END_STEP();
               }
        }
         END_TEST();
}
}

void ut_dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase(int doIt){
if (doIt) {

    START_TEST("47835: [MMP2.11]UTC_dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47835");

            /* Test steps */
            START_STEP("1_NTS", true);
            {
                /* Test case data declarations */
                StbM_SyncRecordTableBlockType buff_syncRecordTableBlock;
                const StbM_SyncRecordTableBlockType * syncRecordTableBlock = &buff_syncRecordTableBlock;
                buff_syncRecordTableBlock.GlbSeconds          = 0x7FFFFFFF;
                buff_syncRecordTableBlock.GlbNanoSeconds      = 0x7FFFFFFF;
                buff_syncRecordTableBlock.TimeBaseStatus      = 0xFF;
                buff_syncRecordTableBlock.VirtualLocalTimeLow = 0x7FFFFFFF;
                buff_syncRecordTableBlock.RateDeviation       = 0x7FFF;
                buff_syncRecordTableBlock.LocSeconds          = 0x7FFFFFFF;
                buff_syncRecordTableBlock.LocNanoSeconds      = 0x7FFFFFFF;
                Std_ReturnType returnValue = E_NOT_OK;

                /* Set global data */
                initialise_global_data();
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x00;

                /* Set expected values for global data checks */
                initialise_expected_global_data();
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x01;
                {
                    /* Expected Call Sequence  */
                    EXPECTED_CALLS("dcom_MB_GTS_Measurement_Fill_TimeRecordHeader#wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader_TRUE;"
                                   "dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1#wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1_TRUE;"
                    		       "rbl_TiSync_cloneToPureLocalTime#default");

                    /* Call SUT */
                   returnValue = dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase(syncRecordTableBlock);

                   /* Test case checks */
                  CHECK_U_CHAR(returnValue, E_OK);
                  CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex),ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex));

                  /* Checks on global data */
                  check_global_data();
                   END_CALLS();
                   END_STEP();
                 }
            }

            /* Test steps */
            START_STEP("2_NTS", true);
            {
                /* Test case data declarations */
                StbM_SyncRecordTableBlockType buff_syncRecordTableBlock;
                const StbM_SyncRecordTableBlockType * syncRecordTableBlock = &buff_syncRecordTableBlock;
                buff_syncRecordTableBlock.GlbSeconds          = 0x7FFFFFFF;
                buff_syncRecordTableBlock.GlbNanoSeconds      = 0x7FFFFFFF;
                buff_syncRecordTableBlock.TimeBaseStatus      = 0xFF;
                buff_syncRecordTableBlock.VirtualLocalTimeLow = 0x7FFFFFFF;
                buff_syncRecordTableBlock.RateDeviation       = 0x7FFF;
                buff_syncRecordTableBlock.LocSeconds          = 0x7FFFFFFF;
                buff_syncRecordTableBlock.LocNanoSeconds      = 0x7FFFFFFF;
                Std_ReturnType returnValue = E_NOT_OK;

                /* Set global data */
                initialise_global_data();
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x0A;

                /* Set expected values for global data checks */
                initialise_expected_global_data();
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x0B;
                {
                    /* Expected Call Sequence  */
                    EXPECTED_CALLS("dcom_MB_GTS_Measurement_Fill_TimeRecordHeader#wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader_TRUE;"
                                   "dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2#wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2_TRUE;"
                    		       "rbl_TiSync_cloneToPureLocalTime#default");
                   /* Call SUT */
                   returnValue = dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase(syncRecordTableBlock);

                   /* Test case checks */
                  CHECK_U_CHAR(returnValue, E_OK);
                  CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex),ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex));

                  /* Checks on global data */
                  check_global_data();
                   END_CALLS();
                   END_STEP();
                 }
            }

            /* Test steps */
            START_STEP("3_NTS", true);
            {
                /* Test case data declarations */
                StbM_SyncRecordTableBlockType buff_syncRecordTableBlock;
                const StbM_SyncRecordTableBlockType * syncRecordTableBlock = &buff_syncRecordTableBlock;
                buff_syncRecordTableBlock.GlbSeconds          = 0x7FFFFFFF;
                buff_syncRecordTableBlock.GlbNanoSeconds      = 0x7FFFFFFF;
                buff_syncRecordTableBlock.TimeBaseStatus      = 0xFF;
                buff_syncRecordTableBlock.VirtualLocalTimeLow = 0x7FFFFFFF;
                buff_syncRecordTableBlock.RateDeviation       = 0x7FFF;
                buff_syncRecordTableBlock.LocSeconds          = 0x7FFFFFFF;
                buff_syncRecordTableBlock.LocNanoSeconds      = 0x7FFFFFFF;
                Std_ReturnType returnValue = E_NOT_OK;

                /* Set global data */
                initialise_global_data();
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x0B;

                /* Set expected values for global data checks */
                initialise_expected_global_data();
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x00;
                {

                    /* Expected Call Sequence  */
                    EXPECTED_CALLS("dcom_MB_GTS_Measurement_Fill_TimeRecordHeader#wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader_TRUE;"
                                   "dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2#wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2_TRUE;"
                    		       "rbl_TiSync_cloneToPureLocalTime#default");

                   /* Call SUT */
                   returnValue = dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase(syncRecordTableBlock);

                   /* Test case checks */
                  CHECK_U_CHAR(returnValue, E_OK);
                  CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex),ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex));

                  /* Checks on global data */
                  check_global_data();
                   END_CALLS();
                   END_STEP();
                 }
            }

            /* Test steps */
            START_STEP("4_NTS", true);
            {
                /* Test case data declarations */
                StbM_SyncRecordTableBlockType buff_syncRecordTableBlock;
                const StbM_SyncRecordTableBlockType * syncRecordTableBlock = &buff_syncRecordTableBlock;
                buff_syncRecordTableBlock.GlbSeconds          = 0x7FFFFFFF;
                buff_syncRecordTableBlock.GlbNanoSeconds      = 0x7FFFFFFF;
                buff_syncRecordTableBlock.TimeBaseStatus      = 0xFF;
                buff_syncRecordTableBlock.VirtualLocalTimeLow = 0x7FFFFFFF;
                buff_syncRecordTableBlock.RateDeviation       = 0x7FFF;
                buff_syncRecordTableBlock.LocSeconds          = 0x7FFFFFFF;
                buff_syncRecordTableBlock.LocNanoSeconds      = 0x7FFFFFFF;
                Std_ReturnType returnValue = E_OK;

                /* Set global data */
                initialise_global_data();
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x00;

                /* Set expected values for global data checks */
                initialise_expected_global_data();
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x01;
                {
                    /* Expected Call Sequence  */
                    EXPECTED_CALLS("dcom_MB_GTS_Measurement_Fill_TimeRecordHeader#wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader_FALSE;"
                            "dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1#wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1_TRUE;"
                    		       "rbl_TiSync_cloneToPureLocalTime#default");

                   /* Call SUT */
                   returnValue = dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase(syncRecordTableBlock);

                   /* Test case checks */
                  CHECK_U_CHAR(returnValue, E_NOT_OK);
                  CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex),ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex));

                  /* Checks on global data */
                  check_global_data();
                   END_CALLS();
                   END_STEP();
                 }
            }

            /* Test steps */
            START_STEP("5_NTS", true);
            {
                /* Test case data declarations */
                StbM_SyncRecordTableBlockType buff_syncRecordTableBlock;
                const StbM_SyncRecordTableBlockType * syncRecordTableBlock = &buff_syncRecordTableBlock;
                buff_syncRecordTableBlock.GlbSeconds          = 0x7FFFFFFF;
                buff_syncRecordTableBlock.GlbNanoSeconds      = 0x7FFFFFFF;
                buff_syncRecordTableBlock.TimeBaseStatus      = 0x7F;
                buff_syncRecordTableBlock.VirtualLocalTimeLow = 0x7FFFFFFF;
                buff_syncRecordTableBlock.RateDeviation       = 0x7FFF;
                buff_syncRecordTableBlock.LocSeconds          = 0x7FFFFFFF;
                buff_syncRecordTableBlock.LocNanoSeconds      = 0x7FFFFFFF;
                Std_ReturnType returnValue = E_OK;

                /* Set global data */
                initialise_global_data();
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x00;

                /* Set expected values for global data checks */
                initialise_expected_global_data();
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x01;
                {
                    /* Expected Call Sequence  */
                    EXPECTED_CALLS("dcom_MB_GTS_Measurement_Fill_TimeRecordHeader#wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader_TRUE;"
                                   "dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1#wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1_FALSE;"
                    		       "rbl_TiSync_cloneToPureLocalTime#default");

                    /* Call SUT */
                   returnValue = dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase(syncRecordTableBlock);

                   /* Test case checks */
                  CHECK_U_CHAR(returnValue, E_NOT_OK);
                  CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex),ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex));

                  /* Checks on global data */
                  check_global_data();
                   END_CALLS();
                   END_STEP();
                 }
            }

            /* Test steps */
            START_STEP("6_NTS", true);
            {
                /* Test case data declarations */
                StbM_SyncRecordTableBlockType buff_syncRecordTableBlock;
                const StbM_SyncRecordTableBlockType * syncRecordTableBlock = &buff_syncRecordTableBlock;
                buff_syncRecordTableBlock.GlbSeconds          = 0x7FFFFFFF;
                buff_syncRecordTableBlock.GlbNanoSeconds      = 0x7FFFFFFF;
                buff_syncRecordTableBlock.TimeBaseStatus      = 0x7F;
                buff_syncRecordTableBlock.VirtualLocalTimeLow = 0x7FFFFFFF;
                buff_syncRecordTableBlock.RateDeviation       = 0x7FFF;
                buff_syncRecordTableBlock.LocSeconds          = 0x7FFFFFFF;
                buff_syncRecordTableBlock.LocNanoSeconds      = 0x7FFFFFFF;
                Std_ReturnType returnValue = E_OK;

                /* Set global data */
                initialise_global_data();
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x0A;

                /* Set expected values for global data checks */
                initialise_expected_global_data();
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x0B;
                {
                    /* Expected Call Sequence  */
                    EXPECTED_CALLS("dcom_MB_GTS_Measurement_Fill_TimeRecordHeader#wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader_TRUE;"
                                   "dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2#wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2_FALSE1;"
                    		       "rbl_TiSync_cloneToPureLocalTime#default");

                    /* Call SUT */
                   returnValue = dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase(syncRecordTableBlock);

                   /* Test case checks */
                  CHECK_U_CHAR(returnValue, E_NOT_OK);
                  CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex),ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex));

                  /* Checks on global data */
                  check_global_data();
                   END_CALLS();
                   END_STEP();
                 }
            }

            START_STEP("7_NTS", true);
            {
                /* Test case data declarations */
                StbM_SyncRecordTableBlockType buff_syncRecordTableBlock;
                const StbM_SyncRecordTableBlockType * syncRecordTableBlock = &buff_syncRecordTableBlock;
                buff_syncRecordTableBlock.GlbSeconds          = 0x7FFFFFFF;
                buff_syncRecordTableBlock.GlbNanoSeconds      = 0x7FFFFFFF;
                buff_syncRecordTableBlock.TimeBaseStatus      = 0xFF;
                buff_syncRecordTableBlock.VirtualLocalTimeLow = 0x7FFFFFFF;
                buff_syncRecordTableBlock.RateDeviation       = 0x7FFF;
                buff_syncRecordTableBlock.LocSeconds          = 0x7FFFFFFF;
                buff_syncRecordTableBlock.LocNanoSeconds      = 0x7FFFFFFF;
                Std_ReturnType returnValue = E_OK;

                /* Set global data */
                initialise_global_data();
                rbl_dcom_MirrorActvtDbgFrmsAppl_u8[0] = 0x01;
                ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x0A;

                /* Set expected values for global data checks */
                initialise_expected_global_data();
                ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex) = 0x0B;
                expected_rbl_dcom_MirrorActvtDbgFrmsAppl_u8[0] = 0x01;
                {
                    /* Expected Call Sequence  */
                    EXPECTED_CALLS("dcom_MB_GTS_Measurement_Fill_TimeRecordHeader#wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader_TRUE;"
                    		       "dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2#wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2_TRUE;"
                    		       "rbl_CustIf_Meas_IMU_X_ST3_PDU_Update#stub_rbl_CustIf_Meas_IMU_X_ST3_PDU_Update_TRUE;"
                    		       "rbl_TiSync_cloneToPureLocalTime#default");

                    /* Call SUT */
                   returnValue = dcom_MB_SyncTimeRecordBlockCallBack_SyncTimeBase(syncRecordTableBlock);

                   /* Test case checks */
                  CHECK_U_CHAR(returnValue, E_OK);
                  CHECK_U_CHAR(ACCESS_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex),ACCESS_EXPECTED_VARIABLE(dcom_MB_GTS_RDBI, dcom_MB_MeasurementDataIndex));
                  CHECK_U_CHAR(rbl_dcom_MirrorActvtDbgFrmsAppl_u8[0], expected_rbl_dcom_MirrorActvtDbgFrmsAppl_u8[0]);

                  /* Checks on global data */
                  check_global_data();
                   END_CALLS();
                   END_STEP();
                 }
            }

        END_TEST();
    }
}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function StbM_GetSyncTimeRecordHead */
Std_ReturnType StbM_GetSyncTimeRecordHead(StbM_SynchronizedTimeBaseType Rte_PDAV0,
                                          StbM_SyncRecordTableHeadType * syncRecordTableHead){
    REGISTER_CALL("StbM_GetSyncTimeRecordHead");

    IF_INSTANCE("stub_StbM_GetSyncTimeRecordHead_TRUE_Valid_Values") {
                 CHECK_U_INT(syncRecordTableHead->HWfrequency, 0x00);
                 CHECK_U_INT(syncRecordTableHead->HWprescaler, 0x00);
                 syncRecordTableHead->HWfrequency = 0xFFFFFFFF;
                 syncRecordTableHead->HWprescaler = 0xFFFFFFFF;
                 return E_OK;
                 }

    IF_INSTANCE("stub_StbM_GetSyncTimeRecordHead_TRUE_Null_Values") {
                 CHECK_U_INT(syncRecordTableHead->HWfrequency, 0x00);
                 CHECK_U_INT(syncRecordTableHead->HWprescaler, 0x00);
                 syncRecordTableHead->HWfrequency = 0x00000000;
                 syncRecordTableHead->HWprescaler = 0x00000000;
                 return E_OK;
                 }

    IF_INSTANCE("stub_StbM_GetSyncTimeRecordHead_FALSE") {
                 CHECK_U_INT(syncRecordTableHead->HWfrequency, 0x00);
                 CHECK_U_INT(syncRecordTableHead->HWprescaler, 0x00);
                 syncRecordTableHead->HWfrequency = 0xFFFFFFFF;
                 syncRecordTableHead->HWprescaler = 0xFFFFFFFF;
                 return E_NOT_OK;
                 }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function rbl_CustIf_Meas_IMU_X_ST3_PDU_Update */
void rbl_CustIf_Meas_IMU_X_ST3_PDU_Update(const StbM_SyncRecordTableBlockType * syncRecordTableBlock){
    REGISTER_CALL("rbl_CustIf_Meas_IMU_X_ST3_PDU_Update");

    IF_INSTANCE("stub_rbl_CustIf_Meas_IMU_X_ST3_PDU_Update_TRUE") {
        CHECK_U_INT(syncRecordTableBlock->GlbSeconds, 0x7FFFFFFF);
        CHECK_U_INT(syncRecordTableBlock->GlbNanoSeconds, 0x7FFFFFFF);
        CHECK_U_INT(syncRecordTableBlock->TimeBaseStatus, 0xFF);
        CHECK_U_INT(syncRecordTableBlock->VirtualLocalTimeLow, 0x7FFFFFFF);
        CHECK_U_INT(syncRecordTableBlock->RateDeviation, 0x7FFF);
        CHECK_U_INT(syncRecordTableBlock->LocSeconds, 0x7FFFFFFF);
        CHECK_U_INT(syncRecordTableBlock->LocNanoSeconds, 0x7FFFFFFF);
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function rbl_TiSync_cloneToPureLocalTime */
void rbl_TiSync_cloneToPureLocalTime(){
    REGISTER_CALL("rbl_TiSync_cloneToPureLocalTime");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function dcom_MB_GTS_Measurement_Fill_TimeRecordHeader */
int BEFORE_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader(){
    REGISTER_CALL("dcom_MB_GTS_Measurement_Fill_TimeRecordHeader");

    IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader_FALSE") {
                    return REPLACE_WRAPPER;
                }

    IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader_TRUE") {
                    return REPLACE_WRAPPER;
                }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function dcom_MB_GTS_Measurement_Fill_TimeRecordHeader */
Std_ReturnType AFTER_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader(Std_ReturnType cppsm_return_value){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function dcom_MB_GTS_Measurement_Fill_TimeRecordHeader */
Std_ReturnType REPLACE_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader(){

    IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader_FALSE") {
                    return E_NOT_OK;
                }

    IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordHeader_TRUE") {
                    return E_OK;
                }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1 */
int BEFORE_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1(const StbM_SyncRecordTableBlockType * syncRecordTableBlock){
    REGISTER_CALL("dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1");

    IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1_FALSE_Null_Values") {
        CHECK_U_INT(syncRecordTableBlock->GlbSeconds, 0x00);
        CHECK_U_INT(syncRecordTableBlock->GlbNanoSeconds, 0x00);
        CHECK_U_INT(syncRecordTableBlock->VirtualLocalTimeLow, 0x00);
        CHECK_U_INT(syncRecordTableBlock->RateDeviation, 0x00);
        CHECK_U_INT(syncRecordTableBlock->LocSeconds, 0x00);
        CHECK_U_INT(syncRecordTableBlock->LocNanoSeconds, 0x00);
        CHECK_CHAR(syncRecordTableBlock->TimeBaseStatus, 0x00);
                return REPLACE_WRAPPER;
            }

        IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1_FALSE") {
            CHECK_U_INT(syncRecordTableBlock->GlbSeconds, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->GlbNanoSeconds, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->VirtualLocalTimeLow, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->RateDeviation, 0x7FFF);
            CHECK_U_INT(syncRecordTableBlock->LocSeconds, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->LocNanoSeconds, 0x7FFFFFFF);
            CHECK_CHAR(syncRecordTableBlock->TimeBaseStatus, 0x7F);
                return REPLACE_WRAPPER;
            }

        IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1_TRUE") {
            CHECK_U_INT(syncRecordTableBlock->GlbSeconds, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->GlbNanoSeconds, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->VirtualLocalTimeLow, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->RateDeviation, 0x7FFF);
            CHECK_U_INT(syncRecordTableBlock->LocSeconds, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->LocNanoSeconds, 0x7FFFFFFF);
            CHECK_CHAR(syncRecordTableBlock->TimeBaseStatus, 0xFF);
                return REPLACE_WRAPPER;
            }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1 */
Std_ReturnType AFTER_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1(Std_ReturnType cppsm_return_value,
                                                                        const StbM_SyncRecordTableBlockType * syncRecordTableBlock){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1 */
Std_ReturnType REPLACE_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1(const StbM_SyncRecordTableBlockType * syncRecordTableBlock){

    IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1_FALSE_Null_Values") {
    return E_NOT_OK;
    }
    IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1_FALSE") {
    return E_NOT_OK;
    }
    IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type1_TRUE") {
    return E_OK;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Before-Wrapper for function dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2 */
int BEFORE_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2(const StbM_SyncRecordTableBlockType * syncRecordTableBlock){
    REGISTER_CALL("dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2");

    IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2_FALSE_Null_Values") {
        CHECK_U_INT(syncRecordTableBlock->GlbSeconds, 0x00);
        CHECK_U_INT(syncRecordTableBlock->GlbNanoSeconds, 0x00);
        CHECK_U_INT(syncRecordTableBlock->VirtualLocalTimeLow, 0x00);
        CHECK_U_INT(syncRecordTableBlock->RateDeviation, 0x00);
        CHECK_U_INT(syncRecordTableBlock->LocSeconds, 0x00);
        CHECK_U_INT(syncRecordTableBlock->LocNanoSeconds, 0x00);
        CHECK_CHAR(syncRecordTableBlock->TimeBaseStatus, 0x00);
                return REPLACE_WRAPPER;
            }

        IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2_FALSE1") {
            CHECK_U_INT(syncRecordTableBlock->GlbSeconds, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->GlbNanoSeconds, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->VirtualLocalTimeLow, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->RateDeviation, 0x7FFF);
            CHECK_U_INT(syncRecordTableBlock->LocSeconds, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->LocNanoSeconds, 0x7FFFFFFF);
            CHECK_CHAR(syncRecordTableBlock->TimeBaseStatus, 0x7F);
                return REPLACE_WRAPPER;
            }

        IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2_TRUE") {
            CHECK_U_INT(syncRecordTableBlock->GlbSeconds, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->GlbNanoSeconds, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->VirtualLocalTimeLow, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->RateDeviation, 0x7FFF);
            CHECK_U_INT(syncRecordTableBlock->LocSeconds, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->LocNanoSeconds, 0x7FFFFFFF);
            CHECK_CHAR(syncRecordTableBlock->TimeBaseStatus, 0xFF);
                return REPLACE_WRAPPER;
            }

        IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2_FALSE2") {
            CHECK_U_INT(syncRecordTableBlock->GlbSeconds, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->GlbNanoSeconds, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->VirtualLocalTimeLow, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->RateDeviation, 0x7FFF);
            CHECK_U_INT(syncRecordTableBlock->LocSeconds, 0x7FFFFFFF);
            CHECK_U_INT(syncRecordTableBlock->LocNanoSeconds, 0x7FFFFFFF);
            CHECK_CHAR(syncRecordTableBlock->TimeBaseStatus, 0xFF);
                return REPLACE_WRAPPER;
            }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2 */
Std_ReturnType AFTER_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2(Std_ReturnType cppsm_return_value,
                                                                        const StbM_SyncRecordTableBlockType * syncRecordTableBlock){
    IF_INSTANCE("default") {
        return cppsm_return_value;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return cppsm_return_value;
}

/* Replace-Wrapper for function dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2 */
Std_ReturnType REPLACE_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2(const StbM_SyncRecordTableBlockType * syncRecordTableBlock){

    IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2_FALSE_Null_Values") {
    return E_NOT_OK;
    }
    IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2_FALSE1") {
    return E_NOT_OK;
    }
    IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2_TRUE") {
    return E_OK;
    }
    IF_INSTANCE("wrapper_dcom_MB_GTS_Measurement_Fill_TimeRecordBlock_Type2_FALSE2") {
    return E_NOT_OK;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

#pragma qas cantata ignore off
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
