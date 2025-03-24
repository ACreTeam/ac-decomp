#include "ac_ev_broker2.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_msg.h"
#include "m_font.h"
#include "m_melody.h"
#include "m_bgm.h"

enum {
    aEBR2_ACTION_WAIT,
    aEBR2_ACTION_WALK_PL_SAME_ZONE,
    aEBR2_ACTION_WALK_PL_OTHER_ZONE,
    aEBR2_ACTION_RUN_PL_SAME_ZONE,
    aEBR2_ACTION_RUN_PL_OTHER_ZONE,
    aEBR2_ACTION_TURN,
    aEBR2_ACTION_TALK_END_WAIT,
    aEBR2_ACTION_SAY_HELLO,
    aEBR2_ACTION_SELL_CHECK,
    aEBR2_ACTION_SELL_AFTER,
    aEBR2_ACTION_GOODBYE_WAIT,
    aEBR2_ACTION_SAY_GOODBYE,
    aEBR2_ACTION_EXIT_WAIT,

    aEBR2_ACTION_NUM
};

enum {
    aEBR2_ZONE0,

    aEBR2_ZONE_NUM
};

enum {
    aEBR2_STATE_UNSOLD = (0 << 0),
    aEBR2_STATE_SOLD_CURRENT = (1 << 0),
    aEBR2_STATE_SOLD_OTHER = (1 << 1),

    aEBR2_STATE_NUM
};

static void aEBR2_actor_ct(ACTOR* actorx, GAME* game);
static void aEBR2_actor_dt(ACTOR* actorx, GAME* game);
static void aEBR2_actor_init(ACTOR* actorx, GAME* game);
static void aEBR2_actor_move(ACTOR* actorx, GAME* game);
static void aEBR2_actor_draw(ACTOR* actorx, GAME* game);
static void aEBR2_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Ev_Broker2_Profile = {
    mAc_PROFILE_EV_BROKER2,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_EV_BROKER2,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EV_BROKER2_ACTOR),
    &aEBR2_actor_ct,
    &aEBR2_actor_dt,
    &aEBR2_actor_init,
    mActor_NONE_PROC1,
    &aEBR2_actor_save,
};
// clang-format on

static void aEBR2_setupAction(EV_BROKER2_ACTOR* broker2, int action);

static void aEBR2_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        &aEBR2_actor_move,
        &aEBR2_actor_draw,
        aNPC_CT_SCHED_TYPE_NONE,
        NULL,
        NULL,
        NULL,
        0
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        EV_BROKER2_ACTOR* broker2 = (EV_BROKER2_ACTOR*)actorx;
        int action;
        
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        broker2->npc_class.condition_info.hide_flg = FALSE;
        broker2->item_idx = -1;
        actorx->shape_info.draw_shadow = TRUE;
        broker2->npc_class.draw.main_animation.keyframe.morph_counter = 0.0f;
        broker2->npc_class.actor_class.status_data.weight = 50;

        if (Common_Get(door_data).door_actor_name == RSV_NO) {
            action = aEBR2_ACTION_WAIT;
            broker2->npc_class.talk_info.melody_inst = 0;
        } else {
            action = aEBR2_ACTION_SAY_HELLO;
        }

        aEBR2_setupAction(broker2, action);
    }
}

static void aEBR2_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aEBR2_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
    Common_Get(special_event_common).broker.hide_npc = TRUE;
}

static void aEBR2_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aEBR2_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/event/ac_ev_broker2_move.c_inc"
