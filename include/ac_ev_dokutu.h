#ifndef AC_EV_DOKUTU_H
#define AC_EV_DOKUTU_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct event_dokutu_actor_s {
  NPC_ACTOR npc_class;
  int _994;
  int _998;
} EVENT_DOKUTU_ACTOR;

extern ACTOR_PROFILE Ev_Dokutu_Profile;

#ifdef __cplusplus
}
#endif

#endif

