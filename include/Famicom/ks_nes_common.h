#ifndef KS_NES_COMMON_H
#define KS_NES_COMMON_H

#include "types.h"
#include "dolphin/os/OSTime.h"
#include "libultra/libultra.h"
#include <dolphin/mtx.h>

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
#define KS_NES_PPU_NAMETABLE_RAM_SIZE 0x800 // 2kb

#define KS_NES_EMU_STACK_SIZE 0x1000 // 4kb for thread stack

#define KS_NES_BYTES_PER_KB (1024)
#define KS_NES_TO_KB(b) ((f32)b * (1.0f / (f32)KS_NES_BYTES_PER_KB))

#define KS_NES_PPU_STATUS_FLG_SPRITE_OVERFLOW (1 << 5)
#define KS_NES_PPU_STATUS_FLG_SPRITE_ZERO_HIT (1 << 6)
#define KS_NES_PPU_STATUS_FLG_VBLANK (1 << 7)

// Timer IRQ control register @ 0x4022
#define KS_NES_FDS_TIMER_CTRL_FLG_IRQ_REPEAT (1 << 0) // 0 = don't repeat, 1 = repeat
#define KS_NES_FDS_TIMRE_CTRL_FLG_IRQ_ENABLE (1 << 1) // 0 = disabled, 1 = enabled

// Master IO register @ 0x4023
#define KS_NES_FDS_MASTER_IO_FLG_ENABLE_DISK_REGS (1 << 0) // enable disk I/O registers
#define KS_NES_FDS_MASTER_IO_FLG_ENABLE_SOUND_REGS (1 << 1) // enable sound I/O registers

// FDS Control register @ 0x4025
#define KS_NES_FDS_CTRL_FLG_TRANSFER_RESET (1 << 0) // 1 = reset transfer timing state
#define KS_NES_FDS_CTRL_FLG_MOTOR (1 << 1) // 0 = start, 1 = stop
#define KS_NES_FDS_CTRL_FLG_TRANSFER_MODE (1 << 2) // 0 = write, 1 = read
#define KS_NES_FDS_CTRL_FLG_NAMETABLE_MODE (1 << 3) // 0 = horizontal (vertical mirroring), 1 = vertical (horizontal mirroring)
#define KS_NES_FDS_CTRL_FLG_CRC_TRANSFER (1 << 4) // 1 = transfer CRC value
#define KS_NES_FDS_CTRL_FLG_5 (1 << 5)// unknown, NESDev says it's always 1
#define KS_NES_FDS_CTRL_FLG_CRC_ENABLE (1 << 6) // 0 = disable/reset, 1 = enable
#define KS_NES_FDS_CTRL_FLG_INTERRUPT_ENABLE (1 << 7) // 1 = generate IRQ every time byte transfer flag is raised

typedef struct _0B40_struct {
    u8* _00;
    u8* _04;
    // u8* _08;
    u8 _08[4]; // idk how many elements this should be
    u32 _0C;
    u32 _10;
    u32 _14;
    u8 _18;
    u8 _19;
    u8 _1A;
    u8 _1B;
    u8 _1C;
    u8 _1D;
    u8 _1E;
    u8 _1F;
} B40_struct; // size == 0x20

typedef struct _0340_struct {
    u8 _00[0x20];
} _0340_struct; // size = 0x20

