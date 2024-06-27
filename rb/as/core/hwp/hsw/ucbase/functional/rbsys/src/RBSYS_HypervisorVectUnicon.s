; Copyright:
; Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
; We reserve all rights of disposal such as copying and passing on to third parties.

; Hypervisor interrupt vector

  .file    "RBSYS_HypervisorVectUnicon.s"
  .section .text
  .align 0x20
  .globl HypVect
  .globl RBSYS_ExceptionVector_HypervisorTrap
  .thumb2

  .globl Os_UnexpectedException0

HypVect:
  B Os_UnexpectedException0
  B Os_UnexpectedException0
  B Os_UnexpectedException0
  B Os_UnexpectedException0
  B Os_UnexpectedException0
  B RBSYS_ExceptionVector_HypervisorTrap
  B Os_UnexpectedException0
  B Os_UnexpectedException0


RBSYS_ExceptionVector_HypervisorTrap:
  mrs SP, SP_usr               ; load stack pointer from interrupted thread
  cpsie a                      ; enable SError interrupt
  mrs lr, elr_hyp              ; copy exception return address to link register
  push {r0}                    ; store r0 to stack in order to be able to use it
  mrs r0, spsr_hyp             ; load saved program status register of interrupted thread
  bfi lr, r0, 0, 1             ; copy instruction set mode bit to link register
  pop {r0}                     ; restore r0 from stack
  bx lr                        ; jump to exception return address in correct instruction set mode without leaving hypervisor mode
