cmake_minimum_required(VERSION 3.24)
project(AnimalCrossing LANGUAGES C CXX OBJCXX)

# -DPLATFORM=macos|ios|ipados  (default: macos)
if(NOT DEFINED PLATFORM)
    set(PLATFORM "macos")
endif()

message(STATUS "Building for platform: ${PLATFORM}")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_OBJCXX_STANDARD 17)

# arm64 only across all Apple targets
set(CMAKE_OSX_ARCHITECTURES arm64)

if(PLATFORM STREQUAL "ios" OR PLATFORM STREQUAL "ipados")
    set(CMAKE_SYSTEM_NAME iOS)
    set(CMAKE_OSX_SYSROOT iphoneos)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0")
    set(IOS_BUILD TRUE)
else()
    set(CMAKE_OSX_DEPLOYMENT_TARGET "12.0")
    set(IOS_BUILD FALSE)
endif()

# ---- Compile definitions applied to all targets ----
add_compile_definitions(
    PLATFORM_APPLE=1
    TARGET_PC=1       # activates #ifdef TARGET_PC seams in original GX headers
    # Prevent OS_BUS_CLOCK / OS_CORE_CLOCK from dereferencing raw addresses
    PLATFORM_OVERRIDE_CLOCKS=1
    VERSION=0         # VER_GAFE01_00 (North American) — excludes AUS/GAFU01 code
)

# Treat missing-function-declarations as errors to catch unimplemented stubs early
add_compile_options(
    -Wall
    -Wno-unused-parameter
    -Wno-unused-function
    -Wno-sign-compare
    -Wno-missing-field-initializers
    # GC code uses GNU extensions
    -fms-extensions
    -Wno-microsoft-anon-tag
    # Original decompiled C uses K&R-style empty () prototypes
    -Wno-strict-prototypes
    -Wno-deprecated-non-prototype
    # Bitfield sign warnings from GBI structs
    -Wno-bitfield-constant-conversion
    # Pragma section directives from Metrowerks code
    -Wno-unknown-pragmas
    # Float/double implicit conversions in game math
    -Wno-implicit-float-conversion
    # Ignore missing return from some game funcs
    -Wno-return-type
)

# ---- SDL2 ----
find_package(SDL2 REQUIRED)

# ---- Repo root (one level above platform/) ----
set(REPO_ROOT "${CMAKE_SOURCE_DIR}/..")

# ---- Include paths shared by all targets ----
set(PLATFORM_INCLUDES
    "${CMAKE_SOURCE_DIR}/include"          # platform/include (shadow headers first)
    "${REPO_ROOT}/include"                 # original Dolphin SDK headers
    "${REPO_ROOT}/src"                     # game source headers
    "${REPO_ROOT}"                         # repo root — for #include "src/..." paths used by .c_inc files
    "${SDL2_INCLUDE_DIRS}"
)

# ---- Subsystem object libraries ----
add_subdirectory(src/os)
add_subdirectory(src/gx)
add_subdirectory(src/vi)
add_subdirectory(src/pad)
add_subdirectory(src/dvd)
add_subdirectory(src/card)
add_subdirectory(src/dsp)
add_subdirectory(src/audio)
add_subdirectory(src/main)

# ---- Game source files ----
# Build GAFE01_00 (North American) version only — exclude AUS/GAFU01 duplicates.
# The AUS/ directory contains a parallel version with different collision logic
# that conflicts if compiled alongside the main sources.
file(GLOB_RECURSE GAME_SOURCES
    "${REPO_ROOT}/src/*.c"
)
list(FILTER GAME_SOURCES EXCLUDE REGEX ".*/static/dolphin/.*\\.c$")
# boot.c defines main(int, char**) which conflicts with src/main.c's main() after -Dmain=game_main
list(FILTER GAME_SOURCES EXCLUDE REGEX ".*/static/boot\\.c$")
list(FILTER GAME_SOURCES EXCLUDE REGEX ".*/src/AUS/.*\\.c$")
# Exclude .c files that are #included as data fragments, not standalone TUs
list(FILTER GAME_SOURCES EXCLUDE REGEX ".*/actor/npc/ac_npc_.*_anime\\.c$")
list(FILTER GAME_SOURCES EXCLUDE REGEX ".*/actor/npc/ac_npc_shop_common\\.c$")
# All furniture/*.c are #included by f_furniture.c — not standalone TUs
list(FILTER GAME_SOURCES EXCLUDE REGEX ".*/src/furniture/.*\\.c$")
# Individual fragment files
list(FILTER GAME_SOURCES EXCLUDE REGEX ".*/effect/ef_effect_lib\\.c$")
list(FILTER GAME_SOURCES EXCLUDE REGEX ".*/actor/ac_animal_logo_misc\\.c$")
list(FILTER GAME_SOURCES EXCLUDE REGEX ".*/game/m_item_debug\\.c$")
list(FILTER GAME_SOURCES EXCLUDE REGEX ".*/libforest/emu64/emu64_utility\\.c$")

# ---- Main executable ----
add_executable(AnimalCrossing
    ${GAME_SOURCES}
    $<TARGET_OBJECTS:platform_os>
    $<TARGET_OBJECTS:platform_gx>
    $<TARGET_OBJECTS:platform_vi>
    $<TARGET_OBJECTS:platform_pad>
    $<TARGET_OBJECTS:platform_dvd>
    $<TARGET_OBJECTS:platform_card>
    $<TARGET_OBJECTS:platform_dsp>
    $<TARGET_OBJECTS:platform_audio>
    $<TARGET_OBJECTS:platform_main>
)

target_include_directories(AnimalCrossing PRIVATE ${PLATFORM_INCLUDES})

# C compile options applied only to game .c sources:
# - Force-include platform.h so shadow header guards are set first
# - -Dmain=game_main avoids conflict with SDL_main
# - gnu89 (C89 + GNU extensions) allows K&R-style empty-parens definitions that
#   follow prototype declarations — a common pattern in this decompiled code
set_source_files_properties(${GAME_SOURCES} PROPERTIES
    COMPILE_OPTIONS
        "-include;${CMAKE_SOURCE_DIR}/include/platform/platform.h;-Dmain=ac_main_entry;-std=gnu89"
)

# ---- Platform-specific link flags ----
if(NOT IOS_BUILD)
    # macOS
    target_link_libraries(AnimalCrossing
        "-framework Metal"
        "-framework MetalKit"
        "-framework Cocoa"
        "-framework QuartzCore"
        "-framework CoreVideo"
        ${SDL2_LIBRARIES}
    )
    set_target_properties(AnimalCrossing PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME "Animal Crossing"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.acdecomp.animalcrossing"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/macos/Info.plist"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
else()
    # iOS / iPadOS
    target_link_libraries(AnimalCrossing
        "-framework Metal"
        "-framework MetalKit"
        "-framework UIKit"
        "-framework QuartzCore"
        "-framework AVFoundation"
        "-framework GameController"
        ${SDL2_LIBRARIES}
    )
    set_target_properties(AnimalCrossing PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_BUNDLE_NAME "Animal Crossing"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.acdecomp.animalcrossing"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_SOURCE_DIR}/ios/Info.plist"
        XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "iPhone Developer"
        XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "${APPLE_TEAM_ID}"
        XCODE_ATTRIBUTE_CODE_SIGN_ENTITLEMENTS
            "${CMAKE_SOURCE_DIR}/ios/AnimalCrossing.entitlements"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif()
