#include "RBSYS_LocksImpl.c"



#include "TRBSYS_LocksImpl_Adaptor.h"
#include "RBSYS_Config.h"

/********************************************************/
/*                Get private variables                 */
/********************************************************/
int TRBSYS_Get_PMR_REG_ID(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    return RBSYS_PMR_REGID;
  #elif ((RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    return RBSYS_PLMR_REGID;
  #endif
}

int TRBSYS_Get_PMR_SEL_ID(void)
{
  #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
    return RBSYS_PMR_SELID;
  #elif ( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    return RBSYS_PLMR_SELID;
  #endif
}


/********************************************************/
/*                Set private variables                 */
/********************************************************/


/********************************************************/
/*              Access private Functions                */
/********************************************************/
