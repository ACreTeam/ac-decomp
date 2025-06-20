#include "ac_quest_manager.h"

#include "m_common_data.h"
#include "m_msg.h"
#include "m_melody.h"
#include "ac_quest_talk_greeting.h"
#include "ac_quest_talk_init.h"
#include "ac_quest_talk_fj_init.h"
#include "ac_quest_talk_normal_init.h"
#include "ac_quest_talk_island.h"
#include "m_soncho.h"
#include "gfxalloc.h"
#include "m_player_lib.h"
#include "libultra/libultra.h"
#include "m_malloc.h"
#include "zurumode.h"

enum {
    aQMgr_MODE_NORMAL,
    aQMgr_MODE_SELECT_TALK,
    aQMgr_MODE_MOVE_TALK,
    aQMgr_MODE_TALK_FIN,
    aQMgr_MODE_TALK_START_KAMAKURA_HELLO,
    aQMgr_MODE_TALK_START_KAMAKURA,
    aQMgr_MODE_TALK_START_SUMMERCAMP_HELLO,
    aQMgr_MODE_TALK_START_SUMMERCAMP,

    aQMgr_MODE_NUM
};

static ACTOR* l_client_p = NULL;
static u8 l_quest_manager_mode = aQMgr_MODE_NORMAL;
static Anmmem_c* l_quest_memory_p = NULL;
static QUEST_MANAGER_ACTOR* l_quest_actor_p = NULL;
static int l_quest_manager_hello = FALSE;
static int l_aQMgr_hand_start = FALSE;

