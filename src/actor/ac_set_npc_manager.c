#include "ac_set_npc_manager.h"

#include "m_name_table.h"
#include "m_player_lib.h"
#include "m_field_info.h"
#include "m_common_data.h"
#include "libultra/libultra.h"
#include "m_random_field.h"
#include "m_event_map_npc.h"

static void aSNMgr_actor_ct(ACTOR* actorx, GAME* game);
static void aSNMgr_actor_dt(ACTOR* actorx, GAME* game);
static void aSNMgr_actor_move(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Set_Npc_Manager_Profile = {
    mAc_PROFILE_SET_NPC_MANAGER,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(SET_NPC_MANAGER_ACTOR),
    &aSNMgr_actor_ct,
    &aSNMgr_actor_dt,
    &aSNMgr_actor_move,
    mActor_NONE_PROC1,
    NULL,
};
// clang-format on

static int aSNMgr_get_player_pos(xyz_t* pos_p, GAME* game);
static void aSNMgr_renewal_player_now_block(SET_NPC_MANAGER_ACTOR* manager);
static void aSNMgr_renewal_set_scope(SET_NPC_MANAGER_ACTOR* manager);
static void aSNMgr_init_winfo_p(SET_NPC_MANAGER_ACTOR* manager);
static void aSNMgr_set_npc_exist(SET_NPC_MANAGER_ACTOR* manager);
static void aSNMgr_clear_make_npc(aSNMgr_make_c* make_p, int count);
static void aSNMgr_clear_event_info(aSNMgr_event_info_c* info_p);
static void aSNMgr_move_event_set(SET_NPC_MANAGER_ACTOR* manager);
static void aSNMgr_force_go_home_event_start(SET_NPC_MANAGER_ACTOR* manager);
static void aSNMgr_setup_set_proc(SET_NPC_MANAGER_ACTOR* manager, int mode);
static void aSNMgr_reset_event_npc_pos(SET_NPC_MANAGER_ACTOR* manager);

static void aSNMgr_actor_ct(ACTOR* actorx, GAME* game) {
    SET_NPC_MANAGER_ACTOR* manager = (SET_NPC_MANAGER_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    int i;

    aSNMgr_get_player_pos(&manager->player_pos.pos, game);
    aSNMgr_renewal_player_now_block(manager);
    mFI_Wpos2BlockNum(&manager->player_pos.next_block[0], &manager->player_pos.next_block[1], manager->player_pos.pos);
    aSNMgr_renewal_set_scope(manager);
    manager->npc_info.animal_p = Save_Get(animals);
    manager->npc_info.list_p = Common_Get(npclist);
    manager->npc_info.schedule_p = Common_Get(npc_schedule);
    manager->npc_info.walk_p = Common_GetPointer(npc_walk);
    aSNMgr_init_winfo_p(manager);
    bzero(manager->npc_info.in_block_num, sizeof(manager->npc_info.in_block_num));
    bzero(manager->npc_info.to_block, sizeof(manager->npc_info.to_block));

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        manager->npc_info.count_p[i] = mNpcW_GetArriveStayCountP(i);
    }

    aSNMgr_set_npc_exist(manager);
    manager->npc_info.appear = 0;
    manager->npc_info.joint_event = 0;
    aSNMgr_clear_make_npc(manager->npc_info.make, mNpc_EVENT_NPC_NUM);
    aSNMgr_clear_event_info(&manager->npc_info.event_info);

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (manager->npc_info.winfo_p[i] != NULL) {
            mNpcW_SetGoalBlock(manager->npc_info.winfo_p[i]);
        }
    }

    bzero(manager->npc_info.timer, sizeof(manager->npc_info.timer));
    
    if (play->fb_wipe_type == WIPE_TYPE_EVENT) {
        aSNMgr_move_event_set(manager);
        aSNMgr_force_go_home_event_start(manager);
    }

    aSNMgr_setup_set_proc(manager, aSNMgr_SET_MODE_REGULAR);
}

static void aSNMgr_actor_dt(ACTOR* actorx, GAME* game) {
    SET_NPC_MANAGER_ACTOR* manager = (SET_NPC_MANAGER_ACTOR*)actorx;

    aSNMgr_reset_event_npc_pos(manager);
}

static void aSNMgr_init_winfo_p(SET_NPC_MANAGER_ACTOR* manager) {
    mNpcW_info_c** winfo_p = manager->npc_info.winfo_p;
    mNpc_walk_c* walk_p = manager->npc_info.walk_p;
    Animal_c* animal_p = manager->npc_info.animal_p;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        int idx = mNpcW_GetNpcWalkInfoIdx(walk_p->info, mNpc_EVENT_NPC_NUM, &animal_p->id);

        if (idx != -1) {
            *winfo_p = &walk_p->info[idx];
        } else {
            *winfo_p = NULL;
        }

        winfo_p++;
        animal_p++;
    }
}

static void aSNMgr_set_npc_exist(SET_NPC_MANAGER_ACTOR* manager) {
    Animal_c* animal_p = manager->npc_info.animal_p;
    u16 exist = 0;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (!mNpc_CheckFreeAnimalPersonalID(&animal_p->id)) {
            exist |= 1 << i;
        }

        animal_p++;
    }

    manager->npc_info.exist = exist;
}

static void aSNMgr_clear_event_info(aSNMgr_event_info_c* info_p) {
    info_p->save_p = NULL;
    info_p->type = mEv_EVENT_NUM;
    info_p->event_map_idx = -1;
    info_p->joint_npc_max = 0;
}

static int aSNMgr_get_event_npc_idx(u8* idx_p, int count, int animal_idx) {
    int i;
    int ret = -1;

    for (i = 0; i < count; i++) {
        if (*idx_p == animal_idx) {
            ret = i;
            break;
        }

        idx_p++;
    }

    return ret;
}

static void aSNMgr_reset_event_npc_pos(SET_NPC_MANAGER_ACTOR* manager) {
    mNpc_NpcList_c* list_p = manager->npc_info.list_p;
    aSNMgr_event_info_c* info_p = &manager->npc_info.event_info;
    aSNMgr_event_save_c* save_p = manager->npc_info.event_info.save_p;
    int idx;
    int i;

    if (info_p->type != mEv_EVENT_NUM && list_p != NULL && save_p != NULL) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            idx = aSNMgr_get_event_npc_idx(save_p->animal_idx, info_p->joint_npc_max, i);

            if (idx != -1) {
                list_p[i].position.x = list_p[i].house_position.x;
                list_p[i].position.y = list_p[i].house_position.y;
                list_p[i].position.z = list_p[i].house_position.z;
            }
        }
    }
}

