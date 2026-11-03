#include <dolphin/exi.h>
#include "dolphin/os.h"
#include "dolphin/hw_regs.h"

static const char *__EXIVersion =
    "<< Dolphin SDK - EXI\trelease build: Apr 17 2003 12:33:17 (0x2301) >>";

#define MAX_DEV 3
#define MAX_CHAN 3

#define REG_MAX 5
#define REG(chan, idx) (__EXIRegs[((chan)*REG_MAX) + (idx)])

#define STATE_IDLE 0x00
#define STATE_DMA 0x01
#define STATE_IMM 0x02
#define STATE_BUSY (STATE_DMA | STATE_IMM)
#define STATE_SELECTED 0x04
#define STATE_ATTACHED 0x08
#define STATE_LOCKED 0x10

#define EXI_0CR(tstart, dma, rw, tlen) \
    ((((u32)(tstart)) << 0) | (((u32)(dma)) << 1) | (((u32)(rw)) << 2) | (((u32)(tlen)) << 4))

#define CPR_CS(x) ((1u << (x)) << 7)
#define CPR_CLK(x) ((x) << 4)


static EXIControl Ecb[MAX_CHAN];
static u32 IDSerialPort1;
s32 __EXIProbeStartTime[2] : (OS_BASE_CACHED | 0x30C0);

#pragma scheduling off

static void SetExiInterruptMask(s32 chan, EXIControl *exi)
{
    EXIControl *exi2;

    exi2 = &Ecb[2];
    switch (chan)
    {
    case 0:
        if ((exi->exiCallback == 0 && exi2->exiCallback == 0) || (exi->state & STATE_LOCKED))
        {
            __OSMaskInterrupts(OS_INTERRUPTMASK_EXI_0_EXI | OS_INTERRUPTMASK_EXI_2_EXI);
        }
        else
        {
            __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_0_EXI | OS_INTERRUPTMASK_EXI_2_EXI);
        }
        break;
    case 1:
        if (exi->exiCallback == 0 || (exi->state & STATE_LOCKED))
        {
            __OSMaskInterrupts(OS_INTERRUPTMASK_EXI_1_EXI);
        }
        else
        {
            __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_1_EXI);
        }
        break;
    case 2:
        if (__OSGetInterruptHandler(__OS_INTERRUPT_PI_DEBUG) == 0 || (exi->state & STATE_LOCKED))
        {
            __OSMaskInterrupts(OS_INTERRUPTMASK_PI_DEBUG);
        }
        else
        {
            __OSUnmaskInterrupts(OS_INTERRUPTMASK_PI_DEBUG);
        }
        break;
    }
}

static void CompleteTransfer(s32 chan)
{
    EXIControl *exi = &Ecb[chan];
    u8 *buf;
    u32 data;
    int i;
    int len;

    if (exi->state & STATE_BUSY)
    {
        if ((exi->state & STATE_IMM) && (len = exi->immLen))
        {
            buf = exi->immBuf;
            data = REG(chan, 4);
            for (i = 0; i < len; i++)
            {
                *buf++ = (u8)((data >> ((3 - i) * 8)) & 0xff);
            }
        }
        exi->state &= ~STATE_BUSY;
    }
}

BOOL EXIImm(s32 chan, void *buf, s32 len, u32 type, EXICallback callback)
{
    EXIControl *exi = &Ecb[chan];
    BOOL enabled;

    enabled = OSDisableInterrupts();
    if ((exi->state & STATE_BUSY) || !(exi->state & STATE_SELECTED))
    {
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    exi->tcCallback = callback;
    if (exi->tcCallback)
    {
        EXIClearInterrupts(chan, FALSE, TRUE, FALSE);
        __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_0_TC >> (3 * chan));
    }

    exi->state |= STATE_IMM;

    if (type != EXI_READ)
    {
        u32 data;
        int i;

        data = 0;
        for (i = 0; i < len; i++)
        {
            data |= ((u8 *)buf)[i] << ((3 - i) * 8);
        }
        REG(chan, 4) = data;
    }

    exi->immBuf = buf;
    exi->immLen = (type != EXI_WRITE) ? len : 0;

    REG(chan, 3) = EXI_0CR(1, 0, type, len - 1);

    OSRestoreInterrupts(enabled);

    return TRUE;
}

