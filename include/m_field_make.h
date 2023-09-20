#ifndef M_FIELD_MAKE_H
#define M_FIELD_MAKE_H

#include "types.h"
#include "m_actor_type.h"
#include "libforest/gbi_extensions.h"
#include "game_h.h"
#include "m_play_h.h"
#include "evw_anime.h"
#include "m_collision_bg.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BLOCK_X_NUM 7
#define BLOCK_Z_NUM 10
#define BLOCK_TOTAL_NUM (BLOCK_X_NUM * BLOCK_Z_NUM)

#define FG_BLOCK_X_NUM (BLOCK_X_NUM - 2) /* 5 */
#define FG_BLOCK_Z_NUM (BLOCK_Z_NUM - 4) /* 6 */
#define FG_BLOCK_TOTAL_NUM (FG_BLOCK_X_NUM * FG_BLOCK_Z_NUM)

#define UT_BASE_NUM 16
#define UT_X_NUM UT_BASE_NUM /* Spaces per block (acre) in x direction */
#define UT_Z_NUM UT_BASE_NUM /* Spaces per block (acre) in z direction */
#define UT_TOTAL_NUM (UT_X_NUM * UT_Z_NUM)

#define IDX_2_UT_X(idx) ((idx) & (UT_X_NUM - 1))
#define IDX_2_UT_Z(idx) (((idx) / UT_X_NUM) & (UT_Z_NUM - 1))

#define FGIDX_2_BLOCK_X(idx) ((idx) % FG_BLOCK_X_NUM + 1)
#define FGIDX_2_BLOCK_Z(idx) ((idx) / FG_BLOCK_X_NUM + 1)
#define FGBLOCKXZ_2_FGIDX(x, z) ((z) * FG_BLOCK_X_NUM + (x))

#define BLOCKXZ_2_BLOCKIDX(x, z) ((z) * BLOCK_X_NUM + (x))

#define mFM_VISIBLE_BLOCK_NUM 4 /* number of visible blocks (nearest to the Player) */
#define mFM_SOUND_SOURCE_NUM 6
#define mFM_MOVE_ACTOR_NUM 16
#define mFM_HANIWA_STEP_NUM 4

#define mFM_BG_ID_MAX 293

#define mFM_FG_START 0
#define mFM_FG_NUM 416
#define mFM_FG_NPC_START mFM_FG_NUM
#define mFM_FG_NPC_NUM 536
#define mFM_FG_ID_MAX (mFM_FG_NUM + mFM_FG_NPC_NUM)
#define mFM_FG2_ID_MAX 743

#define mFM_FIELD_PAL_NUM 12
#define mFM_FIELD_TEX_NUM 27

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

typedef struct field_bg_sound_source_s {
  s16 kind;
  xyz_t pos;
} mFM_bg_sound_source_c;

typedef struct field_bg_info_s {
  mFM_combination_c bg_id;
  Gfx* opaque_gfx;
  Gfx* translucent_gfx;
  EVW_ANIME_DATA* animation;
  s8 animation_count;
  u8 block_type;
  u32 block_kind;
  int _18;
  int _1C;
  mCoBG_Collision_u collision[UT_Z_NUM][UT_X_NUM];
  u8 keep_h[UT_Z_NUM][UT_X_NUM]; // base height?
  mFM_bg_sound_source_c sound_source[mFM_SOUND_SOURCE_NUM];
} mFM_bg_info_c;

typedef struct field_fg_move_actor_s {
  mActor_name_t name_id;
  s8 ut_x;
  s8 ut_z;
  s8 npc_info_idx;
  s16 arg;
} mFM_move_actor_c;

typedef struct field_fg_move_actor_data_s {
  mActor_name_t name_id;
  int block_x;
  int block_z;
  u8 ut_x;
  u8 ut_z;
  s8 npc_info_idx;
  s16 arg;
  u32 desired_block_kind;
} mFM_move_actor_data_c;

