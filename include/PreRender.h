#ifndef PRERENDER_H
#define PRERENDER_H

#include "types.h"
#include "libforest/gbi_extensions.h"

#ifdef __cplusplus
extern "C" {
#endif

#define G_OBJ_RECTANGLE_R 0xDA
#define G_OBJ_MOVEMEM 0xDC
#define G_RDPHALF_0 0xE4
#define G_OBJ_RECTANGLE 0x01
#define G_OBJ_SPRITE 0x02
#define G_SELECT_DL 0x04
#define G_OBJ_LOADTXTR 0x05
#define G_OBJ_LDTX_SPRITE 0x06
#define G_OBJ_LDTX_RECT 0x07
#define G_OBJ_LDTX_RECT_R 0x08
#define G_BG_1CYC 0x09
#define G_BG_COPY 0x0A
#define G_OBJ_RENDERMODE 0x0B

#define G_OBJRM_NOTXCLAMP 0x01
#define G_OBJRM_XLU 0x02       /* Ignored */
#define G_OBJRM_ANTIALIAS 0x04 /* Ignored */
#define G_OBJRM_BILERP 0x08
#define G_OBJRM_SHRINKSIZE_1 0x10
#define G_OBJRM_SHRINKSIZE_2 0x20
#define G_OBJRM_WIDEN 0x40

/*---------------------------------------------------------------------------*
 *	Background wrapped screen
 *---------------------------------------------------------------------------*/
#define gSPBgRectangle(pkt, m, mptr) gDma0p((pkt), (m), (mptr), 0)
#define gsSPBgRectangle(m, mptr) gsDma0p((m), (mptr), 0)
#define gSPBgRectCopy(pkt, mptr) gSPBgRectangle((pkt), G_BG_COPY, (mptr))
#define gsSPBgRectCopy(mptr) gsSPBgRectangle(G_BG_COPY, (mptr))
#define gSPBgRect1Cyc(pkt, mptr) gSPBgRectangle((pkt), G_BG_1CYC, (mptr))
#define gsSPBgRect1Cyc(mptr) gsSPBgRectangle(G_BG_1CYC, (mptr))

/*---------------------------------------------------------------------------*
 *	2D Objects
 *---------------------------------------------------------------------------*/
#define gSPObjSprite(pkt, mptr) gDma0p((pkt), G_OBJ_SPRITE, (mptr), 0)
#define gsSPObjSprite(mptr) gsDma0p(G_OBJ_SPRITE, (mptr), 0)
#define gSPObjRectangle(pkt, mptr) gDma0p((pkt), G_OBJ_RECTANGLE, (mptr), 0)
#define gsSPObjRectangle(mptr) gsDma0p(G_OBJ_RECTANGLE, (mptr), 0)
#define gSPObjRectangleR(pkt, mptr) gDma0p((pkt), G_OBJ_RECTANGLE_R, (mptr), 0)
#define gsSPObjRectangleR(mptr) gsDma0p(G_OBJ_RECTANGLE_R, (mptr), 0)

/*---------------------------------------------------------------------------*
 *	2D Matrix
 *---------------------------------------------------------------------------*/
#define gSPObjMatrix(pkt, mptr) gDma1p((pkt), G_OBJ_MOVEMEM, (mptr), 0, 23)
#define gsSPObjMatrix(mptr) gsDma1p(G_OBJ_MOVEMEM, (mptr), 0, 23)
#define gSPObjSubMatrix(pkt, mptr) gDma1p((pkt), G_OBJ_MOVEMEM, (mptr), 2, 7)
#define gsSPObjSubMatrix(mptr) gsDma1p(G_OBJ_MOVEMEM, (mptr), 2, 7)

/*---------------------------------------------------------------------------*
 *	Loading into TMEM
 *---------------------------------------------------------------------------*/
#define gSPObjLoadTxtr(pkt, tptr) gDma0p((pkt), G_OBJ_LOADTXTR, (tptr), 23)
#define gsSPObjLoadTxtr(tptr) gsDma0p(G_OBJ_LOADTXTR, (tptr), 23)
#define gSPObjLoadTxSprite(pkt, tptr) gDma0p((pkt), G_OBJ_LDTX_SPRITE, (tptr), 47)
#define gsSPObjLoadTxSprite(tptr) gsDma0p(G_OBJ_LDTX_SPRITE, (tptr), 47)
#define gSPObjLoadTxRect(pkt, tptr) gDma0p((pkt), G_OBJ_LDTX_RECT, (tptr), 47)
#define gsSPObjLoadTxRect(tptr) gsDma0p(G_OBJ_LDTX_RECT, (tptr), 47)
#define gSPObjLoadTxRectR(pkt, tptr) gDma0p((pkt), G_OBJ_LDTX_RECT_R, (tptr), 47)
#define gsSPObjLoadTxRectR(tptr) gsDma0p(G_OBJ_LDTX_RECT_R, (tptr), 47)

/*---------------------------------------------------------------------------*
 *	Select Display List
 *---------------------------------------------------------------------------*/
#define gSPSelectDL(pkt, mptr, sid, flag, mask)                           \
    {                                                                     \
        gDma1p((pkt), G_RDPHALF_0, (flag), (u32)(mptr) & 0xFFFF, (sid));  \
        gDma1p((pkt), G_SELECT_DL, (mask), (u32)(mptr) >> 16, G_DL_PUSH); \
    }
#define gsSPSelectDL(mptr, sid, flag, mask)                         \
    {                                                               \
        gsDma1p(G_RDPHALF_0, (flag), (u32)(mptr) & 0xFFFF, (sid));  \
        gsDma1p(G_SELECT_DL, (mask), (u32)(mptr) >> 16, G_DL_PUSH); \
    }
#define gSPSelectBranchDL(pkt, mptr, sid, flag, mask)                       \
    {                                                                       \
        gDma1p((pkt), G_RDPHALF_0, (flag), (u32)(mptr) & 0xFFFF, (sid));    \
        gDma1p((pkt), G_SELECT_DL, (mask), (u32)(mptr) >> 16, G_DL_NOPUSH); \
    }
#define gsSPSelectBranchDL(mptr, sid, flag, mask)                     \
    {                                                                 \
        gsDma1p(G_RDPHALF_0, (flag), (u32)(mptr) & 0xFFFF, (sid));    \
        gsDma1p(G_SELECT_DL, (mask), (u32)(mptr) >> 16, G_DL_NOPUSH); \
    }

#define G_OBJRM_NOTXCLAMP 0x01
#define G_OBJRM_XLU 0x02       /* Ignored */
#define G_OBJRM_ANTIALIAS 0x04 /* Ignored */
#define G_OBJRM_BILERP 0x08
#define G_OBJRM_SHRINKSIZE_1 0x10
#define G_OBJRM_SHRINKSIZE_2 0x20
#define G_OBJRM_WIDEN 0x40

#define gSPObjRenderMode(pkt, mode) gImmp1((pkt), G_OBJ_RENDERMODE, (mode))
#define gsSPObjRenderMode(mode) gsImmp1(G_OBJ_RENDERMODE, (mode))

#define G_BGLT_LOADBLOCK 0x0033
#define G_BGLT_LOADTILE 0xFFF4

#define BG2D_FLAGS_1 (1 << 0)
#define BG2D_FLAGS_2 (1 << 1)
#define BG2D_FLAGS_AC_THRESHOLD (1 << 2)
#define BG2D_FLAGS_LOAD_S2DEX2 (1 << 3)
#define BG2D_FLAGS_COPY (1 << 4)

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

/* Non scalable background plane */
typedef struct {
    u16 imageX; /* x-coordinate of upper-left position of texture (u10.5) */
    u16 imageW; /* width of the texture (u10.2) */
    s16 frameX; /* upper-left position of transferred frame (s10.2) */
    u16 frameW; /* width of transferred frame (u10.2) */

    u16 imageY; /* y-coordinate of upper-left position of texture (u10.5) */
    u16 imageH; /* height of the texture (u10.2) */
    s16 frameY; /* upper-left position of transferred frame (s10.2) */
    u16 frameH; /* height of transferred frame (u10.2) */

    u64* imagePtr; /* texture source address on DRAM */
    u16 imageLoad; /* which to use, LoadBlock or  LoadTile */
    u8 imageFmt;   /* format of texel - G_IM_FMT_*  */
    u8 imageSiz;   /* size of texel - G_IM_SIZ_*   */
    u16 imagePal;  /* pallet number  */
    u16 imageFlip; /* right & left image inversion (Inverted by G_BG_FLAG_FLIPS) */

    /* The following is set in the initialization routine guS2DInitBg(). There is no need for the user to set it. */
    u16 tmemW;      /* TMEM width and Word size of frame 1 line.
                       At LoadBlock, GS_PIX2TMEM(imageW/4,imageSiz)
                       At LoadTile  GS_PIX2TMEM(frameW/4,imageSiz)+1 */
    u16 tmemH;      /* height of TMEM loadable at a time (s13.2) 4 times value
                       When the normal texture, 512/tmemW*4
                       When the CI texture, 256/tmemW*4 */
    u16 tmemLoadSH; /* SH value
                       At LoadBlock, tmemSize/2-1
                       At LoadTile, tmemW*16-1 */
    u16 tmemLoadTH; /* TH value or Stride value
                       At LoadBlock, GS_CALC_DXT(tmemW)
                       At LoadTile, tmemH-1 */
    u16 tmemSizeW;  /* skip value of imagePtr for image 1-line
                       At LoadBlock, tmemW*2
                       At LoadTile, GS_PIX2TMEM(imageW/4,imageSiz)*2 */
    u16 tmemSize;   /* skip value of imagePtr for 1-loading
                       = tmemSizeW*tmemH                          */
} uObjBg_t;         /* 40 bytes */

/* Scalable background plane */
typedef struct {
    u16 imageX; /* x-coordinate of upper-left position of texture (u10.5) */
    u16 imageW; /* width of texture (u10.2) */
    s16 frameX; /* upper-left position of transferred frame (s10.2) */
    u16 frameW; /* width of transferred frame (u10.2) */

    u16 imageY; /* y-coordinate of upper-left position of texture (u10.5) */
    u16 imageH; /* height of texture (u10.2) */
    s16 frameY; /* upper-left position of transferred frame (s10.2) */
    u16 frameH; /* height of transferred frame (u10.2) */

    u64* imagePtr; /* texture source address on DRAM */
    u16 imageLoad; /* Which to use, LoadBlock or LoadTile? */
    u8 imageFmt;   /* format of texel - G_IM_FMT_*  */
    u8 imageSiz;   /* size of texel - G_IM_SIZ_*  */
    u16 imagePal;  /* pallet number */
    u16 imageFlip; /* right & left image inversion (Inverted by G_BG_FLAG_FLIPS) */

    u16 scaleW;     /* scale value of X-direction (u5.10) */
    u16 scaleH;     /* scale value of Y-direction (u5.10) */
    s32 imageYorig; /* start point of drawing on image (s20.5) */

    u8 padding[4];

} uObjScaleBg_t; /* 40 bytes */

typedef union {
    uObjBg_t b;
    uObjScaleBg_t s;
    long long int force_structure_alignment;
} uObjBg;

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
