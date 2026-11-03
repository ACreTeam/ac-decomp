#include <dolphin/pad.h>
#include <dolphin/sipriv.h>

const char *__PADVersion = "<< Dolphin SDK - PAD\trelease build: Aug  6 2003 04:30:02 (0x2301) >>";

u8 UnkVal : (OS_BASE_CACHED | 0x30E3);
u16 __OSWirelessPadFixMode : (OS_BASE_CACHED | 0x30E0);

static void PADTypeAndStatusCallback(s32 chan, u32 type);
static void PADOriginCallback(s32 chan, u32 error, OSContext *context);
static void PADProbeCallback(s32 chan, u32 error, OSContext *context);
static void SPEC0_MakeStatus(s32 chan, PADStatus *status, u32 data[2]);
static void SPEC1_MakeStatus(s32 chan, PADStatus *status, u32 data[2]);
static void SPEC2_MakeStatus(s32 chan, PADStatus *status, u32 data[2]);
static void PADTypeAndStatusCallback(s32 chan, u32 type);

static void PADOriginCallback(s32 chan, u32 error, OSContext *context);
static void PADProbeCallback(s32 chan, u32 error, OSContext *context);

static void SPEC0_MakeStatus(s32 chan, PADStatus *status, u32 data[2]);
static void SPEC1_MakeStatus(s32 chan, PADStatus *status, u32 data[2]);
static void SPEC2_MakeStatus(s32 chan, PADStatus *status, u32 data[2]);

static BOOL Initialized;

static u32 EnabledBits;
static u32 ResettingBits;
static s32 ResettingChan = 32;
static u32 RecalibrateBits;
static u32 WaitingBits;
static u32 CheckingBits;
static u32 PendingBits;
static u32 BarrelBits;

static u32 XPatchBits = PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT;

static u32 AnalogMode = 0x00000300u;

u32 __PADSpec;
static u32 Spec = 5;
static void (*MakeStatus)(s32, PADStatus *, u32[2]) = SPEC2_MakeStatus;

static u32 Type[SI_MAX_CHAN];
static PADStatus Origin[SI_MAX_CHAN];

static u32 CmdReadOrigin = 0x41 << 24;
static u32 CmdCalibrate = 0x42 << 24;
static u32 CmdProbeDevice[SI_MAX_CHAN];

static BOOL OnReset(BOOL final);

static OSResetFunctionInfo ResetFunctionInfo = {OnReset, 127};

static void (*SamplingCallback)(void);

static void PADEnable(s32 chan)
{
    u32 cmd;
    u32 chanBit;
    u32 data[2];

    chanBit = PAD_CHAN0_BIT >> chan;
    EnabledBits |= chanBit;
    SIGetResponse(chan, data);
    cmd = (0x40 << 16) | AnalogMode;
    SISetCommand(chan, cmd);
    SIEnablePolling(EnabledBits);
}

static void PADDisable(s32 chan)
{
    BOOL enabled;
    u32 chanBit;

    enabled = OSDisableInterrupts();

    chanBit = PAD_CHAN0_BIT >> chan;
    SIDisablePolling(chanBit);
    EnabledBits &= ~chanBit;
    WaitingBits &= ~chanBit;
    CheckingBits &= ~chanBit;
    PendingBits &= ~chanBit;
    BarrelBits &= ~chanBit;
    OSSetWirelessID(chan, 0);

    OSRestoreInterrupts(enabled);
}

static void DoReset(void)
{
    u32 chanBit;

    ResettingChan = __cntlzw(ResettingBits);
    if (ResettingChan == 32)
    {
        return;
    }

    chanBit = PAD_CHAN0_BIT >> ResettingChan;
    ResettingBits &= ~chanBit;

    memset(&Origin[ResettingChan], 0, sizeof(PADStatus));
    SIGetTypeAsync(ResettingChan, PADTypeAndStatusCallback);
}

