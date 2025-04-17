#ifndef HEAPCTRL_H
#define HEAPCTRL_H
#include "types.h"

typedef struct jaheap_ {
    void* _00;
    void* _04;
    void* _08;
} JAHEAP;

JAHEAP* Jac_AllocHeap(jaheap_*, jaheap_*, unsigned long);

#endif
