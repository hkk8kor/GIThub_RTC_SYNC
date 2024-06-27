#ifndef TRBSYS_OS_CONFIGINTERRUPTS_H__
#define TRBSYS_OS_CONFIGINTERRUPTS_H__

#include "Platform_Types.h"

#define Os_Enable_ISRMTTCANI0()
#define Os_Enable_ISRMCAN0I0()
#define Os_Enable_ISRMCAN1I0()
#define Os_Enable_ISRMCAN2I0()
#define Os_Enable_ISRCAN0REC()
#define Os_Enable_ISRCAN0TRX()
#define Os_Enable_ISRCAN1REC()
#define Os_Enable_ISRCAN1TRX()
#define Os_Enable_ISRCAN2REC()
#define Os_Enable_ISRCAN2TRX()
#define Os_Enable_ISRCAN6REC()
#define Os_Enable_ISRCAN6TRX()
#define Os_Enable_ISRCAN8REC()
#define Os_Enable_ISRCAN8TRX()
#define Os_Enable_ISRFLX0LINE0()
#define Os_Enable_ISRFLX1LINE0()
#define Os_Enable_ISRRLIN30RX()
#define Os_Enable_ISRRLIN30STATUS()
#define Os_Enable_ISRRLIN31RX()
#define Os_Enable_ISRRLIN31STATUS()

extern uint32 TRBSYS_Os_Enable_ISRSTM04_CallCnt;
extern uint32 TRBSYS_Os_Clear_ISRSTM04_CallCnt;
extern uint32 TRBSYS_Os_ISRSTM04_Status;
extern void Os_Enable_ISRSTM04(void);
extern void Os_Clear_ISRSTM04(void);

extern uint32 TRBSYS_Os_Enable_ISRSTM05_CallCnt;
extern uint32 TRBSYS_Os_Clear_ISRSTM05_CallCnt;
extern uint32 TRBSYS_Os_ISRSTM05_Status;
extern void Os_Enable_ISRSTM05(void);
extern void Os_Clear_ISRSTM05(void);

extern uint32 TRBSYS_Os_Enable_ISRSWINT0_CallCnt;
extern uint32 TRBSYS_Os_Clear_ISRSWINT0_CallCnt;
extern uint32 TRBSYS_Os_ISRSWINT0_Status;
extern void Os_Enable_ISRSWINT0(void);
extern void Os_Clear_ISRSWINT0(void);

extern uint32 TRBSYS_Os_Enable_ISRCommonTimer_CallCnt;
extern uint32 TRBSYS_Os_Clear_ISRCommonTimer_CallCnt;
extern uint32 TRBSYS_Os_ISRCommonTimer_Status;
extern void Os_Enable_ISRCommonTimer(void);
extern void Os_Clear_ISRCommonTimer(void);

#endif