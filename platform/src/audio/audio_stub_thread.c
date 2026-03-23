/* audio_stub_thread.c — Minimal audio-system stub for macOS platform.
 *
 * The real audio system is initialised by Nas_InitAudio() which loads
 * /audiorom.img from the disc.  Without a real disc image we skip that
 * path entirely, but the game still expects:
 *
 *   1. AG queues initialised (Nap_AudioPortInit).
 *   2. AUDIO_SYSTEM_READY == TRUE so Nap_SendStart() dispatches commands.
 *   3. A thread that reads commands from thread_cmd_proc_mq and, for
 *      spec-change commands (AUDIOCMD_RESET_AUDIO_HEAP), sends AG.spec_id
 *      back on spec_change_mq so Nap_CheckSpecChange() returns TRUE.
 *
 * Without this, second_game_main waits forever for the audio ACK and the
 * game never reaches the trademark / title screen.
 */
#include "jaudio_NES/os.h"       /* Z_osRecvMesg / Z_osSendMesg / OSMesgQueue */
#include "jaudio_NES/audiowork.h" /* AG (AudioGlobals) */
#include "jaudio_NES/sub_sys.h"  /* Nap_AudioPortInit */
#include "jaudio_NES/system.h"   /* AUDIO_SYSTEM_READY */
#include <pthread.h>

static void* audio_stub_thread_func(void* arg) {
    (void)arg;
    while (1) {
        OSMesg msg;
        /* Block-wait for a command on thread_cmd_proc_mq. */
        Z_osRecvMesg(AG.thread_cmd_proc_mq_p, &msg, OS_MESG_BLOCK);
        /* Only ACK if spec_change_mq has room — avoids flooding the queue.
         * The first ACK lets Nap_CheckSpecChange succeed; subsequent ones
         * are harmless but filling the queue causes "Mesg Full" spam. */
        if (AG.spec_change_mq_p && AG.spec_change_mq_p->validCount < AG.spec_change_mq_p->msgCount) {
            Z_osSendMesg(AG.spec_change_mq_p,
                         (OSMesg)(intptr_t)AG.spec_id,
                         OS_MESG_NOBLOCK);
        }
    }
    return NULL;
}

/* Called from main_apple.mm before the game thread starts. */
void plat_audio_init(void) {
    Nap_AudioPortInit();      /* initialise AG queue pointers and Z_os queues */
    AUDIO_SYSTEM_READY = TRUE; /* let Nap_SendStart() dispatch commands        */

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&tid, &attr, audio_stub_thread_func, NULL);
    pthread_attr_destroy(&attr);
}
