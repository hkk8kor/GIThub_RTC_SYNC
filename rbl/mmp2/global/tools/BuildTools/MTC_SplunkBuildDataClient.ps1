param(
    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [string]$MapFile=$(throw "MapFile is needed (from out directory or application container)"),    
    [string]$AnaMapFile=$(throw "AnaMapFile is needed (from out directory or application container)")    
    #[string]$MapFile =        "D:\workspace_mmp2_featuremodel_sharcc\mmp2\Gen\GMx2xSC\out\Map_BB82745_GMx2xSC.map",
    #[string]$AnaMapFile =     "D:\workspace_mmp2_featuremodel_sharcc\mmp2\Gen\GMx2xSC\out\AnaMap_Report_BB82745_GMx2xSC.txt"
)

$splunkserver = "https://rb-itoa-splunk-cc-ps.de.bosch.com:8088/services/collector"

#needed for an untrusted SSL certificate:
add-type @"
    using System.Net;
    using System.Security.Cryptography.X509Certificates;
    public class TrustAllCertsPolicy : ICertificatePolicy {
        public bool CheckValidationResult(
            ServicePoint srvPoint, X509Certificate certificate,
            WebRequest request, int certificateProblem) {
            return true;
        }
    }
"@
[System.Net.ServicePointManager]::CertificatePolicy = New-Object TrustAllCertsPolicy


#Adopted for D3/ED devices, without HSM active...
$regionsize = @{ "LRAM_CPU0" =              130048;
                 "LRAM_CPU1" =              0;
                 "BURAM_BB_FSW_INTERFACE" = 36;
                 "BURAM_BB" =               476;
                 "BURAM_FSW" =              512;
                 "LRAM_HSM" =               0;
                 "VARIABLE_RAM_PART1" =     196608;
                 "GRAM_BANK_A"=             163840;
                 "HSM_SHARED_GRAM"=         0;
                 "GRAM_BANK_B"=             157696;
                 "DLM_RAM"=                 6144;
                 "VARIABLE_RAM_PART2"=      524288;
               }


#Post the event with source and sourcetype to the Splunk-Server
function Post-SplunkEvent($sourcetype,$source,$event){

  $response = ""

  $headers = New-Object "System.Collections.Generic.Dictionary[[String],[String]]"
  $headers.Add("Authorization", 'Splunk 6bdf11e9-e7e3-47b0-b394-6fbbccb21620')
 
  $body = '{
          "host":"' + $env:computername + '",
          "sourcetype":"' + $sourcetype + '",
          "source":"' + $source + '",
          "event": ""
        }'
  $body = ConvertFrom-Json $body

  $body.event = $event

  $response = Invoke-RestMethod -Uri $splunkserver -Method Post -Headers $headers -Body ($body | ConvertTo-Json -Compress)

  return $response
}

function Analyse-MapFile($MapFile) {
  $sections = @()
  $freeRamSections = @{}
  $regions = @{}
  $regionslist = @()

  $map = [Io.File]::ReadAllText($MapFile)
  
  #  Section              Base      Size(hex)    Size(dec)  SecOffs
  #  .FSWStartvect        00000000  00000010           16   0000aa0
  $map | Select-String '(?smi)^  (\.[^\s]+)[\s]+(fe[^\s]+)[\s]+([^\s]+)[\s]+([^\s]+)[\s]+([^\s]+)' -AllMatches | Foreach {$_.Matches} | Foreach {
      $value = New-Object PSObject 

      $value | Add-Member "Section"     $_.Groups[1].Value
      $value | Add-Member "Start Address"          ("0x"+([String]::Format("{0:x}",([Convert]::ToInt64($_.Groups[2], 16)))).PadLeft(8,'0'))
      $value | Add-Member "End Address"            ("0x"+([String]::Format("{0:x}",(([Convert]::ToInt64($_.Groups[2], 16))+($_.Groups[4].Value -as[int])))).PadLeft(8,'0'))
      $value | Add-Member "Size in Hex"            ("0x"+([String]::Format("{0:x}",([Convert]::ToInt64($_.Groups[3], 16)))).PadLeft(8,'0'))
      $value | Add-Member "Size in Dec"            ($_.Groups[4].Value -as[int])
      $value | Add-Member "Free in Hex"            ""
      $value | Add-Member "Free in Dec"            ""
      $value | Add-Member "Section Offset (Dec)"   ("0x"+([String]::Format("{0:x}",([Convert]::ToInt64($_.Groups[5], 16)))).PadLeft(8,'0'))

      $sections += $value
  
  }

  # _g_DownloadArea_PUL              g fef76800-fef773ff 000c00 DLM_RAM      .dlm_noclear     .dlm_noclear     RBAPLPLANT_DownloadServices.o
  $map | Select-String '(?smi)^ [^\s]+[\s]+[lg] (fe[^\s]+)-(fe[^\s]+) ([^\s]+) ([^\s]+)' -AllMatches | Foreach {$_.Matches} | Foreach {
    #ignore labels of size 0 !!!
    if ($_.Groups[3].Value -ne "000000"){
      $start = ([Convert]::ToInt64($_.Groups[1], 16)) 
      $end = ([Convert]::ToInt64($_.Groups[2], 16))

      $region = $_.Groups[4].Value 

      if ($regions.ContainsKey($region)){
        if ($regions[$region].Start -gt $start) { $regions[$region].Start = $start }
        if ($regions[$region].End -lt $start) { $regions[$region].End = $end }
      } else {
        $value = New-Object PSObject 

        $value | Add-Member "Region" $region
        $value | Add-Member "Start"  $start
        $value | Add-Member "End"    $end

        $regions.Add($region,$value)
      }
    }
  }

  $freeram = 0
  foreach ($v in $regions.Values | Sort-Object -Property "Start") {

    #next free address is +1
    $v.End++
    $value = New-Object PSObject 

    $value | Add-Member "Section" $v.Region
    $value | Add-Member "Start Address"  ("0x"+([String]::Format("{0:x}",$v.Start)).PadLeft(8,'0'))
    $value | Add-Member "End Address"    ("0x"+([String]::Format("{0:x}",($v.Start+$regionsize[$v.Region]))).PadLeft(8,'0'))
    $value | Add-Member "Size in Hex"    ("0x"+([String]::Format("{0:x}",($v.End-$v.Start))).PadLeft(8,'0'))
    $value | Add-Member "Size in Dec"    ($v.End-$v.Start)
    $value | Add-Member "Free in Hex"    ("0x"+([String]::Format("{0:x}",($v.Start+$regionsize[$v.Region]-$v.End))).PadLeft(8,'0'))
    $value | Add-Member "Free in Dec"    ($v.Start+$regionsize[$v.Region]-$v.End)

    $sections += $value

    if ($value."Free in Dec".length -ne 0){
     
      $freeRamSections.Add($value."Section",$value."Free in Dec")

      $freeram += $value."Free in Dec"
    }
  }  

  $freeRamSections.Add("Overall",$freeram)

  return $freeRamSections

} 

