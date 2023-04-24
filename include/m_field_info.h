#ifndef M_FIELD_INFO_H
#define M_FIELD_INFO_H

#include "types.h"
#include "libu64/gfxprint.h"


#ifdef __cplusplus
extern "C" {
#endif

#define UT_X_NUM 16 /* Spaces per block (acre) in x direction */
#define UT_Z_NUM 16 /* Spaces per block (acre) in z direction */

/* Not sure about these other than the island one */
enum {
  mFI_CLIMATE_0,
  mFI_CLIMATE_ISLAND,
  mFI_CLIMATE_2,
  mFI_CLIMATE_3,
  mFI_CLIMATE_4,
  mFI_CLIMATE_5,
  mFI_CLIMATE_NUM
};

extern int mFI_GetClimate();

extern void mFI_PrintNowBGNum(gfxprint_t* gfxprint);
extern void mFI_PrintFgAttr(gfxprint_t* gfxprint);

#ifdef __cplusplus
}
#endif

#endif
