#include "ac_countdown_npc1.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"

enum {
    aCD1_ACT_BEFORE_WAIT,
    aCD1_ACT_BEFORE_RUN,
    aCD1_ACT_BEFORE_TURN,
    aCD1_ACT_FRONT_TURN,
    aCD1_ACT_FRONT_WAIT,
    aCD1_ACT_COUNT_WAIT,
    aCD1_ACT_FIRE,
    aCD1_ACT_CLAP,
    aCD1_ACT_AFTER_WAIT,
    aCD1_ACT_AFTER_RUN,
    aCD1_ACT_AFTER_TURN,

    aCD1_ACT_NUM
};

enum {
    aCD1_TERM_1_HOUR,
    aCD1_TERM_30_MIN,
    aCD1_TERM_10_MIN,
    aCD1_TERM_5_MIN,
    aCD1_TERM_1_MIN,
    aCD1_TERM_NEW_YEAR,

    aCD1_TERM_NUM
};

enum {
    aCD1_ACT_TYPE_WAIT,
    aCD1_ACT_TYPE_RUN,
    aCD1_ACT_TYPE_TURN,

    aCD1_ACT_TYPE_NUM
};

static void aCD1_actor_ct(ACTOR* actorx, GAME* game);
static void aCD1_actor_dt(ACTOR* actorx, GAME* game);
static void aCD1_actor_move(ACTOR* actorx, GAME* game);
static void aCD1_actor_draw(ACTOR* actorx, GAME* game);
static void aCD1_actor_save(ACTOR* actorx, GAME* game);
static void aCD1_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Countdown_Npc1_Profile = {
    mAc_PROFILE_COUNTDOWN_NPC1,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(COUNTDOWN_NPC1_ACTOR),
    aCD1_actor_ct,
    aCD1_actor_dt,
    aCD1_actor_init,
    mActor_NONE_PROC1,
    aCD1_actor_save,
};
// clang-format on

static void aCD1_talk_request(ACTOR* actorx, GAME* game);
static int aCD1_talk_init(ACTOR* actorx, GAME* game);
static int aCD1_talk_end_chk(ACTOR* actorx, GAME* game);

static void aCD1_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);

static void aCD1_setupAction(COUNTDOWN_NPC1_ACTOR* actor, int action);

static void aCD1_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aCD1_actor_move,
        aCD1_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        aCD1_talk_request,
        aCD1_talk_init,
        aCD1_talk_end_chk,
        0,
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        COUNTDOWN_NPC1_ACTOR* actor = (COUNTDOWN_NPC1_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aCD1_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }
}

static void aCD1_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aCD1_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aCD1_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aCD1_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

static void aCD1_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_countdown_npc1_anime.c_inc"
#include "../src/actor/npc/ac_countdown_npc1_talk.c_inc"
