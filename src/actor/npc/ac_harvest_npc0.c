#include "ac_harvest_npc0.h"
#include "m_name_table.h"
#include "ac_npc.h"
#include "ac_npc_h.h"
#include "m_common_data.h"
#include "m_msg.h"
#include "m_soncho.h"
#include "ac_shrine.h"

typedef struct npc_harvest_npc0_actor_s NPC_HARVEST_NPC0_ACTOR;

typedef void (*aHT0_PROC)(NPC_HARVEST_NPC0_ACTOR* actor, GAME_PLAY* play);

typedef struct npc_harvest_npc0_actor_s {
    NPC_ACTOR actor;
    int _994;
    int _998;
    int _99C;
    aHT0_PROC _9A0;
    int _9A4;
    u8 _9A8;
} NPC_HARVEST_NPC0_ACTOR;

static void aHT0_actor_ct(ACTOR* actorx, GAME* game);
static void aHT0_actor_dt(ACTOR* actorx, GAME* game);
static void aHT0_actor_init(ACTOR* actorx, GAME* game);
static void aHT0_actor_save(ACTOR* actorx, GAME* game);
static void aHT0_actor_move(ACTOR* actorx, GAME* game);
static void aHT0_actor_draw(ACTOR* actorx, GAME* game);
static BOOL aHT0_talk_init(ACTOR* actorx, GAME* game);
static BOOL aHT0_talk_end_chk(ACTOR* actorx, GAME* game);
static void aHT0_schedule_proc(NPC_ACTOR*, GAME_PLAY*, int);
static void aHT0_talk_request(ACTOR* actorx, GAME* game);
static void aHT0_change_talk_proc(NPC_HARVEST_NPC0_ACTOR*, int);

// clang-format off
ACTOR_PROFILE Harvest_Npc0_Profile = {
    mAc_PROFILE_HARVEST_NPC0,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_HARVEST_NPC0_ACTOR),
    aHT0_actor_ct,
    aHT0_actor_dt,
    aHT0_actor_init,
    mActor_NONE_PROC1,
    aHT0_actor_save
};
// clang-format on

static int aHT0_GetMyIdx(NPC_HARVEST_NPC0_ACTOR* actor) {
    return (actor->actor.actor_class.npc_id - SP_NPC_EV_HARVEST_0) & 3;
}

static s16 aHT0_GetDefaultAngle(NPC_HARVEST_NPC0_ACTOR* actor) {
    static s16 first_angle[] = {
        DEG2SHORT_ANGLE2(45),
        DEG2SHORT_ANGLE2(270),
        DEG2SHORT_ANGLE2(315),
        DEG2SHORT_ANGLE2(90),
    };
    return first_angle[aHT0_GetMyIdx(actor)];
}

static void aHT0_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        aHT0_actor_move,
        aHT0_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        aHT0_talk_request,
        aHT0_talk_init,
        aHT0_talk_end_chk
    };
    // clang-format on

    NPC_HARVEST_NPC0_ACTOR* actor = (NPC_HARVEST_NPC0_ACTOR*)actorx;
    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        actor->actor.schedule.schedule_proc = aHT0_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }
}

static void aHT0_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aHT0_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aHT0_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aHT0_set_animation(ACTOR* actorx, int index) {
    static int animeSeqNo[] = { 72, 74, 73, 1 };
    NPC_CLIP->animation_init_proc(actorx, animeSeqNo[index], FALSE);
}

static void aHT0_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

static void aHT0_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../../actor/npc/ac_harvest_npc0.c_inc"
