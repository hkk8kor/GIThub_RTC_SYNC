#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_BBFSW_StartupServices.h"
#include "TRBSYS_BBFSW_StartupServices.h"



volatile RBSYS_BURAM_BB_FSW_INTERFACE_t RBSYS_BURAM_BB_FSW_INTERFACE;

void TRBSYS_setBootblockRequest(uint32 nRequest)
{
  RBSYS_BURAM_BB_FSW_INTERFACE.BootblockRequest = nRequest;
}