#ifndef M_ITEM_DEBUG_H
#define M_ITEM_DEBUG_H

#include "types.h"
#include "libu64/gfxprint.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
  mItemDebug_CATEGORY_NONE,
  mItemDebug_CATEGORY_FTR,
  mItemDebug_CATEGORY_PPR,
  mItemDebug_CATEGORY_MNY,
  mItemDebug_CATEGORY_TOL,
  mItemDebug_CATEGORY_FSH,
  mItemDebug_CATEGORY_CLT,
  mItemDebug_CATEGORY_ELS,
  mItemDebug_CATEGORY_CPT,
  mItemDebug_CATEGORY_WLL,
  mItemDebug_CATEGORY_FOD,
  mItemDebug_CATEGORY_PLT,
  mItemDebug_CATEGORY_MSC,
  mItemDebug_CATEGORY_DST,
  mItemDebug_CATEGORY_LOT,
  mItemDebug_CATEGORY_IST,
  mItemDebug_CATEGORY_HPY,
  mItemDebug_CATEGORY_KAB,

  mItemDebug_CATEGORY_NUM
};

extern void mItemDebug_ItemDebugMain();
extern void mItemDebug_ItemDebugDraw(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
