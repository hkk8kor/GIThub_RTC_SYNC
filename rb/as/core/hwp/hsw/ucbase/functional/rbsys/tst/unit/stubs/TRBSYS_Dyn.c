#include "RBSYS_Config.h"

#include "TRBSYS_Os.h"

void Os_Entry_TaskBaseCtrlCycx24(void){}
void Os_Entry_TaskBaseCtrlCycx8(void){}
void Os_Entry_TaskBaseCtrlCycx4(void){}
void Os_Entry_TaskBaseCtrlCycx2p(void){}
void Os_Entry_TaskBaseCtrlCycx2(void){}
void Os_Entry_TaskBaseCtrlCycx1Low(void){}
void Os_Entry_TaskFlexray(void){}
void Os_Entry_TaskBaseCtrlCycx1High(void){}
void Os_Entry_Task1ms(void){}
void Os_Entry_Task0p5ms(void){}
void Os_Entry_TaskInitP(void){}
void Os_Entry_TaskInit(void){}
void Os_Entry_TaskTPSWKillCore0(void){}
void Os_Entry_TaskTPSWKillCore1(void){}
#if (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_VMPS)
  void Os_Entry_TaskBaseCtrlCycx4pLow(void){}
  void Os_Entry_TaskBaseCtrlCycx200Background(void){}
  void Os_Entry_TaskEventCtrlExtPrio1(void){}
  void Os_Entry_TaskEventCtrlExtPrio2(void){}
#elif (RBFS_TaskSchemeExtension == RBFS_TaskSchemeExtension_HostCore0GuestCore1)
  void Os_Entry_TaskBaseCtrlCycx1Guest(void){}
  void Os_Entry_TaskBaseCtrlCycx2Guest(void){}
  void Os_Entry_TaskBaseCtrlCycx4Guest(void){}
  void Os_Entry_TaskBaseCtrlCycx10Guest(void){}
  void Os_Entry_TaskBaseCtrlCycx20Guest(void){}
#endif