#include "m_huusui_room_ovl.h"

#include "m_huusui_room.h"
#include "m_actor_type.h"
#include "m_room_type.h"
#include "m_house.h"
#include "m_home_h.h"
#include "m_common_data.h"
#include "m_name_table.h"

#define mHsRm_UNIT_MAX_S 6
#define mHsRm_UNIT_MAX_M 8
#define mHsRm_UNIT_MAX_L 10
#define mHsRm_UNIT_MAX_UPPER mHsRm_UNIT_MAX_M
#define mHsRm_UNIT_MAX_BASEMENT mHsRm_UNIT_MAX_L

#define mHsRm_MONEY_LUCKY_PTS 4
#define mHsRm_GOODS_LUCKY_PTS 8

#define mHsRm_MONEY_BAD_PTS 10
#define mHsRm_GOODS_BAD_PTS 5

typedef struct huusui_room_ftr_info_s {
    u8 huusui_type;
    u8 has_face;
} mHsRm_ftr_info_c;

/* table of feng shui data for every item, clearly copy-pasted... should be mHsRm_ftr_info */
static mHsRm_ftr_info_c mMkRm_ftr_info[FTR_NUM] = {
#include "../src/game/m_huusui_room_ovl_data.inc" /* data moved out of file due to length */
};

/* maximum unit position for each main floor size */
static int mHsRm_unit_max[mHm_HOMESIZE_NUM - 1] = {
    mHsRm_UNIT_MAX_S, /* mHm_HOMESIZE_SMALL */
    mHsRm_UNIT_MAX_M, /* mHm_HOMESIZE_MEDIUM */
    mHsRm_UNIT_MAX_L, /* mHm_HOMESIZE_LARGE */
    mHsRm_UNIT_MAX_L, /* mHm_HOMESIZE_UPPER */
};

/* number of units taken up by each furniture size */
static int mHsRm_unit_value[mRmTp_FTRSIZE_NUM] = {
    1, /* mRmTp_FTRSIZE_1x1 */
    2, /* mRmTp_FTRSIZE_1x2 */
    4, /* mRmTp_FTRSIZE_2x2 */
};

/* table indices below are [directions][points] */

#define mHsRm_WALL_NON (0)                                                                 /* No wall */
#define mHsRm_WALL_STH (1 << mHsRm_DIRECTION_SOUTH)                                        /* South wall */
#define mHsRm_WALL_EST (1 << mHsRm_DIRECTION_EAST)                                         /* East wall */
#define mHsRm_WALL_NTH (1 << mHsRm_DIRECTION_NORTH)                                        /* North wall */
#define mHsRm_WALL_WST (1 << mHsRm_DIRECTION_WEST)                                         /* West wall */
#define mHsRm_WALL_ALL (mHsRm_WALL_STH | mHsRm_WALL_EST | mHsRm_WALL_NTH | mHsRm_WALL_WST) /* any wall */

/* money power info table */
static const int money_power_tbl[mHsRm_HUUSUI_NUM][2] = {
    { mHsRm_WALL_NON, 0 }, /* mHsRm_HUUSUI_NONE */
    { mHsRm_WALL_WST, 4 }, /* mHsRm_HUUSUI_YELLOW */
    { mHsRm_WALL_NON, 0 }, /* mHsRm_HUUSUI_RED */
    { mHsRm_WALL_NTH, 2 }, /* mHsRm_HUUSUI_ORANGE */
    { mHsRm_WALL_STH, 2 }, /* mHsRm_HUUSUI_GREEN */
    { mHsRm_WALL_ALL, 4 }, /* mHsRm_HUUSUI_LUCKY */
};

/* goods power info table */
static const int goods_power_tbl[mHsRm_HUUSUI_NUM][2] = {
    { mHsRm_WALL_NON, 0 }, /* mHsRm_HUUSUI_NONE */
    { mHsRm_WALL_NON, 0 }, /* mHsRm_HUUSUI_YELLOW */
    { mHsRm_WALL_EST, 8 }, /* mHsRm_HUUSUI_RED */
    { mHsRm_WALL_NTH, 4 }, /* mHsRm_HUUSUI_ORANGE */
    { mHsRm_WALL_STH, 4 }, /* mHsRm_HUUSUI_GREEN */
    { mHsRm_WALL_ALL, 8 }, /* mHsRm_HUUSUI_LUCKY */
};

