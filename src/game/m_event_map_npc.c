#include "m_event_map_npc.h"

#include "m_actor_type.h"
#include "m_name_table.h"
#include "m_random_field_h.h"
#include "m_event.h"
#include "m_field_info.h"
#include "m_common_data.h"
#include "ac_set_npc_manager.h"

// clang-format off
static int l_event_map_type_table[] = {
    mEv_EVENT_FIREWORKS_SHOW,
    mEv_EVENT_CHERRY_BLOSSOM_FESTIVAL,
    mEv_EVENT_SPORTS_FAIR_FOOT_RACE,
    mEv_EVENT_SPORTS_FAIR_AEROBICS,
    mEv_EVENT_SPORTS_FAIR_BALL_TOSS,
    mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR,
    mEv_EVENT_HALLOWEEN,
    mEv_EVENT_NEW_YEARS_DAY,
    mEv_EVENT_FISHING_TOURNEY_1,
    mEv_EVENT_FISHING_TOURNEY_2,
    mEv_EVENT_MORNING_AEROBICS,
    mEv_EVENT_HARVEST_MOON_FESTIVAL,
    mEv_EVENT_HARVEST_FESTIVAL,
    mEv_EVENT_NEW_YEARS_EVE_COUNTDOWN,
    mEv_EVENT_KAMAKURA,
    mEv_EVENT_GROUNDHOG_DAY,
    mEv_EVENT_METEOR_SHOWER,
};
// clang-format on

typedef struct event_map_actor_pos_s {
    u8 ux;
    u8 uz;
} mEvMN_actor_pos_c;

typedef struct event_map_actor_info_s {
    mActor_name_t* name_table;
    mEvMN_actor_pos_c* pos_table;
} mEvMN_actor_info_c;

typedef struct event_map_npc_data_s {
    u16 are_npc_flags;
    mActor_name_t cloth;
} mEvMN_npc_data_c;

typedef struct event_map_data_s {
    u8 get_npc_idx_type;
    u8 normal_npc_max; // max number of 'normal' npcs to pull in for the event
    u8 map_max; // max number of 'map' variants
    u8 npc_max; // max total number of npcs, both normal, special, and structure
    mEvMN_actor_info_c** actor_info;
    mEvMN_npc_data_c* npc_data;
    u32 block_kind;
} mEvMN_data_c;

#include "../src/game/m_event_map_npc_data.c_inc"

static int mEvMN_GetMapIdx_sub(int event_type) {
    int* event_type_p = l_event_map_type_table;
    int res = -1;
    int i;

    for (i = 0; i < mEvMN_TYPE_NUM; i++) {
        if (*event_type_p == event_type) {
            res = i;
            break;
        }

        event_type_p++;
    }

    return res;
}

extern int mEvMN_GetMapIdx(int event_type) {
    int res = mEvMN_GetMapIdx_sub(event_type);

    if (res != -1 && l_event_set_table[res] == NULL) {
        res = -1;
    }

    return res;
}

extern int mEvMN_GetEventTypeMap(void) {
    int* event_type_p = l_event_map_type_table;
    int res = -1;
    int i;

    for (i = 0; i < mEvMN_TYPE_NUM; i++) {
        if (mEv_check_status(*event_type_p, mEv_STATUS_ACTIVE)) {
            res = *event_type_p;
            break;
        }

        event_type_p++;
    }

    return res;
}

static int mEvMN_GetDataBaseIdx(u32 block_kind) {
    int res = 0;

    if (block_kind == mRF_BLOCKKIND_POOL) {
        res = mFI_GetPuleIdx();
    }

    return res;
}

extern u32 mEvMN_GetEventBlockKind(int map_type) {
    mEvMN_data_c* data_p = l_event_set_table[map_type];
    u32 block_kind = mRF_BLOCKKIND_NONE;

    if (data_p != NULL) {
        block_kind = data_p->block_kind;
    }

    return block_kind;
}

