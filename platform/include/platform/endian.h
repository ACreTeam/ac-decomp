#pragma once
/* Endianness helpers: GameCube (PowerPC) is big-endian; arm64 is little-endian.
 * Every multi-byte value read from disc / assets / save data must be byte-swapped. */

#include <libkern/OSByteOrder.h>
#include <stdint.h>

/* Read big-endian values from unaligned memory pointers (e.g. raw ISO image bytes) */
static inline uint16_t read_be16(const void* p) {
    uint16_t v; __builtin_memcpy(&v, p, 2); return OSSwapBigToHostInt16(v);
}
static inline uint32_t read_be32(const void* p) {
    uint32_t v; __builtin_memcpy(&v, p, 4); return OSSwapBigToHostInt32(v);
}
static inline uint64_t read_be64(const void* p) {
    uint64_t v; __builtin_memcpy(&v, p, 8); return OSSwapBigToHostInt64(v);
}

/* Convenience macros: swap scalar values already loaded into registers */
#define BE16(x) OSSwapBigToHostInt16(x)
#define BE32(x) OSSwapBigToHostInt32(x)
#define BE64(x) OSSwapBigToHostInt64(x)

/* Host-to-big: writing values into structures the game reads as big-endian */
#define HOST_TO_BE16(x) OSSwapHostToBigInt16(x)
#define HOST_TO_BE32(x) OSSwapHostToBigInt32(x)
#define HOST_TO_BE64(x) OSSwapHostToBigInt64(x)
