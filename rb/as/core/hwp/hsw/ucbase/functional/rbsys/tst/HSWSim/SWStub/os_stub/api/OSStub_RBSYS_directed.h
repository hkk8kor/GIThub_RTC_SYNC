#ifndef OSSTUB_RBSYS_DIRECTED_H__
#define OSSTUB_RBSYS_DIRECTED_H__

#include "Os_Cfg.h" ///< RBFS_SysTask0p5ms

#define OSSTUB_RBSYS_API_LEVEL  1
///< v1: 24-Apr-2023: initial revision

#if( RBFS_SysTask0p5ms == RBFS_SysTask0p5ms_OFF )

  /// [ossim_private_500usec_execution]
  /// only available without 500usec task, should be only
  /// used by RBSYS or OSSim internal.
  extern uint32 ossim_priv_500usec_cnt;

#endif

#endif