#ifndef M_NAME_TABLE_H
#define M_NAME_TABLE_H

#include "types.h"
#include "m_actor_type.h"
#include "m_collision_bg.h"
#include "m_name_table_floor_decl.h"
#include "m_name_table_wall_decl.h"

/* TODO: these defintions are likely included from an auto-gen source */

#ifdef __cplusplus
extern "C" {
#endif

// clang-format off

enum {
  NAME_TYPE_ITEM0,  /* Scenery items */
  NAME_TYPE_FTR0,   /* Furniture 0 */
  NAME_TYPE_ITEM1,  /* Obtainable items */
  NAME_TYPE_FTR1,   /* Furniture 1 */
  NAME_TYPE_WARP,   /* Loading zones */
  NAME_TYPE_STRUCT, /* Structures */
  NAME_TYPE_PAD6,   /* Unused? */
  NAME_TYPE_PAD7,   /* Unused? */
  NAME_TYPE_ITEM2,  /* Misc items */
  NAME_TYPE_ACTOR,  /* Actors */
  NAME_TYPE_PROPS,  /* Props */
  NAME_TYPE_PADB,   /* Unused? */
  NAME_TYPE_PADC,   /* Unused? */
  NAME_TYPE_SPNPC,  /* Special NPCs */
  NAME_TYPE_NPC,    /* Villager NPCs */
  NAME_TYPE_PAD15,  /* Unused? */

  NAME_TYPE_NUM
};

#define ITEM0_CAT_OBJ 0
#define ITEM0_CAT_PLANT 8
#define ITEM0_CAT_SIGN 9

enum {
  ITEM1_CAT_PAPER,
  ITEM1_CAT_MONEY,
  ITEM1_CAT_TOOL,
  ITEM1_CAT_FISH,
  ITEM1_CAT_CLOTH,
  ITEM1_CAT_ETC,
  ITEM1_CAT_CARPET,
  ITEM1_CAT_WALL,
  ITEM1_CAT_FRUIT,
  ITEM1_CAT_PLANT,
  ITEM1_CAT_MINIDISK,
  ITEM1_CAT_DUMMY, /* diaries */
  ITEM1_CAT_TICKET,
  ITEM1_CAT_INSECT,
  ITEM1_CAT_HUKUBUKURO,
  ITEM1_CAT_KABU,

  ITEM1_CAT_NUM
};

enum {
  mNT_TREE_TYPE_NORMAL,
  mNT_TREE_TYPE_PALM,
  mNT_TREE_TYPE_CEDAR,
  mNT_TREE_TYPE_GOLD,

  mNT_TREE_TYPE_NUM
};

enum {
  mNT_ITEM_TYPE_NONE,
  mNT_ITEM_TYPE_APPLE,
  mNT_ITEM_TYPE_ORANGE,
  mNT_ITEM_TYPE_PEACH,
  mNT_ITEM_TYPE_PEAR,
  mNT_ITEM_TYPE_NUTS,
  mNT_ITEM_TYPE_MATSUTAKE,
  mNT_ITEM_TYPE_KABU,
  mNT_ITEM_TYPE_FISH,
  mNT_ITEM_TYPE_BAG,
  mNT_ITEM_TYPE_LEAF,
  mNT_ITEM_TYPE_ROLL,
  mNT_ITEM_TYPE_BOX,
  mNT_ITEM_TYPE_PACK,
  mNT_ITEM_TYPE_PRESENT,
  mNT_ITEM_TYPE_SEED,
  mNT_ITEM_TYPE_HANIWA,
  mNT_ITEM_TYPE_ETC,
  mNT_ITEM_TYPE_CAGE,
  mNT_ITEM_TYPE_TOOL,
  mNT_ITEM_TYPE_FOSSIL,
  mNT_ITEM_TYPE_TRASH,
  mNT_ITEM_TYPE_LETTER,
  mNT_ITEM_TYPE_OTOSI,
  mNT_ITEM_TYPE_SHELLA,
  mNT_ITEM_TYPE_SHELLB,
  mNT_ITEM_TYPE_SHELLC,
  mNT_ITEM_TYPE_CANDY,
  mNT_ITEM_TYPE_COCONUT,
  mNT_ITEM_TYPE_OMIKUJI,
  mNT_ITEM_TYPE_CLOTH,
  mNT_ITEM_TYPE_CARPET,
  mNT_ITEM_TYPE_WALL,
  mNT_ITEM_TYPE_AXE,
  mNT_ITEM_TYPE_NET,
  mNT_ITEM_TYPE_ROD,
  mNT_ITEM_TYPE_SHOVEL,
  mNT_ITEM_TYPE_AXE2,
  mNT_ITEM_TYPE_NET2,
  mNT_ITEM_TYPE_ROD2,
  mNT_ITEM_TYPE_SHOVEL2,
  mNT_ITEM_TYPE_UMBRELLA,
  mNT_ITEM_TYPE_KAZA,
  mNT_ITEM_TYPE_UTIWA,
  mNT_ITEM_TYPE_PAPER,
  mNT_ITEM_TYPE_FLOWER_SEED,
  mNT_ITEM_TYPE_HUKUBUKURO,
  mNT_ITEM_TYPE_TAISOU,
  mNT_ITEM_TYPE_MD,
  mNT_ITEM_TYPE_TICKET,
  mNT_ITEM_TYPE_BONE,
  mNT_ITEM_TYPE_DIARY,
  mNT_ITEM_TYPE_FORK_ON,

  mNT_ITEM_TYPE_NUM
};

enum {
  mNT_TREE_SIZE_FULL,
  mNT_TREE_SIZE_S2,
  mNT_TREE_SIZE_S1,
  mNT_TREE_SIZE_S0,

  mNT_TREE_SIZE_NUM
};

typedef struct offset_table_s {
  int type;
  mCoBG_OffsetTable_c table;
} mNT_offset_table_c;

/* TODO: these should be calculated via definitions later */
#define NPC_NUM 236
#define NPC_ISLANDER_NUM 18
#define ALL_NPC_NUM NPC_NUM + 2 // include the two test villagers

#define TICKET_STACK_MAX 5
#define WISP_STACK_MAX 5
#define PAPER_STACK_MAX 4

#define FTR_NUM 1266
#define PAPER_NUM 256
#define MONEY_NUM 4
#define TOOL_NUM 92
#define FISH_NUM 40
#define CLOTH_NUM 255
#define ETC_NUM 49
#define CARPET_NUM 67
#define WALL_NUM 67
#define FRUIT_NUM 8
#define PLANT_NUM 11
#define MINIDISK_NUM 55
#define DIARY_NUM 16
#define TICKET_NUM 96
#define INSECT_ONLY_NUM 40
#define INSECT_NUM INSECT_ONLY_NUM + 5 // 5 spirits
#define HUKUBUKURO_NUM 2
#define KABU_NUM 4
#define SPIRIT_NUM 5

// #define WALL_MY_ORIG_START   (72)
// #define WALL_MY_ORIG_NUM     (8)
// #define WALL_MY_ORIG_END     ((WALL_MY_ORIG_START + WALL_MY_ORIG_NUM) - 1)
// #define WALL_IS_MY_ORIG(idx) ((idx) >= WALL_MY_ORIG_START && (idx) <= WALL_MY_ORIG_END)

#define PAPER_UNIQUE_NUM 64
#define PAINT_NUM 12
#define FLOWER_NUM 9
#define HANIWA_NUM 127
#define NOT_SECRET_MD_NUM 52
#define UMBRELLA_NUM 32

extern s16 move_obj_profile_table[];
extern s16 actor_profile_table[];
extern s16 props_profile_table[];
extern u8 npc_looks_table[];

extern int mNT_get_itemTableNo(mActor_name_t item);
extern mActor_name_t mNT_FishIdx2FishItemNo(int idx);
extern mActor_name_t bg_item_fg_sub(mActor_name_t item, s16 flag);
extern mActor_name_t bg_item_fg_sub_tree_grow(mActor_name_t item, int past_days, int check_plant);
extern mActor_name_t bg_item_fg_sub_dig2take_conv(mActor_name_t item);
extern mNT_offset_table_c* obj_hight_table_item0_nogrow(mActor_name_t item);
extern int FGTreeType_check(mActor_name_t tree);
extern int mNT_ItIsStump(mActor_name_t actor);
extern int mNT_ItIsStoneCoin10(mActor_name_t actor);
extern int mNT_ItIsReserveDummy(mActor_name_t actor);
extern int mNT_check_unknown(mActor_name_t item_no);

/* Retrieve the item actor's category */
#define ITEM_NAME_GET_TYPE(n) (((n) & 0xF000) >> 12)
#define ITEM_NAME_GET_CAT(n) (((n) & 0x0F00) >> 8)
#define ITEM_NAME_GET_INDEX(n) ((mActor_name_t)(n) & 0xFF)

#define NPC_HOUSE_ID_TO_NPC_ID(house) (house + 0x9000)
#define NPC_ID_TO_NPC_HOUSE_ID(npc) (npc - 0x9000)

#define TICKET_MONTH(n) (1 + (((n) >> 3) & 0xF))
#define TICKET_COUNT(n) (1 + ((n) & 7))
#define TICKET_TO_MONTH(month) (((month) - 1) << 3)
#define TICKET_TO_COUNT(cnt) ((cnt) & 7)
#define TICKET_GET_ITEM(month, cnt) (ITM_TICKET_START | (((month) - 1) << 3) | ((cnt) & 7))
#define WISP_COUNT(n) (ITEM_IS_WISP(n) ? (1 + (n) - ITM_SPIRIT0) : 0)

#define ITEM_IS_INSECT(n) ((n) >= ITM_INSECT_START && (n) < ITM_INSECT_END)
#define ITEM_IS_FISH(n) ((n) >= ITM_FISH_START && (n) <= ITM_FISH_END)
#define ITEM_IS_WISP(n) ((n) >= ITM_SPIRIT0 && (n) <= ITM_SPIRIT4)
#define ITEM_IS_PAPER(n) ((n) >= ITM_PAPER_START && (n) <= (ITM_PAPER_END - 1))
#define ITEM_IS_CLOTH(n) ((n) >= ITM_CLOTH_START && (n) < ITM_CLOTH_END)
#define ITEM_IS_NPC_CLOTH(n) ((n) == RSV_CLOTH || ITEM_IS_CLOTH(n))

#define ITEM_IS_RSVCLOTH(n) ((n) >= RSV_CLOTH && (n) <= RSV_CLOTH7)
#define ITEM_IS_RSVNWORG(n) ((n) >= RSV_NW_ORIGINAL0 && (n) <= RSV_NW_ORIGINAL7)
#define ITEM_IS_RSVCPORG(n) ((n) >= RSV_CPORIGINAL_FLD0_00 && (n) <= RSV_CPORIGINAL_FLD7_11)
#define ITEM_IS_RSVGBAORG(n) ((n) >= RSV_GBAORIGINAL0 && (n) <= RSV_GBAORIGINAL7)

#define ITEM_IS_MYMANNIQUIN(n) ((n) >= FTR_CLOTH_MANNIQUIN_MY_ORIGINAL0 && (n) <= FTR_CLOTH_MYMANNIQUIN_END)
#define ITEM_IS_MYUMBRELLA(n) ((n) >= FTR_MYUMBRELLA_START && (n) <= FTR_MYUMBRELLA_END)

#define PAPER2TYPE(n) ((n) % PAPER_UNIQUE_NUM)
#define PAPER2STACK(n) ((n) / PAPER_UNIQUE_NUM)
#define PAPEROFQUANT(n, q) (ITM_PAPER_START + (q - 1) * PAPER_UNIQUE_NUM + PAPER2TYPE(n))

#define ITEM_IS_FTR(n) \
  (ITEM_NAME_GET_TYPE(n) == NAME_TYPE_FTR0 || ITEM_NAME_GET_TYPE(n) == NAME_TYPE_FTR1)

#define ITEM_IS_ITEM1(n) (ITEM_NAME_GET_TYPE(n) == NAME_TYPE_ITEM1)
#define ITEM_IS_CARPET(n) ((n) >= ITM_CARPET_START && (n) < ITM_CARPET_END)
#define ITEM_IS_WALL(n) ((n) >= ITM_WALL_START && (n) < ITM_WALL_END)

#define GET_NAME_ITEM0_CATEGORY(f) (((f) & 0x0800) >> 11) /* enviornmental or static background objects */
#define GET_NAME_ITEM1_CATEGORY(f) (((f) & 0x0F00) >> 8)

#define IS_ITEM_FLOWER(item) ((item) >= FLOWER_LEAVES_PANSIES0 && (item) <= FLOWER_TULIP2)
#define IS_ITEM_ALIVE_TREE(item) \
  (((item) >= TREE_SAPLING && (item) <= TREE_30000BELLS) || \
   ((item) >= TREE_100BELLS_SAPLING && (item) <= TREE_PALM_FRUIT) || \
   ((item) >= CEDAR_TREE_SAPLING && (item) <= CEDAR_TREE) || \
   ((item) >= GOLD_TREE_SAPLING && (item) <= GOLD_TREE) \
  )

#define IS_ITEM_DEAD_SAPLING(item) \
  (((item) == DEAD_SAPLING) || \
   ((item) == DEAD_PALM_SAPLING) || \
   ((item) == DEAD_CEDAR_SAPLING) || \
   ((item) == DEAD_GOLD_SAPLING) \
  )

/*
#define IS_ITEM_TREE(item) \
  (((item) >= TREE_SAPLING && (item) <= TREE_30000BELLS) || \
   ((item) >= TREE_100BELLS_SAPLING && (item) <= TREE_PALM_FRUIT) || \
   ((item) >= CEDAR_TREE_SAPLING && (item) <= CEDAR_TREE) || \
   ((item) >= GOLD_TREE_SAPLING && (item) <= GOLD_TREE) || \
   ((item) == DEAD_SAPLING) || \
   ((item) == DEAD_PALM_SAPLING) || \
   ((item) == DEAD_CEDAR_SAPLING) || \
   ((item) == DEAD_GOLD_SAPLING) \
  )
*/

#define IS_ITEM_TREE(item) (IS_ITEM_ALIVE_TREE(item) || IS_ITEM_DEAD_SAPLING(item))

#define IS_ITEM_GROWN_TREE(item) \
  (((item) == TREE) || \
   ((item) == TREE_1000BELLS) || \
   ((item) == TREE_10000BELLS) || \
   ((item) == TREE_30000BELLS) || \
   ((item) == TREE_100BELLS) || \
   ((item) == CEDAR_TREE) || \
   ((item) == GOLD_TREE_SHOVEL || (item) == GOLD_TREE) || \
   ((item) == TREE_APPLE_NOFRUIT_0 || (item) == TREE_APPLE_NOFRUIT_1 || (item) == TREE_APPLE_NOFRUIT_2 || (item) == TREE_APPLE_FRUIT) || \
   ((item) == TREE_ORANGE_NOFRUIT_0 || (item) == TREE_ORANGE_NOFRUIT_1 || (item) == TREE_ORANGE_NOFRUIT_2 || (item) == TREE_ORANGE_FRUIT) || \
   ((item) == TREE_PEACH_NOFRUIT_0 || (item) == TREE_PEACH_NOFRUIT_1 || (item) == TREE_PEACH_NOFRUIT_2 || (item) == TREE_PEACH_FRUIT) || \
   ((item) == TREE_PEAR_NOFRUIT_0 || (item) == TREE_PEAR_NOFRUIT_1 || (item) == TREE_PEAR_NOFRUIT_2 || (item) == TREE_PEAR_FRUIT) || \
   ((item) == TREE_CHERRY_NOFRUIT_0 || (item) == TREE_CHERRY_NOFRUIT_1 || (item) == TREE_CHERRY_NOFRUIT_2 || (item) == TREE_CHERRY_FRUIT) || \
   ((item) == TREE_PALM_NOFRUIT_0 || (item) == TREE_PALM_NOFRUIT_1 || (item) == TREE_PALM_NOFRUIT_2 || (item) == TREE_PALM_FRUIT) || \
   ((item) == TREE_BEES) || \
   ((item) == TREE_FTR) || \
   ((item) == TREE_LIGHTS) || \
   ((item) == TREE_PRESENT) || \
   ((item) == TREE_BELLS) || \
   ((item) == CEDAR_TREE_BELLS) || \
   ((item) == CEDAR_TREE_FTR) || \
   ((item) == CEDAR_TREE_BEES) || \
   ((item) == CEDAR_TREE_LIGHTS) || \
   ((item) == GOLD_TREE_BELLS) || \
   ((item) == GOLD_TREE_FTR) || \
   ((item) == GOLD_TREE_BEES) \
  )

// @BUG - they check for money tree variants twice
#define IS_ITEM_COLLIDEABLE_TREE(item) \
  (((item) == TREE_S0) || \
   ((item) == TREE_APPLE_S0) || \
   ((item) == TREE_ORANGE_S0) || \
   ((item) == TREE_PEACH_S0) || \
   ((item) == TREE_PEAR_S0) || \
   ((item) == TREE_CHERRY_S0) || \
   ((item) == TREE_1000BELLS_S0) || \
   ((item) == TREE_10000BELLS_S0) || \
   ((item) == TREE_30000BELLS_S0) || \
   ((item) == TREE_1000BELLS_S0) || \
   ((item) == TREE_10000BELLS_S0) || \
   ((item) == TREE_30000BELLS_S0) || \
   ((item) == TREE_100BELLS_S0) || \
   ((item) == TREE_PALM_S0) || \
   ((item) == CEDAR_TREE_S0) || \
   ((item) == GOLD_TREE_S0) || \
   ((item) == TREE_S1) || \
   ((item) == TREE_APPLE_S1) || \
   ((item) == TREE_ORANGE_S1) || \
   ((item) == TREE_PEACH_S1) || \
   ((item) == TREE_PEAR_S1) || \
   ((item) == TREE_CHERRY_S1) || \
   ((item) == TREE_1000BELLS_S1) || \
   ((item) == TREE_10000BELLS_S1) || \
   ((item) == TREE_30000BELLS_S1) || \
   ((item) == TREE_1000BELLS_S1) || \
   ((item) == TREE_10000BELLS_S1) || \
   ((item) == TREE_30000BELLS_S1) || \
   ((item) == TREE_100BELLS_S1) || \
   ((item) == TREE_PALM_S1) || \
   ((item) == CEDAR_TREE_S1) || \
   ((item) == GOLD_TREE_S1) || \
   ((item) == TREE_S2) || \
   ((item) == TREE_APPLE_S2) || \
   ((item) == TREE_ORANGE_S2) || \
   ((item) == TREE_PEACH_S2) || \
   ((item) == TREE_PEAR_S2) || \
   ((item) == TREE_CHERRY_S2) || \
   ((item) == TREE_1000BELLS_S2) || \
   ((item) == TREE_10000BELLS_S2) || \
   ((item) == TREE_30000BELLS_S2) || \
   ((item) == TREE_1000BELLS_S2) || \
   ((item) == TREE_10000BELLS_S2) || \
   ((item) == TREE_30000BELLS_S2) || \
   ((item) == TREE_100BELLS_S2) || \
   ((item) == TREE_PALM_S2) || \
   ((item) == CEDAR_TREE_S2) || \
   ((item) == GOLD_TREE_S2) || \
   ((item) == TREE) || \
   ((item) == TREE_APPLE_FRUIT) || \
   ((item) == TREE_ORANGE_FRUIT) || \
   ((item) == TREE_PEACH_FRUIT) || \
   ((item) == TREE_PEAR_FRUIT) || \
   ((item) == TREE_CHERRY_FRUIT) || \
   ((item) == TREE_1000BELLS) || \
   ((item) == TREE_10000BELLS) || \
   ((item) == TREE_30000BELLS) || \
   ((item) == TREE_100BELLS) || \
   ((item) == TREE_PALM_FRUIT) || \
   ((item) == CEDAR_TREE) || \
   ((item) == GOLD_TREE) || \
   ((item) == GOLD_TREE_SHOVEL) || \
   ((item) == TREE_APPLE_NOFRUIT_0) || \
   ((item) == TREE_ORANGE_NOFRUIT_0) || \
   ((item) == TREE_PEACH_NOFRUIT_0) || \
   ((item) == TREE_PEAR_NOFRUIT_0) || \
   ((item) == TREE_CHERRY_NOFRUIT_0) || \
   ((item) == TREE_PALM_NOFRUIT_0) || \
   ((item) == TREE_APPLE_NOFRUIT_1) || \
   ((item) == TREE_ORANGE_NOFRUIT_1) || \
   ((item) == TREE_PEACH_NOFRUIT_1) || \
   ((item) == TREE_PEAR_NOFRUIT_1) || \
   ((item) == TREE_CHERRY_NOFRUIT_1) || \
   ((item) == TREE_PALM_NOFRUIT_1) || \
   ((item) == TREE_APPLE_NOFRUIT_2) || \
   ((item) == TREE_ORANGE_NOFRUIT_2) || \
   ((item) == TREE_PEACH_NOFRUIT_2) || \
   ((item) == TREE_PEAR_NOFRUIT_2) || \
   ((item) == TREE_CHERRY_NOFRUIT_2) || \
   ((item) == TREE_PALM_NOFRUIT_2) || \
   ((item) == TREE_BEES) || \
   ((item) == TREE_FTR) || \
   ((item) == TREE_LIGHTS) || \
   ((item) == TREE_PRESENT) || \
   ((item) == TREE_BELLS) || \
   ((item) == CEDAR_TREE_BELLS) || \
   ((item) == CEDAR_TREE_FTR) || \
   ((item) == CEDAR_TREE_BEES) || \
   ((item) == CEDAR_TREE_LIGHTS) || \
   ((item) == GOLD_TREE_BELLS) || \
   ((item) == GOLD_TREE_FTR) || \
   ((item) == GOLD_TREE_BEES) \
  )

#define IS_ITEM_XMAS_TREE(item) ((item) == TREE_LIGHTS || (item) == CEDAR_TREE_LIGHTS)
#define IS_ITEM_SMALL_TREE(item) ( \
  ((item) == TREE_S0) || \
  ((item) == TREE_APPLE_S0) || \
  ((item) == TREE_ORANGE_S0) || \
  ((item) == TREE_PEACH_S0) || \
  ((item) == TREE_PEAR_S0) || \
  ((item) == TREE_CHERRY_S0) || \
  ((item) == TREE_1000BELLS_S0) || \
  ((item) == TREE_10000BELLS_S0) || \
  ((item) == TREE_30000BELLS_S0) || \
  ((item) == TREE_1000BELLS_S0) || \
  ((item) == TREE_10000BELLS_S0) || \
  ((item) == TREE_30000BELLS_S0) || \
  ((item) == TREE_100BELLS_S0) || \
  ((item) == TREE_PALM_S0) || \
  ((item) == CEDAR_TREE_S0) || \
  ((item) == GOLD_TREE_S0) \
)
#define IS_ITEM_MED_TREE(item) ( \
  ((item) == TREE_S1) || \
  ((item) == TREE_APPLE_S1) || \
  ((item) == TREE_ORANGE_S1) || \
  ((item) == TREE_PEACH_S1) || \
  ((item) == TREE_PEAR_S1) || \
  ((item) == TREE_CHERRY_S1) || \
  ((item) == TREE_1000BELLS_S1) || \
  ((item) == TREE_10000BELLS_S1) || \
  ((item) == TREE_30000BELLS_S1) || \
  ((item) == TREE_1000BELLS_S1) || \
  ((item) == TREE_10000BELLS_S1) || \
  ((item) == TREE_30000BELLS_S1) || \
  ((item) == TREE_100BELLS_S1) || \
  ((item) == TREE_PALM_S1) || \
  ((item) == CEDAR_TREE_S1) || \
  ((item) == GOLD_TREE_S1) \
)
#define IS_ITEM_LARGE_TREE(item) ( \
  ((item) == TREE_S2) || \
  ((item) == TREE_APPLE_S2) || \
  ((item) == TREE_ORANGE_S2) || \
  ((item) == TREE_PEACH_S2) || \
  ((item) == TREE_PEAR_S2) || \
  ((item) == TREE_CHERRY_S2) || \
  ((item) == TREE_1000BELLS_S2) || \
  ((item) == TREE_10000BELLS_S2) || \
  ((item) == TREE_30000BELLS_S2) || \
  ((item) == TREE_1000BELLS_S2) || \
  ((item) == TREE_10000BELLS_S2) || \
  ((item) == TREE_30000BELLS_S2) || \
  ((item) == TREE_100BELLS_S2) || \
  ((item) == TREE_PALM_S2) || \
  ((item) == CEDAR_TREE_S2) || \
  ((item) == GOLD_TREE_S2) \
)

#define IS_ITEM_FULL_TREE(item) \
  (((item) == TREE) || \
   ((item) == TREE_APPLE_FRUIT) || \
   ((item) == TREE_ORANGE_FRUIT) || \
   ((item) == TREE_PEACH_FRUIT) || \
   ((item) == TREE_PEAR_FRUIT) || \
   ((item) == TREE_CHERRY_FRUIT) || \
   ((item) == TREE_1000BELLS) || \
   ((item) == TREE_10000BELLS) || \
   ((item) == TREE_30000BELLS) || \
   ((item) == TREE_100BELLS) || \
   ((item) == TREE_PALM_FRUIT) || \
   ((item) == CEDAR_TREE) || \
   ((item) == GOLD_TREE) || \
   ((item) == GOLD_TREE_SHOVEL) || \
   ((item) == TREE_APPLE_NOFRUIT_0) || \
   ((item) == TREE_ORANGE_NOFRUIT_0 ) || \
   ((item) == TREE_PEACH_NOFRUIT_0) || \
   ((item) == TREE_PEAR_NOFRUIT_0) || \
   ((item) == TREE_CHERRY_NOFRUIT_0) || \
   ((item) == TREE_PALM_NOFRUIT_0) || \
   ((item) == TREE_APPLE_NOFRUIT_1) || \
   ((item) == TREE_ORANGE_NOFRUIT_1 ) || \
   ((item) == TREE_PEACH_NOFRUIT_1) || \
   ((item) == TREE_PEAR_NOFRUIT_1) || \
   ((item) == TREE_CHERRY_NOFRUIT_1) || \
   ((item) == TREE_PALM_NOFRUIT_1) || \
   ((item) == TREE_APPLE_NOFRUIT_2) || \
   ((item) == TREE_ORANGE_NOFRUIT_2 ) || \
   ((item) == TREE_PEACH_NOFRUIT_2) || \
   ((item) == TREE_PEAR_NOFRUIT_2) || \
   ((item) == TREE_CHERRY_NOFRUIT_2) || \
   ((item) == TREE_PALM_NOFRUIT_2) || \
   ((item) == TREE_BEES) || \
   ((item) == TREE_FTR) || \
   ((item) == TREE_LIGHTS) || \
   ((item) == TREE_PRESENT) || \
   ((item) == TREE_BELLS) || \
   ((item) == CEDAR_TREE_BELLS) || \
   ((item) == CEDAR_TREE_FTR) || \
   ((item) == CEDAR_TREE_BEES) || \
   ((item) == CEDAR_TREE_LIGHTS) || \
   ((item) == GOLD_TREE_BELLS) || \
   ((item) == GOLD_TREE_FTR) || \
   ((item) == GOLD_TREE_BEES) \
  )

#define IS_ITEM_PALM_TREE(item) ((item) >= TREE_PALM_SAPLING && (item) < TREE_PALM_FRUIT)
#define IS_ITEM_ANY_PALM_TREE(item) ((item) >= TREE_PALM_SAPLING && (item) <= TREE_PALM_FRUIT)

#define IS_ITEM_TREE_STUMP(item) ((item >= TREE_STUMP001 && (item) <= TREE_STUMP004) || \
    (item) >= TREE_PALM_STUMP001 && (item) <= TREE_PALM_STUMP004 || \
    (item) >= CEDAR_TREE_STUMP001 && (item) <= CEDAR_TREE_STUMP004 || \
    (item) >= GOLD_TREE_STUMP001 && (item) <= GOLD_TREE_STUMP004 \
)

#define IS_ITEM_HITTABLE_TREE(item) (IS_ITEM_SMALL_TREE(item) || IS_ITEM_MED_TREE(item) || IS_ITEM_LARGE_TREE(item) || IS_ITEM_FULL_TREE(item))
#define IS_ITEM_SHAKEABLE_TREE(item) (IS_ITEM_MED_TREE(item) || IS_ITEM_LARGE_TREE(item) || IS_ITEM_FULL_TREE(item))

#define IS_ITEM_BEE_TREE(item) ((item) == TREE_BEES || (item) == CEDAR_TREE_BEES || (item) == GOLD_TREE_BEES)

#define IS_ITEM_STONE(item) ((item) >= ROCK_A && (item) <= ROCK_E)
#define IS_ITEM_STONE_TC(item) (((item) >= MONEY_ROCK_A && (item) <= MONEY_ROCK_E) || (item) == MONEY_FLOWER_SEED) /* TC is ten coin */
#define IS_ITEM_ROCK(item) (((item) >= ROCK_A && (item) <= ROCK_E) || ((item) >= MONEY_ROCK_A && (item) <= MONEY_ROCK_E) || (item) == MONEY_FLOWER_SEED)

#define IS_ITEM_GRASS(item) ((item) >= GRASS_A && (item) <= GRASS_C) /* aka IS_ITEM_WEED */

#define IS_ITEM_HANIWA(item) ((item) >= HANIWA_START && (item) <= HANIWA_END)

#define IS_ITEM_DIARY(item) ((item) >= ITM_DIARY_START && (item) <= (ITM_DIARY_END-1))

#define IS_ITEM_AXE(item) ((item) == ITM_AXE || ((item) >= ITM_AXE_USE_1 && (item) <= ITM_AXE_USE_7))
#define IS_ITEM_GOLDEN_TOOL(item) ((item) >= ITM_GOLDEN_NET && (item) <= ITM_GOLDEN_ROD)

