#include "ac_quest_talk_greeting.h"

#include "m_common_data.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_string.h"

enum {
    aQMgr_FEEL_RAGE,
    aQMgr_FEEL_SAD,
    aQMgr_FEEL_SLEEP,
    aQMgr_FEEL_4,
    aQMgr_FEEL_5,
    aQMgr_FEEL_UZAI,
    aQMgr_FEEL_UZA2,

    aQMgr_FEEL_NUM
};

enum {
    aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO,             // first meeting
    aQMgr_MEET_TIME_HELLO_AGAIN,                     // more than first time spoken to today
    aQMgr_MEET_TIME_FIRST_HELLO,                     // first time spoken to today
    aQMgr_MEET_TIME_A_LONG_TIME,                     // first time spoken to 'in a long time'
    aQMgr_MEET_TIME_A_REALLY_LONG_TIME,              // first time spoken to 'in a really long time'
    aQMgr_MEET_TIME_FIRST_HELLO_FOREIGN_TOWN,        // first time spoken to today in a foreign town
    aQMgr_MEET_TIME_A_LONG_TIME_FOREIGN_TOWN,        // first time spoken to 'in a long time' in a foreign town
    aQMgr_MEET_TIME_A_REALLY_LONG_TIME_FOREIGN_TOWN, // first time spoken to 'in a really long time' in a foreign town

    aQMgr_MEET_TIME_NUM
};

// clang-format off
static int l_hello_fine_msg_tbl[] = { MSG_1213, MSG_1357, MSG_1285, MSG_1501, MSG_1645, MSG_1429, MSG_1573, MSG_1717 };
static int l_hello_fine_island_msg_tbl[] = { MSG_13400, MSG_13575, MSG_13551, MSG_13647, MSG_13647, MSG_13647, MSG_13647, MSG_13647 };
static int l_hello_rain_msg_tbl[] = { MSG_1213, MSG_3099, MSG_3027, MSG_1501, MSG_1645, MSG_1429, MSG_1573, MSG_1717 };
static int l_hello_snow_msg_tbl[] = { MSG_1213, MSG_3243, MSG_3171, MSG_1501, MSG_1645, MSG_1429, MSG_1573, MSG_1717 };
static int l_grad_hello_msg_tbl[] = { MSG_4644, MSG_4788, MSG_4716, MSG_4716, MSG_4716, MSG_4716, MSG_4716, MSG_4716 };
static int l_indoor_hello_msg_tbl[] = { MSG_8404, MSG_8812, MSG_8740, MSG_8956, MSG_8884, MSG_8668, MSG_8596, MSG_8524 };

static int l_hello_rage_msg[] = { MSG_3315, MSG_3320, MSG_3325, MSG_3330, MSG_3335, MSG_3340 };
static int l_hello_rage_island_msg[] = { MSG_13430, MSG_13433, MSG_13436, MSG_13439, MSG_13442, MSG_13445 };
static int l_hello_sad_msg[] = { MSG_3345, MSG_3350, MSG_3355, MSG_3360, MSG_3365, MSG_3370 };
static int l_hello_sad_island_msg[] = { MSG_13448, MSG_13451, MSG_13454, MSG_13457, MSG_13460, MSG_13463 };
static int l_hello_sleep_msg[] = { MSG_3375, MSG_3380, MSG_3385, MSG_3390, MSG_3395, MSG_3400 };
static int l_hello_uzai_msg[] = { MSG_11901, MSG_11912, MSG_11896, MSG_11923, MSG_11928, MSG_11939 };
static int l_hello_uzai_island_msg[] = { MSG_13466, MSG_13469, MSG_13472, MSG_13475, MSG_13478, MSG_13481 };
// clang-format on

static void aQMgr_actor_set_day_str(int day, int str_no) {
    if (day >= 0) {
        u8 str[mMsg_FREE_STRING_LEN];

        mFont_UnintToString(str, sizeof(str), day, 10, TRUE, FALSE, FALSE);
        mMsg_Set_free_str(mMsg_Get_base_window_p(), str_no, str, sizeof(str));
    }
}