BOOL EXIImmEx(s32 chan, void *buf, s32 len, u32 mode)
{
    s32 xLen;

    while (len)
    {
        xLen = (len < 4) ? len : 4;
        if (!EXIImm(chan, buf, xLen, mode, NULL))
        {
            return FALSE;
        }

        if (!EXISync(chan))
        {
            return FALSE;
        }

        (u8 *)buf += xLen;
        len -= xLen;
    }
    return TRUE;
}

BOOL EXIDma(s32 chan, void *buf, s32 len, u32 type, EXICallback callback)
{
    EXIControl *exi = &Ecb[chan];
    BOOL enabled;

    enabled = OSDisableInterrupts();
    if ((exi->state & STATE_BUSY) || !(exi->state & STATE_SELECTED))
    {
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    exi->tcCallback = callback;
    if (exi->tcCallback)
    {
        EXIClearInterrupts(chan, FALSE, TRUE, FALSE);
        __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_0_TC >> (3 * chan));
    }

    exi->state |= STATE_DMA;

    REG(chan, 1) = (u32)buf & 0x3ffffe0;
    REG(chan, 2) = (u32)len;
    REG(chan, 3) = EXI_0CR(1, 1, type, 0);

    OSRestoreInterrupts(enabled);

    return TRUE;
}

extern u32 __OSGetDIConfig(void);

vu16 __OSDeviceCode : (OS_BASE_CACHED | 0x30E6);

BOOL EXISync(s32 chan)
{
    EXIControl *exi = &Ecb[chan];
    BOOL rc = FALSE;
    BOOL enabled;

    while (exi->state & STATE_SELECTED)
    {
        if (((REG(chan, 3) & 1) >> 0) == 0)
        {
            enabled = OSDisableInterrupts();
            if (exi->state & STATE_SELECTED)
            {
                CompleteTransfer(chan);
                if (__OSGetDIConfig() != 0xff || ((OSGetConsoleType() & OS_CONSOLE_MASK) == OS_CONSOLE_TDEV)  || exi->immLen != 4 ||
                    (REG(chan, 0) & 0x00000070) != (EXI_FREQ_1M << 4) ||
                    (REG(chan, 4) != EXI_USB_ADAPTER && REG(chan, 4) != EXI_IS_VIEWER &&
                     REG(chan, 4) != 0x04220001) ||
                    __OSDeviceCode == 0x8200)
                {
                    rc = TRUE;
                }
            }
            OSRestoreInterrupts(enabled);
            break;
        }
    }
    return rc;
}

u32 EXIClearInterrupts(s32 chan, BOOL exi, BOOL tc, BOOL ext)
{
    u32 cpr;
    u32 prev;

    prev = cpr = REG(chan, 0);
    cpr &= 0x7f5;
    if (exi)
        cpr |= 2;
    if (tc)
        cpr |= 8;
    if (ext)
        cpr |= 0x800;
    REG(chan, 0) = cpr;
    return prev;
}

EXICallback EXISetExiCallback(s32 chan, EXICallback exiCallback)
{
    EXIControl *exi = &Ecb[chan];
    EXICallback prev;
    BOOL enabled;

    enabled = OSDisableInterrupts();
    prev = exi->exiCallback;
    exi->exiCallback = exiCallback;

    if (chan != 2)
    {
        SetExiInterruptMask(chan, exi);
    }
    else
    {
        SetExiInterruptMask(0, &Ecb[0]);
    }

    OSRestoreInterrupts(enabled);
    return prev;
}

