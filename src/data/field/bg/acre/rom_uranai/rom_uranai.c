#include "libforest/gbi_extensions.h"

static u16 rom_uranai_floor_tex_pal[] = {
#include "assets/field/bg/rom_uranai_floor_tex_pal.inc"
};

static u16 rom_uranai_wall_tex_pal[] = {
#include "assets/field/bg/rom_uranai_wall_tex_pal.inc"
};

static u16 rom_uranai_table_tex_pal[] = {
#include "assets/field/bg/rom_uranai_table_tex_pal.inc"
};

static u16 rom_uranai_tubo_tex_pal[] = {
#include "assets/field/bg/rom_uranai_tubo_tex_pal.inc"
};

static u16 rom_uranai_stand_tex_pal[] = {
#include "assets/field/bg/rom_uranai_stand_tex_pal.inc"
};

static u16 rom_uranai_tex_nuno_pal[] = {
#include "assets/field/bg/rom_uranai_tex_nuno_pal.inc"
};

static u16 rom_uranai_tex_bace_pal[] = {
#include "assets/field/bg/rom_uranai_tex_bace_pal.inc"
};

static u16 rom_uranai_card_tex_pal[] = {
#include "assets/field/bg/rom_uranai_card_tex_pal.inc"
};

static u8 rom_uranai_floor_tex[] = {
#include "assets/field/bg/rom_uranai_floor_tex.inc"
};

static u8 rom_uranai_wall01_tex[] = {
#include "assets/field/bg/rom_uranai_wall01_tex.inc"
};

static u8 rom_uranai_wall02_tex[] = {
#include "assets/field/bg/rom_uranai_wall02_tex.inc"
};

static u8 rom_uranai_wall03_tex[] = {
#include "assets/field/bg/rom_uranai_wall03_tex.inc"
};

static u8 rom_uranai_table01_tex[] = {
#include "assets/field/bg/rom_uranai_table01_tex.inc"
};

static u8 rom_uranai_table02_tex[] = {
#include "assets/field/bg/rom_uranai_table02_tex.inc"
};

static u8 rom_uranai_tubo_tex[] = {
#include "assets/field/bg/rom_uranai_tubo_tex.inc"
};

static u8 rom_uranai_shadow01_tex[] = {
#include "assets/field/bg/rom_uranai_shadow01_tex.inc"
};

static u8 rom_uranai_vell_tex[] = {
#include "assets/field/bg/rom_uranai_vell_tex.inc"
};

static u8 rom_uranai_vell02_tex[] = {
#include "assets/field/bg/rom_uranai_vell02_tex.inc"
};

static u8 rom_uranai_stand01_tex[] = {
#include "assets/field/bg/rom_uranai_stand01_tex.inc"
};

static u8 rom_uranai_nuno01_tex[] = {
#include "assets/field/bg/rom_uranai_nuno01_tex.inc"
};

static u8 rom_uranai_nuno02_tex[] = {
#include "assets/field/bg/rom_uranai_nuno02_tex.inc"
};

static u8 rom_uranai_bace_tex[] = {
#include "assets/field/bg/rom_uranai_bace_tex.inc"
};

static u8 rom_uranai_card01_tex[] = {
#include "assets/field/bg/rom_uranai_card01_tex.inc"
};

static u8 rom_uranai_shadow02_tex[] = {
#include "assets/field/bg/rom_uranai_shadow02_tex.inc"
};

static u8 rom_uranai_card02_tex[] = {
#include "assets/field/bg/rom_uranai_card02_tex.inc"
};

static u8 rom_uranai_cris02_tex[] = {
#include "assets/field/bg/rom_uranai_cris02_tex.inc"
};

static u8 rom_uranai_cris01_tex_rgb_ia8[] = {
#include "assets/field/bg/rom_uranai_cris01_tex_rgb_ia8.inc"
};

static u8 rom_uranai_hi02_tex_rgb_i4[] = {
#include "assets/field/bg/rom_uranai_hi02_tex_rgb_i4.inc"
};

static u8 rom_uranai_hi03_tex_rgb_i4[] = {
#include "assets/field/bg/rom_uranai_hi03_tex_rgb_i4.inc"
};

static Vtx rom_uranai_v[] = {
#include "assets/field/bg/rom_uranai_v.inc"
};

