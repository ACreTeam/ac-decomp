"""
Common functions & definitions
"""

from dataclasses import dataclass
from enum import Enum
from hashlib import sha1
import json
import os
from subprocess import PIPE, run
from sys import executable as PYTHON, platform
from typing import List, Tuple, Union

import yaml
try:
    from yaml import CLoader as Loader
except ImportError:
    from yaml import Loader

#############
# Functions #
#############

def get_file_sha1(path: str) -> bytes:
    """Gets the SHA1 hash of a file"""

    with open(path, 'rb') as f:
        return sha1(f.read()).digest()

def get_cmd_stdout(cmd: str, text=True) -> str:
    """Run a command and get the stdout output as a string"""

    ret = run(cmd.split(), stdout=PIPE, text=text)
    assert ret.returncode == 0, f"Command '{cmd}' returned {ret.returncode}"
    return ret.stdout

class Binary(Enum):
    DOL = 1
    REL = 2

# ppcdis source output
SourceDesc = Union[str, Tuple[str, int, int]]

def get_containing_slice(addr: int) -> Tuple[Binary, SourceDesc]:
    """Finds the binary containing an address and its source file
    Source file is empty string if not decompiled"""

    dol_raw = get_cmd_stdout(f"{SLICES} {DOL_YML} {DOL_SLICES} -p {DOL_SRCDIR}/ --containing {addr:x}")
    containing = json.loads(dol_raw)
    if containing is None:
        rel_raw = get_cmd_stdout(
            f"{SLICES} {REL_YML} {REL_SLICES} -p {REL_SRCDIR}/ --containing {addr:x}"
        )
        containing = json.loads(rel_raw)
        assert containing is not None, f"Unknown address {addr:x}"
        return (Binary.REL, containing)
    else:
        return (Binary.DOL, containing)

def lookup_sym(sym: str, dol: bool = False, rel: bool = False, source_name: str = None) -> int:
    """Takes a symbol as a name or address and returns the address"""

    # Get binary
    if dol:
        binary_name = DOL_YML
    elif rel:
        binary_name = REL_YML
    else:
        binary_name = None

    # Determine type    
    try:
        return int(sym, 16)
    except ValueError:
        return get_address(sym, binary_name, source_name)

def lookup_sym_full(sym: str, dol: bool = False, rel: bool = False, source_name: str = None
                   ) -> int:
    """Takes a symbol as a name or address and returns both the name and address"""

    # Get binary
    if dol:
        binary_name = DOL_YML
    elif rel:
        binary_name = REL_YML
    else:
        binary_name = None

    # Determine type    
    try:
        return int(sym, 16), get_name(sym)
    except ValueError:
        return get_address(sym, binary_name, source_name), sym

def get_address(name: str, binary: bool = None, source_name: bool = None) -> int:
    """Finds the address of a symbol"""

    args = [name]
    if binary is not None:
        args.append(f"-b {binary}")
    if source_name is not None:
        args.append(f"-n {source_name}")
    
    raw = get_cmd_stdout(f"{SYMBOLS} {GAME_SYMBOLS} --get-addr {' '.join(args)}")
    return json.loads(raw)

def get_name(addr: int, binary: bool = None, source_name: bool = None) -> int:
    """Finds the name of a symbol"""

    args = [addr]
    if binary is not None:
        args.append(f"-b {binary}")
    if source_name is not None:
        args.append(f"-n {source_name}")
    
    raw = get_cmd_stdout(f"{SYMBOLS} {GAME_SYMBOLS} --get-name {' '.join(args)}")
    return json.loads(raw)

def find_headers(dirname: str, base=None) -> List[str]:
    """Returns a list of all headers in a folder recursively"""

    if base is None:
        base = dirname

    ret = []
    for name in os.listdir(dirname):
        path = dirname + '/' + name
        if os.path.isdir(path):
            ret.extend(find_headers(path, base))
        elif name.endswith('.h'):
            ret.append(path[len(base)+1:])

    return ret

def load_from_yaml(path: str, default=None):
    """Loads an object from a yaml file"""

    if default is None:
        default = {}
    with open(path) as f:
        ret = yaml.load(f.read(), Loader)
        if ret is None:
            ret = default
        return ret

################
# Project dirs #
################

# Directory for decompiled dol code
DOL_SRCDIR = "src/static"

# Directory for decompiled rel code
REL_SRCDIR = "src"

# Include directory
INCDIR = "include"

# Directory for forest_1st data
FOREST_1STDIR = "src/data/bin1"

# Directory for forest_2nd data
FOREST_2NDDIR = "src/data/bin2"

