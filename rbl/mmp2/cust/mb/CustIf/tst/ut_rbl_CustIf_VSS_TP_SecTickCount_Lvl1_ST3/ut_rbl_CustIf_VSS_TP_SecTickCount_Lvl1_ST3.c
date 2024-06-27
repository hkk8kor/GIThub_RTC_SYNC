/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_CustIf_VSS_TP_SecTickCount_Lvl1_ST3.c
 *    Author: GDEV1KOR
 *    Generated on: 15-Apr-2024 10:22:16
 *    Generated from: rbl_CustIf_VSS_TP_SecTickCount_Lvl1_ST3.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "../../../../../../rbl/mmp2/cust/mb/rbl_CustIf/src/rbl_CustIf_Hndl_Utils.h"
#include "rbl_CustIf_VSS_TP_SecTickCount_Lvl1_ST3.h"
#include "Rte_rbl_CustIf.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
Std_ReturnType Rte_Write_rbl_CustIf_P_VSS_TP_SecTickCount_ST3_VSS_TP_SecTickCount_ST3(const uint8 * data);

/* Global data */
Rte_REActCounterType Rte_ActCount_Ssa_BcTp_DRET_Runnable_ReceiveTickCount_VSS_TP_SecTickCount_ST3;

/* Expected variables for global data */
Rte_REActCounterType expected_Rte_ActCount_Ssa_BcTp_DRET_Runnable_ReceiveTickCount_VSS_TP_SecTickCount_ST3;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(Rte_ActCount_Ssa_BcTp_DRET_Runnable_ReceiveTickCount_VSS_TP_SecTickCount_ST3);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(Rte_ActCount_Ssa_BcTp_DRET_Runnable_ReceiveTickCount_VSS_TP_SecTickCount_ST3, expected_Rte_ActCount_Ssa_BcTp_DRET_Runnable_ReceiveTickCount_VSS_TP_SecTickCount_ST3);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_U_CHAR(Rte_ActCount_Ssa_BcTp_DRET_Runnable_ReceiveTickCount_VSS_TP_SecTickCount_ST3, expected_Rte_ActCount_Ssa_BcTp_DRET_Runnable_ReceiveTickCount_VSS_TP_SecTickCount_ST3);
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_CustIf_SgnGrp_Tout_Cbk_VSS_TP_SecTickCount_Lvl1_ST3(int);
void ut_rbl_CustIf_SgnGrp_Cbk_VSS_TP_SecTickCount_Lvl1_ST3(int);
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
    OPEN_LOG("ut_rbl_CustIf_VSS_TP_SecTickCount_Lvl1_ST3.ctr", false, 100);
    START_SCRIPT("rbl_CustIf_VSS_TP_SecTickCount_Lvl1_ST3", true);

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
	ut_rbl_CustIf_SgnGrp_Tout_Cbk_VSS_TP_SecTickCount_Lvl1_ST3(1);
	ut_rbl_CustIf_SgnGrp_Cbk_VSS_TP_SecTickCount_Lvl1_ST3(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_CustIf_VSS_TP_SecTickCount_Lvl1_ST3.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rbl_CustIf_SgnGrp_Tout_Cbk_VSS_TP_SecTickCount_Lvl1_ST3(int doIt)
{
	if (doIt)
	{
		START_TEST("49916: [MMP2.11]UTC_rbl_CustIf_SgnGrp_Tout_Cbk_VSS_TP_SecTickCount_Lvl1_ST3",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49916");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		/* Test case data declarations */

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */
			Rte_ActCount_Ssa_BcTp_DRET_Runnable_ReceiveTickCount_VSS_TP_SecTickCount_ST3 = 0x01U;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			rbl_CustIf_SgnGrp_Tout_Cbk_VSS_TP_SecTickCount_Lvl1_ST3();

			/* Test case checks */
			CHECK_U_CHAR(Rte_ActCount_Ssa_BcTp_DRET_Runnable_ReceiveTickCount_VSS_TP_SecTickCount_ST3,0x01U);

		    END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_SgnGrp_Cbk_VSS_TP_SecTickCount_Lvl1_ST3(int doIt)
{
	if (doIt)
	{
		START_TEST("49917: [MMP2.11]UTC_rbl_CustIf_SgnGrp_Cbk_VSS_TP_SecTickCount_Lvl1_ST3",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49917");

		/* Test case data declarations */
		PduIdType id;
		PduInfoType ptr;

		START_STEP("1_NTS", TRUE);
		{
			/* Test case data Initializations */
			id = 0;
			ptr.SduDataPtr = 0;
			ptr.SduLength = 0;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Rte_Write_rbl_CustIf_P_VSS_TP_SecTickCount_ST3_VSS_TP_SecTickCount_ST3#Rte_Write_rbl_CustIf_P_VSS_TP_SecTickCount_ST3_VSS_TP_SecTickCount_ST3_1");

			/* Call SUT */
			rbl_CustIf_SgnGrp_Cbk_VSS_TP_SecTickCount_Lvl1_ST3(&id,&ptr);

			/* Test case checks */
            CHECK_U_INT(id,0);
            CHECK_U_INT(ptr.SduDataPtr, 0);
            CHECK_U_INT(ptr.SduLength, 0);

		    END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function Rte_Write_rbl_CustIf_P_VSS_TP_SecTickCount_ST3_VSS_TP_SecTickCount_ST3 */
Std_ReturnType Rte_Write_rbl_CustIf_P_VSS_TP_SecTickCount_ST3_VSS_TP_SecTickCount_ST3(const uint8 * data){
    REGISTER_CALL("Rte_Write_rbl_CustIf_P_VSS_TP_SecTickCount_ST3_VSS_TP_SecTickCount_ST3");

    IF_INSTANCE("Rte_Write_rbl_CustIf_P_VSS_TP_SecTickCount_ST3_VSS_TP_SecTickCount_ST3_1") {
    	CHECK_U_CHAR(data,0);
        return CANTATA_DEFAULT_VALUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
