#include "ac_dummy.h"

#include "m_name_table.h"

static void Dummy_Actor_ct(ACTOR* actor, GAME* game);
static void Dummy_Actor_dt(ACTOR* actor, GAME* game);
static void Dummy_Actor_draw(ACTOR* actor, GAME* game);
static void Dummy_Actor_move(ACTOR* actor, GAME* game);

ACTOR_PROFILE Dummy_Profile = {
    mAc_PROFILE_DUMMY,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_NO_DRAW_WHILE_CULLED | ACTOR_STATE_NO_MOVE_WHILE_CULLED,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(DUMMY_ACTOR),
    Dummy_Actor_ct,
    Dummy_Actor_dt,
    Dummy_Actor_move,
    Dummy_Actor_draw,
    NULL
};

static void Dummy_Actor_ct(ACTOR* actor, GAME* game){
}

static void Dummy_Actor_dt(ACTOR* actor, GAME* game){
}

static void Dummy_Actor_draw(ACTOR* actor, GAME* game){
}

static void Dummy_Actor_move(ACTOR* actor, GAME* game){
}
