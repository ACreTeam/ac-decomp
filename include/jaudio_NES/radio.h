#ifndef RADIO_H
#define RADIO_H

#include "types.h"

typedef struct radio_ {
    /* 0x000 */ s8 unk0;
    /* 0x004 */ f32 unk4;
    /* 0x008 */ u16 tempo;
} radio;

#ifdef __cplusplus
extern "C" {
#endif

extern s16 Na_GetRadioCounter(radio* radio);

#ifdef __cplusplus
}
#endif


#endif