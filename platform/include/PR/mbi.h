/* Shadow PR/mbi.h - N64 F3DZEX2 GBI for arm64/Metal port.
 * Defines the Gfx union and all gSP/gDP macros used by AC's display lists.
 * The emu64 layer interprets these at runtime and translates to GX/Metal. */
#ifndef _PR_MBI_H_
#define _PR_MBI_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- Bit helpers ---- */
#define _SHIFTL(v, s, w) (((uint32_t)(v) & ((1u << (w)) - 1u)) << (s))
#define _SHIFTR(v, s, w) (((uint32_t)(v) >> (s)) & ((1u << (w)) - 1u))

/* ---- Core Gfx type ---- */
/* On 64-bit targets, Gfx is 16 bytes: the 'pwords' member holds a 64-bit
 * pointer in the second slot so static initializers with address constants
 * compile cleanly (Clang rejects pointer-to-uint32_t casts in constant exprs).
 * emu64 / the Metal renderer must step by sizeof(Gfx) = 16 bytes. */
typedef union {
    struct { uint32_t w0; uint32_t w1; } words;    /* integer GBI params  */
    struct { uint32_t cmd; void*    ptr; } pwords;  /* pointer GBI params  */
    long long int force_structure_alignment[2];     /* 16-byte size/align  */
} Gfx;

/* ---- GBI command opcodes (F3DZEX2 / libforest emu64) ---- */
/* SP geometry commands (0x01-0x0A) */
#define G_VTX            0x01
#define G_MODIFYVTX      0x02
#define G_CULLDL         0x03
#define G_BRANCH_Z       0x04
#define G_TRI1           0x05
#define G_TRI2           0x06
#define G_QUAD           0x07
#define G_LINE3D         0x08
#define G_TRIN           0x09
#define G_TRIN_INDEPEND  0x0A
/* SP state commands (0xD6-0xE3) */
#define G_TEXTURE        0xD7
#define G_POPMTX         0xD8
#define G_GEOMETRYMODE   0xD9
#define G_MTX            0xDA
#define G_MOVEWORD       0xDB
#define G_MOVEMEM        0xDC
#define G_LOAD_UCODE     0xDD
#define G_DL             0xDE
#define G_ENDDL          0xDF
#define G_SPNOOP         0xE0
#define G_SETOTHERMODE_L 0xE2
#define G_SETOTHERMODE_H 0xE3
/* Dolphin-specific extended SP commands */
#define G_SPECIAL_1      0xD5
#define G_SETTEXEDGEALPHA  0xCE
#define G_SETCOMBINE_NOTEV 0xCF
#define G_SETCOMBINE_TEV   0xD0
#define G_SETTILE_DOLPHIN  0xD2
/* Legacy aliases (some code uses old F3DEX2 names) */
#define G_SETGEOMETRYMODE  G_GEOMETRYMODE
#define G_CLEARGEOMETRYMODE G_GEOMETRYMODE
#define G_RDPHALF_1      0xE1   /* not in F3DZEX2 proper, but referenced */
#define G_RDPHALF_2      0xE1
#define G_RDPNOOP        0xC0
#define G_NOOP           0xC0

/* RDP opcodes */
#define G_SETCIMG        0xFF
#define G_SETZIMG        0xFE
#define G_SETTIMG        0xFD
#define G_SETCOMBINE     0xFC
#define G_SETENVCOLOR    0xFB
#define G_SETPRIMCOLOR   0xFA
#define G_SETBLENDCOLOR  0xF9
#define G_SETFOGCOLOR    0xF8
#define G_SETFILLCOLOR   0xF7
#define G_FILLRECT       0xF6
#define G_SETTILE        0xF5
#define G_LOADTILE       0xF4
#define G_LOADBLOCK      0xF3
#define G_LDTX_RECT      0xF2
#define G_LDTX_RECT_S    0xF1
#define G_SETTILESIZE    0xF2
#define G_LOADTLUT       0xF0
#define G_RDPSETOTHERMODE 0xEF
#define G_SETPRIMDEPTH   0xEE
#define G_SETSCISSOR     0xED
#define G_SETCONVERT     0xEC
#define G_SETKEYR        0xEB
#define G_SETKEYFB       0xEA
#define G_RDPFULLSYNC    0xE9
#define G_RDPTILESYNC    0xE8
#define G_RDPPIPESYNC    0xE7
#define G_RDPLOADSYNC    0xE6
#define G_RDPNOOP2       0xE6
#define G_TEXRECT        0xE4
#define G_TEXRECTFLIP    0xE5
#define G_RDPHALF_CONT   0xF9

/* ---- G_MTX flags ---- */
#define G_MTX_MODELVIEW  0x00
#define G_MTX_PROJECTION 0x01
#define G_MTX_MUL        0x00
#define G_MTX_LOAD       0x02
#define G_MTX_NOPUSH     0x00
#define G_MTX_PUSH       0x04

/* ---- G_MOVEWORD indices ---- */
#define G_MW_MATRIX      0x00
#define G_MW_NUMLIGHT    0x02
#define G_MW_CLIP        0x04
#define G_MW_SEGMENT     0x06
#define G_MW_FOG         0x08
#define G_MW_LIGHTCOL    0x0A
#define G_MW_PERSPNORM   0x0E
#define G_MW_SUBDL       0x10

#define G_MWO_NUMLIGHT   0x00
#define G_MWO_CLIP_RNX   0x04
#define G_MWO_CLIP_RNY   0x0C
#define G_MWO_CLIP_RPX   0x14
#define G_MWO_CLIP_RPY   0x1C
#define G_MWO_SEGMENT_0  0x00
#define G_MWO_SEGMENT_1  0x04
#define G_MWO_SEGMENT_2  0x08
#define G_MWO_SEGMENT_3  0x0C
#define G_MWO_SEGMENT_4  0x10
#define G_MWO_SEGMENT_5  0x14
#define G_MWO_SEGMENT_6  0x18
#define G_MWO_SEGMENT_7  0x1C
#define G_MWO_SEGMENT_8  0x20
#define G_MWO_SEGMENT_9  0x24
#define G_MWO_SEGMENT_A  0x28
#define G_MWO_SEGMENT_B  0x2C
#define G_MWO_SEGMENT_C  0x30
#define G_MWO_SEGMENT_D  0x34
#define G_MWO_SEGMENT_E  0x38
#define G_MWO_SEGMENT_F  0x3C
#define G_MWO_FOG        0x00

/* ---- G_MOVEMEM indices ---- */
#define G_MV_VIEWPORT    0x08
#define G_MV_L0          0x0A
#define G_MV_LIGHT       G_MV_L0
#define G_MV_MATRIX      0x0E
#define G_MV_LOOKATY     0x00   /* lookat Y index (separate movemem) */
#define G_MV_LOOKATX     0x02   /* lookat X index (separate movemem) */
/* Offsets within lights memory for lookat vectors */
#define G_MVO_LOOKATX    0x08
#define G_MVO_LOOKATY    0x10

/* ---- Light definitions ---- */
#define NUMLIGHTS_0      0
#define NUMLIGHTS_1      1
#define NUMLIGHTS_2      2
#define NUMLIGHTS_3      3
#define NUMLIGHTS_4      4
#define NUMLIGHTS_5      5
#define NUMLIGHTS_6      6
#define NUMLIGHTS_7      7
#define NUMLIGHTS_MAX    7

/* ---- Geometry mode bits ---- */
#define G_ZBUFFER           0x00000001
#define G_SHADE             0x00000004
#define G_CULL_FRONT        0x00000200
#define G_CULL_BACK         0x00000400
#define G_CULL_BOTH         0x00000600
#define G_FOG               0x00010000
#define G_LIGHTING          0x00020000
#define G_TEXTURE_GEN       0x00040000
#define G_TEXTURE_GEN_LINEAR 0x00080000
#define G_LOD               0x00100000
#define G_SHADING_SMOOTH    0x00200000
#define G_CLIPPING          0x00800000

/* ---- G_SETOTHERMODE_L / _H bits ---- */
#define G_MDSFT_ALPHACOMPARE  0
#define G_MDSFT_ZSRCSEL       2
#define G_MDSFT_RENDERMODE    3
#define G_MDSFT_BLENDER       16
#define G_MDSFT_BLENDMASK     0
#define G_MDSFT_ALPHADITHER   4
#define G_MDSFT_RGBDITHER     6
#define G_MDSFT_COMBKEY       8
#define G_MDSFT_TEXTCONV      9
#define G_MDSFT_TEXTFILT      12
#define G_MDSFT_TEXTLUT       14
#define G_MDSFT_TEXTLOD       16
#define G_MDSFT_TEXTDETAIL    17
#define G_MDSFT_TEXTPERSP     19
#define G_MDSFT_CYCLETYPE     20
#define G_MDSFT_PIPELINE      23

#define G_PM_1PRIMITIVE  (1 << G_MDSFT_ZSRCSEL)
#define G_PM_NPRIMITIVE  (0 << G_MDSFT_ZSRCSEL)

/* Cycle type */
#define G_CYC_1CYCLE     (_SHIFTL(0, G_MDSFT_CYCLETYPE, 2))
#define G_CYC_2CYCLE     (_SHIFTL(1, G_MDSFT_CYCLETYPE, 2))
#define G_CYC_COPY       (_SHIFTL(2, G_MDSFT_CYCLETYPE, 2))
#define G_CYC_FILL       (_SHIFTL(3, G_MDSFT_CYCLETYPE, 2))

/* Texture perspective */
#define G_TP_NONE        (_SHIFTL(0, G_MDSFT_TEXTPERSP, 1))
#define G_TP_PERSP       (_SHIFTL(1, G_MDSFT_TEXTPERSP, 1))

/* Texture filter */
#define G_TF_POINT       (_SHIFTL(0, G_MDSFT_TEXTFILT, 2))
#define G_TF_AVERAGE     (_SHIFTL(3, G_MDSFT_TEXTFILT, 2))
#define G_TF_BILERP      (_SHIFTL(2, G_MDSFT_TEXTFILT, 2))

/* Texture LUT */
#define G_TT_NONE        (_SHIFTL(0, G_MDSFT_TEXTLUT, 2))
#define G_TT_RGBA16      (_SHIFTL(2, G_MDSFT_TEXTLUT, 2))
#define G_TT_IA16        (_SHIFTL(3, G_MDSFT_TEXTLUT, 2))

/* Texture LOD */
#define G_TL_TILE        (_SHIFTL(0, G_MDSFT_TEXTLOD, 1))
#define G_TL_LOD         (_SHIFTL(1, G_MDSFT_TEXTLOD, 1))

/* Texture detail */
#define G_TD_CLAMP       (_SHIFTL(0, G_MDSFT_TEXTDETAIL, 2))
#define G_TD_SHARPEN     (_SHIFTL(1, G_MDSFT_TEXTDETAIL, 2))
#define G_TD_DETAIL      (_SHIFTL(2, G_MDSFT_TEXTDETAIL, 2))

/* Alpha compare */
#define G_AC_NONE        (_SHIFTL(0, G_MDSFT_ALPHACOMPARE, 2))
#define G_AC_THRESHOLD   (_SHIFTL(1, G_MDSFT_ALPHACOMPARE, 2))
#define G_AC_DITHER      (_SHIFTL(3, G_MDSFT_ALPHACOMPARE, 2))

/* Alpha dither */
#define G_AD_PATTERN     (_SHIFTL(0, G_MDSFT_ALPHADITHER, 2))
#define G_AD_NOTPATTERN  (_SHIFTL(1, G_MDSFT_ALPHADITHER, 2))
#define G_AD_NOISE       (_SHIFTL(2, G_MDSFT_ALPHADITHER, 2))
#define G_AD_DISABLE     (_SHIFTL(3, G_MDSFT_ALPHADITHER, 2))

