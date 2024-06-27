param(
    [Parameter()]
    [ValidateNotNullOrEmpty()]
    [string]$configfile = $(throw "-configfile is required.")
    #[string]$configfile = "..\input\RBL_DAI_BR223_VMPS_Int.xml"
    #[string]$configfile = "..\input\RBL_SPL_Complete.xml"
    #[string]$configfile = "..\input\RB_MS_MMP2_europium_int.xml"
)

$OutputFolder
$FeatureModel
$FeatureHash = @{}
$AttributeHash = @{}
$BuildVariants = @{}
$BVHash = @{}
$GlobalTemplateHash = @{}

$MicIncludeHash = @{}
$MicIgnoreHash = @{}

$MicGlobalSel = @{}
$MicLocalSel = @{}

$NVMDataHash = @{}
$NVMDescrHash = @{}
$NVMUsageHash = @{}
$NVMDataFieldHash = @{}


function ReturnNewBVObject {
    
    $obj = New-Object PSObject
    $obj | Add-Member "Customer" ""
    $obj | Add-Member "Product" ""
    $obj | Add-Member "Project" ""
    $obj | Add-Member "ConfigurationType" ""
    $obj | Add-Member "MTCVersion" ""
    $obj | Add-Member "ConfigurationName" ""
    $obj | Add-Member "BBNo" ""              
    $obj | Add-Member "Comment" ""
    $obj | Add-Member "BMGRConfigurationName" ""
    $obj | Add-Member "BLDRConfigurationName" ""
    $obj | Add-Member "Features" @{}
    $obj | Add-Member "BVReplace" @{}
    $obj | Add-Member "MICVariants" @{}
    $obj | Add-Member "MICIgnores" @{}
    $obj | Add-Member "NVMData" @{}
	$obj | Add-Member "NVMDescr" @{}
	$obj | Add-Member "NVMUsage" @{}
    $obj | Add-Member "NVMDataField" @{}

    return $obj
}

function ReturnNewReplaceObject {
    $obj = New-Object PSObject
    $obj | Add-Member "Switch" ""
    $obj | Add-Member "Pattern" ""

    return $obj
}

function GetParent($node){
    $parent = ""  
    foreach ($r in @($node.relations.relation).GetEnumerator())
    {
      if ($r.type -eq "ps:parent")
      {         
        $t = $r.target.'#text'.Trim("./")
        $parent = $FeatureHash[$t].name
      }
    }
    return $parent
}

# This function generates the local and global selectors replacements and stores it in the BVReplace hash
function GenerateBVReplace($bv){
  foreach ($k in $FeatureHash.Keys.GetEnumerator()) {
    $name = $FeatureHash[$k].name

    foreach ($rs in $FeatureHash[$k].relations) {
      if ($rs.class -eq "ps:children") {
        foreach ($r in $rs.relation) {
          switch ($r.type) {
            "ps:alternative" { 
                 foreach ($t in $r.target) {
                   $childname = (GetChildName($t.'#text'))
                   $childid = ($t.'#text' -replace "\./","")                             
                   if ($bv.Features.containsKey($childid)) {
                     if ($MicLocalSel.ContainsKey($k)) {
                       $bv.BVReplace.Add("#"+$name+"#",$name+"_"+$childname)
                     }
                   }
                 }
                 break
               }
            "ps:optional" {
                 foreach ($t in $r.target) {
                   $childname = (GetChildName($t.'#text'))
                   $childid = ($t.'#text' -replace "\./","")
                          
                   if ($bv.Features.containsKey($childid)){
                     if ($MicLocalSel.ContainsKey($childid)) {
                       $bv.BVReplace.Add("#"+$childname+"#",$childname+"_ON")
                     }
                     
                   } else {
                     if ($MicLocalSel.ContainsKey($childid)) {
                       $bv.BVReplace.Add("#"+$childname+"#",$childname+"_OFF")
                     }                    
                   }                 
                 }
                 break
               }
          }
        }
      }
    }
  }
}

