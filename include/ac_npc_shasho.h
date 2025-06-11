#ifndef AC_NPC_SHASHO_H
#define AC_NPC_SHASHO_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_shasho_s NPC_SHASHO_ACTOR;

typedef void (*aNSS_PROC)(ACTOR*, GAME*);
typedef void (*aNSS_INIT_PROC)(NPC_SHASHO_ACTOR*, GAME_PLAY*);
typedef void (*aNSS_MOVE_PROC)(NPC_SHASHO_ACTOR*, GAME*);

/* sizeof(npc_shasho_s) == 0x9a4 */
struct npc_shasho_s {
    /* 0x000 */ NPC_ACTOR npc_class;
    /* 0x994 */ int action;
    /* 0x998 */ int next_action;
    /* 0x99C */ aNSS_PROC talk_action;
    /* 0x9A0 */ ACTOR* train_door_actor;
};

extern ACTOR_PROFILE Npc_Shasho_Profile;

#ifdef __cplusplus
}
#endif

#endif
