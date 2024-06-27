/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_MB_Main.c
 *    Author: GDEV1KOR
 *    Generated on: 15-Apr-2024 17:22:06
 *    Generated from: dcom_MB_Main.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "Dem.h"
#include "dcom_MB_OsPub.h"
#include "../../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/dcom_MB_RollbackProtection.h"
#include "dcom_Lib.h"
#include "../../../../../../rbl/mmp2/cust/mb/rbl_dcom/src/dcom_MB_RWDBI_VariantCoding.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
Std_ReturnType NvM_GetErrorStatus(NvM_BlockIdType BlockId, NvM_RequestResultType * RequestResultPtr);
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);
void rbl_dcom_DowngradeProtection_Check();

/* Global data */
uint8 rbl_dcom_MirrorAMGVarSwitch_u8[1];

/* Expected variables for global data */
uint8 expected_rbl_dcom_MirrorAMGVarSwitch_u8[1];

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(rbl_dcom_MirrorAMGVarSwitch_u8);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(rbl_dcom_MirrorAMGVarSwitch_u8, expected_rbl_dcom_MirrorAMGVarSwitch_u8);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_MEMORY("rbl_dcom_MirrorAMGVarSwitch_u8", rbl_dcom_MirrorAMGVarSwitch_u8, expected_rbl_dcom_MirrorAMGVarSwitch_u8, sizeof(expected_rbl_dcom_MirrorAMGVarSwitch_u8));
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_dcom_MB_Init_Proc(int);
void ut_rbl_dcom_MB_20ms_Proc(int);
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
    OPEN_LOG("ut_dcom_MB_Main.ctr", false, 100);
    START_SCRIPT("dcom_MB_Main", true);

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
	ut_rbl_dcom_MB_Init_Proc(1);
	ut_rbl_dcom_MB_20ms_Proc(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_MB_Main.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rbl_dcom_MB_Init_Proc(int doIt)
{
	if (doIt)
	{
		START_TEST("49823: [MMP2.11]UTC_rbl_dcom_MB_Init_Proc",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49823");
#if (RBFS_MMP2 == RBFS_MMP2_IMUB)
		/* Test steps*/
		START_STEP("1_NTS", true);
		{
			/*initialise_globals*/
			rbl_dcom_MirrorAMGVarSwitch_u8[0] = RBL_MB_VARIANT;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("NvM_GetErrorStatus#NvM_GetErrorStatus_1;"
					       "Dem_SetEventStatus#Dem_SetEventStatus_1");

			/* Call SUT */
			rbl_dcom_MB_Init_Proc();

			/* Test step checks */
			CHECK_U_CHAR(rbl_dcom_MirrorAMGVarSwitch_u8[0], RBL_MB_VARIANT);

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("2_NTS", true);
		{
			/*initialise_globals*/
			rbl_dcom_MirrorAMGVarSwitch_u8[0] = 0x02;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("NvM_GetErrorStatus#NvM_GetErrorStatus_1;"
					       "Dem_SetEventStatus#Dem_SetEventStatus_2");

			/* Call SUT */
			rbl_dcom_MB_Init_Proc();

			/* Test step checks */
			CHECK_U_CHAR(rbl_dcom_MirrorAMGVarSwitch_u8[0], 0x02);

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("3_NTS", true);
		{
			/*initialise_globals*/
			rbl_dcom_MirrorAMGVarSwitch_u8[0] = RBL_AMG_VARIANT;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("NvM_GetErrorStatus#NvM_GetErrorStatus_1;"
					       "Dem_SetEventStatus#Dem_SetEventStatus_1");

			/* Call SUT */
			rbl_dcom_MB_Init_Proc();

			/* Test step checks */
			CHECK_U_CHAR(rbl_dcom_MirrorAMGVarSwitch_u8[0], RBL_AMG_VARIANT);

		    END_CALLS();
			END_STEP();
		}

		START_STEP("4_NTS", true);
		{
			/*initialise_globals*/
			rbl_dcom_MirrorAMGVarSwitch_u8[0] = 0x02;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("NvM_GetErrorStatus#NvM_GetErrorStatus_2;"
					       "Dem_SetEventStatus#Dem_SetEventStatus_2");

			/* Call SUT */
			rbl_dcom_MB_Init_Proc();

			/* Test step checks */
			CHECK_U_CHAR(rbl_dcom_MirrorAMGVarSwitch_u8[0], 0x02);

		    END_CALLS();
			END_STEP();
		}
#endif
		START_STEP("5_NTS", true);
		{
			/*initialise_globals*/
			initialise_global_data();
			initialise_expected_global_data();

			/* Test case data Initializations */

			/* Expected Call Sequence  */
			EXPECTED_CALLS("NvM_GetErrorStatus#NvM_GetErrorStatus_3;"
					       "Dem_SetEventStatus#Dem_SetEventStatus_3");
			/* Call SUT */
			rbl_dcom_MB_Init_Proc();

			/* Test step checks */
			check_global_data();

		    END_CALLS();
			END_STEP();
		}
		END_TEST();

	}
}

void ut_rbl_dcom_MB_20ms_Proc(int doIt)
{
	if (doIt)
	{
		START_TEST("48996: [MMP2.11]UTC_rbl_dcom_MB_20ms_Proc",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management?oslc_config.context=_6CSOkE5XEea6FIzuTUbGfA&skipDefaultGC=true#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48996");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */

			//Expected Call Sequence
			EXPECTED_CALLS("rbl_dcom_DowngradeProtection_Check#rbl_dcom_DowngradeProtection_Check_1");

			//Call FUT
			 rbl_dcom_MB_20ms_Proc();

			/* Test step checks */
		    check_global_data();

			END_CALLS();
	    }
	    END_STEP();
	    END_TEST();
	}
}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function NvM_GetErrorStatus */
Std_ReturnType NvM_GetErrorStatus(NvM_BlockIdType BlockId,
                                  NvM_RequestResultType * RequestResultPtr){
    REGISTER_CALL("NvM_GetErrorStatus");

#if (RBFS_MMP2 == RBFS_MMP2_IMUB)
    IF_INSTANCE("NvM_GetErrorStatus_1") {
    	CHECK_U_INT(BlockId,NvMConf_NvMBlockDescriptor_DCOM_AMG_SWITCH);
    	* RequestResultPtr = NVM_REQ_OK;
        return RequestResultPtr;
    }
    IF_INSTANCE("NvM_GetErrorStatus_2") {
    	CHECK_U_INT(BlockId,NvMConf_NvMBlockDescriptor_DCOM_AMG_SWITCH);
    	* RequestResultPtr = NVM_REQ_NOT_OK;
        return RequestResultPtr;
    }
#endif
    IF_INSTANCE("NvM_GetErrorStatus_3") {
    	CHECK_U_INT(BlockId,NvMConf_NvMBlockDescriptor_DCOM_AMG_SWITCH);
    	* RequestResultPtr = NVM_REQ_NOT_OK;
        return RequestResultPtr;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function Dem_SetEventStatus */
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId,
                                  Dem_EventStatusType EventStatus){
    REGISTER_CALL("Dem_SetEventStatus");
#if (RBFS_MMP2 == RBFS_MMP2_IMUB)
    IF_INSTANCE("Dem_SetEventStatus_1") {
    	CHECK_U_CHAR(EventId,DemConf_DemEventParameter_RBL_NVM_Variant_handler);
    	CHECK_U_CHAR(EventStatus,DEM_EVENT_STATUS_PASSED);
        return DEM_EVENT_STATUS_PASSED;
    }
    IF_INSTANCE("Dem_SetEventStatus_2") {
    	CHECK_U_CHAR(EventId,DemConf_DemEventParameter_RBL_NVM_Variant_handler);
    	CHECK_U_CHAR(EventStatus,DEM_EVENT_STATUS_FAILED);
        return DEM_EVENT_STATUS_FAILED;
    }
#endif
    IF_INSTANCE("Dem_SetEventStatus_3") {
    	CHECK_U_CHAR(EventId,DemConf_DemEventParameter_RBL_NVM_Variant_handler);
    	CHECK_U_CHAR(EventStatus,DEM_EVENT_STATUS_FAILED);
        return CANTATA_DEFAULT_VALUE;
    }
    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}


/* Stub for function rbl_dcom_DowngradeProtection_Check */
void rbl_dcom_DowngradeProtection_Check(){
    REGISTER_CALL("rbl_dcom_DowngradeProtection_Check");

    IF_INSTANCE("rbl_dcom_DowngradeProtection_Check_1") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
