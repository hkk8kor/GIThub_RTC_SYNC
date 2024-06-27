; Copyright:
; Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
; We reserve all rights of disposal such as copying and passing on to third parties.

  .globl RBSYS_BBStartupPreOSPhase0
  .globl Os_CPUVec0

  .file "RBSYS_Bootblock_ExceptionHandler_Unicon.s"
  .section ".BBintvect",.text
  .offset 0x0000
  .thumb2

; Vector 0x0000: RESET
_BBResetVector:
   B RBSYS_BBStartupPreOSPhase0         ; branch to reset handler
   
; Branches directly to the FSW OS

; Vector 0x04: Undefined Instruction
  B Os_CPUVec0+0x04
; Vector 0x08: SVC (Supervisor Call)
  B Os_CPUVec0+0x08
; Vector 0x0C: Prefetch Abort
  B Os_CPUVec0+0x0C
; Vector 0x10: Data Abort
  B Os_CPUVec0+0x10
; Vector 0x14: Unused (Hypervisor Trap - is never used from this Vector table!)
  B Os_CPUVec0+0x14
; Vector 0x18: IRQ
  B Os_CPUVec0+0x18
; Vector 0x1C: FIQ
  B Os_CPUVec0+0x1C

