#include "ac_ev_broker.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_msg.h"

enum {
    aEBRK_ACTION_TALK_WAIT,
    aEBRK_ACTION_TURN,
    aEBRK_ACTION_ENTER,
    aEBRK_ACTION_HIDE,

    aEBRK_ACTION_NUM
};

static void aEBRK_actor_ct(ACTOR* actorx, GAME* game);
static void aEBRK_actor_dt(ACTOR* actorx, GAME* game);
static void aEBRK_actor_init(ACTOR* actorx, GAME* game);
static void aEBRK_actor_move(ACTOR* actorx, GAME* game);
static void aEBRK_actor_draw(ACTOR* actorx, GAME* game);
static void aEBRK_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Ev_Broker_Profile = {
    mAc_PROFILE_EV_BROKER,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    SP_NPC_BROKER,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EV_BROKER_ACTOR),
    &aEBRK_actor_ct,
    &aEBRK_actor_dt,
    &aEBRK_actor_init,
    mActor_NONE_PROC1,
    &aEBRK_actor_save,
};
// clang-format on

static void aEBRK_talk_request(ACTOR* actorx, GAME* game);
static int aEBRK_talk_init(ACTOR* actorx, GAME* game);
static int aEBRK_talk_end_chk(ACTOR* actorx, GAME* game);

static void aEBRK_schedule_proc(NPC_ACTOR* npc_actorx, GAME_PLAY* play, int sched_type);

static int aEBRK_get_sell_item_sum(void);
static int aEBRK_check_start_around(ACTOR* actorx, GAME* game);

static void aEBRK_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        &aEBRK_actor_move, &aEBRK_actor_draw, 5, &aEBRK_talk_request, &aEBRK_talk_init, &aEBRK_talk_end_chk,
    };

    EV_BROKER_ACTOR* broker = (EV_BROKER_ACTOR*)actorx;

    if (Common_Get(clip).npc_clip->birth_check_proc(actorx, game) == TRUE) {
        broker->npc_class.schedule.schedule_proc = &aEBRK_schedule_proc;
        Common_Get(clip).npc_clip->ct_proc(actorx, game, &ct_data);
        broker->npc_class.actor_class.status_data.weight = 254;

        if (aEBRK_get_sell_item_sum() == 0 || aEBRK_check_start_around(actorx, game) == FALSE) {
            broker->npc_class.talk_info.talk_request_proc = (aNPC_TALK_REQUEST_PROC)&none_proc1;
            broker->next_action = aEBRK_ACTION_HIDE;
        } else {
            int hide_npc = Common_Get(special_event_common).broker.hide_npc;

            broker->npc_class.condition_info.hide_request = hide_npc;
            if (hide_npc == TRUE) {
                broker->npc_class.talk_info.talk_request_proc = (aNPC_TALK_REQUEST_PROC)&none_proc1;
                broker->next_action = aEBRK_ACTION_HIDE;
            } else {
                broker->next_action = aEBRK_ACTION_TALK_WAIT;
            }
        }
    }
}

static void aEBRK_actor_save(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->save_proc(actorx, game);
}

static void aEBRK_actor_dt(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->dt_proc(actorx, game);
    Common_Get(special_event_common).broker.hide_npc = FALSE;
    mEv_actor_dying_message(mEv_EVENT_BROKER_SALE, actorx);
}

static void aEBRK_actor_init(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->init_proc(actorx, game);
}

static void aEBRK_set_animation(EV_BROKER_ACTOR* broker, int action) {
    static int animeSeqNo[] = {
        aNPC_ANIM_WAIT1,
        aNPC_ANIM_WALK1,
        aNPC_ANIM_WALK1,
        aNPC_ANIM_WAIT1,
    };

    Common_Get(clip).npc_clip->animation_init_proc(&broker->npc_class.actor_class, animeSeqNo[action], FALSE);
}

static void aEBRK_actor_draw(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->draw_proc(actorx, game);
}

#include "../src/ac_ev_broker_move.c_inc"
