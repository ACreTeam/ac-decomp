#include "ac_hatumode_npc0.h"

#include "m_common_data.h"
#include "m_player_lib.h"

static void aHN0_actor_ct(ACTOR* actorx, GAME* game);
static void aHN0_actor_dt(ACTOR* actorx, GAME* game);
static void aHN0_actor_move(ACTOR* actorx, GAME* game);
static void aHN0_actor_draw(ACTOR* actorx, GAME* game);
static void aHN0_actor_save(ACTOR* actorx, GAME* game);
static void aHN0_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Hatumode_Npc0_Profile = {
    mAc_PROFILE_HATUMODE_NPC0,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_EV_HATUMODE_0,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(HATUMODE_NPC0_ACTOR),
    &aHN0_actor_ct,
    &aHN0_actor_dt,
    &aHN0_actor_init,
    mActor_NONE_PROC1,
    &aHN0_actor_save
};
// clang-format on

static void aHN0_talk_request(ACTOR* actorx, GAME* game);
static int aHN0_talk_init(ACTOR* actorx, GAME* game);
static int aHN0_talk_end_chk(ACTOR* actorx, GAME* game);

static void aHN0_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aEv_init_hatumode_save_area(void);
static void aHN0_setup_think_proc(HATUMODE_NPC0_ACTOR* h_npc, GAME_PLAY* play, u8 think_idx);

static void aHN0_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        &aHN0_actor_move,
        &aHN0_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)&none_proc1,
        &aHN0_talk_init,
        &aHN0_talk_end_chk,
        0,
    };
    // clang-format on

    // clang-format off
    static int base_msg_table[] = {
        MSG_7679,
        MSG_7697,
        MSG_7661,
        MSG_7715,
        MSG_7733,
        MSG_7751,
    };
    // clang-format on

    if (CLIP(npc_clip)->birth_check_proc(actorx, game) == TRUE) {
        HATUMODE_NPC0_ACTOR* h_npc = (HATUMODE_NPC0_ACTOR*)actorx;

        h_npc->npc_class.schedule.schedule_proc = &aHN0_schedule_proc;
        CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
        h_npc->npc_class.palActorIgnoreTimer = -1;
        h_npc->think_change_flag = FALSE;
        h_npc->base_msg = base_msg_table[mNpc_GetNpcLooks(actorx)];

        if (actorx->npc_id == SP_NPC_EV_HATUMODE_0) {
            aEv_init_hatumode_save_area();
            actorx->cull_radius = 800.0f;
        }

        h_npc->npc_class.collision.check_kind = aNPC_BG_CHECK_TYPE_NONE;
        actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, 0.0f);
        actorx->position_speed.y = 0.0f;
        actorx->gravity = 0.0f;
        actorx->max_velocity_y = 0.0f;
        h_npc->npc_class.collision.pipe.attribute.pipe.radius = 20;
    }
}

static void aHN0_actor_save(ACTOR* actorx, GAME* game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aHN0_actor_dt(ACTOR* actorx, GAME* game) {
    aEv_hatumode_save_c* hatumode_p = (aEv_hatumode_save_c*)mEv_get_save_area(1, 7);

    CLIP(npc_clip)->dt_proc(actorx, game);
    if (actorx->npc_id == SP_NPC_EV_HATUMODE_0) {
        hatumode_p->flags0 = 0x01;
        hatumode_p->state = 2;
    }
}

static void aHN0_actor_init(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->init_proc(actorx, game);
}

static void aHN0_actor_move(ACTOR* actorx, GAME* game) {
    aEv_hatumode_save_c* hatumode_p = (aEv_hatumode_save_c*)mEv_get_save_area(1, 7);

    CLIP(npc_clip)->move_proc(actorx, game);
    ((NPC_ACTOR*)actorx)->collision.pipe.attribute.pipe.radius = 20;
    if (hatumode_p != NULL && actorx->npc_id != SP_NPC_EV_HATUMODE_0 && hatumode_p->state == 2 &&
        (hatumode_p->flags0 & (1 << (actorx->npc_id - SP_NPC_EV_HATUMODE_0))) == 0) {
        hatumode_p->flags0 |= (1 << (actorx->npc_id - SP_NPC_EV_HATUMODE_0));
        Actor_delete(actorx);
    }
}

static void aHN0_actor_draw(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_hatumode_npc0_talk.c_inc"
#include "../src/actor/npc/ac_hatumode_npc0_schedule.c_inc"
