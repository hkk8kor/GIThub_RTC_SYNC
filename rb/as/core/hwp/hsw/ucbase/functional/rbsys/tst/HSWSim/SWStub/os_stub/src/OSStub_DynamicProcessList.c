
#include "OSStub_DynamicProcessList.h" ///< realize

#include "assert.h"

#include "string.h"

#include "Std_Types.h" ///< TRUE/FALSE

static ossim_ProcessContainer* ossim_procList_GetFirst( ossim_ProcessContainer* from )
{
  while( from->Reloc_Prev != NULL )
  {
    from = from->Reloc_Prev;
  }
  
  return from;
}
static ossim_ProcessContainer* ossim_procList_GetLast( ossim_ProcessContainer* from )
{
  while( from->Reloc_Next != NULL )
  {
    from = from->Reloc_Next;
  }
  
  return from;
}

static int ossim_procList_SetNext( ossim_ProcessContainer* setAt,
                                    ossim_ProcessContainer* next )
{
  int result = 0;
  
  /// check whole chain, to avoid double add.
  setAt = ossim_procList_GetFirst(setAt);
  
  while( (setAt->Reloc_Next != NULL)
      && (setAt != next)
    )
  {
    setAt = setAt->Reloc_Next;
  }
  
  /// abort further handling, if same
  if( setAt == next ) return result;

  if( setAt->SortData.SortLogicValue == ossim_PSLV_Last )
  {
    if( next->SortData.SortLogicValue == ossim_PSLV_Last )
    {
      assert( 0 && "Two elements want to be last.");
      result += 1;
    }
    
    setAt->Reloc_Prev->Reloc_Next = next;
    next->Reloc_Prev = setAt->Reloc_Prev;
    next->Reloc_Next = setAt;
    setAt->Reloc_Prev = next;
  }
  else if( setAt->SortData.SortLogicValue == ossim_PSLV_Undefined )
  {
    setAt->Reloc_Next = next;
    next->Reloc_Prev  = setAt;
  }
  else
  {
    assert( 0 && "Unknown ProcessSortingLogicValue (PSLV)");
    result += 1;
  }
  
  return result;
}

static ossim_ProcessContainer* ossim_procList_GetByProc( 
                        Procedure proc,
                        ossim_ProcessContainer* proc_list,
                        int proc_list_len)
{
  ossim_ProcessContainer* container = NULL;
  
  int i;
  
  for( i = 0; i < proc_list_len; i++ )
  {
    if( proc_list[i].Process == proc )
    {
      container = & proc_list[i];
      break;
    }
  }
  
  return container;
}

static int ossim_procListRelocate_GetFirstAndLast( 
                        ossim_ProcessContainer* proc_list,
                        int proc_list_len,
                        ossim_ProcessContainer** first,
                        ossim_ProcessContainer** last
                        )
{
  /// get any used
  
  int i;
  
  int ret = 1;///< found none used
  
  for( i = 0; i < proc_list_len; i++ )
  {
    if( proc_list[i].Process != NULL )
    {
      *first = ossim_procList_GetFirst( & proc_list[i] );
      *last  = ossim_procList_GetLast(  & proc_list[i] );
      break;
    }
  }
  
  if( (*first != NULL) && (*last != NULL) )
    ret = 0;
  
  return ret;
}

static int ossim_procListRelocate_AddToFirstUsedAsNext(
                        ossim_ProcessContainer* current_cont,
                        ossim_ProcessContainer* proc_list,
                        int proc_list_len,
                        int dont_add_if_first_used_is_itself)
{
  int i;
  
  int resp = 0;
  
  /// get any entry unequal this and add
  for( i = 0; i < proc_list_len; i++ )
  {
    if( current_cont != &(proc_list[i]) )
    {
      if( proc_list[i].Process != NULL )
      {
        resp += ossim_procList_SetNext( & proc_list[i], current_cont );
        break;///< abort looking
      }
    }
    else/// itself
    {
      if( dont_add_if_first_used_is_itself )
      {
        break;
      }
    }
  }
  
  return resp;
}

