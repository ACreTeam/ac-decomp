#ifndef M_LIGHTS_H
#define M_LIGHTS_H

#include "types.h"
#include "PR/mbi.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct lightsn_s {
  u8 diffuse_count;
  Lights7 lights;
} LightsN;

#ifdef __cplusplus
}
#endif

#endif
