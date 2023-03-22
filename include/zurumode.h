#ifndef ZURUMODE_H
#define ZURUMODE_H

#include "types.h"

#include "dolphin/os.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct zuru_keycheck {
  u8 state;
  u8 progressing;
  u16 last_controller;
  u8 zurumode_enabled;
} zuru_keycheck;

extern s32 zurumode_flag;

extern void zurumode_cleanup(void);
extern void zurumode_init(void);

#define ZURUMODE_RESET 0
#define ZURUMODE_PROGRESSING 1

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

enum zurumode_stage {
  ZURUMODE_STAGE_BEGIN_e = 0,

  ZURUMODE_STAGE_0_e = ZURUMODE_STAGE_BEGIN_e,
  ZURUMODE_STAGE_1_e,
  ZURUMODE_STAGE_2_e,
  ZURUMODE_STAGE_3_e,
  ZURUMODE_STAGE_4_e,
  ZURUMODE_STAGE_5_e,
  ZURUMODE_STAGE_6_e,
  ZURUMODE_STAGE_7_e,
  ZURUMODE_STAGE_8_e,
  ZURUMODE_STAGE_9_e,
  ZURUMODE_STAGE_91_e = 91,
  ZURUMODE_STAGE_92_e = 92,
  ZURUMODE_STAGE_10_e = 10,
  ZURUMODE_STAGE_11_e,

  ZURUMODE_STAGE_FINAL_e = ZURUMODE_STAGE_11_e
};

#ifdef __cplusplus
}
#endif

#endif