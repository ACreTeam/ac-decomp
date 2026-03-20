# ACGC-Metal-Port: Technical Implementation Reference

## Project Overview

A native port of Animal Crossing (GameCube) targeting all modern Apple Metal devices — macOS (M-series), iPadOS, and iOS. Built on top of a completed decompilation (`ac-decomp`). The approach: keep the original decompiled C source code untouched and route all GameCube hardware API calls through a thin platform shim layer. The result is a native application on each target — not emulation.

- **96% C** — original decompiled game source, unmodified
- **2.3% C++** — the platform shim layer
- **1.5% Python** — inherited build tooling

---

## Repository Structure

- `src/` — original decompiled game C source files
- `include/` — Dolphin SDK headers (GX, OS, DVD, CARD, PAD, VI, MTX subsystems)
- `platform/` — all platform-specific replacement implementations
  - `CMakeLists.txt`
  - `src/` and `include/` for each reimplemented subsystem
- `build.sh` — entry point for the build
- Build output:
  - macOS: `platform/build/bin/AnimalCrossing.app`
  - iOS/iPadOS: `platform/build/bin/AnimalCrossing.ipa`
- Runtime files: `settings.ini`, `rom/` (disc image), `save/`
  - macOS: `~/Library/Application Support/AnimalCrossing/`
  - iOS/iPadOS: app-sandboxed `Documents/` directory

---

## Build System

- **Toolchain:** Apple Clang (Xcode), CMake, SDL2
  - macOS: install dependencies via Homebrew
  - iOS/iPadOS: build via Xcode with an iOS SDK target; CMake toolchain file for iOS cross-compilation (e.g. `cmake-toolchain-ios` or the `ios.toolchain.cmake` community toolchain)
- **Target architecture:** arm64 only across all targets — M-series Macs, iPads, and modern iPhones are all arm64. This simplifies the build significantly.
  - **Critical:** The original GameCube code assumes 32-bit pointer sizes. All struct layouts must be audited for pointer-size assumptions and ported to use explicit fixed-width types (`uint32_t`, `int32_t`, etc.) and `__attribute__((packed))` where necessary. Do not assume `sizeof(void*)` == 4.
- **Build flow:** `./build.sh` → CMake configures with a platform flag (`-DPLATFORM=macos|ios|ipados`) → compiles `src/` with platform-conditional defines (e.g. `#ifdef PLATFORM_APPLE`) that redirect SDK calls to `platform/` implementations
- **iOS entry point:** iOS does not use a standard `main()` — wrap the game's entry point using SDL2's `SDL_main` macro, which handles the `UIApplicationMain` bootstrapping

---

## Subsystem Implementations

### Graphics: GX → Metal

The GameCube's GX API is a state-machine graphics interface. The shim intercepts every GX call the game makes and translates it to native Metal with MSL shaders.

- Use SDL2 with `SDL_WINDOW_METAL` for surface and window management across all platforms, or use a raw `CAMetalLayer` on macOS and a `UIView` with a `CAMetalLayer` on iOS/iPadOS
- Functions intercepted: `GXBegin()`, `GXPosition3f32()`, `GXSetTevOrder()`, `GXLoadTexObj()`, and the full GX surface
- The hardest piece: **TEV combiner** — a multi-stage configurable color/alpha blending pipeline. Must be emulated via MSL fragment shaders, either dynamically compiled per TEV config using `MTLLibrary` with dynamic source compilation, or via a general uber-shader covering all TEV stage combinations the game uses
- **Texture decoding:** GameCube proprietary formats (I4, I8, IA4, IA8, RGB565, RGB5A3, RGBA8, CI4, CI8, CMPR) must be decoded to Metal-compatible formats on load; implement a texture cache with a size cap and LRU eviction — iOS/iPadOS have no swap and will terminate the app if memory pressure is too high
- **Enhancements:** configurable resolution up to native Retina/ProMotion, fullscreen on macOS, VSync via `CAMetalLayer.displaySyncEnabled` — exposed via `settings.ini` and an in-game options menu
- **Retina/display scaling:** query `UIScreen.nativeScale` on iOS/iPadOS or `NSWindow.backingScaleFactor` on macOS and scale the render target accordingly

### Input: PAD → Physical Controller Only

Physical MFi and Bluetooth controllers are the only supported input method. No on-screen touch controls.

