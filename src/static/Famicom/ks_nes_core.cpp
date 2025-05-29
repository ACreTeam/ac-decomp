
#include "Famicom/ks_nes_core.h"
#include "Famicom/ks_nes_draw.h"
#include "dolphin/os/OSCache.h"
#include "dolphin/os/OSTime.h"
#include "dolphin/base/PPCArch.h"
#include "jaudio_NES/emusound.h"
#include "_mem.h"
#include "dolphin/os.h"
#include "jaudio_NES/emusound.h"
// TODO: verify function signatures.
// TODO: replace hard-coded function pointers with function names.

typedef void (*STORE_FUNC)(u32 addr, u32 data);

// clang-format off
STORE_FUNC ksNesStoreFuncTblDefault[] = {
    (STORE_FUNC)ksNesStoreWRAM,         
    (STORE_FUNC)ksNesStorePPU,          
    (STORE_FUNC)ksNesStoreIO,           
    (STORE_FUNC)ksNesLinecntIrqDefault, 
    (STORE_FUNC)ksNesLinecntIrqDefault, 
    (STORE_FUNC)ksNesLinecntIrqDefault, 
    (STORE_FUNC)ksNesLinecntIrqDefault, 
    (STORE_FUNC)ksNesLinecntIrqDefault, 
};

typedef void (*STORE_PPU_FUNC)(u32, u32);

STORE_PPU_FUNC ksNesStorePPUFuncTblDefault[] = {
    (STORE_PPU_FUNC)ksNesStore2000,         
    (STORE_PPU_FUNC)ksNesStorePPURam,       
    (STORE_PPU_FUNC)ksNesLinecntIrqDefault, 
    (STORE_PPU_FUNC)ksNesStorePPURam,       
    (STORE_PPU_FUNC)ksNesStore2004,         
    (STORE_PPU_FUNC)ksNesStore2005,         
    (STORE_PPU_FUNC)ksNesStore2006,         
    (STORE_PPU_FUNC)ksNesStore2007ChrRom,   
};

typedef void (*STORE_IO_FUNC)(u32, u32);

STORE_IO_FUNC ksNesStoreIOFuncTblDefault[] = {
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4003,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4003,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4003,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4003,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4011,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4000,
    (STORE_IO_FUNC)ksNesStore4014,
    (STORE_IO_FUNC)ksNesStore4015,
    (STORE_IO_FUNC)ksNesStore4016,
    (STORE_IO_FUNC)ksNesStore4017,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesLinecntIrqDefault,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesLinecntIrqDefault,
    (STORE_IO_FUNC)ksNesStoreInvalid,
    (STORE_IO_FUNC)ksNesStoreInvalid,
};

typedef void (*STORE_QD_FUNC)(u32, u32);

STORE_QD_FUNC ksNesStoreQDFuncTbl[] = {
    (STORE_QD_FUNC)ksNesStoreQD_4020,
    (STORE_QD_FUNC)ksNesStoreQD_4020,
    (STORE_QD_FUNC)ksNesStoreQD_4022,
    (STORE_QD_FUNC)ksNesStoreQD_4023,
    (STORE_QD_FUNC)ksNesStoreQD_4024,
    (STORE_QD_FUNC)ksNesStoreQD_4025,
    (STORE_QD_FUNC)ksNesStoreQD_4026,
    (STORE_QD_FUNC)ksNesStoreInvalid,
};

u8 ksNesInitQDDataTbl[11] = {
    0x00, 0x2f, 0x00, 0x00, 
    0x00, 0x06, 0x10, 0xc0, 
    0x80, 0x35, 0xac
};

typedef void (*STORE_05_FUNC)(u32, u32);

// 0x800D667C
STORE_05_FUNC ksNesStore05FuncTbl[] = {
    (STORE_05_FUNC)ksNesStore05_5100,
    (STORE_05_FUNC)ksNesStore05_5101,
    (STORE_05_FUNC)ksNesStore05_5102,
    (STORE_05_FUNC)ksNesStore05_5102,
    (STORE_05_FUNC)ksNesStore05_5104,
    (STORE_05_FUNC)ksNesStore05_5105,
    (STORE_05_FUNC)ksNesStore05_5106,
    (STORE_05_FUNC)ksNesStore05_5106,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStore05_5113,
    (STORE_05_FUNC)ksNesStore05_5113,
    (STORE_05_FUNC)ksNesStore05_5113,
    (STORE_05_FUNC)ksNesStore05_5113,
    (STORE_05_FUNC)ksNesStore05_5113,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5120,
    (STORE_05_FUNC)ksNesStore05_5128,
    (STORE_05_FUNC)ksNesStore05_5128,
    (STORE_05_FUNC)ksNesStore05_5128,
    (STORE_05_FUNC)ksNesStore05_5128,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStoreInvalid,
    (STORE_05_FUNC)ksNesStore05_5130
};

typedef u32 (*LOAD_FUNC)(u32);

LOAD_FUNC ksNesLoadFuncTblDefault[] = {
    (LOAD_FUNC)ksNesLoadWRAM,
    (LOAD_FUNC)ksNesLoadPPU,
    (LOAD_FUNC)ksNesLoadIO,
    (LOAD_FUNC)ksNesLoadIgnore,
    (LOAD_FUNC)ksNesLoadBBRAM,
    (LOAD_FUNC)ksNesLoadBBRAM,
    (LOAD_FUNC)ksNesLoadBBRAM,
    (LOAD_FUNC)ksNesLoadBBRAM
};

typedef u32 (*LOAD_IO_FUNC)(u32);

LOAD_IO_FUNC ksNesLoadIOFuncTblDefault[] = {
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoadIgnore,
    (LOAD_IO_FUNC)ksNesLoad4015,
    (LOAD_IO_FUNC)ksNesLoad4016,
    (LOAD_IO_FUNC)ksNesLoad4017
};

u8 ksNesVoiceIdTable_12[] = {
    0x04, 0x05, 0x06, 0x07, 0x01, 0x02, 0x03, 0x08, 0x0a, 0x0b, 0x09, 0x0c, 0x0e, 0x0d, 0x0f, 0x0f,
};

// typedef u32(*MAPPER_INIT_FUNC)(ksNesCommonWorkObj* wp,ksNesStateObj* sp);

// clang-format off
// https://www.nesdev.org/wiki/Mapper
// https://www.nesdev.org/wiki/List_of_mappers
void* ksNesMapperInitFuncTbl[185][5] = {
    // 0    NROM
    {
        NULL,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault
    },
    // 1    SxROM, MMC1
    {
        ksNesInit01,
        ksNesStore01_8000,
        ksNesStore01_8000,
        ksNesStore01_8000,
        ksNesStore01_8000
    },
    // 2    UxROM
    {
        NULL,
        ksNesStore02_8000,
        ksNesStore02_8000,
        ksNesStore02_8000,
        ksNesStore02_8000
    },
    // 3    CNROM
    {
        ksNesInit03,
        ksNesStore03_6000,
        ksNesStore03_6000,
        ksNesStore03_6000,
        ksNesStore03_6000
    },
    // 4    TxROM, MMC3, MMC6
    {
        ksNesInit04,
        ksNesStore04_8000,
        ksNesStore04_a000,
        ksNesStore04_c000,
        ksNesStore04_e000
    },
    // 5    ExROM, MMC5
    {
        ksNesInit05,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault
    },
    // 6 
    {},
    // 7    AxROM
    {
        ksNesInit07,
        ksNesStore07_8000,
        ksNesStore07_8000,
        ksNesStore07_8000,
        ksNesStore07_8000
    },
    // 8 
    {},
    // 9    PxROM, MMC2
    {
        ksNesInit09,
        ksNesStore09_8000,
        ksNesStore09_a000,
        ksNesStore09_c000,
        ksNesStore09_e000
    },
    // 10   FxROM, MMC4
    {
        NULL,
        ksNesStore0a_8000,
        ksNesStore0a_a000,
        ksNesStore09_c000,
        ksNesStore09_e000
    },
    // 11   Color Dreams
    {},
    // 12
    {},
    // 13   CPROM
    {},
    // 14
    {},
    // 15   100-in-1 Contra Function 16
    {},
    // 16   Bandai EPROM (24C02)
    {},
    // 17
    {},
    // 18   Jaleco SS8806
    {
        ksNesInit12,
        ksNesStore12_8000,
        ksNesStore12_a000,
        ksNesStore12_a000,
        ksNesStore12_e000
    },
    // 19   Namco 163
    {
        ksNesInit13,
        ksNesStore13_8000,
        ksNesStore13_8000,
        ksNesStore13_c000,
        ksNesStore13_e000
    },
    // 20
    {},
    // 21   VRC4a, VRC4c
    {
        ksNesInit15,
        ksNesStore19_8000,
        ksNesStore19_a000,
        ksNesStore19_b000,
        ksNesStore19_e000
    },
    // 22   VRC2a
    {
        NULL,
        ksNesStore16_8000,
        ksNesStore16_a000,
        ksNesStore16_b000,
        ksNesStore16_b000
    },
    // 23   VRC2b, VRC4e
    {
        ksNesInit15,
        ksNesStore16_8000,
        ksNesStore17_a000,
        ksNesStore17_b000,
        ksNesStore17_e000
    },
    // 24   VRC6a
    {
        ksNesInit18,
        ksNesStore18_8000,
        ksNesStore18_a000,
        ksNesStore18_c000,
        ksNesStore18_e000
    },
    // 25   VRC4b, VRC4d
    {
        ksNesInit15,
        ksNesStore19_8000,
        ksNesStore19_a000,
        ksNesStore19_b000,
        ksNesStore19_e000
    },
    // 26   VRC6b
    {
        ksNesInit1a,
        ksNesStore18_8000,
        ksNesStore18_a000,
        ksNesStore18_c000,
        ksNesStore18_e000
    },
    // 27
    {},
    // 28
    {},
    // 29
    {},
    // 30
    {},
    // 31
    {},
    // 32
    {},
    // 33
    {},
    // 34   BNROM, NINA-001
    {},
    // 35
    {},
    // 36
    {},
    // 37
    {},
    // 38
    {},
    // 39
    {},
    // 40
    {},
    // 41
    {},
    // 42
    {},
    // 43
    {},
    // 44
    {},
    // 45
    {},
    // 46
    {},
    // 47
    {},
    // 48
    {},
    // 49
    {},
    // 50
    {},
    // 51
    {},
    // 52
    {},
    // 53
    {},
    // 54
    {},
    // 55
    {},
    // 56
    {},
    // 57
    {},
    // 58
    {},
    // 59
    {},
    // 60
    {},
    // 61
    {},
    // 62
    {},
    // 63
    {},
    // 64   RAMBO-1
    {},
    // 65
    {},
    // 66   GxROM, MxROM
    {
        ksNesInit42,
        ksNesStore42_8000,
        ksNesStore42_8000,
        ksNesStore42_8000,
        ksNesStore42_8000
    },
    // 67
    {
        ksNesInit43,
        ksNesStore44_8000,
        ksNesStore44_8000,
        ksNesStore43_c000,
        ksNesStore44_e000
    },
    // 68   After Burner
    {
        NULL,
        ksNesStore44_8000,
        ksNesStore44_8000,
        ksNesStore44_c000,
        ksNesStore44_e000
    },
    // 69   FME-7, Sunsoft 5B
    {
        ksNesInit45,
        ksNesStore45_8000,
        ksNesStore45_a000,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault
    },
    // 70
    {
        NULL,
        ksNesStore46_8000,
        ksNesStore46_8000,
        ksNesStore46_8000,
        ksNesStore46_8000
    },
    // 71   Camerica/Codemasters
    {},
    // 72
    {},
    // 73   VRC3
    {
        ksNesInit49,
        ksNesLinecntIrqDefault,
        ksNesStore49_a000,
        ksNesStore49_c000,
        ksNesStore02_8000
    },
    // 74   Pirate MMC3 derivative
    {},
    // 75   VRC1
    {
        NULL,
        ksNesStore4b_8000,
        ksNesStore4b_a000,
        ksNesStore4b_a000,
        ksNesStore4b_e000
    },
    // 76   Namco 109 variant
    {},
    // 77
    {},
    // 78
    {},
    // 79   NINA-03/NINA-06
    {},
    // 80
    {},
    // 81
    {},
    // 82
    {},
    // 83
    {},
    // 84
    {},
    // 85   VRC7
    {},
    // 86   JALECO-JF-13
    {
        ksNesInit56,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
    },
    // 87
    {
        ksNesInit03,
        ksNesStore57_6000,
        ksNesStore57_6000,
        ksNesStore57_6000,
        ksNesStore57_6000
    },
    // 88
    {},
    // 89
    {
        NULL,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesStore59_c000,
        ksNesLinecntIrqDefault
    },
    // 90
    {},
    // 91
    {},
    // 92
    {},
    // 93
    {
        ksNesInit03,
        ksNesStore5d_6000,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault
    },
    // 94   Senjou no Ookami
    {},
    // 95
    {},
    // 96
    {},
    // 97
    {},
    // 98
    {},
    // 99
    {},
    // 100
    {},
    // 101
    {},
    // 102
    {},
    // 103
    {},
    // 104
    {},
    // 105  NES-EVENT
    {},
    // 106
    {},
    // 107
    {},
    // 108
    {},
    // 109
    {},
    // 110
    {},
    // 111
    {},
    // 112
    {},
    // 113  NINA-03/NINA-06??
    {},
    // 114
    {},
    // 115
    {},
    // 116
    {},
    // 117
    {},
    // 118  TxSROM, MMC3
    {},
    // 119  TQROM, MMC3
    {},
    // 120
    {},
    // 121
    {},
    // 122
    {},
    // 123
    {},
    // 124
    {},
    // 125
    {},
    // 126
    {},
    // 127
    {},
    // 128
    {},
    // 129
    {},
    // 130
    {},
    // 131
    {},
    // 132
    {},
    // 133
    {},
    // 134
    {},
    // 135
    {},
    // 136
    {},
    // 137
    {},
    // 138
    {},
    // 139
    {},
    // 140
    {},
    // 141
    {},
    // 142
    {},
    // 143
    {},
    // 144
    {},
    // 145
    {},
    // 146
    {},
    // 147
    {},
    // 148
    {},
    // 149
    {},
    // 150
    {},
    // 151
    {},
    // 152
    {},
    // 153
    {},
    // 154
    {},
    // 155
    {},
    // 156
    {},
    // 157
    {},
    // 158
    {},
    // 159  Bandai EPROM (24C01)
    {},
    // 160
    {},
    // 161
    {},
    // 162
    {},
    // 163
    {},
    // 164
    {},
    // 165
    {},
    // 166  SUBOR
    {},
    // 167  SUBOR
    {},
    // 168
    {},
    // 169
    {},
    // 170
    {},
    // 171
    {},
    // 172
    {},
    // 173
    {},
    // 174
    {},
    // 175
    {},
    // 176
    {},
    // 177
    {},
    // 178
    {},
    // 179
    {},
    // 180  Crazy Climber
    {},
    // 181
    {},
    // 182
    {},
    // 183
    {},
    // 184
    {
        ksNesInit03,
        ksNesStoreb8_6000,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
        ksNesLinecntIrqDefault,
    }
};

typedef struct {
    void* instructionEvaluationFunction;
    u8 cycles;
    u8 byteSize;
    // u16 unused
    void* followUpFunction;
    u8 padding[4];
} KS_NES_INSTR;

#define TEMP_NULL_CAST (void*)

KS_NES_INSTR ksNesInstJumpTbl[0x100] = {
    // 0x00 BRK
    {
        ksNesInst_brk_00,
        7, 2,
        NULL,
    },
    // 0x01 ORA X,ind
    {
        ksNesInst_load8_dxi,
        6, 2,
        ksNesInst_ora_01
    },
    // 0x02 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        8, 1,
        NULL,
    },
    // 0x03 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x04 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x05 ORA zpg
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_ora_01
    },
    // 0x06 ASL zpg
    {
        ksNesInst_load8_zerop,
        5, 2,
        ksNesInst_asl_06
    },
    // 0x07 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL
    },
    // 0x08 PHP
    {
        ksNesInst_php_08,
        3, 1,
        ksNesLinecntIrqDefault
    },
    // 0x09 ORA #
    {
        ksNesInst_ora_01,
        2, 2,
        NULL
    },
    // 0x0A ASL A
    {
        ksNesInst_asl_0a,
        2, 1,
        NULL
    },
    // 0x0B ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL
    },
    // 0x0C ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL
    },
    // 0x0D ORA abs
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_ora_01
    },
    // 0x0E ASL abs
    {
        ksNesInst_load8_abs,
        6, 3,
        ksNesInst_asl_06,
    },
    // 0x0F ---
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL
    },
    // 0x10 BPL rel
    {
        ksNesInst_bpl_10,
        3, 2,
        NULL,
    },
    // 0x11 ORA ind,Y
    {
        ksNesInst_load8_dyi,
        5, 2,
        ksNesInst_ora_01,
    },
    // 0x12 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL
    },
    // 0x13 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL
    },
    // 0x14 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x15 ORA zpg,X
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_ora_01,
    },
    // 0x16 ROL zpg
    {
        ksNesInst_load8_dx,
        6, 2,
        ksNesInst_asl_06,
    },
    // 0x17 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x18 CLC
    {
        ksNesInst_clc_18,
        2, 1,
        NULL,
    },
    // 0x19 ORA abs,Y
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_ora_01,
    },
    // 0x1A ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x1B ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x1C ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x1D ORA abs,X
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_ora_01,
    },
    // 0x1E ASL abs,X
    {
        ksNesInst_load8_absx,
        7, 3,
        ksNesInst_asl_06,
    },
    // 0x1F ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x20 JSR abs
    {
        ksNesInst_load16_imm,
        6, 3,
        ksNesInst_jsr_20,
    },
    // 0x21 AND X,ind
    {
        ksNesInst_load8_dxi,
        6, 2,
        ksNesInst_and_21,
    },
    // 0x22 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        8, 1,
        NULL,
    },
    // 0x23 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x24 BIT zpg
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_bit_24,
    },
    // 0x25 AND zpg
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_and_21,
    },
    // 0x26 ROL zpg
    {
        ksNesInst_load8_zerop,
        5, 2,
        ksNesInst_rol_26,
    },
    // 0x27 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x28 PLP impl
    {
        ksNesInst_plp_28,
        4, 1,
        ksNesActivateIntrIRQ,
    },
    // 0x29 AND #
    {
        ksNesInst_and_21,
        2, 2,
        NULL,
    },
    // 0x2A ROL A
    {
        ksNesInst_rol_2a,
        2, 1,
        NULL,
    },
    // 0x2B ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x2C BIT abs
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_bit_24,
    },
    // 0x2D AND abs
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_and_21,
    },
    // 0x2E ROL abs
    {
        ksNesInst_load8_abs,
        6, 3,
        ksNesInst_rol_26,
    },
    // 0x2F ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x30 BMI rel
    {
        ksNesInst_bmi_30,
        3, 2,
        NULL,
    },
    // 0x31 AND ind,Y
    {
        ksNesInst_load8_dyi,
        5, 2,
        ksNesInst_and_21,
    },
    // 0x32 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x33 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0x34 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x35 AND zpg,X
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_and_21,
    },
    // 0x36 ROL zpg,X
    {
        ksNesInst_load8_dx,
        6, 2,
        ksNesInst_rol_26,
    },
    // 0x37 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x38 SEC impl
    {
        ksNesInst_sec_38,
        2, 1,
        NULL,
    },
    // 0x39 AND abs,Y
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_and_21,
    },
    // 0x3A ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x3B ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x3C ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x3D AND abs,X
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_and_21,
    },
    // 0x3E ROL abs,X
    {
        ksNesInst_load8_absx,
        7, 3,
        ksNesInst_rol_26,
    },
    // 0x3F ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x40 RTI impl
    {
        ksNesInst_rti_40,
        6, 1,
        ksNesInst_rti_40_2,
    },
    // 0x41 EOR X,ind
    {
        ksNesInst_load8_dxi,
        6, 2,
        ksNesInst_eor_41,
    },
    // 0x42 ILLEGAL INSTRUCTION
    {
        ksNesInst_wdm_42,
        2, 2,
        NULL,
    },
    // 0x43 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x44 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0x45 EOR zpg
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_eor_41,
    },
    // 0x46 LSR zpg
    {
        ksNesInst_load8_zerop,
        5, 2,
        ksNesInst_lsr_46,
    },
    // 0x47 ILLEGAL INSTRUCTION
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x48
    {
        ksNesInst_pha_48,
        3, 1,
        NULL,
    },
    // 0x49
    {
        ksNesInst_eor_41,
        2, 2,
        NULL,
    },
    // 0x4A
    {
        ksNesInst_lsr_4a,
        2, 1,
        NULL,
    },
    // 0x4B
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0x4C
    {
        ksNesInst_load16_imm,
        3, 3,
        ksNesInst_jmp_4c,
    },
    // 0x4D
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_eor_41,
    },
    // 0x4E
    {
        ksNesInst_load8_abs,
        6, 3,
        ksNesInst_lsr_46,
    },
    // 0x4F
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x50
    {
        ksNesInst_bvc_50,
        3, 2,
        NULL,
    },
    // 0x51
    {
        ksNesInst_load8_dyi,
        5, 2,
        ksNesInst_eor_41,
    },
    // 0x52
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x53
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0x54
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0x55
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_eor_41,
    },
    // 0x56
    {
        ksNesInst_load8_dx,
        6, 2,
        ksNesInst_lsr_46,
    },
    // 0x57
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x58
    {
        ksNesInst_cli_58,
        2, 1,
        NULL,
    },
    // 0x59
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_eor_41,
    },
    // 0x5A
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0x5B
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x5C
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x5D
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_eor_41,
    },
    // 0x5E
    {
        ksNesInst_load8_absx,
        7, 3,
        ksNesInst_lsr_46,
    },
    // 0x5F
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x60
    {
        ksNesInst_rts_60,
        6, 1,
        NULL,
    },
    // 0x61
    {
        ksNesInst_load8_dxi,
        6, 2,
        ksNesInst_adc_61,
    },
    // 0x62
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x63
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x64
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0x65
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_adc_61,
    },
    // 0x66
    {
        ksNesInst_load8_zerop,
        5, 2,
        ksNesInst_ror_66,
    },
    // 0x67
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x68
    {
        ksNesInst_pla_68,
        4, 1,
        NULL,
    },
    // 0x69
    {
        ksNesInst_adc_61,
        2, 2,
        NULL,
    },
    // 0x6A
    {
        ksNesInst_ror_6a,
        2, 1,
        NULL,
    },
    // 0x6B
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x6C
    {
        ksNesInst_load16_imm,
        5, 3,
        ksNesInst_jmp_6c,
    },
    // 0x6D
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_adc_61,
    },
    // 0x6E
    {
        ksNesInst_load8_abs,
        6, 3,
        ksNesInst_ror_66,
    },
    // 0x6F
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x70
    {
        ksNesInst_bvs_70,
        3, 2,
        NULL,
    },
    // 0x71
    {
        ksNesInst_load8_dyi,
        5, 2,
        ksNesInst_adc_61,
    },
    // 0x72
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x73
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0x74
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x75
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_adc_61,
    },
    // 0x76
    {
        ksNesInst_load8_dx,
        6, 2,
        ksNesInst_ror_66,
    },
    // 0x77
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x78
    {
        ksNesInst_sei_78,
        2, 1,
        NULL,
    },
    // 0x79
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_adc_61,
    },
    // 0x7A
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x7B
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x7C
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x7D
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_adc_61,
    },
    // 0x7E
    {
        ksNesInst_load8_absx,
        7, 3,
        ksNesInst_ror_66,
    },
    // 0x7F
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x80
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x81
    {
        ksNesInst_load8_dx,
        6, 2,
        ksNesInst_sta_81,
    },
    // 0x82
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x83
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x84
    {
        ksNesInst_sty_84,
        3, 2,
        NULL,
    },
    // 0x85
    {
        ksNesInst_sta_85,
        3, 2,
        NULL,
    },
    // 0x86
    {
        ksNesInst_stx_86,
        3, 2,
        NULL,
    },
    // 0x87
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x88
    {
        ksNesInst_dey_88,
        2, 1,
        NULL,
    },
    // 0x89
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x8A
    {
        ksNesInst_txa_8a,
        2, 1,
        NULL,
    },
    // 0x8B
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0x8C
    {
        ksNesInst_load16_imm,
        4, 3,
        ksNesInst_sty_8c,
    },
    // 0x8D
    {
        ksNesInst_load16_imm,
        4, 3,
        ksNesInst_sta_8d,
    },
    // 0x8E
    {
        ksNesInst_load16_imm,
        4, 3,
        ksNesInst_stx_8e,
    },
    // 0x8F
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x90
    {
        ksNesInst_bcc_90,
        3, 2,
        NULL,
    },
    // 0x91
    {
        ksNesInst_sta_91,
        6, 2,
        NULL,
    },
    // 0x92
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x93
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0x94
    {
        ksNesInst_sty_94,
        4, 2,
        NULL,
    },
    // 0x95
    {
        ksNesInst_sta_95,
        4, 2,
        NULL,
    },
    // 0x96
    {
        ksNesInst_stx_96,
        4, 2,
        NULL,
    },
    // 0x97
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0x98
    {
        ksNesInst_tya_98,
        2, 1,
        NULL,
    },
    // 0x99
    {
        ksNesInst_load16_imm,
        5, 3,
        ksNesInst_sta_99,
    },
    // 0x9A
    {
        ksNesInst_txs_9a,
        2, 1,
        NULL,
    },
    // 0x9B
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0x9C
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0x9D
    {
        ksNesInst_load16_imm,
        5, 3,
        ksNesInst_sta_9d,
    },
    // 0x9E
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0x9F
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xA0
    {
        ksNesInst_ldy_a0,
        2, 2,
        NULL,
    },
    // 0xA1
    {
        ksNesInst_load8_dxi,
        6, 2,
        ksNesInst_lda_a1,
    },
    // 0xA2
    {
        ksNesInst_ldx_a2,
        2, 2,
        NULL,
    },
    // 0xA3
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0xA4
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_ldy_a0,
    },
    // 0xA5
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_lda_a1,
    },
    // 0xA6
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_ldx_a2,
    },
    // 0xA7
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xA8
    {
        ksNesInst_tay_a8,
        2, 1,
        NULL,
    },
    // 0xA9
    {
        ksNesInst_lda_a1,
        2, 2,
        NULL,
    },
    // 0xAA
    {
        ksNesInst_tax_aa,
        2, 1,
        NULL,
    },
    // 0xAB
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0xAC
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_ldy_a0,
    },
    // 0xAD
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_lda_a1,
    },
    // 0xAE
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_ldx_a2,
    },
    // 0xAF
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xB0
    {
        ksNesInst_bcs_b0,
        3, 2,
        NULL,
    },
    // 0xB1
    {
        ksNesInst_load8_dyi,
        5, 2,
        ksNesInst_lda_a1,
    },
    // 0xB2
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xB3
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0xB4
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_ldy_a0,
    },
    // 0xB5
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_lda_a1,
    },
    // 0xB6
    {
        ksNesInst_ldx_b6,
        4, 2,
        NULL,
    },
    // 0xB7
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xB8
    {
        ksNesInst_clv_b8,
        2, 1,
        NULL,
    },
    // 0xB9
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_lda_a1,
    },
    // 0xBA
    {
        ksNesInst_tsx_ba,
        2, 1,
        NULL,
    },
    // 0xBB
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0xBC
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_ldy_a0,
    },
    // 0xBD
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_lda_a1,
    },
    // 0xBE
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_ldx_a2,
    },
    // 0xBF
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xC0
    {
        ksNesInst_cpy_c0,
        2, 2,
        NULL,
    },
    // 0xC1
    {
        ksNesInst_load8_dxi,
        6, 2,
        ksNesInst_cmp_c1,
    },
    // 0xC2
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0xC3
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0xC4
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_cpy_c0,
    },
    // 0xC5
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_cmp_c1,
    },
    // 0xC6
    {
        ksNesInst_load8_zerop,
        5, 2,
        ksNesInst_dec_c6,
    },
    // 0xC7
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xC8
    {
        ksNesInst_iny_c8,
        2, 1,
        NULL,
    },
    // 0xC9
    {
        ksNesInst_cmp_c1,
        2, 2,
        NULL,
    },
    // 0xCA
    {
        ksNesInst_dex_ca,
        2, 1,
        NULL,
    },
    // 0xCB
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0xCC
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_cpy_c0,
    },
    // 0xCD
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_cmp_c1,
    },
    // 0xCE
    {
        ksNesInst_load8_abs,
        6, 3,
        ksNesInst_dec_c6,
    },
    // 0xCF
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xD0
    {
        ksNesInst_bne_d0,
        3, 2,
        NULL,
    },
    // 0xD1
    {
        ksNesInst_load8_dyi,
        5, 2,
        ksNesInst_cmp_c1,
    },
    // 0xD2
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xD3
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0xD4
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xD5
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_cmp_c1,
    },
    // 0xD6
    {
        ksNesInst_load8_dx,
        6, 2,
        ksNesInst_dec_c6,
    },
    // 0xD7
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xD8
    {
        ksNesInst_cld_d8,
        2, 1,
        NULL,
    },
    // 0xD9
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_cmp_c1,
    },
    // 0xDA
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0xDB
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0xDC
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xDD
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_cmp_c1,
    },
    // 0xDE
    {
        ksNesInst_load8_absx,
        7, 3,
        ksNesInst_dec_c6,
    },
    // 0xDF
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xE0
    {
        ksNesInst_cpx_e0,
        2, 2,
        NULL,
    },
    // 0xE1
    {
        ksNesInst_load8_dxi,
        6, 2,
        ksNesInst_sbc_e1,
    },
    // 0xE2
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0xE3
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0xE4
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_cpx_e0,
    },
    // 0xE5
    {
        ksNesInst_load8_zerop,
        3, 2,
        ksNesInst_sbc_e1,
    },
    // 0xE6
    {
        ksNesInst_load8_zerop,
        5, 2,
        ksNesInst_inc_e6,
    },
    // 0xE7
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xE8
    {
        ksNesInst_inx_e8,
        2, 1,
        NULL,
    },
    // 0xE9
    {
        ksNesInst_sbc_e1,
        2, 2,
        NULL,
    },
    // 0xEA
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0xEB
    {
        ksNesLinecntIrqDefault,
        3, 1,
        NULL,
    },
    // 0xEC
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_cpx_e0,
    },
    // 0xED
    {
        ksNesInst_load8_abs,
        4, 3,
        ksNesInst_sbc_e1,
    },
    // 0xEE
    {
        ksNesInst_load8_abs,
        6, 3,
        ksNesInst_inc_e6,
    },
    // 0xEF
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xF0
    {
        ksNesInst_beq_f0,
        3, 2,
        NULL,
    },
    // 0xF1
    {
        ksNesInst_load8_dyi,
        5, 2,
        ksNesInst_sbc_e1,
    },
    // 0xF2
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xF3
    {
        ksNesLinecntIrqDefault,
        7, 1,
        NULL,
    },
    // 0xF4
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
    // 0xF5
    {
        ksNesInst_load8_dx,
        4, 2,
        ksNesInst_sbc_e1,
    },
    // 0xF6
    {
        ksNesInst_load8_dx,
        6, 2,
        ksNesInst_inc_e6,
    },
    // 0xF7
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xF8
    {
        ksNesInst_sed_f8,
        2, 1,
        NULL,
    },
    // 0xF9
    {
        ksNesInst_load8_absy,
        4, 3,
        ksNesInst_sbc_e1,
    },
    // 0xFA
    {
        ksNesLinecntIrqDefault,
        4, 1,
        NULL,
    },
    // 0xFB
    {
        ksNesLinecntIrqDefault,
        2, 1,
        NULL,
    },
    // 0xFC
    {
        ksNesLinecntIrqDefault,
        6, 1,
        NULL,
    },
    // 0xFD
    {
        ksNesInst_load8_absx,
        4, 3,
        ksNesInst_sbc_e1,
    },
    // 0xFE
    {
        ksNesInst_load8_absx,
        7, 3,
        ksNesInst_inc_e6,
    },
    // 0xFF
    {
        ksNesLinecntIrqDefault,
        5, 1,
        NULL,
    },
};
// clang-format on

