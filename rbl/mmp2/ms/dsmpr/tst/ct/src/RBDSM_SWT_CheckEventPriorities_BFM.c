#include "SwTest_Global.h"
#include "Dem.h"
#include "Dem_EventStatus.h"
#include "Dem_Events.h"
#include "Dem_Deb.h"
#include "RBDSMSim_ModeManager.h"
#include "RB_BfmInterfaceRemap.h"
#include "Dem_EvMemBase.h"
#include "Dem_DTCs.h"
#include "Dem_EnvMain.h"
#include "RBDSM_SWT_CheckEventPriorities_BFM.h"

#if(RBFS_DSMSimulation == RBFS_DSMSimulation_ON)
void DSMSim_PriorityDisabled(Dem_EventIdType EventId1, Dem_EventIdType EventId2,Dem_EventIdType EventId3,Dem_EventIdType EventId4,Dem_EventIdType EventId5,Dem_EventIdType EventId6,Dem_EventIdType EventId7,Dem_EventIdType EventId8,Dem_EventIdType EventId9,Dem_EventIdType EventId10 )
{

    rba_DemBfm_LocationDataType location1,location2,location3,location4,location5,location6,location7,location8,location9,location10;
    rba_DemBfm_Record l_BfmRecord1, l_BfmRecord2, l_BfmRecord3,l_BfmRecord4,l_BfmRecord5,l_BfmRecord6,l_BfmRecord7,l_BfmRecord8,l_BfmRecord9,l_BfmRecord10;
    int record1_exists=RBA_DEMBFM_RET_OK_MASK;
    int record2_exists=RBA_DEMBFM_RET_OK_MASK;
    int record3_exists=RBA_DEMBFM_RET_OK_MASK;
    int record4_exists=RBA_DEMBFM_RET_OK_MASK;
    int record5_exists=RBA_DEMBFM_RET_OK_MASK;
    int record6_exists=RBA_DEMBFM_RET_OK_MASK;
    int record7_exists=RBA_DEMBFM_RET_OK_MASK;
    int record8_exists=RBA_DEMBFM_RET_OK_MASK;
    int record9_exists=RBA_DEMBFM_RET_OK_MASK;
    int record10_exists=RBA_DEMBFM_RET_OK_MASK;
    SWT_TestEnvReset();
    SWT_RunSystemMS(200);

    SWT_Info("Set DEM events of Node as FAILED \n");
    if(EventId1 != 0)
    {
        SWT_Info("Set Event %s as FAILED",Dem_EventIdToString(EventId1));
        Dem_ReportErrorStatus(EventId1, DEM_EVENT_STATUS_FAILED);

    }
    if(EventId2 != 0)
    {
        SWT_Info("Set Event %s as FAILED",Dem_EventIdToString(EventId2));
        Dem_ReportErrorStatus(EventId2, DEM_EVENT_STATUS_FAILED);
    }
    if(EventId3 != 0)
    {
        SWT_Info("Set Event %s as FAILED",Dem_EventIdToString(EventId3));
        Dem_ReportErrorStatus(EventId3, DEM_EVENT_STATUS_FAILED);
    }
    if(EventId4 != 0)
    {
        SWT_Info("Set Event %s as FAILED",Dem_EventIdToString(EventId4));
        Dem_ReportErrorStatus(EventId4, DEM_EVENT_STATUS_FAILED);
    }
    if(EventId5 != 0)
    {
        SWT_Info("Set Event %s as FAILED",Dem_EventIdToString(EventId5));
        Dem_ReportErrorStatus(EventId5, DEM_EVENT_STATUS_FAILED);
    }
    if(EventId6 != 0)
    {
        SWT_Info("Set Event %s as FAILED",Dem_EventIdToString(EventId6));
        Dem_ReportErrorStatus(EventId6, DEM_EVENT_STATUS_FAILED);
    }
    if(EventId7 != 0)
    {
        SWT_Info("Set Event %s as FAILED",Dem_EventIdToString(EventId7));
        Dem_ReportErrorStatus(EventId7, DEM_EVENT_STATUS_FAILED);
    }
    if(EventId8 != 0)
    {
        SWT_Info("Set Event %s as FAILED",Dem_EventIdToString(EventId8));
        Dem_ReportErrorStatus(EventId8, DEM_EVENT_STATUS_FAILED);
    }
    if(EventId9 != 0)
    {
        SWT_Info("Set Event %s as FAILED",Dem_EventIdToString(EventId9));
        Dem_ReportErrorStatus(EventId9, DEM_EVENT_STATUS_FAILED);
    }
    if(EventId10 != 0)
    {
        SWT_Info("Set Event %s as FAILED",Dem_EventIdToString(EventId10));
        Dem_ReportErrorStatus(EventId10, DEM_EVENT_STATUS_FAILED);
    }
    SWT_RunSystemMS(200);
    if(EventId1 != 0)
    {
        record1_exists=rba_DemBfm_RecordFind(EventId1,&location1);
    }
    if(EventId2 != 0)
    {
        record2_exists=rba_DemBfm_RecordFind(EventId2,&location2);
    }
    if(EventId3 != 0)
    {
        record3_exists=rba_DemBfm_RecordFind(EventId3,&location3);
    }
    if(EventId4 != 0)
    {
        record4_exists=rba_DemBfm_RecordFind(EventId4,&location4);
    }
    if(EventId5 != 0)
    {
        record5_exists=rba_DemBfm_RecordFind(EventId5,&location5);
    }
    if(EventId6 != 0)
    {
        record6_exists=rba_DemBfm_RecordFind(EventId6,&location6);
    }
    if(EventId7 != 0)
    {
        record7_exists=rba_DemBfm_RecordFind(EventId7,&location7);
    }
    if(EventId8 != 0)
    {
        record8_exists=rba_DemBfm_RecordFind(EventId8,&location8);
    }
    if(EventId9 != 0)
    {
        record9_exists=rba_DemBfm_RecordFind(EventId9,&location9);
    }
    if(EventId10 != 0)
    {
        record10_exists=rba_DemBfm_RecordFind(EventId10,&location10);
    }


   if(((record1_exists == RBA_DEMBFM_RET_OK)||(record1_exists == RBA_DEMBFM_RET_OK_MASK))
      && ((record2_exists == RBA_DEMBFM_RET_OK)||(record2_exists == RBA_DEMBFM_RET_OK_MASK))
      && ((record3_exists == RBA_DEMBFM_RET_OK)||(record3_exists == RBA_DEMBFM_RET_OK_MASK))
      && ((record4_exists == RBA_DEMBFM_RET_OK)||(record4_exists == RBA_DEMBFM_RET_OK_MASK))
      && ((record5_exists == RBA_DEMBFM_RET_OK)||(record5_exists == RBA_DEMBFM_RET_OK_MASK))
      && ((record6_exists == RBA_DEMBFM_RET_OK)||(record6_exists == RBA_DEMBFM_RET_OK_MASK))
      && ((record7_exists == RBA_DEMBFM_RET_OK)||(record7_exists == RBA_DEMBFM_RET_OK_MASK))
      && ((record8_exists == RBA_DEMBFM_RET_OK)||(record8_exists == RBA_DEMBFM_RET_OK_MASK))
      && ((record9_exists == RBA_DEMBFM_RET_OK)||(record9_exists == RBA_DEMBFM_RET_OK_MASK))
      && ((record10_exists == RBA_DEMBFM_RET_OK)||(record10_exists == RBA_DEMBFM_RET_OK_MASK)))
   {
        SWT_Info("All Events are logged in BFM as expected");
        SWT_Eval(1);
   }
   else
   {
        SWT_Info("Events logging into BFM is not as expected");
        SWT_Eval(0);
   }


    if(record1_exists == RBA_DEMBFM_RET_OK)
    {
       SWT_Info("Record Exist status of %s = %d", Dem_EventIdToString(EventId1),record1_exists);
       rba_DemBfm_RecordRead(location1, &l_BfmRecord1);
       SWT_Info("Status of %s in BFM is 0x%X",Dem_EventIdToString(EventId1),l_BfmRecord1.statusAndQualification);
    }

    if(record2_exists == RBA_DEMBFM_RET_OK)
    {
       SWT_Info("Record Exist status of %s = %d", Dem_EventIdToString(EventId2),record2_exists);
       rba_DemBfm_RecordRead(location2, &l_BfmRecord2);
       SWT_Info("Status of %s in BFM is 0x%X",Dem_EventIdToString(EventId2), l_BfmRecord2.statusAndQualification);
    }

    if(record3_exists == RBA_DEMBFM_RET_OK)
    {
       SWT_Info("Record Exist status of %s = %d", Dem_EventIdToString(EventId3),record3_exists);
       rba_DemBfm_RecordRead(location3, &l_BfmRecord3);
       SWT_Info("Status of %s in BFM is 0x%X",Dem_EventIdToString(EventId3), l_BfmRecord3.statusAndQualification);
    }
    if(record4_exists == RBA_DEMBFM_RET_OK)
    {
       SWT_Info("Record Exist status of %s = %d", Dem_EventIdToString(EventId4),record4_exists);
       rba_DemBfm_RecordRead(location4, &l_BfmRecord4);
       SWT_Info("Status of %s in BFM is 0x%X",Dem_EventIdToString(EventId4), l_BfmRecord4.statusAndQualification);
    }
    if(record5_exists == RBA_DEMBFM_RET_OK)
    {
       SWT_Info("Record Exist status of %s = %d", Dem_EventIdToString(EventId5),record5_exists);
       rba_DemBfm_RecordRead(location5, &l_BfmRecord5);
       SWT_Info("Status of %s in BFM is 0x%X",Dem_EventIdToString(EventId5), l_BfmRecord5.statusAndQualification);
    }
    if(record6_exists == RBA_DEMBFM_RET_OK)
    {
       SWT_Info("Record Exist status of %s = %d", Dem_EventIdToString(EventId6),record6_exists);
       rba_DemBfm_RecordRead(location6, &l_BfmRecord6);
       SWT_Info("Status of %s in BFM is 0x%X",Dem_EventIdToString(EventId6), l_BfmRecord6.statusAndQualification);
    }
    if(record7_exists == RBA_DEMBFM_RET_OK)
    {
       SWT_Info("Record Exist status of %s = %d", Dem_EventIdToString(EventId7),record7_exists);
       rba_DemBfm_RecordRead(location7, &l_BfmRecord7);
       SWT_Info("Status of %s in BFM is 0x%X",Dem_EventIdToString(EventId7), l_BfmRecord7.statusAndQualification);
    }
    if(record8_exists == RBA_DEMBFM_RET_OK)
    {
       SWT_Info("Record Exist status of %s = %d", Dem_EventIdToString(EventId8),record8_exists);
       rba_DemBfm_RecordRead(location8, &l_BfmRecord8);
       SWT_Info("Status of %s in BFM is 0x%X",Dem_EventIdToString(EventId8), l_BfmRecord8.statusAndQualification);
    }
    if(record9_exists == RBA_DEMBFM_RET_OK)
    {
       SWT_Info("Record Exist status of %s = %d", Dem_EventIdToString(EventId9),record9_exists);
       rba_DemBfm_RecordRead(location9, &l_BfmRecord9);
       SWT_Info("Status of %s in BFM is 0x%X",Dem_EventIdToString(EventId9), l_BfmRecord9.statusAndQualification);
    }
    if(record10_exists == RBA_DEMBFM_RET_OK)
    {
       SWT_Info("Record Exist status of %s = %d", Dem_EventIdToString(EventId10),record10_exists);
       rba_DemBfm_RecordRead(location10, &l_BfmRecord10);
       SWT_Info("Status of %s in BFM is 0x%X",Dem_EventIdToString(EventId10), l_BfmRecord10.statusAndQualification);
    }
    if(EventId1 != 0)
    {
        SWT_Info("Set Event %s as PASSED", Dem_EventIdToString(EventId1));
        Dem_ReportErrorStatus(EventId1, DEM_EVENT_STATUS_PASSED);
    }
    if(EventId2 != 0)
    {
        SWT_Info("Set Event %s as PASSED", Dem_EventIdToString(EventId2));
        Dem_ReportErrorStatus(EventId2, DEM_EVENT_STATUS_PASSED);
    }
    if(EventId3 != 0)
    {
        SWT_Info("Set Event %s as PASSED", Dem_EventIdToString(EventId3));
        Dem_ReportErrorStatus(EventId3, DEM_EVENT_STATUS_PASSED);
    }
    if(EventId4 != 0)
    {
        SWT_Info("Set Event %s as PASSED", Dem_EventIdToString(EventId4));
        Dem_ReportErrorStatus(EventId4, DEM_EVENT_STATUS_PASSED);
    }
    if(EventId5 != 0)
    {
        SWT_Info("Set Event %s as PASSED", Dem_EventIdToString(EventId5));
        Dem_ReportErrorStatus(EventId5, DEM_EVENT_STATUS_PASSED);
    }
    if(EventId6 != 0)
    {
        SWT_Info("Set Event %s as PASSED", Dem_EventIdToString(EventId6));
        Dem_ReportErrorStatus(EventId6, DEM_EVENT_STATUS_PASSED);
    }
    if(EventId7 != 0)
    {
        SWT_Info("Set Event %s as PASSED", Dem_EventIdToString(EventId7));
        Dem_ReportErrorStatus(EventId7, DEM_EVENT_STATUS_PASSED);
    }
    if(EventId8 != 0)
    {
        SWT_Info("Set Event %s as PASSED", Dem_EventIdToString(EventId8));
        Dem_ReportErrorStatus(EventId8, DEM_EVENT_STATUS_PASSED);
    }
    if(EventId9 != 0)
    {
        SWT_Info("Set Event %s as PASSED", Dem_EventIdToString(EventId9));
        Dem_ReportErrorStatus(EventId9, DEM_EVENT_STATUS_PASSED);
    }
    if(EventId10 != 0)
    {
        SWT_Info("Set Event %s as PASSED", Dem_EventIdToString(EventId10));
        Dem_ReportErrorStatus(EventId10, DEM_EVENT_STATUS_PASSED);
    }
        SWT_RunSystemMS(40);

        SWT_Info("Clear BFM records");
        rba_DemBfm_DeleteAllTrigger();
        SWT_RunSystemMS(40);

}

