#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"

static u16 act_m_maimai_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/act_m_maimai/act_m_maimai_pal.inc"
};

static u8 act_m_maimai_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/act_m_maimai/act_m_maimai_tex.inc"
};

static Vtx act_m_maimai_v[] = {
#include "assets/act_m_maimai/act_m_maimai_v.inc"
};

Gfx act_m_maimaiT_model[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, ENVIRONMENT, 0, COMBINED, 0, SHADE, 0, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
    gsDPSetRenderMode(G_RM_FOG_SHADE_A, G_RM_ZB_XLU_SURF2),
    gsDPLoadTLUT_Dolphin(15, 16, 1, act_m_maimai_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, act_m_maimai_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_CLAMP, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPVertex(act_m_maimai_v, 16, 0),
    gsSPNTrianglesInit_5b(5, 0, 1, 2, 3, 4, 5, 3, 5, 6),
    gsSPNTriangles_5b(3, 7, 1, 8, 2, 1, 0, 0, 0, 0, 0, 0),
    gsSPLoadGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BACK | G_FOG | G_LIGHTING | G_SHADING_SMOOTH),
    gsSPNTrianglesInit_5b(6, 9, 10, 11, 9, 12, 10, 12, 13, 10),
    gsSPNTriangles_5b(13, 14, 10, 14, 15, 10, 15, 11, 10, 0, 0, 0),
    gsSPEndDisplayList(),
};
