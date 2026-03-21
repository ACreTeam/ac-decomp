/* GCM / ISO virtual filesystem.
 * Stage 1: structure and stubs.  Stage 5: full FST parser + pread. */
#include "platform/platform.h"
#include "gcm_fs.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "platform/endian.h"

/* GCM disc image layout:
 *   0x000: disc header (0x440 bytes)
 *     0x420: boot info (DVDBB2) — FSTPosition, FSTLength, etc.
 *   FST: array of entries, each 12 bytes
 *     entry[0] is root dir: nameOffset[1]=0, parent[4]=0, siblingOrFileCount[4]=total
 *     file entry:  [0]=0x00, [1..3]=nameOfs(24-bit), [4..7]=fileOffset, [8..11]=fileLength
 *     dir  entry:  [0]=0x01, [1..3]=nameOfs(24-bit), [4..7]=parentIdx,  [8..11]=nextIdx
 *   String table: immediately after FST entries
 */

#define GCM_BOOT_HDR_OFFSET  0x420
#define GCM_DISKID_OFFSET    0x000
#define FST_ENTRY_SIZE       12

struct FSTEntry {
    uint8_t  flags;          /* 0=file, 1=dir */
    uint32_t nameOffset;     /* 24-bit, relative to string table start */
    uint32_t fileOffOrParent;
    uint32_t lengthOrNext;
};

struct GcmFS {
    int      fd;
    uint32_t fstOffset;
    uint32_t fstLength;
    uint32_t entryCount;
    uint8_t* fstData;        /* entire FST in memory */
    const char* stringTable; /* pointer into fstData */
};

static GcmFS s_fs = { -1, 0, 0, 0, nullptr, nullptr };

static void parse_fst_entry(const uint8_t* raw, FSTEntry* e) {
    e->flags          = raw[0];
    e->nameOffset     = ((uint32_t)raw[1] << 16) | ((uint32_t)raw[2] << 8) | raw[3];
    e->fileOffOrParent = read_be32(raw + 4);
    e->lengthOrNext    = read_be32(raw + 8);
}

bool gcm_fs_open(const char* iso_path) {
    s_fs.fd = open(iso_path, O_RDONLY);
    if (s_fs.fd < 0) {
        fprintf(stderr, "[DVD] Cannot open disc image: %s\n", iso_path);
        return false;
    }
    /* Read boot info block */
    uint8_t boot[32];
    if (pread(s_fs.fd, boot, 32, GCM_BOOT_HDR_OFFSET) < 32) {
        fprintf(stderr, "[DVD] Cannot read boot header\n");
        return false;
    }
    s_fs.fstOffset  = read_be32(boot + 4);
    s_fs.fstLength  = read_be32(boot + 8);
    if (!s_fs.fstOffset || !s_fs.fstLength) {
        fprintf(stderr, "[DVD] Bad FST offset/length\n");
        return false;
    }
    s_fs.fstData = (uint8_t*)malloc(s_fs.fstLength);
    if (!s_fs.fstData) return false;
    if ((size_t)pread(s_fs.fd, s_fs.fstData, s_fs.fstLength, s_fs.fstOffset)
            < s_fs.fstLength) {
        fprintf(stderr, "[DVD] Cannot read FST\n");
        return false;
    }
    /* Root entry count is in the 'lengthOrNext' of entry 0 */
    FSTEntry root;
    parse_fst_entry(s_fs.fstData, &root);
    s_fs.entryCount  = root.lengthOrNext;
    s_fs.stringTable = (const char*)(s_fs.fstData + s_fs.entryCount * FST_ENTRY_SIZE);
    fprintf(stderr, "[DVD] FST loaded: %u entries\n", s_fs.entryCount);
    return true;
}

/* Resolve a path like "/root/subdir/file.arc" → file offset + length */
bool gcm_fs_lookup(const char* path, uint32_t* out_offset, uint32_t* out_length) {
    if (!s_fs.fstData) return false;
    /* Strip leading slash */
    if (path[0] == '/') path++;
    /* Walk entries linearly matching path components */
    /* Simple linear search for now (adequate for Stage 5) */
    for (uint32_t i = 1; i < s_fs.entryCount; i++) {
        FSTEntry e;
        parse_fst_entry(s_fs.fstData + i * FST_ENTRY_SIZE, &e);
        if (e.flags == 0) { /* file */
            const char* name = s_fs.stringTable + e.nameOffset;
            /* Check if the last component matches (simple filename match) */
            const char* last = strrchr(path, '/');
            const char* want = last ? last + 1 : path;
            if (strcmp(name, want) == 0) {
                if (out_offset) *out_offset = e.fileOffOrParent;
                if (out_length) *out_length = e.lengthOrNext;
                return true;
            }
        }
    }
    return false;
}

bool gcm_fs_read(uint32_t disc_offset, void* buf, uint32_t length) {
    if (s_fs.fd < 0) return false;
    ssize_t r = pread(s_fs.fd, buf, length, (off_t)disc_offset);
    return r == (ssize_t)length;
}

int gcm_fs_get_fd(void)  { return s_fs.fd; }
bool gcm_fs_is_open(void) { return s_fs.fd >= 0; }
