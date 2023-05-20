#ifndef M_CONTROLLER_H
#define M_CONTROLLER_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define BUTTON_NONE 0x0000
#define BUTTON_CRIGHT 0x0001
#define BUTTON_CLEFT 0x0002
#define BUTTON_CDOWN 0x0004
#define BUTTON_CUP 0x0008
#define BUTTON_R 0x0010
#define BUTTON_L 0x0020
#define BUTTON_X 0x0040
#define BUTTON_Y 0x0080
#define BUTTON_DRIGHT 0x0100
#define BUTTON_DLEFT 0x0200
#define BUTTON_DDOWN 0x0400
#define BUTTON_DUP 0x0800
#define BUTTON_START 0x1000
#define BUTTON_Z 0x2000
#define BUTTON_B 0x4000
#define BUTTON_A 0x8000

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
