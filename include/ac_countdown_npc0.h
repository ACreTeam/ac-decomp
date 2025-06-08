#ifndef AC_COUNTDOWN_NPC0_H
#define AC_COUNTDOWN_NPC0_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct countdown_npc0_actor_s COUNTDOWN_NPC0_ACTOR;

typedef void (*aCD0_ACT_PROC)(COUNTDOWN_NPC0_ACTOR *actor);

struct countdown_npc0_actor_s {
    NPC_ACTOR npc_class;
    int action;
    aCD0_ACT_PROC act_proc;
    int term;
};

extern ACTOR_PROFILE Countdown_Npc0_Profile;

#ifdef __cplusplus
}
#endif

#endif
