#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>
#include <dolphin/si.h>
#include <dolphin/hw_regs.h>

#include "__gx.h"
#include "__os.h"
#include "__vi.h"

#define VI_DISPLAY_PIX_SZ 2
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(low, high, value) ((value) > (high) ? (high) : (value) < (low) ? (low) : (value))

// Structure to use with timing in vi.c (size 0x28).
typedef struct VITimingInfo
{
    u8 equ;           // _00
    u16 acv;          // _02
    u16 prbOdd;       // _04
    u16 prbEven;      // _06
    u16 psbOdd;       // _08
    u16 psbEven;      // _0A
    u8 bs1;           // _0C
    u8 bs2;           // _0D
    u8 bs3;           // _0E
    u8 bs4;           // _0F
    u16 be1;          // _10
    u16 be2;          // _12
    u16 be3;          // _14
    u16 be4;          // _16
    u16 numHalfLines; // _18
    u16 hlw;          // _1A
    u8 hsy;           // _1C
    u8 hcs;           // _1D
    u8 hce;           // _1E
    u8 hbe640;        // _1F
    u16 hbs640;       // _20
    u8 hbeCCIR656;    // _24
    u16 hbsCCIR656;   // _26
} VITimingInfo;

// Structure to use with HorVer in vi.c (size 0x58).
typedef struct VIPositionInfo
{
    u16 dispPosX;         // _00
    u16 dispPosY;         // _02
    u16 dispSizeX;        // _04
    u16 dispSizeY;        // _06
    u16 adjDispPosX;      // _08
    u16 adjDispPosY;      // _0A
    u16 adjDispSizeY;     // _0C
    u16 adjPanPosY;       // _0E
    u16 adjPanSizeY;      // _10
    u16 fbSizeX;          // _12
    u16 fbSizeY;          // _14
    u16 panPosX;          // _16
    u16 panPosY;          // _18
    u16 panSizeX;         // _1A
    u16 panSizeY;         // _1C
    VIXFBMode xfbMode;    // _20
    u32 nonInter;         // _24
    u32 tv;               // _28
    u8 wordPerLine;       // _2C
    u8 std;               // _2D
    u8 wpl;               // _2E
    u32 bufAddr;          // _30
    u32 tfbb;             // _34
    u32 bfbb;             // _38
    u8 xof;               // _3C
    BOOL isBlack;         // _40
    BOOL is3D;            // _44
    u32 rbufAddr;         // _48
    u32 rtfbb;            // _4C
    u32 rbfbb;            // _50
    VITimingInfo* timing; // _54
} VIPositionInfo;

typedef void (*VIPositionCallback)(s16 x, s16 y);

// Useful macros.
#define IS_LOWER_16MB(x)  ((x) < 16 * 1024 * 1024)
#define ToPhysical(fb)    (u32)(((u32)(fb)) & 0x3FFFFFFF)
#define ONES(x)           ((1 << (x)) - 1)
#define VI_BITMASK(index) (1ull << (63 - (index)))

const char* __VIVersion = "<< Dolphin SDK - VI\trelease build: Apr 17 2003 12:33:22 (0x2301) >>";

static BOOL IsInitialized;
static vu32 retraceCount;
static u32 flushFlag;
static OSThreadQueue retraceQueue;
static VIRetraceCallback PreCB;
static VIRetraceCallback PostCB;
static VIPositionCallback PositionCallback;
static u32 encoderType;

static s16 displayOffsetH;
static s16 displayOffsetV;

static vu32 changeMode;
static vu64 changed;

static vu32 shdwChangeMode;
static vu64 shdwChanged;

static VITimingInfo* CurrTiming;
static u32 CurrTvMode;

static u32 NextBufAddr;
static u32 CurrBufAddr;

static u32 FBSet;

static vu16 regs[59];
static vu16 shdwRegs[59];

static VIPositionInfo HorVer;
// clang-format off
static VITimingInfo timing[10] = {
    { // NTSC INT
        6, 240, 24, 25, 3, 2, 12, 13, 12, 13, 520, 519, 520, 519, 525, 429, 64, 71, 105, 162, 373, 122, 412,
    },
    { // NTSC DS
        6, 240, 24, 24, 4, 4, 12, 12, 12, 12, 520, 520, 520, 520, 526, 429, 64, 71, 105, 162, 373, 122, 412,
    },
    { // PAL INT
        5, 287, 35, 36, 1, 0, 13, 12, 11, 10, 619, 618, 617, 620, 625, 432, 64, 75, 106, 172, 380, 133, 420,
    },
    { // PAL DS
        5, 287, 33, 33, 2, 2, 13, 11, 13, 11, 619, 621, 619, 621, 624, 432, 64, 75, 106, 172, 380, 133, 420,
    },
    { // MPAL INT
        6, 240, 24, 25, 3, 2, 16, 15, 14, 13, 518, 517, 516, 519, 525, 429, 64, 78, 112, 162, 373, 122, 412,
    },
    { // MPAL DS
        6, 240, 24, 24, 4, 4, 16, 14, 16, 14, 518, 520, 518, 520, 526, 429, 64, 78, 112, 162, 373, 122, 412,
    },
    { // NTSC PRO
        12, 480, 48, 48, 6, 6, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 162, 373, 122, 412,
    },
    { // NTSC 3D
        12, 480, 44, 44, 10, 10, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 168, 379, 122, 412,
    },
    { // GCA INT
        6, 241, 24, 25, 1, 0, 12, 13, 12, 13, 520, 519, 520, 519, 525, 429, 64, 71, 105, 159, 370, 122, 412,
    },
    { // GCA DS
        12, 480, 48, 48, 6, 6, 24, 24, 24, 24, 1038, 1038, 1038, 1038, 1050, 429, 64, 71, 105, 180, 391, 122, 412,
    },
};
// clang-format on

