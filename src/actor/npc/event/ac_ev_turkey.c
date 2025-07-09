#include "ac_ev_turkey.h"

#include "m_common_data.h"
#include "m_msg.h"
#include "m_player_lib.h"
#include "libultra/libultra.h"

#define aETKY_PRESENT_NUM 12
#define aETKY_ALL_BITS ((1 << aETKY_PRESENT_NUM) - 1)

enum {
    aETKY_ACTION_WAIT,
    aETKY_ACTION_KYORO,

    aETKY_ACTION_NUM
};

enum {
    aETKY_TALK_WAIT_END,
    aETKY_TALK_EXPLAIN_ENV0,
    aETKY_TALK_EXPLAIN_ENV1,
    aETKY_TALK_EXPLAIN_ENV2,
    aETKY_TALK_EXPLAIN_ENV3,
    aETKY_TALK_FIND_REAC,
    aETKY_TALK_GIVE_ME_FORK,
    aETKY_TALK_GIVE_YOU_PRESENT,

    aETKY_TALK_NUM
};

static void aETKY_actor_ct(ACTOR* actorx, GAME* game);
static void aETKY_actor_dt(ACTOR* actorx, GAME* game);
static void aETKY_actor_init(ACTOR* actorx, GAME* game);
static void aETKY_actor_save(ACTOR* actorx, GAME* game);
static void aETKY_actor_move(ACTOR* actorx, GAME* game);
static void aETKY_actor_draw(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Ev_Turkey_Profile = {
    // clang-format off
    mAc_PROFILE_EV_TURKEY,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_TURKEY,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EV_TURKEY_ACTOR),
    aETKY_actor_ct,
    aETKY_actor_dt,
    aETKY_actor_init,
    mActor_NONE_PROC1,
    aETKY_actor_save,
    // clang-format on
};

static const mActor_name_t aETKY_present_table[] = {
    // clang-format off
    FTR_START(FTR_IKU_TURKEY_LAMP),
    FTR_START(FTR_IKU_TURKEY_TABLE),
    FTR_START(FTR_IKU_TURKEY_TV),
    FTR_START(FTR_IKU_TURKEY_BED),
    FTR_START(FTR_YAZ_TURKEY_CHAIR),
    FTR_START(FTR_YOS_TURKEY_WATCH),
    FTR_START(FTR_HOS_TURKEY_SOFA),
    FTR_START(FTR_YAZ_TURKEY_CLOSET),
    FTR_START(FTR_YAZ_TURKEY_CHEST),
    FTR_START(FTR_YOS_TURKEY_MIRROR),
    ITM_CARPET66,
    ITM_WALL66,
    // clang-format on
};

static int aETKY_DecidePresent(u16* given_bitfield) {
    int dont_have_count = 0;
    int check_count = 0;
    int selected;
    int i;
    
    if ((*given_bitfield & aETKY_ALL_BITS) == aETKY_ALL_BITS) {
        *given_bitfield = 0;
    }

    for (i = 0; i < aETKY_PRESENT_NUM; i++) {
        if (((*given_bitfield >> i) & 1) == 0) {
            dont_have_count++;
        }
    }

    selected = RANDOM(dont_have_count);
    for (i = 0; i < aETKY_PRESENT_NUM; i++) {
        if (((*given_bitfield >> i) & 1) == 0) {
            if (check_count == selected) {
                return i;
            }

            check_count++;
        }
    }

    return 0;
}

static void aETKY_ReportPresent(u16* given_bitfield, int idx) {
    if (given_bitfield != NULL) {
        *given_bitfield |= (u16)(1 << idx);
    }
}

static void aETKY_ActionWait(EV_TURKEY_ACTOR* turkey) {
    if (turkey->npc_class.draw.main_animation_state == cKF_STATE_CONTINUE) {
        if (turkey->npc_class.draw.loop_flag == FALSE) {
            turkey->npc_class.action.step = aNPC_ACTION_END_STEP;
        } else {
            turkey->npc_class.draw.loop_flag--;
        }
    }
}