function Analyse-AnaMapFile($AnaMapFile){
  $Areas = @{}

  $anamap = Get-Content $AnaMapFile

  $values = ($anamap | Select-String -Pattern "Grand Total.*$") -split '\s+'

  $Areas.Add("cinit",$values[3])
  $Areas.Add("code",$values[4])
  $Areas.Add("const",$values[5])
  $Areas.Add("romtotal",$values[6])
  $Areas.Add("ram",$values[7])
  $Areas.Add("overlay",$values[8])
  $Areas.Add("unknown",$values[9])

  return $Areas
}

function Analyse-EnvData(){
  $EnvData = @{}

  $EnvData.Add("ComputerName",$env:COMPUTERNAME)
  $EnvData.Add("BuildVariant",$env:Build_Variant)
  $EnvData.Add("IncrementalBuild",$env:Incremental)
  $EnvData.Add("BuildDefinition",$env:buildDefinitionId)
  $EnvData.Add("BuildLabel",$env:buildLabel)
  $EnvData.Add("PersonalBuild",$env:personalBuild)
  $EnvData.Add("ProcessorNumbers",$env:NUMBER_OF_PROCESSORS)
  $EnvData.Add("Processor",$env:PROCESSOR_IDENTIFIER)
  $EnvData.Add("USER",($env:USERDOMAIN+"\"+$env:USERNAME))
  
  $flagfile = $MapFile
  if ($env:Incremental -ne "Y"){
    #one of the first files that is written during the MTC rebuild execution:
    $flagfile = $flagfile -replace "\\out\\.*$","\make\Cfg_MTC_ConfigurationDefines.cfg"
    $runtime = Get-ChildItem $flagfile | New-TimeSpan
  } else {
    #one of the first files that is written during the MTC incremental execution:
    $flagfile = $flagfile -replace "\\out\\.*$",("\out\_Log_MTCCommands_"+$env:Build_ID+".prt")
    $runtime = Get-ChildItem $flagfile | Select-Object -ExpandProperty CreationTime | New-TimeSpan
  }

  $EnvData.Add("MtcRuntime",($runtime.Hours.ToString().PadLeft(2,'0')+":"+$runtime.Minutes.ToString().PadLeft(2,'0')+":"+$runtime.Seconds.ToString().PadLeft(2,'0')))
  return $EnvData
}

function Analyse-Stack($LogFile){
  $StackData = @{}
  $sum = 0

  $stack = Get-Content $LogFile

  $stack | Select-String '(?smi)^core (\d+) uses (\d+) bytes stack' -AllMatches | Foreach {$_.Matches} | Foreach {
    $StackData.Add("core"+$_.Groups[1].Value,$_.Groups[2].Value)
    $sum += $_.Groups[2].Value
  }

  $StackData.Add("Sum",$sum)
  return $StackData
}


function main(){
  $anamap_data = Analyse-AnaMapFile -AnaMapFile $AnaMapFile
  $mapfile_data = Analyse-MapFile -MapFile $MapFile
  $env_data = Analyse-EnvData

  $event = New-Object PSObject 
  $event | Add-Member "Environment"    ($env_data)
  $event | Add-Member "FreeRAMDetails" ($mapfile_data)
  $event | Add-Member "Ressources"     ($anamap_data)

  $stackfile = $MapFile
  $stackfile = $stackfile -replace "\\out\\.*$",("\out\Log_StackCalculator_"+$env:Build_ID+".prt")
  if (Test-Path -Path $stackfile){
    Write-Host "Stack Analysis data available..."

    $stack_data = Analyse-Stack -LogFile $stackfile
    $event | Add-Member "StackDetails" ($stack_data)
  }

  

  $response = ""
  $response = Post-SplunkEvent -sourcetype "MMP2SWBuildData" -source "MTC_SplunkBuildDataClient" -event $event

  Write-Host "Response to Splunk Post - Code:'" $response.code "' text:'" $response.text  "'" 
}

main

