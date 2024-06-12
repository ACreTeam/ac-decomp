#ifndef DSPBOOT_H
#define DSPBOOT_H

#include "types.h"

typedef struct STRUCT_DSP_TASK2 {
    /* 0x00 */ u16* iram_mmem_addr;
    /* 0x04 */ u32 iram_length;
    /* 0x08 */ u16 iram_addr;
    /* 0x0A */ u16* dram_mmem_addr;
    /* 0x0E */ u32 dram_length;
    /* 0x12 */ u16 dram_addr;
    /* 0x16 */ u16 dsp_init_vector;
}DSPTaskInfo2;

extern s32 __DSPCheckMXICBoot2(DSPTaskInfo2* task);
extern void DSPInit2(DSPTaskInfo2* task);
extern void DspBoot(void);

extern u16 jdsp[];

#endif
