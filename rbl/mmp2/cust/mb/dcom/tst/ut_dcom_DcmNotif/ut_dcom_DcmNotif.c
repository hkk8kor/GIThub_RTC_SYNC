/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_dcom_DcmNotif.c
 *    Author: GDEV1KOR
 *    Generated on: 15-Apr-2024 13:00:34
 *    Generated from: dcom_DcmNotif.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "Dcm.h"
#include "Dcm_Cfg_Prot.h"
#include "DcmDspUds_Roe_Inf.h"
#include "DcmDspUds_Cdtcs_Inf.h"
#include "DcmAppl.h"
#include "dcom_MB_Pub.h"
#include "dcom_Common.h"
#include "Rte_Ports_Adapter.h"
#include "Ports_Adapter_MemMap.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
Std_ReturnType Ssa_Coding_ServiceRequestNotification_Confirmation(uint8 SID, uint8 ReqType, uint16 SourceAddress, Dcm_ConfirmationStatusType ConfirmationStatus);
Std_ReturnType Ssa_Coding_ServiceRequestNotification_Indication(uint8 SID, const uint8 * RequestData, uint32 DataSize, uint8 ReqType, uint16 SourceAddress, Dcm_NegativeResponseCodeType * ErrorCode);
Std_ReturnType Ssa_RightsM_ServiceRequestNotification_Confirmation(uint8 SID, uint8 ReqType, uint16 SourceAddress, Dcm_ConfirmationStatusType ConfirmationStatus);
Std_ReturnType Ssa_RightsM_ServiceRequestNotification_Indication(uint8 SID, const uint8 * RequestData, uint32 DataSize, uint8 ReqType, uint16 SourceAddress, Dcm_NegativeResponseCodeType * ErrorCode);

/* Global data */
extern uint16 dcom_Requested_Tester;
boolean rba_DcmPma_PlantModeStatus_b;

/* Expected variables for global data */
uint16 expected_dcom_Requested_Tester;
boolean expected_rba_DcmPma_PlantModeStatus_b;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(dcom_Requested_Tester);
    INITIALISE(rba_DcmPma_PlantModeStatus_b);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(dcom_Requested_Tester, expected_dcom_Requested_Tester);
    COPY_TO_EXPECTED(rba_DcmPma_PlantModeStatus_b, expected_rba_DcmPma_PlantModeStatus_b);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_U_INT(dcom_Requested_Tester, expected_dcom_Requested_Tester);
    CHECK_BOOLEAN(rba_DcmPma_PlantModeStatus_b, expected_rba_DcmPma_PlantModeStatus_b);
}

/* Prototypes for test functions */
void run_tests();
#if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
void ut_DcmAppl_SupplierNotification(int);
#endif

#if (DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
void ut_DcmAppl_ManufacturerNotification(int);
#endif
void ut_ServiceRequestNotification_Dcm_Coding_Confirmation(int);
void ut_ServiceRequestNotification_Dcm_Coding_Indication(int);
void ut_ServiceRequestNotification_Dcm_RightsM_Confirmation(int);
void ut_ServiceRequestNotification_Dcm_RightsM_Indication(int);
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
    OPEN_LOG("ut_dcom_DcmNotif.ctr", false, 100);
    START_SCRIPT("dcom_DcmNotif", true);

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
#if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
ut_DcmAppl_SupplierNotification(1);
#endif