function GenerateBVConfigs(){
  foreach ($v in $BuildVariants.Keys.GetEnumerator()){

    $obj = ReturnNewBVObject

    foreach($f in $BuildVariants[$v].consulmodel.elements.element.GetEnumerator()) 
    {
      $p_id = ($f.relations.relation.target.'#text' -replace ".*\/","")
      $node = $FeatureHash[$p_id]
      $parent = GetParent -node $node
      $value = $node.name

      if ($f.type -eq "ps:selected") {
        #collect information in selected features...
        $obj.Features.Add($p_id,$f)

        Switch ($parent) {
          "Customer" { $obj.Customer = $value; break}
          "Product"  { $obj.Product = $value; break}
          "Project"  { $obj.Project = $value; break}
          "ConfigurationType" { $obj.ConfigurationType = $value; break}
          "MTCVersion"        { $obj.MTCVersion = (($value -replace "V","") -replace ("p",".")); break}
        }

        #Check for nvmdata
        foreach ($p in $f.properties.GetEnumerator()) {
          switch ($AttributeHash[($p.name) -replace ".*\/",""]) {
            "nvm_data" { $obj.NVMData.Add($p_id,$p.constant.'#text'); break}
			"nvm_descr" { $obj.NVMDescr.Add($p_id,$p.constant.'#text'); break}
			"nvm_usage" { $obj.NVMUsage.Add($p_id,$p.constant.'#text'); break}
            "nvm_data_bitfield" {$obj.NVMDataField.Add($p_id,$p.constant.'#text'); break}
          }
        }
      }      
      
      if ($value -eq "Configuration") {
        foreach ($p in $f.properties.GetEnumerator()) {
          switch ($AttributeHash[($p.name) -replace ".*\/",""]) {
            "ConfigurationName" { $obj.ConfigurationName = $p.constant.'#text'; break}
            "BBNo"              { $obj.BBNo = $p.constant.'#text'; break}
            "Comment"           { $obj.Comment = $p.constant.'#text'; break}            
            "BMGRConfigurationName" { $obj.BMGRConfigurationName = $p.constant.'#text'; break}
            "BLDRConfigurationName" { $obj.BLDRConfigurationName = $p.constant.'#text'; break}
          }
        }
      }
    }    

    $BVHash.Add($v,$obj)
  }

  #Generate the BVReplace in an extra function
  foreach ($bv in $BVHash.values){
    GenerateBVReplace -bv $bv
  }
}

function GenerateCfgConfigurationsXml ($file) {
  $output = "<MTCConfigurations>`n"

  foreach ($c in $BVHash.Values.GetEnumerator() | Sort-Object -Property ConfigurationName) {
    $output += "  <MTCConfiguration>`n"
    $output += "    <ConfigurationName>"+$c.ConfigurationName+"</ConfigurationName>`n"
    $output += "    <BBNo>"+$c.BBNo+"</BBNo>`n"
    $output += "    <ConfigurationType>"+$c.ConfigurationType+"</ConfigurationType>`n"
    $output += "    <MTCVersion>"+$c.MTCVersion+"</MTCVersion>`n"
    $output += "    <Comment>"+$c.Comment+"</Comment>`n"
    if ($c.BMGRConfigurationName -or $c.BLDRConfigurationName) {
      $output += "    <UsedHexBlocks>`n"
      if( $c.BMGRConfigurationName ) {
        $output += "      <UsedHexBlock>"+$c.BMGRConfigurationName+"</UsedHexBlock>`n"
      }
      if( $c.BLDRConfigurationName ) {
        $output += "      <UsedHexBlock>"+$c.BLDRConfigurationName+"</UsedHexBlock>`n"
      }
      $output += "    </UsedHexBlocks>`n"
    }
    $output += "    <BuildIdPrefix>"+$c.BBNo+"</BuildIdPrefix>`n"
    $output += "  </MTCConfiguration>`n"

    if ($c.BLDRConfigurationName) {
      $output += "  <MTCConfiguration>`n"
      $output += "    <ConfigurationName>"+$c.BLDRConfigurationName+"</ConfigurationName>`n"
      $output += "    <BBNo>"+$c.BBNo+"</BBNo>`n"
      $output += "    <ConfigurationType>"+$c.ConfigurationType+"</ConfigurationType>`n"
      $output += "    <MTCVersion>"+$c.MTCVersion+"</MTCVersion>`n"
      $output += "    <Comment>RB Bootloader for Build Configuration "+$c.ConfigurationName+"</Comment>`n"
      $output += "    <BuildIdPrefix>"+$c.BBNo+"</BuildIdPrefix>`n"
      $output += "  </MTCConfiguration>`n"
    }
    if ($c.BMGRConfigurationName) {
      $output += "  <MTCConfiguration>`n"
      $output += "    <ConfigurationName>"+$c.BMGRConfigurationName+"</ConfigurationName>`n"
      $output += "    <BBNo>"+$c.BBNo+"</BBNo>`n"
      $output += "    <ConfigurationType>"+$c.ConfigurationType+"</ConfigurationType>`n"
      $output += "    <MTCVersion>"+$c.MTCVersion+"</MTCVersion>`n"
      $output += "    <Comment>BootManager for Build Configuration "+$c.ConfigurationName+"</Comment>`n"
      $output += "    <BuildIdPrefix>"+$c.BBNo+"</BuildIdPrefix>`n"
      $output += "  </MTCConfiguration>`n"
    }
  }

  $output += "</MTCConfigurations>`n"
  $output | Out-File -FilePath $file -Encoding ascii 
}

