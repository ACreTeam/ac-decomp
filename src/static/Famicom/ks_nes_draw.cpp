#include "gx/GXEnum.h"
#include "gx/GXTexture.h"
#include "gx/GXVert.h"
#define FIX_SQRT_LINKAGE
#include "Famicom/ks_nes_draw.h"
#include "dolphin/gx.h"
#include "dolphin/PPCArch.h"
#include "_mem.h"
#include "dolphin/os.h"

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
        GXPosition2s16(128, -128);
        GXColor1u32(0x00ff0000);

        GXPosition2s16(384, -128);
        GXColor1u32(0x00000000);

        GXPosition2s16(384, -384);
        GXColor1u32(0x0000ff00);

        GXPosition2s16(128, -384);
        GXColor1u32(0x00000000);
    }
    GXEnd();
}

void ksNesDrawMakeBGIndTex(ksNesCommonWorkObj* wp, u32 mapper4) {
    u32 trigger_col = mapper4 ? 9 : 0x7fff;
    u32 CHR_flag_xor = wp->chr_to_i8_buf_size <= CHR_TO_I8_BUF_SIZE ? (wp->chr_to_i8_buf_size >> 13) : 0x80;
    u32 row;
    u32 col;
    
    for (row = 8; row < 236; row++) {
        u32 scanline_ctrl0 = wp->work_priv._0B40[row]._1C;
        u32 scanline_ctrl1 = wp->work_priv._0B40[row]._1B;
        u32 mask;
        u32 nibble_acc; // @bug - uninitialized
        u8* patternPtrBase = (u8*)&wp->work_priv._0B40[row]._10;
        u32 tile_byte;
        u32 palette_bits;
        u32 dst_idx;
        u8* nametable_p;

        mask = mask = (scanline_ctrl0 & 0x04) ? CHR_flag_xor : 0; // bruh

        for (col = 0; col < 34; col++) {
            if (col == trigger_col) {
                patternPtrBase -= 8;
            }

            // _00 and _04 are pointers to ppu_nametable_pointers[0/1]?
            nametable_p = (&wp->work_priv._0B40[row]._00)[((scanline_ctrl1 >> 8) & 1)];
            if (((s32)nametable_p) >= 0) {
                nibble_acc = (((u32)nametable_p) & 3) | (nibble_acc << 4);
                tile_byte = (((u32)nametable_p) >> 8) & 0xFF;
            } else {
                nibble_acc = (((nametable_p[0x3C0 + ((scanline_ctrl0 & 0xE0) >> 2) + ((scanline_ctrl1 & 0xE0) >> 5)] >> ((((scanline_ctrl1 & 0x10) >> 3) | (scanline_ctrl0 & 0x10) >> 2))) & 3) & 0x0F) | ((nibble_acc << 4));
                tile_byte = nametable_p[((scanline_ctrl0 & 0xF8) << 2) + ((scanline_ctrl1 & 0xF8) >> 3)];
            }

            palette_bits = patternPtrBase[((u8)tile_byte >> 6) | ((wp->work_priv._0B40[row]._18 & 0x10) >> 2)];

            // issue is here
            wp->work_priv._3240[(((col & 0x3C) * 8) + ((col & 3) * 2) + ((row >> 2) * 288) + ((row & 3) * 8)) + 0] = (((palette_bits & 1) << 6) | (tile_byte & 0x3F)) - (col & 1);
            wp->work_priv._3240[(((col & 0x3C) * 8) + ((col & 3) * 2) + ((row >> 2) * 288) + ((row & 3) * 8)) + 1] = (palette_bits >> 1) ^ mask;

            if ((col & 1) != 0) {
                wp->work_priv._7840[((col >> 1) & 3) + (col & 0x38) * 4 + ((row & 7) * 4 + (row >> 3) * 160)] = nibble_acc;
            }

            scanline_ctrl1 += 8;
        }
    }

    DCFlushRangeNoSync(wp->work_priv._3240, sizeof(wp->work_priv._3240));
    DCFlushRangeNoSync(wp->work_priv._7840, sizeof(wp->work_priv._7840));
}

