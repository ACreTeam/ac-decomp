#ifndef AC_NPC_ENGINEER_H
#define AC_NPC_ENGINEER_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct actor_npc_engineer_s{
    NPC_ACTOR npc_class;
}NPCENGINEER_ACTOR;

extern ACTOR_PROFILE Npc_Engineer_Profile;

#ifdef __cplusplus
}
#endif

#endif

