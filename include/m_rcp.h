#ifndef M_RCP_H
#define M_RCP_H

#include "types.h"
#include "PR/mbi.h"
#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

extern Gfx* gfx_gSPTextureRectangle1(Gfx* gfx, u32 ulx, u32 uly, u32 lrx, u32 lry, int tile, int s, int t, int dsdx, int dtdy);
extern Gfx* gfx_gDPFillRectangle1(Gfx* gfx, u32 ulx, u32 uly, u32 lrx, u32 lry);
extern Gfx* gfx_gDPFillRectangleF(Gfx* gfx, u32 ulx, u32 uly, u32 lrx, u32 lry);
extern Gfx* gfx_tex_scroll2(Gfx** gfxpp, u32 x, u32 y, int width, int height);
extern void DisplayList_initialize(GRAPH* graph, u32 clear_r, u32 clear_g, u32 clear_b, GAME* game);
extern void fade_black_draw(Gfx** gfxpp, u32 alpha);
extern void rect_moji(GRAPH* graph);

#ifdef __cplusplus
}
#endif

#endif
