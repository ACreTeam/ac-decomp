#ifndef M_MASK_CAT_H
#define M_MASK_CAT_H

#include "types.h"
#include "m_needlework.h"
#include "m_time.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mMC_TALK_IDX_MAX 10

typedef struct mask_cat_data_s {
  /* 0x000 */ PersonalID_c creator_pid;
  /* 0x020 */ mNW_original_tex_c design; /* this is aligned to 32 bytes for ARAM transfer */
} mMC_design_c;

typedef struct mask_cat_s {
  mMC_design_c design;
  u8 palette_no;
  u8 cloth_no;
  u8 talk_idx;
  lbRTC_time_c time;
} MaskCat_c;

#ifdef __cplusplus
}
#endif

#endif
