#include "TRBRCFG_UnsupportedConfig.h"

// set init values
RBRCFG_ConfId_t stubConfId = RBRCFG_ConfId_default;
boolean stubIsUnsupportedCPU = FALSE;
uint32 stubDebug = 0;

void RBRCFG_ReportUnsupportedConfig(RBRCFG_ConfId_t confId, boolean isUnsupported, uint32 debug)
{
  stubConfId = confId;
  stubIsUnsupportedCPU = isUnsupported;
  stubDebug = debug;
}