void DSMSim_NodePriority(Dem_EventIdType EventId1, Dem_EventIdType EventId2,Dem_EventIdType EventId3,Dem_EventIdType EventId_fromParent )

{
    rba_DemBfm_LocationDataType location1,location2,location3,location4;
    rba_DemBfm_Record l_BfmRecord1, l_BfmRecord2, l_BfmRecord3,l_BfmRecord4;
    uint8 i=0;

    int record1_exists=RBA_DEMBFM_RET_OK_MASK;
    int record2_exists=RBA_DEMBFM_RET_OK_MASK;
    int record3_exists=RBA_DEMBFM_RET_OK_MASK;
    int record4_exists=RBA_DEMBFM_RET_OK_MASK;

    Dem_EventStatusExtendedType EventStatus1 = DEM_ISO14229BYTE_INITVALUE;
    Dem_EventStatusExtendedType EventStatus2 = DEM_ISO14229BYTE_INITVALUE;
    Dem_EventStatusExtendedType EventStatus3 = DEM_ISO14229BYTE_INITVALUE;
    Dem_EventStatusExtendedType EventStatus4 = DEM_ISO14229BYTE_INITVALUE;

    SWT_TestEnvReset();
    SWT_RunSystemMS(200);


    SWT_Info("Set DEM events to check the priority among Parent and Child node\n");

    SWT_Info("Set Event %s as FAILED",Dem_EventIdToString(EventId_fromParent));
    Dem_ReportErrorStatus(EventId_fromParent, DEM_EVENT_STATUS_FAILED);
    SWT_Info("Set Event %s as FAILED",Dem_EventIdToString(EventId1));
    Dem_ReportErrorStatus(EventId1, DEM_EVENT_STATUS_FAILED);
    SWT_Info("Set Event %s as FAILED",Dem_EventIdToString(EventId2));
    Dem_ReportErrorStatus(EventId2, DEM_EVENT_STATUS_FAILED);
    SWT_Info("Set Event %s as FAILED",Dem_EventIdToString(EventId3));
    Dem_ReportErrorStatus(EventId3, DEM_EVENT_STATUS_FAILED);

    SWT_RunSystemMS(200);

    record1_exists=rba_DemBfm_RecordFind(EventId1,&location1);
    record2_exists=rba_DemBfm_RecordFind(EventId2,&location2);
    record3_exists=rba_DemBfm_RecordFind(EventId3,&location3);
    record4_exists=rba_DemBfm_RecordFind(EventId_fromParent,&location4);


    if((record4_exists == RBA_DEMBFM_RET_OK) && (record2_exists == RBA_DEMBFM_RET_NOT_FOUND) && (record3_exists == RBA_DEMBFM_RET_NOT_FOUND) && (record1_exists == RBA_DEMBFM_RET_NOT_FOUND))
       {
            SWT_Info("Only parent Node Failure Exists as expected");
            SWT_Eval(1);
      }
   else
      {
            SWT_Info("Events logging into BFM is not as expected");
            SWT_Eval(0);
      }

    if(record1_exists == RBA_DEMBFM_RET_NOT_FOUND)
     {
            SWT_Info("Failure Not found in this Location");
            SWT_Info("Record Exist status of %s = %d",Dem_EventIdToString(EventId1), record1_exists);
     }

   if(record2_exists == RBA_DEMBFM_RET_NOT_FOUND)
    {
       SWT_Info("Failure Not found in this Location");
       SWT_Info("Record Exist status of %s = %d",Dem_EventIdToString(EventId2), record2_exists);
    }

    if(record3_exists == RBA_DEMBFM_RET_NOT_FOUND)
     {
        SWT_Info("Failure Not found in this Location");
        SWT_Info("Record Exist status of %s = %d",Dem_EventIdToString(EventId3), record3_exists);
     }

    if(record4_exists == RBA_DEMBFM_RET_OK)
    {
            SWT_Info("Failure Exists in this Location");
            rba_DemBfm_RecordRead(location4, &l_BfmRecord4);
            SWT_Info("Status of %s in BFM is 0x%X",Dem_EventIdToString(EventId_fromParent),l_BfmRecord4.statusAndQualification);
    }


     SWT_Info("Resetting all Failures\n");

     SWT_Info("Set Event %s as PASSED", Dem_EventIdToString(EventId1));
     Dem_ReportErrorStatus(EventId1, DEM_EVENT_STATUS_PASSED);
     SWT_Info("Set Event %s as PASSED",Dem_EventIdToString(EventId2));
     Dem_ReportErrorStatus(EventId2, DEM_EVENT_STATUS_PASSED);
     SWT_Info("Set Event %s as PASSED",Dem_EventIdToString(EventId3));
     Dem_ReportErrorStatus(EventId3, DEM_EVENT_STATUS_PASSED);
     SWT_Info("Set Event %s as PASSED",Dem_EventIdToString(EventId_fromParent));
     Dem_ReportErrorStatus(EventId_fromParent, DEM_EVENT_STATUS_PASSED);

     SWT_RunSystemMS(40);

     SWT_Info("Clear BFM records");
     rba_DemBfm_DeleteAllTrigger();
     SWT_RunSystemMS(40);
}

