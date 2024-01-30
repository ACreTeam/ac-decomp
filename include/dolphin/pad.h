#ifndef DOLPHIN_PAD_H
#define DOLPHIN_PAD_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define PAD_CONTROLLER_NUM 4

#define PAD_ERR_NONE           0
#define PAD_ERR_NO_CONTROLLER -1
#define PAD_ERR_NOT_READY     -2
#define PAD_ERR_TRANSFER      -3

#define PAD_MOTOR_STOP 0
#define PAD_MOTOR_RUMBLE 1
#define PAD_MOTOR_STOP_HARD 2

#define PAD_BUTTON_LEFT 0x0001
#define PAD_BUTTON_RIGHT 0x0002
#define PAD_BUTTON_DOWN 0x0004
#define PAD_BUTTON_UP 0x0008
#define PAD_TRIGGER_Z 0x0010
#define PAD_TRIGGER_R 0x0020
#define PAD_TRIGGER_L 0x0040
#define PAD_BUTTON_A 0x0100
#define PAD_BUTTON_B 0x0200
#define PAD_BUTTON_X 0x0400
#define PAD_BUTTON_Y 0x0800
#define PAD_BUTTON_MENU 0x1000
#define PAD_BUTTON_START 0x1000

typedef void (*PADSamplingCallback)(void);

typedef struct PADStatus {
  u16 button;
  s8 stickX;
  s8 stickY;
  s8 substickX;
  s8 substickY;
  u8 triggerLeft;
  u8 triggerRight;
  u8 analogA;
  u8 analogB;
  s8 err;
} PADStatus;

BOOL PADInit();
u32 PADRead(PADStatus *status);
BOOL PADReset(u32 mask);
BOOL PADRecalibrate(u32 mask);
void PADClamp(PADStatus *status);
void PADClampCircle(PADStatus *status);
void PADControlMotor(s32 chan, u32 cmd);
void PADSetSpec(u32 spec);
void PADControlAllMotors(const u32 *cmdArr);
void PADSetAnalogMode(u32 mode);
PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback);

#ifdef __cplusplus
}
#endif

#endif
