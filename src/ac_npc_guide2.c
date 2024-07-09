#include "ac_npc_guide2.h"

#include "m_play.h"
#include "m_common_data.h"
#include "ac_train_door.h"
#include "m_player_lib.h"
#include "m_font.h"
#include "m_msg.h"
#include "m_timeIn_ovl.h"
#include "m_ledit_ovl.h"
#include "libultra/libultra.h"
#include "m_bgm.h"
#include "m_soncho.h"

enum {
    aNG2_ACTION_ENTER,
    aNG2_ACTION_APPROACH,
    aNG2_ACTION_TALK_START_WAIT,
    aNG2_ACTION_WAIT_PERMISSION,
    aNG2_ACTION_SITDOWN,
    aNG2_ACTION_SDON_AND_PB_WAIT,
    aNG2_ACTION_PNAME_MENU_OPEN_WAIT,
    aNG2_ACTION_PNAME_MENU_CLOSE_WAIT,
    aNG2_ACTION_MSG_WIN_OPEN_WAIT,
    aNG2_ACTION_PNAME_NG,
    aNG2_ACTION_SEX_SELECT_WAIT,
    aNG2_ACTION_SEX_SELECT_WAIT2,
    aNG2_ACTION_SEX_SELECT_AFTER,
    aNG2_ACTION_STANDUP_START_WAIT,
    aNG2_ACTION_STANDUP,
    aNG2_ACTION_MOVE_READY,
    aNG2_ACTION_MOVE_TO_AISLE,
    aNG2_ACTION_MOVE_TO_DOOR,
    aNG2_ACTION_MOVE_TO_DECK,
    aNG2_ACTION_KEITAI_ON,
    aNG2_ACTION_KEITAI_TALK,
    aNG2_ACTION_KEITAI_OFF,
    aNG2_ACTION_OPEN_DOOR,
    aNG2_ACTION_RETURN_APPROACH,
    aNG2_ACTION_LAST_TALK_START_WAIT,
    aNG2_ACTION_SITDOWN2_START_WAIT,
    aNG2_ACTION_SITDOWN2,
    aNG2_ACTION_LAST_TALK_END_WAIT,
    aNG2_ACTION_SCENE_CHANGE_WAIT,

    aNG2_ACTION_NUM
};

enum {
    aNG2_OBJ_LOOK_TYPE_NORMAL,
    aNG2_OBJ_LOOK_TYPE_TALK,

    aNG2_OBJ_LOOK_TYPE_NUM
};

static void aNG2_actor_ct(ACTOR* actorx, GAME* game);
static void aNG2_actor_dt(ACTOR* actorx, GAME* game);
static void aNG2_actor_init(ACTOR* actorx, GAME* game);
static void aNG2_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Guide2_Profile = {
    mAc_PROFILE_NPC_GUIDE2,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    SP_NPC_GUIDE2,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_GUIDE2_ACTOR),
    &aNG2_actor_ct,
    &aNG2_actor_dt,
    &aNG2_actor_init,
    mActor_NONE_PROC1,
    &aNG2_actor_save,
};
// clang-format on

static void aNG2_actor_move(ACTOR* actorx, GAME* game);
static void aNG2_actor_draw(ACTOR* actorx, GAME* game);

static void aNG2_setupAction(NPC_GUIDE2_ACTOR* guide2, GAME_PLAY* play, int action);

static void aNG2_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = { &aNG2_actor_move, &aNG2_actor_draw, 0, NULL, NULL, NULL, 0 };
    NPC_GUIDE2_ACTOR* guide2 = (NPC_GUIDE2_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player;

    Common_Get(clip).npc_clip->ct_proc(actorx, game, &ct_data);
    guide2->npc_class.condition_info.hide_flg = FALSE; // show guide2 actor
    guide2->npc_class.condition_info.demo_flg =
        aNPC_COND_DEMO_SKIP_ENTRANCE_CHECK | aNPC_COND_DEMO_SKIP_HEAD_LOOKAT | aNPC_COND_DEMO_SKIP_TALK_CHECK |
        aNPC_COND_DEMO_SKIP_ITEM | aNPC_COND_DEMO_SKIP_FORWARD_CHECK | aNPC_COND_DEMO_SKIP_BGCHECK |
        aNPC_COND_DEMO_SKIP_OBJ_COL_CHECK | aNPC_COND_DEMO_SKIP_MOVE_Y | aNPC_COND_DEMO_SKIP_MOVE_CIRCLE_REV |
        aNPC_COND_DEMO_SKIP_MOVE_RANGE_CHECK;
    guide2->camera_morph_counter = 40;
    guide2->obj_look_type = aNG2_OBJ_LOOK_TYPE_NORMAL;
    guide2->npc_class.eye_y = 30.0f;
    guide2->camera_move_set_counter = 1;
    guide2->npc_class.palActorIgnoreTimer = -1;
    guide2->train_door_actor = Actor_info_fgName_search(&play->actor_info, TRAIN_DOOR, ACTOR_PART_BG);
    guide2->npc_class.actor_class.shape_info.draw_shadow = TRUE;
    guide2->npc_class.actor_class.world.position.z = 130.0f;

    /* Put the player into demo wait state */
    mPlib_request_main_demo_wait_type1(game, 0, NULL);
    player = GET_PLAYER_ACTOR(play);
    if (player != NULL) {
        /* Make the player invisible during the intro train ride */
        player->actor_class.state_bitfield |= ACTOR_STATE_INVISIBLE;
    }

    aNG2_setupAction(guide2, play, aNG2_ACTION_ENTER);

    /* Play train noises sfx repeatedly */
    sAdo_SysLevStart(NA_SE_TRAIN_RIDE);
}

static void aNG2_actor_save(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->save_proc(actorx, game);
}

static void aNG2_actor_dt(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->dt_proc(actorx, game);

    /* Stop train noise sfx */
    sAdo_SysLevStop(NA_SE_TRAIN_RIDE);
}

static void aNG2_actor_init(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->init_proc(actorx, game);
}

static void aNG2_actor_draw(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->draw_proc(actorx, game);
}

#include "../src/ac_npc_guide2_animation.c_inc"
#include "../src/ac_npc_guide2_move.c_inc"
