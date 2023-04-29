#include "m_needlework.h"

#include "m_string.h"
#include "m_private.h"
#include "m_common_data.h"
#include "libjsys/jsyswrapper.h"
#include "libultra/libultra.h"
#include "m_lib.h"

/**
 * @brief Initializes all designs' palette indexes for a player.
 * 
 * @param player_no The index of the player whose designs will be updated
 **/
static void mNW_InitMyOriginalPallet(int player_no) {
  static u8 pal_table[mPr_ORIGINAL_DESIGN_COUNT] = {
    0, 8, 7, 7,
    0, 0, 0, 0
  };

  int i;

  for (i = 0; i < mPr_ORIGINAL_DESIGN_COUNT; i++) {
    Save_Set(private[player_no & 3].my_org[i & 7].palette, pal_table[i]);
  }
}

/**
 * @brief Initializes all designs' names for a player.
 * 
 * @param player_no The index of the player whose designs will be renamed
 **/
static void mNW_InitMyOriginalName(int player_no) {
  int i;

  player_no &= 3;
  for (i = 0; i < mPr_ORIGINAL_DESIGN_COUNT; i++) {
    /* TODO: define for the string index? */
    mString_Load_StringFromRom(
      Save_Get(private[player_no].my_org[i & 7].name),
      mNW_ORIGINAL_DESIGN_NAME_LEN,
      0x6DF + i
    );
  }
}

/**
 * @brief Initializes all designs' textures for a player.
 * 
 * @param player_no The index of the player whose designs will be updated
 **/
static void mNW_InitMyOriginalTexture(int player_no) {
  int i;

  player_no &= 3;
  for (i = 0; i < mNW_DEFAULT_ORIGINAL_TEX_NUM; i++) {
    _JW_GetResourceAram(
      JW_GetAramAddress(27) + i * mNW_DESIGN_TEX_SIZE,
      Save_Get(private[player_no].my_org[i & 7].design),
      mNW_DESIGN_TEX_SIZE
    );
  }
}

/**
 * @brief Initializes all designs for all players.
 **/
extern void mNW_InitMyOriginal() {
  int i;

  for (i = 0; i < PLAYER_NUM; i++) {
    mNW_InitOneMyOriginal(i);
  }
}

/**
 * @brief Initializes a single player's designs.
 * 
 * @param player_no The index of the player whose designs will be initialized.
 **/
extern void mNW_InitOneMyOriginal(int player_no) {
  int i;

  mNW_InitMyOriginalPallet(player_no & 3);
  mNW_InitMyOriginalName(player_no & 3);
  mNW_InitMyOriginalTexture(player_no & 3);

  for (i = mNW_DEFAULT_ORIGINAL_TEX_NUM; i < mPr_ORIGINAL_DESIGN_COUNT; i++) {
    mNW_InitOriginalData(Save_Get(private[player_no].my_org + (i & 7)));
  }
}

/**
 * @brief Copies a default design texture into the supplied buffer.
 * 
 * @param dst The destination design texture buffer
 * @param tex_no The index of the texture to retrieve (0-7)
 **/
static void mNW_CopyNeedleworkDefaultTexture(u8* dst, int tex_no) {
  u32 addr = JW_GetAramAddress(28);
  _JW_GetResourceAram(
    addr + (tex_no & 7) * mNW_DESIGN_TEX_SIZE,
    dst,
    mNW_DESIGN_TEX_SIZE
  );
}

/**
 * @brief Initializes all Able Sisters' designs to their default textures.
 **/
static void mNW_InitNeedleworkTexture() {
  int i;

  for (i = 0; i < mNW_TOTAL_DESIGN_NUM; i++) {
    mNW_CopyNeedleworkDefaultTexture(Save_Get(needlework.original_design[i & 7].design), i);
  }
}

/**
 * @brief Initializes all Able Sisters' designs to their default palettes.
 **/
