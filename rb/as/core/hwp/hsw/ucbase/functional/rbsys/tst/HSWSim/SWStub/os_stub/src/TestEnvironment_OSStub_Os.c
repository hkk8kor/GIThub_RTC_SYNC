#include "TestEnironment_OSStub_Os.h"

// It was requested to use SWT_RunSystemPreProc() in combination with a reset. Therefore it was necessary 
// to move this part from OSStub_Os.c to this TestEnvironment_OSStub_Os.c (different reset scope). 
// 
// see 3938221: [HSW][SIM] Support for Recovery Reset
void OSSim_DefaultProcedureExecuter(Procedure proc)
{
  proc();
}
OSSimProcessExecuter OSSim_ProcessExecuter       = &OSSim_DefaultProcedureExecuter;