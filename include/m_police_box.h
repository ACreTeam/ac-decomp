#ifndef M_POLICE_BOX_H
#define M_POLICE_BOX_H

#include "types.h"
#include "m_actor_type.h"
#include "game.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mPB_POLICE_BOX_ITEM_STORAGE_COUNT 20 /* total storage space */
#define mPB_MAX_GROW_SIZE 5 /* Maximum number of items to trigger generating random new items */

/* Possible new items to add to lost and found */
enum police_box_category {
  mPB_CATEGORY_GOODS,
  mPB_CATEGORY_ITEM,
  mPB_CATEGORY_FLOWER,
  mPB_CATEGORY_UMBRELLA,

  mPB_CATEGORY_NUM
};

/* sizeof(PoliceBox_c) == 0x28 */
typedef struct police_box_s {
  /* 0x00 */ mActor_name_t keep_items[mPB_POLICE_BOX_ITEM_STORAGE_COUNT];
} PoliceBox_c;

extern void mPB_copy_itemBuf(mActor_name_t* item_buf);
extern int mPB_get_keep_item_sum();
extern void mPB_keep_item(mActor_name_t item_no);
extern void mPB_keep_all_item_in_block(int blk_x, int blk_z);
extern void mPB_force_set_keep_item();
extern void mPB_police_box_init(GAME* game);

#ifdef __cplusplus
}
#endif

#endif
