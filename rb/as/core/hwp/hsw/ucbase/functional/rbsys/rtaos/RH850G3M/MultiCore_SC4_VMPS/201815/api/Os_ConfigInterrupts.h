/*
 * This is Os_ConfigInterrupts.h, auto-generated for:
 *   Project: rtaos_ccas_mcore_sc4_vmps
 *   Target:  RH850GHS
 *   Variant: P1HC
 *   Version: 5.0.36
 */
/*
 * Include this header in order to allow any configured EI maskable interrupt
 * to be enabled or disabled
 */
#ifndef OS_CONFIGINTERRUPTS_H
#define OS_CONFIGINTERRUPTS_H

#define OS_SET1(addr, bit) __SET1(addr, bit)
#define OS_CLR1(addr, bit) __CLR1(addr, bit)

#define OS_ICR_INTERRUPT_CLEARED_MSK ((uint16)(0xEFFFU))
#define OS_ICR_EIMK 7U

/* These macros can be used to disable/enable and clear individual interrupts by
 * the EI maskable interrupt channel number or RTA-OS configuration name
 */
/* Macros must be protected against interruption. */
/* [$Satisfies $TargetCS_EHI 640569] [$Satisfies $TargetGHS_EHI 639880] [$Satisfies $TargetWR_EHI 640574] */
#define Os_IntChannel_Software_interrupt_0 (9U)
#define Os_IntChannel_ISRSWINT0 (9U)
#define Os_EIC9 ((*(volatile uint16 *) (0xFFFEEA12U)))
#define Os_Disable_EI_Channel_9() OS_SET1((volatile char *)&Os_EIC9, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_9() OS_CLR1((volatile char *)&Os_EIC9, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_9() OS_DI(); (Os_EIC9 &= OS_ICR_INTERRUPT_CLEARED_MSK); OS_EI();
#define Os_Disable_ISRSWINT0() Os_Disable_EI_Channel_9()
#define Os_Enable_ISRSWINT0() Os_Enable_EI_Channel_9()
#define Os_Clear_ISRSWINT0() Os_Clear_EI_Channel_9()

#define Os_IntChannel_STM0_interrupt_4 (14U)
#define Os_IntChannel_ISRSTM04 (14U)
#define Os_EIC14 ((*(volatile uint16 *) (0xFFFEEA1CU)))
#define Os_Disable_EI_Channel_14() OS_SET1((volatile char *)&Os_EIC14, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_14() OS_CLR1((volatile char *)&Os_EIC14, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_14() OS_DI(); (Os_EIC14 &= OS_ICR_INTERRUPT_CLEARED_MSK); OS_EI();
#define Os_Disable_ISRSTM04() Os_Disable_EI_Channel_14()
#define Os_Enable_ISRSTM04() Os_Enable_EI_Channel_14()
#define Os_Clear_ISRSTM04() Os_Clear_EI_Channel_14()

#define Os_IntChannel_STM0_interrupt_5 (15U)
#define Os_IntChannel_ISRSTM05 (15U)
#define Os_EIC15 ((*(volatile uint16 *) (0xFFFEEA1EU)))
#define Os_Disable_EI_Channel_15() OS_SET1((volatile char *)&Os_EIC15, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_15() OS_CLR1((volatile char *)&Os_EIC15, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_15() OS_DI(); (Os_EIC15 &= OS_ICR_INTERRUPT_CLEARED_MSK); OS_EI();
#define Os_Disable_ISRSTM05() Os_Disable_EI_Channel_15()
#define Os_Enable_ISRSTM05() Os_Enable_EI_Channel_15()
#define Os_Clear_ISRSTM05() Os_Clear_EI_Channel_15()

