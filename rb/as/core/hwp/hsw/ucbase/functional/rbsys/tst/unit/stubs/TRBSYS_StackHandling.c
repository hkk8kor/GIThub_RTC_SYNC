#include "SwTest_Global.h"                      // for SWT functionality

#include "RBSYS_StackHandling.h"
#include "TRBSYS_StackHandling.h"

unsigned int RB_Stack0_Bootblock[10];
unsigned int RB_Stack1_Bootblock[10];

unsigned int* const RB_SP0_Bootblock = &RB_Stack0_Bootblock[0];
unsigned int* const RB_SP1_Bootblock = &RB_Stack1_Bootblock[0];


volatile unsigned int RB_Stack0_FSW[RB_STACK0_ARRAYSIZE];
volatile unsigned int RB_Stack1_FSW[RB_STACK0_ARRAYSIZE];

volatile unsigned int* const RB_SP0_FSW = &RB_Stack0_FSW[0];
volatile unsigned int* const RB_SP1_FSW = &RB_Stack0_FSW[0];


uint32 TRBSYS_stackInit_cnt = 0;
void RBSYS_stackInit(volatile unsigned int* const asm_sp0, volatile unsigned int* const asm_sp1)
{
  TRBSYS_stackInit_cnt++;
}