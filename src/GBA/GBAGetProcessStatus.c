#include "GBA/GBAPriv.h"

s32 GBAGetProcessStatus(s32 chan, u8* percentp) {
  BOOL enabled;
  s32 ret;                        // r29
  GBAControl* gba = &__GBA[chan]; // r25
  GBABootInfo* bootInfo;          // r31
  u8 percent;                     // r30
  OSTime t;                       // r27

  bootInfo = &gba->bootInfo;
  enabled = OSDisableInterrupts();

  if (bootInfo->callback != NULL) {
    ret = 2;
    percent = (bootInfo->curOffset * 100) / bootInfo->realLength;
    if (bootInfo->begin != 0) {
      t = OSGetTime();
      if (OSTicksToMilliseconds(t - bootInfo->begin) < (5500)) {
        percent = ((t - bootInfo->begin) * percent) / OSMillisecondsToTicks((OSTime)5500);
      }

      if (percent >= 100) {
        percent = 100;
      }
    }

    if (percentp != NULL) {
      *percentp = percent;
    }
  } else if (gba->callback != NULL) {
    ret = 2;
  } else {
    ret = 0;
  }

  OSRestoreInterrupts(enabled);
  return ret;
}
