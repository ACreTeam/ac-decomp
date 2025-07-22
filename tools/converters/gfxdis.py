from argparse import ArgumentParser
from dataclasses import dataclass


def SEGMENT_ADDR(num, off): return (((num) << 24) + (off))


SHOW_CODE = False

SOFTSPRITE_MTX_SEG = 0x07
ANIME_1_TXT_SEG = 0x08
ANIME_2_TXT_SEG = 0x09
ANIME_3_TXT_SEG = 0x0A
ANIME_4_TXT_SEG = 0x0B
ANIME_5_TXT_SEG = 0x0C
ANIME_6_TXT_SEG = 0x0D

anime_1_txt = SEGMENT_ADDR(ANIME_1_TXT_SEG, 0)
anime_1_model = SEGMENT_ADDR(ANIME_1_TXT_SEG, 0)
anime_2_txt = SEGMENT_ADDR(ANIME_2_TXT_SEG, 0)
anime_2_model = SEGMENT_ADDR(ANIME_2_TXT_SEG, 0)
anime_3_txt = SEGMENT_ADDR(ANIME_3_TXT_SEG, 0)
anime_3_model = SEGMENT_ADDR(ANIME_3_TXT_SEG, 0)
anime_4_txt = SEGMENT_ADDR(ANIME_4_TXT_SEG, 0)
anime_4_model = SEGMENT_ADDR(ANIME_4_TXT_SEG, 0)
anime_5_txt = SEGMENT_ADDR(ANIME_5_TXT_SEG, 0)
anime_5_model = SEGMENT_ADDR(ANIME_5_TXT_SEG, 0)
anime_6_txt = SEGMENT_ADDR(ANIME_6_TXT_SEG, 0)
anime_6_model = SEGMENT_ADDR(ANIME_6_TXT_SEG, 0)


def strarg_animesegment(v):
    return {
        anime_1_txt: "anime_1_txt",
        anime_2_txt: "anime_2_txt",
        anime_3_txt: "anime_3_txt",
        anime_4_txt: "anime_4_txt",
        anime_5_txt: "anime_5_txt",
        anime_6_txt: "anime_6_mdl"
    }.get(v, str(v))


symbol_stack: list[str] = []


def symbol_lookup(addr):
    global symbol_stack
    if (addr == 0):
        if len(symbol_stack) > 0:
            return symbol_stack.pop(0)
        else:
            return "UnknownSymbol"
    else:
        seg = f"{strarg_animesegment(addr & 0xff000000)}"
        if (addr & 0x00ffffff):
            if seg == "anime_6_mdl":
                seg = f"&anime_6_mdl[{(addr & 0x00ffffff) // 0x40}]"
            else:
                seg += f" + 0x{addr & 0x00ffffff:X}"
        return seg


GFX_INSTR_SIZE = 8
GFX_SYMBOL = None
BOWTIE_VAL = 0
DATA_LOWER = 0
DATA_UPPER = 1
DATA_SPREAD = 2
DL = DATA_LOWER
DU = DATA_UPPER
DS = DATA_SPREAD

G_ACMUX_COMBINED = 0
G_ACMUX_TEXEL0 = 1
G_ACMUX_TEXEL1 = 2
G_ACMUX_PRIMITIVE = 3
G_ACMUX_SHADE = 4
G_ACMUX_ENVIRONMENT = 5
G_ACMUX_LOD_FRACTION = 0
G_ACMUX_PRIM_LOD_FRAC = 6
G_ACMUX_1 = 6
G_ACMUX_0 = 7

G_MTX_MODELVIEW = 0x00  # /* matrix types */
G_MTX_PROJECTION = 0x04
G_MTX_MUL = 0x00  # /* concat or load */
G_MTX_LOAD = 0x02
G_MTX_NOPUSH = 0x00  # /* push or not */
G_MTX_PUSH = 0x01

G_IM_FMT_RGBA = 0
G_IM_FMT_YUV = 1
G_IM_FMT_CI = 2
G_IM_FMT_IA = 3
G_IM_FMT_I = 4

G_IM_SIZ_4b = 0
G_IM_SIZ_8b = 1
G_IM_SIZ_16b = 2
G_IM_SIZ_32b = 3
G_IM_SIZ_DD = 5

G_CCMUX_COMBINED = 0
G_CCMUX_TEXEL0 = 1
G_CCMUX_TEXEL1 = 2
G_CCMUX_PRIMITIVE = 3
G_CCMUX_SHADE = 4
G_CCMUX_ENVIRONMENT = 5
G_CCMUX_CENTER = 6
G_CCMUX_SCALE = 6
G_CCMUX_COMBINED_ALPHA = 7
G_CCMUX_TEXEL0_ALPHA = 8
G_CCMUX_TEXEL1_ALPHA = 9
G_CCMUX_PRIMITIVE_ALPHA = 10
G_CCMUX_SHADE_ALPHA = 11
G_CCMUX_ENV_ALPHA = 12
G_CCMUX_LOD_FRACTION = 13
G_CCMUX_PRIM_LOD_FRAC = 14
G_CCMUX_NOISE = 7
G_CCMUX_K4 = 7
G_CCMUX_K5 = 15
G_CCMUX_1 = 6
G_CCMUX_0 = 31

G_TX_LOADTILE = 7
G_TX_RENDERTILE = 0

G_ON = 1
G_OFF = 0

G_TX_NOMIRROR = 0
G_TX_WRAP = 0
G_TX_MIRROR = 0x1
G_TX_CLAMP = 0x2
G_TX_NOMASK = 0
G_TX_NOLOD = 0

G_TEXTURE_ENABLE = (0 << 0)
G_CULL_FRONT = (1 << 9)
G_CULL_BACK = (1 << 10)
G_SHADING_SMOOTH = (1 << 21)
G_ZBUFFER = (1 << 0)
G_SHADE = (1 << 2)
G_CULL_BOTH = (G_CULL_FRONT | G_CULL_BACK)
G_FOG = (1 << 16)
G_LIGHTING = (1 << 17)
G_TEXTURE_GEN = (1 << 18)
G_TEXTURE_GEN_LINEAR = (1 << 19)
G_LOD = (1 << 20)
G_CLIPPING = 0x00800000

G_MDSFT_ALPHADITHER = 4
G_MDSFT_RGBDITHER = 6
G_MDSFT_COMBKEY = 8
G_MDSFT_TEXTCONV = 9
G_MDSFT_TEXTFILT = 12
G_MDSFT_TEXTLUT = 14
G_MDSFT_TEXTLOD = 16
G_MDSFT_TEXTDETAIL = 17
G_MDSFT_TEXTPERSP = 19
G_MDSFT_CYCLETYPE = 20
G_MDSFT_PIPELINE = 23
G_MDSIZ_ALPHADITHER = 2
G_MDSIZ_RGBDITHER = 2
G_MDSIZ_COMBKEY = 1
G_MDSIZ_TEXTCONV = 3
G_MDSIZ_TEXTFILT = 2
G_MDSIZ_TEXTLUT = 2
G_MDSIZ_TEXTLOD = 1
G_MDSIZ_TEXTDETAIL = 2
G_MDSIZ_TEXTPERSP = 1
G_MDSIZ_CYCLETYPE = 2
G_MDSIZ_PIPELINE = 1

G_MDSFT_ALPHACOMPARE = 0
G_MDSFT_ZSRCSEL = 2
G_MDSFT_RENDERMODE = 3
G_MDSIZ_ALPHACOMPARE = 2
G_MDSIZ_ZSRCSEL = 1
G_MDSIZ_RENDERMODE = 29

G_NOOP = 0x00
G_RDPHALF_2 = 0xf1
G_SETOTHERMODE_H = 0xe3
G_SETOTHERMODE_L = 0xe2
G_RDPHALF_1 = 0xe1
G_SPNOOP = 0xe0
G_ENDDL = 0xdf
G_DL = 0xde
G_LOAD_UCODE = 0xdd
G_MOVEMEM = 0xdc
G_MOVEWORD = 0xdb
G_MTX = 0xda
G_GEOMETRYMODE = 0xd9
G_POPMTX = 0xd8
G_TEXTURE = 0xd7
G_DMA_IO = 0xd6
G_SPECIAL_1 = 0xd5
G_SPECIAL_2 = 0xd4
G_SPECIAL_3 = 0xd3

G_VTX = 0x01
G_MODIFYVTX = 0x02
G_CULLDL = 0x03
G_BRANCH_Z = 0x04
G_TRI1 = 0x05
G_TRI2 = 0x06
G_QUAD = 0x07
G_LINE3D = 0x08

G_SETCIMG = 0xff
G_SETZIMG = 0xfe
G_SETTIMG = 0xfd
G_SETCOMBINE = 0xfc
G_SETENVCOLOR = 0xfb
G_SETPRIMCOLOR = 0xfa
G_SETBLENDCOLOR = 0xf9
G_SETFOGCOLOR = 0xf8
G_SETFILLCOLOR = 0xf7
G_FILLRECT = 0xf6
G_SETTILE = 0xf5
G_LOADTILE = 0xf4
G_LOADBLOCK = 0xf3
G_SETTILESIZE = 0xf2
G_LOADTLUT = 0xf0
G_RDPSETOTHERMODE = 0xef
G_SETPRIMDEPTH = 0xee
G_SETSCISSOR = 0xed
G_SETCONVERT = 0xec
G_SETKEYR = 0xeb
G_SETKEYGB = 0xea
G_RDPFULLSYNC = 0xe9
G_RDPTILESYNC = 0xe8
G_RDPPIPESYNC = 0xe7
G_RDPLOADSYNC = 0xe6
G_TEXRECTFLIP = 0xe5
G_TEXRECT = 0xe4

G_TRIN = 0x09
G_TRIN_INDEPEND = 0x0A
G_SETTEXEDGEALPHA = 0xCE
G_SETCOMBINE_NOTEV = 0xCF
G_SETCOMBINE_TEV = 0xD0
G_SETTILE_DOLPHIN = 0xD2

G_DOLPHIN_TLUT_DEFAULT_MODE = 15
GX_CLAMP = 0
GX_REPEAT = 1
GX_MIRROR = 2
GX_MAX_TEXWRAPMODE = 3

AA_EN = 0x8
Z_CMP = 0x10
Z_UPD = 0x20
IM_RD = 0x40
CLR_ON_CVG = 0x80
CVG_DST_CLAMP = 0
CVG_DST_WRAP = 0x100
CVG_DST_FULL = 0x200
CVG_DST_SAVE = 0x300
ZMODE_OPA = 0
ZMODE_INTER = 0x400
ZMODE_XLU = 0x800
ZMODE_DEC = 0xc00
CVG_X_ALPHA = 0x1000
ALPHA_CVG_SEL = 0x2000
FORCE_BL = 0x4000
TEX_EDGE = 0x0000  # /* used to be 0x8000 */