#endif

/** @testlists  RBDSM_SWT_FailureTree_EventPriorities_BFM
 *
 * TESTNAME     : RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SignalChainMonitors_1
 *
 * FUNCTIONALITY: To Validate the priorities of events in a node
 *
 */

SWTEST void RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SignalChainMonitors_1(void)
{

        Dem_EventIdType EventId1 = DemConf_DemEventParameter_RBL_FrequencyFailure_Smu2;
        Dem_EventIdType EventId2 = DemConf_DemEventParameter_RBL_FrequencyFailure_Smu1;
        Dem_EventIdType EventId3 = DemConf_DemEventParameter_RBL_FrequencyFailure_Smu0;
        Dem_EventIdType EventId4 = DemConf_DemEventParameter_RBL_Nvm_SigChain_Content;
        Dem_EventIdType EventId5 = DemConf_DemEventParameter_RBL_ChannelInvalid_Smu1_Acc3;
        Dem_EventIdType EventId6 = DemConf_DemEventParameter_RBL_ChannelInvalid_Smu2_Acc2;
        Dem_EventIdType EventId7 = DemConf_DemEventParameter_RBL_MechOverload_Smu0_Acc3;
        Dem_EventIdType EventId8 = DemConf_DemEventParameter_RBL_MechOverload_Smu2_Acc1;
        Dem_EventIdType EventId9 = DemConf_DemEventParameter_RBL_MechOverload_Smu2_Acc3;
        Dem_EventIdType EventId10 = DemConf_DemEventParameter_RBL_TemperatureRangeExceeded_Smu0;

        StartTest ("RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SignalChainMonitors_1","https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48169");


        SWT_Info("Calling the function to Check Priority Disabled");
        DSMSim_PriorityDisabled (EventId1, EventId2, EventId3, EventId4,EventId5,EventId6,EventId7,EventId8,EventId9,EventId10);

}


