#ifndef _JSYSTEM_J3D_J3DTYPES_H
#define _JSYSTEM_J3D_J3DTYPES_H

#include "JSystem/J3D/J3DGXColor.h"
#include "JSystem/JBlockType.h"

#include <dolphin/gx.h>
//#include <dolphin/vec.h>
//#include "JSystem/J3D/J3DGXColor.h"
#include "JSystem/J3D/J3DGD.h"
#include "JSystem/JGeometry.h"
#include "JSystem/JMath/JMath.h"
#include "types.h"

// TODO: Make a bitmask enum
/**
 * @fabricatedName
 */
typedef u32 J3DModelLoaderFlags;
enum J3DModelLoaderFlagTypes {
    J3DMLF_None = 0x00000000,

    J3DMLF_MtxSoftImageCalc = 0x00000001,
    J3DMLF_MtxMayaCalc      = 0x00000002,
    J3DMLF_MtxBasicCalc     = 0x00000004,
    J3DMLF_04               = 0x00000008,
    J3DMLF_MtxTypeMask
    = J3DMLF_MtxSoftImageCalc | J3DMLF_MtxMayaCalc | J3DMLF_MtxBasicCalc | J3DMLF_04, // 0 - 2 (0 = Basic, 1 = SoftImage, 2 = Maya)

    J3DMLF_UseImmediateMtx          = 0x00000010,
    J3DMLF_UsePostTexMtx            = 0x00000020,
    J3DMLF_07                       = 0x00000040,
    J3DMLF_08                       = 0x00000080,
    J3DMLF_NoMatrixTransform        = 0x00000100,
    J3DMLF_10                       = 0x00000200,
    J3DMLF_11                       = 0x00000400,
    J3DMLF_12                       = 0x00000800,
    J3DMLF_13                       = 0x00001000,
    J3DMLF_DoBdlMaterialCalc        = 0x00002000,
    J3DMLF_15                       = 0x00004000,
    J3DMLF_16                       = 0x00008000,
    J3DMLF_TevNumShift              = 0x00010000,
    J3DMLF_18                       = 0x00020000,
    J3DMLF_UseSingleSharedDL        = 0x00040000,
    J3DMLF_20                       = 0x00080000,
    J3DMLF_21                       = 0x00100000,
    J3DMLF_UseUniqueMaterials       = 0x00200000,
    J3DMLF_23                       = 0x00400000,
    J3DMLF_24                       = 0x00800000,
    J3DMLF_Material_UseIndirect     = 0x01000000,
    J3DMLF_26                       = 0x02000000,
    J3DMLF_27                       = 0x04000000,
    J3DMLF_Material_TexGen_Block4   = 0x08000000,
    J3DMLF_Material_PE_Full         = 0x10000000,
    J3DMLF_Material_PE_FogOff       = 0x20000000,
    J3DMLF_Material_Color_LightOn   = 0x40000000,
    J3DMLF_Material_Color_AmbientOn = 0x80000000
};

enum J3DModelFlags {
    J3DMODEL_Unk1              = 0x1,
    J3DMODEL_UseDefaultJ3D     = 0x2,
    J3DMODEL_SkinPosCpu        = 0x4,
    J3DMODEL_SkinNrmCpu        = 0x8,
    J3DMODEL_LevelOfDetail     = 0x10,
    J3DMODEL_Unk6              = 0x20,
    J3DMODEL_Unk7              = 0x40,
    J3DMODEL_Unk8              = 0x80,
    J3DMODEL_Unk9              = 0x100,
    J3DMODEL_Unk10             = 0x200,
    J3DMODEL_Unk11             = 0x400,
    J3DMODEL_Unk12             = 0x800,
    J3DMODEL_Unk13             = 0x1000,
    J3DMODEL_Unk14             = 0x2000,
    J3DMODEL_Unk15             = 0x4000,
    J3DMODEL_Unk16             = 0x8000,
    J3DMODEL_Unk17             = 0x10000,
    J3DMODEL_CreateNewDL       = 0x20000,
    J3DMODEL_UseSingleSharedDL = 0x40000,
    J3DMODEL_ShareDL           = 0x80000,
    J3DMODEL_Unk21             = 0x100000,
    J3DMODEL_Unk22             = 0x200000,
    J3DMODEL_Unk23             = 0x400000,
    J3DMODEL_Unk24             = 0x800000,
    J3DMODEL_Unk25             = 0x1000000,
    J3DMODEL_Unk26             = 0x2000000,
    J3DMODEL_Unk27             = 0x4000000,
    J3DMODEL_Unk28             = 0x8000000,
    J3DMODEL_Unk29             = 0x10000000,
    J3DMODEL_Unk30             = 0x20000000,
    J3DMODEL_Unk31             = 0x40000000,
    J3DMODEL_Unk32             = 0x80000000,
};

