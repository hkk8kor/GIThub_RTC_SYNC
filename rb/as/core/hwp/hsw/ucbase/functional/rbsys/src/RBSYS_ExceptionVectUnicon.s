; Copyright:
; Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
; We reserve all rights of disposal such as copying and passing on to third parties.

; Exception vector redirections for Unicon. Temporary as RTAOS currently does not provide an option
; to call the same Exception Handler from all cores (for the same exception type). Design is currently
; being checked by XC-ECO and ETAS

  .file    "RBSYS_ExceptionVectUnicon.s"
  .section .text

  .globl b_EXCUndefinedInstruction0
  .globl b_EXCUndefinedInstruction1
  .globl b_EXCPrefetchAbort0
  .globl b_EXCPrefetchAbort1
  .globl b_EXCDataAbort0
  .globl b_EXCDataAbort1

  .globl RBSYS_ExceptionVector_UndefinedInstruction
  .globl RBSYS_ExceptionVector_PrefetchAbort
  .globl RBSYS_ExceptionVector_DataAbort

  .thumb2

  .align 16

b_EXCUndefinedInstruction0:
b_EXCUndefinedInstruction1:
  B RBSYS_ExceptionVector_UndefinedInstruction+4;

b_EXCPrefetchAbort0:
b_EXCPrefetchAbort1:
  B RBSYS_ExceptionVector_PrefetchAbort+4;

b_EXCDataAbort0:
b_EXCDataAbort1:
  B RBSYS_ExceptionVector_DataAbort+4;

; todo: currently offset 4 is necessary to skip stack access at first instruction of the called function, find solution!