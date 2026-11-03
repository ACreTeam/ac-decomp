#include <dolphin/DVDPriv.h>
#include <dolphin/dvd.h>
#include <dolphin/hw_regs.h>
#include <dolphin/os.h>
#include <dolphin/os/OSBootInfo.h>

const char *__DVDVersion = "<< Dolphin SDK - DVD\trelease build: Jul 23 2003 11:27:57 (0x2301) >>";

typedef void (*stateFunc)(DVDCommandBlock *block);
stateFunc LastState;

static DVDBB2 BB2 ALIGN(32);
static DVDDiskID CurrDiskID ALIGN(32);
static DVDCommandBlock *executing;
static DVDDiskID *IDShouldBe;
static OSBootInfo *bootInfo;
static BOOL autoInvalidation = TRUE;
static volatile BOOL PauseFlag = FALSE;
static volatile BOOL PausingFlag = FALSE;
static volatile BOOL AutoFinishing = FALSE;
static volatile BOOL FatalErrorFlag = FALSE;
static vu32 CurrCommand;
static vu32 Canceling = FALSE;
static DVDCBCallback CancelCallback;
static vu32 ResumeFromHere = 0;
static vu32 CancelLastError;
static vu32 LastError;
static vs32 NumInternalRetry = 0;
static volatile BOOL ResetRequired;
static volatile BOOL CancelAllSyncComplete = FALSE;
static volatile BOOL FirstTimeInBootrom = FALSE;

static DVDCommandBlock DummyCommandBlock;
static OSAlarm ResetAlarm;

static BOOL DVDInitialized = FALSE;

/* States */
static void stateReadingFST();
static void stateTimeout();
static void stateGettingError();
static void stateGoToRetry();
static void stateCheckID();
static void stateCheckID3();
static void stateCheckID2a();
static void stateCheckID2();
static void stateCoverClosed();
static void stateCoverClosed_CMD();
static void stateCoverOpen();
static void stateMotorStopped();
static void stateReady();
static void stateBusy();

/* Callbacks */
static void cbForStateReadingFST(u32 intType);
static void cbForStateError(u32 intType);
static void cbForStateGettingError(u32 intType);
static void cbForUnrecoveredError(u32 intType);
static void cbForUnrecoveredErrorRetry(u32 intType);
static void cbForStateGoToRetry(u32 intType);
static void cbForStateCheckID2a(u32 intType);
static void cbForStateCheckID1(u32 intType);
static void cbForStateCheckID2(u32 intType);
static void cbForStateCheckID3(u32 intType);
static void cbForStateCoverClosed(u32 intType);
static void cbForStateMotorStopped(u32 intType);
static void cbForStateBusy(u32 intType);
static void cbForCancelStreamSync(s32 result, DVDCommandBlock *block);
static void cbForCancelSync(s32 result, DVDCommandBlock *block);
static void cbForCancelAllSync(s32 result, DVDCommandBlock *block);

static void defaultOptionalCommandChecker(DVDCommandBlock *block, DVDLowCallback cb);

static DVDOptionalCommandChecker checkOptionalCommand = defaultOptionalCommandChecker;


static void defaultOptionalCommandChecker(DVDCommandBlock *block, DVDLowCallback cb) {}

void DVDInit()
{
    if (DVDInitialized)
    {
        return;
    }

    OSRegisterVersion(__DVDVersion);
    DVDInitialized = TRUE;
    __DVDFSInit();
    __DVDClearWaitingQueue();
    __DVDInitWA();
    bootInfo = (OSBootInfo *)OSPhysicalToCached(0x0000);
    IDShouldBe = &(bootInfo->DVDDiskID);
    __OSSetInterruptHandler(21, __DVDInterruptHandler);
    __OSUnmaskInterrupts(0x400);
    OSInitThreadQueue(&__DVDThreadQueue);
    __DIRegs[0] = 0x2a;
    __DIRegs[1] = 0;
    if (bootInfo->magic == 0xE5207C22)
    {
        OSReport("load fst\n");
        __fstLoad();
    }
    else if (bootInfo->magic != 0xD15EA5E)
    {
        FirstTimeInBootrom = TRUE;
    }
}

static void stateReadingFST()
{
    LastState = (stateFunc)stateReadingFST;

    if (bootInfo->FSTMaxLength < BB2.FSTLength)
    {
#line 650
        OSPanic("dvd.c", 650, "DVDChangeDisk(): FST in the new disc is too big.   ");
    }

    DVDLowRead(bootInfo->FSTLocation, OSRoundUp32B(BB2.FSTLength), BB2.FSTPosition,
               cbForStateReadingFST);
}

