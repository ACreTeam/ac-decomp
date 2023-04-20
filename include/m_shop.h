#ifndef M_SHOP_H
#define M_SHOP_H

#include "types.h"
#include "libu64/gfxprint.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mSP_PrintNowShopSalesSum(gfxprint_t* gfxprint);

extern void mItemDebug_ItemDebugMain();
extern void mItemDebug_ItemDebugDraw(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
