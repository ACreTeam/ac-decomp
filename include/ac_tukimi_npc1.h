#ifndef AC_TUKIMI_NPC1_H
#define AC_TUKIMI_NPC1_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tukimi_npc1_s TUKIMI_NPC1_ACTOR;
extern ACTOR_PROFILE Tukimi_Npc1_Profile;

/* sizeof(tukimi_npc1_s) == 0x998 */
struct tukimi_npc1_s {
    /* 0x000 */ NPC_ACTOR npc_class;
    /* 0x994 */ int event_idx;
};

#ifdef __cplusplus
}
#endif

#endif
