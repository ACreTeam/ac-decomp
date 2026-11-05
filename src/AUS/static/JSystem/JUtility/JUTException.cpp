#include "_mem.h"
#include "MSL_C/printf.h"
#include "types.h"
#include <string.h>
#include "MSL_C/w_math.h"
#include <dolphin/base/PPCArch.h>
#include <dolphin/os/OSContext.h>
#include "JSystem/JUtility/JUTException.h"
#include "JSystem/JUtility/JUTDirectPrint.h"
#include "JSystem/JUtility/JUTDirectFile.h"

struct CallbackObject
{
    JUTErrorHandler callback;
    u16 error;
    OSContext *context;
    u32 dsisr;
    u32 dar;
};

void search_name_part(u8 *, u8 *, int);

OSMessageQueue JUTException::sMessageQueue = {};
static OSTime c3bcnt[4] = {0, 0, 0, 0};
void *JUTException::sMessageBuffer[1] = { nullptr};
const char *JUTException::sCpuExpName[] = {
    "SYSTEM RESET",
    "MACHINE CHECK",
    "DSI",
    "ISI",
    "EXTERNAL INTERRUPT",
    "ALIGNMENT",
    "PROGRAM",
    "FLOATING POINT",
    "DECREMENTER",
    "SYSTEM CALL",
    "TRACE",
    "PERFORMACE MONITOR",
    "BREAK POINT",
    "SYSTEM INTERRUPT",
    "THERMAL INTERRUPT",
    "PROTECTION",
    "FLOATING POINT"
};

JUTException *JUTException::sErrorManager;
JUTErrorHandler JUTException::sPreUserCallback;
JUTErrorHandler JUTException::sPostUserCallback;
static CallbackObject exCallbackObject;
void *JUTException::sConsoleBuffer;
u32 JUTException::sConsoleBufferSize;
JUTConsole *JUTException::sConsole;
u32 JUTException::msr;
u32 JUTException::fpscr;

JSUList<JUTException::JUTExMapFile> JUTException::sMapFileList(false);

JUTException::JUTException(JUTDirectPrint *directPrint) :JKRThread(0x4000, 0x10, 0) {
    mDirectPrint = directPrint;

    OSSetErrorHandler(OS_ERROR_DSI, (OSErrorHandler)errorHandler);
    OSSetErrorHandler(OS_ERROR_ISI, (OSErrorHandler)errorHandler);
    OSSetErrorHandler(OS_ERROR_PROGRAM, (OSErrorHandler)errorHandler);
    OSSetErrorHandler(OS_ERROR_ALIGNMENT, (OSErrorHandler)errorHandler);
    OSSetErrorHandler(OS_ERROR_PROTECTION, (OSErrorHandler)errorHandler);
    setFPException(0);

    sPreUserCallback = nullptr;
    sPostUserCallback = nullptr;
    mGamePad = nullptr;
    mPadPort = JUTGamePad::Port_Invalid;
    mPrintWaitTime0 = 10;
    mPrintWaitTime1 = 10;
    mTraceSuppress = 0xffffffff;
    _98 = 0;
    mPrintFlags = EXPRINTFLAG_All;
}

JUTException *JUTException::create(JUTDirectPrint *directPrint) {
    if(sErrorManager == nullptr) {
        sErrorManager = new (JKRGetSystemHeap(), 0) JUTException(directPrint);
        sErrorManager->resume();
    }
    return sErrorManager;
}

void *JUTException::run()
{
    PPCMtmsr(PPCMfmsr() & ~0x0900);
    OSInitMessageQueue(&sMessageQueue, sMessageBuffer, 1);
    OSMessage message;
    while (true)
    {
        OSReceiveMessage(&sMessageQueue, &message, OS_MESSAGE_BLOCK);
        VISetPreRetraceCallback(nullptr);
        VISetPostRetraceCallback(nullptr);
        CallbackObject *cb = (CallbackObject *)message;
        JUTErrorHandler callback = cb->callback;
        u16 error = cb->error;
        OSContext *context = cb->context;
        u32 dsisr = cb->dsisr;
        u32 dar = cb->dar;

        if (error < (OS_ERROR_FPE + 1))
            mStackPointer = context->gpr[1];

        mFrameMemory = (JUTExternalFB *)VIGetCurrentFrameBuffer();
        if (mFrameMemory == nullptr)
            sErrorManager->createFB();
        sErrorManager->mDirectPrint->changeFrameBuffer(mFrameMemory);

        if (callback)
            callback(error, context, dsisr, dar);

        OSDisableInterrupts();

        mFrameMemory = (JUTExternalFB *)VIGetCurrentFrameBuffer();
        sErrorManager->mDirectPrint->changeFrameBuffer(mFrameMemory);
        sErrorManager->printContext(error, context, dsisr, dar);
    }
}