G_BL_CLR_IN = 0
G_BL_CLR_MEM = 1
G_BL_CLR_BL = 2
G_BL_CLR_FOG = 3
G_BL_1MA = 0
G_BL_A_MEM = 1
G_BL_A_IN = 0
G_BL_A_FOG = 1
G_BL_A_SHADE = 2
G_BL_1 = 2
G_BL_0 = 3

G_AC_NONE = (0 << G_MDSFT_ALPHACOMPARE)
G_AC_THRESHOLD = (1 << G_MDSFT_ALPHACOMPARE)
G_AC_DITHER = (3 << G_MDSFT_ALPHACOMPARE)

G_TT_NONE = (0 << G_MDSFT_TEXTLUT)
G_TT_RGBA16 = (2 << G_MDSFT_TEXTLUT)
G_TT_IA16 = (3 << G_MDSFT_TEXTLUT)

G_AD_PATTERN = (0 << G_MDSFT_ALPHADITHER)
G_AD_NOTPATTERN = (1 << G_MDSFT_ALPHADITHER)
G_AD_NOISE = (2 << G_MDSFT_ALPHADITHER)
G_AD_DISABLE = (3 << G_MDSFT_ALPHADITHER)
G_CD_MAGICSQ = (0 << G_MDSFT_RGBDITHER)
G_CD_BAYER = (1 << G_MDSFT_RGBDITHER)
G_CD_NOISE = (2 << G_MDSFT_RGBDITHER)

G_CD_DISABLE = (3 << G_MDSFT_RGBDITHER)
G_CD_ENABLE = G_CD_NOISE

G_CK_NONE = (0 << G_MDSFT_COMBKEY)
G_CK_KEY = (1 << G_MDSFT_COMBKEY)

G_TC_CONV = (0 << G_MDSFT_TEXTCONV)
G_TC_FILTCONV = (5 << G_MDSFT_TEXTCONV)
G_TC_FILT = (6 << G_MDSFT_TEXTCONV)

G_TF_POINT = (0 << G_MDSFT_TEXTFILT)
G_TF_AVERAGE = (3 << G_MDSFT_TEXTFILT)
G_TF_BILERP = (2 << G_MDSFT_TEXTFILT)

G_TL_TILE = (0 << G_MDSFT_TEXTLOD)
G_TL_LOD = (1 << G_MDSFT_TEXTLOD)

G_TD_CLAMP = (0 << G_MDSFT_TEXTDETAIL)
G_TD_SHARPEN = (1 << G_MDSFT_TEXTDETAIL)
G_TD_DETAIL = (2 << G_MDSFT_TEXTDETAIL)

G_TP_NONE = (0 << G_MDSFT_TEXTPERSP)
G_TP_PERSP = (1 << G_MDSFT_TEXTPERSP)

G_CYC_1CYCLE = (0 << G_MDSFT_CYCLETYPE)
G_CYC_2CYCLE = (1 << G_MDSFT_CYCLETYPE)
G_CYC_COPY = (2 << G_MDSFT_CYCLETYPE)
G_CYC_FILL = (3 << G_MDSFT_CYCLETYPE)

G_PM_1PRIMITIVE = (1 << G_MDSFT_PIPELINE)
G_PM_NPRIMITIVE = (0 << G_MDSFT_PIPELINE)

G_TLUT_DOLPHIN = 2


def GBL_c1(m1a, m1b, m2a, m2b): return (m1a) << 30 | (
    m1b) << 26 | (m2a) << 22 | (m2b) << 18


def GBL_c2(m1a, m1b, m2a, m2b): return (m1a) << 28 | (
    m1b) << 24 | (m2a) << 20 | (m2b) << 16


GBL_c = [None, GBL_c1, GBL_c2]


def RM_AA_ZB_OPA_SURF(clk): return AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ZMODE_OPA | ALPHA_CVG_SEL | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


def RM_RA_ZB_OPA_SURF(clk): return AA_EN | Z_CMP | Z_UPD | CVG_DST_CLAMP | ZMODE_OPA | ALPHA_CVG_SEL | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


def RM_AA_ZB_XLU_SURF(clk): return AA_EN | Z_CMP | IM_RD | CVG_DST_WRAP | CLR_ON_CVG | FORCE_BL | ZMODE_XLU | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_AA_ZB_OPA_DECAL(clk): return AA_EN | Z_CMP | IM_RD | CVG_DST_WRAP | ALPHA_CVG_SEL | ZMODE_DEC | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


def RM_RA_ZB_OPA_DECAL(clk): return AA_EN | Z_CMP | CVG_DST_WRAP | ALPHA_CVG_SEL | ZMODE_DEC | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


def RM_AA_ZB_XLU_DECAL(clk): return AA_EN | Z_CMP | IM_RD | CVG_DST_WRAP | CLR_ON_CVG | FORCE_BL | ZMODE_DEC | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_AA_ZB_OPA_INTER(clk): return AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ALPHA_CVG_SEL | ZMODE_INTER | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


def RM_RA_ZB_OPA_INTER(clk): return AA_EN | Z_CMP | Z_UPD | CVG_DST_CLAMP | ALPHA_CVG_SEL | ZMODE_INTER | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


def RM_AA_ZB_XLU_INTER(clk): return AA_EN | Z_CMP | IM_RD | CVG_DST_WRAP | CLR_ON_CVG | FORCE_BL | ZMODE_INTER | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_AA_ZB_XLU_LINE(clk): return AA_EN | Z_CMP | IM_RD | CVG_DST_CLAMP | CVG_X_ALPHA | ALPHA_CVG_SEL | FORCE_BL | ZMODE_XLU | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_AA_ZB_DEC_LINE(clk): return AA_EN | Z_CMP | IM_RD | CVG_DST_SAVE | CVG_X_ALPHA | ALPHA_CVG_SEL | FORCE_BL | ZMODE_DEC | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_AA_ZB_TEX_EDGE(clk): return AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | CVG_X_ALPHA | ALPHA_CVG_SEL | ZMODE_OPA | TEX_EDGE | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


def RM_AA_ZB_TEX_INTER(clk): return AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | CVG_X_ALPHA | ALPHA_CVG_SEL | ZMODE_INTER | TEX_EDGE | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


def RM_AA_ZB_SUB_SURF(clk): return AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_FULL | ZMODE_OPA | ALPHA_CVG_SEL | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


def RM_AA_ZB_PCL_SURF(clk): return AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ZMODE_OPA | G_AC_DITHER | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_AA_ZB_OPA_TERR(clk): return AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | ZMODE_OPA | ALPHA_CVG_SEL | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_AA_ZB_TEX_TERR(clk): return AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_CLAMP | CVG_X_ALPHA | ALPHA_CVG_SEL | ZMODE_OPA | TEX_EDGE | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_AA_ZB_SUB_TERR(clk): return AA_EN | Z_CMP | Z_UPD | IM_RD | CVG_DST_FULL | ZMODE_OPA | ALPHA_CVG_SEL | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_AA_OPA_SURF(clk): return AA_EN | IM_RD | CVG_DST_CLAMP | ZMODE_OPA | ALPHA_CVG_SEL | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


def RM_RA_OPA_SURF(clk): return AA_EN | CVG_DST_CLAMP | ZMODE_OPA | ALPHA_CVG_SEL | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


def RM_AA_XLU_SURF(clk): return AA_EN | IM_RD | CVG_DST_WRAP | CLR_ON_CVG | FORCE_BL | ZMODE_OPA | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_AA_XLU_LINE(clk): return AA_EN | IM_RD | CVG_DST_CLAMP | CVG_X_ALPHA | ALPHA_CVG_SEL | FORCE_BL | ZMODE_OPA | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_AA_DEC_LINE(clk): return AA_EN | IM_RD | CVG_DST_FULL | CVG_X_ALPHA | ALPHA_CVG_SEL | FORCE_BL | ZMODE_OPA | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_AA_TEX_EDGE(clk): return AA_EN | IM_RD | CVG_DST_CLAMP | CVG_X_ALPHA | ALPHA_CVG_SEL | ZMODE_OPA | TEX_EDGE | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


def RM_AA_SUB_SURF(clk): return AA_EN | IM_RD | CVG_DST_FULL | ZMODE_OPA | ALPHA_CVG_SEL | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


def RM_AA_PCL_SURF(clk): return AA_EN | IM_RD | CVG_DST_CLAMP | ZMODE_OPA | G_AC_DITHER | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_AA_OPA_TERR(clk): return AA_EN | IM_RD | CVG_DST_CLAMP | ZMODE_OPA | ALPHA_CVG_SEL | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_AA_TEX_TERR(clk): return AA_EN | IM_RD | CVG_DST_CLAMP | CVG_X_ALPHA | ALPHA_CVG_SEL | ZMODE_OPA | TEX_EDGE | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_AA_SUB_TERR(clk): return AA_EN | IM_RD | CVG_DST_FULL | ZMODE_OPA | ALPHA_CVG_SEL | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_ZB_OPA_SURF(clk): return Z_CMP | Z_UPD | CVG_DST_FULL | ALPHA_CVG_SEL | ZMODE_OPA | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


def RM_ZB_XLU_SURF(clk): return Z_CMP | IM_RD | CVG_DST_FULL | FORCE_BL | ZMODE_XLU | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_ZB_OPA_DECAL(clk): return Z_CMP | CVG_DST_FULL | ALPHA_CVG_SEL | ZMODE_DEC | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_A_MEM)


def RM_ZB_XLU_DECAL(clk): return Z_CMP | IM_RD | CVG_DST_FULL | FORCE_BL | ZMODE_DEC | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_ZB_CLD_SURF(clk): return Z_CMP | IM_RD | CVG_DST_SAVE | FORCE_BL | ZMODE_XLU | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_ZB_OVL_SURF(clk): return Z_CMP | IM_RD | CVG_DST_SAVE | FORCE_BL | ZMODE_DEC | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_ZB_PCL_SURF(clk): return Z_CMP | Z_UPD | CVG_DST_FULL | ZMODE_OPA | G_AC_DITHER | GBL_c[clk](
    G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)


def RM_OPA_SURF(clk): return CVG_DST_CLAMP | FORCE_BL | ZMODE_OPA | GBL_c[clk](
    G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)


def RM_XLU_SURF(clk): return IM_RD | CVG_DST_FULL | FORCE_BL | ZMODE_OPA | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_TEX_EDGE(clk): return CVG_DST_CLAMP | CVG_X_ALPHA | ALPHA_CVG_SEL | FORCE_BL | ZMODE_OPA | TEX_EDGE | AA_EN | GBL_c[clk](
    G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)


def RM_CLD_SURF(clk): return IM_RD | CVG_DST_SAVE | FORCE_BL | ZMODE_OPA | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)


def RM_PCL_SURF(clk): return CVG_DST_FULL | FORCE_BL | ZMODE_OPA | G_AC_DITHER | GBL_c[clk](
    G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)
