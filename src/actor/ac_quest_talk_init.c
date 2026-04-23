#include "ac_quest_talk_init.h"

#include "m_common_data.h"
#include "m_item_name.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_string.h"
#include "libultra/libultra.h"

enum {
    aQMgr_CHECK_TO,
    aQMgr_CHECK_FROM,

    aQMgr_CHECK_OWN_NUM
};

enum {
    aQMgr_QUEST_TYPE_FJ,
    aQMgr_QUEST_TYPE_QUEST,

    aQMgr_QUEST_TYPE_NUM
};

enum {
    aQMgr_TALK_STEP_SELECT_TALK,
    aQMgr_TALK_STEP_RECONF_OR_NORMAL,
    aQMgr_TALK_STEP_ROOT_RECONF_OR_NORMAL,
    aQMgr_TALK_STEP_NO_OR_NORMAL,
    aQMgr_TALK_STEP_FULL_ITEM_OR_NORMAL,
    aQMgr_TALK_STEP_RENEW_ERRAND_OR_NORMAL,
    aQMgr_TALK_STEP_NEW_QUEST_OR_NORMAL,
    aQMgr_TALK_STEP_NORMAL,
    aQMgr_TALK_STEP_OCCUR_QUEST,
    aQMgr_TALK_STEP_GIVEUP,
    aQMgr_TALK_STEP_GIVEUP_WAIT_BUTTON,
    aQMgr_TALK_STEP_GIVEUP_OPEN_MENU,
    aQMgr_TALK_STEP_GIVEUP_ITEM,
    aQMgr_TALK_STEP_GIVEUP_NPC_ITEM,
    aQMgr_TALK_STEP_FIN_QUEST_START,
    aQMgr_TALK_STEP_TALK_FIN_QUEST_START_NOT_HAND,
    aQMgr_TALK_STEP_FIN_QUEST_REWARD,
    aQMgr_TALK_STEP_FIN_QUEST_THANKS,
    aQMgr_TALK_STEP_AFTER_REWARD,
    aQMgr_TALK_STEP_AFTER_REWARD_THANKS,
    aQMgr_TALK_STEP_WAIT_TALK,
    aQMgr_TALK_STEP_OPEN_MENU,
    aQMgr_TALK_STEP_GET_ITEM,
    aQMgr_TALK_STEP_NPC_GET_ITEM_WAIT,
    aQMgr_TALK_STEP_CHANGE_WAIT,
    aQMgr_TALK_STEP_RENEW_ERRAND_IRAI_END,
    aQMgr_TALK_STEP_RENEW_ERRAND_IRAI_END_GIVE_ITEM,
    aQMgr_TALK_STEP_CONTEST_HOKA_OR_NORMAL,
    aQMgr_TALK_STEP_FINISH_LETTER,
    aQMgr_TALK_STEP_WAIT,
    aQMgr_TALK_STEP_NO_OR_ISLAND,
    aQMgr_TALK_STEP_FINISH
};

static mActor_name_t l_quest_item_list[] = { ITM_QST_VIDEOTAPE,   ITM_QST_ORGANIZER,    ITM_QST_POKEMON_PIKACHU,
                                             ITM_QST_COMIC_BOOK,  ITM_QST_PICTURE_BOOK, ITM_QST_GAME_BOY,
                                             ITM_QST_CAMREA,      ITM_QST_WATCH,        ITM_QST_HANDKERCHIEF,
                                             ITM_QST_GLASSES_CASE };

static int l_reward_msg[] = { 0x011B, 0x00D3, 0x00E5, 0x00F7, 0x0109, 0x013F, 0x012D, 0x081D };

static int l_fruit_reward_msg[] = { 0x011B, 0x00D3, 0x00E5, 0x1146, 0x1158, 0x116A, 0x00E5, 0x081D };

static int l_soccer_reward_msg[] = { 0x0DA3, 0x00D3, 0x00E5, 0x0DB5, 0x0DC7, 0x013F, 0x00E5, 0x081D };

static int l_snowman_reward_msg[] = { 0x0E57, 0x00D3, 0x00E5, 0x0E69, 0x0E7B, 0x013F, 0x00E5, 0x081D };

static int l_flower_reward_msg[] = { 0x0FD9, 0x00D3, 0x00E5, 0x0FEB, 0x0FFD, 0x013F, 0x00E5, 0x081D };

static int l_fish_reward_msg[] = { 0x157A, 0x00D3, 0x00E5, 0x1556, 0x1568, 0x013F, 0x00E5, 0x081D };

static int l_insect_reward_msg[] = { 0x15F8, 0x00D3, 0x00E5, 0x15D4, 0x15E6, 0x013F, 0x00E5, 0x081D };

static int l_after_reward_msg[] = { 0x0304, 0x0000, 0x0000, 0x0316, 0x0328, 0x0000, 0x0000, 0x0000 };

typedef struct quest_manager_quest_info_s {
    int* type_table;
    int type_count;

    int* kind_table[mQst_QUEST_TYPE_NUM];
    int kind_count[mQst_QUEST_TYPE_NUM];
} aQMgr_qst_info_c;

static int l_quest_type_table_fj[] = { mQst_QUEST_TYPE_DELIVERY, mQst_QUEST_TYPE_ERRAND };
static int l_quest_type_table_qst[] = { mQst_QUEST_TYPE_DELIVERY, mQst_QUEST_TYPE_ERRAND, mQst_QUEST_TYPE_CONTEST };

static int l_quest_kind_table_fj_delivery[] = { mQst_DELIVERY_KIND_NORMAL, mQst_DELIVERY_KIND_LOST };
static int l_quest_kind_table_fj_errand[] = { mQst_ERRAND_REQUEST };
static int l_quest_kind_table_qst_delivery[] = { mQst_DELIVERY_KIND_NORMAL, mQst_DELIVERY_KIND_FOREIGN,
                                                 mQst_DELIVERY_KIND_REMOVE, mQst_DELIVERY_KIND_LOST };
static int l_quest_kind_table_qst_errand[] = { mQst_ERRAND_REQUEST };
static int l_quest_kind_table_qst_contest[] = { mQst_CONTEST_KIND_FRUIT,   mQst_CONTEST_KIND_SOCCER,
                                                mQst_CONTEST_KIND_SNOWMAN, mQst_CONTEST_KIND_FLOWER,
                                                mQst_CONTEST_KIND_FISH,    mQst_CONTEST_KIND_INSECT,
                                                mQst_CONTEST_KIND_LETTER };

static aQMgr_qst_info_c l_new_fj_quest_info = { l_quest_type_table_fj,
                                                ARRAY_COUNT(l_quest_type_table_fj),

                                                l_quest_kind_table_fj_delivery,
                                                l_quest_kind_table_fj_errand,
                                                NULL,

                                                ARRAY_COUNT(l_quest_kind_table_fj_delivery),
                                                ARRAY_COUNT(l_quest_kind_table_fj_errand),
                                                0 };

static aQMgr_qst_info_c l_new_quest_quest_info = { l_quest_type_table_qst,
                                                   ARRAY_COUNT(l_quest_type_table_qst),

                                                   l_quest_kind_table_qst_delivery,
                                                   l_quest_kind_table_qst_errand,
                                                   l_quest_kind_table_qst_contest,

                                                   ARRAY_COUNT(l_quest_kind_table_qst_delivery),
                                                   ARRAY_COUNT(l_quest_kind_table_qst_errand),
                                                   ARRAY_COUNT(l_quest_kind_table_qst_contest) };

static int aQMgr_actor_check_own_quest(QUEST_MANAGER_ACTOR* manager, int mode) {
    NPC_ACTOR* client = (NPC_ACTOR*)*manager->client;
    Animal_c* animal = client->npc_info.animal;
    aQMgr_regist_c* regist = manager->regist;
    int res = -1;

    if (animal != NULL) {
        AnmPersonalID_c* pid;
        int i;

        for (i = 0; i < aQMgr_REGIST_NUM; i++, regist++) {
            if (regist->quest_info != NULL) {
                if (mode == aQMgr_CHECK_TO) {
                    pid = &regist->to_id;
                } else {
                    pid = &regist->from_id;
                }

                if (mNpc_CheckCmpAnimalPersonalID(&animal->id, pid) == TRUE) {
                    res = i;
                    break;
                }
            }
        }
    }

    return res;
}

static int aQMgr_actor_check_still_reward(QUEST_MANAGER_ACTOR* manager) {
    Animal_c* animal = ((NPC_ACTOR*)*manager->client)->npc_info.animal;
    aQMgr_regist_c* regist = manager->regist;
    int idx = -1;
    AnmPersonalID_c* anm_id = &animal->id;
    int i;
    PersonalID_c* pid = &Common_Get(now_private)->player_ID;

    if (anm_id != NULL) {

        for (i = 0; i < aQMgr_REGIST_NUM; i++, regist++) {
            if (regist->quest_info != NULL && regist->quest_info->give_reward == TRUE &&
                mNpc_CheckCmpAnimalPersonalID(anm_id, &regist->to_id) == TRUE &&
                mPr_CheckCmpPersonalID(pid, regist->pid) == TRUE) {
                idx = i;
                break;
            }
        }
    }

    return idx;
}