static void UpdateOrigin(s32 chan)
{
    PADStatus *origin;
    u32 chanBit = PAD_CHAN0_BIT >> chan;

    origin = &Origin[chan];
    switch (AnalogMode & 0x00000700u)
    {
    case 0x00000000u:
    case 0x00000500u:
    case 0x00000600u:
    case 0x00000700u:
        origin->triggerLeft &= ~15;
        origin->triggerRight &= ~15;
        origin->analogA &= ~15;
        origin->analogB &= ~15;
        break;
    case 0x00000100u:
        origin->substickX &= ~15;
        origin->substickY &= ~15;
        origin->analogA &= ~15;
        origin->analogB &= ~15;
        break;
    case 0x00000200u:
        origin->substickX &= ~15;
        origin->substickY &= ~15;
        origin->triggerLeft &= ~15;
        origin->triggerRight &= ~15;
        break;
    case 0x00000300u:
        break;
    case 0x00000400u:
        break;
    }

    origin->stickX -= 128;
    origin->stickY -= 128;
    origin->substickX -= 128;
    origin->substickY -= 128;

    if (XPatchBits & chanBit)
    {
        if (64 < origin->stickX && (SIGetType(chan) & 0xffff0000) == SI_GC_CONTROLLER)
        {
            origin->stickX = 0;
        }
    }
}

static void PADOriginCallback(s32 chan, u32 error, OSContext *context)
{
    if (!(error &
          (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN | SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION)))
    {
        UpdateOrigin(ResettingChan);
        PADEnable(ResettingChan);
    }
    DoReset();
}

static void PADOriginUpdateCallback(s32 chan, u32 error, OSContext *context)
{

    if (!(EnabledBits & (PAD_CHAN0_BIT >> chan)))
    {
        return;
    }

    if (!(error &
          (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN | SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION)))
    {
        UpdateOrigin(chan);
    }

    if (error & SI_ERROR_NO_RESPONSE)
    {
        PADDisable(chan);
    }
}

static void PADProbeCallback(s32 chan, u32 error, OSContext *context)
{
    if (!(error &
          (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN | SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION)))
    {
        PADEnable(ResettingChan);
        WaitingBits |= PAD_CHAN0_BIT >> ResettingChan;
    }
    DoReset();
}

static void PADTypeAndStatusCallback(s32 chan, u32 type)
{
    u32 chanBit;
    u32 recalibrate;
    BOOL rc = TRUE;
    u32 error;
    chanBit = PAD_CHAN0_BIT >> ResettingChan;
    error = type & 0xFF;
    recalibrate = RecalibrateBits & chanBit;
    RecalibrateBits &= ~chanBit;

    if (error &
        (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN | SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION))
    {
        DoReset();
        return;
    }

    type &= ~0xFF;

    Type[ResettingChan] = type;

    if ((type & SI_TYPE_MASK) != SI_TYPE_GC || !(type & SI_GC_STANDARD))
    {
        DoReset();
        return;
    }

    if (Spec < PAD_SPEC_2)
    {
        PADEnable(ResettingChan);
        DoReset();
        return;
    }

    if (!(type & SI_GC_WIRELESS) || (type & SI_WIRELESS_IR))
    {
        if (recalibrate)
        {
            rc = SITransfer(ResettingChan, &CmdCalibrate, 3, &Origin[ResettingChan], 10,
                            PADOriginCallback, 0);
        }
        else
        {
            rc = SITransfer(ResettingChan, &CmdReadOrigin, 1, &Origin[ResettingChan], 10,
                            PADOriginCallback, 0);
        }
    }
    else if ((type & SI_WIRELESS_FIX_ID) && (type & SI_WIRELESS_CONT_MASK) == SI_WIRELESS_CONT &&
             !(type & SI_WIRELESS_LITE))
    {
        if (type & SI_WIRELESS_RECEIVED)
        {
            rc = SITransfer(ResettingChan, &CmdReadOrigin, 1, &Origin[ResettingChan], 10,
                            PADOriginCallback, 0);
        }
        else
        {
            rc = SITransfer(ResettingChan, &CmdProbeDevice[ResettingChan], 3, &Origin[ResettingChan], 8,
                            PADProbeCallback, 0);
        }
    }
    if (!rc)
    {
        PendingBits |= chanBit;
        DoReset();
        return;
    }
}

