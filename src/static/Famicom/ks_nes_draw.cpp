#define FIX_SQRT_LINKAGE
#include "Famicom/ks_nes_draw.h"
#include "dolphin/gx.h"
#include "dolphin/PPCArch.h"
#include "_mem.h"

u8 ksNesPaletteNormal[] = {
    0xc2, 0x10, 0x80, 0x17, 0x98, 0x17, 0xc0, 0x14, 0xdc, 0x0d, 0xd8, 0x03, 0xd8, 0x00, 0xc8, 0x80, 0xbc, 0xa0, 0x80,
    0xe0, 0x81, 0x21, 0x80, 0xe4, 0x80, 0xac, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00, 0xe7, 0x39, 0x81, 0x7f, 0xa0, 0xff,
    0xd8, 0xd9, 0xfc, 0xd5, 0xfc, 0xcb, 0xfc, 0xc3, 0xe9, 0x20, 0xe1, 0x80, 0x9d, 0xe0, 0x8e, 0x02, 0x82, 0x4c, 0x82,
    0x18, 0x88, 0x42, 0x80, 0x00, 0x80, 0x00, 0xff, 0xff, 0x82, 0x5f, 0xb6, 0x1f, 0xe9, 0xbf, 0xfd, 0xd9, 0xfd, 0xb3,
    0xfd, 0xeb, 0xfe, 0x4b, 0xfe, 0x86, 0xd2, 0xe0, 0xab, 0x6d, 0xa7, 0x55, 0x83, 0x7f, 0xb1, 0x8c, 0x80, 0x00, 0x80,
    0x00, 0xff, 0xff, 0xc2, 0xff, 0xde, 0xff, 0xea, 0xff, 0xfe, 0xfd, 0xfe, 0xf9, 0xff, 0x16, 0xff, 0x35, 0xff, 0x74,
    0xe7, 0x93, 0xd7, 0xb6, 0xd7, 0xdd, 0xdb, 0xbf, 0xef, 0x7b, 0x80, 0x00, 0x80, 0x00,
};

void ksNesDrawInit(ksNesCommonWorkObj* wp) {
    Mtx44 mtx;
    Vec v1 = { 0.f, 0.f, 800.f };
    Vec v3 = { 0.f, 0.f, -100.f };
    Vec v2 = { 0.f, 1.f, 0.f };
    GXInvalidateTexAll();
    GXInvalidateVtxCache();
    GXSetClipMode(GX_CLIP_DISABLE);
    GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    GXSetCopyFilter(GX_FALSE, NULL, GX_FALSE, NULL);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetZTexture(GX_ZT_DISABLE, GX_TF_Z8, 0);
    GXSetZCompLoc(GX_FALSE);
    GXSetColorUpdate(GX_TRUE);
    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);
    C_MTXOrtho(mtx, 0, -480.f, 0.f, 640.f, 0.f, 2000.f);
    GXSetProjection(mtx, GX_ORTHOGRAPHIC);
    C_MTXLookAt(wp->work_priv.draw_mtx, &v1, &v2, &v3);
}

void ksNesDrawEnd() {
    GXSetClipMode(GX_CLIP_ENABLE);
    GXSetZCompLoc(GX_TRUE);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
    GXSetTevDirect(GX_TEVSTAGE2);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_FALSE, 0, 0);
    GXSetTexCoordScaleManually(GX_TEXCOORD1, GX_FALSE, 0, 0);
}