/* RGB dither */
#define G_CD_MAGICSQ     (_SHIFTL(0, G_MDSFT_RGBDITHER, 2))
#define G_CD_BAYER       (_SHIFTL(1, G_MDSFT_RGBDITHER, 2))
#define G_CD_NOISE       (_SHIFTL(2, G_MDSFT_RGBDITHER, 2))
#define G_CD_DISABLE     (_SHIFTL(3, G_MDSFT_RGBDITHER, 2))

/* Combine key */
#define G_CK_NONE        (_SHIFTL(0, G_MDSFT_COMBKEY, 1))
#define G_CK_KEY         (_SHIFTL(1, G_MDSFT_COMBKEY, 1))

/* Pipeline */
#define G_TP_NONE2       (_SHIFTL(0, G_MDSFT_PIPELINE, 1))
#define G_TP_1           (_SHIFTL(1, G_MDSFT_PIPELINE, 1))

/* G_TC_ (textconv) constants */
#define G_TC_CONV     (_SHIFTL(0, G_MDSFT_TEXTCONV, 3))
#define G_TC_FILTCONV (_SHIFTL(5, G_MDSFT_TEXTCONV, 3))
#define G_TC_FILT     (_SHIFTL(6, G_MDSFT_TEXTCONV, 3))

/* Z source */
#define G_ZS_PIXEL    (0 << G_MDSFT_ZSRCSEL)
#define G_ZS_PRIM     (1 << G_MDSFT_ZSRCSEL)

/* Blend mode alias: 1MA = 1 minus alpha */
#define G_BL_1MA      G_BL_1mA

/* Standard render mode composites */
#define G_RM_OPA_SURF    RM_OPA_SURF(1)
#define G_RM_OPA_SURF2   RM_OPA_SURF(2)
#define G_RM_XLU_SURF    RM_XLU_SURF(1)
#define G_RM_XLU_SURF2   RM_XLU_SURF(2)
#define G_RM_ZB_OPA_SURF    RM_ZB_OPA_SURF(1)
#define G_RM_ZB_OPA_SURF2   RM_ZB_OPA_SURF(2)
#define G_RM_AA_OPA_SURF    RM_AA_OPA_SURF(1)
#define G_RM_AA_OPA_SURF2   RM_AA_OPA_SURF(2)
#define G_RM_AA_XLU_SURF    RM_AA_XLU_SURF(1)
#define G_RM_AA_XLU_SURF2   RM_AA_XLU_SURF(2)
#define G_RM_AA_ZB_OPA_SURF  RM_AA_ZB_OPA_SURF(1)
#define G_RM_AA_ZB_OPA_SURF2 RM_AA_ZB_OPA_SURF(2)
#define G_RM_AA_ZB_XLU_SURF  RM_AA_ZB_XLU_SURF(1)
#define G_RM_AA_ZB_XLU_SURF2 RM_AA_ZB_XLU_SURF(2)
#define G_RM_FOG_SHADE_A     RM_FOG_SHADE_A(1)
#define G_RM_FOG_SHADE_A2    RM_FOG_SHADE_A(2)
#define G_RM_FOG_PRIM_A      RM_FOG_PRIM_A(1)
#define G_RM_FOG_PRIM_A2     RM_FOG_PRIM_A(2)
#define G_RM_PASS            RM_PASS(1)
#define G_RM_PASS2           RM_PASS(2)
/* Coverage visualization */
#define G_RM_VISCVG  (FORCE_BL | GBL_c1(G_BL_CLR_IN, G_BL_0, G_BL_CLR_BL, G_BL_1))
#define G_RM_VISCVG2 (FORCE_BL | GBL_c2(G_BL_CLR_IN, G_BL_0, G_BL_CLR_BL, G_BL_1))
/* Cloud surface */
#define RM_CLD_SURF(c) (IM_RD | CVG_DST_SAVE | ZMODE_OPA | FORCE_BL | \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define G_RM_CLD_SURF    RM_CLD_SURF(1)
#define G_RM_CLD_SURF2   RM_CLD_SURF(2)
#define G_RM_ZB_OPA_DECAL   RM_ZB_OPA_DECAL(1)
#define G_RM_ZB_OPA_DECAL2  RM_ZB_OPA_DECAL(2)
#define G_RM_AA_ZB_OPA_DECAL  RM_AA_ZB_OPA_DECAL(1)
#define G_RM_AA_ZB_OPA_DECAL2 RM_AA_ZB_OPA_DECAL(2)
#define G_RM_AA_ZB_XLU_DECAL  RM_AA_ZB_XLU_DECAL(1)
#define G_RM_AA_ZB_XLU_DECAL2 RM_AA_ZB_XLU_DECAL(2)
#define G_RM_AA_ZB_OPA_INTER  RM_AA_ZB_OPA_INTER(1)
#define G_RM_AA_ZB_OPA_INTER2 RM_AA_ZB_OPA_INTER(2)
#define G_RM_AA_ZB_XLU_INTER  RM_AA_ZB_XLU_INTER(1)
#define G_RM_AA_ZB_XLU_INTER2 RM_AA_ZB_XLU_INTER(2)
#define G_RM_AA_DEC_LINE    RM_AA_DEC_LINE(1)
#define G_RM_AA_DEC_LINE2   RM_AA_DEC_LINE(2)
#define G_RM_AA_ZB_DEC_LINE  RM_AA_ZB_DEC_LINE(1)
#define G_RM_AA_ZB_DEC_LINE2 RM_AA_ZB_DEC_LINE(2)
#define G_RM_ZB_CLD_SURF   RM_ZB_CLD_SURF(1)
#define G_RM_ZB_CLD_SURF2  RM_ZB_CLD_SURF(2)
#define G_RM_AA_ZB_TEX_EDGE  RM_AA_ZB_TEX_EDGE(1)
#define G_RM_AA_ZB_TEX_EDGE2 RM_AA_ZB_TEX_EDGE(2)
#define G_RM_AA_TEX_EDGE   RM_AA_TEX_EDGE(1)
#define G_RM_AA_TEX_EDGE2  RM_AA_TEX_EDGE(2)
#define G_RM_TEX_EDGE      RM_TEX_EDGE(1)
#define G_RM_TEX_EDGE2     RM_TEX_EDGE(2)
#define G_RM_ZB_XLU_SURF   RM_ZB_XLU_SURF(1)
#define G_RM_ZB_XLU_SURF2  RM_ZB_XLU_SURF(2)
#define G_RM_ZB_XLU_DECAL  RM_ZB_XLU_DECAL(1)
#define G_RM_ZB_XLU_DECAL2 RM_ZB_XLU_DECAL(2)
#define G_RM_ZB_OVL_SURF   RM_ZB_OVL_SURF(1)
#define G_RM_ZB_OVL_SURF2  RM_ZB_OVL_SURF(2)
#define G_RM_NOOP          RM_NOOP(1)
#define G_RM_NOOP2         RM_NOOP(2)

/* Render modes (common) */
#define AA_EN              0x8
#define Z_CMP              0x10
#define Z_UPD              0x20
#define IM_RD              0x40
#define CLR_ON_CVG         0x80
#define CVG_DST_CLAMP      0
#define CVG_DST_WRAP       0x100
#define CVG_DST_FULL       0x200
#define CVG_DST_SAVE       0x300
#define ZMODE_OPA          0
#define ZMODE_INTER        0x400
#define ZMODE_XLU          0x800
#define ZMODE_DEC          0xC00
#define CVG_X_ALPHA        0x1000
#define ALPHA_CVG_SEL      0x2000
#define FORCE_BL           0x4000

/* Blend modes */
#define GBL_c1(m1a, m1b, m2a, m2b) \
    (_SHIFTL(m1a, 30, 2) | _SHIFTL(m1b, 26, 2) | \
     _SHIFTL(m2a, 22, 2) | _SHIFTL(m2b, 18, 2))
#define GBL_c2(m1a, m1b, m2a, m2b) \
    (_SHIFTL(m1a, 28, 2) | _SHIFTL(m1b, 24, 2) | \
     _SHIFTL(m2a, 20, 2) | _SHIFTL(m2b, 16, 2))

#define G_BL_CLR_IN      0
#define G_BL_CLR_MEM     1
#define G_BL_CLR_BL      2
#define G_BL_CLR_FOG     3
#define G_BL_A_IN        0
#define G_BL_A_FOG       1
#define G_BL_A_SHADE     2
#define G_BL_0           3
#define G_BL_1mA         0
#define G_BL_A_MEM       1
#define G_BL_1           2

#define RM_AA_ZB_OPA_SURF(c)  (AA_EN|Z_CMP|Z_UPD|IM_RD|CVG_DST_CLAMP|ZMODE_OPA|ALPHA_CVG_SEL| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_AA_ZB_XLU_SURF(c)  (AA_EN|Z_CMP|IM_RD|CVG_DST_WRAP|CLR_ON_CVG|FORCE_BL|ZMODE_XLU| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_ZB_OPA_SURF(c)     (Z_CMP|Z_UPD|CVG_DST_CLAMP|ALPHA_CVG_SEL|ZMODE_OPA|FORCE_BL| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_OPA_SURF(c)        (CVG_DST_CLAMP|ZMODE_OPA|FORCE_BL| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_AA_OPA_SURF(c)     (AA_EN|CVG_DST_CLAMP|ALPHA_CVG_SEL|ZMODE_OPA| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_XLU_SURF(c)        (IM_RD|CVG_DST_FULL|FORCE_BL|ZMODE_OPA| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_AA_XLU_SURF(c)     (AA_EN|IM_RD|CVG_DST_WRAP|CLR_ON_CVG|FORCE_BL|ZMODE_OPA| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_FOG_SHADE_A(c)     (FORCE_BL|GBL_c##c(G_BL_CLR_FOG, G_BL_A_SHADE, G_BL_CLR_IN, G_BL_1mA))
#define RM_FOG_PRIM_A(c)      (FORCE_BL|GBL_c##c(G_BL_CLR_FOG, G_BL_A_FOG,   G_BL_CLR_IN, G_BL_1mA))
#define RM_PASS(c)            (FORCE_BL|GBL_c##c(G_BL_CLR_IN, G_BL_0,        G_BL_CLR_IN, G_BL_1))
#define RM_AA_ZB_OPA_DECAL(c) (AA_EN|Z_CMP|IM_RD|CVG_DST_WRAP|ALPHA_CVG_SEL|ZMODE_DEC| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_ZB_OPA_DECAL(c)    (Z_CMP|CVG_DST_WRAP|ALPHA_CVG_SEL|ZMODE_DEC|FORCE_BL| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_AA_ZB_XLU_DECAL(c) (AA_EN|Z_CMP|IM_RD|CVG_DST_WRAP|CLR_ON_CVG|FORCE_BL|ZMODE_DEC| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_ZB_XLU_DECAL(c)    (Z_CMP|IM_RD|CVG_DST_WRAP|CLR_ON_CVG|FORCE_BL|ZMODE_DEC| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_AA_ZB_OPA_INTER(c) (AA_EN|Z_CMP|Z_UPD|IM_RD|CVG_DST_CLAMP|ALPHA_CVG_SEL|ZMODE_INTER| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_ZB_OPA_INTER(c)    (Z_CMP|Z_UPD|CVG_DST_CLAMP|ALPHA_CVG_SEL|ZMODE_INTER|FORCE_BL| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_AA_ZB_XLU_INTER(c) (AA_EN|Z_CMP|IM_RD|CVG_DST_WRAP|CLR_ON_CVG|FORCE_BL|ZMODE_INTER| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_ZB_XLU_INTER(c)    (Z_CMP|IM_RD|CVG_DST_WRAP|CLR_ON_CVG|FORCE_BL|ZMODE_INTER| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_AA_XLU_LINE(c)     (AA_EN|IM_RD|CVG_DST_CLAMP|CVG_X_ALPHA|ALPHA_CVG_SEL|FORCE_BL|ZMODE_OPA| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_AA_ZB_XLU_LINE(c)  (AA_EN|Z_CMP|IM_RD|CVG_DST_CLAMP|CVG_X_ALPHA|ALPHA_CVG_SEL|FORCE_BL|ZMODE_OPA| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_AA_OPA_LINE(c)     (AA_EN|CVG_DST_CLAMP|CVG_X_ALPHA|ALPHA_CVG_SEL|FORCE_BL|ZMODE_OPA| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_AA_ZB_OPA_LINE(c)  (AA_EN|Z_CMP|Z_UPD|CVG_DST_CLAMP|CVG_X_ALPHA|ALPHA_CVG_SEL|FORCE_BL|ZMODE_OPA| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_AA_DEC_LINE(c)     (AA_EN|IM_RD|CVG_DST_CLAMP|CVG_X_ALPHA|ALPHA_CVG_SEL|FORCE_BL|ZMODE_DEC| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_AA_ZB_DEC_LINE(c)  (AA_EN|Z_CMP|IM_RD|CVG_DST_CLAMP|CVG_X_ALPHA|ALPHA_CVG_SEL|FORCE_BL|ZMODE_DEC| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_ZB_CLD_SURF(c)     (Z_CMP|Z_UPD|IM_RD|CVG_DST_SAVE|ZMODE_OPA|FORCE_BL| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_AA_ZB_TEX_EDGE(c)  (AA_EN|Z_CMP|Z_UPD|IM_RD|CVG_DST_CLAMP|CVG_X_ALPHA|ALPHA_CVG_SEL|ZMODE_OPA| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_AA_TEX_EDGE(c)     (AA_EN|IM_RD|CVG_DST_CLAMP|CVG_X_ALPHA|ALPHA_CVG_SEL|ZMODE_OPA| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_TEX_EDGE(c)        (CVG_DST_CLAMP|CVG_X_ALPHA|ALPHA_CVG_SEL|FORCE_BL|ZMODE_OPA|AA_EN| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_ZB_XLU_SURF(c)     (Z_CMP|IM_RD|CVG_DST_FULL|FORCE_BL|ZMODE_XLU| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_ZB_XLU_DECAL(c)    (Z_CMP|IM_RD|CVG_DST_FULL|FORCE_BL|ZMODE_DEC| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_ZB_OVL_SURF(c)     (Z_CMP|IM_RD|CVG_DST_SAVE|FORCE_BL|ZMODE_DEC| \
    GBL_c##c(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1mA))