static int aQMgr_actor_get_my_hello_msg_com(aQMgr_GET_TIME_KIND_PROC get_time_kind_proc, int base_msg, int looks,
                                            int hour, int kind_count) {
    int msg_no = base_msg + looks * kind_count * 4;
    int time_kind = (*get_time_kind_proc)(hour);

    msg_no += time_kind * kind_count;
    msg_no += mQst_GetRandom(kind_count);
    return msg_no;
}

static int aQMgr_get_random_msg_no(int base_msg, int looks, int kind_count) {
    int msg_no = base_msg + mQst_GetRandom(kind_count) + looks * kind_count;

    return msg_no;
}

static int aQMgr_get_hello_msg_npc_feel(int feel, int looks) {
    static int* feel_msg_table[aQMgr_FEEL_NUM] = { l_hello_rage_msg, l_hello_sad_msg, l_hello_sleep_msg, NULL, NULL,
                                                   l_hello_uzai_msg, l_hello_uzai_msg };
    int* feel_msg_tbl_p;
    int rng_msg;
    int msg_no;

    feel -= mNpc_FEEL_ANGRY; // Remove happy & normal

    if (feel < 0 || feel >= aQMgr_FEEL_NUM) {
        feel = 0;
    }

    feel_msg_tbl_p = feel_msg_table[feel];
    if (feel_msg_tbl_p == NULL) {
        feel_msg_tbl_p = l_hello_rage_msg;
    }

    rng_msg = mQst_GetRandom(5);
    msg_no = rng_msg + feel_msg_tbl_p[looks];
    return msg_no;
}

static int aQMgr_get_hello_msg_npc_feel_island(int feel, int looks) {
    static int* feel_msg_table[aQMgr_FEEL_NUM] = {
        l_hello_rage_island_msg, l_hello_sad_island_msg, l_hello_sleep_msg, NULL, NULL,
        l_hello_uzai_island_msg, l_hello_uzai_island_msg
    };
    int* feel_msg_tbl_p;
    int rng_msg;
    int msg_no;

    feel -= mNpc_FEEL_ANGRY; // Remove happy & normal

    if (feel < 0 || feel >= aQMgr_FEEL_NUM) {
        feel = 0;
    }

    feel_msg_tbl_p = feel_msg_table[feel];
    if (feel_msg_tbl_p == NULL) {
        feel_msg_tbl_p = l_hello_rage_msg;
    }

    rng_msg = mQst_GetRandom(3);
    msg_no = rng_msg + feel_msg_tbl_p[looks];
    return msg_no;
}

static int aQMgr_get_meet_time(Animal_c* animal, Anmmem_c* memory, int* months, int* weeks) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int mem_idx;
    int type = 1;
    int foreigner = FALSE;

    if (memory != NULL) {
        lbRTC_time_c* last_spoken_time;
        int days;

        mem_idx = mNpc_GetAnimalMemoryIdx(&Common_Get(now_private)->player_ID, memory, ANIMAL_MEMORY_NUM);
        if (mem_idx == -1) {
            return aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO;
        }

        memory += mem_idx;
        last_spoken_time = &memory->last_speak_time;
        if (mTM_IsTimeCleared(last_spoken_time)) {
            return aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO;
        }

        if (lbRTC_IsOverTime(rtc_time, last_spoken_time) == lbRTC_OVER) {
            return aQMgr_MEET_TIME_HELLO_AGAIN;
        }

        days = lbRTC_GetIntervalDays(last_spoken_time, rtc_time);
        if (animal != NULL && mNpc_CheckIslandAnimal(animal) == FALSE &&
            mLd_CheckThisLand(memory->memuni.land.name, memory->memuni.land.id) == FALSE) {
            foreigner = TRUE;
        }

        if (days >= 60) {
            int years;

            type = foreigner == FALSE ? aQMgr_MEET_TIME_A_REALLY_LONG_TIME
                                      : aQMgr_MEET_TIME_A_REALLY_LONG_TIME_FOREIGN_TOWN;
            years = days / 365;
            *months = years * lbRTC_MONTHS_MAX;
            *months += (days % 365) / 30;
            *weeks = days / lbRTC_WEEK;
        } else if (days >= 14) {
            type = foreigner == FALSE ? aQMgr_MEET_TIME_A_LONG_TIME : aQMgr_MEET_TIME_A_LONG_TIME_FOREIGN_TOWN;
            *weeks = days / lbRTC_WEEK;
        } else if (days >= 1) {
            if (foreigner == FALSE) {
                type = aQMgr_MEET_TIME_FIRST_HELLO;
            } else {
                type = aQMgr_MEET_TIME_FIRST_HELLO_FOREIGN_TOWN;
            }
        } else {
            type = aQMgr_MEET_TIME_HELLO_AGAIN;
        }
    }

    return type;
}

