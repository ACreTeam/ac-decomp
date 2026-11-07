#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"

u8 log_win_logo[] ATTRIBUTE_ALIGN(32) = {
#include "assets/pal_data/dataobject/log_win_logo.inc"
};

u8 log_win_nintendo[] ATTRIBUTE_ALIGN(32) = {
#include "assets/pal_data/dataobject/log_win_nintendo.inc"
};

Vtx logo_replace_v[] = {
#include "assets/pal_data/dataobject/logo_replace_v.inc"
};

Gfx nintendoT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 256, 16, log_win_nintendo),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(logo_replace_v, 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};

Gfx push_startT_model[] = {
    gsDPSetTextureImage_Dolphin(G_IM_FMT_IA, G_IM_SIZ_8b, 128, 16, log_win_logo),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 0, GX_MIRROR, GX_MIRROR, 0, 0),
    gsSPVertex(&logo_replace_v[4], 4, 0),
    gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
    gsSPEndDisplayList(),
};
