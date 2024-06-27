Working instruction:

  - adapt ind_crt1.c to consider HW RAM zeroing
  - cross-check with GHS/REL if adaptation is ok
    - check also that we execute code before __start is called
      probably relevant for PIC? in case basepointers are not set at that time

  - ensure OS build with new compiler
  - ensure build of external libs with new compiler

------------------------------------------------------------------------------

Current GHS startup libraries are based on GHS2015.1.7, GHS2018.1.5 and GHS2021.1.5

Guideline to rebuild libstartup with new compiler:

Start GHS Multi (ensure binding with required compiler via gcomplink)

Start Project Manager
- Create "New Top Project"
- Operating System: "Stand-alone"
- Target Board: "RH850G3M"

Project Manager:
- Create New... "Program"
- Program Layout: "Link to and Execute out of ROM"
- select "Startup" and "System" Libraries

Strategy:
- only crt0.800 is adapted to support multi-core
    - initialization of co-processor will not be done in GHS startup code:
            => FPU (CU0) should be done explicitly in RBSYS_InitFPU
            => SIMD (CU1) not available in CC CUBE devices
    - provide interface for RBSYS with extern declarations (sep. header from GHS under clarification)
        => extern void _start(void) used in RBSYS_Bootblock_Startup.c and RBSYS_FSWStartup.c
        => move declaraton "extern int main (int argc, char **argv, char **envp)" from ind_crt0.c
           to sep. interface and include this within ind_crt0.c and RBSYS_FSWStartup.c
- other files are untouched
- crt0.800 moved directly to library libstartup.gpj via cut and paste to fix assembler/compiler settings

- adapt relevant compiler settings to ensure consistent settings to MTC build (see list below):
  -> Certified compiler option sets can be found here:
    - GHS 2015: https://inside-docupedia.bosch.com/confluence/display/BBMCOM/Optionsets+REL_comp_201517_7fp
      -> Option Set 2 (Ogeneral)
    - GHS 2018: https://inside-docupedia.bosch.com/confluence/display/BBMCOM/Optionsets+REL_comp_201815_3fp_x64
      -> Option Set RH8-1 for P1x (Ogeneral, G3M)
      -> Option Set RH8H-1 for U2A (Ogeneral, G4M)
    - GHS 2021:
      -> use same option as with GHS 2018

- "Build Library libstartup.a"

For GHS2015 config:
  - copy libraries libstartup.a, libstartup.dba to relevant folder
    comment: libsys is taken from compiler directory directly. There is no check for valid libraries if GHS2015 is used
For GHS2018 config:
  - copy libraries libstartup.a, libstartup.dba to relevant folder
    comment: libsys is taken from compiler directory directly, libraries will be checked by GHS and will be compiled with the correct settings
For GHS2021 config:
  - copy libraries libstartup.a, libstartup.dba to relevant folder
    comment: libsys is taken from compiler directory directly, libraries will be checked by GHS and will be compiled with the correct settings







=================================================================================================#
Following GHS compiler/linker options must be identical on all sources (e.g. generated objects during normal MTC build, libraries ...):

Answer from GHS (Jeff Young):

Now that you mention the linker checking, I have looked into this further and learn that
there are 3 additional options which need to be consistent between modules.
Inconsistencies with these options are reported by elxr
    -mtda -notda -single_tda
    -align4 -align8
    -sda=never

The following options change register usage directly
(differences in the first 4 are reported by the linker):
-registermode=
-reserve_r2
-reserve_r5
-allocate_ep
-r20_has_255
-r21_has_65535

The following options change the size or signedness of data types
and therefore should be kept the same between files:
-pack=
-floatsingle
--short_enum
-wchar_s32 / -wchar_u16
-kanji=
-time32 / -time64
-signedchar
-signedfield
-unsignedpointer

The following options should be consistent between object files:
-cpu=
-act_like=latest
