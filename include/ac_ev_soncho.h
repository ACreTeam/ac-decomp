#ifndef AC_EV_SONCHO_H
#define AC_EV_SONCHO_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  aESC_TALK_OWARI,
  aESC_TALK_SELECT,
  aESC_TALK_SECAND,

  aESC_TALK_NUM
};

typedef struct npc_event_soncho_s {
  NPC_ACTOR npc_class;
  u8 talk_state;
  u8 first_talk;
} EVENT_SONCHO_ACTOR;

extern ACTOR_PROFILE Ev_Soncho_Profile;

#ifdef __cplusplus
}
#endif

#endif