/*
 * J3DModelDiffFlags is an enumeration that defines different flags for 3D model differences.
 * Each flag represents a different aspect of the model that can be different.
 *
 * J3DMDF_DiffMatColor:     This flag is set if the material color is different. It corresponds to the 1st bit.
 * J3DMDF_DiffLight:        This flag is set if the light settings are different. It corresponds to the 2nd bit.
 * J3DMDF_DiffTexGen:       This flag is set if the TexCoordGen is different. It corresponds to the 13th bit.
 * J3DMDF_Unknown:          This flag is reserved for a flag that isn't yet understood. It corresponds to the 18th bit.
 * J3DMDF_DiffColorReg:     This flag is set if the color registers (TEV) are different. It corresponds to the 25th bit.
 * J3DMDF_DiffKonstColor:   This flag is set if the Konst colors are different. It corresponds to the 26th bit.
 * J3DMDF_DiffTevOrderFull: This flag is set if the full TevOrder (TexMap and TexCoordIdx) is different. It corresponds to the 27th bit.
 * J3DMDF_DiffIndTevStage:  This flag is set if the indirect TevStages are different. It corresponds to the 28th bit.
 * J3DMDF_DiffFog:          This flag is set if the fog settings are different. It corresponds to the 29th bit.
 * J3DMDF_DiffBlend:        This flag is set if the blend settings are different. It corresponds to the 30th bit.
 *
 * The CREATE_DIFF_FLAG macro is used to create a u32 value with specific flags set.
 * It takes four parameters: lightObjNum, texGenNum, texCoordNum, and tevStageNum. Each parameter is expected to be a 4-bit value.
 * The parameters are shifted to their respective positions in the u32 value and combined using the bitwise OR operator.
 *
 * lightObjNum: This value is shifted to bits 4 - 7.
 * texGenNum:   This value is shifted to bits 8 - 11.
 * texCoordNum:    This value is shifted to bits 16 - 19.
 * tevStageNum: This value is shifted to bits 20 - 23.
 */

enum J3DModelDiffFlags {
    J3DMDF_DiffMatColor = 0x00000001, // Diff material color
    J3DMDF_DiffLight    = 0x00000002, // Diff light settings
    J3DMDF_DiffTexGen   = 0x00001000, // Diff TexCoordGen

    J3DMDF_TexCoord0 = 0x000010000, // TexCoord0
    J3DMDF_TexCoord1 = 0x000020000, // TexCoord1
    J3DMDF_TexCoord2 = 0x000030000, // TexCoord2
    J3DMDF_TexCoord3 = 0x000040000, // TexCoord3
    J3DMDF_TexCoord4 = 0x000050000, // TexCoord4
    J3DMDF_TexCoord5 = 0x000060000, // TexCoord5
    J3DMDF_TexCoord6 = 0x000070000, // TexCoord6
    J3DMDF_TexCoord7 = 0x000080000, // TexCoord7

    J3DMDF_DiffColorReg         = 0x01000000, // Diff color registers (TEV)
    J3DMDF_DiffKonstColor       = 0x02000000, // Diff Konst colors
    J3DMDF_DiffTexCoordScale    = 0x04000000, // Diff TexCoord scales
    J3DMDF_DiffTevStageIndirect = 0x08000000, // Diff indirect TevStages
    J3DMDF_DiffFog              = 0x10000000, // Diff fog settings
    J3DMDF_DiffBlend            = 0x20000000  // Diff blend settings
};

#define CREATE_DIFF_FLAG(lightObjNum, texGenNum, texCoordNum, tevStageNum) \
    (((lightObjNum & 0xf) << 4) | ((texGenNum & 0xf) << 8) | ((texCoordNum & 0xf) << 16) | ((tevStageNum & 0xf) << 20))

inline u32 getDiffFlag_LightObjNum(u32 diffFlags) { return (diffFlags & 0xf0) >> 4; }
inline u32 getDiffFlag_TexGenNum(u32 diffFlags) { return (diffFlags & 0xf00) >> 8; }
inline u32 getDiffFlag_TexNoNum(u32 diffFlags) { return (diffFlags & 0xf0000) >> 16; }
inline u32 getDiffFlag_TevStageNum(u32 diffFlags) { return (diffFlags & 0xf00000) >> 20; }

inline int calcDifferedBufferSize_TexMtxSize(int diffFlags) { return diffFlags * 53; }
inline int calcDifferedBufferSize_TexGenSize(int diffFlags) { return diffFlags * 61 + 10; }
inline int calcDifferedBufferSize_TexNoSize(int diffFlags) { return diffFlags * 55; }
inline u32 calcDifferedBufferSize_TexNoAndTexCoordScaleSize(u32 diffFlags)
{
    u32 res = diffFlags * 55;
    res += ((diffFlags + 1) >> 1) * 55;
    return res;
}
inline int calcDifferedBufferSize_TevStageSize(int diffFlags) { return diffFlags * 10; }
inline int calcDifferedBufferSize_TevStageDirectSize(int diffFlags) { return diffFlags * 5; }