#define ITEM_IS_HOLE(item) ((item) >= HOLE_START && (item) <= HOLE_END)
#define ITEM_IS_BURIED_PITFALL_HOLE(item) ((item) >= BURIED_PITFALL_HOLE_START && (item) <= BURIED_PITFALL_HOLE_END)
#define ITEM_IS_BURIED_PITFALL_HOLE_RSV(item) ((item) >= BURIED_PITFALL_HOLE_RSV_START && (item) <= BURIED_PITFALL_HOLE_RSV_END)

#define ITEM_IS_PLAYER_HOUSE(item) ((item) >= HOUSE0 && (item) < (HOUSE3 + 1))
#define ITEM_IS_NPC_HOUSE(item) ((item) >= NPC_HOUSE_START && (item) < NPC_HOUSE_END)
#define ITEM_IS_DUMMY_NPC_HOUSE(item) ((item) >= DUMMY_NPC_HOUSE_START && (item) < (DUMMY_NPC_HOUSE_END + 1))
#define ITEM_IS_ISLAND_NPC_HOUSE(item) ((item) >= COTTAGE_NPC && (item) < COTTAGE_NPC_END)

#define ITEM_IS_SIGNBOARD(item) ((item) >= SIGNBOARD_START && (item) <= SIGNBOARD_END)

#define ITEM_IS_FLOWER_BAG(item) ((item) >= ITM_WHITE_PANSY_BAG && (item) <= ITM_YELLOW_TULIP_BAG)
#define ITEM_IS_EXERCISE_CARD(item) ((item) >= ITM_EXCERCISE_CARD00 && (item) <= ITM_EXCERCISE_CARD12)
#define ITEM_IS_BALLOON(item) ((item) >= ITM_BALLOON_START && (item) <= ITM_BUNNY_O_BALLOON)
#define ITEM_IS_UMBRELLA(item) ((item) >= ITM_UMBRELLA_START && (item) <= ITM_UMBRELLA_END)
#define ITEM_IS_UMBRELLA2(item) ((item) >= ITM_UMBRELLA_START && (item) <= ITM_MY_ORG_UMBRELLA7)
#define ITEM_IS_MYUMBRELLA_TOOL(item) ((item) >= ITM_MY_ORG_UMBRELLA0 && (item) <= ITM_MY_ORG_UMBRELLA7)
#define ITEM_IS_SCOOP(item) ((item) >= ITM_SHOVEL && (item) <= ITM_SHOVEL)
#define ITEM_IS_GOLD_SCOOP(item) ((item) >= ITM_GOLDEN_SHOVEL && (item) <= ITM_GOLDEN_SHOVEL)
#define ITEM_IS_PAINT(item) ((item) >= ITM_RED_PAINT && (item) <= ITM_BROWN_PAINT)
#define ITEM_IS_TOOL(item) ((item) >= ITM_TOOL_START && (item) < ITM_TOOL_END)

#define ITEM_IS_DUMMY_MAILBOX(item) ((item) >= DUMMY_MAILBOX0 && (item) <= DUMMY_MAILBOX3)
#define ITEM_IS_SIGN(item) ((item) == DUMMY_RESERVE || ITEM_IS_SIGNBOARD(item))

#define BG_CATEGORY 0
#define ENV_CATEGORY 8

#define EMPTY_NO 0x0000
#define TREE_STUMP001 (EMPTY_NO + 1)
#define TREE_STUMP002 (EMPTY_NO + 2)
#define TREE_STUMP003 (EMPTY_NO + 3)
#define TREE_STUMP004 (EMPTY_NO + 4)
#define FENCE0 (EMPTY_NO + 5)
#define FENCE1 (EMPTY_NO + 6)
#define MESSAGE_BOARD0 0x0007
#define GRASS_A 0x0008
#define GRASS_B (GRASS_A + 1)
#define GRASS_C (GRASS_B + 1)
#define MESSAGE_BOARD1 0x000B
#define MAP_BOARD0 0x000C
#define MAP_BOARD1 0x000D
#define MUSIC_BOARD0 0x000E
#define MUSIC_BOARD1 0x000F
#define WOOD_FENCE 0x0010
#define HOLE_START 0x0011
#define HOLE00 (HOLE_START + 0)
#define HOLE01 (HOLE_START + 1)
#define HOLE02 (HOLE_START + 2)
#define HOLE03 (HOLE_START + 3)
#define HOLE04 (HOLE_START + 4)
#define HOLE05 (HOLE_START + 5)
#define HOLE06 (HOLE_START + 6)
#define HOLE07 (HOLE_START + 7)
#define HOLE08 (HOLE_START + 8)
#define HOLE09 (HOLE_START + 9)
#define HOLE10 (HOLE_START + 10)
#define HOLE11 (HOLE_START + 11)
#define HOLE12 (HOLE_START + 12)
#define HOLE13 (HOLE_START + 13)
#define HOLE14 (HOLE_START + 14)
#define HOLE15 (HOLE_START + 15)
#define HOLE16 (HOLE_START + 16)
#define HOLE17 (HOLE_START + 17)
#define HOLE18 (HOLE_START + 18)
#define HOLE19 (HOLE_START + 19)
#define HOLE20 (HOLE_START + 20)
#define HOLE21 (HOLE_START + 21)
#define HOLE22 (HOLE_START + 22)
#define HOLE23 (HOLE_START + 23)
#define HOLE24 (HOLE_START + 24)
#define HOLE_END HOLE24
#define BURIED_PITFALL_HOLE_START 0x002A
#define BURIED_PITFALL_HOLE00 (BURIED_PITFALL_HOLE_START + 0)
#define BURIED_PITFALL_HOLE01 (BURIED_PITFALL_HOLE_START + 1)
#define BURIED_PITFALL_HOLE02 (BURIED_PITFALL_HOLE_START + 2)
#define BURIED_PITFALL_HOLE03 (BURIED_PITFALL_HOLE_START + 3)
#define BURIED_PITFALL_HOLE04 (BURIED_PITFALL_HOLE_START + 4)
#define BURIED_PITFALL_HOLE05 (BURIED_PITFALL_HOLE_START + 5)
#define BURIED_PITFALL_HOLE06 (BURIED_PITFALL_HOLE_START + 6)
#define BURIED_PITFALL_HOLE07 (BURIED_PITFALL_HOLE_START + 7)
#define BURIED_PITFALL_HOLE08 (BURIED_PITFALL_HOLE_START + 8)
#define BURIED_PITFALL_HOLE09 (BURIED_PITFALL_HOLE_START + 9)
#define BURIED_PITFALL_HOLE10 (BURIED_PITFALL_HOLE_START + 10)
#define BURIED_PITFALL_HOLE11 (BURIED_PITFALL_HOLE_START + 11)
#define BURIED_PITFALL_HOLE12 (BURIED_PITFALL_HOLE_START + 12)
#define BURIED_PITFALL_HOLE13 (BURIED_PITFALL_HOLE_START + 13)
#define BURIED_PITFALL_HOLE14 (BURIED_PITFALL_HOLE_START + 14)
#define BURIED_PITFALL_HOLE15 (BURIED_PITFALL_HOLE_START + 15)
#define BURIED_PITFALL_HOLE16 (BURIED_PITFALL_HOLE_START + 16)
#define BURIED_PITFALL_HOLE17 (BURIED_PITFALL_HOLE_START + 17)
#define BURIED_PITFALL_HOLE18 (BURIED_PITFALL_HOLE_START + 18)
#define BURIED_PITFALL_HOLE19 (BURIED_PITFALL_HOLE_START + 19)
#define BURIED_PITFALL_HOLE20 (BURIED_PITFALL_HOLE_START + 20)
#define BURIED_PITFALL_HOLE21 (BURIED_PITFALL_HOLE_START + 21)
#define BURIED_PITFALL_HOLE22 (BURIED_PITFALL_HOLE_START + 22)
#define BURIED_PITFALL_HOLE23 (BURIED_PITFALL_HOLE_START + 23)
#define BURIED_PITFALL_HOLE24 (BURIED_PITFALL_HOLE_START + 24)
#define BURIED_PITFALL_HOLE_END BURIED_PITFALL_HOLE24
#define BURIED_PITFALL_HOLE_RSV_START 0x0043
#define BURIED_PITFALL_HOLE_RSV00 (BURIED_PITFALL_HOLE_RSV_START + 0)
#define BURIED_PITFALL_HOLE_RSV01 (BURIED_PITFALL_HOLE_RSV_START + 1)
#define BURIED_PITFALL_HOLE_RSV02 (BURIED_PITFALL_HOLE_RSV_START + 2)
#define BURIED_PITFALL_HOLE_RSV03 (BURIED_PITFALL_HOLE_RSV_START + 3)
#define BURIED_PITFALL_HOLE_RSV04 (BURIED_PITFALL_HOLE_RSV_START + 4)
#define BURIED_PITFALL_HOLE_RSV05 (BURIED_PITFALL_HOLE_RSV_START + 5)
#define BURIED_PITFALL_HOLE_RSV06 (BURIED_PITFALL_HOLE_RSV_START + 6)
#define BURIED_PITFALL_HOLE_RSV07 (BURIED_PITFALL_HOLE_RSV_START + 7)
#define BURIED_PITFALL_HOLE_RSV08 (BURIED_PITFALL_HOLE_RSV_START + 8)
#define BURIED_PITFALL_HOLE_RSV09 (BURIED_PITFALL_HOLE_RSV_START + 9)
#define BURIED_PITFALL_HOLE_RSV10 (BURIED_PITFALL_HOLE_RSV_START + 10)
#define BURIED_PITFALL_HOLE_RSV11 (BURIED_PITFALL_HOLE_RSV_START + 11)
#define BURIED_PITFALL_HOLE_RSV12 (BURIED_PITFALL_HOLE_RSV_START + 12)
#define BURIED_PITFALL_HOLE_RSV13 (BURIED_PITFALL_HOLE_RSV_START + 13)
#define BURIED_PITFALL_HOLE_RSV14 (BURIED_PITFALL_HOLE_RSV_START + 14)
#define BURIED_PITFALL_HOLE_RSV15 (BURIED_PITFALL_HOLE_RSV_START + 15)
#define BURIED_PITFALL_HOLE_RSV16 (BURIED_PITFALL_HOLE_RSV_START + 16)
#define BURIED_PITFALL_HOLE_RSV17 (BURIED_PITFALL_HOLE_RSV_START + 17)
#define BURIED_PITFALL_HOLE_RSV18 (BURIED_PITFALL_HOLE_RSV_START + 18)
#define BURIED_PITFALL_HOLE_RSV19 (BURIED_PITFALL_HOLE_RSV_START + 19)
#define BURIED_PITFALL_HOLE_RSV20 (BURIED_PITFALL_HOLE_RSV_START + 20)
#define BURIED_PITFALL_HOLE_RSV21 (BURIED_PITFALL_HOLE_RSV_START + 21)
#define BURIED_PITFALL_HOLE_RSV22 (BURIED_PITFALL_HOLE_RSV_START + 22)
#define BURIED_PITFALL_HOLE_RSV23 (BURIED_PITFALL_HOLE_RSV_START + 23)
#define BURIED_PITFALL_HOLE_RSV24 (BURIED_PITFALL_HOLE_RSV_START + 24)
#define BURIED_PITFALL_HOLE_RSV_END BURIED_PITFALL_HOLE_RSV24
#define SHINE_SPOT 0x005C
#define HOLE_SHINE 0x005D
#define TREE_BEES 0x005E
#define TREE_FTR (TREE_BEES + 1)
#define TREE_LIGHTS (TREE_FTR + 1)
#define TREE_PRESENT (TREE_LIGHTS + 1)

#define HONEYCOMB 0x0062
#define ROCK_A 0x0063
#define ROCK_B (ROCK_A + 1)
#define ROCK_C (ROCK_B + 1)
#define ROCK_D (ROCK_C + 1)
#define ROCK_E (ROCK_D + 1)

#define FLOWER_SEED 0x0068
#define TREE_BELLS 0x0069

#define MONEY_ROCK_A 0x006A
#define MONEY_ROCK_B (MONEY_ROCK_A + 1)
#define MONEY_ROCK_C (MONEY_ROCK_B + 1)
#define MONEY_ROCK_D (MONEY_ROCK_C + 1)
#define MONEY_ROCK_E (MONEY_ROCK_D + 1)

#define MONEY_FLOWER_SEED 0x006F

#define TREE_PALM_STUMP001 (EMPTY_NO + 112)
#define TREE_PALM_STUMP002 (EMPTY_NO + 113)
#define TREE_PALM_STUMP003 (EMPTY_NO + 114)
#define TREE_PALM_STUMP004 (EMPTY_NO + 115)
#define CEDAR_TREE_STUMP001 (EMPTY_NO + 116)
#define CEDAR_TREE_STUMP002 (EMPTY_NO + 117)
#define CEDAR_TREE_STUMP003 (EMPTY_NO + 118)
#define CEDAR_TREE_STUMP004 (EMPTY_NO + 119)

#define CEDAR_TREE_BELLS 0x0078
#define CEDAR_TREE_FTR (CEDAR_TREE_BELLS + 1)
#define CEDAR_TREE_BEES (CEDAR_TREE_FTR + 1)

#define GOLD_TREE_STUMP001 (EMPTY_NO + 123)
#define GOLD_TREE_STUMP002 (EMPTY_NO + 124)
#define GOLD_TREE_STUMP003 (EMPTY_NO + 125)
#define GOLD_TREE_STUMP004 (EMPTY_NO + 126)

#define GOLD_TREE_BELLS 0x007F
#define GOLD_TREE_FTR (GOLD_TREE_BELLS + 1)
#define GOLD_TREE_BEES (GOLD_TREE_FTR + 1)
#define CEDAR_TREE_LIGHTS (GOLD_TREE_BEES + 1)

/* begin environmental/nature objects */
#define ENV_START 0x0800
/* tree */
#define TREE_SAPLING (ENV_START + 0)
#define TREE_S0 (ENV_START + 1)
#define TREE_S1 (ENV_START + 2)
#define TREE_S2 (ENV_START + 3)
#define TREE (ENV_START + 4) /* fully grown */
/* apple tree */
#define TREE_APPLE_SAPLING (ENV_START + 5)
#define TREE_APPLE_S0 (ENV_START + 6)
#define TREE_APPLE_S1 (ENV_START + 7)
#define TREE_APPLE_S2 (ENV_START + 8)
#define TREE_APPLE_NOFRUIT_0 (ENV_START + 9) /* fully grown, no fruit */
#define TREE_APPLE_NOFRUIT_1 (ENV_START + 10)
#define TREE_APPLE_NOFRUIT_2 (ENV_START + 11)
#define TREE_APPLE_FRUIT (ENV_START + 12)
/* orange tree */
#define TREE_ORANGE_SAPLING (ENV_START + 13)
#define TREE_ORANGE_S0 (ENV_START + 14)
#define TREE_ORANGE_S1 (ENV_START + 15)
#define TREE_ORANGE_S2 (ENV_START + 16) /* fully grown, no fruit */
#define TREE_ORANGE_NOFRUIT_0 (ENV_START + 17)
#define TREE_ORANGE_NOFRUIT_1 (ENV_START + 18)
#define TREE_ORANGE_NOFRUIT_2 (ENV_START + 19)
#define TREE_ORANGE_FRUIT (ENV_START + 20)
/* peach tree */
#define TREE_PEACH_SAPLING (ENV_START + 21)
#define TREE_PEACH_S0 (ENV_START + 22)
#define TREE_PEACH_S1 (ENV_START + 23)
#define TREE_PEACH_S2 (ENV_START + 24)
#define TREE_PEACH_NOFRUIT_0 (ENV_START + 25) /* fully grown, no fruit */
#define TREE_PEACH_NOFRUIT_1 (ENV_START + 26)
#define TREE_PEACH_NOFRUIT_2 (ENV_START + 27)
#define TREE_PEACH_FRUIT (ENV_START + 28)
/* pear tree */
#define TREE_PEAR_SAPLING (ENV_START + 29)
#define TREE_PEAR_S0 (ENV_START + 30)
#define TREE_PEAR_S1 (ENV_START + 31)
#define TREE_PEAR_S2 (ENV_START + 32)
#define TREE_PEAR_NOFRUIT_0 (ENV_START + 33) /* fully grown, no fruit */
#define TREE_PEAR_NOFRUIT_1 (ENV_START + 34)
#define TREE_PEAR_NOFRUIT_2 (ENV_START + 35)
#define TREE_PEAR_FRUIT (ENV_START + 36)
/* cherry tree */
#define TREE_CHERRY_SAPLING (ENV_START + 37)
#define TREE_CHERRY_S0 (ENV_START + 38)
#define TREE_CHERRY_S1 (ENV_START + 39)
#define TREE_CHERRY_S2 (ENV_START + 40)
#define TREE_CHERRY_NOFRUIT_0 (ENV_START + 41) /* fully grown, no fruit */
#define TREE_CHERRY_NOFRUIT_1 (ENV_START + 42)
#define TREE_CHERRY_NOFRUIT_2 (ENV_START + 43)
#define TREE_CHERRY_FRUIT (ENV_START + 44)
/* money tree (1,000 Bells) */
#define TREE_1000BELLS_SAPLING (ENV_START + 45)
#define TREE_1000BELLS_S0 (ENV_START + 46)
#define TREE_1000BELLS_S1 (ENV_START + 47)
#define TREE_1000BELLS_S2 (ENV_START + 48)
#define TREE_1000BELLS (ENV_START + 49) /* fully grown w/ bells */
/* money tree (10,000 Bells) */
#define TREE_10000BELLS_SAPLING (ENV_START + 50)
#define TREE_10000BELLS_S0 (ENV_START + 51)
#define TREE_10000BELLS_S1 (ENV_START + 52)
#define TREE_10000BELLS_S2 (ENV_START + 53)
#define TREE_10000BELLS (ENV_START + 54) /* fully grown w/ bells */
/* money tree (30,000 Bells) */
#define TREE_30000BELLS_SAPLING (ENV_START + 55)
#define TREE_30000BELLS_S0 (ENV_START + 56)
#define TREE_30000BELLS_S1 (ENV_START + 57)
#define TREE_30000BELLS_S2 (ENV_START + 58)
#define TREE_30000BELLS (ENV_START + 59) /* fully grown w/ bells */
/* flower leaves (unused growth stage) */
#define FLOWER_LEAVES_PANSIES0 (ENV_START + 60) /* white */
#define FLOWER_LEAVES_PANSIES1 (ENV_START + 61) /* purple */
#define FLOWER_LEAVES_PANSIES2 (ENV_START + 62) /* yellow */
#define FLOWER_LEAVES_COSMOS0 (ENV_START + 63) /* yellow */
#define FLOWER_LEAVES_COSMOS1 (ENV_START + 64) /* purple */
#define FLOWER_LEAVES_COSMOS2 (ENV_START + 65) /* blue */
#define FLOWER_LEAVES_TULIP0 (ENV_START + 66) /* red */
#define FLOWER_LEAVES_TULIP1 (ENV_START + 67) /* white */
#define FLOWER_LEAVES_TULIP2 (ENV_START + 68) /* yellow */
/* flowers */
#define FLOWER_PANSIES0 (ENV_START + 69) /* white */
#define FLOWER_PANSIES1 (ENV_START + 70) /* purple */
#define FLOWER_PANSIES2 (ENV_START + 71) /* yellow */
#define FLOWER_COSMOS0 (ENV_START + 72) /* yellow */
#define FLOWER_COSMOS1 (ENV_START + 73) /* purple */
#define FLOWER_COSMOS2 (ENV_START + 74) /* blue */
#define FLOWER_TULIP0 (ENV_START + 75) /* red */
#define FLOWER_TULIP1 (ENV_START + 76) /* white */
#define FLOWER_TULIP2 (ENV_START + 77) /* yellow */
/* dead sapling */
#define DEAD_SAPLING (ENV_START + 78)
/* money tree (100 Bells) */
#define TREE_100BELLS_SAPLING (ENV_START + 79)
#define TREE_100BELLS_S0 (ENV_START + 80)
#define TREE_100BELLS_S1 (ENV_START + 81)
#define TREE_100BELLS_S2 (ENV_START + 82)
#define TREE_100BELLS (ENV_START + 83) /* fully grown w/ bells */
/* palm tree */
#define TREE_PALM_SAPLING (ENV_START + 84)
#define TREE_PALM_S0 (ENV_START + 85)
#define TREE_PALM_S1 (ENV_START + 86)
#define TREE_PALM_S2 (ENV_START + 87)
#define TREE_PALM_NOFRUIT_0 (ENV_START + 88) /* fully grown, no fruit */
#define TREE_PALM_NOFRUIT_1 (ENV_START + 89)
#define TREE_PALM_NOFRUIT_2 (ENV_START + 90)
#define TREE_PALM_FRUIT (ENV_START + 91)
#define DEAD_PALM_SAPLING (ENV_START + 92)
/* cedar tree */
#define CEDAR_TREE_SAPLING (ENV_START + 93)
#define CEDAR_TREE_S0 (ENV_START + 94)
#define CEDAR_TREE_S1 (ENV_START + 95)
#define CEDAR_TREE_S2 (ENV_START + 96)
#define CEDAR_TREE (ENV_START + 97) /* fully grown */
#define DEAD_CEDAR_SAPLING (ENV_START + 98)
/* gold tree */
#define GOLD_TREE_SAPLING (ENV_START + 99)
#define GOLD_TREE_S0 (ENV_START + 100)
#define GOLD_TREE_S1 (ENV_START + 101)
#define GOLD_TREE_S2 (ENV_START + 102)
#define GOLD_TREE_SHOVEL (ENV_START + 103) /* fully grown w/ golden shovel */
#define GOLD_TREE (ENV_START + 104) /* fully grown */
#define DEAD_GOLD_SAPLING (ENV_START + 105)
/* end of environmental objects */

#define SIGNBOARD_START 0x0900
#define SIGNBOARD0_PLR0 (SIGNBOARD_START + 0)
#define SIGNBOARD1_PLR0 (SIGNBOARD_START + 1)
#define SIGNBOARD2_PLR0 (SIGNBOARD_START + 2)
#define SIGNBOARD3_PLR0 (SIGNBOARD_START + 3)
#define SIGNBOARD4_PLR0 (SIGNBOARD_START + 4)
#define SIGNBOARD5_PLR0 (SIGNBOARD_START + 5)
#define SIGNBOARD6_PLR0 (SIGNBOARD_START + 6)
#define SIGNBOARD7_PLR0 (SIGNBOARD_START + 7)
#define SIGNBOARD0_PLR1 (SIGNBOARD_START + 8)
#define SIGNBOARD1_PLR1 (SIGNBOARD_START + 9)
#define SIGNBOARD2_PLR1 (SIGNBOARD_START + 10)
#define SIGNBOARD3_PLR1 (SIGNBOARD_START + 11)
#define SIGNBOARD4_PLR1 (SIGNBOARD_START + 12)
#define SIGNBOARD5_PLR1 (SIGNBOARD_START + 13)
#define SIGNBOARD6_PLR1 (SIGNBOARD_START + 14)
#define SIGNBOARD7_PLR1 (SIGNBOARD_START + 15)
#define SIGNBOARD0_PLR2 (SIGNBOARD_START + 16)
#define SIGNBOARD1_PLR2 (SIGNBOARD_START + 17)
#define SIGNBOARD2_PLR2 (SIGNBOARD_START + 18)
#define SIGNBOARD3_PLR2 (SIGNBOARD_START + 19)
#define SIGNBOARD4_PLR2 (SIGNBOARD_START + 20)
#define SIGNBOARD5_PLR2 (SIGNBOARD_START + 21)
#define SIGNBOARD6_PLR2 (SIGNBOARD_START + 22)
#define SIGNBOARD7_PLR2 (SIGNBOARD_START + 23)
#define SIGNBOARD0_PLR3 (SIGNBOARD_START + 24)
#define SIGNBOARD1_PLR3 (SIGNBOARD_START + 25)
#define SIGNBOARD2_PLR3 (SIGNBOARD_START + 26)
#define SIGNBOARD3_PLR3 (SIGNBOARD_START + 27)
#define SIGNBOARD4_PLR3 (SIGNBOARD_START + 28)
#define SIGNBOARD5_PLR3 (SIGNBOARD_START + 29)
#define SIGNBOARD6_PLR3 (SIGNBOARD_START + 30)
#define SIGNBOARD7_PLR3 (SIGNBOARD_START + 31)
#define SIGNBOARD (SIGNBOARD_START + 32)
#define SIGNBOARD_END (SIGNBOARD)

#define FTR0_START 0x1000
#define FTR_CLASSIC_WARDROBE 0x1004
#define FTR_FAN 0x1088
#define FTR_PAPA_BEAR 0x10E8
#define FTR_PAPA_BEAR_EAST 0x10E9
#define FTR_PAPA_BEAR_NORTH 0x10EA
#define FTR_PAPA_BEAR_WEST 0x10EB

#define FTR_BIRTHDAY_CAKE 0x11FC
#define FTR_BIRTHDAY_CAKE_EAST 0x11FD
#define FTR_BIRTHDAY_CAKE_NORTH 0x11FE
#define FTR_BIRTHDAY_CAKE_WEST 0x11FF

#define FTR_PAINTING0 0x12AC // famous painting

#define FTR_PAINTING14 0x12E4 // worthy painting
#define FTR_PAINTING14_EAST 0x12E5
#define FTR_PAINTING14_NORTH 0x12E6
#define FTR_PAINTING14_WEST 0x12E7

#define FTR_DRACAENA 0x13B0
#define FTR_DRACAENA_EAST 0x13B1
#define FTR_DRACAENA_NORTH 0x13B2
#define FTR_DRACAENA_WEST 0x13B3

#define FTR_MANHOLE_COVER 0x1444

#define FTR_JACK_O_LANTERN 0x149C

#define FTR_JACK_IN_THE_BOX 0x14C4

#define FTR_BATH_MAT 0x154C