static int mEvMN_GetJointAllNpcMax(int map_type) {
    mEvMN_data_c* data_p = l_event_set_table[map_type];
    int npc_max = 0;

    if (data_p != NULL) {
        npc_max = data_p->npc_max;
    }

    return npc_max;
}

extern int mEvMN_GetJointNpcMax(int map_type) {
    mEvMN_data_c* data_p = l_event_set_table[map_type];
    int normal_npc_max = 0;

    if (data_p != NULL) {
        normal_npc_max = data_p->normal_npc_max;
    }

    return normal_npc_max;
}

extern int mEvMN_GetEventSetUtInBlockMapIdx(int* block_ux, int* block_uz, int map_type, int idx) {
    mEvMN_data_c* data_p;
    mEvMN_actor_pos_c* pos_p;
    mEvMN_actor_info_c* info_p;
    int base_idx;
    int res;

    res = FALSE;
    if (map_type >= 0 && map_type < mEvMN_TYPE_NUM) {
        data_p = l_event_set_table[map_type];

        if (data_p != NULL) {
            base_idx = mEvMN_GetDataBaseIdx(data_p->block_kind);
            info_p = data_p->actor_info[base_idx];
            pos_p = &info_p->pos_table[idx];
            *block_ux = pos_p->ux;
            *block_uz = pos_p->uz;
            res = TRUE;
        }
    }

    return res;
}

extern int mEvMN_GetEventSetUtInBlock(mActor_name_t* actor_name, int* block_ux, int* block_uz, int event_type,
                                      int idx) {
    mEvMN_data_c* data_p;
    mEvMN_actor_pos_c* pos_p;
    mEvMN_actor_info_c* info_p;
    int base_idx;
    int map_idx;
    int res;

    res = FALSE;
    map_idx = mEvMN_GetMapIdx(event_type);
    if (map_idx != -1) {
        data_p = l_event_set_table[map_idx];

        if (data_p != NULL) {
            base_idx = mEvMN_GetDataBaseIdx(data_p->block_kind);
            info_p = data_p->actor_info[base_idx];
            pos_p = &info_p->pos_table[idx];
            *actor_name = info_p->name_table[idx];
            *block_ux = pos_p->ux;
            *block_uz = pos_p->uz;
            res = TRUE;
        }
    }

    return res;
}

static int mEvMN_CheckCanJointEvent(Anmmem_c* memory, PersonalID_c* pid) {
    int res = FALSE;

    if (mNpc_GetAnimalMemoryIdx(pid, memory, ANIMAL_MEMORY_NUM) != -1) {
        res = TRUE;
    }

    return res;
}

static void mEvMN_GetNpcIdxRandom(u8* animal_idx, int max) {
    Animal_c* animal = Save_Get(animals);
    int idx;
    int count = 0;
    int animal_count = 0;
    u16 animal_bitfield = 0;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal->id) == FALSE) {
            animal_count++;
            animal_bitfield |= 1 << i;
        }

        animal++;
    }

    animal_count -= max;
    animal -= ANIMAL_NUM_MAX;
    if (animal_count > 0 && mLd_PlayerManKindCheck() == FALSE) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (((animal_bitfield >> i) & 1) == 1 &&
                mEvMN_CheckCanJointEvent(animal->memories, &Now_Private->player_ID) == FALSE) {
                animal_count--;
                animal_bitfield &= ~(1 << i);

                if (animal_count <= 0) {
                    break;
                }
            }

            animal++;
        }
    }

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (((animal_bitfield >> i) & 1) == 1) {
            count++;
        }
    }

    if (count < max) {
        max = count;
    }

    while (count > 0 && max > 0) {
        if (animal_bitfield == 0) {
            break;
        }

        idx = RANDOM(count);
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (((animal_bitfield >> i) & 1) == 1) {
                if (idx <= 0) {
                    *animal_idx = (u8)i;
                    count--;
                    animal_bitfield &= ~(1 << i);
                    break;
                }

                idx--;
            }
        }

        if (i == ANIMAL_NUM_MAX) {
            break;
        }

        max--;
        animal_idx++;
    }
}

