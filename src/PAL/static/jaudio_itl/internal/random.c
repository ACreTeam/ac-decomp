#include "jaudio_NES/random.h"

static s32 v0 = 0x0001000;
static s32 v1 = 0x0005555;

#define V0_MULT (s32)0x13579BDE
#define V1_MULT (s32)0x98765432

extern s32 GetRandom_s32(void) {
    s32 tmp;

    tmp = (v1 * V1_MULT) + ((v0 * V0_MULT) >> 4);
    tmp += 1;
    v0 = v1;
    v1 = tmp;
    return tmp;
}

extern f32 GetRandom_sf32(void) {
    s32 rnd = GetRandom_s32();
    f32 rnd_float = (f32)(rnd & 0x00FFFFFF) / (f32)(0x00FFFFFF); /* map to float [0, 1] */

    if (rnd < 0) {
        rnd_float = -rnd_float;
    }

    return rnd_float;
}
