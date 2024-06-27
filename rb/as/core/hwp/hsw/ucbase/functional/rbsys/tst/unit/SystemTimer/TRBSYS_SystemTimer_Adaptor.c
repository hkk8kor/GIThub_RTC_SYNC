#include "RBSYS_SystemTimer.h"
#include "TRBSYS_SystemTimer.h"



#include "TRBSYS_SystemTimer_Adaptor.h"

/********************************************************/
/*                Get private variables                 */
/********************************************************/

/********************************************************/
/*                Set private variables                 */
/********************************************************/
void TRBSYS_setSyncTime(uint32 value)
{
  RBSYS_SystemTimerSynctimeCnt = value;
}