static u16 taps[25] = { 496, 476, 430, 372, 297, 219, 142, 70, 12, 226, 203, 192, 196, 207, 222, 236, 252, 8, 15, 19, 19, 15, 12, 8, 1 };

// forward declaring statics
static u32 getCurrentFieldEvenOdd();

static void getEncoderType(void)
{
    // UNUSED FUNCTION
}

static int cntlzd(u64 bit)
{
    u32 hi, lo;
    int value;

    hi    = (u32)(bit >> 32);
    lo    = (u32)(bit & 0xFFFFFFFF);
    value = __cntlzw(hi);

    if (value < 32) {
        return value;
    }

    return (32 + __cntlzw(lo));
}

static BOOL VISetRegs(void)
{
    int regIndex;

    if (!((shdwChangeMode == 1) && (getCurrentFieldEvenOdd() == 0))) {
        while (shdwChanged) {
            regIndex           = cntlzd(shdwChanged);
            __VIRegs[regIndex] = shdwRegs[regIndex];
            shdwChanged &= ~(VI_BITMASK(regIndex));
        }

        shdwChangeMode = 0;
        CurrTiming     = HorVer.timing;
        CurrTvMode     = HorVer.tv;
        CurrBufAddr    = NextBufAddr;

        return TRUE;
    }
    return FALSE;
}

static void __VIRetraceHandler(__OSInterrupt interrupt, OSContext* context)
{
    OSContext exceptionContext;
    u16 viReg;
    u32 inter = 0;

    viReg = __VIRegs[VI_DISP_INT_0];
    if (viReg & 0x8000) {
        __VIRegs[VI_DISP_INT_0] = (u16)(viReg & ~0x8000);
        inter |= 1;
    }

    viReg = __VIRegs[VI_DISP_INT_1];
    if (viReg & 0x8000) {
        __VIRegs[VI_DISP_INT_1] = (u16)(viReg & ~0x8000);
        inter |= 2;
    }

    viReg = __VIRegs[VI_DISP_INT_2];
    if (viReg & 0x8000) {
        __VIRegs[VI_DISP_INT_2] = (u16)(viReg & ~0x8000);
        inter |= 4;
    }

    viReg = __VIRegs[VI_DISP_INT_3];
    if (viReg & 0x8000) {
        __VIRegs[VI_DISP_INT_3] = (u16)(viReg & ~0x8000);
        inter |= 8;
    }

    if ((inter & 4) || (inter & 8)) {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        if (PositionCallback) {
            s16 x, y;
            __VIGetCurrentPosition(&x, &y);
            (*PositionCallback)(x, y);
        }
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
        return;
    }

    retraceCount++;

    OSClearContext(&exceptionContext);
    OSSetCurrentContext(&exceptionContext);
    if (PreCB) {
        (*PreCB)(retraceCount);
    }

    if (flushFlag) {
        if (VISetRegs()) {
            flushFlag = 0;
            SIRefreshSamplingRate();
        }
    }

    if (PostCB) {
        OSClearContext(&exceptionContext);
        (*PostCB)(retraceCount);
    }

    OSWakeupThread(&retraceQueue);
    OSClearContext(&exceptionContext);
    OSSetCurrentContext(context);
}

VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback callback)
{
    int interrupt;
    VIRetraceCallback oldCallback;

    oldCallback = PreCB;

    interrupt = OSDisableInterrupts();
    PreCB     = callback;
    OSRestoreInterrupts(interrupt);

    return oldCallback;
}

VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback callback)
{
    int interrupt;
    VIRetraceCallback oldCallback;

    oldCallback = PostCB;

    interrupt = OSDisableInterrupts();
    PostCB    = callback;
    OSRestoreInterrupts(interrupt);

    return oldCallback;
}

static VITimingInfo* getTiming(VITVMode mode)
{
    switch (mode) {
    case VI_TVMODE_NTSC_INT:
        return &timing[0];
    case VI_TVMODE_NTSC_DS:
        return &timing[1];

    case VI_TVMODE_PAL_INT:
        return &timing[2];
    case VI_TVMODE_PAL_DS:
        return &timing[3];

    case VI_TVMODE_EURGB60_INT:
        return &timing[0];
    case VI_TVMODE_EURGB60_DS:
        return &timing[1];

    case VI_TVMODE_MPAL_INT:
        return &timing[4];
    case VI_TVMODE_MPAL_DS:
        return &timing[5];

    case VI_TVMODE_NTSC_PROG:
        return &timing[6];
    case VI_TVMODE_NTSC_3D:
        return &timing[7];

    case VI_TVMODE_DEBUG_PAL_INT:
        return &timing[2];
    case VI_TVMODE_DEBUG_PAL_DS:
        return &timing[3];

    case VI_TVMODE_GCA_INT:
        return &timing[8];
    case VI_TVMODE_GCA_PROG:
        return &timing[9];
    }

    return NULL;
}

