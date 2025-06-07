#include "ac_hanabi_npc1.h"

#include "m_common_data.h"

enum {
    aHN1_ACT_TURN,
    aHN1_ACT_FAN,
    aHN1_ACT_CLAPPING,
    aHN1_ACT_HURRAHS,

    aHN1_ACT_NUM
};

static void aHN1_actor_ct(ACTOR* actorx, GAME* game);
static void aHN1_actor_dt(ACTOR* actorx, GAME* game);
static void aHN1_actor_move(ACTOR* actorx, GAME* game);
static void aHN1_actor_draw(ACTOR* actorx, GAME* game);
static void aHN1_actor_save(ACTOR* actorx, GAME* game);
static void aHN1_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Hanabi_Npc1_Profile = {
    mAc_PROFILE_HANABI_NPC1,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(HANABI_NPC1_ACTOR),
    aHN1_actor_ct,
    aHN1_actor_dt,
    aHN1_actor_init,
    mActor_NONE_PROC1,
    aHN1_actor_save,
};
// clang-format on

static void aHN1_talk_request(ACTOR* actorx, GAME* game);
static int aHN1_talk_init(ACTOR* actorx, GAME* game);
static int aHN1_talk_end_chk(ACTOR* actorx, GAME* game);

static void aHN1_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);

static void aHN1_setupAction(HANABI_NPC1_ACTOR* actor, int action);

static void aHN1_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aHN1_actor_move,
        aHN1_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        aHN1_talk_request,
        aHN1_talk_init,
        aHN1_talk_end_chk,
        0,
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        HANABI_NPC1_ACTOR* actor = (HANABI_NPC1_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aHN1_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        actor->npc_class.palActorIgnoreTimer = -1;
    }
}

static void aHN1_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aHN1_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aHN1_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aHN1_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

static void aHN1_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_hanabi_npc1_anime.c_inc"
#include "../src/actor/npc/ac_hanabi_npc1_talk.c_inc"
