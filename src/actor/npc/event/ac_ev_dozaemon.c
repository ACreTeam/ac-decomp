#include "ac_ev_dozaemon.h"

#include "m_common_data.h"
#include "libultra/libultra.h"
#include "m_msg.h"
#include "m_player_lib.h"

enum {
    aEDZ_TALK_END_WAIT,
    aEDZ_TALK_STOP_PLAYER,
    aEDZ_TALK_OKIAGARU,
    aEDZ_TALK_GIVE,

    aEDZ_TALK_NUM
};

static void aEDZ_actor_ct(ACTOR* actorx, GAME* game);
static void aEDZ_actor_dt(ACTOR* actorx, GAME* game);
static void aEDZ_actor_move(ACTOR* actorx, GAME* game);
static void aEDZ_actor_init(ACTOR* actorx, GAME* game);
static void aEDZ_actor_draw(ACTOR* actorx, GAME* game);
static void aEDZ_actor_save(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Ev_Dozaemon_Profile = {
    mAc_PROFILE_EV_DOZAEMON,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_EV_DOZAEMON,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(DOZAEMON_ACTOR),
    aEDZ_actor_ct,
    aEDZ_actor_dt,
    aEDZ_actor_init,
    mActor_NONE_PROC1,
    aEDZ_actor_save,
};

static int aEDZ_talk_init(ACTOR* actorx, GAME* game);
static int aEDZ_talk_end_chk(ACTOR* actorx, GAME* game);

static int aEDZ_change_talk_proc(DOZAEMON_ACTOR* dozaemon, int talk_act);

static void aEDZ_setup_think_proc(DOZAEMON_ACTOR* dozaemon, GAME_PLAY* play, u8 think_idx);

static void aEDZ_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int sched_type);

static void aEDZ_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aEDZ_actor_move,
        aEDZ_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        mActor_NONE_PROC1,
        aEDZ_talk_init,
        aEDZ_talk_end_chk,
        0,
    };

    mEv_dozaemon_c* dozaemon_ev = (mEv_dozaemon_c*)mEv_get_save_area(mEv_EVENT_DOZAEMON, 13);

    if (CLIP(npc_clip)->birth_check_proc(actorx, game) == TRUE) {
        DOZAEMON_ACTOR* dozaemon = (DOZAEMON_ACTOR*)actorx;
        u32 attribute;
        f32 pos_z;
        f32 pos_x;

        dozaemon->npc_class.schedule.schedule_proc = aEDZ_schedule_proc;
        CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
        dozaemon->npc_class.palActorIgnoreTimer = -1;
        dozaemon->change_think = 0;
        dozaemon->melody_backup = 0;

        aNPC_SPNPC_BIT_SET(Common_Get(spnpc_first_talk_flags), aNPC_SPNPC_BIT_DOZAEMON);

        attribute = mCoBG_Wpos2BgAttribute_Original(actorx->world.position);
        pos_z = actorx->world.position.z - 10.0f;
        pos_x = actorx->world.position.x;

        if (attribute == mCoBG_ATTRIBUTE_25) {
            pos_x -= 10.0f;
        } else if (attribute == mCoBG_ATTRIBUTE_26) {
            pos_x += 10.0f;
        }

        CLIP(npc_clip)->set_dst_pos_proc(&dozaemon->npc_class, pos_x, pos_z);
        actorx->shape_info.rotation.y = dozaemon->npc_class.movement.mv_angl;
        actorx->world.angle.y = dozaemon->npc_class.movement.mv_angl;

        if (dozaemon_ev == NULL) {
            dozaemon_ev = (mEv_dozaemon_c*)mEv_reserve_save_area(mEv_EVENT_DOZAEMON, 13);
            dozaemon_ev->flags = 0;
        } else if ((dozaemon_ev->flags & aEDZ_SAVE_FLAG_WAKEUP) != 0) {
            Actor_delete(actorx);
        }

        if (actorx->mv_proc != NULL && Save_Get(event_save_common).dozaemon_completed == TRUE) {
            Actor_delete(actorx);
        }
    }
}

static void aEDZ_actor_save(ACTOR* actorx, GAME* game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aEDZ_actor_dt(ACTOR* actorx, GAME* game) {
    if (mEv_check_status(mEv_EVENT_DOZAEMON, mEv_STATUS_SHOW) != FALSE) {
        mEv_actor_dying_message(mEv_EVENT_DOZAEMON, actorx);
    }

    CLIP(npc_clip)->dt_proc(actorx, game);
}

static void aEDZ_actor_init(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->init_proc(actorx, game);
}

static int aEDZ_set_request_act(DOZAEMON_ACTOR* dozaemon, u8 prio, u8 act_idx, u8 act_type, u16 act_obj, s16 move_x, s16 move_z) {
    int ret = FALSE;

    if (prio >= dozaemon->npc_class.request.act_priority) {
        u16 arg_data[aNPC_REQUEST_ARG_NUM];

        bzero(arg_data, sizeof(arg_data));
        arg_data[0] = act_obj;
        arg_data[2] = move_x;
        arg_data[3] = move_z;
        dozaemon->npc_class.request.act_priority = prio;
        dozaemon->npc_class.request.act_idx = act_idx;
        dozaemon->npc_class.request.act_type = act_type;
        mem_copy((u8*)dozaemon->npc_class.request.act_args, (u8*)arg_data, sizeof(arg_data));
        ret = TRUE;
    }

    return ret;
}

static void aEDZ_actor_move(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->move_proc(actorx, game);
}

static void aEDZ_actor_draw(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->draw_proc(actorx, game);
}

#include "../src/actor/npc/event/ac_ev_dozaemon_move.c_inc"
#include "../src/actor/npc/event/ac_ev_dozaemon_schedule.c_inc"