void __VIInit(VITVMode mode)
{
    VITimingInfo* tm;
    u32 nonInter;
    vu32 a;
    u32 tv, tvForReg;

    u16 hct, vct;

    nonInter = mode & 2;
    tv       = (u32)mode >> 2;

    *(u32*)OSPhysicalToCached(0xCC) = tv;

    tm = getTiming(mode);

    __VIRegs[VI_DISP_CONFIG] = 2;
    for (a = 0; a < 1000; a++) {
        ;
    }

    __VIRegs[VI_DISP_CONFIG] = 0;

    __VIRegs[VI_HORIZ_TIMING_0U] = tm->hlw << 0;
    __VIRegs[VI_HORIZ_TIMING_0L] = (tm->hce << 0) | (tm->hcs << 8);

    __VIRegs[VI_HORIZ_TIMING_1U] = (tm->hsy << 0) | ((tm->hbe640 & ((1 << 9) - 1)) << 7);
    __VIRegs[VI_HORIZ_TIMING_1L] = ((tm->hbe640 >> 9) << 0) | (tm->hbs640 << 1);

    __VIRegs[VI_VERT_TIMING] = (tm->equ << 0) | (0 << 4);

    __VIRegs[VI_VERT_TIMING_ODD_U] = (tm->prbOdd + tm->acv * 2 - 2) << 0;
    __VIRegs[VI_VERT_TIMING_ODD]   = tm->psbOdd + 2 << 0;

    __VIRegs[VI_VERT_TIMING_EVEN_U] = (tm->prbEven + tm->acv * 2 - 2) << 0;
    __VIRegs[VI_VERT_TIMING_EVEN]   = tm->psbEven + 2 << 0;

    __VIRegs[VI_BBI_ODD_U] = (tm->bs1 << 0) | (tm->be1 << 5);
    __VIRegs[VI_BBI_ODD]   = (tm->bs3 << 0) | (tm->be3 << 5);

    __VIRegs[VI_BBI_EVEN_U] = (tm->bs2 << 0) | (tm->be2 << 5);
    __VIRegs[VI_BBI_EVEN]   = (tm->bs4 << 0) | (tm->be4 << 5);

    __VIRegs[VI_HSW] = (40 << 0) | (40 << 8);

    __VIRegs[VI_DISP_INT_1U] = 1;
    __VIRegs[VI_DISP_INT_1]  = (1 << 0) | (1 << 12) | (0 << 15);

    hct                      = (tm->hlw + 1);
    vct                      = (tm->numHalfLines / 2 + 1) | (1 << 12) | (0 << 15);
    __VIRegs[VI_DISP_INT_0U] = hct << 0;
    __VIRegs[VI_DISP_INT_0]  = vct;

    if (mode != VI_TVMODE_NTSC_PROG && mode != VI_TVMODE_NTSC_3D && mode != VI_TVMODE_GCA_PROG) {
        __VIRegs[VI_DISP_CONFIG] = (1 << 0) | (0 << 1) | (nonInter << 2) | (0 << 3) | (0 << 4) | (0 << 6) | (tv << 8);
        __VIRegs[VI_CLOCK_SEL]   = 0;

    } else {
        __VIRegs[VI_DISP_CONFIG] = (1 << 0) | (0 << 1) | (1 << 2) | (0 << 3) | (0 << 4) | (0 << 6) | (tv << 8);
        __VIRegs[VI_CLOCK_SEL]   = 1;
    }
}

static void AdjustPosition(u16 acv)
{
    s32 coeff, frac;

    HorVer.adjDispPosX = (u16)CLAMP(0, 720 - HorVer.dispSizeX, (s16)HorVer.dispPosX + displayOffsetH);

    coeff = (HorVer.xfbMode == VI_XFBMODE_SF) ? 2 : 1;
    frac  = HorVer.dispPosY & 1;

    HorVer.adjDispPosY = (u16)MAX((s16)HorVer.dispPosY + displayOffsetV, frac);

    HorVer.adjDispSizeY = (u16)(HorVer.dispSizeY + MIN((s16)HorVer.dispPosY + displayOffsetV - frac, 0)
                                - MAX((s16)HorVer.dispPosY + (s16)HorVer.dispSizeY + displayOffsetV - ((s16)acv * 2 - frac), 0));

    HorVer.adjPanPosY = (u16)(HorVer.panPosY - MIN((s16)HorVer.dispPosY + displayOffsetV - frac, 0) / coeff);

    HorVer.adjPanSizeY = (u16)(HorVer.panSizeY + MIN((s16)HorVer.dispPosY + displayOffsetV - frac, 0) / coeff
                               - MAX((s16)HorVer.dispPosY + (s16)HorVer.dispSizeY + displayOffsetV - ((s16)acv * 2 - frac), 0) / coeff);
}

static void ImportAdjustingValues(void)
{
    displayOffsetH = __OSLockSram()->displayOffsetH;
    displayOffsetV = 0;
    __OSUnlockSram(FALSE);
}

