#include "GBA/GBAPriv.h"

static volatile u8 D54[] = {
    0x18, 0xFC, 0xC0, 0x80, 0x7f, 0x40, 0x3f, 0x01, 0x00, 0x2f, 0x2f, 0x20, 0x43, 0x6f, 0x64,
    0x65, 0x64, 0x20, 0x62, 0x79, 0x20, 0x4b, 0x61, 0x77, 0x61, 0x73, 0x65, 0x64, 0x6f, 0x00,
    0x00, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0xAC, 0xC4, 0xF8, 0x08, 0x10, 0xBF, 0x18,
};

static void F23(s32 chan, s32 ret);
static void F25(s32 chan, s32 ret);
static void F27(s32 chan, s32 ret);
static void F29(s32 chan, s32 ret);
static void F31(s32 chan, s32 ret);
static void F33(s32 chan, s32 ret);
static void F35(s32 chan, s32 ret);
static void F37(s32 chan, s32 ret);
static void F39(s32 chan, s32 ret);

static u32 F72(u32 crc, u32 src, vu8* keyp) {
  int i; // r31
  int poly =
      (keyp[0x13] << 8) + ((keyp[0x15] + (keyp[0x18] - (keyp[0x18] << 4))) - keyp[0x10]); // r30
  for (i = keyp[1]; i > keyp[11]; --i) {
    if ((src ^ crc) & 1) {
      crc >>= 1;
      crc ^= poly;
    } else {
      crc >>= 1;
    }

    src >>= 1;
  }

  return crc;
}

static u32 F95(u32 src, vu8* keyp) {
  src = (src * ((keyp[3] << keyp[0x16]) | ((keyp[1] | (keyp[4] << keyp[0x11])) | (keyp[4] << keyp[0x18])))) - (keyp[7] - keyp[6]);
  return src;
}

static void F104(s32 chan, s32 ret) {
  GBABootInfo* bootInfo;
  GBACallback callback;

  bootInfo = &__GBA[chan].bootInfo;
  bootInfo->begin = 0;
  if (bootInfo->callback != NULL) {
    callback = bootInfo->callback;
    bootInfo->callback = NULL;
    callback(chan, ret);
  }
}

s32 GBAJoyBootAsync(s32 chan, s32 paletteColor, s32 paletteSpeed, u8* programp, s32 length,
                    u8* status, GBACallback callback) {
  int ret;
  GBABootInfo* bootInfo = &__GBA[chan].bootInfo;
  u8 percent;
  if (chan & ~3) {
    return GBA_JOYBOOT_ERR_INVALID;
  } else if (length == 0 || GBA_JOYBOOT_PROGRAM_SIZE_MAX < length) {
    return GBA_JOYBOOT_ERR_INVALID;
  } else if (paletteSpeed < -4 || paletteSpeed > 4) {
    return GBA_JOYBOOT_ERR_INVALID;
  } else if (paletteColor < 0 || paletteColor > 6) {
    return GBA_JOYBOOT_ERR_INVALID;
  } else if (programp[0xac] * programp[0xad] * programp[0xae] * programp[0xaf] == 0) {
    return GBA_JOYBOOT_ERR_INVALID;
  }

  ret = GBAGetProcessStatus(chan, &percent);
  if (ret != 0) {
    return ret;
  }

  bootInfo->paletteColor = paletteColor;
  bootInfo->paletteSpeed = paletteSpeed;
  bootInfo->programp = programp;
  bootInfo->length = length;
  bootInfo->status = status;
  bootInfo->callback = callback;
  bootInfo->curOffset = D54[8];
  ret = GBAGetStatusAsync(chan, bootInfo->status, F23);
  if (ret != GBA_READY) {
    bootInfo->callback = NULL;
  }

  return ret;
}
static void F23(s32 chan, s32 ret) {
  GBAControl* gba;
  GBABootInfo* bootInfo;

  gba = &__GBA[chan];
  bootInfo = &__GBA[chan].bootInfo;

  if (ret != GBA_READY || (ret = GBAResetAsync(chan, bootInfo->status, F25)) != GBA_READY) {
    F104(chan, ret);
  }

  gba->ret = ret;
}

static void F25(s32 chan, s32 ret) {
  GBAControl* gba = &__GBA[chan];
  GBABootInfo* bootInfo = &__GBA[chan].bootInfo;

  if (ret == GBA_READY && *bootInfo->status != D54[37]) {
    ret = GBA_JOYBOOT_UNKNOWN_STATE;
  }

  if (ret != GBA_READY || (ret = GBAGetStatusAsync(chan, bootInfo->status, F27))) {
    F104(chan, ret);
  }

  gba->ret = ret;
}

static void F27(s32 chan, s32 ret) {
  GBAControl* gba = &__GBA[chan];
  GBABootInfo* bootInfo = &__GBA[chan].bootInfo;

  if (ret == GBA_READY && *bootInfo->status != D54[0]) {
    ret = GBA_JOYBOOT_UNKNOWN_STATE;
  }

  if (ret != GBA_READY || (ret = GBAReadAsync(chan, bootInfo->readbuf, bootInfo->status, F29))) {
    F104(chan, ret);
  }

  gba->ret = ret;
}