// clang-format off
static aQMgr_set_data_c l_set_delivery_data[] = {
    {
        aQMgr_QUEST_TARGET_RANDOM,
        2,
        0,
        TRUE,
        aQMgr_QUEST_ITEM_CLOTH,
        EMPTY_NO,
        40, 0, 0, 0, 0, 30, 30, 0,
        200,
        0x0151, 0x024C, 0x0163, 0x025E, 0x0175, 0x0294, 0x0187, 0x02B8, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_FOREIGN,
        2,
        0,
        TRUE,
        aQMgr_QUEST_ITEM_RANDOM,
        EMPTY_NO,
        40, 0, 0, 10, 10, 40, 0, 0,
        1000,
        0x0199, 0x024C, 0x01AB, 0x025E, 0x01BD, 0x0294, 0x01CF, 0x02CA, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_LAST_REMOVE,
        2,
        0,
        TRUE,
        aQMgr_QUEST_ITEM_RANDOM,
        EMPTY_NO,
        20, 0, 0, 20, 20, 40, 0, 0,
        1000,
        0x0205, 0x024C, 0x0217, 0x025E, 0x10BF, 0x0294, 0x023A, 0x02CA, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_RANDOM,
        2,
        0,
        TRUE,
        aQMgr_QUEST_ITEM_RANDOM,
        EMPTY_NO,
        40, 0, 40, 10, 10, 0, 0, 0,
        0,
        0x0A74, 0x024C, 0x0A86, 0x025E, 0x0A98, 0x0294, 0x0AAA, 0x02B8, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
};

static aQMgr_set_data_c l_set_errand_data[] = {
    {
        aQMgr_QUEST_TARGET_RANDOM_EXCLUDED,
        2,
        4,
        FALSE,
        aQMgr_QUEST_ITEM_RANDOM,
        EMPTY_NO,
        50, 0, 0, 0, 0, 0, 0, 0,
        500,
        0x038C, 0x024C, 0x03D4, 0x025E, 0x03F8, 0x0294, 0x2B73, 0x02CA, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_RANDOM_EXCLUDED,
        2,
        1,
        FALSE,
        aQMgr_QUEST_ITEM_CURRENT_ITEM,
        EMPTY_NO,
        50, 0, 0, 0, 0, 0, 0, 0,
        500,
        0x03B0, 0x024C, 0x03E6, 0x025E, 0x03F8, 0x0294, 0x041C, 0x02CA, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_ORIGINAL_TARGET,
        2,
        0,
        TRUE,
        aQMgr_QUEST_ITEM_CURRENT_ITEM,
        EMPTY_NO,
        50, 0, 0, 0, 0, 0, 0, 0,
        500,
        0x039E, 0x024C, 0x03C2, 0x025E, 0x03F8, 0x0294, 0x040A, 0x0452, 0x17B8, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        0,
        0,
        FALSE,
        aQMgr_QUEST_ITEM_CURRENT_ITEM,
        EMPTY_NO,
        0, 0, 0, 0, 0, 0, 0, 100,
        0,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        0,
        0,
        FALSE,
        aQMgr_QUEST_ITEM_CURRENT_ITEM,
        EMPTY_NO,
        0, 0, 0, 0, 0, 0, 0, 100,
        0,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        0,
        0,
        FALSE,
        aQMgr_QUEST_ITEM_CURRENT_ITEM,
        EMPTY_NO,
        0, 0, 0, 0, 0, 0, 0, 100,
        0,
        0x0000, 0x0000, 0x0000, 0x0000, 0x08EF, 0x08F0, 0x0000, 0x0000, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        0,
        0,
        FALSE,
        aQMgr_QUEST_ITEM_CURRENT_ITEM,
        EMPTY_NO,
        0, 0, 0, 0, 0, 0, 0, 100,
        0,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        0,
        0,
        FALSE,
        aQMgr_QUEST_ITEM_CURRENT_ITEM,
        EMPTY_NO,
        0, 0, 0, 0, 0, 0, 0, 100,
        0,
        0x0000, 0x0000, 0x0000, 0x0000, 0x08FB, 0x08FC, 0x0000, 0x0000, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        0,
        0,
        FALSE,
        aQMgr_QUEST_ITEM_CURRENT_ITEM,
        EMPTY_NO,
        0, 0, 0, 0, 0, 0, 0, 100,
        0,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0907, 0x0908, 0x0000, 0x0000, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        0,
        0,
        FALSE,
        aQMgr_QUEST_ITEM_CURRENT_ITEM,
        EMPTY_NO,
        0, 0, 0, 0, 0, 0, 0, 100,
        0,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        0,
        0,
        FALSE,
        aQMgr_QUEST_ITEM_CURRENT_ITEM,
        EMPTY_NO,
        0, 0, 0, 0, 0, 0, 0, 100,
        0,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        0,
        0,
        FALSE,
        aQMgr_QUEST_ITEM_CURRENT_ITEM,
        EMPTY_NO,
        0, 0, 0, 0, 0, 0, 0, 100,
        0,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0907, 0x0908, 0x0000, 0x0000, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        0,
        0,
        FALSE,
        aQMgr_QUEST_ITEM_CURRENT_ITEM,
        EMPTY_NO,
        0, 0, 0, 0, 0, 0, 0, 100,
        0,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        0,
        0,
        FALSE,
        aQMgr_QUEST_ITEM_CURRENT_ITEM,
        EMPTY_NO,
        0, 0, 0, 0, 0, 0, 0, 100,
        0,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        0,
        0,
        FALSE,
        aQMgr_QUEST_ITEM_CURRENT_ITEM,
        EMPTY_NO,
        0, 0, 0, 0, 0, 0, 0, 100,
        0,
        0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
};

static aQMgr_set_data_c l_set_contest_data[] = {
    {
        aQMgr_QUEST_TARGET_CLIENT,
        1,
        1,
        FALSE,
        aQMgr_QUEST_ITEM_FRUIT,
        EMPTY_NO,
        0, 0, 0, 30, 30, 40, 0, 0,
        500,
        0x01E1, 0x0000, 0x01E1, 0x025E, 0x01F3, 0x117C, 0x0000, 0x02CA, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        1,
        2,
        FALSE,
        aQMgr_QUEST_ITEM_NONE,
        EMPTY_NO,
        40, 0, 0, 30, 30, 0, 0, 0,
        0,
        0x0D79, 0x0000, 0x0D79, 0x025E, 0x0D91, 0x0DD9, 0x0000, 0x02CA, 0x0440, 0x0DFD, 0x0DD9, 0x0DEB, 0x0E0F
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        1,
        1,
        FALSE,
        aQMgr_QUEST_ITEM_NONE,
        EMPTY_NO,
        60, 0, 0, 20, 20, 0, 0, 0,
        0,
        0x0E33, 0x0000, 0x0E33, 0x025E, 0x0E45, 0x0E8D, 0x0000, 0x02CA, 0x0440, 0x0EB1, 0x0E8D, 0x0E9F, 0x0EC3
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        3,
        1,
        FALSE,
        aQMgr_QUEST_ITEM_NONE,
        EMPTY_NO,
        60, 0, 0, 20, 20, 0, 0, 0,
        0,
        0x0FB5, 0x0000, 0x0FB5, 0x025E, 0x0FC7, 0x100F, 0x0000, 0x02CA, 0x0440, 0x1033, 0x100F, 0x1021, 0x1045
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        3,
        1,
        FALSE,
        aQMgr_QUEST_ITEM_NONE,
        EMPTY_NO,
        80, 0, 0, 10, 10, 0, 0, 0,
        0,
        0x158C, 0x0000, 0x158C, 0x025E, 0x159E, 0x15B0, 0x0000, 0x02CA, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        3,
        1,
        FALSE,
        aQMgr_QUEST_ITEM_NONE,
        EMPTY_NO,
        80, 0, 0, 10, 10, 0, 0, 0,
        0,
        0x160A, 0x0000, 0x160A, 0x025E, 0x161C, 0x162E, 0x0000, 0x02CA, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
    {
        aQMgr_QUEST_TARGET_CLIENT,
        2,
        2,
        FALSE,
        aQMgr_QUEST_ITEM_NONE,
        EMPTY_NO,
        80, 0, 0, 10, 10, 0, 0, 0,
        0,
        0x1AE1, 0x0000, 0x1AE1, 0x025E, 0x1B17, 0x0294, 0x0000, 0x02CA, 0x0440, 0x035E, 0x034C, 0x0370, 0x033A
    },
};
//clang-format on

static aQMgr_set_data_c* l_set_data[mQst_QUEST_TYPE_NUM] = {
    l_set_delivery_data,
    l_set_errand_data,
    l_set_contest_data
};

static void aQMgr_move_own_errand_cloth(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);
static void aQMgr_move_own_errand_seed(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);
static void aQMgr_move_own_errand_letter(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);
static void aQMgr_move_own_errand_hello(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);

static void aQMgr_actor_contest_check_limit(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist) ;
static int aQMgr_actor_check_fin_fruit(mQst_base_c* quest_info, Animal_c* animal);
static int aQMgr_actor_check_fin_soccer(mQst_base_c* quest_info, Animal_c* animal);
static void aQMgr_actor_contest_snowman_clear(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);
static int aQMgr_actor_check_fin_snowman(mQst_base_c* quest_info, Animal_c* animal);
static void aQMgr_actor_contest_flower_clear(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);
static int aQMgr_actor_check_flower(mQst_contest_c* contest, int bx, int bz);
static int aQMgr_actor_check_fin_flower(mQst_base_c* quest_info, Animal_c* animal);
static int aQMgr_actor_check_fin_fish(mQst_base_c* quest_info, Animal_c* animal);
static void aQMgr_actor_contest_insect_clear(QUEST_MANAGER_ACTOR* manager, aQMgr_regist_c* regist);
static int aQMgr_actor_check_fin_insect(mQst_base_c* quest_info, Animal_c* animal);
static int aQMgr_actor_check_fin_contest_letter(mQst_base_c* quest_info, Animal_c* animal);

static void aQMgr_save_contest_flower(aQMgr_regist_c* regist);
static void aQMgr_save_contest(aQMgr_regist_c* regist);

static aQMgr_CHECK_LIMIT_PROC l_errand_proc[mQst_ERRAND_NUM] = {
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
    &aQMgr_move_own_errand_cloth,
    &aQMgr_move_own_errand_seed,
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
    &aQMgr_move_own_errand_letter,
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
    &aQMgr_move_own_errand_letter,
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
    &aQMgr_move_own_errand_hello,
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1,
    (aQMgr_CHECK_LIMIT_PROC)&none_proc1
};

static aQMgr_CHECK_LIMIT_PROC l_contest_proc[mQst_CONTEST_KIND_NUM] = {
    &aQMgr_actor_contest_check_limit,
    &aQMgr_actor_contest_check_limit,
    &aQMgr_actor_contest_snowman_clear,
    &aQMgr_actor_contest_flower_clear,
    &aQMgr_actor_contest_check_limit,
    &aQMgr_actor_contest_insect_clear,
    &aQMgr_actor_contest_check_limit
};

static aQMgr_CHECK_FINISH_PROC l_contest_check[mQst_CONTEST_KIND_NUM] = {
    &aQMgr_actor_check_fin_fruit,
    &aQMgr_actor_check_fin_soccer,
    &aQMgr_actor_check_fin_snowman,
    &aQMgr_actor_check_fin_flower,
    &aQMgr_actor_check_fin_fish,
    &aQMgr_actor_check_fin_insect,
    &aQMgr_actor_check_fin_contest_letter
};

static int l_proc_max[mQst_QUEST_TYPE_NUM] = { mQst_DELIVERY_KIND_NUM, mQst_ERRAND_NUM, mQst_CONTEST_KIND_NUM };

static void aQMgr_actor_set_memory(ACTOR* client) {
    Animal_c* animal;

    if (client != NULL && client->part == ACTOR_PART_NPC) {
        animal = ((NPC_ACTOR*)client)->npc_info.animal;
    }
    else {
        animal = NULL;
    }

    if (animal != NULL) {
        Anmmem_c* memory = animal->memories;
        int memory_idx = mNpc_GetAnimalMemoryIdx(&Common_Get(now_private)->player_ID, memory, ANIMAL_MEMORY_NUM);

        if (memory_idx != -1) {
            memory += memory_idx;
            l_quest_memory_p = memory;
        }
        else {
            l_quest_memory_p = NULL;
        }
    }
}

static void aQMgr_actor_set_hello_free_str(Animal_c* animal) {
    int mem_idx = mNpc_GetAnimalMemoryIdx(&Common_Get(now_private)->player_ID, animal->memories, ANIMAL_MEMORY_NUM);

    if (mem_idx != -1 && mNpc_CheckIslandAnimal(animal) == FALSE) {
        mLd_SetFreeStrLandMuraName(animal->memories[mem_idx].memuni.land.name, mMsg_FREE_STR6);
    }

    if (mNpc_CheckIslandAnimal(animal) == FALSE) {
        mLd_SetFreeStrLandMuraName(animal->anmuni.previous_land_name, mMsg_FREE_STR10);
    }

    mLd_SetFreeStrLandMuraName(animal->id.land_name, mMsg_FREE_STR11);
}

static int aQMgr_take_hello_msg_no(QUEST_MANAGER_ACTOR* manager) {
    ACTOR* client = *manager->client;
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal;
    PersonalID_c* pid = &Common_Get(now_private)->player_ID;

    if (animal != NULL) {
        if (mNpc_GetAnimalMemoryIdx(pid, animal->memories, ANIMAL_MEMORY_NUM) == -1) {
            l_quest_manager_hello = TRUE;
        }
        else {
            l_quest_manager_hello = FALSE;
        }
    }
    else {
        l_quest_manager_hello = TRUE;
    }

    return aQMgr_get_hello_msg_no(client, manager->get_time_kind_proc, manager->give_item);
}

static void aQMgr_set_talk_info(ACTOR* client) {
    QUEST_MANAGER_ACTOR* manager = l_quest_actor_p;
    Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal;
    int msg_no;

    l_client_p = client;
    msg_no = aQMgr_take_hello_msg_no(manager);
    mDemo_Set_msg_num(msg_no);

    if (animal->mood == mNpc_FEEL_SLEEPY) {
        animal->mood = mNpc_FEEL_NORMAL;
        ((NPC_ACTOR*)client)->condition_info.feel_tim = 0;
    }

    ((NPC_ACTOR*)client)->talk_info.feel = animal->mood;
    aQMgr_actor_set_hello_free_str(animal);
    if (animal != NULL) {
        manager->cloth = animal->cloth;
    }

    if (ZURUMODE2_ENABLED()) {
        mNpc_SetTalkAnimalIdx_fdebug(&animal->id);
    }
}

static int aQMgr_actor_talk_request(ACTOR* client) {
    int res = FALSE;

    if (client != NULL && l_quest_manager_mode == aQMgr_MODE_NORMAL) {
        if (mDemo_Check(mDemo_TYPE_TALK, client) == FALSE) {
            mDemo_Request(mDemo_TYPE_TALK, client, &aQMgr_set_talk_info);
        }
        else if (mDemo_Check_ListenAble() == FALSE) {
            res = TRUE;
        }
    }

    return res;
}

static int aQMgr_actor_talk_start(ACTOR* client) {
    int res = FALSE;

    if (client != NULL && l_quest_manager_mode == aQMgr_MODE_NORMAL && mDemo_Check(mDemo_TYPE_TALK, client) == TRUE &&
        mDemo_Check_ListenAble() == FALSE && mDemo_Check_SpeakerAble() == TRUE && client == l_client_p) {
        mDemo_Set_ListenAble();

        if (client->npc_id == SP_NPC_EV_KAMAKURA_0) {
            if (l_quest_manager_hello == TRUE) {
                l_quest_manager_mode = aQMgr_MODE_TALK_START_KAMAKURA_HELLO;
            }
            else {
                l_quest_manager_mode = aQMgr_MODE_TALK_START_KAMAKURA;
            }
        }
        else if (client->npc_id == SP_NPC_EV_SUMMERCAMP_0) {
            if (l_quest_manager_hello == TRUE) {
                l_quest_manager_mode = aQMgr_MODE_TALK_START_SUMMERCAMP_HELLO;
                Common_Set(npc_is_summercamper, TRUE);
            }
            else {
                l_quest_manager_mode = aQMgr_MODE_TALK_START_SUMMERCAMP;
            }
        }
        else {
            l_quest_manager_mode = aQMgr_MODE_SELECT_TALK;
        }

        aQMgr_actor_set_memory(client);
        mMld_ActorMakeMelody(client);
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_talk_check(ACTOR* client) {
    int res = FALSE;

    if (client != NULL && l_client_p == client && l_quest_manager_mode == aQMgr_MODE_TALK_FIN && mDemo_Get_talk_actor() != client) {
        l_client_p = NULL;
        l_quest_manager_mode = aQMgr_MODE_NORMAL;
        res = TRUE;
    }

    return res;
}

static int aQMgr_get_time_kind(int hour) {
    int res = aQMgr_TIME_MORNING;
    
    if (hour >= 12 && hour < 17) {
        res = aQMgr_TIME_DAY;
    }
    else if (hour >= 17 && hour < 24) {
        res = aQMgr_TIME_EVENING;
    }
    else if (hour >= 0 && hour < 5) {
        res = aQMgr_TIME_NIGHT;
    }

    return res;
}

static void aQMgr_clear_talk_init_ovl(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_init_proc = NULL;
}

static int aQMgr_talk_common_talk_init_ovl(QUEST_MANAGER_ACTOR* manager) {
    static aQMgr_TALK_INIT_PROC talk_init_table[aQMgr_TALK_KIND_NUM] = {
        &aQMgr_actor_move_talk_init,
        &aQMgr_talk_first_job_init,
        &aQMgr_talk_normal_init,
        &aQMgr_talk_island_init
    };

    int type = manager->talk_type;
    
    if (type < 0 || type >= aQMgr_TALK_KIND_NUM) {
        type = aQMgr_TALK_KIND_QUEST;
    }

    manager->talk_init_proc = talk_init_table[type];
    return TRUE;
}

static void aQMgr_actor_change_talk_init_ovl(QUEST_MANAGER_ACTOR* manager) {
    if (manager->talk_change_type < aQMgr_TALK_KIND_NUM) {
        manager->talk_type = manager->talk_change_type;
        if ((*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_TALK_INIT_OVL) == TRUE) {
            manager->talk_change_type = aQMgr_TALK_KIND_NUM;
            manager->sub_talk_state = aQMgr_TALK_SUB_STATE_NO_WAIT;
        }
    }
}

static void aQMgr_actor_clear_regist(aQMgr_regist_c* regist, int count) {
    for (count; count != 0; count--) {
        regist->check_limit_proc = (aQMgr_CHECK_LIMIT_PROC)&none_proc1;
        regist->check_finish_proc = NULL;
        regist->quest_info = NULL;
        regist->pid = NULL;
        mNpc_ClearAnimalPersonalID(&regist->from_id);
        mNpc_ClearAnimalPersonalID(&regist->to_id);
        regist->animal_idx = -1;
        regist++;
    }
}

static int aQMgr_actor_check_fin_item(mQst_base_c* quest_info, Animal_c* animal) {
    mQst_contest_c* contest = (mQst_contest_c*)quest_info;
    int res = FALSE;

    if (mPr_GetPossessionItemIdx(Common_Get(now_private), contest->requested_item) != -1) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_free_regist(QUEST_MANAGER_ACTOR* manager, int start_idx) {
    aQMgr_regist_c* regist = &manager->regist[start_idx];
    int idx = -1;

    if (manager->regist_use_no < aQMgr_REGIST_NUM) {
        int i;

        for (i = start_idx; i < aQMgr_REGIST_NUM; i++) {
            if (regist->quest_info == NULL) {
                idx = i;
                break;
            }

            regist++;
        }
    }

    return idx;
}

static void aQMgr_actor_regist_quest(QUEST_MANAGER_ACTOR* manager, int* idx, aQMgr_quest_c* quest, int animal_idx) {
    mQst_base_c* quest_info = &quest->base;
    u32 type = quest_info->quest_type;

    if (type < mQst_QUEST_TYPE_NUM) {
        *idx = aQMgr_actor_free_regist(manager, *idx);

        if (*idx != -1) {
            int kind = quest_info->quest_kind;
            int max_kind = l_proc_max[type];

            if (kind >= 0 && kind < max_kind) {
                aQMgr_regist_c* regist = &manager->regist[*idx];
                AnmPersonalID_c* from_id;
                AnmPersonalID_c* to_id;
                Animal_c* animal;

                if (type == mQst_QUEST_TYPE_CONTEST) {
                    animal = &Save_Get(animals[animal_idx]);
                    regist->pid = &quest->contest.player_id;
                    regist->check_limit_proc = l_contest_proc[kind];
                    regist->check_finish_proc = l_contest_check[kind];
                    from_id = &animal->id;
                    to_id = &animal->id;
                }
                else {
                    if (type == mQst_QUEST_TYPE_ERRAND) {
                        regist->check_limit_proc = l_errand_proc[kind];
                    }

                    from_id = &quest->delivery.sender;
                    to_id = &quest->delivery.recipient;
                    regist->pid = &Common_Get(now_private)->player_ID;
                }

                mNpc_CopyAnimalPersonalID(&regist->from_id, from_id);
                mNpc_CopyAnimalPersonalID(&regist->to_id, to_id);

                regist->quest_info = quest_info;

                switch (type) {
                    case mQst_QUEST_TYPE_DELIVERY:
                        regist->item = Common_Get(now_private)->inventory.pockets[animal_idx];
                        break;
                    case mQst_QUEST_TYPE_ERRAND:
                        regist->item = quest->errand.item;
                        break;
                    case mQst_QUEST_TYPE_CONTEST:
                        regist->item = quest->contest.requested_item;
                        break;
                }

                regist->animal_idx = animal_idx;
                manager->regist_use_no++;
            }
        }
    }
}

static void aQMgr_talk_clear_talk_order(aQMgr_order_c* demo_order) {
    demo_order->type = mDemo_TYPE_NONE;
    demo_order->value = 0;
}

static int aQMgr_talk_common_clear_talk_info(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_target_c* target_p = &manager->target;
    aQMgr_choice_c* choice_p = &manager->choice;
    int i;

    *manager->memory = NULL;
    manager->talk_step = 0;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    manager->handover_item = EMPTY_NO;
    manager->msg_no = 0;
    manager->category_msg_no_start = 0;
    manager->msg_category = aQMgr_MSG_KIND_NONE;
    
    mQst_ClearQuestInfo(&target_p->quest_info);
    target_p->from_id = NULL;
    target_p->to_id = NULL;
    target_p->quest_inv_item_idx = -1;
    target_p->quest_item = EMPTY_NO;
    target_p->reward_kind = -1;
    target_p->reward_item = EMPTY_NO;
    target_p->pay = 0;
    target_p->set_data_p = NULL;
    target_p->free_data_idx = -1;
    target_p->free_data_p = NULL;
    target_p->errand_type = mQst_ERRAND_TYPE_NONE;
    bzero(&target_p->work, sizeof(target_p->work));

    choice_p->choice_num = 0;
    choice_p->talk_action = -1;

    for (i = 0; i < mChoice_CHOICE_NUM; i++) {
        choice_p->choice_ids[i] = -1;
    }

    manager->regist_idx = -1;
    manager->talk_type = aQMgr_TALK_KIND_QUEST;
    manager->talk_change_type = aQMgr_TALK_KIND_NUM;
    aQMgr_talk_clear_talk_order(&manager->demo_order);
    return TRUE;
}

static int aQMgr_talk_common_get_item_idx(QUEST_MANAGER_ACTOR* manager) {
    int regist_idx = manager->regist_idx;
    aQMgr_regist_c* regist = &manager->regist[regist_idx];
    mQst_base_c* quest_info = regist->quest_info;
    int idx = -1;

    if (quest_info != NULL) {
        int type = quest_info->quest_type;
        int kind = quest_info->quest_kind;

        if (type == mQst_QUEST_TYPE_DELIVERY) {
            idx = regist->animal_idx; // reused here I guess
        }
        else if (type == mQst_QUEST_TYPE_ERRAND) {
            idx = ((mQst_errand_c*)quest_info)->pockets_idx;
        }
        else if (type == mQst_QUEST_TYPE_CONTEST) {
            mActor_name_t item = ((mQst_contest_c*)quest_info)->requested_item;
            Private_c* priv = Common_Get(now_private);

            switch (kind) {
                case mQst_CONTEST_KIND_FISH:
                    idx = mPr_GetPossessionItemIdxItem1Category(priv, ITEM1_CAT_FISH);
                    break;
                case mQst_CONTEST_KIND_INSECT:
                    idx = mPr_GetPossessionItemIdxItem1Category(priv, ITEM1_CAT_INSECT);
                    break;
                default:
                    idx = mPr_GetPossessionItemIdx(priv, item);
                    break;
            }
        }
    }

    return idx;
}

static int aQMgr_talk_common_set_choice_str(QUEST_MANAGER_ACTOR* manager) {
    u8 str[mChoice_CHOICE_NUM][mChoice_CHOICE_STRING_LEN];
    u8* str_p_tbl[mChoice_CHOICE_NUM];
    aQMgr_choice_c* choice_p = &manager->choice;
    int i;

    for (i = 0; i < mChoice_CHOICE_NUM; i++) {
        str_p_tbl[i] = NULL;
    }

    for (i = 0; i < choice_p->choice_num; i++) {
        if (i >= mChoice_CHOICE_NUM) {
            break;
        }

        mChoice_Load_ChoseStringFromRom(mChoice_Get_base_window_p(), str[i], choice_p->choice_ids[i], NULL);
        str_p_tbl[i] = str[i];
    }

    //clang-format off
    mChoice_Set_choice_data(
        mChoice_Get_base_window_p(),
        str_p_tbl[0], mChoice_CHOICE_STRING_LEN,
        str_p_tbl[1], mChoice_CHOICE_STRING_LEN,
        str_p_tbl[2], mChoice_CHOICE_STRING_LEN,
        str_p_tbl[3], mChoice_CHOICE_STRING_LEN,
                NULL, mChoice_CHOICE_STRING_LEN,
                NULL, mChoice_CHOICE_STRING_LEN
    );
    //clang-format on

    return TRUE;
}

static int aQMgr_talk_common_get_set_data_p(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_target_c* target = &manager->target;
    mQst_base_c* quest_info = &target->quest_info;
    aQMgr_set_data_c* set_data_p = NULL;

    if (quest_info != NULL) {
        int type = quest_info->quest_type;
        int kind = quest_info->quest_kind;

        set_data_p = &l_set_data[type][kind];
    }

    target->set_data_p = set_data_p;
    return TRUE;
}

static void aQMgr_actor_init_quest(QUEST_MANAGER_ACTOR* manager) {
    mQst_delivery_c* delivery = Common_Get(now_private)->deliveries;
    mQst_errand_c* errand = Common_Get(now_private)->errands;
    Animal_c* animal = Save_Get(animals);
    int free_idx = 0;
    int i;

    for (i = 0; i < mPr_DELIVERY_QUEST_NUM; i++) {
        if (free_idx == -1) {
            break;
        }

        aQMgr_actor_regist_quest(manager, &free_idx, (aQMgr_quest_c*)delivery, i);
        delivery++;
    }

    for (i = 0; i < mPr_ERRAND_QUEST_NUM; i++) {
        if (free_idx == -1) {
            break;
        }

        aQMgr_actor_regist_quest(manager, &free_idx, (aQMgr_quest_c*)errand, i);
        errand++;
    }

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (free_idx == -1) {
            break;
        }

        aQMgr_actor_regist_quest(manager, &free_idx, (aQMgr_quest_c*)&animal->contest_quest, i);
        animal++;
    }
}

static void aQMgr_actor_regist_quest_move(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_regist_c* regist = manager->regist;
    int i;

    for (i = aQMgr_REGIST_NUM; i != 0; i--) {
        if (regist->quest_info != NULL) {
            if (regist->check_limit_proc != NULL) {
                (*regist->check_limit_proc)(manager, regist);
            }
        }

        regist++;
    }
}

static void aQMgr_actor_move_wait(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_actor_init_quest(manager);
    aQMgr_actor_regist_quest_move(manager);
    (*manager->clear_regist_proc)(manager->regist, aQMgr_REGIST_NUM);
    manager->regist_idx = -1;
    manager->regist_use_no = 0;
    mNpc_TalkInfoMove();
}

static void aQMgr_actor_move_talk_fin(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_actor_init_quest(manager);
    aQMgr_actor_regist_quest_move(manager);
    (*manager->clear_regist_proc)(manager->regist, aQMgr_REGIST_NUM);
    manager->regist_idx = -1;
    manager->regist_use_no = 0;
}

static int aQMgr_actor_get_my_msg(int base_msg, int looks) {
    int msg_no = base_msg + looks * 3;
    msg_no += mQst_GetRandom(3);
    
    return msg_no;
}

static int aQMgr_actor_decide_quest_message_no(aQMgr_target_c* target, int msg_type) {
    aQMgr_set_data_c* set_data_p = target->set_data_p;

    return set_data_p->msg_start[msg_type];
}

static int aQMgr_talk_common_set_msg_no(QUEST_MANAGER_ACTOR* manager) {
    int base_msg;
    int msg_no;

    if (manager->msg_category != aQMgr_MSG_KIND_NONE) {
        manager->category_msg_no_start = aQMgr_actor_decide_quest_message_no(&manager->target, manager->msg_category);
    }

    base_msg = manager->category_msg_no_start;
    if (base_msg != 15 && base_msg != 0) {
        int looks = mNpc_GetNpcLooks(*manager->client);
        
        msg_no = aQMgr_actor_get_my_msg(base_msg, looks);
    }
    else {
        msg_no = base_msg;
    }

    manager->msg_no = msg_no;
    manager->msg_category = aQMgr_MSG_KIND_NONE;
    manager->category_msg_no_start = 0;
    return TRUE;
}

static int aQMgr_talk_common_regist_set_target(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_target_c* target = &manager->target;
    aQMgr_regist_c* regist = &manager->regist[manager->regist_idx];
    mQst_base_c* quest_info = &target->quest_info;
    mQst_base_c* src_info = regist->quest_info;

    quest_info->quest_type = src_info->quest_type;
    quest_info->quest_kind = src_info->quest_kind;

    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_GET_SET_DATA);
    
    target->quest_item = regist->item;
    target->to_id = &regist->to_id;
    target->from_id = &regist->from_id;
    return TRUE;
}

static int aQMgr_talk_common_change_talk_normal(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_state = aQMgr_TALK_STATE_INIT;
    manager->talk_change_type = aQMgr_TALK_KIND_NORMAL;
    manager->talk_step = 0;
    manager->choice.talk_action = -1;
    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    return TRUE;
}

static int aQMgr_talk_common_change_talk_island(QUEST_MANAGER_ACTOR* manager) {
    manager->talk_state = aQMgr_TALK_STATE_INIT;
    manager->talk_change_type = aQMgr_TALK_KIND_ISLAND;
    manager->talk_step = 0;
    manager->choice.talk_action = -1;
    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    return TRUE;
}

static int aQMgr_set_npc_putaway() {
    int res = FALSE;

    if (Common_Get(clip).handOverItem_clip->request_mode == aHOI_REQUEST_TRANS_WAIT) {
        mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 3, 3);
        res = TRUE;
    }

    return res;
}

static int aQMgr_talk_common_set_npc_takeout(mActor_name_t item) {
    mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 3, 2);
    mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 0, item);
    mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 1, 7);
    mDemo_Set_OrderValue(mDemo_ORDER_NPC1, 2, 0);
    return TRUE;
}

