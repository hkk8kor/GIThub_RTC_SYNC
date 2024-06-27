#ifndef TRBRCFG_UNSUPPORTEDCONFIG__
#define TRBRCFG_UNSUPPORTEDCONFIG__

#include "SwTest_Global.h"

typedef enum
{
  RBRCFG_ConfId_default = 0,
  RBRCFG_ConfId_UnsupportedCPU

} RBRCFG_ConfId_t;


#define RBRCFG_STATIC_REGISTER_CONF_ID(conf_id) \
          const RBRCFG_ConfId_t RBRCFG_ConfId_t__My_ID = conf_id;

extern void RBRCFG_ReportUnsupportedConfig(RBRCFG_ConfId_t confId, boolean isUnsupported, uint32 debug);

extern RBRCFG_ConfId_t stubConfId;
extern boolean stubIsUnsupportedCPU;
extern uint32 stubDebug;


#endif
