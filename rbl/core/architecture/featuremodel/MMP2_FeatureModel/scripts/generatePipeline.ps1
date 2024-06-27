
$rootPathOfScript = Split-Path -Parent $PSCommandPath

$pipeLineTemplate = Get-Content "$rootPathOfScript/generateJenkinsFileTemplate/pipeline.template" -Raw
$ecuBuildTemplate = Get-Content "$rootPathOfScript/generateJenkinsFileTemplate/ecuBuildVariant.template" -Raw
$WhenAllTemplate = Get-Content "$rootPathOfScript/generateJenkinsFileTemplate/whenAll.template" -Raw
$WhenAnyTemplate = Get-Content "$rootPathOfScript/generateJenkinsFileTemplate/whenAny.template" -Raw
$caplTestingTemplate = Get-Content "$rootPathOfScript/generateJenkinsFileTemplate/caplTesting.template" -Raw
$deliverTemplate = Get-Content "$rootPathOfScript/generateJenkinsFileTemplate/deliver.template" -Raw
$offlineCallTemplate = Get-Content "$rootPathOfScript/generateJenkinsFileTemplate/callOfflineJob.template" -Raw
$SWUTCTTemplate = Get-Content "$rootPathOfScript/generateJenkinsFileTemplate/callSWUTCTJob.template" -Raw


$pullJobExtension = '_pullChanges'


