# Metal Port for macOS, iOS, and iPadOS

This directory contains all platform-specific implementations for running Animal Crossing on Apple devices via Metal. See [TECHNICAL_REFERENCE.md](./TECHNICAL_REFERENCE.md) for deep architectural details.

## Quick Start

### macOS

```bash
brew install ninja cmake sdl2 llvm
./build.sh macos
# Output: platform/build_macos/Release/AnimalCrossing.app
```

### iOS / iPadOS

```bash
./build.sh ios
# or
./build.sh ipados
# Output: platform/build_ios/Release-iphoneos/AnimalCrossing.app
```

## Build Requirements

| Platform | Tool | Version |
|----------|------|---------|
| macOS | Xcode | 14.0+ |
| macOS | CMake | 3.20+ |
| macOS | SDL2 | 2.24+ |
| iOS | Xcode | 14.0+ |
| iPadOS | Xcode | 14.0+ |

## Runtime Requirements

### macOS
- Apple Silicon (M-series) or Intel Mac running macOS 11+
- Physical MFi or Bluetooth controller (required)
- Animal Crossing: GameCube disc image (ISO or GCM format)

### iOS / iPadOS
- iOS 14+ / iPadOS 14+
- Physical MFi controller (required)
- Animal Crossing: GameCube disc image (via document picker on first launch)

## Directory Structure

```
platform/
├── src/                    # Platform-specific C/C++ implementations
│   ├── audio/             # Audio mixer and DSP emulation
│   ├── card/              # Save data / memory card emulation
│   ├── dsp/               # DSP audio subsystem shims
│   ├── dvd/               # Disc image virtual filesystem
│   ├── gx/                # Graphics (GX → Metal translation)
│   ├── main.cpp           # Entry point
│   ├── os/                # OS services (threading, memory, timers)
│   ├── pad/               # Controller input
│   └── vi/                # Video output
├── include/               # Platform-specific headers
├── ios/                   # iOS-specific config (Info.plist, entitlements)
├── macos/                 # macOS-specific config (Info.plist)
├── toolchains/            # CMake cross-compilation toolchains
├── CMakeLists.txt         # Build configuration
└── PORTING_STATUS.md      # Current implementation status
```

## Build Configuration

### Environment Variables

- `APPLE_TEAM_ID` — Required for iOS/iPadOS notarization (optional for development)
- `PLATFORM` — Set to `macos`, `ios`, or `ipados` (handled by `build.sh`)

### CMake Options

- `-DPLATFORM=macos|ios|ipados` — Target platform
- `-DCMAKE_BUILD_TYPE=Release|Debug` — Build type
- `-DENABLE_PROFILING=ON|OFF` — Enable profiling hooks (default: OFF)

## Troubleshooting

### macOS Build Fails
- Verify Xcode is installed: `xcode-select --install`
- Update SDL2: `brew upgrade sdl2`
- Check CMake version: `cmake --version` (need 3.20+)

### iOS Build Fails
- Ensure Xcode is selected: `sudo xcode-select --reset`
- Check provisioning profiles in Xcode

### Runtime: "Please connect a controller"
- Physical controller required; no on-screen controls supported
- Verify controller is paired via Settings > Bluetooth
- Try reconnecting the controller

### Runtime: Disc image not found
- macOS: Pass disc image path to the app via settings
- iOS/iPadOS: Use document picker on first launch to select the image

## Development

### Making Changes

1. Modify source files in `platform/src/`
2. Rebuild: `./build.sh platform macos` (or ios/ipados)
3. Run the app and test

### Adding New Subsystems

- Create subsystem in `platform/src/{subsystem}/`
- Add CMakeLists.txt for that subsystem
- Link to main target in `platform/CMakeLists.txt`
- Include headers in `platform/include/`

### Debugging

- Install LLDB: `brew install lldb`
- Attach to running process for breakpoints and memory inspection
- macOS: Console.app shows app logs

## References

- [TECHNICAL_REFERENCE.md](./TECHNICAL_REFERENCE.md) — Architecture and implementation details
- [PORTING_STATUS.md](./PORTING_STATUS.md) — Current progress and known issues
