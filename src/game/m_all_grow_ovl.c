#include "m_all_grow.h"

#include "libultra/libultra.h"
#include "m_common_data.h"
#include "m_name_table.h"
#include "m_island.h"
#include "m_collision_bg.h"
#include "m_snowman.h"
#include "m_home.h"
#include "m_house.h"
#include "m_snowman.h"
#include "m_shop.h"
#include "m_scene_table.h"

static u8 l_candidate_num[FG_BLOCK_TOTAL_NUM];

static s8 l_non_area[mAGrw_CHECK_CANCEL_NUM][4] = {
    /*x0  x1  z0  z1*/
    { 0, 0, -1, 0 },  { -1, 1, -2, -1 }, { -1, 0, -1, 0 }, { -1, 1, -3, 2 }, { -1, 2, -2, 2 }, { -2, 1, -2, 2 },
    { -2, 1, -3, 2 }, { -1, 0, -2, 0 },  { -3, 1, -4, 2 }, { -3, 2, -5, 2 }, { -3, 3, -4, 2 }
};

typedef struct hide_area_s {
    int x_ofs;
    int z_ofs;
} mAGrw_HideArea_c;

typedef struct hide_area_table_s {
    int num;
    mAGrw_HideArea_c* hide_p;
} mAGrw_HideAreaTable_c;

static mAGrw_HideArea_c hide_3_2[1] = { { 0, -1 } };

static mAGrw_HideArea_c hide_2_2[2] = {
    { -1, -1 },
    { 1, -1 },
};

static mAGrw_HideArea_c hide_3_6[2] = { { -1, -2 }, { 1, -2 } };

static mAGrw_HideArea_c hide_4_6[2] = { { -2, -1 }, { 1, -1 } };

static mAGrw_HideArea_c hide_2_3[2] = { { -1, -2 }, { 0, -2 } };

static mAGrw_HideArea_c hide_5_7[2] = { { -3, -2 }, { 1, -2 } };

static mAGrw_HideArea_c hide_6_8[2] = { { -3, -2 }, { 2, -2 } };

static mAGrw_HideArea_c hide_7_7[2] = { { -3, -3 }, { 3, -3 } };

static mAGrw_HideAreaTable_c l_hide_area_table[mAGrw_CHECK_CANCEL_NUM] = {
    { 0, NULL },     { 1, hide_3_2 }, { 2, hide_2_2 }, { 2, hide_3_6 }, { 0, NULL },     { 0, NULL },
    { 2, hide_4_6 }, { 2, hide_2_3 }, { 2, hide_5_7 }, { 2, hide_6_8 }, { 2, hide_7_7 },
};

static mActor_name_t l_magrw_change_tree[3] = { TREE, CEDAR_TREE, GOLD_TREE };

static mActor_name_t l_magrw_bee_table[3] = { TREE_BEES, CEDAR_TREE_BEES, GOLD_TREE_BEES };

static mActor_name_t l_magrw_ftr_table[3] = { TREE_FTR, CEDAR_TREE_FTR, GOLD_TREE_FTR };

static mActor_name_t l_magrw_smn_table[3] = { TREE_BELLS, CEDAR_TREE_BELLS, GOLD_TREE_BELLS };

static void mAGrw_ClearSSPosInfo_com(mAGrw_SSPosInfo_c* pos_info) {
    bzero(pos_info, sizeof(mAGrw_SSPosInfo_c));
}

static void mAGrw_ClearStonePosInfo(mAGrw_AllGrow_c* allgrow, int idx) {
    if (idx >= 0 && idx < TOTAL_PLAYER_NUM) {
        mAGrw_ClearSSPosInfo_com(&allgrow->stone_pos[idx]);
    }
}

static void mAGrw_ClearShinePosInfo(mAGrw_AllGrow_c* allgrow, int idx) {
    if (idx >= 0 && idx < TOTAL_PLAYER_NUM) {
        mAGrw_ClearSSPosInfo_com(&allgrow->shine_pos[idx]);
    }
}

static int mAGrw_CheckFreeSSPosInfo_com(mAGrw_SSPosInfo_c* ss_pos_info) {
    int free = FALSE;

    if (ss_pos_info->block_x == 0 && ss_pos_info->block_z == 0) {
        free = TRUE;
    }

    return free;
}

static mActor_name_t mAGrw_ToMoneyStone(mActor_name_t stone) {
    mActor_name_t money_stone = stone - ROCK_A;
    return money_stone + MONEY_ROCK_A;
}

static mActor_name_t mAGrw_ToStone(mActor_name_t money_stone) {
    mActor_name_t stone = money_stone - MONEY_ROCK_A;
    return stone + ROCK_A;
}

#define mAGrw_IsStone(item) ((item) >= ROCK_A && (item) <= ROCK_E)

#define mAGrw_IsMoneyStone(item) (((item) >= MONEY_ROCK_A && (item) <= MONEY_ROCK_E) || (item) == MONEY_FLOWER_SEED)

#define mAGrw_IsPosInfoGood(pos_info)                                                                              \
    ((pos_info)->block_x != 0 && (pos_info)->block_x < FG_BLOCK_X_NUM + 1) &&                                      \
        ((pos_info)->block_z != 0 && (pos_info)->block_z < FG_BLOCK_Z_NUM + 1) && ((pos_info)->ut_x < UT_X_NUM) && \
        ((pos_info)->ut_z < UT_Z_NUM)

extern void mAGrw_ClearMoneyStoneShineGround() {
    mFM_fg_c* block_items = Save_Get(fg[0]);
    mActor_name_t* items;
    mAGrw_AllGrow_c* allgrow = Save_GetPointer(allgrow_ss_pos_info);
    int updated_money_stone = FALSE;
    int updated_shine_spot = FALSE;
    int acre;
    int unit;
    int player_no = Common_Get(player_no);

    for (acre = 0; acre < FG_BLOCK_TOTAL_NUM; acre++) {
        items = block_items->items[0];

        for (unit = 0; unit < UT_TOTAL_NUM; unit++) {
            if (mAGrw_IsMoneyStone(*items)) {
                *items = mAGrw_ToStone(*items);
                updated_money_stone = TRUE;
            } else if (*items == SHINE_SPOT) {
                *items = EMPTY_NO;
                updated_shine_spot = TRUE;
            }

            if (updated_money_stone == TRUE && updated_shine_spot == TRUE) {
                acre = FG_BLOCK_TOTAL_NUM;
                break;
            }

            items++;
        }

        block_items++;
    }

    if (updated_money_stone == FALSE) {
        mAGrw_ClearStonePosInfo(allgrow, player_no);
    }

    if (updated_shine_spot == FALSE) {
        mAGrw_ClearShinePosInfo(allgrow, player_no);
    }
}

extern void mAGrw_ClearAllShine_Stone() {
    mFM_fg_c* block_items = Save_Get(fg[0]);
    mActor_name_t* items;
    int acre;
    int unit;

    for (acre = 0; acre < FG_BLOCK_TOTAL_NUM; acre++) {
        items = block_items->items[0];

        for (unit = 0; unit < UT_TOTAL_NUM; unit++) {
            if (mAGrw_IsMoneyStone(*items)) {
                *items = mAGrw_ToStone(*items);
            } else if (*items == SHINE_SPOT) {
                *items = EMPTY_NO;
            }

            items++;
        }

        block_items++;
    }
}

static void mAGrw_SetShineGround_player(mAGrw_AllGrow_c* allgrow, int player_no) {
    if (player_no >= mPr_PLAYER_0 && player_no < mPr_PLAYER_NUM) {
        mAGrw_SSPosInfo_c* player_ss_pos_info = &allgrow->shine_pos[player_no];

        if (mAGrw_CheckFreeSSPosInfo_com(player_ss_pos_info) == FALSE) {
            if (mAGrw_IsPosInfoGood(player_ss_pos_info)) {
                int block_x = player_ss_pos_info->block_x - 1;
                int block_z = player_ss_pos_info->block_z - 1;
                mFM_fg_c* fg_block = &Save_Get(fg[block_z][block_x]);
                mActor_name_t* item = &fg_block->items[player_ss_pos_info->ut_z][player_ss_pos_info->ut_x];

                if (*item == EMPTY_NO) {
                    *item = SHINE_SPOT;
                }
            } else {
                mAGrw_ClearSSPosInfo_com(player_ss_pos_info); // invalid shine spot position
            }
        } else {
            mAGrw_ClearSSPosInfo_com(player_ss_pos_info); // Ensure it's cleared?
        }
    }
}

static void mAGrw_SetMoneyStone_player(mAGrw_AllGrow_c* allgrow, int player_no) {
    if (player_no >= mPr_PLAYER_0 && player_no < mPr_PLAYER_NUM) {
        mAGrw_SSPosInfo_c* player_ss_pos_info = &allgrow->stone_pos[player_no];

        if (mAGrw_CheckFreeSSPosInfo_com(player_ss_pos_info) == FALSE) {
            if ((player_ss_pos_info->block_x != 0 && player_ss_pos_info->block_x < FG_BLOCK_X_NUM + 1) &&
                (player_ss_pos_info->block_z != 0 && player_ss_pos_info->block_z < FG_BLOCK_Z_NUM + 1) &&
                (player_ss_pos_info->ut_x < UT_X_NUM) && (player_ss_pos_info->ut_z < UT_Z_NUM)) {
                int block_x = player_ss_pos_info->block_x - 1;
                int block_z = player_ss_pos_info->block_z - 1;
                mFM_fg_c* fg_block = &Save_Get(fg[block_z][block_x]);
                mActor_name_t* item = &fg_block->items[player_ss_pos_info->ut_z][player_ss_pos_info->ut_x];

                if (!mAGrw_IsMoneyStone(*item) && (mAGrw_IsStone(*item) || mAGrw_IsMoneyStone(*item))) {
                    *item = mAGrw_ToMoneyStone(*item);
                } else if (!mAGrw_IsStone(*item) && !mAGrw_IsMoneyStone(*item)) {
                    mAGrw_ClearSSPosInfo_com(player_ss_pos_info); // not a stone at this location
                }
            } else {
                mAGrw_ClearSSPosInfo_com(player_ss_pos_info); // invalid shine spot position
            }
        } else {
            mAGrw_ClearSSPosInfo_com(player_ss_pos_info); // Ensure it's cleared?
        }
    }
}

extern void mAGrw_RestoreStoneShine(int player_no) {
    mAGrw_AllGrow_c* ss_pos_info = Save_GetPointer(allgrow_ss_pos_info);
    if (player_no >= mPr_PLAYER_0 && player_no < mPr_PLAYER_NUM) {
        mAGrw_SetMoneyStone_player(ss_pos_info, player_no);
        mAGrw_SetShineGround_player(ss_pos_info, player_no);
    }
}

static int mAGrw_CheckMoneyStonePos(mAGrw_SSPosInfo_c* pos_info) {
    int res = FALSE;

    if (mAGrw_CheckFreeSSPosInfo_com(pos_info) == FALSE && mAGrw_IsPosInfoGood(pos_info)) {
        int block_x = pos_info->block_x - 1;
        int block_z = pos_info->block_z - 1;
        mFM_fg_c* fg_block = &Save_Get(fg[block_z][block_x]);
        mActor_name_t item = fg_block->items[pos_info->ut_z][pos_info->ut_x];

        if ((item >= MONEY_ROCK_A && item <= MONEY_ROCK_E) || item == MONEY_FLOWER_SEED) {
            res = TRUE;
        }
    }

    return res;
}

static void mAGrw_ClearGrowInfo(mAGrw_GrowInfo_c* grow_info) {
    bzero(grow_info, sizeof(mAGrw_GrowInfo_c));
}

static u8 mAGrw_GetTreeGrowCond(int ut_x, int ut_z) {
    return (ut_x ^ ut_z) & 1;
}

static void mAGrw_ClearAroundBlockInfo(mAGrw_GrowInfo_c* grow_info) {
    mFM_fg_c** around_block = grow_info->around_block;
    int i;

    for (i = 0; i < mAGrw_AROUND_NUM; i++) {
        *around_block = NULL;
        around_block++;
    }
}

static void mAGrw_SetAroundBlockInfo(mAGrw_GrowInfo_c* grow_info, int block_x, int block_z) {
    mAGrw_ClearAroundBlockInfo(grow_info);

    if (block_x > 0) {
        grow_info->around_block[mAGrw_AROUND_LEFT] = Save_GetPointer(fg[block_z][block_x - 1]);
    }

    if (block_x < FG_BLOCK_X_NUM - 1) {
        grow_info->around_block[mAGrw_AROUND_RIGHT] = Save_GetPointer(fg[block_z][block_x + 1]);
    }

    if (block_z > 0) {
        grow_info->around_block[mAGrw_AROUND_TOP] = Save_GetPointer(fg[block_z - 1][block_x]);
    }

    if (block_z < FG_BLOCK_Z_NUM - 1) {
        /* @BUG - should be fg[block_z + 1][block_x] */
        grow_info->around_block[mAGrw_AROUND_BOTTOM] = Save_GetPointer(fg[block_z + 1][block_z]);
    }
}

static void mAGrw_SetAroundBlockInfoIsland(mAGrw_GrowInfo_c* grow_info, int island_side) {
    mAGrw_ClearAroundBlockInfo(grow_info);

    if (island_side == mISL_ISLAND_BLOCK_LEFT) {
        grow_info->around_block[mAGrw_AROUND_RIGHT] = Save_GetPointer(island.fgblock[0][1]);
    } else if (island_side == mISL_ISLAND_BLOCK_RIGHT) {
        grow_info->around_block[mAGrw_AROUND_LEFT] = Save_GetPointer(island.fgblock[0][0]);
    }
}

static lbRTC_day_t mAGrw_get_pastDays(lbRTC_time_c* now, lbRTC_time_c* last_grow_time) {
    lbRTC_time_c temp;
    int past_days;

    lbRTC_TimeCopy(&temp, last_grow_time);

    for (past_days = 0; past_days <= mAGrw_MAX_PAST_DAYS; past_days++) {
        if (lbRTC_IsOverTime(now, &temp) == lbRTC_OVER) {
            break;
        }

        lbRTC_Add_DD(&temp, 1);
    }

    return past_days;
}

static int mAGrw_CheckSpoilKabuTime(lbRTC_time_c* grow_time, lbRTC_time_c* now) {
    lbRTC_time_c temp;
    int days = 0;
    int spoil = FALSE;

    lbRTC_TimeCopy(&temp, grow_time);

    if (temp.weekday != lbRTC_SUNDAY && temp.weekday < lbRTC_WEEK) {
        days = lbRTC_WEEK - temp.weekday;
    }

    lbRTC_Add_DD(&temp, days);

    if (lbRTC_IsOverTime(&temp, now) == lbRTC_OVER) {
        spoil = TRUE;
    }

    return spoil;
}

