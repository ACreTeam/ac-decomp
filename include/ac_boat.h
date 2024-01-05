#ifndef AC_BOAT_H
#define AC_BOAT_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct boat_s BOAT_ACTOR;

struct boat_s {
  ACTOR actor_class;
  // TODO
};

extern ACTOR_PROFILE Boat_Profile;

#ifdef __cplusplus
}
#endif

#endif

