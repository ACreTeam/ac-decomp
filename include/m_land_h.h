#ifndef M_LAND_H_H
#define M_LAND_H_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

// Town name character count
#define LAND_NAME_SIZE 8
#define LAND_NAME_MURA_SIZE (LAND_NAME_SIZE + 2)

typedef struct land_info_s {
  u8 name[LAND_NAME_SIZE];
  s8 exists;
  u16 id;
} mLd_land_info_c;

#ifdef __cplusplus
}
#endif

#endif
