#include "jaudio_NES/neosthread.h"

#include "dolphin/os.h"
#include "jaudio_NES/dummyrom.h"
#include "jaudio_NES/dvdthread.h"
#include "jaudio_NES/aictrl.h"
#include "jaudio_NES/rate.h"
#include "jaudio_NES/audioconst.h"
#include "jaudio_NES/system.h"
#include "jaudio_NES/audiothread.h"
#include "jaudio_NES/cpubuf.h"
#include "jaudio_NES/dummyprobe.h"
#include "jaudio_NES/sub_sys.h"
#include "jaudio_NES/rspsim.h"
#include "jaudio_NES/sample.h"

#define NEOSTHREAD_IMAGE_LOADED_MSG (0x12345678)
#define NEOSTHREAD_ACMD_BUF_NUM 1600

static OSMessageQueue neosproc_mq;
static u32 neosproc_mq_init = FALSE;
static s16* tmp_buf = nullptr;
static BOOL neos_ready = FALSE;

extern u32 Neos_Update(s16* dst) {
    if (neosproc_mq_init) {
        if (OSSendMessage(&neosproc_mq, (OSMessage)dst, OS_MESSAGE_NOBLOCK) == TRUE) {
            return TRUE;
        } else {
            return FALSE;
        }
    }

    return FALSE;
}

extern void ImageLoaded(u32 param) {
    OSSendMessage(&neosproc_mq, (OSMessage)NEOSTHREAD_IMAGE_LOADED_MSG, OS_MESSAGE_BLOCK);
}

extern BOOL Neos_CheckBoot(void) {
    return neos_ready;
}

extern void* neosproc(void* param) {
    static OSMessage msgbuf[1];
    static u32 cur = 0;

    neos_ready = FALSE;
    OSInitMessageQueue(&neosproc_mq, msgbuf, 1);
    neosproc_mq_init = TRUE;
    u32 neos_rom_top = GetNeosRomTop();
    u32 neos_rom_preloaded = GetNeosRom_PreLoaded();
    u32 neos_file_top = GetNeos_FileTop();

    DVDT_LoadtoARAM(0, "/audiorom.img", neos_rom_top + neos_rom_preloaded, neos_file_top, 0, nullptr, &ImageLoaded);

    OSMessage msg;
    do {
        OSReceiveMessage(&neosproc_mq, &msg, 1);
    } while (msg != (OSMessage)NEOSTHREAD_IMAGE_LOADED_MSG);

    tmp_buf = (s16*)OSAlloc2(DAC_SIZE * 2);

    /* Initialize neos */
    s32 tmp = AGC.acmdBufSize;
    u64* acmdBuf = (u64*)OSAlloc2(tmp);
    Nas_InitAudio(acmdBuf, tmp);
    NeosSync();
    neos_ready = TRUE;

    Jac_RegisterMixcallback(&MixCpu, MixMode_Interleave);

    do {
        static Acmd task_buf[2][NEOSTHREAD_ACMD_BUF_NUM];
        static u32 tasks[2] = { 0, 0 };

        OSReceiveMessage(&neosproc_mq, &msg, OS_MESSAGE_BLOCK);
        Probe_Start(8, "NEOS THREAD");
        s16* samples_dst = (s16*)msg;
        tasks[cur] = CreateAudioTask(task_buf[cur], tmp_buf, JAC_FRAMESAMPLES, 0);

        tmp = (cur + 1) & 1;
        if (tasks[tmp]) {
            RspStart2((u32*)task_buf[tmp], tasks[tmp], 0);
            tasks[tmp] = 0;
            Jac_bcopy(tmp_buf, samples_dst, DAC_SIZE * 2);
        } else {
            Jac_bzero(samples_dst, DAC_SIZE * 2);
        }

        Probe_Finish(8);
        NeosSync();
        cur = tmp;
    } while (TRUE);
}
