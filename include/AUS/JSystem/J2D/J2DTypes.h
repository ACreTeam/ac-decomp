#ifndef _JSYSTEM_J2D_J2DTYPES_H
#define _JSYSTEM_J2D_J2DTYPES_H

/**
 * Header for J2D POD and nearly POD types, as well as defines, typedefs, and enums that aren't specific to a particular non-POD type.
 */
#include "dolphin/mtx.h"
#include "JSystem/JUtility/TColor.h"
#include "types.h"

struct JUTTexture;

enum J2DBinding {
    J2DBIND_Bottom = 1,
    J2DBIND_Top    = 2,
    J2DBIND_Right  = 4,
    J2DBIND_Left   = 8,
    J2DBIND_Unk15  = 15,
};

enum J2DMirror {
    J2DMIRROR_Unk0 = 0,
    J2DMIRROR_Y    = 1,
    J2DMIRROR_X    = 2,
};

inline u16 J2DCalcAlphaCmp(s32 param_1, u32 param_2, u32 param_3) { return ((param_1) << 5) | ((param_2) << 3) | (param_3 & 0xff); }

extern const u16 j2dDefaultAlphaCmp;

struct J2DAlphaCompInfo {
    u8 _00;   // _00
    u8 _01;   // _01
    u8 mRef0; // _02
    u8 mRef1; // _03
    u8 _04;   // _04
    u8 _05;   // _05
    u8 _06;   // _06
    u8 _07;   // _07
};

struct J2DAlphaComp {
    J2DAlphaComp()
    {
        mAlphaCmp = j2dDefaultAlphaCmp;
        mRef0     = 0;
        mRef1     = 0;
    }
    J2DAlphaComp(const J2DAlphaCompInfo& info)
    {
        mAlphaCmp = J2DCalcAlphaCmp(info._00, info.mRef0, info.mRef1);
        mRef0     = info._01;
        mRef1     = info._04;
    }
    u8 getComp0() { return mAlphaCmp >> 5 & 7; }
    u8 getRef0() { return mRef0; }
    u8 getOp() { return mAlphaCmp >> 3 & 3; }
    u8 getComp1() { return mAlphaCmp & 7; }
    u8 getRef1() { return mRef1; }

    u16 mAlphaCmp; // _00
    u8 mRef0;      // _02
    u8 mRef1;      // _03
};


struct J2DGrafBlend {
    u8 mType;       // _00
    u8 mSrcFactor;  // _01
    u8 mDestFactor; // _02
};

struct J2DBlendInfo {
    // J2DBlendInfo() { }

    void operator=(J2DBlendInfo const& other)
    {
        mType       = other.mType;
        mSrcFactor  = other.mSrcFactor;
        mDestFactor = other.mDestFactor;
        mOp         = other.mOp;
    }

    // J2DBlendInfo(u8 type, u8 src, u8 dst, u8 op)
    // {
    //     mType       = type;
    //     mSrcFactor  = src;
    //     mDestFactor = dst;
    //     mOp         = op;
    // }

    u8 mType;       // _00
    u8 mSrcFactor;  // _01
    u8 mDestFactor; // _02
    u8 mOp;         // _03
};

extern const J2DBlendInfo j2dDefaultBlendInfo;

struct J2DBlend {
    J2DBlend() { mInfo = j2dDefaultBlendInfo; }
    J2DBlend(const J2DBlendInfo& info) { mInfo = info; }

    void setBlendInfo(const J2DBlendInfo& info) { mInfo = info; }
    u8 getType() { return mInfo.mType; }
    u8 getSrcFactor() { return mInfo.mSrcFactor; }
    u8 getDstFactor() { return mInfo.mDestFactor; }
    u8 getOp() { return mInfo.mOp; }

    inline void set(J2DBlend blend)
    {
        mInfo.mType       = blend.mInfo.mType;
        mInfo.mSrcFactor  = blend.mInfo.mSrcFactor;
        mInfo.mDestFactor = blend.mInfo.mDestFactor;
        mInfo.mOp         = blend.mInfo.mOp;
    }

