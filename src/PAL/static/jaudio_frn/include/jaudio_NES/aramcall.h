#ifndef _JAUDIO_ARAMCALL_H
#define _JAUDIO_ARAMCALL_H

#include "types.h"

typedef struct jaheap_ jaheap_;

typedef u32 (*ARAMCallback)(char* filename, u32 src, u32 length, u32* status, jaheap_* heap);

void Jac_RegisterARAMCallback(ARAMCallback callback);
u32 LoadAram(char* filepath, u32* status, u32 dst);
u32 LoadAramSingle(char* filepath, u32 src, u32 length, u32* status, u32 dst);
void Jac_WaveDirectorySet(char* directory);
jaheap_* Get_AramMotherHeap(void);
void Show_AramMotherHeap(void);
void Collect_AramMotherHeap(void);
void Init_AramMotherHeap(void);
u32 LoadAram_Default(char* filename, u32 src, u32 length, u32* status, jaheap_* heap);
u32 LoadAram_All(char* filename, u32* status, jaheap_* heap);
u32 LoadAram_One(char* filename, u32 src, u32 length, u32* status, jaheap_* heap);

#endif