#define RM_NOOP(c)            (GBL_c##c(0, 0, 0, 0))
#define RM_AA_ZB_OPA_SURF2    (RM_AA_ZB_OPA_SURF(2))
#define RM_AA_ZB_XLU_SURF2    (RM_AA_ZB_XLU_SURF(2))
#define RM_AA_ZB_OPA_SURF1    (RM_AA_ZB_OPA_SURF(1))
#define RM_AA_ZB_XLU_SURF1    (RM_AA_ZB_XLU_SURF(1))

/* ---- Color packing helpers ---- */
#define GPACK_RGBA5551(r, g, b, a) \
    ((((r) & 0x1F) << 11) | (((g) & 0x1F) << 6) | (((b) & 0x1F) << 1) | ((a) & 1))
#define GPACK_RGB24A8(r, g, b, a) \
    (((r) << 24) | ((g) << 16) | ((b) << 8) | (a))
#define GPACK_ZDZ(z, dz) \
    (((z) << 2) | (dz))

/* ---- Texture format / size ---- */
#define G_IM_FMT_RGBA  0
#define G_IM_FMT_YUV   1
#define G_IM_FMT_CI    2
#define G_IM_FMT_IA    3
#define G_IM_FMT_I     4

#define G_IM_SIZ_4b    0
#define G_IM_SIZ_8b    1
#define G_IM_SIZ_16b   2
#define G_IM_SIZ_32b   3
#define G_IM_SIZ_DD    5

#define G_IM_SIZ_4b_BYTES      0
#define G_IM_SIZ_8b_BYTES      1
#define G_IM_SIZ_16b_BYTES     2
#define G_IM_SIZ_32b_BYTES     4
#define G_IM_SIZ_4b_TILE_BYTES 0
#define G_IM_SIZ_8b_TILE_BYTES 1
#define G_IM_SIZ_16b_TILE_BYTES 2
#define G_IM_SIZ_32b_TILE_BYTES 2

#define G_IM_SIZ_4b_LINE_BYTES  0
#define G_IM_SIZ_8b_LINE_BYTES  1
#define G_IM_SIZ_16b_LINE_BYTES 2
#define G_IM_SIZ_32b_LINE_BYTES 4

#define G_IM_SIZ_4b_LOAD_BLOCK    0
#define G_IM_SIZ_8b_LOAD_BLOCK    0
#define G_IM_SIZ_16b_LOAD_BLOCK   1
#define G_IM_SIZ_32b_LOAD_BLOCK   1

/* LOADBLOCK count: (width*height + INCR) >> SHIFT */
#define G_IM_SIZ_4b_INCR    3
#define G_IM_SIZ_4b_SHIFT   2
#define G_IM_SIZ_8b_INCR    1
#define G_IM_SIZ_8b_SHIFT   1
#define G_IM_SIZ_16b_INCR   0
#define G_IM_SIZ_16b_SHIFT  0
#define G_IM_SIZ_32b_INCR   0
#define G_IM_SIZ_32b_SHIFT  0

/* G_TEXTURE_IMAGE_FRAC: fractional bits in tile size coords */
#define G_TEXTURE_IMAGE_FRAC 2

/* CALC_DXT: compute DXT (delta X texture) for LOADBLOCK.
 * DXT = ceil(2048 / bytes_per_row).  4b uses TILE_BYTES=0 → DXT=0 (no wrap). */
#define CALC_DXT(width, bsize) \
    ((bsize) > 0 ? (((1 << 11) + (width)*(bsize) - 1) / ((width)*(bsize))) : 0)

/* Texture tile indices */
#define G_TX_LOADTILE  7
#define G_TX_RENDERTILE 0

/* Texture tile parameters */
#define G_TX_NOMIRROR  (0 << 0)
#define G_TX_WRAP      (0 << 0)
#define G_TX_MIRROR    (1 << 0)
#define G_TX_CLAMP     (2 << 0)
#define G_TX_NOMASK    0
#define G_TX_NOLOD     0
#define G_TX_NOSCROLL  0

/* Texture coordinate fractional bits */
#define G_TEXTURE_IMAGE_FRAC  2
#define G_TEXTURE_SCALE_FRAC  16

/* ---- Scissor modes ---- */
#define G_SC_NON_INTERLACE 0
#define G_SC_ODD_INTERLACE 3
#define G_SC_EVEN_INTERLACE 2

/* ---- Combine modes ---- */
/* CC macros — 1-cycle and 2-cycle combine modes */
#define COMBINED      0
#define TEXEL0        1
#define TEXEL1        2
#define PRIMITIVE     3
#define SHADE         4
#define ENVIRONMENT   5
#define CENTER        6
#define SCALE         6
#define COMBINED_ALPHA 7
#define TEXEL0_ALPHA  8
#define TEXEL1_ALPHA  9
#define PRIMITIVE_ALPHA 10
#define SHADE_ALPHA   11
#define ENV_ALPHA     12
#define LOD_FRACTION  13
#define PRIM_LOD_FRAC 14
#define NOISE         7
#define K4            7
#define K5            15
#define ONE           6
#define ZERO          31

/* Alpha combine */
#define A_COMBINED    0
#define A_TEXEL0      1
#define A_TEXEL1      2
#define A_PRIMITIVE   3
#define A_SHADE       4
#define A_ENVIRONMENT 5
#define A_LODFRAC     6
#define A_PRIMLOD     7
#define A_ONE         6
#define A_ZERO        7

/* ---- SEGMENT_ADDR ---- */
#define SEGMENT_ADDR(seg, ofs) (((uint32_t)(seg) << 24) | (uint32_t)(ofs))

/* ---- Core DL helpers ---- */
/* Write a Gfx word to *pkt++ */
#define gImmp0(pkt, c) do {                     \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = _SHIFTL(c, 24, 8);          \
    _g->words.w1 = 0;                           \
} while(0)

#define gImmp1(pkt, c, p) do {                  \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(c, 24, 8) | (uint32_t)(p)); \
    _g->words.w1 = 0;                           \
} while(0)

#define gDma0p(pkt, c, s, l) do {               \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(c, 24, 8) | _SHIFTL((s), 0, 24)); \
    _g->words.w1 = (uint32_t)(l);               \
} while(0)

#define gDma1p(pkt, c, s, f, p) do {            \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(c, 24, 8) | _SHIFTL((s), 16, 8) | _SHIFTL((f), 0, 16)); \
    _g->words.w1 = (uint32_t)(p);               \
} while(0)

#define gDma2p(pkt, c, adrs, len, idx, ofs) do { \
    Gfx* _g = (Gfx*)(pkt);                       \
    _g->words.w0 = (_SHIFTL(c, 24, 8) | _SHIFTL((idx)*2, 16, 8) | _SHIFTL((ofs)*8, 8, 8) | _SHIFTL((len)*8-1, 0, 8)); \
    _g->words.w1 = (uint32_t)(adrs);             \
} while(0)

#define gSPNoOp(pkt) gImmp0(pkt, G_SPNOOP)

#define gSPMatrix(pkt, m, p) do {               \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(G_MTX, 24, 8) | _SHIFTL((uint32_t)sizeof(int[4][4]), 0, 16)); \
    _g->words.w1 = ((uint32_t)(p)) ^ 1;        \
    (void)(m);                                  \
} while(0)

#define gSPPopMatrix(pkt, n) do {               \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = _SHIFTL(G_POPMTX, 24, 8);   \
    _g->words.w1 = (uint32_t)(n) * 64;         \
} while(0)

/* F3DZEX2: w0 = (G_VTX<<24)|(n<<12)|((v0+n)<<1), w1 = ptr */
#define gSPVertex(pkt, v, n, v0) do {           \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(G_VTX, 24, 8) | _SHIFTL((n), 12, 8) | _SHIFTL((n)+(v0), 1, 7)); \
    _g->words.w1 = (uint32_t)(v);               \
} while(0)

#define gSPDisplayList(pkt, dl) dma1p(pkt, G_DL, 0, 0, (uint32_t)(dl))
#define gSPBranchList(pkt, dl)  dma1p(pkt, G_DL, 0, 1, (uint32_t)(dl))

/* Helper (avoids name conflict with gDma1p) */
#define dma1p(pkt, c, s, f, p) do {             \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(c, 24, 8) | _SHIFTL((s), 16, 8) | _SHIFTL((f), 0, 16)); \
    _g->words.w1 = (uint32_t)(p);               \
} while(0)

#define gSPEndDisplayList(pkt) do {             \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = _SHIFTL(G_ENDDL, 24, 8);    \
    _g->words.w1 = 0;                           \
} while(0)

#define gSPSegment(pkt, seg, base) do {         \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(G_MOVEWORD, 24, 8) | _SHIFTL(G_MW_SEGMENT, 16, 8) | (uint32_t)((seg) * 4)); \
    _g->words.w1 = (uint32_t)(base);            \
} while(0)

#define gSPNumLights(pkt, n) do {               \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(G_MOVEWORD, 24, 8) | _SHIFTL(G_MW_NUMLIGHT, 16, 8) | _SHIFTL(G_MWO_NUMLIGHT, 0, 16)); \
    _g->words.w1 = (uint32_t)(n) * 24;         \
} while(0)

#define gSPViewport(pkt, v) do {                \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(G_MOVEMEM, 24, 8) | _SHIFTL((sizeof(Vp_t)-1), 16, 8) | _SHIFTL(G_MV_VIEWPORT, 8, 8)); \
    _g->words.w1 = (uintptr_t)(v);              \
} while(0)

