#!/bin/bash
set -euo pipefail

NCPU=$(sysctl -n hw.logicalcpu 2>/dev/null || echo 4)

usage() {
    cat <<'EOF'
Usage:
    ./build.sh decomp [full|dol|rel] [-j N] [--reconfigure] [--skip-sha]
  ./build.sh platform [macos|ios|ipados] [clean]

Backwards-compatible shortcuts:
  ./build.sh macos [clean]
  ./build.sh ios [clean]
  ./build.sh ipados [clean]

Decomp profiles:
  full   Build everything (default)
  dol    Build only static DOL output
  rel    Build only REL output

Flags:
    --skip-sha   Avoid final build/GAFE01_00/ok checksum check (useful for long non-matching builds)
EOF
}

run_platform_build() {
    local platform="${1:-macos}"
    local maybe_clean="${2:-}"
    local build_dir="platform/build_${platform}"

    if [[ "$maybe_clean" == "clean" && -d "$build_dir" ]]; then
        echo "[build] Cleaning $build_dir"
        rm -rf "$build_dir"
    fi

    mkdir -p "$build_dir"

    if [[ "$platform" == "ios" || "$platform" == "ipados" ]]; then
        echo "[build] Configuring for $platform (Xcode generator)"
        cmake -S platform -B "$build_dir" \
            -DPLATFORM="$platform" \
            -DCMAKE_TOOLCHAIN_FILE="$(pwd)/platform/toolchains/ios.cmake" \
            -GXcode \
            ${APPLE_TEAM_ID:+-DAPPLE_TEAM_ID="$APPLE_TEAM_ID"}
        echo "[build] Building $platform"
        cmake --build "$build_dir" --config Release -- -jobs "$NCPU"
        echo "[build] Output: $build_dir/Release-iphoneos/AnimalCrossing.app"
    elif [[ "$platform" == "macos" ]]; then
        echo "[build] Configuring for macOS"
        cmake -S platform -B "$build_dir" \
            -DPLATFORM=macos \
            -DCMAKE_BUILD_TYPE=Release
        echo "[build] Building macOS"
        cmake --build "$build_dir" -j"$NCPU"
        echo "[build] Output: $build_dir/bin/AnimalCrossing.app"
    else
        echo "Unknown platform: $platform"
        usage
        exit 1
    fi
}

run_decomp_build() {
    local profile="full"
    local jobs="$NCPU"
    local reconfigure="0"
    local skip_sha="0"

    if [[ $# -gt 0 ]]; then
        profile="$1"
        shift
    fi

    while [[ $# -gt 0 ]]; do
        case "$1" in
            -j)
                jobs="$2"
                shift 2
                ;;
            --reconfigure)
                reconfigure="1"
                shift
                ;;
            --skip-sha)
                skip_sha="1"
                shift
                ;;
            *)
                echo "Unknown decomp option: $1"
                usage
                exit 1
                ;;
        esac
    done

    if [[ "$reconfigure" == "1" || ! -f build.ninja ]]; then
        echo "[build] Running configure.py"
        python3 configure.py
    fi

    case "$profile" in
        full)
            if [[ "$skip_sha" == "1" ]]; then
                echo "[build] Running full decomp build without sha check, with -j$jobs"
                ninja -j"$jobs" build/GAFE01_00/static.dol build/GAFE01_00/foresta/foresta.rel
            else
                echo "[build] Running full decomp build with -j$jobs"
                ninja -j"$jobs"
            fi
            ;;
        dol)
            echo "[build] Building static DOL target with -j$jobs"
            ninja -j"$jobs" build/GAFE01_00/static.dol
            ;;
        rel)
            echo "[build] Building REL target with -j$jobs"
            ninja -j"$jobs" build/GAFE01_00/foresta/foresta.rel
            ;;
        *)
            echo "Unknown decomp profile: $profile"
            usage
            exit 1
            ;;
    esac
}

mode="${1:-decomp}"

case "$mode" in
    decomp)
        shift || true
        run_decomp_build "$@"
        ;;
    platform)
        shift || true
        run_platform_build "${1:-macos}" "${2:-}"
        ;;
    macos|ios|ipados)
        run_platform_build "$mode" "${2:-}"
        ;;
    -h|--help|help)
        usage
        ;;
    *)
        echo "Unknown mode: $mode"
        usage
        exit 1
        ;;
esac