static void aQMgr_set_memory(Animal_c* animal, Anmmem_c* memory) {
    PersonalID_c* pid = &Common_Get(now_private)->player_ID;

    if (memory != NULL) {
        int mem_idx = mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM);

        if (mem_idx == -1) {
            mem_idx = mNpc_ForceGetFreeAnimalMemoryIdx(animal, memory, ANIMAL_MEMORY_NUM);

            if (mem_idx != -1) {
                memory += mem_idx;
                mNpc_SetAnimalMemory(pid, &animal->id, memory);
            }
        }
    }
}

static void aQMgr_clear_memory(Animal_c* animal, Anmmem_c* memory) {
    PersonalID_c* pid = &Common_Get(now_private)->player_ID;

    if (memory != NULL) {
        int mem_idx = mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM);

        if (mem_idx != -1) {
            memory += mem_idx;

            if (mNpc_CheckIslandAnimal(animal) == TRUE) {
                mNpc_ClearIslandAnimalMemory(memory, 1);
            } else {
                mNpc_ClearAnimalMemory(memory, 1);
            }
        }
    }
}

static int aQMgr_get_hello_msg_npc_feel_normal(Animal_c* animal, int looks, int last_meet_time_type,
                                               aQMgr_GET_TIME_KIND_PROC get_time_kind_proc) {
    static int* hello_msg_tbl[] = { l_hello_fine_msg_tbl, l_hello_rain_msg_tbl, l_hello_snow_msg_tbl,
                                    l_hello_fine_msg_tbl };
    int* hello_msg_tbl_p;
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int hello_msg;
    int msg_no;
    int weather = Common_Get(weather);
    int anm_idx = mNpc_SearchAnimalPersonalID(&animal->id);

    if (mNpc_CheckOverImpatient(anm_idx, looks) == TRUE) {
        int over_impatient = mNpc_GetOverImpatient(anm_idx, looks);

        msg_no = MSG_2640;
        msg_no += looks * 6 + over_impatient * 3;
        msg_no += mQst_GetRandom(3);
    } else if (last_meet_time_type == aQMgr_MEET_TIME_FIRST_HELLO &&
               mEv_IsEventActive(mEv_EVENT_SPRING_CLEANING) == TRUE) {
        msg_no = aQMgr_get_random_msg_no(MSG_15297, looks, 3);
    } else if (last_meet_time_type == aQMgr_MEET_TIME_FIRST_HELLO &&
               mEv_IsEventActive(mEv_EVENT_APRILFOOLS_DAY) == TRUE) {
        msg_no = aQMgr_get_random_msg_no(MSG_15236, looks, 3);
    } else {
        mActor_name_t field_type = mFI_GET_TYPE(mFI_GetFieldId());

        if (field_type == mFI_FIELD_ROOM0 || field_type == mFI_FIELD_NPCROOM0) {
            hello_msg = l_indoor_hello_msg_tbl[last_meet_time_type];
        } else {
            hello_msg_tbl_p = hello_msg_tbl[weather];
            hello_msg = hello_msg_tbl_p[last_meet_time_type];
        }

        msg_no = aQMgr_actor_get_my_hello_msg_com(get_time_kind_proc, hello_msg, looks, rtc_time->hour, 3);
    }

    return msg_no;
}