static void aETKY_ActionKyoro(EV_TURKEY_ACTOR* turkey) {
    if (turkey->npc_class.draw.main_animation_state == cKF_STATE_CONTINUE) {
        if (turkey->npc_class.draw.loop_flag == FALSE) {
            turkey->npc_class.action.step = aNPC_ACTION_END_STEP;
        } else {
            turkey->npc_class.draw.loop_flag--;
        }
    }
}

static void aETKY_setupAction(EV_TURKEY_ACTOR* turkey, int action) {
    static aETKY_ACT_PROC process[] = { aETKY_ActionWait, aETKY_ActionKyoro };
    static int animeSeqNo[] = { aNPC_ANIM_WAIT1, aNPC_ANIM_TKYKYORO1 };

    turkey->npc_class.action.step = 0;
    turkey->action = action;
    turkey->act_proc = process[action];

    if (action == aETKY_ACTION_WAIT) {
        turkey->npc_class.draw.loop_flag = RANDOM(2);
    } else {
        turkey->npc_class.draw.loop_flag = RANDOM(2);
    }

    NPC_CLIP->animation_init_proc((ACTOR*)turkey, animeSeqNo[action], FALSE);
}

static void aETKY_act_chg_data_proc(NPC_ACTOR* nactorx, GAME_PLAY* play) {
    nactorx->action.act_obj = aNPC_ACT_OBJ_PLAYER;
}

static void aETKY_act_init_proc(NPC_ACTOR* nactorx, GAME_PLAY* play) {
    EV_TURKEY_ACTOR* turkey = (EV_TURKEY_ACTOR*)nactorx;

    if (turkey->_9B1 == 1) {
        aETKY_setupAction(turkey, aETKY_ACTION_WAIT);
    } else {
        aETKY_setupAction(turkey, aETKY_ACTION_KYORO);
    }
}

static void aETKY_act_main_proc(NPC_ACTOR* nactorx, GAME_PLAY* play) {
    EV_TURKEY_ACTOR* turkey = (EV_TURKEY_ACTOR*)nactorx;

    (*turkey->act_proc)(turkey);
}

static void aETKY_act_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int proc_type) {
    static aNPC_SUB_PROC act_proc[] = {
        // clang-format off
        aETKY_act_init_proc,
        aETKY_act_chg_data_proc,
        aETKY_act_main_proc,
        // clang-format on
    };

    (*act_proc[proc_type])(nactorx, play);
}

static void aETKY_set_request_act(NPC_ACTOR* nactorx) {
    nactorx->request.act_priority = 4;
    nactorx->request.act_idx = aNPC_ACT_SPECIAL;
    nactorx->request.act_type = aNPC_ACT_TYPE_SEARCH;
}

static void aETKY_think_init_proc(NPC_ACTOR* nactorx, GAME_PLAY* play) {
    nactorx->think.interrupt_flags = 0;
    nactorx->action.act_proc = aETKY_act_proc;
    aETKY_set_request_act(nactorx);
}

static void aETKY_think_main_proc(NPC_ACTOR* nactorx, GAME_PLAY* play) {
    EV_TURKEY_ACTOR* turkey = (EV_TURKEY_ACTOR*)nactorx;

    if (nactorx->action.step == aNPC_ACTION_END_STEP) {
        switch (nactorx->action.idx) {
            case aNPC_ACT_SPECIAL:
                if (turkey->_9BC != -1) {
                    aETKY_setupAction(turkey, turkey->_9BC);
                    turkey->_9BC = -1;
                } else if (turkey->_9B1 == 1) {
                    aETKY_setupAction(turkey, aETKY_ACTION_WAIT);
                } else {
                    aETKY_setupAction(turkey, (turkey->action + 1) & 1);
                }

                nactorx->condition_info.demo_flg = aNPC_COND_DEMO_SKIP_HEAD_LOOKAT;
                nactorx->collision.check_kind = aNPC_BG_CHECK_TYPE_ONLY_GROUND;

                if (turkey->_9C0.x != nactorx->actor_class.world.position.x) {
                    add_calc(&turkey->_9C0.x, nactorx->actor_class.world.position.x, 1.0f - sqrtf(0.7f), 0.25f, 0.05f);
                } else if (turkey->_9C0.y != nactorx->actor_class.world.position.y) {
                    add_calc(&turkey->_9C0.y, nactorx->actor_class.world.position.y, 1.0f - sqrtf(0.7f), 0.25f, 0.05f);
                } else if (turkey->_9C0.z != nactorx->actor_class.world.position.z) {
                    add_calc(&turkey->_9C0.z, nactorx->actor_class.world.position.z, 1.0f - sqrtf(0.7f), 0.25f, 0.05f);
                }

                break;
            case aNPC_ACT_TALK:
                nactorx->condition_info.demo_flg = aNPC_COND_DEMO_SKIP_HEAD_LOOKAT;
                nactorx->movement.mv_angl = 0;
                aETKY_set_request_act(nactorx);
                break;
        }
    }
}

