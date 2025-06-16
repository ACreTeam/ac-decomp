#ifndef AC_TOKYOSO_NPC0_H
#define AC_TOKYOSO_NPC0_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tokyoso_npc0_actor_s TOKYOSO_NPC0_ACTOR;

typedef void (*aTKN0_THINK_PROC)(TOKYOSO_NPC0_ACTOR* actor, GAME_PLAY* play);
typedef void (*aTKN0_TALK_PROC)(TOKYOSO_NPC0_ACTOR* actor, GAME_PLAY* play);

struct tokyoso_npc0_actor_s {
    NPC_ACTOR npc_class;
    aTKN0_THINK_PROC think_proc;
    aTKN0_TALK_PROC talk_proc;
    int base_msg;
    s16 timer;
    s16 think_idx;
    s16 next_think_idx;
    s16 move_think_idx;
    s16 talk_idx;
    u8 change_flag;
};

extern ACTOR_PROFILE Tokyoso_Npc0_Profile;

#ifdef __cplusplus
}
#endif

#endif
