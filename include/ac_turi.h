#ifndef AC_TURI_H
#define AC_TURI_H

#include "types.h"
#include "m_actor.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct turi_actor_s TURI_ACTOR;

struct turi_actor_s {
    STRUCTURE_ACTOR structure_class;
};

extern ACTOR_PROFILE Turi_Profile;

#ifdef __cplusplus
}
#endif

#endif
