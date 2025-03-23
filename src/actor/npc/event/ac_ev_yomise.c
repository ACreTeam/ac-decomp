#include "ac_ev_yomise.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_string.h"
#include "m_msg.h"
#include "m_font.h"
#include "libultra/libultra.h"

enum {
    aEYMS_TALK_ADD_ACTION,
    aEYMS_TALK_SELECT,
    aEYMS_TALK_SELECT2,
    aEYMS_TALK_FRUIT,
    aEYMS_TALK_END,
    aEYMS_TALK_GIVE,

    aEYMS_TALK_NUM
};

static void aEYMS_actor_ct(ACTOR* actorx, GAME* game);
static void aEYMS_actor_dt(ACTOR* actorx, GAME* game);
static void aEYMS_actor_move(ACTOR* actorx, GAME* game);
static void aEYMS_actor_draw(ACTOR* actorx, GAME* game);
static void aEYMS_actor_init(ACTOR* actorx, GAME* game);
static void aEYMS_actor_save(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Ev_Yomise_Profile = {
    // clang-format off
    mAc_PROFILE_EV_YOMISE,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_EV_YOMISE,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EV_YOMISE_ACTOR),
    aEYMS_actor_ct,
    aEYMS_actor_dt,
    aEYMS_actor_init,
    mActor_NONE_PROC1,
    aEYMS_actor_save,
    // clang-format on
};

static void aEYMS_talk_request(ACTOR* actorx, GAME* game);
static int aEYMS_talk_init(ACTOR* actorx, GAME* game);
static int aEYMS_talk_end_chk(ACTOR* actorx, GAME* game);

static void aEYMS_setupAction(EV_YOMISE_ACTOR* yomise, int action);

static void yomise_save_area_ct(void);

static void aEYMS_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        // clang-format off
        aEYMS_actor_move,
        aEYMS_actor_draw,
        aNPC_CT_SCHED_TYPE_STAND,
        aEYMS_talk_request,
        aEYMS_talk_init,
        aEYMS_talk_end_chk,
        0
        // clang-format on
    };

    EV_YOMISE_ACTOR* yomise = (EV_YOMISE_ACTOR*)actorx;

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        yomise->npc_class.draw.main_animation.keyframe.morph_counter = 0.0f;
        yomise->npc_class.condition_info.hide_flg = FALSE;
        yomise->npc_class.palActorIgnoreTimer = -1;
        actorx->status_data.weight = MASSTYPE_IMMOVABLE;

        mEv_check_status(mEv_EVENT_FIREWORKS_SHOW, mEv_STATUS_SHOW); // @cleanup - not needed
        yomise->npc_class.collision.check_kind = aNPC_BG_CHECK_TYPE_NONE;
        actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, 0.0f);
        actorx->position_speed.y = 0.0f;
        actorx->gravity = 0.0f;
        actorx->max_velocity_y = 0.0f;
        yomise_save_area_ct();
        aEYMS_setupAction(yomise, aEYMS_TALK_END);
        yomise->dst_pos[1] = actorx->world.position.z + 50.0f;

        if (actorx->npc_id == SP_NPC_EV_YOMISE) {
            yomise->dst_pos[0] = actorx->world.position.x + 50.0f;
        } else {
            yomise->dst_pos[0] = actorx->world.position.x - 50.0f;
        }

        NPC_CLIP->set_dst_pos_proc((NPC_ACTOR*)yomise, yomise->dst_pos[0], yomise->dst_pos[1]);
    }
}

static void aEYMS_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aEYMS_actor_dt(ACTOR* actorx, GAME* game) {
    if (mEv_check_status(mEv_EVENT_FIREWORKS_SHOW, mEv_STATUS_SHOW)) {
        mEv_actor_dying_message(mEv_EVENT_FIREWORKS_SHOW, actorx);
    }
    
    NPC_CLIP->dt_proc(actorx, game);
}

static void aEYMS_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aEYMS_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/event/ac_ev_yomise_move.c_inc"
