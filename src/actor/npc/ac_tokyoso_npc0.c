#include "ac_tokyoso_npc0.h"

#include "ac_tokyoso_control.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_soncho.h"
#include "libultra/libultra.h"

// TODO: coordinate enum types with ac_tokyoso_control

// enum {
//     aTKN0_THINK_BIRTH,
//     aTKN0_THINK_KYORO_MAE,
//     aTKN0_THINK_KYORO,
//     aTKN0_THINK_WALK_TURN,
//     aTKN0_THINK_WALK,
//     aTKN0_THINK_HIROU_MAE,
//     aTKN0_THINK_HIROU,
//     aTKN0_THINK_HIROU_SP,
//     aTKN0_THINK_HIROU_END,
//     aTKN0_THINK_NAGERU,
//     aTKN0_THINK_NAGERU_END,

//     aTKN0_THINK_NUM
// };

// enum {
//     aTKN0_THINK_PROC_NONE,
//     aTKN0_THINK_PROC_TIMER_NEXT,
//     aTKN0_THINK_PROC_BIRTH,
//     aTKN0_THINK_PROC_TURN_NEXT,
//     aTKN0_THINK_PROC_WALK,
//     aTKN0_THINK_PROC_HIROU,
//     aTKN0_THINK_PROC_HIROU_SP,
//     aTKN0_THINK_PROC_ANIME_NEXT,
//     aTKN0_THINK_PROC_NAGERU,
//     aTKN0_THINK_PROC_NAGERU_END,

//     aTKN0_THINK_PROC_NUM
// };

// enum {
//     aTKN0_THINK_INIT_PROC_NONE,
//     aTKN0_THINK_INIT_PROC_NORMAL_WAIT,
//     aTKN0_THINK_INIT_PROC_MOVE,
//     aTKN0_THINK_INIT_PROC_KYORO_MAE,
//     aTKN0_THINK_INIT_PROC_KYORO,
//     aTKN0_THINK_INIT_PROC_WALK_TURN,
//     aTKN0_THINK_INIT_PROC_HIROU_MAE,
//     aTKN0_THINK_INIT_PROC_HIROU,
//     aTKN0_THINK_INIT_PROC_HIROU_SP,
//     aTKN0_THINK_INIT_PROC_HIROU_END,
//     aTKN0_THINK_INIT_PROC_NAGERU,
//     aTKN0_THINK_INIT_PROC_NAGERU_END,

//     aTKN0_THINK_INIT_PROC_NUM
// };

static void aTKN0_actor_ct(ACTOR* actorx, GAME* game);
static void aTKN0_actor_dt(ACTOR* actorx, GAME* game);
static void aTKN0_actor_move(ACTOR* actorx, GAME* game);
static void aTKN0_actor_draw(ACTOR* actorx, GAME* game);
static void aTKN0_actor_save(ACTOR* actorx, GAME* game);
static void aTKN0_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Tokyoso_Npc0_Profile = {
    mAc_PROFILE_TOKYOSO_NPC0,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_EV_TOKYOSO_0,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(TOKYOSO_NPC0_ACTOR),
    aTKN0_actor_ct,
    aTKN0_actor_dt,
    aTKN0_actor_init,
    mActor_NONE_PROC1,
    aTKN0_actor_save,
};
// clang-format on

static void aTKN0_talk_request(ACTOR* actorx, GAME* game);
static int aTKN0_talk_init(ACTOR* actorx, GAME* game);
static int aTKN0_talk_end_chk(ACTOR* actorx, GAME* game);

static void aTKN0_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aTKN0_setup_think_proc(TOKYOSO_NPC0_ACTOR* actor, GAME_PLAY* play, s16 think_idx);

static void aTKN0_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aTKN0_actor_move,
        aTKN0_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aTKN0_talk_init,
        aTKN0_talk_end_chk,
        0,
    };
    TOKYOSO_NPC0_ACTOR* actor = (TOKYOSO_NPC0_ACTOR*)actorx;

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        static int base_msg_table[] = { 0x19DD, 0x19ED, 0x19CD, 0x19FD, 0x1A0D, 0x1A1D };

        actor->npc_class.schedule.schedule_proc = aTKN0_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);

        actor->npc_class.palActorIgnoreTimer = -1;
        actor->base_msg = base_msg_table[mNpc_GetNpcLooks(actorx)];
        actor->change_flag = FALSE;
        actorx->cull_radius = 800.0f;

        {
            aEv_tokyoso_c* tokyoso = (aEv_tokyoso_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 8);

            if (tokyoso != NULL && tokyoso->_00 == 3) {
                tokyoso->_00 = 0;
                tokyoso->flags = 0;
            }
        }

        actor->npc_class.head.lock_flag = TRUE;
        actor->npc_class.collision.check_kind = mCoBG_CHECK_TYPE_NORMAL;
        actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, 0.0f);
        actorx->position_speed.y = 0.0f;
        actorx->gravity = 0.0f;
        actorx->max_velocity_y = 0.0f;
    }
}

static void aTKN0_actor_save(ACTOR* actorx, GAME* game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aTKN0_actor_dt(ACTOR* actorx, GAME* game) {
    aEv_tokyoso_c* tokyoso = (aEv_tokyoso_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 8);

    if (tokyoso != NULL) {
        tokyoso->flags = aTKC_FLAG_DELETE_NPC0;
        tokyoso->_00 = 3;
    }

    NPC_CLIP->dt_proc(actorx, game);
}

static void aTKN0_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static int aTKN0_set_request_act(TOKYOSO_NPC0_ACTOR* actor, u8 prio, u8 idx, u8 type, u16 obj, s16 move_x, s16 move_z) {
    int res = FALSE;

    if (prio >= actor->npc_class.request.act_priority) {
        u16 args[6];
        
        bzero(args, sizeof(args));
        args[0] = obj;
        args[2] = move_x;
        args[3] = move_z;
        actor->npc_class.request.act_priority = prio;
        actor->npc_class.request.act_idx = idx;
        actor->npc_class.request.act_type = type;
        mem_copy((u8*)actor->npc_class.request.act_args, (u8*)args, sizeof(args));
        res = TRUE;
    }

    return res;
}

static void aTKN0_make_pistoru(ACTOR* actorx, GAME* game) {
    TOKYOSO_NPC0_ACTOR* actor = (TOKYOSO_NPC0_ACTOR*)actorx;

    if (actor->npc_class.right_hand.item_actor_p == NULL) {
        ACTOR* pistol = CLIP(tools_clip)->aTOL_birth_proc(TOOL_PISTOL, aTOL_ACTION_S_TAKEOUT, actorx, game, -1, NULL);

        if (pistol != NULL) {
            actor->npc_class.right_hand.item_actor_p = pistol;
        }
    }
}

static void aTKN0_actor_move(ACTOR* actorx, GAME* game) {
    aTKN0_make_pistoru(actorx, game);
    NPC_CLIP->move_proc(actorx, game);
}

#include "../src/actor/npc/ac_tokyoso_npc0_talk.c_inc"
#include "../src/actor/npc/ac_tokyoso_npc0_schedule.c_inc"

static void aTKN0_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
