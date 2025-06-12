#ifndef AC_NPC_RESTART_H
#define AC_NPC_RESTART_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_restart_s NPC_RESTART_ACTOR;

typedef void (*aNRST_TALK_PROC)(NPC_RESTART_ACTOR* actor, GAME_PLAY* play);

struct npc_restart_s {
    NPC_ACTOR npc_class;
    int talk_idx;
    int next_talk_idx;
    aNRST_TALK_PROC talk_proc;
    int talk_end;
    int _9A4;
    int think_idx;
    int card_chan;
    u8 actor_saved;
    u8 auto_nwrite_data_set;
    u8 cheated_flag;
    u8 force_home;
};

extern ACTOR_PROFILE Npc_Restart_Profile;

#ifdef __cplusplus
}
#endif

#endif
