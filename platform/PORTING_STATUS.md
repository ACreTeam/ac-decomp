# Apple Metal Port — Status Document

## What Has Been Done

### Build System (`platform/CMakeLists.txt`)
- CMake project targeting macOS, iPadOS, and iOS (arm64 only)
- Shadow header system: `platform/include/` is searched first, overriding original GC SDK headers
- Fragment `.c` files excluded from `GLOB_RECURSE` (furniture/, *_anime.c, etc.)
- Metrowerks SDK files excluded (boot.c, MSL_C.PPCEABI.bare.H/, Runtime.PPCEABI.H/)
- `-Dmain=ac_main_entry` avoids conflict with game's own `game_main(GAME*)` function

### Shadow Headers (`platform/include/`)
- **`platform/compat.h`**: s32/u32 fixed-width typedefs; `membersize` macro; `__abs` shim; `ATTRIBUTE_ALIGN`
- **`PR/mbi.h`**: Full N64 GBI stub:
  - `Gfx` union with `.pwords` for pointer-bearing static initializers
  - All render mode aliases including `G_RM_AA_DEC_LINE`
  - Texture block macros with double-expansion bug fixed
  - `Vtx_tn` with `n[3]` + `a` fields (not combined `cn[4]`)
  - `Mtx` as a struct (so struct-assignment works)
  - `GPACK_RGBA5551`, `GPACK_RGB24A8`, `GPACK_ZDZ`
  - `gsDPSetTextureLOD`, `gsDPSetTextureConvert`, `gsDPSetCombineKey`
  - `gSPViewport` dynamic macro
  - G_CC combiner presets including `G_CC_BLENDPEDECALA`
- **`PR/abi.h`**: `Acmd` type for audio ABI
- **`dolphin/card.h`**: Fixed-width types; correct `CARDStat` struct; private `__CARD*` API declarations
- **`dolphin/types.h`**, **`dolphin/os.h`**, **`dolphin/dvd.h`**, **`dolphin/hw_regs.h`**: arm64-safe shadows
- **`libultra/libultra.h`**: Apple guard around bcmp/bcopy/bzero (conflict with `<strings.h>`)

### Original Headers Fixed
- **`include/libc64/sprintf.h`**: Apple guard for sprintf (conflict with `<stdio.h>`)
- **`include/libultra/libultra.h`**: Apple guard for bcmp/bcopy/bzero
- **`include/m_scene.h`**: `mSc_DATA_*` macros use designated initializers (pointer-in-static-init fix)
- **`include/libforest/gbi_extensions.h`**: `.pwords` for pointer-bearing static macros
- **`include/MSL_C/printf.h`**: Apple guard for vsprintf/vsnprintf/snprintf

### Source Fixes
- **`src/graph.c`**: Fixed `CONSTRUCT_THA_GA` macro — `sys_dynamic.##name` → `sys_dynamic.name`
- **`src/game/m_warning_ovl.c`**: Removed invalid `##` before named (non-variadic) macro params
- **`src/game/m_design_ovl.c`**: Added explicit `mDE_Ovl_c*` type to K&R `mDE_print_texture`
- **`src/game/m_card.c`**: Fixed include path and guarded sub-headers under `#ifndef __APPLE__`
- **`src/data/npc/model/mdl/rhn_1.c`**: Replaced `sizeof(Mtx)*13.0` with integer offset

### Platform Shims (`platform/src/`)
All subsystems have skeleton implementations that compile cleanly:
- **`os/`**: Thread, message queue, alarm, arena, RTC (thin POSIX mapping / stubs)
- **`gx/`**: GX draw call stubs; Metal renderer skeleton; texture decoder stub; TEV shader gen skeleton
- **`vi/`**: Window creation via SDL2 + Metal layer
- **`pad/`**: Controller input shim (SDL2 gamepad)
- **`dvd/`**: GCM filesystem reader stub
- **`card/`**: Memory card → file-backed save shim
- **`dsp/ai/`**: Audio mixer skeleton
- **`main/main_apple.mm`**: SDL2 + Metal app entry point

---

## What Remains

### 1. Remaining Compile Errors (In Progress)
Still working through final categories of compile errors. As of last build:
- `MSL_C.PPCEABI.bare.H/` FILE struct conflicts → excluded from build
- Likely a few more categories of errors remain (unknown until current build completes)