function SetupGlobalTemplateHash () {
  $first = $true
  #loop to set up the template expansion
  foreach ($v in $BVHash.Values.GetEnumerator()){
    if ($first) {
      if ($configfile -eq "..\input\RBL_SPL_CompleteSuperSet.xml") {
        $GlobalTemplateHash.Add("#cust#","rb")
        $GlobalTemplateHash.Add("#prj#","hwref")
        $GlobalTemplateHash.Add("#prod#","mpsp")

      } else {
        $GlobalTemplateHash.Add("#cust#",$v.Customer.ToLower())
        $GlobalTemplateHash.Add("#prj#",$v.Project.ToLower())
        $GlobalTemplateHash.Add("#prod#",$v.Product.ToLower())
      }
      $first = $false
    }
  }
}

function WriteFile ($file,$content) {
  $outpath = $file -replace ($file -replace ".*\\",""),""
  if (!(Test-Path $outpath)) {
      New-Item -Path $outpath -ItemType Directory -Force > $null
  }

  $content | Out-File -FilePath $file -Encoding ascii -Force
}

function ExpandString($in,$rep) {
  $output = $in

  foreach ($r in $GlobalTemplateHash.Keys.GetEnumerator()) {
    $output = $output -replace $r,$GlobalTemplateHash[$r]
  }

  if ($rep) {
    foreach ($r in $rep.Keys.GetEnumerator()) {
      $output = $output -replace $r,$rep[$r]
    } 
  }

  return $output
}

function ExpandTemplate($in,$out,$rep){
  $output = Get-Content $in

  foreach ($r in $GlobalTemplateHash.Keys.GetEnumerator()) {
    $output = $output -replace $r,(ExpandString -in $GlobalTemplateHash[$r] -rep $rep)
  }

  if ($rep) {
    foreach ($r in $rep.Keys.GetEnumerator()) {
      $output = $output -replace $r,(ExpandString -in $rep[$r] -rep $rep)
    } 
  }

  WriteFile -file $out -content $output  
}

function GenerateBcfgFiles ($output, $template) {
  
  # Cfg_Build_Master.bcfg:
  $in  = $template+"\Cfg_Build_Master.bcfg_tpl"
  $out = $output+"\Cfg_Build_Master.bcfg"

  $LocalTemplateHash = @{}
  $LocalBmgrBuild = @()
  $LocalBldrBuild = @()
  foreach ($bv in $BVHash.Values.GetEnumerator()) {
    if($bv.BMGRConfigurationName) {
      $LocalBmgrBuild += "(RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_"+$bv.BMGRConfigurationName+")"
    }
    if($bv.BLDRConfigurationName) {
      $LocalBldrBuild += "(RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_"+$bv.BLDRConfigurationName+")"
    }
  }
  if($LocalBmgrBuild.Count -ge 1) {
    $LocalTemplateHash.Add("#BmgrBuildCfgs#", ($LocalBmgrBuild -join " || \`n    "))
    $LocalTemplateHash.Add("#BldrBuildCfgs#", ($LocalBldrBuild -join " || \`n    "))
  }
  else {
    $LocalTemplateHash.Add("#BmgrBuildCfgs#","0")
    $LocalTemplateHash.Add("#BldrBuildCfgs#","0")
  }

  ExpandTemplate -in $in -out $out -rep $LocalTemplateHash

  # no special treatment for release builds in MMP2 context.
}

function AddToSection($in,$sections,$sectionname,$rep){
  if (!$sections.ContainsKey($sectionname)){    
    $obj = New-Object PSObject    
    $obj | Add-Member "Items" @{}
    $sections.Add($sectionname,$obj)    
  }

  $item = (ExpandString -in $in -rep $rep)
  $items = $item -split "`n"

  foreach ($i in $items) {
    if ($i -match "item:") {
      $sections[$sectionname].Items.Add($i,$i)
    }
  }
}

function GenerateGlobalSelectors($data){
  
  foreach ($k in $FeatureHash.Keys.GetEnumerator()) {
    $name = $FeatureHash[$k].name

    foreach ($rs in $FeatureHash[$k].relations) {
      if ($rs.class -eq "ps:children") {
        foreach ($r in $rs.relation) {
          switch ($r.type) {
            "ps:alternative" { 
                if ($MicGlobalSel.ContainsKey($k)) {                  
                  $out = "def:global:"+$name+" = "
                  $first = $true
                  foreach ($t in $r.target) { 
                    $childid = ($t.'#text' -replace "\./","")                  
                    if (!$first) { $out += ","}
                    $out += $name+"_"+(GetChildName($t.'#text'))
                    $first = $false
                    foreach ($bv in $BVHash.Values) {
                      if ($bv.Features.ContainsKey($childid)){
                        $item = $name+" = "+$name+"_"+(GetChildName($t.'#text'))
                        #Add Definition to BVs
                        $bv.MicVariants.Add($item,$item)
                      }
                    }
                  }
                  $out += "`n"
                  #Add Declaration
                  $data.Add($out,$out)                  
                }
                break
               }
            "ps:optional" {
                 foreach ($t in $r.target) {                   
                   $childid = ($t.'#text' -replace "\./","")                                     
                   if ($MicGlobalSel.ContainsKey($childid)) {
                     $out = "def:global:"+(GetChildName($t.'#text'))+" = "+(GetChildName($t.'#text'))+"_ON,"+(GetChildName($t.'#text'))+"_OFF`n"
                     #Add Declaration
                     $data.Add($out,$out)

                     foreach ($bv in $BVHash.Values) {
                      if ($bv.Features.ContainsKey($childid)){
                        $item = (GetChildName($t.'#text'))+" = "+(GetChildName($t.'#text'))+"_ON"                      
                      } else {
                        $item = (GetChildName($t.'#text'))+" = "+(GetChildName($t.'#text'))+"_OFF"                      
                      }
                      #Add Definition to BVs
                      $bv.MicVariants.Add($item,$item)
                    }
                   }                                      
                 }
                 break
               }
          }
        }
      }
    }
  }
}

