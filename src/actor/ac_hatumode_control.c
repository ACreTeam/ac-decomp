#include "ac_hatumode_control.h"

#include "m_common_data.h"
#include "ac_hatumode_npc0.h"
#include "m_msg.h"
#include "m_player_lib.h"
#include "ac_shrine.h"
#include "libultra/libultra.h"

static void aHTC_actor_ct(ACTOR* actorx, GAME* game);
static void aHTC_actor_dt(ACTOR* actorx, GAME* game);
static void aHTC_actor_move(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Hatumode_Control_Profile = {
    mAc_PROFILE_HATUMODE_CONTROL,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(HATUMODE_CONTROL_ACTOR),
    &aHTC_actor_ct,
    &aHTC_actor_dt,
    &aHTC_actor_move,
    mActor_NONE_PROC1,
    NULL,
};
// clang-format on

static void aHTC_setup_move_proc(HATUMODE_CONTROL_ACTOR* hatumode_control, s16 move_proc_idx);

#include "../src/actor/ac_hatumode_control_move.c_inc"
#include "../src/actor/ac_hatumode_clip_move.c_inc"
#include "../src/actor/ac_hatumode_clip_think.c_inc"

static void aHTC_clip_talk_info(ACTOR*, int);
static int aHTMD_clip_think_init(ACTOR*, GAME_PLAY*);
static int aHTMD_clip_set_start(ACTOR*);
static int aHTMD_clip_player_move(GAME_PLAY*, int);
static int aHTMD_clip_look_player(ACTOR*);


static void aHTC_actor_ct(ACTOR* actorx, GAME* game) {
    HATUMODE_CONTROL_ACTOR* hatumode_control = (HATUMODE_CONTROL_ACTOR*)actorx;

    hatumode_control->clip.talk_info_proc = &aHTC_clip_talk_info;
    hatumode_control->clip.think_init_proc = &aHTMD_clip_think_init;
    hatumode_control->clip.set_start_proc = &aHTMD_clip_set_start;
    hatumode_control->clip.player_move_proc = &aHTMD_clip_player_move;
    hatumode_control->clip.look_player_proc = &aHTMD_clip_look_player;
    CLIP(hatumode_clip) = &hatumode_control->clip;
    aHTC_setup_move_proc(hatumode_control, 0);
}

static void aHTC_actor_dt(ACTOR* actorx, GAME* game) {
    CLIP(hatumode_clip) = NULL;
    mEv_actor_dying_message(mEv_EVENT_NEW_YEARS_DAY, actorx);
}

static void aHTC_actor_move(ACTOR* actorx, GAME* game) {
    HATUMODE_CONTROL_ACTOR* hatumode_control = (HATUMODE_CONTROL_ACTOR*)actorx;

    (*hatumode_control->move_proc)(hatumode_control, (GAME_PLAY*)game);
}
