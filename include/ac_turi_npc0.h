#ifndef AC_TURI_NPC0_H
#define AC_TURI_NPC0_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aTR0_NPC_MAX 5

typedef struct turi_npc0_actor_s TURI_NPC0_ACTOR;

typedef void (*aTR0_PROC)(TURI_NPC0_ACTOR *actor);

struct turi_npc0_actor_s {
    NPC_ACTOR npc_class;
    int action;
    aTR0_PROC act_proc;
};

extern ACTOR_PROFILE Turi_Npc0_Profile;

#ifdef __cplusplus
}
#endif

#endif
