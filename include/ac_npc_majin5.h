#ifndef AC_NPC_MAJIN5_H
#define AC_NPC_MAJIN5_H

#include "ac_npc.h"
#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif
#define ANMJ5_THINK_INIT 0
#define ANMJ5_THINK_MAIN 1
#define ANMJ5_SCHEDULE_INIT 0
#define ANMJ5_SCHEDULE_MAIN 1
typedef struct npc_majin5_s NPC_MAJIN5_ACTOR;

extern ACTOR_PROFILE Npc_Majin5_Profile;
/* sizeof(npc_majin5_s) == 0x994*/
struct npc_majin5_s {
    /* 0x000 */ NPC_ACTOR npc_class;
};

#ifdef __cplusplus
}
#endif

#endif

