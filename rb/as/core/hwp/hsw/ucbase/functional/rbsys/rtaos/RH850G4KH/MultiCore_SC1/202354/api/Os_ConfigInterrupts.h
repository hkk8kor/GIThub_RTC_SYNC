/*
 * This is Os_ConfigInterrupts.h, auto-generated for:
 *   Project: rtaos_ccas_u2c_mcore_sc1
 *   Target:  RH850x2GHS
 *   Variant: U2C4
 *   Version: 5.0.11
 */
/*
 * Include this header in order to allow any configured EI maskable interrupt
 * to be enabled or disabled
 */
#ifndef OS_CONFIGINTERRUPTS_H
#define OS_CONFIGINTERRUPTS_H

/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, Os_Disable_EI_Channel_*, Os_Enable_EI_Channel_*, Os_Clear_EI_Channel_*, Os_Disable_*, Os_Enable_*, Os_Clear_*, Os_DisableAllConfiguredInterrupts_Core*, Os_EnableAllConfiguredInterrupts_Core*) */
/* Os_Disable_EI_Channel_*, Os_Enable_EI_Channel_*, Os_Clear_EI_Channel_*,
Os_Disable_*, Os_Enable_*, Os_Clear_*, Os_DisableAllConfiguredInterrupts_Core*,
Os_EnableAllConfiguredInterrupts_Core* */

/* These macros can be used to disable/enable and clear individual interrupts
 * by either the EI maskable interrupt channel number or RTA-OS configuration
 * name.
 */

#define Os_IntChannel_INTTPTMU00 (64U)
#define Os_IntChannel_ISRSTM04 (64U)
#define Os_Clear_EI_Channel_64() {OS_DI(); OS_INTC_EIC64 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_64() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC64, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_64() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC64, OS_ICR_EIMK)
#define Os_Clear_ISRSTM04() Os_Clear_EI_Channel_64()
#define Os_Disable_ISRSTM04() Os_Disable_EI_Channel_64()
#define Os_Enable_ISRSTM04() Os_Enable_EI_Channel_64()

#define Os_IntChannel_INTTPTMU01 (65U)
#define Os_IntChannel_ISRSTM05 (65U)
#define Os_Clear_EI_Channel_65() {OS_DI(); OS_INTC_EIC65 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_65() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC65, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_65() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC65, OS_ICR_EIMK)
#define Os_Clear_ISRSTM05() Os_Clear_EI_Channel_65()
#define Os_Disable_ISRSTM05() Os_Disable_EI_Channel_65()
#define Os_Enable_ISRSTM05() Os_Enable_EI_Channel_65()

#define Os_IntChannel_INTRCAN015REC0 (107U)
#define Os_IntChannel_ISRCAN0REC (107U)
#define Os_Clear_EI_Channel_107() {OS_DI(); OS_INTC_EIC107 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_107() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC107, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_107() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC107, OS_ICR_EIMK)
#define Os_Clear_ISRCAN0REC() Os_Clear_EI_Channel_107()
#define Os_Disable_ISRCAN0REC() Os_Disable_EI_Channel_107()
#define Os_Enable_ISRCAN0REC() Os_Enable_EI_Channel_107()

#define Os_IntChannel_INTRCAN015TRX0 (108U)
#define Os_IntChannel_ISRCAN0TRX (108U)
#define Os_Clear_EI_Channel_108() {OS_DI(); OS_INTC_EIC108 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_108() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC108, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_108() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC108, OS_ICR_EIMK)
#define Os_Clear_ISRCAN0TRX() Os_Clear_EI_Channel_108()
#define Os_Disable_ISRCAN0TRX() Os_Disable_EI_Channel_108()
#define Os_Enable_ISRCAN0TRX() Os_Enable_EI_Channel_108()

#define Os_IntChannel_INTRCAN015REC1 (113U)
#define Os_IntChannel_ISRCAN1REC (113U)
#define Os_Clear_EI_Channel_113() {OS_DI(); OS_INTC_EIC113 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_113() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC113, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_113() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC113, OS_ICR_EIMK)
#define Os_Clear_ISRCAN1REC() Os_Clear_EI_Channel_113()
#define Os_Disable_ISRCAN1REC() Os_Disable_EI_Channel_113()
#define Os_Enable_ISRCAN1REC() Os_Enable_EI_Channel_113()

#define Os_IntChannel_INTRCAN015TRX1 (114U)
#define Os_IntChannel_ISRCAN1TRX (114U)
#define Os_Clear_EI_Channel_114() {OS_DI(); OS_INTC_EIC114 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_114() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC114, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_114() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC114, OS_ICR_EIMK)
#define Os_Clear_ISRCAN1TRX() Os_Clear_EI_Channel_114()
#define Os_Disable_ISRCAN1TRX() Os_Disable_EI_Channel_114()
#define Os_Enable_ISRCAN1TRX() Os_Enable_EI_Channel_114()