def RM_ADD(clk): return IM_RD | CVG_DST_SAVE | FORCE_BL | ZMODE_OPA | GBL_c[clk](
    G_BL_CLR_IN, G_BL_A_FOG, G_BL_CLR_MEM, G_BL_1)


def RM_NOOP(clk): return GBL_c[clk](0, 0, 0, 0)


def RM_VISCVG(clk): return IM_RD | FORCE_BL | GBL_c[clk](
    G_BL_CLR_IN, G_BL_0, G_BL_CLR_BL, G_BL_A_MEM)

# /* for rendering to an 8-bit framebuffer */


def RM_OPA_CI(clk: int): return CVG_DST_CLAMP | ZMODE_OPA | GBL_c[clk](
    G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)


G_RM_AA_ZB_OPA_SURF = RM_AA_ZB_OPA_SURF(1)
G_RM_AA_ZB_OPA_SURF2 = RM_AA_ZB_OPA_SURF(2)
G_RM_AA_ZB_XLU_SURF = RM_AA_ZB_XLU_SURF(1)
G_RM_AA_ZB_XLU_SURF2 = RM_AA_ZB_XLU_SURF(2)
G_RM_AA_ZB_OPA_DECAL = RM_AA_ZB_OPA_DECAL(1)
G_RM_AA_ZB_OPA_DECAL2 = RM_AA_ZB_OPA_DECAL(2)
G_RM_AA_ZB_XLU_DECAL = RM_AA_ZB_XLU_DECAL(1)
G_RM_AA_ZB_XLU_DECAL2 = RM_AA_ZB_XLU_DECAL(2)
G_RM_AA_ZB_OPA_INTER = RM_AA_ZB_OPA_INTER(1)
G_RM_AA_ZB_OPA_INTER2 = RM_AA_ZB_OPA_INTER(2)
G_RM_AA_ZB_XLU_INTER = RM_AA_ZB_XLU_INTER(1)
G_RM_AA_ZB_XLU_INTER2 = RM_AA_ZB_XLU_INTER(2)
G_RM_AA_ZB_XLU_LINE = RM_AA_ZB_XLU_LINE(1)
G_RM_AA_ZB_XLU_LINE2 = RM_AA_ZB_XLU_LINE(2)
G_RM_AA_ZB_DEC_LINE = RM_AA_ZB_DEC_LINE(1)
G_RM_AA_ZB_DEC_LINE2 = RM_AA_ZB_DEC_LINE(2)
G_RM_AA_ZB_TEX_EDGE = RM_AA_ZB_TEX_EDGE(1)
G_RM_AA_ZB_TEX_EDGE2 = RM_AA_ZB_TEX_EDGE(2)
G_RM_AA_ZB_TEX_INTER = RM_AA_ZB_TEX_INTER(1)
G_RM_AA_ZB_TEX_INTER2 = RM_AA_ZB_TEX_INTER(2)
G_RM_AA_ZB_SUB_SURF = RM_AA_ZB_SUB_SURF(1)
G_RM_AA_ZB_SUB_SURF2 = RM_AA_ZB_SUB_SURF(2)
G_RM_AA_ZB_PCL_SURF = RM_AA_ZB_PCL_SURF(1)
G_RM_AA_ZB_PCL_SURF2 = RM_AA_ZB_PCL_SURF(2)
G_RM_AA_ZB_OPA_TERR = RM_AA_ZB_OPA_TERR(1)
G_RM_AA_ZB_OPA_TERR2 = RM_AA_ZB_OPA_TERR(2)
G_RM_AA_ZB_TEX_TERR = RM_AA_ZB_TEX_TERR(1)
G_RM_AA_ZB_TEX_TERR2 = RM_AA_ZB_TEX_TERR(2)
G_RM_AA_ZB_SUB_TERR = RM_AA_ZB_SUB_TERR(1)
G_RM_AA_ZB_SUB_TERR2 = RM_AA_ZB_SUB_TERR(2)

G_RM_RA_ZB_OPA_SURF = RM_RA_ZB_OPA_SURF(1)
G_RM_RA_ZB_OPA_SURF2 = RM_RA_ZB_OPA_SURF(2)
G_RM_RA_ZB_OPA_DECAL = RM_RA_ZB_OPA_DECAL(1)
G_RM_RA_ZB_OPA_DECAL2 = RM_RA_ZB_OPA_DECAL(2)
G_RM_RA_ZB_OPA_INTER = RM_RA_ZB_OPA_INTER(1)
G_RM_RA_ZB_OPA_INTER2 = RM_RA_ZB_OPA_INTER(2)

G_RM_AA_OPA_SURF = RM_AA_OPA_SURF(1)
G_RM_AA_OPA_SURF2 = RM_AA_OPA_SURF(2)
G_RM_AA_XLU_SURF = RM_AA_XLU_SURF(1)
G_RM_AA_XLU_SURF2 = RM_AA_XLU_SURF(2)
G_RM_AA_XLU_LINE = RM_AA_XLU_LINE(1)
G_RM_AA_XLU_LINE2 = RM_AA_XLU_LINE(2)
G_RM_AA_DEC_LINE = RM_AA_DEC_LINE(1)
G_RM_AA_DEC_LINE2 = RM_AA_DEC_LINE(2)
G_RM_AA_TEX_EDGE = RM_AA_TEX_EDGE(1)
G_RM_AA_TEX_EDGE2 = RM_AA_TEX_EDGE(2)
G_RM_AA_SUB_SURF = RM_AA_SUB_SURF(1)
G_RM_AA_SUB_SURF2 = RM_AA_SUB_SURF(2)
G_RM_AA_PCL_SURF = RM_AA_PCL_SURF(1)
G_RM_AA_PCL_SURF2 = RM_AA_PCL_SURF(2)
G_RM_AA_OPA_TERR = RM_AA_OPA_TERR(1)
G_RM_AA_OPA_TERR2 = RM_AA_OPA_TERR(2)
G_RM_AA_TEX_TERR = RM_AA_TEX_TERR(1)
G_RM_AA_TEX_TERR2 = RM_AA_TEX_TERR(2)
G_RM_AA_SUB_TERR = RM_AA_SUB_TERR(1)
G_RM_AA_SUB_TERR2 = RM_AA_SUB_TERR(2)

G_RM_RA_OPA_SURF = RM_RA_OPA_SURF(1)
G_RM_RA_OPA_SURF2 = RM_RA_OPA_SURF(2)

G_RM_ZB_OPA_SURF = RM_ZB_OPA_SURF(1)
G_RM_ZB_OPA_SURF2 = RM_ZB_OPA_SURF(2)
G_RM_ZB_XLU_SURF = RM_ZB_XLU_SURF(1)
G_RM_ZB_XLU_SURF2 = RM_ZB_XLU_SURF(2)
G_RM_ZB_OPA_DECAL = RM_ZB_OPA_DECAL(1)
G_RM_ZB_OPA_DECAL2 = RM_ZB_OPA_DECAL(2)
G_RM_ZB_XLU_DECAL = RM_ZB_XLU_DECAL(1)
G_RM_ZB_XLU_DECAL2 = RM_ZB_XLU_DECAL(2)
G_RM_ZB_CLD_SURF = RM_ZB_CLD_SURF(1)
G_RM_ZB_CLD_SURF2 = RM_ZB_CLD_SURF(2)
G_RM_ZB_OVL_SURF = RM_ZB_OVL_SURF(1)
G_RM_ZB_OVL_SURF2 = RM_ZB_OVL_SURF(2)
G_RM_ZB_PCL_SURF = RM_ZB_PCL_SURF(1)
G_RM_ZB_PCL_SURF2 = RM_ZB_PCL_SURF(2)

G_RM_OPA_SURF = RM_OPA_SURF(1)
G_RM_OPA_SURF2 = RM_OPA_SURF(2)
G_RM_XLU_SURF = RM_XLU_SURF(1)
G_RM_XLU_SURF2 = RM_XLU_SURF(2)
G_RM_CLD_SURF = RM_CLD_SURF(1)
G_RM_CLD_SURF2 = RM_CLD_SURF(2)
G_RM_TEX_EDGE = RM_TEX_EDGE(1)
G_RM_TEX_EDGE2 = RM_TEX_EDGE(2)
G_RM_PCL_SURF = RM_PCL_SURF(1)
G_RM_PCL_SURF2 = RM_PCL_SURF(2)
G_RM_ADD = RM_ADD(1)
G_RM_ADD2 = RM_ADD(2)
G_RM_NOOP = RM_NOOP(1)
G_RM_NOOP2 = RM_NOOP(2)
G_RM_VISCVG = RM_VISCVG(1)
G_RM_VISCVG2 = RM_VISCVG(2)
G_RM_OPA_CI = RM_OPA_CI(1)
G_RM_OPA_CI2 = RM_OPA_CI(2)

G_RM_FOG_SHADE_A = GBL_c1(G_BL_CLR_FOG, G_BL_A_SHADE, G_BL_CLR_IN, G_BL_1MA)
G_RM_FOG_PRIM_A = GBL_c1(G_BL_CLR_FOG, G_BL_A_FOG, G_BL_CLR_IN, G_BL_1MA)
G_RM_PASS = GBL_c1(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1)

G_RM_RA_SPRITE = (AA_EN | CVG_DST_CLAMP | ZMODE_OPA | CVG_X_ALPHA | ALPHA_CVG_SEL | GBL_c1(
    G_BL_CLR_IN, G_BL_A_IN,                                                        G_BL_CLR_MEM, G_BL_1MA))
G_RM_RA_SPRITE2 = (AA_EN | CVG_DST_CLAMP | ZMODE_OPA | CVG_X_ALPHA | ALPHA_CVG_SEL | GBL_c2(
    G_BL_CLR_IN, G_BL_A_IN,                                                        G_BL_CLR_MEM, G_BL_1MA))

G_ZS_PIXEL = (0 << G_MDSFT_ZSRCSEL)
G_ZS_PRIM = (1 << G_MDSFT_ZSRCSEL)


@dataclass
class rm_preset:
    rm: int
    name: str


