
/* TOOL GENERATED FILES*/

#include "cc_string.h"
#include "SwTest_Global.h"
#include "Dem.h"
#include "RBDsm_Testing.h"
#include "Dem_Ext.h"
//Function for testing Nodes against shutdown strategy

void DSM_SWT_RobustnessTest(DSMRobustnessTestType *EventRobustnessStruct, int elements)
	 {
		int i,j,reportingcycles;
		int NormalizedFailureThreshold; 
		int CyclesToReachRobustnessLimit; 
		boolean FdcThresholdReached;
		int FailedTests=0;
		int Failed_testcase_no[50];

		SWT_TestEnvReset();
		SWT_RunSystemMS(1000);		
		SWT_Info("----------Executing Test RBDSM_SWT_Robustness_Tests()----------");   
        SWT_EvalEx(SWT_IsSystemFaultFree()," System is Faultfree");  
		 for(i=0; i<elements; i++)
			{
				
				SWT_TestEnvReset();
				SWT_RunSystemMS(1000);
				SWT_Info("--------------Excuting Test RBDSM_SWT_Robustness_Tests_%s()--------------",EventRobustnessStruct[i].EvId_Str);
				SWT_EvalEx(SWT_IsSystemFaultFree(),"System is Faultfree");   			/*Evaluate if the system is Fault-Free*/
				SWT_RunSystemMS(1000);
				NormalizedFailureThreshold = 127* EventRobustnessStruct[i].IncrementStep/EventRobustnessStruct[i].FailureThreshold ;
				CyclesToReachRobustnessLimit = EventRobustnessStruct[i].RobustnessThreshold / NormalizedFailureThreshold;
				SWT_Info("Failure Threshold for Event %s = %d",EventRobustnessStruct[i].EvId_Str,EventRobustnessStruct[i].FailureThreshold );
				SWT_Info("Robustness Threshold for Event %s = %d",EventRobustnessStruct[i].EvId_Str,EventRobustnessStruct[i].RobustnessThreshold );
				SWT_Info("Normalized Steps incremented per cycle for Event %s = %d",EventRobustnessStruct[i].EvId_Str,NormalizedFailureThreshold);
				SWT_Info("Cycles\Number of failure debouncing required to reach Robustness Level for Event %s = %d",EventRobustnessStruct[i].EvId_Str,CyclesToReachRobustnessLimit );
				reportingcycles=1;
				 while(reportingcycles <= CyclesToReachRobustnessLimit)
				 {
				   Dem_ReportErrorStatus(EventRobustnessStruct[i].EvId, DEM_EVENT_STATUS_PREFAILED);
				   reportingcycles++;
				 }
				SWT_Info("Number of times even %s reported as invalid = %d",EventRobustnessStruct[i].EvId_Str,reportingcycles );
				Dem_GetEventFdcThresholdReached(EventRobustnessStruct[i].EvId ,  &FdcThresholdReached);			/*check if Node is set to invalid*/				
				SWT_RunSystemMS(1000);
				if(FdcThresholdReached)										/*if  Failure Set*/
				{
				   SWT_Info("%s Set to Robustness Limit",EventRobustnessStruct[i].EvId_Str);	
				 
				} //ifRobustness not reported
				else																	 /* If Robustness level not reached*/
				{
					FailedTests++;
					SWT_Info("Event not set to RobustnessLevel , Testcase Fail!!");
					SWT_EvalEx(0,"Test case fail with node %s",EventRobustnessStruct[i].EvId_Str);
					Failed_testcase_no[FailedTests-1]=i;
				}		
				SWT_TestEnvReset();
				SWT_Info("----------End Of Test RBDSM_SWT_Robustness_Tests__%s()----------",EventRobustnessStruct[i].EvId_Str);
			}//end of for loop

		SWT_TestEnvReset();
		SWT_RunSystemMS(1000);
		SWT_Info("%d out of %d testcases failed in Robustness tests ",FailedTests,elements);
		if(FailedTests!=0)
		{
			SWT_Info("--------------------------------------------SUMMARY OF SIMULATION-----------------------------------------------");
			SWT_Info("Failed test cases :");
			for (i=0; i<FailedTests; i++)
			{
				j= Failed_testcase_no[i];
				SWT_Info("RBDSM_SWT_Robustness_Tests__%s ",EventRobustnessStruct[j].EvId_Str);
			}
		}
		SWT_EvalEx(SWT_IsSystemFaultFree(),"System is Faultfree"); 
		SWT_Info("-----------------End Of Test RBDSM_SWT_Robustness_Tests()-----------------");
		//return 0;
	  }//end Of function  SWTEST void Component_STM_SimTest()