static int aQMgr_get_hello_msg_npc_feel_normal_island(Animal_c* animal, int looks, int last_meet_time_type,
                                                      aQMgr_GET_TIME_KIND_PROC get_time_kind_proc) {
    static int rnd_table[aQMgr_MEET_TIME_NUM] = { 1, 3, 1, 1, 1, 1, 1, 1 };
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int msg_no = -1;

    if (last_meet_time_type == aQMgr_MEET_TIME_FIRST_HELLO) {
        if (mEv_IsEventActive(mEv_EVENT_SPRING_CLEANING) == TRUE) {
            msg_no = aQMgr_get_random_msg_no(MSG_15315, looks, 3);
        } else if (mEv_IsEventActive(mEv_EVENT_APRILFOOLS_DAY) == TRUE) {
            msg_no = aQMgr_get_random_msg_no(MSG_15254, looks, 3);
        }
    }

    if (msg_no == -1) {
        int hello_msg = l_hello_fine_island_msg_tbl[last_meet_time_type];
        int kind_num = rnd_table[last_meet_time_type];

        msg_no = aQMgr_actor_get_my_hello_msg_com(get_time_kind_proc, hello_msg, looks, rtc_time->hour, kind_num);
    }

    return msg_no;
}

static int aQMgr_get_thanks_cloth_msg(Animal_c* animal, int looks) {
    PersonalID_c* pid = &Common_Get(now_private)->player_ID;
    int msg_no = MSG_11752;

    if (pid != NULL && animal != NULL) {
        Anmmem_c* memory = animal->memories;
        int cloth_mem_idx = mNpc_GetPresentClothMemoryIdx_rnd(memory);
        int mem_idx = mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM);
        int cloth_msg;

        if (cloth_mem_idx == mem_idx) {
            // This player gave the cloth
            memory += mem_idx;
            cloth_msg = MSG_11770;
        } else {
            // Another player gave the cloth
            memory += cloth_mem_idx;
            pid = &memory->memory_player_id;
            cloth_msg = MSG_11752;
        }

        msg_no = aQMgr_get_random_msg_no(cloth_msg, looks, 3);
        mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR13, pid->player_name, PLAYER_NAME_LEN);
        mQst_SetItemNameStr(animal->present_cloth, mMsg_ITEM_STR0);
        memory->letter_info.wearing_present_cloth = FALSE;
        animal->present_cloth = EMPTY_NO;
    }

    return msg_no;
}

static int aQMgr_get_hello_msg_npc_feel_grad(int last_meet_time_type, int looks,
                                             aQMgr_GET_TIME_KIND_PROC get_time_kind_proc) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int msg_no = -1;

    if (last_meet_time_type == aQMgr_MEET_TIME_FIRST_HELLO) {
        if (mEv_IsEventActive(mEv_EVENT_SPRING_CLEANING) == TRUE) {
            msg_no = aQMgr_get_random_msg_no(MSG_15297, looks, 3);
        } else if (mEv_IsEventActive(mEv_EVENT_APRILFOOLS_DAY) == TRUE) {
            msg_no = aQMgr_get_random_msg_no(MSG_15236, looks, 3);
        }
    }

    if (msg_no == -1) {
        int hello_msg = l_grad_hello_msg_tbl[last_meet_time_type];

        msg_no = aQMgr_actor_get_my_hello_msg_com(get_time_kind_proc, hello_msg, looks, rtc_time->hour, 3);
    }

    return msg_no;
}

static void aQMgr_set_feel_normal() {
    mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 0, 0xFF);
    mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 2, 5);
}

