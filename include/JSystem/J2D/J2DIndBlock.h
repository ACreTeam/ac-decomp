#ifndef J2DINDBLOCK_H
#define J2DINDBLOCK_H

#include "types.h"
#include "JSystem/J3D/J3DTypes.h"
#include "dolphin/gx.h"

#ifdef __cplusplus
typedef float Mtx23[2][3];

struct J2DIndTexCoordScaleInfo {

    GXIndTexScale getScaleS() const {
        return (GXIndTexScale)mScaleS;
    }
    GXIndTexScale getScaleT() const {
        return (GXIndTexScale)mScaleT;
    }

    u8 mScaleS; // _00
    u8 mScaleT; // _01
};

/**
 * @size{0x2}
 */
struct J2DIndTexCoordScale {
    J2DIndTexCoordScale();

    ~J2DIndTexCoordScale() {
    }

    void load(u8);

    J2DIndTexCoordScaleInfo mScaleInfo; // _00
};

struct J2DIndTexMtxInfo {
    Mtx23 mMtx; // _00
    s8 mScale;  // _18
};

/**
 * @size{0x1C}
 */
struct J2DIndTexMtx {
    J2DIndTexMtx();

    ~J2DIndTexMtx() {
    }

    void load(u8);

    J2DIndTexMtxInfo mMtxInfo; // _00
};

extern J2DIndTexMtxInfo j2dDefaultIndTexMtxInfo;

/**
 * @size{0x2}
 */
struct J2DIndTexOrder {
    J2DIndTexOrder();
    void load(u8);

    u8 mCoord; // _00
    u8 mMap;   // _01
};

struct J2DIndBlock {
    virtual void initialize() {
    } // _08 (weak)
    virtual void setGX() {
    }                          // _0C (weak)
    virtual u32 getType() = 0; // _10
    virtual void setIndTexStageNum(u8 texStageNum) {
    } // _14 (weak)
    virtual u8 getIndTexStageNum() const {
        return 0;
    } // _18 (weak)
    virtual void setIndTexOrder(unsigned long index, J2DIndTexOrder order) {
    } // _1C (weak)
    virtual J2DIndTexOrder* getIndTexOrder(unsigned long index) {
        return nullptr;
    } // _20 (weak)
    virtual void setIndTexMtx(unsigned long index, J2DIndTexMtx texMtx) {
    } // _24 (weak)
    virtual J2DIndTexMtx* getIndTexMtx(unsigned long index) {
        return nullptr;
    } // _28 (weak)
    virtual void setIndTexCoordScale(unsigned long index, J2DIndTexCoordScale scale) {
    } // _2C (weak)
    virtual J2DIndTexCoordScale* getIndTexCoordScale(unsigned long index) {
        return nullptr;
    } // _30 (weak)
    virtual ~J2DIndBlock() {
    } // _34 (weak)

    //  _00 VTBL
};

struct J2DIndBlockNull : public J2DIndBlock {
    inline J2DIndBlockNull() : J2DIndBlock() {
    }

    virtual void setGX();       // _0C (weak)
    virtual u32 getType();      // _10 (weak)
    virtual ~J2DIndBlockNull(); // _34 (weak)
};

struct J2DIndBlockFull : public J2DIndBlock {
    inline J2DIndBlockFull() : J2DIndBlock(), mTexOrders(), mTexMtxes(), mTexCoordScales() {
        initialize();
    }

    virtual void initialize(); // _08
    virtual void setGX();      // _0C
    virtual u32 getType() {
        return JBT_IndFull;
    } // _10 (weak)
    virtual void setIndTexStageNum(u8 texStageNum) {
        mTexStageNum = texStageNum;
    } // _14 (weak)
    virtual u8 getIndTexStageNum() const {
        return mTexStageNum;
    } // _18 (weak)
    virtual void setIndTexOrder(unsigned long index, J2DIndTexOrder order) {
        mTexOrders[index] = order;
    } // _1C (weak)
    virtual J2DIndTexOrder* getIndTexOrder(unsigned long index) {
        return mTexOrders + index;
    }                                                       // _20 (weak)
    virtual void setIndTexMtx(unsigned long, J2DIndTexMtx); // _24 (weak)
    virtual J2DIndTexMtx* getIndTexMtx(unsigned long index) {
        return mTexMtxes + index;
    } // _28 (weak)
    virtual void setIndTexCoordScale(unsigned long index, J2DIndTexCoordScale scale) {
        mTexCoordScales[index] = scale;
    } // _2C (weak)
    virtual J2DIndTexCoordScale* getIndTexCoordScale(unsigned long index) {
        return mTexCoordScales + index;
    } // _30 (weak)
    virtual ~J2DIndBlockFull() {
    } // _34 (weak)

    u8 mTexStageNum;              // _04
    J2DIndTexOrder mTexOrders[4]; // _05
    u32 : 0;
    J2DIndTexMtx mTexMtxes[3];              // _10
    J2DIndTexCoordScale mTexCoordScales[4]; // _64
};
#endif

#endif