void VIInit(void)
{
    u16 dspCfg;
    u32 value, tv, tvInBootrom;

    if (IsInitialized) {
        return;
    }

    OSRegisterVersion(__VIVersion);
    IsInitialized = TRUE;
    encoderType   = 1;

    if (!(__VIRegs[VI_DISP_CONFIG] & 1)) {
        __VIInit(VI_TVMODE_NTSC_INT);
    }

    retraceCount   = 0;
    changed        = 0;
    shdwChanged    = 0;
    changeMode     = 0;
    shdwChangeMode = 0;
    flushFlag      = 0;

    __VIRegs[VI_FCT_0U] = ((((taps[0])) << 0) | (((taps[1] & ((1 << (6)) - 1))) << 10));
    __VIRegs[VI_FCT_0]  = ((((taps[1] >> 6)) << 0) | (((taps[2])) << 4));
    __VIRegs[VI_FCT_1U] = ((((taps[3])) << 0) | (((taps[4] & ((1 << (6)) - 1))) << 10));
    __VIRegs[VI_FCT_1]  = ((((taps[4] >> 6)) << 0) | (((taps[5])) << 4));
    __VIRegs[VI_FCT_2U] = ((((taps[6])) << 0) | (((taps[7] & ((1 << (6)) - 1))) << 10));
    __VIRegs[VI_FCT_2]  = ((((taps[7] >> 6)) << 0) | (((taps[8])) << 4));
    __VIRegs[VI_FCT_3U] = ((((taps[9])) << 0) | (((taps[10])) << 8));
    __VIRegs[VI_FCT_3]  = ((((taps[11])) << 0) | (((taps[12])) << 8));
    __VIRegs[VI_FCT_4U] = ((((taps[13])) << 0) | (((taps[14])) << 8));
    __VIRegs[VI_FCT_4]  = ((((taps[15])) << 0) | (((taps[16])) << 8));
    __VIRegs[VI_FCT_5U] = ((((taps[17])) << 0) | (((taps[18])) << 8));
    __VIRegs[VI_FCT_5]  = ((((taps[19])) << 0) | (((taps[20])) << 8));
    __VIRegs[VI_FCT_6U] = ((((taps[21])) << 0) | (((taps[22])) << 8));
    __VIRegs[VI_FCT_6]  = ((((taps[23])) << 0) | (((taps[24])) << 8));

    __VIRegs[VI_WIDTH] = 640;
    ImportAdjustingValues();
    tvInBootrom = *(u32*)OSPhysicalToCached(0xCC);
    dspCfg      = __VIRegs[VI_DISP_CONFIG];

    HorVer.nonInter = ((((u32)(dspCfg)) >> 2 & 0x00000001));
    HorVer.tv       = ((((u32)(dspCfg)) & 0x00000300) >> 8);

    if ((tvInBootrom == VI_PAL) && (HorVer.tv == VI_NTSC)) {
        HorVer.tv = VI_EURGB60;
    }

    tv                   = (HorVer.tv == VI_DEBUG) ? VI_NTSC : HorVer.tv;
    HorVer.timing        = getTiming((VITVMode)VI_TVMODE(tv, HorVer.nonInter));
    regs[VI_DISP_CONFIG] = dspCfg;

    CurrTiming = HorVer.timing;
    CurrTvMode = HorVer.tv;

    HorVer.dispSizeX = 640;
    HorVer.dispSizeY = (u16)(CurrTiming->acv * 2);
    HorVer.dispPosX  = (u16)((720 - HorVer.dispSizeX) / 2);
    HorVer.dispPosY  = 0;

    AdjustPosition(CurrTiming->acv);

    HorVer.fbSizeX     = 640;
    HorVer.fbSizeY     = (u16)(CurrTiming->acv * 2);
    HorVer.panPosX     = 0;
    HorVer.panPosY     = 0;
    HorVer.panSizeX    = 640;
    HorVer.panSizeY    = (u16)(CurrTiming->acv * 2);
    HorVer.xfbMode     = VI_XFBMODE_SF;
    HorVer.wordPerLine = 40;
    HorVer.std         = 40;
    HorVer.wpl         = 40;
    HorVer.xof         = 0;
    HorVer.isBlack     = TRUE;
    HorVer.is3D        = FALSE;

    OSInitThreadQueue(&retraceQueue);

    value                   = __VIRegs[VI_DISP_INT_0];
    value                   = (((u32)(value)) & ~0x00008000) | (((0)) << 15);
    __VIRegs[VI_DISP_INT_0] = value;

    value                   = __VIRegs[VI_DISP_INT_1];
    value                   = (((u32)(value)) & ~0x00008000) | (((0)) << 15);
    __VIRegs[VI_DISP_INT_1] = value;

    PreCB  = NULL;
    PostCB = NULL;

    __OSSetInterruptHandler(24, __VIRetraceHandler);
    __OSUnmaskInterrupts((0x80000000u >> (24)));
}

void VIWaitForRetrace(void)
{
    int interrupt;
    u32 startCount;

    interrupt  = OSDisableInterrupts();
    startCount = retraceCount;
    do {
        OSSleepThread(&retraceQueue);
    } while (startCount == retraceCount);
    OSRestoreInterrupts(interrupt);
}

static void setInterruptRegs(VITimingInfo* tm)
{
    u16 vct, hct, borrow;

    vct    = (u16)(tm->numHalfLines / 2);
    borrow = (u16)(tm->numHalfLines % 2);
    hct    = (u16)((borrow) ? tm->hlw : (u16)0);

    vct++;
    hct++;

    regs[VI_DISP_INT_0U] = (u16)hct;
    changed |= VI_BITMASK(VI_DISP_INT_0U);

    regs[VI_DISP_INT_0] = (u16)((((u32)(vct))) | (((u32)(1)) << 12) | (((u32)(0)) << 15));
    changed |= VI_BITMASK(VI_DISP_INT_0);
}

static void setPicConfig(u16 fbSizeX, VIXFBMode xfbMode, u16 panPosX, u16 panSizeX, u8* wordPerLine, u8* std, u8* wpl, u8* xof)
{
    *wordPerLine = (u8)((fbSizeX + 15) / 16);
    *std         = (u8)((xfbMode == VI_XFBMODE_SF) ? *wordPerLine : (u8)(2 * *wordPerLine));
    *xof         = (u8)(panPosX % 16);
    *wpl         = (u8)((*xof + panSizeX + 15) / 16);

    regs[VI_HSW] = (u16)((((u32)(*std))) | (((u32)(*wpl)) << 8));
    changed |= VI_BITMASK(VI_HSW);
}

static void setBBIntervalRegs(VITimingInfo* tm)
{
    u16 val;

    val                = (u16)((((u32)(tm->bs1))) | (((u32)(tm->be1)) << 5));
    regs[VI_BBI_ODD_U] = val;
    changed |= VI_BITMASK(VI_BBI_ODD_U);

    val              = (u16)((((u32)(tm->bs3))) | (((u32)(tm->be3)) << 5));
    regs[VI_BBI_ODD] = val;
    changed |= VI_BITMASK(VI_BBI_ODD);

    val                 = (u16)((((u32)(tm->bs2))) | (((u32)(tm->be2)) << 5));
    regs[VI_BBI_EVEN_U] = val;
    changed |= VI_BITMASK(VI_BBI_EVEN_U);

    val               = (u16)((((u32)(tm->bs4))) | (((u32)(tm->be4)) << 5));
    regs[VI_BBI_EVEN] = val;
    changed |= VI_BITMASK(VI_BBI_EVEN);
}

