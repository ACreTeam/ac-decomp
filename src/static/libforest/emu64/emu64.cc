#include "libforest/emu64/emu64.hpp"

#include "libultra/libultra.h"
#include "terminal.h"
#include "boot.h"

static aflags_c aflags;

static u8 texture_buffer_data[TEX_BUFFER_DATA_SIZE];
static u8 texture_buffer_bss[TEX_BUFFER_BSS_SIZE];

static tmem_t tmem_map[TMEM_ENTRIES];

static u32 texture_cache_num = 0;
static texture_cache_entry_t texture_cache_list[TEXTURE_CACHE_LIST_SIZE];

/* These are set externally during emu64 initialization */
static texture_cache_data_entry_t texture_cache_data_entry_tbl[NUM_TEXTURE_CACHE_DATA];
static int texture_cache_data_entry_num = 0;

static texture_cache_funcs texture_cache_data_func = { &texture_cache_data_search, &texture_cache_data_entry,
                                                       &texture_cache_alloc };

static texture_cache_t texture_cache_data = { &texture_cache_data_func,
                                              &texture_buffer_data[0],
                                              &texture_buffer_data[TEX_BUFFER_DATA_SIZE],
                                              &texture_buffer_data[0],
                                              nullptr,
                                              nullptr,
                                              FALSE,
                                              0 };

/* .bss cache functions */
void* texture_cache_bss_search(void* addr);
int texture_cache_bss_entry(void* original, void* converted);

static texture_cache_funcs texture_cache_bss_func = { &texture_cache_bss_search, &texture_cache_bss_entry,
                                                      &texture_cache_alloc };

static texture_cache_t texture_cache_bss = { &texture_cache_bss_func,
                                             &texture_buffer_bss[0],
                                             &texture_buffer_bss[TEX_BUFFER_BSS_SIZE],
                                             &texture_buffer_bss[0],
                                             nullptr,
                                             nullptr,
                                             FALSE,
                                             0 };

extern void emu64_texture_cache_data_entry_set(void* begin, void* end) {
    texture_cache_data_entry_t* entry = &texture_cache_data_entry_tbl[texture_cache_data_entry_num];

    entry->start = begin;
    entry->end = end;
    texture_cache_data_entry_num++;
}

static texture_cache_t* texture_cache_select(void* addr) {
    int i;

    if (aflags[5] < 1 && (addr < _f_rodata || addr > _e_data)) {
        for (i = 0; i < texture_cache_data_entry_num; i++) {
            if (addr >= texture_cache_data_entry_tbl[i].start && addr < texture_cache_data_entry_tbl[i].end) {
                return &texture_cache_data;
            }
        }

        return &texture_cache_bss;
    }

    return &texture_cache_data;
}

static bool texture_cache_is_overflow(texture_cache_t* cache) {
    return cache->is_overflow;
}

static void texture_cache_clear(texture_cache_t* cache) {
    cache->is_overflow = false;
    cache->buffer_current = cache->buffer_start;
}

/* @fabricated */
MATCH_FORCESTRIP static u32 texture_cache_get_max_alloc_size(texture_cache_t* cache) {
    return cache->buffer_current - cache->buffer_start;
}

/* @fabricated */
MATCH_FORCESTRIP static u32 texture_cache_get_alloc_size(texture_cache_t* cache) {
    return cache->buffer_current - cache->last_alloc_start;
}

/* @fabricated */
MATCH_FORCESTRIP static u32 texture_cache_get_free_size(texture_cache_t* cache) {
    return cache->buffer_end - cache->buffer_current;
}

/* @fabricated */
MATCH_FORCESTRIP static u32 texture_cache_get_heap_size(texture_cache_t* cache) {
    return cache->buffer_end - cache->buffer_start;
}

static void* texture_cache_alloc(texture_cache_t* cache, size_t size) {
    u32 new_pos;

    cache->last_alloc_start = cache->buffer_current;
    cache->last_alloc_end = (u8*)ALIGN_NEXT((u32)cache->buffer_current + size, 32);

    new_pos = cache->last_alloc_end - cache->buffer_start;
    if (cache->buffer_pos < new_pos) {
        cache->buffer_pos = new_pos;
    }

    if (cache->buffer_end < cache->last_alloc_end) {
        cache->is_overflow = true;
        return nullptr;
    }

    cache->buffer_current = cache->last_alloc_end;
    return cache->last_alloc_start;
}

static void* texture_cache_data_search(void* original_addr) {
    int i;

    for (i = 0; i < texture_cache_num; i++) {
        if (original_addr == texture_cache_list[i].original) {
            return texture_cache_list[i].converted;
        }
    }

    return nullptr;
}

static int texture_cache_data_entry(void* original_addr, void* converted_addr) {
    if (texture_cache_num < TEXTURE_CACHE_LIST_SIZE && original_addr != nullptr && converted_addr != nullptr) {
        texture_cache_entry_t* entry = &texture_cache_list[texture_cache_num++];

        entry->original = original_addr;
        entry->converted = converted_addr;
        return 0;
    }

    texture_cache_data.is_overflow = true;
    return -1;
}

static void* texture_cache_bss_search(void* original_addr) {
    return nullptr;
}

static int texture_cache_bss_entry(void* original_addr, void* converted_addr) {
    return -1;
}

static void texture_cache_list_clear() {
    texture_cache_clear(&texture_cache_data);
    texture_cache_num = 0;
}

extern void emu64_refresh() {
    texture_cache_list_clear();
}

/* Helper function to convert N64 texture format to Dolphin format */
u16 emu64::fmtxtbl[8][4] = {
    { GX_TF_CMPR, -1, GX_TF_RGB5A3, GX_TF_RGBA8 }, /* G_IM_FMT_RGBA */
    { -1, -1, -1, -1 },                            /* G_IM_FMT_YUV */
    { GX_TF_C4, GX_TF_C8, 0xA, -1 },               /* G_IM_FMT_CI */
    { -1, GX_TF_IA4, GX_TF_IA8, -1 },              /* G_IM_FMT_IA */
    { GX_TF_I4, GX_TF_I8, GX_TF_RGB565, -1 },      /* G_IM_FMT_I */
    { GX_TF_CMPR, GX_CTF_A8, GX_TF_RGB5A3, -1 },   /* ?? */
    { -1, GX_TF_Z8, GX_TF_Z16, GX_TF_Z24X8 },      /* ?? */
    { -1, -1, -1, -1 }                             /* ?? */
};