static void cbForStateReadingFST(u32 intType)
{
    DVDCommandBlock *finished;

    if (intType == 16)
    {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 1)
    {
        NumInternalRetry = 0;
        __DVDFSInit();
        finished = executing;
        executing = &DummyCommandBlock;
        finished->state = 0;
        if (finished->callback)
        {
            (finished->callback)(0, finished);
        }

        stateReady();
    }
    else
    {

        stateGettingError();
    }
}

inline static void stateError(u32 error)
{
    __DVDStoreErrorCode(error);
    DVDLowStopMotor(cbForStateError);
}

static void cbForStateError(u32 intType)
{
    DVDCommandBlock *finished;

    if (intType == 16)
    {
        executing->state = -1;
        stateTimeout();
        return;
    }

    __DVDPrintFatalMessage();

    FatalErrorFlag = TRUE;
    finished = executing;
    executing = &DummyCommandBlock;
    if (finished->callback)
    {
        (finished->callback)(-1, finished);
    }

    if (Canceling)
    {
        Canceling = FALSE;
        if (CancelCallback)
            (CancelCallback)(0, finished);
    }

    stateReady();

    return;
}

static void stateTimeout()
{
    __DVDStoreErrorCode(0x1234568);
    DVDReset();
    cbForStateError(0);
}

static void stateGettingError() { DVDLowRequestError(cbForStateGettingError); }

static u32 CategorizeError(u32 error)
{
    if (error == 0x20400)
    {
        LastError = error;
        return 1;
    }

    error &= 0xffffff;

    if ((error == 0x62800) || (error == 0x23a00) || (error == 0xb5a01))
    {
        return 0;
    }

    ++NumInternalRetry;
    if (NumInternalRetry == 2)
    {
        if (error == LastError)
        {
            LastError = error;
            return 1;
        }
        else
        {
            LastError = error;
            return 2;
        }
    }
    else
    {
        LastError = error;

        if ((error == 0x31100) || (executing->command == 5))
        {
            return 2;
        }
        else
        {
            return 3;
        }
    }
}

inline static BOOL CheckCancel(u32 resume)
{
    DVDCommandBlock *finished;

    if (Canceling)
    {
        ResumeFromHere = resume;
        Canceling = FALSE;

        finished = executing;
        executing = &DummyCommandBlock;

        finished->state = 10;
        if (finished->callback)
            (*finished->callback)(-3, finished);
        if (CancelCallback)
            (CancelCallback)(0, finished);
        stateReady();
        return TRUE;
    }
    return FALSE;
}

static void cbForStateGettingError(u32 intType)
{
    u32 error;
    u32 status;
    u32 errorCategory;
    u32 resume;

    if (intType == 16)
    {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 2)
    {
        executing->state = -1;
        stateError(0x1234567);
        return;
    }

    error = __DIRegs[8];
    status = error & 0xff000000;

    errorCategory = CategorizeError(error);

    if (errorCategory == 1)
    {
        executing->state = -1;
        stateError(error);
        return;
    }

    if ((errorCategory == 2) || (errorCategory == 3))
    {
        resume = 0;
    }
    else
    {
        if (status == 0x01000000)
            resume = 4;
        else if (status == 0x02000000)
            resume = 6;
        else if (status == 0x03000000)
            resume = 3;
        else
            resume = 5;
    }

    if (CheckCancel(resume))
        return;

    if (errorCategory == 2)
    {
        __DVDStoreErrorCode(error);
        stateGoToRetry();
        return;
    }

    if (errorCategory == 3)
    {
        if ((error & 0x00ffffff) == 0x00031100)
        {
            DVDLowSeek(executing->offset, cbForUnrecoveredError);
        }
        else
        {
            LastState(executing);
        }
        return;
    }

    if (status == 0x01000000)
    {
        executing->state = 5;
        stateMotorStopped();
        return;
    }
    else if (status == 0x02000000)
    {
        executing->state = 3;
        stateCoverClosed();
        return;
    }
    else if (status == 0x03000000)
    {
        executing->state = 4;
        stateMotorStopped();
        return;
    }
    else
    {
        executing->state = -1;
        stateError(0x1234567);
        return;
    }
}

