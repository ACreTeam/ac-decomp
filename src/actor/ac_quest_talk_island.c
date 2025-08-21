#include "ac_quest_talk_normal_init.h"

#include "m_font.h"
#include "m_msg.h"
#include "m_shop.h"
#include "m_string.h"
#include "m_handbill.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "lb_reki.h"
#include "m_house.h"
#include "m_melody.h"
#include "m_ledit_ovl.h"
#include "libultra/libultra.h"

static int aQMgr_decide_msg_trade(QUEST_MANAGER_ACTOR* manager, int looks);

enum {
    aQMgr_TALK_STEP_SELECT_TALK,
    aQMgr_TALK_STEP_DEMO_ORDER,
    aQMgr_TALK_STEP_OPEN_LETTER,
    aQMgr_TALK_STEP_OPEN_MSG,
    aQMgr_TALK_STEP_GIVE_ITEM,
    aQMgr_TALK_STEP_TO_WAIT_ORDER,
    aQMgr_TALK_STEP_OPEN_BIRTHDAY,
    aQMgr_TALK_STEP_OPEN_GOBI,
    aQMgr_TALK_STEP_WRITE_LETTER,

    aQMgr_TALK_STEP_NUM
};

enum {
    aQMgr_ORDER_CHANGE_GOBI,
    aQMgr_ORDER_CANCEL_REMOVE,

    aQMgr_ORDER_NUM
};

enum {
    aQMgr_SET_STR_0,
    aQMgr_SET_STR_1,
    aQMgr_SET_STR_2,
    aQMgr_SET_STR_3,

    aQMgr_SET_STR_NUM
};

enum {
    aQMgr_DEMO_ORDER_CHANGE_ROOF_COLOR,
    aQMgr_DEMO_CONTROL_ANIMAL_INFO,
    aQMgr_DEMO_ORDER_DECIDE_TRADE,
    aQMgr_DEMO_ORDER_TRADE,
    aQMgr_DEMO_ORDER_SHOW_LETTER,
    aQMgr_DEMO_ORDER_FLUCTUATION_FRIENDSHIP,
    aQMgr_DEMO_ORDER_PLAY_MEMORY_MELODY,
    aQMgr_DEMO_ORDER_SET_CALENDAR,
    aQMgr_DEMO_ORDER_INPUT_BIRTHDAY,
    aQMgr_DEMO_ORDER_SET_STRING,

    aQMgr_DEMO_ORDER_NUM
};

enum {
    aQMgr_INPUT_BIRTHDAY,
    aQMgr_INPUT_WRITE_LETTER,

    aQMgr_INPUT_NUM
};

enum {
    aQMgr_DECIDE_MSG_FTR,
    aQMgr_DECIDE_MSG_PLAYER,
    aQMgr_DECIDE_MSG_OTHER_PLAYER,
    aQMgr_DECIDE_MSG_MAIL,

    aQMgr_DECIDE_MSG_NUM
};

static aQMgr_normal_info_c l_normal_info;

static int l_quest_category_0[] = { mSP_KIND_FURNITURE, mSP_KIND_CARPET, mSP_KIND_WALLPAPER };
static int l_quest_category_1[] = { mSP_KIND_CLOTH, mSP_KIND_PAPER, mSP_KIND_DIARY };

/* @unused */
static int aQMgr_decide_idx_prob_table(u8* prob_table, int count) {
    static u8 decide_table[100];
    int idx0;
    int idx1;
    u8 prob;
    int res = 0;
    int idx;
    int i;
    u8 j;
    int k;

    bzero(decide_table, 100);
    j = 0;
    for (i = 0; i < count; i++) {
        for (prob = prob_table[i]; prob != 0; j++, prob--) {
            if (j >= 100) {
                break;
            }

            decide_table[j] = i;
        }
    }

    k = 30;
    while (k-- != 0) {
        idx0 = RANDOM(100);
        idx1 = RANDOM(100);
        j = decide_table[idx0];
        decide_table[idx0] = decide_table[idx1];
        decide_table[idx1] = j;
    }

    idx = RANDOM(100);
    if (idx >= 0 && idx < 100) {
        res = decide_table[idx];
    }

    return res;
}

static void aQMgr_init_normal_info(aQMgr_normal_info_c* normal_info) {
    int i;

    normal_info->memory = NULL;
    normal_info->mail = NULL;
    normal_info->pay = 0;
    normal_info->item_idx = -1;
    normal_info->free_idx = -1;

    for (i = 0; i < aQMgr_NORMAL_TRADE_ITEM_NUM; i++) {
        normal_info->trade_items[i] = EMPTY_NO;
    }
}

static u8 l_aqmgr_str[16];

static void aQMgr_set_number_free_str(u32 number, int str_no) {
    mFont_UnintToString(l_aqmgr_str, sizeof(l_aqmgr_str), number, 10, TRUE, FALSE, TRUE);
    mMsg_SET_FREE_STR(str_no, l_aqmgr_str, sizeof(l_aqmgr_str));
}

static void aQMgr_set_number_item_str(u8* str_p, u32 number, int str_no) {
    mFont_UnintToString(str_p, 16, number, 10, TRUE, FALSE, TRUE);
    mMsg_SET_ITEM_STR(str_no, str_p, 16);
}

/* @unused */
static void aQMgr_set_number_free_str_add_nen(u32 year, int str_no) {
    int len;

    mem_clear(l_aqmgr_str, sizeof(l_aqmgr_str), CHAR_SPACE);
    len = mString_Load_YearStringFromRom(l_aqmgr_str, year);
    mMsg_SET_FREE_STR(str_no, l_aqmgr_str, len);
}

static void aQMgr_set_number_free_str_add_gatu(u32 month, int str_no) {
    int len;

    mem_clear(l_aqmgr_str, sizeof(l_aqmgr_str), CHAR_SPACE);

    if (month < lbRTC_JANUARY || month > lbRTC_DECEMBER) {
        month = lbRTC_JANUARY;
    }

    mString_Load_StringFromRom(l_aqmgr_str, sizeof(l_aqmgr_str), mString_MONTH_START + (month - 1));
    mMsg_SET_FREE_STR(str_no, l_aqmgr_str, sizeof(l_aqmgr_str));
}

static void aQMgr_set_number_free_str_add_nichi(u32 day, int str_no) {
    int len;

    mem_clear(l_aqmgr_str, sizeof(l_aqmgr_str), CHAR_SPACE);

    if (day < 1 || day > 31) {
        day = 1;
    }

    mString_Load_StringFromRom(l_aqmgr_str, sizeof(l_aqmgr_str), mString_DAY_START + (day - 1));
    mMsg_SET_FREE_STR(str_no, l_aqmgr_str, sizeof(l_aqmgr_str));
}

static void aQMgr_normal_set_free_str(QUEST_MANAGER_ACTOR* manager) {
    ACTOR* client = *manager->client;
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal;

    mQst_SetItemNameFreeStr(Save_Get(fruit), mMsg_FREE_STR10);
    mLd_SetFreeStrLandMuraName(animal->id.land_name, mMsg_FREE_STR11);
    mMsg_SET_FREE_STR(mMsg_FREE_STR12, animal->parent_name, LAND_NAME_SIZE);
}

typedef int (*aQMgr_CALENDAR_CONV_PROC)(lbRTC_ymd_c*, lbRTC_ymd_c*);

static void aQMgr_set_calendar_free_str(aQMgr_CALENDAR_CONV_PROC conv_proc, int month_str_no, int day_str_no, u8 month, u8 day) {
    static u8 uru_tuki[10] = "leap month";
    lbRTC_ymd_c src_date;
    lbRTC_ymd_c dst_date;
    int ret;
    
    src_date.year = (lbRTC_year_t)Common_Get(time.rtc_time.year);
    src_date.month = (lbRTC_month_t)month;
    src_date.day = (lbRTC_day_t)day;
    ret = (*conv_proc)(&dst_date, &src_date);

    if (dst_date.month == 13) {
        mMsg_SET_FREE_STR(month_str_no, uru_tuki, sizeof(uru_tuki));
    } else {
        aQMgr_set_number_free_str_add_gatu(dst_date.month, month_str_no);
    }

    aQMgr_set_number_free_str_add_nichi(dst_date.day, day_str_no);
}

static u32 aQMgr_get_rnd_no_cut_10(int min, int max, int round_to_tens) {
    int d = max - min;
    u32 add;

    if (d < 0) {
        min = max;
        d = -d;
    }

    add = (u32)RANDOM_F(d);
    if (round_to_tens == TRUE) {
        add = (add / 10) * 10;
    }

    add += min;
    return add;
}

static u32 aQMgr_GetPossessionItemSumFGTypeWithCond_cancelSPFamicom(Private_c* priv, mActor_name_t fg_type, u32 cond) {
    int sum = 0;

    if (priv != NULL) {
        mActor_name_t* pockets = priv->inventory.pockets;
        int i;

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (ITEM_NAME_GET_TYPE(*pockets) == fg_type &&
                cond == mPr_GET_ITEM_COND(priv->inventory.item_conditions, i) && !mSP_SearchItemCategoryPriority(*pockets, mSP_KIND_FURNITURE, mSP_LISTTYPE_SPECIALPRESENT, NULL)) {
                sum++;
            }
            pockets++;
        }
    }

    return sum;
}