static u16 cvtN64ToDol(int n64_fmt, int n64_bpp) {
    u16 dol = emu64::fmtxtbl[n64_fmt][n64_bpp];
    if (dol != 0xFFFF) {
        return dol;
    }

    return GX_TF_I4;
}

MATCH_FORCESTRIP static f32 PsendoArcSinConvert(f32 arcsin) {
    f32 g = 2.0f * (arcsin - 0.5f);
    g = g * 0.4623f * g * g + g * 0.5377f;

    return 0.5f + g * 0.5f;
}

MATCH_FORCESTRIP static void TextureLinearConvert1(Texture* src, Texture* dst) {
    int y;
    int x;

    for (y = 0; y < dst->height; y++) {
        for (x = 0; x < dst->width; x++) {
            f32 arcsin_x = (f32)x / (f32)(dst->width - 1);
            f32 arcsin_y = (f32)y / (f32)(dst->height - 1);

            f32 sin_x = PsendoArcSinConvert(arcsin_x);
            f32 sin_y = PsendoArcSinConvert(arcsin_y);

            dst->putTexel(x, y, src->getTexel(sin_x * (src->width - 1), sin_y * (src->height - 1)));
        }
    }
}

MATCH_FORCESTRIP static void* TextureLinearConvert(void* img_p, unsigned int width, unsigned int height,
                                                   unsigned int fmt, unsigned int bpp) {
    texture_cache_t* tex_cache = texture_cache_select(NULL);
    void* conv_img_p = tex_cache->funcs->alloc(tex_cache, 0x1000);
    Texture src(img_p, width, height, fmt, bpp);
    Texture dst(conv_img_p, width, height, fmt, bpp);

    TextureLinearConvert1(&src, &dst);

    return conv_img_p;
}

static GXColor black_color = { 0, 0, 0, 0 };
static GXColor white_color = { 255, 255, 255, 255 };

static void emu64_init2(GXRenderModeObj* render_mode) {
    GC_Mtx m;

    __GXSetIndirectMask(0);

    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX2, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_TEX3, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD4, GX_TG_MTX2x4, GX_TG_TEX4, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD5, GX_TG_MTX2x4, GX_TG_TEX5, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD6, GX_TG_MTX2x4, GX_TG_TEX6, GX_IDENTITY);
    GXSetTexCoordGen(GX_TEXCOORD7, GX_TG_MTX2x4, GX_TG_TEX7, GX_IDENTITY);

    GXSetNumTexGens(1);
    GXClearVtxDesc();
    GXInvalidateVtxCache();
    GXSetLineWidth(6, GX_TO_ZERO);
    GXSetPointSize(6, GX_TO_ZERO);

    GXEnableTexOffsets(GX_TEXCOORD0, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD1, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD2, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD3, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD4, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD5, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD6, GX_FALSE, GX_FALSE);
    GXEnableTexOffsets(GX_TEXCOORD7, GX_FALSE, GX_FALSE);

    PSMTXIdentity(m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXLoadNrmMtxImm(m, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadTexMtxImm(m, GX_IDENTITY, GX_MTX3x4);

    GXSetViewport(0.0f, 0.0f, render_mode->fbWidth, render_mode->xfbHeight, 0.0f, 1.0f);
    GXSetCoPlanar(GX_FALSE);
    GXSetCullMode(GX_CULL_BACK);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXSetScissor(0, 0, render_mode->fbWidth, render_mode->efbHeight);
    GXSetScissorBoxOffset(0, 0);
    GXSetNumChans(0);

    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR0A0, black_color);
    GXSetChanMatColor(GX_COLOR0A0, white_color);

    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetChanAmbColor(GX_COLOR1A1, black_color);
    GXSetChanMatColor(GX_COLOR1A1, white_color);

    GXInvalidateTexAll();

    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD2, GX_TEXMAP2, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD3, GX_TEXMAP3, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE4, GX_TEXCOORD4, GX_TEXMAP4, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE5, GX_TEXCOORD5, GX_TEXMAP5, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE6, GX_TEXCOORD6, GX_TEXMAP6, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE7, GX_TEXCOORD7, GX_TEXMAP7, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE8, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE9, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE10, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE11, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE12, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE13, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE14, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevOrder(GX_TEVSTAGE15, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
}

void emu64::emu64_init() {
    bzero(this, sizeof(emu64));
    GXSetCurrentGXThread();
    emu64_init2(&GXNtsc480IntDf);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
    GXSetDither(GX_TRUE);
    GXInvalidateTexAll();
    GXInvalidateVtxCache();

    static f32 AAnear = -1.0f;
    static f32 AAfar = 1.0f;

    C_MTXOrtho(this->ortho_mtx, 1.0f, -1.0f, -1.0f, 1.0f, AAnear, AAfar);
    PSMTXIdentity(this->perspective_mtx);
    PSMTXIdentity(this->projection_mtx);
    PSMTXIdentity(this->original_projection_mtx);
    PSMTXIdentity(this->model_view_mtx_stack[0]);
    PSMTXIdentity(this->position_mtx_stack[0]);
    GXSetProjection(this->ortho_mtx, GX_ORTHOGRAPHIC);
    GXLoadPosMtxImm(this->perspective_mtx, GX_VA_PNMTXIDX);
    GXLoadNrmMtxImm(this->perspective_mtx, GX_VA_PNMTXIDX);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(2);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0A0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

    for (int i = GX_TEVSTAGE2; i < GX_TEVSTAGE8; i++) {
        GXSetTevColorIn((GXTevStageID)i, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
        GXSetTevAlphaIn((GXTevStageID)i, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
        GXSetTevOrder((GXTevStageID)i, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorOp((GXTevStageID)i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp((GXTevStageID)i, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    }

    GXSetCurrentMtx(GX_PNMTX0);

    static u8 line_width = 6;
    static GXTexOffset tex_offsets = GX_TO_ZERO;

    GXSetLineWidth(line_width - 1, tex_offsets);

    static u8 black_texture[] = { 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
                                  0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
                                  0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88 };

    for (int i = GX_TEXMAP0; i < GX_MAX_TEXMAP; i++) {
        GXInitTexObj(&this->tex_objs[i], black_texture, 8, 4, GX_TF_I8, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXLoadTexObj(&this->tex_objs[i], (GXTexMapID)i);
    }

    texture_cache_bss.is_overflow = false;
    texture_cache_bss.buffer_current = texture_cache_bss.buffer_start;

    if (texture_cache_data.is_overflow) {
        texture_cache_data.is_overflow = false;
        texture_cache_data.buffer_current = texture_cache_data.buffer_start;
        texture_cache_num = 0;
    }

    bzero(tmem_map, sizeof(tmem_map));

    this->dirty_flags[EMU64_DIRTY_FLAG_PRIM_COLOR] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_ENV_COLOR] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_BLEND_COLOR] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_FOG] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_FILL_COLOR] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_FILL_TEV_COLOR] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_TEX] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_POSITION_MTX] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_COMBINE] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_OTHERMODE_HIGH] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_OTHERMODE_LOW] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_GEOMETRYMODE] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_PROJECTION_MTX] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_LIGHTS] = true;
    this->dirty_flags[EMU64_DIRTY_FLAG_LIGHTING] = true;

    this->tex_edge_alpha = 144;
    this->texture_scale_s = 32.0f;
    this->texture_scale_t = 32.0f;
}