static void cbForUnrecoveredError(u32 intType)
{
    if (intType == 16)
    {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 1)
    {
        stateGoToRetry();
        return;
    }

    DVDLowRequestError(cbForUnrecoveredErrorRetry);
}

static void cbForUnrecoveredErrorRetry(u32 intType)
{
    if (intType == 16)
    {
        executing->state = -1;
        stateTimeout();
        return;
    }
    executing->state = -1;

    if (intType & 2)
    {
        __DVDStoreErrorCode(0x1234567);
        DVDLowStopMotor(cbForStateError);
        return;
    }

    __DVDStoreErrorCode(__DIRegs[8]);
    DVDLowStopMotor(cbForStateError);
}

static void stateGoToRetry() { DVDLowStopMotor(cbForStateGoToRetry); }

static void cbForStateGoToRetry(u32 intType)
{
    if (intType == 16)
    {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 2)
    {
        executing->state = -1;
        stateError(0x1234567);
        return;
    }

    NumInternalRetry = 0;

    if ((CurrCommand == 4) || (CurrCommand == 5) || (CurrCommand == 13) || (CurrCommand == 15))
    {
        ResetRequired = TRUE;
    }

    if (!CheckCancel(2))
    {
        executing->state = 11;
        stateMotorStopped();
    }
}

static void stateCheckID()
{
    switch (CurrCommand)
    {
    case 3:
        if (DVDCompareDiskID(&CurrDiskID, executing->id))
        {
            memcpy(IDShouldBe, &CurrDiskID, sizeof(DVDDiskID));

            executing->state = 1;
            DCInvalidateRange(&BB2, sizeof(DVDBB2));
            LastState = stateCheckID2a;
            stateCheckID2a(executing);
            return;
        }
        else
        {
            DVDLowStopMotor(cbForStateCheckID1);
        }
        break;

    default:
        if (memcmp(&CurrDiskID, IDShouldBe, sizeof(DVDDiskID)))
        {
            DVDLowStopMotor(cbForStateCheckID1);
        }
        else
        {
            LastState = stateCheckID3;
            stateCheckID3(executing);
        }
        break;
    }
}

static void stateCheckID3()
{
    DVDLowAudioBufferConfig(IDShouldBe->streaming, 10, cbForStateCheckID3);
}

static void stateCheckID2a()
{
    DVDLowAudioBufferConfig(IDShouldBe->streaming, 10, cbForStateCheckID2a);
}

static void cbForStateCheckID2a(u32 intType)
{
    if (intType == 16)
    {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 1)
    {
        NumInternalRetry = 0;
        stateCheckID2(executing);
        return;
    }

    DVDLowRequestError(cbForStateGettingError);
}

static void stateCheckID2()
{
    DVDLowRead(&BB2, OSRoundUp32B(sizeof(BB2)), 0x420, cbForStateCheckID2);
}

static void cbForStateCheckID1(u32 intType)
{
    if (intType == 16)
    {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 2)
    {
        executing->state = -1;
        stateError(0x1234567);
        return;
    }

    NumInternalRetry = 0;

    if (!CheckCancel(1))
    {
        executing->state = 6;
        stateMotorStopped();
    }
}

static void cbForStateCheckID2(u32 intType)
{
    if (intType == 16)
    {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 1)
    {

        NumInternalRetry = 0;

        stateReadingFST();
    }
    else
    {

        stateGettingError();
    }
}

static void cbForStateCheckID3(u32 intType)
{
    if (intType == 16)
    {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 1)
    {

        NumInternalRetry = 0;

        if (!CheckCancel(0))
        {
            executing->state = 1;
            stateBusy(executing);
        }
    }
    else
    {
        stateGettingError();
    }
}

static void AlarmHandler(OSAlarm *alarm, OSContext *context)
{
    DVDReset();
    DCInvalidateRange(&CurrDiskID, sizeof(DVDDiskID));
    LastState = stateCoverClosed_CMD;
    stateCoverClosed_CMD(executing);
}

static void stateCoverClosed()
{
    DVDCommandBlock *finished;

    switch (CurrCommand)
    {
    case 5:
    case 4:
    case 13:
    case 15:
        __DVDClearWaitingQueue();
        finished = executing;
        executing = &DummyCommandBlock;
        if (finished->callback)
        {
            (finished->callback)(-4, finished);
        }
        stateReady();
        break;

    default:
        DVDReset();
        OSCreateAlarm(&ResetAlarm);
        OSSetAlarm(&ResetAlarm, OSMillisecondsToTicks(1150), AlarmHandler);
        break;
    }
}

