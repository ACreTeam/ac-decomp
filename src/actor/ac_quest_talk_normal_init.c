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
    aQMgr_TALK_STEP_KAMAKURA_HELLO,
    aQMgr_TALK_STEP_KAMAKRUA,
    aQMgr_TALK_STEP_SUMMERCAMP_HELLO,
    aQMgr_TALK_STEP_SUMMERCAMP,

    aQMgr_TALK_STEP_NUM
};

enum {
    aQMgr_MSG_KI_NORMAL,
    aQMgr_MSG_KI_WEATHER_TIME,
    aQMgr_MSG_KI_FREE_ITEM,
    aQMgr_MSG_KI_FTR,
    aQMgr_MSG_KI_FREE_ITEM_MONEY,

    aQMgr_MSG_KI_NUM
};

enum {
    aQMgr_MEMORY_OTHER_LAND_MEMORY,
    aQMgr_MEMORY_THIS_LAND_MEMORY_TALK_OTHER_LAND_PLAYER,
    aQMgr_MEMORY_THIS_LAND_MEMORY_TALK_THIS_LAND_PLAYER,

    aQMgr_MEMORY_NUM
};

enum {
    aQMgr_GET_MEMORY_MAIL_RND,
    aQMgr_GET_MEMORY_MAIL_BEST_FRIEND,
    aQMgr_GET_MEMORY_MAIL_MORE_FRIEND,
    aQMgr_GET_MEMORY_MAIL_OVER_FRIENDSHIP,
    aQMgr_GET_MEMORY_MAIL_LESS_FRIENDSHIP,
    aQMgr_GET_MEMORY_MAIL_SECRET,

    aQMgr_GET_MEMORY_NUM
};

enum {
    aQMgr_DECIDE_MSG_NORMAL_3_NORMAL,
    aQMgr_DECIDE_MSG_NORMAL_3_WEATHER_TIME,
    aQMgr_DECIDE_MSG_NORMAL_3_WEATHER,
    aQMgr_DECIDE_MSG_NORMAL_3_SEASON,

    aQMgr_DECIDE_MSG_NORMAL_3_NUM
};

enum {
    aQMgr_DECIDE_MSG_TRADE_FREE_ITEM,
    aQMgr_DECIDE_MSG_TRADE_FTR,
    aQMgr_DECIDE_MSG_TRADE_ITEM,
    aQMgr_DECIDE_MSG_TRADE_FREE_ITEM_MONEY,

    aQMgr_DECIDE_MSG_TRADE_NUM
};

enum {
    aQMgr_DECIDE_MSG_NORMAL_2_LETTER,
    aQMgr_DECIDE_MSG_NORMAL_2_NORMAL_3_MSG_NO,
    aQMgr_DECIDE_MSG_NORMAL_2_TRADE,
    aQMgr_DECIDE_MSG_NORMAL_2_MEMORY,

    aQMgr_DECIDE_MSG_NORMAL_2_NUM
};

enum {
    aQMgr_DECIDE_MSG_EV_SPECIAL_EV,
    aQMgr_DECIDE_MSG_EV_CALENDAR_EV,

    aQMgr_DECIDE_MSG_EV_NUM
};

enum {
    aQMgr_DECIDE_MSG_GAME_MSG_GAME_HINT,
    aQMgr_DECIDE_MSG_GAME_MSG_GAME_EV,

    aQMgr_DECIDE_MSG_GAME_MSG_NUM
};

enum {
    aQMgr_DECIDE_MSG_NORMAL_MSG_NORMAL_2_MSG_NO,
    aQMgr_DECIDE_MSG_NORMAL_MSG_GAME_MSG_NO,

    aQMgr_DECIDE_MSG_NORMAL_MSG_NUM
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

static aQMgr_normal_info_c l_normal_info;

static u8 l_ki_prob[aQMgr_MSG_KI_NUM] = { 40, 30, 10, 10, 10 };
static u8 l_normal_1_prob[] = { 70, 30 };
static u8 l_game_prob[aQMgr_DECIDE_MSG_GAME_MSG_NUM] = { 40, 60 };
static u8 l_ev_prob[aQMgr_DECIDE_MSG_EV_NUM] = { 50, 50 };
static u8 l_normal_2_prob[aQMgr_DECIDE_MSG_NORMAL_2_NUM] = { 15, 35, 35, 15 };
static u8 l_trade_prob[aQMgr_DECIDE_MSG_TRADE_NUM] = { 25, 25, 25, 25 };
static u8 l_normal_3_prob[aQMgr_DECIDE_MSG_NORMAL_3_NUM] = { 49, 17, 17, 17 };

static int l_ki_normal[6] = { 0x20C3, 0x2099, 0x25B0, 0x257E, 0x29F0, 0x0F8C };
static int l_ki_weather_time[6] = { 0x1FE8, 0x1DD0, 0x25DF, 0x2621, 0x2A6A, 0x0F60 };
static int l_ki_free_item[6] = { 0x1396, 0x1CBE, 0x2020, 0x202D, 0x2947, 0x0B36 };
static int l_ki_ftr[6] = { 0x13C7, 0x1CC9, 0x2049, 0x205D, 0x2974, 0x0B49 };
static int l_ki_free_item_money[6] = { 0x13DE, 0x1CF9, 0x2134, 0x203A, 0x295A, 0x0B5D };
static int l_ev_special[6] = { 0x11D9, 0x14E2, 0x1885, 0x211C, 0x273A, 0x0D61 };
static int l_ev_cal[6] = { 0x118E, 0x17ED, 0x27B2, 0x2806, 0x26EE, 0x0B87 };
static int l_game_hint[6] = { 0x11F1, 0x14FA, 0x2005, 0x2014, 0x2858, 0x0FAB };
static int l_remove_yes[6] = { 0x11FB, 0x1504, 0x1CD5, 0x1CDF, 0x2862, 0x0FA5 };
static int l_normal2_letter[6] = { 0x136C, 0x1BEB, 0x189D, 0x1C5F, 0x2919, 0x0A12 };
static int l_normal2_memory[6] = { 0x1386, 0x1C78, 0x18B6, 0x1CE9, 0x2933, 0x0D4D };
static int l_trade_free_item[6] = { 0x1205, 0x150C, 0x1772, 0x1C88, 0x2868, 0x0AD7 };
static int l_trade_ftr[6] = { 0x1311, 0x1839, 0x17CA, 0x1CA5, 0x28C9, 0x0ABC };
static int l_trade_item[6] = { 0x12FC, 0x1BA8, 0x1868, 0x2390, 0x2903, 0x0B03 };
static int l_trade_free_item_money[6] = { 0x134B, 0x1BBD, 0x184E, 0x236F, 0x28E4, 0x0B19 };
static int l_normal3_normal[6] = { 0x1526, 0x169A, 0x16BD, 0x16DF, 0x16F9, 0x0EE7 };
static int l_normal3_weather_time[6] = { 0x13A6, 0x1D08, 0x1F81, 0x1FA0, 0x2A9A, 0x0F00 };
static int l_normal3_weather[6] = { 0x1FC1, 0x1D29, 0x206C, 0x20AA, 0x2A38, 0x0F2C };
static int l_normal3_season[6] = { 0x1FD7, 0x1D41, 0x1F55, 0x1F6B, 0x2A13, 0x0F4A };

static int l_quest_category_0[] = { mSP_KIND_FURNITURE, mSP_KIND_CARPET, mSP_KIND_WALLPAPER };
static int l_quest_category_1[] = { mSP_KIND_CLOTH, mSP_KIND_PAPER, mSP_KIND_DIARY };

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

static int aQMgr_get_possession_ftr_cpt_wl(mActor_name_t cancel_item) {
    int idx =
        mPr_GetPossessionItemIdxFGTypeWithCond_cancel(Now_Private, NAME_TYPE_FTR0, mPr_ITEM_COND_NORMAL, cancel_item);

    if (idx == -1) {
        idx = mPr_GetPossessionItemIdxFGTypeWithCond_cancel(Now_Private, NAME_TYPE_FTR1, mPr_ITEM_COND_NORMAL,
                                                            cancel_item);

        if (idx == -1) {
            idx = mPr_GetPossessionItemIdxItem1CategoryWithCond_cancel(Now_Private, ITEM1_CAT_CARPET,
                                                                       mPr_ITEM_COND_NORMAL, cancel_item);

            if (idx == -1) {
                idx = mPr_GetPossessionItemIdxItem1CategoryWithCond_cancel(Now_Private, ITEM1_CAT_WALL,
                                                                           mPr_ITEM_COND_NORMAL, cancel_item);
            }
        }
    }

    return idx;
}

static int aQMgr_get_free_possession_idx(mActor_name_t cancel_item) {
    return mPr_GetPossessionItemIdx(Now_Private, EMPTY_NO);
}

static int aQMgr_get_free_possession_idx_check_money(mActor_name_t cancel_item) {
    int idx = aQMgr_get_free_possession_idx(cancel_item);

    if (idx != -1 && Now_Private->inventory.wallet < 3000) {
        idx = -1;
    }

    return idx;
}

static int aQMgr_get_possession_item(mActor_name_t cancel_item) {
    Private_c* priv = Now_Private;
    int idx = mPr_GetPossessionItemIdxKindWithCond(priv, ITM_INSECT_START, ITM_INSECT_END, mPr_ITEM_COND_NORMAL);

    if (idx == -1) {
        idx = mPr_GetPossessionItemIdxKindWithCond(priv, ITM_FISH_START, ITM_FISH_END, mPr_ITEM_COND_NORMAL);
    }

    return idx;
}

typedef int (*aQMgr_CHECK_ITEM_PROC)(mActor_name_t);

static int aQMgr_decide_msg_check_possession(aQMgr_CHECK_ITEM_PROC check_proc, int base_msg, int* item_idx,
                                             int msg_count, mActor_name_t cancel_item) {
    int msg = -1;
    int idx;

    if (check_proc != NULL) {
        idx = (*check_proc)(cancel_item);
        if (idx != -1) {
            msg = base_msg + mQst_GetRandom(msg_count);
            *item_idx = idx;
        }
    }

    return msg;
}

static int aQMgr_check_client_remove(QUEST_MANAGER_ACTOR* manager) {
    ACTOR* client = *manager->client;
    Animal_c* client_animal = ((NPC_ACTOR*)client)->npc_info.animal;
    Animal_c* animal = Save_Get(animals);
    int i;
    int res = FALSE;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckCmpAnimalPersonalID(&animal->id, &client_animal->id) == TRUE) {
            break;
        }