#define gSPLight(pkt, lp, n) do {               \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(G_MOVEMEM, 24, 8) | _SHIFTL(24-1, 16, 8) | _SHIFTL((n)-1, 8, 8) | 0x80); \
    _g->words.w1 = (uint32_t)(lp);              \
} while(0)

#define gSPLookAt(pkt, l) do {                  \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(G_MOVEMEM, 24, 8) | _SHIFTL(32-1, 16, 8) | _SHIFTL(0, 8, 8) | 0x00); \
    _g->words.w1 = (uint32_t)(l);               \
} while(0)

#define gSPFogPosition(pkt, min, max) do {      \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(G_MOVEWORD, 24, 8) | _SHIFTL(G_MW_FOG, 16, 8) | 4); \
    _g->words.w1 = (_SHIFTL((max), 16, 16) | _SHIFTL((min), 0, 16)); \
} while(0)

#define gSPTexture(pkt, sc, tc, level, tile, on) do { \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(G_TEXTURE, 24, 8) | _SHIFTL((level), 11, 3) | _SHIFTL((tile), 8, 3) | _SHIFTL((on), 0, 8)); \
    _g->words.w1 = (_SHIFTL((sc), 16, 16) | _SHIFTL((tc), 0, 16)); \
} while(0)

#define gSPPerspNormalize(pkt, s) do {          \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(G_MOVEWORD, 24, 8) | _SHIFTL(G_MW_PERSPNORM, 16, 8)); \
    _g->words.w1 = (uint32_t)(s);               \
} while(0)

#define gSPClipRatio(pkt, r) do { (void)(pkt); (void)(r); } while(0)

/* F3DZEX2 G_GEOMETRYMODE: w0[23:0]=clear_mask, w1[23:0]=set_mask */
#define gSPSetGeometryMode(pkt, m) do {         \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(G_GEOMETRYMODE, 24, 8) | 0x00FFFFFF); \
    _g->words.w1 = (uint32_t)(m);               \
} while(0)

#define gSPClearGeometryMode(pkt, m) do {       \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(G_GEOMETRYMODE, 24, 8) | (~(uint32_t)(m) & 0x00FFFFFF)); \
    _g->words.w1 = 0;                           \
} while(0)

#define gSPLoadGeometryMode(pkt, m) do {        \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = _SHIFTL(G_GEOMETRYMODE, 24, 8); \
    _g->words.w1 = (uint32_t)(m);               \
} while(0)

#define gSPGeometryMode(pkt, c, s) do {         \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(G_GEOMETRYMODE, 24, 8) | (~(uint32_t)(c) & 0x00FFFFFF)); \
    _g->words.w1 = (uint32_t)(s);               \
} while(0)

#define gSPSetLights(pkt, n, name) do { (void)(pkt); (void)(n); (void)&(name); } while(0)
#define gSPSetLights0(pkt, name) gSPSetLights(pkt, 0, name)
#define gSPSetLights1(pkt, name) gSPSetLights(pkt, 1, name)
#define gSPSetLights2(pkt, name) gSPSetLights(pkt, 2, name)
#define gSPSetLights3(pkt, name) gSPSetLights(pkt, 3, name)
#define gSPSetLights4(pkt, name) gSPSetLights(pkt, 4, name)
#define gSPSetLights5(pkt, name) gSPSetLights(pkt, 5, name)
#define gSPSetLights6(pkt, name) gSPSetLights(pkt, 6, name)
#define gSPSetLights7(pkt, name) gSPSetLights(pkt, 7, name)

#define gSPLoadUcode(pkt, ptext, pdata) do { (void)(pkt); (void)(ptext); (void)(pdata); } while(0)
#define gSPObjRenderMode(pkt, mode)     do { (void)(pkt); (void)(mode); } while(0)

/* Triangle dynamic macros (F3DZEX2 encoding) */
#define gSP1Triangle(pkt, v0, v1, v2, flag) do { \
    Gfx* _g = (Gfx*)(pkt);                       \
    _g->words.w0 = _SHIFTL(G_TRI1, 24, 8);       \
    _g->words.w1 = (_SHIFTL((v0)*2, 16, 8) | _SHIFTL((v1)*2, 8, 8) | _SHIFTL((v2)*2, 0, 8) | (flag)); \
} while(0)
#define gSP2Triangles(pkt, v00,v01,v02,f0, v10,v11,v12,f1) do { \
    Gfx* _g = (Gfx*)(pkt);                       \
    _g->words.w0 = (_SHIFTL(G_TRI2, 24, 8) | _SHIFTL((v10)*2, 16, 8) | _SHIFTL((v11)*2, 8, 8) | _SHIFTL((v12)*2, 0, 8) | (f1)); \
    _g->words.w1 = (_SHIFTL((v00)*2, 16, 8) | _SHIFTL((v01)*2, 8, 8) | _SHIFTL((v02)*2, 0, 8) | (f0)); \
} while(0)
#define gSPCullDisplayList(pkt, vstart, vend) do { \
    Gfx* _g = (Gfx*)(pkt);                        \
    _g->words.w0 = (_SHIFTL(G_CULLDL, 24, 8) | ((vstart)*2)); \
    _g->words.w1 = ((vend)*2);                     \
} while(0)
#define gSPModifyVertex(pkt, vtx, where, val) do { \
    Gfx* _g = (Gfx*)(pkt);                         \
    _g->words.w0 = (_SHIFTL(G_MODIFYVTX, 24, 8) | _SHIFTL((where), 16, 8) | ((vtx)*2)); \
    _g->words.w1 = (uint32_t)(val);                 \
} while(0)
#define gSPBranchLessZraw(pkt, branchdl, vtx, zval) do { \
    Gfx* _g = (Gfx*)(pkt);                               \
    _g->words.w0 = (_SHIFTL(G_BRANCH_Z, 24, 8) | ((vtx)*2)); \
    _g->words.w1 = (uint32_t)(uintptr_t)(branchdl);       \
} while(0)
#define gSP1Quadrangle(pkt, v0,v1,v2,v3,flag) do { \
    Gfx* _g = (Gfx*)(pkt);                          \
    _g->words.w0 = (_SHIFTL(G_QUAD, 24, 8) | _SHIFTL((v0)*2, 16, 8) | _SHIFTL((v1)*2, 8, 8) | _SHIFTL((v2)*2, 0, 8) | (flag)); \
    _g->words.w1 = (_SHIFTL((v3)*2, 0, 8));         \
} while(0)
#define gSPLine3D(pkt, v0, v1, flag) do { \
    Gfx* _g = (Gfx*)(pkt);               \
    _g->words.w0 = _SHIFTL(G_LINE3D, 24, 8); \
    _g->words.w1 = (_SHIFTL((v0)*2, 16, 8) | _SHIFTL((v1)*2, 8, 8) | (flag)); \
} while(0)

/* NTriangle init (F3DZEX2 extension) */
#define gSPNTrianglesInit(pkt, a, b, c, d) do { \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g->words.w0 = (_SHIFTL(G_TRIN, 24, 8) | _SHIFTL((b)*2, 16, 8) | _SHIFTL((c)*2, 8, 8) | _SHIFTL((d)*2, 0, 8)); \
    _g->words.w1 = (uint32_t)(a);               \
} while(0)

#define gSPScisTextureRectangle(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy) do { \
    Gfx* _g = (Gfx*)(pkt);                     \
    _g[0].words.w0 = (_SHIFTL(G_TEXRECT, 24, 8) | _SHIFTL((xh), 12, 12) | _SHIFTL((yh), 0, 12)); \
    _g[0].words.w1 = (_SHIFTL((xl), 12, 12)     | _SHIFTL((yl), 0, 12)); \
    _g[1].words.w0 = (_SHIFTL(G_RDPHALF_1, 24, 8) | _SHIFTL((tile), 24, 3)); \
    _g[1].words.w1 = 0;                         \
    _g[2].words.w0 = (_SHIFTL(G_RDPHALF_2, 24, 8) | _SHIFTL((s), 16, 16) | _SHIFTL((t), 0, 16)); \
    _g[2].words.w1 = (_SHIFTL((dsdx), 16, 16)  | _SHIFTL((dtdy), 0, 16)); \
} while(0)

#define gSPTextureRectangle(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy) \
    gSPScisTextureRectangle(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy)

#define gSPBgRect(pkt, bg) do { (void)(pkt); (void)(bg); } while(0)
#define gSPBgRectCopy(pkt, bg) do { (void)(pkt); (void)(bg); } while(0)

/* ---- DP macros ---- */
#define gDPNoOp(pkt) gImmp0(pkt, G_NOOP)
#define gDPFullSync(pkt) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = _SHIFTL(G_RDPFULLSYNC, 24, 8); _g->words.w1 = 0; } while(0)
#define gDPTileSync(pkt) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = _SHIFTL(G_RDPTILESYNC, 24, 8); _g->words.w1 = 0; } while(0)
#define gDPLoadSync(pkt) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = _SHIFTL(G_RDPLOADSYNC, 24, 8); _g->words.w1 = 0; } while(0)
#define gDPPipeSync(pkt) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = _SHIFTL(G_RDPPIPESYNC, 24, 8); _g->words.w1 = 0; } while(0)

#define gDPSetColorImage(pkt, fmt, siz, width, img) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_SETCIMG, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | _SHIFTL((width)-1, 0, 12)); \
    _g->words.w1 = (uint32_t)(img); } while(0)

#define gDPSetDepthImage(pkt, img) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = _SHIFTL(G_SETZIMG, 24, 8); \
    _g->words.w1 = (uint32_t)(img); } while(0)

#define gDPSetTextureImage(pkt, fmt, siz, width, img) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_SETTIMG, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | _SHIFTL((width)-1, 0, 12)); \
    _g->words.w1 = (uint32_t)(img); } while(0)

#define gDPSetCombineMode(pkt, a, b) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_SETCOMBINE, 24, 8) | (uint32_t)((a) >> 32)); \
    _g->words.w1 = (uint32_t)(a); (void)(b); } while(0)

#define gDPSetCombineLERP(pkt, a0,b0,c0,d0, aa0,ab0,ac0,ad0, a1,b1,c1,d1, aa1,ab1,ac1,ad1) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_SETCOMBINE, 24, 8) | _SHIFTL(a0, 20, 4) | _SHIFTL(c0, 15, 5) | \
                    _SHIFTL(aa0, 12, 3) | _SHIFTL(ac0, 9, 3) | _SHIFTL(a1, 5, 4) | _SHIFTL(c1, 0, 5)); \
    _g->words.w1 = (_SHIFTL(b0, 28, 4) | _SHIFTL(b1, 24, 4) | _SHIFTL(aa1, 21, 3) | \
                    _SHIFTL(ac1, 18, 3) | _SHIFTL(d0, 15, 3) | _SHIFTL(ab0, 12, 3) | \
                    _SHIFTL(ad0, 9, 3)  | _SHIFTL(d1, 6, 3)  | _SHIFTL(ab1, 3, 3) | _SHIFTL(ad1, 0, 3)); \
} while(0)

#define gDPSetEnvColor(pkt, r, g, b, a) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = _SHIFTL(G_SETENVCOLOR, 24, 8); \
    _g->words.w1 = (_SHIFTL(r, 24, 8) | _SHIFTL(g, 16, 8) | _SHIFTL(b, 8, 8) | _SHIFTL(a, 0, 8)); \
} while(0)

#define gDPSetPrimColor(pkt, m, l, r, g, b, a) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_SETPRIMCOLOR, 24, 8) | _SHIFTL(m, 8, 8) | _SHIFTL(l, 0, 8)); \
    _g->words.w1 = (_SHIFTL(r, 24, 8) | _SHIFTL(g, 16, 8) | _SHIFTL(b, 8, 8) | _SHIFTL(a, 0, 8)); \
} while(0)

