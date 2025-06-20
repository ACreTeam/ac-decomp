#include "ac_tokyoso_npc1.h"

#include "ac_tokyoso_control.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_soncho.h"
#include "libultra/libultra.h"

// TODO: coordinate enum types with ac_tokyoso_control

// enum {
//     aTKN1_THINK_BIRTH,
//     aTKN1_THINK_KYORO_MAE,
//     aTKN1_THINK_KYORO,
//     aTKN1_THINK_WALK_TURN,
//     aTKN1_THINK_WALK,
//     aTKN1_THINK_HIROU_MAE,
//     aTKN1_THINK_HIROU,
//     aTKN1_THINK_HIROU_SP,
//     aTKN1_THINK_HIROU_END,
//     aTKN1_THINK_NAGERU,
//     aTKN1_THINK_NAGERU_END,

//     aTKN1_THINK_NUM
// };

// enum {
//     aTKN1_THINK_PROC_NONE,
//     aTKN1_THINK_PROC_TIMER_NEXT,
//     aTKN1_THINK_PROC_BIRTH,
//     aTKN1_THINK_PROC_TURN_NEXT,
//     aTKN1_THINK_PROC_WALK,
//     aTKN1_THINK_PROC_HIROU,
//     aTKN1_THINK_PROC_HIROU_SP,
//     aTKN1_THINK_PROC_ANIME_NEXT,
//     aTKN1_THINK_PROC_NAGERU,
//     aTKN1_THINK_PROC_NAGERU_END,

//     aTKN1_THINK_PROC_NUM
// };

// enum {
//     aTKN1_THINK_INIT_PROC_NONE,
//     aTKN1_THINK_INIT_PROC_NORMAL_WAIT,
//     aTKN1_THINK_INIT_PROC_MOVE,
//     aTKN1_THINK_INIT_PROC_KYORO_MAE,
//     aTKN1_THINK_INIT_PROC_KYORO,
//     aTKN1_THINK_INIT_PROC_WALK_TURN,
//     aTKN1_THINK_INIT_PROC_HIROU_MAE,
//     aTKN1_THINK_INIT_PROC_HIROU,
//     aTKN1_THINK_INIT_PROC_HIROU_SP,
//     aTKN1_THINK_INIT_PROC_HIROU_END,
//     aTKN1_THINK_INIT_PROC_NAGERU,
//     aTKN1_THINK_INIT_PROC_NAGERU_END,

//     aTKN1_THINK_INIT_PROC_NUM
// };

static void aTKN1_actor_ct(ACTOR* actorx, GAME* game);
static void aTKN1_actor_dt(ACTOR* actorx, GAME* game);
static void aTKN1_actor_move(ACTOR* actorx, GAME* game);
static void aTKN1_actor_draw(ACTOR* actorx, GAME* game);
static void aTKN1_actor_save(ACTOR* actorx, GAME* game);
static void aTKN1_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Tokyoso_Npc1_Profile = {
    mAc_PROFILE_TOKYOSO_NPC1,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_EV_TOKYOSO_1,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(TOKYOSO_NPC1_ACTOR),
    aTKN1_actor_ct,
    aTKN1_actor_dt,
    aTKN1_actor_init,
    mActor_NONE_PROC1,
    aTKN1_actor_save,
};
// clang-format on

static void aTKN1_talk_request(ACTOR* actorx, GAME* game);
static int aTKN1_talk_init(ACTOR* actorx, GAME* game);
static int aTKN1_talk_end_chk(ACTOR* actorx, GAME* game);

static void aTKN1_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aTKN1_setup_think_proc(TOKYOSO_NPC1_ACTOR* actor, GAME_PLAY* play, u8 think_idx);

static void aTKN1_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aTKN1_actor_move,
        aTKN1_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aTKN1_talk_init,
        aTKN1_talk_end_chk,
        0,
    };
    TOKYOSO_NPC1_ACTOR* actor = (TOKYOSO_NPC1_ACTOR*)actorx;

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        static int base_msg_table[] = { MSG_6621, MSG_6637, MSG_6605, MSG_6653, MSG_6669, MSG_6685 };

        actor->npc_class.schedule.schedule_proc = aTKN1_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);

        actor->npc_class.palActorIgnoreTimer = -1;
        actor->base_msg = base_msg_table[mNpc_GetNpcLooks(actorx)];
        actor->change_flag = FALSE;
        actor->flags = 0;
        actor->npc_class.head.lock_flag = TRUE;
    }
}

static void aTKN1_actor_save(ACTOR* actorx, GAME* game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aTKN1_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aTKN1_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static int aTKN1_set_request_act(TOKYOSO_NPC1_ACTOR* actor, u8 prio, u8 idx, u8 type, u16 obj, s16 move_x, s16 move_z) {
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

static void aTKN1_actor_move(ACTOR* actorx, GAME* game) {
    aEv_tokyoso_c* tokyoso = (aEv_tokyoso_c*)mEv_get_save_area(mEv_EVENT_SPORTS_FAIR_FOOT_RACE, 8);

    NPC_CLIP->move_proc(actorx, game);
    if (tokyoso != NULL) {
        if (tokyoso->_00 == 3) {
            if ((tokyoso->flags & aTKC_NPCIDX2DELETEFLG(actorx->npc_id)) == 0) {
                tokyoso->flags |= aTKC_NPCIDX2DELETEFLG(actorx->npc_id);
                Actor_delete(actorx);
            }
        }
    }
}

#include "../src/actor/npc/ac_tokyoso_npc1_talk.c_inc"
#include "../src/actor/npc/ac_tokyoso_npc1_schedule.c_inc"

static void aTKN1_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