static void aETKY_think_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int proc_type) {
    static aNPC_SUB_PROC think_proc[] = { aETKY_think_init_proc, aETKY_think_main_proc };

    (*think_proc[proc_type & 1])(nactorx, play);
}

static void aETKY_schedule_init_proc(NPC_ACTOR* nactorx, GAME_PLAY* play) {
    EV_TURKEY_ACTOR* turkey = (EV_TURKEY_ACTOR*)nactorx;
    
    nactorx->think.think_proc = aETKY_think_proc;
    nactorx->condition_info.hide_request = FALSE;
    nactorx->palActorIgnoreTimer = -1;
    nactorx->talk_info.default_animation = aNPC_ANIM_WAIT1;
    turkey->_9BC = -1;
    NPC_CLIP->think_proc(nactorx, play, aNPC_THINK_SPECIAL, aNPC_THINK_TYPE_INIT);
}

static void aETKY_schedule_main_proc(NPC_ACTOR* nactorx, GAME_PLAY* play) {
    if (NPC_CLIP->think_proc(nactorx, play, -1, aNPC_THINK_TYPE_CHK_INTERRUPT) == FALSE) {
        NPC_CLIP->think_proc(nactorx, play, -1, aNPC_THINK_TYPE_MAIN);
    }
}

static void aETKY_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int proc_type) {
    static aNPC_SUB_PROC sche_proc[] = { aETKY_schedule_init_proc, aETKY_schedule_main_proc };

    (*sche_proc[proc_type & 1])(nactorx, play);
}

static void aETKY_SetupSaveData(ACTOR* actorx) {
    EV_TURKEY_ACTOR* turkey = (EV_TURKEY_ACTOR*)actorx;
    aEv_turkey_save_c* save_p = (aEv_turkey_save_c*)mEv_get_save_area(mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN, 0);

    if (save_p == NULL) {
        save_p = (aEv_turkey_save_c*)mEv_reserve_save_area(mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN, 0);
        bzero(save_p, sizeof(aEv_turkey_save_c));
        mPr_ClearPersonalID(&save_p->pid);
        turkey->ev_save_p = save_p;
    } else {
        turkey->ev_save_p = save_p;
    }
}

static void aETKY_SetupCommonData(ACTOR* actorx) {
    EV_TURKEY_ACTOR* turkey = (EV_TURKEY_ACTOR*)actorx;
    aEv_turkey_common_c* common_p = (aEv_turkey_common_c*)mEv_get_common_area(mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN, 0);

    if (common_p == NULL) {
        common_p = (aEv_turkey_common_c*)mEv_reserve_common_area(mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN, 0);
        turkey->ev_common_p = common_p;
        common_p->_01 = 0;
        common_p->_02 = 0;
        common_p->_00 = 0;
    } else {
        turkey->ev_common_p = common_p;
    }
}

static void aETKY_TalkRequest(ACTOR* actorx, GAME* game);
static int aETKY_TalkInit(ACTOR* actorx, GAME* game);
static int aETKY_TalkEndCheck(ACTOR* actorx, GAME* game);