static int aQMgr_get_possession_ftr_cpt_wl_rnd(mActor_name_t* item_p) {
    u32 item_cnt;
    int sel_idx;
    mActor_name_t* pockets_p = Now_Private->inventory.pockets;
    int ret_idx = -1;
    int i;

    item_cnt = aQMgr_GetPossessionItemSumFGTypeWithCond_cancelSPFamicom(Now_Private, NAME_TYPE_FTR0, mPr_ITEM_COND_NORMAL);
    item_cnt += aQMgr_GetPossessionItemSumFGTypeWithCond_cancelSPFamicom(Now_Private, NAME_TYPE_FTR1, mPr_ITEM_COND_NORMAL);
    item_cnt += mPr_GetPossessionItemSumItemCategoryWithCond(Now_Private, ITEM1_CAT_CARPET, mPr_ITEM_COND_NORMAL);
    item_cnt += mPr_GetPossessionItemSumItemCategoryWithCond(Now_Private, ITEM1_CAT_WALL, mPr_ITEM_COND_NORMAL);

    if (item_cnt > 0) {
        sel_idx = RANDOM(item_cnt);
        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, i) == mPr_ITEM_COND_NORMAL && !mSP_SearchItemCategoryPriority(*pockets_p, mSP_KIND_FURNITURE, mSP_LISTTYPE_SPECIALPRESENT, NULL) && (ITEM_IS_FTR(*pockets_p) || (ITEM_NAME_GET_TYPE(*pockets_p) == NAME_TYPE_ITEM1 && (ITEM_NAME_GET_CAT(*pockets_p) == ITEM1_CAT_CARPET || ITEM_NAME_GET_CAT(*pockets_p) == ITEM1_CAT_WALL)))) {
                if (sel_idx <= 0) {
                    ret_idx = i;
                    *item_p = *pockets_p;
                    break;
                }

                sel_idx--;
            }

            pockets_p++;
        }
    }

    return ret_idx;
}

static int aQMgr_get_possession_item_rnd(mActor_name_t* item_p) {
    mActor_name_t* pockets_p = Now_Private->inventory.pockets;
    u32 item_cnt;
    int sel_idx;
    int ret_idx = -1;
    int i;

    item_cnt = mPr_GetPossessionItemSumKindWithCond(Now_Private, ITM_INSECT_START, ITM_INSECT_END, mPr_ITEM_COND_NORMAL);
    item_cnt += mPr_GetPossessionItemSumKindWithCond(Now_Private, ITM_FISH_START, ITM_FISH_END, mPr_ITEM_COND_NORMAL);

    if (item_cnt > 0) {
        sel_idx = RANDOM(item_cnt);
        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, i) == mPr_ITEM_COND_NORMAL && (ITEM_IS_FISH(*pockets_p) || ITEM_IS_INSECT(*pockets_p))) {
                if (sel_idx <= 0) {
                    ret_idx = i;
                    *item_p = *pockets_p;
                    break;
                }

                sel_idx--;
            }

            pockets_p++;
        }
    }

    return ret_idx;
}

static int aQMgr_check_item_cond(u32 cond, u32 check, int idx) {
    int res = FALSE;

    if (check == mPr_GET_ITEM_COND(cond, idx)) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_get_best_ftr_idx(mActor_name_t* item_p, Private_c* priv) {
    mActor_name_t* pockets_p = priv->inventory.pockets;
    u32 cond = priv->inventory.item_conditions;
    mActor_name_t present_ftr = mNpc_GetIslandPresentFtr();
    int sel_idx;
    int count = 0;
    int ret_idx = -1;
    int i;

    *item_p = EMPTY_NO;
    for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
        if (mNpc_CheckFtrIsIslandBestFtr(pockets_p[i]) == TRUE &&
            mNpc_CheckIslandNpcRoomFtrItemNo_keep(pockets_p[i]) == TRUE &&
            !aMR_CorrespondFurniture(present_ftr, pockets_p[i]) &&
            aQMgr_check_item_cond(cond, mPr_ITEM_COND_NORMAL, i) == TRUE) {
            count++;
        }
    }

    if (count > 0) {
        sel_idx = RANDOM(count);

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++, pockets_p++) {
            if (mNpc_CheckFtrIsIslandBestFtr(*pockets_p) == TRUE &&
                mNpc_CheckIslandNpcRoomFtrItemNo_keep(*pockets_p) == TRUE &&
                !aMR_CorrespondFurniture(present_ftr, *pockets_p) &&
                aQMgr_check_item_cond(cond, mPr_ITEM_COND_NORMAL, i) == TRUE) {
                if (sel_idx == 0) {
                    *item_p = *pockets_p;
                    ret_idx = i;
                    break;
                }

                sel_idx--;
            }
        }
    }

    return ret_idx;
}

static int aQMgr_get_normal_ftr_idx(mActor_name_t* item_p, Private_c* priv) {
    mActor_name_t* pockets_p = priv->inventory.pockets;
    mActor_name_t present_ftr;
    u32 cond = priv->inventory.item_conditions;
    int sel_idx;
    int count = 0;
    int ret_idx = -1;
    int i;

    present_ftr = mNpc_GetIslandPresentFtr();
    for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
        if (!aMR_CorrespondFurniture(pockets_p[i], present_ftr) &&
            mNpc_CheckFtrIsIslandNormalFtr(pockets_p[i]) == TRUE &&
            mNpc_CheckIslandNpcRoomFtrItemNo_keep(pockets_p[i]) == TRUE &&
            aQMgr_check_item_cond(cond, mPr_ITEM_COND_NORMAL, i) == TRUE) {
            count++;
        }
    }

    if (count > 0) {
        sel_idx = RANDOM(count);

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++, pockets_p++) {
            if (!aMR_CorrespondFurniture(*pockets_p, present_ftr) &&
                mNpc_CheckFtrIsIslandNormalFtr(*pockets_p) == TRUE &&
                mNpc_CheckIslandNpcRoomFtrItemNo_keep(*pockets_p) == TRUE &&
                aQMgr_check_item_cond(cond, mPr_ITEM_COND_NORMAL, i) == TRUE) {
                if (sel_idx == 0) {
                    *item_p = *pockets_p;
                    ret_idx = i;
                    break;
                }

                sel_idx--;
            }
        }
    }

    return ret_idx;
}

static int aQMgr_get_cloth(mActor_name_t* item_p, mActor_name_t* pockets_p, u32 cond, mActor_name_t cancel_item) {
    int ret_idx = -1;
    int count = 0;
    int sel_idx;
    int i;

    *item_p = EMPTY_NO;
    for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
        if (ITEM_NAME_GET_TYPE(pockets_p[i]) == NAME_TYPE_ITEM1 &&
            ITEM_NAME_GET_CAT(pockets_p[i]) == ITEM1_CAT_CLOTH &&
            aQMgr_check_item_cond(cond, mPr_ITEM_COND_NORMAL, i) == TRUE &&
            cancel_item != pockets_p[i]) {
            count++;
        }
    }

    if (count > 0) {
        sel_idx = RANDOM(count);

        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++, pockets_p++) {
            if (ITEM_NAME_GET_TYPE(*pockets_p) == NAME_TYPE_ITEM1 &&
                ITEM_NAME_GET_CAT(*pockets_p) == ITEM1_CAT_CLOTH &&
                aQMgr_check_item_cond(cond, mPr_ITEM_COND_NORMAL, i) == TRUE &&
                *pockets_p != cancel_item) {
                if (sel_idx == 0) {
                    *item_p = *pockets_p;
                    ret_idx = i;
                    break;
                }

                sel_idx--;
            }
        }
    }

    return ret_idx;
}

typedef int (*aQMgr_SELECT_RND_ITEM_PROC)(mActor_name_t*);

enum {
    aQMgr_SEL_ITEM_MODE_RANDOM,
    aQMgr_SEL_ITEM_MODE_PITFALL,

    aQMgr_SEL_ITEM_MODE_NUM
};

static void aQMgr_order_decide_trade_common_item(aQMgr_SELECT_RND_ITEM_PROC sel_rnd_item_proc, Animal_c* animal, int* cat_table, int cat_table_cnt, int item_mode) {
    static mActor_name_t other_itemNo[3];
    mActor_name_t itemNo;
    int cat;
    int rnd;
    int i;

    l_normal_info.item_idx = (*sel_rnd_item_proc)(&itemNo);
    if (l_normal_info.item_idx >= 0) {
        mQst_SetItemNameStr(itemNo, mMsg_ITEM_STR0);
        l_normal_info.trade_items[0] = itemNo;
    }

    for (i = 0; i < cat_table_cnt; i++) {
        cat = *cat_table;
        if (cat == mSP_KIND_DIARY) {
            itemNo = mFI_GetOtherFruit();
        } else if (cat == mSP_KIND_CLOTH) {
            bzero(other_itemNo, sizeof(other_itemNo));
            other_itemNo[0] = l_normal_info.trade_items[0];
            other_itemNo[1] = l_normal_info.trade_items[1];
            other_itemNo[2] = Now_Private->cloth.item;
            mQst_GetGoods_common(&itemNo, &animal->id, cat, other_itemNo, 3, mSP_LISTTYPE_ABC);
        } else {
            mQst_GetGoods_common(&itemNo, &animal->id, cat, l_normal_info.trade_items, 2, mSP_LISTTYPE_ABC);
        }

        l_normal_info.trade_items[1 + i] = itemNo;
        mQst_SetItemNameStr(itemNo, mMsg_ITEM_STR1 + i);
        cat_table++;
    }

    if (item_mode == aQMgr_SEL_ITEM_MODE_RANDOM) {
        i = RANDOM(cat_table_cnt);
        itemNo = l_normal_info.trade_items[1 + i];
    } else {
        itemNo = ITM_PITFALL;
    }

    l_normal_info.trade_items[4] = itemNo;
    mQst_SetItemNameStr(itemNo, mMsg_ITEM_STR4);
}