static int aSNMgr_chk_exist_and_appear(SET_NPC_MANAGER_ACTOR* manager, int appear_type, int idx) {
    int ret = FALSE;

    if (((manager->npc_info.exist >> idx) & 1) == 1 && appear_type == ((manager->npc_info.appear >> idx) & 1) &&
        manager->npc_info.list_p[idx].appear_flag == TRUE) {
        ret = TRUE;
    }
    
    return ret;
}

static int aSNMgr_chk_exist_and_appear_and_event(SET_NPC_MANAGER_ACTOR* manager, int appear_type, int idx) {
    int ret = FALSE;

    if (aSNMgr_chk_exist_and_appear(manager, appear_type, idx) && ((manager->npc_info.joint_event >> idx) & 1) == 0) {
        ret = TRUE;
    }

    return ret;
}

static int aSNMgr_chk_arbeit_and_demo_and_halloween(void) {
    int ret = TRUE;

    if (!mEv_CheckArbeit() && !mEv_CheckFirstIntro() && CLIP(demo_clip) == NULL && CLIP(demo_clip2) == NULL &&
        !mEv_check_status(mEv_EVENT_HALLOWEEN, mEv_STATUS_ACTIVE)) {
        ret = FALSE;
    }

    return ret;
}

static int aSNMgr_get_player_pos(xyz_t* pos_p, GAME* game) {
    int ret;
    ACTOR* player = GET_PLAYER_ACTOR_GAME_ACTOR(game);

    ret = FALSE;
    if (player != NULL) {
        *pos_p = player->world.position;
        ret = TRUE;
    }

    return ret;
}

static void aSNMgr_renewal_player_now_block(SET_NPC_MANAGER_ACTOR* manager) {
    mFI_Wpos2BlockNum(&manager->player_pos.now_block[0], &manager->player_pos.now_block[1], manager->player_pos.pos);
}

static void aSNMgr_renewal_player_next_block(SET_NPC_MANAGER_ACTOR* manager) {
    mFI_GetNextBlockNum(&manager->player_pos.next_block[0], &manager->player_pos.next_block[1]);
}

static void aSNMgr_renewal_set_scope(SET_NPC_MANAGER_ACTOR* manager) {
    static int block_wh[] = { mFI_BK_WORLDSIZE_X, mFI_BK_WORLDSIZE_Z };
    static f32 half_block_wh[] = { mFI_BK_WORLDSIZE_HALF_X_F, mFI_BK_WORLDSIZE_HALF_Z_F };
    static f32 r_add[] = { -mFI_BK_WORLDSIZE_HALF_X_F, mFI_BK_WORLDSIZE_HALF_Z_F };
    static f32 gr_add[] = { -mFI_UT_WORLDSIZE_X_F, mFI_UT_WORLDSIZE_Z_F };
    int* next_block_p = manager->player_pos.next_block;
    aSNMgr_scope_c* scope_p = &manager->scope;
    aSNMgr_scope_c* guest_scope_p = &manager->guest_scope;
    f32 center;
    int i;
    int j;

    for (i = 0; i < 2; i++) {
        center = next_block_p[i] * block_wh[i] + half_block_wh[i];

        for (j = 0; j < 2; j++) {
            scope_p->edge[i][j] = center + r_add[j];
            guest_scope_p->edge[i][j] = scope_p->edge[i][j] + gr_add[j];
        }
    }
}

static int aSNMgr_check_in(f32 chk_pos, f32* scope_pos_p) {
    int ret = FALSE;

    if (chk_pos >= scope_pos_p[0] && chk_pos < scope_pos_p[1]) {
        ret = TRUE;
    }

    return ret;
}

static int aSNMgr_check_in_scope(xyz_t chk_pos, aSNMgr_scope_c* scope_p) {
    int ret = FALSE;

    if (aSNMgr_check_in(chk_pos.x, scope_p->edge[0]) == TRUE &&
        aSNMgr_check_in(chk_pos.z, scope_p->edge[1]) == TRUE) {
        ret = TRUE;
    }

    return ret;
}

static void aSNMgr_set_in_block_npc_num(u8* in_block_num_p, mNpc_NpcList_c* list_p, u16 exist) {
    int bx;
    int bz;
    int block;
    int i;

    bzero(in_block_num_p, (BLOCK_Z_NUM - 2) * BLOCK_X_NUM);

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (((exist >> i) & 1) == 1) {
            if (mFI_Wpos2BlockNum(&bx, &bz, list_p->position) == TRUE) {
                block = mFI_GetBlockNum(bx, bz);
                in_block_num_p[block]++;
            }
        }

        list_p++;
    }
}

static int aSNMgr_check_move_npc_schedule(mNPS_schedule_c* sched_p, Animal_c* animal_p) {
    int ret = FALSE;

    if (sched_p->current_type == mNPS_SCHED_FIELD && animal_p != NULL && !animal_p->is_home) {
        ret = TRUE;
    }

    return ret;
}

static void aSNMgr_get_block_ut_num_set_npc(int* bx, int* bz, int* ux, int* uz, mNpc_NpcList_c* list_p) {
    if (mFI_Wpos2BlockNum(bx, bz, list_p->position) == TRUE) {
        mFI_Wpos2UtNum_inBlock(ux, uz, list_p->position);
    }
}

static int aSNMgr_set_appear_info_regular(SET_NPC_MANAGER_ACTOR* manager, int bx, int bz, int idx) {
    int player_bx = manager->player_pos.next_block[0];
    int player_bz = manager->player_pos.next_block[1];
    int ret = FALSE;

    if (bx == player_bx && bz == player_bz) {
        mNpcW_info_c* info_p = manager->npc_info.winfo_p[idx];

        if (info_p != NULL) {
            if (((manager->npc_info.joint_event >> idx) & 1) == 1) {
                info_p->appear_info.status = mNpcW_APPEAR_STATUS_REGULAR;
                ret = TRUE;
            } else {
                switch (info_p->status) {
                    case mNpcW_INFO_STATUS_WALKING:
                    case mNpcW_INFO_STATUS_STAY_IN_BLOCK:
                    case mNpcW_INFO_STATUS_ARRIVE:
                        info_p->appear_info.status = mNpcW_APPEAR_STATUS_REGULAR;
                        ret = TRUE;
                        break;
                }
            }
        } else {
            ret = TRUE;
        }
    }

    return ret;
}

