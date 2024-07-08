#include "ac_npc_guide.h"

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
    aNGD_ACTION_ENTER,
    aNGD_ACTION_APPROACH,
    aNGD_ACTION_TALK_START_WAIT,
    aNGD_ACTION_TIME_CHECK,
    aNGD_ACTION_SDON_AND_PB_WAIT,
    aNGD_ACTION_TIME_MENU_OPEN_WAIT,
    aNGD_ACTION_TIME_MENU_CLOSE_WAIT,
    aNGD_ACTION_MSG_WIN_OPEN_WAIT,
    aNGD_ACTION_CONFIRM_INPUT_DATA,
    aNGD_ACTION_WAIT_PERMISSION,
    aNGD_ACTION_SITDOWN,
    aNGD_ACTION_PNAME_MENU_OPEN_WAIT,
    aNGD_ACTION_PNAME_MENU_CLOSE_WAIT,
    aNGD_ACTION_SEX_SELECT_WAIT,
    aNGD_ACTION_SEX_SELECT_WAIT2,
    aNGD_ACTION_SEX_SELECT_AFTER,
    aNGD_ACTION_CNAME_MENU_OPEN_WAIT,
    aNGD_ACTION_CNAME_MENU_CLOSE_WAIT,
    aNGD_ACTION_STANDUP_START_WAIT,
    aNGD_ACTION_STANDUP,
    aNGD_ACTION_MOVE_READY,
    aNGD_ACTION_MOVE_TO_AISLE,
    aNGD_ACTION_MOVE_TO_DOOR,
    aNGD_ACTION_MOVE_TO_DECK,
    aNGD_ACTION_KEITAI_ON,
    aNGD_ACTION_KEITAI_TALK,
    aNGD_ACTION_KEITAI_OFF,
    aNGD_ACTION_OPEN_DOOR,
    aNGD_ACTION_RETURN_APPROACH,
    aNGD_ACTION_LAST_TALK_START_WAIT,
    aNGD_ACTION_SITDOWN2_START_WAIT,
    aNGD_ACTION_SITDOWN2,
    aNGD_ACTION_LAST_TALK_END_WAIT,
    aNGD_ACTION_SCENE_CHANGE_WAIT,

    aNGD_ACTION_NUM
};

enum {
    aNGD_OBJ_LOOK_TYPE_NORMAL,
    aNGD_OBJ_LOOK_TYPE_TALK,

    aNGD_OBJ_LOOK_TYPE_NUM
};

static void aNGD_actor_ct(ACTOR* actorx, GAME* game);
static void aNGD_actor_dt(ACTOR* actorx, GAME* game);
static void aNGD_actor_init(ACTOR* actorx, GAME* game);
static void aNGD_actor_save(ACTOR* actorx, GAME* game);

// clang-format off
ACTOR_PROFILE Npc_Guide_Profile = {
    mAc_PROFILE_NPC_GUIDE,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    SP_NPC_GUIDE,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_GUIDE_ACTOR),
    &aNGD_actor_ct,
    &aNGD_actor_dt,
    &aNGD_actor_init,
    mActor_NONE_PROC1,
    &aNGD_actor_save,
};
// clang-format on

static void aNGD_actor_move(ACTOR* actorx, GAME* game);
static void aNGD_actor_draw(ACTOR* actorx, GAME* game);

static void aNGD_setupAction(NPC_GUIDE_ACTOR* guide, GAME_PLAY* play, int action);

static void aNGD_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = { &aNGD_actor_move, &aNGD_actor_draw, 0, NULL, NULL, NULL, 0 };
    NPC_GUIDE_ACTOR* guide = (NPC_GUIDE_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;
    PLAYER_ACTOR* player;

    Common_Get(clip).npc_clip->ct_proc(actorx, game, &ct_data);
    guide->npc_class.condition_info.hide_flg = FALSE; // show guide actor
    guide->npc_class.condition_info.demo_flg =
        aNPC_COND_DEMO_SKIP_ENTRANCE_CHECK | aNPC_COND_DEMO_SKIP_HEAD_LOOKAT | aNPC_COND_DEMO_SKIP_TALK_CHECK |
        aNPC_COND_DEMO_SKIP_ITEM | aNPC_COND_DEMO_SKIP_FORWARD_CHECK | aNPC_COND_DEMO_SKIP_BGCHECK |
        aNPC_COND_DEMO_SKIP_OBJ_COL_CHECK | aNPC_COND_DEMO_SKIP_MOVE_Y | aNPC_COND_DEMO_SKIP_MOVE_CIRCLE_REV |
        aNPC_COND_DEMO_SKIP_MOVE_RANGE_CHECK;
    guide->camera_morph_counter = 40;
    guide->obj_look_type = aNGD_OBJ_LOOK_TYPE_NORMAL;
    guide->npc_class.eye_y = 30.0f;
    guide->camera_move_set_counter = 1;
    guide->npc_class.palActorIgnoreTimer = -1;
    guide->train_door_actor = Actor_info_fgName_search(&play->actor_info, TRAIN_DOOR, ACTOR_PART_BG);
    guide->npc_class.actor_class.shape_info.draw_shadow = TRUE;
    guide->npc_class.actor_class.world.position.z = 130.0f;

    /* Put the player into demo wait state */
    mPlib_request_main_demo_wait_type1(game, 0, NULL);
    player = GET_PLAYER_ACTOR(play);
    if (player != NULL) {
        /* Make the player invisible during the intro train ride */
        player->actor_class.state_bitfield |= ACTOR_STATE_INVISIBLE;
    }

    aNGD_setupAction(guide, play, aNGD_ACTION_ENTER);

    /* Play train noises sfx repeatedly */
    sAdo_SysLevStart(NA_SE_TRAIN_RIDE);

    /* Disable sunlight */
    Common_Set(sunlight_flag, FALSE);

    /* Turn on echo for sound effects */
    sAdo_TrgSeEcho(TRUE);
    sAdo_LevSeEcho(TRUE);
}

static void aNGD_actor_save(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->save_proc(actorx, game);
}

static void aNGD_actor_dt(ACTOR* actorx, GAME* game) {
    /* Update all animals in town to have this town's info */
    mNpc_SetAnimalThisLand(Save_Get(animals), ANIMAL_NUM_MAX);
    Common_Get(clip).npc_clip->dt_proc(actorx, game);

    /* Stop train noise sfx */
    sAdo_SysLevStop(NA_SE_TRAIN_RIDE);
}

static void aNGD_actor_init(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->init_proc(actorx, game);
}

static void aNGD_actor_draw(ACTOR* actorx, GAME* game) {
    Common_Get(clip).npc_clip->draw_proc(actorx, game);
}

#include "../src/ac_npc_guide_animation.c_inc"
#include "../src/ac_npc_guide_move.c_inc"
