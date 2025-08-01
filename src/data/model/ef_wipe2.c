#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern Vtx ef_wipe2_v[];
extern u8 ef_wape_tex[];
Vtx ef_wipe2_v[] = {
#include "assets/ef_wipe2_v.inc"
};

Gfx ef_wipe2_modelT[] = {
    gsSPTexture(0, 0, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineLERP(0, 0, 0, PRIMITIVE, 0, 0, 0, TEXEL0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED),
    gsDPSetPrimColor(0, 255, 0, 0, 0, 255),
    gsDPSetCycleType(G_CYC_2CYCLE),
    gsDPSetRenderMode(G_RM_PASS, G_RM_CLD_SURF2),
    gsDPSetTextureImage_Dolphin(G_IM_FMT_I, G_IM_SIZ_4b, 16, 8, ef_wape_tex),
    gsDPSetTile_Dolphin(G_DOLPHIN_TLUT_DEFAULT_MODE, 0, 15, GX_CLAMP, GX_CLAMP, 0, 0),
    gsSPDisplayList(anime_2_txt),
    gsSPLoadGeometryMode(G_SHADE | G_SHADING_SMOOTH | G_DECAL_LEQUAL),
    gsSPVertex(ef_wipe2_v, 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 3, 0, 2, 0, 4, 1),
    gsSPNTriangles_5b(0, 5, 4, 6, 0, 3, 7, 0, 8, 0, 6, 9),
    gsSPNTriangles_5b(0, 9, 10, 8, 0, 11, 0, 10, 11, 0, 12, 13),
    gsSPNTriangles_5b(14, 0, 13, 0, 15, 12, 0, 7, 15, 16, 0, 14),
    gsSPNTriangles_5b(17, 0, 18, 0, 19, 20, 0, 20, 21, 18, 0, 22),
    gsSPNTriangles_5b(0, 21, 22, 0, 23, 24, 25, 0, 24, 0, 26, 23),
    gsSPNTriangles_5b(0, 27, 26, 25, 19, 0, 27, 0, 28, 0, 29, 30),
    gsSPNTriangles_5b(0, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&ef_wipe2_v[32], 32, 0),
    gsSPNTrianglesInit_5b(28, 0, 1, 2, 1, 3, 2, 1, 4, 5),
    gsSPNTriangles_5b(6, 1, 5, 1, 7, 4, 1, 8, 7, 9, 1, 6),
    gsSPNTriangles_5b(10, 11, 1, 1, 9, 12, 1, 12, 13, 10, 1, 14),
    gsSPNTriangles_5b(1, 13, 14, 1, 15, 16, 17, 1, 16, 1, 18, 15),
    gsSPNTriangles_5b(1, 11, 18, 19, 1, 17, 20, 1, 21, 1, 22, 23),
    gsSPNTriangles_5b(1, 23, 24, 21, 1, 25, 1, 24, 25, 1, 26, 27),
    gsSPNTriangles_5b(28, 1, 27, 1, 29, 26, 1, 30, 29, 22, 1, 28),
    gsSPNTriangles_5b(30, 1, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPVertex(&ef_wipe2_v[64], 6, 0),
    gsSPNTrianglesInit_5b(4, 0, 1, 2, 0, 2, 3, 4, 0, 5),
    gsSPNTriangles_5b(0, 3, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    gsSPEndDisplayList(),
};
