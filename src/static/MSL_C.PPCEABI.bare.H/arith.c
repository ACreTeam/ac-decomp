#include "MSL_C/MSL_Common_Embedded/Math/fdlibm.h"
#include "MSL_C/w_math.h"
#include "types.h"
#include "compiler/gcc/stdlib.h" // TODO: we should **not** be using the gcc def for this

u64 __div2i(s32, s32, s32, s32);                    /* extern */

ldiv_t ldiv(s32 num, s32 denom) {
    ldiv_t sp8;
    s32 var_r5;
    s32 var_r6;

    var_r5 = 1;
    var_r6 = 1;
    if (num < 0) {
        num = -num;
        var_r5 = -1;
    }
    if (denom < 0) {
        denom = -denom;
        var_r6 = -1;
    }
    sp8.quot = (num / denom) * (var_r5 * var_r6);
    sp8.rem = (num * var_r5) - (var_r6 * (sp8.quot * denom));
    return sp8;
}

lldiv_t lldiv(s64 num, s64 denom) {
    lldiv_t sp10;
    s64 var_r5;
    s64 var_r6;

    var_r5 = 1;
    var_r6 = 1;
    if (num < 0) {
        num = -num;
        var_r5 = -1;
    }
    if (denom < 0) {
        denom = -denom;
        var_r6 = -1;
    }
    sp10.quot = (num / denom) * (var_r5 * var_r6);
    sp10.rem = (num * var_r5) - (var_r6 * (sp10.quot * denom));
    return sp10;
}