static void aQMgr_order_decide_trade_common_pay(int min, int max, int round_tens) {
    l_normal_info.pay = aQMgr_get_rnd_no_cut_10(min, max, round_tens);
    aQMgr_set_number_free_str(l_normal_info.pay, mMsg_FREE_STR19);
}

static void aQMgr_order_decide_trade_common(aQMgr_SELECT_RND_ITEM_PROC sel_rnd_item_proc, Animal_c* animal, int* cat_table, int cat_table_cnt, int item_mode, int pay_min, int pay_max, int round_tens) {
    aQMgr_order_decide_trade_common_item(sel_rnd_item_proc, animal, cat_table, cat_table_cnt, item_mode);
    aQMgr_order_decide_trade_common_pay(pay_min, pay_max, round_tens);
}

static void aQMgr_trade_give_item(int trade_idx, int pockets_idx) {
    if (pockets_idx != -1) {
        mActor_name_t item = l_normal_info.trade_items[trade_idx];
        mActor_name_t present_ftr = mNpc_GetIslandPresentFtr();

        if (ITEM_IS_FTR(item)) {
            if (aMR_CorrespondFurniture(item, present_ftr) == TRUE && mNpc_GetIslandPresentFtrPersonalID() != NULL) {
                mPr_ClearPersonalID(mNpc_GetIslandPresentFtrPersonalID());
            } else {
                mNpc_EraseIslandFtr(item);
                mNpc_EraseIslandFtr_keep(item);
            }
        }

        mPr_SetPossessionItem(Now_Private, pockets_idx, item, mPr_ITEM_COND_NORMAL);
    }
}

static void aQMgr_trade_take_item(int pockets_idx) {
    if (pockets_idx != -1 && Now_Private->inventory.pockets[pockets_idx] == l_normal_info.trade_items[0]) {
        mPr_SetPossessionItem(Now_Private, pockets_idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);

        if (ITEM_IS_FTR(l_normal_info.trade_items[0])) {
            mNpc_SetIslandGetFtr(l_normal_info.trade_items[0]);
        }
    }
}

static void aQMgr_trade_take_money(void) {
    int money = Now_Private->inventory.wallet;
    
    money -= l_normal_info.pay;
    if (money < 0) {
        money = 0;
    }

    Now_Private->inventory.wallet = money;
}

static void aQMgr_trade_give_money(void) {
    int money;
    int pay;
    Private_c* priv;
    int idx;

    priv = Now_Private;
    pay = l_normal_info.pay;
    money = priv->inventory.wallet;
    money = pay + money;
    idx = l_normal_info.item_idx;

    if (money < 0) {
        money = 0;
    } else if (money > mPr_WALLET_MAX) {
        if (idx != -1) {
            mPr_SetPossessionItem(priv, idx, ITM_MONEY_30000, mPr_ITEM_COND_NORMAL);
            money -= 30000;
        }

        while (money > mPr_WALLET_MAX) {
            idx = mPr_GetPossessionItemIdx(priv, EMPTY_NO);
            if (idx != -1) {
                mPr_SetPossessionItem(priv, idx, ITM_MONEY_30000, mPr_ITEM_COND_NORMAL);
                money -= 30000;
            } else {
                money = mPr_WALLET_MAX;
                break;
            }
        }
    }

    Now_Private->inventory.wallet = money;
}

static void aQMgr_set_give_and_take_mode_GIVE(QUEST_MANAGER_ACTOR* manager, int trade_type) {
    int idx = l_normal_info.item_idx;
    u8 present = NowPrivate_GetItemCond(idx) & mPr_ITEM_COND_PRESENT;

    mPlib_request_main_give_type1(gamePT, l_normal_info.trade_items[0], aHOI_REQUEST_PUTAWAY, present, FALSE);
    manager->target.quest_item = l_normal_info.trade_items[trade_type];
    aQMgr_trade_take_item(idx);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_ITEM_WAIT_END;
    manager->talk_step = aQMgr_TALK_STEP_TO_WAIT_ORDER;
}

static void aQMgr_set_give_item_and_take_money_mode_GIVE(QUEST_MANAGER_ACTOR* manager) {
    mPlib_request_main_give_type1(gamePT, ITM_MONEY_30000, aHOI_REQUEST_PUTAWAY, FALSE, FALSE);
    manager->target.quest_item = ITM_MONEY_30000;
    aQMgr_trade_take_money();
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_ITEM_WAIT_END;
    manager->talk_step = aQMgr_TALK_STEP_TO_WAIT_ORDER;
}

static void aQMgr_set_give_money_and_take_item_mode_GIVE(QUEST_MANAGER_ACTOR* manager) {
    int idx = l_normal_info.item_idx;
    u8 present = NowPrivate_GetItemCond(idx) & mPr_ITEM_COND_PRESENT;

    mPlib_request_main_give_type1(gamePT, l_normal_info.trade_items[0], aHOI_REQUEST_PUTAWAY, present, FALSE);
    aQMgr_trade_take_item(idx);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_ITEM_WAIT_END;
    manager->talk_step = aQMgr_TALK_STEP_TO_WAIT_ORDER;
}

static void aQMgr_set_give_money_and_take_item_mode_TAKE(QUEST_MANAGER_ACTOR* manager) {
    manager->target.quest_item = ITM_MONEY_30000;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_ITEM);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_ITEM_PLAYER_WAIT;
    mMsg_SET_LOCKCONTINUE();
    aQMgr_trade_give_money();
    manager->talk_step = aQMgr_TALK_STEP_TO_WAIT_ORDER;
}

static void aQMgr_set_give_and_take_mode_TAKE(QUEST_MANAGER_ACTOR* manager, int trade_type, int idx) {
    manager->target.quest_item = l_normal_info.trade_items[trade_type];
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_ITEM);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_ITEM_PLAYER_WAIT;
    mMsg_SET_LOCKCONTINUE();
    aQMgr_trade_give_item(trade_type, idx);
    manager->talk_step = aQMgr_TALK_STEP_TO_WAIT_ORDER;
}

static void aQMgr_order_change_roof_color(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_order_c* order_p = &manager->demo_order;
    mHm_hs_c* home = NULL;
    u8 color = 0;

    if (order_p->value > 0 && order_p->value <= 16) {
        color = order_p->value - 1;
    }

    if (Common_Get(player_no) < PLAYER_NUM) {
        home = Save_GetPointer(homes[mHS_get_arrange_idx(Common_Get(player_no))]);
    }

    if (home != NULL) {
        home->outlook_pal = color;

        if ((Now_Private->state_flags & mPr_FLAG_UPDATE_OUTLOOK_PENDING) == 0) {
            home->next_outlook_pal = color;
        }
    }
}

static void aQMgr_order_change_gobi(QUEST_MANAGER_ACTOR* manager) {
    mMsg_SET_LOCKCONTINUE();
    mMsg_REQUEST_MAIN_DISAPPEAR_WAIT_TYPE2();
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_DISAPPEAR_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_OPEN_GOBI;
}

static void aQMgr_order_cancel_remove(QUEST_MANAGER_ACTOR* manager) {
    Save_Set(remove_animal_idx, 0xFF);
    mNpc_SetRemoveAnimalNo(&Save_Get(remove_animal_idx), Save_Get(animals), 0xFF);
}

typedef void (*aQMgr_CONTROL_ORDER_PROC)(QUEST_MANAGER_ACTOR*);

static void aQMgr_control_animal_info(QUEST_MANAGER_ACTOR* manager) {
    // @BUG - this should have the static qualifier
    aQMgr_CONTROL_ORDER_PROC control_order_proc[] = {
        &aQMgr_order_change_gobi,
        &aQMgr_order_cancel_remove,
    };

    int order = manager->demo_order.value;

    if (order <= 0 || order > aQMgr_ORDER_NUM) {
        order = aQMgr_ORDER_CANCEL_REMOVE + 1;
    }

    order--;
    (*control_order_proc[order])(manager);
}

static void aQMgr_order_decide_trade_1(Animal_c* animal) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, 100, 3000, TRUE);
}

static void aQMgr_order_decide_trade_2(Animal_c* animal) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, 1000, 5000, TRUE);
}

static void aQMgr_order_decide_trade_3(Animal_c* animal) {
    int money = Now_Private->inventory.wallet;

    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, money, money, FALSE);
}


static void aQMgr_order_decide_trade_4(Animal_c* animal) {
    int money = Now_Private->inventory.wallet;

    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, money / 2, money / 2, FALSE);
}

static void aQMgr_order_decide_trade_5(Animal_c* animal) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, 3000, 3000, FALSE);
}

static void aQMgr_order_decide_trade_6(Animal_c* animal) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, 1000, 1000, FALSE);
}

static void aQMgr_order_decide_trade_7(Animal_c* animal) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_item_rnd, animal, l_quest_category_1, ARRAY_COUNT(l_quest_category_1), aQMgr_SEL_ITEM_MODE_RANDOM, 100, 3000, TRUE);
}

static void aQMgr_order_decide_trade_8(Animal_c* animal) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_PITFALL, 100, 3000, TRUE);
}

static void aQMgr_order_decide_trade_9(Animal_c* animal) {
    int money = Now_Private->inventory.wallet;

    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_PITFALL, money, money, TRUE);
}

static void aQMgr_order_decide_trade_10(Animal_c* animal) {
    int money = Now_Private->inventory.wallet;

    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_PITFALL, money / 2, money / 2, TRUE);
}

static void aQMgr_order_decide_trade_11(Animal_c* animal) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_item_rnd, animal, l_quest_category_1, ARRAY_COUNT(l_quest_category_1), aQMgr_SEL_ITEM_MODE_PITFALL, 100, 3000, TRUE);
}

