# Configuration & Metadata

This directory contains decompilation metadata for building the game binary.

## Overview

- **Build configuration** per game version (GAFE01_00, GAFU01_00, etc.)
- **Symbol information** (function locations, names in the original binary)
- **File splits** (how to chunk the binary for parallel decompilation)
- **Linker scripts** (memory layout and linking rules)
- **Build checksums** (for verification)

## Structure

```
config/
├── GAFE01_00/           # USA version (Rev 0) - ACTIVE
│   ├── config.yml       # Master build config
│   ├── build.sha1       # Expected checksum
│   ├── symbols.txt      # Symbol table
│   ├── splits.txt       # Binary split points
│   ├── ldscript.tpl     # Linker script template
│   └── foresta/         # REL module config
│       ├── splits.txt
│       ├── symbols.txt
│       └── ldscript.tpl
└── GAFU01_00/           # European version config (not currently used)
    ├── config.yml
    ├── build.sha1
    ├── symbols.txt
    ├── splits.txt
    └── ldscript.tpl
```

## Key Files

### `config.yml`
Master build configuration:
```yaml
name: "GAFE01_00"
version: 0
base_url: "..."                    # Where to download compiler
compiler_version: "..."            # Metrowerks version
```

Edit this to change compilers or build options.

### `symbols.txt`
Maps binary offsets to function/variable names:
```
80004000 game_main
80004100 game_tick
80004200 initialize_memory
...
```

Updated as decompilation progresses.

### `splits.txt`
Breaks the binary into chunks for parallel decompilation:
```
00000000 DOL
00004000 game_main
00005000 init_systems
...
```

Determines how the build assigns object files to binary sections.

### `build.sha1`
Expected SHA1 checksum of the compiled binary. Used for verification:
```
abc123def456...
```

Update when the binary should legitimately change (e.g., fixing a match).

### `ldscript.tpl`
Linker script template. Controls memory layout and section mapping.
Used when linking the compiled object files into the final DOL/REL.

## Important Notes

### For Decompilation Contributors
- **Update `symbols.txt`** when you name a new function
- **Update `build.sha1`** when your changes complete a match
- Don't hand-edit `splits.txt` — it's generated from `symbols.txt`
- Matches are verified against `build.sha1`

### For Metal Port Developers
- **Don't modify these files** — They're specific to the decompilation build
- Platform builds use a different configuration system (CMake)
- Both builds use the same `src/` and `include/` but different build systems

### Version-Specific
Currently only **GAFE01_00 (USA)** is active.
- GAFU01_00 (European) config exists but isn't used
- N64 version has its own repo: [zeldaret/af](https://github.com/zeldaret/af)

## Workflow

### Adding a Decompiled Function

1. **Decompile the function** → write C in `src/`
2. **Add declaration** → add to appropriate `include/ac_*.h`
3. **Update symbols** → add entry to `config/GAFE01_00/symbols.txt`
4. **Build** → `./build.sh decomp full`
5. **Verify** → check against original with objdiff

### Updating Checksums

When a decompilation completes (bit-for-bit match):

1. Build succeeds
2. Compute new checksum: `sha1sum build/GAFE01_00/GAFE01_00.dol`
3. Update `config/GAFE01_00/build.sha1`
4. Commit

### Generating Split Points

Run `configure.py`:
```bash
python configure.py
```

This regenerates `splits.txt` from `symbols.txt` automatically.

## Build System Integration

The build system reads these configs:

```
configure.py
    ↓
config/GAFE01_00/*.txt
    ↓
build.ninja (generated)
    ↓
compile & link
    ↓
build/GAFE01_00/GAFE01_00.dol + foresta.rel
```

See [configure.py](../configure.py) for the integration logic.

## Troubleshooting

### "Build checksum mismatch"
Your compiled binary doesn't match the expected hash. Either:
- Your C code is incorrect (still matching the original, but not yet)
- You've already fixed functions and need to update `build.sha1`
- Something changed in the toolchain

### "Symbol not found"
- Check `config/GAFE01_00/symbols.txt` — is it listed?
- Regenerate splits: `python configure.py`
- Rebuild: `./build.sh decomp full`

### "Linker error"
- Check `ldscript.tpl` — memory layout might be wrong
- Verify sections in the linker script match your object files
- Check object file order in `splits.txt`

## Related

- **Source code:** [src/README.md](../src/README.md)
- **Build system:** [configure.py](../configure.py)
- **Decompilation guide:** [docs/DECOMP_GUIDE.md](../docs/DECOMP_GUIDE.md)
- **Main project:** [README.md](../README.md)
