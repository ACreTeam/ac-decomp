#ifndef AC_MSCORE_CONTROL_H
#define AC_MSCORE_CONTROL_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mscore_control_actor_s MSCORE_CONTROL_ACTOR;

typedef void (*aMSC_ACTION_PROC)(MSCORE_CONTROL_ACTOR*, GAME_PLAY*);

struct mscore_control_actor_s {
    ACTOR actor_class;
    aMSC_ACTION_PROC action_proc;
    int action;
    int counter;
    u8* readbuf_p;
    u8 melody[16];
};

extern ACTOR_PROFILE Mscore_Control_Profile;

#ifdef __cplusplus
}
#endif

#endif