static int aQMgr_actor_check_fin_step(mQst_base_c* quest_info) {
    int res = FALSE;

    if (quest_info->progress == 0) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_check_finish(aQMgr_regist_c* regist, Animal_c* animal) {
    aQMgr_CHECK_FINISH_PROC check_finish_proc = regist->check_finish_proc;
    mQst_base_c* quest_info = regist->quest_info;
    int res = FALSE;

    if (quest_info != NULL) {
        if (check_finish_proc != NULL) {
            res = (*check_finish_proc)(quest_info, animal);
        } else {
            res = aQMgr_actor_check_fin_step(quest_info);
        }
    }

    return res;
}

static int aQMgr_actor_check_limit(aQMgr_regist_c* regist) {
    mQst_base_c* quest_info = regist->quest_info;
    int res = FALSE;

    if (quest_info != NULL) {
        res = mQst_CheckLimitOver(quest_info);
    }

    return res;
}

static int aQMgr_actor_check_errand_from(QUEST_MANAGER_ACTOR* manager) {
    NPC_ACTOR* client = (NPC_ACTOR*)*manager->client;
    int idx = -1;
    Animal_c* animal = client->npc_info.animal;
    aQMgr_regist_c* regist = manager->regist;
    aQMgr_quest_c* quest;
    int count = 0;

    if (animal != NULL) {
        int i;

        for (i = 0; i < aQMgr_REGIST_NUM; i++, regist++) {
            if (count >= manager->regist_use_no) {
                break;
            }

            quest = (aQMgr_quest_c*)regist->quest_info;
            if (quest != NULL) {
                if (quest->base.quest_type == mQst_QUEST_TYPE_ERRAND &&
                    (quest->errand.errand_type == mQst_ERRAND_REQUEST_CONTINUE &&
                     mNpc_CheckCmpAnimalPersonalID(&animal->id, &quest->errand.info.chain.used_ids[0]) == TRUE)) {
                    idx = i;
                    break;
                }

                count++;
            }
        }
    }

    return idx;
}

static int aQMgr_actor_check_client_quest_info(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;

    if (aQMgr_GET_CLIENT(manager)->npc_info.list->quest_info.quest_type != mQst_QUEST_TYPE_NONE) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_get_errand_next_idx(aQMgr_regist_c* regist) {
    mQst_errand_c* errand;
    int idx = -1;

    if (regist != NULL && regist->quest_info != NULL && regist->animal_idx >= 0 && regist->animal_idx < 5) {
        errand = (mQst_errand_c*)regist->quest_info;

        if (errand->base.quest_type == mQst_QUEST_TYPE_ERRAND) {
            idx = regist->animal_idx;
        }
    }

    return idx;
}

static int aQMgr_actor_set_errand_next(u8* next, aQMgr_regist_c* regist, u8 kind) {
    int idx = aQMgr_actor_get_errand_next_idx(regist);

    if (idx >= 0 && idx < mPr_ERRAND_QUEST_NUM) {
        next[idx] = kind;
    }
}

static u8 aQMgr_actor_get_errand_next(aQMgr_regist_c* regist, u8* next) {
    u8 kind = mQst_ERRAND_REQUEST;
    int idx = aQMgr_actor_get_errand_next_idx(regist);

    if (idx >= 0 && idx < mPr_ERRAND_QUEST_NUM) {
        kind = next[idx];
    }

    return kind;
}

static int aQMgr_actor_check_free_quest(mQst_base_c* quest_info) {
    int res = FALSE;

    if (quest_info != NULL && quest_info->quest_type == mQst_QUEST_TYPE_NONE) {
        res = TRUE;
    }

    return res;
}

static void aQMgr_actor_get_free_quest_p(QUEST_MANAGER_ACTOR* manager, int type) {
    AnmPersonalID_c* client_id = &aQMgr_GET_CLIENT_ANIMAL(manager)->id;
    mQst_contest_c* client_contest = &aQMgr_GET_CLIENT_ANIMAL(manager)->contest_quest;
    mQst_base_c** free_data_p = &manager->target.free_data_p;
    Private_c* priv = Common_Get(now_private);
    mActor_name_t item;
    mActor_name_t* pockets = priv->inventory.pockets;
    Animal_c* animal = Save_Get(animals);
    int idx = -1;
    int i;

    *free_data_p = NULL;
    switch (type) {
        case mQst_QUEST_TYPE_DELIVERY: {
            for (i = 0; i < mPr_POCKETS_SLOT_COUNT; i++) {
                if (aQMgr_actor_check_free_quest(&priv->deliveries[i].base) == TRUE && pockets[i] == EMPTY_NO) {
                    manager->target.quest_inv_item_idx = i;
                    *free_data_p = &priv->deliveries[i].base;
                    idx = i;
                    break;
                }
            }
            break;
        }

        case mQst_QUEST_TYPE_ERRAND: {
            for (i = 0; i < mPr_ERRAND_QUEST_NUM; i++) {
                if (aQMgr_actor_check_free_quest(&priv->errands[i].base) == TRUE) {
                    *free_data_p = &priv->errands[i].base;
                    idx = i;
                    break;
                }
            }
            break;
        }

        case mQst_QUEST_TYPE_CONTEST: {
            if (aQMgr_actor_check_free_quest(&client_contest->base) == TRUE) {
                for (i = 0; i < ANIMAL_NUM_MAX; i++, animal++) {
                    if (mNpc_CheckCmpAnimalPersonalID(&animal->id, client_id) == TRUE) {
                        *free_data_p = &animal->contest_quest.base;
                        idx = i;
                        break;
                    }
                }
            }
            break;
        }
    }

    manager->target.free_data_idx = idx;
}

static void aQMgr_actor_set_client_quest_info(QUEST_MANAGER_ACTOR* manager) {
    mQst_CopyQuestInfo(&((NPC_ACTOR*)*manager->client)->npc_info.list->quest_info, &manager->target.quest_info);
}

static void aQMgr_actor_client_quest_set_new(QUEST_MANAGER_ACTOR* manager) {
    mQst_CopyQuestInfo(&manager->target.quest_info, &((NPC_ACTOR*)*manager->client)->npc_info.list->quest_info);
}

static void aQMgr_actor_decide_quest_type_kind(int* type, int* kind) {
    static aQMgr_qst_info_c* type_kind_decide_table[aQMgr_QUEST_TYPE_NUM] = { &l_new_fj_quest_info,
                                                                              &l_new_quest_quest_info };
    aQMgr_qst_info_c* tbl_p;
    int* kind_tbl_p;
    u32 fj_event = mEv_SAVED_FIRSTJOB_PLR0 + Common_Get(player_no);
    int choose_type = aQMgr_QUEST_TYPE_QUEST;

    if (mLd_PlayerManKindCheck() == FALSE && mEv_CheckEvent(fj_event) == TRUE) {
        choose_type = aQMgr_QUEST_TYPE_FJ;
    }

    tbl_p = type_kind_decide_table[choose_type];
    *type = tbl_p->type_table[mQst_GetRandom(tbl_p->type_count)];

    kind_tbl_p = tbl_p->kind_table[*type];
    *kind = kind_tbl_p[mQst_GetRandom(tbl_p->kind_count[*type])];
}

static int aQMgr_get_before_quest_idx(int type, int kind) {
    mNpc_NpcList_c* npclist = Common_Get(npclist);
    int i;
    int res = -1;

    for (i = 0; i < ANIMAL_NUM_MAX; i++, npclist++) {
        if (mQst_CheckFreeQuest(&npclist->quest_info) == FALSE && npclist->quest_info.quest_type == type &&
            npclist->quest_info.quest_kind == kind) {
            res = i;
            break;
        }
    }

    return res;
}

static int aQMgr_actor_check_occur(u32 type, u32 kind, Animal_c* animal, int home_bx, int home_bz) {
    lbRTC_time_c* rtc_time = Common_GetPointer(time.rtc_time);
    int occur = FALSE;
    int animal_idx = -1;

    if (type == mQst_QUEST_TYPE_CONTEST) {
        // Contest kind can't already be active
        if (mQst_GetOccuredContestIdx(kind) == -1) {
            switch (kind) {
                case mQst_CONTEST_KIND_FRUIT:
                    occur = TRUE;
                    break;
                case mQst_CONTEST_KIND_SOCCER:
                    occur = TRUE;
                    break;
                case mQst_CONTEST_KIND_SNOWMAN:
                    if (((rtc_time->month == lbRTC_JANUARY) ||
                         (rtc_time->month == lbRTC_FEBRUARY && rtc_time->day <= 17) ||
                         (rtc_time->month == lbRTC_DECEMBER && rtc_time->day >= 25)) &&
                        (rtc_time->hour >= 8 && rtc_time->hour <= 16)) {
                        occur = TRUE;
                    }
                    break;
                case mQst_CONTEST_KIND_FLOWER:
                    if (((rtc_time->month == lbRTC_FEBRUARY && rtc_time->day >= 25) ||
                         (rtc_time->month >= lbRTC_MARCH && rtc_time->month <= lbRTC_AUGUST)) &&
                        (mQst_GetNullNoNum(home_bx, home_bz) >= 4) && (mQst_GetFlowerNum(home_bx, home_bz) <= 20)) {
                        occur = TRUE;
                    }
                    break;
                case mQst_CONTEST_KIND_FISH:
                    occur = TRUE;
                    break;
                case mQst_CONTEST_KIND_INSECT:
                    if (((rtc_time->month >= lbRTC_MARCH) && (rtc_time->month <= lbRTC_OCTOBER)) ||
                        (rtc_time->month == lbRTC_NOVEMBER && rtc_time->day <= 28)) {
                        occur = TRUE;
                    }
                    break;
                case mQst_CONTEST_KIND_LETTER:
                    if (mLd_PlayerManKindCheck() == FALSE) {
                        occur = TRUE;
                    }
                    break;
            }
        }
    } else if (type == mQst_QUEST_TYPE_DELIVERY) {
        if (animal != NULL) {
            animal_idx = mNpc_SearchAnimalinfo(Save_Get(animals), animal->id.npc_id, ANIMAL_NUM_MAX);
        }

        switch (kind) {
            case mQst_DELIVERY_KIND_FOREIGN: {
                int before_idx = aQMgr_get_before_quest_idx(mQst_QUEST_TYPE_DELIVERY, mQst_DELIVERY_KIND_FOREIGN);
                int occured_idx = mQst_GetOccuredDeliveryIdx(mQst_DELIVERY_KIND_FOREIGN);

                if (occured_idx == -1 && (before_idx == -1 || before_idx == animal_idx) &&
                    mNpc_CheckFreeAnimalPersonalID(&Common_Get(now_private)->stored_anm_id) == FALSE) {
                    occur = TRUE;
                }

                break;
            }

            case mQst_DELIVERY_KIND_REMOVE: {
                int before_idx = aQMgr_get_before_quest_idx(mQst_QUEST_TYPE_DELIVERY, mQst_DELIVERY_KIND_REMOVE);
                int occured_idx = mQst_GetOccuredDeliveryIdx(mQst_DELIVERY_KIND_REMOVE);

                if (occured_idx == -1 && (before_idx == -1 || before_idx == animal_idx) &&
                    mNpc_CheckFreeAnimalPersonalID(Save_GetPointer(last_removed_animal_id)) == FALSE) {
                    occur = TRUE;
                }

                break;
            }

            default:
                occur = TRUE;
                break;
        }
    } else if (type == mQst_QUEST_TYPE_ERRAND) {
        occur = TRUE;
    }

    return occur;
}

static int aQMgr_actor_decide_quest(QUEST_MANAGER_ACTOR* manager) {
    Animal_c* client_animal = ((NPC_ACTOR*)*manager->client)->npc_info.animal;
    aQMgr_target_c* target = &manager->target;
    int res = FALSE;

    if (aQMgr_actor_check_client_quest_info(manager) == TRUE) {
        aQMgr_actor_client_quest_set_new(manager);
        aQMgr_actor_get_free_quest_p(manager, target->quest_info.quest_type);

        if (target->free_data_p != NULL) {
            res = TRUE;
        } else if (target->quest_info.quest_type == mQst_QUEST_TYPE_DELIVERY) {
            aQMgr_actor_set_client_quest_info(manager);
        }
    } else if (mQst_GetRandom(4) != 0) {
        int occur;
        int type;
        int kind;

        aQMgr_actor_decide_quest_type_kind(&type, &kind);
        occur = aQMgr_actor_check_occur(type, kind, client_animal, client_animal->home_info.block_x,
                                        client_animal->home_info.block_z);

        if (occur == TRUE) {
            target->quest_info.quest_type = type;
            target->quest_info.quest_kind = kind;
            aQMgr_actor_get_free_quest_p(manager, target->quest_info.quest_type);

            if (target->free_data_p != NULL) {
                res = TRUE;
            } else if (target->quest_info.quest_type == mQst_QUEST_TYPE_DELIVERY) {
                aQMgr_actor_set_client_quest_info(manager);
            }
        }
    }

    return res;
}

static void aQMgr_actor_decide_item(mActor_name_t* item) {
    *item = l_quest_item_list[RANDOM(ARRAY_COUNT(l_quest_item_list))];
}

static void aQMgr_actor_decide_cloth(mActor_name_t* item, mActor_name_t exclude_item) {
    mSP_SelectRandomItem_New(NULL, item, 1, &exclude_item, 1, mSP_KIND_CLOTH, mSP_LISTTYPE_ABC, FALSE);
}

static void aQMgr_actor_set_contest_work_data(int kind, aQMgr_work_data_c* work, Animal_c* animal) {
    switch (kind) {
        case mQst_CONTEST_KIND_FLOWER: {
            work->flower.exist_num = mQst_GetFlowerSeedNum(animal->home_info.block_x, animal->home_info.block_z);
            work->flower.goal_num = work->flower.exist_num + aQMgr_FLOWER_GOAL_NUM;
            work->flower.remain_num = aQMgr_FLOWER_GOAL_NUM;

            break;
        }
    }
}

static void aQMgr_actor_set_work_data(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_target_c* target = &manager->target;
    mQst_base_c* quest_info = &target->quest_info;

    switch (quest_info->quest_type) {
        case mQst_QUEST_TYPE_CONTEST:
            aQMgr_actor_set_contest_work_data(quest_info->quest_kind, &target->work,
                                              ((NPC_ACTOR*)*manager->client)->npc_info.animal);
            break;
        case mQst_QUEST_TYPE_DELIVERY:
        case mQst_QUEST_TYPE_ERRAND:
            break;
    }
}

static int aQMgr_actor_set_quest_data(QUEST_MANAGER_ACTOR* manager, aQMgr_quest_c* quest) {
    Animal_c* animal = aQMgr_GET_CLIENT_ANIMAL(manager);
    AnmPersonalID_c* from_id = &aQMgr_GET_CLIENT_ANIMAL(manager)->id;
    AnmPersonalID_c* to_id;
    AnmPersonalID_c exclude_ids[mQst_ERRAND_CHAIN_ANIMAL_NUM + 1];
    aQMgr_target_c* target = &manager->target;
    aQMgr_set_data_c* set_data_p = target->set_data_p;
    Private_c* priv = Common_Get(now_private);
    int i;

    if (set_data_p == NULL) {
        return aQMgr_NEW_QUEST_ERROR;
    }

    target->from_id = &animal->id;

    // Set the recipient
    switch (set_data_p->to_type) {
        case aQMgr_QUEST_TARGET_RANDOM: {
            target->to_id = mNpc_GetOtherAnimalPersonalIDOtherBlock(from_id, 1, animal->home_info.block_x,
                                                                    animal->home_info.block_z, TRUE);

            if (target->to_id == NULL) {
                return aQMgr_NEW_QUEST_ERROR;
            }
            break;
        }

        case aQMgr_QUEST_TARGET_RANDOM_EXCLUDED: {
            for (i = 0; i < ARRAY_COUNT(exclude_ids); i++) {
                mNpc_ClearAnimalPersonalID(&exclude_ids[i]);
            }

            // if the quest exists, assume it's an errand and copy up to the 3 other 'chain' villagers
            if (quest != NULL) {
                for (i = 0; i < mQst_ERRAND_CHAIN_ANIMAL_NUM; i++) {
                    mNpc_CopyAnimalPersonalID(&exclude_ids[i], &quest->errand.info.chain.used_ids[i]);
                }
            }

            // copy the quest giver into the exclusion table
            mNpc_CopyAnimalPersonalID(&exclude_ids[mQst_ERRAND_CHAIN_ANIMAL_NUM], &animal->id);
            target->to_id = mNpc_GetOtherAnimalPersonalIDOtherBlock(
                exclude_ids, ARRAY_COUNT(exclude_ids), animal->home_info.block_x, animal->home_info.block_z, TRUE);

            if (target->to_id == NULL) {
                return aQMgr_NEW_QUEST_ERROR;
            }

            target->errand_type = mQst_ERRAND_TYPE_CHAIN;
            break;
        }

        case aQMgr_QUEST_TARGET_ORIGINAL_TARGET: {
            if (quest != NULL) {
                target->to_id = &quest->errand.info.chain.used_ids[0];
            } else {
                target->to_id = from_id;
            }
            break;
        }

        case aQMgr_QUEST_TARGET_FOREIGN: {
            to_id = &Common_Get(now_private)->stored_anm_id;

            if (mNpc_CheckFreeAnimalPersonalID(to_id) == FALSE) {
                target->to_id = to_id;
            } else {
                return aQMgr_NEW_QUEST_NO_FOREIGN_ID;
            }
            break;
        }

        case aQMgr_QUEST_TARGET_LAST_REMOVE: {
            to_id = &Save_Get(last_removed_animal_id);

            if (mNpc_CheckFreeAnimalPersonalID(to_id) == FALSE) {
                target->to_id = to_id;
            } else {
                return aQMgr_NEW_QUEST_NO_REMOVE_ANIMAL_ID;
            }
            break;
        }

        case aQMgr_QUEST_TARGET_CLIENT: {
            target->to_id = &aQMgr_GET_CLIENT_ANIMAL(manager)->id;
            break;
        }
    }

    // Set the item
    switch (set_data_p->src_item_type) {
        case aQMgr_QUEST_ITEM_RANDOM: {
            aQMgr_actor_decide_item(&target->quest_item);
            break;
        }

        case aQMgr_QUEST_ITEM_FRUIT: {
            target->quest_item = mFI_GetOtherFruit();
            break;
        }

        case aQMgr_QUEST_ITEM_CLOTH: {
            aQMgr_actor_decide_cloth(&target->quest_item, animal->cloth);
            break;
        }

        case aQMgr_QUEST_ITEM_FROM_DATA: {
            target->quest_item = set_data_p->item;
            break;
        }

        case aQMgr_QUEST_ITEM_CURRENT_ITEM: {
            if (quest != NULL) {
                target->quest_item = quest->errand.item;
            } else {
                target->quest_item = ITM_CLOTH001;
            }
            break;
        }

        case aQMgr_QUEST_ITEM_NONE: {
            target->quest_item = EMPTY_NO;
            break;
        }

        default: {
            return aQMgr_NEW_QUEST_ERROR;
        }
    }

    // Set whether an item is being entrusted to the player
    if (set_data_p->handover_item == TRUE) {
        int item_idx = mPr_GetPossessionItemIdx(priv, EMPTY_NO);

        if (item_idx != -1) {
            target->quest_inv_item_idx = item_idx;
        } else {
            target->quest_inv_item_idx = -1;
            return aQMgr_NEW_QUEST_NO_SPACE;
        }
    } else {
        target->quest_inv_item_idx = -1;
    }

    // Set time limit
    if (set_data_p->day_limit != 0) {
        lbRTC_TimeCopy(&target->limit, Common_GetPointer(time.rtc_time));
        lbRTC_Add_DD(&target->limit, set_data_p->day_limit);
        target->quest_info.time_limit_enabled = TRUE;
    } else {
        target->quest_info.time_limit_enabled = FALSE;
    }

    target->quest_info.progress = set_data_p->last_step;
    aQMgr_actor_set_work_data(manager);
    return aQMgr_NEW_QUEST_SUCCESS;
}

static void aQMgr_actor_new_quest(QUEST_MANAGER_ACTOR* manager, int animal_idx, int looks, int* sel_regist_idx,
                                  int regist_idx) {
    aQMgr_quest_c* quest = NULL;
    aQMgr_regist_c* regist;
    u32 stage = 0;
    int quest_exist;

    if (regist_idx != -1) {
        int next_type;
        u8 next;

        regist = &manager->regist[regist_idx];
        quest = (aQMgr_quest_c*)regist->quest_info; // TODO: maybe quest_info should be aQMgr_quest_c* here?
        manager->target.quest_info.quest_type = quest->base.quest_type;
        next_type = 0;
        next = aQMgr_actor_get_errand_next(regist, manager->errand_next);

        if (next == 0) {
            next_type = RANDOM(2);
        } else if (next <= 2) {
            next_type = next - 1;
        }

        aQMgr_actor_set_errand_next(manager->errand_next, regist, next_type + 1);

        if (next_type == 0) {
            stage = 0;
        } else {
            stage = quest->base.progress - 1;
        }

        if (stage == 0) {
            manager->target.quest_info.quest_kind = mQst_ERRAND_REQUEST_FINAL;
        } else {
            manager->target.quest_info.quest_kind = mQst_ERRAND_REQUEST_CONTINUE;
        }

        manager->target.free_data_p = (mQst_base_c*)quest; // TODO: Again, should this be aQMgr_quest_c*?
        manager->target.free_data_idx = regist->animal_idx;
        *sel_regist_idx = regist_idx;
        quest_exist = TRUE;
    } else {
        quest_exist = aQMgr_actor_decide_quest(manager);
    }

    if (quest_exist == TRUE) {
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_GET_SET_DATA);
        quest_exist = aQMgr_actor_set_quest_data(manager, quest);

        if (quest_exist == aQMgr_NEW_QUEST_SUCCESS) {
            if (regist_idx != -1) {
                aQMgr_regist_c* regist = manager->regist + regist_idx;

                manager->target.from_id = &aQMgr_GET_CLIENT_ANIMAL(manager)->id;

                if (stage != 0) {
                    manager->target.quest_info.progress = stage;
                }

                aQMgr_actor_set_errand_next(manager->errand_next, regist, 0);
            }
        } else if (quest_exist == aQMgr_NEW_QUEST_NO_SPACE) {
            if (manager->target.quest_info.quest_type == mQst_QUEST_TYPE_DELIVERY) {
                aQMgr_actor_set_client_quest_info(manager);
            }

            manager->talk_step = aQMgr_TALK_STEP_FULL_ITEM_OR_NORMAL;
        } else {
            quest_exist = FALSE;
        }
    }

    if (quest_exist == FALSE) {
        if (aQMgr_actor_check_client_quest_info(manager) == TRUE) {
            manager->talk_step = aQMgr_TALK_STEP_FULL_ITEM_OR_NORMAL;
        } else if (manager->target.quest_info.quest_type == mQst_QUEST_TYPE_DELIVERY &&
                   manager->target.set_data_p == NULL) {
            manager->talk_step = aQMgr_TALK_STEP_FULL_ITEM_OR_NORMAL;
            (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_GET_SET_DATA);
        } else {
            manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
            mNpc_SetQuestRequestOFF(animal_idx, looks);
        }

        mQst_ClearQuestInfo(&manager->target.quest_info);
        manager->target.free_data_p = NULL;
        manager->target.free_data_idx = -1;
    }
}

static void aQMgr_actor_set_delivery(aQMgr_target_c* target, AnmPersonalID_c* from_id) {
    mQst_delivery_c* delivery = (mQst_delivery_c*)target->free_data_p;

    mQst_CopyQuestInfo(&delivery->base, &target->quest_info);
    mNpc_CopyAnimalPersonalID(&delivery->sender, from_id);
    mNpc_CopyAnimalPersonalID(&delivery->recipient, target->to_id);
    delivery->base.time_limit = target->limit;
}

static void aQMgr_actor_set_errand(aQMgr_target_c* target, AnmPersonalID_c* from_id) {
    mQst_errand_c* errand = (mQst_errand_c*)target->free_data_p;
    AnmPersonalID_c* pids = errand->info.chain.used_ids;
    int i;

    mQst_CopyQuestInfo(&errand->base, &target->quest_info);
    mNpc_CopyAnimalPersonalID(&errand->sender, from_id);
    mNpc_CopyAnimalPersonalID(&errand->recipient, target->to_id);
    errand->base.time_limit = target->limit;
    errand->item = target->quest_item;
    errand->pockets_idx = target->quest_inv_item_idx;
    errand->errand_type = target->errand_type;

    switch (target->errand_type) {
        case mQst_ERRAND_TYPE_CHAIN: {
            // Clear intermediate chain animals on initial request
            if (target->quest_info.quest_kind == mQst_ERRAND_REQUEST) {
                for (i = 0; i < mQst_ERRAND_CHAIN_ANIMAL_NUM; i++) {
                    mNpc_ClearAnimalPersonalID(&pids[i]);
                    errand->info.chain.used_num = 0; // Why is this in the loop?
                }
            }

            // Copy this villager as a 'chain step' animal
            for (i = 0; i < mQst_ERRAND_CHAIN_ANIMAL_NUM; i++, pids++) {
                if (mNpc_CheckFreeAnimalPersonalID(pids) == TRUE) {
                    mNpc_CopyAnimalPersonalID(pids, from_id);
                    break;
                }
            }

            // Update that an entry in the chain has been used
            errand->info.chain.used_num++;
            break;
        }
    }
}

static void aQMgr_actor_set_contest(aQMgr_target_c* target) {
    mQst_contest_c* contest = (mQst_contest_c*)target->free_data_p;

    mQst_CopyQuestInfo(&contest->base, &target->quest_info);
    contest->base.time_limit = target->limit;
    contest->requested_item = target->quest_item;

    switch (target->quest_info.quest_kind) {
        case mQst_CONTEST_KIND_FRUIT:
            break;
        case mQst_CONTEST_KIND_SOCCER:
            break;
        case mQst_CONTEST_KIND_SNOWMAN:
            break;

        case mQst_CONTEST_KIND_FLOWER: {
            contest->type = mQst_CONTEST_DATA_FLOWER;
            contest->info.flower_data.flowers_requested = target->work.flower.goal_num;
            break;
        }

        case mQst_CONTEST_KIND_FISH:
            break;
        case mQst_CONTEST_KIND_INSECT:
            break;

        case mQst_CONTEST_KIND_LETTER: {
            contest->type = mQst_CONTEST_DATA_LETTER;
            contest->info.letter_data.score = 0;
            contest->info.letter_data.present = EMPTY_NO;
            break;
        }
    }
}

static void aQMgr_actor_set_quest_info(QUEST_MANAGER_ACTOR* manager) {
    Private_c* priv = Common_Get(now_private);
    AnmPersonalID_c* from_id = &aQMgr_GET_CLIENT_ANIMAL(manager)->id;
    aQMgr_target_c* target = &manager->target;
    int type = target->quest_info.quest_type;

    switch (type) {
        case mQst_QUEST_TYPE_DELIVERY:
            aQMgr_actor_set_delivery(target, from_id);
            break;
        case mQst_QUEST_TYPE_ERRAND:
            aQMgr_actor_set_errand(target, from_id);
            break;
        case mQst_QUEST_TYPE_CONTEST:
            aQMgr_actor_set_contest(target);
            break;
    }

    if (target->quest_inv_item_idx != -1) {
        mPr_SetPossessionItem(priv, target->quest_inv_item_idx, target->quest_item, mPr_ITEM_COND_QUEST);
    }
}

static void aQMgr_actor_clear_client_quest_info(QUEST_MANAGER_ACTOR* manager) {
    mQst_ClearQuestInfo(&aQMgr_GET_CLIENT(manager)->npc_info.list->quest_info);
}

static void aQMgr_actor_set_free_str(QUEST_MANAGER_ACTOR* manager, int regist_idx) {
    u8 str1[ANIMAL_NAME_LEN];
    u8 str0[ANIMAL_NAME_LEN];
    u8 str2[mIN_ITEM_NAME_LEN];

    aQMgr_target_c* target = &manager->target;

    mNpc_GetNpcWorldNameAnm(str0, target->from_id);
    mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR0, str0, sizeof(str0));

    if (target->to_id != NULL) {
        mNpc_GetNpcWorldNameAnm(str1, target->to_id);
        mMsg_Set_free_str_cl(mMsg_Get_base_window_p(), mMsg_FREE_STR1, str1, sizeof(str1), 1);
        mLd_SetFreeStrLandMuraName(target->to_id->land_name, mMsg_FREE_STR3);
    }

    if (target->quest_item != EMPTY_NO) {
        mIN_copy_name_str(str2, target->quest_item);
        mMsg_Set_free_str_cl_art(mMsg_Get_base_window_p(), mMsg_FREE_STR2, str2, sizeof(str2), 2,
                                 mIN_get_item_article(target->quest_item));
    }

    mLd_SetFreeStrLandMuraName(target->from_id->land_name, mMsg_FREE_STR4);
    if (regist_idx != -1) {
        aQMgr_regist_c* regist = manager->regist + regist_idx;

        if (regist != NULL) {
            mQst_errand_c* errand = (mQst_errand_c*)regist->quest_info;

            if (errand != NULL && errand->base.quest_type == mQst_QUEST_TYPE_ERRAND) {
                AnmPersonalID_c* anm_id = &errand->info.chain.used_ids[0];

                if (mNpc_CheckFreeAnimalPersonalID(anm_id) == FALSE) {
                    mNpc_GetNpcWorldNameAnm(str1, anm_id);
                    mMsg_Set_free_str_cl(mMsg_Get_base_window_p(), mMsg_FREE_STR5, str1, sizeof(str1), 1);
                }
            }
        }
    }
}