#define Os_IntChannel_STM0_interrupt_0 (41U)
#define Os_IntChannel_ISRSTM06_SC4core0 (41U)
#define Os_EIC41 ((*(volatile uint16 *) (0xFFFFB052U)))
#define Os_Disable_EI_Channel_41() OS_SET1((volatile char *)&Os_EIC41, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_41() OS_CLR1((volatile char *)&Os_EIC41, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_41() OS_DI(); (Os_EIC41 &= OS_ICR_INTERRUPT_CLEARED_MSK); OS_EI();
#define Os_Disable_ISRSTM06_SC4core0() Os_Disable_EI_Channel_41()
#define Os_Enable_ISRSTM06_SC4core0() Os_Enable_EI_Channel_41()
#define Os_Clear_ISRSTM06_SC4core0() Os_Clear_EI_Channel_41()

#define Os_IntChannel_STM0_interrupt_1 (42U)
#define Os_IntChannel_ISRSTM07_SC4core1 (42U)
#define Os_EIC42 ((*(volatile uint16 *) (0xFFFFB054U)))
#define Os_Disable_EI_Channel_42() OS_SET1((volatile char *)&Os_EIC42, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_42() OS_CLR1((volatile char *)&Os_EIC42, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_42() OS_DI(); (Os_EIC42 &= OS_ICR_INTERRUPT_CLEARED_MSK); OS_EI();
#define Os_Disable_ISRSTM07_SC4core1() Os_Disable_EI_Channel_42()
#define Os_Enable_ISRSTM07_SC4core1() Os_Enable_EI_Channel_42()
#define Os_Clear_ISRSTM07_SC4core1() Os_Clear_EI_Channel_42()

#define Os_IntChannel_RLIN3_0_status (102U)
#define Os_IntChannel_ISRRLIN30STATUS (102U)
#define Os_EIC102 ((*(volatile uint16 *) (0xFFFFB0CCU)))
#define Os_Disable_EI_Channel_102() OS_SET1((volatile char *)&Os_EIC102, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_102() OS_CLR1((volatile char *)&Os_EIC102, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_102() OS_DI(); (Os_EIC102 &= OS_ICR_INTERRUPT_CLEARED_MSK); OS_EI();
#define Os_Disable_ISRRLIN30STATUS() Os_Disable_EI_Channel_102()
#define Os_Enable_ISRRLIN30STATUS() Os_Enable_EI_Channel_102()
#define Os_Clear_ISRRLIN30STATUS() Os_Clear_EI_Channel_102()

#define Os_IntChannel_RLIN3_0_Rx (103U)
#define Os_IntChannel_ISRRLIN30RX (103U)
#define Os_EIC103 ((*(volatile uint16 *) (0xFFFFB0CEU)))
#define Os_Disable_EI_Channel_103() OS_SET1((volatile char *)&Os_EIC103, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_103() OS_CLR1((volatile char *)&Os_EIC103, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_103() OS_DI(); (Os_EIC103 &= OS_ICR_INTERRUPT_CLEARED_MSK); OS_EI();
#define Os_Disable_ISRRLIN30RX() Os_Disable_EI_Channel_103()
#define Os_Enable_ISRRLIN30RX() Os_Enable_EI_Channel_103()
#define Os_Clear_ISRRLIN30RX() Os_Clear_EI_Channel_103()

#define Os_IntChannel_RLIN3_1_status (105U)
#define Os_IntChannel_ISRRLIN31STATUS (105U)
#define Os_EIC105 ((*(volatile uint16 *) (0xFFFFB0D2U)))
#define Os_Disable_EI_Channel_105() OS_SET1((volatile char *)&Os_EIC105, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_105() OS_CLR1((volatile char *)&Os_EIC105, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_105() OS_DI(); (Os_EIC105 &= OS_ICR_INTERRUPT_CLEARED_MSK); OS_EI();
#define Os_Disable_ISRRLIN31STATUS() Os_Disable_EI_Channel_105()
#define Os_Enable_ISRRLIN31STATUS() Os_Enable_EI_Channel_105()
#define Os_Clear_ISRRLIN31STATUS() Os_Clear_EI_Channel_105()

