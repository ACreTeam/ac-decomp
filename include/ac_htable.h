#ifndef AC_HTABLE_H
#define AC_HTABLE_H

#include "types.h"
#include "m_actor.h"
#include "ac_structure.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef mActor_name_t (*aHTBL_SEARCH_PICK_UP_ITEM_LAYER2_PROC)(GAME*);

typedef struct htable_clip_s {
    aHTBL_SEARCH_PICK_UP_ITEM_LAYER2_PROC search_pick_up_item_layer2_proc;
    xyz_t pickup_pos;
    s16 pickup_counter;
} aHTBL_Clip_c;

typedef STRUCTURE_ACTOR HTABLE_ACTOR;

extern ACTOR_PROFILE Htable_Profile;

#ifdef __cplusplus
}
#endif

#endif