static void aQMgr_actor_set_free_str_reward(aQMgr_target_c* target) {
    u8 str[mIN_ITEM_NAME_LEN];

    if (target->reward_kind == aQMgr_QUEST_REWARD_MONEY) {
        mFont_UnintToString(str, sizeof(str), target->pay, 10, TRUE, FALSE, TRUE);
        mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR9, str, sizeof(str));
    } else {
        mQst_SetItemNameStr(target->reward_item, mMsg_ITEM_STR0);
    }
}

static u32 aQMgr_actor_get_rate(int money_power) {
    // spread, base
    static f32 rate_table[][2] = {
        { 0.3000f, 0.0f },    // [  0,  29]
        { 0.7000f, -40.0f },  // [ 30,  99]
        { 2.7000f, -440.0f }, // [100, 367]
        { 1.3000f, -20.0f },  // [370, 498]
        { 1.0000f, 100.0f },  // [500, 599]
        { 0.6000f, 300.0f },  // [600, 659]
        { 0.0012f, 660.0f }   // [660, 660]
    };

    u32 rate = 0;

    if (money_power > 0) {
        f32 base;
        f32 scale;
        int idx = money_power / 100;

        if (idx >= ARRAY_COUNT(rate_table)) {
            idx = ARRAY_COUNT(rate_table) - 1;
        }

        base = rate_table[idx][1];
        scale = rate_table[idx][0];
        rate = base + scale * (f32)money_power;
    }

    return rate;
}

