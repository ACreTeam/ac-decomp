#ifndef M_RCP_H
#define M_RCP_H

#include "types.h"
#include "PR/mbi.h"

#ifdef __cplusplus
extern "C" {
#endif

extern Gfx* gfx_gSPTextureRectangle1(Gfx* gfx, u32 ulx, u32 uly, u32 lrx, u32 lry, int tile, int s, int t, int dsdx, int dtdy);
extern Gfx* gfx_gDPFillRectangle1(Gfx* gfx, u32 ulx, u32 uly, u32 lrx, u32 lry);
extern Gfx* gfx_gDPFillRectangleF(Gfx* gfx, u32 ulx, u32 uly, u32 lrx, u32 lry);
extern Gfx* gfx_tex_scroll2(Gfx** gfxpp, u32 x, u32 y, s32 width, s32 height);


#ifdef __cplusplus
}
#endif

#endif