void emu64::printInfo() {
    // Display DL stack %d level.
    this->Printf0("DLスタック表示 %d level\n", this->DL_stack_level);

    for (int i = 0; i < this->DL_stack_level; i++) {
        this->Printf0("%d %08x %08x\n", i, (u32)this->DL_stack[i], convert_partial_address((u32)this->DL_stack[i]));
    }

    // Display last 16 DLs.
    this->Printf0("最終16DL表示\n");
    for (int i = 0; i < DL_HISTORY_COUNT; i++) {
        Gfx* gfx_p = this->dl_history[(this->dl_history_start + i) % DL_HISTORY_COUNT];

        // Print out the raw Gfx command
        this->Printf0("%016llx ", *(u64*)gfx_p);
        // Convert the second word to resolve the RAM address if it's a segment
        this->Printf0(" %08x\n", convert_partial_address(gfx_p->words.w1));
    }

    // Display segment table.
    this->Printf0("セグメントテーブル表示\n");
    for (int i = 0; i < NUM_SEGMENTS; i++) {
        this->Printf0("%2d %08x %08x\n", i, (u32)this->segments[i], convert_partial_address((u32)this->segments[i]));
    }
}

void emu64::panic(char* fmt, char* file, int line) {
    if (file != nullptr) {
        this->Printf0(VT_COL(RED, WHITE) "emu64 PANIC!! in %s line %d" VT_RST "\n", file, line);
    } else {
        this->Printf0(VT_COL(RED, WHITE) "emu64 PANIC!!" VT_RST "\n");
    }

    if (fmt != nullptr) {
        this->Printf0("%s", fmt);
    }

    this->printInfo();
}

void emu64::emu64_change_ucode(void* ucode_p) {
    if (this->ucode_len != 0) {
        for (int i = 0; i < this->ucode_len; i++) {
            if (ucode_p == this->ucode_info[i].ucode_p) {
                this->ucode_type = this->ucode_info[i].type;
                return;
            }
        }

        // ### Microcode did not match.
        this->Printf0("### マイクロコードが一致しなかった\n");
        this->err_count++;
        this->num_unknown_ucodes++;
        this->ucode_type = UCODE_TYPE_NONE;
    }
}

extern void get_dol_wd_ht(unsigned int siz, unsigned int in_wd, unsigned int in_ht, unsigned int* wd,
                          unsigned int* ht) {
    unsigned int blk_wd;
    unsigned int blk_ht;

    get_blk_wd_ht(siz, &blk_wd, &blk_ht);
    *wd = in_wd + (blk_wd - 1) & ~(blk_wd - 1);
    *ht = in_ht + (blk_ht - 1) & ~(blk_ht - 1);
}

void emu64::texconv_tile(u8* addr, u8* converted_addr, unsigned int wd, unsigned int fmt, unsigned int siz,
                         unsigned int start_wd, unsigned int start_ht, unsigned int end_wd, unsigned int end_ht,
                         unsigned int line_siz) {
    unsigned int blk_wd;
    unsigned int blk_ht;

    get_blk_wd_ht(siz, &blk_wd, &blk_ht);

    for (unsigned int blk_y = start_ht; blk_y < end_ht; blk_y += blk_ht) {
        for (unsigned int blk_x = start_wd; blk_x < end_wd; blk_x += blk_wd) {
            for (unsigned int y = 0; y < blk_ht; y++) {
                unsigned int y_ofs = start_ht + y;

                if (siz == G_IM_SIZ_16b) {
                    if (fmt == G_IM_FMT_RGBA) {
                        unsigned int x_ofs = (blk_x + y_ofs * wd) * sizeof(u16);
                        unsigned int ofs = this->tmem_swap(x_ofs, line_siz);

                        *(u16*)(converted_addr + 0) = rgba5551_to_rgb5a3(*(u16*)(addr + ofs + 0));
                        *(u16*)(converted_addr + 2) = rgba5551_to_rgb5a3(*(u16*)(addr + ofs + 2));

                        ofs = this->tmem_swap(x_ofs + 4, line_siz);

                        *(u16*)(converted_addr + 4) = rgba5551_to_rgb5a3(*(u16*)(addr + ofs + 0));
                        *(u16*)(converted_addr + 6) = rgba5551_to_rgb5a3(*(u16*)(addr + ofs + 2));
                    } else if (fmt == G_IM_FMT_IA) {
                        unsigned int x_ofs = (blk_x + y_ofs * wd) * sizeof(u16);
                        unsigned int ofs = this->tmem_swap(x_ofs, line_siz);
                        u8* src = addr + ofs;

                        *(converted_addr + 0) = *(src + 1);
                        *(converted_addr + 1) = *(src + 0);
                        *(converted_addr + 2) = *(src + 3);
                        *(converted_addr + 3) = *(src + 2);

                        ofs = this->tmem_swap(x_ofs + 4, line_siz);
                        src = addr + ofs;

                        *(converted_addr + 4) = *(src + 1);
                        *(converted_addr + 5) = *(src + 0);
                        *(converted_addr + 6) = *(src + 3);
                        *(converted_addr + 7) = *(src + 2);
                    }

                    converted_addr += 8;
                } else if (siz == G_IM_SIZ_8b) {
                    if (fmt == G_IM_FMT_IA) {
                        unsigned int x_ofs = blk_x + y_ofs * wd;
                        unsigned int ofs = this->tmem_swap(x_ofs, line_siz);

                        *(u32*)(converted_addr + 0) =
                            (((*(u32*)(addr + ofs)) & 0x0F0F0F0F) << 4) | (((*(u32*)(addr + ofs)) & 0xF0F0F0F0) >> 4);
                        ofs = this->tmem_swap(x_ofs + 4, line_siz);
                        *(u32*)(converted_addr + 4) =
                            (((*(u32*)(addr + ofs)) & 0x0F0F0F0F) << 4) | (((*(u32*)(addr + ofs)) & 0xF0F0F0F0) >> 4);
                    } else {
                        unsigned int x_ofs = blk_x + y_ofs * wd;
                        unsigned int ofs = this->tmem_swap(x_ofs, line_siz);

                        *(u32*)(converted_addr + 0) = *(u32*)(addr + ofs);
                        ofs = this->tmem_swap(x_ofs + 4, line_siz);
                        *(u32*)(converted_addr + 4) = *(u32*)(addr + ofs);
                    }

                    converted_addr += 8;
                } else if (siz == G_IM_SIZ_4b) {
                    unsigned int x_ofs = (blk_x + y_ofs * wd) / 2;
                    unsigned int ofs = this->tmem_swap(x_ofs, line_siz);

                    *(u32*)(converted_addr + 0) = *(u32*)(addr + ofs);
                    converted_addr += 4;
                } else {
                    // G_IM_SIZ_32b is not supported.
                    this->Printf0("G_IM_SIZ_32bはサポートしてません");
                }
            }
        }
    }

    this->texconv_cnt++;
}

