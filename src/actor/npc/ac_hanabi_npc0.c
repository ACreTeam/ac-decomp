#include "ac_hanabi_npc0.h"

#include "m_common_data.h"

enum {
    aHN0_ACT_TURN,
    aHN0_ACT_WALK,
    aHN0_ACT_HURRAHS,

    aHN0_ACT_NUM
};

static void aHN0_actor_ct(ACTOR* actorx, GAME* game);
static void aHN0_actor_dt(ACTOR* actorx, GAME* game);
static void aHN0_actor_move(ACTOR* actorx, GAME* game);
static void aHN0_actor_draw(ACTOR* actorx, GAME* game);
static void aHN0_actor_save(ACTOR* actorx, GAME* game);
static void aHN0_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Hanabi_Npc0_Profile = {
    mAc_PROFILE_HANABI_NPC0,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(HANABI_NPC0_ACTOR),
    aHN0_actor_ct,
    aHN0_actor_dt,
    aHN0_actor_init,
    mActor_NONE_PROC1,
    aHN0_actor_save,
};
// clang-format on

static void aHN0_talk_request(ACTOR* actorx, GAME* game);
static int aHN0_talk_init(ACTOR* actorx, GAME* game);
static int aHN0_talk_end_chk(ACTOR* actorx, GAME* game);

static void aHN0_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);

static void aHN0_setupAction(HANABI_NPC0_ACTOR* actor, int action);

static void aHN0_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aHN0_actor_move,
        aHN0_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        aHN0_talk_request,
        aHN0_talk_init,
        aHN0_talk_end_chk,
        0,
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        HANABI_NPC0_ACTOR* actor = (HANABI_NPC0_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aHN0_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }
}

static void aHN0_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aHN0_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aHN0_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aHN0_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

static void aHN0_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_hanabi_npc0_anime.c_inc"
#include "../src/actor/npc/ac_hanabi_npc0_talk.c_inc"
