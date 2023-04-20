#ifndef M_CARD_H
#define M_CARD_H

#include "types.h"
#include "libu64/gfxprint.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mFRm_PrintSavedDebug(gfxprint_t* gfxprint);
extern void mFRm_display_errInfo(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
