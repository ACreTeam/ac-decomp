#ifndef AC_NPC_SENDO_H
#define AC_NPC_SENDO_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_sendo_s NPC_SENDO_ACTOR;

struct npc_sendo_s {
  NPC_ACTOR npc_class;
  // TODO
};

extern ACTOR_PROFILE Npc_Sendo_Profile;

#ifdef __cplusplus
}
#endif

#endif