void emu64::tlutconv_rgba5551(u16* rgba5551_p, u16* rgb5a3_p, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        *rgb5a3_p++ = rgba5551_to_rgb5a3(*rgba5551_p++);
    }
}

void emu64::tlutconv_ia16(u16* src_ia16_p, u16* dst_ia16_p, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        *(((u8*)dst_ia16_p) + 0) = *(((u8*)src_ia16_p) + 1);
        *(((u8*)dst_ia16_p) + 1) = *(((u8*)src_ia16_p) + 0);
        src_ia16_p++;
        dst_ia16_p++;
    }
}

u8* emu64::texconv_tile_new(u8* addr, unsigned int wd, unsigned int fmt, unsigned int siz, unsigned int start_wd,
                            unsigned int start_ht, unsigned int end_wd, unsigned int end_ht, unsigned int line_siz) {
    if (addr == nullptr) {
        return nullptr;
    }

    texture_cache_t* texture_cache = texture_cache_select(addr);
    u8* converted_addr = (u8*)(*texture_cache->funcs->search)(addr);

    /* Check if we already converted this texture */
    if (converted_addr == nullptr) {
        u32 len = get_dol_tex_siz(siz, (end_wd - start_wd) + 1, (end_ht - start_ht) + 1);

        converted_addr = (u8*)(*texture_cache->funcs->alloc)(texture_cache, len);
        if (converted_addr != nullptr) {
            /* Convert from N64 -> GC */
            this->texconv_tile(addr, converted_addr, wd, fmt, siz, start_wd, start_ht, end_wd, end_ht, line_siz);
            /* Update cache & store entry */
            DCStoreRange(converted_addr, len);
            (*texture_cache->funcs->entry)(addr, converted_addr);
        }
    }

    return converted_addr;
}

u16* emu64::tlutconv_new(u16* tlut, unsigned int tlut_fmt, unsigned int count) {
    if (tlut == nullptr) {
        return nullptr;
    }

    texture_cache_t* texture_cache = texture_cache_select(tlut);
    u16* converted_tlut = (u16*)(*texture_cache->funcs->search)(tlut);

    /* Check if we already converted this texture */
    if (converted_tlut == nullptr) {
        u32 len = get_dol_tlut_size(count);

        converted_tlut = (u16*)(*texture_cache->funcs->alloc)(texture_cache, len);
        if (converted_tlut != nullptr) {
            /* Convert from N64 -> GC */
            this->tlutconv(tlut, converted_tlut, count, tlut_fmt);
            /* Update cache & store entry */
            DCStoreRange(converted_tlut, len);
            (*texture_cache->funcs->entry)(tlut, converted_tlut);
        }
    }

    return converted_tlut;
}

void emu64::tlutconv(u16* src_tlut, u16* dst_tlut, unsigned int count, unsigned int tlut_fmt) {
    if (tlut_fmt == EMU64_TLUT_RGBA5551) {
        this->tlutconv_rgba5551(src_tlut, dst_tlut, count);
    } else {
        this->tlutconv_ia16(src_tlut, dst_tlut, count);
    }
}

static const combiner_tev_alpha tbla[8] = { { GX_CA_APREV, GX_CA_KONST }, { GX_CA_TEXA, GX_CA_TEXA },
                                            { GX_CA_TEXA, GX_CA_TEXA },   { GX_CA_A1, GX_CA_A1 },
                                            { GX_CA_RASA, GX_CA_RASA },   { GX_CA_A2, GX_CA_A2 },
                                            { GX_CA_KONST, GX_CA_A0 },    { GX_CA_ZERO, GX_CA_ZERO } };

static const combiner_tev_color tblc[32] = {
    { GX_CC_CPREV, GX_CC_CPREV, GX_CC_CPREV, GX_CC_CPREV }, { GX_CC_TEXC, GX_CC_TEXC, GX_CC_TEXC, GX_CC_TEXC },
    { GX_CC_TEXC, GX_CC_TEXC, GX_CC_TEXC, GX_CC_TEXC },     { GX_CC_C1, GX_CC_C1, GX_CC_C1, GX_CC_C1 },
    { GX_CC_RASC, GX_CC_RASC, GX_CC_RASC, GX_CC_RASC },     { GX_CC_C2, GX_CC_C2, GX_CC_C2, GX_CC_C2 },
    { GX_CC_ONE, GX_CC_HALF, GX_CC_HALF, GX_CC_ONE },       { GX_CC_HALF, GX_CC_HALF, GX_CC_APREV, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXA, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXA, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_A1, GX_CC_ZERO },       { GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASA, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_A2, GX_CC_ZERO },       { GX_CC_ZERO, GX_CC_ZERO, GX_CC_HALF, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_A0, GX_CC_ZERO },       { GX_CC_ZERO, GX_CC_ZERO, GX_CC_HALF, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },
    { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO },     { GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO }
};