void DSM_SWT_SuspicionTest(DSMSuspicionTestType *EventSuspicionStruct, int elements)
	 {
		int i,j,reportingcycles;
		int FailedTests=0;
		int Failed_testcase_no[50];
		boolean EventSuspicious;

		SWT_TestEnvReset();
		SWT_RunSystemMS(1000);		
		SWT_Info("----------Executing Test RBDSM_SWT_Suspicion_Tests()----------");   
        SWT_EvalEx(SWT_IsSystemFaultFree()," System is Faultfree");  
		 for(i=0; i<elements; i++)
			{
				
				SWT_TestEnvReset();
				SWT_RunSystemMS(1000);
				SWT_Info("--------------Excuting Test RBDSM_SWT_Suspicion_Tests_%s()--------------",EventSuspicionStruct[i].EvId_Str);
				SWT_EvalEx(SWT_IsSystemFaultFree(),"System is Faultfree");   			/*Evaluate if the system is Fault-Free*/
				SWT_RunSystemMS(1000);
			     reportingcycles=1;
				 while(reportingcycles <= EventSuspicionStruct[i].SuspicionThreshold)
				 {
				   Dem_ReportErrorStatus(EventSuspicionStruct[i].EvId, DEM_EVENT_STATUS_PREFAILED);
				   reportingcycles++;
				 }
				SWT_Info("Number of times even %s reported as invalid = %d",EventSuspicionStruct[i].EvId_Str,reportingcycles );
				Dem_GetEventSuspicious(EventSuspicionStruct[i].EvId ,  &EventSuspicious);			/*check if Node is set to invalid*/				
				SWT_RunSystemMS(1000);
				if(EventSuspicious)										/*if  Failure Set*/
				{
				   SWT_Info("%s Set to Suspicion Limit",EventSuspicionStruct[i].EvId_Str);	
				 
				} //ifRobustness not reported
				else																	 /* If Robustness level not reached*/
				{
					FailedTests++;
					SWT_Info("Event not set to Suspicious Level , Testcase Fail!!");
					SWT_EvalEx(0,"Test case fail with node %s",EventSuspicionStruct[i].EvId_Str);
					Failed_testcase_no[FailedTests-1]=i;
				}		
				SWT_TestEnvReset();
				SWT_Info("----------End Of Test RBDSM_SWT_Suspicion_Tests__%s()----------",EventSuspicionStruct[i].EvId_Str);
			}//end of for loop

		SWT_TestEnvReset();
		SWT_RunSystemMS(1000);
		SWT_Info("%d out of %d testcases failed in Suspicion tests ",FailedTests,elements);
		if(FailedTests!=0)
		{
			SWT_Info("--------------------------------------------SUMMARY OF SIMULATION-----------------------------------------------");
			SWT_Info("Failed test cases :");
			for (i=0; i<FailedTests; i++)
			{
				j= Failed_testcase_no[i];
				SWT_Info("RBDSM_SWT_Suspicion_Tests__%s ",EventSuspicionStruct[j].EvId_Str);
			}
		}

		SWT_EvalEx(SWT_IsSystemFaultFree(),"System is Faultfree"); 
		SWT_Info("-----------------End Of Test RBDSM_SWT_Suspicion_Tests()-----------------");
		//return 0;
	  }//end Of function  SWTEST void Component_STM_SimTest()
