#include "m_room_type.h"
#include "m_name_table.h"

#define FTR_NO_2_FTR_IDX(f) ((f) >> 2)
#define NUM_FTR_IN_TYPE (FTR_NO_2_FTR_IDX(0x1000))

extern int mRmTp_FtrItemNo2FtrIdx(u16 ftr_no) {
  if (ITEM_IS_FTR(ftr_no)) {
    if (ITEM_NAME_GET_TYPE(ftr_no) == NAME_TYPE_FTR0) {
      return FTR_NO_2_FTR_IDX(ftr_no - FTR0_NO_START);
    }
    return FTR_NO_2_FTR_IDX(ftr_no - FTR1_NO_START) + NUM_FTR_IN_TYPE;
  }

  return NULL_NO;
}
