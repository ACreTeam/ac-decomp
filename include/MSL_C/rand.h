#ifndef RAND_H
#define RAND_H
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void srand(u32 seed);
int rand(void);

#ifdef __cplusplus
}
#endif

#endif