#define Os_IntChannel_RLIN3_1_Rx (106U)
#define Os_IntChannel_ISRRLIN31RX (106U)
#define Os_EIC106 ((*(volatile uint16 *) (0xFFFFB0D4U)))
#define Os_Disable_EI_Channel_106() OS_SET1((volatile char *)&Os_EIC106, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_106() OS_CLR1((volatile char *)&Os_EIC106, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_106() OS_DI(); (Os_EIC106 &= OS_ICR_INTERRUPT_CLEARED_MSK); OS_EI();
#define Os_Disable_ISRRLIN31RX() Os_Disable_EI_Channel_106()
#define Os_Enable_ISRRLIN31RX() Os_Enable_EI_Channel_106()
#define Os_Clear_ISRRLIN31RX() Os_Clear_EI_Channel_106()

#define Os_IntChannel_MTTCAN0_interrupt_0 (172U)
#define Os_IntChannel_ISRMTTCANI0 (172U)
#define Os_EIC172 ((*(volatile uint16 *) (0xFFFFB158U)))
#define Os_Disable_EI_Channel_172() OS_SET1((volatile char *)&Os_EIC172, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_172() OS_CLR1((volatile char *)&Os_EIC172, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_172() OS_DI(); (Os_EIC172 &= OS_ICR_INTERRUPT_CLEARED_MSK); OS_EI();
#define Os_Disable_ISRMTTCANI0() Os_Disable_EI_Channel_172()
#define Os_Enable_ISRMTTCANI0() Os_Enable_EI_Channel_172()
#define Os_Clear_ISRMTTCANI0() Os_Clear_EI_Channel_172()

#define Os_IntChannel_MCAN0_interrupt_0 (175U)
#define Os_IntChannel_ISRMCAN0I0 (175U)
#define Os_EIC175 ((*(volatile uint16 *) (0xFFFFB15EU)))
#define Os_Disable_EI_Channel_175() OS_SET1((volatile char *)&Os_EIC175, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_175() OS_CLR1((volatile char *)&Os_EIC175, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_175() OS_DI(); (Os_EIC175 &= OS_ICR_INTERRUPT_CLEARED_MSK); OS_EI();
#define Os_Disable_ISRMCAN0I0() Os_Disable_EI_Channel_175()
#define Os_Enable_ISRMCAN0I0() Os_Enable_EI_Channel_175()
#define Os_Clear_ISRMCAN0I0() Os_Clear_EI_Channel_175()

#define Os_IntChannel_MCAN1_interrupt_0 (178U)
#define Os_IntChannel_ISRMCAN1I0 (178U)
#define Os_EIC178 ((*(volatile uint16 *) (0xFFFFB164U)))
#define Os_Disable_EI_Channel_178() OS_SET1((volatile char *)&Os_EIC178, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_178() OS_CLR1((volatile char *)&Os_EIC178, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_178() OS_DI(); (Os_EIC178 &= OS_ICR_INTERRUPT_CLEARED_MSK); OS_EI();
#define Os_Disable_ISRMCAN1I0() Os_Disable_EI_Channel_178()
#define Os_Enable_ISRMCAN1I0() Os_Enable_EI_Channel_178()
#define Os_Clear_ISRMCAN1I0() Os_Clear_EI_Channel_178()

#define Os_IntChannel_MCAN2_interrupt_0 (181U)
#define Os_IntChannel_ISRMCAN2I0 (181U)
#define Os_EIC181 ((*(volatile uint16 *) (0xFFFFB16AU)))
#define Os_Disable_EI_Channel_181() OS_SET1((volatile char *)&Os_EIC181, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_181() OS_CLR1((volatile char *)&Os_EIC181, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_181() OS_DI(); (Os_EIC181 &= OS_ICR_INTERRUPT_CLEARED_MSK); OS_EI();
#define Os_Disable_ISRMCAN2I0() Os_Disable_EI_Channel_181()
#define Os_Enable_ISRMCAN2I0() Os_Enable_EI_Channel_181()
#define Os_Clear_ISRMCAN2I0() Os_Clear_EI_Channel_181()