static void stateCoverClosed_CMD(DVDCommandBlock *block)
{
    DVDLowReadDiskID(&CurrDiskID, cbForStateCoverClosed);
}

static void cbForStateCoverClosed(u32 intType)
{
    if (intType == 16)
    {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if (intType & 1)
    {
        NumInternalRetry = 0;
        stateCheckID();
    }
    else
    {
        stateGettingError();
    }
}

static void stateMotorStopped(void) { DVDLowWaitCoverClose(cbForStateMotorStopped); }

static void cbForStateMotorStopped(u32 intType)
{
    __DIRegs[1] = 0;
    executing->state = 3;
    stateCoverClosed();
}

static void stateReady()
{
    DVDCommandBlock *finished;

    if (!__DVDCheckWaitingQueue())
    {
        executing = (DVDCommandBlock *)NULL;
        return;
    }

    if (PauseFlag)
    {
        PausingFlag = TRUE;
        executing = (DVDCommandBlock *)NULL;
        return;
    }

    executing = __DVDPopWaitingQueue();

    if (FatalErrorFlag)
    {
        executing->state = -1;
        finished = executing;
        executing = &DummyCommandBlock;
        if (finished->callback)
        {
            (finished->callback)(-1, finished);
        }
        stateReady();
        return;
    }

    CurrCommand = executing->command;

    if (ResumeFromHere)
    {
        switch (ResumeFromHere)
        {
        case 2:
            executing->state = 11;
            stateMotorStopped();
            break;
        case 3:
            executing->state = 4;
            stateMotorStopped();
            break;

        case 4:
            executing->state = 5;
            stateMotorStopped();
            break;
        case 1:
        case 7:
        case 6:
            executing->state = 3;
            stateCoverClosed();
            break;

        case 5:
            executing->state = -1;
            stateError(CancelLastError);
            break;

        }

        ResumeFromHere = 0;
    }
    else
    {
        executing->state = 1;
        stateBusy(executing);
    }
}

static void stateBusy(DVDCommandBlock *block)
{
    DVDCommandBlock *finished;
    LastState = stateBusy;
    switch (block->command)
    {
    case 5:
        __DIRegs[1] = __DIRegs[1];
        block->currTransferSize = sizeof(DVDDiskID);
        DVDLowReadDiskID(block->addr, cbForStateBusy);
        break;
    case 1:
    case 4:
        if (!block->length)
        {
            finished = executing;
            executing = &DummyCommandBlock;
            finished->state = 0;
            if (finished->callback)
            {
                finished->callback(0, finished);
            }
            stateReady();
        }
        else
        {
            __DIRegs[1] = __DIRegs[1];
            block->currTransferSize = block->length - block->transferredSize > 0x80000 ? 0x80000 : block->length - block->transferredSize;
            DVDLowRead((void *)((u8 *)block->addr + block->transferredSize), block->currTransferSize,
                       block->offset + block->transferredSize, cbForStateBusy);
        }
        break;
    case 2:
        __DIRegs[1] = __DIRegs[1];
        DVDLowSeek(block->offset, cbForStateBusy);
        break;
    case 3:
        DVDLowStopMotor(cbForStateBusy);
        break;
    case 15:
        DVDLowStopMotor(cbForStateBusy);
        break;
    case 6:
        __DIRegs[1] = __DIRegs[1];
        if (AutoFinishing)
        {
            executing->currTransferSize = 0;
            DVDLowRequestAudioStatus(0, cbForStateBusy);
        }
        else
        {
            executing->currTransferSize = 1;
            DVDLowAudioStream(0, block->length, block->offset, cbForStateBusy);
        }
        break;
    case 7:
        __DIRegs[1] = __DIRegs[1];
        DVDLowAudioStream(0x10000, 0, 0, cbForStateBusy);
        break;
    case 8:
        __DIRegs[1] = __DIRegs[1];
        AutoFinishing = TRUE;
        DVDLowAudioStream(0, 0, 0, cbForStateBusy);
        break;
    case 9:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0, cbForStateBusy);
        break;
    case 10:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0x10000, cbForStateBusy);
        break;
    case 11:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0x20000, cbForStateBusy);
        break;
    case 12:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0x30000, cbForStateBusy);
        break;
    case 13:
        __DIRegs[1] = __DIRegs[1];
        DVDLowAudioBufferConfig(block->offset, block->length, cbForStateBusy);
        break;
    case 14:
        __DIRegs[1] = __DIRegs[1];
        block->currTransferSize = sizeof(DVDDriveInfo);
        DVDLowInquiry(block->addr, cbForStateBusy);
        break;
    default:
        checkOptionalCommand(block, cbForStateBusy);
        break;
    }
}