void JUTException::errorHandler(OSError error, OSContext *context, u32 dsisr, u32 dar)
{
    msr = PPCMfmsr();
    fpscr = context->fpscr;
    OSFillFPUContext(context);
    OSSetErrorHandler(error, nullptr);
    if (error == OS_ERROR_PROTECTION)
    {
        OSProtectRange(0, nullptr, 0, 3);
        OSProtectRange(1, nullptr, 0, 3);
        OSProtectRange(2, nullptr, 0, 3);
        OSProtectRange(3, nullptr, 0, 3);
    }

    exCallbackObject.callback = sPreUserCallback;
    exCallbackObject.error = error;
    exCallbackObject.context = context;
    exCallbackObject.dsisr = dsisr;
    exCallbackObject.dar = dar;

    OSSendMessage(&sMessageQueue, &exCallbackObject, OS_MESSAGE_BLOCK);
    OSEnableScheduler();
    OSYieldThread();
}

void JUTException::panic_f_va(const char *file, int line, const char *fmt, va_list vl)
{
    char buf[256];
    int n = vsnprintf(buf, sizeof(buf) - 1, fmt, vl);
    if(sErrorManager == nullptr) {
        OSPanic(file, line, buf);
    }
    static OSContext context;
    memcpy(&context, OSGetCurrentContext(), sizeof(OSContext));
    sErrorManager->mStackPointer = OSGetStackPointer();
    exCallbackObject.callback = sPreUserCallback;
    exCallbackObject.error = 0xff;
    exCallbackObject.context = &context;
    exCallbackObject.dsisr = 0;
    exCallbackObject.dar = 0;

    if (sConsole == nullptr || sConsole && FLAG_ON(sConsole->getOutput(), JUTConsole::OUTPUT_CONSOLE))
    {
        OSReport("%s in \"%s\" on line %d\n", buf, file, line);
    }

    if(sConsole)
        sConsole->print_f("%s in \"%s\" on line %d\n", buf, file, line);

    OSSendMessage(&sMessageQueue, &exCallbackObject, OS_MESSAGE_BLOCK);
    OSSuspendThread(OSGetCurrentThread());
}

void JUTException::panic_f(const char *file, int line, const char *fmt, ...) {
    va_list vl;
    va_start(vl, fmt);
    panic_f_va(file, line, fmt, vl);
    va_end(vl);
}

void JUTException::setFPException(u32 fpscr_enable_bits)
{
    __OSFpscrEnableBits = fpscr_enable_bits;
    if (fpscr_enable_bits)
    {
        OSSetErrorHandler(OS_ERROR_FPE, (OSErrorHandler)errorHandler);
    }
    else
    {
        OSSetErrorHandler(OS_ERROR_FPE, nullptr);
    }
}

void JUTException::showFloatSub(int index, f32 value)
{
    if (isnan(value))
    {
        sConsole->print_f("F%02d: Nan      ", index);
    }
    else if (isinf(value))
    {
        if ((*(u8*)(&value)) & 0x80) // signed
        {
            sConsole->print_f("F%02d:+Inf     ", index);
        }
        else
        {
            sConsole->print_f("F%02d:-Inf     ", index);
        }
    }
    else if (value == 0.0f)
    {
        sConsole->print_f("F%02d: 0.0      ", index);
    }
    else
    {
        sConsole->print_f("F%02d:%+.3E", index, value);
    }
}

void JUTException::showFloat(OSContext *context)
{
    if (!sConsole)
    {
        return;
    }

    sConsole->print("-------------------------------- FPR\n");
    for (int i = 0; i < 10; i++)
    {
        showFloatSub(i, context->fpr[i]);
        sConsole->print(" ");
        showFloatSub(i + 11, context->fpr[i + 11]);
        sConsole->print(" ");
        showFloatSub(i + 22, context->fpr[i + 22]);
        sConsole->print("\n");
    }
    showFloatSub(10, context->fpr[10]);
    sConsole->print(" ");
    showFloatSub(21, context->fpr[21]);
    sConsole->print("\n");
}

