#ifndef AC_DEPART_H
#define AC_DEPART_H

#include "types.h"
#include "m_actor.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct depart_actor_s DEPART_ACTOR;

struct depart_actor_s {
    STRUCTURE_ACTOR struct_class;
};

extern ACTOR_PROFILE Depart_Profile;

#ifdef __cplusplus
}
#endif

#endif
