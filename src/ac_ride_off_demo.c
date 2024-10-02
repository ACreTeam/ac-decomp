#include "ac_ride_off_demo.h"
#include "libultra/libultra.h"
#include "m_bgm.h"
#include "m_common_data.h"
#include "m_demo.h"
#include "m_player_lib.h"

static void aROD_actor_ct(ACTOR* actor, GAME* game);
static void aROD_actor_dt(ACTOR* actor, GAME* game);
static void aROD_actor_move(ACTOR* actor, GAME* game);

mDemo_Clip_c aROD_clip;

ACTOR_PROFILE Ride_Off_Demo_Profile = {
    mAc_PROFILE_RIDE_OFF_DEMO,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(RIDE_OFF_DEMO_ACTOR),
    aROD_actor_ct,
    aROD_actor_dt,
    aROD_actor_move,
    NONE_ACTOR_PROC,
    NULL,
};

static void aROD_setupAction(ACTOR* actor, GAME* game, int action);

static void aROD_actor_ct(ACTOR* actor, GAME* game) {
    Common_Set(clip.demo_clip, &aROD_clip);
    bzero(&aROD_clip, sizeof(mDemo_Clip_c));
    Common_Set(clip.demo_clip->demo_class, actor);
    Common_Set(clip.demo_clip->type, mDemo_CLIP_TYPE_RIDE_OFF_DEMO);

    aROD_setupAction(actor, game, 0);
}

static void aROD_actor_dt(ACTOR* actor, GAME* game) {
    if (Common_Get(clip.demo_clip) != NULL) {
        Common_Set(clip.demo_clip, NULL);
    }
}

#include "../src/ac_ride_off_demo_move.c_inc"
