#include "jaudio_NES/emusound.hpp"

#define NES_CLOCK_SPEED 1789773

#define artificial_padding(lastOffset, currentOffset, typeOfLastMember) \
    u8 __##currentOffset##padding[currentOffset - lastOffset - sizeof(typeOfLastMember)]

struct NESSoundStruct2 {
    u8 _00;
    artificial_padding(0, 0x24, u8);
};
struct NESSoundStruct3 {
    u8 _00;
    artificial_padding(0, 0x18, u8);
};
struct NESSoundStruct {
    u8 _00;
    // bad padding
    union {
        u32 _04;
        struct {
            u16 _04_hi;
            u16 _04_lo;
        } _04p;
    };
    u32 _08;
    u16 _0C;
    // pad badding
    u32 _10;
    u32 _14;
    u32 _18;
    u8 _1C;
    u8 _1D;
    // bad padding
    u32 _20;
    u32 _24;
    u8 _28;
    // bad padding
    u16 _2A;
    u16 _2C;
    // bad padding
    u32 _30;
    u32 _34;
    u8 _38;
    u8 _39;
    u8 _3A;
    u8 _3B;
    u8 _3C;
    // bad padding
    u16 _3E;
    u16 _40;
    u16 _42;
    u8 _44;
    artificial_padding(0x44, 0x48, u8);
    u16 _48;
    // bad padding
}; // size 0x48

// bss
u8 PCMH2[16];
NESSoundStruct SoundA, SoundB, SoundC, SoundD;
NESSoundStruct2 SoundE;
NESSoundStruct SoundX, SoundY, SoundZ;
NESSoundStruct SoundM, SoundN, SoundF;
NESSoundStruct3 SoundP;
u32 PHASE_SYNC_FLAG;

// sdata
u32 NOISE_MASTER = 1;
u32 NOISE_SHIFT = 0x800;
u32 PHASE_SAMPLE = 0x85;
u32 FRAME_SAMPLE = 0x215;
const u64 _STOP = 0;

// sbss
s8 NOISE_PULSE;
u32 delta_counter;
s8 delta_sign;
s32 bias;
s32 bias_move;
f32 voltage;
f32 voltage_out;

// data

// UNUSED
u8 LEN_TABLE[] = { 0x05, 0x7e, 0x0a, 0x01, 0x13, 0x02, 0x28, 0x03, 0x50,  0x04, 0x1e, 0x05, 0x07, 0x06, 0x0d, 0x07,
                   0x06, 0x08, 0x0c, 0x09, 0x18, 0x0a, 0x30, 0x0b, 0x060, 0x0c, 0x24, 0x0d, 0x08, 0x0e, 0x10, 0x0f };

// UNUSED
f32 NOISE_FREQ_TABLE[] = { 4.f,  2.f,   1.f,   0.5f,  0.25f, 0.2f,  0.15f, 0.12f,
                           0.1f, 0.08f, 0.07f, 0.06f, 0.05f, 0.04f, 0.03f, 0.03f };

// https://www.nesdev.org/wiki/APU_registers

typedef struct _PulseChannel {
    // $4000/$4004
    u8 Duty : 2;
    u8 EnvelopeLoopCounter : 1;
    u8 ConstantVolume : 1;
    u8 EnvelopePeriod_Volume : 4;
    // $4001/$4005
    u8 SweepUnitEnabled : 1;
    u8 SweepUnitPeriod : 3;
    u8 SweepUnitNegative : 1;
    u8 SweepUnitShiftCount : 3;
    // $4002/$4006
    u8 TimerLow : 8;
    // $4003/$4007
    u8 LengthCounterLow : 5;
    u8 TimerHigh : 3;
} PulseChannel;

typedef struct _TriangleChannel {
    // $4008
    u8 LengthCounter : 1;
    u8 LinearCounterReloadVaue : 7;
    // $4009
    u8 _unused_4009 : 8;
    // $400A
    u8 TimerLow : 8;
    // $400B
    u8 LengthCounterLoad : 5;
    u8 TimerHigh : 3;
} TriangleChannel;

typedef struct _NoiseChannel {
    // $400C
    u8 _unused_400C_high2 : 2;
    u8 LoopEnvelope : 1;
    u8 ConstantVolume : 1;
    u8 EnvelopePeriod_Volume : 4;
    // $400D
    u8 _unused_400D : 8;
    // $400E
    u8 LoopNoise : 1;
    u8 _unused_400E_3bits : 3;
    u8 Period : 4;
    // $400F
    u8 LengthCounterLoad : 5;
    u8 _unused_400F_low3 : 3;
} NoiseChannel;

typedef struct _DMCChannel {
    // $4010
    u8 IRQEnable : 1;
    u8 LoopSample : 1;
    u8 _unused_4010_middle2 : 2;
    u8 FrequencyIndex : 4;
    // $4011
    u8 _unused_4011_heigh : 1;
    u8 DirectLoad : 7;
    // $4012
    u8 SampleAddress : 8;
    // $4013
    u8 SampleLength : 8;
} DMCChannel;