static int mAGrw_CheckFlowerTime(lbRTC_time_c* time) {
    int res = mAGrw_NOT_FLOWER_TIME;
    lbRTC_day_t day = time->day;

    if ((time->month == lbRTC_FEBRUARY && day >= 25) || (time->month >= lbRTC_MARCH && time->month <= lbRTC_NOVEMBER) ||
        (time->month == lbRTC_DECEMBER && day < 10)) {
        res = mAGrw_FLOWER_TIME;
    }

    return res;
}

static int aAGrw_GrowFlower(mActor_name_t* item) {
    int res = FALSE;

    if (*item >= FLOWER_LEAVES_PANSIES0 && *item <= FLOWER_TULIP2) {
        if (*item <= FLOWER_LEAVES_TULIP2) {
            *item += (FLOWER_PANSIES0 - FLOWER_LEAVES_PANSIES0);
        }

        res = TRUE;
    }

    return res;
}

static void mAGrw_GetUpUt(mActor_name_t** ut_p, mActor_name_t* ut, mFM_fg_c* around, int ut_x, int ut_z) {
    if (ut_z > 0) {
        *ut_p = ut - UT_Z_NUM;
    } else if (around != NULL) {
        *ut_p = &around->items[UT_Z_NUM - 1][ut_x];
    }
}

static void mAGrw_GetDownUt(mActor_name_t** ut_p, mActor_name_t* ut, mFM_fg_c* around, int ut_x, int ut_z) {
    if (ut_z < UT_Z_NUM - 1) {
        *ut_p = ut + UT_Z_NUM;
    } else if (around != NULL) {
        *ut_p = &around->items[0][ut_x];
    }
}

static void mAGrw_GetLeftUt(mActor_name_t** ut_p, mActor_name_t* ut, mFM_fg_c* around, int ut_x, int ut_z) {
    if (ut_x > 0) {
        *ut_p = ut - 1;
    } else if (around != NULL) {
        *ut_p = &around->items[ut_z][UT_X_NUM - 1];
    }
}

static void mAGrw_GetRightUt(mActor_name_t** ut_p, mActor_name_t* ut, mFM_fg_c* around, int ut_x, int ut_z) {
    if (ut_x < UT_X_NUM - 1) {
        *ut_p = ut + 1;
    } else if (around != NULL) {
        *ut_p = &around->items[ut_z][0];
    }
}

static void mAGrw_KillTree(mActor_name_t* tree) {
    static mActor_name_t d_table[mNT_TREE_TYPE_NUM] = { DEAD_SAPLING, DEAD_PALM_SAPLING, DEAD_CEDAR_SAPLING,
                                                        DEAD_GOLD_SAPLING };

    int type = FGTreeType_check(*tree);

    if (type < 0 || type >= mNT_TREE_TYPE_NUM) {
        type = mNT_TREE_TYPE_NORMAL;
    }

    *tree = d_table[type];
}

typedef void (*mAGrw_GET_NEAR_PROC)(mActor_name_t**, mActor_name_t*, mFM_fg_c*, int, int);

static int mAGrw_CheckNearTree(mActor_name_t* item, mAGrw_GrowInfo_c* grow_info, int ut_x, int ut_z) {
    static mAGrw_GET_NEAR_PROC get_near[mAGrw_AROUND_NUM] = { &mAGrw_GetUpUt, &mAGrw_GetDownUt, &mAGrw_GetLeftUt,
                                                              &mAGrw_GetRightUt };

    mActor_name_t* near;
    int res = FALSE;
    int i;

    if (*item == TREE_SAPLING || *item == TREE_APPLE_SAPLING || *item == TREE_ORANGE_SAPLING ||
        *item == TREE_PEACH_SAPLING || *item == TREE_PEAR_SAPLING || *item == TREE_CHERRY_SAPLING ||
        *item == TREE_1000BELLS_SAPLING || *item == TREE_10000BELLS_SAPLING || *item == TREE_30000BELLS_SAPLING ||
        *item == TREE_100BELLS_SAPLING || *item == TREE_PALM_SAPLING || *item == CEDAR_TREE_SAPLING ||
        *item == GOLD_TREE_SAPLING) {
        if (mAGrw_GetTreeGrowCond(ut_x, ut_z) == TRUE) {
            res = TRUE;
            for (i = 0; i < mAGrw_AROUND_NUM; i++) {
                near = NULL;

                (*get_near[i])(&near, item, grow_info->around_block[i], ut_x, ut_z);

                if (near != NULL) {
                    if ((*near >= TREE_SAPLING && *near <= TREE_30000BELLS) ||
                        (*near >= TREE_100BELLS_SAPLING && *near <= TREE_PALM_FRUIT) ||
                        (*near >= CEDAR_TREE_SAPLING && *near <= CEDAR_TREE) ||
                        (*near >= GOLD_TREE_SAPLING && *near <= GOLD_TREE) ||
                        (*near == TREE_BEES || *near == TREE_FTR || *near == TREE_LIGHTS || *near == TREE_PRESENT) ||
                        (*near == TREE_BELLS) ||
                        (*near == CEDAR_TREE_BELLS || *near == CEDAR_TREE_FTR || *near == CEDAR_TREE_BEES) ||
                        (*near == GOLD_TREE_BELLS || *near == GOLD_TREE_FTR || *near == GOLD_TREE_BEES ||
                         *near == CEDAR_TREE_LIGHTS) ||
                        (*near >= TREE_STUMP001 && *near <= TREE_STUMP004) ||
                        (*near >= TREE_PALM_STUMP001 && *near <= TREE_PALM_STUMP004) ||
                        (*near >= CEDAR_TREE_STUMP001 && *near <= CEDAR_TREE_STUMP004) ||
                        (*near >= GOLD_TREE_STUMP001 && *near <= GOLD_TREE_STUMP004)) {
                        mAGrw_KillTree(item);
                        res = FALSE;
                        break;
                    }
                }
            }
        } else {
            for (i = 0; i < mAGrw_AROUND_NUM; i++) {
                near = NULL;

                (*get_near[i])(&near, item, grow_info->around_block[i], ut_x, ut_z);

                if (near != NULL) {
                    if (
                        /* Trees */
                        ((*near >= TREE_SAPLING && *near <= TREE_30000BELLS) ||
                         (*near >= TREE_100BELLS_SAPLING && *near <= TREE_PALM_FRUIT) ||
                         (*near >= CEDAR_TREE_SAPLING && *near <= CEDAR_TREE) ||
                         (*near >= GOLD_TREE_SAPLING && *near <= GOLD_TREE) ||
                         (*near == TREE_BEES || *near == TREE_FTR || *near == TREE_LIGHTS || *near == TREE_PRESENT ||
                          *near == TREE_BELLS) ||
                         (*near == CEDAR_TREE_BELLS || *near == CEDAR_TREE_FTR || *near == CEDAR_TREE_BEES) ||
                         (*near == CEDAR_TREE_LIGHTS) ||
                         (*near == GOLD_TREE_BELLS || *near == GOLD_TREE_FTR || *near == GOLD_TREE_BEES)) &&
                            /* Saplings */
                            (*near != TREE_SAPLING && *near != TREE_APPLE_SAPLING && *near != TREE_ORANGE_SAPLING &&
                             *near != TREE_PEACH_SAPLING && *near != TREE_PEAR_SAPLING &&
                             *near != TREE_CHERRY_SAPLING && *near != TREE_1000BELLS_SAPLING &&
                             *near != TREE_10000BELLS_SAPLING && *near != TREE_30000BELLS_SAPLING &&
                             *near != TREE_100BELLS_SAPLING && *near != TREE_PALM_SAPLING &&
                             *near != CEDAR_TREE_SAPLING && *near != GOLD_TREE_SAPLING) ||
                        /* Stumps */
                        ((*near >= TREE_STUMP001 && *near <= TREE_STUMP004) ||
                         (*near >= TREE_PALM_STUMP001 && *near <= TREE_PALM_STUMP004) ||
                         (*near >= CEDAR_TREE_STUMP001 && *near <= CEDAR_TREE_STUMP004) ||
                         (*near >= GOLD_TREE_STUMP001 && *near <= GOLD_TREE_STUMP004))) {
                        mAGrw_KillTree(item);
                    }
                }
            }

            /* @BUG should be && */
            if (*item != DEAD_SAPLING || *item != DEAD_PALM_SAPLING || *item != DEAD_CEDAR_SAPLING ||
                *item != DEAD_GOLD_SAPLING) {
                res = TRUE;
            }
        }
    } else {
        res = TRUE;
    }

    return res;
}

static int mAGrw_CheckAppleTree(mActor_name_t item, int block_height, int ocean_row) {
    int res = FALSE;

    if (item >= TREE_APPLE_SAPLING && item <= TREE_APPLE_FRUIT) {
        res = TRUE;
    }

    return res;
}

static int mAGrw_CheckChestnutTree(mActor_name_t item, int block_height, int ocean_row) {
    int res = FALSE;

    if (item >= TREE_CHERRY_SAPLING && item <= TREE_CHERRY_FRUIT) {
        res = TRUE;
    }

    return res;
}

static int mAGrw_CheckPearTree(mActor_name_t item, int block_height, int ocean_row) {
    int res = FALSE;

    if (item >= TREE_PEAR_SAPLING && item <= TREE_PEAR_FRUIT) {
        res = TRUE;
    }

    return res;
}

static int mAGrw_CheckPeachTree(mActor_name_t item, int block_height, int ocean_row) {
    int res = FALSE;

    if (item >= TREE_PEACH_SAPLING && item <= TREE_PEACH_FRUIT) {
        res = TRUE;
    }

    return res;
}

static int mAGrw_CheckOrangeTree(mActor_name_t item, int block_height, int ocean_row) {
    int res = FALSE;

    if (item >= TREE_ORANGE_SAPLING && item <= TREE_ORANGE_FRUIT) {
        res = TRUE;
    }

    return res;
}

static int mAGrw_CheckNormalTree(mActor_name_t item, int block_height, int ocean_row) {
    int res = FALSE;

    if (item >= TREE_SAPLING && item <= TREE) {
        res = TRUE;
    }

    return res;
}

static int mAGrw_CheckMoney(mActor_name_t item, int block_height, int ocean_row) {
    int res = FALSE;

    if ((item >= TREE_1000BELLS_SAPLING && item <= TREE_30000BELLS) ||
        (item >= TREE_100BELLS_SAPLING && item <= TREE_100BELLS)) {
        res = TRUE;
    }

    return res;
}

static int mAGrw_CheckPalmTree(mActor_name_t item, int block_height, int ocean_row) {
    int res = FALSE;

    if (ocean_row == TRUE && item >= TREE_PALM_SAPLING && item <= TREE_PALM_FRUIT) {
        res = TRUE;
    }

    return res;
}

static int mAGrw_CheckCedarTree(mActor_name_t item, int block_height, int ocean_row) {
    int res = FALSE;

    if (block_height >= 1 && item >= CEDAR_TREE_SAPLING && item <= CEDAR_TREE) {
        res = TRUE;
    }

    return res;
}

static int mAGrw_CheckGoldTree(mActor_name_t item, int block_height, int ocean_row) {
    int res = FALSE;

    /* @BUG - Should be item <= GOLD_TREE */
    if (item >= GOLD_TREE_SAPLING && item <= GOLD_TREE_SHOVEL) {
        res = TRUE;
    }

    return res;
}

static int mAGrw_CheckKillPalmTree(mActor_name_t item, int block_height, int ocean_row) {
    int res = FALSE;

    if (ocean_row == FALSE && item >= TREE_PALM_SAPLING && item <= TREE_PALM_FRUIT) {
        res = TRUE;
    }

    return res;
}

static int mAGrw_CheckKillCedarTree(mActor_name_t item, int block_height, int ocean_row) {
    int res = FALSE;

    if (block_height <= 0 && item >= CEDAR_TREE_SAPLING && item <= CEDAR_TREE) {
        res = TRUE;
    }

    return res;
}

static void mAGrw_GrowTree_sub(mActor_name_t* item, int check_plant, int past_days) {
    *item = bg_item_fg_sub_tree_grow(*item, past_days - 1, check_plant);
}

typedef int (*mAGrw_CHECK_TREE_PROC)(mActor_name_t, int, int);

static int mAGrw_GrowTree(mActor_name_t* item, mAGrw_GrowInfo_c* grow_info, int ut_x, int ut_z, int check_plant,
                          int past_days, int block_height, int ocean_row) {
    static mAGrw_CHECK_TREE_PROC check_tree_proc[mAGrw_TREE_TYPE_NUM] = {
        &mAGrw_CheckAppleTree,  &mAGrw_CheckChestnutTree, &mAGrw_CheckPearTree, &mAGrw_CheckPeachTree,
        &mAGrw_CheckOrangeTree, &mAGrw_CheckNormalTree,   &mAGrw_CheckMoney,    &mAGrw_CheckPalmTree,
        &mAGrw_CheckCedarTree,  &mAGrw_CheckGoldTree
    };

    static mAGrw_CHECK_TREE_PROC kill_tree_proc[mAGrw_KILL_TREE_NUM] = { &mAGrw_CheckKillPalmTree,
                                                                         &mAGrw_CheckKillCedarTree };

    int res = FALSE;

    if ((*item >= TREE_SAPLING && *item <= TREE_30000BELLS) ||
        (*item >= TREE_100BELLS_SAPLING && *item <= TREE_PALM_FRUIT) ||
        (*item >= CEDAR_TREE_SAPLING && *item <= CEDAR_TREE) || (*item >= GOLD_TREE_SAPLING && *item <= GOLD_TREE)) {
        if (mAGrw_CheckNearTree(item, grow_info, ut_x, ut_z) == TRUE) {
            int i;

            for (i = 0; i < mAGrw_TREE_TYPE_NUM; i++) {
                if ((*check_tree_proc[i])(*item, block_height, ocean_row) == TRUE) {
                    mAGrw_GrowTree_sub(item, check_plant, past_days);
                    break;
                }
            }

            if (i == mAGrw_TREE_TYPE_NUM) {
                for (i = 0; i < mAGrw_KILL_TREE_NUM; i++) {
                    if ((*kill_tree_proc[i])(*item, block_height, ocean_row) == TRUE) {
                        mAGrw_KillTree(item);
                        break;
                    }
                }
            }
        }

        res = TRUE;
    }

    return res;
}

static int mAGrw_GrowPlant_First(mActor_name_t* item, mAGrw_GrowInfo_c* grow_info) {
    int res = FALSE;

    if (ITEM_NAME_GET_TYPE(*item) == NAME_TYPE_ITEM0 && ITEM_NAME_GET_CAT(*item) == ENV_CATEGORY &&
        grow_info->check_plant != -1) {
        res = aAGrw_GrowFlower(item);
    }

    return res;
}