        animal++;
    }

    if (i == Save_Get(remove_animal_idx)) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_check_not_player_memory(PersonalID_c* pid, Anmmem_c* memory) {
    int res = FALSE;

    if (!mNpc_CheckFreeAnimalMemory(memory) && !mPr_CheckCmpPersonalID(pid, &memory->memory_player_id)) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_check_other_land_memory(Anmmem_c* memory, PersonalID_c* pid) {
    Anmlnd_c* land_p = &memory->memuni.land;

    if (aQMgr_check_not_player_memory(pid, memory) == TRUE && !mLd_NullCheckLandName(land_p->name) &&
        mLd_CheckId(land_p->id) == TRUE &&
        (!mLd_CheckCmpLandName(Save_Get(land_info).name, land_p->name) || Save_Get(land_info).id != land_p->id)) {
        return TRUE;
    }

    return FALSE;
}

static Anmmem_c* aQMgr_get_other_land_memory(PersonalID_c* pid, Anmmem_c* memory, int cnt) {
    Anmmem_c* mem_p = memory;
    Anmmem_c* ret_mem = NULL;
    int mem_cnt = 0;
    int idx;
    int i;

    for (i = 0; i < cnt; i++) {
        if (aQMgr_check_other_land_memory(memory, pid) == TRUE) {
            mem_cnt++;
        }

        memory++;
    }

    if (mem_cnt > 0) {
        memory = mem_p;
        idx = RANDOM(mem_cnt);

        for (i = 0; i < cnt; i++) {
            if (aQMgr_check_other_land_memory(memory, pid) == TRUE) {
                if (idx <= 0) {
                    ret_mem = memory;
                    break;
                }

                idx--;
            }

            memory++;
        }
    }

    return ret_mem;
}

static int aQMgr_check_this_land_memory_talk_other_land_player(Anmmem_c* memory, PersonalID_c* pid) {
    Anmlnd_c* land_p = &memory->memuni.land;

    if (aQMgr_check_not_player_memory(pid, memory) == TRUE && !mLd_NullCheckLandName(land_p->name) &&
        mLd_CheckId(land_p->id) == TRUE && mLd_CheckCmpLandName(Save_Get(land_info).name, land_p->name) == TRUE &&
        Save_Get(land_info).id == land_p->id &&
        (!mLd_CheckCmpLandName(Save_Get(land_info).name, memory->memory_player_id.land_name) ||
         Save_Get(land_info).id != memory->memory_player_id.land_id)) {
        return TRUE;
    }

    return FALSE;
}

static Anmmem_c* aQMgr_get_this_land_memory_talk_other_land_player(PersonalID_c* pid, Anmmem_c* memory, int cnt) {
    Anmmem_c* ret_mem = NULL;
    int idx;
    Anmmem_c* mem_p = memory;
    int mem_cnt = 0;
    int i;

    for (i = 0; i < cnt; i++) {
        if (aQMgr_check_this_land_memory_talk_other_land_player(memory, pid) == TRUE) {
            mem_cnt = 1;
            ret_mem = memory;
            break;
        }

        memory++;
    }

    if (mem_cnt > 0) {
        idx = RANDOM(mem_cnt);
        memory = mem_p;

        for (i = 0; i < cnt; i++) {
            if (aQMgr_check_this_land_memory_talk_other_land_player(memory, pid) == TRUE) {
                if (idx <= 0) {
                    ret_mem = memory;
                    break;
                }

                idx--;
            }

            memory++;
        }
    }

    return ret_mem;
}

static int aQMgr_check_this_land_memory_talk_this_land_player(Anmmem_c* memory, PersonalID_c* pid) {
    Anmlnd_c* land_p = &memory->memuni.land;

    if (aQMgr_check_not_player_memory(pid, memory) == TRUE && !mLd_NullCheckLandName(land_p->name) &&
        mLd_CheckId(land_p->id) == TRUE && mLd_CheckCmpLandName(Save_Get(land_info).name, land_p->name) == TRUE &&
        Save_Get(land_info).id == land_p->id &&
        (mLd_CheckCmpLandName(Save_Get(land_info).name, memory->memory_player_id.land_name) == TRUE &&
         Save_Get(land_info).id == memory->memory_player_id.land_id)) {
        return TRUE;
    }

    return FALSE;
}

static Anmmem_c* aQMgr_get_this_land_memory_talk_this_land_player(PersonalID_c* pid, Anmmem_c* memory, int cnt) {
    Anmmem_c* ret_mem = NULL;
    Anmmem_c* mem_p = memory;
    int idx;
    int mem_cnt = 0;
    int i;

    for (i = 0; i < cnt; i++) {
        if (aQMgr_check_this_land_memory_talk_this_land_player(memory, pid) == TRUE) {
            mem_cnt++;
        }

        memory++;
    }

    if (mem_cnt > 0) {
        idx = RANDOM(mem_cnt);
        memory = mem_p;

        for (i = 0; i < cnt; i++) {
            if (aQMgr_check_this_land_memory_talk_this_land_player(memory, pid) == TRUE) {
                if (idx <= 0) {
                    ret_mem = memory;
                    break;
                }

                idx--;
            }

            memory++;
        }
    }

    return ret_mem;
}

static Anmmem_c* aQMgr_get_memory_rnd(PersonalID_c* pid, Anmmem_c* memory, int cnt) {
    Anmmem_c* mem_p = memory;
    Anmmem_c* ret_mem = NULL;
    Anmlnd_c* land_p;
    int mem_cnt = 0;
    int idx;
    int i;

    for (i = 0; i < cnt; i++) {
        land_p = &memory->memuni.land;

        if (aQMgr_check_not_player_memory(pid, memory) == TRUE && !mLd_NullCheckLandName(land_p->name) && mLd_CheckId(land_p->id) == TRUE) {
            mem_cnt++;
        }

        memory++;
    }

    memory = mem_p;
    if (mem_cnt > 0) {
        idx = RANDOM(mem_cnt);

        for (i = 0; i < cnt; i++) {
            land_p = &memory->memuni.land;

            if (aQMgr_check_not_player_memory(pid, memory) == TRUE && !mLd_NullCheckLandName(land_p->name) && mLd_CheckId(land_p->id) == TRUE) {
                if (idx == 0) {
                    ret_mem = memory;
                    break;
                }

                idx--;
            }

            memory++;
        }
    }

    return ret_mem;
}

static Anmplmail_c* aQMgr_get_memory_mail_rnd(Anmmem_c** sel_mem_pp, Anmmem_c* memory, int cnt, Anmmem_c* player_mem) {
    PersonalID_c* pid = &player_mem->memory_player_id;
    Anmplmail_c* ret_mail = NULL;
    Anmmem_c* mem_p = memory;
    int mail_cnt = 0;
    int idx;
    int i;

    for (i = 0; i < cnt; i++) {
        if (!mNpc_CheckFreeAnimalMemory(memory) && !mPr_CheckCmpPersonalID(pid, &memory->memory_player_id) && memory->letter_info.exists == TRUE) {
            mail_cnt++;
        }

        memory++;
    }

    if (mail_cnt > 0) {
        memory = mem_p;
        idx = RANDOM(mail_cnt);

        for (i = 0; i < cnt; i++) {
            if (!mNpc_CheckFreeAnimalMemory(memory) && !mPr_CheckCmpPersonalID(pid, &memory->memory_player_id) && memory->letter_info.exists == TRUE) {
                if (idx <= 0) {
                    *sel_mem_pp = memory;
                    ret_mail = &memory->letter;
                    break;
                }

                idx--;
            }

            memory++;
        }
    }

    return ret_mail;
}

static Anmplmail_c* aQMgr_get_memory_mail_best_friend(Anmmem_c** sel_mem_pp, Anmmem_c* memory, int cnt, Anmmem_c* player_mem) {
    PersonalID_c* pid = &player_mem->memory_player_id;
    Anmplmail_c* ret_mail = NULL;
    int idx = mNpc_GetAnimalMemoryBestFriend(memory, cnt);

    if (idx != -1) {
        memory += idx;
        
        if (memory->letter_info.exists == TRUE && !mPr_CheckCmpPersonalID(pid, &memory->memory_player_id)) {
            ret_mail = &memory->letter;
            *sel_mem_pp = memory;
        }
    }

    return ret_mail;
}

static Anmplmail_c* aQMgr_get_memory_mail_more_friend(Anmmem_c** sel_mem_pp, Anmmem_c* memory, int cnt, Anmmem_c* player_mem) {
    Anmplmail_c* ret_mail = NULL;
    Anmmem_c* mem_p = memory;
    s8 friendship = 0;
    int mem_cnt = 0;
    int i;

    if (player_mem != NULL) {
        friendship = player_mem->friendship;
    }

    for (i = 0; i < cnt; i++) {
        if (!mNpc_CheckFreeAnimalMemory(memory) && memory->friendship > friendship && memory->letter_info.exists == TRUE) {
            mem_cnt++;
        }

        memory++;
    }

    if (mem_cnt > 0) {
        memory = mem_p;
        mem_cnt = RANDOM(mem_cnt);

        for (i = 0; i < cnt; i++) {
            if (!mNpc_CheckFreeAnimalMemory(memory) && memory->friendship > friendship && memory->letter_info.exists == TRUE) {
                if (mem_cnt <= 0) {
                    *sel_mem_pp = memory;
                    ret_mail = &memory->letter;
                    break;
                }

                mem_cnt--;
            }

            memory++;
        }
    }

    return ret_mail;
}

static Anmplmail_c* aQMgr_get_memory_mail_over_friendship(Anmmem_c** sel_mem_pp, Anmmem_c* memory, int cnt, Anmmem_c* player_mem) {
    PersonalID_c* pid = &player_mem->memory_player_id;
    Anmplmail_c* ret_mail = NULL;
    Anmmem_c* mem_p = memory;
    int mem_cnt = 0;
    int i;

    for (i = 0; i < cnt; i++) {
        if (!mNpc_CheckFreeAnimalMemory(memory) && !mPr_CheckCmpPersonalID(pid, &memory->memory_player_id) && memory->friendship >= 80 && memory->letter_info.exists == TRUE) {
            mem_cnt++;
        }

        memory++;
    }

    if (mem_cnt > 0) {
        memory = mem_p;
        mem_cnt = RANDOM(mem_cnt);

        for (i = 0; i < cnt; i++) {
            if (!mNpc_CheckFreeAnimalMemory(memory) && !mPr_CheckCmpPersonalID(pid, &memory->memory_player_id) && memory->friendship >= 80 && memory->letter_info.exists == TRUE) {
                if (mem_cnt == 0) {
                    *sel_mem_pp = memory;
                    ret_mail = &memory->letter;
                    break;
                }

                mem_cnt--;
            }

            memory++;
        }
    }

    return ret_mail;
}

static Anmplmail_c* aQMgr_get_memory_mail_less_friendship(Anmmem_c** sel_mem_pp, Anmmem_c* memory, int cnt, Anmmem_c* player_mem) {
    PersonalID_c* pid = &player_mem->memory_player_id;
    Anmplmail_c* ret_mail = NULL;
    Anmmem_c* mem_p = memory;
    int mem_cnt = 0;
    int idx;
    int mem_idx = -1;
    int i;

    for (i = 0; i < cnt; i++) {
        if (!mNpc_CheckFreeAnimalMemory(memory) && !mPr_CheckCmpPersonalID(pid, &memory->memory_player_id) && memory->friendship < 40 && memory->letter_info.exists == TRUE) {
            mem_cnt++;
        }

        memory++;
    }

    if (mem_cnt > 0) {
        memory = mem_p;
        mem_cnt = RANDOM(mem_cnt);

        for (i = 0; i < cnt; i++) {
            if (!mNpc_CheckFreeAnimalMemory(memory) && !mPr_CheckCmpPersonalID(pid, &memory->memory_player_id) && memory->friendship < 40 && memory->letter_info.exists == TRUE) {
                if (mem_cnt == 0) {
                    *sel_mem_pp = memory;
                    ret_mail = &memory->letter;
                    mem_idx = i;
                    break;
                }

                mem_cnt--;
            }

            memory++;
        }
    }

    if (ret_mail != NULL) {
        idx = mNpc_GetAnimalMemoryBestFriend(mem_p, cnt);

        if (idx != -1 && idx == mem_idx) {
            *sel_mem_pp = NULL;
            ret_mail = NULL;
        }
    }

    return ret_mail;
}

static Anmplmail_c* aQMgr_get_memory_mail_secret(Anmmem_c** sel_mem_pp, Anmmem_c* memory, int cnt, Anmmem_c* player_mem) {
    // clang-format off
    static Anmplmail_c animal_mail = {
        mMl_FONT_RECV,
        0,
        EMPTY_NO,
        0,
        { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        // ひみつの メール  じっけん -> "secret mail experiment"
        {
            0x1a, 0x1f, 0x11, 0x18, 0x20, 0xb2, 0x90, 0xb9, 0x20, 0x20, 0xed, 0xcc, 0x08, 0xc3, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
            0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        },
        { 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
        0,
        { 0, 0, 0 },
    };
    // clang-format on
    Anmplmail_c* ret_mail;
    int header_back_start;
    int mail_idx = RANDOM(15);

    mHandbill_Load_HandbillFromRom(animal_mail.header, &header_back_start, animal_mail.footer, animal_mail.body, 0x22 + mail_idx);
    animal_mail.header_back_start = header_back_start;
    animal_mail.font = mMl_FONT_RECV;
    animal_mail.paper_type = mNpc_GetPaperType();
    *sel_mem_pp = NULL;
    return &animal_mail;
}

static int aQMgr_get_msg_weather_time(QUEST_MANAGER_ACTOR* manager, int base_msg, int time_msg_cnt, int weather_msg_cnt, int msg_cnt) {
    int time_kind = (*manager->get_time_kind_proc)(Common_Get(time.rtc_time.hour));
    int weather = Common_Get(weather);
    int ret_msg;

    if (weather == mEnv_WEATHER_SAKURA) {
        weather = mEnv_WEATHER_CLEAR;
    }

    ret_msg = base_msg;
    ret_msg += time_kind * time_msg_cnt;
    ret_msg += weather * weather_msg_cnt;
    ret_msg += mQst_GetRandom(msg_cnt);
    return ret_msg;
}

static void aQMgr_normal_set_free_str(QUEST_MANAGER_ACTOR* manager) {
    ACTOR* client = *manager->client;
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal;
    AnmPersonalID_c* other_id;

    if (animal != NULL) {
        mQst_SetItemNameFreeStr(Save_Get(fruit), mMsg_FREE_STR10);
        mLd_SetFreeStrLandMuraName(animal->id.land_name, mMsg_FREE_STR11);
        mMsg_SET_FREE_STR(mMsg_FREE_STR12, animal->parent_name, LAND_NAME_SIZE);
        
        other_id = mNpc_GetOtherAnimalPersonalID(&animal->id, 1);
        if (other_id != NULL) {
            mNpc_GetNpcWorldNameAnm(l_aqmgr_str, other_id);
            mMsg_SET_FREE_STR(mMsg_FREE_STR13, l_aqmgr_str, ANIMAL_NAME_LEN);
        }
    }
}

static void aQMgr_set_free_str_memory(Anmmem_c* memory) {
    mLd_SetFreeStrLandMuraName(memory->memory_player_id.land_name, mMsg_FREE_STR14);
    mMsg_SET_FREE_STR(mMsg_FREE_STR15, memory->memory_player_id.player_name, PLAYER_NAME_LEN);
    mLd_SetFreeStrLandMuraName(memory->memuni.land.name, mMsg_FREE_STR16);
    aQMgr_set_number_free_str_add_nen(memory->last_speak_time.year, mMsg_FREE_STR17);
    aQMgr_set_number_free_str_add_gatu(memory->last_speak_time.month, mMsg_FREE_STR18);
    aQMgr_set_number_free_str_add_nichi(memory->last_speak_time.day, mMsg_FREE_STR19);
}

typedef int (*aQMgr_CALENDAR_CONV_PROC)(lbRTC_ymd_c*, lbRTC_ymd_c*);

static void aQMgr_set_calendar_free_str(aQMgr_CALENDAR_CONV_PROC conv_proc, int month_str_no, int day_str_no, u8 month, u8 day) {
    static u8 uru_tuki[10] = "leap month";
    lbRTC_ymd_c src_date;
    lbRTC_ymd_c dst_date;
    int ret;
    
    if (conv_proc != NULL) {
        src_date.year = (lbRTC_year_t)Common_Get(time.rtc_time.year);
        src_date.month = (lbRTC_month_t)month;
        src_date.day = (lbRTC_day_t)day;
        dst_date.year = (lbRTC_year_t)Common_Get(time.rtc_time.year);
        dst_date.month = (lbRTC_month_t)month;
        dst_date.day = (lbRTC_day_t)day;

        ret = (*conv_proc)(&dst_date, &src_date);
    }

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

static int aQMgr_get_possession_ftr_cpt_wl_rnd(mActor_name_t* item_p, mActor_name_t cancel_item) {
    mActor_name_t* pockets_p = Now_Private->inventory.pockets;
    u32 item_cnt;
    int sel_idx;
    int ret_idx = -1;
    int i;

    item_cnt = mPr_GetPossessionItemSumFGTypeWithCond_cancel(Now_Private, NAME_TYPE_FTR0, mPr_ITEM_COND_NORMAL, cancel_item);
    item_cnt += mPr_GetPossessionItemSumFGTypeWithCond_cancel(Now_Private, NAME_TYPE_FTR1, mPr_ITEM_COND_NORMAL, cancel_item);
    item_cnt += mPr_GetPossessionItemSumItemCategoryWithCond_cancel(Now_Private, ITEM1_CAT_CARPET, mPr_ITEM_COND_NORMAL, cancel_item);
    item_cnt += mPr_GetPossessionItemSumItemCategoryWithCond_cancel(Now_Private, ITEM1_CAT_WALL, mPr_ITEM_COND_NORMAL, cancel_item);

    if (item_cnt > 0 && item_cnt <= mPr_POCKETS_SLOT_COUNT) {
        sel_idx = RANDOM(item_cnt);
        for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
            if (mPr_GET_ITEM_COND(Now_Private->inventory.item_conditions, i) == mPr_ITEM_COND_NORMAL && *pockets_p != cancel_item && (ITEM_IS_FTR(*pockets_p) || (ITEM_NAME_GET_TYPE(*pockets_p) == NAME_TYPE_ITEM1 && (ITEM_NAME_GET_CAT(*pockets_p) == ITEM1_CAT_CARPET || ITEM_NAME_GET_CAT(*pockets_p) == ITEM1_CAT_WALL)))) {
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

static int aQMgr_get_possession_item_rnd(mActor_name_t* item_p, mActor_name_t cancel_item) {
    mActor_name_t* pockets_p = Now_Private->inventory.pockets;
    u32 item_cnt;
    int sel_idx;
    int ret_idx = -1;
    int i;

    item_cnt = mPr_GetPossessionItemSumKindWithCond(Now_Private, ITM_INSECT_START, ITM_INSECT_END, mPr_ITEM_COND_NORMAL);
    item_cnt += mPr_GetPossessionItemSumKindWithCond(Now_Private, ITM_FISH_START, ITM_FISH_END, mPr_ITEM_COND_NORMAL);

    if (item_cnt > 0 && item_cnt <= mPr_POCKETS_SLOT_COUNT) {
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

typedef int (*aQMgr_SELECT_RND_ITEM_PROC)(mActor_name_t*, mActor_name_t);

enum {
    aQMgr_SEL_ITEM_MODE_RANDOM,
    aQMgr_SEL_ITEM_MODE_PITFALL,

    aQMgr_SEL_ITEM_MODE_NUM
};

static void aQMgr_order_decide_trade_common_item(aQMgr_SELECT_RND_ITEM_PROC sel_rnd_item_proc, Animal_c* animal, int* cat_table, int cat_table_cnt, int item_mode, mActor_name_t cancel_item) {
    static mActor_name_t other_itemNo[3];
    mActor_name_t itemNo;
    int cat;
    int list = mSP_LISTTYPE_ABC;
    int rnd;
    int i;

    l_normal_info.item_idx = (*sel_rnd_item_proc)(&itemNo, cancel_item);
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
            mQst_GetGoods_common(&itemNo, &animal->id, cat, other_itemNo, 3, list);
        } else {
            if (cat == mSP_KIND_FURNITURE) {
                rnd = RANDOM(100);

                if (Save_Get(scene_no) == SCENE_KAMAKURA && rnd >= 90) {
                    // 10% chance for kamakura list item
                    list = mSP_LISTTYPE_KAMAKURA;
                } else if (Save_Get(scene_no) == SCENE_TENT && rnd >= 80) {
                    // 20% chance for summer camper list item
                    list = mSP_LISTTYPE_TENT;
                }
            }

            mQst_GetGoods_common(&itemNo, &animal->id, cat, l_normal_info.trade_items, 2, list);
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

static void aQMgr_order_decide_trade_common(aQMgr_SELECT_RND_ITEM_PROC sel_rnd_item_proc, Animal_c* animal, int* cat_table, int cat_table_cnt, int item_mode, int pay_min, int pay_max, int round_tens, mActor_name_t cancel_item) {
    aQMgr_order_decide_trade_common_item(sel_rnd_item_proc, animal, cat_table, cat_table_cnt, item_mode, cancel_item);
    aQMgr_order_decide_trade_common_pay(pay_min, pay_max, round_tens);
}

static void aQMgr_trade_give_item(int trade_idx, int pockets_idx) {
    if (pockets_idx != -1) {
        mActor_name_t item = l_normal_info.trade_items[trade_idx];

        mPr_SetPossessionItem(Now_Private, pockets_idx, item, mPr_ITEM_COND_NORMAL);
    }
}

static void aQMgr_trade_take_item(int pockets_idx) {
    if (pockets_idx != -1 && Now_Private->inventory.pockets[pockets_idx] == l_normal_info.trade_items[0]) {
        mPr_SetPossessionItem(Now_Private, pockets_idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
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
    manager->give_item = l_normal_info.trade_items[trade_type];
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_ITEM);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_ITEM_PLAYER_WAIT;
    mMsg_SET_LOCKCONTINUE();
    aQMgr_trade_give_item(trade_type, idx);
    manager->talk_step = aQMgr_TALK_STEP_TO_WAIT_ORDER;
}

static int aQMgr_decide_msg_ki_weather_time(QUEST_MANAGER_ACTOR* manager, int looks) {
    int ret_msg = aQMgr_get_msg_weather_time(manager, l_ki_weather_time[looks], 6, 2, 2);
    return ret_msg;
}

static int aQMgr_decide_msg_ki_normal(QUEST_MANAGER_ACTOR* manager, int looks) {
    int ret_msg = l_ki_normal[looks];

    return ret_msg + mQst_GetRandom(10);
}

static int aQMgr_decide_msg_ki_free_item(QUEST_MANAGER_ACTOR* manager, int looks) {
    return aQMgr_decide_msg_check_possession(&aQMgr_get_free_possession_idx, l_ki_free_item[looks], &l_normal_info.free_idx, 3, manager->give_item);
}

static int aQMgr_decide_msg_ki_ftr(QUEST_MANAGER_ACTOR* manager, int looks) {
    return aQMgr_decide_msg_check_possession(&aQMgr_get_possession_ftr_cpt_wl, l_ki_ftr[looks], &l_normal_info.item_idx, 3, manager->give_item);
}

static int aQMgr_decide_msg_ki_free_item_money(QUEST_MANAGER_ACTOR* manager, int looks) {
    return aQMgr_decide_msg_check_possession(&aQMgr_get_free_possession_idx_check_money, l_ki_free_item_money[looks], &l_normal_info.free_idx, 3, manager->give_item);
}

typedef int (*aQMgr_NORMAL_MSG_PROC)(QUEST_MANAGER_ACTOR*, int);

static int aQMgr_decide_ki_msg_no(QUEST_MANAGER_ACTOR* manager, int looks) {
    static aQMgr_NORMAL_MSG_PROC msg_proc[] = {
        &aQMgr_decide_msg_ki_normal,
        &aQMgr_decide_msg_ki_weather_time,
        &aQMgr_decide_msg_ki_free_item,
        &aQMgr_decide_msg_ki_ftr,
        &aQMgr_decide_msg_ki_free_item_money,
    };

    int ret_msg;
    int idx;

    idx = aQMgr_decide_idx_prob_table(l_ki_prob, aQMgr_MSG_KI_NUM);

    if (idx >= 0 && idx < aQMgr_MSG_KI_NUM) {
        ret_msg = (*msg_proc[idx])(manager, looks);

        if (ret_msg == -1) {
            ret_msg = (*msg_proc[aQMgr_MSG_KI_NORMAL])(manager, looks);
        }
    }

    return ret_msg;
}

typedef Anmmem_c* (*aQMgr_GET_MEMORY_PROC)(PersonalID_c*, Anmmem_c*, int);

static int aQMgr_decide_msg_memory(QUEST_MANAGER_ACTOR* manager, int looks) {
    static aQMgr_GET_MEMORY_PROC get_memory_proc[] = {
        &aQMgr_get_other_land_memory,
        &aQMgr_get_this_land_memory_talk_other_land_player,
        &aQMgr_get_this_land_memory_talk_this_land_player,
    };

    ACTOR* client = *manager->client;
    PersonalID_c* pid = &Now_Private->player_ID;
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal;
    Anmmem_c* memory = animal->memories;
    Anmmem_c* ret_mem;
    int ret_msg = -1;
    int idx = mQst_GetRandom(aQMgr_MEMORY_NUM);

    ret_mem = (*get_memory_proc[idx])(pid, memory, ANIMAL_MEMORY_NUM);
    if (ret_mem != NULL) {
        ret_msg = idx * 2;
        ret_msg += l_normal2_memory[looks];

        if (!ret_mem->letter_info.exists) {
            ret_msg += 1;
        } else {
            l_normal_info.mail = &ret_mem->letter;
        }
    } else {
        ret_mem = aQMgr_get_memory_rnd(pid, memory, ANIMAL_MEMORY_NUM);
        if (ret_mem != NULL) {
            ret_msg = aQMgr_MEMORY_NUM * 2;
            ret_msg += l_normal2_memory[looks];

            if (!ret_mem->letter_info.exists) {
                ret_msg += 1;
            } else {
                l_normal_info.mail = &ret_mem->letter;
            }
        } else {
            int mem_idx;
            
            ret_mem = NULL;
            mem_idx = mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM);

            if (mem_idx != -1 && memory[mem_idx].friendship > 80) {
                ret_msg = aQMgr_MEMORY_NUM * 2 + 2;
                ret_msg += l_normal2_memory[looks];
            }
        }
    }

    l_normal_info.memory = ret_mem;
    if (ret_msg == -1) {
        ret_msg = aQMgr_decide_msg_trade(manager, looks);
        l_normal_info.memory = NULL;
        l_normal_info.mail = NULL;
    } else if (ret_mem != NULL) {
        aQMgr_set_free_str_memory(ret_mem);
    }

    return ret_msg;
}

typedef Anmplmail_c* (*aQMgr_GET_MAIL_PROC)(Anmmem_c**, Anmmem_c*, int, Anmmem_c*);

static int aQMgr_decide_msg_letter(QUEST_MANAGER_ACTOR* manager, int looks) {
    static aQMgr_GET_MAIL_PROC get_mail_proc[aQMgr_GET_MEMORY_NUM] = {
        &aQMgr_get_memory_mail_rnd,
        &aQMgr_get_memory_mail_best_friend,
        &aQMgr_get_memory_mail_more_friend,
        &aQMgr_get_memory_mail_over_friendship,
        &aQMgr_get_memory_mail_less_friendship,
        &aQMgr_get_memory_mail_secret,
    };

    ACTOR* client = *manager->client;
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal;
    Anmmem_c* memory = animal->memories;
    int idx;
    Anmplmail_c* ret_mail;
    int ret_msg = -1;

    idx = mQst_GetRandom(aQMgr_GET_MEMORY_NUM);
    ret_mail = (*get_mail_proc[idx])(&l_normal_info.memory, memory, ANIMAL_MEMORY_NUM, *manager->memory);
    if (ret_mail == NULL) {
        l_normal_info.memory = NULL;

        if (idx != aQMgr_GET_MEMORY_MAIL_RND) {
            ret_mail = aQMgr_get_memory_mail_rnd(&l_normal_info.memory, memory, ANIMAL_MEMORY_NUM, *manager->memory);
            idx = aQMgr_GET_MEMORY_MAIL_RND;
        }
    }

    if (ret_mail != NULL) {
        int base_msg = l_normal2_letter[looks];

        ret_msg = base_msg + idx;
        l_normal_info.mail = ret_mail;
        if (l_normal_info.memory != NULL) {
            aQMgr_set_free_str_memory(l_normal_info.memory);
        }
    }

    return ret_msg;
}

static int aQMgr_decide_msg_normal_3_normal(QUEST_MANAGER_ACTOR* manager, int looks) {
    int base_msg = l_normal3_normal[looks];
    int ret_msg = base_msg + mQst_GetRandom(10);

    return ret_msg;
}

static int aQMgr_decide_msg_normal_3_weather_time(QUEST_MANAGER_ACTOR* manager, int looks) {
    int ret_msg = aQMgr_get_msg_weather_time(manager, l_normal3_weather_time[looks], 6, 2, 2);

    return ret_msg;
}

static int aQMgr_decide_msg_normal_3_weather(QUEST_MANAGER_ACTOR* manager, int looks) {
    int weather = Common_Get(weather);
    int msg_cnt = 5;
    int ofs = 0;
    int base_msg;
    int ret_msg;

    if (weather == mEnv_WEATHER_SAKURA) {
        weather = mEnv_WEATHER_CLEAR;
    }

    if (mLd_PlayerManKindCheck()) {
        msg_cnt = 4;
        ofs = 1;
    }

    base_msg = l_normal3_weather[looks] + weather * 5;
    ret_msg = base_msg + mQst_GetRandom(msg_cnt) + ofs;
    return ret_msg;
}

static int aQMgr_decide_msg_normal_3_season(QUEST_MANAGER_ACTOR* manager, int looks) {
    int month = Common_Get(time.rtc_time.month);
    static int add_table[] = { 10, 11, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int ret_msg;

    month--;
    if (month < 0 || month >= lbRTC_MONTHS_MAX) {
        month = 0;
    }

    ret_msg = l_normal3_season[looks] + add_table[month];
    return ret_msg;
}

static int aQMgr_decide_msg_normal_3_msg_no(QUEST_MANAGER_ACTOR* manager, int looks) {
    static aQMgr_NORMAL_MSG_PROC msg_proc[aQMgr_DECIDE_MSG_NORMAL_3_NUM] = {
        &aQMgr_decide_msg_normal_3_normal,
        &aQMgr_decide_msg_normal_3_weather_time,
        &aQMgr_decide_msg_normal_3_weather,
        &aQMgr_decide_msg_normal_3_season,
    };

    int idx = aQMgr_decide_idx_prob_table(l_normal_3_prob, aQMgr_DECIDE_MSG_NORMAL_3_NUM);
    int ret_msg; // @BUG - this should have a default value of -1

    if (idx >= 0 && idx < aQMgr_DECIDE_MSG_NORMAL_3_NUM) {
        ret_msg = (*msg_proc[idx])(manager, looks);
    }

    return ret_msg;
}

static int aQMgr_decide_msg_trade_free_item(QUEST_MANAGER_ACTOR* manager, int looks) {
    int ret_msg = aQMgr_decide_msg_check_possession(&aQMgr_get_free_possession_idx, l_trade_free_item[looks], &l_normal_info.free_idx, 5, manager->give_item);
    
    return ret_msg;
}

static int aQMgr_decide_msg_trade_ftr(QUEST_MANAGER_ACTOR* manager, int looks) {
    int ret_msg = aQMgr_decide_msg_check_possession(&aQMgr_get_possession_ftr_cpt_wl, l_trade_ftr[looks], &l_normal_info.item_idx, 5, manager->give_item);
    
    return ret_msg;
}

static int aQMgr_decide_msg_trade_free_item_money(QUEST_MANAGER_ACTOR* manager, int looks) {
    int ret_msg = aQMgr_decide_msg_check_possession(&aQMgr_get_free_possession_idx_check_money, l_trade_free_item_money[looks], &l_normal_info.free_idx, 5, manager->give_item);
    
    return ret_msg;
}

static int aQMgr_decide_msg_trade_item(QUEST_MANAGER_ACTOR* manager, int looks) {
    int ret_msg = aQMgr_decide_msg_check_possession(&aQMgr_get_possession_item, l_trade_item[looks], &l_normal_info.item_idx, 5, manager->give_item);
    
    return ret_msg;
}

static int aQMgr_decide_msg_trade(QUEST_MANAGER_ACTOR* manager, int looks) {
    static aQMgr_NORMAL_MSG_PROC msg_proc[aQMgr_DECIDE_MSG_NORMAL_3_NUM] = {
        &aQMgr_decide_msg_trade_free_item,
        &aQMgr_decide_msg_trade_ftr,
        &aQMgr_decide_msg_trade_item,
        &aQMgr_decide_msg_trade_free_item_money,
    };

    int idx = aQMgr_decide_idx_prob_table(l_trade_prob, aQMgr_DECIDE_MSG_TRADE_NUM);
    int ret_msg; // @BUG - this should have a default value of -1

    if (idx >= 0 && idx < aQMgr_DECIDE_MSG_TRADE_NUM) {
        ret_msg = (*msg_proc[idx])(manager, looks);
    }

    return ret_msg;
}

static int aQMgr_decide_normal_2_msg_no(QUEST_MANAGER_ACTOR* manager, int looks) {
    static aQMgr_NORMAL_MSG_PROC msg_proc[] = {
        &aQMgr_decide_msg_letter,
        &aQMgr_decide_msg_normal_3_msg_no,
        &aQMgr_decide_msg_trade,
        &aQMgr_decide_msg_memory,
    };

    int idx = aQMgr_decide_idx_prob_table(l_normal_2_prob, aQMgr_DECIDE_MSG_NORMAL_2_NUM);
    int ret_msg; // @BUG - this should have a default value of -1

    if (idx >= 0 && idx < aQMgr_DECIDE_MSG_NORMAL_2_NUM) {
        ret_msg = (*msg_proc[idx])(manager, looks);
    }

    if (ret_msg == -1) {
        ret_msg = aQMgr_decide_msg_normal_3_msg_no(manager, looks);
    }

    return ret_msg;
}

static int aQMgr_decide_msg_game_hint(QUEST_MANAGER_ACTOR* manager, int looks) {
    int base_msg = l_game_hint[looks];
    int ret_msg = base_msg + mQst_GetRandom(5);

    return ret_msg;
}

static int aQMgr_decide_msg_remove(QUEST_MANAGER_ACTOR* manager, int looks) {
    int base_msg = l_remove_yes[looks];
    int ret_msg = base_msg + mQst_GetRandom(3);

    return ret_msg;
}

static int aQMgr_decide_msg_calendar_ev(QUEST_MANAGER_ACTOR* manager, int looks) {
    int ret_msg = -1;
    int rumor_subtype = -1;
    int rumor_base_msg;
    int rumor = mEv_get_rumor();
    u8 day;

    if (rumor != 0) {
        rumor_subtype = mEv_GET_SUBTYPE(rumor);
    }

    if (rumor_subtype != -1) {
        rumor_subtype *= 2;
        rumor_subtype += mQst_GetRandom(2);
        ret_msg = l_ev_cal[looks] + rumor_subtype;
    }

    if ((rumor == mEv_RUMOR_CHERRY_BLOSSOM_FESTIVAL2 && Common_Get(time).term_idx != mTM_TERM_4) || (rumor == mEv_RUMOR_KAMAKURA && Common_Get(time).season != mTM_SEASON_WINTER)) {
        ret_msg = -1;
    } else if (rumor == mEv_RUMOR_SUMMER_FISHING_TOURNEY || rumor == mEv_RUMOR_SUMMER_FISHING_TOURNEY2 || rumor == mEv_RUMOR_FALL_FISHING_TOURNEY || rumor == mEv_RUMOR_FALL_FISHING_TOURNEY2) {
        day = mEv_get_next_weekday(lbRTC_SUNDAY);
        aQMgr_set_number_free_str_add_nichi(day, mMsg_FREE_STR14);
    } else if (rumor == mEv_RUMOR_FIREWORKS_SHOW) {
        day = mEv_get_next_weekday(lbRTC_SATURDAY);
        aQMgr_set_number_free_str_add_nichi(day, mMsg_FREE_STR15);
    }

    aQMgr_set_calendar_free_str(&lbRk_ToSeiyouReki, mMsg_FREE_STR16, mMsg_FREE_STR17, 8, 15); // 8th moon 15th day
    aQMgr_set_calendar_free_str(&lbRk_ToSeiyouReki, mMsg_FREE_STR18, mMsg_FREE_STR19, 9, 13); // 9th moon 13th day
    return ret_msg;
}

static int aQMgr_decide_msg_special_ev(QUEST_MANAGER_ACTOR* manager, int looks) {
    int ret_msg = -1;
    int base_msg;
    u32 ev_kind;
    int sp_ev_msg_no;
    mActor_name_t item;
    int str_no = -1;
    mActor_name_t category;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int i;

    ev_kind = Save_Get(event_save_data).special.kind;

    if (ev_kind != -1) {
        // clang-format off
        if ((lbRTC_IsOverTime(&Save_Get(event_save_data).special.scheduled, rtc_time) == lbRTC_LESS) ||
            (ev_kind == mEv_SPNPC_SHOP && lbRTC_IsOverTime(&Save_Get(event_save_data).special.event.bargin.end_time, rtc_time) == lbRTC_LESS) ||
            (ev_kind != mEv_SPNPC_SHOP && lbRTC_IsEqualTime(&Save_Get(event_save_data).special.scheduled, rtc_time, lbRTC_CHECK_YEARS | lbRTC_CHECK_MONTHS | lbRTC_CHECK_DAYS) == TRUE)
        ) {
            u32 month;
            u32 day;

            base_msg = l_ev_special[looks];
            ret_msg = base_msg + mEv_GET_SUBTYPE(ev_kind) * 3;
            ret_msg += mQst_GetRandom(3);

            if (ev_kind == mEv_SPNPC_SHOP) {
                for (i = 0; i < mEv_BARGIN_ITEM_NUM; i++) {
                    item = Save_Get(event_save_data).special.event.bargin.items[i];
                    if (ITEM_IS_FTR(item)) {
                        str_no = 0x55D;
                    } else if (ITEM_NAME_GET_TYPE(item) == NAME_TYPE_ITEM1) {
                        category = ITEM_NAME_GET_CAT(item);
                        switch (category) {
                            case ITEM1_CAT_CARPET:
                                str_no = 0x55E;
                                break;
                            case ITEM1_CAT_WALL:
                                str_no = 0x55F;
                                break;
                            case ITEM1_CAT_CLOTH:
                                str_no = 0x560;
                                break;
                        }
                    }

                    if (str_no != -1) {
                        mString_Load_StringFromRom(l_aqmgr_str, sizeof(l_aqmgr_str), str_no);
                        mMsg_SET_FREE_STR(mMsg_FREE_STR11, l_aqmgr_str, sizeof(l_aqmgr_str));
                        break;
                    }
                }

                if (str_no == -1) {
                    ret_msg = -1;
                }
            }

            if (ret_msg != -1) {
                month = Save_Get(event_save_data).special.scheduled.month;
                day = Save_Get(event_save_data).special.scheduled.day;

                aQMgr_set_number_free_str_add_gatu(month, mMsg_FREE_STR12);
                aQMgr_set_number_free_str_add_nichi(day, mMsg_FREE_STR13);
            }
        }
    }

    return ret_msg;
}

static int aQMgr_decide_msg_ev(QUEST_MANAGER_ACTOR* manager, int looks) {
    static aQMgr_NORMAL_MSG_PROC msg_proc[] = {
        &aQMgr_decide_msg_special_ev,
        &aQMgr_decide_msg_calendar_ev,
    };

    int idx;
    int ret_msg = -1;

    idx = aQMgr_decide_idx_prob_table(l_ev_prob, aQMgr_DECIDE_MSG_EV_NUM);
    if (idx >= 0 && idx < aQMgr_DECIDE_MSG_EV_NUM) {
        ret_msg = (*msg_proc[idx])(manager, looks);
    }

    if (ret_msg == -1) {
        ret_msg = aQMgr_decide_msg_special_ev(manager, looks);
    }

    if (ret_msg == -1) {
        ret_msg = aQMgr_decide_msg_game_hint(manager, looks);
    }

    return ret_msg;
}

static int aQMgr_decide_msg_game_ev(QUEST_MANAGER_ACTOR* manager, int looks) {
    int ret_msg;

    if (!mLd_PlayerManKindCheck() && aQMgr_check_client_remove(manager) == TRUE) {
        ret_msg = aQMgr_decide_msg_remove(manager, looks);
    } else {
        ret_msg = aQMgr_decide_msg_ev(manager, looks);
    }

    return ret_msg;
}

static int aQMgr_decide_game_msg_no(QUEST_MANAGER_ACTOR* manager, int looks) {
    static aQMgr_NORMAL_MSG_PROC msg_proc[] = {
        &aQMgr_decide_msg_game_hint,
        &aQMgr_decide_msg_game_ev,
    };

    int idx;
    int ret_msg;

    idx = aQMgr_decide_idx_prob_table(l_game_prob, aQMgr_DECIDE_MSG_GAME_MSG_NUM);
    ret_msg = (*msg_proc[idx])(manager, looks);
    return ret_msg;
}

static int aQMgr_decide_normal_msg_no(QUEST_MANAGER_ACTOR* manager, int looks) {
    static aQMgr_NORMAL_MSG_PROC msg_proc[] = {
        &aQMgr_decide_normal_2_msg_no,
        &aQMgr_decide_game_msg_no,
    };

    int idx;
    int ret_msg; // @BUG -- should be initialized to -1

    idx = aQMgr_decide_idx_prob_table(l_normal_1_prob, aQMgr_DECIDE_MSG_NORMAL_MSG_NUM);
    if (idx >= 0 && idx < aQMgr_DECIDE_MSG_NORMAL_MSG_NUM) {
        ret_msg = (*msg_proc[idx])(manager, looks);
    }

    return ret_msg;
}

static void aQMgr_get_fj_hint_msg(int* msg_no, int hint_type, int looks) {
    *msg_no = hint_type + looks * 10 + 0x0841;
}

static int aQMgr_decide_fj_hint_msg_no(int looks) {
    int hint_type;
    int ret_msg;

    ret_msg = -1;
    hint_type = mPr_GetFirstJobHintTime(Now_Private);
    aQMgr_get_fj_hint_msg(&ret_msg, hint_type, looks);
    return ret_msg;
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
    int remove_no = Save_Get(remove_animal_idx);

    Save_Set(remove_animal_idx, 0xFF);
    mNpc_SetRemoveAnimalNo(&Save_Get(remove_animal_idx), Save_Get(animals), remove_no);
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

static void aQMgr_order_decide_trade_1(Animal_c* animal, mActor_name_t cancel_item) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, 100, 3000, TRUE, cancel_item);
}

static void aQMgr_order_decide_trade_2(Animal_c* animal, mActor_name_t cancel_item) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, 1000, 5000, TRUE, cancel_item);
}

static void aQMgr_order_decide_trade_3(Animal_c* animal, mActor_name_t cancel_item) {
    int money = Now_Private->inventory.wallet;

    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, money, money, FALSE, cancel_item);
}


static void aQMgr_order_decide_trade_4(Animal_c* animal, mActor_name_t cancel_item) {
    int money = Now_Private->inventory.wallet;

    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, money / 2, money / 2, FALSE, cancel_item);
}

static void aQMgr_order_decide_trade_5(Animal_c* animal, mActor_name_t cancel_item) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, 3000, 3000, FALSE, cancel_item);
}

static void aQMgr_order_decide_trade_6(Animal_c* animal, mActor_name_t cancel_item) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, 1000, 1000, FALSE, cancel_item);
}

static void aQMgr_order_decide_trade_7(Animal_c* animal, mActor_name_t cancel_item) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_item_rnd, animal, l_quest_category_1, ARRAY_COUNT(l_quest_category_1), aQMgr_SEL_ITEM_MODE_RANDOM, 100, 3000, TRUE, cancel_item);
}

