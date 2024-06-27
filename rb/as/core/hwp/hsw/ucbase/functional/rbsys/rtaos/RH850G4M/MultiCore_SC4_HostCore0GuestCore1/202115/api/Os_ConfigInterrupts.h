/*
 * This is Os_ConfigInterrupts.h, auto-generated for:
 *   Project: rtaos_ccas_u2a_mcore_sc4
 *   Target:  RH850x2GHS
 *   Variant: U2A
 *   Version: 5.0.6
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

#define Os_IntChannel_INTTPTMU00 (209U)
#define Os_IntChannel_ISRSTM04 (209U)
#define Os_Clear_EI_Channel_209() {OS_DI(); OS_INTC_EIC209 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_209() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC209, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_209() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC209, OS_ICR_EIMK)
#define Os_Clear_ISRSTM04() Os_Clear_EI_Channel_209()
#define Os_Disable_ISRSTM04() Os_Disable_EI_Channel_209()
#define Os_Enable_ISRSTM04() Os_Enable_EI_Channel_209()

#define Os_IntChannel_INTTPTMU01 (210U)
#define Os_IntChannel_ISRSTM05 (210U)
#define Os_Clear_EI_Channel_210() {OS_DI(); OS_INTC_EIC210 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_210() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC210, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_210() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC210, OS_ICR_EIMK)
#define Os_Clear_ISRSTM05() Os_Clear_EI_Channel_210()
#define Os_Disable_ISRSTM05() Os_Disable_EI_Channel_210()
#define Os_Enable_ISRSTM05() Os_Enable_EI_Channel_210()

#define Os_IntChannel_INTTPTMU02 (211U)
#define Os_IntChannel_ISRSTM06_SC4core0 (211U)
#define Os_Clear_EI_Channel_211() {OS_DI(); OS_INTC_EIC211 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_211() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC211, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_211() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC211, OS_ICR_EIMK)
#define Os_Clear_ISRSTM06_SC4core0() Os_Clear_EI_Channel_211()
#define Os_Disable_ISRSTM06_SC4core0() Os_Disable_EI_Channel_211()
#define Os_Enable_ISRSTM06_SC4core0() Os_Enable_EI_Channel_211()

#define Os_IntChannel_INTTPTMU03 (212U)
#define Os_IntChannel_ISRSTM07_SC4core1 (212U)
#define Os_Clear_EI_Channel_212() {OS_DI(); OS_INTC_EIC212 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_212() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC212, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_212() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC212, OS_ICR_EIMK)
#define Os_Clear_ISRSTM07_SC4core1() Os_Clear_EI_Channel_212()
#define Os_Disable_ISRSTM07_SC4core1() Os_Disable_EI_Channel_212()
#define Os_Enable_ISRSTM07_SC4core1() Os_Enable_EI_Channel_212()

#define Os_IntChannel_INTRCAN0REC (299U)
#define Os_IntChannel_ISRCAN0REC (299U)
#define Os_Clear_EI_Channel_299() {OS_DI(); OS_INTC_EIC299 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_299() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC299, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_299() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC299, OS_ICR_EIMK)
#define Os_Clear_ISRCAN0REC() Os_Clear_EI_Channel_299()
#define Os_Disable_ISRCAN0REC() Os_Disable_EI_Channel_299()
#define Os_Enable_ISRCAN0REC() Os_Enable_EI_Channel_299()

#define Os_IntChannel_INTRCAN0TRX (300U)
#define Os_IntChannel_ISRCAN0TRX (300U)
#define Os_Clear_EI_Channel_300() {OS_DI(); OS_INTC_EIC300 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_300() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC300, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_300() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC300, OS_ICR_EIMK)
#define Os_Clear_ISRCAN0TRX() Os_Clear_EI_Channel_300()
#define Os_Disable_ISRCAN0TRX() Os_Disable_EI_Channel_300()
#define Os_Enable_ISRCAN0TRX() Os_Enable_EI_Channel_300()

#define Os_IntChannel_INTRCAN1REC (302U)
#define Os_IntChannel_ISRCAN1REC (302U)
#define Os_Clear_EI_Channel_302() {OS_DI(); OS_INTC_EIC302 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_302() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC302, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_302() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC302, OS_ICR_EIMK)
#define Os_Clear_ISRCAN1REC() Os_Clear_EI_Channel_302()
#define Os_Disable_ISRCAN1REC() Os_Disable_EI_Channel_302()
#define Os_Enable_ISRCAN1REC() Os_Enable_EI_Channel_302()

#define Os_IntChannel_INTRCAN1TRX (303U)
#define Os_IntChannel_ISRCAN1TRX (303U)
#define Os_Clear_EI_Channel_303() {OS_DI(); OS_INTC_EIC303 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_303() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC303, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_303() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC303, OS_ICR_EIMK)
#define Os_Clear_ISRCAN1TRX() Os_Clear_EI_Channel_303()
#define Os_Disable_ISRCAN1TRX() Os_Disable_EI_Channel_303()
#define Os_Enable_ISRCAN1TRX() Os_Enable_EI_Channel_303()

#define Os_IntChannel_INTRCAN2REC (305U)
#define Os_IntChannel_ISRCAN2REC (305U)
#define Os_Clear_EI_Channel_305() {OS_DI(); OS_INTC_EIC305 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_305() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC305, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_305() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC305, OS_ICR_EIMK)
#define Os_Clear_ISRCAN2REC() Os_Clear_EI_Channel_305()
#define Os_Disable_ISRCAN2REC() Os_Disable_EI_Channel_305()
#define Os_Enable_ISRCAN2REC() Os_Enable_EI_Channel_305()

#define Os_IntChannel_INTRCAN2TRX (306U)
#define Os_IntChannel_ISRCAN2TRX (306U)
#define Os_Clear_EI_Channel_306() {OS_DI(); OS_INTC_EIC306 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_306() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC306, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_306() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC306, OS_ICR_EIMK)
#define Os_Clear_ISRCAN2TRX() Os_Clear_EI_Channel_306()
#define Os_Disable_ISRCAN2TRX() Os_Disable_EI_Channel_306()
#define Os_Enable_ISRCAN2TRX() Os_Enable_EI_Channel_306()

#define Os_IntChannel_INTRCAN6REC (317U)
#define Os_IntChannel_ISRCAN6REC (317U)
#define Os_Clear_EI_Channel_317() {OS_DI(); OS_INTC_EIC317 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_317() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC317, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_317() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC317, OS_ICR_EIMK)
#define Os_Clear_ISRCAN6REC() Os_Clear_EI_Channel_317()
#define Os_Disable_ISRCAN6REC() Os_Disable_EI_Channel_317()
#define Os_Enable_ISRCAN6REC() Os_Enable_EI_Channel_317()

#define Os_IntChannel_INTRCAN6TRX (318U)
#define Os_IntChannel_ISRCAN6TRX (318U)
#define Os_Clear_EI_Channel_318() {OS_DI(); OS_INTC_EIC318 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_318() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC318, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_318() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC318, OS_ICR_EIMK)
#define Os_Clear_ISRCAN6TRX() Os_Clear_EI_Channel_318()
#define Os_Disable_ISRCAN6TRX() Os_Disable_EI_Channel_318()
#define Os_Enable_ISRCAN6TRX() Os_Enable_EI_Channel_318()

#define Os_IntChannel_INTRCAN8REC (325U)
#define Os_IntChannel_ISRCAN8REC (325U)
#define Os_Clear_EI_Channel_325() {OS_DI(); OS_INTC_EIC325 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_325() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC325, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_325() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC325, OS_ICR_EIMK)
#define Os_Clear_ISRCAN8REC() Os_Clear_EI_Channel_325()
#define Os_Disable_ISRCAN8REC() Os_Disable_EI_Channel_325()
#define Os_Enable_ISRCAN8REC() Os_Enable_EI_Channel_325()

#define Os_IntChannel_INTRCAN8TRX (326U)
#define Os_IntChannel_ISRCAN8TRX (326U)
#define Os_Clear_EI_Channel_326() {OS_DI(); OS_INTC_EIC326 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_326() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC326, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_326() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC326, OS_ICR_EIMK)
#define Os_Clear_ISRCAN8TRX() Os_Clear_EI_Channel_326()
#define Os_Disable_ISRCAN8TRX() Os_Disable_EI_Channel_326()
#define Os_Enable_ISRCAN8TRX() Os_Enable_EI_Channel_326()

#define Os_IntChannel_INTFLXA0LINE0 (623U)
#define Os_IntChannel_ISRFLX0LINE0 (623U)
#define Os_Clear_EI_Channel_623() {OS_DI(); OS_INTC_EIC623 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_623() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC623, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_623() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC623, OS_ICR_EIMK)
#define Os_Clear_ISRFLX0LINE0() Os_Clear_EI_Channel_623()
#define Os_Disable_ISRFLX0LINE0() Os_Disable_EI_Channel_623()
#define Os_Enable_ISRFLX0LINE0() Os_Enable_EI_Channel_623()

#define Os_IntChannel_INTFLXA1LINE0 (634U)
#define Os_IntChannel_ISRFLX1LINE0 (634U)
#define Os_Clear_EI_Channel_634() {OS_DI(); OS_INTC_EIC634 &= (uint16)OS_ICR_EIRF_MASK; OS_EI();}
#define Os_Disable_EI_Channel_634() OS_SET1((OS_VOLATILE char *)&OS_INTC_EIC634, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_634() OS_CLR1((OS_VOLATILE char *)&OS_INTC_EIC634, OS_ICR_EIMK)
#define Os_Clear_ISRFLX1LINE0() Os_Clear_EI_Channel_634()
#define Os_Disable_ISRFLX1LINE0() Os_Disable_EI_Channel_634()
#define Os_Enable_ISRFLX1LINE0() Os_Enable_EI_Channel_634()

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
  Os_Disable_ISRSTM04(); \
  Os_Disable_ISRSTM05(); \
  Os_Disable_ISRSTM06_SC4core0(); \
  Os_Disable_ISRCAN0REC(); \
  Os_Disable_ISRCAN0TRX(); \
  Os_Disable_ISRCAN1REC(); \
  Os_Disable_ISRCAN1TRX(); \
  Os_Disable_ISRCAN2REC(); \
  Os_Disable_ISRCAN2TRX(); \
  Os_Disable_ISRCAN6REC(); \
  Os_Disable_ISRCAN6TRX(); \
  Os_Disable_ISRCAN8REC(); \
  Os_Disable_ISRCAN8TRX(); \
  Os_Disable_ISRFLX0LINE0(); \
  Os_Disable_ISRFLX1LINE0();

#define Os_DisableAllConfiguredInterrupts_Core1() \
  Os_Disable_ISRSTM07_SC4core1(); \
  Os_Disable_ISRSWINT0();

#define Os_EnableAllConfiguredInterrupts_Core0() \
  Os_Enable_ISRSTM04(); \
  Os_Enable_ISRSTM05(); \
  Os_Enable_ISRSTM06_SC4core0(); \
  Os_Enable_ISRCAN0REC(); \
  Os_Enable_ISRCAN0TRX(); \
  Os_Enable_ISRCAN1REC(); \
  Os_Enable_ISRCAN1TRX(); \
  Os_Enable_ISRCAN2REC(); \
  Os_Enable_ISRCAN2TRX(); \
  Os_Enable_ISRCAN6REC(); \
  Os_Enable_ISRCAN6TRX(); \
  Os_Enable_ISRCAN8REC(); \
  Os_Enable_ISRCAN8TRX(); \
  Os_Enable_ISRFLX0LINE0(); \
  Os_Enable_ISRFLX1LINE0();

#define Os_EnableAllConfiguredInterrupts_Core1() \
  Os_Enable_ISRSTM07_SC4core1(); \
  Os_Enable_ISRSWINT0();

#endif /* OS_CONFIGINTERRUPTS_H */
