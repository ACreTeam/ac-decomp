#include "ac_ev_pumpkin.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_msg.h"
#include "m_font.h"
#include "m_melody.h"
#include "m_bgm.h"

enum {
    aEPK_FIRST_CALL_TALK_PROC,
    aEPK_TRICK_OR_TREAT_TALK_PROC,
    aEPK_MENU_OPEN_WAIT_TALK_PROC,
    aEPK_MENU_CLOSE_WAIT_TALK_PROC,
    aEPK_GET_OTHER_ITEM_WAIT_TALK_PROC,
    aEPK_RECEIVE_TOOL_ITEM_START_WAIT_TALK_PROC,
    aEPK_RECEIVE_TOOL_ITEM_END_WAIT_TALK_PROC,
    aEPK_TRICK_TIMING_WAIT_TALK_PROC,
    aEPK_TRICK_CHG_CLOTH_TALK_PROC,
    aEPK_TRICK_CHG_CLOTH_END_WAIT_TALK_PROC,
    aEPK_GET_AME_WAIT_TALK_PROC,
    aEPK_GET_AME_TALK_PROC,
    aEPK_GIVE_A_PRESENT_DEMO_START_WAIT_TALK_PROC,
    aEPK_GIVE_A_PRESENT_DEMO_END_WAIT_TALK_PROC,
    aEPK_PL_DEMO_CODE_END_WAIT_TALK_PROC,
    aEPK_END_TALK,

    aEPK_TALK_NUM
};

enum {
    aEPK_TRICK_TYPE_CLOTH,
    aEPK_TRICK_TYPE_ITEM,

    aEPK_TRICK_TYPE_NUM
};

static void aEPK_actor_ct(ACTOR* actorx, GAME* game);
static void aEPK_actor_dt(ACTOR* actorx, GAME* game);
static void aEPK_actor_init(ACTOR* actorx, GAME* game);
static void aEPK_actor_move(ACTOR* actorx, GAME* game);
static void aEPK_actor_draw(ACTOR* actorx, GAME* game);
static void aEPK_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Ev_Pumpkin_Profile = {
    mAc_PROFILE_EV_PUMPKIN,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EV_PUMPKIN_ACTOR),
    &aEPK_actor_ct,
    &aEPK_actor_dt,
    &aEPK_actor_init,
    mActor_NONE_PROC1,
    &aEPK_actor_save,
};
// clang-format on

static void aEPK_talk_request(ACTOR* actorx, GAME* game);
static int aEPK_talk_init(ACTOR* actorx, GAME* game);
static int aEPK_talk_end_chk(ACTOR* actorx, GAME* game);

static void aEPK_change_talk_proc(EV_PUMPKIN_ACTOR* pumpkin, int talk_action);

static void aEPK_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        // clang-format off
        &aEPK_actor_move,
        &aEPK_actor_draw,
        aNPC_CT_SCHED_TYPE_WANDER,
        aEPK_talk_request,
        aEPK_talk_init,
        aEPK_talk_end_chk,
        0,
        // clang-format on
    };

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        EV_PUMPKIN_ACTOR* pumpkin = (EV_PUMPKIN_ACTOR*)actorx;
        aEv_pumpkin_common_c* common_p;

        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        pumpkin->npc_class.palActorIgnoreTimer = -1;
        
        common_p = (aEv_pumpkin_common_c*)mEv_get_common_area(mEv_EVENT_HALLOWEEN, 0);
        if (common_p == NULL) {
            common_p = (aEv_pumpkin_common_c*)mEv_reserve_common_area(mEv_EVENT_HALLOWEEN, 0);
        }
        pumpkin->common_p = common_p;
    }
}

static void aEPK_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aEPK_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
    mEv_actor_dying_message(mEv_EVENT_HALLOWEEN, actorx);
}

static void aEPK_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aEPK_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
}

static void aEPK_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/event/ac_ev_pumpkin_talk.c_inc"
