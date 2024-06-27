; Copyright:
; Robert Bosch GmbH reserves all rights even in the event of industrial property rights.
; We reserve all rights of disposal such as copying and passing on to third parties.

; Start of FSW vector, reset vector is excluded form .os_intvecs
; therefore branch done manually

  .file    "RBSYS_FSWStartVectUnicon.s"
  .section ".FSWStartvect",.text
  .align 0x200
  .globl FSWStart
  .thumb2

FSWStart:
  .need Os_CPUVec0               ; ensure retain of .os_text_core0 which are not directly referenced within C code
  B RBSYS_StartupPreOSPhase0+4   ; use Jump w/ 32bit addressing here to avoid further FarCall patches - see defect
                                 ; 475964: [RBSYS] Linker modification within interrupt vector table
                                 ; todo: currently offset 4 is necessary to skip stack access in RBSYS_StartupPreOsPhase0,
                                 ;       find solution!
  .align 16
