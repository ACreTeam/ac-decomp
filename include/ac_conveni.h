#ifndef AC_CONVENI_H
#define AC_CONVENI_H

#include "types.h"
#include "m_actor.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct conveni_actor_s CONVENI_ACTOR;

struct conveni_actor_s {
    STRUCTURE_ACTOR struct_class;
};

extern ACTOR_PROFILE Conveni_Profile;

#ifdef __cplusplus
}
#endif

#endif
