#ifndef ARAMCALL_H
#define ARAMCALL_H
#include "types.h"
#include "jaudio_NES/heapctrl.h"

void Jac_WaveDirectorySet(char*);
void Jac_RegisterARAMCallback(u32 (*callback)(char*, u32, u32, u32*, JAHEAP*));
void Init_AramMotherHeap();
JAHEAP* Get_AramMotherHeap();

#endif