void EXIProbeReset(void)
{
    __EXIProbeStartTime[0] = __EXIProbeStartTime[1] = 0;
    Ecb[0].idTime = Ecb[1].idTime = 0;
    __EXIProbe(0);
    __EXIProbe(1);
}

static BOOL __EXIProbe(s32 chan)
{
    EXIControl *exi = &Ecb[chan];
    BOOL enabled;
    BOOL rc;
    u32 cpr;
    s32 t;

    if (chan == 2)
    {
        return TRUE;
    }

    rc = TRUE;
    enabled = OSDisableInterrupts();
    cpr = REG(chan, 0);
    if (!(exi->state & STATE_ATTACHED))
    {
        if (cpr & 0x00000800)
        {
            EXIClearInterrupts(chan, FALSE, FALSE, TRUE);
            __EXIProbeStartTime[chan] = exi->idTime = 0;
        }

        if (cpr & 0x00001000)
        {
            t = (s32)(OSTicksToMilliseconds(OSGetTime()) / 100) + 1;
            if (__EXIProbeStartTime[chan] == 0)
            {
                __EXIProbeStartTime[chan] = t;
            }
            if (t - __EXIProbeStartTime[chan] < 300 / 100)
            {
                rc = FALSE;
            }
        }
        else
        {
            __EXIProbeStartTime[chan] = exi->idTime = 0;
            rc = FALSE;
        }
    }
    else if (!(cpr & 0x00001000) || (cpr & 0x00000800))
    {
        __EXIProbeStartTime[chan] = exi->idTime = 0;
        rc = FALSE;
    }
    OSRestoreInterrupts(enabled);

    return rc;
}

BOOL EXIProbe(s32 chan)
{
    EXIControl *exi = &Ecb[chan];
    BOOL rc;
    u32 id;

    rc = __EXIProbe(chan);
    if (rc && exi->idTime == 0)
    {
        rc = EXIGetID(chan, 0, &id) ? TRUE : FALSE;
    }
    return rc;
}

