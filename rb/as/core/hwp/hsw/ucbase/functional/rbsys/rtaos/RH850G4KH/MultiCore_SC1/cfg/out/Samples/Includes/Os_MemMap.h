/*
 * This is Os_MemMap.h, auto-generated for:
 *   Project: rtaos_ccas_u2a_mcore_sc1
 *   Target:  RH850x2GHS
 *   Variant: U2C4
 *   Version: 5.0.11
 *   
 */
/* Generator info: generate_always */
/* This file is a sample version of Os_MemMap.h that can be used
 * as a starting template.
 * [$UKS 652] [$UKS 653] [$UKS 655] [$UKS 656] [$UKS 657]
 */
#if defined (NOT_DEFINED)

/* OS Uninitialized RAM: trace data */
#elif defined (OS_START_SEC_VAR_TRACE)
  #undef      OS_START_SEC_VAR_TRACE
  #define DEFAULT_START_SEC_VAR_NO_INIT_UNSPECIFIED
#elif defined (OS_STOP_SEC_VAR_TRACE)
  #undef      OS_STOP_SEC_VAR_TRACE
  #define DEFAULT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED

/* OS Uninitialized RAM: unspecified size */
#elif defined (OS_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef      OS_START_SEC_VAR_NO_INIT_UNSPECIFIED
  #define DEFAULT_START_SEC_VAR_NO_INIT_UNSPECIFIED
#elif defined (OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef      OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #define DEFAULT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED

/* OS reset cleared RAM: unspecified size */
#elif defined (OS_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef      OS_START_SEC_VAR_CLEARED_UNSPECIFIED
  #define DEFAULT_START_SEC_VAR_CLEARED_UNSPECIFIED
#elif defined (OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef      OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #define DEFAULT_STOP_SEC_VAR_CLEARED_UNSPECIFIED

/* OS Const (ROM): Often accessed */
#elif defined (OS_START_SEC_CONST_FAST_UNSPECIFIED)
  #undef      OS_START_SEC_CONST_FAST_UNSPECIFIED
  #define DEFAULT_START_SEC_CONST_FAST_UNSPECIFIED
#elif defined (OS_STOP_SEC_CONST_FAST_UNSPECIFIED)
  #undef      OS_STOP_SEC_CONST_FAST_UNSPECIFIED
  #define DEFAULT_STOP_SEC_CONST_FAST_UNSPECIFIED

/* OS Const (ROM): unspecified size */
#elif defined (OS_START_SEC_CONST_UNSPECIFIED)
  #undef      OS_START_SEC_CONST_UNSPECIFIED
  #define DEFAULT_START_SEC_CONST_UNSPECIFIED
#elif defined (OS_STOP_SEC_CONST_UNSPECIFIED)
  #undef      OS_STOP_SEC_CONST_UNSPECIFIED
  #define DEFAULT_STOP_SEC_CONST_UNSPECIFIED

/* (Compatability) Callouts from the OS. */
#elif defined (OS_START_SEC_APPL_CODE)
  #undef      OS_START_SEC_APPL_CODE
  #define DEFAULT_START_SEC_APPL_CODE
#elif defined (OS_STOP_SEC_APPL_CODE)
  #undef      OS_STOP_SEC_APPL_CODE
  #define DEFAULT_STOP_SEC_APPL_CODE

/* Callouts from the OS. */
#elif defined (OS_START_SEC_CALLOUT_CODE)
  #undef      OS_START_SEC_CALLOUT_CODE
  #define DEFAULT_START_SEC_CALLOUT_CODE
#elif defined (OS_STOP_SEC_CALLOUT_CODE)
  #undef      OS_STOP_SEC_CALLOUT_CODE
  #define DEFAULT_STOP_SEC_CALLOUT_CODE

/* OS Fast Code */
#elif defined (OS_START_SEC_CODE_FAST)
  #undef      OS_START_SEC_CODE_FAST
  #define DEFAULT_START_SEC_CODE_FAST
#elif defined (OS_STOP_SEC_CODE_FAST)
  #undef      OS_STOP_SEC_CODE_FAST
  #define DEFAULT_STOP_SEC_CODE_FAST

/* OS Library Code */
#elif defined (OS_START_SEC_CODE)
  #undef      OS_START_SEC_CODE
  #define DEFAULT_START_SEC_CODE
#elif defined (OS_STOP_SEC_CODE)
  #undef      OS_STOP_SEC_CODE
  #define DEFAULT_STOP_SEC_CODE

/* OS Interrupt vectors */
#elif defined (OS_START_SEC_VECTORS)
  #undef      OS_START_SEC_VECTORS
  #define DEFAULT_START_SEC_VECTORS
#elif defined (OS_STOP_SEC_VECTORS)
  #undef      OS_STOP_SEC_VECTORS
  #define DEFAULT_STOP_SEC_VECTORS

/* OS Core 0 Code */
#elif defined (OS_START_SEC_CODE_CORE0_LOCAL)
  #undef      OS_START_SEC_CODE_CORE0_LOCAL
  #define DEFAULT_START_SEC_CODE
#elif defined (OS_STOP_SEC_CODE_CORE0_LOCAL)
  #undef      OS_STOP_SEC_CODE_CORE0_LOCAL
  #define DEFAULT_STOP_SEC_CODE

/* OS Core 1 Code */
#elif defined (OS_START_SEC_CODE_CORE1_LOCAL)
  #undef      OS_START_SEC_CODE_CORE1_LOCAL
  #define DEFAULT_START_SEC_CODE
#elif defined (OS_STOP_SEC_CODE_CORE1_LOCAL)
  #undef      OS_STOP_SEC_CODE_CORE1_LOCAL
  #define DEFAULT_STOP_SEC_CODE

/* MemoryMappingCodeLocations */
#elif defined (OS_START_SEC_CONST_CORE0_LOCAL)
  #undef      OS_START_SEC_CONST_CORE0_LOCAL
#elif defined (OS_STOP_SEC_CONST_CORE0_LOCAL)
  #undef      OS_STOP_SEC_CONST_CORE0_LOCAL

#elif defined (OS_START_SEC_CONST_CORE1_LOCAL)
  #undef      OS_START_SEC_CONST_CORE1_LOCAL
#elif defined (OS_STOP_SEC_CONST_CORE1_LOCAL)
  #undef      OS_STOP_SEC_CONST_CORE1_LOCAL

#elif defined (OS_START_SEC_CALLOUT_CODE)
  #undef      OS_START_SEC_CALLOUT_CODE
#elif defined (OS_STOP_SEC_CALLOUT_CODE)
  #undef      OS_STOP_SEC_CALLOUT_CODE

#else
  #error No section in Os_MemMap was matched
#endif
