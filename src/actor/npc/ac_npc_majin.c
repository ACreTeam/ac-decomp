#include "ac_npc_majin.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"
#include "ac_reset_demo.h"
#include "m_bgm.h"
#include "m_house.h"

enum {
    aMJN_THINK_START_WAIT,
    aMJN_THINK_START_WAIT_ST,
    aMJN_THINK_CALL,
    aMJN_THINK_CALL_2,
    aMJN_THINK_CALL_3,
    aMJN_THINK_CALL_4,
    aMJN_THINK_CALL_5,
    aMJN_THINK_EXIT,

    aMJN_THINK_NUM
};

static void aMJN_actor_ct(ACTOR* actorx, GAME* game);
static void aMJN_actor_dt(ACTOR* actorx, GAME* game);
static void aMJN_actor_move(ACTOR* actorx, GAME* game);
static void aMJN_actor_draw(ACTOR* actorx, GAME* game);
static void aMJN_actor_save(ACTOR* actorx, GAME* game);
static void aMJN_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Majin_Profile = {
    mAc_PROFILE_NPC_MAJIN,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    SP_NPC_MAJIN,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_MAJIN_ACTOR),
    aMJN_actor_ct,
    aMJN_actor_dt,
    aMJN_actor_init,
    mActor_NONE_PROC1,
    aMJN_actor_save,
};
// clang-format on

static void aMJN_force_talk_request(ACTOR* actorx, GAME* game);
static void aMJN_norm_talk_request(ACTOR* actorx, GAME* game);
static int aMJN_talk_init(ACTOR* actorx, GAME* game);
static int aMJN_talk_end_chk(ACTOR* actorx, GAME* game);

static void aMJN_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aMJN_setup_think_proc(NPC_MAJIN_ACTOR* actor, GAME_PLAY* play, int think_idx);

static void aMJN_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aMJN_actor_move,
        aMJN_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aMJN_talk_init,
        aMJN_talk_end_chk,
        0,
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_MAJIN_ACTOR* actor = (NPC_MAJIN_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aMJN_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }
}

static void aMJN_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aMJN_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
    eEC_CLIP->effect_kill_proc(eEC_EFFECT_RESET_HOLE, RSV_NO);
    if (CLIP(demo_clip2) != NULL && CLIP(demo_clip2)->type == mDemo_CLIP_TYPE_RESET_DEMO) {
        ACTOR* demox = (ACTOR*)CLIP(demo_clip2)->demo_class;

        if (demox != NULL) {
            RESET_DEMO_ACTOR* reset_demo = (RESET_DEMO_ACTOR*)demox;

            reset_demo->reset_actor = NULL;
            reset_demo->request_light = FALSE;
        }
    }
}

static void aMJN_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aMJN_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
    actorx->shape_info.draw_shadow = FALSE;
}

static void aMJN_set_animation(NPC_MAJIN_ACTOR* actor, int think_idx) {
    static s16 animeSeqNo[] = { aNPC_ANIM_WAIT1, aNPC_ANIM_WAIT1, aNPC_ANIM_APPEAR1, aNPC_ANIM_APPEAR1, aNPC_ANIM_APPEAR1, aNPC_ANIM_APPEAR1, aNPC_ANIM_APPEAR1,  aNPC_ANIM_GO_UG1};

    NPC_CLIP->animation_init_proc((ACTOR*)actor, animeSeqNo[think_idx], FALSE);
}

static void aMJN_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_majin_talk.c_inc"
#include "../src/actor/npc/ac_npc_majin_schedule.c_inc"