static int ossim_procListRelocate_SetNextAndPrev( 
                        ossim_ProcessContainer* current_cont,
                        ossim_ProcessContainer* proc_list,
                        int proc_list_len)
{
  int i;
  
  int result = 0;
  
  /// early exit, don't do anything for empty entries.
  if( current_cont->Process == NULL )
    return 0;

  /// handle "before anchor"
  if( current_cont->SortData.BeforeProc != NULL )
  {
    ossim_ProcessContainer* post = ossim_procList_GetByProc( 
                                      current_cont->SortData.BeforeProc, 
                                      proc_list, 
                                      proc_list_len );
    
    if( post != NULL )
    {
      ossim_ProcessContainer* prev = ossim_procList_GetFirst( post );
      result += ossim_procList_SetNext( current_cont , prev );
    }
  }
  
  /// handle "after anchor"
  if( current_cont->SortData.AfterProc != NULL )
  {
    ossim_ProcessContainer* pre = ossim_procList_GetByProc( 
                                      current_cont->SortData.AfterProc,
                                      proc_list, 
                                      proc_list_len );
    
    if( pre != NULL )
    {
      ossim_ProcessContainer* current_first = ossim_procList_GetFirst( current_cont );
      result += ossim_procList_SetNext( pre , current_first );
    }
  }
  
  /// handle processing sorting logic value (PSLV)
  if( current_cont->SortData.SortLogicValue != ossim_PSLV_Undefined )
  {
    if( current_cont->SortData.SortLogicValue == ossim_PSLV_Last )
    {
      result += ossim_procListRelocate_AddToFirstUsedAsNext( current_cont, proc_list,
                                           proc_list_len, FALSE 
                                           /*dont add if first is itself*/);
    }
    else
    {
      assert( 0 && "Unknown ProcessSortingLogicValue (PSLV)");
      result += 1;
    }
  }
  
  /// complete no dependency defined
  if( //( current_cont->Reloc_Next == NULL )
    //&&
    ( current_cont->Reloc_Prev == NULL )
    )
  {
    /// same like "last"
    result += ossim_procListRelocate_AddToFirstUsedAsNext( current_cont, proc_list,
                                         proc_list_len, 
                                         TRUE /*dont add if first is itself*/);
  }
  
  return result;
}

/// just to simplify parameter handling internally
typedef struct
{
  ossim_ProcessContainer* list;
  int                     len;
  
}procListContainer;


static int ossim_procListRelocate_ResetLocationingData(procListContainer* cont)
{
  int i;
  
  int isAnyUsed = FALSE;
  
  for( i = 0; i < cont->len ; i++ )
  {
    ossim_ProcessContainer* single = &(cont->list[i]);
    
    if( single->Process != NULL )
      isAnyUsed = TRUE;
    
    single->Reloc_OldLoc = i;
    single->Reloc_Next   = NULL;
    single->Reloc_Prev   = NULL;
  }
  
  return isAnyUsed;
}

static int ossim_procListRelocate_EstablishChain( procListContainer* cont )
{
  int i;
  
  int result = 1;
  
  for( i = 0; i < cont->len ; i++ )
  {
    ossim_ProcessContainer* single = &(cont->list[i]);
   
    result = ossim_procListRelocate_SetNextAndPrev(single, cont->list, cont->len);
    
    if( result != 0 )
      break;
  }
  
  return result;
}

static int ossim_procCont_ReplaceNext(ossim_ProcessContainer* moved, 
                                      ossim_ProcessContainer* original_next,
                                      ossim_ProcessContainer* new_next
                                      )
{
  while( moved->Reloc_Next != NULL )
  {
    if( moved->Reloc_Next == original_next )
    {
      moved->Reloc_Next = new_next;
      return 0;
    }
    
    moved = moved->Reloc_Next;
  }
  
  assert( 0 && "Next replaced, but not found in remaining list anymore.");
  
  return 1;
}

static int ossim_procCont_IsAnyNext(ossim_ProcessContainer* move, ossim_ProcessContainer* check)
{
  while( move->Reloc_Next != NULL )
  {
    if( move->Reloc_Next == check )
      return TRUE;
    
    move = move->Reloc_Next;
  }
  
  return FALSE;
}

static int ossim_procCont_IsBefore( procListContainer* cont, 
                                   Procedure proc_before,
                                   Procedure proc_after )
{
  int i;
  
  int i_after  = cont->len;
  int i_before = -1;
  
  int isBefore = FALSE;
  
  for( i = 0; i < cont->len; i++ )
  {
    if( cont->list[i].Process == NULL )
      break;///< stop at first unused
    
    if( cont->list[i].Process == proc_after )
      i_after  = i;
    if( cont->list[i].Process == proc_before )
      i_before = i;
  }
  
  return i_before < i_after;
}