typedef struct _APURegisters {
    // $4000
    PulseChannel Pulse1;
    // $4004
    PulseChannel Pulse2;
    // $4008
    TriangleChannel Triangle;
    // $400C
    NoiseChannel Noise;
    // $4010
    DMCChannel DMC;
    // $4014
    u8 _unused_4014;
    // $4015
    u8 DMCInterrupt : 1;
    u8 FrameInterrupt : 1;
    u8 _unused_4015_1bit : 1;
    u8 LengthCounterStatus : 1;
    u8 NoiseStatus : 1;
    u8 TriangleStatus : 1;
    u8 Pulse2Status : 1;
    u8 Pulse1Status : 1;
    // $4016
    u8 _unused_4016;
    // $4017
    u8 FrameCounter_5FrameSequence : 1;
    u8 FrameCounter_DisableFrameInterrupt : 1;
    u8 _unused_4017_low : 6;

} APURegisters;

typedef struct _sbufferStruct {
    APURegisters apu;
    u8 buff[0x4100 - (0x4000 + sizeof(APURegisters))];
} sbufferStruct;

sbufferStruct sbuffer = { 0 };
#define SBUFFER ((u8*)&sbuffer)

u8 LEN_TABLE_HVC[] = { 0x05, 0x7e, 0x0a, 0x01, 0x13, 0x02, 0x28, 0x03, 0x50, 0x04, 0x1e, 0x05, 0x07, 0x06, 0x0d, 0x07,
                       0x06, 0x08, 0x0c, 0x09, 0x18, 0x0a, 0x30, 0x0b, 0x60, 0x0c, 0x24, 0x0d, 0x08, 0x0e, 0x10, 0x0f };

u8 TRIANGLE_TABLE[] = {
    0x00, 0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 0x78, 0x69, 0x5a, 0x4b, 0x3c, 0x2d, 0x1e,
    0x0f, 0x00, 0xef, 0xde, 0xcd, 0xbb, 0xaa, 0x99, 0x88, 0x88, 0x99, 0xaa, 0xbb, 0xcd, 0xde, 0xef
};

int NOISE_TABLE[] = { 0x000df86a, 0x0006fc35, 0x00037e1a, 0x0001bf0d, 0x0000df86, 0x00009504, 0x00006fc3, 0x00005969,
                      0x000046d1, 0x00003852, 0x000025a5, 0x00001c29, 0x000012c6, 0x00000e14, 0x00000708, 0x000006fd };

u8 NOISE_PULSE_TABLE[] = { 0x30, 0x32, 0x34, 0x38, 0x3c, 0x3d, 0x3e, 0x3f,
                           0x40, 0x42, 0x44, 0x46, 0x48, 0x50, 0x60, 0x60 };

u32 DMOD_TABLE[] = { 0x000010bd, 0x000012db, 0x00001513, 0x00001663, 0x0000190d, 0x00001c36, 0x00001fb4, 0x00002115,
                     0x000025b6, 0x00002cbf, 0x000032a4, 0x000037fb, 0x00004399, 0x00005475, 0x00006385, 0x000084b1 };

// UNUSED
u8 VOLTABLE_DELTAMOD[] = {
    0x00, 0x00, 0x00, 0xff, 0x01, 0xfc, 0x02, 0xf7, 0x03, 0xf0, 0x04, 0xe7, 0x05, 0xdc, 0x06, 0xcf, 0x07, 0xc0, 0x08,
    0xaf, 0x09, 0x9c, 0x0a, 0x87, 0x0b, 0x70, 0x0c, 0x57, 0x0d, 0x3c, 0x0e, 0x1f, 0x0f, 0x00, 0x0f, 0xdf, 0x10, 0xbc,
    0x11, 0x97, 0x12, 0x70, 0x13, 0x47, 0x14, 0x1c, 0x14, 0xef, 0x15, 0xc0, 0x16, 0x8f, 0x17, 0x5c, 0x18, 0x27, 0x18,
    0xf0, 0x19, 0xb7, 0x1a, 0x7c, 0x1b, 0x3f, 0x1c, 0x00, 0x1c, 0xbf, 0x1d, 0x7c, 0x1e, 0x37, 0x1e, 0xf0, 0x1f, 0xa7,
    0x20, 0x5c, 0x21, 0x0f, 0x21, 0xc0, 0x22, 0x6f, 0x23, 0x1c, 0x23, 0xc7, 0x24, 0x70, 0x25, 0x17, 0x25, 0xbc, 0x26,
    0x5f, 0x27, 0x00, 0x27, 0x9f, 0x28, 0x3c, 0x28, 0xd7, 0x29, 0x70, 0x2a, 0x07, 0x2a, 0x9c, 0x2b, 0x2f, 0x2b, 0xc0,
    0x2c, 0x4f, 0x2c, 0xdc, 0x2d, 0x67, 0x2d, 0xf0, 0x2e, 0x77, 0x2e, 0xfc, 0x2f, 0x7f, 0x30, 0x00, 0x30, 0x7f, 0x30,
    0xfc, 0x31, 0x77, 0x31, 0xf0, 0x32, 0x67, 0x32, 0xdc, 0x33, 0x4f, 0x33, 0xc0, 0x34, 0x2f, 0x34, 0x9c, 0x35, 0x07,
    0x35, 0x70, 0x35, 0xd7, 0x36, 0x3c, 0x36, 0x9f, 0x37, 0x00, 0x37, 0x5f, 0x37, 0xbc, 0x38, 0x17, 0x38, 0x70, 0x38,
    0xc7, 0x39, 0x1c, 0x39, 0x6f, 0x39, 0xc0, 0x3a, 0x0f, 0x3a, 0x5c, 0x3a, 0xa7, 0x3a, 0xf0, 0x3b, 0x37, 0x3b, 0x7c,
    0x3b, 0xbf, 0x3c, 0x00, 0x3c, 0x3f, 0x3c, 0x7c, 0x3c, 0xb7, 0x3c, 0xf0, 0x3d, 0x27, 0x3d, 0x5c, 0x3d, 0x8f, 0x3d,
    0xc0, 0x3d, 0xef, 0x3e, 0x1c, 0x3e, 0x47, 0x3e, 0x70, 0x3e, 0x97, 0x3e, 0xbc, 0x3e, 0xdf, 0x3f, 0x00, 0x3f, 0x1f,
    0x3f, 0x3c, 0x3f, 0x57, 0x3f, 0x70, 0x3f, 0x87, 0x3f, 0x9c, 0x3f, 0xaf, 0x3f, 0xc0, 0x3f, 0xcf, 0x3f, 0xdc, 0x3f,
    0xe7, 0x3f, 0xf0, 0x3f, 0xf7, 0x3f, 0xfc, 0x3f, 0xff
};

