#ifndef AC_PRESENT_NPC_H
#define AC_PRESENT_NPC_H

#include "types.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aPST_PRESENT_TYPE_GOLDEN_ROD (1 << 0)
#define aPST_PRESENT_TYPE_GOLDEN_NET (1 << 1)

typedef struct present_npc_actor_s PRESENT_NPC_ACTOR;

typedef void (*aPST_THINK_PROC)(PRESENT_NPC_ACTOR* actor, GAME_PLAY* play);
typedef void (*aPST_TALK_PROC)(PRESENT_NPC_ACTOR* actor);

struct present_npc_actor_s {
    NPC_ACTOR npc_class;
    int think_idx;
    int next_think_idx;
    aPST_THINK_PROC think_proc;
    int talk_type;
    aPST_TALK_PROC talk_proc;
    u8 _9A8;
    u8 umbrella_flag;
};

extern ACTOR_PROFILE Present_Npc_Profile;

#ifdef __cplusplus
}
#endif

#endif
