#include "JSystem/JUtility/JUTFont.h"
#include "JSystem/JUtility/JUTAssertion.h"

JUTFont::JUTFont() : mColor1(), mColor2(), mColor3(), mColor4()
{
    mValid = false;
}

void JUTFont::initialize_state()
{
    setCharColor(JUtility::TColor());
    setFixedWidth(false, 0);
    mValid = false;
}

void JUTFont::setCharColor(JUtility::TColor color)
{
    mColor1 = color;
    mColor2 = color;
    mColor3 = color;
    mColor4 = color;
}

void JUTFont::setGradColor(JUtility::TColor color, JUtility::TColor color2)
{
    mColor1 = color;
    mColor2 = color;
    mColor3 = color2;
    mColor4 = color2;
}

f32 JUTFont::drawString_size_scale(f32 w, f32 x, f32 y, f32 z, const char *str, u32 usz, bool flag)
{
    int str_int;
    f32 w_old = w;

    for (; usz != 0; usz--, str++)
    {
        str_int = (u8)*str;
        if (isLeadByte(str_int))
        {
            JUT_ASSERT(usz >= 2);
            usz--;
            str++;
            str_int <<= 8;
            str_int |= (u8)*str;
        }
        w += (drawChar_scale(w, x, y, z, str_int, flag));
        flag = true;
    }
    return w - w_old;
}