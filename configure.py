#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import json
import os
import re
import sys
import urllib.request
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "GAFE01_00",  # USA Rev 0
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--orthrus",
    metavar="BINARY",
    type=Path,
    help="path to orthrus[.exe] (optional)",
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.orthrus_path = args.orthrus
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-1"
config.compilers_tag = "20240706"
config.dtk_tag = "v1.2.0"
config.objdiff_tag = "v2.3.4"
config.sjiswrap_tag = "v1.2.0"
config.wibo_tag = "0.6.11"
config.orthrus_tag = "v0.2.0"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    "-I include/dolphin",
    "-I include/libc",
    "-I src/static/dolphin",
    f"-I build/{config.version}/include",
    # needed for JUTResFONT_Ascfont_fix12
    f"-I build/{config.version}/bin/assets",
    f"--defsym version={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
    "-warn off",
]
if args.debug:
    config.ldflags.append("-g")
if args.map:
    config.ldflags.append("-mapunused")

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    # Platform Definitions
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    # Multibyte Definitions
    "-multibyte",
    "-char unsigned",
    # Gekko Specific Definitions
    "-fp hardware",
    "-Cpp_exceptions off",
    '-pragma "cats off"',
    # Default compiler flags (turn off if needed)
    # "-W all",
    # "-O4,p",
    # "-inline auto",
    '-pragma "warn_notinlined off"',
    # Helpful linker flags
    "-maxerrors 1",
    "-nosyspath",
    # dtk-specific includes
    "-i include",
    "-i include/dolphin",
    "-i include/libc",
    "-i src/static/dolphin",
    f"-i build/{config.version}/include",
    f"-DVERSION={version_num}",
]

# Debug flags
if args.debug:
    cflags_base.extend(["-sym on", "-DDEBUG=1", "-D_DEBUG"])
else:
    cflags_base.extend(["-sym on", "-DDEBUG=0", "-DNDEBUG"])

cflags_common = [
    # Needed for N64 SDK
    "-d _LANGUAGE_C",
    "-d F3DEX_GBI_2",
    # Project-specific stuff
    "-d MUST_MATCH",
]

# DOL flags
cflags_static = [
    *cflags_base,
    *cflags_common,
    "-O4,s",
]

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-O4,p",
    "-inline all",
]

# REL flags
cflags_foresta = [
    *cflags_base,
    *cflags_common,
    "-O4,s",
    "-sdata 0",
    "-sdata2 0",
    "-d IS_REL",
    "-requireprotos",
    "-sym on",
]

config.linker_version = "GC/1.3.2"


# Helper function for Dolphin libraries
def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": [*cflags_runtime, "-char signed"],
        "progress_category": "sdk",
        "src_dir": "src/static",
        "objects": objects,
    }


def JSystemLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3.2",
        "cflags": [*cflags_base, "-O4,s", "-char signed"],
        "progress_category": "jsystem",
        "src_dir": "src/static",
        "objects": objects,
    }


# Helper function for REL script objects
def Rel(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3.2",
        "cflags": cflags_foresta,
        "progress_category": "game",
        "objects": objects,
    }