static int aQMgr_get_hello_msg_how_do_you_do(NPC_ACTOR* client, aQMgr_GET_TIME_KIND_PROC get_time_kind_proc,
                                             int last_meet_time_type) {
    Animal_c* animal = client->npc_info.animal;
    mNpc_NpcList_c* npclist = client->npc_info.list;
    int feel = animal->mood;
    int looks = mNpc_GetNpcLooks((ACTOR*)client);
    int msg_no;

    if (animal->moved_in == TRUE) {
        msg_no =
            aQMgr_actor_get_my_hello_msg_com(get_time_kind_proc, MSG_11573, looks, Common_Get(time.rtc_time).hour, 3);
    } else if (mLd_CheckThisLand(animal->id.land_name, animal->id.land_id) == FALSE) {
        msg_no =
            aQMgr_actor_get_my_hello_msg_com(get_time_kind_proc, MSG_11666, looks, Common_Get(time.rtc_time).hour, 3);
    } else if (feel == mNpc_FEEL_HAPPY) {
        msg_no = aQMgr_get_hello_msg_npc_feel_grad(last_meet_time_type, looks, get_time_kind_proc);
    } else {
        msg_no = aQMgr_get_hello_msg_npc_feel_normal(animal, looks, last_meet_time_type, get_time_kind_proc);

        if (msg_no != -1 && (feel == mNpc_FEEL_ANGRY || feel == mNpc_FEEL_SAD || feel == mNpc_FEEL_SLEEPY ||
                             feel == mNpc_FEEL_UZAI_0 || feel == mNpc_FEEL_UZAI_1)) {
            aQMgr_set_feel_normal();
        }
    }

    if (npclist != NULL) {
        npclist->conversation_flags.beesting = FALSE;
    }

    return msg_no;
}

static int aQMgr_check_possession_item(mActor_name_t ignore_item) {
    static u8 category[] = { ITEM1_CAT_CARPET, ITEM1_CAT_WALL };
    Private_c* priv = Common_Get(now_private);
    int res = FALSE;

    if (mPr_GetPossessionItemIdxFGTypeWithCond_cancel(priv, NAME_TYPE_FTR0, mPr_ITEM_COND_NORMAL, ignore_item) != -1 ||
        mPr_GetPossessionItemIdxFGTypeWithCond_cancel(priv, NAME_TYPE_FTR1, mPr_ITEM_COND_NORMAL, ignore_item) != -1) {
        res = TRUE;
    } else {
        u8* category_p = category;
        int i;

        for (i = 0; i < ARRAY_COUNT(category); i++) {
            if (mPr_GetPossessionItemIdxItem1CategoryWithCond_cancel(priv, *category_p, mPr_ITEM_COND_NORMAL,
                                                                     ignore_item) != -1) {
                res = TRUE;
                break;
            }

            category_p++;
        }
    }

    return res;
}

static int aQMgr_get_harvestfestival_msg(mNpc_NpcList_c* npclist, int looks) {
    static u8 str0[mMsg_FREE_STRING_LEN];
    static u8 str1[mMsg_FREE_STRING_LEN];

    int msg_no;
    int bx = 0;
    int bz = 0;
    int ev_bx = 0;
    int ev_bz = 0;
    mEv_place_data_c* harvestfestival_place = mEv_get_common_place(mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN, 81);

    msg_no = aQMgr_get_random_msg_no(MSG_15200, looks, 3);
    if (harvestfestival_place != NULL) {
        if (harvestfestival_place->block.x > 0 && harvestfestival_place->block.x < 7) {
            ev_bx = harvestfestival_place->block.x;
        }

        if (harvestfestival_place->block.z > 0 && harvestfestival_place->block.z < 8) {
            ev_bz = harvestfestival_place->block.z;
        }
    }

    if (mFI_Wpos2BlockNum(&bx, &bz, npclist->position) == TRUE) {
        if (bx == ev_bx) {
            ev_bx = 0;
        }

        if (bz == ev_bz) {
            ev_bz = 0;
        }
    }

    mem_clear(str0, sizeof(str0), CHAR_SPACE);
    mString_Load_StringFromRom(str0, sizeof(str0), 0x775 + ev_bx);
    mem_clear(str1, sizeof(str1), CHAR_SPACE);
    mString_Load_StringFromRom(str1, sizeof(str1), 0x76E + ev_bz);

    mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR1, str0, sizeof(str0)); // column
    mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR0, str1, sizeof(str1)); // row

    return msg_no;
}

