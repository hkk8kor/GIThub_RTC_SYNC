// Wrap UnitUnderTest
#include "RBSYS_ClockSettings.c"



#include "RBSYS_Config.h"
// Access API for private variables and functions
#include "TRBSYS_ClockSettingsAdaptor.h"


/* ************************************************ */
/*    indirect calls to achieve coverage reporting  */
/* ************************************************ */


#if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2))

void call_RBSYS_SetupClocks_RenesasP1x(void)
{
    RBSYS_SetupClocks_RenesasP1x();
}

#endif

#if(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))

void call_RBSYS_SetupClocks_RenesasU2A(void)
{
    RBSYS_SetupClocks_RenesasU2A();
}

#endif
