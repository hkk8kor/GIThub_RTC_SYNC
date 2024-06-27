param(
    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [string]$InFile=$(throw "Input File is needed (typically mmp2.bat from cc-as)"),    
    [string]$OutFile=$(throw "Output File is needed (typically StartDebugger.bat in out directory)")    ,
    [string]$ElfFile=$(throw "ElfFile is needed")
    #[string]$InFile =        ".\rb\as\core\hwp\hsw\tools\_ghs_debugger\RH850\mmp2.bat",
    #[string]$OutFile =       ".\GEN\RBx4xPLANT\out\StartDebugger.bat",
    #[string]$ElfFile=       ".\GEN\RBx4xPLANT\out\Bin_BB99999_RBx4xPLANT.elf"
)


function main(){
  
  $script = Get-Content $InFile
  $output = ""
  $ghs_tooling = $InFile -replace "\\mmp2\.bat","\scripts\set_GHS_tooling.bat"

  foreach ($l in $script){

    $l = $l -replace "call scripts\\set_GHS_tooling\.bat.*$",""
    $l = $l -replace "set PRJ_ROOT=.*$","set PRJ_ROOT=..\..\.."
    $l = $l -replace "set OUTFILE=.*$","set OUTFILE=$ElfFile"
    $l = $l -replace "pushd %PRJ_ROOT%","pushd %PRJ_ROOT%`ncall $ghs_tooling"

    $output += $l+"`n"
  }
  $output | Out-File -FilePath $OutFile -Encoding ascii
  
  Write-Host "Debugger Start Script generated:"$OutFile
}

main

