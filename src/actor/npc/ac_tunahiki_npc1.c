#include "ac_tunahiki_npc1.h"

#include "ac_tunahiki_control.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_soncho.h"
#include "libultra/libultra.h"

// TODO: coordinate enum types with ac_tunahiki_control

// enum {
//     aTNN1_THINK_BIRTH,
//     aTNN1_THINK_KYORO_MAE,
//     aTNN1_THINK_KYORO,
//     aTNN1_THINK_WALK_TURN,
//     aTNN1_THINK_WALK,
//     aTNN1_THINK_HIROU_MAE,
//     aTNN1_THINK_HIROU,
//     aTNN1_THINK_HIROU_SP,
//     aTNN1_THINK_HIROU_END,
//     aTNN1_THINK_NAGERU,
//     aTNN1_THINK_NAGERU_END,

//     aTNN1_THINK_NUM
// };

// enum {
//     aTNN1_THINK_PROC_NONE,
//     aTNN1_THINK_PROC_TIMER_NEXT,
//     aTNN1_THINK_PROC_BIRTH,
//     aTNN1_THINK_PROC_TURN_NEXT,
//     aTNN1_THINK_PROC_WALK,
//     aTNN1_THINK_PROC_HIROU,
//     aTNN1_THINK_PROC_HIROU_SP,
//     aTNN1_THINK_PROC_ANIME_NEXT,
//     aTNN1_THINK_PROC_NAGERU,
//     aTNN1_THINK_PROC_NAGERU_END,

//     aTNN1_THINK_PROC_NUM
// };

// enum {
//     aTNN1_THINK_INIT_PROC_NONE,
//     aTNN1_THINK_INIT_PROC_NORMAL_WAIT,
//     aTNN1_THINK_INIT_PROC_MOVE,
//     aTNN1_THINK_INIT_PROC_KYORO_MAE,
//     aTNN1_THINK_INIT_PROC_KYORO,
//     aTNN1_THINK_INIT_PROC_WALK_TURN,
//     aTNN1_THINK_INIT_PROC_HIROU_MAE,
//     aTNN1_THINK_INIT_PROC_HIROU,
//     aTNN1_THINK_INIT_PROC_HIROU_SP,
//     aTNN1_THINK_INIT_PROC_HIROU_END,
//     aTNN1_THINK_INIT_PROC_NAGERU,
//     aTNN1_THINK_INIT_PROC_NAGERU_END,

//     aTNN1_THINK_INIT_PROC_NUM
// };

static void aTNN1_actor_ct(ACTOR* actorx, GAME* game);
static void aTNN1_actor_dt(ACTOR* actorx, GAME* game);
static void aTNN1_actor_move(ACTOR* actorx, GAME* game);
static void aTNN1_actor_draw(ACTOR* actorx, GAME* game);
static void aTNN1_actor_save(ACTOR* actorx, GAME* game);
static void aTNN1_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Tunahiki_Npc1_Profile = {
    mAc_PROFILE_TUNAHIKI_NPC1,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_EV_TUNAHIKI_1,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(TUNAHIKI_NPC1_ACTOR),
    aTNN1_actor_ct,
    aTNN1_actor_dt,
    aTNN1_actor_init,
    mActor_NONE_PROC1,
    aTNN1_actor_save,
};
// clang-format on

static int aTNN1_talk_init(ACTOR* actorx, GAME* game);
static int aTNN1_talk_end_chk(ACTOR* actorx, GAME* game);

static void aTNN1_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aTNN1_setup_think_proc(TUNAHIKI_NPC1_ACTOR* actor, GAME_PLAY* play, u8 think_idx);

static void aTNN1_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aTNN1_actor_move,
        aTNN1_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aTNN1_talk_init,
        aTNN1_talk_end_chk,
        0,
    };
    TUNAHIKI_NPC1_ACTOR* actor = (TUNAHIKI_NPC1_ACTOR*)actorx;

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        static int base_msg_table[] = { MSG_6532, MSG_6544, MSG_6520, MSG_6556, MSG_6568, MSG_6580 };

        actor->npc_class.schedule.schedule_proc = aTNN1_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);

        actor->npc_class.palActorIgnoreTimer = -1;
        actor->change_flag = FALSE;
        actor->npc_class.head.lock_flag = TRUE;
        actor->npc_class.talk_info.turn = aNPC_TALK_TURN_NONE;
        actor->base_msg = base_msg_table[mNpc_GetNpcLooks(actorx)];
        actor->npc_class.collision.check_kind = mCoBG_CHECK_TYPE_NORMAL;
        actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, 0.0f);
        actorx->position_speed.y = 0.0f;
        actorx->gravity = 0.0f;
        actorx->max_velocity_y = 0.0f;
    }
}

static void aTNN1_actor_save(ACTOR* actorx, GAME* game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aTNN1_actor_dt(ACTOR* actorx, GAME* game) {
    aEv_tunahiki_c* tunahiki = (aEv_tunahiki_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR, 9);

    NPC_CLIP->dt_proc(actorx, game);
    tunahiki->flag |= aTNC_NPCIDX2DELETEFLG(actorx->npc_id);
}

static void aTNN1_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static int aTNN1_set_request_act(TUNAHIKI_NPC1_ACTOR* actor, u8 prio, u8 idx, u8 type, u16 obj, s16 move_x,
                                 s16 move_z) {
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

static void aTNN1_actor_move(ACTOR* actorx, GAME* game) {
    aEv_tunahiki_c* tunahiki = (aEv_tunahiki_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR, 9);
    TUNAHIKI_NPC1_ACTOR* actor = (TUNAHIKI_NPC1_ACTOR*)actorx;

    NPC_CLIP->move_proc(actorx, game);
    actorx->world.position.z = actorx->home.position.z;

    if (actor->think_idx != 0 && tunahiki != NULL) {
        actorx->world.position.x = actorx->home.position.x + tunahiki->rope_base;
    }

    if (tunahiki != NULL) {
        if (tunahiki->npc_state == aTNC_NPC_STATE2 && (tunahiki->flag & aTNC_NPCIDX2DELETEFLG(actorx->npc_id)) == 0) {
            Actor_delete(actorx);
        }
    }
}

#include "../src/actor/npc/ac_tunahiki_npc1_talk.c_inc"
#include "../src/actor/npc/ac_tunahiki_npc1_schedule.c_inc"

static void aTNN1_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
