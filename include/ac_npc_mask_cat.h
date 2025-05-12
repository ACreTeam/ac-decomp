#ifndef AC_NPC_MASK_CAT_H
#define AC_NPC_MASK_CAT_H

#include "types.h"
#include "m_actor.h"
#include "ac_npc.h"
#ifdef __cplusplus
extern "C" {
#endif

typedef struct npc_mask_cat_s NPC_MASK_CAT_ACTOR;

/* sizeof(npc_mask_cat_s) == 0x994*/
struct npc_mask_cat_s {
    /* 0x000 */ NPC_ACTOR npc_class;
};

extern ACTOR_PROFILE Npc_Mask_Cat_Profile;

#ifdef __cplusplus
}
#endif

#endif