static void aETKY_SetupTalkStat(EV_TURKEY_ACTOR* turkey, GAME_PLAY* play, int talk_action);

static void aETKY_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        // clang-format off
        aETKY_actor_move,
        aETKY_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        aETKY_TalkRequest,
        aETKY_TalkInit,
        aETKY_TalkEndCheck,
        0,
        // clang-format on
    };

    EV_TURKEY_ACTOR* turkey = (EV_TURKEY_ACTOR*)actorx;

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        turkey->npc_class.schedule.schedule_proc = aETKY_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        turkey->talk_setup_proc = aETKY_SetupTalkStat;
        aETKY_SetupSaveData(actorx);
        aETKY_SetupCommonData(actorx);
        turkey->present_idx = aETKY_DecidePresent(&turkey->ev_save_p->given_present_bitfield);
        turkey->npc_class.actor_class.status_data.weight = MASSTYPE_HEAVY;
    }

    turkey->_9C0 = turkey->npc_class.actor_class.world.position;
}

static void aETKY_Give_Me_Fork_Init(EV_TURKEY_ACTOR* turkey, GAME_PLAY* play) {
    // nothing
}

static void aETKY_Give_You_Present_Init(EV_TURKEY_ACTOR* turkey, GAME_PLAY* play) {
    // nothing
}

typedef void (*aETKY_TALK_INIT_PROC)(EV_TURKEY_ACTOR* turkey, GAME_PLAY* play);

static void aETKY_init_proc(EV_TURKEY_ACTOR* turkey, GAME_PLAY* play, int talk_act) {
    static aETKY_TALK_INIT_PROC init_proc[] = {
        // clang-format off
        (aETKY_TALK_INIT_PROC)none_proc1,
        (aETKY_TALK_INIT_PROC)none_proc1,
        (aETKY_TALK_INIT_PROC)none_proc1,
        (aETKY_TALK_INIT_PROC)none_proc1,
        (aETKY_TALK_INIT_PROC)none_proc1,
        (aETKY_TALK_INIT_PROC)none_proc1,
        aETKY_Give_Me_Fork_Init,
        aETKY_Give_You_Present_Init,
        // clang-format on
    };

    (*init_proc[talk_act])(turkey, play);
}

static void aETKY_DeleteKnifeInPlayerBag(void) {
    int idx = mPr_GetPossessionItemIdxWithCond(Now_Private, ITM_KNIFE_AND_FORK, mPr_ITEM_COND_NORMAL);

    if (idx != -1) {
        mPr_SetPossessionItem(Now_Private, idx, EMPTY_NO, mPr_ITEM_COND_NORMAL);
    }
}

static void aETKY_SetKnifeForkSequence(EV_TURKEY_ACTOR* turkey, GAME_PLAY* play) {
    int item_idx = mPr_GetPossessionItemIdxWithCond(Now_Private, ITM_KNIFE_AND_FORK, mPr_ITEM_COND_NORMAL);
    u8 present_idx;
    mActor_name_t present;
    u8 item_name[mIN_ITEM_NAME_LEN];

    if (item_idx == -1) {
        mMsg_SET_CONTINUE_MSG_NUM(0x3C02 + RANDOM(3));
        aETKY_SetupTalkStat(turkey, play, aETKY_TALK_WAIT_END);
    } else {
        present_idx = turkey->present_idx;
        present = aETKY_present_table[present_idx];
        mIN_copy_name_str(item_name, present);
        mMsg_SET_CONTINUE_MSG_NUM(0x3C11 + present_idx);
        mMsg_SET_ITEM_STR_ART(mMsg_ITEM_STR0, item_name, mIN_ITEM_NAME_LEN, present);
        aETKY_SetupTalkStat(turkey, play, aETKY_TALK_GIVE_ME_FORK);
    }
}