static void setScalingRegs(u16 panSizeX, u16 dispSizeX, BOOL is3D)
{
    u32 scale;

    panSizeX = (u16)(is3D ? panSizeX * 2 : panSizeX);

    if (panSizeX < dispSizeX) {
        scale = (256 * (u32)panSizeX + (u32)dispSizeX - 1) / (u32)dispSizeX;

        regs[VI_HSR] = (u16)((((u32)(scale))) | (((u32)(1)) << 12));
        changed |= VI_BITMASK(VI_HSR);

        regs[VI_WIDTH] = (u16)((((u32)(panSizeX))));
        changed |= VI_BITMASK(VI_WIDTH);
    } else {
        regs[VI_HSR] = (u16)((((u32)(256))) | (((u32)(0)) << 12));
        changed |= VI_BITMASK(VI_HSR);
    }
}

static void calcFbbs(u32 bufAddr, u16 panPosX, u16 panPosY, u8 wordPerLine, VIXFBMode xfbMode, u16 dispPosY, u32* tfbb, u32* bfbb)
{
    u32 bytesPerLine, xoffInWords;
    xoffInWords  = (u32)panPosX / 16;
    bytesPerLine = (u32)wordPerLine * 32;

    *tfbb = bufAddr + xoffInWords * 32 + bytesPerLine * panPosY;
    *bfbb = (xfbMode == VI_XFBMODE_SF) ? *tfbb : (*tfbb + bytesPerLine);

    if (dispPosY % 2 == 1) {
        u32 tmp = *tfbb;
        *tfbb   = *bfbb;
        *bfbb   = tmp;
    }

    *tfbb = ToPhysical(*tfbb);
    *bfbb = ToPhysical(*bfbb);
}

static void setFbbRegs(VIPositionInfo* hv, u32* tfbb, u32* bfbb, u32* rtfbb, u32* rbfbb)
{
    u32 shifted;
    calcFbbs(hv->bufAddr, hv->panPosX, hv->adjPanPosY, hv->wordPerLine, hv->xfbMode, hv->adjDispPosY, tfbb, bfbb);

    if (hv->is3D) {
        calcFbbs(hv->rbufAddr, hv->panPosX, hv->adjPanPosY, hv->wordPerLine, hv->xfbMode, hv->adjDispPosY, rtfbb, rbfbb);
    }

    if (IS_LOWER_16MB(*tfbb) && IS_LOWER_16MB(*bfbb) && IS_LOWER_16MB(*rtfbb) && IS_LOWER_16MB(*rbfbb)) {
        shifted = 0;
    } else {
        shifted = 1;
    }

    if (shifted) {
        *tfbb >>= 5;
        *bfbb >>= 5;
        *rtfbb >>= 5;
        *rbfbb >>= 5;
    }

    regs[VI_TOP_FIELD_BASE_LEFT_U] = (u16)(*tfbb & 0xFFFF);
    changed |= VI_BITMASK(VI_TOP_FIELD_BASE_LEFT_U);

    regs[VI_TOP_FIELD_BASE_LEFT] = (u16)((((*tfbb >> 16))) | hv->xof << 8 | shifted << 12);
    changed |= VI_BITMASK(VI_TOP_FIELD_BASE_LEFT);

    regs[VI_BTTM_FIELD_BASE_LEFT_U] = (u16)(*bfbb & 0xFFFF);
    changed |= VI_BITMASK(VI_BTTM_FIELD_BASE_LEFT_U);

    regs[VI_BTTM_FIELD_BASE_LEFT] = (u16)(*bfbb >> 16);
    changed |= VI_BITMASK(VI_BTTM_FIELD_BASE_LEFT);

    if (hv->is3D) {
        regs[VI_TOP_FIELD_BASE_RIGHT_U] = *rtfbb & 0xffff;
        changed |= VI_BITMASK(VI_TOP_FIELD_BASE_RIGHT_U);

        regs[VI_TOP_FIELD_BASE_RIGHT] = *rtfbb >> 16;
        changed |= VI_BITMASK(VI_TOP_FIELD_BASE_RIGHT);

        regs[VI_BTTM_FIELD_BASE_RIGHT_U] = *rbfbb & 0xFFFF;
        changed |= VI_BITMASK(VI_BTTM_FIELD_BASE_RIGHT_U);

        regs[VI_BTTM_FIELD_BASE_RIGHT] = *rbfbb >> 16;
        changed |= VI_BITMASK(VI_BTTM_FIELD_BASE_RIGHT);
    }
}

static void setHorizontalRegs(VITimingInfo* tm, u16 dispPosX, u16 dispSizeX)
{
    u32 hbe, hbs, hbeLo, hbeHi;

    regs[VI_HORIZ_TIMING_0U] = (u16)tm->hlw;
    changed |= VI_BITMASK(VI_HORIZ_TIMING_0U);

    regs[VI_HORIZ_TIMING_0L] = (u16)(tm->hce | tm->hcs << 8);
    changed |= VI_BITMASK(VI_HORIZ_TIMING_0L);

    hbe = (u32)(tm->hbe640 - 40 + dispPosX);
    hbs = (u32)(tm->hbs640 + 40 + dispPosX - (720 - dispSizeX));

    hbeLo = hbe & ONES(9);
    hbeHi = hbe >> 9;

    regs[VI_HORIZ_TIMING_1U] = (u16)(tm->hsy | hbeLo << 7);
    changed |= VI_BITMASK(VI_HORIZ_TIMING_1U);

    regs[VI_HORIZ_TIMING_1L] = (u16)(hbeHi | hbs << 1);
    changed |= VI_BITMASK(VI_HORIZ_TIMING_1L);
}

