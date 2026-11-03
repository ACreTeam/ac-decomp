#include "arith.h"

int abs(int n) {
    if (n < 0)
        return (-n);
    else
        return (n);
}

long labs(long __x) {
    return __x > 0 ? __x : -__x;
}

div_t div(int numerator, int denominator) {
    div_t ret;
    int i = 1;
    int j = 1;

    if (numerator < 0 ) {
        numerator = -numerator;
        i = -1;
    }

    if (denominator < 0) {
        denominator = -denominator;
        j = -1;
    }

    ret.quot = (numerator / denominator) * (i * j);
    ret.rem = numerator * i - j * (ret.quot * denominator);
    return ret;
}

ldiv_t ldiv(long num, long denom) {
    ldiv_t sp8;
    long var_r5;
    long var_r6;

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

lldiv_t lldiv(long long num, long long denom) {
    lldiv_t sp10;
    long long var_r5;
    long long var_r6;

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