static int aQMgr_talk_common_set_npc_takeout_item(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_common_set_npc_takeout(manager->target.quest_item);
    return TRUE;
}

static int aQMgr_talk_common_set_npc_takeout_reward(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_common_set_npc_takeout(manager->target.reward_item);
    return TRUE;
}

static int aQMgr_check_npc_hand_item() {
    int res = FALSE;

    if (l_aQMgr_hand_start == FALSE && Common_Get(clip).handOverItem_clip->master_actor != NULL) {
        l_aQMgr_hand_start = TRUE;
    }

    if (l_aQMgr_hand_start && Common_Get(clip).handOverItem_clip->master_actor == NULL) {
        mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
        l_aQMgr_hand_start = FALSE;
        res = TRUE;
    }

    return res;
}

typedef int (*aQMgr_COMMON_PROC)(QUEST_MANAGER_ACTOR*);

static int aQMgr_talk_common_proc(QUEST_MANAGER_ACTOR* manager, int proc) {
    static aQMgr_COMMON_PROC common_proc[aQMgr_TALK_COMMON_NUM] = {
        &aQMgr_talk_common_regist_set_target,
        &aQMgr_talk_common_get_item_idx,
        &aQMgr_talk_common_set_msg_no,
        &aQMgr_talk_common_clear_talk_info,
        &aQMgr_talk_common_set_choice_str,
        &aQMgr_talk_common_get_set_data_p,
        &aQMgr_talk_common_set_npc_takeout_item,
        &aQMgr_talk_common_set_npc_takeout_reward,
        &aQMgr_talk_common_talk_init_ovl,
        &aQMgr_talk_common_change_talk_normal,
        &aQMgr_talk_common_change_talk_island
    };

    return (*common_proc[proc])(manager);
}

