#ifndef M_FIELD_MAKE_H
#define M_FIELD_MAKE_H

#include "types.h"
#include "m_actor_type.h"
#include "libforest/gbi_extensions.h"
#include "game_h.h"
#include "m_play_h.h"
#include "evw_anime.h"
#include "m_collision_bg.h"
#include "m_combi_type.h"

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
#define UNITXZ_2_UNIT(x, z) ((z) * UT_X_NUM + (x))

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

enum {
    mFM_BLOCK_TYPE_BORDER_CLIFF_TOP,
    mFM_BLOCK_TYPE_BORDER_CLIFF_RIVER,
    mFM_BLOCK_TYPE_BORDER_CLIFF_LEFT,
    mFM_BLOCK_TYPE_3,
    mFM_BLOCK_TYPE_BORDER_CLIFF_RIGHT,
    mFM_BLOCK_TYPE_BORDER_CLIFF_CORNER_TOP_LEFT,
    mFM_BLOCK_TYPE_6,
    mFM_BLOCK_TYPE_TRACKS,
    mFM_BLOCK_TYPE_BORDER_CLIFF_CORNER_TOP_RIGHT,
    mFM_BLOCK_TYPE_BORDER_CLIFF_LEFT_TUNNEL,
    mFM_BLOCK_TYPE_BORDER_CLIFF_RIGHT_TUNNEL,
    mFM_BLOCK_TYPE_TRACKS_STATION,
    mFM_BLOCK_TYPE_TRACKS_DUMP,
    mFM_BLOCK_TYPE_TRACKS_RIVER,
    mFM_BLOCK_TYPE_PLAYER_HOUSE,
    mFM_BLOCK_TYPE_CLIFF_HORIZONTAL,
    mFM_BLOCK_TYPE_CLIFF_BOTTOM_RIGHT_CORNER,
    mFM_BLOCK_TYPE_CLIFF_VERTICAL_RIGHT,
    mFM_BLOCK_TYPE_CLIFF_TOP_RIGHT_CORNER,
    mFM_BLOCK_TYPE_CLIFF_TOP_LEFT_CORNER,
    mFM_BLOCK_TYPE_CLIFF_VERTICAL_LEFT,
    mFM_BLOCK_TYPE_CLIFF_BOTTOM_LEFT_CORNER,
    mFM_BLOCK_TYPE_WATERFALL_STRAIGHT_CLIFF_HORIZONTAL,
    mFM_BLOCK_TYPE_WATERFALL_STRAIGHT_CLIFF_BOTTOM_RIGHT_CORNER,
    mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_RIGHT,
    mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_TOP_RIGHT_CORNER,
    mFM_BLOCK_TYPE_WATERFALL_STRAIGHT_CLIFF_TOP_LEFT_CORNER,
    mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_LEFT,
    mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_BOTTOM_LEFT_CORNER,
    mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_HORIZONTAL,
    mFM_BLOCK_TYPE_WATERFALL_EAST_CLIFF_BOTTOM_RIGHT_CORNER,
    mFM_BLOCK_TYPE_WATERFALL_EAST_CLIFF_VERTICAL_RIGHT,
    mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_RIGHT_CORNER,
    mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_LEFT_CORNER,
    mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_HORIZONTAL,
    mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_RIGHT_CORNER,
    mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_LEFT_CORNER,
    mFM_BLOCK_TYPE_WATERFALL_WEST_CLIFF_VERTICAL_LEFT,
    mFM_BLOCK_TYPE_WATERFALL_WEST_CLIFF_BOTTOM_LEFT_CORNER,
    mFM_BLOCK_TYPE_FLAT, // grass
    mFM_BLOCK_TYPE_RIVER_SOUTH,
    mFM_BLOCK_TYPE_RIVER_EAST,
    mFM_BLOCK_TYPE_RIVER_WEST,
    mFM_BLOCK_TYPE_RIVER_SOUTH_EAST,
    mFM_BLOCK_TYPE_RIVER_EAST_SOUTH,
    mFM_BLOCK_TYPE_RIVER_SOUTH_WEST,
    mFM_BLOCK_TYPE_RIVER_WEST_SOUTH,
    mFM_BLOCK_TYPE_RIVER_SOUTH_BRIDGE,
    mFM_BLOCK_TYPE_RIVER_EAST_BRIDGE,
    mFM_BLOCK_TYPE_RIVER_WEST_BRIDGE,
    mFM_BLOCK_TYPE_RIVER_SOUTH_EAST_BRIDGE,
    mFM_BLOCK_TYPE_RIVER_EAST_SOUTH_BRIDGE,
    mFM_BLOCK_TYPE_RIVER_SOUTH_WEST_BRIDGE,
    mFM_BLOCK_TYPE_RIVER_WEST_SOUTH_BRIDGE,
    mFM_BLOCK_TYPE_SLOPE_HORIZONTAL,
    mFM_BLOCK_TYPE_SLOPE_BOTTOM_RIGHT_CORNER,
    mFM_BLOCK_TYPE_SLOPE_VERTICAL_RIGHT,
    mFM_BLOCK_TYPE_SLOPE_TOP_RIGHT_CORNER,
    mFM_BLOCK_TYPE_SLOPE_TOP_LEFT_CORNER,
    mFM_BLOCK_TYPE_SLOPE_VERTICAL_LEFT,
    mFM_BLOCK_TYPE_SLOPE_BOTTOM_LEFT_CORNER,
    mFM_BLOCK_TYPE_BORDER_CLIFF_LEFT_TRANSITION,
    mFM_BLOCK_TYPE_BORDER_CLIFF_RIGHT_TRANSITION,
    mFM_BLOCK_TYPE_BEACH,
    mFM_BLOCK_TYPE_BEACH_RIVER,
    mFM_BLOCK_TYPE_TRACKS_SHOP,
    mFM_BLOCK_TYPE_SHRINE,
    mFM_BLOCK_TYPE_TRACKS_POST_OFFICE,
    mFM_BLOCK_TYPE_POLICE_BOX,
    mFM_BLOCK_TYPE_POOL_SOUTH,
    mFM_BLOCK_TYPE_POOL_EAST,
    mFM_BLOCK_TYPE_POOL_WEST,
    mFM_BLOCK_TYPE_POOL_SOUTH_EAST,
    mFM_BLOCK_TYPE_POOL_EAST_SOUTH,
    mFM_BLOCK_TYPE_POOL_SOUTH_WEST,
    mFM_BLOCK_TYPE_POOL_WEST_SOUTH,
    mFM_BLOCK_TYPE_TRACKS6,
    mFM_BLOCK_TYPE_TRACKS7,
    mFM_BLOCK_TYPE_TRACKS8,
    mFM_BLOCK_TYPE_TRACKS9,
    mFM_BLOCK_TYPE_BORDER_CLIFF_OCEAN_LEFT,
    mFM_BLOCK_TYPE_BORDER_CLIFF_OCEAN_RIGHT,
    mFM_BLOCK_TYPE_BEACH_RIVER_BRIDGE,
    mFM_BLOCK_TYPE_OCEAN,
    mFM_BLOCK_TYPE_MUSEUM,
    mFM_BLOCK_TYPE_NEEDLEWORK,
    mFM_BLOCK_TYPE_TRACKS_RIVER_BRIDGE,
    mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_HORIZONTAL_BRIDGE,
    mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_RIGHT_BRIDGE,
    mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_TOP_RIGHT_CORNER_BRIDGE,
    mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_RIGHT_CORNER_BRIDGE,
    mFM_BLOCK_TYPE_RIVER_EAST_CLIFF_TOP_LEFT_CORNER_BRIDGE,
    mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_VERTICAL_LEFT_BRIDGE,
    mFM_BLOCK_TYPE_RIVER_STRAIGHT_CLIFF_BOTTOM_LEFT_CORNER_BRIDGE,
    mFM_BLOCK_TYPE_OCEAN_2,
    mFM_BLOCK_TYPE_OCEAN_3,
    mFM_BLOCK_TYPE_OCEAN_4,
    mFM_BLOCK_TYPE_OCEAN_5,
    mFM_BLOCK_TYPE_ISLAND_LEFT,
    mFM_BLOCK_TYPE_ISLAND_RIGHT,
    mFM_BLOCK_TYPE_PORT,
    mFM_BLOCK_TYPE_SEA_EXCEPTIONAL,
    mFM_BLOCK_TYPE_OCEAN_6,
    mFM_BLOCK_TYPE_OCEAN_7,
    mFM_BLOCK_TYPE_OCEAN_8,
    mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_HORIZONTAL_BRIDGE,
    mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_RIGHT_CORNER_BRIDGE,
    mFM_BLOCK_TYPE_RIVER_WEST_CLIFF_TOP_LEFT_CORNER_BRIDGE,

