/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_CustIf_ECU_Stat_IMU_A_ST3.c
 *    Author: XEK1KOR
 *    Generated on: 16-Sep-2022 13:13:52
 *    Generated from: rbl_CustIf_ECU_Stat_IMU_A_ST3.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "../../../../../../rbl/mmp2/cust/mb/rbl_CustIf/src/rbl_CustIf_Hndl_Utils.h"
#include "rbl_CustIf_ECU_Stat_IMU_A_ST3.h"

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
uint8 Com_SendSignal(Com_SignalIdType idSignal_u16, const void * signalDataPtr_pcv);

/* Global data */
/* None */

/* Expected variables for global data */
/* None */

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    /* No global data */
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    /* No global data */
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    /* No global data */
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_CustIf_ECU_Stat_IMU_A_ST3_PDU_Update(int );
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
    OPEN_LOG("ut_rbl_CustIf_ECU_Stat_IMU_A_ST3.ctr", false, 100);
    START_SCRIPT("rbl_CustIf_ECU_Stat_IMU_A_ST3", true);

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
	ut_rbl_CustIf_ECU_Stat_IMU_A_ST3_PDU_Update(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_CustIf_ECU_Stat_IMU_A_ST3.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rbl_CustIf_ECU_Stat_IMU_A_ST3_PDU_Update(int doIt)
{

	if (doIt)
	{


		START_TEST("46998: UTC_rbl_CustIf_ECU_Stat_IMU_A_ST3_PDU_Update",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47965");

		START_STEP("1_NTS", TRUE);
		{

			// Expected Call Sequence
			EXPECTED_CALLS("1*Com_SendSignal#Com_SendSignal_imu_ECU_Id_IMU_A_ST3\
								1*Com_SendSignal#Com_SendSignal_imu_NwId_Rsrv_ST3\
								1*Com_SendSignal#Com_SendSignal_imu_WakeupRsn_IMU_A_ST3\
								1*Com_SendSignal#Com_SendSignal_imu_Awake_Diag_Actv_IMU_A_ST3\
								1*Com_SendSignal#Com_SendSignal_imu_Awake_NwStart_IMU_A_ST3");


			// Call SUT
			rbl_CustIf_ECU_Stat_IMU_A_ST3_PDU_Update();
			// Test case checks


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
#if (RBFS_MMP2 == RBFS_MMP2_IMUA)
    IF_INSTANCE("Com_SendSignal_imu_ECU_Id_IMU_A_ST3") {

    	CHECK_U_INT(idSignal_u16,ComConf_ComSignal_S_ECU_Id_IMU_A_ST3_HAD_BACKUP_CAN_Tx);
    	CHECK_U_INT (*(uint16*) signalDataPtr_pcv,0x16A);
        return 0;
    }
    IF_INSTANCE("Com_SendSignal_imu_NwId_Rsrv_ST3") {

    	CHECK_U_INT(idSignal_u16,ComConf_ComSignal_S_NwId_Rsrv_ST3_HAD_BACKUP_CAN_Tx);
    	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0);
        return 0;
    }
    IF_INSTANCE("Com_SendSignal_imu_WakeupRsn_IMU_A_ST3") {

    	CHECK_U_INT(idSignal_u16,ComConf_ComSignal_S_WakeupRsn_IMU_A_ST3_HAD_BACKUP_CAN_Tx);
    	CHECK_U_INT (*(uint16*) signalDataPtr_pcv,RBL_CUSTIF_WAKEUPRSN_ST3_NETWORK);
        return 0;
    }
    IF_INSTANCE("Com_SendSignal_imu_Awake_Diag_Actv_IMU_A_ST3") {

    	CHECK_U_INT(idSignal_u16,ComConf_ComSignal_S_Awake_Diag_Actv_IMU_A_ST3_HAD_BACKUP_CAN_Tx);
    	CHECK_BOOLEAN (*(uint8*) signalDataPtr_pcv,FALSE);
    	signalDataPtr_pcv = (void *)0x1;
        return 0;
    }

    IF_INSTANCE("Com_SendSignal_imu_Awake_NwStart_IMU_A_ST3") {

    	CHECK_U_INT(idSignal_u16,ComConf_ComSignal_S_Awake_NwStart_IMU_A_ST3_HAD_BACKUP_CAN_Tx);
    	CHECK_BOOLEAN (*(uint8*) signalDataPtr_pcv,FALSE);
        return 0;
    }

#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
    IF_INSTANCE("Com_SendSignal_imu_ECU_Id_IMU_A_ST3") {

    	CHECK_U_INT(idSignal_u16,ComConf_ComSignal_S_ECU_Id_IMU_B_ST3_HAD_IMU_CAN_Tx);
    	CHECK_U_INT (*(uint16*) signalDataPtr_pcv,0x16B);
        return 0;
    }
    IF_INSTANCE("Com_SendSignal_imu_NwId_Rsrv_ST3") {

    	CHECK_U_INT(idSignal_u16,ComConf_ComSignal_S_NwId_HAD_IMU_ST3_CAN_Tx);
    	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0);
        return 0;
    }
    IF_INSTANCE("Com_SendSignal_imu_WakeupRsn_IMU_A_ST3") {

    	CHECK_U_INT(idSignal_u16,ComConf_ComSignal_S_WakeupRsn_IMU_B_ST3_HAD_IMU_CAN_Tx);
    	CHECK_U_INT (*(uint16*) signalDataPtr_pcv,RBL_CUSTIF_WAKEUPRSN_ST3_NETWORK);
        return 0;
    }
    IF_INSTANCE("Com_SendSignal_imu_Awake_Diag_Actv_IMU_A_ST3") {

    	CHECK_U_INT(idSignal_u16,ComConf_ComSignal_S_Awake_Diag_Actv_IMU_B_ST3_HAD_IMU_CAN_Tx);
    	CHECK_BOOLEAN (*(uint8*) signalDataPtr_pcv,FALSE);
        return 0;
    }

    IF_INSTANCE("Com_SendSignal_imu_Awake_NwStart_IMU_A_ST3") {

    	CHECK_U_INT(idSignal_u16,ComConf_ComSignal_S_Awake_NwStart_IMU_B_ST3_HAD_IMU_CAN_Tx);
    	CHECK_BOOLEAN (*(uint8*) signalDataPtr_pcv,FALSE);
        return 0;
    }
#endif
    IF_INSTANCE("default") {
        return CANTATA_DEFAULT_VALUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
