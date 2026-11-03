#include <dolphin/exi.h>
#include "dolphin/os.h"

#define EXI_TX 0x800400u
#define EXI_MAGIC 0xa5ff005a

static s32 Chan;
static u32 Dev;
static u32 Enabled = 0;
static u32 BarnacleEnabled = 0;

static BOOL ProbeBarnacle(s32 chan, u32 dev, u32 *revision)
{
    BOOL err;
    u32 cmd;

    if (chan != 2 && dev == 0 && !EXIAttach(chan, NULL))
    {
        return FALSE;
    }

    err = !EXILock(chan, dev, NULL);
    if (!err)
    {
        err = !EXISelect(chan, dev, EXI_FREQ_1M);
        if (!err)
        {
            cmd = 0x20011300;
            err = FALSE;
            err |= !EXIImm(chan, &cmd, 4, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, revision, 4, EXI_READ, NULL);
            err |= !EXISync(chan);
            err |= !EXIDeselect(chan);
        }
        EXIUnlock(chan);
    }

    if (chan != 2 && dev == 0)
    {
        EXIDetach(chan);
    }

    if (err)
    {
        return FALSE;
    }

    return (*revision != 0xFFFFFFFF) ? TRUE : FALSE;
}

void __OSEnableBarnacle(s32 chan, u32 dev)
{
    u32 id;

    if (EXIGetID(chan, dev, &id))
    {
        switch (id)
        {
        case 0xffffffff:
        case EXI_MEMORY_CARD_59:
        case EXI_MEMORY_CARD_123:
        case EXI_MEMORY_CARD_251:
        case EXI_MEMORY_CARD_507:
        case EXI_USB_ADAPTER:
        case EXI_NPDP_GDEV:
        case EXI_MODEM:
        case EXI_MARLIN:
        case 0x04220000:
        case 0x04020100:
        case 0x04020200:
        case 0x04020300:
        case 0x04040404:
        case 0x04060000:
        case 0x04120000:
        case 0x04130000:
        case 0x80000000 | EXI_MEMORY_CARD_59:
        case 0x80000000 | EXI_MEMORY_CARD_123:
        case 0x80000000 | EXI_MEMORY_CARD_251:
        case 0x80000000 | EXI_MEMORY_CARD_507:
            break;
        default:
            if (ProbeBarnacle(chan, dev, &id))
            {
                Chan = chan;
                Dev = dev;
                Enabled = BarnacleEnabled = EXI_MAGIC;
            }
            break;
        }
    }
}

u32 InitializeUART(u32 baudRate)
{
    if (BarnacleEnabled == EXI_MAGIC)
    {
        return 0;
    }

    if (!(OSGetConsoleType() & OS_CONSOLE_DEVELOPMENT))
    {
        Enabled = 0;
        return 2;
    }
    else
    {
        Chan = 0;
        Dev = 1;
        Enabled = EXI_MAGIC;
        return 0;
    }
}

u32 ReadUARTN(void *bytes, unsigned long length) { return 4; }

static int QueueLength(void)
{
    u32 cmd;

    if (!EXISelect(Chan, Dev, EXI_FREQ_8M))
        return -1;

    cmd = EXI_TX << 6;
    EXIImm(Chan, &cmd, 4, EXI_WRITE, NULL);
    EXISync(Chan);

    EXIImm(Chan, &cmd, 1, EXI_READ, NULL);
    EXISync(Chan);
    EXIDeselect(Chan);

    return 16 - (int)((cmd >> 24) & 0xff);
}

u32 WriteUARTN(const void *buf, unsigned long len)
{
    BOOL enabled;
    u32 cmd;
    int qLen;
    long xLen;
    char *ptr;
    BOOL locked;
    u32 error;

    if (Enabled != EXI_MAGIC)
        return 2;

    enabled = OSDisableInterrupts();

    locked = EXILock(Chan, Dev, 0);
    if (!locked)
    {
        OSRestoreInterrupts(enabled);
        return 0;
    }

    for (ptr = (char *)buf; ptr - buf < len; ptr++)
    {
        if (*ptr == '\n')
            *ptr = '\r';
    }

    error = 0;
    cmd = (EXI_TX | 0x2000000) << 6;
    while (len)
    {
        qLen = QueueLength();
        if (qLen < 0)
        {
            error = 3;
            break;
        }

        if (qLen < 12 && qLen < len)
            continue;

        if (!EXISelect(Chan, Dev, EXI_FREQ_8M))
        {
            error = 3;
            break;
        }

        EXIImm(Chan, &cmd, 4, EXI_WRITE, NULL);
        EXISync(Chan);

        while (qLen && len)
        {
            if (qLen < 4 && qLen < len)
                break;
            xLen = (len < 4) ? (long)len : 4;
            EXIImm(Chan, (void *)buf, xLen, EXI_WRITE, NULL);
            (u8 *)buf += xLen;
            len -= xLen;
            qLen -= xLen;
            EXISync(Chan);
        }
        EXIDeselect(Chan);
    }

    EXIUnlock(Chan);
    OSRestoreInterrupts(enabled);
    return error;
}