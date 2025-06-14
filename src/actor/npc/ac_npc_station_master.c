#include "ac_npc_station_master.h"

#include "libultra/libultra.h"
#include "m_common_data.h"
#include "m_msg.h"
#include "m_font.h"
#include "m_player_lib.h"
#include "m_string.h"
#include "m_bgm.h"
#include "m_train_control.h"
#include "ac_intro_demo.h"
#include "ac_ride_off_demo.h"

enum {
    aSTM_THINK_GET_OFF_WAIT,
    aSTM_THINK_TURN,
    aSTM_THINK_2,
    aSTM_THINK_3,
    aSTM_THINK_4,
    aSTM_THINK_5,
    aSTM_THINK_INTERRUPT_TURN,
    aSTM_THINK_INTERRUPT_MOVE,
    aSTM_THINK_8,
    aSTM_THINK_9,
    aSTM_THINK_MAKE_TRAIN_BF,
    aSTM_THINK_MAKE_TRAIN,
    aSTM_THINK_TRAIN_ARRIVE_WAIT,
    aSTM_THINK_MOVE_TURN_BF,
    aSTM_THINK_14,
    aSTM_THINK_MOVE,
    aSTM_THINK_16,
    aSTM_THINK_17,
    aSTM_THINK_IN_TRAIN,
    aSTM_THINK_IN_TRAIN2,
    aSTM_THINK_SEE_OFF,
    aSTM_THINK_GAME_END,

    aSTM_THINK_NUM
};

static void aSTM_actor_ct(ACTOR* actorx, GAME* game);
static void aSTM_actor_dt(ACTOR* actorx, GAME* game);
static void aSTM_actor_init(ACTOR* actorx, GAME* game);
static void aSTM_actor_save(ACTOR* actorx, GAME* game);
static void aSTM_actor_move(ACTOR* actorx, GAME* game);
static void aSTM_actor_draw(ACTOR* actorx, GAME* game);
static int aSTM_talk_init(ACTOR* actorx, GAME* game);
static int aSTM_talk_end_chk(ACTOR* actorx, GAME* game);
static void aSTM_schedule_proc(NPC_ACTOR*, GAME_PLAY*, int);
static void aSTM_talk_request(ACTOR* actorx, GAME* game);
static int aSTM_change_talk_proc(NPC_STATION_MASTER_ACTOR*, u8);
static void aSTM_setup_think_proc(NPC_STATION_MASTER_ACTOR* actor, GAME_PLAY* play, u8 think_idx);

// clang-format off
ACTOR_PROFILE Npc_Station_Master_Profile = {
    mAc_PROFILE_NPC_STATION_MASTER,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_STATION_MASTER,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_STATION_MASTER_ACTOR),
    aSTM_actor_ct,
    aSTM_actor_dt,
    aSTM_actor_init,
    mActor_NONE_PROC1,
    aSTM_actor_save
};
// clang-format on

static void aSTM_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        aSTM_actor_move,
        aSTM_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aSTM_talk_init,
        aSTM_talk_end_chk,
        0
    };
    // clang-format on

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_STATION_MASTER_ACTOR* actor = (NPC_STATION_MASTER_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aSTM_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        actor->sound = 0;
        actor->happening_sound = 0;
        actor->melody_save = 0;
        actor->npc_class.palActorIgnoreTimer = -1;
    }
}

static void aSTM_actor_save(ACTOR* actorx, GAME* game) {
    mNpc_RenewalSetNpc(actorx);
}

static void aSTM_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_STATION_MASTER_ACTOR* actor = (NPC_STATION_MASTER_ACTOR*)actorx;

    if (actor->sound != 0) {
        mBGMPsComp_delete_ps_demo(actor->sound, 0x168);
    }

    switch (actor->happening_sound) {
        case BGM_INTRO_ARRIVE:
        case BGM_INTRO_NEW_TOWN:
            mBGMPsComp_delete_ps_happening(actor->happening_sound, 0x168);
            break;
    }

    NPC_CLIP->dt_proc(actorx, game);
}

static void aSTM_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aSTM_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_station_master_move.c_inc"
#include "../src/actor/npc/ac_npc_station_master_talk.c_inc"
#include "../src/actor/npc/ac_npc_station_master_schedule.c_inc"
