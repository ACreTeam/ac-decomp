#ifndef M_ALL_GROW_H
#define M_ALL_GROW_H

#include "types.h"
#include "m_all_grow_ovl.h"
#include "m_field_info.h"
#include "m_time.h"
#include "libu64/gfxprint.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mAGrw_DUMP_WIDTH 4
#define mAGrw_DUMP_HEIGHT 4

enum {
  mAGrw_XMAS_PROC_CLEAR,
  mAGrw_XMAS_PROC_SET,

  mAGrw_XMAS_PROC_NUM
};

enum {
  mAGrw_FRUIT_APPLE,
  mAGrw_FRUIT_CHERRY,
  mAGrw_FRUIT_PEAR,
  mAGrw_FRUIT_PEACH,
  mAGrw_FRUIT_ORANGE,

  mAGrw_FRUIT_NUM
};

#define mAGrw_XMAS_LIGHTS_MAX_BLOCK 3
#define mAGrw_CEDAR_BLOCK_Z_MIN 0
#define mAGrw_CEDAR_BLOCK_Z_MAX 3 // [min, max)

extern void mAGrw_PrintFossilHaniwa_debug(gfxprint_t* gfxprint);
extern int mAGrw_CheckKabuPeddler();
extern void mAGrw_OrderSetHaniwa();
extern void mAGrw_ChangeItemBlock(mActor_name_t* block_items, mActor_name_t new_item, mActor_name_t target_item, u8 possible_num);
extern void mAGrw_SetXmasTree();
extern void mAGrw_RenewalFgItem(lbRTC_time_c* time);
extern void mAGrw_ChangeTree2FruitTree();
extern void mAGrw_ChangeTree2Cedar();
extern void mAGrw_ChangeCedar2Tree();

#ifdef __cplusplus
}
#endif

#endif
