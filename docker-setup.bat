@echo off
echo "Please ensure Docker Desktop is running before continuing."
pause
:: Check if the compilers are present. If any one compiler doesn't exist, the download process will be initiated.
IF exist tools\1.2.5n\ ( echo 1.2.5n exists ) ELSE ( goto compilers )
IF exist tools\1.3.2\ ( echo 1.3.2 exists ) ELSE ( goto compilers )
IF exist tools\1.3.2r\ ( echo 1.3.2r exists ) ELSE ( goto compilers )
goto buildimage

:buildimage
docker build -t ac-decomp .
echo "Docker image setup is now complete. You may proceed with the instructions."
pause
exit

:compilers
curl -O https://files.decomp.dev/compilers_latest.zip
mkdir compilers_temp
powershell -command "Expand-Archive -LiteralPath 'compilers_latest.zip' -DestinationPath compilers_temp"
:: Only copy compilers that the user doesn't already have.
IF exist tools\1.2.5n\ ( echo 1.2.5n already exists, skipping copy ) ELSE ( xcopy compilers_temp\GC\1.2.5n\ tools\1.2.5n\ /E /I )
IF exist tools\1.3.2\ ( echo 1.3.2 already exists, skipping copy ) ELSE ( xcopy compilers_temp\GC\1.3.2\ tools\1.3.2\ /E /I )
IF exist tools\1.3.2r\ ( echo 1.3.2r already exists, skipping copy ) ELSE ( xcopy compilers_temp\GC\1.3.2r\ tools\1.3.2r\ /E /I )
del compilers_latest.zip
rmdir /S /Q compilers_temp\
goto buildimage
