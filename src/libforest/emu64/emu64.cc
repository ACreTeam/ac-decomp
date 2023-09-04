#include "libforest/emu64/emu64.hpp"

static aflags_c aflags;

static u8 texture_buffer_data[TEX_BUFFER_DATA_SIZE];
static u8 texture_buffer_bss[TEX_BUFFER_BSS_SIZE];

static u32 texture_cache_num;
static texture_cache_entry_t texture_cache_list[TEXTURE_CACHE_LIST_SIZE];

/* These are set externally during emu64 initialization */
static texture_cache_data_entry_t texture_cache_data_entry_tbl[NUM_TEXTURE_CACHE_DATA];
static int texture_cache_data_entry_num;

static texture_cache_funcs texture_cache_data_func = {
    &texture_cache_data_search,
    &texture_cache_data_entry,
    &texture_cache_alloc
};

static texture_cache_t texture_cache_data = {
    &texture_cache_data_func,
    &texture_buffer_data[0],
    &texture_buffer_data[TEX_BUFFER_DATA_SIZE],
    &texture_buffer_data[0],
    nullptr,
    nullptr,
    FALSE,
    0
};

/* .bss cache functions */
void* texture_cache_bss_search(void* addr);
int texture_cache_bss_entry(void* original, void* converted);

static texture_cache_funcs texture_cache_bss_func = {
    &texture_cache_bss_search,
    &texture_cache_bss_entry,
    &texture_cache_alloc
};

static texture_cache_t texture_cache_bss = {
    &texture_cache_bss_func,
    &texture_buffer_bss[0],
    &texture_buffer_bss[TEX_BUFFER_BSS_SIZE],
    &texture_buffer_bss[0],
    nullptr,
    nullptr,
    FALSE,
    0
};

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
      return  texture_cache_list[i].converted;
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
  { -1, -1, -1, -1 }, /* G_IM_FMT_YUV */
  { GX_TF_C4, GX_TF_C8, 0xA, -1 }, /* G_IM_FMT_CI */
  { -1, GX_TF_IA4, GX_TF_IA8, -1 }, /* G_IM_FMT_IA */
  { GX_TF_I4, GX_TF_I8, GX_TF_RGB565, -1 }, /* G_IM_FMT_I */
  { GX_TF_CMPR, GX_CTF_A8, GX_TF_RGB5A3, -1 }, /* ?? */
  { -1, GX_TF_Z8, GX_TF_Z16, GX_TF_Z24X8 }, /* ?? */
  { -1, -1, -1, -1 } /* ?? */
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

MATCH_FORCESTRIP static void* TextureLinearConvert(void* img_p, unsigned int width, unsigned int height, unsigned int fmt, unsigned int bpp) {
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
  Mtx m;

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