function GenerateMicFile ($prop,$file,$globalselectors){
  $out = "; This file is automatically generated by the VariantGenerator.ps1 from pure::variants feature models`n"
  $out += "; DO NOT EDIT THIS FILE MANUALLY ! > please contact your SW architect !`n"

  if (($globalselectors) -and ($MicGlobalSel.Count -gt 0)) {
    $globaldeclarations = @{}
    GenerateGlobalSelectors -data $globaldeclarations

    $out += "[settings]`n"
    foreach ($text in $globaldeclarations.Values | Sort-Object){
      $out += $text
    }
    $out += "`n"
  }

  $commons = @{}
  #simple compare the first BV list against all others to determine the common elements
  foreach ($item in ($BVHash.Values.GetEnumerator() | Select-Object -First 1).$prop.Keys ){
    $common = $true
    foreach ($bv in $BVHash.Values.GetEnumerator()){
      if (!$bv.$prop.ContainsKey($item)) {
        $common = $false
      }
    }
    if ($common) {
      $commons.Add($item,$item)
    }
  }

  #generate the common elements
  $out += "[common]`n"
  foreach($item in $commons.Keys | Sort-Object){
    if ($item -match "^(.*)(;.*)$") {
      $out += $Matches[2]+"`n"
      $out += $Matches[1]+"`n"
    } else {
      $out += $item+"`n"
    }
  }

  #generate all other sections  
  foreach ($bv in $BVHash.Values.GetEnumerator() | Sort-Object -Property "ConfigurationName"){
    $out += "`n[conf:"+$bv.ConfigurationName+"]`n"
    foreach ($item in $bv.$prop.Keys | Sort-Object) {
      if (!$commons.ContainsKey($item)){
        if ($item -match "^(.*)(;.*)$") {
          $out += $Matches[2]+"`n"
          $out += $Matches[1]+"`n"
        } else {
          $out += $item+"`n"
        }   
      }
    }
  }

  WriteFile -file $file -content $out  
}

function FillMicData($data,$prop){
  foreach ($d in $data.Keys){
    foreach ($bv in $BVHash.Values.GetEnumerator()){
      if ($bv.Features.ContainsKey($d)){
        $item = (ExpandString -in $data[$d] -rep $bv.BVReplace)
        $items = $item -split "`n"

        foreach ($i in $items) {
          if ($i -match "item:") {
            $bv.$prop.Add($i,$i)
          }
        }
      }
    }
  }
}

function GenerateMicFiles ($output) {

  FillMicData -data $MicIncludeHash -prop "MICVariants"
  FillMicData -data $MicIgnoreHash -prop "MICIgnores"

  GenerateMicFile -prop "MICVariants" -file ($output + "\_metadata\mic\variants.mic") -globalselectors $true
  GenerateMicFile -prop "MICIgnores" -file ($output + "\_metadata\mic\overrule.mic") -globalselectors $false
}

function GenerateLoadrule ($output, $template) {
  $in = $template+"\loadrule.tpl"
  $out = $output+"\rbl\"+$GlobalTemplateHash["#prod#"]+"\"+$GlobalTemplateHash["#prj#"]+"\project\"+$GlobalTemplateHash["#prod#"]+".loadrule"
  ExpandTemplate -in $in -out $out -localrep $null
}
 