/** @testlists  RBDSM_SWT_FailureTree_EventPriorities_BFM
 *
 * TESTNAME     : RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SignalChainMonitors_2
 *
 * FUNCTIONALITY: To Validate the priorities of events in a node
 *
 */

SWTEST void RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SignalChainMonitors_2(void)
{

        Dem_EventIdType EventId1 = DemConf_DemEventParameter_RBL_FrequencyFailure_Smu0;
        Dem_EventIdType EventId2 = DemConf_DemEventParameter_RBL_FrequencyFailure_Smu1;
        Dem_EventIdType EventId3 = DemConf_DemEventParameter_RBL_FrequencyFailure_Smu2;
        Dem_EventIdType EventId4 = DemConf_DemEventParameter_RBL_Nvm_SigChain_Content;
        Dem_EventIdType EventId5 = DemConf_DemEventParameter_RBL_ChannelInvalid_Smu1_Acc3;
        Dem_EventIdType EventId6 = DemConf_DemEventParameter_RBL_ChannelInvalid_Smu2_Acc2;
        Dem_EventIdType EventId7 = DemConf_DemEventParameter_RBL_MechOverload_Smu0_Acc3;
        Dem_EventIdType EventId8 = DemConf_DemEventParameter_RBL_MechOverload_Smu2_Acc1;
        Dem_EventIdType EventId9 = DemConf_DemEventParameter_RBL_MechOverload_Smu2_Acc3;
        Dem_EventIdType EventId10 = DemConf_DemEventParameter_RBL_TemperatureRangeExceeded_Smu0;

        StartTest ("RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SignalChainMonitors_2","https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48169");


        SWT_Info("Calling the function to Check Priority Disabled");
        DSMSim_PriorityDisabled (EventId1, EventId2, EventId3, EventId4,EventId5,EventId6,EventId7,EventId8,EventId9,EventId10);

}

