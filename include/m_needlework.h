#ifndef M_NEEDLEWORK_H
#define M_NEEDLEWORK_H

#include "types.h"
#include "m_personal_id.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mNW_ORIGINAL_DESIGN_NAME_LEN 16 /* length of design name */
#define mNW_ORIGINAL_DESIGN_WIDTH 32 /* width */
#define mNW_ORIGINAL_DESIGN_HEIGHT 32 /* height */
#define mNW_DEFAULT_ORIGINAL_TEX_NUM 4 /* number of 'default' player textures which are not blank */

#define mNW_CLOTH_DESIGN_NUM 4 /* number of clothing designs in Able Sisters' */
#define mNW_UMBRELLA_DESIGN_NUM 4 /* number of umbrella designs in Able Sisters' */
#define mNW_TOTAL_DESIGN_NUM (mNW_CLOTH_DESIGN_NUM + mNW_UMBRELLA_DESIGN_NUM) /* total designs in Able Sisters' */

#define mNW_DESIGN_TEX_SIZE (mNW_ORIGINAL_DESIGN_HEIGHT * (mNW_ORIGINAL_DESIGN_WIDTH / 2)) /* total texture data size */
#define mNW_PALETTE_COUNT 16 /* number of design palettes */

/* sizeof(mNW_original_design_c) == 0x220 */
typedef struct original_data_s {
  /* 0x000 */ u8 name[mNW_ORIGINAL_DESIGN_NAME_LEN];
  /* 0x010 */ u8 palette;
  /* 0x011 */ u8 pad[15];

  /* 0x020 */ u8 design[mNW_DESIGN_TEX_SIZE];
} mNW_original_design_c;

/* sizeof(mNW_needlework_c) == 0x1100 */
typedef struct needlework_s {
  /* 0x0000 */  mNW_original_design_c original_design[mNW_TOTAL_DESIGN_NUM];
} mNW_needlework_c;

extern void mNW_InitMyOriginal();
extern void mNW_InitOneMyOriginal(int player_no);
extern void mNW_InitNeedleworkData();
extern void mNW_AGB_to_GC_texture(u8* agb, u8* gc);
extern void mNW_GC_to_Agb_texture(u8* gc, u8* agb);
extern u16* mNW_PaletteIdx2Palette(int palette_idx);
extern void mNW_CopyOriginalTextureClass(mNW_original_design_c* dst, mNW_original_design_c* src) ;
extern void mNW_CopyOriginalTexture(void* dst, mNW_original_design_c* src);
extern void mNW_CopyOriginalPalette(void* dst, mNW_original_design_c* src);
extern void mNW_OverWriteOriginalTexture(mNW_original_design_c* dst, u8* src);
extern void mNW_OverWriteOriginalName(mNW_original_design_c* dst, u8* src);
extern void mNW_SwapOriginalData(mNW_original_design_c* org0, mNW_original_design_c* org1);
extern void mNW_InitOriginalData(mNW_original_design_c* design);
extern void mNW_InitPrivateOriginalData(int player_no);

#ifdef __cplusplus
}
#endif

#endif
