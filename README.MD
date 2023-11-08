# Animal Crossing Decompilation [![Discord Channel][discord-badge]][discord]
[discord]: https://discord.gg/hKx3FJJgrV
[discord-badge]: https://img.shields.io/discord/727908905392275526?color=%237289DA&logo=discord&logoColor=%23FFFFFF

Decompilation in progress of Animal Crossing (GAFE01)

A decompilation of the original N64 version of the game is being worked on [here](https://github.com/zeldaret/af).
## Cloning

Use `--recursive` when cloning to have ppcdis in the repository. 

## Building

> ℹ️ When using Windows, it's recommended to use WSL.

### Docker

1. Dump a copy of the game and extract **main.dol** and **foresta.rel.szs**.
2. Decompress **foresta.rel.szs** with yaz0 found in *tools/* (`yaz0 -d foresta.rel.szs foresta.rel`).
3. Place **main.dol** and **foresta.rel** in *dump/*.
4. Download the [CodeWarrior 1.3.2 and 1.2.5n compilers](https://files.decomp.dev/compilers_20230715.zip) and extract them to *tools/1.3.2/* and *tools/1.2.5n/*, respectively.
5. Download the [CodeWarrior 1.3.2r compiler](https://mega.nz/file/WuBFTCLT#TmB5R4-1mEFkk4G1Vjn9_cHXRD9wOIH9CtOLaVSWEas) and extract it to *tools/1.3.2r/*.
6. Install Docker.
7. Build the Docker image (`docker build -t ac-decomp .`).
8. Run configure.py (`docker run --rm -v ${PWD}:/ac-decomp ac-decomp python3 configure.py`).
9. Run ninja (`docker run --rm -v ${PWD}:/ac-decomp ac-decomp ninja`).

### Build manually

> ℹ️ When building manually from a work directory originally used for Docker, you will need to run `sudo ninja -t clean` for the build to execute properly.

1. Dump a copy of the game and extract **main.dol** and **foresta.rel.szs**.
2. Decompress **foresta.rel.szs** with yaz0 found in *tools/* (`yaz0 -d foresta.rel.szs foresta.rel`).
3. Place **main.dol** and **foresta.rel** in *dump/*.
4. Download the [CodeWarrior 1.3.2 and 1.2.5n compilers](https://files.decomp.dev/compilers_20230715.zip) and extract them to *tools/1.3.2/* and *tools/1.2.5n/*, respectively.
5. Download the [CodeWarrior 1.3.2r compiler](https://mega.nz/file/WuBFTCLT#TmB5R4-1mEFkk4G1Vjn9_cHXRD9wOIH9CtOLaVSWEas) and extract it to *tools/1.3.2r/*.
6. Install Python, pip, and [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages#package-managers) using your package manager of choice.
7. Install Python modules from requirements.txt (`pip install -r requirements.txt`).
8. Install [wibo](https://github.com/decompals/wibo)
    - Wibo is a lightweight Wine replacement that's tailor-made for use with decomp projects. Regular Wine can be used if preferred, but for the purposes of this guide, these instructions will use wibo.
    - Download [the latest GitHub release](https://github.com/decompals/wibo/releases/latest) and run `install ./wibo /usr/bin` to install it to your system.
9. Install devkitPPC.
    - To get devkitPPC, you'll need [devkitPro Pacman](https://devkitpro.org/wiki/devkitPro_pacman#Installing_devkitPro_Pacman).
        - Run `dkp-pacman -S devkitPPC` once dkp-pacman is installed to install devkitPPC.
        - Set the `DEVKITPPC` environment variable to */opt/devkitpro/devkitPPC*.
10. Set the `N64_SDK` environment variable to the path of your libultra or equivalent headers. If you need headers, you can use the ones from [ultralib](https://github.com/decompals/ultralib).
    - Headers should be located at `$N64_SDK/ultra/usr/include`.
    - You may need to modify `Gpopmtx`'s `param` member to be `unsigned int` in **gbi.h**.
11. Run `python3 configure.py`.
12. Run `ninja`.

## Credits

- jamchamb, Cuyler36, NWPlayer123 and fraser125 for past documentation of Animal Crossing.
- SeekyCt for [ppcdis](https://github.com/SeekyCt/ppcdis/) and helping setting up the project.
- msg for helping with *tools/map.py*.