int emu64::replace_combine_to_tev(Gfx* g) {
    Gsetcombine_new* setcombine = (Gsetcombine_new*)g;

    if ((setcombine->a0 == G_CCMUX_TEXEL1 || setcombine->b0 == G_CCMUX_TEXEL1 || setcombine->c0 == G_CCMUX_TEXEL1 ||
         setcombine->d0 == G_CCMUX_TEXEL1 || setcombine->c0 == G_CCMUX_TEXEL1_ALPHA) ||
        (setcombine->Aa0 == G_ACMUX_TEXEL1 || setcombine->Ab0 == G_ACMUX_TEXEL1 || setcombine->Ac0 == G_ACMUX_TEXEL1 ||
         setcombine->Ad0 == G_ACMUX_TEXEL1) ||
        (setcombine->a1 == G_CCMUX_TEXEL1 || setcombine->b1 == G_CCMUX_TEXEL1 || setcombine->c1 == G_CCMUX_TEXEL1 ||
         setcombine->d1 == G_CCMUX_TEXEL1 || setcombine->c1 == G_CCMUX_TEXEL1_ALPHA) ||
        (setcombine->Aa1 == G_ACMUX_TEXEL1 || setcombine->Ab1 == G_ACMUX_TEXEL1 || setcombine->Ac1 == G_ACMUX_TEXEL1 ||
         setcombine->Ad1 == G_ACMUX_TEXEL1)) {
        g->setcombine.cmd = G_SETCOMBINE_NOTEV;
        return -1;
    }

    Gsetcombine_tev sc_tev;

    int a0_color0 = tblc[(int)setcombine->a0].color0;
    int b0_color1 = tblc[(int)setcombine->b0].color1;
    int c0_color2 = tblc[(int)setcombine->c0].color2;
    int d0_color3 = tblc[(int)setcombine->d0].color3;

    int Aa0_alpha0 = tbla[(int)setcombine->Aa0].alpha0;
    int Ab0_alpha0 = tbla[(int)setcombine->Ab0].alpha0;
    int Ac0_alpha1 = tbla[(int)setcombine->Ac0].alpha1;
    int Ad0_alpha0 = tbla[(int)setcombine->Ad0].alpha0;

    /* Set TEV color 0 */
    if (b0_color1 == TEV_ZERO) {
        sc_tev.a0 = TEV_ZERO;
        sc_tev.b0 = b0_color1;
        sc_tev.c0 = c0_color2;
        sc_tev.d0 = d0_color3;
    } else if (b0_color1 == d0_color3) {
        sc_tev.a0 = b0_color1;
        sc_tev.b0 = a0_color0;
        sc_tev.c0 = c0_color2;
        sc_tev.d0 = TEV_ZERO;

    } else {
        g->setcombine.cmd = G_SETCOMBINE_NOTEV;
        return -1;
    }

    /* Set TEV alpha 0 */
    if (Ab0_alpha0 == TEV_ALPHA_ZERO) {
        sc_tev.Aa0 = TEV_ALPHA_ZERO;
        sc_tev.Ab0 = Aa0_alpha0;
        sc_tev.Ac0 = Ac0_alpha1;
        sc_tev.Ad0 = Ad0_alpha0;
    } else if (Ab0_alpha0 == Ad0_alpha0) {
        sc_tev.Aa0 = Ab0_alpha0;
        sc_tev.Ab0 = Aa0_alpha0;
        sc_tev.Ac0 = Ac0_alpha1;
        sc_tev.Ad0 = TEV_ALPHA_ZERO;
    } else {
        g->setcombine.cmd = G_SETCOMBINE_NOTEV;
        return -1;
    }

    int a1_color0 = tblc[(int)setcombine->a1].color0;
    int b1_color1 = tblc[(int)setcombine->b1].color1;
    int c1_color2 = tblc[(int)setcombine->c1].color2;
    int d1_color3 = tblc[(int)setcombine->d1].color3;

    int Aa1_alpha0 = tbla[(int)setcombine->Aa1].alpha0;
    int Ab1_alpha0 = tbla[(int)setcombine->Ab1].alpha0;
    int Ac1_alpha1 = tbla[(int)setcombine->Ac1].alpha1;
    int Ad1_alpha0 = tbla[(int)setcombine->Ad1].alpha0;

    /* Set TEV color 1 */
    if (b1_color1 == TEV_ZERO) {
        sc_tev.a1 = TEV_ZERO;
        sc_tev.b1 = a1_color0;
        sc_tev.c1 = c1_color2;
        sc_tev.d1 = d1_color3;
    } else if (b1_color1 == d1_color3) {
        sc_tev.a1 = b1_color1;
        sc_tev.b1 = a1_color0;
        sc_tev.c1 = c1_color2;
        sc_tev.d1 = TEV_ZERO;
    } else {
        g->setcombine.cmd = G_SETCOMBINE_NOTEV;
        return -1;
    }

    /* Set TEV alpha 1 */
    if (Ab1_alpha0 == TEV_ALPHA_ZERO) {
        sc_tev.Aa1 = TEV_ALPHA_ZERO;
        sc_tev.Ab1 = Aa1_alpha0;
        sc_tev.Ac1 = Ac1_alpha1;
        sc_tev.Ad1 = Ad1_alpha0;
    } else if (Ab1_alpha0 == Ad1_alpha0) {
        sc_tev.Aa1 = Ab1_alpha0;
        sc_tev.Ab1 = Aa1_alpha0;
        sc_tev.Ac1 = Ac1_alpha1;
        sc_tev.Ad1 = TEV_ALPHA_ZERO;
    } else {
        g->setcombine.cmd = G_SETCOMBINE_NOTEV;
        return -1;
    }

    sc_tev.cmd = G_SETCOMBINE_TEV;
    g->words.w0 = ((Gwords*)&sc_tev)->w0;
    g->words.w1 = ((Gwords*)&sc_tev)->w1;
    return 0;
}