static int ossim_procCont_IsAfter( procListContainer* cont, 
                                   Procedure proc_after,
                                   Procedure proc_before )
{
  return ossim_procCont_IsBefore( cont, proc_before, proc_after );
}

/** Detects cyclic dependencies etc.
*/
static int ossim_procListRelocate_ValidateResult( procListContainer* cont )
{
  int result = 0;

  int i;
  
  int lastAlreadySet = FALSE;
  int firstUnusedFound = FALSE;
  
  for( i = 0; i < cont->len; i++ )
  {
    ossim_ProcessContainer* single = &(cont->list[i]);
    
    int isUsed = single->Process != NULL;
    
    if( isUsed )
    {
      if( firstUnusedFound )
      {
        assert( 0 && "Unused followed by unused not allowed.");
        result += 1;
      }
      if( lastAlreadySet )
      {
        assert( 0 && "Last element already set, but followed by another used.");
        result += 1;
      }
    }
    else /// unused
    {
      firstUnusedFound = TRUE;
      
      continue;///< following checks not performed for unused.
    }
  
    if( single->SortData.BeforeProc != NULL )
    {
      int isBefore = ossim_procCont_IsBefore( cont, single->Process, single->SortData.BeforeProc );
      if( !isBefore )
      {
        assert( 0 && "Process order not achieved [BeforeProc]");
        result += 1;
      }
    }
    
    if( single->SortData.AfterProc != NULL )
    {
      int isAfter = ossim_procCont_IsAfter(  cont, single->Process, single->SortData.AfterProc );
      if( !isAfter )
      {
        assert( 0 && "Process order not achieved [AfterProc]");
        result += 1;
      }
    }
    
    if( single->SortData.SortLogicValue != ossim_PSLV_Undefined )
    {
      switch( single->SortData.SortLogicValue )
      {
        case ossim_PSLV_Last:
          lastAlreadySet = TRUE;
          break;
          
        default:
          assert( 0 && "SortLogicValue not handled in ValidateResult");
          result += 1;
          break;
      }
    }
    
  }/// end for each element (used and unused).
  
  return result;
}


static int ossim_procListRelocate_RelocateInPlace( procListContainer* cont,
                                                   ossim_ProcessContainer* first,
                                                   ossim_ProcessContainer* last )
{
  int result = 0;
  
  int i;
  
  ossim_ProcessContainer* curr   = NULL;
  ossim_ProcessContainer* toMove = NULL;
  ossim_ProcessContainer* tmp    = NULL;
  ossim_ProcessContainer  mem;
  
  toMove = first;
  
  /// now move elements according there order in list.
  /// problem: have to be "in-place", realloc shall not be used.
  for( i = 0; i < cont->len; i++ )
  {
    curr = &(cont->list[i]);
    
    if( toMove != NULL )
    {
      if( curr->Process != toMove->Process )
      {
        ossim_ProcessContainer* next_replaced = NULL;
        
        int isCurrLast = FALSE;
        int isToMoveLast = FALSE;
        
        if( ossim_procCont_IsAnyNext(toMove, curr) )
          next_replaced = curr;
        if( curr == last )
          isCurrLast = TRUE;
        if( toMove == last )
          isToMoveLast = TRUE;
        
        /// save current data to memory.
        memcpy( &mem, curr  , sizeof( ossim_ProcessContainer ) );
        /// move current "mover" to desired location
        memcpy( curr, toMove, sizeof( ossim_ProcessContainer ) );
        /// move "data from memory" to previous location of "mover".
        memcpy( &(cont->list[toMove->Reloc_OldLoc]), &mem, sizeof( ossim_ProcessContainer ) );
        
        /// pointer "toMove" now point to "curr" data, and "curr" to "mover" data.
        /// twist that
        tmp = curr;
        curr = toMove;
        toMove = tmp;
        
        if( next_replaced != NULL )///< next was the one which is moved soon
        {
          result = ossim_procCont_ReplaceNext( toMove, next_replaced, curr );

          /// also update storage location of "curr"
          curr->Reloc_OldLoc = toMove->Reloc_OldLoc;
        }
        if( isCurrLast )
        {
          last = curr;
        }
        if( isToMoveLast )
        {
          last = toMove;
        }
      }
      else
      {
        /// nothing to do.
      }
      
      ///< Reloc_Next can be NULL, but we will nevertheless go through whole list
      if( toMove->Reloc_Next == NULL )
      {
        if (toMove != last)
        {
          assert( 0 && "Chain calculation failed.");
          result = 1;
        }
      }
      toMove = toMove->Reloc_Next;
      
    }
    else
    {/// nothing to move anymore, so remaining list should be "empty"
      if( curr->Process != NULL )
      {
        assert( 0 && "Relocation algorithm failed.");
        result = 2;
      }
    }
    
    if( result != 0 )
      break;
  }/// end for complete process list (incl. unused items)                      
  
  return result;
}

