#ifndef AC_EV_CARPETPEDDLER_H
#define AC_EV_CARPETPEDDLER_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Ev_CarpetPeddler_Profile;

#define eECPD_PRICE_MULT_CAP 4
#define eECPD_PRICE_START 3000

typedef struct ev_carpetpeddler_s EV_CARPETPEDDLER_ACTOR;

typedef void (*aECPD_PROC)(EV_CARPETPEDDLER_ACTOR*, GAME_PLAY*, int);
typedef void (*aECPD_INIT_PROC)(EV_CARPETPEDDLER_ACTOR*, GAME_PLAY*);

struct ev_carpetpeddler_s {
    NPC_ACTOR npc_class;
    /* 0x994 */ int _994;
    /* 0x998 */ int _998;
    /* 0x99c */ aECPD_INIT_PROC proc;
    /* 0x9a0 */ aECPD_PROC setup_action;
    /* 0x9a4 */ int price;
    /* 0x9a8 */ mActor_name_t carpet;
    /* 0x9aa */ mActor_name_t trade_in_item;
    /* 0x9ac */ int next_action;
};

enum ev_carpetpeddler_action {
    eECPD_ACTION_NONE,
    eECPD_ACTION_MSG_WIN_OPEN_WAIT,
    eECPD_ACTION_DEMO_START_WAIT,
    eECPD_ACTION_1ST_CHECK,
    eECPD_ACTION_2ND_CHECK,
    eECPD_ACTION_GRAD_MESSAGE,
    eECPD_ACTION_MENU_OPEN_WAIT,
    eECPD_ACTION_MENU_CLOSE_WAIT,
    eECPD_ACTION_DEMO0_END_WAIT,
    eECPD_ACTION_DEMO1_END_WAIT,
    eECPD_ACTION_DEMO2_START_WAIT,
    eECPD_ACTION_DEMO2_START_CHECK,
    eECPD_ACTION_DEMO2_END_WAIT,
    eECPD_ACTION_REFUSE_TRADE_IN,
    eECPD_ACTION_REFUSE_TRADE_IN_END_WAIT
};

#ifdef __cplusplus
}
#endif

#endif

