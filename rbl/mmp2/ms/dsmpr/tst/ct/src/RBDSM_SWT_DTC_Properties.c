#include "SwTest_Global.h"
#include "Dem.h"
#include "Dem_EventStatus.h"
#include "Dem_Events.h"
#include "Dem_Deb.h"
#include "RBDSMSim_ModeManager.h"
#include "RBDSM_SWT_DTC_Properties.h"


/** @testlists  RBDSM_SWT_DTC_Mapping_Property
 *
 * TESTNAME     : RBDSM_SWT_DTC_Mapping
 *
 * FUNCTIONALITY: To verify correct DTC mapped to event ID
 *
 */

SWTEST void RBDSM_SWT_DTC_Mapping(void)
{

	uint32 DTCOfEvent = 0x000000;
    uint8 DTCStatus;
	Dem_EventIdType eventId = DEM_EVENTID_INVALID;
    Dem_EventStatusExtendedType EventStatus = DEM_ISO14229BYTE_INITVALUE;
	Dem_DtcIdType dtcId = DEM_DTCID_INVALID;
	StartTestTitle("RBDSM_SWT_DTC_MAPPING");


    StartTest ("RBDSM_SWT_DTC_Mapping","https://rb-alm-06-p.de.bosch.com/qm/web/console/Complex%20Sensors%20-%20Quality%20Management/_6CSOkE5XEea6FIzuTUbGfA#action=com.ibm.rqm.planning.home.actionDispatcher&subAction=viewTestCase&id=48176");



    for(eventId=1; eventId<NUMBER_OF_EVENTS; eventId++)
    {
          SWT_Info("RBDSM_SWT_DTC_Mapping for Event = %s",Dem_EventIdToString(eventId));

          SWT_Info("Step1: Reset the Environment");
          SWT_TestEnvReset();
          SWT_RunSystemMS(200);
          (void)Dem_SetOperationCycleState(DemConf_DemOperationCycle_IgnitionCycle, DEM_CYCLE_STATE_START);

          SWT_Info("Step2: Verify that Event has DTC");
          if(Dem_GetDTCOfEvent (eventId, DEM_DTC_FORMAT_UDS, &DTCOfEvent)== E_OK)
          {

              SWT_Info("Obtained DTC of Event %s is 0x%X and the expected DTC is 0x%X",Dem_EventIdToString(eventId), DTCOfEvent, EventID[eventId].DTC_ID);
			  Validate((DTCOfEvent == (EventID[eventId].DTC_ID)), "DTC of event is as expected", "DTC of event is not as expected");

			  if(DTCOfEvent == (EventID[eventId].DTC_ID))
			  {
				 SWT_Info("DTC of event is as expected");
				 SWT_Eval(1);
			  }
			  else
			  {
				 SWT_Info("DTC of event is not as expected");
				 SWT_Eval(0);
			  }



              SWT_Info("Step3: Get Event Status and verify that the status is not failed");
              Dem_GetEventStatus(eventId, &EventStatus);
              SWT_Info(" Event Status of Event %s is 0x%X and the expected status should be other than 0x2F", Dem_EventIdToString(eventId), EventStatus);
			  Validate((EventStatus != 0x2F), "Event Status passed as expected ", "Event Status failed which is not expected");
			   if(EventStatus != 0x2F)
			  {
				 SWT_Info("Event Status passed as expected");
				 SWT_Eval(1);
			  }
			  else
			  {
				 SWT_Info("Event Status failed which is not expected");
				 SWT_Eval(0);
			  }


              SWT_Info("Step4: Get DTC Status and verify status not failed");
			  dtcId = Dem_DtcIdFromEventId(eventId);
              DSMSim_GetStatusOfDTC(dtcId, &DTCStatus);
              SWT_Info(" DTC Status of Event %s is 0x%X and the expected status should be other than 0x2B", Dem_EventIdToString(eventId), DTCStatus);
			  Validate((DTCStatus != 0x2B), "DTC Status passed as expected ", "DTC Status failed which is not expected");
			  if(DTCStatus != 0x2B)
			  {
				 SWT_Info("DTC Status passed as expected");
				 SWT_Eval(1);
			  }
			  else
			  {
				 SWT_Info("DTC Status failed which is not expected");
				 SWT_Eval(0);
			  }

              SWT_Info("Step5: Set Event %s as FAILED",Dem_EventIdToString(eventId));
              Dem_ReportErrorStatus(eventId, DEM_EVENT_STATUS_FAILED);
              SWT_RunSystemMS(40);

              SWT_Info("Step6: Get Event Status and verify status to failed");
              Dem_GetEventStatus(eventId, &EventStatus);
              SWT_Info("Event Status of Event %s is 0x%X and the expected status is 0x2F", Dem_EventIdToString(eventId), EventStatus);
			  Validate((EventStatus == 0x2F), "Logged Event Status as expected", "Logged Event Status not as expected");
			  if(EventStatus == 0x2F)
			  {
				 SWT_Info("Logged Event Status as expected");
				 SWT_Eval(1);
			  }
			  else
			  {
				 SWT_Info("Logged Event Status not as expected");
				 SWT_Eval(0);
			  }

              SWT_Info("Step7: Get DTC Status and verify status to be failed");
              DSMSim_GetStatusOfDTC(dtcId, &DTCStatus);
              SWT_Info(" DTC Status of Event %s is 0x%X and the expected status is 0x2B", Dem_EventIdToString(eventId), DTCStatus);
			  Validate((DTCStatus == 0x2B), "Logged DTC Status as expected", "Logged DTC Status not as expected");
			  if(DTCStatus == 0x2B)
			  {
				 SWT_Info("Logged DTC Status as expected");
				 SWT_Eval(1);
			  }
			  else
			  {
				 SWT_Info("Logged DTC Status not as expected");
				 SWT_Eval(0);
			  }

              SWT_Info("Step8: Set Event %s as Passed",Dem_EventIdToString(eventId));
              Dem_ReportErrorStatus(eventId, DEM_EVENT_STATUS_PASSED);
              SWT_RunSystemMS(40);


              SWT_Info("Step9: Clear DTC records");
              Dem_ClearDTC(DEM_DTC_GROUP_ALL_DTCS);

              SWT_Info("Step10: Clear BFM records");
              rba_DemBfm_DeleteAllTrigger();

          }
          else
          {
              Validate(((EventID[eventId].DTC_ID) == 0x000000), "DTC of event is not assigned which is as expected", "DTC of event is assigned which is not as expected");
          }

          SWT_Info("End of RBDSM_SWT_DTC_Mapping for Event %s",Dem_EventIdToString(eventId));

    }

}