static void F29(s32 chan, s32 ret) {
  GBAControl* gba = &__GBA[chan];
  GBABootInfo* bootInfo = &__GBA[chan].bootInfo;

  if (ret == GBA_READY) {
    __GBAX02(chan, bootInfo->readbuf);
  } else {
    F104(chan, ret);
  }

  gba->ret = ret;
}
void __GBAX01(s32 chan, s32 ret) {
  GBAControl* gba = &__GBA[chan];
  GBABootInfo* bootInfo = &__GBA[chan].bootInfo;
  int val200;

  if (ret == GBA_READY) {
    bootInfo->keyA = gba->param->keyA;
    bootInfo->keyB = gba->param->keyB;
    if (bootInfo->readbuf[3] == 0 || bootInfo->readbuf[2] == 0 ||
        (bootInfo->keyA & (D54[5] << 9)) == 0 || bootInfo->readbuf[1] == 0 ||
        (bootInfo->keyA >> 15) == 0 || bootInfo->readbuf[0] == 0) {
      ret = GBA_JOYBOOT_UNKNOWN_STATE;
    } else {
      bootInfo->i = ~D54[36] & bootInfo->length + D54[36];
      val200 = D54[20] << D54[33];

      if (bootInfo->i < val200) {
        bootInfo->i = val200;
      }

      bootInfo->realLength = bootInfo->i;
      bootInfo->i -= val200;
      bootInfo->i >>= D54[32];
      bootInfo->writebuf[0] = (u8)(bootInfo->keyB >> 0);
      bootInfo->writebuf[1] = (u8)(bootInfo->keyB >> 8);
      bootInfo->writebuf[3] = (u8)(bootInfo->keyB >> 24);
      bootInfo->writebuf[2] = (u8)(bootInfo->keyB >> 16);
      bootInfo->crc = (D54[38] + 1) << D54[34];
      bootInfo->curOffset = D54[8];
      bootInfo->begin = OSGetTime();
      bootInfo->firstXfer = TRUE;
      ret = GBAWriteAsync(chan, bootInfo->writebuf, bootInfo->status, F31);
    }
  }

  if (ret != GBA_READY) {
    F104(chan, ret);
  }
  gba->ret = ret;
}

