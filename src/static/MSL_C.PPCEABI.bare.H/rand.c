#include "MSL_C/rand.h"

static unsigned long next = 1;

int rand() {
    next = next * 1103515245 + 12345;
    return ((next >> 16) & 0x7fff);
}

void srand(unsigned long seed) {
    next = seed;
}
