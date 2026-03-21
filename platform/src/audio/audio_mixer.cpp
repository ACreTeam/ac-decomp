/* Software audio mixer: CPU-side ADPCM decode + voice mixing.
 * Stage 1: skeleton.  Stage 10: implement ADPCM + 64-voice mix. */
#include "platform/platform.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* Fill 'out' with 'num_samples' stereo int16 samples.
 * Called from the SDL2 audio callback in ai_shim.cpp. */
extern "C" void plat_audio_mix(int16_t* out, uint32_t num_samples) {
    /* Stage 1: silence */
    memset(out, 0, num_samples * 2 * sizeof(int16_t));
    /* TODO Stage 10: iterate active voices, ADPCM-decode, mix */
}
