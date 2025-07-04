
/* @(#)s_ldexp.c 1.3 95/01/18 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

/* 
 * scalbn (double x, int n)
 * scalbn(x,n) returns x* 2**n  computed by  exponent  
 * manipulation rather than by actually performing an 
 * exponentiation or a multiplication.
 */

 #include "MSL_C/MSL_Common_Embedded/Math/fdlibm.h"
#include "MSL_C/w_math.h"

#ifdef __STDC__
static const double
#else
static double
#endif
two54   =  1.80143985094819840000e+16, /* 0x43500000, 0x00000000 */
twom54  =  5.55111512312578270212e-17, /* 0x3C900000, 0x00000000 */
huge   = 1.0e+300,
tiny   = 1.0e-300;

#ifdef __STDC__
	double ldexp(double value, int exp)
#else
	double ldexp(value, exp)
	double value; int exp;
#endif
{
	int  k,hx,lx;

	if(!isfinite(value)||value==0.0) return value;

    // scalbn manually inlined from FDLIBM (s_scalbn.c)
	hx = __HI(value);
	lx = __LO(value);
    k = (hx&0x7ff00000)>>20;		/* extract exponent */
    if (k==0) {				/* 0 or subnormal x */
        if ((lx|(hx&0x7fffffff))==0) return value; /* +-0 */
    value *= two54; 
    hx = __HI(value);
    k = ((hx&0x7ff00000)>>20) - 54; 
        if (exp< -50000) return tiny*value; 	/*underflow*/
    }
    if (k==0x7ff) return value+value;		/* NaN or Inf */
    k = k+exp; 
    if (k >  0x7fe) return huge*copysign(huge,value); /* overflow  */
    if (k > 0) 				/* normal result */
    {__HI(value) = (hx&0x800fffff)|(k<<20); return value;}
    if (k <= -54)
        if (exp > 50000) 	/* in case integer overflow in n+k */
    return huge*copysign(huge,value);	/*overflow*/
    else return tiny*copysign(tiny,value); 	/*underflow*/
    k += 54;				/* subnormal result */
    __HI(value) = (hx&0x800fffff)|(k<<20);
    return value*twom54;
    
	return value;
}
