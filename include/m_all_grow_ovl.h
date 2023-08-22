#ifndef M_ALL_GROW_OVL_H
#define M_ALL_GROW_OVL_H

#include "types.h"
#include "m_time.h"
#include "m_field_info.h"
#include "m_field_make.h"
#include "m_island.h"
#include "m_private.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mAGrw_FOSSIL_NUM 5
#define mAGrw_HANIWA_NUM 3
#define mAGrw_FTR_TREE_NUM 2
#define mAGrw_MAX_PAST_DAYS 5
#define mAGrw_GRASS_TABLE_NUM 12
#define mAGrw_MONEY_TREE_NUM 30
#define mAGrw_MAX_TREES_PER_BLOCK 32
#define mAGrw_ISL_TREE_MAX_LINE 3
#define mAGrw_ISL_MAX_TREES_PER_BLOCK 15
#define mAGrw_DUMP_ITEM_NUM 2
#define mAGrw_GRASS_PER_DAY 5

enum {
  mAGrw_GROW_FIRST,
  mAGrw_GROW,
  mAGrw_GROW_FIRST_FORCE, /* Used when you go back in time */

  mAGrw_GROW_ISLAND_FIRST,
  mAGrw_GROW_ISLAND,
  mAGrw_GROW_ISLAND_FIRST_FORCE, /* Used when you go back in time */

  mAGrw_GROW_NUM
};

enum {
  mAGrw_TREE000,
  mAGrw_TREE001,
  mAGrw_TREE002,
  mAGrw_TREE003,
  mAGrw_TREE004,

  mAGrw_TREE_STAGE_NUM
};

enum {
  mAGrw_AROUND_TOP,
  mAGrw_AROUND_BOTTOM,
  mAGrw_AROUND_LEFT,
  mAGrw_AROUND_RIGHT,

  mAGrw_AROUND_NUM
};

enum {
  mAGrw_FLOWER_TIME,
  mAGrw_NOT_FLOWER_TIME,

  mAGrw_FLOWER_TIME_NUM
};

enum {
  mAGrw_TREE_TYPE_APPLE,
  mAGrw_TREE_TYPE_CHESTNUT, // cherry tree
  mAGrw_TREE_TYPE_PEAR,
  mAGrw_TREE_TYPE_PEACH,
  mAGrw_TREE_TYPE_ORANGE,
  mAGrw_TREE_TYPE_NORMAL,
  mAGrw_TREE_TYPE_MONEY,
  mAGrw_TREE_TYPE_PALM,
  mAGrw_TREE_TYPE_CEDAR,
  mAGrw_TREE_TYPE_GOLD,

  mAGrw_TREE_TYPE_NUM
};

enum {
  mAGrw_KILL_PALM_TREE,
  mAGrw_KILL_CEDAR_TREE,

  mAGrw_KILL_TREE_NUM
};

enum {
  mAGrw_CARP_UNCHANGED,
  mAGrw_CARP_PLACE,
  mAGrw_CARP_REMOVE,

  mAGrw_CARP_NUM
};

enum {
  mAGrw_CHECK_CANCEL_12,
  mAGrw_CHECK_CANCEL_32,
  mAGrw_CHECK_CANCEL_22,
  mAGrw_CHECK_CANCEL_36,
  mAGrw_CHECK_CANCEL_LEFT_45,
  mAGrw_CHECK_CANCEL_RIGHT_45,
  mAGrw_CHECK_CANCEL_46,
  mAGrw_CHECK_CANCEL_23,
  mAGrw_CHECK_CANCEL_57,
  mAGrw_CHECK_CANCEL_68,
  mAGrw_CHECK_CANCEL_77,

  mAGrw_CHECK_CANCEL_NUM
};

typedef struct shine_stone_pos_info {
  u8 block_x;
  u8 block_z;
  u8 ut_x;
  u8 ut_z;
} mAGrw_SSPosInfo_c;

typedef struct allgrow_s {
  mAGrw_SSPosInfo_c shine_pos[TOTAL_PLAYER_NUM];
  mAGrw_SSPosInfo_c stone_pos[TOTAL_PLAYER_NUM];
} mAGrw_AllGrow_c;

typedef struct grow_info_s {
  mFM_fg_c* around_block[mAGrw_AROUND_NUM];

  int check_plant;
  int past_days;
  int block_height;
  int ocean_row;
  int flower_time;
  int spoil_kabu;

  int block_x;
  int block_z;
  int ut_x;
  int ut_z;

  int deposited_item;
  int money_tree_num;
  u8 fossil_record;
  int fossil_num;
  u8 honeycomb_tree_record;
  u8 ftr_tree_record;
  u8 money_stone_spawned;
} mAGrw_GrowInfo_c;

typedef struct carp_block_info_s {
  u8 signboard_in_block:1;
  u8 carp_already_exists:1;
  u8 villager_house_in_block:1;
  u8 signboard_count:5;
} mAGrw_CarpBlockInfo_c;

typedef struct carp_info_s {
  mAGrw_CarpBlockInfo_c block_flags[FG_BLOCK_TOTAL_NUM];
  u8 signboard_blocks;
  u8 carp_blocks;
  u8 villager_house_blocks;
} mAGrw_CarpInfo_c;

extern void mAGrw_ClearMoneyStoneShineGround();
extern void mAGrw_ClearAllShine_Stone();
extern void mAGrw_RestoreStoneShine(int player_no);
extern void mAGrw_SetHideUtInfo(u16* hide, mActor_name_t* items);
extern void mAGrw_SearchDump(mFI_unit_c* dump_info);
extern void mAGrw_SpoilKabuIsland(Island_c* island);
extern void mAGrw_RenewalFgItem_ovl(lbRTC_time_c* now_time, int* deposit_haniwa);

#ifdef __cplusplus
}
#endif

#endif
