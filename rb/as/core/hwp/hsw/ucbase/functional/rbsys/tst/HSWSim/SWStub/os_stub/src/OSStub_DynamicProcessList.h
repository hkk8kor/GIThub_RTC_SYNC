#ifndef OSSTUB_DYNAMICPROCESSLIST_H__
#define OSSTUB_DYNAMICPROCESSLIST_H__

#include "RB_Config.h" // <RBFS_TexecUsedIn

#include "OSStub_Procedure.h" ///< for Procedure-type.

typedef enum
{
  /// ProcessSortLogicValue = PSLV
  ossim_PSLV_Undefined = 0,
  ossim_PSLV_Last
}ossim_ProcessSortLogicValue;

typedef struct
{
  Procedure                   BeforeProc;
  Procedure                   AfterProc;
  ossim_ProcessSortLogicValue SortLogicValue;
  
}ossim_ProcessSortData;

typedef struct ossim_ProcessContainer
{
  Procedure               Process;
  ossim_ProcessSortData   SortData;
  
  /// for "in-place" relocations.
  /// Each add/remove will trigger a relocation.
  struct ossim_ProcessContainer* Reloc_Next;
  struct ossim_ProcessContainer* Reloc_Prev;
  int                            Reloc_OldLoc;
  
}ossim_ProcessContainer;


/** Functions ********************************************* */

extern int ossim_AddProcess(ossim_ProcessContainer* proc_list,
                                int proc_list_len,
                                Procedure proc);
                                
extern int ossim_RemoveProcess( ossim_ProcessContainer* proc_list,
                                int proc_list_len,
                                Procedure proc );
                                
extern int ossim_AddProcessX( ossim_ProcessContainer* proc_list,
                                int proc_list_len,
                                Procedure proc,
                                Procedure run_before_proc,
                                Procedure run_after_proc,
                                ossim_ProcessSortLogicValue pslv );

#endif
