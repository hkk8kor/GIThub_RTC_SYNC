/*
 * This is Os_ConfigInterrupts.h, auto-generated for:
 *   Project: rtaos_ccas_stellar_mcore_sc1
 *   Target:  Stellar-R52-GHS
 *   Variant: SR6P6
 *   Version: 5.0.4
 */


#ifndef OS_CONFIGINTERRUPTS_H
#define OS_CONFIGINTERRUPTS_H
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, Os_Enable_*, Os_Disable_*, Os_Clear_*, Os_DisableAllConfiguredInterrupts_Core*, Os_EnableAllConfiguredInterrupts_Core*, Os_Set_Edge_Triggered_*, Os_Set_Level_Sensitive_*, Os_IsPending_*, Os_IsEnabled_*, Os_Trigger_*) */
/* Os_Enable_*, Os_Disable_*, Os_Clear_*, Os_IsPending_*, Os_IsEnabled_*, Os_Trigger_*, Os_DisableAllConfiguredInterrupts_Core*, Os_EnableAllConfiguredInterrupts_Core*, Os_Set_Edge_Triggered_*, Os_Set_Level_Sensitive_* */


#define Os_IntChannel_ISRCommonTimer (317)
#define Os_Disable_ISRCommonTimer() (OS_R52_GICD_ICENABLER[9] = 0x20000000U)
#define Os_Enable_ISRCommonTimer() (OS_R52_GICD_ISENABLER[9] = 0x20000000U)
#define Os_Clear_ISRCommonTimer() (OS_R52_GICD_ICPENDR[9] = 0x20000000U)
#define Os_IsPending_ISRCommonTimer() (OS_R52_GICD_ISPENDR[9] & 0x20000000U)
#define Os_IsEnabled_ISRCommonTimer() (OS_R52_GICD_ISENABLER[9] & 0x20000000U)
#define Os_Trigger_ISRCommonTimer() (OS_R52_GICD_ISPENDR[9] = 0x20000000U)
#define Os_Set_Edge_Triggered_ISRCommonTimer() (OS_R52_GICD_ICFGR[19] |= 0x8000000U)
#define Os_Set_Level_Sensitive_ISRCommonTimer() (OS_R52_GICD_ICFGR[19] &= 0xF3FFFFFFU)
#define Os_IntChannel_ISRGenericTimerCore0 (30)
#define Os_Disable_ISRGenericTimerCore0() (OS_R52_GICR0_ICENABLER[0] = 0x40000000U)
#define Os_Enable_ISRGenericTimerCore0() (OS_R52_GICR0_ISENABLER[0] = 0x40000000U)
#define Os_Clear_ISRGenericTimerCore0() (OS_R52_GICR0_ICPENDR[0] = 0x40000000U)
#define Os_IsPending_ISRGenericTimerCore0() (OS_R52_GICR0_ISPENDR[0] & 0x40000000U)
#define Os_IsEnabled_ISRGenericTimerCore0() (OS_R52_GICR0_ISENABLER[0] & 0x40000000U)
#define Os_Trigger_ISRGenericTimerCore0() (OS_R52_GICR0_ISPENDR[0] = 0x40000000U)
#define Os_Set_Edge_Triggered_ISRGenericTimerCore0() (OS_R52_GICR0_ICFGR[1] |= 0x20000000U)
#define Os_Set_Level_Sensitive_ISRGenericTimerCore0() (OS_R52_GICR0_ICFGR[1] &= 0xCFFFFFFFU)
#define Os_IntChannel_ISRGenericTimerCore1 (30)
#define Os_Disable_ISRGenericTimerCore1() (OS_R52_GICR1_ICENABLER[0] = 0x40000000U)
#define Os_Enable_ISRGenericTimerCore1() (OS_R52_GICR1_ISENABLER[0] = 0x40000000U)
#define Os_Clear_ISRGenericTimerCore1() (OS_R52_GICR1_ICPENDR[0] = 0x40000000U)
#define Os_IsPending_ISRGenericTimerCore1() (OS_R52_GICR1_ISPENDR[0] & 0x40000000U)
#define Os_IsEnabled_ISRGenericTimerCore1() (OS_R52_GICR1_ISENABLER[0] & 0x40000000U)
#define Os_Trigger_ISRGenericTimerCore1() (OS_R52_GICR1_ISPENDR[0] = 0x40000000U)
#define Os_Set_Edge_Triggered_ISRGenericTimerCore1() (OS_R52_GICR1_ICFGR[1] |= 0x20000000U)
#define Os_Set_Level_Sensitive_ISRGenericTimerCore1() (OS_R52_GICR1_ICFGR[1] &= 0xCFFFFFFFU)

/* [MISRA 2012 Rule 5.4] */ /*lint -estring(621, Os_DisableAllConfiguredInterrupts_Core0) */
/* Os_DisableAllConfiguredInterrupts_Core0 */
/* [MISRA 2012 Rule 5.4] */ /*lint -estring(621, Os_EnableAllConfiguredInterrupts_Core0) */
/* Os_EnableAllConfiguredInterrupts_Core0 */
/* [MISRA 2012 Rule 12.3] */ /*lint -save  -e9008 -e9050 -e9084 */
#define Os_DisableAllConfiguredInterrupts_Core0() ( (OS_R52_GICR0_ICENABLER[0] = 0x40000000U) )
/*lint -restore */
/* [MISRA 2012 Rule 12.3] */ /*lint -save  -e9008 -e9050 -e9084 */
#define Os_EnableAllConfiguredInterrupts_Core0() ( (OS_R52_GICR0_ISENABLER[0] = 0x40000000U) )
/*lint -restore */
/* [MISRA 2012 Rule 5.4] */ /*lint -estring(621, Os_DisableAllConfiguredInterrupts_Core1) */
/* Os_DisableAllConfiguredInterrupts_Core1 */
/* [MISRA 2012 Rule 5.4] */ /*lint -estring(621, Os_EnableAllConfiguredInterrupts_Core1) */
/* Os_EnableAllConfiguredInterrupts_Core1 */
/* [MISRA 2012 Rule 12.3] */ /*lint -save  -e9008 -e9050 -e9084 */
#define Os_DisableAllConfiguredInterrupts_Core1() ( (OS_R52_GICD_ICENABLER[9] = 0x20000000U), (OS_R52_GICR1_ICENABLER[0] = 0x40000000U) )
/*lint -restore */
/* [MISRA 2012 Rule 12.3] */ /*lint -save  -e9008 -e9050 -e9084 */
#define Os_EnableAllConfiguredInterrupts_Core1() ( (OS_R52_GICD_ISENABLER[9] = 0x20000000U), (OS_R52_GICR1_ISENABLER[0] = 0x40000000U) )
/*lint -restore */


#endif

