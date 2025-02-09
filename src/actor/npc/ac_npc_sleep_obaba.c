#include "ac_npc_sleep_obaba.h"

#include "m_common_data.h"

enum {
    aNSO_ACT_SLEEP,
    aNSO_ACT_CRAMP,

    aNSO_ACT_NUM
};

static void aNSO_actor_ct(ACTOR* actorx, GAME* game);
static void aNSO_actor_dt(ACTOR* actorx, GAME* game);
static void aNSO_actor_move(ACTOR* actorx, GAME* game);
static void aNSO_actor_draw(ACTOR* actorx, GAME* game);
static void aNSO_actor_save(ACTOR* actorx, GAME* game);
static void aNSO_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Sleep_Obaba_Profile = {
    mAc_PROFILE_NPC_SLEEP_OBABA,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_SLEEP_OBABA,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_SLEEP_OBABA_ACTOR),
    aNSO_actor_ct,
    aNSO_actor_dt,
    aNSO_actor_init,
    mActor_NONE_PROC1,
    aNSO_actor_save,
};
// clang-format on

static void aNSO_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int proc_type);
static void aNSO_setupAction(NPC_SLEEP_OBABA_ACTOR* actor, int action);

static void aNSO_actor_ct(ACTOR* actorx, GAME* game) {
    NPC_SLEEP_OBABA_ACTOR* actor = (NPC_SLEEP_OBABA_ACTOR*)actorx;
    static aNPC_ct_data_c ct_data = {
        aNSO_actor_move,
        aNSO_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        (aNPC_TALK_INIT_PROC)none_proc1,
        (aNPC_TALK_END_CHECK_PROC)none_proc1,
        1,
    };

    if (CLIP(npc_clip)->birth_check_proc(actorx, game) == TRUE) {
        NPC_SLEEP_OBABA_ACTOR* actor = (NPC_SLEEP_OBABA_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aNSO_schedule_proc;
        CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
        actorx->world.position.x -= 6.0f;
        actorx->world.position.z -= 24.0f;
    }
}

static void aNSO_actor_save(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->save_proc(actorx, game);
}

static void aNSO_actor_dt(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->dt_proc(actorx, game);
}

static void aNSO_actor_init(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->init_proc(actorx, game);
}

static void aNSO_actor_move(ACTOR* actorx, GAME* game) {
    NPC_SLEEP_OBABA_ACTOR* actor = (NPC_SLEEP_OBABA_ACTOR*)actorx;

    actor->npc_class.condition_info.demo_flg =
        aNPC_COND_DEMO_SKIP_ENTRANCE_CHECK | aNPC_COND_DEMO_SKIP_HEAD_LOOKAT | aNPC_COND_DEMO_SKIP_TALK_CHECK |
        aNPC_COND_DEMO_SKIP_FORWARD_CHECK | aNPC_COND_DEMO_SKIP_BGCHECK | aNPC_COND_DEMO_SKIP_OBJ_COL_CHECK |
        aNPC_COND_DEMO_SKIP_MOVE_Y | aNPC_COND_DEMO_SKIP_MOVE_CIRCLE_REV | aNPC_COND_DEMO_SKIP_MOVE_RANGE_CHECK;
    CLIP(npc_clip)->move_proc(actorx, game);
}

static void aNSO_actor_draw(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_sleep_obaba_animation.c_inc"
#include "../src/actor/npc/ac_npc_sleep_obaba_act.c_inc"