function ImportData ($FeatureModel) {
  
  foreach($f in $FeatureModel.consulmodel.elements.element.GetEnumerator()) 
  {
    $FeatureHash.Add($f.id,$f)
    foreach ($a in $f.properties.property.GetEnumerator()){
      $AttributeHash.Add($a.id,$a.name)

      switch ($a.name) {        
       "mic_ignore"          { $MicIgnoreHash.Add($f.id,$a.constant.'#text') ;break}
       "mic_include"         { $MicIncludeHash.Add($f.id,$a.constant.'#text') ;break}
       "mic_global_selector" { if ($a.constant.'#text' -eq "true") { $MicGlobalSel.Add($f.id,$a.constant.'#text')}; break}
       "mic_local_selector"  { if ($a.constant.'#text' -eq "true") { $MicLocalSel.Add($f.id,$a.constant.'#text')}; break}
       "nvm_data"            { $NVMDataHash.Add($f.id,$a.constant.'#text'); break}
       "nvm_descr"           { $NVMDescrHash.Add($f.id,$a.constant.'#text'); break}
       "nvm_usage"           { $NVMUsageHash.Add($f.id,$a.constant.'#text'); break}
       "nvm_data_bitfield"   { $NVMDataFieldHash.Add($f.id,$a.constant.'#text'); break;}
      }
    }      
  }

  foreach ($bv in $cfg.BuildVariantConfig.BuildVariants.BuildVariant.GetEnumerator()) {
    $content = new-object psobject
    [xml]$content = Get-Content $bv.'#text'
    $BuildVariants.Add($bv.'#text',$content)
  }
}

function CheckBVForCommonFeature($id) {
  $common = $true
  foreach ($bv in $BVHash.Values.GetEnumerator()){
    if (!$bv.Features.ContainsKey($id)){
      $common = $false
    }
  }   
  return $common
}

function CheckBVForCommonOptOFFFeature($id) {
  $common = $true
  foreach ($bv in $BVHash.Values.GetEnumerator()){
    if ($bv.Features.ContainsKey($id)){
      $common = $false
    }
  }   
  return $common
}

function GenerateGlobalConfigurationHeader ($bv,$outpath,$commons) {
  $out =  ""

  $DH = @{}
  foreach ($k in $FeatureHash.Keys.GetEnumerator()) {
    $name = $FeatureHash[$k].name

    foreach ($rs in $FeatureHash[$k].relations) {
      if ($rs.class -eq "ps:children") {
        foreach ($r in $rs.relation) {
          switch ($r.type) {
            "ps:alternative" { 
                 foreach ($t in $r.target) {
                   $childname = (GetChildName($t.'#text'))
                   $childid = ($t.'#text' -replace "\./","")                             
                   if ($bv.Features.containsKey($childid)) {
                     if (CheckBVForCommonFeature -id $childid) {
                       if (!$commons.ContainsKey($name)){ $commons.Add($name,"#define RBFS_"+$name+"   RBFS_"+$name+"_"+$childname+"`n") }
                     } else { 
                       $DH.Add($name,"#define RBFS_"+$name+"   RBFS_"+$name+"_"+$childname+"`n")
                     }
                   }
                 }
                 break
               }
            "ps:optional" {
                 foreach ($t in $r.target) {
                   $childname = (GetChildName($t.'#text'))
                   $childid = ($t.'#text' -replace "\./","")
                          
                   if ($bv.Features.containsKey($childid)){
                     if (!($FeatureHash[$childid].relations.class -contains "ps:children")) {
                       if (CheckBVForCommonFeature -id $childid) {
                         if (!$commons.ContainsKey($childname)){ $commons.Add($childname,"#define RBFS_"+$childname+"   RBFS_"+$childname+"_ON`n") }
                       } else {
                         $DH.Add($childname,"#define RBFS_"+$childname+"   RBFS_"+$childname+"_ON`n")
                       }
                     }
                   } else {
                     if (!($FeatureHash[$childid].relations.class -contains "ps:children")) {                     
                       if (CheckBVForCommonOptOFFFeature -id $childid) {
                         if (!$commons.ContainsKey($childname)){ $commons.Add($childname,"#define RBFS_"+$childname+"   RBFS_"+$childname+"_OFF`n") }
                       } else {
                         $DH.Add($childname,"#define RBFS_"+$childname+"   RBFS_"+$childname+"_OFF`n")
                       }
                     }
                   }                 
                 }
                 break
               }
            "ps:mandatory" {
                 foreach ($t in $r.target) {
                   $childname = (GetChildName($t.'#text'))
                   $childid = ($t.'#text' -replace "\./","")

                   #mandatories are currently only generated as a test, if it brings advantages for future restructurings, as code can check for dedicated features, rather than the variable "top"-feature
                   #they are only added, if there are no further children       
                   if ($bv.Features.containsKey($childid)){
                     if (!($FeatureHash[$childid].relations.class -contains "ps:children")) {
                       if (CheckBVForCommonFeature -id $childid) {
                         if (!$commons.ContainsKey($childname)){ $commons.Add($childname,"#define RBFS_"+$childname+"   RBFS_"+$childname+"_ON`n") }
                       } else {
                         $DH.Add($childname,"#define RBFS_"+$childname+"   RBFS_"+$childname+"_ON`n")
                       }
                     }
                   } else {
                     if (!($FeatureHash[$childid].relations.class -contains "ps:children")) {                     
                       if (CheckBVForCommonOptOFFFeature -id $childid) {
                         if (!$commons.ContainsKey($childname)){ $commons.Add($childname,"#define RBFS_"+$childname+"   RBFS_"+$childname+"_OFF`n") }
                       } else {
                         $DH.Add($childname,"#define RBFS_"+$childname+"   RBFS_"+$childname+"_OFF`n")
                      }
                     }
                   }               
                 }
                 break
               }
          }
        }
      }
    }
  }

  foreach ($o in $DH.Keys.GetEnumerator() | Sort-Object) {
    $out += "  "+$DH[$o]
  }

  return $out
}

