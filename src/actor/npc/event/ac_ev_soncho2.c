#include "ac_ev_soncho2.h"
#include "m_common_data.h"
#include "m_string.h"
#include "m_msg.h"
#include "m_private.h"
#include "m_demo.h"
#include "m_soncho.h"
#include "m_calendar.h"
#include "m_play.h"
#include "m_player.h"
#include "m_player_lib.h"
#include "libultra/libultra.h"
#include "m_event_map_npc.h"
#include "ac_tokyoso_control.h"

static int aES2_change_talk_proc(ACTOR* actorx, u8 talk_proc);
static void aES2_setup_think_proc(NPC_SONCHO2* soncho, GAME_PLAY* play, u8 think_proc);
static void aES2_schedule_proc(NPC_ACTOR* npc, GAME_PLAY* play, int schedule);

static void aES2_actor_ct(ACTOR* actor, GAME* game);
static void aES2_actor_dt(ACTOR* actor, GAME* game);
static void aES2_actor_init(ACTOR* actor, GAME* game);
static void aES2_actor_save(ACTOR* actor, GAME* game);
static void aES2_actor_move(ACTOR* actor, GAME* game);
static void aES2_actor_draw(ACTOR* actor, GAME* game);
static int aES2_talk_init(ACTOR* actorx, GAME* game);
static int aES2_talk_end_chk(NPC_ACTOR* nactorx, GAME* game);

// clang-format off
ACTOR_PROFILE Ev_Soncho2_Profile = {
    mAc_PROFILE_EV_SONCHO2,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_EV_SONCHO2,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_SONCHO2),
    &aES2_actor_ct,
    &aES2_actor_dt,
    &aES2_actor_init,
    mActor_NONE_PROC1,
    &aES2_actor_save,
};
// clang-format on

static void aES2_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        &aES2_actor_move,
        &aES2_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        mActor_NONE_PROC1,
        &aES2_talk_init,
        (aNPC_TALK_END_CHECK_PROC)&aES2_talk_end_chk,
        0,
    };
    NPC_SONCHO2* soncho = (NPC_SONCHO2*)actorx;
    if (CLIP(npc_clip)->birth_check_proc(actorx, game) == TRUE) {
        ACTOR* player = (ACTOR*)GET_PLAYER_ACTOR_GAME(game);
        soncho->npc_class.schedule.schedule_proc = aES2_schedule_proc;
        CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
        soncho->npc_class.palActorIgnoreTimer = -1;
        soncho->npc_class.draw.sub_anim_type = aNPC_SUB_ANIM_TUE;
        soncho->_9ac = FALSE;
        soncho->melody_inst = 0;
        CLIP(npc_clip)->set_dst_pos_proc((NPC_ACTOR*)actorx, player->world.position.x, player->world.position.z);
        actorx->cull_width = 1350.0f;
        soncho->year = Common_Get(time).rtc_time.year;
        soncho->month = Common_Get(time).rtc_time.month;
        soncho->day = Common_Get(time).rtc_time.day;
        mCD_calendar_check_delete(-1, soncho->year, soncho->month, soncho->day);
    }
}

static void aES2_actor_save(ACTOR* actor, GAME* game) {
    mNpc_RenewalSetNpc(actor);
}

static void aES2_actor_dt(ACTOR* actor, GAME* game) {
    CLIP(npc_clip)->dt_proc(actor, game);
    mSC_delete_soncho(actor, (GAME_PLAY*)game);
}

static void aES2_actor_init(ACTOR* actor, GAME* game) {
    CLIP(npc_clip)->init_proc(actor, game);
}

static int aES2_set_request_act(NPC_SONCHO2* soncho, u8 priority, int idx, int type, int obj, int x, int z) {
    u16 arg_data[aNPC_REQUEST_ARG_NUM];
    int res = FALSE;

    if (priority >= soncho->npc_class.request.act_priority) {
        bzero(arg_data, sizeof(arg_data));
        arg_data[0] = obj;
        arg_data[2] = x;
        arg_data[3] = z;
        soncho->npc_class.request.act_priority = priority;
        soncho->npc_class.request.act_idx = idx;
        soncho->npc_class.request.act_type = type;
        mem_copy((u8*)soncho->npc_class.request.act_args, (u8*)arg_data, sizeof(arg_data));
        res = TRUE;
    }

    return res;
}

static void aES2_actor_move(ACTOR* actor, GAME* game) {
    CLIP(npc_clip)->move_proc(actor, game);
}

static void aES2_actor_draw(ACTOR* actor, GAME* game) {
    CLIP(npc_clip)->draw_proc(actor, game);
}

#include "src/actor/npc/event/ac_ev_soncho2_talk.c_inc"
#include "src/actor/npc/event/ac_ev_soncho2_think.c_inc"
