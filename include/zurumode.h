#ifndef ZURUMODE_H
#define ZURUMODE_H

#include "types.h"
#include "m_controller.h"
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

#define ZURUMODE_ENABLED() (zurumode_flag >= 1)
#define ZURUMODE2_ENABLED() (zurumode_flag >= 2)

#ifdef __cplusplus
}
#endif

#endif
