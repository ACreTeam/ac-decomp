/* Arena / memory allocation shim — stub only; real allocation via os_shim.cpp */
#include "platform/platform.h"
#include <dolphin/os/OSAlloc.h>
#include <stdlib.h>

extern "C" {

void OSDestroyHeap(int heap) { (void)heap; }
void OSAddToHeap(int heap, void* start, void* end) { (void)heap; (void)start; (void)end; }
long OSCheckHeap(int heap) { (void)heap; return 0; }
unsigned long OSReferentSize(void* ptr) { (void)ptr; return 0; }
void OSDumpHeap(int heap) { (void)heap; }
void OSVisitAllocated(void (*v)(void*, unsigned long)) { (void)v; }
void* OSAllocFixed(void* rstart, void* rend) { (void)rend; return rstart; }

} /* extern "C" */