static int aSNMgr_set_appear_info_guest(SET_NPC_MANAGER_ACTOR* manager, mNpcW_info_c* info_p, int bx, int bz) {
    int ret = FALSE;

    if (info_p != NULL) {
        int diff_bx;
        int diff_bz;
        int player_bx = manager->player_pos.next_block[0];
        int player_bz = manager->player_pos.next_block[1];

        switch (info_p->status) {
            case mNpcW_INFO_STATUS_STAY_IN_BLOCK:
            case mNpcW_INFO_STATUS_ARRIVE:
            case mNpcW_INFO_STATUS_4:
            default:
                break;
            case mNpcW_INFO_STATUS_WALKING: {
                diff_bx = bx - player_bx;
                diff_bz = bz - player_bz;

                if (diff_bx == 0) {
                    if (diff_bz == -1) {
                        info_p->appear_info.status = mNpcW_APPEAR_STATUS_GUEST;
                        info_p->appear_info.way = mNpcW_APPEAR_WAY_DOWN;
                        ret = TRUE;
                    } else if (diff_bz == 1) {
                        info_p->appear_info.status = mNpcW_APPEAR_STATUS_GUEST;
                        info_p->appear_info.way = mNpcW_APPEAR_WAY_UP;
                        ret = TRUE;
                    }
                } else if (diff_bz == 0) {
                    if (diff_bx == -1) {
                        info_p->appear_info.status = mNpcW_APPEAR_STATUS_GUEST;
                        info_p->appear_info.way = mNpcW_APPEAR_WAY_RIGHT;
                        ret = TRUE;
                    } else if (diff_bx == 1) {
                        info_p->appear_info.status = mNpcW_APPEAR_STATUS_GUEST;
                        info_p->appear_info.way = mNpcW_APPEAR_WAY_LEFT;
                        ret = TRUE;
                    }
                }
            }
        }
    }

    return ret;
}

static int aSNMgr_check_safe_ut(int bx, int bz, int ux, int uz, mActor_name_t item, mCoBG_Collision_u* col_p) {
    int ret = FALSE;

    if (col_p != NULL) {
        xyz_t pos;

        if (mNpc_CheckNpcSet_fgcol(item, col_p->data.unit_attribute)) {
            mFI_BkandUtNum2Wpos(&pos, bx, bz, ux, uz);

            if (!mCoBG_ExistHeightGap_KeepAndNow(pos)) {
                ret = TRUE;
            }
        }
    }

    return ret;
}

static void aSNMgr_get_safe_sp_event_structure_4x4(int* safe_ux, int* safe_uz, int ux, int uz) {
    int chk_ux = *safe_ux;
    int chk_uz = *safe_uz;



    if (ux >= 1 && ux <= (UT_X_NUM - 1) && (ux - 1 <= chk_ux) && (ux + 1 >= chk_ux) &&
        uz >= 1 && uz <= (UT_Z_NUM - 2) && (uz - 1 <= chk_uz) && (uz + 2 >= chk_uz)
    ) {
        if (ux >= chk_ux) {
            *safe_ux = ux - 1;
        } else {
            *safe_ux = ux + 1;
        }

        *safe_uz = uz + 4;
    }
}

static void aSNMgr_get_safe_sp_event_structure(int* safe_ux, int* safe_uz, mActor_name_t* fg_p) {
    static mActor_name_t sp_event_fg[] = { BROKER_TENT, DUMMY_BROKER_SHOP, DESIGNER_CAR, DUMMY_CAR };
    int i;
    int j;

    if (fg_p != NULL) {
        for (i = 0; i < UT_TOTAL_NUM; i++) {
            for (j = 0; j < ARRAY_COUNT(sp_event_fg); j++) {
                if (*fg_p == sp_event_fg[j]) {
                    aSNMgr_get_safe_sp_event_structure_4x4(safe_ux, safe_uz, i & 0xF, i >> 4);
                    i = UT_TOTAL_NUM;
                    break;
                }
            }

            fg_p++;
        }
    }
}

static int aSNMgr_get_safe_utnum_3x3(int* safe_ux, int* safe_uz, int bx, int bz) {
    mCoBG_Collision_u* col_p = mFI_GetBkNum2ColTop(bx, bz);
    mActor_name_t* fg_p = mFI_BkNumtoUtFGTop(bx, bz);
    static int ux_table[] = { 0, 1, -1, 0, 1, -1, 0, 1, -1 };
    static int uz_table[] = { 0, 0, 0, 1, 1, 1, -1, -1, -1 };
    int n_ux;
    int n_uz;
    int i;
    int ret = FALSE;
    int ut;
    int ux;
    int uz;

    if (col_p != NULL && fg_p != NULL) {
        ux = *safe_ux;
        uz = *safe_uz;

        for (i = 0; i < 9; i++) {
            n_ux = ux + ux_table[i];
            n_uz = uz + uz_table[i];

            if (n_ux >= 1 && n_ux < (UT_X_NUM - 1) && n_uz >= 1 && n_uz < (UT_Z_NUM - 1)) {
                ut = n_uz * UT_X_NUM + n_ux;

                if (aSNMgr_check_safe_ut(bx, bz, n_ux, n_uz, fg_p[ut], &col_p[ut]) == TRUE) {
                    *safe_ux = n_ux;
                    *safe_uz = n_uz;
                    ret = TRUE;
                    break;
                }
            }
        }
    }

    return ret;
}

