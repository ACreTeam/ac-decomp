#include "ac_boxTrick01.h"

#include "m_name_table.h"

extern void BoxTrick01_Actor_ct(ACTOR* actor, GAME* game);
extern void BoxTrick01_Actor_dt(ACTOR* actor, GAME* game);
extern void BoxTrick01_Actor_move(ACTOR* actor, GAME* game);

ACTOR_PROFILE BoxTrick01_Profile = {
    mAc_PROFILE_BOXTRICK01,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    ETC_BOXTRICK,
    ACTOR_OBJ_BANK_3,
    sizeof(BOXTRICK01_ACTOR),
    &BoxTrick01_Actor_ct,
    &BoxTrick01_Actor_dt,
    &BoxTrick01_Actor_move,
    (mActor_proc)&none_proc1,
    NULL
};


static void BoxTrick01_Actor_ct(ACTOR* actor, GAME* game){

}

static void BoxTrick01_Actor_dt(ACTOR* actor, GAME* game){

}

static void BoxTrick01_Actor_move(ACTOR* actor, GAME* game){

}