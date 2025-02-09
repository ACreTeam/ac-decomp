#ifndef AC_NPC_SLEEP_OBABA_H
#define AC_NPC_SLEEP_OBABA_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_sleep_obaba_actor_s NPC_SLEEP_OBABA_ACTOR;

typedef void (*aNSO_ACT_PROC)(NPC_SLEEP_OBABA_ACTOR* actor);

struct npc_sleep_obaba_actor_s {
    NPC_ACTOR npc_class;
    int action;
    aNSO_ACT_PROC act_proc;
};

extern ACTOR_PROFILE Npc_Sleep_Obaba_Profile;

#ifdef __cplusplus
}
#endif

#endif