static void mNW_InitNeedleworkPelatteNo() {
  static u8 pal_table[mNW_TOTAL_DESIGN_NUM] = {
    7, 1, 10, 3,
    6, 0, 6, 7
  };

  int i;

  for (i = 0; i < mNW_TOTAL_DESIGN_NUM; i++) {
    Save_Set(needlework.original_design[i & 7].palette, pal_table[i]);
  }
}

/**
 * @brief Initializes all Able Sisters' designs to their default names.
 **/
static void mNW_InitNeedleworkTextureName() {
  int i;

  for (i = 0; i < mNW_TOTAL_DESIGN_NUM; i++) {
    mString_Load_StringFromRom(
      Save_Get(needlework.original_design[i & 7].name),
      mNW_ORIGINAL_DESIGN_NAME_LEN,
      0x6E7 + i
    );
  }
}

/**
 * @brief Initializes all Able Sisters' designs to their default data.
 **/
extern void mNW_InitNeedleworkData() {
  mNW_InitNeedleworkTexture();
  mNW_InitNeedleworkPelatteNo();
  mNW_InitNeedleworkTextureName();
}

/**
 * @brief Converts a design texture from GBA format to GC format.
 * 
 * @param agb Pointer to the source GBA texture
 * @param gc Pointer to the destination GC texture
 **/
extern void mNW_AGB_to_GC_texture(u8* agb, u8* gc) {
  int i;

  for (i = 0; i < mNW_DESIGN_TEX_SIZE; i++) {
    u8 src = *agb++;
    *gc++ = (((src >> 4) & 0xF) | ((src & 0xF) << 4));
  }
}

/**
 * @brief Converts a design texture from GC format to GBA format.
 * 
 * @param gc Pointer to the source GC texture
 * @param agb Pointer to the destination GBA texture
 **/
extern void mNW_GC_to_Agb_texture(u8* gc, u8* agb) {
  mNW_AGB_to_GC_texture(gc, agb);
}

/* RGB5A3 color palettes for each pattern palette aligned to 32 bytes */

static u16 needlework0_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0xE529, 0xEE08, 0xF2A3, 0xF304, 0xEB63, 0xDB83, 0xC34A,
  0x9F0D, 0x96B8, 0xA1FD, 0xB53C, 0xC979, 0xDD16, 0x8000, 0xFFFF
};

static u16 needlework1_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0xFE31, 0xFF30, 0xFF8B, 0xFFCC, 0xFFF0, 0xEFEA, 0xDBF0,
  0xBFD5, 0xB39E, 0xC31F, 0xD27F, 0xEA7F, 0xFE7E, 0xC631, 0xFFFF
};

static u16 needlework2_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0xCC63, 0xD541, 0xD9E0, 0xDA40, 0xD2A0, 0xC2C0, 0xAA86,
  0x8647, 0x81F2, 0x8937, 0x9C75, 0xACB2, 0xC42F, 0x8421, 0xFFFF
};

static u16 needlework3_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0xA24B, 0xBB11, 0xCB95, 0x822F, 0xAED5, 0xC318, 0x91D4,
  0xA679, 0xB6BB, 0xBA17, 0xB5D5, 0xA952, 0x9CEF, 0x8C6C, 0xFFFF
};

static u16 needlework4_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0xCE0A, 0xDE4B, 0xEAF0, 0xCD4A, 0xE5CC, 0xF671, 0xC590,
  0xD216, 0xEEDB, 0xDE10, 0xD5CD, 0xC94A, 0xBCE7, 0xB062, 0xFFFF
};

static u16 needlework5_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0xF560, 0xFE68, 0xFF30, 0xFFB4, 0xC525, 0xD9EB, 0xF2B1,
  0xFF77, 0x9A3F, 0xB2DF, 0xCF7F, 0xE39F, 0xB5AD, 0x8000, 0xFFFF
};

static u16 needlework6_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0x9EC8, 0xB36B, 0xC7B0, 0xDBF5, 0x9098, 0xA95E, 0xC21F,
  0xDADF, 0xE4E7, 0xEDAD, 0xF233, 0xF6F7, 0xB5AD, 0x8000, 0xFFFF
};

