#ifndef M_LAND_H
#define M_LAND_H

#include "types.h"
#include "m_land_h.h"

#ifdef __cplusplus
extern "C" {
#endif

#define mLd_BITMASK 0x3000
#define mLd_CHECK_ID(id) (((id) & mLd_BITMASK) == mLd_BITMASK)

#define NATIVE 0
#define FOREIGN 1

extern u8* mLd_GetLandName();

#ifdef __cplusplus
}
#endif

#endif
