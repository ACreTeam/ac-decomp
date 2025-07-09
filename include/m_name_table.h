#ifndef M_NAME_TABLE_H
#define M_NAME_TABLE_H

#include "types.h"
#include "m_actor_type.h"
#include "m_collision_bg.h"
#include "m_name_table_floor_decl.h"
#include "m_name_table_wall_decl.h"
#include "m_ftr_def.h"

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

// #define FTR_NUM 1266
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

#define ITEM_IS_RSVPOLICE(n) ((n) >= RSV_POLICE_ITEM_0 && (n) < RSV_POLICE_ITEM_END)

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
#define IS_ITEM_GROWN_FLOWER(item) ((item) >= FLOWER_PANSIES0 && (item) <= FLOWER_TULIP2)
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

#define FTR_START(x) (x##_SOUTH)
#define FTR_END(x) (x##_WEST)

enum {
#define X(e) \
    e##_SOUTH, \
    e##_EAST, \
    e##_NORTH, \
    e##_WEST

    ___FTR0_START = FTR0_START-1,
    X(FTR_SUM_HAL_CHEST02),
    X(FTR_SUM_CLCHEST03),
    X(FTR_SUM_BLUE_BUREAU01),
    X(FTR_KOB_LOCKER1),
    X(FTR_SUM_X_CHEST01),
    X(FTR_SUM_WHI_CHEST02),
    X(FTR_SUM_RATAN_CHEST02),
    X(FTR_SUM_LOG_CHEST02),
    X(FTR_SUM_LICCACHEST),
    X(FTR_SUM_GRE_CHEST02),
    X(FTR_SUM_FRUITCHEST03),
    X(FTR_SUM_CONT_CHEST02),
    X(FTR_SUM_BLUE_CAB01),
    X(FTR_SUM_BLA_CHEST03),
    X(FTR_SUM_ASI_CHEST03),
    X(FTR_SUM_X_CHEST02),
    X(FTR_SUM_WHI_CHEST01),
    X(FTR_SUM_RATAN_CHEST01),
    X(FTR_SUM_LOG_CHEST01),
    X(FTR_SUM_LICCALOWCHEST),
    X(FTR_SUM_HAL_CHEST03),
    X(FTR_SUM_GRE_CHEST03),
    X(FTR_SUM_FRUITCHEST01),
    X(FTR_SUM_CONT_CHEST03),
    X(FTR_SUM_CLASSICCHEST01),
    X(FTR_SUM_BLUE_LOWCHEST01),
    X(FTR_SUM_BLA_CHEST01),
    X(FTR_SUM_ASI_CHEST02),
    X(FTR_NOG_TRI_CHEST01),
    X(FTR_NOG_TRI_CHEST02),
    X(FTR_NOG_TRI_CHEST03),
    X(FTR_NKH_BOX01),
    X(FTR_IKE_JPN_STEP01),
    X(FTR_IKE_JPN_SAI01),
    X(FTR_NOG_FAN01),
    X(FTR_NKH_LIGHT01),
    X(FTR_NKH_TABLE01),
    X(FTR_NKH_TABLE02),
    X(FTR_NKH_WALL01),
    X(FTR_NKH_ZAB01),
    X(FTR_NKH_BOARD01),
    X(FTR_ARI_ISU01),
    X(FTR_ARI_TABLE01),
    X(FTR_ARI_REIZOU01),
    X(FTR_SUM_CHEST01),
    X(FTR_SUM_CHEST02),
    X(FTR_SUM_SOFE01),
    X(FTR_SUM_SOFE02),
    X(FTR_IKE_JPN_HIBATI01),
    X(FTR_ARI_KITCHEN01),
    X(FTR_SUM_SOFE03),
    X(FTR_IKE_JPN_TANSU01),
    X(FTR_IKE_JPN_KOTATU01),
    X(FTR_IKE_JPN_KOTATU02),
    X(FTR_SUM_GUITAR01),
    X(FTR_SUM_GUITAR02),
    X(FTR_SUM_GUITAR03),
    X(FTR_SUM_DOLL01),
    X(FTR_SUM_DOLL02),
    X(FTR_SUM_DOLL03),
    X(FTR_SUM_DOLL04),
    X(FTR_SUM_CLASSICCABINET01),
    X(FTR_SUM_CLASSICCHAIR01),
    X(FTR_SUM_CLASSICCHEST02),
    X(FTR_SUM_CLASSICTABLE01),
    X(FTR_SUM_CLASSICWARDROPE01),
    X(FTR_SUM_CLCHAIR02),
    X(FTR_SUM_CUPBOARD01),
    X(FTR_SUM_DESK01),
    X(FTR_SUM_DOLL05),
    X(FTR_SUM_DOLL06),
    X(FTR_SUM_DOLL07),
    X(FTR_SUM_DOLL08),
    X(FTR_SUM_DOLL09),
    X(FTR_SUM_DOLL10),
    X(FTR_SUM_GLOBE01),
    X(FTR_SUM_KITCHAIR01),
    X(FTR_SUM_KITTABLE01),
    X(FTR_SUM_TV01),
    X(FTR_SUM_TOTEMP01),
    X(FTR_SUM_TOTEMP02),
    X(FTR_SUM_TOTEMP03),
    X(FTR_SUM_TOTEMP04),
    X(FTR_SUM_TAIKO01),
    X(FTR_SUM_STOVE01),
    X(FTR_SUM_STEREO01),
    X(FTR_SUM_RATAN_ISU01),
    X(FTR_SUM_OLDSOFA01),
    X(FTR_SUM_LICCATABLE),
    X(FTR_SUM_LICCASOFA),
    X(FTR_SUM_LICCAPIANO),
    X(FTR_SUM_LICCALANP),
    X(FTR_SUM_LICCAKITCHEN),
    X(FTR_SUM_LICCACHAIR),
    X(FTR_SUM_LICCABED),
    X(FTR_SUM_OLDCLK01),
    X(FTR_SUM_RATAN_BED01),
    X(FTR_SUM_GOLFBAG01),
    X(FTR_SUM_GOLFBAG02),
    X(FTR_SUM_GOLFBAG03),
    X(FTR_SUM_BOOKCHT01),
    X(FTR_SUM_CHAIR01),
    X(FTR_SUM_CONT_SOFA01),
    X(FTR_SUM_CONT_SOFA02),
    X(FTR_SUM_CONT_TABLE01),
    X(FTR_SUM_CONT_CAB01),
    X(FTR_SUM_CONT_CHEST01),
    X(FTR_SUM_CONT_CHAIR01),
    X(FTR_SUM_CONT_BED01),
    X(FTR_SUM_CONT_TABLE02),
    X(FTR_SUM_COMP01),
    X(FTR_KOB_JIMUDESK),
    X(FTR_KOB_MASTERSWORD),
    X(FTR_KOB_NCUBE),
    X(FTR_SUM_TEKIN01),
    X(FTR_SUM_BIWA01),
    X(FTR_SUM_CONGA01),
    X(FTR_SUM_SHOUKAKI),
    X(FTR_SUM_COL_CHAIR01),
    X(FTR_SUM_COL_CHAIR02),
    X(FTR_SUM_COL_CHAIR03),
    X(FTR_SUM_CONPO01),
    X(FTR_KOB_PIPEISU),
    X(FTR_SUM_LICCAMIRROR),
    X(FTR_SUM_PET01),
    X(FTR_SUM_TIMPANI01),
    X(FTR_SUM_SPIKA01),
    X(FTR_SUM_BDCAKE01),
    X(FTR_KOB_S_DESK1),
    X(FTR_KOB_S_DESK2),
    X(FTR_KOB_S_DESK3),
    X(FTR_SUM_SABO01),
    X(FTR_SUM_SABO02),
    X(FTR_SUM_CLBED02),
    X(FTR_SUM_TV02),
    X(FTR_SUM_LICCALOWTABLE),
    X(FTR_SUM_KADOMATU),
    X(FTR_SUM_KAGAMOCHI),
    X(FTR_SUM_TOURO01),
    X(FTR_SUM_TOURO02),
    X(FTR_SUM_TOURO03),
    X(FTR_KOB_JIMUISU),
    X(FTR_KOB_GETABAKO1),
    X(FTR_KOB_GETABAKO2),
    X(FTR_KOB_S_ISU1),
    X(FTR_KOB_S_ISU2),
    X(FTR_KOB_S_ISU3),
    X(FTR_KOB_RIKA_DESK),
    X(FTR_KOB_TYOUREIDAI),
    X(FTR_SUM_TOURO04),
    X(FTR_SUM_TARU01),
    X(FTR_SUM_TARU02),
    X(FTR_KOB_TOBIBAKO),
    X(FTR_KON_TUKUE),
    X(FTR_SUM_MEZACLOCK),
    X(FTR_SUM_POPTABLE01),
    X(FTR_SUM_POPTABLE02),
    X(FTR_SUM_POPTABLE03),
    X(FTR_KON_TUBO),
    X(FTR_SUM_POPCHAIR01),
    X(FTR_SUM_POPCHAIR02),
    X(FTR_SUM_POPCHAIR03),
    X(FTR_SUM_SUBERI01),
    X(FTR_SUM_WC01),
    X(FTR_SUM_WC02),
    X(FTR_TAK_TABLE02),
    X(FTR_TAK_ISU03),
    X(FTR_KON_TUBO2),
    X(FTR_KON_TUBO3),
    X(FTR_SUM_MISIN01),
    X(FTR_SUM_BILLIADS),
    X(FTR_SUM_ART01),
    X(FTR_IKE_ART_ANG),
    X(FTR_IKE_ART_SYA),
    X(FTR_SUM_ART04),
    X(FTR_SUM_ART05),
    X(FTR_SUM_ART06),
    X(FTR_IKE_ART_FEL),
    X(FTR_SUM_ART08),
    X(FTR_SUM_ART09),
    X(FTR_SUM_ART10),
    X(FTR_SUM_ART11),
    X(FTR_SUM_ART12),
    X(FTR_SUM_ART13),
    X(FTR_SUM_ART14),
    X(FTR_SUM_ART15),
    X(FTR_SUM_FRUITBED01),
    X(FTR_SUM_FRUITCHAIR01),
    X(FTR_SUM_FRUITCHEST02),
    X(FTR_SUM_FRUITTABLE01),
    X(FTR_SUM_FRUITTV01),
    X(FTR_SUM_TAKKYU),
    X(FTR_SUM_HARP),
    X(FTR_SUM_LOG_HATOCLK),
    X(FTR_SUM_KISHA),
    X(FTR_SUM_MIZUNOMI),
    X(FTR_SUM_OKIAGARI01),
    X(FTR_SUM_SARU),
    X(FTR_SUM_SLOT),
    X(FTR_SUM_ASI_CHAIR01),
    X(FTR_SUM_ASI_CHAIR02),
    X(FTR_SUM_ASI_CHEST01),
    X(FTR_SUM_ASI_LANP01),
    X(FTR_SUM_PL_CALADIUM01),
    X(FTR_SUM_PL_SHUROCI),
    X(FTR_SUM_ASI_SCREEN01),
    X(FTR_SUM_ASI_TABLE01),
    X(FTR_SUM_ASI_TAIKO),
    X(FTR_SUM_BLA_BED01),
    X(FTR_BLA_CHAIR01),
    X(FTR_SUM_BLA_CHEST02),
    X(FTR_SUM_BLA_DESK01),
    X(FTR_SUM_BLA_SOFA02),
    X(FTR_SUM_BLA_TABLE01),
    X(FTR_SUM_BLUE_BED01),
    X(FTR_SUM_BLUE_BENCH01),
    X(FTR_SUM_BLUE_CHAIR01),
    X(FTR_SUM_BLUE_CHEST01),
    X(FTR_SUM_BLUE_CHEST02),
    X(FTR_SUM_BLUE_TABLE01),
    X(FTR_SUM_GRE_BED01),
    X(FTR_SUM_GRE_CHAIR01),
    X(FTR_SUM_GRE_CHAIR02),
    X(FTR_SUM_GRE_CHEST01),
    X(FTR_SUM_GRE_COUNTER01),
    X(FTR_SUM_GRE_LANP01),
    X(FTR_SUM_GRE_TABLE01),
    X(FTR_SUM_LOG_BED01),
    X(FTR_SUM_LOG_CHAIR01),
    X(FTR_SUM_LOG_CHAIR02),
    X(FTR_SUM_LOG_CHEST03),
    X(FTR_SUM_LOG_TABLE01),
    X(FTR_SUM_PL_ALOE01),
    X(FTR_SUM_PL_ANANAS),
    X(FTR_SUM_PL_COCOS),
    X(FTR_SUM_PL_COMPACTA),
    X(FTR_SUM_PL_DRACAENA),
    X(FTR_SUM_PL_GOMUNOKI),
    X(FTR_SUM_PL_POTHOS),
    X(FTR_SUM_PL_YAMAYASI),
    X(FTR_SUM_FRUITTABLE02),
    X(FTR_SUM_FRUITCHAIR02),
    X(FTR_SUM_PL_BENJYAMI),
    X(FTR_SUM_PL_DRACA02),
    X(FTR_SUM_PL_KUROTON),
    X(FTR_SUM_PL_PAKILA),
    X(FTR_SUM_PL_HIRASABO),
    X(FTR_TAK_METRO),
    X(FTR_KON_SISIODOSI),
    X(FTR_SUM_BON_MATU01),
    X(FTR_SUM_BON_MATU02),
    X(FTR_TAK_BARBER),
    X(FTR_SUM_BON_MATU03),
    X(FTR_SUM_BON_UME),
    X(FTR_NOG_DARUMAL),
    X(FTR_NOG_DARUMAM),
    X(FTR_NOG_DARUMAS),
    X(FTR_SUM_BON_BOKE),
    X(FTR_SUM_BON_SATUKI),
    X(FTR_SUM_BON_SANSHU),
    X(FTR_KON_CRACKER),
    X(FTR_TAK_CONE01),
    X(FTR_TAK_CONE02),
    X(FTR_TAK_CONE03),
    X(FTR_KON_JIHANKI01),
    X(FTR_SUM_BON_MOMIJI),
    X(FTR_SUM_BON_PIRA),
    X(FTR_SUM_BON_TURU),
    X(FTR_TAK_FENCE01),
    X(FTR_TAK_FENCE02),
    X(FTR_TAK_FENCE03),
    X(FTR_TAK_FENCE04),
    X(FTR_KON_JIHANKI02),
    X(FTR_TAK_HOLE01),
    X(FTR_KON_JIHANKI03),
    X(FTR_TAK_DRUM01),
    X(FTR_TAK_DRUM02),
    X(FTR_TAK_DRUM03),
    X(FTR_KON_JIHANKI04),
    X(FTR_TAK_TEKKIN),
    X(FTR_KON_GOMI01),
    X(FTR_KON_GOMI02),
    X(FTR_SUM_FRUITCHAIR03),
    X(FTR_SUM_FRUITCHAIR04),
    X(FTR_SUM_FRUITTABLE03),
    X(FTR_TAK_UDEFURI),
    X(FTR_KON_GOMI03),
    X(FTR_KON_GOMI04),
    X(FTR_SUM_VIOLA01),
    X(FTR_SUM_BASS01),
    X(FTR_SUM_CELLO01),
    X(FTR_SUM_PIANO01),
    X(FTR_KON_CHOUZU01),
    X(FTR_TAK_NEKO),
    X(FTR_KON_CHOUZU02),
    X(FTR_SUM_HAL_PKIN),
    X(FTR_TAK_DENKO),
    X(FTR_TAK_YAJI),
    X(FTR_KON_ISI01),
    X(FTR_KON_ISI02),
    X(FTR_TAK_KANBAN01),
    X(FTR_TAK_KANBAN02),
    X(FTR_TAK_KANBAN03),
    X(FTR_KON_CHOUZU03),
    X(FTR_SUM_HAL_BED01),
    X(FTR_SUM_HAL_BOX01),
    X(FTR_SUM_HAL_CHAIR01),
    X(FTR_SUM_GST_CHAIR01),
    X(FTR_SUM_HAL_CHEST01),
    X(FTR_SUM_HAL_SOFA01),
    X(FTR_SUM_HAL_TABLE01),
    X(FTR_TAK_APOLLO1),
    X(FTR_TAK_EISEI),
    X(FTR_KON_ISI03),
    X(FTR_KON_ISI04),
    X(FTR_KON_ISI05),
    X(FTR_TAK_UFO),
    X(FTR_KON_ISI06),
    X(FTR_KON_POUND),
    X(FTR_TAK_ROCKET1),
    X(FTR_TAK_ASTRO),
    X(FTR_SUM_HAL_CLK01),
    X(FTR_SUM_HAL_LANP01),
    X(FTR_SUM_ASI_BED01),
    X(FTR_SUM_ASI_TABLE02),
    X(FTR_TAK_ASTEROID1),
    X(FTR_SUM_RATAN_LANP),
    X(FTR_SUM_RATAN_TABLE01),
    X(FTR_KON_OKE),
    X(FTR_KON_TAIJU),
    X(FTR_KON_ARAIBA),
    X(FTR_KON_HUROISU),
    X(FTR_SUM_RATAN_SCREEN),
    X(FTR_SUM_RATAN_MIRROR),
    X(FTR_SUM_RATAN_ISU02),
    X(FTR_SUM_RATAN_CHEST03),
    X(FTR_TAK_ARWING),
    X(FTR_TAK_MOONCAR),
    X(FTR_KON_MASAJI),
    X(FTR_KON_MAT),
    X(FTR_KON_YUBUNE),
    X(FTR_SUM_BLUE_CLK),
    X(FTR_TAK_MOTI),
    X(FTR_SUM_HAL_MIRROR01),
    X(FTR_SUM_GRE_DESK01),
    X(FTR_KON_BANDAI),
    X(FTR_SUM_BLA_CHAIR02),
    X(FTR_SUM_BLA_TABLE02),
    X(FTR_TAK_STATION),
    X(FTR_KON_TUITATE),
    X(FTR_SUM_LOG_CHAIR03),
    X(FTR_SUM_WHI_BED01),
    X(FTR_TAK_SHUTTLE),
    X(FTR_SUM_WHI_MIRROR),
    X(FTR_SUM_WHI_SOFA01),
    X(FTR_SUM_WHI_LANP),
    X(FTR_SUM_LOG_TABLE02),
    X(FTR_KON_LOCKER),
    X(FTR_KON_MILK),
    X(FTR_SUM_UWA_CUP01),
    X(FTR_SUM_UWA_POTO01),
    X(FTR_SUM_UWA_VASE01),
    X(FTR_SUM_UWA_VASE02),
    X(FTR_SUM_UWA_VASE03),
    X(FTR_HNW_COMMON000),
    X(FTR_HNW_COMMON001),
    X(FTR_HNW_COMMON002),
    X(FTR_HNW_COMMON003),
    X(FTR_HNW_COMMON004),
    X(FTR_HNW_COMMON005),
    X(FTR_HNW_COMMON006),
    X(FTR_HNW_COMMON007),
    X(FTR_HNW_COMMON008),
    X(FTR_HNW_COMMON009),
    X(FTR_HNW_COMMON010),
    X(FTR_HNW_COMMON011),
    X(FTR_HNW_COMMON012),
    X(FTR_HNW_COMMON013),
    X(FTR_HNW_COMMON014),
    X(FTR_HNW_COMMON015),
    X(FTR_HNW_COMMON016),
    X(FTR_HNW_COMMON017),
    X(FTR_HNW_COMMON018),
    X(FTR_HNW_COMMON019),
    X(FTR_HNW_COMMON020),
    X(FTR_HNW_COMMON021),
    X(FTR_HNW_COMMON022),
    X(FTR_HNW_COMMON023),
    X(FTR_HNW_COMMON024),
    X(FTR_HNW_COMMON025),
    X(FTR_HNW_COMMON026),
    X(FTR_HNW_COMMON027),
    X(FTR_HNW_COMMON028),
    X(FTR_HNW_COMMON029),
    X(FTR_HNW_COMMON030),
    X(FTR_HNW_COMMON031),
    X(FTR_HNW_COMMON032),
    X(FTR_HNW_COMMON033),
    X(FTR_HNW_COMMON034),
    X(FTR_HNW_COMMON035),
    X(FTR_HNW_COMMON036),
    X(FTR_HNW_COMMON037),
    X(FTR_HNW_COMMON038),
    X(FTR_HNW_COMMON039),
    X(FTR_HNW_COMMON040),
    X(FTR_HNW_COMMON041),
    X(FTR_HNW_COMMON042),
    X(FTR_HNW_COMMON043),
    X(FTR_HNW_COMMON044),
    X(FTR_HNW_COMMON045),
    X(FTR_HNW_COMMON046),
    X(FTR_HNW_COMMON047),
    X(FTR_HNW_COMMON048),
    X(FTR_HNW_COMMON049),
    X(FTR_HNW_COMMON050),
    X(FTR_HNW_COMMON051),
    X(FTR_HNW_COMMON052),
    X(FTR_HNW_COMMON053),
    X(FTR_HNW_COMMON054),
    X(FTR_HNW_COMMON055),
    X(FTR_HNW_COMMON056),
    X(FTR_HNW_COMMON057),
    X(FTR_HNW_COMMON058),
    X(FTR_HNW_COMMON059),
    X(FTR_HNW_COMMON060),
    X(FTR_HNW_COMMON061),
    X(FTR_HNW_COMMON062),
    X(FTR_HNW_COMMON063),
    X(FTR_HNW_COMMON064),
    X(FTR_HNW_COMMON065),
    X(FTR_HNW_COMMON066),
    X(FTR_HNW_COMMON067),
    X(FTR_HNW_COMMON068),
    X(FTR_HNW_COMMON069),
    X(FTR_HNW_COMMON070),
    X(FTR_HNW_COMMON071),
    X(FTR_HNW_COMMON072),
    X(FTR_HNW_COMMON073),
    X(FTR_HNW_COMMON074),
    X(FTR_HNW_COMMON075),
    X(FTR_HNW_COMMON076),
    X(FTR_HNW_COMMON077),
    X(FTR_HNW_COMMON078),
    X(FTR_HNW_COMMON079),
    X(FTR_HNW_COMMON080),
    X(FTR_HNW_COMMON081),
    X(FTR_HNW_COMMON082),
    X(FTR_HNW_COMMON083),
    X(FTR_HNW_COMMON084),
    X(FTR_HNW_COMMON085),
    X(FTR_HNW_COMMON086),
    X(FTR_HNW_COMMON087),
    X(FTR_HNW_COMMON088),
    X(FTR_HNW_COMMON089),
    X(FTR_HNW_COMMON090),
    X(FTR_HNW_COMMON091),
    X(FTR_HNW_COMMON092),
    X(FTR_HNW_COMMON093),
    X(FTR_HNW_COMMON094),
    X(FTR_HNW_COMMON095),
    X(FTR_HNW_COMMON096),
    X(FTR_HNW_COMMON097),
    X(FTR_HNW_COMMON098),
    X(FTR_HNW_COMMON099),
    X(FTR_HNW_COMMON100),
    X(FTR_HNW_COMMON101),
    X(FTR_HNW_COMMON102),
    X(FTR_HNW_COMMON103),
    X(FTR_HNW_COMMON104),
    X(FTR_HNW_COMMON105),
    X(FTR_HNW_COMMON106),
    X(FTR_HNW_COMMON107),
    X(FTR_HNW_COMMON108),
    X(FTR_HNW_COMMON109),
    X(FTR_HNW_COMMON110),
    X(FTR_HNW_COMMON111),
    X(FTR_HNW_COMMON112),
    X(FTR_HNW_COMMON113),
    X(FTR_HNW_COMMON114),
    X(FTR_HNW_COMMON115),
    X(FTR_HNW_COMMON116),
    X(FTR_HNW_COMMON117),
    X(FTR_HNW_COMMON118),
    X(FTR_HNW_COMMON119),
    X(FTR_HNW_COMMON120),
    X(FTR_HNW_COMMON121),
    X(FTR_HNW_COMMON122),
    X(FTR_HNW_COMMON123),
    X(FTR_HNW_COMMON124),
    X(FTR_HNW_COMMON125),
    X(FTR_HNW_COMMON126),
    X(FTR_FMANEKIN000),
    X(FTR_FMANEKIN001),
    X(FTR_FMANEKIN002),
    X(FTR_FMANEKIN003),
    X(FTR_FMANEKIN004),
    X(FTR_FMANEKIN005),
    X(FTR_FMANEKIN006),
    X(FTR_FMANEKIN007),
    X(FTR_FMANEKIN008),
    X(FTR_FMANEKIN009),
    X(FTR_FMANEKIN010),
    X(FTR_FMANEKIN011),
    X(FTR_FMANEKIN012),
    X(FTR_FMANEKIN013),
    X(FTR_FMANEKIN014),
    X(FTR_FMANEKIN015),
    X(FTR_FMANEKIN016),
    X(FTR_FMANEKIN017),
    X(FTR_FMANEKIN018),
    X(FTR_FMANEKIN019),
    X(FTR_FMANEKIN020),
    X(FTR_FMANEKIN021),
    X(FTR_FMANEKIN022),
    X(FTR_FMANEKIN023),
    X(FTR_FMANEKIN024),
    X(FTR_FMANEKIN025),
    X(FTR_FMANEKIN026),
    X(FTR_FMANEKIN027),
    X(FTR_FMANEKIN028),
    X(FTR_FMANEKIN029),
    X(FTR_FMANEKIN030),
    X(FTR_FMANEKIN031),
    X(FTR_FMANEKIN032),
    X(FTR_FMANEKIN033),
    X(FTR_FMANEKIN034),
    X(FTR_FMANEKIN035),
    X(FTR_FMANEKIN036),
    X(FTR_FMANEKIN037),
    X(FTR_FMANEKIN038),
    X(FTR_FMANEKIN039),
    X(FTR_FMANEKIN040),
    X(FTR_FMANEKIN041),
    X(FTR_FMANEKIN042),
    X(FTR_FMANEKIN043),
    X(FTR_FMANEKIN044),
    X(FTR_FMANEKIN045),
    X(FTR_FMANEKIN046),
    X(FTR_FMANEKIN047),
    X(FTR_FMANEKIN048),
    X(FTR_FMANEKIN049),
    X(FTR_FMANEKIN050),
    X(FTR_FMANEKIN051),
    X(FTR_FMANEKIN052),
    X(FTR_FMANEKIN053),
    X(FTR_FMANEKIN054),
    X(FTR_FMANEKIN055),
    X(FTR_FMANEKIN056),
    X(FTR_FMANEKIN057),
    X(FTR_FMANEKIN058),
    X(FTR_FMANEKIN059),
    X(FTR_FMANEKIN060),
    X(FTR_FMANEKIN061),
    X(FTR_FMANEKIN062),
    X(FTR_FMANEKIN063),
    X(FTR_FMANEKIN064),
    X(FTR_FMANEKIN065),
    X(FTR_FMANEKIN066),
    X(FTR_FMANEKIN067),
    X(FTR_FMANEKIN068),
    X(FTR_FMANEKIN069),
    X(FTR_FMANEKIN070),
    X(FTR_FMANEKIN071),
    X(FTR_FMANEKIN072),
    X(FTR_FMANEKIN073),
    X(FTR_FMANEKIN074),
    X(FTR_FMANEKIN075),
    X(FTR_FMANEKIN076),
    X(FTR_FMANEKIN077),
    X(FTR_FMANEKIN078),
    X(FTR_FMANEKIN079),
    X(FTR_FMANEKIN080),
    X(FTR_FMANEKIN081),
    X(FTR_FMANEKIN082),
    X(FTR_FMANEKIN083),
    X(FTR_FMANEKIN084),
    X(FTR_FMANEKIN085),
    X(FTR_FMANEKIN086),
    X(FTR_FMANEKIN087),
    X(FTR_FMANEKIN088),
    X(FTR_FMANEKIN089),
    X(FTR_FMANEKIN090),
    X(FTR_FMANEKIN091),
    X(FTR_FMANEKIN092),
    X(FTR_FMANEKIN093),
    X(FTR_FMANEKIN094),
    X(FTR_FMANEKIN095),
    X(FTR_FMANEKIN096),
    X(FTR_FMANEKIN097),
    X(FTR_FMANEKIN098),
    X(FTR_FMANEKIN099),
    X(FTR_FMANEKIN100),
    X(FTR_FMANEKIN101),
    X(FTR_FMANEKIN102),
    X(FTR_FMANEKIN103),
    X(FTR_FMANEKIN104),
    X(FTR_FMANEKIN105),
    X(FTR_FMANEKIN106),
    X(FTR_FMANEKIN107),
    X(FTR_FMANEKIN108),
    X(FTR_FMANEKIN109),
    X(FTR_FMANEKIN110),
    X(FTR_FMANEKIN111),
    X(FTR_FMANEKIN112),
    X(FTR_FMANEKIN113),
    X(FTR_FMANEKIN114),
    X(FTR_FMANEKIN115),
    X(FTR_FMANEKIN116),
    X(FTR_FMANEKIN117),
    X(FTR_FMANEKIN118),
    X(FTR_FMANEKIN119),
    X(FTR_FMANEKIN120),
    X(FTR_FMANEKIN121),
    X(FTR_FMANEKIN122),
    X(FTR_FMANEKIN123),
    X(FTR_FMANEKIN124),
    X(FTR_FMANEKIN125),
    X(FTR_FMANEKIN126),
    X(FTR_FMANEKIN127),
    X(FTR_FMANEKIN128),
    X(FTR_FMANEKIN129),
    X(FTR_FMANEKIN130),
    X(FTR_FMANEKIN131),
    X(FTR_FMANEKIN132),
    X(FTR_FMANEKIN133),
    X(FTR_FMANEKIN134),
    X(FTR_FMANEKIN135),
    X(FTR_FMANEKIN136),
    X(FTR_FMANEKIN137),
    X(FTR_FMANEKIN138),
    X(FTR_FMANEKIN139),
    X(FTR_FMANEKIN140),
    X(FTR_FMANEKIN141),
    X(FTR_FMANEKIN142),
    X(FTR_FMANEKIN143),
    X(FTR_FMANEKIN144),
    X(FTR_FMANEKIN145),
    X(FTR_FMANEKIN146),
    X(FTR_FMANEKIN147),
    X(FTR_FMANEKIN148),
    X(FTR_FMANEKIN149),
    X(FTR_FMANEKIN150),
    X(FTR_FMANEKIN151),
    X(FTR_FMANEKIN152),
    X(FTR_FMANEKIN153),
    X(FTR_FMANEKIN154),
    X(FTR_FMANEKIN155),
    X(FTR_FMANEKIN156),
    X(FTR_FMANEKIN157),
    X(FTR_FMANEKIN158),
    X(FTR_FMANEKIN159),
    X(FTR_FMANEKIN160),
    X(FTR_FMANEKIN161),
    X(FTR_FMANEKIN162),
    X(FTR_FMANEKIN163),
    X(FTR_FMANEKIN164),
    X(FTR_FMANEKIN165),
    X(FTR_FMANEKIN166),
    X(FTR_FMANEKIN167),
    X(FTR_FMANEKIN168),
    X(FTR_FMANEKIN169),
    X(FTR_FMANEKIN170),
    X(FTR_FMANEKIN171),
    X(FTR_FMANEKIN172),
    X(FTR_FMANEKIN173),
    X(FTR_FMANEKIN174),
    X(FTR_FMANEKIN175),
    X(FTR_FMANEKIN176),
    X(FTR_FMANEKIN177),
    X(FTR_FMANEKIN178),
    X(FTR_FMANEKIN179),
    X(FTR_FMANEKIN180),
    X(FTR_FMANEKIN181),
    X(FTR_FMANEKIN182),
    X(FTR_FMANEKIN183),
    X(FTR_FMANEKIN184),
    X(FTR_FMANEKIN185),
    X(FTR_FMANEKIN186),
    X(FTR_FMANEKIN187),
    X(FTR_FMANEKIN188),
    X(FTR_FMANEKIN189),
    X(FTR_FMANEKIN190),
    X(FTR_FMANEKIN191),
    X(FTR_FMANEKIN192),
    X(FTR_FMANEKIN193),
    X(FTR_FMANEKIN194),
    X(FTR_FMANEKIN195),
    X(FTR_FMANEKIN196),
    X(FTR_FMANEKIN197),
    X(FTR_FMANEKIN198),
    X(FTR_FMANEKIN199),
    X(FTR_FMANEKIN200),
    X(FTR_FMANEKIN201),
    X(FTR_FMANEKIN202),
    X(FTR_FMANEKIN203),
    X(FTR_FMANEKIN204),
    X(FTR_FMANEKIN205),
    X(FTR_FMANEKIN206),
    X(FTR_FMANEKIN207),
    X(FTR_FMANEKIN208),
    X(FTR_FMANEKIN209),
    X(FTR_FMANEKIN210),
    X(FTR_FMANEKIN211),
    X(FTR_FMANEKIN212),
    X(FTR_FMANEKIN213),
    X(FTR_FMANEKIN214),
    X(FTR_FMANEKIN215),
    X(FTR_FMANEKIN216),
    X(FTR_FMANEKIN217),
    X(FTR_FMANEKIN218),
    X(FTR_FMANEKIN219),
    X(FTR_FMANEKIN220),
    X(FTR_FMANEKIN221),
    X(FTR_FMANEKIN222),
    X(FTR_FMANEKIN223),
    X(FTR_FMANEKIN224),
    X(FTR_FMANEKIN225),
    X(FTR_FMANEKIN226),
    X(FTR_FMANEKIN227),
    X(FTR_FMANEKIN228),
    X(FTR_FMANEKIN229),
    X(FTR_FMANEKIN230),
    X(FTR_FMANEKIN231),
    X(FTR_FMANEKIN232),
    X(FTR_FMANEKIN233),
    X(FTR_FMANEKIN234),
    X(FTR_FMANEKIN235),
    X(FTR_FMANEKIN236),
    X(FTR_FMANEKIN237),
    X(FTR_FMANEKIN238),
    X(FTR_FMANEKIN239),
    X(FTR_FMANEKIN240),
    X(FTR_FMANEKIN241),
    X(FTR_FMANEKIN242),
    X(FTR_FMANEKIN243),
    X(FTR_FMANEKIN244),
    X(FTR_FMANEKIN245),
    X(FTR_FMANEKIN246),
    X(FTR_FMANEKIN247),
    X(FTR_FMANEKIN248),
    X(FTR_FMANEKIN249),
    X(FTR_FMANEKIN250),
    X(FTR_FMANEKIN251),
    X(FTR_FMANEKIN252),
    X(FTR_FMANEKIN253),
    X(FTR_FMANEKIN254),
    X(FTR_MYFMANEKIN0),
    X(FTR_MYFMANEKIN1),
    X(FTR_MYFMANEKIN2),
    X(FTR_MYFMANEKIN3),
    X(FTR_MYFMANEKIN4),
    X(FTR_MYFMANEKIN5),
    X(FTR_MYFMANEKIN6),
    X(FTR_MYFMANEKIN7),
    X(FTR_SUM_MONSHIRO),
    X(FTR_SUM_MONKI),
    X(FTR_SUM_KIAGEHA),
    X(FTR_SUM_OHMURASAKI),
    X(FTR_SUM_MINMIN),
    X(FTR_SUM_TUKUTUKU),
    X(FTR_SUM_HIGURASHI),
    X(FTR_SUM_ABURA),
    X(FTR_SUM_HACHI),
    X(FTR_SUM_SHIOKARA),
    X(FTR_SUM_AKIAKANE),
    X(FTR_SUM_GINYANMA),
    X(FTR_SUM_ONIYANMA),
    X(FTR_SUM_SYOURYOU),
    X(FTR_SUM_TONOSAMA),
    X(FTR_SUM_KOOROGI),
    X(FTR_SUM_KIRIGIRISU),
    X(FTR_SUM_SUZUMUSHI),
    X(FTR_SUM_MATUMUSHI),
    X(FTR_SUM_KANABUN),
    X(FTR_SUM_KABUTO),
    X(FTR_SUM_HIRATA),
    X(FTR_SUM_TAMAMUSHI),
    X(FTR_SUM_GOMADARA),
    X(FTR_SUM_TENTOU),
    X(FTR_SUM_NANAHOSHI),
    X(FTR_SUM_KAMAKIRI),
    X(FTR_SUM_GENJI),
    X(FTR_SUM_DANNA),
    X(FTR_SUM_NOKOGIRI),
    X(FTR_SUM_MIYAMA),
    X(FTR_SUM_OKUWA),
    X(FTR_NOG_MAIMAI),
    X(FTR_NOG_KERA),
    X(FTR_NOG_AMENBO),
    X(FTR_NOG_MINO),
    X(FTR_NOG_DANGO),
    X(FTR_NOG_KUMO),
    X(FTR_NOG_ARI),
    X(FTR_NOG_KA),
    X(FTR_SUM_FUNA),
    X(FTR_SUM_HERA),
    X(FTR_SUM_KOI),
    X(FTR_SUM_NISIKI),
    X(FTR_SUM_NAMAZU),
    X(FTR_SUM_BASS),
    X(FTR_SUM_BASSM),
    X(FTR_SUM_BASSL),
    X(FTR_SUM_GILL),
    X(FTR_SUM_OONAMAZU),
    X(FTR_SUM_RAIGYO),
    X(FTR_SUM_NIGOI),
    X(FTR_SUM_UGUI),
    X(FTR_SUM_OIKAWA),
    X(FTR_SUM_TANAGO),
    X(FTR_SUM_DOJYO),
    X(FTR_SUM_WAKASAGI),
    X(FTR_SUM_AYU),
    X(FTR_SUM_YAMAME),
    X(FTR_SUM_IWANA),
    X(FTR_SUM_NIJI),
    X(FTR_SUM_ITO),
    X(FTR_SUM_SAKE),
    X(FTR_SUM_KINGYO),
    X(FTR_SUM_PIRANIA),
    X(FTR_SUM_AROANA),
    X(FTR_SUM_UNAGI),
    X(FTR_SUM_DONKO),
    X(FTR_SUM_ANGEL),
    X(FTR_SUM_GUPI),
    X(FTR_SUM_DEMEKIN),
    X(FTR_SUM_KASEKI),
    X(FTR_NOG_ZARIGANI),
    X(FTR_NOG_KAERU),
    X(FTR_NOG_MEDAKA),
    X(FTR_NOG_KURAGE),
    X(FTR_NOG_SUZUKI),
    X(FTR_NOG_TAI),
    X(FTR_NOG_ISIDAI),
    X(FTR_NOG_PIRALUKU),
    X(FTR_FUMBRELLA00),
    X(FTR_FUMBRELLA01),
    X(FTR_FUMBRELLA02),
    X(FTR_FUMBRELLA03),
    X(FTR_FUMBRELLA04),
    X(FTR_FUMBRELLA05),
    X(FTR_FUMBRELLA06),
    X(FTR_FUMBRELLA07),
    X(FTR_FUMBRELLA08),
    X(FTR_FUMBRELLA09),
    X(FTR_FUMBRELLA10),
    X(FTR_FUMBRELLA11),
    X(FTR_FUMBRELLA12),
    X(FTR_FUMBRELLA13),
    X(FTR_FUMBRELLA14),
    X(FTR_FUMBRELLA15),
    X(FTR_FUMBRELLA16),
    X(FTR_FUMBRELLA17),
    X(FTR_FUMBRELLA18),
    X(FTR_FUMBRELLA19),
    X(FTR_FUMBRELLA20),
    X(FTR_FUMBRELLA21),
    X(FTR_FUMBRELLA22),
    X(FTR_FUMBRELLA23),
    X(FTR_FUMBRELLA24),
    X(FTR_FUMBRELLA25),
    X(FTR_FUMBRELLA26),
    X(FTR_FUMBRELLA27),
    X(FTR_FUMBRELLA28),
    X(FTR_FUMBRELLA29),
    X(FTR_FUMBRELLA30),
    X(FTR_FUMBRELLA31),
    X(FTR_MYFUMBRELLA0),
    X(FTR_MYFUMBRELLA1),
    X(FTR_MYFUMBRELLA2),
    X(FTR_MYFUMBRELLA3),
    X(FTR_MYFUMBRELLA4),
    X(FTR_MYFUMBRELLA5),
    X(FTR_MYFUMBRELLA6),
    X(FTR_MYFUMBRELLA7),
    X(FTR_FAMICOM_COMMON00),
    X(FTR_FAMICOM_COMMON01),
    X(FTR_FAMICOM_COMMON02),
    X(FTR_FAMICOM_COMMON03),
    X(FTR_FAMICOM_COMMON04),
    X(FTR_FAMICOM_COMMON05),
    X(FTR_FAMICOM_COMMON06),
    X(FTR_FAMICOM_COMMON07),
    X(FTR_FAMICOM_COMMON08),
    X(FTR_FAMICOM_COMMON09),
    X(FTR_FAMICOM_COMMON10),
    X(FTR_FAMICOM_COMMON11),
    X(FTR_FAMICOM_COMMON12),
    X(FTR_FAMICOM_COMMON13),
    X(FTR_FAMICOM_COMMON14),
    X(FTR_FAMICOM_COMMON15),
    X(FTR_FAMICOM_COMMON16),
    X(FTR_FAMICOM_COMMON17),
    X(FTR_FAMICOM_COMMON18),
    X(FTR_KOB_DISKSYSTEM8),
    X(FTR_SUM_CHIKUON01),
    X(FTR_SUM_CHIKUON02),
    X(FTR_SUM_JUKEBOX),
    X(FTR_SUM_RADIO01),
    X(FTR_SUM_RADIO02),
    X(FTR_SUM_CONPO02),
    X(FTR_SUM_STEREO02),
    X(FTR_SUM_LV_STEREO),
    X(FTR_SUM_X_LANP),
    X(FTR_SUM_X_CHAIR01),
    X(FTR_SUM_X_CHEST03),
    X(FTR_SUM_X_SOFA01),
    X(FTR_SUM_X_BED01),
    X(FTR_SUM_X_CLK),
    X(FTR_SUM_X_TABLE01),
    X(FTR_SUM_X_PIANO),
    X(FTR_SUM_DOLL11),
    X(FTR_SUM_ROBOCONPO),
    X(FTR_SUM_SAICONPO),
    X(FTR_SUM_FRUITCLK),
    X(FTR_SUM_ROBOCLK),
    X(FTR_KON_AMECLOCK),
    X(FTR_KON_ATQCLOCK),
    X(FTR_SUM_RECO01),
    X(FTR_SUM_CASSE01),
    X(FTR_SUM_MD01),
    X(FTR_KON_GRCLOCK),
    X(FTR_KON_WACLOCK),
    X(FTR_KON_REDCLOCK),
    X(FTR_KON_BLUECLOCK),
    X(FTR_KON_MIMICLOCK),
    X(FTR_KON_MANEKI01),
    X(FTR_KON_MANEKI02),
    X(FTR_KON_MUSYA),
    X(FTR_KON_TANUKI),
    X(FTR_KON_KAERU),
    X(FTR_KON_XTREE02),
    X(FTR_NOG_ROOKW),
    X(FTR_NOG_ROOKB),
    X(FTR_NOG_QUEENW),
    X(FTR_NOG_QUEENB),
    X(FTR_NOG_BISHOPW),
    X(FTR_NOG_BISHOPB),
    X(FTR_NOG_KINGW),
    X(FTR_NOG_KINGB),
    X(FTR_NOG_KNIGHTW),
    X(FTR_NOG_KNIGHTB),
    X(FTR_NOG_PAWNW),
    X(FTR_NOG_PAWNB),
    X(FTR_NOG_XTREE),
    X(FTR_NOG_TRI_CLOCK01),
    X(FTR_NOG_TRI_BED01),
    X(FTR_NOG_TRI_TABLE01),
    X(FTR_NOG_TRI_SOFA01),
    X(FTR_NOG_TRI_AUDIO01),
    X(FTR_NOG_TRI_CHAIR01),
    X(FTR_NOG_TRI_RACK01),
    X(FTR_IKE_JPN_TOKONOMA01),
    X(FTR_IKE_JPN_IRORI01),
    X(FTR_SUM_KOKUBAN),
    X(FTR_SUM_BAKETU),
    X(FTR_DIN_TRIKERA_HEAD),
    X(FTR_DIN_TRIKERA_TAIL),
    X(FTR_DIN_TRIKERA_BODY),
    X(FTR_DIN_TREX_HEAD),
    X(FTR_DIN_TREX_TAIL),
    X(FTR_DIN_TREX_BODY),
    X(FTR_DIN_BRONT_HEAD),
    X(FTR_DIN_BRONT_TAIL),
    X(FTR_DIN_BRONT_BODY),
    X(FTR_DIN_STEGO_HEAD),
    X(FTR_DIN_STEGO_TAIL),
    X(FTR_DIN_STEGO_BODY),
    X(FTR_DIN_PTERA_HEAD),
    X(FTR_DIN_PTERA_RWING),
    X(FTR_DIN_PTERA_LWING),
    X(FTR_DIN_HUTABA_HEAD),
    X(FTR_DIN_HUTABA_NECK),
    X(FTR_DIN_HUTABA_BODY),
    X(FTR_DIN_MAMMOTH_HEAD),
    X(FTR_DIN_MAMMOTH_BODY),
    X(FTR_DIN_AMBER),
    X(FTR_DIN_STUMP),
    X(FTR_DIN_AMMONITE),
    X(FTR_DIN_EGG),
    X(FTR_DIN_TRILOBITE),
    X(FTR_SUM_BLA_LANP),
    X(FTR_KON_SNOWFREEZER),
    X(FTR_KON_SNOWTABLE),
    X(FTR_KON_SNOWBED),
    X(FTR_TAK_SNOWISU),
    X(FTR_TAK_SNOWLAMP),
    X(FTR_KON_SNOWSOFA),
    X(FTR_KON_SNOWTV),
    X(FTR_KON_SNOWTANSU),
    X(FTR_KON_SNOWBOX),
    X(FTR_KON_SNOWCLOCK),
    X(FTR_DIN_TRIKERA_DUMMY),
    X(FTR_DIN_TREX_DUMMY),
    X(FTR_DIN_BRONT_DUMMY),
    X(FTR_DIN_PTERA_DUMMY),
    X(FTR_DIN_HUTABA_DUMMY),
    X(FTR_DIN_MAMMOTH_DUMMY),
    X(FTR_DIN_STEGO_DUMMYA),
    X(FTR_DIN_STEGO_DUMMYB),
    X(FTR_DIN_DUMMY),
    X(FTR_TAK_SYOGI),
    X(FTR_IKE_JNY_MAKADA01),
    X(FTR_IKE_PST_POST01),
    X(FTR_IKE_PST_PIG01),
    X(FTR_IKE_PST_TESYU01),
    X(FTR_IKE_JNY_AFMEN01),
    X(FTR_IKE_JNY_ROSIA01),
    X(FTR_HAYAKAWA_FAMICOM),
    X(FTR_IKE_JNY_BOTLE01),
    X(FTR_IKE_JNY_HARIKO01),
    X(FTR_IKE_JNY_MOAI01),
    X(FTR_RADIO_TEST),
    X(FTR_IKE_JNY_GOJYU01),
    X(FTR_IKE_JNY_KIBORI01),
    X(FTR_IKE_JNY_TRUTH01),
    X(FTR_IKE_JNY_SIRSER01),
    X(FTR_IKE_JNY_PISA01),
    X(FTR_TAK_LION),
    X(FTR_IKE_JNY_SYON01),
    X(FTR_IKE_JNY_TOWER01),
    X(FTR_NOG_BALLOON_COMMON0),
    X(FTR_NOG_BALLOON_COMMON1),
    X(FTR_NOG_BALLOON_COMMON2),
    X(FTR_NOG_BALLOON_COMMON3),