static void PADReceiveCheckCallback(s32 chan, u32 type)
{
    u32 error;
    u32 chanBit;

    chanBit = PAD_CHAN0_BIT >> chan;
    if (!(EnabledBits & chanBit))
    {
        return;
    }

    error = type & 0xFF;
    type &= ~0xFF;

    WaitingBits &= ~chanBit;
    CheckingBits &= ~chanBit;

    if (!(error &
          (SI_ERROR_UNDER_RUN | SI_ERROR_OVER_RUN | SI_ERROR_NO_RESPONSE | SI_ERROR_COLLISION)) &&
        (type & SI_GC_WIRELESS) && (type & SI_WIRELESS_FIX_ID) && (type & SI_WIRELESS_RECEIVED) &&
        !(type & SI_WIRELESS_IR) && (type & SI_WIRELESS_CONT_MASK) == SI_WIRELESS_CONT &&
        !(type & SI_WIRELESS_LITE))
    {
        SITransfer(chan, &CmdReadOrigin, 1, &Origin[chan], 10, PADOriginUpdateCallback, 0);
    }
    else
    {
        PADDisable(chan);
    }
}

#pragma push
#pragma auto_inline off // fakematch most likely

BOOL PADReset(u32 mask)
{
    BOOL enabled;
    u32 diableBits;

    enabled = OSDisableInterrupts();

    mask |= PendingBits;
    PendingBits = 0;
    mask &= ~(WaitingBits | CheckingBits);
    ResettingBits |= mask;
    diableBits = ResettingBits & EnabledBits;
    EnabledBits &= ~mask;
    BarrelBits &= ~mask;

    if (Spec == PAD_SPEC_4)
    {
        RecalibrateBits |= mask;
    }

    SIDisablePolling(diableBits);

    if (ResettingChan == 32)
    {
        DoReset();
    }
    OSRestoreInterrupts(enabled);
    return TRUE;
}

BOOL PADRecalibrate(u32 mask)
{
    BOOL enabled;
    u32 disableBits;

    enabled = OSDisableInterrupts();

    mask |= PendingBits;
    PendingBits = 0;
    mask &= ~(WaitingBits | CheckingBits);
    ResettingBits |= mask;
    disableBits = ResettingBits & EnabledBits;
    EnabledBits &= ~mask;
    BarrelBits &= ~mask;

    if (!(UnkVal & 0x40))
    {
        RecalibrateBits |= mask;
    }

    SIDisablePolling(disableBits);
    if (ResettingChan == 32)
    {
        DoReset();
    }
    OSRestoreInterrupts(enabled);
    return TRUE;
}

BOOL PADInit()
{
    s32 chan;
    if (Initialized)
    {
        return TRUE;
    }

    OSRegisterVersion(__PADVersion);

    if (__PADSpec)
    {
        PADSetSpec(__PADSpec);
    }

    Initialized = TRUE;

    if (__PADFixBits != 0)
    {
        OSTime time = OSGetTime();
        __OSWirelessPadFixMode = (u16)((((time)&0xffff) + ((time >> 16) & 0xffff) +
                                        ((time >> 32) & 0xffff) + ((time >> 48) & 0xffff)) &
                                       0x3fffu);
        RecalibrateBits = PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT;
    }

    for (chan = 0; chan < SI_MAX_CHAN; ++chan)
    {
        CmdProbeDevice[chan] = (0x4D << 24) | (chan << 22) | ((__OSWirelessPadFixMode & 0x3fffu) << 8);
    }

    SIRefreshSamplingRate();
    OSRegisterResetFunction(&ResetFunctionInfo);

    return PADReset((PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT));
}




