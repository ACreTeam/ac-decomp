#include "ac_npc_majin3.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"
#include "ac_reset_demo.h"
#include "m_bgm.h"
#include "m_house.h"
#include "m_ledit_ovl.h"

enum {
    aMJN3_THINK_START_WAIT,
    aMJN3_THINK_START_WAIT_ST,
    aMJN3_THINK_START_WAIT_ST2,
    aMJN3_THINK_CALL,
    aMJN3_THINK_EXIT,

    aMJN3_THINK_NUM
};

enum {
    aMJN3_TALK_MSG_WIN_CLOSE_WAIT,
    aMJN3_TALK_MENU_OPEN_WAIT,
    aMJN3_TALK_MENU_CLOSE_WAIT,
    aMJN3_TALK_MSG_WIN_OPEN_WAIT,
    aMJN3_TALK_END_WAIT,
    
    aMJN3_TALK_NUM
};

enum {
    aMJN3_WORD_GOOD, // user input the correct phrase
    aMJN3_WORD_NG, // user input a 'ng' word, special response
    aMJN3_WORD_WRONG, // user input the wrong phrase

    aMJN3_WORD_NUM
};

static void aMJN3_actor_ct(ACTOR* actorx, GAME* game);
static void aMJN3_actor_dt(ACTOR* actorx, GAME* game);
static void aMJN3_actor_move(ACTOR* actorx, GAME* game);
static void aMJN3_actor_draw(ACTOR* actorx, GAME* game);
static void aMJN3_actor_save(ACTOR* actorx, GAME* game);
static void aMJN3_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Majin3_Profile = {
    mAc_PROFILE_NPC_MAJIN3,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    SP_NPC_MAJIN3,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_MAJIN3_ACTOR),
    aMJN3_actor_ct,
    aMJN3_actor_dt,
    aMJN3_actor_init,
    mActor_NONE_PROC1,
    aMJN3_actor_save,
};
// clang-format on

static void aMJN3_force_talk_request(ACTOR* actorx, GAME* game);
static void aMJN3_norm_talk_request(ACTOR* actorx, GAME* game);
static int aMJN3_talk_init(ACTOR* actorx, GAME* game);
static int aMJN3_talk_end_chk(ACTOR* actorx, GAME* game);

static void aMJN3_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aMJN3_setup_think_proc(NPC_MAJIN3_ACTOR* actor, GAME_PLAY* play, int think_idx);
static void aMJN3_change_talk_proc(NPC_MAJIN3_ACTOR* actor, int talk_idx);

static void aMJN3_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aMJN3_actor_move,
        aMJN3_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aMJN3_talk_init,
        aMJN3_talk_end_chk,
        0,
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_MAJIN3_ACTOR* actor = (NPC_MAJIN3_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aMJN3_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
    }
}

static void aMJN3_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aMJN3_actor_dt(ACTOR* actorx, GAME* game) {
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

static void aMJN3_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aMJN3_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
    actorx->shape_info.draw_shadow = FALSE;
}

static void aMJN3_set_animation(NPC_MAJIN3_ACTOR* actor, int think_idx) {
    static s16 animeSeqNo[] = { aNPC_ANIM_WAIT1, aNPC_ANIM_WAIT1, aNPC_ANIM_WAIT1, aNPC_ANIM_APPEAR1, aNPC_ANIM_GO_UG1 };

    NPC_CLIP->animation_init_proc((ACTOR*)actor, animeSeqNo[think_idx], FALSE);
}

static void aMJN3_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_majin3_talk.c_inc"
#include "../src/actor/npc/ac_npc_majin3_schedule.c_inc"
