#include "RBSYS_ExceptionHandler.c"



#include "TRBSYS_ExceptionHandler_Adaptor.h"
#include "RBSYS_Config.h"

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    void TRBSYS_Set_ExceptionProgramCounterForDebug(uint32 coreId, uint32 LP)
    {
        RBSYS_ExceptionProgramCounterForDebug[coreId] = LP;
    }
#endif