static u32 aQMgr_actor_get_pay(u32 base_pay) {
    f32 scale = 100.0f;
    static f32 plus_minus[2] = { 1.0f, -1.0f };
    int dir_idx = RANDOM(2);
    f32 percent = fqrand();
    f32 dir = plus_minus[dir_idx];
    u32 pay;
    f32 pay_f;
    f32 final_pay;

    scale += dir * 10.0f * percent;

    pay = aQMgr_actor_get_rate(mPr_GetMoneyPower());

    if (pay > 700) {
        pay = 700;
    }

    // min:  (~90.0 * 100) / 10000 = ~0.91x (max percent = ~1.1x)
    // max: (~109.9 * 760) / 10000 = ~8.36x (min percent = ~6.916x)
    pay_f = 100.0f;
    pay_f += pay;
    final_pay = (scale * pay_f) / 10000.0f;
    final_pay = base_pay * final_pay;
    return final_pay;
}

static int aQMgr_actor_hand_reward(aQMgr_target_c* target) {
    Private_c* priv = Common_Get(now_private);
    int reward_kind = target->reward_kind;
    int inv_idx = target->quest_inv_item_idx;
    int res = FALSE;

    if (reward_kind == aQMgr_QUEST_REWARD_MONEY) {
        u32 money = priv->inventory.wallet;

        money += target->pay;
        if (money > mPr_WALLET_MAX) {
            if (money <= (mPr_WALLET_MAX + mPr_GetPossessionItemSum(priv, EMPTY_NO) * 30000)) {
                if (inv_idx != -1 && priv->inventory.pockets[inv_idx] == EMPTY_NO) {
                    mPr_SetPossessionItem(priv, inv_idx, ITM_MONEY_30000, mPr_ITEM_COND_NORMAL);
                    money -= 30000;
                }

                while (money > mPr_WALLET_MAX) {
                    inv_idx = mPr_GetPossessionItemIdx(priv, EMPTY_NO);

                    if (inv_idx != -1) {
                        mPr_SetPossessionItem(priv, inv_idx, ITM_MONEY_30000, mPr_ITEM_COND_NORMAL);
                        money -= 30000;
                    } else {
                        money = mPr_WALLET_MAX; // ran out of space
                        break;
                    }
                }

                priv->inventory.wallet = money; // remaining money goes in the wallet
                res = TRUE;
            }
        } else {
            priv->inventory.wallet = money;
            res = TRUE;
        }
    } else if (reward_kind != -1) {
        if (inv_idx != -1 && priv->inventory.pockets[inv_idx] == EMPTY_NO) {
            mPr_SetPossessionItem(priv, inv_idx, target->reward_item, mPr_ITEM_COND_NORMAL);
            res = TRUE;
        } else {
            inv_idx = mPr_GetPossessionItemIdx(priv, EMPTY_NO);

            if (inv_idx != -1) {
                mPr_SetPossessionItem(priv, inv_idx, target->reward_item, mPr_ITEM_COND_NORMAL);
                res = TRUE;
            }
        }
    }

    return res;
}

static void aQMgr_actor_get_errand_reward(u8* reward_percents, u32* payment, u8 npc_num) {
    static u8 errand_reward[4][aQMgr_QUEST_REWARD_NUM] = {
        { 0, 75, 25, 0, 0, 0, 0, 0 },   // 75% stationery, 25% clothing
        { 25, 25, 25, 0, 0, 25, 0, 0 }, // 25% ftr, 25% stationery, 25% clothing, 25% money
        { 50, 0, 25, 0, 0, 25, 0, 0 },  // 50% ftr, 25% clothing, 25% money
        { 65, 0, 0, 5, 5, 25, 0, 0 },   // 65% ftr, 5% carpet, 5% wallpaper, 25% money
    };
    u32 reward_pay[4] = { 0, 500, 750, 1000 }; // someone forgot a `static` qualifier here
    u8* reward_p;
    int i;

    npc_num--;
    if (npc_num >= ARRAY_COUNT(reward_pay)) {
        npc_num = ARRAY_COUNT(reward_pay) - 1;
    }

    reward_p = errand_reward[npc_num];
    for (i = 0; i < aQMgr_QUEST_REWARD_NUM; i++) {
        *reward_percents++ = *reward_p++;
    }

    *payment = reward_pay[npc_num];
}

