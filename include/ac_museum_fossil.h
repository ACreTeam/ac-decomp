#ifndef AC_MUSEUM_FOSSIL_H
#define AC_MUSEUM_FOSSIL_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct museum_fossil_actor_s {
    ACTOR actor_class;
    s16 target_angle;
    int msg_no;
} MUSEUM_FOSSIL_ACTOR;

extern ACTOR_PROFILE Museum_Fossil_Profile;

#ifdef __cplusplus
}
#endif

#endif