    mFM_BLOCK_TYPE_NUM,

    mFM_BLOCK_TYPE_NONE = 255
};

/* sizeof(mFM_combination_c) == 2 */
typedef struct block_combination_s {
    /* 0x00 */ u16 combination_type : 14; /* acre type index */
    /* 0x00 */ u16 height : 2;            /* 0, 1, 2, or 3 (unused) */
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
    u32 dma_loaded;
} mFM_field_draw_info_c;

typedef struct field_pal_s {
/* 0x00 */ u16* earth_pal;
/* 0x04 */ u16* cliff_pal;
/* 0x08 */ u16* bush_pal;
/* 0x0C */ u16* flower0_pal;
/* 0x10 */ u16* flower1_pal;
/* 0x14 */ u16* flower2_pal;
/* 0x18 */ u16* grass_pal;
/* 0x1C */ u16* tree_pal;
/* 0x20 */ u16* cedar_tree_pal; // probably?
/* 0x24 */ u16* palm_tree_pal;
/* 0x28 */ u16* golden_tree_pal;
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
    int rom_start_addr;
    int rom_size;
    mCoBG_Collision_u collision[UT_Z_NUM][UT_X_NUM];
    u8 keep_h[UT_Z_NUM][UT_X_NUM]; // base height?
    mFM_bg_sound_source_c sound_source[mFM_SOUND_SOURCE_NUM];
} mFM_bg_info_c;

typedef struct field_fg_move_actor_s {
    mActor_name_t name_id;
    u8 ut_x;
    u8 ut_z;
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
    u32 rom_start_addr;
    u32 rom_end_addr;
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
