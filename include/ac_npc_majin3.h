#ifndef AC_NPC_MAJIN3_H
#define AC_NPC_MAJIN3_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#include "m_string.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_majin3_actor_s NPC_MAJIN3_ACTOR;

typedef void (*aMJN3_THINK_PROC)(NPC_MAJIN3_ACTOR* actor, GAME_PLAY* play);
typedef void (*aMJN3_TALK_PROC)(NPC_MAJIN3_ACTOR* actor, GAME_PLAY* play);

struct npc_majin3_actor_s {
    NPC_ACTOR npc_class;
    int think_idx;
    int next_think_idx;
    aMJN3_THINK_PROC think_proc;
    int talk_idx;
    aMJN3_TALK_PROC talk_proc;
    u8 reply[mString_DEFAULT_STR_SIZE];
    u8 reply_idx;
};

extern ACTOR_PROFILE Npc_Majin3_Profile;

#ifdef __cplusplus
}
#endif

#endif
