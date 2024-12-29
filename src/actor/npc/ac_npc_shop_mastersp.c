#include "ac_npc_shop_mastersp.h"

#include "m_common_data.h"
#include "libultra/libultra.h"
#include "m_item_name.h"
#include "m_msg.h"
#include "m_bgm.h"

enum {
    aSHM_WON_FIRST_PLACE,
    aSHM_WON_SECOND_PLACE,
    aSHM_WON_THIRD_PLACE,
    aSHM_DIDNT_WIN,

    aSHM_WIN_NUM
};

enum {
    aSHM_TALK_TALK_TRY,
    aSHM_TALK_TALK_HAZURE,
    aSHM_TALK_TALK_RETRY,
    aSHM_TALK_STOP_PLAYER,
    aSHM_TALK_GIVE_PLAYER,
    aSHM_TALK_TALK_TAMAKESI,
    aSHM_TALK_END_WAIT,
    aSHM_TALK_SAY_GOODBYE,
    aSHM_TALK_EXIT_WAIT,

    aSHM_TALK_NUM
};

enum {
    aSHM_THINK_NORMAL_WAIT,
    aSHM_THINK_NORMAL_WAIT2,
    aSHM_THINK_NORMAL_WAIT3,
    aSHM_THINK_NORMAL_TURN,
    aSHM_THINK_4,
    aSHM_THINK_5,
    aSHM_THINK_WIN1,
    aSHM_THINK_WIN2,
    aSHM_THINK_WIN3,
    aSHM_THINK_LOSE,
    aSHM_THINK_10,
    aSHM_THINK_11,
    aSHM_THINK_12,
    aSHM_THINK_MOVE,
    aSHM_THINK_MOVE_TURN,
    aSHM_THINK_FADE_OUT,
    aSHM_THINK_MOVE_PLAYER,
    aSHM_THINK_WAIT_PLAYER,
    aSHM_THINK_WAIT_PLAYER2,
    aSHM_THINK_WAIT_PLAYER3,
    aSHM_THINK_WAIT_PLAYER4,
    aSHM_THINK_HIROU,
    aSHM_THINK_HAPPY_ACADEMY,
    aSHM_THINK_HAPPY_ACADEMY2,
    aSHM_THINK_HAPPY_ACADEMY3,

    aSHM_THINK_NUM
};

static void aSHM_actor_ct(ACTOR* actorx, GAME* game);
static void aSHM_actor_dt(ACTOR* actorx, GAME* game);
static void aSHM_actor_move(ACTOR* actorx, GAME* game);
static void aSHM_actor_init(ACTOR* actorx, GAME* game);
static void aSHM_actor_draw(ACTOR* actorx, GAME* game);
static void aSHM_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Shop_Mastersp_Profile = {
    mAc_PROFILE_NPC_SHOP_MASTERSP,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_SHOP_MASTERSP,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_SHOP_MASTERSP_ACTOR),
    &aSHM_actor_ct,
    &aSHM_actor_dt,
    &aSHM_actor_init,
    mActor_NONE_PROC1,
    &aSHM_actor_save,
};
// clang-format on

static int aSHM_talk_init(ACTOR* actorx, GAME* game);
static int aSHM_talk_end_chk(ACTOR* actorx, GAME* game);

static void aSHM_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static int aSHM_change_talk_proc(NPC_SHOP_MASTERSP_ACTOR* shop_mastersp, int talk_proc_idx);
static void aSHM_setup_think_proc(NPC_SHOP_MASTERSP_ACTOR* shop_mastersp, GAME_PLAY* play, int think_idx);

static void aSHM_set_base_position(ACTOR* actorx, GAME_PLAY* play);

static void aSHM_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        &aSHM_actor_move,
        &aSHM_actor_draw,
        5,
        (aNPC_TALK_REQUEST_PROC)&none_proc1,
        &aSHM_talk_init,
        &aSHM_talk_end_chk,
        0,
    };
    // clang-format on

    if (CLIP(npc_clip)->birth_check_proc(actorx, game) == TRUE) {
        NPC_SHOP_MASTERSP_ACTOR* shop_mastersp = (NPC_SHOP_MASTERSP_ACTOR*)actorx;

        shop_mastersp->npc_class.schedule.schedule_proc = &aSHM_schedule_proc;
        CLIP(npc_clip)->ct_proc(actorx, game, &ct_data);
        aSHM_set_base_position(actorx, (GAME_PLAY*)game);
        shop_mastersp->melody_bak = 0;
    }
}

static void aSHM_actor_save(ACTOR* actorx, GAME* game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aSHM_actor_dt(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->dt_proc(actorx, game);
}

static void aSHM_actor_init(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->init_proc(actorx, game);
}

static void aSHM_actor_draw(ACTOR* actorx, GAME* game) {
    CLIP(npc_clip)->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_shop_mastersp_move.c_inc"
#include "../src/actor/npc/ac_npc_shop_mastersp_talk.c_inc"
#include "../src/actor/npc/ac_npc_shop_mastersp_schedule.c_inc"
