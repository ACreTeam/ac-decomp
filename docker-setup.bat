@echo off
echo "Please ensure Docker Desktop is running before continuing."
pause
curl -O https://files.decomp.dev/compilers_latest.zip
mkdir compilers_temp
tar -xf compilers_latest.zip -C compilers_temp
xcopy compilers_temp\GC\1.2.5n\ tools\1.2.5n\ /E /I
xcopy compilers_temp\GC\1.3.2\ tools\1.3.2\ /E /I
xcopy compilers_temp\GC\1.3.2r\ tools\1.3.2r\ /E /I
del compilers_latest.zip
rmdir /S /Q compilers_temp\
docker build -t ac-decomp .
echo "Docker image setup is now complete. You may proceed with the instructions."
pause
exit
