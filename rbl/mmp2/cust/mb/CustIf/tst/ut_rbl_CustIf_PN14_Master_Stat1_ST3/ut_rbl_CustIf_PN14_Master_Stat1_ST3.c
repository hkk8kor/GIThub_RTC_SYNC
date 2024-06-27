/*****************************************************************************/
/*                            Cantata Test Script                            */
/*****************************************************************************/
/*
 *    Filename: ut_rbl_CustIf_PN14_Master_Stat1_ST3.c
 *    Author: GDEV1KOR
 *    Generated on: 14-Apr-2024 14:57:40
 *    Generated from: rbl_CustIf_PN14_Master_Stat1_ST3.c
 */
/*****************************************************************************/
/* Environment Definition                                                    */
/*****************************************************************************/

#define TEST_SCRIPT_GENERATOR 2

/* Include files from software under test */
#include "rbl_CustIf_PN14_Master_Stat1_ST3.h"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
#include "Rte_rbl_CustIf.h"
#endif

#define CANTATA_DEFAULT_VALUE 0 /* Default value of variables & stub returns */

#include <cantpp.h>  /* Cantata Directives */
/* pragma qas cantata testscript start */
/*****************************************************************************/
/* Global Data Definitions                                                   */
/*****************************************************************************/

/* Global Functions */
extern void ACCESS_FUNCTION_rbl_CustIf_PN14_Master_Stat1_ST3_RBSYS_EnterCommonLockSysfast();
extern void ACCESS_FUNCTION_rbl_CustIf_PN14_Master_Stat1_ST3_RBSYS_ExitCommonLockSysfast();
void RBSYS_EnterCommonLockSysfast_intern();
void RBSYS_ExitCommonLockSysfast_intern();
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);
Std_ReturnType Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3(Ssa_PowernetMgmtStateType data);

/* Global data */
extern volatile RBMESG_Type_PN14_TransMd_Stat_ST3 RBMESG_PN14_TransMd_Stat_ST3;
extern volatile RBMESG_Type_PN14_DDP_Sw_Stat_ST3 RBMESG_PN14_DDP_Sw_Stat_ST3;
extern volatile RBMESG_Type_PN14_ProdMd_Stat_ST3 RBMESG_PN14_ProdMd_Stat_ST3;
extern volatile RBMESG_Type_PN14_ProdMd_BatStat_ST3 RBMESG_PN14_ProdMd_BatStat_ST3;
extern volatile RBMESG_Type_PN14_SupBat_Stat_ST3 RBMESG_PN14_SupBat_Stat_ST3;
extern volatile RBMESG_Type_PN14_SupBat_Volt_ST3 RBMESG_PN14_SupBat_Volt_ST3;
extern volatile RBMESG_Type_PN14_SupBat_Curr_ST3 RBMESG_PN14_SupBat_Curr_ST3;
extern volatile RBMESG_Type_PN14_SupBat_Temp_ST3 RBMESG_PN14_SupBat_Temp_ST3;
extern volatile RBMESG_Type_PN14_PNSec_RechargeEnable_ST3 RBMESG_PN14_PNSec_RechargeEnable_ST3;
extern volatile RBMESG_Type_PN14_ExtBat_Charge_Actv_ST3 RBMESG_PN14_ExtBat_Charge_Actv_ST3;
extern volatile RBMESG_Type_PN14_DDP_Sw2_Stat_ST3 RBMESG_PN14_DDP_Sw2_Stat_ST3;
extern volatile RBMESG_Type_rbl_CustIf_PN14_TransMd_Stat_ST3 RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3;
extern volatile RBMESG_Type_rbl_CustIf_PN14_ProdMd_Stat_ST3 RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3;
extern volatile RBMESG_Type_rbl_CustIf_PN14_SupBat_Volt_ST3 RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3;
extern volatile RBMESG_Type_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3;
extern volatile RBMESG_Type_rbl_CustIf_PN14_ProdMd_BatStat_ST3 RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3;
extern volatile RBMESG_Type_rbl_CustIf_PN14_SupBat_Stat_ST3 RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3;
extern volatile RBMESG_Type_rbl_CustIf_PN14_SupBat_Curr_ST3 RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3;
extern volatile RBMESG_Type_rbl_CustIf_PN14_SupBat_Temp_ST3 RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3;
extern volatile RBMESG_Type_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3;
extern volatile RBMESG_Type_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3;
extern volatile RBMESG_Type_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3;
typedef struct rbl_CustIf_PN14_Master_Stat1_ST3_av_struct { boolean * ref_rbl_CustIf_Pn14_Signal_Timeout; } rbl_CustIf_PN14_Master_Stat1_ST3_av_struct;
extern rbl_CustIf_PN14_Master_Stat1_ST3_av_struct av_rbl_CustIf_PN14_Master_Stat1_ST3;

