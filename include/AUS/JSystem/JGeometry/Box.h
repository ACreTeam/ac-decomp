#ifndef JGEOMETRY_BOX_H
#define JGEOMETRY_BOX_H

#include <JSystem/JGeometry/Vec.h>
#include "types.h"

namespace JGeometry {
    // Size: 0x10
    template <class T>
    struct TBox
    {
        TBox()
            : i(), f()
        {
        }
        TBox(const TBox &other)
            : i(other.f), f(other.y)
        {
        }

        T i, f;
    };

    // clang-format off
    template<> struct TBox<TVec2<f32> > {
    f32 getWidth() const { return f.x - i.x; }
    f32 getHeight() const { return f.y - i.y; }

    bool isValid() const { return f.isAbove(i); }

    void addPos(f32 x, f32 y) {
        addPos(TVec2<f32>(x, y));
    }

    void addPos(const TVec2<f32>& pos) {
        i.add(pos);
        f.add(pos);
    }

    bool intersect(const TBox<TVec2<f32> >& other) {
        i.setMax(other.i);
        f.setMin(other.f);
        return isValid();
    }

    TVec2<f32> i, f;
};

template <typename T>
struct TBox2 : TBox<TVec2<T> > {
    TBox2() {}
    TBox2(const TVec2<f32>& i, const TVec2<f32> &f) { 
        this->i.set(i);
        this->f.set(f);
    }
    TBox2(f32 x0, f32 y0, f32 x1, f32 y1) { set(x0, y0, x1, y1); }
	TBox2(f32 x0, f32 y0, const TVec2<f32>& f) { set(x0, y0, x0 + f.x, y0 + f.y);	}
	TBox2(f32 val)
	{
		this->f.y = val;
		this->f.x = val;
		this->i.y = val;
		this->i.x = val;
	}

    void absolute() {
        if (!this->isValid()) {
            TBox2<T> box(*this);
            this->i.setMin(box.i);
            this->i.setMin(box.f);
            this->f.setMax(box.i);
            this->f.setMax(box.f);
        }
    }

	// /** @fabricated */
	// TBox2<T>& addingPos(TBox2<T>& result, const TVec2<T>& pos) {
	// 	return TBox2<T>(i.adding(pos), f.adding(pos));
	// }

    void set(const TBox2& other) { set(other.i, other.f); }
    void set(const TVec2<f32>& i, const TVec2<f32>& f) { this->i.set(i), this->f.set(f); }
    void set(f32 x0, f32 y0, f32 x1, f32 y1) { this->i.set(x0, y0); this->f.set(x1, y1); }
};

    // clang-format on
    template <typename T>
    struct TBox3
    {
        T minX;
        T minY;
        T minZ;
        T maxX;
        T maxY;
        T maxZ;
    };

    template <typename T>
    class TDirBox3
    {
    public:
        TVec3<T> _0;
        TVec3<T> _C;
        TVec3<T> _18;
        TVec3<T> _24;
        TVec3<T> _30;
    };

    typedef TBox2<f32> TBox2f;
    typedef TBox3<f32> TBox3f;
    typedef TBox3<TVec3f> TBoxVec3f;
    typedef TDirBox3<f32> TDirBox3f;
}

#endif