/** @testlists  RBDSM_SWT_FailureTree_EventPriorities_BFM
 *
 * TESTNAME     : RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SignalChainMonitors_MMP_NvmFreqContent
 *
 * FUNCTIONALITY: To Validate the priorities between Parent and Child node
 *
 */

SWTEST void RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SignalChainMonitors_MMP_NvmFreqContent(void)
{

        Dem_EventIdType EventId1 = DemConf_DemEventParameter_RBL_FrequencyFailure_Smu2;
        Dem_EventIdType EventId2 = DemConf_DemEventParameter_RBL_FrequencyFailure_Smu1;
        Dem_EventIdType EventId3 = DemConf_DemEventParameter_RBL_FrequencyFailure_Smu0;
        Dem_EventIdType EventId_fromParent = DemConf_DemEventParameter_RBL_Nvm_RefFreq_Content;

        StartTest ("RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SignalChainMonitors_BFM_MMP_SignalChainMonitors_MMP_SensorModuleError","https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48169");

        SWT_Info("Calling the function to Check Node Priority");
        DSMSim_NodePriority (EventId1, EventId2, EventId3,EventId_fromParent);

}

/** @testlists  RBDSM_SWT_FailureTree_EventPriorities_BFM
 *
 * TESTNAME     : RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SensorModuleError_1
 *
 * FUNCTIONALITY: To Validate the priorities of events in a node
 *
 */