typedef void (*mEvMN_GET_NPC_IDX_PROC)(u8*, int);

static void mEvMN_GetNpcIdx(u8* animal_idx, int max, u8 type) {
    static mEvMN_GET_NPC_IDX_PROC get_npc_idx[] = { &mEvMN_GetNpcIdxRandom };

    (*get_npc_idx[type])(animal_idx, max);
}

extern void mEvMN_GetNpcJointEv(aSNMgr_event_save_c* event_data, int event_type) {
    int idx;
    mEvMN_data_c* data_p;

    idx = mEvMN_GetMapIdx(event_type);
    if (idx != -1) {
        data_p = l_event_set_table[idx];

        if (data_p != NULL) {
            mEvMN_GetNpcIdx(event_data->animal_idx, data_p->normal_npc_max, data_p->get_npc_idx_type);
        }
    }
}

static void mEvMN_ClearRemoveNpcJoint(u8* animal_idx, int max) {
    Animal_c* animal;
    int i;

    for (i = 0; i < max; i++) {
        if (*animal_idx != 0xFF && *animal_idx < ANIMAL_NUM_MAX) {
            animal = Save_GetPointer(animals[*animal_idx]);

            if (mNpc_CheckFreeAnimalInfo(animal) == TRUE) {
                *animal_idx = 0xFF;
            }
        }

        animal_idx++;
    }
}

static void mEvMN_SetNpcJointEvRandom(u8* animal_idx, int max) {
    Animal_c* animal = Save_Get(animals);
    int idx;
    u16 animal_bitfield = 0;
    int count = 0;
    int animal_count = 0;
    int req_count = 0;
    int i;
    int j;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (mNpc_CheckFreeAnimalPersonalID(&animal[i].id) == FALSE) {
            animal_count++;
            animal_bitfield |= 1 << i;
        }
    }

    for (i = 0; i < max; i++) {
        if (*animal_idx != 0xFF && *animal_idx < ANIMAL_NUM_MAX) {
            if (((animal_bitfield >> (*animal_idx)) & 1) == 1) {
                animal_count--;
            }

            animal_bitfield &= ~(1 << (*animal_idx));
        } else {
            req_count++;
        }

        animal_idx++;
    }

    animal_count -= max;
    animal_idx -= max;

    if (animal_count > 0 && mLd_PlayerManKindCheck() == FALSE) {
        Animal_c* sec_animal = animal;

        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (((animal_bitfield >> i) & 1) == 1 &&
                mEvMN_CheckCanJointEvent(sec_animal[i].memories, &Now_Private->player_ID) == FALSE) {
                animal_count--;
                animal_bitfield &= ~(1 << i);

                if (animal_count <= 0) {
                    break;
                }
            }
        }
    }

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (((animal_bitfield >> i) & 1) == 1) {
            count++;
        }
    }

    if (count < req_count) {
        req_count = count;
    }

    if (req_count > 0) {
        for (i = 0; i < max; i++) {
            if (animal_bitfield == 0 || count <= 0) {
                break;
            }

            if (*animal_idx == 0xFF) {
                idx = RANDOM(count); // @cleanup - we don't need this, it's leftover from a copy-paste job?

                for (j = 0; j < ANIMAL_NUM_MAX; j++) {
                    if (((animal_bitfield >> j) & 1) == 1) {
                        *animal_idx = (u8)j;
                        count--;
                        animal_bitfield &= ~(1 << j);
                        break;
                    }
                }
            }

            animal_idx++;
        }
    }
}

extern void mEvMN_SetNpcJointEv(aSNMgr_event_save_c* event_data, int event_type) {
    int idx = mEvMN_GetMapIdx(event_type);
    mEvMN_data_c* data_p;

    if (idx != -1) {
        data_p = l_event_set_table[idx];

        if (data_p != NULL) {
            mEvMN_ClearRemoveNpcJoint(event_data->animal_idx, data_p->normal_npc_max);
            mEvMN_SetNpcJointEvRandom(event_data->animal_idx, data_p->normal_npc_max);
        }
    }
}

