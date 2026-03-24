# Documentation Index

This repository has two main areas. Use this index to find what you need.

---

## 🔷 Decompilation (Reverse-Engineering)

For contributing to the C source code decompilation effort.

### Quick Start
- **[Decompilation Guide](./DECOMP_GUIDE.md)** — Start here for decompilation concepts
- **[Dumping Game Files](./extract_game.md)** — How to extract your disc
- **[Ghidra Setup](./ghidra_setup.md)** — Install and configure Ghidra

### In-Depth Guides
- **[Ghidra Basics](./ghidra_basics.md)** — Using Ghidra for analysis
- **[m2c Basics](./m2c_basics.md)** — Assembly-to-C conversion tools
- **[decomp.me Basics](./decomp_me_basics.md)** — Online matching tool

### Reference
- **[Generating Decomp Context](./generating_decomp_context.md)** — Build metadata setup
- [decomp.dev](https://decomp.dev/ACreTeam/ac-decomp) — Live progress tracker
- [decomp.me](https://decomp.me) — Assembly-to-C matcher

---

## 🍎 Metal Port (macOS/iOS/iPadOS)

For porting the decompiled game to Apple platforms using Metal graphics.

### Quick Start
- **[Platform README](../platform/README.md)** — Build instructions for macOS and iOS
- **[Technical Reference](../platform/TECHNICAL_REFERENCE.md)** — Architecture deep-dive
- **[Porting Status](../platform/PORTING_STATUS.md)** — What's implemented vs. TODO

### Subsystems
- Graphics: GX → Metal translation
- Input: PAD → MFi controller mapping
- Disc: DVD → ISO file reader
- Audio: DSP/AI → SDL2 audio
- Save Data: CARD → GCI files

---

## 📋 Project Organization

- **[Main README](../README.md)** — Project overview and navigation
- [Repository Structure](../README.md#repository-structure) — Directory layout
- [Build Instructions](../README.md#building) — How to build either component
- [Contributing Guide](../README.md#contributing) — How to contribute

---

## 📚 Related Resources

| Resource | Purpose |
|----------|---------|
| [Ghidra](https://ghidra-sre.org/) | Reverse engineering framework |
| [Dolphin Wiki](https://wiki.dolphin-emu.org/) | GameCube/Wii hardware docs |
| [Metal Documentation](https://developer.apple.com/metal/) | Apple graphics framework |
| [Discord Community](https://discord.gg/hKx3FJJgrV) | Live development chat |

---

## 🎯 Common Tasks

### "I want to help decompose functions"
1. Read [Decompilation Guide](./DECOMP_GUIDE.md)
2. Set up Ghidra via [Ghidra Setup](./ghidra_setup.md)
3. Check [decomp.dev](https://decomp.dev/ACreTeam/ac-decomp) for available functions
4. Use [decomp.me](https://decomp.me) to match your C code to the original assembly

### "I want to work on the Metal port"
1. Read [Platform README](../platform/README.md)
2. Check [Porting Status](../platform/PORTING_STATUS.md) for TODO items
3. Review [Technical Reference](../platform/TECHNICAL_REFERENCE.md) for system details
4. Modify `platform/src/` and test locally

### "I need to understand the project structure"
1. Read main [README.md](../README.md)
2. Check [Repository Structure](../README.md#repository-structure) section
3. Review sub-READMEs in each directory

---

## 🗂️ File Structure

```
docs/
├── README.md (this file)
├── DECOMP_GUIDE.md              # Decompilation entry point
├── extract_game.md              # Dumping disc files
├── ghidra_setup.md              # Install Ghidra
├── ghidra_basics.md             # Using Ghidra
├── m2c_basics.md                # Assembly→C tools
├── decomp_me_basics.md          # Online matcher
├── generating_decomp_context.md # Build setup
└── doc_assets/                  # Screenshots & images

../platform/
├── README.md                    # Platform-specific build guide
├── TECHNICAL_REFERENCE.md       # Subsystem architecture
└── PORTING_STATUS.md            # Implementation progress
```

---

**Last Updated:** See git history for this file
