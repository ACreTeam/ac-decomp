#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

static u16 ef_tamaire01_r_pal[] ATTRIBUTE_ALIGN(32) = {
#include "assets/ef_tamaire01_r/ef_tamaire01_r_pal.inc"
};

u8 tama01_r_tex[] = {
#include "assets/tama01_r_tex.inc"
};

static Vtx ef_tamaire01_r_v[] = {
#include "assets/ef_tamaire01_r/ef_tamaire01_r_v.inc"
};

Gfx tama01_model[] = {
    gsDPLoadTLUT_Dolphin(15, 16, 1, ef_tamaire01_r_pal),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_CI, G_IM_SIZ_4b, 32, 32, anime_1_txt),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(ef_tamaire01_r_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 1, 3, 2, 0, 0, 0),
    gsSPEndDisplayList(),
};

u8 tama01_w_tex[] ATTRIBUTE_ALIGN(32) = {
#include "assets/tama01_w_tex.inc"
};
