#ifndef AC_EV_CASTAWAY_H
#define AC_EV_CASTAWAY_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ev_castaway_s EV_CASTAWAY_ACTOR;

struct ev_castaway_s {
  NPC_ACTOR npc_class;
  s16 bobbing_cycle;
};

extern ACTOR_PROFILE Ev_Castaway_Profile;

#ifdef __cplusplus
}
#endif

#endif