    J2DBlendInfo mInfo;
};

struct J2DColorChanInfo {
    u8 _00; // _00
    u8 _01; // _01
    u8 _02; // _02, padding?
    u8 _03; // _03, padding?
};

inline u8 J2DCalcColorChanID(u8 id) { return id; }
extern const J2DColorChanInfo j2dDefaultColorChanInfo;

/**
 * @size{0x2}
 */
struct J2DColorChan {
    J2DColorChan() { setColorChanInfo(j2dDefaultColorChanInfo); }
    J2DColorChan(const J2DColorChanInfo& info) { mColorChan = J2DCalcColorChanID(info._01); }
    void setColorChanInfo(const J2DColorChanInfo& info) { mColorChan = J2DCalcColorChanID(info._01); }
    u32 getMatSrc() const { return mColorChan & 1; }

    u16 mColorChan; // _00
};

struct J2DTevOrderInfo {
    u8 mTexCoord; // _00
    u8 mTexMap;   // _01
    u8 mColor;    // _02
    u8 _03;       // _03

    J2DTevOrderInfo& operator=(const J2DTevOrderInfo& other)
    {
        mTexCoord = other.mTexCoord;
        mTexMap   = other.mTexMap;
        mColor    = other.mColor;
        return *this;
    }
};

extern const J2DTevOrderInfo j2dDefaultTevOrderInfoNull;

struct J2DTevOrder {
    J2DTevOrder() { mTevOrderInfo = j2dDefaultTevOrderInfoNull; }

    J2DTevOrder(const J2DTevOrderInfo& info) { mTevOrderInfo = info; }

    /** @fabricated */
    inline J2DTevOrder(u8 texCoord, u8 texMap, u8 color)
    {
        mTevOrderInfo.mTexCoord = texCoord;
        mTevOrderInfo.mTexMap   = texMap;
        mTevOrderInfo.mColor    = color;
    }

    /** @fabricated */
    inline J2DTevOrder& operator=(const J2DTevOrderInfo& other)
    {
        mTevOrderInfo = other;
        return *this;
    }

    /** @fabricated */
    inline J2DTevOrder& operator=(const J2DTevOrder& other)
    {
        mTevOrderInfo = other.mTevOrderInfo;
        return *this;
    }

    void setTevOrderInfo(const J2DTevOrderInfo& info) { mTevOrderInfo = info; }
    inline GXChannelID getColor() const { return (GXChannelID)mTevOrderInfo.mColor; }
    inline GXTexMapID getTexMap() const { return (GXTexMapID)mTevOrderInfo.mTexMap; }
    inline GXTexCoordID getTexCoord() const { return (GXTexCoordID)mTevOrderInfo.mTexCoord; }

    J2DTevOrderInfo mTevOrderInfo; // _00
};

struct J2DTevSwapModeInfo {
    const u8 mRasSel; // _00
    const u8 mTexSel; // _01
    u8 _02;     // _02
    u8 _03;     // _03
};

struct J2DTevSwapModeTableInfo {
    u8 mR; // _00
    u8 mG; // _01
    u8 mB; // _02
    u8 mA; // _03
};

extern const J2DTevSwapModeInfo j2dDefaultTevSwapMode;
extern const J2DTevSwapModeTableInfo j2dDefaultTevSwapModeTable;
extern const u8 j2dDefaultTevSwapTable;

inline u8 J2DCalcTevSwapTable(u8 r, u8 g, u8 b, u8 a) { return ((r&0xff) << 6) + ((g&0xff) << 4) + ((b&0xff) << 2) + a; }

struct J2DTevSwapModeTable {
    J2DTevSwapModeTable() { _00 = j2dDefaultTevSwapTable; }

    J2DTevSwapModeTable(const J2DTevSwapModeTableInfo& info) { _00 = J2DCalcTevSwapTable(info.mR, info.mG, info.mB, info.mA); }

    void setTevSwapModeTableInfo(const J2DTevSwapModeTableInfo& info)
    {
        _00  = J2DCalcTevSwapTable(info.mR, info.mG, info.mB, info.mA);
    }