/* Expected variables for global data */
RBMESG_Type_PN14_TransMd_Stat_ST3 expected_RBMESG_PN14_TransMd_Stat_ST3;
RBMESG_Type_PN14_DDP_Sw_Stat_ST3 expected_RBMESG_PN14_DDP_Sw_Stat_ST3;
RBMESG_Type_PN14_ProdMd_Stat_ST3 expected_RBMESG_PN14_ProdMd_Stat_ST3;
RBMESG_Type_PN14_ProdMd_BatStat_ST3 expected_RBMESG_PN14_ProdMd_BatStat_ST3;
RBMESG_Type_PN14_SupBat_Stat_ST3 expected_RBMESG_PN14_SupBat_Stat_ST3;
RBMESG_Type_PN14_SupBat_Volt_ST3 expected_RBMESG_PN14_SupBat_Volt_ST3;
RBMESG_Type_PN14_SupBat_Curr_ST3 expected_RBMESG_PN14_SupBat_Curr_ST3;
RBMESG_Type_PN14_SupBat_Temp_ST3 expected_RBMESG_PN14_SupBat_Temp_ST3;
RBMESG_Type_PN14_PNSec_RechargeEnable_ST3 expected_RBMESG_PN14_PNSec_RechargeEnable_ST3;
RBMESG_Type_PN14_ExtBat_Charge_Actv_ST3 expected_RBMESG_PN14_ExtBat_Charge_Actv_ST3;
RBMESG_Type_PN14_DDP_Sw2_Stat_ST3 expected_RBMESG_PN14_DDP_Sw2_Stat_ST3;
RBMESG_Type_rbl_CustIf_PN14_TransMd_Stat_ST3 expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3;
RBMESG_Type_rbl_CustIf_PN14_ProdMd_Stat_ST3 expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3;
RBMESG_Type_rbl_CustIf_PN14_SupBat_Volt_ST3 expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3;
RBMESG_Type_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3;
RBMESG_Type_rbl_CustIf_PN14_ProdMd_BatStat_ST3 expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3;
RBMESG_Type_rbl_CustIf_PN14_SupBat_Stat_ST3 expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3;
RBMESG_Type_rbl_CustIf_PN14_SupBat_Curr_ST3 expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3;
RBMESG_Type_rbl_CustIf_PN14_SupBat_Temp_ST3 expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3;
RBMESG_Type_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3;
RBMESG_Type_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3;
RBMESG_Type_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3;
typedef struct expected_rbl_CustIf_PN14_Master_Stat1_ST3_av_struct { boolean ref_rbl_CustIf_Pn14_Signal_Timeout; } expected_rbl_CustIf_PN14_Master_Stat1_ST3_av_struct;
expected_rbl_CustIf_PN14_Master_Stat1_ST3_av_struct expected_av_rbl_CustIf_PN14_Master_Stat1_ST3;

