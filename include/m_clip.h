#ifndef M_CLIP_H
#define M_CLIP_H

#include "types.h"
#include "ac_gyoei_h.h"
#include "ac_insect_h.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(Clip_c) == 0x104 */
typedef struct clip_s {
  /* 0x000 */ void* _000[(0x07C - 0x000) / sizeof(void*)];
  /* 0x07C */ aINS_Clip_c* insect_clip;
  /* 0x080 */ void* _080[(0x0AC - 0x080) / sizeof(void*)];
  /* 0x0AC */ aGYO_Clip_c* gyo_clip;
  /* 0x0B0 */ void* _0B0[(0x104 - 0x0B0) / sizeof(void*)];
} Clip_c;

#ifdef __cplusplus
}
#endif

#endif
