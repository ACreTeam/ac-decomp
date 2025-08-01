#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_sofe02_v[];
u16 int_sum_sofe02_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/int_sum_sofe02_pal.inc"
};

static u16 int_sum_sofe01_pal[] = {
#include "assets/int_sum_sofe02/int_sum_sofe01_pal.inc"
};

static u16 int_sofe01_pal[] = {
#include "assets/int_sum_sofe02/int_sofe01_pal.inc"
};

u8 int_sum_sofe02_back_txt[] = {
#include "assets/int_sum_sofe02_back_txt.inc"
};

static u8 int_sum_sofe01_facet_txt[] = {
#include "assets/int_sum_sofe02/int_sum_sofe01_facet_txt.inc"
};

static u8 int_sum_sofe01_side_txt[] = {
#include "assets/int_sum_sofe02/int_sum_sofe01_side_txt.inc"
};

static u8 int_sum_sofe01_backside_txt[] = {
#include "assets/int_sum_sofe02/int_sum_sofe01_backside_txt.inc"
};

u8 int_sum_sofe02_front_txt[] = {
#include "assets/int_sum_sofe02_front_txt.inc"
};

Vtx int_sum_sofe02_v[] = {
#include "assets/int_sum_sofe02_v.inc"
};

Gfx int_sum_sofe02_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_sofe02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_sofe02_front_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_sofe02_v, 17, 0),
    gsSPNTrianglesInit_5b(6, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 4, 8, 5, 8, 7, 5, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_sofe01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_sofe01_backside_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPNTrianglesInit_5b(4, 9, 10, 11, 10, 12, 11, 13, 14, 15),
    gsSPNTriangles_5b(13, 15, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sofe01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_sofe01_side_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&int_sum_sofe02_v[17], 16, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 11, 8, 10, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_sofe01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 48, int_sum_sofe01_facet_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_sofe02_v[33], 21, 0),
    gsSPNTrianglesInit_5b(12, 0, 1, 2, 1, 3, 2, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 9, 10, 8, 10, 11, 12, 13, 14),
    gsSPNTriangles_5b(12, 14, 15, 16, 17, 1, 17, 18, 1, 14, 19, 20),
    gsSPNTriangles_5b(14, 13, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_sofe02_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_sum_sofe02_back_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_sofe02_v[54], 17, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 3, 1, 1, 4, 5),
    gsSPNTriangles_5b(1, 5, 6, 1, 6, 7, 1, 7, 8, 1, 8, 9),
    gsSPNTriangles_5b(1, 9, 2, 1, 10, 11, 1, 11, 12, 1, 12, 13),
    gsSPNTriangles_5b(1, 13, 14, 1, 14, 4, 14, 15, 4, 14, 16, 15),
    gsSPEndDisplayList(),
};