#define gDPSetBlendColor(pkt, r, g, b, a) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = _SHIFTL(G_SETBLENDCOLOR, 24, 8); \
    _g->words.w1 = (_SHIFTL(r, 24, 8) | _SHIFTL(g, 16, 8) | _SHIFTL(b, 8, 8) | _SHIFTL(a, 0, 8)); \
} while(0)

#define gDPSetFogColor(pkt, r, g, b, a) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = _SHIFTL(G_SETFOGCOLOR, 24, 8); \
    _g->words.w1 = (_SHIFTL(r, 24, 8) | _SHIFTL(g, 16, 8) | _SHIFTL(b, 8, 8) | _SHIFTL(a, 0, 8)); \
} while(0)

#define gDPSetFillColor(pkt, color) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = _SHIFTL(G_SETFILLCOLOR, 24, 8); \
    _g->words.w1 = (uint32_t)(color); } while(0)

#define gDPSetColor(pkt, cmd, color) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = _SHIFTL(cmd, 24, 8); \
    _g->words.w1 = (uint32_t)(color); } while(0)

#define gDPSetPrimDepth(pkt, z, dz) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = _SHIFTL(G_SETPRIMDEPTH, 24, 8); \
    _g->words.w1 = (_SHIFTL(z, 16, 16) | _SHIFTL(dz, 0, 16)); } while(0)

#define gDPSetOtherMode(pkt, mode0, mode1) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_RDPSETOTHERMODE, 24, 8) | (uint32_t)((mode0) & 0x00FFFFFF)); \
    _g->words.w1 = (uint32_t)(mode1); } while(0)

#define gDPSetCycleType(pkt, type) \
    gSPSetOtherMode_H(pkt, G_MDSFT_CYCLETYPE, 2, type)
#define gDPSetTexturePersp(pkt, type) \
    gSPSetOtherMode_H(pkt, G_MDSFT_TEXTPERSP, 1, type)
#define gDPSetTextureFilter(pkt, type) \
    gSPSetOtherMode_H(pkt, G_MDSFT_TEXTFILT, 2, type)
#define gDPSetTextureLUT(pkt, type) \
    gSPSetOtherMode_H(pkt, G_MDSFT_TEXTLUT, 2, type)
#define gDPSetTextureLOD(pkt, type) \
    gSPSetOtherMode_H(pkt, G_MDSFT_TEXTLOD, 1, type)
#define gDPSetTextureConvert(pkt, type) \
    gSPSetOtherMode_H(pkt, G_MDSFT_TEXTCONV, 3, type)
#define gDPSetCombineKey(pkt, type) \
    gSPSetOtherMode_H(pkt, G_MDSFT_COMBKEY, 1, type)
#define gDPSetAlphaCompare(pkt, type) \
    gSPSetOtherMode_L(pkt, G_MDSFT_ALPHACOMPARE, 2, type)
#define gDPSetAlphaDither(pkt, type) \
    gSPSetOtherMode_H(pkt, G_MDSFT_ALPHADITHER, 2, type)
#define gDPSetColorDither(pkt, type) \
    gSPSetOtherMode_H(pkt, G_MDSFT_RGBDITHER, 2, type)
#define gDPSetRenderMode(pkt, c1, c2) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_SETOTHERMODE_L, 24, 8) | _SHIFTL(G_MDSFT_RENDERMODE, 8, 8) | _SHIFTL(29, 0, 8)); \
    _g->words.w1 = ((c1) | (c2)); } while(0)
#define gDPSetTextureAdjustMode(pkt, type) do { (void)(pkt); (void)(type); } while(0)

#define gSPSetOtherMode_H(pkt, sft, len, val) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_SETOTHERMODE_H, 24, 8) | _SHIFTL(32-(sft)-(len), 8, 8) | _SHIFTL((len)-1, 0, 8)); \
    _g->words.w1 = (uint32_t)(val); } while(0)

#define gSPSetOtherMode_L(pkt, sft, len, val) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_SETOTHERMODE_L, 24, 8) | _SHIFTL(32-(sft)-(len), 8, 8) | _SHIFTL((len)-1, 0, 8)); \
    _g->words.w1 = (uint32_t)(val); } while(0)

#define gDPSetScissor(pkt, mode, xl, yl, xh, yh) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_SETSCISSOR, 24, 8) | _SHIFTL((xl)*4, 12, 12) | _SHIFTL((yl)*4, 0, 12)); \
    _g->words.w1 = (_SHIFTL(mode, 24, 2) | _SHIFTL((xh)*4, 12, 12) | _SHIFTL((yh)*4, 0, 12)); } while(0)

#define gDPSetTile(pkt, fmt, siz, line, tmem, tile, palette, cmt, maskt, shiftt, cms, masks, shifts) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_SETTILE, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | \
                    _SHIFTL(line, 9, 9) | _SHIFTL(tmem, 0, 9)); \
    _g->words.w1 = (_SHIFTL(tile, 24, 3) | _SHIFTL(palette, 20, 4) | _SHIFTL(cmt, 18, 2) | \
                    _SHIFTL(maskt, 14, 4) | _SHIFTL(shiftt, 10, 4) | _SHIFTL(cms, 8, 2) | \
                    _SHIFTL(masks, 4, 4) | _SHIFTL(shifts, 0, 4)); } while(0)

#define gDPSetTileSize(pkt, tile, uls, ult, lrs, lrt) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_SETTILESIZE, 24, 8) | _SHIFTL(uls, 12, 12) | _SHIFTL(ult, 0, 12)); \
    _g->words.w1 = (_SHIFTL(tile, 24, 3) | _SHIFTL(lrs, 12, 12) | _SHIFTL(lrt, 0, 12)); } while(0)

#define gDPLoadBlock(pkt, tile, uls, ult, lrs, dxt) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_LOADBLOCK, 24, 8) | _SHIFTL(uls, 12, 12) | _SHIFTL(ult, 0, 12)); \
    _g->words.w1 = (_SHIFTL(tile, 24, 3) | _SHIFTL(lrs, 12, 12) | _SHIFTL(dxt, 0, 12)); } while(0)

#define gDPLoadTile(pkt, tile, uls, ult, lrs, lrt) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_LOADTILE, 24, 8) | _SHIFTL(uls, 12, 12) | _SHIFTL(ult, 0, 12)); \
    _g->words.w1 = (_SHIFTL(tile, 24, 3) | _SHIFTL(lrs, 12, 12) | _SHIFTL(lrt, 0, 12)); } while(0)

/* Dynamic TLUT palette load: loads 16-color (pal16) or 256-color (pal256) palette */
#define gDPLoadTLUTCmd(pkt, tile, count) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_LOADTLUT, 24, 8) | _SHIFTL((tile), 24, 3) | _SHIFTL((count), 14, 10)); \
    _g->words.w1 = 0; } while(0)
#define gDPLoadTLUT_pal16(pkt, pal, dram) do { \
    gDPSetTextureImage((pkt), G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dram); \
    gDPTileSync((pkt)+1); \
    gDPSetTile((pkt)+2, 0, 0, 0, (256+(((pal)&0xF)*16)), G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0); \
    gDPLoadSync((pkt)+3); \
    gDPLoadTLUTCmd((pkt)+4, G_TX_LOADTILE, 15); \
    gDPPipeSync((pkt)+5); } while(0)
#define gDPLoadTLUT_pal256(pkt, dram) do { \
    gDPSetTextureImage((pkt), G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dram); \
    gDPTileSync((pkt)+1); \
    gDPSetTile((pkt)+2, 0, 0, 0, 256, G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0); \
    gDPLoadSync((pkt)+3); \
    gDPLoadTLUTCmd((pkt)+4, G_TX_LOADTILE, 255); \
    gDPPipeSync((pkt)+5); } while(0)

/* Game uses gDPLoadTLUT(pkt, count, palette_count, imgaddr) — 4-arg form */
#define gDPLoadTLUT(pkt, count, pal_size, imgaddr) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_LOADTLUT, 24, 8) | _SHIFTL(0, 12, 12) | _SHIFTL(0, 0, 12)); \
    _g->words.w1 = (_SHIFTL(G_TX_LOADTILE, 24, 3) | _SHIFTL((count)-1, 14, 10)); \
    (void)(pal_size); (void)(imgaddr); } while(0)

/* Texture loading helpers.
 * _gDPLoadTextureBlock_impl takes pre-computed siz_lb (LOAD_BLOCK value) and
 * siz_line (LINE_BYTES value) to avoid double-expansion of the siz token
 * (passing siz through an intermediate macro would expand G_IM_SIZ_8b to 1
 * before ## concatenation, producing 1_LOAD_BLOCK which is invalid). */
#define _gDPLoadTextureBlock_impl(pkt, timg, fmt, siz, siz_lb, siz_line, width, height, pal, \
                                   cms, cmt, masks, maskt, shifts, shiftt)                    \
    gDPPipeSync(pkt);                                                                         \
    gDPSetTextureImage((pkt)+1, fmt, siz_lb, 1, timg);                                       \
    gDPSetTile((pkt)+2, fmt, siz_lb, 0, 0, G_TX_LOADTILE, 0,                                \
               cmt, maskt, shiftt, cms, masks, shifts);                                       \
    gDPLoadBlock((pkt)+3, G_TX_LOADTILE, 0, 0,                                               \
                 (((width)*(height) + siz_lb - 1) >> siz_lb),                                \
                 ((1 << 11) + (siz_line*(width) - 1)) / (siz_line*(width)));                 \
    gDPPipeSync((pkt)+4);                                                                     \
    gDPSetTile((pkt)+5, fmt, siz, (((width)*siz_line+7)>>3), 0,                              \
               G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts);                \
    gDPSetTileSize((pkt)+6, G_TX_RENDERTILE, 0, 0,                                           \
                   ((width)-1) << 2, ((height)-1) << 2)

/* Outer wrappers: ## happens here, in the same macro that receives siz as a
 * token — no intermediate expansion occurs. */
#define gDPLoadTextureBlock(pkt, timg, fmt, siz, width, height, pal,  \
                             cms, cmt, masks, maskt, shifts, shiftt)   \
    _gDPLoadTextureBlock_impl(pkt, timg, fmt, siz,                     \
        siz##_LOAD_BLOCK, siz##_LINE_BYTES,                            \
        width, height, pal, cms, cmt, masks, maskt, shifts, shiftt)

#define gDPLoadTextureBlockS(pkt, timg, fmt, siz, width, height, pal,  \
                              cms, cmt, masks, maskt, shifts, shiftt)   \
    _gDPLoadTextureBlock_impl(pkt, timg, fmt, siz,                      \
        siz##_LOAD_BLOCK, siz##_LINE_BYTES,                             \
        width, height, pal, cms, cmt, masks, maskt, shifts, shiftt)

