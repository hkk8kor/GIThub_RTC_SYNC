
extern FUNC(void, OS_CODE_CORE0_LOCAL) Os_Cat1Wrapper0(void);
extern FUNC(void, OS_CODE_CORE0_LOCAL) Os_ISRWrapper0(uint32 intid, Os_imaskType previous_imask);

extern FUNC(void, OS_CODE_CORE1_LOCAL) Os_Cat1Wrapper1(void);
extern FUNC(void, OS_CODE_CORE1_LOCAL) Os_ISRWrapper1(uint32 intid, Os_imaskType previous_imask);


extern void b_EXCUndefinedInstruction1(void); /*lint -esym(752, b_EXCUndefinedInstruction1) allow to be unreferenced */
extern void b_EXCUndefinedInstruction0(void); /*lint -esym(752, b_EXCUndefinedInstruction0) allow to be unreferenced */
extern void b_EXCPrefetchAbort1(void); /*lint -esym(752, b_EXCPrefetchAbort1) allow to be unreferenced */
extern void b_EXCPrefetchAbort0(void); /*lint -esym(752, b_EXCPrefetchAbort0) allow to be unreferenced */
extern void b_EXCDataAbort1(void); /*lint -esym(752, b_EXCDataAbort1) allow to be unreferenced */
extern void b_EXCDataAbort0(void); /*lint -esym(752, b_EXCDataAbort0) allow to be unreferenced */
extern void ISRGenericTimerCore1(void); /*lint -esym(752, ISRGenericTimerCore1) allow to be unreferenced */
extern void ISRGenericTimerCore0(void); /*lint -esym(752, ISRGenericTimerCore0) allow to be unreferenced */
extern void InvalidInt(void);


extern FUNC(void, OS_CODE_CORE0_LOCAL) Os_CrossCoreISR0(uint32 intid, Os_imaskType previous_imask);



extern FUNC(void, OS_CODE_CORE1_LOCAL) Os_CrossCoreISR1(uint32 intid, Os_imaskType previous_imask);




