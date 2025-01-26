#ifndef AC_RESET_DEMO_H
#define AC_RESET_DEMO_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct reset_demo_actor_s RESET_DEMO_ACTOR;

typedef void (*aRSD_ACT_PROC)(RESET_DEMO_ACTOR* reset_demo, GAME_PLAY* play);

struct reset_demo_actor_s {
    /* 0x000 */ ACTOR actor_class;
    /* 0x174 */ int action;
    /* 0x178 */ aRSD_ACT_PROC act_proc;
    /* 0x17C */ u16 request_light;
    /* 0x17E */ mActor_name_t reset_name;
    /* 0x180 */ ACTOR* reset_actor;
    /* 0x184 */ Lights light;
    /* 0x194 */ Light_list* light_list;
};

extern ACTOR_PROFILE Reset_Demo_Profile;

#ifdef __cplusplus
}
#endif

#endif
