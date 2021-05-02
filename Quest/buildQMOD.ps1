# Builds a .qmod file for loading with QuestPatcher
$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

$buildScript = "$NDKPath/build/ndk-build"
if (-not ($PSVersionTable.PSEdition -eq "Core")) {
    $buildScript += ".cmd"
}

$ArchiveName = "Skrypt.qmod"
$TempArchiveName = "Skrypt.qmod.zip"

& $buildScript NDK_PROJECT_PATH=$PSScriptRoot APP_BUILD_SCRIPT=$PSScriptRoot/Android.mk NDK_APPLICATION_MK=$PSScriptRoot/Application.mk
Compress-Archive -Path "./libs/arm64-v8a/libskrypt.so", "./libs/arm64-v8a/libbeatsaber-hook_1_3_3.so", "./mod.json", "./thumbnail.jpg" -DestinationPath $TempArchiveName -Force
Move-Item $TempArchiveName $ArchiveName -Force