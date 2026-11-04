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
    0xc2, 0x10, 0x80, 0x17, 0x98, 0x17, 0xc0, 0x14, 0xdc, 0x0d, 0xd8, 0x03, 0xd8, 0x00, 0xc8, 0x80,
    0xbc, 0xa0, 0x80, 0xe0, 0x81, 0x21, 0x80, 0xe4, 0x80, 0xac, 0x80, 0x00, 0x80, 0x00, 0x80, 0x00,
    0xe7, 0x39, 0x81, 0x7f, 0xa0, 0xff, 0xd8, 0xd9, 0xfc, 0xd5, 0xfc, 0xcb, 0xfc, 0xc3, 0xe9, 0x20,
    0xe1, 0x80, 0x9d, 0xe0, 0x8e, 0x02, 0x82, 0x4c, 0x82, 0x18, 0x88, 0x42, 0x80, 0x00, 0x80, 0x00,
    0xff, 0xff, 0x82, 0x5f, 0xb6, 0x1f, 0xe9, 0xbf, 0xfd, 0xd9, 0xfd, 0xb3, 0xfd, 0xeb, 0xfe, 0x4b,
    0xfe, 0x86, 0xd2, 0xe0, 0xab, 0x6d, 0xa7, 0x55, 0x83, 0x7f, 0xb1, 0x8c, 0x80, 0x00, 0x80, 0x00,
    0xff, 0xff, 0xc2, 0xff, 0xde, 0xff, 0xea, 0xff, 0xfe, 0xfd, 0xfe, 0xf9, 0xff, 0x16, 0xff, 0x35,
    0xff, 0x74, 0xe7, 0x93, 0xd7, 0xb6, 0xd7, 0xdd, 0xdb, 0xbf, 0xef, 0x7b, 0x80, 0x00, 0x80, 0x00,
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
    C_MTXLookAt(wp->draw_ctx.draw_mtx, &v1, &v2, &v3);
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
    DCFlushRange(wp->draw_ctx.post_process_lut, sizeof(wp->draw_ctx.post_process_lut));
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
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetCurrentMtx(0);
    GXLoadPosMtxImm(wp->draw_ctx.draw_mtx, 0);
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

void ksNesDrawMakeBGIndTex(ksNesCommonWorkObj* wp, u32 mmc3) {
    u32 trigger_col = mmc3 ? 9 : 0x7fff;
    u32 CHR_flag_xor = wp->chr_to_i8_buf_size <= CHR_TO_I8_BUF_SIZE ? (wp->chr_to_i8_buf_size >> 13) : 0x80;
    u32 row;
    u32 col;

    for (row = 8; row < 236; row++) {
        u32 scanline_ctrl0 = wp->draw_ctx.ppu_scanline_regs[row].vram_addr_y;
        u32 scanline_ctrl1 = wp->draw_ctx.ppu_scanline_regs[row].vram_addr_coarse_x;
        u32 mask;
        u32 nibble_acc; // @bug - uninitialized
        u8* patternPtrBase;
        u32 tile_byte;
        u32 palette_bits;
        u32 dst_idx;
        u8* nametable_p;
        u32 flags;

        patternPtrBase = (u8*)wp->draw_ctx.ppu_scanline_regs[row].chr_bank_bg;

        mask = mask = (scanline_ctrl0 & 0x04) ? CHR_flag_xor : 0;

        for (col = 0; col < 34; col++) {
            if (col == trigger_col) {
                patternPtrBase -= 8;
            }

            nametable_p = wp->draw_ctx.ppu_scanline_regs[row].nametable_ptrs[((scanline_ctrl1 >> 8) & 1)];
            if (((s32)nametable_p) >= 0) {
                nibble_acc = (((u32)nametable_p) & 3) | (nibble_acc << 4);
                tile_byte = (((u32)nametable_p) >> 8) & 0xFF;
            } else {
                nibble_acc = (((nametable_p[0x3C0 + ((scanline_ctrl0 & 0xE0) >> 2) + ((scanline_ctrl1 & 0xE0) >> 5)] >> ((((scanline_ctrl1 >> 3) & 2) | (scanline_ctrl0 & 0x10) >> 2))) & 3) & 0x0F) | ((nibble_acc << 4));
                tile_byte = nametable_p[((scanline_ctrl0 & 0xF8) << 2) + ((scanline_ctrl1 >> 3) & 0x1F)];
            }

            palette_bits = patternPtrBase[((wp->draw_ctx.ppu_scanline_regs[row].ppu_ctrl >> 2) & 4) | ((u8)tile_byte >> 6)];

            wp->draw_ctx.bg_tile_index_texture[((((col * 2) & 6)) + (((col * 8) & 0x1E0)) + ((row >> 2) * 288) + (((row * 8) & 0x18))) + 0] = (((palette_bits & 1) << 6) | (tile_byte & 0x3F)) - (col & 1);
            wp->draw_ctx.bg_tile_index_texture[((((col * 2) & 6)) + (((col * 8) & 0x1E0)) + ((row >> 2) * 288) + (((row * 8) & 0x18))) + 1] = (palette_bits >> 1) ^ mask;

            if ((col & 1) != 0) {
                wp->draw_ctx.bg_palette_attr_texture[((col >> 1) & 3) + ((col * 4) & 0xE0) + (((row * 4) & 0x1C) + (row >> 3) * 160)] = nibble_acc;
            }

            scanline_ctrl1 += 8;
        }
    }

    DCFlushRangeNoSync(wp->draw_ctx.bg_tile_index_texture, sizeof(wp->draw_ctx.bg_tile_index_texture));
    DCFlushRangeNoSync(wp->draw_ctx.bg_palette_attr_texture, sizeof(wp->draw_ctx.bg_palette_attr_texture));
}

