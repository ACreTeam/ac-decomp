#ifndef AC_HOUSE_GOKI_H
#define AC_HOUSE_GOKI_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct house_goki_actor_s HOUSE_GOKI_ACTOR;
typedef void (*aHG_ACT_PROC)(ACTOR* actorx, GAME* game);

struct house_goki_actor_s {
    /* 0x000 */ACTOR actor_class;
    /* 0x174 */aHG_ACT_PROC act_proc;
    /* 0x178 */int _178;
    /* 0x17C */int action;
    /* 0x180 */f32 timer;
    /* 0x184 */f32 timer2;
    /* 0x188 */int jump_flag;
    /* 0x18C */f32 shadow_alpha;
    /* 0x190 */f32 alpha;
    /* 0x194 */f32 anm_no;
};

extern ACTOR_PROFILE House_Goki_Profile;

#ifdef __cplusplus
}
#endif

#endif