# Build artifacts directory
BUILDDIR = "build"

# Build include directory
BUILD_INCDIR = f"{BUILDDIR}/include"

# Output binaries directory
OUTDIR = "out"

# Original binaries directory
ORIG = "dump"

# Tools directory
TOOLS = "tools"

# Config directory
CONFIG = "config"

# Extracted assets directory
ASSETS = "assets"

#########
# Tools #
#########

# ppcdis
PPCDIS = "tools/ppcdis"
PPCDIS_INCDIR = f"{PPCDIS}/include"
RELEXTERN = f"{PYTHON} {PPCDIS}/relextern.py"
ANALYSER = f"{PYTHON} {PPCDIS}/analyser.py"
DISASSEMBLER = f"{PYTHON} {PPCDIS}/disassembler.py"
ORDERSTRINGS = f"{PYTHON} {PPCDIS}/orderstrings.py"
ORDERFLOATS = f"{PYTHON} {PPCDIS}/orderfloats.py"
ASSETRIP = f"{PYTHON} {PPCDIS}/assetrip.py"
ASSETINC = f"{PYTHON} {PPCDIS}/assetinc.py"
FORCEACTIVEGEN = f"{PYTHON} {PPCDIS}/forceactivegen.py"
ELF2DOL = f"{PYTHON} {PPCDIS}/elf2dol.py"
ELF2REL = f"{PYTHON} {PPCDIS}/elf2rel.py"
SLICES = f"{PYTHON} {PPCDIS}/slices.py"
PROGRESS = f"{PYTHON} {PPCDIS}/progress.py"
SYMBOLS = f"{PYTHON} {PPCDIS}/symbols.py"
FORCEFILESGEN = f"{PYTHON} {PPCDIS}/forcefilesgen.py"

# Codewarrior
TOOLS = "tools"
CODEWARRIOR = os.path.join(TOOLS, "1.3.2")
CODEWARRIOR_RODATA_POOL_FIX = os.path.join(TOOLS, "1.3.2r")
SDK_CW = os.path.join(TOOLS, "1.2.5n")
CC = os.path.join(CODEWARRIOR, "mwcceppc.exe")
CC_R = os.path.join(CODEWARRIOR_RODATA_POOL_FIX, "mwcceppc.exe")
OCC = os.path.join(SDK_CW, "mwcceppc.exe")
LD = os.path.join(CODEWARRIOR, "mwldeppc.exe")
if platform != "win32":
    CC = f"wibo {CC}"
    CC_R = f"wibo {CC_R}"
    OCC = f"wibo {OCC}"
    LD = f"wibo {LD}"

# DevkitPPC
DEVKITPPC = os.environ.get("DEVKITPPC")
AS = os.path.join(DEVKITPPC, "bin", "powerpc-eabi-as")
OBJDUMP = os.path.join(DEVKITPPC, "bin", "powerpc-eabi-objdump")
CPP = os.path.join(DEVKITPPC, "bin", "powerpc-eabi-cpp")

# Asset Converters
VTXDIS = f"{PYTHON} {TOOLS}/converters/vtxdis.py"
PAL16DIS = f"{PYTHON} {TOOLS}/converters/pal16dis.py"

# JSystem JKernel archive tool
ARC_TOOL = f"{PYTHON} {TOOLS}/arc_tool.py"

ICONV = f"{PYTHON} tools/sjis.py" # TODO: get actual iconv working(?)

# N64 SDK path for GBI
N64SDK = os.environ.get("N64_SDK")
assert N64SDK != None, "N64_SDK is not defined as a system environment variable"

#########
# Files #
#########

# Slices
DOL_SLICES = f"{CONFIG}/dol_slices.yml"
REL_SLICES = f"{CONFIG}/rel_slices.yml"

# Overrides
ANALYSIS_OVERRIDES = f"{CONFIG}/analysis_overrides.yml"
DOL_DISASM_OVERRIDES = f"{CONFIG}/disasm_overrides.yml"
REL_DISASM_OVERRIDES = f"{CONFIG}/rel_disasm_overrides.yml"

# Binaries
DOL = f"{ORIG}/static.dol" # read in python code
REL = f"{ORIG}/foresta.rel" # read in python code
DOL_YML = f"{CONFIG}/dol.yml"
REL_YML = f"{CONFIG}/rel.yml"
DOL_SHA = f"{ORIG}/static.dol.sha1"
REL_SHA = f"{ORIG}/foresta.rel.sha1"
DOL_OK = f"{BUILDDIR}/static.dol.ok"
REL_OK = f"{BUILDDIR}/foresta.rel.ok"
DOL_ASM_LIST = f"{BUILDDIR}/static.dol.asml"
REL_ASM_LIST = f"{BUILDDIR}/foresta.rel.asml"

