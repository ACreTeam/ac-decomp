#include "ac_present_demo.h"

#include "libultra/libultra.h"
#include "m_common_data.h"
#include "m_soncho.h"
#include "m_player_lib.h"

static void aPRD_actor_ct(ACTOR* actorx, GAME* game);
static void aPRD_actor_dt(ACTOR* actorx, GAME* game);
static void aPRD_actor_move(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Present_Demo_Profile = {
    mAc_PROFILE_PRESENT_DEMO,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(PRESENT_DEMO_ACTOR),
    aPRD_actor_ct,
    aPRD_actor_dt,
    aPRD_actor_move,
    mActor_NONE_PROC1,
    NULL,
};
// clang-format on

static mDemo_Clip_c aPRD_clip;

static void aPRD_setupAction(PRESENT_DEMO_ACTOR* present_demo, GAME* game, int action);

static void aPRD_actor_ct(ACTOR* actorx, GAME* game) {
    PRESENT_DEMO_ACTOR* actor = (PRESENT_DEMO_ACTOR*)actorx;
    
    CLIP(demo_clip2) = &aPRD_clip;
    bzero(CLIP(demo_clip2), sizeof(aPRD_clip));
    CLIP(demo_clip2)->demo_class = actorx;
    CLIP(demo_clip2)->type = mDemo_CLIP_TYPE_PRESENT_DEMO;
    aPRD_setupAction(actor, game, aPRD_ACTION_FIRST_SET);
}

static void aPRD_actor_dt(ACTOR* actorx, GAME* game) {
    if (CLIP(demo_clip2) != NULL) {
        CLIP(demo_clip2) = NULL;
    }
}

#include "../src/actor/ac_present_demo_move.c_inc"