void ksNesDrawMakeBGIndTexMMC5(ksNesCommonWorkObj* wp, ksNesStateObj* sp) {
    u32 row;
    u32 col;
    u32 scanline_ctrl1;
    u32 tile_byte;
    u32 palette_bits;
    u8* nametable_p;
    u32 banks_mask = sp->chr_banks & 0x1FC;

    u32 scanline_ctrl0;
    u32 nibble_acc;
    u8* patternPtrBase;
    for (row = 8; row < 236; row++) {
        scanline_ctrl0 = wp->draw_ctx.ppu_scanline_regs[row].vram_addr_y;
        scanline_ctrl1 = wp->draw_ctx.ppu_scanline_regs[row].vram_addr_coarse_x;
 // @bug - uninitialized
        patternPtrBase = (u8*)&wp->draw_ctx.ppu_scanline_regs[row].chr_bank_bg;

        for (col = 0; col < 34; col++) {
            nametable_p = wp->draw_ctx.ppu_scanline_regs[row].nametable_ptrs[((scanline_ctrl1 >> 8) & 1)];
            if (((s32)nametable_p) >= 0) {
                nibble_acc = (((u32)nametable_p) & 3) | (nibble_acc << 4);
                tile_byte = (((u32)nametable_p) >> 8) & 0xFF;
            } else {
                nibble_acc = ((nametable_p[0x3C0 + ((scanline_ctrl0 & 0xE0) >> 2) + ((scanline_ctrl1 & 0xE0) >> 5)] >> ((((scanline_ctrl1 >> 3) & 2) | (scanline_ctrl0 & 0x10) >> 2))) & 3) | (nibble_acc << 4);
                tile_byte = nametable_p[((scanline_ctrl0 << 2) & 0x3E0) + ((scanline_ctrl1 >> 3) & 0x1F)];
            }

            // issue in this area too probably
            if (wp->draw_ctx.ppu_scanline_regs[row].mmc5_ext_mode & 0x20) {
                // MMC5 extension ram
                nibble_acc = ((sp->mmc5_extension_ram[((scanline_ctrl1 >> 3) & 0x1F) + ((scanline_ctrl0 << 2) & 0x3E0)] >> 6) & 0x0F) | (nibble_acc & 0xF0);
                palette_bits = ((sp->mmc5_extension_ram[((scanline_ctrl1 >> 3) & 0x1F) + ((scanline_ctrl0 << 2) & 0x3E0)] << 2) & banks_mask) | ((u8)tile_byte >> 6);
            } else {
                palette_bits = patternPtrBase[((wp->draw_ctx.ppu_scanline_regs[row].ppu_ctrl >> 2) & 4) | ((u8)tile_byte >> 6)] | ((wp->draw_ctx.ppu_scanline_regs[row].chr_bank_ext_upper_bg << ((((wp->draw_ctx.ppu_scanline_regs[row].ppu_ctrl >> 2) & 4) | ((u8)tile_byte >> 6)) + 1)) & 0x100);
            }

            wp->draw_ctx.bg_tile_index_texture[((((col * 2) & 6)) + (((col * 8) & 0x1E0)) + ((row >> 2) * 288) + (((row * 8) & 0x18))) + 0] = (((palette_bits & 1) << 6) | (tile_byte & 0x3F)) - (col & 1);
            wp->draw_ctx.bg_tile_index_texture[((((col * 2) & 6)) + (((col * 8) & 0x1E0)) + ((row >> 2) * 288) + (((row * 8) & 0x18))) + 1] = (palette_bits >> 1);

            if ((col & 1) != 0) {
                wp->draw_ctx.bg_palette_attr_texture[((col >> 1) & 3) + ((col * 4) & 0xE0) + (((row * 4) & 0x1C) + (row >> 3) * 160)] = nibble_acc;
            }

            scanline_ctrl1 += 8;
        }
    }

    DCFlushRangeNoSync(wp->draw_ctx.bg_tile_index_texture, sizeof(wp->draw_ctx.bg_tile_index_texture));
    DCFlushRangeNoSync(wp->draw_ctx.bg_palette_attr_texture, sizeof(wp->draw_ctx.bg_palette_attr_texture));
}

#define ksNes_MMC2_LATCH_LO 0xFD // select chr bank 0/2
#define ksNes_MMC2_LATCH_HI 0xFE // select chr bank 1/3

void ksNesDrawMakeBGIndTexMMC2(ksNesCommonWorkObj* wp, u32 default_bank) {
    u32 CHR_flag_xor = wp->chr_to_i8_buf_size <= CHR_TO_I8_BUF_SIZE ? (wp->chr_to_i8_buf_size >> 13) : 0x80;

    u32 mask;
    u32 nibble_acc;
    u8* patternPtrBase;
    u32 mmc2_bank = 0x02;
    u32 idx;
    u32 i;
    u32 j;
    u32 scanline_ctrl1;

    i = 239;
    do {
        scanline_ctrl1 = wp->draw_ctx.ppu_scanline_regs[i].vram_addr_coarse_x;
        idx = (wp->draw_ctx.ppu_scanline_regs[i].vram_addr_y * 4) & 0x3E0;

        for (j = 0; j < 34; j++) {
            u32 val = (wp->draw_ctx.ppu_scanline_regs[i].nametable_ptrs[(scanline_ctrl1 >> 8) & 1] + ((scanline_ctrl1 >> 3) & 0x1F))[idx];

            if (val == ksNes_MMC2_LATCH_HI) {
                mmc2_bank = 0x00;
            } else if (val == ksNes_MMC2_LATCH_LO) {
                mmc2_bank = 0x01;
            }

            scanline_ctrl1 += 8;
        }
    } while (i-- != 0 && mmc2_bank == 0x02);

    // If the bank is still unset, use the default bank
    if (mmc2_bank == 0x02) {
        mmc2_bank = default_bank;
    }

    u32 table_offset;
    for (u32 i = 0; i < 8; i++) {
        u32 scanline_ctrl1 = wp->draw_ctx.ppu_scanline_regs[i].vram_addr_coarse_x;
        table_offset = wp->draw_ctx.ppu_scanline_regs[i].vram_addr_y;

        for (u32 j = 0; j < 34; j++) {
            u32 val = (wp->draw_ctx.ppu_scanline_regs[i].nametable_ptrs[(scanline_ctrl1 >> 8) & 1] + ((scanline_ctrl1 >> 3) & 0x1F))[(table_offset * 4) & 0x3E0];

            if (val == ksNes_MMC2_LATCH_HI) {
                mmc2_bank = 0x00;
            } else if (val == ksNes_MMC2_LATCH_LO) {
                mmc2_bank = 0x01;
            }

            scanline_ctrl1 += 8;
        }
    }

    for (i = 8; i < 236; i++) {
        u32 scanline_ctrl0 = wp->draw_ctx.ppu_scanline_regs[i].vram_addr_y;
        scanline_ctrl1 = wp->draw_ctx.ppu_scanline_regs[i].vram_addr_coarse_x;

 // @bug - uninitialized
        patternPtrBase = wp->draw_ctx.ppu_scanline_regs[i].chr_bank_sprite;
        u32 tile_byte;
        u32 palette_bits;
        u32 dst_idx;
        u8* nametable_p;

        mask = mask = (scanline_ctrl0 & 0x04) ? CHR_flag_xor : 0;

        for (j = 0; j < 34; j++) {
            nametable_p = wp->draw_ctx.ppu_scanline_regs[i].nametable_ptrs[((scanline_ctrl1 >> 8) & 1)];
            if (((s32)nametable_p) >= 0) {
                nibble_acc = (((u32)nametable_p) & 3) | (nibble_acc << 4);
                tile_byte = (((u32)nametable_p) >> 8) & 0xFF;
            } else {
                nibble_acc = (((nametable_p[0x3C0 + ((scanline_ctrl0 & 0xE0) >> 2) + ((scanline_ctrl1 & 0xE0) >> 5)] >> ((((scanline_ctrl1 >> 3) & 2) | (scanline_ctrl0 & 0x10) >> 2))) & 3) & 0x0F) | ((nibble_acc << 4));
                tile_byte = nametable_p[((scanline_ctrl0 << 2) & 0x3E0) + ((scanline_ctrl1 >> 3) & 0x1F)];

                if (tile_byte == ksNes_MMC2_LATCH_HI) {
                    palette_bits = patternPtrBase[((wp->draw_ctx.ppu_scanline_regs[i].ppu_ctrl >> 2) & 4) | mmc2_bank] | 0x03;
                    mmc2_bank = 0x00;
                    goto set;
                } else if (tile_byte == ksNes_MMC2_LATCH_LO) {
                    mmc2_bank = 0x01;
                }
            }

            palette_bits = ((u8)tile_byte >> 6) | patternPtrBase[(((wp->draw_ctx.ppu_scanline_regs[i].ppu_ctrl >> 2) & 4) | mmc2_bank)];

set:

            wp->draw_ctx.bg_tile_index_texture[((((j * 2) & 6)) + (((j * 8) & 0x1E0)) + ((i >> 2) * 288) + (((i * 8) & 0x18))) + 0] = (((palette_bits & 1) << 6) | (tile_byte & 0x3F)) - (j & 1);
            wp->draw_ctx.bg_tile_index_texture[((((j * 2) & 6)) + (((j * 8) & 0x1E0)) + ((i >> 2) * 288) + (((i * 8) & 0x18))) + 1] = (palette_bits >> 1) ^ mask;

            if ((j & 1) != 0) {
                wp->draw_ctx.bg_palette_attr_texture[((j >> 1) & 3) + ((j * 4) & 0xE0) + (((i * 4) & 0x1C) + (i >> 3) * 160)] = nibble_acc;
            }

            scanline_ctrl1 += 8;
        }
    }

    DCFlushRangeNoSync(wp->draw_ctx.bg_tile_index_texture, sizeof(wp->draw_ctx.bg_tile_index_texture));
    DCFlushRangeNoSync(wp->draw_ctx.bg_palette_attr_texture, sizeof(wp->draw_ctx.bg_palette_attr_texture));
}

