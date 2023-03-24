/* This file is fabriacted. These structs are in a unified file in N64 SDK. */

#ifndef OS_CONT_PAD
#define OS_CONT_PAD

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAXCONTROLLERS 4

typedef struct {
  u16 type;
  u8 status;
  u8 errno;
} OSContStatus;

typedef struct {
  u16 button;
  s8 stick_x;
  s8 stick_y;
  u8 errno;
} OSContPad;

#ifdef __cplusplus
}
#endif

#endif