/**
 * @brief Feng Shui scoring algorithm for a single furniture.
 *
 * This function checks which side of the room the furniture is on,
 * along with its orientation. It returns the point score for both
 * money power and goods power into 'money_power' and 'goods_power'.
 * The result can be negative if a 'doll'/'item with a face' is facing
 * the wall.
 *
 * @param ftr The actor furniture number
 * @param ut_x Unit x position
 * @param ut_z Unit z position
 * @param money_power Calculated money power for the furniture position
 * @param goods_power Calculated goods power for the furniture position
 **/
static void mHsRm_EvaluateHuusuiPoint_Single(mActor_name_t ftr, int ut_x, int ut_z, int ut_max, int* money_power,
                                             int* goods_power) {
    int i;
    int ftr_idx;
    int room_side_bits;
    int ut_value;
    int rotation_bits;
    int huusui_type;
    int room_side_tbl[mHsRm_DIRECTION_NUM];
    int rotation_tbl[mHsRm_DIRECTION_NUM];
    mRmTp_FtrPlaceInfoOne_t place_info[mRmTp_FTR_UNIT_MAX];
    int ftr_rot;
    int has_face;
    int start_ut;

    *money_power = 0;
    *goods_power = 0;

    ftr_idx = mRmTp_FtrItemNo2FtrIdx(ftr);
    ftr_rot = FTR_GET_ROTATION(ftr);
    huusui_type = mMkRm_ftr_info[ftr_idx].huusui_type;
    has_face = mMkRm_ftr_info[ftr_idx].has_face;
    ut_value = mHsRm_unit_value[mRmTp_GetFurnitureData(ftr, ut_x, ut_z,
                                                       place_info)]; /* number of units occupied by this furniture */

    /* maximum top/left position for feng shui */
    if (ut_max == mHsRm_UNIT_MAX_S && ut_value == 1) {
        start_ut = 1;
    } else {
        start_ut = 2;
    }

    for (i = 0; i < mHsRm_DIRECTION_NUM; i++) {
        room_side_tbl[i] = 0;
        rotation_tbl[i] = 0;
    }

    /* loop through all units occupied by the furniture and check feng shui parameters on each unit */
    for (i = 0; i < ut_value; i++) {
        if (place_info[i].ut_z <= start_ut) {
            room_side_tbl[mHsRm_DIRECTION_NORTH]++;

            if (place_info[i].ut_z <= 1) {
                rotation_tbl[mHsRm_DIRECTION_NORTH]++;
            }
        } else if (place_info[i].ut_z >= ((ut_max - start_ut) - 1)) {
            room_side_tbl[mHsRm_DIRECTION_SOUTH]++;

            if (place_info[i].ut_z >= ut_max - 2) {
                rotation_tbl[mHsRm_DIRECTION_SOUTH]++;
            }
        }

        if (place_info[i].ut_x <= start_ut) {
            room_side_tbl[mHsRm_DIRECTION_WEST]++;

            if (place_info[i].ut_x <= 1) {
                rotation_tbl[mHsRm_DIRECTION_WEST]++;
            }
        } else if (place_info[i].ut_x >= ((ut_max - start_ut) - 1)) {
            room_side_tbl[mHsRm_DIRECTION_EAST]++;

            if (place_info[i].ut_x >= ut_max - 2) {
                rotation_tbl[mHsRm_DIRECTION_EAST]++;
            }
        }
    }

    room_side_bits = 0;
    rotation_bits = 0;

    /* log positioning & rotation */
    for (i = 0; i < mHsRm_DIRECTION_NUM; i++) {
        /* if all units belonging to this furniture are in the same feng shui room side, add feng shui type */
        if (ut_value == room_side_tbl[i]) {
            room_side_bits |= (1 << i);
        }

        /* if any of the furnitures units are directly adjecent to a wall, mark it for rotation check */
        if ((ut_value >= 2 && rotation_tbl[i] >= 2) || (ut_value == 1 && rotation_tbl[i] >= 1)) {
            rotation_bits |= (1 << i);
        }
    }

    if (huusui_type == mHsRm_HUUSUI_LUCKY) {
        *money_power += mHsRm_MONEY_LUCKY_PTS;
        *goods_power += mHsRm_GOODS_LUCKY_PTS;
    }

    if (room_side_bits != 0) {
        for (i = 0; i < mHsRm_DIRECTION_NUM; i++) {
            if (huusui_type != mHsRm_HUUSUI_LUCKY) {
                /* if the furniture was properly placed entirely in the feng shui area, check points & add */
                if (room_side_bits & (1 << i)) {
                    if (money_power_tbl[huusui_type][0] & (1 << i)) {
                        *money_power += money_power_tbl[huusui_type][1];
                    }

                    if (goods_power_tbl[huusui_type][0] & (1 << i)) {
                        *goods_power += goods_power_tbl[huusui_type][1];
                    }
                }
            }
        }

        /* If the furniture has a "face" (front side), deduct points if that side is facing the wall */
        if (has_face != 0) {
            for (i = 0; i < mHsRm_DIRECTION_NUM; i++) {
                /* check is for furniture is directly adjacent to the given wall and the rotation is the same direction
                 * as the wall */
                if ((rotation_bits & (1 << i)) && (ftr_rot == i)) {
                    *money_power -= mHsRm_MONEY_BAD_PTS;
                    *goods_power -= mHsRm_GOODS_BAD_PTS;
                }
            }
        }
    }
}

