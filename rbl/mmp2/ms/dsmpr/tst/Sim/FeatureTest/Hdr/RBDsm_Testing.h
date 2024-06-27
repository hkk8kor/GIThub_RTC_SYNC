 
/* TOOL GENERATED FILES*/
#ifndef RBDSM_TESTING_H__
#define RBDSM_TESTING_H__
//Header includes
#include "Std_Types.h"
#include "SwTest_Global.h"
#include "Dem.h"
#include "RBSMM.h" // for eval
#include "rba_STM.h"


typedef struct {  Dem_EventIdType EvId;
                  uint16 FailureThreshold;
				  uint8  IncrementStep;
				  uint16 RobustnessThreshold ;
				  const char EvId_Str[100];
				}DSMRobustnessTestType;


typedef struct {  Dem_EventIdType EvId;
				  uint16 SuspicionThreshold ;
				  const char EvId_Str[100];
				}DSMSuspicionTestType;


void DSM_SWT_RobustnessTest(DSMRobustnessTestType *EventRobustnessStruct, int elements);
void DSM_SWT_SuspicionTest(DSMSuspicionTestType *EventSuspicionStruct, int elements);
#endif
