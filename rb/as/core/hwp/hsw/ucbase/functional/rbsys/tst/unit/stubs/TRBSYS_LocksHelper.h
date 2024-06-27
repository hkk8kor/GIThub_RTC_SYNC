#ifndef TRBSYS_LOCKSHELPER_H__
#define TRBSYS_LOCKSHELPER_H__


#include "Std_Types.h"


typedef struct{
    uint32 fnc_call_cnt;
    uint32 nest_cnt;
} TRBSYS_LockCounter_t;

extern TRBSYS_LockCounter_t TRBSYS_CoreLocalLock;
extern TRBSYS_LockCounter_t TRBSYS_GlobLock;





#endif