void ksNesDrawMakeBGIndTexMMC5(ksNesCommonWorkObj* wp, ksNesStateObj* sp) {
    u32 banks_mask = sp->chr_banks & 0x1FC;
    u32 row;
    u32 col;
    
    for (row = 8; row < 236; row++) {
        u32 tile_byte;
        u32 scanline_ctrl0 = wp->work_priv._0B40[row]._1C;
        u32 scanline_ctrl1 = wp->work_priv._0B40[row]._1B;
        u32 nibble_acc; // @bug - uninitialized
        u8* patternPtrBase = (u8*)&wp->work_priv._0B40[row]._10;
        u32 palette_bits;
        u32 tmp;
        u8* nametable_p;

        for (col = 0; col < 34; col++) {
            // _00 and _04 are pointers to ppu_nametable_pointers[0/1]?
            nametable_p = (&wp->work_priv._0B40[row]._00)[((scanline_ctrl1 >> 8) & 1)];
            if (((s32)nametable_p) >= 0) {
                nibble_acc = (((u32)nametable_p) & 3) | (nibble_acc << 4);
                tile_byte = (((u32)nametable_p) >> 8) & 0xFF;
            } else {
                nibble_acc = ((nametable_p[0x3C0 + ((scanline_ctrl0 & 0xE0) >> 2) + ((scanline_ctrl1 & 0xE0) >> 5)] >> ((((scanline_ctrl1 & 0x10) >> 3) | (scanline_ctrl0 & 0x10) >> 2))) & 3) | (nibble_acc << 4);
                tile_byte = nametable_p[((scanline_ctrl0 & 0xF8) << 2) + ((scanline_ctrl1 & 0xF8) >> 3)];
            }

            // issue in this area too probably
            if (wp->work_priv._0B40[row]._1D & 0x20) {
                nibble_acc = (nibble_acc & 0xF0) | (sp->mmc5_extension_ram[((scanline_ctrl1 >> 3) & 0x1F) + ((scanline_ctrl0 & 0xF8) << 2)] >> 6) & 0x0F;
                palette_bits = ((sp->mmc5_extension_ram[((scanline_ctrl1 >> 3) & 0x1F) + ((scanline_ctrl0 & 0xF8) << 2)] << 2) & banks_mask) | ((u8)tile_byte >> 6);
            } else {
                tmp = ((wp->work_priv._0B40[row]._18 & 0x10) >> 2) | ((tile_byte >> 6) & 0x3);
                palette_bits = ((wp->work_priv._0B40[row]._1F << (tmp + 1)) & 0x100) | (patternPtrBase[tmp]);
            }

            // issue is here
            wp->work_priv._3240[(((col & 3) * 2) + ((col & 0x3C) * 8) + ((row >> 2) * 288) + ((row & 3) * 8)) + 0] = (((palette_bits & 1) << 6) | (tile_byte & 0x3F)) - (col & 1);
            wp->work_priv._3240[(((col & 3) * 2) + ((col & 0x3C) * 8) + ((row >> 2) * 288) + ((row & 3) * 8)) + 1] = (palette_bits >> 1);

            if ((col & 1) != 0) {
                wp->work_priv._7840[((col >> 1) & 3) + (col & 0x38) * 4 + ((row & 7) * 4 + (row >> 3) * 160)] = nibble_acc;
            }

            scanline_ctrl1 += 8;
        }
    }

    DCFlushRangeNoSync(wp->work_priv._3240, sizeof(wp->work_priv._3240));
    DCFlushRangeNoSync(wp->work_priv._7840, sizeof(wp->work_priv._7840));
}

#define ksNes_MMC2_LATCH_LO 0xFD // select chr bank 0/2
#define ksNes_MMC2_LATCH_HI 0xFE // select chr bank 1/3

void ksNesDrawMakeBGIndTexMMC2(ksNesCommonWorkObj* wp, u32 mode) {
}

void ksNesDrawOBJSetupMMC2(ksNesCommonWorkObj* wp) {
    u32 i;
    u32 j;
    u32 k;
    
    memset(&wp->work_priv._0200, 0, sizeof(wp->work_priv._0200));
    for (i = 0; i < 64; i++) {
        // _0B40 is the scanline state, _2940 is list of scanline triggers?
        if (wp->work_priv._2940[i]._00 >= 236 || (wp->work_priv._2940[i]._01 != ksNes_MMC2_LATCH_HI && wp->work_priv._2940[i]._01 != ksNes_MMC2_LATCH_LO)) {
            continue;
        }

        j = wp->work_priv._2940[i]._00;
        k = (((wp->work_priv._0B40[j]._18 >> 2) & 0x08) + 8) + j;
        do {
            wp->work_priv._0200[j] = wp->work_priv._2940[i]._01;
            j++;
        } while(j < k);
    }

    // _0200 is the scanline marker entries
    for (i = 0, k = 0; i < ARRAY_COUNT(wp->work_priv._0200); i++) {
        if (wp->work_priv._0200[i] == ksNes_MMC2_LATCH_HI) {
            k = 0;
        } else if (wp->work_priv._0200[i] == ksNes_MMC2_LATCH_LO) {
            k = 1;
        }

        if (k) {
            wp->work_priv._0B40[i]._08[0] = wp->work_priv._0B40[i]._08[1] - 1;
            wp->work_priv._0B40[i]._08[2] = wp->work_priv._0B40[i]._08[1] + 1;
            wp->work_priv._0B40[i]._08[3] = wp->work_priv._0B40[i]._08[1] + 2;
        } else {
            wp->work_priv._0B40[i]._08[1] = wp->work_priv._0B40[i]._08[0] + 1;
            wp->work_priv._0B40[i]._08[2] = wp->work_priv._0B40[i]._08[0] + 2;
            wp->work_priv._0B40[i]._08[3] = wp->work_priv._0B40[i]._08[0] + 3;
        }
    }
}

