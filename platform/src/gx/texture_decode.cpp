/* GameCube texture format decoder → RGBA8 for Metal upload.
 *
 * All GC texture formats store pixels in 4×4 (or 8×4 / 8×8) tiles in
 * row-major tile order.  Multi-byte values in the ROM image are big-endian.
 *
 * Output is always RGBA8 (4 bytes / pixel), row-major, no tiling.
 * Caller must free() the returned buffer.
 */
#include "platform/platform.h"
#include <dolphin/gx.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

extern "C" {

/* ------------------------------------------------------------------ */
/* Helpers                                                              */
/* ------------------------------------------------------------------ */

/* Read a big-endian 16-bit value from unaligned memory */
static inline uint16_t read_be16(const uint8_t* p) {
    return (uint16_t)((p[0] << 8) | p[1]);
}

/* Expand a 5-bit value to 8 bits */
static inline uint8_t expand5(uint8_t v) { return (v << 3) | (v >> 2); }
/* Expand a 6-bit value to 8 bits */
static inline uint8_t expand6(uint8_t v) { return (v << 2) | (v >> 4); }
/* Expand a 4-bit value to 8 bits */
static inline uint8_t expand4(uint8_t v) { return (v << 4) | v; }

/* ------------------------------------------------------------------ */
/* Per-format decoders (write one RGBA8 pixel at *dst)                  */
/* ------------------------------------------------------------------ */

/* GX_TF_I4  — 8×8 tiles, 4 bits per pixel (intensity, no alpha)
 * Two pixels per byte: high nibble = left pixel, low = right pixel.    */
static void decode_I4(const uint8_t* src, uint8_t* rgba,
                      uint32_t width, uint32_t height) {
    const uint32_t tw = 8, th = 8;
    uint32_t tw_count = (width  + tw - 1) / tw;
    uint32_t th_count = (height + th - 1) / th;
    for (uint32_t ty = 0; ty < th_count; ty++) {
        for (uint32_t tx = 0; tx < tw_count; tx++) {
            /* 32 bytes per tile */
            const uint8_t* tile = src + (ty * tw_count + tx) * 32;
            for (uint32_t ly = 0; ly < th; ly++) {
                for (uint32_t lx = 0; lx < tw; lx++) {
                    uint32_t px = tx * tw + lx;
                    uint32_t py = ty * th + ly;
                    if (px >= width || py >= height) continue;
                    uint32_t byte_idx = ly * 4 + lx / 2;
                    uint8_t byte = tile[byte_idx];
                    uint8_t nib  = (lx & 1) ? (byte & 0x0F) : (byte >> 4);
                    uint8_t i    = expand4(nib);
                    uint8_t* d   = rgba + (py * width + px) * 4;
                    d[0] = d[1] = d[2] = i; d[3] = 255;
                }
            }
        }
    }
}

/* GX_TF_I8  — 8×4 tiles, 8 bits per pixel */
static void decode_I8(const uint8_t* src, uint8_t* rgba,
                      uint32_t width, uint32_t height) {
    const uint32_t tw = 8, th = 4;
    uint32_t tw_count = (width  + tw - 1) / tw;
    uint32_t th_count = (height + th - 1) / th;
    for (uint32_t ty = 0; ty < th_count; ty++) {
        for (uint32_t tx = 0; tx < tw_count; tx++) {
            const uint8_t* tile = src + (ty * tw_count + tx) * 32;
            for (uint32_t ly = 0; ly < th; ly++) {
                for (uint32_t lx = 0; lx < tw; lx++) {
                    uint32_t px = tx * tw + lx;
                    uint32_t py = ty * th + ly;
                    if (px >= width || py >= height) continue;
                    uint8_t i  = tile[ly * tw + lx];
                    uint8_t* d = rgba + (py * width + px) * 4;
                    d[0] = d[1] = d[2] = i; d[3] = 255;
                }
            }
        }
    }
}

/* GX_TF_IA4 — 8×4 tiles, 4-bit intensity + 4-bit alpha */
static void decode_IA4(const uint8_t* src, uint8_t* rgba,
                       uint32_t width, uint32_t height) {
    const uint32_t tw = 8, th = 4;
    uint32_t tw_count = (width  + tw - 1) / tw;
    uint32_t th_count = (height + th - 1) / th;
    for (uint32_t ty = 0; ty < th_count; ty++) {
        for (uint32_t tx = 0; tx < tw_count; tx++) {
            const uint8_t* tile = src + (ty * tw_count + tx) * 32;
            for (uint32_t ly = 0; ly < th; ly++) {
                for (uint32_t lx = 0; lx < tw; lx++) {
                    uint32_t px = tx * tw + lx;
                    uint32_t py = ty * th + ly;
                    if (px >= width || py >= height) continue;
                    uint8_t byte = tile[ly * tw + lx];
                    uint8_t i    = expand4(byte >> 4);
                    uint8_t a    = expand4(byte & 0x0F);
                    uint8_t* d   = rgba + (py * width + px) * 4;
                    d[0] = d[1] = d[2] = i; d[3] = a;
                }
            }
        }
    }
}

/* GX_TF_IA8 — 4×4 tiles, 8-bit intensity + 8-bit alpha (BE pair) */
static void decode_IA8(const uint8_t* src, uint8_t* rgba,
                       uint32_t width, uint32_t height) {
    const uint32_t tw = 4, th = 4;
    uint32_t tw_count = (width  + tw - 1) / tw;
    uint32_t th_count = (height + th - 1) / th;
    for (uint32_t ty = 0; ty < th_count; ty++) {
        for (uint32_t tx = 0; tx < tw_count; tx++) {
            const uint8_t* tile = src + (ty * tw_count + tx) * 32;
            for (uint32_t ly = 0; ly < th; ly++) {
                for (uint32_t lx = 0; lx < tw; lx++) {
                    uint32_t px = tx * tw + lx;
                    uint32_t py = ty * th + ly;
                    if (px >= width || py >= height) continue;
                    const uint8_t* p = tile + (ly * tw + lx) * 2;
                    uint8_t i  = p[0];
                    uint8_t a  = p[1];
                    uint8_t* d = rgba + (py * width + px) * 4;
                    d[0] = d[1] = d[2] = i; d[3] = a;
                }
            }
        }
    }
}

/* GX_TF_RGB565 — 4×4 tiles, 16-bit big-endian RGB565 */
static void decode_RGB565(const uint8_t* src, uint8_t* rgba,
                          uint32_t width, uint32_t height) {
    const uint32_t tw = 4, th = 4;
    uint32_t tw_count = (width  + tw - 1) / tw;
    uint32_t th_count = (height + th - 1) / th;
    for (uint32_t ty = 0; ty < th_count; ty++) {
        for (uint32_t tx = 0; tx < tw_count; tx++) {
            const uint8_t* tile = src + (ty * tw_count + tx) * 32;
            for (uint32_t ly = 0; ly < th; ly++) {
                for (uint32_t lx = 0; lx < tw; lx++) {
                    uint32_t px = tx * tw + lx;
                    uint32_t py = ty * th + ly;
                    if (px >= width || py >= height) continue;
                    uint16_t v   = read_be16(tile + (ly * tw + lx) * 2);
                    uint8_t r    = expand5((v >> 11) & 0x1F);
                    uint8_t g    = expand6((v >>  5) & 0x3F);
                    uint8_t b    = expand5((v)       & 0x1F);
                    uint8_t* d   = rgba + (py * width + px) * 4;
                    d[0] = r; d[1] = g; d[2] = b; d[3] = 255;
                }
            }
        }
    }
}

/* GX_TF_RGB5A3 — 4×4 tiles, 16-bit big-endian
 *   bit 15 = 1: RGB555 (A=255)    bit 15 = 0: RGB444 + A3 */
static void decode_RGB5A3(const uint8_t* src, uint8_t* rgba,
                          uint32_t width, uint32_t height) {
    const uint32_t tw = 4, th = 4;
    uint32_t tw_count = (width  + tw - 1) / tw;
    uint32_t th_count = (height + th - 1) / th;
    for (uint32_t ty = 0; ty < th_count; ty++) {
        for (uint32_t tx = 0; tx < tw_count; tx++) {
            const uint8_t* tile = src + (ty * tw_count + tx) * 32;
            for (uint32_t ly = 0; ly < th; ly++) {
                for (uint32_t lx = 0; lx < tw; lx++) {
                    uint32_t px = tx * tw + lx;
                    uint32_t py = ty * th + ly;
                    if (px >= width || py >= height) continue;
                    uint16_t v   = read_be16(tile + (ly * tw + lx) * 2);
                    uint8_t* d   = rgba + (py * width + px) * 4;
                    if (v & 0x8000) {
                        /* RGB5, A=255 */
                        d[0] = expand5((v >> 10) & 0x1F);
                        d[1] = expand5((v >>  5) & 0x1F);
                        d[2] = expand5((v)       & 0x1F);
                        d[3] = 255;
                    } else {
                        /* RGB4, A3 */
                        d[3] = ((v >> 12) & 0x7) * 255 / 7;
                        d[0] = expand4((v >>  8) & 0xF);
                        d[1] = expand4((v >>  4) & 0xF);
                        d[2] = expand4((v)       & 0xF);
                    }
                }
            }
        }
    }
}

/* GX_TF_RGBA8 — 4×4 tiles, 64 bytes each.
 * First 32 bytes: 16 (A,R) pairs.  Second 32 bytes: 16 (G,B) pairs. */
static void decode_RGBA8(const uint8_t* src, uint8_t* rgba,
                         uint32_t width, uint32_t height) {
    const uint32_t tw = 4, th = 4;
    uint32_t tw_count = (width  + tw - 1) / tw;
    uint32_t th_count = (height + th - 1) / th;
    for (uint32_t ty = 0; ty < th_count; ty++) {
        for (uint32_t tx = 0; tx < tw_count; tx++) {
            const uint8_t* tile = src + (ty * tw_count + tx) * 64;
            for (uint32_t ly = 0; ly < th; ly++) {
                for (uint32_t lx = 0; lx < tw; lx++) {
                    uint32_t px = tx * tw + lx;
                    uint32_t py = ty * th + ly;
                    if (px >= width || py >= height) continue;
                    uint32_t idx = ly * tw + lx;
                    uint8_t a    = tile[idx * 2];        /* first plane AR */
                    uint8_t r    = tile[idx * 2 + 1];
                    uint8_t g    = tile[32 + idx * 2];   /* second plane GB */
                    uint8_t b    = tile[32 + idx * 2 + 1];
                    uint8_t* d   = rgba + (py * width + px) * 4;
                    d[0] = r; d[1] = g; d[2] = b; d[3] = a;
                }
            }
        }
    }
}

/* GX_TF_CMPR — S3TC DXT1 variant.
 * 8×8 tiles each holding four 4×4 DXT1 sub-blocks in Z order:
 *   block[0]=(0..3,0..3)  block[1]=(4..7,0..3)
 *   block[2]=(0..3,4..7)  block[3]=(4..7,4..7)
 * Colours are big-endian RGB565. */
static void decode_CMPR(const uint8_t* src, uint8_t* rgba,
                        uint32_t width, uint32_t height) {
    const uint32_t tw = 8, th = 8;
    uint32_t tw_count = (width  + tw - 1) / tw;
    uint32_t th_count = (height + th - 1) / th;
    for (uint32_t ty = 0; ty < th_count; ty++) {
        for (uint32_t tx = 0; tx < tw_count; tx++) {
            const uint8_t* tile = src + (ty * tw_count + tx) * 32;
            /* Four DXT1 sub-blocks */
            for (int sub = 0; sub < 4; sub++) {
                const uint8_t* blk = tile + sub * 8;
                int bx = (sub & 1) * 4;  /* sub-block x offset in tile */
                int by = (sub >> 1) * 4; /* sub-block y offset in tile */

                uint16_t c0v = read_be16(blk);
                uint16_t c1v = read_be16(blk + 2);

                /* Decode the two endpoint colours */
                uint8_t cr[4], cg[4], cb[4];
                cr[0] = expand5((c0v >> 11) & 0x1F);
                cg[0] = expand6((c0v >>  5) & 0x3F);
                cb[0] = expand5((c0v)       & 0x1F);
                cr[1] = expand5((c1v >> 11) & 0x1F);
                cg[1] = expand6((c1v >>  5) & 0x3F);
                cb[1] = expand5((c1v)       & 0x1F);

                if (c0v > c1v) {
                    /* 4-colour mode */
                    cr[2] = (2 * cr[0] + cr[1]) / 3;
                    cg[2] = (2 * cg[0] + cg[1]) / 3;
                    cb[2] = (2 * cb[0] + cb[1]) / 3;
                    cr[3] = (cr[0] + 2 * cr[1]) / 3;
                    cg[3] = (cg[0] + 2 * cg[1]) / 3;
                    cb[3] = (cb[0] + 2 * cb[1]) / 3;
                } else {
                    /* 3-colour + transparent mode */
                    cr[2] = (cr[0] + cr[1]) / 2;
                    cg[2] = (cg[0] + cg[1]) / 2;
                    cb[2] = (cb[0] + cb[1]) / 2;
                    cr[3] = cg[3] = cb[3] = 0; /* transparent */
                }

                /* Pixel indices: 4 bytes, 2 bits per pixel, LSB first */
                for (int row = 0; row < 4; row++) {
                    uint8_t row_bits = blk[4 + row];
                    for (int col = 0; col < 4; col++) {
                        uint32_t px = tx * tw + bx + col;
                        uint32_t py = ty * th + by + row;
                        if (px >= width || py >= height) continue;
                        uint8_t idx  = (row_bits >> (col * 2)) & 0x3;
                        uint8_t* d   = rgba + (py * width + px) * 4;
                        d[0] = cr[idx];
                        d[1] = cg[idx];
                        d[2] = cb[idx];
                        /* alpha: transparent only in 3-colour mode, idx==3 */
                        d[3] = (c0v <= c1v && idx == 3) ? 0 : 255;
                    }
                }
            }
        }
    }
}

/* ------------------------------------------------------------------ */
/* Public decoder dispatcher                                            */
/* ------------------------------------------------------------------ */

uint8_t* plat_decode_texture(const void* src, GXTexFmt fmt,
                              uint32_t width, uint32_t height) {
    if (!src || width == 0 || height == 0) return nullptr;
    uint8_t* dst = (uint8_t*)calloc((size_t)width * height, 4);
    if (!dst) return nullptr;

    const uint8_t* s = (const uint8_t*)src;
    switch (fmt) {
    case GX_TF_I4:     decode_I4    (s, dst, width, height); break;
    case GX_TF_I8:     decode_I8    (s, dst, width, height); break;
    case GX_TF_IA4:    decode_IA4   (s, dst, width, height); break;
    case GX_TF_IA8:    decode_IA8   (s, dst, width, height); break;
    case GX_TF_RGB565: decode_RGB565(s, dst, width, height); break;
    case GX_TF_RGB5A3: decode_RGB5A3(s, dst, width, height); break;
    case GX_TF_RGBA8:  decode_RGBA8 (s, dst, width, height); break;
    case GX_TF_CMPR:   decode_CMPR  (s, dst, width, height); break;
    default:
        /* Unknown / CI format — return magenta so missing textures are obvious */
        for (uint32_t i = 0; i < width * height; i++) {
            dst[i*4+0] = 255; dst[i*4+1] = 0; dst[i*4+2] = 255; dst[i*4+3] = 255;
        }
        break;
    }
    return dst;
}

} /* extern "C" */