void ksNesDrawOBJSetupMMC2(ksNesCommonWorkObj* wp) {
    u32 i;
    u32 j;
    u32 k;

    memset(wp->draw_ctx.mmc2_scanline_latch_tiles, 0, KS_NES_SCANLINE_COUNT);
    for (i = 0; i < sizeof(wp->draw_ctx.OAMTable); i += sizeof(ksNesOAMEntry)) {
        // ppu_scanline_regs is the scanline state, OAMTable is list of scanline triggers?
        if ((*(ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + i)).y_pos >= 236 || ((*(ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + i)).tile_index != ksNes_MMC2_LATCH_HI && (*(ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + i)).tile_index != ksNes_MMC2_LATCH_LO)) {
            continue;
        }

        j = (*(ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + i)).y_pos;
        k = (j + 8) + ((wp->draw_ctx.ppu_scanline_regs[j].ppu_ctrl >> 2) & 0x08);
        do {
            wp->draw_ctx.mmc2_scanline_latch_tiles[j] = (*(ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + i)).tile_index;
            j++;
        } while(j < k);
    }

    u32 bank;
    // _0200 is the scanline marker entries
    for (bank = 0, i = 0; i < KS_NES_SCANLINE_COUNT; i++) {
        if (wp->draw_ctx.mmc2_scanline_latch_tiles[i] == ksNes_MMC2_LATCH_HI) {
            bank = 0;
        } else if (wp->draw_ctx.mmc2_scanline_latch_tiles[i] == ksNes_MMC2_LATCH_LO) {
            bank = 1;
        }

        if (bank) {
            wp->draw_ctx.ppu_scanline_regs[i].chr_bank_sprite[0] = wp->draw_ctx.ppu_scanline_regs[i].chr_bank_sprite[1] - 1;
            wp->draw_ctx.ppu_scanline_regs[i].chr_bank_sprite[2] = wp->draw_ctx.ppu_scanline_regs[i].chr_bank_sprite[1] + 1;
            wp->draw_ctx.ppu_scanline_regs[i].chr_bank_sprite[3] = wp->draw_ctx.ppu_scanline_regs[i].chr_bank_sprite[1] + 2;
        } else {
            wp->draw_ctx.ppu_scanline_regs[i].chr_bank_sprite[1] = wp->draw_ctx.ppu_scanline_regs[i].chr_bank_sprite[0] + 1;
            wp->draw_ctx.ppu_scanline_regs[i].chr_bank_sprite[2] = wp->draw_ctx.ppu_scanline_regs[i].chr_bank_sprite[0] + 2;
            wp->draw_ctx.ppu_scanline_regs[i].chr_bank_sprite[3] = wp->draw_ctx.ppu_scanline_regs[i].chr_bank_sprite[0] + 3;
        }
    }
}

void ksNesDrawBG(ksNesCommonWorkObj* wp, ksNesStateObj* sp) {
    static const GXColor color_r_0xf0 = { 240, 0, 0, 0 };
    static f32 indtexmtx_screen[2][3] = {
        {0.5f, 0.0f, 0.0f}, // S offset = (Intensity from bg_tile_index_texture) × 0.5
        {0.0f, 0.0625f, 0.0f}, // T offset = (Alpha from bg_tile_index_texture) × 0.0625 (1/16)
    };

    GXTexObj obj0;
    GXTexObj obj1;
    GXTexObj obj2;
    u32 y;
    u32 line_color;
    u32 scanline;
    u32 curline;
    u32 cnt;
    u32 x0;
    u32 x1;
    u32 color;
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
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 10);
    GXInitTexObj(&obj0, wp->draw_ctx.bg_palette_attr_texture, 40, 256, GX_TF_I4, GX_CLAMP, GX_REPEAT, 0);
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
    GXInitTexObj(&obj1, wp->draw_ctx.bg_tile_index_texture, 36, 256, GX_TF_IA8, GX_CLAMP, GX_CLAMP, 0);
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
            if (sp->mapper == KS_NES_MAPPER_MMC5) {
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
                if ((wp->draw_ctx.ppu_scanline_regs[j].ppumask_flags & KS_NES_PPU_MASK_SHOW_BG) != 0 && j >= 8 && j < 236) {
                    cnt += 2;
                }
                j = wp->draw_ctx.ppu_scanline_regs[j].fine_x_and_next;
            } while (j != 0);

            if (cnt != 0) {
                GXBegin(GX_LINES, GX_VTXFMT0, cnt);

                do {
                    if ((wp->draw_ctx.ppu_scanline_regs[curline].ppumask_flags & KS_NES_PPU_MASK_SHOW_BG) != 0 && curline >= 8 && curline < 236) {
                        if ((wp->draw_ctx.ppu_scanline_regs[curline].ppumask_flags & KS_NES_PPU_MASK_SHOW_BG_LEFT) == 0) {
                            x0 = 0x80 + 8;
                            x1 = (wp->draw_ctx.ppu_scanline_regs[curline].vram_addr_coarse_x & 0x07) + 8;
                        } else {
                            x0 = 0x80 - (wp->draw_ctx.ppu_scanline_regs[curline].vram_addr_coarse_x & 0x07);
                            x1 = 0;
                        }

                        color = (wp->draw_ctx.ppu_scanline_regs[curline].ppu_ctrl & 0xC0) << 24;

                        GXPosition2s16(x0, -0x81 - curline);
                        GXColor1u32(color);
                        GXTexCoord2u16(x1, curline);

                        GXPosition2s16(x0 + 0x100 + 8, -0x81 - curline);
                        GXColor1u32(color);
                        GXTexCoord2u16(x1 + 0x100 + 8, curline);
                    }

                    curline = wp->draw_ctx.ppu_scanline_regs[curline].fine_x_and_next;
                } while (curline != 0);

                GXEnd();
            }
        }
    }

    cnt = 0;
    for (i = 8; i < 236; i++) {
        if ((wp->draw_ctx.ppu_scanline_regs[i].ppumask_flags & KS_NES_PPU_MASK_SHOW_BG) == 0) {
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
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetTevDirect(GX_TEVSTAGE0);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);

        GXBegin(GX_LINES, GX_VTXFMT0, cnt);

        for (scanline = 8; scanline < 236; scanline++) {

            if ((wp->draw_ctx.ppu_scanline_regs[scanline].ppumask_flags & KS_NES_PPU_MASK_SHOW_BG) == 0) {
                y = -0x81 - scanline;
                line_color = (wp->draw_ctx.ppu_scanline_regs[scanline].ppu_ctrl & 0xC0) << 24;

                GXPosition2s16(0x80, y);
                GXColor1u32(line_color);

                GXPosition2s16(0x180, y);
                GXColor1u32(line_color);
            }
        }

        GXEnd();
    }
}