static int aSNMgr_get_safe_utnum_in_block(int* safe_ux, int* safe_uz, int bx, int bz) {
    static u16 candidate_ut[16];
    u16* candidate_ut_p = candidate_ut;
    int candidate_num = 0;
    mCoBG_Collision_u* col_p = mFI_GetBkNum2ColTop(bx, bz);
    mActor_name_t* fg_p = mFI_BkNumtoUtFGTop(bx, bz);
    int idx;
    int ret = FALSE;
    int i;
    int j;

    if (col_p != NULL && fg_p != NULL) {
        bzero(candidate_ut, sizeof(candidate_ut));
        for (i = 0; i < UT_Z_NUM; i++) {
            for (j = 0; j < UT_X_NUM; j++) {
                if (j >= 1 && j < (UT_X_NUM - 1) && i >= 1 && i < (UT_Z_NUM - 1)) {
                    if (aSNMgr_check_safe_ut(bx, bz, j, i, *fg_p, col_p) == TRUE) {
                        (*candidate_ut_p) |= 1 << j;
                        candidate_num++;
                    }
                }

                fg_p++;
                col_p++;
            }

            candidate_ut_p++;
        }

        if (candidate_num > 0) {
            candidate_ut_p = candidate_ut;
            idx = RANDOM(candidate_num);

            for (i = 0; i < UT_Z_NUM; i++) {
                for (j = 0; j < UT_X_NUM; j++) {
                    if ((((*candidate_ut_p) >> j) & 1) == 1) {
                        if (idx <= 0) {
                            *safe_ux = j;
                            *safe_uz = i;
                            ret = TRUE;
                            i = UT_Z_NUM;
                            break;
                        }

                        idx--;
                    }
                }

                candidate_ut_p++;
            }
        }
    }

    return ret;
}

static int aSNMgr_get_safe_utnum_regular(int* safe_ux, int* safe_uz, int bx, int bz) {
    int ret;

    aSNMgr_get_safe_sp_event_structure(safe_ux, safe_uz, mFI_BkNumtoUtFGTop(bx, bz));
    ret = aSNMgr_get_safe_utnum_3x3(safe_ux, safe_uz, bx, bz);
    if (!ret) {
        ret = aSNMgr_get_safe_utnum_in_block(safe_ux, safe_uz, bx, bz);
    }

    return ret;
}

static int aSNMgr_get_safe_utnum_guest(int* safe_ux, int* safe_uz, int bx, int bz, int way) {
    static u8 l_gate_direct[] = { mRF_DIRECT_NORTH, mRF_DIRECT_SOUTH, mRF_DIRECT_WEST, mRF_DIRECT_EAST };
    int ret = FALSE;
    u8 type = mFI_BkNum2BlockType(bx, bz);
    int gate_count;
    mRF_gate_c* gate_p = mRF_BlockTypeDirect2GateData(&gate_count, type, l_gate_direct[way]);

    if (gate_p != NULL) {
        int idx = RANDOM(gate_count);

        *safe_ux = gate_p[idx].ut0 & 0xF;
        *safe_uz = gate_p[idx].ut0 >> 4;
        ret = TRUE;
    }

    return ret;
}

static int aSNMgr_get_safe_utnum(int* safe_ux, int* safe_uz, int bx, int bz, mNpcW_info_c* info_p) {
    int status;
    int way;

    way = mNpcW_APPEAR_WAY_UP;
    if (info_p != NULL) {
        status = info_p->appear_info.status;
        way = info_p->appear_info.way;
    } else {
        status = mNpcW_APPEAR_STATUS_REGULAR;
    }

    if (status == mNpcW_APPEAR_STATUS_GUEST) {
        return aSNMgr_get_safe_utnum_guest(safe_ux, safe_uz, bx, bz, way);
    } else {
        return aSNMgr_get_safe_utnum_regular(safe_ux, safe_uz, bx, bz);
    }
}

static int aSNMgr_set_event_info(aSNMgr_event_info_c* info_p) {
    int ret = FALSE;
    int type;
    int i;

    if (info_p->type == mEv_EVENT_NUM) {
        type = mEvMN_GetEventTypeMap();
        if (type != -1) {
            info_p->type = type;
            info_p->event_map_idx = mEvMN_GetMapIdx(type);
            if (info_p->event_map_idx != -1) {
                info_p->save_p = (aSNMgr_event_save_c*)mEv_get_save_area(type, 0xF);
                if (info_p->save_p == NULL) {
                    info_p->save_p = (aSNMgr_event_save_c*)mEv_reserve_save_area(type, 0xF);
                    for (i = 0; i < aSNMgr_EVENT_NORMAL_NPC_NUM; i++) {
                        info_p->save_p->animal_idx[i] = 0xFF;
                    }
                    mEvMN_GetNpcJointEv(info_p->save_p, type);
                } else {
                    mEvMN_SetNpcJointEv(info_p->save_p, type);
                }

                ret = TRUE;
            }
        }
    }

    return ret;
}

static void aSNMgr_set_npc_event(Animal_c* animal_p, mNpc_NpcList_c* list_p, aSNMgr_event_info_c* info_p, int idx) {
    int event_npc_idx = aSNMgr_get_event_npc_idx(info_p->save_p->animal_idx, info_p->joint_npc_max, idx);

    if (event_npc_idx != -1) {
        list_p->position.x = info_p->pos[event_npc_idx].x;
        list_p->position.y = info_p->pos[event_npc_idx].y;
        list_p->position.z = info_p->pos[event_npc_idx].z;
        animal_p->is_home = FALSE;
    }
}

static void aSNMgr_move_event_arrange(SET_NPC_MANAGER_ACTOR* manager, int bx, int bz) {
    Animal_c* animal_p = manager->npc_info.animal_p;
    mNpc_NpcList_c* list_p = manager->npc_info.list_p;
    aSNMgr_event_info_c* info_p = &manager->npc_info.event_info;
    u16 joint_event = manager->npc_info.joint_event;
    u8* idx_p = info_p->save_p->animal_idx;
    int idx;
    int ux;
    int uz;
    int set_ret;
    int i;

    for (i = 0; i < info_p->joint_npc_max; i++) {
        set_ret = mEvMN_GetEventSetUtInBlockMapIdx(&ux, &uz, info_p->event_map_idx, i);
        if (set_ret == TRUE) {
            idx = *idx_p;
            mFI_BkandUtNum2Wpos(&list_p[idx].position, bx, bz, ux, uz);
            info_p->pos[i].x = list_p[idx].position.x;
            info_p->pos[i].y = list_p[idx].position.y;
            info_p->pos[i].z = list_p[idx].position.z;
            animal_p[idx].is_home = FALSE;
            joint_event |= 1 << idx;
        }

        idx_p++;
    }

    manager->npc_info.joint_event = joint_event;
}

static void aSNMgr_move_event_set(SET_NPC_MANAGER_ACTOR* manager) {
    aSNMgr_event_info_c* info_p = &manager->npc_info.event_info;
    u32 kind;
    int bx;
    int bz;

    if (aSNMgr_set_event_info(info_p) == TRUE && info_p->event_map_idx != -1) {
        kind = mEvMN_GetEventBlockKind(info_p->event_map_idx);
        mFI_BlockKind2BkNum(&bx, &bz, kind);
        info_p->joint_npc_max = mEvMN_GetJointNpcMax(info_p->event_map_idx);
        aSNMgr_move_event_arrange(manager, bx, bz);
    }
}

