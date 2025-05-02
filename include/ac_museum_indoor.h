#ifndef AC_MUSEUM_INDOOR_H
#define AC_MUSEUM_INDOOR_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct museum_indoor_actor_s MUSEUM_INDOOR_ACTOR;

struct museum_indoor_actor_s {
    ACTOR actor_class;
    f32 alpha;
    int cull_index;
};

extern ACTOR_PROFILE Museum_Indoor_Profile;

#ifdef __cplusplus
}
#endif

#endif