u32 ksNesDrawMakeOBJBlankVtxList(ksNesCommonWorkObj* wp) {
    u32 ret = 0;
    u32 comparison_mask = KS_NES_PPU_MASK_SPRITES_COMBINED;
    int i;

    for (i = 8; i < ARRAY_COUNT(wp->draw_ctx.ppu_scanline_regs); i++) {
        int bMask = wp->draw_ctx.ppu_scanline_regs[i].ppumask_flags & KS_NES_PPU_MASK_SPRITES_COMBINED;
        if (bMask != comparison_mask && ((bMask != 0) || (comparison_mask != KS_NES_PPU_MASK_SHOW_SPRITES_LEFT)) &&
            (bMask != KS_NES_PPU_MASK_SHOW_SPRITES_LEFT || comparison_mask != 0)) {
            if ((ret & 1) != 0) {
                wp->draw_ctx.scanline_y_coords[ret] = i - wp->draw_ctx.scanline_y_coords[ret - 1];
                ret++;
            }
            if ((comparison_mask == KS_NES_PPU_MASK_SPRITES_COMBINED) || (wp->draw_ctx.ppu_scanline_regs[i].ppumask_flags & KS_NES_PPU_MASK_SHOW_SPRITES) == 0) {
                wp->draw_ctx.scanline_y_coords[ret++] = i;
            }
            comparison_mask = wp->draw_ctx.ppu_scanline_regs[i].ppumask_flags & KS_NES_PPU_MASK_SPRITES_COMBINED;
        }
    }

    if (ret & 1) {
        wp->draw_ctx.scanline_y_coords[ret] = i - wp->draw_ctx.scanline_y_coords[ret - 1];
        ret++;
    }
    return ret;
}

u32 ksNesDrawMakeOBJAppearVtxList(ksNesCommonWorkObj* wp) {
    u32 ret = 0;
    u32 comparison_mask = 0;
    int i;

    for (i = 8; i < ARRAY_COUNT(wp->draw_ctx.ppu_scanline_regs); i++) {
        int bMask = wp->draw_ctx.ppu_scanline_regs[i].ppumask_flags & KS_NES_PPU_MASK_SPRITES_COMBINED;
        if (bMask != comparison_mask && ((bMask != 0) || (comparison_mask != KS_NES_PPU_MASK_SHOW_SPRITES_LEFT)) &&
            (bMask != KS_NES_PPU_MASK_SHOW_SPRITES_LEFT || comparison_mask != 0)) {
            if ((ret & 1) != 0) {
                wp->draw_ctx.scanline_y_coords[ret] = i - wp->draw_ctx.scanline_y_coords[ret - 1];
                ret++;
            }
            if ((wp->draw_ctx.ppu_scanline_regs[i].ppumask_flags & KS_NES_PPU_MASK_SHOW_SPRITES)) {
                wp->draw_ctx.scanline_y_coords[ret++] = i;
            }
            comparison_mask = wp->draw_ctx.ppu_scanline_regs[i].ppumask_flags & KS_NES_PPU_MASK_SPRITES_COMBINED;
        }
    }

    if (ret & 1) {
        wp->draw_ctx.scanline_y_coords[ret] = i - wp->draw_ctx.scanline_y_coords[ret - 1];
        ret++;
    }
    return ret;
}