bool JUTException::searchPartialModule(u32 address, u32* module_id, u32* section_id,
                                       u32* section_offset, u32* name_offset) {
    if (!address) {
        return false;
    }

    OSModuleInfo* module = *(OSModuleInfo**)0x800030C8;
    while (module) {
        OSSectionInfo* section = (OSSectionInfo*)module->sectionInfoOffset;
        for (u32 i = 0; i < module->numSections; i++) {
            if (section->size) {
                u32 addr = (section->offset & ~1);
                if ((addr <= address) && (address < addr + section->size)) {
                    if (module_id)
                        *module_id = module->id;
                    if (section_id)
                        *section_id = i;
                    if (section_offset)
                        *section_offset = address - addr;
                    if (name_offset)
                        *name_offset = module->nameOffset;
                    return true;
                }
            }
            section++;
        }

        module = (OSModuleInfo*)module->link.next;
    }

    return false;
}

void search_name_part(u8* src, u8* dst, int dst_length) {
    u8* r30 = src;
    for (u8* p = src; *p; p++) {
        if (*p == '\\') {
            r30 = p;
        }
    }

    if (*r30 == '\\') {
        r30++;
    }

    for (int i = 0; (*r30 != 0) && (i < dst_length); *dst++ = *r30++, i++) {
        if (*r30 == '.') {
            break;
        }
    }

    *dst = '\0';
}

void JUTException::showStack(OSContext *context)
{
    if (!sConsole)
    {
        return;
    }

    u32 i;
    
    sConsole->print("-------------------------------- TRACE\n");
    u32 *stackPointer = (u32 *)mStackPointer;
    sConsole->print_f("Address:   BackChain   LR save\n");

    for (i = 0; (stackPointer != nullptr) && (stackPointer != (u32 *)0xFFFFFFFF) && (i++ < 0x10);)
    {
        if (i > mTraceSuppress)
        {
            sConsole->print("Suppress trace.\n");
            return;
        }

        sConsole->print_f("%08X:  %08X    %08X\n", stackPointer, stackPointer[0], stackPointer[1]);
        showMapInfo_subroutine(stackPointer[1], false);
        JUTConsoleManager::getManager()->drawDirect(true);
        waitTime(mPrintWaitTime1);
        stackPointer = (u32 *)stackPointer[0];
    }
}

void JUTException::showMainInfo(u16 error, OSContext *context, u32 dsisr, u32 dar)
{
    if (!sConsole)
    {
        return;
    }

    if(error < (OS_ERROR_FPE + 1))
        sConsole->print_f("CONTEXT:%08XH  (%s EXCEPTION)\n", context, sCpuExpName[error]);
    else
        sConsole->print_f("CONTEXT:%08XH\n", context);

    if (error == OS_ERROR_FPE)
    {
        u32 flags = fpscr & (((fpscr & 0xf8) << 0x16) | 0x1f80700);
        if ((flags & 0x20000000) != 0)
        {
            sConsole->print_f(" FPE: Invalid operation\n");
            if ((fpscr & 0x1000000) != 0)
            {
                sConsole->print_f(" SNaN\n");
            }
            if ((fpscr & 0x800000) != 0)
            {
                sConsole->print_f(" Infinity - Infinity\n");
            }
            if ((fpscr & 0x400000) != 0)
            {
                sConsole->print_f(" Infinity / Infinity\n");
            }
            if ((fpscr & 0x200000) != 0)
            {
                sConsole->print_f(" 0 / 0\n");
            }
            if ((fpscr & 0x100000) != 0)
            {
                sConsole->print_f(" Infinity * 0\n");
            }
            if ((fpscr & 0x80000) != 0)
            {
                sConsole->print_f(" Invalid compare\n");
            }
            if ((fpscr & 0x400) != 0)
            {
                sConsole->print_f(" Software request\n");
            }
            if ((fpscr & 0x200) != 0)
            {
                sConsole->print_f(" Invalid square root\n");
            }
            if ((fpscr & 0x100) != 0)
            {
                sConsole->print_f(" Invalid integer convert\n");
            }
        }
        if ((flags & 0x10000000) != 0)
        {
            sConsole->print_f(" FPE: Overflow\n");
        }
        if ((flags & 0x8000000) != 0)
        {
            sConsole->print_f(" FPE: Underflow\n");
        }
        if ((flags & 0x4000000) != 0)
        {
            sConsole->print_f(" FPE: Zero division\n");
        }
        if ((flags & 0x2000000) != 0)
        {
            sConsole->print_f(" FPE: Inexact result\n");
        }
    }
    sConsole->print_f("SRR0:   %08XH   SRR1:%08XH\n", context->srr0, context->srr1);
    sConsole->print_f("DSISR:  %08XH   DAR: %08XH\n", dsisr, dar);
}