function GetChildName($ref){
  $ref = $ref -replace "\./",""
  return $FeatureHash[$ref].name
}

function GenerateGlobalSwitchSettingHeader($outpath) {
  $out =  "/// @file`n"
  $out += "/// @copyright (C) 2022 Robert Bosch GmbH.`n"
  $out += "/// The reproduction, distribution and utilization of this file as well as the`n"
  $out += "/// communication of its contents to others without express authorization is`n"
  $out += "/// prohibited. Offenders will be held liable for the payment of damages. All rights`n"
  $out += "/// reserved in the event of the grant of a patent, utility model or design. `n"
  $out += "#ifndef RB_PRJ_GLOBALSWITCHSETTINGS_H__`n"
  $out += "#define RB_PRJ_GLOBALSWITCHSETTINGS_H__`n"
  $out += "/**`n"
  $out += "    This file is automatically generated by the VariantGenerator.ps1 from pure::variants feature models`n"
  $out += "    DO NOT EDIT THIS FILE MANUALLY ! > please contact your SW architect !`n"
  $out += "*/`n`n`n"
  $out += "#define RBFS_BuildConfigType_BMGR 1`n"
  $out += "#define RBFS_BuildConfigType_RBBLDR 2`n"
  $out += "#define RBFS_BuildConfigType_APPLICATION 3`n`n"
  
  $SSH = @{}

  foreach ($k in $FeatureHash.Keys.GetEnumerator()) {
    $name = $FeatureHash[$k].name

    foreach ($rs in $FeatureHash[$k].relations) {
      if ($rs.class -eq "ps:children") {
        foreach ($r in $rs.relation) {
          $count = 1
          switch ($r.type) {
            "ps:alternative" { 
                 foreach ($t in $r.target) {
                   if (!($SSH.ContainsKey($name))) {
                     $SSH.Add($name,"#define RBFS_"+$name+"_"+(GetChildName($t.'#text'))+" $count`n")                     
                   } else {
                     $SSH[$name] += "#define RBFS_"+$name+"_"+(GetChildName($t.'#text'))+" $count`n"
                   }
                   $count++;
                 }
                 break
               }
            "ps:optional" {
                 foreach ($t in $r.target) {
                   $childid = ($t.'#text' -replace "\./","")
                   if (!($FeatureHash[$childid].relations.class -contains "ps:children")) {
                     $SSH.Add((GetChildName($t.'#text')),"#define RBFS_"+(GetChildName($t.'#text'))+"_ON 1`n#define RBFS_"+(GetChildName($t.'#text'))+"_OFF 2`n")
                   }
                 }
                 break
               }
            #mandatories are currently only generated as a test, if it brings advantages for future restructurings, as code can check for dedicated features, rather than the variable "top"-feature
            #they are only added, if there are no further children
            "ps:mandatory" {                 
                 foreach ($t in $r.target) { 
                   $childid = ($t.'#text' -replace "\./","")
                   if (!($FeatureHash[$childid].relations.class -contains "ps:children")) {
                     $SSH.Add((GetChildName($t.'#text')),"#define RBFS_"+(GetChildName($t.'#text'))+"_ON 1`n#define RBFS_"+(GetChildName($t.'#text'))+"_OFF 2`n")
                   }
                 }
                 break
               }
          }
        }
      }
    }
  }

  foreach ($o in $SSH.Keys.GetEnumerator() | Sort-Object) {
    $out += $SSH[$o]
    $out += "`n"
  }

  $outfile = $outpath + "RB_Prj_GlobalSwitchSettings.h"
  $out += "`n#endif /* End of multiple include protection */`n"
  WriteFile -file $outfile -content $out
}

