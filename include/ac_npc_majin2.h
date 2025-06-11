#ifndef AC_NPC_MAJIN2_H
#define AC_NPC_MAJIN2_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_majin2_actor_s NPC_MAJIN2_ACTOR;

typedef void (*aMJN2_THINK_PROC)(NPC_MAJIN2_ACTOR* actor, GAME_PLAY* play);
typedef void (*aMJN2_TALK_PROC)(NPC_MAJIN2_ACTOR* actor, GAME_PLAY* play);

struct npc_majin2_actor_s {
    NPC_ACTOR npc_class;
    int think_idx;
    int next_think_idx;
    aMJN2_THINK_PROC think_proc;
    int norm_talk_idx;
    int force_talk_idx;
    aMJN2_TALK_PROC talk_proc;
};

extern ACTOR_PROFILE Npc_Majin2_Profile;

#ifdef __cplusplus
}
#endif

#endif
