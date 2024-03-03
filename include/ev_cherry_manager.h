#ifndef EV_CHERRY_MANAGER_H
#define EV_CHERRY_MANAGER_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

extern ACTOR_PROFILE Ev_Cherry_Manager_Profile;

typedef struct cherry_manager_s {
  ACTOR actor_class;
} CHERRY_MANAGER_EVENT_ACTOR;

#ifdef __cplusplus
}
#endif

#endif