void ksNesDrawOBJ(ksNesCommonWorkObj* wp, ksNesStateObj* state, u32 sprite_priority_pass) {
    u32 size = wp->chr_to_i8_buf_size <= CHR_TO_I8_BUF_SIZE ? wp->chr_to_i8_buf_size : CHR_TO_I8_BUF_SIZE;

    GXTexObj tex_obj0;
    GXTexObj tex_obj1;
    GXTexObj tex_obj2;
    u32 i;
    u32 j;

    u8* quad_pairs;
    u32 idx;

    unsigned int color;

    u32 t1;
    u32 t1_2;
    u32 y0, y1;
    u32 s0, oam_attrs, tile_index, flags2;

    int v_offset;
    int v_step;
    // check the pass is for foreground sprites
    if (sprite_priority_pass == 0) {
        u32 i;

        for (i = 0; i < KS_NES_SCANLINE_SPRITE_OVERDRAW_COUNT; i++) {
            wp->draw_ctx.sprite_scanline_limit[i] = i < KS_NES_SCANLINE_COUNT ? ((state->frame_flags & KS_NES_FLAG_NINES_OVER_MODE) ? 255 : KS_NES_SPRITES_PER_SCANLINE) : 0;

            // Disable sprites if the ppu's config on this scanline doesn't have sprites enabled.
            // @BUG - ppu_scanline_regs only has 240 entries, but this loop iterates 272 times.
            // The final 32 iterations read beyond the scanline array into the
            // following work data, treating those bytes as PPU mask flags.
#ifndef BUGFIXES
            if ((wp->draw_ctx.ppu_scanline_regs[i].ppumask_flags & KS_NES_PPU_MASK_SHOW_SPRITES) == 0) {
                wp->draw_ctx.sprite_scanline_limit[i] = 0;
            }
#else
            if (i < KS_NES_SCANLINE_COUNT && (wp->draw_ctx.ppu_scanline_regs[i].ppumask_flags & KS_NES_PPU_MASK_SHOW_SPRITES) == 0) {
                wp->draw_ctx.sprite_scanline_limit[i] = 0;
            }
#endif
        }

        if (state->prg_size == 0x40000 && memcmp(state->prgromp + 0x3ffe9, "MARIO 3", 7) == 0) {
            for (i = 0; i < ARRAY_COUNT(wp->draw_ctx.ppu_scanline_regs); i++) {
                // This is a hack for SMB3 where the emulator was drawing sprites (OBJ) on transition screens because
                // it isn't accurate enough. So, when this specific bank setup is detected on the MMC3 chip's alternate
                // banks, sprites are entirely disabled by setting the per-scanline limit to 0.
                if (wp->draw_ctx.ppu_scanline_regs[i].chr_bank_bg_mmc3[1] == 0x7e7e7e7e) {
                    wp->draw_ctx.sprite_scanline_limit[i] = 0;
                }
            }
        }

        memset(wp->draw_ctx.sprite_quad_data, 0, sizeof(wp->draw_ctx.sprite_quad_data));
        u32 oam_offset;

        int pair_count;
        int sprite_height;
        ksNesSpriteQuadData* quad_p = wp->draw_ctx.sprite_quad_data;

        for (oam_offset = 0; oam_offset < 0x100; oam_offset += 4) {
            sprite_height = 8; // 8x8 sprite
            if (wp->draw_ctx.ppu_scanline_regs[((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + oam_offset))->y_pos].ppu_ctrl & KS_NES_PPU_CTRL_SPRITE_SIZE) {
                sprite_height = 16; // 8x16 sprite
            }
            pair_count = 0;
            if (((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + oam_offset))->attributes & KS_NES_OAM_ATTR_FLIP_VERTICAL) {
                v_offset = sprite_height << 2;
                v_step = -4;
            } else {
                v_offset = 0;
                v_step = 4;
            }
            for (j = 0; j < sprite_height; j++) {
                u32 ypos = ((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + oam_offset))->y_pos;
                ypos += j;
                if ((*(&wp->draw_ctx.sprite_scanline_limit[((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + oam_offset))->y_pos] + j)) != 0) {
                    (*(&wp->draw_ctx.sprite_scanline_limit[((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + oam_offset))->y_pos] + j))--;
                    if ((pair_count & 2) == 0) {
                        quad_p->y_and_v_pairs[pair_count] = ((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + oam_offset))->y_pos + j;
                        quad_p->y_and_v_pairs[pair_count + 1] = v_offset;
                        pair_count += 2;
                    }
                } else if ((pair_count & 2) != 0) {
                    quad_p->y_and_v_pairs[pair_count] = ((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + oam_offset))->y_pos + j;
                    quad_p->y_and_v_pairs[pair_count + 1] = v_offset;
                    pair_count += 2;
                }
                v_offset += v_step;
            }
            if ((pair_count & 2) != 0) {
                quad_p->y_and_v_pairs[pair_count] = ((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + oam_offset))->y_pos + j;
                quad_p->y_and_v_pairs[pair_count + 1] = v_offset;
                pair_count += 2;
            }
            wp->draw_ctx.sprite_vertex_count[oam_offset >> 2] = pair_count;
            quad_p++;

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
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 10);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_TEX_ST, GX_U16, 10);
    GXInitTexObj(&tex_obj0, wp->chr_to_u8_bufp, 0x400, (u16)(size >> 10), GX_TF_I8, GX_MIRROR, GX_CLAMP, 0);
    GXInitTexObjLOD(&tex_obj0, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&tex_obj0, GX_TEXMAP0);
#ifndef BUGFIXES
    GXInitTexObj(&tex_obj1, wp->draw_ctx.sprite_chr_bank_lut, 8, 4, GX_TF_IA8, GX_CLAMP, GX_CLAMP, 0);
#else
    GXInitTexObj(&tex_obj1, wp->draw_ctx.sprite_chr_bank_lut, 5, 4, GX_TF_IA8, GX_CLAMP, GX_CLAMP, 0);
#endif
    GXInitTexObjLOD(&tex_obj1, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&tex_obj1, GX_TEXMAP1);
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
    GXInitTexObj(&tex_obj2, wp->draw_ctx.sprite_indirect_lut, 4, 16, GX_TF_IA8, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&tex_obj2, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, 0, 0, GX_ANISO_1);
    GXLoadTexObj(&tex_obj2, GX_TEXMAP2);
    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, 0x3c);
    GXSetTexCoordScaleManually(GX_TEXCOORD1, GX_TRUE, 0x100, 0x101);
    GXSetTexCoordBias(GX_TEXCOORD1, 0, 0);
    GXSetIndTexOrder(GX_INDTEXSTAGE1, GX_TEXCOORD1, GX_TEXMAP2);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_8, GX_ITS_1);
    {

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

    i = 0;
    for (j = 0; j < sizeof(wp->draw_ctx.OAMTable); j += 4) {
        if (sprite_priority_pass == 0 || (wp->draw_ctx.oam_bytes[j + 2] & KS_NES_OAM_ATTR_PRIORITY) != 0) {
            i += wp->draw_ctx.sprite_vertex_count[j >> 2];
        }
    }

    idx = sizeof(wp->draw_ctx.OAMTable) - sizeof(ksNesOAMEntry);
    u32 idx2 = ARRAY_COUNT(wp->draw_ctx.OAMTable) - 1;
    GXBegin(GX_QUADS, GX_VTXFMT0, i);
    while (TRUE) {

        quad_pairs = wp->draw_ctx.sprite_quad_data[idx2].y_and_v_pairs;
        tile_index = ((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + idx))->tile_index;

        if (wp->draw_ctx.ppu_scanline_regs[((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + idx))->y_pos].ppu_ctrl & KS_NES_PPU_CTRL_SPRITE_SIZE) {
            // 8x16 sprite
            flags2 = wp->draw_ctx.ppu_scanline_regs[((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + idx))->y_pos].chr_bank_sprite[(tile_index >> 6) | ((tile_index & KS_NES_OAM_TILE_BANK) << 2)];
            tile_index &= KS_NES_OAM_TILE_IDX;
        } else {
            // 8x8 sprite
            flags2 = wp->draw_ctx.ppu_scanline_regs[((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + idx))->y_pos].chr_bank_sprite[(tile_index >> 6) | ((wp->draw_ctx.ppu_scanline_regs[((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + idx))->y_pos].ppu_ctrl >> 1) & 4)];
        }

        oam_attrs = ((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + idx))->attributes;
        u32 t0;
        u32 x0, x1;
        x0 = ((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + idx))->x_pos + 128;
        x1 = ((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + idx))->x_pos + 136;
        color = (((oam_attrs & KS_NES_OAM_ATTR_PALETTE_MASK) * 16 + 4) * 0x01000000);

        if (sprite_priority_pass != 0) {
            // We're in the BG pass so skip if the sprite is supposed to be drawn in front of the BG
            if ((oam_attrs & KS_NES_OAM_ATTR_PRIORITY) == 0) {
                goto loop_condition;
            }
        } else {
            // We're in the FG pass
            if ((oam_attrs & KS_NES_OAM_ATTR_PRIORITY) != 0) {
                color |= 0xFF010000;
            }
        }

        u32 s1, s1_2;
        s0 = 0;
        t0 = (flags2 & 0xFE) * 2; // select chr bank offset
        flags2 = ((tile_index & 0x3F) * 0x20) | ((flags2 & 0x01) * 0x800); // flags2 bit0 determines the pattern table

        if (((ksNesOAMEntry*)((u8*)wp->draw_ctx.OAMTable + idx))->attributes & KS_NES_OAM_ATTR_FLIP_HORIZONTAL) {
            s1 = flags2 + 32;
            s1_2 = flags2;
        } else {
            s1 = flags2;
            s1_2 = flags2 + 32;
        }

        for (j = 0; j < wp->draw_ctx.sprite_vertex_count[idx >> 2]; j += 4) {
            y0 = -129 - quad_pairs[0];
            t1 = quad_pairs[1];
            y1 = -129 - quad_pairs[2];
            t1_2 = quad_pairs[3];

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
            quad_pairs += 4;
        }

loop_condition:
        if (idx == 0) {
            break;
        }

        idx2--;
        idx -= 4;
    }

    GXEnd();

    if (sprite_priority_pass != 0) {
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
                int x1 = (wp->draw_ctx.ppu_scanline_regs[wp->draw_ctx.scanline_y_coords[i]].ppumask_flags & KS_NES_PPU_MASK_SPRITES_COMBINED) == KS_NES_PPU_MASK_SHOW_SPRITES ? 136 : 384;

                GXPosition2s16(128, -128 - wp->draw_ctx.scanline_y_coords[i]);
                GXColor1u32(0x00000000);
                GXPosition2s16(x1, -128 - wp->draw_ctx.scanline_y_coords[i]);
                GXColor1u32(0x00000000);
                GXPosition2s16(x1, -128 - wp->draw_ctx.scanline_y_coords[i] - wp->draw_ctx.scanline_y_coords[i + 1]);
                GXColor1u32(0x00000000);
                GXPosition2s16(128, -128 - wp->draw_ctx.scanline_y_coords[i] - wp->draw_ctx.scanline_y_coords[i + 1]);
                GXColor1u32(0x00000000);
            }
            GXEnd();
        }
    }
}