#define HANIWA_START 0x15B0
#define FTR_HANIWA000_SOUTH (HANIWA_START +   0)
#define FTR_HANIWA000_EAST  (HANIWA_START +   1)
#define FTR_HANIWA000_NORTH (HANIWA_START +   2)
#define FTR_HANIWA000_WEST  (HANIWA_START +   3)
#define FTR_HANIWA001_SOUTH (HANIWA_START +   4)
#define FTR_HANIWA001_EAST  (HANIWA_START +   5)
#define FTR_HANIWA001_NORTH (HANIWA_START +   6)
#define FTR_HANIWA001_WEST  (HANIWA_START +   7)
#define FTR_HANIWA002_SOUTH (HANIWA_START +   8)
#define FTR_HANIWA002_EAST  (HANIWA_START +   9)
#define FTR_HANIWA002_NORTH (HANIWA_START +  10)
#define FTR_HANIWA002_WEST  (HANIWA_START +  11)
#define FTR_HANIWA003_SOUTH (HANIWA_START +  12)
#define FTR_HANIWA003_EAST  (HANIWA_START +  13)
#define FTR_HANIWA003_NORTH (HANIWA_START +  14)
#define FTR_HANIWA003_WEST  (HANIWA_START +  15)
#define FTR_HANIWA004_SOUTH (HANIWA_START +  16)
#define FTR_HANIWA004_EAST  (HANIWA_START +  17)
#define FTR_HANIWA004_NORTH (HANIWA_START +  18)
#define FTR_HANIWA004_WEST  (HANIWA_START +  19)
#define FTR_HANIWA005_SOUTH (HANIWA_START +  20)
#define FTR_HANIWA005_EAST  (HANIWA_START +  21)
#define FTR_HANIWA005_NORTH (HANIWA_START +  22)
#define FTR_HANIWA005_WEST  (HANIWA_START +  23)
#define FTR_HANIWA006_SOUTH (HANIWA_START +  24)
#define FTR_HANIWA006_EAST  (HANIWA_START +  25)
#define FTR_HANIWA006_NORTH (HANIWA_START +  26)
#define FTR_HANIWA006_WEST  (HANIWA_START +  27)
#define FTR_HANIWA007_SOUTH (HANIWA_START +  28)
#define FTR_HANIWA007_EAST  (HANIWA_START +  29)
#define FTR_HANIWA007_NORTH (HANIWA_START +  30)
#define FTR_HANIWA007_WEST  (HANIWA_START +  31)
#define FTR_HANIWA008_SOUTH (HANIWA_START +  32)
#define FTR_HANIWA008_EAST  (HANIWA_START +  33)
#define FTR_HANIWA008_NORTH (HANIWA_START +  34)
#define FTR_HANIWA008_WEST  (HANIWA_START +  35)
#define FTR_HANIWA009_SOUTH (HANIWA_START +  36)
#define FTR_HANIWA009_EAST  (HANIWA_START +  37)
#define FTR_HANIWA009_NORTH (HANIWA_START +  38)
#define FTR_HANIWA009_WEST  (HANIWA_START +  39)
#define FTR_HANIWA010_SOUTH (HANIWA_START +  40)
#define FTR_HANIWA010_EAST  (HANIWA_START +  41)
#define FTR_HANIWA010_NORTH (HANIWA_START +  42)
#define FTR_HANIWA010_WEST  (HANIWA_START +  43)
#define FTR_HANIWA011_SOUTH (HANIWA_START +  44)
#define FTR_HANIWA011_EAST  (HANIWA_START +  45)
#define FTR_HANIWA011_NORTH (HANIWA_START +  46)
#define FTR_HANIWA011_WEST  (HANIWA_START +  47)
#define FTR_HANIWA012_SOUTH (HANIWA_START +  48)
#define FTR_HANIWA012_EAST  (HANIWA_START +  49)
#define FTR_HANIWA012_NORTH (HANIWA_START +  50)
#define FTR_HANIWA012_WEST  (HANIWA_START +  51)
#define FTR_HANIWA013_SOUTH (HANIWA_START +  52)
#define FTR_HANIWA013_EAST  (HANIWA_START +  53)
#define FTR_HANIWA013_NORTH (HANIWA_START +  54)
#define FTR_HANIWA013_WEST  (HANIWA_START +  55)
#define FTR_HANIWA014_SOUTH (HANIWA_START +  56)
#define FTR_HANIWA014_EAST  (HANIWA_START +  57)
#define FTR_HANIWA014_NORTH (HANIWA_START +  58)
#define FTR_HANIWA014_WEST  (HANIWA_START +  59)
#define FTR_HANIWA015_SOUTH (HANIWA_START +  60)
#define FTR_HANIWA015_EAST  (HANIWA_START +  61)
#define FTR_HANIWA015_NORTH (HANIWA_START +  62)
#define FTR_HANIWA015_WEST  (HANIWA_START +  63)
#define FTR_HANIWA016_SOUTH (HANIWA_START +  64)
#define FTR_HANIWA016_EAST  (HANIWA_START +  65)
#define FTR_HANIWA016_NORTH (HANIWA_START +  66)
#define FTR_HANIWA016_WEST  (HANIWA_START +  67)
#define FTR_HANIWA017_SOUTH (HANIWA_START +  68)
#define FTR_HANIWA017_EAST  (HANIWA_START +  69)
#define FTR_HANIWA017_NORTH (HANIWA_START +  70)
#define FTR_HANIWA017_WEST  (HANIWA_START +  71)
#define FTR_HANIWA018_SOUTH (HANIWA_START +  72)
#define FTR_HANIWA018_EAST  (HANIWA_START +  73)
#define FTR_HANIWA018_NORTH (HANIWA_START +  74)
#define FTR_HANIWA018_WEST  (HANIWA_START +  75)
#define FTR_HANIWA019_SOUTH (HANIWA_START +  76)
#define FTR_HANIWA019_EAST  (HANIWA_START +  77)
#define FTR_HANIWA019_NORTH (HANIWA_START +  78)
#define FTR_HANIWA019_WEST  (HANIWA_START +  79)
#define FTR_HANIWA020_SOUTH (HANIWA_START +  80)
#define FTR_HANIWA020_EAST  (HANIWA_START +  81)
#define FTR_HANIWA020_NORTH (HANIWA_START +  82)
#define FTR_HANIWA020_WEST  (HANIWA_START +  83)
#define FTR_HANIWA021_SOUTH (HANIWA_START +  84)
#define FTR_HANIWA021_EAST  (HANIWA_START +  85)
#define FTR_HANIWA021_NORTH (HANIWA_START +  86)
#define FTR_HANIWA021_WEST  (HANIWA_START +  87)
#define FTR_HANIWA022_SOUTH (HANIWA_START +  88)
#define FTR_HANIWA022_EAST  (HANIWA_START +  89)
#define FTR_HANIWA022_NORTH (HANIWA_START +  90)
#define FTR_HANIWA022_WEST  (HANIWA_START +  91)
#define FTR_HANIWA023_SOUTH (HANIWA_START +  92)
#define FTR_HANIWA023_EAST  (HANIWA_START +  93)
#define FTR_HANIWA023_NORTH (HANIWA_START +  94)
#define FTR_HANIWA023_WEST  (HANIWA_START +  95)
#define FTR_HANIWA024_SOUTH (HANIWA_START +  96)
#define FTR_HANIWA024_EAST  (HANIWA_START +  97)
#define FTR_HANIWA024_NORTH (HANIWA_START +  98)
#define FTR_HANIWA024_WEST  (HANIWA_START +  99)
#define FTR_HANIWA025_SOUTH (HANIWA_START + 100)
#define FTR_HANIWA025_EAST  (HANIWA_START + 101)
#define FTR_HANIWA025_NORTH (HANIWA_START + 102)
#define FTR_HANIWA025_WEST  (HANIWA_START + 103)
#define FTR_HANIWA026_SOUTH (HANIWA_START + 104)
#define FTR_HANIWA026_EAST  (HANIWA_START + 105)
#define FTR_HANIWA026_NORTH (HANIWA_START + 106)
#define FTR_HANIWA026_WEST  (HANIWA_START + 107)
#define FTR_HANIWA027_SOUTH (HANIWA_START + 108)
#define FTR_HANIWA027_EAST  (HANIWA_START + 109)
#define FTR_HANIWA027_NORTH (HANIWA_START + 110)
#define FTR_HANIWA027_WEST  (HANIWA_START + 111)
#define FTR_HANIWA028_SOUTH (HANIWA_START + 112)
#define FTR_HANIWA028_EAST  (HANIWA_START + 113)
#define FTR_HANIWA028_NORTH (HANIWA_START + 114)
#define FTR_HANIWA028_WEST  (HANIWA_START + 115)
#define FTR_HANIWA029_SOUTH (HANIWA_START + 116)
#define FTR_HANIWA029_EAST  (HANIWA_START + 117)
#define FTR_HANIWA029_NORTH (HANIWA_START + 118)
#define FTR_HANIWA029_WEST  (HANIWA_START + 119)
#define FTR_HANIWA030_SOUTH (HANIWA_START + 120)
#define FTR_HANIWA030_EAST  (HANIWA_START + 121)
#define FTR_HANIWA030_NORTH (HANIWA_START + 122)
#define FTR_HANIWA030_WEST  (HANIWA_START + 123)
#define FTR_HANIWA031_SOUTH (HANIWA_START + 124)
#define FTR_HANIWA031_EAST  (HANIWA_START + 125)
#define FTR_HANIWA031_NORTH (HANIWA_START + 126)
#define FTR_HANIWA031_WEST  (HANIWA_START + 127)
#define FTR_HANIWA032_SOUTH (HANIWA_START + 128)
#define FTR_HANIWA032_EAST  (HANIWA_START + 129)
#define FTR_HANIWA032_NORTH (HANIWA_START + 130)
#define FTR_HANIWA032_WEST  (HANIWA_START + 131)
#define FTR_HANIWA033_SOUTH (HANIWA_START + 132)
#define FTR_HANIWA033_EAST  (HANIWA_START + 133)
#define FTR_HANIWA033_NORTH (HANIWA_START + 134)
#define FTR_HANIWA033_WEST  (HANIWA_START + 135)
#define FTR_HANIWA034_SOUTH (HANIWA_START + 136)
#define FTR_HANIWA034_EAST  (HANIWA_START + 137)
#define FTR_HANIWA034_NORTH (HANIWA_START + 138)
#define FTR_HANIWA034_WEST  (HANIWA_START + 139)
#define FTR_HANIWA035_SOUTH (HANIWA_START + 140)
#define FTR_HANIWA035_EAST  (HANIWA_START + 141)
#define FTR_HANIWA035_NORTH (HANIWA_START + 142)
#define FTR_HANIWA035_WEST  (HANIWA_START + 143)
#define FTR_HANIWA036_SOUTH (HANIWA_START + 144)
#define FTR_HANIWA036_EAST  (HANIWA_START + 145)
#define FTR_HANIWA036_NORTH (HANIWA_START + 146)
#define FTR_HANIWA036_WEST  (HANIWA_START + 147)
#define FTR_HANIWA037_SOUTH (HANIWA_START + 148)
#define FTR_HANIWA037_EAST  (HANIWA_START + 149)
#define FTR_HANIWA037_NORTH (HANIWA_START + 150)
#define FTR_HANIWA037_WEST  (HANIWA_START + 151)
#define FTR_HANIWA038_SOUTH (HANIWA_START + 152)
#define FTR_HANIWA038_EAST  (HANIWA_START + 153)
#define FTR_HANIWA038_NORTH (HANIWA_START + 154)
#define FTR_HANIWA038_WEST  (HANIWA_START + 155)
#define FTR_HANIWA039_SOUTH (HANIWA_START + 156)
#define FTR_HANIWA039_EAST  (HANIWA_START + 157)
#define FTR_HANIWA039_NORTH (HANIWA_START + 158)
#define FTR_HANIWA039_WEST  (HANIWA_START + 159)
#define FTR_HANIWA040_SOUTH (HANIWA_START + 160)
#define FTR_HANIWA040_EAST  (HANIWA_START + 161)
#define FTR_HANIWA040_NORTH (HANIWA_START + 162)
#define FTR_HANIWA040_WEST  (HANIWA_START + 163)
#define FTR_HANIWA041_SOUTH (HANIWA_START + 164)
#define FTR_HANIWA041_EAST  (HANIWA_START + 165)
#define FTR_HANIWA041_NORTH (HANIWA_START + 166)
#define FTR_HANIWA041_WEST  (HANIWA_START + 167)
#define FTR_HANIWA042_SOUTH (HANIWA_START + 168)
#define FTR_HANIWA042_EAST  (HANIWA_START + 169)
#define FTR_HANIWA042_NORTH (HANIWA_START + 170)
#define FTR_HANIWA042_WEST  (HANIWA_START + 171)
#define FTR_HANIWA043_SOUTH (HANIWA_START + 172)
#define FTR_HANIWA043_EAST  (HANIWA_START + 173)
#define FTR_HANIWA043_NORTH (HANIWA_START + 174)
#define FTR_HANIWA043_WEST  (HANIWA_START + 175)
#define FTR_HANIWA044_SOUTH (HANIWA_START + 176)
#define FTR_HANIWA044_EAST  (HANIWA_START + 177)
#define FTR_HANIWA044_NORTH (HANIWA_START + 178)
#define FTR_HANIWA044_WEST  (HANIWA_START + 179)
#define FTR_HANIWA045_SOUTH (HANIWA_START + 180)
#define FTR_HANIWA045_EAST  (HANIWA_START + 181)
#define FTR_HANIWA045_NORTH (HANIWA_START + 182)
#define FTR_HANIWA045_WEST  (HANIWA_START + 183)
#define FTR_HANIWA046_SOUTH (HANIWA_START + 184)
#define FTR_HANIWA046_EAST  (HANIWA_START + 185)
#define FTR_HANIWA046_NORTH (HANIWA_START + 186)
#define FTR_HANIWA046_WEST  (HANIWA_START + 187)
#define FTR_HANIWA047_SOUTH (HANIWA_START + 188)
#define FTR_HANIWA047_EAST  (HANIWA_START + 189)
#define FTR_HANIWA047_NORTH (HANIWA_START + 190)
#define FTR_HANIWA047_WEST  (HANIWA_START + 191)
#define FTR_HANIWA048_SOUTH (HANIWA_START + 192)
#define FTR_HANIWA048_EAST  (HANIWA_START + 193)
#define FTR_HANIWA048_NORTH (HANIWA_START + 194)
#define FTR_HANIWA048_WEST  (HANIWA_START + 195)
#define FTR_HANIWA049_SOUTH (HANIWA_START + 196)
#define FTR_HANIWA049_EAST  (HANIWA_START + 197)
#define FTR_HANIWA049_NORTH (HANIWA_START + 198)
#define FTR_HANIWA049_WEST  (HANIWA_START + 199)
#define FTR_HANIWA050_SOUTH (HANIWA_START + 200)
#define FTR_HANIWA050_EAST  (HANIWA_START + 201)
#define FTR_HANIWA050_NORTH (HANIWA_START + 202)
#define FTR_HANIWA050_WEST  (HANIWA_START + 203)
#define FTR_HANIWA051_SOUTH (HANIWA_START + 204)
#define FTR_HANIWA051_EAST  (HANIWA_START + 205)
#define FTR_HANIWA051_NORTH (HANIWA_START + 206)
#define FTR_HANIWA051_WEST  (HANIWA_START + 207)
#define FTR_HANIWA052_SOUTH (HANIWA_START + 208)
#define FTR_HANIWA052_EAST  (HANIWA_START + 209)
#define FTR_HANIWA052_NORTH (HANIWA_START + 210)
#define FTR_HANIWA052_WEST  (HANIWA_START + 211)
#define FTR_HANIWA053_SOUTH (HANIWA_START + 212)
#define FTR_HANIWA053_EAST  (HANIWA_START + 213)
#define FTR_HANIWA053_NORTH (HANIWA_START + 214)
#define FTR_HANIWA053_WEST  (HANIWA_START + 215)
#define FTR_HANIWA054_SOUTH (HANIWA_START + 216)
#define FTR_HANIWA054_EAST  (HANIWA_START + 217)
#define FTR_HANIWA054_NORTH (HANIWA_START + 218)
#define FTR_HANIWA054_WEST  (HANIWA_START + 219)
#define FTR_HANIWA055_SOUTH (HANIWA_START + 220)
#define FTR_HANIWA055_EAST  (HANIWA_START + 221)
#define FTR_HANIWA055_NORTH (HANIWA_START + 222)
#define FTR_HANIWA055_WEST  (HANIWA_START + 223)
#define FTR_HANIWA056_SOUTH (HANIWA_START + 224)
#define FTR_HANIWA056_EAST  (HANIWA_START + 225)
#define FTR_HANIWA056_NORTH (HANIWA_START + 226)
#define FTR_HANIWA056_WEST  (HANIWA_START + 227)
#define FTR_HANIWA057_SOUTH (HANIWA_START + 228)
#define FTR_HANIWA057_EAST  (HANIWA_START + 229)
#define FTR_HANIWA057_NORTH (HANIWA_START + 230)
#define FTR_HANIWA057_WEST  (HANIWA_START + 231)
#define FTR_HANIWA058_SOUTH (HANIWA_START + 232)
#define FTR_HANIWA058_EAST  (HANIWA_START + 233)
#define FTR_HANIWA058_NORTH (HANIWA_START + 234)
#define FTR_HANIWA058_WEST  (HANIWA_START + 235)
#define FTR_HANIWA059_SOUTH (HANIWA_START + 236)
#define FTR_HANIWA059_EAST  (HANIWA_START + 237)
#define FTR_HANIWA059_NORTH (HANIWA_START + 238)
#define FTR_HANIWA059_WEST  (HANIWA_START + 239)
#define FTR_HANIWA060_SOUTH (HANIWA_START + 240)
#define FTR_HANIWA060_EAST  (HANIWA_START + 241)
#define FTR_HANIWA060_NORTH (HANIWA_START + 242)
#define FTR_HANIWA060_WEST  (HANIWA_START + 243)
#define FTR_HANIWA061_SOUTH (HANIWA_START + 244)
#define FTR_HANIWA061_EAST  (HANIWA_START + 245)
#define FTR_HANIWA061_NORTH (HANIWA_START + 246)
#define FTR_HANIWA061_WEST  (HANIWA_START + 247)
#define FTR_HANIWA062_SOUTH (HANIWA_START + 248)
#define FTR_HANIWA062_EAST  (HANIWA_START + 249)
#define FTR_HANIWA062_NORTH (HANIWA_START + 250)
#define FTR_HANIWA062_WEST  (HANIWA_START + 251)
#define FTR_HANIWA063_SOUTH (HANIWA_START + 252)
#define FTR_HANIWA063_EAST  (HANIWA_START + 253)
#define FTR_HANIWA063_NORTH (HANIWA_START + 254)
#define FTR_HANIWA063_WEST  (HANIWA_START + 255)
#define FTR_HANIWA064_SOUTH (HANIWA_START + 256)
#define FTR_HANIWA064_EAST  (HANIWA_START + 257)
#define FTR_HANIWA064_NORTH (HANIWA_START + 258)
#define FTR_HANIWA064_WEST  (HANIWA_START + 259)
#define FTR_HANIWA065_SOUTH (HANIWA_START + 260)
#define FTR_HANIWA065_EAST  (HANIWA_START + 261)
#define FTR_HANIWA065_NORTH (HANIWA_START + 262)
#define FTR_HANIWA065_WEST  (HANIWA_START + 263)
#define FTR_HANIWA066_SOUTH (HANIWA_START + 264)
#define FTR_HANIWA066_EAST  (HANIWA_START + 265)
#define FTR_HANIWA066_NORTH (HANIWA_START + 266)
#define FTR_HANIWA066_WEST  (HANIWA_START + 267)
#define FTR_HANIWA067_SOUTH (HANIWA_START + 268)
#define FTR_HANIWA067_EAST  (HANIWA_START + 269)
#define FTR_HANIWA067_NORTH (HANIWA_START + 270)
#define FTR_HANIWA067_WEST  (HANIWA_START + 271)
#define FTR_HANIWA068_SOUTH (HANIWA_START + 272)
#define FTR_HANIWA068_EAST  (HANIWA_START + 273)
#define FTR_HANIWA068_NORTH (HANIWA_START + 274)
#define FTR_HANIWA068_WEST  (HANIWA_START + 275)
#define FTR_HANIWA069_SOUTH (HANIWA_START + 276)
#define FTR_HANIWA069_EAST  (HANIWA_START + 277)
#define FTR_HANIWA069_NORTH (HANIWA_START + 278)
#define FTR_HANIWA069_WEST  (HANIWA_START + 279)
#define FTR_HANIWA070_SOUTH (HANIWA_START + 280)
#define FTR_HANIWA070_EAST  (HANIWA_START + 281)
#define FTR_HANIWA070_NORTH (HANIWA_START + 282)
#define FTR_HANIWA070_WEST  (HANIWA_START + 283)
#define FTR_HANIWA071_SOUTH (HANIWA_START + 284)
#define FTR_HANIWA071_EAST  (HANIWA_START + 285)
#define FTR_HANIWA071_NORTH (HANIWA_START + 286)
#define FTR_HANIWA071_WEST  (HANIWA_START + 287)
#define FTR_HANIWA072_SOUTH (HANIWA_START + 288)
#define FTR_HANIWA072_EAST  (HANIWA_START + 289)
#define FTR_HANIWA072_NORTH (HANIWA_START + 290)
#define FTR_HANIWA072_WEST  (HANIWA_START + 291)
#define FTR_HANIWA073_SOUTH (HANIWA_START + 292)
#define FTR_HANIWA073_EAST  (HANIWA_START + 293)
#define FTR_HANIWA073_NORTH (HANIWA_START + 294)
#define FTR_HANIWA073_WEST  (HANIWA_START + 295)
#define FTR_HANIWA074_SOUTH (HANIWA_START + 296)
#define FTR_HANIWA074_EAST  (HANIWA_START + 297)
#define FTR_HANIWA074_NORTH (HANIWA_START + 298)
#define FTR_HANIWA074_WEST  (HANIWA_START + 299)
#define FTR_HANIWA075_SOUTH (HANIWA_START + 300)
#define FTR_HANIWA075_EAST  (HANIWA_START + 301)
#define FTR_HANIWA075_NORTH (HANIWA_START + 302)
#define FTR_HANIWA075_WEST  (HANIWA_START + 303)
#define FTR_HANIWA076_SOUTH (HANIWA_START + 304)
#define FTR_HANIWA076_EAST  (HANIWA_START + 305)
#define FTR_HANIWA076_NORTH (HANIWA_START + 306)
#define FTR_HANIWA076_WEST  (HANIWA_START + 307)
#define FTR_HANIWA077_SOUTH (HANIWA_START + 308)
#define FTR_HANIWA077_EAST  (HANIWA_START + 309)
#define FTR_HANIWA077_NORTH (HANIWA_START + 310)
#define FTR_HANIWA077_WEST  (HANIWA_START + 311)
#define FTR_HANIWA078_SOUTH (HANIWA_START + 312)
#define FTR_HANIWA078_EAST  (HANIWA_START + 313)
#define FTR_HANIWA078_NORTH (HANIWA_START + 314)
#define FTR_HANIWA078_WEST  (HANIWA_START + 315)
#define FTR_HANIWA079_SOUTH (HANIWA_START + 316)
#define FTR_HANIWA079_EAST  (HANIWA_START + 317)
#define FTR_HANIWA079_NORTH (HANIWA_START + 318)
#define FTR_HANIWA079_WEST  (HANIWA_START + 319)
#define FTR_HANIWA080_SOUTH (HANIWA_START + 320)
#define FTR_HANIWA080_EAST  (HANIWA_START + 321)
#define FTR_HANIWA080_NORTH (HANIWA_START + 322)
#define FTR_HANIWA080_WEST  (HANIWA_START + 323)
#define FTR_HANIWA081_SOUTH (HANIWA_START + 324)
#define FTR_HANIWA081_EAST  (HANIWA_START + 325)
#define FTR_HANIWA081_NORTH (HANIWA_START + 326)
#define FTR_HANIWA081_WEST  (HANIWA_START + 327)
#define FTR_HANIWA082_SOUTH (HANIWA_START + 328)
#define FTR_HANIWA082_EAST  (HANIWA_START + 329)
#define FTR_HANIWA082_NORTH (HANIWA_START + 330)
#define FTR_HANIWA082_WEST  (HANIWA_START + 331)
#define FTR_HANIWA083_SOUTH (HANIWA_START + 332)
#define FTR_HANIWA083_EAST  (HANIWA_START + 333)
#define FTR_HANIWA083_NORTH (HANIWA_START + 334)
#define FTR_HANIWA083_WEST  (HANIWA_START + 335)
#define FTR_HANIWA084_SOUTH (HANIWA_START + 336)
#define FTR_HANIWA084_EAST  (HANIWA_START + 337)
#define FTR_HANIWA084_NORTH (HANIWA_START + 338)
#define FTR_HANIWA084_WEST  (HANIWA_START + 339)
#define FTR_HANIWA085_SOUTH (HANIWA_START + 340)
#define FTR_HANIWA085_EAST  (HANIWA_START + 341)
#define FTR_HANIWA085_NORTH (HANIWA_START + 342)
#define FTR_HANIWA085_WEST  (HANIWA_START + 343)
#define FTR_HANIWA086_SOUTH (HANIWA_START + 344)
#define FTR_HANIWA086_EAST  (HANIWA_START + 345)
#define FTR_HANIWA086_NORTH (HANIWA_START + 346)
#define FTR_HANIWA086_WEST  (HANIWA_START + 347)
#define FTR_HANIWA087_SOUTH (HANIWA_START + 348)
#define FTR_HANIWA087_EAST  (HANIWA_START + 349)
#define FTR_HANIWA087_NORTH (HANIWA_START + 350)
#define FTR_HANIWA087_WEST  (HANIWA_START + 351)
#define FTR_HANIWA088_SOUTH (HANIWA_START + 352)
#define FTR_HANIWA088_EAST  (HANIWA_START + 353)
#define FTR_HANIWA088_NORTH (HANIWA_START + 354)
#define FTR_HANIWA088_WEST  (HANIWA_START + 355)
#define FTR_HANIWA089_SOUTH (HANIWA_START + 356)
#define FTR_HANIWA089_EAST  (HANIWA_START + 357)
#define FTR_HANIWA089_NORTH (HANIWA_START + 358)
#define FTR_HANIWA089_WEST  (HANIWA_START + 359)
#define FTR_HANIWA090_SOUTH (HANIWA_START + 360)
#define FTR_HANIWA090_EAST  (HANIWA_START + 361)
#define FTR_HANIWA090_NORTH (HANIWA_START + 362)
#define FTR_HANIWA090_WEST  (HANIWA_START + 363)
#define FTR_HANIWA091_SOUTH (HANIWA_START + 364)
#define FTR_HANIWA091_EAST  (HANIWA_START + 365)
#define FTR_HANIWA091_NORTH (HANIWA_START + 366)
#define FTR_HANIWA091_WEST  (HANIWA_START + 367)
#define FTR_HANIWA092_SOUTH (HANIWA_START + 368)
#define FTR_HANIWA092_EAST  (HANIWA_START + 369)
#define FTR_HANIWA092_NORTH (HANIWA_START + 370)
#define FTR_HANIWA092_WEST  (HANIWA_START + 371)
#define FTR_HANIWA093_SOUTH (HANIWA_START + 372)
#define FTR_HANIWA093_EAST  (HANIWA_START + 373)
#define FTR_HANIWA093_NORTH (HANIWA_START + 374)
#define FTR_HANIWA093_WEST  (HANIWA_START + 375)
#define FTR_HANIWA094_SOUTH (HANIWA_START + 376)
#define FTR_HANIWA094_EAST  (HANIWA_START + 377)
#define FTR_HANIWA094_NORTH (HANIWA_START + 378)
#define FTR_HANIWA094_WEST  (HANIWA_START + 379)
#define FTR_HANIWA095_SOUTH (HANIWA_START + 380)
#define FTR_HANIWA095_EAST  (HANIWA_START + 381)
#define FTR_HANIWA095_NORTH (HANIWA_START + 382)
#define FTR_HANIWA095_WEST  (HANIWA_START + 383)
#define FTR_HANIWA096_SOUTH (HANIWA_START + 384)
#define FTR_HANIWA096_EAST  (HANIWA_START + 385)
#define FTR_HANIWA096_NORTH (HANIWA_START + 386)
#define FTR_HANIWA096_WEST  (HANIWA_START + 387)
#define FTR_HANIWA097_SOUTH (HANIWA_START + 388)
#define FTR_HANIWA097_EAST  (HANIWA_START + 389)
#define FTR_HANIWA097_NORTH (HANIWA_START + 390)
#define FTR_HANIWA097_WEST  (HANIWA_START + 391)
#define FTR_HANIWA098_SOUTH (HANIWA_START + 392)
#define FTR_HANIWA098_EAST  (HANIWA_START + 393)
#define FTR_HANIWA098_NORTH (HANIWA_START + 394)
#define FTR_HANIWA098_WEST  (HANIWA_START + 395)
#define FTR_HANIWA099_SOUTH (HANIWA_START + 396)
#define FTR_HANIWA099_EAST  (HANIWA_START + 397)
#define FTR_HANIWA099_NORTH (HANIWA_START + 398)
#define FTR_HANIWA099_WEST  (HANIWA_START + 399)
#define FTR_HANIWA100_SOUTH (HANIWA_START + 400)
#define FTR_HANIWA100_EAST  (HANIWA_START + 401)
#define FTR_HANIWA100_NORTH (HANIWA_START + 402)
#define FTR_HANIWA100_WEST  (HANIWA_START + 403)
#define FTR_HANIWA101_SOUTH (HANIWA_START + 404)
#define FTR_HANIWA101_EAST  (HANIWA_START + 405)
#define FTR_HANIWA101_NORTH (HANIWA_START + 406)
#define FTR_HANIWA101_WEST  (HANIWA_START + 407)
#define FTR_HANIWA102_SOUTH (HANIWA_START + 408)
#define FTR_HANIWA102_EAST  (HANIWA_START + 409)
#define FTR_HANIWA102_NORTH (HANIWA_START + 410)
#define FTR_HANIWA102_WEST  (HANIWA_START + 411)
#define FTR_HANIWA103_SOUTH (HANIWA_START + 412)
#define FTR_HANIWA103_EAST  (HANIWA_START + 413)
#define FTR_HANIWA103_NORTH (HANIWA_START + 414)
#define FTR_HANIWA103_WEST  (HANIWA_START + 415)
#define FTR_HANIWA104_SOUTH (HANIWA_START + 416)
#define FTR_HANIWA104_EAST  (HANIWA_START + 417)
#define FTR_HANIWA104_NORTH (HANIWA_START + 418)
#define FTR_HANIWA104_WEST  (HANIWA_START + 419)
#define FTR_HANIWA105_SOUTH (HANIWA_START + 420)
#define FTR_HANIWA105_EAST  (HANIWA_START + 421)
#define FTR_HANIWA105_NORTH (HANIWA_START + 422)
#define FTR_HANIWA105_WEST  (HANIWA_START + 423)
#define FTR_HANIWA106_SOUTH (HANIWA_START + 424)
#define FTR_HANIWA106_EAST  (HANIWA_START + 425)
#define FTR_HANIWA106_NORTH (HANIWA_START + 426)
#define FTR_HANIWA106_WEST  (HANIWA_START + 427)
#define FTR_HANIWA107_SOUTH (HANIWA_START + 428)
#define FTR_HANIWA107_EAST  (HANIWA_START + 429)
#define FTR_HANIWA107_NORTH (HANIWA_START + 430)
#define FTR_HANIWA107_WEST  (HANIWA_START + 431)
#define FTR_HANIWA108_SOUTH (HANIWA_START + 432)
#define FTR_HANIWA108_EAST  (HANIWA_START + 433)
#define FTR_HANIWA108_NORTH (HANIWA_START + 434)
#define FTR_HANIWA108_WEST  (HANIWA_START + 435)
#define FTR_HANIWA109_SOUTH (HANIWA_START + 436)
#define FTR_HANIWA109_EAST  (HANIWA_START + 437)
#define FTR_HANIWA109_NORTH (HANIWA_START + 438)
#define FTR_HANIWA109_WEST  (HANIWA_START + 439)
#define FTR_HANIWA110_SOUTH (HANIWA_START + 440)
#define FTR_HANIWA110_EAST  (HANIWA_START + 441)
#define FTR_HANIWA110_NORTH (HANIWA_START + 442)
#define FTR_HANIWA110_WEST  (HANIWA_START + 443)
#define FTR_HANIWA111_SOUTH (HANIWA_START + 444)
#define FTR_HANIWA111_EAST  (HANIWA_START + 445)
#define FTR_HANIWA111_NORTH (HANIWA_START + 446)
#define FTR_HANIWA111_WEST  (HANIWA_START + 447)
#define FTR_HANIWA112_SOUTH (HANIWA_START + 448)
#define FTR_HANIWA112_EAST  (HANIWA_START + 449)
#define FTR_HANIWA112_NORTH (HANIWA_START + 450)
#define FTR_HANIWA112_WEST  (HANIWA_START + 451)
#define FTR_HANIWA113_SOUTH (HANIWA_START + 452)
#define FTR_HANIWA113_EAST  (HANIWA_START + 453)
#define FTR_HANIWA113_NORTH (HANIWA_START + 454)
#define FTR_HANIWA113_WEST  (HANIWA_START + 455)
#define FTR_HANIWA114_SOUTH (HANIWA_START + 456)
#define FTR_HANIWA114_EAST  (HANIWA_START + 457)
#define FTR_HANIWA114_NORTH (HANIWA_START + 458)
#define FTR_HANIWA114_WEST  (HANIWA_START + 459)
#define FTR_HANIWA115_SOUTH (HANIWA_START + 460)
#define FTR_HANIWA115_EAST  (HANIWA_START + 461)
#define FTR_HANIWA115_NORTH (HANIWA_START + 462)
#define FTR_HANIWA115_WEST  (HANIWA_START + 463)
#define FTR_HANIWA116_SOUTH (HANIWA_START + 464)
#define FTR_HANIWA116_EAST  (HANIWA_START + 465)
#define FTR_HANIWA116_NORTH (HANIWA_START + 466)
#define FTR_HANIWA116_WEST  (HANIWA_START + 467)
#define FTR_HANIWA117_SOUTH (HANIWA_START + 468)
#define FTR_HANIWA117_EAST  (HANIWA_START + 469)
#define FTR_HANIWA117_NORTH (HANIWA_START + 470)
#define FTR_HANIWA117_WEST  (HANIWA_START + 471)
#define FTR_HANIWA118_SOUTH (HANIWA_START + 472)
#define FTR_HANIWA118_EAST  (HANIWA_START + 473)
#define FTR_HANIWA118_NORTH (HANIWA_START + 474)
#define FTR_HANIWA118_WEST  (HANIWA_START + 475)
#define FTR_HANIWA119_SOUTH (HANIWA_START + 476)
#define FTR_HANIWA119_EAST  (HANIWA_START + 477)
#define FTR_HANIWA119_NORTH (HANIWA_START + 478)
#define FTR_HANIWA119_WEST  (HANIWA_START + 479)
#define FTR_HANIWA120_SOUTH (HANIWA_START + 480)
#define FTR_HANIWA120_EAST  (HANIWA_START + 481)
#define FTR_HANIWA120_NORTH (HANIWA_START + 482)
#define FTR_HANIWA120_WEST  (HANIWA_START + 483)
#define FTR_HANIWA121_SOUTH (HANIWA_START + 484)
#define FTR_HANIWA121_EAST  (HANIWA_START + 485)
#define FTR_HANIWA121_NORTH (HANIWA_START + 486)
#define FTR_HANIWA121_WEST  (HANIWA_START + 487)
#define FTR_HANIWA122_SOUTH (HANIWA_START + 488)
#define FTR_HANIWA122_EAST  (HANIWA_START + 489)
#define FTR_HANIWA122_NORTH (HANIWA_START + 490)
#define FTR_HANIWA122_WEST  (HANIWA_START + 491)
#define FTR_HANIWA123_SOUTH (HANIWA_START + 492)
#define FTR_HANIWA123_EAST  (HANIWA_START + 493)
#define FTR_HANIWA123_NORTH (HANIWA_START + 494)
#define FTR_HANIWA123_WEST  (HANIWA_START + 495)
#define FTR_HANIWA124_SOUTH (HANIWA_START + 496)
#define FTR_HANIWA124_EAST  (HANIWA_START + 497)
#define FTR_HANIWA124_NORTH (HANIWA_START + 498)
#define FTR_HANIWA124_WEST  (HANIWA_START + 499)
#define FTR_HANIWA125_SOUTH (HANIWA_START + 500)
#define FTR_HANIWA125_EAST  (HANIWA_START + 501)
#define FTR_HANIWA125_NORTH (HANIWA_START + 502)
#define FTR_HANIWA125_WEST  (HANIWA_START + 503)
#define FTR_HANIWA126_SOUTH (HANIWA_START + 504)
#define FTR_HANIWA126_EAST  (HANIWA_START + 505)
#define FTR_HANIWA126_NORTH (HANIWA_START + 506)
#define FTR_HANIWA126_WEST  (HANIWA_START + 507)
#define HANIWA_END          (HANIWA_START + 507)