    FTR0_END

#undef XW
};

#define HANIWA_START FTR_START(FTR_HNW_COMMON000)
#define HANIWA_END   FTR_END(FTR_HNW_COMMON126)

#define FTR_CLOTH_START FTR_START(FTR_FMANEKIN000)
#define FTR_CLOTH_END FTR_END(FTR_FMANEKIN254)

#define FTR_CLOTH_MANNIQUIN_MY_ORIGINAL0 FTR_START(FTR_MYFMANEKIN0)
#define FTR_CLOTH_MYMANNIQUIN_END FTR_END(FTR_MYFMANEKIN7)

#define FTR_INSECT_START FTR_START(FTR_SUM_MONSHIRO)
#define FTR_INSECT_END FTR_END(FTR_NOG_KA)

#define FTR_FISH_START FTR_START(FTR_SUM_FUNA)
#define FTR_FISH_END FTR_END(FTR_NOG_PIRALUKU)

#define FTR_UMBRELLA_START FTR_START(FTR_FUMBRELLA00)
#define FTR_UMBRELLA_END FTR_END(FTR_FUMBRELLA31)

#define FTR_MYUMBRELLA_START FTR_START(FTR_MYFUMBRELLA0)
#define FTR_MYUMBRELLA_END FTR_END(FTR_MYFUMBRELLA7)