/* This function initialises global data to default values. This function       */
/* is called by every test case so must not contain test case specific settings */
static void initialise_global_data(){
    INITIALISE(ACCESS_VARIABLE(rbl_CustIf_PN14_Master_Stat1_ST3, rbl_CustIf_Pn14_Signal_Timeout));
    INITIALISE(RBMESG_PN14_TransMd_Stat_ST3);
    INITIALISE(RBMESG_PN14_DDP_Sw_Stat_ST3);
    INITIALISE(RBMESG_PN14_ProdMd_Stat_ST3);
    INITIALISE(RBMESG_PN14_ProdMd_BatStat_ST3);
    INITIALISE(RBMESG_PN14_SupBat_Stat_ST3);
    INITIALISE(RBMESG_PN14_SupBat_Volt_ST3);
    INITIALISE(RBMESG_PN14_SupBat_Curr_ST3);
    INITIALISE(RBMESG_PN14_SupBat_Temp_ST3);
    INITIALISE(RBMESG_PN14_PNSec_RechargeEnable_ST3);
    INITIALISE(RBMESG_PN14_ExtBat_Charge_Actv_ST3);
    INITIALISE(RBMESG_PN14_DDP_Sw2_Stat_ST3);
    INITIALISE(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
    INITIALISE(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
    INITIALISE(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
    INITIALISE(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
    INITIALISE(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
    INITIALISE(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
    INITIALISE(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
    INITIALISE(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
    INITIALISE(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
    INITIALISE(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
    INITIALISE(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);
}

/* This function copies the global data settings into expected variables for */
/* use in check_global_data(). It is called by every test case so must not   */
/* contain test case specific settings.                                      */
static void initialise_expected_global_data(){
    COPY_TO_EXPECTED(ACCESS_VARIABLE(rbl_CustIf_PN14_Master_Stat1_ST3, rbl_CustIf_Pn14_Signal_Timeout), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PN14_Master_Stat1_ST3, rbl_CustIf_Pn14_Signal_Timeout));
    COPY_TO_EXPECTED(RBMESG_PN14_TransMd_Stat_ST3, expected_RBMESG_PN14_TransMd_Stat_ST3);
    COPY_TO_EXPECTED(RBMESG_PN14_DDP_Sw_Stat_ST3, expected_RBMESG_PN14_DDP_Sw_Stat_ST3);
    COPY_TO_EXPECTED(RBMESG_PN14_ProdMd_Stat_ST3, expected_RBMESG_PN14_ProdMd_Stat_ST3);
    COPY_TO_EXPECTED(RBMESG_PN14_ProdMd_BatStat_ST3, expected_RBMESG_PN14_ProdMd_BatStat_ST3);
    COPY_TO_EXPECTED(RBMESG_PN14_SupBat_Stat_ST3, expected_RBMESG_PN14_SupBat_Stat_ST3);
    COPY_TO_EXPECTED(RBMESG_PN14_SupBat_Volt_ST3, expected_RBMESG_PN14_SupBat_Volt_ST3);
    COPY_TO_EXPECTED(RBMESG_PN14_SupBat_Curr_ST3, expected_RBMESG_PN14_SupBat_Curr_ST3);
    COPY_TO_EXPECTED(RBMESG_PN14_SupBat_Temp_ST3, expected_RBMESG_PN14_SupBat_Temp_ST3);
    COPY_TO_EXPECTED(RBMESG_PN14_PNSec_RechargeEnable_ST3, expected_RBMESG_PN14_PNSec_RechargeEnable_ST3);
    COPY_TO_EXPECTED(RBMESG_PN14_ExtBat_Charge_Actv_ST3, expected_RBMESG_PN14_ExtBat_Charge_Actv_ST3);
    COPY_TO_EXPECTED(RBMESG_PN14_DDP_Sw2_Stat_ST3, expected_RBMESG_PN14_DDP_Sw2_Stat_ST3);
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3, expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3, expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3, expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3, expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3, expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3, expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3, expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3, expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3, expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3, expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
    COPY_TO_EXPECTED(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3, expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);
}

/* This function checks global data against the expected values. */
static void check_global_data(){
    CHECK_BOOLEAN(ACCESS_VARIABLE(rbl_CustIf_PN14_Master_Stat1_ST3, rbl_CustIf_Pn14_Signal_Timeout), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PN14_Master_Stat1_ST3, rbl_CustIf_Pn14_Signal_Timeout));
    CHECK_U_CHAR(RBMESG_PN14_TransMd_Stat_ST3, expected_RBMESG_PN14_TransMd_Stat_ST3);
    CHECK_U_CHAR(RBMESG_PN14_DDP_Sw_Stat_ST3, expected_RBMESG_PN14_DDP_Sw_Stat_ST3);
    CHECK_U_CHAR(RBMESG_PN14_ProdMd_Stat_ST3, expected_RBMESG_PN14_ProdMd_Stat_ST3);
    CHECK_U_CHAR(RBMESG_PN14_ProdMd_BatStat_ST3, expected_RBMESG_PN14_ProdMd_BatStat_ST3);
    CHECK_U_CHAR(RBMESG_PN14_SupBat_Stat_ST3, expected_RBMESG_PN14_SupBat_Stat_ST3);
    CHECK_U_INT(RBMESG_PN14_SupBat_Volt_ST3, expected_RBMESG_PN14_SupBat_Volt_ST3);
    CHECK_U_INT(RBMESG_PN14_SupBat_Curr_ST3, expected_RBMESG_PN14_SupBat_Curr_ST3);
    CHECK_U_CHAR(RBMESG_PN14_SupBat_Temp_ST3, expected_RBMESG_PN14_SupBat_Temp_ST3);
    CHECK_U_CHAR(RBMESG_PN14_PNSec_RechargeEnable_ST3, expected_RBMESG_PN14_PNSec_RechargeEnable_ST3);
    CHECK_U_CHAR(RBMESG_PN14_ExtBat_Charge_Actv_ST3, expected_RBMESG_PN14_ExtBat_Charge_Actv_ST3);
    CHECK_U_CHAR(RBMESG_PN14_DDP_Sw2_Stat_ST3, expected_RBMESG_PN14_DDP_Sw2_Stat_ST3);
    CHECK_U_CHAR(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3, expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
    CHECK_U_CHAR(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3, expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3, expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
    CHECK_U_CHAR(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3, expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
    CHECK_U_CHAR(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3, expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
    CHECK_U_CHAR(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3, expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3, expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
    CHECK_U_CHAR(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3, expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
    CHECK_U_CHAR(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3, expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
    CHECK_U_CHAR(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3, expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
    CHECK_U_CHAR(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3, expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);
}

/* Prototypes for test functions */
void run_tests();
void ut_rbl_CustIf_TimeOut_Cbk_PN14_Master_Stat1_ST3(int);
void ut_rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive(int);
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
    OPEN_LOG("ut_rbl_CustIf_PN14_Master_Stat1_ST3.ctr", false, 100);
    START_SCRIPT("rbl_CustIf_PN14_Master_Stat1_ST3", true);

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
	ut_rbl_CustIf_TimeOut_Cbk_PN14_Master_Stat1_ST3(1);
	ut_rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive(1);
    rule_set("*", "*");
    EXPORT_COVERAGE("ut_rbl_CustIf_PN14_Master_Stat1_ST3.cov", cppca_export_replace);
}

/*****************************************************************************/
/* Test Cases                                                                */
/*****************************************************************************/
void ut_rbl_CustIf_TimeOut_Cbk_PN14_Master_Stat1_ST3(int doIt)
{
	if (doIt)
	{
		START_TEST("49454: [MMP2.11]UTC_rbl_CustIf_TimeOut_Cbk_PN14_Master_Stat1_ST3",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=49454");

		/*initialise_globals*/
		initialise_global_data();
		initialise_expected_global_data();

		/* Test case data declarations */

		/* Test steps*/
		START_STEP("1_NTS", true);
		{
			/* Test case data Initializations */
			ACCESS_VARIABLE(rbl_CustIf_PN14_Master_Stat1_ST3, rbl_CustIf_Pn14_Signal_Timeout) = TRUE;
			ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PN14_Master_Stat1_ST3, rbl_CustIf_Pn14_Signal_Timeout) = ACCESS_VARIABLE(rbl_CustIf_PN14_Master_Stat1_ST3, rbl_CustIf_Pn14_Signal_Timeout);

			/* Expected Call Sequence  */
			EXPECTED_CALLS("");

			/* Call SUT */
			rbl_CustIf_TimeOut_Cbk_PN14_Master_Stat1_ST3();

			/* Test step checks */
			CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PN14_Master_Stat1_ST3, rbl_CustIf_Pn14_Signal_Timeout), ACCESS_EXPECTED_VARIABLE(rbl_CustIf_PN14_Master_Stat1_ST3, rbl_CustIf_Pn14_Signal_Timeout));
			check_global_data();

		    END_CALLS();
			END_STEP();
		}
		END_TEST();
	}
}

void ut_rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive(int doIt)
{
	if (doIt)
	{

		START_TEST("47963: [MMP2.11]UTC_rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive",
				   "https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=47963");


     START_STEP("1_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();
	    ACCESS_VARIABLE(rbl_CustIf_PN14_Master_Stat1_ST3, rbl_CustIf_Pn14_Signal_Timeout) = FALSE;

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 0;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_2;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("2_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_TEMP_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 0;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_TEMP_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_2;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("3_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_ACTV;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 0;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_ACTV;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_2;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("4_NTS", TRUE);
     {

 	    initialise_global_data();
 	    initialise_expected_global_data();

 	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
 	    RBMESG_PN14_TransMd_Stat_ST3 = 3;
 	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
 	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
 	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
 	    RBMESG_PN14_SupBat_Volt_ST3 = 0;
 	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
 	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
 	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
 	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
 	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
 	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

 	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
 	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
 	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
 	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
 	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
 	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
 	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
 	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
 	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
 	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
 	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

 	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_SNA;
 	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
 	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
 	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
 	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 0;
 	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
 	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
 	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
 	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
 	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
 	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

 	    // Expected Call Sequence
 	   EXPECTED_CALLS("Dem_SetEventStatus#Stub_1;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

 	    // Call SUT
 	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

 	    // Test case checks
 	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
 	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
 	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
 	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
 	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
 	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
 	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
 	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
 	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
 	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
 	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


 	    END_CALLS();
 	    END_STEP();

     }

    START_STEP("5_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_ON;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 1023;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_ON;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1023;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_1;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("6_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_SF01;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 1023;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_SF01;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1023;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_1;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("7_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_SF02;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 1023;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_SF02;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1023;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_1;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("8_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_SF03;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 1023;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_SF03;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1023;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_1;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("9_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    RBMESG_PN14_ProdMd_Stat_ST3 = 5;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 0;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_SNA;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_1;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("10_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_PRE_RESET;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 1023;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_PRE_RESET;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1023;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_1;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("11_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_RESET;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 1023;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_RESET;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1023;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_1;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("12_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_PRE_OPN;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 1023;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_PRE_OPN;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1023;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_1;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("13_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_OPN;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 1023;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_OPN;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1023;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_1;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("14_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = 5;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 0;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_SNA;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_1;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("15_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 511;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 511;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_2;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("16_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 1021;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1021;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_2;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("17_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 1022;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1022;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_2;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);


	    END_CALLS();
	    END_STEP();

    }

    START_STEP("18_NTS", TRUE);
    {

	    initialise_global_data();
	    initialise_expected_global_data();

	    //InitialisationRBMESG_PN14_TransMd_Stat_ST3
	    RBMESG_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    RBMESG_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    RBMESG_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    RBMESG_PN14_ProdMd_BatStat_ST3 = 0;
	    RBMESG_PN14_SupBat_Volt_ST3 = 1023;
	    RBMESG_PN14_SupBat_Stat_ST3 = 0;
	    RBMESG_PN14_SupBat_Curr_ST3 = 0;
	    RBMESG_PN14_SupBat_Temp_ST3 = 0;
	    RBMESG_PN14_PNSec_RechargeEnable_ST3 = 0;
	    RBMESG_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    RBMESG_PN14_DDP_Sw2_Stat_ST3 = 0;

	    RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 1;
	    RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 1;

	    expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3 = I_C02_TRANSMD_STAT_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3 = I_C03_PN14_TDP_SW_STAT_CLS;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3 = I_C03_PN14_PRODMD_STAT_ST3_OFF;
	    expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3 = 1023;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3 = 0;
	    expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3 = 0;

	    // Expected Call Sequence
	    EXPECTED_CALLS("Dem_SetEventStatus#Stub_1;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );

	    // Call SUT
	    rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

	    // Test case checks
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3,expected_RBMESG_rbl_CustIf_PN14_ProdMd_BatStat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Stat_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Curr_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3,expected_RBMESG_rbl_CustIf_PN14_SupBat_Temp_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3,expected_RBMESG_rbl_CustIf_PN14_PNSec_RechargeEnable_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3,expected_RBMESG_rbl_CustIf_PN14_ExtBat_Charge_Actv_ST3);
	    CHECK_U_INT(RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3,expected_RBMESG_rbl_CustIf_PN14_DDP_Sw2_Stat_ST3);

	    END_CALLS();
	    END_STEP();

    }

	/* Test steps*/
	START_STEP("19_NTS", true);
	{

		/*initialise_globals*/
		ACCESS_VARIABLE(rbl_CustIf_PN14_Master_Stat1_ST3, rbl_CustIf_Pn14_Signal_Timeout) = TRUE;

		/* Expected Call Sequence  */
		EXPECTED_CALLS("Dem_SetEventStatus#Dem_SetEventStatus_1;"
#if(RBFS_ThirdPartySoftware == RBFS_ThirdPartySoftware_ON)
	    		       "Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3#default;"
#endif
                       );
		/* Call SUT */
		rbl_CustIf_PN14_Master_Stat1_ST3_PDU_Receive();

		/* Test step checks */
		CHECK_U_INT(ACCESS_VARIABLE(rbl_CustIf_PN14_Master_Stat1_ST3, rbl_CustIf_Pn14_Signal_Timeout), FALSE);
		CHECK_U_INT(RBMESG_rbl_CustIf_PN14_TransMd_Stat_ST3, I_C02_TRANSMD_STAT_SNA);
		CHECK_U_INT(RBMESG_rbl_CustIf_PN14_ProdMd_Stat_ST3, I_C03_PN14_PRODMD_STAT_ST3_SNA);
		CHECK_U_INT(RBMESG_rbl_CustIf_PN14_SupBat_Volt_ST3, I_C10_V_0_25K55_0K025_SNA);

	    END_CALLS();
		END_STEP();
	}

    END_TEST();


	}
}
/*****************************************************************************/
/* Call Interface Control                                                    */
/*****************************************************************************/

/* Stub for function RBSYS_EnterCommonLockSysfast_intern */
void RBSYS_EnterCommonLockSysfast_intern(){
    REGISTER_CALL("RBSYS_EnterCommonLockSysfast_intern");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function RBSYS_ExitCommonLockSysfast_intern */
void RBSYS_ExitCommonLockSysfast_intern(){
    REGISTER_CALL("RBSYS_ExitCommonLockSysfast_intern");

    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Stub for function Dem_SetEventStatus */
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId,
                                  Dem_EventStatusType EventStatus){
    REGISTER_CALL("Dem_SetEventStatus");

    IF_INSTANCE("Stub_1") {
	    CHECK_U_INT(EventId,DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_PN14_Master_Stat1_ST3);
	    CHECK_U_INT(EventStatus,DEM_EVENT_STATUS_PREFAILED);
        return DEM_EVENT_STATUS_PREFAILED;
    }

    IF_INSTANCE("Stub_2") {
	    CHECK_U_INT(EventId,DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_PN14_Master_Stat1_ST3);
	    CHECK_U_INT(EventStatus,DEM_EVENT_STATUS_PREPASSED);
        return DEM_EVENT_STATUS_PREPASSED;
    }

    IF_INSTANCE("Dem_SetEventStatus_1") {
	    CHECK_U_INT(EventId,DemConf_DemEventParameter_RBL_CUSTIF_SIGNAL_INVALID_PN14_Master_Stat1_ST3);
	    CHECK_U_INT(EventStatus,CANTATA_DEFAULT_VALUE);
        return CANTATA_DEFAULT_VALUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

/* Stub for function Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3 */
Std_ReturnType Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3(Ssa_PowernetMgmtStateType data){
    REGISTER_CALL("Rte_Write_rbl_CustIf_P_PwrMgmt_Stat_ST3_PN14_DDP_Sw_Stat_ST3");

    IF_INSTANCE("default") {
        return CANTATA_DEFAULT_VALUE;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return CANTATA_DEFAULT_VALUE;
}

#pragma qas cantata ignore on

/* Before-Wrapper for function RBSYS_EnterCommonLockSysfast */
int BEFORE_RBSYS_EnterCommonLockSysfast(){
    REGISTER_CALL("RBSYS_EnterCommonLockSysfast");

    IF_INSTANCE("default") {
        return AFTER_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function RBSYS_EnterCommonLockSysfast */
void AFTER_RBSYS_EnterCommonLockSysfast(struct cppsm_void_return cppsm_dummy){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function RBSYS_EnterCommonLockSysfast */
void REPLACE_RBSYS_EnterCommonLockSysfast(){

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Before-Wrapper for function RBSYS_ExitCommonLockSysfast */
int BEFORE_RBSYS_ExitCommonLockSysfast(){
    REGISTER_CALL("RBSYS_ExitCommonLockSysfast");

    IF_INSTANCE("default") {
        return AFTER_WRAPPER;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return AFTER_WRAPPER;
}

/* After-Wrapper for function RBSYS_ExitCommonLockSysfast */
void AFTER_RBSYS_ExitCommonLockSysfast(struct cppsm_void_return cppsm_dummy){
    IF_INSTANCE("default") {
        return;
    }

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

/* Replace-Wrapper for function RBSYS_ExitCommonLockSysfast */
void REPLACE_RBSYS_ExitCommonLockSysfast(){

    LOG_SCRIPT_ERROR("Call instance not defined.");
    return;
}

#pragma qas cantata ignore off
/* pragma qas cantata testscript end */
/*****************************************************************************/
/* End of test script                                                        */
/*****************************************************************************/
