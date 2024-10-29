#include "libultra/gu.h"

void guLookAtHilite (Mtx *m, LookAt *l, Hilite *h, 
		float xEye, float yEye, float zEye,
		float xAt,  float yAt,  float zAt,
		float xUp,  float yUp,  float zUp,
		float xl1,  float yl1,  float zl1,   /* light 1 direction */
		float xl2,  float yl2,  float zl2,   /* light 2 direction */
		int twidth, int theight)	     /* highlight txtr size*/
{
	float mf[4][4];

	guLookAtHiliteF(mf, l, h, xEye, yEye, zEye, xAt, yAt, zAt,
			xUp, yUp, zUp, xl1, yl1, zl1, xl2, yl2, zl2,
			twidth, theight);

	guMtxF2L(mf, m);
}