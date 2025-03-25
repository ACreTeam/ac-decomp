#ifndef AC_EV_MAJIN_H
#define AC_EV_MAJIN_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ev_majin_actor_s EV_MAJIN_ACTOR;

typedef void (*aEMJ_PROC)(EV_MAJIN_ACTOR* majin, GAME_PLAY* play);

struct ev_majin_actor_s {
    NPC_ACTOR npc_class;
    int action;
    aEMJ_PROC act_proc;
};

extern ACTOR_PROFILE Ev_Majin_Profile;

#ifdef __cplusplus
}
#endif

#endif
