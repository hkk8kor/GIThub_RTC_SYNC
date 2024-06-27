/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_RBEMM_Extended_Callouts.c
 *    Author: GDEV1KOR
 *    Generated on: 28-Mar-2024 19:40:51
 *    Generated from: RBEMM_Extended_Callouts.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "Std_Types.h"
#include "RBEMM_Config.h"
#include "RBEMM_Types.h"
#include "RBEMM_Extended_Callouts.h"
#include "RBEMM_Project.h"
#if (RBFS_EMM == RBFS_EMM_Extended)
#if(RBFS_MMP2 == RBFS_MMP2_IMUB)
    #include "CanNm.h"
#endif
#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
void RBSMM_RequestMode(RBSMM_Requester_ST * self, SystemMode_N systemmode);
void CanNm_ConfirmPnAvailability(NetworkHandleType nmChannelHandle);
SystemMode_N RBSMM_CurrentSystemMode();

/* Global data */
const RBEMM_ExtPrjNetwork_ParamType g_RBEMM_Prj_NetworkChnlPara_ast[1U];
RBSMM_Requester_ST RBAllSMM_Requester_st[RBSMM_NUMBER_OF_REQUESTER];

/* Expected variables for global data */
RBSMM_Requester_ST expected_RBAllSMM_Requester_st[RBSMM_NUMBER_OF_REQUESTER];

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    /* No initialisation for const data: g_RBEMM_Prj_NetworkChnlPara_ast */
    INITIALISE(RBAllSMM_Requester_st);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(RBAllSMM_Requester_st, expected_RBAllSMM_Requester_st);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_MEMORY("RBAllSMM_Requester_st", RBAllSMM_Requester_st, expected_RBAllSMM_Requester_st, sizeof(expected_RBAllSMM_Requester_st));
}

/* Prototypes for test functions */
void run_tests();
void ut_RBEMM_ExtRequestNetOn_ECUM_WKSOURCE_CAN_Callout(int);
void ut_NM_RxIndication(int);
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
    OPEN_LOG("ut_RBEMM_Extended_Callouts.ctr", false, 100);
    START_SCRIPT("RBEMM_Extended_Callouts", true);

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
    ut_RBEMM_ExtRequestNetOn_ECUM_WKSOURCE_CAN_Callout(1);
    ut_NM_RxIndication(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_RBEMM_Extended_Callouts.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_RBEMM_ExtRequestNetOn_ECUM_WKSOURCE_CAN_Callout(int doIt)
{
	if (doIt)
	{
		START_TEST("49829: [MMP2.11]UTC_RBEMM_ExtRequestNetOn_ECUM_WKSOURCE_CAN_Callout",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49829");

		/* Test steps*/
		START_STEP("1_NTS", true);
		{
			/*initialise_globals*/
			uint8 l_cnt;
			for(l_cnt=0;l_cnt<RBEMM_PROJECT_NETWORK_MAXCHANNELS;l_cnt++)
			{
				RBAllSMM_Requester_st[l_cnt].requestedSystemMode = EMM_CFG_NO_REQUESTER;
			}
			/* Expected Call Sequence  */
			EXPECTED_CALLS("RBSMM_RequestMode#default;"
#if(RBFS_MMP2 != RBFS_MMP2_IMUA)
					       "CanNm_ConfirmPnAvailability#default;"
#endif
					);

			/* Call SUT */
			RBEMM_ExtRequestNetOn_ECUM_WKSOURCE_CAN_Callout();

			/* Test step checks */

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("2_NTS", true);
		{
			/*initialise_globals*/
			uint8 l_cnt;
			for(l_cnt=0;l_cnt<RBEMM_PROJECT_NETWORK_MAXCHANNELS;l_cnt++)
			{
				RBAllSMM_Requester_st[l_cnt].requestedSystemMode = EMM_CFG_NO_REQUESTER + 1;
			}
			/* Expected Call Sequence  */
			EXPECTED_CALLS("RBSMM_RequestMode#default_1;"
#if(RBFS_MMP2 != RBFS_MMP2_IMUA)
					       "CanNm_ConfirmPnAvailability#default;"
#endif
					);

			/* Call SUT */
			RBEMM_ExtRequestNetOn_ECUM_WKSOURCE_CAN_Callout();

			/* Test step checks */

		    END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_NM_RxIndication(int doIt)
{
	if (doIt)
	{
		NetworkHandleType NetworkHandle;
		START_TEST("49830: [MMP2.11]UTC_NM_RxIndication",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49830");

		/* Test steps*/
		START_STEP("1_NTS", true);
		{
			/*initialise_globals*/
			NetworkHandle = NmConf_NmChannelConfig_NmChannelConfig_Can;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("RBSMM_CurrentSystemMode#RBSMM_CurrentSystemMode_1;"
#if(RBFS_MMP2 != RBFS_MMP2_IMUD)
					       "RBSMM_RequestMode#default_2;"
#endif
			);
			/* Call SUT */
			NM_RxIndication(NetworkHandle);

			/* Test step checks */

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("2_NTS", true);
		{
			/*initialise_globals*/
			NetworkHandle = NmConf_NmChannelConfig_NmChannelConfig_Can;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("RBSMM_CurrentSystemMode#RBSMM_CurrentSystemMode_2");

			/* Call SUT */
			NM_RxIndication(NetworkHandle);

			/* Test step checks */

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("3_NTS", true);
		{
			/*initialise_globals*/
			NetworkHandle = 0;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("RBSMM_CurrentSystemMode#RBSMM_CurrentSystemMode_3");

			/* Call SUT */
			NM_RxIndication(&NetworkHandle);

			/* Test step checks */

		    END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}
#endif
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function RBSMM_RequestMode */
void RBSMM_RequestMode(RBSMM_Requester_ST * self,
                       SystemMode_N systemmode){
    REGISTER_CALL("RBSMM_RequestMode");

    IF_INSTANCE("default") {
    	CHECK_U_CHAR(systemmode,C_SMM_NET_ON_N);
        return;
    }
    IF_INSTANCE("default_1") {
    	CHECK_U_CHAR(systemmode,C_SMM_NET_ON_N);
        return;
    }
    IF_INSTANCE("default_2") {
    	CHECK_U_CHAR(systemmode,C_SMM_NET_ON_N);
        return;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function CanNm_ConfirmPnAvailability */
void CanNm_ConfirmPnAvailability(NetworkHandleType nmChannelHandle){
    REGISTER_CALL("CanNm_ConfirmPnAvailability");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSMM_CurrentSystemMode */
SystemMode_N RBSMM_CurrentSystemMode(){
    REGISTER_CALL("RBSMM_CurrentSystemMode");

    IF_INSTANCE("RBSMM_CurrentSystemMode_1") {
        return (SystemMode_N) C_SMM_NET_ON_N;
    }
    IF_INSTANCE("RBSMM_CurrentSystemMode_2") {
        return (SystemMode_N) C_SMM_NET_OFF_N;
    }
    IF_INSTANCE("RBSMM_CurrentSystemMode_3") {
        return (SystemMode_N) CANTATA_DEFAULT_VALUE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return (SystemMode_N) CANTATA_DEFAULT_VALUE;
}

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
