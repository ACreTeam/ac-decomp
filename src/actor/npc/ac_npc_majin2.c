#include "ac_npc_majin2.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"
#include "ac_reset_demo.h"
#include "m_bgm.h"
#include "m_house.h"

enum {
    aMJN2_THINK_START_WAIT,
    aMJN2_THINK_START_WAIT_ST,
    aMJN2_THINK_CALL,
    aMJN2_THINK_WAIT,
    aMJN2_THINK_FORCE_CALL,
    aMJN2_THINK_FORCE_CALL_2,
    aMJN2_THINK_EXIT,

    aMJN2_THINK_NUM
};

enum {
    aMJN2_TALK_WAIT,
    aMJN2_TALK_END_WAIT,
    
    aMJN2_TALK_NUM
};

static void aMJN2_actor_ct(ACTOR* actorx, GAME* game);
static void aMJN2_actor_dt(ACTOR* actorx, GAME* game);
static void aMJN2_actor_move(ACTOR* actorx, GAME* game);
static void aMJN2_actor_draw(ACTOR* actorx, GAME* game);
static void aMJN2_actor_save(ACTOR* actorx, GAME* game);
static void aMJN2_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Majin2_Profile = {
    mAc_PROFILE_NPC_MAJIN2,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    SP_NPC_MAJIN2,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_MAJIN2_ACTOR),
    aMJN2_actor_ct,
    aMJN2_actor_dt,
    aMJN2_actor_init,
    mActor_NONE_PROC1,
    aMJN2_actor_save,
};
// clang-format on

static void aMJN2_force_talk_request(ACTOR* actorx, GAME* game);
static void aMJN2_norm_talk_request(ACTOR* actorx, GAME* game);
static int aMJN2_talk_init(ACTOR* actorx, GAME* game);
static int aMJN2_talk_end_chk(ACTOR* actorx, GAME* game);

static void aMJN2_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aMJN2_setup_think_proc(NPC_MAJIN2_ACTOR* actor, GAME_PLAY* play, int think_idx);
static void aMJN2_change_talk_proc(NPC_MAJIN2_ACTOR* actor, int talk_idx);

static void aMJN2_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aMJN2_actor_move,
        aMJN2_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aMJN2_talk_init,
        aMJN2_talk_end_chk,
        0,
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_MAJIN2_ACTOR* actor = (NPC_MAJIN2_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aMJN2_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }
}

static void aMJN2_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aMJN2_actor_dt(ACTOR* actorx, GAME* game) {
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

static void aMJN2_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aMJN2_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
    actorx->shape_info.draw_shadow = FALSE;
}

static void aMJN2_set_animation(NPC_MAJIN2_ACTOR* actor, int think_idx) {
    static s16 animeSeqNo[] = { aNPC_ANIM_WAIT_R1, aNPC_ANIM_WAIT_R1, aNPC_ANIM_WAIT_R1, aNPC_ANIM_WAIT_R1, aNPC_ANIM_WAIT_R1, aNPC_ANIM_WAIT_R1, aNPC_ANIM_GO_UG1};

    NPC_CLIP->animation_init_proc((ACTOR*)actor, animeSeqNo[think_idx], FALSE);
}

static void aMJN2_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_majin2_talk.c_inc"
#include "../src/actor/npc/ac_npc_majin2_schedule.c_inc"
