#ifndef CARD_H
#define CARD_H

#include "types.h"
#include "dolphin/card.h"
#include "dolphin/dvd.h"
#include "dolphin/os/OSAlarm.h"
#include "dolphin/os/OSThread.h"
#include "dolphin/dsp.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CARDDir {
    // total size: 0x40
    u8 gameName[4];                 // offset 0x0, size 0x4
    u8 company[2];                  // offset 0x4, size 0x2
    u8 _padding0;                   // offset 0x6, size 0x1
    u8 bannerFormat;                // offset 0x7, size 0x1
    u8 fileName[CARD_FILENAME_MAX]; // offset 0x8, size 0x20
    u32 time;                       // offset 0x28, size 0x4
    u32 iconAddr;                   // offset 0x2C, size 0x4
    u16 iconFormat;                 // offset 0x30, size 0x2
    u16 iconSpeed;                  // offset 0x32, size 0x2
    u8 permission;                  // offset 0x34, size 0x1
    u8 copyTimes;                   // offset 0x35, size 0x1
    u16 startBlock;                 // offset 0x36, size 0x2
    u16 length;                     // offset 0x38, size 0x2
    u8 _padding1[2];                // offset 0x3A, size 0x2
    u32 commentAddr;                // offset 0x3C, size 0x4
} CARDDir;

typedef struct CARDControl {
    // total size: 0x110
    int attached;                // offset 0x0, size 0x4
    s32 result;                  // offset 0x4, size 0x4
    u16 size;                    // offset 0x8, size 0x2
    u16 pageSize;                // offset 0xA, size 0x2
    s32 sectorSize;              // offset 0xC, size 0x4
    u16 cBlock;                  // offset 0x10, size 0x2
    u16 vendorID;                // offset 0x12, size 0x2
    s32 latency;                 // offset 0x14, size 0x4
    u8 id[12];                   // offset 0x18, size 0xC
    int mountStep;               // offset 0x24, size 0x4
    int formatStep;              // offset 0x28, size 0x4
    u32 scramble;                // offset 0x2C, size 0x4
    DSPTaskInfo task;            // offset 0x30, size 0x50
    void* workArea;              // offset 0x80, size 0x4
    CARDDir* currentDir;         // offset 0x84, size 0x4
    u16* currentFat;             // offset 0x88, size 0x4
    OSThreadQueue threadQueue;   // offset 0x8C, size 0x8
    u8 cmd[9];                   // offset 0x94, size 0x9
    s32 cmdlen;                  // offset 0xA0, size 0x4
    u32 mode;                    // offset 0xA4, size 0x4
    int retry;                   // offset 0xA8, size 0x4
    int repeat;                  // offset 0xAC, size 0x4
    u32 addr;                    // offset 0xB0, size 0x4
    void* buffer;                // offset 0xB4, size 0x4
    s32 xferred;                 // offset 0xB8, size 0x4
    u16 freeNo;                  // offset 0xBC, size 0x2
    u16 startBlock;              // offset 0xBE, size 0x2
    CARDFileInfo* fileInfo;      // offset 0xC0, size 0x4
    CARDCallback extCallback;    // offset 0xC4, size 0x4
    CARDCallback txCallback;     // offset 0xC8, size 0x4
    CARDCallback exiCallback;    // offset 0xCC, size 0x4
    CARDCallback apiCallback;    // offset 0xD0, size 0x4
    CARDCallback xferCallback;   // offset 0xD4, size 0x4
    CARDCallback eraseCallback;  // offset 0xD8, size 0x4
    CARDCallback unlockCallback; // offset 0xDC, size 0x4
    OSAlarm alarm;               // offset 0xE0, size 0x28
    u32 cid;                     // offset 0x108, size 0x4
    const DVDDiskID* diskID;     // offset 0x10C, size 0x4
} CARDControl;

s32 __CARDGetStatusEx(s32 chan, s32 fileNo, CARDDir* dirent);
s32 __CARDSetStatusExAsync(s32 chan, s32 fileNo, CARDDir* dirent, CARDCallback callback);
s32 __CARDSetStatusEx(s32 chan, s32 fileNo, CARDDir* dirent);

#ifdef __cplusplus
}
#endif

#endif
