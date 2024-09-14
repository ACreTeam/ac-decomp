#ifndef AC_EV_BROKER_H
#define AC_EV_BROKER_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ac_ev_broker EV_BROKER_ACTOR;

typedef void (*aEBRK_ACT_PROC)(EV_BROKER_ACTOR*);

/* sizeof(EV_BROKER_ACTOR) == 0x9AC */
struct ac_ev_broker {
    /* 0x000 */ NPC_ACTOR npc_class;
    /* 0x994 */ int action;
    /* 0x998 */ int next_action;
    /* 0x99C */ int action_step;
    /* 0x9A0 */ aEBRK_ACT_PROC action_proc;
    /* 0x9A4 */ ACTOR* tent_actor;
    /* 0x9A8 */ u8 pl_talk_lock;
};

extern ACTOR_PROFILE Ev_Broker_Profile;

#ifdef __cplusplus
}
#endif

#endif
