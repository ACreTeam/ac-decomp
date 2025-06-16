#ifndef AC_TUNAHIKI_NPC0_H
#define AC_TUNAHIKI_NPC0_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tunahiki_npc0_actor_s TUNAHIKI_NPC0_ACTOR;

typedef void (*aTNN0_THINK_PROC)(TUNAHIKI_NPC0_ACTOR* actor, GAME_PLAY* play);
typedef void (*aTNN0_TALK_PROC)(TUNAHIKI_NPC0_ACTOR* actor, GAME_PLAY* play);

struct tunahiki_npc0_actor_s {
    NPC_ACTOR npc_class;
    aTNN0_THINK_PROC think_proc;
    aTNN0_TALK_PROC talk_proc;
    ACTOR* rope_p;
    int base_msg;
    s16 timer;
    u8 think_idx;
    u8 next_think_idx;
    u8 talk_idx;
    u8 change_flag;
};

extern ACTOR_PROFILE Tunahiki_Npc0_Profile;

#ifdef __cplusplus
}
#endif

#endif