static int aQMgr_get_harvestfestival_island_msg(int looks) {
    static u8 str0[mMsg_FREE_STRING_LEN];
    static u8 str1[mMsg_FREE_STRING_LEN];

    int msg_no;
    int ev_bx = 0;
    int ev_bz = 0;
    mEv_place_data_c* harvestfestival_place = mEv_get_common_place(mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN, 81);

    msg_no = aQMgr_get_random_msg_no(MSG_15218, looks, 3);
    if (harvestfestival_place != NULL) {
        if (harvestfestival_place->block.x > 0 && harvestfestival_place->block.x < 7) {
            ev_bx = harvestfestival_place->block.x;
        }

        if (harvestfestival_place->block.z > 0 && harvestfestival_place->block.z < 8) {
            ev_bz = harvestfestival_place->block.z;
        }
    }

    mem_clear(str0, sizeof(str0), CHAR_SPACE);
    mString_Load_StringFromRom(str0, sizeof(str0), 0x775 + ev_bx);
    mem_clear(str1, sizeof(str1), CHAR_SPACE);
    mString_Load_StringFromRom(str1, sizeof(str1), 0x76E + ev_bz);

    mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR1, str0, sizeof(str0)); // column
    mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR0, str1, sizeof(str1)); // row

    return msg_no;
}

static int aQMgr_get_hello_msg_no_normal(NPC_ACTOR* client, aQMgr_GET_TIME_KIND_PROC get_time_kind_proc,
                                         int last_meet_time_type) {
    Animal_c* animal = client->npc_info.animal;
    mNpc_NpcList_c* npclist = client->npc_info.list;
    int destiny = Common_Get(now_private)->destiny.type;
    int feel = animal->mood;
    int looks = mNpc_GetNpcLooks((ACTOR*)client);
    int msg_no;

    if (feel == mNpc_FEEL_PITFALL) {
        msg_no = aQMgr_get_random_msg_no(MSG_8327, looks, 3);

        if (last_meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
            aQMgr_clear_memory(animal, animal->memories);
        }

        npclist->conversation_flags.beesting = FALSE;
    } else if (Common_Get(player_bee_chase_flag)) {
        msg_no = aQMgr_get_random_msg_no(MSG_10988, looks, 3);

        if (last_meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
            aQMgr_clear_memory(animal, animal->memories);
        }

        npclist->conversation_flags.beesting = FALSE;
    } else if (last_meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
        msg_no = aQMgr_get_hello_msg_how_do_you_do(client, get_time_kind_proc, last_meet_time_type);
    } else if (mPr_GetFishCompTalkPermission() == TRUE && mNpc_GetFishCompleteTalk(npclist) != TRUE &&
               mPr_GetInsectCompTalkPermission() == TRUE && mNpc_GetInsectCompleteTalk(npclist) != TRUE) {
        int type = mQst_GetRandom(4) & 1;

        msg_no = aQMgr_get_random_msg_no(MSG_10700 + type * 18, looks, 3);
        if (type == 0) {
            mNpc_SetInsectCompleteTalk(npclist);
            mPr_SetInsectCompleteTalk();
        } else {
            mNpc_SetFishCompleteTalk(npclist);
            mPr_SetFishCompleteTalk();
        }

        npclist->conversation_flags.beesting = FALSE;
    } else if (mNpc_GetInsectCompleteTalk(npclist) != TRUE && mPr_GetInsectCompTalkPermission() == TRUE) {
        msg_no = aQMgr_get_random_msg_no(MSG_10700, looks, 3);
        mNpc_SetInsectCompleteTalk(npclist);
        mPr_SetInsectCompleteTalk();
        npclist->conversation_flags.beesting = FALSE;
    } else if (mNpc_GetFishCompleteTalk(npclist) != TRUE && mPr_GetFishCompTalkPermission() == TRUE) {
        msg_no = aQMgr_get_random_msg_no(MSG_10718, looks, 3);
        mNpc_SetFishCompleteTalk(npclist);
        mPr_SetFishCompleteTalk();
        npclist->conversation_flags.beesting = FALSE;
    } else if (npclist->conversation_flags.beesting == TRUE) {
        msg_no =
            aQMgr_actor_get_my_hello_msg_com(get_time_kind_proc, MSG_6987, looks, Common_Get(time.rtc_time).hour, 3);
        npclist->conversation_flags.beesting = FALSE;
    } else if (feel == mNpc_FEEL_ANGRY || feel == mNpc_FEEL_SAD || feel == mNpc_FEEL_SLEEPY ||
               feel == mNpc_FEEL_UZAI_0 || feel == mNpc_FEEL_UZAI_1) {
        msg_no = aQMgr_get_hello_msg_npc_feel(feel, looks);
    } else if (destiny == mPr_DESTINY_UNPOPULAR) {
        msg_no = aQMgr_get_random_msg_no(MSG_1869, looks, 3);
    } else if (mNpc_GetPresentClothMemoryIdx(animal->memories) != -1) {
        msg_no = aQMgr_get_thanks_cloth_msg(animal, looks);
    } else if (mEv_IsEventActive(mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN) == TRUE) {
        msg_no = aQMgr_get_harvestfestival_msg(npclist, looks);
    } else if (feel == mNpc_FEEL_HAPPY) {
        msg_no = aQMgr_get_hello_msg_npc_feel_grad(last_meet_time_type, looks, get_time_kind_proc);
    } else {
        msg_no = aQMgr_get_hello_msg_npc_feel_normal(animal, looks, last_meet_time_type, get_time_kind_proc);
    }

    return msg_no;
}