/**
 * @enum J3DErrType
 * @brief Enumerates the types of errors that can occur in the J3D engine.
 *
 * @var J3DErrType::JET_Success
 * Operation completed successfully.
 *
 * @var J3DErrType::JET_NoMatAnm
 * Error occurred due to no material animation.
 *
 * @var J3DErrType::JET_LockedModelData
 * Error occurred due to locked model data.
 *
 * @var J3DErrType::JET_NullBinRes
 * Error occurred due to null binary resource.
 *
 * @var J3DErrType::JET_OutOfMemory
 * Error occurred due to insufficient memory.
 *
 * @var J3DErrType::JET_InvalidArg
 * Error occurred due to an invalid argument.
 *
 * @var J3DErrType::JET_InvalidData
 * Error occurred due to invalid data.
 */
enum J3DErrType {
    JET_Success = 0,
    JET_NoMatAnm,
    JET_LockedModelData,
    JET_NullBinRes,
    JET_OutOfMemory,
    JET_InvalidArg,
    JET_InvalidData,
};

extern u8 j3dTevSwapTableTable[1024];

struct J3DAlphaCompInfo {
    u8 mComp0; // _00
    u8 mRef0;  // _01
    u8 mOp;    // _02
    u8 mComp1; // _03
    u8 mRef1;  // _04
    u8 _05;    // _05
    u8 _06;    // _06
    u8 _07;    // _07
};

inline u16 calcAlphaCmpID(u32 comp0, u32 op, u32 comp1) { return (comp0 << 5) + (op << 3) + (comp1 & 0xFF); }

extern const u16 j3dDefaultAlphaCmpID;
extern u8 j3dAlphaCmpTable[768];

struct J3DAlphaComp {
    J3DAlphaComp()
    {
        mAlphaCmpID = j3dDefaultAlphaCmpID;
        mRef0       = 0;
        mRef1       = 0;
    }

    J3DAlphaComp(u16 id)
        : mAlphaCmpID(id)
        , mRef0(0)
        , mRef1(0)
    {
    }

    J3DAlphaComp(const J3DAlphaCompInfo& info) { setAlphaCompInfo(info); }

    void setAlphaCompInfo(const J3DAlphaCompInfo& info)
    {
        mAlphaCmpID = calcAlphaCmpID(info.mComp0, info.mOp, info.mComp1);
        mRef0       = info.mRef0;
        mRef1       = info.mRef1;
    }

    void load() { J3DGDSetAlphaCompare(getComp0(), getRef0(), getOp(), getComp1(), getRef1()); }

    GXCompare getComp0() const { return GXCompare(j3dAlphaCmpTable[mAlphaCmpID * 3]); }
    GXAlphaOp getOp() const { return GXAlphaOp(j3dAlphaCmpTable[mAlphaCmpID * 3 + 1]); }
    GXCompare getComp1() const { return GXCompare(j3dAlphaCmpTable[mAlphaCmpID * 3 + 2]); }
    u8 getRef0() const { return mRef0; }
    u8 getRef1() const { return mRef1; }

    u16 mAlphaCmpID; // _00
    u8 mRef0;        // _02
    u8 mRef1;        // _03
};

struct J3DBlendInfo {
    inline J3DBlendInfo& operator=(const J3DBlendInfo& other)
    {
        mBlendMode = other.mBlendMode;
        mSrcFactor = other.mSrcFactor;
        mDstFactor = other.mDstFactor;
        mLogicOp   = other.mLogicOp;
        return *this;
    }

    u8 mBlendMode; // _00
    u8 mSrcFactor; // _01
    u8 mDstFactor; // _02
    u8 mLogicOp;   // _03
};

extern const J3DBlendInfo j3dDefaultBlendInfo;

struct J3DBlend : public J3DBlendInfo {
    J3DBlend() { *(J3DBlendInfo*)this = j3dDefaultBlendInfo; }
    J3DBlend(const J3DBlendInfo& info) { *(J3DBlendInfo*)this = info; }

    GXBlendMode getBlendMode() const { return (GXBlendMode)mBlendMode; }
    GXBlendFactor getSrcFactor() const { return (GXBlendFactor)mSrcFactor; }
    GXBlendFactor getDstFactor() const { return (GXBlendFactor)mDstFactor; }
    GXLogicOp getLogicOp() const { return (GXLogicOp)mLogicOp; }

    void load(u8 ditherEnable) { J3DGDSetBlendMode(getBlendMode(), getSrcFactor(), getDstFactor(), getLogicOp(), ditherEnable); }