void ksNesDrawMakeOBJIndTex(ksNesCommonWorkObj* wp) {
    static const u8 array[] = {
        0x00, 0x02, 0x04, 0x06, 0x07, 0x05, 0x03, 0x01,
    };
    u32 i;
    u32 j;

    for (i = 0; i < 16; i++) {
#define TO_IND1(x) ((((x) << 3) & ~0x1f) + (((x) & 3) << 3))
#define TO_IND2(x) ((((x) & 3) << 1) + (((x) << 3) & ~0x1f))
        for (j = 0; j < 4; j++) {
            wp->work_priv._8E40[TO_IND1(i) + TO_IND2(j)] = (i >> 3) & 1;
            wp->work_priv._8E40[TO_IND1(i) + TO_IND2(j) + 1] = array[i & 7] << 2;
        }
    }
#undef TO_IND1
#undef TO_IND2
    DCFlushRangeNoSync(wp->work_priv._8E40, sizeof(wp->work_priv._8E40));
}

void ksNesDrawMakeOBJIndTexMMC5(ksNesCommonWorkObj* wp) {
    static const u8 array[] = {
        0x00,
        0x01,
        0x02,
        0x03,
    };
    u32 i;
    u32 j;

#define TO_IND1(x) ((((x) << 3) & ~0x1f) + (((x) & 7) << 3))
#define TO_IND2(x) ((((x) & 3) << 1) + (((x) << 3) & ~0x1f))
    for (i = 0; i < 16; i++) {
        for (j = 0; j < 4; j++) {
            wp->work_priv._8E40[TO_IND1(i) + TO_IND2(j)] = 0;
            wp->work_priv._8E40[TO_IND1(i) + TO_IND2(j) + 1] = array[i & 3] << 2;
        }
    }
#undef TO_IND1
#undef TO_IND2
    DCFlushRangeNoSync(&wp->work_priv._8E40, sizeof(wp->work_priv._8E40));
}

void ksNesConvertChrToI8(ksNesCommonWorkObj* wp, const u8* data, u32 flags) {
    u32 bufSize = 0x100;
    if (wp->chr_to_i8_buf_size <= 0x100000) {
        bufSize = wp->chr_to_i8_buf_size >> 0xc;
    }
    u32 a = flags & 0x40;
    u32 b = flags >> 4 & 0x18;
    u32 c = flags & 0x3f;
    for (int i = 0; i < 8u; i++) {
        u16 d;
        if (i & 1) {
            d = data[8 + (i >> 1)];
        } else {
            d = data[0xf - (i >> 1)];
        }
        int iVar2 = i * (bufSize >> 3);
        u16 uVar3 = 0x8080;
        for (int j = 0; j < 8; j++) {
            u16 uVar1 = d & uVar3;
            uVar3 >>= 1;
            wp->chr_to_u8_bufp[c + a + b + (flags & 0x3e00) * 8 + iVar2 * 0x1000 + j] =
                (uVar1 & 0xff00) != 0 ? 3 : uVar1 != 0;
        }
        DCStoreRangeNoSync(wp->chr_to_u8_bufp + b + ((flags >> 9) & 0x1f + iVar2) * 0x1000 + a + c, 0x20);
    }
}

void ksNesConvertChrToI8MMC5(ksNesCommonWorkObj* wp, const unsigned char* foo, unsigned long bar) {
}
void ksNesQDSoundSync() {
    u32 i;
    u32 j;
    for (i = 0; i < 0xd; i++) {
        for (j = 0; j < 0x106; j++) {
            Sound_Write(0, 0, j * 0x72);
        }
        OSTick tick = OSGetTick();
        while ((OSGetTick() - tick) / (OS_BUS_CLOCK / 4 / 1000) < 0x10) {}
    }
}
void ksNesQDFastLoad(ksNesCommonWorkObj* wp, ksNesStateObj* sp) {
}
void ksNesQDFastSave(ksNesCommonWorkObj* wp, ksNesStateObj* sp) {
}

void ksNesPushResetButton(ksNesStateObj* sp) {
    sp->_1846[0x0] = 0;
    sp->_1846[0x1] = 0;
    sp->_1846[0x2] = 0;
    sp->_1846[0x3] = 0xff; // S?
    sp->_1846[0x8] = 4;
    sp->_1846[0x10] = 0;
    sp->_1846[0xf] = 0x40;
    sp->_1846[0xc] = 0;
    sp->_1846[0x11] = 0;

    // These could be related to the APU frame counter LFSR.
    // They could also be related to cartridge RAM, typically mapped to [0x6000, 0x7fff].
    // I can't think of anything else that would need to be initialized to 0x7fff.
    sp->_1828 = 0x7fff;
    sp->_17AE = 0x7fff;

    sp->_182C = 0xff;

    sp->_17B0[0x1b] = 0;
    sp->_17B0[0x1c] = 0;

    // 32-bit int initialized to 0 on reset.
    // maybe a frame counter?
    sp->_16C0 = 0;

    sp->_16C4[0x5] = 0x27;
    sp->_16B8[0x4] = 0x27;

    sp->disk_motor = 0;

    sp->_1768[0x4] = 0x78;

    sp->_176E[0x2f] = 0xff;
    sp->_176E[0x31] = 0;

    // grab the reset vector and assign it to the program counter.
    sp->PC = (sp->cpu_e000_ffff[0xfffd] << 8) | sp->cpu_e000_ffff[0xfffc];

    return;
}

int ksNesReset(ksNesCommonWorkObj* wp, ksNesStateObj* sp, u32 flags, u8* chrramp, u8* bbramp) {
    u8* wramp;
    uint uVar1;
    uint uVar2;
    int iVar2;
    int result;
    u8* nesromp;
    OSTick os_tick;
    uint uVar4;
    int iVar4;
    size_t count;
    u8 bVar1;

    // 0x40XX values appear to be NES APU addresses
    // 0x5015 could be the address of the MMC5's audio status register
    // i think these are arguments for something like Sound_Write(u16, u8, u8)
    static u16 sound_init_data[] = {
        0x4015, 0x0000, 0x4008, 0x0000, 0x4080, 0x0080, 0x5015, 0x0000, 0x4010, 0x000f,
        0x4011, 0x0000, 0x4012, 0x0000, 0x4013, 0x0000, 0x4015, 0x0000, 0x5015, 0x0007,
    };
    const static u8 table[] = { 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04,
                                0x00, 0x04, 0x00, 0x04, 0x00, 0x00, 0x04, 0x04 };

    // looks like we're checking memory alignment.
    // maybe done for performance reasons?
    if ((uint)wp & 0x1f || (uint)sp & 0x1f || (uint)&wp->work_priv & 0x1f || (uint)&wp->work_priv._0B40 & 0x1f ||
        (uint)sp->_17FC & 0x03 || (uint)&wp->work_priv._2A40 & 0x1f) {
        return 0x515;
    }

    if ((flags & 0x40) == 0) {
        Sound_SetC000(sp->wram);
        Sound_SetE000(sp->wram);
        count = 0;
        uVar4 = 0;

        do {
            if (!(count & 7) && 0x40 <= count && count < 0x90) {

                uVar1 = count - 0x40 >> 3 & 0x3fffffff;

                Sound_Write((u16)sound_init_data[uVar1], (u8)sound_init_data[uVar1 + 1], uVar4);
            }

            Sound_Write(0, 0, uVar4);

            count++;
            uVar4 += 0x72;

        } while (count < 0x106);
    }

    if (flags & 1) {
        // temporarily save the work ram state.
        memcpy(&wp->work_priv.wram, &sp->wram, KS_NES_WRAM_SIZE);
    }

    // zero out the state struct.
    memset(sp, 0, sizeof(ksNesStateObj));

    if (flags & 1) {
        // restore the previously saved work ram state.
        memcpy(&sp->wram, &wp->work_priv.wram, KS_NES_WRAM_SIZE);
    } else {
        // fill ram with a predetermined pattern.

        iVar2 = 0;

        for (count = 0x200; count; count--) {
            wramp = &sp->wram[iVar2];

            wramp[0] = 0x0f;
            wramp[1] = 0xef;
            wramp[2] = 0xfe;
            wramp[3] = 0x7d;

            iVar2 += 4;
        }
    }

    // zero out the private work struct
    memset(&wp->work_priv, 0, sizeof(ksNesCommonWorkPriv));

    iVar4 = 0;
    iVar2 = 0;

    // the state struct is (mostly) zeroed out.
    // this sets up some self referential pointer in the state struct for an unknown reason.
    for (count = 0x18; count; count--) {
        sp->_186C[iVar2] = &sp->_0800[table[iVar4 & 0xf] * 0x100];
        iVar4++;
        iVar2++;
    }

    sp->nesromp = wp->nesromp;
    nesromp = sp->nesromp;

    if (nesromp[0] == 1) {
        if (((chrramp == nullptr) || (bbramp == nullptr)) || ((flags & 0x10) == 0)) {
            return 0x570;
        }
        memcpy(&sp->_1810[0], &sp->_186C[0xc], 0x10);
        sp->_1768[0x2] = wp->_001D;
    } else {
        // extract the mapper number from the ines header
        sp->mapper = (nesromp[7] & 0xf0) | (nesromp[6] >> 4);

        // skip over the ines header to grab a pointer to the prg rom data.
        sp->prgromp = sp->nesromp + KS_NES_NESFILE_HEADER_SIZE;

        // extract the prg rom size from the ines header and convert it from 16k chunks to bytes.
        sp->prg_size = (uint)sp->nesromp[0x4] << 0xe;

        if (sp->prg_size > wp->prg_size) {
            return 0x57a;
        }

        // calculate the number of 8k PRG ROM banks.
        sp->prg_banks = (sp->prg_size >> 0xd) - 1;

        // extract the chr ram/rom size from the ines header and convert it from 8k chunks to bytes.
        sp->chr_size = (size_t)sp->nesromp[0x5] << 0xd;

        if ((sp->chr_size > 0x40000) && ((sp->mapper != 5 || (wp->chr_to_i8_buf_size < sp->chr_size << 2)))) {
            return 0x584;
        }

        // i think this is reading the ppu mirroring configuration from the ines header
        // and doing... something based on it.
        // TODO: check the nes rom injection tool to see if this flag is what i think it is.
        if ((sp->nesromp[0x6] & 1)) {
            memcpy(&sp->_1810[0], &sp->_186C[0x8], 0x10);
        } else {
            memcpy(&sp->_1810[0], &sp->_186C[0xc], 0x10);
        }
    }

    sp->reset_flags = flags;

    if (sp->mapper == 5) {
        ksNesDrawMakeOBJIndTexMMC5(wp);
    } else {
        ksNesDrawMakeOBJIndTex(wp);
    }

    if ((flags & 0x20) == 0) {
        memcpy(sp->palette_normal, &ksNesPaletteNormal, 0x80);
    }

    iVar2 = 0;

    for (count = 0x80; count; count--) {
        sp->_16CC[iVar2] = 0x0f;
        iVar2++;
    }

    iVar2 = 0;

    for (count = 8; count; count--) {
        sp->_16A0[iVar2] = 0x20;
        iVar2++;
    }

    iVar2 = 0;

    // i think we're dealing a new type of struct here.
    for (count = 0xf0; count; count--) {
        wp->work_priv._0B40[iVar2] = sp->_1810[0];
        wp->work_priv._0B40[iVar2 + 1] = sp->_1810[1];
        iVar2 += 8;
    }

    iVar2 = 0;

    for (count = 8; count; count--) {
        sp->_17FC[iVar2] = (u8)iVar2;
        iVar2++;
    }

    memset(wp->chr_to_u8_bufp, 0, wp->chr_to_i8_buf_size);

    if (sp->chr_size == 0) {
        if (chrramp == nullptr) {
            return 0x5be;
        }

        sp->_1768[0x1] = 1;
        sp->chrramp = chrramp;
        sp->chr_size = 0x2000;

        if (((flags & 8) != 0) && (sp->mapper == 5)) {
            sp->chr_size = 0x20000;
        }

        if ((flags & 2) == 0) {
            memset(sp->chrramp, 0, sp->chr_size);
        }

    } else {
        sp->chrramp = sp->prgromp + sp->prg_size;

        if (sp->mapper == 5) {
            for (uVar4 = 0; uVar4 < sp->chr_size; uVar4 = uVar4 + 0x10) {
                ksNesConvertChrToI8MMC5(wp, sp->chrramp + uVar4, uVar4 >> 4);
            }
        } else {
            for (uVar4 = 0; uVar4 < sp->chr_size; uVar4 = uVar4 + 0x10) {
                ksNesConvertChrToI8(wp, sp->chrramp + uVar4, uVar4 >> 4);
            }
        }
    }

    sp->chr_banks = (sp->chr_size >> 10) - 1;

    DCFlushRangeNoSync(wp->chr_to_u8_bufp, wp->chr_to_i8_buf_size);

    sp->_1822 = -0x1dbe; // -7614
    sp->_1824 = -0x2a00; // -10752
    sp->_1826 = -0x2800; // -10240

    sp->_1840 = ksNesLinecntIrqDefault;

    memcpy(sp->store_func, ksNesStoreFuncTblDefault, sizeof(ksNesStoreFuncTblDefault));
    memcpy(sp->store_ppu_func, ksNesStorePPUFuncTblDefault, sizeof(ksNesStorePPUFuncTblDefault));
    memcpy(sp->store_io_func, ksNesStoreIOFuncTblDefault, 0xa0);
    memcpy(sp->load_func, ksNesLoadFuncTblDefault, 0x20);
    memcpy(sp->load_io_func, ksNesLoadIOFuncTblDefault, 0x60);

    sp->cpu_0000_1fff = sp->wram;
    sp->cpu_2000_3fff = sp->wram - 0x2000;
    sp->cpu_4000_5fff = sp->wram - 0x4000;
    sp->cpu_6000_7fff = sp->wram - 0x6000;
    sp->cpu_8000_9fff = sp->prgromp - 0x8000;
    sp->cpu_a000_bfff = sp->prgromp - 0x8000;
    sp->cpu_c000_dfff = sp->prgromp + sp->prg_size - 0x10000;
    sp->cpu_e000_ffff = sp->prgromp + sp->prg_size - 0x10000;

    sp->bbramp = bbramp;

    if (bbramp) {
        sp->cpu_6000_7fff = bbramp - 0x6000;

        sp->store_func[3] = ksNesStoreBBRAM;
        sp->load_func[3] = ksNesLoadBBRAM;

        sp->_1768[0] = flags & 0x10 ? 3 : 0;
    }

    if (*sp->nesromp == 1) {
        // sp->_0800 + 0xdc0 overlaps the end of sp->store_io_func.
        // we should probably define a union or struct for the shared memory.
        memcpy(sp->store_io_func + 0x20, &ksNesStoreQDFuncTbl, 0x20);

        sp->cpu_8000_9fff = sp->bbramp - 0x6000;
        sp->cpu_a000_bfff = sp->bbramp - 0x6000;
        sp->cpu_c000_dfff = sp->bbramp - 0x6000;
        sp->cpu_e000_ffff = wp->noise_bufp - 0xe000;

        // unknown pointer types. leaving as void pointers for now.
        *(void**)(sp->_0800 + 0xdf0) = ksNesStoreBBRAM;
        *(void**)(sp->_0800 + 0xdf4) = ksNesStoreBBRAM;
        *(void**)(sp->_0800 + 0xdf8) = ksNesStoreBBRAM;
        sp->_1840 = ksNesLinecntIrqQD;

        wp->noise_bufp[0xebd] = 'B';
        sp->_1768[0x3] = 'G';
        sp->_16B2 = 'G';
        sp->_16B3 = 0x80;

        // looks to be a special case for one particular rom
        iVar2 = memcmp(sp->nesromp + KS_NES_NESFILE_HEADER_SIZE, "koro", 4);

        if (iVar2 == 0) {
            wp->noise_bufp[0x1a0] = 0xff;
        } else {
            wp->noise_bufp[0x1a0] = 0x7f;
        }
    } else {
        uVar2 = ksNesResetAsm(wp, sp);
        if (uVar2) {
            return uVar2;
        } else {
            // check some special cases for particular roms
            if (sp->prg_size == 0x20000) {
                iVar2 = memcmp(sp->prgromp + 0x1ffe8, "BomBliss", 8);
                if (iVar2 == 0) {
                    sp->_182E = '\x03';
                } else {
                    iVar2 = memcmp(sp->prgromp + 0x1fc01, "BY!\xc8\x0dSAT", 8);
                    if (iVar2 == 0) {
                        sp->_182E = '\x18';
                    }
                }
            }
        }
    }

    ksNesPushResetButton(sp);
    DCStoreRange(wp, 0x8f78);

    if ((flags & 0x40) == 0) {
        Sound_SetC000(&sp->cpu_c000_dfff[0xc000]);
        Sound_SetE000(&sp->cpu_e000_ffff[0xe000]);

        switch (sp->mapper) {
            case 5: // Nintendo's MMC5
                Sound_SetMMC(0);
                break;
            case 24: // Konami's VRC6a
            case 26: // Konami's VRC6b
                Sound_SetMMC(1);
                Sound_Write(0x5015, 7, 0);
                break;
            default: // all other mappers
                if (sp->nesromp[0] == 1) {
                    Sound_SetMMC(2);
                } else {
                    Sound_SetMMC(3);
                }
        }
    }

    os_tick = OSGetTick();
    sp->os_tick = os_tick;
    return 0; // return success.
}

void ksNesEmuFrame(ksNesCommonWorkObj* wp, ksNesStateObj* sp, u32 flags) {
    u8 status;
    size_t count = 0;

    sp->frame_flags = flags;

    while (true) {
        do {
            if ((flags & 0x1000) == 0) {
                status = Sound_Read(0x4015);
                sp->_1846[0xc] = sp->_1846[0xc] & 0xc0 | status;

                if (wp->frames != 1) {
                    sp->_1846[0xd] = 0xc0;
                    sp->_1846[0xc] = sp->_1846[0xc] & 0xc0;
                } else {
                    sp->_1846[0xd] = 0xff;
                }

                status = Sound_Read(0x5015);

                sp->_176E[0x47] = status & 0x03;

                Sound_SetC000(&sp->cpu_c000_dfff[0xc000]);
                Sound_SetE000(&sp->cpu_e000_ffff[0xe000]);
            }

            ksNesEmuFrameAsm(wp, sp);

        } while (((flags & 0x400) == 0) && ((sp->_16B8[0x11] & 0x02) == 0));

        if (((flags & 0x4000) == 0) || count == 0)
            break;

        count--;
    }

    PPCSync();

    return;
}