static mNpc_EventNpc_c* mEvMN_CheckEventNpcList(mActor_name_t npc_name) {
    mNpc_EventNpc_c* event_npc = Common_Get(event_npc);
    mNpc_EventNpc_c* ret_npc = NULL;
    int i;

    for (i = 0; i < mNpc_EVENT_NPC_NUM; i++) {
        if (event_npc->in_use == TRUE && event_npc->npc_id == npc_name) {
            ret_npc = event_npc;
        }

        event_npc++;
    }

    return ret_npc;
}

static void mEvMN_GetFireWorksNpcName(mActor_name_t* npc_name, int map_type, int animal_idx, int idx) {
    int max_npc = l_event_set_table[map_type]->normal_npc_max;

    if (idx >= 0 && idx < max_npc && map_type >= 0 && map_type < mEvMN_TYPE_NUM) {
        mNpc_EventNpc_c* event_npc = mEvMN_CheckEventNpcList(*npc_name);

        if (event_npc == NULL) {
            mEvMN_data_c* data_p = l_event_set_table[map_type];

            if (data_p != NULL) {
                int base_idx = mEvMN_GetDataBaseIdx(data_p->block_kind);
                mEvMN_actor_info_c* info_p = data_p->actor_info[base_idx];
                mEvMN_npc_data_c* npc_p = data_p->npc_data;
                mActor_name_t spnpc_name = info_p->name_table[idx];
                mActor_name_t tex_name;
                mActor_name_t anm_name = *npc_name;
                mActor_name_t cloth_name;
                u16 check_bitfield = npc_p->are_npc_flags;

                if (((check_bitfield >> idx) & 1) == 1) {
                    cloth_name = npc_p->cloth;
                    tex_name = anm_name;

                    if (cloth_name != EMPTY_NO &&
                        mNpc_GetLooks2Sex(Save_Get(animals[animal_idx]).id.looks) == mPr_SEX_MALE) {
                        cloth_name++;
                    }
                } else {
                    tex_name = spnpc_name;
                    cloth_name = EMPTY_NO;
                }

                mNpc_RegistEventNpc(spnpc_name, tex_name, anm_name, cloth_name);
                *npc_name = spnpc_name;
            }
        } else {
            *npc_name = event_npc->event_id;
        }
    }
}

static void mEvMN_GetHalloweenNpcName(mActor_name_t* npc_name, int map_type, int animal_idx, int idx) {
    mNpc_EventNpc_c* event_npc = mEvMN_CheckEventNpcList(*npc_name);

    if (event_npc == NULL) {
        int free_idx = mNpc_GetFreeEventNpcIdx();

        if (free_idx != -1) {
            mActor_name_t event_name = SP_NPC_EV_HALLOWEEN_0 + free_idx;

            mNpc_RegistEventNpc(event_name, event_name, *npc_name, EMPTY_NO);
            *npc_name = event_name;
        }
    } else {
        *npc_name = event_npc->event_id;
    }
}

typedef void (*mEvMN_SET_NAME_PROC)(mActor_name_t*, int, int, int);

extern void mEvMN_GetEventNpcName(mActor_name_t* npc_name, int event_type, int animal_idx, int idx) {
    // clang-format off
    static mEvMN_SET_NAME_PROC set_name[] =  {
        &mEvMN_GetFireWorksNpcName,
        &mEvMN_GetFireWorksNpcName,
        &mEvMN_GetFireWorksNpcName,
        &mEvMN_GetFireWorksNpcName,
        &mEvMN_GetFireWorksNpcName,
        &mEvMN_GetFireWorksNpcName,
        &mEvMN_GetHalloweenNpcName,
        &mEvMN_GetFireWorksNpcName,
        &mEvMN_GetFireWorksNpcName,
        &mEvMN_GetFireWorksNpcName,
        &mEvMN_GetFireWorksNpcName,
        &mEvMN_GetFireWorksNpcName,
        &mEvMN_GetFireWorksNpcName,
        &mEvMN_GetFireWorksNpcName,
        &mEvMN_GetFireWorksNpcName,
        &mEvMN_GetFireWorksNpcName,
        &mEvMN_GetFireWorksNpcName,
    };
    // clang-format on

    int map_type = mEvMN_GetMapIdx_sub(event_type);

    if (map_type != -1) {
        (*set_name[map_type])(npc_name, map_type, animal_idx, idx);
    }
}

