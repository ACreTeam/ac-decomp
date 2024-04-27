#include "PreRender.h"

#include "libultra/libultra.h"
#include "gfxalloc.h"
#include "sys_ucode.h"
#include "libforest/gbi_extensions.h"

extern void wallpaper_draw1(PreRenderBackground2DParams* bg2D, Gfx** gfxp) {
    Gfx* gfx;
    uObjBg* bg;
    int alphaCompare;
    Gfx* gfxTemp;
    int loadS2DEX2;

    loadS2DEX2 = (bg2D->flags & BG2D_FLAGS_LOAD_S2DEX2) != 0;
    alphaCompare = (bg2D->flags & BG2D_FLAGS_AC_THRESHOLD) ? G_AC_THRESHOLD : G_AC_NONE;

    gfxTemp = *gfxp;
    bg = (uObjBg*)gfxalloc(&gfxTemp, sizeof(uObjBg));
    gfx = gfxTemp;

    bg->b.imageX = 0;
    bg->b.imageW = (bg2D->width * (1 << 2)) + 1;
    bg->b.frameX = bg2D->x * (1 << 2);

    bg->b.imageY = 0;
    bg->b.imageH = (bg2D->height * (1 << 2)) + 1;
    bg->b.frameY = bg2D->y * (1 << 2);

    bg->b.imagePtr = bg2D->timg;
    bg->b.imageLoad = G_BGLT_LOADTILE;
    bg->b.imageFmt = bg2D->fmt;
    bg->b.imageSiz = bg2D->siz;
    bg->b.imagePal = 0;
    bg->b.imageFlip = 0;

    if (loadS2DEX2 != 0) {
        gSPLoadUcode(gfx++, ucode_GetSpriteTextStart(), ucode_GetSpriteDataStart());
    }

    if ((bg2D->fmt == G_IM_FMT_CI) && (bg2D->tlut != NULL)) {
        gDPLoadTLUT(gfx++, bg2D->tlutCount, 256, bg2D->tlut);
    } else {
        gDPPipeSync(gfx++);
    }

    if (bg2D->flags & BG2D_FLAGS_COPY) {
        bg->b.frameW = bg2D->width * (1 << 2);
        bg->b.frameH = bg2D->height * (1 << 2);

        if (!(bg2D->flags & BG2D_FLAGS_SAVE_OTHERMODE)) {
            gDPSetOtherMode(gfx++, bg2D->tt | G_CYC_COPY, alphaCompare);
        }

        gSPBgRectCopy(gfx++, bg);
    } else {
        bg->b.frameW = ((u32)bg2D->width << 2) * bg2D->xScale;
        bg->b.frameH = ((u32)bg2D->height << 2) * bg2D->yScale;
        bg->b.tmemW = (1 << 10) / bg2D->xScale;
        bg->b.tmemH = (1 << 10) / bg2D->yScale;
        bg->s.imageYorig = bg->b.imageY;

        if (!(bg2D->flags & BG2D_FLAGS_SAVE_OTHERMODE)) {
            gDPSetOtherMode(gfx++, bg2D->tt | G_AD_DISABLE | G_CD_DISABLE | G_TC_FILT,
                            AA_EN | CVG_X_ALPHA | ALPHA_CVG_SEL |
                                GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_BL, G_BL_1MA) |
                                GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_BL, G_BL_1MA) | alphaCompare);
        }

        if (!(bg2D->flags & BG2D_FLAGS_SAVE_COMBINER)) {
            gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, 0, 0, 0, 1, 0, 0, 0, TEXEL0, 0, 0, 0, 1);
        }

        gSPObjRenderMode(gfx++, G_OBJRM_ANTIALIAS | G_OBJRM_BILERP);
        gSPBgRect1Cyc(gfx++, bg);
    }

    gDPPipeSync(gfx++);

    if (loadS2DEX2) {
        gSPLoadUcode(gfx++, ucode_GetPolyTextStart(), ucode_GetPolyDataStart());
    }

    *gfxp = gfx;
}

extern void wallpaper_draw(Gfx** const gfxp, u16* const timg, u16* const tlut, const u16 width, const u16 height,
                           const u8 fmt, const u8 siz, const u16 tt, const u16 tlutCount, f32 x, const f32 y,
                           const f32 xScale, const f32 yScale, const u32 flags) {

    PreRenderBackground2DParams bg2D;

    bg2D.timg = timg;
    bg2D.tlut = tlut;
    bg2D.width = width;
    bg2D.height = height;
    bg2D.fmt = fmt;
    bg2D.siz = siz;
    bg2D.tt = tt;
    bg2D.tlutCount = tlutCount;
    bg2D.x = x;
    bg2D.y = y;
    bg2D.xScale = xScale;
    bg2D.yScale = yScale;
    bg2D.flags = flags;

    wallpaper_draw1(&bg2D, gfxp);
}

static Gfx* gfx_SetUpCFB(Gfx* gfx, void* ptr, u32 width, u32 heiht) {

    gDPPipeSync(gfx + 0);
    gDPSetColorImage(gfx + 1, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, ptr);
    gDPSetScissor(gfx + 2, G_SC_NON_INTERLACE, 0, 0, width, heiht);

    return gfx + 3;
}

