#ifndef PAD_H
#define PAD_H

#include "types.h"
#include "libultra/osContPad.h"

#ifdef __cplusplus
extern "C" {
#endif

/* sizeof(pad_t) == 0x18 */
typedef struct {
  /* 0x00 */ OSContPad now;
  /* 0x06 */ OSContPad last;
  /* 0x0C */ OSContPad on;
  /* 0x12 */ OSContPad off;
} pad_t;

#ifdef __cplusplus
}
#endif

#endif
