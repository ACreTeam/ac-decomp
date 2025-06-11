#ifndef AC_NPC_MAJIN_H
#define AC_NPC_MAJIN_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_majin_actor_s NPC_MAJIN_ACTOR;

typedef void (*aMJN_THINK_PROC)(NPC_MAJIN_ACTOR* actor, GAME_PLAY* play);

struct npc_majin_actor_s {
    NPC_ACTOR npc_class;
    int think_idx;
    int next_think_idx;
    aMJN_THINK_PROC think_proc;
    int talk_idx;
    int camera_zoomup;
    int set_head_request;
};

extern ACTOR_PROFILE Npc_Majin_Profile;

#ifdef __cplusplus
}
#endif

#endif
