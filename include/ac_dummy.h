#ifndef AC_DUMMY_H
#define AC_DUMMY_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct actor_dummy_s DUMMY_ACTOR;

typedef void (*DUMMY_PROC)(DUMMY_ACTOR*, GAME_PLAY*);

struct actor_dummy_s{
    ACTOR actor_class;
};

extern ACTOR_PROFILE Dummy_Profile;

#ifdef __cplusplus
}
#endif

#endif

