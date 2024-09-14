echo "Please ensure Docker is installed before continuing."
read -p "Press Enter to continue or CTRL-C to exit."
if [ -d "tools/1.2.5n" ]; then echo "1.2.5n exists" && export one_two_five_n_exist=1; fi
if [ -d "tools/1.3.2" ]; then echo "1.3.2 exists" && export one_three_two_exist=1; fi
if [ -d "tools/1.3.2r" ]; then echo "1.3.2r exists" && export one_three_two_r_exist=1; fi
if [ "$one_two_five_n_exist" -eq 1 ] && [ "$one_three_two_exist" -eq 1 ] && [ "$one_three_two_r_exist" -eq 1 ]; then docker build -t ac-decomp . && echo "Docker image setup is now complete. You may proceed with the instructions." && exit; fi


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
    rm -r compilers_temp compilers_latest.zip
    exit 1
fi
if [ ! -d "tools/1.2.5n" ]; then mv compilers_temp/GC/1.2.5n/ tools/; fi
if [ ! -d "tools/1.3.2" ]; then mv compilers_temp/GC/1.3.2/ tools/; fi
if [ ! -d "tools/1.3.2r" ]; then mv compilers_temp/GC/1.3.2r/ tools/; fi
rm -r compilers_temp compilers_latest.zip
docker build -t ac-decomp .
echo "Docker image setup is now complete. You may proceed with the instructions."