void ksNesDrawClearEFBFirst(ksNesCommonWorkObj* wp) {
    DCFlushRange(&wp->work_priv._2A40, sizeof(wp->work_priv._2A40));
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetBlendMode(GX_BM_LOGIC, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGB, GX_RGBA4, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetCurrentMtx(0);
    GXLoadPosMtxImm(wp->work_priv.draw_mtx, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    {
        GXPosition2s16(0x80, -0x80);
        GXColor1u32(0x00ff0000);

        GXPosition2s16(0x180, -0x80);
        GXColor1u32(0x00000000);

        GXPosition2s16(0x180, -0x180);
        GXColor1u32(0x0000ff00);

        GXPosition2s16(0x80, -0x180);
        GXColor1u32(0x00000000);
    }
    GXEnd();
}

void ksNesDrawMakeBGIndTex(ksNesCommonWorkObj* wp, u32 ind) {
    u32 myInd = 0x7fff;
    u8 myInd2 = 0x80;
    if (ind) {
        myInd = 9;
    }
    if (wp->chr_to_i8_buf_size <= 0x1000000) {
        myInd2 = wp->chr_to_i8_buf_size >> 0xd;
    }
    DCFlushRangeNoSync(wp->work_priv._3240, sizeof(wp->work_priv._3240));
    DCFlushRangeNoSync(wp->work_priv._7840, sizeof(wp->work_priv._7840));
}

void ksNesDrawMakeBGIndTexMMC5(ksNesCommonWorkObj*, ksNesStateObj*) {
}

void ksNesDrawMakeBGIndTexMMC2(ksNesCommonWorkObj*, u32) {
}

void ksNesDrawOBJSetupMMC2(ksNesCommonWorkObj*) {
}

void ksNesDrawBG(ksNesCommonWorkObj*, ksNesStateObj*) {
}

u32 ksNesDrawMakeOBJBlankVtxList(ksNesCommonWorkObj* wp) {
    u32 ret = 0;
    u32 comparison_mask = 20;
    int i;

    for (i = 8; i < 0xf0; i++) {
        int bMask = wp->work_priv._0B40[i]._19 & 0x14;
        if (bMask != comparison_mask && ((bMask != 0) || (comparison_mask != 4)) &&
            (bMask != 4 || comparison_mask != 0)) {
            if (ret & 1 != 0) {
                wp->work_priv.wram[ret] = i - wp->_004C[ret + 0x13];
                ret++;
            }
            if ((comparison_mask == 20) || (wp->work_priv._0B40[i]._19 & 0x10) == 0) {
                wp->work_priv.wram[ret++] = i;
            }
            comparison_mask = wp->work_priv._0B40[i]._19 & 0x14;
        }
    }

    if (ret & 1) {
        wp->work_priv.wram[ret] = i - wp->_004C[ret + 0x13];
        ret++;
    }
    return ret;
}

u32 ksNesDrawMakeOBJAppearVtxList(ksNesCommonWorkObj* wp) {
    u32 ret = 0;
    u32 comparison_mask = 0;
    int i;

    for (i = 8; i < 0xf0; i++) {
        int bMask = wp->work_priv._0B40[i]._19 & 0x14;
        if (bMask != comparison_mask && ((bMask != 0) || (comparison_mask != 4)) &&
            (bMask != 4 || comparison_mask != 0)) {
            if (ret & 1 != 0) {
                wp->work_priv.wram[ret] = i - wp->_004C[ret + 0x13];
                ret++;
            }
            if ((wp->work_priv._0B40[i]._19 & 0x10)) {
                wp->work_priv.wram[ret++] = i;
            }
            comparison_mask = wp->work_priv._0B40[i]._19 & 0x14;
        }
    }

    if (ret & 1) {
        wp->work_priv.wram[ret] = i - wp->_004C[ret + 0x13];
        ret++;
    }
    return ret;
}

void ksNesDrawOBJ(ksNesCommonWorkObj* wp, ksNesStateObj* state, u32 c) {
    u32 size = 0x100000;
    int i;
    GXTexObj GStack_7c;
    GXTexObj GStack_9c;
    GXTexObj GStack_bc;
    if (wp->chr_to_i8_buf_size <= 0x100000) {
        size = wp->chr_to_i8_buf_size;
    }
    if (c == 0) {
        for (u32 i = 0; i < 0x110; i++) {
            u32 v;
            if (i < 0xf0) {
                v = 8;
                if (state->frame_flags & 0x2000) {
                    v = 255;
                }
            } else {
                v = 0;
            }
            wp->work_priv.wram[i] = v;
            if ((wp->work_priv._0B40[i]._19 & 0x10) == 0) {
                wp->work_priv.wram[i] = 0;
            }
        }
        if (state->prg_size == 0x40000 && memcmp(state->prgromp + 0x3ffe9, "MARIO 3", 7) == 0) {
            for (i = 0; i < 0xf0; i++) {
                if (wp->work_priv._0B40[i]._0C == 0x7e7e7e7e) {
                    wp->work_priv.wram[i] = 0;
                }
            }
        }
        memset(&wp->work_priv.wram[0x340], 0, 0x800);
        u8* uVar6 = &wp->work_priv.wram[0x340];
        int a;
        for (u32 i = 0; i < 0x100; i++) {
            int _j = 8;
            if (wp->work_priv._0B40[wp->work_priv._2940[i]]._18 & 0x20) {
                _j = 0x10;
            }
            a = 0;
            int b, _c;
            if (wp->work_priv._2940[i + 2] & 0x80) {
                b = _j << 2;
                _c = -4;
            } else {
                b = 0;
                _c = 4;
            }
            u32 j, val;
            for (j = 0; j < _j; j++) {
                int ind = j + wp->work_priv._2940[i];
                val = wp->work_priv.wram[ind];
                if (val) {
                    wp->work_priv.wram[ind]--;
                    if ((a & 2) == 0) {
                        uVar6[a] = wp->work_priv._2940[i] + j;
                        uVar6[a + 1] = b;
                        a += 2;
                    }
                } else if ((a & 2) != 0) {
                    uVar6[a] = wp->work_priv._2940[i] + j;
                    uVar6[a + 1] = b;
                    a += 2;
                }
                b += _c;
                val = b;
            }
            if ((a & 2) != 0) {
                uVar6[a] = wp->work_priv._2940[i] + j;
                uVar6[a + 1] = val;
                a += 2;
            }
            wp->work_priv.wram[0x300 + (i / 4)] = a;
        }
    }
    GXSetNumChans(1);
    GXSetNumTexGens(2);
    GXSetNumTevStages(3);
    GXSetNumIndStages(2);
    GXSetBlendMode(GX_BM_LOGIC, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX1, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGB, GX_RGBA4, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGBX8, 10);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_CLR_RGBA, GX_RGBX8, 10);
    GXInitTexObj(&GStack_7c, wp->chr_to_u8_bufp, 0x400, (u16)(size >> 10), GX_TF_I8, GX_MIRROR, GX_CLAMP, 0);
    GXInitTexObjLOD(&GStack_7c, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&GStack_7c, GX_TEXMAP0);
    GXInitTexObj(&GStack_9c, wp->work_priv._8EC0, 8, 4, GX_TF_IA8, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&GStack_9c, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&GStack_9c, GX_TEXMAP1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 0x3c);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_TRUE, 0x100, 0x101);
    GXSetTexCoordBias(GX_TEXCOORD0, 0, 0);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_8, GX_ITS_1);
    GXSetTevIndirect(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_OFF, GX_ITW_OFF, GX_ITW_OFF, GX_FALSE,
                     GX_FALSE, GX_ITBA_OFF);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEX_DISABLE, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);
    GXInitTexObj(&GStack_bc, wp->work_priv._8E40, 4, 0x10, GX_TF_IA8, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&GStack_bc, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&GStack_bc, GX_TEXMAP2);
    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, 0x3c);
    GXSetTexCoordScaleManually(GX_TEXCOORD1, GX_TRUE, 0x100, 0x101);
    GXSetTexCoordBias(GX_TEXCOORD1, 0, 0);
    GXSetIndTexOrder(GX_INDTEXSTAGE1, GX_TEXCOORD1, GX_TEXMAP2);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_8, GX_ITS_1);
    {
        u32 i;
        for (i = 0; size > (0x8000 << i); i++) {}

        static f32 indtexmtx_obj[2][3] = { { 0.5f, 0.f, 0.f }, { 0.f, 0.0625f, 0.f } };
        indtexmtx_obj[0][0] = 0.5f / (i >= 4 ? (1 << i - 3) : 1);
        indtexmtx_obj[1][1] = 0.5f / (i <= 2 ? (1 << 3 - i) : 1);
        GXSetIndTexMtx(GX_ITM_0, indtexmtx_obj, 36 + (i < 4 ? 0 : i - 3));
    }
    GXSetTevIndirect(GX_TEVSTAGE1, GX_INDTEXSTAGE1, GX_ITF_8, GX_ITB_NONE, GX_ITM_0, GX_ITW_OFF, GX_ITW_0, GX_TRUE,
                     GX_FALSE, GX_ITBA_OFF);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_C2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevDirect(GX_TEVSTAGE2);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    const static GXColor color_thres = { 0xff, 1, 0, 0 };
    GXSetTevColor(GX_TEVREG0, color_thres);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C0, GX_CC_C2, GX_CC_CPREV, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_COMP_GR16_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_APREV, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
}

