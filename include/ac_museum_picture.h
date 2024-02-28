#ifndef AC_MUSEUM_PICTURE_H
#define AC_MUSEUM_PICTURE_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct museum_picture_actor_s {
    ACTOR actor_class;
    int msg_no;
} MUSEUM_PICTURE_ACTOR;

extern ACTOR_PROFILE Museum_Picture_Profile;

#ifdef __cplusplus
}
#endif

#endif
