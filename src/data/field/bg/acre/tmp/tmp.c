#include "libforest/gbi_extensions.h"

extern u8 grass_tex_dummy[];

static Vtx tmp_v[] = {
#include "assets/field/bg/tmp_v.inc"
};

extern Gfx tmp_modelT[] = {
    gsSPEndDisplayList(),
};

extern Gfx tmp_model[] = {
    gsSPTexture(65535, 65535, 0, 0, G_ON),
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTextureBlock_4b(grass_tex_dummy, G_IM_FMT_CI, 32, 32, 15, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&tmp_v[0], 28, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 3, 0, 4, 3, 6, 0),
    gsSP2Triangles(7, 0, 8, 0, 7, 8, 9, 0),
    gsSP2Triangles(10, 7, 9, 0, 10, 9, 11, 0),
    gsSP2Triangles(12, 4, 6, 0, 12, 6, 13, 0),
    gsSP2Triangles(14, 10, 11, 0, 14, 11, 15, 0),
    gsSP2Triangles(16, 12, 13, 0, 16, 13, 17, 0),
    gsSP2Triangles(18, 14, 15, 0, 18, 15, 19, 0),
    gsSP2Triangles(20, 16, 17, 0, 20, 17, 21, 0),
    gsSP2Triangles(22, 18, 19, 0, 22, 19, 23, 0),
    gsSP2Triangles(24, 20, 21, 0, 24, 21, 25, 0),
    gsSP2Triangles(26, 8, 5, 0, 26, 5, 27, 0),
    gsSPEndDisplayList(),
};