#define FTR_CLOTH_START 0x17AC
#define FTR_CLOTH_MANNIQUIN000_SOUTH FTR_CLOTH_START

#define FTR_REDALOHASHIRT 0x1814

#define FTR_BLUEALOHASHIRT 0x1818

#define FTR_CLOTH_MANNIQUIN254_SOUTH 0x1BA4
#define FTR_CLOTH_MANNIQUIN254_WEST 0x1BA7
#define FTR_CLOTH_END FTR_CLOTH_MANNIQUIN254_WEST
#define FTR_CLOTH_MANNIQUIN_MY_ORIGINAL0 0x1BA8
#define FTR_CLOTH_MYMANNIQUIN_END 0x1BC7
#define FTR_INSECT_START 0x1BC8
#define FTR_INSECT00 FTR_INSECT_START

#define FTR_INSECT39 0x1C64
#define FTR_INSECT39_EAST 0x1C65
#define FTR_INSECT39_NORTH 0x1C66
#define FTR_INSECT39_WEST 0x1C67
#define FTR_INSECT_END FTR_INSECT39_WEST
#define FTR_FISH_START 0x1C68
#define FTR_FISH00 FTR_FISH_START

#define FTR_FISH39 0x1D04
#define FTR_FISH39_EAST 0x1D05
#define FTR_FISH39_NORTH 0x1D06
#define FTR_FISH39_WEST 0x1D07
#define FTR_FISH_END FTR_FISH39_WEST
#define FTR_UMBRELLA_START 0x1D08
#define FTR_UMBRELLA00_SOUTH FTR_UMBRELLA_START

#define FTR_UMBRELLA31_WEST 0x1D87
#define FTR_UMBRELLA_END FTR_UMBRELLA31_WEST

#define FTR_MYUMBRELLA_START 0x1D88
#define FTR_MYUMBRELLA_END 0x1DA7

#define FTR_FAMICOM_START 0x1DA8
#define FTR_FAMICOM_CLU_CLU_LAND FTR_FAMICOM_START
#define FTR_FAMICOM_BALLOON_FIGHT 0x1DAC
#define FTR_FAMICOM_DONKEY_KONG 0x1DB0
#define FTR_FAMICOM_DK_JR_MATCH 0x1DB4
#define FTR_FAMICOM_PINBALL 0x1DB8
#define FTR_FAMICOM_TENNIS 0x1DBC
#define FTR_FAMICOM_GOLF 0x1DC0
#define FTR_FAMICOM_PUNCHOUT 0x1DC4
#define FTR_FAMICOM_BASEBALL 0x1DC8
#define FTR_FAMICOM_CLU_CLU_LAND_DISK 0x1DCC
#define FTR_FAMICOM_DONKEY_KONG_3 0x1DD0
#define FTR_FAMICOM_DONKEY_KONG_JR 0x1DD4
#define FTR_FAMICOM_SOCCER 0x1DD8
#define FTR_FAMICOM_EXCITEBIKE 0x1DDC
#define FTR_FAMICOM_WARIOS_WOODS 0x1DE0
#define FTR_FAMICOM_ICE_CLIMBERS 0x1DE4
#define FTR_FAMICOM_MARIO_BROS 0x1DE8
#define FTR_FAMICOM_SUPER_MARIO_BROS 0x1DEC
#define FTR_FAMICOM_LEGEND_OF_ZELDA 0x1DF0
#define FTR_FAMICOM_END 0x1DF3
#define FTR_FAMICOM 0x1DF4

#define FTR_TAPEDECK 0x1E58

#define FTR_BIG_FESTIVE_TREE 0x1E88

#define FTR_FESTIVE_TREE 0x1EBC

#define FTR_DINO_START 0x1EEC
#define FTR_DINO_TRICERA_SKULL FTR_DINO_START
#define FTR_DINO_TRICERA_TAIL 0x1EF0
#define FTR_DINO_TRICERA_BODY 0x1EF4
#define FTR_DINO_TREX_SKULL 0x1EF8
#define FTR_DINO_TREX_TAIL 0x1EFC
#define FTR_DINO_TREX_BODY 0x1F00
#define FTR_DINO_APATO_SKULL 0x1F04
#define FTR_DINO_APATO_TAIL 0x1F08
#define FTR_DINO_APATO_BODY 0x1F0C
#define FTR_DINO_STEGO_SKULL 0x1F10
#define FTR_DINO_STEGO_TAIL 0x1F14
#define FTR_DINO_STEGO_BODY 0x1F18
#define FTR_DINO_PTERA_SKULL 0x1F1C
#define FTR_DINO_PTERA_RIGHT_WING 0x1F20
#define FTR_DINO_PTERA_LEFT_WING 0x1F24
#define FTR_DINO_PLESIO_SKULL 0x1F28
#define FTR_DINO_PLESIO_NECK 0x1F2C
#define FTR_DINO_PLESIO_TORSO 0x1F30
#define FTR_DINO_MAMMOTH_SKULL 0x1F34
#define FTR_DINO_MAMMOTH_TORSO 0x1F38
#define FTR_FOSSIL_AMBER 0x1F3C
#define FTR_FOSSIL_TRACK 0x1F40
#define FTR_FOSSIL_AMMONITE 0x1F44
#define FTR_FOSSIL_EGG 0x1F48
#define FTR_FOSSIL_TRILOBITE 0x1F4C
//
#define FTR_DINO_TRILOBITE_WEST 0x1F4F
#define FTR_DINO_END FTR_DINO_TRILOBITE_WEST

#define FTR_DINO_DISP_TRICERA 0x1F7C
#define FTR_DINO_DISP_TREX 0x1F80
#define FTR_DINO_DISP_BRONTO 0x1F84
#define FTR_DINO_DISP_PTERA 0x1F88
#define FTR_DINO_DISP_PLESIO 0x1F8C
#define FTR_DINO_DISP_MAMMOTH 0x1F90
#define FTR_DINO_DISP_STEGO 0x1F94
#define FTR_DINO_DISP_STEGO2 0x1F98
#define FTR_FOSSIL 0x1F9C
#define FTR_SHOGI_PIECE 0x1FA0
#define FTR_CHOCOLATES 0x1FA4
#define FTR_POST_BOX 0x1FA8
#define FTR_PIGGY_BANK 0x1FAC
#define FTR_TISSUE 0x1FB0
#define FTR_TRIBAL_MASK 0x1FB4
#define FTR_MATRYOSHKA 0x1FB8
#define FTR_FAMICOM_LEGEND_OF_ZELDA_DISK 0x1FBC
#define FTR_BOTTLED_SHIP 0x1FC0
#define FTR_TIGER_BOBBLEHEAD 0x1FC4
#define FTR_MOAI_STATUE 0x1FC8
#define FTR_AEROBICS_RADIO 0x1FCC
#define FTR_PAGODA 0x1FD0
#define FTR_FISHING_BEAR 0x1FD4
#define FTR_MOUTH_OF_TRUTH 0x1FD8
#define FTR_CHINESE_LIONESS 0x1FDC
#define FTR_TOWER_OF_PISA 0x1FE0
#define FTR_MERLION 0x1FE4
#define FTR_MANEKIN_PIS 0x1FE8
#define FTR_TOKYO_TOWER 0x1FEC
#define FTR_RED_BALLOON 0x1FF0
#define FTR_YELLOW_BALLOON 0x1FF4
#define FTR_BLUE_BALLOON 0x1FF8
#define FTR_GREE_BALLOON 0x1FFC
#define FTR0_END 0x1FFF

#define ITM_PAPER_START 0x2000
#define ITM_PAPER00 (ITM_PAPER_START +   0)
#define ITM_PAPER01 (ITM_PAPER_START +   1)
#define ITM_PAPER02 (ITM_PAPER_START +   2)
#define ITM_PAPER03 (ITM_PAPER_START +   3)
#define ITM_PAPER04 (ITM_PAPER_START +   4)
#define ITM_PAPER05 (ITM_PAPER_START +   5)
#define ITM_PAPER06 (ITM_PAPER_START +   6)
#define ITM_PAPER07 (ITM_PAPER_START +   7)
#define ITM_PAPER08 (ITM_PAPER_START +   8)
#define ITM_PAPER09 (ITM_PAPER_START +   9)
#define ITM_PAPER10 (ITM_PAPER_START +  10)
#define ITM_PAPER11 (ITM_PAPER_START +  11)
#define ITM_PAPER12 (ITM_PAPER_START +  12)
#define ITM_PAPER13 (ITM_PAPER_START +  13)
#define ITM_PAPER14 (ITM_PAPER_START +  14)
#define ITM_PAPER15 (ITM_PAPER_START +  15)
#define ITM_PAPER16 (ITM_PAPER_START +  16)
#define ITM_PAPER17 (ITM_PAPER_START +  17)
#define ITM_PAPER18 (ITM_PAPER_START +  18)
#define ITM_PAPER19 (ITM_PAPER_START +  19)
#define ITM_PAPER20 (ITM_PAPER_START +  20)
#define ITM_PAPER21 (ITM_PAPER_START +  21)
#define ITM_PAPER22 (ITM_PAPER_START +  22)
#define ITM_PAPER23 (ITM_PAPER_START +  23)
#define ITM_PAPER24 (ITM_PAPER_START +  24)
#define ITM_PAPER25 (ITM_PAPER_START +  25)
#define ITM_PAPER26 (ITM_PAPER_START +  26)
#define ITM_PAPER27 (ITM_PAPER_START +  27)
#define ITM_PAPER28 (ITM_PAPER_START +  28)
#define ITM_PAPER29 (ITM_PAPER_START +  29)
#define ITM_PAPER30 (ITM_PAPER_START +  30)
#define ITM_PAPER31 (ITM_PAPER_START +  31)
#define ITM_PAPER32 (ITM_PAPER_START +  32)
#define ITM_PAPER33 (ITM_PAPER_START +  33)
#define ITM_PAPER34 (ITM_PAPER_START +  34)
#define ITM_PAPER35 (ITM_PAPER_START +  35)
#define ITM_PAPER36 (ITM_PAPER_START +  36)
#define ITM_PAPER37 (ITM_PAPER_START +  37)
#define ITM_PAPER38 (ITM_PAPER_START +  38)
#define ITM_PAPER39 (ITM_PAPER_START +  39)
#define ITM_PAPER40 (ITM_PAPER_START +  40)
#define ITM_PAPER41 (ITM_PAPER_START +  41)
#define ITM_PAPER42 (ITM_PAPER_START +  42)
#define ITM_PAPER43 (ITM_PAPER_START +  43)
#define ITM_PAPER44 (ITM_PAPER_START +  44)
#define ITM_PAPER45 (ITM_PAPER_START +  45)
#define ITM_PAPER46 (ITM_PAPER_START +  46)
#define ITM_PAPER47 (ITM_PAPER_START +  47)
#define ITM_PAPER48 (ITM_PAPER_START +  48)
#define ITM_PAPER49 (ITM_PAPER_START +  49)
#define ITM_PAPER50 (ITM_PAPER_START +  50)
#define ITM_PAPER51 (ITM_PAPER_START +  51)
#define ITM_PAPER52 (ITM_PAPER_START +  52)
#define ITM_PAPER53 (ITM_PAPER_START +  53)
#define ITM_PAPER54 (ITM_PAPER_START +  54)
#define ITM_PAPER55 (ITM_PAPER_START +  55)
#define ITM_PAPER56 (ITM_PAPER_START +  56)
#define ITM_PAPER57 (ITM_PAPER_START +  57)
#define ITM_PAPER58 (ITM_PAPER_START +  58)
#define ITM_PAPER59 (ITM_PAPER_START +  59)
#define ITM_PAPER60 (ITM_PAPER_START +  60)
#define ITM_PAPER61 (ITM_PAPER_START +  61)
#define ITM_PAPER62 (ITM_PAPER_START +  62)
#define ITM_PAPER63 (ITM_PAPER_START +  63)
#define ITM_PAPER_STACK_TWO_START 0x2040
#define ITM_PAPER_STACK_THREE_START 0x2080
#define ITM_PAPER_STACK_FOUR_START 0x20C0
#define ITM_PAPER_END (ITM_PAPER_START + 256)

#define ITM_MONEY_START 0x2100
#define ITM_MONEY_1000 ITM_MONEY_START // 0x2100
#define ITM_MONEY_10000 (ITM_MONEY_1000 + 1) // 0x2101
#define ITM_MONEY_30000 (ITM_MONEY_10000 + 1) // 0x2102
#define ITM_MONEY_100 (ITM_MONEY_30000 + 1) // 0x2103
#define ITM_MONEY_END ITM_MONEY_100 // 0x2103

#define ITM_TOOL_START 0x2200
#define ITM_NET ITM_TOOL_START
#define ITM_AXE 0x2201
#define ITM_SHOVEL 0x2202
#define ITM_ROD 0x2203
#define ITM_UMBRELLA_START (ITM_TOOL_START + 4)
#define ITM_UMBRELLA00 (ITM_TOOL_START +  4)
#define ITM_UMBRELLA01 (ITM_TOOL_START +  5)
#define ITM_UMBRELLA02 (ITM_TOOL_START +  6)
#define ITM_UMBRELLA03 (ITM_TOOL_START +  7)
#define ITM_UMBRELLA04 (ITM_TOOL_START +  8)
#define ITM_UMBRELLA05 (ITM_TOOL_START +  9)
#define ITM_UMBRELLA06 (ITM_TOOL_START + 10)
#define ITM_UMBRELLA07 (ITM_TOOL_START + 11)
#define ITM_UMBRELLA08 (ITM_TOOL_START + 12)
#define ITM_UMBRELLA09 (ITM_TOOL_START + 13)
#define ITM_UMBRELLA10 (ITM_TOOL_START + 14)
#define ITM_UMBRELLA11 (ITM_TOOL_START + 15)
#define ITM_UMBRELLA12 (ITM_TOOL_START + 16)
#define ITM_UMBRELLA13 (ITM_TOOL_START + 17)
#define ITM_UMBRELLA14 (ITM_TOOL_START + 18)
#define ITM_UMBRELLA15 (ITM_TOOL_START + 19)
#define ITM_UMBRELLA16 (ITM_TOOL_START + 20)
#define ITM_UMBRELLA17 (ITM_TOOL_START + 21)
#define ITM_UMBRELLA18 (ITM_TOOL_START + 22)
#define ITM_UMBRELLA19 (ITM_TOOL_START + 23)
#define ITM_UMBRELLA20 (ITM_TOOL_START + 24)
#define ITM_UMBRELLA21 (ITM_TOOL_START + 25)
#define ITM_UMBRELLA22 (ITM_TOOL_START + 26)
#define ITM_UMBRELLA23 (ITM_TOOL_START + 27)
#define ITM_UMBRELLA24 (ITM_TOOL_START + 28)
#define ITM_UMBRELLA25 (ITM_TOOL_START + 29)
#define ITM_UMBRELLA26 (ITM_TOOL_START + 30)
#define ITM_UMBRELLA27 (ITM_TOOL_START + 31)
#define ITM_UMBRELLA28 (ITM_TOOL_START + 32)
#define ITM_UMBRELLA29 (ITM_TOOL_START + 33)
#define ITM_UMBRELLA30 (ITM_TOOL_START + 34)
#define ITM_UMBRELLA31 (ITM_TOOL_START + 35)
#define ITM_MY_ORG_UMBRELLA0 (ITM_TOOL_START + 36)
#define ITM_MY_ORG_UMBRELLA1 (ITM_TOOL_START + 37)
#define ITM_MY_ORG_UMBRELLA2 (ITM_TOOL_START + 38)
#define ITM_MY_ORG_UMBRELLA3 (ITM_TOOL_START + 39)
#define ITM_MY_ORG_UMBRELLA4 (ITM_TOOL_START + 40)
#define ITM_MY_ORG_UMBRELLA5 (ITM_TOOL_START + 41)
#define ITM_MY_ORG_UMBRELLA6 (ITM_TOOL_START + 42)
#define ITM_MY_ORG_UMBRELLA7 (ITM_TOOL_START + 43)
#define ITM_UMBRELLA_END (ITM_TOOL_START + 44)
#define ITM_SICKLE 0x222C
#define ITM_RED_PAINT 0x222D
#define ITM_ORANGE_PAINT 0x222E
#define ITM_YELLOW_PAINT 0x222F
#define ITM_PALE_GREEN_PAINT 0x2230
#define ITM_GREEN_PAINT 0x2231
#define ITM_SKY_BLUE_PAINT 0x2232
#define ITM_BLUE_PAINT 0x2233
#define ITM_PURPLE_PAINT 0x2234
#define ITM_PINK_PAINT 0x2235
#define ITM_BLACK_PAINT 0x2236
#define ITM_WHITE_PAINT 0x2237
#define ITM_BROWN_PAINT 0x2238
#define ITM_GOLDEN_NET 0x2239
#define ITM_GOLDEN_AXE 0x223A
#define ITM_GOLDEN_SHOVEL 0x223B
#define ITM_GOLDEN_ROD 0x223C
#define ITM_AXE_USE_1 0x223D
#define ITM_AXE_USE_2 0x223E
#define ITM_AXE_USE_3 0x223F
#define ITM_AXE_USE_4 0x2240
#define ITM_AXE_USE_5 0x2241
#define ITM_AXE_USE_6 0x2242
#define ITM_AXE_USE_7 0x2243
#define ITM_BALLOON_START (ITM_TOOL_START + 68)
#define ITM_RED_BALLOON 0x2244
#define ITM_YELLOW_BALLOON 0x2245
#define ITM_BLUE_BALLOON 0x2246
#define ITM_GREEN_BALLOON 0x2247
#define ITM_PURPLE_BALLOON 0x2248
#define ITM_BUNNY_P_BALLOON 0x2249
#define ITM_BUNNY_B_BALLOON 0x224A
#define ITM_BUNNY_O_BALLOON 0x224B
#define ITM_YELLOW_PINWHEEL 0x224C
#define ITM_RED_PINWHEEL 0x224D
#define ITM_TIGER_PINWHEEL 0x224E
#define ITM_GREEN_PINWHEEL 0x224F
#define ITM_PINK_PINWHEEL 0x2250
#define ITM_STRIPED_PINWHEEL 0x2251
#define ITM_FLOWER_PINWHEEL 0x2252
#define ITM_FANCY_PINWHEEL 0x2253
#define ITM_BLUEBELL_FAN 0x2254
#define ITM_PLUM_FAN 0x2255
#define ITM_BAMBOO_FAN 0x2256
#define ITM_CLOUD_FAN 0x2257
#define ITM_MAPLE_FAN 0x2258
#define ITM_FAN_FAN 0x2259
#define ITM_FLOWER_FAN 0x225A
#define ITM_LEAF_FAN 0x225B
#define ITM_TOOL_END (ITM_LEAF_FAN + 1)

#define ITM_FISH_START 0x2300
#define ITM_FISH00 (ITM_FISH_START + 0)
#define ITM_FISH01 (ITM_FISH_START + 1)
#define ITM_FISH02 (ITM_FISH_START + 2)
#define ITM_FISH03 (ITM_FISH_START + 3)
#define ITM_FISH04 (ITM_FISH_START + 4)
#define ITM_FISH05 (ITM_FISH_START + 5)
#define ITM_FISH06 (ITM_FISH_START + 6)
#define ITM_FISH07 (ITM_FISH_START + 7)
#define ITM_FISH08 (ITM_FISH_START + 8)
#define ITM_FISH09 (ITM_FISH_START + 9)
#define ITM_FISH10 (ITM_FISH_START + 10)
#define ITM_FISH11 (ITM_FISH_START + 11)
#define ITM_FISH12 (ITM_FISH_START + 12)
#define ITM_FISH13 (ITM_FISH_START + 13)
#define ITM_FISH14 (ITM_FISH_START + 14)
#define ITM_FISH15 (ITM_FISH_START + 15)
#define ITM_FISH16 (ITM_FISH_START + 16)
#define ITM_FISH17 (ITM_FISH_START + 17)
#define ITM_FISH18 (ITM_FISH_START + 18)
#define ITM_FISH19 (ITM_FISH_START + 19)
#define ITM_FISH20 (ITM_FISH_START + 20)
#define ITM_FISH21 (ITM_FISH_START + 21)
#define ITM_FISH22 (ITM_FISH_START + 22)
#define ITM_FISH23 (ITM_FISH_START + 23)
#define ITM_FISH24 (ITM_FISH_START + 24)
#define ITM_FISH25 (ITM_FISH_START + 25)
#define ITM_FISH26 (ITM_FISH_START + 26)
#define ITM_FISH27 (ITM_FISH_START + 27)
#define ITM_FISH28 (ITM_FISH_START + 28)
#define ITM_FISH29 (ITM_FISH_START + 29)
#define ITM_FISH30 (ITM_FISH_START + 30)
#define ITM_FISH31 (ITM_FISH_START + 31)
#define ITM_FISH32 (ITM_FISH_START + 32)
#define ITM_FISH33 (ITM_FISH_START + 33)
#define ITM_FISH34 (ITM_FISH_START + 34)
#define ITM_FISH35 (ITM_FISH_START + 35)
#define ITM_FISH36 (ITM_FISH_START + 36)
#define ITM_FISH37 (ITM_FISH_START + 37)
#define ITM_FISH38 (ITM_FISH_START + 38)
#define ITM_FISH39 (ITM_FISH_START + 39)
#define ITM_FISH_END (ITM_FISH_START + 40)

