#include "TRBSYS_Os_ConfigInterrupts.h"
#include "Platform_Types.h"

uint32 TRBSYS_Os_Enable_ISRSTM04_CallCnt = 0;
uint32 TRBSYS_Os_Clear_ISRSTM04_CallCnt = 0;
uint32 TRBSYS_Os_ISRSTM04_Status = 0;
void Os_Enable_ISRSTM04(void)
{
  TRBSYS_Os_Enable_ISRSTM04_CallCnt++;
  TRBSYS_Os_ISRSTM04_Status |= 1;
}
void Os_Clear_ISRSTM04(void)
{
  TRBSYS_Os_Clear_ISRSTM04_CallCnt++;
  TRBSYS_Os_ISRSTM04_Status &= ~1;
}

uint32 TRBSYS_Os_Enable_ISRSTM05_CallCnt = 0;
uint32 TRBSYS_Os_Clear_ISRSTM05_CallCnt = 0;
uint32 TRBSYS_Os_ISRSTM05_Status = 0;
void Os_Enable_ISRSTM05(void)
{
  TRBSYS_Os_Enable_ISRSTM05_CallCnt++;
  TRBSYS_Os_ISRSTM05_Status |= 1;
}
void Os_Clear_ISRSTM05(void)
{
  TRBSYS_Os_Clear_ISRSTM05_CallCnt++;
  TRBSYS_Os_ISRSTM05_Status &= ~1;
}

uint32 TRBSYS_Os_Enable_ISRSWINT0_CallCnt = 0;
uint32 TRBSYS_Os_Clear_ISRSWINT0_CallCnt = 0;
uint32 TRBSYS_Os_ISRSWINT0_Status = 0;
void Os_Enable_ISRSWINT0(void)
{
  TRBSYS_Os_Enable_ISRSWINT0_CallCnt++;
  TRBSYS_Os_ISRSWINT0_Status |= 1;
}
void Os_Clear_ISRSWINT0(void)
{
  TRBSYS_Os_Clear_ISRSWINT0_CallCnt++;
  TRBSYS_Os_ISRSWINT0_Status &= ~1;
}

uint32 TRBSYS_Os_Enable_ISRCommonTimer_CallCnt = 0;
uint32 TRBSYS_Os_Clear_ISRCommonTimer_CallCnt = 0;
uint32 TRBSYS_Os_ISRCommonTimer_Status = 0;
void Os_Enable_ISRCommonTimer(void)
{
  TRBSYS_Os_Enable_ISRCommonTimer_CallCnt++;
  TRBSYS_Os_ISRCommonTimer_Status |= 1;
}
void Os_Clear_ISRCommonTimer(void)
{
  TRBSYS_Os_Clear_ISRCommonTimer_CallCnt++;
  TRBSYS_Os_ISRCommonTimer_Status &= ~1;
}