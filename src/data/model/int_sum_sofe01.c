#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_sofe01_v[];
static u16 int_sum_sofe01_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/int_sum_sofe01/int_sum_sofe01_pal.inc"
};

static u16 int_sofe01_pal[] = {
#include "assets/int_sum_sofe01/int_sofe01_pal.inc"
};

u8 int_sum_sofe01_back_txt[] = {
#include "assets/int_sum_sofe01_back_txt.inc"
};

static u8 int_sum_sofe01_facet_txt[] = {
#include "assets/int_sum_sofe01/int_sum_sofe01_facet_txt.inc"
};

u8 int_sum_sofe01_front_txt[] = {
#include "assets/int_sum_sofe01_front_txt.inc"
};

static u8 int_sum_sofe01_side_txt[] = {
#include "assets/int_sum_sofe01/int_sum_sofe01_side_txt.inc"
};

static u8 int_sum_sofe01_backside_txt[] = {
#include "assets/int_sum_sofe01/int_sum_sofe01_backside_txt.inc"
};

Vtx int_sum_sofe01_v[] = {
#include "assets/int_sum_sofe01_v.inc"
};

Gfx int_sum_sofe01_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_sofe01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_sofe01_backside_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_sofe01_v, 24, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(4, 6, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sofe01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_sofe01_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(8, 8, 9, 10, 8, 11, 9, 12, 13, 14),
    gsSPNTriangles_5b(13, 15, 14, 16, 17, 18, 16, 18, 19, 20, 21, 22),
    gsSPNTriangles_5b(21, 23, 22, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_sofe01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_sofe01_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_sum_sofe01_v[24], 31, 0),
    gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 3, 1, 3, 4, 1),
    gsSPNTriangles_5b(4, 2, 1, 3, 5, 4, 5, 6, 4, 3, 7, 5),
    gsSPNTriangles_5b(7, 6, 5, 6, 8, 2, 8, 9, 2, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_sofe01_facet_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 10, 11, 12, 11, 13, 12, 14, 15, 16),
    gsSPNTriangles_5b(15, 17, 16, 18, 19, 11, 19, 20, 11, 21, 22, 23),
    gsSPNTriangles_5b(21, 23, 24, 25, 26, 27, 25, 27, 28, 27, 29, 30),
    gsSPNTriangles_5b(27, 26, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_sofe01_back_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_sofe01_v[55], 10, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 2, 3, 0, 4, 5),
    gsSPNTriangles_5b(0, 5, 1, 5, 6, 1, 6, 7, 1, 0, 3, 8),
    gsSPNTriangles_5b(3, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
