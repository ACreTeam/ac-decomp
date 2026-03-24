# Decompilation Guide

This directory contains documentation for the Animal Crossing decompilation effort. This is an ongoing project to reverse-engineer and rewrite the original GameCube source code in C.

## What is Decompilation?

Decompilation is the process of converting compiled machine code (assembly) back into readable source code. For Animal Crossing, we:

1. Extract the game binary from the disc image
2. Use tools like Ghidra to analyze and understand the code
3. Write C source that matches the original behavior
4. Verify the compiled output matches the original binary (bit-for-bit)

## Getting Started

- **[Decomp Basics](./decomp_basics.md)** — Introduction to decompilation concepts
- **[Ghidra Setup](./ghidra_setup.md)** — Install and configure Ghidra for analysis
- **[Ghidra Basics](./ghidra_basics.md)** — How to use Ghidra effectively
- **[m2c Basics](./m2c_basics.md)** — Decompiled-to-C assembly converter

## Decompilation Workflow

### 1. Extract Game Files

See [Dumping Game Files](./extract_game.md) for instructions to extract the game binary and assets from your disc.

### 2. Generate Decomp Context

See [Generating Decomp Context](./generating_decomp_context.md) to set up the analysis environment.

### 3. Analyze with Ghidra

Open the extracted binary in Ghidra and start reverse-engineering functions:

- Right-click functions → Rename/retype
- Create structs for data types
- Add comments explaining logic
- Export findings for the C codebase

### 4. Match with C Code

Write C implementations that match the decompiled assembly:

- Use decomp.me online tool or local m2c for guidance
- Compile with the Metrowerks compiler (via build system)
- Compare generated assembly against the original
- Iterate until byte-for-byte match

### 5. Verify Build

```bash
./build.sh decomp full
```

The build system will verify the compiled output matches the original binary.

## Progress Tracking

- View real-time decomp progress on [decomp.dev](https://decomp.dev/ACreTeam/ac-decomp)
- Check symbol completion rates for DOL and REL modules

## Directory Organization

| Directory | Purpose |
|-----------|---------|
| `include/` | Decompiled function/data declarations and GameCube SDK headers |
| `src/` | C source files for decompiled game logic |
| `tools/` | Python build tools (ninja config, decompctx, etc.) |
| `config/GAFE01_00/` | Decompilation metadata for USA version (splits, symbols) |
| `build/` | Generated build artifacts (intermediate objects, final DOL/REL) |

## Key Files

- **[configure.py](../configure.py)** — Sets up decompilation build (run once)
- **[build.sh](../build.sh)** — Main build entry point
- **[build.ninja](../build.ninja)** — Generated Ninja build rules (auto-generated, don't edit)

## Decompilation Tips

### Finding Functions in Ghidra
- Use Ghidra's Symbol Table to search for known function names
- Cross-reference calls to locate related functions
- Look at string references to find handlers

### Writing Matching C
- Study the original assembly closely — every instruction matters
- Use compiler pragmas to force specific code generation
- Test on both debug and release builds
- Use `#pragma pack()` for struct memory layouts

### Common Issues
- **Pointer size assumptions** — GameCube is 32-bit PowerPC; use `uint32_t` explicitly
- **Floating point precision** — Match compiler settings exactly
- **Instruction ordering** — Some sequences depend on CPU cache behavior

## Resources

- [decomp.me](https://decomp.me) — Online decompilation matching tool with compiler options
- [Ghidra docs](https://ghidra-sre.org/CheatSheet.html) — Official Ghidra documentation
- [ac-decomp contributing guide](https://github.com/Prakxo/ac-decomp#contributing) — Community standards
- [Dolphin emulator docs](https://dolphin-emu.org/) — GameCube/Wii hardware reference

## Contributing

Decompilation is community-driven:

1. Fork the repository
2. Pick a function or symbol to decompose
3. Create a descriptive PR with your C implementation
4. Include reference to the original assembly/Ghidra findings
5. Maintainers will review matching results

See main [README.md](../README.md) for build prerequisites.
