#include "ac_npc_rcn_guide.h"

#include "m_play.h"
#include "m_name_table.h"
#include "libultra/libultra.h"
#include "m_common_data.h"
#include "m_player_lib.h"
#include "m_bgm.h"
#include "m_msg.h"
#include "m_font.h"
#include "m_house.h"
#include "ac_intro_demo.h"

/* sizeof(aNRG_talk_data_c) == 0x0C */
typedef struct rcn_guide_talk_data_s {
    /* 0x00 */ int msg_no;
    /* 0x04 */ u8 turn_flag;
    /* 0x05 */ u8 camera_type;
    /* 0x06 */ u8 melody_flag;
    /* 0x08 */ aNRG_TALK_PROC talk_proc;
} aNRG_talk_data_c;

enum {
    aNRC_THINK_CALL,
    aNRC_THINK_APPROACH,
    aNRG_THINK_INTRODUCE,
    aNRC_THINK_TURN,
    aNRC_THINK_TAKE_WITH,
    aNRC_THINK_EXPLAIN,
    aNRC_THINK_DECIDE_HOUSE_WAIT,
    aNRC_THINK_STOP_WADE,
    aNRC_THINK_BEFORE_OPEN_DOOR_TALK,
    aNRC_THINK_BEFORE_OPEN_DOOR_TALK2,
    aNRC_THINK_ENTER_WAIT,
    aNRC_THINK_RESTART_WAIT,
    aNRC_THINK_RESTART_TALK,
    aNRC_THINK_DECIDE_HOUSE,
    aNRC_THINK_EXIT_TURN,
    aNRC_THINK_EXIT,
    aNRC_THINK_WAIT,

    aNRC_THINK_NUM
};

enum {
    aNRG_FORCE_TALK_CALL,
    aNRG_FORCE_TALK_INTRODUCE,
    aNRG_FORCE_TALK_EXPLAIN,
    aNRG_FORCE_TALK_STOP_WADE,
    aNRG_FORCE_TALK_BEFORE_OPEN_DOOR_TALK,
    aNRG_FORCE_TALK_BEFORE_OPEN_DOOR2_TALK,
    aNRG_FORCE_TALK_HOUSE_TAKEN,
    aNRG_FORCE_TALK_HOUSE_VACANT,

    aNRG_FORCE_TALK_NUM
};

enum {
    aNRG_NORM_TALK_DECIDE_HOUSE,

    aNRG_NORM_TALK_NUM
};

static void aNRG_actor_ct(ACTOR* actorx, GAME* game);
static void aNRG_actor_save(ACTOR* actorx, GAME* game);
static void aNRG_actor_dt(ACTOR* actorx, GAME* game);
static void aNRG_actor_init(ACTOR* actorx, GAME* game);
static void aNRG_actor_draw(ACTOR* actorx, GAME* game);
static void aNRG_actor_move(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Rcn_Guide_Profile = {
    mAc_PROFILE_NPC_RCN_GUIDE,
    ACTOR_PART_NPC,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    SP_NPC_RCN_GUIDE,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_RCN_GUIDE_ACTOR),
    &aNRG_actor_ct,
    &aNRG_actor_dt,
    &aNRG_actor_init,
    mActor_NONE_PROC1,
    &aNRG_actor_save,
};
// clang-format on

static void aNRG_force_talk_request(ACTOR* actorx, GAME* game);
static int aNRG_talk_init(ACTOR* actorx, GAME* game);
static int aNRG_talk_end_chk(ACTOR* actorx, GAME* game);

static void aNRG_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* game, int sched_idx);
static void aNRG_setup_think_proc(NPC_RCN_GUIDE_ACTOR* rcn_guide, GAME_PLAY* play, int think_idx);

static void aNRG_actor_ct(ACTOR* actorx, GAME* game) {
    // clang-format off
    static aNPC_ct_data_c ct_data = {
        &aNRG_actor_move,
        &aNRG_actor_draw,
        5,
        &aNRG_force_talk_request,
        &aNRG_talk_init,
        &aNRG_talk_end_chk,
        0,
    };
    // clang-format on

    NPC_RCN_GUIDE_ACTOR* rcn_guide = (NPC_RCN_GUIDE_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player;
    s16 angle_y;

    if (Common_Get(clip).npc_clip->birth_check_proc(actorx, &play->game) == TRUE) {
        rcn_guide->npc_class.schedule.schedule_proc = &aNRG_schedule_proc;
        Common_Get(clip).npc_clip->ct_proc(actorx, &play->game, &ct_data);
        rcn_guide->npc_class.collision.priority = 2;
        rcn_guide->melody_copy = rcn_guide->npc_class.talk_info.melody_inst;

        /* Set shop acre */
        mFI_BlockKind2BkNum(&rcn_guide->shop_bx, &rcn_guide->shop_bz, mRF_BLOCKKIND_SHOP);

        rcn_guide->npc_class.draw.main_animation.keyframe.morph_counter = 0.0f;
        rcn_guide->npc_class.actor_class.status_data.weight = 255;

        player = GET_PLAYER_ACTOR(play);
        if (player != NULL) {
            angle_y = search_position_angleY(&rcn_guide->npc_class.actor_class.world.position,
                                             &player->actor_class.world.position);
        } else {
            angle_y = 0;
        }

        rcn_guide->npc_class.actor_class.shape_info.rotation.y = angle_y;
        rcn_guide->npc_class.actor_class.world.angle.y = angle_y;
    }
}

static void aNRG_actor_save(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->save_proc(actorx, game);
}

static void aNRG_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_RCN_GUIDE_ACTOR* rcn_guide = (NPC_RCN_GUIDE_ACTOR*)actorx;

    /* Stop playing the initial intro music when destruct due to entering a house */
    if (rcn_guide->think_idx == aNRC_THINK_WAIT) {
        mBGMPsComp_delete_ps_demo(BGM_INTRO_RCN_GUIDE, 0x168);
    }

    Common_Get(clip).npc_clip->dt_proc(actorx, game);
}

static void aNRG_actor_init(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->init_proc(actorx, game);
}

static void aNRG_actor_draw(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->draw_proc(actorx, game);
}

#include "../src/ac_npc_rcn_guide_move.c_inc"
#include "../src/ac_npc_rcn_guide_talk.c_inc"
#include "../src/ac_npc_rcn_guide_schedule.c_inc"