u32 PADRead(PADStatus *status)
{
    BOOL enabled;
    s32 chan;
    u32 data[2];
    u32 chanBit;
    u32 sr;
    int chanShift;
    u32 motor;

    enabled = OSDisableInterrupts();

    motor = 0;
    for (chan = 0; chan < SI_MAX_CHAN; chan++, status++)
    {
        chanBit = PAD_CHAN0_BIT >> chan;
        chanShift = 8 * (SI_MAX_CHAN - 1 - chan);

        if (PendingBits & chanBit)
        {
            PADReset(0);
            status->err = PAD_ERR_NOT_READY;
            memset(status, 0, offsetof(PADStatus, err));
            continue;
        }

        if ((ResettingBits & chanBit) || ResettingChan == chan)
        {
            status->err = PAD_ERR_NOT_READY;
            memset(status, 0, offsetof(PADStatus, err));
            continue;
        }

        if (!(EnabledBits & chanBit))
        {
            status->err = (s8)PAD_ERR_NO_CONTROLLER;
            memset(status, 0, offsetof(PADStatus, err));
            continue;
        }

        if (SIIsChanBusy(chan))
        {
            status->err = PAD_ERR_TRANSFER;
            memset(status, 0, offsetof(PADStatus, err));
            continue;
        }

        sr = SIGetStatus(chan);
        if (sr & SI_ERROR_NO_RESPONSE)
        {
            SIGetResponse(chan, data);

            if (WaitingBits & chanBit)
            {
                status->err = (s8)PAD_ERR_NONE;
                memset(status, 0, offsetof(PADStatus, err));

                if (!(CheckingBits & chanBit))
                {
                    CheckingBits |= chanBit;
                    SIGetTypeAsync(chan, PADReceiveCheckCallback);
                }
                continue;
            }

            PADDisable(chan);

            status->err = (s8)PAD_ERR_NO_CONTROLLER;
            memset(status, 0, offsetof(PADStatus, err));
            continue;
        }

        if (!(SIGetType(chan) & SI_GC_NOMOTOR))
        {
            motor |= chanBit;
        }

        if (!SIGetResponse(chan, data))
        {
            status->err = PAD_ERR_TRANSFER;
            memset(status, 0, offsetof(PADStatus, err));
            continue;
        }

        if (data[0] & 0x80000000)
        {
            status->err = PAD_ERR_TRANSFER;
            memset(status, 0, offsetof(PADStatus, err));
            continue;
        }

        MakeStatus(chan, status, data);

        // Check and clear PAD_ORIGIN bit
        if (status->button & 0x2000)
        {
            status->err = PAD_ERR_TRANSFER;
            memset(status, 0, offsetof(PADStatus, err));

            // Get origin. It is okay if the following transfer fails
            // since the PAD_ORIGIN bit remains until the read origin
            // command complete.
            SITransfer(chan, &CmdReadOrigin, 1, &Origin[chan], 10, PADOriginUpdateCallback, 0);
            continue;
        }

        status->err = PAD_ERR_NONE;

        // Clear PAD_INTERFERE bit
        status->button &= ~0x0080;
    }

    OSRestoreInterrupts(enabled);
    return motor;
}

#pragma pop

void PADControlAllMotors(const u32 *commandArray)
{
    BOOL enabled;
    int chan;
    u32 command;
    BOOL commit;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    commit = FALSE;
    for (chan = 0; chan < SI_MAX_CHAN; chan++, commandArray++)
    {
        chanBit = PAD_CHAN0_BIT >> chan;
        if ((EnabledBits & chanBit) && !(SIGetType(chan) & SI_GC_NOMOTOR))
        {
            command = *commandArray;
            if (Spec < PAD_SPEC_2 && command == PAD_MOTOR_STOP_HARD)
            {
                command = PAD_MOTOR_STOP;
            }

            if (UnkVal & 0x20)
            {
                command = PAD_MOTOR_STOP;
            }

            SISetCommand(chan, (0x40 << 16) | AnalogMode | (command & (0x00000001 | 0x00000002)));
            commit = TRUE;
        }
    }
    if (commit)
    {
        SITransferCommands();
    }
    OSRestoreInterrupts(enabled);
}

