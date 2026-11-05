#ifndef AUS_J2D_ORTHOGRAPH_H
#define AUS_J2D_ORTHOGRAPH_H
#include "JSystem/J2D/J2DGrafContext.h"

struct J2DOrthoGraph : public J2DGrafContext
{
    J2DOrthoGraph();
    J2DOrthoGraph(f32 l, f32 t, f32 r, f32 b, f32 n, f32 f);

    virtual ~J2DOrthoGraph(){};                                           // _08 (weak)
    virtual void setPort();                                               // _14
    virtual J2DGrafType getGrafType() const { return J2DGraf_Ortho; }; // _20 (weak)
    virtual void setLookat();                                           // _24

    void setOrtho(JGeometry::TBox2f const &, f32, f32);
    void scissorBounds(JGeometry::TBox2f *, JGeometry::TBox2f const *);

    f32 getWidthPower() const { return mBounds.getWidth() / mOrtho.getWidth(); }
    f32 getHeightPower() const { return mBounds.getHeight() / mOrtho.getHeight(); }

    void setOrtho(f32 l, f32 t, f32 w, f32 h, f32 n, f32 f)
    {
        setOrtho(JGeometry::TBox2<f32>(l, t, l + w, t + h), n, f);
    }

    const JGeometry::TBox2f &getOrtho() const { return mOrtho; }

    // _00         = VTBL
    // _00-_BC    = J2DGrafContext
    JGeometry::TBox2f mOrtho; // _BC
    f32 mNear;                  // _CC
    f32 mFar;                  // _D0
};

#endif