void ksNesDrawOBJMMC5(ksNesCommonWorkObj*, ksNesStateObj*, u32) {
}

void ksNesDrawFlushEFBToRed8(u8* buf) {
    static const GXColor black = { 0, 0, 0, 0 };
    GXSetTexCopySrc(0x80, 0x88, 0x100, 0xe4);
    GXSetTexCopyDst(0x100, 0xe4, GX_CTF_R8, GX_FALSE);
    GXSetCopyClear(black, 0xffffff);
    GXCopyTex(buf, GX_FALSE);
    GXPixModeSync();
    GXInvalidateTexAll();
}

void ksNesDrawOBJI8ToEFB(ksNesCommonWorkObj* wp, u8* buf) {
}

void ksNesDrawEmuResult(ksNesCommonWorkObj*) {
}

void ksNesDraw(ksNesCommonWorkObj* wp, ksNesStateObj* state) {
    ksNesDrawInit(wp);
    ksNesDrawClearEFBFirst(wp);
    if (state->mapper == 9 || state->mapper == 10) {
        ksNesDrawMakeBGIndTexMMC2(wp, state->mapper == 9 ? TRUE : FALSE);
        ksNesDrawOBJSetupMMC2(wp);
    } else if (state->mapper == 5) {
        ksNesDrawMakeBGIndTexMMC5(wp, state);
    } else {
        ksNesDrawMakeBGIndTex(wp, state->mapper == 4 ? TRUE : FALSE);
    }
    PPCSync();
    if (state->mapper == 5) {
        ksNesDrawOBJMMC5(wp, state, 0);
    } else {
        ksNesDrawOBJ(wp, state, 0);
    }
    ksNesDrawFlushEFBToRed8(wp->result_bufp);
    if (state->mapper == 5) {
        ksNesDrawOBJMMC5(wp, state, 1);
    } else {
        ksNesDrawOBJ(wp, state, 1);
    }

    ksNesDrawBG(wp, state);
    ksNesDrawOBJI8ToEFB(wp, wp->result_bufp);
    ksNesDrawFlushEFBToRed8(wp->result_bufp);
    ksNesDrawEmuResult(wp);
    ksNesDrawEnd();
}
