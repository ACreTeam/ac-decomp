#include "ac_countdown_npc0.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"

enum {
    aCD0_ACT_BEFORE_WAIT,
    aCD0_ACT_FREEZE_PL_WAIT,
    aCD0_ACT_AFTER_WAIT,
    aCD0_ACT_TALK_AFTER_TURN,

    aCD0_ACT_NUM
};

enum {
    aCD0_TERM_1_HOUR,
    aCD0_TERM_30_MIN,
    aCD0_TERM_10_MIN,
    aCD0_TERM_5_MIN,
    aCD0_TERM_1_MIN,
    aCD0_TERM_NEW_YEAR,
    aCD0_TERM_AFTER_10_SEC,

    aCD0_TERM_NUM
};

static void aCD0_actor_ct(ACTOR* actorx, GAME* game);
static void aCD0_actor_dt(ACTOR* actorx, GAME* game);
static void aCD0_actor_move(ACTOR* actorx, GAME* game);
static void aCD0_actor_draw(ACTOR* actorx, GAME* game);
static void aCD0_actor_save(ACTOR* actorx, GAME* game);
static void aCD0_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Countdown_Npc0_Profile = {
    mAc_PROFILE_COUNTDOWN_NPC0,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(COUNTDOWN_NPC0_ACTOR),
    aCD0_actor_ct,
    aCD0_actor_dt,
    aCD0_actor_init,
    mActor_NONE_PROC1,
    aCD0_actor_save,
};
// clang-format on

// clang-format off
static int aCD0_demo_flg[] = {
    aNPC_COND_DEMO_SKIP_HEAD_LOOKAT | aNPC_COND_DEMO_SKIP_FORWARD_CHECK | aNPC_COND_DEMO_SKIP_BGCHECK | aNPC_COND_DEMO_SKIP_MOVE_Y | aNPC_COND_DEMO_SKIP_MOVE_CIRCLE_REV | aNPC_COND_DEMO_SKIP_MOVE_RANGE_CHECK,
    aNPC_COND_DEMO_SKIP_HEAD_LOOKAT | aNPC_COND_DEMO_SKIP_FORWARD_CHECK | aNPC_COND_DEMO_SKIP_BGCHECK | aNPC_COND_DEMO_SKIP_MOVE_Y | aNPC_COND_DEMO_SKIP_MOVE_CIRCLE_REV | aNPC_COND_DEMO_SKIP_MOVE_RANGE_CHECK,
    aNPC_COND_DEMO_SKIP_FORWARD_CHECK | aNPC_COND_DEMO_SKIP_BGCHECK | aNPC_COND_DEMO_SKIP_MOVE_Y | aNPC_COND_DEMO_SKIP_MOVE_CIRCLE_REV | aNPC_COND_DEMO_SKIP_MOVE_RANGE_CHECK,
    aNPC_COND_DEMO_SKIP_FORWARD_CHECK | aNPC_COND_DEMO_SKIP_BGCHECK | aNPC_COND_DEMO_SKIP_MOVE_Y | aNPC_COND_DEMO_SKIP_MOVE_CIRCLE_REV | aNPC_COND_DEMO_SKIP_MOVE_RANGE_CHECK,
};
// clang-format on

static void aCD0_force_talk_request(ACTOR* actorx, GAME* game);
static void aCD0_norm_talk_request(ACTOR* actorx, GAME* game);
static int aCD0_talk_init(ACTOR* actorx, GAME* game);
static int aCD0_talk_end_chk(ACTOR* actorx, GAME* game);

static void aCD0_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);

static void aCD0_setupAction(COUNTDOWN_NPC0_ACTOR* actor, int action);

static void aCD0_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aCD0_actor_move,
        aCD0_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        aCD0_norm_talk_request,
        aCD0_talk_init,
        aCD0_talk_end_chk,
        0,
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        COUNTDOWN_NPC0_ACTOR* actor = (COUNTDOWN_NPC0_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aCD0_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }
}

static void aCD0_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aCD0_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aCD0_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aCD0_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

static void aCD0_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_countdown_npc0_anime.c_inc"
#include "../src/actor/npc/ac_countdown_npc0_talk.c_inc"
