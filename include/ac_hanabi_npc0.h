#ifndef AC_HANABI_NPC0_H
#define AC_HANABI_NPC0_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hanabi_npc0_actor_s HANABI_NPC0_ACTOR;

typedef void (*aHN0_ACT_PROC)(HANABI_NPC0_ACTOR* actor);

struct hanabi_npc0_actor_s {
    NPC_ACTOR npc_class;
    int action;
    int next_action;
    aHN0_ACT_PROC act_proc;
    s16 base_angle;
};

extern ACTOR_PROFILE Hanabi_Npc0_Profile;

#ifdef __cplusplus
}
#endif

#endif