#include "../src/actor/ac_quest_errand.c_inc"
#include "../src/actor/ac_quest_contest.c_inc"

static void aQMgr_clear_talk_wait_info(aQMgr_talk_wait_info_c* wait_info) {
    bzero(wait_info, sizeof(aQMgr_talk_wait_info_c));
}

static int aQMgr_actor_move_talk_sub_no_wait(QUEST_MANAGER_ACTOR* manager) {
    return TRUE;
}

static int aQMgr_actor_move_talk_sub_wait(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;

    if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == TRUE) {
        if (manager->wait_info.flags[2] == FALSE) {
            manager->wait_info.flags[2] = TRUE;
            res = TRUE;
        }
    }
    else {
        manager->wait_info.flags[2] = FALSE;
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_msg_disappear_wait(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;

    if (mMsg_Check_main_wait(mMsg_Get_base_window_p()) == TRUE) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_msg_appear_wait(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;

    if (mMsg_Check_not_series_main_wait(mMsg_Get_base_window_p()) == TRUE) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_check_button(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;

    if (mMsg_Check_MainNormal(mMsg_Get_base_window_p()) == FALSE) {
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_hand_item_wait(QUEST_MANAGER_ACTOR* manager) {
    Submenu* submenu = manager->submenu;
    int res = FALSE;

    if (submenu->open_flag == FALSE) {
        manager->handover_item = submenu->item_p->item;
        res = TRUE;

        if (manager->mail_memory != NULL) {
            mNpc_Mail2AnimalMail(&manager->mail_memory->letter, &manager->mail);
            manager->mail_memory->letter_info.exists = TRUE;
        }
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_npc_hand_wait(QUEST_MANAGER_ACTOR* manager) {
    return aQMgr_set_npc_putaway();
}

static int aQMgr_actor_move_talk_sub_item_wait(QUEST_MANAGER_ACTOR* manager) {
    return aQMgr_check_npc_hand_item();
}

static int aQMgr_actor_move_talk_sub_demo_order_wait(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_order_c* order = &manager->demo_order;
    int res = FALSE;
    int i;
    
    for (i = 0; i < mDemo_ORDER_VALUE_MAX; i++) {
        u16 value = mDemo_Get_OrderValue(mDemo_ORDER_QUEST, i);

        if (value != 0) {
            order->type = i;
            order->value = value;
            mDemo_Set_OrderValue(mDemo_ORDER_QUEST, i, 0);
            res = TRUE;
            break;
        }
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_npc_hand_wait_msg_wait(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;
    
    if (manager->wait_info.flags[0] == FALSE) {
        manager->wait_info.flags[0] = aQMgr_set_npc_putaway();
        mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    }

    if (manager->wait_info.flags[1] == FALSE) {
        if (mMsg_Check_MainNormalContinue(mMsg_Get_base_window_p()) == TRUE) {
            manager->wait_info.flags[1] = TRUE;
        }
    }

    if (manager->wait_info.flags[0] == TRUE && manager->wait_info.flags[1] == TRUE) {
        manager->wait_info.flags[0] = FALSE;
        manager->wait_info.flags[1] = FALSE;
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_item_wait_end(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;
    
    if (manager->wait_info.flags[0] == FALSE) {
        manager->wait_info.flags[0] = aQMgr_set_npc_putaway();
    }

    if (manager->wait_info.flags[0] == TRUE) {
        manager->wait_info.flags[1] = aQMgr_check_npc_hand_item();
    }

    if (manager->wait_info.flags[0] == TRUE && manager->wait_info.flags[1] == TRUE) {
        manager->wait_info.flags[0] = FALSE;
        manager->wait_info.flags[1] = FALSE;
        res = TRUE;
    }

    return res;
}

static int aQMgr_actor_move_talk_sub_item_player_wait(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;
    
    if (manager->wait_info.flags[0] == FALSE) {
        manager->wait_info.flags[0] = aQMgr_check_npc_hand_item();
    }

    mMsg_Set_LockContinue(mMsg_Get_base_window_p());
    if (manager->wait_info.flags[0] == TRUE && mPlib_check_player_actor_main_index_RecieveMove(gamePT) == FALSE) {
        mMsg_Unset_LockContinue(mMsg_Get_base_window_p());
        manager->wait_info.flags[0] = FALSE;
        res = TRUE;
    }

    return res;
}

static void aQMgr_select_talk(QUEST_MANAGER_ACTOR* manager) {
    u32 event_id;
    Animal_c* animal = ((NPC_ACTOR*)*manager->client)->npc_info.animal;

    event_id = mEv_SAVED_FJOPENQUEST_PLR0 + Common_Get(player_no);
    aQMgr_actor_init_quest(manager);
    aQMgr_clear_talk_wait_info(&manager->wait_info);

    if ((animal != NULL && mNpc_CheckIslandAnimal(animal) == TRUE) || (mLd_PlayerManKindCheck() == FALSE && mEv_CheckEvent(event_id) == TRUE)) {
        manager->talk_type = aQMgr_TALK_KIND_QUEST;
    }
    else if (mEv_CheckFirstJob() == TRUE) {
        manager->talk_type = aQMgr_TALK_KIND_FIRST_JOB;
    }
    else {
        manager->talk_type = aQMgr_TALK_KIND_QUEST;
    }

    *manager->mode = aQMgr_MODE_MOVE_TALK;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_TALK_INIT_OVL);
}

static int aQMgr_talk_init(QUEST_MANAGER_ACTOR* manager) {
    int res = FALSE;

    if (manager->talk_init_proc != NULL) {
        (*manager->talk_init_proc)(manager);
        res = TRUE;
    }

    return res;
}

typedef int (*aQMgr_TALK_SUB_PROC)(QUEST_MANAGER_ACTOR*);

static int aQMgr_talk_sub(QUEST_MANAGER_ACTOR* manager) {
    int sub_mode = manager->sub_talk_state;
    static aQMgr_TALK_SUB_PROC talk_sub_proc[] = { 
        &aQMgr_actor_move_talk_sub_wait,
        &aQMgr_actor_move_talk_sub_msg_disappear_wait,
        &aQMgr_actor_move_talk_sub_msg_appear_wait,
        &aQMgr_actor_move_talk_sub_check_button,
        &aQMgr_actor_move_talk_sub_hand_item_wait,
        &aQMgr_actor_move_talk_sub_npc_hand_wait,
        &aQMgr_actor_move_talk_sub_item_wait,
        &aQMgr_actor_move_talk_sub_demo_order_wait,
        &aQMgr_actor_move_talk_sub_no_wait,
        &aQMgr_actor_move_talk_sub_npc_hand_wait_msg_wait,
        &aQMgr_actor_move_talk_sub_item_wait_end,
        &aQMgr_actor_move_talk_sub_item_player_wait
    };

    int res = (*talk_sub_proc[sub_mode])(manager);

    if (res == TRUE) {
        manager->talk_state = aQMgr_TALK_STATE_INIT;
    }

    return res;
}

typedef int (*aQMgr_TALK_PROC)(QUEST_MANAGER_ACTOR*);

static void aQMgr_move_talk(QUEST_MANAGER_ACTOR* manager) {
    ACTOR* client = *manager->client;
    
    if (mDemo_Get_talk_actor() == client) {
        static aQMgr_TALK_PROC talk_proc[aQMgr_TALK_STATE_NUM] = {
            &aQMgr_talk_init,
            &aQMgr_talk_sub
        };
        int sub_res;

        aQMgr_actor_change_talk_init_ovl(manager);
        sub_res = (*talk_proc[aQMgr_TALK_STATE_SUB])(manager);
        mDemo_Set_OrderValue(mDemo_ORDER_QUEST, 0, 0);

        if (sub_res == TRUE) {
            (*talk_proc[aQMgr_TALK_STATE_INIT])(manager);
        }

        aQMgr_talk_clear_talk_order(&manager->demo_order);
    }

    if (mDemo_CheckDemo() == FALSE || mDemo_Check(mDemo_TYPE_TALK, client) == FALSE) {
        (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_CLEAR_TALK_INFO);
        *manager->mode = aQMgr_MODE_TALK_FIN;
        aQMgr_clear_talk_init_ovl(manager);

        if (client != NULL && client->part == ACTOR_PART_NPC) {
            Animal_c* animal = ((NPC_ACTOR*)client)->npc_info.animal;

            if (animal != NULL) {
                Anmmem_c* memory;
                int memory_idx = mNpc_GetAnimalMemoryIdx(&Common_Get(now_private)->player_ID, animal->memories, ANIMAL_MEMORY_NUM);

                if (memory_idx != -1) {
                    memory = animal->memories + memory_idx;
                    lbRTC_TimeCopy(&memory->last_speak_time, Common_GetPointer(time.rtc_time));

                    if (mNpc_CheckIslandAnimal(animal) == FALSE) {
                        mLd_CopyLandName(memory->memuni.land.name, Save_Get(land_info).name);
                        memory->memuni.land.id = Save_Get(land_info).id;
                    }

                    memory->saved_town_tune = Save_Get(melody);
                }
            }
        }

        {
            Animal_c* animal = ((NPC_ACTOR*)*manager->client)->npc_info.animal;
            int animal_idx = mNpc_SearchAnimalPersonalID(&animal->id);

            if (mNpc_CheckIslandAnimal(animal) == TRUE) {
                mNpc_TalkEndMove(mNpc_ISLANDER_NO, animal->id.looks);
            }
            else {
                mNpc_TalkEndMove(animal_idx, animal->id.looks);
            }
        }
    }
}

static void aQMgr_talk_start_kamakura_common(QUEST_MANAGER_ACTOR* manager, u8 step) {
    aQMgr_clear_talk_wait_info(&manager->wait_info);
    *manager->mode = aQMgr_MODE_MOVE_TALK;
    manager->talk_step = step;
    manager->talk_type = aQMgr_TALK_KIND_NORMAL;
    (*manager->talk_common_proc)(manager, aQMgr_TALK_COMMON_TALK_INIT_OVL);
    aQMgr_talk_init(manager);
}

static void aQMgr_talk_start_kamakura_hello(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_start_kamakura_common(manager, 8);
}

static void aQMgr_talk_start_kamakura(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_start_kamakura_common(manager, 9);
}

static void aQMgr_talk_start_summercamp_hello(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_start_kamakura_common(manager, 10);
}

static void aQMgr_talk_start_summercamp(QUEST_MANAGER_ACTOR* manager) {
    aQMgr_talk_start_kamakura_common(manager, 11);
}

typedef void (*aQMgr_MOVE_PROC)(QUEST_MANAGER_ACTOR*);
static void aQMgr_actor_move_main(ACTOR* actorx, GAME* game) {
    QUEST_MANAGER_ACTOR* manager = (QUEST_MANAGER_ACTOR*)actorx;
    static aQMgr_MOVE_PROC move_proc[aQMgr_MODE_NUM] = {
        &aQMgr_actor_move_wait,
        &aQMgr_select_talk,
        &aQMgr_move_talk,
        &aQMgr_actor_move_talk_fin,
        &aQMgr_talk_start_kamakura_hello,
        &aQMgr_talk_start_kamakura,
        &aQMgr_talk_start_summercamp_hello,
        &aQMgr_talk_start_summercamp
    };

    u8 mode = *manager->mode;

    if (mEv_IsNotTitleDemo()) {
        (*move_proc[mode])(manager);
    }

    {
        GRAPH* graph = game->graph;
        gfxprint_t gfxprint;
        Gfx* gfx;
        gfxprint_t* gfxprint_p = &gfxprint;
        Gfx* gfx_work;

        if (ZURUMODE2_ENABLED()) {
            gfxprint_init(gfxprint_p);
            
            OPEN_DISP(graph);
            gfx = NOW_POLY_OPA_DISP;
            gfx_work = gfxopen(gfx);

            gSPDisplayList(NEXT_OVERLAY_DISP, gfx_work);
            gfxprint_open(gfxprint_p, gfx_work);
            gfxprint_color(gfxprint_p, 245, 50, 50, 255);
            gfxprint_locate8x8(gfxprint_p, 22, 3);
            gfxprint_printf(gfxprint_p, "msg no :");
            gfxprint_locate8x8(gfxprint_p, 30, 3);
            gfxprint_printf(gfxprint_p, "%5d", mFRm_get_msg_idx());

            {
            mEv_gst_common_c* ghost_common = (mEv_gst_common_c*)mEv_get_common_area(mEv_EVENT_GHOST, 55);

            if (ghost_common != NULL) {
                int i;
                
                gfxprint_color(gfxprint_p, 45, 250, 50, 255);

                for (i = 0; i < mEv_GHOST_HITODAMA_NUM; i++) {
                    gfxprint_locate8x8(gfxprint_p, 30, 19 + i);
                    gfxprint_printf(gfxprint_p, "%3d,%3d", ghost_common->hitodama_block_data.block_x[i], ghost_common->hitodama_block_data.block_z[i]);
                }
            }
            }

            gfx_work = gfxprint_close(gfxprint_p);
            gSPEndDisplayList(gfx_work++);
            gfxclose(gfx, gfx_work);
            SET_POLY_OPA_DISP(gfx_work);
            CLOSE_DISP(graph);

            gfxprint_cleanup(gfxprint_p);
        }
    }
}

static void aQMgr_actor_ct(ACTOR* actorx, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;
    QUEST_MANAGER_ACTOR* manager = (QUEST_MANAGER_ACTOR*)actorx;

    if (Common_Get(clip).quest_manager_clip == NULL) {
        Common_Get(clip).quest_manager_clip = (aQMgr_Clip_c*)zelda_malloc(sizeof(aQMgr_Clip_c));
    }

    Common_Get(clip).quest_manager_clip->talk_request_proc = &aQMgr_actor_talk_request;
    Common_Get(clip).quest_manager_clip->talk_start_proc = &aQMgr_actor_talk_start;
    Common_Get(clip).quest_manager_clip->talk_check_proc = &aQMgr_actor_talk_check;

    l_client_p = NULL;
    l_quest_manager_mode = aQMgr_MODE_NORMAL;
    l_quest_memory_p = NULL;
    l_quest_actor_p = NULL;
    l_quest_manager_hello = FALSE;

    manager->client = &l_client_p;
    manager->memory = &l_quest_memory_p;
    manager->submenu = &play->submenu;
    manager->mode = &l_quest_manager_mode;
    manager->talk_state = aQMgr_TALK_STATE_INIT;
    manager->sub_talk_state = aQMgr_TALK_SUB_STATE_WAIT;
    
    aQMgr_talk_common_clear_talk_info(manager);
    aQMgr_actor_clear_regist(manager->regist, aQMgr_REGIST_NUM);
    manager->regist_idx = -1;
    manager->regist_use_no = 0;
    aQMgr_actor_init_quest(manager);
    manager->talk_common_proc = &aQMgr_talk_common_proc;
    manager->clear_regist_proc = &aQMgr_actor_clear_regist;
    manager->regist_quest_proc = &aQMgr_actor_regist_quest;
    manager->get_time_kind_proc = &aQMgr_get_time_kind;
    bzero(manager->errand_next, sizeof(manager->errand_next));
    manager->clip = NULL;
    aQMgr_clear_talk_init_ovl(manager);
    aQMgr_clear_talk_wait_info(&manager->wait_info);
    l_aQMgr_hand_start = FALSE;
    l_quest_actor_p = (QUEST_MANAGER_ACTOR*)actorx; // l_quest_actor_p is probably just ACTOR*
    mem_clear(manager->last_strings, 7, 0xFF);
    manager->give_item = EMPTY_NO;
}

static void aQMgr_actor_dt(ACTOR* actorx, GAME* game) {
    QUEST_MANAGER_ACTOR* manager = (QUEST_MANAGER_ACTOR*)actorx;

    if (Common_Get(clip).quest_manager_clip != NULL) {
        zelda_free(Common_Get(clip).quest_manager_clip);
        Common_Get(clip).quest_manager_clip = NULL;
    }

    if (manager->clip != NULL) {
        zelda_free(manager->clip);
    }
}

typedef void (*aQMgr_SAVE_PROC)(aQMgr_regist_c*);

static void aQMgr_actor_save(ACTOR* actorx, GAME* game) {
    QUEST_MANAGER_ACTOR* manager = (QUEST_MANAGER_ACTOR*)actorx;
    aQMgr_regist_c* regist = manager->regist;
    static aQMgr_SAVE_PROC save_proc[mQst_QUEST_TYPE_NUM] = {
        (aQMgr_SAVE_PROC)&none_proc1,
        (aQMgr_SAVE_PROC)&none_proc1,
        &aQMgr_save_contest
    };
    int i;

    aQMgr_actor_init_quest(manager);
    for (i = 0; i < aQMgr_REGIST_NUM; i++) {
        if (regist->quest_info != NULL) {
            int type = regist->quest_info->quest_type;

            if (type >= 0 && type < mQst_QUEST_TYPE_NUM) {
                (*save_proc[type])(regist);
            }
        }

        regist++;
    }
}

ACTOR_PROFILE Quest_Manager_Profile = {
    mAc_PROFILE_QUEST_MANAGER,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(QUEST_MANAGER_ACTOR),
    &aQMgr_actor_ct,
    &aQMgr_actor_dt,
    &aQMgr_actor_move_main,
    mActor_NONE_PROC1,
    &aQMgr_actor_save
};
