#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

u8 sen_qitem_kage_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/sen_qitem_kage_tex.inc"
};

static u8 sen_win_yaji2_tex[] = {
#include "assets/sen_qitem/sen_win_yaji2_tex.inc"
};

u8 sen_qitem_waku_tex[] = {
#include "assets/sen_qitem_waku_tex.inc"
};

static u8 sen_itemw_yaji2_tex[] = {
#include "assets/sen_qitem/sen_itemw_yaji2_tex.inc"
};

u8 sen_qitem_yajirushi[] = {
#include "assets/sen_qitem_yajirushi.inc"
};

u8 sen_qitem_yajirushi2[] = {
#include "assets/sen_qitem_yajirushi2.inc"
};

static u8 sen_itemw_yaji_tex[] = {
#include "assets/sen_qitem/sen_itemw_yaji_tex.inc"
};

static u8 sen_item2_yaji_tex[] = {
#include "assets/sen_qitem/sen_item2_yaji_tex.inc"
};

Vtx sen_qitem_v[] = {
#include "assets/sen_qitem_v.inc"
};

Gfx sen_qitem_kage_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, PRIMITIVE, PRIMITIVE, 0, TEXEL0, 0),
    gsDPSetPrimColor(0, 255, 30, 20, 20, 160),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 64, 32, sen_qitem_kage_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(sen_qitem_v, 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_qitem_yajirushi3_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 210, 165, 60, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, sen_itemw_yaji_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_qitem_v[4], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_qitem_yajirushi5_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 215, 165, 60, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, sen_qitem_yajirushi),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_qitem_v[8], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 3, 0, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_qitem_wakuT_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 255, 245, 140, 255),
    gsDPSetEnvColor(215, 165, 60, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 64, 32, sen_qitem_waku_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_qitem_v[12], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_qitem_yajirushiT_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 16, sen_item2_yaji_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_qitem_v[16], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_qitem_yajirushi2T_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 215, 165, 60, 255),
    gsDPSetEnvColor(30, 20, 20, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, sen_win_yaji2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_qitem_v[20], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_qitem_yajirushi4T_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 215, 165, 60, 255),
    gsDPSetEnvColor(30, 20, 20, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, sen_itemw_yaji2_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_qitem_v[24], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};

Gfx sen_qitem_yajirushi6T_model[] = {
    gsDPPipeSync(),
    gsDPSetCombineLERP(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 0, 0, 0, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0,
                       ENVIRONMENT, 0, 0, 0, TEXEL0),
    gsDPSetPrimColor(0, 255, 215, 165, 60, 255),
    gsDPSetEnvColor(30, 20, 20, 255),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 16, 16, sen_qitem_yajirushi2),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&sen_qitem_v[28], 4, 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 3, 2, 0),
    gsSPEndDisplayList(),
};
