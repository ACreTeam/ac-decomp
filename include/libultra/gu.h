#ifndef GU_H
#define GU_H
#include "PR/mbi.h"
#include "types.h"
#include "libultra/u64types.h"


inline void guTranslateF(float m[4][4], float x, float y, float z){
    guMtxIdentF(m);
    m[3][0] = x;
    m[3][1] = y;
    m[3][2] = z;
}

inline void guScaleF(float mf[4][4], float x, float y, float z) {
    guMtxIdentF(mf);
    mf[0][0] = x;
    mf[1][1] = y;
    mf[2][2] = z;
    mf[3][3] = 1.0;
}

void guMtxF2L(float mf[4][4], Mtx *m);
void guMtxIdentF(float mf[4][4]);
void guTranslate(Mtx *m, float x, float y, float z);
void guScale(Mtx *m, float x, float y, float z);

void guMtxIdent(Mtx *m);
void guNormalize(float* x, float* y, float* z); 
void guOrtho(Mtx *m, float l, float r, float b, float t, float n, float f, float scale);

void guLookAtHilite (Mtx *m, LookAt *l, Hilite *h, 
		float xEye, float yEye, float zEye,
		float xAt,  float yAt,  float zAt,
		float xUp,  float yUp,  float zUp,
		float xl1,  float yl1,  float zl1,   /* light 1 direction */
		float xl2,  float yl2,  float zl2,   /* light 2 direction */
		int twidth, int theight);	     /* highlight txtr size*/

#endif