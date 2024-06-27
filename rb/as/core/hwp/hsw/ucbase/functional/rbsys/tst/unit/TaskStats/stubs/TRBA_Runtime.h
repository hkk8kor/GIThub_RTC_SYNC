#ifndef TRBA_RUNTIME_H__
#define TRBA_RUNTIME_H__


typedef struct {
  /* Runtime */
  uint32 tiCurRT_u32;
  uint32 tiMinRT_u32;
  uint32 tiMaxRT_u32;
}rba_Runtime_MonTask_t;

typedef struct {
  /* Runtime */
  uint32 tiCurRT_u32;
  uint32 tiMinRT_u32;
  uint32 tiMaxRT_u32;
}rba_Runtime_MonISR_t;

extern rba_Runtime_MonTask_t rba_Runtime_MonTask_ast[OS_NUM_TASKS];
extern rba_Runtime_MonISR_t  rba_Runtime_MonIsr_ast[OS_NUM_ISRS];

#define RBA_RUNTIME_TASKNOTUSED (0xFFFFFFFFu)
#define RBA_RUNTIME_ISRNOTUSED  (0xFFFFFFFFu)

extern boolean rba_Runtime_GetTaskIdx_ReturnValid;
extern boolean rba_Runtime_GetIsrIdx_ReturnValid;


static inline uint32 rba_Runtime_GetTaskIdx(TaskType foo)
{
  uint32 idx = OS_TASKTYPE_TO_INDEX(foo);

  if( rba_Runtime_GetTaskIdx_ReturnValid )
    return idx; // mapping is done by rba. No need to test it via UT
  else
    return RBA_RUNTIME_TASKNOTUSED;
}

static inline uint32 rba_Runtime_GetIsrIdx(ISRType foo)
{
  uint32 idx = OS_ISRTYPE_TO_INDEX(foo);

  if( rba_Runtime_GetIsrIdx_ReturnValid )
    return idx; // mapping is done by rba. No need to test it via UT
  else
    return RBA_RUNTIME_ISRNOTUSED;
}




#endif