#define gDPLoadTextureTile(pkt, timg, fmt, siz, width, height,         \
                            uls, ult, lrs, lrt, pal,                    \
                            cms, cmt, masks, maskt, shifts, shiftt) do {\
    gDPPipeSync(pkt);                                                    \
    gDPSetTextureImage((pkt)+1, fmt, siz, width, timg);                 \
    gDPSetTile((pkt)+2, fmt, siz, (((lrs-uls+1)*siz##_LINE_BYTES+7)>>3), 0, \
               G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, masks, shifts); \
    gDPLoadTile((pkt)+3, G_TX_LOADTILE, uls<<2, ult<<2, lrs<<2, lrt<<2); \
    gDPPipeSync((pkt)+4);                                                \
    gDPSetTile((pkt)+5, fmt, siz, (((lrs-uls+1)*siz##_LINE_BYTES+7)>>3), 0, \
               G_TX_RENDERTILE, pal, cmt, maskt, shiftt, cms, masks, shifts); \
    gDPSetTileSize((pkt)+6, G_TX_RENDERTILE, uls<<2, ult<<2, lrs<<2, lrt<<2); \
} while(0)

#define gDPFillRectangle(pkt, xl, yl, xh, yh) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = (_SHIFTL(G_FILLRECT, 24, 8) | _SHIFTL((xh)*4+3, 12, 12) | _SHIFTL((yh)*4+3, 0, 12)); \
    _g->words.w1 = (_SHIFTL((xl)*4, 12, 12) | _SHIFTL((yl)*4, 0, 12)); } while(0)

#define gDPFillRectangleF(pkt, xl, yl, xh, yh) gDPFillRectangle(pkt, (int)(xl), (int)(yl), (int)(xh), (int)(yh))

/* TEV extension macros (F3DZEX2 custom) */
#define gDPSetTexEdgeAlpha(pkt, alpha) do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = _SHIFTL(G_SETTEXEDGEALPHA, 24, 8); \
    _g->words.w1 = (uint32_t)(alpha); } while(0)

/* ---- Static (gs*) initializer versions ---- */
#define gsSPNoOp()         {{ _SHIFTL(G_SPNOOP, 24, 8), 0 }}
#define gsSPEndDisplayList() {{ _SHIFTL(G_ENDDL, 24, 8), 0 }}
#define gsDPNoOp()         {{ _SHIFTL(G_NOOP, 24, 8), 0 }}
#define gsDPPipeSync()     {{ _SHIFTL(G_RDPPIPESYNC, 24, 8), 0 }}
#define gsDPFullSync()     {{ _SHIFTL(G_RDPFULLSYNC, 24, 8), 0 }}
#define gsDPTileSync()     {{ _SHIFTL(G_RDPTILESYNC, 24, 8), 0 }}

#define gsDPSetCombineMode(a, b) \
    {{ _SHIFTL(G_SETCOMBINE, 24, 8), 0 }}

#define gsDPSetCombineLERP(a0,b0,c0,d0,aa0,ab0,ac0,ad0,a1,b1,c1,d1,aa1,ab1,ac1,ad1) \
    {{ (_SHIFTL(G_SETCOMBINE, 24, 8) | _SHIFTL(a0, 20, 4) | _SHIFTL(c0, 15, 5) | \
        _SHIFTL(aa0, 12, 3) | _SHIFTL(ac0, 9, 3) | _SHIFTL(a1, 5, 4) | _SHIFTL(c1, 0, 5)), \
       (_SHIFTL(b0, 28, 4) | _SHIFTL(b1, 24, 4) | _SHIFTL(aa1, 21, 3) | \
        _SHIFTL(ac1, 18, 3) | _SHIFTL(d0, 15, 3) | _SHIFTL(ab0, 12, 3) | \
        _SHIFTL(ad0, 9, 3)  | _SHIFTL(d1, 6, 3)  | _SHIFTL(ab1, 3, 3) | _SHIFTL(ad1, 0, 3)) }}

#define gsDPSetEnvColor(r, g, b, a) \
    {{ _SHIFTL(G_SETENVCOLOR, 24, 8), \
       (_SHIFTL(r, 24, 8) | _SHIFTL(g, 16, 8) | _SHIFTL(b, 8, 8) | _SHIFTL(a, 0, 8)) }}

#define gsDPSetPrimColor(m, l, r, g, b, a) \
    {{ (_SHIFTL(G_SETPRIMCOLOR, 24, 8) | _SHIFTL(m, 8, 8) | _SHIFTL(l, 0, 8)), \
       (_SHIFTL(r, 24, 8) | _SHIFTL(g, 16, 8) | _SHIFTL(b, 8, 8) | _SHIFTL(a, 0, 8)) }}

#define gsDPSetFogColor(r, g, b, a) \
    {{ _SHIFTL(G_SETFOGCOLOR, 24, 8), \
       (_SHIFTL(r, 24, 8) | _SHIFTL(g, 16, 8) | _SHIFTL(b, 8, 8) | _SHIFTL(a, 0, 8)) }}

#define gsDPSetBlendColor(r, g, b, a) \
    {{ _SHIFTL(G_SETBLENDCOLOR, 24, 8), \
       (_SHIFTL(r, 24, 8) | _SHIFTL(g, 16, 8) | _SHIFTL(b, 8, 8) | _SHIFTL(a, 0, 8)) }}

#define gsDPSetFillColor(color) \
    {{ _SHIFTL(G_SETFILLCOLOR, 24, 8), (uint32_t)(color) }}

#define gsDPSetColor(cmd, color) \
    {{ _SHIFTL(cmd, 24, 8), (uint32_t)(color) }}

#define gsDPSetRenderMode(c1, c2) \
    {{ (_SHIFTL(G_SETOTHERMODE_L, 24, 8) | _SHIFTL(G_MDSFT_RENDERMODE, 8, 8) | _SHIFTL(29, 0, 8)), \
       ((c1) | (c2)) }}

#define gsDPSetOtherMode(mode0, mode1) \
    {{ (_SHIFTL(G_RDPSETOTHERMODE, 24, 8) | (uint32_t)((mode0) & 0x00FFFFFF)), (uint32_t)(mode1) }}

#define gsSPSetOtherMode_H(sft, len, val) \
    {{ (_SHIFTL(G_SETOTHERMODE_H, 24, 8) | _SHIFTL(32-(sft)-(len), 8, 8) | _SHIFTL((len)-1, 0, 8)), (uint32_t)(val) }}

#define gsSPSetOtherMode_L(sft, len, val) \
    {{ (_SHIFTL(G_SETOTHERMODE_L, 24, 8) | _SHIFTL(32-(sft)-(len), 8, 8) | _SHIFTL((len)-1, 0, 8)), (uint32_t)(val) }}

#define gsDPSetCycleType(type)     gsSPSetOtherMode_H(G_MDSFT_CYCLETYPE, 2, type)
#define gsDPSetTexturePersp(type)  gsSPSetOtherMode_H(G_MDSFT_TEXTPERSP, 1, type)
#define gsDPSetTextureFilter(type) gsSPSetOtherMode_H(G_MDSFT_TEXTFILT, 2, type)
#define gsDPSetTextureLUT(type)     gsSPSetOtherMode_H(G_MDSFT_TEXTLUT, 2, type)
#define gsDPSetTextureLOD(type)     gsSPSetOtherMode_H(G_MDSFT_TEXTLOD, 1, type)
#define gsDPSetTextureConvert(type) gsSPSetOtherMode_H(G_MDSFT_TEXTCONV, 3, type)
#define gsDPSetCombineKey(type)     gsSPSetOtherMode_H(G_MDSFT_COMBKEY, 1, type)
#define gsDPSetAlphaCompare(type)   gsSPSetOtherMode_L(G_MDSFT_ALPHACOMPARE, 2, type)
#define gsDPSetAlphaDither(type)    gsSPSetOtherMode_H(G_MDSFT_ALPHADITHER, 2, type)
#define gsDPSetColorDither(type)    gsSPSetOtherMode_H(G_MDSFT_RGBDITHER, 2, type)

#define gsDPSetScissor(mode, xl, yl, xh, yh) \
    {{ (_SHIFTL(G_SETSCISSOR, 24, 8) | _SHIFTL((xl)*4, 12, 12) | _SHIFTL((yl)*4, 0, 12)), \
       (_SHIFTL(mode, 24, 2) | _SHIFTL((xh)*4, 12, 12) | _SHIFTL((yh)*4, 0, 12)) }}

#define gsDPSetTile(fmt, siz, line, tmem, tile, pal, cmt, maskt, shiftt, cms, masks, shifts) \
    {{ (_SHIFTL(G_SETTILE, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | \
        _SHIFTL(line, 9, 9) | _SHIFTL(tmem, 0, 9)), \
       (_SHIFTL(tile, 24, 3) | _SHIFTL(pal, 20, 4) | _SHIFTL(cmt, 18, 2) | \
        _SHIFTL(maskt, 14, 4) | _SHIFTL(shiftt, 10, 4) | _SHIFTL(cms, 8, 2) | \
        _SHIFTL(masks, 4, 4) | _SHIFTL(shifts, 0, 4)) }}

#define gsDPSetTileSize(tile, uls, ult, lrs, lrt) \
    {{ (_SHIFTL(G_SETTILESIZE, 24, 8) | _SHIFTL(uls, 12, 12) | _SHIFTL(ult, 0, 12)), \
       (_SHIFTL(tile, 24, 3) | _SHIFTL(lrs, 12, 12) | _SHIFTL(lrt, 0, 12)) }}

/* Use .pwords for pointer-bearing static initializers — Clang forbids
 * (uint32_t)ptr casts in constant expressions, but (void*)ptr is fine. */
#define gsDisplayList(dl)   { .pwords = { (_SHIFTL(G_DL, 24, 8) | 0), (void*)(dl) } }
#define gsSPDisplayList(dl) { .pwords = { (_SHIFTL(G_DL, 24, 8) | 0), (void*)(dl) } }
#define gsSPBranchList(dl)  { .pwords = { (_SHIFTL(G_DL, 24, 8) | 1), (void*)(dl) } }

#define gsSPSegment(seg, base) \
    { .pwords = { (_SHIFTL(G_MOVEWORD, 24, 8) | _SHIFTL(G_MW_SEGMENT, 16, 8) | (uint32_t)((seg)*4)), \
                  (void*)(uintptr_t)(base) } }

#define gsSPMatrix(m, p) \
    { .pwords = { (_SHIFTL(G_MTX, 24, 8) | _SHIFTL((uint32_t)sizeof(int[4][4]), 0, 16) | ((p)&1)), \
                  (void*)(m) } }

#define gsSPNumLights(n) \
    {{ (_SHIFTL(G_MOVEWORD, 24, 8) | _SHIFTL(G_MW_NUMLIGHT, 16, 8)), \
       (uint32_t)(n) * 24 }}

#define gsSPTexture(sc, tc, level, tile, on) \
    {{ (_SHIFTL(G_TEXTURE, 24, 8) | _SHIFTL(level, 11, 3) | _SHIFTL(tile, 8, 3) | _SHIFTL(on, 0, 8)), \
       (_SHIFTL(sc, 16, 16) | _SHIFTL(tc, 0, 16)) }}

/* F3DZEX2 geometry mode: w0[23:0]=clear_mask, w1[23:0]=set_mask */
#define gsSPSetGeometryMode(m) \
    {{ (_SHIFTL(G_GEOMETRYMODE, 24, 8) | 0x00FFFFFF), (uint32_t)(m) }}
#define gsSPClearGeometryMode(m) \
    {{ (_SHIFTL(G_GEOMETRYMODE, 24, 8) | (~(uint32_t)(m) & 0x00FFFFFF)), 0 }}

#define gsSPFogPosition(min, max) \
    {{ (_SHIFTL(G_MOVEWORD, 24, 8) | _SHIFTL(G_MW_FOG, 16, 8) | 4), \
       (_SHIFTL(max, 16, 16) | _SHIFTL(min, 0, 16)) }}

/* Texture enable constants */
#define G_ON   1
#define G_OFF  0

/* gsSPLoadGeometryMode: in a static initializer context, treat as single
 * set-geometry-mode command (the clear is a no-op for our purposes) */
/* F3DZEX2 geometry mode static macros */
#define gsSPSetGeometryMode(m) \
    {{ (_SHIFTL(G_GEOMETRYMODE, 24, 8) | 0x00FFFFFF), (uint32_t)(m) }}
#define gsSPClearGeometryMode(m) \
    {{ (_SHIFTL(G_GEOMETRYMODE, 24, 8) | (~(uint32_t)(m) & 0x00FFFFFF)), 0 }}
#define gsSPLoadGeometryMode(m) \
    {{ _SHIFTL(G_GEOMETRYMODE, 24, 8), (uint32_t)(m) }}
#define gsSPGeometryMode(c, s) \
    {{ (_SHIFTL(G_GEOMETRYMODE, 24, 8) | (~(uint32_t)(c) & 0x00FFFFFF)), (uint32_t)(s) }}
#define gsSPPopMatrix(n) {{ _SHIFTL(G_POPMTX, 24, 8), (uint32_t)(n) * 64 }}

/* Vertex / triangle static macros (F3DZEX2 encoding) */
#define gsSPVertex(v, n, v0) \
    { .pwords = { (_SHIFTL(G_VTX, 24, 8) | _SHIFTL((n), 12, 8) | _SHIFTL((n)+(v0), 1, 7)), (void*)(v) } }
#define gsSP1Triangle(v0, v1, v2, flag) \
    {{ _SHIFTL(G_TRI1, 24, 8), \
       (_SHIFTL((v0)*2, 16, 8) | _SHIFTL((v1)*2, 8, 8) | _SHIFTL((v2)*2, 0, 8) | (flag)) }}
#define gsSP2Triangles(v00,v01,v02,f0, v10,v11,v12,f1) \
    {{ (_SHIFTL(G_TRI2, 24, 8) | _SHIFTL((v10)*2, 16, 8) | _SHIFTL((v11)*2, 8, 8) | _SHIFTL((v12)*2, 0, 8) | (f1)), \
       (_SHIFTL((v00)*2, 16, 8) | _SHIFTL((v01)*2, 8, 8) | _SHIFTL((v02)*2, 0, 8) | (f0)) }}
#define gsSP1Quadrangle(v0,v1,v2,v3,flag) \
    {{ (_SHIFTL(G_QUAD, 24, 8) | _SHIFTL((v0)*2, 16, 8) | _SHIFTL((v1)*2, 8, 8) | _SHIFTL((v2)*2, 0, 8) | (flag)), \
       (_SHIFTL((v3)*2, 0, 8)) }}
#define gsSPCullDisplayList(vstart, vend) \
    {{ (_SHIFTL(G_CULLDL, 24, 8) | ((vstart)*2)), ((vend)*2) }}
#define gsSPLine3D(v0, v1, flag) \
    {{ _SHIFTL(G_LINE3D, 24, 8), \
       (_SHIFTL((v0)*2, 16, 8) | _SHIFTL((v1)*2, 8, 8) | (flag)) }}
#define gsSPLineW3D(v0, v1, wd, flag) \
    {{ _SHIFTL(G_LINE3D, 24, 8), \
       (_SHIFTL((v0)*2, 16, 8) | _SHIFTL((v1)*2, 8, 8) | _SHIFTL((wd), 0, 8) | (flag)) }}
#define gsSPModifyVertex(vtx, where, val) \
    {{ (_SHIFTL(G_MODIFYVTX, 24, 8) | _SHIFTL((where), 16, 8) | ((vtx)*2)), (uint32_t)(val) }}
#define gsSPBranchLessZraw(branchdl, vtx, zval) \
    { .pwords = { (_SHIFTL(G_BRANCH_Z, 24, 8) | ((vtx)*2)), (void*)(branchdl) } }

/* MOVEMEM-based static macros */
#define gsSPViewport(v) \
    { .pwords = { (_SHIFTL(G_MOVEMEM, 24, 8) | _SHIFTL((sizeof(Vp_t)-1), 16, 8) | _SHIFTL(G_MV_VIEWPORT, 8, 8)), (void*)(v) } }
#define gsSPLight(lp, n) \
    { .pwords = { (_SHIFTL(G_MOVEMEM, 24, 8) | _SHIFTL((8*4-1), 16, 8) | _SHIFTL(G_MV_LIGHT, 8, 8) | _SHIFTL((n)-1, 0, 8)), (void*)(lp) } }
#define gsSPLookAtX(la) \
    { .pwords = { (_SHIFTL(G_MOVEMEM, 24, 8) | _SHIFTL((8*4-1), 16, 8) | _SHIFTL(G_MV_LIGHT, 8, 8) | (G_MVO_LOOKATX/8)), (void*)(la) } }
#define gsSPLookAtY(la) \
    { .pwords = { (_SHIFTL(G_MOVEMEM, 24, 8) | _SHIFTL((8*4-1), 16, 8) | _SHIFTL(G_MV_LIGHT, 8, 8) | (G_MVO_LOOKATY/8)), (void*)(la) } }
#define gsSPForceMatrix(mptr) \
    { .pwords = { (_SHIFTL(G_MOVEMEM, 24, 8) | _SHIFTL(32*4-1, 16, 8) | _SHIFTL(G_MV_MATRIX, 8, 8)), (void*)(mptr) } }

/* MOVEWORD-based static macros */
#define gsSPLightColor(n, col) \
    {{ (_SHIFTL(G_MOVEWORD, 24, 8) | _SHIFTL(G_MW_LIGHTCOL, 16, 8) | _SHIFTL(((n)-1)*4, 0, 16)), (uint32_t)(col) }}
#define gsSPPerspNormalize(s) \
    {{ (_SHIFTL(G_MOVEWORD, 24, 8) | _SHIFTL(G_MW_PERSPNORM, 16, 8)), (uint32_t)(s) }}
#define gsSPFogFactor(fm, fb) \
    {{ (_SHIFTL(G_MOVEWORD, 24, 8) | _SHIFTL(G_MW_FOG, 16, 8) | 0), \
       (_SHIFTL((fm), 16, 16) | _SHIFTL((fb), 0, 16)) }}
#define gsSPClipRatio(r) \
    {{ (_SHIFTL(G_MOVEWORD, 24, 8) | _SHIFTL(G_MW_CLIP, 16, 8)), (uint32_t)(r) }}
#define gsSPSegmentA(seg, base) \
    {{ (_SHIFTL(G_MOVEWORD, 24, 8) | _SHIFTL(G_MW_SEGMENT, 16, 8) | (uint32_t)((seg)*4)), \
       (uint32_t)(base) }}
#define gsSPSetOtherModeH(sft, len, val) \
    {{ (_SHIFTL(G_SETOTHERMODE_H, 24, 8) | _SHIFTL(32-(sft)-(len), 8, 8) | _SHIFTL((len)-1, 0, 8)), (uint32_t)(val) }}
#define gsSPSetOtherModeL(sft, len, val) \
    {{ (_SHIFTL(G_SETOTHERMODE_L, 24, 8) | _SHIFTL(32-(sft)-(len), 8, 8) | _SHIFTL((len)-1, 0, 8)), (uint32_t)(val) }}

/* Load microcode */
#define gsSPLoadUcode(uc_start, uc_dstart) \
    {{ (_SHIFTL(G_LOAD_UCODE, 24, 8)), (uint32_t)(uc_start) }}
#define gsSPLoadUcodeEx(uc_start, uc_dstart, uc_dsize) \
    {{ (_SHIFTL(G_LOAD_UCODE, 24, 8)), (uint32_t)(uc_start) }}

/* Texture rectangle */
#define gsSPTextureRectangle(xl, yl, xh, yh, tile, s, t, dsdx, dtdy) \
    {{ (_SHIFTL(G_TEXRECT, 24, 8) | _SHIFTL((xh), 12, 12) | _SHIFTL((yh), 0, 12)), \
       (_SHIFTL((xl), 12, 12) | _SHIFTL((yl), 0, 12)) }}, \
    {{ (_SHIFTL(G_RDPHALF_1, 24, 8) | _SHIFTL((tile), 24, 3)), 0 }}, \
    {{ (_SHIFTL(G_RDPHALF_2, 24, 8) | _SHIFTL((s), 16, 16) | _SHIFTL((t), 0, 16)), \
       (_SHIFTL((dsdx), 16, 16) | _SHIFTL((dtdy), 0, 16)) }}
#define gsSPTextureL(sc, tc, level, tile, on) \
    {{ (_SHIFTL(G_TEXTURE, 24, 8) | _SHIFTL((level), 11, 3) | _SHIFTL((tile), 8, 3) | _SHIFTL((on), 0, 8)), \
       (_SHIFTL((sc), 16, 16) | _SHIFTL((tc), 0, 16)) }}

/* N-quadrangle data helpers */
#define gsSPNQuadrangleData1(v0,v1,v2,v3) \
    (_SHIFTL((v0)*2, 24, 8) | _SHIFTL((v1)*2, 16, 8) | _SHIFTL((v2)*2, 8, 8) | _SHIFTL((v3)*2, 0, 8))
#define gsSPNQuadrangles(n, v0,v1,v2,v3) \
    {{ (_SHIFTL(G_QUAD, 24, 8) | _SHIFTL((n)-1, 17, 7)), gsSPNQuadrangleData1(v0,v1,v2,v3) }}

/* RDP static macros */
#define gsDPSetColorImage(fmt, siz, width, img) \
    { .pwords = { (_SHIFTL(G_SETCIMG, 24, 8) | _SHIFTL((fmt), 21, 3) | _SHIFTL((siz), 19, 2) | _SHIFTL((width)-1, 0, 12)), \
                  (void*)(img) } }
#define gsDPSetDepthImage(img) \
    { .pwords = { (_SHIFTL(G_SETZIMG, 24, 8)), (void*)(img) } }
#define gsDPSetTextureImage(fmt, siz, width, img) \
    { .pwords = { (_SHIFTL(G_SETTIMG, 24, 8) | _SHIFTL((fmt), 21, 3) | _SHIFTL((siz), 19, 2) | _SHIFTL((width)-1, 0, 12)), \
                  (void*)(img) } }
#define gsDPFillRectangle(xl, yl, xh, yh) \
    {{ (_SHIFTL(G_FILLRECT, 24, 8) | _SHIFTL((xh), 14, 10) | _SHIFTL((yh), 2, 10)), \
       (_SHIFTL((xl), 14, 10) | _SHIFTL((yl), 2, 10)) }}
#define gsDPSetPrimDepth(z, dz) \
    {{ _SHIFTL(G_SETPRIMDEPTH, 24, 8), (_SHIFTL((z), 16, 16) | _SHIFTL((dz), 0, 16)) }}
#define gsDPSetScissorFrac(mode, xl, yl, xh, yh) \
    {{ (_SHIFTL(G_SETSCISSOR, 24, 8) | _SHIFTL((xl)<<2, 12, 12) | _SHIFTL((yl)<<2, 0, 12)), \
       (_SHIFTL((mode), 24, 2) | _SHIFTL((xh)<<2, 12, 12) | _SHIFTL((yh)<<2, 0, 12)) }}
#define gsDPSpecial_1(mode) \
    {{ (_SHIFTL(G_SPECIAL_1, 24, 8) | _SHIFTL(G_SPECIAL_TA_MODE, 16, 8) | _SHIFTL((mode), 0, 16)), 0 }}
#define gsDPSetCombineLERPInline(a0,b0,c0,d0,aa0,ab0,ac0,ad0, a1,b1,c1,d1,aa1,ab1,ac1,ad1) \
    gsDPSetCombineLERP(a0,b0,c0,d0,aa0,ab0,ac0,ad0, a1,b1,c1,d1,aa1,ab1,ac1,ad1)

/* Texture block load static macros */
#define gsDPLoadBlock(tile, uls, ult, lrs, dxt) \
    {{ (_SHIFTL(G_LOADBLOCK, 24, 8) | _SHIFTL((uls), 12, 12) | _SHIFTL((ult), 0, 12)), \
       (_SHIFTL((lrs), 12, 12) | _SHIFTL((tile), 24, 3) | _SHIFTL((dxt), 0, 12)) }}
#define gsDPLoadTile(tile, uls, ult, lrs, lrt) \
    {{ (_SHIFTL(G_LOADTILE, 24, 8) | _SHIFTL((uls), 12, 12) | _SHIFTL((ult), 0, 12)), \
       (_SHIFTL((tile), 24, 3) | _SHIFTL((lrs), 12, 12) | _SHIFTL((lrt), 0, 12)) }}
#define gsDPLoadTLUTCmd(tile, count) \
    {{ (_SHIFTL(G_LOADTLUT, 24, 8) | _SHIFTL((tile), 24, 3) | _SHIFTL((count), 14, 10)), 0 }}
#define gsDPLoadTLUT_pal16(pal, dram) \
    gsDPSetTextureImage(G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, dram), \
    gsDPTileSync(), \
    gsDPSetTile(0, 0, 0, (256+(((pal)&0xF)*16)), G_TX_LOADTILE, 0, 0, 0, 0, 0, 0, 0), \
    gsDPLoadSync(), \
    gsDPLoadTLUTCmd(G_TX_LOADTILE, 15), \
    gsDPPipeSync()
#define gsDPLoadSync() {{ _SHIFTL(G_RDPLOADSYNC, 24, 8), 0 }}
#define gsDPNoOpTag(tag, value) {{ _SHIFTL(G_NOOP, 24, 8), (uint32_t)(value) }}

/* Multi-block texture load (standard N64-style, 4-arg version).
 * _impl takes pre-computed size variants to prevent double-expansion. */
#define _gsDPLoadTextureBlock_impl(timg, fmt, siz, siz_lb, siz_line, siz_bytes, \
                                    siz_incr, siz_shift,                         \
                                    width, height, pal,                           \
                                    cms, cmt, masks, maskt, shifts, shiftt)       \
    gsDPSetTextureImage(fmt, siz_lb, 1, timg),                                   \
    gsDPTileSync(),                                                               \
    gsDPSetTile(fmt, siz_lb, 0, 0, G_TX_LOADTILE, 0,                            \
                cmt, maskt, shiftt, cms, masks, shifts),                          \
    gsDPLoadSync(),                                                               \
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0,                                           \
        ((width)*(height) + siz_incr) >> siz_shift,                              \
        CALC_DXT(width, siz_bytes)),                                              \
    gsDPPipeSync(),                                                               \
    gsDPSetTile(fmt, siz, (((width)*siz_line)+7)>>3, 0,                          \
                G_TX_RENDERTILE, pal,                                             \
                cmt, maskt, shiftt, cms, masks, shifts),                          \
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0,                                       \
        (((width)-1) << G_TEXTURE_IMAGE_FRAC),                                   \
        (((height)-1) << G_TEXTURE_IMAGE_FRAC))