static mActor_name_t aQMgr_actor_get_other_pl_cloth() {
    Private_c* priv = Common_Get(now_private);
    mActor_name_t other_pl_cloth = ITM_CLOTH001;

    if (priv != NULL) {
        aQMgr_actor_decide_cloth(&other_pl_cloth, priv->cloth.item);
    }

    return other_pl_cloth;
}

static void aQMgr_actor_set_reward(QUEST_MANAGER_ACTOR* manager) {
    Animal_c* animal = aQMgr_GET_CLIENT_ANIMAL(manager);
    aQMgr_target_c* target = &manager->target;
    aQMgr_set_data_c* set_data_p = target->set_data_p;
    u32 pay = 0;
    u8 reward_percentages[aQMgr_QUEST_REWARD_NUM];
    u8* reward_percent_p;
    int prob_tbl[100];
    int prob_idx;
    int j;
    int i;

    if (target->quest_info.quest_type == mQst_QUEST_TYPE_ERRAND) {
        aQMgr_actor_get_errand_reward(
            reward_percentages, &pay,
            ((mQst_errand_c*)manager->regist[manager->regist_idx].quest_info)->info.chain.used_num);
        reward_percent_p = reward_percentages;
    } else {
        pay = set_data_p->max_pay;
        reward_percent_p = set_data_p->reward_percentages;
    }

    // 100 slots (1% each), values ranging from 0-7 (aQMgr_QUEST_REWARD_*)
    prob_idx = 0;
    bzero(prob_tbl, sizeof(prob_tbl));
    for (i = 0; i < aQMgr_QUEST_REWARD_NUM; i++) {
        j = reward_percent_p[i];

        while (j != 0) {
            if (prob_idx >= 100) {
                break;
            }

            prob_tbl[prob_idx] = i;
            prob_idx++;
            j--;
        }
    }

    target->reward_kind = prob_tbl[RANDOM(100)];
    if (target->reward_kind == aQMgr_QUEST_REWARD_MONEY) {
        pay = aQMgr_actor_get_pay(pay);
        target->pay = pay;
        target->reward_item = ITM_MONEY_1000;
    } else if (target->reward_kind == aQMgr_QUEST_REWARD_WORN_CLOTH) {
        if (animal != NULL) {
            if (manager->cloth == RSV_CLOTH) {
                target->reward_item = aQMgr_actor_get_other_pl_cloth();
                target->reward_kind = aQMgr_QUEST_REWARD_CLOTH;
            } else {
                target->reward_item = manager->cloth;
            }
        } else {
            target->reward_item = ITM_CLOTH001;
        }
    } else {
        mQst_GetGoods_common(&target->reward_item, &animal->id, target->reward_kind, NULL, 0, mSP_LISTTYPE_ABC);
    }
}

static void aQMgr_talk_quest_clear_quest(QUEST_MANAGER_ACTOR* manager) {
    int regist_idx = manager->regist_idx;

    if (regist_idx != -1) {
        aQMgr_regist_c* regist = manager->regist + regist_idx;
        aQMgr_quest_c* quest = (aQMgr_quest_c*)regist->quest_info;

        switch (quest->base.quest_type) {
            case mQst_QUEST_TYPE_DELIVERY:
                mQst_ClearDelivery(&quest->delivery, 1);
                break;
            case mQst_QUEST_TYPE_ERRAND:
                mQst_ClearErrand(&quest->errand, 1);
                break;
            case mQst_QUEST_TYPE_CONTEST:
                mQst_ClearContest(&quest->contest);
                break;
        }
    }
}

static void aQMgr_actor_talk_finish(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_target_c* target = &manager->target;
    aQMgr_quest_c* free_quest = (aQMgr_quest_c*)target->free_data_p;
    int regist_idx = manager->regist_idx;

    if (regist_idx != -1) {
        aQMgr_talk_quest_clear_quest(manager);
        (*manager->clear_regist_proc)(manager->regist, aQMgr_REGIST_NUM);
    }

    if (free_quest != NULL) {
        int idx = 0;
        (*manager->regist_quest_proc)(manager, &idx, free_quest, target->free_data_idx);
    }
}

static void aQMgr_talk_quest_start_choice_random(int* choice_no, int start, int num) {
    *choice_no = start + mQst_GetRandom(num);
}

static void aQMgr_talk_quest_select_get_choice(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_choice_c* choice = &manager->choice;
    int talk_step = manager->talk_step;
    aQMgr_target_c* target = &manager->target;
    int type = target->quest_info.quest_type;
    int kind = target->quest_info.quest_kind;

    switch (talk_step) {
        case aQMgr_TALK_STEP_RENEW_ERRAND_OR_NORMAL: {
            choice->choice_ids[0] = 0x97; // "I'm picking up!"
            choice->choice_ids[1] = 0x89; // "Let's talk!"
            break;
        }

        case aQMgr_TALK_STEP_FIN_QUEST_START: {
            choice->choice_ids[0] = 0x94; // "Delivery!"

            if (type == mQst_QUEST_TYPE_DELIVERY) {
                if (kind == mQst_DELIVERY_KIND_NORMAL) {
                    choice->choice_ids[0] = 0x94; // "Delivery!"
                } else if (kind == mQst_DELIVERY_KIND_FOREIGN) {
                    choice->choice_ids[0] = 0x95; // "You forgot this!"
                } else if (kind == mQst_DELIVERY_KIND_REMOVE) {
                    choice->choice_ids[0] = 0x95; // "You forgot this!"
                }
            } else if (type == mQst_QUEST_TYPE_ERRAND) {
                switch (kind) {
                    case mQst_ERRAND_REQUEST_FINAL:
                        choice->choice_ids[0] = 0x94; // "Delivery!"
                        break;
                    default:
                        choice->choice_ids[0] = 0x97; // "I'm picking up!"
                        break;
                }
            } else if (type == mQst_QUEST_TYPE_CONTEST) {
                switch (kind) {
                    case mQst_CONTEST_KIND_FRUIT:
                        choice->choice_ids[0] = 0x96; // "It's fruit time!"
                        break;
                    case mQst_CONTEST_KIND_FISH:
                        choice->choice_ids[0] = 0xEA; // "I brought fish."
                        break;
                    case mQst_CONTEST_KIND_INSECT:
                        choice->choice_ids[0] = 0xEB; // "I caught a bug!"
                        break;
                    default:
                        choice->choice_ids[0] = 0x94; // "Delivery!"
                        break;
                }
            }

            aQMgr_talk_quest_start_choice_random(&choice->choice_ids[1], 0x89, 10);
            break;
        }

        case aQMgr_TALK_STEP_TALK_FIN_QUEST_START_NOT_HAND: {
            if (type == mQst_QUEST_TYPE_CONTEST) {
                if (kind == mQst_CONTEST_KIND_SOCCER) {
                    choice->choice_ids[0] = 0x98; // "Here's the ball."
                } else if (kind == mQst_CONTEST_KIND_SNOWMAN) {
                    choice->choice_ids[0] = 0x99; // "Look! Snowman!"
                } else if (kind == mQst_CONTEST_KIND_FLOWER) {
                    choice->choice_ids[0] = 0x9A; // "The flowers..."
                }

                choice->choice_ids[1] = 0x9B; // "Yeah, um..."
            }

            break;
        }

        case aQMgr_TALK_STEP_FULL_ITEM_OR_NORMAL: {
            if (type == mQst_QUEST_TYPE_ERRAND) {
                if (kind == mQst_ERRAND_REQUEST) {
                    choice->choice_ids[0] = 0x97; // "I'm picking up!"
                } else if (kind == mQst_ERRAND_REQUEST_CONTINUE) {
                    choice->choice_ids[0] = 0x97; // "I'm picking up!"
                } else if (kind == mQst_ERRAND_REQUEST_FINAL) {
                    choice->choice_ids[0] = 0x97; // "I'm picking up!"
                }
            } else {
                aQMgr_talk_quest_start_choice_random(&choice->choice_ids[0], 0x7F, 10);
            }

            aQMgr_talk_quest_start_choice_random(&choice->choice_ids[1], 0x89, 10);
            break;
        }

        default: {
            aQMgr_talk_quest_start_choice_random(&choice->choice_ids[0], 0x7F, 10);
            aQMgr_talk_quest_start_choice_random(&choice->choice_ids[1], 0x89, 10);
            break;
        }
    }

    aQMgr_talk_quest_start_choice_random(&choice->choice_ids[2], 0x16A, 5);
    choice->talk_action = -1;
    choice->choice_num = 3;
}

static void aQMgr_talk_quest_select_get_choice_island(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_choice_c* choice = &manager->choice;

    aQMgr_talk_quest_start_choice_random(&choice->choice_ids[0], 0x89, 10);
    aQMgr_talk_quest_start_choice_random(&choice->choice_ids[1], 0x16A, 5);
    choice->talk_action = -1;
    choice->choice_num = 2;
}

static void aQMgr_talk_quest_start_choice(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_choice_c* choice = &manager->choice;

    aQMgr_talk_quest_start_choice_random(&choice->choice_ids[0], 0x43, 10);
    aQMgr_talk_quest_start_choice_random(&choice->choice_ids[1], 0x4D, 10);
    choice->choice_num = 2;
    choice->talk_action = -1;
}

static void aQMgr_talk_quest_finish_firstjob_open_quest() {
    mQst_errand_c* errand = mQst_GetFirstJobData();
    u32 event_id = mEv_SAVED_FIRSTJOB_PLR0 + Common_Get(player_no);

    if (mLd_PlayerManKindCheck() == FALSE && mEv_CheckEvent(event_id) == TRUE && errand != NULL &&
        errand->base.quest_type == mQst_QUEST_TYPE_ERRAND && errand->base.quest_kind == mQst_ERRAND_FIRSTJOB_OPEN &&
        errand->base.progress == 2 && errand->errand_type == mQst_ERRAND_TYPE_FIRST_JOB) {
        errand->base.progress = 0;
    }
}

static void aQMgr_talk_quest_set_cancel_msg_com(QUEST_MANAGER_ACTOR* manager, int base_cancel_msg) {
    manager->msg_category = aQMgr_MSG_KIND_NONE;
    manager->category_msg_no_start = base_cancel_msg;
    manager->choice.talk_action = -1;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_talk_quest_change_normal_or_hint(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 2) {
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        aQMgr_talk_quest_set_cancel_msg_com(manager, 0x254A);
    } else {
        if (*manager->memory != NULL) {
            mNpc_AddFriendship(*manager->memory, 1);
        }

        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_CHANGE_TALK_NORMAL);
    }
}

static int l_contest_hoka_msg_no[mQst_CONTEST_KIND_NUM] = { 0x1134, 0x0E21, 0x0ED5, 0x1057, 0x1544, 0x15C2, 0x1AF3 };

