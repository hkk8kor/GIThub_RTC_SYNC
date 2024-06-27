/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_DiagnosticSessionControl.c
 *    Author: GDEV1KOR
 *    Generated on: 11-Oct-2023 11:56:29
 *    Generated from: dcom_DiagnosticSessionControl.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"
#include "DcmDspUds_Roe_Inf.h"
#include "Rte_Dcm.h"
#include "DcmAppl.h"
#include "dcom_MB_Pub.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
void dcom_SetProgConditions();
/* None */

/* Global data */
extern boolean rbl_dcomActiveDiagSession;

/* Expected variables for global data */
boolean expected_rbl_dcomActiveDiagSession;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(rbl_dcomActiveDiagSession);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(rbl_dcomActiveDiagSession, expected_rbl_dcomActiveDiagSession);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_BOOLEAN(rbl_dcomActiveDiagSession, expected_rbl_dcomActiveDiagSession);
}

/* Prototypes for test functions */
void run_tests();
void ut_DcmAppl_DcmSesCtrlChangeIndication(int);
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF ) )
void ut_DcmAppl_DcmGetSesChgPermission(int);
#endif
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
    OPEN_LOG("ut_dcom_DiagnosticSessionControl.ctr", false, 100);
    START_SCRIPT("dcom_DiagnosticSessionControl", true);

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
	ut_DcmAppl_DcmSesCtrlChangeIndication(1);
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF ) )
	ut_DcmAppl_DcmGetSesChgPermission(1);