#define ITM_CLOTH_START 0x2400
#define ITM_CLOTH000 (ITM_CLOTH_START +   0)
#define ITM_CLOTH001 (ITM_CLOTH_START +   1)
#define ITM_CLOTH002 (ITM_CLOTH_START +   2)
#define ITM_CLOTH003 (ITM_CLOTH_START +   3)
#define ITM_CLOTH004 (ITM_CLOTH_START +   4)
#define ITM_CLOTH005 (ITM_CLOTH_START +   5)
#define ITM_CLOTH006 (ITM_CLOTH_START +   6)
#define ITM_CLOTH007 (ITM_CLOTH_START +   7)
#define ITM_CLOTH008 (ITM_CLOTH_START +   8)
#define ITM_CLOTH009 (ITM_CLOTH_START +   9)
#define ITM_CLOTH010 (ITM_CLOTH_START +  10)
#define ITM_CLOTH011 (ITM_CLOTH_START +  11)
#define ITM_CLOTH012 (ITM_CLOTH_START +  12)
#define ITM_CLOTH013 (ITM_CLOTH_START +  13)
#define ITM_CLOTH014 (ITM_CLOTH_START +  14)
#define ITM_CLOTH015 (ITM_CLOTH_START +  15)
#define ITM_CLOTH016 (ITM_CLOTH_START +  16)
#define ITM_CLOTH017 (ITM_CLOTH_START +  17)
#define ITM_CLOTH018 (ITM_CLOTH_START +  18)
#define ITM_CLOTH019 (ITM_CLOTH_START +  19)
#define ITM_CLOTH020 (ITM_CLOTH_START +  20)
#define ITM_CLOTH021 (ITM_CLOTH_START +  21)
#define ITM_CLOTH022 (ITM_CLOTH_START +  22)
#define ITM_CLOTH023 (ITM_CLOTH_START +  23)
#define ITM_CLOTH024 (ITM_CLOTH_START +  24)
#define ITM_CLOTH025 (ITM_CLOTH_START +  25)
#define ITM_CLOTH026 (ITM_CLOTH_START +  26)
#define ITM_CLOTH027 (ITM_CLOTH_START +  27)
#define ITM_CLOTH028 (ITM_CLOTH_START +  28)
#define ITM_CLOTH029 (ITM_CLOTH_START +  29)
#define ITM_CLOTH030 (ITM_CLOTH_START +  30)
#define ITM_CLOTH031 (ITM_CLOTH_START +  31)
#define ITM_CLOTH032 (ITM_CLOTH_START +  32)
#define ITM_CLOTH033 (ITM_CLOTH_START +  33)
#define ITM_CLOTH034 (ITM_CLOTH_START +  34)
#define ITM_CLOTH035 (ITM_CLOTH_START +  35)
#define ITM_CLOTH036 (ITM_CLOTH_START +  36)
#define ITM_CLOTH037 (ITM_CLOTH_START +  37)
#define ITM_CLOTH038 (ITM_CLOTH_START +  38)
#define ITM_CLOTH039 (ITM_CLOTH_START +  39)
#define ITM_CLOTH040 (ITM_CLOTH_START +  40)
#define ITM_CLOTH041 (ITM_CLOTH_START +  41)
#define ITM_CLOTH042 (ITM_CLOTH_START +  42)
#define ITM_CLOTH043 (ITM_CLOTH_START +  43)
#define ITM_CLOTH044 (ITM_CLOTH_START +  44)
#define ITM_CLOTH045 (ITM_CLOTH_START +  45)
#define ITM_CLOTH046 (ITM_CLOTH_START +  46)
#define ITM_CLOTH047 (ITM_CLOTH_START +  47)
#define ITM_CLOTH048 (ITM_CLOTH_START +  48)
#define ITM_CLOTH049 (ITM_CLOTH_START +  49)
#define ITM_CLOTH050 (ITM_CLOTH_START +  50)
#define ITM_CLOTH051 (ITM_CLOTH_START +  51)
#define ITM_CLOTH052 (ITM_CLOTH_START +  52)
#define ITM_CLOTH053 (ITM_CLOTH_START +  53)
#define ITM_CLOTH054 (ITM_CLOTH_START +  54)
#define ITM_CLOTH055 (ITM_CLOTH_START +  55)
#define ITM_CLOTH056 (ITM_CLOTH_START +  56)
#define ITM_CLOTH057 (ITM_CLOTH_START +  57)
#define ITM_CLOTH058 (ITM_CLOTH_START +  58)
#define ITM_CLOTH059 (ITM_CLOTH_START +  59)
#define ITM_CLOTH060 (ITM_CLOTH_START +  60)
#define ITM_CLOTH061 (ITM_CLOTH_START +  61)
#define ITM_CLOTH062 (ITM_CLOTH_START +  62)
#define ITM_CLOTH063 (ITM_CLOTH_START +  63)
#define ITM_CLOTH064 (ITM_CLOTH_START +  64)
#define ITM_CLOTH065 (ITM_CLOTH_START +  65)
#define ITM_CLOTH066 (ITM_CLOTH_START +  66)
#define ITM_CLOTH067 (ITM_CLOTH_START +  67)
#define ITM_CLOTH068 (ITM_CLOTH_START +  68)
#define ITM_CLOTH069 (ITM_CLOTH_START +  69)
#define ITM_CLOTH070 (ITM_CLOTH_START +  70)
#define ITM_CLOTH071 (ITM_CLOTH_START +  71)
#define ITM_CLOTH072 (ITM_CLOTH_START +  72)
#define ITM_CLOTH073 (ITM_CLOTH_START +  73)
#define ITM_CLOTH074 (ITM_CLOTH_START +  74)
#define ITM_CLOTH075 (ITM_CLOTH_START +  75)
#define ITM_CLOTH076 (ITM_CLOTH_START +  76)
#define ITM_CLOTH077 (ITM_CLOTH_START +  77)
#define ITM_CLOTH078 (ITM_CLOTH_START +  78)
#define ITM_CLOTH079 (ITM_CLOTH_START +  79)
#define ITM_CLOTH080 (ITM_CLOTH_START +  80)
#define ITM_CLOTH081 (ITM_CLOTH_START +  81)
#define ITM_CLOTH082 (ITM_CLOTH_START +  82)
#define ITM_CLOTH083 (ITM_CLOTH_START +  83)
#define ITM_CLOTH084 (ITM_CLOTH_START +  84)
#define ITM_CLOTH085 (ITM_CLOTH_START +  85)
#define ITM_CLOTH086 (ITM_CLOTH_START +  86)
#define ITM_CLOTH087 (ITM_CLOTH_START +  87)
#define ITM_CLOTH088 (ITM_CLOTH_START +  88)
#define ITM_CLOTH089 (ITM_CLOTH_START +  89)
#define ITM_CLOTH090 (ITM_CLOTH_START +  90)
#define ITM_CLOTH091 (ITM_CLOTH_START +  91)
#define ITM_CLOTH092 (ITM_CLOTH_START +  92)
#define ITM_CLOTH093 (ITM_CLOTH_START +  93)
#define ITM_CLOTH094 (ITM_CLOTH_START +  94)
#define ITM_CLOTH095 (ITM_CLOTH_START +  95)
#define ITM_CLOTH096 (ITM_CLOTH_START +  96)
#define ITM_CLOTH097 (ITM_CLOTH_START +  97)
#define ITM_CLOTH098 (ITM_CLOTH_START +  98)
#define ITM_CLOTH099 (ITM_CLOTH_START +  99)
#define ITM_CLOTH100 (ITM_CLOTH_START + 100)
#define ITM_CLOTH101 (ITM_CLOTH_START + 101)
#define ITM_CLOTH102 (ITM_CLOTH_START + 102)
#define ITM_CLOTH103 (ITM_CLOTH_START + 103)
#define ITM_CLOTH104 (ITM_CLOTH_START + 104)
#define ITM_CLOTH105 (ITM_CLOTH_START + 105)
#define ITM_CLOTH106 (ITM_CLOTH_START + 106)
#define ITM_CLOTH107 (ITM_CLOTH_START + 107)
#define ITM_CLOTH108 (ITM_CLOTH_START + 108)
#define ITM_CLOTH109 (ITM_CLOTH_START + 109)
#define ITM_CLOTH110 (ITM_CLOTH_START + 110)
#define ITM_CLOTH111 (ITM_CLOTH_START + 111)
#define ITM_CLOTH112 (ITM_CLOTH_START + 112)
#define ITM_CLOTH113 (ITM_CLOTH_START + 113)
#define ITM_CLOTH114 (ITM_CLOTH_START + 114)
#define ITM_CLOTH115 (ITM_CLOTH_START + 115)
#define ITM_CLOTH116 (ITM_CLOTH_START + 116)
#define ITM_CLOTH117 (ITM_CLOTH_START + 117)
#define ITM_CLOTH118 (ITM_CLOTH_START + 118)
#define ITM_CLOTH119 (ITM_CLOTH_START + 119)
#define ITM_CLOTH120 (ITM_CLOTH_START + 120)
#define ITM_CLOTH121 (ITM_CLOTH_START + 121)
#define ITM_CLOTH122 (ITM_CLOTH_START + 122)
#define ITM_CLOTH123 (ITM_CLOTH_START + 123)
#define ITM_CLOTH124 (ITM_CLOTH_START + 124)
#define ITM_CLOTH125 (ITM_CLOTH_START + 125)
#define ITM_CLOTH126 (ITM_CLOTH_START + 126)
#define ITM_CLOTH127 (ITM_CLOTH_START + 127)
#define ITM_CLOTH128 (ITM_CLOTH_START + 128)
#define ITM_CLOTH129 (ITM_CLOTH_START + 129)
#define ITM_CLOTH130 (ITM_CLOTH_START + 130)
#define ITM_CLOTH131 (ITM_CLOTH_START + 131)
#define ITM_CLOTH132 (ITM_CLOTH_START + 132)
#define ITM_CLOTH133 (ITM_CLOTH_START + 133)
#define ITM_CLOTH134 (ITM_CLOTH_START + 134)
#define ITM_CLOTH135 (ITM_CLOTH_START + 135)
#define ITM_CLOTH136 (ITM_CLOTH_START + 136)
#define ITM_CLOTH137 (ITM_CLOTH_START + 137)
#define ITM_CLOTH138 (ITM_CLOTH_START + 138)
#define ITM_CLOTH139 (ITM_CLOTH_START + 139)
#define ITM_CLOTH140 (ITM_CLOTH_START + 140)
#define ITM_CLOTH141 (ITM_CLOTH_START + 141)
#define ITM_CLOTH142 (ITM_CLOTH_START + 142)
#define ITM_CLOTH143 (ITM_CLOTH_START + 143)
#define ITM_CLOTH144 (ITM_CLOTH_START + 144)
#define ITM_CLOTH145 (ITM_CLOTH_START + 145)
#define ITM_CLOTH146 (ITM_CLOTH_START + 146)
#define ITM_CLOTH147 (ITM_CLOTH_START + 147)
#define ITM_CLOTH148 (ITM_CLOTH_START + 148)
#define ITM_CLOTH149 (ITM_CLOTH_START + 149)
#define ITM_CLOTH150 (ITM_CLOTH_START + 150)
#define ITM_CLOTH151 (ITM_CLOTH_START + 151)
#define ITM_CLOTH152 (ITM_CLOTH_START + 152)
#define ITM_CLOTH153 (ITM_CLOTH_START + 153)
#define ITM_CLOTH154 (ITM_CLOTH_START + 154)
#define ITM_CLOTH155 (ITM_CLOTH_START + 155)
#define ITM_CLOTH156 (ITM_CLOTH_START + 156)
#define ITM_CLOTH157 (ITM_CLOTH_START + 157)
#define ITM_CLOTH158 (ITM_CLOTH_START + 158)
#define ITM_CLOTH159 (ITM_CLOTH_START + 159)
#define ITM_CLOTH160 (ITM_CLOTH_START + 160)
#define ITM_CLOTH161 (ITM_CLOTH_START + 161)
#define ITM_CLOTH162 (ITM_CLOTH_START + 162)
#define ITM_CLOTH163 (ITM_CLOTH_START + 163)
#define ITM_CLOTH164 (ITM_CLOTH_START + 164)
#define ITM_CLOTH165 (ITM_CLOTH_START + 165)
#define ITM_CLOTH166 (ITM_CLOTH_START + 166)
#define ITM_CLOTH167 (ITM_CLOTH_START + 167)
#define ITM_CLOTH168 (ITM_CLOTH_START + 168)
#define ITM_CLOTH169 (ITM_CLOTH_START + 169)
#define ITM_CLOTH170 (ITM_CLOTH_START + 170)
#define ITM_CLOTH171 (ITM_CLOTH_START + 171)
#define ITM_CLOTH172 (ITM_CLOTH_START + 172)
#define ITM_CLOTH173 (ITM_CLOTH_START + 173)
#define ITM_CLOTH174 (ITM_CLOTH_START + 174)
#define ITM_CLOTH175 (ITM_CLOTH_START + 175)
#define ITM_CLOTH176 (ITM_CLOTH_START + 176)
#define ITM_CLOTH177 (ITM_CLOTH_START + 177)
#define ITM_CLOTH178 (ITM_CLOTH_START + 178)
#define ITM_CLOTH179 (ITM_CLOTH_START + 179)
#define ITM_CLOTH180 (ITM_CLOTH_START + 180)
#define ITM_CLOTH181 (ITM_CLOTH_START + 181)
#define ITM_CLOTH182 (ITM_CLOTH_START + 182)
#define ITM_CLOTH183 (ITM_CLOTH_START + 183)
#define ITM_CLOTH184 (ITM_CLOTH_START + 184)
#define ITM_CLOTH185 (ITM_CLOTH_START + 185)
#define ITM_CLOTH186 (ITM_CLOTH_START + 186)
#define ITM_CLOTH187 (ITM_CLOTH_START + 187)
#define ITM_CLOTH188 (ITM_CLOTH_START + 188)
#define ITM_CLOTH189 (ITM_CLOTH_START + 189)
#define ITM_CLOTH190 (ITM_CLOTH_START + 190)
#define ITM_CLOTH191 (ITM_CLOTH_START + 191)
#define ITM_CLOTH192 (ITM_CLOTH_START + 192)
#define ITM_CLOTH193 (ITM_CLOTH_START + 193)
#define ITM_CLOTH194 (ITM_CLOTH_START + 194)
#define ITM_CLOTH195 (ITM_CLOTH_START + 195)
#define ITM_CLOTH196 (ITM_CLOTH_START + 196)
#define ITM_CLOTH197 (ITM_CLOTH_START + 197)
#define ITM_CLOTH198 (ITM_CLOTH_START + 198)
#define ITM_CLOTH199 (ITM_CLOTH_START + 199)
#define ITM_CLOTH200 (ITM_CLOTH_START + 200)
#define ITM_CLOTH201 (ITM_CLOTH_START + 201)
#define ITM_CLOTH202 (ITM_CLOTH_START + 202)
#define ITM_CLOTH203 (ITM_CLOTH_START + 203)
#define ITM_CLOTH204 (ITM_CLOTH_START + 204)
#define ITM_CLOTH205 (ITM_CLOTH_START + 205)
#define ITM_CLOTH206 (ITM_CLOTH_START + 206)
#define ITM_CLOTH207 (ITM_CLOTH_START + 207)
#define ITM_CLOTH208 (ITM_CLOTH_START + 208)
#define ITM_CLOTH209 (ITM_CLOTH_START + 209)
#define ITM_CLOTH210 (ITM_CLOTH_START + 210)
#define ITM_CLOTH211 (ITM_CLOTH_START + 211)
#define ITM_CLOTH212 (ITM_CLOTH_START + 212)
#define ITM_CLOTH213 (ITM_CLOTH_START + 213)
#define ITM_CLOTH214 (ITM_CLOTH_START + 214)
#define ITM_CLOTH215 (ITM_CLOTH_START + 215)
#define ITM_CLOTH216 (ITM_CLOTH_START + 216)
#define ITM_CLOTH217 (ITM_CLOTH_START + 217)
#define ITM_CLOTH218 (ITM_CLOTH_START + 218)
#define ITM_CLOTH219 (ITM_CLOTH_START + 219)
#define ITM_CLOTH220 (ITM_CLOTH_START + 220)
#define ITM_CLOTH221 (ITM_CLOTH_START + 221)
#define ITM_CLOTH222 (ITM_CLOTH_START + 222)
#define ITM_CLOTH223 (ITM_CLOTH_START + 223)
#define ITM_CLOTH224 (ITM_CLOTH_START + 224)
#define ITM_CLOTH225 (ITM_CLOTH_START + 225)
#define ITM_CLOTH226 (ITM_CLOTH_START + 226)
#define ITM_CLOTH227 (ITM_CLOTH_START + 227)
#define ITM_CLOTH228 (ITM_CLOTH_START + 228)
#define ITM_CLOTH229 (ITM_CLOTH_START + 229)
#define ITM_CLOTH230 (ITM_CLOTH_START + 230)
#define ITM_CLOTH231 (ITM_CLOTH_START + 231)
#define ITM_CLOTH232 (ITM_CLOTH_START + 232)
#define ITM_CLOTH233 (ITM_CLOTH_START + 233)
#define ITM_CLOTH234 (ITM_CLOTH_START + 234)
#define ITM_CLOTH235 (ITM_CLOTH_START + 235)
#define ITM_CLOTH236 (ITM_CLOTH_START + 236)
#define ITM_CLOTH237 (ITM_CLOTH_START + 237)
#define ITM_CLOTH238 (ITM_CLOTH_START + 238)
#define ITM_CLOTH239 (ITM_CLOTH_START + 239)
#define ITM_CLOTH240 (ITM_CLOTH_START + 240)
#define ITM_CLOTH241 (ITM_CLOTH_START + 241)
#define ITM_CLOTH242 (ITM_CLOTH_START + 242)
#define ITM_CLOTH243 (ITM_CLOTH_START + 243)
#define ITM_CLOTH244 (ITM_CLOTH_START + 244)
#define ITM_CLOTH245 (ITM_CLOTH_START + 245)
#define ITM_CLOTH246 (ITM_CLOTH_START + 246)
#define ITM_CLOTH247 (ITM_CLOTH_START + 247)
#define ITM_CLOTH248 (ITM_CLOTH_START + 248)
#define ITM_CLOTH249 (ITM_CLOTH_START + 249)
#define ITM_CLOTH250 (ITM_CLOTH_START + 250)
#define ITM_CLOTH251 (ITM_CLOTH_START + 251)
#define ITM_CLOTH252 (ITM_CLOTH_START + 252)
#define ITM_CLOTH253 (ITM_CLOTH_START + 253)
#define ITM_CLOTH254 (ITM_CLOTH_START + 254)
#define ITM_CLOTH_MANEKIN (ITM_CLOTH_START + 255)
#define ITM_CLOTH_END (ITM_CLOTH_START + 255)

#define ITM_ETC_START 0x2500
#define ITM_QST_LETTER (ITM_ETC_START + 0)
#define ITM_QST_CLOTH (ITM_ETC_START + 1)
#define ITM_QST_MONEY (ITM_ETC_START + 2)
#define ITM_QST_VIDEOTAPE (ITM_ETC_START + 3)
#define ITM_QST_ORGANIZER (ITM_ETC_START + 4)
#define ITM_QST_POKEMON_PIKACHU (ITM_ETC_START + 5)
#define ITM_QST_COMIC_BOOK (ITM_ETC_START + 6)
#define ITM_QST_PICTURE_BOOK (ITM_ETC_START + 7)
#define ITM_QST_GAME_BOY (ITM_ETC_START + 8)
#define ITM_QST_CAMREA (ITM_ETC_START + 9)
#define ITM_QST_WATCH (ITM_ETC_START + 10)
#define ITM_QST_HANDKERCHIEF (ITM_ETC_START + 11)
#define ITM_QST_GLASSES_CASE (ITM_ETC_START + 12)
#define ITM_MONEY1000BELL (ITM_ETC_START + 13)
#define ITM_DUST0_EMPTY_CAN (ITM_ETC_START + 14)
#define ITM_DUST1_BOOT (ITM_ETC_START + 15)
#define ITM_DUST2_OLD_TIRE (ITM_ETC_START + 16)
#define ITM_FOSSIL (ITM_ETC_START + 17)
#define ITM_PITFALL (ITM_ETC_START + 18)
#define ITM_FORTUNE_SLIP (ITM_ETC_START + 19)
#define ITM_SHELL_START (ITM_ETC_START + 20)
#define ITM_SHELL0 (ITM_ETC_START + 20)
#define ITM_SHELL1 (ITM_ETC_START + 21)
#define ITM_SHELL2 (ITM_ETC_START + 22)
#define ITM_SHELL3 (ITM_ETC_START + 23)
#define ITM_SHELL4 (ITM_ETC_START + 24)
#define ITM_SHELL5 (ITM_ETC_START + 25)
#define ITM_SHELL6 (ITM_ETC_START + 26)
#define ITM_SHELL7 (ITM_ETC_START + 27)
#define ITM_SHELL_END (ITM_ETC_START + 28)
#define ITM_PRESENT (ITM_ETC_START + 28)
#define ITM_TOWN_MAP (ITM_ETC_START + 29)
#define ITM_SIGNBOARD (ITM_ETC_START + 30)
#define ITM_GOLDEN_NET_PRESENT (ITM_ETC_START + 31)
#define ITM_GOLDEN_AXE_PRESENT (ITM_ETC_START + 32)
#define ITM_GOLDEN_SHOVEL_PRESENT (ITM_ETC_START + 33)
#define ITM_GOLDEN_ROD_PRESENT (ITM_ETC_START + 34)
#define ITM_EXCERCISE_CARD00 (ITM_ETC_START + 35)
#define ITM_EXCERCISE_CARD01 (ITM_ETC_START + 36)
#define ITM_EXCERCISE_CARD02 (ITM_ETC_START + 37)
#define ITM_EXCERCISE_CARD03 (ITM_ETC_START + 38)
#define ITM_EXCERCISE_CARD04 (ITM_ETC_START + 39)
#define ITM_EXCERCISE_CARD05 (ITM_ETC_START + 40)
#define ITM_EXCERCISE_CARD06 (ITM_ETC_START + 41)
#define ITM_EXCERCISE_CARD07 (ITM_ETC_START + 42)
#define ITM_EXCERCISE_CARD08 (ITM_ETC_START + 43)
#define ITM_EXCERCISE_CARD09 (ITM_ETC_START + 44)
#define ITM_EXCERCISE_CARD10 (ITM_ETC_START + 45)
#define ITM_EXCERCISE_CARD11 (ITM_ETC_START + 46)
#define ITM_EXCERCISE_CARD12 (ITM_ETC_START + 47)
#define ITM_KNIFE_AND_FORK (ITM_ETC_START + 48)
#define ITM_ETC_END 0x2531

#define ITM_CARPET_START 0x2600
#define ITM_CARPET00 (ITM_CARPET_START +  0)
#define ITM_CARPET01 (ITM_CARPET_START +  1)
#define ITM_CARPET02 (ITM_CARPET_START +  2)
#define ITM_CARPET03 (ITM_CARPET_START +  3)
#define ITM_CARPET04 (ITM_CARPET_START +  4)
#define ITM_CARPET05 (ITM_CARPET_START +  5)
#define ITM_CARPET06 (ITM_CARPET_START +  6)
#define ITM_CARPET07 (ITM_CARPET_START +  7)
#define ITM_CARPET08 (ITM_CARPET_START +  8)
#define ITM_CARPET09 (ITM_CARPET_START +  9)
#define ITM_CARPET10 (ITM_CARPET_START + 10)
#define ITM_CARPET11 (ITM_CARPET_START + 11)
#define ITM_CARPET12 (ITM_CARPET_START + 12)
#define ITM_CARPET13 (ITM_CARPET_START + 13)
#define ITM_CARPET14 (ITM_CARPET_START + 14)
#define ITM_CARPET15 (ITM_CARPET_START + 15)
#define ITM_CARPET16 (ITM_CARPET_START + 16)
#define ITM_CARPET17 (ITM_CARPET_START + 17)
#define ITM_CARPET18 (ITM_CARPET_START + 18)
#define ITM_CARPET19 (ITM_CARPET_START + 19)
#define ITM_CARPET20 (ITM_CARPET_START + 20)
#define ITM_CARPET21 (ITM_CARPET_START + 21)
#define ITM_CARPET22 (ITM_CARPET_START + 22)
#define ITM_CARPET23 (ITM_CARPET_START + 23)
#define ITM_CARPET24 (ITM_CARPET_START + 24)
#define ITM_CARPET25 (ITM_CARPET_START + 25)
#define ITM_CARPET26 (ITM_CARPET_START + 26)
#define ITM_CARPET27 (ITM_CARPET_START + 27)
#define ITM_CARPET28 (ITM_CARPET_START + 28)
#define ITM_CARPET29 (ITM_CARPET_START + 29)
#define ITM_CARPET30 (ITM_CARPET_START + 30)
#define ITM_CARPET31 (ITM_CARPET_START + 31)
#define ITM_CARPET32 (ITM_CARPET_START + 32)
#define ITM_CARPET33 (ITM_CARPET_START + 33)
#define ITM_CARPET34 (ITM_CARPET_START + 34)
#define ITM_CARPET35 (ITM_CARPET_START + 35)
#define ITM_CARPET36 (ITM_CARPET_START + 36)
#define ITM_CARPET37 (ITM_CARPET_START + 37)
#define ITM_CARPET38 (ITM_CARPET_START + 38)
#define ITM_CARPET39 (ITM_CARPET_START + 39)
#define ITM_CARPET40 (ITM_CARPET_START + 40)
#define ITM_CARPET41 (ITM_CARPET_START + 41)
#define ITM_CARPET42 (ITM_CARPET_START + 42)
#define ITM_CARPET43 (ITM_CARPET_START + 43)
#define ITM_CARPET44 (ITM_CARPET_START + 44)
#define ITM_CARPET45 (ITM_CARPET_START + 45)
#define ITM_CARPET46 (ITM_CARPET_START + 46)
#define ITM_CARPET47 (ITM_CARPET_START + 47)
#define ITM_CARPET48 (ITM_CARPET_START + 48)
#define ITM_CARPET49 (ITM_CARPET_START + 49)
#define ITM_CARPET50 (ITM_CARPET_START + 50)
#define ITM_CARPET51 (ITM_CARPET_START + 51)
#define ITM_CARPET52 (ITM_CARPET_START + 52)
#define ITM_CARPET53 (ITM_CARPET_START + 53)
#define ITM_CARPET54 (ITM_CARPET_START + 54)
#define ITM_CARPET55 (ITM_CARPET_START + 55)
#define ITM_CARPET56 (ITM_CARPET_START + 56)
#define ITM_CARPET57 (ITM_CARPET_START + 57)
#define ITM_CARPET58 (ITM_CARPET_START + 58)
#define ITM_CARPET59 (ITM_CARPET_START + 59)
#define ITM_CARPET60 (ITM_CARPET_START + 60)
#define ITM_CARPET61 (ITM_CARPET_START + 61)
#define ITM_CARPET62 (ITM_CARPET_START + 62)
#define ITM_CARPET63 (ITM_CARPET_START + 63)
#define ITM_CARPET64 (ITM_CARPET_START + 64)
#define ITM_CARPET65 (ITM_CARPET_START + 65)
#define ITM_CARPET66 (ITM_CARPET_START + 66)
#define ITM_CARPET67 (ITM_CARPET_START + 67)
#define ITM_CARPET68 (ITM_CARPET_START + 68)
#define ITM_CARPET69 (ITM_CARPET_START + 69)
#define ITM_CARPET70 (ITM_CARPET_START + 70)
#define ITM_CARPET_END (ITM_CARPET_START + 71)

#define ITM_WALL_START 0x2700
#define ITM_WALL00 (ITM_WALL_START +  0)
#define ITM_WALL01 (ITM_WALL_START +  1)
#define ITM_WALL02 (ITM_WALL_START +  2)
#define ITM_WALL03 (ITM_WALL_START +  3)
#define ITM_WALL04 (ITM_WALL_START +  4)
#define ITM_WALL05 (ITM_WALL_START +  5)
#define ITM_WALL06 (ITM_WALL_START +  6)
#define ITM_WALL07 (ITM_WALL_START +  7)
#define ITM_WALL08 (ITM_WALL_START +  8)
#define ITM_WALL09 (ITM_WALL_START +  9)
#define ITM_WALL10 (ITM_WALL_START + 10)
#define ITM_WALL11 (ITM_WALL_START + 11)
#define ITM_WALL12 (ITM_WALL_START + 12)
#define ITM_WALL13 (ITM_WALL_START + 13)
#define ITM_WALL14 (ITM_WALL_START + 14)
#define ITM_WALL15 (ITM_WALL_START + 15)
#define ITM_WALL16 (ITM_WALL_START + 16)
#define ITM_WALL17 (ITM_WALL_START + 17)
#define ITM_WALL18 (ITM_WALL_START + 18)
#define ITM_WALL19 (ITM_WALL_START + 19)
#define ITM_WALL20 (ITM_WALL_START + 20)
#define ITM_WALL21 (ITM_WALL_START + 21)
#define ITM_WALL22 (ITM_WALL_START + 22)
#define ITM_WALL23 (ITM_WALL_START + 23)
#define ITM_WALL24 (ITM_WALL_START + 24)
#define ITM_WALL25 (ITM_WALL_START + 25)
#define ITM_WALL26 (ITM_WALL_START + 26)
#define ITM_WALL27 (ITM_WALL_START + 27)
#define ITM_WALL28 (ITM_WALL_START + 28)
#define ITM_WALL29 (ITM_WALL_START + 29)
#define ITM_WALL30 (ITM_WALL_START + 30)
#define ITM_WALL31 (ITM_WALL_START + 31)
#define ITM_WALL32 (ITM_WALL_START + 32)
#define ITM_WALL33 (ITM_WALL_START + 33)
#define ITM_WALL34 (ITM_WALL_START + 34)
#define ITM_WALL35 (ITM_WALL_START + 35)
#define ITM_WALL36 (ITM_WALL_START + 36)
#define ITM_WALL37 (ITM_WALL_START + 37)
#define ITM_WALL38 (ITM_WALL_START + 38)
#define ITM_WALL39 (ITM_WALL_START + 39)
#define ITM_WALL40 (ITM_WALL_START + 40)
#define ITM_WALL41 (ITM_WALL_START + 41)
#define ITM_WALL42 (ITM_WALL_START + 42)
#define ITM_WALL43 (ITM_WALL_START + 43)
#define ITM_WALL44 (ITM_WALL_START + 44)
#define ITM_WALL45 (ITM_WALL_START + 45)
#define ITM_WALL46 (ITM_WALL_START + 46)
#define ITM_WALL47 (ITM_WALL_START + 47)
#define ITM_WALL48 (ITM_WALL_START + 48)
#define ITM_WALL49 (ITM_WALL_START + 49)
#define ITM_WALL50 (ITM_WALL_START + 50)
#define ITM_WALL51 (ITM_WALL_START + 51)
#define ITM_WALL52 (ITM_WALL_START + 52)
#define ITM_WALL53 (ITM_WALL_START + 53)
#define ITM_WALL54 (ITM_WALL_START + 54)
#define ITM_WALL55 (ITM_WALL_START + 55)
#define ITM_WALL56 (ITM_WALL_START + 56)
#define ITM_WALL57 (ITM_WALL_START + 57)
#define ITM_WALL58 (ITM_WALL_START + 58)
#define ITM_WALL59 (ITM_WALL_START + 59)
#define ITM_WALL60 (ITM_WALL_START + 60)
#define ITM_WALL61 (ITM_WALL_START + 61)
#define ITM_WALL62 (ITM_WALL_START + 62)
#define ITM_WALL63 (ITM_WALL_START + 63)
#define ITM_WALL64 (ITM_WALL_START + 64)
#define ITM_WALL65 (ITM_WALL_START + 65)
#define ITM_WALL66 (ITM_WALL_START + 66)
#define ITM_WALL67 (ITM_WALL_START + 67)
#define ITM_WALL68 (ITM_WALL_START + 68)
#define ITM_WALL69 (ITM_WALL_START + 69)
#define ITM_WALL70 (ITM_WALL_START + 70)
#define ITM_WALL_END (ITM_WALL_START + 71)

#define ITM_FOOD_START 0x2800
#define ITM_FOOD_APPLE (ITM_FOOD_START + 0)
#define ITM_FOOD_CHERRY (ITM_FOOD_START + 1)
#define ITM_FOOD_PEAR (ITM_FOOD_START + 2)
#define ITM_FOOD_PEACH (ITM_FOOD_START + 3)
#define ITM_FOOD_ORANGE (ITM_FOOD_START + 4)
#define ITM_FOOD_MUSHROOM (ITM_FOOD_START + 5)
#define ITM_FOOD_CANDY (ITM_FOOD_START + 6)
#define ITM_FOOD_COCONUT (ITM_FOOD_START + 7)
#define ITM_FOOD_END (ITM_FOOD_START + 8)

#define ITM_ENV_START 0x2900
#define ITM_SAPLING ITM_ENV_START
#define ITM_CEDAR_SAPLING 0x2901
#define ITM_WHITE_PANSY_BAG 0x2902
#define ITM_PURPLE_PANSY_BAG 0x2903
#define ITM_YELLOW_PANSY_BAG 0x2904
#define ITM_WHITE_COSMOS_BAG 0x2905
#define ITM_PINK_COSMOS_BAG 0x2906
#define ITM_BLUE_COSMOS_BAG 0x2907
#define ITM_RED_TULIP_BAG 0x2908
#define ITM_WHITE_TULIP_BAG 0x2909
#define ITM_YELLOW_TULIP_BAG 0x290A

