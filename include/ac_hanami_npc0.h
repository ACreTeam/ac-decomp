#ifndef AC_HANAMI_NPC0_H
#define AC_HANAMI_NPC0_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hanami_npc0_actor_s HANAMI_NPC0_ACTOR;

typedef void (*aHM0_ACT_PROC)(HANAMI_NPC0_ACTOR* actor);

struct hanami_npc0_actor_s {
    NPC_ACTOR npc_class;
    int action;
    aHM0_ACT_PROC act_proc;
    int event_idx;
    u8 clap_se_no;
};

extern ACTOR_PROFILE Hanami_Npc0_Profile;

#ifdef __cplusplus
}
#endif

#endif
