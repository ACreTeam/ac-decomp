/* GameCube texture format decoder.
 * Stage 1: function stubs returning empty/black pixels.
 * Stage 8: implement each format. */
#include "platform/platform.h"
#include <dolphin/gx.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* Output: always RGBA8 (4 bytes per pixel) for Metal upload */

extern "C" {

/* Decode a GC texture into a freshly malloc'd RGBA8 buffer.
 * Caller must free() the result.
 * Returns NULL on unsupported format (Stage 1). */
uint8_t* plat_decode_texture(const void* src, GXTexFmt fmt,
                              uint32_t width, uint32_t height) {
    uint32_t pixels = width * height;
    uint8_t* dst = (uint8_t*)calloc(pixels, 4); /* black + transparent */
    if (!dst) return nullptr;

    /* TODO Stage 8: implement each format */
    switch (fmt) {
    case GX_TF_RGBA8:
        /* RGBA8: 4×4 blocks, AR plane then GB plane */
        /* Fall through to stub for now */
        break;
    case GX_TF_RGB565:
        break;
    case GX_TF_RGB5A3:
        break;
    case GX_TF_I4:
        break;
    case GX_TF_I8:
        break;
    case GX_TF_IA4:
        break;
    case GX_TF_IA8:
        break;
    case GX_TF_CMPR:
        break;
    default:
        break;
    }

    return dst;
}

} /* extern "C" */