#define ITM_MINIDISK_START 0x2A00
#define ITM_MINIDISK00 (ITM_MINIDISK_START + 0)
#define ITM_MINIDISK01 (ITM_MINIDISK_START + 1)
#define ITM_MINIDISK02 (ITM_MINIDISK_START + 2)
#define ITM_MINIDISK03 (ITM_MINIDISK_START + 3)
#define ITM_MINIDISK04 (ITM_MINIDISK_START + 4)
#define ITM_MINIDISK05 (ITM_MINIDISK_START + 5)
#define ITM_MINIDISK06 (ITM_MINIDISK_START + 6)
#define ITM_MINIDISK07 (ITM_MINIDISK_START + 7)
#define ITM_MINIDISK08 (ITM_MINIDISK_START + 8)
#define ITM_MINIDISK09 (ITM_MINIDISK_START + 9)
#define ITM_MINIDISK10 (ITM_MINIDISK_START + 10)
#define ITM_MINIDISK11 (ITM_MINIDISK_START + 11)
#define ITM_MINIDISK12 (ITM_MINIDISK_START + 12)
#define ITM_MINIDISK13 (ITM_MINIDISK_START + 13)
#define ITM_MINIDISK14 (ITM_MINIDISK_START + 14)
#define ITM_MINIDISK15 (ITM_MINIDISK_START + 15)
#define ITM_MINIDISK16 (ITM_MINIDISK_START + 16)
#define ITM_MINIDISK17 (ITM_MINIDISK_START + 17)
#define ITM_MINIDISK18 (ITM_MINIDISK_START + 18)
#define ITM_MINIDISK19 (ITM_MINIDISK_START + 19)
#define ITM_MINIDISK20 (ITM_MINIDISK_START + 20)
#define ITM_MINIDISK21 (ITM_MINIDISK_START + 21)
#define ITM_MINIDISK22 (ITM_MINIDISK_START + 22)
#define ITM_MINIDISK23 (ITM_MINIDISK_START + 23)
#define ITM_MINIDISK24 (ITM_MINIDISK_START + 24)
#define ITM_MINIDISK25 (ITM_MINIDISK_START + 25)
#define ITM_MINIDISK26 (ITM_MINIDISK_START + 26)
#define ITM_MINIDISK27 (ITM_MINIDISK_START + 27)
#define ITM_MINIDISK28 (ITM_MINIDISK_START + 28)
#define ITM_MINIDISK29 (ITM_MINIDISK_START + 29)
#define ITM_MINIDISK30 (ITM_MINIDISK_START + 30)
#define ITM_MINIDISK31 (ITM_MINIDISK_START + 31)
#define ITM_MINIDISK32 (ITM_MINIDISK_START + 32)
#define ITM_MINIDISK33 (ITM_MINIDISK_START + 33)
#define ITM_MINIDISK34 (ITM_MINIDISK_START + 34)
#define ITM_MINIDISK35 (ITM_MINIDISK_START + 35)
#define ITM_MINIDISK36 (ITM_MINIDISK_START + 36)
#define ITM_MINIDISK37 (ITM_MINIDISK_START + 37)
#define ITM_MINIDISK38 (ITM_MINIDISK_START + 38)
#define ITM_MINIDISK39 (ITM_MINIDISK_START + 39)
#define ITM_MINIDISK40 (ITM_MINIDISK_START + 40)
#define ITM_MINIDISK41 (ITM_MINIDISK_START + 41)
#define ITM_MINIDISK42 (ITM_MINIDISK_START + 42)
#define ITM_MINIDISK43 (ITM_MINIDISK_START + 43)
#define ITM_MINIDISK44 (ITM_MINIDISK_START + 44)
#define ITM_MINIDISK45 (ITM_MINIDISK_START + 45)
#define ITM_MINIDISK46 (ITM_MINIDISK_START + 46)
#define ITM_MINIDISK47 (ITM_MINIDISK_START + 47)
#define ITM_MINIDISK48 (ITM_MINIDISK_START + 48)
#define ITM_MINIDISK49 (ITM_MINIDISK_START + 49)
#define ITM_MINIDISK50 (ITM_MINIDISK_START + 50)
#define ITM_MINIDISK51 (ITM_MINIDISK_START + 51)
#define ITM_MINIDISK52 (ITM_MINIDISK_START + 52)
#define ITM_MINIDISK53 (ITM_MINIDISK_START + 53)
#define ITM_MINIDISK54 (ITM_MINIDISK_START + 54)
#define ITM_MINIDISK_END (ITM_MINIDISK_START + 55)

#define ITM_DIARY_START 0x2B00
#define ITM_DIARY00 (ITM_DIARY_START +  0)
#define ITM_DIARY01 (ITM_DIARY_START +  1)
#define ITM_DIARY02 (ITM_DIARY_START +  2)
#define ITM_DIARY03 (ITM_DIARY_START +  3)
#define ITM_DIARY04 (ITM_DIARY_START +  4)
#define ITM_DIARY05 (ITM_DIARY_START +  5)
#define ITM_DIARY06 (ITM_DIARY_START +  6)
#define ITM_DIARY07 (ITM_DIARY_START +  7)
#define ITM_DIARY08 (ITM_DIARY_START +  8)
#define ITM_DIARY09 (ITM_DIARY_START +  9)
#define ITM_DIARY10 (ITM_DIARY_START + 10)
#define ITM_DIARY11 (ITM_DIARY_START + 11)
#define ITM_DIARY12 (ITM_DIARY_START + 12)
#define ITM_DIARY13 (ITM_DIARY_START + 13)
#define ITM_DIARY14 (ITM_DIARY_START + 14)
#define ITM_DIARY15 (ITM_DIARY_START + 15)
#define ITM_DIARY_END (ITM_DIARY_START + 16)

#define ITM_TICKET_START 0x2C00
#define ITM_TICKET_END (ITM_TICKET_START + 95)

#define ITM_INSECT_START 0x2D00
#define ITM_INSECT00 (ITM_INSECT_START + 0)
#define ITM_INSECT01 (ITM_INSECT_START + 1)
#define ITM_INSECT02 (ITM_INSECT_START + 2)
#define ITM_INSECT03 (ITM_INSECT_START + 3)
#define ITM_INSECT04 (ITM_INSECT_START + 4)
#define ITM_INSECT05 (ITM_INSECT_START + 5)
#define ITM_INSECT06 (ITM_INSECT_START + 6)
#define ITM_INSECT07 (ITM_INSECT_START + 7)
#define ITM_INSECT08 (ITM_INSECT_START + 8)
#define ITM_INSECT09 (ITM_INSECT_START + 9)
#define ITM_INSECT10 (ITM_INSECT_START + 10)
#define ITM_INSECT11 (ITM_INSECT_START + 11)
#define ITM_INSECT12 (ITM_INSECT_START + 12)
#define ITM_INSECT13 (ITM_INSECT_START + 13)
#define ITM_INSECT14 (ITM_INSECT_START + 14)
#define ITM_INSECT15 (ITM_INSECT_START + 15)
#define ITM_INSECT16 (ITM_INSECT_START + 16)
#define ITM_INSECT17 (ITM_INSECT_START + 17)
#define ITM_INSECT18 (ITM_INSECT_START + 18)
#define ITM_INSECT19 (ITM_INSECT_START + 19)
#define ITM_INSECT20 (ITM_INSECT_START + 20)
#define ITM_INSECT21 (ITM_INSECT_START + 21)
#define ITM_INSECT22 (ITM_INSECT_START + 22)
#define ITM_INSECT23 (ITM_INSECT_START + 23)
#define ITM_INSECT24 (ITM_INSECT_START + 24)
#define ITM_INSECT25 (ITM_INSECT_START + 25)
#define ITM_INSECT26 (ITM_INSECT_START + 26)
#define ITM_INSECT27 (ITM_INSECT_START + 27)
#define ITM_INSECT28 (ITM_INSECT_START + 28)
#define ITM_INSECT29 (ITM_INSECT_START + 29)
#define ITM_INSECT30 (ITM_INSECT_START + 30)
#define ITM_INSECT31 (ITM_INSECT_START + 31)
#define ITM_INSECT32 (ITM_INSECT_START + 32)
#define ITM_INSECT33 (ITM_INSECT_START + 33)
#define ITM_INSECT34 (ITM_INSECT_START + 34)
#define ITM_INSECT35 (ITM_INSECT_START + 35)
#define ITM_INSECT36 (ITM_INSECT_START + 36)
#define ITM_INSECT37 (ITM_INSECT_START + 37)
#define ITM_INSECT38 (ITM_INSECT_START + 38)
#define ITM_INSECT39 (ITM_INSECT_START + 39)
#define ITM_INSECT_END (ITM_INSECT_START + 40)
#define ITM_SPIRIT0 (ITM_INSECT_START + 40)
#define ITM_SPIRIT1 (ITM_INSECT_START + 41)
#define ITM_SPIRIT2 (ITM_INSECT_START + 42)
#define ITM_SPIRIT3 (ITM_INSECT_START + 43)
#define ITM_SPIRIT4 (ITM_INSECT_START + 44)
#define ITM_INSECT_ALL_END (ITM_INSECT_START + 45)

#define ITM_HUKUBUKURO_START 0x2E00
#define ITM_HUKUBUKURO_BAG (ITM_HUKUBUKURO_START + 0)
#define ITM_HUKUBUKURO_PRESENT (ITM_HUKUBUKURO_START + 1)
#define ITM_HUKUBUKURO_END (ITM_HUKUBUKURO_START + 2)

#define ITM_KABU_START 0x2F00
#define ITM_KABU_10 (ITM_KABU_START + 0)
#define ITM_KABU_50 (ITM_KABU_START + 1)
#define ITM_KABU_100 (ITM_KABU_START + 2)
#define ITM_KABU_SPOILED (ITM_KABU_START + 3)
#define ITM_KABU_END (ITM_KABU_START + 4)

#define FTR1_START 0x3000

#define FTR_POST_MODEL 0x3020
#define FTR_HOUSE_MODEL 0x3024
#define FTR_MANOR_MODEL 0x3028
#define FTR_POLICE_MODEL 0x302C
#define FTR_MUSEUM_MODEL 0x3030
#define FTR_PLATE_ARMOR 0x3034
#define FTR_TSUKIMI_DANGO 0x3038
#define FTR_BEAN_THROWING_SET 0x303C
#define FTR_OSECHI 0x3040
#define FTR_LOVELY_PHONE 0x3044
#define FTR_MARKET_MODEL 0x3048
#define FTR_FORTUNE_TENT_MODEL 0x304C
#define FTR_CHINESE_LION 0x3050
#define FTR_TANABATA_PALM 0x3054
#define FTR_SPRING_PENNANT 0x3058
#define FTR_AUTUMN_PENNANT 0x305C
#define FTR_SHOP_MDOEL 0x3060
#define FTR_COMPASS 0x3064
#define FTR_LONG_LIFE_NOODLES 0x3068
#define FTR_BASS_BOAT 0x306C
#define FTR_LIGHTHOUSE_MODEL 0x3070
#define FTR_LIFE_RING 0x3074
#define FTR_TREE_MODEL 0x3078
#define FTR_PINK_TREE_MODEL 0x307C
#define FTR_WEED_MODEL 0x3080
#define FTR_NEEDLEWORK_MODEL 0x3084
#define FTR_DUMP_MODEL 0x3088
#define FTR_MORTAR_BALL 0x308C
#define FTR_SNOWMAN 0x3090
#define FTR_MINI_CAR 0x3094
#define FTR_BIG_CATCH_FLAG 0x3098
#define FTR_MOON 0x309C
#define FTR_LOCOMOTIVE_MODEL 0x30A0
#define FTR_DOLLY 0x30A4
#define FTR_STATION_MODEL0  0x30A8
#define FTR_STATION_MODEL1  0x30AC
#define FTR_STATION_MODEL2  0x30B0
#define FTR_STATION_MODEL3  0x30B4
#define FTR_STATION_MODEL4  0x30B8
#define FTR_STATION_MODEL5  0x30BC
#define FTR_STATION_MODEL6  0x30C0
#define FTR_STATION_MODEL7  0x30C4
#define FTR_STATION_MODEL8  0x30C8
#define FTR_STATION_MODEL9  0x30CC
#define FTR_STATION_MODEL10 0x30D0
#define FTR_STATION_MODEL11 0x30D4
#define FTR_STATION_MODEL12 0x30D8
#define FTR_STATION_MODEL13 0x30DC
#define FTR_STATION_MODEL14 0x30E0
#define FTR_WELL_MODEL 0x30E4
#define FTR_GRASS_MODEL 0x30E8
#define FTR_TRACK_MODEL 0x30EC
#define FTR_DIRT_MODEL 0x30F0
#define FTR_TRAIN_CAR_MODEL 0x30F4
#define FTR_ORANGEBOX 0x30F8

#define FTR_COLLEGERULE 0x30FC

#define FTR_CALLIGRAPHY_PAD_WEST 0x313B

#define FTR_NET 0x318C
#define FTR_AXE 0x3190
#define FTR_SHOVEL 0x3194
#define FTR_FISHING_ROD 0x3198
#define FTR_CRAB_STEW 0x319C
#define FTR_FIREPLACE 0x31A0
#define FTR_IGLOO_MODEL 0x31A4
#define FTR_SNOWY_TREE_MODEL 0x31A8

#define FTR_SNOWBOARD 0x31C4

#define FTR_SNOW_BUNNY 0x31D4
#define FTR_PAINTING15_UNUSED 0x31D8
#define FTR_PAINTING16_UNUSED 0x31DC
#define FTR_SLEIGH 0x31E0

#define FTR_BOTTLE_ROCKET 0x31F0

#define FTR_FISHING_TROPHY 0x3210

#define FTR_TELESCOPE 0x3238

#define FTR_FESTIVE_FLAG 0x327C
#define FTR_SUPER_TORTIMER 0x3280

#define FTR_MAILBOX 0x3294
#define FTR_FESTIVE_CANDLE 0x3298

#define FTR_SPRING_MEDAL 0x32A8
#define FTR_AUTUMN_MEDAL 0x32AC
#define FTR_TUMBLEWEED 0x32B0
#define FTR_COW_SKULL 0x32B4
#define FTR_OIL_DRUM 0x32B8
#define FTR_SADDLE_FENCE 0x32BC
#define FTR_WESTERN_FENCE 0x32C0
#define FTR_WATERING_TROUGH 0x32C4
#define FTR_LUIGI_TROPHY 0x32C8
#define FTR_MARIO_TROPHY 0x32CC
#define FTR_HARVEST_LAMP 0x32D0
#define FTR_COVERED_WAGON 0x32D4
#define FTR_STOREFRONT 0x32D8
#define FTR_PICNIC_TABLE 0x32DC
#define FTR_HARVEST_TABLE 0x32E0
#define FTR_HARVEST_TV 0x32E4
#define FTR_HARVEST_BED 0x32E8
#define FTR_HARVEST_CHAIR 0x32EC
#define FTR_HARVEST_CLOCK 0x32F0
#define FTR_HARVEST_SOFA 0x32F4
#define FTR_GREEN_PIPE 0x32F8
#define FTR_BRICK_BLOCK 0x32FC
#define FTR_HARVEST_BUREAU 0x3300
#define FTR_FLAGPOLE 0x3304
#define FTR_HARVEST_DRESSER 0x3308
#define FTR_SUPER_MUSHROOM 0x330C
#define FTR_HARVEST_MIRROR 0x3310
#define FTR_COIN 0x3314
#define FTR_Q_BLOCK 0x3318
#define FTR_STARMAN 0x331C
#define FTR_KOOPA_SHELL 0x3320
#define FTR_CANNON 0x3324
#define FTR_DESERT_CACTUS 0x3328
#define FTR_FIRE_FLOWER 0x332C
#define FTR_WAGON_WHEEL 0x3330
#define FTR_WELL 0x3334
#define FTR_BOXING_BARRICADE 0x3338
#define FTR_NEUTRAL_CORNER 0x333C
#define FTR_RED_CORNER 0x3340
#define FTR_BLUE_CORNER 0x3344
#define FTR_BOXING_MAT 0x3348
#define FTR_RINGSIDE_TABLE 0x334C
#define FTR_SPEED_BAG 0x3350
#define FTR_SANDBAG 0x3354
#define FTR_WEIGHT_BENCH 0x3358
#define FTR_CAMPFIRE 0x335C
#define FTR_BONFIRE 0x3360
#define FTR_KAYAK 0x3364
#define FTR_SPRINKLER 0x3368
#define FTR_TENT_MODEL 0x336C
#define FTR_BACKPACK 0x3370
#define FTR_ANGLER_TROPHY 0x3374
#define FTR_PANSY_MODEL1 0x3378
#define FTR_PANSY_MODEL2 0x337C
#define FTR_PANSY_MODEL3 0x3380
#define FTR_COSMOS_MODEL1 0x3384
#define FTR_COSMOS_MODEL2 0x3388
#define FTR_COSMOS_MODEL3 0x338C
#define FTR_TULIP_MODEL1 0x3390
#define FTR_TULIP_MODEL2 0x3394
#define FTR_TULIP_MODEL3 0x3398
#define FTR_LANTERN 0x339C
#define FTR_LAWN_MOWER 0x33A0
#define FTR_COOLER 0x33A4
#define FTR_MOUNTAIN_BIKE 0x33A8
#define FTR_SLEEPING_BAG 0x33AC
#define FTR_PROPANE_STOVE 0x33B0
#define FTR_CORNUCOPIA 0x33B4
#define FTR_JUDGES_BELL 0x33B8
#define FTR_NOISEMAKER 0x33BC
#define FTR_CHOWER 0x33C0
#define FTR_DUMMY 0x33C4
#define FTR1_END 0x33C8

#define DOOR_START 0x4000
#define DOOR0 DOOR_START  /* 0x4000 */
#define DOOR1 (DOOR0 + 1) /* 0x4001 */

#define EXIT_DOOR 0x4080
#define EXIT_DOOR1 (EXIT_DOOR + 1) /* 0x4081 */

#define NPC_HOUSE_START 0x5000
#define NPC_HOUSE000 NPC_HOUSE_START
//
#define NPC_HOUSE_END 0x50EE

#define STRUCTURE_START 0x5800
#define HOUSE0 (STRUCTURE_START + 0)
#define HOUSE1 (STRUCTURE_START + 1)
#define HOUSE2 (STRUCTURE_START + 2)
#define HOUSE3 (STRUCTURE_START + 3)
#define SHOP0 (STRUCTURE_START + 4)
#define SHOP1 (STRUCTURE_START + 5)
#define SHOP2 (STRUCTURE_START + 6)
#define SHOP3 (STRUCTURE_START + 7)
#define POST_OFFICE (STRUCTURE_START + 8)
#define TRAIN_STATION (STRUCTURE_START + 9)
#define TRAIN0 (STRUCTURE_START + 10)
#define TRAIN1 (STRUCTURE_START + 11)
#define POLICE_STATION (STRUCTURE_START + 12)
#define WATERFALL_SOUTH (STRUCTURE_START + 13)
#define WATERFALL_EAST (STRUCTURE_START + 14)
#define WATERFALL_WEST (STRUCTURE_START + 15)
#define SIGN00 (STRUCTURE_START + 16)
#define SIGN01 (STRUCTURE_START + 17)
#define SIGN02 (STRUCTURE_START + 18)
#define SIGN03 (STRUCTURE_START + 19)
#define SIGN04 (STRUCTURE_START + 20)
#define SIGN05 (STRUCTURE_START + 21)
#define SIGN06 (STRUCTURE_START + 22)
#define SIGN07 (STRUCTURE_START + 23)
#define SIGN08 (STRUCTURE_START + 24)
#define SIGN09 (STRUCTURE_START + 25)
#define SIGN10 (STRUCTURE_START + 26)
#define SIGN11 (STRUCTURE_START + 27)
#define SIGN12 (STRUCTURE_START + 28)
#define SIGN13 (STRUCTURE_START + 29)
#define SIGN14 (STRUCTURE_START + 30)
#define SIGN15 (STRUCTURE_START + 31)
#define SIGN16 (STRUCTURE_START + 32)
#define SIGN17 (STRUCTURE_START + 33)
#define SIGN18 (STRUCTURE_START + 34)
#define SIGN19 (STRUCTURE_START + 35)
#define SIGN20 (STRUCTURE_START + 36)
#define WISHING_WELL (STRUCTURE_START + 37)
#define BROKER_TENT (STRUCTURE_START + 38)
#define FORTUNE_TENT (STRUCTURE_START + 39)
#define DESIGNER_CAR (STRUCTURE_START + 40)
#define KAMAKURA (STRUCTURE_START + 41)
#define SAKURA_TABLE0 (STRUCTURE_START + 42)
#define SAKURA_TABLE1 (STRUCTURE_START + 43)
#define AEROBICS_RADIO (STRUCTURE_START + 44)
#define FIREWORKS_STALL0 (STRUCTURE_START + 45)
#define FIREWORKS_STALL1 (STRUCTURE_START + 46)
#define NEWYEAR_SHRINE0 (STRUCTURE_START + 47)
#define NEWYEAR_SHRINE1 (STRUCTURE_START + 48)
#define NEWYEAR_TABLE (STRUCTURE_START + 49)
#define NEWYEAR_COUNTDOWN0 (STRUCTURE_START + 50)
#define NEWYEAR_COUNTDOWN1 (STRUCTURE_START + 51)
#define SPORTSFAIR_BALLS_RED (STRUCTURE_START + 52)
#define SPORTSFAIR_BALLS_WHITE (STRUCTURE_START + 53)
#define SPORTSFAIR_BASKET_RED (STRUCTURE_START + 54)
#define SPORTSFAIR_BASKET_WHITE (STRUCTURE_START + 55)
#define FISHCHECK_STAND0 (STRUCTURE_START + 56)
#define FISHCHECK_STAND1 (STRUCTURE_START + 57)
#define KOINOBORI_WINDSOCK (STRUCTURE_START + 58)
#define DUMP (STRUCTURE_START + 59)
#define WINDMILL0 (STRUCTURE_START + 60)
#define WINDMILL1 (STRUCTURE_START + 61)
#define WINDMILL2 (STRUCTURE_START + 62)
#define WINDMILL3 (STRUCTURE_START + 63)
#define WINDMILL4 (STRUCTURE_START + 64)
#define LOTUS (STRUCTURE_START + 65)
#define MIKANBOX (STRUCTURE_START + 66)
#define DOUZOU (STRUCTURE_START + 67) // train station statue
#define TOUDAI (STRUCTURE_START + 68) // lighthouse
#define GHOG (STRUCTURE_START + 69)
#define HTABLE0 (STRUCTURE_START + 70)
#define HTABLE1 (STRUCTURE_START + 71)
#define HTABLE2 (STRUCTURE_START + 72)
#define TENT (STRUCTURE_START + 73)
#define MUSEUM (STRUCTURE_START + 74)
#define BRIDGE_A0 (STRUCTURE_START + 75)
#define BRIDGE_A1 (STRUCTURE_START + 76)
#define NEEDLEWORK_SHOP (STRUCTURE_START + 77)
#define FLAG (STRUCTURE_START + 78)
#define BOAT (STRUCTURE_START + 79)
#define COTTAGE_MY (STRUCTURE_START + 80)
#define COTTAGE_NPC (STRUCTURE_START + 81)
#define COTTAGE_NPC_END (COTTAGE_NPC + 1)
#define PORT_SIGN (STRUCTURE_START + 82)
#define STRUCTURE_END (STRUCTURE_START + 83)

#define ETC_START 0x8000
#define ETC_AIRPLANE ETC_START
#define ETC_BALL (ETC_START + 1)
#define ETC_MY_ROOM (ETC_START + 2)
#define ETC_MBG (ETC_START + 3)
#define ETC_BOXTRICK (ETC_START + 4)
#define ETC_BOXMANAGER (ETC_START + 5)
#define ETC_ARRANGE_ROOM (ETC_START + 6)
#define ETC_ARRANGE_FURNITURE (ETC_START + 7)
#define ETC_SNOWMAN_BALL_A (ETC_START + 13)
#define ETC_SNOWMAN_BALL_B (ETC_START + 14)
#define ETC_TRAIN_WINDOW (ETC_START + 17)
#define ETC_UKI (ETC_START + 18)

#define MISC_ACTOR_START 0x9000
#define MISC_ACTOR_SAMPLE MISC_ACTOR_START

#define ACTOR_PROP_START 0xA000
#define ACTOR_PROP_MAILBOX0 (ACTOR_PROP_START + 0) // A000
#define ACTOR_PROP_MAILBOX1 (ACTOR_PROP_START + 1) // A001
#define ACTOR_PROP_MAILBOX2 (ACTOR_PROP_START + 2) // A002
#define ACTOR_PROP_MAILBOX3 (ACTOR_PROP_START + 3) // A003
#define ACTOR_PROP_HANIWA0 (ACTOR_PROP_START + 4) // A004
#define ACTOR_PROP_HANIWA1 (ACTOR_PROP_START + 5) // A005
#define ACTOR_PROP_HANIWA2 (ACTOR_PROP_START + 6) // A006
#define ACTOR_PROP_HANIWA3 (ACTOR_PROP_START + 7) // A007
#define SNOWMAN0 (ACTOR_PROP_START + 8) // A008
#define SNOWMAN1 (ACTOR_PROP_START + 9) // A009
#define SNOWMAN2 (ACTOR_PROP_START + 10) // A00A
#define SNOWMAN3 (ACTOR_PROP_START + 11) // A00B
#define SNOWMAN4 (ACTOR_PROP_START + 12) // A00C
#define SNOWMAN5 (ACTOR_PROP_START + 13) // A00D
#define SNOWMAN6 (ACTOR_PROP_START + 14) // A00E
#define SNOWMAN7 (ACTOR_PROP_START + 15) // A00F
#define SNOWMAN8 (ACTOR_PROP_START + 16) // A010
#define TRAIN_DOOR (ACTOR_PROP_START + 17) // A011
#define ACTOR_PROP_VILLAGER_SIGNBOARD (ACTOR_PROP_START + 18) // A012