/** @brief Reorganize complete process-list.
  
  Function have to be used after any add/remove activity in list.
  
  Complete list will be checked, only entries with "Process != NULL"
  will be organized.
  
  All known elements have to be in list.
  
  @return return code == 0 (good) and != 0 (bad/error) ,
          but relocation errors, will currently result in "assert()".
*/
static int ossim_procListRelocate( ossim_ProcessContainer* proc_list,
                                    int proc_list_len )
{
  int i;
  
  int result = 0;
  
  ossim_ProcessContainer* first  = NULL;
  ossim_ProcessContainer* last   = NULL;
  
  int isAnyUsed;
  
  procListContainer proc_list_cont;
  proc_list_cont.list  = proc_list;
  proc_list_cont.len   = proc_list_len;
  
  /// reset relocation data.
  isAnyUsed = ossim_procListRelocate_ResetLocationingData(&proc_list_cont);
  
  if( !isAnyUsed ) return result;

  /// set "Reloc_Next" and "Reloc_Prev" for each single element.
  result = ossim_procListRelocate_EstablishChain(&proc_list_cont);
  
  if( result != 0 ) return result;
  
  /// now Reloc_Next and Reloc_Prev are set for all
  /// check chain and get first and last
  result = ossim_procListRelocate_GetFirstAndLast(  proc_list, proc_list_len,
                                                    &first, &last );

  if( result != 0 ) return result;
  
  result = ossim_procListRelocate_RelocateInPlace( &proc_list_cont,
                                                   first, last );

  if( result != 0 ) return result;
  
  result = ossim_procListRelocate_ValidateResult( &proc_list_cont );
  
  return result;
}

int ossim_RemoveProcess( ossim_ProcessContainer* proc_list,
                                int proc_list_len,
                                Procedure proc )
{
  /// order is only handled during "add", therefore here
  /// I will just condense the list (all after "removed" are moved upwards).

  int i = 0;
  
  int ret = 0;
  
  while(  (i < proc_list_len)
        &&(proc_list[i].Process != NULL)
       )
  {
    if( proc_list[i].Process == proc )
    {
      proc_list[i].Process = NULL;
      /// may not be twice in list -> we can break
      break;
    }

    i++;
  }

  ret = ossim_procListRelocate(proc_list, proc_list_len);
  
  return ret == 0;
}

int ossim_AddProcess(ossim_ProcessContainer* proc_list,
                                int proc_list_len,
                                Procedure proc)
{
  return ossim_AddProcessX( proc_list,
                            proc_list_len,
                            proc,
                            NULL/*bef*/,
                            NULL/*after*/,
                            ossim_PSLV_Undefined );
}

int ossim_AddProcessX( ossim_ProcessContainer* proc_list,
                                int proc_list_len,
                                Procedure proc,
                                Procedure run_before_proc,
                                Procedure run_after_proc,
                                ossim_ProcessSortLogicValue pslv )
{
  int i = 0;

  int alreadyIn = FALSE;///< allow multiple calls with same function.

  while( proc_list[i].Process != NULL )
  {
    if( proc_list[i].Process == proc )
    {
      alreadyIn = TRUE;
    }

    i++;

    if(  ( i >= proc_list_len )
      || (alreadyIn) )
    {
      break;/// abort looping.
    }
  }

  if( alreadyIn )
  {
    return TRUE;/// already in
  }
  else if( i < proc_list_len )
  {
    int ret;
    
    /// ensure, that other members are zeroed.
    memset( & proc_list[i], 0, sizeof( ossim_ProcessContainer ) ) ;
    
    proc_list[i].Process = proc;
    proc_list[i].SortData.SortLogicValue = pslv;
    proc_list[i].SortData.BeforeProc     = run_before_proc;
    proc_list[i].SortData.AfterProc      = run_after_proc;
    
    ret = ossim_procListRelocate(proc_list, proc_list_len);
    
    if( ret != 0 )///< failure - remove newly added element again.
    {
      ret += ossim_RemoveProcess( proc_list, proc_list_len, proc );
    }
    
    return ret == 0;
  }
  else
  {
    return FALSE;
  }
}