#endif
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_DiagnosticSessionControl.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_DcmAppl_DcmSesCtrlChangeIndication(int doIt){
if (doIt)
	{
    /* Test case data declarations */
	Dcm_SesCtrlType SesCtrlTypeOld;
	Dcm_SesCtrlType SesCtrlTypeNew;
	boolean rbl_dcomActiveDiagSession = FALSE;

    START_TEST("46384: [MMP2.11]UTC_DcmAppl_DcmSesCtrlChangeIndication",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46384");

	START_STEP("1_NTS", true);
	{
			SesCtrlTypeNew = DCM_DEFAULT_SESSION;
			boolean rbl_dcomActiveDiagSession = FALSE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

            /* Call SUT */
            DcmAppl_DcmSesCtrlChangeIndication(SesCtrlTypeOld,SesCtrlTypeNew);

            /* Test case checks */
            CHECK_BOOLEAN(rbl_dcomActiveDiagSession,FALSE);

			END_CALLS();
	END_STEP();
	}

	START_STEP("2_NTS", true);
	{
			SesCtrlTypeNew = DCM_EXTENDED_DIAGNOSTIC_SESSION;
			boolean rbl_dcomActiveDiagSession = TRUE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

            /* Call SUT */
            DcmAppl_DcmSesCtrlChangeIndication(SesCtrlTypeOld,SesCtrlTypeNew);

			/* Test case checks */
            CHECK_BOOLEAN(rbl_dcomActiveDiagSession,TRUE);

			END_CALLS();

	END_STEP();
	}

	START_STEP("3_NTS", true);
	{
			SesCtrlTypeNew = DCM_PROGRAMMING_SESSION;

			/* Expected Call Sequence  */
            #if (RBFS_DcomReprogResponseType != RBFS_DcomReprogResponseType_Warm)
			EXPECTED_CALLS("dcom_SetProgConditions#dcom_SetProgConditions_01");

           #else
			EXPECTED_CALLS("");

            #endif

            /* Call SUT */
            DcmAppl_DcmSesCtrlChangeIndication(SesCtrlTypeOld,SesCtrlTypeNew);

			/* Test case checks */
			END_CALLS();

	END_STEP();
	}

	START_STEP("4_NTS", true);
	{
#if (RBFS_DcomSupplierSession != RBFS_DcomSupplierSession_Disabled)
			SesCtrlTypeNew = DCM_SUPPLIER_SESSION;

			/* Expected Call Sequence  */


			EXPECTED_CALLS("");
#endif
            /* Call SUT */
            DcmAppl_DcmSesCtrlChangeIndication(SesCtrlTypeOld,SesCtrlTypeNew);

			/* Test case checks */
#if (RBFS_DcomSupplierSession != RBFS_DcomSupplierSession_Disabled)
			END_CALLS();
#endif

	END_STEP();
	}

	START_STEP("5_NTS", true);
	{
			SesCtrlTypeNew = 0x05;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

            /* Call SUT */
            DcmAppl_DcmSesCtrlChangeIndication(SesCtrlTypeOld,SesCtrlTypeNew);

			/* Test case checks */
			END_CALLS();

	END_STEP();
	}
    END_TEST();
}}

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF ) )
void ut_DcmAppl_DcmGetSesChgPermission(int doIt){
if (doIt) {

    /* Test case data declarations */
	Dcm_SesCtrlType SesCtrlTypeActive;
	Dcm_SesCtrlType SesCtrlTypeNew;
	Dcm_NegativeResponseCodeType test;
    Dcm_NegativeResponseCodeType  * ErrorCode = &test;
    Std_ReturnType returnValue=E_OK;

    START_TEST("46385: [MMP2.11]UTC_DcmAppl_DcmGetSesChgPermission",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46385");

	START_STEP("1_NTS", true);
	{
			SesCtrlTypeNew = DCM_DEFAULT_SESSION;
			*ErrorCode = 0x55;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

            /* Call SUT */
            returnValue = DcmAppl_DcmGetSesChgPermission(SesCtrlTypeActive, SesCtrlTypeNew, ErrorCode);

			/* Test case checks */
            CHECK_U_CHAR(returnValue, E_OK);
            CHECK_U_CHAR(*ErrorCode, DCOM_NO_ERROR);
			END_CALLS();

	END_STEP();
	}

	START_STEP("2_NTS", true);
	{
			SesCtrlTypeNew = DCM_EXTENDED_DIAGNOSTIC_SESSION;
			*ErrorCode = 0x55;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

            /* Call SUT */
            returnValue = DcmAppl_DcmGetSesChgPermission(SesCtrlTypeActive, SesCtrlTypeNew, ErrorCode);

			/* Test case checks */
            CHECK_U_CHAR(returnValue, E_OK);
            CHECK_U_CHAR(*ErrorCode, DCOM_NO_ERROR);
			END_CALLS();

	END_STEP();
	}

	START_STEP("3_NTS", true);
	{
			SesCtrlTypeNew = DCM_PROGRAMMING_SESSION;
			*ErrorCode = 0x55;

#if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)

		    /* Set global data */
		    initialise_global_data();
			dcom_CheckReprogPreConditionFullfilled = TRUE;

		    /* Set expected values for global data checks */
		    initialise_expected_global_data();
		    expected_dcom_CheckReprogPreConditionFullfilled = FALSE;
#endif
			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

            /* Call SUT */
            returnValue = DcmAppl_DcmGetSesChgPermission(SesCtrlTypeActive, SesCtrlTypeNew, ErrorCode);

			/* Test case checks */
            CHECK_U_CHAR(returnValue, E_OK);
            CHECK_U_CHAR(*ErrorCode, DCOM_NO_ERROR);

#if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)
            check_global_data();
#endif
			END_CALLS();
	END_STEP();
	}

	START_STEP("3_1_NTS", true);
	{
			SesCtrlTypeNew = DCM_PROGRAMMING_SESSION;
			*ErrorCode = 0x55;

#if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)

		    /* Set global data */
		    initialise_global_data();
			dcom_CheckReprogPreConditionFullfilled = FALSE;

		    /* Set expected values for global data checks */
		    initialise_expected_global_data();
			expected_dcom_CheckReprogPreConditionFullfilled = FALSE;
#endif
			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

            /* Call SUT */
            returnValue = DcmAppl_DcmGetSesChgPermission(SesCtrlTypeActive, SesCtrlTypeNew, ErrorCode);

#if (RBFS_CheckProgPreCondition == RBFS_CheckProgPreCondition_ON)			/* Test case checks */
            CHECK_U_CHAR(returnValue, E_NOT_OK);
            CHECK_U_CHAR(*ErrorCode, DCM_E_CONDITIONSNOTCORRECT);
			check_global_data();
#endif
			END_CALLS();

	END_STEP();
	}

	START_STEP("4_NTS", true);
	{
#if (RBFS_DcomSupplierSession != RBFS_DcomSupplierSession_Disabled)
			SesCtrlTypeNew = DCM_SUPPLIER_SESSION;
			*ErrorCode = 0x55;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");
#endif
            /* Call SUT */
            returnValue = DcmAppl_DcmGetSesChgPermission(SesCtrlTypeActive, SesCtrlTypeNew, ErrorCode);

#if (RBFS_DcomSupplierSession != RBFS_DcomSupplierSession_Disabled)
			/* Test case checks */
            CHECK_U_CHAR(returnValue, E_OK);
            CHECK_U_CHAR(*ErrorCode, DCOM_NO_ERROR);
			END_CALLS();
#endif
	END_STEP();
	}

	START_STEP("5_NTS", true);
	{
			 SesCtrlTypeNew = 0x09;
			*ErrorCode = 0x55;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

            /* Call SUT */
            returnValue = DcmAppl_DcmGetSesChgPermission(SesCtrlTypeActive, SesCtrlTypeNew, ErrorCode);

			/* Test case checks */
            CHECK_U_CHAR(returnValue, DCM_E_SESSION_NOT_ALLOWED);
            CHECK_U_CHAR(*ErrorCode, DCOM_NO_ERROR);
			END_CALLS();

	END_STEP();
	}
    END_TEST();
}}
#endif
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/
/* Stub for function dcom_SetProgConditions */
void dcom_SetProgConditions(){
    REGISTER_CALL("dcom_SetProgConditions");

    IF_INSTANCE("dcom_SetProgConditions_01") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