    void setType(u8 i_type) { mBlendMode = i_type; }

    void setSrcFactor(u8 i_src) { mSrcFactor = i_src; }

    void setDstFactor(u8 i_dst) { mDstFactor = i_dst; }
};

struct J3DZModeInfo {
    u8 mCompareEnable; // _00
    u8 mFunc;          // _01
    u8 mUpdateEnable;  // _02
    u8 _03;            // _03, padding
};

inline u16 calcZModeID(u32 param_0, u32 param_1, u32 param_2) { return (param_1 * 2) + (param_0 * 0x10) + param_2; }

extern u8 j3dZModeTable[96];

extern const u16 j3dDefaultZModeID;

struct J3DZMode {
    J3DZMode() { mZModeID = j3dDefaultZModeID; }
    explicit J3DZMode(const J3DZModeInfo& info) { setZModeInfo(info); }

    u8 getCompareEnable() const { return j3dZModeTable[mZModeID * 3 + 0]; }
    u8 getFunc() const { return j3dZModeTable[mZModeID * 3 + 1]; }
    u8 getUpdateEnable() const { return j3dZModeTable[mZModeID * 3 + 2]; }

    void setZModeInfo(const J3DZModeInfo& info)
    {
        u32 compareEn = info.mCompareEnable;
        mZModeID      = calcZModeID(compareEn, info.mFunc, info.mUpdateEnable);
    }

    void load() const { J3DGDSetZMode(getCompareEnable(), GXCompare(getFunc()), getUpdateEnable()); }

    void setCompareEnable(u8 i_compare)
    {
        mZModeID = calcZModeID(i_compare, j3dZModeTable[mZModeID * 3 + 1], j3dZModeTable[mZModeID * 3 + 2]);
    }

    void setUpdateEnable(u8 i_enable) { mZModeID = calcZModeID(j3dZModeTable[mZModeID * 3], j3dZModeTable[mZModeID * 3 + 1], i_enable); }

    u16 mZModeID; // _00
};

struct J3DColorChanInfo {
    u8 mEnable;    // _00
    u8 mMatSrc;    // _01
    u8 mLightMask; // _02
    u8 mDiffuseFn; // _03
    u8 mAttnFn;    // _04
    u8 mAmbSrc;    // _05
    u8 _06;        // _06
    u8 _07;        // _07
};

extern const J3DColorChanInfo j3dDefaultColorChanInfo;

inline u16 calcColorChanID(u16 enable, u8 matSrc, u8 lightMask, u8 diffuseFn, u8 attnFn, u8 ambSrc)
{
    u32 reg = 0;
    reg     = reg & ~0x0002 | enable << 1;
    reg     = reg & ~0x0001 | matSrc;
    reg     = reg & ~0x0040 | ambSrc << 6;
    reg     = reg & ~0x0004 | bool(lightMask & 0x01) << 2;
    reg     = reg & ~0x0008 | bool(lightMask & 0x02) << 3;
    reg     = reg & ~0x0010 | bool(lightMask & 0x04) << 4;
    reg     = reg & ~0x0020 | bool(lightMask & 0x08) << 5;
    reg     = reg & ~0x0800 | bool(lightMask & 0x10) << 11;
    reg     = reg & ~0x1000 | bool(lightMask & 0x20) << 12;
    reg     = reg & ~0x2000 | bool(lightMask & 0x40) << 13;
    reg     = reg & ~0x4000 | bool(lightMask & 0x80) << 14;
    reg     = reg & ~0x0180 | (attnFn == GX_AF_SPEC ? 0 : diffuseFn) << 7;
    reg     = reg & ~0x0200 | (attnFn != GX_AF_NONE) << 9;
    reg     = reg & ~0x0400 | (attnFn != GX_AF_SPEC) << 10;
    return reg;
}

inline u32 setChanCtrlMacro(u8 enable, GXColorSrc ambSrc, GXColorSrc matSrc, u32 lightMask, GXDiffuseFn diffuseFn, GXAttnFn attnFn)
{
    u32 ret = matSrc << 0; // Putting this as a separate statement fixes codegen, but regalloc is still wrong
    return ret | enable << 1 | (lightMask & 0x0F) << 2 | ambSrc << 6 | ((attnFn == GX_AF_SPEC) ? GX_DF_NONE : diffuseFn) << 7
         | (attnFn != GX_AF_NONE) << 9 | (attnFn != GX_AF_SPEC) << 10 | (lightMask >> 4 & 0x0F) << 11;
}

struct J3DColorChan {
    J3DColorChan() { setColorChanInfo(j3dDefaultColorChanInfo); }

    J3DColorChan(const J3DColorChanInfo& info)
    {
        mChanCtrl = calcColorChanID(info.mEnable, info.mMatSrc, info.mLightMask, info.mDiffuseFn, info.mAttnFn,
                                    info.mAmbSrc == 0xFF ? 0 : info.mAmbSrc);
    }