void ksNesDrawBG(ksNesCommonWorkObj* wp, ksNesStateObj* sp) {
    static const GXColor color_r_0xf0 = { 240, 0, 0, 0 };
    static f32 indtexmtx_screen[2][3] = {
        {0.5f, 0.0f, 0.0f},
        {0.0f, 0.0625f, 0.0f},
    };

    GXTexObj obj0;
    GXTexObj obj1;
    GXTexObj obj2;
    u32 curline;
    u32 cnt;
    u32 color;
    u32 x0;
    u32 x1;
    s16 y;
    u32 i;
    u32 j;

    GXSetNumChans(1);
    GXSetNumTexGens(2);
    GXSetNumTevStages(3);
    GXSetNumIndStages(1);
    GXSetBlendMode(GX_BM_LOGIC, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGB, GX_RGBA4, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_RGBX8, 10);
    GXInitTexObj(&obj0, wp->work_priv._7840, 40, 256, GX_TF_I4, GX_CLAMP, GX_REPEAT, 0);
    GXInitTexObjLOD(&obj0, GX_NEAR, GX_NEAR, 0.0, 0.0, 0.0, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&obj0, GX_TEXMAP0);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_TRUE, 128, 1025);
    GXSetTexCoordBias(GX_TEXCOORD0, GX_FALSE, GX_FALSE);
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColor(GX_TEVREG0, color_r_0xf0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_C0, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXInitTexObj(&obj1, wp->work_priv._3240, 36, 256, GX_TF_IA8, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&obj1, GX_NEAR, GX_NEAR, 0.0, 0.0, 0.0, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&obj1, GX_TEXMAP1);
    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTexCoordScaleManually(GX_TEXCOORD1, GX_TRUE, 1024, 1025);
    GXSetTexCoordBias(GX_TEXCOORD1, GX_FALSE, GX_FALSE);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_8, GX_ITS_1);
    GXSetIndTexMtx(GX_ITM_0, indtexmtx_screen, 36);
    GXSetTevIndirect(GX_TEVSTAGE1, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_0, GX_ITW_16, GX_ITW_0, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP2, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevDirect(GX_TEVSTAGE2);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetLineWidth(6, GX_TO_ZERO);

    for (i = 0; i < 8; i++) {
        if (sp->ppu_render_latches[i] != 0) {
            if (sp->mapper == 5) {
                GXInitTexObj(&obj2, wp->chr_to_u8_bufp + (wp->chr_to_i8_buf_size >> 3) * i, 1024, wp->chr_to_i8_buf_size >> 13, GX_TF_I8, GX_MIRROR, GX_CLAMP, 0);
                GXInitTexObjLOD(&obj2, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
                GXLoadTexObj(&obj2, GX_TEXMAP2);
            } else if ((i & 1) == 0) {
                if (wp->chr_to_i8_buf_size > CHR_TO_I8_BUF_SIZE) {
                    GXInitTexObj(&obj2, wp->chr_to_u8_bufp + 0x20000 * (i & 6), 1024, 256, GX_TF_I8, GX_MIRROR, GX_CLAMP, 0);
                } else {
                    GXInitTexObj(&obj2, wp->chr_to_u8_bufp + (wp->chr_to_i8_buf_size >> 3) * (i & 6), 1024, wp->chr_to_i8_buf_size >> 12, GX_TF_I8, GX_MIRROR, GX_CLAMP, 0);
                }

                GXInitTexObjLOD(&obj2, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
                GXLoadTexObj(&obj2, GX_TEXMAP2);
            }

            cnt = 0;
            curline = sp->ppu_render_latches[i + 8];
            j = curline;
            do {
                if ((wp->work_priv._0B40[j]._19 & 0x08) != 0 && j >= 8 && j < 236) {
                    cnt += 2;
                }
                j = wp->work_priv._0B40[j]._1A;
            } while (j != 0);

            if (cnt != 0) {
                GXBegin(GX_LINES, GX_VTXFMT0, cnt);

                do {
                    if ((wp->work_priv._0B40[curline]._19 & 0x08) != 0 && curline >= 8 && curline < 236) {
                        if ((wp->work_priv._0B40[curline]._19 & 0x02) == 0) {
                            x0 = 0x80 + 8;
                            x1 = (wp->work_priv._0B40[curline]._1B & 0x07) + 8;
                        } else {
                            x0 = 0x80 - (wp->work_priv._0B40[curline]._1B & 0x07);
                            x1 = 0;
                        }

                        color = (wp->work_priv._0B40[curline]._18 & 0xC0) << 24;

                        GXPosition2s16(x0, -0x81 - curline);
                        GXColor1u32(color);
                        GXTexCoord2u16(x1, curline);

                        GXPosition2s16(x0 + 0x100 + 8, -0x81 - curline);
                        GXColor1u32(color);
                        GXTexCoord2u16(x1 + 0x100 + 8, curline);
                    }

                    curline = wp->work_priv._0B40[curline]._1A;
                } while (curline != 0);

                GXEnd();
            }
        }
    }

    cnt = 0;
    for (i = 8; i < 236; i++) {
        if ((wp->work_priv._0B40[i]._19 & 0x08) == 0) {
            cnt += 2;
        }
    }

    if (cnt != 0) {
        GXSetNumTexGens(0);
        GXSetNumTevStages(1);
        GXSetNumIndStages(0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGB, GX_RGBA4, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);

        GXBegin(GX_LINES, GX_VTXFMT0, cnt);

        for (i = 8; i < 236; i++) {

            if ((wp->work_priv._0B40[i]._19 & 0x08) == 0) {
                s16 y = -0x81 - i;
                u32 color = (wp->work_priv._0B40[i]._18 & 0xC0) << 24;

                GXPosition2s16(0x80, y);
                GXColor1u32(color);

                GXPosition2s16(0x180, y);
                GXColor1u32(color);
            }
        }

        GXEnd();
    }
}

u32 ksNesDrawMakeOBJBlankVtxList(ksNesCommonWorkObj* wp) {
    u32 ret = 0;
    u32 comparison_mask = 20;
    int i;

    for (i = 8; i < 0xf0; i++) {
        int bMask = wp->work_priv._0B40[i]._19 & 0x14;
        if (bMask != comparison_mask && ((bMask != 0) || (comparison_mask != 4)) &&
            (bMask != 4 || comparison_mask != 0)) {
            if ((ret & 1) != 0) {
                wp->work_priv._0000[ret] = i - wp->_004C[ret + 0x13];
                ret++;
            }
            if ((comparison_mask == 20) || (wp->work_priv._0B40[i]._19 & 0x10) == 0) {
                wp->work_priv._0000[ret++] = i;
            }
            comparison_mask = wp->work_priv._0B40[i]._19 & 0x14;
        }
    }

    if (ret & 1) {
        wp->work_priv._0000[ret] = i - wp->_004C[ret + 0x13];
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
            if ((ret & 1) != 0) {
                wp->work_priv._0000[ret] = i - wp->_004C[ret + 0x13];
                ret++;
            }
            if ((wp->work_priv._0B40[i]._19 & 0x10)) {
                wp->work_priv._0000[ret++] = i;
            }
            comparison_mask = wp->work_priv._0B40[i]._19 & 0x14;
        }
    }

    if (ret & 1) {
        wp->work_priv._0000[ret] = i - wp->_004C[ret + 0x13];
        ret++;
    }
    return ret;
}

void ksNesDrawOBJ(ksNesCommonWorkObj* wp, ksNesStateObj* state, u32 c) {
    u32 size = wp->chr_to_i8_buf_size <= CHR_TO_I8_BUF_SIZE ? wp->chr_to_i8_buf_size : CHR_TO_I8_BUF_SIZE;
    // int i;
    GXTexObj GStack_7c;
    GXTexObj GStack_9c;
    GXTexObj GStack_bc;
    u32 i;
    u32 j;
    
    if (c == 0) {
        for (i = 0; i < 0x110; i++) {
            wp->work_priv._0000[i] = i < 0xF0 ? ((state->frame_flags & 0x2000) ? 255 : 8) : 0;
            if ((wp->work_priv._0B40[i]._19 & 0x10) == 0) {
                wp->work_priv._0000[i] = 0;
            }
        }
        if (state->prg_size == 0x40000 && memcmp(state->prgromp + 0x3ffe9, "MARIO 3", 7) == 0) {
            for (i = 0; i < 0xf0; i++) {
                if (wp->work_priv._0B40[i]._0C == 0x7e7e7e7e) {
                    wp->work_priv._0000[i] = 0;
                }
            }
        }

        memset(&wp->work_priv._0340, 0, sizeof(wp->work_priv._0340));
        int b;
        int _c;
        int a;
        int _j;
        _0340_struct* _340_p = wp->work_priv._0340;
        
        for (i = 0; i < 0x100; i += 4) {
            _j = 8;
            if (wp->work_priv._0B40[wp->work_priv._2940[i]._00]._18 & 0x20) {
                _j = 0x10;
            }
            a = 0;
            if (wp->work_priv._2940[i]._02 & 0x80) {
                b = _j << 2;
                _c = -4;
            } else {
                b = 0;
                _c = 4;
            }
            for (j = 0; j < _j; j++) {
                if (wp->work_priv._0000[wp->work_priv._2940[i]._00 + j] != 0) {
                    wp->work_priv._0000[wp->work_priv._2940[i]._00 + j]--;
                    if ((a & 2) == 0) {
                        _340_p->_00[a] = j + wp->work_priv._2940[i]._00;
                        _340_p->_00[a + 1] = b;
                        a += 2;
                    }
                } else if ((a & 2) != 0) {
                    _340_p->_00[a] = j + wp->work_priv._2940[i]._00;
                    _340_p->_00[a + 1] = b;
                    a += 2;
                }
                b += _c;
            }
            if ((a & 2) != 0) {
                _340_p->_00[a] = j + wp->work_priv._2940[i]._00;
                _340_p->_00[a + 1] = b;
                a += 2;
            }
            wp->work_priv._0300[i >> 2] = a;
            _340_p++;
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
        // u32 i;
        for (i = 0; size > (0x8000 << i); i++) {}

        static f32 indtexmtx_obj[2][3] = { { 0.5f, 0.f, 0.f }, { 0.f, 0.0625f, 0.f } };
        indtexmtx_obj[0][0] = 0.5f / (i >= 4 ? (1 << (i - 3)) : 1);
        indtexmtx_obj[1][1] = 0.5f / (i <= 2 ? (1 << (3 - i)) : 1);
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
    static const GXColor color_thres = { 255, 1, 0, 0 };
    GXSetTevColor(GX_TEVREG0, color_thres);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C0, GX_CC_C2, GX_CC_CPREV, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_COMP_GR16_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_APREV, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);

    u32 n_verts = 0;
    for (i = 0; i < 0x100; i += 4) {
        if (c == 0 || (wp->work_priv._2940[i]._02 & 0x20) != 0) {
            n_verts += wp->work_priv._0300[i >> 2];
        }
    }

    u32 idx = 0x100-4;
    u32 idx2 = 0x40-1;
    GXBegin(GX_QUADS, GX_VTXFMT0, n_verts);
    while (TRUE) {
        _0340_struct* _0340_thing = &wp->work_priv._0340[idx2];
        u8* bruh = _0340_thing->_00;
        // u32 scanline_idx = wp->work_priv._2940[idx];
        u32 flags = wp->work_priv._2940[idx]._01;
        u32 flags2;

        if (wp->work_priv._0B40[wp->work_priv._2940[idx]._00]._18 & 0x20) {
            flags2 = wp->work_priv._0B40[wp->work_priv._2940[idx]._00]._08[(flags >> 6) | ((flags & 1) << 2)];
            flags &= (u8)~0x01;
        } else {
            flags2 = wp->work_priv._0B40[wp->work_priv._2940[idx]._00]._08[(flags >> 6) | ((wp->work_priv._0B40[wp->work_priv._2940[idx]._00]._18 >> 1) & 4)];
        }

        // u32 flags3 = wp->work_priv._2940[idx + 2];
        u32 x0 = wp->work_priv._2940[idx]._03 + 128;
        u32 x1 = wp->work_priv._2940[idx]._03 + 136;
        u32 color = ((wp->work_priv._2940[idx]._02 & 3) * 0x10 + 4) * 0x01000000;

        if (c != 0) {
            if ((flags & 0x20) == 0) {
                goto loop_condition;
            }
        }  else {
            if ((flags & 0x20) != 0) {
                color |= 0xFF010000;
            }
        }
        
        u32 s0;
        u32 t0;
        u32 s1;
        u32 s1_2;
        u32 t1;
        u32 t1_2;
        u32 temp;
        // u32 j;

        s0 = 0;
        t0 = (flags2 & (u8)~0x01) * 2;
        temp = ((flags & 0x3F) * 0x20) | ((flags2 & 0x01) * 0x800);

        if (wp->work_priv._2940[idx]._02 & 0x40) {
            s1 = temp + 32;
            s1_2 = temp;
        } else {
            s1 = temp;
            s1_2 = temp + 32;
        }

        for (j = 0; j < wp->work_priv._0300[idx >> 2]; j += 4) {
            u32 y0 = -129 - bruh[0];
            t1 = bruh[1];
            u32 y1 = -129 - bruh[2];
            t1_2 = bruh[3];

            bruh += 4;
            GXPosition2s16(x0, y0);
            GXColor1u32(color);
            GXTexCoord2u16(s0, t0);
            GXTexCoord2u16(s1, t1);
            
            GXPosition2s16(x1, y0);
            GXColor1u32(color);
            GXTexCoord2u16(s0, t0);
            GXTexCoord2u16(s1_2, t1);

            GXPosition2s16(x1, y1);
            GXColor1u32(color);
            GXTexCoord2u16(s0, t0);
            GXTexCoord2u16(s1_2, t1_2);

            GXPosition2s16(x0, y1);
            GXColor1u32(color);
            GXTexCoord2u16(s0, t0);
            GXTexCoord2u16(s1, t1_2);
        }

        
loop_condition:
        if (idx == 0) {
            break;
        }

        idx -= 4;
        idx2--;
    }

    GXEnd();

    if (c != 0) {
        u32 n = ksNesDrawMakeOBJBlankVtxList(wp);

        if (n != 0) {
            GXSetNumChans(1);
            GXSetNumTexGens(0);
            GXSetNumTevStages(1);
            GXSetNumIndStages(0);
            GXSetBlendMode(GX_BM_LOGIC, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
            GXSetTevDirect(GX_TEVSTAGE0);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
            GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
            GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
            
            GXBegin(GX_QUADS, GX_VTXFMT0, n * 2);
            for (u32 i = 0; i < n; i += 2) {
                s16 x1 = (wp->work_priv._0B40[wp->work_priv._0000[i]]._19 & 0x14) == 0x10 ? 136 : 384;

                GXPosition2s16(128, -128 - wp->work_priv._0000[i]);
                GXColor1u32(0x00000000);
                GXPosition2s16(x1, -128 - wp->work_priv._0000[i]);
                GXColor1u32(0x00000000);
                GXPosition2s16(x1, -128 - wp->work_priv._0000[i] - wp->work_priv._0000[i + 1]);
                GXColor1u32(0x00000000);
                GXPosition2s16(128, -128 - wp->work_priv._0000[i] - wp->work_priv._0000[i + 1]);
                GXColor1u32(0x00000000);
            }
            GXEnd();
        }
    }
}

void ksNesDrawOBJMMC5(ksNesCommonWorkObj* wp, ksNesStateObj* sp, u32 c) {
    static const GXColor color_thres = { 255, 1, 0, 0 };
    // clang-format off
    static f32 indtexmtx_obj[2][3] = {
        { 0.5f, 0.0f,    0.0f },
        { 0.0f, 0.0625f, 0.0f },
    };
    // clang-format on

    GXTexObj obj3;
    GXTexObj obj;
    GXTexObj obj2;
    size_t var_r25 = wp->chr_to_i8_buf_size;
    u32 sft;
    u32 var_r3;
    u32 i, j;
    u32 var_r15;
    u32 var_r24;
    u32 x;
    u32 x1, x2, y1, y2;
    u32 u1, u2, v;
    u32 clr;
    u32 flags;
    u8 *work;

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

    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 10);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_TEX_ST, GX_U16, 10);

    GXInitTexObj(&obj, wp->work_priv._8EC0, 8, 4, GX_TF_IA8, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP1);

    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_TRUE, 0x100, 0x101);
    GXSetTexCoordBias(GX_TEXCOORD0, 0, 0);
    
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_8, GX_ITS_1);

    GXSetTevIndirect(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_OFF, GX_ITW_OFF, GX_ITW_OFF, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEX_DISABLE, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVREG2);

    GXInitTexObj(&obj2, wp->work_priv._8E40, 4, 16, GX_TF_IA8, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&obj2, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj2, GX_TEXMAP2);

    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, 60);
    GXSetTexCoordScaleManually(GX_TEXCOORD1, GX_TRUE, 0x100, 0x101);
    GXSetTexCoordBias(GX_TEXCOORD1, 0, 0);
    GXSetIndTexOrder(GX_INDTEXSTAGE1, GX_TEXCOORD1, GX_TEXMAP2);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_8, GX_ITS_1);
    
    sft = 0;
    while (var_r25 > (0x8000 << sft)) {
        sft++;
    }

    indtexmtx_obj[0][0] = 0.5f / (sft >= 4 ? (1 << (sft - 3)) : 1);
    indtexmtx_obj[1][1] = 0.5f / (sft <= 2 ? (1 << (3 - sft)) : 1);
    GXSetIndTexMtx(GX_ITM_0, indtexmtx_obj, 36 + (sft < 4 ? 0 : sft - 3));

    GXSetTevIndirect(GX_TEVSTAGE1, GX_INDTEXSTAGE1, GX_ITF_8, GX_ITB_NONE, GX_ITM_0, GX_ITW_OFF, GX_ITW_0, GX_TRUE, GX_FALSE, GX_ITBA_OFF);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_C2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    
    GXSetTevDirect(GX_TEVSTAGE2);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColor(GX_TEVREG0, color_thres);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C0, GX_CC_C2, GX_CC_CPREV, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_COMP_GR16_GT, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_APREV, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);

    var_r24 = 0;
    for (i = 0; i < ARRAY_COUNT(wp->work_priv._2940); i++) {
        if (c == 0 || (wp->work_priv._2940[i]._02 & 0x20) != 0) {
            var_r24 += (wp->work_priv._0B40[wp->work_priv._2940[i]._00]._18 & 0x20) ? 8 : 4;
        }
    }

    for (i = 0; i < 8; i += 4) {
        GXInitTexObj(&obj3, &wp->chr_to_u8_bufp[(var_r25 >> 3) * i], 1024, var_r25 >> 11, GX_TF_I8, GX_MIRROR, GX_CLAMP, 0);
        GXInitTexObjLOD(&obj3, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&obj3, GX_TEXMAP0);

        // why is this loop value loaded here???
        j = 63 * sizeof(wp->work_priv._2940[0]);
        GXBegin(GX_QUADS, GX_VTXFMT0, var_r24);
        while (TRUE) {
            u8 scanline = ((u8*)wp->work_priv._2940)[j + 0];
            u32 obj_flags = ((u8*)wp->work_priv._2940)[j + 1];
            u32 mode = (wp->work_priv._0B40[scanline]._18 >> 5) & 1;
            u32 palette_bits;
            u32 tmp;

            if (mode != 0) {
                palette_bits = (obj_flags >> 6) | ((obj_flags & 1) << 2);
                palette_bits = ((wp->work_priv._0B40[scanline]._1E << (palette_bits + 1)) & 0x100) | ((wp->work_priv._0B40[scanline]._08[palette_bits]));
                obj_flags &= 0xFE;
            } else {
                palette_bits = (obj_flags >> 6) | (wp->work_priv._0B40[scanline]._18 >> 1) & 4;
                palette_bits = ((wp->work_priv._0B40[scanline]._1E << (palette_bits + 1)) & 0x100) | ((wp->work_priv._0B40[scanline]._08[palette_bits]));
            }


            flags = ((u8*)wp->work_priv._2940)[j + 2];
            x1 = ((u8*)wp->work_priv._2940)[j + 3] + 128;
            x2 = ((u8*)wp->work_priv._2940)[j + 3] + 128 + 8;
            clr = ((((flags & 0x03) * 16) + 4) | (wp->work_priv._0B40[scanline]._18 & 0xC0)) << 24;

            if (c != 0) {
                if ((flags & 0x20) == 0) {
                    goto loop_point;
                }
            } else if ((flags & 0x20) != 0) {
                clr |= 0xFF010000;
            }

            v = (palette_bits << 1) & 0x3FC;
            tmp = ((obj_flags << 5) & 0x7E0) | ((palette_bits << 0xB) & 0x800 & ~0x7E0);
            if (flags & 0x40) {
                u2 = tmp;
                u1 = tmp + 0x20;
            } else {
                u1 = tmp;
                u2 = tmp + 0x20;
            }
            if ((flags & 0x80) != 0) {
                tmp = (-0x81 - scanline) + i;
                y1 = tmp - 8;
                y2 = tmp - 4;
                if (var_r24 != 0) {
                    u1 += 0x20;
                    u2 += 0x20;
                }
            } else {
                tmp = (-0x81 - scanline) - i;
                y1 = tmp;
                y2 = tmp - 4;
            }
            do {
                GXPosition2s16(x1, y1);
                GXColor1u32(clr);
                GXTexCoord2u16(0, v);
                GXTexCoord2u16(u1, 0);
            
                GXPosition2s16(x2, y1);
                GXColor1u32(clr);
                GXTexCoord2u16(0, v);
                GXTexCoord2u16(u2, 0);
            
                GXPosition2s16(x2, y2);
                GXColor1u32(clr);
                GXTexCoord2u16(0, v);
                GXTexCoord2u16(u2, 0x10);
            
                GXPosition2s16(x1, y2);
                GXColor1u32(clr);
                GXTexCoord2u16(0, v);
                GXTexCoord2u16(u1, 0x10);
            
                y1 -= 8;
                y2 -= 8;
                if ((flags & 0x80) != 0) {
                    u1 -= 0x20;
                    u2 -= 0x20;
                } else {
                    u1 += 0x20;
                    u2 += 0x20;
                }
            } while (var_r24-- != 0);

loop_point:
            if (j == 0) break;
            j -= sizeof(wp->work_priv._2940[0]);
        }

        GXEnd();
    }

    if (c == 0) return;

    u32 quads = ksNesDrawMakeOBJBlankVtxList(wp);
    if (quads == 0) return;

    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetNumIndStages(0);
    GXSetBlendMode(GX_BM_LOGIC, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);

    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, quads << 1);
    for (i = 0; i < quads; i += 2) {
        work = (u8*)wp + i;
        x = 0x180;
        if ((wp->work_priv._0B40[(u8)((u8*)wp + i)[0x60]]._19 & 0x14) == 0x10) {
            x = 0x88;
        }
        GXPosition2s16(0x80, -128 - x);
        GXColor1u32(0);
        GXPosition2s16(x, -128 - work[0x60]);
        GXColor1u32(0);
        GXPosition2s16(x, -128 - work[0x60] - work[0x61]);
        GXColor1u32(0);
        GXPosition2s16(0x80, -128 - work[0x60] - work[0x61]);
        GXColor1u32(0);
    }
    GXEnd();
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
    GXTexObj obj;
    u32 i;
    s32 u;
    u8* work;
    u32 cnt;

    GXSetNumChans(0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetNumIndStages(0);
    GXSetBlendMode(GX_BM_LOGIC, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 8);
    
    GXInitTexObj(&obj, (void*)buf, 256, 228, GX_TF_I8, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP0);

    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_TRUE, 0x100, 0x100);
    GXSetTexCoordBias(GX_TEXCOORD0, 0, 0);

    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);

    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
    
    cnt = ksNesDrawMakeOBJAppearVtxList(wp);
    if (cnt == 0) return;

    GXBegin(GX_QUADS, GX_VTXFMT0, cnt * 2);
    
    for (i = 0; i < cnt; i += 2) {
        work = (u8*)wp + i; // if it works...
        u = (wp->work_priv._0B40[(u8)((u8*)wp)[i + 0x60]]._19 & 0x14) == 0x10 ? 8 : 0;
        
        GXPosition2s16(u + 0x80, -128 - work[0x60]);
        GXTexCoord2u16(u, work[0x60] - 8);

        GXPosition2s16(0x180, -128 - work[0x60]);
        GXTexCoord2u16(0x100, work[0x60] - 8);

        GXPosition2s16(0x180, -128 - work[0x60] - work[0x61]);
        GXTexCoord2u16(0x100, work[0x60] + work[0x61] - 8);

        GXPosition2s16(u + 0x80, -128 - work[0x60] - work[0x61]);
        GXTexCoord2u16(u, work[0x60] + work[0x61] - 8);
    }

    GXEnd();
}

