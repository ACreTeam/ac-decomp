#ifndef _JSYSTEM_J2D_J2DGXCOLORS10_H
#define _JSYSTEM_J2D_J2DGXCOLORS10_H

#include "types.h"
#include <dolphin/gx.h>

#include "JSystem/JUtility/TColor.h"

/**
 * Everything is fabricated here except for the default ctor.
 * Copied from J3DGXColorS10. 
 */
struct J2DGXColorS10 : public GXColorS10
{
    J2DGXColorS10() {}

    J2DGXColorS10(u16 _r, u16 _g, u16 _b, u16 _a)
    {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    /** @fabricated */
    J2DGXColorS10 &operator=(const GXColorS10 &other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
        return *this;
    }

    J2DGXColorS10(const GXColorS10 &other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
    }

    J2DGXColorS10(const J2DGXColorS10 &other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
    }

    J2DGXColorS10(const u64 &other)
    {
        GXColorS10 *otherBytes = (GXColorS10 *)&other;
        r = otherBytes->r;
        g = otherBytes->g;
        b = otherBytes->b;
        a = otherBytes->a;
    }

    // TODO: remove when const issue has been resolved
    J2DGXColorS10(J2DGXColorS10 &other) 
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
    }
    J2DGXColorS10(GXColorS10 &other)
    {
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
    }

    inline operator u64() const { return toUInt64(); }
    inline u32 toUInt64() const { return *(u64 *)&r; }

    inline operator JUtility::TColor() const { return toTColor(); }
    inline JUtility::TColor toTColor() const { return JUtility::TColor(r, g, b, a); }
};

#endif