rm_presets = [
    rm_preset(G_RM_OPA_SURF, "G_RM_OPA_SURF"),
    rm_preset(G_RM_OPA_SURF2, "G_RM_OPA_SURF2"),
    rm_preset(G_RM_AA_OPA_SURF, "G_RM_AA_OPA_SURF"),
    rm_preset(G_RM_AA_OPA_SURF2, "G_RM_AA_OPA_SURF2"),
    rm_preset(G_RM_RA_OPA_SURF, "G_RM_RA_OPA_SURF"),
    rm_preset(G_RM_RA_OPA_SURF2, "G_RM_RA_OPA_SURF2"),
    rm_preset(G_RM_ZB_OPA_SURF, "G_RM_ZB_OPA_SURF"),
    rm_preset(G_RM_ZB_OPA_SURF2, "G_RM_ZB_OPA_SURF2"),
    rm_preset(G_RM_AA_ZB_OPA_SURF, "G_RM_AA_ZB_OPA_SURF"),
    rm_preset(G_RM_AA_ZB_OPA_SURF2, "G_RM_AA_ZB_OPA_SURF2"),
    rm_preset(G_RM_RA_ZB_OPA_SURF, "G_RM_RA_ZB_OPA_SURF"),
    rm_preset(G_RM_RA_ZB_OPA_SURF2, "G_RM_RA_ZB_OPA_SURF2"),
    rm_preset(G_RM_XLU_SURF, "G_RM_XLU_SURF"),
    rm_preset(G_RM_XLU_SURF2, "G_RM_XLU_SURF2"),
    rm_preset(G_RM_AA_XLU_SURF, "G_RM_AA_XLU_SURF"),
    rm_preset(G_RM_AA_XLU_SURF2, "G_RM_AA_XLU_SURF2"),
    rm_preset(G_RM_ZB_XLU_SURF, "G_RM_ZB_XLU_SURF"),
    rm_preset(G_RM_ZB_XLU_SURF2, "G_RM_ZB_XLU_SURF2"),
    rm_preset(G_RM_AA_ZB_XLU_SURF, "G_RM_AA_ZB_XLU_SURF"),
    rm_preset(G_RM_AA_ZB_XLU_SURF2, "G_RM_AA_ZB_XLU_SURF2"),
    rm_preset(G_RM_ZB_OPA_DECAL, "G_RM_ZB_OPA_DECAL"),
    rm_preset(G_RM_ZB_OPA_DECAL2, "G_RM_ZB_OPA_DECAL2"),
    rm_preset(G_RM_AA_ZB_OPA_DECAL, "G_RM_AA_ZB_OPA_DECAL"),
    rm_preset(G_RM_AA_ZB_OPA_DECAL2, "G_RM_AA_ZB_OPA_DECAL2"),
    rm_preset(G_RM_RA_ZB_OPA_DECAL, "G_RM_RA_ZB_OPA_DECAL"),
    rm_preset(G_RM_RA_ZB_OPA_DECAL2, "G_RM_RA_ZB_OPA_DECAL2"),
    rm_preset(G_RM_ZB_XLU_DECAL, "G_RM_ZB_XLU_DECAL"),
    rm_preset(G_RM_ZB_XLU_DECAL2, "G_RM_ZB_XLU_DECAL2"),
    rm_preset(G_RM_AA_ZB_XLU_DECAL, "G_RM_AA_ZB_XLU_DECAL"),
    rm_preset(G_RM_AA_ZB_XLU_DECAL2, "G_RM_AA_ZB_XLU_DECAL2"),
    rm_preset(G_RM_AA_ZB_OPA_INTER, "G_RM_AA_ZB_OPA_INTER"),
    rm_preset(G_RM_AA_ZB_OPA_INTER2, "G_RM_AA_ZB_OPA_INTER2"),
    rm_preset(G_RM_RA_ZB_OPA_INTER, "G_RM_RA_ZB_OPA_INTER"),
    rm_preset(G_RM_RA_ZB_OPA_INTER2, "G_RM_RA_ZB_OPA_INTER2"),
    rm_preset(G_RM_AA_ZB_XLU_INTER, "G_RM_AA_ZB_XLU_INTER"),
    rm_preset(G_RM_AA_ZB_XLU_INTER2, "G_RM_AA_ZB_XLU_INTER2"),
    rm_preset(G_RM_AA_XLU_LINE, "G_RM_AA_XLU_LINE"),
    rm_preset(G_RM_AA_XLU_LINE2, "G_RM_AA_XLU_LINE2"),
    rm_preset(G_RM_AA_ZB_XLU_LINE, "G_RM_AA_ZB_XLU_LINE"),
    rm_preset(G_RM_AA_ZB_XLU_LINE2, "G_RM_AA_ZB_XLU_LINE2"),
    rm_preset(G_RM_AA_DEC_LINE, "G_RM_AA_DEC_LINE"),
    rm_preset(G_RM_AA_DEC_LINE2, "G_RM_AA_DEC_LINE2"),
    rm_preset(G_RM_AA_ZB_DEC_LINE, "G_RM_AA_ZB_DEC_LINE"),
    rm_preset(G_RM_AA_ZB_DEC_LINE2, "G_RM_AA_ZB_DEC_LINE2"),
    rm_preset(G_RM_TEX_EDGE, "G_RM_TEX_EDGE"),
    rm_preset(G_RM_TEX_EDGE2, "G_RM_TEX_EDGE2"),
    rm_preset(G_RM_AA_TEX_EDGE, "G_RM_AA_TEX_EDGE"),
    rm_preset(G_RM_AA_TEX_EDGE2, "G_RM_AA_TEX_EDGE2"),
    rm_preset(G_RM_AA_ZB_TEX_EDGE, "G_RM_AA_ZB_TEX_EDGE"),
    rm_preset(G_RM_AA_ZB_TEX_EDGE2, "G_RM_AA_ZB_TEX_EDGE2"),
    rm_preset(G_RM_AA_ZB_TEX_INTER, "G_RM_AA_ZB_TEX_INTER"),
    rm_preset(G_RM_AA_ZB_TEX_INTER2, "G_RM_AA_ZB_TEX_INTER2"),
    rm_preset(G_RM_AA_SUB_SURF, "G_RM_AA_SUB_SURF"),
    rm_preset(G_RM_AA_SUB_SURF2, "G_RM_AA_SUB_SURF2"),
    rm_preset(G_RM_AA_ZB_SUB_SURF, "G_RM_AA_ZB_SUB_SURF"),
    rm_preset(G_RM_AA_ZB_SUB_SURF2, "G_RM_AA_ZB_SUB_SURF2"),
    rm_preset(G_RM_PCL_SURF, "G_RM_PCL_SURF"),
    rm_preset(G_RM_PCL_SURF2, "G_RM_PCL_SURF2"),
    rm_preset(G_RM_AA_PCL_SURF, "G_RM_AA_PCL_SURF"),
    rm_preset(G_RM_AA_PCL_SURF2, "G_RM_AA_PCL_SURF2"),
    rm_preset(G_RM_ZB_PCL_SURF, "G_RM_ZB_PCL_SURF"),
    rm_preset(G_RM_ZB_PCL_SURF2, "G_RM_ZB_PCL_SURF2"),
    rm_preset(G_RM_AA_ZB_PCL_SURF, "G_RM_AA_ZB_PCL_SURF"),
    rm_preset(G_RM_AA_ZB_PCL_SURF2, "G_RM_AA_ZB_PCL_SURF2"),
    rm_preset(G_RM_AA_OPA_TERR, "G_RM_AA_OPA_TERR"),
    rm_preset(G_RM_AA_OPA_TERR2, "G_RM_AA_OPA_TERR2"),
    rm_preset(G_RM_AA_ZB_OPA_TERR, "G_RM_AA_ZB_OPA_TERR"),
    rm_preset(G_RM_AA_ZB_OPA_TERR2, "G_RM_AA_ZB_OPA_TERR2"),
    rm_preset(G_RM_AA_TEX_TERR, "G_RM_AA_TEX_TERR"),
    rm_preset(G_RM_AA_TEX_TERR2, "G_RM_AA_TEX_TERR2"),
    rm_preset(G_RM_AA_ZB_TEX_TERR, "G_RM_AA_ZB_TEX_TERR"),
    rm_preset(G_RM_AA_ZB_TEX_TERR2, "G_RM_AA_ZB_TEX_TERR2"),
    rm_preset(G_RM_AA_SUB_TERR, "G_RM_AA_SUB_TERR"),
    rm_preset(G_RM_AA_SUB_TERR2, "G_RM_AA_SUB_TERR2"),
    rm_preset(G_RM_AA_ZB_SUB_TERR, "G_RM_AA_ZB_SUB_TERR"),
    rm_preset(G_RM_AA_ZB_SUB_TERR2, "G_RM_AA_ZB_SUB_TERR2"),
    rm_preset(G_RM_CLD_SURF, "G_RM_CLD_SURF"),
    rm_preset(G_RM_CLD_SURF2, "G_RM_CLD_SURF2"),
    rm_preset(G_RM_ZB_CLD_SURF, "G_RM_ZB_CLD_SURF"),
    rm_preset(G_RM_ZB_CLD_SURF2, "G_RM_ZB_CLD_SURF2"),
    rm_preset(G_RM_ZB_OVL_SURF, "G_RM_ZB_OVL_SURF"),
    rm_preset(G_RM_ZB_OVL_SURF2, "G_RM_ZB_OVL_SURF2"),
    rm_preset(G_RM_ADD, "G_RM_ADD"),
    rm_preset(G_RM_ADD2, "G_RM_ADD2"),
    rm_preset(G_RM_VISCVG, "G_RM_VISCVG"),
    rm_preset(G_RM_VISCVG2, "G_RM_VISCVG2"),
    rm_preset(G_RM_OPA_CI, "G_RM_OPA_CI"),
    rm_preset(G_RM_OPA_CI2, "G_RM_OPA_CI2"),
    rm_preset(G_RM_RA_SPRITE, "G_RM_RA_SPRITE"),
    rm_preset(G_RM_RA_SPRITE2, "G_RM_RA_SPRITE2"),
]

bl1_presets = [
    rm_preset(G_RM_FOG_SHADE_A, "G_RM_FOG_SHADE_A"),
    rm_preset(G_RM_FOG_PRIM_A, "G_RM_FOG_PRIM_A"),
    rm_preset(G_RM_PASS, "G_RM_PASS"),
    rm_preset(G_RM_NOOP, "G_RM_NOOP"),
]

bl2_presets = [
    rm_preset(G_RM_NOOP2, "G_RM_NOOP2")
]


def strarg_acmuxc(v):
    return {
        G_ACMUX_LOD_FRACTION: "LOD_FRACTION",
        G_ACMUX_TEXEL0: "TEXEL0",
        G_ACMUX_TEXEL1: "TEXEL1",
        G_ACMUX_PRIMITIVE: "PRIMITIVE",
        G_ACMUX_SHADE: "SHADE",
        G_ACMUX_ENVIRONMENT: "ENVIRONMENT",
        G_ACMUX_PRIM_LOD_FRAC: "PRIM_LOD_FRAC",
    }.get(v, "0")


def strarg_ccmuxa(v):
    return {
        G_CCMUX_COMBINED: "COMBINED",
        G_CCMUX_TEXEL0: "TEXEL0",
        G_CCMUX_TEXEL1: "TEXEL1",
        G_CCMUX_PRIMITIVE: "PRIMITIVE",
        G_CCMUX_SHADE: "SHADE",
        G_CCMUX_ENVIRONMENT: "ENVIRONMENT",
        G_CCMUX_1: "1",
        G_CCMUX_NOISE: "NOISE",
    }.get(v, "0")