void ksNesDrawEmuResult(ksNesCommonWorkObj* wp) {
    static f32 indtexmtx[2][3] = {
        { 0.5f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f }
    };
    static const GXColor black = { 0, 0, 0, 0 };
    static const GXColor color0 = { 0x3A, 0x3A, 0x3A, 0x00 };
    static const GXColor color1 = { 0x71, 0x71, 0x71, 0x00 };
    static const GXColor color2 = { 0x15, 0x15, 0x15, 0x00 };

    u32 cnt;
    u32 i;
    u32 unk_r7;
    u8 y;
    u32 val;
    u32 clr;
    u8 *work;
    GXTexObj obj;
    GXTexObj obj2;

    cnt = 0;
    i = 8;
    unk_r7 = 0xFF;
    for (; i < 228 + 8; i++) {
        val = wp->work_priv._0B40[i]._19 & 0xE1;
        if (val != unk_r7) {
            unk_r7 = val;
            if ((cnt & 1) != 0) {
                wp->work_priv._0000[cnt++] = i - 8;
            }
            wp->work_priv._0000[cnt++] = i - 8;
        }
    }

    if ((cnt & 1) != 0) {
        wp->work_priv._0000[cnt++] = i - 8;
    }
    wp->work_priv._0000[cnt] = 0xFF;

    GXInitTexObj(&obj2, wp->result_bufp, 256, 228, GX_TF_I8, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&obj2, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj2, GX_TEXMAP1);

    GXInitTexObj(&obj, wp->work_priv._2A40, 256, 4, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP0);

    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, 125);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_TRUE, 256, 256);
    GXSetTexCoordBias(GX_TEXCOORD0, 0, 0);

    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexMtx(GX_ITM_0, indtexmtx, 1);

    GXSetTevIndirect(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_0, GX_ITW_0, GX_ITW_0, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);

    cnt = 0;
    for (i = 0; wp->work_priv._0000[i] != 0xFF; i += 2) {
        val = wp->work_priv._0B40[wp->work_priv._0000[i]]._19;
        if ((val & 0xE1) == 0) { 
            cnt += 4;
        }
    }

    if (cnt != 0) {
        GXSetNumChans(0);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetNumIndStages(1);
        
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 8);
        GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);

        GXBegin(GX_QUADS, GX_VTXFMT0, cnt);

        do {
            i -= 2;
            work = ((u8*)wp + i);
            val = wp->work_priv._0B40[work[0x60]]._19 & 0xE1;
            if (val == 0) {
                GXPosition2s16(0x180, -136 - work[0x60]);
                GXTexCoord2u16(0x100, work[0x60]);

                GXPosition2s16(0x180, -136 - work[0x61]);
                GXTexCoord2u16(0x100, work[0x61]);

                GXPosition2s16(0x080, -136 - work[0x61]);
                GXTexCoord2u16(0x000, work[0x61]);

                GXPosition2s16(0x080, -136 - work[0x60]);
                GXTexCoord2u16(0x000, work[0x60]);
            }
        } while (i != 0);
    }

    cnt = 0;
    for (i = 0; wp->work_priv._0000[i] != 0xFF; i += 2) {
        val = wp->work_priv._0B40[wp->work_priv._0000[i]]._19;
        if ((val & 0xE1) != 0) { 
            cnt += 4;
        }
    }

    if (cnt != 0) {
        GXSetNumChans(1);
        GXSetNumTexGens(1);
        GXSetNumTevStages(4);
        GXSetNumIndStages(1);
        
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA,  GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 8);

        GXSetTevIndirect(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_0, GX_ITW_0, GX_ITW_0, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevIndirect(GX_TEVSTAGE1, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_0, GX_ITW_0, GX_ITW_0, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevIndirect(GX_TEVSTAGE2, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_0, GX_ITW_0, GX_ITW_0, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
        GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        
        GXSetTevDirect(GX_TEVSTAGE3);
        GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
        
        GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_ALPHA);
        GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_GREEN, GX_CH_GREEN, GX_CH_GREEN, GX_CH_ALPHA);
        GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);
        
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP2);
        GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP3);
        GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);
        
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_CPREV);
        GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C2, GX_CC_CPREV);
        GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);

        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);

        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        GXSetTevColor(GX_TEVREG0, color0);
        GXSetTevColor(GX_TEVREG1, color1);
        GXSetTevColor(GX_TEVREG2, color2);

        GXBegin(GX_QUADS, GX_VTXFMT0, cnt);

        do {
            i -= 2;
            work = (u8*)wp + i;
            if ((wp->work_priv._0B40[work[0x60]]._19 & 0xE1) != 0) {
                clr = 0x2F2F2F00;
                if ((wp->work_priv._0B40[work[0x60]]._19 & 0x20) != 0) {
                    clr += 0x10000000;
                }
                if ((wp->work_priv._0B40[work[0x60]]._19 & 0x40) != 0) {
                    clr += 0x00100000;
                }
                if ((wp->work_priv._0B40[work[0x60]]._19 & 0x80) != 0) {
                    clr += 0x00001000;
                }

                GXPosition2s16(0x180, -136 - work[0x60]);
                GXColor1u32(clr);
                GXTexCoord2u16(0x100, work[0x60]);

                GXPosition2s16(0x180, -136 - work[0x61]);
                GXColor1u32(clr);
                GXTexCoord2u16(0x100, work[0x61]);

                GXPosition2s16(0x080, -136 - work[0x61]);
                GXColor1u32(clr);
                GXTexCoord2u16(0x000, work[0x61]);

                GXPosition2s16(0x080, -136 - work[0x60]);
                GXColor1u32(clr);
                GXTexCoord2u16(0x000, work[0x60]);
            }
        } while (i != 0);
    }

    GXSetTexCopySrc(128, 136, 256, 228);
    GXSetTexCopyDst(256, 228, GX_TF_RGB565, GX_FALSE);
    GXSetCopyClear(black, 0xFFFFFF);
    GXCopyTex(wp->result_bufp, GX_FALSE);
    GXPixModeSync();
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