static int mAGrw_GrowPlant(mActor_name_t* item, mAGrw_GrowInfo_c* grow_info) {
    int res = FALSE;

    if (ITEM_NAME_GET_TYPE(*item) == NAME_TYPE_ITEM0) {
        int category = ITEM_NAME_GET_CAT(*item);

        if (category == ENV_CATEGORY) {
            switch (grow_info->check_plant) {
                case -1: {
                    *item = EMPTY_NO;
                    res = TRUE;

                    break;
                }

                case mCoBG_PLANT0: {
                    res = aAGrw_GrowFlower(item);

                    if (res == FALSE) {
                        if (IS_ITEM_ALIVE_TREE(*item)) {
                            mAGrw_KillTree(item);
                            res = TRUE;
                        } else if (IS_ITEM_DEAD_SAPLING(*item)) {
                            *item = EMPTY_NO; /* Clear dead saplings */
                            res = TRUE;
                        }
                    }

                    break;
                }

                default: {
                    res = aAGrw_GrowFlower(item);

                    if (res == FALSE) {
                        res = mAGrw_GrowTree(item, grow_info, grow_info->ut_x, grow_info->ut_z, grow_info->check_plant,
                                             grow_info->past_days, grow_info->block_height, grow_info->ocean_row);

                        if (res == FALSE && IS_ITEM_DEAD_SAPLING(*item)) {
                            *item = EMPTY_NO;
                            res = TRUE;
                        }
                    }
                    break;
                }
            }
        } else if (IS_ITEM_GRASS(*item)) {
            switch (grow_info->check_plant) {
                case -1: {
                    *item = EMPTY_NO;
                    break;
                }
            }

            res = TRUE;
        }
    }

    return res;
}

static int mAGrw_MeltSnowman(mActor_name_t* item, mAGrw_GrowInfo_c* grow_info) {
    return mSN_MeltSnowman(item, grow_info->past_days);
}

static void mAGrw_MakeGrassTable(mActor_name_t* grass_table) {
    static mActor_name_t base_grass_table[mAGrw_GRASS_TABLE_NUM] = { GRASS_A, GRASS_A, GRASS_A, GRASS_A,
                                                                     GRASS_B, GRASS_B, GRASS_B, GRASS_B,
                                                                     GRASS_C, GRASS_C, GRASS_C, GRASS_C };

    int i;

    for (i = 0; i < mAGrw_GRASS_TABLE_NUM; i++) {
        grass_table[i] = base_grass_table[i];
    }

    for (i = 0; i < 4; i++) {
        int a = RANDOM(mAGrw_GRASS_TABLE_NUM);
        int b = RANDOM(mAGrw_GRASS_TABLE_NUM);
        mActor_name_t temp;

        temp = grass_table[a];
        grass_table[a] = grass_table[b];
        grass_table[b] = temp;
    }
}

static int mAGrw_SpoilKabu(mActor_name_t* item, mAGrw_GrowInfo_c* grow_info) {
    int res = FALSE;

    if (ITEM_NAME_GET_TYPE(*item) == NAME_TYPE_ITEM1 && ITEM_NAME_GET_CAT(*item) == ITEM1_CAT_KABU) {
        if (grow_info != NULL) {
            if (grow_info->spoil_kabu == TRUE) {
                *item = ITM_KABU_SPOILED;
            }
        } else {
            *item = ITM_KABU_SPOILED;
        }

        res = TRUE;
    }

    return res;
}

static int mAGrw_ClearSpoiledKabu(mActor_name_t* item, mAGrw_GrowInfo_c* grow_info) {
    int res = FALSE;

    if (*item == ITM_KABU_SPOILED) {
        *item = EMPTY_NO;
        res = TRUE;
    }

    return res;
}

static int mAGrw_ClearShineGround(mActor_name_t* item, mAGrw_GrowInfo_c* grow_info) {
    int res = FALSE;

    if (*item == SHINE_SPOT) {
        *item = EMPTY_NO;
        res = TRUE;
    }

    return res;
}

static int mAGrw_RecordCheckItem(u8* record, mActor_name_t check_item, mActor_name_t* valid_items, int count,
                                 int block_x) {
    int res = FALSE;
    int i;

    for (i = 0; i < count; i++) {
        if (check_item == *valid_items) {
            *record |= (1 << block_x);
            res = TRUE;

            break;
        }

        valid_items++;
    }

    return res;
}

static int mAGrw_RecordHoneycombTree(mActor_name_t* item, mAGrw_GrowInfo_c* grow_info) {
    return mAGrw_RecordCheckItem(&grow_info->honeycomb_tree_record, *item, l_magrw_bee_table, 3, grow_info->block_x);
}

static int mAGrw_RecordFtrTree(mActor_name_t* item, mAGrw_GrowInfo_c* grow_info) {
    return mAGrw_RecordCheckItem(&grow_info->ftr_tree_record, *item, l_magrw_ftr_table, 3, grow_info->block_x);
}

static int mAGrw_RecordDepositFossil(mActor_name_t* item, mAGrw_GrowInfo_c* grow_info) {
    int res = FALSE;

    if (grow_info->deposited_item == TRUE) {
        res = mMsm_RecordDepositFossil(&grow_info->fossil_record, *item, grow_info->block_x);

        if (res == TRUE) {
            grow_info->fossil_num++;
        }
    }

    return res;
}

static int mAGrw_CheckChangeTree(mActor_name_t item) {
    int res = FALSE;
    int i;

    for (i = 0; i < 3; i++) {
        if (item == l_magrw_change_tree[i]) {
            res = TRUE;

            break;
        }
    }

    return res;
}

static int mAGrw_CheckMoneyTree(mActor_name_t item) {
    int res = FALSE;
    int i;

    for (i = 0; i < 3; i++) {
        if (item == l_magrw_smn_table[i]) {
            res = TRUE;

            break;
        }
    }

    return res;
}

static int mAGrw_CountMoneyTree(mActor_name_t* item, mAGrw_GrowInfo_c* grow_info) {
    int res = FALSE;

    if (mAGrw_CheckMoneyTree(*item) == TRUE) {
        grow_info->money_tree_num++;
        res = TRUE;
    }

    return res;
}

static int mAGrw_CheckMoneyStone(mActor_name_t* item, mAGrw_GrowInfo_c* grow_info) {
    int res = FALSE;

    if ((*item >= MONEY_ROCK_A && *item <= MONEY_ROCK_E) || *item == MONEY_FLOWER_SEED) {
        grow_info->money_stone_spawned = TRUE;
        res = TRUE;
    }

    return res;
}

static int mAGrw_GetChangeAbleTreeNum2(mActor_name_t* items) {
    int num = 0;

    if (items != NULL) {
        int i;

        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (mAGrw_CheckChangeTree(*items) == TRUE) {
                num++;
            }

            items++;
        }
    }

    return num;
}

static void mAGrw_ChangeItemBlock2(mActor_name_t* block_items, u8 changeable_num, mActor_name_t* target_table,
                                   mActor_name_t* source_table, int table_num) {
    int changed = FALSE;
    int selected = RANDOM(changeable_num);
    int j;
    int i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        for (j = 0; j < table_num; j++) {
            if (*block_items == source_table[j]) {
                if (selected <= 0) {
                    *block_items = target_table[j];
                    changed = TRUE;

                    break;
                } else {
                    selected--;
                }
            }
        }

        if (changed) {
            break;
        }

        block_items++;
    }
}

static void mAGrw_SetTreeBlockLine(int block_x, mActor_name_t* target_table) {
    u8 changeable_num[FG_BLOCK_Z_NUM];
    int possible_lines = 0;
    int i;

    for (i = 0; i < FG_BLOCK_Z_NUM; i++) {
        changeable_num[i] = mAGrw_GetChangeAbleTreeNum2(Save_Get(fg[i][block_x]).items[0]);

        if (changeable_num[i] != 0) {
            possible_lines++;
        }
    }

    if (possible_lines > 0) {
        int selected = RANDOM(possible_lines);

        for (i = 0; i < FG_BLOCK_Z_NUM; i++) {
            if (changeable_num[i] != 0) {
                if (selected == 0) {
                    mAGrw_ChangeItemBlock2(Save_Get(fg[i][block_x]).items[0], changeable_num[i], target_table,
                                           l_magrw_change_tree, 3);
                    break;
                } else {
                    selected--;
                }
            }
        }
    }
}

static void mAGrw_SetHoneycombTree(u8 honeycomb_record) {
    u8 block_num = mMsm_GetDepositBlockNum(honeycomb_record);

    if (block_num < FG_BLOCK_X_NUM) {
        int i;

        for (i = 0; i < FG_BLOCK_X_NUM; i++) {
            if (((honeycomb_record >> (i + 1)) & 1) == 0) {
                mAGrw_SetTreeBlockLine(i, l_magrw_bee_table);
            }
        }
    }
}

static void mAGrw_SetFtrTree(u8 ftr_record) {
    u8 block_num;
    int selected;
    int vacant_lines;
    int n;
    int i;
    int j;

    block_num = mMsm_GetDepositBlockNum(ftr_record);

    if (block_num < mAGrw_FTR_TREE_NUM) {
        vacant_lines = FG_BLOCK_X_NUM - block_num;
        n = mAGrw_FTR_TREE_NUM - block_num;

        for (i = 0; i < n; i++) {
            selected = RANDOM(vacant_lines);

            for (j = 0; j < FG_BLOCK_X_NUM; j++) {
                if (((ftr_record >> (j + 1)) & 1) == 0) {
                    if (selected == 0) {
                        mAGrw_SetTreeBlockLine(j, l_magrw_ftr_table);
                        vacant_lines--;
                        ftr_record |= (1 << (j + 1));

                        break;
                    } else {
                        selected--;
                    }
                }
            }
        }
    }
}

static void mAGrw_SetMoneyTreeRandom(mFM_fg_c* fg_block, u8* changeable_num, u8* candidates) {
    int selected = RANDOM(*candidates);
    int i;

    for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
        if (changeable_num[0] != 0) {
            if (selected <= 0) {
                mAGrw_ChangeItemBlock2(fg_block->items[0], changeable_num[0], l_magrw_smn_table, l_magrw_change_tree,
                                       3);
                changeable_num[0]--;

                if (changeable_num[0] == 0) {
                    candidates[0]--;
                }

                break;
            } else {
                selected--;
            }
        }

        fg_block++;
        changeable_num++;
    }
}

static void mAGrw_SetMoneyTree(int moneytree_num) {
    mFM_fg_c* fg_block = Save_Get(fg[0]);
    u8* candidate_num = l_candidate_num;
    u8 candidates = 0;
    int total_candidate_num = 0;
    int spawn_num;
    int i;

    if (moneytree_num < mAGrw_MONEY_TREE_NUM) {
        spawn_num = mAGrw_MONEY_TREE_NUM - moneytree_num;
        bzero(candidate_num, FG_BLOCK_TOTAL_NUM * sizeof(u8));

        for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
            candidate_num[0] = mAGrw_GetChangeAbleTreeNum2(fg_block->items[0]);

            if (candidate_num[0] != 0) {
                total_candidate_num += candidate_num[0];
                candidates++;
            }

            candidate_num++;
            fg_block++;
        }

        if (total_candidate_num > 0) {

            if (spawn_num > total_candidate_num) {
                spawn_num = total_candidate_num;
            }

            for (spawn_num; spawn_num != 0; spawn_num--) {
                mAGrw_SetMoneyTreeRandom(Save_Get(fg[0]), l_candidate_num, &candidates);
            }
        }
    }
}

static int mAGrw_CountNormalStone(mActor_name_t* block_items) {
    int normal_stone = 0;
    int i;

    if (block_items != NULL) {
        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (*block_items >= ROCK_A && *block_items <= ROCK_E) {
                normal_stone++;
            }

            block_items++;
        }
    }

    return normal_stone;
}

static void mAGrw_SetMoneyStoneBlock(mAGrw_SSPosInfo_c* pos_info, mActor_name_t* items, u8 candidate_num) {
    int selected = RANDOM(candidate_num);
    int i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (*items >= ROCK_A && *items <= ROCK_E) {
            if (selected <= 0) {
                pos_info->ut_x = i % UT_X_NUM;
                pos_info->ut_z = i / UT_X_NUM;

                break;
            } else {
                selected--;
            }
        }

        items++;
    }
}

static void mAGrw_SetMoneyStone_com(mAGrw_SSPosInfo_c* pos_info, mActor_name_t* items) {
    u8* candidate_num;
    int selected_block;
    u8 candidate_blocks = 0;
    int total_spots = 0;
    int i;

    candidate_num = l_candidate_num;
    bzero(candidate_num, FG_BLOCK_TOTAL_NUM * sizeof(u8));

    for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
        *candidate_num = mAGrw_CountNormalStone(items);

        if (*candidate_num != 0) {
            total_spots += candidate_num[0];
            candidate_blocks++;
        }

        candidate_num++;
        items += UT_TOTAL_NUM;
    }

    items -= UT_TOTAL_NUM * FG_BLOCK_TOTAL_NUM;

    if (total_spots > 0) {
        candidate_num = l_candidate_num;
        selected_block = RANDOM(candidate_blocks);

        for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
            if (candidate_num[0] != 0) {
                if (selected_block <= 0) {
                    pos_info->block_x = 1 + (i % FG_BLOCK_X_NUM);
                    pos_info->block_z = 1 + (i / FG_BLOCK_X_NUM);
                    mAGrw_SetMoneyStoneBlock(pos_info, items, candidate_num[0]);

                    break;
                } else {
                    selected_block--;
                }
            }

            candidate_num++;
            items += UT_TOTAL_NUM;
        }
    }
}

static void mAGrw_SetMoneyStone(mAGrw_AllGrow_c* all_grow, mActor_name_t* items) {
    mAGrw_SSPosInfo_c* pos_info = all_grow->stone_pos;
    int i;

    for (i = 0; i < TOTAL_PLAYER_NUM; i++) {
        if (mAGrw_CheckFreeSSPosInfo_com(pos_info) == TRUE ||
            (Common_Get(player_no) == i && mAGrw_CheckMoneyStonePos(pos_info) == FALSE)) {
            mAGrw_SetMoneyStone_com(pos_info, items);
        }

        pos_info++;
    }
}