#if (DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
ut_DcmAppl_ManufacturerNotification(1);
#endif
	ut_ServiceRequestNotification_Dcm_Coding_Confirmation(1);
	ut_ServiceRequestNotification_Dcm_Coding_Indication(1);
    ut_ServiceRequestNotification_Dcm_RightsM_Confirmation(1);
	ut_ServiceRequestNotification_Dcm_RightsM_Indication(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_dcom_DcmNotif.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
#if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
void ut_DcmAppl_SupplierNotification(int doIt){
   if (doIt) {

    START_TEST("46400: [MMP2.11]UTC_DcmAppl_DcmNotification",
               "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46400");

				/* Test steps */
			    START_STEP("1_NTS", true);
			    {
			    /*Test step data */
				Std_ReturnType returnValue = E_OK;

	            uint8 SID = 0x01;
                uint8 RequestType = 0x02;
                uint16 TesterSourceAddress = 0x03;
				uint8 buffer_RequestData = 0x04 ;
				const uint8* RequestData = &buffer_RequestData;
                uint32 RequestLength = 0x05;
                uint16 ConnectionId = 0x06;
				Dcm_NegativeResponseCodeType* ErrorCode = 0x00;
				Dcm_ProtocolType ProtocolType = DCOM_NO_ERROR;

				/* Set global data */
                initialise_global_data();

                /* Set expected values for global data checks */
                initialise_expected_global_data();

	            /* Expected Call Sequence  */
                EXPECTED_CALLS("");

                /* Call SUT */
                returnValue = DcmAppl_SupplierNotification(&SID,&RequestData,&RequestLength,&RequestType,&ConnectionId,&TesterSourceAddress,&ErrorCode,&ProtocolType);

                /* Test case checks */
                CHECK_U_CHAR(returnValue, E_OK);
                CHECK_U_CHAR(SID, 0x01);
                CHECK_U_CHAR(RequestType, 0x02);
                CHECK_U_INT(TesterSourceAddress, 0x00);
                CHECK_U_CHAR(RequestData, 0x49);
                CHECK_U_CHAR(RequestLength, 0x05);
		        CHECK_U_CHAR(ConnectionId, 0x06);
		        CHECK_U_CHAR(ErrorCode, 0x00);
		        CHECK_U_CHAR(ProtocolType, DCOM_NO_ERROR);

	            /* Checks on global data */
                check_global_data();
          END_CALLS();
		END_STEP();
			    }
    END_TEST();
	}}
#endif


#if (DCM_CFG_MANUFACTURER_NOTIFICATION_ENABLED != DCM_CFG_OFF)

void ut_DcmAppl_ManufacturerNotification(int doIt)
{
if (doIt)
{
  START_TEST("46399: [MMP2.11]UTC_DcmAppl_ManufacturerNotification ",
             "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=46399");

#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
				START_STEP("1_NTS", true);
				{
				initialise_expected_global_data();

				/* Test case data declarations */
				uint8 SID = 0x00;
				uint8 buffer_RequestData = 0x01 ;
				const uint8 * RequestData = &buffer_RequestData;
				uint32 DataSize = 0;
				Dcm_NegativeResponseCodeType  ErrorCode = DCOM_SECOND_TESTER;
				Std_ReturnType returnValue;
				uint16 TesterSourceAddress = DCOM_SECOND_TESTER;
				uint8 ReqType = 0x01;
				uint16 ConnectionId= 0;
				Dcm_ProtocolType ProtocolType = 0x00;
				dcom_Requested_Tester = DCOM_SECOND_TESTER;

				/* Set expected values for global data checks */
				initialise_expected_global_data();

				/* Expected Call Sequence  */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = DcmAppl_ManufacturerNotification(&SID, &RequestData, &DataSize, &ReqType, &ConnectionId, &ErrorCode, &ProtocolType, TesterSourceAddress);

				/* Test case checks */
				CHECK_U_CHAR(returnValue, E_OK);
				CHECK_U_CHAR(SID, 0x00);
				CHECK_U_CHAR(ReqType, 0x01);
				CHECK_U_INT(TesterSourceAddress, DCOM_SECOND_TESTER);
				CHECK_U_CHAR(RequestData, 0x47);
			    CHECK_U_CHAR(ConnectionId, 0x00);
				CHECK_U_CHAR(ErrorCode, 0x00);
			    CHECK_U_CHAR(ProtocolType, 0x00);

				/* Checks on global data */

				END_CALLS();
			END_STEP();
				}

				START_STEP("2_NTS", true);
				initialise_expected_global_data();
				{
				/* Test case data declarations */

				uint8 SID = 0;
				uint8 buffer_RequestData = 0x01 ;
				const uint8 * RequestData = &buffer_RequestData;
				uint32 DataSize = 0;
				Dcm_NegativeResponseCodeType  ErrorCode = DCOM_FIRST_TESTER;
				Std_ReturnType returnValue;
				uint16 TesterSourceAddress  = DCOM_FIRST_TESTER;
				uint8 ReqType = 0x01;
				uint16 ConnectionId = 0;
				Dcm_ProtocolType ProtocolType = 0x00;
				dcom_Requested_Tester = DCOM_FIRST_TESTER;

				/* Set expected values for global data checks */
				initialise_expected_global_data();

				/* Expected Call Sequence  */
				EXPECTED_CALLS("");

				/* Call SUT */
				returnValue = DcmAppl_ManufacturerNotification(&SID, &RequestData, &DataSize, &ReqType, &ConnectionId, &ErrorCode, &ProtocolType, TesterSourceAddress);

				/* Test case checks */
				CHECK_U_CHAR(returnValue, E_OK);
				CHECK_U_CHAR(SID, 0x00);
				CHECK_U_CHAR(ReqType, 0x01);
				CHECK_U_INT(TesterSourceAddress, DCOM_FIRST_TESTER);
				CHECK_U_CHAR(RequestData, 0x35);
			    CHECK_U_CHAR(ConnectionId, 0x00);
				CHECK_U_CHAR(ErrorCode, 0x00);
			    CHECK_U_CHAR(ProtocolType, 0x00);
				/* Checks on global data */

				END_CALLS();
			END_STEP();
                }
#endif
    END_TEST();
    }}
#endif

void ut_ServiceRequestNotification_Dcm_Coding_Confirmation(int doIt)
{
	if (doIt)
	{
		Std_ReturnType retValue = RTE_E_OK;
		START_TEST("49431: [MMP2.11]UTC_ServiceRequestNotification_Dcm_Coding_Confirmation",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49431");

		/* Test steps*/
		START_STEP("1_NTS", true);
		{
			/*initialise_globals*/
			uint8 SID = 0x00;
			uint8 ReqType = 0x00;
			uint16 ConnectionId = 0x00;
			Dcm_ConfirmationStatusType ConfirmationStatus = 0x00;
			Dcm_ProtocolType ProtocolType = 0x00;
			uint16 TesterSourceAddress = 0x00;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Ssa_Coding_ServiceRequestNotification_Confirmation#default");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_Coding_Confirmation(SID,ReqType,ConnectionId,ConfirmationStatus,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x00);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_CHAR(ConfirmationStatus, 0x00);
			CHECK_U_INT(TesterSourceAddress, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);
		    END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_ServiceRequestNotification_Dcm_Coding_Indication(int doIt)
{
	if (doIt)
	{
		Std_ReturnType retValue = RTE_E_OK;
		/*initialise_globals*/
		uint8 SID = 0x00;
		uint8 RequestData = 0x00;
		uint32 DataSize = 0x00;
		uint8 ReqType = 0x00;
		uint16 ConnectionId = 0x00;
		Dcm_NegativeResponseCodeType ErrorCode = 0x00;
		Dcm_ProtocolType ProtocolType = 0x00;
		uint16 TesterSourceAddress = 0x00;
		START_TEST("49432: [MMP2.11]UTC_ServiceRequestNotification_Dcm_Coding_Indication",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49432");

#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
		/* Test steps*/
		START_STEP("1_NTS", true);
		{
            /*initial conditions*/
			TesterSourceAddress = DCOM_SECOND_TESTER;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Ssa_Coding_ServiceRequestNotification_Indication#default");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_Coding_Indication(SID,RequestData,DataSize,ReqType,ConnectionId,ErrorCode,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x00);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_INT(TesterSourceAddress, DCOM_SECOND_TESTER);
			CHECK_U_CHAR(RequestData, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
			CHECK_U_CHAR(ErrorCode, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);
		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("2_NTS", true);
		{
            /*initial conditions*/
			TesterSourceAddress = DCOM_FIRST_TESTER;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Ssa_Coding_ServiceRequestNotification_Indication#default_1");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_Coding_Indication(SID,RequestData,DataSize,ReqType,ConnectionId,ErrorCode,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x00);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_INT(TesterSourceAddress, DCOM_FIRST_TESTER);
			CHECK_U_CHAR(RequestData, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
			CHECK_U_CHAR(ErrorCode, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);
		    END_CALLS();
			END_STEP();
		}
#endif
		END_TEST();
	}
}

void ut_ServiceRequestNotification_Dcm_RightsM_Confirmation(int doIt)
{
	if (doIt)
	{
		Std_ReturnType retValue = RTE_E_OK;

		START_TEST("49433: [MMP2.11]UTC_ServiceRequestNotification_Dcm_RightsM_Confirmation",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49433");

			/*initialise_globals*/
		    uint8 SID = 0x00;
			uint8 ReqType = 0x00;
			uint16 ConnectionId = 0x00;
			Dcm_ConfirmationStatusType ConfirmationStatus = 0x00;
			Dcm_ProtocolType ProtocolType = 0x00;
			uint16 TesterSourceAddress = 0x00;

#if(RBFS_HSWSimulation != RBFS_HSWSimulation_ON)
			/* Test steps*/
			START_STEP("1_NTS", true);
			{
			SID = 0x80;
			rba_DcmPma_PlantModeStatus_b = TRUE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_RightsM_Confirmation(SID,ReqType,ConnectionId,ConfirmationStatus,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x80);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_CHAR(ConfirmationStatus, 0x00);
			CHECK_U_INT(TesterSourceAddress, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);
		    END_CALLS();
			END_STEP();
		    }

			/* Test steps*/
			START_STEP("2_NTS", true);
			{
			SID = 0x00;
			rba_DcmPma_PlantModeStatus_b = TRUE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_RightsM_Confirmation(SID,ReqType,ConnectionId,ConfirmationStatus,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x00);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_CHAR(ConfirmationStatus, 0x00);
			CHECK_U_INT(TesterSourceAddress, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);
		    END_CALLS();
			END_STEP();
		    }

			/* Test steps*/
			START_STEP("3_NTS", true);
			{
			SID = 0x80;
			rba_DcmPma_PlantModeStatus_b = FALSE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_RightsM_Confirmation(SID,ReqType,ConnectionId,ConfirmationStatus,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x80);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_CHAR(ConfirmationStatus, 0x00);
			CHECK_U_INT(TesterSourceAddress, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);
		    END_CALLS();
			END_STEP();
		    }

			/* Test steps*/
			START_STEP("4_NTS", true);
			{
			SID = 0x00;
			rba_DcmPma_PlantModeStatus_b = FALSE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Ssa_RightsM_ServiceRequestNotification_Confirmation#default");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_RightsM_Confirmation(SID,ReqType,ConnectionId,ConfirmationStatus,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x00);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_CHAR(ConfirmationStatus, 0x00);
			CHECK_U_INT(TesterSourceAddress, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);
		    END_CALLS();
			END_STEP();
		    }
#else
			/* Test steps*/
			START_STEP("5_NTS", true);
			{

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_RightsM_Confirmation(SID,ReqType,ConnectionId,ConfirmationStatus,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x00);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_CHAR(ConfirmationStatus, 0x00);
			CHECK_U_INT(TesterSourceAddress, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);
		    END_CALLS();
			END_STEP();
		    }
#endif
			/* Test steps*/
			START_STEP("6_NTS", true);
			{

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Ssa_RightsM_ServiceRequestNotification_Confirmation#default");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_RightsM_Confirmation(SID,ReqType,ConnectionId,ConfirmationStatus,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x00);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_CHAR(ConfirmationStatus, 0x00);
			CHECK_U_INT(TesterSourceAddress, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);
		    END_CALLS();
			END_STEP();
		    }
		END_TEST();
	}
}

void ut_ServiceRequestNotification_Dcm_RightsM_Indication(int doIt)
{
	if (doIt)
	{
		Std_ReturnType retValue = RTE_E_OK;

		START_TEST("49434: [MMP2.11]UTC_ServiceRequestNotification_Dcm_RightsM_Indication",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49434");

			/*initialise_globals*/
		    uint8 SID = 0x00;
			uint8 RequestData = 0x00;
			uint32 DataSize = 0x00;
			uint8 ReqType = 0x00;
			uint16 ConnectionId = 0x00;
			Dcm_NegativeResponseCodeType ErrorCode = 0x00;
			Dcm_ProtocolType ProtocolType = 0x00;
			uint16 TesterSourceAddress = 0x00;

#if(RBFS_HSWSimulation != RBFS_HSWSimulation_ON)
			/* Test steps*/
			START_STEP("1_NTS", true);
			{
			SID = 0x80;
			rba_DcmPma_PlantModeStatus_b = TRUE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_RightsM_Indication(SID,RequestData,DataSize,ReqType,ConnectionId,ErrorCode,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x80);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_INT(TesterSourceAddress, 0x00);
			CHECK_U_CHAR(RequestData, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
			CHECK_U_CHAR(ErrorCode, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);
		    END_CALLS();
			END_STEP();
		    }

			/* Test steps*/
			START_STEP("2_NTS", true);
			{
			SID = 0x00;
			rba_DcmPma_PlantModeStatus_b = TRUE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_RightsM_Indication(SID,RequestData,DataSize,ReqType,ConnectionId,ErrorCode,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x00);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_INT(TesterSourceAddress, 0x00);
			CHECK_U_CHAR(RequestData, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
			CHECK_U_CHAR(ErrorCode, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);

		    END_CALLS();
			END_STEP();
		    }

			/* Test steps*/
			START_STEP("3_NTS", true);
			{
			SID = 0x80;
			rba_DcmPma_PlantModeStatus_b = FALSE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_RightsM_Indication(SID,RequestData,DataSize,ReqType,ConnectionId,ErrorCode,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x80);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_INT(TesterSourceAddress, 0x00);
			CHECK_U_CHAR(RequestData, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
			CHECK_U_CHAR(ErrorCode, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);

		    END_CALLS();
			END_STEP();
		    }

			/* Test steps*/
			START_STEP("4_NTS", true);
			{
			SID = 0x00;
			rba_DcmPma_PlantModeStatus_b = FALSE;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Ssa_RightsM_ServiceRequestNotification_Indication#default_2");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_RightsM_Indication(SID,RequestData,DataSize,ReqType,ConnectionId,ErrorCode,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x00);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_INT(TesterSourceAddress, 0x00);
			CHECK_U_CHAR(RequestData, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
			CHECK_U_CHAR(ErrorCode, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);

		    END_CALLS();
			END_STEP();
		    }
#else
			/* Test steps*/
			START_STEP("5_NTS", true);
			{

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_RightsM_Indication(SID,RequestData,DataSize,ReqType,ConnectionId,ErrorCode,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x00);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_INT(TesterSourceAddress, 0x00);
			CHECK_U_CHAR(RequestData, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
			CHECK_U_CHAR(ErrorCode, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);

		    END_CALLS();
			END_STEP();
		    }
#endif
			/* Test steps*/
			START_STEP("6_NTS", true);
			{

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Ssa_RightsM_ServiceRequestNotification_Indication#default_2");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_RightsM_Indication(SID,RequestData,DataSize,ReqType,ConnectionId,ErrorCode,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x00);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_INT(TesterSourceAddress, 0x00);
			CHECK_U_CHAR(RequestData, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
			CHECK_U_CHAR(ErrorCode, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);

		    END_CALLS();
			END_STEP();
		    }

#if (RBFS_DcomSecondTesterSupport != RBFS_DcomSecondTesterSupport_OFF)
		/* Test steps*/
		START_STEP("7_NTS", true);
		{
            /*initial conditions*/
			TesterSourceAddress = DCOM_SECOND_TESTER;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Ssa_RightsM_ServiceRequestNotification_Indication#default");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_RightsM_Indication(SID,RequestData,DataSize,ReqType,ConnectionId,ErrorCode,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x00);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_INT(TesterSourceAddress, DCOM_SECOND_TESTER);
			CHECK_U_CHAR(RequestData, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
			CHECK_U_CHAR(ErrorCode, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);

		    END_CALLS();
			END_STEP();
		}

		/* Test steps*/
		START_STEP("8_NTS", true);
		{
            /*initial conditions*/
			TesterSourceAddress = DCOM_FIRST_TESTER;

			/* Expected Call Sequence  */
			EXPECTED_CALLS("Ssa_RightsM_ServiceRequestNotification_Indication#default_1");

			/* Call SUT */
			retValue = ServiceRequestNotification_Dcm_RightsM_Indication(SID,RequestData,DataSize,ReqType,ConnectionId,ErrorCode,ProtocolType,TesterSourceAddress);

			/* Test step checks */
			CHECK_U_CHAR(retValue, RTE_E_OK);
			CHECK_U_CHAR(SID, 0x00);
			CHECK_U_CHAR(ReqType, 0x00);
			CHECK_U_INT(TesterSourceAddress, DCOM_FIRST_TESTER);
			CHECK_U_CHAR(RequestData, 0x00);
		    CHECK_U_CHAR(ConnectionId, 0x00);
			CHECK_U_CHAR(ErrorCode, 0x00);
		    CHECK_U_CHAR(ProtocolType, 0x00);

		    END_CALLS();
			END_STEP();
		}
#endif
		END_TEST();
	}
}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function Ssa_Coding_ServiceRequestNotification_Confirmation */
Std_ReturnType Ssa_Coding_ServiceRequestNotification_Confirmation(uint8 SID,
                                                                  uint8 ReqType,
                                                                  uint16 SourceAddress,
                                                                  Dcm_ConfirmationStatusType ConfirmationStatus){
    REGISTER_CALL("Ssa_Coding_ServiceRequestNotification_Confirmation");

    IF_INSTANCE("default") {
    	CHECK_U_CHAR(SID,0x00);
    	CHECK_U_CHAR(ReqType,0x00);
    	CHECK_U_INT(SourceAddress,0x00);
    	CHECK_U_CHAR(ConfirmationStatus,0x00);
        return CANTATA_DEFAULT_VALUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function Ssa_Coding_ServiceRequestNotification_Indication */
Std_ReturnType Ssa_Coding_ServiceRequestNotification_Indication(uint8 SID,
                                                                const uint8 * RequestData,
                                                                uint32 DataSize,
                                                                uint8 ReqType,
                                                                uint16 SourceAddress,
                                                                Dcm_NegativeResponseCodeType * ErrorCode){
    REGISTER_CALL("Ssa_Coding_ServiceRequestNotification_Indication");

    IF_INSTANCE("default") {
    	CHECK_U_CHAR(SID,0x00);
    	CHECK_U_CHAR(RequestData,0x00);
    	CHECK_U_INT(DataSize,0x00);
    	CHECK_U_CHAR(ReqType,0x00);
    	CHECK_U_INT(SourceAddress,DCOM_SECOND_TESTER);
    	CHECK_U_CHAR(ErrorCode,0x00);
        return CANTATA_DEFAULT_VALUE;
    }
    IF_INSTANCE("default_1") {
    	CHECK_U_CHAR(SID,0x00);
    	CHECK_U_CHAR(RequestData,0x00);
    	CHECK_U_INT(DataSize,0x00);
    	CHECK_U_CHAR(ReqType,0x00);
    	CHECK_U_INT(SourceAddress,DCOM_FIRST_TESTER);
    	CHECK_U_CHAR(ErrorCode,0x00);
        return CANTATA_DEFAULT_VALUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function Ssa_RightsM_ServiceRequestNotification_Confirmation */
Std_ReturnType Ssa_RightsM_ServiceRequestNotification_Confirmation(uint8 SID,
                                                                   uint8 ReqType,
                                                                   uint16 SourceAddress,
                                                                   Dcm_ConfirmationStatusType ConfirmationStatus){
    REGISTER_CALL("Ssa_RightsM_ServiceRequestNotification_Confirmation");

    IF_INSTANCE("default") {
    	CHECK_U_CHAR(SID,0x00);
    	CHECK_U_CHAR(ReqType,0x00);
    	CHECK_U_INT(SourceAddress,0x00);
    	CHECK_U_CHAR(ConfirmationStatus,0x00);
        return CANTATA_DEFAULT_VALUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function Ssa_RightsM_ServiceRequestNotification_Indication */
Std_ReturnType Ssa_RightsM_ServiceRequestNotification_Indication(uint8 SID,
                                                                 const uint8 * RequestData,
                                                                 uint32 DataSize,
                                                                 uint8 ReqType,
                                                                 uint16 SourceAddress,
                                                                 Dcm_NegativeResponseCodeType * ErrorCode){
    REGISTER_CALL("Ssa_RightsM_ServiceRequestNotification_Indication");

    IF_INSTANCE("default") {
    	CHECK_U_CHAR(SID,0x00);
    	CHECK_U_CHAR(RequestData,0x00);
    	CHECK_U_INT(DataSize,0x00);
    	CHECK_U_CHAR(ReqType,0x00);
    	CHECK_U_INT(SourceAddress,DCOM_SECOND_TESTER);
    	CHECK_U_CHAR(ErrorCode,0x00);
        return CANTATA_DEFAULT_VALUE;
    }
    IF_INSTANCE("default_1") {
    	CHECK_U_CHAR(SID,0x00);
    	CHECK_U_CHAR(RequestData,0x00);
    	CHECK_U_INT(DataSize,0x00);
    	CHECK_U_CHAR(ReqType,0x00);
    	CHECK_U_INT(SourceAddress,DCOM_FIRST_TESTER);
    	CHECK_U_CHAR(ErrorCode,0x00);
        return CANTATA_DEFAULT_VALUE;
    }
    IF_INSTANCE("default_2") {
    	CHECK_U_CHAR(SID,0x00);
    	CHECK_U_CHAR(RequestData,0x00);
    	CHECK_U_INT(DataSize,0x00);
    	CHECK_U_CHAR(ReqType,0x00);
    	CHECK_U_INT(SourceAddress,0x00);
    	CHECK_U_CHAR(ErrorCode,0x00);
        return CANTATA_DEFAULT_VALUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
