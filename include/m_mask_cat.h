#ifndef M_MASK_CAT_H
#define M_MASK_CAT_H

#include "types.h"
#include "m_needlework.h"
#include "m_time.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct mask_cat_s {
  mNW_original_design_c design;
  u8 palette_no;
  u8 cloth_no;
  u8 talk_idx;
  lbRTC_time_c time;
} MaskCat_c;

#ifdef __cplusplus
}
#endif

#endif
