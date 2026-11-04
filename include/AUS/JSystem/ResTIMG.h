#ifndef _JSYSTEM_RESTIMG_H
#define _JSYSTEM_RESTIMG_H

#include "dolphin/gx.h"
#include "types.h"

#ifdef __cplusplus

#ifndef _JUTTransparency
typedef u8 _JUTTransparency;
#endif

enum {
    ResTIMG_FORMAT_C8 = 9
    // TODO: others
};

enum { ResTIMG_NO_PALETTE, ResTIMG_PALETTE };

struct ResTIMG {
    inline BOOL isMIPmapEnabled() const {
        return (mIsMIPmapEnabled > 0);
    }

    inline u16 getWidth() const {
        return mSizeX;
    }
    inline u16 getHeight() const {
        return mSizeY;
    }

    u8 mTextureFormat;              // _00
    _JUTTransparency mTransparency; // _01
    u16 mSizeX;                     // _02
    u16 mSizeY;                     // _04
    u8 mWrapS;                      // _06
    u8 mWrapT;                      // _07
    u8 mPaletteFormat;              // _08
    u8 mColorFormat;                // _09
    u16 mPaletteEntryCount;         // _0A
    u32 mPaletteOffset;             // _0C
    GXBool mIsMIPmapEnabled;        // _10
    GXBool mDoEdgeLOD;              // _11
    GXBool mIsBiasClamp;            // _12
    GXBool mIsMaxAnisotropy;        // _13
    u8 mMinFilterType;              // _14
    u8 mMagFilterType;              // _15
    s8 mMinLOD;                     // _16
    s8 mMaxLOD;                     // _17
    u8 mTotalImageCount;            // _18
    u8 _19;                         // _19, unknown
    s16 mLODBias;                   // _1A
    u32 mImageDataOffset;           // _1C
};

struct ResTIMGPair {
    ResTIMG _00;
    ResTIMG _20;
};
#endif
#endif