Matching = True  # Object matches and should be linked
NonMatching = False  # Object does not match and should not be linked
Equivalent = (
    config.non_matching
)  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = False
config.warn_missing_source = False
config.libs = [
    {
        "lib": "boot",
        "mw_version": config.linker_version,
        "cflags": [
            *cflags_static,
            "-sdata 0",
            "-sdata2 0",
            "-inline on",
        ],
        "progress_category": "game",
        "src_dir": "src/static",
        "objects": [
            Object(Matching, "boot.c"),
            Object(Matching, "jsyswrap.cpp"),
            Object(Matching, "version.c"),
            Object(Matching, "initial_menu.c"),
            Object(Matching, "dvderr.c", extra_cflags=["-pool off"]),
            Object(Matching, "bootdata/gam_win1.c"),
            Object(Matching, "bootdata/gam_win2.c"),
            Object(Matching, "bootdata/gam_win3.c"),
            Object(Matching, "bootdata/logo_nin.c"),
            Object(Matching, "nintendo_hi_0.c"),
            Object(Matching, "GBA2/JoyBoot.c"),
        ],
    },
    {
        "lib": "libforest",
        "mw_version": config.linker_version,
        "cflags": cflags_static,
        "progress_category": "library",
        "src_dir": "src/static",
        "objects": [
            Object(NonMatching, "libforest/emu64/emu64.cc", extra_cflags=["-lang=c++", "-O4,p", "-inline auto"]),
            Object(Matching, "libforest/osreport.c"),
            Object(Matching, "libforest/fault.c"),
            Object(Matching, "libforest/ReconfigBATs.c"),
        ],
    },
    {
        "lib": "libu64",
        "mw_version": config.linker_version,
        "cflags": cflags_static,
        "progress_category": "library",
        "src_dir": "src/static",
        "objects": [
            Object(Matching, "libu64/debug.c"),
            Object(Matching, "libu64/gfxprint.c"),
            Object(Matching, "libu64/gfxprint_data.c"),
            Object(Matching, "libu64/pad.c"),
        ],
    },
    {
        "lib": "libc64",
        "mw_version": config.linker_version,
        "cflags": cflags_static,
        "progress_category": "library",
        "src_dir": "src/static",
        "objects": [
            Object(NonMatching, "libc64/__osMalloc.c"),
            Object(Matching, "libc64/aprintf.c"),
            Object(Matching, "libc64/math64.c"),
            Object(Matching, "libc64/qrand.c"),
            Object(Matching, "libc64/sleep.c"),
            Object(Matching, "libc64/sprintf.c"),
            Object(Matching, "libc64/malloc.c"),
        ],
    },
    {
        "lib": "libultra",
        "mw_version": config.linker_version,
        "cflags": [*cflags_static, "-O4,p", "-inline auto"],
        "progress_category": "library",
        "src_dir": "src/static",
        "objects": [
            Object(Matching, "libultra/contquery.c"),
            Object(NonMatching, "libultra/contreaddata.c"),
            Object(Matching, "libultra/controller.c"),
            Object(Matching, "libultra/contsetch.c"),
            Object(Matching, "libultra/gu/coss.c"),
            Object(Matching, "libultra/createmesgqueue.c"),
            Object(Matching, "libultra/createthread.c"),
            Object(Matching, "libultra/destroythread.c"),
            Object(Matching, "libultra/getthreadid.c"),
            Object(Matching, "libultra/gettime.c"),
            Object(Matching, "libultra/initialize.c"),
            Object(Matching, "libultra/gu/lookat.c"),
            Object(Matching, "libultra/gu/lookathil.c"),
            Object(Matching, "libultra/gu/mtxutil.c"),
            Object(Matching, "libultra/gu/normalize.c"),
            Object(Matching, "libultra/gu/ortho.c"),
            Object(Matching, "libultra/gu/perspective.c"),
            Object(Matching, "libultra/recvmesg.c"),
            Object(Matching, "libultra/gu/rotate.c"),
            Object(Matching, "libultra/gu/scale.c"),
            Object(Matching, "libultra/sendmesg.c"),
            Object(Matching, "libultra/setthreadpri.c"),
            Object(NonMatching, "libultra/settimer.c"),
            Object(Matching, "libultra/shutdown.c"),
            Object(Matching, "libultra/gu/sins.c"),
            Object(Matching, "libultra/startthread.c"),
            Object(Matching, "libultra/stoptimer.c"),
            Object(Matching, "libultra/timerintr.c"),
            Object(Matching, "libultra/gu/translate.c"),
            Object(Matching, "libultra/ultra.c"),
            Object(Matching, "libultra/xldtob.c"),
            Object(Matching, "libultra/xlitob.c"),
            Object(Equivalent, "libultra/xprintf.c"),
        ],
    },
    {
        "lib": "libjsys",
        "mw_version": config.linker_version,
        "cflags": cflags_static,
        "progress_category": "library",
        "src_dir": "src/static",
        "objects": [
            Object(NonMatching, "libjsys/jsyswrapper.cpp"),
        ],
    },
    DolphinLib(
        "ai",
        [
            Object(NonMatching, "dolphin/ai/ai.c"),
        ],
    ),
    DolphinLib(
        "ar",
        [
            Object(NonMatching, "dolphin/ar/ar.c"),
            Object(NonMatching, "dolphin/ar/arq.c"),
        ],
    ),
    DolphinLib(
        "amcstubs",
        [
            Object(Matching, "dolphin/amcstubs/AmcExi2Stubs.c"),
        ],
    ),
    DolphinLib(
        "base",
        [
            Object(Matching, "dolphin/base/PPCArch.c"),
        ],
    ),
    DolphinLib(
        "card",
        [
            Object(Matching, "dolphin/card/CARDBios.c"),
            Object(Matching, "dolphin/card/CARDBlock.c"),
            Object(Matching, "dolphin/card/CARDCheck.c"),
            Object(Matching, "dolphin/card/CARDCreate.c"),
            Object(Matching, "dolphin/card/CARDDelete.c"),
            Object(Matching, "dolphin/card/CARDDir.c"),
            Object(Matching, "dolphin/card/CARDFormat.c"),
            Object(Matching, "dolphin/card/CARDMount.c"),
            Object(Matching, "dolphin/card/CARDNet.c"),
            Object(Matching, "dolphin/card/CARDOpen.c"),
            Object(Matching, "dolphin/card/CARDRdwr.c"),
            Object(Matching, "dolphin/card/CARDRead.c"),
            Object(Matching, "dolphin/card/CARDRename.c"),
            Object(Matching, "dolphin/card/CARDStat.c"),
            Object(Matching, "dolphin/card/CARDStatEx.c"),
            Object(Matching, "dolphin/card/CARDWrite.c"),
        ],
    ),
    DolphinLib(
        "db",
        [
            Object(NonMatching, "dolphin/db/db.c"),
        ],
    ),
    DolphinLib(
        "dsp",
        [
            Object(NonMatching, "dolphin/dsp/dsp.c"),
        ],
    ),
    DolphinLib(
        "dvd",
        [
            Object(Matching, "dolphin/dvd/dvd.c"),
            Object(Matching, "dolphin/dvd/dvderror.c"),
            Object(Matching, "dolphin/dvd/dvdfs.c"),
            Object(Matching, "dolphin/dvd/dvdlow.c"),
            Object(Matching, "dolphin/dvd/dvdqueue.c"),
            Object(Matching, "dolphin/dvd/fstload.c"),
        ],
    ),
    DolphinLib(
        "exi",
        [
            Object(Matching, "dolphin/exi/EXIBios.c"),
            Object(Matching, "dolphin/exi/EXIUart.c"),
        ],
    ),
    DolphinLib(
        "gba",
        [
            Object(Matching, "dolphin/gba/GBA.c"),
            Object(Matching, "dolphin/gba/GBAGetProcessStatus.c"),
            Object(Matching, "dolphin/gba/GBAJoyBoot.c"),
            Object(Matching, "dolphin/gba/GBARead.c"),
            Object(Matching, "dolphin/gba/GBAWrite.c"),
            Object(Matching, "dolphin/gba/GBAXfer.c"),
        ],
    ),
    DolphinLib(
        "gx",
        [
            Object(Matching, "dolphin/gx/GXAttr.c"),
            Object(Matching, "dolphin/gx/GXBump.c"),
            Object(Matching, "dolphin/gx/GXDisplayList.c"),
            Object(Matching, "dolphin/gx/GXFifo.c"),
            Object(Matching, "dolphin/gx/GXFrameBuf.c"),
            Object(Matching, "dolphin/gx/GXGeometry.c"),
            Object(Matching, "dolphin/gx/GXInit.c"),
            Object(Matching, "dolphin/gx/GXLight.c"),
            Object(Matching, "dolphin/gx/GXMisc.c"),
            Object(Matching, "dolphin/gx/GXPerf.c"),
            Object(Matching, "dolphin/gx/GXPixel.c"),
            Object(Matching, "dolphin/gx/GXStubs.c"),
            Object(Matching, "dolphin/gx/GXTev.c"),
            Object(Matching, "dolphin/gx/GXTexture.c"),
            Object(Matching, "dolphin/gx/GXTransform.c"),
        ],
    ),
    DolphinLib(
        "mtx",
        [
            Object(NonMatching, "dolphin/mtx/mtx.c"),
            Object(NonMatching, "dolphin/mtx/mtx44.c"),
            Object(NonMatching, "dolphin/mtx/mtxvec.c"),
            Object(NonMatching, "dolphin/mtx/vec.c"),
        ],
    ),
    DolphinLib(
        "OdemuExi2",
        [
            Object(NonMatching, "dolphin/OdemuExi2/DebuggerDriver.c"),
        ],
    ),
    DolphinLib(
        "odenotstub",
        [
            Object(Matching, "dolphin/odenotstub/odenotstub.c"),
        ],
    ),
    DolphinLib(
        "os",
        [
            Object(Matching, "dolphin/os/__ppc_eabi_init.cpp"),
            Object(Matching, "dolphin/os/__start.c"),
            Object(NonMatching, "dolphin/os/OS.c"),
            Object(Matching, "dolphin/os/OSAlarm.c"),
            Object(NonMatching, "dolphin/os/OSAlloc.c"),
            Object(Matching, "dolphin/os/OSArena.c"),
            Object(Matching, "dolphin/os/OSAudioSystem.c"),
            Object(Matching, "dolphin/os/OSCache.c"),
            Object(Matching, "dolphin/os/OSContext.c"),
            Object(Matching, "dolphin/os/OSError.c"),
            Object(NonMatching, "dolphin/os/OSFont.c"),
            Object(NonMatching, "dolphin/os/OSInterrupt.c"),
            Object(NonMatching, "dolphin/os/OSLink.c"),
            Object(NonMatching, "dolphin/os/OSMemory.c"),
            Object(NonMatching, "dolphin/os/OSMessage.c"),
            Object(NonMatching, "dolphin/os/OSMutex.c"),
            Object(NonMatching, "dolphin/os/OSReboot.c"),
            Object(NonMatching, "dolphin/os/OSReset.c"),
            Object(NonMatching, "dolphin/os/OSResetSW.c"),
            Object(Matching, "dolphin/os/OSRtc.c"),
            Object(NonMatching, "dolphin/os/OSSync.c"),
            Object(NonMatching, "dolphin/os/OSThread.c"),
            Object(NonMatching, "dolphin/os/OSTime.c"),
        ],
    ),
    DolphinLib(
        "pad",
        [
            Object(Matching, "dolphin/pad/Pad.c"),
            Object(Matching, "dolphin/pad/Padclamp.c"),
        ],
    ),
    DolphinLib(
        "si",
        [
            Object(Matching, "dolphin/si/SIBios.c"),
            Object(Matching, "dolphin/si/SISamplingRate.c"),
        ],
    ),
    DolphinLib(
        "vi",
        [
            Object(NonMatching, "dolphin/vi/vi.c"),
        ],
    ),
    JSystemLib(
        "J2DGraph",
        [
            Object(NonMatching, "JSystem/J2DGraph/J2DGrafContext.cpp"),
            Object(NonMatching, "JSystem/J2DGraph/J2DOrthoGraph.cpp"),
        ],
    ),
    JSystemLib(
        "JFramework",
        [
            Object(NonMatching, "JSystem/JFramework/JFWDisplay.cpp"),
            Object(NonMatching, "JSystem/JFramework/JFWSystem.cpp"),
        ],
    ),
    JSystemLib(
        "JGadget",
        [
            Object(Matching, "JSystem/JGadget/linklist.cpp"),
        ],
    ),
    JSystemLib(
        "JKernel",
        [
            Object(Matching, "JSystem/JKernel/JKRAram.cpp"),
            Object(Matching, "JSystem/JKernel/JKRAramArchive.cpp"),
            Object(Matching, "JSystem/JKernel/JKRAramBlock.cpp"),
            Object(Matching, "JSystem/JKernel/JKRAramHeap.cpp"),
            Object(Matching, "JSystem/JKernel/JKRAramPiece.cpp"),
            Object(Matching, "JSystem/JKernel/JKRAramStream.cpp"),
            Object(NonMatching, "JSystem/JKernel/JKRArchivePri.cpp"),
            Object(NonMatching, "JSystem/JKernel/JKRArchivePub.cpp"),
            Object(Matching, "JSystem/JKernel/JKRCompArchive.cpp"),
            Object(Matching, "JSystem/JKernel/JKRDecomp.cpp"),
            Object(Matching, "JSystem/JKernel/JKRDisposer.cpp"),
            Object(Matching, "JSystem/JKernel/JKRDvdAramRipper.cpp"),
            Object(Matching, "JSystem/JKernel/JKRDvdArchive.cpp"),
            Object(Matching, "JSystem/JKernel/JKRDvdFile.cpp"),
            Object(Matching, "JSystem/JKernel/JKRDvdRipper.cpp"),
            Object(Matching, "JSystem/JKernel/JKRExpHeap.cpp"),
            Object(Matching, "JSystem/JKernel/JKRFileFinder.cpp"),
            Object(Matching, "JSystem/JKernel/JKRFileLoader.cpp"),
            Object(Matching, "JSystem/JKernel/JKRHeap.cpp"),
            Object(Matching, "JSystem/JKernel/JKRMemArchive.cpp"),
            Object(Matching, "JSystem/JKernel/JKRThread.cpp"),
        ],
    ),
    JSystemLib(
        "JSupport",
        [
            Object(NonMatching, "JSystem/JSupport/JSUFileStream.cpp"),
            Object(Matching, "JSystem/JSupport/JSUInputStream.cpp"),
            Object(NonMatching, "JSystem/JSupport/JSUList.cpp"),
        ],
    ),
    JSystemLib(
        "JUtility",
        [
            Object(NonMatching, "JSystem/JUtility/JUTAssert.cpp"),
            Object(NonMatching, "JSystem/JUtility/JUTConsole.cpp"),
            Object(NonMatching, "JSystem/JUtility/JUTDbPrint.cpp"),
            Object(NonMatching, "JSystem/JUtility/JUTDirectFile.cpp"),
            Object(NonMatching, "JSystem/JUtility/JUTDirectPrint.cpp"),
            Object(NonMatching, "JSystem/JUtility/JUTException.cpp"),
            Object(NonMatching, "JSystem/JUtility/JUTFader.cpp"),
            Object(NonMatching, "JSystem/JUtility/JUTFont.cpp"),
            Object(Matching, "JSystem/JUtility/JUTFontData_Ascfont_fix12.s"),
            Object(Matching, "JSystem/JUtility/JUTGamePad.cpp"),
            Object(NonMatching, "JSystem/JUtility/JUTGraphFifo.cpp"),
            Object(NonMatching, "JSystem/JUtility/JUTProcBar.cpp"),
            Object(NonMatching, "JSystem/JUtility/JUTResFont.cpp"),
            Object(NonMatching, "JSystem/JUtility/JUTVideo.cpp"),
            Object(NonMatching, "JSystem/JUtility/JUTXfb.cpp"),
        ],
    ),
    {
        "lib": "jaudio_NES",
        "mw_version": config.linker_version,
        "cflags": [*cflags_static, "-lang=c++", "-O4,s", "-str readonly"],
        "progress_category": "library",
        "src_dir": "src/static",
        "objects": [
            Object(NonMatching, "jaudio_NES/aramcall.c"),
            Object(NonMatching, "jaudio_NES/audioconst.c"),
            Object(NonMatching, "jaudio_NES/audiotable.c"),
            Object(NonMatching, "jaudio_NES/audiowork.c"),
            Object(NonMatching, "jaudio_NES/bankdrv.c"),
            Object(NonMatching, "jaudio_NES/bankread.c"),
            Object(NonMatching, "jaudio_NES/centcalc.c"),
            Object(NonMatching, "jaudio_NES/channel.c"),
            Object(NonMatching, "jaudio_NES/cmdstack.c"),
            Object(NonMatching, "jaudio_NES/connect.c"),
            Object(NonMatching, "jaudio_NES/driver.c"),
            Object(NonMatching, "jaudio_NES/driverinterface.c"),
            Object(NonMatching, "jaudio_NES/dsp_cardunlock.c"),
            Object(NonMatching, "jaudio_NES/dsp_GBAKey.c"),
            Object(NonMatching, "jaudio_NES/dspdriver.c"),
            Object(NonMatching, "jaudio_NES/dspinterface.c"),
            Object(NonMatching, "jaudio_NES/effect.c"),
            Object(NonMatching, "jaudio_NES/fat.c"),
            Object(NonMatching, "jaudio_NES/fxinterface.c"),
            Object(NonMatching, "jaudio_NES/heapctrl.c"),
            Object(NonMatching, "jaudio_NES/ipldec.c"),
            Object(NonMatching, "jaudio_NES/ja_calc.c"),
            Object(NonMatching, "jaudio_NES/jammain_2.c"),
            Object(NonMatching, "jaudio_NES/jamosc.c"),
            Object(NonMatching, "jaudio_NES/memory.c"),
            Object(NonMatching, "jaudio_NES/midplay.c"),
            Object(NonMatching, "jaudio_NES/noteon.c"),
            Object(NonMatching, "jaudio_NES/oneshot.c"),
            Object(NonMatching, "jaudio_NES/rate.c"),
            Object(NonMatching, "jaudio_NES/rspsim.c"),
            Object(NonMatching, "jaudio_NES/seqsetup.c"),
            Object(NonMatching, "jaudio_NES/system.c"),
            Object(NonMatching, "jaudio_NES/tables.c"),
            Object(NonMatching, "jaudio_NES/waveread.c"),
        ],
    },
    {
        "lib": "jaudio_NES_game",
        "mw_version": config.linker_version,
        "cflags": [*cflags_static, "-O0", "-inline off", "-lang=c++"],
        "progress_category": "library",
        "src_dir": "src/static",
        "objects": [
            Object(Matching, "jaudio_NES/game/audioheaders.c"),
            Object(Matching, "jaudio_NES/game/dummyprobe.c"),
            Object(NonMatching, "jaudio_NES/game/emusound.c"),
            Object(NonMatching, "jaudio_NES/game/game64.c"),
            Object(Matching, "jaudio_NES/game/kappa.c"),
            Object(Matching, "jaudio_NES/game/melody.c"),
            Object(Matching, "jaudio_NES/game/radio.c"),
            Object(Matching, "jaudio_NES/game/rhythm.c"),
            Object(Matching, "jaudio_NES/game/staff.c"),
            Object(Matching, "jaudio_NES/game/verysimple.c"),
        ],
    },
    {
        "lib": "jaudio_NES_internal",
        "mw_version": config.linker_version,
        "cflags": [
            *cflags_static,
            "-lang=c++",
            "-common on",
            "-func_align 32",
            "-inline off",
            "-str readonly",
            "-char signed",
            "-sdata 8",
            "-sdata2 8",
        ],
        "progress_category": "library",
        "src_dir": "src/static",
        "objects": [
            Object(Matching, "jaudio_NES/internal/aictrl.c"),
            Object(Matching, "jaudio_NES/internal/astest.c"),
            Object(Matching, "jaudio_NES/internal/audiothread.c"),
            Object(Matching, "jaudio_NES/internal/cpubuf.c"),
            Object(Matching, "jaudio_NES/internal/dspboot.c"),
            Object(Matching, "jaudio_NES/internal/dspbuf.c"),
            Object(Matching, "jaudio_NES/internal/dspproc.c"),
            Object(Matching, "jaudio_NES/internal/dummyrom.c"),
            Object(Matching, "jaudio_NES/internal/dvdthread.c"),
            Object(Matching, "jaudio_NES/internal/neosthread.c"),
            Object(Matching, "jaudio_NES/internal/os.c"),
            Object(Matching, "jaudio_NES/internal/playercall.c"),
            Object(Matching, "jaudio_NES/internal/random.c"),
            Object(Matching, "jaudio_NES/internal/sample.c"),
            Object(Matching, "jaudio_NES/internal/streamctrl.c"),
            Object(Matching, "jaudio_NES/internal/sub_sys.c"),
            Object(Matching, "jaudio_NES/internal/track.c"),
        ],
    },
    {
        "lib": "Famicom",
        "mw_version": "GC/1.3.2",
        "cflags": [
            *cflags_static,
            "-sdata 0",
            "-sdata2 0",
            "-sym on",
        ],
        "progress_category": "library",
        "src_dir": "src/static",
        "objects": [
            Object(NonMatching, "Famicom/ks_nes_core.cpp"),
            Object(NonMatching, "Famicom/ks_nes_draw.cpp"),
            # TODO: get ~J2DOrthoGraph's dtor in here somehow? 0x800468fc
            # also add in JUTGamePad::getPortStatus when JUTGamePad is linked?
            Object(NonMatching, "Famicom/famicom.cpp"),
            Object(Matching, "Famicom/famicom_nesinfo.cpp"),
        ],
    },
    {
        "lib": "MSL_C.PPCEABI.bare.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "src_dir": "src/static",
        "objects": [
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/abort_exit.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/ansi_files.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/ansi_fp.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/arith.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/buffer_io.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/ctype.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/direct_io.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/e_acos.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/e_atan2.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/e_rem_pio2.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/errno.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/file_io.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/FILE_POS.C"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/float.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/k_cos.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/k_rem_pio2.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/k_sin.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/mbstring.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/mem.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/mem_funcs.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/misc_io.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/printf.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/rand.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_atan.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_copysign.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_cos.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_floor.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_frexp.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_ldexp.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_modf.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/s_sin.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/scanf.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/string.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/strtoul.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/uart_console_io.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/w_acos.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/w_atan2.c"),
            Object(NonMatching, "MSL_C.PPCEABI.bare.H/wchar_io.c"),
        ],
    },
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "src_dir": "src/static",
        "objects": [
            Object(Matching, "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
            Object(Matching, "Runtime.PPCEABI.H/__mem.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/__va_arg.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/CPlusLibPPC.cp"),
            Object(NonMatching, "Runtime.PPCEABI.H/Gecko_ExceptionPPC.cp"),
            Object(Matching, "Runtime.PPCEABI.H/global_destructor_chain.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/NMWException.cp"),
            Object(NonMatching, "Runtime.PPCEABI.H/ptmf.c"),
            Object(NonMatching, "Runtime.PPCEABI.H/runtime.c"),
        ],
    },
    {
        "lib": "TRK_MINNOW_DOLPHIN",
        "mw_version": "GC/1.3",
        "cflags": [
            *cflags_static,
            "-O4,p",
            "-sdata 0",
            "-sdata2 0",
            "-inline auto,deferred",
            "-rostr",
            "-char signed",
            "-use_lmw_stmw on"
        ],
        "progress_category": "sdk",
        "src_dir": "src/static",
        "objects": [
            Object(Matching, "TRK_MINNOW_DOLPHIN/__exception.s"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/dispatch.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/dolphin_trk.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/dolphin_trk_glue.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/flush_cache.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/main_TRK.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/mainloop.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/mem_TRK.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/mpc_7xx_603e.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/msg.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/msgbuf.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/msghndlr.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/mslsupp.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/mutex_TRK.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/notify.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/nubevent.c"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/nubinit.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/serpoll.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/support.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/targcont.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/target_options.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/targimpl.c"),
            Object(NonMatching, "TRK_MINNOW_DOLPHIN/targsupp.s"),
            Object(Matching, "TRK_MINNOW_DOLPHIN/usr_put.c"),
        ],
    },
    Rel(
        "foresta",
        [
            Object(Matching, "audio.c"),
            Object(Matching, "c_keyframe.c"),
            Object(Matching, "ev_cherry_manager.c"),
            Object(Matching, "evw_anime.c"),
            Object(Matching, "executor.c"),
            Object(Matching, "f_furniture.c"),
            Object(Matching, "famicom_emu.c"),
            Object(Matching, "first_game.c"),
            Object(Matching, "game.c"),
            Object(Matching, "gamealloc.c"),
            Object(Matching, "gfxalloc.c"),
            Object(Matching, "graph.c"),
            Object(Matching, "irqmgr.c"),
            Object(Matching, "lb_reki.c"),
            Object(Matching, "lb_rtc.c"),
            Object(Matching, "main.c"),
            Object(Matching, "padmgr.c"),
            Object(Matching, "player_select.c"),
            Object(Matching, "PreRender.c"),
            Object(Matching, "s_cpak.c"),
            Object(Matching, "save_menu.c"),
            Object(Matching, "second_game.c"),
            Object(Matching, "THA_GA.c"),
            Object(Matching, "TwoHeadArena.c"),
            Object(Matching, "zurumode.c"),
        ],
    ),
    Rel(
        "actor",
        [
            Object(Matching, "actor/ac_airplane.c"),
            Object(Matching, "actor/ac_animal_logo.c"),
            Object(Matching, "actor/ac_ant.c"),
            Object(Matching, "actor/ac_aprilfool_control.c"),
            Object(Matching, "actor/ac_arrange_ftr.c"),
            Object(Matching, "actor/ac_arrange_room.c"),
            Object(Matching, "actor/ac_ball.c"),
            Object(Matching, "actor/ac_balloon.c"),
            Object(Matching, "actor/ac_bee.c"),
            Object(Matching, "actor/ac_birth_control.c"),
            Object(Matching, "actor/ac_boat.c"),
            Object(Matching, "actor/ac_boat_demo.c"),
            Object(Matching, "actor/ac_boxManager.c"),
            Object(Matching, "actor/ac_boxMove.c"),
            Object(Matching, "actor/ac_boxTrick01.c"),
            Object(Matching, "actor/ac_br_shop.c"),
            Object(Matching, "actor/ac_bridge_a.c"),
            Object(Matching, "actor/ac_broker_design.c"),
            Object(Matching, "actor/ac_buggy.c"),
            Object(Matching, "actor/ac_conveni.c"),
            Object(Matching, "actor/ac_cottage.c"),
            Object(NonMatching, "actor/ac_count02.c"),
            Object(NonMatching, "actor/ac_countdown.c"),
            Object(Matching, "actor/ac_depart.c"),
            Object(Matching, "actor/ac_douzou.c"),
            Object(Matching, "actor/ac_dummy.c"),
            Object(Matching, "actor/ac_dump.c"),
            Object(Matching, "actor/ac_effectbg.c"),
            Object(Matching, "actor/ac_event_manager.c"),
            Object(Matching, "actor/ac_fallS.c"),
            Object(Matching, "actor/ac_fallSESW.c"),
            Object(Matching, "actor/ac_field_draw.c"),
            Object(Matching, "actor/ac_fieldm_draw.c"),
            Object(Matching, "actor/ac_flag.c"),
            Object(Matching, "actor/ac_fuusen.c"),
            Object(Matching, "actor/ac_garagara.c"),
            Object(Matching, "actor/ac_ghog.c"),
            Object(Matching, "actor/ac_goza.c"),
            Object(Matching, "actor/ac_groundhog_control.c"),
            Object(Matching, "actor/ac_gyo_kage.c"),
            Object(Matching, "actor/ac_gyo_kaseki.c"),
            Object(Matching, "actor/ac_gyo_release.c"),
            Object(Matching, "actor/ac_gyo_test.c"),
            Object(Matching, "actor/ac_gyoei.c"),
            Object(Matching, "actor/ac_handOverItem.c"),
            Object(Matching, "actor/ac_haniwa.c"),
            Object(Matching, "actor/ac_hatumode_control.c"),
            Object(Matching, "actor/ac_house.c"),
            Object(Matching, "actor/ac_house_clock.c"),
            Object(Matching, "actor/ac_house_goki.c"),
            Object(Matching, "actor/ac_htable.c"),
            Object(Matching, "actor/ac_ins_amenbo.c"),
            Object(Matching, "actor/ac_ins_batta.c"),
            Object(Matching, "actor/ac_ins_chou.c"),
            Object(Matching, "actor/ac_ins_dango.c"),
            Object(Matching, "actor/ac_ins_goki.c"),
            Object(Matching, "actor/ac_ins_hitodama.c"),
            Object(Matching, "actor/ac_ins_hotaru.c"),
            Object(Matching, "actor/ac_ins_ka.c"),
            Object(Matching, "actor/ac_ins_kabuto.c"),
            Object(Matching, "actor/ac_ins_kera.c"),
            Object(Matching, "actor/ac_ins_mino.c"),
            Object(Matching, "actor/ac_ins_semi.c"),
            Object(Matching, "actor/ac_ins_tentou.c"),
            Object(Matching, "actor/ac_ins_tonbo.c"),
            Object(Matching, "actor/ac_insect.c"),
            Object(Matching, "actor/ac_intro_demo.c"),
            Object(Matching, "actor/ac_kago.c"),
            Object(Matching, "actor/ac_kamakura.c"),
            Object(Matching, "actor/ac_kamakura_indoor.c"),
            Object(Matching, "actor/ac_koinobori.c"),
            Object(NonMatching, "actor/ac_lighthouse_switch.c"),
            Object(Matching, "actor/ac_lotus.c"),
            Object(NonMatching, "actor/ac_mailbox.c"),
            Object(Matching, "actor/ac_mbg.c"),
            Object(Matching, "actor/ac_mikanbox.c"),
            Object(Matching, "actor/ac_mikuji.c"),
            Object(Matching, "actor/ac_misin.c"),
            Object(Matching, "actor/ac_mscore_control.c"),
            Object(Matching, "actor/ac_mural.c"),
            Object(Matching, "actor/ac_museum.c"),
            Object(Matching, "actor/ac_museum_fish.c"),
            Object(Matching, "actor/ac_museum_fossil.c"),
            Object(NonMatching, "actor/ac_museum_indoor.c"),
            Object(Matching, "actor/ac_museum_insect.c"),
            Object(Matching, "actor/ac_museum_picture.c"),
            Object(Matching, "actor/ac_my_house.c"),
            Object(Matching, "actor/ac_my_indoor.c"),
            Object(Matching, "actor/ac_my_room.c"),
            Object(Matching, "actor/ac_nameplate.c"),
            Object(NonMatching, "actor/ac_needlework_indoor.c"),
            Object(Matching, "actor/ac_needlework_shop.c"),
            Object(Matching, "actor/ac_police_box.c"),
            Object(Matching, "actor/ac_post_office.c"),
            Object(Matching, "actor/ac_present_demo.c"),
            Object(Matching, "actor/ac_psnowman.c"),
            Object(NonMatching, "actor/ac_pterminal.c"),
            Object(Matching, "actor/ac_quest_manager.c"),
            Object(Matching, "actor/ac_quest_talk_fj_init.c"),
            Object(Matching, "actor/ac_quest_talk_greeting.c"),
            Object(Matching, "actor/ac_quest_talk_init.c"),
            Object(Matching, "actor/ac_quest_talk_island.c"),
            Object(Matching, "actor/ac_quest_talk_normal_init.c"),
            Object(Matching, "actor/ac_radio.c"),
            Object(Matching, "actor/ac_reserve.c"),
            Object(Matching, "actor/ac_reset_demo.c"),
            Object(Matching, "actor/ac_ride_off_demo.c"),
            Object(Matching, "actor/ac_rope.c"),
            Object(Matching, "actor/ac_s_car.c"),
            Object(Matching, "actor/ac_sample.c"),
            Object(Matching, "actor/ac_set_manager.c"),
            Object(Matching, "actor/ac_set_npc_manager.c"),
            Object(Matching, "actor/ac_set_ovl_gyoei.c"),
            Object(Matching, "actor/ac_set_ovl_insect.c"),
            Object(Matching, "actor/ac_shop.c"),
            Object(Matching, "actor/ac_shop_design.c"),
            Object(Matching, "actor/ac_shop_goods.c"),
            Object(Matching, "actor/ac_shop_indoor.c"),
            Object(Matching, "actor/ac_shop_level.c"),
            Object(Matching, "actor/ac_shop_manekin.c"),
            Object(Matching, "actor/ac_shop_umbrella.c"),
            Object(Matching, "actor/ac_shrine.c"),
            Object(Matching, "actor/ac_sign.c"),
            Object(NonMatching, "actor/ac_snowman.c"),
            Object(Matching, "actor/ac_station.c"),
            Object(Matching, "actor/ac_structure.c"),
            Object(Matching, "actor/ac_super.c"),
            Object(Matching, "actor/ac_tama.c"),
            Object(Matching, "actor/ac_tent.c"),
            Object(NonMatching, "actor/ac_tokyoso_control.c"),
            Object(Matching, "actor/ac_tools.c"),
            Object(Matching, "actor/ac_toudai.c"),
            Object(Matching, "actor/ac_train0.c"),
            Object(Matching, "actor/ac_train1.c"),
            Object(Matching, "actor/ac_train_door.c"),
            Object(Matching, "actor/ac_train_window.c"),
            Object(Matching, "actor/ac_tukimi.c"),
            Object(NonMatching, "actor/ac_tunahiki_control.c"),
            Object(Matching, "actor/ac_turi.c"),
            Object(Matching, "actor/ac_uki.c"),
            Object(Matching, "actor/ac_weather.c"),
            Object(Matching, "actor/ac_weather_fine.c"),
            Object(Matching, "actor/ac_weather_leaf.c"),
            Object(Matching, "actor/ac_weather_rain.c"),
            Object(Matching, "actor/ac_weather_sakura.c"),
            Object(Matching, "actor/ac_weather_snow.c"),
            Object(Matching, "actor/ac_windmill.c"),
            Object(Matching, "actor/ac_yatai.c"),
        ],
    ),
    Rel(
        "actor_npc",
        [
            Object(NonMatching, "actor/npc/ac_countdown_npc0.c"),
            Object(NonMatching, "actor/npc/ac_countdown_npc1.c"),
            Object(Matching, "actor/npc/ac_go_home_npc.c"),
            Object(NonMatching, "actor/npc/ac_groundhog_npc0.c"),
            Object(NonMatching, "actor/npc/ac_halloween_npc.c"),
            Object(NonMatching, "actor/npc/ac_hanabi_npc0.c"),
            Object(NonMatching, "actor/npc/ac_hanabi_npc1.c"),
            Object(NonMatching, "actor/npc/ac_hanami_npc0.c"),
            Object(NonMatching, "actor/npc/ac_hanami_npc1.c"),
            Object(NonMatching, "actor/npc/ac_harvest_npc0.c"),
            Object(NonMatching, "actor/npc/ac_harvest_npc1.c"),
            Object(Matching, "actor/npc/ac_hatumode_npc0.c"),
            Object(NonMatching, "actor/npc/ac_kamakura_npc0.c"),
            Object(Matching, "actor/npc/ac_normal_npc.c"),
            Object(Matching, "actor/npc/ac_npc.c"),
            Object(Matching, "actor/npc/ac_npc2.c"),
            Object(Matching, "actor/npc/ac_npc_conv_master.c"),
            Object(Matching, "actor/npc/ac_npc_curator.c"),
            Object(Matching, "actor/npc/ac_npc_depart_master.c"),
            Object(Matching, "actor/npc/ac_npc_engineer.c"),
            Object(Matching, "actor/npc/ac_npc_guide.c"),
            Object(Matching, "actor/npc/ac_npc_guide2.c"),
            Object(NonMatching, "actor/npc/ac_npc_hem.c"),
            Object(NonMatching, "actor/npc/ac_npc_majin.c"),
            Object(NonMatching, "actor/npc/ac_npc_majin2.c"),
            Object(NonMatching, "actor/npc/ac_npc_majin3.c"),
            Object(NonMatching, "actor/npc/ac_npc_majin4.c"),
            Object(NonMatching, "actor/npc/ac_npc_majin5.c"),
            Object(Matching, "actor/npc/ac_npc_mamedanuki.c"),
            Object(NonMatching, "actor/npc/ac_npc_mask_cat.c"),
            Object(NonMatching, "actor/npc/ac_npc_mask_cat2.c"),
            Object(NonMatching, "actor/npc/ac_npc_needlework.c"),
            Object(Matching, "actor/npc/ac_npc_p_sel.c"),
            Object(Matching, "actor/npc/ac_npc_p_sel2.c"),
            Object(Matching, "actor/npc/ac_npc_police.c"),
            Object(NonMatching, "actor/npc/ac_npc_police2.c"),
            Object(Matching, "actor/npc/ac_npc_post_girl.c"),
            Object(NonMatching, "actor/npc/ac_npc_post_man.c"),
            Object(Matching, "actor/npc/ac_npc_rcn_guide.c"),
            Object(Matching, "actor/npc/ac_npc_rcn_guide2.c"),
            Object(NonMatching, "actor/npc/ac_npc_restart.c"),
            Object(Matching, "actor/npc/ac_npc_rtc.c"),
            Object(Matching, "actor/npc/ac_npc_sendo.c"),
            Object(NonMatching, "actor/npc/ac_npc_shasho.c"),
            Object(Matching, "actor/npc/ac_npc_shop_master.c"),
            Object(Matching, "actor/npc/ac_npc_shop_mastersp.c"),
            Object(Matching, "actor/npc/ac_npc_sleep_obaba.c"),
            Object(NonMatching, "actor/npc/ac_npc_soncho.c"),
            Object(NonMatching, "actor/npc/ac_npc_station_master.c"),
            Object(Matching, "actor/npc/ac_npc_super_master.c"),
            Object(Matching, "actor/npc/ac_npc_totakeke.c"),
            Object(NonMatching, "actor/npc/ac_present_npc.c"),
            Object(NonMatching, "actor/npc/ac_taisou_npc0.c"),
            Object(NonMatching, "actor/npc/ac_tamaire_npc0.c"),
            Object(NonMatching, "actor/npc/ac_tamaire_npc1.c"),
            Object(NonMatching, "actor/npc/ac_tokyoso_npc0.c"),
            Object(NonMatching, "actor/npc/ac_tokyoso_npc1.c"),
            Object(NonMatching, "actor/npc/ac_tukimi_npc0.c"),
            Object(NonMatching, "actor/npc/ac_tukimi_npc1.c"),
            Object(NonMatching, "actor/npc/ac_tunahiki_npc0.c"),
            Object(NonMatching, "actor/npc/ac_tunahiki_npc1.c"),
            Object(NonMatching, "actor/npc/ac_turi_npc0.c"),
        ],
    ),
    Rel(
        "actor_npc_event",
        [
            Object(NonMatching, "actor/npc/event/ac_ev_angler.c"),
            Object(Matching, "actor/npc/event/ac_ev_artist.c"),
            Object(Matching, "actor/npc/event/ac_ev_broker.c"),
            Object(NonMatching, "actor/npc/event/ac_ev_broker2.c"),
            Object(Matching, "actor/npc/event/ac_ev_carpetPeddler.c"),
            Object(Matching, "actor/npc/event/ac_ev_castaway.c"),
            Object(Matching, "actor/npc/event/ac_ev_designer.c"),
            Object(Matching, "actor/npc/event/ac_ev_dokutu.c"),
            Object(Matching, "actor/npc/event/ac_ev_dozaemon.c"),
            Object(Matching, "actor/npc/event/ac_ev_ghost.c"),
            Object(Matching, "actor/npc/event/ac_ev_gypsy.c"),
            Object(Matching, "actor/npc/event/ac_ev_kabuPeddler.c"),
            Object(Matching, "actor/npc/event/ac_ev_majin.c"),
            Object(NonMatching, "actor/npc/event/ac_ev_miko.c"),
            Object(NonMatching, "actor/npc/event/ac_ev_pumpkin.c"),
            Object(Matching, "actor/npc/event/ac_ev_santa.c"),
            Object(Matching, "actor/npc/event/ac_ev_soncho.c"),
            Object(Matching, "actor/npc/event/ac_ev_soncho2.c"),
            Object(Matching, "actor/npc/event/ac_ev_speech_soncho.c"),
            Object(NonMatching, "actor/npc/event/ac_ev_turkey.c"),
            Object(NonMatching, "actor/npc/event/ac_ev_yomise.c"),
        ],
    ),
    Rel(
        "actor_tool",
        [
            Object(Matching, "actor/tool/ac_t_anrium1.c"),
            Object(Matching, "actor/tool/ac_t_bag1.c"),
            Object(Matching, "actor/tool/ac_t_bag2.c"),
            Object(Matching, "actor/tool/ac_t_biscus1.c"),
            Object(Matching, "actor/tool/ac_t_biscus2.c"),
            Object(Matching, "actor/tool/ac_t_biscus3.c"),
            Object(Matching, "actor/tool/ac_t_biscus4.c"),
            Object(Matching, "actor/tool/ac_t_cobra1.c"),
            Object(Matching, "actor/tool/ac_t_cracker.c"),
            Object(Matching, "actor/tool/ac_t_flag.c"),
            Object(Matching, "actor/tool/ac_t_hanabi.c"),
            Object(Matching, "actor/tool/ac_t_hasu1.c"),
            Object(Matching, "actor/tool/ac_t_hat1.c"),
            Object(Matching, "actor/tool/ac_t_hat2.c"),
            Object(Matching, "actor/tool/ac_t_hat3.c"),
            Object(Matching, "actor/tool/ac_t_keitai.c"),
            Object(Matching, "actor/tool/ac_t_npc_sao.c"),
            Object(Matching, "actor/tool/ac_t_pistol.c"),
            Object(Matching, "actor/tool/ac_t_rei1.c"),
            Object(Matching, "actor/tool/ac_t_rei2.c"),
            Object(Matching, "actor/tool/ac_t_tama.c"),
            Object(Matching, "actor/tool/ac_t_tumbler.c"),
            Object(Matching, "actor/tool/ac_t_umbrella.c"),
            Object(Matching, "actor/tool/ac_t_utiwa.c"),
            Object(Matching, "actor/tool/ac_t_zinnia1.c"),
            Object(Matching, "actor/tool/ac_t_zinnia2.c"),
        ],
    ),
    Rel(
        "bg_item",
        [
            Object(Matching, "bg_item/bg_cherry_item.c"),
            Object(Matching, "bg_item/bg_item.c"),
            Object(Matching, "bg_item/bg_police_item.c"),
            Object(Matching, "bg_item/bg_post_item.c"),
            Object(Matching, "bg_item/bg_winter_item.c"),
            Object(Matching, "bg_item/bg_xmas_item.c"),
        ],
    ),
    Rel(
        "effect",
        [
            Object(Matching, "effect/ef_ami_mizu.c"),
            Object(Matching, "effect/ef_anahikari.c"),
            Object(Matching, "effect/ef_ase.c"),
            Object(Matching, "effect/ef_ase2.c"),
            Object(Matching, "effect/ef_ase_ch.c"),
            Object(Matching, "effect/ef_break_axe.c"),
            Object(Matching, "effect/ef_bubu.c"),
            Object(Matching, "effect/ef_buruburu.c"),
            Object(Matching, "effect/ef_bush_happa.c"),
            Object(Matching, "effect/ef_bush_yuki.c"),
            Object(Matching, "effect/ef_car_blight.c"),
            Object(Matching, "effect/ef_car_light.c"),
            Object(Matching, "effect/ef_clacker.c"),
            Object(Matching, "effect/ef_coin.c"),
            Object(Matching, "effect/ef_dash_asimoto.c"),
            Object(Matching, "effect/ef_dig_hole.c"),
            Object(Matching, "effect/ef_dig_mud.c"),
            Object(Matching, "effect/ef_dig_scoop.c"),
            Object(Matching, "effect/ef_douzou_light.c"),
            Object(Matching, "effect/ef_doyon.c"),
            Object(NonMatching, "effect/ef_dust.c"),
            Object(Matching, "effect/ef_effect_control.c"),
            Object(Matching, "effect/ef_flash.c"),
            Object(Matching, "effect/ef_footprint.c"),
            Object(NonMatching, "effect/ef_furo_yuge.c"),
            Object(NonMatching, "effect/ef_gimonhu.c"),
            Object(NonMatching, "effect/ef_goki.c"),
            Object(NonMatching, "effect/ef_ha.c"),
            Object(Matching, "effect/ef_halloween.c"),
            Object(Matching, "effect/ef_halloween_smoke.c"),
            Object(NonMatching, "effect/ef_hanabi_botan1.c"),
            Object(NonMatching, "effect/ef_hanabi_botan2.c"),
            Object(Matching, "effect/ef_hanabi_dummy.c"),
            Object(NonMatching, "effect/ef_hanabi_hoshi.c"),
            Object(NonMatching, "effect/ef_hanabi_set.c"),
            Object(NonMatching, "effect/ef_hanabi_switch.c"),
            Object(NonMatching, "effect/ef_hanabi_yanagi.c"),
            Object(NonMatching, "effect/ef_hanabira.c"),
            Object(Matching, "effect/ef_hanatiri.c"),
            Object(NonMatching, "effect/ef_hirameki_den.c"),
            Object(NonMatching, "effect/ef_hirameki_hikari.c"),
            Object(NonMatching, "effect/ef_ikigire.c"),
            Object(Matching, "effect/ef_impact_star.c"),
            Object(NonMatching, "effect/ef_kagu_happa.c"),
            Object(NonMatching, "effect/ef_kamifubuki.c"),
            Object(NonMatching, "effect/ef_kangaeru.c"),
            Object(NonMatching, "effect/ef_kantanhu.c"),
            Object(Matching, "effect/ef_kasamizu.c"),
            Object(Matching, "effect/ef_kasamizutama.c"),
            Object(NonMatching, "effect/ef_kaze.c"),
            Object(NonMatching, "effect/ef_kaze_happa.c"),
            Object(NonMatching, "effect/ef_kigae.c"),
            Object(NonMatching, "effect/ef_kigae_light.c"),
            Object(NonMatching, "effect/ef_kikuzu.c"),
            Object(Matching, "effect/ef_killer.c"),
            Object(NonMatching, "effect/ef_kisha_kemuri.c"),
            Object(NonMatching, "effect/ef_konpu.c"),
            Object(NonMatching, "effect/ef_kpun.c"),
            Object(NonMatching, "effect/ef_kyousou_onpu.c"),
            Object(Matching, "effect/ef_lamp_light.c"),
            Object(NonMatching, "effect/ef_lovelove.c"),
            Object(NonMatching, "effect/ef_lovelove2.c"),
            Object(NonMatching, "effect/ef_lovelove_heart.c"),
            Object(Matching, "effect/ef_make_hem.c"),
            Object(NonMatching, "effect/ef_mizutama.c"),
            Object(NonMatching, "effect/ef_motiyuge.c"),
            Object(NonMatching, "effect/ef_muka.c"),
            Object(NonMatching, "effect/ef_naku.c"),
            Object(NonMatching, "effect/ef_namida.c"),
            Object(NonMatching, "effect/ef_neboke.c"),
            Object(NonMatching, "effect/ef_neboke_akubi.c"),
            Object(NonMatching, "effect/ef_neboke_awa.c"),
            Object(NonMatching, "effect/ef_night13_moon.c"),
            Object(NonMatching, "effect/ef_night15_moon.c"),
            Object(NonMatching, "effect/ef_ongen.c"),
            Object(NonMatching, "effect/ef_otikomi.c"),
            Object(Matching, "effect/ef_otosiana.c"),
            Object(Matching, "effect/ef_pun.c"),
            Object(Matching, "effect/ef_pun_sekimen.c"),
            Object(Matching, "effect/ef_pun_yuge.c"),
            Object(NonMatching, "effect/ef_reset_hole.c"),
            Object(Matching, "effect/ef_room_sunshine.c"),
            Object(Matching, "effect/ef_room_sunshine_minsect.c"),
            Object(Matching, "effect/ef_room_sunshine_museum.c"),
            Object(Matching, "effect/ef_room_sunshine_police.c"),
            Object(Matching, "effect/ef_room_sunshine_posthouse.c"),
            Object(NonMatching, "effect/ef_sandsplash.c"),
            Object(NonMatching, "effect/ef_shock.c"),
            Object(NonMatching, "effect/ef_shooting.c"),
            Object(NonMatching, "effect/ef_shooting_kira.c"),
            Object(NonMatching, "effect/ef_shooting_set.c"),
            Object(NonMatching, "effect/ef_siawase_hana.c"),
            Object(NonMatching, "effect/ef_siawase_hana_ch.c"),
            Object(NonMatching, "effect/ef_siawase_hikari.c"),
            Object(NonMatching, "effect/ef_sibuki.c"),
            Object(NonMatching, "effect/ef_situren.c"),
            Object(NonMatching, "effect/ef_slip.c"),
            Object(NonMatching, "effect/ef_slip_footprint.c"),
            Object(NonMatching, "effect/ef_soba_yuge.c"),
            Object(NonMatching, "effect/ef_steam.c"),
            Object(NonMatching, "effect/ef_string.c"),
            Object(NonMatching, "effect/ef_suisou_awa.c"),
            Object(NonMatching, "effect/ef_swing_axe.c"),
            Object(NonMatching, "effect/ef_swing_net.c"),
            Object(NonMatching, "effect/ef_swing_rod.c"),
            Object(NonMatching, "effect/ef_taberu.c"),
            Object(NonMatching, "effect/ef_takurami.c"),
            Object(NonMatching, "effect/ef_takurami_kira.c"),
            Object(NonMatching, "effect/ef_tamaire.c"),
            Object(NonMatching, "effect/ef_tape.c"),
            Object(Matching, "effect/ef_tent_lamp.c"),
            Object(NonMatching, "effect/ef_tumble.c"),
            Object(NonMatching, "effect/ef_tumble_bodyprint.c"),
            Object(NonMatching, "effect/ef_tumble_dust.c"),
            Object(NonMatching, "effect/ef_turi_hamon.c"),
            Object(NonMatching, "effect/ef_turi_hane0.c"),
            Object(NonMatching, "effect/ef_turi_hane1.c"),
            Object(NonMatching, "effect/ef_turi_mizu.c"),
            Object(NonMatching, "effect/ef_turi_suiteki.c"),
            Object(NonMatching, "effect/ef_turn_asimoto.c"),
            Object(NonMatching, "effect/ef_turn_footprint.c"),
            Object(NonMatching, "effect/ef_uranai.c"),
            Object(NonMatching, "effect/ef_wait_asimoto.c"),
            Object(NonMatching, "effect/ef_walk_asimoto.c"),
            Object(NonMatching, "effect/ef_warau.c"),
            Object(NonMatching, "effect/ef_yajirushi.c"),
            Object(Matching, "effect/ef_young_tree.c"),
            Object(Matching, "effect/ef_yukidama.c"),
            Object(Matching, "effect/ef_yukidaruma.c"),
            Object(Matching, "effect/ef_yukihane.c"),
        ],
    ),
    Rel(
        "game",
        [
            Object(Matching, "game/m_actor.c"),
            Object(Matching, "game/m_actor_dlftbls.c"),
            Object(Matching, "game/m_actor_shadow.c"),
            Object(NonMatching, "game/m_address_ovl.c"),
            Object(Matching, "game/m_all_grow.c"),
            Object(Matching, "game/m_all_grow_ovl.c"),
            Object(Matching, "game/m_bank_ovl.c"),
            Object(Matching, "game/m_banti.c"),
            Object(Matching, "game/m_bg_item.c"),
            Object(Matching, "game/m_bg_tex.c"),
            Object(Matching, "game/m_bgm.c"),
            Object(Matching, "game/m_birthday_ovl.c"),
            Object(Matching, "game/m_board_ovl.c"),
            Object(Matching, "game/m_calendar.c"),
            Object(NonMatching, "game/m_calendar_ovl.c"),
            Object(Matching, "game/m_camera2.c"),
            Object(NonMatching, "game/m_card.c"),
            Object(Matching, "game/m_catalog_ovl.c"),
            Object(Matching, "game/m_choice.c"),
            Object(Matching, "game/m_clip.c"),
            Object(Matching, "game/m_cockroach.c"),
            Object(Matching, "game/m_collision_bg.c"),
            Object(Matching, "game/m_collision_obj.c"),
            Object(Matching, "game/m_common_data.c"),
            Object(Matching, "game/m_controller.c"),
            Object(Matching, "game/m_cpak.c"),
            Object(Matching, "game/m_cpedit_ovl.c"),
            Object(NonMatching, "game/m_cpmail_ovl.c"),
            Object(NonMatching, "game/m_cporiginal_ovl.c"),
            Object(Matching, "game/m_cpwarning_ovl.c"),
            Object(Matching, "game/m_debug.c"),
            Object(Matching, "game/m_debug_display.c"),
            Object(Matching, "game/m_debug_hayakawa.c"),
            Object(Matching, "game/m_debug_mode.c"),
            Object(Matching, "game/m_demo.c"),
            Object(NonMatching, "game/m_design_ovl.c"),
            Object(Matching, "game/m_diary.c"),
            Object(NonMatching, "game/m_diary_ovl.c"),
            Object(Matching, "game/m_eappli.c"),
            Object(Matching, "game/m_editEndChk_ovl.c"),
            Object(Matching, "game/m_editor_ovl.c"),
            Object(Matching, "game/m_event.c"),
            Object(Matching, "game/m_event_map_npc.c"),
            Object(Matching, "game/m_fbdemo.c"),
            Object(Matching, "game/m_fbdemo_fade.c"),
            Object(Matching, "game/m_fbdemo_triforce.c"),
            Object(Matching, "game/m_fbdemo_wipe1.c"),
            Object(Matching, "game/m_field_assessment.c"),
            Object(Matching, "game/m_field_info.c"),
            Object(Matching, "game/m_field_make.c"),
            Object(Matching, "game/m_fishrecord.c"),
            Object(Matching, "game/m_flashrom.c"),
            Object(Matching, "game/m_font.c"),
            Object(Matching, "game/m_fuusen.c"),
            Object(Matching, "game/m_game_dlftbls.c"),
            Object(Matching, "game/m_gba_ovl.c"),
            Object(Matching, "game/m_hand_ovl.c"),
            Object(Matching, "game/m_handbill.c"),
            Object(NonMatching, "game/m_haniwa_ovl.c"),
            Object(Matching, "game/m_haniwaPortrait_ovl.c"),
            Object(Matching, "game/m_hboard_ovl.c"),
            Object(Matching, "game/m_home.c"),
            Object(Matching, "game/m_house.c"),
            Object(Matching, "game/m_huusui_room.c"),
            Object(Matching, "game/m_huusui_room_ovl.c"),
            Object(Matching, "game/m_inventory_ovl.c"),
            Object(Matching, "game/m_island.c"),
            Object(Matching, "game/m_item_name.c"),
            Object(Matching, "game/m_kabu_manager.c"),
            Object(Matching, "game/m_kankyo.c"),
            Object(Matching, "game/m_land.c"),
            Object(Matching, "game/m_ledit_ovl.c"),
            Object(Matching, "game/m_lib.c"),
            Object(Matching, "game/m_lights.c"),
            Object(Matching, "game/m_mail.c"),
            Object(Matching, "game/m_mail_check.c"),
            Object(Matching, "game/m_mail_check_ovl.c"),
            Object(Matching, "game/m_mail_password_check.c"),
            Object(NonMatching, "game/m_mailbox_ovl.c"),
            Object(Matching, "game/m_malloc.c"),
            Object(Matching, "game/m_map_ovl.c"),
            Object(Matching, "game/m_mark_room.c"),
            Object(Matching, "game/m_mark_room_ovl.c"),
            Object(Matching, "game/m_melody.c"),
            Object(Matching, "game/m_mscore_ovl.c"),
            Object(Matching, "game/m_msg.c"),
            Object(Matching, "game/m_museum.c"),
            Object(Matching, "game/m_museum_display.c"),
            Object(Matching, "game/m_mushroom.c"),
            Object(NonMatching, "game/m_music_ovl.c"),
            Object(Matching, "game/m_name_table.c"),
            Object(Matching, "game/m_needlework.c"),
            Object(Matching, "game/m_needlework_ovl.c"),
            Object(Matching, "game/m_notice.c"),
            Object(Matching, "game/m_notice_ovl.c"),
            Object(Matching, "game/m_npc.c"),
            Object(Matching, "game/m_npc_schedule.c"),
            Object(Matching, "game/m_npc_walk.c"),
            Object(Matching, "game/m_olib.c"),
            Object(Matching, "game/m_passwordChk_ovl.c"),
            Object(Matching, "game/m_passwordMake_ovl.c"),
            Object(Matching, "game/m_pause.c"),
            Object(Matching, "game/m_play.c"),
            Object(Matching, "game/m_player.c"),
            Object(Matching, "game/m_player_call.c"),
            Object(Matching, "game/m_player_lib.c"),
            Object(Matching, "game/m_police_box.c"),
            Object(Matching, "game/m_post_office.c"),
            Object(Matching, "game/m_prenmi.c"),
            Object(Matching, "game/m_private.c"),
            Object(Matching, "game/m_quest.c"),
            Object(Matching, "game/m_random_field.c"),
            Object(Matching, "game/m_random_field_ovl.c"),
            Object(Matching, "game/m_rcp.c"),
            Object(Matching, "game/m_repay_ovl.c"),
            Object(Matching, "game/m_roll_lib.c"),
            Object(Matching, "game/m_room_type.c"),
            Object(Matching, "game/m_scene.c"),
            Object(Matching, "game/m_scene_ftr.c"),
            Object(Matching, "game/m_scene_table.c"),
            Object(Matching, "game/m_select.c"),
            Object(Equivalent, "game/m_shop.c"),
            Object(Matching, "game/m_skin_matrix.c"),
            Object(Matching, "game/m_snowman.c"),
            Object(Matching, "game/m_soncho.c"),
            Object(Matching, "game/m_start_data_init.c"),
            Object(Matching, "game/m_string.c"),
            Object(Matching, "game/m_submenu.c"),
            Object(Matching, "game/m_submenu_ovl.c"),
            Object(Matching, "game/m_tag_ovl.c"),
            Object(Matching, "game/m_time.c"),
            Object(Matching, "game/m_timeIn_ovl.c"),
            Object(Matching, "game/m_titledemo.c"),
            Object(Matching, "game/m_trademark.c"),
            Object(Matching, "game/m_train_control.c"),
            Object(Matching, "game/m_vibctl.c"),
            Object(Matching, "game/m_view.c"),
            Object(Matching, "game/m_warning_ovl.c"),
            Object(Matching, "game/m_watch_my_step.c"),
        ],
    ),
    Rel(
        "system",
        [
            Object(Matching, "system/sys_dynamic.c"),
            Object(Matching, "system/sys_math.c"),
            Object(Matching, "system/sys_math3d.c"),
            Object(Matching, "system/sys_math_atan.c"),
            Object(Matching, "system/sys_matrix.c"),
            Object(Matching, "system/sys_romcheck.c"),
            Object(Matching, "system/sys_stacks.c"),
            Object(Matching, "system/sys_ucode.c"),
            Object(Matching, "system/sys_vimgr.c"),
        ],
    ),
    Rel(
        "dataobject",
        [
            Object(Matching, "data/npc/model/mdl/bev_1.c"),
            Object(Matching, "data/npc/model/tex/bev_1.c"),
            Object(Matching, "data/npc/model/mdl/ant_1.c"),
            Object(Matching, "data/npc/model/tex/ant_1.c"),
            Object(Matching, "data/npc/model/tex/ant_2.c"),
            Object(Matching, "data/npc/model/tex/ant_3.c"),
            Object(Matching, "data/npc/model/tex/ant_4.c"),
            Object(Matching, "data/npc/model/tex/ant_5.c"),
            Object(Matching, "data/npc/model/mdl/wls_1.c"),
            Object(Matching, "data/npc/model/tex/wls_1.c"),
            Object(Matching, "data/scene/BG_TEST01.c"),
            Object(Matching, "data/scene/BG_TEST01_XLU.c"),
            Object(Matching, "data/scene/broker_shop.c"),
            Object(Matching, "data/scene/buggy.c"),
            Object(Matching, "data/npc/model/mdl/bea_1.c"),
            Object(Matching, "data/npc/model/tex/bea_1.c"),
            Object(Matching, "data/npc/model/tex/bea_2.c"),
            Object(Matching, "data/npc/model/tex/bea_3.c"),
            Object(Matching, "data/npc/model/tex/bea_5.c"),
            Object(Matching, "data/npc/model/tex/bea_6.c"),
            Object(Matching, "data/npc/model/tex/bea_7.c"),
            Object(Matching, "data/npc/model/tex/bea_8.c"),
            Object(Matching, "data/npc/model/tex/bea_9.c"),
            Object(Matching, "data/npc/model/tex/bea_10.c"),
            Object(Matching, "data/field/bg/acre/bg_data.c"),
            Object(Matching, "data/field/bg/flower/obj_flower.c"),
            Object(Matching, "data/field/bg/flower/obj_flower_leaf.c"),
            Object(Matching, "data/npc/model/mdl/pbr_1.c"),
            Object(Matching, "data/npc/model/tex/pbr_1.c"),
            Object(Matching, "data/npc/model/tex/pbr_2.c"),
            Object(Matching, "data/npc/model/tex/pbr_3.c"),
            Object(Matching, "data/npc/model/tex/pbr_4.c"),
            Object(Matching, "data/npc/model/tex/pbr_5.c"),
            Object(Matching, "data/npc/model/mdl/brd_1.c"),
            Object(Matching, "data/npc/model/tex/brd_1.c"),
            Object(Matching, "data/npc/model/tex/brd_2.c"),
            Object(Matching, "data/npc/model/tex/brd_11.c"),
            Object(Matching, "data/npc/model/tex/brd_3.c"),
            Object(Matching, "data/npc/model/tex/brd_4.c"),
            Object(Matching, "data/npc/model/tex/brd_5.c"),
            Object(Matching, "data/npc/model/tex/brd_6.c"),
            Object(Matching, "data/npc/model/tex/brd_7.c"),
            Object(Matching, "data/npc/model/tex/brd_8.c"),
            Object(Matching, "data/npc/model/tex/brd_9.c"),
            Object(Matching, "data/npc/model/tex/brd_10.c"),
            Object(Matching, "data/player/BOY_part_data.c"),
            Object(Matching, "data/npc/model/mdl/fox_1.c"),
            Object(Matching, "data/npc/model/tex/fox_1.c"),
            Object(Matching, "data/npc/model/mdl/bul_1.c"),
            Object(Matching, "data/npc/model/tex/bul_1.c"),
            Object(Matching, "data/npc/model/tex/bul_2.c"),
            Object(Matching, "data/npc/model/tex/bul_3.c"),
            Object(Matching, "data/npc/model/tex/bul_4.c"),
            Object(Matching, "data/npc/model/mdl/cml_1.c"),
            Object(Matching, "data/npc/model/tex/cml_1.c"),
            Object(Matching, "data/npc/model/mdl/cat_1.c"),
            Object(Matching, "data/npc/model/tex/cat_1.c"),
            Object(Matching, "data/npc/model/tex/cat_2.c"),
            Object(Matching, "data/npc/model/tex/cat_11.c"),
            Object(Matching, "data/npc/model/tex/cat_12.c"),
            Object(Matching, "data/npc/model/tex/cat_13.c"),
            Object(Matching, "data/npc/model/tex/cat_14.c"),
            Object(Matching, "data/npc/model/tex/cat_15.c"),
            Object(Matching, "data/npc/model/tex/cat_3.c"),
            Object(Matching, "data/npc/model/tex/cat_4.c"),
            Object(Matching, "data/npc/model/tex/cat_5.c"),
            Object(Matching, "data/npc/model/tex/cat_6.c"),
            Object(Matching, "data/npc/model/tex/cat_7.c"),
            Object(Matching, "data/npc/model/tex/cat_8.c"),
            Object(Matching, "data/npc/model/tex/cat_9.c"),
            Object(Matching, "data/npc/model/tex/cat_10.c"),
            Object(Matching, "data/npc/model/mdl/chn_1.c"),
            Object(Matching, "data/npc/model/tex/chn_1.c"),
            Object(Matching, "data/npc/model/tex/chn_2.c"),
            Object(Matching, "data/npc/model/tex/chn_3.c"),
            Object(Matching, "data/npc/model/tex/chn_4.c"),
            Object(Matching, "data/npc/model/tex/chn_5.c"),
            Object(Matching, "data/npc/model/tex/chn_6.c"),
            Object(Matching, "data/npc/model/tex/chn_7.c"),
            Object(Matching, "data/npc/model/tex/chn_8.c"),
            Object(Matching, "data/npc/model/tex/chn_9.c"),
            Object(Matching, "data/npc/model/mdl/cbr_1.c"),
            Object(Matching, "data/npc/model/tex/cbr_1.c"),
            Object(Matching, "data/npc/model/tex/cbr_2.c"),
            Object(Matching, "data/npc/model/tex/cbr_11.c"),
            Object(Matching, "data/npc/model/tex/cbr_3.c"),
            Object(Matching, "data/npc/model/tex/cbr_4.c"),
            Object(Matching, "data/npc/model/tex/cbr_5.c"),
            Object(Matching, "data/npc/model/tex/cbr_6.c"),
            Object(Matching, "data/npc/model/tex/cbr_7.c"),
            Object(Matching, "data/npc/model/tex/cbr_8.c"),
            Object(Matching, "data/npc/model/tex/cbr_9.c"),
            Object(Matching, "data/npc/model/tex/cbr_10.c"),
            Object(Matching, "data/combi/data_combi.c"),
            Object(Matching, "data/npc/model/mdl/rcc_1.c"),
            Object(Matching, "data/npc/model/tex/rcc_1.c"),
            Object(Matching, "data/npc/model/mdl/cow_1.c"),
            Object(Matching, "data/npc/model/tex/cow_1.c"),
            Object(Matching, "data/npc/model/tex/cow_2.c"),
            Object(Matching, "data/npc/model/tex/cow_3.c"),
            Object(Matching, "data/npc/model/tex/cow_4.c"),
            Object(Matching, "data/npc/model/mdl/crd_1.c"),
            Object(Matching, "data/npc/model/tex/crd_1.c"),
            Object(Matching, "data/npc/model/tex/crd_2.c"),
            Object(Matching, "data/npc/model/tex/crd_3.c"),
            Object(Matching, "data/npc/model/tex/crd_4.c"),
            Object(Matching, "data/npc/model/mdl/owl_1.c"),
            Object(Matching, "data/npc/model/tex/owl_1.c"),
            Object(Matching, "data/npc/model/mdl/rcd_1.c"),
            Object(Matching, "data/npc/model/tex/rcd_1.c"),
            Object(Matching, "data/npc/model/mdl/grf_1.c"),
            Object(Matching, "data/npc/model/tex/grf_1.c"),
            Object(Matching, "data/npc/model/mdl/dog_1.c"),
            Object(Matching, "data/npc/model/tex/dog_1.c"),
            Object(Matching, "data/npc/model/tex/dog_2.c"),
            Object(Matching, "data/npc/model/tex/dog_3.c"),
            Object(Matching, "data/npc/model/tex/dog_4.c"),
            Object(Matching, "data/npc/model/tex/dog_5.c"),
            Object(Matching, "data/npc/model/tex/dog_6.c"),
            Object(Matching, "data/npc/model/tex/dog_7.c"),
            Object(Matching, "data/npc/model/tex/dog_8.c"),
            Object(Matching, "data/npc/model/tex/dog_9.c"),
            Object(Matching, "data/npc/model/tex/dog_10.c"),
            Object(Matching, "data/npc/model/mdl/seg_1.c"),
            Object(Matching, "data/npc/model/tex/seg_1.c"),
            Object(Matching, "data/npc/model/mdl/duk_1.c"),
            Object(Matching, "data/npc/model/tex/duk_1.c"),
            Object(Matching, "data/npc/model/tex/duk_2.c"),
            Object(Matching, "data/npc/model/tex/duk_11.c"),
            Object(Matching, "data/npc/model/tex/duk_3.c"),
            Object(Matching, "data/npc/model/tex/duk_4.c"),
            Object(Matching, "data/npc/model/tex/duk_5.c"),
            Object(Matching, "data/npc/model/tex/duk_6.c"),
            Object(Matching, "data/npc/model/tex/duk_7.c"),
            Object(Matching, "data/npc/model/tex/duk_8.c"),
            Object(Matching, "data/npc/model/tex/duk_9.c"),
            Object(Matching, "data/npc/model/tex/duk_10.c"),
            Object(Matching, "data/scene/event_notification.c"),
            Object(Matching, "data/npc/model/mdl/elp_1.c"),
            Object(Matching, "data/npc/model/tex/elp_1.c"),
            Object(Matching, "data/npc/model/tex/elp_2.c"),
            Object(Matching, "data/npc/model/tex/elp_3.c"),
            Object(Matching, "data/npc/model/tex/elp_4.c"),
            Object(Matching, "data/npc/model/tex/elp_5.c"),
            Object(Matching, "data/npc/model/tex/elp_6.c"),
            Object(Matching, "data/npc/model/tex/elp_7.c"),
            Object(Matching, "data/scene/fg_tool_in.c"),
            Object(Matching, "data/scene/field_tool_field.c"),
            Object(Matching, "data/npc/model/mdl/flg_1.c"),
            Object(Matching, "data/npc/model/tex/flg_1.c"),
            Object(Matching, "data/npc/model/tex/flg_2.c"),
            Object(Matching, "data/npc/model/tex/flg_11.c"),
            Object(Matching, "data/npc/model/tex/flg_12.c"),
            Object(Matching, "data/npc/model/tex/flg_13.c"),
            Object(Matching, "data/npc/model/tex/flg_3.c"),
            Object(Matching, "data/npc/model/tex/flg_4.c"),
            Object(Matching, "data/npc/model/tex/flg_5.c"),
            Object(Matching, "data/npc/model/tex/flg_6.c"),
            Object(Matching, "data/npc/model/tex/flg_7.c"),
            Object(Matching, "data/npc/model/tex/flg_8.c"),
            Object(Matching, "data/npc/model/tex/flg_9.c"),
            Object(Matching, "data/npc/model/tex/flg_10.c"),
            Object(Matching, "data/npc/model/mdl/rcf_1.c"),
            Object(Matching, "data/npc/model/tex/rcf_1.c"),
            Object(Matching, "data/npc/model/mdl/gst_1.c"),
            Object(Matching, "data/npc/model/tex/gst_1.c"),
            Object(Matching, "data/npc/model/mdl/goa_1.c"),
            Object(Matching, "data/npc/model/tex/goa_1.c"),
            Object(Matching, "data/npc/model/tex/goa_2.c"),
            Object(Matching, "data/npc/model/tex/goa_3.c"),
            Object(Matching, "data/npc/model/tex/goa_4.c"),
            Object(Matching, "data/npc/model/tex/goa_5.c"),
            Object(Matching, "data/npc/model/tex/goa_6.c"),
            Object(Matching, "data/npc/model/mdl/gor_1.c"),
            Object(Matching, "data/npc/model/tex/gor_1.c"),
            Object(Matching, "data/npc/model/tex/gor_2.c"),
            Object(Matching, "data/npc/model/tex/gor_3.c"),
            Object(Matching, "data/npc/model/tex/gor_4.c"),
            Object(Matching, "data/npc/model/tex/gor_5.c"),
            Object(Matching, "data/npc/model/mdl/xct_1.c"),
            Object(Matching, "data/npc/model/tex/xct_1.c"),
            Object(Matching, "data/npc/model/mdl/bpt_1.c"),
            Object(Matching, "data/npc/model/tex/bpt_1.c"),
            Object(Matching, "data/npc/model/mdl/pkn_1.c"),
            Object(Matching, "data/npc/model/tex/pkn_1.c"),
            Object(Matching, "data/npc/model/mdl/hem_1.c"),
            Object(Matching, "data/npc/model/tex/hem_1.c"),
            Object(Matching, "data/npc/model/mdl/hip_1.c"),
            Object(Matching, "data/npc/model/tex/hip_1.c"),
            Object(Matching, "data/npc/model/tex/hip_2.c"),
            Object(Matching, "data/npc/model/tex/hip_3.c"),
            Object(Matching, "data/npc/model/tex/hip_4.c"),
            Object(Matching, "data/npc/model/tex/hip_5.c"),
            Object(Matching, "data/npc/model/tex/hip_6.c"),
            Object(Matching, "data/npc/model/tex/hip_7.c"),
            Object(Matching, "data/npc/model/mdl/hrs_1.c"),
            Object(Matching, "data/npc/model/tex/hrs_1.c"),
            Object(Matching, "data/npc/model/tex/hrs_2.c"),
            Object(Matching, "data/npc/model/tex/hrs_3.c"),
            Object(Matching, "data/npc/model/tex/hrs_4.c"),
            Object(Matching, "data/npc/model/tex/hrs_5.c"),
            Object(Matching, "data/npc/model/tex/hrs_6.c"),
            Object(Matching, "data/npc/model/tex/hrs_7.c"),
            Object(Matching, "data/npc/model/tex/hrs_8.c"),
            Object(Matching, "data/npc/model/mdl/plj_1.c"),
            Object(Matching, "data/npc/model/tex/plj_1.c"),
            Object(Matching, "data/npc/model/mdl/xsq_1.c"),
            Object(Matching, "data/npc/model/tex/xsq_1.c"),
            Object(Matching, "data/item/item_name.c"),
            Object(Matching, "data/scene/kamakura.c"),
            Object(Matching, "data/npc/model/mdl/boa_1.c"),
            Object(Matching, "data/npc/model/tex/boa_1.c"),
            Object(Matching, "data/npc/model/mdl/kgr_1.c"),
            Object(Matching, "data/npc/model/tex/kgr_1.c"),
            Object(Matching, "data/npc/model/tex/kgr_2.c"),
            Object(Matching, "data/npc/model/tex/kgr_3.c"),
            Object(Matching, "data/npc/model/tex/kgr_4.c"),
            Object(Matching, "data/npc/model/tex/kgr_5.c"),
            Object(Matching, "data/npc/model/tex/kgr_6.c"),
            Object(Matching, "data/npc/model/mdl/fob_1.c"),
            Object(Matching, "data/npc/model/tex/fob_1.c"),
            Object(Matching, "data/npc/model/mdl/kal_1.c"),
            Object(Matching, "data/npc/model/tex/kal_1.c"),
            Object(Matching, "data/npc/model/tex/kal_2.c"),
            Object(Matching, "data/npc/model/tex/kal_3.c"),
            Object(Matching, "data/npc/model/tex/kal_4.c"),
            Object(Matching, "data/npc/model/tex/kal_5.c"),
            Object(Matching, "data/npc/model/tex/kal_6.c"),
            Object(Matching, "data/scene/lighthouse.c"),
            Object(Matching, "data/npc/model/mdl/lon_1.c"),
            Object(Matching, "data/npc/model/tex/lon_1.c"),
            Object(Matching, "data/npc/model/tex/lon_2.c"),
            Object(Matching, "data/npc/model/tex/lon_3.c"),
            Object(Matching, "data/npc/model/tex/lon_4.c"),
            Object(Matching, "data/scene/museum_entrance.c"),
            Object(Matching, "data/scene/museum_fish.c"),
            Object(Matching, "data/scene/museum_fossil.c"),
            Object(Matching, "data/scene/museum_insect.c"),
            Object(Matching, "data/scene/museum_picture.c"),
            Object(Matching, "data/npc/model/mdl/mos_1.c"),
            Object(Matching, "data/npc/model/tex/mos_1.c"),
            Object(Matching, "data/npc/model/mdl/mol_1.c"),
            Object(Matching, "data/npc/model/tex/mol_1.c"),
            Object(Matching, "data/npc/model/mdl/lrc_1.c"),
            Object(Matching, "data/npc/model/tex/lrc_1.c"),
            Object(Matching, "data/npc/model/mdl/mka_1.c"),
            Object(Matching, "data/npc/model/tex/mka_1.c"),
            Object(Matching, "data/npc/model/mdl/mus_1.c"),
            Object(Matching, "data/npc/model/tex/mus_1.c"),
            Object(Matching, "data/npc/model/tex/mus_2.c"),
            Object(Matching, "data/npc/model/tex/mus_3.c"),
            Object(Matching, "data/npc/model/tex/mus_4.c"),
            Object(Matching, "data/npc/model/tex/mus_5.c"),
            Object(Matching, "data/npc/model/tex/mus_6.c"),
            Object(Matching, "data/npc/model/tex/mus_7.c"),
            Object(Matching, "data/npc/model/tex/mus_8.c"),
            Object(Matching, "data/npc/model/tex/mus_9.c"),
            Object(Matching, "data/npc/model/tex/mus_10.c"),
            Object(Matching, "data/model/mural/obj_mural.c"),
            Object(Matching, "data/scene/NEEDLEWORK.c"),
            Object(Matching, "data/scene/npc_room01.c"),
            Object(Matching, "data/scene/npc_room_island.c"),
            Object(Matching, "data/npc/model/mdl/hgh_1.c"),
            Object(Matching, "data/npc/model/tex/hgh_1.c"),
            Object(Matching, "data/npc/model/mdl/hgs_1.c"),
            Object(Matching, "data/npc/model/tex/hgs_1.c"),
            Object(Matching, "data/npc/default_list.c"),
            Object(Matching, "data/npc/npc_draw_data.c"),
            Object(Matching, "data/npc/grow_list.c"),
            Object(Matching, "data/npc/house_list.c"),
            Object(Matching, "data/npc/model/mdl/oct_1.c"),
            Object(Matching, "data/npc/model/tex/oct_1.c"),
            Object(Matching, "data/npc/model/mdl/ost_1.c"),
            Object(Matching, "data/npc/model/tex/ost_1.c"),
            Object(Matching, "data/npc/model/tex/ost_2.c"),
            Object(Matching, "data/npc/model/tex/ost_3.c"),
            Object(Matching, "data/npc/model/tex/ost_4.c"),
            Object(Matching, "data/scene/player_room_island.c"),
            Object(Matching, "data/scene/player_room_ll1.c"),
            Object(Matching, "data/scene/player_room_ll2.c"),
            Object(Matching, "data/scene/player_room_l.c"),
            Object(Matching, "data/scene/player_room_m.c"),
            Object(Matching, "data/scene/player_room_s.c"),
            Object(Matching, "data/scene/PLAYER_SELECT2.c"),
            Object(Matching, "data/scene/PLAYER_SELECT3.c"),
            Object(Matching, "data/scene/PLAYER_SELECT4.c"),
            Object(Matching, "data/scene/player_select.c"),
            Object(Matching, "data/scene/police_box.c"),
            Object(Matching, "data/scene/post_office.c"),
            Object(Matching, "data/scene/p_room_bm_ll1.c"),
            Object(Matching, "data/scene/p_room_bm_l.c"),
            Object(Matching, "data/scene/p_room_bm_m.c"),
            Object(Matching, "data/scene/p_room_bm_s.c"),
            Object(Matching, "data/npc/model/mdl/pgn_1.c"),
            Object(Matching, "data/npc/model/tex/pgn_1.c"),
            Object(Matching, "data/npc/model/tex/pgn_2.c"),
            Object(Matching, "data/npc/model/tex/pgn_3.c"),
            Object(Matching, "data/npc/model/tex/pgn_4.c"),
            Object(Matching, "data/npc/model/tex/pgn_5.c"),
            Object(Matching, "data/npc/model/tex/pgn_6.c"),
            Object(Matching, "data/npc/model/tex/pgn_7.c"),
            Object(Matching, "data/npc/model/tex/pgn_8.c"),
            Object(Matching, "data/npc/model/mdl/pig_1.c"),
            Object(Matching, "data/npc/model/tex/pig_1.c"),
            Object(Matching, "data/npc/model/tex/pig_2.c"),
            Object(Matching, "data/npc/model/tex/pig_11.c"),
            Object(Matching, "data/npc/model/tex/pig_3.c"),
            Object(Matching, "data/npc/model/tex/pig_4.c"),
            Object(Matching, "data/npc/model/tex/pig_5.c"),
            Object(Matching, "data/npc/model/tex/pig_6.c"),
            Object(Matching, "data/npc/model/tex/pig_7.c"),
            Object(Matching, "data/npc/model/tex/pig_8.c"),
            Object(Matching, "data/npc/model/tex/pig_9.c"),
            Object(Matching, "data/npc/model/tex/pig_10.c"),
            Object(Matching, "data/npc/model/mdl/pla_1.c"),
            Object(Matching, "data/npc/model/mdl/plc_1.c"),
            Object(Matching, "data/npc/model/tex/plc_1.c"),
            Object(Matching, "data/npc/model/tex/pla_1.c"),
            Object(Matching, "data/npc/model/mdl/pga_1.c"),
            Object(Matching, "data/npc/model/tex/pga_1.c"),
            Object(Matching, "data/npc/model/mdl/pgb_1.c"),
            Object(Matching, "data/npc/model/tex/pgb_1.c"),
            Object(Matching, "data/npc/model/mdl/plb_1.c"),
            Object(Matching, "data/npc/model/tex/plb_1.c"),
            Object(Matching, "data/npc/model/mdl/rbt_1.c"),
            Object(Matching, "data/npc/model/tex/rbt_1.c"),
            Object(Matching, "data/npc/model/tex/rbt_2.c"),
            Object(Matching, "data/npc/model/tex/rbt_11.c"),
            Object(Matching, "data/npc/model/tex/rbt_3.c"),
            Object(Matching, "data/npc/model/tex/rbt_4.c"),
            Object(Matching, "data/npc/model/tex/rbt_5.c"),
            Object(Matching, "data/npc/model/tex/rbt_6.c"),
            Object(Matching, "data/npc/model/tex/rbt_7.c"),
            Object(Matching, "data/npc/model/tex/rbt_8.c"),
            Object(Matching, "data/npc/model/tex/rbt_9.c"),
            Object(Matching, "data/npc/model/tex/rbt_10.c"),
            Object(Matching, "data/npc/model/mdl/mob_1.c"),
            Object(Matching, "data/npc/model/tex/mob_1.c"),
            Object(Matching, "data/npc/model/mdl/rhn_1.c"),
            Object(Matching, "data/npc/model/tex/rhn_1.c"),
            Object(Matching, "data/npc/model/tex/rhn_2.c"),
            Object(Matching, "data/npc/model/tex/rhn_3.c"),
            Object(Matching, "data/npc/model/tex/rhn_4.c"),
            Object(Matching, "data/scene/shop01.c"),
            Object(Matching, "data/scene/shop02.c"),
            Object(Matching, "data/scene/shop03.c"),
            Object(Matching, "data/scene/shop04_1f.c"),
            Object(Matching, "data/scene/shop04_2f.c"),
            Object(Matching, "data/scene/start_demo1.c"),
            Object(Matching, "data/scene/start_demo2.c"),
            Object(Matching, "data/scene/start_demo3.c"),
            Object(Matching, "data/npc/model/mdl/snt_1.c"),
            Object(Matching, "data/npc/model/tex/snt_1.c"),
            Object(Matching, "data/npc/model/mdl/wip_1.c"),
            Object(Matching, "data/npc/model/tex/wip_1.c"),
            Object(Matching, "data/npc/model/mdl/shp_1.c"),
            Object(Matching, "data/npc/model/tex/shp_1.c"),
            Object(Matching, "data/npc/model/tex/shp_2.c"),
            Object(Matching, "data/npc/model/tex/shp_3.c"),
            Object(Matching, "data/npc/model/tex/shp_4.c"),
            Object(Matching, "data/npc/model/tex/shp_5.c"),
            Object(Matching, "data/npc/model/tex/shp_6.c"),
            Object(Matching, "data/npc/model/mdl/rcn_1.c"),
            Object(Matching, "data/npc/model/tex/rcn_1.c"),
            Object(Matching, "data/npc/model/mdl/kab_1.c"),
            Object(Matching, "data/npc/model/tex/kab_1.c"),
            Object(Matching, "data/npc/model/mdl/ttl_1.c"),
            Object(Matching, "data/npc/model/tex/ttl_1.c"),
            Object(Matching, "data/npc/model/mdl/squ_1.c"),
            Object(Matching, "data/npc/model/tex/squ_1.c"),
            Object(Matching, "data/npc/model/tex/squ_2.c"),
            Object(Matching, "data/npc/model/tex/squ_11.c"),
            Object(Matching, "data/npc/model/tex/squ_3.c"),
            Object(Matching, "data/npc/model/tex/squ_4.c"),
            Object(Matching, "data/npc/model/tex/squ_5.c"),
            Object(Matching, "data/npc/model/tex/squ_6.c"),
            Object(Matching, "data/npc/model/tex/squ_7.c"),
            Object(Matching, "data/npc/model/tex/squ_8.c"),
            Object(Matching, "data/npc/model/tex/squ_9.c"),
            Object(Matching, "data/npc/model/tex/squ_10.c"),
            Object(Matching, "data/npc/model/mdl/mnk_1.c"),
            Object(Matching, "data/npc/model/tex/mnk_1.c"),
            Object(Matching, "data/npc/model/mdl/rcs_1.c"),
            Object(Matching, "data/npc/model/tex/rcs_1.c"),
            Object(Matching, "data/scene/tent.c"),
            Object(Matching, "data/scene/test_fd_npc_land.c"),
            Object(Matching, "data/scene/water_test.c"),
            Object(Matching, "data/scene/test_step01.c"),
            Object(Matching, "data/scene/title_demo.c"),
            Object(Matching, "data/scene/test01.c"),
            Object(Matching, "data/scene/test02.c"),
            Object(Matching, "data/scene/test03.c"),
            Object(Matching, "data/scene/test04.c"),
            Object(Matching, "data/scene/test05.c"),
            Object(Matching, "data/npc/model/mdl/tig_1.c"),
            Object(Matching, "data/npc/model/tex/tig_1.c"),
            Object(Matching, "data/npc/model/tex/tig_2.c"),
            Object(Matching, "data/npc/model/tex/tig_3.c"),
            Object(Matching, "data/npc/model/tex/tig_4.c"),
            Object(Matching, "data/titledemo/pact0.c"),
            Object(Matching, "data/titledemo/pact1.c"),
            Object(Matching, "data/titledemo/pact2.c"),
            Object(Matching, "data/titledemo/pact3.c"),
            Object(Matching, "data/titledemo/pact4.c"),
            Object(Matching, "data/npc/model/mdl/end_1.c"),
            Object(Matching, "data/npc/model/tex/end_1.c"),
            Object(Matching, "data/npc/model/mdl/tuk_1.c"),
            Object(Matching, "data/npc/model/tex/tuk_1.c"),
            Object(Matching, "data/npc/model/mdl/wol_1.c"),
            Object(Matching, "data/npc/model/tex/wol_1.c"),
            Object(Matching, "data/npc/model/tex/wol_2.c"),
            Object(Matching, "data/npc/model/tex/wol_3.c"),
            Object(Matching, "data/npc/model/tex/wol_4.c"),
            Object(Matching, "data/npc/model/tex/wol_5.c"),
            Object(Matching, "data/npc/model/tex/wol_6.c"),
            Object(Matching, "data/field/bg/beach_pal.c"),
            Object(Matching, "data/field/bg/acre/grd_yamishop/grd_yamishop.c"),
            Object(Matching, "data/field/bg/acre/grd_post_office/grd_post_office.c"),
            Object(Matching, "data/field/bg/acre/tmp4/tmp4.c"),
            Object(Matching, "data/field/bg/acre/tmpr4/tmpr4_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/tmpr4/tmpr4.c"),
            Object(Matching, "data/field/bg/acre/tmp3/tmp3.c"),
            Object(Matching, "data/field/bg/acre/tmpr3/tmpr3_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/tmpr3/tmpr3.c"),
            Object(Matching, "data/field/bg/acre/tmp/tmp.c"),
            Object(Matching, "data/field/bg/acre/tmpr/tmpr_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/tmpr/tmpr.c"),
            Object(Matching, "data/field/bg/acre/tmp2/tmp2.c"),
            Object(Matching, "data/field/bg/acre/tmpr2/tmpr2_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/tmpr2/tmpr2.c"),
            Object(Matching, "data/field/bg/bush_pal.c"),
            Object(Matching, "data/field/bg/cliff_pal.c"),
            Object(Matching, "data/field/bg/earth_pal.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c1_1/grd_s_c1_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c1_2/grd_s_c1_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c1_3/grd_s_c1_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c1_4/grd_s_c1_4.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c1_5/grd_s_c1_5.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c1_r1_1/grd_s_c1_r1_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c1_r1_1/grd_s_c1_r1_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c1_r1_2/grd_s_c1_r1_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c1_r1_2/grd_s_c1_r1_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c1_r1_3/grd_s_c1_r1_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c1_r1_3/grd_s_c1_r1_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c1_r2_1/grd_s_c1_r2_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c1_r2_1/grd_s_c1_r2_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c1_r2_2/grd_s_c1_r2_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c1_r2_2/grd_s_c1_r2_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c1_r2_3/grd_s_c1_r2_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c1_r2_3/grd_s_c1_r2_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c1_r3_1/grd_s_c1_r3_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c1_r3_1/grd_s_c1_r3_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c1_r3_2/grd_s_c1_r3_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c1_r3_2/grd_s_c1_r3_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c1_r3_3/grd_s_c1_r3_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c1_r3_3/grd_s_c1_r3_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c1_s_1/grd_s_c1_s_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c1_s_2/grd_s_c1_s_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c1_s_3/grd_s_c1_s_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c1_s_4/grd_s_c1_s_4.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c2_1/grd_s_c2_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c2_2/grd_s_c2_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c2_3/grd_s_c2_3_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c2_3/grd_s_c2_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c2_r1_1/grd_s_c2_r1_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c2_r1_1/grd_s_c2_r1_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c2_r1_2/grd_s_c2_r1_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c2_r1_2/grd_s_c2_r1_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c2_r2_1/grd_s_c2_r2_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c2_r2_1/grd_s_c2_r2_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c2_r2_2/grd_s_c2_r2_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c2_r2_2/grd_s_c2_r2_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c2_s_1/grd_s_c2_s_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c2_s_2/grd_s_c2_s_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c2_s_3/grd_s_c2_s_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c3_1/grd_s_c3_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c3_2/grd_s_c3_2_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c3_2/grd_s_c3_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c3_3/grd_s_c3_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c3_r1_1/grd_s_c3_r1_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c3_r1_1/grd_s_c3_r1_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c3_r1_2/grd_s_c3_r1_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c3_r1_2/grd_s_c3_r1_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c3_r2_1/grd_s_c3_r2_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c3_r2_1/grd_s_c3_r2_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c3_r2_2/grd_s_c3_r2_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c3_r2_2/grd_s_c3_r2_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c3_s_1/grd_s_c3_s_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c3_s_1/grd_s_c3_s_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c4_1/grd_s_c4_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c4_2/grd_s_c4_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c4_3/grd_s_c4_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c4_r1_1/grd_s_c4_r1_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c4_r1_1/grd_s_c4_r1_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c4_r1_2/grd_s_c4_r1_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c4_r1_2/grd_s_c4_r1_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c4_r2_1/grd_s_c4_r2_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c4_r2_1/grd_s_c4_r2_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c4_r2_2/grd_s_c4_r2_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c4_r2_2/grd_s_c4_r2_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c4_r3_1/grd_s_c4_r3_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c4_r3_1/grd_s_c4_r3_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c4_r3_2/grd_s_c4_r3_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c4_r3_2/grd_s_c4_r3_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c4_s_1/grd_s_c4_s_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c4_s_2/grd_s_c4_s_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c5_1/grd_s_c5_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c5_2/grd_s_c5_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c5_3/grd_s_c5_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c5_r1_1/grd_s_c5_r1_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c5_r1_1/grd_s_c5_r1_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c5_r1_2/grd_s_c5_r1_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c5_r1_2/grd_s_c5_r1_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c5_r2_1/grd_s_c5_r2_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c5_r2_1/grd_s_c5_r2_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c5_r2_2/grd_s_c5_r2_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c5_r2_2/grd_s_c5_r2_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c5_r3_1/grd_s_c5_r3_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c5_r3_1/grd_s_c5_r3_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c5_r3_2/grd_s_c5_r3_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c5_r3_2/grd_s_c5_r3_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c5_s_1/grd_s_c5_s_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c5_s_2/grd_s_c5_s_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c6_1/grd_s_c6_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c6_2/grd_s_c6_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c6_3/grd_s_c6_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c6_r1_1/grd_s_c6_r1_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c6_r1_1/grd_s_c6_r1_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c6_r1_2/grd_s_c6_r1_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c6_r1_2/grd_s_c6_r1_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c6_r3_1/grd_s_c6_r3_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c6_r3_1/grd_s_c6_r3_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c6_s_1/grd_s_c6_s_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c7_1/grd_s_c7_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c7_2/grd_s_c7_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c7_3/grd_s_c7_3_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c7_3/grd_s_c7_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c7_r1_1/grd_s_c7_r1_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c7_r1_1/grd_s_c7_r1_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c7_r1_2/grd_s_c7_r1_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c7_r1_2/grd_s_c7_r1_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c7_r3_1/grd_s_c7_r3_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c7_r3_1/grd_s_c7_r3_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_c7_r3_2/grd_s_c7_r3_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_c7_r3_2/grd_s_c7_r3_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c7_s_1/grd_s_c7_s_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c7_s_2/grd_s_c7_s_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_c7_s_3/grd_s_c7_s_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_e1_1/grd_s_e1_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_e1_r1_1/grd_s_e1_r1_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_e1_r1_1/grd_s_e1_r1_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_e2_1/grd_s_e2_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_e2_c1_1/grd_s_e2_c1_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_e2_m_1/grd_s_e2_m_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_e2_o_1/grd_s_e2_o_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_e2_t_1/grd_s_e2_t_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_e3_1/grd_s_e3_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_e3_c1_1/grd_s_e3_c1_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_e3_m_1/grd_s_e3_m_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_e3_o_1/grd_s_e3_o_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_e3_t_1/grd_s_e3_t_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_e4_1/grd_s_e4_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_e5_1/grd_s_e5_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_1/grd_s_f_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_10/grd_s_f_10.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_2/grd_s_f_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_3/grd_s_f_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_4/grd_s_f_4_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_4/grd_s_f_4.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_5/grd_s_f_5_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_5/grd_s_f_5.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_6/grd_s_f_6_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_6/grd_s_f_6.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_7/grd_s_f_7.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_8/grd_s_f_8.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_9/grd_s_f_9.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_ko_1/grd_s_f_ko_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_ko_2/grd_s_f_ko_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_f_ko_3/grd_s_f_ko_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_f_ko_3/grd_s_f_ko_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_mh_1/grd_s_f_mh_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_mh_2/grd_s_f_mh_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_mh_3/grd_s_f_mh_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_mu_1/grd_s_f_mu_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_mu_2/grd_s_f_mu_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_f_mu_3/grd_s_f_mu_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_f_mu_3/grd_s_f_mu_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_pk_1/grd_s_f_pk_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_pk_2/grd_s_f_pk_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_f_pk_3/grd_s_f_pk_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_hole_test/grd_s_hole_test.c"),
            Object(Matching, "data/field/bg/acre/grd_s_il_1/grd_s_il_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_il_2/grd_s_il_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_il_3/grd_s_il_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_il_4/grd_s_il_4.c"),
            Object(Matching, "data/field/bg/acre/grd_s_ir_1/grd_s_ir_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_ir_2/grd_s_ir_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_ir_3/grd_s_ir_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_ir_4/grd_s_ir_4.c"),
            Object(Matching, "data/field/bg/acre/grd_s_m_1/grd_s_m_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_m_10/grd_s_m_10.c"),
            Object(Matching, "data/field/bg/acre/grd_s_m_2/grd_s_m_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_m_3/grd_s_m_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_m_4/grd_s_m_4.c"),
            Object(Matching, "data/field/bg/acre/grd_s_m_5/grd_s_m_5.c"),
            Object(Matching, "data/field/bg/acre/grd_s_m_6/grd_s_m_6.c"),
            Object(Matching, "data/field/bg/acre/grd_s_m_7/grd_s_m_7.c"),
            Object(Matching, "data/field/bg/acre/grd_s_m_8/grd_s_m_8.c"),
            Object(Matching, "data/field/bg/acre/grd_s_m_9/grd_s_m_9.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_m_r1_1/grd_s_m_r1_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_m_r1_1/grd_s_m_r1_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_m_r1_2/grd_s_m_r1_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_m_r1_2/grd_s_m_r1_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_m_r1_3/grd_s_m_r1_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_m_r1_3/grd_s_m_r1_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_m_r1_4/grd_s_m_r1_4_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_m_r1_4/grd_s_m_r1_4.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_m_r1_5/grd_s_m_r1_5_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_m_r1_5/grd_s_m_r1_5.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_m_r1_b_1/grd_s_m_r1_b_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_m_r1_b_1/grd_s_m_r1_b_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_m_r1_b_2/grd_s_m_r1_b_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_m_r1_b_2/grd_s_m_r1_b_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_m_r1_b_3/grd_s_m_r1_b_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_m_r1_b_3/grd_s_m_r1_b_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_m_ta_1/grd_s_m_ta_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_m_ta_1/grd_s_m_ta_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_m_ta_2/grd_s_m_ta_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_m_ta_2/grd_s_m_ta_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_m_ta_3/grd_s_m_ta_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_m_ta_3/grd_s_m_ta_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_m_wf_1/grd_s_m_wf_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_m_wf_1/grd_s_m_wf_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_m_wf_2/grd_s_m_wf_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_m_wf_2/grd_s_m_wf_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_m_wf_3/grd_s_m_wf_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_m_wf_3/grd_s_m_wf_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_1/grd_s_o_1_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_1/grd_s_o_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_10/grd_s_o_10_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_10/grd_s_o_10.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_2/grd_s_o_2_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_2/grd_s_o_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_3/grd_s_o_3_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_3/grd_s_o_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_4/grd_s_o_4_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_4/grd_s_o_4.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_5/grd_s_o_5_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_5/grd_s_o_5.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_6/grd_s_o_6_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_6/grd_s_o_6.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_7/grd_s_o_7_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_7/grd_s_o_7.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_8/grd_s_o_8_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_8/grd_s_o_8.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_9/grd_s_o_9_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_9/grd_s_o_9.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_i_1/grd_s_o_i_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_i_2/grd_s_o_i_2_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_o_i_2/grd_s_o_i_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_o_r1_1/grd_s_o_r1_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_o_r1_1/grd_s_o_r1_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_o_r1_2/grd_s_o_r1_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_o_r1_2/grd_s_o_r1_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_o_r1_3/grd_s_o_r1_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_o_r1_3/grd_s_o_r1_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_o_r1_4/grd_s_o_r1_4_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_o_r1_4/grd_s_o_r1_4.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_o_r1_5/grd_s_o_r1_5_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_o_r1_5/grd_s_o_r1_5.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_o_r1_b_1/grd_s_o_r1_b_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_o_r1_b_1/grd_s_o_r1_b_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_o_r1_b_2/grd_s_o_r1_b_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_o_r1_b_2/grd_s_o_r1_b_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_o_r1_b_3/grd_s_o_r1_b_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_o_r1_b_3/grd_s_o_r1_b_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_o_ta_1/grd_s_o_ta_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_o_ta_1/grd_s_o_ta_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_o_ta_2/grd_s_o_ta_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_o_ta_2/grd_s_o_ta_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_o_ta_3/grd_s_o_ta_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_o_ta_3/grd_s_o_ta_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_o_wf_1/grd_s_o_wf_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_o_wf_1/grd_s_o_wf_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_o_wf_2/grd_s_o_wf_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_o_wf_2/grd_s_o_wf_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_o_wf_3/grd_s_o_wf_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_o_wf_3/grd_s_o_wf_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r1_1/grd_s_r1_1_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r1_1/grd_s_r1_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r1_2/grd_s_r1_2_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r1_2/grd_s_r1_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r1_3/grd_s_r1_3_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r1_3/grd_s_r1_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r1_4/grd_s_r1_4_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r1_4/grd_s_r1_4.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r1_b_1/grd_s_r1_b_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r1_b_1/grd_s_r1_b_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r1_b_2/grd_s_r1_b_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r1_b_2/grd_s_r1_b_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r1_b_3/grd_s_r1_b_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r1_b_3/grd_s_r1_b_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r1_p_1/grd_s_r1_p_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r1_p_1/grd_s_r1_p_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r2_1/grd_s_r2_1_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r2_1/grd_s_r2_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r2_2/grd_s_r2_2_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r2_2/grd_s_r2_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r2_3/grd_s_r2_3_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r2_3/grd_s_r2_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r2_4/grd_s_r2_4_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r2_4/grd_s_r2_4.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r2_b_1/grd_s_r2_b_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r2_b_1/grd_s_r2_b_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r2_b_2/grd_s_r2_b_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r2_b_2/grd_s_r2_b_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r2_b_3/grd_s_r2_b_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r2_b_3/grd_s_r2_b_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r2_p_1/grd_s_r2_p_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r2_p_1/grd_s_r2_p_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r3_1/grd_s_r3_1_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r3_1/grd_s_r3_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r3_2/grd_s_r3_2_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r3_2/grd_s_r3_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r3_3/grd_s_r3_3_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r3_3/grd_s_r3_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r3_4/grd_s_r3_4_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r3_4/grd_s_r3_4.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r3_b_1/grd_s_r3_b_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r3_b_1/grd_s_r3_b_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r3_b_2/grd_s_r3_b_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r3_b_2/grd_s_r3_b_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r3_b_3/grd_s_r3_b_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r3_b_3/grd_s_r3_b_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r3_p_1/grd_s_r3_p_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r3_p_1/grd_s_r3_p_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r4_1/grd_s_r4_1_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r4_1/grd_s_r4_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r4_2/grd_s_r4_2_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r4_2/grd_s_r4_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r4_3/grd_s_r4_3_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r4_3/grd_s_r4_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r4_b_1/grd_s_r4_b_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r4_b_1/grd_s_r4_b_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r4_b_2/grd_s_r4_b_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r4_b_2/grd_s_r4_b_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r4_p_1/grd_s_r4_p_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r4_p_1/grd_s_r4_p_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r5_1/grd_s_r5_1_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r5_1/grd_s_r5_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r5_2/grd_s_r5_2_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r5_2/grd_s_r5_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r5_3/grd_s_r5_3_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r5_3/grd_s_r5_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r5_b_1/grd_s_r5_b_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r5_b_1/grd_s_r5_b_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r5_b_2/grd_s_r5_b_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r5_b_2/grd_s_r5_b_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r5_p_1/grd_s_r5_p_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r5_p_1/grd_s_r5_p_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r6_1/grd_s_r6_1_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r6_1/grd_s_r6_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r6_2/grd_s_r6_2_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r6_2/grd_s_r6_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r6_3/grd_s_r6_3_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r6_3/grd_s_r6_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r6_b_1/grd_s_r6_b_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r6_b_1/grd_s_r6_b_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r6_b_2/grd_s_r6_b_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r6_b_2/grd_s_r6_b_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r6_p_1/grd_s_r6_p_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r6_p_1/grd_s_r6_p_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r7_1/grd_s_r7_1_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r7_1/grd_s_r7_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r7_2/grd_s_r7_2_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r7_2/grd_s_r7_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r7_3/grd_s_r7_3_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_r7_3/grd_s_r7_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r7_b_1/grd_s_r7_b_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r7_b_1/grd_s_r7_b_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r7_b_2/grd_s_r7_b_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r7_b_2/grd_s_r7_b_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_r7_p_1/grd_s_r7_p_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_r7_p_1/grd_s_r7_p_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_1/grd_s_t_1_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_1/grd_s_t_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_10/grd_s_t_10.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_2/grd_s_t_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_3/grd_s_t_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_4/grd_s_t_4_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_4/grd_s_t_4.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_5/grd_s_t_5_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_5/grd_s_t_5.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_6/grd_s_t_6.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_7/grd_s_t_7.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_8/grd_s_t_8.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_9/grd_s_t_9.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_po_1/grd_s_t_po_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_po_2/grd_s_t_po_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_t_po_3/grd_s_t_po_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_t_po_3/grd_s_t_po_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_t_r1_1/grd_s_t_r1_1_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_t_r1_1/grd_s_t_r1_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_t_r1_2/grd_s_t_r1_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_t_r1_2/grd_s_t_r1_2.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_t_r1_3/grd_s_t_r1_3_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_t_r1_3/grd_s_t_r1_3.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_t_r1_4/grd_s_t_r1_4_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_t_r1_4/grd_s_t_r1_4.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_t_r1_5/grd_s_t_r1_5_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_t_r1_5/grd_s_t_r1_5.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_sh_1/grd_s_t_sh_1.c"),
            Object(
                Matching, "data/field/bg/acre/grd_s_t_sh_2/grd_s_t_sh_2_evw_anime.c"
            ),
            Object(Matching, "data/field/bg/acre/grd_s_t_sh_2/grd_s_t_sh_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_sh_3/grd_s_t_sh_3.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_st1_1/grd_s_t_st1_1.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_st1_2/grd_s_t_st1_2.c"),
            Object(Matching, "data/field/bg/acre/grd_s_t_st1_3/grd_s_t_st1_3.c"),
            Object(Matching, "data/field/bg/acre/rom_toudai/rom_toudai.c"),
            Object(Matching, "data/submenu/map/kan_tizu.c"),
            Object(Matching, "data/submenu/map/kan_tizu2.c"),
            Object(Matching, "data/field/bg/acre/rom_museum1/rom_museum1.c"),
            Object(Matching, "data/field/bg/acre/rom_museum5/rom_museum5.c"),
            Object(Matching, "data/field/bg/acre/rom_museum2/rom_museum2.c"),
            Object(Matching, "data/field/bg/acre/rom_museum3/rom_museum3.c"),
            Object(Matching, "data/field/bg/acre/rom_tailor/rom_tailor.c"),
            Object(Matching, "data/field/bg/acre/myr_etc/myr_etc.c"),
            Object(
                Matching,
                "data/field/bg/acre/grd_player_select/grd_player_select_evw_anime.c",
            ),
            Object(
                Matching, "data/field/bg/acre/grd_player_select/grd_player_select.c"
            ),
            Object(Matching, "data/field/bg/acre/police_indoor/police_indoor.c"),
            Object(Matching, "data/field/bg/rail_pal.c"),
            Object(Matching, "data/field/bg/acre/rom_shop4_1/rom_shop4_1.c"),
            Object(Matching, "data/field/bg/acre/rom_shop4_fuku/rom_shop4_fuku.c"),
            Object(Matching, "data/field/bg/acre/rom_tent/rom_tent.c"),
            Object(Matching, "data/field/bg/acre/room01/room01.c"),
            Object(Matching, "data/field/bg/acre/rom_train_in/rom_train_in.c"),
            Object(Matching, "data/field/bg/acre/rom_uranai/rom_uranai_evw_anime.c"),
            Object(Matching, "data/field/bg/acre/rom_uranai/rom_uranai.c"),

            Object(Matching, "data/item/binsen_price.c"),
            Object(Matching, "data/item/cloth_price.c"),
            Object(Matching, "data/item/carpet_price.c"),
            Object(Matching, "data/item/wall_price.c"),
            Object(Matching, "data/item/tool_price.c"),
            Object(Matching, "data/item/plant_price.c"),
            Object(Matching, "data/item/food_price.c"),
            Object(Matching, "data/item/fish_price.c"),
            Object(Matching, "data/item/md_price.c"),
            Object(Matching, "data/item/diary_price.c"),
            Object(Matching, "data/item/insect_price.c"),
            Object(Matching, "data/item/ftr_price.c"),

            Object(Matching, "data/item/ftr_list.c"),
            Object(Matching, "data/item/binsen_list.c"),
            Object(Matching, "data/item/cloth_list.c"),
            Object(Matching, "data/item/carpet_list.c"),
            Object(Matching, "data/item/wall_list.c"),

            Object(Matching, "data/model/structure/palette/structure_pal_data.c"),
            Object(Matching, "data/model/structure/structure_pal.c"),
        ],
    ),
]