#define Os_IntChannel_FLXA0_universal_ch_A (186U)
#define Os_IntChannel_ISRFLX0LINE0 (186U)
#define Os_EIC186 ((*(volatile uint16 *) (0xFFFFB174U)))
#define Os_Disable_EI_Channel_186() OS_SET1((volatile char *)&Os_EIC186, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_186() OS_CLR1((volatile char *)&Os_EIC186, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_186() OS_DI(); (Os_EIC186 &= OS_ICR_INTERRUPT_CLEARED_MSK); OS_EI();
#define Os_Disable_ISRFLX0LINE0() Os_Disable_EI_Channel_186()
#define Os_Enable_ISRFLX0LINE0() Os_Enable_EI_Channel_186()
#define Os_Clear_ISRFLX0LINE0() Os_Clear_EI_Channel_186()

#define Os_IntChannel_FLXA1_universal_ch_A (197U)
#define Os_IntChannel_ISRFLX1LINE0 (197U)
#define Os_EIC197 ((*(volatile uint16 *) (0xFFFFB18AU)))
#define Os_Disable_EI_Channel_197() OS_SET1((volatile char *)&Os_EIC197, OS_ICR_EIMK)
#define Os_Enable_EI_Channel_197() OS_CLR1((volatile char *)&Os_EIC197, OS_ICR_EIMK)
#define Os_Clear_EI_Channel_197() OS_DI(); (Os_EIC197 &= OS_ICR_INTERRUPT_CLEARED_MSK); OS_EI();
#define Os_Disable_ISRFLX1LINE0() Os_Disable_EI_Channel_197()
#define Os_Enable_ISRFLX1LINE0() Os_Enable_EI_Channel_197()
#define Os_Clear_ISRFLX1LINE0() Os_Clear_EI_Channel_197()

/* These macros can be used to disable and enable in one call, all of the
 * configured EI maskable interrupts that are defined as Os_Disable_x and
 * Os_Enable_x above
 */
#define Os_DisableAllConfiguredInterrupts() { \
  Os_Disable_ISRSWINT0(); \
  Os_Disable_ISRSTM04(); \
  Os_Disable_ISRSTM05(); \
  Os_Disable_ISRSTM06_SC4core0(); \
  Os_Disable_ISRSTM07_SC4core1(); \
  Os_Disable_ISRRLIN30STATUS(); \
  Os_Disable_ISRRLIN30RX(); \
  Os_Disable_ISRRLIN31STATUS(); \
  Os_Disable_ISRRLIN31RX(); \
  Os_Disable_ISRMTTCANI0(); \
  Os_Disable_ISRMCAN0I0(); \
  Os_Disable_ISRMCAN1I0(); \
  Os_Disable_ISRMCAN2I0(); \
  Os_Disable_ISRFLX0LINE0(); \
  Os_Disable_ISRFLX1LINE0(); }

#define Os_EnableAllConfiguredInterrupts() { \
  Os_Enable_ISRSWINT0(); \
  Os_Enable_ISRSTM04(); \
  Os_Enable_ISRSTM05(); \
  Os_Enable_ISRSTM06_SC4core0(); \
  Os_Enable_ISRSTM07_SC4core1(); \
  Os_Enable_ISRRLIN30STATUS(); \
  Os_Enable_ISRRLIN30RX(); \
  Os_Enable_ISRRLIN31STATUS(); \
  Os_Enable_ISRRLIN31RX(); \
  Os_Enable_ISRMTTCANI0(); \
  Os_Enable_ISRMCAN0I0(); \
  Os_Enable_ISRMCAN1I0(); \
  Os_Enable_ISRMCAN2I0(); \
  Os_Enable_ISRFLX0LINE0(); \
  Os_Enable_ISRFLX1LINE0(); }

#endif /* OS_CONFIGINTERRUPTS_H */
