#include "ac_ev_artist.h"

#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_msg.h"
#include "libultra/libultra.h"

enum {
    aEART_ACTION_SAY_HUNGRY,
    aEART_ACTION_TALK_END_WAIT,
    aEART_ACTION_MENU_OPEN_WAIT,
    aEART_ACTION_MENU_CLOSE_WAIT,
    aEART_ACTION_MSG_WIN_OPEN_WAIT,
    aEART_ACTION_DEMO_START_WAIT,
    aEART_ACTION_REFUSE_DEMO_START_WAIT,
    aEART_ACTION_REFUSE_DEMO_END_WAIT,

    aEART_ACTION_NUM
};

enum {
    aEART_ITEM_TYPE_FISH,
    aEART_ITEM_TYPE_FOOD,
    aEART_ITEM_TYPE_TOOL,
    aEART_ITEM_TYPE_OTHER,

    aEART_ITEM_TYPE_NUM
};

static void aEART_actor_ct(ACTOR* actorx, GAME* game);
static void aEART_actor_dt(ACTOR* actorx, GAME* game);
static void aEART_actor_move(ACTOR* actorx, GAME* game);
static void aEART_actor_draw(ACTOR* actorx, GAME* game);
static void aEART_actor_init(ACTOR* actorx, GAME* game);
static void aEART_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Ev_Artist_Profile = {
    mAc_PROFILE_EV_ARTIST,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_ARTIST,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EV_ARTIST_ACTOR),
    aEART_actor_ct,
    aEART_actor_dt,
    aEART_actor_init,
    mActor_NONE_PROC1,
    aEART_actor_save,
};
// clang-format on

static void aEART_talk_request(ACTOR* actorx, GAME* game);
static int aEART_talk_init(ACTOR* actorx, GAME* game);
static int aEART_talk_end_chk(ACTOR* actorx, GAME* game);

static void aEART_setupAction(EV_ARTIST_ACTOR* artist, GAME_PLAY* play, int action);

static void aEART_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        // clang-format off
        aEART_actor_move,
        aEART_actor_draw,
        aNPC_CT_SCHED_TYPE_WANDER,
        aEART_talk_request,
        aEART_talk_init,
        aEART_talk_end_chk,
        0,
        // clang-format on
    };

    if (CLIP(npc_clip)->birth_check_proc(actorx, game) == TRUE) {
        EV_ARTIST_ACTOR* artist = (EV_ARTIST_ACTOR*)actorx;
        
        CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
        artist->setupAction_proc = aEART_setupAction;
    }
}

static void aEART_actor_save(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->save_proc(actorx, game);
}

static void aEART_actor_dt(ACTOR* actorx, GAME* game) {
    EV_ARTIST_ACTOR* artist = (EV_ARTIST_ACTOR*)actorx;

    CLIP(npc_clip)->dt_proc(actorx, game);
    mEv_actor_dying_message(mEv_EVENT_ARTIST, actorx);

    {
        mEv_artist_c* ev_save_p = &Save_Get(event_save_data).special.event.artist;

        if (ev_save_p->used > mEv_ARTIST_ENTRY_SAVE_NUM) {
            mEv_special_event_soldout(mEv_EVENT_ARTIST);
        }
    }
}

static void aEART_actor_init(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->init_proc(actorx, game);
}

static void aEART_actor_draw(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->draw_proc(actorx, game);
}

#include "../src/actor/npc/event/ac_ev_artist_move.c_inc"