static void mAGrw_SetTree0Info(u16* tree0_info, mActor_name_t* items) {
    int z;
    int x;

    bzero(tree0_info, UT_Z_NUM * sizeof(u16));

    for (z = 0; z < UT_Z_NUM; z++) {
        for (x = 0; x < UT_X_NUM; x++) {
            if (*items == TREE_SAPLING || *items == TREE_APPLE_SAPLING || *items == TREE_ORANGE_SAPLING ||
                *items == TREE_PEACH_SAPLING || *items == TREE_PEAR_SAPLING || *items == TREE_CHERRY_SAPLING ||
                *items == TREE_1000BELLS_SAPLING || *items == TREE_10000BELLS_SAPLING ||
                *items == TREE_30000BELLS_SAPLING || *items == TREE_100BELLS_SAPLING || *items == TREE_PALM_SAPLING ||
                *items == CEDAR_TREE_SAPLING || *items == GOLD_TREE_SAPLING) {
                (*tree0_info) |= (1 << x);
            }

            items++;
        }

        tree0_info++;
    }
}

static void mAGrw_ResetTree0Info(u16* tree0_info, u8* normal_trees, u8* other_trees, mActor_name_t* items) {
    int z;
    int x;

    for (z = 0; z < UT_Z_NUM; z++) {
        for (x = 0; x < UT_X_NUM; x++) {
            if (((*tree0_info >> x) & 1) == 1) {
                if (*items == DEAD_SAPLING || *items == DEAD_PALM_SAPLING || *items == DEAD_CEDAR_SAPLING ||
                    *items == DEAD_GOLD_SAPLING) {
                    (*tree0_info) &= ~(1 << x);
                } else if ((*items >= TREE_SAPLING && *items <= TREE) ||
                           (*items >= CEDAR_TREE_SAPLING && *items <= CEDAR_TREE)) {
                    normal_trees[0]++;
                } else if (*items != EMPTY_NO) {
                    other_trees[0]++;
                }
            }

            items++;
        }

        tree0_info++;
    }
}

static void mAGrw_KillTree0(mActor_name_t* items, u16* tree0_info, int* normal_trees, int* other_trees) {
    int selected_tree;
    int is_normal_tree;
    int kill_normal_tree = TRUE;
    int* trees;
    int z;
    int x;

    if (*normal_trees > 0) {
        trees = normal_trees; /* prefer to kill regular trees or cedar trees */
    } else {
        kill_normal_tree = FALSE;
        trees = other_trees;
    }

    selected_tree = RANDOM(*trees);

    for (z = 0; z < UT_Z_NUM; z++) {
        for (x = 0; x < UT_X_NUM; x++) {
            if (((*tree0_info >> x) & 1) == 1) {
                is_normal_tree = (*items >= TREE_SAPLING && *items <= TREE) ||
                                 (*items >= CEDAR_TREE_SAPLING && *items <= CEDAR_TREE);

                if (kill_normal_tree == is_normal_tree) {
                    if (selected_tree <= 0) {
                        tree0_info[0] &= ~(1 << x); /* remove the tree from the bitfield */
                        mAGrw_KillTree(items);      /* remove the tree item */
                        trees[0]--;                 /* remove the tree from the 'other tree' count */
                        z = UT_Z_NUM;               /* break out of outer loop */

                        break;
                    } else {
                        selected_tree--;
                    }
                }
            }

            items++;
        }

        tree0_info++;
    }
}

static void mAGrw_ThinTree(mActor_name_t* items, u16* tree0_info, int normal_trees, int other_trees, int max_trees) {
    u8 trees = 0;
    u8 trees_in_acre;
    int t_normal_trees;
    int t_other_trees;
    int i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if ((*items >= TREE_SAPLING && *items <= TREE_30000BELLS) ||
            (*items >= TREE_100BELLS_SAPLING && *items <= TREE_PALM_FRUIT) ||
            (*items >= CEDAR_TREE_SAPLING && *items <= CEDAR_TREE) ||
            (*items >= GOLD_TREE_SAPLING && *items <= GOLD_TREE) ||
            (*items == TREE_BEES || *items == TREE_FTR || *items == TREE_LIGHTS || *items == TREE_PRESENT ||
             *items == TREE_BELLS) ||
            (*items == CEDAR_TREE_BELLS || *items == CEDAR_TREE_FTR || *items == CEDAR_TREE_BEES ||
             *items == CEDAR_TREE_LIGHTS) ||
            (*items == GOLD_TREE_BELLS || *items == GOLD_TREE_FTR || *items == GOLD_TREE_BEES)) {
            trees++;
        }

        items++;
    }

    i = trees - max_trees;
    if (i > 0) {
        trees_in_acre = normal_trees + other_trees;
        for (i; trees_in_acre != 0 && i != 0; i--, trees_in_acre--) {
            mAGrw_KillTree0(items - UT_TOTAL_NUM, tree0_info, &normal_trees, &other_trees);
        }
    }
}

static int mAGrw_CheckCarpTime(lbRTC_time_c* time) {
    int carp_type = mAGrw_CARP_UNCHANGED;

    if (Common_Get(time.rtc_time.month) == lbRTC_MAY && Common_Get(time.rtc_time.day) <= 5) {
        carp_type = mAGrw_CARP_PLACE;
    } else if (time->month == lbRTC_MAY && time->day <= 5) {
        carp_type = mAGrw_CARP_REMOVE;
    }

    return carp_type;
}

static void mAGrw_SetCarpBlockInfo(mAGrw_CarpBlockInfo_c* block_info, mActor_name_t* items) {
    int i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (*items >= SIGN00 && *items <= SIGN20) {
            block_info->signboard_in_block = TRUE;
            block_info->signboard_count++;
        } else if (*items == KOINOBORI_WINDSOCK) {
            block_info->carp_already_exists = TRUE;
        } else if (*items >= NPC_HOUSE_START && *items < NPC_HOUSE_END) {
            block_info->villager_house_in_block = TRUE;
        }

        items++;
    }
}

static void mAGrw_SetCarpInfo(mAGrw_CarpInfo_c* carp_info, mFM_fg_c* fg_block) {
    mAGrw_CarpBlockInfo_c* block_info = carp_info->block_flags;
    int i;

    for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
        mAGrw_SetCarpBlockInfo(block_info, fg_block->items[0]);

        if (block_info->carp_already_exists == TRUE) {
            carp_info->carp_blocks++;
            block_info->signboard_in_block = FALSE;
        } else if (block_info->signboard_in_block == TRUE) {
            carp_info->signboard_blocks++;
        }

        if (block_info->villager_house_in_block == TRUE) {
            carp_info->villager_house_blocks++;
        }

        block_info++;
        fg_block++;
    }
}

static void mAGrw_SetCarpBlock(mActor_name_t* items, int signboard_count) {
    if (signboard_count > 0 && items != NULL) {
        int selected = RANDOM(signboard_count);
        int i;

        for (i = 0; i < UT_TOTAL_NUM; i++) {
            if (*items >= SIGN00 && *items <= SIGN20) {
                if (selected <= 0) {
                    *items = KOINOBORI_WINDSOCK;

                    break;
                } else {
                    selected--;
                }
            }

            items++;
        }
    }
}

static void mAGrw_ClearCarpBlock(mActor_name_t* items, int block_x, int block_z) {
    int i;

    for (i = 0; i < UT_TOTAL_NUM; i++) {
        if (*items == KOINOBORI_WINDSOCK) {
            *items = mFM_GetReseveName(block_x, block_z);
        }

        items++;
    }
}

static void mAGrw_KeepReserve(mAGrw_CarpInfo_c* carp_info, mFM_fg_c* fg_blocks) {
    u8 valid_signboard_map[FG_BLOCK_Z_NUM];
    mAGrw_CarpBlockInfo_c* block_info;
    mFM_fg_c* fg_block_p = fg_blocks;
    int selected;
    int blocks;
    int bx;
    int bz;
    u8* map_p;
    u8 can_have_villager_house;
    int j;
    int i;
    int valid;
    int temp;

    if (carp_info->signboard_blocks < 3) {
        for (blocks = 3 - carp_info->signboard_blocks; blocks != 0 && carp_info->carp_blocks != 0; blocks--) {
            block_info = carp_info->block_flags;
            fg_blocks = fg_block_p;
            selected = RANDOM(carp_info->carp_blocks);

            for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
                for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
                    if (block_info->carp_already_exists == TRUE) {
                        if (selected <= 0) {
                            mAGrw_ClearCarpBlock(fg_blocks->items[0], bx + 1, bz + 1);
                            block_info->carp_already_exists = FALSE;
                            carp_info->carp_blocks--;

                            bz = FG_BLOCK_Z_NUM;
                            break;
                        } else {
                            selected--;
                        }
                    }

                    fg_blocks++;
                    block_info++;
                }
            }
        }
    } else if (carp_info->carp_blocks < 5) {
        can_have_villager_house = FALSE;
        i = 3;
        while (carp_info->signboard_blocks != 0 && i != 0) {
            for (j = 1; j <= 3; j++) {
                map_p = valid_signboard_map;
                valid = 0;

                bzero(valid_signboard_map, FG_BLOCK_Z_NUM * sizeof(u8));
                block_info = carp_info->block_flags;

                for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
                    for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
                        if (block_info->signboard_in_block == TRUE &&
                            block_info->villager_house_in_block == can_have_villager_house &&
                            block_info->signboard_count == j) {
                            valid++;
                            map_p[0] |= (1 << bx);
                        }

                        block_info++;
                    }

                    map_p++;
                }

                if (valid > i) {
                    temp = i;
                } else {
                    temp = valid;
                }

                /* Place koinobori windsocks */
                while (temp != 0 && valid != 0) {
                    selected = RANDOM(valid);
                    map_p = valid_signboard_map;
                    block_info = carp_info->block_flags;

                    for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
                        for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
                            if (((map_p[0] >> bx) & 1) == 1) {
                                if (selected <= 0) {
                                    block_info->signboard_in_block = FALSE;
                                    bz = 6;
                                    valid--;
                                    i--;
                                    carp_info->signboard_blocks--;
                                    map_p[0] &= ~(1 << bx); /* clear signboard in valid map */

                                    break;
                                } else {
                                    selected--;
                                }
                            }

                            block_info++;
                        }

                        map_p++;
                    }

                    temp--;
                }
            }

            can_have_villager_house ^= TRUE;
        }
    }
}

static void mAGrw_SetCarpOnHomeBlock(mAGrw_CarpInfo_c* carp_info, mFM_fg_c* fg_block, int count) {
    u8 block_house_info[2];
    mAGrw_CarpBlockInfo_c* block_info;
    mFM_fg_c* fg_block_p = fg_block;
    u8 spawn_on_home_block = TRUE;
    int selected;
    int i;

    bzero(block_house_info, 2 * sizeof(u8));

    block_info = carp_info->block_flags;
    for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
        if (block_info->signboard_in_block == TRUE) {
            if (block_info->villager_house_in_block == TRUE) {
                block_house_info[1]++;
            } else {
                block_house_info[0]++;
            }

        }
        
        fg_block++;
        block_info++;
    }

    while (count != 0 && carp_info->signboard_blocks != 0) {
        while (block_house_info[spawn_on_home_block] != 0 && count != 0) {
            block_info = carp_info->block_flags;
            fg_block = fg_block_p;
            selected = RANDOM(block_house_info[spawn_on_home_block]);

            for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
                if (block_info->signboard_in_block == TRUE &&
                    block_info->villager_house_in_block == spawn_on_home_block) {
                    if (selected <= 0) {
                        mAGrw_SetCarpBlock(fg_block->items[0], block_info->signboard_count);
                        count--;

                        block_info->signboard_in_block = FALSE;
                        carp_info->signboard_blocks--;

                        block_info->carp_already_exists = TRUE;
                        carp_info->carp_blocks++;

                        block_house_info[spawn_on_home_block]--;

                        break;
                    } else {
                        selected--;
                    }
                }

                fg_block++;
                block_info++;
            }
        }

        if (block_house_info[0] == 0 && block_house_info[1] == 0) {
            break;
        }

        spawn_on_home_block ^= TRUE;
    }
}

static void mAGrw_SetEnoughCarp(mAGrw_CarpInfo_c* carp_info, mFM_fg_c* fg_block) {
    mAGrw_KeepReserve(carp_info, fg_block);

    if (carp_info->signboard_blocks > 3 && carp_info->carp_blocks < 5) {
        int count = 5 - carp_info->carp_blocks;
        int signboard_blocks = carp_info->signboard_blocks - 3;

        if (count > signboard_blocks) {
            count = signboard_blocks;
        }

        if (count > 0) {
            mAGrw_SetCarpOnHomeBlock(carp_info, fg_block, count);
        }
    }
}

static void mAGrw_ClearAllCarp(mFM_fg_c* fg_block) {
    int bz;
    int bx;

    for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
        for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
            mAGrw_ClearCarpBlock(fg_block->items[0], bx + 1, bz + 1);
            fg_block++;
        }
    }
}

static void mAGrw_SetCarp(lbRTC_time_c* time) {
    mAGrw_CarpInfo_c carp_info;
    int carp_state = mAGrw_CheckCarpTime(time);
    mFM_fg_c* fg_block = Save_Get(fg[0]);

    if (carp_state == mAGrw_CARP_PLACE || carp_state == mAGrw_CARP_REMOVE) {
        if (carp_state == mAGrw_CARP_PLACE) {
            bzero(&carp_info, sizeof(mAGrw_CarpInfo_c));
            mAGrw_SetCarpInfo(&carp_info, fg_block);
            mAGrw_SetEnoughCarp(&carp_info, fg_block);
        } else {
            mAGrw_ClearAllCarp(fg_block);
        }
    }
}

typedef int (*mAGrw_GROW_PROC)(mActor_name_t*, mAGrw_GrowInfo_c*);

