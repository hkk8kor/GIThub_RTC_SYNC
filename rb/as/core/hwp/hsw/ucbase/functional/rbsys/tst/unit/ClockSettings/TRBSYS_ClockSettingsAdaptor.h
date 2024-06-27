#ifndef TRBSYS_CLOCKSETTINGSADAPTOR_H__
#define TRBSYS_CLOCKSETTINGSADAPTOR_H__

#include "SwTest_Global.h"
#include "RBSYS_Config.h"


#if((RBFS_TargetDevice == RBFS_TargetDevice_RenesasD1) || (RBFS_TargetDevice == RBFS_TargetDevice_RenesasD2))
extern void call_RBSYS_SetupClocks_RenesasP1x(void);
#endif

#if(( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A ) || ( RBFS_uCFamily == RBFS_uCFamily_RenesasU2C ))
    extern void call_RBSYS_SetupClocks_RenesasU2A(void);
#endif

#endif /* multi include protection */
