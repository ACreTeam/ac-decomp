#ifndef AC_NPC_POLICE_H
#define AC_NPC_POLICE_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_police_actor_s NPC_POLICE_ACTOR;

typedef void (*aPOL_TALK_PROC)(NPC_POLICE_ACTOR* actor, GAME_PLAY* play);
typedef void (*aPOL_SETUP_ACTION_PROC)(NPC_POLICE_ACTOR* actor, GAME_PLAY* play, int action);

struct npc_police_actor_s {
    NPC_ACTOR npc_class;
    int _994;
    int talk_act;
    aPOL_TALK_PROC talk_proc;
    aPOL_SETUP_ACTION_PROC setup_action_proc;
    int exit_greeting;
};

extern ACTOR_PROFILE Npc_Police_Profile;

#ifdef __cplusplus
}
#endif

#endif
