#ifndef AC_SET_OVL_INSECT_H
#define AC_SET_OVL_INSECT_H

#include "types.h"
#include "ac_set_manager.h"
#include "ac_insect_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aSOI_TERM_TRANSITION_MAX_DAYS 5

#define aINS_INSECT_TYPE_INVALID -1

#define aSOI_SPAWN_AREA_INVALID -1

enum insect_spawn_area {
    aSOI_SPAWN_AREA_ON_TREE,
    aSOI_SPAWN_AREA_ON_FLOWER,
    aSOI_SPAWN_AREA_RAINING_ON_FLOWER,
    aSOI_SPAWN_AREA_FLYING,
    aSOI_SPAWN_AREA_ON_GROUND,
    aSOI_SPAWN_AREA_IN_BUSH,
    aSOI_SPAWN_AREA_FLYING_NEAR_WATER,
    aSOI_SPAWN_AREA_ON_WATER,
    aSOI_SPAWN_AREA_ON_CANDY,
    aSOI_SPAWN_AREA_ON_TRASH,
    aSOI_SPAWN_AREA_UNDER_ROCK,
    aSOI_SPAWN_AREA_UNDERGROUND,
    aSOI_SPAWN_AREA_FLYING_NEAR_FLOWERS_OR_AROUND, /* this prefers flowers, but will default to "FLYING" if no flowers
                                                      are in the acre */
    aSOI_SPAWN_AREA_NOTHING,

    aSOI_SPAWN_AREA_NUM
};

enum insect_spawn_type {
    aSOI_SPAWN_TYPE_NONE,   /* none/unused? */
    aSOI_SPAWN_TYPE_TOWN,   /* pull from town spawns */
    aSOI_SPAWN_TYPE_ISLAND, /* pull from island spawns */
    aSOI_SPAWN_TYPE_SPIRIT, /* pull from town spawns but force spirit if Wisp is active */

    aSOI_SPAWN_TYPE_NUM
};

enum insect_spawn_category {
    aSOI_SPAWN_CATEGORY_FG_ITEM_RANGE,
    aSOI_SPAWN_CATEGORY_UT_ATTRIBUTE,
    aSOI_SPAWN_CATEGORY_TREE,
    aSOI_SPAWN_CATEGORY_UT_ATTRIBUTE_AND_FG_ITEM_RANGE,

    aSOI_SPAWN_CATEGORY_NUM
};

#define aSOI_SPAWN_NORMAL 0
#define aSOI_SPAWN_TREE 4
#define aSOI_SPAWN_ITEM 6

/**
 * Insect term periods:
 *  TERM0: 11PM-4AM  (5 hours)
 *  TERM1:  4AM-8AM  (4 hours)
 *  TERM2:  8AM-4PM  (8 hours)
 *  TERM3:  4PM-5PM  (1 hour)
 *  TERM4:  5PM-7PM  (2 hours)
 *  TERM5:  7PM-11PM (4 hours)
 **/

#define aSOI_TERM0_START_HR 11 + 12 // 11:00PM
#define aSOI_TERM0_END_HR 3         // 03:59AM
#define aSOI_TERM1_START_HR 4       // 04:00AM
#define aSOI_TERM1_END_HR 7         // 07:59AM
#define aSOI_TERM2_START_HR 8       // 08:00AM
#define aSOI_TERM2_END_HR 3 + 12    // 03:59PM
#define aSOI_TERM3_START_HR 4 + 12  // 04:00PM
#define aSOI_TERM3_END_HR 4 + 12    // 04:59PM
#define aSOI_TERM4_START_HR 5 + 12  // 05:00PM
#define aSOI_TERM4_END_HR 6 + 12    // 06:59PM
#define aSOI_TERM5_START_HR 7 + 12  // 07:00PM
#define aSOI_TERM5_END_HR 10 + 12   // 10:59PM

enum insect_term {
    aSOI_TERM0,
    aSOI_TERM1,
    aSOI_TERM2,
    aSOI_TERM3,
    aSOI_TERM4,
    aSOI_TERM5,

    aSOI_TERM_NUM
};

extern int aSOI_insect_set(SET_MANAGER* set_manager, GAME_PLAY* play);

#ifdef __cplusplus
}
#endif

#endif