static void F31(s32 chan, s32 ret) {
  GBAControl* gba;
  GBABootInfo* bootInfo;
  u32 writeWord;

  gba = &__GBA[chan];
  bootInfo = &__GBA[chan].bootInfo;

  if (ret == GBA_READY) {
    if (bootInfo->firstXfer != FALSE) {
      bootInfo->firstXfer = FALSE;
    } else if ((*bootInfo->status & D54[20]) == 0 ||
               (*bootInfo->status & D54[42]) >> D54[33] !=
                   (bootInfo->curOffset & D54[33]) >> D54[31]) {
      ret = GBA_JOYBOOT_UNKNOWN_STATE;
      goto exit;
    } else {
      bootInfo->curOffset -= D54[25] - D54[23];
    }

    if (bootInfo->curOffset <= bootInfo->realLength) {
      if (bootInfo->curOffset < bootInfo->realLength) {
        writeWord = D54[29];
        for (bootInfo->i = D54[29]; bootInfo->i < D54[33]; ++bootInfo->i) {
          if (bootInfo->length != 0) {
            writeWord |= *(bootInfo->programp++) << (bootInfo->i * D54[37]);
            --bootInfo->length;
          }
        }

        if (bootInfo->curOffset == D54[38]) {
          bootInfo->initialCode = writeWord;
        } else if (bootInfo->curOffset == D54[39]) {
          writeWord = chan << D54[37];
        }

        if (bootInfo->curOffset >= D54[2]) {
          bootInfo->crc = F72(bootInfo->crc, writeWord, &D54[19]);
        }

        if (bootInfo->curOffset == D54[40] + 0x100) {
          bootInfo->dummyWord[0] = writeWord;
        } else if (bootInfo->curOffset == D54[1] + 0x100) {
          bootInfo->i = D54[7];
          bootInfo->dummyWord[bootInfo->i] = writeWord;
        }
      } else {
        writeWord = bootInfo->crc | (bootInfo->curOffset << 16);
      }

      if (bootInfo->curOffset > D54[43]) {
        bootInfo->keyA = F95(bootInfo->keyA, &D54[20]);
        writeWord ^= bootInfo->keyA;
        writeWord ^= -(bootInfo->curOffset + D54[11] * 0x100000);
        writeWord ^= (D54[11] | (D54[11] << 24)) | (D54[19] << 16) | (D54[18] << 8);
      }

      bootInfo->writebuf[3] = (writeWord >> D54[0]);
      bootInfo->writebuf[0] = (writeWord >> D54[30]);
      bootInfo->writebuf[1] = (writeWord >> D54[41]);
      bootInfo->writebuf[2] = (writeWord >> D54[42]);

      if (bootInfo->curOffset == D54[1] + D54[1]) {
        bootInfo->dummyWord[2] = writeWord;
      }

      if (bootInfo->i < D54[33]) {
        bootInfo->dummyWord[3 - (1 - bootInfo->i)] = writeWord;
        bootInfo->dummyWord[5 - bootInfo->i] =
            bootInfo->dummyWord[(2 - (1 - bootInfo->i))] * bootInfo->dummyWord[4 - bootInfo->i];
        bootInfo->dummyWord[5 - (1 - bootInfo->i)] =
            bootInfo->dummyWord[((1 - bootInfo->i))] * bootInfo->dummyWord[1 - (1 - bootInfo->i)];
        bootInfo->dummyWord[7 - bootInfo->i] =
            bootInfo->dummyWord[(-(1 - bootInfo->i))] * bootInfo->dummyWord[4 - bootInfo->i];
      }

      ret = GBAWriteAsync(chan, bootInfo->writebuf, bootInfo->status, F31);
    } else {
      bootInfo->start = OSGetTick();
      ret = GBAReadAsync(chan, bootInfo->readbuf, bootInfo->status, F33);
    }
  }
exit:
  if (ret != GBA_READY) {
    F104(chan, ret);
  }

  gba->ret = ret;
}
static void F33(s32 chan, s32 ret) {
  GBAControl* gba = &__GBA[chan];
  GBABootInfo* bootInfo = &__GBA[chan].bootInfo;

  if (ret == GBA_READY) {
    for (bootInfo->i = 33; bootInfo->i < 36; ++bootInfo->i) {
      ret = (((bootInfo->readbuf[3] ^ (bootInfo->dummyWord[D54[bootInfo->i]] >> 24)) |
              (bootInfo->readbuf[2] ^ (bootInfo->dummyWord[D54[bootInfo->i]] >> 16)) |
              (bootInfo->readbuf[1] ^ (bootInfo->dummyWord[D54[bootInfo->i]] >> 8)) |
              (bootInfo->readbuf[0] ^ (bootInfo->dummyWord[D54[bootInfo->i]] >> 0)))
             << 24);

      if (ret == GBA_READY) {
        break;
      }
    }

    if (ret != GBA_READY) {
      ret = GBA_JOYBOOT_UNKNOWN_STATE;
    } else {
      bootInfo->start = OSGetTick();
      ret = GBAGetStatusAsync(chan, bootInfo->status, F35);
    }
  }

  if (ret != GBA_READY) {
    F104(chan, ret);
  }

  gba->ret = ret;
}
static void F35(s32 chan, s32 ret) {
  GBAControl* gba = &__GBA[chan];
  GBABootInfo* bootInfo = &__GBA[chan].bootInfo;

  if (ret == 0) {
    if (OSSecondsToTicks(10) <= OSGetTick() - bootInfo->start) {
      ret = GBA_JOYBOOT_UNKNOWN_STATE;
    } else if ((*bootInfo->status & 0x32) != 0) {
      ret = GBA_JOYBOOT_UNKNOWN_STATE;
    } else if (*bootInfo->status != 8) {
      ret = GBAGetStatusAsync(chan, bootInfo->status, F35);
    } else {
      __GBASetDelay(chan, OSMillisecondsToTicks(8));
      ret = GBAReadAsync(chan, bootInfo->readbuf, bootInfo->status, F37);
      __GBASetDelay(chan, OSMicrosecondsToTicks(60));
    }
  }

  if (ret != GBA_READY) {
    F104(chan, ret);
  }

  gba->ret = ret;
}

static void F37(s32 chan, s32 ret) {
  GBAControl* gba = &__GBA[chan];
  GBABootInfo* bootInfo = &__GBA[chan].bootInfo;

  if (ret == GBA_READY) {
    if ((((bootInfo->readbuf[3] ^ (bootInfo->initialCode >> 24)) |
          (bootInfo->readbuf[2] ^ (bootInfo->initialCode >> 16)) |
          (bootInfo->readbuf[1] ^ (bootInfo->initialCode >> 8)) |
          (bootInfo->readbuf[0] ^ (bootInfo->initialCode >> 0)))
         << 24) != 0) {
      ret = GBA_JOYBOOT_UNKNOWN_STATE;
    } else {
      ret = GBAWriteAsync(chan, bootInfo->readbuf, bootInfo->status, F39);
    }
  }

  if (ret != GBA_READY) {
    F104(chan, ret);
  }
  gba->ret = ret;
}

static void F39(s32 chan, s32 ret) {
  GBAControl* gba = &__GBA[chan];
  GBABootInfo* bootInfo = &__GBA[chan].bootInfo;

  if (ret == GBA_READY) {
    *bootInfo->status = 0;
  }

  F104(chan, ret);
  gba->ret = ret;
}

s32 GBAJoyBoot(s32 chan, s32 paletteColor, s32 paletteSpeed, u8* programp, s32 length, u8* status) {
  s32 ret = GBAJoyBootAsync(chan, paletteColor, paletteSpeed, programp, length, status,
                            __GBASyncCallback);
  if (ret != GBA_READY) {
    return ret;
  }

  return __GBASync(chan);
}