static int aQMgr_talk_quest_get_contest_hoka_msg_no(mQst_contest_c* contest, Animal_c* animal) {
    int kind = contest->base.quest_kind;
    int hoka_msg_no = 0;

    if (kind == mQst_CONTEST_KIND_FLOWER &&
        contest->info.flower_data.flowers_requested >
            mQst_GetFlowerSeedNum(animal->home_info.block_x, animal->home_info.block_z)) {
        hoka_msg_no = 0x1069; // flower quest complete but less flowers than originally requested (some were destroyed)
    }

    if (hoka_msg_no == 0) {
        hoka_msg_no = l_contest_hoka_msg_no[kind];
    }

    return hoka_msg_no;
}

static void aQMgr_talk_quest_set_work(aQMgr_work_data_c* work, int type, int kind) {
    // stubbed
}

static void aQMgr_actor_talk_select_talk(QUEST_MANAGER_ACTOR* manager) {
    Animal_c* animal = aQMgr_GET_CLIENT_ANIMAL(manager);
    int animal_idx = mNpc_SearchAnimalPersonalID(&animal->id);
    aQMgr_quest_c* quest;
    aQMgr_regist_c* regist;
    int sel_regist_idx = -1;
    int regist_idx;
    int target_flag = TRUE;

    regist_idx = aQMgr_actor_check_still_reward(manager);
    if (regist_idx != -1) {
        manager->msg_category = aQMgr_MSG_KIND_AFTER_REWARD;
        manager->talk_step = aQMgr_TALK_STEP_AFTER_REWARD;
    } else {
        regist_idx = aQMgr_actor_check_own_quest(manager, aQMgr_CHECK_TO);

        if (regist_idx != -1) {
            regist = manager->regist + regist_idx;
            quest = (aQMgr_quest_c*)regist->quest_info;

            if (quest->base.quest_type == mQst_QUEST_TYPE_ERRAND &&
                quest->errand.errand_type == mQst_ERRAND_TYPE_FIRST_JOB) {
                manager->talk_state = aQMgr_TALK_STATE_INIT;
                manager->talk_change_type = aQMgr_TALK_KIND_FIRST_JOB;
                manager->talk_step = aQMgr_TALK_STEP_SELECT_TALK;
                target_flag = FALSE;
                mMsg_Set_LockContinue(mMsg_Get_base_window_p());
            } else if (aQMgr_actor_check_finish(regist, animal) == TRUE) {
                manager->category_msg_no_start = 0x2A6;

                if (quest->base.quest_type == mQst_QUEST_TYPE_CONTEST &&
                    quest->base.quest_kind == mQst_CONTEST_KIND_LETTER) {
                    if (mQst_SendRemail(&quest->contest, &animal->id) == TRUE) {
                        manager->talk_step = aQMgr_TALK_STEP_FINISH_LETTER;
                    } else {
                        manager->talk_step = aQMgr_TALK_STEP_CONTEST_HOKA_OR_NORMAL;
                        manager->category_msg_no_start = 0x2A6;
                    }
                } else if (quest->base.quest_type == mQst_QUEST_TYPE_CONTEST &&
                           (quest->base.quest_kind == mQst_CONTEST_KIND_SOCCER ||
                            quest->base.quest_kind == mQst_CONTEST_KIND_SNOWMAN ||
                            quest->base.quest_kind == mQst_CONTEST_KIND_FLOWER)) {
                    mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR12, quest->contest.player_id.player_name,
                                      PLAYER_NAME_LEN);
                    manager->talk_step = aQMgr_TALK_STEP_TALK_FIN_QUEST_START_NOT_HAND;
                } else {
                    manager->talk_step = aQMgr_TALK_STEP_FIN_QUEST_START;
                }
            } else {
                if (quest->base.quest_type == mQst_QUEST_TYPE_ERRAND) {
                    manager->talk_step = aQMgr_TALK_STEP_RENEW_ERRAND_OR_NORMAL;
                    sel_regist_idx = regist_idx;
                    regist_idx = -1;
                } else if (quest->base.quest_type == mQst_QUEST_TYPE_CONTEST) {
                    regist = manager->regist + regist_idx;

                    if (aQMgr_actor_check_limit(regist) == FALSE) {
                        if (quest->base.progress == 0) {
                            if (mPr_CheckCmpPersonalID(&quest->contest.player_id,
                                                       &Common_Get(now_private)->player_ID) == TRUE) {
                                manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
                                mQst_ClearQuestInfo(&manager->target.quest_info);
                                manager->target.free_data_p = NULL;
                                manager->target.free_data_idx = -1;
                                target_flag = FALSE;
                            } else if (mPr_NullCheckPersonalID(&quest->contest.player_id) == FALSE) {
                                manager->talk_step = aQMgr_TALK_STEP_CONTEST_HOKA_OR_NORMAL;
                            } else {
                                manager->talk_step = aQMgr_TALK_STEP_RECONF_OR_NORMAL;
                            }
                        } else if (quest->base.quest_kind == mQst_CONTEST_KIND_LETTER) {
                            if (mLd_PlayerManKindCheck() == FALSE) {
                                manager->talk_step = aQMgr_TALK_STEP_RECONF_OR_NORMAL;
                            } else {
                                manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
                                mQst_ClearQuestInfo(&manager->target.quest_info);
                                manager->target.free_data_p = NULL;
                                manager->target.free_data_idx = -1;
                                target_flag = FALSE;
                            }
                        } else {
                            manager->talk_step = aQMgr_TALK_STEP_RECONF_OR_NORMAL;
                        }
                    } else {
                        manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
                        mQst_ClearQuestInfo(&manager->target.quest_info);
                        manager->target.free_data_p = NULL;
                        manager->target.free_data_idx = -1;
                        target_flag = FALSE;
                        manager->regist_idx = regist_idx;
                        aQMgr_actor_talk_finish(manager);
                    }
                }

                manager->category_msg_no_start = 0x2A6;
            }
        } else {
            regist_idx = aQMgr_actor_check_own_quest(manager, aQMgr_CHECK_FROM);

            if (regist_idx != -1) {
                regist = manager->regist + regist_idx;

                if (aQMgr_actor_check_limit(regist) == FALSE) {
                    manager->talk_step = aQMgr_TALK_STEP_RECONF_OR_NORMAL;
                    manager->category_msg_no_start = 0x2A6;
                } else {
                    regist = manager->regist + regist_idx;
                    quest = (aQMgr_quest_c*)regist->quest_info;

                    if (quest->base.quest_type == mQst_QUEST_TYPE_ERRAND &&
                        (quest->base.quest_kind == mQst_ERRAND_REQUEST ||
                         quest->base.quest_kind == mQst_ERRAND_REQUEST_CONTINUE)) {
                        manager->regist_idx = regist_idx;

                        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_TARGET);

                        manager->target.quest_inv_item_idx =
                            (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_GET_ITEM_IDX);

                        aQMgr_talk_quest_set_work(&manager->target.work, manager->target.quest_info.quest_type,
                                                  manager->target.quest_info.quest_kind);
                        aQMgr_actor_set_free_str(manager, regist_idx);
                        manager->target.free_data_p = NULL;
                        manager->target.free_data_idx = -1;
                        aQMgr_actor_talk_finish(manager);
                        target_flag = FALSE;
                    }

                    manager->talk_step = aQMgr_TALK_STEP_GIVEUP;
                    manager->msg_category = aQMgr_MSG_KIND_FAILURE_INIT;
                }
            } else {
                regist_idx = aQMgr_actor_check_errand_from(manager);

                if (regist_idx != -1) {
                    regist = manager->regist + regist_idx;
                    quest = (aQMgr_quest_c*)regist->quest_info;

                    if (aQMgr_actor_check_limit(regist) == FALSE) {
                        manager->talk_step = aQMgr_TALK_STEP_ROOT_RECONF_OR_NORMAL;
                        manager->category_msg_no_start = 0x2A6;
                    } else {
                        manager->talk_step = aQMgr_TALK_STEP_GIVEUP;
                        manager->msg_category = aQMgr_MSG_KIND_FAILURE_INIT;

                        if (quest->base.quest_kind == mQst_ERRAND_REQUEST ||
                            quest->base.quest_kind == mQst_ERRAND_REQUEST_CONTINUE) {
                            manager->regist_idx = regist_idx;

                            (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_TARGET);

                            manager->target.quest_inv_item_idx =
                                (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_GET_ITEM_IDX);

                            aQMgr_talk_quest_set_work(&manager->target.work, manager->target.quest_info.quest_type,
                                                      manager->target.quest_info.quest_kind);
                            aQMgr_actor_set_free_str(manager, regist_idx);
                            manager->target.free_data_p = NULL;
                            manager->target.free_data_idx = -1;
                            aQMgr_actor_talk_finish(manager);

                            if (quest->base.quest_kind == mQst_ERRAND_REQUEST) {
                                manager->msg_category = aQMgr_MSG_KIND_NONE;
                                manager->category_msg_no_start = 0x2B73;
                            }

                            target_flag = FALSE;
                        }
                    }
                } else if (mNpc_CheckQuestRequest(animal_idx) == TRUE) {
                    manager->talk_step = aQMgr_TALK_STEP_NEW_QUEST_OR_NORMAL;
                    manager->category_msg_no_start = 0x2A6;
                } else {
                    manager->talk_step = aQMgr_TALK_STEP_NO_OR_NORMAL;
                    manager->category_msg_no_start = 0x2A6;
                    mQst_ClearQuestInfo(&manager->target.quest_info);
                    manager->target.free_data_p = NULL;
                    manager->target.free_data_idx = -1;
                    target_flag = FALSE;
                }
            }
        }
    }

    if (manager->category_msg_no_start == 0x2A6) {
        mChoice_no_b_set(mChoice_Get_base_window_p());
    }

    if (target_flag == TRUE) {
        if (regist_idx != -1) {
            manager->regist_idx = regist_idx;
            (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_TARGET);

            if (manager->talk_step != aQMgr_TALK_STEP_AFTER_REWARD) {
                manager->target.quest_inv_item_idx =
                    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_GET_ITEM_IDX);
            }
        } else {
            aQMgr_actor_new_quest(manager, animal_idx, animal->id.looks, &regist_idx, sel_regist_idx);
        }

        if (manager->target.quest_info.quest_type != mQst_QUEST_TYPE_NONE) {
            aQMgr_talk_quest_set_work(&manager->target.work, manager->target.quest_info.quest_type,
                                      manager->target.quest_info.quest_kind);
            aQMgr_actor_set_free_str(manager, regist_idx);
        }

        manager->regist_idx = regist_idx;
    }

    aQMgr_talk_quest_select_get_choice(manager);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_select_talk_island(QUEST_MANAGER_ACTOR* manager) {
    manager->category_msg_no_start = 0x3567;
    mChoice_no_b_set(mChoice_Get_base_window_p());
    aQMgr_talk_quest_select_get_choice_island(manager);
    manager->msg_category = aQMgr_MSG_KIND_NONE;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_NO_OR_ISLAND;
}

