#include "gba/GBAPriv.h"
#include "dolphin/dsp.h"

static s32 F152(DSPTaskInfo* task) {
    s32 chan; // r31
    GBAControl* gba = &__GBA[chan]; // r29

    for (chan = 0; chan < 4; chan++) {
        if (&gba->task == task) {
            return chan;
        }
    }
    
    ASSERTLINE(168, 0 <= chan && chan < 4);
    ASSERTMSGLINE(169, FALSE, "GBA - unexpected dsp call");
    return -1;
}

void __GBAX02(s32 chan, u8* readbuf) {
    
}
