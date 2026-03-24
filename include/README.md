# Include Headers (Decompilation)

This directory contains C/C++ header files for the decompilation.

## Overview

- **Decompiled function/struct declarations** for the game logic
- **Dolphin SDK headers** (GameCube HAL: GX, PAD, DVD, CARD, VI, etc.)
- **Standard C library headers** (MSL_C, MSL_CPP — Metrowerks Standard Library)
- **Convenience headers** for common types and utilities

## Structure

```
include/
├── ac_*.h               # Decompiled game structures & functions
├── _mem.h               # Memory allocation
├── JSystem/             # JSystem framework (Nintendo graphics/audio)
├── GBA/, Famicom/       # Embedded emulators framework
├── Dolphin/             # GameCube SDK (GX, PAD, DVD, CARD, OS, etc.)
├── MSL_C/, MSL_CPP/     # Metrowerks Standard Library
├── OdemuExi/            # Emulator debugging
├── PowerPC_EABI_Support/# PowerPC calling conventions
└── Runtime.PPCEABI.H/   # Runtime environment
```

## Important Notes

### For Decompilation Contributors
- Add decompiled function/struct declarations here
- Keep declarations organized by subsystem (e.g., `ac_*.h` for game code)
- Must match the decompiled source in `src/`
- Include guards prevent multiple inclusion

### For Metal Port Developers
- **Platform-specific headers go in `platform/include/`**
- These headers are used by both decomp and platform builds
- Platform shim layer provides platform-specific implementations
- See [Platform README](../platform/README.md)

### Dolphin SDK Headers
These are the official GameCube SDK headers:
- `Dolphin/gx.h` — Graphics subsystem (GX)
- `Dolphin/pad.h` — Controller input (PAD)
- `Dolphin/dvd.h` — Disc access (DVD)
- `Dolphin/card.h` — Save data (CARD)
- `Dolphin/vi.h` — Video interface
- `Dolphin/os.h` — OS services (threading, interrupts, etc.)

For the Metal port, platform shims replace functions from these headers.

## Adding New Headers

1. Decompiled declarations: Create `include/ac_*.h` matching the subsystem
2. Platform-specific: Put in `platform/include/` instead
3. Follow existing naming conventions
4. Ensure include guards: `#ifndef AC_SUBSYSTEM_H` / `#define AC_SUBSYSTEM_H`
5. Reference related headers in comments

## Key Files

| Header | Purpose |
|--------|---------|
| `_mem.h` | Memory allocation macros |
| `JSystem/*.h` | Nintendo graphics/audio framework |
| `Dolphin/*.h` | GameCube SDK subsystems |
| `ac_*.h` | Decompiled game logic |

## Verification

Run the full build to ensure headers are used correctly:

```bash
./build.sh decomp full
```

The compiler will report any missing declarations or type mismatches.

## Troubleshooting

### Header not found
- Check include paths in [configure.py](../configure.py)
- Verify header is in a tracked location (not in platform/)

### Type mismatches in compilation
- Ensure struct definition matches decompiled code
- Use `#pragma pack(1)` for packed structures if needed
- Check pointer sizes (GC = 32-bit; must handle explicitly for Metal port)

### Platform-specific code
- Use `#ifdef PLATFORM_APPLE` for platform-specific includes
- Keep main includes clean; shim implementations in `platform/include/`

## Related

- **Source code:** [src/README.md](../src/README.md)
- **Platform headers:** [platform/include/](../platform/include/)
- **Decompilation guide:** [docs/DECOMP_GUIDE.md](../docs/DECOMP_GUIDE.md)
- **Main project:** [README.md](../README.md)
