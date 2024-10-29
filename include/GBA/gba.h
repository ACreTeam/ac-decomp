#ifndef GBA
#define GBA

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define GBA_CHAN0 0
#define GBA_CHAN1 1
#define GBA_CHAN2 2
#define GBA_CHAN3 3
#define GBA_MAX_CHAN 4

#define GBA_ALL_KEY_MASK 0x03FF
#define GBA_A_BUTTON 0x0001
#define GBA_B_BUTTON 0x0002
#define GBA_SELECT_BUTTON 0x0004
#define GBA_START_BUTTON 0x0008
#define GBA_R_KEY 0x0010
#define GBA_L_KEY 0x0020
#define GBA_U_KEY 0x0040
#define GBA_D_KEY 0x0080
#define GBA_R_BUTTON 0x0100
#define GBA_L_BUTTON 0x0200

#define GBA_JSTAT_MASK 0x3A
#define GBA_JSTAT_FLAGS_SHIFT 4
#define GBA_JSTAT_FLAGS_MASK 0x30
#define GBA_JSTAT_PSF1 0x20
#define GBA_JSTAT_PSF0 0x10
#define GBA_JSTAT_SEND 0x08
#define GBA_JSTAT_RECV 0x02

#define GBA_READY 0
#define GBA_NOT_READY 1
#define GBA_BUSY 2
#define GBA_JOYBOOT_UNKNOWN_STATE 3
#define GBA_JOYBOOT_ERR_INVALID 4

#define GBA_JOYBOOT_PROGRAM_SIZE_MAX 0x40000

#define GBA_JOYBOOT_BOOTPARAM_OFFSET 0xC8
#define GBA_JOYBOOT_BOOTPARAM_SIZE 0x18

typedef void (*GBACallback)(s32 chan, s32 ret);

void GBAInit(void);
s32 GBAGetStatus(s32 chan, u8* status);
s32 GBAGetStatusAsync(s32 chan, u8* status, GBACallback callback);
s32 GBAReset(s32 chan, u8* status);
s32 GBAResetAsync(s32 chan, u8* status, GBACallback callback);
s32 GBAGetProcessStatus(s32 chan, u8* percentp);
s32 GBARead(s32 chan, u8* dst, u8* status);
s32 GBAReadAsync(s32 chan, u8* dst, u8* status, GBACallback callback);
s32 GBAWrite(s32 chan, u8* src, u8* status);
s32 GBAWriteAsync(s32 chan, u8* src, u8* status, GBACallback callback);
s32 GBAJoyBoot(s32 chan, s32 palette_color, s32 palette_speed, u8* programp, s32 length,
               u8* status);
s32 GBAJoyBootAsync(s32 chan, s32 palette_color, s32 palette_speed, u8* programp, s32 length,
                    u8* status, GBACallback callback);

#ifdef __cplusplus
}
#endif

#endif
