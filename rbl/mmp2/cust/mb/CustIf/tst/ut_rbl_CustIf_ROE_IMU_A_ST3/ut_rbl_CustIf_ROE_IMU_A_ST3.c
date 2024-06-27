/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_CustIf_ROE_IMU_A_ST3.c
 *    Author: GDEV1KOR
 *    Generated on: 15-Apr-2024 08:21:55
 *    Generated from: rbl_CustIf_ROE_IMU_A_ST3.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "rbl_CustIf_ROE_IMU_A_ST3.h"

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
void ut_rbl_CustIf_ROE_IMU_A_ST3_PDU_Update(int);
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
    OPEN_LOG("ut_rbl_CustIf_ROE_IMU_A_ST3.ctr", false, 100);
    START_SCRIPT("rbl_CustIf_ROE_IMU_A_ST3", true);

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
	ut_rbl_CustIf_ROE_IMU_A_ST3_PDU_Update(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_CustIf_ROE_IMU_A_ST3.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rbl_CustIf_ROE_IMU_A_ST3_PDU_Update(int doIt)
{
	if (doIt)
	{
		// Test case data declarations
		SwcDiag_RoERecordType RoERecord_ST3;

		START_TEST("48731: [MMP2.11]UTC_rbl_CustIf_ROE_IMU_A_ST3_PDU_Update",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48731");

		START_STEP("1_NTS", TRUE);
		{
			//INITIAL CONDITIONS
			RoERecord_ST3.ROE_0 = 0x10;
			RoERecord_ST3.ROE_1 = 0x20;
			RoERecord_ST3.ROE_2 = 0x30;
			RoERecord_ST3.ROE_3 = 0x40;
			RoERecord_ST3.ROE_4 = 0x50;
			RoERecord_ST3.ROE_5 = 0x60;
			RoERecord_ST3.ROE_6 = 0x70;
			RoERecord_ST3.ROE_7 = 0x80;

			//Expected Call Sequence
			EXPECTED_CALLS("Com_SendSignal#Com_SendSignal_0;\
					        Com_SendSignal#Com_SendSignal_1;\
					        Com_SendSignal#Com_SendSignal_2;\
					        Com_SendSignal#Com_SendSignal_3;\
					        Com_SendSignal#Com_SendSignal_4;\
					        Com_SendSignal#Com_SendSignal_5;\
					        Com_SendSignal#Com_SendSignal_6;\
					        Com_SendSignal#Com_SendSignal_7;\
					        Com_SendSignalGroup#Update_SendSignalGroup");

			// Call SUT
			rbl_CustIf_ROE_IMU_A_ST3_PDU_Update(RoERecord_ST3);

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

    IF_INSTANCE("Com_SendSignal_0")
              {
        	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
              	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_0_IMU_A_ST3_HAD_BACKUP_CAN_Tx);
              	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x10);

        		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
        		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_0_IMU_B_ST3_IMU_INTERNAL_CAN_Tx);
        		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x10);
        		#endif

                  return 0x00;
              }

              IF_INSTANCE("Com_SendSignal_1")
              {
        	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
              	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_1_IMU_A_ST3_HAD_BACKUP_CAN_Tx);
              	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x20);
        		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
        		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_1_IMU_B_ST3_IMU_INTERNAL_CAN_Tx);
        		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x20);
        		#endif
                  return 0x00;
              }

              IF_INSTANCE("Com_SendSignal_2")
              {
        	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
              	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_2_IMU_A_ST3_HAD_BACKUP_CAN_Tx);
            	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x30);
        		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
        		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_2_IMU_B_ST3_IMU_INTERNAL_CAN_Tx);
        		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x30);
        		#endif
                  return 0x00;
              }

              IF_INSTANCE("Com_SendSignal_3")
              {
        	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
              	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_3_IMU_A_ST3_HAD_BACKUP_CAN_Tx);
            	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x40);
        		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
        		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_3_IMU_B_ST3_IMU_INTERNAL_CAN_Tx);
        		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x40);
        		#endif
                  return 0x00;
              }

              IF_INSTANCE("Com_SendSignal_4")
              {
        	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
              	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_4_IMU_A_ST3_HAD_BACKUP_CAN_Tx);
            	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x50);
        		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
        		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_4_IMU_B_ST3_IMU_INTERNAL_CAN_Tx);
        		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x50);
        		#endif
                  return 0x00;
              }

              IF_INSTANCE("Com_SendSignal_5")
              {
        	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
              	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_5_IMU_A_ST3_HAD_BACKUP_CAN_Tx);
            	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x60);
        		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
        		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_5_IMU_B_ST3_IMU_INTERNAL_CAN_Tx);
        		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x60);
        		#endif
                  return 0x00;
              }

              IF_INSTANCE("Com_SendSignal_6")
              {
        	    #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
              	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_6_IMU_A_ST3_HAD_BACKUP_CAN_Tx);
            	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x70);
        		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
        		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_6_IMU_B_ST3_IMU_INTERNAL_CAN_Tx);
        		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x70);
        		#endif
                  return 0x00;
              }

              IF_INSTANCE("Com_SendSignal_7")
              {
        	     #if (RBFS_MMP2 == RBFS_MMP2_IMUA)
              	CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_7_IMU_A_ST3_HAD_BACKUP_CAN_Tx);
            	CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x80);
        		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
        		CHECK_U_INT(idSignal_u16, ComConf_ComGroupSignal_GS_ROE_7_IMU_B_ST3_IMU_INTERNAL_CAN_Tx);
        		CHECK_U_INT (*(uint8*) signalDataPtr_pcv,0x80);
        		#endif
                  return 0x00;
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
        	CHECK_U_INT(idSignalGroup_u16, ComConf_ComSignalGroup_SG_ROE_IMU_A_ST3_edm6y60q0qq6e5iaka50e3c31_HAD_BACKUP_CAN_Tx);
    		#elif (RBFS_MMP2 == RBFS_MMP2_IMUB)
    		CHECK_U_INT(idSignalGroup_u16, ComConf_ComSignalGroup_SG_ROE_IMU_B_ST3_7zavpp3siu6s2eitdaqxg7lwg_IMU_INTERNAL_CAN_Tx);
    		#endif
            return 0x00;
        }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
