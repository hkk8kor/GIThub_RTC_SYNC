#ifndef TRBSYS_UCRESET_H__
#define TRBSYS_UCRESET_H__

#include "RBSYS_Config.h"
#include "Platform_Types.h"

#include "RBSYS_uCResetInfo.h"
#include "TRBSYS_uCRegisters.h"

extern uint32 TRBSYS_uCResetSkipBootBlock_CallCnt;

extern void TRBSYS_setTerminalReset(void);
extern void TRBSYS_setSoftwareReset(void);
extern void TRBSYS_setSWResetTriggeredByFSW(void);

static inline void TRBSYS_setSWResetByApplicationReset(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    RBSYS_RESF = RBSYS_RESET_FLAG_SW_APPLICATION_0;
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    MC_RGM_PER.FES = RBSYS_RESET_FUNC_FLAG_SW_RESET;
  #endif
}

static inline void TRBSYS_setSWResetBySystemReset(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    RBSYS_RESF = RBSYS_RESET_FLAG_SW_SYSTEM_0;
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    MC_RGM_PER.DES = RBSYS_RESET_DEST_FLAG_SW_RESET;
  #endif
}

#endif