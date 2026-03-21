#ifndef RAND_H
#define RAND_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __APPLE__
void srand(unsigned long seed);
int rand(void);
#else
#include <stdlib.h>
#endif

#ifdef __cplusplus
}
#endif

#endif