void PADControlMotor(s32 chan, u32 command)
{
    BOOL enabled;
    u32 chanBit;

    enabled = OSDisableInterrupts();
    chanBit = PAD_CHAN0_BIT >> chan;
    if ((EnabledBits & chanBit) && !(SIGetType(chan) & SI_GC_NOMOTOR))
    {
        if (Spec < PAD_SPEC_2 && command == PAD_MOTOR_STOP_HARD)
        {
            command = PAD_MOTOR_STOP;
        }

        if (UnkVal & 0x20)
        {
            command = PAD_MOTOR_STOP;
        }

        SISetCommand(chan, (0x40 << 16) | AnalogMode | (command & (0x00000001 | 0x00000002)));
        SITransferCommands();
    }
    OSRestoreInterrupts(enabled);
}

void PADSetSpec(u32 spec)
{
    __PADSpec = 0;
    switch (spec)
    {
    case PAD_SPEC_0:
        MakeStatus = SPEC0_MakeStatus;
        break;
    case PAD_SPEC_1:
        MakeStatus = SPEC1_MakeStatus;
        break;
    case PAD_SPEC_2:
    case PAD_SPEC_3:
    case PAD_SPEC_4:
    case PAD_SPEC_5:
        MakeStatus = SPEC2_MakeStatus;
        break;
    }
    Spec = spec;
}

u32 PADGetSpec(void) { return Spec; }

static void SPEC0_MakeStatus(s32 chan, PADStatus *status, u32 data[2])
{
    status->button = 0;
    status->button |= ((data[0] >> 16) & 0x0008) ? PAD_BUTTON_A : 0;
    status->button |= ((data[0] >> 16) & 0x0020) ? PAD_BUTTON_B : 0;
    status->button |= ((data[0] >> 16) & 0x0100) ? PAD_BUTTON_X : 0;
    status->button |= ((data[0] >> 16) & 0x0001) ? PAD_BUTTON_Y : 0;
    status->button |= ((data[0] >> 16) & 0x0010) ? PAD_BUTTON_START : 0;
    status->stickX = (s8)(data[1] >> 16);
    status->stickY = (s8)(data[1] >> 24);
    status->substickX = (s8)(data[1]);
    status->substickY = (s8)(data[1] >> 8);
    status->triggerLeft = (u8)(data[0] >> 8);
    status->triggerRight = (u8)data[0];
    status->analogA = 0;
    status->analogB = 0;
    if (170 <= status->triggerLeft)
    {
        status->button |= PAD_TRIGGER_L;
    }
    if (170 <= status->triggerRight)
    {
        status->button |= PAD_TRIGGER_R;
    }
    status->stickX -= 128;
    status->stickY -= 128;
    status->substickX -= 128;
    status->substickY -= 128;
}

static void SPEC1_MakeStatus(s32 chan, PADStatus *status, u32 data[2])
{

    status->button = 0;
    status->button |= ((data[0] >> 16) & 0x0080) ? PAD_BUTTON_A : 0;
    status->button |= ((data[0] >> 16) & 0x0100) ? PAD_BUTTON_B : 0;
    status->button |= ((data[0] >> 16) & 0x0020) ? PAD_BUTTON_X : 0;
    status->button |= ((data[0] >> 16) & 0x0010) ? PAD_BUTTON_Y : 0;
    status->button |= ((data[0] >> 16) & 0x0200) ? PAD_BUTTON_START : 0;

    status->stickX = (s8)(data[1] >> 16);
    status->stickY = (s8)(data[1] >> 24);
    status->substickX = (s8)(data[1]);
    status->substickY = (s8)(data[1] >> 8);

    status->triggerLeft = (u8)(data[0] >> 8);
    status->triggerRight = (u8)data[0];

    status->analogA = 0;
    status->analogB = 0;

    if (170 <= status->triggerLeft)
    {
        status->button |= PAD_TRIGGER_L;
    }
    if (170 <= status->triggerRight)
    {
        status->button |= PAD_TRIGGER_R;
    }

    status->stickX -= 128;
    status->stickY -= 128;
    status->substickX -= 128;
    status->substickY -= 128;
}