void ksNesDrawOBJMMC5(ksNesCommonWorkObj* wp, ksNesStateObj* sp, u32 sprite_priority_pass) {
    GXTexObj obj3;
    GXTexObj obj;
    GXTexObj obj2;
    static f32 indtexmtx_obj[2][3] = {
        { 0.5f, 0.0f,    0.0f },
        { 0.0f, 0.0625f, 0.0f },
    };
    static const GXColor color_thres = { 255, 1, 0, 0 };
    size_t var_r25 = wp->chr_to_i8_buf_size;
    u32 j;
    u32 v;
    u32 size_mode;
    u32 i;
    u32 x1;
    u32 x2;
    u32 y1;
    u32 y2;
    u32 scanline;
    u32 u1;
    u32 u2;
    u32 clr;
    u32 bank;
    u32 flip_vertical;
    u32 tile_idx;
    u32 palette_bits;
    u32 tmp;
    u32 color_base;
    u32 oam_offset;
    u32 actual_color;

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

#ifndef BUGFIXES
    GXInitTexObj(&obj, wp->draw_ctx.sprite_chr_bank_lut, 8, 4, GX_TF_IA8, GX_CLAMP, GX_CLAMP, 0);
#else
    GXInitTexObj(&GStack_9c, wp->draw_ctx.sprite_chr_bank_lut, 5, 4, GX_TF_IA8, GX_CLAMP, GX_CLAMP, 0);
#endif
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

    GXInitTexObj(&obj2, wp->draw_ctx.sprite_indirect_lut, 4, 16, GX_TF_IA8, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&obj2, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj2, GX_TEXMAP2);

    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, 60);
    GXSetTexCoordScaleManually(GX_TEXCOORD1, GX_TRUE, 0x100, 0x101);
    GXSetTexCoordBias(GX_TEXCOORD1, 0, 0);
    GXSetIndTexOrder(GX_INDTEXSTAGE1, GX_TEXCOORD1, GX_TEXMAP2);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE1, GX_ITS_8, GX_ITS_1);

    {
        u32 shift = 0;
        while (var_r25 > (0x8000 << shift)) {
            shift++;
        }

        indtexmtx_obj[0][0] = 0.5f / (shift >= 4 ? (1 << (shift - 3)) : 1);
        indtexmtx_obj[1][1] = 0.5f / (shift <= 2 ? (1 << (3 - shift)) : 1);
        GXSetIndTexMtx(GX_ITM_0, indtexmtx_obj, 36 + (shift < 4 ? 0 : shift - 3));
    }

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

    i = 0;
    for (oam_offset = 0; oam_offset < sizeof(wp->draw_ctx.OAMTable); oam_offset += sizeof(ksNesOAMEntry)) {
        if (sprite_priority_pass == 0 || (wp->draw_ctx.oam_bytes[oam_offset + 2] & KS_NES_OAM_ATTR_PRIORITY) != 0) {
            i += (wp->draw_ctx.ppu_scanline_regs[wp->draw_ctx.oam_bytes[oam_offset + 0]].ppu_ctrl & KS_NES_PPU_CTRL_SPRITE_SIZE) ? 8 : 4;
        }
    }

    for (bank = 0; bank < 8; bank += 4) {
        GXInitTexObj(&obj3, &wp->chr_to_u8_bufp[(var_r25 >> 3) * bank], 1024, var_r25 >> 11, GX_TF_I8, GX_MIRROR, GX_CLAMP, 0);
        GXInitTexObjLOD(&obj3, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&obj3, GX_TEXMAP0);

        // why is this loop value loaded here???
        j = (ARRAY_COUNT(wp->draw_ctx.OAMTable) - 1) * sizeof(wp->draw_ctx.OAMTable[0]);
        GXBegin(GX_QUADS, GX_VTXFMT0, i);
        while (TRUE) {
            tile_idx = wp->draw_ctx.oam_bytes[j + 1]; // loading tile index & bank
            scanline = wp->draw_ctx.oam_bytes[j + 0];
            size_mode = (wp->draw_ctx.ppu_scanline_regs[(u8)scanline].ppu_ctrl >> 5) & 1; // sprite size mode, 0 = 8x8, 1 = 8x16

            if (size_mode != 0) {
                // 8x16 sprite
                palette_bits = ((wp->draw_ctx.ppu_scanline_regs[scanline].chr_bank_ext_upper_sprite << (((tile_idx >> 6) | ((tile_idx & KS_NES_OAM_TILE_BANK) << 2)) + 1)) & 0x100) | wp->draw_ctx.ppu_scanline_regs[scanline].chr_bank_sprite[((tile_idx >> 6) | ((tile_idx & KS_NES_OAM_TILE_BANK) << 2))];
                tile_idx &= KS_NES_OAM_TILE_IDX;
            } else {
                // 8x8 sprite
                tmp = (tile_idx >> 6) | (wp->draw_ctx.ppu_scanline_regs[scanline].ppu_ctrl >> 1) & 4;
                palette_bits = ((wp->draw_ctx.ppu_scanline_regs[scanline].chr_bank_ext_upper_sprite << (tmp + 1)) & 0x100) | wp->draw_ctx.ppu_scanline_regs[scanline].chr_bank_sprite[tmp];
            }

            color_base = ((wp->draw_ctx.oam_bytes[j + 2] & KS_NES_OAM_ATTR_PALETTE_MASK) * 16) + 4;
            clr = (color_base | (wp->draw_ctx.ppu_scanline_regs[(u8)scanline].ppu_ctrl & (KS_NES_PPU_CTRL_NMI_ENABLE | KS_NES_PPU_CTRL_MASTER_SLAVE))) << 24;
            x1 = wp->draw_ctx.oam_bytes[j + 3] + 128; // OAM X position
            x2 = wp->draw_ctx.oam_bytes[j + 3] + 128 + 8; // OAM X position + 8

            if (sprite_priority_pass != 0) {
                if ((wp->draw_ctx.oam_bytes[j + 2] & KS_NES_OAM_ATTR_PRIORITY) == 0) {
                    goto loop_point;
                }
            } else if ((wp->draw_ctx.oam_bytes[j + 2] & KS_NES_OAM_ATTR_PRIORITY) != 0) {
                clr |= 0xFF010000;
            }

            v = (palette_bits << 1) & 0x3FC;
            tmp = ((tile_idx << 5) & 0x7E0) | ((palette_bits << 0xB) & 0x800 & ~0x7E0);
            if (wp->draw_ctx.oam_bytes[j + 2] & KS_NES_OAM_ATTR_FLIP_HORIZONTAL) {
                u2 = tmp;
                u1 = tmp + 0x20;
            } else {
                u1 = tmp;
                u2 = tmp + 0x20;
            }
            flip_vertical = wp->draw_ctx.oam_bytes[j + 2] & KS_NES_OAM_ATTR_FLIP_VERTICAL;
            if (flip_vertical != 0) {
                tmp = (-0x81 - scanline) + bank;
                y1 = tmp - 8;
                y2 = tmp - 4;
                if (size_mode != 0) {
                    u1 += 0x20;
                    u2 += 0x20;
                }
            } else {
                tmp = (-0x81 - scanline) - bank;
                y1 = tmp;
                y2 = tmp - 4;
            }

            do {
                GXPosition2s16(x1, y1);
                GXColor1u32((u32)clr);
                GXTexCoord2u16(0, v);
                GXTexCoord2u16(u1, 0);

                GXPosition2s16(x2, y1);
                GXColor1u32((u32)clr);
                GXTexCoord2u16(0, v);
                GXTexCoord2u16(u2, 0);

                GXPosition2s16(x2, y2);
                GXColor1u32((u32)clr);
                GXTexCoord2u16(0, v);
                GXTexCoord2u16(u2, 0x10);

                GXPosition2s16(x1, y2);
                GXColor1u32((u32)clr);
                GXTexCoord2u16(0, v);
                GXTexCoord2u16(u1, 0x10);

                y1 -= 8;
                y2 -= 8;
                if (flip_vertical != 0) {
                    u1 -= 0x20;
                    u2 -= 0x20;
                } else {
                    u1 += 0x20;
                    u2 += 0x20;
                }
            } while (size_mode-- != 0);

loop_point:
            if (j == 0) break;
            j -= sizeof(ksNesOAMEntry);
        }

        GXEnd();
    }

    if (sprite_priority_pass != 0) {
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
                int x1 = (wp->draw_ctx.ppu_scanline_regs[wp->draw_ctx.scanline_y_coords[i]].ppumask_flags & KS_NES_PPU_MASK_SPRITES_COMBINED) == KS_NES_PPU_MASK_SHOW_SPRITES ? 136 : 384;

                GXPosition2s16(128, -128 - wp->draw_ctx.scanline_y_coords[i]);
                GXColor1u32(0x00000000);
                GXPosition2s16(x1, -128 - wp->draw_ctx.scanline_y_coords[i]);
                GXColor1u32(0x00000000);
                GXPosition2s16(x1, -128 - wp->draw_ctx.scanline_y_coords[i] - wp->draw_ctx.scanline_y_coords[i + 1]);
                GXColor1u32(0x00000000);
                GXPosition2s16(128, -128 - wp->draw_ctx.scanline_y_coords[i] - wp->draw_ctx.scanline_y_coords[i + 1]);
                GXColor1u32(0x00000000);
            }
            GXEnd();
        }
    }
}

