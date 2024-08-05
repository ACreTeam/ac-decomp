echo "Please ensure Docker is installed before continuing."
read -p "Press Enter to continue or CTRL-C to exit."
if command -v curl &> /dev/null; then
    curl -O https://files.decomp.dev/compilers_latest.zip
elif command -v wget &> /dev/null; then
    wget https://files.decomp.dev/compilers_latest.zip
else
    echo "You do not seem to have curl or wget installed on this system. Please install one or the other to continue."
    exit 0
fi

mkdir compilers_temp
if command -v unzip &> /dev/null; then
    unzip compilers_latest.zip -d compilers_temp
else
    echo "You do not seem to have unzip installed on this system. Please install it to continue."
    rm compilers_latest.zip
    rm -r compilers_temp
    exit 1
fi
mv compilers_temp/GC/1.2.5n/ tools/ && mv compilers_temp/GC/1.3.2/ tools/ && mv compilers_temp/GC/1.3.2r/ tools/
rm -r compilers_temp compilers_latest.zip
docker build -t ac-decomp .
echo "Docker image setup is now complete. You may proceed with the instructions."