function GenerateNVMDataJson($bv){


  $nvmdata=@{}
  $nvmdesc=@{}
  $nvmusage=@{}


  foreach ($nvm in $NVMDataHash.GetEnumerator()){
    if ($bv.Features.ContainsKey($nvm.Key)){

      
      if ($bv.NVMData.ContainsKey($nvm.key)){
        # write value from .vdm
        $entry = $bv.NVMData[$nvm.key]
      } else {
        # write default value from .xfm
        $entry = $nvm.Value
      }
      foreach ($e in ($entry -split "\n")){
        if ($e.length -gt 0){
	  $in = ($e -split ":",2)
          $nvmdata.Add($in[0],$in[1])
        }
      }
    }
  }

  foreach ($nvm in $NVMDataFieldHash.GetEnumerator()){
    if ($bv.Features.ContainsKey($nvm.Key)){
      
      
      if ($bv.NVMDataField.ContainsKey($nvm.key)){
        # write value from .vdm
        $entry = $bv.NVMDataField[$nvm.key]
      } else {
        # write default value from .xfm
        $entry = $nvm.Value
      }
      foreach ($e in ($entry -split "\n")){
        if ($e.length -gt 0){
	      $in = ($e -split ":",2)
          if ($nvmdata.ContainsKey($in[0])){
            $NewElements = ((($in[1] -replace "\[","") -replace "\]","") -replace " ","") -split(",")
            $ExistingElements = ((($nvmdata[$in[0]] -replace "\[","") -replace "\]","") -replace " ","") -split(",")
            $NewData = @()
            for ($i=0; $i -lt $NewElements.count; $i++){
              $NewData += ( [string]::Format("0x{0:X2}",(([Int32]$NewElements[$i]) -bor ([Int32]$ExistingElements[$i]))) )
            }
            $nvmdata[$in[0]] = ("["+($NewData -join ",")+"]")
          }
          else
          {
            $nvmdata.Add($in[0],$in[1])
          }
        }
      }
    }
  }

  foreach ($nvm in $NVMDescrHash.GetEnumerator()){
    if ($bv.Features.ContainsKey($nvm.Key)){

      
      if ($bv.NVMDescr.ContainsKey($nvm.key)){
        # write value from .vdm
        $entry = $bv.NVMDescr[$nvm.key]
      } else {
        # write default value from .xfm
        $entry = $nvm.Value
      }
      foreach ($e in ($entry -split "\n")){
        if ($e.length -gt 0){
          $in = ($e -split ":",2)
          $nvmdesc.Add($in[0],$in[1])
        }
      }
    }
  }

  foreach ($nvm in $NVMUsageHash.GetEnumerator()){
    if ($bv.Features.ContainsKey($nvm.Key)){

      
      if ($bv.NVMUsage.ContainsKey($nvm.key)){
        # write value from .vdm
        $entry = $bv.NVMUsage[$nvm.key]
      } else {
        # write default value from .xfm
        $entry = $nvm.Value
      }
      foreach ($e in ($entry -split "\n")){
        if ($e.length -gt 0){
          $in = ($e -split ":",2)
          $nvmusage.Add($in[0],$in[1])
        }
      }
    }
  }


  $nvm = New-Object PSObject
  $nvm | Add-Member NoteProperty "data" $nvmdata
  $nvm | Add-Member NoteProperty "descr" $nvmdesc
  $nvm | Add-Member NoteProperty "usage" $nvmusage

  return ($nvm | ConvertTo-Json -Depth 15)
}

function GenerateNVMDataFiles ($output) {

  $outpath = $output+"\NVMData\cfg\"
  
  #Remove all the exisiting files inside the folder
  Remove-Item -Path $outpath\*.*

  foreach ($bv in $BVHash.Values.GetEnumerator() | Sort-Object -Property ConfigurationName){
    $out = GenerateNVMDataJson -bv $bv
    $outfile = $outpath + $bv.ConfigurationName+".json"
    WriteFile -file $outfile -content $out

    if( $bv.BLDRConfigurationName ) {
      $outfile = $outpath + $bv.BLDRConfigurationName+".json"
      WriteFile -file $outfile -content $out
    }
    if( $bv.BMGRConfigurationName ) {
      $outfile = $outpath + $bv.BMGRConfigurationName+".json"
      WriteFile -file $outfile -content $out
    }
  }
}

