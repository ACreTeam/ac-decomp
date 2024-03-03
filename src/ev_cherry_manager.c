#include "m_event.h"
#include "ev_cherry_manager.h"

void eChryMgr_move(ACTOR* actor, GAME* game);
void eChryMgr_draw(ACTOR* actor, GAME* game);
void eChryMgr_ct(ACTOR* actor, GAME* game);
void eChryMgr_dt(ACTOR* actor, GAME* game);

ACTOR_PROFILE Ev_Cherry_Manager_Profile = {
    mAc_PROFILE_EV_CHERRY_MANAGER,
    ACTOR_PART_CONTROL,
    ACTOR_STATE_CAN_MOVE_IN_DEMO_SCENES,
    EMPTY_NO,
    ACTOR_OBJ_BANK_KEEP,
    sizeof(CHERRY_MANAGER_EVENT_ACTOR),

    &eChryMgr_ct,
    &eChryMgr_dt,
    &eChryMgr_move,
    &eChryMgr_draw,
    NULL,
};

void eChryMgr_move(ACTOR* actor, GAME* game) {

}

void eChryMgr_draw(ACTOR* actor, GAME* game) {

}

void eChryMgr_ct(ACTOR* actor, GAME* game) {

}

void eChryMgr_dt(ACTOR* actor, GAME* game) {
    mEv_clear_status(mEv_EVENT_CHERRY_BLOSSOM_FESTIVAL, mEv_STATUS_ACTIVE);
}
