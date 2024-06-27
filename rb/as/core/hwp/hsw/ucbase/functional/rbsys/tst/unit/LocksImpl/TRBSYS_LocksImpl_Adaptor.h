#ifndef TRBSYS_LOCKSIMPL_ADAPTOR_H__
#define TRBSYS_LOCKSIMPL_ADAPTOR_H__

#include "SwTest_Global.h"                      // for SWT functionality
#include "RBSYS_Config.h"

#include "RBSYS_LocksImplIntern.h"

/********************************************************/
/*                Get private variables                 */
/********************************************************/
#if (RBFS_MCORE == RBFS_MCORE_ON)
  extern volatile lockstr_t RBSYS_common_lock;
#endif

extern int TRBSYS_Get_PMR_REG_ID(void);
extern int TRBSYS_Get_PMR_SEL_ID(void);


/********************************************************/
/*                Set private variables                 */
/********************************************************/


/********************************************************/
/*              Access private Functions                */
/********************************************************/


#endif