#include "ac_npc_police2.h"

#include "m_common_data.h"
#include "libultra/libultra.h"
#include "m_msg.h"
#include "m_font.h"
#include "m_string.h"
#include "m_player_lib.h"
#include "m_bgm.h"
#include "m_melody.h"

enum {
    aPOL2_ACT_GREET,
    aPOL2_ACT_WAIT,
    aPOL2_ACT_WALK_PL_SAME_ZONE,
    aPOL2_ACT_WALK_PL_OTHER_ZONE,
    aPOL2_ACT_RUN_PL_SAME_ZONE,
    aPOL2_ACT_RUN_PL_OTHER_ZONE,
    aPOL2_ACT_TURN,
    aPOL2_ACT_CHECK_ANSWER,
    aPOL2_ACT_TALK_END_WAIT,

    aPOL2_ACT_NUM
};

static void aPOL2_actor_ct(ACTOR* actorx, GAME* game);
static void aPOL2_actor_dt(ACTOR* actorx, GAME* game);
static void aPOL2_actor_move(ACTOR* actorx, GAME* game);
static void aPOL2_actor_draw(ACTOR* actorx, GAME* game);
static void aPOL2_actor_save(ACTOR* actorx, GAME* game);
static void aPOL2_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Police2_Profile = {
    mAc_PROFILE_NPC_POLICE2,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_POLICE2,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_POLICE2_ACTOR),
    aPOL2_actor_ct,
    aPOL2_actor_dt,
    aPOL2_actor_init,
    mActor_NONE_PROC1,
    aPOL2_actor_save,
};
// clang-format on

static void aPOL2_setupAction(NPC_POLICE2_ACTOR* actor, int action);

static void aPOL2_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aPOL2_actor_move,
        aPOL2_actor_draw,
        aNPC_CT_SCHED_TYPE_NONE,
        NULL,
        NULL,
        NULL,
        0,
    };

    NPC_POLICE2_ACTOR* actor = (NPC_POLICE2_ACTOR*)actorx;
    int action;
        
    CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
    actor->npc_class.condition_info.hide_flg = FALSE;
    actor->item_idx = -1;
    actorx->shape_info.draw_shadow = TRUE;
    actor->npc_class.draw.main_animation.keyframe.morph_counter = 0.0f;
    actorx->status_data.weight = 50;

    if (Common_Get(door_data).door_actor_name == RSV_NO) {
        action = aPOL2_ACT_WAIT;
        actor->npc_class.talk_info.melody_inst = 0;
    } else {
        action = aPOL2_ACT_GREET;
    }

    aPOL2_setupAction(actor, action);
}

static void aPOL2_actor_save(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->save_proc(actorx, game);
}

static void aPOL2_actor_dt(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->dt_proc(actorx, game);
}

static void aPOL2_actor_init(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->init_proc(actorx, game);
}

static void aPOL2_actor_draw(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_police2_move.c_inc"
