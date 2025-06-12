#include "ac_npc_restart.h"

#include "m_common_data.h"
#include "m_msg.h"
#include "m_card.h"
#include "m_player_lib.h"
#include "m_soncho.h"
#include "m_house.h"
#include "m_bgm.h"
#include "m_string.h"

enum {
    aNRST_THINK_START,
    aNRST_THINK_TITLE,
    aNRST_THINK_DOOR,
    aNRST_THINK_WAIT,

    aNRST_THINK_NUM
};

enum {
    aNRST_TALK_SELECT,
    aNRST_TALK_BEFORE_SAVE,
    aNRST_TALK_SAVE,
    aNRST_TALK_SELECT2,
    aNRST_TALK_SELECT3,
    aNRST_TALK_BEFORE_INIT,
    aNRST_TALK_INIT,
    aNRST_TALK_WAIT_END,

    aNRST_TALK_NUM
};

enum {
    aNRST_MSG_GROUP1,
    aNRST_MSG_GROUP2,
    aNRST_MSG_GROUP3,

    aNRST_MSG_TYPE_NUM
};

static void aNRST_actor_ct(ACTOR* actorx, GAME* game);
static void aNRST_actor_dt(ACTOR* actorx, GAME* game);
static void aNRST_actor_move(ACTOR* actorx, GAME* game);
static void aNRST_actor_draw(ACTOR* actorx, GAME* game);
static void aNRST_actor_save(ACTOR* actorx, GAME* game);
static void aNRST_actor_init(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Restart_Profile = {
    mAc_PROFILE_NPC_RESTART,
    ACTOR_PART_NPC,
    ACTOR_STATE_NONE,
    SP_NPC_RESTART,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_RESTART_ACTOR),
    aNRST_actor_ct,
    aNRST_actor_dt,
    aNRST_actor_init,
    mActor_NONE_PROC1,
    aNRST_actor_save,
};
// clang-format on

static u8 aNRST_sound_mode[] = { 0, 1, 2 };
static u8 aNRST_voice_mode[] = { 0, 1, 2 };

static void aNRST_talk_request(ACTOR* actorx, GAME* game);
static int aNRST_talk_init(ACTOR* actorx, GAME* game);
static int aNRST_talk_end_chk(ACTOR* actorx, GAME* game);

static void aNRST_schedule_proc(NPC_ACTOR* nactorx, GAME_PLAY* play, int type);
static void aNRST_setup_think_proc(NPC_RESTART_ACTOR* actor, GAME_PLAY* play, int think_idx);
static void aNRST_change_talk_proc(NPC_RESTART_ACTOR* actor, int talk_idx);

static void aNRST_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        aNRST_actor_move,
        aNRST_actor_draw,
        aNPC_CT_SCHED_TYPE_SPECIAL,
        (aNPC_TALK_REQUEST_PROC)none_proc1,
        aNRST_talk_init,
        aNRST_talk_end_chk,
        0,
    };
    GAME_PLAY* play = (GAME_PLAY*)game;

    if (NPC_CLIP->birth_check_proc(actorx, game) == TRUE) {
        NPC_RESTART_ACTOR* actor = (NPC_RESTART_ACTOR*)actorx;

        actor->npc_class.schedule.schedule_proc = aNRST_schedule_proc;
        NPC_CLIP->ct_proc(actorx, game, &ct_data);
        actorx->status_data.weight = MASSTYPE_IMMOVABLE;

        mPlib_request_main_demo_wait_type1(game, FALSE, NULL);

        {
            ACTOR* playerx = GET_PLAYER_ACTOR_GAME_ACTOR(game);

            if (playerx != NULL) {
                playerx->state_bitfield |= ACTOR_STATE_INVISIBLE;
            }
        }

        {
            xyz_t pos;
            xyz_t eye;

            pos.x = 100.0f;
            pos.y = 60.0f;
            pos.z = 60.0f;

            eye.x = 100.0f;
            eye.y = 130.0f;
            eye.z = 210.0f;

            Camera2_change_priority(play, 0);
            Camera2_request_main_lock(play, &pos, &eye, 40.0f, 0, 100.0f, 400.0f, 5);
        }

        sAdo_SetOutMode(aNRST_sound_mode[Save_Get(config).sound_mode]);
        sAdo_SetVoiceMode(aNRST_voice_mode[Save_Get(config).voice_mode]);

        actor->npc_class.condition_info.hide_request = FALSE;
        actor->npc_class.condition_info.demo_flg = aNPC_COND_DEMO_SKIP_FEEL_CHECK;
        actor->npc_class.talk_info.melody_inst = 0;
        actor->npc_class.talk_info.memory = 0;

        actor->actor_saved = FALSE;
        actor->auto_nwrite_data_set = FALSE;
        actor->cheated_flag = Save_Get(cheated_flag);
        actor->force_home = Save_Get(npc_force_go_home);
    }
}

static void aNRST_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aNRST_actor_dt(ACTOR* actorx, GAME* game) {
    NPC_CLIP->dt_proc(actorx, game);
}

static void aNRST_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aNRST_actor_move(ACTOR* actorx, GAME* game) {
    NPC_CLIP->move_proc(actorx, game);
    mSC_change_player_freeze((GAME_PLAY*)game);
}

#include "../src/actor/npc/ac_npc_restart_schedule.c_inc"
#include "../src/actor/npc/ac_npc_restart_talk.c_inc"

static void aNRST_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}