// UNUSED
u8 VOLTABLE_DISKFM[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e, 0x10,
                         0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26,
                         0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c };

// UNUSED
u8 VOLTABLE_DISKFM_SUB[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a,
                             0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
                             0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20 };

// UNUSED
u32 DISKFM_GAINTABLE[] = { 30, 20, 15, 12 };

// UNUSED
u32 DEB1[4] = { 0, 0, 0, 0 };

f32 VOLTABLE_HVCPULSE[] = { 0.0f,      0.080128,  0.157051f, 0.224359f, 0.294872f, 0.365385f,
                            0.435897f, 0.50641f,  0.592949f, 0.657051f, 0.730769f, 0.801282f,
                            0.865385f, 0.929487f, 0.99359f,  1.064103f, 1.064103f };

u8 VOLTABLE_VRCPULSE[] = { 0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e, 0x10, 0x12, 0x14,
                           0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25,
                           0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f };

// UNUSED
void* PCM[9] = { (void*)&_STOP, (void*)&_STOP, NULL, NULL, NULL, NULL, NULL, NULL, NULL };

// UNUSED
u32 PCMSIZE[9] = { sizeof(_STOP), sizeof(_STOP), 0, 0, 0, 0, 0, 0, 0 };

s32 __GetWave_Pulse(s32 a, s32 b) {
    switch (a) {

        case 0:
            if (b >= 4 && b <= 7) {
                return 1;
            } else {
                return 0;
            }
        case 1:
            return b <= 7;
        case 2:
            return b <= 15;
        case 3:
            return b > 7;
        case 0xb:
            return b & 0xff;
        case 0xc:
            return b <= 0 ? 127 : 0;
        case 0xd:
            return b <= 1 ? 127 : 0;
        case 0xe:
            return b <= 2 ? 127 : 0;
        case 0xf:
            return b <= 3 ? 127 : 0;
        case 0x10:
            return b <= 4 ? 127 : 0;
        case 0x11:
            return b <= 5 ? 0 : 127;
        case 0x12:
            return b <= 6 ? 0 : 127;
        case 0x13:
            return b <= 7 ? 0 : 127;
    }
    return a;
}

u32 __PitchTo32_VRC_C(u16 pitch) {
    f32 scalefactor = 2.f;
    return (u32)((NES_CLOCK_SPEED - 0.25f) / scalefactor / (pitch + 1) / 1000.875f * 32768.f);
}

u32 __PitchTo32_VRC_PULSE(u16 pitch) {
    f32 scalefactor = 16.f;
    return (u32)((NES_CLOCK_SPEED - 0.25f) / scalefactor / (pitch + 1) / 1000.875f * 32768.f);
}

u32 __PitchTo32_HVC(u16 pitch) {
    f32 scalefactor = 8.f;
    return (u32)((NES_CLOCK_SPEED - 0.25f) / scalefactor / (pitch + 1) / 1000.875f * 32768.f);
}