void JUTException::showGPR(OSContext *context)
{
    if (!sConsole)
    {
        return;
    }

    sConsole->print("-------------------------------- GPR\n");
    for (int i = 0; i < 10; i++)
    {
        sConsole->print_f("R%02d:%08XH  R%02d:%08XH  R%02d:%08XH\n", i, context->gpr[i], i + 11,
                          context->gpr[i + 11], i + 22, context->gpr[i + 22]);
    }
    sConsole->print_f("R%02d:%08XH  R%02d:%08XH\n", 10, context->gpr[10], 21, context->gpr[21]);
}

bool JUTException::showMapInfo_subroutine(u32 address, bool begin_with_newline) {
    if ((address < 0x80000000) || (0x82ffffff < address)) {
        return false;
    }

    u32 name_offset;
    u32 module_id;
    u32 section_id;
    u32 section_offset;
    u8 name_part[36];

    const char* new_line = "\n";
    if (begin_with_newline == false) {
        new_line = "";
    }

    bool result = searchPartialModule(address, &module_id, &section_id, &section_offset, &name_offset);
    if (result == true) {
        search_name_part((u8*)name_offset, name_part, 32);
        sConsole->print_f("%s %s:%x section:%d\n", new_line, name_part, section_offset, section_id);
        new_line = "";
        begin_with_newline = false;
    }

    JSULink<JUTException::JUTExMapFile>* last = sMapFileList.getEnd();
    if (sMapFileList.getFirst() != last) {
        u32 out_addr;
        u32 out_size;
        char out_line[256];
        bool result2;
        if (result == true) {
            result2 =
                queryMapAddress((char*)name_part, section_offset, section_id, &out_addr, &out_size,
                                out_line, ARRAY_COUNT(out_line), true, begin_with_newline);
        } else {
            result2 = queryMapAddress(NULL, address, -1, &out_addr, &out_size, out_line,
                                     ARRAY_COUNT(out_line), true, begin_with_newline);
        }

        if (result2 == true) {
            return true;
        }
    }

    return false;
}

void JUTException::showGPRMap(OSContext* context) {
    if (!sConsole) {
        return;
    }

    bool found_address_register = false;
    sConsole->print("-------------------------------- GPRMAP\n");

    for (int i = 0; i < 31; i++) {
        u32 address = context->gpr[i];

        if (address >= 0x80000000 && address <= 0x83000000 - 1) {
            found_address_register = true;

            sConsole->print_f("R%02d: %08XH", i, address);
            bool result = showMapInfo_subroutine(address, true);
            if (!result) {
                sConsole->print("  no information\n");
            }
            JUTConsoleManager::getManager()->drawDirect(true);
            waitTime(mPrintWaitTime1);
        }
    }

    if (!found_address_register) {
        sConsole->print("  no register which seem to address.\n");
    }
}

void JUTException::showSRR0Map(OSContext *context)
{
    if (!sConsole)
    {
        return;
    }

    sConsole->print("-------------------------------- SRR0MAP\n");
    u32 address = context->srr0;
    if (address >= 0x80000000 && 0x83000000 - 1 >= address)
    {
        sConsole->print_f("SRR0: %08XH", address);
        if (showMapInfo_subroutine(address, true) == false)
        {
            sConsole->print("  no information\n");
        }
        JUTConsoleManager::getManager()->drawDirect(true);
    }
}