SWTEST void RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SensorModuleError_1(void)
{

        Dem_EventIdType EventId1 = DemConf_DemEventParameter_RBL_ChannelInvalid_Smu0_Acc1;
        Dem_EventIdType EventId2 = DemConf_DemEventParameter_RBL_ChannelInvalid_Smu0_Rate1;
        Dem_EventIdType EventId3 = DemConf_DemEventParameter_RBL_ChannelInvalid_Smu1_Rate1;
        Dem_EventIdType EventId4 = DemConf_DemEventParameter_RBL_ChannelInvalid_Smu1_Acc3;
        Dem_EventIdType EventId5 = DemConf_DemEventParameter_RBL_MechOverload_Smu0_Acc3;
        Dem_EventIdType EventId6 = DemConf_DemEventParameter_RBL_MechOverload_Smu0_Acc2;
        Dem_EventIdType EventId7 = DemConf_DemEventParameter_RBL_MechOverload_Smu1_Acc1;
        Dem_EventIdType EventId8 = DemConf_DemEventParameter_RBL_MechOverload_Smu1_Rate1;
        Dem_EventIdType EventId9 = DemConf_DemEventParameter_RBL_MechOverload_Smu2_Rate1;
        Dem_EventIdType EventId10 = DemConf_DemEventParameter_RBL_TemperatureRangeExceeded_Smu2;

        StartTest ("RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SensorModuleError_1","https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48169");


        SWT_Info("Calling the function to Check Priority Disabled");
        DSMSim_PriorityDisabled (EventId1, EventId2, EventId3, EventId4,EventId5,EventId6,EventId7,EventId8,EventId9,EventId10);

}