static void setVerticalRegs(u16 dispPosY, u16 dispSizeY, u8 equ, u16 acv, u16 prbOdd, u16 prbEven, u16 psbOdd, u16 psbEven, BOOL black)
{
    u16 actualPrbOdd, actualPrbEven, actualPsbOdd, actualPsbEven, actualAcv, c, d;

    if (regs[VI_CLOCK_SEL] & 1) {
        c = 1;
        d = 2;
    } else {
        c = 2;
        d = 1;
    }

    if (dispPosY % 2 == 0) {
        actualPrbOdd  = (u16)(prbOdd + d * dispPosY);
        actualPsbOdd  = (u16)(psbOdd + d * ((c * acv - dispSizeY) - dispPosY));
        actualPrbEven = (u16)(prbEven + d * dispPosY);
        actualPsbEven = (u16)(psbEven + d * ((c * acv - dispSizeY) - dispPosY));
    } else {
        actualPrbOdd  = (u16)(prbEven + d * dispPosY);
        actualPsbOdd  = (u16)(psbEven + d * ((c * acv - dispSizeY) - dispPosY));
        actualPrbEven = (u16)(prbOdd + d * dispPosY);
        actualPsbEven = (u16)(psbOdd + d * ((c * acv - dispSizeY) - dispPosY));
    }

    actualAcv = (u16)(dispSizeY / c);

    if (black) {
        actualPrbOdd += 2 * actualAcv - 2;
        actualPsbOdd += 2;
        actualPrbEven += 2 * actualAcv - 2;
        actualPsbEven += 2;
        actualAcv = 0;
    }

    regs[VI_VERT_TIMING] = (u16)(equ | actualAcv << 4);
    changed |= VI_BITMASK(VI_VERT_TIMING);

    regs[VI_VERT_TIMING_ODD_U] = (u16)actualPrbOdd << 0;
    changed |= VI_BITMASK(VI_VERT_TIMING_ODD_U);

    regs[VI_VERT_TIMING_ODD] = (u16)actualPsbOdd << 0;
    changed |= VI_BITMASK(VI_VERT_TIMING_ODD);

    regs[VI_VERT_TIMING_EVEN_U] = (u16)actualPrbEven << 0;
    changed |= VI_BITMASK(VI_VERT_TIMING_EVEN_U);

    regs[VI_VERT_TIMING_EVEN] = (u16)actualPsbEven << 0;
    changed |= VI_BITMASK(VI_VERT_TIMING_EVEN);
}

static void PrintDebugPalCaution(void)
{
    static u32 message = 0;

    if (message == 0) {
        message = 1;
        OSReport("***************************************\n");
        OSReport(" ! ! ! C A U T I O N ! ! !             \n");
        OSReport("This TV format \"DEBUG_PAL\" is only for \n");
        OSReport("temporary solution until PAL DAC board \n");
        OSReport("is available. Please do NOT use this   \n");
        OSReport("mode in real games!!!                  \n");
        OSReport("***************************************\n");
    }
}

void VIConfigure(const GXRenderModeObj* obj)
{
    VITimingInfo* tm;
    u32 regDspCfg;
    BOOL enabled;
    u32 newNonInter, tvInBootrom, tvInGame;

    enabled     = OSDisableInterrupts();
    newNonInter = (u32)obj->viTVmode & 3;

    if (HorVer.nonInter != newNonInter) {
        changeMode      = 1;
        HorVer.nonInter = newNonInter;
    }

    tvInGame    = (u32)obj->viTVmode >> 2;
    tvInBootrom = *(u32*)OSPhysicalToCached(0xCC);

    if (tvInGame == VI_DEBUG_PAL) {
        PrintDebugPalCaution();
    }

    switch (tvInBootrom) {
    case VI_MPAL:
    case VI_NTSC:
    case VI_GCA:
        if (tvInGame == VI_NTSC || tvInGame == VI_MPAL || tvInGame == VI_GCA) {
            break;
        }
        goto panic;
    case VI_PAL:
    case VI_EURGB60:
        if (tvInGame == VI_PAL || tvInGame == VI_EURGB60) {
            break;
        }
    default:
    panic:
        OSPanic("vi.c", 1908, "VIConfigure(): Tried to change mode from (%d) to (%d), which is forbidden\n", tvInBootrom, tvInGame);
    }
    // if (((tvInBootrom != VI_PAL && tvInBootrom != VI_EURGB60) && (tvInGame == VI_PAL || tvInGame == VI_EURGB60))
    //     || ((tvInBootrom == VI_PAL || tvInBootrom == VI_EURGB60) && (tvInGame != VI_PAL && tvInGame != VI_EURGB60))) {

    //     OSErrorLine(1908, "VIConfigure(): Tried to change mode from (%d) to (%d), which is forbidden\n", tvInBootrom, tvInGame);
    // }

    if ((tvInGame == VI_NTSC) || (tvInGame == VI_MPAL)) {
        HorVer.tv = tvInBootrom;
    } else {
        HorVer.tv = tvInGame;
    }

    HorVer.dispPosX  = obj->viXOrigin;
    HorVer.dispPosY  = (u16)((HorVer.nonInter == VI_NON_INTERLACE) ? (u16)(obj->viYOrigin * 2) : obj->viYOrigin);
    HorVer.dispSizeX = obj->viWidth;
    HorVer.fbSizeX   = obj->fbWidth;
    HorVer.fbSizeY   = obj->xfbHeight;
    HorVer.xfbMode   = obj->xFBmode;
    HorVer.panSizeX  = HorVer.fbSizeX;
    HorVer.panSizeY  = HorVer.fbSizeY;
    HorVer.panPosX   = 0;
    HorVer.panPosY   = 0;

    HorVer.dispSizeY = (u16)((HorVer.nonInter == VI_PROGRESSIVE) ? HorVer.panSizeY
                             : (HorVer.nonInter == VI_3D)        ? HorVer.panSizeY
                             : (HorVer.xfbMode == VI_XFBMODE_SF) ? (u16)(2 * HorVer.panSizeY)
                                                                 : HorVer.panSizeY);

    HorVer.is3D = (HorVer.nonInter == VI_3D) ? TRUE : FALSE;

    tm            = getTiming((VITVMode)VI_TVMODE(HorVer.tv, HorVer.nonInter));
    HorVer.timing = tm;

    AdjustPosition(tm->acv);
    if (encoderType == 0) {
        HorVer.tv = VI_DEBUG;
    }
    setInterruptRegs(tm);

    regDspCfg = regs[VI_DISP_CONFIG];
    // TODO: USE BIT MACROS OR SOMETHING
    if ((HorVer.nonInter == VI_PROGRESSIVE) || (HorVer.nonInter == VI_3D)) {
        regDspCfg = (((u32)(regDspCfg)) & ~0x00000004) | (((u32)(1)) << 2);
    } else {
        regDspCfg = (((u32)(regDspCfg)) & ~0x00000004) | (((u32)(HorVer.nonInter & 1)) << 2);
    }

    regDspCfg = (((u32)(regDspCfg)) & ~0x00000008) | (((u32)(HorVer.is3D)) << 3);

    if ((HorVer.tv == VI_DEBUG_PAL) || (HorVer.tv == VI_EURGB60) || (HorVer.tv == VI_GCA)) {
        regDspCfg = (((u32)(regDspCfg)) & ~0x00000300);
    } else {
        regDspCfg = (((u32)(regDspCfg)) & ~0x00000300) | (((u32)(HorVer.tv)) << 8);
    }

    regs[VI_DISP_CONFIG] = (u16)regDspCfg;
    changed |= VI_BITMASK(0x01);

    regDspCfg = regs[VI_CLOCK_SEL];
    if (obj->viTVmode == VI_TVMODE_NTSC_PROG || obj->viTVmode == VI_TVMODE_NTSC_3D || obj->viTVmode == VI_TVMODE_GCA_PROG) {
        regDspCfg = (u32)(regDspCfg & ~0x1) | 1;
    } else {
        regDspCfg = (u32)(regDspCfg & ~0x1);
    }

    regs[VI_CLOCK_SEL] = (u16)regDspCfg;

    changed |= 0x200;

    setScalingRegs(HorVer.panSizeX, HorVer.dispSizeX, HorVer.is3D);
    setHorizontalRegs(tm, HorVer.adjDispPosX, HorVer.dispSizeX);
    setBBIntervalRegs(tm);
    setPicConfig(HorVer.fbSizeX, HorVer.xfbMode, HorVer.panPosX, HorVer.panSizeX, &HorVer.wordPerLine, &HorVer.std, &HorVer.wpl,
                 &HorVer.xof);

    if (FBSet) {
        setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
    }

    setVerticalRegs(HorVer.adjDispPosY, HorVer.adjDispSizeY, tm->equ, tm->acv, tm->prbOdd, tm->prbEven, tm->psbOdd, tm->psbEven,
                    HorVer.isBlack);
    OSRestoreInterrupts(enabled);
}