static void aQMgr_order_decide_trade_12(Animal_c* animal) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, 100, 500, TRUE);
}

static void aQMgr_order_decide_trade_13(Animal_c* animal) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, 1000, 2000, TRUE);
}

static void aQMgr_order_decide_trade_14(Animal_c* animal) {
    aQMgr_order_decide_trade_common_pay(3000, 5000, TRUE);
}

static void aQMgr_order_decide_trade_15(Animal_c* animal) {
    aQMgr_order_decide_trade_common_pay(2000, 2999, TRUE);
}

static void aQMgr_order_decide_trade_16(Animal_c* animal) {
    aQMgr_order_decide_trade_common_pay(1000, 1999, TRUE);
}

static void aQMgr_order_decide_trade_17(Animal_c* animal) {
    aQMgr_order_decide_trade_common_pay(100, 999, TRUE);
}

static void aQMgr_order_decide_trade_18(Animal_c* animal) {
    aQMgr_normal_info_c* info_p = &l_normal_info;
    Private_c* priv = Now_Private;
    mActor_name_t ftr;
    PersonalID_c* pid;

    l_normal_info.item_idx = aQMgr_get_best_ftr_idx(&info_p->trade_items[0], priv);
    if (l_normal_info.item_idx != -1 && ITEM_IS_FTR(info_p->trade_items[0])) {
        mQst_SetItemNameStr(info_p->trade_items[0], mMsg_ITEM_STR0);
    } else {
        info_p->item_idx = -1;
        info_p->trade_items[0] = EMPTY_NO;
    }

    ftr = mNpc_GetIslandPresentFtr();
    if (ftr != EMPTY_NO) {
        mQst_SetItemNameStr(ftr, mMsg_ITEM_STR1);
        info_p->trade_items[1] = ftr;
    }

    ftr = mNpc_GetRandomBestFtr();
    if (ftr != EMPTY_NO) {
        mQst_SetItemNameStr(ftr, mMsg_ITEM_STR2);
        info_p->trade_items[2] = ftr;
    }

    ftr = (mActor_name_t)mNpc_GetPlayerFtr(&priv->player_ID);
    info_p->trade_items[3] = ftr;
    if (ITEM_IS_FTR(ftr)) {
        mQst_SetItemNameStr(ftr, mMsg_ITEM_STR3);
    } else {
        info_p->trade_items[3] = EMPTY_NO;
    }

    pid = mNpc_GetIslandPresentFtrPersonalID();
    if (pid != NULL) {
        mMsg_SET_FREE_STR(mMsg_FREE_STR18, pid->player_name, PLAYER_NAME_LEN);
    }

    aQMgr_order_decide_trade_common_pay(100, 3000, TRUE);
}

static void aQMgr_order_decide_trade_19(Animal_c* animal) {
    aQMgr_normal_info_c* info_p = &l_normal_info;
    Private_c* priv = Now_Private;
    mActor_name_t ftr;
    Anmmem_c* memory;

    l_normal_info.item_idx = aQMgr_get_normal_ftr_idx(&info_p->trade_items[0], priv);
    if (l_normal_info.item_idx != -1 && ITEM_IS_FTR(info_p->trade_items[0])) {
        mQst_SetItemNameStr(info_p->trade_items[0], mMsg_ITEM_STR0);
    } else {
        info_p->item_idx = -1;
        info_p->trade_items[0] = EMPTY_NO;
    }

    memory = mNpc_GetOtherBestFtr(&priv->player_ID, &info_p->trade_items[1], EMPTY_NO);
    if (memory != NULL && ITEM_IS_FTR(info_p->trade_items[1])) {
        mQst_SetItemNameStr(info_p->trade_items[1], mMsg_ITEM_STR1);
    }

    ftr = mNpc_GetRandomBestFtr();
    if (ftr != EMPTY_NO) {
        mQst_SetItemNameStr(ftr, mMsg_ITEM_STR2);
        info_p->trade_items[2] = ftr;
    }

    ftr = (mActor_name_t)mNpc_GetPlayerFtr(&priv->player_ID);
    info_p->trade_items[3] = ftr;
    if (ITEM_IS_FTR(ftr)) {
        mQst_SetItemNameStr(ftr, mMsg_ITEM_STR3);
    } else {
        info_p->trade_items[3] = EMPTY_NO;
    }

    if (memory != NULL) {
        mMsg_SET_FREE_STR(mMsg_FREE_STR18, memory->memory_player_id.player_name, PLAYER_NAME_LEN);
    }

    aQMgr_order_decide_trade_common_pay(100, 3000, TRUE);
}

static void aQMgr_order_decide_trade_20(Animal_c* animal) {
    aQMgr_normal_info_c* info_p = &l_normal_info;
    Private_c* priv = Now_Private;
    mActor_name_t ftr;

    l_normal_info.item_idx = aQMgr_get_cloth(&info_p->trade_items[0], priv->inventory.pockets, priv->inventory.item_conditions, animal->cloth);
    if (info_p->trade_items[0] != EMPTY_NO && info_p->item_idx != -1) {
        mQst_SetItemNameStr(info_p->trade_items[0], mMsg_ITEM_STR0);
    } else {
        info_p->trade_items[0] = EMPTY_NO;
        info_p->item_idx = -1;
    }

    ftr = mNpc_GetRandomBestFtr();
    if (ftr != EMPTY_NO) {
        mQst_SetItemNameStr(ftr, mMsg_ITEM_STR2);
        info_p->trade_items[2] = ftr;
    }

    ftr = (mActor_name_t)mNpc_GetPlayerFtr(&priv->player_ID);
    info_p->trade_items[3] = ftr;
    if (ITEM_IS_FTR(ftr)) {
        mQst_SetItemNameStr(ftr, mMsg_ITEM_STR3);
    } else {
        info_p->trade_items[3] = EMPTY_NO;
    }

    aQMgr_order_decide_trade_common_pay(100, 3000, TRUE);
}

static void aQMgr_order_decide_trade_21(Animal_c* animal) {
    aQMgr_normal_info_c* info_p = &l_normal_info;
    Private_c* priv = Now_Private;
    mActor_name_t ftr;
    Anmmem_c* memory;

    l_normal_info.item_idx = aQMgr_get_best_ftr_idx(&info_p->trade_items[0], priv);
    if (l_normal_info.item_idx != -1 && ITEM_IS_FTR(info_p->trade_items[0])) {
        mQst_SetItemNameStr(info_p->trade_items[0], mMsg_ITEM_STR0);
    } else {
        info_p->item_idx = -1;
        info_p->trade_items[0] = EMPTY_NO;
    }

    memory = mNpc_GetOtherBestFtr(&priv->player_ID, &info_p->trade_items[1], EMPTY_NO);
    if (memory != NULL && ITEM_IS_FTR(info_p->trade_items[1]) && info_p->trade_items[1] != EMPTY_NO) {
        mQst_SetItemNameStr(info_p->trade_items[1], mMsg_ITEM_STR1);
    }

    ftr = (mActor_name_t)mNpc_GetPlayerBestFtr(&priv->player_ID, EMPTY_NO);
    info_p->trade_items[2] = ftr;
    if (ITEM_IS_FTR(ftr)) {
        mQst_SetItemNameStr(ftr, mMsg_ITEM_STR2);
    } else {
        info_p->trade_items[2] = EMPTY_NO;
    }

    ftr = (mActor_name_t)mNpc_GetPlayerFtr(&priv->player_ID);
    info_p->trade_items[3] = ftr;
    if (ITEM_IS_FTR(ftr)) {
        mQst_SetItemNameStr(ftr, mMsg_ITEM_STR3);
    } else {
        info_p->trade_items[3] = EMPTY_NO;
    }

    if (memory != NULL) {
        mMsg_SET_FREE_STR(mMsg_FREE_STR18, memory->memory_player_id.player_name, PLAYER_NAME_LEN);
    }

    aQMgr_order_decide_trade_common_pay(100, 3000, TRUE);
}

typedef void (*aQMgr_DECIDE_TRADE_PROC)(Animal_c*);

static void aQMgr_order_decide_trade(QUEST_MANAGER_ACTOR* manager) {
    static aQMgr_DECIDE_TRADE_PROC decide_proc[] = {
        &aQMgr_order_decide_trade_1,
        &aQMgr_order_decide_trade_2,
        &aQMgr_order_decide_trade_3,
        &aQMgr_order_decide_trade_4,
        &aQMgr_order_decide_trade_5,
        &aQMgr_order_decide_trade_6,
        &aQMgr_order_decide_trade_7,
        &aQMgr_order_decide_trade_8,
        &aQMgr_order_decide_trade_9,
        &aQMgr_order_decide_trade_10,
        &aQMgr_order_decide_trade_11,
        &aQMgr_order_decide_trade_12,
        &aQMgr_order_decide_trade_13,
        &aQMgr_order_decide_trade_14,
        &aQMgr_order_decide_trade_15,
        &aQMgr_order_decide_trade_16,
        &aQMgr_order_decide_trade_17,
        &aQMgr_order_decide_trade_18,
        &aQMgr_order_decide_trade_19,
        &aQMgr_order_decide_trade_20,
        &aQMgr_order_decide_trade_21,
    };

    aQMgr_order_c* order_p = &manager->demo_order;
    Animal_c* animal = aQMgr_GET_CLIENT_ANIMAL(manager);
    int val = order_p->value;

    val--;
    (*decide_proc[val])(animal);
}