def strarg_ccmuxb(v):
    return {
        G_CCMUX_COMBINED: "COMBINED",
        G_CCMUX_TEXEL0: "TEXEL0",
        G_CCMUX_TEXEL1: "TEXEL1",
        G_CCMUX_PRIMITIVE: "PRIMITIVE",
        G_CCMUX_SHADE: "SHADE",
        G_CCMUX_ENVIRONMENT: "ENVIRONMENT",
        G_CCMUX_CENTER: "CENTER",
        G_CCMUX_K4: "K4",
    }.get(v, "0")


def strarg_ccmuxc(v):
    return {
        G_CCMUX_COMBINED: "COMBINED",
        G_CCMUX_TEXEL0: "TEXEL0",
        G_CCMUX_TEXEL1: "TEXEL1",
        G_CCMUX_PRIMITIVE: "PRIMITIVE",
        G_CCMUX_SHADE: "SHADE",
        G_CCMUX_ENVIRONMENT: "ENVIRONMENT",
        G_CCMUX_SCALE: "SCALE",
        G_CCMUX_COMBINED_ALPHA: "COMBINED_ALPHA",
        G_CCMUX_TEXEL0_ALPHA: "TEXEL0_ALPHA",
        G_CCMUX_TEXEL1_ALPHA: "TEXEL1_ALPHA",
        G_CCMUX_PRIMITIVE_ALPHA: "PRIMITIVE_ALPHA",
        G_CCMUX_SHADE_ALPHA: "SHADE_ALPHA",
        G_CCMUX_ENV_ALPHA: "ENV_ALPHA",
        G_CCMUX_LOD_FRACTION: "LOD_FRACTION",
        G_CCMUX_PRIM_LOD_FRAC: "PRIM_LOD_FRAC",
        G_CCMUX_K5: "K5",
    }.get(v, "0")


def strarg_ccmuxd(v):
    return {
        G_CCMUX_COMBINED: "COMBINED",
        G_CCMUX_TEXEL0: "TEXEL0",
        G_CCMUX_TEXEL1: "TEXEL1",
        G_CCMUX_PRIMITIVE: "PRIMITIVE",
        G_CCMUX_SHADE: "SHADE",
        G_CCMUX_ENVIRONMENT: "ENVIRONMENT",
        G_CCMUX_1: "1",
    }.get(v, "0")


def strarg_acmuxabd(v):
    return {
        G_ACMUX_COMBINED: "COMBINED",
        G_ACMUX_TEXEL0: "TEXEL0",
        G_ACMUX_TEXEL1: "TEXEL1",
        G_ACMUX_PRIMITIVE: "PRIMITIVE",
        G_ACMUX_SHADE: "SHADE",
        G_ACMUX_ENVIRONMENT: "ENVIRONMENT",
        G_ACMUX_1: "1",
    }.get(v, "0")


def strarg_acmuxc(v):
    return {
        G_ACMUX_LOD_FRACTION: "LOD_FRACTION",
        G_ACMUX_TEXEL0: "TEXEL0",
        G_ACMUX_TEXEL1: "TEXEL1",
        G_ACMUX_PRIMITIVE: "PRIMITIVE",
        G_ACMUX_SHADE: "SHADE",
        G_ACMUX_ENVIRONMENT: "ENVIRONMENT",
        G_ACMUX_PRIM_LOD_FRAC: "PRIM_LOD_FRAC",
    }.get(v, "0")


def strarg_tile(v):
    return {
        G_TX_LOADTILE: "G_TX_LOADTILE",
        G_TX_RENDERTILE: "G_TX_RENDERTILE",
    }.get(v, str(v))


def strarg_switch(v):
    return {
        G_ON: "G_ON",
        G_OFF: "G_OFF",
    }.get(v, str(v))


def strarg_fmt(v):
    return {
        G_IM_FMT_RGBA: "G_IM_FMT_RGBA",
        G_IM_FMT_YUV: "G_IM_FMT_YUV",
        G_IM_FMT_CI: "G_IM_FMT_CI",
        G_IM_FMT_IA: "G_IM_FMT_IA",
        G_IM_FMT_I: "G_IM_FMT_I",
    }.get(v, str(v))


def strarg_siz(v):
    return {
        G_IM_SIZ_4b: "G_IM_SIZ_4b",
        G_IM_SIZ_8b: "G_IM_SIZ_8b",
        G_IM_SIZ_16b: "G_IM_SIZ_16b",
        G_IM_SIZ_32b: "G_IM_SIZ_32b",
    }.get(v, str(v))


def strarg_cm(v):
    return {
        G_TX_MIRROR | G_TX_WRAP: "G_TX_MIRROR | G_TX_WRAP",
        G_TX_NOMIRROR | G_TX_WRAP: "G_TX_NOMIRROR | G_TX_WRAP",
        G_TX_MIRROR | G_TX_CLAMP: "G_TX_MIRROR | G_TX_CLAMP",
        G_TX_NOMIRROR | G_TX_CLAMP: "G_TX_NOMIRROR | G_TX_CLAMP",
    }.get(v, str(v))


def strarg_tm(v):
    return {
        G_TX_NOMASK: "G_TX_NOMASK",
    }.get(v, str(v))


def strarg_ts(v):
    return {
        G_TX_NOLOD: "G_TX_NOLOD",
    }.get(v, str(v))


MDMASK_RM_C1 = 0xCCCC0000
MDMASK_RM_C2 = 0x33330000
MDMASK_RM_LO = 0x0000FFF8


def MDMASK(siz, ft): return (((1 << siz)-1) << ft)


MDMASK_ALPHACOMPARE = MDMASK(G_MDSIZ_ALPHACOMPARE, G_MDSFT_ALPHACOMPARE)
MDMASK_ZSRCSEL = MDMASK(G_MDSIZ_ZSRCSEL, G_MDSFT_ZSRCSEL)
MDMASK_ALPHADITHER = MDMASK(G_MDSIZ_ALPHADITHER, G_MDSFT_ALPHADITHER)
MDMASK_RGBDITHER = MDMASK(G_MDSIZ_RGBDITHER, G_MDSFT_RGBDITHER)
MDMASK_COMBKEY = MDMASK(G_MDSIZ_COMBKEY, G_MDSFT_COMBKEY)
MDMASK_TEXTCONV = MDMASK(G_MDSIZ_TEXTCONV, G_MDSFT_TEXTCONV)
MDMASK_TEXTFILT = MDMASK(G_MDSIZ_TEXTFILT, G_MDSFT_TEXTFILT)
MDMASK_TEXTLUT = MDMASK(G_MDSIZ_TEXTLUT, G_MDSFT_TEXTLUT)
MDMASK_TEXTLOD = MDMASK(G_MDSIZ_TEXTLOD, G_MDSFT_TEXTLOD)
MDMASK_TEXTDETAIL = MDMASK(G_MDSIZ_TEXTDETAIL, G_MDSFT_TEXTDETAIL)
MDMASK_TEXTPERSP = MDMASK(G_MDSIZ_TEXTPERSP, G_MDSFT_TEXTPERSP)
MDMASK_CYCLETYPE = MDMASK(G_MDSIZ_CYCLETYPE, G_MDSFT_CYCLETYPE)
MDMASK_PIPELINE = MDMASK(G_MDSIZ_PIPELINE, G_MDSFT_PIPELINE)


def rm_mode_str(buf, arg):
    if (arg & AA_EN):
        buf += ("AA_EN")
    if (arg & Z_CMP):
        if (len(buf) > 0):
            buf += (" | ")
        buf += ("Z_CMP")

    if (arg & Z_UPD):
        if (len(buf) > 0):
            buf += (" | ")
        buf += ("Z_UPD")

    if (arg & IM_RD):
        if (len(buf) > 0):
            buf += (" | ")
        buf += ("IM_RD")

    if (arg & CLR_ON_CVG):
        if (len(buf) > 0):
            buf += (" | ")
        buf += ("CLR_ON_CVG")

    if (len(buf) > 0):
        buf += (" | ")
    cvg = arg & 0x00000300
    if cvg == CVG_DST_CLAMP:
        buf += "CVG_DST_CLAMP"
    elif cvg == CVG_DST_WRAP:
        buf += "CVG_DST_WRAP"
    elif cvg == CVG_DST_FULL:
        buf += "CVG_DST_FULL"
    elif cvg == CVG_DST_SAVE:
        buf += "CVG_DST_SAVE"
    zmode = arg & 0x00000C00
    if zmode == ZMODE_OPA:
        buf += " | ZMODE_OPA"
    elif zmode == ZMODE_INTER:
        buf += " | ZMODE_INTER"
    elif zmode == ZMODE_XLU:
        buf += " | ZMODE_XLU"
    elif zmode == ZMODE_DEC:
        buf += " | ZMODE_DEC"

    if (arg & CVG_X_ALPHA):
        buf += (" | CVG_X_ALPHA")
    if (arg & ALPHA_CVG_SEL):
        buf += (" | ALPHA_CVG_SEL")
    if (arg & FORCE_BL):
        buf += (" | FORCE_BL")
    return buf


def rm_cbl_str(buf, arg, c):
    if (c == 2):
        arg <<= 2
    bp = (arg >> 30) & 0b11
    if bp == G_BL_CLR_IN:
        buf += f"GBL_c{c}(G_BL_CLR_IN"
    elif bp == G_BL_CLR_MEM:
        buf += f"GBL_c{c}(G_BL_CLR_MEM"
    elif bp == G_BL_CLR_BL:
        buf += f"GBL_c{c}(G_BL_CLR_BL"
    elif bp == G_BL_CLR_FOG:
        buf += f"GBL_c{c}(G_BL_CLR_FOG"

    ba = (arg >> 26) & 0b11
    if ba == G_BL_A_IN:
        buf += ", G_BL_A_IN"
    if ba == G_BL_A_FOG:
        buf += ", G_BL_A_FOG"
    if ba == G_BL_A_SHADE:
        buf += ", G_BL_A_SHADE"
    if ba == G_BL_0:
        buf += ", G_BL_0"

    bm = (arg >> 22) & 0b11
    if bm == G_BL_CLR_IN:
        buf += ", G_BL_CLR_IN"
    elif bm == G_BL_CLR_MEM:
        buf += ", G_BL_CLR_MEM"
    elif bm == G_BL_CLR_BL:
        buf += ", G_BL_CLR_BL"
    elif bm == G_BL_CLR_FOG:
        buf += ", G_BL_CLR_FOG"

    bb = (arg >> 18) & 0b11
    if bb == G_BL_1MA:
        buf += ", G_BL_1MA)"
    elif bb == G_BL_A_MEM:
        buf += ", G_BL_A_MEM)"
    elif bb == G_BL_1:
        buf += ", G_BL_1)"
    elif bb == G_BL_0:
        buf += ", G_BL_0)"

    return buf


