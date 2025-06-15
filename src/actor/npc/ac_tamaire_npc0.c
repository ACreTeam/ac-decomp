#include "ac_tamaire_npc0.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_soncho.h"
#include "libultra/libultra.h"

static void aTMN0_actor_ct(ACTOR* actorx, GAME* game);
static void aTMN0_actor_dt(ACTOR* actorx, GAME* game);
static void aTMN0_actor_move(ACTOR* actorx, GAME* game);
static void aTMN0_actor_draw(ACTOR* actorx, GAME* game);
static void aTMN0_actor_save(ACTOR* actorx, GAME* game);
static void aTMN0_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Tamaire_Npc0_Profile = {
    mAc_PROFILE_TAMAIRE_NPC0,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_EV_TAMAIRE_0,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(TAMAIRE_NPC0_ACTOR),
    aTMN0_actor_ct,
    aTMN0_actor_dt,
    aTMN0_actor_init,
    mActor_NONE_PROC1,
    aTMN0_actor_save,
};
// clang-format on

static void aTMN0_talk_request(ACTOR* actorx, GAME* game);
static int aTMN0_talk_init(ACTOR* actorx, GAME* game);
static int aTMN0_talk_end_chk(ACTOR* actorx, GAME* game);

static void aTMN0_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aTMN0_setup_think_proc(TAMAIRE_NPC0_ACTOR* actor, GAME_PLAY* play, u8 think_idx);

static void aTMN0_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aTMN0_actor_move,
        aTMN0_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aTMN0_talk_init,
        aTMN0_talk_end_chk,
        0,
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        TAMAIRE_NPC0_ACTOR* actor = (TAMAIRE_NPC0_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aTMN0_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);

        actor->npc_class.palActorIgnoreTimer = -1;
        actor->change_flag = FALSE;
        actor->npc_class.collision.check_kind = aNPC_BG_CHECK_TYPE_NONE;
        actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, 0.0f);
        actorx->position_speed.y = 0.0f;
        actorx->gravity = 0.0;
        actorx->max_velocity_y = 0.0f;
    }
}

static void aTMN0_actor_save(ACTOR* actorx, GAME* game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aTMN0_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aTMN0_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static int aTMN0_set_request_act(TAMAIRE_NPC0_ACTOR* actor, u8 prio, u8 idx, u8 type, u16 obj, s16 move_x, s16 move_z) {
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

static void aTMN0_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

#include "../src/actor/npc/ac_tamaire_npc0_talk.c_inc"
#include "../src/actor/npc/ac_tamaire_npc0_schedule.c_inc"

static void aTMN0_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