static void aQMgr_order_move_trade_no_term(QUEST_MANAGER_ACTOR* manager, int idx) {
    aQMgr_trade_give_item(idx, l_normal_info.free_idx);
    manager->target.quest_item = l_normal_info.trade_items[idx];
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_ITEM);
    mMsg_SET_LOCKCONTINUE();
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_ITEM_PLAYER_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_TO_WAIT_ORDER;
}

static void aQMgr_order_move_trade_1(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_order_move_trade_no_term(manager, 1);
}


static void aQMgr_order_move_trade_2(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_order_move_trade_no_term(manager, 2);
}

static void aQMgr_order_move_trade_3(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_order_move_trade_no_term(manager, 3);
}

static void aQMgr_order_move_trade_4(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_order_move_trade_no_term(manager, 4);
}

static void aQMgr_order_move_trade_5(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_and_take_mode_GIVE(manager, 1);
}

static void aQMgr_order_move_trade_6(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_and_take_mode_GIVE(manager, 2);
}

static void aQMgr_order_move_trade_7(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_and_take_mode_GIVE(manager, 3);
}

static void aQMgr_order_move_trade_8(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_and_take_mode_GIVE(manager, 4);
}

static void aQMgr_order_move_trade_9(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_item_and_take_money_mode_GIVE(manager);
}

static void aQMgr_order_move_trade_10(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_item_and_take_money_mode_GIVE(manager);
}

static void aQMgr_order_move_trade_11(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_item_and_take_money_mode_GIVE(manager);
}

static void aQMgr_order_move_trade_12(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_item_and_take_money_mode_GIVE(manager);
}

static void aQMgr_order_move_trade_13(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_money_and_take_item_mode_GIVE(manager);
}

static void aQMgr_order_move_trade_14(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_and_take_mode_TAKE(manager, 1, l_normal_info.item_idx);
}

static void aQMgr_order_move_trade_15(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_and_take_mode_TAKE(manager, 2, l_normal_info.item_idx);
}

static void aQMgr_order_move_trade_16(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_and_take_mode_TAKE(manager, 3, l_normal_info.item_idx);
}

static void aQMgr_order_move_trade_17(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_and_take_mode_TAKE(manager, 4, l_normal_info.item_idx);
}

static void aQMgr_order_move_trade_18(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_and_take_mode_TAKE(manager, 1, l_normal_info.free_idx);
}

static void aQMgr_order_move_trade_19(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_and_take_mode_TAKE(manager, 2, l_normal_info.free_idx);
}

static void aQMgr_order_move_trade_20(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_and_take_mode_TAKE(manager, 3, l_normal_info.free_idx);
}

static void aQMgr_order_move_trade_21(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_and_take_mode_TAKE(manager, 4, l_normal_info.free_idx);
}

static void aQMgr_order_move_trade_22(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_give_money_and_take_item_mode_TAKE(manager);
}

static void aQMgr_order_move_trade_23(QUEST_MANAGER_ACTOR* manager) {
    int item_idx = l_normal_info.item_idx;
    int present = NowPrivate_GetItemCond(item_idx) & mPr_ITEM_COND_PRESENT;

    mPlib_request_main_give_type1(gamePT, l_normal_info.trade_items[0], aHOI_REQUEST_PUTAWAY, present, FALSE);
    aQMgr_trade_take_item(item_idx);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_ITEM_WAIT_END;
    manager->talk_step = aQMgr_TALK_STEP_TO_WAIT_ORDER;
}

static void aQMgr_order_move_trade_24(QUEST_MANAGER_ACTOR* manager) {
    int present;
    int item_idx;
    int after_mode;
    mActor_name_t item;

    item = l_normal_info.trade_items[0];
    item_idx = l_normal_info.item_idx;
    present = NowPrivate_GetItemCond(item_idx) & mPr_ITEM_COND_PRESENT;
    after_mode = aHOI_REQUEST_PUTAWAY;
    if (ITEM_IS_CLOTH(item)) {
        Common_Set(npc_chg_cloth, item);
        after_mode = aHOI_REQUEST_CHANGE;
        mISL_SetNowPlayerAction(mISL_PLAYER_ACTION_TRADE_CLOTH);
    }

    mPlib_request_main_give_type1(gamePT, item, after_mode, present, FALSE);
    aQMgr_trade_take_item(item_idx);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_ITEM_WAIT_END;
    manager->talk_step = aQMgr_TALK_STEP_TO_WAIT_ORDER;
}

typedef void (*aQMgr_ORDER_MOVE_PROC)(QUEST_MANAGER_ACTOR*);

static void aQMgr_order_trade(QUEST_MANAGER_ACTOR* manager) {
    static aQMgr_ORDER_MOVE_PROC move_proc[] = {
        &aQMgr_order_move_trade_1,
        &aQMgr_order_move_trade_2,
        &aQMgr_order_move_trade_3,
        &aQMgr_order_move_trade_4,
        &aQMgr_order_move_trade_5,
        &aQMgr_order_move_trade_6,
        &aQMgr_order_move_trade_7,
        &aQMgr_order_move_trade_8,
        &aQMgr_order_move_trade_9,
        &aQMgr_order_move_trade_10,
        &aQMgr_order_move_trade_11,
        &aQMgr_order_move_trade_12,
        &aQMgr_order_move_trade_13,
        &aQMgr_order_move_trade_14,
        &aQMgr_order_move_trade_15,
        &aQMgr_order_move_trade_16,
        &aQMgr_order_move_trade_17,
        &aQMgr_order_move_trade_18,
        &aQMgr_order_move_trade_19,
        &aQMgr_order_move_trade_20,
        &aQMgr_order_move_trade_21,
        &aQMgr_order_move_trade_22,
        &aQMgr_order_move_trade_23,
        &aQMgr_order_move_trade_24,
    };

    aQMgr_order_c* order_p = &manager->demo_order;
    int val = order_p->value;

    if (val <= 0 || val > 24) {
        val = 1;
    }

    val--;
    (*move_proc[val])(manager);
}

static void aQMgr_order_show_letter(QUEST_MANAGER_ACTOR* manager) {
    mMsg_SET_LOCKCONTINUE();
    mMsg_REQUEST_MAIN_DISAPPEAR_WAIT_TYPE2();
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_DISAPPEAR_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_OPEN_LETTER;
}

static void aQMgr_order_write_letter(QUEST_MANAGER_ACTOR* manager) {
    mMsg_SET_LOCKCONTINUE();
    mMsg_REQUEST_MAIN_DISAPPEAR_WAIT_TYPE2();
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_DISAPPEAR_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_WRITE_LETTER;
}

static void aQMgr_order_fluctuation_friendship(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_order_c* order_p = &manager->demo_order;
    Anmmem_c* memory = *manager->memory;
    int fluctuation = order_p->value;

    if (fluctuation > 100) {
        fluctuation = 100 - fluctuation;
    }

    if (memory != NULL) {
        mNpc_AddFriendship(memory, fluctuation);
    }
}

static void aQMgr_order_play_memory_melody(QUEST_MANAGER_ACTOR* manager) {
    ACTOR* client = *manager->client;
    Anmmem_c* memory = l_normal_info.memory;
    static u8 melody[16];

    if (memory != NULL) {
        mMld_TransformMelodyData_u64_2_u8(melody, memory->saved_town_tune);
        mMld_ActorMakeThisMelody(melody, client);
    }
}

static void aQMgr_order_set_calendar(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_order_c* order_p = &manager->demo_order;
    int val = order_p->value;

    if (val == 1) {
        aQMgr_set_calendar_free_str(&lbRk_ToSeiyouReki, mMsg_FREE_STR11, mMsg_FREE_STR12, 8, 15);
        aQMgr_set_calendar_free_str(&lbRk_ToSeiyouReki, mMsg_FREE_STR13, mMsg_FREE_STR14, 9, 13);
        aQMgr_set_calendar_free_str(&lbRk_ToKyuuReki, mMsg_FREE_STR15, mMsg_FREE_STR16, Common_Get(time.rtc_time).month, Common_Get(time.rtc_time).day);
    }
}

static void aQMgr_order_input_birthday(QUEST_MANAGER_ACTOR* manager) {
    mMsg_SET_LOCKCONTINUE();
    mMsg_REQUEST_MAIN_DISAPPEAR_WAIT_TYPE2();
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_DISAPPEAR_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_OPEN_BIRTHDAY;
}

typedef void (*aQMgr_ORDER_INPUT_PROC)(QUEST_MANAGER_ACTOR*);

static void aQMgr_order_input_data(QUEST_MANAGER_ACTOR* manager) {
    static aQMgr_ORDER_INPUT_PROC input_proc[] = {
        &aQMgr_order_input_birthday,
        &aQMgr_order_write_letter,
    };

    aQMgr_order_c* order_p = &manager->demo_order;
    int val = order_p->value;

    if (val <= 0 || val > aQMgr_INPUT_NUM) {
        val = aQMgr_INPUT_BIRTHDAY + 1;
    }

    val--;
    (*input_proc[val])(manager);
}

static int aQMgr_set_random_string(u8* str, int item_str_no, int base_str, f32 str_num, int skip_idx) {
    int idx;

    idx = RANDOM(str_num);
    if (skip_idx >= 0 && idx == skip_idx) {
        idx++;
    }

    mString_Load_StringFromRom(str, 16, base_str + idx);
    mMsg_SET_ITEM_STR(item_str_no, str, 16);
    return idx;
}

