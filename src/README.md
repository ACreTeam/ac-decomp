# Source Code (Decompilation)

This directory contains the decompiled C source code for Animal Crossing (GameCube version GAFE01_00).

## Overview

- **~22,000 files** of original decompiled game code
- Written in **C** (with some headers for C++ compatibility)
- Compiles with the **Metrowerks PowerPC compiler** via the build system
- Output: Static DOL executable + REL dynamic modules

## Structure

```
src/
├── actor/              # Actor/entity implementations (NPCs, objects)
├── effect/             # Visual effects
├── furniture/          # Furniture logic
├── game/               # Core game systems
├── system/             # Low-level system code
├── bg_item/            # Background item handling
├── data/               # Static game data
├── main.c              # Entry point
├── game.c              # Main game loop
├── audio.c             # Audio driver interface
├── padmgr.c            # Pad/controller manager
├── save_menu.c         # Save menu logic
└── ... (many more)     # Various game systems
```

## Important Notes

### For Decompilation Contributors
- **Don't modify for the Metal port** — These files should stay true to the original
- Use this with `./build.sh decomp` to build the decompiled version
- Any changes must match the original assembly bit-for-bit
- See [Decompilation Guide](../docs/DECOMP_GUIDE.md) for contributing

### For Metal Port Developers
- **Don't directly modify these files** — They're shared with the decomp build
- Platform-specific code goes in `platform/src/` instead
- Use platform shim layer to translate API calls (e.g., GX → Metal)
- See [Platform README](../platform/README.md) for the architecture

### Dependencies
- Includes from `include/` directory (SDK headers + decompiled declarations)
- Standard library functions (headers in `include/MSL_C/`, etc.)
- No external dependencies beyond GameCube SDK

## Building

### Decompilation Only
```bash
./build.sh decomp full   # Full build
./build.sh decomp dol    # DOL only
./build.sh decomp rel    # REL modules only
```

Output: `build/GAFE01_00/GAFE01_00.dol` + `build/GAFE01_00/foresta.rel`

### With Metal Port
```bash
./build.sh platform macos   # Compiles src/ + platform/src/
```

The same `src/` files compile into both:
- A reference build (native PowerPC, via decomp build)
- An Apple port (arm64 Metal, via platform build)

## Verification

The build system verifies decompiled code by comparing compiled output to the original:

```bash
./build.sh decomp full --skip-sha   # Disable final checksum check
```

Use this if your decompilation is incomplete and won't match yet.

## Common Issues

### Build fails with "compiler not found"
- The Metrowerks compiler is downloaded automatically
- If it fails, check your Python version (needs 3.8+)
- See main [README](../README.md) for platform-specific setup

### Compiler errors about struct layout
- GC code assumes 32-bit pointers
- Use `#ifdef PLATFORM_APPLE` guards for platform-specific code
- See [Metal Port Technical Reference](../platform/TECHNICAL_REFERENCE.md) for details

### Function not matching
- Every instruction matters — check alignment, register usage, etc.
- Use decomp.me online tool for quick feedback
- Consult Ghidra analysis for the original assembly

## Related

- **Decompilation progress:** [decomp.dev](https://decomp.dev/ACreTeam/ac-decomp)
- **Decomp guide:** [docs/DECOMP_GUIDE.md](../docs/DECOMP_GUIDE.md)
- **Platform port:** [platform/README.md](../platform/README.md)
- **Main project:** [README.md](../README.md)