void ksNesDrawFlushEFBToRed8(u8* buf) {
    static const GXColor black = { 0, 0, 0, 0 };
    GXSetTexCopySrc(128, 136, 256, 228);
    GXSetTexCopyDst(256, 228, GX_CTF_R8, GX_FALSE);
    GXSetCopyClear(black, 0xffffff);
    GXCopyTex(buf, GX_FALSE);
    GXPixModeSync();
    GXInvalidateTexAll();
}

void ksNesDrawOBJI8ToEFB(ksNesCommonWorkObj* wp, u8* buf) {
    GXTexObj obj;
    u32 i;
    u32 x;
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

    for (i = 0; i < cnt; i += sizeof(ksNesScanlineYCoords)) {
        ksNesScanlineYCoords* scanline_y_coords = KS_NES_TYPE_FROM_DRAW_CTX_SCANLINE_BUF_OFS(ksNesScanlineYCoords, wp->draw_ctx, i);
        x = (wp->draw_ctx.ppu_scanline_regs[(u8)KS_NES_TYPE_FROM_DRAW_CTX_SCANLINE_BUF_OFS(ksNesScanlineYCoords, wp->draw_ctx, i)->top].ppumask_flags & KS_NES_PPU_MASK_SPRITES_COMBINED) == KS_NES_PPU_MASK_SHOW_SPRITES ? 8 : 0;

        GXPosition2s16(x + 0x80, -128 - scanline_y_coords->top);
        GXTexCoord2u16(x, scanline_y_coords->top - 8);

        GXPosition2s16(0x180, -128 - scanline_y_coords->top);
        GXTexCoord2u16(0x100, scanline_y_coords->top - 8);

        GXPosition2s16(0x180, -128 - scanline_y_coords->top - scanline_y_coords->bottom);
        GXTexCoord2u16(0x100, scanline_y_coords->top + scanline_y_coords->bottom - 8);

        GXPosition2s16(x + 0x80, -128 - scanline_y_coords->top - scanline_y_coords->bottom);
        GXTexCoord2u16(x, scanline_y_coords->top + scanline_y_coords->bottom - 8);
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
    u32 color_effects_state;
    u8 y;
    u32 val;
    u32 clr;
    ksNesScanlineYCoords* scanline_y_coords;
    GXTexObj obj;
    GXTexObj obj2;

    cnt = 0;
    for (i = 8, color_effects_state = 0xFF; i < ARRAY_COUNT(wp->draw_ctx.ppu_scanline_regs) - 4; i++) {
        val = wp->draw_ctx.ppu_scanline_regs[i].ppumask_flags & KS_NES_PPU_MASK_COLOR_EFFECTS;
        if (val != color_effects_state) {
            color_effects_state = val;
            if ((cnt & 1) != 0) {
                wp->draw_ctx.scanline_y_coords[cnt++] = i - 8;
            }
            wp->draw_ctx.scanline_y_coords[cnt++] = i - 8;
        }
    }

    if ((cnt & 1) != 0) {
        wp->draw_ctx.scanline_y_coords[cnt++] = i - 8;
    }
    wp->draw_ctx.scanline_y_coords[cnt] = 0xFF;

    GXInitTexObj(&obj2, wp->result_bufp, KS_NES_WIDTH, KS_NES_HEIGHT, GX_TF_I8, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&obj2, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj2, GX_TEXMAP1);

    // Sampling LUT for applying color effects like color emphasis (I think)
    GXInitTexObj(&obj, wp->draw_ctx.post_process_lut, 256, 4, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, 0);
    GXInitTexObjLOD(&obj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&obj, GX_TEXMAP0);

    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60);
    GXSetTexCoordScaleManually(GX_TEXCOORD0, GX_TRUE, 256, 256);
    GXSetTexCoordBias(GX_TEXCOORD0, 0, 0);

    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD0, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexMtx(GX_ITM_0, indtexmtx, 1);

    GXSetTevIndirect(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_ITF_8, GX_ITB_NONE, GX_ITM_0, GX_ITW_0, GX_ITW_0, GX_FALSE, GX_FALSE, GX_ITBA_OFF);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);

    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);

    // Count non-grayscale scanlines
    cnt = 0;
    for (i = 0; wp->draw_ctx.scanline_y_coords[i] != 0xFF; i += sizeof(ksNesScanlineYCoords)) {
        val = wp->draw_ctx.ppu_scanline_regs[wp->draw_ctx.scanline_y_coords[i]].ppumask_flags;
        if ((val & KS_NES_PPU_MASK_COLOR_EFFECTS) == 0) {
            cnt += 4; // has color and no color emphasis
        }
    }

    // Draw non-grayscale scanlines
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
            i -= sizeof(ksNesScanlineYCoords);

            val = wp->draw_ctx.ppu_scanline_regs[wp->draw_ctx.scanline_y_coords[i]].ppumask_flags & KS_NES_PPU_MASK_COLOR_EFFECTS;
            if (val == 0) {
                GXPosition2s16(KS_NES_WIDTH + KS_NES_CENTER_X, -KS_NES_CENTER_Y - wp->draw_ctx.scanline_y_coords[i]);
                GXTexCoord2u16(256, wp->draw_ctx.scanline_y_coords[i]);

                GXPosition2s16(KS_NES_WIDTH + KS_NES_CENTER_X, -KS_NES_CENTER_Y - wp->draw_ctx.scanline_y_coords[i + 1]);
                GXTexCoord2u16(256, wp->draw_ctx.scanline_y_coords[i + 1]);

                GXPosition2s16(KS_NES_CENTER_X, -KS_NES_CENTER_Y - wp->draw_ctx.scanline_y_coords[i + 1]);
                GXTexCoord2u16(0, wp->draw_ctx.scanline_y_coords[i + 1]);

                GXPosition2s16(KS_NES_CENTER_X, -KS_NES_CENTER_Y - wp->draw_ctx.scanline_y_coords[i]);
                GXTexCoord2u16(0, wp->draw_ctx.scanline_y_coords[i]);
            }
        } while (i != 0);
        GXEnd();
    }

    // Count grayscale scanlines
    cnt = 0;
    for (i = 0; wp->draw_ctx.scanline_y_coords[i] != 0xFF; i += 2) {
        val = wp->draw_ctx.ppu_scanline_regs[wp->draw_ctx.scanline_y_coords[i]].ppumask_flags;
        if ((val & KS_NES_PPU_MASK_COLOR_EFFECTS) != 0) {
            cnt += 4;
        }
    }

    // Draw grayscale scanlines
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
            i -= sizeof(ksNesScanlineYCoords);

            if ((wp->draw_ctx.ppu_scanline_regs[wp->draw_ctx.scanline_y_coords[i]].ppumask_flags & KS_NES_PPU_MASK_COLOR_EFFECTS) != 0) {
                clr = 0x2F2F2F00; // If any of the grayscale color bits are set, force the color to RGB8 (47, 47, 47) (chroma removed, only luma left)

                // For each emphasis bit set, add one to the luma value to get 48 (0x30).
                if ((wp->draw_ctx.ppu_scanline_regs[wp->draw_ctx.scanline_y_coords[i]].ppumask_flags & KS_NES_PPU_MASK_EMPHASIZE_RED) != 0) {
                    clr += 0x10000000;
                }
                if ((wp->draw_ctx.ppu_scanline_regs[wp->draw_ctx.scanline_y_coords[i]].ppumask_flags & KS_NES_PPU_MASK_EMPHASIZE_GREEN) != 0) {
                    clr += 0x00100000;
                }
                if ((wp->draw_ctx.ppu_scanline_regs[wp->draw_ctx.scanline_y_coords[i]].ppumask_flags & KS_NES_PPU_MASK_EMPHASIZE_BLUE) != 0) {
                    clr += 0x00001000;
                }

                GXPosition2s16(KS_NES_WIDTH + KS_NES_CENTER_X, -KS_NES_CENTER_Y - wp->draw_ctx.scanline_y_coords[i]);
                GXColor1u32(clr);
                GXTexCoord2u16(256, wp->draw_ctx.scanline_y_coords[i]);

                GXPosition2s16(KS_NES_WIDTH + KS_NES_CENTER_X, -KS_NES_CENTER_Y - wp->draw_ctx.scanline_y_coords[i + 1]);
                GXColor1u32(clr);
                GXTexCoord2u16(256, wp->draw_ctx.scanline_y_coords[i + 1]);

                GXPosition2s16(KS_NES_CENTER_X, -KS_NES_CENTER_Y - wp->draw_ctx.scanline_y_coords[i + 1]);
                GXColor1u32(clr);
                GXTexCoord2u16(0, wp->draw_ctx.scanline_y_coords[i + 1]);

                GXPosition2s16(KS_NES_CENTER_X, -KS_NES_CENTER_Y - wp->draw_ctx.scanline_y_coords[i]);
                GXColor1u32(clr);
                GXTexCoord2u16(0, wp->draw_ctx.scanline_y_coords[i]);
            }
        } while (i != 0);
        GXEnd();
    }

    GXSetTexCopySrc(KS_NES_CENTER_X, KS_NES_CENTER_Y, KS_NES_WIDTH, KS_NES_HEIGHT);
    GXSetTexCopyDst(KS_NES_WIDTH, KS_NES_HEIGHT, GX_TF_RGB565, GX_FALSE);
    GXSetCopyClear(black, 0xFFFFFF);
    GXCopyTex(wp->result_bufp, GX_FALSE);
    GXPixModeSync();
}

