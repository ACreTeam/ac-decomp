#include "libforest/gbi_extensions.h"

static u16 myr_kotei_pal[] = {
#include "assets/field/bg/myr_kotei_pal.inc"
};

static u8 myr_enter[] = {
#include "assets/field/bg/myr_enter.inc"
};

static u8 myr_window[] = {
#include "assets/field/bg/myr_window.inc"
};

static Vtx myr_kotei_v[] = {
#include "assets/field/bg/myr_kotei_v.inc"
};

static Gfx myr_kotei_model[] = {
    gsSPTexture(65535, 65535, 0, 0, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_AA_ZB_TEX_EDGE2),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, myr_kotei_pal),
    gsDPLoadTextureBlock_4b(myr_enter, G_IM_FMT_CI, 64, 32, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, 6,
                            5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPClearGeometryMode(G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(&myr_kotei_v[0], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 2, 0, 5, 0, 2, 0),
    gsSPEndDisplayList(),
};

static Gfx myr_out_model[] = {
    gsSPTexture(65535, 65535, 0, 0, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PASS2),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_AA_ZB_TEX_EDGE2),
    gsSPClearGeometryMode(G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(&myr_kotei_v[6], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
    gsSPEndDisplayList(),
};

static Gfx myr_koteiT_model[] = {
    gsSPTexture(65535, 65535, 0, 0, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, COMBINED, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_NOOP, G_RM_AA_ZB_TEX_EDGE2),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, myr_kotei_pal),
    gsDPLoadTextureBlock_4b(myr_window, G_IM_FMT_CI, 64, 64, 15, G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP, 6,
                            6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPClearGeometryMode(G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR),
    gsSPSetGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_SHADING_SMOOTH),
    gsSPVertex(&myr_kotei_v[14], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPEndDisplayList(),
};

extern Gfx myr_etc_model[] = {
    gsDPPipeSync(),
    gsSPDisplayList(myr_kotei_model),
    gsSPDisplayList(myr_koteiT_model),
    gsSPDisplayList(myr_out_model),
    gsSPEndDisplayList(),
};
