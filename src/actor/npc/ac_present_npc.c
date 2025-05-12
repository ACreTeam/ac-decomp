#include "ac_present_npc.h"

#include "m_common_data.h"
#include "ac_present_demo.h"
#include "libultra/libultra.h"
#include "m_msg.h"
#include "m_soncho.h"
#include "m_house.h"

enum {
    aPST_TALK_PRESENT_SEND_START_WAIT,
    aPST_TALK_PRESENT_SEND_END_WAIT,
    aPST_TALK_END_WAIT,

    aPST_TALK_NUM
};

enum {
    aPST_THINK_WAIT,
    aPST_THINK_TALK,
    aPST_THINK_EXIT_TURN,
    aPST_THINK_EXIT,

    aPST_THINK_NUM
};

static void aPST_actor_ct(ACTOR* actorx, GAME* game);
static void aPST_actor_draw(ACTOR* actorx, GAME* game);
static void aPST_actor_dt(ACTOR* actorx, GAME* game);
static void aPST_actor_init(ACTOR* actorx, GAME* game);
static void aPST_actor_move(ACTOR* actorx, GAME* game);
static void aPST_actor_save(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Present_Npc_Profile = {
    // clang-format off
    mAc_PROFILE_PRESENT_NPC,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(PRESENT_NPC_ACTOR),
    aPST_actor_ct,
    aPST_actor_dt,
    aPST_actor_init,
    mActor_NONE_PROC1,
    aPST_actor_save,
    // clang-format on
};

static int aPST_talk_end_chk(ACTOR* actorx, GAME* game);
static int aPST_talk_init(ACTOR* actorx, GAME* game);

static void aPST_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aPST_change_talk_proc(PRESENT_NPC_ACTOR* actor, int type);
static void aPST_setup_think_proc(PRESENT_NPC_ACTOR* actor, GAME_PLAY* play, int type);

static void aPST_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        // clang-format off
        aPST_actor_move,
        aPST_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        NULL,
        aPST_talk_init,
        aPST_talk_end_chk,
        0,
        // clang-format on
    };

    PRESENT_NPC_ACTOR* actor = (PRESENT_NPC_ACTOR*)actorx;

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        actor->npc_class.schedule.schedule_proc = aPST_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }
}

static void aPST_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);

    if (CLIP(demo_clip2) != NULL && CLIP(demo_clip2)->type == mDemo_CLIP_TYPE_PRESENT_DEMO) {
        ACTOR* demo_actorx = (ACTOR*)CLIP(demo_clip2)->demo_class;

        if (demo_actorx != NULL) {
            PRESENT_DEMO_ACTOR* present_demo = (PRESENT_DEMO_ACTOR*)demo_actorx;

            present_demo->world_actor = NULL;
        }
    }
}

static void aPST_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aPST_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aPST_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_present_npc_schedule.c_inc"