    J3DColorChan(u16 id)
        : mChanCtrl(id)
    {
    }

    void setColorChanInfo(const J3DColorChanInfo& info)
    {
        // Bug: It compares info.mAmbSrc (an 8 bit integer) with 0xFFFF instead of 0xFF.
        // This inline is only called by the default constructor J3DColorChan().
        // The J3DColorChan(const J3DColorChanInfo&) constructor does not call this inline, and instead duplicates the
        // same logic but without the bug.
        // See J3DMaterialFactory::newColorChan - both the bugged and correct behavior are present there, as it calls
        // both constructors.
        mChanCtrl = calcColorChanID(info.mEnable, info.mMatSrc, info.mLightMask, info.mDiffuseFn, info.mAttnFn,
                                    info.mAmbSrc == 0xFFFF ? 0 : info.mAmbSrc);
    }

    GXAttnFn getAttnFn();
    GXDiffuseFn getDiffuseFn() { return GXDiffuseFn(mChanCtrl >> 7 & 3); }
    u8 getLightMask() { return ((mChanCtrl >> 2 & 0x0f) | (mChanCtrl >> 11 & 0x0f) << 4); }
    void setLightMask(u8 mask)
    {
        mChanCtrl = (mChanCtrl & ~0x003c) | ((mask & 0x0F) << 2);
        mChanCtrl = (mChanCtrl & ~0x7800) | ((mask & 0xF0) << 7);
    }
    GXColorSrc getMatSrc() { return GXColorSrc(mChanCtrl >> 0 & 0x01); }
    GXColorSrc getAmbSrc() { return GXColorSrc(mChanCtrl >> 6 & 0x01); }
    u8 getEnable() { return !!(mChanCtrl & 0x02); }
    void load()
    {
        // something in here is not quite right still
        J3DGDWrite_u32(setChanCtrlMacro(getEnable(), getAmbSrc(), getMatSrc(), getLightMask(), getDiffuseFn(), getAttnFn()));
    }

    u16 mChanCtrl; // _00
};

// IDK what the structure of this is meant to be
struct J3DIndTevStageInfo {
    u8 mIndStage;  // _00
    u8 mIndFormat; // _01
    u8 mBiasSel;   // _02
    u8 mMtxSel;    // _03
    u8 mWrapS;     // _04
    u8 mWrapT;     // _05
    u8 mPrev;      // _06
    u8 mLod;       // _07
    u8 mAlphaSel;  // _08
    u8 _09;        // _09, padding?
    u8 _0A;        // _0A, padding?
    u8 _0B;        // _0B, padding?
};

extern const J3DIndTevStageInfo j3dDefaultIndTevStageInfo;

struct J3DIndTevStage {
    J3DIndTevStage()
    {
        mInfo = 0;
        setIndTevStageInfo(j3dDefaultIndTevStageInfo);
    }

    J3DIndTevStage(const J3DIndTevStageInfo& info)
    {
        mInfo = 0;
        setIndTevStageInfo(info);
    }

    void setIndStage(u32 stage) { mInfo = mInfo & ~0x03 | stage; }
    void setIndFormat(u32 format) { mInfo = mInfo & ~0x0C | format << 2; }
    void setBiasSel(u32 sel) { mInfo = mInfo & ~0x70 | sel << 4; }
    void setAlphaSel(u32 sel) { mInfo = mInfo & ~0x0180 | sel << 7; }
    void setMtxSel(u32 sel) { mInfo = mInfo & ~0x1E00 | sel << 9; }
    void setWrapS(u32 wrap) { mInfo = mInfo & ~0xE000 | wrap << 13; }
    void setWrapT(u32 wrap) { mInfo = mInfo & ~0x070000 | wrap << 16; }
    void setLod(u32 lod) { mInfo = mInfo & ~0x080000 | lod << 19; }
    void setPrev(u32 prev) { mInfo = mInfo & ~0x100000 | prev << 20; }

    void setIndTevStageInfo(const J3DIndTevStageInfo& info)
    {
        setIndStage(info.mIndStage);
        setIndFormat(info.mIndFormat);
        setBiasSel(info.mBiasSel);
        setMtxSel(info.mMtxSel);
        setWrapS(info.mWrapS);
        setWrapT(info.mWrapT);
        setPrev(info.mPrev);
        setLod(info.mLod);
        setAlphaSel(info.mAlphaSel);
    }

    void load(u32 p1) { J3DGDWriteBPCmd(mInfo | (p1 + 16) << 24); }

    u32 mInfo; // _00, bitflag
};