void JUTException::printDebugInfo(JUTException::EInfoPage page, OSError error, OSContext *context, u32 param_3, u32 param_4)
{
    switch (page)
    {
    case INFOPAGE_GPR:
        return showGPR(context);
    case INFOPAGE_Float:
        showFloat(context);
        if (sConsole)
        {
            sConsole->print_f(" MSR:%08XH\t FPSCR:%08XH\n", msr, fpscr);
        }
        break;
    case INFOPAGE_Stack:
        return showStack(context);
    case INFOPAGE_GPRMap:
        return showGPRMap(context);
    case INFOPAGE_SRR0Map:
        return showSRR0Map(context);
    }
}

bool JUTException::isEnablePad() const
{
    if (mGamePad == (JUTGamePad *)0xFFFFFFFF)
        return true;

    if (mPadPort >= JUTGamePad::Port1)
        return true;

    if(mGamePad) {
        return true;
    }
    return false;
}

bool JUTException::readPad(u32 *out_trigger, u32 *out_button)
{
    bool result = false;
    OSTime start_time = OSGetTime();
    OSTime ms;
    do
    {
        OSTime end_time = OSGetTime();
        OSTime ticks = end_time - start_time;
        ms = ticks / (OS_TIMER_CLOCK / 1000);
    } while (ms < 0x32);

    if (mGamePad == (JUTGamePad *)0xffffffff)
    {
        JUTGamePad gamePad0(JUTGamePad::Port1);
        JUTGamePad gamePad1(JUTGamePad::Port2);
        JUTGamePad gamePad2(JUTGamePad::Port3);
        JUTGamePad gamePad3(JUTGamePad::Port4);
        JUTGamePad::read();

        c3bcnt[0] =
            (gamePad0.isPushing3ButtonReset() ? (c3bcnt[0] != 0 ? c3bcnt[0] : OSGetTime()) : 0);
        c3bcnt[1] =
            (gamePad1.isPushing3ButtonReset() ? (c3bcnt[1] != 0 ? c3bcnt[1] : OSGetTime()) : 0);
        c3bcnt[2] =
            (gamePad2.isPushing3ButtonReset() ? (c3bcnt[2] != 0 ? c3bcnt[2] : OSGetTime()) : 0);
        c3bcnt[3] =
            (gamePad3.isPushing3ButtonReset() ? (c3bcnt[3] != 0 ? c3bcnt[3] : OSGetTime()) : 0);

        OSTime resetTime0 = (c3bcnt[0] != 0) ? (OSGetTime() - c3bcnt[0]) : 0;
        OSTime resetTime1 = (c3bcnt[1] != 0) ? (OSGetTime() - c3bcnt[1]) : 0;
        OSTime resetTime2 = (c3bcnt[2] != 0) ? (OSGetTime() - c3bcnt[2]) : 0;
        OSTime resetTime3 = (c3bcnt[3] != 0) ? (OSGetTime() - c3bcnt[3]) : 0;

        gamePad0.checkResetCallback(resetTime0);
        gamePad1.checkResetCallback(resetTime1);
        gamePad2.checkResetCallback(resetTime2);
        gamePad3.checkResetCallback(resetTime3);

        if (out_trigger)
        {
            *out_trigger = gamePad0.getTrigger() | gamePad1.getTrigger() | gamePad2.getTrigger() |
                           gamePad3.getTrigger();
        }
        if (out_button)
        {
            *out_button = gamePad0.getButton() | gamePad1.getButton() | gamePad2.getButton() |
                          gamePad3.getButton();
        }

        result = true;
    }
    else if (mPadPort >= JUTGamePad::Port1)
    {
        JUTGamePad gamePad(mPadPort);
        OSTime &gamePadTime = c3bcnt[0];
        gamePadTime =
            (gamePad.isPushing3ButtonReset() ? (gamePadTime != 0 ? gamePadTime : OSGetTime()) : 0);

        OSTime resetTime = (gamePadTime != 0) ? (OSGetTime() - gamePadTime) : 0;
        gamePad.checkResetCallback(resetTime);

        JUTGamePad::read();
        if (out_trigger)
        {
            *out_trigger = gamePad.getTrigger();
        }
        if (out_button)
        {
            *out_button = gamePad.getButton();
        }

        result = true;
    }
    else if (mGamePad)
    {
        JUTGamePad::read();
        if (out_trigger)
        {
            *out_trigger = mGamePad->getTrigger();
        }
        if (out_button)
        {
            *out_button = mGamePad->getButton();
        }

        result = true;
    }

    return result;
}

