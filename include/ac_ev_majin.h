#ifndef AC_EV_MAJIN_H
#define AC_EV_MAJIN_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct actor_ev_majin_actor_s{
    NPC_ACTOR npc_class;
    int unk994;
    aNPC_SUB_PROC think_proc;
}EV_NPCMAJIN_ACTOR;

extern ACTOR_PROFILE Ev_Majin_Profile;

#ifdef __cplusplus
}
#endif

#endif

