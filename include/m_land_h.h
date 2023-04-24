#ifndef M_LAND_H_H
#define M_LAND_H_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Town name character count
#define LAND_NAME_SIZE 8
#define LAND_NAME_MURA_SIZE (LAND_NAME_SIZE + 2)

/* sizeof(mLd_land_info_c) == 0x0C */
typedef struct land_info_s {
  /* 0x00 */ u8 name[LAND_NAME_SIZE];
  /* 0x08 */ s8 exists;
  /* 0x0A */ u16 id;
} mLd_land_info_c;

#ifdef __cplusplus
}
#endif

#endif