- Redirect `PADRead()` to SDL2's Game Controller API
- Support controller hotplug detection
- SDL2 handles MFi and Xbox/PlayStation controllers natively on iOS 13+ and macOS 11+ via the GameController framework — no extra entitlements needed for standard HID gamepads
- If no controller is connected, the game should display a "please connect a controller" prompt and wait rather than attempting to proceed

### Disc Access: DVD → ISO file reader

- Redirect `DVDOpen()` / `DVDReadPrio()` to a virtual filesystem that reads from a disc image at startup
- Supported formats: ISO, GCM
- No extraction/preprocessing needed — implement a virtual FS that maps DVD file paths to byte offsets within the image
- Use standard POSIX file I/O (`open`, `pread`, `close`)
- **iOS/iPadOS file access:** the app sandbox prevents arbitrary file path access. Present a `UIDocumentPickerViewController` on first launch to let the user select their disc image; persist the resulting security-scoped bookmark in `UserDefaults` so the app can re-open it on subsequent launches without prompting again

### Save Data: CARD → GCI file I/O

- Redirect `CARDOpen()` / `CARDRead()` / `CARDWrite()` to file operations on GCI-format files in the save directory
- Support Memory Card A only
- Use the same GCI format as Dolphin exports for bidirectional save compatibility
- Save directory:
  - macOS: `~/Library/Application Support/AnimalCrossing/save/`
  - iOS/iPadOS: `<app Documents>/save/`

### Audio: DSP/AI → SDL2 Audio / Core Audio

- The GameCube DSP handles hardware ADPCM decoding + mixing (up to 64 voices); the AI handles DMA output
- Replace with: CPU-side ADPCM decoder + software voice mixer + SDL2 audio callback for output
- SDL2 on all Apple platforms routes through Core Audio — no additional platform-specific work needed beyond the SDL2 layer
- **iOS/iPadOS:** configure the app's `AVAudioSession` category to `.playback` so audio continues when the device is silenced via the hardware mute switch and does not get interrupted by other apps' audio without intent

### Video Output: VI → SDL2 Window

- Replace Video Interface hardware config with SDL2 window management + Metal context
- Frame timing via `CVDisplayLink` (macOS) or `CADisplayLink` (iOS/iPadOS) for display-synced callbacks; SDL2 timers are an acceptable fallback
- Support a `--no-framelimit` flag on macOS for unlocked FPS
- **ProMotion:** on 120Hz iPads and iPhones, `CADisplayLink` will default to 60Hz unless `preferredFrameRateRange` is set — cap explicitly at 60 FPS to match the game's intended framerate

### OS Services

- Map GameCube OS threading, memory allocation, interrupt handling, and timer calls to POSIX equivalents (`pthreads`, `malloc`/`free`, `clock_gettime`, `mach_absolute_time` for high-resolution timing)
- PowerPC-specific initialization (paired-singles, cache management, BAT register config) should be stubbed out or no-op'd

---

## Endianness

GameCube (PowerPC) is **big-endian**; arm64 is **little-endian**. Every multi-byte value read from disc (filesystem metadata, assets, textures, save data, event schedules) must be byte-swapped on read. Use `OSSwapBigToHostInt16/32/64` (from `<libkern/OSByteOrder.h>`) or portable `be32toh` / `be16toh` macros. This is a cross-cutting concern — missing a single swap causes subtle data corruption (e.g. event dates triggering at wrong times).

---

## Other Porting Concerns

- **Metrowerks compiler extensions:** at-address variable declarations used for memory-mapped registers — stub these out
- **Split memory:** GameCube has 24 MB main RAM + 16 MB ARAM; the build uses standard heap allocation. The game's memory footprint is inherently small, but the texture cache must enforce a size cap on iOS/iPadOS to avoid jetsam termination
- **REL dynamic linking:** the game's main logic is in a relocatable module (`foresta.rel.szs`, Yaz0-compressed) — the port must handle REL loading/linking at runtime
- **Hardened Runtime / entitlements:** if the REL loader writes executable code into memory at runtime, add the `com.apple.security.cs.allow-jit` entitlement on macOS. On iOS, JIT is not permitted for App Store distribution — the REL loader must use a pure data-linking approach (patch pointers and relocations without marking pages executable)
