#include "ac_npc_shasho.h"

#include "ac_npc.h"
#include "ac_npc_mask_cat2.h"
#include "ac_train_door.h"
#include "audio.h"
#include "c_keyframe.h"
#include "m_actor.h"
#include "m_actor_type.h"
#include "m_common_data.h"
#include "m_lib.h"

enum {
    aNSS_ACT_ENTER_WALK_BACK_DECK,
    aNSS_ACT_ENTER_TURN_BACK_DECK,
    aNSS_ACT_ENTER_BACK_DOOR,
    aNSS_ACT_WALK_TO_FRONT_DOOR,
    aNSS_ACT_EXIT_FRONT_DOOR,
    aNSS_ACT_EXIT_FRONT_DOOR2,
    aNSS_ACT_WALK_TO_BACK_DOOR,
    aNSS_ACT_ENTER_BACK_DOOR2,
    aNSS_ACT_EXIT_TURN_BACK_DECK,
    aNSS_ACT_EXIT_WALK_BACK_DECK,

    aNSS_ACT_NUM
};

static void aNSS_actor_ct(ACTOR* actorx, GAME* game);
static void aNSS_actor_dt(ACTOR* actorx, GAME* game);
static void aNSS_actor_init(ACTOR* actorx, GAME* game);
static void aNSS_actor_move(ACTOR* actorx, GAME* game);
static void aNSS_actor_draw(ACTOR* actorx, GAME* game);
static void aNSS_actor_save(ACTOR* actorx, GAME* game);

static void aNSS_set_animation(ACTOR*, int);
static void aNSS_set_walk_spd(NPC_SHASHO_ACTOR*);
static void aNSS_set_stop_spd(NPC_SHASHO_ACTOR*);
static void aNSS_set_door_SE(NPC_SHASHO_ACTOR* shasho_actor);
static void aNSS_enter_walk_back_deck(ACTOR* actorx, GAME* game);
static void aNSS_enter_turn_back_deck(ACTOR* actorx, GAME* game);
static void aNSS_enter_back_door(ACTOR* actorx, GAME* game);
static void aNSS_walk_to_front_door(ACTOR* actorx, GAME* game);
static void aNSS_exit_front_door(ACTOR* actorx, GAME* game);
static void aNSS_walk_to_back_door(ACTOR* actorx, GAME* game);
static void aNSS_exit_turn_back_deck(ACTOR* actorx, GAME* game);
static void aNSS_exit_walk_back_deck(ACTOR* actorx, GAME* game);
static void aNSS_enter_walk_back_deck_init(NPC_SHASHO_ACTOR* shasho_actor, GAME_PLAY* game_play);
static void aNSS_enter_turn_back_deck_init(NPC_SHASHO_ACTOR* shasho_actor, GAME_PLAY* game_play);
static void aNSS_enter_back_door_init(NPC_SHASHO_ACTOR* shasho_actor, GAME_PLAY* game_play);
static void aNSS_walk_to_front_door_init(NPC_SHASHO_ACTOR* shasho_actor, GAME_PLAY* game_play);
static void aNSS_exit_front_door_init(NPC_SHASHO_ACTOR* shasho_actor, GAME_PLAY* game_play);
static void aNSS_enter_front_door_init(NPC_SHASHO_ACTOR* shasho_actor, GAME_PLAY* game_play);
static void aNSS_exit_back_door_init(NPC_SHASHO_ACTOR* shasho_actor, GAME_PLAY* game_play);
static void aNSS_exit_walk_back_deck_init(NPC_SHASHO_ACTOR* shasho_actor, GAME_PLAY* game_play);
static void aNSS_init_proc(ACTOR* actorx, GAME* game, int action);
static void aNSS_setupAction(ACTOR* actorx, GAME* game, int action);

// clang-format off
ACTOR_PROFILE Npc_Shasho_Profile = {
    mAc_PROFILE_NPC_SHASHO,
    ACTOR_PART_NPC,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    SP_NPC_SASHO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(NPC_SHASHO_ACTOR),
    &aNSS_actor_ct,
    &aNSS_actor_dt,
    &aNSS_actor_init,
    mActor_NONE_PROC1,
    &aNSS_actor_save,
};
// clang-format on

static void aNSS_actor_ct(ACTOR* actorx, GAME* game) {
    static aNPC_ct_data_c ct_data = {
        &aNSS_actor_move, &aNSS_actor_draw, aNPC_CT_SCHED_TYPE_NONE, NULL, NULL, NULL, 0
    };
    static xyz_t start_pos[2] = { { 140.0f, 0.0f, 350.0f }, { 100.0f, 0.0f, 48.0f } };
    static short start_angl[2] = { DEG2SHORT_ANGLE(-180.0f), DEG2SHORT_ANGLE(90.0f) };
    static int action[2] = { aNSS_ACT_EXIT_FRONT_DOOR2, aNSS_ACT_ENTER_WALK_BACK_DECK };

    NPC_SHASHO_ACTOR* shasho_actor = (NPC_SHASHO_ACTOR*)actorx;
    GAME_PLAY* play = (GAME_PLAY*)game;

    int type = actorx->actor_specific;

    NPC_CLIP->ct_proc(actorx, game, &ct_data);

    shasho_actor->npc_class.condition_info.demo_flg =
        aNPC_COND_DEMO_SKIP_MOVE_RANGE_CHECK | aNPC_COND_DEMO_SKIP_MOVE_CIRCLE_REV | aNPC_COND_DEMO_SKIP_MOVE_Y |
        aNPC_COND_DEMO_SKIP_OBJ_COL_CHECK | aNPC_COND_DEMO_SKIP_BGCHECK | aNPC_COND_DEMO_SKIP_FORWARD_CHECK |
        aNPC_COND_DEMO_SKIP_ITEM | aNPC_COND_DEMO_SKIP_TALK_CHECK | aNPC_COND_DEMO_SKIP_HEAD_LOOKAT |
        aNPC_COND_DEMO_SKIP_ENTRANCE_CHECK;
    shasho_actor->npc_class.palActorIgnoreTimer = -1;
    shasho_actor->npc_class.condition_info.hide_flg = FALSE;
    shasho_actor->train_door_actor = Actor_info_fgName_search(&play->actor_info, TRAIN_DOOR, ACTOR_PART_BG);
    actorx->shape_info.draw_shadow = TRUE;
    actorx->shape_info.rotation.y = start_angl[type];
    actorx->world.angle.y = start_angl[type];
    actorx->world.position.x = start_pos[type].x;
    actorx->world.position.z = start_pos[type].z;

    aNSS_setupAction(&shasho_actor->npc_class.actor_class, &play->game, action[type]);
}

static void aNSS_actor_save(ACTOR* actorx, GAME* game) {
    NPC_CLIP->save_proc(actorx, game);
}

static void aNSS_actor_dt(ACTOR* actorx, GAME* game) {
    ACTOR* sasho_actor = actorx;
    NPC_MASK_CAT2_ACTOR* mask_cat2_actor = (NPC_MASK_CAT2_ACTOR*)sasho_actor->parent_actor;

    if (sasho_actor->parent_actor) {
        sasho_actor->parent_actor = NULL;
        mask_cat2_actor->sasho_actor = NULL;
    }

    NPC_CLIP->dt_proc(actorx, game);
}

static void aNSS_actor_init(ACTOR* actorx, GAME* game) {
    NPC_CLIP->init_proc(actorx, game);
}

static void aNSS_actor_draw(ACTOR* actorx, GAME* game) {
    NPC_CLIP->draw_proc(actorx, game);
}

#include "../src/actor/npc/ac_npc_shasho_move.c_inc"