static void aETKY_Explain_Env0123(EV_TURKEY_ACTOR* turkey, GAME_PLAY* play) {
    int talk_action = turkey->talk_action;
    int msg_no = mMsg_GET_MSG_NUM();

    if (mMsg_CHECK_MAINNORMALCONTINUE() && msg_no == 0x3BFD + talk_action) {
        if (turkey->talk_action == aETKY_TALK_EXPLAIN_ENV3) {
            aETKY_SetKnifeForkSequence(turkey, play);
        } else {
            mMsg_SET_CONTINUE_MSG_NUM(0x3BFD + talk_action + 1);
            aETKY_SetupTalkStat(turkey, play, turkey->talk_action + 1);
        }
    }
}

static void aETKY_Find_Reac(EV_TURKEY_ACTOR* turkey, GAME_PLAY* play) {
    if (mMsg_CHECK_MAINNORMALCONTINUE()) {
        aETKY_SetKnifeForkSequence(turkey, play);
    }
}

static void aETKY_Give_Me_Fork(EV_TURKEY_ACTOR* turkey, GAME_PLAY* play) {
    int order = mDemo_Get_OrderValue(mDemo_ORDER_NPC0, 9);
    int msg_no = mMsg_GET_MSG_NUM(); // @unused

    switch (order) {
        case 1:
            // Wait for give_type1 to succeed, and then move over to waiting for give to finish
            if (mPlib_request_main_give_type1((GAME*)play, ITM_KNIFE_AND_FORK, aHOI_REQUEST_PUTAWAY, FALSE, FALSE)) {
                mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 9, 2);
                mMsg_SET_LOCKCONTINUE();
                mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 1, 3);
                aETKY_DeleteKnifeInPlayerBag();
            }
            break;
        case 2:
            // Wait for hand over item sequence to finish, then clear order
            if (CLIP(handOverItem_clip)->master_actor == NULL) {
                mMsg_UNSET_LOCKCONTINUE();
                mDemo_Set_OrderValue(mDemo_ORDER_NPC0, 9, 0);
                aETKY_SetupTalkStat(turkey, play, aETKY_TALK_GIVE_YOU_PRESENT);
            }
            break;
    }
}

static void aETKY_Give_You_Present(EV_TURKEY_ACTOR* turkey, GAME_PLAY* play) {
    int order = mDemo_Get_OrderValue(mDemo_ORDER_NPC0, 1);

    if (order == 2) {
        mActor_name_t present = aETKY_present_table[turkey->present_idx];

        aNPC_DEMO_GIVE_ITEM(present, aHOI_REQUEST_PUTAWAY, FALSE);
        mPr_SetFreePossessionItem(Now_Private, present, mPr_ITEM_COND_NORMAL);
        aETKY_ReportPresent(&turkey->ev_save_p->given_present_bitfield, turkey->present_idx);
        aETKY_SetupTalkStat(turkey, play, aETKY_TALK_WAIT_END);
    }
}

static void aETKY_SetupTalkStat(EV_TURKEY_ACTOR* turkey, GAME_PLAY* play, int talk_act) {
    static aETKY_TALK_PROC process[] = {
        // clang-format off
        (aETKY_TALK_PROC)none_proc1,
        aETKY_Explain_Env0123,
        aETKY_Explain_Env0123,
        aETKY_Explain_Env0123,
        aETKY_Explain_Env0123,
        aETKY_Find_Reac,
        aETKY_Give_Me_Fork,
        aETKY_Give_You_Present,
        // clang-format on
    };

    turkey->talk_action = talk_act;
    turkey->talk_proc = process[talk_act];
    aETKY_init_proc(turkey, play, talk_act);
}

static void aETKY_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aETKY_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
    mEv_actor_dying_message(mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN, actorx);
}

static void aETKY_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aETKY_GetTalkStartStatus(int* msg_no, int* next_talk_act, ACTOR* actorx) {
    EV_TURKEY_ACTOR* turkey = (EV_TURKEY_ACTOR*)actorx;
    aEv_turkey_common_c* common_p = turkey->ev_common_p;

    if (turkey->_9B1 == 1) {
        *msg_no = 0x3C1D + gamePT->frame_counter % 5;
        *next_talk_act = aETKY_TALK_WAIT_END;
    } else {
        *msg_no = 0x3BFE;
        *next_talk_act = aETKY_TALK_EXPLAIN_ENV0;

        if (common_p != NULL && common_p->_00 != 0) {
            *msg_no = 0x3C05 + turkey->present_idx;
            *next_talk_act = aETKY_TALK_FIND_REAC;
        }
    }
}