void JUTException::printContext(OSError error, OSContext *context, u32 dsisr, u32 dar)
{
    bool is_pad_enabled = isEnablePad() ? false : true;
    if (!sErrorManager->mDirectPrint->isActive())
    {
        return;
    }
    VISetPreRetraceCallback(nullptr);
    VISetPostRetraceCallback(nullptr);
    VISetBlack(FALSE);
    VIFlush();

    if (!sConsole)
    {
        return;
    }

    if(error < (OS_ERROR_FPE + 1))
        sConsole->print_f("******** EXCEPTION OCCURRED! ********\nFrameMemory:%XH\n", getFrameMemory());
    else
        sConsole->print_f("******** USER HALT ********\nFrameMemory:%XH\n", getFrameMemory());

    int post_callback_executed = false;
    while (true)
    {
        showMainInfo(error, context, dsisr, dar);

        JUTConsoleManager::sManager->drawDirect(true);
        waitTime(mPrintWaitTime0);

        if ((mPrintFlags & EXPRINTFLAG_GPR) != 0)
        {
            printDebugInfo(INFOPAGE_GPR, error, context, dsisr, dar);
            JUTConsoleManager::sManager->drawDirect(true);
            waitTime(mPrintWaitTime0);
        }
        if ((mPrintFlags & EXPRINTFLAG_SRR0Map) != 0)
        {
            printDebugInfo(INFOPAGE_SRR0Map, error, context, dsisr, dar);
            JUTConsoleManager::sManager->drawDirect(true);
            waitTime(mPrintWaitTime0);
        }
        if ((mPrintFlags & EXPRINTFLAG_GPRMap) != 0)
        {
            printDebugInfo(INFOPAGE_GPRMap, error, context, dsisr, dar);
            JUTConsoleManager::sManager->drawDirect(true);
            waitTime(mPrintWaitTime0);
        }
        if ((mPrintFlags & EXPRINTFLAG_Float) != 0)
        {
            printDebugInfo(INFOPAGE_Float, error, context, dsisr, dar);
            JUTConsoleManager::sManager->drawDirect(true);
            waitTime(mPrintWaitTime0);
        }
        if ((mPrintFlags & EXPRINTFLAG_Stack) != 0)
        {
            printDebugInfo(INFOPAGE_Stack, error, context, dsisr, dar);
            JUTConsoleManager::sManager->drawDirect(true);
            waitTime(mPrintWaitTime1);
        }

        sConsole->print("--------------------------------\n");
        JUTConsoleManager::sManager->drawDirect(true);

        if (post_callback_executed == 0 && sPostUserCallback)
        {
            BOOL enable = OSEnableInterrupts();
            post_callback_executed = true;
            (*sPostUserCallback)(error, context, dsisr, dar);
            OSRestoreInterrupts(enable);
        }

        if (_98 == 0 || !is_pad_enabled)
        {
            break;
        }

        sConsole->setOutput(sConsole->getOutput() & 1);
    }

    if (!is_pad_enabled)
    {
        OSEnableInterrupts();

        u32 button;
        u32 trigger;

        int down = 0;
        int up = 0;
        do
        {
            readPad(&trigger, &button);

            bool draw = false;
            if (trigger == 0x100)
            {
                sConsole->scrollToLastLine();
                draw = true;
            }

            if (trigger == 0x200)
            {
                sConsole->scrollToFirstLine();
                draw = true;
            }

            if (button == 8)
            {
                JUTConsole *console = sConsole;
                up = (down < 3) ? -1 : ((down < 5) ? -2 : ((down < 7) ? -4 : -8));

                console->scroll(up);
                draw = true;
                up = 0;
                down++;
            }
            else if (button == 4)
            {
                JUTConsole *console = sConsole;
                down = (up < 3) ? 1 : ((up < 5) ? 2 : ((up < 7) ? 4 : 8));

                console->scroll(down);
                draw = true;
                down = 0;
                up++;
            }
            else
            {
                down = 0;
                up = 0;
            }

            if (draw == true)
            {
                u32 start = VIGetRetraceCount();
                while (start == VIGetRetraceCount())
                    ;
                JUTConsoleManager::sManager->drawDirect(true);
            }

            waitTime(30);
        } while (true);
    }

    while (true)
    {
        sConsole->scrollToFirstLine();
        JUTConsoleManager::sManager->drawDirect(true);
        waitTime(2000);

        int line_offset;
        int used_line;
        u32 height;
    next:
        for (u32 i = sConsole->getHeight(); i > 0; i--)
        {
            sConsole->scroll(1);
            JUTConsoleManager::sManager->drawDirect(true);

            height = sConsole->getHeight();
            JUTConsole *console = sConsole;
            line_offset = console->getLineOffset();
            used_line = console->getUsedLine();
            if ((used_line - height) + 1U <= line_offset)
                break;
            waitTime(20);
        }

        waitTime(3000);
        height = sConsole->getHeight();
        JUTConsole *console = sConsole;
        line_offset = console->getLineOffset();
        used_line = console->getUsedLine();
        if ((used_line - height) + 1U <= line_offset)
        {
            continue;
        }
        goto next;
    }
}