struct J3DLightObj {
    JGeometry::TVec3f mPosition;  // _00
    JGeometry::TVec3f mDirection; // _0C
    _GXColor mLightColor;         // _18
    f32 _1C;                      // _1C
    f32 _20;                      // _20
    f32 _24;                      // _24
    f32 _28;                      // _28
    f32 _2C;                      // _2C
    f32 _30;                      // _30

    void load(u32) const;
};

struct J3DTevOrderInfo {
    inline J3DTevOrderInfo& operator=(const J3DTevOrderInfo& other)
    {
        mTexCoordID = other.mTexCoordID;
        mTexMapID   = other.mTexMapID;
        mChannelID  = other.mChannelID;
        return *this;
    }

    u8 mTexCoordID; // _00
    u8 mTexMapID;   // _01
    u8 mChannelID;  // _02
    u8 _03;         // _03 - unknown/padding
};

extern const J3DTevOrderInfo j3dDefaultTevOrderInfoNull;

struct J3DTevOrder : public J3DTevOrderInfo {
    J3DTevOrder() { *(J3DTevOrderInfo*)this = j3dDefaultTevOrderInfoNull; }

    /** @fabricated */
    inline J3DTevOrder(const J3DTevOrderInfo& info) { *(J3DTevOrderInfo*)this = info; }

    inline void setTexCoordID(GXTexCoordID id) { mTexCoordID = id; }
    inline void setTexMapID(GXTexMapID id) { mTexMapID = id; }
    inline void setChannelID(u8 id) { mChannelID = id; }

    J3DTevOrderInfo& getTevOrderInfo() { return *this; }
    u8 getTexMap() { return mTexMapID; }
};

struct J3DTevSwapModeInfo {
    u8 mRasSel; // _00
    u8 mTexSel; // _01
};

struct J3DTevSwapModeTableInfo {
    u8 mR; // _00
    u8 mG; // _01
    u8 mB; // _02
    u8 mA; // _03
};

extern const J3DTevSwapModeInfo j3dDefaultTevSwapMode;
extern const J3DTevSwapModeTableInfo j3dDefaultTevSwapModeTable;
extern const u8 j3dDefaultTevSwapTableID;

/**
 * @size{0x1}
 */
struct J3DTevSwapModeTable {
    J3DTevSwapModeTable() { mTevSwapID = j3dDefaultTevSwapTableID; }
    J3DTevSwapModeTable(const J3DTevSwapModeTableInfo& info) { mTevSwapID = calcTevSwapTableID(info.mR, info.mG, info.mB, info.mA); }

    u8 calcTevSwapTableID(u32 r, u32 g, u32 b, u32 a) { return 0x40 * r + 0x10 * g + 4 * b + a; }

    u8 getR() { return j3dTevSwapTableTable[mTevSwapID * 4]; }
    u8 getG() { return j3dTevSwapTableTable[mTevSwapID * 4 + 1]; }
    u8 getB() { return j3dTevSwapTableTable[mTevSwapID * 4 + 2]; }
    u8 getA() { return j3dTevSwapTableTable[mTevSwapID * 4 + 3]; }

    u8 mTevSwapID; // _00
};

struct J3DTevStageInfo {
    u8 mTevStageMode; // _00
    u8 mColorInA;     // _01
    u8 mColorInB;     // _02
    u8 mColorInC;     // _03
    u8 mColorInD;     // _04
    u8 mColorOp;      // _05
    u8 mColorBias;    // _06
    u8 mColorScale;   // _07
    bool mColorClamp; // _08
    u8 mColorRegID;   // _09
    u8 mAlphaInA;     // _0A
    u8 mAlphaInB;     // _0B
    u8 mAlphaInC;     // _0C
    u8 mAlphaInD;     // _0D
    u8 mAlphaOp;      // _0E
    u8 mAlphaBias;    // _0F
    u8 mAlphaScale;   // _10
    bool mAlphaClamp; // _11
    u8 mAlphaRegID;   // _12
    u8 _13;           // _13 - unknown
};
extern const J3DTevStageInfo j3dDefaultTevStageInfo;

struct J3DTevStage {
    J3DTevStage()
    {
        setTevStageInfo(j3dDefaultTevStageInfo);
        setTevSwapModeInfo(j3dDefaultTevSwapMode);
    }

    J3DTevStage(const J3DTevStageInfo& info)
    {
        setTevStageInfo(info);
        setTevSwapModeInfo(j3dDefaultTevSwapMode);
    }

    inline J3DTevStage& operator=(const J3DTevStage& other)
    {
        mTevColorOp      = other.mTevColorOp;
        mTevColorAB      = other.mTevColorAB;
        mTevColorCD      = other.mTevColorCD;
        mTevAlphaOp      = other.mTevAlphaOp;
        mTevAlphaAB      = other.mTevAlphaAB;
        mTevSwapModeInfo = other.mTevSwapModeInfo;
        return *this;
    }