// clang-format off
asm u32 ksNesResetAsm(register ksNesCommonWorkObj* work, register ksNesStateObj* state)
{
    register void* func_tbl;
    register ksNesStateObj* state_temp;
    #define REGISTER_A r14
    #define REGISTER_X r15
    #define REGISTER_Y r16
    #define REGISTER_PC r17
    #define REGISTER_STACK r18
    #define REGISTER_FLAG_ZERO r19
    #define REGISTER_FLAG_CARRY r20
    #define REGISTER_FLAG_OVERFLOW r21
    #define REGISTER_FLAG_NEGATIVE r22
    #define WRAM r31
    nofralloc

    stwu r1, -0xf0(r1)
    mflr r0
    stw r0, 0xf4(r1)
    stw state_temp, 0xec(r1)
    stw func_tbl, 0xe8(r1)
    stw work, 0xe0(r1)
    stw state, 0xe4(r1)
    stw work, 0x08(r1)
    stw state, 0x0c(r1)

    mr state_temp, state

    li r3, 0 // return code
    lis func_tbl, ksNesMapperInitFuncTbl@h
    ori func_tbl, func_tbl, ksNesMapperInitFuncTbl@l

    // return an error if the mapper number is greater than the highest supported mapper.
    lbz r7, state_temp->mapper
    cmpwi r7, sizeof(ksNesMapperInitFuncTbl) / sizeof(ksNesMapperInitFuncTbl[0]) / 5
    blt init_mapper

mapper_error:
    li r3, 0x732
    b exit

init_mapper:
    mulli r7, r7, 0x14
    add func_tbl, func_tbl, r7

    // void* store_8000 = ksNesMapperInitFuncTbl[(mapper + 1) * 5];
    // void* store_a000 = ksNesMapperInitFuncTbl[(mapper + 2) * 5];
    // void* store_c000 = ksNesMapperInitFuncTbl[(mapper + 3) * 5];
    // void* store_e000 = ksNesMapperInitFuncTbl[(mapper + 4) * 5];
    lwz r7, 0x04(func_tbl)
    lwz r8, 0x08(func_tbl)
    lwz r9, 0x0c(func_tbl)
    lwz r10, 0x10(func_tbl)

    // state_temp->store_func[4] = store_8000;
    // state_temp->store_func[5] = store_a000;
    // state_temp->store_func[6] = store_c000;
    // state_temp->store_func[7] = store_e000;
    stw r7, state_temp->store_func[4]
    stw r8, state_temp->store_func[5]
    stw r9, state_temp->store_func[6]
    stw r10, state_temp->store_func[7]

    // return an error if the mapper number isn't supported.
    // all supported mappers have a non-null pointer defined for state->store_func[4].
    cmpwi r7, nullptr
    beq mapper_error

    // call the mapper-specific initialization function if one exists.
    // if (ksNesMapperInitFuncTbl[mapper * 5] != nullptr) {
    //     ksNesMapperInitFuncTbl[mapper * 5]();
    // }
    lwz r0, 0x00(func_tbl)
    mtctr r0
    cmpwi r0, nullptr
    bnectrl

    b exit

entry ksNesInit01
    li r8, 0x05
    stb r8, state_temp->_176E[0x20]

    li r8, 0x0f
    stb r8, state_temp->_176E[0x1b]

    lwz r9, state_temp->prg_size
    lis r8, 0x08
    cmpw r9, r8
    bnelr

    li r8, 0x01
    stb r8, state_temp->_176E[0x1f]

    li r8, 0x10
    stb r8, state_temp->_176E[0x1c]

    blr

entry ksNesInit03

    // state_temp->store_func[3] = store_8000;
    stw r7, state_temp->store_func[3]
    blr

entry ksNesInit04
    // state_temp->_1840 = (void *)0x8003c8e8; // ksNesLinecntIrq04
    lis r8, 0x8003 // ksNesLinecntIrq04@h
    ori r8, r8, 0xc8e8 // ksNesLinecntIrq04@l
    stw r8, state_temp->_1840

    blr

entry ksNesInit05
    // if (state_temp->bbramp == nullptr) {
    //     return 0x78e;
    // }
    lwz r8, state_temp->bbramp
    cmpwi r8, nullptr
    bne init_05
    li r3, 0x78e // error

init_05:
    // state_temp->_176E[0x2a] = 0x03;
    li r8, 0x03
    stb r8, state_temp->_176E[0x2a]

    // state_temp->_176E[0x2f] = 0xff;
    li r8, 0xff
    stb r8, state_temp->_176E[0x2f]

    // state_temp->_17B0[2] = 0x03;
    li r8, 0x03
    stb r8, state_temp->_17B0[2]

    // state_temp->_17B0[4] = 0x01;
    li r8, 0x01
    stb r8, state_temp->_17B0[4]

    // state_temp->store_func[2] = (void *)0x8003cba0; // ksNesStore05_4000
    lis r8, 0x8003 // ksNesStore05_4000@h
    ori r8, r8, 0xcba0 // ksNesStore05_4000@l
    stw r8, state_temp->store_func[2]

    // state_temp->load_func[2] = (void *)0x8003d01c; // ksNesLoad05_4000
    lis r8, 0x8003 // ksNesLoad05_4000@h
    ori r8, r8, 0xd01c // ksNesLoad05_4000@l
    stw r8, state_temp->load_func[2]

    // state_temp->_1840 = (void *)0x8003cb8c; // ksNesLinecntIrq05Vcount
    lis r8, 0x8003 // ksNesLinecntIrq05Vcount@h
    ori r8, r8, 0xcb8c // ksNesLinecntIrq05Vcount@l
    stw r8, state_temp->_1840

    blr

entry ksNesInit07
    // state_temp->cpu_c000_dfff = state_temp->cpu_8000_9fff;
    // state_temp->cpu_e000_ffff = state_temp->cpu_8000_9fff;
    lwz r8, state_temp->cpu_8000_9fff
    stw r8, state_temp->cpu_c000_dfff
    stw r8, state_temp->cpu_e000_ffff

    blr

entry ksNesInit09
    // state_temp->cpu_a000_bfff = state_temp->cpu_c000_dfff;
    lwz r8, state_temp->cpu_c000_dfff
    stw r8, state_temp->cpu_a000_bfff

    blr

entry ksNesInit12
    // state_temp->_1840 = (void *)0x8003d1e4; // ksNesLinecntIrq49
    lis r8, 0x8003 // ksNesLinecntIrq49@h
    ori r8, r8, 0xd1e4 // ksNesLinecntIrq49@l
    stw r8, state_temp->_1840

    blr

entry ksNesInit13
    // if (state_temp->bbramp == nullptr) {
    //     return 0x7c3;
    // }
    lwz r8, state_temp->bbramp
    cmpwi r8, nullptr
    bne init_13
    li r3, 0x7c3

    blr

init_13:
    // state_temp->store_func[2] = (void *)0x8003d368; // ksNesStore13_4000
    lis r8, 0x8003 // ksNesStore13_4000@h
    ori r8, r8, 0xd368 // ksNesStore13_4000@l
    stw r8, state_temp->store_func[2]

    // state_temp->load_func[2] = (void *)0x8003d3dc; // ksNesLoad13_4000
    lis r8, 0x8003 // ksNesLoad13_4000@h
    ori r8, r8, 0xd3dc // ksNesLoad13_4000@l
    stw r8, state_temp->load_func[2]

    // state_temp->_1840 = (void *)0x8003d1e4; // ksNesLinecntIrq49
    lis r8, 0x8003 // ksNesLinecntIrq49@h
    ori r8, r8, 0xd1e4 // ksNesLinecntIrq49@l
    stw r8, state_temp->_1840

    blr

entry ksNesInit15
    // state_temp->_1840 = (void *)0x8003d754; // ksNesLinecntIrq19
    lis r8, 0x8003 // ksNesLinecntIrq19@h
    ori r8, r8, 0xd754 // ksNesLinecntIrq19@l
    stw r8, state_temp->_1840

    blr

entry ksNesInit18
    // state_temp->_17B0[0x1e] = 0x01;
    li r8, 0x01
    stb r8, state_temp->_17B0[0x1e]

    // state_temp->_1840 = (void *)0x8003d5d8; // ksNesLinecntIrq18
    lis r8, 0x8003 // ksNesLinecntIrq18@h
    ori r8, r8, 0xd5d8 // ksNesLinecntIrq18@l
    stw r8, state_temp->_1840

    blr

entry ksNesInit1a
    // state_temp->_17B0[0x1d] = 0x03;
    li r8, 0x03;
    stb r8, state_temp->_17B0[0x1d]

    // state_temp->_17B0[0x1e] = 0x02;
    li r8, 0x02;
    stb r8, state_temp->_17B0[0x1e]

    // state_temp->_1840 = (void *)0x8003d5d8; // ksNesLinecntIrq18
    lis r8, 0x8003 // ksNesLinecntIrq18@h
    ori r8, r8, 0xd5d8 // ksNesLinecntIrq18@l
    stw r8, state_temp->_1840

    blr

entry ksNesInit42
    // state_temp->store_func[3] = store_8000;
    // state_temp->cpu_c000_dfff = state_temp->cpu_8000_9fff;
    // state_temp->cpu_e000_ffff = state_temp->cpu_8000_9fff;
    lwz r9, state_temp->cpu_8000_9fff
    stw r7, state_temp->store_func[3]
    stw r9, state_temp->cpu_c000_dfff
    stw r9, state_temp->cpu_e000_ffff

    blr

entry ksNesInit43
    // state_temp->_1840 = (void *)0x8003d928; // ksNesLinecntIrq43
    lis r8, 0x8003 // ksNesLinecntIrq43@h
    ori r8, r8, 0xd928 // ksNesLinecntIrq43@l
    stw r8, state_temp->_1840

    blr

entry ksNesInit45
    // state_temp->_1840 = (void *)0x8003d1e4; // ksNesLinecntIrq49
    lis r8, 0x8003 // ksNesLinecntIrq49@h
    ori r8, r8, 0xd1e4 // ksNesLinecntIrq49@l
    stw r8, state_temp->_1840

    // state_temp->store_func[3] = (void*)0x8003ada4; // ksNesLinecntIrqDefault
    lis r8, 0x8003 // ksNesLinecntIrqDefault@h
    ori r8, r8, 0xada4 // ksNesLinecntIrqDefault@l
    stw r8, state_temp->store_func[3]

    blr

entry ksNesInit49
    // state_temp->_1840 = (void *)0x8003d1e4; // ksNesLinecntIrq49
    lis r8, 0x8003 // ksNesLinecntIrq49@h
    ori r8, r8, 0xd1e4 // ksNesLinecntIrq49@l
    stw r8, state_temp->_1840

    blr

entry ksNesInit56
    // state_temp->store_func[3] = (void *)0x8003dd3c; // ksNesStore56_6000
    lis r8, 0x8003 // ksNesStore56_6000@h
    ori r8, r8, 0xdd3c // ksNesStore56_6000@l
    stw r8, state_temp->store_func[3]

    blr

exit:
    lwz state_temp, 0xec(r1)
    lwz func_tbl, 0xe8(r1)
    lwz r0, 0xf4(r1)
    mtlr r0
    addi r1, r1, 0xf0
    blr
}

