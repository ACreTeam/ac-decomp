#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"
#include "ac_npc.h"
#include "ef_effect_control.h"

extern u8 elf_layA0_txt[];
Vtx point_light_v[] = {
#include "assets/point_light_v.inc"
};

Gfx point_light_init_model[] = {
    gsDPSetTextureImage(G_IM_FMT_I, G_IM_SIZ_16b, 1, elf_layA0_txt),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_16b, 0, 0, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
    gsDPLoadSync(),
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0, 1023, 512),
    gsDPPipeSync(),
    gsDPSetTile(G_IM_FMT_I, G_IM_SIZ_8b, 4, 0, G_TX_RENDERTILE, 0, G_TX_MIRROR | G_TX_WRAP, 6, G_TX_NOLOD,
                G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD),
    gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 124, 252),
    gsSPEndDisplayList(),
};

Gfx point_light_model[] = {
    gsSPMatrix(117440512, G_MTX_NOPUSH | G_MTX_MUL | G_MTX_MODELVIEW),
    gsSPVertex(point_light_v, 4, 0),
    gsSP2Triangles(2, 1, 0, 0, 3, 2, 0, 0),
    gsSPEndDisplayList(),
};

u8 elf_layA0_txt[] = {
#include "assets/elf_layA0_txt.inc"
};