static void aETKY_SetTalkInfo(ACTOR* actorx) {
    EV_TURKEY_ACTOR* turkey = (EV_TURKEY_ACTOR*)actorx;
    int msg_no;
    int next_talk_act;

    aETKY_GetTalkStartStatus(&msg_no, &next_talk_act, actorx);
    turkey->talk_msg_no = msg_no;
    turkey->next_talk_action = next_talk_act;
    mEv_set_status(mEv_EVENT_HARVEST_FESTIVAL_FRANKLIN, mEv_STATUS_TALK);
    mDemo_Set_msg_num(msg_no);
    turkey->ev_common_p->_00++;
    turkey->_9B1 = 1;
}

static void aETKY_TalkRequest(ACTOR* actorx, GAME* game) {
    EV_TURKEY_ACTOR* turkey = (EV_TURKEY_ACTOR*)actorx;
    
    if (turkey->_9B1 == 0) {
        ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
        xyz_t delta;

        delta.x = playerx->world.position.x - actorx->world.position.x;
        delta.y = ABS(playerx->world.position.y - actorx->world.position.y);
        delta.z = playerx->world.position.z - actorx->world.position.z;

        if (delta.y <= 10.0f) {
            if (SQ(delta.x) + SQ(delta.z) <= SQ(55.0f)) {
                if (mDemo_Check(mDemo_TYPE_SPEAK, actorx) == TRUE) {
                    if (mDemo_Check_ListenAble() == FALSE) {
                        mDemo_Set_ListenAble();
                        turkey->_9B1 = 1;
                    }
                } else {
                    mDemo_Request(mDemo_TYPE_SPEAK, actorx, aETKY_SetTalkInfo);
                }
            }
        }
    } else {
        mDemo_Request(mDemo_TYPE_TALK, actorx, aETKY_SetTalkInfo);
    }
}

static int aETKY_TalkInit(ACTOR* actorx, GAME* game) {
    EV_TURKEY_ACTOR* turkey = (EV_TURKEY_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    (*turkey->talk_setup_proc)(turkey, play, turkey->next_talk_action);
    mDemo_Set_ListenAble();
    return TRUE;
}

static int aETKY_TalkEndCheck(ACTOR* actorx, GAME* game) {
    EV_TURKEY_ACTOR* turkey = (EV_TURKEY_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    (*turkey->talk_proc)(turkey, play);
    
    if (!mDemo_Check(mDemo_TYPE_TALK, actorx) && !mDemo_Check(mDemo_TYPE_SPEAK, actorx)) {
        return TRUE;
    }

    if (mDemo_Check(mDemo_TYPE_SPEAK, actorx) == TRUE) {
        ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);
        s16 actor_look_angle = actorx->shape_info.rotation.y + DEG2SHORT_ANGLE2(180.0f);
        s_xyz pl_angle = playerx->shape_info.rotation;

        if (actor_look_angle != pl_angle.y) {
            add_calc_short_angle2(&pl_angle.y, actor_look_angle, 0.2f, DEG2SHORT_ANGLE(22.5f), 0);
            GET_PLAYER_ACTOR_NOW()->Set_force_position_angle_proc(gamePT, NULL, &pl_angle, mPlayer_FORCE_POSITION_ANGLE_ROTY);
        }
    }

    return FALSE;
}

static void aETKY_actor_move(ACTOR* actorx, GAME* game) {
    EV_TURKEY_ACTOR* turkey = (EV_TURKEY_ACTOR*)actorx;    
    ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game); // @unused

    turkey->npc_class.palActorIgnoreTimer = -1;
    NPC_CLIP->move_proc(actorx, game);
    turkey->npc_class.palActorIgnoreTimer = -1;
}

static void aETKY_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