#define FTR_DINO_START FTR_START(FTR_DIN_TRIKERA_HEAD)
#define FTR_DINO_END FTR_END(FTR_DIN_TRILOBITE)
// #define FTR0_END 0x1FFF

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

enum ftr1_e {
#define X(e) \
    e##_SOUTH, \
    e##_EAST,  \
    e##_NORTH, \
    e##_WEST

    __FTR1_START = FTR1_START-1,
    X(FTR_NOG_BALLOON_COMMON4),
    X(FTR_NOG_BALLOON_COMMON5),
    X(FTR_NOG_BALLOON_COMMON6),
    X(FTR_NOG_BALLOON_COMMON7),
    X(FTR_TAK_MEGAMI),
    X(FTR_IKE_JNY_GATE01),
    X(FTR_TAK_MONEY),
    X(FTR_IKE_JNY_NINGYO01),
    X(FTR_NOG_YUBIN),
    X(FTR_NOG_MYHOME2),
    X(FTR_NOG_MYHOME4),
    X(FTR_NOG_KOBAN),
    X(FTR_NOG_MUSEUM),
    X(FTR_TAK_YOROI),
    X(FTR_IKE_K_TUKIMI01),
    X(FTR_IKE_K_MAME01),
    X(FTR_IKE_K_SINNEN01),
    X(FTR_IKE_K_OTOME01),
    X(FTR_NOG_YAMISHOP),
    X(FTR_NOG_URANAI),
    X(FTR_IKE_JNY_SIRSER201),
    X(FTR_IKE_K_TANABATA01),
    X(FTR_TAK_FLAG01),
    X(FTR_TAK_FLAG02),
    X(FTR_NOG_SHOP1),
    X(FTR_IKE_JNY_HOUI01),
    X(FTR_IKE_K_COUNT01),
    X(FTR_IKE_K_TURIS01),
    X(FTR_TAK_TOUDAI),
    X(FTR_IKE_K_SUM01),
    X(FTR_NOG_S_TREE),
    X(FTR_NOG_F_TREE),
    X(FTR_NOG_ZASSOU),
    X(FTR_TAK_TAILOR),
    X(FTR_NOG_DUMP),
    X(FTR_IID_HANABI),
    X(FTR_NOG_SNOWMAN),
    X(FTR_IKE_K_IVEBOY01),
    X(FTR_TAK_FLAG03),
    X(FTR_TAK_MOON),
    X(FTR_IKE_K_KID01),
    X(FTR_IID_NINGYOU),
    X(FTR_NOG_STATION00),
    X(FTR_NOG_STATION01),
    X(FTR_NOG_STATION02),
    X(FTR_NOG_STATION03),
    X(FTR_NOG_STATION04),
    X(FTR_NOG_STATION05),
    X(FTR_NOG_STATION06),
    X(FTR_NOG_STATION07),
    X(FTR_NOG_STATION08),
    X(FTR_NOG_STATION09),
    X(FTR_NOG_STATION10),
    X(FTR_NOG_STATION11),
    X(FTR_NOG_STATION12),
    X(FTR_NOG_STATION13),
    X(FTR_NOG_STATION14),
    X(FTR_NOG_SHRINE),
    X(FTR_NOG_FLAT),
    X(FTR_NOG_RAIL),
    X(FTR_NOG_EARTH),
    X(FTR_IKE_K_KID02),
    X(FTR_NOG_MIKANBOX),
    X(FTR_NOG_COLLEGENOTE),
    X(FTR_NOG_SCHOOLNOTE),
    X(FTR_NOG_SYSTEMNOTE),
    X(FTR_NOG_HARDDIARY),
    X(FTR_NOG_TUDURINOTE),
    X(FTR_IID_DIARY),
    X(FTR_IID_FUNEDIARY),
    X(FTR_IID_MDIARY),
    X(FTR_IID_NEWDIARY),
    X(FTR_TAK_NIKKI01),
    X(FTR_IKE_NIKKI_FAN1),
    X(FTR_IKE_NIKKI_FAN2),
    X(FTR_IKE_NIKKI_FAN3),
    X(FTR_IKE_NIKKI_FAN4),
    X(FTR_IKE_NIKKI_FAN5),
    X(FTR_IKE_NIKKI_WAFU1),
    X(FTR_GOLD_ITEM0),
    X(FTR_GOLD_ITEM1),
    X(FTR_GOLD_ITEM2),
    X(FTR_GOLD_ITEM3),
    X(FTR_UTIWA0),
    X(FTR_UTIWA1),
    X(FTR_UTIWA2),
    X(FTR_UTIWA3),
    X(FTR_UTIWA4),
    X(FTR_UTIWA5),
    X(FTR_UTIWA6),
    X(FTR_UTIWA7),
    X(FTR_KAZAGURUMA0),
    X(FTR_KAZAGURUMA1),
    X(FTR_KAZAGURUMA2),
    X(FTR_KAZAGURUMA3),
    X(FTR_KAZAGURUMA4),
    X(FTR_KAZAGURUMA5),
    X(FTR_KAZAGURUMA6),
    X(FTR_KAZAGURUMA7),
    X(FTR_TOOL0),
    X(FTR_TOOL1),
    X(FTR_TOOL2),
    X(FTR_TOOL3),
    X(FTR_NOG_NABE),
    X(FTR_IKE_KAMA_DANRO01),
    X(FTR_NOG_KAMAKURA),
    X(FTR_NOG_W_TREE),
    X(FTR_TAK_ICE),
    X(FTR_IKE_ISLAND_HAKO01),
    X(FTR_NOG_BEACHBED),
    X(FTR_NOG_BEACHTABLE),
    X(FTR_TAK_HIBATI),
    X(FTR_IID_SURF),
    X(FTR_IID_SNOW),
    X(FTR_TAK_TETRA),
    X(FTR_IKE_ISLAND_UKU01),
    X(FTR_IKE_ISLAND_SENSUI01),
    X(FTR_IID_YUKI),
    X(FTR_SUM_ART02),
    X(FTR_SUM_ART03),
    X(FTR_TAK_SORI01),
    X(FTR_IID_BENTI),
    X(FTR_TAK_CUBE),
    X(FTR_IKU_DENKO),
    X(FTR_YAZ_ROCKET),
    X(FTR_IKU_SLIP),
    X(FTR_IKU_UKAI),
    X(FTR_IKU_WORK),
    X(FTR_HOS_DESKL),
    X(FTR_HOS_DESKR),
    X(FTR_HOS_FLIP),
    X(FTR_IKU_FLAGMAN),
    X(FTR_YAZ_FISH_TROPHY),
    X(FTR_IKU_JERSEY),
    X(FTR_IKU_REDUCESPEED),
    X(FTR_YAZ_GOLF_TROPHY),
    X(FTR_HOS_TDESK),
    X(FTR_IKU_HAZARDOUS_TOP),
    X(FTR_YAZ_TENNIS_TROPHY),
    X(FTR_IKU_SAWHOUSEV),
    X(FTR_YAZ_KART_TROPHY),
    X(FTR_IKU_BUGZAPPER),
    X(FTR_YAZ_TELESCOPE),
    X(FTR_IKU_COCOA),
    X(FTR_YAZ_B_BATH),
    X(FTR_SUGI_BARBECUE),
    X(FTR_SUGI_RADIATORL),
    X(FTR_SUGI_ALCHAIR),
    X(FTR_SUGI_CHESSTABLE),
    X(FTR_IKU_CANDY),
    X(FTR_SUGI_KPOOL),
    X(FTR_IKU_CEMENT),
    X(FTR_IKU_JACK),
    X(FTR_SUGI_TORCH),
    X(FTR_YAZ_B_HOUSE),
    X(FTR_YOS_PBSTOVE),
    X(FTR_IKU_BUSSTOP),
    X(FTR_TAK_HAM1),
    X(FTR_IKU_FLIP_TOP),
    X(FTR_YOS_KFLAG),
    X(FTR_TAK_NES01),
    X(FTR_YOS_B_FEEDER),
    X(FTR_IKU_CHAIR),
    X(FTR_IKU_ROLLER),
    X(FTR_YOS_FLAMINGO),
    X(FTR_YOS_MAILBOX),
    X(FTR_YAZ_CANDLE),
    X(FTR_IKU_HAM),
    X(FTR_YOS_GNOME),
    X(FTR_YOS_FLAMINGO2),
    X(FTR_IKU_GOLD_GREEN),
    X(FTR_IKU_GOLD_RED),
    X(FTR_IKU_TUMBLE),
    X(FTR_IKU_COW),
    X(FTR_IKU_ORANGE),
    X(FTR_IKU_SAKU_A),
    X(FTR_IKU_SAKU_B),
    X(FTR_YAZ_TUB),
    X(FTR_YOS_LUIGI),
    X(FTR_YOS_MARIO),
    X(FTR_IKU_TURKEY_LAMP),
    X(FTR_YAZ_WAGON),
    X(FTR_YOS_TERRACE),
    X(FTR_HOS_PIKNIC),
    X(FTR_IKU_TURKEY_TABLE),
    X(FTR_IKU_TURKEY_TV),
    X(FTR_IKU_TURKEY_BED),
    X(FTR_YAZ_TURKEY_CHAIR),
    X(FTR_YOS_TURKEY_WATCH),
    X(FTR_HOS_TURKEY_SOFA),
    X(FTR_IKU_MARIO_DOKAN),
    X(FTR_IKU_MARIO_RENGA),
    X(FTR_YAZ_TURKEY_CLOSET),
    X(FTR_HOS_MARIO_HATA),
    X(FTR_YAZ_TURKEY_CHEST),
    X(FTR_HOS_MARIO_KINOKO),
    X(FTR_YOS_TURKEY_MIRROR),
    X(FTR_IKU_MARIO_COIN),
    X(FTR_IKU_MARIO_HATENA),
    X(FTR_IKU_MARIO_STAR),
    X(FTR_IKU_MARIO_KOURA),
    X(FTR_IKU_MARIO_TAIHOU),
    X(FTR_YOS_CACTUS),
    X(FTR_YAZ_MARIO_FLOWER),
    X(FTR_YOS_WHEEL),
    X(FTR_IKU_IDO),
    X(FTR_IKE_PRORES_FENSE01),
    X(FTR_IKE_PRORES_LING01),
    X(FTR_IKE_PRORES_LING02),
    X(FTR_IKE_PRORES_LING03),
    X(FTR_IKE_PRORES_MAT01),
    X(FTR_IKE_PRORES_TABLE01),
    X(FTR_IKE_PRORES_PUNCH01),
    X(FTR_IKE_PRORES_SANDBAG01),
    X(FTR_IKE_PRORES_BENCH01),
    X(FTR_IKE_TENT_FIRE01),
    X(FTR_IKE_TENT_FIRE02),
    X(FTR_IKE_TENT_KAYAK01),
    X(FTR_NOG_SPRINKLER),
    X(FTR_TAK_TENT),
    X(FTR_IKE_TENT_KNAP01),
    X(FTR_IKE_FISH_TRO2),
    X(FTR_NOG_FLOWER0),
    X(FTR_NOG_FLOWER1),
    X(FTR_NOG_FLOWER2),
    X(FTR_NOG_FLOWER3),
    X(FTR_NOG_FLOWER4),
    X(FTR_NOG_FLOWER5),
    X(FTR_NOG_FLOWER6),
    X(FTR_NOG_FLOWER7),
    X(FTR_NOG_FLOWER8),
    X(FTR_TAK_TENT_LAMP),
    X(FTR_NOG_LAWNMOWER),
    X(FTR_TAK_TENT_BOX),
    X(FTR_IKE_TENT_BIKE01),
    X(FTR_IKE_TENT_SLEEPBAG01),
    X(FTR_NOG_BURNER),
    X(FTR_NOG_CORNUCOPIA),
    X(FTR_NOG_GONG),
    X(FTR_TAK_NOISE),
    X(FTR_TAK_STEW),
    X(FTR_DUMMY),

