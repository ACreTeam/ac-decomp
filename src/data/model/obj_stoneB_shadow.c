#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"


Vtx obj_stoneB_shadow_v[] = { 
#include "assets/obj_stoneB_shadow_v.inc"
};

Gfx obj_stoneB_shadowT_gfx_model[] = { 
gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 7, 6, 8, 7, 8, 9, 9, 8, 1),
gsSPNTriangles_5b(9, 1, 0, 10, 11, 5, 10, 5, 4, 0, 0, 0),
gsSPEndDisplayList()
};

