#ifndef TRBSYS_GHS_H__
#define TRBSYS_GHS_H__


extern uint32 TRBSYS_start_cnt;
extern void _start(void);

extern uint32 TRBSYS_main_cnt;
extern void _main(void); //< provided by GHS if configured for CPP

#endif