static int mEvMN_GetNpcIdxListJointEvent(u8** npc_idx_pp, int* npc_max_p) {
    aSNMgr_event_save_c* event_save_p;
    int event_type;
    int map_type;
    int res;

    res = FALSE;
    *npc_idx_pp = NULL;
    *npc_max_p = 0;
    event_type = mEvMN_GetEventTypeMap();

    if (event_type != -1) {
        map_type = mEvMN_GetMapIdx(event_type);

        if (map_type != -1) {
            event_save_p = (aSNMgr_event_save_c*)mEv_get_save_area(event_type, 15);

            if (event_save_p != NULL) {
                *npc_max_p = mEvMN_GetJointNpcMax(map_type);
                *npc_idx_pp = event_save_p->animal_idx;
                res = TRUE;
            }
        }
    }

    return res;
}

extern int mEvNM_CheckJointEvent(mActor_name_t npc_name) {
    u8* animal_idx_p;
    int npc_max;
    int animal_idx;
    int res;
    int i;

    res = FALSE;

    if (ITEM_NAME_GET_TYPE(npc_name) == NAME_TYPE_NPC &&
        mEvMN_GetNpcIdxListJointEvent(&animal_idx_p, &npc_max) == TRUE && animal_idx_p != NULL) {
        animal_idx = mNpc_SearchAnimalinfo(Save_Get(animals), npc_name, ANIMAL_NUM_MAX);

        if (animal_idx != -1) {
            for (i = 0; i < npc_max; i++) {
                if (*animal_idx_p != 0xFF && *animal_idx_p == (u8)animal_idx) {
                    res = TRUE;
                    break;
                }

                animal_idx_p++;
            }
        }
    }

    return res;
}

extern int mEvMN_GetJointEventRandomNpc(mActor_name_t* npc_name_p) {
    Animal_c* animal;
    u8* animal_idx_p;
    int npc_max;
    int sel_npc_idx;
    int sel_idx;
    int res;

    res = FALSE;
    if (mEvMN_GetNpcIdxListJointEvent(&animal_idx_p, &npc_max) == TRUE) {
        sel_idx = RANDOM(npc_max);
        sel_npc_idx = animal_idx_p[sel_idx];
        animal = Save_GetPointer(animals[sel_npc_idx]);
        *npc_name_p = animal->id.npc_id;
        res = TRUE;
    }

    return res;
}

extern int mEvMN_CheckLapPlayer(int block_ux, int block_uz) {
    int event_type;
    int map_type;
    int npc_max;
    mActor_name_t name;
    int ux;
    int uz;
    int res;
    int i;
    int j;
    int k;

    event_type = mEvMN_GetEventTypeMap();
    if (event_type != -1) {
        map_type = mEvMN_GetMapIdx(event_type);
        if (map_type != -1) {
            npc_max = mEvMN_GetJointAllNpcMax(map_type);
            if (npc_max > 0) {
                for (i = 0; i < npc_max; i++) {
                    mEvMN_GetEventSetUtInBlock(&name, &ux, &uz, event_type, i);

                    if (ITEM_NAME_GET_TYPE(name) == NAME_TYPE_STRUCT) {
                        res = mFI_CheckStructureArea(block_ux, block_uz, name, ux, uz);
                        if (res == TRUE) {
                            return 2;
                        }
                    } else {
                        for (j = -1; j < 2; j++) {
                            for (k = -1; k < 2; k++) {
                                if (block_ux == ux + k && block_uz == uz + j) {
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}