# Define our custom asset processing scripts
config.custom_build_rules = [
    {
        "name": "convert_pal16",
        "command": "$python tools/converters/pal16dis.py $in $out",
        "description": "CONVERT $symbol",
    },
    # We run the script in "scan" mode first to generate a .dd (dyndep) file
    # This allows ninja to understand what files are generated by the script
    {
        "name": "scan_pal16_chunked",
        "command": "$python tools/converters/pal16dis_chunked.py $in $base -s $stamp -d $out",
        "description": "SCAN $symbol",
    },
    {
        "name": "convert_pal16_chunked",
        "command": "$python tools/converters/pal16dis_chunked.py $in $base -s $out",
        "description": "CONVERT $symbol",
    },
    {
        "name": "convert_vtx",
        "command": "$python tools/converters/vtxdis.py $in $out",
        "description": "CONVERT $symbol",
    },
]
config.custom_build_steps = {}

# Grab the specific GameID so we can format our strings properly
version = VERSIONS[version_num]
out_dir = config.build_dir / version


# This generates the build steps needed for preprocessing
def emit_build_rule(asset):
    steps = config.custom_build_steps.setdefault("pre-compile", [])

    match asset.get("custom_type"):
        case None:
            return

        case "pal16":
            steps.append(
                {
                    "rule": "convert_pal16",
                    "inputs": out_dir / "bin" / asset["binary"],
                    "outputs": out_dir / "include" / asset["header"],
                    "variables": {
                        "symbol": asset["symbol"],
                    },
                    "implicit": Path("tools/converters/pal16dis.py"),
                }
            )

        case "pal16c":
            # Run the script in scan mode first to generate a .dd file
            input = out_dir / "bin" / asset["binary"]
            out_base = out_dir / "include" / asset["header"]
            dyndep = out_dir / "include" / f"{asset['header']}.dd"
            # We need a stamp file to use as a marker for ninja
            stamp = out_dir / "include" / f"{asset['header']}.stamp"
            steps.append(
                {
                    "rule": "scan_pal16_chunked",
                    "inputs": input,
                    "outputs": dyndep,
                    "variables": {
                        "base": out_base,
                        "stamp": stamp,
                        "symbol": asset["symbol"],
                    },
                    "implicit": Path("tools/converters/pal16dis_chunked.py"),
                }
            )
            # Now the script will generate all the dynamic outputs and stamp file
            steps.append(
                {
                    "rule": "convert_pal16_chunked",
                    "inputs": input,
                    "outputs": stamp,
                    "variables": {
                        "base": out_base,
                        "symbol": asset["symbol"],
                    },
                    "implicit": Path("tools/converters/pal16dis_chunked.py"),
                    "dyndep": dyndep,
                    "order_only": dyndep,
                }
            )

        case "vtx":
            steps.append(
                {
                    "rule": "convert_vtx",
                    "inputs": out_dir / "bin" / asset["binary"],
                    "outputs": out_dir / "include" / asset["header"],
                    "variables": {
                        "symbol": asset["symbol"],
                    },
                    "implicit": Path("tools/converters/vtxdis.py"),
                }
            )

        case _:
            print("Unknown asset type: " + asset["custom_type"])