# Symbols
GAME_SYMBOLS = f"{CONFIG}/symbols.yml"

# Assets
ASSETS_YML = f"{CONFIG}/assets.yml"

# Analysis outputs
EXTERNS = f"{BUILDDIR}/externs.pickle"
DOL_LABELS = f"{BUILDDIR}/labels.pickle"
DOL_RELOCS = f"{BUILDDIR}/relocs.pickle"
REL_LABELS = f"{BUILDDIR}/rel_labels.pickle"
REL_RELOCS = f"{BUILDDIR}/rel_relocs.pickle"

# Linker
DOL_LCF_TEMPLATE = f"{CONFIG}/dol.lcf"
DOL_LCF_TEMP = f"{BUILDDIR}/dol_temp.lcf"
DOL_LCF = f"{BUILDDIR}/dol.lcf"
REL_LCF = f"{CONFIG}/rel.lcf"

# Outputs
DOL_ELF = f"{BUILDDIR}/static.elf"
REL_PLF = f"{BUILDDIR}/foresta.plf"
DOL_OUT = f"{OUTDIR}/static.dol"
REL_OUT = f"{OUTDIR}/foresta.rel"
DOL_MAP = f"{OUTDIR}/static.map"
REL_MAP = f"{OUTDIR}/foresta.map"

# Optional full disassembly
DOL_FULL = f"{OUTDIR}/dol.s"
REL_FULL = f"{OUTDIR}/rel.s"

##############
# Tool Flags #
##############

ASFLAGS = ' '.join([
    "-m gekko",
    f"-I {INCDIR}",
    f"-I {PPCDIS_INCDIR}",
    f"-I orig",
    f"-I {N64SDK}/ultra/usr/include"
])

CPPFLAGS = ' '.join([
    "-nostdinc",
    f"-I {INCDIR}",
    f"-I {PPCDIS_INCDIR}",
    f"-I {BUILD_INCDIR}",
    f"-I {N64SDK}/ultra/usr/include"
])

DOL_SDATA2_SIZE = 8
REL_SDATA2_SIZE = 0

CFLAGS = [
    "-O4",
    "-char unsigned",
    "-fp hard"
]
CPLFLAGS = [
    "-lang=c++",
    "-O0"
]
COMMON_DEFINES = [
    "-d _LANGUAGE_C",
    "-d F3DEX_GBI_2",
    "-d NDEBUG",
    "-d DEBUG=0",
    "-d MUST_MATCH"
]
DOL_DEFINES = COMMON_DEFINES + []
REL_DEFINES = COMMON_DEFINES + [ 
    #"-d OPTIMIZED_SQRTF",
    "-d IS_REL"
]
BASE_DOL_CFLAGS = CFLAGS + [
    "-inline on",
    "-sdata 8",
    f"-sdata2 {DOL_SDATA2_SIZE}"
] + DOL_DEFINES
BOOT_CFLAGS = CFLAGS + [
    "-inline on",
    "-sdata 0",
    "-sdata2 0"
] + DOL_DEFINES
DOL_CFLAGS_NO_SDATA = CFLAGS + [
    "-inline on",
    "-enum int",
    "-sdata 0",
    "-sdata2 0"
] + DOL_DEFINES
DVDERR_CFLAGS = CFLAGS + [
    "-inline on",
    "-sdata 0",
    "-sdata2 0",
    "-pool off"
] + DOL_DEFINES
TRK_CFLAGS = [
    "-O4,p",
    "-sdata 0",
    "-sdata2 0",
    "-fp hard",
    "-enum int",
    "-char unsigned",
    "-inline deferred",
    "-rostr"
] + DOL_DEFINES
BASE_REL_CFLAGS = CFLAGS + [
     "-sdata 0",
     f"-sdata2 {REL_SDATA2_SIZE}",
     "-enum int",
     #"-pool off",
     "-sym on"
] + REL_DEFINES

LOCAL_CFLAGS = [
    "-nostdinc",
    "-proc gekko",
    "-maxerrors 1",
    "-Cpp_exceptions off",
    "-I-",
    f"-i {INCDIR}",
    f"-i {PPCDIS_INCDIR}",
    f"-i {BUILD_INCDIR}",
   f"-ir {N64SDK}/ultra/usr/include"
]