static int aQMgr_get_hello_msg_no_kamakura(NPC_ACTOR* client, aQMgr_GET_TIME_KIND_PROC get_time_kind_proc,
                                           int last_meet_time_type, mActor_name_t ignore_item) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    static int hello_msg[] = { MSG_6367, MSG_6376, MSG_6358, MSG_6385, MSG_6394, MSG_6403 };
    int msg_no;

    if (last_meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
        msg_no = aQMgr_get_hello_msg_how_do_you_do(client, get_time_kind_proc, last_meet_time_type);
    } else {
        int looks = mNpc_GetNpcLooks((ACTOR*)client);
        int hello_type = 0;

        if (mPr_GetPossessionItemIdx(Common_Get(now_private), EMPTY_NO) != -1 &&
            Common_Get(now_private)->inventory.wallet >= aQMgr_GREETING_GAME_BELL_MIN) {
            hello_type |= aQMgr_GREETING_GAME_TYPE_MONEY;
        }

        if (aQMgr_check_possession_item(ignore_item) == TRUE) {
            hello_type |= aQMgr_GREETING_GAME_TYPE_ITEM;
        }

        if (hello_type == aQMgr_GREETING_GAME_TYPE_ALL) {
            int rng = RANDOM(2);

            msg_no = 1 + hello_msg[looks] + rng;
        } else {
            msg_no = hello_msg[looks] + hello_type;
        }
    }

    return msg_no;
}

static int aQMgr_get_hello_msg_no_summercamp(NPC_ACTOR* client, aQMgr_GET_TIME_KIND_PROC get_time_kind_proc,
                                             int last_meet_time_type, mActor_name_t ignore_item) {
    static int msg_table[] = { MSG_16002, MSG_16032, MSG_16063, MSG_16093, MSG_16123, MSG_16153 };
    int looks = mNpc_GetNpcLooks((ACTOR*)client);
    int hello_type = 0;
    int msg_no;

    if (last_meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
        msg_no =
            aQMgr_actor_get_my_hello_msg_com(get_time_kind_proc, MSG_15930, looks, Common_Get(time.rtc_time).hour, 3);
    } else {
        if (mPr_GetPossessionItemIdx(Common_Get(now_private), EMPTY_NO) != -1 &&
            Common_Get(now_private)->inventory.wallet >= aQMgr_GREETING_GAME_BELL_MIN) {
            hello_type |= aQMgr_GREETING_GAME_TYPE_MONEY;
        }

        if (aQMgr_check_possession_item(ignore_item) == TRUE) {
            hello_type |= aQMgr_GREETING_GAME_TYPE_ITEM;
        }

        if (hello_type == aQMgr_GREETING_GAME_TYPE_ALL) {
            int rng = RANDOM(2);

            msg_no = 1 + msg_table[looks] + rng;
        } else {
            msg_no = msg_table[looks] + hello_type;
        }
    }

    return msg_no;
}