static void aQMgr_order_set_string_1(u8* last_str_tbl) {
    static int base_str_no[] = { 0x6A1, 0x679, 0x334, 0x314, 0x414 };
    static f32 rand_max_table[] = { 40.0f, 40.0f, 32.0f, 32.0f, 32.0f };
    int last_str_no;
    int i;

    last_str_tbl += 2;
    for (i = 0; i < (aQMgr_LAST_STR_NUM - 2); i++) {
        if (*last_str_tbl < (u8)rand_max_table[i]) {
            last_str_no = aQMgr_set_random_string(l_aqmgr_str, i, base_str_no[i], rand_max_table[i] - 1.0f, *last_str_tbl);
        } else {
            last_str_no = aQMgr_set_random_string(l_aqmgr_str, i, base_str_no[i], rand_max_table[i], -1);
        }

        *last_str_tbl++ = last_str_no;
    }
}

static void aQMgr_set_random_number_item_str(u8* str, int item_str_no, u32 min, u32 max) {
    u32 idx = min + (u32)RANDOM_F(max - min);

    aQMgr_set_number_item_str(str, idx, item_str_no);
}

static void aQMgr_order_set_string_2(u8* last_str_tbl) {
    u8 str[16];
    int shop_level;

    aQMgr_set_random_number_item_str(l_aqmgr_str, mMsg_ITEM_STR0, 1, 10);
    aQMgr_set_random_number_item_str(l_aqmgr_str, mMsg_ITEM_STR1, 10, 99);
    aQMgr_set_random_number_item_str(l_aqmgr_str, mMsg_ITEM_STR2, 0, 9);
    shop_level = mSP_GetShopLevel();
    mString_Load_StringFromRom(str, sizeof(str), 0x454 + shop_level);
    mMsg_SET_ITEM_STR(mMsg_ITEM_STR3, str, sizeof(str));
    aQMgr_set_random_string(l_aqmgr_str, mMsg_ITEM_STR4, 0x434, 32.0f, -1);
}

static void aQMgr_order_set_string_3(u8* last_str_tbl) {
    static int base_str_no[] = { 0x464, 0x2F4, 0x4A0 };
    int i;

    for (i = 0; i < 3; i++) {
        aQMgr_set_random_string(l_aqmgr_str, i, base_str_no[i], 32.0f, -1);
    }
}

typedef struct month_day_s {
    u8 month;
    u8 day;
} aQMgr_month_day_c;

// clang-format off
static aQMgr_month_day_c constellation_table[] = {
    { lbRTC_JANUARY, 19 },
    { lbRTC_FEBRUARY, 18 },
    { lbRTC_MARCH, 20 },
    { lbRTC_APRIL, 19 },
    { lbRTC_MAY, 20 },
    { lbRTC_JUNE, 21 },
    { lbRTC_JULY, 22 },
    { lbRTC_AUGUST, 22 },
    { lbRTC_SEPTEMBER, 22 },
    { lbRTC_OCTOBER, 23 },
    { lbRTC_NOVEMBER, 21 },
    { lbRTC_DECEMBER, 21 },
};
// clang-format on

static void aQMgr_order_set_string_4(u8* last_str_tbl) {
    static int base_str_no[] = { 0x458, 0x494 };
    mPr_birthday_c* birthday_p = &Now_Private->birthday;
    aQMgr_month_day_c* const_p = constellation_table;
    int constellation;
    int i;
    int str_idx;
    u8 birthday_month = birthday_p->month;
    u8 birthday_day = birthday_p->day;

    for (i = 0; i < 2; i++) {
        if (*last_str_tbl < 12) {
            str_idx = aQMgr_set_random_string(l_aqmgr_str, i, base_str_no[i], 11.0f, *last_str_tbl);
        } else {
            str_idx = aQMgr_set_random_string(l_aqmgr_str, i, base_str_no[i], 12.0f, -1);
        }

        *last_str_tbl++ = str_idx;
    }

    constellation = 0;
    for (i = 0; i < 12; i++) {
        if (birthday_p->month < const_p->month || (birthday_p->month == const_p->month && birthday_p->day <= const_p->day)) {
            constellation = i;
            break;
        }

        const_p++;
    }

    constellation -= 3;
    if (constellation < 0) {
        constellation += 12;
    }

    mString_Load_StringFromRom(l_aqmgr_str, sizeof(l_aqmgr_str), 0x494 + constellation);
    mMsg_SET_ITEM_STR(mMsg_ITEM_STR2, l_aqmgr_str, sizeof(l_aqmgr_str));

    mem_clear(l_aqmgr_str, sizeof(l_aqmgr_str), CHAR_SPACE);
    if (birthday_month < lbRTC_JANUARY || birthday_month > lbRTC_DECEMBER) {
        birthday_month = lbRTC_JANUARY;
    }
    birthday_month--;
    mString_Load_StringFromRom(l_aqmgr_str, sizeof(l_aqmgr_str), mString_MONTH_START + birthday_month);
    mMsg_SET_ITEM_STR(mMsg_ITEM_STR3, l_aqmgr_str, sizeof(l_aqmgr_str));

    mem_clear(l_aqmgr_str, sizeof(l_aqmgr_str), CHAR_SPACE);
    if (birthday_day < 1 || birthday_day > 31) {
        birthday_day = 1;
    }
    birthday_day--;
    mString_Load_StringFromRom(l_aqmgr_str, sizeof(l_aqmgr_str), mString_DAY_START + birthday_day);
    mMsg_SET_ITEM_STR(mMsg_ITEM_STR4, l_aqmgr_str, sizeof(l_aqmgr_str));
}

typedef void (*aQMgr_SET_STRING_PROC)(u8*);

static void aQMgr_order_set_string(QUEST_MANAGER_ACTOR* manager) {
    static aQMgr_SET_STRING_PROC set_string_proc[] = {
        &aQMgr_order_set_string_1,
        &aQMgr_order_set_string_2,
        &aQMgr_order_set_string_3,
        &aQMgr_order_set_string_4,
    };
    int val = manager->demo_order.value;

    val--;
    (*set_string_proc[val])(manager->last_strings);
}

static int aQMgr_decide_normal_msg_no_island(QUEST_MANAGER_ACTOR* manager, int looks) {
    static int msg_table[] = { 0x3631, 0x3654, 0x36BC, 0x36DB, 0x367A, 0x369D };
    static int oldMsg = 0;

    int ret_msg;

    if (looks >= mNpc_LOOKS_NUM || looks < 0) {
        looks = 0;
    }

    ret_msg = msg_table[looks] + mQst_GetRandom(10);
    if (ret_msg == oldMsg) {
        ret_msg = msg_table[looks] + mQst_GetRandom(9);
        if (ret_msg == oldMsg) {
            ret_msg++;
        }
    }

    if (ret_msg != -1) {
        oldMsg = ret_msg;
    }

    return ret_msg;
}

static int aQMgr_check_trade_0(QUEST_MANAGER_ACTOR* manager, Private_c* priv, int* free_idx_p) {
    mActor_name_t* pockets_p = priv->inventory.pockets;
    mActor_name_t ftr = mNpc_GetIslandPresentFtr();
    u32 cond = priv->inventory.item_conditions;
    int ret = FALSE;
    int i;

    for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
        if (ITEM_IS_FTR(pockets_p[i]) && !aMR_CorrespondFurniture(pockets_p[i], ftr) &&
            mNpc_CheckFtrIsIslandBestFtr(pockets_p[i]) == TRUE && mNpc_CheckIslandNpcRoomFtrItemNo_keep(pockets_p[i]) == TRUE &&
            aQMgr_check_item_cond(cond, mPr_ITEM_COND_NORMAL, i) == TRUE) {
            ret = TRUE;
            break;
        }
    }

    return ret;
}

static int aQMgr_check_trade_1(QUEST_MANAGER_ACTOR* manager, Private_c* priv, int* free_idx_p) {
    mActor_name_t* pockets_p = priv->inventory.pockets;
    mActor_name_t ftr;
    u32 cond = priv->inventory.item_conditions;
    int ret = FALSE;
    int i;

    ftr = mNpc_GetIslandPresentFtr();
    for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
        if (ITEM_IS_FTR(pockets_p[i]) && !mSP_SearchItemCategoryPriority(pockets_p[i], mSP_KIND_FURNITURE, mSP_LISTTYPE_SPECIALPRESENT, NULL) &&
            !aMR_CorrespondFurniture(pockets_p[i], ftr) && mNpc_CheckFtrIsIslandNormalFtr(pockets_p[i]) == TRUE &&
            mNpc_CheckIslandNpcRoomFtrItemNo_keep(pockets_p[i]) == TRUE && aQMgr_check_item_cond(cond, mPr_ITEM_COND_NORMAL, i) == TRUE) {
            ret = TRUE;
            break;
        }
    }

    return ret;
}

static int aQMgr_check_trade_2(QUEST_MANAGER_ACTOR* manager, Private_c* priv, int* free_idx_p) {
    Anmmem_c* memory = Save_Get(island).animal.memories;
    PersonalID_c* pid;
    int free_idx;
    int ret = FALSE;

    if (memory != NULL && mNpc_CheckIslandPresentFtrIs() == TRUE) {
        free_idx = mPr_GetPossessionItemIdx(priv, EMPTY_NO);
        pid = mNpc_GetIslandPresentFtrPersonalID();

        if (free_idx != -1 && priv->inventory.wallet > 3000 && pid != NULL &&
            !mPr_CheckCmpPersonalID(&priv->player_ID, pid) &&
            mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM) != -1) {
            *free_idx_p = free_idx;
            ret = TRUE;
        }
    }

    return ret;
}

