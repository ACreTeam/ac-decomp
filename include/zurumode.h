#ifndef ZURUMODE_H
#define ZURUMODE_H

#include "types.h"

#include "dolphin/os.h"
#include "libultra/libultra.h"
#include "JSystem/JUT/JUTAssertion.h"
#include "JSystem/JUT/JUTDbPrint.h"

typedef struct zuru_keycheck_s {
  u8 state;
  u8 progressing;
  u16 last_controller;
  u8 zurumode_enabled;
} zuru_keycheck;

typedef struct { // This needs to be researched and in its corresponding file tbh
    u8 pad_pattern;
    void (*callback)(void*);
    void* callback_param;
    void (*callback2)(void*);
    void* callback2_param;
} padmgr;

extern padmgr padmgr_class;
extern zuru_keycheck zuruKeyCheck;


void zurumode_cleanup(void);
int zerucheck_init(zuru_keycheck* key_check);
void zurumode_update(void);
void zurumode_callback(void* padmgr);
int zerucheck_key_check(zuru_keycheck* key_check, u32 controller);

#define ZURUMODE_RESET 0
#define ZURUMODE_PROGRESSING 1

#define OS_APP_NMI_ZURUMODE_IDX 15


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

#endif