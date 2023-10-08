#include "ac_boxMove.h"

#include "m_name_table.h"


static void BoxMove_Actor_ct(ACTOR* actor, GAME* game);
static void BoxMove_Actor_dt(ACTOR* actor, GAME* game);
static void BoxMove_Actor_move(ACTOR* actor, GAME* game);
static void BoxMove_Actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE BoxMove_Profile = {
    mAc_PROFILE_BOXMOVE,
    ACTOR_PART_BG,
    ACTOR_STATE_NONE,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(BOXMOVE_ACTOR),
    &BoxMove_Actor_ct,
    &BoxMove_Actor_dt,
    &BoxMove_Actor_move,
    &BoxMove_Actor_draw,
    NULL
};

static void BoxMove_Actor_ct(ACTOR* actor, GAME* game){

}

static void BoxMove_Actor_dt(ACTOR* actor, GAME* game){

}

static void BoxMove_Actor_move(ACTOR* actor, GAME* game){
    
}

static void BoxMove_Actor_draw(ACTOR* actor, GAME* game){
    
}