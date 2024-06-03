#ifndef DVDTHREAD_H
#define DVDTHREAD_H

#include "types.h"
#include "dolphin/dvd.h"

typedef void (*Jac_DVDCallback)(u32);

extern s32 DVDT_DRAMtoARAM(u32 owner, u32 dram, u32 aram, u32 len, u32* outLen, Jac_DVDCallback callback);
extern s32 DVDT_ARAMtoDRAM(u32 owner, u32 dram, u32 aram, u32 len, u32* outLen, Jac_DVDCallback callback);
extern u32 Jac_CheckFile(char* path);

#endif
