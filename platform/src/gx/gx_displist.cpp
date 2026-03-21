/* GX display list recording/playback.
 * Stage 1: stubs.  Stage 7: record all GX calls into a buffer and replay. */
#include "gx_state.h"
#include <dolphin/gx.h>

extern "C" {

void GXBeginDisplayList(void* list, u32 size) {
    (void)list; (void)size;
    /* TODO Stage 7: start recording GX calls */
}

u32 GXEndDisplayList(void) {
    /* TODO Stage 7: stop recording, return byte count */
    return 0;
}

void GXCallDisplayList(void* list, u32 nbytes) {
    (void)list; (void)nbytes;
    /* TODO Stage 7: replay recorded GX calls */
}

} /* extern "C" */