void VIConfigurePan(u16 xOrg, u16 yOrg, u16 width, u16 height)
{
    BOOL enabled;
    VITimingInfo* tm;

#if DEBUG
    ASSERTMSGLINEV(2118, (xOrg & 1) == 0,
        "VIConfigurePan(): Odd number(%d) is specified to xOrg\n",
        xOrg);
    if (HorVer.FBMode == VI_XFBMODE_DF) {
        ASSERTMSGLINEV(2123, (height & 1) == 0,
            "VIConfigurePan(): Odd number(%d) is specified to height when DF XFB mode\n",
            height);
    }
#endif
    enabled = OSDisableInterrupts();
    HorVer.panPosX   = xOrg;
    HorVer.panPosY   = yOrg;
    HorVer.panSizeX  = width;
    HorVer.panSizeY  = height;
    HorVer.dispSizeY = (HorVer.nonInter == 2)           ? HorVer.panSizeY :
                       (HorVer.nonInter == 3)           ? HorVer.panSizeY :
                       (HorVer.xfbMode == VI_XFBMODE_SF) ? (u16)(HorVer.panSizeY * 2) :
                                                          HorVer.panSizeY;
    tm = HorVer.timing;
    AdjustPosition(tm->acv);
    setScalingRegs(HorVer.panSizeX, HorVer.dispSizeX, HorVer.is3D);
    setPicConfig(HorVer.fbSizeX, HorVer.xfbMode, HorVer.panPosX, HorVer.panSizeX, &HorVer.wordPerLine, &HorVer.std, &HorVer.wpl, &HorVer.xof);
    if (FBSet != 0) {
        setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
    }
    setVerticalRegs(HorVer.adjDispPosY, HorVer.dispSizeY, tm->equ, tm->acv, tm->prbOdd, tm->prbEven, tm->psbOdd, tm->psbEven, HorVer.isBlack);
    OSRestoreInterrupts(enabled);
}

void VIFlush(void)
{
    BOOL enabled;
    s32 regIndex;
    u32 val; // for stack.

    enabled = OSDisableInterrupts();
    shdwChangeMode |= changeMode;
    changeMode = 0;
    shdwChanged |= changed;

    while (changed) {
        regIndex           = cntlzd(changed);
        shdwRegs[regIndex] = regs[regIndex];
        changed &= ~VI_BITMASK(regIndex);
    }

    flushFlag   = 1;
    NextBufAddr = HorVer.bufAddr;
    OSRestoreInterrupts(enabled);
}

void VISetNextFrameBuffer(void* fb)
{
    BOOL enabled   = OSDisableInterrupts();
    HorVer.bufAddr = (u32)fb;
    FBSet          = 1;
    setFbbRegs(&HorVer, &HorVer.tfbb, &HorVer.bfbb, &HorVer.rtfbb, &HorVer.rbfbb);
    OSRestoreInterrupts(enabled);
}

void* VIGetNextFrameBuffer(void) { return (void*)NextBufAddr; }

void* VIGetCurrentFrameBuffer(void) { return (void*)CurrBufAddr; }

void VISetNextRightFrameBuffer(void* fb)
{
    // UNUSED FUNCTION
}