function GenerateGlobalHeader ($output) {

  $commons = @{}

  $out =  "/// @file`n"
  $out += "/// @copyright (C) 2022 Robert Bosch GmbH.`n"
  $out += "/// The reproduction, distribution and utilization of this file as well as the`n"
  $out += "/// communication of its contents to others without express authorization is`n"
  $out += "/// prohibited. Offenders will be held liable for the payment of damages. All rights`n"
  $out += "/// reserved in the event of the grant of a patent, utility model or design. `n"
  $out += "#ifndef RB_PRJ_GLOBALSETTINGS_H__`n"
  $out += "#define RB_PRJ_GLOBALSETTINGS_H__`n"
  $out += "/**`n"
  $out += "    This file is automatically generated by the VariantGenerator.ps1 from pure::variants feature models`n"
  $out += "    DO NOT EDIT THIS FILE MANUALLY ! > please contact your SW architect !`n"
  $out += "*/`n`n`n"
  $out += "#include `"Cfg_MTC_ConfigurationDefines.cfg`"`n"
  $out += "#include `"RB_Prj_GlobalSwitchSettings.h`"`n`n"

  $outpath = $output+"\rbl\"+$GlobalTemplateHash["#prod#"]+"\"+$GlobalTemplateHash["#prj#"]+"\cswpr\cfg\"

  $LocalBmgrBuild = @()
  $LocalBldrBuild = @()
  foreach ($bv in $BVHash.Values.GetEnumerator()) {
    if($bv.BMGRConfigurationName) {
      $LocalBmgrBuild += "(RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_" + $bv.BMGRConfigurationName + ")"
    }
    if($bv.BLDRConfigurationName) {
      $LocalBldrBuild += "(RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_" + $bv.BLDRConfigurationName + ")"
    }
  }
  if($LocalBmgrBuild.Count -ge 1) {
    $out += "#if ("
    $out += ($LocalBmgrBuild -join " || \`n    ")
    $out += ")`n"
    $out += "  #define RBFS_BuildConfigType	RBFS_BuildConfigType_BMGR`n"
    $out += "#elif ("
    $out += ($LocalBldrBuild -join " || \`n    ")
    $out += ")`n"
    $out += "  #define RBFS_BuildConfigType	RBFS_BuildConfigType_RBBLDR`n"
    $out += "#else`n"
    $out += "  #define RBFS_BuildConfigType	RBFS_BuildConfigType_APPLICATION`n"
    $out += "#endif`n`n`n"
  }
  else {
    $out += "#define RBFS_BuildConfigType	RBFS_BuildConfigType_APPLICATION`n`n`n"
  }

  foreach ($bv in $BVHash.Values.GetEnumerator() | Sort-Object -Property ConfigurationName){
    if( $bv.BMGRConfigurationName -or $bv.BLDRConfigurationName ) {
      $out += "#if ((RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_"+$bv.ConfigurationName+") || \`n"
      if( $bv.BMGRConfigurationName ) {
        $out += "    (RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_"+$bv.BMGRConfigurationName+")"
        if( $bv.BLDRConfigurationName ) {
          $out += " || \`n"
        }
        else {
          $out += ")`n"
        }
      }
      if( $bv.BLDRConfigurationName ) {
        $out += "    (RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_"+$bv.BLDRConfigurationName+"))`n"
      }
    }
    else {
      $out += "#if (RBFS_BUILDCONFIG == RBFS_BUILDCONFIG_"+$bv.ConfigurationName+")`n"  
    }
    $out += GenerateGlobalConfigurationHeader -bv $bv -outpath $outpath -common $commons
    $out += "#endif`n`n`n"    
  }

  $out += "/* COMMON DEFINES (for all defined build variants) */`n"
  foreach ($o in $commons.Keys.GetEnumerator() | Sort-Object) {
    $out += $commons[$o]
  }

  GenerateGlobalSwitchSettingHeader -outpath $outpath

  $outfile = $outpath + "RB_Prj_GlobalSettings.h"
  $out += "`n#endif /* End of multiple include protection */`n"
  WriteFile -file $outfile -content $out
}

function GenerateMTCStartScripts($output,$template){
	
  #Remove all the exisiting files inside the folder
  Remove-Item -Path $output\*.*

  foreach ($bv in $BVHash.Values.GetEnumerator()) {
      $LocalTemplateHash = @{}
      $LocalTemplateHash.Add("#incremental#","-IncrementalBuild")
      $LocalTemplateHash.Add("#type#","Incremental")
      $LocalTemplateHash.Add("#configname#",$bv.ConfigurationName)
      $in  = $template+"\Start_MTC.bat_tpl"
      $out = $output+"\Start_"+$LocalTemplateHash["#configname#"]+"_Incremental.bat"
      ExpandTemplate -in $in -out $out -rep $LocalTemplateHash

      $LocalTemplateHash.Clear()
      $LocalTemplateHash.Add("#incremental#","-GenerateMakeFile")
      $LocalTemplateHash.Add("#type#","Rebuild")
      $LocalTemplateHash.Add("#configname#",$bv.ConfigurationName)
      $in  = $template+"\Start_MTC.bat_tpl"
      $out = $output+"\Start_"+$LocalTemplateHash["#configname#"]+"_Rebuild.bat"
      ExpandTemplate -in $in -out $out -rep $LocalTemplateHash
  }

}


function Main(){
  Get-Date

  [xml]$cfg = Get-Content $configfile

  $OutputFolder = $cfg.BuildVariantConfig.Settings.OutputFolder
  $TemplateFolder = $cfg.BuildVariantConfig.Settings.TemplateFolder

  [xml]$FeatureModel = Get-Content $cfg.BuildVariantConfig.Settings.FeatureModel


  ImportData -FeatureModel $FeatureModel

  GenerateBVConfigs

  GenerateCfgConfigurationsXml -file ($OutputFolder+"\Cfg_Configurations.xml")

  SetupGlobalTemplateHash

  GenerateBcfgFiles -output $OutputFolder -template $TemplateFolder

  GenerateMicFiles -output $OutputFolder 

  GenerateLoadrule -output $OutputFolder -template $TemplateFolder

  GenerateGlobalHeader -output $OutputFolder

  GenerateMTCStartScripts -output ($OutputFolder+"\Start_Batches") -template $TemplateFolder

  GenerateNVMDataFiles -output $OutputFolder

  Get-Date
}

Main