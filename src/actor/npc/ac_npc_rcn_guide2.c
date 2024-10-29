#include "ac_npc_rcn_guide2.h"

#include "m_common_data.h"
#include "m_bgm.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_soncho.h"
#include "ac_intro_demo.h"

enum {
    aNRG2_JOB1,
    aNRG2_JOB2,
    aNRG2_JOB3,
    aNRG2_JOB4,
    aNRG2_JOB5,
    aNRG2_JOB6,
    aNRG2_JOB7,
    aNRG2_JOB8,
    aNRG2_JOB9,
    aNRG2_JOB10,
    aNRG2_JOB11,

    aNRG2_JOB_NUM
};

enum {
    aNRG2_NORM_TALK_JOB1_START,
    aNRG2_NORM_TALK_JOB2_START,
    aNRG2_NORM_TALK_JOB3_START,
    aNRG2_NORM_TALK_JOB4_START,
    aNRG2_NORM_TALK_JOB5_START,
    aNRG2_NORM_TALK_JOB5_2_START,
    aNRG2_NORM_TALK_JOB6_START,
    aNRG2_NORM_TALK_JOB7_START,
    aNRG2_NORM_TALK_JOB10_START,
    aNRG2_NORM_TALK_JOB11_START,

    aNRG2_NORM_TALK_JOB1_REFUSE,
    aNRG2_NORM_TALK_JOB2_REFUSE,
    aNRG2_NORM_TALK_JOB3_REFUSE,
    aNRG2_NORM_TALK_JOB4_REFUSE,
    aNRG2_NORM_TALK_JOB5_REFUSE,
    aNRG2_NORM_TALK_JOB5_2_REFUSE,
    aNRG2_NORM_TALK_JOB6_REFUSE,
    aNRG2_NORM_TALK_JOB7_REFUSE,

    aNRG2_NORM_TALK_J1_CONT1,
    aNRG2_NORM_TALK_J1_CONT2,
    aNRG2_NORM_TALK_J1_CONT3,

    aNRG2_NORM_TALK_J2_CONT1,

    aNRG2_NORM_TALK_J3_CONT1,
    aNRG2_NORM_TALK_J3_CONT2,

    aNRG2_NORM_TALK_J4_CONT1,
    aNRG2_NORM_TALK_J4_CONT2,
    aNRG2_NORM_TALK_J5_CONT3,

    aNRG2_NORM_TALK_J5_CONT1,
    aNRG2_NORM_TALK_J5_CONT2,

    aNRG2_NORM_TALK_J6_CONT1,
    aNRG2_NORM_TALK_J6_CONT2,

    aNRG2_NORM_TALK_J7_CONT1,

    aNRG2_NORM_TALK_J10_CONT1,

    aNRG2_NORM_TALK_J11_CONT1,

    aNRG2_NORM_TALK_J1_END,
    aNRG2_NORM_TALK_J2_END,
    aNRG2_NORM_TALK_J3_END,
    aNRG2_NORM_TALK_J4_END,
    aNRG2_NORM_TALK_J5_END,
    aNRG2_NORM_TALK_J6_END,
    aNRG2_NORM_TALK_J7_END,
    aNRG2_NORM_TALK_J10_END,
    aNRG2_NORM_TALK_J11_END,

    aNRG2_NORM_TALK_AGAIN,

    aNRG2_NORM_TALK_NUM
};

enum {
    aNRG2_FORCE_TALK_SAY_HELLO,
    aNRG2_FORCE_TALK_SAY_HELLO2,
    aNRG2_FORCE_TALK_SAY_HELLO_SP,
    aNRG2_FORCE_TALK_CLOTH_CHK,
    aNRG2_FORCE_TALK_UPSTAIR_CHK,

    aNRG2_FORCE_TALK_NUM
};

enum {
    aNRG2_THINK_SAY_HELLO,
    aNRG2_THINK_SAY_HELLO2,
    aNRG2_THINK_SAY_HELLO3,
    aNRG2_THINK_SEND_AWAY,
    aNRG2_THINK_TALK_START_WAIT,
    aNRG2_THINK_JOB_START_WAIT,
    aNRG2_THINK_ALL_JOB_END,

    aNRG2_THINK_NUM
};

