#include "ac_npc_sendo.h"

#include "m_common_data.h"
#include "ac_boat_demo.h"
#include "sys_matrix.h"
#include "m_msg.h"
#include "libultra/libultra.h"
#include "GBA2/gba2.h"
#include "m_ledit_ovl.h"

static void aSEN_actor_ct(ACTOR* actorx, GAME* game);
static void aSEN_actor_dt(ACTOR* actorx, GAME* game);
static void aSEN_actor_init(ACTOR* actorx, GAME* game);
static void aSEN_actor_move(ACTOR* actorx, GAME* game);
static void aSEN_actor_draw(ACTOR* actorx, GAME* game);
static void aSEN_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Sendo_Profile = {
    mAc_PROFILE_NPC_SENDO,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_SENDO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_SENDO_ACTOR),
    aSEN_actor_ct,
    aSEN_actor_dt,
    aSEN_actor_init,
    mActor_NONE_PROC1,
    aSEN_actor_save,
};
// clang-format on

static int aSEN_talk_init(ACTOR*, GAME*);
static int aSEN_talk_end_chk(ACTOR*, GAME*);

static void aSEN_schedule_proc(NPC_ACTOR*, GAME_PLAY*, int);
static void aSEN_setup_think_proc(NPC_SENDO_ACTOR*, GAME_PLAY*, u8);

static MtxF aSEN_matrix;

static void aSEN_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        &aSEN_actor_move,
        &aSEN_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)&none_proc1,
        &aSEN_talk_init,
        &aSEN_talk_end_chk,
        0,
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_ACTOR* npc_actor = (NPC_ACTOR*)actorx;
        GAME_PLAY* play = (GAME_PLAY*)game;

        npc_actor->schedule.schedule_proc = &aSEN_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }
}

static void aSEN_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aSEN_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_SENDO_ACTOR* sendo = (NPC_SENDO_ACTOR*)actorx;
    BOAT_DEMO_ACTOR* boat_demo;

    NPC_CLIP->dt_proc(actorx, game);

    boat_demo = (BOAT_DEMO_ACTOR*)actorx->parent_actor;
    if (boat_demo != NULL && boat_demo->npc_sendo_actor == sendo) {
        boat_demo->npc_sendo_actor = NULL;
    }
}

static void aSEN_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aSEN_actor_draw(ACTOR* actorx, GAME* game) {
    Matrix_put(&aSEN_matrix);
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_sendo_move.c_inc"