static void aSNMgr_get_event_name(mActor_name_t* name_p, aSNMgr_event_info_c* info_p, int animal_idx) {
    int idx = -1;

    if (info_p->type != mEv_EVENT_NUM && info_p->type != mEv_EVENT_KAMAKURA) {
        if (info_p->event_map_idx != -1) {
            idx = aSNMgr_get_event_npc_idx(info_p->save_p->animal_idx, info_p->joint_npc_max, animal_idx);
        }

        mEvMN_GetEventNpcName(name_p, info_p->type, animal_idx, idx);
    }
}

static void aSNMgr_clear_make_npc(aSNMgr_make_c* make_p, int count) {
    while (count > 0) {
        make_p->name = EMPTY_NO;
        make_p->make_name = EMPTY_NO;
        make_p->bx = -1;
        make_p->bz = -1;
        make_p->ux = -1;
        make_p->uz = -1;
        make_p->idx = -1;
        
        make_p++;
        count--;
    }
}

static int aSNMgr_get_make_npc_idx(mActor_name_t name, int animal_idx, aSNMgr_make_c* make_p) {
    int ret = -1;
    int i;

    for (i = 0; i < aSNMgr_EVENT_NORMAL_NPC_NUM; i++) {
        if (make_p->name == name && make_p->idx == animal_idx) {
            ret = i;
            break;
        }

        make_p++;
    }

    return ret;
}

static int aSNMgr_set_make_npc(aSNMgr_make_c* make_p, mActor_name_t name, int bx, int bz, int ux, int uz, aSNMgr_event_info_c* info_p, int animal_idx) {
    aSNMgr_make_c* sel_make_p;
    int idx = aSNMgr_get_make_npc_idx(EMPTY_NO, -1, make_p);

    if (idx != -1) {
        sel_make_p = &make_p[idx];

        sel_make_p->name = name;
        sel_make_p->make_name = name;
        aSNMgr_get_event_name(&sel_make_p->make_name, info_p, animal_idx);
        sel_make_p->bx = bx;
        sel_make_p->bz = bz;
        sel_make_p->ux = ux;
        sel_make_p->uz = uz;
        sel_make_p->idx = animal_idx;
    }

    return idx;
}

static void aSNMgr_make_npc(SET_NPC_MANAGER_ACTOR* manager, GAME_PLAY* play) {
    aSNMgr_make_c* make_p = manager->npc_info.make;
    mNpc_NpcList_c* list_p = manager->npc_info.list_p;
    int idx;
    int make_ret;
    int i;

    if (CLIP(npc_clip) != NULL && CLIP(npc_clip)->setupActor_proc != NULL) {
        for (i = 0; i < aSNMgr_EVENT_NORMAL_NPC_NUM; i++) {
            switch (ITEM_NAME_GET_TYPE(make_p->name)) {
                case NAME_TYPE_SPNPC:
                case NAME_TYPE_NPC:
                    idx = make_p->idx;
                    if (idx != -1) {
                        make_ret = CLIP(npc_clip)->setupActor_proc(play, make_p->make_name, idx, idx, -1, make_p->bx, make_p->bz, make_p->ux, make_p->uz);
                        if (make_ret == TRUE) {
                            aSNMgr_clear_make_npc(make_p, 1);
                            list_p[idx].appear_flag = FALSE;
                        }
                    }
                    break;
                default:
                    if (make_p->name != EMPTY_NO) {
                        aSNMgr_clear_make_npc(make_p, 1);
                    }
                    break;
            }

            make_p++;
        }
    }
}

static void aSNMgr_set_to_block(u8* to_block_p, xyz_t pos, u8 goal_bx, u8 goal_bz) {
    int bx;
    int bz;
    int diff[2];
    int idx;

    if (mFI_Wpos2BlockNum(&bx, &bz, pos) == TRUE) {
        if (to_block_p[0] == 0 && to_block_p[1] == 0) {
            to_block_p[0] = bx;
            to_block_p[1] = bz;
        }

        if (bx == to_block_p[0] && bz == to_block_p[1]) {
            diff[0] = goal_bx - bx;
            diff[1] = goal_bz - bz;

            idx = 0;
            if (ABS(diff[0]) < ABS(diff[1])) {
                idx = 1;
            }

            if (diff[idx] > 0) {
                to_block_p[idx]++;
            } else {
                to_block_p[idx]--;
            }
        }
    }
}

static void aSNMgr_walk_to_next_block(xyz_t* pos_p, u8* to_block_p, u8* in_block_p, SET_NPC_MANAGER_ACTOR* manager) {
    aSNMgr_player_pos_c* player_pos_p = &manager->player_pos;
    int block[2];
    int prev_block[2];
    int idx;
    int unit[2];
    int i;
    int change_block = FALSE;

    if (mFI_Wpos2BkandUtNuminBlock(&block[0], &block[1], &unit[0], &unit[1], *pos_p) == TRUE) {
        for (i = 0; i < 2; i++) {
            unit[i] += (to_block_p[i] - block[i]);
            prev_block[i] = block[i];
            if (unit[i] < 0) {
                block[i]--;
                unit[i] = (UT_BASE_NUM - 2);
                change_block = TRUE;
            } else if (unit[i] >= UT_BASE_NUM) {
                block[i]++;
                unit[i] = 1;
                change_block = TRUE;
            }
        }

        if (block[0] != player_pos_p->now_block[0] || block[1] != player_pos_p->now_block[1]) {
            mFI_BkandUtNum2CenterWpos(pos_p, block[0], block[1], unit[0], unit[1]);

            if (change_block == TRUE) {
                idx = mFI_GetBlockNum(prev_block[0], prev_block[1]);
                in_block_p[idx]--;
                
                idx = mFI_GetBlockNum(block[0], block[1]);
                in_block_p[idx]++;
                if (in_block_p[idx] >= ANIMAL_NUM_MAX) {
                    in_block_p[idx] = 14;
                }
            }
        }
    }
}

static void aSNMgr_check_set_arrive(u8* status_p, xyz_t pos, u8 goal_bx, u8 goal_bz) {
    int bx;
    int bz;

    if (mFI_Wpos2BlockNum(&bx, &bz, pos) == TRUE && bx == goal_bx && bz == goal_bz) {
        *status_p = mNpcW_INFO_STATUS_ARRIVE;
    }
}

