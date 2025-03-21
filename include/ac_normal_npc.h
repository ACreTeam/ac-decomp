#ifndef AC_NORMAL_NPC_H
#define AC_NORMAL_NPC_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct normal_npc_actor_s NORMAL_NPC_ACTOR;

struct normal_npc_actor_s {
    NPC_ACTOR npc_class;
};

extern ACTOR_PROFILE Normal_Npc_Profile;

#ifdef __cplusplus
}
#endif

#endif
