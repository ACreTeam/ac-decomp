#ifndef M_NAME_TABLE_H
#define M_NAME_TABLE_H

#include "types.h"
#include "m_actor_type.h"

/* TODO: these defintions are likely included from an auto-gen source */

#ifdef __cplusplus
extern "C" {
#endif

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

/* Retrieve the item actor's category */
#define ITEM_NAME_GET_TYPE(n) (((n) & 0xF000) >> 12)

#define ITEM_IS_FTR(n) \
  (ITEM_NAME_GET_TYPE(n) == NAME_TYPE_FTR0 || ITEM_NAME_GET_TYPE(n) == NAME_TYPE_FTR1)

#define ITEM_IS_ITEM1(n) (ITEM_NAME_GET_TYPE(n) == NAME_TYPE_ITEM1)

#define GET_NAME_ITEM0_CATEGORY(f) (((f) & 0x0800) >> 11)
#define GET_NAME_ITEM1_CATEGORY(f) (((f) & 0x0F00) >> 8)

#define EMPTY_NO 0x0000

#define FTR_REDALOHASHIRT 0x1814
#define FTR_BLUEALOHASHIRT 0x1818

#define FTR_TAPEDECK 0x1E58

#define ITM_TOOL_START 0x2200
#define ITM_NET ITM_TOOL_START
#define ITM_AXE 0x2201
#define ITM_SHOVEL 0x2202
#define ITM_ROD 0x2203

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
#define ITEM_YELLOW_TULIP_BAG 0x290A

#define ITM_COLLEGERULE 0x2B00

#define FTR_ORANGEBOX 0x30F8

#define DOOR_START 0x4000
#define DOOR0 DOOR_START  /* 0x4000 */
#define DOOR1 (DOOR0 + 1) /* 0x4001 */

#define EXIT_DOOR 0x4080

#define RSV_DOOR 0xFE1B
#define RSV_WALL_NO 0xFFFE /* interior wall item, no collision */
#define RSV_NO 0xFFFF /* reserved space, can't interact but no collision */

#ifdef __cplusplus
}
#endif

#endif
