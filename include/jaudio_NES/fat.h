#ifndef _JAUDIO_FAT_H
#define _JAUDIO_FAT_H

#include "types.h"

void Jac_FatMemory_Init(u32);
void FAT_InitSystem(u8*, u32);
int FAT_AllocateMemory(u32);
int FAT_FreeMemory(u16);
u8* FAT_GetPointer(u16, u32);
u8 FAT_ReadByte(u16, u32);
u16 FAT_ReadWord(u16, u32);   // UNUSED, but these were probably global
void FAT_ReadWordD(u16, u32); // UNUSED, but these were probably global
u32 FAT_ReadLong(u16, u32);   // UNUSED, but these were probably global
void FAT_ReadLongD(u16, u32); // UNUSED, but these were probably global
int FAT_StoreBlock(u8*, u16, u32, u32);

#endif
