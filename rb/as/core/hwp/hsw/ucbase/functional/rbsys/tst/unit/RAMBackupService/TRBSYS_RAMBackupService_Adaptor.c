#include "RBSYS_RAMBackupService.c"



#include "TRBSYS_RAMBackupService_Adaptor.h"
#include "RBSYS_PlantStartupCtrl.h"

/********************************************************/
/*                Get private variables                 */
/********************************************************/
uint32 TRBSYS_getRBSYSBaseOSRequestbySW_u32(void)
{
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);
  RBMESG_RcvMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);

  return l_RBMESG_RBSYSBaseOSRequestbySW_u32;
}

void TRBSYS_setRBSYSBaseOSRequestbySW_u32(uint32 value)
{
  RBMESG_DefineMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);
  l_RBMESG_RBSYSBaseOSRequestbySW_u32 = value;
  RBMESG_SendMESGDef(RBMESG_RBSYSBaseOSRequestbySW_u32);
}


/********************************************************/
/*                Set private variables                 */
/********************************************************/

/********************************************************/
/*              Access private Functions                */
/********************************************************/