#define SP_NPC_START 0xD000
#define SP_NPC_ARTIST (SP_NPC_START + 0) // D000
#define SP_NPC_BROKER (SP_NPC_START + 1) // D001
#define SP_NPC_DESIGNER (SP_NPC_START + 2) // D002
#define SP_NPC_POST_GIRL (SP_NPC_START + 3) // D003
#define SP_NPC_GUIDE (SP_NPC_START + 4) // D004
#define SP_NPC_GUIDE2 (SP_NPC_START + 5) // D005
#define SP_NPC_CARPETPEDDLER (SP_NPC_START + 6) // D006
#define SP_NPC_KABUPEDDLER (SP_NPC_START + 7) // D007
#define SP_NPC_SHOP_MASTER (SP_NPC_START + 8) // D008
#define SP_NPC_CONV_MASTER (SP_NPC_START + 9) // D009
#define SP_NPC_SUPER_MASTER (SP_NPC_START + 10) // D00A
#define SP_NPC_DEPART_MASTER (SP_NPC_START + 11) // D00B
#define SP_NPC_GYPSY (SP_NPC_START + 12) // D00C
#define SP_NPC_POLICE (SP_NPC_START + 13) // D00D
#define SP_NPC_STATION_MASTER (SP_NPC_START + 14) // D00E
#define SP_NPC_SANTA (SP_NPC_START + 15) // D00F
#define SP_NPC_POLICE2 (SP_NPC_START + 16) // D010
#define SP_NPC_POST_MAN (SP_NPC_START + 17) // D011
#define SP_NPC_POST_GIRL2 (SP_NPC_START + 18) // D012
#define SP_NPC_EV_BROKER2 (SP_NPC_START + 19) // D013
#define SP_NPC_RCN_GUIDE (SP_NPC_START + 20) // D014
#define SP_NPC_RCN_GUIDE_1 (SP_NPC_START + 21) // D015
#define SP_NPC_RCN_GUIDE_2 (SP_NPC_START + 22) // D016
#define SP_NPC_RCN_GUIDE_3 (SP_NPC_START + 23) // D017
#define SP_NPC_P_SEL (SP_NPC_START + 24) // D018
#define SP_NPC_RCN_GUIDE2 (SP_NPC_START + 25) // D019
#define SP_NPC_RCN_GUIDE2_1 (SP_NPC_START + 26) // D01A
#define SP_NPC_RCN_GUIDE2_2 (SP_NPC_START + 27) // D01B
#define SP_NPC_RCN_GUIDE2_3 (SP_NPC_START + 28) // D01C
#define SP_NPC_ANGLER (SP_NPC_START + 29) // D01D
#define SP_NPC_SHOP_MASTERSP (SP_NPC_START + 30) // D01E
#define SP_NPC_P_SEL2 (SP_NPC_START + 31) // D01F
#define SP_NPC_EV_HALLOWEEN_0 (SP_NPC_START + 32) // D020
#define SP_NPC_EV_HALLOWEEN_1 (SP_NPC_START + 33) // D021
#define SP_NPC_EV_HALLOWEEN_2 (SP_NPC_START + 34) // D022
#define SP_NPC_EV_HALLOWEEN_3 (SP_NPC_START + 35) // D023
#define SP_NPC_EV_HALLOWEEN_4 (SP_NPC_START + 36) // D024
#define SP_NPC_HALLOWEEN (SP_NPC_START + 37) // D025
#define SP_NPC_MAMEDANUKI0 (SP_NPC_START + 38) // D026
#define SP_NPC_EV_HANABI_0 (SP_NPC_START + 39) // D027
#define SP_NPC_EV_HANABI_1 (SP_NPC_START + 40) // D028
#define SP_NPC_EV_HANABI_2 (SP_NPC_START + 41) // D029
#define SP_NPC_EV_HANABI_3 (SP_NPC_START + 42) // D02A
#define SP_NPC_EV_HANABI_4 (SP_NPC_START + 43) // D02B
#define SP_NPC_EV_YOMISE (SP_NPC_START + 44) // D02C
#define SP_NPC_EV_TOKYOSO_0 (SP_NPC_START + 45) // D02D
#define SP_NPC_EV_TOKYOSO_1 (SP_NPC_START + 46) // D02E
#define SP_NPC_EV_TOKYOSO_2 (SP_NPC_START + 47) // D02F
#define SP_NPC_EV_TOKYOSO_3 (SP_NPC_START + 48) // D030
#define SP_NPC_EV_TOKYOSO_4 (SP_NPC_START + 49) // D031
#define SP_NPC_EV_HANAMI_0 (SP_NPC_START + 50) // D032
#define SP_NPC_EV_HANAMI_1 (SP_NPC_START + 51) // D033
#define SP_NPC_EV_HANAMI_2 (SP_NPC_START + 52) // D034
#define SP_NPC_EV_HANAMI_3 (SP_NPC_START + 53) // D035
#define SP_NPC_EV_HANAMI_4 (SP_NPC_START + 54) // D036
#define SP_NPC_MAMEDANUKI1 (SP_NPC_START + 55) // D037
#define SP_NPC_SLEEP_OBABA (SP_NPC_START + 56) // D038
#define SP_NPC_EV_YOMISE2 (SP_NPC_START + 57) // D039
#define SP_NPC_SHOP_MASTERSP_2 (SP_NPC_START + 58) // D03A
#define SP_NPC_SHOP_MASTERSP_3 (SP_NPC_START + 59) // D03B
#define SP_NPC_SHOP_MASTERSP_4 (SP_NPC_START + 60) // D03C
#define SP_NPC_EV_MIKO (SP_NPC_START + 61) // D03D
#define SP_NPC_MAJIN (SP_NPC_START + 62) // D03E
#define SP_NPC_EV_TUKIMI_0 (SP_NPC_START + 63) // D03F
#define SP_NPC_EV_TUKIMI_1 (SP_NPC_START + 64) // D040
#define SP_NPC_EV_TUKIMI_2 (SP_NPC_START + 65) // D041
#define SP_NPC_EV_TUKIMI_3 (SP_NPC_START + 66) // D042
#define SP_NPC_EV_TUKIMI_4 (SP_NPC_START + 67) // D043
#define SP_NPC_EV_COUNTDOWN_0 (SP_NPC_START + 68) // D044
#define SP_NPC_EV_COUNTDOWN_1 (SP_NPC_START + 69) // D045
#define SP_NPC_EV_COUNTDOWN_2 (SP_NPC_START + 70) // D046
#define SP_NPC_EV_COUNTDOWN_3 (SP_NPC_START + 71) // D047
#define SP_NPC_EV_COUNTDOWN_4 (SP_NPC_START + 72) // D048
#define SP_NPC_EV_TURI_0 (SP_NPC_START + 73) // D049
#define SP_NPC_EV_TURI_1 (SP_NPC_START + 74) // D04A
#define SP_NPC_EV_TURI_2 (SP_NPC_START + 75) // D04B
#define SP_NPC_EV_TURI_3 (SP_NPC_START + 76) // D04C
#define SP_NPC_EV_TURI_4 (SP_NPC_START + 77) // D04D
#define SP_NPC_EV_TAISOU_0 (SP_NPC_START + 78) // D04E
#define SP_NPC_EV_TAISOU_1 (SP_NPC_START + 79) // D04F
#define SP_NPC_EV_TAISOU_2 (SP_NPC_START + 80) // D050
#define SP_NPC_EV_TAISOU_3 (SP_NPC_START + 81) // D051
#define SP_NPC_EV_TAISOU_4 (SP_NPC_START + 82) // D052
#define SP_NPC_EV_TAMAIRE_0 (SP_NPC_START + 83) // D053
#define SP_NPC_EV_TAMAIRE_1 (SP_NPC_START + 84) // D054
#define SP_NPC_EV_TAMAIRE_2 (SP_NPC_START + 85) // D055
#define SP_NPC_EV_TAMAIRE_3 (SP_NPC_START + 86) // D056
#define SP_NPC_EV_TAMAIRE_4 (SP_NPC_START + 87) // D057
#define SP_NPC_EV_HATUMODE_0 (SP_NPC_START + 88) // D058
#define SP_NPC_EV_HATUMODE_1 (SP_NPC_START + 89) // D059
#define SP_NPC_EV_HATUMODE_2 (SP_NPC_START + 90) // D05A
#define SP_NPC_EV_HATUMODE_3 (SP_NPC_START + 91) // D05B
#define SP_NPC_EV_HATUMODE_4 (SP_NPC_START + 92) // D05C
#define SP_NPC_TOTAKEKE (SP_NPC_START + 93) // D05D
#define SP_NPC_EV_KAMAKURA_0 (SP_NPC_START + 94) // D05E
#define SP_NPC_EV_TUNAHIKI_0 (SP_NPC_START + 95) // D05F
#define SP_NPC_EV_TUNAHIKI_1 (SP_NPC_START + 96) // D060
#define SP_NPC_EV_TUNAHIKI_2 (SP_NPC_START + 97) // D061
#define SP_NPC_EV_TUNAHIKI_3 (SP_NPC_START + 98) // D062
#define SP_NPC_EV_TUNAHIKI_4 (SP_NPC_START + 99) // D063
#define SP_NPC_EV_DOZAEMON (SP_NPC_START + 100) // D064
#define SP_NPC_MAJIN2 (SP_NPC_START + 101) // D065
#define SP_NPC_RTC (SP_NPC_START + 102) // D066
#define SP_NPC_ENGINEER (SP_NPC_START + 103) // D067
#define SP_NPC_MAJIN3 (SP_NPC_START + 104) // D068
#define SP_NPC_MAJIN4 (SP_NPC_START + 105) // D069
#define SP_NPC_RESTART (SP_NPC_START + 106) // D06A
#define SP_NPC_MAJIN5 (SP_NPC_START + 107) // D06B
#define SP_NPC_EV_DOKUTU (SP_NPC_START + 108) // D06C
#define SP_NPC_CURATOR (SP_NPC_START + 109) // D06D
#define SP_NPC_EV_SONCHO (SP_NPC_START + 110) // D06E
#define SP_NPC_EV_GHOST (SP_NPC_START + 111) // D06F
#define SP_NPC_NEEDLEWORK0 (SP_NPC_START + 112) // D070
#define SP_NPC_NEEDLEWORK1 (SP_NPC_START + 113) // D071
#define SP_NPC_SENDO (SP_NPC_START + 114) // D072
#define SP_NPC_PRESENT_NPC (SP_NPC_START + 115) // D073
#define SP_NPC_EV_SONCHO2 (SP_NPC_START + 116) // D074
#define SP_NPC_MASK_CAT (SP_NPC_START + 117) // D075
#define SP_NPC_MASK_CAT2 (SP_NPC_START + 118) // D076
#define SP_NPC_GO_HONE_NPC (SP_NPC_START + 119) // D077
#define SP_NPC_SONCHO_D078 (SP_NPC_START + 120) // D078
#define SP_NPC_SONCHO_D079 (SP_NPC_START + 121) // D079
#define SP_NPC_SASHO (SP_NPC_START + 122) // D07A
#define SP_NPC_CASTAWAY (SP_NPC_START + 123) // D07B
#define SP_NPC_MAJIN_D07C (SP_NPC_START + 124) // D07C
#define SP_NPC_MAJIN_D07D (SP_NPC_START + 125) // D07D
#define SP_NPC_MAJIN_BROTHER (SP_NPC_START + 126) // D07E
#define SP_NPC_SONCHO (SP_NPC_START + 127) // D07F
#define SP_NPC_MAJIN_D080 (SP_NPC_START + 128) // D080
#define SP_NPC_EV_MAJIN (SP_NPC_START + 129) // D081
#define SP_NPC_EV_HARVEST_0 (SP_NPC_START + 130) // D082
#define SP_NPC_EV_HARVEST_1 (SP_NPC_START + 131) // D083
#define SP_NPC_EV_HARVEST_2 (SP_NPC_START + 132) // D084
#define SP_NPC_EV_HARVEST_3 (SP_NPC_START + 133) // D085
#define SP_NPC_EV_HARVEST_4 (SP_NPC_START + 134) // D086
#define SP_NPC_EV_SPEECH_SONCHO (SP_NPC_START + 135) // D087
#define SP_NPC_EV_GROUNDHOG_0 (SP_NPC_START + 136) // D088
#define SP_NPC_EV_GROUNDHOG_1 (SP_NPC_START + 137) // D089
#define SP_NPC_EV_GROUNDHOG_2 (SP_NPC_START + 138) // D08A
#define SP_NPC_EV_GROUNDHOG_3 (SP_NPC_START + 139) // D08B
#define SP_NPC_EV_GROUNDHOG_4 (SP_NPC_START + 140) // D08C
#define SP_NPC_TURKEY (SP_NPC_START + 141) // D08D
#define SP_NPC_HEM (SP_NPC_START + 142) // D08E
#define SP_NPC_EV_SUMMERCAMP_0 (SP_NPC_START + 143) // 0xD08F

#define NPC_START    0xE000
// cats
#define NPC_BOB      NPC_START
#define NPC_OLIVIA   (NPC_START + 1)
#define NPC_MITZI    (NPC_START + 2)
#define NPC_KIKI     (NPC_START + 3)
#define NPC_TANGY    (NPC_START + 4)
#define NPC_KABUKI   (NPC_START + 5)
#define NPC_TABBY    (NPC_START + 6)
#define NPC_MONIQUE  (NPC_START + 7)
#define NPC_STINKY   (NPC_START + 8)
#define NPC_PURRL    (NPC_START + 9)
#define NPC_KITTY    (NPC_START + 10)
#define NPC_TOM      (NPC_START + 11)
#define NPC_ROSIE    (NPC_START + 12)
// anteaters
#define NPC_NOSEGAY  (NPC_START + 13)
#define NPC_ZOE      (NPC_START + 14)
#define NPC_PANGO    (NPC_START + 15)
#define NPC_CYRANO   (NPC_START + 16)
#define NPC_SNOOTY   (NPC_START + 17)
// bears
#define NPC_TEDDY    (NPC_START + 18)
#define NPC_CHOW     (NPC_START + 19)
#define NPC_DOZER    (NPC_START + 20)
#define NPC_NATE     (NPC_START + 21)
#define NPC_GROUCHO  (NPC_START + 22)
#define NPC_TUTU     (NPC_START + 23)
#define NPC_URSALA   (NPC_START + 24)
#define NPC_GRIZZLY  (NPC_START + 25)
#define NPC_PINKY    (NPC_START + 26)
// birds
#define NPC_JAY      (NPC_START + 27)
#define NPC_TWIGGY   (NPC_START + 28)
#define NPC_ANCHOVY  (NPC_START + 29)
#define NPC_PIPER    (NPC_START + 30)
#define NPC_ADMIRAL  (NPC_START + 31)
#define NPC_OTIS     (NPC_START + 32)
#define NPC_ROBIN    (NPC_START + 33)
#define NPC_MIDGE    (NPC_START + 34)
#define NPC_ACE      (NPC_START + 35)
#define NPC_TWIRP    (NPC_START + 36)
// bulls)
#define NPC_CHUCK    (NPC_START + 37)
#define NPC_STU      (NPC_START + 38)
// chickens
#define NPC_GOOSE    (NPC_START + 39)
#define NPC_BETTY    (NPC_START + 40)
#define NPC_HECTOR   (NPC_START + 41)
#define NPC_EGBERT   (NPC_START + 42)
#define NPC_AVA      (NPC_START + 43)
#define NPC_HANK     (NPC_START + 44)
#define NPC_LEIGH    (NPC_START + 45)
#define NPC_RHODA    (NPC_START + 46)
// cubs
#define NPC_VLADIMIR (NPC_START + 47)
#define NPC_MURPHY   (NPC_START + 48)
#define NPC_CUPCAKE  (NPC_START + 49)
#define NPC_KODY     (NPC_START + 50)
#define NPC_MAPLE    (NPC_START + 51)
#define NPC_PUDGE    (NPC_START + 52)
#define NPC_OLIVE    (NPC_START + 53)
#define NPC_PONCHO   (NPC_START + 54)
#define NPC_BLUEBEAR (NPC_START + 55)
// cows
#define NPC_PATTY    (NPC_START + 56)
#define NPC_PETUNIA  (NPC_START + 57)
#define NPC_BESSIE   (NPC_START + 58)
#define NPC_BELLE    (NPC_START + 59)
// crocodiles / alligators
#define NPC_ALFONSO  (NPC_START + 60)
#define NPC_BOOTS    (NPC_START + 61)
#define NPC_LIZ      (NPC_START + 62)
#define NPC_BISKIT   (NPC_START + 63)
// dogs
#define NPC_GOLDIE   (NPC_START + 64)
#define NPC_DAISY    (NPC_START + 65)
#define NPC_LUCKY    (NPC_START + 66)
#define NPC_PORTIA   (NPC_START + 67)
#define NPC_MADDIE   (NPC_START + 68)
#define NPC_BUTCH    (NPC_START + 69)
// ducks
#define NPC_BILL     (NPC_START + 70)
#define NPC_POMPOM   (NPC_START + 71)
#define NPC_JOEY     (NPC_START + 72)
#define NPC_SCOOT    (NPC_START + 73)
#define NPC_DERWIN   (NPC_START + 74)
#define NPC_FRECKLES (NPC_START + 75)
// elephants
#define NPC_PAOLO    (NPC_START + 76)
#define NPC_DIZZY    (NPC_START + 77)
#define NPC_AXEL     (NPC_START + 78)
// frogs
#define NPC_EMERALD  (NPC_START + 79)
#define NPC_TAD      (NPC_START + 80)
#define NPC_WART_JR  (NPC_START + 81)
#define NPC_COUSTEAU (NPC_START + 82)
#define NPC_PUDDLES  (NPC_START + 83)
#define NPC_LILY     (NPC_START + 84)
#define NPC_JEREMIAH (NPC_START + 85)
#define NPC_HUCK     (NPC_START + 86)
#define NPC_CAMOFROG (NPC_START + 87)
#define NPC_RIBBOT   (NPC_START + 88)
#define NPC_PRINCE   (NPC_START + 89)
#define NPC_JAMBETTE (NPC_START + 90)
// goats
#define NPC_BILLY    (NPC_START + 91)
#define NPC_CHEVRE   (NPC_START + 92)
#define NPC_IGGY     (NPC_START + 93)
#define NPC_GRUFF    (NPC_START + 94)
#define NPC_SVEN     (NPC_START + 95)
#define NPC_VELMA    (NPC_START + 96)
// gorillas
#define NPC_JANE     (NPC_START + 97)
#define NPC_CESAR    (NPC_START + 98)
#define NPC_LOUIE    (NPC_START + 99)
#define NPC_PEEWEE   (NPC_START + 100)
// hippos
#define NPC_ROLLO    (NPC_START + 101)
#define NPC_BUBBLES  (NPC_START + 102)
#define NPC_BERTHA   (NPC_START + 103)
// horses
#define NPC_ELMER    (NPC_START + 104)
#define NPC_WINNIE   (NPC_START + 105)
#define NPC_SAVANNAH (NPC_START + 106)
#define NPC_ED       (NPC_START + 107)
#define NPC_CLEO     (NPC_START + 108)
#define NPC_PEACHES  (NPC_START + 109)
#define NPC_BUCK     (NPC_START + 110)
// kangaroos
#define NPC_CARRIE   (NPC_START + 111)
#define NPC_MATHILDA (NPC_START + 112)
#define NPC_MARCY    (NPC_START + 113)
#define NPC_KITT     (NPC_START + 114)
#define NPC_VALISE   (NPC_START + 115)
#define NPC_ASTRID   (NPC_START + 116)
// koalas
#define NPC_SYDNEY   (NPC_START + 117)
#define NPC_GONZO    (NPC_START + 118)
#define NPC_OZZIE    (NPC_START + 119)
#define NPC_YUKA     (NPC_START + 120)
#define NPC_HUGGY    (NPC_START + 121)
// lions
#define NPC_REX      (NPC_START + 122)
#define NPC_AZIZ     (NPC_START + 123)
#define NPC_LEOPOLD  (NPC_START + 124)
// mice
#define NPC_SAMSON   (NPC_START + 125)
#define NPC_PENNY    (NPC_START + 126)
#define NPC_DORA     (NPC_START + 127)
#define NPC_CHICO    (NPC_START + 128)
#define NPC_CANDI    (NPC_START + 129)
#define NPC_RIZZO    (NPC_START + 130)
#define NPC_ANICOTTI (NPC_START + 131)
#define NPC_LIMBERG  (NPC_START + 132)
#define NPC_CARMEN   (NPC_START + 133)
// octopus
#define NPC_OCTAVIAN (NPC_START + 134)
// ostriches
#define NPC_SANDY    (NPC_START + 135)
#define NPC_SPROCKET (NPC_START + 136)
#define NPC_RIO      (NPC_START + 137)
#define NPC_QUEENIE  (NPC_START + 138)
// eagles
#define NPC_APOLLO   (NPC_START + 139)
#define NPC_BUZZ     (NPC_START + 140)
#define NPC_QUETZAL  (NPC_START + 141)
#define NPC_AMELIA   (NPC_START + 142)
#define NPC_PIERCE   (NPC_START + 143)
// penguins
#define NPC_ROALD    (NPC_START + 144)
#define NPC_AURORA   (NPC_START + 145)
#define NPC_HOPPER   (NPC_START + 146)
#define NPC_CUBE     (NPC_START + 147)
#define NPC_PUCK     (NPC_START + 148)
#define NPC_GWEN     (NPC_START + 149)
#define NPC_FRIGA    (NPC_START + 150)
// pigs
#define NPC_CURLY    (NPC_START + 151)
#define NPC_TRUFFLES (NPC_START + 152)
#define NPC_SPORK    (NPC_START + 153)
#define NPC_HUGH     (NPC_START + 154)
#define NPC_RASHER   (NPC_START + 155)
#define NPC_SUE_E    (NPC_START + 156)
#define NPC_HAMBO    (NPC_START + 157)
#define NPC_LUCY     (NPC_START + 158)
#define NPC_COBB     (NPC_START + 159)
#define NPC_BORIS    (NPC_START + 160)
// rabbits
#define NPC_BUNNIE   (NPC_START + 161)
#define NPC_DOC      (NPC_START + 162)
#define NPC_GASTON   (NPC_START + 163)
#define NPC_COCO     (NPC_START + 164)
#define NPC_GABI     (NPC_START + 165)
#define NPC_DOTTY    (NPC_START + 166)
#define NPC_GENJI    (NPC_START + 167)
#define NPC_SNAKE    (NPC_START + 168)
#define NPC_CLAUDE   (NPC_START + 169)
// rhinos 
#define NPC_TANK     (NPC_START + 170)
#define NPC_SPIKE    (NPC_START + 171)
#define NPC_TIARA    (NPC_START + 172)
// sheep
#define NPC_VESTA    (NPC_START + 173)
// squirrels
#define NPC_FILBERT  (NPC_START + 174)
#define NPC_HAZEL    (NPC_START + 175)
#define NPC_PEANUT   (NPC_START + 176)
#define NPC_PECAN    (NPC_START + 177)
#define NPC_RICKY    (NPC_START + 178)
#define NPC_STATIC   (NPC_START + 179)
#define NPC_MINT     (NPC_START + 180)
#define NPC_NIBBLES  (NPC_START + 181)
// tigers
#define NPC_TYBALT   (NPC_START + 182)
#define NPC_ROLF     (NPC_START + 183)
#define NPC_BANGLE   (NPC_START + 184)
// wolves
#define NPC_LOBO     (NPC_START + 185)
#define NPC_FREYA    (NPC_START + 186)
#define NPC_CHIEF    (NPC_START + 187)
// late additions
#define NPC_WEBER    (NPC_START + 188)
#define NPC_MALLARY  (NPC_START + 189)
#define NPC_WOLFGANG (NPC_START + 190)
#define NPC_HORNSBY  (NPC_START + 191)
#define NPC_OXFORD   (NPC_START + 192)
#define NPC_T_BONE   (NPC_START + 193)
#define NPC_BIFF     (NPC_START + 194)
#define NPC_OPAL     (NPC_START + 195)
#define NPC_BONES    (NPC_START + 196)
#define NPC_BEA      (NPC_START + 197)
#define NPC_BITTY    (NPC_START + 198)
#define NPC_ROCCO    (NPC_START + 199)
#define NPC_LULU     (NPC_START + 200)
#define NPC_BLAIRE   (NPC_START + 201)
#define NPC_SALLY    (NPC_START + 202)
#define NPC_ELLIE    (NPC_START + 203)
#define NPC_ELOISE   (NPC_START + 204)
#define NPC_ALLI     (NPC_START + 205)
#define NPC_PIPPY    (NPC_START + 206)
#define NPC_EUNICE   (NPC_START + 207)
#define NPC_BAABARA  (NPC_START + 208)
#define NPC_FANG     (NPC_START + 209)
#define NPC_DEENA    (NPC_START + 210)
#define NPC_PATE     (NPC_START + 211)
#define NPC_STELLA   (NPC_START + 212)
#define NPC_CASHMERE (NPC_START + 213)
#define NPC_WOOLIO   (NPC_START + 214)
#define NPC_COOKIE   (NPC_START + 215)
// gamecube additions
#define NPC_MAELLE   (NPC_START + 216)
#define NPC_OHARE    (NPC_START + 217)
#define NPC_BLISS    (NPC_START + 218)
#define NPC_DRIFT    (NPC_START + 219)
#define NPC_BUD      (NPC_START + 220)
#define NPC_BOOMER   (NPC_START + 221)
#define NPC_ELINA    (NPC_START + 222)
#define NPC_FLASH    (NPC_START + 223)
#define NPC_DOBIE    (NPC_START + 224)
#define NPC_FLOSSIE  (NPC_START + 225)
#define NPC_ANNALISE (NPC_START + 226)
#define NPC_PLUCKY   (NPC_START + 227)
#define NPC_FAITH    (NPC_START + 228)
#define NPC_YODEL    (NPC_START + 229)
#define NPC_ROWAN    (NPC_START + 230)
#define NPC_JUNE     (NPC_START + 231)
#define NPC_CHERI    (NPC_START + 232)
#define NPC_PIGLEG   (NPC_START + 233)
#define NPC_ANKHA    (NPC_START + 234)
#define NPC_PUNCHY   (NPC_START + 235)
#define NPC_END      (NPC_START + 236)

