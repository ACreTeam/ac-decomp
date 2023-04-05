#ifndef M_FIELD_INFO_H
#define M_FIELD_INFO_H

#include "types.h"


#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif
