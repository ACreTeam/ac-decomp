#include "libforest/gbi_extensions.h"
#include "PR/gbi.h"
#include "evw_anime.h"
#include "c_keyframe.h"


Vtx obj_zassou_b_v[] = { 
#include "assets/obj_zassou_b_v.inc"
};

Gfx obj_zassou_bT_gfx_model[] = { 
gsSPVertex(obj_zassou_b_v, 4, 0),
gsSPNTrianglesInit_5b(2, 0, 1, 2, 0, 2, 3, 0, 0, 0),
gsSPEndDisplayList()
};

