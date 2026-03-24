# Build Tools

This directory contains Python utilities for the decompilation build system.

## Overview

- **Build configuration generators** — Create Ninja build rules
- **Metadata managers** — Track symbols, file splits, decompilation context
- **Asset converters** — Process textures, audio, archives
- **Integration scripts** — Connect decompilation metadata to build steps

## Structure

```
tools/
├── project.py           # Project metadata & configuration
├── ninja_syntax.py      # Ninja build file generator
├── decompctx.py         # Decompilation context manager
├── arc_tool.py          # Archive/asset extraction
├── texture_tool.py      # Texture format conversion
├── audio/               # Audio processing
├── converters/          # Format converters (Yaz0, BCH, etc.)
├── pyjkernel/           # Python JKernel library
└── download_tool.py     # Compiler/tool downloading
```

## Key Files

### `project.py`
Defines the build project structure:
- Loads `config/GAFE01_00/config.yml`
- Manages object files, sections, and linking
- Generates build metadata for Ninja

Used by: `configure.py`, build system

### `ninja_syntax.py`
Generates Ninja build rules from project metadata:
- Compiler flags, include paths, optimization levels
- Link rules for DOL and REL modules
- Automatic rebuild triggers

Output: `build.ninja`

### `decompctx.py`
Manages decompilation context:
- Downloads SDK headers if needed
- Sets up analysis environment
- Tracks which functions are matched vs. unmatched

### `arc_tool.py`
Extracts archives from the game disc:
- Yaz0-compressed archives
- File system navigation
- Asset extraction

### `converters/`
Format conversion utilities:
- **Yaz0** — Compression format used by GameCube
- **BCH** — Binary container headers
- **Texture formats** — I4, I8, IA4, IA8, RGB565, RGB5A3, RGBA8, CMPR
- **Audio formats** — ADPCM

### `audio/`
Audio processing tools:
- ADPCM decoding utilities (important for Metal port)
- DSP configuration

### `pyjkernel/`
Python implementation of JKernel (Nintendo audio/OS) subsystem library.

## Important Notes

### For Decompilation Contributors
- You shouldn't need to modify these files
- They're automatically used by `./build.sh` and `configure.py`
- If the build breaks, report to maintainers with full error output

### For Metal Port Developers
- These tools support the decompilation build
- Platform builds use CMake instead (in `platform/`)
- However, some converters (texture, audio) may be useful for asset processing

### Modifying Build Tools
- Changes require Python knowledge
- Test modifications before committing
- Run existing builds to ensure compatibility

## Common Operations

### Regenerating Build Configuration

```bash
python configure.py
```

This uses `tools/project.py` and `tools/ninja_syntax.py` to generate `build.ninja`.

### Extracting Game Assets

```bash
python tools/arc_tool.py orig/GAFE01_00/files/foresta.rel.szs extract
```

### Checking Decompilation Status

Uses `tools/decompctx.py`:
```bash
# Counts matched vs. unmatched functions
ninja status
```

## Build Flow

```
User runs: ./build.sh decomp full
         ↓
    configure.py (if needed)
         ↓
    tools/project.py (loads config)
    tools/ninja_syntax.py (generates build.ninja)
         ↓
    ninja (executes generated rules)
         ↓
    Metrowerks compiler (via Wine/wibo)
    ↓
    built objects
         ↓
    linker
         ↓
    build/GAFE01_00/GAFE01_00.dol + foresta.rel
```

## Adding New Build Features

To add a new tool or converter:

1. Create a Python module in `tools/`
2. Import in `project.py` or `ninja_syntax.py`
3. Update build metadata in `config/GAFE01_00/config.yml`
4. Test: `python configure.py && ./build.sh decomp full`

## Troubleshooting

### "Python module not found"
- Check that module is in `tools/` directory
- Verify Python path includes `tools/`
- See [configure.py](../configure.py) for import logic

### "Build rules out of date"
```bash
python configure.py  # Regenerate build.ninja
./build.sh decomp full
```

### "Asset extraction fails"
- Check that disc image is in `orig/GAFE01_00/`
- Verify format is ISO, RVZ, WIA, WBFS, CISO, or GCZ
- Run with verbose output if needed

## Related

- **Configuration:** [config/README.md](../config/README.md)
- **Build scripts:** [build.sh](../build.sh)
- **Main entry:** [configure.py](../configure.py)
- **Main project:** [README.md](../README.md)