extern Gfx rom_uranai_modelT[] = {
    gsSPTexture(65535, 65535, 0, 0, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 150, 20, 0, 30, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPLoadTextureBlock_4b(rom_uranai_shadow02_tex, G_IM_FMT_I, 16, 32, 15, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_uranai_v[224], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsDPPipeSync(),
    gsDPSetPrimColor(0, 120, 10, 0, 30, 255),
    gsDPPipeSync(),
    gsDPLoadTextureBlock_4b(rom_uranai_shadow01_tex, G_IM_FMT_I, 16, 32, 15, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[232], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0, 0,
                       COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 80),
    gsDPSetEnvColor(0x64, 0xFF, 0x00, 0xFF),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPPipeSync(),
    gsDPLoadTextureBlock_4b(rom_uranai_vell02_tex, G_IM_FMT_I, 32, 64, 15, G_TX_MIRROR | G_TX_CLAMP,
                            G_TX_MIRROR | G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[240], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsDPPipeSync(),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 100),
    gsDPSetEnvColor(0xFF, 0x00, 0x00, 0xFF),
    gsDPPipeSync(),
    gsDPLoadTextureBlock_4b(rom_uranai_vell_tex, G_IM_FMT_I, 32, 64, 15, G_TX_MIRROR | G_TX_CLAMP,
                            G_TX_MIRROR | G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[248], 24, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(2, 4, 5, 0, 2, 5, 3, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 7, 5, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsSP2Triangles(10, 1, 0, 0, 10, 0, 11, 0),
    gsSP2Triangles(12, 13, 14, 0, 12, 14, 15, 0),
    gsSP2Triangles(14, 16, 17, 0, 14, 17, 15, 0),
    gsSP2Triangles(16, 18, 19, 0, 16, 19, 17, 0),
    gsSP2Triangles(19, 18, 20, 0, 19, 20, 21, 0),
    gsSP2Triangles(20, 22, 23, 0, 20, 23, 21, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 120, 10, 0, 30, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_XLU_DECAL2),
    gsDPPipeSync(),
    gsDPLoadTextureBlock_4b(rom_uranai_shadow01_tex, G_IM_FMT_I, 16, 32, 15, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_CLAMP, 4, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[272], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, ENVIRONMENT, COMBINED,
                       ENVIRONMENT, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 0, 255, 150, 0, 255),
    gsDPSetEnvColor(0xFF, 0x96, 0x00, 0xFF),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTextureBlock_4b(rom_uranai_hi02_tex_rgb_i4, G_IM_FMT_I, 32, 32, 15, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsDPLoadMultiBlock_4b(rom_uranai_hi03_tex_rgb_i4, 0x0040, 1, G_IM_FMT_I, 32, 32, 15, G_TX_NOMIRROR | G_TX_WRAP,
                          G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPDisplayList(0x09000000),
    gsSPVertex(&rom_uranai_v[280], 8, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSPTexture(4000, 4000, 0, 0, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, TEXEL1, TEXEL0, TEXEL1, TEXEL0, 0, TEXEL1, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 128, 200, 255, 255, 120),
    gsDPLoadTextureBlock(rom_uranai_cris01_tex_rgb_ia8, G_IM_FMT_IA, G_IM_SIZ_8b, 32, 32, 0, G_TX_MIRROR | G_TX_WRAP,
                         G_TX_MIRROR | G_TX_WRAP, 5, 5, 1, 1),
    gsDPLoadMultiBlock(rom_uranai_cris02_tex, 0x0080, 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, 2, 2),
    gsSPDisplayList(0x0A000000),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_SHADING_SMOOTH),
    gsSPVertex(&rom_uranai_v[288], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(0, 4, 3, 0, 3, 5, 6, 0),
    gsSP2Triangles(3, 4, 5, 0, 5, 7, 6, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 11, 9, 0),
    gsSP2Triangles(9, 12, 10, 0, 6, 13, 8, 0),
    gsSP2Triangles(6, 7, 13, 0, 13, 11, 8, 0),
    gsSP2Triangles(14, 10, 12, 0, 14, 15, 10, 0),
    gsSP2Triangles(14, 16, 15, 0, 17, 15, 16, 0),
    gsSP2Triangles(17, 1, 15, 0, 17, 2, 1, 0),
    gsSP2Triangles(3, 18, 1, 0, 19, 3, 6, 0),
    gsSP2Triangles(20, 6, 8, 0, 21, 8, 10, 0),
    gsSP2Triangles(15, 22, 10, 0, 1, 23, 15, 0),
    gsSP2Triangles(19, 6, 20, 0, 18, 3, 19, 0),
    gsSP2Triangles(1, 18, 23, 0, 10, 22, 21, 0),
    gsSP2Triangles(20, 8, 21, 0, 15, 23, 22, 0),
    gsSP2Triangles(24, 19, 20, 0, 24, 18, 19, 0),
    gsSP2Triangles(18, 24, 23, 0, 23, 24, 22, 0),
    gsSP2Triangles(24, 20, 21, 0, 22, 24, 21, 0),
    gsSP2Triangles(25, 12, 9, 0, 25, 9, 26, 0),
    gsSP2Triangles(11, 27, 26, 0, 11, 26, 9, 0),
    gsSP2Triangles(13, 28, 27, 0, 13, 27, 11, 0),
    gsSP2Triangles(7, 29, 28, 0, 7, 28, 13, 0),
    gsSP2Triangles(5, 30, 29, 0, 5, 29, 7, 0),
    gsSP2Triangles(4, 31, 30, 0, 4, 30, 5, 0),
    gsSPVertex(&rom_uranai_v[320], 14, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 7, 5, 0),
    gsSP2Triangles(6, 8, 9, 0, 6, 9, 7, 0),
    gsSP2Triangles(8, 10, 11, 0, 8, 11, 9, 0),
    gsSP2Triangles(10, 12, 13, 0, 10, 13, 11, 0),
    gsSPEndDisplayList(),
};

extern Gfx rom_uranai_model[] = {
    gsSPTexture(65535, 65535, 0, 0, G_ON),
    gsDPPipeSync(),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPPipeSync(),
    gsDPSetTextureLUT(G_TT_RGBA16),
    gsDPLoadTLUT_pal16(15, rom_uranai_floor_tex_pal),
    gsDPLoadTextureBlock_4b(rom_uranai_floor_tex, G_IM_FMT_CI, 64, 64, 15, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_WRAP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
    gsSPVertex(&rom_uranai_v[0], 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(0, 4, 1, 0, 4, 3, 1, 0),
    gsSP2Triangles(5, 3, 6, 0, 3, 4, 6, 0),
    gsSP2Triangles(4, 7, 6, 0, 8, 9, 10, 0),
    gsSP2Triangles(9, 0, 10, 0, 0, 11, 10, 0),
    gsSP2Triangles(12, 0, 13, 0, 0, 2, 13, 0),
    gsSP2Triangles(2, 14, 13, 0, 15, 2, 16, 0),
    gsSP2Triangles(2, 3, 16, 0, 3, 17, 16, 0),
    gsSP2Triangles(2, 15, 14, 0, 8, 7, 4, 0),
    gsSP2Triangles(3, 5, 17, 0, 11, 0, 12, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, rom_uranai_wall_tex_pal),
    gsDPLoadTextureBlock_4b(rom_uranai_wall01_tex, G_IM_FMT_CI, 48, 64, 15, G_TX_MIRROR | G_TX_CLAMP,
                            G_TX_MIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[18], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(3, 4, 2, 0, 5, 6, 7, 0),
    gsSP2Triangles(6, 8, 7, 0, 8, 9, 7, 0),
    gsSP2Triangles(10, 11, 12, 0, 10, 13, 11, 0),
    gsSP2Triangles(13, 14, 11, 0, 15, 16, 17, 0),
    gsSP2Triangles(16, 18, 17, 0, 16, 19, 18, 0),
    gsSP2Triangles(20, 21, 22, 0, 20, 10, 21, 0),
    gsSP2Triangles(10, 23, 21, 0, 24, 25, 26, 0),
    gsSP2Triangles(24, 27, 25, 0, 25, 28, 26, 0),
    gsSP1Triangle(29, 30, 31, 0),
    gsSPVertex(&rom_uranai_v[50], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 3, 1, 0),
    gsSP2Triangles(4, 5, 6, 0, 5, 7, 6, 0),
    gsSP2Triangles(7, 8, 6, 0, 9, 10, 11, 0),
    gsSP2Triangles(9, 12, 10, 0, 12, 13, 10, 0),
    gsSP2Triangles(14, 15, 16, 0, 14, 16, 17, 0),
    gsSP2Triangles(18, 19, 20, 0, 18, 20, 21, 0),
    gsSP2Triangles(9, 22, 23, 0, 9, 23, 24, 0),
    gsSP2Triangles(25, 26, 27, 0, 26, 28, 27, 0),
    gsSP2Triangles(28, 29, 27, 0, 30, 2, 31, 0),
    gsSP1Triangle(2, 1, 31, 0),
    gsSPVertex(&rom_uranai_v[82], 18, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 4, 5, 0),
    gsSP2Triangles(3, 5, 6, 0, 4, 7, 8, 0),
    gsSP2Triangles(4, 8, 5, 0, 8, 9, 5, 0),
    gsSP2Triangles(10, 11, 12, 0, 10, 12, 13, 0),
    gsSP2Triangles(10, 13, 14, 0, 11, 15, 16, 0),
    gsSP2Triangles(11, 16, 12, 0, 11, 17, 15, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, rom_uranai_wall_tex_pal),
    gsDPLoadTextureBlock_4b(rom_uranai_wall03_tex, G_IM_FMT_CI, 32, 64, 15, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[100], 6, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(4, 5, 1, 0, 4, 1, 0, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, rom_uranai_table_tex_pal),
    gsDPLoadTextureBlock_4b(rom_uranai_table01_tex, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[106], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, rom_uranai_tex_nuno_pal),
    gsDPLoadTextureBlock_4b(rom_uranai_nuno01_tex, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_WRAP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[110], 7, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(0, 4, 1, 0, 4, 5, 1, 0),
    gsSP2Triangles(5, 6, 1, 0, 6, 3, 1, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, rom_uranai_tex_bace_pal),
    gsDPLoadTextureBlock_4b(rom_uranai_bace_tex, G_IM_FMT_CI, 32, 32, 15, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[117], 5, 0),
    gsSP2Triangles(0, 1, 2, 0, 2, 3, 0, 0),
    gsSP1Triangle(0, 4, 1, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, rom_uranai_wall_tex_pal),
    gsDPLoadTextureBlock_4b(rom_uranai_wall02_tex, G_IM_FMT_CI, 32, 64, 15, G_TX_MIRROR | G_TX_CLAMP,
                            G_TX_MIRROR | G_TX_CLAMP, 5, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[122], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(2, 4, 5, 0, 2, 5, 3, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
    gsSP2Triangles(8, 10, 11, 0, 8, 11, 9, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, rom_uranai_table_tex_pal),
    gsDPLoadTextureBlock_4b(rom_uranai_table02_tex, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[134], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 9, 10, 0, 8, 10, 11, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, rom_uranai_card_tex_pal),
    gsDPLoadTextureBlock_4b(rom_uranai_card01_tex, G_IM_FMT_CI, 32, 32, 15, G_TX_MIRROR | G_TX_CLAMP,
                            G_TX_MIRROR | G_TX_CLAMP, 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[146], 14, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(4, 5, 6, 0, 4, 6, 7, 0),
    gsSP2Triangles(8, 2, 1, 0, 8, 1, 9, 0),
    gsSP2Triangles(10, 11, 12, 0, 10, 12, 13, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, rom_uranai_card_tex_pal),
    gsDPLoadTextureBlock_4b(rom_uranai_card02_tex, G_IM_FMT_CI, 48, 48, 15, G_TX_MIRROR | G_TX_CLAMP,
                            G_TX_MIRROR | G_TX_CLAMP, 6, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[160], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, rom_uranai_tubo_tex_pal),
    gsDPLoadTextureBlock_4b(rom_uranai_tubo_tex, G_IM_FMT_CI, 16, 64, 15, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_CLAMP, 4, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[164], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSP2Triangles(3, 4, 2, 0, 4, 5, 2, 0),
    gsSP2Triangles(6, 7, 8, 0, 7, 9, 8, 0),
    gsSP2Triangles(9, 10, 8, 0, 10, 11, 8, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, rom_uranai_stand_tex_pal),
    gsDPLoadTextureBlock_4b(rom_uranai_stand01_tex, G_IM_FMT_CI, 16, 64, 15, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_CLAMP, 4, 6, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[176], 12, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(1, 4, 5, 0, 1, 5, 2, 0),
    gsSP2Triangles(6, 7, 8, 0, 6, 8, 9, 0),
    gsSP2Triangles(7, 10, 11, 0, 7, 11, 8, 0),
    gsDPPipeSync(),
    gsDPLoadTLUT_pal16(15, rom_uranai_tex_nuno_pal),
    gsDPLoadTextureBlock_4b(rom_uranai_nuno02_tex, G_IM_FMT_CI, 16, 16, 15, G_TX_MIRROR | G_TX_WRAP,
                            G_TX_MIRROR | G_TX_CLAMP, 4, 4, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&rom_uranai_v[188], 32, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSP2Triangles(0, 3, 4, 0, 5, 1, 0, 0),
    gsSP2Triangles(5, 0, 6, 0, 5, 6, 7, 0),
    gsSP2Triangles(0, 8, 9, 0, 0, 9, 6, 0),
    gsSP2Triangles(4, 10, 8, 0, 4, 8, 0, 0),
    gsSP2Triangles(11, 12, 13, 0, 11, 13, 14, 0),
    gsSP2Triangles(13, 15, 16, 0, 13, 16, 14, 0),
    gsSP2Triangles(15, 17, 18, 0, 15, 18, 16, 0),
    gsSP2Triangles(19, 11, 14, 0, 19, 14, 16, 0),
    gsSP2Triangles(19, 16, 20, 0, 16, 18, 21, 0),
    gsSP2Triangles(16, 21, 20, 0, 22, 23, 24, 0),
    gsSP2Triangles(22, 24, 25, 0, 24, 26, 27, 0),
    gsSP2Triangles(24, 27, 25, 0, 26, 28, 29, 0),
    gsSP2Triangles(26, 29, 27, 0, 23, 30, 31, 0),
    gsSP2Triangles(23, 31, 26, 0, 23, 26, 24, 0),
    gsSPVertex(&rom_uranai_v[220], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList(),
};
