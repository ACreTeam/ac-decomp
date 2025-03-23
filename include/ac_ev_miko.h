#ifndef AC_EV_MIKO_H
#define AC_EV_MIKO_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ev_miko_actor_s EV_MIKO_ACTOR;

typedef void (*aEMK_TALK_PROC)(EV_MIKO_ACTOR* miko, GAME_PLAY* play);

struct ev_miko_actor_s {
    NPC_ACTOR npc_class;
    int talk_action;
    aEMK_TALK_PROC talk_proc;
    int omikuji;
    u8 in_front;
};

extern ACTOR_PROFILE Ev_Miko_Profile;

#ifdef __cplusplus
}
#endif

#endif
