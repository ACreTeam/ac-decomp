#ifndef KS_NES_COMMON_H
#define KS_NES_COMMON_H

#include "types.h"
#include "dolphin/os/OSTime.h"

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
#define KS_NES_BBRAM_SIZE 0x8000  // 32kb, battery backed-up ram
#define KS_NES_NOISE_DATA_SIZE 0x7F000
#define KS_NES_DRAW_RESULT_BUF_SIZE 0x1C800

#define KS_NES_WRAM_SIZE 0x800 // 2kb

#define KS_NES_EMU_STACK_SIZE 0x1000 // 4kb for thread stack

#define KS_NES_BYTES_PER_KB (1024)
#define KS_NES_TO_KB(b) ((f32)b * (1.0f / (f32)KS_NES_BYTES_PER_KB))

typedef struct ksNesCommonWorkPriv {
    /* 0x0000 */ u8 wram[KS_NES_WRAM_SIZE];
    /* 0x0800 */ u8 _0800[0x340];
    /* 0x0B40 */ u8* _0B40[0x7c0];
    /* 0x2A40 */ u8 _2A40[0x800];
    /* 0x3240 */ u8 _3240[0x5cd8];
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
    /* 0x0800 */ u8 _0800[0x800];
    /* 0x0800 */ u8 _1000[0x520];
    // these are all function pointers.
    // leaving these as void pointers until we figure out the function signature.
    /* 0x1520 */ void* store_ppu_func[8];   // ksNesStorePPUFuncTblDefault
    /* 0x1540 */ void* store_io_func[0x28]; // ksNesStoreIOFuncTblDefault
    /* 0x15E0 */ void* store_func[8];       // ksNesStoreFuncTblDefault
    /* 0x1600 */ void* load_func[8];        // ksNesLoadFuncTblDefault
    /* 0x1620 */ void* load_io_func[0x18];  // ksNesLoadIOFuncTblDefault
    /* 0x1680 */ u8* cpu_0000_1fff;         // work RAM and its mirrors
    /* 0x1684 */ u8* cpu_2000_3fff;         // PPU registers and their mirrors
    /* 0x1688 */ u8* cpu_4000_5fff;         // APU registers, I/O registers, and usually unmapped cartridge addresses
    /* 0x168C */ u8* cpu_6000_7fff;         // usually battery backed cartridge RAM
    /* 0x1690 */ u8* cpu_8000_9fff;         // usually cartridge ROM and mapper registers
    /* 0x1694 */ u8* cpu_a000_bfff;         // usually cartridge ROM and mapper registers
    /* 0x1698 */ u8* cpu_c000_dfff;         // usually cartridge ROM and mapper registers
    /* 0x169C */ u8* cpu_e000_ffff;         // usually cartridge ROM and mapper registers
    /* 0x16A0 */ u8 _16A0[8];
    /* 0x16A8 */ u8 _16A8[8];
    /* 0x16B0 */ u8 _16B0;
    /* 0x16B1 */ u8 _16B1;
    /* 0x16B2 */ u8 _16B2;
    /* 0x16B3 */ u8 _16B3;
    /* 0x16B4 */ u32 _16B4;
    /* 0x16B8 */ u8 _16B8[8];
    /* 0x16C0 */ u32 _16C0;
    /* 0x16C4 */ u8 _16C4[8];
    /* 0x16CC */ u8 _16CC[0x80];
    /* 0x174C */ u8 _174C[0x18];
    /* 0x1764 */ u8 mapper;
    /* 0x1765 */ u8 prg_banks;  // init to number of 8k PRG banks - 1. might indicate currently selected bank
    /* 0x1766 */ u16 chr_banks; // init to number of 1k CHR banks - 1. might indicate currently selected bank
    /* 0x1768 */ u8 _1768[5];
    /* 0x176D */ u8 disk_motor;
    /* 0x176E */ u8 _176E[0x40]; // MMC5 registers?
    /* 0x17AE */ u16 _17AE;      // APU frame counter LFSR?
    /* 0x17B0 */ u8 _17B0[0x40]; // TODO not an array
    /* 0x17F0 */ u8* prgromp;    // pointer to the start of PRG ROM?
    /* 0x17F4 */ u8* chrramp;    // pointer to the end of PRG ROM?
    /* 0x17F8 */ u8* bbramp;     // pointer to battery backed RAM?
    /* 0x17FC */ u8 _17FC[8];
    /* 0x1804 */ u8 _1804[0xC];
    /* 0x1810 */ u8* _1810[4];
    /* 0x1820 */ s16 _1820; // this appears to be a u16
    /* 0x1822 */ s16 _1822;
    /* 0x1824 */ s16 _1824;
    /* 0x1826 */ s16 _1826;
    /* 0x1828 */ u16 _1828; // APU frame counter LFSR?
    /* 0x182A */ u16 _182A;
    /* 0x182C */ u8 _182C;
    /* 0x182C */ u8 _182D;
    /* 0x182E */ u8 _182E;
    /* 0x182F */ u8 _182F;
    /* 0x1830 */ u8 _1830;
    /* 0x1831 */ u8 _1831;
    /* 0x1832 */ u16 _1832;
    /* 0x1834 */ u8 _1834;
    /* 0x1835 */ u8 _1835;
    /* 0x1836 */ u16 _1836;
    /* 0x1838 */ u16 _1838;
    /* 0x183A */ u16 _183A;
    /* 0x183C */ u16 _183C;
    /* 0x183E */ u16 _183E;
    /* 0x1840 */ void* _1840; // some sort of function pointer with the same signature as ksNesStoreFuncXxxTblDefault
    /* 0x1844 */ u16 PC;
    // /* 0x1846 */ u8 A; //
    // /* 0x1847 */ u8 X; // ?
    // /* 0x1848 */ u8 Y; // ?
    /* 0x1846 */ u8 _1846[0x12];
    /* 0x1858 */ u32 reset_flags; // this should probably be defined as an enum.
    /* 0x185C */ u32 frame_flags; // this should probably be defined as an enum.
    /* 0x1860 */ size_t prg_size; // PRG size in bytes
    /* 0x1864 */ size_t chr_size; // CHR size in bytes
    /* 0x1868 */ u8* nesromp;
    /* 0x186C */ u8* _186C[0x18]; // this holds pointers to ksNesStateObj._0800
    /* 0x18CC */ u8 _18CC[0x1C];
    /* 0x18E8 */ u8 palette_normal[0x80]; // ksNesPaletteNormal
    /* 0x1968 */ u8 _1968[0x108];
    /* 0x1A70 */ u32 _1A70;
    /* 0x1A74 */ OSTick os_tick;
} ksNesStateObj;

#ifdef __cplusplus
}
#endif

#endif
