#ifndef PAD_H
#define PAD_H

#include "types.h"
#include "libultra/osContPad.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  OSContPad now;
  OSContPad last;
  OSContPad on;
  OSContPad off;
} pad_t;

#ifdef __cplusplus
}
#endif

#endif
