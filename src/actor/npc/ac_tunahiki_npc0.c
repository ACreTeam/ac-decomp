#include "ac_tunahiki_npc0.h"

#include "ac_tunahiki_control.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_soncho.h"
#include "libultra/libultra.h"

// TODO: coordinate enum types with ac_tunahiki_control

// enum {
//     aTNN0_THINK_BIRTH,
//     aTNN0_THINK_KYORO_MAE,
//     aTNN0_THINK_KYORO,
//     aTNN0_THINK_WALK_TURN,
//     aTNN0_THINK_WALK,
//     aTNN0_THINK_HIROU_MAE,
//     aTNN0_THINK_HIROU,
//     aTNN0_THINK_HIROU_SP,
//     aTNN0_THINK_HIROU_END,
//     aTNN0_THINK_NAGERU,
//     aTNN0_THINK_NAGERU_END,

//     aTNN0_THINK_NUM
// };

// enum {
//     aTNN0_THINK_PROC_NONE,
//     aTNN0_THINK_PROC_TIMER_NEXT,
//     aTNN0_THINK_PROC_BIRTH,
//     aTNN0_THINK_PROC_TURN_NEXT,
//     aTNN0_THINK_PROC_WALK,
//     aTNN0_THINK_PROC_HIROU,
//     aTNN0_THINK_PROC_HIROU_SP,
//     aTNN0_THINK_PROC_ANIME_NEXT,
//     aTNN0_THINK_PROC_NAGERU,
//     aTNN0_THINK_PROC_NAGERU_END,

//     aTNN0_THINK_PROC_NUM
// };

// enum {
//     aTNN0_THINK_INIT_PROC_NONE,
//     aTNN0_THINK_INIT_PROC_NORMAL_WAIT,
//     aTNN0_THINK_INIT_PROC_MOVE,
//     aTNN0_THINK_INIT_PROC_KYORO_MAE,
//     aTNN0_THINK_INIT_PROC_KYORO,
//     aTNN0_THINK_INIT_PROC_WALK_TURN,
//     aTNN0_THINK_INIT_PROC_HIROU_MAE,
//     aTNN0_THINK_INIT_PROC_HIROU,
//     aTNN0_THINK_INIT_PROC_HIROU_SP,
//     aTNN0_THINK_INIT_PROC_HIROU_END,
//     aTNN0_THINK_INIT_PROC_NAGERU,
//     aTNN0_THINK_INIT_PROC_NAGERU_END,

//     aTNN0_THINK_INIT_PROC_NUM
// };

static void aTNN0_actor_ct(ACTOR* actorx, GAME* game);
static void aTNN0_actor_dt(ACTOR* actorx, GAME* game);
static void aTNN0_actor_move(ACTOR* actorx, GAME* game);
static void aTNN0_actor_draw(ACTOR* actorx, GAME* game);
static void aTNN0_actor_save(ACTOR* actorx, GAME* game);
static void aTNN0_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Tunahiki_Npc0_Profile = {
    mAc_PROFILE_TUNAHIKI_NPC0,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_EV_TUNAHIKI_0,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(TUNAHIKI_NPC0_ACTOR),
    aTNN0_actor_ct,
    aTNN0_actor_dt,
    aTNN0_actor_init,
    mActor_NONE_PROC1,
    aTNN0_actor_save,
};
// clang-format on

static int aTNN0_talk_init(ACTOR* actorx, GAME* game);
static int aTNN0_talk_end_chk(ACTOR* actorx, GAME* game);

static void aTNN0_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aTNN0_setup_think_proc(TUNAHIKI_NPC0_ACTOR* actor, GAME_PLAY* play, u8 think_idx);

static void aTNN0_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aTNN0_actor_move,
        aTNN0_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aTNN0_talk_init,
        aTNN0_talk_end_chk,
        0,
    };
    TUNAHIKI_NPC0_ACTOR* actor = (TUNAHIKI_NPC0_ACTOR*)actorx;

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        static int base_msg_table[] = { 0x1984, 0x1990, 0x1978, 0x199C, 0x19A8, 0x19B4 };

        actor->npc_class.schedule.schedule_proc = aTNN0_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);

        actor->npc_class.palActorIgnoreTimer = -1;
        actor->change_flag = FALSE;
        actor->npc_class.head.lock_flag = TRUE;
        actor->base_msg = base_msg_table[mNpc_GetNpcLooks(actorx)];
        actor->npc_class.talk_info.turn = aNPC_TALK_TURN_NONE;
        actor->npc_class.talk_info.default_animation = aNPC_ANIM_HATAFURI1;
        actorx->talk_distance = 85.0f;
        actor->npc_class.collision.check_kind = mCoBG_CHECK_TYPE_NORMAL;
        actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, 0.0f);
        actorx->position_speed.y = 0.0f;
        actorx->gravity = 0.0f;
        actorx->max_velocity_y = 0.0f;
    }
}

static void aTNN0_actor_save(ACTOR* actorx, GAME* game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aTNN0_actor_dt(ACTOR* actorx, GAME* game) {
    aEv_tunahiki_c* tunahiki = (aEv_tunahiki_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_TUG_OF_WAR, 9);
    TUNAHIKI_NPC0_ACTOR* actor = (TUNAHIKI_NPC0_ACTOR*)actorx;

    if (tunahiki != NULL) {
        tunahiki->flag = 0;
        tunahiki->npc_state = aTNC_NPC_STATE2;
    }

    if (actor->rope_p != NULL) {
        Actor_delete(actor->rope_p);
    }

    NPC_CLIP->dt_proc(actorx, game);
}

static void aTNN0_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static int aTNN0_set_request_act(TUNAHIKI_NPC0_ACTOR* actor, u8 prio, u8 idx, u8 type, u16 obj, s16 move_x, s16 move_z) {
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

static void aTNN0_make_hata(ACTOR* actorx, GAME* game) {
    TUNAHIKI_NPC0_ACTOR* actor = (TUNAHIKI_NPC0_ACTOR*)actorx;

    if (actor->npc_class.right_hand.item_actor_p == NULL) {
        ACTOR* flag = CLIP(tools_clip)->aTOL_birth_proc(TOOL_FLAG, aTOL_ACTION_S_TAKEOUT, actorx, game, -1, NULL);

        if (flag != NULL) {
            actor->npc_class.right_hand.item_actor_p = flag;
        }
    }
}

static void aTNN0_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
    aTNN0_make_hata(actorx, game);
}

#include "../src/actor/npc/ac_tunahiki_npc0_talk.c_inc"
#include "../src/actor/npc/ac_tunahiki_npc0_schedule.c_inc"

static void aTNN0_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
