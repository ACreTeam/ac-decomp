#ifndef AC_STATION_H
#define AC_STATION_H

#include "types.h"
#include "m_actor.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct station_actor_s STATION_ACTOR;

struct station_actor_s {
    STRUCTURE_ACTOR struct_class;
};

extern ACTOR_PROFILE Station_Profile;

#ifdef __cplusplus
}
#endif

#endif
