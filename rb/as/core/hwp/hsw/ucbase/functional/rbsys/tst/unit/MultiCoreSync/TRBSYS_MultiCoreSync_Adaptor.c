#include "RBSYS_MultiCoreSync.c"



#include "TRBSYS_MultiCoreSync_Adaptor.h"
#include "RBSYS_Config.h"
#include <assert.h>

#if( RBFS_HexBlockBuild == RBFS_HexBlockBuild_APPLICATION )
  #if (RBFS_MCORE == RBFS_MCORE_ON)
    /********************************************************/
    /*                Get private variables                 */
    /********************************************************/
    volatile uint8* GetPrivate_RBSYS_Core0_arrived_ptr(unsigned int sync_phase)
    {
      //assert(sync_phase < RBSYS_MaxNumberOfStartupSyncPhases);
      return &RBSYS_StartupSync.ptr[0][sync_phase];
    }

    volatile uint8* GetPrivate_RBSYS_Core1_arrived_ptr(unsigned int sync_phase)
    {
      //assert(sync_phase < RBSYS_MaxNumberOfStartupSyncPhases);
      return &RBSYS_StartupSync.ptr[1][sync_phase];
    }

    volatile uint8* GetPrivate_RBSYS_StartupSyncPtr(unsigned int coreid)
    {
      return RBSYS_StartupSync.ptr[coreid];
    }
    void SetPrivate_RBSYS_RuntimeResetSyncPhase(unsigned int core, unsigned int value)
    {
      RBSYS_RuntimeResetSync.ptr[core][RBSYS_RuntimeResetSyncPhase_BeforeReset] = value;
    }


    /********************************************************/
    /*                Set private variables                 */
    /********************************************************/
    void SetPrivate_RBSYS_Core0_arrived(unsigned int sync_phase, uint8 value)
    {
      RBSYS_StartupSync.ptr[0][sync_phase] = value;
    }

    void SetPrivate_RBSYS_Core1_arrived(unsigned int sync_phase, uint8 value)
    {
      RBSYS_StartupSync.ptr[1][sync_phase] = value;
    }


    /********************************************************/
    /*              Access private Functions                */
    /********************************************************/


    /********************************************************/
    /*              Helper Functions                        */
    /********************************************************/
  #endif // RBFS_MCORE
#endif // RBFS_HexBlockBuild
