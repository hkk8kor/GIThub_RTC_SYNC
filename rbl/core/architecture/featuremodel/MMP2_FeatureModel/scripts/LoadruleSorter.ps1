param(
    [Parameter()]
    [ValidateNotNullOrEmpty()]
    #[string]$loadrule_in = $(throw "-configfile is required.")
    [string]$loadrule_in = "..\input\templates\loadrule.tpl"
)

function Format-XML ($xml, $indent=2) { 
    $StringWriter = New-Object System.IO.StringWriter 
    $XmlWriter = New-Object System.XMl.XmlTextWriter $StringWriter 
    $xmlWriter.Formatting = “indented” 
    $xmlWriter.Indentation = $Indent 
    $xml.WriteContentTo($XmlWriter) 
    $XmlWriter.Flush() 
    $StringWriter.Flush() 
    Write-Output $StringWriter.ToString() 
}

function WriteFile ($file,$content) {
  $outpath = $file -replace ($file -replace ".*\\",""),""
  if (!(Test-Path $outpath)) {
      New-Item -Path $outpath -ItemType Directory -Force > $null
  }

  $content | Out-File -FilePath $file -Encoding ascii -Force
}

function Main(){
  Get-Date

  [xml]$source = Get-Content -Path $loadrule_in
  
  $sorted = $source.sourceControlLoadRule.parentLoadRule | Sort-Object {$_.component.name}
  $lastChild = $sorted[-1]
  $sorted[0..($sorted.Length-2)] | Foreach {$source.sourceControlLoadRule.InsertBefore($_,$lastChild)} > $null

  $sorted = $source.sourceControlLoadRule.itemLoadRule | Sort-Object {$_.component.name}
  $lastChild = $sorted[-1]
  $sorted[0..($sorted.Length-2)] | Foreach {$source.sourceControlLoadRule.InsertBefore($_,$lastChild)} > $null

  WriteFile -file "C:\temp\loadrule.tpl" -content (Format-XML $source)
  Get-Date
}

Main

