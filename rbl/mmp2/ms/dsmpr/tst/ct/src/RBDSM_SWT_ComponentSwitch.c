/* TOOL GENERATED FILES*/
#include "RBDSM_SWT_STM.h"

int ComponentState_Sim(ComponentName TestComponent)
{
    int ComponentStateSim;

    switch(TestComponent)
    {
    }//end of switch Statement
    return ComponentStateSim;
}//end of function int ComponentState_Sim

void MasterSystemStatesChar(uint8 MasterSystemStatenum)
{
    MasterSystem_DegStateName MasterSystemDegStatesChar[]={
    };
	SWT_Info("Master system  is in %s state", MasterSystemDegStatesChar[MasterSystemStatenum]);
}