static s8 ClampS8(s8 var, s8 org)
{
    if (0 < org)
    {
        s8 min = (s8)(-128 + org);
        if (var < min)
        {
            var = min;
        }
    }
    else if (org < 0)
    {
        s8 max = (s8)(127 + org);
        if (max < var)
        {
            var = max;
        }
    }
    return var -= org;
}

static u8 ClampU8(u8 var, u8 org)
{
    if (var < org)
    {
        var = org;
    }
    return var -= org;
}

#define PAD_ALL                                                                                  \
    (PAD_BUTTON_LEFT | PAD_BUTTON_RIGHT | PAD_BUTTON_DOWN | PAD_BUTTON_UP | PAD_TRIGGER_Z |      \
     PAD_TRIGGER_R | PAD_TRIGGER_L | PAD_BUTTON_A | PAD_BUTTON_B | PAD_BUTTON_X | PAD_BUTTON_Y | \
     PAD_BUTTON_MENU | 0x2000 | 0x0080)

static void SPEC2_MakeStatus(s32 chan, PADStatus *status, u32 data[2])
{
    PADStatus *origin;

    status->button = (u16)((data[0] >> 16) & PAD_ALL);
    status->stickX = (s8)(data[0] >> 8);
    status->stickY = (s8)(data[0]);

    switch (AnalogMode & 0x00000700)
    {
    case 0x00000000:
    case 0x00000500:
    case 0x00000600:
    case 0x00000700:
        status->substickX = (s8)(data[1] >> 24);
        status->substickY = (s8)(data[1] >> 16);
        status->triggerLeft = (u8)(((data[1] >> 12) & 0x0f) << 4);
        status->triggerRight = (u8)(((data[1] >> 8) & 0x0f) << 4);
        status->analogA = (u8)(((data[1] >> 4) & 0x0f) << 4);
        status->analogB = (u8)(((data[1] >> 0) & 0x0f) << 4);
        break;
    case 0x00000100:
        status->substickX = (s8)(((data[1] >> 28) & 0x0f) << 4);
        status->substickY = (s8)(((data[1] >> 24) & 0x0f) << 4);
        status->triggerLeft = (u8)(data[1] >> 16);
        status->triggerRight = (u8)(data[1] >> 8);
        status->analogA = (u8)(((data[1] >> 4) & 0x0f) << 4);
        status->analogB = (u8)(((data[1] >> 0) & 0x0f) << 4);
        break;
    case 0x00000200:
        status->substickX = (s8)(((data[1] >> 28) & 0x0f) << 4);
        status->substickY = (s8)(((data[1] >> 24) & 0x0f) << 4);
        status->triggerLeft = (u8)(((data[1] >> 20) & 0x0f) << 4);
        status->triggerRight = (u8)(((data[1] >> 16) & 0x0f) << 4);
        status->analogA = (u8)(data[1] >> 8);
        status->analogB = (u8)(data[1] >> 0);
        break;
    case 0x00000300:
        status->substickX = (s8)(data[1] >> 24);
        status->substickY = (s8)(data[1] >> 16);
        status->triggerLeft = (u8)(data[1] >> 8);
        status->triggerRight = (u8)(data[1] >> 0);
        status->analogA = 0;
        status->analogB = 0;
        break;
    case 0x00000400:
        status->substickX = (s8)(data[1] >> 24);
        status->substickY = (s8)(data[1] >> 16);
        status->triggerLeft = 0;
        status->triggerRight = 0;
        status->analogA = (u8)(data[1] >> 8);
        status->analogB = (u8)(data[1] >> 0);
        break;
    }

    status->stickX -= 128;
    status->stickY -= 128;
    status->substickX -= 128;
    status->substickY -= 128;

    if ((Type[chan] & 0xffff0000) == SI_GC_CONTROLLER && (((status->button) & 0x80) ^ 0x80))
    {
        BarrelBits |= PAD_CHAN0_BIT >> chan;
        status->stickX = 0;
        status->stickY = 0;
        status->substickX = 0;
        status->substickY = 0;
    }
    else {
        BarrelBits &= ~(PAD_CHAN0_BIT >> chan);
        origin = &Origin[chan];
        status->stickX = ClampS8(status->stickX, origin->stickX);
        status->stickY = ClampS8(status->stickY, origin->stickY);
        status->substickX = ClampS8(status->substickX, origin->substickX);
        status->substickY = ClampS8(status->substickY, origin->substickY);
        status->triggerLeft = ClampU8(status->triggerLeft, origin->triggerLeft);
        status->triggerRight = ClampU8(status->triggerRight, origin->triggerRight);
    }


}

