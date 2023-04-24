#ifndef M_POLICE_BOX_H
#define M_POLICE_BOX_H

#include "types.h"
#include "m_actor_type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mPB_POLICE_BOX_ITEM_STORAGE_COUNT 20

/* sizeof(PoliceBox_c) == 0x28 */
typedef struct police_box_s {
  /* 0x00 */ mActor_name_t keep_items[mPB_POLICE_BOX_ITEM_STORAGE_COUNT];
} PoliceBox_c;

#ifdef __cplusplus
}
#endif

#endif
