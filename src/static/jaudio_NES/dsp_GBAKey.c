#include "gba/GBAPriv.h"
#include "dolphin/os/OSAddress.h"
#include "_mem.h"

//TODO: remove this once ipldec is decompiled
extern void Jac_DSPagbDecodeAsync(void*, void*, void (*)(void*));

static s32 F152(DSPTaskInfo* task) {
    s32 chan; // r31
    GBAControl* gba; // r29

    for (chan = 0; chan < 4; chan++) {
        gba = &__GBA[chan];
        if (&gba->task == task) {
            return chan;
        }
    }
    
    (void)((0 <= chan && chan < 4) || (OSPanic(__FILE__, 173, "Failed assertion 0 <= chan && chan < 4"), 0));
    OSPanic(__FILE__, 174, "GBA - unexpected dsp call");
    return -1;
}

static void F25(void* task) {
    s32 chan; // r31

    chan = F152((DSPTaskInfo *)task);
    __GBAX01(chan, 0);
}

void __GBAX02(s32 chan, u8* readbuf) {
    GBAControl* gba = &__GBA[chan]; // r28
    GBABootInfo* bootInfo = &__GBA[chan].bootInfo; // r29
    GBASecParam* param = gba->param; // r30
    DSPTaskInfo* task = &gba->task; // r31

    memcpy(param, readbuf, 4u);
    param->paletteColor = bootInfo->paletteColor;
    param->paletteSpeed = bootInfo->paletteSpeed;
    param->length = bootInfo->length;
    param->out = &param->keyA;
    DCInvalidateRange(&param->keyA, 32);
    DCFlushRange(param, 32);
    Jac_DSPagbDecodeAsync(task, param, F25);
}
