/*
 * This is Os_MemMap.h, auto-generated for:
 *   Project: rtaos_ccas_stellar_mcore_sc1
 *   Target:  Stellar-R52-GHS
 *   Variant: SR6P6
 *   Version: 5.0.4
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
  #pragma ghs section data=".os_data"
#elif defined (OS_STOP_SEC_VAR_TRACE)
  #undef      OS_STOP_SEC_VAR_TRACE
  #pragma ghs section data=default

/* OS Uninitialized RAM: unspecified size */
#elif defined (OS_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef      OS_START_SEC_VAR_NO_INIT_UNSPECIFIED
  #pragma ghs section bss=".os_bss"
#elif defined (OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef      OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #pragma ghs section bss=default

/* OS reset cleared RAM: unspecified size */
#elif defined (OS_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef      OS_START_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma ghs section data=".os_data"
#elif defined (OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef      OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma ghs section data=default

/* OS Const (ROM): Often accessed */
#elif defined (OS_START_SEC_CONST_FAST_UNSPECIFIED)
  #undef      OS_START_SEC_CONST_FAST_UNSPECIFIED
  #pragma ghs section rodata=".os_const"
#elif defined (OS_STOP_SEC_CONST_FAST_UNSPECIFIED)
  #undef      OS_STOP_SEC_CONST_FAST_UNSPECIFIED
  #pragma ghs section rodata=default

/* OS Const (ROM): unspecified size */
#elif defined (OS_START_SEC_CONST_UNSPECIFIED)
  #undef      OS_START_SEC_CONST_UNSPECIFIED
  #pragma ghs section rodata=".os_const"
#elif defined (OS_STOP_SEC_CONST_UNSPECIFIED)
  #undef      OS_STOP_SEC_CONST_UNSPECIFIED
  #pragma ghs section rodata=default

/* (Compatability) Callouts from the OS. */
#elif defined (OS_START_SEC_APPL_CODE)
  #undef      OS_START_SEC_APPL_CODE
  #pragma ghs section text=".app_text"
#elif defined (OS_STOP_SEC_APPL_CODE)
  #undef      OS_STOP_SEC_APPL_CODE
  #pragma ghs section text=default

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
  #pragma ghs section text=".os_text"
#elif defined (OS_STOP_SEC_CODE_FAST)
  #undef      OS_STOP_SEC_CODE_FAST
  #pragma ghs section text=default

/* OS Library Code */
#elif defined (OS_START_SEC_CODE)
  #undef      OS_START_SEC_CODE
  #pragma ghs section text=".os_text"
#elif defined (OS_STOP_SEC_CODE)
  #undef      OS_STOP_SEC_CODE
  #pragma ghs section text=default

/* OS Interrupt vectors */
#elif defined (OS_START_SEC_VECTORS)
  #undef      OS_START_SEC_VECTORS
  #pragma ghs section rodata=".os_vectors"
#elif defined (OS_STOP_SEC_VECTORS)
  #undef      OS_STOP_SEC_VECTORS
  #pragma ghs section rodata=default

/* OS Core 0 Code */
#elif defined (OS_START_SEC_CODE_CORE0_LOCAL)
  #undef      OS_START_SEC_CODE_CORE0_LOCAL
  #pragma ghs section text=".os_text"
#elif defined (OS_STOP_SEC_CODE_CORE0_LOCAL)
  #undef      OS_STOP_SEC_CODE_CORE0_LOCAL
  #pragma ghs section text=default

/* OS Core 1 Code */
#elif defined (OS_START_SEC_CODE_CORE1_LOCAL)
  #undef      OS_START_SEC_CODE_CORE1_LOCAL
  #pragma ghs section text=".os_text"
#elif defined (OS_STOP_SEC_CODE_CORE1_LOCAL)
  #undef      OS_STOP_SEC_CODE_CORE1_LOCAL
  #pragma ghs section text=default

/* MemoryMappingCodeLocations */
#elif defined (OS_START_SEC_CONST_CORE0_LOCAL)
  #undef      OS_START_SEC_CONST_CORE0_LOCAL
    #pragma ghs section rodata=".os_const"
#elif defined (OS_STOP_SEC_CONST_CORE0_LOCAL)
  #undef      OS_STOP_SEC_CONST_CORE0_LOCAL
    #pragma ghs section rodata=default

#elif defined (OS_START_SEC_CONST_CORE1_LOCAL)
  #undef      OS_START_SEC_CONST_CORE1_LOCAL
    #pragma ghs section rodata=".os_const"
#elif defined (OS_STOP_SEC_CONST_CORE1_LOCAL)
  #undef      OS_STOP_SEC_CONST_CORE1_LOCAL
    #pragma ghs section rodata=default

#elif defined (OS_START_SEC_CALLOUT_CODE)
  #undef      OS_START_SEC_CALLOUT_CODE
#elif defined (OS_STOP_SEC_CALLOUT_CODE)
  #undef      OS_STOP_SEC_CALLOUT_CODE

/* Callouts */
#elif defined (OS_START_SEC_CODE_LIB_CORE0_LOCAL)
  #undef      OS_START_SEC_CODE_LIB_CORE0_LOCAL
    #pragma ghs section text=".os_text_core0"
#elif defined (OS_STOP_SEC_CODE_LIB_CORE0_LOCAL)
  #undef      OS_STOP_SEC_CODE_LIB_CORE0_LOCAL
    #pragma ghs section text=default

#elif defined (OS_START_SEC_CONST_LIB_CORE0_LOCAL)
  #undef      OS_START_SEC_CONST_LIB_CORE0_LOCAL
    #pragma ghs section rodata=".os_const_core0"
#elif defined (OS_STOP_SEC_CONST_LIB_CORE0_LOCAL)
  #undef      OS_STOP_SEC_CONST_LIB_CORE0_LOCAL
    #pragma ghs section rodata=default

#elif defined (OS_START_SEC_CODE_LIB_CORE1_LOCAL)
  #undef      OS_START_SEC_CODE_LIB_CORE1_LOCAL
    #pragma ghs section text=".os_text_core1"
#elif defined (OS_STOP_SEC_CODE_LIB_CORE1_LOCAL)
  #undef      OS_STOP_SEC_CODE_LIB_CORE1_LOCAL
    #pragma ghs section text=default

#elif defined (OS_START_SEC_CONST_LIB_CORE1_LOCAL)
  #undef      OS_START_SEC_CONST_LIB_CORE1_LOCAL
    #pragma ghs section rodata=".os_const_core1"
#elif defined (OS_STOP_SEC_CONST_LIB_CORE1_LOCAL)
  #undef      OS_STOP_SEC_CONST_LIB_CORE1_LOCAL
    #pragma ghs section rodata=default

#elif defined (OS_START_SEC_VAR_SYSTEM_RAM)
  #undef      OS_START_SEC_VAR_SYSTEM_RAM
    #pragma ghs section bss=".os_shared_bss"
#elif defined (OS_STOP_SEC_VAR_SYSTEM_RAM)
  #undef      OS_STOP_SEC_VAR_SYSTEM_RAM
    #pragma ghs section bss=default

#else
  #error No section in Os_MemMap was matched
#endif

