#ifndef TRBSYS_GUARDCONFIG_H__
#define TRBSYS_GUARDCONFIG_H__

#include "SwTest_Global.h"
#include "RBSYS_Config.h"
#include "RBSYS_GuardConfigCommon.h"

extern void call_RBSYS_setCoreSPID(uint32 nSPID);
extern uint32 call_RBSYS_getCoreSPID(void);
extern void call_RBSYS_PEGuardInit(void);
extern void call_RBSYS_PBUSGuardInit(void);
extern void call_RBSYS_FSW_FinalGuardInit(void);

#if( RBFS_uCFamily == RBFS_uCFamily_RenesasU2A )
  extern uint32 TRBSYS_GetNumOfPBUSGuards(void);
  extern const RBSYS_BUSGuardConfig_t* TRBSYS_GetPBUSGuardsPointer(void);
#endif

#if( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
  typedef struct
  {
    uint32 StartAddr;
    uint32 Size;
    uint32 PermittedBusMasters; /* Read as bitfield */
  } TRBSYS_NOCFirewallRegionConfig_t;
  typedef struct 
  {
    const TRBSYS_NOCFirewallRegionConfig_t* regions;
    volatile rba_Reg_FIREWALL_tst * fwPtr;
    uint32 numRegions;
  } TRBSYS_NOCFirewallConfig_t;

  extern void TRBSYS_Callrbsys_NOCFirewallConfigure(const TRBSYS_NOCFirewallConfig_t* config);

  extern void TRBSYS_GuardConfig_InvalidRegionTypeConfiguration(void);
#endif


#endif /* multi include protection */
