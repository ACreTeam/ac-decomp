#ifndef M_FLASHROM_H
#define M_FLASHROM_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void mFRm_PrintSavedDebug(gfxprint_t* gfxprint);
extern void mFRm_display_errInfo(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