static void mAGrw_GrowBlockFgItem(mActor_name_t* items, mCoBG_Collision_u* col, u16* deposit,
                                  mAGrw_GrowInfo_c* grow_info, int proc_type) {
    static mAGrw_GROW_PROC first_grow_proc[] = { &mAGrw_GrowPlant_First,     &mAGrw_ClearShineGround,
                                                 &mAGrw_RecordHoneycombTree, &mAGrw_RecordFtrTree,
                                                 &mAGrw_RecordDepositFossil, &mAGrw_CountMoneyTree,
                                                 &mAGrw_CheckMoneyStone,     &mAGrw_MeltSnowman };

    static mAGrw_GROW_PROC grow_proc[] = { &mAGrw_ClearSpoiledKabu, &mAGrw_SpoilKabu,
                                           &mAGrw_GrowPlant,        &mAGrw_MeltSnowman,
                                           &mAGrw_ClearShineGround, &mAGrw_RecordHoneycombTree,
                                           &mAGrw_RecordFtrTree,    &mAGrw_RecordDepositFossil,
                                           &mAGrw_CountMoneyTree,   &mAGrw_CheckMoneyStone };

    static mAGrw_GROW_PROC first_island_proc[] = { &mAGrw_GrowPlant_First };

    static mAGrw_GROW_PROC grow_island_proc[] = { &mAGrw_ClearSpoiledKabu, &mAGrw_SpoilKabu, &mAGrw_GrowPlant };

    static mAGrw_GROW_PROC* grow_proc_table[mAGrw_GROW_NUM] = {
        first_grow_proc, grow_proc, first_grow_proc, first_island_proc, grow_island_proc, first_island_proc
    };

    static int proc_max_table[mAGrw_GROW_NUM] = { 8, 10, 8, 1, 3, 1 };

    xyz_t t_wpos = { 0.0f, 0.0f, 0.0f };
    xyz_t wpos = { 0.0f, 0.0f, 0.0f };

    mAGrw_GROW_PROC* proc_table;
    int proc_table_num;
    int ut_z;
    int ut_x;
    int i;

    mFI_BkNum2WposXZ(&wpos.x, &wpos.z, grow_info->block_x, grow_info->block_z);
    wpos.x += mFI_UT_WORLDSIZE_X_F / 2.0f;
    wpos.z += mFI_UT_WORLDSIZE_Z_F / 2.0f;

    t_wpos = wpos;
    proc_table = grow_proc_table[proc_type];
    proc_table_num = proc_max_table[proc_type];

    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        t_wpos.x = wpos.x;

        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
            grow_info->deposited_item = mFI_GetLineDeposit(deposit, ut_x);
            grow_info->ut_x = ut_x;
            grow_info->ut_z = ut_z;
            grow_info->check_plant = mCoBG_Attribute2CheckPlant(col->data.unit_attribute, &t_wpos);
            grow_info->block_height = mCoBG_GetLayer(&t_wpos);

            for (i = 0; i < proc_table_num; i++) {
                if ((*proc_table[i])(items, grow_info) == TRUE) {
                    break;
                }
            }

            items++;
            col++;
            t_wpos.x += mFI_UT_WORLDSIZE_X_F;
        }

        deposit++;
        t_wpos.z += mFI_UT_WORLDSIZE_Z_F;
    }
}

static void mAGrw_GrowFieldFgItem(lbRTC_time_c* now_time, lbRTC_time_c* grow_time, int flower_time, int spoil_kabu,
                                  u8* fossil_record, int* fossil_num, int proc_type) {
    static u16 tree0_info[UT_Z_NUM];

    mAGrw_GrowInfo_c grow_info;
    mCoBG_Collision_u* col;
    mFM_fg_c* fg_block;
    u8 normal_trees;
    u8 other_trees;
    int bz;
    int bx;

    fg_block = Save_Get(fg[0]);
    mAGrw_ClearGrowInfo(&grow_info);
    grow_info.spoil_kabu = spoil_kabu;

    if (proc_type == mAGrw_GROW) {
        grow_info.past_days = mAGrw_get_pastDays(now_time, grow_time);
    } else if (proc_type == mAGrw_GROW_FIRST_FORCE) {
        if (now_time->day != Save_Get(all_grow_renew_time).day) {
            grow_info.past_days = -1;
        } else {
            grow_info.past_days = 0;
        }
    }

    grow_info.flower_time = flower_time;

    for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
        for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
            normal_trees = 0;
            other_trees = 0;

            mAGrw_SetTree0Info(tree0_info, fg_block->items[0]);
            grow_info.block_x = bx + 1;
            grow_info.block_z = bz + 1;

            if (bz + 1 == FG_BLOCK_Z_NUM) {
                grow_info.ocean_row = TRUE;
            } else {
                grow_info.ocean_row = FALSE;
            }

            col = mFI_GetBkNum2ColTop(grow_info.block_x, grow_info.block_z);

            if (col != NULL) {
                if (proc_type == mAGrw_GROW) {
                    mAGrw_SetAroundBlockInfo(&grow_info, bx, bz);
                }

                mAGrw_GrowBlockFgItem(fg_block->items[0], col, Save_Get(deposit[bx + bz * FG_BLOCK_X_NUM]), &grow_info,
                                      proc_type);
            }

            mAGrw_ResetTree0Info(tree0_info, &normal_trees, &other_trees, fg_block->items[0]);
            mAGrw_ThinTree(fg_block->items[0], tree0_info, normal_trees, other_trees, mAGrw_MAX_TREES_PER_BLOCK);

            fg_block++;
        }
    }

    *fossil_record = grow_info.fossil_record;
    *fossil_num = grow_info.fossil_num;

    mAGrw_SetHoneycombTree(grow_info.honeycomb_tree_record);
    mAGrw_SetFtrTree(grow_info.ftr_tree_record);
    mAGrw_SetMoneyTree(grow_info.money_tree_num);
}

static int mAGrw_CheckTree000(mActor_name_t item) {
    return item == TREE_SAPLING || item == TREE_APPLE_SAPLING || item == TREE_ORANGE_SAPLING ||
           item == TREE_PEACH_SAPLING || item == TREE_PEAR_SAPLING || item == TREE_CHERRY_SAPLING ||
           item == TREE_1000BELLS_SAPLING || item == TREE_10000BELLS_SAPLING || item == TREE_30000BELLS_SAPLING ||
           item == TREE_100BELLS_SAPLING || item == TREE_PALM_SAPLING || item == CEDAR_TREE_SAPLING ||
           item == GOLD_TREE_SAPLING;
}

static int mAGrw_CheckTree001(mActor_name_t item) {
    return item == TREE_S0 || item == TREE_APPLE_S0 || item == TREE_ORANGE_S0 || item == TREE_PEACH_S0 ||
           item == TREE_PEAR_S0 || item == TREE_CHERRY_S0 || item == TREE_1000BELLS_S0 || item == TREE_10000BELLS_S0 ||
           item == TREE_30000BELLS_S0 || item == TREE_1000BELLS_S0 || item == TREE_10000BELLS_S0 ||
           item == TREE_30000BELLS_S0 || item == TREE_100BELLS_S0 || item == TREE_PALM_S0 || item == CEDAR_TREE_S0 ||
           item == GOLD_TREE_S0;
}

static int mAGrw_CheckTree002(mActor_name_t item) {
    return item == TREE_S1 || item == TREE_APPLE_S1 || item == TREE_ORANGE_S1 || item == TREE_PEACH_S1 ||
           item == TREE_PEAR_S1 || item == TREE_CHERRY_S1 || item == TREE_1000BELLS_S1 || item == TREE_10000BELLS_S1 ||
           item == TREE_30000BELLS_S1 || item == TREE_1000BELLS_S1 || item == TREE_10000BELLS_S1 ||
           item == TREE_30000BELLS_S1 || item == TREE_100BELLS_S1 || item == TREE_PALM_S1 || item == CEDAR_TREE_S1 ||
           item == GOLD_TREE_S1;
}

static int mAGrw_CheckTree003(mActor_name_t item) {
    return item == TREE_S2 || item == TREE_APPLE_S2 || item == TREE_ORANGE_S2 || item == TREE_PEACH_S2 ||
           item == TREE_PEAR_S2 || item == TREE_CHERRY_S2 || item == TREE_1000BELLS_S2 || item == TREE_10000BELLS_S2 ||
           item == TREE_30000BELLS_S2 || item == TREE_1000BELLS_S2 || item == TREE_10000BELLS_S2 ||
           item == TREE_30000BELLS_S2 || item == TREE_100BELLS_S2 || item == TREE_PALM_S2 || item == CEDAR_TREE_S2 ||
           item == GOLD_TREE_S2;
}

static int mAGrw_CheckTree004(mActor_name_t item) {
    return item == TREE || item == TREE_APPLE_FRUIT || item == TREE_ORANGE_FRUIT || item == TREE_PEACH_FRUIT ||
           item == TREE_PEAR_FRUIT || item == TREE_CHERRY_FRUIT || item == TREE_1000BELLS || item == TREE_10000BELLS ||
           item == TREE_30000BELLS || item == TREE_100BELLS || item == TREE_PALM_FRUIT || item == CEDAR_TREE ||
           item == GOLD_TREE || item == GOLD_TREE_SHOVEL || item == TREE_APPLE_NOFRUIT_0 ||
           item == TREE_ORANGE_NOFRUIT_0 || item == TREE_PEACH_NOFRUIT_0 || item == TREE_PEAR_NOFRUIT_0 ||
           item == TREE_CHERRY_NOFRUIT_0 || item == TREE_PALM_NOFRUIT_0 || item == TREE_APPLE_NOFRUIT_1 ||
           item == TREE_ORANGE_NOFRUIT_1 || item == TREE_PEACH_NOFRUIT_1 || item == TREE_PEAR_NOFRUIT_1 ||
           item == TREE_CHERRY_NOFRUIT_1 || item == TREE_PALM_NOFRUIT_1 || item == TREE_APPLE_NOFRUIT_2 ||
           item == TREE_ORANGE_NOFRUIT_2 || item == TREE_PEACH_NOFRUIT_2 || item == TREE_PEAR_NOFRUIT_2 ||
           item == TREE_CHERRY_NOFRUIT_2 || item == TREE_PALM_NOFRUIT_2 || item == TREE_BEES || item == TREE_FTR ||
           item == TREE_LIGHTS || item == TREE_PRESENT || item == TREE_BELLS || item == CEDAR_TREE_BELLS ||
           item == CEDAR_TREE_FTR || item == CEDAR_TREE_BEES || item == CEDAR_TREE_LIGHTS || item == GOLD_TREE_BELLS ||
           item == GOLD_TREE_FTR || item == GOLD_TREE_BEES;
}

typedef int (*mAGrw_CHECK_FG_PROC)(mActor_name_t);

static int mAGrw_CheckTree000(mActor_name_t);
static int mAGrw_CheckTree001(mActor_name_t);
static int mAGrw_CheckTree002(mActor_name_t);
static int mAGrw_CheckTree003(mActor_name_t);
static int mAGrw_CheckTree004(mActor_name_t);

typedef int (*mAGrw_CHECK_FG_PROC)(mActor_name_t);

static void mAGrw_LimitTreeLineIsland(mFM_fg_c* island_block) {
    static mAGrw_CHECK_FG_PROC check_fg[mAGrw_TREE_STAGE_NUM] = { &mAGrw_CheckTree000, &mAGrw_CheckTree001,
                                                                  &mAGrw_CheckTree002, &mAGrw_CheckTree003,
                                                                  &mAGrw_CheckTree004, };
// TODO: Ordering needs to be fixed, this seems fake
#if VERSION >= VER_GAFU01_00
    int tree_size_count_tbl[mAGrw_TREE_STAGE_NUM];
    mFM_fg_c* island_block_p;
    u8 ignored_record;
    int max_trees;
    int selected;
    mActor_name_t* items;
    int trees;
    int ut_x;
    int ut_z;
    int tree_size;
    int block;
#else
    int tree_size_count_tbl[mAGrw_TREE_STAGE_NUM];
    mFM_fg_c* island_block_p;
    u8 ignored_record;
    int max_trees;
    int selected;
    int ut_x;
    int ut_z;
    mActor_name_t* items;
    int trees;
    int tree_size;
    int block;
#endif

    island_block_p = island_block;

    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        bzero(tree_size_count_tbl, sizeof(int) * mAGrw_TREE_STAGE_NUM);
        island_block = island_block_p;
        trees = 0;
        ignored_record = 0;

        /* Count all trees and log size of each tree */
        for (block = 0; block < mISL_FG_BLOCK_X_NUM; block++) {
            items = island_block->items[ut_z];
            for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                for (tree_size = 0; tree_size < mAGrw_TREE_STAGE_NUM; tree_size++) {
                    if ((*check_fg[tree_size])(*items) == TRUE) {
                        tree_size_count_tbl[tree_size]++;
                        trees++;

                        break;
                    }
                }

                items++;
            }

            island_block++;
        }

        /* Check and do trimming */
        if (trees > mAGrw_ISL_TREE_MAX_LINE) {
            max_trees = trees - mAGrw_ISL_TREE_MAX_LINE;

            for (tree_size = 0; tree_size < mAGrw_TREE_STAGE_NUM; tree_size++) {
                island_block = island_block_p;
                if (max_trees < tree_size_count_tbl[tree_size]) {
                    break;
                }

                for (block = 0; block < mISL_FG_BLOCK_X_NUM; block++) {
                    items = island_block->items[ut_z];
                    for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                        if ((*check_fg[tree_size])(*items) == TRUE) {
                            mAGrw_KillTree(items);
                        }

                        items++;
                    }

                    island_block++;
                }

                ignored_record |= (1 << tree_size);
                max_trees -= tree_size_count_tbl[tree_size];
                tree_size_count_tbl[tree_size] = 0;

                if (max_trees == 0) {
                    break;
                }
            }

            tree_size = 0;

            while (max_trees > 0) {
                if (((ignored_record >> tree_size) & 1) == 0 && tree_size_count_tbl[tree_size] > 0) {
                    island_block = island_block_p;
                    selected = RANDOM(tree_size_count_tbl[tree_size]);

                    for (block = 0; block < mISL_FG_BLOCK_X_NUM; block++) {
                        items = island_block->items[ut_z];
                        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                            if ((*check_fg[tree_size])(*items) == TRUE) {
                                if (selected == 0) {
                                    mAGrw_KillTree(items);
                                    block = mISL_FG_BLOCK_X_NUM;

                                    break;
                                } else {
                                    selected--;
                                }
                            }

                            items++;
                        }

                        island_block++;
                    }

                    tree_size_count_tbl[tree_size]--;
                    max_trees--;
                } else {
                    tree_size++;
                }

                if (tree_size >= mAGrw_TREE_STAGE_NUM) {
                    break;
                }
            }
        }
    }
}

static void mAGr_GrowIslandFgItem(lbRTC_time_c* now_time, lbRTC_time_c* grow_time, int flower_time, int spoil_kabu,
                                  int proc_type) {
    static u16 tree0_info[UT_Z_NUM];

    mAGrw_GrowInfo_c grow_info;
    int island_block_x_nums[mISL_FG_BLOCK_X_NUM];
    mFM_fg_c* island_block = Save_Get(island).fgblock[0];
    mCoBG_Collision_u* col;
    int bx;

    mAGrw_ClearGrowInfo(&grow_info);
    grow_info.spoil_kabu = spoil_kabu;

    if (proc_type == mAGrw_GROW) {
        grow_info.past_days = mAGrw_get_pastDays(now_time, grow_time);
    } else if (proc_type == mAGrw_GROW_FIRST_FORCE) {
        if (now_time->day != Save_Get(all_grow_renew_time).day) {
            grow_info.past_days = -1;
        } else {
            grow_info.past_days = 0;
        }
    }

    grow_info.flower_time = flower_time;
    mFI_GetIslandBlockNumX(island_block_x_nums);
    grow_info.ocean_row = TRUE;

    for (bx = 0; bx < mISL_FG_BLOCK_X_NUM; bx++) {
        u8 normal_trees = 0;
        u8 other_trees = 0;

        mAGrw_SetTree0Info(tree0_info, island_block->items[0]);
        grow_info.block_x = island_block_x_nums[bx];
        grow_info.block_z = mISL_BLOCK_Z;
        col = mFI_GetBkNum2ColTop(grow_info.block_x, mISL_BLOCK_Z);

        if (col != NULL) {
            if (proc_type == mAGrw_GROW) {
                mAGrw_SetAroundBlockInfoIsland(&grow_info, bx);
            }

            mAGrw_GrowBlockFgItem(island_block->items[0], col, Save_Get(island.deposit[bx]), &grow_info,
                                  proc_type + mAGrw_GROW_ISLAND_FIRST);
        }

        mAGrw_ResetTree0Info(tree0_info, &normal_trees, &other_trees, island_block->items[0]);
        mAGrw_ThinTree(island_block->items[0], tree0_info, normal_trees, other_trees, mAGrw_ISL_MAX_TREES_PER_BLOCK);

        island_block++;
    }

    mAGrw_LimitTreeLineIsland(Save_Get(island).fgblock[0]);
}

