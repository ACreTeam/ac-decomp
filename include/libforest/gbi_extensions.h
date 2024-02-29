#ifndef __GBI_EXTENSIONS_H__
#define __GBI_EXTENSIONS_H__

#ifdef __cplusplus
extern "C" {
#endif

// clang-format off

#include "types.h"
#include <PR/mbi.h>
#include "dolphin/gx.h"

/* New Microcode Command Ids */
#define G_TRIN 0x09
#define G_TRIN_INDEPEND 0x0A

#define G_SETTEXEDGEALPHA 0xCE
#define G_SETCOMBINE_NOTEV 0xCF
#define G_SETCOMBINE_TEV 0xD0
#define G_SETTILE_DOLPHIN 0xD2

#define G_FIRST_CMD G_SETTEXEDGEALPHA

#define G_CC_BLENDPRIMDECALA 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0

/* Triangle/Quad vertex bit size */
#define POLY_5b 0 /* 5 bits per vertex index (0 - 31) */
#define POLY_7b 1 /* 7 bits per vertex index (0 - 127) */
#define POLY_BITMASK 1

/* First face, 5 bits */
#define POLY_GET_V0_5b(g)((g->words.w1 >> 4) & 0x1F)
#define POLY_GET_V1_5b(g)((g->words.w1 >> 9) & 0x1F)
#define POLY_GET_V2_5b(g)((g->words.w1 >> 14) & 0x1F)

/* Second face, 5 bits */
#define POLY_GET_V3_5b(g)((g->words.w1 >> 19) & 0x1F)
#define POLY_GET_V4_5b(g)((g->words.w1 >> 24) & 0x1F)
#define POLY_GET_V5_5b(g)((((g->words.w1 >> 29) & 7) | ((g->words.w0 & 3) << 3)) & 0x1F)

/* Third face, 5 bits */
#define POLY_GET_V6_5b(g)((g->words.w0 >> 2) & 0x1F)
#define POLY_GET_V7_5b(g)((g->words.w0 >> 7) & 0x1F)
#define POLY_GET_V8_5b(g)((g->words.w0 >> 12) & 0x1F)

/* Fourth face, 5 bits */
#define POLY_GET_V9_5b(g)((g->words.w0 >> 17) & 0x1F)
#define POLY_GET_V10_5b(g)((g->words.w0 >> 22) & 0x1F)
#define POLY_GET_V11_5b(g)((g->words.w0 >> 27) & 0x1F)

/* First face, 7 bits */
#define POLY_GET_V0_7b(g)((g->words.w1 >> 1) & 0x7F)
#define POLY_GET_V1_7b(g)((g->words.w1 >> 8) & 0x7F)
#define POLY_GET_V2_7b(g)((g->words.w1 >> 15) & 0x7F)

/* Second face, 7 bits */
#define POLY_GET_V3_7b(g)((g->words.w1 >> 22) & 0x7F)
#define POLY_GET_V4_7b(g)((((g->words.w1 >> 29) & 7) | ((g->words.w0 & 0xF) << 3)) & 0x7F)
#define POLY_GET_V5_7b(g)((g->words.w0 >> 4) & 0x7F)

/* Third face, 7 bits */
#define POLY_GET_V6_7b(g)((g->words.w0 >> 11) & 0x7F)
#define POLY_GET_V7_7b(g)((g->words.w0 >> 18) & 0x7F)
#define POLY_GET_V8_7b(g)((g->words.w0 >> 25) & 0x7F)

/* Vertex matrix types */
#define SHARED_MTX GX_PNMTX0
#define NONSHARED_MTX GX_PNMTX1

#define MTX_SHARED 0
#define MTX_NONSHARED 1

/* NOOP Debug Tags */
#define G_TAG_NONE 0
#define G_TAG_HERE 1
#define G_TAG_STRING 2
#define G_TAG_WORD 3
#define G_TAG_FLOAT 4
#define G_TAG_INFO 5
#define G_TAG_CALLBACK 6
#define G_TAG_OPENDISP 7
#define G_TAG_CLOSEDISP 8
#define G_TAG_FILL 9

/* Vertex Culling Flags */
#define G_CULL_X_LESSTHAN 0x100 /* x component left of culling plane */
#define G_CULL_X_GREATERTHAN 0x200 /* x component right of culling plane */
#define G_CULL_Y_LESSTHAN 0x400 /* y component below culling plane */
#define G_CULL_Y_GREATERTHAN 0x800 /* y component above culling plane */
#define G_CULL_Z_LESSTHAN 0x1000 /* z component behind culling plane */
#define G_CULL_Z_GREATERTHAN 0x2000 /* z component farther than culling plane */

/* Extra Geometry Mode Flags */
#define G_LIGHTING_POSITIONAL 0x400000
#define G_DECAL_LEQUAL 0x00
#define G_DECAL_GEQUAL 0x10
#define G_DECAL_EQUAL 0x20
#define G_DECAL_ALWAYS 0x30
#define G_DECAL_SPECIAL 0x40
#define G_DECAL_ALL G_DECAL_ALWAYS | G_DECAL_SPECIAL

/* Indicies for G_SPECIAL_1 */
#define G_SPECIAL_NONE 0
#define G_SPECIAL_UNKNOWN 1
#define G_SPECIAL_TA_MODE 2

/* Texture Adjust Modes (used in G_SPECIAL1) */
#define G_TA_N64 0
#define G_TA_DOLPHIN 1

/* Combiner Param Ids */
#define COMBINER_PARAM_A 1
#define COMBINER_PARAM_B 2
#define COMBINER_PARAM_C 3
#define COMBINER_PARAM_D 4

/* TEV Combiner Settings */

#define TEV_COMBINED 0
#define TEV_COMBINED_ALPHA 1
#define TEV_FILL 2
#define TEV_PRIM_LOD_FRAC 3
#define TEV_PRIMITIVE 4
#define TEV_PRIMITIVE_ALPHA 5
#define TEV_ENVIRONMENT 6
#define TEV_ENV_ALPHA 7
#define TEV_TEXEL0 8
#define TEV_TEXEL0_ALPHA 9
#define TEV_SHADE 10
#define TEV_SHADE_ALPHA 11
#define TEV_ONE 12
#define TEV_HALF 13
#define TEV_KONST 14
#define TEV_ZERO 15

#define TEV_ALPHA_COMBINED 0
#define TEV_ALPHA_PRIM_LOD_FRAC 1
#define TEV_ALPHA_PRIMITIVE 2
#define TEV_ALPHA_ENVIRONMENT 3
#define TEV_ALPHA_TEXEL0 4
#define TEV_ALPHA_SHADE 5
#define TEV_ALPHA_ONE 6
#define TEV_ALPHA_ZERO 7

/* Macro to expand packed image/tile width and height */
#define EXPAND_WIDTH(wd)(wd + 1)
#define EXPAND_HEIGHT(ht)((ht + 1) * 4)

/* Combiner Macros */

#define COMBINER_GET_a0(words)((words.w0 >> 20) & 0xF)
#define COMBINER_GET_b0(words)((words.w1 >> 28) & 0xF)
#define COMBINER_GET_c0(words)((words.w0 >> 15) & 0x1F)
#define COMBINER_GET_d0(words)((words.w1 >> 15) & 7)

#define COMBINER_GET_Aa0(words)((words.w0 >> 12) & 7)
#define COMBINER_GET_Ab0(words)((words.w1 >> 12) & 7)
#define COMBINER_GET_Ac0(words)((words.w0 >> 9) & 7)
#define COMBINER_GET_Ad0(words)((words.w1 >> 9) & 7)

#define COMBINER_GET_a1(words)((words.w0 >> 5) & 0xF)
#define COMBINER_GET_b1(words)((words.w1 >> 24) & 0xF)
#define COMBINER_GET_c1(words)(words.w0 & 0x1F)
#define COMBINER_GET_d1(words)((words.w1 >> 6) & 7)

#define COMBINER_GET_Aa1(words)((words.w1 >> 21) & 7)
#define COMBINER_GET_Ab1(words)((words.w1 >> 3) & 7)
#define COMBINER_GET_Ac1(words)((words.w1 >> 18) & 7)
#define COMBINER_GET_Ad1(words)(words.w1 & 7)

/* TEV Combiner Macros */

#define COMBINER_TEV_GET_a0(words)((words.w1 >> 28) & 0xF)
#define COMBINER_TEV_GET_b0(words)((words.w1 >> 24) & 0xF)
#define COMBINER_TEV_GET_c0(words)((words.w1 >> 20) & 0xF)
#define COMBINER_TEV_GET_d0(words)((words.w1 >> 16) & 0xF)

#define COMBINER_TEV_GET_Aa0(words)((words.w0 >> 21) & 7)
#define COMBINER_TEV_GET_Ab0(words)((words.w0 >> 18) & 7)
#define COMBINER_TEV_GET_Ac0(words)((words.w0 >> 15) & 7)
#define COMBINER_TEV_GET_Ad0(words)((words.w0 >> 12) & 7)

#define COMBINER_TEV_GET_a1(words)((words.w1 >> 12) & 0xF)
#define COMBINER_TEV_GET_b1(words)((words.w1 >>  8) & 0xF)
#define COMBINER_TEV_GET_c1(words)((words.w1 >>  4) & 0xF)
#define COMBINER_TEV_GET_d1(words)((words.w1 >>  0) & 0xF)

#define COMBINER_TEV_GET_Aa1(words)((words.w0 >>  9) & 7)
#define COMBINER_TEV_GET_Ab1(words)((words.w0 >>  6) & 7)
#define COMBINER_TEV_GET_Ac1(words)((words.w0 >>  3) & 7)
#define COMBINER_TEV_GET_Ad1(words)((words.w0 >>  0) & 7)

typedef struct {
    int cmd:8;
    unsigned int a0:4;
    unsigned int c0:5;
    unsigned int Aa0:3;
    unsigned int Ac0:3;
    unsigned int a1:4;
    unsigned int c1:5;

    unsigned int b0:4;
    unsigned int b1:4;
    unsigned int Aa1:3;
    unsigned int Ac1:3;
    unsigned int d0:3;
    unsigned int Ab0:3;
    unsigned int Ad0:3;
    unsigned int d1:3;
    unsigned int Ab1:3;
    unsigned int Ad1:3;
} Gsetcombine_new;

typedef struct {
    int cmd:8; /* 0xCF */
    unsigned int Aa0:3;
    unsigned int Ab0:3;
    unsigned int Ac0:3;
    unsigned int Ad0:3;

    unsigned int Aa1:3;
    unsigned int Ab1:3;
    unsigned int Ac1:3;
    unsigned int Ad1:3;

    unsigned int a0:4;
    unsigned int b0:4;
    unsigned int c0:4;
    unsigned int d0:4;

    unsigned int a1:4;
    unsigned int b1:4;
    unsigned int c1:4;
    unsigned int d1:4;
} Gsetcombine_tev;

typedef struct {
    unsigned int cmd:8;
    unsigned int xl:12;	/* Top-left x coord */
    unsigned int yl:12;	/* Top-left y coord */
    unsigned int pad1:5;
    unsigned int tile:3; /* Tile descriptor index */
    unsigned int xh:12;	/* Lower-right x coord */
    unsigned int yh:12;	/* Lower-right y coord */

    unsigned int pad2:32;

    unsigned int s:16;	/* S (X) texture coord at top left */
    unsigned int t:16;	/* T (Y) texture coord at top left */

    unsigned int pad3:32;

    unsigned int dsdx:16; /* Change in S (X) per change in X */
    unsigned int dtdy:16; /* Change in T (Y) per change in Y */
} Gtexrect2;

typedef struct {
    int cmd:8;
    unsigned int dol_fmt:4;
    unsigned int pad0:1;
    unsigned int tile:3;
    unsigned int tlut_name:4;
    unsigned int wrap_s:2;
    unsigned int wrap_t:2;
    unsigned int shift_s:4;
    unsigned int shift_t:4;
    unsigned int pad1:32;
} Gsettile_dolphin;

typedef struct {
    int cmd:8;
    unsigned int sl:14; /* Start of S coordinate */
    unsigned int slen:10; /* Length of S coordinate */
    
    unsigned int isDolphin:1; /* If true, format is Gsettilesize_dolphin. If false, format is Gsettilesize2 */
    unsigned int pad:4;
    unsigned int tile:3; /* Tile descriptor */
    unsigned int tl:14; /* Start of T coordinate */
    unsigned int tlen:10; /* Length of T coordinate */
} Gsettilesize_dolphin;

typedef struct {
    int cmd:8; /* Command */
    unsigned int fmt:3; /* Image format */
    unsigned int siz:2; /* Image format texel size */
    unsigned int isDolphin:1; /* Is this Gsetimg2 or Gsetimg */
    unsigned int ht:8; /* Height, packed: (height / 4) - 1 */
    unsigned int wd:10; /* Width, packed: width - 1 */

    unsigned int imgaddr:32; /* Image RAM address */
} Gsetimg2;

typedef union {
    Gsetimg setimg;
    Gsetimg2 setimg2;
} Gsetimg_new;

typedef struct {
    int cmd:8;
    unsigned int type:2; /* Type - if 2, is Gloadtlut_dolphin. Otherwise is Gloadtlut. */
    unsigned int pad0:2;
    unsigned int tlut_name:4; /* GC Palette/TLUT name(index). */
    unsigned int pad1:2;
    unsigned int count:14; /* Number of entries in the TLUT. Max by GC spec is 0x4000. */
    
    unsigned int tlut_addr:32;
} Gloadtlut_dolphin;

typedef struct {
    unsigned int cmd:8;
    unsigned int xparam:8;
    unsigned int pad:2;
    unsigned int level:3;
    unsigned int tile:3;
    unsigned int on:8; /* Should be 7 bits w/ 1 bit padding, but emulator doesn't do this */
    unsigned short s:16;
    unsigned short t:16;
} Gtexture_internal;

typedef struct {
    unsigned int cmd:8;
    unsigned int index:8;
    unsigned int offset:16;
    unsigned int data;
} Gmoveword;

typedef struct {
    unsigned int cmd:8;
    unsigned int length:8;
    unsigned int offset:8;
    unsigned int index:8;

    unsigned int data;
} Gmovemem;

typedef struct {
    unsigned char col[3];
    unsigned char kc;
    unsigned char colc[3];
    unsigned char kl;
    signed short pos[3]; /* position of light */
    unsigned char kq;
} Light_pos_t;

typedef union {
    Light_t l;
    Light_pos_t p;
    long long int force_align[2];
} Light_new;

/* Combiner Structs */
typedef struct {
    u8 color0;
    u8 color1;
    u8 color2;
    u8 color3;
} combiner_tev_color;

typedef struct {
    u8 alpha0;
    u8 alpha1;
} combiner_tev_alpha;

/* New Command Macros */
#define gsDPParam2(cmd, tag, param, extra) \
{{ \
	_SHIFTL(cmd, 24, 8) | _SHIFTL(tag, 16, 8) | _SHIFTL(param, 0, 16), extra \
}}

#define gsDPNoOpTag2(tag, param, extra) gsDPParam2(G_NOOP, tag, param, extra) 
#define	gsDPNoOpHere() gsDPNoOpTag2(G_TAG_HERE, __LINE__, __FILE__)
#define gsDPNoOpString(str, param) gsDPNoOpTag2(G_TAG_STRING, param, str)
#define gsDPNoOpWord(word, param) gsDPNoOpTag2(G_TAG_WORD, param, word)
#define gsDPNoOpFloat(float, param) gsDPNoOpTag2(G_TAG_FLOAT, param, float)
#define gsDPNoOpQuiet() gsDPNoOpTag2(G_TAG_INFO, 0, 0)
#define gsDPNoOpVerbose() gsDPNoOpTag2(G_TAG_INFO, 0xF, 0)
#define gsDPNoOpCallBack(callback, param) gsDPNoOpTag2(G_TAG_CALLBACK, param, callback)
#define gsDPNoOpOpenDisp() gsDPNoOpTag2(G_TAG_OPENDISP, __LINE__, __FILE__)
#define gsDPNoOpCloseDisp() gsDPNoOpTag2(G_TAG_CLOSEDISP, __LINE__, __FILE__)
#define gsDPNoOpFill() gsDPNoOpTag2(G_TAG_FILL, 0, 0)
#define gsDPNoOpTag3(tag, extra, param) gsDPNoOpTag2(tag, param, extra)

#define G_TLUT_DOLPHIN 2
#define gDPLoadTLUT_Dolphin(pkt, name, count, unk, addr) \
do { \
    Gfx* _g = (Gfx*)(pkt); \
    _g->words.w0 = _SHIFTL(G_LOADTLUT, 24, 8) | _SHIFTL(G_TLUT_DOLPHIN, 22, 2) | _SHIFTL(name, 16, 4) | _SHIFTL(unk, 14, 2) | _SHIFTL(count, 0, 14); \
    _g->words.w1 = (unsigned int)addr; \
} while (0)

#define gsDPLoadTLUT_Dolphin(name, count, unk, addr) \
{{ \
    _SHIFTL(G_LOADTLUT, 24, 8) | _SHIFTL(G_TLUT_DOLPHIN, 22, 2) | _SHIFTL(name, 16, 4) | _SHIFTL(unk, 14, 2) | _SHIFTL(count, 0, 14), (unsigned int)addr \
}}

#define gsDPSetTextureImage_Dolphin(fmt, siz, h, w, img) \
{{ \
    _SHIFTL(G_SETTIMG, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | _SHIFTL(1, 18, 1) | \
        _SHIFTL((h/4)-1, 10, 8) | _SHIFTL((w-1), 0, 10), (unsigned int)img \
}}

#define gsDPSetTile_Dolphin(d_fmt, tile, tlut_name, wrap_s, wrap_t, shift_s, shift_t) \
{{ \
    _SHIFTL(G_SETTILE_DOLPHIN, 24, 8) | _SHIFTL(d_fmt, 20, 4) | _SHIFTL(tile, 16, 3) | \
        _SHIFTL(tlut_name, 12, 4) | _SHIFTL(wrap_s, 10, 2) | _SHIFTL(wrap_t, 8, 2) | \
        _SHIFTL(shift_s, 4, 4) | _SHIFTL(shift_t, 0, 4), 0 \
}}

#define gDPSetTextureImage_Dolphin(pkt, fmt, siz, h, w, img) \
{{ \
    Gfx* _gfx = (Gfx*)(pkt); \
    _gfx->words.w0 = _SHIFTL(G_SETTIMG, 24, 8) | _SHIFTL(fmt, 21, 3) | _SHIFTL(siz, 19, 2) | _SHIFTL(1, 18, 1) | \
        _SHIFTL((h/4)-1, 10, 8) | _SHIFTL((w-1), 0, 10); \
    _gfx->words.w1 = (unsigned int)img; \
}}

#define gDPSetTile_Dolphin(pkt, d_fmt, tile, tlut_name, wrap_s, wrap_t, shift_s, shift_t) \
{{ \
    Gfx* _gfx = (Gfx*)(pkt); \
    _gfx->words.w0 = _SHIFTL(G_SETTILE_DOLPHIN, 24, 8) | _SHIFTL(d_fmt, 20, 4) | _SHIFTL(tile, 16, 3) | \
        _SHIFTL(tlut_name, 12, 4) | _SHIFTL(wrap_s, 10, 2) | _SHIFTL(wrap_t, 8, 2) | \
        _SHIFTL(shift_s, 4, 4) | _SHIFTL(shift_t, 0, 4); \
    /*_gfx->words.w1 = 0;*/ /* bug? they don't set the second word */ \
}}

#define gDPSetTileSize_Dolphin(pkt, tile, s, t, width, height)		\
do { \
    Gfx* _gfx = (Gfx*)(pkt); \
    _gfx->words.w0 = _SHIFTL(G_SETTILESIZE, 24, 8) | _SHIFTL(s, 10, 14) | _SHIFTL(width - 1, 0, 10); \
    _gfx->words.w1 = _SHIFTL(1, 31, 1) | _SHIFTL(tile, 24, 3) | _SHIFTL(t, 10, 14) | _SHIFTL(height - 1, 0, 10); \
} while (0)

#define gsDPSetTileSize_Dolphin(tile, s, t, width, height)		\
{{									\
	_SHIFTL(G_SETTILESIZE, 24, 8) | _SHIFTL(s, 10, 14) | _SHIFTL(width - 1, 0, 10),	\
	_SHIFTL(1, 31, 1) | _SHIFTL(tile, 24, 3) | _SHIFTL(t, 10, 14) | _SHIFTL(height - 1, 0, 10)\
}}

#define G_DOLPHIN_TLUT_DEFAULT_MODE 15 // used almost always? CI palettes are forced to GX_TF_RGB5A3
#define gsDPLoadTextureBlock_4b_Dolphin(timg, fmt, w, h, pal, ws, wt, ss, st) \
    gsDPSetTextureImage_Dolphin(fmt, G_IM_SIZ_4b, h, w, timg), \
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, pal, ws, wt, ss, st)

#define gDPLoadTextureTile_4b_Dolphin(pkt, timg, fmt, w, h) \
do { \
    gDPSetTextureImage_Dolphin(pkt, fmt, G_IM_SIZ_4b, h, w, timg); \
    gDPSetTile_Dolphin(pkt, G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, 0, 0, 0, 0) \
} while (0);

#define gsSPNTriangles(n) \
{{ \
    _SHIFTL(G_TRIN_INDEPEND, 24, 8) | _SHIFTL(n-1, 17, 7), 0 \
}}

/* 5 bits per vertex id (32) */
#define gsSPNTriangleData1(v0, v1, v2, flag) (_SHIFTL(v2, 10, 5) | _SHIFTL(v1, 5, 5) | _SHIFTL(v0, 0, 5))

/* 7 bits per vertex id (128) */
#define gsSPNTriangleData2(v0, v1, v2, flag) \
{{ \
    (unsigned long long)(_SHIFTL(v2, 14, 7) | _SHIFTL(v1, 7, 7) | _SHIFTL(v0, 0, 7)) \
}}

#define G_VTX_MODE_5bit 0
#define G_VTX_MODE_7bit 1

#define gSPNTriangles_5b(pkt, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) \
{{ \
  Gfx* _g = (Gfx*)(pkt); \
  _g->words.w0 = (u32)((gsSPNTriangleData1(v9, v10, v11) << 17) | (gsSPNTriangleData1(v6, v7, v8) << 2) | ((gsSPNTriangleData1(v3, v4, v5) >> 13) & 3)); \
  _g->words.w1 = (u32)(((gsSPNTriangleData1(v3, v4, v5) & 7) << 19) | (gsSPNTriangleData1(v0, v1, v2) << 4) | G_VTX_MODE_5bit); \
}}

#define gSPNTrianglesInit_5b(pkt, n, v0, v1, v2, v3, v4, v5, v6, v7, v8) \
{{ \
  Gfx* _g = (Gfx*)(pkt); \
  _g->words.w0 = (u32)(_SHIFTL(G_TRIN_INDEPEND, 24, 8) | _SHIFTL(n-1, 17, 7) | _SHIFTL(gsSPNTriangleData1(v6, v7, v8, 0), 2, 15) | _SHIFTL(_SHIFTR(gsSPNTriangleData1(v3, v4, v5, 0), 2, 13), 0, 2)); \
  _g->words.w1 = (u32)(_SHIFTL(gsSPNTriangleData1(v3, v4, v5, 0), 19, 13) | _SHIFTL(gsSPNTriangleData1(v0, v1, v2, 0), 4, 15) | _SHIFTL(G_VTX_MODE_5bit, 0, 1)); \
}}

// TODO: convert
#define gSPNTriangles_7b(v0, v1, v2, v3, v4, v5, v6, v7, v8) \
{{ \
    (unsigned long long)((gsSPNTriangleData2(v6, v7, v8) << 43) | (gsSPNTriangleData2(v3, v4, v5) << 22) | \
        (gsSPNTriangleData2(v0, v1, v2) << 1)) | G_VTX_MODE_7bit \
}}

#define gSPNTrianglesInit_7b(n, v0, v1, v2, v3, v4, v5) \
{{ \
    (unsigned long long)((((unsigned long long)gsSPNTriangles(n)) << 32) | (gsSPNWTriangleData2(v3, v4, v5) << 22) | \
        (gsSPNTriangleData2(v0, v1, v2) << 1)) | G_VTX_MODE_7bit \
}}

#define gsSPNTriangles_5b(v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) \
{{ \
    _SHIFTL(gsSPNTriangleData1(v9, v10, v11, 0), 17, 15) | _SHIFTL(gsSPNTriangleData1(v6, v7, v8, 0), 2, 15) | _SHIFTL(_SHIFTR(gsSPNTriangleData1(v3, v4, v5, 0), 13, 2), 0, 2), \
    _SHIFTL(gsSPNTriangleData1(v3, v4, v5, 0), 19, 13) | _SHIFTL(gsSPNTriangleData1(v0, v1, v2, 0), 4, 15) | _SHIFTL(G_VTX_MODE_5bit, 0, 1) \
}}

#define gsSPNTrianglesInit_5b(n, v0, v1, v2, v3, v4, v5, v6, v7, v8) \
{{ \
    _SHIFTL(G_TRIN_INDEPEND, 24, 8) | _SHIFTL(n-1, 17, 7) | _SHIFTL(gsSPNTriangleData1(v6, v7, v8, 0), 2, 15) | _SHIFTL(_SHIFTR(gsSPNTriangleData1(v3, v4, v5, 0), 13, 2), 0, 2), \
    _SHIFTL(gsSPNTriangleData1(v3, v4, v5, 0), 19, 13) | _SHIFTL(gsSPNTriangleData1(v0, v1, v2, 0), 4, 15) | _SHIFTL(G_VTX_MODE_5bit, 0, 1) \
}}

#define gsSPNTriangles_7b(v0, v1, v2, v3, v4, v5, v6, v7, v8) \
{{ \
    (unsigned long long)((gsSPNTriangleData2(v6, v7, v8) << 43) | (gsSPNTriangleData2(v3, v4, v5) << 22) | \
        (gsSPNTriangleData2(v0, v1, v2) << 1)) | G_VTX_MODE_7bit \
}}

#define gsSPNTrianglesInit_7b(n, v0, v1, v2, v3, v4, v5) \
{{ \
    (unsigned long long)((((unsigned long long)gsSPNTriangles(n)) << 32) | (gsSPNWTriangleData2(v3, v4, v5) << 22) | \
        (gsSPNTriangleData2(v0, v1, v2) << 1)) | G_VTX_MODE_7bit \
}}

#define gDPSetTexEdgeAlpha(pkt, alpha) \
do { \
  Gfx* _g = (Gfx*)(pkt); \
  _g->words.w0 = (u32)(_SHIFTL(G_SETTEXEDGEALPHA, 24, 8)); \
  _g->words.w1 = (u32)(_SHIFTL(alpha, 0, 8)); \
} while(0)

#define gsDPSetTexEdgeAlpha(alpha) \
{{ \
  (u32)(_SHIFTL(G_SETTEXEDGEALPHA, 24, 8)), \
  (u32)(_SHIFTL(alpha, 0, 8)) \
}}

#define gDPSetTextureAdjustMode(pkt, mode) \
do { \
  Gfx* _g = (Gfx*)(pkt); \
  _g->words.w0 = (u32)(_SHIFTL(G_SPECIAL_1, 24, 8) | _SHIFTL(G_SPECIAL_TA_MODE, 16, 8) | _SHIFTL(mode, 0, 16)); \
  _g->words.w1 = (u32)0; \
} while(0)

#define gsDPSetTextureAdjustMode(mode) \
{{ \
  (u32)(_SHIFTL(G_SPECIAL_1, 24, 8) | _SHIFTL(G_SPECIAL_TA_MODE, 16, 8) | _SHIFTL(mode, 0, 16)), \
  (u32)0 \
}}

//Helpful macro for defining values of a Matrix

#define qs1616(e) ((s32)((e) * 0x00010000))

#define IPART(x) ((qs1616(x) >> 16) & 0xFFFF)
#define FPART(x) (qs1616(x) & 0xFFFF)

#define gdSPDefMtx(     \
        xx, yx, zx, wx, \
        xy, yy, zy, wy, \
        xz, yz, zz, wz, \
        xw, yw, zw, ww) \
    {{                                  \
        (IPART(xx) << 0x10) | IPART(xy),  \
        (IPART(xz) << 0x10) | IPART(xw),  \
        (IPART(yx) << 0x10) | IPART(yy),  \
        (IPART(yz) << 0x10) | IPART(yw),  \
        (IPART(zx) << 0x10) | IPART(zy),  \
        (IPART(zz) << 0x10) | IPART(zw),  \
        (IPART(wx) << 0x10) | IPART(wy),  \
        (IPART(wz) << 0x10) | IPART(ww),  \
        (FPART(xx) << 0x10) | FPART(xy),  \
        (FPART(xz) << 0x10) | FPART(xw),  \
        (FPART(yx) << 0x10) | FPART(yy),  \
        (FPART(yz) << 0x10) | FPART(yw),  \
        (FPART(zx) << 0x10) | FPART(zy),  \
        (FPART(zz) << 0x10) | FPART(zw),  \
        (FPART(wx) << 0x10) | FPART(wy),  \
        (FPART(wz) << 0x10) | FPART(ww),  \
    }}


#define G_DL_GXDL 2

/* Macro for calling GC formatted display lists from N64 lists */
#define gGXCallDisplayList(pkt, dl, nbytes) gDma1p(pkt, G_DL, dl, nbytes, G_DL_GXDL)
#define gsGXCallDisplayList(dl, nbytes) gsDma1p(pkt, G_DL, dl, nbytes, G_DL_GXDL)

// clang-format on

#ifdef __cplusplus
}
#endif

#endif /* __GBI_EXTENSIONS_H__ */