typedef struct field_fg_info_s {
  mActor_name_t fg_id;
  mActor_name_t* items_p;
  u16* deposit_p;
  mFM_move_actor_c move_actors[mFM_MOVE_ACTOR_NUM];
  u16 move_actor_bit_data;
  u8 haniwa_step[mFM_HANIWA_STEP_NUM];
} mFM_fg_info_c;

typedef struct field_block_info_s {
  mFM_bg_info_c bg_info;
  mFM_fg_info_c fg_info;
} mFM_block_info_c;

typedef struct field_bg_sound_source_data_s {
  s16 kind;
  u8 ut_x;
  u8 ut_z;
} mFM_bg_sound_source_data_c;

typedef struct field_bg_data_s {
  mActor_name_t bg_id;
  Gfx* opaque_gfx;
  Gfx* translucent_gfx;
  EVW_ANIME_DATA* animation;
  s8 animation_count;
  u32 _14;
  u32 _18;
  mCoBG_Collision_u collision[UT_Z_NUM][UT_X_NUM];
  mFM_bg_sound_source_data_c sound_source[mFM_SOUND_SOURCE_NUM];
} mFM_bg_data_c;

typedef struct field_fg_data_s {
  mActor_name_t fg_id;
  mActor_name_t items[UT_Z_NUM][UT_X_NUM];
  u8 haniwa_step[mFM_HANIWA_STEP_NUM];
} mFM_fg_data_c;

typedef struct field_data_s {
  mActor_name_t field_name;
  u8 block_x_max;
  u8 block_z_max;
  mFM_combination_c combi[BLOCK_TOTAL_NUM];
  mFM_move_actor_data_c* move_actor_data;
  u32 _94;
  u32 _98;
  u32 _9C;
  u32 _A0;
} mFM_field_data_c;

typedef struct field_info_s {
  mActor_name_t field_id;
  u32 _04; // only set, never read?
  mFM_field_draw_info_c bg_draw_info[mFM_VISIBLE_BLOCK_NUM];
  u8* bg_display_list_p[mFM_VISIBLE_BLOCK_NUM];
  mFM_field_pal_c field_palette;
  mFM_block_info_c* block_info;
  mActor_name_t** fg2_p;
  int last_bg_idx[mFM_VISIBLE_BLOCK_NUM];
  u16 bg_max;
  u8 bg_num;
  u8 update_fg;
  u8 born_item;
  u8 born_actor;
  u8 block_x_max;
  u8 block_z_max;
} mFM_fdinfo_c;

enum {
  mFM_BG_TEX_TRIANGLE,
  mFM_BG_TEX_SQUARE,
  mFM_BG_TEX_CIRCLE,

  mFM_BG_TEX_NUM
};

extern u8* g_block_type_p;
extern int* g_block_kind_p;

extern mFM_fdinfo_c* g_fdinfo;
extern int l_bg_disp_num;
extern int l_bg_disp_size;

extern mFM_bg_data_c data_bgd[];
extern int data_bgd_number;

extern void mFM_GetPolicePos(int* bx, int* bz, int* ut_x, int* ut_z);
extern void mFM_DecideBgTexIdx(u8* bg_tex_idx);
extern void mFM_SetFieldInitData(int bg_disp_num, int bg_disp_size);
extern void mFM_FieldInit(GAME_PLAY* play);
extern void mFM_Field_dt();
extern void mFM_SetBlockKindLoadCombi();
extern void mFM_InitFgCombiSaveData(GAME* game);
extern void mFM_RenewalReserve();
extern mActor_name_t mFM_GetReseveName(int bx, int bz);
extern void mFM_toSummer();
extern void mFM_returnSeason();
extern void mFM_RestoreIslandBG(int* island_x_blocks, int bx_num);
extern void mFM_SetIslandNpcRoomData(GAME* game, int malloc_flag);

#ifdef __cplusplus
}
#endif

#endif