#define DUMMY_START 0xF000
#define DUMMY_MAILBOX0 (DUMMY_START + 1) // 0xF001
#define DUMMY_MAILBOX1 (DUMMY_START + 2) // 0xF002
#define DUMMY_MAILBOX2 (DUMMY_START + 3) // 0xF003
#define DUMMY_MAILBOX3 (DUMMY_START + 4) // 0xF004
#define DUMMY_NPC_HOUSE_START (DUMMY_START + 5) // 0xF005
#define DUMMY_NPC_HOUSE_000 (DUMMY_START + 5) // F005
#define DUMMY_NPC_HOUSE_001 (DUMMY_START + 6) // F006
#define DUMMY_NPC_HOUSE_002 (DUMMY_START + 7) // F007
#define DUMMY_NPC_HOUSE_003 (DUMMY_START + 8) // F008
#define DUMMY_NPC_HOUSE_004 (DUMMY_START + 9) // F009
#define DUMMY_NPC_HOUSE_005 (DUMMY_START + 10) // F00A
#define DUMMY_NPC_HOUSE_006 (DUMMY_START + 11) // F00B
#define DUMMY_NPC_HOUSE_007 (DUMMY_START + 12) // F00C
#define DUMMY_NPC_HOUSE_008 (DUMMY_START + 13) // F00D
#define DUMMY_NPC_HOUSE_009 (DUMMY_START + 14) // F00E
#define DUMMY_NPC_HOUSE_010 (DUMMY_START + 15) // F00F
#define DUMMY_NPC_HOUSE_011 (DUMMY_START + 16) // F010
#define DUMMY_NPC_HOUSE_012 (DUMMY_START + 17) // F011
#define DUMMY_NPC_HOUSE_013 (DUMMY_START + 18) // F012
#define DUMMY_NPC_HOUSE_014 (DUMMY_START + 19) // F013
#define DUMMY_NPC_HOUSE_015 (DUMMY_START + 20) // F014
#define DUMMY_NPC_HOUSE_016 (DUMMY_START + 21) // F015
#define DUMMY_NPC_HOUSE_017 (DUMMY_START + 22) // F016
#define DUMMY_NPC_HOUSE_018 (DUMMY_START + 23) // F017
#define DUMMY_NPC_HOUSE_019 (DUMMY_START + 24) // F018
#define DUMMY_NPC_HOUSE_020 (DUMMY_START + 25) // F019
#define DUMMY_NPC_HOUSE_021 (DUMMY_START + 26) // F01A
#define DUMMY_NPC_HOUSE_022 (DUMMY_START + 27) // F01B
#define DUMMY_NPC_HOUSE_023 (DUMMY_START + 28) // F01C
#define DUMMY_NPC_HOUSE_024 (DUMMY_START + 29) // F01D
#define DUMMY_NPC_HOUSE_025 (DUMMY_START + 30) // F01E
#define DUMMY_NPC_HOUSE_026 (DUMMY_START + 31) // F01F
#define DUMMY_NPC_HOUSE_027 (DUMMY_START + 32) // F020
#define DUMMY_NPC_HOUSE_028 (DUMMY_START + 33) // F021
#define DUMMY_NPC_HOUSE_029 (DUMMY_START + 34) // F022
#define DUMMY_NPC_HOUSE_030 (DUMMY_START + 35) // F023
#define DUMMY_NPC_HOUSE_031 (DUMMY_START + 36) // F024
#define DUMMY_NPC_HOUSE_032 (DUMMY_START + 37) // F025
#define DUMMY_NPC_HOUSE_033 (DUMMY_START + 38) // F026
#define DUMMY_NPC_HOUSE_034 (DUMMY_START + 39) // F027
#define DUMMY_NPC_HOUSE_035 (DUMMY_START + 40) // F028
#define DUMMY_NPC_HOUSE_036 (DUMMY_START + 41) // F029
#define DUMMY_NPC_HOUSE_037 (DUMMY_START + 42) // F02A
#define DUMMY_NPC_HOUSE_038 (DUMMY_START + 43) // F02B
#define DUMMY_NPC_HOUSE_039 (DUMMY_START + 44) // F02C
#define DUMMY_NPC_HOUSE_040 (DUMMY_START + 45) // F02D
#define DUMMY_NPC_HOUSE_041 (DUMMY_START + 46) // F02E
#define DUMMY_NPC_HOUSE_042 (DUMMY_START + 47) // F02F
#define DUMMY_NPC_HOUSE_043 (DUMMY_START + 48) // F030
#define DUMMY_NPC_HOUSE_044 (DUMMY_START + 49) // F031
#define DUMMY_NPC_HOUSE_045 (DUMMY_START + 50) // F032
#define DUMMY_NPC_HOUSE_046 (DUMMY_START + 51) // F033
#define DUMMY_NPC_HOUSE_047 (DUMMY_START + 52) // F034
#define DUMMY_NPC_HOUSE_048 (DUMMY_START + 53) // F035
#define DUMMY_NPC_HOUSE_049 (DUMMY_START + 54) // F036
#define DUMMY_NPC_HOUSE_050 (DUMMY_START + 55) // F037
#define DUMMY_NPC_HOUSE_051 (DUMMY_START + 56) // F038
#define DUMMY_NPC_HOUSE_052 (DUMMY_START + 57) // F039
#define DUMMY_NPC_HOUSE_053 (DUMMY_START + 58) // F03A
#define DUMMY_NPC_HOUSE_054 (DUMMY_START + 59) // F03B
#define DUMMY_NPC_HOUSE_055 (DUMMY_START + 60) // F03C
#define DUMMY_NPC_HOUSE_056 (DUMMY_START + 61) // F03D
#define DUMMY_NPC_HOUSE_057 (DUMMY_START + 62) // F03E
#define DUMMY_NPC_HOUSE_058 (DUMMY_START + 63) // F03F
#define DUMMY_NPC_HOUSE_059 (DUMMY_START + 64) // F040
#define DUMMY_NPC_HOUSE_060 (DUMMY_START + 65) // F041
#define DUMMY_NPC_HOUSE_061 (DUMMY_START + 66) // F042
#define DUMMY_NPC_HOUSE_062 (DUMMY_START + 67) // F043
#define DUMMY_NPC_HOUSE_063 (DUMMY_START + 68) // F044
#define DUMMY_NPC_HOUSE_064 (DUMMY_START + 69) // F045
#define DUMMY_NPC_HOUSE_065 (DUMMY_START + 70) // F046
#define DUMMY_NPC_HOUSE_066 (DUMMY_START + 71) // F047
#define DUMMY_NPC_HOUSE_067 (DUMMY_START + 72) // F048
#define DUMMY_NPC_HOUSE_068 (DUMMY_START + 73) // F049
#define DUMMY_NPC_HOUSE_069 (DUMMY_START + 74) // F04A
#define DUMMY_NPC_HOUSE_070 (DUMMY_START + 75) // F04B
#define DUMMY_NPC_HOUSE_071 (DUMMY_START + 76) // F04C
#define DUMMY_NPC_HOUSE_072 (DUMMY_START + 77) // F04D
#define DUMMY_NPC_HOUSE_073 (DUMMY_START + 78) // F04E
#define DUMMY_NPC_HOUSE_074 (DUMMY_START + 79) // F04F
#define DUMMY_NPC_HOUSE_075 (DUMMY_START + 80) // F050
#define DUMMY_NPC_HOUSE_076 (DUMMY_START + 81) // F051
#define DUMMY_NPC_HOUSE_077 (DUMMY_START + 82) // F052
#define DUMMY_NPC_HOUSE_078 (DUMMY_START + 83) // F053
#define DUMMY_NPC_HOUSE_079 (DUMMY_START + 84) // F054
#define DUMMY_NPC_HOUSE_080 (DUMMY_START + 85) // F055
#define DUMMY_NPC_HOUSE_081 (DUMMY_START + 86) // F056
#define DUMMY_NPC_HOUSE_082 (DUMMY_START + 87) // F057
#define DUMMY_NPC_HOUSE_083 (DUMMY_START + 88) // F058
#define DUMMY_NPC_HOUSE_084 (DUMMY_START + 89) // F059
#define DUMMY_NPC_HOUSE_085 (DUMMY_START + 90) // F05A
#define DUMMY_NPC_HOUSE_086 (DUMMY_START + 91) // F05B
#define DUMMY_NPC_HOUSE_087 (DUMMY_START + 92) // F05C
#define DUMMY_NPC_HOUSE_088 (DUMMY_START + 93) // F05D
#define DUMMY_NPC_HOUSE_089 (DUMMY_START + 94) // F05E
#define DUMMY_NPC_HOUSE_090 (DUMMY_START + 95) // F05F
#define DUMMY_NPC_HOUSE_091 (DUMMY_START + 96) // F060
#define DUMMY_NPC_HOUSE_092 (DUMMY_START + 97) // F061
#define DUMMY_NPC_HOUSE_093 (DUMMY_START + 98) // F062
#define DUMMY_NPC_HOUSE_094 (DUMMY_START + 99) // F063
#define DUMMY_NPC_HOUSE_095 (DUMMY_START + 100) // F064
#define DUMMY_NPC_HOUSE_096 (DUMMY_START + 101) // F065
#define DUMMY_NPC_HOUSE_097 (DUMMY_START + 102) // F066
#define DUMMY_NPC_HOUSE_098 (DUMMY_START + 103) // F067
#define DUMMY_NPC_HOUSE_099 (DUMMY_START + 104) // F068
#define DUMMY_NPC_HOUSE_100 (DUMMY_START + 105) // F069
#define DUMMY_NPC_HOUSE_101 (DUMMY_START + 106) // F06A
#define DUMMY_NPC_HOUSE_102 (DUMMY_START + 107) // F06B
#define DUMMY_NPC_HOUSE_103 (DUMMY_START + 108) // F06C
#define DUMMY_NPC_HOUSE_104 (DUMMY_START + 109) // F06D
#define DUMMY_NPC_HOUSE_105 (DUMMY_START + 110) // F06E
#define DUMMY_NPC_HOUSE_106 (DUMMY_START + 111) // F06F
#define DUMMY_NPC_HOUSE_107 (DUMMY_START + 112) // F070
#define DUMMY_NPC_HOUSE_108 (DUMMY_START + 113) // F071
#define DUMMY_NPC_HOUSE_109 (DUMMY_START + 114) // F072
#define DUMMY_NPC_HOUSE_110 (DUMMY_START + 115) // F073
#define DUMMY_NPC_HOUSE_111 (DUMMY_START + 116) // F074
#define DUMMY_NPC_HOUSE_112 (DUMMY_START + 117) // F075
#define DUMMY_NPC_HOUSE_113 (DUMMY_START + 118) // F076
#define DUMMY_NPC_HOUSE_114 (DUMMY_START + 119) // F077
#define DUMMY_NPC_HOUSE_115 (DUMMY_START + 120) // F078
#define DUMMY_NPC_HOUSE_116 (DUMMY_START + 121) // F079
#define DUMMY_NPC_HOUSE_117 (DUMMY_START + 122) // F07A
#define DUMMY_NPC_HOUSE_118 (DUMMY_START + 123) // F07B
#define DUMMY_NPC_HOUSE_119 (DUMMY_START + 124) // F07C
#define DUMMY_NPC_HOUSE_120 (DUMMY_START + 125) // F07D
#define DUMMY_NPC_HOUSE_121 (DUMMY_START + 126) // F07E
#define DUMMY_NPC_HOUSE_122 (DUMMY_START + 127) // F07F
#define DUMMY_NPC_HOUSE_123 (DUMMY_START + 128) // F080
#define DUMMY_NPC_HOUSE_124 (DUMMY_START + 129) // F081
#define DUMMY_NPC_HOUSE_125 (DUMMY_START + 130) // F082
#define DUMMY_NPC_HOUSE_126 (DUMMY_START + 131) // F083
#define DUMMY_NPC_HOUSE_127 (DUMMY_START + 132) // F084
#define DUMMY_NPC_HOUSE_128 (DUMMY_START + 133) // F085
#define DUMMY_NPC_HOUSE_129 (DUMMY_START + 134) // F086
#define DUMMY_NPC_HOUSE_130 (DUMMY_START + 135) // F087
#define DUMMY_NPC_HOUSE_131 (DUMMY_START + 136) // F088
#define DUMMY_NPC_HOUSE_132 (DUMMY_START + 137) // F089
#define DUMMY_NPC_HOUSE_133 (DUMMY_START + 138) // F08A
#define DUMMY_NPC_HOUSE_134 (DUMMY_START + 139) // F08B
#define DUMMY_NPC_HOUSE_135 (DUMMY_START + 140) // F08C
#define DUMMY_NPC_HOUSE_136 (DUMMY_START + 141) // F08D
#define DUMMY_NPC_HOUSE_137 (DUMMY_START + 142) // F08E
#define DUMMY_NPC_HOUSE_138 (DUMMY_START + 143) // F08F
#define DUMMY_NPC_HOUSE_139 (DUMMY_START + 144) // F090
#define DUMMY_NPC_HOUSE_140 (DUMMY_START + 145) // F091
#define DUMMY_NPC_HOUSE_141 (DUMMY_START + 146) // F092
#define DUMMY_NPC_HOUSE_142 (DUMMY_START + 147) // F093
#define DUMMY_NPC_HOUSE_143 (DUMMY_START + 148) // F094
#define DUMMY_NPC_HOUSE_144 (DUMMY_START + 149) // F095
#define DUMMY_NPC_HOUSE_145 (DUMMY_START + 150) // F096
#define DUMMY_NPC_HOUSE_146 (DUMMY_START + 151) // F097
#define DUMMY_NPC_HOUSE_147 (DUMMY_START + 152) // F098
#define DUMMY_NPC_HOUSE_148 (DUMMY_START + 153) // F099
#define DUMMY_NPC_HOUSE_149 (DUMMY_START + 154) // F09A
#define DUMMY_NPC_HOUSE_150 (DUMMY_START + 155) // F09B
#define DUMMY_NPC_HOUSE_151 (DUMMY_START + 156) // F09C
#define DUMMY_NPC_HOUSE_152 (DUMMY_START + 157) // F09D
#define DUMMY_NPC_HOUSE_153 (DUMMY_START + 158) // F09E
#define DUMMY_NPC_HOUSE_154 (DUMMY_START + 159) // F09F
#define DUMMY_NPC_HOUSE_155 (DUMMY_START + 160) // F0A0
#define DUMMY_NPC_HOUSE_156 (DUMMY_START + 161) // F0A1
#define DUMMY_NPC_HOUSE_157 (DUMMY_START + 162) // F0A2
#define DUMMY_NPC_HOUSE_158 (DUMMY_START + 163) // F0A3
#define DUMMY_NPC_HOUSE_159 (DUMMY_START + 164) // F0A4
#define DUMMY_NPC_HOUSE_160 (DUMMY_START + 165) // F0A5
#define DUMMY_NPC_HOUSE_161 (DUMMY_START + 166) // F0A6
#define DUMMY_NPC_HOUSE_162 (DUMMY_START + 167) // F0A7
#define DUMMY_NPC_HOUSE_163 (DUMMY_START + 168) // F0A8
#define DUMMY_NPC_HOUSE_164 (DUMMY_START + 169) // F0A9
#define DUMMY_NPC_HOUSE_165 (DUMMY_START + 170) // F0AA
#define DUMMY_NPC_HOUSE_166 (DUMMY_START + 171) // F0AB
#define DUMMY_NPC_HOUSE_167 (DUMMY_START + 172) // F0AC
#define DUMMY_NPC_HOUSE_168 (DUMMY_START + 173) // F0AD
#define DUMMY_NPC_HOUSE_169 (DUMMY_START + 174) // F0AE
#define DUMMY_NPC_HOUSE_170 (DUMMY_START + 175) // F0AF
#define DUMMY_NPC_HOUSE_171 (DUMMY_START + 176) // F0B0
#define DUMMY_NPC_HOUSE_172 (DUMMY_START + 177) // F0B1
#define DUMMY_NPC_HOUSE_173 (DUMMY_START + 178) // F0B2
#define DUMMY_NPC_HOUSE_174 (DUMMY_START + 179) // F0B3
#define DUMMY_NPC_HOUSE_175 (DUMMY_START + 180) // F0B4
#define DUMMY_NPC_HOUSE_176 (DUMMY_START + 181) // F0B5
#define DUMMY_NPC_HOUSE_177 (DUMMY_START + 182) // F0B6
#define DUMMY_NPC_HOUSE_178 (DUMMY_START + 183) // F0B7
#define DUMMY_NPC_HOUSE_179 (DUMMY_START + 184) // F0B8
#define DUMMY_NPC_HOUSE_180 (DUMMY_START + 185) // F0B9
#define DUMMY_NPC_HOUSE_181 (DUMMY_START + 186) // F0BA
#define DUMMY_NPC_HOUSE_182 (DUMMY_START + 187) // F0BB
#define DUMMY_NPC_HOUSE_183 (DUMMY_START + 188) // F0BC
#define DUMMY_NPC_HOUSE_184 (DUMMY_START + 189) // F0BD
#define DUMMY_NPC_HOUSE_185 (DUMMY_START + 190) // F0BE
#define DUMMY_NPC_HOUSE_186 (DUMMY_START + 191) // F0BF
#define DUMMY_NPC_HOUSE_187 (DUMMY_START + 192) // F0C0
#define DUMMY_NPC_HOUSE_188 (DUMMY_START + 193) // F0C1
#define DUMMY_NPC_HOUSE_189 (DUMMY_START + 194) // F0C2
#define DUMMY_NPC_HOUSE_190 (DUMMY_START + 195) // F0C3
#define DUMMY_NPC_HOUSE_191 (DUMMY_START + 196) // F0C4
#define DUMMY_NPC_HOUSE_192 (DUMMY_START + 197) // F0C5
#define DUMMY_NPC_HOUSE_193 (DUMMY_START + 198) // F0C6
#define DUMMY_NPC_HOUSE_194 (DUMMY_START + 199) // F0C7
#define DUMMY_NPC_HOUSE_195 (DUMMY_START + 200) // F0C8
#define DUMMY_NPC_HOUSE_196 (DUMMY_START + 201) // F0C9
#define DUMMY_NPC_HOUSE_197 (DUMMY_START + 202) // F0CA
#define DUMMY_NPC_HOUSE_198 (DUMMY_START + 203) // F0CB
#define DUMMY_NPC_HOUSE_199 (DUMMY_START + 204) // F0CC
#define DUMMY_NPC_HOUSE_200 (DUMMY_START + 205) // F0CD
#define DUMMY_NPC_HOUSE_201 (DUMMY_START + 206) // F0CE
#define DUMMY_NPC_HOUSE_202 (DUMMY_START + 207) // F0CF
#define DUMMY_NPC_HOUSE_203 (DUMMY_START + 208) // F0D0
#define DUMMY_NPC_HOUSE_204 (DUMMY_START + 209) // F0D1
#define DUMMY_NPC_HOUSE_205 (DUMMY_START + 210) // F0D2
#define DUMMY_NPC_HOUSE_206 (DUMMY_START + 211) // F0D3
#define DUMMY_NPC_HOUSE_207 (DUMMY_START + 212) // F0D4
#define DUMMY_NPC_HOUSE_208 (DUMMY_START + 213) // F0D5
#define DUMMY_NPC_HOUSE_209 (DUMMY_START + 214) // F0D6
#define DUMMY_NPC_HOUSE_210 (DUMMY_START + 215) // F0D7
#define DUMMY_NPC_HOUSE_211 (DUMMY_START + 216) // F0D8
#define DUMMY_NPC_HOUSE_212 (DUMMY_START + 217) // F0D9
#define DUMMY_NPC_HOUSE_213 (DUMMY_START + 218) // F0DA
#define DUMMY_NPC_HOUSE_214 (DUMMY_START + 219) // F0DB
#define DUMMY_NPC_HOUSE_215 (DUMMY_START + 220) // F0DC
#define DUMMY_NPC_HOUSE_216 (DUMMY_START + 221) // F0DD
#define DUMMY_NPC_HOUSE_217 (DUMMY_START + 222) // F0DE
#define DUMMY_NPC_HOUSE_218 (DUMMY_START + 223) // F0DF
#define DUMMY_NPC_HOUSE_219 (DUMMY_START + 224) // F0E0
#define DUMMY_NPC_HOUSE_220 (DUMMY_START + 225) // F0E1
#define DUMMY_NPC_HOUSE_221 (DUMMY_START + 226) // F0E2
#define DUMMY_NPC_HOUSE_222 (DUMMY_START + 227) // F0E3
#define DUMMY_NPC_HOUSE_223 (DUMMY_START + 228) // F0E4
#define DUMMY_NPC_HOUSE_224 (DUMMY_START + 229) // F0E5
#define DUMMY_NPC_HOUSE_225 (DUMMY_START + 230) // F0E6
#define DUMMY_NPC_HOUSE_226 (DUMMY_START + 231) // F0E7
#define DUMMY_NPC_HOUSE_227 (DUMMY_START + 232) // F0E8
#define DUMMY_NPC_HOUSE_228 (DUMMY_START + 233) // F0E9
#define DUMMY_NPC_HOUSE_229 (DUMMY_START + 234) // F0EA
#define DUMMY_NPC_HOUSE_230 (DUMMY_START + 235) // F0EB
#define DUMMY_NPC_HOUSE_231 (DUMMY_START + 236) // F0EC
#define DUMMY_NPC_HOUSE_232 (DUMMY_START + 237) // F0ED
#define DUMMY_NPC_HOUSE_233 (DUMMY_START + 238) // F0EE
#define DUMMY_NPC_HOUSE_234 (DUMMY_START + 239) // F0EF
#define DUMMY_NPC_HOUSE_235 (DUMMY_START + 240) // F0F0
#define DUMMY_NPC_HOUSE_236 (DUMMY_START + 241) // F0F1
#define DUMMY_NPC_HOUSE_237 (DUMMY_START + 242) // F0F2
#define DUMMY_NPC_HOUSE_END (DUMMY_START + 242) // F0F2
#define DUMMY_HOUSE0 0xF0F3
#define DUMMY_HOUSE1 0xF0F4
#define DUMMY_HOUSE2 0xF0F5
#define DUMMY_HOUSE3 0xF0F6
#define DUMMY_SHOP0 0xF0F7
#define DUMMY_SHOP1 0xF0F8
#define DUMMY_SHOP2 0xF0F9
#define DUMMY_SHOP3 0xF0FA
#define DUMMY_HANIWA0 0xF0FB
#define DUMMY_HANIWA1 (DUMMY_HANIWA0 + 1)
#define DUMMY_HANIWA2 (DUMMY_HANIWA1 + 1)
#define DUMMY_HANIWA3 (DUMMY_HANIWA2 + 1)
#define DUMMY_POST_OFFICE 0xF0FF
#define DUMMY_NEEDLEWORK_SHOP 0xF0FF
#define DUMMY_STATION 0xF100
#define DUMMY_POLICE_STATION 0xF101
#define DUMMY_RESERVE 0xF102
#define DUMMY_SHRINE 0xF103
#define DUMMY_BROKER_SHOP 0xF104
#define DUMMY_BUGGY 0xF105
#define DUMMY_CAR 0xF106
#define DUMMY_KAMAKURA 0xF107
#define DUMMY_GOZA 0xF108
#define DUMMY_RADIO 0xF109
#define DUMMY_YATAI 0xF10A
#define DUMMY_TUKIMI 0xF10A
#define DUMMY_MIKUJI 0xF10D
#define DUMMY_TAMA 0xF110
#define DUMMY_TURI 0xF111
#define DUMMY_KOINOBORI 0xF114
#define DUMMY_WINDMILL 0xF116
#define DUMMY_LOTUS 0xF11B
#define DUMMY_MIKANBOX 0xF11C
#define DUMMY_DOUZOU 0xF11D
#define DUMMY_NAMEPLATE 0xF11F
#define DUMMY_MUSEUM 0xF120
#define DUMMY_BRIDGE 0xF121
#define DUMMY_FLAG 0xF122
#define DUMMY_COTTAGE_MY 0xF123
#define DUMMY_COTTAGE_NPC 0xF124
#define DUMMY_GHOG 0xF125
#define DUMMY_HTABLE 0xF126
#define DUMMY_TENT 0xF127
#define DUMMY_BOAT 0xF128
#define RSV_POLICE_ITEM_0 0xF128 // why is this duplicated?
#define RSV_POLICE_ITEM_1 0xF129
#define RSV_POLICE_ITEM_2 0xF12A
#define RSV_POLICE_ITEM_3 0xF12B
#define RSV_POLICE_ITEM_4 0xF12C
#define RSV_POLICE_ITEM_5 0xF12D
#define RSV_POLICE_ITEM_6 0xF12E
#define RSV_POLICE_ITEM_7 0xF12F
#define RSV_POLICE_ITEM_8 0xF130
#define RSV_POLICE_ITEM_9 0xF131
#define RSV_POLICE_ITEM_10 0xF132
#define RSV_POLICE_ITEM_11 0xF133
#define RSV_POLICE_ITEM_12 0xF134
#define RSV_POLICE_ITEM_13 0xF135
#define RSV_POLICE_ITEM_14 0xF136
#define RSV_POLICE_ITEM_15 0xF137
#define RSV_POLICE_ITEM_16 0xF138
#define RSV_POLICE_ITEM_17 0xF139
#define RSV_POLICE_ITEM_18 0xF13A
#define RSV_POLICE_ITEM_19 0xF13B
#define RSV_POLICE_ITEM_20 0xF13C
#define RSV_POLICE_ITEM_21 0xF13D
#define RSV_POLICE_ITEM_22 0xF13E
#define RSV_POLICE_ITEM_23 0xF13F
#define RSV_POLICE_ITEM_24 0xF140
#define RSV_POLICE_ITEM_25 0xF141
#define RSV_POLICE_ITEM_26 0xF142
#define RSV_POLICE_ITEM_27 0xF143
#define RSV_POLICE_ITEM_28 0xF144
#define RSV_POLICE_ITEM_29 0xF145
#define RSV_POLICE_ITEM_30 0xF146
#define RSV_POLICE_ITEM_31 0xF147
#define RSV_POLICE_ITEM_END 0xF148

#define RSV_SHOP_PAPER 0xFE00
#define RSV_SHOP_CLOTH 0xFE01
#define RSV_SHOP_FTR 0xFE02
#define RSV_SHOP_CARPET 0xFE03
#define RSV_SHOP_WALL 0xFE04
#define RSV_SHOP_HALLOWEEN 0xFE05
#define RSV_SHOP_TOOL 0xFE06
#define RSV_SHOP_EVENT 0xFE07
#define RSV_SHOP_PLANT 0xFE08
#define RSV_SHOP_RARE 0xFE09
#define RSV_SHOP_UMBRELLA 0xFE0A
#define RSV_SHOP_PAINT 0xFE0B
#define RSV_SHOP_SIGNBOARD 0xFE0C
#define RSV_SHOP_FE0D 0xFE0D
#define RSV_SHOP_SOLD_PAPER 0xFE0E
#define RSV_SHOP_SOLD_CLOTH 0xFE0F
#define RSV_SHOP_SOLD_FTR 0xFE10
#define RSV_SHOP_SOLD_CARPET 0xFE11
#define RSV_SHOP_SOLD_WALL 0xFE12
#define RSV_SHOP_SOLD_PLANT 0xFE13
#define RSV_SHOP_SOLD_TOOL 0xFE14
#define RSV_SHOP_SOLD_RARE 0xFE15
#define RSV_SHOP_SOLD_UMBRELLA 0xFE16
#define RSV_SHOP_SOLD_PAINT 0xFE17
#define RSV_SHOP_SOLD_SIGNBOARD 0xFE18
#define RSV_HOLE 0xFE19
#define RSV_TREE 0xFE1A
#define RSV_DOOR 0xFE1B
#define RSV_FE1C 0xFE1C
#define RSV_BRIDGE0 0xFE1D
#define RSV_BRIDGE1 0xFE1E
#define RSV_FE1F 0xFE1F
#define RSV_CLOTH 0xFE20
#define RSV_CLOTH1 0xFE21
#define RSV_CLOTH2 0xFE22
#define RSV_CLOTH3 0xFE23
#define RSV_CLOTH4 0xFE24
#define RSV_CLOTH5 0xFE25
#define RSV_CLOTH6 0xFE26
#define RSV_CLOTH7 0xFE27
#define RSV_SIGNBOARD 0xFE30
#define RSV_NW_ORIGINAL0 0xFE31
#define RSV_NW_ORIGINAL1 0xFE32
#define RSV_NW_ORIGINAL2 0xFE33
#define RSV_NW_ORIGINAL3 0xFE34
#define RSV_NW_ORIGINAL4 0xFE35
#define RSV_NW_ORIGINAL5 0xFE36
#define RSV_NW_ORIGINAL6 0xFE37
#define RSV_NW_ORIGINAL7 0xFE38
#define RSV_CPORIGINAL_FLD0_00 0xFE39
#define RSV_CPORIGINAL_FLD0_01 0xFE3A
#define RSV_CPORIGINAL_FLD0_02 0xFE3B
#define RSV_CPORIGINAL_FLD0_03 0xFE3C
#define RSV_CPORIGINAL_FLD0_04 0xFE3D
#define RSV_CPORIGINAL_FLD0_05 0xFE3E
#define RSV_CPORIGINAL_FLD0_06 0xFE3F
#define RSV_CPORIGINAL_FLD0_07 0xFE40
#define RSV_CPORIGINAL_FLD0_08 0xFE41
#define RSV_CPORIGINAL_FLD0_09 0xFE42
#define RSV_CPORIGINAL_FLD0_10 0xFE43
#define RSV_CPORIGINAL_FLD0_11 0xFE44
#define RSV_CPORIGINAL_FLD1_00 0xFE45
#define RSV_CPORIGINAL_FLD1_01 0xFE46
#define RSV_CPORIGINAL_FLD1_02 0xFE47
#define RSV_CPORIGINAL_FLD1_03 0xFE48
#define RSV_CPORIGINAL_FLD1_04 0xFE49
#define RSV_CPORIGINAL_FLD1_05 0xFE4A
#define RSV_CPORIGINAL_FLD1_06 0xFE4B
#define RSV_CPORIGINAL_FLD1_07 0xFE4C
#define RSV_CPORIGINAL_FLD1_08 0xFE4D
#define RSV_CPORIGINAL_FLD1_09 0xFE4E
#define RSV_CPORIGINAL_FLD1_10 0xFE4F
#define RSV_CPORIGINAL_FLD1_11 0xFE50
#define RSV_CPORIGINAL_FLD2_00 0xFE51
#define RSV_CPORIGINAL_FLD2_01 0xFE52
#define RSV_CPORIGINAL_FLD2_02 0xFE53
#define RSV_CPORIGINAL_FLD2_03 0xFE54
#define RSV_CPORIGINAL_FLD2_04 0xFE55
#define RSV_CPORIGINAL_FLD2_05 0xFE56
#define RSV_CPORIGINAL_FLD2_06 0xFE57
#define RSV_CPORIGINAL_FLD2_07 0xFE58
#define RSV_CPORIGINAL_FLD2_08 0xFE59
#define RSV_CPORIGINAL_FLD2_09 0xFE5A
#define RSV_CPORIGINAL_FLD2_10 0xFE5B
#define RSV_CPORIGINAL_FLD2_11 0xFE5C
#define RSV_CPORIGINAL_FLD3_00 0xFE5D
#define RSV_CPORIGINAL_FLD3_01 0xFE5E
#define RSV_CPORIGINAL_FLD3_02 0xFE5F
#define RSV_CPORIGINAL_FLD3_03 0xFE60
#define RSV_CPORIGINAL_FLD3_04 0xFE61
#define RSV_CPORIGINAL_FLD3_05 0xFE62
#define RSV_CPORIGINAL_FLD3_06 0xFE63
#define RSV_CPORIGINAL_FLD3_07 0xFE64
#define RSV_CPORIGINAL_FLD3_08 0xFE65
#define RSV_CPORIGINAL_FLD3_09 0xFE66
#define RSV_CPORIGINAL_FLD3_10 0xFE67
#define RSV_CPORIGINAL_FLD3_11 0xFE68
#define RSV_CPORIGINAL_FLD4_00 0xFE69
#define RSV_CPORIGINAL_FLD4_01 0xFE6A
#define RSV_CPORIGINAL_FLD4_02 0xFE6B
#define RSV_CPORIGINAL_FLD4_03 0xFE6C
#define RSV_CPORIGINAL_FLD4_04 0xFE6D
#define RSV_CPORIGINAL_FLD4_05 0xFE6E
#define RSV_CPORIGINAL_FLD4_06 0xFE6F
#define RSV_CPORIGINAL_FLD4_07 0xFE70
#define RSV_CPORIGINAL_FLD4_08 0xFE71
#define RSV_CPORIGINAL_FLD4_09 0xFE72
#define RSV_CPORIGINAL_FLD4_10 0xFE73
#define RSV_CPORIGINAL_FLD4_11 0xFE74
#define RSV_CPORIGINAL_FLD5_00 0xFE75
#define RSV_CPORIGINAL_FLD5_01 0xFE76
#define RSV_CPORIGINAL_FLD5_02 0xFE77
#define RSV_CPORIGINAL_FLD5_03 0xFE78
#define RSV_CPORIGINAL_FLD5_04 0xFE79
#define RSV_CPORIGINAL_FLD5_05 0xFE7A
#define RSV_CPORIGINAL_FLD5_06 0xFE7B
#define RSV_CPORIGINAL_FLD5_07 0xFE7C
#define RSV_CPORIGINAL_FLD5_08 0xFE7D
#define RSV_CPORIGINAL_FLD5_09 0xFE7E
#define RSV_CPORIGINAL_FLD5_10 0xFE7F
#define RSV_CPORIGINAL_FLD5_11 0xFE80
#define RSV_CPORIGINAL_FLD6_00 0xFE81
#define RSV_CPORIGINAL_FLD6_01 0xFE82
#define RSV_CPORIGINAL_FLD6_02 0xFE83
#define RSV_CPORIGINAL_FLD6_03 0xFE84
#define RSV_CPORIGINAL_FLD6_04 0xFE85
#define RSV_CPORIGINAL_FLD6_05 0xFE86
#define RSV_CPORIGINAL_FLD6_06 0xFE87
#define RSV_CPORIGINAL_FLD6_07 0xFE88
#define RSV_CPORIGINAL_FLD6_08 0xFE89
#define RSV_CPORIGINAL_FLD6_09 0xFE8A
#define RSV_CPORIGINAL_FLD6_10 0xFE8B
#define RSV_CPORIGINAL_FLD6_11 0xFE8C
#define RSV_CPORIGINAL_FLD7_00 0xFE8D
#define RSV_CPORIGINAL_FLD7_01 0xFE8E
#define RSV_CPORIGINAL_FLD7_02 0xFE8F
#define RSV_CPORIGINAL_FLD7_03 0xFE90
#define RSV_CPORIGINAL_FLD7_04 0xFE91
#define RSV_CPORIGINAL_FLD7_05 0xFE92
#define RSV_CPORIGINAL_FLD7_06 0xFE93
#define RSV_CPORIGINAL_FLD7_07 0xFE94
#define RSV_CPORIGINAL_FLD7_08 0xFE95
#define RSV_CPORIGINAL_FLD7_09 0xFE96
#define RSV_CPORIGINAL_FLD7_10 0xFE97
#define RSV_CPORIGINAL_FLD7_11 0xFE98
#define RSV_GBAORIGINAL0 0xFE99
#define RSV_GBAORIGINAL1 0xFE9A
#define RSV_GBAORIGINAL2 0xFE9B
#define RSV_GBAORIGINAL3 0xFE9C
#define RSV_GBAORIGINAL4 0xFE9D
#define RSV_GBAORIGINAL5 0xFE9E
#define RSV_GBAORIGINAL6 0xFE9F
#define RSV_GBAORIGINAL7 0xFEA0
#define RSV_ISLAND_FTR0 0xFEB3  /* mRmTp_FTRSIZE_1x1 S */
#define RSV_ISLAND_FTR1 0xFEB4  /* mRmTp_FTRSIZE_1x1 E */
#define RSV_ISLAND_FTR2 0xFEB5  /* mRmTp_FTRSIZE_1x1 N */
#define RSV_ISLAND_FTR3 0xFEB6  /* mRmTp_FTRSIZE_1x1 W */
#define RSV_ISLAND_FTR4 0xFEB7  /* mRmTp_FTRSIZE_1x1 S */
#define RSV_ISLAND_FTR5 0xFEB8  /* mRmTp_FTRSIZE_1x1 E */
#define RSV_ISLAND_FTR6 0xFEB9  /* mRmTp_FTRSIZE_1x1 N */
#define RSV_ISLAND_FTR7 0xFEBA  /* mRmTp_FTRSIZE_1x1 W */
#define RSV_ISLAND_FTR8 0xFEBB  /* mRmTp_FTRSIZE_1x2 S */
#define RSV_ISLAND_FTR9 0xFEBC  /* mRmTp_FTRSIZE_1x2 E */
#define RSV_ISLAND_FTR10 0xFEBD /* mRmTp_FTRSIZE_1x2 N */
#define RSV_ISLAND_FTR11 0xFEBE /* mRmTp_FTRSIZE_1x2 W */
#define RSV_ISLAND_FTR12 0xFEBF /* mRmTp_FTRSIZE_2x2 S */
#define RSV_ISLAND_FTR13 0xFEC0 /* mRmTp_FTRSIZE_2x2 E */
#define RSV_ISLAND_FTR14 0xFEC1 /* mRmTp_FTRSIZE_2x2 N */
#define RSV_ISLAND_FTR15 0xFEC2 /* mRmTp_FTRSIZE_2x2 W */
#define RSV_WALL_NO 0xFFFE /* interior wall item, no collision */
#define RSV_NO 0xFFFF /* reserved space, can't interact but no collision */

#define mNT_IS_RESERVE(n) ((n) >= SIGN00 && (n) <= SIGN20)

// clang-format on

#ifdef __cplusplus
}
#endif

#endif
