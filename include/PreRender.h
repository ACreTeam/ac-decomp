#ifndef PRERENDER_H
#define PRERENDER_H

#include "types.h"
#include <PR/gbi.h>
#include <PR/gs2dex.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BG2D_FLAGS_SAVE_OTHERMODE (1 << 0) /* Keep othermode settings */
#define BG2D_FLAGS_SAVE_COMBINER (1 << 1)  /* Keep combiner settings */
#define BG2D_FLAGS_AC_THRESHOLD (1 << 2)   /* Alpha compare uses threshold */
#define BG2D_FLAGS_LOAD_S2DEX2 (1 << 3)    /* Load S2DEX2 ucode */
#define BG2D_FLAGS_COPY (1 << 4)           /* Direct copy instead of combined */

typedef struct prerender_s {
    /* 0x00 */ u16 width;
    /* 0x02 */ u16 height;
    /* 0x04 */ u16 width_bak;
    /* 0x06 */ u16 height_bak;
    /* 0x08 */ u16 unk8;
    /* 0x0A */ u16 unkA;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 unkD;
    /* 0x0E */ u16 unkE; /* inferred */
    /* 0x10 */ u16* framebuffer;
    /* 0x14 */ u16* framebuffer_bak;
    /* 0x18 */ u8* cvg_bak;
    /* 0x1C */ u16* zbuffer;
    /* 0x20 */ u16* zbuffer_bak;
    /* 0x24 */ u16 ulx_bak;
    /* 0x26 */ u16 uly_bak;
    /* 0x28 */ u16 lrx_bak;
    /* 0x2A */ u16 lry_bak;
    /* 0x2C */ u16 ulx;
    /* 0x2E */ u16 uly;
    /* 0x30 */ u16 lrx;
    /* 0x32 */ u16 lry;
    /* 0x34 */ u8 _34[0x14];
} PreRender;

typedef struct {
    /* 0x00 */ void* timg;
    /* 0x04 */ void* tlut;
    /* 0x08 */ u16 width;
    /* 0x0A */ u16 height;
    /* 0x0C */ u8 fmt;
    /* 0x0D */ u8 siz;
    /* 0x0E */ u16 tt;
    /* 0x10 */ u16 tlutCount;
    /* 0x14 */ f32 x;
    /* 0x18 */ f32 y;
    /* 0x1C */ f32 xScale;
    /* 0x20 */ f32 yScale;
    /* 0x24 */ u32 flags;
} PreRenderBackground2DParams; // size = 0x28

extern void wallpaper_draw1(PreRenderBackground2DParams* bg2D, Gfx** gfxp);
extern void wallpaper_draw(Gfx** const gfxp, u16* const timg, u16* const tlut, const u16 width, const u16 height,
                           const u8 fmt, const u8 siz, const u16 tt, const u16 tlutCount, f32 x, const f32 y,
                           const f32 xScale, const f32 yScale, const u32 flags);
extern void PreRender_setup_savebuf(PreRender* render, u32 width, u32 height, void* fbuf, void* zbuf, void* cvg);
extern void PreRender_init(PreRender* render);
extern void PreRender_setup_renderbuf(PreRender* render, u32 width, u32 height, void* fbuf, void* zbuf);
extern void PreRender_cleanup(PreRender* render);
extern void PreRender_CopyRGBC(PreRender* render, Gfx** gfxp, int width, int height);

#ifdef __cplusplus
}
#endif

#endif