static u16 needlework7_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0x8480, 0xA167, 0xB60C, 0xCED2, 0xACA0, 0xBD24, 0xD1C9,
  0xEA8F, 0xC9E0, 0xDA47, 0xE6CD, 0xEF53, 0xB5AD, 0x8000, 0xFFFF
};

static u16 needlework8_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0x909F, 0xFC84, 0xEB40, 0xB19F, 0xFD8C, 0xEB4C, 0xCA5F,
  0xFE52, 0xEB52, 0xD6BF, 0xFEB5, 0xF395, 0xB5AD, 0x8000, 0xFFFF
};

static u16 needlework9_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0x9284, 0x9EBF, 0xCD5D, 0xAAEA, 0xAF1F, 0xDA7F, 0xB74E,
  0xC79F, 0xE6DF, 0xCB75, 0xDFDF, 0xEB3F, 0xB5AD, 0x8000, 0xFFFF
};

static u16 needlework10_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0xE800, 0xFEE0, 0xF7C6, 0xA728, 0x9665, 0xAA37, 0xA135,
  0xC95A, 0xF9FB, 0xD247, 0xCD08, 0xACC7, 0xB5AD, 0x8000, 0xFFFF
};

static u16 needlework11_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0xF323, 0x9303, 0xFDA0, 0x801F, 0xC817, 0xF323, 0x8280,
  0xE500, 0x801A, 0xAC11, 0xCE23, 0x8200, 0xD080, 0x8014, 0xA40B
};

static u16 needlework12_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0xFC84, 0xF340, 0xF8F7, 0x8353, 0x89C2, 0xE084, 0xDE80,
  0xE4F2, 0x826D, 0x9124, 0xC484, 0xC1A0, 0xC86C, 0x81C9, 0x8CE3
};

static u16 needlework13_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0xF75A, 0xEF18, 0xE6D6, 0xDE94, 0xD652, 0xCE10, 0xC5CE,
  0xBD8C, 0xB54A, 0xAD08, 0xA4C6, 0x9C84, 0x9442, 0x8C00, 0x8800
};

static u16 needlework14_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0xF7BD, 0xEF7B, 0xE739, 0xDEF7, 0xD6B5, 0xCE73, 0xC631,
  0xBDEF, 0xB5AD, 0xAD6B, 0xA529, 0x9CE7, 0x94A5, 0x8C63, 0x8842
};

static u16 needlework15_pal[16] ATTRIBUTE_ALIGN(32) = {
  0xA94A, 0xF5EF, 0xE863, 0xFA43, 0xF38A, 0x81A0, 0x9EC7, 0x80F6,
  0x9E7F, 0xC812, 0xFDBF, 0xC901, 0xF66B, 0xFF12, 0x8000, 0xFFFF
};

static u16* mNW_needlework_pallet_table[mNW_PALETTE_COUNT] = {
  needlework0_pal, needlework1_pal, needlework2_pal, needlework3_pal,
  needlework4_pal, needlework5_pal, needlework6_pal, needlework7_pal,
  needlework8_pal, needlework9_pal, needlework10_pal, needlework11_pal,
  needlework12_pal, needlework13_pal, needlework14_pal, needlework15_pal
};

/**
 * @brief Gets a pointer to the requested palette color data.
 * 
 * @param palette_idx Index of the palette to retrieve (0-15)
 * @return Palette color data pointer
 **/
extern u16* mNW_PaletteIdx2Palette(int palette_idx) {
  return mNW_needlework_pallet_table[palette_idx & 15];
}

/**
 * @brief Copies one design class to another and updates data cache.
 * 
 * @param dst Destination design class
 * @param src Source design class
 **/