static void mAGrw_CancelOn(u16* cancel, int x, int z) {
    if (x < 0)
        return;
    if (x >= FG_BLOCK_X_NUM * UT_X_NUM)
        return;
    if (z < 0)
        return;
    if (z >= FG_BLOCK_Z_NUM * UT_Z_NUM)
        return;

    {
        int bx = x / UT_X_NUM;
        int bz = z / UT_Z_NUM;
        int ut_x = x % UT_X_NUM;
        int ut_z = z % UT_Z_NUM;

        cancel += (bx + bz * FG_BLOCK_X_NUM) * UT_Z_NUM;
        cancel[ut_z] |= (1 << ut_x);
    }
}

static int mAGrw_CheckCancel12(mActor_name_t item) {
    if ((item == GOLD_TREE_S0) || (item == TREE_S0 || item == TREE_S1) ||
        (item == TREE_APPLE_S0 || item == TREE_APPLE_S1) || (item == TREE_ORANGE_S0 || item == TREE_ORANGE_S1) ||
        (item == TREE_PEACH_S0 || item == TREE_PEACH_S1) || (item == TREE_PEAR_S0 || item == TREE_PEAR_S1) ||
        (item == TREE_CHERRY_S0 || item == TREE_CHERRY_S1) ||
        (item == TREE_1000BELLS_S0 || item == TREE_1000BELLS_S1) ||
        (item == TREE_10000BELLS_S0 || item == TREE_10000BELLS_S1) ||
        (item == TREE_30000BELLS_S0 || item == TREE_30000BELLS_S1) ||
        (item == TREE_100BELLS_S0 || item == TREE_100BELLS_S1) || (item == TREE_PALM_S0 || item == TREE_PALM_S1) ||
        (item == CEDAR_TREE_S0 || item == CEDAR_TREE_S1) || (item == GOLD_TREE_S1)) {
        return TRUE;
    }

    return FALSE;
}

static int mAGrw_CheckCancel32(mActor_name_t item) {
    if ((item == TREE_S2 || item == TREE) || (item == TREE_1000BELLS_S2 || item == TREE_1000BELLS) ||
        (item == TREE_10000BELLS_S2 || item == TREE_10000BELLS) ||
        (item == TREE_30000BELLS_S2 || item == TREE_30000BELLS) ||
        (item == TREE_100BELLS_S2 || item == TREE_100BELLS) || (item == CEDAR_TREE_S2 || item == CEDAR_TREE) ||
        (item == GOLD_TREE_S2 || item == GOLD_TREE_SHOVEL || item == GOLD_TREE) ||
        (item == TREE_APPLE_S2 || item == TREE_APPLE_NOFRUIT_0 || item == TREE_APPLE_NOFRUIT_1 ||
         item == TREE_APPLE_NOFRUIT_2 || item == TREE_APPLE_FRUIT) ||
        (item == TREE_ORANGE_S2 || item == TREE_ORANGE_NOFRUIT_0 || item == TREE_ORANGE_NOFRUIT_1 ||
         item == TREE_ORANGE_NOFRUIT_2 || item == TREE_ORANGE_FRUIT) ||
        (item == TREE_PEACH_S2 || item == TREE_PEACH_NOFRUIT_0 || item == TREE_PEACH_NOFRUIT_1 ||
         item == TREE_PEACH_NOFRUIT_2 || item == TREE_PEACH_FRUIT) ||
        (item == TREE_PEAR_S2 || item == TREE_PEAR_NOFRUIT_0 || item == TREE_PEAR_NOFRUIT_1 ||
         item == TREE_PEAR_NOFRUIT_2 || item == TREE_PEAR_FRUIT) ||
        (item == TREE_CHERRY_S2 || item == TREE_CHERRY_NOFRUIT_0 || item == TREE_CHERRY_NOFRUIT_1 ||
         item == TREE_CHERRY_NOFRUIT_2 || item == TREE_CHERRY_FRUIT) ||
        (item == TREE_PALM_S2 || item == TREE_PALM_NOFRUIT_0 || item == TREE_PALM_NOFRUIT_1 ||
         item == TREE_PALM_NOFRUIT_2 || item == TREE_PALM_FRUIT) ||
        (item == TREE_BEES || item == TREE_FTR || item == TREE_LIGHTS || item == TREE_PRESENT) ||
        (item == TREE_BELLS) || (item == CEDAR_TREE_BELLS || item == CEDAR_TREE_FTR || item == CEDAR_TREE_BEES) ||
        (item == CEDAR_TREE_LIGHTS) || (item == GOLD_TREE_BELLS || item == GOLD_TREE_FTR || item == GOLD_TREE_BEES)) {
        return TRUE;
    }

    return FALSE;
}

static int mAGrw_CheckCancel22(mActor_name_t item) {
    switch (item) {
        case MAP_BOARD0:
        case MESSAGE_BOARD0:
        case MUSIC_BOARD0:
            return TRUE;

        default:
            return FALSE;
    }
}

static int mAGrw_CheckCancel36(mActor_name_t item) {
    if (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_STRUCT) {
        if ((item >= SIGN00 && item <= SIGN20) || (item >= NPC_HOUSE_START && item <= NPC_HOUSE_END) ||
            (item == KAMAKURA) || (item == POLICE_STATION) || (item == TENT)) {
            return TRUE;
        }
    }

    return FALSE;
}

static int mAGrw_CheckHide36(mActor_name_t item) {
    if (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_STRUCT) {
        if ((item >= NPC_HOUSE_START && item <= NPC_HOUSE_END) || (item == KAMAKURA) || (item == POLICE_STATION) ||
            (item == TENT)) {
            return TRUE;
        }
    }

    return FALSE;
}

static int mAGrw_CheckCancelLeft45(mActor_name_t item) {
    if (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_STRUCT) {
        if ((item == HOUSE0) || (item == HOUSE2)) {
            return TRUE;
        }
    }

    return FALSE;
}

static int mAGrw_CheckCancelRight45(mActor_name_t item) {
    if (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_STRUCT) {
        if ((item == HOUSE1) || (item == HOUSE3)) {
            return TRUE;
        }
    }

    return FALSE;
}

static int mAGrw_CheckCancel46(mActor_name_t item) {
    switch (item) {
        case POST_OFFICE:
        case SHOP0:
        case NEEDLEWORK_SHOP:
            return TRUE;

        default:
            return FALSE;
    }
}

static int mAGrw_CheckCancel23(mActor_name_t item) {
    if (item == TOUDAI) {
        return TRUE;
    }

    return FALSE;
}

static int mAGrw_CheckCancel57(mActor_name_t item) {
    if (item == SHOP1) {
        return TRUE;
    }

    return FALSE;
}

static int mAGrw_CheckCancel68(mActor_name_t item) {
    if (item == SHOP2 || item == SHOP3) {
        return TRUE;
    }

    return FALSE;
}

static int mAGrw_CheckCancel77(mActor_name_t item) {
    if (item == MUSEUM) {
        return TRUE;
    }

    return FALSE;
}

static void mAGrw_SetCancelOn(u16* cancel, int x_base, int z_base, int x_start, int x_end, int z_start, int z_end) {
    int z;
    int x;

    for (z = z_start; z <= z_end; z++) {
        for (x = x_start; x <= x_end; x++) {
            mAGrw_CancelOn(cancel, x_base + x, z_base + z);
        }
    }
}

typedef int (*mAGrw_CHECK_CANCEL_UT_PROC)(mActor_name_t);

static void mAGrw_SetblockCancelUtInfo(u16* cancel_ut, mActor_name_t* items, int x_base, int z_base) {
    static mAGrw_CHECK_CANCEL_UT_PROC check_cancel[mAGrw_CHECK_CANCEL_NUM] = {
        &mAGrw_CheckCancel12,     &mAGrw_CheckCancel32,      &mAGrw_CheckCancel22, &mAGrw_CheckCancel36,
        &mAGrw_CheckCancelLeft45, &mAGrw_CheckCancelRight45, &mAGrw_CheckCancel46, &mAGrw_CheckCancel23,
        &mAGrw_CheckCancel57,     &mAGrw_CheckCancel68,      &mAGrw_CheckCancel77
    };

    int proc;
    int ut_z;
    int ut_x;

    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
            for (proc = 0; proc < mAGrw_CHECK_CANCEL_NUM; proc++) {
                if ((*check_cancel[proc])(*items) == TRUE) {
                    mAGrw_SetCancelOn(cancel_ut, x_base + ut_x, z_base + ut_z, l_non_area[proc][0], l_non_area[proc][1],
                                      l_non_area[proc][2], l_non_area[proc][3]);
                    mAGrw_SetCancelOn(cancel_ut, x_base + ut_x, z_base + ut_z, 0, 0, 0, 0);

                    break;
                }
            }

            items++;
        }
    }
}

static void mAGrw_HideOn(u16* hide, int ut_x, int ut_z) {
    if (ut_x < 0)
        return;
    if (ut_x >= UT_X_NUM)
        return;
    if (ut_z < 0)
        return;
    if (ut_z >= UT_Z_NUM)
        return;

    hide[ut_z] |= (1 << ut_x);
}

static void mAGrw_SetHideOn(u16* hide, int x_base, int z_base, mAGrw_HideAreaTable_c* hide_area) {
    mAGrw_HideArea_c* hide_p = hide_area->hide_p;
    int num = hide_area->num;
    int i;

    if (num > 0 && hide_p != NULL) {
        for (i = 0; i < num; i++) {
            mAGrw_HideOn(hide, x_base + hide_p->x_ofs, z_base + hide_p->z_ofs);
            hide_p++;
        }
    }
}

extern void mAGrw_SetHideUtInfo(u16* hide, mActor_name_t* items) {
    static mAGrw_CHECK_CANCEL_UT_PROC check_hide[mAGrw_CHECK_CANCEL_NUM] = {
        &mAGrw_CheckCancel12,     &mAGrw_CheckCancel32,      &mAGrw_CheckCancel22, &mAGrw_CheckHide36,
        &mAGrw_CheckCancelLeft45, &mAGrw_CheckCancelRight45, &mAGrw_CheckCancel46, &mAGrw_CheckCancel23,
        &mAGrw_CheckCancel57,     &mAGrw_CheckCancel68,      &mAGrw_CheckCancel77
    };

    int i;
    int ut_z;
    int ut_x;

    if (hide != NULL && items != NULL) {
        for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
            for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                for (i = 0; i < mAGrw_CHECK_CANCEL_NUM; i++) {
                    if ((*check_hide[i])(*items) == TRUE) {
                        mAGrw_SetHideOn(hide, ut_x, ut_z, &l_hide_area_table[i]);

                        break;
                    }
                }

                items++;
            }
        }
    }
}

static void mAGrw_SetCancelUtInfo(u16* cancel) {
    mFM_fg_c* fg_block = Save_Get(fg[0]);
    int z_base;
    int bz;
    int bx;

    bzero(cancel, FG_BLOCK_TOTAL_NUM * UT_Z_NUM * sizeof(u16));
    z_base = 0;

    for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
        for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
            mAGrw_SetblockCancelUtInfo(cancel, fg_block->items[0], bx * UT_X_NUM, bz * UT_Z_NUM);
            fg_block++;
        }
    }
}

static void mAGrw_GetDepositAbleFlatNum(u8* candidate_num, u8* flat_num, mActor_name_t* items, mCoBG_Collision_u* col,
                                        u16* cancel) {
    int ut_z;
    int ut_x;

    *candidate_num = 0;
    *flat_num = 0;

    if (items != NULL && col != NULL) {
        for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
            for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
                /* Check that the cancel flag for the unit isn't set, that the unit has no item, and that a hole can be
                 * dug */
                if ((((cancel[0] >> ut_x) & 1) != 1) && (items[0] == EMPTY_NO) &&
                    (mCoBG_CheckHole_OrgAttr(col->data.unit_attribute))) {
                    candidate_num[0]++;

                    /* Check if the unit collision data is a flat square */
                    if ((col->data.center == col->data.top_left) && (col->data.center == col->data.bot_left) &&
                        (col->data.center == col->data.bot_right) && (col->data.center == col->data.top_right) &&
                        (mCoBG_CheckSandHole_ClData(col) != TRUE)) {
                        flat_num[0]++;
                    }
                }

                items++;
                col++;
            }

            cancel++;
        }
    }
}

static void mAGrw_SetShineGroundBlock(mAGrw_SSPosInfo_c* pos_info, mActor_name_t* items, mCoBG_Collision_u* col,
                                      u8 flat_num, u16* cancel) {
    int selected_ut = RANDOM(flat_num);

    int ut_z;
    int ut_x;

    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
            /* Check that the cancel flag for the unit isn't set, that the unit has no item, and that a hole can be dug
             */
            if ((((cancel[0] >> ut_x) & 1) != 1) && (items[0] == EMPTY_NO) &&
                (mCoBG_CheckHole_OrgAttr(col->data.unit_attribute))) {
                /* Check if the unit collision data is a flat square */
                if ((col->data.center == col->data.top_left) && (col->data.center == col->data.bot_left) &&
                    (col->data.center == col->data.bot_right) && (col->data.center == col->data.top_right) &&
                    (mCoBG_CheckSandHole_ClData(col) != TRUE)) {
                    if (selected_ut == 0) {
                        pos_info->ut_x = ut_x;
                        pos_info->ut_z = ut_z;
                        cancel[0] |= (1 << ut_x); // update unit as taken

                        ut_z = UT_Z_NUM;
                        break;
                    } else {
                        selected_ut--;
                    }
                }
            }

            items++;
            col++;
        }

        cancel++;
    }
}

