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
  u8 readbuf[4];
  s32 paletteColor;
  s32 paletteSpeed;
  s32 length;
  u32* out;
  u8 _padding0[12];
  u32 keyA;
  s32 keyB;
  u8 _padding1[24];
} GBASecParam;

typedef struct GBABootInfo {
  s32 paletteColor;
  s32 paletteSpeed;
  u8* programp;
  s32 length;
  u8* status;
  GBACallback callback;
  u8 readbuf[4];
  u8 writebuf[4];
  int i;
  OSTick start;
  OSTime begin;
  int firstXfer;
  int curOffset;
  u32 crc;
  u32 dummyWord[7];
  u32 keyA;
  s32 keyB;
  u32 initialCode;
  int realLength;
} GBABootInfo;

typedef struct GBAControl {
  u8 output[5];
  u8 input[5];
  s32 outputBytes;
  s32 inputBytes;
  u8* status;
  u8* ptr;
  GBACallback callback;
  s32 ret;
  OSThreadQueue threadQueue;
  OSTime delay;
  GBATransferCallback proc;
  GBABootInfo bootInfo;
  DSPTaskInfo task;
  GBASecParam* param;
} GBAControl;

extern GBAControl __GBA[4];
extern BOOL __GBAReset;

void __GBAHandler(s32 chan, u32 error, OSContext* context);
void __GBASyncCallback(s32 chan, s32 ret);
s32 __GBASync(s32 chan);
OSTime __GBASetDelay(s32 chan, OSTime delay);
s32 __GBATransfer(s32 chan, s32 w1, s32 w2, GBATransferCallback callback);

#ifdef __cplusplus
}
#endif

#endif
