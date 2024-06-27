#ifndef TRBSYS_UCRESET_ADAPTER_H__
#define TRBSYS_UCRESET_ADAPTER_H__

#include "RBSYS_uCResetCtrl.h"
#include "RBSYS_uCResetInfo.h"

extern void TRBSYS_SetInvalidRequestedResetType(void);
extern void TRBSYS_SetUndefinedRequestedResetType(void);
extern void TRBSYS_SetValidRequestedResetType(void);

extern void TRBSYS_TriggerReset(void);
extern void TRBSYS_ExecuteReset(void);

#endif