    FTR1_END
#undef X
};

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
#define ETC_EFFECT_CONTROL (ETC_START + 8)
#define ETC_SHOP_DESIGN (ETC_START + 9)
#define ETC_SHOP_MANEKIN (ETC_START + 10)
#define ETC_SHOP_INDOOR (ETC_START + 11)
#define ETC_SHOP_GOODS (ETC_START + 12)
#define ETC_SNOWMAN_BALL_A (ETC_START + 13)
#define ETC_SNOWMAN_BALL_B (ETC_START + 14)
#define ETC_BROKER_DESIGN (ETC_START + 15)
#define ETC_MY_INDOOR (ETC_START + 16)
#define ETC_TRAIN_WINDOW (ETC_START + 17)
#define ETC_UKI (ETC_START + 18)
#define ETC_SHOP_UMBRELLA (ETC_START + 19)
#define ETC_KAMAKURA_INDOOR (ETC_START + 20)
#define ETC_HOUSE_CLOCK (ETC_START + 21)

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

#define NPC_START    0xE000 // 0xE000
// cats
#define NPC_BOB      (NPC_START + 0) // 0xE000
#define NPC_OLIVIA   (NPC_START + 1) // 0xE001
#define NPC_MITZI    (NPC_START + 2) // 0xE002
#define NPC_KIKI     (NPC_START + 3) // 0xE003
#define NPC_TANGY    (NPC_START + 4) // 0xE004
#define NPC_KABUKI   (NPC_START + 5) // 0xE005
#define NPC_TABBY    (NPC_START + 6) // 0xE006
#define NPC_MONIQUE  (NPC_START + 7) // 0xE007
#define NPC_STINKY   (NPC_START + 8) // 0xE008
#define NPC_PURRL    (NPC_START + 9) // 0xE009
#define NPC_KITTY    (NPC_START + 10) // 0xE00A
#define NPC_TOM      (NPC_START + 11) // 0xE00B
#define NPC_ROSIE    (NPC_START + 12) // 0xE00C
// anteaters
#define NPC_NOSEGAY  (NPC_START + 13) // 0xE00D
#define NPC_ZOE      (NPC_START + 14) // 0xE00E
#define NPC_PANGO    (NPC_START + 15) // 0xE00F
#define NPC_CYRANO   (NPC_START + 16) // 0xE010
#define NPC_SNOOTY   (NPC_START + 17) // 0xE011
// bears
#define NPC_TEDDY    (NPC_START + 18) // 0xE012
#define NPC_CHOW     (NPC_START + 19) // 0xE013
#define NPC_DOZER    (NPC_START + 20) // 0xE014
#define NPC_NATE     (NPC_START + 21) // 0xE015
#define NPC_GROUCHO  (NPC_START + 22) // 0xE016
#define NPC_TUTU     (NPC_START + 23) // 0xE017
#define NPC_URSALA   (NPC_START + 24) // 0xE018
#define NPC_GRIZZLY  (NPC_START + 25) // 0xE019
#define NPC_PINKY    (NPC_START + 26) // 0xE01A
// birds
#define NPC_JAY      (NPC_START + 27) // 0xE01B
#define NPC_TWIGGY   (NPC_START + 28) // 0xE01C
#define NPC_ANCHOVY  (NPC_START + 29) // 0xE01D
#define NPC_PIPER    (NPC_START + 30) // 0xE01E
#define NPC_ADMIRAL  (NPC_START + 31) // 0xE01F
#define NPC_OTIS     (NPC_START + 32) // 0xE020
#define NPC_ROBIN    (NPC_START + 33) // 0xE021
#define NPC_MIDGE    (NPC_START + 34) // 0xE022
#define NPC_ACE      (NPC_START + 35) // 0xE023
#define NPC_TWIRP    (NPC_START + 36) // 0xE024
// bulls)
#define NPC_CHUCK    (NPC_START + 37) // 0xE025
#define NPC_STU      (NPC_START + 38) // 0xE026
// chickens
#define NPC_GOOSE    (NPC_START + 39) // 0xE027
#define NPC_BETTY    (NPC_START + 40) // 0xE028
#define NPC_HECTOR   (NPC_START + 41) // 0xE029
#define NPC_EGBERT   (NPC_START + 42) // 0xE02A
#define NPC_AVA      (NPC_START + 43) // 0xE02B
#define NPC_HANK     (NPC_START + 44) // 0xE02C
#define NPC_LEIGH    (NPC_START + 45) // 0xE02D
#define NPC_RHODA    (NPC_START + 46) // 0xE02E
// cubs
#define NPC_VLADIMIR (NPC_START + 47) // 0xE02F
#define NPC_MURPHY   (NPC_START + 48) // 0xE030
#define NPC_CUPCAKE  (NPC_START + 49) // 0xE031
#define NPC_KODY     (NPC_START + 50) // 0xE032
#define NPC_MAPLE    (NPC_START + 51) // 0xE033
#define NPC_PUDGE    (NPC_START + 52) // 0xE034
#define NPC_OLIVE    (NPC_START + 53) // 0xE035
#define NPC_PONCHO   (NPC_START + 54) // 0xE036
#define NPC_BLUEBEAR (NPC_START + 55) // 0xE037
// cows
#define NPC_PATTY    (NPC_START + 56) // 0xE038
#define NPC_PETUNIA  (NPC_START + 57) // 0xE039
#define NPC_BESSIE   (NPC_START + 58) // 0xE03A
#define NPC_BELLE    (NPC_START + 59) // 0xE03B
// crocodiles / alligators
#define NPC_ALFONSO  (NPC_START + 60) // 0xE03C
#define NPC_BOOTS    (NPC_START + 61) // 0xE03D
#define NPC_LIZ      (NPC_START + 62) // 0xE03E
#define NPC_BISKIT   (NPC_START + 63) // 0xE03F
// dogs
#define NPC_GOLDIE   (NPC_START + 64) // 0xE040
#define NPC_DAISY    (NPC_START + 65) // 0xE041
#define NPC_LUCKY    (NPC_START + 66) // 0xE042
#define NPC_PORTIA   (NPC_START + 67) // 0xE043
#define NPC_MADDIE   (NPC_START + 68) // 0xE044
#define NPC_BUTCH    (NPC_START + 69) // 0xE045
// ducks
#define NPC_BILL     (NPC_START + 70) // 0xE046
#define NPC_POMPOM   (NPC_START + 71) // 0xE047
#define NPC_JOEY     (NPC_START + 72) // 0xE048
#define NPC_SCOOT    (NPC_START + 73) // 0xE049
#define NPC_DERWIN   (NPC_START + 74) // 0xE04A
#define NPC_FRECKLES (NPC_START + 75) // 0xE04B
// elephants
#define NPC_PAOLO    (NPC_START + 76) // 0xE04C
#define NPC_DIZZY    (NPC_START + 77) // 0xE04D
#define NPC_AXEL     (NPC_START + 78) // 0xE04E
// frogs
#define NPC_EMERALD  (NPC_START + 79) // 0xE04F
#define NPC_TAD      (NPC_START + 80) // 0xE050
#define NPC_WART_JR  (NPC_START + 81) // 0xE051
#define NPC_COUSTEAU (NPC_START + 82) // 0xE052
#define NPC_PUDDLES  (NPC_START + 83) // 0xE053
#define NPC_LILY     (NPC_START + 84) // 0xE054
#define NPC_JEREMIAH (NPC_START + 85) // 0xE055
#define NPC_HUCK     (NPC_START + 86) // 0xE056
#define NPC_CAMOFROG (NPC_START + 87) // 0xE057
#define NPC_RIBBOT   (NPC_START + 88) // 0xE058
#define NPC_PRINCE   (NPC_START + 89) // 0xE059
#define NPC_JAMBETTE (NPC_START + 90) // 0xE05A
// goats
#define NPC_BILLY    (NPC_START + 91) // 0xE05B
#define NPC_CHEVRE   (NPC_START + 92) // 0xE05C
#define NPC_IGGY     (NPC_START + 93) // 0xE05D
#define NPC_GRUFF    (NPC_START + 94) // 0xE05E
#define NPC_SVEN     (NPC_START + 95) // 0xE05F
#define NPC_VELMA    (NPC_START + 96) // 0xE060
// gorillas
#define NPC_JANE     (NPC_START + 97) // 0xE061
#define NPC_CESAR    (NPC_START + 98) // 0xE062
#define NPC_LOUIE    (NPC_START + 99) // 0xE063
#define NPC_PEEWEE   (NPC_START + 100) // 0xE064
// hippos
#define NPC_ROLLO    (NPC_START + 101) // 0xE065
#define NPC_BUBBLES  (NPC_START + 102) // 0xE066
#define NPC_BERTHA   (NPC_START + 103) // 0xE067
// horses
#define NPC_ELMER    (NPC_START + 104) // 0xE068
#define NPC_WINNIE   (NPC_START + 105) // 0xE069
#define NPC_SAVANNAH (NPC_START + 106) // 0xE06A
#define NPC_ED       (NPC_START + 107) // 0xE06B
#define NPC_CLEO     (NPC_START + 108) // 0xE06C
#define NPC_PEACHES  (NPC_START + 109) // 0xE06D
#define NPC_BUCK     (NPC_START + 110) // 0xE06E
// kangaroos
#define NPC_CARRIE   (NPC_START + 111) // 0xE06F
#define NPC_MATHILDA (NPC_START + 112) // 0xE070
#define NPC_MARCY    (NPC_START + 113) // 0xE071
#define NPC_KITT     (NPC_START + 114) // 0xE072
#define NPC_VALISE   (NPC_START + 115) // 0xE073
#define NPC_ASTRID   (NPC_START + 116) // 0xE074
// koalas
#define NPC_SYDNEY   (NPC_START + 117) // 0xE075
#define NPC_GONZO    (NPC_START + 118) // 0xE076
#define NPC_OZZIE    (NPC_START + 119) // 0xE077
#define NPC_YUKA     (NPC_START + 120) // 0xE078
#define NPC_HUGGY    (NPC_START + 121) // 0xE079
// lions
#define NPC_REX      (NPC_START + 122) // 0xE07A
#define NPC_AZIZ     (NPC_START + 123) // 0xE07B
#define NPC_LEOPOLD  (NPC_START + 124) // 0xE07C
// mice
#define NPC_SAMSON   (NPC_START + 125) // 0xE07D
#define NPC_PENNY    (NPC_START + 126) // 0xE07E
#define NPC_DORA     (NPC_START + 127) // 0xE07F
#define NPC_CHICO    (NPC_START + 128) // 0xE080
#define NPC_CANDI    (NPC_START + 129) // 0xE081
#define NPC_RIZZO    (NPC_START + 130) // 0xE082
#define NPC_ANICOTTI (NPC_START + 131) // 0xE083
#define NPC_LIMBERG  (NPC_START + 132) // 0xE084
#define NPC_CARMEN   (NPC_START + 133) // 0xE085
// octopus
#define NPC_OCTAVIAN (NPC_START + 134) // 0xE086
// ostriches
#define NPC_SANDY    (NPC_START + 135) // 0xE087
#define NPC_SPROCKET (NPC_START + 136) // 0xE088
#define NPC_RIO      (NPC_START + 137) // 0xE089
#define NPC_QUEENIE  (NPC_START + 138) // 0xE08A
// eagles
#define NPC_APOLLO   (NPC_START + 139) // 0xE08B
#define NPC_BUZZ     (NPC_START + 140) // 0xE08C
#define NPC_QUETZAL  (NPC_START + 141) // 0xE08D
#define NPC_AMELIA   (NPC_START + 142) // 0xE08E
#define NPC_PIERCE   (NPC_START + 143) // 0xE08F
// penguins
#define NPC_ROALD    (NPC_START + 144) // 0xE090
#define NPC_AURORA   (NPC_START + 145) // 0xE091
#define NPC_HOPPER   (NPC_START + 146) // 0xE092
#define NPC_CUBE     (NPC_START + 147) // 0xE093
#define NPC_PUCK     (NPC_START + 148) // 0xE094
#define NPC_GWEN     (NPC_START + 149) // 0xE095
#define NPC_FRIGA    (NPC_START + 150) // 0xE096
// pigs
#define NPC_CURLY    (NPC_START + 151) // 0xE097
#define NPC_TRUFFLES (NPC_START + 152) // 0xE098
#define NPC_SPORK    (NPC_START + 153) // 0xE099
#define NPC_HUGH     (NPC_START + 154) // 0xE09A
#define NPC_RASHER   (NPC_START + 155) // 0xE09B
#define NPC_SUE_E    (NPC_START + 156) // 0xE09C
#define NPC_HAMBO    (NPC_START + 157) // 0xE09D
#define NPC_LUCY     (NPC_START + 158) // 0xE09E
#define NPC_COBB     (NPC_START + 159) // 0xE09F
#define NPC_BORIS    (NPC_START + 160) // 0xE0A0
// rabbits
#define NPC_BUNNIE   (NPC_START + 161) // 0xE0A1
#define NPC_DOC      (NPC_START + 162) // 0xE0A2
#define NPC_GASTON   (NPC_START + 163) // 0xE0A3
#define NPC_COCO     (NPC_START + 164) // 0xE0A4
#define NPC_GABI     (NPC_START + 165) // 0xE0A5
#define NPC_DOTTY    (NPC_START + 166) // 0xE0A6
#define NPC_GENJI    (NPC_START + 167) // 0xE0A7
#define NPC_SNAKE    (NPC_START + 168) // 0xE0A8
#define NPC_CLAUDE   (NPC_START + 169) // 0xE0A9
// rhinos
#define NPC_TANK     (NPC_START + 170) // 0xE0AA
#define NPC_SPIKE    (NPC_START + 171) // 0xE0AB
#define NPC_TIARA    (NPC_START + 172) // 0xE0AC
// sheep
#define NPC_VESTA    (NPC_START + 173) // 0xE0AD
// squirrels
#define NPC_FILBERT  (NPC_START + 174) // 0xE0AE
#define NPC_HAZEL    (NPC_START + 175) // 0xE0AF
#define NPC_PEANUT   (NPC_START + 176) // 0xE0B0
#define NPC_PECAN    (NPC_START + 177) // 0xE0B1
#define NPC_RICKY    (NPC_START + 178) // 0xE0B2
#define NPC_STATIC   (NPC_START + 179) // 0xE0B3
#define NPC_MINT     (NPC_START + 180) // 0xE0B4
#define NPC_NIBBLES  (NPC_START + 181) // 0xE0B5
// tigers
#define NPC_TYBALT   (NPC_START + 182) // 0xE0B6
#define NPC_ROLF     (NPC_START + 183) // 0xE0B7
#define NPC_BANGLE   (NPC_START + 184) // 0xE0B8
// wolves
#define NPC_LOBO     (NPC_START + 185) // 0xE0B9
#define NPC_FREYA    (NPC_START + 186) // 0xE0BA
#define NPC_CHIEF    (NPC_START + 187) // 0xE0BB
// late additions
#define NPC_WEBER    (NPC_START + 188) // 0xE0BC
#define NPC_MALLARY  (NPC_START + 189) // 0xE0BD
#define NPC_WOLFGANG (NPC_START + 190) // 0xE0BE
#define NPC_HORNSBY  (NPC_START + 191) // 0xE0BF
#define NPC_OXFORD   (NPC_START + 192) // 0xE0C0
#define NPC_T_BONE   (NPC_START + 193) // 0xE0C1
#define NPC_BIFF     (NPC_START + 194) // 0xE0C2
#define NPC_OPAL     (NPC_START + 195) // 0xE0C3
#define NPC_BONES    (NPC_START + 196) // 0xE0C4
#define NPC_BEA      (NPC_START + 197) // 0xE0C5
#define NPC_BITTY    (NPC_START + 198) // 0xE0C6
#define NPC_ROCCO    (NPC_START + 199) // 0xE0C7
#define NPC_LULU     (NPC_START + 200) // 0xE0C8
#define NPC_BLAIRE   (NPC_START + 201) // 0xE0C9
#define NPC_SALLY    (NPC_START + 202) // 0xE0CA
#define NPC_ELLIE    (NPC_START + 203) // 0xE0CB
#define NPC_ELOISE   (NPC_START + 204) // 0xE0CC
#define NPC_ALLI     (NPC_START + 205) // 0xE0CD
#define NPC_PIPPY    (NPC_START + 206) // 0xE0CE
#define NPC_EUNICE   (NPC_START + 207) // 0xE0CF
#define NPC_BAABARA  (NPC_START + 208) // 0xE0D0
#define NPC_FANG     (NPC_START + 209) // 0xE0D1
#define NPC_DEENA    (NPC_START + 210) // 0xE0D2
#define NPC_PATE     (NPC_START + 211) // 0xE0D3
#define NPC_STELLA   (NPC_START + 212) // 0xE0D4
#define NPC_CASHMERE (NPC_START + 213) // 0xE0D5
#define NPC_WOOLIO   (NPC_START + 214) // 0xE0D6
#define NPC_COOKIE   (NPC_START + 215) // 0xE0D7
// gamecube additions
#define NPC_MAELLE   (NPC_START + 216) // 0xE0D8
#define NPC_OHARE    (NPC_START + 217) // 0xE0D9
#define NPC_BLISS    (NPC_START + 218) // 0xE0DA
#define NPC_DRIFT    (NPC_START + 219) // 0xE0DB
#define NPC_BUD      (NPC_START + 220) // 0xE0DC
#define NPC_BOOMER   (NPC_START + 221) // 0xE0DD
#define NPC_ELINA    (NPC_START + 222) // 0xE0DE
#define NPC_FLASH    (NPC_START + 223) // 0xE0DF
#define NPC_DOBIE    (NPC_START + 224) // 0xE0E0
#define NPC_FLOSSIE  (NPC_START + 225) // 0xE0E1
#define NPC_ANNALISE (NPC_START + 226) // 0xE0E2
#define NPC_PLUCKY   (NPC_START + 227) // 0xE0E3
#define NPC_FAITH    (NPC_START + 228) // 0xE0E4
#define NPC_YODEL    (NPC_START + 229) // 0xE0E5
#define NPC_ROWAN    (NPC_START + 230) // 0xE0E6
#define NPC_JUNE     (NPC_START + 231) // 0xE0E7
#define NPC_CHERI    (NPC_START + 232) // 0xE0E8
#define NPC_PIGLEG   (NPC_START + 233) // 0xE0E9
#define NPC_ANKHA    (NPC_START + 234) // 0xE0EA
#define NPC_PUNCHY   (NPC_START + 235) // 0xE0EB
#define NPC_END      (NPC_START + 236) // 0xE0EC
#define NPC_TEST0    (NPC_START + 236) // 0xE0EC
#define NPC_TEST1    (NPC_START + 237) // 0xE0ED
#define NPC_ALL_END  (NPC_START + 238) // 0xE0EE

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
#define DUMMY_COUNT 0xF10E
#define DUMMY_COUNT02 0xF10F
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