static void aSNMgr_go_back_home_sub(mNpc_walk_c* walk_p, mNpcW_info_c** winfo_pp, mNpcW_info_c** winfo_src_pp) {
    int anm_idx;
    int info_idx;

    anm_idx = mNpcW_ChangeNpcWalk(walk_p, *winfo_pp);
    *winfo_pp = NULL;
    if (anm_idx >= 0) {
        info_idx = mNpcW_GetNpcWalkInfoIdx(walk_p->info, mNpcW_MAX, &Save_Get(animals[anm_idx]).id);
        if (info_idx != -1) {
            winfo_src_pp[anm_idx] = &walk_p->info[info_idx];
        }
    }
}

static void aSNMgr_go_back_home(mNpc_walk_c* walk_p, mNpcW_info_c** winfo_pp, mNpcW_info_c** winfo_src_pp, u32* count_p) {
    if (*count_p > 108000) {
        if ((*winfo_pp)->goal_type == mNpcW_GOAL_MY_HOME) {
            aSNMgr_go_back_home_sub(walk_p, winfo_pp, winfo_src_pp);
        } else {
            (*winfo_pp)->status = mNpcW_INFO_STATUS_WALKING;
            (*winfo_pp)->goal_type = mNpcW_GOAL_MY_HOME;
            *count_p = 0;
            mNpcW_SetGoalBlock(*winfo_pp);
        }
    } else {
        (*count_p)++;
    }
}

static void aSNMgr_check_into_block_npc_sum(u8* status_p, u8* to_block_p, u8* in_block_p) {
    int block = mFI_GetBlockNum(to_block_p[0], to_block_p[1]);

    if (in_block_p[block] >= 3) {
        if (*status_p == mNpcW_INFO_STATUS_WALKING) {
            *status_p = mNpcW_INFO_STATUS_STAY_IN_BLOCK;
        }
    } else {
        if (*status_p == mNpcW_INFO_STATUS_STAY_IN_BLOCK) {
            *status_p = mNpcW_INFO_STATUS_WALKING;
        }
    }
}

static int aSNMgr_check_in_block_max(int bx, int bz, u8* in_block_p) {
    int ret = FALSE;
    int block = mFI_GetBlockNum(bx, bz);

    if (in_block_p[block] >= 3) {
        ret = TRUE;
    }

    return ret;
}

static void aSNMgr_walk_to_goal_npc(mNpc_NpcList_c* list_p, mNpcW_info_c* winfo_p, u8* to_block_p, u8* in_block_p, SET_NPC_MANAGER_ACTOR* manager, int walk_flag) {
    aSNMgr_set_to_block(to_block_p, list_p->position, winfo_p->goal_block_x, winfo_p->goal_block_z);

    if (walk_flag == TRUE) {
        aSNMgr_walk_to_next_block(&list_p->position, to_block_p, in_block_p, manager);
        aSNMgr_check_set_arrive(&winfo_p->status, list_p->position, winfo_p->goal_block_x, winfo_p->goal_block_z);
    }
}

static void aSNMgr_walk_npc(SET_NPC_MANAGER_ACTOR* manager, GAME* game) {
    mNPS_schedule_c* schedule_p = manager->npc_info.schedule_p;
    Animal_c* animal_p = manager->npc_info.animal_p;
    mNpc_NpcList_c* list_p = manager->npc_info.list_p;
    mNpcW_info_c** winfo_p = manager->npc_info.winfo_p;
    u32** count_p = manager->npc_info.count_p;
    int* timer_p = manager->npc_info.timer;
    int walk_flag = FALSE;
    int i;

    aSNMgr_set_in_block_npc_num((u8*)manager->npc_info.in_block_num, list_p, manager->npc_info.exist);
    if ((game->frame_counter % (7 * FRAMES_PER_SECOND)) == 0) {
        walk_flag = TRUE;
    }

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (aSNMgr_chk_exist_and_appear_and_event(manager, mNpcW_APPEAR_STATUS_REGULAR, i) == TRUE &&
            aSNMgr_check_move_npc_schedule(schedule_p, animal_p) == TRUE &&
            *winfo_p != NULL
        ) {
            if ((*winfo_p)->status == mNpcW_INFO_STATUS_WALKING || (*winfo_p)->status == mNpcW_INFO_STATUS_STAY_IN_BLOCK) {
                aSNMgr_check_into_block_npc_sum(&(*winfo_p)->status, (u8*)&manager->npc_info.to_block[i], (u8*)manager->npc_info.in_block_num);
            }

            switch ((*winfo_p)->status) {
                case mNpcW_INFO_STATUS_NONE:
                    break;
                case mNpcW_INFO_STATUS_WALKING:
                    if (*timer_p == 0) {
                        aSNMgr_walk_to_goal_npc(list_p, *winfo_p, (u8*)&manager->npc_info.to_block[i], (u8*)manager->npc_info.in_block_num, manager, walk_flag);
                    } else {
                        (*timer_p)--;
                        if (*timer_p < 0) {
                            *timer_p = 0;
                        }
                    }
                    break;
                case mNpcW_INFO_STATUS_STAY_IN_BLOCK:
                    break;
                case mNpcW_INFO_STATUS_ARRIVE:
                    aSNMgr_go_back_home(manager->npc_info.walk_p, winfo_p, manager->npc_info.winfo_p, *count_p);
                    break;
                case mNpcW_INFO_STATUS_4:
                    break;
            }
        }

        schedule_p++;
        animal_p++;
        list_p++;
        winfo_p++;
        count_p++;
        timer_p++;
    }
}

static int aSNMgr_set_go_home_status_sub(SET_NPC_MANAGER_ACTOR* manager, int anm_idx, int bx, int bz, int status) {
    int ux;
    int uz;
    xyz_t pos;
    int ret = FALSE;


    if (aSNMgr_get_safe_utnum_in_block(&ux, &uz, bx, bz) == TRUE) {
        mNpc_NpcList_c* list_p = &manager->npc_info.list_p[anm_idx];
        mNpcW_info_c* winfo_p = manager->npc_info.winfo_p[anm_idx];

        mFI_BkandUtNum2Wpos(&pos, bx, bz, ux, uz);
        list_p->position.x = pos.x;
        list_p->position.z = pos.z;

        if (winfo_p != NULL) {
            u32* count_p = manager->npc_info.count_p[anm_idx];

            winfo_p->status = status;
            winfo_p->goal_type = mNpcW_GOAL_MY_HOME;
            winfo_p->goal_block_x = bx;
            winfo_p->goal_block_z = bz;
            *count_p = 108001;
        }

        ret = TRUE;
    }

    return ret;
}

