#include "ac_ev_miko.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_string.h"
#include "m_handbill.h"
#include "m_msg.h"
#include "libultra/libultra.h"

enum {
    aEMK_TALK_END_WAIT,
    aEMK_TALK_SELECT,
    aEMK_TALK_OMIKUJI,
    aEMK_TALK_GIVE,

    aEMK_TALK_NUM
};

enum {
    aEMK_OMIKUJI_NORMAL,
    aEMK_OMIKUJI_BAD,
    aEMK_OMIKUJI_MONEY,
    aEMK_OMIKUJI_GOODS,

    aEMK_OMIKUJI_NUM
};

static void aEMK_actor_ct(ACTOR* actorx, GAME* game);
static void aEMK_actor_dt(ACTOR* actorx, GAME* game);
static void aEMK_actor_move(ACTOR* actorx, GAME* game);
static void aEMK_actor_draw(ACTOR* actorx, GAME* game);
static void aEMK_actor_init(ACTOR* actorx, GAME* game);
static void aEMK_actor_save(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Ev_Miko_Profile = {
    // clang-format off
    mAc_PROFILE_EV_MIKO,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    SP_NPC_EV_MIKO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EV_MIKO_ACTOR),
    aEMK_actor_ct,
    aEMK_actor_dt,
    aEMK_actor_init,
    mActor_NONE_PROC1,
    aEMK_actor_save,
    // clang-format on
};

static void aEMK_talk_request(ACTOR* actorx, GAME* game);
static int aEMK_talk_init(ACTOR* actorx, GAME* game);
static int aEMK_talk_end_chk(ACTOR* actorx, GAME* game);

static void aEMK_setupAction(EV_MIKO_ACTOR* miko, GAME_PLAY* play, int action);

static void aEMK_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        // clang-format off
        aEMK_actor_move,
        aEMK_actor_draw,
        aNPC_CT_SCHED_TYPE_STAND,
        aEMK_talk_request,
        aEMK_talk_init,
        aEMK_talk_end_chk,
        0
        // clang-format on
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        EV_MIKO_ACTOR* miko = (EV_MIKO_ACTOR*)actorx;
        
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        miko->npc_class.condition_info.hide_flg = FALSE;
        miko->npc_class.palActorIgnoreTimer = -1;
        actorx->status_data.weight = MASSTYPE_IMMOVABLE;
        miko->npc_class.collision.check_kind = aNPC_BG_CHECK_TYPE_NONE;
        actorx->world.position.y = mCoBG_GetBgY_OnlyCenter_FromWpos2(actorx->world.position, 0.0f);
        actorx->position_speed.y = 0.0f;
        actorx->gravity = 0.0f;
        actorx->max_velocity_y = 0.0f;
        actorx->talk_distance = 78.0f;

        NPC_CLIP->set_dst_pos_proc((NPC_ACTOR*)miko, actorx->world.position.x + 10.0f, actorx->world.position.z + 10.0f);
    }
}

static void aEMK_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aEMK_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
    mEv_actor_dying_message(mEv_EVENT_NEW_YEARS_DAY, actorx);
}

static void aEMK_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aEMK_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/event/ac_ev_miko_move.c_inc"
