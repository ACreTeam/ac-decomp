#ifndef AC_EV_PUMPKIN_H
#define AC_EV_PUMPKIN_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ev_pumpkin_common_s {
    s8 bx;
    s8 bz;
} aEv_pumpkin_common_c;

typedef struct ev_pumpkin_actor_s EV_PUMPKIN_ACTOR;

typedef void (*aEPK_TALK_PROC)(EV_PUMPKIN_ACTOR* pumpkin, GAME_PLAY* play);

struct ev_pumpkin_actor_s {
    NPC_ACTOR npc_class;
    int talk_action;
    aEPK_TALK_PROC talk_proc;
    aEv_pumpkin_common_c* common_p;
    mActor_name_t present;
    mActor_name_t item;
};

extern ACTOR_PROFILE Ev_Pumpkin_Profile;

#ifdef __cplusplus
}
#endif

#endif
