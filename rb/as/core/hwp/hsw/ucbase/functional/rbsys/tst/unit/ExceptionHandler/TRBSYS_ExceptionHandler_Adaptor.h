#ifndef TRBSYS_EXCEPTIONHANDLER_ADAPTOR_H__
#define TRBSYS_EXCEPTIONHANDLER_ADAPTOR_H__

#include "RBSYS_ExceptionHandler.h"
#include "RBSYS_Config.h"

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    extern void TRBSYS_Set_ExceptionProgramCounterForDebug(uint32 coreId, uint32 LP);
#endif

#endif