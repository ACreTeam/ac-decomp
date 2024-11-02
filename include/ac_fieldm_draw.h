#ifndef AC_FIELDM_DRAW_H
#define AC_FIELDM_DRAW_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct fieldm_actor_s FIELDM_ACTOR;

struct fieldm_actor_s {
    ACTOR actor_class;
    int _174[4];
};

extern ACTOR_PROFILE Fieldm_Draw_Profile;

#ifdef __cplusplus
}
#endif

#endif