Get-ChildItem -Path "$rootPathOfScript/../input" -Filter "Jenkins*.xml" | %{

    $foundMappingFile = $_
    [xml] $xmlDoc = Get-Content $foundMappingFile.FullName

    $foundMappingFile.Name -match "(.*?)\.xml"  > $null
    $JenkinsFile = "$rootPathOfScript/../output/Jenkins/" + $Matches.1
    

    $generatedBuildSteps = ''
    $generatedCaplTestSteps = ''
    $generatedHpneOfflineTest = ''
    $generatedDeliver = ''
    $generatedOfflineCall = ''
	$generatedSWUTCTCall = ''
    $parameters=''
    $callOfflineJob=''

    $buildVariantHash = @{}
    $buildVariantHash.Clear()
	
	[xml] $xmlTestingConfig = Get-Content ($foundMappingFile.Directory.FullName+ "/" + $xmlDoc.config.testing)

    $xmlDoc.config.mappings.mapping | %{
        $streamNamePattern = $_.streamNamePattern

        [xml] $xmlConfig = Get-Content ($foundMappingFile.Directory.FullName+ "/" + $_.config)

        $xmlConfig.BuildVariantConfig.BuildVariants.BuildVariant.VDM | %{

            $_ -match ".*?([^\\\/]*)\.vdm$" > $null
            $configName = $Matches.1

            if(-not($buildVariantHash.ContainsKey($configName)))
            {
                $buildVariantHash.Add("$configName", {@()}.Invoke())
            }
            $buildVariantHash[$configName].Add($streamNamePattern)
        }
    }

    $xmlDoc.config.deliveries.deliver | %{
        $deliverElement = $_
        $pullJobCall = ''
        $deliverElement.deliverTo.stream  | %{
            $pullJobCall += 'try {build job: "/*%streamName%*//*%streamNamePullExtension%*/", parameters: [[$class: "StringParameterValue", name: "pathJSONFile", value: "${jsonFile}"]], wait: false} catch (Exception e) {}'.Replace("/*%streamName%*/", $_ ).Replace("/*%streamNamePullExtension%*/", $pullJobExtension )
            $pullJobCall += "`r`n"
        }
        
        
        $generatedDeliver  += $deliverTemplate.Replace('/*%deliverStream%*/', $deliverElement.stream).Replace('/*%pullJobCall%*/', $pullJobCall)
    }

    $offlineToolWhenPattern = ''


    $xmlDoc.config.callOfflineTool.stream.usedServices.name | select -Unique | %{
        $parameters += "booleanParam defaultValue: true, description: '', name: 'OfflineTool/*%correctionName%*/'`r`n".replace('/*%correctionName%*/', $_.toLower())
    }

    $replaceForWhen = ''
    $xmlDoc.config.callOfflineTool.stream | %{
        $streamSettings = $_

        $streamSettings.usedServices.name | select -Unique | %{
            $replaceForWhen += "allOf {`r`n"
            $replaceForWhen += "    expression { env.JOB_BASE_NAME ==~ //*%offlineStreamPattern%*//}`r`n".Replace('/*%offlineStreamPattern%*/', $streamSettings.streamNamePattern)
            $replaceForWhen += "    environment name: 'OfflineTool/*%correctionName%*/', value: 'true'`r`n".Replace("/*%correctionName%*/", $_.toLower())
            $replaceForWhen += "`r`n}`r`n"
        }

    }


    $generatedOfflineCall=''

    if($replaceForWhen.Trim() -ne ''){
        $generatedOfflineCall = $offlineCallTemplate.Replace('/*%when%*/',$WhenAnyTemplate.replace('/*%whenExpression%*/', $replaceForWhen))
		
		$offlineToolCall = ''
		$xmlDoc.config.callOfflineTool.stream | %{
		
			$streamSettings = $_
        
			$offlineToolCall += 'if (env.JOB_BASE_NAME ==~ //*%offlineStreamPattern%*//) {try {build job: "${env.JOB_BASE_NAME}_OfflineTool", parameters: [booleanParam(name: "ExecOfflineToolTrimble", value: /*%execTrimble%*/), booleanParam(name: "ExecOfflineToolQX", value: /*%execQX%*/), booleanParam(name: "Evaluation", value: /*%execEval%*/), string(name: "jsonFile", value: "${jsonFile}"), string(name: "personalBuild", value: ""), string(name: "buildRequesterUserId", value: "")], wait: false} catch (Exception e) {}}'
			$offlineToolCall += "`r`n"
			$offlineToolCall = $offlineToolCall.Replace('/*%offlineStreamPattern%*/', $streamSettings.streamNamePattern)
			$offlineToolCall = $offlineToolCall.Replace('/*%execTrimble%*/', ($streamSettings.usedServices.name.ToLower() -eq 'Trimble'.ToLower()).toString().ToLower())
			$offlineToolCall = $offlineToolCall.Replace('/*%execQX%*/', ($streamSettings.usedServices.name.ToLower() -eq 'QX'.ToLower()).toString().ToLower())
			$offlineToolCall = $offlineToolCall.Replace('/*%execEval%*/', $xmlDoc.config.callOfflineTool.evaluate.ToLower())
		
		}

        $generatedOfflineCall = $offlineCallTemplate
        $generatedOfflineCall = $generatedOfflineCall.Replace('/*%offlineJobCall%*/', $offlineToolCall)
        $generatedOfflineCall = $generatedOfflineCall.Replace('/*%when%*/', $WhenAnyTemplate.Replace('/*%whenExpression%*/', $replaceForWhen))
    }



	$WhenSWUTCT = ""
	$SWUTCTJobCall = ""
	[System.Collections.ArrayList] $SWUTCTParameters = @()
	
	$SWUTCTParameters.Add("string(name: 'PathJSONFile', value: jsonFile)") | Out-Null
	$SWUTCTParameters.Add("string(name: 'Stream', value: env.JOB_BASE_NAME)") | Out-Null
	$SWUTCTParameters.Add("string(name: 'BuildNumber', value: env.BUILD_NUMBER)") | Out-Null

    $buildVariantHash.Keys | %{
        $buildVariant = $_
        $replaceForWhen = ""
        $buildVariantHash[$buildVariant] | %{
            $replaceForWhen += ('expression { env.JOB_BASE_NAME ==~  /\*%pattern%*//}' + "`r`n").Replace('\*%pattern%*/', $_)
        }

        if($replaceForWhen -ne ""){
            $replaceForWhen = "anyOf {`r`n" + $replaceForWhen
            $replaceForWhen += "`r`n}`r`n"

         }

        $replaceWhenAllBuild = $WhenAllTemplate.Replace('/*%whenExpression%*/', $replaceForWhen)
        $generatedBuildSteps += $ecuBuildTemplate.replace('/*%buildVariantName%*/', $buildVariant).Replace('/*%when%*/', $replaceWhenAllBuild)
		
		# Add the CAPLTesting Pipeline Code
        $replaceForWhen += "environment name: 'caplTest/*%buildVariantName%*/', value: 'true'`r`n".replace('/*%buildVariantName%*/', $buildVariant)
        $replaceWhenAllCAPL = $WhenAllTemplate.Replace('/*%whenExpression%*/', $replaceForWhen)
        $generatedCaplTestSteps += $caplTestingTemplate.replace('/*%buildVariantName%*/', $buildVariant).Replace('/*%when%*/', $replaceWhenAllCAPL)
		$CAPLTestingSwitch = [System.Convert]::ToBoolean(($xmlTestingConfig.config.Variants.Variant | Where-Object {$_.Name -eq $buildVariant}).CAPLTesting)
		$parameters += "booleanParam defaultValue: $($CAPLTestingSwitch.ToString().ToLower()), description: '', name: 'caplTest$buildVariant'`r`n"
		
		# Add SW-UT/CT Pipeline Code
		$SWUTCTSwitch = [System.Convert]::ToBoolean(($xmlTestingConfig.config.Variants.Variant | Where-Object {$_.Name -eq $buildVariant}).SW_UT_CT)
		$parameters += "booleanParam defaultValue: $($SWUTCTSwitch.ToString().ToLower()), description: '', name: 'SWUTCT$buildVariant'`r`n"
		$WhenSWUTCT += "expression {env.SWUTCT$buildVariant}`n"
		$SWUTCTParameters.Add("booleanParam(name: '$buildVariant', value: env.SWUTCT$buildVariant)") | Out-Null

    }
	
	$SWUTCTJobCall = 'try {build job: "${env.JOB_BASE_NAME}_SW-UT_CT_Delta", parameters: [/*%SWUTCTParameters%*/], wait: false} catch (Exception e) {}'.Replace('/*%SWUTCTParameters%*/', [String]::Join(",", $SWUTCTParameters.ToArray()))
	$generatedSWUTCTCall = $SWUTCTTemplate.Replace('/*%when%*/', $WhenAnyTemplate.Replace('/*%whenExpression%*/', $WhenSWUTCT))
	$generatedSWUTCTCall = $generatedSWUTCTCall.Replace('/*%SWUTCTJobCall%*/', $SWUTCTJobCall)

    if(-not (Test-Path (Split-Path -Parent $JenkinsFile))){
        New-Item -Force (Split-Path -Parent $JenkinsFile) -ItemType Directory
    }

    #patch into the complete template
    $pipeLineText=$pipeLineTemplate.Replace('/*%buildVariant%*/', $generatedBuildSteps)
    $pipeLineText=$pipeLineText.Replace('/*%ecuCaplTests%*/', $generatedCaplTestSteps)
    $pipeLineText=$pipeLineText.Replace('/*%generatedParameters%*/', $parameters)
    $pipeLineText=$pipeLineText.Replace('/*%deliverStep%*/', $generatedDeliver) 
    $pipeLineText=$pipeLineText.Replace('/*%callOfflineJob%*/', $generatedOfflineCall)
	$pipeLineText=$pipeLineText.Replace('/*%callSWUTCTJob%*/', $generatedSWUTCTCall)

    $pipeLineText | Out-File $JenkinsFile -Encoding ascii

}