#include "bootdata.h"
#include "libforest/gbi_extensions.h"

static u8 gam_win_moji3_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/bootdata/gam_win_moji3_tex_1.inc"
};

static u8 gam_win_moji5_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/bootdata/gam_win_moji5_tex.inc"
};

static Vtx gam_win3_v[] = {
#include "assets/bootdata/gam_win3_v.inc"
};

Gfx gam_win3_moji_model[] = {
  gsSPTexture(0, 0, 0, 0, G_ON),
  gsDPSetCombineMode(G_CC_BLENDPRIMDECALA, G_CC_PASS2),
  gsDPSetPrimColor(0, 255, 50, 50, 60, 255),
  gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
  gsDPLoadTextureBlock_4b_Dolphin(gam_win_moji5_tex, G_IM_FMT_I, 112, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_SHADING_SMOOTH),
  gsSPVertex(&gam_win3_v[0], 8, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsDPLoadTextureBlock_4b_Dolphin(gam_win_moji3_tex, G_IM_FMT_I, 160, 16, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    4, 5, 6, // tri0
    5, 7, 6, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};