extern void mNW_CopyOriginalTextureClass(mNW_original_design_c* dst, mNW_original_design_c* src) {
  bcopy(src, dst, sizeof(mNW_original_design_c));
  DCStoreRangeNoSync(dst->design, mNW_DESIGN_TEX_SIZE);
}

/**
 * @brief Copies a design's texture data to a block of memory and updates data cache.
 * 
 * @param dst Destination pointer
 * @param src Source design class
 **/
extern void mNW_CopyOriginalTexture(void* dst, mNW_original_design_c* src) {
  if (dst != NULL) {
    bcopy(src->design, dst, mNW_DESIGN_TEX_SIZE);
    DCStoreRangeNoSync(dst, mNW_DESIGN_TEX_SIZE);
  }
}

/**
 * @brief Copies a design's palette colors to a block of memory and updates data cache.
 * 
 * @param dst Destination pointer
 * @param src Source design class
 **/
extern void mNW_CopyOriginalPalette(void* dst, mNW_original_design_c* src) {
  if (dst != NULL) {
    bcopy(mNW_PaletteIdx2Palette(src->palette), dst, 16 * sizeof(u16));
    DCStoreRangeNoSync(dst, 16 * sizeof(u16));
  }
}

/**
 * @brief Copies a block of memory to a design's texture data and updates data cache.
 * 
 * @param dst The destination design class
 * @param src Source data pointer
 **/
extern void mNW_OverWriteOriginalTexture(mNW_original_design_c* dst, u8* src) {
  if (src != NULL) {
    u8* tex = dst->design; 
    bcopy(src, tex, mNW_DESIGN_TEX_SIZE);
    DCStoreRangeNoSync(tex, mNW_DESIGN_TEX_SIZE);
  }
}

/**
 * @brief Copies a block of memory to a design's name.
 * 
 * @param dst The destination design class
 * @param src Source name pointer
 **/
extern void mNW_OverWriteOriginalName(mNW_original_design_c* dst, u8* src) {
  if (src != NULL) {
    bcopy(src, dst->name, mNW_ORIGINAL_DESIGN_NAME_LEN);
  }
}

/* swap buffer for original design */
static mNW_original_design_c mNW_swap_work;

/**
 * @brief Swaps two design classes' data in memory and updates data cache.
 * 
 * @param org0 First design class
 * @param org1 Second design class
 **/
extern void mNW_SwapOriginalData(mNW_original_design_c* org0, mNW_original_design_c* org1) {
  bcopy(org0, &mNW_swap_work, sizeof(mNW_original_design_c));
  bcopy(org1, org0, sizeof(mNW_original_design_c));
  bcopy(&mNW_swap_work, org1, sizeof(mNW_original_design_c));
  DCStoreRangeNoSync(org0->design, mNW_DESIGN_TEX_SIZE);
  DCStoreRangeNoSync(org1->design, mNW_DESIGN_TEX_SIZE);
}

/**
 * @brief Initializes a design class to 'blank' data.
 * 
 * @param design The design which will be initialized
 **/
extern void mNW_InitOriginalData(mNW_original_design_c* design) {
  static u8 name[mNW_ORIGINAL_DESIGN_NAME_LEN] = "blank           ";

  u8* tex;
  mNW_OverWriteOriginalName(design, name);
  tex = design->design;
  mem_clear(tex, mNW_DESIGN_TEX_SIZE, 0xFF);
  DCStoreRangeNoSync(tex, mNW_DESIGN_TEX_SIZE);
  design->palette = 0;
}

/**
 * @brief Initializes a player's design related data to the default state.
 * 
 * @param player_no The index of the player whose design data will be initialized
 **/
extern void mNW_InitPrivateOriginalData(int player_no) {
  int i;
  Private_c* private = Save_Get(private + player_no);

  for (i = 0; i < mPr_ORIGINAL_DESIGN_COUNT; i++) {
    private->my_org_no_table[i] = i;
  }

  for (i = 0; i < mPr_ORIGINAL_DESIGN_COUNT; i++) {
    mNW_InitOriginalData(private->my_org + i);
  }
}
