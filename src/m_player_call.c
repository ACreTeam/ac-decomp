#include "m_player_call.h"

#include "m_player.h"
#include "m_name_table.h"
#include "m_play.h"

mActor_proc Player_actor_ct_func;
mActor_proc Player_actor_dt_func;
mActor_proc Player_actor_move_func;
mActor_proc Player_actor_draw_func;

void Player_actor_ct_call(ACTOR* actor, GAME* game);
void Player_actor_dt_call(ACTOR* actor, GAME* game);
void Player_actor_move_call(ACTOR* actor, GAME* game);
void Player_actor_draw_call(ACTOR* actor, GAME* game);

ACTOR_PROFILE Player_Profile = {
    mAc_PROFILE_PLAYER,
    ACTOR_PART_PLAYER,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES | ACTOR_STATE_26 | ACTOR_STATE_25 | ACTOR_STATE_NO_MOVE_WHILE_CULLED |
        ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_2 | ACTOR_STATE_0,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(PLAYER_ACTOR),
    Player_actor_ct_call,
    Player_actor_dt_call,
    Player_actor_move_call,
    Player_actor_draw_call,
    NULL,
};

static void initfunc(GAME_PLAY* play) {
    Submenu* submenu = &play->submenu;

    Player_actor_ct_func = mSM_ovlptr_dllcnv(&Player_actor_ct, submenu, 1);
    Player_actor_dt_func = mSM_ovlptr_dllcnv(&Player_actor_dt, submenu, 1);
    Player_actor_move_func = mSM_ovlptr_dllcnv(&Player_actor_move, submenu, 1);
    Player_actor_draw_func = mSM_ovlptr_dllcnv(&Player_actor_draw, submenu, 1);
}

static void Player_actor_ct_call(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    load_player(&play->submenu);
    initfunc(play);
    Player_actor_ct_func(actor, game);
}

static void Player_actor_dt_call(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    load_player(&play->submenu);
    Player_actor_dt_func(actor, game);
}

static void Player_actor_move_call(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    load_player(&play->submenu);
    Player_actor_move_func(actor, game);
}

static void Player_actor_draw_call(ACTOR* actor, GAME* game) {
    GAME_PLAY* play = (GAME_PLAY*)game;

    load_player(&play->submenu);
    Player_actor_draw_func(actor, game);
}
