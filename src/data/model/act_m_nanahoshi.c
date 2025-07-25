#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

static u16 act_m_nanahoshi_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/act_m_nanahoshi/act_m_nanahoshi_pal.inc"
};

static u8 act_m_nanahoshi[] = {
#include "assets/act_m_nanahoshi/act_m_nanahoshi.inc"
};

static Vtx act_m_nanahoshi_v[] = {
#include "assets/act_m_nanahoshi/act_m_nanahoshi_v.inc"
};

Gfx act_m_nanahoshi1T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_nanahoshi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_m_nanahoshi),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_m_nanahoshi_v, 14, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 3, 4, 5, 6, 3, 5),
    gsSPNTriangles_5b(2, 1, 7, 6, 5, 8, 9, 6, 8, 7, 1, 10),
    gsSPNTriangles_5b(9, 8, 7, 11, 9, 7, 4, 3, 12, 4, 12, 13),
    gsSPNTriangles_5b(1, 0, 4, 10, 1, 4, 11, 7, 13, 11, 13, 12),
    gsSPEndDisplayList(),
};

Gfx act_m_nanahoshi2T_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_nanahoshi_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 16, 32, act_m_nanahoshi),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(&act_m_nanahoshi_v[14], 15, 0),
    gsSPNTrianglesInit_5b(15, 0, 1, 2, 0, 3, 1, 4, 5, 6),
    gsSPNTriangles_5b(5, 7, 6, 8, 2, 1, 8, 9, 2, 0, 10, 3),
    gsSPNTriangles_5b(10, 11, 3, 12, 5, 4, 10, 13, 11, 13, 7, 11),
    gsSPNTriangles_5b(14, 5, 12, 13, 9, 7, 9, 8, 7, 7, 5, 14),
    gsSPEndDisplayList(),
};
