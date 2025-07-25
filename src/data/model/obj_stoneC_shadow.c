#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"


Vtx obj_stoneC_shadow_v[] = { 
#include "assets/obj_stoneC_shadow_v.inc"
};

Gfx obj_stoneC_shadowT_gfx_model[] = { 
gsSPNTrianglesInit_5b(10, 0, 1, 2, 0, 2, 3, 4, 5, 6),
gsSPNTriangles_5b(4, 6, 7, 8, 9, 5, 8, 5, 4, 3, 2, 9),
gsSPNTriangles_5b(3, 9, 8, 7, 6, 10, 7, 10, 11, 0, 0, 0),
gsSPEndDisplayList()
};

