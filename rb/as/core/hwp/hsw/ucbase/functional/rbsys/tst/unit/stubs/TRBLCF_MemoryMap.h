#ifndef TRBLCF_MEMORYMAP_H__
#define TRBLCF_MEMORYMAP_H__

extern uint32 TRBSYS_DummyReprogDriver_cnt;

extern void TRBSYS_DummyReprogDriver(void);
extern uint32 RBLCF_getStartAddress_DLM_RAM(void);

#define TRBSYS_BURAM_FSW_Length (15)
extern uint32 TRBSYS_BURAM_FSW[TRBSYS_BURAM_FSW_Length];
extern uint32 RBLCF_getStartAddress_BURAM_FSW(void);
extern uint32 RBLCF_getLength_BURAM_FSW(void);


#endif
