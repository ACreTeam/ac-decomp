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


int pad_physical_stick_x(pad_t*);
int pad_physical_stick_y(pad_t*);
void pad_set_logical_stick(pad_t*, int, int);
void pad_correct_stick(pad_t*);

#ifdef __cplusplus
}
#endif

#endif
