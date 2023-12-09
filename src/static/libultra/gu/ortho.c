#include "libultra/gu.h"

void guOrtho(Mtx *m, float l, float r, float b, float t, float n, float f, float scale)
{
	float mf[4][4];
	guOrthoF(mf, l, r, b, t, n, f, scale);
	guMtxF2L(mf, m);
}