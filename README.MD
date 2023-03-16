# Animal Crossing Decompilation

Decompilation in progress of Animal Crossing (GAFE01)

## Cloning

Use `--recursive` when cloning to have ppcdis in the repository. 

## Build

**Currently, it has only been tested with [wibo](https://github.com/decompals/wibo) under WSL2, but should build under other platforms and with Wine.**

### Building

- Dump a copy of the game and extract **main.dol** and **foresta.rel.szs**.
- Decompress **foresta.rel.szs** with yaz0 found in *tools/*.
- Place **main.dol** and **foresta.rel** in *dump/*.
- Place CodeWarrior 1.3.2 in *tools/1.3.2/*, 1.2.5 in *tools/1.2.5/* and 1.2.5e in *tools/1.2.5e/*.
- Install DevkitPPC, Ninja and Python:
    - **Only tested with DevkitPPC r41 and Python 3.8.10**, however other versions should work fine.
- Install Python modules from requirements.txt (`pip install -r requirements.txt`)
- Run configure.py
- Run ninja

## Credits

- jamchamb, Cuyler36, NWPlayer123 and fraser125 for past documentation of Animal Crossing.
- SeekyCt for [ppcdis](https://github.com/SeekyCt/ppcdis/) and helping setting up the project.
- msg for helping with *tools/map.py*.