static u32 ImmCommand[] = {0xffffffff, 0xffffffff, 0xffffffff};
/* Somehow this got included even though the function is stripped? O.o */
static char string_DVDChangeDiskAsyncMsg[] =
    "DVDChangeDiskAsync(): You can't specify NULL to company name.  \n";
static u32 DmaCommand[] = {0xffffffff};

inline static BOOL IsImmCommandWithResult(u32 command)
{
    u32 i;

    if (command == 9 || command == 10 || command == 11 || command == 12)
    {
        return TRUE;
    }

    for (i = 0; i < sizeof(ImmCommand) / sizeof(ImmCommand[0]); i++)
    {
        if (command == ImmCommand[i])
            return TRUE;
    }

    return FALSE;
}

inline static BOOL IsDmaCommand(u32 command)
{
    u32 i;

    if (command == 1 || command == 4 || command == 5 || command == 14)
        return TRUE;

    for (i = 0; i < sizeof(DmaCommand) / sizeof(DmaCommand[0]); i++)
    {
        if (command == DmaCommand[i])
            return TRUE;
    }

    return FALSE;
}

static void cbForStateBusy(u32 intType)
{
    DVDCommandBlock *finished;

    if (intType == 16)
    {
        executing->state = -1;
        stateTimeout();
        return;
    }

    if ((CurrCommand == 3) || (CurrCommand == 15))
    {
        if (intType & 2)
        {
            executing->state = -1;
            stateError(0x1234567);
            return;
        }

        NumInternalRetry = 0;

        if (CurrCommand == 15)
        {
            ResetRequired = TRUE;
        }

        if (CheckCancel(7))
        {
            return;
        }

        executing->state = 7;
        stateMotorStopped();
        return;
    }

    if (IsDmaCommand(CurrCommand))
    {
        executing->transferredSize += executing->currTransferSize - __DIRegs[6];
    }

    if (intType & 8)
    {
        Canceling = FALSE;
        finished = executing;
        executing = &DummyCommandBlock;

        finished->state = 10;
        if (finished->callback)
            (*finished->callback)(-3, finished);
        if (CancelCallback)
            (CancelCallback)(0, finished);
        stateReady();

        return;
    }

    if (intType & 1)
    {
        NumInternalRetry = 0;

        if (CheckCancel(0))
            return;

        if (IsDmaCommand(CurrCommand))
        {
            if (executing->transferredSize != executing->length)
            {
                stateBusy(executing);
                return;
            }

            finished = executing;
            executing = &DummyCommandBlock;

            finished->state = 0;
            if (finished->callback)
            {
                (finished->callback)((s32)finished->transferredSize, finished);
            }
            stateReady();
        }
        else if (IsImmCommandWithResult(CurrCommand))
        {
            s32 result;

            if ((CurrCommand == 11) || (CurrCommand == 10))
            {
                result = (s32)(__DIRegs[8] << 2);
            }
            else
            {
                result = (s32)__DIRegs[8];
            }
            finished = executing;
            executing = &DummyCommandBlock;

            finished->state = 0;
            if (finished->callback)
            {
                (finished->callback)(result, finished);
            }
            stateReady();
        }
        else if (CurrCommand == 6)
        {
            if (executing->currTransferSize == 0)
            {
                if (__DIRegs[8] & 1)
                {
                    finished = executing;
                    executing = &DummyCommandBlock;

                    finished->state = 9;
                    if (finished->callback)
                    {
                        (finished->callback)(-2, finished);
                    }
                    stateReady();
                }
                else
                {
                    AutoFinishing = FALSE;
                    executing->currTransferSize = 1;
                    DVDLowAudioStream(0, executing->length, executing->offset, cbForStateBusy);
                }
            }
            else
            {
                finished = executing;
                executing = &DummyCommandBlock;

                finished->state = 0;
                if (finished->callback)
                {
                    (finished->callback)(0, finished);
                }
                stateReady();
            }
        }
        else
        {
            finished = executing;
            executing = &DummyCommandBlock;

            finished->state = 0;
            if (finished->callback)
            {
                (finished->callback)(0, finished);
            }
            stateReady();
        }
    }
    else
    {
        if (CurrCommand == 14)
        {
            executing->state = -1;
            stateError(0x01234567);
            return;
        }

        if ((CurrCommand == 1 || CurrCommand == 4 || CurrCommand == 5 || CurrCommand == 14) &&
            (executing->transferredSize == executing->length))
        {
            if (CheckCancel(0))
            {
                return;
            }
            finished = executing;
            executing = &DummyCommandBlock;

            finished->state = 0;
            if (finished->callback)
            {
                (finished->callback)((s32)finished->transferredSize, finished);
            }
            stateReady();
            return;
        }

        stateGettingError();
    }
}

