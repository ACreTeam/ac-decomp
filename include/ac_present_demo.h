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

enum {
    aPRD_ACTION_FIRST_SET,
    aPRD_ACTION_PL_COME_OUT_WAIT,
    aPRD_ACTION_PRESENT_WAIT,
    aPRD_ACTION_RETIRE_NPC_WAIT,

    aPRD_ACTION_NUM
};

typedef struct present_demo_actor_s PRESENT_DEMO_ACTOR;

typedef void (*aPRD_ACTION_PROC)(PRESENT_DEMO_ACTOR* present_demo, GAME* game);

struct present_demo_actor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ int action;
    /* 0x178 */ aPRD_ACTION_PROC action_proc;
    /* 0x17C */ ACTOR* world_actor;
    /* 0x180 */ int _180;
    /* 0x184 */ int type;
    /* 0x188 */ mActor_name_t present;
};

extern ACTOR_PROFILE Present_Demo_Profile;

#ifdef __cplusplus
}
#endif

#endif
