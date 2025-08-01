#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

static u16 int_kon_isi01_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/int_kon_isi01/int_kon_isi01_pal.inc"
};

u8 int_kon_isi01_mae_tex[] = {
#include "assets/int_kon_isi01_mae_tex.inc"
};

u8 int_kon_isi01_teppen_tex[] = {
#include "assets/int_kon_isi01_teppen_tex.inc"
};

u8 int_kon_isi01_yoko_tex[] = {
#include "assets/int_kon_isi01_yoko_tex.inc"
};

Vtx int_kon_isi01_v[] = {
#include "assets/int_kon_isi01_v.inc"
};

Gfx int_kon_isi01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kon_isi01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_isi01_yoko_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_REPEAT, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kon_isi01_v, 28, 0),
    gsSPNTrianglesInit_5b(14, 0, 1, 2, 1, 3, 2, 0, 4, 1),
    gsSPNTriangles_5b(4, 5, 1, 4, 6, 5, 5, 7, 1, 7, 3, 1),
    gsSPNTriangles_5b(8, 9, 10, 8, 10, 11, 11, 12, 13, 8, 11, 13),
    gsSPNTriangles_5b(8, 13, 0, 2, 9, 8, 2, 8, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_kon_isi01_teppen_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(5, 14, 15, 16, 17, 15, 14, 18, 15, 17),
    gsSPNTriangles_5b(19, 15, 18, 16, 15, 19, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_kon_isi01_mae_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(7, 20, 21, 22, 21, 23, 22, 24, 22, 23),
    gsSPNTriangles_5b(24, 25, 22, 25, 26, 22, 26, 27, 22, 27, 20, 22),
    gsSPEndDisplayList(),
};