/** @testlists  RBDSM_SWT_FailureTree_EventPriorities_BFM
 *
 * TESTNAME     : RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SensorModuleError_2
 *
 * FUNCTIONALITY: To Validate the priorities of events in a node
 *
 */

SWTEST void RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SensorModuleError_2(void)
{

        Dem_EventIdType EventId1 = DemConf_DemEventParameter_RBL_TemperatureRangeExceeded_Smu1;
        Dem_EventIdType EventId2 = DemConf_DemEventParameter_RBL_MechOverload_Smu2_Acc2;
        Dem_EventIdType EventId3 = DemConf_DemEventParameter_RBL_MechOverload_Smu1_Acc2;
        Dem_EventIdType EventId4 = DemConf_DemEventParameter_RBL_MechOverload_Smu2_Rate1;
        Dem_EventIdType EventId5 = DemConf_DemEventParameter_RBL_ChannelInvalid_Smu2_Acc3;
        Dem_EventIdType EventId6 = DemConf_DemEventParameter_RBL_ChannelInvalid_Smu2_Acc1;
        Dem_EventIdType EventId7 = DemConf_DemEventParameter_RBL_ChannelInvalid_Smu1_Acc2;
        Dem_EventIdType EventId8 = DemConf_DemEventParameter_RBL_ChannelInvalid_Smu0_Acc3;
        Dem_EventIdType EventId9 = DemConf_DemEventParameter_RBL_ChannelInvalid_Smu0_Acc2;
        Dem_EventIdType EventId10 = DemConf_DemEventParameter_RBL_ChannelInvalid_Smu1_Acc1;


        StartTest ("RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SensorModuleError_2","https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48169");


        SWT_Info("Calling the function to Check Priority Disabled");
        DSMSim_PriorityDisabled (EventId1, EventId2, EventId3, EventId4,EventId5,EventId6,EventId7,EventId8,EventId9,EventId10);

}

/** @testlists  RBDSM_SWT_FailureTree_EventPriorities_BFM
 *
 * TESTNAME     : RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SensorModuleError_MMP_CommunicationFailure
 *
 * FUNCTIONALITY: To Validate the priorities between Parent and Child node
 *
 */