int emu64::combine_auto() {
    Gsetcombine_new* setcombine = (Gsetcombine_new*)&this->combine;
    bool two_cycle = (this->othermode_high & G_CYC_2CYCLE) != 0;

    if (setcombine->a0 == G_CCMUX_TEXEL1 || setcombine->b0 == G_CCMUX_TEXEL1 || setcombine->c0 == G_CCMUX_TEXEL1 ||
        setcombine->d0 == G_CCMUX_TEXEL1 || setcombine->c0 == G_CCMUX_TEXEL1_ALPHA ||
        setcombine->Aa0 == G_ACMUX_TEXEL1 || setcombine->Ab0 == G_ACMUX_TEXEL1 || setcombine->Ac0 == G_ACMUX_TEXEL1 ||
        setcombine->Ad0 == G_ACMUX_TEXEL1 ||
        two_cycle &&
            (setcombine->a1 == G_CCMUX_TEXEL1 || setcombine->b1 == G_CCMUX_TEXEL1 || setcombine->c1 == G_CCMUX_TEXEL1 ||
             setcombine->d1 == G_CCMUX_TEXEL1 || setcombine->c1 == G_CCMUX_TEXEL1_ALPHA ||
             setcombine->Aa1 == G_ACMUX_TEXEL1 || setcombine->Ab1 == G_ACMUX_TEXEL1 ||
             setcombine->Ac1 == G_ACMUX_TEXEL1 || setcombine->Ad1 == G_ACMUX_TEXEL1)) {
        return -1;
    }

    int stage = GX_TEVSTAGE0;

    GXTevColorArg a = (GXTevColorArg)tblc[setcombine->b0].color1; /* b0 */
    GXTevColorArg b = (GXTevColorArg)tblc[setcombine->a0].color0; /* a0 */
    GXTevColorArg c = (GXTevColorArg)tblc[setcombine->c0].color2; /* c0 */
    GXTevColorArg d = (GXTevColorArg)tblc[setcombine->d0].color3; /* d0 */

    GXTevAlphaArg alpha_b = (GXTevAlphaArg)tbla[setcombine->Aa0].alpha0; /* Aa0 */
    GXTevAlphaArg alpha_a = (GXTevAlphaArg)tbla[setcombine->Ab0].alpha0; /* Ab0 */
    GXTevAlphaArg alpha_c = (GXTevAlphaArg)tbla[setcombine->Ac0].alpha1; /* Ac0 */
    GXTevAlphaArg alpha_d = (GXTevAlphaArg)tbla[setcombine->Ad0].alpha0; /* Ad0 */

    int color_stages, tevstages;
    if (a == GX_CC_ZERO) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, b, c, d);
        color_stages = 1;
    } else if (a == d) {
        GXSetTevColorIn(GX_TEVSTAGE0, a, b, c, GX_CC_ZERO);
        color_stages = 1;
    } else {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, b, c, d);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, a, c, GX_CC_CPREV);
        color_stages = 2;
    }

    if (alpha_a == GX_CA_ZERO) {
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, alpha_b, alpha_c, alpha_d);
        tevstages = 1;
    } else if (alpha_a == alpha_d) {
        GXSetTevAlphaIn(GX_TEVSTAGE0, alpha_a, alpha_b, alpha_c, GX_CA_ZERO);
        tevstages = 1;
    } else {
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, alpha_b, alpha_c, alpha_d);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, alpha_a, alpha_c, GX_CA_APREV);
        tevstages = 2;
    }

    if (tevstages < color_stages) {
        tevstages = color_stages;
    }

    for (stage; stage < tevstages; stage++) {
        GXSetTevOrder((GXTevStageID)stage, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    }

    if (two_cycle) {
        GXTevColorArg a2 = (GXTevColorArg)tblc[setcombine->b1].color1; /* b1 */
        GXTevColorArg b2 = (GXTevColorArg)tblc[setcombine->a1].color0; /* a1 */
        GXTevColorArg c2 = (GXTevColorArg)tblc[setcombine->c1].color2; /* c1 */
        GXTevColorArg d2 = (GXTevColorArg)tblc[setcombine->d1].color3; /* d1 */

        GXTevAlphaArg alpha_b2 = (GXTevAlphaArg)tbla[setcombine->Aa1].alpha0; /* Aa1 */
        GXTevAlphaArg alpha_a2 = (GXTevAlphaArg)tbla[setcombine->Ab1].alpha0; /* Ab1 */
        GXTevAlphaArg alpha_c2 = (GXTevAlphaArg)tbla[setcombine->Ac1].alpha1; /* Ac1 */
        GXTevAlphaArg alpha_d2 = (GXTevAlphaArg)tbla[setcombine->Ad1].alpha0; /* Ad1 */

        /* @BUG - Is this alpha_c2 != GX_CC_ZERO check supposed to be alpha_c2 != GX_CA_ZERO? */
        if (c2 != GX_CC_ZERO || d2 != GX_CC_CPREV || alpha_c2 != GX_CC_ZERO || alpha_d2 != GX_CA_APREV) {
            if (a2 == GX_CC_ZERO) {
                GXSetTevColorIn((GXTevStageID)stage, GX_CC_ZERO, b2, c2, d2);
                color_stages = stage + 1;
            } else if (a2 == d2) {
                GXSetTevColorIn((GXTevStageID)stage, a2, b2, c2, GX_CC_ZERO);
                color_stages = stage + 1;
            } else {
                GXSetTevColorIn((GXTevStageID)stage, GX_CC_ZERO, b2, c2, d2);
                GXSetTevColorOp((GXTevStageID)(stage + 1), GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevColorIn((GXTevStageID)(stage + 1), GX_CC_ZERO, a2, c2, GX_CC_CPREV);
                color_stages = stage + 2;
            }

            if (alpha_a2 == GX_CA_ZERO) {
                GXSetTevAlphaIn((GXTevStageID)stage, GX_CA_ZERO, alpha_b2, alpha_c2, alpha_d2);
                tevstages = stage + 1;
            } else if (alpha_a2 == alpha_d2) {
                GXSetTevAlphaIn((GXTevStageID)stage, alpha_a2, alpha_b2, alpha_c2, GX_CA_ZERO);
                tevstages = stage + 1;
            } else {
                GXSetTevAlphaIn((GXTevStageID)stage, GX_CA_ZERO, alpha_b2, alpha_c2, alpha_d2);
                GXSetTevAlphaOp((GXTevStageID)(stage + 1), GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
                GXSetTevAlphaIn((GXTevStageID)(stage + 1), GX_CA_ZERO, alpha_a2, alpha_c2, GX_CA_APREV);
                tevstages = stage + 2;
            }

            if (tevstages < color_stages) {
                tevstages = color_stages;
            }

            for (stage; stage < tevstages; stage++) {
                GXSetTevOrder((GXTevStageID)stage, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            }
        }
    }

    EMU64_ASSERTLINE(tevstages <= 4, 1934);
    GXSetNumTevStages(tevstages);
    this->combine_auto_cnt[tevstages]++;
    return 0;
}

int emu64::combine_tev() {
    Gsetcombine_tev combine_tev = *((Gsetcombine_tev*)&this->combine);

    if (((this->combine.words.w0 >> 24) & 0xFF) == G_SETCOMBINE_TEV) {
        if (aflags[AFLAGS_FORCE_TEV_COMBINE_MODE] != 0) {
            if (aflags[AFLAGS_FORCE_TEV_COMBINE_MODE] == 1) {
                static u32 c = TEV_SHADE;
                static u32 c1 = TEV_SHADE;
                static u32 a = TEV_ALPHA_SHADE;
                static u32 a1 = TEV_ALPHA_SHADE;

                if (combine_tev.a0 == c) {
                    combine_tev.a0 = c1;
                }

                if (combine_tev.b0 == c) {
                    combine_tev.b0 = c1;
                }

                if (combine_tev.c0 == c) {
                    combine_tev.c0 = c1;
                }

                if (combine_tev.d0 == c) {
                    combine_tev.d0 = c1;
                }

                if (combine_tev.a1 == c) {
                    combine_tev.a1 = c1;
                }

                if (combine_tev.b1 == c) {
                    combine_tev.b1 = c1;
                }

                if (combine_tev.c1 == c) {
                    combine_tev.c1 = c1;
                }

                if (combine_tev.d1 == c) {
                    combine_tev.d1 = c1;
                }

                if (combine_tev.Aa0 == a) {
                    combine_tev.Aa0 = a1;
                }

                if (combine_tev.Ab0 == a) {
                    combine_tev.Ab0 = a1;
                }

                if (combine_tev.Ac0 == a) {
                    combine_tev.Ac0 = a1;
                }

                if (combine_tev.Ad0 == a) {
                    combine_tev.Ad0 = a1;
                }

                if (combine_tev.Aa1 == a) {
                    combine_tev.Aa1 = a1;
                }

                if (combine_tev.Ab1 == a) {
                    combine_tev.Ab1 = a1;
                }

                if (combine_tev.Ac1 == a) {
                    combine_tev.Ac1 = a1;
                }

                if (combine_tev.Ad1 == a) {
                    combine_tev.Ad1 = a1;
                }
            }

            if (aflags[AFLAGS_FORCE_TEV_COMBINE_MODE] == 2) {
                combine_tev.d1 = TEV_ENVIRONMENT;
                combine_tev.Ad1 = TEV_ALPHA_ONE;
            }
        }

        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);

        GXSetTevColorIn(GX_TEVSTAGE0, (GXTevColorArg)combine_tev.a0, (GXTevColorArg)combine_tev.b0,
                        (GXTevColorArg)combine_tev.c0, (GXTevColorArg)combine_tev.d0);
        GXSetTevAlphaIn(GX_TEVSTAGE0, (GXTevAlphaArg)combine_tev.Aa0, (GXTevAlphaArg)combine_tev.Ab0,
                        (GXTevAlphaArg)combine_tev.Ac0, (GXTevAlphaArg)combine_tev.Ad0);

        if ((this->othermode_high & G_CYC_2CYCLE) == 0 ||
            ((this->combine.words.w1 & 0xFFFF) == 0xFFF0 && ((this->combine.words.w0 & 0xFFF) == 0xFF8))) {
            GXSetNumTexGens(1);
            GXSetNumTevStages(1);

            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
            GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);

            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
            GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        } else {
            GXSetNumTexGens(2);
            GXSetNumTevStages(2);

            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE1, (GXTevColorArg)combine_tev.a1, (GXTevColorArg)combine_tev.b1,
                            (GXTevColorArg)combine_tev.c1, (GXTevColorArg)combine_tev.d1);
            GXSetTevAlphaIn(GX_TEVSTAGE1, (GXTevAlphaArg)combine_tev.Aa1, (GXTevAlphaArg)combine_tev.Ab1,
                            (GXTevAlphaArg)combine_tev.Ac1, (GXTevAlphaArg)combine_tev.Ad1);

            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
            GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        }

        if (aflags[ALFAGS_TEV_ALPHA_KONST] != 0 || aflags[AFLAGS_2TRIS] != 0) {
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
        }
    }
}

