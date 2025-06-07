#ifndef AC_HANABI_NPC1_H
#define AC_HANABI_NPC1_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hanabi_npc1_actor_s HANABI_NPC1_ACTOR;

typedef void (*aHN1_ACT_PROC)(HANABI_NPC1_ACTOR* actor);

struct hanabi_npc1_actor_s {
    NPC_ACTOR npc_class;
    int action;
    aHN1_ACT_PROC act_proc;
    s16 dst_pos_x;
    s16 dst_pos_z;
    int npc_idx;
    u8 clap_se_no;
};

extern ACTOR_PROFILE Hanabi_Npc1_Profile;

#ifdef __cplusplus
}
#endif

#endif
