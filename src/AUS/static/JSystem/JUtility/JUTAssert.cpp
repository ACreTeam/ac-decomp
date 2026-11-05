#include "MSL_C/printf.h"
#include "types.h"
#include <dolphin/pad.h>
#include <dolphin/vi.h>
#include "JSystem/JUtility/JUTAssert.h"
#include "JSystem/JUtility/JUTConsole.h"
#include "JSystem/JUtility/JUTDbPrint.h"
#include "JSystem/JUtility/JUTDirectPrint.h"

namespace JUTAssertion
{
    namespace
    {
        static u32 sMessageLife;
        static u32 sMessageOwner;
        static bool mSynchro;
        static char sMessageFileLine[64];
        static char sMessageString[256];

        static u32 sDisplayTime = -1;
        static u32 sDevice = 3;
        static bool sVisible = true;
    }

    void create() {}

    u32 flush_subroutine()
    {
        if (sMessageLife == 0) {
            return 0;
        }
        if (sMessageLife != -1) {
            sMessageLife--;
        }
        if (sMessageLife < 5) {
            return 0;
        }
        return sMessageLife;
    }

    void flushMessage()
    {
        if (flush_subroutine() && sVisible == true)
        {
            JUTDirectPrint *manager = JUTDirectPrint::getManager();
            JUtility::TColor color = manager->getCharColor();
            manager->setCharColor(JUtility::TColor(255, 200, 200, 255));
            manager->drawString(16, 16, sMessageFileLine);
            manager->drawString(16, 24, sMessageString);
            manager->setCharColor(color);
        }
    }

    void flushMessage_dbPrint()
    {
        if (flush_subroutine() && sVisible == true && JUTDbPrint::getManager())
        {
            JUTFont *font = JUTDbPrint::getManager()->getFont();
            if (font)
            {
                u8 tmp = ((VIGetRetraceCount() & 60) << 2) | 0xF;
                font->setGX();
                font->setCharColor(JUtility::TColor(255, tmp, tmp, 255));
                font->drawString(30, 36, sMessageFileLine, true);
                font->drawString(30, 54, sMessageString, true);
            }
        }
    }
    
    void changeDisplayTime(u32 time) {
        sDisplayTime = time;
    }
    void changeDevice(u32 device) {
        sDevice = device;
    }

#if DEBUG
    u32 getSDevice() {
        return sDevice;
    }

    void setConfirmMessage(u32 device, char *file, int line, bool condition, const char *msg) {
        if (condition == true) 
            return;

        u32 messageLife = sMessageLife;
        if(messageLife == 0 && (device & 1)) {
            sMessageLife = sDisplayTime;
            sMessageOwner = 2;
            snprintf(sMessageFileLine, STRING_SIZE(sMessageFileLine), "FAILED [%s:%d]", file, line);
            snprintf(sMessageString, STRING_SIZE(sMessageString) , "%s", msg);
        }
        if ((messageLife == 0 || !mSynchro) && (device & 2)) {
            JUTWarningConsole_f("FAILED [%s:%d] %s\n", file, line, msg);
        }        
    }

    void showAssert_f_va(u32 device, const char *file, int line, const char *fmt, va_list vl)
    {
        sMessageLife = -1;
        vsnprintf(sMessageString, STRING_SIZE(sMessageString), fmt, vl);
        if(device & 2) {
            OSReport("Failed assertion: %s:%d\n", file, line);
            OSReport("%s\n", sMessageString);
        }

        if(device & 1) {
            JUTDirectPrint *directPrint = JUTDirectPrint::getManager();
            if (directPrint) {
                
                JUtility::TColor curColor = directPrint->getCharColor();
                directPrint->setCharColor(TCOLOR_WHITE);
                directPrint->erase(10, 16, 306, 24);

                snprintf(sMessageFileLine, STRING_SIZE(sMessageFileLine), "Failed assertion: %s:%d", file, line);
                directPrint->drawString(16, 16, sMessageFileLine);
                directPrint->drawString(16, 24, sMessageString);

                directPrint->setCharColor(curColor);
                VISetNextFrameBuffer(directPrint->getFrameBuffer());
                VIFlush();
                OSEnableInterrupts();

                u32 count = VIGetRetraceCount();
                while (count == VIGetRetraceCount()) {}


                s64 start_time = OSGetTime();                
                while (OSTicksToMilliseconds(OSGetTime() - start_time) < 2000) {}
            }
        }
    }

    void showAssert_f(u32 device, const char *file, int line, const char *fmt, ...)
    {
        va_list vl;
        va_start(vl, fmt);
        showAssert_f_va(device, file, line, fmt, vl);
        va_end(vl);
    }

    void setWarningMessage_f_va(u32 device, char *file, int line, const char *fmt, va_list vl)
    {
        u32 life = sMessageLife;
        bool showMessage = false;

        PADControlMotor(0, 0);
        PADControlMotor(1, 0);
        PADControlMotor(2, 0);
        PADControlMotor(3, 0);

        if(life == 0) {
            if(device & 1) {
                sMessageLife = sDisplayTime;
                sMessageOwner = 3;
                snprintf(sMessageFileLine, STRING_SIZE(sMessageFileLine), "WARNING [%s:%d]", file, line);
            }
            vsnprintf(sMessageString, STRING_SIZE(sMessageString), fmt, vl);
            showMessage = true;
        }

        if((life == 0 || !mSynchro) && (device & 2)) {
            JUTWarningConsole_f("WARNING [%s:%d] ", file, line);
            if(!showMessage) {
                JUTWarningConsole_f_va(fmt, vl);
            }
            else {
                JUTWarningConsole(sMessageString);
            }
            JUTWarningConsole("\n");
        }
    }

    void setWarningMessage_f(u32 device, char *file, int line, const char *fmt, ...)
    {
        va_list vl;
        va_start(vl, fmt);
        setWarningMessage_f_va(device, file, line, fmt, vl);
        va_end(vl);
    }

    void setLogMessage_f_va(u32 device, char *file, int line, const char *fmt, va_list vl)
    {
        u32 life = sMessageLife;
        bool showMessage = false;
        if (life == 0)
        {
            if (device & 1)
            {
                sMessageLife = sDisplayTime;
                sMessageOwner = 4;
                snprintf(sMessageFileLine, STRING_SIZE(sMessageFileLine), "[%s:%d]", file, line);
            }
            vsnprintf(sMessageString, STRING_SIZE(sMessageString), fmt, vl);
            showMessage = true;
        }

        if ((life == 0 || !mSynchro) && (device & 2))
        {
            JUTReportConsole_f("[%s:%d] ", file, line);
            if (!showMessage)
            {
                JUTReportConsole_f_va(fmt, vl);
            }
            else
            {
                JUTReportConsole(sMessageString);
            }
            JUTReportConsole("\n");
        }
    }

    void setLogMessage_f(u32 device, char *file, int line, const char *fmt, ...) {
        va_list vl;
        va_start(vl, fmt);
        setLogMessage_f_va(device, file, line, fmt, vl);
        va_end(vl);
    }





    void setVisible(bool visible) {
        sVisible = visible;
    }

    bool getVisible() {
        return sVisible;
    }    

    void setMessageCount(int msg_count) {
        sMessageLife = msg_count <= 0 ? 0 : msg_count;
    }

    void setDeviceSynchro(bool synchro) {
        mSynchro = synchro;
    }
#endif
}