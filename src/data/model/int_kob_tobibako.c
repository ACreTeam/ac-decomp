#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u16 int_kob_tobibako_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/int_kob_tobibako_pal.inc"
};

u8 int_kob_tobibako_zengo_tex[] = {
#include "assets/int_kob_tobibako_zengo_tex.inc"
};

u8 int_kob_tobibako_sayu_tex[] = {
#include "assets/int_kob_tobibako_sayu_tex.inc"
};

u8 int_kob_tobibako_ue_tex[] = {
#include "assets/int_kob_tobibako_ue_tex.inc"
};

Vtx int_kob_tobibako_v[] = {
#include "assets/int_kob_tobibako_v.inc"
};

Gfx int_kob_tobibako_on_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_AA_ZB_TEX_EDGE2),
    gsDPSetCombineLERP(TEXEL0, 0, SHADE, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, COMBINED, 0, 0, 0, 0, COMBINED),
    gsDPLoadTLUT_Dolphin(15, 16, 1, int_kob_tobibako_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 16, int_kob_tobibako_ue_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_MIRROR, 0, 0),
    gsDPSetPrimColor(0, 128, 255, 255, 255, 255),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(int_kob_tobibako_v, 30, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_kob_tobibako_sayu_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(12, 4, 5, 6, 4, 6, 7, 4, 7, 8),
    gsSPNTriangles_5b(9, 10, 11, 9, 11, 12, 9, 12, 13, 14, 11, 15),
    gsSPNTriangles_5b(11, 10, 15, 14, 12, 11, 16, 8, 17, 16, 4, 8),
    gsSPNTriangles_5b(8, 7, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 48, int_kob_tobibako_zengo_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPNTrianglesInit_5b(8, 18, 19, 20, 18, 20, 21, 22, 23, 24),
    gsSPNTriangles_5b(22, 24, 25, 26, 22, 25, 26, 25, 27, 28, 18, 21),
    gsSPNTriangles_5b(28, 21, 29, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
