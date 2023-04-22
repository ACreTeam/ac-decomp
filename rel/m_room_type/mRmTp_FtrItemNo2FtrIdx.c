#include "m_room_type.h"

#define FTR_NO_2_FTR_IDX(f) ((f) >> 2)
#define NUM_FTR_IN_TYPE (FTR_NO_2_FTR_IDX(0x1000))
#define IS_FTR(f) ((f) == FG_FTR0_TYPE || (f) == FG_FTR1_TYPE)

extern int mRmTp_FtrItemNo2FtrIdx(u16 ftr_no) {
  int type = GET_FG_TYPE(ftr_no);
  if (IS_FTR(type)) {
    if (type == FG_FTR0_TYPE) {
      return FTR_NO_2_FTR_IDX(ftr_no - FTR0_NO_START);
    }
    return FTR_NO_2_FTR_IDX(ftr_no - FTR1_NO_START) + NUM_FTR_IN_TYPE;
  }

  return NULL_NO;
}