enum {
    aNRG2_TALK_SAY_HELLO,
    aNRG2_TALK_SAY_HELLO_SP,
    aNRG2_TALK_SAY_HELLO_SP2,
    aNRG2_TALK_CLOTH_CHK,
    aNRG2_TALK_TALK_END_WAIT,
    aNRG2_TALK_DEMO_START_WAIT,
    aNRG2_TALK_DEMO_END_WAIT,
    aNRG2_TALK_DEMO_END_WAIT2,
    aNRG2_TALK_JOB_START,
    aNRG2_TALK_JOB_END,
    aNRG2_TALK_3RD_JOB_END,
    aNRG2_TALK_DEMO2_START_WAIT,
    aNRG2_TALK_DEMO2_START_WAIT2,
    aNRG2_TALK_DEMO2_END,
    aNRG2_TALK_GIVE_NEW_PAPER,
    aNRG2_TALK_CHECK_MORE_PAPER,
    aNRG2_TALK_DECIDE_NEW_TARGET,
    aNRG2_TALK_DEMO3_START_WAIT,
    aNRG2_TALK_DEMO3_START_WAIT2,
    aNRG2_TALK_DEMO3_END_WAIT,
    aNRG2_TALK_ALL_JOB_END,

    aNRG2_TALK_NUM
};

typedef struct rcn_guide2_talk_info_s {
    int msg_no;
    aNRG2_TALK_PROC talk_proc;
} aNRG2_talk_info_c;

static void aNRG2_actor_ct(ACTOR* actorx, GAME* game);
static void aNRG2_actor_save(ACTOR* actorx, GAME* game);
static void aNRG2_actor_dt(ACTOR* actorx, GAME* game);
static void aNRG2_actor_init(ACTOR* actorx, GAME* game);
static void aNRG2_actor_draw(ACTOR* actorx, GAME* game);
static void aNRG2_actor_move(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Rcn_Guide2_Profile = {
    mAc_PROFILE_NPC_RCN_GUIDE2,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_RCN_GUIDE2,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_RCN_GUIDE2_ACTOR),
    &aNRG2_actor_ct,
    &aNRG2_actor_dt,
    &aNRG2_actor_init,
    mActor_NONE_PROC1,
    &aNRG2_actor_save,
};
// clang-format on

static void aNRG2_change_talk_proc(NPC_RCN_GUIDE2_ACTOR* rcn_guide2, int talk_proc_idx);
static void aNRG2_force_talk_request(ACTOR* actorx, GAME* game);
static int aNRG2_talk_init(ACTOR* actorx, GAME* game);
static int aNRG2_talk_end_chk(ACTOR* actorx, GAME* game);

static void aNRG2_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* game, int sched_idx);
static void aNRG2_setup_think_proc(NPC_RCN_GUIDE2_ACTOR* rcn_guide2, GAME_PLAY* play, int think_idx);

static void aNRG2_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        &aNRG2_actor_move,
        &aNRG2_actor_draw,
        5,
        &aNRG2_force_talk_request,
        &aNRG2_talk_init,
        &aNRG2_talk_end_chk,
        1,
    };
    // clang-format on

    NPC_RCN_GUIDE2_ACTOR* rcn_guide2 = (NPC_RCN_GUIDE2_ACTOR*)actorx;

    if (Common_Get(clip).npc_clip->birth_check_proc(actorx, game) == TRUE) {
        int shop_type = 0;

        switch (actorx->npc_id) {
            case SP_NPC_RCN_GUIDE2:
                shop_type = 0;
                break;
            case SP_NPC_RCN_GUIDE2_1:
                shop_type = 1;
                break;
            case SP_NPC_RCN_GUIDE2_2:
                shop_type = 2;
                break;
            case SP_NPC_RCN_GUIDE2_3:
                shop_type = 3;
                break;
        }

        rcn_guide2->npc_class.draw.draw_type = shop_type;
        rcn_guide2->npc_class.schedule.schedule_proc = &aNRG2_schedule_proc;
        Common_Get(clip).npc_clip->ct_proc(actorx, game, &ct_data);
    }
}

static void aNRG2_actor_save(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->save_proc(actorx, game);
}

static void aNRG2_actor_dt(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->dt_proc(actorx, game);
}

static void aNRG2_actor_init(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->init_proc(actorx, game);
}

static void aNRG2_actor_draw(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_rcn_guide2_move.c_inc"
#include "../src/actor/npc/ac_npc_rcn_guide2_talk.c_inc"
#include "../src/actor/npc/ac_npc_rcn_guide2_schedule.c_inc"
