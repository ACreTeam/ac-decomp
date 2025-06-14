#include "ac_groundhog_npc0.h"

#include "ac_groundhog_control.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"

enum {
    aGH0_ACT_WAIT,
    aGH0_ACT_TURN,

    aGH0_ACT_NUM
};

static void aGH0_actor_ct(ACTOR* actorx, GAME* game);
static void aGH0_actor_dt(ACTOR* actorx, GAME* game);
static void aGH0_actor_move(ACTOR* actorx, GAME* game);
static void aGH0_actor_draw(ACTOR* actorx, GAME* game);
static void aGH0_actor_save(ACTOR* actorx, GAME* game);
static void aGH0_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Groundhog_Npc0_Profile = {
    mAc_PROFILE_GROUNDHOG_NPC0,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(GROUNDHOG_NPC0_ACTOR),
    aGH0_actor_ct,
    aGH0_actor_dt,
    aGH0_actor_init,
    mActor_NONE_PROC1,
    aGH0_actor_save,
};
// clang-format on

static void aGH0_force_talk_request(ACTOR* actorx, GAME* game);
static void aGH0_norm_talk_request(ACTOR* actorx, GAME* game);
static int aGH0_talk_init(ACTOR* actorx, GAME* game);
static int aGH0_talk_end_chk(ACTOR* actorx, GAME* game);

static void aGH0_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);

static void aGH0_setupAction(GROUNDHOG_NPC0_ACTOR* actor, int action);

static void aGH0_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aGH0_actor_move,
        aGH0_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        aGH0_norm_talk_request,
        aGH0_talk_init,
        aGH0_talk_end_chk,
        0,
    };
    f32 speed;

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        GROUNDHOG_NPC0_ACTOR* actor = (GROUNDHOG_NPC0_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aGH0_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        actor->npc_class.draw.anim_speed_type = aNPC_ANIM_SPEED_TYPE_FREE;

        speed = (RANDOM(3.0f) * 0.5f) / 2.0f;
        actor->npc_class.draw.frame_speed = speed + 0.4f;
    }
}

static void aGH0_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aGH0_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aGH0_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aGH0_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

#include "../src/actor/npc/ac_groundhog_npc0_anime.c_inc"
#include "../src/actor/npc/ac_groundhog_npc0_talk.c_inc"

static void aGH0_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
