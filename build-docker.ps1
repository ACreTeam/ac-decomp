docker build -t ac-decomp .
curl -O https://files.decomp.dev/compilers_latest.zip
Expand-Archive -LiteralPath compilers_latest.zip -DestinationPath compilers_temp
move compilers_temp\GC\1.2.5n\ tools\ && mv compilers_temp\GC\1.3.2\ tools\ && mv compilers_temp\GC\1.3.2r\ tools\
Remove-Item compilers_latest.zip
Remove-Item -Path compilers_temp\ -Recurse
echo "Docker image setup is now complete. You may proceed with the instructions."