static void aQMgr_actor_talk_select_talk_2(QUEST_MANAGER_ACTOR* manager) {
    Animal_c* animal = aQMgr_GET_CLIENT_ANIMAL(manager);

    manager->mail_memory = NULL;
    if (mNpc_CheckIslandAnimal(animal) == TRUE) {
        aQMgr_actor_talk_select_talk_island(manager);
    } else {
        aQMgr_actor_talk_select_talk(manager);
    }
}

static void aQMgr_actor_talk_reconf_or_normal(QUEST_MANAGER_ACTOR* manager) {
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;

    if (manager->choice.talk_action == 0) {
        manager->msg_category = aQMgr_MSG_KIND_REQUEST_RECONF;
        manager->choice.talk_action = -1;
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_root_reconf_or_normal(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 0) {
        manager->category_msg_no_start = 0x03D4;
        manager->choice.talk_action = -1;
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_no_or_normal(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 0) {
        aQMgr_talk_quest_finish_firstjob_open_quest();
        manager->target.free_data_p = NULL;
        manager->category_msg_no_start = 0x0282;
        manager->choice.talk_action = -1;
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_no_or_island(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 0) {
        if (*manager->memory != NULL) {
            mNpc_AddFriendship(*manager->memory, 1);
        }

        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_CHANGE_TALK_ISLAND);
    } else {
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        aQMgr_talk_quest_set_cancel_msg_com(manager, 0x359D);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_full_item_or_normal(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 0) {
        if (manager->target.set_data_p == NULL) {
            manager->category_msg_no_start = 0x0440;
        } else {
            manager->msg_category = aQMgr_MSG_KIND_FULL_ITEM;
        }

        manager->choice.talk_action = -1;
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_renew_errand_or_normal(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 0) {
        manager->msg_category = aQMgr_MSG_KIND_REQUEST_INIT;
        aQMgr_actor_set_quest_info(manager);
        aQMgr_actor_clear_client_quest_info(manager);
        (*manager->clear_regist_proc)(manager->regist, aQMgr_REGIST_NUM);
        manager->regist_idx = -1;
        aQMgr_talk_quest_start_choice(manager);
        mChoice_no_b_set(mChoice_Get_base_window_p());
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());

        if (manager->target.free_data_p->quest_type == mQst_QUEST_TYPE_ERRAND &&
            manager->target.free_data_p->progress == 0) {
            manager->talk_step = aQMgr_TALK_STEP_RENEW_ERRAND_IRAI_END_GIVE_ITEM;
        } else {
            manager->talk_step = aQMgr_TALK_STEP_RENEW_ERRAND_IRAI_END;
        }

        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_renew_errand_irai_end_give_item(QUEST_MANAGER_ACTOR* manager) {
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_ITEM);
    manager->talk_step = aQMgr_TALK_STEP_CHANGE_WAIT;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    manager->msg_category = aQMgr_MSG_KIND_REQUEST_END;
    aQMgr_actor_talk_finish(manager);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_talk_renew_errand_irai_end(QUEST_MANAGER_ACTOR* manager) {
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    manager->msg_category = aQMgr_MSG_KIND_REQUEST_END;
    aQMgr_actor_talk_finish(manager);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_talk_new_quest_or_normal(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 0) {
        aQMgr_talk_quest_finish_firstjob_open_quest();
        manager->talk_step = aQMgr_TALK_STEP_OCCUR_QUEST;
        manager->msg_category = aQMgr_MSG_KIND_REQUEST_INIT;

        if (manager->target.quest_info.quest_type == mQst_QUEST_TYPE_CONTEST) {
            aQMgr_actor_set_quest_info(manager);
            aQMgr_actor_clear_client_quest_info(manager);
        }

        aQMgr_talk_quest_start_choice(manager);
        mChoice_no_b_set(mChoice_Get_base_window_p());
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_occur_quest(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 0) {
        mQst_base_c* quest_info;

        manager->msg_category = aQMgr_MSG_KIND_REQUEST_END;
        aQMgr_actor_set_quest_info(manager);
        aQMgr_actor_clear_client_quest_info(manager);

        quest_info = manager->target.free_data_p;
        if (quest_info->quest_type != mQst_QUEST_TYPE_ERRAND ||
            (quest_info->quest_type == mQst_QUEST_TYPE_ERRAND && quest_info->progress == 0)) {
            manager->talk_step = aQMgr_TALK_STEP_WAIT_TALK;
            manager->sub_talk_state = aQMgr_TALK_SUB_STATE_NO_WAIT;

            if (quest_info->quest_type != mQst_QUEST_TYPE_ERRAND) {
                sAdo_SysTrgStart(0x12E);
            }
        } else {
            manager->talk_step = aQMgr_TALK_STEP_FINISH;
            manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;

            if (quest_info->quest_type == mQst_QUEST_TYPE_ERRAND && quest_info->quest_kind == mQst_ERRAND_REQUEST) {
                sAdo_SysTrgStart(0x12E);
            }
        }

        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else if (manager->choice.talk_action == 1) {
        aQMgr_actor_set_client_quest_info(manager);
        manager->msg_category = aQMgr_MSG_KIND_REQUEST_REJECT;
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);

        /* If the player rejects a quest then apply a friendship penalty */
        if (*manager->memory != NULL) {
            mNpc_AddFriendship(*manager->memory, -3);
        }
    } else if (manager->choice.talk_action == 2) {
        aQMgr_talk_quest_set_cancel_msg_com(manager, 0x254A);
    } else {
        manager->msg_category = aQMgr_MSG_KIND_REQUEST_END;
        aQMgr_actor_set_quest_info(manager);
        aQMgr_actor_clear_client_quest_info(manager);
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    }

    mMsg_Set_ForceNext(mMsg_Get_base_window_p());
}

static void aQMgr_talk_quest_wait_talk(QUEST_MANAGER_ACTOR* manager) {
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_ITEM);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_ITEM_PLAYER_WAIT;
    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    manager->msg_category = aQMgr_MSG_KIND_REQUEST_END;
    aQMgr_actor_talk_finish(manager);
    manager->talk_step = aQMgr_TALK_STEP_CHANGE_WAIT;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_talk_giveup(QUEST_MANAGER_ACTOR* manager) {
    if (manager->target.quest_inv_item_idx != -1) {
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_CHECK_BUTTON;
        manager->talk_step = aQMgr_TALK_STEP_GIVEUP_WAIT_BUTTON;
    }

    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_talk_quest_giveup_wait_button(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_step = aQMgr_TALK_STEP_GIVEUP_OPEN_MENU;
    mMsg_request_main_disappear_wait_type2(mMsg_Get_base_window_p());
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_DISAPPEAR_WAIT;
    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    mMsg_Set_ForceNext(mMsg_Get_base_window_p());
}

static void aQMgr_talk_quest_giveup_open_menu(QUEST_MANAGER_ACTOR* manager) {
    mSM_open_submenu_new2(manager->submenu, mSM_OVL_INVENTORY, mSM_IV_OPEN_QUEST, manager->target.quest_inv_item_idx,
                          NULL, mSM_IV_ITEM_PUT_AWAY);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_HAND_ITEM_WAIT;
    manager->talk_step = aQMgr_TALK_STEP_GIVEUP_ITEM;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_talk_quest_giveup_item(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_set_data_c* set_data = (aQMgr_set_data_c*)manager->target.set_data_p;
    int base_msg;
    int friendship = 0;

    if (manager->handover_item) {
        manager->msg_category = aQMgr_MSG_KIND_FAILURE_END;
        manager->talk_step = aQMgr_TALK_STEP_GIVEUP_NPC_ITEM;
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_APPEAR_WAIT;

        if (set_data != NULL && *manager->memory != NULL) {
            base_msg = set_data->msg_start[aQMgr_MSG_KIND_FAILURE_END];

            switch (base_msg) {
                case 0x2B8:
                    friendship = -5;
                    break;
                case 0x452:
                    friendship = -2;
                    break;
                case 0x2CA:
                    friendship = -1;
                    break;
            }

            mNpc_AddFriendship(*manager->memory, friendship);
        }
    } else {
        manager->msg_category = aQMgr_MSG_KIND_NONE;
        manager->category_msg_no_start = 0x499;
        manager->talk_step = aQMgr_TALK_STEP_GIVEUP;
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    }

    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_ChangeMsgData(mMsg_Get_base_window_p(), manager->msg_no);
    mMsg_request_main_appear_wait_type1(mMsg_Get_base_window_p());
    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
}

static void aQMgr_talk_quest_giveup_npc_item(QUEST_MANAGER_ACTOR* manager) {
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_NPC_HAND_WAIT_MSG_WAIT;
    aQMgr_actor_talk_finish(manager);
    manager->talk_step = aQMgr_TALK_STEP_CHANGE_WAIT;
}

static void aQMgr_actor_talk_fin_quest_start(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 0) {
        mMsg_Set_LockContinue(mMsg_Get_base_window_p());
        mMsg_request_main_disappear_wait_type2(mMsg_Get_base_window_p());

        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_DISAPPEAR_WAIT;
        manager->talk_step = aQMgr_TALK_STEP_OPEN_MENU;
        manager->choice.talk_action = -1;
        manager->msg_category = aQMgr_MSG_KIND_COMPLETE_INIT;

        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
        manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    }
}

static void aQMgr_talk_quest_talk_fin_quest_start_not_hand(QUEST_MANAGER_ACTOR* manager) {
    if (manager->choice.talk_action == 2) {
        aQMgr_talk_quest_set_cancel_msg_com(manager, 0x254A);
    } else {
        manager->talk_step = aQMgr_TALK_STEP_FIN_QUEST_REWARD;
        manager->choice.talk_action = -1;
        manager->msg_category = aQMgr_MSG_KIND_COMPLETE_INIT;

        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    }

    mMsg_Set_ForceNext(mMsg_Get_base_window_p());
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_talk_quest_open_menu(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_target_c* target = &manager->target;
    Submenu* submenu = manager->submenu;
    int item_idx = target->quest_inv_item_idx;

    if (target->quest_info.quest_type == mQst_QUEST_TYPE_CONTEST) {
        switch (target->quest_info.quest_kind) {
            case mQst_CONTEST_KIND_FISH:
                mSM_open_submenu(submenu, mSM_OVL_INVENTORY, mSM_IV_OPEN_TAKE, 1);
                break;
            case mQst_CONTEST_KIND_INSECT:
                mSM_open_submenu(submenu, mSM_OVL_INVENTORY, mSM_IV_OPEN_TAKE, 2);
                break;
            default:
                mSM_open_submenu_new2(submenu, mSM_OVL_INVENTORY, mSM_IV_OPEN_QUEST, item_idx, NULL,
                                      mSM_IV_ITEM_PUT_AWAY);
                break;
        }
    } else {
        int mode;

        if (ITEM_NAME_GET_TYPE(target->quest_item) == NAME_TYPE_ITEM1 &&
            ITEM_NAME_GET_CAT(target->quest_item) == ITEM1_CAT_CLOTH) {
            mode = mSM_IV_ITEM_NORMAL;
        } else {
            mode = mSM_IV_ITEM_PUT_AWAY;
        }

        mSM_open_submenu_new2(submenu, mSM_OVL_INVENTORY, mSM_IV_OPEN_QUEST, item_idx, NULL, mode);
    }

    manager->talk_step = aQMgr_TALK_STEP_GET_ITEM;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_HAND_ITEM_WAIT;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_talk_quest_get_item(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_target_c* target = &manager->target;

    if (manager->handover_item) {
        manager->msg_category = aQMgr_MSG_KIND_COMPLETE_INIT;
        manager->talk_step = aQMgr_TALK_STEP_NPC_GET_ITEM_WAIT;

        mQst_SetItemNameFreeStr(manager->handover_item, mMsg_FREE_STR2);
        if (ITEM_NAME_GET_TYPE(target->quest_item) == NAME_TYPE_ITEM1 &&
            ITEM_NAME_GET_CAT(target->quest_item) == ITEM1_CAT_CLOTH) {
            Common_Set(npc_chg_cloth, target->quest_item);
        }
    } else {
        manager->msg_category = aQMgr_MSG_KIND_NONE;
        manager->category_msg_no_start = 0x4AB;
        manager->talk_step = aQMgr_TALK_STEP_CHANGE_WAIT;

        if (*manager->memory != NULL) {
            mNpc_AddFriendship(*manager->memory, -1);
        }
    }

    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_ChangeMsgData(mMsg_Get_base_window_p(), manager->msg_no);
    mMsg_request_main_appear_wait_type1(mMsg_Get_base_window_p());
    mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_MSG_APPEAR_WAIT;
}

static void aQMgr_talk_quest_npc_get_item_wait(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_step = aQMgr_TALK_STEP_FIN_QUEST_REWARD;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_NPC_HAND_WAIT_MSG_WAIT;
}

static void aQMgr_actor_talk_fin_quest_reward(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_target_c* target = &manager->target;
    aQMgr_regist_c* regist = &manager->regist[manager->regist_idx];

    aQMgr_actor_set_reward(manager);

    if (aQMgr_actor_hand_reward(target) == TRUE) {
        aQMgr_actor_set_free_str_reward(target);
        manager->msg_category = aQMgr_MSG_KIND_NONE;

        if (regist->quest_info != NULL && regist->quest_info->quest_type == mQst_QUEST_TYPE_CONTEST) {
            // missing static qualifier
            int* reward_msg_table[mQst_CONTEST_KIND_NUM] = { l_fruit_reward_msg,   l_soccer_reward_msg,
                                                             l_snowman_reward_msg, l_flower_reward_msg,
                                                             l_fish_reward_msg,    l_insect_reward_msg,
                                                             l_reward_msg };

            if (regist->quest_info->quest_kind >= mQst_CONTEST_KIND_NUM) {
                regist->quest_info->quest_kind = mQst_CONTEST_KIND_LETTER;
            }

            manager->category_msg_no_start = reward_msg_table[regist->quest_info->quest_kind][target->reward_kind];
        } else {
            manager->category_msg_no_start = l_reward_msg[target->reward_kind];
        }

        manager->talk_step = aQMgr_TALK_STEP_FIN_QUEST_THANKS;
        sAdo_SysTrgStart(0x12F);
        if (*manager->memory != NULL) {
            mNpc_AddFriendship(*manager->memory, 3);
        }
    } else {
        manager->msg_category = aQMgr_MSG_KIND_REWARD_FULL_ITEM;
        regist->quest_info->give_reward = TRUE;
        manager->regist_idx = -1;
    }

    if (regist->quest_info->quest_type == mQst_QUEST_TYPE_CONTEST) {
        if (regist->quest_info->progress != 0) {
            regist->quest_info->progress--;
            lbRTC_Add_DD(&regist->quest_info->time_limit, 3); // add 3 extra days to finish
            mPr_CopyPersonalID(&((mQst_contest_c*)regist->quest_info)->player_id, &Common_Get(now_private)->player_ID);
        }

        manager->regist_idx = -1;
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    aQMgr_actor_talk_finish(manager);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_talk_fin_quest_thanks(QUEST_MANAGER_ACTOR* manager) {
    manager->msg_category = aQMgr_MSG_KIND_COMPLETE_END;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_REWARD);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_talk_after_reward(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_regist_c* regist;
    int regist_idx = manager->regist_idx;

    aQMgr_actor_set_reward(manager);

    if (aQMgr_actor_hand_reward(&manager->target) == TRUE) {
        aQMgr_actor_set_free_str_reward(&manager->target);
        regist = &manager->regist[regist_idx];
        manager->msg_category = aQMgr_MSG_KIND_NONE;

        if (regist->quest_info != NULL && regist->quest_info->quest_type == mQst_QUEST_TYPE_CONTEST) {
            // missing static qualifier
            int* reward_msg_table[mQst_CONTEST_KIND_NUM] = { l_after_reward_msg,   l_soccer_reward_msg,
                                                             l_snowman_reward_msg, l_flower_reward_msg,
                                                             l_after_reward_msg,   l_after_reward_msg,
                                                             l_after_reward_msg };

            if (regist->quest_info->quest_kind >= mQst_CONTEST_KIND_NUM) {
                regist->quest_info->quest_kind = mQst_CONTEST_KIND_LETTER;
            }

            manager->category_msg_no_start =
                reward_msg_table[regist->quest_info->quest_kind][manager->target.reward_kind];
        } else {
            manager->category_msg_no_start = l_after_reward_msg[manager->target.reward_kind];
        }

        manager->talk_step = aQMgr_TALK_STEP_AFTER_REWARD_THANKS;
        sAdo_SysTrgStart(0x12F);
    } else {
        manager->msg_category = aQMgr_MSG_KIND_REWARD_FULL_ITEM2;
    }

    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_actor_talk_after_reward_thanks(QUEST_MANAGER_ACTOR* manager) {
    manager->msg_category = aQMgr_MSG_KIND_AFTER_REWARD_THANKS;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_NPC_TAKEOUT_REWARD);
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    aQMgr_actor_talk_finish(manager);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_talk_quest_contest_hoka_or_normal(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_regist_c* regist = &manager->regist[manager->regist_idx];

    if (manager->choice.talk_action == 0) {
        aQMgr_talk_quest_finish_firstjob_open_quest();
        manager->target.free_data_p = NULL;
        mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR12,
                          ((mQst_contest_c*)regist->quest_info)->player_id.player_name, PLAYER_NAME_LEN);
        if (regist->quest_info->quest_type == mQst_QUEST_TYPE_CONTEST &&
            regist->quest_info->quest_kind == mQst_CONTEST_KIND_LETTER) {
            if (mPr_CheckCmpPersonalID(&((mQst_contest_c*)regist->quest_info)->player_id,
                                       &Common_Get(now_private)->player_ID) == FALSE) {
                manager->category_msg_no_start = aQMgr_talk_quest_get_contest_hoka_msg_no(
                    (mQst_contest_c*)regist->quest_info, aQMgr_GET_CLIENT_ANIMAL(manager));
            } else {
                manager->category_msg_no_start = 0x1B05;
            }
        } else {
            manager->category_msg_no_start = aQMgr_talk_quest_get_contest_hoka_msg_no(
                (mQst_contest_c*)regist->quest_info, aQMgr_GET_CLIENT_ANIMAL(manager));
            manager->target.free_data_p = NULL;
            aQMgr_actor_talk_finish(manager);
        }

        manager->choice.talk_action = -1;
        mMsg_Set_ForceNext(mMsg_Get_base_window_p());
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
        mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    } else {
        aQMgr_talk_quest_change_normal_or_hint(manager);
    }

    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
}

static void aQMgr_talk_quest_change_wait(QUEST_MANAGER_ACTOR* manager) {
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
}

static void aQMgr_actor_talk_finish_letter(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_regist_c* regist = &manager->regist[manager->regist_idx];
    mQst_contest_c* contest = (mQst_contest_c*)regist->quest_info;

    mMsg_Set_free_str(mMsg_Get_base_window_p(), mMsg_FREE_STR12, contest->player_id.player_name, PLAYER_NAME_LEN);

    if (mPr_CheckCmpPersonalID(&contest->player_id, &Common_Get(now_private)->player_ID) == TRUE) {
        manager->category_msg_no_start = 0x1B17;
    } else {
        manager->category_msg_no_start = 0x1B29;
    }

    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_MSG_NO);
    mMsg_Set_continue_msg_num(mMsg_Get_base_window_p(), manager->msg_no);
    manager->talk_step = aQMgr_TALK_STEP_CHANGE_WAIT;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    manager->target.free_data_p = NULL;
    aQMgr_actor_talk_finish(manager);
    mMsg_Set_ForceNext(mMsg_Get_base_window_p());
}

typedef void (*aQMgr_QUEST_TALK_PROC)(QUEST_MANAGER_ACTOR*);

extern void aQMgr_actor_move_talk_init(QUEST_MANAGER_ACTOR* manager) {
    static aQMgr_QUEST_TALK_PROC talk_proc[] = {
        &aQMgr_actor_talk_select_talk_2,
        &aQMgr_actor_talk_reconf_or_normal,
        &aQMgr_actor_talk_root_reconf_or_normal,
        &aQMgr_actor_talk_no_or_normal,
        &aQMgr_actor_talk_full_item_or_normal,
        &aQMgr_actor_talk_renew_errand_or_normal,
        &aQMgr_actor_talk_new_quest_or_normal,
        &aQMgr_actor_talk_finish,
        &aQMgr_actor_talk_occur_quest,
        &aQMgr_actor_talk_giveup,
        &aQMgr_talk_quest_giveup_wait_button,
        &aQMgr_talk_quest_giveup_open_menu,
        &aQMgr_talk_quest_giveup_item,
        &aQMgr_talk_quest_giveup_npc_item,
        &aQMgr_actor_talk_fin_quest_start,
        &aQMgr_talk_quest_talk_fin_quest_start_not_hand,
        &aQMgr_actor_talk_fin_quest_reward,
        &aQMgr_actor_talk_fin_quest_thanks,
        &aQMgr_actor_talk_after_reward,
        &aQMgr_actor_talk_after_reward_thanks,
        &aQMgr_talk_quest_wait_talk,
        &aQMgr_talk_quest_open_menu,
        &aQMgr_talk_quest_get_item,
        &aQMgr_talk_quest_npc_get_item_wait,
        &aQMgr_talk_quest_change_wait,
        &aQMgr_actor_talk_renew_errand_irai_end,
        &aQMgr_actor_talk_renew_errand_irai_end_give_item,
        &aQMgr_talk_quest_contest_hoka_or_normal,
        &aQMgr_actor_talk_finish_letter,
        (aQMgr_QUEST_TALK_PROC)&none_proc1,
        &aQMgr_actor_talk_no_or_island,
        &aQMgr_actor_talk_finish,
    };

    int step = manager->talk_step;
    int choice = mChoice_Get_ChoseNum(mChoice_Get_base_window_p());

    mChoice_Clear_ChoseNum(mChoice_Get_base_window_p());
    manager->choice.talk_action = choice;
    (*talk_proc[step])(manager);
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_SET_CHOICE_STR);

    if (manager->talk_change_type >= aQMgr_TALK_KIND_NUM) {
        manager->talk_state = aQMgr_TALK_STATE_SUB;
    }
}