static void aQMgr_order_decide_trade_8(Animal_c* animal, mActor_name_t cancel_item) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_PITFALL, 100, 3000, TRUE, cancel_item);
}

static void aQMgr_order_decide_trade_9(Animal_c* animal, mActor_name_t cancel_item) {
    int money = Now_Private->inventory.wallet;

    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_PITFALL, money, money, TRUE, cancel_item);
}

static void aQMgr_order_decide_trade_10(Animal_c* animal, mActor_name_t cancel_item) {
    int money = Now_Private->inventory.wallet;

    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_PITFALL, money / 2, money / 2, TRUE, cancel_item);
}

static void aQMgr_order_decide_trade_11(Animal_c* animal, mActor_name_t cancel_item) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_item_rnd, animal, l_quest_category_1, ARRAY_COUNT(l_quest_category_1), aQMgr_SEL_ITEM_MODE_PITFALL, 100, 3000, TRUE, cancel_item);
}

static void aQMgr_order_decide_trade_12(Animal_c* animal, mActor_name_t cancel_item) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, 100, 500, TRUE, cancel_item);
}

static void aQMgr_order_decide_trade_13(Animal_c* animal, mActor_name_t cancel_item) {
    aQMgr_order_decide_trade_common(&aQMgr_get_possession_ftr_cpt_wl_rnd, animal, l_quest_category_0, ARRAY_COUNT(l_quest_category_0), aQMgr_SEL_ITEM_MODE_RANDOM, 1000, 2000, TRUE, cancel_item);
}

