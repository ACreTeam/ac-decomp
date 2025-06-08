#ifndef AC_TUKIMI_NPC0_H
#define AC_TUKIMI_NPC0_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tukimi_npc0_s TUKIMI_NPC0_ACTOR;
extern ACTOR_PROFILE Tukimi_Npc0_Profile;

/* sizeof(tukimi_npc0_s) == 0x994 */
struct tukimi_npc0_s {
    /* 0x000 */ NPC_ACTOR npc_class;
};

#ifdef __cplusplus
}
#endif

#endif

