#include "libforest/gbi_extensions.h"

static u16 grd_1_earth_pal[] = {
#include "assets/field/bg/grd_1_earth_pal.inc"
};

static u8 grd_s_river_tex[] = {
#include "assets/field/bg/grd_s_river_tex.inc"
};

static u8 grd_water1_tex[] = {
#include "assets/field/bg/grd_water1_tex.inc"
};

static u8 grd_s_grass_tex[] = {
#include "assets/field/bg/grd_s_grass_tex2.inc"
};

static Vtx tmpr2_v[] = {
#include "assets/field/bg/tmpr2_v.inc"
};

static Gfx tmpr2_grp_grd_s_r1_1_river[] = {
    gsSPTexture(65535, 65535, 0, 0, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, grd_1_earth_pal),
    gsDPLoadTextureBlock_4b(grd_s_river_tex, G_IM_FMT_CI, 64, 32, 15, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_CLAMP, 6, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tmpr2_v[25], 19, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(1, 4, 3, 0, 4, 5, 3, 0),
    gsSP2Triangles(4, 6, 5, 0, 6, 7, 5, 0),
    gsSP2Triangles(6, 8, 7, 0, 6, 9, 8, 0),
    gsSP2Triangles(10, 11, 12, 0, 11, 13, 12, 0),
    gsSP2Triangles(13, 4, 12, 0, 14, 15, 16, 0),
    gsSP2Triangles(14, 17, 15, 0, 15, 13, 16, 0),
    gsSP2Triangles(15, 4, 13, 0, 10, 18, 11, 0),
    gsSPEndDisplayList(),
};

static Gfx tmpr2_grp_grd_s_r1_1_grass[] = {
    gsSPTexture(65535, 65535, 0, 0, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, grd_1_earth_pal),
    gsDPLoadTextureBlock_4b(grd_s_grass_tex, G_IM_FMT_CI, 32, 32, 15, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tmpr2_v[0], 25, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(3, 4, 2, 0, 3, 5, 4, 0),
    gsSP2Triangles(0, 6, 1, 0, 0, 7, 6, 0),
    gsSP2Triangles(7, 8, 6, 0, 8, 9, 6, 0),
    gsSP2Triangles(9, 10, 6, 0, 10, 11, 6, 0),
    gsSP2Triangles(11, 1, 6, 0, 11, 12, 1, 0),
    gsSP2Triangles(12, 3, 1, 0, 12, 13, 3, 0),
    gsSP2Triangles(13, 14, 3, 0, 14, 5, 3, 0),
    gsSP2Triangles(15, 16, 17, 0, 16, 18, 17, 0),
    gsSP2Triangles(19, 17, 18, 0, 19, 20, 17, 0),
    gsSP2Triangles(15, 21, 16, 0, 21, 22, 16, 0),
    gsSP2Triangles(21, 23, 22, 0, 21, 24, 23, 0),
    gsSPEndDisplayList(),
};

static Gfx tmpr2_grp_grd_s_r1_1_waterT[] = {
    gsSPTexture(65535, 65535, 0, 0, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock_4b(grd_water1_tex, G_IM_FMT_I, 32, 32, 15, G_TX_MIRROR | G_TX_WRAP, G_TX_MIRROR | G_TX_WRAP, 5,
                            5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tmpr2_v[44], 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(1, 4, 2, 0, 4, 5, 2, 0),
    gsSP2Triangles(4, 6, 5, 0, 6, 7, 5, 0),
    gsSP2Triangles(6, 8, 7, 0, 8, 9, 7, 0),
    gsSPEndDisplayList(),
};

extern Gfx tmpr2_modelT[] = {
    gsSPDisplayList(tmpr2_grp_grd_s_r1_1_waterT),
    gsSPEndDisplayList(),
};

extern Gfx tmpr2_model[] = {
    gsSPDisplayList(tmpr2_grp_grd_s_r1_1_grass),
    gsSPDisplayList(tmpr2_grp_grd_s_r1_1_river),
    gsSPEndDisplayList(),
};