static int aQMgr_check_trade_3(QUEST_MANAGER_ACTOR* manager, Private_c* priv, int* free_idx_p) {
    PersonalID_c* pid;
    Anmmem_c* memory = Save_Get(island).animal.memories;
    int free_idx;
    int ret = FALSE;

    if (memory != NULL && mNpc_CheckIslandPresentFtrIs() == TRUE) {
        free_idx = mPr_GetPossessionItemIdx(priv, EMPTY_NO);
        pid = mNpc_GetIslandPresentFtrPersonalID();

        if (free_idx != -1 && pid != NULL &&
            !mPr_CheckCmpPersonalID(&priv->player_ID, pid) &&
            mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM) != -1) {
            *free_idx_p = free_idx;
            ret = TRUE;
        }
    }

    return ret;
}

static int aQMgr_check_trade_4(QUEST_MANAGER_ACTOR* manager, Private_c* priv, int* free_idx_p) {
    PersonalID_c* pid;
    Anmmem_c* memory = Save_Get(island).animal.memories;
    int free_idx;
    int ret = FALSE;

    if (memory != NULL && mNpc_CheckIslandPresentFtrIs() == TRUE) {
        free_idx = mPr_GetPossessionItemIdx(priv, EMPTY_NO);
        pid = mNpc_GetIslandPresentFtrPersonalID();

        if (free_idx != -1 && pid != NULL &&
            mPr_CheckCmpPersonalID(&priv->player_ID, pid) == TRUE &&
            mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM) != -1) {
            *free_idx_p = free_idx;
            ret = TRUE;
        }
    }

    return ret;
}

static int aQMgr_check_trade_5(QUEST_MANAGER_ACTOR* manager, Private_c* priv, int* free_idx_p) {
    mActor_name_t present_ftr = mNpc_GetIslandPresentFtr();
    int ret = FALSE;
    mActor_name_t best_ftr = mNpc_GetRandomBestFtr();

    if (best_ftr != EMPTY_NO && ITEM_IS_FTR(best_ftr) && !aMR_CorrespondFurniture(present_ftr, best_ftr)) {
        ret = TRUE;
    }

    return ret;
}

static int aQMgr_check_trade_6(QUEST_MANAGER_ACTOR* manager, Private_c* priv, int* free_idx_p) {
    int ret = FALSE;
    mActor_name_t other_best_ftr = EMPTY_NO;
    mActor_name_t present_ftr = mNpc_GetIslandPresentFtr();
    Anmmem_c* mem = mNpc_GetOtherBestFtr(&priv->player_ID, &other_best_ftr, present_ftr);

    if (mem != NULL) {
        ret = TRUE;
    }

    return ret;
}

static int aQMgr_check_trade_7(QUEST_MANAGER_ACTOR* manager, Private_c* priv, int* free_idx_p) {
    Anmmem_c* memory = Save_Get(island).animal.memories;
    int ret = FALSE;
    mActor_name_t present_ftr = mNpc_GetIslandPresentFtr();
    mActor_name_t best_ftr = mNpc_GetPlayerBestFtr(&priv->player_ID, present_ftr);

    if (best_ftr != EMPTY_NO && ITEM_IS_FTR(best_ftr) && memory != NULL && mNpc_GetAnimalMemoryIdx(&priv->player_ID, memory, ANIMAL_MEMORY_NUM) != -1) {
        ret = TRUE;
    }

    return ret;
}

static int aQMgr_check_trade_8(QUEST_MANAGER_ACTOR* manager, Private_c* priv, int* free_idx_p) {
    mActor_name_t* pockets_p = priv->inventory.pockets;
    u32 cond = priv->inventory.item_conditions;
    int ret = FALSE;
    int i;

    for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
        if (ITEM_NAME_GET_TYPE(pockets_p[i]) == NAME_TYPE_ITEM1 && ITEM_NAME_GET_CAT(pockets_p[i]) == ITEM1_CAT_CLOTH &&
            aQMgr_check_item_cond(cond, mPr_ITEM_COND_NORMAL, i) == TRUE && Save_Get(island).animal.cloth != pockets_p[i]) {
            ret = TRUE;
        }
    }

    return ret;
}

typedef int (*aQMgr_CHECK_TRADE_PROC)(QUEST_MANAGER_ACTOR*, Private_c*, int*);

static int aQMgr_decide_ftr_msg_no(QUEST_MANAGER_ACTOR* manager, int looks) {
    static aQMgr_CHECK_TRADE_PROC check_proc[] = {
        &aQMgr_check_trade_0,
        &aQMgr_check_trade_1,
        &aQMgr_check_trade_2,
        &aQMgr_check_trade_3,
        &aQMgr_check_trade_4,
        &aQMgr_check_trade_5,
        &aQMgr_check_trade_6,
        &aQMgr_check_trade_7,
        &aQMgr_check_trade_8,
    };
    static int msg_table[] = { 0x35E0, 0x35FB, 0x382F, 0x3844, 0x3616, 0x381A };
    int check_idx;
    int check_ret;
    int ret_msg = -1;

    if (Now_Private != NULL) {
        if (!mNpc_GetIslandCheckFtrMsg()) {
            check_idx = 0;
            mNpc_SetIslandCheckFtrMsg(TRUE);
        } else {
            check_idx = RANDOM(5);
        }

        check_ret = (*check_proc[check_idx])(manager, Now_Private, &l_normal_info.free_idx);
        if (!check_ret) {
            check_idx = 5 + RANDOM(4);
            check_ret = (*check_proc[check_idx])(manager, Now_Private, &l_normal_info.free_idx);

            if (check_ret == TRUE && check_idx == 5) {
                if (aQMgr_check_trade_0(manager, Now_Private, &l_normal_info.free_idx) == TRUE) {
                    check_idx = 0;
                }

                check_ret = TRUE;
            }
        }
    }

    // @BUG - they check for Now_Private being NULL but never initialize this,
    // so there's techincally a chance that this is undefined even though
    // it should be impossible to happen
    if (check_ret == TRUE) {
        ret_msg = msg_table[looks] + check_idx;
    }

    return ret_msg;
}

static int aQMgr_decide_player_msg_no(QUEST_MANAGER_ACTOR* manager, int looks) {
    static int msg_table[] = { 0x3937, 0x3974, 0x37BA, 0x378A, 0x39B1, 0x37EA };
    int ret_msg = -1;
    int action_type = RANDOM(mISL_PLAYER_ACTION_NUM);
    int i;

    for (i = 0; i < 3; i++) {
        if (mISL_CheckNowPlayerAction(1 << action_type) == TRUE) {
            ret_msg = msg_table[looks] + action_type;
            break;
        }

        action_type++;
        if (action_type >= mISL_PLAYER_ACTION_NUM) {
            action_type = 0;
        }
    }

    return ret_msg;
}

static Anmmem_c* aQMgr_get_other_memory(Anmmem_c* memory, int cnt, PersonalID_c* pid, int needs_letter) {
    int j;
    int mem_cnt;
    Anmmem_c* ret_mem = NULL;
    int i;
    int sel_idx;

    ret_mem = NULL;
    mem_cnt = 0;

    for (i = 0; i < cnt; i++) {
        if (!mNpc_CheckFreeAnimalMemory(&memory[i]) && mPr_CheckCmpPersonalID(pid, &memory[i].memory_player_id) != TRUE && (!needs_letter || memory[i].letter_info.exists == TRUE)) {
            mem_cnt++;
        }
    }

    if (mem_cnt > 0) {
        sel_idx = RANDOM(mem_cnt);

        for (j = 0; j < cnt; j++) {
            if (!mNpc_CheckFreeAnimalMemory(&memory[j]) && !mPr_CheckCmpPersonalID(pid, &memory[j].memory_player_id) && (!needs_letter || memory[j].letter_info.exists == TRUE)) {
                if (sel_idx == 0) {
                    ret_mem = &memory[j];
                    break;
                }

                sel_idx--;
            }
        }
    }

    return ret_mem;
}

static int aQMgr_decide_other_player_msg_no(QUEST_MANAGER_ACTOR* manager, int looks) {
    static int msg_table[] = { 0x3880, 0x38BD, 0x372A, 0x375A, 0x38FA, 0x36FA };
    Anmmem_c* memory = NULL;
    int ret_msg = -1;
    int action_type;
    int i;

    if (Now_Private != NULL) {
        memory = aQMgr_get_other_memory(Save_Get(island).animal.memories, ANIMAL_MEMORY_NUM, &Now_Private->player_ID, FALSE);
    }

    if (memory != NULL) {
        action_type = RANDOM(mISL_PLAYER_ACTION_NUM);
        for (i = 0; i < 3; i++) {
            if (mISL_CheckPlayerAction(&memory->memory_player_id, 1 << action_type) == TRUE) {
                ret_msg = msg_table[looks] + action_type;
                mMsg_SET_FREE_STR(mMsg_FREE_STR0, memory->memory_player_id.player_name, PLAYER_NAME_LEN);
                mMsg_SET_FREE_STR(mMsg_FREE_STR1, memory->memory_player_id.land_name, LAND_NAME_SIZE);
                break;
            }

            action_type++;
            if (action_type >= mISL_PLAYER_ACTION_NUM) {
                action_type = 0;
            }
        }
    }

    return ret_msg;
}

