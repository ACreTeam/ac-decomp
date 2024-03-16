#ifndef M_RCP_H
#define M_RCP_H

#include "types.h"
#include "PR/mbi.h"
#include "libforest/gbi_extensions.h"
#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void gfx_set_fog_position(Gfx** gfxp, int near, int far);
extern Gfx* gfx_set_fog_nosync(Gfx* gfx, int r, int g, int b, int a, int near, int far);
extern void texture_z_light_prim_xlu_disp(GRAPH* graph);
extern void _texture_z_light_fog_prim_bg(GRAPH* graph);
extern void _texture_z_light_fog_prim(GRAPH* graph);
extern void _texture_z_light_fog_prim_shadow(GRAPH* graph);
extern void _texture_z_light_fog_prim_xlu(GRAPH* graph);
extern void _texture_z_light_fog_prim_light(GRAPH* graph);
extern void _texture_z_light_fog_prim_npc(GRAPH* graph);
extern Gfx* texture_z_light_fog_prim_bb_pal_opa(Gfx* gfx);
extern Gfx* texture_z_light_fog_prim_bb_pal_xlu(Gfx* gfx);
extern Gfx* texture_z_fog_lod_alpha_shadow(Gfx* gfx);
extern Gfx* gfx_rect_moji(Gfx* gfx);
extern void rect_moji(GRAPH* graph);
extern void polygon_z_light_prim(GRAPH* graph);
extern void softsprite_prim(GRAPH* graph);
extern Gfx* gfx_softsprite_prim_xlu(Gfx* gfx);
extern Gfx* gfx_tex_scroll2(Gfx** gfxpp, int x, int y, int width, int height);
extern Gfx* tex_scroll2(GRAPH* graph, u32 x, u32 y, int width, int height);
extern Gfx* tex_scroll2_dolphin(GRAPH* graph, int x, int y, int width, int height);
extern Gfx* two_tex_scroll(GRAPH* graph, int tile1, int x1, int y1, int width1, int height1, int tile2, int x2, int y2,
                           int width2, int height2);
extern Gfx* two_tex_scroll_dolphin(GRAPH* graph, int tile1, int x1, int y1, int width1, int height1, int tile2, int x2,
                                   int y2, int width2, int height2);
extern void DisplayList_initialize(GRAPH* graph, u8 clear_r, u8 clear_g, u8 clear_b, GAME* game);
extern void fade_rgba8888_draw(Gfx** gfxp, u32 color);
extern void fade_black_draw(Gfx** gfx, u32 color);
extern Gfx* gfx_gDPFillRectangle1(Gfx* gfx, u32 ulx, u32 uly, u32 lrx, u32 lry);
extern Gfx* gfx_gDPFillRectangleF(Gfx* gfx, u32 ulx, u32 uly, u32 lrx, u32 lry);
extern Gfx* gfx_gSPTextureRectangle1(Gfx* gfx, int xl, int yl, int xh, int yh, int tile, int s, int t, int dsdx,
                                     int dtdy);
extern Gfx* gfx_gSPScisTextureRectangle1(Gfx* gfx, int xl, int yl, int xh, int yh, int tile, int s, int t, int dsdx,
                                         int dtdy);

extern Gfx RSP_RDP_clear_data[];
extern int fbdemo_mode;

#ifdef __cplusplus
}
#endif

#endif