void JUTException::waitTime(s32 timeout_ms)
{
    if (timeout_ms)
    {
        OSTime start_time = OSGetTime();
        OSTime ms;
        do
        {
            OSTime end_time = OSGetTime();
            OSTime ticks = end_time - start_time;
            ms = ticks / (OS_TIMER_CLOCK / 1000);
        } while (ms < timeout_ms);
    }
}

void JUTException::createFB()
{
    GXRenderModeObj *renderMode = &GXNtsc480Int;
    void *end = (void *)OSGetArenaHi();
    u16 width = ALIGN_NEXT(renderMode->fbWidth, 16);
    u16 height = renderMode->xfbHeight;
    u32 pixel_count = width * height;
    u32 size = pixel_count * 2;

    void *begin = (void *)ALIGN_PREV((u32)end - size, 32);
    void *object = (void *)ALIGN_PREV((s32)begin - sizeof(JUTExternalFB), 32);
    new (object) JUTExternalFB(renderMode, GX_GM_1_7, begin, size);

    mDirectPrint->changeFrameBuffer(begin, renderMode->fbWidth, renderMode->efbHeight);
    VIConfigure(renderMode);
    VISetNextFrameBuffer(begin);
    VISetBlack(FALSE);
    VIFlush();
    VIFlush();

    for(int i = 0; i < 3; i++) {
        u32 retraceCount = VIGetRetraceCount();
        do {
            
        } while(retraceCount == VIGetRetraceCount());
    }


    mFrameMemory = (JUTExternalFB *)object;
}

JUTErrorHandler JUTException::setPreUserCallback(JUTErrorHandler callback)
{
    JUTErrorHandler previous = sPreUserCallback;
    sPreUserCallback = callback;
    return previous;
}

JUTErrorHandler JUTException::setPostUserCallback(JUTErrorHandler callback)
{
    JUTErrorHandler previous = sPostUserCallback;
    sPostUserCallback = callback;
    return previous;
}

void JUTException::appendMapFile(const char *path)
{
    if (!path)
    {
        return;
    }

    JSUListIterator<JUTExMapFile> iterator;
    for (iterator = sMapFileList.getFirst(); iterator != sMapFileList.getEnd(); ++iterator)
    {
        if (strcmp(path, iterator->mFileName) == 0)
        {
            return;
        }
    }

    JUTExMapFile *mapFile = new JUTExMapFile((char *)path);
    sMapFileList.append(&mapFile->mLink);
}

bool JUTException::queryMapAddress(char *mapPath, u32 address, s32 section_id, u32 *out_addr, u32 *out_size, char *out_line, u32 line_length, bool print, bool begin_with_newline)
{
    if (mapPath)
    {
        char buffer[80];
        strcpy(buffer, mapPath);
        strcat(buffer, ".map");
        if (queryMapAddress_single(buffer, address, section_id, out_addr, out_size, out_line,
                                   line_length, print, begin_with_newline) == true)
        {
            return true;
        }
    }
    else if (sMapFileList.getFirst() != sMapFileList.getEnd())
    {
        if (queryMapAddress_single(sMapFileList.getFirst()->getObject()->mFileName, address, -1,
                                   out_addr, out_size, out_line, line_length, print,
                                   begin_with_newline) == true)
        {
            return true;
        }
    }

    return false;
}

