#ifndef AC_NPC_RCN_GUIDE_H
#define AC_NPC_RCN_GUIDE_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_rcn_guide_s NPC_RCN_GUIDE_ACTOR;

typedef void (*aNRG_THINK_PROC)(NPC_RCN_GUIDE_ACTOR*, GAME_PLAY*);
typedef void (*aNRG_TALK_PROC)(NPC_RCN_GUIDE_ACTOR*, GAME_PLAY*);

/* sizeof(NPC_RCN_GUIDE_ACTOR) == 0x9B4 */
struct npc_rcn_guide_s {
    /* 0x000 */ NPC_ACTOR npc_class;
    /* 0x994 */ int think_idx;
    /* 0x998 */ int next_think_idx;
    /* 0x99C */ aNRG_THINK_PROC think_proc;
    /* 0x9A0 */ int talk_idx;
    /* 0x9A4 */ aNRG_TALK_PROC talk_proc;
    /* 0x9A8 */ u8 talk_proc_idx;
    /* 0x9A9 */ u8 path;
    /* 0x9AA */ u8 melody_copy;
    /* 0x9AC */ int shop_bx;
    /* 0x9B0 */ int shop_bz;
};

extern ACTOR_PROFILE Npc_Rcn_Guide_Profile;

#ifdef __cplusplus
}
#endif

#endif