    u8 getR() { return _00 >> 6 & 3; }
    u8 getG() { return _00 >> 4 & 3; }
    u8 getB() { return _00 >> 2 & 3; }
    u8 getA() { return _00 & 3; }

    u8 _00; // _00
};

struct J2DTevStageInfo {
    u8 _00;     // _00
    u8 mColorA; // _01
    u8 mColorB; // _02
    u8 mColorC; // _03
    u8 mColorD; // _04
    u8 mCOp;    // _05
    u8 mCBias;  // _06
    u8 mCScale; // _07
    u8 mCClamp; // _08
    u8 mCReg;   // _09
    u8 mAlphaA; // _0A
    u8 mAlphaB; // _0B
    u8 mAlphaC; // _0C
    u8 mAlphaD; // _0D
    u8 mAOp;    // _0E
    u8 mABias;  // _0F
    u8 mAScale; // _10
    u8 mAClamp; // _11
    u8 mAReg;   // _12
    u8 _13;     // _13
};


struct J2DIndTevStageInfo {
    inline void operator=(const J2DIndTevStageInfo& other)
    {
        mIndStage  = other.mIndStage;
        mIndFormat = other.mIndFormat;
        mBiasSel   = other.mBiasSel;
        mMtxSel    = other.mMtxSel;
        mWrapS     = other.mWrapS;
        mWrapT     = other.mWrapT;
        mPrev      = other.mPrev;
        mLod       = other.mLod;
        mAlphaSel  = other.mAlphaSel;
    }

    u8 mIndStage;  // _00
    u8 mIndFormat; // _01
    u8 mBiasSel;   // _02
    u8 mMtxSel;    // _03
    u8 mWrapS;     // _04
    u8 mWrapT;     // _05
    u8 mPrev;      // _06
    u8 mLod;       // _07
    u8 mAlphaSel;  // _08
    u8 _09;        // _09
    u8 _0A;        // _0A
    u8 _0B;        // _0B
};

struct J2DTexCoordInfo {
    u8 mTexGenType; // _00
    u8 mTexGenSrc;  // _01
    u8 mTexGenMtx;  // _02

    u8 _03; // _03 - padding?

    J2DTexCoordInfo& operator=(const J2DTexCoordInfo& other)
    {
        mTexGenType = other.mTexGenType;
        mTexGenSrc  = other.mTexGenSrc;
        mTexGenMtx  = other.mTexGenMtx;
        return *this;
    }
};

extern const J2DTexCoordInfo j2dDefaultTexCoordInfo[8];

struct J2DTexCoord {
    J2DTexCoord() { mTexCoordInfo = j2dDefaultTexCoordInfo[0]; }
    // J2DTexCoordInfo _00;

    J2DTexCoord(J2DTexCoordInfo& info) { mTexCoordInfo = info; }
    J2DTexCoord(const J2DTexCoordInfo& info) { mTexCoordInfo = info; }

    void setTexCoordInfo(const J2DTexCoordInfo& info) { mTexCoordInfo = info; }
    s32 getTexGenType() { return mTexCoordInfo.mTexGenType; }
    s32 getTexGenSrc() { return mTexCoordInfo.mTexGenSrc; }
    s32 getTexGenMtx() { return mTexCoordInfo.mTexGenMtx; }

    void setTexGenMtx(u8 mtx) { mTexCoordInfo.mTexGenMtx = mtx; }

    J2DTexCoordInfo mTexCoordInfo; // _00
};

extern const J2DTevStageInfo j2dDefaultTevStageInfo;
extern const GXColor j2dDefaultColInfo;
extern const GXColorS10 j2dDefaultTevColor;
extern const GXColor j2dDefaultTevKColor;

extern const u8 j2dDefaultDither;

enum J2DTextBoxHBinding {
    J2DHBIND_Center = 0,
    J2DHBIND_Right  = 1,
    J2DHBIND_Left   = 2,
};

enum J2DTextBoxVBinding {
    J2DVBIND_Center = 0,
    J2DVBIND_Bottom = 1,
    J2DVBIND_Top    = 2,
};

#endif