asm void ksNesEmuFrameAsm(register ksNesCommonWorkObj* work_arg, register ksNesStateObj* state_arg) {
    register int local_25;
    register int local_26;
    register int local_27;
    register int local_28;
    register int local_29;

    register void* state_cpu_ranges;
    register void* state_store_func;
    register void* state_load_func;
    register void* instr_jump_tbl;      // r30
    register ksNesStateObj* state_temp; // r31
    fralloc
    stw r3, 0xe0(r1)
    stw r4, 0xe4(r1)
    stw r3, 0x08(r1)
    stw r4, 0x0c(r1)
    mr state_temp, r4
    addi r7, r3, 0x0ba0
    stw r7, 0xf4(r1)
    lwz r7, 0x14(r3)
    stw r7, 0xf0(r1)
    lbz r7, 0x1c(r3)
    stw r7, 0xec(r1)

    // r8 = state_temp->frame_flags & 0x4000 ? 2 : 0
    lwz r7, state_temp->frame_flags
    andi. r8, r7, 0x4000
    beq asdfasdf
    li r8, 2
asdfasdf:
    stw r8, 0xe8(r1)

    // state_temp->_1A70++;
    lwz r7, state_temp->_1A70
    addi r7, r7, 1
    stw r7, state_temp->_1A70

    lhz r17, state_temp->PC
    lbz REGISTER_A, state_temp->_1846[0] // A
    lbz REGISTER_X, state_temp->_1846[1] // X
    lbz REGISTER_Y, state_temp->_1846[2] // Y
    lbz r18, state_temp->_1846[3] // C?
    lbz r19, state_temp->_1846[4] // Z?
    lbz r20, state_temp->_1846[5] // I?
    lbz r21, state_temp->_1846[6] // V?
    lbz r22, state_temp->_1846[7] // N
    // no D or B flag?

    lis instr_jump_tbl, ksNesInstJumpTbl@h
    ori instr_jump_tbl, instr_jump_tbl, ksNesInstJumpTbl@l

    // r29 = &state_temp->load_func
    addi state_load_func, state_temp, state_temp.load_func

    // r28 = &state_temp->store_func
    addi state_store_func, state_temp, state_temp.store_func

    // r27 = &state_temp->cpu_0000_1fff
    addi state_cpu_ranges, state_temp, state_temp.cpu_0000_1fff

    lwz r25, state_temp->_1838 // total_cycles?

// SUB_8003ada4
entry ksNesLinecntIrqDefault
    cmpwi r25, 0
    bge somewhere

entry ksNesMainLoop2
ksNesMainLoop1:
    // r26 = (r17 >> 11) & 0x1C;
    // address range | r26  | description
    // --------------+------+--------------------------
    // 0x0000–0x1FFF | 0x00 | internal RAM and mirrors
    // 0x2000–0x3FFF | 0x04 | PPU registers and mirrors
    // 0x4000-0x5FFF | 0x08 | APU, I/O, and usually unmapped cartridge addresses
    // 0x6000–0x7FFF | 0x0C | usually cartridge RAM
    // 0x8000–0x9FFF | 0x10 | usually cartridge ROM and mapper registers
    // 0xA000–0xBFFF | 0x14 | usually cartridge ROM and mapper registers
    // 0xC000–0xDFFF | 0x18 | usually cartridge ROM and mapper registers
    // 0xE000–0xFFFF | 0x1C | usually cartridge ROM and mapper registers
    rlwinm r26, REGISTER_PC, 21, 27, 29

    // r0 = r17 - 0x2000;
    // subtract 0x2000 from the PC.
    // if PC points to the NES's internal 2k of RAM or one if its mirrors,
    // then r0 will be negative.
    // r0 will be positive otherwise.
    //
    // address range | size   | description
    // --------------+--------+----------------------
    // 0x0000–0x07FF | 0x0800 | 2 KB internal RAM
    // 0x0800–0x0FFF | 0x0800 | mirror of $0000–$07FF
    // 0x1000–0x17FF | 0x0800 | mirror of $0000–$07FF
    // 0x1800–0x1FFF | 0x0800 | mirror of $0000–$07FF
    subi r0, REGISTER_PC, 0x2000

    // r7 = state_cpu_ranges[r26];
    // select 1 of 8 pointers to an 8k range of the CPU address space.
    lwzx r7, state_cpu_ranges, r26

    // r0 = (r0 >> 16) & 0xF800;
    // if r0 is negative then r0 = 0x00000000
    // if r0 is positive then r0 = 0x0000F800
    // r0 will be used as a bitmask later.
    rlwinm r0, r0, 16, 16, 20

    // r17 = r17 & 0xFFFF;
    // restrict PC to a 16-bit value.
    andi. r17, r17, 0xFFFF

    // r17 = r17 & ~r0;
    // if PC points to RAM or one of its mirrors then ~r0 will be 0xFFFF07FF.
    // ~r0 will be 0xFFFFFFFF otherwise.
    // that redirects RAM mirror access to actual RAM or leaves PC unchanged otherwise.
    andc r17, r17, r0

    // r12 = (u8) r7[r17];
    // grab the byte pointed to by PC.
    // this should be an instruction opcode.
    lbzx r12, r7, r17

    // r4 = r17 + 1;
    // get the address of the byte following PC.
    addi r4, r17, 1

    // r26 = (r4 >> 11) & 0x1C;
    // check which CPU range the next byte falls into.
    rlwinm r26, r4, 21, 27, 29

    // r7 = r12 << 4;
    // shift the opcode byte by 4, effectively multiplying by 16.
    // that allows r7 to be used as an offset into instr_jump_tbl
    // since every item in that array is 16 bytes.
    slwi r7, r12, 4

    // r26 = state_cpu_ranges[r26];
    // get a pointer to the range containing the byte following the one pointed to by PC.
    lwzx r26, state_cpu_ranges, r26

    // r8 = instr_jump_tbl[r7]
    // r7 = &instr_jump_tbl[r7]
    // grab a pointer to the first handler function for this instruction.
    lwzux r8, r7, instr_jump_tbl

    // r10 = r7[1]
    // grab size and cycle information about this instruction
    lhz r10, 0x04(r7)

    // r9 = r7[2]
    // grab a pointer to the second handler function for this instruction.
    // may be a null pointer.
    lwz r9, 0x08(r7)

    // lr = r8
    // put the address of the first handler in the link register
    // we'll use this to call the function shortly
    mtlr r8

    andi. r11, r10, 0x00ff // instruction bytes
    andi. r10, r10, 0xff00 // instruction cycles << 8

    // ctr = r9
    // put the address of the second handler in the counter register
    // it may be called later if it isn't null.
    mtctr r9

    // r4 = (u8) r26[r4]
    // get the byte following the one pointed to by PC.
    lbzx r4, r26, r4

    // r17 += r11
    // advance PC to the next instruction?
    add r17, r17, r11

    // r25 += r10
    // increase the total cycle count by the number of cycles this instruction takes?
    add r25, r25, r10

    // r4  == the byte following the instruction opcode
    // r10 == instruction cycle count shifted left by 8 bits
    // r11 == instruction length in bytes
    // r17 == 6502 address of the next instruction
    // r25 == something to do with cycle count
    // r26 == pointer to the range containing the byte following the instruction opcode
    // ctr == pointer to a second handler function, if any
    // lr()
    blrl

    // while (r25 < 0)
    cmpwi r25, 0
    blt ksNesMainLoop1

somewhere:
    lha r3, state_temp->_1820
    clrlslwi. r7, r25, 30, 3
    lha r9, state_temp->_1824
    rlwimi r25, r25, 31, 30, 31
    beq LAB_8003b2f0

    cmpwi r3, 0
    add r25, r25, r9
    blt LAB_8003b4b8

    cmpwi r3, 0xf0
    bge LAB_8003b3b4

    lwz r9, 0xf4(r1)
    slwi r8, r3, 5
    lwz r0, state_temp->_17FC
    lwz r10, state_temp->_17FC[4]
    add  r26, r8, r9
    stwux r0, r7, r26
    andi. r0, r25, 0x1
    stw r10, 0x4(r7)
    bne ksNesMainLoop1

    lhz r0, state_temp->_16A0[8]
    lbz r8, state_temp->_17B0[22]
    lbz r7, state_temp->mapper
    rlwimi r0, r8, 0x9, 0x10, 0x11
    sth r0, 0x18(r26)
    cmpwi r7, 0x5
    bne LAB_8003b19c

    lbz r7, state_temp->_17B0[23]
    stb r0, state_temp->_17B0[23]
    xor r9, r7, r0
    and r9, r9, r7
    andi.      r9, r9, 0x8
    beq        LAB_8003aecc
    cmpwi      r8, 0x60
    bge        LAB_8003aecc
    addi       r7, state_temp, state_temp._16CC
    addi       r9, r8, 0x20
    add        r8, r8, r7
    stb        r9, state_temp->_17B0[22]
    rlwimi     r0, r9, 0x9, 0x10, 0x11
    sth        r0, 0x18(r26)
    add        r9, r9, r7
    lswi       r3, r8, 0x10
    addi       r8, r8, 0x10
    stswi      r3, r9, 0x10
    addi       r9, r9, 0x10
    lswi       r3, r8, 0x10
    stswi      r3, r9, 0x10
    lha        r3, state_temp->_1820

LAB_8003aecc:
    lbz        r7, state_temp->_176E[48]
    lhz        r8, state_temp->chr_banks
    lbz        r9, state_temp->_176E[57]
    cmpwi      r7, 0x2
    bge        LAB_8003af34
    cmpwi      r7, 0x0
    bne        LAB_8003af00
    rlwinm     r9, r9, 0x3, 0x0, 0x1c
    and        r9, r9, r8
    rlwinm     r10, r9, 0x18, 0x8, 0x1f
    subi       r10, r10, 0x1
    xori       r10, r10, 0xff
    b          LAB_8003afc4
LAB_8003af00:
    rlwinm     r9, r9, 0x2, 0x0, 0x1d
    and        r9, r9, r8
    rlwinm     r10, r9, 0x18, 0x8, 0x1f
    lbz        r9, state_temp->_176E[53]
    subi       r10, r10, 0x1
    xori       r10, r10, 0xff
    rlwinm     r9, r9, 0x2, 0x0, 0x1d
    and        r9, r9, r8
    rlwinm     r9, r9, 0x18, 0x8, 0x1f
    subi       r9, r9, 0x1
    xori       r9, r9, 0xff
    rlwimi     r10, r9, 0x0, 0x18, 0x1b
    b          LAB_8003afc4
LAB_8003af34:
    cmpwi      r7, 0x2
    bne        LAB_8003afa8
    rlwinm     r9, r9, 0x1, 0x0, 0x1e
    and        r9, r9, r8
    rlwinm     r10, r9, 0x18, 0x8, 0x1f
    lbz        r9, state_temp->_176E[55]
    subi       r10, r10, 0x1
    xori       r10, r10, 0xff
    rlwinm     r9, r9, 0x1, 0x0, 0x1e
    and        r9, r9, r8
    rlwinm     r9, r9, 0x18, 0x8, 0x1f
    subi       r9, r9, 0x1
    xori       r9, r9, 0xff
    rlwimi     r10, r9, 0x0, 0x1c, 0x1d
    lbz        r9, state_temp->_176E[53]
    rlwinm     r9, r9, 0x1, 0x0, 0x1e
    and        r9, r9, r8
    rlwinm     r9, r9, 0x18, 0x8, 0x1f
    subi       r9, r9, 0x1
    xori       r9, r9, 0xff
    rlwimi     r10, r9, 0x0, 0x1a, 0x1b
    lbz        r9, state_temp->_176E[51]
    rlwinm     r9, r9, 0x1, 0x0, 0x1e
    and        r9, r9, r8
    rlwinm     r9, r9, 0x18, 0x8, 0x1f
    subi       r9, r9, 0x1
    xori       r9, r9, 0xff
    rlwimi     r10, r9, 0x0, 0x18, 0x19
    b          LAB_8003afc4
LAB_8003afa8:
    addi       r7, state_temp, state_temp._17FC[7]
    addi       r0, state_temp, state_temp._1804[7]
LAB_8003afb0:
    lbzu       r9, 0x1(r7)
    rlwinm     r10, r10, 0x1, 0x0, 0x1e
    rlwinm     r10, r9, 0x0, 0x1f, 0x1f
    cmpw       r7, r0
    bne        LAB_8003afb0
LAB_8003afc4:
    stb        r10, 0x1e(r26)
    lbz        r0, state_temp->_16A0[8]
    andi.      r0, r0, 0x20
    beq        LAB_8003b134
    lbz        r7, state_temp->_176E[48]
    lhz        r8, state_temp->chr_banks
    lbz        r9, state_temp->_176E[61]
    cmpwi      r7, 0x2
    bge        LAB_8003b054
    cmpwi      r7, 0x0
    bne        LAB_8003b01c
    rlwinm     r9, r9, 0x3, 0x0, 0x1c
    addi       r6, r26, 0xf
    and        r9, r9, r8
    addi       r0, r6, 0x8
LAB_8003b000:
    stbu       r9, 0x1(r6)
    rlwinm     r10, r10, 0x1, 0x0, 0x1e
    rlwimi     r10, r9, 0x18, 0x1f, 0x1f
    cmpw       r6, r0
    addi       r9, r9, 0x1
    bne        LAB_8003b000
    b          LAB_8003b138
LAB_8003b01c:
    rlwinm     r9, r9, 0x2, 0x0, 0x1d
    addi       r6, r26, 0x10
    and        r9, r9, r8
    addi       r0, r6, 0x4
LAB_8003b02c:
    stb        r9, 0x0(r6)
    rlwinm     r10, r10, 0x1, 0x0, 0x1e
    stb        r9, 0x4(r6)
    addi       r6, r6, 0x1
    rlwimi     r10, r9, 0x18, 0x1f, 0x1f
    cmpw       r6, r0
    addi       r9, r9, 0x1
    bne        LAB_8003b02c
    rlwimi     r10, r10, 0x4, 0x18, 0x1b
    b          LAB_8003b138
LAB_8003b054:
    cmpwi      r7, 0x2
    bne        LAB_8003b0b0
    rlwinm     r9, r9, 0x1, 0x0, 0x1e
    and        r9, r9, r8
    stb        r9, 0x12(r26)
    stb        r9, 0x16(r26)
    addi       r9, r9, 0x1
    stb        r9, 0x13(r26)
    stb        r9, 0x17(r26)
    rlwinm     r10, r9, 0x1d, 0x1a, 0x1a
    lbz        r9, 0x17a9(r31)
    rlwinm     r9, r9, 0x1, 0x0, 0x1e
    and        r9, r9, r8
    stb        r9, 0x10(r26)
    stb        r9, 0x14(r26)
    addi       r9, r9, 0x1
    stb        r9, 0x11(r26)
    stb        r9, 0x15(r26)
    rlwimi     r10, r8, 0x1f, 0x18, 0x18
    rlwinm     r9, r10, 0x1f, 0x1, 0x1f
    or         r10, r10, r9
    rlwimi     r10, r10, 0x1c, 0x18, 0x1b
    b          LAB_8003b138
LAB_8003b0b0:
    lbz        r10, 0x180f(r31)
    and        r9, r9, r8
    stb        r9, 0x13(r26)
    lbz        r9, 0x17aa(r31)
    and        r9, r9, r8
    stb        r9, 0x12(r26)
    lbz        r9, 0x17a9(r31)
    and        r9, r9, r8
    stb        r9, 0x11(r26)
    lbz        r9, 0x17a8(r31)
    and        r9, r9, r8
    stb        r9, 0x10(r26)
    lwz        r9, 0x10(r26)
    stw        r9, 0x14(r26)
    lbz        r9, 0x180e(r31)
    subi       r10, r10, 0x1
    lbz        r8, 0x180d(r31)
    xori       r10, r10, 0xff
    lbz        r0, 0x180c(r31)
    subi       r9, r9, 0x1
    andi.      r10, r10, 0x11
    xori       r9, r9, 0xff
    subi       r8, r8, 0x1
    andi.      r9, r9, 0x22
    li         r0, -0x1
    or         r10, r10, r9
    xori       r8, r8, 0xff
    xori       r0, r0, 0xff
    andi.      r8, r8, 0x44
    andi.      r0, r0, 0x88
    or         r10, r10, r8
    or         r10, r10, r0
    b          LAB_8003b138
LAB_8003b134:
    lbz        r10, 0x1e(r26)
LAB_8003b138:
    stb        r10, 0x1f(r26)
    lhz        r7, 0x1830(r31)
    addi       r0, r31, 0x1810
    xori       r9, r7, 0x100
    rlwinm     r8, r7, 0x1a, 0x1c, 0x1d
    rlwinm     r9, r9, 0x1a, 0x1c, 0x1d
    lwzx       r8, r8, r0
    lwzx       r9, r9, r0
    addi       r0, r31, 0x1000
    cmpw       r8, r0
    bne        LAB_8003b168
    lhz        r8, 0x17ac(r31)
LAB_8003b168:
    cmpw       r9, r0
    bne        LAB_8003b174
    lhz        r9, 0x17ac(r31)
LAB_8003b174:
    lbz        r0, 0x17b2(r31)
    lbz        r10, 0x17c0(r31)
    cmpwi      r0, 0x1
    bne        LAB_8003b188
    ori        r10, r10, 0x20
LAB_8003b188:
    stb        r10, 0x1d(r26)
    stw        r8, 0x0(r26)
    stw        r9, 0x4(r26)
    andi.      r4, r7, 0x7
    b          LAB_8003b1dc
LAB_8003b19c:
    lhz        r7, 0x1830(r31)
    addi       r0, r31, 0x1810
    xori       r9, r7, 0x100
    rlwinm     r8, r7, 0x1a, 0x1c, 0x1d
    rlwinm     r9, r9, 0x1a, 0x1c, 0x1d
    lwzx       r8, r8, r0
    lwzx       r9, r9, r0
    stw        r8, 0x0(r26)
    stw        r9, 0x4(r26)
    rlwinm     r8, r7, 0x1e, 0x1f, 0x1f
    rlwinm     r9, r7, 0x1, 0x0, 0x1e
    xor        r10, r7, r8
    xor        r9, r7, r9
    rlwinm     r10, r10, 0x1, 0x1e, 0x1e
    rlwimi     r8, r9, 0x0, 0x1d, 0x1d
    or         r4, r8, r10
LAB_8003b1dc:
    stb        r7, 0x1c(r26)
    add        r4, r31, r4
    addi       r8, r7, 0x1
    andi.      r0, r7, 0x300
    lbz        r10, 0x174c(r4)
    andi.      r8, r8, 0xff
    cmpwi      r8, 0xf0
    lbz        r9, 0x182f(r31)
    bne        LAB_8003b208
    xori       r0, r0, 0x200
    li         r8, 0x0
LAB_8003b208:
    sth        r9, 0x1a(r26)
    or         r8, r8, r0
    sth        r8, 0x1830(r31)
    subic.     r10, r10, 0x80
    lbz        r9, 0x175c(r4)
    beq        LAB_8003b230
    stb        r10, 0x174c(r4)
    stb        r3, 0x1754(r4)
    stb        r3, 0x175c(r4)
    b          LAB_8003b244
LAB_8003b230:
    subf       r8, r9, r3
    stb        r3, 0x175c(r4)
    rlwinm     r8, r8, 0x5, 0x0, 0x1a
    subf       r8, r8, r26
    stb        r3, 0x1a(r8)
LAB_8003b244:
    lbz        r8, 0x1020(r31)
    lbz        r10, 0x182c(r31)
    cmpw       r3, r8
    bne        LAB_8003b2d8
    lbz        r8, state_temp->_16A0[8]
    li         r0, 0x0
    lbz        r10, 0x1021(r31)
    andi.      r9, r8, 0x20
    beq        LAB_8003b270
    rlwinm     r0, r10, 0x3, 0x1c, 0x1c
    andi.      r10, r10, 0xfe
LAB_8003b270:
    xor        r8, r8, r0
    rlwinm     r0, r10, 0x1a, 0x1e, 0x1f
    rlwinm     r8, r8, 0x1f, 0x1d, 0x1d
    add        r0, r0, r31
    lwz        r7, 0x17f4(r31)
    add        r8, r8, r0
    lbz        r8, 0x17fc(r8)
    rlwinm     r10, r10, 0x4, 0x16, 0x1b
    add        r7, r7, r10
    rlwinm     r8, r8, 0xa, 0x0, 0x15
    add        r8, r8, r7
    li         r10, 0x0
LAB_8003b2a0:
    lbz        r0, 0x0(r8)
    lbz        r7, 0x8(r8)
    addi       r10, r10, 0x1
    or.        r7, r7, r0
    bne        LAB_8003b2d0
    andi.      r7, r10, 0x7
    addi       r8, r8, 0x1
    bne        LAB_8003b2a0
    subic.     r9, r9, 0x20
    addi       r8, r8, 0x8
    bge        LAB_8003b2a0
    li         r10, 0x1
LAB_8003b2d0:
    add        r10, r10, r3
    stb        r10, 0x182c(r31)
LAB_8003b2d8:
    cmpw       r3, r10
    bne        ksNesMainLoop1
    lbz        r8, 0x16a2(r31)
    ori        r8, r8, 0x40
    stb        r8, 0x16a2(r31)
    b          ksNesMainLoop1
LAB_8003b2f0:
    lwz        r8, 0x185c(r31)
    lwz        r5, 0xf0(r1)
    lbz        r7, 0xec(r1)
    andi.      r8, r8, 0x1000
    bne        LAB_8003b340
    divwu      r5, r5, r7
    li         r3, 0x0
    bl         Sound_Write
    li         r3, 0x4015
    bl         Sound_Read
    lbz        r7, 0x1852(r31)
    lbz        r8, 0x1853(r31)
    or         r7, r7, r3
    and        r7, r7, r8
    stb        r7, 0x1852(r31)
    li         r3, 0x5015
    bl         Sound_Read
    andi.      r3, r3, 0x3
    stb        r3, 0x17b5(r31)
    lha        r3, state_temp->_1820
LAB_8003b340:
    lha        r9, 0x1822(r31)
    addi       r8, r3, 0x1
    lwz        r7, 0xf0(r1)
    add        r25, r25, r9
    lha        r10, 0x1828(r31)
    lha        r9, 0x17ae(r31)
    sth        r8, state_temp->_1820
    addi       r7, r7, 0x72
    stw        r7, 0xf0(r1)
    cmpw       r8, r9
    beq        ksNesLinecntIrq05Timer // LAB_8003cb78
    cmpw       r8, r10
    bne        ksNesMainLoop1
    lbz        r7, 0x1855(r31)
    andi.      r7, r7, 0xc0
    bne        LAB_8003b390
    lbz        r7, 0x1852(r31)
    ori        r7, r7, 0x40
    stb        r7, 0x1852(r31)
    b          SUB_8003b3a0
LAB_8003b390:
    lwz        r8, 0x1840(r31)
    mtspr      CTR, r8
    lbz        r7, 0x1857(r31)
    bctr
 SUB_8003b3a0:
    lbz        r7, 0x184e(r31)
    andi.      r7, r7, 0x4
    stb        r7, 0x1856(r31)
    beq        ksNesActivateIntrIRQ // FUN_8003bc54
    b          ksNesMainLoop1
LAB_8003b3b4:
    lbz        r7, 0x16a2(r31)
    li         r8, 0xff
    stb        r8, 0x182c(r31)
    li         r8, 0x80
    li         r9, -0x16
    rlwimi     r7, r8, 0x0, 0x18, 0x19
    lwz        r8, 0x16b4(r31)
    stb        r7, 0x16a2(r31)
    sth        r9, state_temp->_1820
    lwz        r9, 0x8(r1)
    addi       r8, r8, 0x1
    stw        r8, 0x16b4(r31)
    lwz        r7, 0x44(r9)
    addi       r7, r7, 0x1
    stw        r7, 0x44(r9)
    lbz        r7, 0x176c(r31)
    cmpwi      r7, 0xc3
    bgt        LAB_8003b418
    cmpwi      r7, 0x78
    blt        LAB_8003b418
    lwz        r9, 0x8(r1)
    lwz        r8, 0x20(r9)
    rlwinm.    r8, r8, 0x1, 0x1f, 0x1f
    beq        LAB_8003b420
    li         r7, 0xc3
LAB_8003b418:
    addi       r7, r7, 0x1
    stb        r7, 0x176c(r31)
LAB_8003b420:
    lbz        r7, 0x16c9(r31)
    lbz        r8, 0x176d(r31)
    andi.      r0, r7, 0x2
    bne        LAB_8003b434
    li         r8, 0x5a
LAB_8003b434:
    subic.     r8, r8, 0x1
    bge        LAB_8003b440
    li         r8, 0x0
LAB_8003b440:
    stb        r8, 0x176d(r31)
    lwz        r9, 0x8(r1)
    li         r8, 0x80
    addi       r7, r31, 0x16cc
    mtspr      CTR, r8
    li         r8, 0x0
    addi       r9, r9, 0x2aa0
    addi       r3, r31, 0x18e8
LAB_8003b460:
    lbzx       r0, r7, r8
    rlwinm     r10, r8, 0x1, 0x1a, 0x1a
    rlwimi     r10, r8, 0x5, 0x17, 0x18
    rlwimi     r10, r8, 0x4, 0x15, 0x16
    rlwinm     r0, r0, 0x1, 0x0, 0x1e
    lhzx       r0, r3, r0
    rlwimi     r10, r8, 0x1, 0x1d, 0x1e
    addi       r8, r8, 0x1
    sthx       r0, r9, r10
    bdnz       LAB_8003b460
    lbz        r8, state_temp->_17B0[22]
    addi       r7, r31, 0x16cc
    add        r8, r8, r7
    lswi       r3, r8, 0x10
    addi       r8, r8, 0x10
    stswi      r3, r7, 0x10
    addi       r7, r7, 0x10
    lswi       r3, r8, 0x10
    stswi      r3, r7, 0x10
    li         r8, 0x0
    stb        r8, state_temp->_17B0[22]
    b          LAB_8003b570
LAB_8003b4b8:
    add        r25, r25, r9
    rlwinm     r25, r25, 0x0, 0x0, 0x1d
    cmpwi      r3, -0x15
    bne        LAB_8003b4fc
    li         r7, 0x0
    stb        r7, 0x17b6(r31)
    lbz        r8, state_temp->_16A0[8]
    lha        r7, 0x1826(r31)
    andi.      r8, r8, 0x80
    add        r25, r25, r7
    beq        ksNesMainLoop1
    lis        r0, ksNesMainLoop2@h
    nop
    lis        r7, 0x0
    ori        r7, r7, 0xfffa
    mtspr      CTR, r0
    b          ksNesActivateIntr
LAB_8003b4fc:
    cmpwi      r3, -0x1
    bne        ksNesMainLoop1
    lbz        r7, 0x16a2(r31)
    lhz        r8, 0x1834(r31)
    andi.      r7, r7, 0x3f
    sth        r8, 0x1830(r31)
    stb        r7, 0x16a2(r31)
    li         r8, 0x0
    sth        r8, 0x17c4(r31)
    lbz        r7, 0x16a9(r31)
    stb        r7, 0x17c7(r31)
    addi       r7, r31, 0x174c
    li         r8, 0x0
    li         r9, 0x0
    stswi      r8, r7, 0x8
    lbz        r8, 0x1764(r31)
    cmpwi      r8, 0x5
    bne        LAB_8003b54c
    li         r7, 0x40
    stb        r7, 0x17b6(r31)
LAB_8003b54c:
    lwz        r9, 0x8(r1)
    li         r0, 0x40
    addi       r7, r31, 0x101c
    mtctr      r0
    addi       r9, r9, 0x299c
LAB_8003b560:
    lwzu       r0, 0x4(r7)
    stwu       r0, 0x4(r9)
    bdnz       LAB_8003b560
    b          ksNesMainLoop1
LAB_8003b570:
    sth        r17, 0x1844(r31)
    stb        r14, 0x1846(r31)
    stb        r15, 0x1847(r31)
    stb        r16, 0x1848(r31)
    stb        r18, 0x1849(r31)
    stb        r19, 0x184a(r31)
    stb        r20, 0x184b(r31)
    cmpwi      r21, 0x0
    beq        LAB_8003b598
    li         r21, 0x40
LAB_8003b598:
    stb        r21, 0x184c(r31)
    stb        r22, 0x184d(r31)
    stw        r25, 0x1838(r31)
    lwz        r3, 0x8(r1)
    lwz        r7, 0xf0(r1)
    lwz        r8, 0x18(r3)
    stw        r7, 0x14(r3)
    add        r8, r8, r7
    stw        r8, 0x18(r3)
    frfree
    blr

// load a 16-bit immediate value into r3.
// calls: CTR
// < r4 = the first byte (low byte) of a 16-bit immediate
// < r17 = 16-bit 6502 address of the following instruction
// > r3 = 16-bit immediate value following the opcode
// > r26 = ???
entry ksNesInst_load16_imm
    // decrement r17 by 1 to get the address of the high byte of the 16-bit immediate
    subi r7, r17, 0x1

    // get the high byte of the 16-bit immediate from somewhere in memory
    // r8 = (r7 >> 11) & 0x1C;
    rlwinm r8, r7, 21, 27, 29
    // r9 = state_cpu_ranges[r8]
    lwzx r9, state_cpu_ranges, r8
    // r8 = r9[r7]
    lbzx r8, r9, r7

    // r26 = (r8 >> 3) & 0x1C;
    // why?
    rlwinm r26, r8, 29, 27, 29

    // r8 = r8 << 8
    slwi r8, r8, 8

    // combine the low and high bytes of the 16-bit immediate
    // r4 already had the low byte
    or r3, r4, r8

    // call the second handler for this instruction
    bctr

entry ksNesInst_load8_abs
    subi r7, r17, 0x1
    rlwinm r8, r7, 21, 27, 29
    lwzx r9, state_cpu_ranges, r8
    lbzx r8, r9, r7
    rlwinm r26, r8, 29, 27, 29
    slwi r8, r8, 8

    // get a pointer to a function for loading bytes
    // r9 = state_load_func[r26]
    lwzx r9, state_load_func, r26

    or r3, r4, r8
    mtspr LR, r9
    blr

entry ksNesInst_load8_absx
    subi       r7, r17, 0x1
    add        r4, r4, r15
    rlwinm     r8, r7, 0x15, 0x1b, 0x1d
    lwzx       r9, r27, r8
    lbzx       r8, r9, r7
    rlwinm     r8, r8, 0x8, 0x0, 0x17
    add        r3, r8, r4
    rlwinm     r26, r3, 0x15, 0x1b, 0x1d
    lwzx       r9, r29, r26
    mtlr       r9
    blr

entry ksNesInst_load8_absy
    subi       r7, r17, 0x1
    add        r4, r4, r16
    rlwinm     r8, r7, 0x15, 0x1b, 0x1d
    lwzx       r9, r27, r8
    lbzx       r8, r9, r7
    rlwinm     r8, r8, 0x8, 0x0, 0x17
    add        r3, r8, r4
    rlwinm     r26, r3, 0x15, 0x1b, 0x1d
    lwzx       r9, r29, r26
    mtlr       r9
    blr

entry ksNesInst_load8_zerop
    or         r3, r4, r4
    lbzx       r4, r31, r4
    li         r26, 0x0
    bctr

entry ksNesInst_load8_dx
    add        r3, r4, r15
    li         r26, 0x0
    andi.      r3, r3, 0xff
    lbzx       r4, r31, r3
    bctr

entry ksNesInst_load8_dxi
    add        r8, r4, r15
    andi.      r7, r8, 0xff
    addi       r8, r8, 0x1
    lbzx       r3, r31, r7
    andi.      r8, r8, 0xff
    lbzx       r8, r31, r8
    rlwinm     r26, r8, 0x1d, 0x1b, 0x1d
    rlwimi     r3, r8, 0x8, 0x10, 0x17
    lwzx       r9, r29, r26
    mtlr       r9
    blr

entry ksNesInst_load8_dyi
    lbzx       r3, r31, r4
    addi       r4, r4, 0x1
    andi.      r4, r4, 0xff
    lbzx       r8, r31, r4
    add        r3, r3, r16
    rlwinm     r8, r8, 0x8, 0x0, 0x17
    add        r3, r8, r3
    rlwinm     r26, r3, 0x15, 0x1b, 0x1d
    lwzx       r9, r29, r26
    mtlr       r9
    blr

// https://www.masswerk.at/6502/6502_instruction_set.html

//      addressing	assembler	  opc bytes cycles
// LDA (indirect,X)	LDA (oper,X)	A1	2	6
entry ksNesInst_lda_a1
    mr REGISTER_FLAG_ZERO, r4
    andi. REGISTER_FLAG_NEGATIVE, r4, 0x80
    mr REGISTER_A, r4
    b ksNesLinecntIrqDefault

// LDX zeropage,Y	LDX oper,Y	B6	2	4  
entry ksNesInst_ldx_b6
    add r7, r4, REGISTER_Y
    andi. r7, r7, 0xff
    lbzx r4, WRAM, r7
// fallthrough

// LDX immediate	LDX #oper	A2	2	2
entry ksNesInst_ldx_a2
    mr REGISTER_FLAG_ZERO, r4
    andi. REGISTER_FLAG_NEGATIVE, r4, 0x80
    mr REGISTER_X, r4
    b ksNesLinecntIrqDefault

// LDY immediate	LDY #oper	A0	2	2  
entry ksNesInst_ldy_a0
    mr REGISTER_FLAG_ZERO, r4
    andi. REGISTER_FLAG_NEGATIVE, r4, 0x80
    mr REGISTER_Y, r4
    b ksNesLinecntIrqDefault

// STA zeropage	    STA oper	85	2	3  
entry ksNesInst_sta_85
    stbx REGISTER_A, WRAM, r4
    b ksNesLinecntIrqDefault

// STX zeropage	    STX oper	86	2	3  
entry ksNesInst_stx_86
    stbx REGISTER_X, WRAM, r4
    b ksNesLinecntIrqDefault

// STY zeropage	    STY oper	84	2	3  
entry ksNesInst_sty_84
    stbx REGISTER_Y, WRAM, r4
    b ksNesLinecntIrqDefault

// STA zeropage,X	STA oper,X	95	2	4  
entry ksNesInst_sta_95
    add r7, r4, REGISTER_X
    andi. r7, r7, 0xff
    stbx REGISTER_A, WRAM, r7
    b ksNesLinecntIrqDefault

// STX zeropage,Y	STX oper,Y	96	2	4  
entry ksNesInst_stx_96
    add r7, r4, REGISTER_Y
    andi. r7, r7, 0xff
    stbx REGISTER_X, WRAM, r7
    b ksNesLinecntIrqDefault

// STY zeropage,X	STY oper,X	94	2	4  
entry ksNesInst_sty_94
    add r7, r4, REGISTER_X
    andi. r7, r7, 0xff
    stbx REGISTER_Y, WRAM, r7
    b ksNesLinecntIrqDefault

//STA absolute	    STA oper	8D	3	4  
entry ksNesInst_sta_8d
    lwzx r8, r28, r26
    mr r4, REGISTER_A
    mtctr r8
    bctr

//STX absolute	    STX oper	8E	3	4  
entry ksNesInst_stx_8e
    lwzx r8, r28, r26
    mr r4, REGISTER_X
    mtctr r8
    bctr

// STY absolute     STY oper	8C	3	4  
entry ksNesInst_sty_8c
    lwzx r8, r28, r26
    mr r4, REGISTER_Y
    mtctr r8
    bctr

// STA  absolute,X	STA oper,X	9D	3	5  
entry ksNesInst_sta_9d
    add r3, r3, REGISTER_X
    mr r4, REGISTER_A
    rlwinm r26, r3, 21, 27, 29 //  (r3 >> 11) & 0x1C
    lwzx r8, r28, r26
    mtctr r8
    bctr

// STA  absolute,Y	STA oper,Y	99	3	5  
entry ksNesInst_sta_99
    add r3, r3, REGISTER_Y
    mr r4, REGISTER_A
    rlwinm r26, r3, 21, 27, 29 //  (r3 >> 11) & 0x1C
    lwzx r8, r28, r26
    mtctr r8
    bctr

// STA  (indirect,X)    STA (oper,X)	81	2	6  
entry ksNesInst_sta_81
    addi r8, r3, 0x1
    andi. r8, r8, 0xff
    lbzx r3, WRAM, r8
    rlwinm r26, r3, 29, 27, 29 // (r3 >> 3) & 0x1C;
    slwi r3, r3, 8
    lwzx r8, r28, r26
    or r3, r3, r4
    mtctr r8
    mr r4, REGISTER_A
    bctr

//STA   (indirect),Y	STA (oper),Y	91	2	6  
entry ksNesInst_sta_91
    lbzx r3, WRAM, r4
    addi r8, r4, 0x1
    andi. r8, r8, 0xff
    lbzx r4, WRAM, r8
    add r3, r3, REGISTER_Y
    rlwinm r26, r4, 29, 27, 29
    slwi r4, r4, 8
    lwzx r8, r28, r26
    add r3, r3, r4
    mtctr r8
    mr r4, REGISTER_A
    bctr

// CLC  implied	CLC	18	1	2
// Clear Carry Flag
entry ksNesInst_clc_18
    li REGISTER_FLAG_CARRY, 0x0
    b ksNesLinecntIrqDefault

// SEC  implied	SEC	38	1	2
// Set Carry Flag
entry ksNesInst_sec_38
    li REGISTER_FLAG_CARRY, 0x1
    b ksNesLinecntIrqDefault

// DEX  implied	DEX	CA	1	2  
entry ksNesInst_dex_ca
    subi REGISTER_FLAG_ZERO, REGISTER_X, 0x1
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. REGISTER_X, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// INX  implied	INX	E8	1	2  
entry ksNesInst_inx_e8
    addi REGISTER_FLAG_ZERO, REGISTER_X, 0x1
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. REGISTER_X, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// DEY  implied	DEY	88	1	2  
entry ksNesInst_dey_88
    subi REGISTER_FLAG_ZERO, REGISTER_Y, 0x1
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. REGISTER_Y, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// INY  implied	INY	C8	1	2  
entry ksNesInst_iny_c8
    addi REGISTER_FLAG_ZERO, REGISTER_Y, 0x1
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. REGISTER_Y, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// TXA  implied	TXA	8A	1	2  
// Transfer Index X to Accumulator
entry ksNesInst_txa_8a
    mr REGISTER_FLAG_ZERO, REGISTER_X
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_X, 0x80
    mr REGISTER_A, REGISTER_X
    b ksNesLinecntIrqDefault

// TYA  implied	TYA	98	1	2  
// Transfer Index Y to Accumulator
entry ksNesInst_tya_98
    mr REGISTER_FLAG_ZERO, REGISTER_Y
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_Y, 0x80
    mr REGISTER_A, REGISTER_Y
    b ksNesLinecntIrqDefault

// TAX  implied	TAX	AA	1	2  
// Transfer Accumulator to Index X
entry ksNesInst_tax_aa
    mr REGISTER_FLAG_ZERO, REGISTER_A
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_A, 0x80
    mr REGISTER_X, REGISTER_A
    b ksNesLinecntIrqDefault

// TAY  implied	TAY	A8	1	2  
// Transfer Accumulator to Index Y
entry ksNesInst_tay_a8
    mr REGISTER_FLAG_ZERO, REGISTER_A
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_A, 0x80
    mr REGISTER_Y, REGISTER_A
    b ksNesLinecntIrqDefault

// CMP  (indirect,X)	CMP (oper,X)	C1	2	6  
// Compare Memory with Accumulator
entry ksNesInst_cmp_c1
    subf REGISTER_FLAG_ZERO, r4, REGISTER_A
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    srwi REGISTER_FLAG_CARRY, REGISTER_FLAG_ZERO, 31
    xori REGISTER_FLAG_CARRY, REGISTER_FLAG_CARRY, 0x1
    b ksNesLinecntIrqDefault

// CPX  immediate	CPX #oper	E0	2	2  
// Compare Memory with Index X
entry ksNesInst_cpx_e0
    subf REGISTER_FLAG_ZERO, r4, REGISTER_X
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    srwi REGISTER_FLAG_CARRY, REGISTER_FLAG_ZERO, 31
    xori REGISTER_FLAG_CARRY, REGISTER_FLAG_CARRY, 0x1
    b ksNesLinecntIrqDefault
// CPY  immediate	CPY #oper	C0	2	2  
// Compare Memory and Index Y
entry ksNesInst_cpy_c0
    subf REGISTER_FLAG_ZERO, r4, REGISTER_Y
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    srwi REGISTER_FLAG_CARRY, REGISTER_FLAG_ZERO, 31
    xori REGISTER_FLAG_CARRY, REGISTER_FLAG_CARRY, 0x1
    b ksNesLinecntIrqDefault

// ADC (indirect,X)	ADC (oper,X)	61	2	6  
// Add Memory to Accumulator with Carry
entry ksNesInst_adc_61
    extsb r7, REGISTER_A
    add REGISTER_FLAG_ZERO, REGISTER_A, REGISTER_FLAG_CARRY
    add r7, r7, REGISTER_FLAG_CARRY
    add REGISTER_FLAG_ZERO, REGISTER_FLAG_ZERO, r4
    extsb r8, r4
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    add r7, r7, r8
    andi. REGISTER_A, REGISTER_FLAG_ZERO, 0xff
    addi r7, r7, 0x80
    extrwi REGISTER_FLAG_CARRY, REGISTER_FLAG_ZERO, 1, 23 // (REGISTER_FLAG_ZERO >> 8) & 0x1
    srwi REGISTER_FLAG_OVERFLOW, r7, 8
    b ksNesLinecntIrqDefault

// SBC  (indirect,X)	SBC (oper,X)	E1	2	6  
// Subtract Memory from Accumulator with Borrow
entry ksNesInst_sbc_e1
    extsb r7, REGISTER_A
    xori REGISTER_FLAG_CARRY, REGISTER_FLAG_CARRY, 0x1
    subf REGISTER_FLAG_ZERO, r4, REGISTER_A
    subf r7, REGISTER_FLAG_CARRY, r7
    subf REGISTER_FLAG_ZERO, REGISTER_FLAG_CARRY, REGISTER_FLAG_ZERO
    extsb r8, r4
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    subf r7, r8, r7
    extrwi REGISTER_FLAG_CARRY, REGISTER_FLAG_ZERO, 1, 23 // (REGISTER_FLAG_ZERO >> 8) & 0x1
    addi r7, r7, 0x80
    andi. REGISTER_A, REGISTER_FLAG_ZERO, 0xff
    srwi REGISTER_FLAG_OVERFLOW, r7, 8
    xori REGISTER_FLAG_CARRY, REGISTER_FLAG_CARRY, 0x1
    b ksNesLinecntIrqDefault

// ora  (indirect,X)	ORA (oper,X)	01	2	6  
// OR Memory with Accumulator
entry ksNesInst_ora_01
    // bitwise or A with some value
    // using Z as temporary storage?
    or REGISTER_FLAG_ZERO, REGISTER_A, r4
    // set the N flag if A is negative
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    // assign the result to A
    andi. REGISTER_A, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// AND  (indirect,X)	AND (oper,X)	21	2	6  
// AND Memory with Accumulator
entry ksNesInst_and_21
    and REGISTER_FLAG_ZERO, REGISTER_A, r4
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. REGISTER_A, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// BIT  zeropage	BIT oper	24	2	3  
// Test Bits in Memory with Accumulator
// https://www.masswerk.at/6502/6502_instruction_set.html#bitcompare
entry ksNesInst_bit_24
    and REGISTER_FLAG_ZERO, REGISTER_A, r4
    andi. REGISTER_FLAG_NEGATIVE, r4, 0x80
    andi. REGISTER_FLAG_OVERFLOW, r4, 0x40
    b ksNesLinecntIrqDefault

// EOR  (indirect,X)	EOR (oper,X)	41	2	6  
// Exclusive-OR Memory with Accumulator
entry ksNesInst_eor_41
    xor REGISTER_FLAG_ZERO, REGISTER_A, r4
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. REGISTER_A, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// INC  zeropage	INC oper	E6	2	5  
// Increment Memory by One
entry ksNesInst_inc_e6
    lwzx r7, r28, r26
    addi REGISTER_FLAG_ZERO, r4, 0x1
    mtctr r7
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. r4, REGISTER_FLAG_ZERO, 0xff
    bctr

// DEC  zeropage	DEC oper	C6	2	5  
// Decrement Memory by One
entry ksNesInst_dec_c6
    lwzx r7, r28, r26
    subi REGISTER_FLAG_ZERO, r4, 0x1
    mtctr r7
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. r4, REGISTER_FLAG_ZERO, 0xff
    bctr

// ASL  accumulator	ASL A	0A	1	2  
// Shift Left One Bit (Memory or Accumulator)
entry ksNesInst_asl_0a
    slwi REGISTER_FLAG_ZERO, REGISTER_A, 1
    extrwi REGISTER_FLAG_CARRY, REGISTER_A, 1, 24 // (REGISTER_A >> 7) & 0x1
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. REGISTER_A, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// ASL  zeropage	ASL oper	06	2	5  
// Shift Left One Bit (Memory or Accumulator)
entry ksNesInst_asl_06
    lwzx r7, r28, r26
    slwi REGISTER_FLAG_ZERO, r4, 1
    mtctr r7
    extrwi REGISTER_FLAG_CARRY, r4, 1, 24 // (r4 >> 7) & 0x1
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO, 0x80
    andi. r4, REGISTER_FLAG_ZERO, 0xff
    bctr

// LSR  accumulator	LSR A	4A	1	2  
// Shift One Bit Right (Memory or Accumulator)
entry ksNesInst_lsr_4a
andi. REGISTER_FLAG_CARRY, REGISTER_A, 0x1
andi. REGISTER_FLAG_ZERO, REGISTER_A, 0xfe
li REGISTER_FLAG_NEGATIVE, 0x0
srwi REGISTER_A, REGISTER_A, 1
b ksNesLinecntIrqDefault

// LSR  zeropage	LSR oper	46	2	5  
// Shift One Bit Right (Memory or Accumulator)
entry ksNesInst_lsr_46
    lwzx r7, r28, r26
    li REGISTER_FLAG_NEGATIVE, 0x0
    mtctr r7
    andi. REGISTER_FLAG_CARRY, r4, 0x1
    andi. REGISTER_FLAG_ZERO, r4, 0xfe
    srwi r4, r4, 1
    bctr

// ROL  accumulator	ROL A	2A	1	2  
// Rotate One Bit Left (Memory or Accumulator)
entry ksNesInst_rol_2a
    slwi REGISTER_FLAG_ZERO, REGISTER_A, 1
    rlwinm REGISTER_FLAG_NEGATIVE, REGISTER_A, 1, 24, 24 // (REGISTER_A << 1) & 0x80
    or REGISTER_FLAG_ZERO, REGISTER_FLAG_ZERO, REGISTER_FLAG_CARRY
    extrwi REGISTER_FLAG_CARRY, REGISTER_A, 1, 24 // (REGISTER_A >> 7) & 0x1
    andi. REGISTER_A, REGISTER_FLAG_ZERO, 0xff
    b ksNesLinecntIrqDefault

// ROL  zeropage	ROL oper	26	2	5  
// Rotate One Bit Left (Memory or Accumulator)
entry ksNesInst_rol_26
    lwzx r7, r28, r26
    slwi REGISTER_FLAG_ZERO, r4, 1
    mtctr r7
    rlwinm REGISTER_FLAG_NEGATIVE, r4, 1, 24, 24 // (r4 << 1) & 0x80
    or REGISTER_FLAG_ZERO, REGISTER_FLAG_ZERO, REGISTER_FLAG_CARRY
    extrwi REGISTER_FLAG_CARRY, r4, 1, 24 // (r4 >> 7) & 0x1
    andi. r4, REGISTER_FLAG_ZERO, 0xff
    bctr

// ROR  accumulator	ROR A	6A	1	2  
// Rotate One Bit Right (Memory or Accumulator)
entry ksNesInst_ror_6a
    slwi REGISTER_FLAG_ZERO, REGISTER_FLAG_CARRY, 7
    andi. REGISTER_FLAG_CARRY, REGISTER_A, 0x1
    mr REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO
    
    rlwimi REGISTER_FLAG_ZERO, REGISTER_A, 31, 25, 31 
    // REGISTER_FLAG_ZERO = ((REGISTER_A>>1) & 0x7F) | (REGISTER_FLAG_ZERO & ~0x7F)
    
    mr REGISTER_A, REGISTER_FLAG_ZERO
    b ksNesLinecntIrqDefault

// ROR  zeropage	ROR oper	66	2	5  
// Rotate One Bit Right (Memory or Accumulator)
entry ksNesInst_ror_66
    lwzx r7, r28, r26
    slwi REGISTER_FLAG_ZERO, REGISTER_FLAG_CARRY, 7
    mtctr r7
    andi. REGISTER_FLAG_CARRY, r4, 0x1
    mr REGISTER_FLAG_NEGATIVE, REGISTER_FLAG_ZERO

    rlwimi REGISTER_FLAG_ZERO, r4, 31, 25, 31
    // REGISTER_FLAG_ZERO = ((r4>>1) & 0x7F) | (REGISTER_FLAG_ZERO & ~0x7F)

    mr r4, REGISTER_FLAG_ZERO
    bctr

// BPL  relative	BPL oper	10	2	2**
// Branch on Result Plus
entry ksNesInst_bpl_10
    extsb r8, r4
    andi. r7, REGISTER_FLAG_NEGATIVE, 0x80
    add REGISTER_PC, REGISTER_PC, r8
    beq ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi r25, r25, 0x100
    b ksNesLinecntIrqDefault

// BMI  relative	BMI oper	30	2	2**
// Branch on Result Minus
entry ksNesInst_bmi_30
    extsb r8, r4
    andi. r7, REGISTER_FLAG_NEGATIVE, 0x80
    add REGISTER_PC, REGISTER_PC, r8
    bne ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi r25, r25, 0x100
    b ksNesLinecntIrqDefault

// BVC  relative	BVC oper	50	2	2**
// Branch on Overflow Clear
entry ksNesInst_bvc_50
    extsb r8, r4
    cmpwi REGISTER_FLAG_OVERFLOW, 0x0
    add REGISTER_PC, REGISTER_PC, r8
    beq ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi r25, r25, 0x100
    b ksNesLinecntIrqDefault

// BVS  relative	BVS oper	70	2	2**
// Branch on Overflow Set
entry ksNesInst_bvs_70
    extsb r8, r4
    cmpwi REGISTER_FLAG_OVERFLOW, 0x0
    add REGISTER_PC, REGISTER_PC, r8
    bne ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi r25, r25, 0x100
    b ksNesLinecntIrqDefault
    
// BCC  relative	BCC oper	90	2	2**
// Branch on Carry Clear
entry ksNesInst_bcc_90
    extsb r8, r4
    andi. r7, REGISTER_FLAG_CARRY, 0x1
    add REGISTER_PC, REGISTER_PC, r8
    beq ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi r25, r25, 0x100
    b ksNesLinecntIrqDefault

// BCS  relative	BCS oper	B0	2	2**
// Branch on Carry Set
entry ksNesInst_bcs_b0
    extsb r8, r4
    andi. r7, REGISTER_FLAG_CARRY, 0x1
    add REGISTER_PC, REGISTER_PC, r8
    bne ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi r25, r25, 0x100
    b ksNesLinecntIrqDefault

// BNE  relative	BNE oper	D0	2	2**
// Branch on Result not Zero
entry ksNesInst_bne_d0
    extsb r8, r4
    andi. r7, REGISTER_FLAG_ZERO, 0xff
    add REGISTER_PC, REGISTER_PC, r8
    bne ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi r25, r25, 0x100
    b ksNesLinecntIrqDefault

// BEQ  relative	BEQ oper	D0	2	2**
// Branch on Result Zero
entry ksNesInst_beq_f0
    extsb r8, r4
    andi. r7, REGISTER_FLAG_ZERO, 0xff
    add REGISTER_PC, REGISTER_PC, r8
    beq ksNesLinecntIrqDefault
    subf REGISTER_PC, r8, REGISTER_PC
    subi r25, r25, 0x100
    b ksNesLinecntIrqDefault

// JSR absolute	JSR oper	20	3	6  
// Jump to New Location Saving Return Address
entry ksNesInst_jsr_20
    subi r4, REGISTER_PC, 0x1
    mr REGISTER_PC, r3
    // fallthrough

entry ksNesPush16_a1
    addi r0, WRAM, 0x100
    srwi r8, r4, 8
    stbx r8, REGISTER_STACK, r0
    subi r7, REGISTER_STACK, 0x1
    andi. r7, r7, 0xff
    subi REGISTER_STACK, REGISTER_STACK, 0x2
    stbx r4, r7, r0
    andi. REGISTER_STACK, REGISTER_STACK, 0xff
    blr

// PHA  implied	PHA	48	1	3  
// Push Accumulator on Stack
entry ksNesInst_pha_48
    addi r7, REGISTER_STACK, 0x100
    subi REGISTER_STACK, REGISTER_STACK, 0x1
    stbx REGISTER_A, WRAM, r7
    andi. REGISTER_STACK, REGISTER_STACK, 0xff
    b ksNesLinecntIrqDefault

// PLA  implied	PLA	68	1	4  
// Pull Accumulator from Stack
entry ksNesInst_pla_68
    addi REGISTER_STACK, REGISTER_STACK, 0x1
    addi r7, WRAM, 0x100
    andi. REGISTER_STACK, REGISTER_STACK, 0xff
    lbzx REGISTER_A, r7, REGISTER_STACK
    mr REGISTER_FLAG_ZERO, REGISTER_A
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_A, 0x80
    b ksNesLinecntIrqDefault
    
// RTS  implied	RTS	60	1	6  
// Return from Subroutine
entry ksNesInst_rts_60
    li r4, 0x1
    // fallthrough

entry ksNesPopPC
    addi r8, REGISTER_STACK, 0x1
    addi r7, REGISTER_STACK, 0x2
    ori r8, r8, 0x100
    ori r7, r7, 0x100
    lbzx r3, WRAM, r8
    andi. REGISTER_STACK, r7, 0xff
    lbzx r9, WRAM, r7
    add r3, r3, r4
    slwi r9, r9, 8
    add r3, r3, r9
    andi. REGISTER_PC, r3, 0xffff
    blr

// JMP  absolute	JMP oper	4C	3	3  
// Jump to New Location  
entry ksNesInst_jmp_4c
    mr REGISTER_PC, r3
    b ksNesLinecntIrqDefault

// JMP  indirect	JMP (oper)	6C	3	5  
// Jump to New Location
entry ksNesInst_jmp_6c
    lwzx r9, r27, r26
    subi r7, r3, 0x2000
    addi r4, r3, 0x1
    rlwinm r7, r7, 16, 16, 20
    andc r8, r3, r7
    lbzx REGISTER_PC, r9, r8
    rlwimi r3, r4, 0, 24, 31
    andc r3, r3, r7
    lbzx r4, r9, r3
    rlwimi REGISTER_PC, r4, 8, 16, 23
    b ksNesLinecntIrqDefault

// BRK  implied	BRK	00	1	7  
// Force Break
entry ksNesInst_brk_00
    li r9, 0x14
    lis r7, 0x0
    ori r7, r7, 0xfffe
    b L_8003BC60

entry ksNesActivateIntrIRQ
    lis r7, 0x0
    ori r7, r7, 0xfffe
    // fallthrough

entry ksNesActivateIntr
    li r9, 0x24
L_8003BC60:
    lwz r8, state_temp.cpu_e000_ffff
    mr r4, REGISTER_PC
    lbzux REGISTER_PC, r8, r7
    lbz r7, 0x1(r8)
    rlwimi REGISTER_PC, r7, 8, 16, 23
    bl ksNesPush16_a1
    addi r25, r25, 0x700
L_8003BC7C:
    lbz r7, state_temp._1846[8]
    cmpwi REGISTER_FLAG_OVERFLOW, 0x0
    rlwinm r8, r9, 31, 27, 27
    or r0, REGISTER_FLAG_NEGATIVE, r20
    andc r7, r7, r8
    beq L_8003BC98
    ori r0, r0, 0x40
L_8003BC98:
    andi. r9, r9, 0x14
    andi. r8, r19, 0xff
    or r0, r0, r7
    subi r8, r8, 0x1
    or r9, r9, r7
    addi r7, REGISTER_STACK, 0x100
    stb r9, state_temp._1846[8]
    rlwimi r0, r8, 2, 30, 30
    subi REGISTER_STACK, REGISTER_STACK, 0x1
    stbx r0, WRAM, r7
    andi. REGISTER_STACK, REGISTER_STACK, 0xff
    b ksNesLinecntIrqDefault


// PHP  implied	PHP	08	1	3  
// Push Processor Status on Stack
entry ksNesInst_php_08
    li r9, 0x0
    b L_8003BC7C

// PLP  implied	PLP	28	1	4  
// Pull Processor Status from Stack
entry ksNesInst_plp_28
    addi REGISTER_STACK, REGISTER_STACK, 0x1
    addi r7, WRAM, 0x100
    andi. REGISTER_STACK, REGISTER_STACK, 0xff
    lbzx r8, r7, REGISTER_STACK
    lbz r9, state_temp._1846[8]
    andi. r7, r8, 0x3c
    andi. REGISTER_FLAG_CARRY, r8, 0x1
    stb r7, state_temp._1846[8]
    andi. REGISTER_FLAG_ZERO, r8, 0x2
    andi. REGISTER_FLAG_OVERFLOW, r8, 0x40
    xori REGISTER_FLAG_ZERO, REGISTER_FLAG_ZERO, 0x2
    andi. REGISTER_FLAG_NEGATIVE, r8, 0x80
    andi. r7, r7, 0x4
    lbz r8, state_temp._1846[0x10]
    bnelr
    cmpwi r8, 0x0
    beqlr
    li r8, 0x0
    stb r8, state_temp._1846[0x10]
    bctr

// RTI  implied	RTI	40	1	6  
// Return from Interrupt
entry ksNesInst_rti_40
    bl ksNesInst_plp_28
    li r4, 0x0
    bl ksNesPopPC
    b ksNesLinecntIrqDefault

entry ksNesInst_rti_40_2
    li r4, 0x0
    bl ksNesPopPC
    b ksNesActivateIntrIRQ

// CLI  implied	CLI	58	1	2  
// Clear Interrupt Disable Bit
entry ksNesInst_cli_58
    lbz r7, state_temp._1846[8]
    andi. r7, r7, 0xfb
    stb r7, state_temp._1846[8]
    lbz r8, state_temp._1846[0x10]
    cmpwi r8, 0x0
    beq ksNesLinecntIrqDefault
    li r8, 0x0
    stb r8, state_temp._1846[0x10]
    b ksNesActivateIntrIRQ

// SEI  implied	SEI	78	1	2  
// Set Interrupt Disable Status
entry ksNesInst_sei_78
    lbz r7, state_temp._1846[8]
    ori r7, r7, 0x4
    stb r7, state_temp._1846[8]
    b ksNesLinecntIrqDefault

// TXS  implied	TXS	9A	1	2  
// Transfer Index X to Stack Register
entry ksNesInst_txs_9a
    mr REGISTER_STACK, REGISTER_X
    b ksNesLinecntIrqDefault

// TSX  implied	TSX	BA	1	2  
// Transfer Stack Pointer to Index X
entry ksNesInst_tsx_ba
    mr REGISTER_FLAG_ZERO, REGISTER_STACK
    andi. REGISTER_FLAG_NEGATIVE, REGISTER_STACK, 0x80
    mr REGISTER_X, REGISTER_STACK
    b ksNesLinecntIrqDefault

// CLD  Clear Decimal Mode
// Clear Decimal Mode
entry ksNesInst_cld_d8
    lbz r7, state_temp._1846[8]
    andi. r7, r7, ~0x8 & 0xff
    stb r7, state_temp._1846[8]
    b ksNesLinecntIrqDefault

// SED  implied	SED	F8	1	2  
// Set Decimal Flag
entry ksNesInst_sed_f8
    lbz r7, state_temp._1846[8]
    ori r7, r7, 0x8
    stb r7, state_temp._1846[8]
    b ksNesLinecntIrqDefault

// CLV implied	CLV	B8	1	2  
// Clear Overflow Flag
entry ksNesInst_clv_b8
    li REGISTER_FLAG_OVERFLOW, 0x0
    b ksNesLinecntIrqDefault

entry ksNesLoadInvalid
    bctr
entry ksNesLoadIgnore
    srwi r4, r3, 8
    bctr
// < r3 = address to load from
entry ksNesLoadWRAM
    // we're loading from wram so we'll limit the address to valid wram addresses
    andi.      r7,r3,0x7ff

    // r4 = state_temp->wram[r7]
    // read a byte from work ram
    // the state object starts with a work ram array.
    lbzx       r4,WRAM,r7
    bctr

entry ksNesLoadBBRAM
    // r7 = r27[r26]
    lwzx       r7,r27,r26
    // r4 = r7[r3]
    lbzx       r4,r7,r3
    bctr

entry ksNesLoadPPU
    andi.      r7,r3,0x7
    addi       r8, state_temp, ksNesStateObj._16A0
    cmpwi      r7,0x7
    lbzx       r4,r8,r7
    bne        LAB_8003be58
    lhz        r7,state_temp._1832
    cmpwi      r7,0x3000
    bge        LAB_8003be14
    cmpwi      r7,0x2000
    blt        LAB_8003be30
    rlwinm     r9,r7,0x18,0x1c,0x1d // r9 = (r7 >> 8) & 0xC;
    addi       r0, state_temp, ksNesStateObj._1810
    lwzx       r9,r9,r0
    andi.      r8,r7,0x3ff
    lbzx       r9,r9,r8
    stb        r9, state_temp._16A0[7]
LAB_8003be14:
    lbz        r8, state_temp._16A0[8]
    li         r0,0x3
    andi.      r8,r8,0x4
    rlwnm      r8,r0,r8,0x1f,0x1a // r8 = (r0 << r8) & 0x8000003F
    add        r7,r7,r8
    sth        r7,state_temp._1832
    bctr
LAB_8003be30:
    rlwinm     r8, r7, 0x16, 0x1d, 0x1f
    addi       r9, state_temp, ksNesStateObj._17FC
    lbzx       r9, r9, r8
    andi.      r0, r7, 0x3ff
    lwz        r8, state_temp.chrramp
    rlwinm     r9, r9, 0xa, 0x0, 0x15 // r9=r9*1024
    add        r8, r8, r0
    lbzx       r9, r8, r9
    stb        r9, state_temp._16A0[7]
    b          LAB_8003be14
LAB_8003be58:
    li         r9,0x20
    stbx       r9,r8,r7
    bctr

entry ksNesLoadIO
    addi r8, r29, 0x20
    clrlslwi r7, r3, 26, 2
    lwzx r0, r8, r7
    cmpwi r3, 0x4018
    mtlr r0
    bltlr
    cmpwi r3, 0x4034
    bge L_8003BF0C
    subic. r7, r3, 0x4030
    addi r8, state_temp, ksNesStateObj._16B0
    blt ksNesLoadInvalid
    lbzx r4, r8, r7
    bne L_8003BEA4
    li r7, 0x0
    stb r7, state_temp._16B0
    bctr
L_8003BEA4:
    cmpwi r3, 0x4031
    beq L_8003BEFC
    cmpwi r3, 0x4032
    bnectr
    lbz r7, 0x176b(r31)
    and r4, r4, r7
    cmplwi r17, 0xe000
    blt L_8003BEDC
    cmplwi r17, 0xeee2
    beqctr
    cmplwi r17, 0xef36
    beqctr
    li r4, 0x40
    bctr
L_8003BEDC:
    lbz r7, 0x176c(r31)
    ori r4, r4, 0x47
    cmpwi r7, 0xc3
    bgectr
    lbz r7, 0x16c9(r31)
    andi. r4, r4, 0xfa
    rlwimi r4, r7, 0, 30, 30
    bctr
L_8003BEFC:
    lhz r9, 0x16c2(r31)
    addi r9, r9, 0x1
    sth r9, 0x16c2(r31)
    bctr
L_8003BF0C:
    mfctr r0
    stw r0, 0xd0(r1)
    bl Sound_Read
    lwz r0, 0xd0(r1)
    mr r4, r3
    mtctr r0
    bctr

entry ksNesLoad4015
	lbz r4, state_temp._1846[0xc]
	andi. r7, r4, 0x3f
	stb r7, 0x1852(r31)
	bctr
    
entry ksNesLoad4017
    lwz r0, state_temp._186C[0x1E]
    li r4, 0x40
    lwz r10, state_temp._186C[0x1D]
    lwz r9, state_temp._186C[0x1C]
    rlwimi r4, r0, 5, 27, 27
    lwz r8, state_temp._186C[0x1B]
    rlwimi r4, r10, 4, 28, 28
    lwz r7, state_temp._186C[0x1A]
    rlwimi r4, r9, 3, 29, 29
    lbz r5, state_temp._1846[0xE]
    rlwimi r4, r8, 2, 30, 30
    rlwimi r4, r7, 1, 31, 31
    andi. r5, r5, 0x1
    bnectr
    slwi r0, r0, 1
    slwi r10, r10, 1
    stw r0, state_temp._186C[0x1E]
    slwi r9, r9, 1
    stw r10, state_temp._186C[0x1D]
    slwi r8, r8, 1
    stw r9, state_temp._186C[0x1C]
    slwi r7, r7, 1
    stw r8, state_temp._186C[0x1B]
    stw r7, state_temp._186C[0x1A]
    bctr

entry ksNesLoad4016
    lbz r7, state_temp._1846[0xE]
    li r4, 0x40
    lwz r8, state_temp._186C[0x19]
    andi. r7, r7, 0x1
    lwz r9, state_temp._186C[0x18]
    rlwimi r4, r8, 2, 30, 30
    rlwimi r4, r9, 1, 31, 31
    bnectr
    slwi r8, r8, 1
    slwi r9, r9, 1
    stw r8, state_temp._186C[0x19]
    stw r9, state_temp._186C[0x18]
    bctr

entry ksNesStoreWRAM
    andi. r7, r3, 0x7ff
    stbx r4, WRAM, r7
    b ksNesLinecntIrqDefault

entry ksNesStoreBBRAM
    lwzx       r7,r27,r26
    stbx       r4,r7,r3
    b          ksNesLinecntIrqDefault

entry ksNesStoreInvalid
    b ksNesLinecntIrqDefault

entry ksNesStorePPU
    clrlslwi r7, r3, 29, 2
    subi r8, r28, 0xc0
    lwzx r7, r8, r7
    mtctr r7
    bctr

entry ksNesStore2000
    lbz r9, state_temp._1830
    andi. r8, r4, 0x3
    lbz r7, state_temp._16A8[0]
    stb r4, state_temp._16A8[0]
    rlwimi r9, r4, 0, 31, 31
    stb r8, state_temp._1834
    stb r9, state_temp._1830
    b ksNesLinecntIrqDefault

entry ksNesStorePPURam
    andi. r7, r3, 0x7
    addi r8, state_temp, state_temp._16A8
    stbx r4, r8, r7
    b ksNesLinecntIrqDefault

entry ksNesStore2004
    b ksNesLinecntIrqDefault

entry ksNesStore2005
    lbz r7, state_temp._16A0[2]
    andi. r9, r7, 0x1
    xori r7, r7, 0x1
    stb r7, state_temp._16A0[2]
    bne L_8003C050
    stb r4, state_temp._182F
    b ksNesLinecntIrqDefault
L_8003C050:
    lbz r8, state_temp._182E
    stb r4, state_temp._1835
    cmpwi r8, 0x0
    beq ksNesLinecntIrqDefault
    lha r9, state_temp._1820
    cmpw r9, r8
    bge ksNesLinecntIrqDefault
    stb r4, state_temp._1831
    cmpwi r9, 0x8
    blt ksNesLinecntIrqDefault
    add r4, r4, r9
L_8003C07C:
    cmpwi r4, 0xf0
    blt L_8003C08C
    subi r4, r4, 0xf0
    b L_8003C07C
L_8003C08C:
    stb r4, state_temp._1831
    b ksNesLinecntIrqDefault

entry ksNesStore2006
    lbz r7, state_temp._16A0[2]
    addi r8, state_temp, state_temp._1832 // used to store u8 into a u16?
    andi. r9, r7, 0x1
    xori r7, r7, 0x1
    stbx r4, r8, r9 // stores to index 0 or 1, essentially writing to the u16 here
    stb r7, state_temp._16A0[2]
    beq ksNesLinecntIrqDefault
    lhz r8, state_temp._1832
    andi. r8, r8, 0x3fff
    sth r8, state_temp._1832
    rlwinm r7, r8, 30, 22, 28
    rlwimi r7, r8, 20, 30, 31
    lbz r9, state_temp.mapper
    cmpwi r9, 0x5
    bne L_8003C0D4
    andi. r7, r7, 0x7ffe
L_8003C0D4:
    sth r7, state_temp._1834
    sth r7, state_temp._1830
    b ksNesLinecntIrqDefault

entry ksNesStore2007ChrRom
    lhz r7, state_temp._1832
    cmpwi r7, 0x3000
    bge L_8003C18C
    cmpwi r7, 0x2000
    blt L_8003C130
    rlwinm r9, r7, 24, 28, 29 // (r7 >> 8) & 0xC // ((r7 >> 10) & 0x2) << 2
    addi r0, state_temp, state_temp._1810
    lwzx r9, r9, r0
    andi. r8, r7, 0x3ff
    addi r10, state_temp, state_temp._1000
    cmpw r10, r9
    beq L_8003C114
    stbx r4, r9, r8
L_8003C114:
    lbz r8, 0x16a8(r31)
    li r0, 0x3
    andi. r8, r8, 0x4
    rlwnm r8, r0, r8, 31, 26
    add r7, r7, r8
    sth r7, 0x1832(r31)
    b ksNesLinecntIrqDefault
L_8003C130:
    lbz r10, 0x1769(r31)
    extrwi r8, r7, 3, 19
    addi r9, r31, 0x17fc
    andi. r0, r7, 0x3ff
    cmpwi r10, 0x0
    lbzx r9, r9, r8
    beq ksNesLinecntIrqDefault
    lwz r8, 0x17f4(r31)
    slwi r9, r9, 10
    add r9, r9, r0
    stbx r4, r8, r9
    lwz r3, 0x8(r1)
    srwi r5, r9, 4
    lbz r7, 0x1764(r31)
    clrrwi r9, r9, 4
    add r4, r8, r9
    cmpwi r7, 0x5
    beq L_8003C180
    bl ksNesConvertChrToI8
    b L_8003C184
L_8003C180:
    bl ksNesConvertChrToI8MMC5
L_8003C184:
    lhz r7, 0x1832(r31)
    b L_8003C114
L_8003C18C:
    cmpwi r7, 0x3f00
    blt L_8003C114
    cmpwi r7, 0x3f20
    bge L_8003C114
    lbz r10, 0x17c6(r31)
    andi. r8, r7, 0x1f
    andi. r0, r4, 0x3f
    andi. r9, r7, 0xf
    addi r10, r10, 0x16cc
    add r10, r10, r31
    beq L_8003C1CC
    andi. r9, r7, 0x3
    beq L_8003C114
    stbx r0, r10, r8
    sth r7, 0x17c4(r31)
    b L_8003C114
L_8003C1CC:
    stb r0, 0x0(r10)
    stb r0, 0x4(r10)
    stb r0, 0x8(r10)
    stb r0, 0xc(r10)
    stb r0, 0x10(r10)
    stb r0, 0x14(r10)
    stb r0, 0x18(r10)
    stb r0, 0x1c(r10)
    sth r7, 0x17c4(r31)
    b L_8003C114

entry ksNesStoreIO
    subi r8, r28, 0xa0
    clrlslwi r7, r3, 26, 2
    lwzx r0, r8, r7
    cmpwi r3, 0x4027
    mtctr r0
    bge ksNesStoreQDSound
    bctr

entry ksNesStoreQDSound
    b ksNesStore4000

entry ksNesStore4017
    andi. r8, r4, 0xc0
    bne L_8003C234
    lhz r7, 0x1820(r31)
    li r9, 0x1
    stb r8, 0x1855(r31)
    sth r7, 0x1828(r31)
    stb r9, 0x1857(r31)
    b ksNesStore4000
L_8003C234:
    lbz r9, 0x1855(r31)
    andi. r9, r9, 0xc0
    stb r8, 0x1855(r31)
    bne ksNesStore4000
    stb r9, 0x1857(r31)
    b ksNesStore4000

entry ksNesStore4011
    lbz r8, 0x1851(r31)
    cmpw r8, r4
    beq ksNesLinecntIrqDefault
    stb r4, 0x1851(r31)
    b ksNesStore4000

entry ksNesStore4015
	lbz r9, 0x1852(r31)
	andi. r8, r4, 0x10
	or r9, r9, r8
	stb r9, 0x1852(r31)
	b ksNesStore4003

entry ksNesStore4003
    lbz r9, 0x1852(r31)
    srwi r7, r3, 30
    li r8, 0x1
    slw r8, r8, r7
    or r9, r9, r8
    stb r9, 0x1852(r31)
    // fallthrough

entry ksNesStore4000
    lwz r8, 0x185c(r31)
    lwz r5, 0xf0(r1)
    lbz r7, 0xec(r1)
    andi. r8, r8, 0x1000
    bne ksNesLinecntIrqDefault
    divwu r5, r5, r7
    bl Sound_Write
    b ksNesLinecntIrqDefault

entry ksNesStore4014
    rlwinm r7, r4, 29, 27, 29
    slwi r8, r4, 8
    lwzx r7, r27, r7
    li r0, 0x40
    addi r9, r31, 0x101c
    mtctr r0
    add r7, r7, r8
    subi r7, r7, 0x4
L_8003C2CC:
    lwzu r0, 0x4(r7)
    stwu r0, 0x4(r9)
    bdnz L_8003C2CC
    addis r25, r25, 0x2
    b ksNesLinecntIrqDefault

entry ksNesStore4016
    andi. r7, r4, 0x1
    stb r4, 0x1854(r31)
    beq ksNesLinecntIrqDefault
    lwz r9, 0x8(r1)
    lwz r7, 0x20(r9)
    lwz r8, 0x24(r9)
    stw r7, 0x18cc(r31)
    stw r8, 0x18d0(r31)
    lwz r7, 0x28(r9)
    lwz r8, 0x2c(r9)
    stw r7, 0x18d4(r31)
    stw r8, 0x18d8(r31)
    lwz r7, 0x30(r9)
    lwz r8, 0x34(r9)
    lwz r0, 0x38(r9)
    stw r7, 0x18dc(r31)
    stw r8, 0x18e0(r31)
    stw r0, 0x18e4(r31)
    b ksNesLinecntIrqDefault

entry ksNesInst_wdm_42
    lwz r7, 0x17f0(r31)
    cmpwi r7, 0x0
    bne ksNesLinecntIrqDefault
    cmplwi r17, 0xe408
    beq L_8003C4D8
    cmplwi r17, 0xeebf
    beq L_8003C464
    cmplwi r17, 0xeef6
    beq L_8003C440
    cmplwi r17, 0xe23b
    beq L_8003C36C
    cmplwi r17, 0xe7a6
    bne ksNesLinecntIrqDefault
    andi. r25, r25, 0x7
    subi r17, r17, 0x2
    b ksNesLinecntIrqDefault
L_8003C36C:
    stb r14, 0xe(r31)
    cmpwi r14, 0xff
    beq ksNesLinecntIrqDefault
    add r7, r31, r18
    lbzu r9, 0x101(r7)
    lbz r8, 0x1(r7)
    rlwimi r9, r8, 8, 16, 23
    addi r5, r9, 0x1
    addi r6, r9, 0x5
    sth r6, 0x16b8(r31)
    rlwinm r26, r5, 21, 27, 29
    lwzx r7, r27, r26
    lbzx r7, r7, r5
    addi r5, r5, 0x1
    rlwinm r26, r5, 21, 27, 29
    lwzx r8, r27, r26
    lbzx r8, r8, r5
    addi r5, r5, 0x1
    rlwimi r7, r8, 8, 16, 23
    addi r3, r31, 0x176d
    addi r4, r31, 0x1777
L_8003C3C0:
    rlwinm r26, r7, 21, 27, 29
    lwzx r8, r27, r26
    lbzx r8, r8, r7
    addi r7, r7, 0x1
    stbu r8, 0x1(r3)
    cmpw r3, r4
    bne L_8003C3C0
    rlwinm r26, r5, 21, 27, 29
    lwzx r7, r27, r26
    lbzx r7, r7, r5
    addi r5, r5, 0x1
    rlwinm r26, r5, 21, 27, 29
    lwzx r8, r27, r26
    lbzx r8, r8, r5
    rlwimi r7, r8, 8, 16, 23
    addi r3, r4, 0x11
L_8003C400:
    rlwinm r26, r7, 21, 27, 29
    lwzx r8, r27, r26
    lbzx r8, r8, r7
    addi r7, r7, 0x1
    stbu r8, 0x1(r4)
    cmpw r4, r3
    bne L_8003C400
    lwz r3, 0x8(r1)
    lwz r4, 0xc(r1)
    bl ksNesQDFastSave
    andi. r19, r3, 0xff
    andi. r14, r3, 0xff
    bne ksNesLinecntIrqDefault
    bl ksNesInst_rts_60
    lhz r17, 0x16b8(r31)
    b ksNesLinecntIrqDefault
L_8003C440:
    lwz r9, 0x8(r1)
    lwz r8, 0x20(r9)
    srwi r7, r8, 28
    cmpwi r7, 0x6
    beq L_8003C45C
    li r8, 0x46
    stb r8, 0x176b(r31)
L_8003C45C:
    lbz r14, 0x90(r31)
    b ksNesLinecntIrqDefault
L_8003C464:
    andi. r7, r14, 0xf0
    cmpwi r7, 0x60
    beq ksNesLinecntIrqDefault
    subi r7, r26, 0x2
    li r8, 0xa9
    stbx r8, r7, r17
    lwz r3, 0x8(r1)
    lwz r4, 0xc(r1)
    bl ksNesQDFastLoad
    andi. r19, r3, 0xff
    bne ksNesLinecntIrqDefault
    subi r7, r31, 0x1
    li r8, 0x46
    stb r8, 0x16b2(r31)
    stb r8, 0x176b(r31)
    li r8, 0x0
    addi r0, r7, 0xfa
L_8003C4A8:
    stbu r8, 0x1(r7)
    cmpw r7, r0
    bne L_8003C4A8
    addi r0, r7, 0x104
    lis r9, ksNesInitQDDataTbl@h
    ori r9, r9, ksNesInitQDDataTbl@l
L_8003C4C0:
    lbzu r8, 0x1(r9)
    stbu r8, 0x1(r7)
    cmpw r7, r0
    bne L_8003C4C0
    subi r17, r17, 0x24
    b ksNesLinecntIrqDefault
L_8003C4D8:
    lbz r7, 0x0(r31)
    stb r14, 0x1(r31)
    rlwinm r26, r14, 29, 27, 29
    rlwimi r7, r14, 8, 16, 23
    lwzx r8, r27, r26
    add r7, r7, r8
    addi r7, r7, 0x1
    lswi r8, r7, 8
    cmpwi r8, -0x1
    beq ksNesLinecntIrqDefault
    lwz r5, 0x1868(r31)
    lbz r7, 0x176a(r31)
    addi r10, r5, 0x10
L_8003C50C:
    lswi r3, r10, 8
    cmpw r3, r8
    bne L_8003C520
    cmpw r4, r9
    beq L_8003C530
L_8003C520:
    addis r10, r10, 0x1
    subic. r7, r7, 0x1
    bgt L_8003C50C
    b ksNesLinecntIrqDefault
L_8003C530:
    subi r10, r10, 0x10
    subf r10, r5, r10
    stw r10, 0x16c0(r31)
    b ksNesLinecntIrqDefault

entry ksNesLinecntIrqQD
    lbz r0, 0x16c9(r31)
    andi. r8, r0, 0x80
    beq L_8003C588
    andi. r9, r0, 0xe3
    cmpwi r9, 0xe1
    bne ksNesMainLoop2
    addi r10, r10, 0x1
    cmpwi r10, 0xee
    ble L_8003C568
    li r10, -0x14
L_8003C568:
    sth r10, 0x1828(r31)
    lwz r8, 0x1868(r31)
    lwz r9, 0x16c0(r31)
    andi. r10, r0, 0x4
    beq SUB_8003b3a0
    lbzx r10, r8, r9
    stb r10, 0x16b1(r31)
    b SUB_8003b3a0
L_8003C588:
    lbz r8, 0x16c6(r31)
    andi. r0, r8, 0xfd
    li r9, 0x7fff
    andi. r8, r8, 0x1
    beq L_8003C5A8
    mr r0, r8
    lhz r9, 0x183c(r31)
    add r9, r9, r10
L_8003C5A8:
    sth r9, 0x1828(r31)
    stb r0, 0x16c6(r31)
    andi. r0, r0, 0x2
    stb r0, 0x1857(r31)
    li r9, 0x1
    stb r9, 0x16b0(r31)
    cmpwi r7, 0x0
    bne SUB_8003b3a0
    b ksNesMainLoop2

entry ksNesStoreQD_4020
    subi r7, r31, 0x2855
    stbx r4, r7, r3
    b ksNesLinecntIrqDefault

entry ksNesStoreQD_4022
    stb r4, 0x16c6(r31)
    andi. r8, r4, 0x2
    stb r8, 0x1857(r31)
    lbz r8, 0x17cc(r31)
    lbz r7, 0x17cb(r31)
    li r0, 0x72
    lha r9, 0x1820(r31)
    rlwimi r7, r8, 8, 16, 23
    divwu r8, r7, r0
    sth r8, 0x183c(r31)
    add r9, r9, r8
    sth r9, 0x1828(r31)
    b ksNesLinecntIrqDefault

entry ksNesStoreQD_4023
    stb r4, 0x16c7(r31)
    b ksNesStore4000

entry ksNesStoreQD_4024
    lbz r7, 0x16c9(r31)
    lwz r8, 0x1868(r31)
    lwz r9, 0x16c0(r31)
    andi. r7, r7, 0x87
    cmpwi r7, 0x81
    bne ksNesLinecntIrqDefault
    add r8, r8, r9
    stb r4, -0x2(r8)
    li r7, 0x1
    stb r7, 0x16bd(r31)
    b ksNesLinecntIrqDefault

entry ksNesStoreQD_4025
    lbz r7, 0x16c9(r31)
    xor r8, r7, r4
    andi. r8, r8, 0x2
    stb r4, 0x16c9(r31)
    beq L_8003C65C
    bl ksNesQDSoundSync
    lbz r4, 0x16c9(r31)
L_8003C65C:
    andi. r7, r4, 0x80
    beq L_8003C684
    stb r7, 0x1857(r31)
    lha r8, 0x1820(r31)
    addi r8, r8, 0x1
    cmpwi r8, 0xee
    ble L_8003C67C
    li r8, -0x14
L_8003C67C:
    sth r8, 0x1828(r31)
    b L_8003C69C
L_8003C684:
    lbz r7, 0x16c6(r31)
    andi. r7, r7, 0x2
    stb r7, 0x1857(r31)
    bne L_8003C69C
    li r7, 0x7fff
    sth r7, 0x1828(r31)
L_8003C69C:
    andi. r7, r4, 0x3
    cmpwi r7, 0x2
    bne L_8003C6BC
    lbz r8, 0x16b2(r31)
    li r7, 0x0
    andi. r8, r8, 0xfd
    stb r8, 0x16b2(r31)
    sth r7, 0x16c2(r31)
L_8003C6BC:
    rlwinm r7, r4, 1, 27, 27
    addi r0, r31, 0x1888
    addi r9, r31, 0x180c
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003C6D0:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003C6D0
    b ksNesLinecntIrqDefault

entry ksNesStoreQD_4026
    stb r4, 0x16b3(r31)
    b ksNesLinecntIrqDefault

entry ksNesStore01_8000
    lbz r9, 0x178f(r31)
    andi. r7, r4, 0x80
    bne L_8003C718
    lbz r8, 0x178e(r31)
    srwi r7, r9, 1
    subic. r8, r8, 0x1
    rlwimi r7, r4, 4, 27, 27
    beq L_8003C724
    stb r8, 0x178e(r31)
    stb r7, 0x178f(r31)
    b ksNesLinecntIrqDefault
L_8003C718:
    lbz r7, 0x1789(r31)
    li r3, 0x0
    ori r7, r7, 0xc
L_8003C724:
    li r8, 0x5
    addi r0, r31, 0x1789
    stb r8, 0x178e(r31)
    extrwi r9, r3, 2, 17
    lbzx r8, r9, r0
    cmpw r8, r7
    beq ksNesLinecntIrqDefault
    stbx r7, r9, r0
    lbz r7, 0x1789(r31)
    lbz r10, 0x178c(r31)
    lbz r8, 0x1765(r31)
    rlwinm r0, r7, 30, 30, 30
    slwi r10, r10, 1
    ori r0, r0, 0x1c
    and r10, r10, r8
    lwz r9, 0x17f0(r31)
    and r10, r10, r0
    subi r10, r10, 0x4
    slwi r10, r10, 13
    add r10, r10, r9
    andi. r0, r7, 0x8
    bne L_8003C790
    stw r10, 0x1690(r31)
    stw r10, 0x1694(r31)
    stw r10, 0x1698(r31)
    stw r10, 0x169c(r31)
    b L_8003C7FC
L_8003C790:
    andi. r0, r7, 0x4
    bne L_8003C7B4
    subi r10, r10, 0x4000
    stw r10, 0x1698(r31)
    stw r10, 0x169c(r31)
    addi r0, r9, -0x8000
    stw r0, 0x1690(r31)
    stw r0, 0x1694(r31)
    b L_8003C7FC
L_8003C7B4:
    lbz r8, 0x178d(r31)
    cmpwi r8, 0x0
    beq L_8003C7D0
    lbz r0, 0x178a(r31)
    andi. r0, r0, 0x10
    slwi r0, r0, 14
    add r10, r10, r0
L_8003C7D0:
    stw r10, 0x1690(r31)
    stw r10, 0x1694(r31)
    cmpwi r8, 0x0
    beq L_8003C7E8
    xoris r0, r0, 0x4
    subf r9, r0, r9
L_8003C7E8:
    lwz r0, 0x1860(r31)
    subis r10, r9, 0x1
    add r10, r10, r0
    stw r10, 0x1698(r31)
    stw r10, 0x169c(r31)
L_8003C7FC:
    andi. r0, r7, 0x10
    lbz r8, 0x178a(r31)
    lhz r9, 0x1766(r31)
    bne L_8003C834
    rlwinm r8, r8, 2, 25, 28
    and r8, r8, r9
    addi r9, r31, 0x17fc
    addi r0, r31, 0x1804
L_8003C81C:
    stb r8, 0x0(r9)
    addi r9, r9, 0x1
    addi r8, r8, 0x1
    cmpw r9, r0
    bne L_8003C81C
    b L_8003C86C
L_8003C834:
    lbz r0, 0x178b(r31)
    clrlslwi r8, r8, 27, 2
    and r8, r8, r9
    clrlslwi r0, r0, 27, 2
    and r9, r0, r9
    addi r10, r31, 0x17fc
    addi r0, r31, 0x1800
L_8003C850:
    stb r8, 0x0(r10)
    addi r8, r8, 0x1
    stb r9, 0x4(r10)
    addi r10, r10, 0x1
    cmpw r10, r0
    addi r9, r9, 0x1
    bne L_8003C850
L_8003C86C:
    clrlslwi r7, r7, 30, 4
    addi r0, r31, 0x1868
    addi r9, r31, 0x180c
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003C880:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003C880
    b ksNesLinecntIrqDefault

entry ksNesStore02_8000
    lbz r7, 0x1765(r31)
    slwi r8, r4, 1
    lwz r9, 0x17f0(r31)
    and r8, r8, r7
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r9
    stw r8, 0x1690(r31)
    stw r8, 0x1694(r31)
    b ksNesLinecntIrqDefault

entry ksNesStore03_6000
    lhz r0, 0x1766(r31)
    clrlslwi r7, r4, 30, 3
    addi r9, r31, 0x17fc
    li r8, 0x0
    and r7, r7, r0
L_8003C8D0:
    stbx r7, r9, r8
    addi r8, r8, 0x1
    addi r7, r7, 0x1
    cmpwi r8, 0x8
    blt L_8003C8D0
    b ksNesLinecntIrqDefault

entry ksNesLinecntIrq04
    cmpwi r10, 0x0
    blt L_8003C924
    cmpwi r10, 0xef
    bgt L_8003C924
    lha r9, 0x183c(r31)
    lbz r8, 0x16a9(r31)
    addi r9, r9, 0x1
    add r9, r9, r10
    sth r9, 0x1828(r31)
    cmpwi r7, 0x0
    beq ksNesMainLoop2
    andi. r8, r8, 0x18
    beq L_8003C924
    rlwinm r25, r25, 0, 28, 20
    b SUB_8003b3a0
L_8003C924:
    li r8, 0x7fff
    sth r8, 0x1828(r31)
    b ksNesMainLoop2

entry ksNesStore04_8000
    lbz r0, 0x182d(r31)
    andi. r8, r3, 0x1
    bne L_8003CA34
    stb r4, 0x182d(r31)
    xor r7, r0, r4
    andi. r8, r7, 0x80
    beq L_8003C9C8
    andi. r8, r4, 0x80
    bne L_8003C990
    lbz r8, 0x1790(r31)
    lbz r9, 0x1791(r31)
    andi. r8, r8, 0xfffe
    andi. r9, r9, 0xfffe
    stb r8, 0x17fc(r31)
    stb r9, 0x17fe(r31)
    ori r8, r8, 0x1
    ori r9, r9, 0x1
    stb r8, 0x17fd(r31)
    stb r9, 0x17ff(r31)
    addi r8, r31, 0x1792
    lswi r9, r8, 4
    addi r8, r31, 0x1800
    stswi r9, r8, 4
    b L_8003C9C8
L_8003C990:
    addi r8, r31, 0x1792
    lswi r9, r8, 4
    addi r8, r31, 0x17fc
    stswi r9, r8, 4
    lbz r8, 0x1790(r31)
    lbz r9, 0x1791(r31)
    andi. r8, r8, 0xfffe
    andi. r9, r9, 0xfffe
    stb r8, 0x1800(r31)
    stb r9, 0x1802(r31)
    ori r8, r8, 0x1
    ori r9, r9, 0x1
    stb r8, 0x1801(r31)
    stb r9, 0x1803(r31)
L_8003C9C8:
    andi. r8, r7, 0x40
    beq ksNesLinecntIrqDefault
    lbz r8, 0x1796(r31)
    andi. r9, r4, 0x40
    lbz r0, 0x1765(r31)
    lwz r10, 0x17f0(r31)
    lwz r5, 0x1860(r31)
    and r8, r8, r0
    bne L_8003CA0C
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r10
    stw r8, 0x1690(r31)
    add r10, r10, r5
    subis r10, r10, 0x1
    stw r10, 0x1698(r31)
    b ksNesLinecntIrqDefault
L_8003CA0C:
    subi r8, r8, 0x6
    slwi r8, r8, 13
    add r8, r8, r10
    stw r8, 0x1698(r31)
    add r10, r10, r5
    lis r7, 0x0
    ori r7, r7, 0xc000
    subf r10, r7, r10
    stw r10, 0x1690(r31)
    b ksNesLinecntIrqDefault
L_8003CA34:
    andi. r7, r0, 0x7
    add r8, r7, r31
    lbz r9, 0x1790(r8)
    cmpw r9, r4
    beq ksNesLinecntIrqDefault
    lbz r9, 0x1765(r31)
    subic. r10, r7, 0x6
    bge L_8003CA9C
    lhz r9, 0x1766(r31)
    subic. r10, r7, 0x2
    addi r5, r31, 0x17fc
    xor r0, r0, r10
    and r9, r9, r4
    rlwinm r0, r0, 27, 29, 29
    stb r9, 0x1790(r8)
    xori r0, r0, 0x4
    add r10, r10, r0
    bge L_8003CA94
    clrlslwi r10, r7, 31, 1
    andi. r9, r9, 0xfffe
    add r10, r10, r0
    stbx r9, r5, r10
    ori r9, r9, 0x1
    addi r10, r10, 0x1
L_8003CA94:
    stbx r9, r5, r10
    b ksNesLinecntIrqDefault
L_8003CA9C:
    lwz r7, 0x17f0(r31)
    and r9, r9, r4
    stb r9, 0x1790(r8)
    bne L_8003CADC
    andi. r0, r0, 0x40
    beq L_8003CAC8
    subi r9, r9, 0x6
    slwi r9, r9, 13
    add r9, r9, r7
    stw r9, 0x1698(r31)
    b ksNesLinecntIrqDefault
L_8003CAC8:
    subi r9, r9, 0x4
    slwi r9, r9, 13
    add r9, r9, r7
    stw r9, 0x1690(r31)
    b ksNesLinecntIrqDefault
L_8003CADC:
    subi r9, r9, 0x5
    slwi r9, r9, 13
    add r9, r9, r7
    stw r9, 0x1694(r31)
    b ksNesLinecntIrqDefault
    
entry ksNesStore04_a000
    andi. r7, r3, 0x1
    bne ksNesLinecntIrqDefault
    clrlslwi r7, r4, 31, 4
    addi r0, r31, 0x1888
    addi r9, r31, 0x180c
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003CB0C:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003CB0C
    b ksNesLinecntIrqDefault

entry ksNesStore04_c000
    lha r8, 0x1820(r31)
    andi. r7, r3, 0x1
    bne L_8003CB50
    sth r4, 0x183c(r31)
    cmpwi r8, 0x0
    blt ksNesLinecntIrqDefault
    addi r10, r4, 0x1
    cmpwi r8, 0xef
    bgt ksNesLinecntIrqDefault
L_8003CB44:
    add r10, r10, r8
L_8003CB48:
    sth r10, 0x1828(r31)
    b ksNesLinecntIrqDefault
L_8003CB50:
    lha r10, 0x183c(r31)
    cmpwi r8, 0x0
    blt L_8003CB48
    cmpwi r8, 0xef
    bgt L_8003CB48
    addi r8, r8, 0x1
    b L_8003CB44
    
entry ksNesStore04_e000
    andi. r7, r3, 0x1
    stb r7, 0x1857(r31)
    b ksNesLinecntIrqDefault

entry ksNesLinecntIrq05Timer
    li r0, 0x80
    stb r0, 0x17bb(r31)
    li r0, 0x7fff
    sth r0, 0x17ae(r31)
    b SUB_8003b3a0

entry ksNesLinecntIrq05Vcount
    li r0, 0xc0
    stb r0, 0x17b6(r31)
    cmpwi r7, 0x0
    bne SUB_8003b3a0
    b ksNesMainLoop2

entry ksNesStore05_4000
    andi.      r7,r3,0x1000
    beq        ksNesStoreIO
    lbz        r7,0x17b2(r31)
    subic.     r8,r3,0x5c00
    blt        LAB_8003cbc8
    cmpwi      r7,0x3
    addi       r9,r31,0x1120
    beq        ksNesLinecntIrqDefault
    stbx       r4,r8,r9
    b          ksNesLinecntIrqDefault
LAB_8003cbc8:
    cmpwi      r3,0x520a
    bgt        ksNesLinecntIrqDefault
    subic.     r7,r3,0x5209
    blt        LAB_8003cc20
    addi       r8,r31,0x17cb
    stbx       r4,r8,r7
    bne        ksNesLinecntIrqDefault
    lbz        r8,0x17cc(r31)
    li         r9,0x72
    rlwimi     r4,r8,0x8,0x10,0x17
    cmpwi      r4,0x0
    beq        LAB_8003cc14
    divwu      r7,r4,r9
    lha        r8,0x1820(r31)
    add        r7,r7,r8
    sth        r7,0x17ae(r31)
    li         r8,0x0
    stb        r8,0x17cc(r31)
    b          ksNesLinecntIrqDefault
LAB_8003cc14:
    li         r7,0x7fff
    sth        r7,0x17ae(r31)
    b          ksNesLinecntIrqDefault
LAB_8003cc20:
    cmpwi      r3,0x5207
    bge        ksNesLinecntIrqDefault
    subic.     r7,r3,0x5205
    blt        LAB_8003cc54
    addi       r8,r31,0x17bc
    stbx       r4,r8,r7
    bne        ksNesLinecntIrqDefault
    lbz        r8,0x17bd(r31)
    mullw      r9,r8,r4
    stb        r9,0x17b7(r31)
    rlwinm     r10,r9,0x18,0x8,0x1f
    stb        r10,0x17b8(r31)
    b          ksNesLinecntIrqDefault
LAB_8003cc54:
    subic.     r7,r3,0x5203
    blt        LAB_8003cc84
    beq        LAB_8003cc6c
    andi.      r7,r4,0x80
    stb        r7,0x1857(r31)
    b          ksNesLinecntIrqDefault
LAB_8003cc6c:
    stb        r4,0x17bf(r31)
    cmpwi      r4,0xf0
    blt        LAB_8003cc7c
    subi       r4,r4,0x14
LAB_8003cc7c:
    sth        r4,0x1828(r31)
    b          ksNesLinecntIrqDefault
LAB_8003cc84:
    subic.     r7,r3,0x5200
    blt        LAB_8003cca0
    bne        LAB_8003cc94
    andi.      r4,r4,0xdf
LAB_8003cc94:
    addi       r8,r31,0x17c0
    stbx       r4,r8,r7
    b          ksNesLinecntIrqDefault
LAB_8003cca0:
    cmpwi      r3,0x5130
    bgt        ksNesLinecntIrqDefault
    subic.     r7,r3,0x5100
    blt        LAB_8003ccc8
    rlwinm     r8,r7,0x2,0x0,0x1d
    lis        r9,ksNesStore05FuncTbl@h
    ori        r9,r9,ksNesStore05FuncTbl@l
    lwzx       r8,r9,r8
    mtspr      CTR,r8
    bctr
LAB_8003ccc8:
    cmpwi      r3,0x5015
    bgt        ksNesLinecntIrqDefault
    beq        ksNesStore4000
    cmpwi      r3,0x5011
    bgt        ksNesLinecntIrqDefault
    beq        LAB_8003ccf0
    cmpwi      r3,0x5010
    beq        LAB_8003ccf0
    cmpwi      r3,0x5008
    bge        ksNesLinecntIrqDefault
LAB_8003ccf0:
    b          ksNesStore4000

entry ksNesStore05_5130
    lhz r7, 0x1766(r31)
    cmpwi r7, 0x100
    blt ksNesLinecntIrqDefault
    andi. r8, r4, 0x1
    stb r8, 0x179f(r31)
    b ksNesLinecntIrqDefault

entry ksNesStore05_5100
    andi.      r7, r4, 0x3
    stb        r7, state_temp->_176E[42] // register 0x5100. Select PRG banking mode.
LAB_8003cd14:
    // select bbram bank?
    lbz        r8, state_temp->_1768[0] // 0 or 3
    lbz        r9, state_temp->_176E[43] // bank number?
    lwz        r10, state_temp->bbramp
    // r9 = r9 & r8;
    // r8 must be 0x03 to limit it to the range [0, 3]
    // r8 must be 0x03 to limit it to the range [3, 6]
    and        r9, r9, r8
    // r9 = r9 - 3;
    subi       r9, r9, 0x3
    // r9 = r9 << 13;
    // r9 = r9 * 8192;
    // r9 = r9 * 0x2000;
    slwi       r9, r9, 13
    // r9 = r9 + r10;
    add        r9, r9, r10
    // state_temp->cpu_6000_7fff = bbramp + (((r9 & r8) - 3) * 0x2000)
    // state_temp->cpu_6000_7fff = r9;
    stw        r9, state_temp->cpu_6000_7fff

    lbz        r8, state_temp->prg_banks
    lbz        r9, state_temp->_176E[47]
    lbz        r7, state_temp->_176E[42]
    lwz        r5, state_temp->prgromp
    and        r9, r9, r8
    cmpwi      r7, 0x2
    bge        LAB_8003cdac
    cmpwi      r7, 0x0
    bne        LAB_8003cd78
    subi       r9, r9, 0x4
    rlwinm     r9, r9, 0xd, 0x0, 0x10
    add        r9, r9, r5
    stw        r9, state_temp->cpu_8000_9fff
    stw        r9, state_temp->cpu_a000_bfff
    stw        r9, state_temp->cpu_c000_dfff
    stw        r9, state_temp->cpu_e000_ffff
    b          ksNesLinecntIrqDefault
LAB_8003cd78:
    subi       r9, r9, 0x6
    rlwinm     r9, r9, 0xd, 0x0, 0x11
    add        r9, r9, r5
    stw        r9, state_temp->cpu_c000_dfff
    stw        r9, state_temp->cpu_e000_ffff
    lbz        r9, state_temp->_176E[45]
    and        r9, r9, r8
    subi       r9, r9, 0x4
    rlwinm     r9, r9, 0xd, 0x0, 0x11
    add        r9, r9, r5
    stw        r9, state_temp->cpu_8000_9fff
    stw        r9, state_temp->cpu_a000_bfff
    b          ksNesLinecntIrqDefault
LAB_8003cdac:
    cmpwi      r7, 0x2
    bne        LAB_8003cdfc
    subi       r9, r9, 0x7
    rlwinm     r9, r9, 0xd, 0x0, 0x12
    add        r9, r9, r5
    stw        r9, state_temp->cpu_e000_ffff
    lbz        r9, state_temp->_176E[46]
    and        r9, r9, r8
    subi       r9, r9, 0x6
    rlwinm     r9, r9, 0xd, 0x0, 0x12
    add        r9, r9, r5
    stw        r9, state_temp->cpu_c000_dfff
    lbz        r9, state_temp->_176E[45]
    and        r9, r9, r8
    subi       r9, r9, 0x4
    rlwinm     r9, r9, 0xd, 0x0, 0x11
    add        r9, r9, r5
    stw        r9, state_temp->cpu_8000_9fff
    stw        r9, state_temp->cpu_a000_bfff
    b          ksNesLinecntIrqDefault
LAB_8003cdfc:
    subi       r9, r9, 0x7
    rlwinm     r9, r9, 0xd, 0x0, 0x12
    add        r9, r9, r5
    stw        r9, state_temp->cpu_e000_ffff
    lbz        r9, state_temp->_176E[46]
    and        r9, r9, r8
    subi       r9, r9, 0x6
    rlwinm     r9, r9, 0xd, 0x0, 0x12
    add        r9, r9, r5
    stw        r9, state_temp->cpu_c000_dfff
    lbz        r9, state_temp->_176E[45]
    and        r9, r9, r8
    subi       r9, r9, 0x5
    rlwinm     r9, r9, 0xd, 0x0, 0x12
    add        r9, r9, r5
    stw        r9, state_temp->cpu_a000_bfff
    lbz        r9, state_temp->_176E[44]
    and        r9, r9, r8
    subi       r9, r9, 0x4
    rlwinm     r9, r9, 0xd, 0x0, 0x12
    add        r9, r9, r5
    stw        r9, state_temp->cpu_8000_9fff
    b          ksNesLinecntIrqDefault

entry ksNesStore05_5113
    // r8 = &state_temp->_176E[24];
    addi r8, state_temp, state_temp._176E[24]
    // this functions handles memory mapped registers 0x5113-0x5117.
    // r7 must control which register is written to.
    // r8[r7] = r4
    stbx r4, r8, r7
    b LAB_8003cd14

entry ksNesStore05_5101
    andi. r7, r4, 0x3
    stb r7, 0x179e(r31)
L_8003CE6C:
    lbz r7, 0x179e(r31)
    lhz r8, 0x1766(r31)
    lbz r9, 0x17a7(r31)
    cmpwi r7, 0x2
    bge L_8003CEF4
    cmpwi r7, 0x0
    bne L_8003CEAC
    slwi r9, r9, 3
    addi r5, r31, 0x17fb
    and r9, r9, r8
    addi r0, r5, 0x8
L_8003CE98:
    stbu r9, 0x1(r5)
    addi r9, r9, 0x1
    cmpw r5, r0
    bne L_8003CE98
    b ksNesLinecntIrqDefault
L_8003CEAC:
    slwi r9, r9, 2
    addi r5, r31, 0x17ff
    and r9, r9, r8
    addi r0, r5, 0x4
L_8003CEBC:
    stbu r9, 0x1(r5)
    addi r9, r9, 0x1
    cmpw r5, r0
    bne L_8003CEBC
    lbz r9, 0x17a3(r31)
    addi r5, r31, 0x17fb
    slwi r9, r9, 2
    addi r0, r5, 0x4
    and r9, r9, r8
L_8003CEE0:
    stbu r9, 0x1(r5)
    addi r9, r9, 0x1
    cmpw r5, r0
    bne L_8003CEE0
    b ksNesLinecntIrqDefault
L_8003CEF4:
    cmpwi r7, 0x2
    bne L_8003CF5C
    slwi r9, r9, 1
    and r9, r9, r8
    stb r9, 0x1802(r31)
    addi r9, r9, 0x1
    stb r9, 0x1803(r31)
    lbz r9, 0x17a5(r31)
    slwi r9, r9, 1
    and r9, r9, r8
    stb r9, 0x1800(r31)
    addi r9, r9, 0x1
    stb r9, 0x1801(r31)
    lbz r9, 0x17a3(r31)
    slwi r9, r9, 1
    and r9, r9, r8
    stb r9, 0x17fe(r31)
    addi r9, r9, 0x1
    stb r9, 0x17ff(r31)
    lbz r9, 0x17a1(r31)
    slwi r9, r9, 1
    and r9, r9, r8
    stb r9, 0x17fc(r31)
    addi r9, r9, 0x1
    stb r9, 0x17fd(r31)
    b ksNesLinecntIrqDefault
L_8003CF5C:
    addi r5, r31, 0x17fc
    li r10, 0x7
    addi r7, r31, 0x17a0
L_8003CF68:
    and r9, r9, r8
    stbx r9, r5, r10
    subic. r10, r10, 0x1
    lbzx r9, r7, r10
    bge L_8003CF68
    b ksNesLinecntIrqDefault

entry ksNesStore05_5120
    lbz r9, 0x179f(r31)
    addi r8, r31, 0x1780
    stbx r4, r8, r7
    addi r8, r31, 0x17e4
    stbx r9, r8, r7
    b L_8003CE6C

entry ksNesStore05_5128
    lbz r9, 0x179f(r31)
    addi r8, r31, 0x1780
    stbx r4, r8, r7
    addi r8, r31, 0x17e4
    stbx r9, r8, r7
    b ksNesLinecntIrqDefault

entry ksNesStore05_5102
    subi r7, r31, 0x3952
    stbx r4, r7, r3
    b ksNesLinecntIrqDefault

entry ksNesStore05_5104
    andi. r7, r4, 0x3
    stb r7, 0x17b2(r31)
    b ksNesLinecntIrqDefault

entry ksNesStore05_5105
    stb r4, 0x17b3(r31)
    ori r5, r4, 0x100
    addi r7, r31, 0x180c
    addi r8, r31, 0x800
L_8003CFD8:
    andi. r9, r5, 0x3
    srwi r5, r5, 2
    cmpwi r9, 0x2
    bge L_8003CFF4
    slwi r9, r9, 10
    add r0, r8, r9
    b L_8003D000
L_8003CFF4:
    addi r0, r31, 0x1120
    beq L_8003D000
    addi r0, r31, 0x1000
L_8003D000:
    cmpwi r5, 0x1
    stwu r0, 0x4(r7)
    bne L_8003CFD8
    b ksNesLinecntIrqDefault

entry ksNesStore05_5106
    subi r7, r31, 0x395a
    stbx r4, r7, r3
    b ksNesLinecntIrqDefault

entry ksNesLoad05_4000
    andi. r7, r3, 0x1000
    beq ksNesLoadIO
    subic. r7, r3, 0x5c00
    addi r9, r31, 0x1120
    blt L_8003D038
    lbzx r4, r9, r7
    bctr
L_8003D038:
    cmpwi r3, 0x5010
    bltctr
    bgt L_8003D054
    lbz r4, 0x17b4(r31)
    li r7, 0x1
    stb r7, 0x17b4(r31)
    bctr
L_8003D054:
    cmpwi r3, 0x5015
    bltctr
    bgt L_8003D068
    lbz r4, 0x17b5(r31)
    bctr
L_8003D068:
    subic. r7, r3, 0x5204
    bltctr
    bgt L_8003D084
    lbz r4, 0x17b6(r31)
    andi. r8, r4, 0x7f
    stb r8, 0x17b6(r31)
    bctr
L_8003D084:
    cmpwi r3, 0x5209
    bgtctr
    beq L_8003D09C
    addi r9, r31, 0x17b6
    lbzx r4, r9, r7
    bctr
L_8003D09C:
    lbz r4, 0x17bb(r31)
    li r8, 0x0
    stb r8, 0x17bb(r31)
    bctr

entry ksNesStore07_8000
    lbz r8, 0x1765(r31)
    clrlslwi r10, r4, 28, 2
    lwz r9, 0x17f0(r31)
    addi r0, r31, 0x800
    and r10, r10, r8
    rlwinm r7, r4, 6, 21, 21
    subi r10, r10, 0x4
    add r7, r7, r0
    slwi r10, r10, 13
    stw r7, 0x1810(r31)
    stw r7, 0x1814(r31)
    stw r7, 0x1818(r31)
    stw r7, 0x181c(r31)
    add r10, r10, r9
    stw r10, 0x1690(r31)
    stw r10, 0x1694(r31)
    stw r10, 0x1698(r31)
    stw r10, 0x169c(r31)
    b ksNesLinecntIrqDefault

entry ksNesStore09_8000
    b ksNesLinecntIrqDefault

entry ksNesStore09_a000
    andi. r7, r3, 0x1000
    bne L_8003D124
    lbz r8, 0x1765(r31)
    lwz r9, 0x17f0(r31)
    and r8, r8, r4
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r9
    stw r8, 0x1690(r31)
    b ksNesLinecntIrqDefault
L_8003D124:
    lhz r8, 0x1766(r31)
    slwi r7, r4, 2
    and r8, r8, r7
    addi r8, r8, 0x1
    stb r8, 0x17fd(r31)
    b ksNesLinecntIrqDefault

entry ksNesStore09_c000
    andi. r7, r3, 0x1000
    bne L_8003D158
    lhz r8, 0x1766(r31)
    slwi r7, r4, 2
    and r8, r8, r7
    stb r8, 0x17fc(r31)
    b ksNesLinecntIrqDefault
L_8003D158:
    lhz r8, 0x1766(r31)
    slwi r7, r4, 2
    and r8, r8, r7
    stb r8, 0x1801(r31)
    b ksNesLinecntIrqDefault

entry ksNesStore09_e000
    andi. r7, r3, 0x1000
    bne L_8003D188
    lhz r8, 0x1766(r31)
    slwi r7, r4, 2
    and r8, r8, r7
    stb r8, 0x1800(r31)
    b ksNesLinecntIrqDefault
L_8003D188:
    clrlslwi r7, r4, 31, 4
    addi r0, r31, 0x1888
    addi r9, r31, 0x180c
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003D19C:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003D19C
    b ksNesLinecntIrqDefault
    
entry ksNesStore0a_8000
    b ksNesLinecntIrqDefault

entry ksNesStore0a_a000
    andi. r7, r3, 0x1000
    bne L_8003D124
    lbz r8, 0x1765(r31)
    slwi r7, r4, 1
    lwz r9, 0x17f0(r31)
    and r8, r8, r7
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r9
    stw r8, 0x1690(r31)
    stw r8, 0x1694(r31)
    b ksNesLinecntIrqDefault

entry ksNesLinecntIrq49
    li r8, 0x7fff
    sth r8, 0x1828(r31)
    cmpwi r7, 0x0
    bne SUB_8003b3a0
    b ksNesMainLoop2

entry ksNesStore12_8000
    rlwinm r7, r3, 22, 29, 29
    addi r0, r31, 0x17d0
    rlwimi r7, r3, 0, 30, 31
    andi. r8, r4, 0xf
    cmpwi r7, 0x6
    bge ksNesLinecntIrqDefault
    stbx r8, r7, r0
    andi. r9, r7, 0x1
    xori r7, r7, 0x1
    lbzx r9, r7, r0
    slwi r8, r8, 4
    lbz r10, 0x1765(r31)
    bne L_8003D234
    srwi r8, r8, 4
    slwi r9, r9, 4
L_8003D234:
    or r8, r8, r9
    lwz r9, 0x17f0(r31)
    and r8, r8, r10
    srwi r7, r7, 1
    subi r8, r8, 0x4
    subf r8, r7, r8
    slwi r7, r7, 2
    slwi r8, r8, 13
    add r7, r7, r31
    add r8, r8, r9
    stw r8, 0x1690(r7)
    b ksNesLinecntIrqDefault

entry ksNesStore12_a000
    rlwinm r7, r3, 22, 27, 29
    addi r0, r31, 0x17ce
    rlwimi r7, r3, 0, 30, 31
    andi. r8, r4, 0xf
    stbx r8, r7, r0
    andi. r9, r7, 0x1
    xori r7, r7, 0x1
    lbzx r9, r7, r0
    slwi r8, r8, 4
    bne L_8003D294
    srwi r8, r8, 4
    slwi r9, r9, 4
L_8003D294:
    lhz r10, 0x1766(r31)
    or r8, r8, r9
    srwi r7, r7, 1
    addi r0, r31, 0x17f8
    and r8, r8, r10
    stbx r8, r7, r0
    b ksNesLinecntIrqDefault
    
entry ksNesStore12_e000
    andi. r7, r3, 0x1000
    bne L_8003D2CC
    andi. r8, r4, 0xf
    andi. r7, r3, 0x3
    addi r0, r31, 0x17e6
    stbx r8, r7, r0
    b ksNesLinecntIrqDefault
L_8003D2CC:
    andi. r7, r3, 0x2
    bne L_8003D318
    andi. r7, r3, 0x1
    beq ksNesLinecntIrqDefault
    andi. r7, r4, 0x1
    stb r7, 0x1857(r31)
    lbz r7, 0x17e6(r31)
    lbz r8, 0x17e7(r31)
    lbz r9, 0x17e8(r31)
    lbz r10, 0x17e9(r31)
    rlwimi r7, r8, 4, 24, 27
    rlwimi r7, r9, 8, 20, 23
    rlwimi r7, r10, 12, 16, 19
    li r8, 0x72
    divwu r9, r7, r8
    lha r8, 0x1820(r31)
    add r8, r8, r9
    sth r8, 0x1828(r31)
    b ksNesLinecntIrqDefault
L_8003D318:
    andi. r8, r3, 0x1
    bne L_8003D328
    xori r4, r4, 0x1
    b ksNesStore16_9000
L_8003D328:
    cmpwi r4, 0x4e
    li r3, 0x10
    beq L_8003D354
    andi. r7, r4, 0x42
    xori r7, r7, 0x2
    cmpwi r7, 0x0
    bne ksNesLinecntIrqDefault
    extrwi r8, r4, 4, 26
    lis r7, 0x800d
    ori r7, r7, 0x67c0
    lbzx r3, r7, r8
L_8003D354:
    lwz r9, 0x185c(r31)
    andi. r9, r9, 0x1000
    bne ksNesLinecntIrqDefault
    bl Sound_PlayMENUPCM
    b ksNesLinecntIrqDefault
    
entry ksNesStore13_4000
    cmpwi r3, 0x4800
    blt ksNesStoreIO
    beq L_8003D3B4
    extrwi r8, r3, 1, 20
    addi r7, r31, 0x17cb
    stbx r4, r7, r8
    lbz r8, 0x17cc(r31)
    lbz r7, 0x17cb(r31)
    andi. r9, r8, 0x80
    stb r9, 0x1857(r31)
    rlwimi r7, r8, 8, 17, 23
    li r8, 0x7fff
    subf r7, r7, r8
    li r8, 0x72
    divwu r9, r7, r8
    lha r8, 0x1820(r31)
    add r9, r9, r8
    sth r9, 0x1828(r31)
    b ksNesLinecntIrqDefault
L_8003D3B4:
    lbz r8, 0x17ea(r31)
    lwz r7, 0x17f8(r31)
    andi. r9, r8, 0x7f
    andi. r10, r8, 0x80
    stbx r4, r7, r8
    beq ksNesLinecntIrqDefault
    addi r8, r8, 0x1
    ori r8, r8, 0x80
    stb r8, 0x17ea(r31)
    b ksNesLinecntIrqDefault
    
entry ksNesLoad13_4000
    cmpwi r3, 0x4800
    blt ksNesLoadIO
    beq L_8003D41C
    lha r7, 0x1820(r31)
    lha r8, 0x1828(r31)
    subf r7, r7, r8
    li r8, 0x7fff
    mulli r7, r7, 0x72
    andi. r9, r3, 0x800
    subf r7, r7, r8
    bne L_8003D410
    andi. r4, r7, 0xff
    bctr
L_8003D410:
    lbz r4, 0x17cc(r31)
    rlwimi r4, r7, 0, 25, 31
    bctr
L_8003D41C:
    lbz r8, 0x17ea(r31)
    lwz r7, 0x17f8(r31)
    andi. r9, r8, 0x7f
    andi. r10, r8, 0x80
    lbzx r4, r7, r8
    beqctr
    addi r8, r8, 0x1
    ori r8, r8, 0x80
    stb r8, 0x17ea(r31)
    bctr

entry ksNesStore13_8000
    lhz r8, 0x1766(r31)
    extrwi r7, r3, 3, 18
    addi r9, r31, 0x17fc
    and r8, r8, r4
    stbx r8, r9, r7
    b ksNesLinecntIrqDefault

entry ksNesStore13_c000
    lhz r8, 0x1766(r31)
    rlwinm r7, r3, 23, 28, 29
    cmpwi r4, 0x1
    ble ksNesLinecntIrqDefault
    cmpwi r4, 0xe0
    addi r9, r31, 0x1810
    bge L_8003D490
    lwz r5, 0x17f4(r31)
    and r8, r8, r4
    slwi r8, r8, 10
    add r8, r8, r5
    stwx r8, r9, r7
    b ksNesLinecntIrqDefault
L_8003D490:
    addi r5, r31, 0x800
    clrlslwi r8, r4, 31, 10
    add r8, r8, r5
    stwx r8, r9, r7
    b ksNesLinecntIrqDefault

entry ksNesStore13_e000
    andi. r7, r3, 0x1000
    beq L_8003D4B4
    andi. r7, r3, 0x800
    bne L_8003D4E4
L_8003D4B4:
    lbz r9, 0x1765(r31)
    extrwi r7, r3, 2, 19
    rlwinm r8, r3, 23, 28, 29
    addi r5, r31, 0x1690
    and r9, r9, r4
    addi r7, r7, 0x4
    lwz r10, 0x17f0(r31)
    subf r9, r7, r9
    slwi r9, r9, 13
    add r9, r9, r10
    stwx r9, r5, r8
    b ksNesLinecntIrqDefault
L_8003D4E4:
    stb r4, 0x17ea(r31)
    b ksNesLinecntIrqDefault

entry ksNesStore16_8000
    lbz r8, 0x1765(r31)
    andi. r7, r3, 0x1000
    bne ksNesStore16_9000
    lwz r7, 0x17f0(r31)
    and r9, r4, r8
    subi r9, r9, 0x4
    slwi r9, r9, 13
    add r7, r7, r9
    stw r7, 0x1690(r31)
    b ksNesLinecntIrqDefault

entry ksNesStore16_9000
    clrlslwi r7, r4, 30, 4
    addi r0, r31, 0x1888
    addi r9, r31, 0x180c
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003D528:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003D528
    b ksNesLinecntIrqDefault

entry ksNesStore16_a000
    lbz r8, 0x1765(r31)
    andi. r7, r3, 0x1000
    bne ksNesStore16_b000
L_8003D548:
    lwz r7, 0x17f0(r31)
    and r9, r4, r8
    subi r9, r9, 0x5
    slwi r9, r9, 13
    add r7, r7, r9
    stw r7, 0x1694(r31)
    b ksNesLinecntIrqDefault

entry ksNesStore16_b000
    rlwinm r7, r3, 21, 28, 30
    andi. r8, r3, 0x2
    bne ksNesLinecntIrqDefault
    rlwimi r7, r3, 0, 31, 31
    srwi r8, r4, 1
    add r7, r7, r31
    stb r8, 0x17f6(r7)
    b ksNesLinecntIrqDefault

entry ksNesStore17_a000
    lbz r8, 0x1765(r31)
    andi. r7, r3, 0x1000
    beq L_8003D548

entry ksNesStore17_b000
    rlwinm r7, r3, 21, 28, 30
    andi. r8, r3, 0xa
    beq L_8003D5A0
    addi r7, r7, 0x1
L_8003D5A0:
    add r7, r7, r31
    lbz r10, 0x17f6(r7)
    andi. r8, r3, 0x5
    bne L_8003D814
    b L_8003D820
    
entry ksNesStore17_e000
    andi. r8, r3, 0x1000
    beq ksNesStore17_b000
    andi. r7, r3, 0xf
    beq L_8003D870
    andi. r8, r7, 0x4
    bne L_8003D87C
    andi. r8, r7, 0x8
    bne L_8003D888
    b ksNesLinecntIrqDefault

entry ksNesLinecntIrq18
    addi r25, r25, 0xc00
    andi. r8, r7, 0x1
    bne L_8003D5F0
    li r8, 0x7fff
    sth r8, 0x1828(r31)
    b L_8003D608
L_8003D5F0:
    lbz r8, 0x17cf(r31)
    lha r9, 0x1820(r31)
    li r10, 0x100
    subf r8, r8, r10
    add r9, r9, r8
    sth r9, 0x1828(r31)
L_8003D608:
    cmpwi r7, 0x0
    beq ksNesMainLoop2
    b SUB_8003b3a0

entry ksNesStore18_8000
    lbz r8, 0x1765(r31)
    andi. r7, r3, 0x1000
    bne L_8003D644
    lwz r7, 0x17f0(r31)
    slwi r9, r4, 1
    and r8, r8, r9
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r7, r7, r8
    stw r7, 0x1690(r31)
    stw r7, 0x1694(r31)
    b ksNesLinecntIrqDefault
L_8003D644:
    lbz r10, 0x17cd(r31)
    andi. r7, r3, 0x3000
    subi r7, r7, 0x1000
    srwi r7, r7, 10
    andi. r8, r3, 0x3
    beq L_8003D670
    xor r8, r8, r10
    add r7, r7, r8
    addi r7, r7, 0x1
    cmpwi r8, 0x3
    beq ksNesLinecntIrqDefault
L_8003D670:
    ori r3, r7, 0x5000
    b ksNesStore4000

entry ksNesStore18_a000
    andi. r7, r3, 0x1fff
    cmpwi r7, 0x1003
    bne L_8003D644
    rlwinm r7, r4, 2, 26, 27
    addi r0, r31, 0x1888
    addi r9, r31, 0x180c
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003D698:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003D698
    b ksNesLinecntIrqDefault

entry ksNesStore18_c000
    lbz r8, 0x1765(r31)
    andi. r7, r3, 0x1000
    bne L_8003D6D4
    lwz r7, 0x17f0(r31)
    and r8, r8, r4
    subi r8, r8, 0x6
    slwi r8, r8, 13
    add r7, r7, r8
    stw r7, 0x1698(r31)
    b ksNesLinecntIrqDefault
L_8003D6D4:
    lbz r9, 0x17cd(r31)
    andi. r8, r3, 0x3
    beq L_8003D6EC
    cmpwi r8, 0x3
    beq L_8003D6EC
    xor r8, r8, r9
L_8003D6EC:
    rlwimi r8, r7, 22, 29, 29
    xori r8, r8, 0x4
    add r8, r8, r31
    stb r4, 0x17fc(r8)
    b ksNesLinecntIrqDefault
    
entry ksNesStore18_e000
    andi. r7, r3, 0x1000
    beq L_8003D6D4
    andi. r7, r3, 0x3
    beq L_8003D720
    lbz r10, 0x17ce(r31)
    and. r8, r3, r10
    bne L_8003D728
    b ksNesLinecntIrqDefault
L_8003D720:
    stb r4, 0x17cf(r31)
    b ksNesLinecntIrqDefault
L_8003D728:
    andi. r7, r4, 0x3
    stb r7, 0x1857(r31)
    lbz r8, 0x17cf(r31)
    lha r9, 0x1820(r31)
    li r10, 0x100
    subf r8, r8, r10
    add r9, r9, r8
    sth r9, 0x1828(r31)
    bne ksNesLinecntIrqDefault
    stb r7, 0x1856(r31)
    b ksNesLinecntIrqDefault

entry ksNesLinecntIrq19
    subi r25, r25, 0xc00
    li r8, 0x7fff
    sth r8, 0x1828(r31)
    cmpwi r7, 0x0
    bne SUB_8003b3a0
    b ksNesMainLoop2
    
entry ksNesStore19_8000
    lbz r8, 0x17c9(r31)
    andi. r7, r3, 0x1000
    bne L_8003D7A4
    lwz r7, 0x17f0(r31)
    lbz r9, 0x1765(r31)
    and r9, r9, r4
    stb r9, 0x17ca(r31)
    subi r9, r9, 0x4
    slwi r9, r9, 13
    add r7, r7, r9
    andi. r8, r8, 0x2
    bne L_8003D7DC
L_8003D79C:
    stw r7, 0x1690(r31)
    b ksNesLinecntIrqDefault
L_8003D7A4:
    lbz r8, 0x17c9(r31)
    andi. r7, r3, 0x2
    beq ksNesStore16_9000
    lbz r9, 0x17ca(r31)
    stb r4, 0x17c9(r31)
    xor r8, r8, r4
    andi. r8, r8, 0x2
    bne ksNesLinecntIrqDefault
    lwz r7, 0x17f0(r31)
    subi r9, r9, 0x4
    slwi r9, r9, 13
    add r7, r7, r9
    andi. r8, r4, 0x2
    beq L_8003D79C
L_8003D7DC:
    subi r7, r7, 0x4000
    stw r7, 0x1698(r31)
    b ksNesLinecntIrqDefault
    
entry ksNesStore19_a000
    lbz r8, 0x1765(r31)
    andi. r7, r3, 0x1000
    beq L_8003D548

entry ksNesStore19_b000
    andi. r9, r3, 0x85
    rlwinm r7, r3, 21, 28, 30
    beq L_8003D804
    addi r7, r7, 0x1
L_8003D804:
    add r7, r7, r31
    lbz r10, 0x17f6(r7)
    andi. r8, r3, 0x42
    beq L_8003D820
L_8003D814:
    rlwimi r10, r4, 4, 24, 27
    stb r10, 0x17f6(r7)
    b ksNesLinecntIrqDefault
L_8003D820:
    rlwimi r10, r4, 0, 28, 31
    stb r10, 0x17f6(r7)
    b ksNesLinecntIrqDefault

entry ksNesStore19_e000
    andi. r7, r3, 0x1000
    beq ksNesStore19_b000
    andi. r7, r3, 0xc7
    beq L_8003D870
    cmpwi r7, 0x2
    beq L_8003D87C
    cmpwi r7, 0x1
    beq L_8003D888
    cmpwi r7, 0x4
    beq L_8003D888
    cmpwi r7, 0x3
    beq L_8003D8B8
    andi. r8, r7, 0x40
    bne L_8003D87C
    andi. r8, r7, 0x80
    bne L_8003D888
    b ksNesLinecntIrqDefault
L_8003D870:
    andi. r8, r4, 0xf
    stb r8, 0x17cb(r31)
    b ksNesLinecntIrqDefault
L_8003D87C:
    slwi r8, r4, 4
    stb r8, 0x17cc(r31)
    b ksNesLinecntIrqDefault
L_8003D888:
    andi. r7, r4, 0x2
    stb r7, 0x1857(r31)
    lha r10, 0x1820(r31)
    lbz r7, 0x17cb(r31)
    lbz r8, 0x17cc(r31)
    sth r10, 0x182a(r31)
    or r7, r7, r8
    li r9, 0x101
    subf r7, r7, r9
    add r10, r10, r7
    sth r10, 0x1828(r31)
    b ksNesLinecntIrqDefault
L_8003D8B8:
    lbz r7, 0x17cb(r31)
    lbz r8, 0x17cc(r31)
    lha r10, 0x182a(r31)
    or r7, r7, r8
    add r10, r10, r7
    sth r10, 0x1828(r31)
    b ksNesLinecntIrqDefault

entry ksNesStore42_8000
    lhz r5, 0x1766(r31)
    addi r7, r31, 0x17fb
    clrlslwi r10, r4, 28, 3
    addi r0, r7, 0x8
    and r10, r10, r5
    L_8003D8E8:
    stbu r10, 0x1(r7)
    addi r10, r10, 0x1
    cmpw r7, r0
    bne L_8003D8E8
    lbz r8, 0x1765(r31)
    rlwinm r9, r4, 30, 28, 29
    lwz r7, 0x17f0(r31)
    and r8, r8, r9
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r7
    stw r8, 0x1690(r31)
    stw r8, 0x1694(r31)
    stw r8, 0x1698(r31)
    stw r8, 0x169c(r31)
    b ksNesLinecntIrqDefault
    
entry ksNesLinecntIrq43
    addi r25, r25, 0x4000
    li r8, 0x7fff
    sth r8, 0x1828(r31)
    cmpwi r7, 0x0
    bne SUB_8003b3a0
    b ksNesMainLoop2
    
entry ksNesStore43_c000
    andi. r7, r3, 0x1000
    bne L_8003D960
    lha r8, 0x1820(r31)
    li r9, 0xdb
    subf r9, r4, r9
    add r8, r8, r9
    sth r8, 0x1828(r31)
    b ksNesLinecntIrqDefault
L_8003D960:
    andi. r7, r4, 0x10
    stb r7, 0x1857(r31)
    b ksNesLinecntIrqDefault

entry ksNesStore44_8000
    lhz r7, 0x1766(r31)
    slwi r8, r4, 1
    rlwinm r9, r3, 21, 29, 30
    addi r0, r31, 0x17fc
    and r7, r7, r8
    stbux r7, r9, r0
    addi r7, r7, 0x1
    stb r7, 0x1(r9)
    b ksNesLinecntIrqDefault

entry ksNesStore44_c000
    lhz r8, 0x1766(r31)
    extrwi r7, r3, 1, 19
    addi r9, r31, 0x17eb
    and r8, r8, r4
    stbx r8, r9, r7
L_8003D9A4:
    lbz r0, 0x17ed(r31)
    andi. r8, r0, 0x10
    bne L_8003D9D8
    clrlslwi r7, r0, 30, 4
    addi r0, r31, 0x1888
    addi r9, r31, 0x180c
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003D9C4:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003D9C4
    b ksNesLinecntIrqDefault
L_8003D9D8:
    lbz r7, 0x17eb(r31)
    lwz r9, 0x17f4(r31)
    lbz r8, 0x17ec(r31)
    addis r9, r9, 0x2
    slwi r7, r7, 10
    slwi r8, r8, 10
    add r7, r7, r9
    add r8, r8, r9
    andi. r9, r0, 0x3
    bne L_8003DA14
    stw r7, 0x1810(r31)
    stw r8, 0x1814(r31)
    stw r7, 0x1818(r31)
    stw r8, 0x181c(r31)
    b ksNesLinecntIrqDefault
L_8003DA14:
    cmpwi r9, 0x1
    bne L_8003DA30
    stw r7, 0x1810(r31)
    stw r7, 0x1814(r31)
    stw r8, 0x1818(r31)
    stw r8, 0x181c(r31)
    b ksNesLinecntIrqDefault
L_8003DA30:
    andi. r9, r9, 0x1
    bne L_8003DA3C
    mr r8, r7
L_8003DA3C:
    stw r8, 0x1810(r31)
    stw r8, 0x1814(r31)
    stw r8, 0x1818(r31)
    stw r8, 0x181c(r31)
    b ksNesLinecntIrqDefault
    
entry ksNesStore44_e000
    andi. r7, r3, 0x1000
    beq L_8003DA80
    lbz r9, 0x1765(r31)
    slwi r7, r4, 1
    lwz r8, 0x17f0(r31)
    and r7, r7, r9
    subi r7, r7, 0x4
    slwi r7, r7, 13
    add r7, r7, r8
    stw r7, 0x1690(r31)
    stw r7, 0x1694(r31)
    b ksNesLinecntIrqDefault
L_8003DA80:
    stb r4, 0x17ed(r31)
    b L_8003D9A4
    
entry ksNesStore45_8000
    stb r4, 0x17ee(r31)
    b ksNesLinecntIrqDefault

entry ksNesStore45_a000
    lbz r7, 0x17ee(r31)
    cmpwi r7, 0x8
    blt L_8003DAD0
    cmpwi r7, 0xc
    bge L_8003DAE4
    lbz r8, 0x1765(r31)
    clrlslwi r5, r7, 30, 2
    lwz r9, 0x17f0(r31)
    subi r7, r7, 0x5
    and r8, r8, r4
    addi r0, r31, 0x168c
    subf r8, r7, r8
    slwi r8, r8, 13
    add r8, r8, r9
    stwx r8, r5, r0
    b ksNesLinecntIrqDefault
L_8003DAD0:
    lhz r8, 0x1766(r31)
    addi r0, r31, 0x17fc
    and r8, r8, r4
    stbx r8, r7, r0
    b ksNesLinecntIrqDefault
L_8003DAE4:
    bne L_8003DB10
    clrlslwi r7, r4, 30, 4
    addi r0, r31, 0x1888
    addi r9, r31, 0x180c
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003DAFC:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003DAFC
    b ksNesLinecntIrqDefault
L_8003DB10:
    cmpwi r7, 0xd
    bne L_8003DB54
    li r8, 0x1
    cmpwi r4, 0x81
    beq L_8003DB28
    li r8, 0x0
L_8003DB28:
    stb r8, 0x1857(r31)
    lbz r8, 0x17cc(r31)
    lbz r7, 0x17cb(r31)
    li r0, 0x72
    lha r9, 0x1820(r31)
    rlwimi r7, r8, 8, 16, 23
    divwu r8, r7, r0
    add r9, r9, r8
    addi r9, r9, 0x1
    sth r9, 0x1828(r31)
    b ksNesLinecntIrqDefault
L_8003DB54:
    cmpwi r7, 0x10
    bge ksNesLinecntIrqDefault
    addi r0, r31, 0x17bd
    stbx r4, r7, r0
    b ksNesLinecntIrqDefault

entry ksNesStore46_8000
    lbz r8, 0x1765(r31)
    rlwinm r7, r4, 29, 28, 30
    lwz r9, 0x17f0(r31)
    and r8, r8, r7
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r9
    stw r8, 0x1690(r31)
    stw r8, 0x1694(r31)
    lhz r8, 0x1766(r31)
    clrlslwi r7, r4, 28, 3
    and r8, r8, r7
    addi r9, r31, 0x17fb
    addi r0, r9, 0x8
L_8003DBA0:
    stbu r8, 0x1(r9)
    addi r8, r8, 0x1
    cmpw r9, r0
    bne L_8003DBA0
    andi. r0, r4, 0x80
    addi r7, r31, 0x800
    addi r8, r31, 0xc00
    bne L_8003DBC4
    mr r7, r8
L_8003DBC4:
    stw r7, 0x1810(r31)
    stw r8, 0x1814(r31)
    stw r7, 0x1818(r31)
    stw r8, 0x181c(r31)
    b ksNesLinecntIrqDefault

entry ksNesStore49_a000
    andi. r7, r4, 0xf
    extrwi. r8, r3, 1, 19
    beq L_8003DBE8
    clrlslwi r7, r4, 28, 4
L_8003DBE8:
    add r8, r8, r31
    stb r7, 0x17cb(r8)
    b ksNesLinecntIrqDefault
    
entry ksNesStore49_c000
    lbz r8, 0x17cb(r31)
    andi. r7, r4, 0x2
    lbz r9, 0x17cc(r31)
    lha r10, 0x1820(r31)
    stb r7, 0x1857(r31)
    or r8, r8, r9
    li r9, 0x17a
    subf r8, r8, r9
    add r8, r8, r10
    sth r8, 0x1828(r31)
    b ksNesLinecntIrqDefault

entry ksNesStore4b_8000
    andi. r7, r3, 0x1000
    bne L_8003DC54
    // fallthrough

entry ksNesStore4b_a000
    lbz r9, 0x1765(r31)
    andi. r0, r3, 0xe000
    lwz r10, 0x17f0(r31)
    rlwinm r7, r3, 21, 28, 29
    and r9, r9, r4
    addi r8, r31, 0x1690
    slwi r9, r9, 13
    subf r10, r0, r10
    add r9, r9, r10
    stwx r9, r8, r7
    b ksNesLinecntIrqDefault
L_8003DC54:
    lbz r7, 0x17fc(r31)
    rlwinm r8, r4, 5, 25, 25
    lhz r9, 0x1766(r31)
    addi r10, r31, 0x17fb
    andi. r7, r7, 0x3c
    addi r0, r10, 0x4
    or r7, r7, r8
    and r7, r7, r9
L_8003DC74:
    stbu r7, 0x1(r10)
    cmpw r10, r0
    addi r7, r7, 0x1
    bne L_8003DC74
    lbz r7, 0x1800(r31)
    rlwinm r8, r4, 4, 25, 25
    addi r0, r10, 0x4
    andi. r7, r7, 0x3c
    or r7, r7, r8
    and r7, r7, r9
L_8003DC9C:
    stbu r7, 0x1(r10)
    cmpw r10, r0
    addi r7, r7, 0x1
    bne L_8003DC9C
    clrlslwi r7, r4, 31, 4
    addi r0, r31, 0x1888
    addi r9, r31, 0x180c
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003DCC0:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003DCC0
    b ksNesLinecntIrqDefault

entry ksNesStore4b_e000
    andi. r7, r3, 0x1000
    lhz r9, 0x1766(r31)
    clrlslwi r8, r4, 28, 2
    bne L_8003DD10
    lbz r7, 0x17fc(r31)
    addi r10, r31, 0x17fb
    addi r0, r10, 0x4
    andi. r7, r7, 0x40
    or r7, r7, r8
    and r7, r7, r9
L_8003DCFC:
    stbu r7, 0x1(r10)
    cmpw r10, r0
    addi r7, r7, 0x1
    bne L_8003DCFC
    b ksNesLinecntIrqDefault
L_8003DD10:
    lbz r7, 0x1800(r31)
    addi r10, r31, 0x17ff
    addi r0, r10, 0x4
    andi. r7, r7, 0x40
    or r7, r7, r8
    and r7, r7, r9
L_8003DD28:
    stbu r7, 0x1(r10)
    cmpw r10, r0
    addi r7, r7, 0x1
    bne L_8003DD28
    b ksNesLinecntIrqDefault

entry ksNesStore56_6000
    andi. r7, r3, 0x1000
    bne L_8003DD94
    lbz r10, 0x1765(r31)
    rlwinm r8, r4, 30, 28, 29
    lwz r9, 0x17f0(r31)
    and r10, r10, r8
    subi r10, r10, 0x4
    slwi r10, r10, 13
    add r10, r10, r9
    stw r10, 0x1690(r31)
    stw r10, 0x1694(r31)
    stw r10, 0x1698(r31)
    stw r10, 0x169c(r31)
    clrlslwi r7, r4, 30, 3
    addi r8, r31, 0x17fb
    rlwimi r7, r4, 31, 26, 26
    addi r0, r8, 0x8
L_8003DD80:
    stbu r7, 0x1(r8)
    addi r7, r7, 0x1
    cmpw r8, r0
    bne L_8003DD80
    b ksNesLinecntIrqDefault
L_8003DD94:
    andi. r7, r4, 0x10
    bne ksNesLinecntIrqDefault
    lwz r8, 0x185c(r31)
    andi. r3, r4, 0xf
    addi r3, r3, 0x1
    andi. r8, r8, 0x1000
    bne ksNesLinecntIrqDefault
    bl Sound_PlayMENUPCM
    b ksNesLinecntIrqDefault

entry ksNesStore57_6000
    rlwinm r7, r4, 2, 28, 28
    addi r9, r31, 0x17fc
    li r8, 0x0
L_8003DDC4:
    stbx r7, r9, r8
    addi r8, r8, 0x1
    addi r7, r7, 0x1
    cmpwi r8, 0x8
    blt L_8003DDC4
    b ksNesLinecntIrqDefault

entry ksNesStore59_c000
    lbz r8, 0x1765(r31)
    rlwinm r7, r4, 29, 28, 30
    lwz r9, 0x17f0(r31)
    and r8, r8, r7
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r9
    stw r8, 0x1690(r31)
    stw r8, 0x1694(r31)
    lhz r8, 0x1766(r31)
    clrlslwi r7, r4, 29, 3
    rlwimi r7, r4, 31, 25, 25
    addi r9, r31, 0x17fb
    and r7, r7, r8
    addi r0, r9, 0x8
L_8003DE18:
    stbu r7, 0x1(r9)
    addi r7, r7, 0x1
    cmpw r9, r0
    bne L_8003DE18
    rlwinm r7, r4, 1, 27, 27
    addi r0, r31, 0x1868
    addi r9, r31, 0x180c
    add r7, r7, r0
    addi r0, r7, 0x10
L_8003DE3C:
    lwzu r10, 0x4(r7)
    stwu r10, 0x4(r9)
    cmpw r7, r0
    bne L_8003DE3C
    b ksNesLinecntIrqDefault
   
entry ksNesStore5d_6000
    lbz r8, 0x1765(r31)
    slwi r7, r4, 1
    lwz r9, 0x17f0(r31)
    and r8, r8, r7
    subi r8, r8, 0x4
    slwi r8, r8, 13
    add r8, r8, r9
    stw r8, 0x1690(r31)
    stw r8, 0x1694(r31)
    b ksNesLinecntIrqDefault

entry ksNesStoreb8_6000
    lhz r10, 0x1766(r31)
    addi r9, r31, 0x17fc
    clrlslwi r7, r4, 28, 2
    addi r0, r9, 0x4
    and r7, r7, r10
    rlwinm r8, r4, 30, 26, 29
    and r8, r8, r10
L_8003DE94:
    stb r7, 0x0(r9)
    addi r7, r7, 0x1
    stb r8, 0x4(r9)
    addi r9, r9, 0x1
    addi r8, r8, 0x1
    cmpw r9, r0
    bne L_8003DE94
    b ksNesLinecntIrqDefault
}

// clang-format on

// address: 0x8003bfdc
// void ksNesStoreBBRAM() {}