s32 EXIProbeEx(s32 chan)
{
    if (EXIProbe(chan))
    {
        return 1;
    }
    else if (__EXIProbeStartTime[chan] != 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

static BOOL __EXIAttach(s32 chan, EXICallback extCallback)
{
    EXIControl *exi = &Ecb[chan];
    BOOL enabled;

    enabled = OSDisableInterrupts();
    if ((exi->state & STATE_ATTACHED) || __EXIProbe(chan) == FALSE)
    {
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    EXIClearInterrupts(chan, TRUE, FALSE, FALSE);

    exi->extCallback = extCallback;
    __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_0_EXT >> (3 * chan));
    exi->state |= STATE_ATTACHED;
    OSRestoreInterrupts(enabled);

    return TRUE;
}

BOOL EXIAttach(s32 chan, EXICallback extCallback)
{
    EXIControl *exi = &Ecb[chan];
    BOOL enabled;
    BOOL rc;

    EXIProbe(chan);

    enabled = OSDisableInterrupts();
    if (exi->idTime == 0)
    {
        OSRestoreInterrupts(enabled);
        return FALSE;
    }
    rc = __EXIAttach(chan, extCallback);
    OSRestoreInterrupts(enabled);
    return rc;
}

BOOL EXIDetach(s32 chan)
{
    EXIControl *exi = &Ecb[chan];
    BOOL enabled;

    enabled = OSDisableInterrupts();
    if (!(exi->state & STATE_ATTACHED))
    {
        OSRestoreInterrupts(enabled);
        return TRUE;
    }
    if ((exi->state & STATE_LOCKED) && exi->dev == 0)
    {
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    exi->state &= ~STATE_ATTACHED;
    __OSMaskInterrupts((OS_INTERRUPTMASK_EXI_0_EXT | OS_INTERRUPTMASK_EXI_0_EXI) >> (3 * chan));
    OSRestoreInterrupts(enabled);
    return TRUE;
}

BOOL EXISelect(s32 chan, u32 dev, u32 freq)
{
    EXIControl *exi = &Ecb[chan];
    u32 cpr;
    BOOL enabled;

    enabled = OSDisableInterrupts();
    if ((exi->state & STATE_SELECTED) ||
        chan != 2 && (dev == 0 && !(exi->state & STATE_ATTACHED) && !__EXIProbe(chan) ||
                      !(exi->state & STATE_LOCKED) || (exi->dev != dev)))
    {
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    exi->state |= STATE_SELECTED;
    cpr = REG(chan, 0);
    cpr &= 0x405;
    cpr |= CPR_CS(dev) | CPR_CLK(freq);
    REG(chan, 0) = cpr;

    if (exi->state & STATE_ATTACHED)
    {
        switch (chan)
        {
        case 0:
            __OSMaskInterrupts(OS_INTERRUPTMASK_EXI_0_EXT);
            break;
        case 1:
            __OSMaskInterrupts(OS_INTERRUPTMASK_EXI_1_EXT);
            break;
        }
    }

    OSRestoreInterrupts(enabled);
    return TRUE;
}

BOOL EXIDeselect(s32 chan)
{
    EXIControl *exi = &Ecb[chan];
    u32 cpr;
    BOOL enabled;

    enabled = OSDisableInterrupts();
    if (!(exi->state & STATE_SELECTED))
    {
        OSRestoreInterrupts(enabled);
        return FALSE;
    }
    exi->state &= ~STATE_SELECTED;
    cpr = REG(chan, 0);
    REG(chan, 0) = cpr & 0x405;

    if (exi->state & STATE_ATTACHED)
    {
        switch (chan)
        {
        case 0:
            __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_0_EXT);
            break;
        case 1:
            __OSUnmaskInterrupts(OS_INTERRUPTMASK_EXI_1_EXT);
            break;
        }
    }

    OSRestoreInterrupts(enabled);

    if (chan != 2 && (cpr & CPR_CS(0)))
    {
        return __EXIProbe(chan) ? TRUE : FALSE;
    }

    return TRUE;
}

static void EXIIntrruptHandler(__OSInterrupt interrupt, OSContext *context)
{
    s32 chan;
    EXIControl *exi;
    EXICallback callback;

    chan = (interrupt - __OS_INTERRUPT_EXI_0_EXI) / 3;
    exi = &Ecb[chan];
    EXIClearInterrupts(chan, TRUE, FALSE, FALSE);
    callback = exi->exiCallback;
    if (callback)
    {
        OSContext exceptionContext;

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);

        callback(chan, context);

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

static void TCIntrruptHandler(__OSInterrupt interrupt, OSContext *context)
{
    OSContext exceptionContext;
    s32 chan;
    EXIControl *exi;
    EXICallback callback;

    chan = (interrupt - __OS_INTERRUPT_EXI_0_TC) / 3;
    exi = &Ecb[chan];
    __OSMaskInterrupts(OS_INTERRUPTMASK(interrupt));
    EXIClearInterrupts(chan, FALSE, TRUE, FALSE);
    callback = exi->tcCallback;
    if (callback)
    {
        exi->tcCallback = 0;
        CompleteTransfer(chan);

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);

        callback(chan, context);

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

static void EXTIntrruptHandler(__OSInterrupt interrupt, OSContext *context)
{
    s32 chan;
    EXIControl *exi;
    EXICallback callback;

    chan = (interrupt - __OS_INTERRUPT_EXI_0_EXT) / 3;
    __OSMaskInterrupts((OS_INTERRUPTMASK_EXI_0_EXT | OS_INTERRUPTMASK_EXI_0_EXI) >> (3 * chan));
    exi = &Ecb[chan];
    callback = exi->extCallback;
    exi->state &= ~STATE_ATTACHED;
    if (callback)
    {
        OSContext exceptionContext;

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);

        exi->extCallback = 0;
        callback(chan, context);

        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

void EXIInit(void)
{
    u32 id;
    while (((REG(0, 3) & 0x1) == 1) || ((REG(1, 3) & 0x1) == 1) || ((REG(2, 3) & 0x1) == 1)) {
        continue;
    }

    __OSMaskInterrupts(OS_INTERRUPTMASK_EXI_0_EXI | OS_INTERRUPTMASK_EXI_0_TC | OS_INTERRUPTMASK_EXI_0_EXT | OS_INTERRUPTMASK_EXI_1_EXI
                       | OS_INTERRUPTMASK_EXI_1_TC | OS_INTERRUPTMASK_EXI_1_EXT | OS_INTERRUPTMASK_EXI_2_EXI | OS_INTERRUPTMASK_EXI_2_TC);

    REG(0, 0) = 0;
    REG(1, 0) = 0;
    REG(2, 0) = 0;

    REG(0, 0) = 0x00002000;

    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_0_EXI, EXIIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_0_TC, TCIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_0_EXT, EXTIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_1_EXI, EXIIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_1_TC, TCIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_1_EXT, EXTIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_2_EXI, EXIIntrruptHandler);
    __OSSetInterruptHandler(__OS_INTERRUPT_EXI_2_TC, TCIntrruptHandler);

    EXIGetID(0, 2, &IDSerialPort1);

    if (__OSInIPL) {
        __EXIProbeStartTime[0] = __EXIProbeStartTime[1] = 0;
        Ecb[0].idTime = Ecb[1].idTime = 0;
        __EXIProbe(0);
        __EXIProbe(1);
    } else if (EXIGetID(0, 0, &id) && id == 0x07010000) {
        __OSEnableBarnacle(1, 0);
    } else if (EXIGetID(1, 0, &id) && id == 0x07010000) {
        __OSEnableBarnacle(0, 2);
    }

    OSRegisterVersion(__EXIVersion);
}

BOOL EXILock(s32 chan, u32 dev, EXICallback unlockedCallback)
{
    EXIControl *exi = &Ecb[chan];
    BOOL enabled;
    int i;

    enabled = OSDisableInterrupts();
    if (exi->state & STATE_LOCKED)
    {
        if (unlockedCallback)
        {
            for (i = 0; i < exi->items; i++)
            {
                if (exi->queue[i].dev == dev)
                {
                    OSRestoreInterrupts(enabled);
                    return FALSE;
                }
            }
            exi->queue[exi->items].callback = unlockedCallback;
            exi->queue[exi->items].dev = dev;
            exi->items++;
        }
        OSRestoreInterrupts(enabled);
        return FALSE;
    }

    exi->state |= STATE_LOCKED;
    exi->dev = dev;
    SetExiInterruptMask(chan, exi);

    OSRestoreInterrupts(enabled);
    return TRUE;
}

BOOL EXIUnlock(s32 chan)
{
    EXIControl *exi = &Ecb[chan];
    BOOL enabled;
    EXICallback unlockedCallback;

    enabled = OSDisableInterrupts();
    if (!(exi->state & STATE_LOCKED))
    {
        OSRestoreInterrupts(enabled);
        return FALSE;
    }
    exi->state &= ~STATE_LOCKED;
    SetExiInterruptMask(chan, exi);

    if (0 < exi->items)
    {
        unlockedCallback = exi->queue[0].callback;
        if (0 < --exi->items)
        {
            memmove(&exi->queue[0], &exi->queue[1], sizeof(exi->queue[0]) * exi->items);
        }
        unlockedCallback(chan, 0);
    }

    OSRestoreInterrupts(enabled);
    return TRUE;
}

u32 EXIGetState(s32 chan)
{
    EXIControl *exi = &Ecb[chan];

    return (u32)exi->state;
}

static void UnlockedHandler(s32 chan, OSContext *context)
{
    u32 id;

    EXIGetID(chan, 0, &id);
}

s32 EXIGetID(s32 chan, u32 dev, u32* id)
{
    EXIControl* exi = &Ecb[chan];
    BOOL err;
    u32 cmd;
    s32 startTime;
    BOOL enabled;
    BOOL interrupt;

    if (chan == 0 && dev == 2 && IDSerialPort1) {
        *id = IDSerialPort1;
        return 1;
    }

    if (chan < 2 && dev == 0) {
        if (!__EXIProbe(chan)) {
            return 0;
        }

        if (exi->idTime == __EXIProbeStartTime[chan]) {
            *id = exi->id;
            return exi->idTime;
        }

        if (!__EXIAttach(chan, NULL)) {
            return 0;
        }
        startTime = __EXIProbeStartTime[chan];
    }

    interrupt = OSDisableInterrupts();
    err       = !EXILock(chan, dev, (chan < 2 && dev == 0) ? UnlockedHandler : NULL);
    if (!err) {
        err = !EXISelect(chan, dev, EXI_FREQ_1M);
        if (!err) {
            cmd = 0;
            err |= !EXIImm(chan, &cmd, 2, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, id, 4, EXI_READ, NULL);
            err |= !EXISync(chan);
            err |= !EXIDeselect(chan);
        }
        EXIUnlock(chan);
    }
    OSRestoreInterrupts(interrupt);

    if (chan < 2 && dev == 0) {
        EXIDetach(chan);
        enabled = OSDisableInterrupts();
        err |= (startTime != __EXIProbeStartTime[chan]);
        if (!err) {
            exi->id     = *id;
            exi->idTime = startTime;
        }
        OSRestoreInterrupts(enabled);

        return err ? 0 : exi->idTime;
    }

    return err ? 0 : !0;
}

s32 EXIGetType(s32 chan, u32 dev, u32 *type) {
    u32 _type;
    s32 probe;

    probe = EXIGetID(chan, dev, &_type);
    if(probe == 0)
        return probe;

    switch(_type & 0xffffff00)
    {
    case 0x4020100:
    case 0x4020200:
    case 0x4020300:
    case 0x4060000:
        *type = _type & 0xffffff00;
        return probe;
    }

    switch(_type & 0xffff0000)
    {
    case 0:
    {
        if ((_type & 0x3803))
            break;

        switch (_type & 0xfc)
        {
        case 4:
        case 8:
        case 16:
        case 32:
        case 64:
        case 128:
            *type = _type  & 0xfc;
            return probe;
        }
        break;
    }
    case 0x5070000:
        *type = 0x5070000;
        return probe;
    }
    *type = _type;
    return probe;
}

char* EXIGetTypeString(u32 type)
{
    switch (type) {
    case EXI_MEMORY_CARD_59:
        return "Memory Card 59";
    case EXI_MEMORY_CARD_123:
        return "Memory Card 123";
    case EXI_MEMORY_CARD_251:
        return "Memory Card 251";
    case EXI_MEMORY_CARD_507:
        return "Memory Card 507";
    case EXI_MEMORY_CARD_1019:
        return "Memory Card 1019";
    case EXI_MEMORY_CARD_2043:
        return "Memory Card 2043";
    case EXI_USB_ADAPTER:
        return "USB Adapter";
    case 0x80000000 | EXI_MEMORY_CARD_59:
    case 0x80000000 | EXI_MEMORY_CARD_123:
    case 0x80000000 | EXI_MEMORY_CARD_251:
    case 0x80000000 | EXI_MEMORY_CARD_507:
        return "Net Card";
    case EXI_ETHER_VIEWER:
        return "Artist Ether";
    case EXI_MODEM:
        return "Broadband Adapter";
    case EXI_STREAM_HANGER:
        return "Stream Hanger";
    case EXI_IS_VIEWER:
        return "IS-DOL-VIEWER";
    }
}

#pragma scheduling reset
