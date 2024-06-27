#ifndef TRBSYS_MULTICORESYNC_ADAPTOR_H__
#define TRBSYS_MULTICORESYNC_ADAPTOR_H__

#include "RBSYS_Config.h"
#include "RBSYS_MultiCoreSync.h"

#if (RBFS_MCORE == RBFS_MCORE_ON)
/********************************************************/
/*                Get private variables                 */
/********************************************************/

extern volatile uint8* GetPrivate_RBSYS_Core0_arrived_ptr(unsigned int sync_phase);
extern volatile uint8* GetPrivate_RBSYS_Core1_arrived_ptr(unsigned int sync_phase);
extern volatile uint8* GetPrivate_RBSYS_StartupSyncPtr(unsigned int coreid);

/********************************************************/
/*                Set private variables                 */
/********************************************************/
extern void SetPrivate_RBSYS_Core0_arrived(unsigned int sync_phase, uint8 value);
extern void SetPrivate_RBSYS_Core1_arrived(unsigned int sync_phase, uint8 value);
extern void SetPrivate_RBSYS_RuntimeResetSyncPhase(unsigned int core, unsigned int value);

/********************************************************/
/*              Access private Functions                */
/********************************************************/


/********************************************************/
/*              Helper Functions                        */
/********************************************************/
#endif

#endif