SWTEST void RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SensorModuleError_MMP_CommunicationFailure(void)
{

        Dem_EventIdType EventId1 = DemConf_DemEventParameter_RBL_ChannelInvalid_Smu2_Acc3;
        Dem_EventIdType EventId2 = DemConf_DemEventParameter_RBL_TemperatureRangeExceeded_Smu1;
        Dem_EventIdType EventId3 = DemConf_DemEventParameter_RBL_MechOverload_Smu1_Acc2;
        Dem_EventIdType EventId_fromParent = DemConf_DemEventParameter_RBL_CommunicationFailure_Smu1;

        StartTest ("RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_SignalChainMonitors_BFM_MMP_SignalChainMonitors_MMP_SensorModuleError","https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48169");

        SWT_Info("Calling the function to Check Node Priority");
        DSMSim_NodePriority (EventId1, EventId2, EventId3,EventId_fromParent);

}

/** @testlists  RBDSM_SWT_FailureTree_EventPriorities_BFM
 *
 * TESTNAME     : RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_TracebilityData_1
 *
 * FUNCTIONALITY: To Validate the priorities of events in a node
 *
 */

SWTEST void RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_TracebilityData_1(void)
{

        Dem_EventIdType EventId1 = 0;
        Dem_EventIdType EventId2 = DemConf_DemEventParameter_RBL_Nvm_HwVersNr;
        Dem_EventIdType EventId3 = DemConf_DemEventParameter_RBL_Nvm_PcbDmc;
        Dem_EventIdType EventId4 = DemConf_DemEventParameter_RBL_Nvm_ProcProgsId;
        Dem_EventIdType EventId5 = DemConf_DemEventParameter_RBL_Nvm_ProdDate;
        Dem_EventIdType EventId6 = DemConf_DemEventParameter_RBL_Nvm_RbAsblyPartNr;
        Dem_EventIdType EventId7 = DemConf_DemEventParameter_RBL_Nvm_RbPartNr;
        Dem_EventIdType EventId8 = DemConf_DemEventParameter_RBL_Nvm_SnsrSerlNr;
        Dem_EventIdType EventId9 = DemConf_DemEventParameter_RBL_Nvm_PlaIdNr;
        Dem_EventIdType EventId10 = 0;

        StartTest ("RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_TracebilityData_1","https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48169");


        SWT_Info("Calling the function to Check Priority Disabled");
        DSMSim_PriorityDisabled (EventId1,EventId2,EventId3, EventId4,EventId5,EventId6,EventId7,EventId8,EventId9,EventId10);

}

/** @testlists  RBDSM_SWT_FailureTree_EventPriorities_BFM
 *
 * TESTNAME     : RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_TracebilityData_2
 *
 * FUNCTIONALITY: To Validate the priorities of events in a node
 *
 */

SWTEST void RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_TracebilityData_2(void)
{


        Dem_EventIdType EventId1 = DemConf_DemEventParameter_RBL_Nvm_ProcProgsId;
        Dem_EventIdType EventId2 = DemConf_DemEventParameter_RBL_Nvm_RbAsblyPartNr;
        Dem_EventIdType EventId3 = DemConf_DemEventParameter_RBL_Nvm_ProdDate;
        Dem_EventIdType EventId4 = DemConf_DemEventParameter_RBL_Nvm_PlaIdNr;
        Dem_EventIdType EventId5 = DemConf_DemEventParameter_RBL_Nvm_PcbDmc;
        Dem_EventIdType EventId6 = 0;
        Dem_EventIdType EventId7 = DemConf_DemEventParameter_RBL_Nvm_HwVersNr;
        Dem_EventIdType EventId8 = DemConf_DemEventParameter_RBL_Nvm_RbPartNr;
        Dem_EventIdType EventId9 = 0;
        Dem_EventIdType EventId10 = DemConf_DemEventParameter_RBL_Nvm_SnsrSerlNr;


        StartTest ("RBDSM_SWT_FailureTree_EventPriorities_BFM_MMP_TracebilityData_2","https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48169");


        SWT_Info("Calling the function to Check Priority Disabled");
        DSMSim_PriorityDisabled (EventId1,EventId2,EventId3, EventId4,EventId5,EventId6,EventId7,EventId8,EventId9,EventId10);

}
