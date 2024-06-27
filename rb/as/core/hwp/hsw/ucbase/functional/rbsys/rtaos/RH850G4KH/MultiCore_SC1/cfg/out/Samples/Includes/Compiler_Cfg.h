/*
 * This is Compiler_Cfg.h for target platform: RH850x2GHS/U2C4
 */

/* [COMPILER054] [COMPILER055] */
#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

/*
 * Compiler_Cfg.c is normally a system-wide header file.
 * Typically the system integrator will take the settings
 * from each module and construct this by hand.
 * The contents of "Os_Compiler_Cfg.h" can be used by
 * the system integrator for this purpose.
 */
#include <Os_Compiler_Cfg.h>

#ifndef OS_VAR_NO_INIT_CORE0_LOCAL
  #define OS_VAR_NO_INIT_CORE0_LOCAL /* default */ /* Core 0 local data never initialized */
  #define OS_VAR_CLEARED_CORE0_LOCAL /* default */ /* Core 0 local data cleared after reset. */
  #define OS_VAR_NO_INIT_CORE1_LOCAL /* default */ /* Core 1 local data never initialized */
  #define OS_VAR_CLEARED_CORE1_LOCAL /* default */ /* Core 1 local data cleared after reset. */
#endif
#ifndef OS_CODE_CORE0_LOCAL
  #define OS_CODE_CORE0_LOCAL /* default */ /* Core 0 code. */
  #define OS_CODE_CORE1_LOCAL /* default */ /* Core 1 code. */
#endif
#ifndef OS_CALLOUT_CODE
  #define OS_CALLOUT_CODE
#endif
#endif /* COMPILER_CFG_H */