BOOL PADGetType(s32 chan, u32 *type)
{
    u32 chanBit;

    *type = SIGetType(chan);
    chanBit = PAD_CHAN0_BIT >> chan;
    if ((ResettingBits & chanBit) || ResettingChan == chan || !(EnabledBits & chanBit))
    {
        return FALSE;
    }
    return TRUE;
}

BOOL PADSync(void) { return ResettingBits == 0 && ResettingChan == 32 && !SIBusy(); }

void PADSetAnalogMode(u32 mode)
{
    BOOL enabled;
    u32 mask;

    enabled = OSDisableInterrupts();
    AnalogMode = mode << 8;
    mask = EnabledBits;

    EnabledBits &= ~mask;
    WaitingBits &= ~mask;
    CheckingBits &= ~mask;

    SIDisablePolling(mask);
    OSRestoreInterrupts(enabled);
}

static BOOL OnReset(BOOL f)
{
    static BOOL recalibrated = FALSE;
    BOOL sync;

    if (SamplingCallback)
    {
        PADSetSamplingCallback(NULL);
    }

    if (!f)
    {
        sync = PADSync();
        if (!recalibrated && sync)
        {
            recalibrated = PADRecalibrate(PAD_CHAN0_BIT | PAD_CHAN1_BIT | PAD_CHAN2_BIT | PAD_CHAN3_BIT);
            return FALSE;
        }
        return sync;
    }
    else
    {
        recalibrated = FALSE;
    }

    return TRUE;
}

void __PADDisableXPatch(void) { XPatchBits = 0; }

static void SamplingHandler(__OSInterrupt interrupt, OSContext *context)
{
    OSContext exceptionContext;

    if (SamplingCallback)
    {
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(&exceptionContext);
        SamplingCallback();
        OSClearContext(&exceptionContext);
        OSSetCurrentContext(context);
    }
}

PADSamplingCallback PADSetSamplingCallback(PADSamplingCallback callback)
{
    PADSamplingCallback prev;

    prev = SamplingCallback;
    SamplingCallback = callback;
    if (callback)
    {
        SIRegisterPollingHandler(SamplingHandler);
    }
    else
    {
        SIUnregisterPollingHandler(SamplingHandler);
    }
    return prev;
}

BOOL __PADDisableRecalibration(BOOL disable)
{
    BOOL enabled;
    BOOL prev;

    enabled = OSDisableInterrupts();
    prev = (UnkVal & 0x40) ? TRUE : FALSE;
    UnkVal &= ~0x40;
    if (disable)
    {
        UnkVal |= 0x40;
    }
    OSRestoreInterrupts(enabled);
    return prev;
}