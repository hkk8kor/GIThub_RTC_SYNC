/* TOOL GENERATED FILES*/

#include "cc_string.h"
#include "SwTest_Global.h"
#include "Dem.h"
#include "RBDsm_Testing.h"

/** @testlists  RBDSM_SWT_FeatureLevel_Integration_Tests
 *
 * TESTNAME     : RBDSM_SWT_FeatureLevel_Integration_Test__Robustness
 *
 * FUNCTIONALITY: Check Robustness Feature (FW_RBBrakeLightSwitchLineInterrupt locally enabled Robustness level for Testing. 
 *                                          Official delivered FW doesn't have FW enabled)
 *
 */

SWTEST void RBDSM_SWT_FeatureLevel_Integration_Test_Robustness(void)
{

#ifdef DemConf_DemEventParameter_RBBrakeLightSwitchLineInterrupt
  /*struct of Failurewords with Robustness threshold defined */
    DSMRobustnessTestType EventRobustnessStruct[] =
    {
         { DemConf_DemEventParameter_RBBrakeLightSwitchLineInterrupt, 100, 1, 2,"FW_RBBrakeLightSwitchLineInterrupt" }

    };

    DSM_SWT_RobustnessTest(&EventRobustnessStruct[0], (sizeof(EventRobustnessStruct)/sizeof(DSMRobustnessTestType)) );
#else
	/*report atleast one test report to avoid the testlist being failed*/
	SWT_EvalEx(1,"To make atleast one test report");
#endif
}




/** @testlists  RBDSM_SWT_FeatureLevel_Integration_Tests
 *
 * TESTNAME     : RBDSM_SWT_FeatureLevel_Integration_Test__Suspicion
 *
 * FUNCTIONALITY: Check Suspicion Feature
 *
 */

SWTEST void RBDSM_SWT_FeatureLevel_Integration_Test_Suspicion(void)
{


#if defined(DemConf_DemEventParameter_RBIISSMI7GeneralYrsFault) && defined(DemConf_DemEventParameter_RBIISSMI7GeneralAsFault) && defined(DemConf_DemEventParameter_RBIISSMI7SpiTransError )

/*struct of Failurewords with Suspicion level defined */
DSMSuspicionTestType EventSuspicionStruct[] =
{  
		
		 { DemConf_DemEventParameter_RBIISSMI7SpiTransError, 1 ,"FW_RBIISSMI7SpiTransError" },
		 { DemConf_DemEventParameter_RBIISSMI7GeneralAsFault, 1 ,"FW_RBIISSMI7GeneralAsFault" },
	     { DemConf_DemEventParameter_RBIISSMI7GeneralYrsFault, 1 ,"FW_RBIISSMI7GeneralYrsFault" }
    };

    DSM_SWT_SuspicionTest(&EventSuspicionStruct[0], (sizeof(EventSuspicionStruct)/sizeof(DSMSuspicionTestType)) );
#else
	/*report atleast one test report to avoid the testlist being failed*/
	SWT_EvalEx(1,"To make atleast one test report");
#endif

}
