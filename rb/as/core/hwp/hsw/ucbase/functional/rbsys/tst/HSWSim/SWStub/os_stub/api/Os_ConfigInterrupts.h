/*
 * Include this header in order to allow any configured EI maskable interrupt
 * to be enabled or disabled
 */
#ifndef OS_CONFIGINTERRUPTS_H
#define OS_CONFIGINTERRUPTS_H

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
#define Os_Enable_ISRSTM04()
#define Os_Clear_ISRSTM04()
#define Os_Enable_ISRSTM05()
#define Os_Clear_ISRSTM05()
#define Os_Enable_ISRSWINT0()
#define Os_Clear_ISRSWINT0()

#endif /* OS_CONFIGINTERRUPTS_H */