    void setTevColorOp(u8 param_1, u8 param_2, u8 param_3, u8 param_4, u8 param_5)
    {
        mTevColorOp = mTevColorOp & ~(0x01 << 2) | param_1 << 2;
        if (param_1 <= 1) {
            mTevColorOp = mTevColorOp & ~(0x03 << 4) | param_3 << 4;
            mTevColorOp = mTevColorOp & ~0x03 | param_2;
        } else {
            mTevColorOp = mTevColorOp & ~(0x03 << 4) | (param_1 >> 1 & 3) << 4;
            mTevColorOp = mTevColorOp & ~0x03 | 3;
        }
        mTevColorOp = mTevColorOp & ~(0x01 << 3) | param_4 << 3;
        mTevColorOp = mTevColorOp & ~(0x03 << 6) | param_5 << 6;
    }
    void setTevColorAB(u8 a, u8 b) { mTevColorAB = a << 4 | b; }
    void setTevColorCD(u8 c, u8 d) { mTevColorCD = c << 4 | d; }
    void setAlphaA(u8 a) { mTevAlphaAB = mTevAlphaAB & ~(0x07 << 5) | a << 5; }
    void setAlphaB(u8 b) { mTevAlphaAB = mTevAlphaAB & ~(0x07 << 2) | b << 2; }
    void setAlphaC(u8 c)
    {
        mTevAlphaAB      = mTevAlphaAB & ~0x03 | c >> 1;
        mTevSwapModeInfo = mTevSwapModeInfo & ~(0x01 << 7) | c << 7;
    }
    void setAlphaD(u8 d) { mTevSwapModeInfo = mTevSwapModeInfo & ~(0x07 << 4) | d << 4; }
    void setAlphaABCD(u8 a, u8 b, u8 c, u8 d)
    {
        setAlphaA(a);
        setAlphaB(b);
        setAlphaC(c);
        setAlphaD(d);
    }
    void setTevAlphaOp(u8 param_1, u8 param_2, u8 param_3, u8 param_4, u8 param_5)
    {
        mTevAlphaOp = mTevAlphaOp & ~(0x01 << 2) | param_1 << 2;
        if (param_1 <= 1) {
            mTevAlphaOp = mTevAlphaOp & ~0x03 | param_2;
            mTevAlphaOp = mTevAlphaOp & ~(0x03 << 4) | param_3 << 4;
        } else {
            mTevAlphaOp = mTevAlphaOp & ~(0x03 << 4) | (param_1 >> 1 & 3) << 4;
            mTevAlphaOp = mTevAlphaOp & ~0x03 | 3;
        }
        mTevAlphaOp = mTevAlphaOp & ~(0x01 << 3) | param_4 << 3;
        mTevAlphaOp = mTevAlphaOp & ~(0x03 << 6) | param_5 << 6;
    }

    void setTevStageInfo(const J3DTevStageInfo& info)
    {
        setTevColorOp(info.mColorOp, info.mColorBias, info.mColorScale, info.mColorClamp, info.mColorRegID);
        setTevColorAB(info.mColorInA, info.mColorInB);
        setTevColorCD(info.mColorInC, info.mColorInD);
        setAlphaABCD(info.mAlphaInA, info.mAlphaInB, info.mAlphaInC, info.mAlphaInD);
        setTevAlphaOp(info.mAlphaOp, info.mAlphaBias, info.mAlphaScale, info.mAlphaClamp, info.mAlphaRegID);
    }

    void setTexSel(u32 newTexSel) { mTevSwapModeInfo = mTevSwapModeInfo & ~0x0C | newTexSel << 2; }
    void setRasSel(u32 newRasSel) { mTevSwapModeInfo = mTevSwapModeInfo & ~0x03 | newRasSel; }
    void setTevSwapModeInfo(const J3DTevSwapModeInfo& info)
    {
        setTexSel(info.mTexSel);
        setRasSel(info.mRasSel);
    }

    void load(u32) const
    {
        J3DGDWriteBPCmd(*(u32*)&mBPCommand1);
        J3DGDWriteBPCmd(*(u32*)&mBPCommand2);
    }

    u8 mBPCommand1;      // _00
    u8 mTevColorOp;      // _01
    u8 mTevColorAB;      // _02
    u8 mTevColorCD;      // _03
    u8 mBPCommand2;      // _04
    u8 mTevAlphaOp;      // _05
    u8 mTevAlphaAB;      // _06
    u8 mTevSwapModeInfo; // _07
};

struct J3DTexCoordInfo {
    void operator=(J3DTexCoordInfo const& other)
    {
        mTexGenType = other.mTexGenType;
        mTexGenSrc  = other.mTexGenSrc;
        mTexGenMtx  = other.mTexGenMtx;
    }

