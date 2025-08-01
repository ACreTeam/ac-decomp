#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx int_sum_clchair02_v[];
u16 int_sum_clchair02_pal01_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/int_sum_clchair02_pal01_pal.inc"
};

u8 int_sum_clchair02_back[] = {
#include "assets/int_sum_clchair02_back.inc"
};

u8 int_sum_clchair02_seat[] = {
#include "assets/int_sum_clchair02_seat.inc"
};

u8 int_sum_clchair02_foot[] = {
#include "assets/int_sum_clchair02_foot.inc"
};

u8 int_sum_clchair02_foot2[] = {
#include "assets/int_sum_clchair02_foot2.inc"
};

u8 int_sum_clchair02_foot3[] = {
#include "assets/int_sum_clchair02_foot3.inc"
};

u8 int_sum_clchair02_hiji[] = {
#include "assets/int_sum_clchair02_hiji.inc"
};

u8 int_sum_clchair02_hiji2[] = {
#include "assets/int_sum_clchair02_hiji2.inc"
};

Vtx int_sum_clchair02_v[] = {
#include "assets/int_sum_clchair02_v.inc"
};

Gfx int_sum_clcheir02_onT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_sum_clchair02_pal01_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 16, int_sum_clchair02_hiji2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_sum_clchair02_v, 28, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 3, 4, 5, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, int_sum_clchair02_hiji),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(2, 6, 7, 8, 9, 10, 11, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_clchair02_foot3),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 12, 13, 14, 14, 13, 15, 16, 17, 18),
    gsSPNTriangles_5b(18, 17, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_sum_clchair02_foot2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 26, 27, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_clchair02_foot),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPVertex(&int_sum_clchair02_v[28], 28, 0),
    gsSPNTrianglesInit_5b(8, 0, 1, 2, 3, 4, 2, 5, 6, 7),
    gsSPNTriangles_5b(5, 8, 9, 10, 11, 12, 13, 14, 12, 15, 16, 17),
    gsSPNTriangles_5b(15, 18, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_clchair02_seat),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPNTrianglesInit_5b(4, 20, 21, 22, 20, 22, 23, 24, 25, 26),
    gsSPNTriangles_5b(24, 27, 25, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, int_sum_clchair02_back),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(&int_sum_clchair02_v[56], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 1, 3, 2, 4, 2, 5),
    gsSPNTriangles_5b(2, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