#define Os_IntChannel_INTRCAN015REC2 (119U)
#define Os_IntChannel_ISRCAN2REC (119U)
#define Os_Clear_EI_Channel_119() {OS_DI(); OS_INTC_EIC119 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_119() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC119, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_119() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC119, OS_ICR_EIMK)
#define Os_Clear_ISRCAN2REC() Os_Clear_EI_Channel_119()
#define Os_Disable_ISRCAN2REC() Os_Disable_EI_Channel_119()
#define Os_Enable_ISRCAN2REC() Os_Enable_EI_Channel_119()

#define Os_IntChannel_INTRCAN015TRX2 (120U)
#define Os_IntChannel_ISRCAN2TRX (120U)
#define Os_Clear_EI_Channel_120() {OS_DI(); OS_INTC_EIC120 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_120() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC120, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_120() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC120, OS_ICR_EIMK)
#define Os_Clear_ISRCAN2TRX() Os_Clear_EI_Channel_120()
#define Os_Disable_ISRCAN2TRX() Os_Disable_EI_Channel_120()
#define Os_Enable_ISRCAN2TRX() Os_Enable_EI_Channel_120()

#define Os_IntChannel_INTRCAN015REC3 (125U)
#define Os_IntChannel_ISRCAN3REC (125U)
#define Os_Clear_EI_Channel_125() {OS_DI(); OS_INTC_EIC125 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_125() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC125, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_125() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC125, OS_ICR_EIMK)
#define Os_Clear_ISRCAN3REC() Os_Clear_EI_Channel_125()
#define Os_Disable_ISRCAN3REC() Os_Disable_EI_Channel_125()
#define Os_Enable_ISRCAN3REC() Os_Enable_EI_Channel_125()

#define Os_IntChannel_INTRCAN015TRX3 (126U)
#define Os_IntChannel_ISRCAN3TRX (126U)
#define Os_Clear_EI_Channel_126() {OS_DI(); OS_INTC_EIC126 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_126() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC126, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_126() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC126, OS_ICR_EIMK)
#define Os_Clear_ISRCAN3TRX() Os_Clear_EI_Channel_126()
#define Os_Disable_ISRCAN3TRX() Os_Disable_EI_Channel_126()
#define Os_Enable_ISRCAN3TRX() Os_Enable_EI_Channel_126()

#define Os_IntChannel_INTFLXA0LINE0 (509U)
#define Os_IntChannel_ISRFLX0LINE0 (509U)
#define Os_Clear_EI_Channel_509() {OS_DI(); OS_INTC_EIC509 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_509() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC509, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_509() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC509, OS_ICR_EIMK)
#define Os_Clear_ISRFLX0LINE0() Os_Clear_EI_Channel_509()
#define Os_Disable_ISRFLX0LINE0() Os_Disable_EI_Channel_509()
#define Os_Enable_ISRFLX0LINE0() Os_Enable_EI_Channel_509()

#define Os_IntChannel_CPU0_INTEINTSW0 (14U)
#define Os_IntChannel_ISRSWINT0 (14U)
#define Os_Clear_EI_Channel_14() {OS_DI(); OS_INTC_EIC14 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_14() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC14, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_14() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC14, OS_ICR_EIMK)
#define Os_Clear_ISRSWINT0() Os_Clear_EI_Channel_14()
#define Os_Disable_ISRSWINT0() Os_Disable_EI_Channel_14()
#define Os_Enable_ISRSWINT0() Os_Enable_EI_Channel_14()
/* These macros can be used to disable and enable in one call, all of the
 * configured EI maskable interrupts that are defined as Os_Disable_x and
 * Os_Enable_x above
 */
#define Os_DisableAllConfiguredInterrupts_Core0() \
  Os_Disable_ISRSTM05(); \
  Os_Disable_ISRCAN0REC(); \
  Os_Disable_ISRCAN0TRX(); \
  Os_Disable_ISRCAN1REC(); \
  Os_Disable_ISRCAN1TRX(); \
  Os_Disable_ISRCAN2REC(); \
  Os_Disable_ISRCAN2TRX(); \
  Os_Disable_ISRCAN3REC(); \
  Os_Disable_ISRCAN3TRX(); \
  Os_Disable_ISRFLX0LINE0();

#define Os_DisableAllConfiguredInterrupts_Core1() \
  Os_Disable_ISRSTM04(); \
  Os_Disable_ISRSWINT0();

#define Os_EnableAllConfiguredInterrupts_Core0() \
  Os_Enable_ISRSTM05(); \
  Os_Enable_ISRCAN0REC(); \
  Os_Enable_ISRCAN0TRX(); \
  Os_Enable_ISRCAN1REC(); \
  Os_Enable_ISRCAN1TRX(); \
  Os_Enable_ISRCAN2REC(); \
  Os_Enable_ISRCAN2TRX(); \
  Os_Enable_ISRCAN3REC(); \
  Os_Enable_ISRCAN3TRX(); \
  Os_Enable_ISRFLX0LINE0();

#define Os_EnableAllConfiguredInterrupts_Core1() \
  Os_Enable_ISRSTM04(); \
  Os_Enable_ISRSWINT0();

#endif /* OS_CONFIGINTERRUPTS_H */
