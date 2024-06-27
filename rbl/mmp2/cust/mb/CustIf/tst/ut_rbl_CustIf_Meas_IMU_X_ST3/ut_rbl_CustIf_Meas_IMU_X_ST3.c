/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_CustIf_Meas_IMU_X_ST3.c
 *    Author: HFB2KOR
 *    Generated on: 28-Mar-2023 10:31:07
 *    Generated from: rbl_CustIf_Meas_IMU_X_ST3.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "rbl_CustIf_Meas_IMU_X_ST3.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
uint8 Com_SendSignal(Com_SignalIdType idSignal_u16, const void * signalDataPtr_pcv);
uint8 Com_SendSignalGroup(Com_SignalGroupIdType idSignalGroup_u16);

/* Global data */
typedef struct rbl_CustIf_Meas_IMU_X_ST3_av_struct { uint8(* ref_rbl_CustIf_Meas_IMU_X_ST3_Msg)[64]; } rbl_CustIf_Meas_IMU_X_ST3_av_struct;
extern rbl_CustIf_Meas_IMU_X_ST3_av_struct av_rbl_CustIf_Meas_IMU_X_ST3;

/* Expected variables for global data */
typedef struct expected_rbl_CustIf_Meas_IMU_X_ST3_av_struct { uint8 ref_rbl_CustIf_Meas_IMU_X_ST3_Msg[64]; } expected_rbl_CustIf_Meas_IMU_X_ST3_av_struct;
expected_rbl_CustIf_Meas_IMU_X_ST3_av_struct expected_av_rbl_CustIf_Meas_IMU_X_ST3;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg));
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg));
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_MEMORY("ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)", ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg), sizeof(ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)));
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_CustIf_Meas_IMU_X_ST3_PDU_Update(int);
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
    OPEN_LOG("ut_rbl_CustIf_Meas_IMU_X_ST3.ctr", false, 100);
    START_SCRIPT("rbl_CustIf_Meas_IMU_X_ST3", true);

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
	ut_rbl_CustIf_Meas_IMU_X_ST3_PDU_Update(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_CustIf_Meas_IMU_X_ST3.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/

void ut_rbl_CustIf_Meas_IMU_X_ST3_PDU_Update(int doIt)
{
	if (doIt)
	{
		START_TEST("48736: ut_rbl_CustIf_Meas_IMU_X_ST3_PDU_Update",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48736");

		START_STEP("1_NTS", TRUE);
		{

			/* Set global data */
            initialise_global_data();
            initialise_expected_global_data();
            StbM_SyncRecordTableBlockType buff_syncRecordTableBlock;
            const StbM_SyncRecordTableBlockType *syncRecordTableBlock  = &buff_syncRecordTableBlock;
            buff_syncRecordTableBlock.GlbSeconds          = 0xF3F2F1F0;
            buff_syncRecordTableBlock.GlbNanoSeconds      = 0xF3F2F1F0;
            buff_syncRecordTableBlock.TimeBaseStatus      = 0xF0;
            buff_syncRecordTableBlock.VirtualLocalTimeLow = 0xF3F2F1F0;
            buff_syncRecordTableBlock.RateDeviation       = 0xF1F0;
            buff_syncRecordTableBlock.LocSeconds          = 0xF3F2F1F0;
            buff_syncRecordTableBlock.LocNanoSeconds      = 0xF3F2F1F0;


            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[0]  = 0x00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[1]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[2]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[3]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[4]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[5]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[6]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[7]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[8]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[9]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[10]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[11]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[12]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[13]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[14]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[15]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[16]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[17]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[18]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[19]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[20]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[21]  = 0X00;
            ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[22]  = 0X00;
            /* Set expected values for global data checks */



            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[0]  = 0XF3;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[1]  = 0XF2;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[2]  = 0XF1;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[3]  = 0XF0;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[4]  = 0XF3;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[5]  = 0XF2;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[6]  = 0XF1;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[7]  = 0XF0;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[8]  = 0XF0;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[9]  = 0XF3;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[10]  = 0XF2;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[11]  = 0XF1;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[12]  = 0XF0;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[13]  = 0XF1;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[14]  = 0XF0;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[15]  = 0XF3;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[16]  = 0XF2;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[17]  = 0XF1;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[18]  = 0XF0;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[19]  = 0XF3;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[20]  = 0XF2;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[21]  = 0XF1;
            ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[22]  = 0XF0;

			// Expected Call Sequence

            EXPECTED_CALLS("Com_SendSignal#Com_SendSignal_0;"
					"Com_SendSignal#Com_SendSignal_1;"
					"Com_SendSignal#Com_SendSignal_2;"
					"Com_SendSignal#Com_SendSignal_3;"
					"Com_SendSignal#Com_SendSignal_4;"
					"Com_SendSignal#Com_SendSignal_5;"
					"Com_SendSignal#Com_SendSignal_6;"
					"Com_SendSignal#Com_SendSignal_7;"
					"Com_SendSignal#Com_SendSignal_8;"
					"Com_SendSignal#Com_SendSignal_9;"
					"Com_SendSignal#Com_SendSignal_10;"
					"Com_SendSignal#Com_SendSignal_11;"
					"Com_SendSignal#Com_SendSignal_12;"
					"Com_SendSignal#Com_SendSignal_13;"
					"Com_SendSignal#Com_SendSignal_14;"
					"Com_SendSignal#Com_SendSignal_15;"
					"Com_SendSignal#Com_SendSignal_16;"
					"Com_SendSignal#Com_SendSignal_17;"
					"Com_SendSignal#Com_SendSignal_18;"
					"Com_SendSignal#Com_SendSignal_19;"
					"Com_SendSignal#Com_SendSignal_20;"
					"Com_SendSignal#Com_SendSignal_21;"
					"Com_SendSignal#Com_SendSignal_22;"
					"Com_SendSignalGroup#Update_SendSignalGroup;");
            // Call SUT
          rbl_CustIf_Meas_IMU_X_ST3_PDU_Update(syncRecordTableBlock);

			// Test case checks
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[0],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[0]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[1],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[1]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[2],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[2]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[3],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[3]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[4],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[4]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[5],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[5]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[6],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[6]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[7],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[7]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[8],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[8]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[9],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[9]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[10],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[10]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[11],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[11]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[12],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[12]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[13],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[13]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[14],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[14]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[15],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[15]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[16],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[16]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[17],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[17]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[18],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[18]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[19],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[19]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[20],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[20]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[21],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[21]);
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[22],ACCESS_EXPECTED_VARIABLE(rbl_CustIf_Meas_IMU_X_ST3, rbl_CustIf_Meas_IMU_X_ST3_Msg)[22]);



			END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}


/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function Com_SendSignal */
uint8 Com_SendSignal(Com_SignalIdType idSignal_u16,
                     const void * signalDataPtr_pcv){
    REGISTER_CALL("Com_SendSignal");

    IF_INSTANCE("Com_SendSignal_0")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_01_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF3);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_01_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF3);
		#endif

          return 0;
      }

      IF_INSTANCE("Com_SendSignal_1")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_02_ST3_HAD_BACKUP_CAN_Tx);
        CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF2);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_02_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF2);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_2")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_03_ST3_HAD_BACKUP_CAN_Tx);
    	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF1);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_03_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF1);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_3")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_04_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF0);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_04_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF0);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_4")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_05_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF3);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_05_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF3);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_5")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_06_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF2);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_06_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF2);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_6")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_07_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF1);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_07_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF1);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_7")
      {
	     #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_08_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF0);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_08_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF0);
		#endif
          return 0;
      }
      IF_INSTANCE("Com_SendSignal_8")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_09_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF0);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_09_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF0);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_9")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_10_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF3);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_10_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF3);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_10")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_11_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF2);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_11_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF2);
		#endif
          return- 0;
      }

      IF_INSTANCE("Com_SendSignal_11")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_12_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF1);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_12_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF1);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_12")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_13_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF0);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_13_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF0);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_13")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_14_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF1);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_14_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF1);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_14")
      {
	     #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_15_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF0);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_15_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF0);
		#endif
          return 0;
      }
      IF_INSTANCE("Com_SendSignal_15")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_16_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF3);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_16_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF3);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_16")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_17_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF2);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_17_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF2);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_17")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_18_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF1);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_18_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF1);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_18")
      {
	     #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_19_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF0);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_19_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF0);
		#endif
          return 0;
      }
      IF_INSTANCE("Com_SendSignal_19")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_20_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF3);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_20_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF3);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_20")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_21_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF2);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_21_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF2);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_21")
      {
	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_22_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF1);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_22_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF1);
		#endif
          return 0;
      }

      IF_INSTANCE("Com_SendSignal_22")
      {
	     #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
      	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_A_23_ST3_HAD_BACKUP_CAN_Tx);
      	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF0);

		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_Meas_IMU_B_23_ST3_IMU_INTERNAL_CAN_Tx);
		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0XF0);
		#endif
          return 0;
      }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function Com_SendSignalGroup */
uint8 Com_SendSignalGroup(Com_SignalGroupIdType idSignalGroup_u16){
    REGISTER_CALL("Com_SendSignalGroup");

    IF_INSTANCE("Update_SendSignalGroup")
        {
    	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
        	CHECK_U_INT(idSignalGroup_u16, ComConf_ComSignalGroup_SG_Meas_IMU_A_ST3_3n5lsz3gjs8xv6brvjbxgbhhx_HAD_BACKUP_CAN_Tx);
    		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
    		CHECK_U_INT(idSignalGroup_u16, ComConf_ComSignalGroup_SG_Meas_IMU_B_ST3_9b4k5uqw790qkzbaaznvwy423_IMU_INTERNAL_CAN_Tx);
    		#endif
            return 0;
        }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/

