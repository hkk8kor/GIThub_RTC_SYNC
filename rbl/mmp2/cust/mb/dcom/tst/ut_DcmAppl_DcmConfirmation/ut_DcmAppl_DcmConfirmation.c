/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_DcmAppl_DcmConfirmation.c
 *    Author: GDEV1KOR
 *    Generated on: 17-Apr-2024 14:18:08
 *    Generated from: DcmAppl_DcmConfirmation.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "Dcm_Cfg_Prot.h"
#include "Dcm.h"
#include "Dcm_Types.h"
#include "DcmDspUds_Uds_Prot.h"
#include "Rte_Dcm.h"
#include "RBAPLHELP_ServiceStateHandler.h"
#define DCM_START_SEC_CODE 
#include "Dcm_MemMap.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
void rba_DcmPma_PlantModeActivation(boolean Active_b);
void APLPLANT_DcmConfirmation(uint8 SID, uint8 ReqType, uint16 ConnectionId, Dcm_ConfirmationStatusType ConfirmationStatus, Dcm_ProtocolType ProtocolType, uint16 TesterSourceAddress);

/* Global data */
rba_DcmPma_PlantModeActivationType_ten rba_DcmPma_PlantModeActivation_en;
boolean rba_DcmPma_PlantModeStatus_b;

/* Expected variables for global data */
rba_DcmPma_PlantModeActivationType_ten expected_rba_DcmPma_PlantModeActivation_en;
boolean expected_rba_DcmPma_PlantModeStatus_b;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(rba_DcmPma_PlantModeActivation_en);
    INITIALISE(rba_DcmPma_PlantModeStatus_b);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(rba_DcmPma_PlantModeActivation_en, expected_rba_DcmPma_PlantModeActivation_en);
    COPY_TO_EXPECTED(rba_DcmPma_PlantModeStatus_b, expected_rba_DcmPma_PlantModeStatus_b);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_U_INT(rba_DcmPma_PlantModeActivation_en, expected_rba_DcmPma_PlantModeActivation_en);
    CHECK_BOOLEAN(rba_DcmPma_PlantModeStatus_b, expected_rba_DcmPma_PlantModeStatus_b);
}

/* Prototypes for test functions */
void run_tests();
void ut_DcmAppl_DcmConfirmation(int);
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
    OPEN_LOG("ut_DcmAppl_DcmConfirmation.ctr", false, 100);
    START_SCRIPT("DcmAppl_DcmConfirmation", true);

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
	ut_DcmAppl_DcmConfirmation(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_DcmAppl_DcmConfirmation.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_DcmAppl_DcmConfirmation(int doIt){
if (doIt) {

    START_TEST("48787: [MMP2.11]UTC_DcmAppl_DcmConfirmation",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management?oslc_config.context=_6CSOkE5XEea6FIzuTUbGfA&skipDefaultGC=true#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48787");

    uint8 SID;
    uint8 ReqType;
    uint16 ConnectionId;
    Dcm_ConfirmationStatusType ConfirmationStatus;
    Dcm_ProtocolType ProtocolType;
    uint16 TesterSourceAddress;

#if (RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED != DCM_CFG_OFF)
		START_STEP("1_NTS", true);

		    SID = RBA_DCMPMA_SID_PLANTMODEACTIVATION;
			ConfirmationStatus = DCM_RES_POS_OK;
			rba_DcmPma_PlantModeActivation_en = RBA_DCMPMA_PLANTMODE_INIT2;
			rba_DcmPma_PlantModeStatus_b = TRUE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("rba_DcmPma_PlantModeActivation#001;"
						"APLPLANT_DcmConfirmation#001");

            /* Call SUT */
            DcmAppl_DcmConfirmation(SID,&ReqType,&ConnectionId, ConfirmationStatus,&ProtocolType,&TesterSourceAddress);


			END_CALLS();
		END_STEP();
		START_STEP("2_NTS", true);

		    SID = RBA_DCMPMA_SID_PLANTMODEACTIVATION;
		    ConfirmationStatus = DCM_RES_POS_NOT_OK;
			rba_DcmPma_PlantModeActivation_en = RBA_DCMPMA_PLANTMODE_INIT2;
			rba_DcmPma_PlantModeStatus_b = TRUE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("APLPLANT_DcmConfirmation#001");

            /* Call SUT */
			DcmAppl_DcmConfirmation(SID,&ReqType,&ConnectionId, ConfirmationStatus,&ProtocolType,&TesterSourceAddress);


			END_CALLS();
		END_STEP();
#endif
		START_STEP("3_NTS", true);

		    SID = RBA_DCMPMA_SID_PLANTMODEACTIVATION;
		    ConfirmationStatus = DCM_RES_POS_OK;
			rba_DcmPma_PlantModeActivation_en = RBA_DCMPMA_PLANTMODE_INACTIVE;
			rba_DcmPma_PlantModeStatus_b = TRUE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("APLPLANT_DcmConfirmation#001");

            /* Call SUT */
			DcmAppl_DcmConfirmation(SID,&ReqType,&ConnectionId,ConfirmationStatus,&ProtocolType,&TesterSourceAddress);


			END_CALLS();
		END_STEP();
		START_STEP("4_NTS", true);

		    SID = RBA_DCMPMA_SID_PLANTMODEACTIVATION + 1;
			ConfirmationStatus = DCM_RES_POS_OK;
			rba_DcmPma_PlantModeActivation_en = RBA_DCMPMA_PLANTMODE_INIT2;
			rba_DcmPma_PlantModeStatus_b = FALSE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

            /* Call SUT */
			DcmAppl_DcmConfirmation(SID,&ReqType,&ConnectionId, ConfirmationStatus,&ProtocolType,&TesterSourceAddress);


			END_CALLS();
		END_STEP();
    END_TEST();
}}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function rba_DcmPma_PlantModeActivation */
void rba_DcmPma_PlantModeActivation(boolean Active_b){
    REGISTER_CALL("rba_DcmPma_PlantModeActivation");

    IF_INSTANCE("001") {
		return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function APLPLANT_DcmConfirmation */
void APLPLANT_DcmConfirmation(uint8 SID,
                              uint8 ReqType,
                              uint16 ConnectionId,
                              Dcm_ConfirmationStatusType ConfirmationStatus,
                              Dcm_ProtocolType ProtocolType,
                              uint16 TesterSourceAddress){
    REGISTER_CALL("APLPLANT_DcmConfirmation");

    IF_INSTANCE("001") {
		return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
