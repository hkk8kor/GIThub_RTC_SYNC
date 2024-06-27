#ifndef RBDSM_SWT_COMPONENTSWITCH_H_
#define RBDSM_SWT_COMPONENTSWITCH_H_

#include "Std_Types.h"

typedef enum {
	ESPBase
} ComponentName;

extern int ComponentState_Sim(ComponentName TestComponent);
extern void MasterSystemStatesChar(uint8 MasterSystemStatenum);

#endif /* RBDSM_SWT_COMPONENTSWITCH_H_ */
