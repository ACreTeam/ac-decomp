# Animal Crossing Decompilation [![Discord Channel][discord-badge]][discord] ![rel progress] ![dol progress]
[discord]: https://discord.gg/hKx3FJJgrV
[discord-badge]: https://img.shields.io/discord/727908905392275526?color=%237289DA&logo=discord&logoColor=%23FFFFFF
[rel progress]: https://img.shields.io/endpoint?label=rel&url=https%3A%2F%2Fprogress.decomp.club%2Fdata%2Fanimalcrossing%2Fus%2Frel%2F%3Fmode%3Dshield%26measure%3Dcode
[dol progress]: https://img.shields.io/endpoint?label=dol&url=https%3A%2F%2Fprogress.decomp.club%2Fdata%2Fanimalcrossing%2Fus%2Fdol%2F%3Fmode%3Dshield%26measure%3Dcode

Decompilation in progress of Animal Crossing (GAFE01)

A decompilation of the original N64 version of the game is being worked on [here](https://github.com/zeldaret/af).

## Cloning

Use `--recursive` when cloning to have ppcdis in the repository. 

## Building

> ℹ️ On Windows, the build is known to run disproportionately slow when ran natively, so we recommend using WSL.

### Docker

1. [Dump a copy of the game](./docs/extract_game.md) and extract all files.
2. Place **main.dol**, **foresta.rel.szs**, **forest_1st.arc**, and **forest_2nd.arc** in *dump/*.
3. Install Docker.
4. Set up the Docker image. If using MacOS or Linux (including WSL), run `chmod +x docker-setup.sh && ./docker-setup.sh`. If using Windows, run the `docker-setup.bat` file.
5. Run configure.py (`docker run --rm -v ${PWD}:/ac-decomp ac-decomp python3 configure.py`).
6. Run build.py (`docker run --rm -v ${PWD}:/ac-decomp ac-decomp python3 build.py`).

### Build manually

> ℹ️ When building manually from a work directory previously used for Docker, you will need to run `sudo ninja -t clean` for the build to execute properly.

1. [Dump a copy of the game](./docs/extract_game.md) and extract all files.
2. Place **main.dol**, **foresta.rel.szs**, **forest_1st.arc**, and **forest_2nd.arc** in *dump/*.
3. Download the [CodeWarrior 1.3.2, 1.3.2r, and 1.2.5n compilers](https://files.decomp.dev/compilers_latest.zip) and extract them to *tools/1.3.2/*, *tools/1.3.2r/*, and *tools/1.2.5n/*, respectively.
4. Install Python, pip, and [ninja](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages#package-managers) using your package manager of choice.
5. Install Python modules from requirements.txt (`pip install -r requirements.txt`).
6. Install version 0.6.13 of [wibo](https://github.com/decompals/wibo)
    - Wibo is a lightweight Wine replacement that's tailor-made for use with decomp projects. Regular Wine can be used if preferred, but for the purposes of this guide, these instructions will use wibo.
    - Download the [GitHub release of version 0.6.13](https://github.com/decompals/wibo/releases/tag/0.6.13) and run `install ./wibo /usr/bin` to install it to your system.
7. Install devkitPPC.
    - To get devkitPPC, you'll need [devkitPro Pacman](https://devkitpro.org/wiki/devkitPro_pacman#Installing_devkitPro_Pacman).
        - Run `dkp-pacman -S devkitPPC` once dkp-pacman is installed to install devkitPPC.
        - Set the `DEVKITPPC` environment variable to */opt/devkitpro/devkitPPC*.
8. Set the `N64_SDK` environment variable to the path of your libultra or equivalent headers. If you need headers, you can use the ones from [ultralib](https://github.com/decompals/ultralib).
    - Headers should be located at `$N64_SDK/ultra/usr/include`.
    - You must modify `Gpopmtx`'s `param` member to be `unsigned int` in **gbi.h**.
9. Run `python3 configure.py`.
10. Run `python3 build.py`.

## Quick Guides
- [Dumping Game Files](./docs/extract_game.md)
- [Ghidra Setup](./docs/ghidra_setup.md)
- [Generating Decomp Context](./docs/generating_decomp_context.md)
- [decomp.me Basics](./docs/decomp_me_basics.md)
- [Ghidra Basics](./docs/ghidra_basics.md)
- [m2c Basics](./docs/m2c_basics.md)
- [Decomp Basics](./docs/decomp_basics.md)

## Credits

- jamchamb, Cuyler36, NWPlayer123 and fraser125 for past documentation of Animal Crossing.
- SeekyCt for [ppcdis](https://github.com/SeekyCt/ppcdis/) and helping setting up the project.
- msg for helping with *tools/map.py*.