void __Sound_Write_VRC(u16 a, u8 b) {
    NESSoundStruct* pSound;
    u8* pBuffer;
    int v;
    int xyzIndex;

    u16 index = a - 0xc0;
    if (index <= 3) {
        pSound = &SoundX;
        xyzIndex = 0;
        pBuffer = &SBUFFER[192];
    } else if (index <= 7) {
        pSound = &SoundY;
        xyzIndex = 1;
        pBuffer = &SBUFFER[196];
    } else {
        pSound = &SoundZ;
        xyzIndex = 2;
        pBuffer = &SBUFFER[200];
    }

    if (index == 21) {
        if (!(b & 1)) {
            SoundX._00 = 0;
        }
        if (!(b & 2)) {
            SoundY._00 = 0;
        }
        if (!(b & 4)) {
            SoundZ._00 = 0;
        }
        return;
    }

    switch (index & 3) {
        case 0:
            pSound->_3C = pBuffer[0] >> 4 & 7;
            pSound->_28 = pBuffer[0] >> 7 & 1;
            pSound->_1C = VOLTABLE_VRCPULSE[pBuffer[0] & 0xf];
            pSound->_1D = pBuffer[0] & 0xf;
            pSound->_2A = pSound->_1D;
            if (xyzIndex == 2) {
                pSound->_24 = ((pSound->_3C & 3) << 4) | pSound->_2A;
                pSound->_1C = (pSound->_24 * 7) / 3;
                if (pSound->_1C >= 0x7f) {
                    pSound->_1C = 0x7f;
                }
            }
            break;
        case 2:
            pSound->_0C = ((pBuffer[3] & 0xf) << 8) | pBuffer[2];
            if (xyzIndex == 2) {
                pSound->_08 = __PitchTo32_VRC_C(pSound->_0C);
            } else {
                pSound->_08 = __PitchTo32_VRC_PULSE(pSound->_0C);
            }
            break;
        case 3:
            pSound->_0C = ((pBuffer[3] & 0xf) << 8) | pBuffer[2];
            if (xyzIndex == 2) {
                pSound->_08 = __PitchTo32_VRC_C(pSound->_0C);
            } else {
                pSound->_08 = __PitchTo32_VRC_PULSE(pSound->_0C);
            }

            if (!pSound->_00 && !pSound->_3E) {
                pSound->_04 = 0;
            }

            if (xyzIndex == 0) {
                v = SBUFFER[213] & 1;
            }
            if (xyzIndex == 1) {
                v = SBUFFER[213] >> 1 & 1;
            }
            if (xyzIndex == 2) {
                v = SBUFFER[213] >> 2 & 1;
            }

            if ((u8)v == 1 && (pBuffer[3] >> 7) & 1) {
                pSound->_00 = 1;
            } else {
                pSound->_00 = 0;
            }

            pSound->_2A = pSound->_1D;
            pSound->_20 = 0;

            break;
    }
}

void __Sound_Write_MMC5(u16 a, u8 b) {
    NESSoundStruct* pSound;
    u8* pBuffer;
    u32 v;
    int xyzIndex;

    u16 index = a - 0xc0;
    pBuffer = 0;
    if (index <= 3) {
        pSound = &SoundX;
        xyzIndex = 0;
        pBuffer = &SBUFFER[192];
    } else if (index <= 7) {
        pSound = &SoundY;
        xyzIndex = 1;
        pBuffer = &SBUFFER[196];
    }

    if (index == 17) {
        SoundZ._3E = (b << 6) & 0x3fc0;
    } else if (index == 21) {
        if (!(b & 1)) {
            SoundX._00 = 0;
        }
        if (!(b & 2)) {
            SoundY._00 = 0;
        }
    } else if (pBuffer) {
        switch (index & 3) {
            case 0: {
                pSound->_3C = (pBuffer[0] >> 6) & 0x3;
                v = pSound->_28;
                pSound->_28 = (pBuffer[0] >> 4 & 1) ^ 1;
                pSound->_14 = (pBuffer[0] >> 5 & 1);
                pSound->_1D = VOLTABLE_HVCPULSE[pBuffer[0] & 0xf];
                if (pSound->_28 == 0 && pSound->_00 == 1) {
                    pSound->_1C = VOLTABLE_HVCPULSE[pBuffer[0] & 0xf];
                } else {
                    pSound->_24 = PHASE_SAMPLE * ((pBuffer[0] & 0xf) + 1);
                    if (v == 0) {
                        pSound->_2A = 0xf;
                        pSound->_20 = 0;
                    }
                }
            } break;
            case 2:
                pSound->_0C = ((pBuffer[3] & 0x7) << 8) | pBuffer[2];
                pSound->_08 = __PitchTo32_HVC_C(pSound->_0C);
                break;
            case 3: {
                pSound->_0C = ((pBuffer[3] & 0x7) << 8) | pBuffer[2];
                pSound->_08 = __PitchTo32_HVC_C(pSound->_0C);
                pSound->_18 = LEN_TABLE_HVC[(pBuffer[3] >> 3) & 0x1f];
                pSound->_10 = FRAME_SAMPLE * pSound->_18;
                if (!pSound->_00 && !pSound->_3E) {
                    pSound->_04 = 0;
                }

                if (xyzIndex == 0) {
                    v = SBUFFER[213] & 1;
                }
                if (xyzIndex == 1) {
                    v = SBUFFER[213] >> 1 & 1;
                }

                if ((v & 0xff) != 0) {
                    pSound->_00 = 1;
                }

                if ((pBuffer[0] >> 4 & 1) == 0) {
                    pSound->_1C = VOLTABLE_HVCPULSE[15];
                } else {
                    pSound->_1C = pSound->_1D;
                }

                pSound->_2A = 0xf;
                pSound->_20 = 0;
                pSound->_30 = 0;
                pSound->_3A = 0;
            } break;
        }
    }
}