void ksNesDraw(ksNesCommonWorkObj* wp, ksNesStateObj* state) {
    ksNesDrawInit(wp);
    ksNesDrawClearEFBFirst(wp);
    if (state->mapper == KS_NES_MAPPER_MMC2 || state->mapper == KS_NES_MAPPER_MMC4) {
        ksNesDrawMakeBGIndTexMMC2(wp, state->mapper == KS_NES_MAPPER_MMC2 ? TRUE : FALSE);
        ksNesDrawOBJSetupMMC2(wp);
    } else if (state->mapper == KS_NES_MAPPER_MMC5) {
        ksNesDrawMakeBGIndTexMMC5(wp, state);
    } else {
        ksNesDrawMakeBGIndTex(wp, state->mapper == KS_NES_MAPPER_MMC3 ? TRUE : FALSE);
    }
    PPCSync();
    if (state->mapper == KS_NES_MAPPER_MMC5) {
        ksNesDrawOBJMMC5(wp, state, 0);
    } else {
        ksNesDrawOBJ(wp, state, 0);
    }
    ksNesDrawFlushEFBToRed8(wp->result_bufp);
    if (state->mapper == KS_NES_MAPPER_MMC5) {
        ksNesDrawOBJMMC5(wp, state, 1);
    } else {
        ksNesDrawOBJ(wp, state, 1);
    }

    GXPixModeSync();
    ksNesDrawBG(wp, state);
    ksNesDrawOBJI8ToEFB(wp, wp->result_bufp);
    ksNesDrawFlushEFBToRed8(wp->result_bufp);
    ksNesDrawEmuResult(wp);
    ksNesDrawEnd();
}
