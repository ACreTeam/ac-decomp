#ifndef GBAPRIV
#define GBAPRIV

#include "types.h"

#include "GBA/gba.h"
#include "dolphin/os.h"
#include "dolphin/dsp.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*GBATransferCallback)(s32 chan);

typedef struct GBASecParam {
    // total size: 0x40
    u8 readbuf[4]; // offset 0x0, size 0x4
    s32 paletteColor; // offset 0x4, size 0x4
    s32 paletteSpeed; // offset 0x8, size 0x4
    s32 length; // offset 0xC, size 0x4
    u32* out; // offset 0x10, size 0x4
    u8 _padding0[12]; // offset 0x14, size 0xC
    u32 keyA; // offset 0x20, size 0x4
    s32 keyB; // offset 0x24, size 0x4
    u8 _padding1[24]; // offset 0x28, size 0x18
} GBASecParam;

typedef struct GBABootInfo {
    // total size: 0x68
    s32 paletteColor; // offset 0x0, size 0x4
    s32 paletteSpeed; // offset 0x4, size 0x4
    u8* programp; // offset 0x8, size 0x4
    s32 length; // offset 0xC, size 0x4
    u8* status; // offset 0x10, size 0x4
    GBACallback callback; // offset 0x14, size 0x4
    u8 readbuf[4]; // offset 0x18, size 0x4
    u8 writebuf[4]; // offset 0x1C, size 0x4
    int i; // offset 0x20, size 0x4
    OSTick start; // offset 0x24, size 0x4
    OSTime begin; // offset 0x28, size 0x8
    BOOL firstXfer; // offset 0x30, size 0x4
    int curOffset; // offset 0x34, size 0x4
    u32 crc; // offset 0x38, size 0x4
    u32 dummyWord[7]; // offset 0x3C, size 0x1C
    u32 keyA; // offset 0x58, size 0x4
    s32 keyB; // offset 0x5C, size 0x4
    u32 initialCode; // offset 0x60, size 0x4
    int realLength; // offset 0x64, size 0x4
} GBABootInfo;

typedef struct GBAControl {
    // total size: 0x100
    u8 output[5]; // offset 0x0, size 0x5
    u8 input[5]; // offset 0x5, size 0x5
    u32 outputBytes; // offset 0xC, size 0x4
    u32 inputBytes; // offset 0x10, size 0x4
    u8* status; // offset 0x14, size 0x4
    void* ptr; // offset 0x18, size 0x4
    GBACallback callback; // offset 0x1C, size 0x4
    s32 ret; // offset 0x20, size 0x4
    OSThreadQueue threadQueue; // offset 0x24, size 0x8
    OSTime delay; // offset 0x30, size 0x8
    GBATransferCallback proc; // offset 0x38, size 0x4
    GBABootInfo bootInfo; // offset 0x40, size 0x68
    DSPTaskInfo task; // offset 0xA8, size 0x50
    GBASecParam * param; // offset 0xF8, size 0x4
} GBAControl;

extern GBAControl __GBA[4];
extern BOOL __GBAReset;

void __GBAHandler(s32 chan, u32 error, OSContext* context);
void __GBASyncCallback(s32 chan, s32 ret);
s32 __GBASync(s32 chan);
OSTime __GBASetDelay(s32 chan, OSTime delay);
s32 __GBATransfer(s32 chan, u32 outputBytes, u32 inputBytes, GBATransferCallback proc);
void __GBAX01(s32 chan, s32 ret);
// void __GBAX02(s32 chan, u8* readbuf);

#ifdef __cplusplus
}
#endif

#endif