#define NUM_COMBINER_HIGHLOW_ERRS 10
static u32 last_highlow;
static u64 highlow_errs[NUM_COMBINER_HIGHLOW_ERRS];

/* Combine Manual Macros */

#define gsDPSetCombineLERPInline(a0, b0, c0, d0, Aa0, Ab0, Ac0, Ad0, a1, b1, c1, d1, Aa1, Ab1, Ac1, Ad1)               \
    (((u64)_SHIFTL(G_SETCOMBINE, 24, 8) |                                                                              \
      _SHIFTL(GCCc0w0(G_CCMUX_##a0, G_CCMUX_##c0, G_ACMUX_##Aa0, G_ACMUX_##Ac0) | GCCc1w0(G_CCMUX_##a1, G_CCMUX_##c1), \
              0, 24))                                                                                                  \
     << 32) |                                                                                                          \
        ((u64)(GCCc0w1(G_CCMUX_##b0, G_CCMUX_##d0, G_ACMUX_##Ab0, G_ACMUX_##Ad0) |                                     \
               GCCc1w1(G_CCMUX_##b1, G_ACMUX_##Aa1, G_ACMUX_##Ac1, G_CCMUX_##d1, G_ACMUX_##Ab1, G_ACMUX_##Ad1)))
#define COMBINE_CONSTEXPR(mode0, mode1) (gsDPSetCombineLERPInline(mode0, mode1))

void emu64::combine_manual() {
    u64 combine_mode = *(u64*)&this->combine;

    switch (combine_mode) {
        case gsDPSetCombineLERPInline(TEXEL0, 0, SHADE, TEXEL0, 0, 0, 0, TEXEL0, SHADE, ENVIRONMENT, PRIMITIVE,
                                      COMBINED, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_RASC, GX_CC_C1, GX_CC_CPREV);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C2, GX_CC_C1, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            break;
        }
        case gsDPSetCombineLERPInline(NOISE, TEXEL0, PRIMITIVE, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, COMBINED, 0,
                                      SHADE, 0, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_HALF);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_C1, GX_CC_C2);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A1, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, TEXEL1, PRIMITIVE, 0, 0, 0,
                                      0, COMBINED, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C2, GX_CC_C1, GX_CC_TEXC, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A1, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A1, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL1, TEXEL0, PRIMITIVE_ALPHA, TEXEL0, SHADE, 0, PRIM_LOD_FRAC, 0, COMBINED, 0,
                                      SHADE, 0, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A1, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE,
                                      ENVIRONMENT, COMBINED, ENVIRONMENT, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C2, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL0, 0, TEXEL1, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, ENVIRONMENT, COMBINED,
                                      ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C2, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A1, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0,
                                      PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C2, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A1, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, TEXEL0, ENVIRONMENT, TEXEL0,
                                      PRIMITIVE, ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C2, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_TEXA, GX_CA_A2, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A1, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL0, 0, TEXEL1_ALPHA, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, ENVIRONMENT,
                                      COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXA, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C2, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A1, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(0, 0, 0, PRIMITIVE, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, COMBINED,
                                      COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C1);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A1, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL1, TEXEL0, PRIM_LOD_FRAC,
                                      TEXEL0, COMBINED, 0, SHADE, 0, COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_C1, GX_CC_C2, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A1, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(0, 0, 0, PRIMITIVE, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, SHADE, 0, COMBINED, 0,
                                      COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_C1, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_APREV, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A1, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL1, 0, TEXEL0, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE, 0, SHADE, COMBINED, 0,
                                      0, 0, COMBINED): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_CPREV);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_RASC, GX_CC_C1, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 0, TEXEL0, 0, PRIMITIVE,
                                      ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_C2, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A1, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL0, 0, TEXEL1_ALPHA, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, 0, SHADE, COMBINED,
                                      COMBINED, 0, PRIM_LOD_FRAC, PRIMITIVE): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXA, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C1, GX_CC_RASC, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_A1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL0, 0, TEXEL1_ALPHA, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, 0, SHADE, COMBINED,
                                      COMBINED, 0, PRIM_LOD_FRAC, 0): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXA, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_C1, GX_CC_RASC, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_A0, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, 0, 0,
                                      0, 0, COMBINED): {
            GXSetNumTevStages(3);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_A0, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(1, 0, TEXEL0, TEXEL0, 0, 0, 0, TEXEL0, COMBINED, 0, SHADE, TEXEL1, 0, 0, 0,
                                      COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, 0, PRIM_LOD_FRAC, ENVIRONMENT, 0, 0, 0, TEXEL0, TEXEL1, 0, COMBINED, 0,
                                      0, 0, 0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C1, GX_CC_A0, GX_CC_C2);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, SHADE, PRIM_LOD_FRAC, SHADE, 0, 0, 0, TEXEL0, TEXEL1, 0, COMBINED, 0,
                                      0, 0, 0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_RASC, GX_CC_C1, GX_CC_A0, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_TEXC, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(0, 0, 0, PRIMITIVE, TEXEL0, 0, TEXEL1, 0, 0, 0, 0, COMBINED, COMBINED, 0,
                                      PRIM_LOD_FRAC, 0): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, TEXEL1, TEXEL0, TEXEL1, TEXEL0, 0, TEXEL1, 0, 0, 0, 0, COMBINED, 0, 0,
                                      0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_TEXC, GX_CC_C1, GX_CC_CPREV, GX_CC_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_TEXA, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, 0, SHADE, ENVIRONMENT, TEXEL0, 0, TEXEL1, 0, TEXEL0, 0, PRIM_LOD_FRAC,
                                      COMBINED, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_C1, GX_CC_C2);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, 0, SHADE, ENVIRONMENT, TEXEL0, 0, TEXEL1, TEXEL1, TEXEL1, 0,
                                      PRIM_LOD_FRAC, COMBINED, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_C2);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_RASC, GX_CC_C1, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_TEXA);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(1, 0, PRIMITIVE, TEXEL0, TEXEL0, 0, TEXEL1, 0, COMBINED, 0, SHADE, TEXEL1, 0, 0,
                                      0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_RASC, GX_CC_C1, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(TEXEL0, 0, ENV_ALPHA, 0, TEXEL0, 0, TEXEL1, 0, PRIMITIVE, 0, PRIMITIVE_ALPHA,
                                      COMBINED, COMBINED, 0, PRIM_LOD_FRAC, 0): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A2, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_C1, GX_CC_A1, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(1, 0, PRIMITIVE, TEXEL0, TEXEL1, 0, TEXEL0, 0, COMBINED, 0, SHADE, TEXEL0,
                                      COMBINED, 0, PRIM_LOD_FRAC, 0): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C1);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_TEXC);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, TEXEL1, TEXEL1, 0, 0, 0,
                                      COMBINED, COMBINED, 0, PRIM_LOD_FRAC, 0): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C2, GX_CC_C1, GX_CC_TEXC, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_A0);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(0, 0, 0, TEXEL0, 0, 0, 0, TEXEL1, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(1, 0, PRIMITIVE, TEXEL0, TEXEL1, 0, PRIMITIVE, 0, COMBINED, 0, SHADE, TEXEL1, 0,
                                      0, 0, COMBINED): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_TEXC);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_C1, GX_CC_RASC, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A1);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_APREV, GX_CA_TEXA, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(0, 0, 0, PRIMITIVE, TEXEL0, 0, TEXEL1, 0, 0, 0, 0, COMBINED, COMBINED, 0,
                                      PRIMITIVE, 0): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C1);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A1, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_APREV, GX_CA_ZERO);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(0, 0, 0, PRIMITIVE, 1, 0, TEXEL0, TEXEL1, 0, 0, 0, COMBINED, COMBINED, 0,
                                      PRIMITIVE, 0): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A1, GX_CA_ZERO);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A1, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        case gsDPSetCombineLERPInline(PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, 1, 0, TEXEL0, TEXEL1, COMBINED, 0,
                                      SHADE, TEXEL0, COMBINED, 0, PRIM_LOD_FRAC, PRIMITIVE): {
            GXSetNumTevStages(2);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C2, GX_CC_C1, GX_CC_TEXC, GX_CC_ZERO);
            GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_RASC, GX_CC_CPREV, GX_CC_TEXC);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_A1);
            GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_APREV);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
            break;
        }
        default: {
            if (aflags[AFLAGS_COMBINE_AUTO] != 0 || this->combine_auto() != 0) {
                if (aflags[AFLAGS_SKIP_COMBINE_TEV] == 2) {
                    last_highlow = 0;
                }

                if (last_highlow < NUM_COMBINER_HIGHLOW_ERRS) {
                    bool found = false;
                    int i;
                    for (i = 0; i < last_highlow; i++) {
                        if (combine_mode == highlow_errs[i]) {
                            found = true;
                            break;
                        }
                    }

                    if (!found) {

                        highlow_errs[i] = combine_mode;
                        this->err_count++;
                        /* ### Unsupported combine mode ###\ncase 0x%16llx:// */
                        this->Printf0(VT_COL(YELLOW, BLACK) "### 未対応のコンバインモードです ###\ncase 0x%16llx:// ", combine_mode);
                        this->print_combine(combine_mode);
                        this->Printf0("\n" VT_RST);
                    }
                }

                /* Default case */
                GXSetNumTevStages(1);
                GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
                GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
                GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            }
            break;
        }
    }
}