def othermodehi_str(arg, which):
    buf = ""
    ad_mask = MDMASK_ALPHADITHER
    if ((arg | which) & ad_mask):
        ad = arg & ad_mask
        if ad == G_AD_PATTERN:
            buf += ("G_AD_PATTERN")
        elif ad == G_AD_NOTPATTERN:
            buf += ("G_AD_NOTPATTERN")
        elif ad == G_AD_NOISE:
            buf += ("G_AD_NOISE")
        elif ad == G_AD_DISABLE:
            buf += ("G_AD_DISABLE")
        else:
            buf += hex(ad)
    cd_mask = MDMASK_RGBDITHER
    if ((arg | which) & cd_mask):
        if (len(buf) > 0):
            buf += (" | ")
        cd = arg & cd_mask
        if cd == G_CD_MAGICSQ:
            buf += ("G_CD_MAGICSQ")
        elif cd == G_CD_BAYER:
            buf += ("G_CD_BAYER")
        elif cd == G_CD_NOISE:
            buf += ("G_CD_NOISE")
        elif cd == G_CD_DISABLE:
            buf += ("G_CD_DISABLE")
        else:
            buf += hex(cd)

    ck_mask = MDMASK_COMBKEY
    if ((arg | which) & ck_mask):
        if (len(buf) > 0):
            buf += (" | ")
        ck = arg & ck_mask
        if ck == G_CK_NONE:
            buf += ("G_CK_NONE")
        elif ck == G_CK_KEY:
            buf += ("G_CK_KEY")
        else:
            buf += hex(ck)

    tc_mask = MDMASK_TEXTCONV
    if ((arg | which) & tc_mask):
        if (len(buf) > 0):
            buf += (" | ")
        tc = arg & tc_mask
        if tc == G_TC_CONV:
            buf += ("G_TC_CONV")
        elif tc == G_TC_FILTCONV:
            buf += ("G_TC_FILTCONV")
        elif tc == G_TC_FILT:
            buf += ("G_TC_FILT")
        else:
            buf += hex(tc)

    tf_mask = MDMASK_TEXTFILT
    if ((arg | which) & tf_mask):
        if (len(buf) > 0):
            buf += (" | ")
        tf = arg & tf_mask
        if tf == G_TF_POINT:
            buf += ("G_TF_POINT")
        elif tf == G_TF_BILERP:
            buf += ("G_TF_BILERP")
        elif tf == G_TF_AVERAGE:
            buf += ("G_TF_AVERAGE")
        else:
            buf += hex(tf)

    tt_mask = MDMASK_TEXTLUT
    if ((arg | which) & tt_mask):
        if (len(buf) > 0):
            buf += (" | ")
        tt = arg & tt_mask
        if tt == G_TT_NONE:
            buf += ("G_TT_NONE")
        elif tt == G_TT_RGBA16:
            buf += ("G_TT_RGBA16")
        elif tt == G_TT_IA16:
            buf += ("G_TT_IA16")
        else:
            buf += hex(tt)

    tl_mask = MDMASK_TEXTLOD
    if ((arg | which) & tl_mask):
        if (len(buf) > 0):
            buf += (" | ")
        tl = arg & tl_mask
        if tl == G_TL_TILE:
            buf += ("G_TL_TILE")
        elif tl == G_TL_LOD:
            buf += ("G_TL_LOD")
        else:
            buf += hex(tl)

    td_mask = MDMASK_TEXTDETAIL
    if ((arg | which) & td_mask):
        if (len(buf) > 0):
            buf += (" | ")
        td = arg & td_mask
        if td == G_TD_CLAMP:
            buf += ("G_TD_CLAMP")
        elif td == G_TD_SHARPEN:
            buf += ("G_TD_SHARPEN")
        elif td == G_TD_DETAIL:
            buf += ("G_TD_DETAIL")
        else:
            buf += hex(td)

    tp_mask = MDMASK_TEXTPERSP
    if ((arg | which) & tp_mask):
        if (len(buf) > 0):
            buf += (" | ")
        tp = arg & tp_mask
        if tp == G_TP_NONE:
            buf += ("G_TP_NONE")
        elif tp == G_TP_PERSP:
            buf += ("G_TP_PERSP")
        else:
            buf += hex(tp)

    cyc_mask = MDMASK_CYCLETYPE
    if ((arg | which) & cyc_mask):
        if (len(buf) > 0):
            buf += (" | ")
        cyc = arg & cyc_mask
        if cyc == G_CYC_1CYCLE:
            buf += ("G_CYC_1CYCLE")
        elif cyc == G_CYC_2CYCLE:
            buf += ("G_CYC_2CYCLE")
        elif cyc == G_CYC_COPY:
            buf += ("G_CYC_COPY")
        elif cyc == G_CYC_FILL:
            buf += ("G_CYC_FILL")
        else:
            buf += hex(cyc)

    pm_mask = MDMASK_PIPELINE
    if ((arg | which) & pm_mask):
        if (len(buf) > 0):
            buf += (" | ")
        pm = arg & pm_mask
        if pm == G_PM_NPRIMITIVE:
            buf += ("G_PM_NPRIMITIVE")
        elif pm == G_PM_1PRIMITIVE:
            buf += ("G_PM_1PRIMITIVE")
        else:
            buf += hex(pm)

    unk_mask = ~(ad_mask | cd_mask | ck_mask | tc_mask | tf_mask |
                 tt_mask | tl_mask | td_mask | tp_mask | cyc_mask |
                 pm_mask)
    if (arg & unk_mask):
        if (len(buf) > 0):
            buf += (" | ")
        unk = arg & unk_mask
        buf += hex(unk)
    return buf


def strarg_ad(arg):
    return othermodehi_str(arg, (MDMASK_ALPHADITHER))


def strarg_cd(arg):
    return othermodehi_str(arg, (MDMASK_RGBDITHER))


def strarg_ck(arg):
    return othermodehi_str(arg, (MDMASK_COMBKEY))


def strarg_tc(arg):
    return othermodehi_str(arg, (MDMASK_TEXTCONV))


def strarg_tf(arg):
    return othermodehi_str(arg, (MDMASK_TEXTFILT))


def strarg_tt(arg):
    return othermodehi_str(arg, (MDMASK_TEXTLUT))


def strarg_tl(arg):
    return othermodehi_str(arg, (MDMASK_TEXTLOD))


def strarg_td(arg):
    return othermodehi_str(arg, (MDMASK_TEXTDETAIL))


def strarg_tp(arg):
    return othermodehi_str(arg, (MDMASK_TEXTPERSP))


def strarg_cyc(arg):
    return othermodehi_str(arg, (MDMASK_CYCLETYPE))


def strarg_pm(arg):
    return othermodehi_str(arg, (MDMASK_PIPELINE))


def strarg_othermodehi(arg):
    mask = (MDMASK_ALPHADITHER) | (MDMASK_RGBDITHER) | (MDMASK_COMBKEY) | (MDMASK_TEXTCONV) | (MDMASK_TEXTFILT) | (
        MDMASK_TEXTLUT) | (MDMASK_TEXTLOD) | (MDMASK_TEXTDETAIL) | (MDMASK_TEXTPERSP) | (MDMASK_CYCLETYPE) | (MDMASK_PIPELINE)
    return othermodehi_str(arg, mask)


def othermodelo_str(arg, which):
    buf = ""
    rm_c1_mask = MDMASK_RM_C1
    rm_c2_mask = MDMASK_RM_C2
    rm_mode_lo = MDMASK_RM_LO
    rm_mask = rm_c1_mask | rm_c2_mask | rm_mode_lo
    pre_c1: rm_preset = None
    pre_c2: rm_preset = None
    pre_c1_ind = -2
    pre_c1_ind = -2
    for i, pre in enumerate(rm_presets):
        rm_c1 = arg & (rm_c1_mask | rm_mode_lo | (pre.rm & ~rm_mask))
        if (pre_c1 == None and rm_c1 == pre.rm):
            pre_c1 = pre
            pre_c1_ind = i
        rm_c2 = arg & (rm_c2_mask | rm_mode_lo | (pre.rm & ~rm_mask))
        if (pre_c2 == None and rm_c2 == pre.rm):
            pre_c2 = pre
            pre_c2_ind = i

    if (pre_c1 == None or pre_c2 == None or pre_c1_ind + 1 != pre_c2_ind):
        for i, pre in enumerate(bl1_presets):
            rm_c1 = arg & (rm_c1_mask | (pre.rm & ~rm_mask))
            if (rm_c1 == pre.rm):
                pre_c1 = pre
                break

        for i, pre in enumerate(bl2_presets):
            rm_c2 = arg & (rm_c2_mask | (pre.rm & ~rm_mask))
            if (rm_c2 == pre.rm):
                pre_c2 = pre
                break

    pre_rm = 0
    if (pre_c1 != None):
        pre_rm |= pre_c1.rm
    if (pre_c2 != None):
        pre_rm |= pre_c2.rm
    ac_mask = MDMASK_ALPHACOMPARE
    if (((arg & ~pre_rm) | which) & ac_mask):
        ac = arg & ac_mask
        if (ac == G_AC_NONE):
            buf += "G_AC_NONE"
        elif (ac == G_AC_THRESHOLD):
            buf += "G_AC_THRESHOLD"
        elif (ac == G_AC_DITHER):
            buf += "G_AC_DITHER"
        else:
            buf += f"{ac:04x}"

    zs_mask = MDMASK_ZSRCSEL
    if (((arg & ~pre_rm) | which) & zs_mask):
        if (len(buf) > 0):
            buf += " | "
        zs = arg & zs_mask
        if (zs == G_ZS_PIXEL):
            buf += "G_ZS_PIXEL"
        elif (zs == G_ZS_PRIM):
            buf += "G_ZS_PRIM"
        else:
            buf += f"{ac:04x}"

    rm = arg & (rm_mask | pre_rm)
    if (((arg & ~pre_rm) | which) & rm_mode_lo):
        if (len(buf) > 0):
            buf += " | "
        buf = rm_mode_str(buf, rm)

    c = 0
    if (which & rm_c1_mask):
        c |= 1
    if (which & rm_c2_mask):
        c |= 2
    if (c & 1 or (c == 0 and arg & rm_c1_mask)):
        if (len(buf) > 0):
            buf += " | "
        if (pre_c1):
            buf += pre_c1.name
        else:
            buf = rm_cbl_str(buf, rm, 1)

    if (c & 2 or (c == 0 and arg & rm_c2_mask)):
        if (len(buf) > 0):
            buf += " | "
        if (pre_c2):
            buf += pre_c2.name
        else:
            buf = rm_cbl_str(buf, rm, 2)

    unk_mask = ~(rm_mask | ac_mask | zs_mask)
    if (arg & unk_mask):
        if (len(buf) > 0):
            buf += " | "
        unk = arg & unk_mask
        buf += unk
    return buf


