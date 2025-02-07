#ifndef AC_PRESENT_DEMO_H
#define AC_PRESENT_DEMO_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    aPRD_TYPE_BIRTHDAY,
    aPRD_TYPE_GOLDEN_ROD,
    aPRD_TYPE_GOLDEN_NET,
    aPRD_TYPE_SONCHO_VACATION0_CONTRIBUTED,
    aPRD_TYPE_SONCHO_VACATION1_CONTRIBUTED,
    aPRD_TYPE_SONCHO_VACATION0_STARTED,
    aPRD_TYPE_SONCHO_VACATION1_STARTED,

    aPRD_TYPE_NUM
};

typedef struct present_demo_actor_s PRESENT_DEMO_ACTOR;

typedef void (*aPRD_ACTION_PROC)(PRESENT_DEMO_ACTOR* present_demo, GAME* game);

struct present_demo_actor_s {
    ACTOR actor_class;
    int action;
    aPRD_ACTION_PROC action_proc;
    ACTOR* world_actor;
    int _180;
    int type;
    mActor_name_t present;
};

extern ACTOR_PROFILE Present_Demo_Profile;

#ifdef __cplusplus
}
#endif

#endif