static void aQMgr_order_decide_trade_14(Animal_c* animal, mActor_name_t cancel_item) {
    aQMgr_order_decide_trade_common_pay(3000, 5000, TRUE);
}

static void aQMgr_order_decide_trade_15(Animal_c* animal, mActor_name_t cancel_item) {
    aQMgr_order_decide_trade_common_pay(2000, 2999, TRUE);
}

static void aQMgr_order_decide_trade_16(Animal_c* animal, mActor_name_t cancel_item) {
    aQMgr_order_decide_trade_common_pay(1000, 1999, TRUE);
}

static void aQMgr_order_decide_trade_17(Animal_c* animal, mActor_name_t cancel_item) {
    aQMgr_order_decide_trade_common_pay(100, 999, TRUE);
}

typedef void (*aQMgr_DECIDE_TRADE_PROC)(Animal_c*, mActor_name_t);

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
    };

    aQMgr_order_c* order_p = &manager->demo_order;
    Animal_c* animal = aQMgr_GET_CLIENT_ANIMAL(manager);
    int val = order_p->value;

    val--;
    (*decide_proc[val])(animal, manager->give_item);
}

static void aQMgr_order_move_trade_no_term(QUEST_MANAGER_ACTOR* manager, int idx) {
    aQMgr_trade_give_item(idx, l_normal_info.free_idx);
    manager->target.quest_item = l_normal_info.trade_items[idx];
    manager->give_item = l_normal_info.trade_items[idx];
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
        &aQMgr_order_move_trade_13,
    };

    aQMgr_order_c* order_p = &manager->demo_order;
    int val = order_p->value;

    if (val > 0 && val <= 23) {
        val--;
        (*move_proc[val])(manager);
    }
}

