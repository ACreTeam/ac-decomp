#include "ac_harvest_npc1.h"
#include "m_name_table.h"
#include "ac_npc.h"
#include "ac_npc_h.h"
#include "m_common_data.h"
#include "m_msg.h"
#include "m_soncho.h"
#include "ac_shrine.h"

typedef struct npc_harvest_npc1_actor_s NPC_HARVEST_NPC1_ACTOR;

typedef void (*aHT1_PROC)(NPC_HARVEST_NPC1_ACTOR* actor, GAME_PLAY* play);

typedef struct npc_harvest_npc1_actor_s {
    NPC_ACTOR actor;
    int _994;
    int _998;
    aHT1_PROC _99C;
} NPC_HARVEST_NPC1_ACTOR;

static void aHT1_actor_ct(ACTOR* actorx, GAME* game);
static void aHT1_actor_dt(ACTOR* actorx, GAME* game);
static void aHT1_actor_init(ACTOR* actorx, GAME* game);
static void aHT1_actor_save(ACTOR* actorx, GAME* game);
static void aHT1_actor_move(ACTOR* actorx, GAME* game);
static void aHT1_actor_draw(ACTOR* actorx, GAME* game);
static BOOL aHT1_talk_init(ACTOR* actorx, GAME* game);
static BOOL aHT1_talk_end_chk(ACTOR* actorx, GAME* game);
static void aHT1_schedule_proc(NPC_ACTOR*, GAME_PLAY*, int);
static void aHT1_talk_request(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Harvest_Npc1_Profile = {
    mAc_PROFILE_HARVEST_NPC1,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_HARVEST_NPC1_ACTOR),
    aHT1_actor_ct,
    aHT1_actor_dt,
    aHT1_actor_init,
    mActor_NONE_PROC1,
    aHT1_actor_save
};
// clang-format on

static void aHT1_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        aHT1_actor_move,
        aHT1_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        aHT1_talk_request,
        aHT1_talk_init,
        aHT1_talk_end_chk
    };
    // clang-format on

    NPC_HARVEST_NPC1_ACTOR* actor = (NPC_HARVEST_NPC1_ACTOR*)actorx;
    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        actor->actor.actor_class.world.position.x += 20.f;
        actor->actor.schedule.schedule_proc = aHT1_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }
}

static void aHT1_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aHT1_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aHT1_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aHT1_set_animation(ACTOR* actorx, int index) {
    static int animeSeqNo[] = { 5, 1 };
    NPC_CLIP->animation_init_proc(actorx, animeSeqNo[index], FALSE);
}

static void aHT1_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

static s16 aHT1_GetDefaultAngle() {
    return 0;
}

static void aHT1_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../../actor/npc/ac_harvest_npc1.c_inc"
