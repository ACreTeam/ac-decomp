#ifndef W_MATH_H
#define W_MATH_H
#include "types.h"

/* this is needed to keep $localstatic$ variables out of the rel */
#ifndef OPTIMIZED_SQRTF
extern inline float sqrtf(float x)
{
	static const double _half=.5;
	static const double _three=3.0;
	volatile float y;
	if(x > 0.0f)
	{
		double guess = __frsqrte((double)x);   // returns an approximation to
		guess = _half*guess*(_three - guess*guess*x);  // now have 12 sig bits
		guess = _half*guess*(_three - guess*guess*x);  // now have 24 sig bits
		guess = _half*guess*(_three - guess*guess*x);  // now have 32 sig bits
		y=(float)(x*guess);
		return y;
	}
	return x;
}
#else
extern inline float sqrtf(float x)
{
	volatile float y;
	if(x > 0.0f)
	{
		double guess = __frsqrte((double)x);   // returns an approximation to
		guess = .5*guess*(3.0 - guess*guess*x);  // now have 12 sig bits
		guess = .5*guess*(3.0 - guess*guess*x);  // now have 24 sig bits
		guess = .5*guess*(3.0 - guess*guess*x);  // now have 32 sig bits
		y=(float)(x*guess);
		return y;
	}
	return x;
}
#endif

extern inline double fabs(double x)
{
   return __fabs(x) ;
}

inline float fabsf(float x) {
	return (float)fabs((double)x);
}

f64 atan2(f64, f64);
f64 acos(f32);

#endif