PREPROCESSOR_CFLAGS = [
    "-E",
    "-P"
]

SDK_CFLAG = [
    "-O4,p",
    "-inline all",
    "-sdata 8",
    f"-sdata2 {DOL_SDATA2_SIZE}"
]
ALIGN16_CFLAG = [
    "-func_align 16",
]
JSYSTEM_BASE = [
    "-lang=c++",
    "-inline on",
    "-fp fmadd",
    #"-fp_contract on",
    #"-pool off", # this is wrong
    "-Cpp_exceptions off",
    "-RTTI on",
    "-char signed",
    "-enum int",
    "-sym on", # might also be on for base flags?
    "-O4,s" # in mkdd some libraries use O4,p, might be the case here too
]
JSYSTEM_JGADGET_BASE = [
    "-lang=c++",
    "-inline on",
    "-fp fmadd",
    #"-fp_contract on",
    #"-pool off", # this is wrong
    "-Cpp_exceptions off",
    "-RTTI on",
    "-char signed",
    "-enum int",
    # "-sym on", # might also be on for base flags?
    "-O4,s" # in mkdd some libraries use O4,p, might be the case here too
]
FAMICOM_BASE = CFLAGS + [
    "-lang=c++",
    "-sdata 0",
    "-sdata2 0",
    "-enum int",
    "-sym on"
] + DOL_DEFINES

JSYSTEM_CFLAGS = ' '.join(JSYSTEM_BASE + LOCAL_CFLAGS)
JSYSTEM_JGADGET_CFLAGS = ' '.join(JSYSTEM_JGADGET_BASE + LOCAL_CFLAGS)
DOL_CFLAGS = ' '.join(BASE_DOL_CFLAGS + LOCAL_CFLAGS)
DOL_BOOT_CFLAGS = ' '.join(BOOT_CFLAGS + LOCAL_CFLAGS)
DOL_DVDERR_CFLAGS = ' '.join(DVDERR_CFLAGS + LOCAL_CFLAGS)
DOL_CFLAGS_SDATA0_CFLAGS = ' '.join(DOL_CFLAGS_NO_SDATA + LOCAL_CFLAGS)
DOL_TRK_CFLAGS = ' '.join(TRK_CFLAGS + LOCAL_CFLAGS)
SDK_FLAGS = ' '.join(SDK_CFLAG + LOCAL_CFLAGS)
ALIGN16 = ' '.join(BASE_DOL_CFLAGS + LOCAL_CFLAGS + ALIGN16_CFLAG)
DOL_CPPFLAGS = ' '.join(CPLFLAGS + BASE_DOL_CFLAGS + LOCAL_CFLAGS)
REL_CFLAGS = ' '.join(BASE_REL_CFLAGS + LOCAL_CFLAGS)
EXTERNAL_DOL_CFLAGS = ' '.join(BASE_DOL_CFLAGS)
EXTERNAL_REL_CFLAGS = ' '.join(BASE_REL_CFLAGS)
PREPROCESS_CFLAGS = ' '.join(PREPROCESSOR_CFLAGS)
FAMICOM_CLFAGS = ' '.join(FAMICOM_BASE + LOCAL_CFLAGS)

DOL_LDFLAGS = ' '.join([
    "-maxerrors 1",
    "-mapunused"
])

LDFLAGS = ' '.join([
    "-maxerrors 1",
    "-mapunused",
    "-opt_partial",
    "-strip_partial"
])

PPCDIS_ANALYSIS_FLAGS = ' '.join([
    f"-o {ANALYSIS_OVERRIDES}",
    f"-l {EXTERNS}"
])


############
# Contexts #
############

@dataclass
class SourceContext:
    srcdir: str
    cflags: str
    binary: str
    labels: str
    relocs: str
    slices: str
    compiler: str
    sdata2_threshold: int
    disasm_overrides: int

DOL_CTX = SourceContext(DOL_SRCDIR, DOL_CFLAGS, DOL_YML, DOL_LABELS, DOL_RELOCS, DOL_SLICES,
                        CC, DOL_SDATA2_SIZE, DOL_DISASM_OVERRIDES)
REL_CTX = SourceContext(REL_SRCDIR, REL_CFLAGS, REL_YML, REL_LABELS, REL_RELOCS, REL_SLICES,
                        CC, REL_SDATA2_SIZE, REL_DISASM_OVERRIDES)

####################
# diff.py Expected #
####################

EXPECTED = "expected"
DOL_EXPECTED = f"{EXPECTED}/build/main.elf"
REL_EXPECTED = f"{EXPECTED}/build/foresta.plf"
