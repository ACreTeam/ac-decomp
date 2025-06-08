#include "ac_hanami_npc0.h"

#include "m_common_data.h"

enum {
    aHM0_ACT_WAIT,
    aHM0_ACT_MERRY,
    aHM0_ACT_DRINK,

    aHM0_ACT_NUM
};

static void aHM0_actor_ct(ACTOR* actorx, GAME* game);
static void aHM0_actor_dt(ACTOR* actorx, GAME* game);
static void aHM0_actor_move(ACTOR* actorx, GAME* game);
static void aHM0_actor_draw(ACTOR* actorx, GAME* game);
static void aHM0_actor_save(ACTOR* actorx, GAME* game);
static void aHM0_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Hanami_Npc0_Profile = {
    mAc_PROFILE_HANAMI_NPC0,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(HANAMI_NPC0_ACTOR),
    aHM0_actor_ct,
    aHM0_actor_dt,
    aHM0_actor_init,
    mActor_NONE_PROC1,
    aHM0_actor_save,
};
// clang-format on

static void aHM0_talk_request(ACTOR* actorx, GAME* game);
static int aHM0_talk_init(ACTOR* actorx, GAME* game);
static int aHM0_talk_end_chk(ACTOR* actorx, GAME* game);

static void aHM0_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);

static void aHM0_setupAction(HANAMI_NPC0_ACTOR* actor, int action);

static void aHM0_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aHM0_actor_move,
        aHM0_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        aHM0_talk_request,
        aHM0_talk_init,
        aHM0_talk_end_chk,
        0,
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        HANAMI_NPC0_ACTOR* actor = (HANAMI_NPC0_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aHM0_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }
}

static void aHM0_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aHM0_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aHM0_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aHM0_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

static void aHM0_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_hanami_npc0_anime.c_inc"
#include "../src/actor/npc/ac_hanami_npc0_talk.c_inc"