def strarg_rm1(v):
    return othermodelo_str(v, MDMASK_RM_C1)


def strarg_rm2(v):
    return othermodelo_str(v, MDMASK_RM_C2)


def strarg_ac(v):
    return othermodelo_str(v, MDMASK_ALPHACOMPARE)


def strarg_zs(v):
    return othermodelo_str(v, MDMASK_ZSRCSEL)


def strarg_orthermodelo(v):
    return othermodelo_str(v, MDMASK_ALPHACOMPARE | MDMASK_ZSRCSEL | MDMASK_RM_C1 | MDMASK_RM_C2)


def strarg_texwrap(v):
    return {
        GX_CLAMP: "GX_CLAMP",
        GX_REPEAT: "GX_REPEAT",
        GX_MIRROR: "GX_MIRROR",
        GX_MAX_TEXWRAPMODE: "GX_MAX_TEXWRAPMODE",
    }.get(v, str(v))


def strarg_dolphintile(v):
    return {
        G_DOLPHIN_TLUT_DEFAULT_MODE: "G_DOLPHIN_TLUT_DEFAULT_MODE"
    }.get(v, str(v))


def strarg_gm(arg):
    buf = ""
    if (arg == 0):
        buf += ("0")
        return buf

    if (arg & G_ZBUFFER):
        buf += ("G_ZBUFFER")
    if (arg & G_TEXTURE_ENABLE):
        if (len(buf) > 0):
            buf += (" | ")
        buf += ("G_TEXTURE_ENABLE")

    if (arg & G_SHADE):
        if (len(buf) > 0):
            buf += (" | ")
        buf += ("G_SHADE")

    if ((arg & G_CULL_BOTH) == G_CULL_BOTH):
        if (len(buf) > 0):
            buf += (" | ")
        buf += ("G_CULL_BOTH")

    else:
        if (arg & G_CULL_FRONT):
            if (len(buf) > 0):
                buf += (" | ")
            buf += ("G_CULL_FRONT")

        if (arg & G_CULL_BACK):
            if (len(buf) > 0):
                buf += (" | ")
            buf += ("G_CULL_BACK")

    if (arg & G_FOG):
        if (len(buf) > 0):
            buf += (" | ")
        buf += ("G_FOG")

    if (arg & G_LIGHTING):
        if (len(buf) > 0):
            buf += (" | ")
        buf += ("G_LIGHTING")

    if (arg & G_TEXTURE_GEN):
        if (len(buf) > 0):
            buf += (" | ")
        buf += ("G_TEXTURE_GEN")

    if (arg & G_TEXTURE_GEN_LINEAR):
        if (len(buf) > 0):
            buf += (" | ")
        buf += ("G_TEXTURE_GEN_LINEAR")

    if (arg & G_LOD):
        if (len(buf) > 0):
            buf += (" | ")
        buf += ("G_LOD")

    if (arg & G_SHADING_SMOOTH):
        if (len(buf) > 0):
            buf += (" | ")
        buf += ("G_SHADING_SMOOTH")

    if (arg & G_CLIPPING):
        if (len(buf) > 0):
            buf += (" | ")
        buf += ("G_CLIPPING")

    arg = arg & ~(G_ZBUFFER | G_TEXTURE_ENABLE | G_SHADE | G_CULL_BOTH | G_FOG |
                  G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_LOD |
                  G_SHADING_SMOOTH | G_CLIPPING)
    if (arg):
        if (len(buf) > 0):
            buf += (" | ")
        buf += f"{arg:08x}"

    return buf


def strarg_mp(arg):
    buf = ""
    if (arg & G_MTX_PUSH):
        buf += ("G_MTX_PUSH")
    else:
        buf += ("G_MTX_NOPUSH")

    if (arg & G_MTX_LOAD):
        buf += (" | G_MTX_LOAD")
    else:
        buf += (" | G_MTX_MUL")

    if (arg & G_MTX_PROJECTION):
        buf += (" | G_MTX_PROJECTION")
    else:
        buf += (" | G_MTX_MODELVIEW")

    for i in range(3, 8):
        if (arg & (1 << i)):
            buf += (" | 0x%02x" % (1 << i))
    return buf


@dataclass
class BitToArgs:
    offset: int
    size: int
    data_location: int
    to_str: callable = (lambda x: str(x))


B2A = BitToArgs


def extract_data(buff, offs, size): return (buff >> offs) & ((1 << size) - 1)


def extract_data_upper(buff, offs=0, size=32): return extract_data(
    int.from_bytes(buff[0:4], 'big'), offs, size)


def extract_data_lower(buff, offs=0, size=32): return extract_data(
    int.from_bytes(buff[4:8], 'big'), offs, size)


def gf_call(name: str, data: bytes, *offs: BitToArgs) -> str:
    upper_data = extract_data_upper(data)
    lower_data = extract_data_lower(data)
    datas = [lower_data, upper_data, (upper_data << 32) | lower_data]
    strs_out = []
    for bitArgs in offs:
        if bitArgs == GFX_SYMBOL:
            strs_out.append(symbol_lookup(lower_data))
        else:
            strs_out.append(bitArgs.to_str(extract_data(
                datas[bitArgs.data_location], bitArgs.offset, bitArgs.size)))
    if SHOW_CODE:
        return f"/* {upper_data:08x} {lower_data:08x} */ {name}({', '.join(strs_out)})"
    else:
        return f"{name}({', '.join(strs_out)})"


def unsupported_gfx_call(data):
    if SHOW_CODE:
        return f"/* {extract_data_upper(data):08x} {extract_data_lower(data):08x} */ UNSUPPORTED_CALL({", ".join(f"0x{d:02x}" for d in data)})"
    else:
        return f"UNSUPPORTED_CALL({", ".join(f"0x{d:02x}" for d in data)})"


def gfx_gsSPTexture(data):
    if (extract_data_upper(data, 16, 8) == BOWTIE_VAL):
        return gf_call("gsSPTexture", data, B2A(16, 16, DL), B2A(0, 16, DL), B2A(11, 3, DU), B2A(8, 3, DU, strarg_tile), B2A(1, 7, DU, strarg_switch))
    else:
        return gf_call("gsSPTextureL", data, B2A(16, 16, DL), B2A(0, 16, DL), B2A(11, 3, DU), B2A(16, 8, DU), B2A(8, 3, DU, strarg_tile), B2A(1, 7, DU, strarg_switch))


def gfx_gsDPSetRenderMode(data):
    return gf_call("gsDPSetRenderMode", data, B2A(0, 32, DL, strarg_rm1), B2A(0, 32, DL, strarg_rm2))


def gfx_gsSPSetOther_Lo(data):
    length = extract_data_upper(data, 0, 8) + 1
    shift = 32 - (extract_data_upper(data, 8, 8) + length)
    return {
        (G_MDSFT_ALPHACOMPARE, G_MDSIZ_ALPHACOMPARE): None,
        (G_MDSFT_ZSRCSEL, G_MDSIZ_ZSRCSEL): None,
        (G_MDSFT_RENDERMODE, G_MDSIZ_RENDERMODE): gfx_gsDPSetRenderMode
    }.get((shift, length), unsupported_gfx_call)(data)


def gfx_gsDPSetTextureLUT(data):
    return gf_call("gsDPSetTextureLUT", data,
                   B2A(0, 32, DL, strarg_tt))


def gfx_gsSPSetOther_Hi(data):
    length = extract_data_upper(data, 0, 8) + 1
    shift = 32 - (extract_data_upper(data, 8, 8) + length)
    return {
        (G_MDSFT_ALPHADITHER, G_MDSIZ_ALPHADITHER): None,
        (G_MDSFT_RGBDITHER, G_MDSIZ_RGBDITHER): None,
        (G_MDSFT_COMBKEY, G_MDSIZ_COMBKEY): None,
        (G_MDSFT_TEXTCONV, G_MDSIZ_TEXTCONV): None,
        (G_MDSFT_TEXTFILT, G_MDSIZ_TEXTFILT): None,
        (G_MDSFT_TEXTLUT, G_MDSIZ_TEXTLUT): gfx_gsDPSetTextureLUT,
        (G_MDSFT_TEXTLOD, G_MDSIZ_TEXTLOD): None,
        (G_MDSFT_TEXTDETAIL, G_MDSIZ_TEXTDETAIL): None,
        (G_MDSFT_TEXTPERSP, G_MDSIZ_TEXTPERSP): None,
        (G_MDSFT_CYCLETYPE, G_MDSIZ_CYCLETYPE): None,
        (G_MDSFT_PIPELINE, G_MDSIZ_PIPELINE): None,
    }.get((shift, length), unsupported_gfx_call)(data)


def gfx_gsSPSettImg(data):
    if extract_data_upper(data, 18, 1) == 1:
        return gf_call("gsDPSetTextureImage_Dolphin", data,
                       B2A(21, 3, DU, strarg_fmt),
                       B2A(19, 2, DU, strarg_siz),
                       B2A(0, 10, DU, lambda x: str(x+1)),
                       B2A(10, 8, DU, lambda x: str((x+1)*4)),
                       GFX_SYMBOL)
    else:
        return gf_call("gsDPSetTextureImage", data,
                       B2A(21, 3, DU, strarg_fmt),
                       B2A(19, 2, DU, strarg_siz),
                       B2A(0, 12, DU, lambda x: str(x+1)),
                       GFX_SYMBOL)


def gfx_gsDPPipeSync(data):
    return gf_call("gsDPPipeSync", data)


def gfx_gsDPTileSync(data):
    return gf_call("gsDPTileSync", data)


def gfx_gsDPLoadSync(data):
    return gf_call("gsDPLoadSync", data)


def gfx_gsDPLoadTLUTCmd(data):
    if extract_data_upper(data, 22, 2) == G_TLUT_DOLPHIN:
        return gf_call("gsDPLoadTLUT_Dolphin", data, B2A(16, 4, DU), B2A(0, 14, DU), B2A(14, 2, DU), GFX_SYMBOL)
    else:
        return gf_call("gsDPLoadTLUTCmd", data, B2A(24, 3, DL, strarg_tile), B2A(14, 10, DL))


def gfx_SetCombineLERP(data):
    return gf_call("gsDPSetCombineLERP", data,
                   B2A(20, 4, DU, strarg_ccmuxa),
                   B2A(28, 4, DL, strarg_ccmuxb),
                   B2A(15, 5, DU, strarg_ccmuxc),
                   B2A(15, 3, DL, strarg_ccmuxd),
                   B2A(12, 3, DU, strarg_acmuxabd),
                   B2A(12, 3, DL, strarg_acmuxabd),
                   B2A(9, 3, DU, strarg_acmuxc),
                   B2A(9, 3, DL, strarg_acmuxabd),
                   B2A(5, 4, DU, strarg_ccmuxa),
                   B2A(24, 4, DL, strarg_ccmuxb),
                   B2A(0, 5, DU, strarg_ccmuxc),
                   B2A(6, 3, DL, strarg_ccmuxd),
                   B2A(21, 3, DL, strarg_acmuxabd),
                   B2A(3, 3, DL, strarg_acmuxabd),
                   B2A(18, 3, DL, strarg_acmuxc),
                   B2A(0, 3, DL, strarg_acmuxabd))


