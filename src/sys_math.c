#include "sys_math.h"
#include "libultra/libultra.h"
#include "libc64/qrand.h"
#include "libc/math.h"


void init_rnd(){
    sqrand(osGetCount());
}

f32 sinf_table(f32 x){
	f32 max = 3.05185094476e-05f;
    s16 sinf = sins((s16)(10430.0595703f * x));
    return  sinf * max; 
}

f32 cosf_table(f32 x){
	f32 max = 3.05185094476e-05f;
    s16 cosf = coss((s16)(10430.0595703f * x));
    return cosf * max;
}
