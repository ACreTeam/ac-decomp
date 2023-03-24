#ifndef M_CONTROLLER_H
#define M_CONTROLLER_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(struct controller_s) == 0x38 */
typedef struct controller_s {
  /* 0x00 */ f32 move_pX;
  /* 0x04 */ f32 move_pY;
  /* 0x08 */ f32 move_pR;
  /* 0x0C */ s16 move_angle;

  /* 0x10 */ f32 last_move_pX;
  /* 0x14 */ f32 last_move_pY;
  /* 0x18 */ f32 last_move_pR;
  /* 0x1C */ s16 last_move_angle;

  /* 0x20 */ f32 adjusted_pX;
  /* 0x24 */ f32 adjusted_pY;
  /* 0x28 */ f32 adjusted_pR;
  
  /* 0x2C */ f32 last_adjusted_pX;
  /* 0x30 */ f32 last_adjusted_pY;
  /* 0x34 */ f32 last_adjusted_pR;
} MCON;

#ifdef __cplusplus
}
#endif

#endif
