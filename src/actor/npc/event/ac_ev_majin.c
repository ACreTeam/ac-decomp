#include "ac_ev_majin.h"

#include "m_common_data.h"
#include "m_name_table.h"
#include "m_demo.h"
#include "ac_groundhog_control.h"

enum {
    aEMJ_ACT_APPEAR,
    aEMJ_ACT_WAIT,
    aEMJ_ACT_RETIRE,

    aEMJ_ACT_NUM
};

static void aEMJ_actor_ct(ACTOR*, GAME*);
static void aEMJ_actor_dt(ACTOR*, GAME*);
static void aEMJ_actor_init(ACTOR*, GAME*);
static void aEMJ_actor_save(ACTOR*, GAME*);

ACTOR_PROFILE Ev_Majin_Profile = {
    // clang-format off
    mAc_PROFILE_EV_MAJIN,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    SP_NPC_EV_MAJIN,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EV_MAJIN_ACTOR),
    aEMJ_actor_ct,
    aEMJ_actor_dt,
    aEMJ_actor_init,
    mActor_NONE_PROC1,
    aEMJ_actor_save,
    // clang-format on
};

static void aEMJ_actor_move(ACTOR*, GAME*);
static void aEMJ_actor_draw(ACTOR*, GAME*);

static int aEMJ_talk_init(ACTOR*, GAME*);
static int aEMJ_talk_end_chk(ACTOR*, GAME*);
static void aEMJ_schedule_proc(NPC_ACTOR*, GAME_PLAY*, int);

static void aEMJ_actor_ct(ACTOR* actor, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        // clang-format off
        aEMJ_actor_move,
        aEMJ_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aEMJ_talk_init,
        aEMJ_talk_end_chk,
        0,
        // clang-format on
    };
    EV_MAJIN_ACTOR* majin = (EV_MAJIN_ACTOR*)actor;

    if (NPC_CLIP->birth_check_proc(actor, game) == TRUE) {
        majin->npc_class.schedule.schedule_proc = aEMJ_schedule_proc;
        NPC_CLIP->ct_proc(actor, game, &ct_data);
        majin->npc_class.head.lock_flag = TRUE;
        majin->npc_class.talk_info.default_turn_animation = aNPC_ANIM_WAIT_R1;
        majin->npc_class.talk_info.default_animation = aNPC_ANIM_WAIT_R1;
        majin->npc_class.talk_info.turn = aNPC_TALK_TURN_NONE;
    }
}

static void aEMJ_actor_save(ACTOR* actor, GAME* game) {
    NPC_CLIP->save_proc(actor, game);
}

static void aEMJ_actor_dt(ACTOR* actor, GAME* game) {
    if (CLIP(groundhog_control_clip) != NULL) {
        CLIP(groundhog_control_clip)->groundhog_npc_actor = NULL;
    }

    NPC_CLIP->dt_proc(actor, game);
    eEC_CLIP->effect_kill_proc(eEC_EFFECT_RESET_HOLE, RSV_NO);
}

static void aEMJ_actor_init(ACTOR* actor, GAME* game) {
    NPC_CLIP->init_proc(actor, game);
}

static void aEMJ_set_animation(EV_MAJIN_ACTOR* majin, int idx) {
    static s16 animeSeqNo[] = { aNPC_ANIM_APPEAR1, aNPC_ANIM_WAIT_R1, aNPC_ANIM_GO_UG1 };

    NPC_CLIP->animation_init_proc((ACTOR*)majin, animeSeqNo[idx], FALSE);
}

static void aEMJ_actor_move(ACTOR* actor, GAME* game) {
    NPC_CLIP->move_proc(actor, game);
    actor->shape_info.draw_shadow = FALSE;
}

static void aEMJ_actor_draw(ACTOR* actor, GAME* game) {
    NPC_CLIP->draw_proc(actor, game);
}

#include "../src/actor/npc/event/ac_ev_majin_move.c_inc"
