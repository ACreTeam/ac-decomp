#!/bin/bash
# Animal Crossing Metal Port — build entry point
# Usage: ./build.sh [macos|ios|ipados] [clean]
set -euo pipefail

PLATFORM="${1:-macos}"
BUILD_DIR="platform/build_${PLATFORM}"

if [[ "${2:-}" == "clean" && -d "$BUILD_DIR" ]]; then
    echo "[build] Cleaning $BUILD_DIR"
    rm -rf "$BUILD_DIR"
fi

mkdir -p "$BUILD_DIR"

NCPU=$(sysctl -n hw.logicalcpu 2>/dev/null || echo 4)

if [[ "$PLATFORM" == "ios" || "$PLATFORM" == "ipados" ]]; then
    echo "[build] Configuring for $PLATFORM (Xcode generator)"
    cmake -S platform -B "$BUILD_DIR" \
        -DPLATFORM="$PLATFORM" \
        -DCMAKE_TOOLCHAIN_FILE="$(pwd)/platform/toolchains/ios.cmake" \
        -GXcode \
        ${APPLE_TEAM_ID:+-DAPPLE_TEAM_ID="$APPLE_TEAM_ID"}
    echo "[build] Building $PLATFORM"
    cmake --build "$BUILD_DIR" --config Release -- -jobs "$NCPU"
    echo "[build] Output: $BUILD_DIR/Release-iphoneos/AnimalCrossing.app"
else
    echo "[build] Configuring for macOS"
    cmake -S platform -B "$BUILD_DIR" \
        -DPLATFORM=macos \
        -DCMAKE_BUILD_TYPE=Release
    echo "[build] Building macOS"
    cmake --build "$BUILD_DIR" -j"$NCPU"
    echo "[build] Output: $BUILD_DIR/bin/AnimalCrossing.app"
fi
