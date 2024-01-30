#ifndef KS_NES_COMMON_H
#define KS_NES_COMMON_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define KS_NES_WIDTH 256
#define KS_NES_HEIGHT 228

#define CHR_TO_I8_BUF_SIZE 0x100000
#define KS_NES_NESFILE_HEADER_SIZE 0x10
#define KS_NES_PRGROM_SIZE 0x80000 // 512kb for MMC3
#define KS_NES_CHRROM_SIZE 0x40000 // 256kb for MMC3

#define KS_NES_CHRRAM_SIZE 0x2000 // 8kb
#define KS_NES_BBRAM_SIZE 0x8000 // 32kb, battery backed-up ram
#define KS_NES_NOISE_DATA_SIZE 0x7F000
#define KS_NES_DRAW_RESULT_BUF_SIZE 0x1C800

#define KS_NES_WRAM_SIZE 0x800 // 2kb

#define KS_NES_EMU_STACK_SIZE 0x1000 // 4kb for thread stack

#define KS_NES_BYTES_PER_KB (1024)
#define KS_NES_TO_KB(b) ((f32)b * (1.0f / (f32)KS_NES_BYTES_PER_KB))

typedef struct ksNesCommonWorkPriv {
  /* 0x0000 */ u8 wram[KS_NES_WRAM_SIZE];
  /* 0x0800 */ u8 _0800[0x0B40 - 0x0800];
  /* 0x0B40 */ u8 _0B40[1]; // TODO: figure out what this is and its size
  /* 0x0B41 */ u8 _0B41[0x2A40 - 0x0B41];
  /* 0x2A40 */ u8 _2A40[0x800];
  /* 0x3240 */ u8 _3240[0x8F18 - 0x3240];
} ksNesCommonWorkPriv;

typedef struct ksNesCommonWorkObj {
  /* 0x0000 */ u8* nesromp;
  /* 0x0004 */ u8* noise_bufp;
  /* 0x0008 */ size_t chr_to_i8_buf_size;
  /* 0x000C */ u8* chr_to_u8_bufp;
  /* 0x0010 */ u8* result_bufp;
  /* 0x0014 */ int _0014;
  /* 0x0018 */ int _0018;
  /* 0x001C */ u8 frames;
  /* 0x001D */ u8 _001D;
  /* 0x001E */ u8 _001E;
  /* 0x001F */ u8 _001F;
  /* 0x0020 */ u32 pads[4];
  /* 0x0030 */ u32 _0030;
  /* 0x0034 */ u32 _0034;
  /* 0x0038 */ u32 _0038;
  /* 0x003C */ u8 _003C[0x0048 - 0x003C];
  /* 0x0048 */ size_t prg_size;
  /* 0x004C */ u8 _004C[0x0060 - 0x004C]; 
  /* 0x0060 */ ksNesCommonWorkPriv work_priv;
} ksNesCommonWorkObj;

typedef struct ksNesStateObj {
  /* 0x0000 */ u8 wram[KS_NES_WRAM_SIZE];
  /* 0x0800 */ u8 _0800[0x16B4 - 0x0800];
  /* 0x16B4 */ u32 _16B4;
  /* 0x16BC */ u8 _16B8[0x176D - 0x16B8];
  /* 0x176D */ u8 disk_motor;
  /* 0x176E */ u8 _176E[0x17FC - 0x176E];
  /* 0x17FC */ u8 _17FC[8];
  /* 0x1804 */ u8 _1804[0x1844 - 0x1804];
  /* 0x1844 */ u16 PC;
  /* 0x1846 */ u8 _1846[0x1860 - 0x1846];
  /* 0x1860 */ size_t prg_size;
  /* 0x1864 */ size_t chr_size;
  /* 0x1868 */ u8 _1868[0x1A78 - 0x1868];
} ksNesStateObj;

#ifdef __cplusplus
}
#endif

#endif