static void mAGrw_SetShineGround_com(mAGrw_SSPosInfo_c* pos_info, u8* block_flat_candidates, u8* flat_num,
                                     u8* block_candidates, u8* candidate_num, u16* cancel) {
    int selected_block;
    mFM_fg_c* fg_block;

    int i;

    if (block_flat_candidates[0] != 0) {
        selected_block = RANDOM(block_flat_candidates[0]);
        fg_block = Save_Get(fg[0]);

        for (i = 0; i < FG_BLOCK_TOTAL_NUM; i++) {
            if (flat_num[0] != 0) {
                if (selected_block == 0) {
                    int bx = (i % FG_BLOCK_X_NUM) + 1;
                    int bz = (i / FG_BLOCK_X_NUM) + 1;

                    pos_info->block_x = bx;
                    pos_info->block_z = bz;

                    mAGrw_SetShineGroundBlock(pos_info, fg_block->items[0], mFI_GetBkNum2ColTop(bx, bz), flat_num[0],
                                              cancel);
                    flat_num[0]--;
                    if (flat_num[0] == 0) {
                        block_flat_candidates[0]--;
                    }

                    candidate_num[0]--;
                    if (candidate_num[0] == 0) {
                        block_candidates[0]--; // remove this block from possible candidates
                    }

                    break;
                } else {
                    selected_block--;
                }
            }

            flat_num++;
            candidate_num++;
            fg_block++;
            cancel += UT_Z_NUM;
        }
    }
}

static void mAGrw_SetShineGround(mAGrw_SSPosInfo_c* pos_info, u8* block_flat_candidates, u8* flat_num,
                                 u8* block_candidates, u8* candidate_num, u16* cancel) {
    mAGrw_SSPosInfo_c* p_info = pos_info;
    int i;

    for (i = 0; i < TOTAL_PLAYER_NUM; i++) {
        mAGrw_ClearSSPosInfo_com(p_info);
        mAGrw_SetShineGround_com(p_info, block_flat_candidates, flat_num, block_candidates, candidate_num, cancel);

        p_info++;
    }
}

static void mAGrw_SetHaniwaBlock(mActor_name_t* items, mActor_name_t haniwa_item, mCoBG_Collision_u* col, u16* deposit,
                                 u16* cancel, u8 depositable_num) {
    mMsm_DepositItemBlock_cancel(items, haniwa_item, col, deposit, cancel, depositable_num);
}

static void mAGrw_SetHaniwa(u8* block_candidates, u8* candidate_num, u16* cancel) {
    mActor_name_t haniwas[mAGrw_HANIWA_NUM];
    u8 depositable_num;
    int selected_block;
    u8* candidate_num_p = candidate_num;
    u16* cancel_p = cancel;
    int bz;
    int bx;
    int i;
    int block;

    mSP_RandomHaniwaSelect(haniwas, mAGrw_HANIWA_NUM);

    for (i = 0; i < mAGrw_HANIWA_NUM; i++) {
        candidate_num = candidate_num_p;
        cancel = cancel_p;

        if (block_candidates[0] == 0) {
            break; // no candidate blocks for placing a haniwa down
        }

        selected_block = RANDOM(block_candidates[0]);

        for (block = 0; block < FG_BLOCK_TOTAL_NUM; block++) {
            depositable_num = candidate_num[0];

            if (depositable_num != 0) {
                if (selected_block <= 0) {
                    bx = block % FG_BLOCK_X_NUM;
                    bz = block / FG_BLOCK_X_NUM;

                    mAGrw_SetHaniwaBlock(Save_Get(fg[bz][bx]).items[0], haniwas[i], mFI_GetBkNum2ColTop(bx + 1, bz + 1),
                                         Save_Get(deposit[block]), cancel, depositable_num);

                    if (block_candidates[0] > 1) {
                        block_candidates[0]--;
                        candidate_num[0] = 0;
                    }

                    break;
                } else {
                    selected_block--;
                }
            }

            candidate_num++;
            cancel += UT_Z_NUM;
        }
    }
}

static u8 l_candidate_flat_num[FG_BLOCK_TOTAL_NUM]; /* TODO: this is definitely going to be bss ordering issue */

static void mAGrw_SetDigItem(mAGrw_SSPosInfo_c* pos_info, int* deposit_haniwa, u16* cancel) {
    mFM_fg_c* fg = Save_Get(fg[0]);
    u8 block_candidates = 0;
    u8 block_flat_candidates = 0;
    u8* candidate_num_p = l_candidate_num;
    u8* candidate_flat_num_p = l_candidate_flat_num;
    u16* cancel_p = cancel;
    int bz;
    int bx;

    bzero(l_candidate_num, FG_BLOCK_TOTAL_NUM * sizeof(u8));
    bzero(l_candidate_flat_num, FG_BLOCK_TOTAL_NUM * sizeof(u8));
    for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
        for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
            if (mFI_CheckBlockKind_OR(bx + 1, bz + 1,
                                      mRF_BLOCKKIND_PLAYER | mRF_BLOCKKIND_SHRINE | mRF_BLOCKKIND_STATION |
                                          mRF_BLOCKKIND_POOL | mRF_BLOCKKIND_DUMP) == FALSE) {
                mAGrw_GetDepositAbleFlatNum(candidate_num_p, candidate_flat_num_p, fg->items[0],
                                            mFI_GetBkNum2ColTop(bx + 1, bz + 1), cancel);

                if (candidate_num_p[0] != 0) {
                    block_candidates++;
                }

                if (candidate_flat_num_p[0] != 0) {
                    block_flat_candidates++;
                }
            }

            candidate_num_p++;
            candidate_flat_num_p++;
            fg++;
            cancel += UT_Z_NUM;
        }
    }

    mAGrw_SetShineGround(pos_info, &block_flat_candidates, l_candidate_flat_num, &block_candidates, l_candidate_num,
                         cancel_p);

    if (deposit_haniwa[0] == TRUE) {
        mAGrw_SetHaniwa(&block_candidates, l_candidate_num, cancel_p);
        deposit_haniwa[0] = FALSE;
    }
}

static void mAGrw_SpoilPossession(mActor_name_t* items, int count) {
    for (count; count != 0; count--) {
        mAGrw_SpoilKabu(items, NULL);
        items++;
    }
}

static void mAGrw_SpoilAllPossession(int spoil_kabu) {
    Private_c* priv;
    Haniwa_Item_c* haniwa_item;

    int i;
    int j;
    int k;

    if (spoil_kabu == TRUE) {
        priv = Save_Get(private_data);

        for (i = 0; i < PLAYER_NUM; i++) {
            mAGrw_SpoilPossession(priv->inventory.pockets, mPr_POCKETS_SLOT_COUNT);
            priv++;
        }

        if (Common_Get(player_no) == mPr_FOREIGNER) {
            mAGrw_SpoilPossession(Common_Get(now_private)->inventory.pockets, mPr_POCKETS_SLOT_COUNT);
        }

        for (i = 0; i < mHS_HOUSE_NUM; i++) {
            for (j = 0; j < mHm_ROOM_NUM; j++) {
                for (k = 0; k < mHm_LAYER_NUM; k++) {
                    mAGrw_SpoilPossession((&Save_Get(homes[i]).floors[j].layer_main)[k].items[0], UT_TOTAL_NUM);
                }
            }

            haniwa_item = Save_Get(homes[i]).haniwa.items;
            for (j = 0; j < HANIWA_ITEM_HOLD_NUM; j++) {
                mAGrw_SpoilKabu(&haniwa_item->item, NULL);
                haniwa_item++;
            }
        }
    }
}

static int mAGrw_CheckClearDumpDay(lbRTC_time_c* grow_time, lbRTC_time_c* now_time) {
    static int clean_week[2] = { lbRTC_MONDAY, lbRTC_THURSDAY };

    int delta_days;
    lbRTC_time_c temp;
    int add_days;
    int weekday;
    int res = FALSE;
    int i;

    if (lbRTC_IsOverTime(grow_time, now_time) == lbRTC_OVER) {
        delta_days = lbRTC_GetIntervalDays(grow_time, now_time);
    } else {
        delta_days = lbRTC_GetIntervalDays(now_time, grow_time);
    }

    if (delta_days >= lbRTC_WEEK) {
        res = TRUE;
    } else {
        for (i = 0; i < 2; i++) {
            add_days = 0;
            lbRTC_TimeCopy(&temp, grow_time);

            if (temp.weekday > clean_week[i]) {
                add_days = (lbRTC_WEEK - temp.weekday) + clean_week[i];
            } else if (temp.weekday < clean_week[i]) {
                add_days = clean_week[i] - temp.weekday;
            }

            lbRTC_Add_DD(&temp, add_days);

            if (lbRTC_IsOverTime(&temp, now_time) == lbRTC_OVER) {
                res = TRUE;

                break;
            }
        }
    }

    return res;
}

extern void mAGrw_SearchDump(mFI_unit_c* dump_info) {
    if (mFI_BlockKind2BkNum(&dump_info->block_x, &dump_info->block_z, mRF_BLOCKKIND_DUMP)) {
        mActor_name_t* fg = mFI_BkNumtoUtFGTop(dump_info->block_x, dump_info->block_z);
        dump_info->block_data = fg;

        if (fg != NULL) {
            int i;

            for (i = 0; i < UT_TOTAL_NUM; i++) {
                if (fg[0] == DUMP) {
                    dump_info->unit_x = i & 15;
                    dump_info->unit_z = i >> 4;

                    break;
                }

                fg++;
            }
        }
    } else {
        dump_info->block_x = -1;
        dump_info->block_z = -1;
        dump_info->block_data = NULL;
    }
}

static void mAGrw_ClearDumpArea(mFI_unit_c* dump_info) {
    mActor_name_t* dump_item;
    u16* deposit;
    int ut_x;
    int ut_z;
    int row;
    int col;

    deposit = mFI_GetDepositP(dump_info->block_x, dump_info->block_z);

    ut_x = dump_info->unit_x - 4;
    ut_z = dump_info->unit_z - 4;
    dump_item = dump_info->block_data + dump_info->unit_x + (dump_info->unit_z * UT_X_NUM);

    dump_item -= (4 * UT_X_NUM) + 4; /* dump is 4x4 so move back to the actual start */

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            if (dump_item != NULL) {
                mSN_ClearSnowman(dump_item);
                *dump_item = EMPTY_NO;

                if (deposit != NULL) {
                    mFI_BlockDepositOFF(deposit, ut_x + col, ut_z + row);
                }
            }

            dump_item++;
        }

        dump_item += 12; /* move on to the next row */
    }
}

static void mAGrw_ClearDump(mFI_unit_c* dump_info, lbRTC_time_c* grow_time, lbRTC_time_c* now_time) {
    if (mAGrw_CheckClearDumpDay(grow_time, now_time) == TRUE && dump_info->block_data != NULL) {
        mAGrw_ClearDumpArea(dump_info);
    }
}

static mActor_name_t mAGrw_GetSetItemDump() {
    static int category[10] = { mSP_KIND_FURNITURE, mSP_KIND_FURNITURE, mSP_KIND_CLOTH, mSP_KIND_CLOTH, mSP_KIND_CLOTH,
                                mSP_KIND_CLOTH,     mSP_KIND_PAPER,     mSP_KIND_PAPER, mSP_KIND_PAPER, mSP_KIND_MAX };

    mActor_name_t set_item = EMPTY_NO;
    int cat = category[RANDOM(10)];

    if (cat == mSP_KIND_MAX) {
        mSP_RandomUmbSelect(&set_item, 1);
    } else {
        mSP_SelectRandomItem_New(NULL, &set_item, 1, NULL, 0, cat, mSP_LISTTYPE_ABC, FALSE);
    }

    return set_item;
}

static void mAGrw_SetItemDumpBlock(mActor_name_t* items) {
    int col;
    int row;
    mActor_name_t* dump_item = items;
    int empty_slots = 0;

    for (row = 0; row < 4; row++) {
        for (col = 0; col < 4; col++) {
            if (*items == EMPTY_NO) {
                empty_slots++;
            }

            items++;
        }

        items += 12; /* move on to the next row */
    }

    if (empty_slots > 0) {
        int selected_ut = RANDOM(empty_slots);
        items = dump_item;

        for (row = 0; row < 4; row++) {
            for (col = 0; col < 4; col++) {
                if (*items == EMPTY_NO) {
                    if (selected_ut <= 0) {
                        *items = mAGrw_GetSetItemDump();

                        row = 4;
                        break;
                    } else {
                        selected_ut--;
                    }
                }

                items++;
            }

            items += 12; /* move on to the next row */
        }
    }
}

static void mAGrw_SetItemDump(mFI_unit_c* dump_info) {
    int used_spots = 0;
    int i;

    if (dump_info->block_data != NULL) {
        mActor_name_t* dump_item_p;
        mActor_name_t* dump_item = dump_info->block_data + dump_info->unit_x + (dump_info->unit_z * UT_X_NUM);
        int row;
        int col;

        dump_item -= (4 * UT_X_NUM) + 4; /* dump is 4x4 so move back to the actual start */
        dump_item_p = dump_item;
        for (row = 0; row < 4; row++) {
            for (col = 0; col < 4; col++) {
                if (*dump_item != EMPTY_NO) {
                    used_spots++;
                }

                dump_item++;
            }

            dump_item += 12; /* move on to the next row */
        }

        if (used_spots <= 7) {
            for (i = 0; i < mAGrw_DUMP_ITEM_NUM; i++) {
                mAGrw_SetItemDumpBlock(dump_item_p);
            }
        }
    }
}

static int mAGrw_GetGrassMax(lbRTC_time_c* now_time, lbRTC_time_c* grow_time) {
    int delta_days;
    int grass_days;

    if (lbRTC_IsOverTime(grow_time, now_time) == lbRTC_OVER) {
        delta_days = lbRTC_GetIntervalDays(grow_time, now_time);
    } else {
        delta_days = lbRTC_GetIntervalDays(now_time, grow_time);
    }

    delta_days++;
    if (delta_days > 1 && now_time->hour < 6) {
        delta_days--;
    }

    return delta_days * mAGrw_GRASS_PER_DAY;
}

static u8 mAGrw_GetChangeAbleGrass(mActor_name_t* items, mCoBG_Collision_u* col, u16* cancel, int bx, int bz) {
    xyz_t wpos_temp = { 0.0f, 0.0f, 0.0f };
    xyz_t wpos = { 0.0f, 0.0f, 0.0f };
    u8 change_able_grass = 0;
    int ut_z;
    int ut_x;

    mFI_BkNum2WposXZ(&wpos.x, &wpos.z, bx, bz);

    wpos.x += mFI_UT_WORLDSIZE_X_F / 2.0f;
    wpos.z += mFI_UT_WORLDSIZE_Z_F / 2.0f;

    wpos_temp = wpos;
    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        wpos_temp.x = wpos.x;
        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
            if (((cancel[0] >> ut_x) & 1) != 1 && (items[0] == EMPTY_NO) &&
                (mCoBG_Attribute2CheckPlant(col->data.unit_attribute, &wpos_temp) == mCoBG_PLANT4)) {
                change_able_grass++;
            }

            items++;
            col++;
            wpos_temp.x += mFI_UT_WORLDSIZE_X_F;
        }

        cancel++;
        wpos_temp.z += mFI_UT_WORLDSIZE_Z_F;
    }

    return change_able_grass;
}