### 2. Linker Errors (After Clean Compile)
Once all .c files compile, there will be linker errors from:
- **Missing GX function bodies**: `GXBegin`, `GXEnd`, `GXPosition3f`, `GXColor4u8`, etc. in `platform/src/gx/` are currently empty stubs
- **Missing OS function bodies**: Some thread/sync primitives may be stubs
- **Missing audio bodies**: DSP/AI audio functions

### 3. Rendering Backend — `platform/src/gx/` (Major Work)
The largest remaining piece. Currently skeleton code only:

**`gx_geometry.cpp`** — GXBegin/GXEnd vertex buffer:
- Must capture `GXPosition*`, `GXColor*`, `GXTexCoord*` calls into a per-primitive vertex buffer
- On `GXEnd`, submit buffer as Metal draw call

**`metal_renderer.mm`** — Metal render pipeline:
- Create `MTLRenderPipelineDescriptor` for each unique TEV/vertex format combination
- Manage `MTLBuffer` pool for vertex data
- Handle `MTLCommandBuffer`/`MTLRenderCommandEncoder` lifecycle

**`tev_shader_gen.mm`** — TEV → Metal shader:
- Translate GX TEV stage configuration (up to 16 stages) to Metal Shading Language
- Cache compiled `MTLFunction` objects by TEV hash
- Map GX texture units to Metal texture bindings

**`texture_decode.cpp`** — GX texture format → MTLTexture:
- Decode CMPR (S3TC-like), I4, I8, IA4, IA8, RGB565, RGB5A3, RGBA8, CI4, CI8, CI14 formats
- Upload to `MTLTexture` via `replaceRegion:mipmapLevel:withBytes:`

**`gx_transform.cpp`** — Matrix and viewport:
- Keep GX matrix stack in sync with Metal vertex shader uniforms
- Convert GX viewport/scissor to Metal viewport

**`gx_pixel.cpp`** — Blend modes, depth test:
- Map GX render modes (RM_AA_ZB_OPA_SURF etc.) to `MTLRenderPipelineDescriptor` blend state

### 4. Display Link / Game Loop — `platform/src/vi/vi_window.mm`
- Wire up `CADisplayLink` (iOS) / `CVDisplayLink` (macOS) to call the GX frame flush
- Current stub calls SDL2 event loop but doesn't drive the game's VI retrace callback

### 5. DVD / Asset Pipeline — `platform/src/dvd/`
- `gcm_fs.cpp` needs to locate and parse the game's GCM/ISO image
- All `DVDOpen`/`DVDRead` calls must resolve to real file data
- The `.rvz` format used by Dolphin emulator requires extraction first — the raw ISO/GCM is needed
- ROM asset stubs generated by `tools/gen_asset_stubs.py` return zero-filled data; real data needed

### 6. Audio — `platform/src/audio/` and `platform/src/dsp/`
- `audio_mixer.cpp`: implement ADPCM/PCM mixing for the game's audio channels
- Need to route the game's `JAudio`/`JAS` audio engine output to CoreAudio or AVAudioEngine
- DSP microcode emulation not required — the game uses a known DSP program that can be replaced

### 7. Memory Card Save System — `platform/src/card/card_shim.cpp`
- `card_shim.cpp` is a skeleton; needs file-backed implementation
- Map GC memory card blocks to a local `.sav` file
- Implement async callbacks (CARDMountAsync, CARDReadAsync, CARDWriteAsync)

### 8. iOS-Specific
- Touch input → GC controller mapping in `pad_shim.cpp`
- iOS Info.plist and entitlements are present but may need bundle ID / signing configuration
- Screen orientation lock and safe area insets for notch/Dynamic Island

### 9. REL / Overlay Loading (Investigation Needed)
- If the game dynamically loads `.rel` relocation files, a runtime linker shim is needed
- Check whether `src/static/` contains REL loader code; if so, it may need porting

---

## Build Instructions (Current State)

```sh
cd platform
cmake -B build_test -DPLATFORM=macos
cmake --build build_test --target AnimalCrossing
```

For iOS:
```sh
cmake -B build_ios -DPLATFORM=ios -DAPPLE_TEAM_ID=YOURTEAMID
cmake --build build_ios --target AnimalCrossing
```

---

## Priority Order

1. **Achieve clean compile** (in progress — last few error categories)
2. **Achieve clean link** — fill in minimum stub bodies
3. **Boot to black screen** — game loop runs, Metal renders empty frame
4. **Boot to title** — DVD/asset pipeline, basic rendering
5. **Playable** — full rendering, audio, save system
