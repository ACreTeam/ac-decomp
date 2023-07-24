#ifndef M_FIELD_MAKE_H
#define M_FIELD_MAKE_H

#include "types.h"
#include "m_actor_type.h"
#include "libforest/gbi_extensions.h"
#include "game_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLOCK_X_NUM 7
#define BLOCK_Z_NUM 10
#define BLOCK_TOTAL_NUM (BLOCK_X_NUM * BLOCK_Z_NUM)

#define FG_BLOCK_X_NUM (BLOCK_X_NUM - 2) /* 5 */
#define FG_BLOCK_Z_NUM (BLOCK_Z_NUM - 4) /* 6 */
#define FG_BLOCK_TOTAL_NUM (FG_BLOCK_X_NUM * FG_BLOCK_Z_NUM)

#define UT_X_NUM 16 /* Spaces per block (acre) in x direction */
#define UT_Z_NUM 16 /* Spaces per block (acre) in z direction */
#define UT_TOTAL_NUM (UT_X_NUM * UT_Z_NUM)

#define IDX_2_UT_X(idx) ((idx) & (UT_X_NUM - 1))
#define IDX_2_UT_Z(idx) (((idx) / UT_X_NUM) & (UT_Z_NUM - 1))

#define FGIDX_2_BLOCK_X(idx) ((idx) % FG_BLOCK_X_NUM + 1)
#define FGIDX_2_BLOCK_Z(idx) ((idx) / FG_BLOCK_X_NUM + 1)
#define FGBLOCKXZ_2_FGIDX(x, z) ((z) * FG_BLOCK_X_NUM + (x))

#define BLOCKXZ_2_BLOCKIDX(x, z) ((z) * BLOCK_X_NUM + (x))

#define mFM_VISIBLE_BLOCK_NUM 4 /* number of visible blocks (nearest to the Player) */

/* sizeof(mFM_combination_c) == 2 */
typedef struct block_combination_s {
  /* 0x00 */ u16 combination_type:14; /* acre type index */
  /* 0x00 */ u16 height:2; /* 0, 1, 2, or 3 (unused) */
} mFM_combination_c;

/* sizeof(mFM_fg_c) == 0x200 */
typedef struct fg_items_s {
  /* 0x000 */ mActor_name_t items[UT_Z_NUM][UT_X_NUM];
} mFM_fg_c;

/* sizeof (mFM_combo_info_c) == 6 */
typedef struct block_combo_s {
  /* 0x00 */ mActor_name_t bg_id;
  /* 0x02 */ mActor_name_t fg_id;
  /* 0x05 */ u8 type;
} mFM_combo_info_c;

typedef struct field_display_list_info_s {
  int block_x;
  int block_z;
  u8* display_list;
} mFM_field_draw_info_c;

typedef struct field_pal_s {
  u16* earth_pal;
  u16* cliff_pal;
  u16* bush_pal;
  u16* flower0_pal;
  u16* flower1_pal;
  u16* flower2_pal;
  u16* grass_pal;
  u16* tree_pal;
  u16* cedar_tree_pal; // probably?
  u16* palm_tree_pal;
  u16* golden_tree_pal;
} mFM_field_pal_c;

typedef struct field_bg_info_s {
  mFM_combination_c bg_id;
  Gfx* oapque_gfx;
  Gfx* translucent_gfx;

} mFM_bg_info_c;

typedef struct field_info_s {
  mActor_name_t field_id;
  u32 _04; // only set, never read?
  mFM_field_draw_info_c bg_draw_info[mFM_VISIBLE_BLOCK_NUM];
  u8* bg_display_list_p[mFM_VISIBLE_BLOCK_NUM];
  mFM_field_pal_c field_palette;

} mFM_fdinfo_c;

extern u8* g_block_type_p;
extern int* g_block_kind_p;

extern void mFM_DecideBgTexIdx(u8* bg_tex_idx);
extern void mFM_InitFgCombiSaveData(GAME* game);

#ifdef __cplusplus
}
#endif

#endif
