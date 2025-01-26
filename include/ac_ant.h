#ifndef AC_ANT_H
#define AC_ANT_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ant_actor_s ANT_ACTOR;

typedef void (*aANT_ACT_PROC)(ANT_ACTOR* ant, GAME* game);

struct ant_actor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ aANT_ACT_PROC act_proc;
    /* 0x178 */ int action;
    /* 0x17C */ int alpha;
    /* 0x180 */ ACTOR* insect_actor;
    /* 0x184 */ int disappear_counter;
    /* 0x188 */ mActor_name_t* below_fg_p;
};

extern ACTOR_PROFILE Ant_Profile;

#ifdef __cplusplus
}
#endif

#endif
