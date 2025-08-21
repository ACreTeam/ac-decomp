#include "ac_ev_santa.h"

#include "libultra/libultra.h"
#include "m_common_data.h"
#include "m_msg.h"
#include "m_play.h"

enum {
    aESNT_ACTION_TALK_END_WAIT,
    aESNT_ACTION_CHK_WISH_1ST,
    aESNT_ACTION_CHK_WISH_2ND,
    aESNT_ACTION_CHK_WISH_FINAL,
    aESNT_ACTION_CHK_WISH_MORE,
    aESNT_ACTION_MOTION_START_WAIT,
    aESNT_ACTION_MOTION_END_WAIT,

    aESNT_ACTION_NUM
};

enum {
    aESNT_WISH_FTR,
    aESNT_WISH_CLOTH,
    aESNT_WISH_WALL,
    aESNT_WISH_CARPET,

    aESNT_WISH_NUM
};

#define aESNT_TALK_TALK_SAME_PLAYER_NUM 3
#define aESNT_TALK_TALK_OTHER_PLAYER_NUM 3
#define aESNT_TALK_FINAL_PRESENT_NUM 1
#define aESNT_TALK_FINAL_NO_PRESENT_NUM 1
#define aESNT_TALK_SAME_BLOCK_NUM 3
#define aESNT_TALK_HELLO_NUM 1
#define aESNT_TALK_CHK_1ST_NUM 1
#define aESNT_TALK_CHK_2ND_NUM 1
#define aESNT_TALK_CHK_FINAL_NUM aESNT_WISH_NUM
#define aESNT_TALK_ALMOST_RECOGNIZE_NUM 1
#define aESNT_TALK_FINAL_PRESENT2_NUM 1
#define aESNT_TALK_FINAL_NO_PRESENT2_NUM 1
#define aESNT_TALK_NO_MORE_PRESENTS_NUM 3

enum {
    aESNT_TALK_TALK_SAME_PLAYER,
    aESNT_TALK_TALK_OTHER_PLAYER = aESNT_TALK_TALK_SAME_PLAYER + aESNT_TALK_TALK_SAME_PLAYER_NUM,
    aESNT_TALK_FINAL_PRESENT = aESNT_TALK_TALK_OTHER_PLAYER + aESNT_TALK_TALK_OTHER_PLAYER_NUM,
    aESNT_TALK_FINAL_NO_PRESENT = aESNT_TALK_FINAL_PRESENT + aESNT_TALK_FINAL_PRESENT_NUM,
    aESNT_TALK_SAME_BLOCK = aESNT_TALK_FINAL_NO_PRESENT + aESNT_TALK_FINAL_NO_PRESENT_NUM,
    aESNT_TALK_HELLO = aESNT_TALK_SAME_BLOCK + aESNT_TALK_SAME_BLOCK_NUM,
    aESNT_TALK_CHK_1ST = aESNT_TALK_HELLO + aESNT_TALK_HELLO_NUM,
    aESNT_TALK_CHK_2ND = aESNT_TALK_CHK_1ST + aESNT_TALK_CHK_1ST_NUM,
    aESNT_TALK_CHK_FINAL = aESNT_TALK_CHK_2ND + aESNT_TALK_CHK_2ND_NUM,
    aESNT_TALK_ALMOST_RECOGNIZE = aESNT_TALK_CHK_FINAL + aESNT_TALK_CHK_FINAL_NUM,
    aESNT_TALK_FINAL_PRESENT2 = aESNT_TALK_ALMOST_RECOGNIZE + aESNT_TALK_ALMOST_RECOGNIZE_NUM,
    aESNT_TALK_FINAL_NO_PRESENT2 = aESNT_TALK_FINAL_PRESENT2 + aESNT_TALK_FINAL_PRESENT2_NUM,
    aESNT_TALK_NO_MORE_PRESENTS = aESNT_TALK_FINAL_NO_PRESENT2 + aESNT_TALK_FINAL_NO_PRESENT2_NUM,

    aESNT_TALK_NUM = aESNT_TALK_NO_MORE_PRESENTS + aESNT_TALK_NO_MORE_PRESENTS_NUM
};

static void aESNT_actor_ct(ACTOR*, GAME*);
static void aESNT_actor_dt(ACTOR*, GAME*);
static void aESNT_actor_init(ACTOR*, GAME*);
static void aESNT_actor_move(ACTOR*, GAME*);
static void aESNT_actor_draw(ACTOR*, GAME*);
static void aESNT_actor_save(ACTOR*, GAME*);
static void aESNT_talk_request(ACTOR*, GAME*);
static int aESNT_talk_init(ACTOR*, GAME*);
static int aESNT_talk_end_chk(ACTOR*, GAME*);
static void aESNT_setupAction(EVENT_SANTA_ACTOR*, GAME_PLAY*, int);

// clang-format off
ACTOR_PROFILE Ev_Santa_Profile = {
    mAc_PROFILE_EV_SANTA,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_SANTA,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(EVENT_SANTA_ACTOR),
    aESNT_actor_ct,
    aESNT_actor_dt,
    aESNT_actor_init,
    mActor_NONE_PROC1,
    aESNT_actor_save,
};
// clang-format on

static void aESNT_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aESNT_actor_move,
        aESNT_actor_draw,
        aNPC_CT_SCHED_TYPE_WANDER,
        aESNT_talk_request,
        aESNT_talk_init,
        aESNT_talk_end_chk,
        0,
    };

    EVENT_SANTA_ACTOR* santa = (EVENT_SANTA_ACTOR*)actorx;

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        mEv_santa_event_c* event_p;
        mEv_santa_event_common_c* event_common_p;

        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        santa->setup_talk_proc = &aESNT_setupAction;
// Aus version adds logic to prevent jingle from being in the border units of an acre.
// This was added to fix the exploit where by trapping Jingle in a border acre,
// he could be tricked over and over without having to find him again.
#if VERSION >= VER_GAFU01_00
        santa->npc_class.movement.range_type = aNPC_MOVE_RANGE_TYPE_SQUARE;
#endif

        event_p = (mEv_santa_event_c*)mEv_get_save_area(mEv_EVENT_TOY_DAY_JINGLE, 0);
        if (event_p == NULL) {
            /* Reserve event data */
            event_p = (mEv_santa_event_c*)mEv_reserve_save_area(mEv_EVENT_TOY_DAY_JINGLE, 0);
            bzero(event_p, sizeof(mEv_santa_event_c));
            mPr_ClearPersonalID(&event_p->pid);
        }
        santa->event_p = event_p;

        event_common_p = (mEv_santa_event_common_c*)mEv_get_common_area(mEv_EVENT_TOY_DAY_JINGLE, 0);
        if (event_common_p == NULL) {
            event_common_p = (mEv_santa_event_common_c*)mEv_reserve_common_area(mEv_EVENT_TOY_DAY_JINGLE, 0);
        }
        santa->event_common_p = event_common_p;
    }
}

static void aESNT_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aESNT_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
    mEv_actor_dying_message(mEv_EVENT_TOY_DAY_JINGLE, actorx);
}

static void aESNT_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aESNT_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/event/ac_ev_santa_move.c_inc"