static BOOL issueCommand(s32 prio, DVDCommandBlock *block)
{
    BOOL level;
    BOOL result;

    if (autoInvalidation &&
        (block->command == 1 || block->command == 4 || block->command == 5 || block->command == 14))
    {
        DCInvalidateRange(block->addr, block->length);
    }

    level = OSDisableInterrupts();

    block->state = 2;
    result = __DVDPushWaitingQueue(prio, block);

    if ((executing == (DVDCommandBlock *)NULL) && (PauseFlag == FALSE))
    {
        stateReady();
    }

    OSRestoreInterrupts(level);

    return result;
}

BOOL DVDReadAbsAsyncPrio(DVDCommandBlock *block, void *addr, s32 length, s32 offset,
                         DVDCBCallback callback, s32 prio)
{
    BOOL idle;
    block->command = 1;
    block->addr = addr;
    block->length = length;
    block->offset = offset;
    block->transferredSize = 0;
    block->callback = callback;

    idle = issueCommand(prio, block);
    return idle;
}

BOOL DVDReadAbsAsyncForBS(DVDCommandBlock *block, void *addr, s32 length, s32 offset,
                          DVDCBCallback callback)
{
    BOOL idle;
    block->command = 4;
    block->addr = addr;
    block->length = length;
    block->offset = offset;
    block->transferredSize = 0;
    block->callback = callback;

    idle = issueCommand(2, block);
    return idle;
}

BOOL DVDReadDiskID(DVDCommandBlock *block, DVDDiskID *diskID, DVDCBCallback callback)
{
    BOOL idle;
    block->command = 5;
    block->addr = diskID;
    block->length = sizeof(DVDDiskID);
    ;
    block->offset = 0;
    block->transferredSize = 0;
    block->callback = callback;

    idle = issueCommand(2, block);
    return idle;
}

BOOL DVDPrepareStreamAbsAsync(DVDCommandBlock *block, u32 length, u32 offset,
                              DVDCBCallback callback)
{
    BOOL idle;
    block->command = 6;
    block->length = length;
    block->offset = offset;
    block->callback = callback;

    idle = issueCommand(1, block);
    return idle;
}

