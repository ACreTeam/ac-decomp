#include "ac_normal_npc.h"

#include "m_common_data.h"

static void aNOR_actor_ct(ACTOR* actorx, GAME* game);
static void aNOR_actor_dt(ACTOR* actorx, GAME* game);
static void aNOR_actor_move(ACTOR* actorx, GAME* game);
static void aNOR_actor_draw(ACTOR* actorx, GAME* game);
static void aNOR_actor_init(ACTOR* actorx, GAME* game);
static void aNOR_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Normal_Npc_Profile = {
    mAc_PROFILE_NORMAL_NPC,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NORMAL_NPC_ACTOR),
    aNOR_actor_ct,
    aNOR_actor_dt,
    aNOR_actor_init,
    mActor_NONE_PROC1,
    aNOR_actor_save,
};
// clang-format on

static void aNOR_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        // clang-format off
        aNOR_actor_move,
        aNOR_actor_draw,
        aNPC_CT_SCHED_TYPE_NORMAL,
        NULL,
        NULL,
        NULL,
        0,
        // clang-format on
    };

    if (CLIP(npc_clip)->birth_check_proc(actorx, game) == TRUE) {
        CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
    }
}

static void aNOR_actor_dt(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->dt_proc(actorx, game);
}

static void aNOR_actor_save(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->save_proc(actorx, game);
}

static void aNOR_actor_init(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->init_proc(actorx, game);
}

static void aNOR_actor_move(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->move_proc(actorx, game);
}

static void aNOR_actor_draw(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->draw_proc(actorx, game);
}
