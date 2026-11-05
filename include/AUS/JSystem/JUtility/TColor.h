
#ifndef _JSYSTEM_JUT_TCOLOR_H
#define _JSYSTEM_JUT_TCOLOR_H

#include "macros.h"
#include "types.h"
#include <dolphin/gx.h>

#define GXCOLOR_AS_U32(color)   (*((u32*)&(color)))
#define RGBA_TO_U32(r, g, b, a) (((u8)(r) << 24) | ((u8)(g) << 16) | ((u8)(b) << 8) | ((u8)(a)))
#define TCOLOR_WHITE JUtility::TColor(0xFF, 0xFF, 0xFF, 0xFF)
#define TCOLOR_BLACK JUtility::TColor(0, 0, 0, 0)
#define TCOLOR_WHITE_U32 0xFFFFFFFF
#define TCOLOR_BLACK_U32 0x00000000

namespace JUtility
{
    struct TColor : public GXColor
    {
        TColor() { set(0xFFFFFFFF); }

        TColor(u8 _r, u8 _g, u8 _b, u8 _a) { set(_r, _g, _b, _a); }

        TColor(u32 u32Color) { set(u32Color); }

        TColor(GXColor color) { set(color); }

        /** @fabricated */
        TColor &operator=(const GXColorS10 &other)
        {
            r = other.r;
            g = other.g;
            b = other.b;
            a = other.a;
            return *this;
        }

        operator u32() const { return toUInt32(); }
        u32 toUInt32() const { return *(u32 *)&r; }

        void set(u8 cR, u8 cG, u8 cB, u8 cA)
        {
            r = cR;
            g = cG;
            b = cB;
            a = cA;
        }

        void set(u32 u32Color) { *(u32 *)&r = u32Color; }

        void set(GXColor gxColor) { *(GXColor *)&r = gxColor; }
        //void set(TColor color) { *this = color; }

        void setRGB(u8 cR, u8 cG, u8 cB)
        {
            r = cR;
            g = cG;
            b = cB;
        }

        void setRGB(const TColor &other) { setRGB(other.r, other.g, other.b); }

        void setRGBA(const TColor &other)
        {
            r = other.r;
            g = other.g;
            b = other.b;
            a = other.a;
        }

        // fabricated. but helped solve regswaps in a function
        void setRGBA(const TColor &RGB, u8 _a)
        {
            setRGB(RGB);
            a = _a;
        }

        // _00 = GXColor (_00 = r, _01 = g, _02 = b, _03 = a)
    } ATTRIBUTE_ALIGN(4);
} // namespace JUtility

typedef JUtility::TColor JUTColor;

#endif