void __Sound_Write_A(u16 a, u8 b) {
    switch (a) {
        case 0: {
            SoundA._3C = sbuffer.apu.Pulse1.Duty;
            u32 v = SoundA._28;
            SoundA._28 = sbuffer.apu.Pulse1.ConstantVolume ^ 1;
            SoundA._14 = sbuffer.apu.Pulse1.EnvelopeLoopCounter;
            if (!SoundA._28) {
                SoundA._2C = sbuffer.apu.Pulse1.EnvelopePeriod_Volume << 8;
            } else {
                SoundA._24 = sbuffer.apu.Pulse1.EnvelopePeriod_Volume + 1;
                if (!v && SoundA._00) {
                    SoundA._2C = 0xf00;
                    SoundA._20 = 0;
                }
            }
        } break;
        case 1: {
            SoundA._34 = (sbuffer.apu.Pulse1.SweepUnitPeriod + 1) << 1;
            SoundA._39 = sbuffer.apu.Pulse1.SweepUnitNegative;
            SoundA._38 = sbuffer.apu.Pulse1.SweepUnitShiftCount;
            SoundA._30 = 0;
            SoundA._3B = 0;
            SoundA._3A = sbuffer.apu.Pulse1.SweepUnitEnabled;
        } break;
        case 2: {
            SoundA._0C = SoundA._0C & 0xf00 | sbuffer.apu.Pulse1.TimerLow;
            SoundA._08 = __PitchTo32_HVC(SoundA._0C);
        } break;
        case 3: {
            SoundA._0C = (sbuffer.apu.Pulse1.TimerHigh << 8) | sbuffer.apu.Pulse1.TimerLow;
            SoundA._08 = __PitchTo32_HVC(SoundA._0C);
            SoundA._18 = LEN_TABLE_HVC[sbuffer.apu.Pulse1.LengthCounterLow];
            SoundA._10 = SoundA._18 << 2;
            SoundA._04 = 0;
            SoundA._48 = 0;
            SoundA._3E = 0;
            SoundA._2A = 0;
            if (sbuffer.apu.Pulse1Status) {
                SoundA._00 = 1;
            }
            if (!sbuffer.apu.Pulse1.ConstantVolume) {
                SoundA._2C = 0xf00;
            } else {
                SoundA._2C = sbuffer.apu.Pulse1.EnvelopePeriod_Volume << 8;
            }
            SoundA._20 = 0;
            SoundA._30 = 0;
            SoundA._3B = 0;
            SoundA._3A = sbuffer.apu.Pulse1.SweepUnitEnabled;
        } break;
    }
}

