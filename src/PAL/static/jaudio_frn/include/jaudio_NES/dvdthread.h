#ifndef DVDTHREAD_H
#define DVDTHREAD_H

#include "types.h"
#include "dolphin/dvd.h"

typedef void (*Jac_DVDCallback)(u32);
typedef s32 (*TaskCallback)(void*);
typedef void (*ErrorCallback)(char*, u8* addr);

extern void DVDT_ExtendPath(char* dst, char* ext);
extern s32 DVDT_AddTaskHigh(TaskCallback callback, void* stackp, size_t len);
extern s32 DVDT_AddTask(TaskCallback callback, void* stackp, size_t len);
extern void jac_dvdproc_init();
extern void* jac_dvdproc(void*);
extern s32 DVDT_LoadtoARAM_Main(void* arg);
extern s32 DVDT_LoadtoARAM(u32 owner, char* name, u32 dst, u32 src, u32 length, u32* status, Jac_DVDCallback callback);
extern s32 DVDT_ARAMtoDRAM_Main(void* arg);
extern s32 DVDT_DRAMtoARAM_Main(void* arg);
extern s32 DVDT_ARAMtoDRAM(u32 owner, u32 dst, u32 src, u32 length, u32* status, Jac_DVDCallback callback);
extern s32 DVDT_DRAMtoARAM(u32 owner, u32 dst, u32 src, u32 length, u32* status, Jac_DVDCallback callback);
extern s32 DVDT_CheckFile(char* file);
extern s32 DVDT_CheckPass(u32 owner, u32* status, Jac_DVDCallback callback);
extern s32 Jac_CheckFile(char* file);
extern void Jac_RegisterDVDErrorCallback(ErrorCallback callback);
extern s32 Jac_RegisterFastOpen(char* file);
extern BOOL Jac_DVDOpen(char* name, DVDFileInfo* info);


#endif