static void aQMgr_order_show_letter(QUEST_MANAGER_ACTOR* manager) {
    mMsg_SET_LOCKCONTINUE();
    mMsg_REQUEST_MAIN_DISAPPEAR_WAIT_TYPE2();
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_DISAPPEAR_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_OPEN_LETTER;
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

static int aQMgr_set_random_string(u8* str, int item_str_no, int base_str, f32 str_num, int skip_idx) {
    int idx;

    idx = RANDOM(str_num);
    if (skip_idx >= 0 && skip_idx == idx) {
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

    if (shop_level < 0 || shop_level >= mSP_SHOP_TYPE_NUM) {
        shop_level = mSP_SHOP_TYPE_ZAKKA;
    }

    mem_clear(str, sizeof(str), CHAR_SPACE);
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

    if (val <= 0 || val > aQMgr_SET_STR_NUM) {
        val = aQMgr_SET_STR_0 + 1;
    }

    val--;
    (*set_string_proc[val])(manager->last_strings);
}

static int l_aqmgr_hint_ng_msg[] = { 0x0F12, 0x0F91, 0x152E, 0x2586, 0x262E, 0x29F0, 0x29F9, 0x2A76 };
static int l_aqmgr_hint_ng_base_msg[] = { 0x0F12, 0x0F8C, 0x1526, 0x257E, 0x262D, 0x29F0, 0x29F0, 0x2A76 };
static int l_aqmgr_hint_ng_rnd_max[] = {2, 10, 10, 10, 2, 10, 10, 2};

static int aQMgr_change_NG_msg(int msg_no) {
    int i;
    int j;
    int ret_msg = msg_no; 

    if (Now_Private != NULL && !mPr_CheckFirstJobHint(Now_Private)) {
        for (i = 0; i < ARRAY_COUNT(l_aqmgr_hint_ng_msg); i++) {
            if (msg_no == l_aqmgr_hint_ng_msg[i]) {
                int base_msg;
                int max;
                
                base_msg = l_aqmgr_hint_ng_base_msg[i];
                max = l_aqmgr_hint_ng_rnd_max[i] - 1;
                ret_msg = base_msg + RANDOM(max);
                for (j = 0; j < ARRAY_COUNT(l_aqmgr_hint_ng_msg); j++) {
                    if (ret_msg == l_aqmgr_hint_ng_msg[j]) {
                        ret_msg++;
                        break;
                    }
                }

                break;
            }
        }
    }

    return ret_msg;
}

static void aQMgr_talk_normal_select_talk(QUEST_MANAGER_ACTOR* manager) {
    ACTOR* client = *manager->client;
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal;
    int looks = mNpc_GetNpcLooks(client);
    u32 player_event;
    int msg_no;

    manager->mail_memory = NULL;
    mMsg_UNSET_LOCKCONTINUE();
    aQMgr_init_normal_info(&l_normal_info);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_DEMO_ORDER_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_DEMO_ORDER;

    player_event = mEv_SAVED_FIRSTJOB_PLR0 + Common_Get(player_no);
    aQMgr_normal_set_free_str(manager);
    
    if (!mLd_PlayerManKindCheck() && ((mEv_CheckFirstJob() == TRUE && !mEv_CheckEvent(player_event)) || mPr_CheckFirstJobHint(Now_Private) != TRUE)) {
        msg_no = aQMgr_decide_fj_hint_msg_no(looks);
        mPr_AddFirstJobHint(Now_Private);
    } else {
        if (animal->mood == mNpc_FEEL_HAPPY) {
            msg_no = aQMgr_decide_ki_msg_no(manager, looks);
        } else {
            msg_no = aQMgr_decide_normal_msg_no(manager, looks);
        }
    }

    manager->msg_no = aQMgr_change_NG_msg(msg_no);
    mMsg_SET_CONTINUE_MSG_NUM(manager->msg_no);
    mMsg_SET_FORCENEXT();
}

typedef void (*aQMgr_DEMO_PROC)(QUEST_MANAGER_ACTOR*);

static void aQMgr_talk_normal_demo_order(QUEST_MANAGER_ACTOR* manager) {
    static aQMgr_DEMO_PROC order_proc[] = {
        &aQMgr_order_change_roof_color,
        &aQMgr_control_animal_info,
        &aQMgr_order_decide_trade,
        &aQMgr_order_trade,
        &aQMgr_order_show_letter,
        &aQMgr_order_fluctuation_friendship,
        &aQMgr_order_play_memory_melody,
        &aQMgr_order_set_calendar,
        &aQMgr_order_input_birthday,
        &aQMgr_order_set_string,
    };

    aQMgr_order_c* order_p = &manager->demo_order;
    int type = order_p->type;
    
    if (type < 0 || type >= aQMgr_DEMO_ORDER_NUM) {
        type = aQMgr_DEMO_ORDER_CHANGE_ROOF_COLOR;
    }

    (*order_proc[type])(manager);
}

static void aQMgr_talk_normal_open_letter(QUEST_MANAGER_ACTOR* manager) {
    Submenu* submenu = manager->submenu;
    ACTOR* client = *manager->client;
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal;
    static Mail_c show_mail;

    mMl_clear_mail(&show_mail);
    if (l_normal_info.memory != NULL) {
        mNpc_AnimalMail2Mail(&show_mail, l_normal_info.mail, &l_normal_info.memory->memory_player_id, &animal->id);
        show_mail.content.mail_type = mMl_TYPE_MAIL;
    } else {
        mNpc_AnimalMail2Mail(&show_mail, l_normal_info.mail, NULL, &animal->id);
        show_mail.content.mail_type = mMl_TYPE_MAIL;
        mem_clear(show_mail.header.sender.personalID.player_name, PLAYER_NAME_LEN, CHAR_SPACE);
    }

    mSM_open_submenu_new(submenu, mSM_OVL_BOARD, mSM_BD_OPEN_READ, 0, &show_mail);
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

    if (animal != NULL) {
        mSM_open_submenu_new(submenu, mSM_OVL_LEDIT, mLE_TYPE_EPHRASE, 0, animal->catchphrase);
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_HAND_ITEM_WAIT;
        manager->talk_step = aQMgr_TALK_STEP_OPEN_MSG;
    }
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

static void aQMgr_talk_normal_kamakura_hello(QUEST_MANAGER_ACTOR* manager) {
    manager->mail_memory = NULL;
    aQMgr_init_normal_info(&l_normal_info);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_DEMO_ORDER_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_DEMO_ORDER;
}

static void aQMgr_talk_normal_kamakura(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_normal_kamakura_hello(manager);
    aQMgr_normal_set_free_str(manager);
    l_normal_info.free_idx = aQMgr_get_free_possession_idx(manager->give_item);
}

static void aQMgr_talk_normal_summercamp_hello(QUEST_MANAGER_ACTOR* manager) {
    manager->mail_memory = NULL;
    aQMgr_init_normal_info(&l_normal_info);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_DEMO_ORDER_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_DEMO_ORDER;
}

static void aQMgr_talk_normal_summercamp(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_normal_summercamp_hello(manager);
    aQMgr_normal_set_free_str(manager);
    l_normal_info.free_idx = aQMgr_get_free_possession_idx(manager->give_item);
}

extern void aQMgr_talk_normal_init(QUEST_MANAGER_ACTOR* manager) {
    static aQMgr_TALK_INIT_PROC talk_proc[] = {
        &aQMgr_talk_normal_select_talk,
        &aQMgr_talk_normal_demo_order,
        &aQMgr_talk_normal_open_letter,
        &aQMgr_talk_normal_open_msg,
        &aQMgr_talk_normal_give_item,
        &aQMgr_talk_normal_to_wait_order,
        &aQMgr_talk_normal_open_birthday,
        &aQMgr_talk_normal_open_gobi,
        &aQMgr_talk_normal_kamakura_hello,
        &aQMgr_talk_normal_kamakura,
        &aQMgr_talk_normal_summercamp_hello,
        &aQMgr_talk_normal_summercamp,
    };

    int step = manager->talk_step;

    if (step < 0 || step >= aQMgr_TALK_STEP_NUM) {
        step = aQMgr_TALK_STEP_SELECT_TALK;
    }

    (*talk_proc[step])(manager);
    manager->talk_state = aQMgr_TALK_STATE_SUB;
}
