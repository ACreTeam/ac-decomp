#include "bootdata.h"
#include "libforest/gbi_extensions.h"

#include "assets/bootdata/nintendo_376x104.inc"

Vtx logo_nin_v[] = {
  #include "assets/bootdata/logo_nin_v.inc"
};

Gfx logo_ninT_model[] = {
  gsDPLoadTextureBlock_4b_Dolphin(nintendo_376x104, G_IM_FMT_I, 376, 104, 15, GX_CLAMP, GX_CLAMP, 0, 0),
  gsSPVertex(&logo_nin_v[0], 4, 0),
  gsSPNTrianglesInit_5b(
    2, // tri count
    0, 1, 2, // tri0
    1, 3, 2, // tri1
    0, 0, 0 // tri2
  ),
  gsSPEndDisplayList(),
};