BOOL DVDCancelStreamAsync(DVDCommandBlock *block, DVDCBCallback callback)
{
    BOOL idle;
    block->command = 7;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

s32 DVDCancelStream(DVDCommandBlock *block)
{
    BOOL result;
    s32 state;
    BOOL enabled;
    s32 retVal;

    result = DVDCancelStreamAsync(block, cbForCancelStreamSync);

    if (result == FALSE)
    {
        return -1;
    }

    enabled = OSDisableInterrupts();

    while (TRUE)
    {
        state = ((volatile DVDCommandBlock *)block)->state;

        if (state == 0 || state == -1 || state == 10)
        {
            retVal = (s32)block->transferredSize;
            break;
        }

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}
static void cbForCancelStreamSync(s32 result, DVDCommandBlock *block)
{
    block->transferredSize = (u32)result;
    OSWakeupThread(&__DVDThreadQueue);
}
BOOL DVDStopStreamAtEndAsync(DVDCommandBlock *block, DVDCBCallback callback)
{
    BOOL idle;

    block->command = 8;
    block->callback = callback;

    idle = issueCommand(1, block);

    return idle;
}
BOOL DVDGetStreamErrorStatusAsync(DVDCommandBlock *block, DVDCBCallback callback)
{
    BOOL idle;

    block->command = 9;
    block->callback = callback;

    idle = issueCommand(1, block);

    return idle;
}
BOOL DVDGetStreamPlayAddrAsync(DVDCommandBlock *block, DVDCBCallback callback)
{
    BOOL idle;

    block->command = 10;
    block->callback = callback;

    idle = issueCommand(1, block);

    return idle;
}
BOOL DVDInquiryAsync(DVDCommandBlock *block, DVDDriveInfo *info, DVDCBCallback callback)
{
    BOOL idle;

    block->command = 14;
    block->addr = (void *)info;
    block->length = sizeof(DVDDriveInfo);
    block->transferredSize = 0;
    block->callback = callback;

    idle = issueCommand(2, block);

    return idle;
}

void DVDReset(void)
{
    DVDLowReset();
    __DIRegs[0] = 0x2a;
    __DIRegs[1] = __DIRegs[1];
    ResetRequired = FALSE;
    ResumeFromHere = 0;
}

s32 DVDGetCommandBlockStatus(const DVDCommandBlock *block)
{
    BOOL enabled;
    s32 retVal;

    enabled = OSDisableInterrupts();

    if (block->state == 3)
    {
        retVal = 1;
    }
    else
    {
        retVal = block->state;
    }

    OSRestoreInterrupts(enabled);

    return retVal;
}

s32 DVDGetDriveStatus()
{
    BOOL enabled;
    s32 retVal;

    enabled = OSDisableInterrupts();

    if (FatalErrorFlag)
    {
        retVal = -1;
    }
    else if (PausingFlag)
    {
        retVal = 8;
    }
    else
    {
        if (executing == (DVDCommandBlock *)NULL)
        {
            retVal = 0;
        }
        else if (executing == &DummyCommandBlock)
        {
            retVal = 0;
        }
        else
        {
            retVal = DVDGetCommandBlockStatus(executing);
        }
    }

    OSRestoreInterrupts(enabled);

    return retVal;
}

BOOL DVDSetAutoInvalidation(BOOL autoInval)
{
    BOOL prev;
    prev = autoInvalidation;
    autoInvalidation = autoInval;
    return prev;
}

void DVDPause(void)
{
    BOOL level;
    level = OSDisableInterrupts();
    PauseFlag = TRUE;
    if (executing == (DVDCommandBlock *)NULL)
    {
        PausingFlag = TRUE;
    }
    OSRestoreInterrupts(level);
}

void DVDResume(void)
{
    BOOL level;
    level = OSDisableInterrupts();
    PauseFlag = FALSE;
    if (PausingFlag)
    {
        PausingFlag = FALSE;
        stateReady();
    }
    OSRestoreInterrupts(level);
}

BOOL DVDCancelAsync(DVDCommandBlock *block, DVDCBCallback callback)
{
    BOOL enabled;
    DVDLowCallback old;
    DVDCommandBlock *finished; // needed for stack? maybe it actually gets used but not bothered to figure that out

    enabled = OSDisableInterrupts();

    switch (block->state)
    {
    case -1:
    case 0:
    case 10:
        if (callback)
            (*callback)(0, block);
        break;

    case 1:
        if (Canceling)
        {
            OSRestoreInterrupts(enabled);
            return FALSE;
        }

        Canceling = TRUE;
        CancelCallback = callback;
        if (block->command == 4 || block->command == 1)
        {
            DVDLowBreak();
        }
        break;

    case 2:
        __DVDDequeueWaitingQueue(block);
        block->state = 10;
        if (block->callback)
            (block->callback)(-3, block);
        if (callback)
            (*callback)(0, block);
        break;

    case 3:
        switch (block->command)
        {
        case 5:
        case 4:
        case 13:
        case 15:
            if (callback)
                (*callback)(0, block);
            break;

        default:
            if (Canceling)
            {
                OSRestoreInterrupts(enabled);
                return FALSE;
            }
            Canceling = TRUE;
            CancelCallback = callback;
            break;
        }
        break;

    case 4:
    case 5:
    case 6:
    case 7:
    case 11:
        old = DVDLowClearCallback();
        if (old != cbForStateMotorStopped)
        {
            OSRestoreInterrupts(enabled);
            return FALSE;
        }

        if (block->state == 4)
            ResumeFromHere = 3;
        if (block->state == 5)
            ResumeFromHere = 4;
        if (block->state == 6)
            ResumeFromHere = 1;
        if (block->state == 11)
            ResumeFromHere = 2;
        if (block->state == 7)
            ResumeFromHere = 7;

        executing = &DummyCommandBlock;

        block->state = 10;
        if (block->callback)
        {
            (block->callback)(-3, block);
        }
        if (callback)
        {
            (callback)(0, block);
        }
        stateReady();
        break;
    }

    OSRestoreInterrupts(enabled);
    return TRUE;
}

s32 DVDCancel(DVDCommandBlock *block)
{
    BOOL result;
    s32 state;
    u32 command;
    BOOL enabled;

    result = DVDCancelAsync(block, cbForCancelSync);

    if (result == FALSE)
    {
        return -1;
    }

    enabled = OSDisableInterrupts();

    for (;;)
    {
        state = ((volatile DVDCommandBlock *)block)->state;

        if ((state == 0) || (state == -1) || (state == 10))
        {
            break;
        }

        if (state == 3)
        {
            command = ((volatile DVDCommandBlock *)block)->command;

            if ((command == 4) || (command == 5) || (command == 13) || (command == 15))
            {
                break;
            }
        }

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return 0;
}

static void cbForCancelSync(s32 result, DVDCommandBlock *block)
{
    OSWakeupThread(&__DVDThreadQueue);
}

inline BOOL DVDCancelAllAsync(DVDCBCallback callback)
{
    BOOL enabled;
    DVDCommandBlock *p;
    BOOL retVal;

    enabled = OSDisableInterrupts();
    DVDPause();

    while ((p = __DVDPopWaitingQueue()) != 0)
    {
        DVDCancelAsync(p, NULL);
    }

    if (executing)
        retVal = DVDCancelAsync(executing, callback);
    else
    {
        retVal = TRUE;
        if (callback)
            (*callback)(0, NULL);
    }

    DVDResume();
    OSRestoreInterrupts(enabled);
    return retVal;
}

s32 DVDCancelAll(void)
{
    BOOL result;
    BOOL enabled;

    enabled = OSDisableInterrupts();
    CancelAllSyncComplete = FALSE;

    result = DVDCancelAllAsync(cbForCancelAllSync);

    if (result == FALSE)
    {
        OSRestoreInterrupts(enabled);
        return -1;
    }

    for (;;)
    {
        if (CancelAllSyncComplete)
            break;

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return 0;
}

static void cbForCancelAllSync(s32 result, DVDCommandBlock *block)
{
    CancelAllSyncComplete = TRUE;
    OSWakeupThread(&__DVDThreadQueue);
}

DVDDiskID *DVDGetCurrentDiskID(void) { return (DVDDiskID *)OSPhysicalToCached(0); }

BOOL DVDCheckDisk(void)
{
    BOOL enabled;
    s32 retVal;
    s32 state;
    u32 coverReg;

    enabled = OSDisableInterrupts();

    if (FatalErrorFlag)
    {
        state = -1;
    }
    else if (PausingFlag)
    {
        state = 8;
    }
    else
    {
        if (executing == (DVDCommandBlock *)NULL)
        {
            state = 0;
        }
        else if (executing == &DummyCommandBlock)
        {
            state = 0;
        }
        else
        {
            state = executing->state;
        }
    }

    switch (state)
    {
    case 1:
    case 9:
    case 10:
    case 2:
        retVal = TRUE;
        break;

    case -1:
    case 11:
    case 7:
    case 3:
    case 4:
    case 5:
    case 6:
        retVal = FALSE;
        break;

    case 0:
    case 8:
        coverReg = __DIRegs[1];
        if (((coverReg >> 2) & 1) || (coverReg & 1))
        {
            retVal = FALSE;
        }
        else if (ResumeFromHere)
        {
            retVal = FALSE;
        }
        else
        {
            retVal = TRUE;
        }

    }

    OSRestoreInterrupts(enabled);

    return retVal;
}

void __DVDPrepareResetAsync(DVDCBCallback callback)
{
    BOOL enabled;

    enabled = OSDisableInterrupts();

    __DVDClearWaitingQueue();

    if (Canceling)
    {
        CancelCallback = callback;
    }
    else
    {
        if (executing)
        {
            executing->callback = NULL;
        }

        DVDCancelAllAsync(callback);
    }

    OSRestoreInterrupts(enabled);
}

BOOL __DVDTestAlarm(const OSAlarm *alarm) {
    BOOL ret;
    if(alarm == &ResetAlarm) {
        ret = TRUE;
    }
    else {
        ret = __DVDLowTestAlarm(alarm);
    }
    return ret;
}