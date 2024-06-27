#include "SwTest_Global.h"                      // for SWT functionality

#include "TRBSYS_GHS.h"



uint32 TRBSYS_start_cnt = 0;
void _start(void)
{
  TRBSYS_start_cnt++;
}

uint32 TRBSYS_main_cnt = 0;
void _main(void) //< provided by GHS if configured for CPP
{
  TRBSYS_main_cnt++;
}