    u8 mTexGenType; // _00
    u8 mTexGenSrc;  // _01
    u8 mTexGenMtx;  // _02
    u8 _03;         // _03, padding
};

extern const J3DTexCoordInfo j3dDefaultTexCoordInfo[8];

struct J3DTexCoord : public J3DTexCoordInfo {
    J3DTexCoord()
    {
        *(J3DTexCoordInfo*)this = j3dDefaultTexCoordInfo[0];
        resetTexMtxReg();
    }
    J3DTexCoord(const J3DTexCoordInfo& info)
    {
        *(J3DTexCoordInfo*)this = info;
        resetTexMtxReg();
    }

    void setTexCoordInfo(J3DTexCoordInfo* info) { *(J3DTexCoordInfo*)this = *info; }

    void operator=(const J3DTexCoord& other)
    {
        mTexGenType = other.mTexGenType;
        mTexGenSrc  = other.mTexGenSrc;
        mTexGenMtx  = other.mTexGenMtx;
    }

    u8 getTexGenType() { return mTexGenType; }
    u8 getTexGenSrc() { return mTexGenSrc; }
    u8 getTexGenMtx() { return mTexGenMtx & 0xFF; }
    u16 getTexMtxReg() { return mTexMtxReg & 0xFF; }

    void setTexMtxReg(u16 reg) { mTexMtxReg = reg; }
    void setTexGenMtx(u8 mtx) { mTexGenMtx = mtx; }
    void resetTexMtxReg() { mTexMtxReg = mTexGenMtx; }

    // _00-_04 = J3DTexCoordInfo
    u16 mTexMtxReg; // _04
};

extern u8 j3dTexCoordTable[7623];

struct J3DTextureSRTInfo {
    f32 mScaleX;       // _00
    f32 mScaleY;       // _04
    s16 mRotation;     // _08
    f32 mTranslationX; // _0C
    f32 mTranslationY; // _10
};

// hate this but whatever's in here can't have constructors bc of J3DTransform
struct J3DTransformInfo {
    inline J3DTransformInfo& operator=(const J3DTransformInfo& b)
    {
        mScale       = b.mScale;
        mRotation    = b.mRotation;
        mTranslation = b.mTranslation;
        return *this;
    }

    Vec mScale;         // _00
    S16Vec mRotation;   // _0C
    Vec mTranslation;   // _14
};

extern const J3DTransformInfo j3dDefaultTransformInfo;

struct J3DNBTScaleInfo {
    inline void operator=(const J3DNBTScaleInfo& other)
    {
        mHasScale = other.mHasScale;
        mScale    = other.mScale;
    }

    u8 mHasScale; // _00
    Vec mScale;   // _04
};

extern const J3DNBTScaleInfo j3dDefaultNBTScaleInfo;

struct J3DNBTScale : public J3DNBTScaleInfo {
    J3DNBTScale() { *(J3DNBTScaleInfo*)this = j3dDefaultNBTScaleInfo; }

    J3DNBTScale(const J3DNBTScaleInfo& info) { *(J3DNBTScaleInfo*)this = info; }

    Vec* getScale() { return &mScale; }
};

struct J3DTexCoordScaleInfo {
    u16 mScaleS; // _00
    u16 mScaleT; // _02
    u16 mBiasS;  // _04
    u16 mBiasT;  // _06
};

void patchTexNo_PtrToIdx(u32 texID, const u16& idx);

void loadNBTScale(J3DNBTScale&);

void loadTexCoordGens(u32, J3DTexCoord*);

inline void loadTexCoordScale(GXTexCoordID coord, const J3DTexCoordScaleInfo& info)
{
    J3DGDSetTexCoordScale2(coord, info.mScaleS, info.mBiasS == 1, 0, info.mScaleT, info.mBiasT == 1, 0);
}

inline void loadTevColor(u32 reg, const J3DGXColorS10& color) { J3DGDSetTevColorS10(GXTevRegID(reg + 1), (GXColorS10)color); }

inline void loadTevKColor(u32 reg, const J3DGXColor& color) { J3DGDSetTevKColor(GXTevKColorID(reg), (GXColor)color); }

inline void loadZCompLoc(u8 compLoc) { J3DGDSetZCompLoc(compLoc); }

enum J3DTexDiffFlag {
    TEXDIFF_Material = 0,
    TEXDIFF_Default,
};

enum J3DDeformAttachFlag {
    DeformAttach_0 = 0,
    DeformAttach_1 = 1,
};

extern const GXColor j3dDefaultColInfo;
extern const GXColor j3dDefaultAmbInfo;
extern const u8 j3dDefaultColorChanNum;
// extern const J3DGXColor j3dDefaultTevColor;
// extern const J3DGXColorS10 j3dDefaultTevKColor;
extern const GXColorS10 j3dDefaultTevColor;
extern const GXColor j3dDefaultTevKColor;

#endif
