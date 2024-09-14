#include "libforest/gbi_extensions.h"

static u16 grd_s_cliff_pal[] = {
#include "assets/field/bg/grd_s_cliff_pal.inc"
};

static u16 grd_s_earth_pal[] = {
#include "assets/field/bg/grd_s_earth_pal.inc"
};

static u8 grd_s_cliff_tex[] = {
#include "assets/field/bg/grd_s_cliff_tex.inc"
};

static u8 grd_s_earth_tex[] = {
#include "assets/field/bg/grd_s_earth_tex.inc"
};

static u8 grd_s_grass_tex[] = {
#include "assets/field/bg/grd_s_grass_tex.inc"
};

static Vtx tmp2_v[] = {
#include "assets/field/bg/tmp2_v.inc"
};

extern Gfx tmp2_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx tmp2_model[] = {
    gsSPTexture(65535, 65535, 0, 0, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, grd_s_earth_pal),
    gsDPLoadTextureBlock_4b(grd_s_grass_tex, G_IM_FMT_CI, 32, 32, 15, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&tmp2_v[232], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tmp2_v[0], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(0, 4, 5, 0, 0, 5, 3, 0),
    gsSP2Triangles(4, 6, 5, 0, 7, 8, 9, 0),
    gsSP2Triangles(7, 10, 8, 0, 10, 2, 11, 0),
    gsSP2Triangles(0, 12, 4, 0, 12, 13, 4, 0),
    gsSP2Triangles(14, 15, 6, 0, 8, 10, 16, 0),
    gsSP2Triangles(16, 10, 17, 0, 10, 11, 17, 0),
    gsSP2Triangles(18, 19, 20, 0, 21, 22, 23, 0),
    gsSP2Triangles(21, 24, 22, 0, 22, 25, 26, 0),
    gsSP2Triangles(22, 26, 23, 0, 27, 28, 29, 0),
    gsSP1Triangle(27, 29, 30, 0),
    gsSPVertex(&tmp2_v[31], 10, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 7, 5, 0),
    gsSP2Triangles(5, 8, 9, 0, 5, 9, 6, 0),
    gsSPVertex(&tmp2_v[41], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 4, 0),
    gsSP2Triangles(2, 4, 0, 0, 4, 3, 5, 0),
    gsSP2Triangles(5, 3, 6, 0, 6, 7, 5, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(8, 12, 13, 0, 8, 13, 9, 0),
    gsSP2Triangles(14, 15, 16, 0, 14, 16, 17, 0),
    gsSP2Triangles(18, 19, 15, 0, 18, 15, 14, 0),
    gsSP2Triangles(6, 20, 7, 0, 21, 7, 20, 0),
    gsSP2Triangles(21, 20, 22, 0, 23, 22, 20, 0),
    gsSP2Triangles(23, 20, 24, 0, 25, 23, 24, 0),
    gsSP2Triangles(24, 26, 25, 0, 24, 27, 28, 0),
    gsSP2Triangles(24, 28, 26, 0, 29, 30, 31, 0),
    gsSPVertex(&tmp2_v[73], 16, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 5, 6, 0, 6, 5, 7, 0),
    gsSP2Triangles(6, 7, 8, 0, 8, 7, 9, 0),
    gsSP2Triangles(8, 9, 10, 0, 2, 11, 12, 0),
    gsSP2Triangles(2, 12, 4, 0, 12, 13, 4, 0),
    gsSP2Triangles(2, 1, 11, 0, 4, 13, 14, 0),
    gsSP1Triangle(14, 15, 4, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&tmp2_v[89], 14, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 2, 0, 5, 6, 2, 0),
    gsSP2Triangles(5, 2, 4, 0, 7, 6, 8, 0),
    gsSP2Triangles(6, 9, 8, 0, 6, 5, 9, 0),
    gsSP2Triangles(7, 10, 6, 0, 11, 12, 13, 0),
    gsSP2Triangles(11, 13, 10, 0, 11, 10, 7, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_pal16(15, grd_s_earth_pal),
    gsDPLoadTextureBlock_4b(grd_s_earth_tex, G_IM_FMT_CI, 64, 64, 15, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&tmp2_v[103], 29, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(6, 3, 7, 0, 7, 8, 6, 0),
    gsSP2Triangles(9, 6, 8, 0, 10, 9, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 10, 15, 16, 0),
    gsSP2Triangles(16, 12, 14, 0, 14, 13, 17, 0),
    gsSP2Triangles(17, 18, 19, 0, 9, 20, 21, 0),
    gsSP2Triangles(10, 22, 9, 0, 23, 24, 10, 0),
    gsSP2Triangles(25, 26, 23, 0, 27, 25, 28, 0),
    gsSP1Triangle(2, 27, 28, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, grd_s_cliff_pal),
    gsDPLoadTextureBlock_4b(grd_s_cliff_tex, G_IM_FMT_CI, 64, 64, 15, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&tmp2_v[132], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 5, 6, 0, 0, 7, 8, 0),
    gsSP2Triangles(0, 8, 1, 0, 9, 10, 4, 0),
    gsSP2Triangles(9, 4, 11, 0, 12, 13, 14, 0),
    gsSP2Triangles(12, 14, 0, 0, 15, 16, 17, 0),
    gsSP2Triangles(18, 19, 20, 0, 19, 21, 20, 0),
    gsSP2Triangles(18, 22, 19, 0, 23, 24, 25, 0),
    gsSP2Triangles(23, 25, 26, 0, 18, 27, 28, 0),
    gsSP2Triangles(18, 28, 22, 0, 29, 30, 24, 0),
    gsSP1Triangle(29, 24, 31, 0),
    gsSPVertex(&tmp2_v[164], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(11, 10, 12, 0, 11, 12, 13, 0),
    gsSP2Triangles(7, 6, 0, 0, 7, 0, 3, 0),
    gsSP2Triangles(12, 14, 15, 0, 12, 16, 14, 0),
    gsSP2Triangles(17, 18, 19, 0, 17, 19, 20, 0),
    gsSP2Triangles(21, 22, 23, 0, 21, 23, 24, 0),
    gsSP2Triangles(20, 25, 26, 0, 20, 26, 27, 0),
    gsSP2Triangles(28, 23, 29, 0, 28, 29, 30, 0),
    gsSP1Triangle(20, 27, 31, 0),
    gsSPVertex(&tmp2_v[196], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSP2Triangles(4, 5, 6, 0, 7, 4, 6, 0),
    gsSP2Triangles(7, 6, 8, 0, 9, 10, 11, 0),
    gsSP2Triangles(9, 11, 3, 0, 12, 13, 7, 0),
    gsSP2Triangles(12, 7, 14, 0, 15, 5, 13, 0),
    gsSP2Triangles(15, 13, 12, 0, 1, 16, 10, 0),
    gsSP2Triangles(1, 10, 9, 0, 17, 18, 19, 0),
    gsSP2Triangles(17, 19, 20, 0, 21, 22, 23, 0),
    gsSP2Triangles(21, 23, 24, 0, 24, 23, 25, 0),
    gsSP2Triangles(24, 25, 26, 0, 20, 19, 27, 0),
    gsSP2Triangles(20, 27, 28, 0, 25, 29, 30, 0),
    gsSP2Triangles(25, 31, 29, 0, 31, 22, 29, 0),
    gsSPVertex(&tmp2_v[228], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};
