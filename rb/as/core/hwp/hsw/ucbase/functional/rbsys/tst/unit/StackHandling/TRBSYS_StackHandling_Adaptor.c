#include "RBSYS_StackHandling.c"



#include "TRBSYS_StackHandling_Adaptor.h"
#include "RBSYS_Config.h"

/********************************************************/
/*                Get private variables                 */
/********************************************************/
uint32 GetPrivate_STACK_LIMITRED_BYTES(void)
{
  return STACK_LIMITRED_BYTES;
}


uint32 GetPrivate_RBSYS_Stack_freespace(uint32 coreId)
{
  if(coreId == 0){
    return RBSYS_Stack0_freespace;
  }
  #if(RBFS_MCORE == RBFS_MCORE_ON)
    else if(coreId == 1){
      return RBSYS_Stack1_freespace;
    }
  #endif
  else
  {
    assert(FALSE);
    return 0;
  }
}


/********************************************************/
/*                Set private variables                 */
/********************************************************/


/********************************************************/
/*              Access private Functions                */
/********************************************************/
