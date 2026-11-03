#include <dolphin/os.h>
#include <dolphin/vi.h>
#include <dolphin/hw_regs.h>

// there shoudl be more in this file, however this is the only thing that gets used, i'm not gonna add 1000 lines of text that have no value here

u16 OSGetFontEncode()
{
    static u16 fontEncode = OS_FONT_ENCODE_NULL;

    if (fontEncode <= 1)
    {
        return fontEncode;
    }

    switch (__OSTVMode)
    {
    case VI_NTSC:
        fontEncode = (__VIRegs[VI_DTV_STAT] & 2) ? OS_FONT_ENCODE_SJIS : OS_FONT_ENCODE_ANSI;
        break;

    case VI_PAL:
    case VI_MPAL:
    case VI_DEBUG:
    case VI_DEBUG_PAL:
    case VI_EURGB60:
    default:
        fontEncode = OS_FONT_ENCODE_ANSI;
    }

    return fontEncode;
}