extern void PreRender_setup_savebuf(PreRender* render, u32 width, u32 height, void* fbuf, void* zbuf, void* cvg) {
    render->width_bak = width;
    render->height_bak = height;

    render->framebuffer_bak = fbuf;
    render->cvg_bak = cvg;

    render->zbuffer_bak = zbuf;

    render->ulx_bak = 0;
    render->uly_bak = 0;
    render->lrx_bak = width - 1;
    render->lry_bak = height - 1;
}

extern void PreRender_init(PreRender* render) {
    bzero(render, sizeof(PreRender));
}

extern void PreRender_setup_renderbuf(PreRender* render, u32 width, u32 height, void* fbuf, void* zbuf) {
    render->width = width;
    render->height = height;

    render->framebuffer = fbuf;
    render->zbuffer = zbuf;

    render->ulx = 0;
    render->uly = 0;
    render->lrx = width - 1;
    render->lry = height - 1;
}

extern void PreRender_cleanup(PreRender* render) {
    // nothing
}

static void PreRender_ShowCoveredge(Gfx** gfxp, u16 ulx, u16 uly, u16 lrx, u16 lry) {
    Gfx* gfx = *gfxp;

    gDPPipeSync(gfx++);

    gDPSetBlendColor(gfx++, 255, 255, 255, 8);
    gDPSetPrimDepth(gfx++, -1, -1);

    gDPSetOtherMode(gfx++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_VISCVG | G_RM_VISCVG2);

    gDPFillRectangle(gfx++, ulx, uly, lrx, lry);

    gDPPipeSync(gfx++);

    *gfxp = gfx;
}

extern void PreRender_CopyRGBC(PreRender* render, Gfx** gfxp, int width, int height) {
    Gfx* gfx = *gfxp;

    u32 remain;
    u32 term;

    u32 uls;
    u32 ult;
    u32 lrs;
    u32 lrt;

    u32 w;
    u32 h;
    u32 lrs_max;
    u32 lrt_max;

    if ((render->width_bak + width) <= 0 || (render->height_bak + height) <= 0) {
        return;
    }

    gDPPipeSync(gfx++);

    gfx = gfx_SetUpCFB(gfx, render->framebuffer, render->width, render->height);

    gDPSetOtherMode(gfx++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_OPA_SURF | G_RM_OPA_SURF2);
    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, 0, 0, 0, 1, 0, 0, 0, TEXEL0, 0, 0, 0, 1);

    wallpaper_draw(&gfx, render->framebuffer_bak, 0, render->width_bak, render->height_bak, G_IM_FMT_RGBA, G_IM_SIZ_16b,
                   0, 0, width, height, 1.0f, 1.0f,
                   BG2D_FLAGS_SAVE_OTHERMODE | BG2D_FLAGS_SAVE_COMBINER | BG2D_FLAGS_LOAD_S2DEX2);

    gfx = gfx_SetUpCFB(gfx, render->framebuffer_bak, render->width_bak, render->height_bak);

    PreRender_ShowCoveredge(&gfx, 0, 0, render->width_bak, render->height_bak);

    gfx = gfx_SetUpCFB(gfx, render->framebuffer, render->width, render->height);

    gDPSetOtherMode(gfx++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | AA_EN | IM_RD | CVG_DST_WRAP | ZMODE_OPA | CVG_X_ALPHA | ALPHA_CVG_SEL |
                        FORCE_BL | G_RM_PASS | GBL_c2(G_BL_CLR_IN, G_BL_0, G_BL_CLR_MEM, G_BL_1));

    gDPSetCombineLERP(gfx++, 0, 0, 0, 0, 1, 0, TEXEL0, ENVIRONMENT, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

    gDPSetEnvColor(gfx++, 255, 255, 255, 32);

    remain = (1 << 12) / (u32)((u16)render->width_bak << 1);
    term = render->width_bak;

    if (width < 0) {
        uls = -width;
        lrs = 0;
    } else {
        uls = 0;
        lrs = width;
    }

    if (height < 0) {
        ult = -height;
        lrt = 0;
        term = render->height_bak + height;
    } else {
        term = render->height_bak;
        lrt = height;
        ult = 0;
    }

    w = (render->width_bak + width);
    lrs_max = (u32)render->width_bak;

    while (term > 0) {
        if (remain > term) {
            remain = term;
        }

        lrt_max = ult + remain;
        if (lrt_max > render->width_bak) {
            lrt_max = render->width_bak;
            remain = render->width_bak - ult;
        }

        h = lrt + remain;

        gDPLoadTextureTile(gfx++, render->framebuffer_bak, G_IM_FMT_I, G_IM_SIZ_8b, (render->width_bak << 1),
                           (render->height_bak << 1), (uls * 2), ult, ((lrs_max * 2) - 1), (lrt_max - 1), 0,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                           G_TX_NOLOD);

        gSPTextureRectangle(gfx++, ((u32)lrs) * 4, ((u32)lrt) << G_TEXTURE_IMAGE_FRAC, ((u32)w) << G_TEXTURE_IMAGE_FRAC,
                            ((u32)h) << G_TEXTURE_IMAGE_FRAC, G_TX_RENDERTILE, (uls * 2) << 5, ult << 5, (1 << 1) << 10,
                            1 << 10);

        term -= remain;
        ult += remain;
        lrt += remain;
    }
    gDPPipeSync(gfx++);
    *gfxp = gfx;
}