s16 __ProcessSoundA() {
    if (SoundA._3A) {
        if (PHASE_SYNC_FLAG) {
            SoundA._30++;
            if (SoundA._30 % SoundA._34 == 0) {
                SoundA._3B |= 1;
            }
        }

        if (SoundA._3B == 3) {
            SoundA._3B = 0;
            u32 c = SoundA._0C;
            u16 j = SoundA._0C >> SoundA._38;
            if (!SoundA._38) {
                j = 0;
            }
            switch (SoundA._39) {
                case 0:
                    SoundA._0C = SoundA._0C + j;
                    break;
                case 1:
                    if (!SoundA._38) {
                        j = 0;
                    }
                    j = SoundA._0C - j;
                    SoundA._0C = j;
                    if (j && SoundA._38) {
                        SoundA._0C--;
                    }
            }
            if (SoundA._0C >= 0x800) {
                SoundA._0C = 0x800;
            } else {
                SoundA._08 = __PitchTo32_HVC(SoundA._0C);
            }
        }
    }

    if (!SoundA._00 && !SoundA._3E) {
        return 0;
    }

    if (SoundA._28 && PHASE_SYNC_FLAG) {
        SoundA._20++;
        if ((SoundA._20 % SoundA._24) == 0) {
            switch (SoundA._14) {
                case 0:
                    if (SoundA._2C) {
                        SoundA._2C -= 0x100;
                    } else {
                        SoundA._00 = 0;
                    }
                    break;
                case 1:
                    if (SoundA._2C) {
                        SoundA._2C -= 0x100;
                    } else {
                        SoundA._2C = 0xf00;
                    }
                    break;
            }
        }
    }

    if (SoundA._14 == 0) {
        if (PHASE_SYNC_FLAG && SoundA._10) {
            SoundA._10--;
        }
        if (SoundA._10 == 0) {
            SoundA._00 = 0;
        }
    }

    if (SoundA._0C <= 7) {
        SoundA._44 = 1;
    } else if (SoundA._0C >= 0x800) {
        SoundA._44 = 1;
    } else {
        SoundA._44 = 0;
    }

    s8 c = __GetWave_Pulse(SoundA._3C, SoundA._04p._04_hi);

    if (SoundA._44) {
        SoundA._04 += SoundA._40;
    } else {
        SoundA._04 += SoundA._08;
        SoundA._40 = SoundA._08;
    }

    if (SoundA._04 & 0xffe00000) {
        SoundA._3B |= 2;
    }

    SoundA._04 &= 0x1fffff;
    if (SoundA._44 == 1 || !SoundA._00) {
        if (SoundA._3E) {
            SoundA._3E--;
        }
    } else {
        if (SoundA._3E < 0x20) {
            SoundA._3E++;
        }
        if (SoundA._3E < 0x20) {
            SoundA._3E++;
        }
    }

    u32 _2a_6 = SoundA._2A >> 8 & 0xff;
    f32 f_2a = (SoundA._2A & 0xff) / 256.f;
    f32 param0 = VOLTABLE_HVCPULSE[_2a_6];
    f32 param1 = VOLTABLE_HVCPULSE[_2a_6 + 1];
    f32 f_sum = param0 * (1.f - f_2a) + param1 * f_2a;

    if (SoundA._2A != SoundA._2C) {
        if (SoundA._2A > SoundA._2C) {
            u16 diff = (SoundA._2A - SoundA._2C) >> 4;
            if (!diff) {
                SoundA._2A = SoundA._2C;
            } else {
                SoundA._2A -= diff;
            }
        } else if (SoundA._2A < SoundA._2C) {
            u16 diff = (SoundA._2C - SoundA._2A) >> 4;
            if (!diff) {
                SoundA._2A = SoundA._2C;
            } else {
                SoundA._2A += diff;
            }
        }
    }

    switch (c) {
        case 0:
            // almost 1. / 15.6
            f_sum = -0.064103;
            break;
        case 1:
            f_sum = -0.064103 + f_sum;
            break;
    }

    s16 t = f_sum * 4096.f;

    t = (t * SoundA._3E) >> 5;
    return t;
}

void __Sound_Write_B(u16 a, u8 b) {
    a -= 4;
    switch (a) {
        case 0: {
            SoundB._3C = sbuffer.apu.Pulse2.Duty;
            u32 v = SoundB._28;
            SoundB._28 = sbuffer.apu.Pulse2.ConstantVolume ^ 1;
            SoundB._14 = sbuffer.apu.Pulse2.EnvelopeLoopCounter;
            if (!SoundB._28) {
                SoundB._2C = sbuffer.apu.Pulse2.EnvelopePeriod_Volume << 8;
            } else {
                SoundB._24 = sbuffer.apu.Pulse2.EnvelopePeriod_Volume + 1;
                if (!v && SoundB._00) {
                    SoundB._2C = 0xf00;
                    SoundB._20 = 0;
                }
            }
        } break;
        case 1: {
            SoundB._34 = (sbuffer.apu.Pulse2.SweepUnitPeriod + 1) << 1;
            SoundB._39 = sbuffer.apu.Pulse2.SweepUnitNegative;
            SoundB._38 = sbuffer.apu.Pulse2.SweepUnitShiftCount;
            SoundB._30 = 0;
            SoundB._3B = 0;
            SoundB._3A = sbuffer.apu.Pulse2.SweepUnitEnabled;
        } break;
        case 2: {
            SoundB._0C = SoundB._0C & 0xf00 | sbuffer.apu.Pulse2.TimerLow;
            SoundB._08 = __PitchTo32_HVC(SoundB._0C);
        } break;
        case 3: {
            SoundB._0C = (sbuffer.apu.Pulse2.TimerHigh << 8) | sbuffer.apu.Pulse2.TimerLow;
            SoundB._08 = __PitchTo32_HVC(SoundB._0C);
            SoundB._18 = LEN_TABLE_HVC[sbuffer.apu.Pulse2.LengthCounterLow];
            SoundB._10 = SoundB._18 << 2;
            SoundB._04 = 0;
            SoundB._48 = 0;
            SoundB._3E = 0;
            SoundB._2A = 0;
            if (sbuffer.apu.Pulse2Status) {
                SoundB._00 = 1;
            }
            if (!sbuffer.apu.Pulse2.ConstantVolume) {
                SoundB._2C = 0xf00;
            } else {
                SoundB._2C = sbuffer.apu.Pulse2.EnvelopePeriod_Volume << 8;
            }
            SoundB._20 = 0;
            SoundB._30 = 0;
            SoundB._3B = 0;
            SoundB._3A = sbuffer.apu.Pulse2.SweepUnitEnabled;
        } break;
    }
}