static int aQMgr_decide_mail_msg_no(QUEST_MANAGER_ACTOR* manager, int looks) {
    static int msg_table[] = { 0x35BF, 0x35CA, 0x3866, 0x3873, 0x35D5, 0x3859 };
    Anmmem_c* memory = *manager->memory;
    int ret_msg = -1;
    int action_type;
    int i;

    if (memory != NULL) {
        switch (RANDOM(3)) {
            case 0:
                if (!mNpc_GetIslandGetLetter()) {
                    l_normal_info.memory = memory;
                    l_normal_info.mail = &memory->letter;
                    ret_msg = msg_table[looks];
                }
                break;
            case 1:
                if (!mNpc_GetIslandGetLetter() && memory->letter_info.exists == TRUE) {
                    l_normal_info.memory = memory;
                    l_normal_info.mail = &memory->letter;
                    ret_msg = msg_table[looks] + 1;
                    mNpc_SetIslandGetLetter(TRUE);
                }
                break;
            case 2:
                if (Now_Private != NULL) {
                    Anmmem_c* mem = aQMgr_get_other_memory(Save_Get(island).animal.memories, ANIMAL_MEMORY_NUM, &Now_Private->player_ID, TRUE);

                    if (mem != NULL && mem->letter_info.exists == TRUE) {
                        l_normal_info.memory = mem;
                        l_normal_info.mail = &mem->letter;
                        ret_msg = msg_table[looks] + 2;
                    }
                }
                break;
        }

        if (l_normal_info.memory != NULL) {
            mMsg_SET_FREE_STR(mMsg_FREE_STR0, l_normal_info.memory->memory_player_id.player_name, PLAYER_NAME_LEN);
            mMsg_SET_FREE_STR(mMsg_FREE_STR1, l_normal_info.memory->memory_player_id.land_name, LAND_NAME_SIZE);
        }
    }

    return ret_msg;
}

typedef int (*aQMgr_GET_MSG_PROC)(QUEST_MANAGER_ACTOR*, int);

static void aQMgr_talk_island_select_talk(QUEST_MANAGER_ACTOR* manager) {
    static aQMgr_GET_MSG_PROC get_msg_proc[aQMgr_DECIDE_MSG_NUM] = {
        &aQMgr_decide_ftr_msg_no,
        &aQMgr_decide_player_msg_no,
        &aQMgr_decide_other_player_msg_no,
        &aQMgr_decide_mail_msg_no,
    };
    static int prob_table[aQMgr_DECIDE_MSG_NUM] = { 10, 50, 85, 100 };

    int sel_idx;
    ACTOR* client = *manager->client;
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal;
    int msg_no = -1;
    int looks;
    int sel_percent;
    int i;

    sel_idx = aQMgr_DECIDE_MSG_FTR;
    looks = mNpc_LOOKS_GIRL;
    manager->mail_memory = NULL;
    mMsg_UNSET_LOCKCONTINUE();
    aQMgr_init_normal_info(&l_normal_info);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_DEMO_ORDER_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_DEMO_ORDER;
    aQMgr_normal_set_free_str(manager);
    
    if (animal != NULL) {
        looks = animal->id.looks;
    }

    if (!mNpc_GetIslandCheckFtrMsg()) {
        msg_no = aQMgr_decide_ftr_msg_no(manager, looks);
        sel_idx = aQMgr_DECIDE_MSG_FTR;
    }

    if (msg_no == -1) {
        sel_percent = RANDOM(100);
        if (sel_percent >= 100) {
            sel_percent = 99;
        }

        for (i = 0; i < aQMgr_DECIDE_MSG_NUM; i++) {
            if (sel_percent < prob_table[i]) {
                sel_idx = i;
                break;
            }
        }

        msg_no = (*get_msg_proc[sel_idx])(manager, looks);
    }

    if (msg_no == -1) {
        if (sel_idx == aQMgr_DECIDE_MSG_PLAYER || sel_idx == aQMgr_DECIDE_MSG_OTHER_PLAYER) {
            msg_no = aQMgr_decide_ftr_msg_no(manager, looks);
        }

        if (msg_no == -1) {
            msg_no = aQMgr_decide_normal_msg_no_island(manager, looks);
        }
    }

    manager->msg_no = msg_no;
    mMsg_SET_CONTINUE_MSG_NUM(manager->msg_no);
    mMsg_SET_FORCENEXT();
}

typedef void (*aQMgr_DEMO_PROC)(QUEST_MANAGER_ACTOR*);

static void aQMgr_talk_island_demo_order(QUEST_MANAGER_ACTOR* manager) {
    static aQMgr_DEMO_PROC order_proc[] = {
        &aQMgr_order_change_roof_color,
        &aQMgr_control_animal_info,
        &aQMgr_order_decide_trade,
        &aQMgr_order_trade,
        &aQMgr_order_show_letter,
        &aQMgr_order_fluctuation_friendship,
        &aQMgr_order_play_memory_melody,
        &aQMgr_order_set_calendar,
        &aQMgr_order_input_data,
        &aQMgr_order_set_string,
    };

    aQMgr_order_c* order_p = &manager->demo_order;
    int type = order_p->type;

    (*order_proc[type])(manager);
}

static void aQMgr_talk_normal_open_letter(QUEST_MANAGER_ACTOR* manager) {
    Submenu* submenu = manager->submenu;
    ACTOR* client = *manager->client;
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal;
    Mail_c* mail = &manager->mail;

    mMl_clear_mail(mail);
    if (l_normal_info.memory != NULL) {
        mNpc_AnimalMail2Mail(mail, l_normal_info.mail, &l_normal_info.memory->memory_player_id, &animal->id);
        mail->content.mail_type = mMl_TYPE_MAIL;
    } else {
        mNpc_AnimalMail2Mail(mail, l_normal_info.mail, NULL, &animal->id);
        mail->content.mail_type = mMl_TYPE_MAIL;
        mem_clear(mail->header.sender.personalID.player_name, PLAYER_NAME_LEN, CHAR_SPACE);
    }

    mSM_open_submenu_new(submenu, mSM_OVL_BOARD, mSM_BD_OPEN_READ_ISLAND, 0, mail);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_HAND_ITEM_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_OPEN_MSG;
    mMsg_SET_LOCKCONTINUE();
}

static u8 l_aqmgr_sakubunn[4] = "NOTE";

static void aQMgr_talk_normal_open_letter_to_write(QUEST_MANAGER_ACTOR* manager) {
    Submenu* submenu = manager->submenu;
    ACTOR* client = *manager->client;
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal;
    Mail_c* mail = &manager->mail;
    Private_c* priv = Now_Private;
    mActor_name_t stationery;
    int len;

    mSP_SelectRandomItem_New(NULL, &stationery, 1, NULL, 0, mSP_KIND_PAPER, mSP_LISTTYPE_ABC, FALSE);
    mMl_clear_mail(mail);
    manager->mail_memory = l_normal_info.memory;
    mail->content.paper_type = PAPER2TYPE(stationery - ITM_PAPER_START);
    mPr_CopyPersonalID(&mail->header.sender.personalID, &priv->player_ID);
    mail->header.sender.type = mMl_NAME_TYPE_PLAYER;
    len = mMsg_Get_Length_String(priv->player_ID.player_name, PLAYER_NAME_LEN);
    bcopy(priv->player_ID.player_name, mail->content.footer, len);
    bcopy(l_aqmgr_sakubunn, mail->content.header, sizeof(l_aqmgr_sakubunn));
    mNpc_SetIslandGetLetter(TRUE);
    mMl_set_mail_name_npcinfo(&mail->header.recipient, &animal->id);
    mail->content.header_back_start = 0;
    mail->content.font = mMl_FONT_RECV;
    mail->content.mail_type = mMl_TYPE_MAIL;
    mSM_open_submenu_new(submenu, mSM_OVL_BOARD, mSM_BD_OPEN_WRITE_ISLAND, -1, mail);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_HAND_ITEM_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_OPEN_MSG;
    mMsg_SET_LOCKCONTINUE();
}

static void aQMgr_talk_normal_open_birthday(QUEST_MANAGER_ACTOR* manager) {
    Submenu* submenu = manager->submenu;

    mSM_open_submenu(submenu, mSM_OVL_BIRTHDAY, 0, 0);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_HAND_ITEM_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_OPEN_MSG;
}

static void aQMgr_talk_normal_open_gobi(QUEST_MANAGER_ACTOR* manager) {
    Submenu* submenu = manager->submenu;
    ACTOR* client = *manager->client;
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal;

    mSM_open_submenu_new(submenu, mSM_OVL_LEDIT, mLE_TYPE_EPHRASE, 0, animal->catchphrase);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_HAND_ITEM_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_OPEN_MSG;
}

static void aQMgr_talk_normal_open_msg(QUEST_MANAGER_ACTOR* manager) {
    mMsg_UNSET_LOCKCONTINUE();
    mMsg_SET_FORCENEXT();
    mMsg_REQUEST_MAIN_APPEAR_WAIT_TYPE1();
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_DEMO_ORDER_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_DEMO_ORDER;
}

static void aQMgr_talk_normal_give_item(QUEST_MANAGER_ACTOR* manager) {
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_ITEM);
    mMsg_SET_LOCKCONTINUE();
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_ITEM_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_TO_WAIT_ORDER;
}

static void aQMgr_talk_normal_to_wait_order(QUEST_MANAGER_ACTOR* manager) {
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_DEMO_ORDER_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_DEMO_ORDER;
}

extern void aQMgr_talk_island_init(QUEST_MANAGER_ACTOR* manager) {
    static aQMgr_TALK_INIT_PROC talk_proc[] = {
        &aQMgr_talk_island_select_talk,
        &aQMgr_talk_island_demo_order,
        &aQMgr_talk_normal_open_letter,
        &aQMgr_talk_normal_open_msg,
        &aQMgr_talk_normal_give_item,
        &aQMgr_talk_normal_to_wait_order,
        &aQMgr_talk_normal_open_birthday,
        &aQMgr_talk_normal_open_gobi,
        &aQMgr_talk_normal_open_letter_to_write,
    };

    int step = manager->talk_step;

    (*talk_proc[step])(manager);
    manager->talk_state = aQMgr_TALK_STATE_SUB;
}