# Parse the config and create the build rules for all our assets
config_path = out_dir / "config.json"
if config_path.exists():
    config_data = json.load(open(config_path))
    for asset in config_data.get("extract", []):
        emit_build_rule(asset)
    for module in config_data.get("modules", []):
        for asset in module.get("extract", []):
            emit_build_rule(asset)

N64_SDK_urls = [
    "https://raw.githubusercontent.com/decompals/ultralib/main/include/PR/abi.h",
    "https://raw.githubusercontent.com/decompals/ultralib/main/include/PR/gbi.h",
    "https://raw.githubusercontent.com/decompals/ultralib/main/include/PR/gs2dex.h",
    "https://raw.githubusercontent.com/decompals/ultralib/main/include/PR/mbi.h",
    "https://raw.githubusercontent.com/decompals/ultralib/main/include/PR/ultratypes.h",
    "https://raw.githubusercontent.com/decompals/ultralib/main/include/compiler/gcc/stdlib.h",
]

# If we don't have these downloaded, we need to grab em
for url in N64_SDK_urls:
    file_path = os.path.join("include", url.split("include/")[-1])

    if not os.path.exists(file_path):
        os.makedirs(os.path.dirname(file_path), exist_ok=True)

        print(f"Fetching {file_path} from {url}")
        req = urllib.request.Request(
            url, headers={"User-Agent": "Mozilla/5.0"})
        with urllib.request.urlopen(req) as response:
            if response.getcode() == 200:
                content = response.read()

                # We need to modify gbi.h for AC
                if os.path.normpath(file_path) == os.path.normpath("include/PR/gbi.h"):
                    content = re.sub(
                        rb"unsigned char\s+param:8;", b"unsigned int\tparam:8;", content
                    )

                with open(file_path, "wb") as file:
                    file.write(content)
            else:
                print(
                    f"Failed to download {file_path}. Status code: {response.getcode()}"
                )

# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("game", "Game Code"),
    ProgressCategory("sdk", "SDK Code"),
    ProgressCategory("jsystem", "JSystem Code"),
    # catch-all for the rest of static
    ProgressCategory("library", "Library Code"),
]
config.progress_each_module = args.verbose

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress and write progress.json
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