s16 __ProcessSoundB() {
    if (SoundB._3A) {
        if (PHASE_SYNC_FLAG) {
            SoundB._30++;
            if (SoundB._30 % SoundB._34 == 0) {
                SoundB._3B |= 1;
            }
        }

        if (SoundB._3B == 3) {
            SoundB._3B = 0;
            u32 c = SoundB._0C;
            u16 j = SoundB._0C >> SoundB._38;
            if (!SoundB._38) {
                j = 0;
            }
            switch (SoundB._39) {
                case 0:
                    SoundB._0C = SoundB._0C + j;
                    break;
                case 1:
                    if (!SoundB._38) {
                        j = 0;
                    }

                    SoundB._0C = SoundB._0C - j;
            }
            if (SoundB._0C >= 0x800) {
                SoundB._0C = 0x800;
            } else {
                SoundB._08 = __PitchTo32_HVC(SoundB._0C);
            }
        }
    }

    if (!SoundB._00 && !SoundB._3E) {
        return 0;
    }

    if (SoundB._28 && PHASE_SYNC_FLAG) {
        SoundB._20++;
        if ((SoundB._20 % SoundB._24) == 0) {
            switch (SoundB._14) {
                case 0:
                    if (SoundB._2C) {
                        SoundB._2C -= 0x100;
                    } else {
                        SoundB._00 = 0;
                    }
                    break;
                case 1:
                    if (SoundB._2C) {
                        SoundB._2C -= 0x100;
                    } else {
                        SoundB._2C = 0xf00;
                    }
                    break;
            }
        }
    }

    if (SoundB._14 == 0) {
        if (PHASE_SYNC_FLAG && SoundB._10) {
            SoundB._10--;
        }
        if (SoundB._10 == 0) {
            SoundB._00 = 0;
        }
    }

    if (SoundB._0C <= 7) {
        SoundB._44 = 1;
    } else if (SoundB._0C >= 0x800) {
        SoundB._44 = 1;
    } else {
        SoundB._44 = 0;
    }

    s8 c = __GetWave_Pulse(SoundB._3C, SoundB._04p._04_hi);

    if (SoundB._44) {
        SoundB._04 += SoundB._40;
    } else {
        SoundB._04 += SoundB._08;
        SoundB._40 = SoundB._08;
    }

    if (SoundB._04 & 0xffe00000) {
        SoundB._3B |= 2;
    }

    SoundB._04 &= 0x1fffff;
    if (SoundB._44 == 1 || !SoundB._00) {
        if (SoundB._3E) {
            SoundB._3E--;
        }
    } else {
        if (SoundB._3E < 0x20) {
            SoundB._3E++;
        }
        if (SoundB._3E < 0x20) {
            SoundB._3E++;
        }
    }

    u32 _2a_6 = SoundB._2A >> 8 & 0xff;
    f32 f_2a = (SoundB._2A & 0xff) / 256.f;
    f32 param0 = VOLTABLE_HVCPULSE[_2a_6];
    f32 param1 = VOLTABLE_HVCPULSE[_2a_6 + 1];
    f32 f_sum = param0 * (1.f - f_2a) + param1 * f_2a;

    if (SoundB._2A != SoundB._2C) {
        if (SoundB._2A > SoundB._2C) {
            u16 diff = (SoundB._2A - SoundB._2C) >> 4;
            if (!diff) {
                SoundB._2A = SoundB._2C;
            } else {
                SoundB._2A -= diff;
            }
        } else if (SoundB._2A < SoundB._2C) {
            u16 diff = (SoundB._2C - SoundB._2A) >> 4;
            if (!diff) {
                SoundB._2A = SoundB._2C;
            } else {
                SoundB._2A += diff;
            }
        }
    }

    switch (c) {
        case 0:
            // almost 1. / 15.6
            f_sum = -0.064103;
            break;
        case 1:
            f_sum = -0.064103 + f_sum;
            break;
    }

    s16 t = f_sum * 4096.f;

    t = (t * SoundB._3E) >> 5;
    return t;
}

int __PitchTo32_HVC_D(u16 a) {
    return NOISE_TABLE[a];
}

void __Sound_Write_D(u16 a, u8 b) {
    switch (a) {
        case 0xc:
            u32 v = SoundD._28;
            SoundD._28 = sbuffer.apu.Noise.ConstantVolume ^ 1;
            SoundD._14 = sbuffer.apu.Noise.LoopEnvelope;
            SoundD._1D = (u8)(16.f * VOLTABLE_HVCPULSE[sbuffer.apu.Noise.EnvelopePeriod_Volume]);
            if (!SoundD._28) {
                SoundD._1C = SoundD._1D;
            } else {
                SoundD._24 = sbuffer.apu.Noise.EnvelopePeriod_Volume + 1;
                if (!v) {
                    SoundD._2A = 0xf;
                    SoundD._20 = 0;
                }
            }
            break;
        case 0xe:
            SoundD._0C = sbuffer.apu.Noise.Period;
            if (sbuffer.apu.Noise.LoopNoise == 1u) {
                SoundD._0C += 0x10;
                NOISE_SHIFT = 0x40;
                NOISE_MASTER = 1;
            } else {

                NOISE_SHIFT = 0x4000;
            }
            NOISE_PULSE = NOISE_PULSE_TABLE[SoundD._0C & 0xf];
            SoundD._08 = __PitchTo32_HVC_D(SoundD._0C & 0xf);
            break;
        case 0xf:
            SoundD._0C = sbuffer.apu.Noise.Period;
            if (sbuffer.apu.Noise.LoopNoise == 1u) {
                SoundD._0C += 0x10;
                NOISE_SHIFT = 0x40;
                NOISE_MASTER = 1;
            } else {
                NOISE_SHIFT = 0x4000;
            }
            NOISE_PULSE = NOISE_PULSE_TABLE[SoundD._0C % 16u];
            SoundD._08 = __PitchTo32_HVC_D(SoundD._0C % 16u);
            SoundD._18 = LEN_TABLE_HVC[sbuffer.apu.Noise.LengthCounterLoad];
            SoundD._10 = SoundD._18 * 4;
            if (sbuffer.apu.NoiseStatus != 0) {
                SoundD._00 = '\x01';
            }
            if (sbuffer.apu.Noise.ConstantVolume == 0) {
                SoundD._1C = (u8)(16.f * VOLTABLE_HVCPULSE[15]);
            } else {
                SoundD._1C = SoundD._1D;
            }
            SoundD._2A = 0xf;
            SoundD._20 = 0;
            break;
    }
}

