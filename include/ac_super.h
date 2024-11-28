#ifndef AC_SUPER_H
#define AC_SUPER_H

#include "types.h"
#include "m_actor.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct super_actor_s SUPER_ACTOR;

struct super_actor_s {
    STRUCTURE_ACTOR struct_class;
};

extern ACTOR_PROFILE Super_Profile;

#ifdef __cplusplus
}
#endif

#endif
