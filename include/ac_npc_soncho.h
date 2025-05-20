#ifndef AC_NPC_SONCHO_H
#define AC_NPC_SONCHO_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_soncho_actor_s NPC_SONCHO_ACTOR;

typedef void (*aNS_PROC)(NPC_SONCHO_ACTOR* actor);

struct npc_soncho_actor_s {
    NPC_ACTOR npc_class;
    aNS_PROC think_proc;
    int _998;
    u16 _99C;
    u8 think_idx;
    u8 think_after_talk_idx;
    u8 _9A0;
    u8 talk_idx;
    u8 think_chg_flag;
    u8 _9A3;
};

extern ACTOR_PROFILE Npc_Soncho_Profile;

#ifdef __cplusplus
}
#endif

#endif
