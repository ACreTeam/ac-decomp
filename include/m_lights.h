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


typedef struct global_light_s {
    /* 0x0 */ void* list;
    /* 0x4 */ u8 ambientColor[3];
    /* 0x7 */ u8 fogColor[3];
    /* 0xA */ s16 fogNear;
    /* 0xC */ s16 fogFar; 
} Global_light;

#ifdef __cplusplus
}
#endif

#endif
