#ifndef AC_SET_NPC_MANAGER_H
#define AC_SET_NPC_MANAGER_H

#include "types.h"
#include "m_actor.h"

#ifdef __cplusplus
extern "C" {
#endif

#define aSNMgr_EVENT_NORMAL_NPC_NUM mNpc_EVENT_NPC_NUM

typedef struct set_npc_event_save_s {
    u8 animal_idx[aSNMgr_EVENT_NORMAL_NPC_NUM];
} aSNMgr_event_save_c;

extern ACTOR_PROFILE Set_Npc_Manager_Profile;

#ifdef __cplusplus
}
#endif

#endif
