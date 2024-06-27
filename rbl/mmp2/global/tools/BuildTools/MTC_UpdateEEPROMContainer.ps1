param(
    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [string]$NVMDataFile=$(throw "NVMData Json file from FeatureModel generation is needed."),    
    [string]$ContainerFile=$(throw "EEPROM Containerfile from MTC Build is missing.")    
    #[string]$NVMDataFile =       "D:\workspace_mmp2_featuremodel_sharcc\mmp2\NVMData\cfg\GMx2xSC.json",
    #[string]$ContainerFile =     "D:\workspace_mmp2_featuremodel_sharcc\mmp2\GEN\GMx2xSC\out\EEPROM_Container_BB99999_GMx2xSC.cnt"
)

function Add-DescrBlock($Container,$Name,$Data){
  $Elements = ((($Data -replace "\[","") -replace "\]","") -replace " ","") -split(",")
  $DataString = ""
  foreach ($e in $Elements){    
    $DataString += "<DATA>"+$e+"</DATA>"    
  }  

  [xml]$datablock = "<DATABLOCK>
      <DATABLOCK-NAME>"+$Name+"__Desc</DATABLOCK-NAME>
      <DATAFORMAT>text</DATAFORMAT>
      <DATABLOCK-CLASS>eeprom_data_description</DATABLOCK-CLASS>
      "+$DataString+"
    </DATABLOCK>" 

  $imported=$Container.ImportNode($datablock.DATABLOCK,$true) 
  $Container.'ECU-MEM'.MEM.AppendChild($imported) | Out-Null
}

function Add-DataBlock($Container,$Name,$Data){  
  $Elements = ((($Data -replace "\[","") -replace "\]","") -replace " ","") -split(",")
  $DataString = ""
  foreach ($e in $Elements){
    if ($e -match "\*"){
      $j = $e -replace "\*.*",""
      $d = $e -replace ".*x",""
      for ($i=0;$i -lt $j;$i++){
        $DataString += "<DATA>"+($d)+"</DATA>"    
      }
    } else {
      $DataString += "<DATA>"+($e -replace "0x","")+"</DATA>"    
    }
  }

  [xml]$datablock = "<DATABLOCK>
      <DATABLOCK-NAME>"+$Name+"__Org</DATABLOCK-NAME>
      <DATAFORMAT>hexadecimal</DATAFORMAT>
      <DATABLOCK-CLASS>eeprom_data_original</DATABLOCK-CLASS>
      "+$DataString+"
    </DATABLOCK>" 

  $imported=$Container.ImportNode($datablock.DATABLOCK,$true) 
  $Container.'ECU-MEM'.MEM.AppendChild($imported) | Out-Null
}

function Add-Session($name,$comment,$Container){

  [xml]$datablock = "<SESSION>
        <COMMENT>"+$comment+"</COMMENT>
        <SESSION-NAME>"+$name+"</SESSION-NAME>
        <IMPLIED></IMPLIED>
        <DATAPOINTERS>          
        </DATAPOINTERS>
      </SESSION>"
  $imported=$Container.ImportNode($datablock.SESSION,$true)   
  return $Container.'ECU-MEM'.MEM.SESSIONS.AppendChild($imported)
}

function Create-Copy($datapointer,$key,$copy){
  if ($datapointer.SelectSingleNode('DATAPOINTERS').HasChildNodes){
    if (!($datapointer.DATAPOINTERS.DATAPOINTER).'DATAPOINTER-NAME'.Contains($key)){
      $datapointer.SelectSingleNode('DATAPOINTERS').AppendChild($copy) | Out-Null
    }
  } else {
    $datapointer.SelectSingleNode('DATAPOINTERS').AppendChild($copy) | Out-Null
  }
}

