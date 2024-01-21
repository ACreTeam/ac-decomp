#include "ac_ev_kabuPeddler.h"

#include "m_common_data.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_player_lib.h"
#include "m_play.h"

enum {
    aEKPD_ACTION_TALK_END_WAIT,
    aEKPD_ACTION_SELL_CHECK,
    aEKPD_ACTION_SELL_CHECK_AFTER,
    aEKPD_ACTION_SELL_CHECK2,
    aEKPD_ACTION_SELL_CEHCK_AFTER2,
    aEKPD_ACTION_MONEY_GET_DEMO_START_WAIT,
    aEKPD_ACTION_MONEY_GET_DEMO_END_WAIT,
    aEKPD_ACTION_KABU_TRANS_DEMO_START_WAIT,

    aEKPD_ACTION_NUM
};

static void aEKPD_actor_ct(ACTOR* actorx, GAME* game);
static void aEKPD_actor_dt(ACTOR* actorx, GAME* game);
static void aEKPD_actor_draw(ACTOR* actorx, GAME* game);
static void aEKPD_actor_move(ACTOR* actorx, GAME* game);
static void aEKPD_actor_save(ACTOR* actorx, GAME* game);
static void aEKPD_actor_init(ACTOR* actorx, GAME* game);

ACTOR_PROFILE Ev_KabuPeddler_Profile = {
    mAc_PROFILE_EV_KABUPEDDLER,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_KABUPEDDLER,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EV_KABUPEDDLER_ACTOR),
    &aEKPD_actor_ct,
    &aEKPD_actor_dt,
    &aEKPD_actor_init,
    mActor_NONE_PROC1,
    &aEKPD_actor_save
};

static void aEKPD_setupAction(EV_KABUPEDDLER_ACTOR* kabuPeddler, GAME_PLAY* play, int talk_act);
static void aEKPD_talk_request(ACTOR*, GAME*);
static int aEKPD_talk_init(ACTOR*, GAME*);
static int aEKPD_talk_end_chk(ACTOR*, GAME*);

static void aEKPD_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        &aEKPD_actor_move,
        &aEKPD_actor_draw,
        3,
        &aEKPD_talk_request,
        &aEKPD_talk_init,
        &aEKPD_talk_end_chk,
        0
    };

    EV_KABUPEDDLER_ACTOR* kabuPeddler = (EV_KABUPEDDLER_ACTOR*)actorx;

    if ((*Common_Get(clip).npc_clip->birth_check_proc)(actorx, game) == TRUE) {
        (*Common_Get(clip).npc_clip->ct_proc)(actorx, game, &ct_data);
        kabuPeddler->setup_talk_proc = &aEKPD_setupAction;
    }
}

static void aEKPD_actor_save(ACTOR* actorx, GAME* game) {
    (*Common_Get(clip).npc_clip->save_proc)(actorx, game);
}

static void aEKPD_actor_dt(ACTOR* actorx, GAME* game) {
    (*Common_Get(clip).npc_clip->dt_proc)(actorx, game);
    mEv_actor_dying_message(mEv_EVENT_KABU_PEDDLER, actorx);
}

static void aEKPD_actor_init(ACTOR* actorx, GAME* game) {
    (*Common_Get(clip).npc_clip->init_proc)(actorx, game);
}

static void aEKPD_actor_draw(ACTOR* actorx, GAME* game) {
    (*Common_Get(clip).npc_clip->draw_proc)(actorx, game);
}

#include "../src/ac_ev_kabuPeddler_move.c_inc"