def gfx_gsDPSetTile(data):
    return gf_call("gsDPSetTile", data,
                   B2A(21, 3, DU, strarg_fmt),
                   B2A(19, 2, DU, strarg_siz),
                   B2A(9, 9, DU),
                   B2A(0, 9, DU),
                   B2A(24, 3, DL, strarg_tile),
                   B2A(20, 4, DL),
                   B2A(18, 2, DL, strarg_cm),
                   B2A(14, 4, DL, strarg_tm),
                   B2A(10, 4, DL, strarg_ts),
                   B2A(8, 2, DL, strarg_cm),
                   B2A(4, 4, DL, strarg_tm),
                   B2A(0, 4, DL, strarg_ts),
                   )


def gfx_gsDPLoadBlock(data):
    return gf_call("gsDPLoadBlock", data,
                   B2A(24, 3, DL, strarg_tile),
                   B2A(12, 12, DU),
                   B2A(0, 12, DU),
                   B2A(12, 12, DL),
                   B2A(0, 12, DL),
                   )


def gfx_gsDPSetTileSize(data):
    return gf_call("gsDPSetTileSize", data,
                   B2A(24, 3, DL, strarg_tile),
                   B2A(12, 12, DU),
                   B2A(0, 12, DU),
                   B2A(12, 12, DL),
                   B2A(0, 12, DL),
                   )


def gfx_gsSp1Triangle(data):
    def _C(v):
        return str(v//2)
    return gf_call("gsSP1Triangle", data,
                   B2A(16, 8, DU, _C),
                   B2A(8, 8, DU, _C),
                   B2A(0, 8, DU, _C),
                   B2A(0, 1, DU, lambda _: "0")
                   )


def gfx_gsDPSetEnvColor(data):
    return gf_call("gsDPSetEnvColor", data,
                   B2A(24, 8, DL),
                   B2A(16, 8, DL),
                   B2A(8, 8, DL),
                   B2A(0, 8, DL))


def gfx_gsDPSetTile_Dolphin(data):
    return gf_call("gsDPSetTile_Dolphin", data, B2A(20, 4, DU, strarg_dolphintile), B2A(16, 3, DU), B2A(12, 4, DU), B2A(10, 2, DU, strarg_texwrap), B2A(8, 2, DU, strarg_texwrap), B2A(4, 4, DU), B2A(4, 4, DU))


def gfx_dl(data):
    if extract_data_upper(data, 16, 8) == 0:
        return gf_call("gsSPDisplayList", data, GFX_SYMBOL)
    else:
        return gf_call("gsSPBranchList", data, GFX_SYMBOL)


def gfx_gsSPEndDisplayList(data):
    return gf_call("gsSPEndDisplayList", data)


def gfx_gsSPGeometryMode(data):
    clear_bits = ~extract_data_upper(data, 0, 24) & 0xffffff
    set_bits = extract_data_lower(data)
    if (clear_bits == 0xffffff):
        return gf_call("gsSPLoadGeometryMode", data, B2A(0, 32, DL, strarg_gm))
    elif clear_bits == 0:
        return gf_call("gsSPSetGeometryMode", data, B2A(0, 32, DL, strarg_gm))
    elif set_bits == 0:
        return gf_call("gsSPClearGeometryMode", data, B2A(0, 24, DU, lambda x: strarg_gm(~x & 0xffffff)))
    else:
        return gf_call("gsSPGeometryMode", data, B2A(0, 24, DU, lambda x: strarg_gm(~x & 0xffffff)), B2A(0, 32, DL, strarg_gm))


def gfx_gsSPVertex(data):
    global triangle_count, extended_func
    n = extract_data_upper(data, 12, 8)

    return gf_call("gsSPVertex", data, GFX_SYMBOL, B2A(12, 8, DU), B2A(1, 7, DU, lambda x: str(x-n)))


def gfx_gsSP2Triangles(data):
    def _C(v):
        return str(v//2)
    return gf_call("gsSP2Triangles", data,
                   B2A(16, 8, DU, _C),
                   B2A(8, 8, DU, _C),
                   B2A(0, 8, DU, _C),
                   B2A(0, 1, DU, lambda _: "0"),
                   B2A(16, 8, DL, _C),
                   B2A(8, 8, DL, _C),
                   B2A(0, 8, DL, _C),
                   B2A(0, 1, DL, lambda _: "0"))


triangle_count = 0
extended_func = None


def gfx_gsSPNTrianglesInit(data):
    global triangle_count, extended_func
    assert (extract_data_lower(data, 0, 1) == 0)
    # if extract_data_lower(data, 0, 1) == 0:
    #     count = extract_data_upper(data, 17, 7) + 1
    #     outs = gf_call("gsSPNTrianglesInit_7b", data, B2A(17, 7, DU, lambda x: str(x+1)),
    #                    B2A(4, 5, DL), B2A(9, 5, DL), B2A(14, 5, DL),
    #                    B2A(19, 5, DL), B2A(24, 5, DL), B2A(29, 5, DS),
    #                    B2A(2, 5, DU), B2A(7, 5, DU), B2A(12, 5, DU),
    #                    )
    #     this_extended_func = gfx_gsSPNTriangles_7b
    # else:
    #     count = extract_data_upper(data, 17, 7) + 1
    #     outs = gf_call("gsSPNTrianglesInit_5b", data, B2A(17, 7, DU, lambda x: str(x+1)),
    #                    B2A(4, 5, DL), B2A(9, 5, DL), B2A(14, 5, DL),
    #                    B2A(19, 5, DL), B2A(24, 5, DL), B2A(29, 5, DS),
    #                    B2A(2, 5, DU), B2A(7, 5, DU), B2A(12, 5, DU),
    #                    )
    #     this_extended_func = gfx_gsSPNTriangles_5b

    count = extract_data_upper(data, 17, 7) + 1
    outs = gf_call("gsSPNTrianglesInit_5b", data, B2A(17, 7, DU, lambda x: str(x+1)),
                   B2A(4, 5, DL), B2A(9, 5, DL), B2A(14, 5, DL),
                   B2A(19, 5, DL), B2A(24, 5, DL), B2A(29, 5, DS),
                   B2A(2, 5, DU), B2A(7, 5, DU), B2A(12, 5, DU),
                   )
    this_extended_func = gfx_gsSPNTriangles_5b
    triangle_count = count - 3
    if triangle_count > 0:
        extended_func = this_extended_func
    return outs


def gfx_gsSPNTriangles_5b(data):
    global triangle_count, extended_func
    triangle_count -= 4
    if triangle_count <= 0:
        extended_func = None
    return gf_call("gsSPNTriangles_5b", data,
                   B2A(4, 5, DL), B2A(9, 5, DL), B2A(14, 5, DL),
                   B2A(19, 5, DL), B2A(24, 5, DL), B2A(29, 5, DS),
                   B2A(2, 5, DU), B2A(7, 5, DU), B2A(12, 5, DU),
                   B2A(17, 5, DU), B2A(22, 5, DU), B2A(27, 5, DU))


def gfx_gsSPMatrix(data):
    return gf_call("gsSPMatrix", data,
                   GFX_SYMBOL, B2A(0, 8, DU, lambda x: strarg_mp(x ^ G_MTX_PUSH)))


def gfx_gsDPSetPrimColor(data):
    return gf_call("gsDPSetPrimColor", data,
                   B2A(8, 8, DU), B2A(0, 8, DU),
                   B2A(24, 8, DL), B2A(16, 8, DL),
                   B2A(8, 8, DL), B2A(0, 8, DL))


# main
GFX_LOOKUP = {
    G_TEXTURE: gfx_gsSPTexture,
    G_SETCOMBINE: gfx_SetCombineLERP,
    G_SETOTHERMODE_L: gfx_gsSPSetOther_Lo,
    G_SETOTHERMODE_H: gfx_gsSPSetOther_Hi,
    G_SETTIMG: gfx_gsSPSettImg,
    G_SETTILE_DOLPHIN: gfx_gsDPSetTile_Dolphin,
    G_DL: gfx_dl,
    G_ENDDL: gfx_gsSPEndDisplayList,
    G_GEOMETRYMODE: gfx_gsSPGeometryMode,
    G_VTX: gfx_gsSPVertex,
    G_TRIN_INDEPEND: gfx_gsSPNTrianglesInit,
    G_MTX: gfx_gsSPMatrix,
    G_SETPRIMCOLOR: gfx_gsDPSetPrimColor,
    G_RDPPIPESYNC: gfx_gsDPPipeSync,
    G_RDPTILESYNC: gfx_gsDPTileSync,
    G_RDPLOADSYNC: gfx_gsDPLoadSync,
    G_TRI2: gfx_gsSP2Triangles,
    G_LOADTLUT: gfx_gsDPLoadTLUTCmd,
    G_SETTILE: gfx_gsDPSetTile,
    G_LOADBLOCK: gfx_gsDPLoadBlock,
    G_SETTILESIZE: gfx_gsDPSetTileSize,
    G_TRI1: gfx_gsSp1Triangle,
    G_SETENVCOLOR: gfx_gsDPSetEnvColor
}


def convert_binary_to_gfx(b: bytes, symbol_names: list[str]):
    global symbol_stack
    symbol_stack = symbol_names
    i = 0
    out = []
    while True:
        chunk = b[i: i + 8]
        i += 8
        if len(chunk) < 8:
            break
        if extended_func:
            a = extended_func(chunk)
        else:
            a = GFX_LOOKUP.get(chunk[0], unsupported_gfx_call)(chunk)
        out.append(a)
    return ",\n".join(out)


def convert_binary_to_gfx_c_source(src_path, dest_path):
    global extended_func
    # Load data
    with open(src_path, "rb") as binary_file, open(dest_path, "w") as c_file:
        while True:
            chunk = binary_file.read(8)

            if len(chunk) < 8:
                break
            if extended_func:
                a = extended_func(chunk)
            else:
                a = GFX_LOOKUP.get(chunk[0], unsupported_gfx_call)(chunk)
            c_file.write(a)


def main():
    parser = ArgumentParser(
        description="Converts a binary file into gfx calls"
    )
    parser.add_argument("src_path", type=str, help="Binary source file path")
    parser.add_argument("dest_path", type=str,
                        help="Destination C include file path")

    args = parser.parse_args()
    convert_binary_to_gfx_c_source(args.src_path, args.dest_path)


if __name__ == "__main__":
    main()