function main(){
  Get-Date
  $nvm = @{}
  $nvmdescr = @{}
  $nvmusage = @{}

  #set up data hash
  $NVMData = (Get-Content -Path $NVMDataFile | ConvertFrom-Json)
  foreach ($key in (($NVMData.data  | Get-Member -Type NoteProperty).Name)){
    $nvm.Add($key,$NVMData.data.$key)
  }
  foreach ($key in (($NVMData.descr  | Get-Member -Type NoteProperty).Name)){
    $nvmdescr.Add($key,$NVMData.descr.$key)
  }
  foreach ($key in (($NVMData.usage  | Get-Member -Type NoteProperty).Name)){
    $nvmusage.Add($key,@((((($NVMData.usage.$key) -replace "\[","") -replace "\]","") -replace " ","") -split(",")))
  }

  #inport XML Container
  [xml]$Container = Get-Content $ContainerFile

  $Delivery = $null
  $Reprog = $null
  $Reset = $null
  $All = $null

  foreach ($session in $Container.'ECU-MEM'.MEM.SESSIONS.SESSION){
    if ($session."SESSION-NAME" -eq "__ALL__"){
      $All = $session
      foreach ($datapointer in $session.DATAPOINTERS.DATAPOINTER){
        $out = "  "+$datapointer."DATABLOCK-NAME"+"  "+$datapointer."DATAPOINTER-NAME"+"  "+$datapointer."DATAPOINTER-IDENT"+"  "+$datapointer."DATAFORMAT-IDENTIFIER"
        if (($nvm.ContainsKey($datapointer."DATABLOCK-NAME")) -and ($datapointer."DATAFORMAT-IDENTIFIER" -eq "ee_range")){
          Write-Host $out
          $datapointer."DATAFORMAT-IDENTIFIER" = "ee_datablock"
          Add-DataBlock -Container $Container -Name ($datapointer."DATABLOCK-NAME") -Data $nvm[($datapointer."DATABLOCK-NAME")]

          if ($nvmdescr.ContainsKey($datapointer."DATABLOCK-NAME")){
            Add-DescrBlock -Container $Container -Name ($datapointer."DATABLOCK-NAME") -Data $nvmdescr[($datapointer."DATABLOCK-NAME")]
          }
        }
      }
    } else {
      switch ($session."SESSION-NAME"){

       "DeliveryState"        { 
         $Delivery = $session ;break
       }
       "ResetToDeliveryState" { 
         $Reset = $session ;break
       }
       "ECUReprogramming" { 
         $Reprog = $session ;break
       }
      }
    }
  }
  
  if ($Reprog -eq $null){
    Write-Host "Adding the reprog session..."
    $Reprog = Add-Session -name "ECUReprogramming" -comment "Reprog" -Container $Container    
  }

  if ($Delivery -eq $null){
    Write-Host "Adding the delivery session..."
    $Delivery = Add-Session -name "DeliveryState" -comment "DeliveryState" -Container $Container    
  }

  if ($Reset -eq $null){
    Write-Host "Adding the reset session..."
    $Reset = Add-Session -name "ResetToDeliveryState" -comment "ResetToDeliveryState" -Container $Container    
  }

  #Correct the DataBlock-Name and Copy Entry also for Delivery Session:
  foreach ($datapointer in $All.DATAPOINTERS.DATAPOINTER){
    if ($nvmusage.ContainsKey($datapointer."DATAPOINTER-NAME")){      
      foreach ($e in $nvmusage[$datapointer."DATAPOINTER-NAME"]){
        $datapointer."DATABLOCK-NAME" = $datapointer."DATAPOINTER-NAME"
        $copy = $datapointer.Clone()

        switch ($e){
          "Reprog" {
            Create-Copy -datapointer $Reprog -key $datapointer."DATAPOINTER-NAME" -copy $copy
            break }
          "DeliveryState" { 
            Create-Copy -datapointer $Delivery -key $datapointer."DATAPOINTER-NAME" -copy $copy
            break }
          "ResetToDeliveryState" { 
            Create-Copy -datapointer $Reset -key $datapointer."DATAPOINTER-NAME" -copy $copy
            break }
        }
      }
    }
  }

  $Container.Save(($ContainerFile -replace "\.cnt","_patched.cnt"))
  Get-Date

}

main

