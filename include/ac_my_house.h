#ifndef AC_MY_HOUSE_H
#define AC_MY_HOUSE_H

#include "types.h"
#include "m_actor.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct my_house_actor_s MY_HOUSE_ACTOR;

struct my_house_actor_s {
    STRUCTURE_ACTOR structure_class;
};

extern ACTOR_PROFILE MyHouse_Profile;

#ifdef __cplusplus
}
#endif

#endif