static int aSNMgr_set_go_home_status(SET_NPC_MANAGER_ACTOR* manager, int anm_idx, int bx, int bz, int player_bx, int player_bz) {
    // clang-format off
    static int add_bx[] = { 0,  0, 0, -1, 1 };
    static int add_bz[] = { 0, -1, 1,  0, 0 };
    static u8 walk_status[] = {
        mNpcW_INFO_STATUS_ARRIVE,
        mNpcW_INFO_STATUS_WALKING,
        mNpcW_INFO_STATUS_WALKING,
        mNpcW_INFO_STATUS_WALKING,
        mNpcW_INFO_STATUS_WALKING,
    };
    // clang-format on
    Animal_c* animal_p = &manager->npc_info.animal_p[anm_idx];
    int home_bx = animal_p->home_info.block_x;
    int home_bz = animal_p->home_info.block_z;
    int chk_bx;
    int chk_bz;
    int i;
    int ret = FALSE;

    for (i = 0; i < 5; i++) {
        chk_bx = home_bx + add_bx[i];
        chk_bz = home_bz + add_bz[i];
        
        if (mFI_BlockCheck(chk_bx, chk_bz) == TRUE) {
            if ((chk_bx != bx || chk_bz != bz) && (chk_bx != player_bx || chk_bz != player_bz)) {
                if (aSNMgr_set_go_home_status_sub(manager, anm_idx, chk_bx, chk_bz, walk_status[i]) == TRUE) {
                    ret = TRUE;
                    break;
                }
            }
        }
    }

    return ret;
}

static void aSNMgr_set_stay_home_status(SET_NPC_MANAGER_ACTOR* manager, int anm_idx) {
    mNpc_NpcList_c* list_p = &manager->npc_info.list_p[anm_idx];
    mNpcW_info_c* winfo_p = manager->npc_info.winfo_p[anm_idx];
    Animal_c* animal_p = &manager->npc_info.animal_p[anm_idx];
    u32* count_p;

    list_p->position = list_p->house_position;
    animal_p->is_home = TRUE;
    if (winfo_p != NULL) {
        mNpcW_ClearNpcWalkInfo(winfo_p, 1);
        count_p = manager->npc_info.count_p[anm_idx];
        *count_p = 108001;
    }
}

static void aSNMgr_force_go_home_event_start(SET_NPC_MANAGER_ACTOR* manager) {
    Animal_c* animal_p = manager->npc_info.animal_p;
    mNpc_NpcList_c* list_p = manager->npc_info.list_p;
    int player_bx = manager->player_pos.now_block[0];
    int player_bz = manager->player_pos.now_block[1];
    int now_bx;
    int now_bz;
    int goal_bx = 0;
    int goal_bz = 0;
    int event_type;
    int event_map_idx;
    u32 block_kind;
    int i;

    event_type = mEvMN_GetEventTypeMap();
    if (event_type != -1) {
        event_map_idx = mEvMN_GetMapIdx(event_type);
        if (event_map_idx != -1) {
            block_kind = mEvMN_GetEventBlockKind(event_map_idx);
            mFI_BlockKind2BkNum(&goal_bx, &goal_bz, block_kind);
        }
    }

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (((manager->npc_info.exist >> i) & 1) == 1 && ((manager->npc_info.joint_event >> i) & 1) == 0) {
            if (mFI_Wpos2BlockNum(&now_bx, &now_bz, list_p->position) == TRUE && !animal_p->is_home) {
                if (now_bx == goal_bx && now_bz == goal_bz) {
                    if (animal_p->home_info.block_x != now_bx || animal_p->home_info.block_z != now_bz) {
                        if (!aSNMgr_set_go_home_status(manager, i, goal_bx, goal_bz, player_bx, player_bz)) {
                            aSNMgr_set_stay_home_status(manager, i);
                        }
                    }
                }
            }
        }

        animal_p++;
        list_p++;
    }
}

static void aSNMgr_force_go_home(SET_NPC_MANAGER_ACTOR* manager) {
    mNPS_schedule_c* schedule_p = manager->npc_info.schedule_p;
    Animal_c* animal_p = manager->npc_info.animal_p;
    mNpc_NpcList_c* list_p = manager->npc_info.list_p;
    mNpcW_info_c** winfo_p = manager->npc_info.winfo_p;
    int* timer_p = manager->npc_info.timer;
    int player_bx = manager->player_pos.now_block[0];
    int player_bz = manager->player_pos.now_block[1];
    int bx;
    int bz;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (aSNMgr_chk_exist_and_appear_and_event(manager, mNpcW_APPEAR_STATUS_REGULAR, i) == TRUE) {
            if (mFI_Wpos2BlockNum(&bx, &bz, list_p->position) == TRUE) {
                if (!aSNMgr_check_move_npc_schedule(schedule_p, animal_p) && *timer_p == 0) {
                    if (animal_p->home_info.block_x != bx || animal_p->home_info.block_z != bz) {
                        aSNMgr_set_go_home_status(manager, i, -1, -1, player_bx, player_bz);
                    } else if ((bx != player_bx || bz != player_bz) && animal_p->is_home == TRUE && *winfo_p != NULL) {
                        aSNMgr_go_back_home_sub(manager->npc_info.walk_p, winfo_p, manager->npc_info.winfo_p);
                    }
                }
            }
        }

        schedule_p++;
        animal_p++;
        list_p++;
        winfo_p++;
        timer_p++;
    }
}

static void aSNMgr_reset_npc(SET_NPC_MANAGER_ACTOR* manager) {
    mNpc_NpcList_c* list_p = manager->npc_info.list_p;
    aSNMgr_make_c* make_p = manager->npc_info.make;
    u16 appear;
    int* timer_p = manager->npc_info.timer;
    int i;

    appear = manager->npc_info.appear;
    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        if (aSNMgr_chk_exist_and_appear(manager, mNpcW_APPEAR_STATUS_GUEST, i) == TRUE) {
            if (aSNMgr_get_make_npc_idx(list_p->name, i, make_p) == -1) {
                appear &= ~(1 << i);
                *timer_p = 10800; // is this supposed to be 108001?
            }
        }

        list_p++;
        timer_p++;
    }

    manager->npc_info.appear = appear;
}

