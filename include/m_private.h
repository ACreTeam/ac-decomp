#ifndef M_PRIVATE_H
#define M_PRIVATE_H

#include "types.h"
#include "libu64/gfxprint.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PLAYER_NUM 4

extern s16 mPr_GetGoodsPower();
extern s16 mPr_GetMoneyPower();

extern void mPr_PrintMapInfo_debug(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