void VISetBlack(BOOL isBlack)
{
    int interrupt;
    VITimingInfo* tm;

    interrupt      = OSDisableInterrupts();
    HorVer.isBlack = isBlack;
    tm             = HorVer.timing;
    setVerticalRegs(HorVer.adjDispPosY, HorVer.dispSizeY, tm->equ, tm->acv, tm->prbOdd, tm->prbEven, tm->psbOdd, tm->psbEven,
                    HorVer.isBlack);
    OSRestoreInterrupts(interrupt);
}

void VISet3D(BOOL threeD)
{
    // UNUSED FUNCTION
}

u32 VIGetRetraceCount(void) { return retraceCount; }

static void GetCurrentDisplayPosition(u32* hct, u32* vct)
{
    u32 hcount, vcount0, vcount;
    vcount = __VIRegs[VI_VERT_COUNT] & 0x7FF;

    do {
        vcount0 = vcount;
        hcount  = __VIRegs[VI_HORIZ_COUNT] & 0x7FF;
        vcount  = __VIRegs[VI_VERT_COUNT] & 0x7FF;
    } while (vcount0 != vcount);

    *hct = hcount;
    *vct = vcount;
}

static u32 getCurrentHalfLine(void)
{
    u32 hcount, vcount;
    GetCurrentDisplayPosition(&hcount, &vcount);

    return ((vcount - 1) << 1) + ((hcount - 1) / CurrTiming->hlw);
}

static u32 getCurrentFieldEvenOdd() { return (getCurrentHalfLine() < CurrTiming->numHalfLines) ? 1 : 0; }

u32 VIGetNextField(void)
{
    u32 nextField;
    int interrupt;

    interrupt = OSDisableInterrupts();
    nextField = getCurrentFieldEvenOdd() ^ 1;
    OSRestoreInterrupts(interrupt);
    return nextField ^ (HorVer.adjDispPosY & 1);
}

u32 VIGetCurrentLine(void)
{
    u32 line;
    VITimingInfo* tm;
    int interrupt;

    tm        = CurrTiming;
    interrupt = OSDisableInterrupts();
    line      = getCurrentHalfLine();
    OSRestoreInterrupts(interrupt);

    if (line >= tm->numHalfLines) {
        line -= tm->numHalfLines;
    }

    return (line >> 1);
}

u32 VIGetTvFormat(void)
{
    u32 fmt;
    int interrupt;

    interrupt = OSDisableInterrupts();

    switch (CurrTvMode) {
    case VI_NTSC:
    case VI_DEBUG:
    case VI_GCA:
        fmt = VI_NTSC;
        break;
    case VI_PAL:
    case VI_DEBUG_PAL:
        fmt = VI_PAL;
        break;
    case VI_EURGB60:
    case VI_MPAL:
        fmt = CurrTvMode;
        break;
    }

    OSRestoreInterrupts(interrupt);
    return fmt;
}

u32 VIGetDTVStatus(void)
{
    u32 stat;
    int interrupt;

    interrupt = OSDisableInterrupts();
    stat      = (__VIRegs[VI_DTV_STAT] & 3);
    OSRestoreInterrupts(interrupt);
    return (stat & 1);
}

void __VIDisplayPositionToXY(u32 hcount, u32 vcount, s16* x, s16* y)
{
    u32 halfLine = ((vcount - 1) << 1) + ((hcount - 1) / CurrTiming->hlw);

    if (HorVer.nonInter == VI_INTERLACE) {
        if (halfLine < CurrTiming->numHalfLines) {
            if (halfLine < CurrTiming->equ * 3 + CurrTiming->prbOdd) {
                *y = -1;
            } else if (halfLine >= CurrTiming->numHalfLines - CurrTiming->psbOdd) {
                *y = -1;
            } else {
                *y = (s16)((halfLine - CurrTiming->equ * 3 - CurrTiming->prbOdd) & ~1);
            }
        } else {
            halfLine -= CurrTiming->numHalfLines;

            if (halfLine < CurrTiming->equ * 3 + CurrTiming->prbEven) {
                *y = -1;
            } else if (halfLine >= CurrTiming->numHalfLines - CurrTiming->psbEven) {
                *y = -1;
            } else {
                *y = (s16)(((halfLine - CurrTiming->equ * 3 - CurrTiming->prbEven) & ~1) + 1);
            }
        }
    } else if (HorVer.nonInter == VI_NON_INTERLACE) {
        if (halfLine >= CurrTiming->numHalfLines) {
            halfLine -= CurrTiming->numHalfLines;
        }

        if (halfLine < CurrTiming->equ * 3 + CurrTiming->prbOdd) {
            *y = -1;
        } else if (halfLine >= CurrTiming->numHalfLines - CurrTiming->psbOdd) {
            *y = -1;
        } else {
            *y = (s16)((halfLine - CurrTiming->equ * 3 - CurrTiming->prbOdd) & ~1);
        }
    } else if (HorVer.nonInter == VI_PROGRESSIVE) {
        if (halfLine < CurrTiming->numHalfLines) {
            if (halfLine < CurrTiming->equ * 3 + CurrTiming->prbOdd) {
                *y = -1;
            } else if (halfLine >= CurrTiming->numHalfLines - CurrTiming->psbOdd) {
                *y = -1;
            } else {
                *y = (s16)(halfLine - CurrTiming->equ * 3 - CurrTiming->prbOdd);
            }
        } else {
            halfLine -= CurrTiming->numHalfLines;

            if (halfLine < CurrTiming->equ * 3 + CurrTiming->prbEven) {
                *y = -1;
            } else if (halfLine >= CurrTiming->numHalfLines - CurrTiming->psbEven) {
                *y = -1;
            } else
                *y = (s16)((halfLine - CurrTiming->equ * 3 - CurrTiming->prbEven) & ~1);
        }
    }

    *x = (s16)(hcount - 1);
}

void __VIGetCurrentPosition(s16* x, s16* y)
{
    u32 h, v;
    GetCurrentDisplayPosition(&h, &v);
    __VIDisplayPositionToXY(h, v, x, y);
}
