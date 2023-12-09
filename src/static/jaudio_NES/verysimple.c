#include "jaudio_NES/verysimple.h"
#include "jaudio_NES/audiothread.h"
#include "jaudio_NES/aramcall.h"
#include "jaudio_NES/cmdstack.h"
#include "jaudio_NES/seqsetup.h"
#include "jaudio_NES/connect.h"
#include "jaudio_NES/jammain.h"

void Jac_Start(void *heap, u32 heap_size, u32 aram_size) {
    StartAudioThread(heap,heap_size, aram_size, 7);
    Jac_WaveDirectorySet("/");
    Jac_PlayInit();
    Jac_Portcmd_Init();
}
void Jac_PlayInit(void) { // funcalign?
    Jaq_Reset();
    Jac_ConnectTableInit();
    Jam_InitRegistTrack();
}