s8 __GetNoise(u32 a) {
    static u8 data = 0;

    for (int i = 0; i < a >> 16; i++) {
        data = NOISE_MASTER & 3;
        switch (data) {
            case 0:
            case 3:
                NOISE_MASTER = (NOISE_MASTER >> 1) | NOISE_SHIFT;
                break;
            case 1:
            case 2:
                NOISE_MASTER >>= 1;
        }
    }

    if (NOISE_MASTER & 1) {
        return (s32)NOISE_PULSE;
    } else {
        return -(s32)NOISE_PULSE;
    }
}

s16 __ProcessSoundD() {
    s16 ret;
    if (!SoundD._00) {
        if (!SoundD._3E) {
            return 0;
        }
        SoundD._3E--;
        SoundD._1C = SoundD._3E;
    }
    SoundD._04 += SoundD._08;
    __GetNoise(SoundD._04);
    SoundD._04 &= 0xffff;
    SoundD._3E = SoundD._1C;

    if (!SoundD._14) {
        if (PHASE_SYNC_FLAG && SoundD._10) {
            SoundD._10--;
        }
        if (!SoundD._10) {
            SoundD._00 = 0;
        }
    }
    return ret;
}

void MoveDeltaCounter(u8 a) {
    if (a) {
        delta_counter++;
        delta_sign++;
    } else {
        delta_counter--;
        delta_sign--;
    }
}

void MoveBias() {
    s32 oldBias = bias;
    bias += delta_sign * 2;
    if (bias > 0x7f) {
        bias = 0x7f;
    }
    if (bias < 0) {
        bias = 0;
    }
    bias_move += bias - oldBias;
    delta_sign = 0;
}

void WriteBias(u16 a) {
    bias_move = (s16)a - (s16)bias;
    bias = (a & 0xffff);
}

int MoveVoltage() {
    voltage = 0.9994586f * voltage;
    voltage += bias_move;
    bias_move = 0;
    if (voltage > 127.f) {
        voltage = 127.f;
    }
    if (voltage < -127.f) {
        voltage = -127.f;
    }
    voltage_out += (voltage - voltage_out) / 4.f;

    return (int)(216.f * voltage_out);
}

u32 __PitchTo32_HVC_E(u16 a) {
    return DMOD_TABLE[a];
}

void __Sound_Write_E(u16, u8) {
}

void StartE() {
}
void __ProcessSoundE() {
}

u8 __GetWave_Triangle(s32 a) {
    return TRIANGLE_TABLE[a];
}

u32 __PitchTo32_HVC_C(u16 a) {
    u32 pitch;
    if (a == 0) {
        return 0;
    } else {
        f32 scalefactor = 16.f;
        return (u32)((NES_CLOCK_SPEED - 0.25f) / scalefactor / (a + 1) / 1000.875f * 32768.f);
    }
}

void __Sound_Write_C(u16, u8) {
}
void __ProcessSoundC() {
}
void __CreateDiskSubWave() {
}
void __PitchTo32_DISKFM(u16) {
}
void __Sound_Write_Disk(u16, u8) {
}
void HS_Event_Reset() {
}
void HS_Event_Update() {
}
void HS_Event_Write(u16, u8) {
}
void ProcessPhaseCounter() {
}
void ForceProcessPhaseCounter() {
}
void Sound_Make_HVC(s32, s16*) {
}
void Buffer_Reset() {
}
void Sample_Copy(u16, s16*) {
}
void Sound_Write(u16 event, u8 value, u16 maybe_frames) {
}
void Sound_Reset() {
}
void __FrameCallback(s32) {
}
void EmuSound_Start(u8* noise_data) {
}
void EmuSound_Exit() {
}
void Sound_Read() {
}
void Sound_SetC000() {
}
void Sound_SetE000() {
}
void Sound_SetMMC() {
}
void Sound_PlayMENUPCM() {
}
void __Sound_Write_HVC(u16, u8) {
}