/**
 * @brief Scores an entire room's Feng Shui.
 *
 * @param layers Pointer to array of mHm_lyr_c room layers to score (main & secondary)
 * @param ut_max The maximum unit position (both x & z) for the room's size
 * @param money_power Calculated room money power
 * @param goods_power Calculated room goods power
 **/
static void mHsRm_EvaluateHuusuiPoint(mHm_lyr_c** layers, int ut_max, int* money_power, int* goods_power) {
    mActor_name_t item_no;
    int room_money_power;
    int room_goods_power;
    int lyr;
    int ut_x;
    int ut_z;
    int item_money_power;
    int item_goods_power;
    mActor_name_t* fg_p_top;
    int z;
    
    room_money_power = 0;
    room_goods_power = 0;

    /* loop through each unit on both main & secondary layers and score each ftr */
    for (lyr = 0; lyr < 2; lyr++) {
        fg_p_top = (mActor_name_t*)layers[lyr];
        for (ut_z = 0; ut_z < ut_max; ut_z++) {
            int z = ut_z * UT_X_NUM;

            for (ut_x = 0; ut_x < ut_max; ut_x++) {
                item_no = *((fg_p_top + z + ut_x));
                if (ITEM_IS_FTR(item_no)) {
                    mHsRm_EvaluateHuusuiPoint_Single(item_no, ut_x, ut_z, ut_max, &item_money_power, &item_goods_power);
                    room_money_power += item_money_power;
                    room_goods_power += item_goods_power;
                }
            }
        }
    }

    *money_power += room_money_power;
    *goods_power += room_goods_power;
}

/**
 * @brief Main Feng Shui scoring function. Will score all three rooms in house
 * depending on house size.
 *
 * @param player_no The index of the player whose house will be scored for Feng Shui
 **/
extern void mHsRm_HuusuiRoomOvl(int player_no) {
    int ut_max;
    mHm_hs_c* home;
    int money_power;
    int goods_power;
    mHm_lyr_c* layers[2];
    f32 real_goods_power;

    home = Save_Get(homes + mHS_get_arrange_idx(player_no));
    money_power = 0;
    goods_power = 0;

    /* Evaluate the main room first */
    ut_max = mHsRm_unit_max[home->size_info.size];
    layers[0] = &home->floors[mHm_ROOM_MAIN].layer_main;
    layers[1] = &home->floors[mHm_ROOM_MAIN].layer_secondary;
    mHsRm_EvaluateHuusuiPoint(layers, ut_max, &money_power, &goods_power);

    /* Evaluate the second floor next if it exists */
    if (home->size_info.size == mHm_HOMESIZE_UPPER) {
        layers[0] = &home->floors[mHm_ROOM_UPPER].layer_main;
        layers[1] = &home->floors[mHm_ROOM_UPPER].layer_secondary;
        mHsRm_EvaluateHuusuiPoint(layers, mHsRm_UNIT_MAX_UPPER, &money_power, &goods_power);
    }

    /* Finally, evaluate the basement if it exists */
    if (home->flags.has_basement == TRUE) {
        layers[0] = &home->floors[mHm_ROOM_BASEMENT].layer_main;
        layers[1] = &home->floors[mHm_ROOM_BASEMENT].layer_secondary;
        mHsRm_EvaluateHuusuiPoint(layers, mHsRm_UNIT_MAX_BASEMENT, &money_power, &goods_power);
    }

    /* Goods power is clamed to its upper bound of 40 */
    if (goods_power > mHsRm_GOODS_POWER_MAX) {
        goods_power = mHsRm_GOODS_POWER_MAX;
    }

    /* Adjust goods power by dividing it in half and rounding up */
    real_goods_power = (f32)goods_power * 0.5f;
    goods_power = real_goods_power;

    /* Always round up if there's any fractional part to goods_power */
    real_goods_power -= goods_power;
    if (real_goods_power > 0.0f) {
        goods_power++;
    }

    Common_Set(money_power, money_power);
    Common_Set(goods_power, goods_power);
}
