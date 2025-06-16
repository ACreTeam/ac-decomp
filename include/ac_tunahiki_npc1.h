#ifndef AC_TUNAHIKI_NPC1_H
#define AC_TUNAHIKI_NPC1_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tunahiki_npc1_actor_s TUNAHIKI_NPC1_ACTOR;

typedef void (*aTNN1_THINK_PROC)(TUNAHIKI_NPC1_ACTOR* actor, GAME_PLAY* play);
typedef void (*aTNN1_TALK_PROC)(TUNAHIKI_NPC1_ACTOR* actor, GAME_PLAY* play);

struct tunahiki_npc1_actor_s {
    NPC_ACTOR npc_class;
    aTNN1_THINK_PROC think_proc;
    aTNN1_TALK_PROC talk_proc;
    int base_msg;
    s16 dir;
    s16 timer;
    u8 talk_idx;
    u8 think_idx;
    u8 next_think_idx;
    u8 change_flag;
};

extern ACTOR_PROFILE Tunahiki_Npc1_Profile;

#ifdef __cplusplus
}
#endif

#endif
