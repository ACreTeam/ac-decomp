/* AI (Audio Interface) shim: replaces GC DMA audio with SDL2 audio callback.
 * Stage 1: stubs.  Stage 10: open SDL2 audio device. */
#include "platform/platform.h"
#include <dolphin/ai.h>
#include <SDL2/SDL.h>
#include <stdint.h>
#include <string.h>

static AIDCallback s_dma_cb       = nullptr;
static uint8_t*    s_dma_addr     = nullptr;
static uint32_t    s_dma_length   = 0;
static uint32_t    s_sample_rate  = 32000;
static bool        s_dma_running  = false;
static SDL_AudioDeviceID s_audio_dev = 0;

/* SDL2 audio callback: called when the audio device needs more samples */
static void sdl_audio_callback(void* /*userdata*/, uint8_t* stream, int len) {
    if (!s_dma_running || !s_dma_addr) {
        memset(stream, 0, (size_t)len);
        return;
    }
    /* TODO Stage 10: call audio_mixer to fill 'stream' */
    memset(stream, 0, (size_t)len);
    /* Signal the game's DMA callback to queue the next buffer */
    if (s_dma_cb) s_dma_cb();
}

extern "C" {

void AIInit(u8* stack) { (void)stack; }

void AISetDSPSampleRate(u32 rate) {
    s_sample_rate = (rate == AI_SAMPLERATE_48KHZ) ? 48000 : 32000;
}
u32 AIGetDSPSampleRate(void) {
    return (s_sample_rate == 48000) ? AI_SAMPLERATE_48KHZ : AI_SAMPLERATE_32KHZ;
}

AIDCallback AIRegisterDMACallback(AIDCallback cb) {
    AIDCallback old = s_dma_cb;
    s_dma_cb = cb;
    return old;
}

void AIInitDMA(u32 start_addr, u32 length) {
    s_dma_addr   = (uint8_t*)(uintptr_t)start_addr;
    s_dma_length = length;
}

void AIStartDMA(void) {
    if (s_audio_dev == 0) {
        SDL_AudioSpec want = {}, got = {};
        want.freq     = (int)s_sample_rate;
        want.format   = AUDIO_S16SYS;
        want.channels = 2;
        want.samples  = 1024;
        want.callback = sdl_audio_callback;
        s_audio_dev = SDL_OpenAudioDevice(nullptr, 0, &want, &got, 0);
        if (s_audio_dev == 0)
            fprintf(stderr, "[AI] SDL_OpenAudioDevice: %s\n", SDL_GetError());
        else
            SDL_PauseAudioDevice(s_audio_dev, 0);
    }
    s_dma_running = true;
}

void AIStopDMA(void)             { s_dma_running = false; }
u32  AIGetDMABytesLeft(void)     { return s_dma_running ? s_dma_length : 0; }
u32  AIGetDMAStartAddr(void)     { return (u32)(uintptr_t)s_dma_addr; }
u32  AIGetDMALength(void)        { return s_dma_length; }
BOOL AIGetDMAEnableFlag(void)    { return s_dma_running ? TRUE : FALSE; }
void AISetStreamPlayState(u32 s) { (void)s; }
u32  AIGetStreamPlayState(void)  { return 0; }
void AISetStreamVolLeft(u8 v)    { (void)v; }
void AISetStreamVolRight(u8 v)   { (void)v; }
u8   AIGetStreamVolLeft(void)    { return 0xFF; }
u8   AIGetStreamVolRight(void)   { return 0xFF; }
void AISetStreamSampleRate(u32 r){ (void)r; }
u32  AIGetStreamSampleRate(void) { return s_sample_rate; }

AISCallback AIRegisterStreamCallback(AISCallback cb) { (void)cb; return nullptr; }

} /* extern "C" */
