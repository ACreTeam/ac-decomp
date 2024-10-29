#include "ac_boxManager.h"

#include "m_name_table.h"


static void BoxManager_Actor_ct(ACTOR* actor, GAME* game);
static void BoxManager_Actor_dt(ACTOR* actor, GAME* game);
static void BoxManager_Actor_move(ACTOR* actor, GAME* game);
static void BoxManager_Actor_draw(ACTOR* actor, GAME* game);

ACTOR_PROFILE BoxManager_Profile = {
    mAc_PROFILE_BOXMANAGER,
    ACTOR_PART_BG,
    ACTOR_STATE_NO_MOVE_WHILE_CULLED | ACTOR_STATE_NO_DRAW_WHILE_CULLED,
    ETC_BOXMANAGER,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(BOXMANAGER_ACTOR),
    &BoxManager_Actor_ct,
    &BoxManager_Actor_dt,
    &BoxManager_Actor_move,
    &BoxManager_Actor_draw,
    NULL
};


static void BoxManager_Actor_ct(ACTOR* actor, GAME* game){

}

static void BoxManager_Actor_dt(ACTOR* actor, GAME* game){

}

static void BoxManager_Actor_move(ACTOR* actor, GAME* game){

}

static void BoxManager_Actor_draw(ACTOR* actor, GAME* game){
    
}