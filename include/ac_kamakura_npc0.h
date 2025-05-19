#ifndef AC_KAMAKURA_NPC0_H
#define AC_KAMAKURA_NPC0_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_kamakura_npc0_s NPC_KAMUKURA_NPC0_ACTOR;

/* sizeof(npc_kamakura_npc0_s) == 0x994*/
struct npc_kamakura_npc0_s {
    /* 0x000 */ NPC_ACTOR npc_class;
};
extern ACTOR_PROFILE Kamakura_Npc0_Profile;

#ifdef __cplusplus
}
#endif

#endif