static void aSNMgr_set_npc_regular(SET_NPC_MANAGER_ACTOR* manager) {
    aSNMgr_npc_info_c* npc_info_p = &manager->npc_info;
    Animal_c* animal_p = npc_info_p->animal_p;
    mNpc_NpcList_c* list_p = npc_info_p->list_p;
    mNpcW_info_c** winfo_p = npc_info_p->winfo_p;
    aSNMgr_event_info_c* info_p = &npc_info_p->event_info;
    u16 joint_event = npc_info_p->joint_event;
    int bx;
    int bz;
    int ux;
    int uz;
    int i;

    for (i = 0; i < ANIMAL_NUM_MAX; i++) {
        int set = TRUE;

        if (aSNMgr_chk_exist_and_appear(manager, mNpcW_APPEAR_STATUS_REGULAR, i) == TRUE) {
            if (aSNMgr_check_in_scope(list_p->position, &manager->scope) == TRUE) {
                if (((joint_event >> i) & 1) == 1) {
                    if (info_p->type != mEv_EVENT_KAMAKURA) {
                        aSNMgr_set_npc_event(animal_p, list_p, info_p, i);
                    } else {
                        set = FALSE;
                    }
                }

                if (set == TRUE) {
                    int make_flag;

                    aSNMgr_get_block_ut_num_set_npc(&bx, &bz, &ux, &uz, list_p);
                    make_flag = aSNMgr_set_appear_info_regular(manager, bx, bz, i);
                    if (make_flag == TRUE) {
                        if (((joint_event >> i) & 1) == 0) {
                            make_flag = aSNMgr_get_safe_utnum(&ux, &uz, bx, bz, *winfo_p);
                        }

                        if (make_flag == TRUE &&
                            aSNMgr_set_make_npc(manager->npc_info.make, animal_p->id.npc_id, bx, bz, ux, uz, info_p, i) != -1) {
                            manager->npc_info.appear |= 1 << i;
                        }
                    }
                }
            }
        }

        animal_p++;
        list_p++;
        winfo_p++;
    }

    switch (mFI_GetPlayerWade()) {
        case mFI_WADE_NONE:
            aSNMgr_setup_set_proc(manager, aSNMgr_SET_MODE_GUEST);
            break;
        default:
            aSNMgr_setup_set_proc(manager, aSNMgr_SET_MODE_NONE);
            break;
    }
}

static void aSNMgr_set_npc_guest(SET_NPC_MANAGER_ACTOR* manager) {
    aSNMgr_npc_info_c* npc_info_p = &manager->npc_info;
    Animal_c* animal_p = npc_info_p->animal_p;
    mNpc_NpcList_c* list_p = npc_info_p->list_p;
    mNpcW_info_c** winfo_p = npc_info_p->winfo_p;
    aSNMgr_scope_c* scope_p = &manager->guest_scope;
    aSNMgr_event_info_c* info_p = &npc_info_p->event_info;
    int bx;
    int bz;
    int ux;
    int uz;
    int i;

    if (!aSNMgr_chk_arbeit_and_demo_and_halloween() &&
        !aSNMgr_check_in_block_max(manager->player_pos.now_block[0], manager->player_pos.now_block[1], (u8*)manager->npc_info.in_block_num)) {
        for (i = 0; i < ANIMAL_NUM_MAX; i++) {
            if (aSNMgr_chk_exist_and_appear_and_event(manager, mNpcW_APPEAR_STATUS_REGULAR, i) == TRUE) {
                if (aSNMgr_check_in_scope(list_p->position, scope_p) == TRUE) {
                    aSNMgr_get_block_ut_num_set_npc(&bx, &bz, &ux, &uz, list_p);
                    if (aSNMgr_set_appear_info_guest(manager, *winfo_p, bx, bz) == TRUE &&
                        aSNMgr_get_safe_utnum(&ux, &uz, bx, bz, *winfo_p) == TRUE &&
                        aSNMgr_set_make_npc(manager->npc_info.make, animal_p->id.npc_id, bx, bz, ux, uz, info_p, i) != -1) {
                        manager->npc_info.appear |= 1 << i;
                    }
                }
            }

            animal_p++;
            list_p++;
            winfo_p++;
        }
    }
}

static void aSNMgr_setup_set_proc(SET_NPC_MANAGER_ACTOR* manager, int set_mode) {
    // clang-format off
    static aSNMgr_SET_PROC set_proc[] = {
        (aSNMgr_SET_PROC)&none_proc1,
        &aSNMgr_set_npc_regular,
        &aSNMgr_set_npc_guest,
    };
    // clang-format on

    if (set_mode < 0 || set_mode >= aSNMgr_SET_MODE_NUM) {
        set_mode = aSNMgr_SET_MODE_REGULAR;
    }

    manager->set_mode = set_mode;
    manager->set_proc = set_proc[set_mode];
}

static void aSNMgr_actor_move(ACTOR* actorx, GAME* game) {
    SET_NPC_MANAGER_ACTOR* manager = (SET_NPC_MANAGER_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    aSNMgr_get_player_pos(&manager->player_pos.pos, game);
    switch (mFI_GetPlayerWade()) {
        case mFI_WADE_START:
            aSNMgr_clear_make_npc(manager->npc_info.make, aSNMgr_EVENT_NORMAL_NPC_NUM);
            aSNMgr_renewal_player_next_block(manager);
            aSNMgr_renewal_set_scope(manager);
            aSNMgr_setup_set_proc(manager, aSNMgr_SET_MODE_REGULAR);
            break;
        case mFI_WADE_END:
            aSNMgr_renewal_player_now_block(manager);
            aSNMgr_setup_set_proc(manager, aSNMgr_SET_MODE_GUEST);
            break;
        case mFI_WADE_NONE:
            if (play->fb_fade_type == FADE_TYPE_NONE) {
                aSNMgr_clear_make_npc(manager->npc_info.make, aSNMgr_EVENT_NORMAL_NPC_NUM);
                if (!aSNMgr_chk_arbeit_and_demo_and_halloween()) {
                    aSNMgr_force_go_home(manager);
                    aSNMgr_walk_npc(manager, game);
                }
            }
            break;
    }

    aSNMgr_move_event_set(manager);
    (*manager->set_proc)(manager);
    aSNMgr_make_npc(manager, play);
    aSNMgr_reset_npc(manager);
}