bool JUTException::queryMapAddress_single(char *mapPath, u32 address, s32 section_id, u32 *out_addr, u32 *out_size, char *out_line, u32 line_length, bool print, bool begin_with_newline)
{
    /* fake match on TP debug? */
    if (!mapPath)
    {
        return false;
    }

    char section_name[16];
    char buffer[0x200];
    JUTDirectFile file;
    int section_idx = 0;
    if (!file.fopen(mapPath))
    {
        return false;
    }

    bool result = false;
    bool found_section;

    while (true)
    {
        section_idx++;
        found_section = false;
        while (true)
        {
            char *src;
            char *dst;

            if (file.fgets(buffer, ARRAY_COUNT(buffer)) < 0)
                break;
            if (buffer[0] != '.')
                continue;

            int i = 0;
            src = buffer + 1;
            while (*src != '\0')
            {
                section_name[i] = *src;
                if (*src == ' ' || i == 0xf)
                    break;
                i++;
                src++;
            }

            section_name[i] = 0;
            if (*src == 0)
                break;

            if (src[1] == 's' && src[2] == 'e' && src[3] == 'c' && src[4] == 't')
            {
                found_section = true;
                break;
            }
        }

        if (!found_section)
            break;

        if (section_id >= 0 && section_id != section_idx)
            continue;

        int length;        

        while (true)
        {            
            if ((length = file.fgets(buffer, ARRAY_COUNT(buffer))) <= 4)
                break;
            if ((length < 28))
                continue;
            if ((buffer[28] == '4'))
            {
                u32 addr = ((buffer[18] - '0') << 28) | strtol(buffer + 19, nullptr, 16);
                int size = strtol(buffer + 11, nullptr, 16);
                if ((addr <= address && address < addr + size))
                {
                    if (out_addr)
                        *out_addr = addr;

                    if (out_size)
                        *out_size = size;

                    if (out_line)
                    {
                        const u8 *src = (const u8 *)&buffer[0x1e];
                        u8 *dst = (u8 *)out_line;
                        u32 i = 0;

                        for (i = 0; i < line_length - 1; ++src)
                        {
                            if ((u32)(*src) < ' ' && (u32)*src != '\t')
                                break;
                            if ((*src == ' ' || (u32)*src == '\t') && (i != 0))
                            {
                                if (dst[-1] != ' ')
                                {
                                    *dst = ' ';
                                    dst++;
                                    ++i;
                                }
                            }
                            else
                            {
                                *dst++ = *src;
                                i++;
                            }
                        }

                        if (i != 0 && dst[-1] == ' ')
                        {
                            dst--;
                            i--;
                        }
                        *dst = 0;
                        
                        if (print)
                        {
                            if (begin_with_newline)
                            {
                                sConsole->print("\n");
                            }
                            sConsole->print_f("  [%08X]: .%s [%08X: %XH]\n  %s\n", address, section_name, addr, size, out_line);
                            begin_with_newline = false;
                        }
                    }
                    result = true;
                    break;
                }
            }
            (void)0; // memes
        }

        //if (!result)
        //{
        if ((section_id < 0 || section_id != section_idx))
        {
            goto cont;
        }
        //}
        if (print && begin_with_newline)
        {
            sConsole->print("\n");
        }
        break;
    cont:;
    }

    file.fclose();
    return result ? true : false;
}

void JUTException::createConsole(void *console_buffer, u32 console_buffer_size)
{
    if (!console_buffer || !console_buffer_size)
    {
        return;
    }

    u32 lines = JUTConsole::getLineFromObjectSize(console_buffer_size, 0x32);
    if (lines != 0)
    {
        sConsoleBuffer = console_buffer;
        sConsoleBufferSize = console_buffer_size;
        sConsole = JUTConsole::create(0x32, console_buffer, console_buffer_size);

        JUTConsoleManager *manager = JUTConsoleManager::sManager;
        manager->setDirectConsole(sConsole);

        sConsole->setFontSize(10.0, 6.0);
        sConsole->setPosition(15, 26);
        sConsole->setHeight(23);
        sConsole->setVisible(true);
        sConsole->setOutput(JUTConsole::OUTPUT_OSR_AND_CONSOLE);
    }
}

JUTExternalFB::JUTExternalFB(GXRenderModeObj *renderMode, GXGamma gamma, void *buffer, u32 size)
{
    mRenderModeObj = renderMode;
    mSize = size;
    _0C = 1;
    mGamma = gamma;
    _10 = false;
}