typedef struct ksNesCommonWorkPriv {
    /* 0x0000 */ u8 _0000[0x200];
    /* 0x0200 */ u8 _0200[0xF0];
    /* 0x02F0 */ u8 _pad_02F0[0x10];
    /* 0x0300 */ u8 _0300[0x40];
    /* 0x0340 */ _0340_struct _0340[0x40];
    /* 0x0B40 */ B40_struct _0B40[240];
    /* 0x2940 */ u8 _2940[0x100];
    /* 0x2A40 */ u8 _2A40[0x800];
    /* 0x3240 */ u8 _3240[0x4800];
    /* 0x7840 */ u8 _7840[0x1400];
    /* 0x8E40 */ u8 _8E40[0x80]; // 4x16 texture IA8
    /* 0x8EC0 */ u8 _8EC0[0x28]; // 8x4 texture IA8
    /* 0x8EE8 */ Mtx34 draw_mtx;
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
    /* 0x0800 */ u8 ppu_nametable_ram[KS_NES_PPU_NAMETABLE_RAM_SIZE];
    /* 0x1000 */ u8 cartridge_nametable_ram[28];
    /* 0x101C */ u8 primary_oam[0x100];
    /* 0x111C */ u8 _pad[4]; // this might not exist and instead the next member might be ATTRIBUTE_ALIGN(16/32)
    /* 0x1120 */ u8 mmc5_extension_ram[0x400];
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
    /* 0x16A0 */ u8 ppu_internal_state[8];
    /* 0x16A8 */ u8 ppu_register_cache[8];
    /* 0x16B0 */ union {
        u8 raw[4];
        struct {
            u8 disk_status; // 0x00
            u8 data; // 0x01
            u8 drive_status; // 0x02
            u8 expansion_connector; // 0x03 top-most bit is battery status
        } registers;
    } qd_drive;
    /* 0x16B4 */ u32 vblank_frame_counter;
    /* 0x16B8 */ u16 wdm_return_addr; // return address calculated by opcode 42, WDM
    /* 0x16BA */ u16 _16BA;
    /* 0x16BC */ u8 _16BC;
    /* 0x16BD */ u8 qd_irq_acknowledged_flag;
    /* 0x16BE */ u8 _16BE;
    /* 0x16BF */ u8 _16BF;
    /* 0x16C0 */ union {
        u32 full;
        struct {
            u16 upper;
            u16 lower;
        } split;
    } qd_disk_head_position;
    /* 0x16C4 */ u8 _16C4; // 0x4020 ?
    /* 0x16C5 */ u8 _16C5; // 0x4021 ?
    /* 0x16C6 */ u8 fds_timer_control_register; // 0x4022
    /* 0x16C7 */ u8 fds_master_io_enable_register; // 0x4023
    /* 0x16C8 */ u8 _16C8; // 0x4024 ?
    /* 0x16C9 */ u8 fds_control_register; // 0x4025
    /* 0x16CA */ u8 _16CA;
    /* 0x16CB */ u8 _16CB;
    /* 0x16CC */ u8 ppu_palette_ram[4 * 0x20];
    /* 0x174C */ u8 ppu_render_latches[24]; // PPU latches for tile/attribute data
    /* 0x1764 */ u8 mapper;
    /* 0x1765 */ u8 prg_banks;  // init to number of 8k PRG banks - 1. might indicate currently selected bank
    /* 0x1766 */ u16 chr_banks; // init to number of 1k CHR banks - 1. might indicate currently selected bank
    /* 0x1768 */ u8 bbram_mode_select;
    /* 0x1769 */ u8 chr_ram_write_enable; // 0 = can't write to chr ram, 1 = can write
    /* 0x176A */ u8 fds_disk_count;
    /* 0x176B */ u8 fds_disk_drive_status; // duplicate of qd_drive.registers.drive_status?
    /* 0x176C */ u8 fds_ready_delay_counter;
    /* 0x176D */ u8 motor_timer;
    // /* 0x176E */ u8 mmc5_registers[0x40]; // MMC5 registers -- also used to store QD info during fast save
    /* 0x176E */ u8 _176E[26];
    /* 0x1788 */ u8 fds_fast_io_lock;
    
    // MMC1 mapper specific (mapper 01)
    // 0x00 = control
    // 0x01 = chr_bank0, 0x02 = chr_bank1
    // 0x03 = selected_reg_idx
    // 0x04 = 512k_prg_mode_flag
    // 0x05 = load_counter
    // 0x06 = shift_register
    /* 0x1789 */ u8 mmc1_regs[7];
    /* 0x1790 */ u8 mmc3_bank_select_regs[8];
    /* 0x1798 */ u8 _1798;
    /* 0x1799 */ u8 _1799;
    /* 0x179A */ u8 _179A;
    /* 0x179B */ u8 _179B;
    /* 0x179C */ u8 _179C;
    /* 0x179D */ u8 _179D;
    /* 0x179E */ u8 _179E;
    /* 0x179F */ u8 _179F;
    /* 0x17A0 */ u8 _17A0;
    /* 0x17A1 */ u8 _17A1;
    /* 0x17A2 */ u8 _17A2;
    /* 0x17A3 */ u8 _17A3;
    /* 0x17A4 */ u8 _17A4;
    /* 0x17A5 */ u8 _17A5;
    /* 0x17A6 */ u8 _17A6;
    /* 0x17A7 */ u8 _17A7;
    /* 0x17A8 */ u8 _17A8;
    /* 0x17A9 */ u8 _17A9;
    /* 0x17AA */ u8 _17AA;
    /* 0x17AB */ u8 _17AB;
    /* 0x17AC */ u8 _17AC;
    /* 0x17AD */ u8 _17AD;
    /* 0x17AE */ u16 mmc5_scanline_irq_target_val;
    /* 0x17B0 */ u8 mmc5_prg_ram_protect[2];
    /* 0x17B2 */ u8 mmc5_ext_ram_mode;
    /* 0x17B3 */ u8 mmc5_nametable_mapping;
    /* 0x17B4 */ u8 mmc5_apu_pcm_mode_irq; // 0x5010
    /* 0x17B5 */ u8 mmc5_apu_status; // 0x5015 analagous to 0x4015 (regular NES APU status), but only bottom two bits are used for MMC5 pulse channels
    /* 0x17B6 */ u8 mmc5_scanline_irq_status;
    /* 0x17B7 */ u8 mmc5_mul_regs[2]; // 0 = operand 0, 1 = operand 1, 0 = result lo, 1 = result hi
    /* 0x17B9 */ u8 mmc5a_cl3_sl3_data_dir_output_src; // 5207 (read/write)
    /* 0x17BA */ u8 mmc5a_cl3_sl3_status; // 5208 (write only)
    /* 0x17BB */ u8 mmc5a_hardware_timer_irq_upper; // 5209 (read/write)
    /* 0x17BC */// u8 mmc5a_hardware_timer_irq_lower; // 520A (write only)
    /* 0x17BC */ u8 mmc5_mul_operands[2]; // 0 = operand 0, 1 = operand 1
    /* 0x17BE */ u8 _17BE;
    /* 0x17BF */ u8 mmc5_scanline_irq_compare_value;
    /* 0x17C0 */ u8 _17C0;
    /* 0x17C1 */ u8 _17C1;
    /* 0x17C2 */ u8 _17C2;
    /* 0x17C3 */ u8 _17C3;
    /* 0x17C4 */ u8 _17C4;
    /* 0x17C5 */ u8 _17C5;
    /* 0x17C6 */ u8 _17C6;
    /* 0x17C7 */ u8 _17C7;
    /* 0x17C8 */ u8 _17C8;
    /* 0x17C9 */ u8 _17C9;
    /* 0x17CA */ u8 _17CA;
    /* 0x17CB */ u8 _17CB;
    /* 0x17CC */ u8 _17CC;
    /* 0x17CD */ u8 _17CD;
    /* 0x17CE */ u8 _17CE;
    /* 0x17CF */ u8 _17CF;
    /* 0x17D0 */ u8 _17D0;
    /* 0x17D1 */ u8 _17D1;
    /* 0x17D2 */ u8 _17D2;
    /* 0x17D3 */ u8 _17D3;
    /* 0x17D4 */ u8 _17D4;
    /* 0x17D5 */ u8 _17D5;
    /* 0x17D6 */ u8 _17D6;
    /* 0x17D7 */ u8 _17D7;
    /* 0x17D8 */ u8 _17D8;
    /* 0x17D9 */ u8 _17D9;
    /* 0x17DA */ u8 _17DA;
    /* 0x17DB */ u8 _17DB;
    /* 0x17DC */ u8 _17DC;
    /* 0x17DD */ u8 _17DD;
    /* 0x17DE */ u8 _17DE;
    /* 0x17DF */ u8 _17DF;
    /* 0x17E0 */ u8 _17E0;
    /* 0x17E1 */ u8 _17E1;
    /* 0x17E2 */ u8 _17E2;
    /* 0x17E3 */ u8 _17E3;
    /* 0x17E4 */ u8 _17E4;
    /* 0x17E5 */ u8 _17E5;
    /* 0x17E6 */ u8 _17E6;
    /* 0x17E7 */ u8 _17E7;
    /* 0x17E8 */ u8 _17E8;
    /* 0x17E9 */ u8 _17E9;
    /* 0x17EA */ u8 _17EA;
    /* 0x17EB */ u8 _17EB;
    /* 0x17EC */ u8 _17EC;
    /* 0x17ED */ u8 _17ED;
    /* 0x17EE */ u8 _17EE;
    /* 0x17EF */ u8 _17EF;
    /* 0x17F0 */ u8* prgromp;    // pointer to the start of PRG ROM?
    /* 0x17F4 */ u8* chrramp;    // pointer to the end of PRG ROM?
    /* 0x17F8 */ u8* bbramp;     // pointer to battery backed RAM?
    /* 0x17FC */ u8 ppu_chr_banks[8];
    /* 0x1804 */ u8 mapper_chr_bank_ext[12];
    /* 0x1810 */ u8* ppu_nametable_pointers[4];
    /* 0x1820 */ s16 ppu_scanline_counter;
    /* 0x1822 */ s16 cpu_cycles_per_visible_scanline;
    /* 0x1824 */ s16 cpu_cycles_per_vblank_scanline;
    /* 0x1826 */ s16 cpu_cycles_for_nmi;
    /* 0x1828 */ u16 scanline_irq_target_val; // scanline target to initiate iterrupt request
    /* 0x182A */ u16 mapper19_irq_scanline_latch; // latch value used for IRQ timings for Namco 163 mapper
    /* 0x182C */ u8 sprite0_hit_scanline; // scanline which 
    /* 0x182D */ u8 mmc3_command_register; // Used exclusive in ksNesStore04_8000 for routing logic
    /* 0x182E */ u8 ppu_scanline_threshold; // used for Tetris 2 + Bombliss & Quinty to correct scrolling behavior
    /* 0x182F */ u8 ppu_fine_x_scroll;
    /* 0x1830 */ u8 ppu_vram_addr_v_hi; // vram address for the current bg tile (v)
    /* 0x1831 */ u8 ppu_vram_addr_v_lo; // fine Y scroll corrected
    /* 0x1832 */ u16 ppu_addr_latch;
    /* 0x1834 */ u8 ppu_vram_addr_t_hi; // vram address for work (t)
    /* 0x1835 */ u8 ppu_vram_addr_t_lo; // fine Y scroll raw
    /* 0x1836 */ u16 _1836; // assumed to be an unused ppu latch value for t?
    /* 0x1838 */ u16 cycle_count;
    /* 0x183A */ u16 _183A; // unused
    /* 0x183C */ u16 mapper_irq_latch;
    /* 0x183E */ u16 _183E; // unused
    /* 0x1840 */ void* mapper_irq_handler;
    /* 0x1844 */ u16 PC;
    /* 0x1846 */ struct {
        u8 A; // 0x00
        u8 X; // 0x01
        u8 Y; // 0x02
        u8 S; // 0x03

        u8 flag_z; // 0x04
        u8 flag_c; // 0x05
        u8 flag_v; // 0x06
        u8 flag_n; // 0x07

        u8 P; // 0x08

        u8 _unused_09; // 0x09

        u8 apu_dma_dmc_flags; // 0x0A
        u8 dac_value; // 0x0B

        u8 irq_status_flags; // 0x0C
        u8 irq_mask_flags; // 0x0D

        u8 controller_strobe; // 0x0E

        u8 apu_frame_counter_mode; // 0x0F

        u8 irq_pending_flag; // 0x10

        u8 mapper_irq_enable; // 0x11
    } cpu_state;
    /* 0x1858 */ u32 reset_flags; // this should probably be defined as an enum.
    /* 0x185C */ u32 frame_flags; // this should probably be defined as an enum.
    /* 0x1860 */ size_t prg_size; // PRG size in bytes
    /* 0x1864 */ size_t chr_size; // CHR size in bytes
    /* 0x1868 */ u8* nesromp;
    /* 0x186C */ u8* ppu_chr_bank_pointers[24];
    /* 0x18CC */ u32 io_shift_registers[7];
    /* 0x18E8 */ u8 palette_normal[0x80]; // ksNesPaletteNormal
    /* 0x1968 */ u8 _1968[0x108]; // unused? (might be in the draw TU)
    /* 0x1A70 */ u32 frame_counter;
    /* 0x1A74 */ OSTick os_tick;
} ksNesStateObj;

#ifdef __cplusplus
}
#endif

#endif