static void mAGrw_PutGrassBlock(mActor_name_t* items, mActor_name_t grass, mCoBG_Collision_u* col,
                                u8* change_able_grass, u16* cancel, int bx, int bz) {
    xyz_t wpos_temp = { 0.0f, 0.0f, 0.0f };
    xyz_t wpos = { 0.0f, 0.0f, 0.0f };
    int selected_ut;
    int ut_z;
    int ut_x;

    mFI_BkNum2WposXZ(&wpos.x, &wpos.z, bx, bz);

    wpos.x += mFI_UT_WORLDSIZE_X_F / 2.0f;
    wpos.z += mFI_UT_WORLDSIZE_Z_F / 2.0f;

    wpos_temp = wpos;
    selected_ut = RANDOM(*change_able_grass);
    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        wpos_temp.x = wpos.x;
        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
            if (((cancel[0] >> ut_x) & 1) != 1 && (items[0] == EMPTY_NO) &&
                (mCoBG_Attribute2CheckPlant(col->data.unit_attribute, &wpos_temp) == mCoBG_PLANT4)) {
                if (selected_ut <= 0) {
                    items[0] = grass;
                    change_able_grass[0]--;

                    return;
                } else {
                    selected_ut--;
                }
            }

            items++;
            col++;
            wpos_temp.x += mFI_UT_WORLDSIZE_X_F;
        }

        cancel++;
        wpos_temp.z += mFI_UT_WORLDSIZE_Z_F;
    }
}

static void mAGrw_SetGrass(lbRTC_time_c* now_time, lbRTC_time_c* grow_time, u16* cancel) {
    mActor_name_t grass_table[mAGrw_GRASS_TABLE_NUM];
    int grass_max;
    mFM_fg_c* fg_block;
    u8* candidate_num;
    u16* cancel_p;
    int grass_table_idx;
    int candidate_blocks;
    int bx;
    int bz;
    int i;
    int j;

    fg_block = Save_Get(fg[0]);
    cancel_p = cancel;
    candidate_num = l_candidate_num;
    grass_table_idx = 0;
    candidate_blocks = 0;

    mAGrw_MakeGrassTable(grass_table);
    bzero(l_candidate_num, FG_BLOCK_TOTAL_NUM * sizeof(u8));
    grass_max = mAGrw_GetGrassMax(now_time, grow_time);

    for (i = 1; i < FG_BLOCK_Z_NUM + 1; i++) {
        for (j = 1; j < FG_BLOCK_X_NUM + 1; j++) {
            mCoBG_Collision_u* col = mFI_GetBkNum2ColTop(j, i);

            if (fg_block != NULL && col != NULL) {
                candidate_num[0] = mAGrw_GetChangeAbleGrass(fg_block->items[0], col, cancel, j, i);

                if (candidate_num[0] > 0) {
                    candidate_blocks++;
                }
            }

            candidate_num++;
            fg_block++;
            cancel += UT_Z_NUM;
        }
    }

    for (i = 0; i < grass_max; i++) {
        if (candidate_blocks > 0) {
            int selected_block;
            mCoBG_Collision_u* col;

            fg_block = Save_Get(fg[0]);
            candidate_num = l_candidate_num;
            selected_block = RANDOM(candidate_blocks);
            cancel = cancel_p;

            for (j = 0; j < FG_BLOCK_TOTAL_NUM; j++) {
                if (candidate_num[0] > 0) {
                    if (selected_block <= 0) {
                        bx = (j % FG_BLOCK_X_NUM) + 1;
                        bz = (j / FG_BLOCK_X_NUM) + 1;
                        col = mFI_GetBkNum2ColTop(bx, bz);
                        mAGrw_PutGrassBlock(fg_block->items[0], grass_table[grass_table_idx], col, candidate_num,
                                            cancel, bx, bz);

                        if (candidate_num[0] <= 0) {
                            candidate_blocks--;
                        }

                        break;
                    }

                    selected_block--;
                }

                candidate_num++;
                fg_block++;
                cancel += UT_Z_NUM;
            }

            grass_table_idx++;
            if (grass_table_idx >= mAGrw_GRASS_TABLE_NUM) {
                grass_table_idx = 0;
            }
        } else {
            break;
        }
    }
}

static void mAGrw_ClearGrass() {
    mFM_fg_c* fg_block = Save_Get(fg[0]);
    mActor_name_t* items;
    int block;
    int unit;

    for (block = 0; block < FG_BLOCK_TOTAL_NUM; block++) {
        items = fg_block->items[0];
        for (unit = 0; unit < UT_TOTAL_NUM; unit++) {
            if (IS_ITEM_GRASS(items[0])) {
                items[0] = EMPTY_NO;
            }

            items++;
        }

        fg_block++;
    }
}

static void mAGrw_AllMeltSnowman() {
    mFM_fg_c* fg_block = Save_Get(fg[0]);
    mActor_name_t* items;
    int block;
    int unit;

    for (block = 0; block < FG_BLOCK_TOTAL_NUM; block++) {
        items = fg_block->items[0];
        for (unit = 0; unit < UT_TOTAL_NUM; unit++) {
            mSN_ClearSnowman(items);

            items++;
        }

        fg_block++;
    }
}

static void mAgrw_ZuruSpoilKabuBlockFgItem(mActor_name_t* items, mCoBG_Collision_u* col, mAGrw_GrowInfo_c* grow_info) {
    xyz_t wpos_temp;
    xyz_t wpos = { 0.0f, 0.0f, 0.0f };
    int ut_z;
    int ut_x;

    mFI_BkNum2WposXZ(&wpos.x, &wpos.z, grow_info->block_x, grow_info->block_z);
    wpos.x += mFI_UT_WORLDSIZE_X_F / 2.0f;
    wpos.z += mFI_UT_WORLDSIZE_Z_F / 2.0f;

    wpos_temp = wpos;
    for (ut_z = 0; ut_z < UT_Z_NUM; ut_z++) {
        wpos_temp.x = wpos.x;
        for (ut_x = 0; ut_x < UT_X_NUM; ut_x++) {
            grow_info->ut_x = ut_x;
            grow_info->ut_z = ut_z;

            mAGrw_SpoilKabu(items, grow_info);
            items++;
            wpos_temp.x += mFI_UT_WORLDSIZE_X_F;
        }
        wpos_temp.z += mFI_UT_WORLDSIZE_X_F;
    }
}

static void mAGrw_ZuruSpoilKabuFieldFgItem() {
    mAGrw_GrowInfo_c grow_info;
    mFM_fg_c* fg_block = Save_Get(fg[0]);
    mCoBG_Collision_u* col;
    int bz;
    int bx;

    mAGrw_ClearGrowInfo(&grow_info);
    grow_info.spoil_kabu = TRUE;

    for (bz = 0; bz < FG_BLOCK_Z_NUM; bz++) {
        for (bx = 0; bx < FG_BLOCK_X_NUM; bx++) {
            grow_info.block_x = bx + 1;
            grow_info.block_z = bz + 1;

            col = mFI_GetBkNum2ColTop(bx + 1, bz + 1);

            if (col != NULL) {
                mAgrw_ZuruSpoilKabuBlockFgItem(fg_block->items[0], col, &grow_info);
            }

            fg_block++;
        }
    }
}

static void mAGrw_ZuruSpoilKabuIslandFgItem(Island_c* island) {
    mAGrw_GrowInfo_c grow_info;
    mFM_fg_c* fg_block = island->fgblock[0];
    mCoBG_Collision_u* col;
    int island_bx[mISL_FG_BLOCK_X_NUM];
    int bx;

    mAGrw_ClearGrowInfo(&grow_info);
    grow_info.spoil_kabu = TRUE;
    mFI_GetIslandBlockNumX(island_bx);

    for (bx = 0; bx < mISL_FG_BLOCK_X_NUM; bx++) {
        grow_info.block_x = island_bx[bx];
        grow_info.block_z = mISL_BLOCK_Z;

        col = mFI_GetBkNum2ColTop(island_bx[bx], mISL_BLOCK_Z);

        if (col != NULL) {
            mAgrw_ZuruSpoilKabuBlockFgItem(fg_block->items[0], col, &grow_info);
        }

        fg_block++;
    }
}

static void mAGrw_ZuruSpoilKabu(lbRTC_time_c* now_time) {
    if (Save_Get(save_exist) == TRUE &&
        lbRTC_IsEqualDate(now_time->year, now_time->month, now_time->day, Save_Get(save_check).time.year,
                          Save_Get(save_check).time.month, Save_Get(save_check).time.day) < lbRTC_EQUAL) {
        mAGrw_ZuruSpoilKabuFieldFgItem();
        mAGrw_ZuruSpoilKabuIslandFgItem(Save_GetPointer(island));
        mAGrw_SpoilAllPossession(TRUE);
    }
}

static void mAGrw_SpoilKabuIslandCottage(Island_c* island) {
    int i;

    for (i = 0; i < mHm_LAYER_NUM; i++) {
        mAGrw_SpoilPossession((&island->cottage.room.layer_main)[i].items[0], UT_TOTAL_NUM);
    }
}

extern void mAGrw_SpoilKabuIsland(Island_c* island) {
    mAGrw_ZuruSpoilKabuIslandFgItem(island);
    mAGrw_SpoilKabuIslandCottage(island);
}

static u16 l_cancel_ut[FG_BLOCK_TOTAL_NUM * UT_Z_NUM];

extern void mAGrw_RenewalFgItem_ovl(lbRTC_time_c* now_time, int* deposit_haniwa) {
    lbRTC_time_c* last_grow_time;
    int flower_time;
    int is_grow_time_equal;
    int is_over_time;
    int spoil_kabu;
    int proc_type;
    u8 fossil_record;
    int fossil_num;
    lbRTC_time_c grow_time;
    mFI_unit_c dump_info;

    last_grow_time = Save_GetPointer(all_grow_renew_time);
    fossil_record = 0;
    fossil_num = 0;

    if (Save_Get(scene_no) == SCENE_FG) {
        flower_time = mAGrw_CheckFlowerTime(now_time);

        if (Save_Get(clear_grass)) {
            mAGrw_ClearGrass();
        }

        if (flower_time == FALSE) {
            mAGrw_AllMeltSnowman();
        }

        if (Common_Get(event_notification_active) != TRUE) {
            is_grow_time_equal = mTM_AreTimesEqual(&mTM_rtcTime_clear_code, last_grow_time);
            is_over_time = lbRTC_IsOverTime(last_grow_time, now_time);

            if (is_grow_time_equal == TRUE || is_over_time == lbRTC_LESS) {
                if (is_grow_time_equal == TRUE) {
                    proc_type = mAGrw_GROW_FIRST;
                    *deposit_haniwa = TRUE;
                } else {
                    proc_type = mAGrw_GROW_FIRST_FORCE;
                }

                lbRTC_TimeCopy(&grow_time, &mTM_rtcTime_clear_code);
                mAGrw_SearchDump(&dump_info);
                mAGrw_GrowFieldFgItem(now_time, &grow_time, flower_time, FALSE, &fossil_record, &fossil_num, proc_type);
                mAGr_GrowIslandFgItem(now_time, &grow_time, flower_time, FALSE, proc_type);
                mAGrw_SetCancelUtInfo(l_cancel_ut);
                mMsm_DepositFossil(fossil_record, fossil_num, l_cancel_ut, proc_type);
                mAGrw_SetDigItem(Save_Get(allgrow_ss_pos_info).shine_pos, deposit_haniwa, l_cancel_ut);
                mAGrw_SetShineGround_player(Save_GetPointer(allgrow_ss_pos_info), Common_Get(player_no));
                mAGrw_SetMoneyStone(Save_GetPointer(allgrow_ss_pos_info), Save_Get(fg[0][0]).items[0]);
                mAGrw_SetMoneyStone_player(Save_GetPointer(allgrow_ss_pos_info), Common_Get(player_no));
                mAGrw_SetCarp(last_grow_time);
                mAGrw_ZuruSpoilKabu(now_time);
                lbRTC_TimeCopy(last_grow_time, now_time);
                mFAs_SetFieldRank();
            } else {
                lbRTC_TimeCopy(&grow_time, last_grow_time);
                grow_time.min = 0;
                grow_time.sec = 0;

                if (grow_time.hour >= 6) {
                    lbRTC_Add_DD(&grow_time, 1);
                    grow_time.weekday++;

                    if (grow_time.weekday >= lbRTC_WEEK) {
                        grow_time.weekday = lbRTC_SUNDAY;
                    }
                }

                grow_time.hour = 6;

                if (lbRTC_IsOverTime(&grow_time, now_time) == lbRTC_OVER) {
                    spoil_kabu = mAGrw_CheckSpoilKabuTime(&grow_time, now_time);
                    mAGrw_SearchDump(&dump_info);
                    mAGrw_GrowFieldFgItem(now_time, &grow_time, flower_time, spoil_kabu, &fossil_record, &fossil_num,
                                          mAGrw_GROW);
                    mAGr_GrowIslandFgItem(now_time, &grow_time, flower_time, spoil_kabu, mAGrw_GROW);
                    mAGrw_SetCancelUtInfo(l_cancel_ut);
                    mMsm_DepositFossil(fossil_record, fossil_num, l_cancel_ut, mAGrw_GROW);
                    mAGrw_SetDigItem(Save_Get(allgrow_ss_pos_info).shine_pos, deposit_haniwa, l_cancel_ut);
                    mAGrw_SetShineGround_player(Save_GetPointer(allgrow_ss_pos_info), Common_Get(player_no));
                    mAGrw_SetMoneyStone(Save_GetPointer(allgrow_ss_pos_info), Save_Get(fg[0][0]).items[0]);
                    mAGrw_SetMoneyStone_player(Save_GetPointer(allgrow_ss_pos_info), Common_Get(player_no));
                    mAGrw_SpoilAllPossession(spoil_kabu);
                    mAGrw_ClearDump(&dump_info, &grow_time, now_time);

                    if (Save_Get(clear_grass) == FALSE) {
                        mAGrw_SetGrass(now_time, &grow_time, l_cancel_ut);
                    }

                    mAGrw_SetCarp(last_grow_time);
                    mPB_force_set_keep_item();
                    mAGrw_SetItemDump(&dump_info);
                    lbRTC_TimeCopy(last_grow_time, now_time);
                    mFAs_SetFieldRank();
                }
            }

            Save_Set(clear_grass, FALSE);
        }
    }
}
