#ifndef AC_HANAMI_NPC1_H
#define AC_HANAMI_NPC1_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hanami_npc1_actor_s HANAMI_NPC1_ACTOR;

typedef void (*aHM1_ACT_PROC)(HANAMI_NPC1_ACTOR* actor);

struct hanami_npc1_actor_s {
    NPC_ACTOR npc_class;
    int action;
    int next_action;
    aHM1_ACT_PROC act_proc;
};

extern ACTOR_PROFILE Hanami_Npc1_Profile;

#ifdef __cplusplus
}
#endif

#endif