#define gsDPLoadTextureBlock(timg, fmt, siz, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt) \
    _gsDPLoadTextureBlock_impl(timg, fmt, siz,                                   \
        siz##_LOAD_BLOCK, siz##_LINE_BYTES, siz##_BYTES,                         \
        siz##_INCR, siz##_SHIFT,                                                 \
        width, height, pal, cms, cmt, masks, maskt, shifts, shiftt)
#define gsDPLoadTextureBlock_4b(timg, fmt, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt) \
    _gsDPLoadTextureBlock_impl(timg, fmt, G_IM_SIZ_4b,                           \
        G_IM_SIZ_4b_LOAD_BLOCK, G_IM_SIZ_4b_LINE_BYTES, G_IM_SIZ_4b_BYTES,     \
        G_IM_SIZ_4b_INCR, G_IM_SIZ_4b_SHIFT,                                    \
        width, height, pal, cms, cmt, masks, maskt, shifts, shiftt)
#define gsDPLoadMultiBlock(timg, tmem, rtile, fmt, siz, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt) \
    gsDPSetTextureImage(fmt, siz##_LOAD_BLOCK, 1, timg),                       \
    gsDPTileSync(),                                                             \
    gsDPSetTile(fmt, siz##_LOAD_BLOCK, 0, (tmem), G_TX_LOADTILE, 0,           \
                cmt, maskt, shiftt, cms, masks, shifts),                       \
    gsDPLoadSync(),                                                             \
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0,                                         \
        ((width)*(height) + siz##_INCR) >> siz##_SHIFT,                       \
        CALC_DXT(width, siz##_BYTES)),                                         \
    gsDPPipeSync(),                                                             \
    gsDPSetTile(fmt, siz, (((width)*siz##_LINE_BYTES)+7)>>3, (tmem),          \
                rtile, pal,                                                    \
                cmt, maskt, shiftt, cms, masks, shifts),                       \
    gsDPSetTileSize(rtile, 0, 0,                                               \
        (((width)-1) << G_TEXTURE_IMAGE_FRAC),                                 \
        (((height)-1) << G_TEXTURE_IMAGE_FRAC))
#define gsDPLoadMultiBlock_4b(timg, tmem, rtile, fmt, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt) \
    gsDPLoadMultiBlock(timg, tmem, rtile, fmt, G_IM_SIZ_4b, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt)

/* ---- Combine mode presets ---- */
/* G_CC_MODULATEIDECALA: modulate with shade, pass alpha */
#define G_CC_MODULATEIDECALA  TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0
#define G_CC_MODULATEIA       TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0
#define G_CC_MODULATERGB      TEXEL0, 0, SHADE, 0, 1, 0, 0, 0
#define G_CC_MODULATERGBA     TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0
#define G_CC_DECALRGB         0, 0, 0, TEXEL0, 0, 0, 0, SHADE
#define G_CC_DECALRGBA        0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0
#define G_CC_FADE             SHADE, 0, ENVIRONMENT, 0, SHADE, 0, ENVIRONMENT, 0
#define G_CC_PASS             0, 0, 0, COMBINED, 0, 0, 0, COMBINED
#define G_CC_DECAL_RGBA       0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0
/* TM (texture modulate — texel * shade) */
#define G_CC_TM               TEXEL0, 0, SHADE, 0, TEXEL0, 0, SHADE, 0
/* BACK (for S2DEX2 background) */
#define G_CC_BACK             0, 0, 0, TEXEL0, 0, 0, 0, 1
/* PRIMITIVE: solid primitive color */
#define G_CC_PRIMITIVE        0, 0, 0, PRIMITIVE, 0, 0, 0, PRIMITIVE
/* SHADE: pass through shade color */
#define G_CC_SHADE            0, 0, 0, SHADE, 0, 0, 0, SHADE
/* Additional common presets */
#define G_CC_MODULATEI        TEXEL0, 0, SHADE, 0, 0, 0, 0, SHADE
#define G_CC_DECAL_RGB        0, 0, 0, TEXEL0, 0, 0, 0, SHADE
#define G_CC_BLENDI           ENVIRONMENT, SHADE, TEXEL0, SHADE, 0, 0, 0, SHADE
#define G_CC_HILITERGB        PRIMITIVE, SHADE, TEXEL0, SHADE, 0, 0, 0, SHADE
#define G_CC_HILITERGBA       PRIMITIVE, SHADE, TEXEL0, SHADE, PRIMITIVE, SHADE, TEXEL0, SHADE
#define G_CC_HILITERGBDECALA  PRIMITIVE, SHADE, TEXEL0, SHADE, 0, 0, 0, TEXEL0
#define G_CC_SHADEDECALA      0, 0, 0, SHADE, 0, 0, 0, TEXEL0
#define G_CC_BLENDPEDECALA    ENVIRONMENT, SHADE, TEXEL0, SHADE, 0, 0, 0, TEXEL0
#define G_CC_TRILERP          TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0, TEXEL1, TEXEL0, LOD_FRACTION, TEXEL0
#define G_CC_INTERFERENCE     TEXEL0, 0, TEXEL1, 0, TEXEL0, 0, TEXEL1, 0

/* ---- Vertex types ---- */
typedef struct {
    short ob[3];
    unsigned short flag;
    short tc[2];
    unsigned char cn[4];
} Vtx_t;

typedef struct {
    short ob[3];
    unsigned short flag;
    short tc[2];
    signed char n[3];
    unsigned char a;
} Vtx_tn;

typedef union {
    Vtx_t  v;
    Vtx_tn n;
    long long int force_structure_alignment;
} Vtx;

/* ---- Light types ---- */
typedef struct {
    unsigned char col[3];
    unsigned char pad1;
    unsigned char colc[3];
    unsigned char pad2;
    signed char dir[3];
    unsigned char pad3;
} Light_t;

typedef struct {
    unsigned char col[3];
    unsigned char pad1;
    unsigned char colc[3];
    unsigned char pad2;
    int pad3[2];
} Ambient_t;

typedef union { Light_t l;   long long int force_structure_alignment[2]; } Light;
typedef union { Ambient_t l; long long int force_structure_alignment[2]; } Ambient;

#define NUMLIGHTS_STRUCT_MEMBER(n) \
    Light l[n]; Ambient a;

typedef struct { NUMLIGHTS_STRUCT_MEMBER(1) } Lights0;
typedef struct { NUMLIGHTS_STRUCT_MEMBER(1) } Lights1;
typedef struct { NUMLIGHTS_STRUCT_MEMBER(2) } Lights2;
typedef struct { NUMLIGHTS_STRUCT_MEMBER(3) } Lights3;
typedef struct { NUMLIGHTS_STRUCT_MEMBER(4) } Lights4;
typedef struct { NUMLIGHTS_STRUCT_MEMBER(5) } Lights5;
typedef struct { NUMLIGHTS_STRUCT_MEMBER(6) } Lights6;
typedef struct { NUMLIGHTS_STRUCT_MEMBER(7) } Lights7;

#define gdSPDefLights0(ar, ag, ab) \
    { { {{ {255,255,255}, 0, {255,255,255}, 0, {0,0,0}, 0 } } }, \
      { { {ar, ag, ab}, 0, {ar, ag, ab}, 0, {0,0} } } }

#define gdSPDefLights1(ar, ag, ab, r0, g0, b0, x0, y0, z0) \
    { { {{ {r0,g0,b0}, 0, {r0,g0,b0}, 0, {x0,y0,z0}, 0 } } }, \
      { { {ar, ag, ab}, 0, {ar, ag, ab}, 0, {0,0} } } }

/* Lookat */
typedef struct {
    struct {
        unsigned char col[3]; unsigned char pad;
        unsigned char colc[3]; unsigned char pad2;
        signed char dir[3]; unsigned char pad3;
    } l[2];
} LookAt;

#define gdSPDefLookAt(rx, ry, rz, ux, uy, uz) \
    { { { {0,0,0}, 0, {0,0,0}, 0, {rx, ry, rz}, 0 }, \
        { {0,0,0}, 0, {0,0,0}, 0, {ux, uy, uz}, 0 } } }

/* N64 Mtx (fixed-point 16.16 4x4) — struct so struct-assignment works */
typedef struct { long long int m[4]; } Mtx;   /* 4 × 8 bytes = 32 bytes */

/* ---- Viewport ---- */
typedef struct {
    short vscale[4];  /* scale: x, y, z, ? */
    short vtrans[4];  /* translate: x, y, z, ? */
} Vp_t;

typedef union {
    Vp_t vp;
    long long int force_structure_alignment;
} Vp;

/* ---- Hilite (specular highlight) ---- */
typedef struct {
    int x1, y1;
    int x2, y2;
} Hilite_t;

typedef union {
    Hilite_t h;
    long long int force_structure_alignment[2];
} Hilite;

/* ---- GBI command structs (used by emu64 and gbi_extensions) ---- */
typedef struct {
    unsigned int cmd   : 8;
    unsigned int fmt   : 3;
    unsigned int siz   : 2;
    unsigned int pad   : 7;
    unsigned int width : 12;
    unsigned int imgaddr;
} Gsettimg;

typedef Gsettimg Gsetimg;  /* alias used by gbi_extensions */

typedef struct {
    unsigned int cmd : 8;
    unsigned int unk : 24;
    unsigned int addr;
} Gsetzimg;

/* S2DEX2 background/sprite types are in PR/gs2dex.h */
#define G_BGLT_LOADBLOCK  0x0033
#define G_BGLT_LOADTILE   0xfff4
#define G_BG_FLAG_FLIPS   (1 << 0)
#define G_BG_FLAG_FLIPT   (1 << 1)

/* ---- ClipRatio ---- */
#define FRUSTRATIO_1  1
#define FRUSTRATIO_2  2
#define FRUSTRATIO_3  3
#define FRUSTRATIO_4  4
#define FRUSTRATIO_5  5
#define FRUSTRATIO_6  6

#ifdef __cplusplus
}
#endif

#endif /* _PR_MBI_H_ */
