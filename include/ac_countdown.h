#ifndef AC_COUNTDOWN_H
#define AC_COUNTDOWN_H

#include "types.h"
#include "ac_structure.h"
#include "ac_countdown_clip.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct countdown_actor_s COUNT_ACTOR;

struct countdown_actor_s {
    /* 0x000 */ STRUCTURE_ACTOR structure_class;
};

extern ACTOR_PROFILE Count_Profile;

#ifdef __cplusplus
}
#endif

#endif
