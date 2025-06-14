#ifndef AC_NPC_POLICE2_H
#define AC_NPC_POLICE2_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_police2_actor_s NPC_POLICE2_ACTOR;

typedef void (*aPOL2_ACT_PROC)(NPC_POLICE2_ACTOR* actor, GAME_PLAY* play);

struct npc_police2_actor_s {
    NPC_ACTOR npc_class;
    int action;
    aPOL2_ACT_PROC act_proc;
    u8 _99C;
    u8 now_zone;
    u8 next_zone;
    u8 pl_zone;
    s16 player_angl;
    s16 item_idx;
};

extern ACTOR_PROFILE Npc_Police2_Profile;

#ifdef __cplusplus
}
#endif

#endif
