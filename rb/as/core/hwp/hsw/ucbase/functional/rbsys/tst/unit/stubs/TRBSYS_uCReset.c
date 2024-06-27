#include "RBSYS_Config.h"


#include "RBSYS_uCResetInfo.h"
#include "RBSYS_uCResetInternal.h"
#include "RBSYS_uCResetCtrl.h"
#include "TRBSYS_uCReset.h"
#include "Platform_Types.h"

#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
uint32 TRBSYS_uCResetSkipBootBlock_CallCnt = 0;
void RBSYS_uCReset_ApplResetSkipBootBlock(void)
{
  TRBSYS_uCResetSkipBootBlock_CallCnt++;
}
#endif


static boolean terminalReset = FALSE;

void TRBSYS_setTerminalReset(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    RBSYS_RESF = RBSYS_RESET_FLAG_TERMINAL;
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    MC_RGM_PER.DES = RBSYS_RESET_DEST_FLAG_RESETPIN_A;
  #endif
}


static boolean softwareReset = FALSE;
void TRBSYS_setSoftwareReset(void)
{
  #if( (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) \
    || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
    RBSYS_RESF = RBSYS_RESET_FLAG_SW_APPLICATION_0;
  #elif( RBFS_uCFamily == RBFS_uCFamily_STMStellar )
    MC_RGM_PER.FES = RBSYS_RESET_FUNC_FLAG_SW_RESET;
  #endif
}

static boolean SWResetTriggeredByFSW = FALSE;
void TRBSYS_setSWResetTriggeredByFSW(void)
{
  SWResetTriggeredByFSW = TRUE;
}
boolean RBSYS_isSWResetTriggeredByFSW(void)
{
  return SWResetTriggeredByFSW;
}


void RBSYS_ClearResetFactorsAtStartup(void)
{
  #if( RBFS_uCFamily != RBFS_uCFamily_STMStellar )
    // If a Terminal Reset was seen, previous Application and System Resets are not relevant anymore */
    if( RBSYS_isTerminalReset() )
    {
        // Delete System, Application and Terminal Reset flag => Next reset can be identified from now on
        RBSYS_RESFC = RBSYS_RESET_FLAG_SW_SYSTEM_0 | RBSYS_RESET_FLAG_SW_APPLICATION_0 | RBSYS_RESET_FLAG_TERMINAL;
        RBSYS_RESF &= ~RBSYS_RESFC;
    }
  #endif
}

#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
  void RBSYS_ClearResetFactorsAfterSafetyTests(void)
  {
    #if (RBFS_uCFamily == RBFS_uCFamily_RenesasP1x)
      RBSYS_RESFC = (RBSYS_RESET_FLAG_POWERON | RBSYS_RESET_FLAG_HW_BIST);
    #elif( (RBFS_uCFamily == RBFS_uCFamily_RenesasU2A) || (RBFS_uCFamily == RBFS_uCFamily_RenesasU2C) )
      RBSYS_RESFC = (RBSYS_RESET_FLAG_POWERON | RBSYS_RESET_FLAG_HW_BIST_F0 |
              RBSYS_RESET_FLAG_HW_BIST_F1 | RBSYS_RESET_FLAG_HW_BIST_F2);
    #endif
  }
#endif