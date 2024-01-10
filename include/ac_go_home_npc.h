#ifndef AC_GO_HOME_NPC_H
#define AC_GO_HOME_NPC_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct go_home_npc_s GO_HOME_NPC_ACTOR;

struct go_home_npc_s {
  NPC_ACTOR npc_class;
};

extern ACTOR_PROFILE Go_Home_Npc_Profile;

#ifdef __cplusplus
}
#endif

#endif