static int aQMgr_get_hello_msg_no_island(NPC_ACTOR* client, aQMgr_GET_TIME_KIND_PROC get_time_kind_proc,
                                         int last_meet_time_type) {
    Animal_c* animal = client->npc_info.animal;
    mNpc_NpcList_c* npclist = client->npc_info.list;
    int destiny = Common_Get(now_private)->destiny.type;
    int feel = animal->mood;
    int looks = mNpc_GetNpcLooks((ACTOR*)client);
    int msg_no;

    if (feel == mNpc_FEEL_PITFALL) {
        msg_no = aQMgr_get_random_msg_no(MSG_13382, looks, 3);

        if (last_meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
            aQMgr_clear_memory(animal, animal->memories);
        }

        npclist->conversation_flags.beesting = FALSE;
    } else if (last_meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
        msg_no = aQMgr_get_hello_msg_npc_feel_normal_island(animal, looks, last_meet_time_type, get_time_kind_proc);
        npclist->conversation_flags.beesting = FALSE;
    } else if (npclist->conversation_flags.beesting == TRUE) {
        msg_no = aQMgr_get_random_msg_no(MSG_13424, looks, 1);
        npclist->conversation_flags.beesting = FALSE;
    } else if (feel == mNpc_FEEL_ANGRY || feel == mNpc_FEEL_SAD || feel == mNpc_FEEL_SLEEPY ||
               feel == mNpc_FEEL_UZAI_0 || feel == mNpc_FEEL_UZAI_1) {
        msg_no = aQMgr_get_hello_msg_npc_feel_island(feel, looks);
    } else if (destiny == mPr_DESTINY_UNPOPULAR) {
        msg_no = aQMgr_get_random_msg_no(MSG_13520, looks, 3);
    } else if (mEv_IsEventActive(mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN) == TRUE) {
        msg_no = aQMgr_get_harvestfestival_island_msg(looks);
    } else {
        msg_no = aQMgr_get_hello_msg_npc_feel_normal_island(animal, looks, last_meet_time_type, get_time_kind_proc);
    }

    return msg_no;
}

extern int aQMgr_get_hello_msg_no(ACTOR* client, aQMgr_GET_TIME_KIND_PROC get_time_kind_proc, mActor_name_t give_item) {
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal;
    int msg_no;
    int weeks = -1;
    int months = -1;
    int last_meet_time_type = aQMgr_get_meet_time(animal, animal->memories, &months, &weeks);

    if (last_meet_time_type == aQMgr_MEET_TIME_HELLO_HOW_DO_YOU_DO) {
        aQMgr_set_memory(animal, animal->memories);
    }

    if (mNpc_CheckIslandAnimal(animal) == TRUE) {
        msg_no = aQMgr_get_hello_msg_no_island((NPC_ACTOR*)client, get_time_kind_proc, last_meet_time_type);
    } else if (client->npc_id == SP_NPC_EV_KAMAKURA_0) {
        msg_no =
            aQMgr_get_hello_msg_no_kamakura((NPC_ACTOR*)client, get_time_kind_proc, last_meet_time_type, give_item);
    } else if (client->npc_id == SP_NPC_EV_SUMMERCAMP_0) {
        msg_no =
            aQMgr_get_hello_msg_no_summercamp((NPC_ACTOR*)client, get_time_kind_proc, last_meet_time_type, give_item);
    } else {
        msg_no = aQMgr_get_hello_msg_no_normal((NPC_ACTOR*)client, get_time_kind_proc, last_meet_time_type);
    }

    aQMgr_actor_set_day_str(months, mMsg_FREE_STR7);
    aQMgr_actor_set_day_str(weeks, mMsg_FREE_STR8);
    return msg_no;
}
